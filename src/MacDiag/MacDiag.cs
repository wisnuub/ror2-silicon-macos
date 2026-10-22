// Optional in-game diagnostic for the macOS port (built with RoR2_MAC_DIAG=1).
// - Logs startup state, frame-time statistics and input status to Player.log ("[MacDiag]").
// - Autopilot (when /tmp/ror2-autopilot exists): starts a singleplayer run through the game's
//   own console commands and grabs frames to /tmp/ror2-run-*.png, so a build can be verified
//   without anyone at the keyboard.
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using UnityEngine;
using UnityEngine.SceneManagement;

public class MacDiag : MonoBehaviour
{
    // Called from RoR2Application.Awake via a build-time IL patch.
    public static void Boot(GameObject host)
    {
        if (host.GetComponent<MacDiag>() == null) host.AddComponent<MacDiag>();
    }

    static void Log(string s) { Debug.Log("[MacDiag] " + s); }

    static string Arg(string name)
    {
        var args = Environment.GetCommandLineArgs();
        int i = Array.IndexOf(args, name);
        return i >= 0 && i + 1 < args.Length ? args[i + 1] : null;
    }

    string apMode, cmdPath;

    readonly List<float> frameTimes = new List<float>();
    float statsNext, stateNext;
    bool autopilot;
    string apStage = "wait-title";
    float apAt;
    int grabs;
    int burstLeft;

    void DumpHud()
    {
        int n = 0;
        foreach (var g in FindObjectsOfType<UnityEngine.UI.Graphic>())
        {
            var path = g.transform.name; var tr = g.transform.parent;
            for (int d = 0; d < 4 && tr != null; d++, tr = tr.parent) path = tr.name + "/" + path;
            if (!(path.Contains("Health") || path.Contains("health"))) continue;
            var img = g as UnityEngine.UI.Image;
            var mat = g.materialForRendering;
            Log(string.Format("hud {0} type={1} active={2} color={3} shader={4} mat={5} sprite={6} fill={7} rect={8}",
                path, g.GetType().Name, g.isActiveAndEnabled, g.color, mat ? mat.shader.name : "null", mat ? mat.name : "null",
                img && img.sprite ? img.sprite.name : "-", img ? img.fillAmount.ToString() : "-", g.rectTransform.rect.size));
            if (mat && mat.shader.name == "UI/Healthbar")
            {
                Log(string.Format("  props fill=[{0},{1}] rect={2} st={3} color={4} tex={5}",
                    mat.GetFloat("_FillStart"), mat.GetFloat("_FillEnd"), mat.GetVector("_Rect"), mat.GetVector("_MainTex_ST"),
                    mat.GetColor("_Color"), mat.mainTexture ? mat.mainTexture.name + " " + mat.mainTexture.width : "null"));
                healthImages.Add(g);
            }
            if (++n > 40) break;
        }
    }
    readonly List<UnityEngine.UI.Graphic> healthImages = new List<UnityEngine.UI.Graphic>();

    void SwapHealthShader()
    {
        var ui = Shader.Find("UI/Default");
        foreach (var g in healthImages) { var m = new Material(ui); g.material = m; }
        Log("swapped " + healthImages.Count + " health images to UI/Default");
    }

    void Awake()
    {
        apMode = Arg("-autopilot") ?? (System.IO.File.Exists("/tmp/ror2-autopilot") ? System.IO.File.ReadAllText("/tmp/ror2-autopilot") : null);
        autopilot = apMode != null;
        cmdPath = Arg("-diagcmd") ?? "/tmp/ror2-cmd";
        Log("loaded; autopilot=" + autopilot + " cwd=" + Environment.CurrentDirectory);
        Application.logMessageReceived += (msg, trace, type) => {
            if (type == LogType.Exception) Log("EXC: " + msg + "\n" + trace);
        };
    }

