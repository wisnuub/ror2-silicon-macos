#!/bin/bash
# Build the DXBC->Metal translator (HLSLcc + driver) and the runtime MSL checker.
set -euo pipefail
cd "$(dirname "$0")"
HERE="$(pwd)"
SRC="$HERE/.hlslcc"
COMMIT=3ea1fcd

if [ ! -d "$SRC" ]; then
    git clone -q https://github.com/Unity-Technologies/HLSLcc.git "$SRC"
    git -C "$SRC" checkout -q "$COMMIT"
    git -C "$SRC" apply "$HERE/hlslcc-unity-player.patch"
fi
cmake -S "$SRC" -B "$SRC/build" -DHLSLCC_LIBRARY_SHARED=OFF -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_POLICY_VERSION_MINIMUM=3.5 >/dev/null
cmake --build "$SRC/build" -j8 >/dev/null
c++ -std=c++14 -O2 -I"$SRC/include" -I"$SRC/src/internal_includes" -I"$SRC/src/cbstring" -I"$SRC/src" \
    dxbc2msl.cpp "$SRC/build/libhlslcc.a" -o dxbc2msl
clang -fobjc-arc -O2 -Wno-deprecated-declarations mslcheck.m -framework Foundation -framework Metal -o mslcheck
echo "Built $HERE/dxbc2msl and $HERE/mslcheck"
