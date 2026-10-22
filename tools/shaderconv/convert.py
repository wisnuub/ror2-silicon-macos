#!/usr/bin/env python3
"""Convert D3D11-only Unity 2021.3 shaders in asset files/bundles to Metal.

For every Shader object, each D3D11 vertex/fragment subprogram is:
  1. given back the RDEF chunk Unity stripped (rebuilt from Unity's parameter data),
  2. translated DXBC -> MSL with HLSLcc (the translator Unity itself uses for Metal),
  3. re-serialized as a Unity Metal subprogram plus a Metal parameter entry.
The shader's platform data is then switched from D3D11 (4) to Metal (14).

usage: convert.py [--dry-run] [--work DIR] <in-file> [<out-file>]
       convert.py [--dry-run] --data <Game>_Data
"""
import argparse
import hashlib
import json
import os
import subprocess
import sys
import collections
import re

import lz4.block
import UnityPy

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import compute  # noqa: E402
import metal  # noqa: E402
import rdef as R  # noqa: E402
import unityblob as U  # noqa: E402

D3D11, METAL = 4, 14
STAGE_TYPES = {"progVertex": ({15, 16}, metal.METAL_VS), "progFragment": ({17, 18}, metal.METAL_FS)}
OTHER_STAGES = ("progGeometry", "progHull", "progDomain", "progRayTracing")
SEGMENT_LIMIT = 1 << 20

# Per-shader MSL fixups for behaviour that differs between D3D11 and Apple GPUs.
# UI/Healthbar divides by _Rect.y, which its material leaves at 0: on D3D11 the vertex outputs
# are +/-inf, the rasterizer interpolates them to NaN and no pixel is discarded. Apple GPUs
# interpolate non-finite varyings to finite values, so every pixel was discarded (empty bar).
MSL_FIXUPS = {
    "UI/Healthbar": [(r"output\.TEXCOORD2 = (u_xlat\d\.x) / VGlobals\._Rect\.y;",
                      r"output.TEXCOORD2 = (VGlobals._Rect.y == 0.0) ? 0.5 : (\1 / VGlobals._Rect.y);")],
}  # keep each decompressed blob segment modest
EMPTY_COMMON = {k: [] for k in ("m_VectorParams", "m_MatrixParams", "m_TextureParams", "m_BufferParams",
                                "m_ConstantBuffers", "m_ConstantBufferBindings", "m_UAVParams", "m_Samplers")}


def blob_entries(t, pi):
    blob = bytes(t["compressedBlob"])
    segs = [lz4.block.decompress(blob[o:o + c], uncompressed_size=d)
            for o, c, d in zip(t["offsets"][pi], t["compressedLengths"][pi], t["decompressedLengths"][pi])]
    return U.entries(segs)


class Job:
    __slots__ = ("key", "dxbc_path", "metal_path", "json_path", "ok")


