"""Is the same take index the same move on different PSP characters?

    python3 index_agreement.py [--mode pos|angle] [--samples 12]

Uses `takecore` (the rig-agnostic signature the earlier study built: joint positions in a
frame taken from the hips, scaled by hips->neck, so bone roll, rest pose and body size
drop out) and asks, for every take index, whether the four rigs' takes at that index are
closer to each other than to any other index.

Writes notes/take_index_agreement_psp.tsv and prints a summary. The number it produces is
the honest version of "the same index tends to be the same move": a per-index verdict,
not an average that hides the disagreements.
"""
import argparse
import itertools
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import takecore as T  # noqa: E402

DUMP = os.path.normpath(os.path.join(HERE, "..", "dump", "g3d"))
NOTES = os.path.normpath(os.path.join(HERE, "..", "notes"))
RIGS = ["chrm17", "chrm18", "chrm19", "chrm02"]


def load():
    out = {}
    for rig in RIGS:
        path = os.path.join(DUMP, rig + ".gmo")
        out[rig] = T.load_psp(path)
    return out


def signature(rig, clip, mode, samples):
    return rig.signature(clip, mode, samples)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--mode", default="pos")
    ap.add_argument("--samples", type=int, default=12)
    a = ap.parse_args()
    rigs = load()
    sigs = {}
    for rig, r in rigs.items():
        for clip in r.clips:
            if not clip["tracks"]:
                continue
            if a.mode == "pos":
                s = r.pos_signature(clip, a.samples, "psp")
            else:
                s = r.signature(clip, a.mode, a.samples)
            sigs[(rig, clip["index"])] = s
    rows = []
    for index in range(76):
        present = [rig for rig in RIGS if (rig, index) in sigs]
        if len(present) < 2:
            continue
        ds = []
        for x, y in itertools.combinations(present, 2):
            ds.append((T.distance(sigs[(x, index)], sigs[(y, index)], a.samples), x, y))
        mean = sum(d for d, _, _ in ds) / len(ds)
        rows.append((index, len(present), mean, min(ds)))
    # For each rig pair and index, rank the same index against all other indices.
    ranks = []
    for x, y in itertools.combinations(RIGS, 2):
        common = [i for i in range(76) if (x, i) in sigs and (y, i) in sigs]
        for index in common:
            best, best_at = 1e9, None
            for other in common:
                d = T.distance(sigs[(x, index)], sigs[(y, other)], a.samples)
                if d < best:
                    best, best_at = d, other
            same = T.distance(sigs[(x, index)], sigs[(y, index)], a.samples)
            ranks.append((x, y, index, same, best_at, best, 1 if best_at == index else 0))
    out = os.path.join(NOTES, "take_index_agreement_psp.tsv")
    with open(out, "w") as f:
        f.write("pair\tmode\ttake_index\tdistance\tbest_take\tbest_distance\tsame\n")
        for r in ranks:
            f.write("%s/%s\t%s\t%d\t%.4f\t%d\t%.4f\t%d\n" % (r[0], r[1], a.mode, r[2], r[3], r[4], r[5], r[6]))
    hits = sum(r[6] for r in ranks)
    print(f"{out}: {len(ranks)} (pair, index) rows, same index is the best match in "
          f"{hits} ({100.0 * hits / len(ranks):.1f}%)")
    per_index = {}
    for r in ranks:
        per_index.setdefault(r[2], []).append(r[6])
    agree = [(i, v) for i, v in per_index.items() if all(v)]
    disagree = [(i, v) for i, v in per_index.items() if not all(v)]
    print(f"indices where every measured pair agrees: {[i for i, _ in agree]}")
    print(f"indices where some pair disagrees: {[i for i, _ in disagree]}")
    print(f"{'idx':>3} {'n':>2} {'mean_d':>7}")
    for index, n, mean, best in sorted(rows, key=lambda r: r[2]):
        print(f"{index:>3} {n:>2} {mean:7.4f}")


if __name__ == "__main__":
    main()
