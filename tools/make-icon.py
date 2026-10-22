#!/usr/bin/env python3
"""Extract the game icon from the Windows executable and build a macOS .icns.

usage: make-icon.py <game.exe> <out.icns>
"""
import io
import os
import struct
import subprocess
import sys
import tempfile

import pefile

RT_ICON, RT_GROUP_ICON = 3, 14


def best_icon(exe):
    pe = pefile.PE(exe)
    icons, groups = {}, []
    for entry in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        for e in entry.directory.entries:
            for lang in e.directory.entries:
                data = pe.get_data(lang.data.struct.OffsetToData, lang.data.struct.Size)
                if entry.id == RT_ICON:
                    icons[e.id] = data
                elif entry.id == RT_GROUP_ICON:
                    groups.append(data)
    best, best_size = None, 0
    for g in groups:
        count = struct.unpack_from("<H", g, 4)[0]
        for i in range(count):
            w, h, _, _, _, bpp, _, icon_id = struct.unpack_from("<BBBBHHIH", g, 6 + i * 14)
            size = w or 256
            if size > best_size and icon_id in icons:
                best, best_size = icons[icon_id], size
    return best, best_size


def to_png(data, size, path):
    if data[:8] == b"\x89PNG\r\n\x1a\n":
        open(path, "wb").write(data)
        return
    # Classic DIB icon: wrap it in a one-image .ico and let sips convert it.
    ico = struct.pack("<HHH", 0, 1, 1) + struct.pack("<BBBBHHII", size % 256, size % 256, 0, 0, 1, 32, len(data), 22) + data
    tmp = path + ".ico"
    open(tmp, "wb").write(ico)
    subprocess.run(["sips", "-s", "format", "png", tmp, "--out", path], check=True, capture_output=True)


def main(exe, out):
    data, size = best_icon(exe)
    if not data:
        sys.exit("no icon found in " + exe)
    with tempfile.TemporaryDirectory() as tmp:
        src = os.path.join(tmp, "icon.png")
        to_png(data, size, src)
        iconset = os.path.join(tmp, "AppIcon.iconset")
        os.mkdir(iconset)
        for px in (16, 32, 128, 256, 512):
            for scale in (1, 2):
                dim = px * scale
                name = "icon_%dx%d%s.png" % (px, px, "@2x" if scale == 2 else "")
                subprocess.run(["sips", "-z", str(dim), str(dim), src, "--out", os.path.join(iconset, name)],
                               check=True, capture_output=True)
        subprocess.run(["iconutil", "-c", "icns", iconset, "-o", out], check=True)
    print("icon: %dx%d source -> %s" % (size, size, out))


if __name__ == "__main__":
    main(sys.argv[1], sys.argv[2])
