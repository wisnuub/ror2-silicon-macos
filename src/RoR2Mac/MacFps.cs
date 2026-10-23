// Optional on-screen FPS counter for the macOS port (attached at startup by src/ILPatcher).
//
// Apple's Metal HUD counts frames that reach the screen, so on a 60 Hz display it never shows
// more than 60. This counter shows how many frames the game actually renders per second, which is
// the useful number for performance. Toggle with F10, or start the game with -fps.
//
// It is a single uGUI Text on its own overlay canvas, updated twice a second, so it costs nothing
// measurable. (An OnGUI version halved the frame rate on Metal: IMGUI adds its own render pass.)
using System;
using UnityEngine;
using UnityEngine.UI;

public class MacFps : MonoBehaviour
{
    public static void Boot(GameObject host)
    {
        if (host.GetComponent<MacFps>() == null) host.AddComponent<MacFps>();
        if (host.GetComponent<MacDisplaySync>() == null) host.AddComponent<MacDisplaySync>();
    }

    GameObject root;
    Text label;
    int frames;
    float elapsed, worst;

    void Awake()
    {
        if (Array.IndexOf(Environment.GetCommandLineArgs(), "-fps") >= 0) SetVisible(true);
    }

    void SetVisible(bool on)
    {
        if (on && root == null) Create();
        if (root != null) root.SetActive(on);
        frames = 0; elapsed = 0f; worst = 0f;
    }

    void Create()
    {
        root = new GameObject("MacFps");
        DontDestroyOnLoad(root);
        var canvas = root.AddComponent<Canvas>();
        canvas.renderMode = RenderMode.ScreenSpaceOverlay;
        canvas.sortingOrder = 32000;
        var scaler = root.AddComponent<CanvasScaler>();
        scaler.uiScaleMode = CanvasScaler.ScaleMode.ScaleWithScreenSize;
        scaler.referenceResolution = new Vector2(1920, 1080);

        var textGo = new GameObject("Text");
        textGo.transform.SetParent(root.transform, false);
        label = textGo.AddComponent<Text>();
        label.font = Resources.GetBuiltinResource<Font>("Arial.ttf");
        label.fontSize = 18;
        label.fontStyle = FontStyle.Bold;
        label.alignment = TextAnchor.UpperRight;
        label.color = Color.white;
        label.raycastTarget = false;
        var outline = textGo.AddComponent<Outline>();
        outline.effectColor = new Color(0f, 0f, 0f, 0.85f);
        outline.effectDistance = new Vector2(1.5f, -1.5f);
        var rt = label.rectTransform;
        // Small, in the top-right corner above RoR2's stage/timer panel
        rt.anchorMin = new Vector2(1f, 1f); rt.anchorMax = new Vector2(1f, 1f); rt.pivot = new Vector2(1f, 1f);
        rt.anchoredPosition = new Vector2(-10f, -4f);
        rt.sizeDelta = new Vector2(600f, 26f);
        label.text = "FPS";
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.F10)) SetVisible(root == null || !root.activeSelf);
        if (root == null || !root.activeSelf) return;
        float dt = Time.unscaledDeltaTime;
        frames++; elapsed += dt; worst = Mathf.Max(worst, dt);
        if (elapsed < 0.5f) return;
        label.text = string.Format("{0:0} FPS  {1:0.0} ms  max {2:0.0} ms", frames / elapsed, elapsed * 1000f / frames, worst * 1000f);
        frames = 0; elapsed = 0f; worst = 0f;
    }
}
