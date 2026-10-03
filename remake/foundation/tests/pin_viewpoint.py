#!/usr/bin/env python3
"""pin_viewpoint.py — re-run the A2 spawn sweep (ROADMAP-PENDING.md A2).

The pinned stage01 viewpoint is the instrument every print-parity number is
measured with, so it must be re-runnable, not lore: P1 on each env.dat point
with P2 on its pair-mate, print cast (rena/mion), converged --match captures,
scored on the scene-floor band. Winner must be config 0 (P1 points[0]) at the
recorded values, within tolerance; anything else means a camera, preset,
spawn, or spawn-pairing regression moved the instrument.

Expected (recorded 2026-10-02, reproduced 2026-10-03):
  scene-floor: 0.2772 / 0.2908 / 0.3162 / 0.2961 (tolerance 0.002)
  whole-frame: 0.2567 / 0.2438 / 0.2699 / 0.2478 (context only, tolerance 0.01;
    config 1 wins whole-frame — the mirrored fighter pose and HUD art confound
    it, which is why the scene band is the prescribed instrument).

Usage:
  python3 tests/pin_viewpoint.py [--keep DIR]

Exit status 0 when the winner and all scene-floor values reproduce, 1 otherwise.
Captures land in a temp dir unless --keep is given.
"""

import argparse
import math
import re
import subprocess
import sys
import tempfile
from pathlib import Path

import numpy as np
from PIL import Image

sys.path.insert(0, str(Path(__file__).resolve().parent))
import hud_bands  # noqa: E402  (band crops + RMSE, same instrument as A2)

FOUNDATION = Path(__file__).resolve().parents[1]
DATA = FOUNDATION.parents[1] / "Higurashi-Daybreak" / "data"
BINARY = FOUNDATION / "build" / "linux" / "foundation_demo"
PRINT = FOUNDATION.parent / "docs" / "reference" / "battle-hud.webp"
COMPARE = Path(__file__).resolve().parent / "compare_frames.py"

# (P1 spawn, P2 spawn): P1 on each point, P2 on its pair-mate — far pair
# z=-2200 (points 0,1), near pair z=-105 (points 2,3). Order is the A2 record.
CONFIGS = [
    ("-463,200,-2200", "-1363,200,-2200"),
    ("-1363,200,-2200", "-463,200,-2200"),
    ("-406,200,-105", "-1363,200,-105"),
    ("-1363,200,-105", "-406,200,-105"),
]

EXPECT_FLOOR = (0.2772, 0.2908, 0.3162, 0.2961)
EXPECT_WHOLE = (0.2567, 0.2438, 0.2699, 0.2478)
TOL_FLOOR = 0.002
TOL_WHOLE = 0.01


WHOLE_RE = re.compile(r"overall (\d+\.\d+)")


def run_capture(spawn, spawn2, out):
    cmd = [str(BINARY), "--headless", f"--out={out}",
           f"--stage={DATA / 'stage01'}", f"--character={DATA / 'rena'}",
           f"--enemy={DATA / 'mion'}", "--match", "--camera=arena",
           f"--spawn={spawn}", f"--spawn2={spawn2}",
           "--frames=150", "--size=800x600"]
    try:
        p = subprocess.run(cmd, capture_output=True, text=True,
                           encoding="utf-8", errors="replace", timeout=180)
    except subprocess.TimeoutExpired:
        return False
    return p.returncode == 0 and "RESULT: ok" in (p.stdout + p.stderr)


def band_rmse(print_img, frame, name):
    a, b = hud_bands.crop_pair(print_img, frame, *hud_bands.BANDS[name])
    return hud_bands.rmse(a, b)


def whole_rmse(frame_path):
    # Same tool the A2 record used (it resamples to the print size).
    p = subprocess.run([sys.executable, str(COMPARE), str(PRINT), str(frame_path)],
                       capture_output=True, text=True, encoding="utf-8",
                       errors="replace", timeout=120)
    m = WHOLE_RE.search(p.stdout)
    return float(m.group(1)) if m else float("nan")


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--keep", default=None, help="keep captures in DIR")
    args = ap.parse_args()

    if not BINARY.is_file():
        print(f"SKIP: no demo binary at {BINARY} (build linux first)")
        return 0
    if not (DATA / "stage01").is_dir():
        print(f"SKIP: no game data at {DATA} (needs the install)")
        return 0

    with tempfile.TemporaryDirectory() as tmp:
        out_dir = Path(args.keep) if args.keep else Path(tmp)
        out_dir.mkdir(parents=True, exist_ok=True)
        print_img = np.array(Image.open(PRINT).convert("RGB"))
        floors, wholes = [], []
        for i, (s1, s2) in enumerate(CONFIGS):
            out = out_dir / f"viewpoint_cfg{i}.ppm"
            if not run_capture(s1, s2, out):
                print(f"config {i}: capture FAILED")
                return 1
            frame = hud_bands.read_ppm(str(out))
            floors.append(band_rmse(print_img, frame, "scene-floor"))
            wholes.append(whole_rmse(out))
            print(f"config {i}: P1=({s1}) P2=({s2}) "
                  f"scene-floor={floors[-1]:.4f} (expect {EXPECT_FLOOR[i]:.4f}) "
                  f"whole={wholes[-1]:.4f} (expect {EXPECT_WHOLE[i]:.4f})")

    failed = 0
    winner = min(range(4), key=lambda i: floors[i])
    if winner != 0:
        print(f"FAIL: winner is config {winner}, want 0 (P1 points[0])")
        failed = 1
    for i in range(4):
        # NaN (a failed compare) must fail, and NaN comparisons never do —
        # so test finiteness explicitly.
        if math.isnan(floors[i]) or abs(floors[i] - EXPECT_FLOOR[i]) > TOL_FLOOR:
            print(f"FAIL: config {i} scene-floor {floors[i]:.4f} outside "
                  f"{TOL_FLOOR} of {EXPECT_FLOOR[i]:.4f}")
            failed = 1
        if math.isnan(wholes[i]) or abs(wholes[i] - EXPECT_WHOLE[i]) > TOL_WHOLE:
            print(f"FAIL: config {i} whole-frame {wholes[i]:.4f} outside "
                  f"{TOL_WHOLE} of {EXPECT_WHOLE[i]:.4f}")
            failed = 1
    print("PIN_VIEWPOINT: " + ("ok" if not failed else "FAIL"))
    return failed


if __name__ == "__main__":
    sys.exit(main())
