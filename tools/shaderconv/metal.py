"""Build Unity Metal subprogram entries from HLSLcc output."""
import re
import struct

import unityblob as U

# Program code header Unity 2021.3 writes before the MSL text (identical for every VS/FS).
CODE_HEADER = struct.pack("<12I", 0xF00DCAFE, 0x30, 5, 0x3C, 0, 0, 0, 0, 0, 5, 0xFFFFFFFF, 0) + b"xlatMtlMain\0"

METAL_VS, METAL_FS = 23, 24
VERTEX_ATTR0 = 13  # Unity vertex component id for Metal attribute(0)

_SCALAR = {"float": (4, 0), "half": (2, 3), "int": (4, 1), "uint": (4, 5), "bool": (1, 2),
           "short": (2, 1), "ushort": (2, 5)}
_MEMBER = re.compile(r"^\s*(packed_)?([a-z]+?)(\d)?(?:x(\d))?\s+(\w+)\s*(?:\[\s*(\d+)\s*\])?\s*;")
_STRUCT_MEMBER = re.compile(r"^\s*(\w+_Type)\s+(\w+)\s*(?:\[\s*(\w+)\s*\])?\s*;")
_MTX = re.compile(r"^hlslcc_mtx(\d)x(\d)(.+)$")


def struct_layout(msl, struct_name, structs_out=None):
    """Return (size, params) for `struct <struct_name> {...}` using Metal layout rules.

    Nested struct members are appended to structs_out as Unity struct params."""
    m = re.search(r"struct\s+" + re.escape(struct_name) + r"\s*\{(.*?)\};", msl, re.S)
    if not m:
        raise ValueError("struct %s not found" % struct_name)
    off, max_align, params = 0, 1, []
    for line in m.group(1).splitlines():
        if not line.strip():
            continue
        sm = _STRUCT_MEMBER.match(line)
        if sm:
            if structs_out is None:
                raise ValueError("nested struct in %s" % struct_name)
            ssize_, sparams = struct_layout(msl, sm.group(1))
            salign = 16
            count = int(sm.group(3)) if sm.group(3) and sm.group(3).isdigit() else 2
            off = (off + salign - 1) // salign * salign
            structs_out.append({"name": sm.group(2), "index": off, "arraySize": count,
                                "structSize": ssize_, "params": sparams})
            off += ssize_ * count
            max_align = max(max_align, salign)
            continue
        mm = _MEMBER.match(line)
        if not mm:
            raise ValueError("unparsed member %r in %s" % (line.strip(), struct_name))
        packed, base, n1, n2, name, arr = mm.groups()
        ssize, ptype = _SCALAR[base]
        if n2:  # floatCxR matrix: C columns of R-vectors
            cols, rows = int(n1), int(n2)
            vec = ssize * (4 if rows == 3 else rows)
            size, align = vec * cols, vec
        else:
            n = int(n1) if n1 else 1
            if packed:
                size, align = ssize * n, ssize
            else:
                size = ssize * (4 if n == 3 else n)
                align = size
        count = int(arr) if arr else 0
        off = (off + align - 1) // align * align
        p = {"type": ptype, "index": off, "arraySize": 0}
        mt = _MTX.match(name)
        if mt:  # HLSLcc's translated matrix: float4 hlslcc_mtxRxCname[R*k]
            r_, c_ = int(mt.group(1)), int(mt.group(2))
            per = r_
            p.update(name=mt.group(3), rows=r_, cols=c_, isMatrix=1,
                     arraySize=(count // per) if count > per else 0)
        elif n2:
            p.update(name=name, rows=int(n2), cols=int(n1), isMatrix=1, arraySize=count)
        else:
            p.update(name=name, rows=1, cols=int(n1) if n1 else 1, isMatrix=0, arraySize=count)
        if not name.startswith("hlslcc_pad"):  # layout filler emitted by our HLSLcc patch
            params.append(p)
        off += size * max(count, 1)
        max_align = max(max_align, align)
    return (off + max_align - 1) // max_align * max_align, params


def param_entry(msl, refl, d3d_params):
    """Build the Metal parameter entry describing what the MSL actually binds."""
    tex_dim = {b["name"]: b["tex"] for b in d3d_params["bindings"] if b["kind"] == 0}
    groups = [{"name": "", "size": 0, "params": [], "structs": []}]
    bindings = []
    for r in refl:
        if r["kind"] == "cbuffer":
            structs = []
            size, params = struct_layout(msl, r["name"] + "_Type", structs)
            params.sort(key=lambda p: p["isMatrix"])
            groups.append({"name": r["name"], "size": size, "params": params, "structs": structs})
            bindings.append({"name": r["name"], "kind": 1, "index": r["index"], "extra": 0})
        elif r["kind"] == "texture":
            if r["uav"]:
                bindings.append({"name": r["name"], "kind": 3, "index": r["index"], "extra": r["index"]})
                continue
            tex = tex_dim.get(r["name"], (2 << 1))
            bindings.append({"name": r["name"], "kind": 0, "index": r["index"], "extra": r["sampler"], "tex": tex})
        elif r["kind"] == "buffer":
            bindings.append({"name": r["name"], "kind": 3 if r["uav"] else 2, "index": r["index"], "extra": 0})
    return U.write_params({"version": U.VERSION, "groups": groups, "bindings": bindings, "tail": b""})


def input_signature(dxbc_chunks):
    """Return [(semantic name+index, register, system value)] for inputs read by the program."""
    isgn = dxbc_chunks.get(b"ISGN") or dxbc_chunks.get(b"ISG1")
    if not isgn:
        return []
    n = struct.unpack_from("<I", isgn, 0)[0]
    out = []
    for i in range(n):
        name_off, sem_idx, sv, comp, reg, mask, rw = struct.unpack_from("<5I2B", isgn, 8 + i * 24)
        name = isgn[name_off:isgn.index(b"\0", name_off)].decode()
        if rw:  # only inputs the program actually reads get a vertex channel
            out.append((name + str(sem_idx), reg, sv))
    return out


def map_channels(d3d_channels, dxbc_chunks, refl):
    """Translate D3D11 vertex channel targets to Metal attribute targets."""
    if not d3d_channels:
        return []
    inputs = sorted((e for e in input_signature(dxbc_chunks) if e[2] == 0), key=lambda e: e[1])
    attr = {r["name"]: r["index"] for r in refl if r["kind"] == "input"}
    if len(inputs) != len(d3d_channels):
        raise ValueError("channel/input mismatch %r vs %r" % (d3d_channels, inputs))
    out = []
    for (src, _), (sem, _, _) in zip(d3d_channels, inputs):
        if sem not in attr:
            raise ValueError("no Metal attribute for %s" % sem)
        out.append((src, VERTEX_ATTR0 + attr[sem]))
    return out


def minify(msl):
    """Drop indentation and blank lines: Unity keeps decompressed shader source in memory."""
    return "\n".join(l.strip() for l in msl.splitlines() if l.strip()) + "\n"


def program_entry(stage_type, d3d_prog, msl, channels):
    return U.write_program({
        "version": U.VERSION, "type": stage_type, "stats": [0, 0, 0, 0],
        "keywords": d3d_prog["keywords"], "code": CODE_HEADER + minify(msl).encode(),
        "sourceMap": d3d_prog["sourceMap"], "channels": channels, "tail": b"",
    })
