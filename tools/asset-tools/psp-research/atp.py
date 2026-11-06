"""Parser for assault/chrNNx.atp : container {u32 total, u32 ver, u32 payload, u32 count}
then count * 0x94-byte row records (Fighter+0x25e4)."""
import struct

REC = 0x94

class Atp:
    def __init__(self, path):
        self.b = open(path, "rb").read()
        self.total, self.ver, self.payload, self.count = struct.unpack_from("<4I", self.b, 0)
        self.base = 0x10
    def rec(self, row):
        return self.b[self.base + row * REC: self.base + (row + 1) * REC]
    def ok(self, row):
        return self.base + (row + 1) * REC <= len(self.b)
    def u32s(self, row):
        if not self.ok(row):
            return (0,) * (REC // 4)
        return struct.unpack_from("<%dI" % (REC // 4), self.b, self.base + row * REC)
    def floats(self, row):
        if not self.ok(row):
            return (0.0,) * (REC // 4)
        return struct.unpack_from("<%df" % (REC // 4), self.b, self.base + row * REC)

if __name__ == "__main__":
    import sys
    a = Atp(sys.argv[1])
    print("total %d ver %d payload %d count %d" % (a.total, a.ver, a.payload, a.count))
    lo = int(sys.argv[2]) if len(sys.argv) > 2 else 100
    hi = int(sys.argv[3]) if len(sys.argv) > 3 else 120
    for r in range(lo, hi):
        w = a.u32s(r)
        f = a.floats(r)
        print("row %3d: %s" % (r, " ".join("%08x" % x for x in w)))
        print("        f: %s" % " ".join(("%.3g" % x) for x in f))
