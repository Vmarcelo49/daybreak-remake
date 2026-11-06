"""Merge the root-motion table and the pose profile into one per-take summary.

    python3 take_summary.py [rig ...]

Prints one line per non-empty take, with the numbers that decide the label: length,
net and peak root motion, whether the take is airborne, the torso pitch range (0 upright,
90 horizontal) and whether the first and last pose agree (a loop).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
PSP = os.path.normpath(os.path.join(HERE, ".."))
NOTES = os.path.join(PSP, "notes")


def read_tsv(path):
    with open(path) as f:
        header = f.readline().rstrip("\n").split("\t")
        rows = []
        for line in f:
            if not line.strip() or line.startswith("#"):
                continue
            rows.append(dict(zip(header, line.rstrip("\n").split("\t"))))
    return rows


def merged(rig):
    root = {(r["rig"], r["take_index"]): r for r in read_tsv(os.path.join(NOTES, "take_root_motion.tsv"))
            if r["rig"] == rig}
    profile = {r["take_index"]: r for r in read_tsv(os.path.join(NOTES, f"take_profile_{rig}.tsv"))}
    out = []
    for index, p in sorted(profile.items(), key=lambda kv: int(kv[0])):
        r = root.get((rig, index), {})
        out.append((index, p, r))
    return out


def main():
    rigs = sys.argv[1:] or ["chrm17"]
    for rig in rigs:
        print(f"=== {rig}")
        print(f"{'idx':>3} {'name':16s} {'frm':>4} {'dy':>6} {'dz':>6} {'dx':>6} "
              f"{'y_rng':>11} {'foot_rng':>11} {'air':>4} {'pitch0/1':>9} {'pitch_rng':>10} "
              f"{'loop':>4} {'pfwd':>5}")
        for index, p, r in merged(rig):
            print(f"{int(index):>3} {p['take_name']:16s} {int(p['frames']):4d} "
                  f"{float(p['net_dy']):6.1f} {float(p['net_dz']):6.1f} {float(p['net_dx']):6.1f} "
                  f"{float(p['y_min']):5.0f}..{float(p['y_max']):5.0f} "
                  f"{float(p['foot_min']):5.1f}..{float(p['foot_max']):5.1f} "
                  f"{int(p['air_frames']):4d} "
                  f"{float(p['pitch0']):4.0f}/{float(p['pitch1']):4.0f} "
                  f"{float(p['pitch_min']):4.0f}..{float(p['pitch_max']):4.0f} "
                  f"{int(p['loops']):4d} {float(r.get('path_fwd', 0)):5.0f}")
        print()


if __name__ == "__main__":
    main()
