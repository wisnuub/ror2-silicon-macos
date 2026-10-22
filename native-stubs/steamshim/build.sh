#!/bin/bash
# Build the Steamworks SDK 1.42 compatibility shim for Facepunch.Steamworks on arm64.
#
#   native-stubs/steamshim/build.sh <real libsteam_api.dylib> <output dir>
#
# Produces <output dir>/libsteam_api.dylib (the shim) and libsteam_api_real.dylib (current SDK).
# SDK 1.42 headers come from Facepunch.Steamworks' generator history (MIT repo, commit 0633bae).
set -euo pipefail
HERE="$(cd "$(dirname "$0")" && pwd)"
REPO="$(cd "$HERE/../.." && pwd)"
REAL="$1"; OUT="$2"
SDK="$REPO/lib/steamworks-sdk-142"
PYTHON="${PYTHON:-$REPO/.venv/bin/python}"

if [ ! -f "$SDK/steam_api_flat.h" ]; then
    echo "Fetching Steamworks SDK 1.42 headers..."
    TMP="$(mktemp -d)"
    git clone -q --filter=blob:none --no-checkout https://github.com/Facepunch/Facepunch.Steamworks.git "$TMP/fp"
    mkdir -p "$SDK"
    for f in $(git -C "$TMP/fp" ls-tree --name-only 0633bae Generator/steam_sdk/); do
        git -C "$TMP/fp" show "0633bae:$f" > "$SDK/$(basename "$f")"
    done
    rm -rf "$TMP"
fi

GEN="$(mktemp -d)"
"$PYTHON" "$HERE/gen_shim.py" "$SDK" "$GEN/steam_api_flat_142.cpp"
mkdir -p "$OUT"
cp "$REAL" "$OUT/libsteam_api_real.dylib"
clang++ -std=c++11 -O2 -arch arm64 -shared -fvisibility=hidden -w -I"$SDK" -DPOSIX -DOSX \
    -install_name @rpath/libsteam_api.dylib \
    "$HERE/steam_core.cpp" "$GEN/steam_api_flat_142.cpp" -o "$OUT/libsteam_api.dylib"
rm -rf "$GEN"
echo "Steam shim: $OUT/libsteam_api.dylib -> libsteam_api_real.dylib"
