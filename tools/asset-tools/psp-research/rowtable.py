"""Build the row table: row -> handler id/fn/class, .acs events, .acv S1 program,
.acv S2 record count, .atp record fields.  Writes notes/rowtable.tsv."""
import os, re, struct, sys
import eboot as e, acs as A, acv as V, atp as P

HAND = 0x1b08f4
_c = {}

def handler(i):
    if i >= 479:
        return (0, 0, False, "OOB:%d" % i)
    if i not in _c:
        fn, fl = e.u32(HAND + i * 8), e.u32(HAND + i * 8 + 4)
        p = os.path.join(e.DECOMP, "%08x.c" % fn)
        txt = open(p, encoding="utf-8", errors="replace").read() if os.path.exists(p) else ""
        m = re.search(r"FUN_00077cd8\(([^;]*)\);", txt)
        _c[i] = (fn, fl, bool(m), (m.group(1) if m else ""))
    return _c[i]

def dump(char, wp):
    a = A.Acs("../dump/activity_chr%s%s.acs" % (char, wp))
    v = V.Acv("../dump/activity_chr%s%s.acv" % (char, wp))
    t = P.Atp("../dump/assault_chr%s%s.atp" % (char, wp))
    out = []
    e1, e2 = v.entries(0), v.entries(1)
    for row in range(350):
        h = v.handlers[row] if row < len(v.handlers) else 0xffffffff
        fn, gen, args = 0, False, ""
        if h != 0xffffffff:
            fn, fl, gen, args = handler(h)
        if row < len(e1):
            q, stride, n = e1[row]
            s1 = " ".join("%g:%08x" % struct.unpack_from("<fI", v.b, q + 8 + 8 * k) for k in range(n))
            n2 = e2[row][2]
        else:
            s1, n2 = "", 0
        w = t.u32s(row)
        out.append(dict(row=row, hid=h, fn=fn, gen=gen, args=args,
                        acs=" ".join("%g:%08x" % x for x in a.blk1[row]),
                        acv=s1, s2=n2, w=w, f=t.floats(row)))
    return out

def tsv(path):
    with open(path, "w") as f:
        f.write("weapon\trow\thandler_id\thandler_fn\tclass\tgeneric_args\tmotion\ts2_recs\t"
                "atp_pow\tatp_a\tatp_b\tatp_w5\tatp_w6\tatp_7\tatp_8\tatp_9\tatp_e0\tacs\tacv_s1\n")
        for c in ("01", "16", "17", "18", "19"):
            for wp in "abcd":
                p = "../dump/activity_chr%s%s.acs" % (c, wp)
                if not os.path.exists(p):
                    continue
                for r in dump(c, wp):
                    f.write("\t".join(str(x) for x in (
                        c + wp, r["row"], r["hid"] if r["hid"] != 0xffffffff else -1,
                        "%08x" % r["fn"] if r["fn"] else "-", "gen" if r["gen"] else ("-" if not r["fn"] else "spec"),
                        r["args"].replace("\t", " "), r["w"][35], r["s2"],
                        "%.4g" % r["f"][0], "%.4g" % r["f"][1], "%.4g" % r["f"][2],
                        "%08x" % r["w"][5], r["w"][6], "%.4g" % r["f"][7], "%.4g" % r["f"][8],
                        "%08x" % r["w"][9], "%d" % r["w"][34], r["acs"], r["acv"])) + "\n")
    print("wrote", path)

if __name__ == "__main__":
    tsv("../notes/rowtable.tsv")
    # summary
    for c in ("01", "16", "17", "18", "19"):
        for wp in "abcd":
            if not os.path.exists("../dump/activity_chr%s%s.acs" % (c, wp)):
                continue
            d = dump(c, wp)
            v = [r for r in d if r["hid"] != 0xffffffff]
            g = [r for r in v if r["gen"]]
            spec = [r for r in v if not r["gen"]]
            print("chr%s%s: valid %3d  generic %3d  specialized %3d" % (c, wp, len(v), len(g), len(spec)))
    if (len(sys.argv) > 1):
        c, wp = sys.argv[1], sys.argv[2]
        lo, hi = int(sys.argv[3]), int(sys.argv[4])
        for r in dump(c, wp)[lo:hi]:
            print("%3d h=%-3d %-8s %-5s mot=%-4d s2=%-2d pow=%-5.3g w5=%08x w6=%-3d w7=%-5.3g w8=%-5.3g w9=%08x | acs=%s | acv=%s"
                  % (r["row"], r["hid"], "%08x" % r["fn"] if r["fn"] else "-",
                     "gen" if r["gen"] else "SPEC", r["w"][35], r["s2"],
                     r["f"][0], r["w"][5], r["w"][6], r["f"][7], r["f"][8], r["w"][9],
                     r["acs"][:26], r["acv"][:26]))
