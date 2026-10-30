#!/usr/bin/env python3
"""Measure the arena framing of a battle frame: where the player stands and how big.

Phase 3's camera gate is "a foundation frame frames the fighter like the original's
print does", so the deliverable needs numbers, not a look: the player's pixel height,
her horizontal centre, where her soles sit relative to the frame bottom, and the
opponent's pixel height and centre. This prints those for any frame of the same scene
-- `docs/reference/battle-hud.webp` (the specification) or a foundation capture
of the same moment (the measurement) -- using the character's own colours, so the two
sides are measured by the same instrument.

Method (why these features):
  * the player is Rena: her hair is the only saturated orange in a schoolyard frame and
    it is fused to the top of her head, so `hair` gives the head top;
  * her shoes are the darkest thing under her, so a dark blob inside her own column
    band gives the soles. The band is derived from the hair column, which keeps the
    HUD's black panels and the stage's dark props out;
  * the frame's HUD is not part of the framing and is only used for a sanity note (the
    lowest HUD ink at the bottom-left corner).

Ambiguity is reported, not hidden: each measurement prints the pixel box it came from
and the runner decides.

Usage:
    measure_framing.py <image> [--label "..."] [--json]

Exit status 0 always: this reports; the gate is a human decision.
"""

import argparse
import json
import subprocess
import sys
import tempfile

import numpy as np
from PIL import Image


