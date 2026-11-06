"""Census of GMO vertex formats across every model in the pack.

tools/asset-tools/gmo_blender.py only lays out the formats it can import and raises on
the rest, so this repeats its GE layout arithmetic without the raise, which is what the
census needs. The rules are the same as gmo_blender.vertex_layout:
weights, UV, colour, normal, position, each aligned to its own size; the stride is
rounded up to the largest component.
"""
import os
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psppack import Pack  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
NOTES = os.path.normpath(os.path.join(HERE, "..", "notes"))

SIZES = {0: 0, 1: 1, 2: 2, 3: 4}
COLOUR_SIZE = {0: 0, 1: 1, 2: 2, 3: 4}
NAMES = {0: "none", 1: "u8", 2: "u16", 3: "f32"}


def layout(vtype):
    at, largest = 0, 1

    def place(item, count):
        nonlocal at, largest
        if not item:
            return None
        at = (at + item - 1) & ~(item - 1)
        start = at
        at += item * count
        largest = max(largest, item)
        return start

    wk = (vtype >> 9) & 3
    wc = ((vtype >> 14) & 7) + 1
    weights = place(SIZES[wk], wc) if wk else None
    uvk = vtype & 3
    uv = place(SIZES[uvk], 2) if uvk else None
    ck = (vtype >> 2) & 7
    colour = place(COLOUR_SIZE.get(ck, 0), 1)
    nk = (vtype >> 5) & 3
    normal = place(SIZES[nk], 3) if nk else None
    pk = (vtype >> 7) & 3
    position = place(SIZES[pk], 3) if pk else None
    stride = (at + largest - 1) & ~(largest - 1)
    return {
        "vtype": vtype, "weight_kind": NAMES[wk], "weight_count": wc if wk else 0,
        "uv": NAMES[uvk], "colour": {0: "none", 4: "bgra5551", 5: "bgr565",
                                     6: "bgra4444", 7: "bgra8888"}.get(ck, "?"),
        "normal": NAMES[nk], "position": NAMES[pk], "stride": stride,
        "weights": weights, "uv_off": uv, "colour_off": colour,
        "normal_off": normal, "position_off": position,
        "extra_flags": vtype & 0xFE000000,
    }


def walk(d, start, end):
    while start + 8 <= end:
        kind, header = struct.unpack_from("<HH", d, start)
        size = struct.unpack_from("<I", d, start + 4)[0]
        if size < 8 or start + size > end:
            return
        yield kind, header, size, start
        start += size


CONTAINERS = (2, 3, 5, 6, 8, 9, 0xA)


def scan(d):
    arrays, bones, motions, materials, meshes = [], 0, 0, [], 0

    def descend(start, end):
        nonlocal bones, motions, meshes
        for kind, header, size, at in walk(d, start, end):
            if kind == 4:
                bones += 1
            elif kind == 0xB:
                motions += 1
            elif kind == 7:
                vt, count = struct.unpack_from("<II", d, at + header)
                arrays.append((vt, count))
            elif kind == 6:
                meshes += 1
            elif kind == 8:
                name = d[at + 16:at + header].split(b"\0", 1)[0].decode("ascii", "replace")
                materials.append(name)
            elif kind in CONTAINERS:
                descend(at + header, at + size)

    descend(0x10, len(d))
    return arrays, bones, motions, materials, meshes


def main():
    pack = Pack()
    resolved = {}
    for line in open(os.path.join(NOTES, "resolved.tsv")).read().splitlines()[1:]:
        path, family, csize, usize, sha = line.split("\t")
        resolved[int(sha[:0] or 0) or 0] = None
    by_hash = {}
    for line in open(os.path.join(NOTES, "resolved.tsv")).read().splitlines()[1:]:
        path, family, csize, usize, sha = line.split("\t")
        by_hash[sha] = path
    # path -> sha for the report
    rows = []
    census = {}
    families = {}
    for line in open(os.path.join(NOTES, "all_files.tsv")).read().splitlines()[1:]:
        h, csize, off, usize, magic, sha, sig = line.split("\t")
        if magic != "GMO":
            continue
        cs, o, _u = pack.rows[int(h, 16)]
        pack.f.seek(__import__("psppack").BASE + o)
        d = __import__("gzip").decompress(pack.f.read(cs))
        arrays, bones, motions, materials, meshes = scan(d)
        path = by_hash.get(sha, "<%s>" % h)
        rows.append((path, len(d), bones, motions, meshes, len(materials),
                     sorted({a[0] for a in arrays}), sum(a[1] for a in arrays)))
        for vt, count in arrays:
            census.setdefault(vt, [0, 0])
            census[vt][0] += 1
            census[vt][1] += count
        key = path.split("/")[0] + "/" + os.path.basename(path)[:5]
    with open(os.path.join(NOTES, "gmo_census.tsv"), "w") as f:
        f.write("path\tbytes\tbones\tmotions\tmeshes\tmaterials\tvertex_types\tvertices\n")
        for r in sorted(rows):
            f.write("%s\t%d\t%d\t%d\t%d\t%d\t%s\t%d\n"
                    % (r[0], r[1], r[2], r[3], r[4], r[5],
                       ",".join("0x%x" % v for v in r[6]), r[7]))
    print("GMO files:", len(rows))
    print("\nvertex type census (type: arrays, vertices, layout):")
    for vt, (n, verts) in sorted(census.items()):
        lay = layout(vt)
        print("  0x%08x  arrays=%-4d verts=%-7d %s weights=%d(%s) uv=%s colour=%s "
              "normal=%s pos=%s stride=%d"
              % (vt, n, verts, "", lay["weight_count"], lay["weight_kind"], lay["uv"],
                 lay["colour"], lay["normal"], lay["position"], lay["stride"]))
    print()
    for r in sorted(rows):
        if r[0].startswith("g3d/chrm") or r[0].startswith("g3d/chrt"):
            continue
        print("%-26s %7dB bones=%-3d motions=%-3d meshes=%-2d mat=%-2d vt=%s verts=%d"
              % (r[0], r[1], r[2], r[3], r[4], r[5],
                 ",".join("0x%x" % v for v in r[6]), r[7]))


if __name__ == "__main__":
    main()
