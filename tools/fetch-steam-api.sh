#!/bin/bash
# Download Valve's macOS libsteam_api.dylib (the redistributable shipped in a pinned, checksummed
# Steamworks.NET release) into lib/steamworks/.
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$REPO/lib/steamworks/libsteam_api.dylib"
[ -f "$OUT" ] && exit 0
echo "Downloading libsteam_api.dylib (Steamworks.NET 2025.164.1)..."
TMP="$(mktemp -d)"
curl -fsSL -o "$TMP/s.zip" \
    "https://github.com/rlabrecque/Steamworks.NET/releases/download/2025.164.1/Steamworks.NET-Standalone_2025.164.1.zip"
echo "9412348cc404563be5a43a28347cfeda3c679ee044a14d87a507ed2d796a537d  $TMP/s.zip" | shasum -a 256 -c - >/dev/null \
    || { echo "ERROR: Steamworks.NET download checksum mismatch"; exit 1; }
mkdir -p "$(dirname "$OUT")"
unzip -q -o -j "$TMP/s.zip" "OSX-Linux-x64/steam_api.bundle/Contents/MacOS/libsteam_api.dylib" -d "$(dirname "$OUT")"
rm -rf "$TMP"
