"""Parser for activity/chrNNx.acv  (Fighter row table container).

Layout (observed; matches FUN_0005d5d4 / FUN_00063634):
  +0x00 u32 total_size
  +0x04 u32 version (1)
  +0x08 .. series of sections, each { u32 size_incl_8hdr, u32 count, payload }
    S1 350 entries variable stride  -> Fighter+0x3b4+8*row  {count, ptr to (f32 time,u32 code)?}
    S2 350 entries variable stride  -> Fighter+0x1994+8*row
    S3 count entries (usually 2)    -> FUN_0007d288/FUN_0007d034 into Fighter+0x2604
    S4 350 u32                      -> Fighter+0x25e0 : row -> handler index (0x1b08f4)
"""
import struct

class Acv:
    def __init__(self, path):
        self.b = b = open(path, "rb").read()
        self.total, self.ver = struct.unpack_from("<2I", b, 0)
        secs, p = [], 0x10
        while p + 8 <= len(b):
            size, cnt = struct.unpack_from("<2I", b, p)
            if size < 8 or p + size > len(b):
                break
            secs.append((p, size, cnt))
            p += size
        self.secs = secs
        # S1 / S2: variable-stride entry lists
        self.s1 = self.list(0)
        self.s2 = self.list(1)
        p3, sz3, c3 = secs[2]
        self.s3_off, self.s3_cnt, self.s3 = p3, c3, b[p3 + 8:p3 + sz3]
        p4, sz4, c4 = secs[3]
        self.handlers = list(struct.unpack_from("<%dI" % c4, b, p4 + 8))

    def entries(self, idx):
        p, size, cnt = self.secs[idx]
        q, end, out = p + 8, p + size, []
        while q < end and len(out) < cnt:
            stride, n = struct.unpack_from("<2I", self.b, q)
            if stride < 8:
                break
            out.append((q, stride, n))
            q += stride
        return out

    def list(self, idx):
        """[(row, raw bytes of entry)]"""
        out = []
        for row, (q, stride, n) in enumerate(self.entries(idx)):
            out.append((row, self.b[q:q + stride]))
        return out

if __name__ == "__main__":
    import sys
    a = Acv(sys.argv[1])
    print("total", a.total, "ver", a.ver, "secs", [(hex(p), s, c) for p, s, c in a.secs])
    e1 = [x for x in a.entries(0)]
    print("S1: %d entries, strides %s" % (len(e1), sorted(set(s for _, s, _ in e1))))
    e2 = [x for x in a.entries(1)]
    print("S2: %d entries, strides %s" % (len(e2), sorted(set(s for _, s, _ in e2))))
    print("S3: %d entries, %d bytes" % (a.s3_cnt, len(a.s3)))
    print("S4 handlers:", a.handlers[:24], "...")
    import collections
    print("S4 distinct:", len(set(a.handlers)), "min", min(a.handlers), "max", max(a.handlers))
    print("S4 first 40:", a.handlers[:40])
