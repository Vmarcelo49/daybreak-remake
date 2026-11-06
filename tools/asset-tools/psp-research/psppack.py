"""Reader for the Higurashi Daybreak Portable gzpack.pck inside the ISO.

Layout (verified):
  base = LBA_of_gzpack.pck * 2048
  u32 count, then count * 16-byte rows {u32 name_hash, u32 csize, u32 offset, u32 unk}
  offset is relative to pack start, payload is a gzip stream.

name_hash = zlib.crc32(path_bytes, 0xFFFFFFFF), path written WITHOUT a leading slash.
"""
import gzip
import hashlib
import os
import struct
import zlib

ISO = "/mnt/disco2/Roms/PSP/Higurashi_Daybrake_Portable_Mega_Edition_JPN_PSP-Caravan.iso"
PACK_LBA = 72848
PACK_SIZE = 326807872
BASE = PACK_LBA * 2048


def crc(path):
    return zlib.crc32(path.encode("ascii"), 0xFFFFFFFF)


class Pack:
    def __init__(self, iso=ISO):
        self.f = open(iso, "rb")
        self.f.seek(BASE)
        n = struct.unpack("<I", self.f.read(4))[0]
        self.count = n
        blob = self.f.read(n * 16)
        self.rows = {}
        for i in range(n):
            h, cs, off, unk = struct.unpack_from("<4I", blob, i * 16)
            self.rows[h] = (cs, off, unk)
        # order in file (sorted by hash?) for sanity checks
        self.hashes = [struct.unpack_from("<I", blob, i * 16)[0] for i in range(n)]

    def has(self, path):
        return crc(path) in self.rows

    def raw(self, path):
        h = crc(path)
        r = self.rows.get(h)
        if r is None:
            return None
        cs, off, _unk = r
        self.f.seek(BASE + off)
        return self.f.read(cs)

    def head(self, offset, n):
        self.f.seek(BASE + offset)
        return self.f.read(n)

    def get(self, path):
        """Return the inflated payload, or None when the path is not in the pack."""
        blob = self.raw(path)
        if blob is None:
            return None
        if blob[:2] == b"\x1f\x8b":
            return gzip.decompress(blob)
        return blob


def sha256(data):
    return hashlib.sha256(data).hexdigest()


if __name__ == "__main__":
    p = Pack()
    print("count", p.count, "unique hashes", len(p.rows))
    for path in ("g3d/chrm19.gmo", "activity/chr19a.acs", "g3d/chr190.gmo"):
        d = p.get(path)
        print(path, "MISSING" if d is None else (len(d), d[:8].hex(), sha256(d)[:16]))
    del os
