#!/bin/bash
# Fetch Unity 2021.3.45f2's macOS Mono class libraries (mscorlib, System, ...).
# The game ships Unity's Windows build of these (they P/Invoke kernel32), so the
# Mac player needs the unityjit-macos set. They only ship inside the Unity Editor
# installer, so we stream the installer's payload and extract just that folder
# (nothing else is written to disk).
#
#   tools/fetch-unity-classlibs.sh        -> lib/unity/classlibs/
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
OUT="$REPO/lib/unity/classlibs"
URL="https://download.unity3d.com/download_unity/88f88f591b2e/MacEditorInstallerArm64/Unity-2021.3.45f2.pkg"
MEMBER="./Unity/Unity.app/Contents/MonoBleedingEdge/lib/mono/unityjit-macos"

if [ -f "$OUT/mscorlib.dll" ]; then echo "Already present: $OUT"; exit 0; fi

# Locate the Payload inside the xar archive from its table of contents.
read -r OFF LEN < <(curl -fsS -r 0-262143 "$URL" | python3 -I -c '
import sys, struct, zlib, re
d = sys.stdin.buffer.read()
_, hsize, _, toc_c, _, _ = struct.unpack(">4sHHQQI", d[:28])
toc = zlib.decompress(d[hsize:hsize + toc_c]).decode()
for m in re.finditer(r"<file id=\"\d+\">\s*<data>(.*?)</data>.*?<name>(.*?)</name>", toc, re.S):
    if m.group(2) == "Payload":
        off = int(re.search(r"<offset>(\d+)", m.group(1)).group(1))
        ln = int(re.search(r"<length>(\d+)", m.group(1)).group(1))
        print(hsize + toc_c + off, ln)
')

TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT
echo "Streaming Unity Editor payload ($((LEN / 1048576)) MB) and extracting class libraries..."
( cd "$TMP" && curl -fsS -r "$OFF-$((OFF + LEN - 1))" "$URL" | gunzip -c | cpio -idm "$MEMBER/*" 2>/dev/null )
mkdir -p "$OUT"
cp -R "$TMP/$MEMBER/." "$OUT/"
echo "Installed $(ls "$OUT"/*.dll | wc -l | tr -d ' ') class libraries to $OUT"
