"""Dump the binary .X token stream, so a GMO->.X writer can mirror the shipped layout exactly.

Not part of the product: a reading aid. Usage:
    python3 xdump.py <file.X> [--frames] [--object Mesh] [--limit N]
"""
import struct
import sys

NAMES = {1: "NAME", 2: "STRING", 3: "INT", 5: "GUID", 6: "INT_LIST", 7: "FLOAT_LIST",
         10: "OBRACE", 11: "CBRACE", 12: "OPAREN", 13: "CPAREN", 14: "OBRACKET",
         15: "CBRACKET", 19: "COMMA", 20: "SEMI", 31: "TEMPLATE"}
for i, n in enumerate(["WORD", "DWORD", "FLOAT", "DOUBLE", "CHAR", "UCHAR", "SWORD",
                       "SDWORD", "VOID", "STRING_T", "UNICODE", "CSTRING", "ARRAY"]):
    NAMES[40 + i] = n


def tokens(d):
    at = 16
    fw = 8 if d[12:16] == b"0064" else 4
    while at < len(d):
        kind = struct.unpack_from("<H", d, at)[0]
        at += 2
        val = None
        if kind in (1, 2):
            n = struct.unpack_from("<I", d, at)[0]
            at += 4
            val = d[at:at + n]
            at += n
        elif kind == 3:
            val = struct.unpack_from("<I", d, at)[0]
            at += 4
        elif kind == 5:
            val = d[at:at + 16]
            at += 16
        elif kind in (6, 7):
            n = struct.unpack_from("<I", d, at)[0]
            at += 4
            fmt = "<%d%s" % (n, "f" if kind == 7 else "i")
            val = struct.unpack_from(fmt, d, at) if n else ()
            at += n * (fw if kind == 7 else 4)
        yield kind, val


def main():
    path = sys.argv[1]
    want = None
    limit = 3
    show_frames = "--frames" in sys.argv
    for i, a in enumerate(sys.argv):
        if a == "--object":
            want = sys.argv[i + 1]
        if a == "--limit":
            limit = int(sys.argv[i + 1])
    d = open(path, "rb").read()
    print("header", d[:16], "bytes", len(d))
    toks = list(tokens(d))
    print("tokens", len(toks))
    depth = 0
    obj = None
    shown = 0
    pending = []
    in_template = False
    for kind, val in toks:
        name = NAMES.get(kind, str(kind))
        if kind == 31 and depth == 0:
            in_template = True
            continue
        if in_template:
            if kind == 10:
                depth += 1
            elif kind == 11:
                depth -= 1
                if depth == 0:
                    in_template = False
            continue
        if kind == 1 and depth == 0:
            pending = [val.decode("ascii", "replace")]
            continue
        if kind == 10:
            if pending and obj is None:
                obj = pending[0]
                pending = []
                if want is None or obj == want:
                    shown += 1
                    print("\n== %s (depth %d) shown %d" % (obj, depth, shown))
            else:
                print("  " * depth + "{")
            depth += 1
            continue
        if kind == 11:
            depth -= 1
            continue
        if depth == 0:
            continue
        line = "  " * depth + name
        if val is not None:
            if isinstance(val, bytes):
                line += " " + repr(val[:40])
            elif isinstance(val, tuple):
                line += " n=%d %s" % (len(val), str(val[:8]) + (" ..." if len(val) > 8 else ""))
            elif kind == 1:
                line += " " + repr(val)
            else:
                line += " " + str(val)
        print(line)
        if shown > limit:
            break


if __name__ == "__main__":
    main()
