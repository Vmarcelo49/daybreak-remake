"""Dump the 350-entry row handler table at 0x1b08f4 and group by handler."""
import collections, eboot as e

TBL = 0x1b08f4
N = 0x15e  # 350

rows = []
for i in range(N):
    fn = e.u32(TBL + i * 8)
    fl = e.u32(TBL + i * 8 + 4)
    rows.append((i, fn, fl))

by = collections.OrderedDict()
for i, fn, fl in rows:
    by.setdefault(fn, []).append((i, fl))

print("distinct handlers:", len(by))
GEN = 0x77cd8
gen = by.get(GEN, [])
print("generic FUN_00077cd8 rows: %d" % len(gen))
print()
print("=== handlers, sorted by address; rows that use them ===")
def rng(lst):
    out, s, p = [], None, None
    for i, _ in lst:
        if s is None: s = p = i
        elif i == p + 1: p = i
        else: out.append((s, p)); s = p = i
    if s is not None: out.append((s, p))
    return " ".join(("%d" % a) if a == b else ("%d-%d" % (a, b)) for a, b in out)

for fn in sorted(by):
    lst = by[fn]
    idx = e.func_at(fn)
    sz = idx[2] if idx else -1
    fl = set(f for _, f in lst)
    print("%08x sz=%-5d n=%-3d flags=%s :: %s" % (fn, sz, len(lst), sorted(hex(x) for x in fl), rng(lst)))
