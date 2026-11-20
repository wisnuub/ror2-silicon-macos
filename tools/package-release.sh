#!/bin/bash
# Make the release download: a disk image with the app and an Applications shortcut, split into
# parts that fit GitHub's 2 GiB limit per release file, plus checksums and release notes.
#
#   tools/package-release.sh <version>      e.g. tools/package-release.sh 1.0.0
#
# It asks Steam (SteamCMD, anonymous) for the current game build and refuses to package older game
# files. The release notes name the game patch and link its SteamDB page. If the game wasn't
# downloaded with tools/fetch-ror2.sh, set ROR2_BUILD_ID to its Steam build ID, and STEAMCMD to
# steamcmd.sh if it isn't in .work/steamcmd/.
#
# Run it right after tools/build-mac.sh, before opening the built app (the game writes into its
# Config folder when it runs, which breaks the app's signature). It first checks that the build is
# a clean release build: ownership check in the Steam layer, sound engine included, and no test
# tools, mods or other changes. Output replaces build/release/.
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
VERSION="${1:?usage: tools/package-release.sh <version>}"
APP="$REPO/build/Risk of Rain 2.app"
OUT="$REPO/build/release"
NAME="Risk-of-Rain-2-Mac-$VERSION"
fail() { echo "NOT A RELEASE BUILD: $*"; exit 1; }

[ -d "$APP" ] || { echo "No built app. Run tools/build-mac.sh first."; exit 1; }
C="$APP/Contents"; P="$C/PlugIns"; M="$C/Resources/Data/Managed"

echo "== Checking the build"
# The ownership check is in the Steam layer, and only the release version of it
# (grep -a reads the binaries directly: "strings | grep -q" fails at random under pipefail)
has() { LC_ALL=C grep -a -q "$@"; }
has "this account owns Risk of Rain 2" "$P/libsteam_api.dylib" \
    || fail "the Steam layer has no ownership check"
has "STEAMSHIM_TEST_APPID" "$P/libsteam_api.dylib" \
    && fail "the Steam layer is a test build (SHIM_CFLAGS=-DSTEAMSHIM_TEST)"
# Only Valve's own libsteam_api next to the layer, and no Steam emulators or unlockers. The build
# re-signs every library ad hoc, so compare the code with the signatures taken off.
unsigned_hash() {
    local t; t="$(mktemp)"; cp "$1" "$t"; codesign --remove-signature "$t" 2>/dev/null || true
    shasum -a 256 < "$t"; rm -f "$t"
}
[ "$(unsigned_hash "$P/libsteam_api_real.dylib")" = "$(unsigned_hash "$REPO/lib/steamworks/libsteam_api.dylib")" ] \
    || fail "libsteam_api_real.dylib is not Valve's library from lib/steamworks"
for f in "$P/libsteam_api.dylib" "$P/libsteam_api_real.dylib"; do
    has -i cream "$f" && fail "$(basename "$f") contains unlocker code"
done
found="$(find "$APP" \( -iname '*cream*' -o -iname 'steam_settings' -o -iname 'steam_emu*' -o -iname '*goldberg*' \
    -o -iname 'BepInEx' -o -iname '*doorstop*' -o -iname 'run_bepinex.sh' -o -iname 'MacDiag.dll' \) -print)"
[ -z "$found" ] || fail "found files that don't belong in a release:"$'\n'"$found"
# Sound: the real Mac Wwise engine, not the silent stand-in
[ -f "$P/libAkSoundEngineCompat.dylib" ] && has 'wwise_v2023\.1\.' "$P/libAkSoundEngine.dylib" \
    || fail "no Mac Wwise 2023.1 sound engine (see README, Sound)"
codesign --verify --deep --strict "$APP" 2>/dev/null \
    || fail "the app's signature is broken (was it opened after building?). Run tools/build-mac.sh again"
echo "  ok: ownership check, Valve's Steam library, sound engine, no test tools or mods, signature valid"

# Which game patch this is. The Steam build ID of the game files comes from SteamCMD's app manifest
# (tools/fetch-ror2.sh) or ROR2_BUILD_ID. It must be Steam's current public build: Mac and Windows
# players need the same game version to play together.
echo "== Checking the game version"
GAME_DIR="${ROR2_GAME_DIR:-$REPO/game}"
BUILD_ID="${ROR2_BUILD_ID:-$(awk -F'"' '/"buildid"/ { print $4; exit }' "$GAME_DIR/steamapps/appmanifest_632360.acf" 2>/dev/null || true)}"
[ -n "$BUILD_ID" ] || { echo "Can't tell which Steam build the game files are. Download the game with"
    echo "tools/fetch-ror2.sh, or set ROR2_BUILD_ID to its build ID (https://steamdb.info/app/632360/patchnotes/)."; exit 1; }
