#!/bin/bash
# Build all native plugin stubs for macOS arm64.
# These are no-op dylibs that prevent Mono from aborting on missing DLLImports.
# With crossplay off, the game uses Steam networking, so the Party/PlayFab/EOS paths are never hit.
set -euo pipefail
cd "$(dirname "$0")"
OUT="${1:-../build/plugins}"
mkdir -p "$OUT"

cc -shared -o "$OUT/libParty.dylib" party-stub.c -arch arm64
cc -shared -o "$OUT/libPlayFabMultiplayer.dylib" playfab-multiplayer-stub.c -arch arm64
cc -shared -o "$OUT/libRewired_DirectInput.dylib" rewired-stub.c -arch arm64
cp "$OUT/libRewired_DirectInput.dylib" "$OUT/libRewired_WindowsGamingInput.dylib"
cc -shared -o "$OUT/libAkSoundEngine.dylib" aksoundengine-stub.c -arch arm64
cc -shared -o "$OUT/libEOSSDK-Mac-Shipping.dylib" eossdk-stub.c -arch arm64
cc -shared -o "$OUT/libdiscord_game_sdk.dylib" discord-stub.c -arch arm64
cc -shared -o "$OUT/libxaudio2_stub.dylib" xaudio2-stub.c -arch arm64
cc -shared -o "$OUT/libBCrypt.dylib" bcrypt-stub.c -arch arm64
cc -shared -o "$OUT/libwin32compat.dylib" win32-stub.c -arch arm64

echo "Built stubs in $OUT:"
ls -lh "$OUT"/*.dylib
