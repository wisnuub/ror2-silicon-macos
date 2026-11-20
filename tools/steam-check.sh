#!/bin/bash
# Stop unless Steam is running, a user is logged in, and that account owns Risk of Rain 2.
# Uses Valve's Steamworks API against the Steam app on this Mac (native-stubs/steamcheck).
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
"$REPO/tools/fetch-steam-api.sh"
CHECK="$REPO/.work/steamcheck/steamcheck"
if [ ! -x "$CHECK" ] || [ "$REPO/native-stubs/steamcheck/steamcheck.c" -nt "$CHECK" ]; then
    mkdir -p "$(dirname "$CHECK")"
    clang -O2 -arch arm64 -o "$CHECK" "$REPO/native-stubs/steamcheck/steamcheck.c"
fi
"$CHECK" "$REPO/lib/steamworks/libsteam_api.dylib" 2>/dev/null
