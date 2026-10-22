"""Rebuild the DXBC RDEF reflection chunk that Unity strips from player builds.

Unity keeps the information in its own parameter format (blob parameter entries
plus m_CommonParameters in the parsed form). HLSLcc needs RDEF to name constant
buffers, variables, textures and samplers, so we synthesize one from Unity's data.
"""
import struct

# Unity ShaderParamType -> D3D_SHADER_VARIABLE_TYPE
_SVT = {0: 3, 1: 2, 2: 1, 3: 3, 4: 2, 5: 19}  # float,int,bool,half,short,uint
# Unity TextureDimension -> D3D_SRV_DIMENSION (non-MS, MS)
_SRV = {2: (4, 6), 3: (8, 8), 4: (9, 9), 5: (5, 7), 6: (10, 10)}


def params_from_common(cp, names):
    """Convert a parsed-form m_CommonParameters dict into blob-entry layout."""
    def vec(v):
        return {"name": names[v["m_NameIndex"]], "type": v["m_Type"], "rows": 1, "cols": v["m_Dim"],
                "isMatrix": 0, "arraySize": v["m_ArraySize"], "index": v["m_Index"]}

    def mat(m):
        return {"name": names[m["m_NameIndex"]], "type": m["m_Type"], "rows": m["m_RowCount"],
                "cols": m.get("m_ColumnCount", m["m_RowCount"]), "isMatrix": 1,
                "arraySize": m["m_ArraySize"], "index": m["m_Index"]}

    groups = [{"name": "", "size": 0, "params": [vec(v) for v in cp["m_VectorParams"]] +
               [mat(m) for m in cp["m_MatrixParams"]], "structs": []}]
    def struct_(sp):
        return {"name": names[sp["m_NameIndex"]], "index": sp["m_Index"], "arraySize": sp["m_ArraySize"],
                "structSize": sp["m_StructSize"],
                "params": [vec(v) for v in sp["m_VectorMembers"]] + [mat(m) for m in sp["m_MatrixMembers"]]}

    for cb in cp["m_ConstantBuffers"]:
        groups.append({"name": names[cb["m_NameIndex"]], "size": cb["m_Size"],
                       "params": [vec(v) for v in cb["m_VectorParams"]] + [mat(m) for m in cb["m_MatrixParams"]],
                       "structs": [struct_(sp) for sp in cb.get("m_StructParams", [])]})
    b = []
    for t in cp["m_TextureParams"]:
        b.append({"name": names[t["m_NameIndex"]], "kind": 0, "index": t["m_Index"], "extra": t["m_SamplerIndex"],
                  "tex": (t["m_Dim"] << 1) | int(t["m_MultiSampled"])})
    for c in cp["m_ConstantBufferBindings"]:
        b.append({"name": names[c["m_NameIndex"]], "kind": 1, "index": c["m_Index"], "extra": c.get("m_ArraySize", 1)})
    for c in cp["m_BufferParams"]:
        b.append({"name": names[c["m_NameIndex"]], "kind": 2, "index": c["m_Index"], "extra": c.get("m_ArraySize", 1)})
    for u in cp["m_UAVParams"]:
        b.append({"name": names[u["m_NameIndex"]], "kind": 3, "index": u["m_Index"], "extra": u["m_OriginalIndex"]})
    for s in cp["m_Samplers"]:
        bind = s.get("m_BindPoint", s.get("bindPoint"))
        state = s.get("m_Sampler", s.get("sampler"))
        b.append({"name": "", "kind": 4, "index": bind, "extra": state})
    return {"groups": groups, "bindings": b}


_FILTERS = ("point", "linear", "trilinear", "linear")
_WRAPS = ("repeat", "clamp", "mirror", "mirroronce")


def inline_sampler_name(state):
    """Rebuild an inline sampler name (e.g. sampler_linear_clamp) from Unity's packed sampler state.

    Layout: filter bits 0-1, wrap U/V/W in bits 2-3/4-5/6-7, depth compare in bit 8.
    HLSLcc turns names like this into Metal constexpr samplers."""
    f = _FILTERS[state & 3]
    u, v, w = (_WRAPS[(state >> s) & 3] for s in (2, 4, 6))
    wrap = u if u == v == w else "%su_%sv_%sw" % (u, v, w)
    return "sampler_%s_%s%s" % (f, wrap, "_compare" if state & 0x100 else "")


