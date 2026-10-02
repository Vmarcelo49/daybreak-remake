#!/usr/bin/env python3
"""Measure the title menu's elements against the original print.

This is the front end's instance of the `hud_bands.py` recipe, which is the
instrument FRONTEND-PLAN.md §6.3 names for "did each element land where the
original draws it": the band tables are per screen, the reading/cropping/RMSE/ink
-half lives in `hud_bands.py` and is imported rather than copied.

The print is `remake/docs/reference/title-menu.webp`, 803x608: a capture of the
800x600 frame with a **(+1,+5) px offset**, so
    game = (print_x - 1, print_y - 5)
That is this screen's own measurement, **not** the battle HUD's (-2,+6):

  * the logo's ink box, placed from FUN_00410d60.c:35 + FUN_004114f0.c:18, matches
    the print's at best offset (0,0) with IoU 0.980 over 22.6k ink pixels;
  * the six-item column, placed from FUN_006556c0/FUN_00655830's 192x48 cells at
    x = 400 and y = i*48 + 285, matches at (0,0) with IoU 0.975 over 11.9k pixels;
  * independently, every background-only tile of the print (the shrine photo, which
    our capture reproduces byte-identically from data/title/back00.cnv) minimises
    its mean |diff| at (+1,+5): 1.6..3.1 of 255 against 3.1..13.5 at the neighbours.

    tests/title_bands.py <foundation.ppm> [--save /tmp/prefix] [--bands a,b,c] [--shapes]

Reported per band: RMSE (0..1, the compare_frames.py convention) and the print's and
the capture's luminance means. --save writes <prefix>_<band>.png as a 3x-magnified
print|ours side-by-side plus the two halves, which is what "look at the crop" needs.
--shapes adds the dark/white ink masks' best integer offset and IoU.

Exit status 0 always: this reports, it does not gate.
"""

import argparse
import os
import sys

import numpy as np
from PIL import Image

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import hud_bands as hb   # read_ppm / luminance / crop_pair / rmse / ink_mask

HERE = os.path.dirname(os.path.abspath(__file__))
PRINT = os.path.join(HERE, "..", "..", "docs", "reference", "title-menu.webp")
OFF_X, OFF_Y = -1, -5   # game = print + (-1,-5)

# name: (game x, y, w, h). The three sprite rects FUN_00410d60.c:34-36 configures and
# FUN_004114f0.c:17-22 draws: back (0,0,800,600); logo (0,0,512,300) at (400,-20), so
# its quad is (144,-20)-(656,280); item cells 192x48 at x = 400 (quad x 304..496) with
# their top edges at 285 + i*48.
BANDS = {
    "title-all":   (0, 0, 800, 600),
    "title-logo":  (144, 0, 512, 282),      # the visible part of (-20 .. 280)
    "title-items": (296, 280, 208, 300),
    "title-item0": (304, 285, 192, 48),
    "title-item1": (304, 333, 192, 48),
    "title-item2": (304, 381, 192, 48),
    "title-item3": (304, 429, 192, 48),
    "title-item4": (304, 477, 192, 48),
    "title-item5": (304, 525, 192, 48),
    # background-only control: no sprite of either side is here, so this is the floor
    # the print's own lossy compression sets.
    "title-floor": (20, 580, 220, 15),
}

# name: ((game x, y, w, h), ink mode). "dark" is the unselected columns' black glyphs,
# "bright" the selected column's white one: the selection state is exactly which
# column each row draws, so the masks are also the cursor check.
SHAPES = {
    "title-items-ink":  ((296, 280, 208, 300), "dark"),
    "title-logo-ink":   ((144, 0, 512, 282), "dark"),
    "title-select-ink": ((304, 285, 192, 48), "bright"),
}


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ppm")
    ap.add_argument("--save", default="")
    ap.add_argument("--bands", default=",".join(BANDS))
    ap.add_argument("--shapes", action="store_true")
    args = ap.parse_args()

    # crop_pair() reads the module's offset, which is this screen's.
    hb.OFF_X, hb.OFF_Y = OFF_X, OFF_Y

    print_img = np.array(Image.open(PRINT).convert("RGB"))
    frame = hb.read_ppm(args.ppm)
    print(f"print       : {PRINT} ({print_img.shape[1]}x{print_img.shape[0]}) "
          f"off {OFF_X},{OFF_Y}")
    print(f"frame       : {args.ppm} ({frame.shape[1]}x{frame.shape[0]})")
    print(f"{'band':<13}{'crop (game)':<22}{'RMSE':>8}{'lum print':>11}{'lum frame':>11}"
          f"{'dLum':>9}")
    for name in args.bands.split(","):
        x, y, w, h = BANDS[name]
        a, b = hb.crop_pair(print_img, frame, x, y, w, h)
        if a is None or a.shape != b.shape:
            print(f"{name:<13}(outside both images)")
            continue
        la = float(hb.luminance(a).mean()) / 255.0
        lb = float(hb.luminance(b).mean()) / 255.0
        print(f"{name:<13}{f'{x},{y} {a.shape[1]}x{a.shape[0]}':<22}{hb.rmse(a, b):8.4f}"
              f"{la:11.4f}{lb:11.4f}{lb - la:+9.4f}")
        if args.save:
            gap = np.full((a.shape[0], 4, 3), 255, np.uint8)
            side = np.concatenate([a, gap, b], axis=1)
            scale = 3
            Image.fromarray(side).resize((side.shape[1] * scale, side.shape[0] * scale),
                                         Image.NEAREST).save(f"{args.save}_{name}.png")

    if args.shapes:
        print(f"\n{'element':<18}{'ink px':>8}{'best offset':>14}{'IoU':>8}{'xor(0,0)':>10}")
        for name, (box, mode) in SHAPES.items():
            a, b = hb.crop_pair(print_img, frame, *box)
            if a is None or a.shape != b.shape:
                continue
            pa, pb = hb.ink_mask(a, mode), hb.ink_mask(b, mode)
            best = min(((int((np.roll(np.roll(pb, oy, 0), ox, 1) ^ pa).sum()), ox, oy)
                        for oy in range(-6, 7) for ox in range(-6, 7)))
            union = int((pa | pb).sum())
            iou = float((pa & pb).sum()) / union if union else 0.0
            print(f"{name:<18}{int(pa.sum()):>8}{f'({best[1]:+d},{best[2]:+d})':>14}"
                  f"{iou:>8.3f}{best[0]:>10}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
