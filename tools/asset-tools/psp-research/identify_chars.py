"""Identify the PSP character numbers against the PC roster.

Two independent measurements:
  A. .atp row values against the PC .dat combat records.
     The plan measured  word0 == combat[0]/1000, word1 == combat[5]/100,
     word2 == combat[6]/100, and PC move id -> PSP row 300->107, 301->109,
     302->110, 310->112, 311->114, 320->163, 330->124, 331->126, 332->167,
     340->172, 341->174.
  B. shared weapon-model hashes: a PSP weapon GMO byte-identical to another
     character's names the same model, which cross-checks the numbering.

Run:  python3 identify_chars.py   (needs the local PC install for part A)
"""
import os
import struct
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
DUMP = os.path.normpath(os.path.join(HERE, "..", "dump"))
PC_DIR = "/home/marcelo/Projects/daybreak-remake/Higurashi-Daybreak/data"

PC_ORDER = ["rena", "mion", "keiichi", "satoko", "rika", "shion", "tomitake",
            "takano", "ohishi", "akasaka", "irie", "chie", "kasai", "akane",
            "hanyu", "natumi"]
PSP_W = "abcd"
KNOWN = {300: 107, 301: 109, 302: 110, 310: 112, 311: 114, 320: 163,
         330: 124, 331: 126, 332: 167, 340: 172, 341: 174}


def pc_records(path):
    """{move id: [(combat0, combat5, combat6), ...]} from a PC .dat, hit records only."""
    d = open(path, "rb").read()
    at = 0

    def u32():
        nonlocal at
        v = struct.unpack_from("<i", d, at)[0]
        at += 4
        return v

    u32()
    at += 0x104
    for _ in range(6):
        u32()
    moves = u32()
    out = {}
    for _ in range(moves):
        mid = u32()
        u32()
        u32()
        sections = u32()
        rows = out.setdefault(mid, [])
        for _s in range(sections):
            u32()
            entries = u32()
            for _e in range(entries):
                at += 30
                at += 4  # activeFrame
                at += 12  # anchor
                radius = struct.unpack_from("<i", d, at)[0]
                at += 4
                combat = list(struct.unpack_from("<20i", d, at))
                at += 80
                at += 12  # stateFlags, attackFlags, collisionShape
                at += 12  # endAnchor
                if radius != 0:
                    rows.append((combat[0], combat[5], combat[6]))
    return out


def atp_rows(path):
    """[(row, (w0*1000, w1*100, w2*100))] for the populated rows of a PSP .atp."""
    d = open(path, "rb").read()
    size, ver, size2, n = struct.unpack_from("<4I", d, 0)
    hdr = 0x10 if ver == 1 else 0x18
    rec = (len(d) - hdr) // n
    out = []
    for i in range(n):
        off = hdr + i * rec
        if not any(d[off:off + rec]):
            continue
        w = struct.unpack_from("<3f", d, off)
        out.append((i, (round(w[0] * 1000), round(w[1] * 100), round(w[2] * 100))))
    return out


def main():
    pc = {}
    for ci, name in enumerate(PC_ORDER):
        for slot in range(3):
            p = os.path.join(PC_DIR, name, "%02d.dat" % slot)
            if os.path.exists(p):
                pc[(ci, slot)] = pc_records(p)
    print("PC combos parsed:", len(pc))

    psp = {}
    for nn in range(1, 20):
        for w in PSP_W:
            p = os.path.join(DUMP, "assault", "chr%02d%s.atp" % (nn, w))
            if os.path.exists(p):
                psp[(nn, w)] = dict(atp_rows(p))
    print("PSP weapon tables:", len(psp))

    # A1: per-row agreement under the plan's known id map, which is what pins identity
    print("\n=== A. per-move agreement (plan's id map), PC char x PC slot vs PSP nn x letter ===")
    print("cells: matched / PSP rows with a known id, then PC triples of that move")
    best = {}
    for (ci, slot), moves in pc.items():
        row = []
        for nn in range(1, 20):
            for w in PSP_W:
                if (nn, w) not in psp:
                    continue
                hit = tot = 0
                for mid, prow in KNOWN.items():
                    if mid not in moves or prow not in psp[(nn, w)]:
                        continue
                    tot += 1
                    if psp[(nn, w)][prow] in moves[mid]:
                        hit += 1
                row.append((hit, tot, nn, w))
        row.sort(reverse=True)
        top = row[0]
        best[(ci, slot)] = top
        print("%-9s slot %d -> best chr%02d%s %d/%d ; next %s"
              % (PC_ORDER[ci], slot, top[2], top[3], top[0], top[1],
                 [(h, t, n, w) for h, t, n, w in row[1:3]]))

    print("\n=== B. per-character vote across weapon slots ===")
    votes = {}
    for (ci, slot), (hit, tot, nn, w) in best.items():
        votes.setdefault(ci, []).append(nn)
    for ci in range(16):
        v = votes.get(ci, [])
        print("%-9s -> PSP numbers voted %s" % (PC_ORDER[ci], v))

    # B2: best character number per PC character, summed over its weapon slots and
    # over every letter assignment for those slots. This is the identification table.
    import itertools
    print("\n=== B2. PSP number per PC character (sum of matched known-id rows) ===")
    for ci, cname in enumerate(PC_ORDER):
        slots = [s for s in range(3) if (ci, s) in pc]
        row = []
        for nn in range(1, 20):
            best = 0
            for perm in itertools.permutations(PSP_W, len(slots)):
                h = t = 0
                for slot, w in zip(slots, perm):
                    if (nn, w) not in psp:
                        continue
                    for mid, prow in KNOWN.items():
                        if mid in pc[(ci, slot)] and prow in psp[(nn, w)]:
                            t += 1
                            if psp[(nn, w)][prow] in pc[(ci, slot)][mid]:
                                h += 1
                best = max(best, h)
            row.append((best, nn))
        row.sort(reverse=True)
        print("%-9s -> %s" % (cname, row[:4]))

    # C: whole-set overlap, ignoring the id map (independent of the plan's mapping)
    print("\n=== C. triple-set overlap (no id map used) ===")
    for ci in range(16):
        sets = {s: set(t for rows in pc[(ci, s)].values() for t in rows) for s in range(3)
                if (ci, s) in pc}
        scored = []
        for nn in range(1, 20):
            tot = 0
            for slot, s in sets.items():
                cand = psp.get((nn, PSP_W[min(slot, 3)]))
                if not cand:
                    continue
                vals = set(cand.values())
                tot += len(s & vals) - 0.3 * len(vals - s)
            scored.append((tot, nn))
        scored.sort(reverse=True)
        print("%-9s -> %s" % (PC_ORDER[ci], scored[:4]))


if __name__ == "__main__":
    main()
