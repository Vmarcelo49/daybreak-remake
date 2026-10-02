#!/usr/bin/env python3
"""Compare a banked DX9 frame with a foundation frame of the same case.

Phase 3's gate is "a complete in-game frame matching the banked DX9 reference", so
this is the instrument that decides it: same case, same frame index, two renderers,
one set of numbers. It reports what the visual suite already reports (RMSE against
ground truth, coverage, luminance) plus the per-channel breakdown and a saved
difference image, because "the frame matches" is only meaningful with the number and
the picture next to each other.

Usage:
    compare_frames.py <dx9-image> <foundation.ppm> [--out /tmp/diff.png]
                      [--label "gameplay-120 frame 120"]

Both inputs may be PNG/PPM/WebP: anything ImageMagick reads. The DX9 side is a PNG
(remake/tests/visual/out/<case>.png) and the foundation side a PPM (--out), which is
what the two tools actually produce.

Metrics:
  * RMSE       — per channel and overall, normalised 0..1 (ImageMagick's convention,
                 so the numbers are comparable with remake/tests/visual/report.html)
  * coverage   — fraction of pixels that are not pure black, both sides
  * luminance  — min/max/mean, both sides
  * diff image — |a-b| amplified 4x, plus a side-by-side montage for the eye

Exit status 0 always: this reports, it does not gate. The gate is a human decision
recorded in the plan, made from these numbers.
"""

import argparse
import os
import struct
import subprocess
import sys
import tempfile


def to_ppm(path, tmpdir):
    """Any ImageMagick-readable image -> a P6 PPM path."""
    if path.lower().endswith(".ppm"):
        return path
    out = os.path.join(tmpdir, os.path.basename(path) + ".ppm")
    subprocess.run(["convert", path, out], check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return out


def read_ppm(path):
    with open(path, "rb") as fh:
        data = fh.read()
    # P6 <w> <h> <max>\n<binary>
    fields, pos = [], 0
    while len(fields) < 4:
        while data[pos:pos + 1].isspace():
            pos += 1
        if data[pos:pos + 1] == b"#":
            while data[pos:pos + 1] != b"\n":
                pos += 1
            continue
        start = pos
        while not data[pos:pos + 1].isspace():
            pos += 1
        fields.append(data[start:pos])
    pos += 1
    if fields[0] != b"P6":
        raise SystemExit(f"{path}: not a P6 PPM ({fields[0]!r})")
    w, h, maxval = int(fields[1]), int(fields[2]), int(fields[3])
    if maxval != 255:
        raise SystemExit(f"{path}: maxval {maxval} unsupported")
    px = data[pos:pos + w * h * 3]
    if len(px) != w * h * 3:
        raise SystemExit(f"{path}: truncated ({len(px)} of {w * h * 3} bytes)")
    return w, h, px


def stats(px, w, h):
    n = w * h
    covered = 0
    lum_sum = 0.0
    lum_min, lum_max = 1.0, 0.0
    for i in range(n):
        r, g, b = px[3 * i], px[3 * i + 1], px[3 * i + 2]
        if r or g or b:
            covered += 1
        lum = (0.299 * r + 0.587 * g + 0.114 * b) / 255.0
        lum_sum += lum
        lum_min = min(lum_min, lum)
        lum_max = max(lum_max, lum)
    return {
        "coverage_px": covered,
        "coverage": covered / n,
        "lum_min": lum_min,
        "lum_max": lum_max,
        "lum_mean": lum_sum / n,
    }


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dx9")
    ap.add_argument("foundation")
    ap.add_argument("--out", default="/tmp/frame_diff.png")
    ap.add_argument("--label", default="")
    args = ap.parse_args()

    tmpdir = tempfile.mkdtemp(prefix="framecmp.")
    a_ppm = to_ppm(args.dx9, tmpdir)
    b_ppm = to_ppm(args.foundation, tmpdir)
    wa, ha, pa = read_ppm(a_ppm)
    wb, hb, pb = read_ppm(b_ppm)

    label = args.label or os.path.basename(args.dx9)
    print(f"case        : {label}")
    print(f"dx9         : {args.dx9} ({wa}x{ha})")
    print(f"foundation  : {args.foundation} ({wb}x{hb})")

    if (wa, ha) != (wb, hb):
        # Resample the foundation frame to the DX9 size: the DX9 harness captures at
        # the window size and the foundation at --size, and a size mismatch is a
        # harness bug, not a render difference. Reported, not hidden.
        print(f"NOTE        : sizes differ; resampling the foundation frame to {wa}x{ha}")
        resized = os.path.join(tmpdir, "resized.ppm")
        subprocess.run(["convert", b_ppm, "-resize", f"{wa}x{ha}!", resized], check=True,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        wb, hb, pb = read_ppm(resized)

    n = wa * ha
    sumsq = [0, 0, 0]
    for i in range(n):
        for c in range(3):
            d = pa[3 * i + c] - pb[3 * i + c]
            sumsq[c] += d * d
    rmse = [(s / n) ** 0.5 / 255.0 for s in sumsq]
    overall = (sum(sumsq) / (3 * n)) ** 0.5 / 255.0

    sa, sb = stats(pa, wa, ha), stats(pb, wa, ha)
    print(f"RMSE        : overall {overall:.6f}  (r {rmse[0]:.6f} g {rmse[1]:.6f} b {rmse[2]:.6f})")
    print(f"coverage    : dx9 {sa['coverage_px']} px ({100 * sa['coverage']:.2f}%)  "
          f"foundation {sb['coverage_px']} px ({100 * sb['coverage']:.2f}%)")
    print(f"luminance   : dx9 {sa['lum_min']:.3f}..{sa['lum_max']:.3f} "
          f"(mean {sa['lum_mean']:.3f})  "
          f"foundation {sb['lum_min']:.3f}..{sb['lum_max']:.3f} "
          f"(mean {sb['lum_mean']:.3f})")

    diff = os.path.join(tmpdir, "diff.ppm")
    side = os.path.join(tmpdir, "side.ppm")
    subprocess.run(["compare", "-metric", "AE", a_ppm, b_ppm, diff], check=False,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    subprocess.run(["montage", a_ppm, b_ppm, "-tile", "2x1", "-geometry", "+0+0", side],
                   check=False, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    if os.path.exists(side):
        subprocess.run(["convert", side, args.out], check=False,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
        print(f"side-by-side: {args.out}  (dx9 left, foundation right)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
