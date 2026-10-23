#!/bin/bash
# Build Risk of Rain 2 for native macOS (Apple Silicon) from your own copy of the game.
#
# Prerequisites:
#   - Game files: tools/fetch-ror2.sh <steam-username>   (downloads into game/; or set ROR2_GAME_DIR)
#   - Unity player: tools/extract-unity-player.sh        (into lib/unity/)
#   - Optional audio: macOS Wwise 2023.1.x Unity integration in lib/wwise/ (see README)
#
# The .app it produces contains your game files: don't share it.
set -euo pipefail

REPO="$(cd "$(dirname "$0")/.." && pwd)"
GAME_SRC="${ROR2_GAME_DIR:-$REPO/game}"
PLAYER="$REPO/lib/unity/player"
BUILD="$REPO/build"
APP="$BUILD/Risk of Rain 2.app"

if [ ! -f "$GAME_SRC/Risk of Rain 2.exe" ]; then
    echo "ERROR: Game files not found at $GAME_SRC"
    echo "Run: tools/fetch-ror2.sh <steam-username>"
    exit 1
fi

TEMPLATE="$PLAYER/UnityPlayer.app"
if [ ! -d "$TEMPLATE" ]; then
    echo "ERROR: Unity Mac player not found at $TEMPLATE"
    echo "Run: tools/extract-unity-player.sh"
    exit 1
fi

# Python tooling (UnityPy etc.) lives in a project virtualenv
PYTHON="$REPO/.venv/bin/python"
if [ ! -x "$PYTHON" ]; then
    PYBASE="$(command -v python3.14 || command -v python3.13 || command -v python3.12 || command -v python3)"
    "$PYBASE" -m venv "$REPO/.venv"
    "$PYTHON" -m pip install -q -r "$REPO/tools/requirements.txt"
fi

echo "=== Building Risk of Rain 2 for macOS (arm64) ==="

rm -rf "$APP"
mkdir -p "$BUILD"

# Step 1: Copy the Unity player template
echo "Copying Unity player template..."
cp -R "$TEMPLATE" "$APP"

CONTENTS="$APP/Contents"

# Rename the executable
mv "$CONTENTS/MacOS/UnityPlayer" "$CONTENTS/MacOS/RoR2"

# Step 2: Set up Data directory with game content
DATA_DIR="$CONTENTS/Resources/Data"
mkdir -p "$DATA_DIR/Managed"

echo "Copying managed assemblies..."
cp "$GAME_SRC/Risk of Rain 2_Data/Managed/"*.dll "$DATA_DIR/Managed/"

# The game ships Windows builds of the UnityEngine modules and the Mono class
# libraries (mscorlib & co. P/Invoke kernel32). Swap in the macOS builds of the
# same Unity version for every assembly the game has.
swap_assemblies() {
    local from="$1" label="$2" n=0
    for f in "$DATA_DIR/Managed/"*.dll; do
        local name; name="$(basename "$f")"
        local src; src="$(find "$from" -name "$name" -print -quit)"
        if [ -n "$src" ]; then cp "$src" "$f"; n=$((n + 1)); fi
    done
    echo "  replaced $n $label"
}
swap_assemblies "$PLAYER/Managed" "engine modules with macOS builds"
CLASSLIBS="$REPO/lib/unity/classlibs"
[ -f "$CLASSLIBS/mscorlib.dll" ] || "$REPO/tools/fetch-unity-classlibs.sh"
swap_assemblies "$CLASSLIBS" "class libraries with unityjit-macos builds"

echo "Copying game assets..."
for item in Resources StreamingAssets Licenses \
    globalgamemanagers globalgamemanagers.assets resources.assets resources.assets.resS \
    boot.config app.info ScriptingAssemblies.json RuntimeInitializeOnLoads.json; do
    src="$GAME_SRC/Risk of Rain 2_Data/$item"
    if [ -e "$src" ]; then
        cp -R "$src" "$DATA_DIR/"
    fi
done
# RoR2 reads and writes Config/ under Application.dataPath, which is Contents/ on macOS
cp -R "$GAME_SRC/Risk of Rain 2_Data/Config" "$CONTENTS/Config"

# Copy level and shared assets files
for f in "$GAME_SRC/Risk of Rain 2_Data/"level* "$GAME_SRC/Risk of Rain 2_Data/"sharedassets*; do
    [ -e "$f" ] && cp -R "$f" "$DATA_DIR/"
done

# Mono.Cecil for the IL patcher (NuGet, MIT)
CECIL="$REPO/lib/cecil/Mono.Cecil.dll"
if [ ! -f "$CECIL" ]; then
    echo "Downloading Mono.Cecil..."
    TMP="$(mktemp -d)"
    curl -fsSL -o "$TMP/cecil.nupkg" "https://www.nuget.org/api/v2/package/Mono.Cecil/0.11.6"
    mkdir -p "$(dirname "$CECIL")"
    unzip -q -o -j "$TMP/cecil.nupkg" "lib/net40/Mono.Cecil.dll" -d "$(dirname "$CECIL")"
    rm -rf "$TMP"
