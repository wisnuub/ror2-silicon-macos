"""Convert D3D11 ComputeShader variants to Metal (Unity 2021.3 ComputeShader serialization)."""
import copy
import struct

import metal
import rdef as R

D3D11_RENDERER, METAL_RENDERER = 2, 16
# Unity TextureDimension codes used by kernel bindings -> blob-style "tex" field
_UAV_TEX = 4  # D3D_SIT_UAV_RWTYPED


def kernel_params(variant, kv):
    """Express one kernel's bindings in the blob parameter layout rdef.build_rdef expects."""
    groups, bindings = [{"name": "", "size": 0, "params": [], "structs": []}], []
    cbs = variant["constantBuffers"]
    for i, cb in zip(kv["cbVariantIndices"], kv["cbs"]):
        src = cbs[i]
        groups.append({"name": cb["name"], "size": src["byteSize"], "structs": [], "params": [
            {"name": p["name"], "type": p["type"], "rows": p["rowCount"], "cols": p["colCount"],
             "isMatrix": int(p["rowCount"] > 1), "arraySize": p["arraySize"], "index": p["offset"]}
            for p in src["params"]]})
        bindings.append({"name": cb["name"], "kind": 1, "index": cb["bindPoint"], "extra": 0})
    for t in kv["textures"]:
        bindings.append({"name": t["name"], "kind": 0, "index": t["bindPoint"], "extra": t["samplerBindPoint"],
                         "tex": max(t["texDimension"], 2) << 1})
    for b in kv["inBuffers"]:
        bindings.append({"name": b["name"], "kind": 2, "index": b["bindPoint"], "extra": 0})
    uav_textures = []
    for b in kv["outBuffers"]:
        if b["texDimension"] > 0:
            uav_textures.append(b)
        else:
            bindings.append({"name": b["name"], "kind": 3, "index": b["bindPoint"], "extra": 0})
    for s in kv["builtinSamplers"]:
        bindings.append({"name": "", "kind": 4, "index": s["bindPoint"], "extra": s["sampler"]})
    return {"groups": groups, "bindings": bindings}, uav_textures


def fixed_dxbc(variant, kv):
    params, uav_textures = kernel_params(variant, kv)
    dx = bytes(kv["code"])
    major, minor, ptype, _ = R.dxbc_info(dx)
    rd = R.build_rdef(params, major, minor, ptype, extra_resources=[
        (u["name"], _UAV_TEX, 5, _srv_dim(u["texDimension"]), 0, u["bindPoint"], 1, 0) for u in uav_textures])
    return R.with_rdef(dx, rd)


def _srv_dim(unity_dim):
    return {2: 4, 3: 8, 4: 9, 5: 5, 6: 10}.get(unity_dim, 4)


def code_blob(msl, group):
    x, y, z = group
    return struct.pack("<3I4H", 0xDEADCAFE, 1, 20, x, y, z, 1) + msl.encode()


def metal_kernel(kv, msl, refl):
    """Rewrite one kernel descriptor's bind points to HLSLcc's Metal slots."""
    slots = {}
    for r in refl:
        if r["kind"] in ("cbuffer", "buffer"):
            slots[r["name"]] = (r["index"], -1)
        elif r["kind"] == "texture":
            slots[r["name"]] = (r["index"], r["sampler"] if not r["uav"] else -1)
    out = copy.deepcopy(kv)
    for key in ("cbs", "textures", "inBuffers", "outBuffers"):
        for b in out[key]:
            name = b["name"]
            alias = "Globals" if name == "$Globals" else name
            if alias not in slots:
                raise ValueError("no Metal slot for %s" % name)
            b["name"] = alias
            b["bindPoint"], samp = slots[alias]
            if key == "textures":
                b["samplerBindPoint"] = samp
    out["code"] = code_blob(metal.minify(msl), kv["threadGroupSize"])
    return out


def metal_cbuffers(variant, msl_by_cb):
    """Metal-layout copies of the variant's constant buffers."""
    out = []
    for cb in variant["constantBuffers"]:
        name = "Globals" if cb["name"] == "$Globals" else cb["name"]
        msl = msl_by_cb.get(name)
        if msl is None:  # no kernel binds it; keep the declared layout
            out.append(dict(cb, name=name))
            continue
        size, params = metal.struct_layout(msl, name + "_Type")
        out.append({"name": name, "byteSize": size, "params": [
            {"name": p["name"], "type": p["type"], "offset": p["index"], "arraySize": p["arraySize"],
             "rowCount": p["rows"] if p["isMatrix"] else 1, "colCount": p["cols"]} for p in params]})
    return out
