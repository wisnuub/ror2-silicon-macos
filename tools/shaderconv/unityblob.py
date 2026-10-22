"""Reader/writer for Unity 2021.2+ (version 202012090) serialized shader subprogram blobs."""
import struct

VERSION = 202012090


class R:
    def __init__(self, b, p=0):
        self.b, self.p = b, p

    def i32(self):
        v = struct.unpack_from("<i", self.b, self.p)[0]; self.p += 4; return v

    def u32(self):
        v = struct.unpack_from("<I", self.b, self.p)[0]; self.p += 4; return v

    def align(self):
        self.p = (self.p + 3) & ~3

    def string(self):
        n = self.i32(); s = self.b[self.p:self.p + n].decode("utf-8"); self.p += n; self.align(); return s

    def bytes_(self):
        n = self.i32(); v = self.b[self.p:self.p + n]; self.p += n; self.align(); return v


class W:
    def __init__(self):
        self.b = bytearray()

    def i32(self, v):
        self.b += struct.pack("<i", v)

    def u32(self, v):
        self.b += struct.pack("<I", v)

    def align(self):
        while len(self.b) % 4: self.b.append(0)

    def string(self, s):
        e = s.encode("utf-8"); self.i32(len(e)); self.b += e; self.align()

    def bytes_(self, v):
        self.i32(len(v)); self.b += v; self.align()


def entries(raw_segments):
    """Return list of entry byte strings from the decompressed segments."""
    head = raw_segments[0]
    n = struct.unpack_from("<I", head, 0)[0]
    out = []
    for i in range(n):
        off, ln, seg = struct.unpack_from("<III", head, 4 + i * 12)
        out.append(raw_segments[seg][off:off + ln])
    return out


def pack_entries(blobs):
    """Pack entry byte strings into a single segment with the offset table."""
    hdr = 4 + 12 * len(blobs)
    table, body, off = bytearray(struct.pack("<I", len(blobs))), bytearray(), hdr
    for e in blobs:
        table += struct.pack("<III", off, len(e), 0)
        body += e; off += len(e)
    return bytes(table + body)


def parse_program(e):
    r = R(e)
    d = {"version": r.i32(), "type": r.i32(), "stats": [r.i32(), r.i32(), r.i32(), r.i32()]}
    d["keywords"] = [r.string() for _ in range(r.i32())]
    d["code"] = r.bytes_()
    d["sourceMap"] = r.u32()
    d["channels"] = [(r.u32(), r.u32()) for _ in range(r.i32())]
    d["tail"] = e[r.p:]
    return d


def write_program(d):
    w = W()
    w.i32(d["version"]); w.i32(d["type"])
    for s in d["stats"]: w.i32(s)
    w.i32(len(d["keywords"]))
    for k in d["keywords"]: w.string(k)
    w.bytes_(d["code"])
    w.u32(d["sourceMap"]); w.i32(len(d["channels"]))
    for a, b in d["channels"]: w.u32(a); w.u32(b)
    w.b += d["tail"]
    return bytes(w.b)


def parse_params(e):
    r = R(e)
    d = {"version": r.i32(), "groups": [], "bindings": []}
    for _ in range(r.i32()):
        g = {"name": r.string(), "size": r.i32(), "params": [], "structs": []}
        for _ in range(r.i32()):
            g["params"].append({"name": r.string(), "type": r.i32(), "rows": r.i32(), "cols": r.i32(),
                                "isMatrix": r.i32(), "arraySize": r.i32(), "index": r.i32()})
        for _ in range(r.i32()):
            st = {"name": r.string(), "index": r.i32(), "arraySize": r.i32(), "structSize": r.i32(), "params": []}
            for _ in range(r.i32()):
                st["params"].append({"name": r.string(), "type": r.i32(), "rows": r.i32(), "cols": r.i32(),
                                     "isMatrix": r.i32(), "arraySize": r.i32(), "index": r.i32()})
            g["structs"].append(st)
        d["groups"].append(g)
    for _ in range(r.i32()):
        b = {"name": r.string(), "kind": r.i32(), "index": r.i32(), "extra": r.i32()}
        if b["kind"] == 0:
            b["tex"] = r.u32()
        d["bindings"].append(b)
    d["tail"] = e[r.p:]
    return d


def write_params(d):
    w = W()
    w.i32(d["version"]); w.i32(len(d["groups"]))
    for g in d["groups"]:
        w.string(g["name"]); w.i32(g["size"]); w.i32(len(g["params"]))
        for p in g["params"]:
            w.string(p["name"]); w.i32(p["type"]); w.i32(p["rows"]); w.i32(p["cols"])
            w.i32(p["isMatrix"]); w.i32(p["arraySize"]); w.i32(p["index"])
        w.i32(len(g.get("structs", [])))
        for st in g.get("structs", []):
            w.string(st["name"]); w.i32(st["index"]); w.i32(st["arraySize"]); w.i32(st["structSize"])
            w.i32(len(st["params"]))
            for p in st["params"]:
                w.string(p["name"]); w.i32(p["type"]); w.i32(p["rows"]); w.i32(p["cols"])
                w.i32(p["isMatrix"]); w.i32(p["arraySize"]); w.i32(p["index"])
    w.i32(len(d["bindings"]))
    for b in d["bindings"]:
        w.string(b["name"]); w.i32(b["kind"]); w.i32(b["index"]); w.i32(b["extra"])
        if b["kind"] == 0: w.u32(b["tex"])
    w.b += d["tail"]
    return bytes(w.b)
