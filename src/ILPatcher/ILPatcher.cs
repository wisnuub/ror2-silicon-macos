// Build-time IL patcher for the macOS port. Harmony can't detour methods on arm64 Mono
// (BepInEx 5's MonoMod has no ARM64 backend), so behaviour changes are applied to the
// game assemblies directly with Mono.Cecil.
//
//   mono ILPatcher.exe <Managed dir> [--diag]
//       [--wwise-mac <AkSoundEnginePINVOKE_Mac.cs> --wwise-exports <exports.txt> --wwise-unmatched <out.txt>]
using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using System.Linq;
using Mono.Cecil;
using Mono.Cecil.Cil;

static class ILPatcher
{
    // Run `hook` whenever `method` returns: the final ret becomes the hook call (so branches that
    // target it still reach the hook) followed by a new ret.
    static void HookReturns(MethodDefinition method, MethodReference hook, bool passArg0)
    {
        var il = method.Body.GetILProcessor();
        foreach (var ret in method.Body.Instructions.Where(i => i.OpCode == OpCodes.Ret).ToList())
        {
            var tail = il.Create(OpCodes.Ret);
            il.InsertAfter(ret, tail);
            if (passArg0)
            {
                ret.OpCode = OpCodes.Ldarg_0; ret.Operand = null;
                il.InsertAfter(ret, il.Create(OpCodes.Call, hook));
            }
            else
            {
                ret.OpCode = OpCodes.Call; ret.Operand = hook;
            }
        }
    }

    // Replace a bool-returning method's body with "return value;".
    static void ReturnConstant(ModuleDefinition module, string type, string method, bool value)
    {
        var t = module.GetType(type);
        var targets = t == null ? Enumerable.Empty<MethodDefinition>() : t.Methods.Where(m => m.Name == method && m.HasBody);
        int n = 0;
        foreach (var m in targets)
        {
            m.Body.Instructions.Clear();
            m.Body.ExceptionHandlers.Clear();
            m.Body.Variables.Clear();
            var il = m.Body.GetILProcessor();
            il.Append(il.Create(value ? OpCodes.Ldc_I4_1 : OpCodes.Ldc_I4_0));
            il.Append(il.Create(OpCodes.Ret));
            n++;
        }
        Console.WriteLine("{0}::{1} -> return {2} ({3} overloads)", type, method, value, n);
    }

    // ---- Wwise: rebind the Windows integration's P/Invokes to the macOS engine ----------------

    class MacDecl { public string Entry, Base, Ret, RetMarshal; public string[] Types; public string[] Marshal; }

    static string BaseName(string entry) { return Regex.Replace(entry, "__SWIG_[0-9]+$", ""); }

    static readonly Dictionary<string, string> CsKeywords = new Dictionary<string, string> {
        { "uint", "UInt32" }, { "int", "Int32" }, { "ulong", "UInt64" }, { "long", "Int64" }, { "ushort", "UInt16" },
        { "short", "Int16" }, { "byte", "Byte" }, { "sbyte", "SByte" }, { "bool", "Boolean" }, { "float", "Single" },
        { "double", "Double" }, { "string", "String" }, { "char", "Char" }, { "void", "Void" }, { "object", "Object" } };

    // C# source type ("out uint", "global::System.IntPtr", "UnityEngine.Vector3[]") -> Cecil short name
    static string NormCs(string t)
    {
        t = t.Replace("global::", "").Trim();
        string suffix = "";
        foreach (var mod in new[] { "out ", "ref " })
            if (t.StartsWith(mod)) { t = t.Substring(mod.Length).Trim(); suffix = "&"; }
        string arr = "";
        while (t.EndsWith("[]")) { arr += "[]"; t = t.Substring(0, t.Length - 2).Trim(); }
        string name;
        if (!CsKeywords.TryGetValue(t, out name)) name = t.Substring(t.LastIndexOf('.') + 1);
        return name + arr + suffix;
    }

