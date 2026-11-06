"""Inflate every payload of gzpack.pck, classify it by magic, and record sizes/hashes.

  all_files.tsv   hash \t csize \t offset \t usize \t magic \t sha256 \t signature

'signature' is the first printable ASCII run of the payload (GMO/GIM/pck name table),
which is what lets an unnamed file be matched to a family.
"""
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psppack import Pack, sha256

HERE = os.path.dirname(os.path.abspath(__file__))
NOTES = os.path.normpath(os.path.join(HERE, "..", "notes"))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))

MAGICS = [
    (b"OMG.00.1", "GMO"),
    (b"MIG.00.1PSP", "GIM"),
    (b"MIG.00.1", "GIM"),
    (b"\x1f\x8b", "gzip"),
]


def classify(data):
    for m, name in MAGICS:
        if data[:len(m)] == m:
            return name
    # audio / container heuristics
    if len(data) >= 16:
        n = int.from_bytes(data[:4], "little")
        if 0 < n < 100000 and len(data) > 16 and n * 16 + 4 <= len(data) + 64:
            return "table?"  # .acs/.acv style
        if data[:4] == b"VAGp" or data[:4] == b"VAGi":
            return "VAG"
    if data[:3] == b"\x00\x00\x02" or data[:4] == b"PSMF":
        return "psmf?"
    for m, name in ((b"\x00\x00\x02\x00", "TGA?"), (b"\x89PNG", "PNG")):
        if data[:len(m)] == m:
            return name
    return "?"


def signature(data, limit=64):
    runs = re.findall(rb"[\x20-\x7e]{4,}", data[:4096])
    s = "|".join(r.decode("ascii") for r in runs[:6])
    return s.replace("\t", " ")[:limit]


def main():
    pack = Pack()
    os.makedirs(DUMP, exist_ok=True)
    out = []
    for i, h in enumerate(pack.hashes):
        cs, off, unk = pack.rows[h]
        pack.f.seek(__import__("psppack").BASE + off)
        raw = pack.f.read(cs)
        try:
            data = __import__("gzip").decompress(raw) if raw[:2] == b"\x1f\x8b" else raw
        except Exception as e:  # noqa: BLE001
            data = b""
        out.append((h, cs, off, len(data), classify(data), sha256(data), signature(data)))
    with open(os.path.join(NOTES, "all_files.tsv"), "w") as f:
        f.write("hash\tcsize\toffset\tusize\tmagic\tsha256\tsignature\n")
        for h, cs, off, us, mg, sh, sg in out:
            f.write("%08x\t%d\t%d\t%d\t%s\t%s\t%s\n" % (h, cs, off, us, mg, sh, sg))
    from collections import Counter
    print(Counter(x[4] for x in out))
    print("total inflated bytes:", sum(x[3] for x in out))


if __name__ == "__main__":
    main()
