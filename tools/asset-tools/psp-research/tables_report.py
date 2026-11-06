"""Structural reading of the PSP moveset tables: .acs, .acv, .atp.

Verified layouts (see formats.md):
  .acs / .atp / .acv share an outer header {u32 bytes, u32 version, u32 ?, u32 n_sections}
  .acs: n_sections == 350, one section per move row, each {u32 row_bytes, u32 items, item[items]}
        item = {f32 time, u32 code}; row_bytes = 8 + 8*items
  .atp: n_sections == 350, then 350 fixed 148-byte records (no per-row header)
  .acv: n_sections == 4, each section {u32 bytes, u32 rows}, each row {u32 bytes, u32 items, payload}
"""
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))


def header(d):
    return struct.unpack_from("<4I", d, 0)


def parse_acs(d):
    size, ver, size2, n = header(d)
    rows, at = [], 0x10
    for _ in range(n):
        rb, cnt = struct.unpack_from("<2I", d, at)
        items = [struct.unpack_from("<fI", d, at + 8 + 8 * i) for i in range(cnt)]
        rows.append((rb, cnt, items))
        at += rb
    return ver, rows, at


def parse_acv(d):
    size, ver, size2, n = header(d)
    if ver != 1:
        return ver, [], 0
    secs, at = [], 0x10
    for _ in range(n):
        sb, srows = struct.unpack_from("<2I", d, at)
        rows, q = [], at + 8
        for _ in range(srows):
            rb, cnt = struct.unpack_from("<2I", d, q)
            rows.append((q, rb, cnt))
            q += rb
        secs.append((at, sb, srows, rows, q))
        at += sb
    return ver, secs, at


def parse_atp(d):
    """Header word 3 is the record count; the record size follows from the file size."""
    size, ver, size2, n = header(d)
    hdrlen = 0x10 if ver == 1 else 0x18
    rec = (len(d) - hdrlen) // n
    assert rec * n + hdrlen == len(d), (len(d), n, rec)
    return ver, n, rec, [struct.unpack_from("<%dI" % (rec // 4), d, hdrlen + i * rec)
                         for i in range(n)]


def acs_codes(paths):
    from collections import Counter
    fam = Counter()
    for p in paths:
        _, rows, _ = parse_acs(open(p, "rb").read())
        for _, cnt, items in rows:
            for _t, code in items:
                fam[code] += 1
    return fam


def main():
    chrs = list(range(1, 20))
    weapons = "abcd"
    print("=== .acs header + populated rows ===")
    acs_pop = {}
    for nn in chrs:
        for w in weapons:
            p = os.path.join(DUMP, "activity", "chr%02d%s.acs" % (nn, w))
            if not os.path.exists(p):
                continue
            d = open(p, "rb").read()
            ver, rows, end = parse_acs(d)
            pop = [i for i, (rb, cnt, it) in enumerate(rows) if cnt]
            acs_pop["%02d%s" % (nn, w)] = set(pop)
            print("chr%02d%s ver=%d size=%d end=0x%x rows=%d populated=%d"
                  % (nn, w, ver, len(d), end, len(rows), len(pop)))
    common = set.intersection(*acs_pop.values())
    print("\n.acs rows populated in every combo (%d):" % len(common), sorted(common))
    union = set.union(*acs_pop.values())
    print(".acs rows populated somewhere (%d):" % len(union), sorted(union))
    for nn in (17, 18, 19):
        for w in weapons:
            k = "%02d%s" % (nn, w)
            if k in acs_pop:
                only = sorted(acs_pop[k] - common)
                print("chr%s rows beyond the common set (%d): %s" % (k, len(only), only))

    print("\n=== .atp ===")
    atp_nonzero = {}
    for nn in chrs:
        for w in weapons:
            p = os.path.join(DUMP, "assault", "chr%02d%s.atp" % (nn, w))
            if not os.path.exists(p):
                continue
            d = open(p, "rb").read()
            ver, n, rec, recs = parse_atp(d)
            nz = [i for i, r in enumerate(recs) if any(r)]
            atp_nonzero["%02d%s" % (nn, w)] = set(nz)
            print("chr%02d%s ver=%d size=%d rows=%d rec=%d populated=%d first=%s"
                  % (nn, w, ver, len(d), n, rec, len(nz), nz[:8]))
    common = set.intersection(*atp_nonzero.values())
    print(".atp rows populated in every combo:", sorted(common))
    union = set.union(*atp_nonzero.values())
    print(".atp rows populated somewhere (%d):" % len(union), sorted(union))
    for nn in (17, 18, 19):
        for w in weapons:
            k = "%02d%s" % (nn, w)
            if k in atp_nonzero:
                print("chr%s beyond common: %s" % (k, sorted(atp_nonzero[k] - common)))

    print("\n=== .acv ===")
    for nn in chrs:
        for w in weapons:
            p = os.path.join(DUMP, "activity", "chr%02d%s.acv" % (nn, w))
            if not os.path.exists(p):
                continue
            d = open(p, "rb").read()
            ver, secs, end = parse_acv(d)
            if ver != 1:
                print("chr%02d%s ver=%d sections=%d end=0x%x (non-v1, skipped)"
                      % (nn, w, ver, len(secs), end))
                continue
            desc = []
            for at, sb, srows, rows, q in secs:
                nzr = sum(1 for (_q, rb, cnt) in rows if cnt)
                items = sorted({(rb - 8) // cnt if cnt else 0 for (_q, rb, cnt) in rows})
                desc.append("sec@0x%x(%dB,%d rows,%d used,itemsz=%s)" % (at, sb, srows, nzr, items))
            print("chr%02d%s ver=%d end=0x%x/%d  %s" % (nn, w, ver, end, len(d), " ".join(desc)))

    print("\n=== .acs code families ===")
    paths = []
    for nn in chrs:
        for w in weapons:
            p = os.path.join(DUMP, "activity", "chr%02d%s.acs" % (nn, w))
            if os.path.exists(p):
                paths.append(p)
    fam = acs_codes(paths)
    for code, n in sorted(fam.items()):
        print("  %08x  %6d" % (code, n))


if __name__ == "__main__":
    main()
