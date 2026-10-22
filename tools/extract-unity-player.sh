#!/bin/bash
# Extract the macOS arm64 Mono standalone player from Unity's Mac Build Support pkg.
#
#   tools/extract-unity-player.sh [path-to-pkg]
#
# Output (lib/unity/player/):
#   UnityPlayer.app/       arm64 non-development player (executable, UnityPlayer.dylib, Mono)
#   MonoBleedingEdge/      Mono runtime config
#   Managed/               macOS builds of the UnityEngine.* engine modules
#   MainMenu.nib           player menu nib (required: it wires up PlayerAppDelegate)
#   Info.plist.template    Unity's player Info.plist template
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
PKG="${1:-$REPO/lib/unity/UnitySetup-Mac-Mono-Support.pkg}"
OUT="$REPO/lib/unity/player"
VARIATION=macos_arm64_player_nondevelopment_mono

if [ ! -f "$PKG" ]; then
    echo "Downloading Unity 2021.3.45f2 Mac Mono Build Support..."
    mkdir -p "$(dirname "$PKG")"
    curl -fL -o "$PKG" \
        "https://download.unity3d.com/download_unity/88f88f591b2e/MacEditorTargetInstaller/UnitySetup-Mac-Mono-Support-for-Editor-2021.3.45f2.pkg"
fi

WORK="$(mktemp -d)"
trap 'rm -rf "$WORK"' EXIT

echo "Extracting package..."
pkgutil --expand "$PKG" "$WORK/expanded"
mkdir -p "$WORK/content"
for payload in "$WORK"/expanded/*/Payload; do
    ( cd "$WORK/content" && { gunzip -c "$payload" 2>/dev/null | cpio -idm 2>/dev/null || cpio -idm < "$payload" 2>/dev/null; } )
done

C="$WORK/content"
ENTRY="$C/Source/Player/MacPlayer/MacPlayerEntryPoint"
[ -d "$C/Variations/$VARIATION/UnityPlayer.app" ] || { echo "Player variation $VARIATION not found"; exit 1; }

rm -rf "$OUT"
mkdir -p "$OUT"
cp -R "$C/Variations/$VARIATION/UnityPlayer.app" "$OUT/"
cp -R "$C/MonoBleedingEdge" "$OUT/"
mkdir -p "$OUT/Managed"
cp "$C/Variations/mono/Managed/"*.dll "$OUT/Managed/"
cp -R "$ENTRY/Resources/MainMenu.nib" "$OUT/"
cp "$ENTRY/Info.plist" "$OUT/Info.plist.template"

# The installer is only needed for this step
[ "$PKG" = "$REPO/lib/unity/UnitySetup-Mac-Mono-Support.pkg" ] && rm -f "$PKG"
echo "Mac standalone player extracted to: $OUT"
ls "$OUT"