STEAMCMD="${STEAMCMD:-$REPO/.work/steamcmd/steamcmd.sh}"
[ -x "$STEAMCMD" ] || { echo "SteamCMD not found at $STEAMCMD (run tools/fetch-ror2.sh once, or set STEAMCMD)"; exit 1; }
INFO="$("$STEAMCMD" +login anonymous +app_info_update 1 +app_info_print 632360 +quit 2>/dev/null || true)"
public_field() { awk -v k="\"$1\"" '/"branches"/ { b = 1 } b && /"public"/ { p = 1 } b && p && $1 == k { gsub(/"/, "", $2); print $2; exit }' <<< "$INFO"; }
PUBLIC_ID="$(public_field buildid)"; PUBLIC_TIME="$(public_field timeupdated)"
[ -n "$PUBLIC_ID" ] && [ -n "$PUBLIC_TIME" ] || { echo "ERROR: could not get Risk of Rain 2's current build from Steam"; exit 1; }
[ "$BUILD_ID" = "$PUBLIC_ID" ] || fail "the game files are Steam build $BUILD_ID, but the current game is build $PUBLIC_ID. Run tools/fetch-ror2.sh and tools/build-mac.sh again"
# The patch notes post for this build: the newest Steam news post tagged as patch notes, from before
# the build went live (or up to 3 days after it)
PY="$REPO/.venv/bin/python"; [ -x "$PY" ] || PY=python3
PATCH="$(curl -fsS 'https://api.steampowered.com/ISteamNews/GetNewsForApp/v2/?appid=632360&count=30&maxlength=1&format=json' 2>/dev/null \
    | "$PY" -I -c '
import json, sys
limit = int(sys.argv[1]) + 3 * 86400
posts = [n for n in json.load(sys.stdin)["appnews"]["newsitems"]
         if "patchnotes" in n.get("tags", []) and n["date"] <= limit]
if posts:
    n = max(posts, key=lambda n: n["date"])
    print(n["title"] + "\t" + n["url"].replace("steamstore-a.akamaihd.net", "store.steampowered.com"))
' "$PUBLIC_TIME" 2>/dev/null || true)"
PATCH_NAME="${PATCH%%$'\t'*}"; PATCH_URL="${PATCH#*$'\t'}"
[ -n "$PATCH_URL" ] && PATCH_URL="$(curl -fsS -o /dev/null -L -w '%{url_effective}' "$PATCH_URL" 2>/dev/null || echo "$PATCH_URL")"
BUILD_DATE="$(date -u -r "$PUBLIC_TIME" '+%-d %B %Y')"
STEAMDB="https://steamdb.info/patchnotes/$BUILD_ID/"
if [ -n "$PATCH_NAME" ]; then
    GAME_VERSION="[$PATCH_NAME]($PATCH_URL), Steam build [$BUILD_ID]($STEAMDB) from $BUILD_DATE"
else
    GAME_VERSION="Steam build [$BUILD_ID]($STEAMDB) from $BUILD_DATE"
fi
echo "  ok: Steam build $BUILD_ID ($BUILD_DATE) is the current game${PATCH_NAME:+: $PATCH_NAME}"

echo "== Making the disk image"
rm -rf "$OUT"; mkdir -p "$OUT"
WORK="$(mktemp -d)"
trap 'hdiutil detach -quiet "$WORK/mnt" 2>/dev/null || true; rm -rf "$WORK"' EXIT
mkdir "$WORK/stage" "$WORK/mnt"
cp -c -R "$APP" "$WORK/stage/" 2>/dev/null || cp -R "$APP" "$WORK/stage/"
ln -s /Applications "$WORK/stage/Applications"
hdiutil create -quiet -volname "Risk of Rain 2" -srcfolder "$WORK/stage" -fs HFS+ -format ULFO "$WORK/full.dmg"
rm -rf "$WORK/stage"

# GitHub takes at most 2 GiB per release file, so split the image into segments. Players don't join
# them: with every part in one folder, double-clicking the .dmg opens them as one disk image.
echo "== Splitting it into parts of at most 1900 MB"
hdiutil segment -quiet -segmentSize 1900m -o "$OUT/$NAME" "$WORK/full.dmg"
rm -f "$WORK/full.dmg"
PARTS=("$OUT/$NAME.dmg")
for f in "$OUT/$NAME".*.dmgpart; do [ -e "$f" ] && PARTS+=("$f"); done
for f in "${PARTS[@]}"; do
    [ "$(stat -f %z "$f")" -lt 2147483648 ] || { echo "ERROR: $(basename "$f") is 2 GiB or more"; exit 1; }
done

echo "== Checking that the parts open as one image"
hdiutil attach -quiet -readonly -nobrowse -mountpoint "$WORK/mnt" "$OUT/$NAME.dmg"
codesign --verify --deep --strict "$WORK/mnt/Risk of Rain 2.app" \
    || { echo "ERROR: the app in the image fails its signature check"; exit 1; }
