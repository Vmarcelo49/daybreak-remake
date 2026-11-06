"""Fetch a file from the ISO pack into local-data/harness/psp/dump/<path with _>."""
import os, sys, eboot  # noqa
import psppack

HERE = os.path.dirname(os.path.abspath(__file__))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))

def get(path, out=None):
    p = psppack.Pack()
    blob = p.get(path)
    if blob is None:
        raise SystemExit("not in pack: " + path)
    os.makedirs(DUMP, exist_ok=True)
    out = out or os.path.join(DUMP, path.replace("/", "_"))
    open(out, "wb").write(blob)
    return out, len(blob)

if __name__ == "__main__":
    for path in sys.argv[1:]:
        o, n = get(path)
        print("%-40s %8d  %s" % (path, n, o))