    static string NormCecil(TypeReference t)
    {
        var br = t as ByReferenceType;
        return br != null ? br.ElementType.Name + "&" : t.Name;
    }

    static List<string> SplitParams(string s)
    {
        var parts = new List<string>(); int depth = 0, last = 0;
        for (int i = 0; i < s.Length; i++)
        {
            char c = s[i];
            if (c == '[' || c == '(' || c == '<') depth++;
            else if (c == ']' || c == ')' || c == '>') depth--;
            else if (c == ',' && depth == 0) { parts.Add(s.Substring(last, i - last)); last = i + 1; }
        }
        if (s.Trim().Length > 0) parts.Add(s.Substring(last));
        return parts;
    }

    static List<MacDecl> ParseMacPinvoke(string path)
    {
        var decls = new List<MacDecl>();
        var rx = new Regex(@"DllImport\(""AkSoundEngine"", EntryPoint=""(?<entry>\w+)""\)\]\s*(\[return: [^\]]*MarshalAs\([^)]*UnmanagedType\.(?<rm>\w+)\)\]\s*)?public static extern (?<ret>[^(]+?) \w+\((?<params>[^;]*)\);");
        foreach (Match m in rx.Matches(File.ReadAllText(path)))
        {
            var types = new List<string>(); var marsh = new List<string>();
            foreach (var raw in SplitParams(m.Groups["params"].Value))
            {
                var p = raw.Trim();
                var ma = Regex.Match(p, @"UnmanagedType\.(\w+)");
                marsh.Add(ma.Success ? ma.Groups[1].Value : null);
                p = Regex.Replace(p, @"^(\[[^\]]*\]\s*)+", "");          // attributes
                p = p.Substring(0, p.LastIndexOf(' '));                    // drop the parameter name
                types.Add(NormCs(p));
            }
            decls.Add(new MacDecl { Entry = m.Groups["entry"].Value, Base = BaseName(m.Groups["entry"].Value),
                Ret = NormCs(m.Groups["ret"].Value), RetMarshal = m.Groups["rm"].Success ? m.Groups["rm"].Value : null,
                Types = types.ToArray(), Marshal = marsh.ToArray() });
        }
        return decls;
    }

    static MarshalInfo ToMarshalInfo(string unmanagedType)
    {
        switch (unmanagedType)
        {
            case null: return null;
            case "LPStr": return new MarshalInfo(NativeType.LPStr);
            case "LPWStr": return new MarshalInfo(NativeType.LPWStr);
            default: return null;   // non-string marshalling is the same on every platform
        }
    }

