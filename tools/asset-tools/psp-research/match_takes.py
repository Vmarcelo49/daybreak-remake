"""Rank PSP motion takes against PC animation sets for one dispatch character.

    python3 match_takes.py <pc char> [--psp chrmNN.gmo] [--mode local|global|angle]
                          [--samples N] [--sets 0,1,2] [--top 3]

`<pc char>` is an install directory name (keiichi, satoko, tomitake); the default PSP
model is the same person's (`chrm02.gmo`, `chrm05a.gmo`, `chrm10.gmo`).
"""
import argparse
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import takecore as T

REPO = "/home/marcelo/Projects/daybreak-remake"
INSTALL = os.path.join(REPO, "Higurashi-Daybreak")
PSP_DUMP = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "dump", "g3d")
SELF_PSP = {"keiichi": "chrm02.gmo", "satoko": "chrm05a.gmo", "tomitake": "chrm10.gmo"}


def ranks(pc_rig, psp_rig, mode, samples, set_index, top=3):
    a = pc_rig.signature(pc_rig.clips[set_index], mode, samples)
    out = []
    for take in psp_rig.clips:
        b = psp_rig.signature(take, mode, samples)
        out.append((T.distance(a, b, samples), take["index"], take["frames"]))
    out.sort()
    return out[:top]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("char")
    ap.add_argument("--psp")
    ap.add_argument("--mode", default="global")
    ap.add_argument("--samples", type=int, default=24)
    ap.add_argument("--sets", default="")
    ap.add_argument("--top", type=int, default=3)
    a = ap.parse_args()
    pc = T.load_pc(os.path.join(INSTALL, "data", a.char, "00.X"))
    psp = T.load_psp(os.path.join(PSP_DUMP, a.psp or SELF_PSP[a.char]))
    want = [int(x) for x in a.sets.split(",")] if a.sets else list(range(124))
    for s in want:
        r = ranks(pc, psp, a.mode, a.samples, s, a.top)
        print("%-4d %-18s %-8s -> %s" % (
            s, "%.1ff" % pc.clips[s]["frames"], a.mode,
            "  ".join("take %2d (%.0ff) %.3f" % (t, f, 1 - d) for d, t, f in r)))


if __name__ == "__main__":
    main()
