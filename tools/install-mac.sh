#!/bin/bash
# Move the built app into /Applications as "Risk of Rain 2.app", so it shows up in Launchpad.
#
#   tools/install-mac.sh
#
# Run it after every tools/build-mac.sh. Steam can stay open.
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
SRC="$REPO/build/Risk of Rain 2.app"
DEST="/Applications/Risk of Rain 2.app"

[ -d "$SRC" ] || { echo "No built app found. Run tools/build-mac.sh first."; exit 1; }
if pgrep -x RoR2 >/dev/null; then
    echo "Risk of Rain 2 is running. Quit the game first, then run this again."
    exit 1
fi
if [ -e "$DEST" ]; then
    # Only replace an app built by this project, never anything else with the same name
    if [ ! -f "$DEST/Contents/MacOS/RoR2" ]; then
        echo "$DEST already exists and was not built by this project. Not touching it."
        exit 1
    fi
    rm -rf "$DEST"
fi
mv "$SRC" "$DEST"
echo "Installed: $DEST"
echo "Open Risk of Rain 2 from Launchpad or the Applications folder. Steam must be running."
