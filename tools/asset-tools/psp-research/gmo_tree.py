"""Standalone GMO chunk walker: prints the tree, so the layout can be read without Blender.

GMO: 16-byte header "OMG.00.1PSP\\0", then chunks {u16 type, u16 header, u32 size}.
header is the byte offset from the chunk start to its payload; a chunk name sits at
chunk+16 when header > 16. 0x8000 in the type marks a leaf.
"""
import struct
import sys

CONTAINERS = (2, 3, 4, 5, 6, 8, 9, 0xa, 0xb)
NAMES = {
    2: "container", 3: "container/name", 4: "bone", 5: "bone/name", 6: "mesh",
    7: "array", 8: "material", 9: "material/name", 0xa: "texture", 0xb: "motion",
    0xc: "curve",
}


def walk(d, start, end):
    while start + 8 <= end:
        kind, header = struct.unpack_from("<HH", d, start)
        size = struct.unpack_from("<I", d, start + 4)[0]
        if size < 8 or start + size > end:
            yield kind, header, size, start, True
            return
        yield kind, header, size, start, False
        start += size


def name_of(d, at, header):
    if header > 16:
        return d[at + 16:at + header].split(b"\0", 1)[0].decode("ascii", "replace")
    return ""


def tree(d, start, end, depth=0, limit=3, out=None):
    for kind, header, size, at, bad in walk(d, start, end):
        tag = "%s%s" % (" " * depth, NAMES.get(kind, "?"))
        nm = name_of(d, at, header)
        out.append("%-28s type=0x%04x hdr=0x%02x size=%d at=0x%x%s %s"
                   % (tag, kind, header, size, at, " BAD" if bad else "", nm))
        if bad:
            return
        if kind == 7:
            if header >= 8:
                vt, count = struct.unpack_from("<II", d, at + header)
                out.append("%s   vtype=0x%x count=%d" % (" " * depth, vt, count))
        if kind == 0xc:
            fmt, dims, count = struct.unpack_from("<3I", d, at + header)
            out.append("%s   curve fmt=0x%x dims=%d keys=%d" % (" " * depth, fmt, dims, count))
        if kind == 0xb:
            out.append("%s   motion '%s'" % (" " * depth, nm))
        if kind in CONTAINERS and depth < limit:
            tree(d, at + header, at + size, depth + 2, limit, out)


def main():
    for rel in sys.argv[1:]:
        d = open(rel, "rb").read()
        out = ["==== %s (%d bytes) magic=%s" % (rel, len(d), d[:12])]
        tree(d, 0x10, len(d), 0, 4, out)
        print("\n".join(out))


if __name__ == "__main__":
    main()