    static void PatchWwise(string managed, ReaderParameters rp, AssemblyDefinition core, string macPinvoke, string exportsPath, string unmatchedOut)
    {
        string akPath = Path.Combine(managed, "AK.Wwise.Unity.API.dll");
        var ak = AssemblyDefinition.ReadAssembly(akPath, rp);
        var mod = ak.MainModule;
        var exports = new HashSet<string>(File.ReadAllLines(exportsPath));
        var mac = ParseMacPinvoke(macPinvoke).Where(d => exports.Contains(d.Entry)).ToList();
        var byBase = mac.GroupBy(d => d.Base).ToDictionary(g => g.Key, g => g.ToList());
        var compat = new ModuleReference("AkSoundEngineCompat");
        mod.ModuleReferences.Add(compat);

        int kept = 0, renamed = 0, remarshaled = 0;
        var unmatched = new List<string>();
        foreach (var t in mod.GetTypes())
            foreach (var m in t.Methods.Where(x => x.IsPInvokeImpl && x.PInvokeInfo != null && x.PInvokeInfo.Module.Name == "AkSoundEngine"))
            {
                string entry = m.PInvokeInfo.EntryPoint ?? m.Name;
                var types = m.Parameters.Select(p => NormCecil(p.ParameterType)).ToArray();
                string ret = NormCecil(m.ReturnType);
                List<MacDecl> cands;
                MacDecl match = null;
                if (byBase.TryGetValue(BaseName(entry), out cands))
                {
                    var same = cands.Where(d => d.Ret == ret && d.Types.SequenceEqual(types)).ToList();
                    match = same.FirstOrDefault(d => d.Entry == entry) ?? same.FirstOrDefault();
                }
                if (match == null)
                {
                    m.PInvokeInfo.Module = compat;
                    unmatched.Add(entry);
                    continue;
                }
                if (match.Entry != entry) { m.PInvokeInfo.EntryPoint = match.Entry; renamed++; } else kept++;
                bool changed = false;
                // Only string encoding differs by platform (AkOSChar: wchar_t on Windows, char on macOS)
                for (int i = 0; i < m.Parameters.Count; i++)
                {
                    if (types[i] != "String") continue;
                    var want = ToMarshalInfo(match.Marshal[i]);
                    var have = m.Parameters[i].MarshalInfo;
                    if ((want == null) != (have == null) || (want != null && want.NativeType != have.NativeType))
                    {
                        m.Parameters[i].MarshalInfo = want;
                        changed = true;
                    }
                }
                var wantRet = ToMarshalInfo(match.RetMarshal);
                var haveRet = m.MethodReturnType.MarshalInfo;
                if (ret == "String" && ((wantRet == null) != (haveRet == null) || (wantRet != null && wantRet.NativeType != haveRet.NativeType)))
                {
                    m.MethodReturnType.MarshalInfo = wantRet;
                    changed = true;
                }
                if (changed) remarshaled++;
            }
        File.WriteAllLines(unmatchedOut, unmatched.Distinct());
        Console.WriteLine("AK.Wwise.Unity.API: {0} P/Invokes bound as is, {1} rebound to the matching macOS overload, " +
                          "{2} with string encoding fixed, {3} to AkSoundEngineCompat", kept, renamed, remarshaled, unmatched.Count);
        foreach (var u in unmatched) Console.WriteLine("  compat: " + u);

        // OS strings (AkOSChar) are UTF-16 on Windows and UTF-8 on macOS.
        var akSe = mod.GetType("AkSoundEngine");
        var osString = akSe.Methods.First(x => x.Name == "StringFromIntPtrOSString");
        var utf8 = akSe.Methods.First(x => x.Name == "StringFromIntPtrString");
        osString.Body.Instructions.Clear();
        var op = osString.Body.GetILProcessor();
        op.Append(op.Create(OpCodes.Ldarg_0));
        op.Append(op.Create(OpCodes.Call, utf8));
        op.Append(op.Create(OpCodes.Ret));
        Console.WriteLine("AkSoundEngine.StringFromIntPtrOSString -> UTF-8");

        // The Windows build looks for AkSoundEngine.dll to find the plug-in folder and passes NULL
        // on macOS; point Wwise at Contents/PlugIns, where any DSP plug-in bundles are installed.
        var getPluginPath = mod.GetType("AkCommonUserSettings").Methods.First(x => x.Name == "GetPluginPath");
        var appData = mod.ImportReference(core.MainModule.GetType("UnityEngine.Application").Properties.First(p => p.Name == "dataPath").GetMethod);
        var combine = mod.ImportReference(typeof(Path).GetMethod("Combine", new[] { typeof(string), typeof(string) }));
        var getFull = mod.ImportReference(typeof(Path).GetMethod("GetFullPath", new[] { typeof(string) }));
        getPluginPath.Body.Instructions.Clear();
        getPluginPath.Body.ExceptionHandlers.Clear();
        getPluginPath.Body.Variables.Clear();
        var gp = getPluginPath.Body.GetILProcessor();
        gp.Append(gp.Create(OpCodes.Call, appData));                       // <app>/Contents on macOS
        gp.Append(gp.Create(OpCodes.Ldstr, "PlugIns/"));
        gp.Append(gp.Create(OpCodes.Call, combine));
        gp.Append(gp.Create(OpCodes.Call, getFull));
        gp.Append(gp.Create(OpCodes.Ret));
        Console.WriteLine("AkCommonUserSettings.GetPluginPath -> Contents/PlugIns/");

        ak.Write(akPath + ".tmp");
        File.Copy(akPath + ".tmp", akPath, true);
        File.Delete(akPath + ".tmp");
    }