fi

# Step 2a: Build-time IL patches (Harmony can't detour on arm64 Mono, so patch RoR2.dll directly)
command -v mcs >/dev/null || { echo "ERROR: Mono is required for the IL patcher (brew install mono)"; exit 1; }
ILP="$REPO/src/ILPatcher"
mcs -out:"$ILP/ILPatcher.exe" -r:"$CECIL" "$ILP/ILPatcher.cs"
cp "$CECIL" "$ILP/"
DIAG_FLAG=""
if [ "${RoR2_MAC_DIAG:-0}" = "1" ]; then
    M="$DATA_DIR/Managed"
    mcs -target:library -out:"$M/MacDiag.dll" -nostdlib -r:"$M/mscorlib.dll" -r:"$M/System.dll" \
        -r:"$M/System.Core.dll" -r:"$M/netstandard.dll" -r:"$M/UnityEngine.dll" -r:"$M/UnityEngine.CoreModule.dll" \
        -r:"$M/UnityEngine.ImageConversionModule.dll" -r:"$M/UnityEngine.ScreenCaptureModule.dll" \
        -r:"$M/UnityEngine.InputLegacyModule.dll" -r:"$M/UnityEngine.UI.dll" -r:"$M/UnityEngine.UIModule.dll" "$REPO/src/MacDiag/MacDiag.cs"
    DIAG_FLAG="--diag"
fi
M="$DATA_DIR/Managed"
mcs -target:library -out:"$M/RoR2Mac.dll" -nostdlib -r:"$M/mscorlib.dll" -r:"$M/System.dll" -r:"$M/System.Core.dll" \
    -r:"$M/netstandard.dll" -r:"$M/UnityEngine.dll" -r:"$M/UnityEngine.CoreModule.dll" -r:"$M/UnityEngine.InputLegacyModule.dll" -r:"$M/UnityEngine.TextRenderingModule.dll" -r:"$M/UnityEngine.UI.dll" -r:"$M/UnityEngine.UIModule.dll" -r:"$M/RoR2.dll" -r:"$M/Zio.dll" -r:"$M/com.unity.multiplayer-hlapi.Runtime.dll" \
    "$REPO/src/RoR2Mac/MacSettings.cs" "$REPO/src/RoR2Mac/MacFps.cs" "$REPO/src/RoR2Mac/MacDisplaySync.cs"
# Audio: real Wwise when the macOS Wwise 2023.1.x Unity integration is present (see README),
# otherwise a silent stub.
WWISE_DIR="${RoR2_WWISE_DIR:-$REPO/lib/wwise}"
AK_BIN=""
if [ -d "$WWISE_DIR" ]; then
    AK_BIN="$(find "$WWISE_DIR" -type f -path '*Mac*Release*AkSoundEngine.bundle/Contents/MacOS/AkSoundEngine' | head -1)"
fi
WWISE_FLAG=""
WWISE_WORK="$REPO/.work/wwise"
if [ -n "$AK_BIN" ]; then
    echo "Wwise: using $AK_BIN"
    lipo -archs "$AK_BIN" | grep -q arm64 || { echo "ERROR: $AK_BIN has no arm64 slice"; exit 1; }
    AK_VERSION="$(strings -a "$AK_BIN" | grep -o -m1 'wwise_v20[0-9][0-9]\.[0-9]*\.[0-9]*' || true)"
    case "$AK_VERSION" in
        wwise_v2023.1.*) echo "Wwise: engine ${AK_VERSION#wwise_v}" ;;
        *) echo "WARNING: $AK_BIN is '${AK_VERSION:-unknown}', not Wwise 2023.1.x (the game's banks are 2023.1 format)" ;;
    esac
    # Audiokinetic's generated Mac bindings tell ILPatcher how each P/Invoke is declared on macOS
    AK_MAC_PINVOKE="$(find "$WWISE_DIR" -name 'AkSoundEnginePINVOKE_Mac.cs' | head -1)"
    [ -n "$AK_MAC_PINVOKE" ] || { echo "ERROR: AkSoundEnginePINVOKE_Mac.cs not found in $WWISE_DIR"; exit 1; }
    mkdir -p "$WWISE_WORK"
    "$PYTHON" "$REPO/tools/wwise-compat.py" exports "$AK_BIN" "$WWISE_WORK/exports.txt"
    WWISE_FLAG="--wwise-mac $AK_MAC_PINVOKE --wwise-exports $WWISE_WORK/exports.txt --wwise-unmatched $WWISE_WORK/unmatched.txt"