class Converter:
    def __init__(self, work, translator):
        self.work, self.translator = work, translator
        self.jobs = {}
        self.stats = collections.Counter()
        os.makedirs(work, exist_ok=True)

    def job_for(self, fixed_dxbc):
        key = hashlib.sha1(fixed_dxbc).hexdigest()
        if key not in self.jobs:
            j = Job()
            j.key = key
            j.dxbc_path = os.path.join(self.work, key + ".dxbc")
            j.metal_path = os.path.join(self.work, key + ".metal")
            j.json_path = os.path.join(self.work, key + ".json")
            j.ok = os.path.exists(j.metal_path) and os.path.exists(j.json_path)
            if not j.ok:
                tmp = "%s.%d" % (j.dxbc_path, os.getpid())
                with open(tmp, "wb") as f:
                    f.write(fixed_dxbc)
                os.replace(tmp, j.dxbc_path)
            self.jobs[key] = j
        return self.jobs[key]

    def plan_shader(self, t):
        """Phase 1: work out every subprogram's translation job. Returns a plan or None."""
        if D3D11 not in t["platforms"]:
            return None
        pi = t["platforms"].index(D3D11)
        entries = blob_entries(t, pi)
        plan = []
        for si, ss in enumerate(t["m_ParsedForm"]["m_SubShaders"]):
            for pj, p in enumerate(ss["m_Passes"]):
                extra = [st for st in OTHER_STAGES if p.get(st) and any(p[st]["m_PlayerSubPrograms"])]
                if extra:
                    # Geometry/tessellation stages have no HLSLcc Metal path here: leave the pass
                    # without Metal programs so Unity skips the subshader and uses the fallback.
                    self.stats["pass disabled (%s)" % "+".join(extra)] += 1
                    continue
                names = {i: n for n, i in p["m_NameIndices"]}
                for stage, (d3d_types, mtype) in STAGE_TYPES.items():
                    prog = p[stage]
                    common = R.params_from_common(prog["m_CommonParameters"], names)
                    for li, lst in enumerate(prog["m_PlayerSubPrograms"]):
                        for k, sub in enumerate(lst):
                            if sub["m_GpuProgramType"] not in d3d_types:
                                continue
                            pidx = prog["m_ParameterBlobIndices"][li][k]
                            d3d_prog = U.parse_program(entries[sub["m_BlobIndex"]])
                            params = R.merge(common, U.parse_params(entries[pidx]))
                            dx = d3d_prog["code"][d3d_prog["code"].find(b"DXBC"):]
                            major, minor, ptype, chunks = R.dxbc_info(dx)
                            fixed = R.with_rdef(dx, R.build_rdef(params, major, minor, ptype))
                            plan.append((si, pj, stage, li, sub, mtype, d3d_prog, params, chunks,
                                         self.job_for(fixed)))
        return plan

    def plan_compute(self, t):
        """Translation jobs for every D3D11 kernel variant of a ComputeShader."""
        variants = [v for v in t["variants"] if v["targetRenderer"] == compute.D3D11_RENDERER]
        if not variants:
            return None
        plan = []
        for vi, v in enumerate(t["variants"]):
            if v["targetRenderer"] != compute.D3D11_RENDERER:
                continue
            for ki, k in enumerate(v["kernels"]):
                for mi, (kw, kv) in enumerate(k["variantMap"]):
                    plan.append((vi, ki, mi, self.job_for(compute.fixed_dxbc(v, kv))))
        return plan

    def build_compute(self, t, plan):
        """Replace D3D11 compute variants with Metal ones."""
        failed = False
        msl_by_cb = collections.defaultdict(dict)
        new_kernels = {}
        for vi, ki, mi, job in plan:
            kv = t["variants"][vi]["kernels"][ki]["variantMap"][mi][1]
            if not job.ok:
                failed = True
                break
            msl = open(job.metal_path).read()
            refl = json.load(open(job.json_path))
            try:
                new_kernels[(vi, ki, mi)] = compute.metal_kernel(kv, msl, refl)
            except Exception as e:  # noqa: BLE001
                print("  compute %s: %s" % (t["m_Name"], e), file=sys.stderr)
                failed = True
                break
            for r in refl:
                if r["kind"] == "cbuffer":
                    msl_by_cb[vi].setdefault(r["name"], msl)
        if failed:
            self.stats["compute shader left as-is"] += 1
            return None
        for vi, v in enumerate(t["variants"]):
            if v["targetRenderer"] != compute.D3D11_RENDERER:
                continue
            for ki, k in enumerate(v["kernels"]):
                k["variantMap"] = [[kw, new_kernels[(vi, ki, mi)]] for mi, (kw, _) in enumerate(k["variantMap"])]
            v["constantBuffers"] = compute.metal_cbuffers(v, msl_by_cb[vi])
            v["targetRenderer"] = compute.METAL_RENDERER
            self.stats["compute kernels converted"] += sum(len(k["variantMap"]) for k in v["kernels"])
        self.stats["compute shaders"] += 1
        return t

    def run_jobs(self):
        """Phase 2: translate all pending jobs in one batch process (restarting after crashes)."""
        pending = [j for j in self.jobs.values() if not j.ok]
        while pending:
            proc = subprocess.Popen([self.translator, "--batch"], stdin=subprocess.PIPE,
                                    stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, text=True)
            pid = os.getpid()
            lines = "".join("%s\t%s.%d\t%s.%d\n" % (j.dxbc_path, j.metal_path, pid, j.json_path, pid) for j in pending)
            out, _ = proc.communicate(lines)
            done = 0
            for line in out.splitlines():
                status, n = line.split()
                j = pending[int(n)]
                j.ok = status == "ok"
                if j.ok:  # publish atomically; other workers may share the cache
                    os.replace("%s.%d" % (j.metal_path, pid), j.metal_path)
                    os.replace("%s.%d" % (j.json_path, pid), j.json_path)
                done = int(n) + 1
            if done < len(pending):  # translator crashed on pending[done]
                pending[done].ok = False
                self.stats["translator crash"] += 1
                pending = pending[done + 1:]
            else:
                pending = []

    def build_shader(self, t, plan):
        """Phase 3: replace D3D11 platform data with Metal subprograms."""
        out_entries, cache = [], {}

        def add(entry):
            if entry not in cache:
                cache[entry] = len(out_entries)
                out_entries.append(entry)
            return cache[entry]

        new_lists = {}
        for (si, pj, stage, li, sub, mtype, d3d_prog, params, chunks, job) in plan:
            key = (si, pj, stage)
            if key not in new_lists:
                stage_obj = t["m_ParsedForm"]["m_SubShaders"][si]["m_Passes"][pj][stage]
                new_lists[key] = ([[] for _ in stage_obj["m_PlayerSubPrograms"]],
                                  [[] for _ in stage_obj["m_PlayerSubPrograms"]])
            if not job.ok:
                self.stats["variant dropped (translate failed: %s)" % t["m_ParsedForm"]["m_Name"]] += 1
                continue
            try:
                msl = open(job.metal_path).read()
                for pat, rep in MSL_FIXUPS.get(t["m_ParsedForm"]["m_Name"], ()):
                    msl, n = re.subn(pat, rep, msl)
                    self.stats["msl fixups applied"] += n
                refl = json.load(open(job.json_path))
                chans = metal.map_channels(d3d_prog["channels"], chunks, refl)
                prog_e = metal.program_entry(mtype, d3d_prog, msl, chans)
                param_e = metal.param_entry(msl, refl, params)
            except Exception as e:  # noqa: BLE001 - report and drop the variant
                self.stats["variant dropped (%s)" % type(e).__name__] += 1
                if self.stats["variant dropped (%s)" % type(e).__name__] <= 3:
                    print("  drop:", e, file=sys.stderr)
                continue
            subs, pidx = new_lists[key]
            subs[li].append({"m_BlobIndex": add(prog_e), "m_KeywordIndices": sub["m_KeywordIndices"],
                             "m_ShaderRequirements": sub["m_ShaderRequirements"], "m_GpuProgramType": mtype})
            pidx[li].append(add(param_e))
            self.stats["variant converted"] += 1

        for ss in t["m_ParsedForm"]["m_SubShaders"]:
            for p in ss["m_Passes"]:
                p["m_Platforms"] = [METAL if x == D3D11 else x for x in p["m_Platforms"]]
        for si, ss in enumerate(t["m_ParsedForm"]["m_SubShaders"]):
            for pj, p in enumerate(ss["m_Passes"]):
                for stage in tuple(STAGE_TYPES) + OTHER_STAGES:
                    prog = p.get(stage)
                    if not prog:
                        continue
                    n = len(prog["m_PlayerSubPrograms"])
                    subs, pidx = new_lists.get((si, pj, stage), ([[] for _ in range(n)], [[] for _ in range(n)]))
                    prog["m_PlayerSubPrograms"] = subs
                    prog["m_ParameterBlobIndices"] = pidx
                    prog["m_CommonParameters"] = dict(EMPTY_COMMON)

        # Pack into segments, entries never straddle segments.
        segs, cur, table = [], bytearray(), []
        hdr = 4 + 12 * len(out_entries)
        cur_base = hdr
        for e in out_entries:
            if len(cur) and cur_base + len(cur) + len(e) > SEGMENT_LIMIT:
                segs.append(bytes(cur)); cur = bytearray(); cur_base = 0
            table.append((cur_base + len(cur), len(e), len(segs)))
            cur += e
        segs.append(bytes(cur))
        head = bytearray(U.struct.pack("<I", len(out_entries)))
        for off, ln, sg in table:
            head += U.struct.pack("<III", off, ln, sg)
        segs[0] = bytes(head) + segs[0]

        blob, offs, clens, dlens = bytearray(), [], [], []
        for s in segs:
            c = lz4.block.compress(s, mode="high_compression", compression=12, store_size=False)
            offs.append(len(blob)); clens.append(len(c)); dlens.append(len(s))
            blob += c
        pi = t["platforms"].index(D3D11)
        t["platforms"] = [METAL]
        t["offsets"] = [offs]
        t["compressedLengths"] = [clens]
        t["decompressedLengths"] = [dlens]
        t["stageCounts"] = [t["stageCounts"][pi]]
        t["compressedBlob"] = bytes(blob)
        return t


