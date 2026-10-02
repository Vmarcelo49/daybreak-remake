#!/usr/bin/env python3
"""Measure the battle HUD's elements against the original print.

`compare_frames.py` answers "how far is the whole frame", which on this track is
mostly the scene: the camera-framing track is still fitting the projection, so a
frame-wide RMSE cannot say whether a HUD element landed. This script answers the
narrower question instead — did each element land where the original draws it —
using the print's own coordinate mapping.

The print is 798x606: a capture of the 800x600 frame with a (-2,+6) px offset, so
    game = (print_x + 2, print_y - 6)
(BATTLE-HUD-SPEC.md, verified on the HP and MAIN fills and re-checked here). Bands
are given in game coordinates and cropped from both images without resampling, so
an element with exact anchors is measured exactly.

    tests/hud_bands.py <foundation.ppm> [--save /tmp/prefix] [--bands a,b,c]

Reported per band: RMSE (0..1, the compare_frames.py convention), and the print's
and the frame's luminance means. --save also writes <prefix>_<band>.png as a
3x-magnified print|ours side-by-side, plus the two halves, which is what "look at
the crop" needs.

`--shapes` additionally compares the two frames' dark-ink masks per element (the
frame/bar silhouettes and the fan's black interior): the best integer offset and
the IoU, which is the alignment claim a luminance mean cannot make.

Exit status 0 always: this reports, it does not gate.
"""

import argparse
import os
import sys

import numpy as np
from PIL import Image

HERE = os.path.dirname(os.path.abspath(__file__))
PRINT = os.path.join(HERE, "..", "..", "docs", "reference", "battle-hud.webp")
OFF_X, OFF_Y = 2, -6   # game = print + (2,-6)

# name: (game x, y, w, h). The wide bands are the spec's element groups; the tight
# ones are a single element's footprint, where a change is the HUD's and not the
# scene's.
BANDS = {
    "bottom-right": (480, 425, 320, 175),
    "hp-bar":       (490, 535, 262, 65),
    "main-bar":     (600, 435, 200, 75),
    "charge-bar":   (575, 483, 200, 75),
    "fan-gauge":    (0, 455, 320, 145),
    "hud-all":      (0, 0, 800, 600),
    "hp-frame":     (490, 538, 262, 62),
    "main-frame":   (605, 440, 196, 68),
    "charge-frame": (579, 488, 196, 68),
    "main-count":   (630, 440, 76, 40),
    "charge-count": (605, 485, 76, 40),
    "fan-frame":    (35, 463, 270, 133),
    # scene-only control: no HUD element of either composition is here, so this is
    # the floor a HUD band cannot beat while the framing differs.
    "scene-floor":  (300, 250, 200, 120),
}

# name: (game x, y, w, h) — the sprite rects as drawn, for the shape comparison.
SHAPES = {
    "main-pill":   (607, 442, 192, 64),
    "charge-pill": (581, 490, 192, 64),
    "hp-pill":     (492, 540, 256, 60),
    "fan":         (10, 467, 300, 128),
}


def read_ppm(path):
    with open(path, "rb") as fh:
        data = fh.read()
    fields, pos = [], 0
    while len(fields) < 4:
        while data[pos:pos + 1].isspace():
            pos += 1
        start = pos
        while not data[pos:pos + 1].isspace():
            pos += 1
        fields.append(data[start:pos])
    pos += 1
    w, h = int(fields[1]), int(fields[2])
    return np.frombuffer(data[pos:pos + w * h * 3], dtype=np.uint8).reshape(h, w, 3)


def luminance(a):
    return 0.2126 * a[:, :, 0] + 0.7152 * a[:, :, 1] + 0.0722 * a[:, :, 2]


def crop_pair(print_img, frame, x, y, w, h):
    """The band's pixels from both images, in game coordinates, clipped to what
    each actually covers (the print has no game x < 2 and no game y > 599)."""
    x0 = max(x, OFF_X)
    y0 = max(y, 0)
    pw = min(x + w, frame.shape[1], print_img.shape[1] + OFF_X) - x0
    ph = min(y + h, frame.shape[0], print_img.shape[0] - OFF_Y) - y0
    if pw <= 0 or ph <= 0:
        return None, None
    return (print_img[y0 - OFF_Y:y0 - OFF_Y + ph, x0 - OFF_X:x0 - OFF_X + pw],
            frame[y0:y0 + ph, x0:x0 + pw])


def rmse(a, b):
    d = a.astype(float) - b.astype(float)
    return float(np.sqrt((d ** 2).mean())) / 255.0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ppm")
    ap.add_argument("--save", default="")
    ap.add_argument("--bands", default=",".join(BANDS))
    ap.add_argument("--shapes", action="store_true")
    args = ap.parse_args()

    print_img = np.array(Image.open(PRINT).convert("RGB"))
    frame = read_ppm(args.ppm)
    print(f"print       : {PRINT} ({print_img.shape[1]}x{print_img.shape[0]})")
    print(f"frame       : {args.ppm} ({frame.shape[1]}x{frame.shape[0]})")
    print(f"{'band':<14}{'crop (game)':<22}{'RMSE':>8}{'lum print':>11}{'lum frame':>11}{'dLum':>9}")
    for name in args.bands.split(","):
        a, b = crop_pair(print_img, frame, *BANDS[name])
        if a is None:
            print(f"{name:<14}(outside both images)")
            continue
        x, y, w, h = BANDS[name]
        la, lb = float(luminance(a).mean()) / 255.0, float(luminance(b).mean()) / 255.0
        print(f"{name:<14}{f'{x},{y} {a.shape[1]}x{a.shape[0]}':<22}{rmse(a, b):8.4f}"
              f"{la:11.4f}{lb:11.4f}{lb - la:+9.4f}")
        if args.save:
            gap = np.full((a.shape[0], 4, 3), 255, np.uint8)
            side = np.concatenate([a, gap, b], axis=1)
            scale = 3
            Image.fromarray(side).resize((side.shape[1] * scale, side.shape[0] * scale),
                                         Image.NEAREST).save(f"{args.save}_{name}.png")
            Image.fromarray(a).resize((a.shape[1] * scale, a.shape[0] * scale),
                                      Image.NEAREST).save(f"{args.save}_{name}_print.png")
            Image.fromarray(b).resize((b.shape[1] * scale, b.shape[0] * scale),
                                      Image.NEAREST).save(f"{args.save}_{name}_frame.png")

    if args.shapes:
        # The dark ink (bar outlines, the fan's black interior) is the silhouette a
        # luminance mean cannot check: compare the two binary masks and search the
        # integer offset. (0,0) is the claim; the IoU says how much of the edge is
        # the print's own lossy ringing rather than a placement error.
        print(f"\n{'element':<14}{'ink px':>8}{'best offset':>14}{'IoU':>8}{'err at (0,0)':>14}")
        for name, box in SHAPES.items():
            a, b = crop_pair(print_img, frame, *box)
            if a is None:
                continue
            pa, pb = luminance(a) < 50, luminance(b) < 50
            best = min(((int((np.roll(np.roll(pb, oy, 0), ox, 1) ^ pa).sum()), ox, oy)
                        for oy in range(-6, 7) for ox in range(-6, 7)))
            union = int((pa | pb).sum())
            iou = float((pa & pb).sum()) / union if union else 0.0
            print(f"{name:<14}{int(pa.sum()):>8}{f'({best[1]:+d},{best[2]:+d})':>14}{iou:>8.3f}"
                  f"{int((pa ^ pb).sum()):>14}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