def merge(a, b):
    """Merge two parameter sets (common + per-variant); cbuffers merge by name."""
    groups = {g["name"]: {"name": g["name"], "size": g["size"], "params": list(g["params"]),
                          "structs": list(g.get("structs", []))} for g in a["groups"]}
    order = [g["name"] for g in a["groups"]]
    for g in b["groups"]:
        if g["name"] in groups:
            dst = groups[g["name"]]
            have = {p["name"] for p in dst["params"]}
            dst["params"] += [p for p in g["params"] if p["name"] not in have]
            have_s = {x["name"] for x in dst["structs"]}
            dst["structs"] += [x for x in g.get("structs", []) if x["name"] not in have_s]
            dst["size"] = max(dst["size"], g["size"])
        else:
            groups[g["name"]] = {"name": g["name"], "size": g["size"], "params": list(g["params"]),
                                 "structs": list(g.get("structs", []))}
            order.append(g["name"])
    if "" not in groups:
        groups[""] = {"name": "", "size": 0, "params": [], "structs": []}
        order.insert(0, "")
    seen, bindings = set(), []
    for x in a["bindings"] + b["bindings"]:
        k = (x["kind"], x["name"], x["index"])
        if k not in seen:
            seen.add(k); bindings.append(x)
    return {"groups": [groups[n] for n in order], "bindings": bindings}


def _type_desc(p):
    if p["isMatrix"]:
        cls = 3
    elif p["rows"] == 1 and p["cols"] == 1:
        cls = 0
    else:
        cls = 1
    return struct.pack("<6HI", cls, _SVT.get(p["type"], 3), p["rows"], p["cols"], p["arraySize"], 0, 0)


def _struct_var(st):
    return {"name": st["name"], "index": st["index"], "arraySize": st["arraySize"],
            "structSize": st["structSize"], "members": sorted(st["params"], key=lambda m: m["index"])}


def _var_size(p):
    if "members" in p:
        stride = (p["structSize"] + 15) & ~15
        return stride * max(p["arraySize"], 1)
    n = max(p["arraySize"], 1)
    if p["isMatrix"]:
        regs, last = p["cols"], (p["cols"] - 1) * 16 + p["rows"] * 4
    else:
        regs, last = 1, p["cols"] * 4
    return (n - 1) * regs * 16 + last


class _Strings:
    def __init__(self):
        self.items = []

    def add(self, s):
        self.items.append(s)
        return len(self.items) - 1


