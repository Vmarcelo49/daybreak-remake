"""Collect all .acs/.acv event codes across every weapon file, and their per-family stats."""
import collections, os, struct, sys
import psppack

CHARS = ["%02d" % i for i in range(1, 20)]
WP = "abcd"

def all_files():
    for c in CHARS:
        for w in WP:
            yield c, w, "activity/chr%s%s.acs" % (c, w)
            yield c, w, "activity/chr%s%s.acv" % (c, w)

def lists_from_acs(b):
    """350 (count, [..]) lists, entries (f32 time, u32 code)."""
    n = struct.unpack_from("<I", b, 8)[0]
    q, end = 0x10, 8 + n
    out = []
    while q < end and len(out) < 350:
        stride, cnt = struct.unpack_from("<2I", b, q)
        ev = [struct.unpack_from("<fI", b, q + 8 + 8 * k) for k in range(cnt)]
        out.append(ev)
        q += stride
    return out

def lists_from_acv(b):
    n = struct.unpack_from("<I", b, 0x10)[0]
    q, end = 0x18, 0x10 + n
    out = []
    while q < end and len(out) < 350:
        stride, cnt = struct.unpack_from("<2I", b, q)
        ev = [struct.unpack_from("<fI", b, q + 8 + 8 * k) for k in range(cnt)]
        out.append(ev)
        q += stride
    return out

if __name__ == "__main__":
    p = psppack.Pack()
    codes = collections.Counter()
    times = collections.Counter()
    per = {}
    for c, w, path in all_files():
        b = p.get(path)
        if b is None:
            continue
        lst = lists_from_acs(b) if path.endswith(".acs") else lists_from_acv(b)
        for row, ev in enumerate(lst):
            for t, code in ev:
                codes[code] += 1
        per[(c, w, path.split(".")[-1])] = lst
    print("distinct codes:", len(codes))
    fam = collections.Counter((code & 0x7fffffff) >> 24 for code in codes)
    print("families by bits30..24:", sorted(fam.items()))
    for code, n in sorted(codes.items()):
        print("%08x  x%-4d fam=%2d" % (code, n, (code & 0x7fffffff) >> 24))
