#!/usr/bin/env python3
"""Make the Addressables catalog usable on macOS.

The Windows build writes bundle locations as
  {UnityEngine.AddressableAssets.Addressables.RuntimePath}\\StandaloneWindows64\\x.bundle
Backslashes are not path separators on macOS, so every bundle load would fail.
"""
import json
import sys


def main(path):
    cat = json.load(open(path, encoding="utf-8"))
    ids = cat["m_InternalIds"]
    fixed = 0
    for i, s in enumerate(ids):
        if s.startswith("{UnityEngine.AddressableAssets.Addressables.RuntimePath}") and "\\" in s:
            ids[i] = s.replace("\\", "/")
            fixed += 1
    with open(path, "w", encoding="utf-8") as f:
        json.dump(cat, f, separators=(",", ":"))
    print("Catalog: fixed %d bundle paths" % fixed)


if __name__ == "__main__":
    if len(sys.argv) != 2:
        sys.exit("usage: patch-catalog.py <StreamingAssets/aa/catalog.json>")
    main(sys.argv[1])