def convert_file(src, dst, work, translator, dry_run=False):
    """Convert every D3D11 shader in one bundle or serialized file; returns stats."""
    conv = Converter(work, translator)
    env = UnityPy.load(src)
    plans = []
    for o in env.objects:
        if o.type.name not in ("Shader", "ComputeShader"):
            continue
        t = o.read_typetree()
        try:
            plan = conv.plan_compute(t) if o.type.name == "ComputeShader" else conv.plan_shader(t)
        except Exception as e:  # noqa: BLE001
            conv.stats["shader skipped (%s)" % type(e).__name__] += 1
            name = t["m_ParsedForm"]["m_Name"] if "m_ParsedForm" in t else t.get("m_Name")
            print("  skip %s: %s" % (name, e), file=sys.stderr)
            continue
        if plan is not None:
            plans.append((o, t, plan))
    if not plans:
        return conv.stats
    conv.stats["unique programs"] = len(conv.jobs)
    conv.run_jobs()
    conv.stats["programs failed"] = sum(1 for j in conv.jobs.values() if not j.ok)

    is_bundle = open(src, "rb").read(8) == b"UnityFS\0"
    patches = []
    for o, t, plan in plans:
        if o.type.name == "ComputeShader":
            t = conv.build_compute(t, plan)
            if t is None:
                continue
        else:
            t = conv.build_shader(t, plan)
            conv.stats["shaders"] += 1
        if dry_run:
            continue
        old_start, old_size = o.byte_start, o.byte_size
        new_data = o.save_typetree(t)  # get_raw_data() would re-read the original bytes
        if not is_bundle:
            sf = o.assets_file
            patches.append((o.path_id, o.type_id, old_start - sf.header.data_offset, old_size, new_data))
    if dry_run:
        return conv.stats
    if is_bundle:
        data = env.file.save(packer="lz4")
    else:
        import serialized
        data = serialized.patch_objects(open(src, "rb").read(), patches)
    tmp = dst + ".tmp"
    with open(tmp, "wb") as f:
        f.write(data)
    os.replace(tmp, dst)
    return conv.stats


