"""Parser for activity/chrNNx.acs (PSP moveset script container).

Layout (observed, matches parser FUN_0005d5d4):
  +0  u32 ?       (header 0)
  +4  u32 ?       (header 1)
  +8  block1: u32 size, u32 ?, then `size` bytes payload
      payload = 350 entries { u32 stride, u32 count, count * 8 bytes }
      -> Fighter+0x3b4 + 8*row = {count, ptr} per-row event script
      next block starts at (block1_start + size)
  ... block2 same shape -> Fighter+0x1994 + 8*row
  ... block3: variable entries, parsed by FUN_0007d288 / FUN_0007d034 into Fighter+0x2604
  ... block4: u32 size, u32 ?, payload = 350 u32 handler indices -> Fighter+0x25e0
"""
import struct

class Acs:
    def __init__(self, path):
        self.b = open(path, "rb").read()
        self.h = struct.unpack_from("<2I", self.b, 0)
        p = 8
        self.blocks = []
        self.blk1, p = self.parse_list(p)
        self.end = p
        self.blk2 = self.blk3 = self.handlers = None

    def parse_list(self, p):
        n = struct.unpack_from("<I", self.b, p)[0]
        base = p + 8
        entries, q = [], base
        for i in range(350):
            stride, count = struct.unpack_from("<2I", self.b, q)
            ev = []
            for k in range(count):
                t, c = struct.unpack_from("<fI", self.b, q + 8 + k * 8)
                ev.append((t, c))
            entries.append(ev)
            q += stride
        return entries, p + n

if __name__ == "__main__":
    import sys
    a = Acs(sys.argv[1])
    print("hdr", [hex(x) for x in a.h], "blk3@%#x len %d" % (a.blk3_off, len(a.blk3)), "blk4@%#x end %#x size %d" % (a.blk4_off, a.end, len(a.b)))
    import collections
    print("handlers:", collections.Counter(a.handlers).most_common(8))
    rows_with = [(i, e) for i, e in enumerate(a.blk1) if e]
    print("rows with events (blk1):", len(rows_with))
    for i, e in rows_with[:20]:
        print(" row %3d h=%3d : %s" % (i, a.handlers[i], " ".join("%.3f:%08x" % x for x in e)))