    void Update()
    {
        frameTimes.Add(Time.unscaledDeltaTime);
        float now = Time.realtimeSinceStartup;
        if (now >= statsNext) { statsNext = now + 5; LogStats(); }
        if (now >= stateNext) { stateNext = now + 30; LogState(); }
        if (autopilot) Autopilot(now);
        if (now >= cmdNext) { cmdNext = now + 1; RunCommandFile(); }
    }

    float cmdNext;

    // Console lines written to the command file (-diagcmd, default /tmp/ror2-cmd) are submitted once
    // and the file removed. Lines starting with '!' are diagnostic helpers (see Helper).
    void RunCommandFile()
    {
        var path = cmdPath;
        try
        {
            if (!System.IO.File.Exists(path)) return;
            var lines = System.IO.File.ReadAllLines(path);
            System.IO.File.Delete(path);
            foreach (var line in lines)
                if (line.Trim().Length > 0)
                    try { if (line.Trim().StartsWith("!")) Helper(line.Trim().Substring(1).Split(' ')); else Submit(line.Trim()); } catch (Exception e) { Log(line + " failed: " + (e.InnerException ?? e).Message); }
        }
        catch (Exception e) { Log("command file: " + e.Message); }
    }

    void LogStats()
    {
        if (frameTimes.Count == 0) return;
        var sorted = frameTimes.OrderBy(x => x).ToList();
        float avg = frameTimes.Average();
        float p99 = sorted[Mathf.Min(sorted.Count - 1, (int)(sorted.Count * 0.99f))];
        int hitches = frameTimes.Count(x => x > 0.0334f);
        Log(string.Format("perf scene={0} fps={1:F1} avg={2:F1}ms p99={3:F1}ms max={4:F1}ms hitches(>33ms)={5} frames={6} res={7}x{8} vsync={9} target={10}",
            SceneManager.GetActiveScene().name, 1f / avg, avg * 1000, p99 * 1000, sorted[sorted.Count - 1] * 1000, hitches,
            frameTimes.Count, Screen.width, Screen.height, QualitySettings.vSyncCount, Application.targetFrameRate));
        frameTimes.Clear();
    }

    static Assembly Asm(string name)
    {
        return AppDomain.CurrentDomain.GetAssemblies().FirstOrDefault(a => a.GetName().Name == name);
    }

    static object StaticGet(Type t, string name)
    {
        if (t == null) return null;
        var p = t.GetProperty(name, BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
        if (p != null) return p.GetValue(null, null);
        var f = t.GetField(name, BindingFlags.Static | BindingFlags.Public | BindingFlags.NonPublic);
        return f != null ? f.GetValue(null) : null;
    }

    static object InstGet(object o, string name)
    {
        if (o == null) return null;
        var t = o.GetType();
        var p = t.GetProperty(name, BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
        if (p != null) return p.GetValue(o, null);
        var f = t.GetField(name, BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic);
        return f != null ? f.GetValue(o) : null;
    }

