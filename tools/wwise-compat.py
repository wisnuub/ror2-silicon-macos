#!/usr/bin/env python3
"""Helpers for running RoR2's Windows Wwise bindings against the macOS AkSoundEngine.

RoR2's AK.Wwise.Unity.API.dll is the Windows build of the Wwise 2023.1 Unity integration.
ILPatcher (--wwise-mac) rebinds its P/Invokes to the macOS engine using Audiokinetic's generated
Mac bindings; the few without a macOS counterpart (Windows-only settings and devices) are routed
to libAkSoundEngineCompat.dylib, built here.

usage: wwise-compat.py exports <macOS AkSoundEngine binary> <out.txt>
       wwise-compat.py compat  <unmatched.txt> <out dir>
"""
import os
import subprocess
import sys

mode = sys.argv[1]
if mode == "exports":
    binary, out = sys.argv[2:4]
    nm = subprocess.run(["nm", "-gU", "-arch", "arm64", binary], capture_output=True, text=True, check=True).stdout
    names = sorted({line.split()[-1].lstrip("_") for line in nm.splitlines() if line.strip()})
    with open(out, "w") as f:
        f.write("\n".join(names) + "\n")
    print("Wwise: macOS engine exports %d symbols" % len(names))
elif mode == "compat":
    listing, out = sys.argv[2:4]
    missing = [l.strip() for l in open(listing) if l.strip()]
    os.makedirs(out, exist_ok=True)
    # Every stub returns 0 in both the integer and the floating-point return register, so it is a
    # safe default for any signature (void, bool, int, pointer, float).
    asm = [".text"]
    for name in missing:
        asm += [".globl _%s" % name, ".p2align 2", "_%s:" % name, "  mov x0, #0", "  fmov d0, xzr", "  ret"]
    src = os.path.join(out, "akcompat.s")
    with open(src, "w") as f:
        f.write("\n".join(asm) + "\n")
    subprocess.run(["clang", "-arch", "arm64", "-shared", "-install_name", "@rpath/libAkSoundEngineCompat.dylib",
                    src, "-o", os.path.join(out, "libAkSoundEngineCompat.dylib")], check=True)
    print("Wwise: %d entry points without a macOS counterpart -> libAkSoundEngineCompat" % len(missing))
else:
    sys.exit(__doc__)
