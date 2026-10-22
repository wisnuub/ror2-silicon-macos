#!/usr/bin/env python3
"""Patch globalgamemanagers to use Metal instead of D3D11.

Unity stores the graphics API list in BuildSettings. Windows builds have
D3D11 (value 2); macOS needs Metal (value 16 = 0x10).

This does a targeted binary patch: it finds the m_GraphicsAPIs array in
BuildSettings (located right after the "2021.3.45f2" version string) and
changes the first API value. The file size stays identical.
"""
import struct, sys

def patch(path):
    data = bytearray(open(path, 'rb').read())
    version = b'2021.3.45f2'
    # BuildSettings.m_Version is a length-prefixed, 4-byte aligned string directly
    # followed by m_GraphicsAPIs (the file header holds a NUL-terminated copy too).
    needle = struct.pack('<I', len(version)) + version
    pos = data.find(needle)
    if pos < 0:
        print("ERROR: BuildSettings version string not found", file=sys.stderr)
        return False
    api_offset = pos + len(needle)
    api_offset = (api_offset + 3) & ~3

    count = struct.unpack_from('<I', data, api_offset)[0]
    value = struct.unpack_from('<I', data, api_offset + 4)[0]

    if count != 1:
        print(f"ERROR: expected 1 graphics API, found {count}", file=sys.stderr)
        return False

    API_NAMES = {2: 'D3D11', 11: 'Vulkan', 16: 'Metal', 17: 'OpenGLCore'}
    old_name = API_NAMES.get(value, f'unknown({value})')

    if value == 16:
        print(f"Already set to Metal (16)")
        return True

    data[api_offset + 4] = 16
    open(path, 'wb').write(data)
    print(f"Patched: {old_name} ({value}) -> Metal (16)")
    return True

if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <globalgamemanagers>")
        sys.exit(1)
    sys.exit(0 if patch(sys.argv[1]) else 1)
