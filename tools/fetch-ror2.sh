#!/bin/bash
# Download your own copy of Risk of Rain 2 (Windows build) with Valve's SteamCMD.
#
#   tools/fetch-ror2.sh <your-steam-username>
#
# Run it in your own Terminal: SteamCMD asks for your Steam password and Steam Guard code itself.
# The account must own Risk of Rain 2. Nothing here sees or stores your credentials; SteamCMD
# keeps its own login session. Run it again later to update the game.
set -euo pipefail
REPO="$(cd "$(dirname "$0")/.." && pwd)"
USER_NAME="${1:?usage: tools/fetch-ror2.sh <steam-username>}"
GAME_DIR="${ROR2_GAME_DIR:-$REPO/game}"
SC_DIR="$REPO/.work/steamcmd"
APP=632360

if [ ! -x "$SC_DIR/steamcmd.sh" ]; then
    echo "Installing SteamCMD (from Valve) into $SC_DIR..."
    mkdir -p "$SC_DIR"
    curl -fsSL "https://steamcdn-a.akamaihd.net/client/installer/steamcmd_osx.tar.gz" | tar -xz -C "$SC_DIR"
fi

mkdir -p "$GAME_DIR"
# The Mac Steam client can't install Windows-only games, so SteamCMD is told to fetch the Windows build.
"$SC_DIR/steamcmd.sh" +@sSteamCmdForcePlatformType windows +force_install_dir "$GAME_DIR" \
    +login "$USER_NAME" +app_update "$APP" validate +quit

if [ -f "$GAME_DIR/Risk of Rain 2.exe" ]; then
    echo; echo "Game files are in $GAME_DIR. Next: tools/extract-unity-player.sh, then tools/build-mac.sh"
else
    echo; echo "Download did not complete (is Risk of Rain 2 in this account's library?)"; exit 1
fi
