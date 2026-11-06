"""GMO/TGA inventory of the character and weapon models, using the repository parser.

tools/asset-tools/gmo_blender.py is imported through scripts/gmo.py (bpy stubbed), so
this walks the files with the same code the Blender importer uses.
"""
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))
sys.path.insert(0, HERE)
import gmo  # noqa: E402


def gmo_summary(path):
    d = open(path, "rb").read()
    try:
        m = gmo.parse_gmo(d)
    except ValueError as e:
        return {"error": str(e), "bytes": len(d)}
    vtypes = {}
    verts = 0
    for a in m.arrays:
        # parse_arrays already validated the layout; recover the type from the chunk
        pass
    for kind, header, size, at in gmo.walk(d, 0x10, len(d)):
        if kind == 7:
            vt, count = struct.unpack_from("<II", d, at + header)
            vtypes[vt] = vtypes.get(vt, 0) + count
            verts += count
    tex = []
    for name, tga in m.textures:
        if tga is None:
            tex.append((name, "external"))
            continue
        try:
            w, h, _px = gmo.decode_tga(tga)
            tex.append((name, "TGA %dx%d" % (w, h)))
        except Exception:  # noqa: BLE001
            tex.append((name, "TGA? %d bytes" % len(tga)))
    return {
        "bytes": len(d), "bones": len(m.bones), "motions": m.motions,
        "arrays": len(m.arrays), "vertices": verts, "vtypes": vtypes,
        "meshes": len(m.meshes), "materials": m.materials, "textures": tex,
        "motion_names": [mo.name for mo in m.motions],
    }


def main():
    lines = []
    # --- skeleton + motion files -------------------------------------------
    for nn in range(1, 20):
        rel = "g3d/chrm%02d.gmo" % nn
        p = os.path.join(DUMP, rel)
        if not os.path.exists(p):
            lines.append("%-22s MISSING" % rel)
            continue
        s = gmo_summary(p)
        if "error" in s:
            lines.append("%-22s PARSE FAILED %s" % (rel, s["error"]))
            continue
        anim = [(mo.name, mo.range, mo.fps, len(mo.curves)) for mo in s["motions"]]
        bones = [mo for mo in s["motions"]]
        lines.append("%-22s %7d bytes  bones=%d motions=%d" %
                     (rel, s["bytes"], s["bones"], len(s["motions"])))
        lines.append("   animation names: %s" % ",".join(a[0] for a in anim))
        lines.append("   takes with curves: %d ; fps sample %s ; frame range sample %s"
                     % (sum(1 for a in anim if a[3]), anim[0][2] if anim else "-",
                        anim[0][1] if anim else "-"))

    # --- costumes ----------------------------------------------------------
    lines.append("")
    for nn in range(1, 20):
        row = []
        for k in range(9):
            p = os.path.join(DUMP, "g3d/chr%02d%d.gmo" % (nn, k))
            if os.path.exists(p):
                row.append(k)
        lines.append("chr%02d costumes present: %s (%d)" % (nn, row, len(row)))

    # --- one costume in detail, for each new fighter -----------------------
    lines.append("")
    for nn in (3, 2, 17, 18, 19):
        rel = "g3d/chr%02d0.gmo" % nn
        p = os.path.join(DUMP, rel)
        if not os.path.exists(p):
            continue
        s = gmo_summary(p)
        if "error" in s:
            lines.append("%-22s PARSE FAILED %s" % (rel, s["error"]))
            continue
        lines.append("%-22s %7d bytes bones=%d arrays=%d verts=%d meshes=%d materials=%d"
                     % (rel, s["bytes"], s["bones"], s["arrays"], s["vertices"],
                        s["meshes"], len(s["materials"])))
        lines.append("   vertex types: %s" % {hex(k): v for k, v in s["vtypes"].items()})
        lines.append("   materials: %s" % [m[0] for m in s["materials"]])
        lines.append("   textures: %s" % s["textures"])

    # --- weapon models -----------------------------------------------------
    lines.append("")
    for nn in range(1, 25):
        row = []
        for base in ["a", "b", "c", "d", "e", "f", "z"]:
            for suffix in ("", "r1", "r2", "l1", "l2"):
                rel = "g3d/wpn%02d%s%s.gmo" % (nn, base, suffix)
                p = os.path.join(DUMP, rel)
                if os.path.exists(p):
                    s = gmo_summary(p)
                    if "error" in s:
                        row.append("%s%s(PARSE FAILED)" % (base, suffix))
                        continue
                    row.append("%s%s(%dB,%dmat,%dtex)" % (base, suffix, s["bytes"],
                                                          len(s["materials"]),
                                                          len(s["textures"])))
        if row:
            lines.append("wpn%02d: %s" % (nn, " ".join(row)))

    out = os.path.join(HERE, "..", "notes", "gmo_report.txt")
    with open(out, "w") as f:
        f.write("\n".join(lines) + "\n")
    print("\n".join(lines[:12]))
    print("... %d lines -> gmo_report.txt" % len(lines))


if __name__ == "__main__":
    main()
