"""Build the PC animation-set -> PSP motion-take tables for the borrowed PC combos.

Inputs, all shipped data (nothing from the PSP executable):
  install data/<char>/00.dat   frame table: states -> phases -> animation set index
  install data/<char>/00.X     the animation sets those indices name (the loader reverses
                               the file array, so controller index i is file set N-1-i)
  PSP g3d/chrm17|18|19.gmo     the PSP fighter that will wear the table (Satoshi, Miyoko,
                               Okonogi) and g3d/chrm02|05a|10.gmo, the same persons as the
                               dispatch PC characters, used as a cross-check

Selection: a take's own length is the one cue with a recovered mechanism behind it — the
phase advances when its tick counter passes the set's length — so duration dominates the
score; the per-bone motion spread (which joints move) and the joint-angle shape break ties.

    python3 build_take_map.py [--out DIR]
"""
import argparse
import csv
import collections
import math
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pc_frametable as FT
import takecore as T

REPO = "/home/marcelo/Projects/daybreak-remake"
INSTALL = os.path.join(REPO, "Higurashi-Daybreak")
PSP_DUMP = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "dump", "g3d")
OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "notes")
SAMPLES = 16

# dispatch PC character, same person's PSP model (cross-check), PSP model that will play it
DISPATCH = [
    ("keiichi", "chrm02.gmo", "chrm17.gmo"),   # Satoshi
    ("satoko", "chrm05a.gmo", "chrm18.gmo"),   # Miyoko
    ("tomitake", "chrm10.gmo", "chrm19.gmo"),  # Okonogi
]
WEIGHTS = (0.60, 0.25, 0.15)   # duration, motion spread, joint-angle shape


def usable(take):
    return len(take["tracks"]) >= 15 and take["frames"] > 3


def energy_profile(rig, clip, side, n=SAMPLES):
    out = []
    for pc_b, psp_b, w in T.BONE_MAP:
        b = pc_b if side == "pc" else psp_b
        if b not in rig.bones:
            continue
        vals = []
        for i in range(n):
            u = i / (n - 1)
            d = T.qmul(T.qconj(rig.local_at(clip, b, 0.0)), rig.local_at(clip, b, u))
            vals.append(2 * math.acos(min(1.0, abs(d[3]))) / math.pi)
        mean = sum(vals) / len(vals)
        out.append((b, math.sqrt(sum((v - mean) ** 2 for v in vals) / len(vals))))
    return out


def cosine(a, b):
    num = sum(x * y for (_, x), (_, y) in zip(a, b))
    da = math.sqrt(sum(x * x for _, x in a))
    db = math.sqrt(sum(y * y for _, y in b))
    return num / (da * db) if da > 1e-9 and db > 1e-9 else 0.0


def features(rig, clip, side):
    ang = rig.angle_signature(clip, SAMPLES, side)
    centred, _rms = T.shape(ang)
    return {"shape": centred, "energy": energy_profile(rig, clip, side),
            "seconds": clip["seconds"], "frames": clip["frames"]}


def components(fa, fb):
    """(shape, spread, duration) each in [0,1]."""
    num = suma = sumb = 0.0
    for (_, _, w, va), (_, _, _, vb) in zip(fa["shape"], fb["shape"]):
        num += w * va * vb
        suma += w * va * va
        sumb += w * vb * vb
    corr = num / math.sqrt(suma * sumb) if suma > 1e-12 and sumb > 1e-12 else 0.0
    shape = (1.0 + corr) / 2.0
    spread = (1.0 + cosine(fa["energy"], fb["energy"])) / 2.0
    if fa["seconds"] > 0 and fb["seconds"] > 0:
        dur = max(0.0, 1.0 - abs(math.log2(fb["seconds"] / fa["seconds"])) / 2.0)
    else:
        dur = 0.0
    return shape, spread, dur


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", default=OUT)
    args = ap.parse_args()
    os.makedirs(args.out, exist_ok=True)

    for pc_char, same_psp, target_psp in DISPATCH:
        dat = FT.read(os.path.join(INSTALL, "data", pc_char, "00.dat"))
        rig = T.load_pc(os.path.join(INSTALL, "data", pc_char, "00.X"))
        for c in rig.clips:
            c["seconds"] = c["ticks"] / 4800.0
        target = T.load_psp(os.path.join(PSP_DUMP, target_psp))
        same = T.load_psp(os.path.join(PSP_DUMP, same_psp))
        for m in (target, same):
            for t in m.clips:
                t["seconds"] = t["frames"] / 30.0
        uses = collections.defaultdict(list)
        for st in dat["states"]:
            for ph in st["phases"]:
                uses[ph["set"]].append(st["id"])
        tfeat = {t["index"]: features(target, t, "psp") for t in target.clips if usable(t)}
        sfeat = {t["index"]: features(same, t, "psp") for t in same.clips if usable(t)}

        rows = []
        for s in sorted(uses):
            clip = rig.clips[s]
            fa = features(rig, clip, "pc")
            ranked = []
            for t, fb in tfeat.items():
                sh, sp, du = components(fa, fb)
                ranked.append((WEIGHTS[0] * du + WEIGHTS[1] * sp + WEIGHTS[2] * sh, t, sh, sp, du))
            ranked.sort(reverse=True)
            best = ranked[0]
            samepick = None
            if sfeat:
                cand = []
                for t, fb in sfeat.items():
                    sh, sp, du = components(fa, fb)
                    cand.append((WEIGHTS[0] * du + WEIGHTS[1] * sp + WEIGHTS[2] * sh, t))
                cand.sort(reverse=True)
                samepick = cand[0][1]
            take = target.clips[best[1]]
            rows.append({
                "pc_set_index": s,
                "pc_set_name": clip["name"].split("(")[-1].rstrip(")"),
                "pc_frames": round(clip["frames"], 2),
                "pc_states_using_it": " ".join(str(x) for x in sorted(set(uses[s]))),
                "psp_take_index": best[1],
                "psp_take_name": take["name"],
                "psp_frames": round(take["frames"], 1),
                "score": round(best[0], 4),
                "method": "fallback",
                "pc_seconds": round(fa["seconds"], 3),
                "psp_seconds": round(take["seconds"], 3),
                "score_duration": round(best[4], 3),
                "score_spread": round(best[3], 3),
                "score_shape": round(best[2], 3),
                "same_person_take_index": samepick if samepick is not None else "",
                "same_person_agrees": int(samepick == best[1]),
                "confidence": ("medium" if (samepick == best[1] and best[4] >= 0.9)
                               else "low-medium" if best[4] >= 0.9 else "low"),
            })
        path = os.path.join(args.out, "take_map_%s.tsv" % pc_char)
        with open(path, "w", newline="") as fh:
            w = csv.DictWriter(fh, fieldnames=list(rows[0].keys()), delimiter="\t")
            w.writeheader()
            w.writerows(rows)
        agree = sum(r["same_person_agrees"] for r in rows)
        print("%-9s %3d sets -> %s (%d usable takes); same-person cross-check agrees on %d/%d"
              % (pc_char, len(rows), target_psp, len(tfeat), agree, len(rows)))
        print("   wrote", path)


if __name__ == "__main__":
    main()