else
    echo "Wwise: macOS integration not found in $WWISE_DIR -- building without audio"
fi
mono "$ILP/ILPatcher.exe" "$DATA_DIR/Managed" $DIAG_FLAG $WWISE_FLAG
[ -n "$AK_BIN" ] && "$PYTHON" "$REPO/tools/wwise-compat.py" compat "$WWISE_WORK/unmatched.txt" "$WWISE_WORK"

# Step 2b: Patch graphics API from D3D11 to Metal
echo "Patching graphics API..."
"$PYTHON" "$REPO/tools/patch-graphics-api.py" "$DATA_DIR/globalgamemanagers"

# Step 2c: Addressables catalog uses Windows path separators
"$PYTHON" "$REPO/tools/patch-catalog.py" "$DATA_DIR/StreamingAssets/aa/catalog.json"

# Step 2d: Translate every shader from D3D11 bytecode to Metal
SHADERCONV="$REPO/tools/shaderconv"
[ -x "$SHADERCONV/dxbc2msl" ] || "$SHADERCONV/build.sh"
"$PYTHON" "$SHADERCONV/convert.py" --work "$REPO/.work/shaders" --data "$DATA_DIR"

# Step 3: Set up native plugins
# Unity on macOS loads native plugins from Contents/PlugIns
PLUGIN_DIR="$CONTENTS/PlugIns"
mkdir -p "$PLUGIN_DIR"

echo "Building native stubs..."
"$REPO/native-stubs/build-stubs.sh" "$PLUGIN_DIR"
if [ -n "$AK_BIN" ]; then
    # Replace the silent stub with the real engine (a loadable bundle binary; dlopen takes it as is)
    lipo -thin arm64 "$AK_BIN" -output "$PLUGIN_DIR/libAkSoundEngine.dylib" 2>/dev/null || cp "$AK_BIN" "$PLUGIN_DIR/libAkSoundEngine.dylib"
    cp "$REPO/.work/wwise/libAkSoundEngineCompat.dylib" "$PLUGIN_DIR/"
    # Effect plug-ins shipped as separate bundles (Plugins/Mac/DSP, e.g. libAkMeter.bundle)
    find "$WWISE_DIR" -path '*API/Runtime/Plugins/Mac/DSP/*' \( -name '*.bundle' -o -name '*.dylib' \) -prune \
        -exec cp -R {} "$PLUGIN_DIR/" \;
fi

# Step 4: Steamworks. The game's Facepunch.Steamworks speaks the SDK 1.42 flat API; the shim wraps a
# current macOS libsteam_api.dylib (Valve's redistributable, as shipped in Steamworks.NET releases).
STEAM_DYLIB="${RoR2_STEAM_API:-$REPO/lib/steamworks/libsteam_api.dylib}"
if [ ! -f "$STEAM_DYLIB" ]; then
    echo "Downloading libsteam_api.dylib (Steamworks.NET 2025.164.1)..."
    TMP="$(mktemp -d)"
    curl -fsSL -o "$TMP/s.zip" \
        "https://github.com/rlabrecque/Steamworks.NET/releases/download/2025.164.1/Steamworks.NET-Standalone_2025.164.1.zip"
    echo "9412348cc404563be5a43a28347cfeda3c679ee044a14d87a507ed2d796a537d  $TMP/s.zip" | shasum -a 256 -c - >/dev/null \
        || { echo "ERROR: Steamworks.NET download checksum mismatch"; exit 1; }
    mkdir -p "$(dirname "$STEAM_DYLIB")"
    unzip -q -o -j "$TMP/s.zip" "OSX-Linux-x64/steam_api.bundle/Contents/MacOS/libsteam_api.dylib" -d "$(dirname "$STEAM_DYLIB")"
    rm -rf "$TMP"
fi
echo "Building Steamworks 1.42 shim..."
PYTHON="$PYTHON" "$REPO/native-stubs/steamshim/build.sh" "$STEAM_DYLIB" "$PLUGIN_DIR"

# Step 5: Set up Mono runtime and DLL mapping
# Copy MonoBleedingEdge etc from the player support (has the mono config)
if [ -d "$PLAYER/MonoBleedingEdge" ]; then
    cp -R "$PLAYER/MonoBleedingEdge" "$CONTENTS/"
fi

MONO_CONFIG="$CONTENTS/MonoBleedingEdge/etc/mono/config"
if [ -f "$MONO_CONFIG" ]; then
    # Add game-specific DLL mappings before closing tag
    "$PYTHON" -c "
