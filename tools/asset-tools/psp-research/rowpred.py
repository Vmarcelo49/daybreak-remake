"""Find functions that classify a row id: bitmask tests and switch tables."""
import re, os, eboot as e

def rowsets(txt):
    """Extract row sets from common Ghidra patterns."""
    out = set()
    # pattern A: (param - 0xNNU < 0xMM) && ((1 << ... & 0xMASK) != 0)
    for m in re.finditer(r"\((\w+) - (0x[0-9a-f]+)U < (0x[0-9a-f]+)\)[^\n]*?& (0x[0-9a-f]+)U\)", txt):
        base = int(m.group(2), 16); mask = int(m.group(4), 16)
        for b in range(32):
            if mask >> b & 1:
                out.add(base + b)
    # pattern B: (param_2 < 9) && ((1 << (param_2 & 0x1f) & 0x150U) != 0)
    for m in re.finditer(r"\((\w+) < (\d+)\)[^\n]*?& (0x[0-9a-f]+)U\)", txt):
        mask = int(m.group(3), 16)
        for b in range(32):
            if mask >> b & 1:
                out.add(b)
    # pattern C: switch cases
    cases = [int(c, 16) for c in re.findall(r"^  case (0x[0-9a-f]+):$", txt, re.M)]
    return out | set(cases)

if __name__ == "__main__":
    lo, hi = 0x7c000, 0x89000
    for a, n, s in e.index():
        if not (lo <= a < hi):
            continue
        p = os.path.join(e.DECOMP, "%08x.c" % a)
        if not os.path.exists(p):
            continue
        t = open(p, encoding="utf-8", errors="replace").read()
        if len(t.splitlines()) > 40:
            continue
        rs = rowsets(t)
        rs = {r for r in rs if r < 0x15e}
        if len(rs) >= 2:
            print("%08x sz=%-4d n=%-3d %s" % (a, s, len(rs), sorted(rs)))