def _worker(args):
    src, work, translator, dry_run = args
    try:
        return src, dict(convert_file(src, src, work, translator, dry_run)), None
    except Exception as e:  # noqa: BLE001
        return src, {}, "%s: %s" % (type(e).__name__, e)


def find_shader_files(data_dir):
    """Loose serialized files and Addressables bundles that contain Shader objects."""
    import glob
    cands = [os.path.join(data_dir, f) for f in os.listdir(data_dir)
             if f.endswith(".assets") or f.startswith("level") and not f.endswith(".resS")]
    cands += glob.glob(os.path.join(data_dir, "Resources", "unity_builtin_extra"))
    cands += glob.glob(os.path.join(data_dir, "StreamingAssets", "aa", "*", "*.bundle"))
    out = []
    for f in sorted(cands):
        try:
            env = UnityPy.load(f)
        except Exception:  # noqa: BLE001
            continue
        if any(o.type.name in ("Shader", "ComputeShader") for o in env.objects):
            out.append(f)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--dry-run", action="store_true")
    ap.add_argument("--work", default=os.path.join(HERE, ".work"))
    ap.add_argument("--translator", default=os.path.join(HERE, "dxbc2msl"))
    ap.add_argument("--data", help="convert every shader file under this <Game>_Data dir in place")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("src", nargs="?")
    ap.add_argument("dst", nargs="?")
    a = ap.parse_args()
    os.makedirs(a.work, exist_ok=True)

    if a.data:
        import multiprocessing as mp
        files = find_shader_files(a.data)
        print("Converting shaders in %d files..." % len(files))
        total, errors = collections.Counter(), []
        with mp.Pool(a.jobs) as pool:
            for i, (src, stats, err) in enumerate(pool.imap_unordered(
                    _worker, [(f, a.work, a.translator, a.dry_run) for f in files]), 1):
                total.update(stats)
                if err:
                    errors.append((src, err))
                print("  [%d/%d] %s %s" % (i, len(files), os.path.basename(src), err or ""), flush=True)
        print(json.dumps(dict(total), indent=1))
        for src, err in errors:
            print("ERROR", src, err)
        sys.exit(1 if errors else 0)

    stats = convert_file(a.src, a.dst or a.src, a.work, a.translator, a.dry_run)
    print(json.dumps(dict(stats), indent=1))


if __name__ == "__main__":
    main()