def build_rdef(params, major, minor, shader_type, extra_resources=()):
    """Return RDEF chunk payload. shader_type: 0 pixel, 1 vertex (DXBC program type)."""
    cbuffers = [g for g in params["groups"] if g["name"]]
    resources = []  # (name, type, ret, dim, samples, bind, count, flags)
    sampler_names = {}
    for b in params["bindings"]:
        if b["kind"] == 0:
            dim, ms = b["tex"] >> 1, b["tex"] & 1
            srv = _SRV.get(dim, (4, 6))[ms]
            resources.append((b["name"], 2, 5, srv, 0xFFFFFFFF if not ms else 0, b["index"], 1, 0xC))
            sampler_names.setdefault(b["extra"], "sampler" + b["name"])
    for b in params["bindings"]:
        if b["kind"] == 4:
            sampler_names.setdefault(b["index"], inline_sampler_name(b["extra"]))
    for s, name in sorted(sampler_names.items()):
        if s >= 0:
            resources.append((name, 3, 0, 0, 0, s, 1, 0))
    for b in params["bindings"]:
        if b["kind"] == 1:
            resources.append((b["name"], 0, 0, 0, 0, b["index"], 1, 0))
        elif b["kind"] == 2:
            resources.append((b["name"], 5, 6, 1, 0, b["index"], 1, 0))
        elif b["kind"] == 3:
            resources.append((b["name"], 6, 6, 1, 0, b["index"], 1, 0))
    resources.extend(extra_resources)

    sm5 = major >= 5
    var_words = 10 if sm5 else 6
    hdr = 28  # 7 words
    rb_off = hdr
    cb_off = rb_off + len(resources) * 32
    var_off = cb_off + len(cbuffers) * 24
    # Declaration order must follow byte offsets: HLSLcc lays struct members out in RDEF order,
    # and Unity's parameter lists put vectors before matrices.
    cb_vars = [sorted(list(g["params"]) + [_struct_var(st) for st in g.get("structs", [])], key=lambda v: v["index"])
               for g in cbuffers]
    nvars = sum(len(v) for v in cb_vars)
    nmembers = sum(len(v["members"]) for vs in cb_vars for v in vs if "members" in v)
    type_off = var_off + nvars * var_words * 4
    member_type_off = type_off + nvars * 16
    member_off = member_type_off + nmembers * 16
    str_off = member_off + nmembers * 12

    strings = bytearray()
    str_pos = {}

    def s(name):
        if name not in str_pos:
            str_pos[name] = str_off + len(strings)
            strings.extend(name.encode() + b"\0")
        return str_pos[name]

    out = bytearray()
    version = ({0: 0xFFFF, 1: 0xFFFE, 5: 0x4353}.get(shader_type, 0xFFFE) << 16) | (major << 4) | minor
    out += struct.pack("<7I", len(cbuffers), cb_off, len(resources), rb_off, version, 0, s("RoR2-Mac"))
    for r in resources:
        out += struct.pack("<8I", s(r[0]), *r[1:])
    vi = 0
    for g, vs in zip(cbuffers, cb_vars):
        size = (max(g["size"], max([p["index"] + _var_size(p) for p in vs] or [0])) + 15) & ~15
        out += struct.pack("<6I", s(g["name"]), len(vs), var_off + vi * var_words * 4, size, 0, 0)
        vi += len(vs)
    ti = 0
    for vs in cb_vars:
        for p in vs:
            out += struct.pack("<6I", s(p["name"]), p["index"], _var_size(p), 2, type_off + ti * 16, 0)
            if sm5:
                out += struct.pack("<4I", 0xFFFFFFFF, 0, 0xFFFFFFFF, 0)
            ti += 1
    mi = 0
    for vs in cb_vars:
        for p in vs:
            if "members" in p:
                out += struct.pack("<6HI", 5, 0, 1, p["structSize"] // 4, p["arraySize"], len(p["members"]),
                                   member_off + mi * 12)
                mi += len(p["members"])
            else:
                out += _type_desc(p)
    for vs in cb_vars:
        for p in vs:
            for m in p.get("members", []):
                out += _type_desc(m)
    mi = 0
    for vs in cb_vars:
        for p in vs:
            for m in p.get("members", []):
                out += struct.pack("<3I", s(m["name"]), member_type_off + mi * 16, m["index"])
                mi += 1
    assert len(out) == str_off, (len(out), str_off)
    out += strings
    while len(out) % 4:
        out.append(0)
    return bytes(out)


def dxbc_info(dxbc):
    """Return (major, minor, program_type, chunk dict) for a DXBC container."""
    n = struct.unpack_from("<I", dxbc, 28)[0]
    chunks = {}
    for i in range(n):
        off = struct.unpack_from("<I", dxbc, 32 + i * 4)[0]
        cc = dxbc[off:off + 4]
        size = struct.unpack_from("<I", dxbc, off + 4)[0]
        chunks[cc] = dxbc[off + 8:off + 8 + size]
    code = chunks.get(b"SHDR") or chunks.get(b"SHEX")
    tok = struct.unpack_from("<I", code, 0)[0]
    return (tok >> 4) & 0xF, tok & 0xF, (tok >> 16) & 0xFFFF, chunks


def with_rdef(dxbc, rdef):
    """Return a new DXBC container with an RDEF chunk prepended (checksum left stale)."""
    n = struct.unpack_from("<I", dxbc, 28)[0]
    parts = [b"RDEF" + struct.pack("<I", len(rdef)) + rdef]
    for i in range(n):
        off = struct.unpack_from("<I", dxbc, 32 + i * 4)[0]
        size = struct.unpack_from("<I", dxbc, off + 4)[0]
        if dxbc[off:off + 4] != b"RDEF":
            parts.append(dxbc[off:off + 8 + size])
    head = 32 + 4 * len(parts)
    offs, pos = [], head
    for p in parts:
        offs.append(pos); pos += len(p)
    out = bytearray(dxbc[:20]) + struct.pack("<III", 1, pos, len(parts)) + struct.pack("<%dI" % len(parts), *offs)
    for p in parts:
        out += p
    return bytes(out)
