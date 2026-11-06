"""Inventory of the .pck containers (activity/chrNNx_voice.pck, _se.pck, _eff.pck).

Layout (verified on chr19a's three and chr00a_se):
  u32 count
  count x {u32 id, u32 payload_bytes, u32 file_offset}
  a NUL-padded name table (the source paths), then the payloads, back to back.
  _voice/_se payloads are VAG streams ("VAGp"), _eff payloads are GMO effect models.
"""
import os
import re
import struct
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from psppack import Pack  # noqa: E402

HERE = os.path.dirname(os.path.abspath(__file__))
NOTES = os.path.normpath(os.path.join(HERE, "..", "notes"))


def parse_pck(d):
    n = struct.unpack_from("<I", d, 0)[0]
    if n == 0 or 4 + 12 * n > len(d):
        return None
    rows = [struct.unpack_from("<3I", d, 4 + 12 * i) for i in range(n)]
    table_end = 4 + 12 * n
    first = min(r[2] for r in rows)
    if not (table_end <= first <= len(d)):
        return None
    names = [s.decode("ascii", "replace")
             for s in re.findall(rb"[ -~]{4,}", d[table_end:first])]
    return {"count": n, "rows": rows, "table_end": table_end, "first": first,
            "names": names, "ids": [r[0] for r in rows],
            "sizes": [r[1] for r in rows], "offsets": sorted({r[2] for r in rows})}


def main():
    pack = Pack()
    out = []
    for line in open(os.path.join(NOTES, "resolved.tsv")).read().splitlines()[1:]:
        path, family, csize, usize, sha = line.split("\t")
        if not path.endswith(".pck"):
            continue
        data = pack.get(path)
        p = parse_pck(data)
        if p is None:
            out.append("%-34s NOT A PCK" % path)
            continue
        ids = p["ids"]
        out.append("%-34s %7dB entries=%-4d ids=%d..%d unique_ids=%d payloads=%d "
                   "first_payload=%d"
                   % (path, len(data), p["count"], min(ids), max(ids), len(set(ids)),
                      len(p["offsets"]), p["first"]))
        blocks = p["offsets"] + [len(data)]
        sizes = [blocks[i + 1] - blocks[i] for i in range(len(blocks) - 1)]
        vag = sum(data[o:o + 4] == b"VAGp" for o in p["offsets"])
        gmo = sum(data[o:o + 8] == b"OMG.00.1" for o in p["offsets"])
        out.append("    payload kinds: VAG=%d GMO=%d other=%d ; block sizes %s"
                   % (vag, gmo, len(p["offsets"]) - vag - gmo, sizes[:6]))
        out.append("    names (%d): %s" % (len(p["names"]), ", ".join(p["names"][:8])))
    text = "\n".join(out)
    with open(os.path.join(NOTES, "pck_report.txt"), "w") as f:
        f.write(text + "\n")
    print(text[:4000])


if __name__ == "__main__":
    main()