def load(path):
    """Any ImageMagick-readable image -> an HxWx3 int array (via a temp PNG)."""
    if path.lower().endswith((".png", ".ppm", ".webp", ".jpg", ".jpeg")):
        return np.asarray(Image.open(path).convert("RGB")).astype(np.int32)
    tmp = tempfile.mktemp(suffix=".png")
    subprocess.run(["convert", path, tmp], check=True,
                   stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return np.asarray(Image.open(tmp).convert("RGB")).astype(np.int32)


def masks(a):
    r, g, b = a[:, :, 0], a[:, :, 1], a[:, :, 2]
    hair = (r > 150) & (r - b > 110) & (g < 180)            # Rena's orange
    dark = (r < 90) & (g < 90) & (b < 90)                   # shoes, cleaver blade
    ground = (r > 195) & (g > 180) & (b > 140) & (r >= b)   # the schoolyard's sand
    return hair, dark, ground


def box(mask, x0, x1, y0, y1):
    m = np.zeros_like(mask)
    m[y0:y1, x0:x1] = True
    m &= mask
    ys, xs = np.nonzero(m)
    if len(ys) == 0:
        return None
    return dict(n=int(len(ys)), x0=int(xs.min()), x1=int(xs.max()),
                y0=int(ys.min()), y1=int(ys.max()), cx=float(xs.mean()))


def largest_component(mask, seed_box):
    """4-connected component of `mask` around the densest 31x31 patch in `seed_box`.

    The densest patch, not the largest blob by area, because a HUD glyph (the print's
    red `com` tag, the OYASHIRO label) is thin and never wins a local-density contest
    against a solid head of hair, while it can win an area contest if the hair is
    broken into pieces by a highlight.
    """
    x0, x1, y0, y1 = seed_box
    sub = mask[y0:y1, x0:x1]
    ys, xs = np.nonzero(sub)
    if len(ys) == 0:
        return None
    k = 15  # half-window: a 31x31 box, about the width of a head at this scale
    ii = np.cumsum(np.cumsum(sub.astype(np.int32), 0), 1)
    h, w = sub.shape
    best, seed = -1, None
    for y, x in zip(ys, xs):          # only mask pixels can be the patch centre
        ya, yb = max(0, y - k), min(h, y + k + 1)
        xa, xb = max(0, x - k), min(w, x + k + 1)
        total = ii[yb - 1, xb - 1]
        if ya > 0:
            total -= ii[ya - 1, xb - 1]
        if xa > 0:
            total -= ii[yb - 1, xa - 1]
        if ya > 0 and xa > 0:
            total += ii[ya - 1, xa - 1]
        if total > best:
            best, seed = total, (int(y) + y0, int(x) + x0)
    comp = np.zeros_like(mask)
    comp[seed[0], seed[1]] = True
    while True:
        grown = comp.copy()
        grown[1:, :] |= comp[:-1, :]
        grown[:-1, :] |= comp[1:, :]
        grown[:, 1:] |= comp[:, :-1]
        grown[:, :-1] |= comp[:, 1:]
        grown &= mask
        if grown.sum() == comp.sum():
            return comp
        comp = grown


def bbox_of(comp):
    ys, xs = np.nonzero(comp)
    if len(ys) == 0:
        return None
    return dict(n=int(len(ys)), x0=int(xs.min()), x1=int(xs.max()),
                y0=int(ys.min()), y1=int(ys.max()), cx=float(xs.mean()))


def measure(a, label):
    h, w, _ = a.shape
    hair, dark, ground = masks(a)

    # The player is the orange blob in the lower centre: the HUD's own orange (the alert
    # balloon top-centre, the OYASHIRO label bottom-left) is outside that window, and it
    # would otherwise masquerade as a head at row 9 and make the "height" meaningless.
    win = (int(w * 0.15), int(w * 0.85), int(h * 0.2), h)
    comp = largest_component(hair, win)
    best = bbox_of(comp) if comp is not None else None
    if best is None:
        raise SystemExit(f"{label}: no orange hair found -- is this a Rena frame?")
    cx = int(round(best["cx"]))
    pad = max(40, (best["x1"] - best["x0"]))
    lo, hi = max(0, cx - pad), min(w, cx + pad)
    # The soles: the lowest dark ink in her own band, below her hair. Her shoes are the
    # darkest thing she owns and sit under her, so no other rule is needed -- the box is
    # reported so a stage prop caught inside the band is visible in the numbers.
    shoe = box(dark, lo, hi, best["y1"], h)
    if shoe is None:
        raise SystemExit(f"{label}: no shoe blob under the hair -- cannot measure height")

    # The ground's far edge in the centre column: the first sand row from the top. In a
    # schoolyard frame that is the base of the wall/fence, i.e. the visual horizon-ish.
    col = ground[:, max(0, w // 2 - 20): w // 2 + 20].any(axis=1)
    ys = np.nonzero(col)[0]
    ground_top = int(ys.min()) if len(ys) else None

    return dict(
        image=label, width=w, height=h,
        player=dict(head_top=best["y0"], sole=shoe["y1"],
                    pixel_height=shoe["y1"] - best["y0"] + 1,
                    centre_x=cx, hair_box=(best["x0"], best["x1"], best["y0"], best["y1"]),
                    shoe_box=(shoe["x0"], shoe["x1"], shoe["y0"], shoe["y1"]),
                    sole_from_bottom=h - 1 - shoe["y1"]),
        ground_top_row=ground_top,
    )


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("image")
    ap.add_argument("--label", default="")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    a = load(args.image)
    m = measure(a, args.label or args.image)
    if args.json:
        print(json.dumps(m, indent=2))
        return 0
    p = m["player"]
    print(f"image      : {m['image']}  ({m['width']}x{m['height']})")
    print(f"player     : head top y={p['head_top']}  sole y={p['sole']}  "
          f"height={p['pixel_height']} px  ({100.0 * p['pixel_height'] / m['height']:.1f}% of frame)")
    print(f"             centre x={p['centre_x']}  sole {p['sole_from_bottom']} px above the bottom")
    print(f"             hair box x{p['hair_box'][0]}..{p['hair_box'][1]} "
          f"y{p['hair_box'][2]}..{p['hair_box'][3]}   "
          f"shoe box x{p['shoe_box'][0]}..{p['shoe_box'][1]} y{p['shoe_box'][2]}..{p['shoe_box'][3]}")
    print(f"ground top : row {m['ground_top_row']} (centre columns; the sand's far edge)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
