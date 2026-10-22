"""Patch individual objects in a Unity SerializedFile (format 22) without re-laying out the file.

Replaced objects are appended at the end of the data section and only their object-table
entry plus the header's file size change, so every other byte stays identical."""
import struct


def _header(data):
    version = struct.unpack_from(">I", data, 8)[0]
    if version < 22:
        raise ValueError("unsupported SerializedFile version %d" % version)
    meta_size, file_size, data_offset = struct.unpack_from(">IQQ", data, 20)
    return meta_size, file_size, data_offset


def patch_objects(data, objects):
    """objects: list of (path_id, type_id, old_rel_start, old_size, new_bytes)."""
    data = bytearray(data)
    meta_size, file_size, data_offset = _header(data)
    meta_end = 48 + meta_size
    for path_id, type_id, start, size, new in objects:
        entry = struct.pack("<qqIi", path_id, start, size, type_id)
        pos = data.find(entry, 48, meta_end)
        if pos < 0 or data.find(entry, pos + 1, meta_end) >= 0:
            raise ValueError("object table entry for %d not found uniquely" % path_id)
        while len(data) % 16:
            data.append(0)
        rel = len(data) - data_offset
        data += new
        struct.pack_into("<qqIi", data, pos, path_id, rel, len(new), type_id)
    while len(data) % 16:
        data.append(0)
    struct.pack_into(">Q", data, 24, len(data))
    return bytes(data)
