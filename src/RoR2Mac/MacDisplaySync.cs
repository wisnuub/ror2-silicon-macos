// Make RoR2's VSync setting work on macOS (attached at startup together with MacFps).
//
// On macOS the game's CAMetalLayer has displaySyncEnabled on by default, so every frame waits for
// the display's refresh even with VSync off in the game settings: the game never runs above the
// screen's refresh rate (60 fps on a MacBook). This mirrors the game's setting onto the layer:
// VSync on keeps display sync, VSync off turns it off so the frame rate is no longer capped.
using System;
using System.Runtime.InteropServices;
using UnityEngine;

public class MacDisplaySync : MonoBehaviour
{
    const string ObjC = "/usr/lib/libobjc.A.dylib";
    [DllImport(ObjC)] static extern IntPtr objc_getClass(string name);
    [DllImport(ObjC)] static extern IntPtr sel_registerName(string name);
    [DllImport(ObjC, EntryPoint = "objc_msgSend")] static extern IntPtr Send(IntPtr obj, IntPtr sel);
    [DllImport(ObjC, EntryPoint = "objc_msgSend")] static extern IntPtr SendIndex(IntPtr obj, IntPtr sel, ulong index);
    [DllImport(ObjC, EntryPoint = "objc_msgSend")] static extern bool SendBoolSel(IntPtr obj, IntPtr sel, IntPtr arg);
    [DllImport(ObjC, EntryPoint = "objc_msgSend")] static extern void SendBool(IntPtr obj, IntPtr sel, bool value);
    [DllImport(ObjC, EntryPoint = "objc_msgSend")] static extern bool SendGetBool(IntPtr obj, IntPtr sel);

    float next;
    int lastVsync = -1;
    int lastWidth, lastHeight;
    bool failed;

    void Update()
    {
        if (failed || Time.unscaledTime < next) return;
        next = Time.unscaledTime + 2f;   // cheap check; Unity can recreate the layer on mode changes
        int vsync = QualitySettings.vSyncCount;
        if (vsync == lastVsync && Screen.width == lastWidth && Screen.height == lastHeight) return;
        try
        {
            int changed = Apply(vsync > 0);
            if (changed >= 0)
            {
                lastVsync = vsync; lastWidth = Screen.width; lastHeight = Screen.height;
                Debug.Log("[RoR2Mac] display sync " + (vsync > 0 ? "on" : "off") + " (VSync " + vsync + "), " + changed + " layer(s)");
            }
        }
        catch (Exception e) { failed = true; Debug.LogError("[RoR2Mac] display sync: " + e); }
    }

    static int Apply(bool sync)
    {
        IntPtr app = Send(objc_getClass("NSApplication"), sel_registerName("sharedApplication"));
        IntPtr windows = Send(app, sel_registerName("windows"));
        ulong count = (ulong)Send(windows, sel_registerName("count"));
        IntPtr objectAtIndex = sel_registerName("objectAtIndex:"), contentView = sel_registerName("contentView");
        IntPtr layerSel = sel_registerName("layer"), responds = sel_registerName("respondsToSelector:");
        IntPtr setSync = sel_registerName("setDisplaySyncEnabled:"), getSync = sel_registerName("displaySyncEnabled");
        int n = 0;
        for (ulong i = 0; i < count; i++)
        {
            IntPtr view = Send(SendIndex(windows, objectAtIndex, i), contentView);
            if (view == IntPtr.Zero) continue;
            IntPtr layer = Send(view, layerSel);
            if (layer == IntPtr.Zero || !SendBoolSel(layer, responds, setSync)) continue;
            if (SendGetBool(layer, getSync) != sync) SendBool(layer, setSync, sync);
            n++;
        }
        return n;
    }
}
