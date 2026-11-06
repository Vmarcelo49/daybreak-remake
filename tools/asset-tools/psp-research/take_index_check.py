"""Measure whether PSP motion take index i is the same move on two PSP characters.

The PSP models all ship 76 motion slots, but only 39-56 of them carry curves and the
"dummy" slots differ per character. Comparing take i of two characters uses joint
positions in a body frame built from the hips, which needs no shared bone roll.

    python3 take_index_check.py [--out DIR]
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import takecore as T

DUMP = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "dump", "g3d")
PAIRS = [("chrm02.gmo", "chrm17.gmo", "keiichi", "satoshi"),
         ("chrm05a.gmo", "chrm18.gmo", "satoko", "miyoko"),
         ("chrm10.gmo", "chrm19.gmo", "tomitake", "okonogi")]
SAMPLES = 16


def usable(take):
    return len(take["tracks"]) >= 15 and take["frames"] > 3


def _s(v):
    return (v,) if isinstance(v, float) else v


def dist(a, b):
    tot = wsum = 0.0
    for (_, _, w, va), (_, _, _, vb) in zip(a, b):
        tot += w * sum((x - y) ** 2 for x, y in zip(_s(va), _s(vb))) ** 0.5
        wsum += w
    return tot / wsum


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--mode", default="both", choices=("pos", "angle", "both"))
    ap.add_argument("--out", default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "notes"))
    args = ap.parse_args()
    rows = ["pair\tmode\ttake_index\tdistance\trank_of_same_index\tbest_take\tbest_distance\tsame"]
    for mode in (("pos", "angle") if args.mode == "both" else (args.mode,)):
        run(rows, mode)
    path = os.path.join(args.out, "take_index_agreement.tsv")
    open(path, "w").write("\n".join(rows) + "\n")
    print("wrote", path)


def run(rows, mode):
    for fa, fb, na, nb in PAIRS:
        a = T.load_psp(os.path.join(DUMP, fa))
        b = T.load_psp(os.path.join(DUMP, fb))
        if mode == "pos":
            sa = {t["index"]: a.pos_signature(t, SAMPLES, "psp") for t in a.clips if usable(t)}
            sb = {t["index"]: b.pos_signature(t, SAMPLES, "psp") for t in b.clips if usable(t)}
        else:
            sa = {t["index"]: T.shape(a.angle_signature(t, SAMPLES, "psp"))[0] for t in a.clips if usable(t)}
            sb = {t["index"]: T.shape(b.angle_signature(t, SAMPLES, "psp"))[0] for t in b.clips if usable(t)}
        common = sorted(set(sa) & set(sb))
        wins = 0
        for i in common:
            ranked = sorted((dist(sa[i], sb[j]), j) for j in common)
            rank = [j for _, j in ranked].index(i)
            wins += rank == 0
            rows.append("%s/%s\t%s\t%d\t%.4f\t%d\t%d\t%.4f\t%d"
                        % (na, nb, mode, i, dist(sa[i], sb[i]), rank + 1,
                           ranked[0][1], ranked[0][0], int(rank == 0)))
        top3 = rank < 3
        same = [dist(sa[i], sb[i]) for i in common]
        tight = sum(1 for d in same if d < 0.05)
        print("[%s] %-9s vs %-9s: %d takes with curves in both, same index is best for %d, "
              "%d agree within 0.05, median same-index distance %.3f"
              % (mode, na, nb, len(common), wins, tight, sorted(same)[len(same) // 2]))


if __name__ == "__main__":
    main()
