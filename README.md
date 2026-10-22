# Risk of Rain 2 Native macOS Build for Apple Silicon

**ror2-silicon-macos**: play Risk of Rain 2 natively on Apple Silicon Macs (M1, M2, M3, M4).

**Tested on a Mac with an M1 chip and 8 GB of memory (macOS 26).**

This is an **unofficial** project. It turns **your own Steam copy** of Risk of Rain 2 into a
native macOS app. It does not use Wine, CrossOver or Rosetta. The game's code runs on Unity's
own Mac player, and the graphics are converted to Metal when you build the app.

This repository has **no game files**. The scripts download the game with your Steam account,
and your account must own the game.

> This project is not made by, or connected to, Hopoo Games, Gearbox, Unity, Audiokinetic or
> Valve. Risk of Rain 2 is a trademark of its owners.

## What works

| Part | Status |
|---|---|
| Singleplayer (menus, runs, stages, HUD, combat) | Works. About 57 fps in a 1080p window on an 8 GB M1 Mac |
| Graphics (Metal) | Works. All 1,643 shaders and 696 compute shaders are converted |
| Steam (login, profile, cloud saves) | Works |
| Sound | Works, after you download the free Mac sound engine yourself. See [Sound](#sound) |
| Multiplayer (Steam lobbies, Mac and Windows together) | Hosting and joining worked in tests. Please report problems |
| Tessellated water | Shows as flat water (Metal has no tessellation stage for it) |

## What you need

- A Mac with Apple Silicon (M1 or newer) and macOS 12 or newer
- Steam for Mac, installed and logged in
- A Steam account that owns Risk of Rain 2
- About 15 GB of free disk space
- [Homebrew](https://brew.sh)

## How to build and play

Open Terminal and run these steps one by one.

```bash
# 1. Install the tools
xcode-select --install
brew install cmake mono python@3.13

# 2. Get this project
git clone https://github.com/wisnuub/ror2-silicon-macos.git
cd ror2-silicon-macos

# 3. Download your copy of the game (the Windows version) with Valve's SteamCMD.
#    SteamCMD asks for your Steam password and Steam Guard code. Type them there.
tools/fetch-ror2.sh <your-steam-username>

# 4. Download Unity's Mac player
tools/extract-unity-player.sh

# 5. Optional: add the Mac sound engine (see "Sound" below)

# 6. Build the app. The first build takes about 40 minutes on an M1, because it downloads
#    Unity parts and converts every shader. Later builds take a few minutes.
tools/build-mac.sh

# 7. Move the app into your Applications folder
tools/install-mac.sh
```

Now open **Risk of Rain 2** from Launchpad or the Applications folder. Steam must be running.

When the game gets an update, run `tools/fetch-ror2.sh`, `tools/build-mac.sh` and
`tools/install-mac.sh` again.

**The Play button in Steam can't start this app.** Steam lists Risk of Rain 2 as a Windows game,
so on a Mac it won't play it from your library. Start the game from Launchpad or Applications
instead. Steam still knows you are playing Risk of Rain 2, so friends, multiplayer and cloud
saves work as normal.

**The first start is slow.** macOS checks a new app the first time it opens, and the game builds
its Metal shaders the first time it needs them. Later starts are faster.

**Do not share the app you build.** It contains your game files. Share this project instead, so
other people can build the app from their own copy.

## Sound

The game uses Audiokinetic Wwise 2023.1 for sound. The game's sound files work on a Mac, but the
Mac sound engine is not included. Only Audiokinetic gives it out. It is free, but you need an
Audiokinetic account. Without it, the game runs with no sound.

1. Install the [Wwise Launcher](https://www.audiokinetic.com/download/) and sign in (or make a
   free account).
2. Open the **Unity** tab and choose **Download Unity offline integration files**.
3. Pick the newest **2023.1.x** version (2023.1.19.8928 is tested) and tick **Mac**. Do not pick
   2024.1 or 2025.1. They cannot read the game's sound files.
4. Unpack `Unity.Mac.tar.xz` into the `lib/wwise/` folder of this project.
5. Run `tools/build-mac.sh` again.

## Multiplayer

Mac players and Windows players can play together. The game uses Steam lobbies and Steam's
network, and this app reports the same game version as the Windows game.

- Start the game before you join a friend. If the game is closed, Steam's "Join game" looks for
  a Mac version of Risk of Rain 2, and there is none.
- The Steam overlay (Shift+Tab) does not show up, because Steam did not start the game. Invite
  friends from the Steam friends list instead.

## Settings

The game saves its settings in Steam Cloud. A Windows PC and a Mac would keep changing each
other's screen and quality settings. To stop this, the Mac app keeps its graphics settings in its
own file:

`~/Library/Application Support/com.hopoo.riskofrain2/mac_graphics.cfg`

This covers resolution, window mode, resolution scale, vsync, frame cap, texture quality,
filtering, shadows, soft particles, level of detail, foliage wind, anti-aliasing, ambient
occlusion, bloom, motion blur and the particle budget. Everything else, including your key
bindings, still syncs with Steam Cloud.

On the first start, the game opens in a 1920x1080 window. On Macs with 8 GB of memory it also
uses half-size textures. This uses about half the graphics memory and keeps the Mac from
slowing down. You can change all of this in the game's settings. Delete the file to go back to
the defaults.

## Problems

- **macOS says the app is damaged or won't open it:** run
  `xattr -cr "build/Risk of Rain 2.app"`, then open it again.
- **Black screen at start:** make sure Steam is running and logged in before you open the game.
- **Log file:** `~/Library/Logs/Hopoo Games, LLC/Risk of Rain 2/Player.log`
- **Test build:** `RoR2_MAC_DIAG=1 tools/build-mac.sh` adds a tool that writes performance
  numbers to the log, saves screenshots and can run automatic tests.

## Legal

- This project only has build scripts, converters, small stand-in libraries and patch code. It
  has no Risk of Rain 2 files and no files from Unity, Audiokinetic or Valve.
- You must own Risk of Rain 2 on Steam. The game is downloaded with Valve's SteamCMD, using your
  account. Steam checks that you own the game when you play.
- Unity's Mac player, the Mono libraries, HLSLcc and Valve's Steam library are downloaded from
  their makers when you build. You download Audiokinetic's sound engine yourself. Their own
  licenses apply.
- Everything happens on your own Mac, with your own copy. Do not share the app you build.
- The code in this project uses the MIT license (see `LICENSE`).

---

# How it works

Risk of Rain 2 is a Unity 2021.3.45f2 game that uses **Mono**. That means most of the game's
code is portable and can run on a Mac. The work is in everything around that code:

1. **Unity Mac player.** The build uses Unity's official arm64 Mac player, with Unity's own
   `Info.plist` and `MainMenu.nib`. Without the nib, the player never starts.
2. **Mac libraries.** The game comes with Windows versions of the UnityEngine modules and the
   Mono class libraries. The build swaps in the Mac versions from the same Unity release. The
   class libraries only come inside the Unity Editor installer, so
   `tools/fetch-unity-classlibs.sh` downloads just that part of it.
3. **Shaders, from D3D11 to Metal** (`tools/shaderconv/`). The game only has compiled D3D11
   shaders (DXBC). For each one, the converter:
   - rebuilds the reflection data (`RDEF`) that Unity removes from game builds, using Unity's
     own parameter data;
   - translates it to Metal with a patched [HLSLcc](https://github.com/Unity-Technologies/HLSLcc).
     The patch keeps positions invariant, reads buffer strides from the shader code, and keeps
     constant buffers at their D3D11 offsets, because Unity fills its own buffers that way;
   - writes Unity's Metal shader data and marks the shader as Metal;
   - fixes a few shaders where Apple GPUs behave differently from D3D. For example, the health
     bar shader divides by zero. On D3D this gives a value that still shows the bar. On Metal the
     bar came out empty.

   The reflection data must list buffer variables in offset order. If it doesn't, HLSLcc reads
   the wrong values and models look "exploded". Compute shaders are converted the same way.
   Every shader is checked with Apple's Metal compiler (`mslcheck`).
4. **Patches to the game code** (`src/ILPatcher/`, using Mono.Cecil). Harmony can't change
   methods on arm64 Mono, so the build edits the game's files directly:
   - The Steam library check looks for the Windows `steam_api64.dll`, so it is told the Mac
     library is fine.
   - The Steam app ID is set inside the game, because the game deletes `steam_appid.txt`.
   - Without the Mac sound engine, sound files never finish loading, so the game does not wait
     for them.
   - The sound engine calls are matched to the Mac engine (see below).
   - Settings loading and saving is hooked to keep graphics settings on the Mac
     (`src/RoR2Mac/MacSettings.cs`).
5. **Steam layer** (`native-stubs/steamshim/`). The game's Steam code (Facepunch.Steamworks) was
   written for an old Steam SDK, version 1.42. Only new versions of `libsteam_api.dylib` exist
   for arm64. The layer gives the game the old 1.42 functions (696 of them, generated) and
   passes them to Valve's current library. That library comes from a fixed Steamworks.NET
   release.
6. **Stand-in libraries** for Windows-only parts (EOS, PlayFab Party, Discord, Rewired
   DirectInput, XAudio2, BCrypt, and a small kernel32/user32/ntdll library).
7. **Data fixes.** The graphics setting changes from D3D11 to Metal in `globalgamemanagers`, and
   the Addressables catalog paths change from `\` to `/`.
8. **App bundle.** The app uses the game's own icon (taken from the Windows exe) and supports
   macOS Game Mode.

## Sound engine details

The game's sound code was made for the Windows version of the Wwise 2023.1.4 Unity integration.
The build connects it to the Mac engine with Audiokinetic's own Mac binding file
(`AkSoundEnginePINVOKE_Mac.cs`):

- The binding tool numbers its functions differently on each platform, because Windows has extra
  wide-text versions. So each call is matched to the Mac function with the same parameter types,
  not by name.
- Windows Wwise uses UTF-16 text and Mac Wwise uses UTF-8, so text is converted to UTF-8.
- Calls that have no Mac version (Windows-only settings and audio device lists, plus a few
  functions the game never uses) go to a small stand-in library made by `tools/wwise-compat.py`.
- All the sound effects the game uses (EQ, limiter, reverb, delay, harmonizer, distortion and
  meter) are built into the Mac engine.

Test builds can record the sound engine's output to a WAV file (`-autopilot audio`).

## Performance notes

- In a run, speed depends on the GPU and the scene, not on shader loading. macOS saves compiled
  shaders for each app, so later starts are faster.
- Short pauses on the title screen and between stages come from scene loading, memory cleanup
  and Mono compiling code.
- Unity's graphics jobs made frame times worse on Metal, so they are off.

## Project files

```
tools/
  fetch-ror2.sh              download your copy of the game with SteamCMD
  extract-unity-player.sh    get Unity's Mac player
  build-mac.sh               build the app
  install-mac.sh             move the app into /Applications
  fetch-unity-classlibs.sh   get the Mac Mono libraries from the Unity Editor installer
  patch-graphics-api.py      change the graphics setting from D3D11 to Metal
  patch-catalog.py           fix Addressables paths for macOS
  make-icon.py               make the app icon from the game's Windows exe
  wwise-compat.py            list the Mac sound engine's functions, build the stand-in library
  shaderconv/                D3D11 to Metal shader converter (Python and HLSLcc)
src/
  ILPatcher/                 patches to the game's code (Mono.Cecil)
  RoR2Mac/                   code the patched game calls (Mac graphics settings)
  MacDiag/                   optional test tool and automatic test runs
native-stubs/
  steamshim/                 Steam SDK 1.42 layer generator
  *.c                        stand-ins for Windows-only libraries
```

Multiplayer was tested by making a Steam lobby, hosting a game, and connecting a second copy of
the game to it over Steam's network, through the login and version checks.