    void LogState()
    {
        try
        {
            var rw = Asm("Rewired_Core");
            var reinput = rw == null ? null : rw.GetType("Rewired.ReInput");
            var controllers = StaticGet(reinput, "controllers");
            Log(string.Format("input rewired.ready={0} keyboard={1} mouse={2} joysticks={3} unityMouse={4}",
                StaticGet(reinput, "isReady"), InstGet(controllers, "Keyboard") != null, InstGet(controllers, "Mouse") != null,
                InstGet(controllers, "joystickCount"), Input.mousePresent));
            var ror2 = Asm("RoR2");
            var lum = ror2.GetType("RoR2.LocalUserManager");
            var users = StaticGet(lum, "readOnlyLocalUsersList") as IEnumerable;
            int n = 0;
            if (users != null) foreach (var u in users) n++;
            Log(string.Format("memory textures current={0:F0}MB desired={1:F0}MB total={2:F0}MB nonStreamed={3:F0}MB mipLimit={4} | unity allocated={5:F0}MB reserved={6:F0}MB gfx={7:F0}MB | mono used={8:F0}MB heap={9:F0}MB",
                Texture.currentTextureMemory / 1048576.0, Texture.desiredTextureMemory / 1048576.0, Texture.totalTextureMemory / 1048576.0,
                Texture.nonStreamingTextureMemory / 1048576.0, QualitySettings.masterTextureLimit,
                UnityEngine.Profiling.Profiler.GetTotalAllocatedMemoryLong() / 1048576.0, UnityEngine.Profiling.Profiler.GetTotalReservedMemoryLong() / 1048576.0,
                UnityEngine.Profiling.Profiler.GetAllocatedMemoryForGraphicsDriver() / 1048576.0,
                UnityEngine.Profiling.Profiler.GetMonoUsedSizeLong() / 1048576.0, UnityEngine.Profiling.Profiler.GetMonoHeapSizeLong() / 1048576.0));
            Log("users signedIn=" + StaticGet(lum, "isAnyUserSignedIn") + " count=" + n +
                " gpu=" + SystemInfo.graphicsDeviceName + " quality=" + QualitySettings.GetQualityLevel());
        }
        catch (Exception e) { Log("state error: " + e.Message); }
    }

    static void Helper(string[] a)
    {
        var ror2 = Asm("RoR2");
        switch (a[0])
        {
            case "serverid":
            {
                // Facepunch caches Server.SteamId before logon; ask the GameServer interface directly.
                var server = StaticGet(Asm("Facepunch.Steamworks").GetType("Facepunch.Steamworks.Server"), "Instance");
                var gs = InstGet(InstGet(server, "native"), "gameServer");
                var id = gs == null ? null : gs.GetType().GetMethod("GetSteamID").Invoke(gs, null);
                Log("gameserver steamid=" + id + " loggedOn=" + InstGet(server, "LoggedOn"));
                break;
            }
            case "p2p":
            {
                // Connect to a Steam ID over P2P (what joining a lobby does, without the lobby check).
                var pidType = ror2.GetType("RoR2.PlatformID");
                var hdType = ror2.GetType("RoR2.Networking.HostDescription");
                var pid = Activator.CreateInstance(pidType, new object[] { ulong.Parse(a[1]) });
                var steamType = Enum.Parse(hdType.GetNestedType("HostType"), "Steam");
                var hd = Activator.CreateInstance(hdType, new object[] { pid, steamType });
                var nms = StaticGet(ror2.GetType("RoR2.Networking.NetworkManagerSystem"), "singleton");
                nms.GetType().GetProperty("desiredHost").SetValue(nms, hd, null);
                Log("desiredHost = P2P " + a[1]);
                break;
            }
            case "capture":
            case "endcapture":
            {
                // Wwise records its final mix to a WAV file: lets an unattended run check the audio.
                var se = Asm("AK.Wwise.Unity.API").GetType("AkSoundEngine");
                object r = a[0] == "capture"
                    ? se.GetMethod("StartOutputCapture").Invoke(null, new object[] { a[1] })
                    : se.GetMethod("StopOutputCapture").Invoke(null, null);
                Log(a[0] + " -> " + r);
                break;
            }
            default: Log("unknown helper " + a[0]); break;
        }
    }

    static void Submit(string cmd)
    {
        var console = StaticGet(Asm("RoR2").GetType("RoR2.Console"), "instance");
        var m = console.GetType().GetMethods(BindingFlags.Instance | BindingFlags.Public | BindingFlags.NonPublic)
            .First(x => x.Name == "SubmitCmd" && x.GetParameters().Length >= 2 && x.GetParameters()[1].ParameterType == typeof(string));
        var args = new object[m.GetParameters().Length];
        args[1] = cmd;
        for (int i = 2; i < args.Length; i++) args[i] = m.GetParameters()[i].ParameterType == typeof(bool) ? (object)false : null;
        m.Invoke(console, args);
        Log("autopilot submitted: " + cmd);
    }

