// Mac-local graphics settings for the macOS port (hooked into RoR2.dll by src/ILPatcher).
//
// RoR2 keeps its archived settings in config.cfg and syncs a copy through Steam Cloud, so a
// Windows PC and this Mac would overwrite each other's resolution, window mode and quality
// settings. Hardware-specific graphics/display settings are kept in a Mac-only file instead;
// everything else (audio, HUD, language, gameplay toggles, and controls, which live in the
// user profile) stays shared.
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using RoR2;
using Path = System.IO.Path;
using UnityEngine;
using Zio;

public static class MacSettings
{
    static readonly string[] LocalKeys = {
        "resolution", "window_mode", "resolution_scale", "vsync_count", "fps_max",
        "master_texture_limit", "anisotropic_filtering", "shadow_resolution", "shadow_cascades",
        "shadow_distance", "r_shadows", "r_softparticles", "r_lod_bias", "r_lod_max", "r_foliagewind",
        "pp_aa", "pp_ao", "pp_bloom", "pp_motionblur", "vfxbudget_particle_cost_bias",
    };

    static readonly Dictionary<string, string> cloudValues = new Dictionary<string, string>();
    static string cloudConfigPath;

    static string LocalPath
    {
        get { return Path.Combine(Application.persistentDataPath, "mac_graphics.cfg"); }
    }

    static string Get(string key)
    {
        var cv = RoR2.Console.instance != null ? RoR2.Console.instance.FindConVar(key) : null;
        return cv != null ? cv.GetString() : null;
    }

    static string Serialize(Func<string, string> value)
    {
        var sb = new StringBuilder();
        foreach (var k in LocalKeys)
        {
            var v = value(k);
            if (v != null) sb.Append(k).Append(' ').Append(v).Append(";\n");
        }
        return sb.ToString();
    }

    // Hooked at the end of Console.LoadUserConfigFile(path): the cloud config has just been applied.
    public static void AfterUserConfigLoaded(string path)
    {
        try
        {
            cloudConfigPath = path;
            cloudValues.Clear();
            foreach (var k in LocalKeys) { var v = Get(k); if (v != null) cloudValues[k] = v; }

            if (!File.Exists(LocalPath))
            {
                // First run on this Mac: start from the shared values, with Mac-appropriate display defaults.
                var defaults = new Dictionary<string, string>(cloudValues);
                defaults["window_mode"] = "Windowed";
                defaults["resolution"] = "1920x1080x60";
                if (SystemInfo.systemMemorySize <= 8 * 1024)
                    defaults["master_texture_limit"] = "1"; // full-size textures push 8 GB Macs into swap
                Directory.CreateDirectory(Path.GetDirectoryName(LocalPath));
                File.WriteAllText(LocalPath, Serialize(k => defaults.ContainsKey(k) ? defaults[k] : null));
                Debug.Log("[RoR2Mac] created " + LocalPath);
            }
            RoR2.Console.instance.SubmitCmd((NetworkUser)null, File.ReadAllText(LocalPath), false);
            Debug.Log("[RoR2Mac] applied Mac graphics settings from " + LocalPath);
        }
        catch (Exception e) { Debug.LogError("[RoR2Mac] AfterUserConfigLoaded: " + e); }
    }

    // Hooked at the end of Console.SaveArchiveConVars(): keep Mac graphics local, Windows ones in the cloud.
    public static void AfterSave()
    {
        try
        {
            File.WriteAllText(LocalPath, Serialize(Get));
            if (cloudConfigPath == null || RoR2Application.cloudStorage == null || cloudValues.Count == 0) return;
            var fs = RoR2Application.cloudStorage;
            var upath = (UPath)cloudConfigPath;
            if (!fs.FileExists(upath)) return;
            var lines = fs.ReadAllText(upath).Split('\n');
            for (int i = 0; i < lines.Length; i++)
            {
                var line = lines[i].Trim();
                int sp = line.IndexOf(' ');
                if (sp <= 0) continue;
                var key = line.Substring(0, sp);
                string original;
                if (cloudValues.TryGetValue(key, out original)) lines[i] = key + " " + original + ";";
            }
            fs.WriteAllText(upath, string.Join("\n", lines));
        }
        catch (Exception e) { Debug.LogError("[RoR2Mac] AfterSave: " + e); }
    }
}