hdiutil detach -quiet "$WORK/mnt"
(cd "$OUT" && shasum -a 256 "${PARTS[@]##*/}" > SHA256SUMS.txt)

# Release notes for the GitHub release page: how to download the parts, install, allow the app in
# Gatekeeper and play
FILES=""
for f in "${PARTS[@]}"; do
    FILES+="- \`$(basename "$f")\` ($(awk -v b="$(stat -f %z "$f")" 'BEGIN { printf "%.1f GB", b / 1e9 }'))"$'\n'
done
case ${#PARTS[@]} in 1) WHICH="the file below" ;; 2) WHICH="**both** files below" ;; *) WHICH="**all ${#PARTS[@]}** files below" ;; esac
export NAME FILES WHICH GAME_VERSION SUMS="$(cat "$OUT/SHA256SUMS.txt")"
# (plain text replacement: patch names can contain characters that are special to gsub, like &)
awk 'function fill(s, key,   i, v) { v = ENVIRON[key]; key = "@" key "@"
         while ((i = index(s, key)) > 0) s = substr(s, 1, i - 1) v substr(s, i + length(key)); return s }
     { $0 = fill($0, "NAME"); $0 = fill($0, "WHICH"); $0 = fill($0, "FILES"); $0 = fill($0, "GAME_VERSION")
       $0 = fill($0, "SUMS"); print }' > "$OUT/RELEASE-NOTES.md" <<'EOF'
Risk of Rain 2 for Apple Silicon Macs (M1 or newer, macOS 12 or newer). Sound is included, and
it only runs if your Steam account owns Risk of Rain 2.

> **Do not sell this release.** Don't charge for it, put it behind a paywall or bundle it with
> anything paid.

**Game version:** @GAME_VERSION@. This is the same version as the Windows game on Steam, so you
can play together.

## 1. Download

Download @WHICH@ into the same folder (your Downloads folder is fine):

@FILES@
The game is too big for one GitHub file, so it comes in parts. You don't need to join them: when
all the parts are in the same folder, macOS opens them as one disk image.

If macOS says **"missing segment"**, a part is missing or still downloading. Wait until every file
has finished downloading, then open the `.dmg` again. (Safari may try to open the `.dmg` as soon
as that one file finishes. That's fine, just open it again when everything is done.)

## 2. Install

1. Double-click `@NAME@.dmg`. macOS checks the disk image first, which can take a minute or two.
2. Drag **Risk of Rain 2** onto the **Applications** folder in the window. Don't play it straight
   from the disk image.
3. Eject the disk image. You can delete the downloaded files now.

## 3. Allow it in Gatekeeper (first time only)

The app isn't signed by Apple, so macOS blocks it the first time you open it. This is normal for
community projects. You only need to do this once.

**macOS 15 Sequoia or newer**

1. Open **Risk of Rain 2** from Applications. macOS says *“Risk of Rain 2” Not Opened*. Click
   **Done** (not Move to Trash).
2. Open **System Settings**, go to **Privacy & Security** and scroll down to **Security**.
3. Next to *“Risk of Rain 2” was blocked to protect your Mac*, click **Open Anyway** and enter
   your Mac password.
4. Click **Open Anyway** once more when macOS asks.

**macOS 12 to 14**

Control-click (or right-click) **Risk of Rain 2** in Applications, choose **Open**, then click
**Open** again.

**Or with Terminal (any macOS version)**

```
xattr -dr com.apple.quarantine "/Applications/Risk of Rain 2.app"
```

This also fixes *“Risk of Rain 2” is damaged and can't be opened*.

## 4. Play

1. Open Steam and log in with the account that owns Risk of Rain 2.
2. Open **Risk of Rain 2** from Launchpad or Applications. (Steam's Play button can't start it.)

If the game says *Steam is not running* or *Risk of Rain 2 is not in your Steam library*, see
[Steam ownership check](https://github.com/wisnuub/ror2-silicon-macos#steam-ownership-check-and-sharing).

Mac and Windows players need the same game version to play together. When Risk of Rain 2 gets an
update on Steam ([all game updates on SteamDB](https://steamdb.info/app/632360/patchnotes/)),
download the newest release here.

## Checksums (optional)

```
@SUMS@
```

The Risk of Rain team has said it's fine to share this project as long as nobody is charged for
it. Never sell it. Not made by or connected to Hopoo Games, Gearbox, Unity, Audiokinetic or Valve.
EOF

echo ""
echo "Release files in $OUT:"
for f in "${PARTS[@]}"; do echo "  $(basename "$f")  ($(du -h "$f" | cut -f1))"; done
echo "  SHA256SUMS.txt"
echo "  RELEASE-NOTES.md   (paste into the GitHub release, or: gh release create ... --notes-file)"