import sys
config = open(sys.argv[1]).read()
mappings = '''
\t<!-- RoR2 macOS native plugin mappings -->
\t<dllmap dll=\"PartyWin32\" target=\"libParty.dylib\"/>
\t<dllmap dll=\"PlayFabMultiplayerWin\" target=\"libPlayFabMultiplayer.dylib\"/>
\t<dllmap dll=\"PlayFabMultiplayerGDK\" target=\"libPlayFabMultiplayer.dylib\"/>
\t<dllmap dll=\"PartyXboxLiveWin32\" target=\"libParty.dylib\"/>
\t<dllmap dll=\"Rewired_DirectInput\" target=\"libRewired_DirectInput.dylib\"/>
\t<dllmap dll=\"Rewired_WindowsGamingInput\" target=\"libRewired_WindowsGamingInput.dylib\"/>
\t<dllmap dll=\"EOSSDK-Win64-Shipping\" target=\"libEOSSDK-Mac-Shipping.dylib\"/>
\t<dllmap dll=\"EOSSDK-Win32-Shipping\" target=\"libEOSSDK-Mac-Shipping.dylib\"/>
\t<dllmap dll=\"discord_game_sdk\" target=\"libdiscord_game_sdk.dylib\"/>
\t<dllmap dll=\"AkSoundEngine\" target=\"libAkSoundEngine.dylib\"/>
\t<dllmap dll=\"AkSoundEngineCompat\" target=\"libAkSoundEngineCompat.dylib\"/>
\t<dllmap dll=\"xaudio2_9redist\" target=\"libxaudio2_stub.dylib\"/>
\t<dllmap dll=\"steam_api64\" target=\"libsteam_api.dylib\"/>
\t<dllmap dll=\"BCrypt\" target=\"libBCrypt.dylib\"/>
\t<dllmap dll=\"kernel32\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"kernel32.dll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"user32\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"user32.dll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"ntdll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"ntdll.dll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"xinput1_1.dll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"xinput1_2.dll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"xinput1_3.dll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"xinput1_4.dll\" target=\"libwin32compat.dylib\"/>
\t<dllmap dll=\"xinput9_1_0.dll\" target=\"libwin32compat.dylib\"/>
'''
config = config.replace('</configuration>', mappings + '</configuration>')
open(sys.argv[1], 'w').write(config)
" "$MONO_CONFIG"
    echo "DLL mappings added to Mono config"
fi

# Step 6: Info.plist from Unity's player template, plus MainMenu.nib.
# NSPrincipalClass=PlayerApplication and the nib are what create Unity's app
# delegate; without them the player idles in the event loop and never starts.
cp -R "$PLAYER/MainMenu.nib" "$CONTENTS/Resources/"
sed -e 's/UnityPlayerExec/RoR2/' \
    -e 's/UNITY_BUNDLE_IDENTIFIER/com.hopoo.riskofrain2/' \
    -e 's/UNITY_APPLICATION_CATEGORY/public.app-category.games/' \
    -e 's/UNITY_PLAYER_BUNDLE_NAME/Risk of Rain 2/' \
    -e 's/UNITY_PLAYER_BUNDLE_VERSION/1.0/' \
    -e 's/UNITY_PLAYER_BUILD_NUMBER/1/' \
    -e 's/DEVELOPMENT_VERSION_WITH_BUILD_NUMBER/2021.3.45f2/' \
    -e 's/ DEVELOPMENT_COPYRIGHT//' \
    -e 's/DEVELOPMENT_BUILD_NUMBER/88f88f591b2e/' \
    -e 's/10\.13\.0/12.0/' \
    "$PLAYER/Info.plist.template" > "$CONTENTS/Info.plist"
# App icon: the game's own icon, extracted from the Windows executable
"$PYTHON" "$REPO/tools/make-icon.py" "$GAME_SRC/Risk of Rain 2.exe" "$CONTENTS/Resources/AppIcon.icns"
/usr/libexec/PlistBuddy -c "Set :CFBundleIconFile AppIcon" "$CONTENTS/Info.plist"
/usr/libexec/PlistBuddy -c "Add :NSHighResolutionCapable bool true" "$CONTENTS/Info.plist"
# Let macOS Game Mode prioritise the game (CPU scheduling on performance cores, GPU priority)
/usr/libexec/PlistBuddy -c "Add :LSSupportsGameMode bool true" "$CONTENTS/Info.plist"
/usr/libexec/PlistBuddy -c "Add :NSMicrophoneUsageDescription string Voice chat" "$CONTENTS/Info.plist"

# Step 7: steam_appid.txt next to the executable
cp "$GAME_SRC/steam_appid.txt" "$CONTENTS/MacOS/"

# Step 8: Ad-hoc sign
echo "Signing bundle..."
codesign --force --deep -s - "$APP" 2>/dev/null || true

echo ""
echo "=== Build complete ==="
echo "App bundle: $APP"
du -sh "$APP"
echo ""
echo "To play: start Steam and log in, then open '$APP'"
[ -n "$AK_BIN" ] || echo "Audio: off (no macOS Wwise engine in lib/wwise; see README)"
echo "This app contains your game files -- don't share it."