    void Grab(string tag)
    {
        var path = "/tmp/ror2-run-" + grabs++ + "-" + tag + ".png";
        ScreenCapture.CaptureScreenshot(path);
        Log("grab " + path);
    }

    void Autopilot(float now)
    {
        string scene = SceneManager.GetActiveScene().name;
        try
        {
            switch (apStage)
            {
                case "wait-title":
                    if (scene == "title") { apStage = "title"; apAt = now + 8; }
                    break;
                case "title":
                    if (now >= apAt)
                    {
                        Grab("title");
                        if (apMode.Contains("audio"))
                        {
                            Helper(new[] { "capture", "/tmp/ror2-title-audio.wav" });
                            apStage = "audio"; apAt = now + 15;
                            break;
                        }
                        var cfg = apMode;
                        var m = System.Text.RegularExpressions.Regex.Match(cfg, @"stage=(\w+)");
                        if (m.Success) Submit("run_scene_override " + m.Groups[1].Value);
                        if (cfg.Contains("host"))
                        {
                            // Multiplayer host test: Steam lobby + listen server (GameServer, P2P).
                            Submit("steam_id");
                            if (cfg.Contains("gsp2p")) Submit("steam_p2p_use_steam_server 1");
                            Submit("steam_lobby_create");
                            apStage = "host-lobby"; apAt = now + 10;
                            break;
                        }
                        Submit("transition_command \"gamemode ClassicRun; host 0;\"");
                        apStage = "wait-lobby"; apAt = now + 60;
                    }
                    break;
                case "audio":
                    if (now >= apAt) { Helper(new[] { "endcapture" }); apStage = "done"; Log("autopilot: finished"); }
                    break;
                case "host-lobby":
                    if (now >= apAt)
                    {
                        Submit("steam_lobby_id");
                        Submit("transition_command \"gamemode ClassicRun; host 1;\"");
                        apStage = "wait-lobby"; apAt = now + 60;
                    }
                    break;
                case "wait-lobby":
                    if (scene == "lobby") { apStage = "lobby"; apAt = now + 8; }
                    else if (now >= apAt) { Log("autopilot: no lobby, scene=" + scene); apStage = "done"; }
                    break;
                case "lobby":
                    if (now >= apAt)
                    {
                        Grab("lobby");
                        var mode = apMode;
                        if (mode.Contains("host"))
                        {
                            foreach (var c in new[] { "steam_lobby_id", "steam_lobby_print_members", "steam_lobby_print_data", "steam_server_print_info" })
                                try { Submit(c); } catch (Exception e) { Log(c + " failed: " + (e.InnerException ?? e).Message); }
                            apStage = "done"; break;
                        }
                        if (mode.Contains("lobby")) { apStage = "done"; break; }
                        Submit("pregame_start_run"); apStage = "wait-stage"; apAt = now + 90;
                    }
                    break;
                case "wait-stage":
                    if (scene != "lobby" && scene != "title" && scene != "loadingbasic")
                    { Log("autopilot: in stage " + scene); apStage = "stage"; apAt = now + 30; }
                    else if (now >= apAt) { Log("autopilot: no stage, scene=" + scene); apStage = "done"; }
                    break;
                case "stage":
                    if (now >= apAt)
                    {
                        DumpHud();
                        apStage = "burst"; burstLeft = 10; apAt = now;
                    }
                    break;
                case "burst":
                    if (burstLeft == 5) SwapHealthShader();
                    if (now >= apAt && burstLeft-- > 0) { Grab(scene); apAt = now + 0.25f; }
                    else if (burstLeft <= 0) { apStage = "done"; Log("autopilot: finished"); }
                    break;
            }
        }
        catch (Exception e) { Log("autopilot error in " + apStage + ": " + e); apStage = "done"; }
    }
}