    static int Main(string[] args)
    {
        if (args.Length < 1) { Console.Error.WriteLine("usage: ILPatcher <Managed dir> [--diag]"); return 2; }
        string managed = args[0];
        bool diag = args.Contains("--diag");
        Func<string, string> opt = name => { int i = Array.IndexOf(args, name); return i >= 0 && i + 1 < args.Length ? args[i + 1] : null; };
        string wwiseMac = opt("--wwise-mac"), wwiseExports = opt("--wwise-exports"), wwiseUnmatched = opt("--wwise-unmatched");

        var resolver = new DefaultAssemblyResolver();
        resolver.AddSearchDirectory(managed);
        var rp = new ReaderParameters { AssemblyResolver = resolver, ReadWrite = false, InMemory = true };
        string ror2Path = Path.Combine(managed, "RoR2.dll");
        var ror2 = AssemblyDefinition.ReadAssembly(ror2Path, rp);
        var module = ror2.MainModule;

        var core = resolver.Resolve(AssemblyNameReference.Parse("UnityEngine.CoreModule"));
        if (diag)
        {
            var diagAsm = AssemblyDefinition.ReadAssembly(Path.Combine(managed, "MacDiag.dll"), rp);
            var boot = diagAsm.MainModule.GetType("MacDiag").Methods.First(m => m.Name == "Boot");
            var awake = module.GetType("RoR2.RoR2Application").Methods.First(m => m.Name == "Awake");
            var getGo = module.ImportReference(core.MainModule.GetType("UnityEngine.Component")
                .Properties.First(p => p.Name == "gameObject").GetMethod);
            var il = awake.Body.GetILProcessor();
            var first = awake.Body.Instructions[0];
            il.InsertBefore(first, il.Create(OpCodes.Ldarg_0));
            il.InsertBefore(first, il.Create(OpCodes.Call, getGo));
            il.InsertBefore(first, il.Create(OpCodes.Call, module.ImportReference(boot)));
            Console.WriteLine("patched RoR2Application.Awake -> MacDiag.Boot");

            // RoR2Application's Print* helpers are compiled to empty bodies; route them to Debug.Log
            // so the startup checkpoints ("After PlatformSystems.Init", ...) show up in Player.log.
            var log = module.ImportReference(core.MainModule.GetType("UnityEngine.Debug").Methods
                .First(m => m.Name == "Log" && m.Parameters.Count == 1));
            var concat = module.ImportReference(typeof(string).GetMethod("Concat", new[] { typeof(object), typeof(object) }));
            var format = module.ImportReference(typeof(string).GetMethod("Format", new[] { typeof(string), typeof(object[]) }));
            foreach (var m in module.GetType("RoR2.RoR2Application").Methods.Where(m => m.Name.StartsWith("Print") && m.IsStatic && m.Parameters.Count >= 1))
            {
                m.Body.Instructions.Clear();
                var p = m.Body.GetILProcessor();
                p.Append(p.Create(OpCodes.Ldstr, "[RoR2] " + m.Name + ": "));
                p.Append(p.Create(OpCodes.Ldarg_0));
                if (m.Parameters.Count == 2) { p.Append(p.Create(OpCodes.Ldarg_1)); p.Append(p.Create(OpCodes.Call, format)); }
                p.Append(p.Create(OpCodes.Call, concat));
                p.Append(p.Create(OpCodes.Call, log));
                p.Append(p.Create(OpCodes.Ret));
            }
            Console.WriteLine("enabled RoR2Application.Print* logging");
        }

        // Steamworks: the validator checks the Windows steam_api64.dll signature; on macOS the
        // native library is libsteam_api.dylib, so report it as valid.
        ReturnConstant(module, "SteamAPIValidator.SteamApiValidator", "IsValidSteamApiDll", true);
        ReturnConstant(module, "SteamAPIValidator.SteamApiValidator", "IsValidSteamClientDll", true);

        // Steamworks: when Steam launches a game it sets SteamAppId/SteamGameId. The game deletes
        // steam_appid.txt, so provide the IDs in-process before Facepunch initializes the API.
        var setEnv = module.ImportReference(typeof(Environment).GetMethod("SetEnvironmentVariable", new[] { typeof(string), typeof(string) }));
        var ctor = module.GetType("RoR2.SteamworksClientManager").Methods.First(m => m.IsConstructor && !m.IsStatic);
        var cil = ctor.Body.GetILProcessor();
        var head = ctor.Body.Instructions[0];
        foreach (var name in new[] { "SteamAppId", "SteamGameId" })
        {
            cil.InsertBefore(head, cil.Create(OpCodes.Ldstr, name));
            cil.InsertBefore(head, cil.Create(OpCodes.Ldstr, "632360"));
            cil.InsertBefore(head, cil.Create(OpCodes.Call, setEnv));
        }
        Console.WriteLine("SteamworksClientManager..ctor sets SteamAppId/SteamGameId=632360");

        // Memory: keep at most two decompressed shader chunks per shader (Unity otherwise keeps every
        // chunk it has touched; translated Metal shaders carry MSL source, ~2x the D3D bytecode).
        int chunkLimit = int.Parse(Environment.GetEnvironmentVariable("RoR2_MAC_SHADER_CHUNKS") ?? "0");
        if (chunkLimit > 0)
        {
            var awake2 = module.GetType("RoR2.RoR2Application").Methods.First(m => m.Name == "Awake");
            var setChunks = module.ImportReference(core.MainModule.GetType("UnityEngine.Shader").Methods.First(m => m.Name == "set_maximumChunksOverride"));
            var ap = awake2.Body.GetILProcessor();
            var a0 = awake2.Body.Instructions[0];
            ap.InsertBefore(a0, ap.Create(OpCodes.Ldc_I4, chunkLimit));
            ap.InsertBefore(a0, ap.Create(OpCodes.Call, setChunks));
            Console.WriteLine("RoR2Application.Awake sets Shader.maximumChunksOverride = " + chunkLimit);
        }

        // Settings: keep hardware-specific graphics settings Mac-local (see src/RoR2Mac/MacSettings.cs).
        {
            var mac = AssemblyDefinition.ReadAssembly(Path.Combine(managed, "RoR2Mac.dll"), rp).MainModule.GetType("MacSettings");
            var console = module.GetType("RoR2.Console");
            HookReturns(console.Methods.First(m => m.Name == "LoadUserConfigFile"),
                module.ImportReference(mac.Methods.First(m => m.Name == "AfterUserConfigLoaded")), true);
            HookReturns(console.Methods.First(m => m.Name == "SaveArchiveConVars"),
                module.ImportReference(mac.Methods.First(m => m.Name == "AfterSave")), false);
            Console.WriteLine("Console config load/save hooked for Mac-local graphics settings");
        }

        if (wwiseMac != null)
            PatchWwise(managed, rp, core, wwiseMac, wwiseExports, wwiseUnmatched);
        else
        {
            // Audio: without the macOS Wwise library, Wwise runs through a silent stub, so soundbanks
            // never finish loading and RoR2Application.LoadGameContent would wait forever at 99%.
            ReturnConstant(module, "RoR2.WwiseUtils.SoundbankLoader", "get_doneLoading", true);
        }

        string tmp = ror2Path + ".tmp";
        ror2.Write(tmp);
        File.Copy(tmp, ror2Path, true);
        File.Delete(tmp);
        return 0;
    }
}
