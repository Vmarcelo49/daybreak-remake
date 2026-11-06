"""Grep decomp for calls to a function, print call site + args snippet."""
import os, re, sys, eboot as e

def scan(fnname, pat=None):
    out = []
    for a, n, s in e.index():
        p = os.path.join(e.DECOMP, "%08x.c" % a)
        if not os.path.exists(p):
            continue
        txt = open(p, encoding="utf-8", errors="replace").read()
        if fnname not in txt:
            continue
        for i, line in enumerate(txt.splitlines(), 1):
            if fnname in line:
                out.append((a, i, line.strip()))
    return out

if __name__ == "__main__":
    fn = sys.argv[1]
    for a, i, line in scan(fn):
        print("%08x:%-4d %s" % (a, i, line[:220]))
