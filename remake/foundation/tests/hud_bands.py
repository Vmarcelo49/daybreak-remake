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
    # Balloon corners: the `0%` / `LIMIT 100%` readouts, the label sprite and the
    # balloon tip (print ink (73,83)-(106,103), (116,84)-(142,104), (31,115)-(82,121),
    # (90,111)-(152,122), tip (72,112)-(97,144)).
    "balloon-left":  (25, 75, 140, 80),
    "balloon-right": (655, 75, 140, 80),
    "balloon-tip":   (60, 105, 50, 45),
    # The boxed `適当` command label (print ink (155,503)-(276,537)) and the fan's
    # hypermode caption (print OYASHIRO at (196,558)-(298,569)).
    "command-label": (150, 485, 135, 70),
    "fan-caption":   (180, 550, 125, 25),
    # The per-fighter cluster over the distant fighter: the P06 alert pentagon
    # (print (379,40)-(423,85)), the target's com bar + tag (print bar
    # (356,96)-(443,108), "com" at (412,111)-(439,117)) and the red ring
    # (print (368,130)-(433,195)).
    "alert":         (370, 35, 60, 55),
    "com-bar":       (345, 85, 120, 50),
    "ring":          (355, 120, 90, 90),
    "per-fighter":   (340, 30, 130, 180),
    # STAMINA (print battle-stamina.webp: the frame is centred on (400,517)) and the
    # KO sting (spec §2 item 25: P09 (0,256,512,256) drawn 256x128 centred).
    "stamina":       (295, 480, 210, 75),
    "ko-sting":      (140, 170, 520, 260),
    # scene-only control: no HUD element of either composition is here, so this is
    # the floor a HUD band cannot beat while the framing differs.
    "scene-floor":  (300, 250, 200, 120),
}

# name: ((game x, y, w, h), ink mode) — the sprite rects as drawn, for the shape
# comparison. The mode picks the mask: "dark" for bar outlines and the fan's black
# interior, "bright" for pale fills, "yellow" for the boxed `適当` label (whose yellow
# would otherwise be swamped by bright sand behind it in the print).
SHAPES = {
    "main-pill":     ((607, 442, 192, 64), "dark"),
    "charge-pill":   ((581, 490, 192, 64), "dark"),
    "hp-pill":       ((492, 540, 256, 60), "dark"),
    "fan":           ((10, 467, 300, 128), "dark"),
    # The per-fighter cluster: the com bar's black interior, the ring's outline, the
    # pale com-bar fill and the red ring's own ink.
    "com-bar":       ((352, 92, 96, 22), "dark"),
    "ring":          ((362, 124, 78, 78), "dark"),
    "com-bar-fill":  ((356, 95, 88, 10), "bright"),
    "command-label": ((150, 485, 135, 70), "yellow"),
    # The STAMINA bar's dark frame and its pale fill, measured against
    # battle-stamina.webp (the frame is centred on (400,517): outline (341,499)-(459,525)).
    "stamina":       ((330, 495, 140, 35), "dark"),
    "stamina-fill":  ((340, 505, 120, 22), "bright"),
}

def ink_mask(img, mode):
    lum = luminance(img)
    if mode == "bright":
        return lum > 150
    if mode == "yellow":
        return (img[:, :, 0] > 190) & (img[:, :, 1] > 140) & (img[:, :, 2] < 140)
    return lum < 50


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
    """The band's pixels from both images, in game coordinates, clipped to the game
    rectangle each one actually covers: the frame is 0..w-1, the print covers
    OFF..OFF+size-1 in both axes (so a negative offset, as battle-stamina.webp's is,
    starts at game 0 too)."""
    ph, pw = print_img.shape[:2]
    x0 = max(x, 0, OFF_X)
    y0 = max(y, 0, OFF_Y)
    x1 = min(x + w, frame.shape[1], pw + OFF_X)
    y1 = min(y + h, frame.shape[0], ph + OFF_Y)
    if x1 <= x0 or y1 <= y0:
        return None, None
    return (print_img[y0 - OFF_Y:y1 - OFF_Y, x0 - OFF_X:x1 - OFF_X], frame[y0:y1, x0:x1])


def rmse(a, b):
    d = a.astype(float) - b.astype(float)
    return float(np.sqrt((d ** 2).mean())) / 255.0


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("ppm")
    ap.add_argument("--save", default="")
    ap.add_argument("--bands", default=",".join(BANDS))
    ap.add_argument("--shapes", action="store_true")
    # A second reference print with its own window offset: battle-stamina.webp is the
    # STAMINA bar's reference and shows the per-fighter com bars over both fighters.
    # Its client area sits at (3,26) in an 808x622 window (solved by template-matching
    # the boxed 適当 cell, mean |diff| 31 at scale 1.02), so game = print - (3,26).
    ap.add_argument("--print", default=PRINT)
    ap.add_argument("--off", default="2,-6", help="game = print + (dx,dy)")
    args = ap.parse_args()
    global OFF_X, OFF_Y
    OFF_X, OFF_Y = (int(v) for v in args.off.split(","))

    print_img = np.array(Image.open(args.print).convert("RGB"))
    frame = read_ppm(args.ppm)
    print(f"print       : {args.print} ({print_img.shape[1]}x{print_img.shape[0]}) off {OFF_X},{OFF_Y}")
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
        for name, (box, mode) in SHAPES.items():
            a, b = crop_pair(print_img, frame, *box)
            if a is None or a.shape != b.shape:
                continue
            pa, pb = ink_mask(a, mode), ink_mask(b, mode)
            best = min(((int((np.roll(np.roll(pb, oy, 0), ox, 1) ^ pa).sum()), ox, oy)
                        for oy in range(-6, 7) for ox in range(-6, 7)))
            union = int((pa | pb).sum())
            iou = float((pa & pb).sum()) / union if union else 0.0
            print(f"{name:<14}{int(pa.sum()):>8}{f'({best[1]:+d},{best[2]:+d})':>14}{iou:>8.3f}"
                  f"{int((pa ^ pb).sum()):>14}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
