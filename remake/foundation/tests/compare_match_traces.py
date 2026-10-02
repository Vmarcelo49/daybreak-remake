#!/usr/bin/env python3
"""Compare fighter traces between the DX9 build and the WebGPU foundation.

Why this exists: Phase 2 ports the fighter simulation out of `remake/src` into
`remake/foundation`, and the only cross-implementation evidence available is the
console trace the DX9 build already prints under DAYBREAK_CAMINFO (one line per
60 render calls: eye, both fighters' positions and animation-state names). This
script turns two logs into a per-sample verdict instead of an eyeball diff.

Usage:
    compare_match_traces.py <dx9.log> <foundation.log> [--tol 0.5]

Both logs must contain lines of the form

    [daybreak] cam eye=(x,y,z) p1=(x,y,z,anim) p2=(x,y,z,anim)

which is the exact format `remake/src/core/scenes.cpp` prints. Positions are
printed with %.0f on both sides, so the default tolerance is 0.5 units (half a
printed unit); animation-state names must match exactly. `eye` is reported but
not asserted: the DX9 camera (ArenaCamera, unclamped) and the foundation's
(render::arenaViewProj + clamp) are different implementations on purpose, so
only fighter state is comparable.

Exit status: 0 when every sampled fighter field agrees, 1 otherwise.
"""

import argparse
import re
import sys

LINE = re.compile(
    r"cam eye=\((-?\d+),(-?\d+),(-?\d+)\) "
    r"p1=\((-?\d+),(-?\d+),(-?\d+),([^)]+)\) "
    r"p2=\((-?\d+),(-?\d+),(-?\d+),([^)]+)\)"
)


def parse(path):
    samples = []
    with open(path, encoding="utf-8", errors="replace") as fh:
        for line in fh:
            m = LINE.search(line)
            if m:
                g = m.groups()
                samples.append(
                    {
                        "eye": tuple(float(v) for v in g[0:3]),
                        "p1": tuple(float(v) for v in g[3:6]),
                        "p1anim": g[6].strip(),
                        "p2": tuple(float(v) for v in g[7:10]),
                        "p2anim": g[10].strip(),
                    }
                )
    return samples


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dx9")
    ap.add_argument("foundation")
    ap.add_argument("--tol", type=float, default=0.5,
                    help="max per-axis position delta in game units (default 0.5)")
    args = ap.parse_args()

    a = parse(args.dx9)
    b = parse(args.foundation)
    print(f"dx9={args.dx9}: {len(a)} sample(s)")
    print(f"foundation={args.foundation}: {len(b)} sample(s)")

    if not a or not b:
        print("FAIL: one side has no trace lines "
              "(is DAYBREAK_CAMINFO=1 set on the DX9 run?)")
        return 1
    n = min(len(a), len(b))
    if len(a) != len(b):
        print(f"NOTE: comparing the first {n} samples; counts differ")

    worst = 0.0
    failures = []
    for i in range(n):
        frame = 1 + 60 * i  # the probe fires on render call 1, 61, 121, ...
        for side in ("p1", "p2"):
            d = max(abs(a[i][side][k] - b[i][side][k]) for k in range(3))
            worst = max(worst, d)
            anim_a, anim_b = a[i][side + "anim"], b[i][side + "anim"]
            ok = d <= args.tol and anim_a == anim_b
            if not ok:
                failures.append((frame, side, a[i][side], b[i][side], d, anim_a, anim_b))
        eye_d = max(abs(a[i]["eye"][k] - b[i]["eye"][k]) for k in range(3))
        print(f"frame {frame:5d}  p1 dx9={a[i]['p1']} fnd={b[i]['p1']} "
              f"({a[i]['p1anim']}/{b[i]['p1anim']})  "
              f"p2 dx9={a[i]['p2']} fnd={b[i]['p2']} "
              f"({a[i]['p2anim']}/{b[i]['p2anim']})  eye delta={eye_d:.0f} (informational)")

    print(f"\nworst fighter position delta: {worst:.0f} unit(s), tolerance {args.tol}")
    if failures:
        print(f"MATCH_TRACES: FAIL ({len(failures)} field(s))")
        for frame, side, pa, pb, d, aa, ab in failures:
            print(f"  frame {frame} {side}: dx9={pa} anim={aa} vs fnd={pb} anim={ab} (d={d:.0f})")
        return 1
    print(f"MATCH_TRACES: ok ({n} sample(s) x 2 fighters)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
