#!/usr/bin/env python3
"""Builds assets/fonts/daybreak-latin.ttf, the Latin face for translated menus and HUD.

The game's own wide italic lettering exists only for the words it uses, mostly at 16 px, so tracing
it would give a partial alphabet with uneven weight. Each glyph here is instead a centre line, swept
with one stroke width, then sheared. The proportions were read from data/object/system.

    usage: build_daybreak_font.py [output.ttf]
"""
import math
import sys
from pathlib import Path

import cv2
import numpy as np
from fontTools.fontBuilder import FontBuilder
from fontTools.pens.ttGlyphPen import TTGlyphPen

UPM = 1000
CAP = 700        # cap height
STROKE = 205
RADIUS = 190     # of a rounded corner, on the centre line
SHEAR = 0.32     # x per y; the study of data/object/system fitted about 0.4 at its grid's edge
GAP = 22         # between glyphs
WIDE, MID, NARROW = 840, 620, 205
SCALE = 2        # raster pixels per font unit
EPSILON = 1.4    # contour simplification, in raster pixels

# Each stroke is a list of (u, v) points on a unit box, or (u, v, "s") for a sharp corner. "closed"
# makes a loop. A point needs no flag at a stroke's ends.
O = [(0, 0), (1, 0), (1, 1), (0, 1), "closed"]
GLYPHS = {
    "A": (WIDE, [[(0, 0, "s"), (0.3, 1), (1, 1), (1, 0)], [(0.13, 0.36), (1, 0.36)]]),
    "B": (WIDE, [[(0, 0, "s"), (0, 1, "s"), (0.9, 1), (0.9, 0.52), (0, 0.52)],
                 [(0.5, 0.52), (1, 0.52), (1, 0), (0, 0)]]),
    "C": (WIDE, [[(1, 1), (0, 1), (0, 0), (1, 0)]]),
    "D": (WIDE, [[(0, 0, "s"), (0, 1, "s"), (1, 1), (1, 0), "closed"]]),
    "E": (WIDE, [[(1, 1), (0, 1), (0, 0), (1, 0)], [(0, 0.5), (0.9, 0.5)]]),
    "F": (WIDE, [[(1, 1), (0, 1), (0, 0)], [(0, 0.5), (0.85, 0.5)]]),
    "G": (WIDE, [[(1, 1), (0, 1), (0, 0), (1, 0), (1, 0.48, "s"), (0.5, 0.48)]]),
    "H": (WIDE, [[(0, 0), (0, 1)], [(1, 0), (1, 1)], [(0, 0.5), (1, 0.5)]]),
    "I": (NARROW, [[(0.5, 0), (0.5, 1)]]),
    "J": (WIDE, [[(1, 1), (1, 0), (0, 0), (0, 0.28)]]),
    "K": (WIDE, [[(0, 0), (0, 1)], [(1, 1), (0, 0.5, "s"), (1, 0)]]),
    "L": (WIDE, [[(0, 1), (0, 0), (1, 0)]]),
    "M": (1060, [[(0, 0), (0, 1), (1, 1), (1, 0)], [(0.5, 0), (0.5, 1)]]),
    "N": (WIDE, [[(0, 0), (0, 1), (1, 1), (1, 0)]]),
    "O": (WIDE, [O]),
    "P": (WIDE, [[(0, 0), (0, 1, "s"), (1, 1), (1, 0.42), (0, 0.42)]]),
    "Q": (WIDE, [O, [(0.62, 0.22), (1.04, -0.08)]]),
    "R": (WIDE, [[(0, 0), (0, 1, "s"), (1, 1), (1, 0.48), (0, 0.48)], [(0.5, 0.48), (1, 0)]]),
    "S": (WIDE, [[(1, 1), (0, 1), (0, 0.5), (1, 0.5), (1, 0), (0, 0)]]),
    "T": (WIDE, [[(0, 1), (1, 1)], [(0.5, 0), (0.5, 1)]]),
    "U": (WIDE, [[(0, 1), (0, 0), (1, 0), (1, 1)]]),
    "V": (WIDE, [[(0, 1), (0, 0.42, "s"), (0.5, 0, "s"), (1, 0.42, "s"), (1, 1)]]),
    "W": (1060, [[(0, 1), (0, 0), (1, 0), (1, 1)], [(0.5, 0), (0.5, 1)]]),
    "X": (WIDE, [[(0, 0), (1, 1)], [(1, 0), (0, 1)]]),
    "Y": (WIDE, [[(0, 1), (0, 0.42), (1, 0.42), (1, 1)], [(0.5, 0), (0.5, 0.42)]]),
    "Z": (WIDE, [[(0, 1), (1, 1, "s"), (0, 0, "s"), (1, 0)]]),
    "0": (WIDE, [O]),
    "1": (MID, [[(0.1, 0.8), (0.65, 1, "s"), (0.65, 0)]]),
    "2": (WIDE, [[(0, 1), (1, 1), (1, 0.5), (0, 0.5), (0, 0), (1, 0)]]),
    "3": (WIDE, [[(0, 1), (1, 1), (1, 0), (0, 0)], [(0.2, 0.5), (1, 0.5)]]),
    "4": (WIDE, [[(0, 1), (0, 0.4, "s"), (1, 0.4)], [(0.8, 0), (0.8, 0.75)]]),
    "5": (WIDE, [[(1, 1), (0, 1, "s"), (0, 0.5), (1, 0.5), (1, 0), (0, 0)]]),
    "6": (WIDE, [[(1, 1), (0, 1), (0, 0), (1, 0), (1, 0.5), (0, 0.5)]]),
    "7": (WIDE, [[(0, 1), (1, 1, "s"), (0.4, 0)]]),
    "8": (WIDE, [O, [(0, 0.5), (1, 0.5)]]),
    "9": (WIDE, [[(0, 0), (1, 0), (1, 1), (0, 1), (0, 0.5), (1, 0.5)]]),
    "!": (NARROW, [[(0.5, 0.3), (0.5, 1)], [(0.5, 0), (0.5, 0.13)]]),
    "?": (MID, [[(0, 1), (1, 1), (1, 0.5), (0.5, 0.5), (0.5, 0.3)], [(0.5, 0), (0.5, 0.13)]]),
    ".": (NARROW, [[(0.5, 0), (0.5, 0.13)]]),
    ",": (NARROW, [[(0.5, 0.13), (0.5, -0.12)]]),
    ":": (NARROW, [[(0.5, 0), (0.5, 0.13)], [(0.5, 0.55), (0.5, 0.68)]]),
    "'": (NARROW, [[(0.5, 0.75), (0.5, 1)]]),
    "-": (MID, [[(0, 0.5), (1, 0.5)]]),
    "+": (MID, [[(0, 0.5), (1, 0.5)], [(0.5, 0.15), (0.5, 0.85)]]),
    "/": (MID, [[(0, 0), (1, 1)]]),
    "%": (WIDE, [[(0.05, 0), (0.95, 1)], [(0, 0.62), (0.3, 0.62), (0.3, 1), (0, 1), "closed"],
                 [(0.7, 0), (1, 0), (1, 0.38), (0.7, 0.38), "closed"]]),
    "&": (WIDE, [[(1, 0), (0.1, 0.75), (0.1, 1), (0.8, 1), (0.8, 0.75), (0, 0.32), (0, 0), (0.8, 0), (1, 0.3)]]),
    "(": (NARROW * 2, [[(1, 1.05), (0, 1.05), (0, -0.05), (1, -0.05)]]),
    ")": (NARROW * 2, [[(0, 1.05), (1, 1.05), (1, -0.05), (0, -0.05)]]),
}


def centre_line(stroke, width):
    """The stroke in font units, with its rounded corners expanded to arcs."""
    closed = stroke[-1] == "closed"
    points = stroke[:-1] if closed else stroke
    inset = STROKE / 2
    span_x = width - STROKE
    span_y = CAP - STROKE
    placed = [(inset + p[0] * span_x, inset + p[1] * span_y, len(p) > 2) for p in points]
    out = []
    count = len(placed)
    for i, (x, y, sharp) in enumerate(placed):
        is_end = not closed and i in (0, count - 1)
        if sharp or is_end:
            out.append((x, y))
            continue
        ax, ay, _ = placed[(i - 1) % count]
        bx, by, _ = placed[(i + 1) % count]
        la, lb = math.hypot(ax - x, ay - y), math.hypot(bx - x, by - y)
        r = min(RADIUS, la / 2.05, lb / 2.05)
        ux, uy = (ax - x) / la, (ay - y) / la
        vx, vy = (bx - x) / lb, (by - y) / lb
        for k in range(13):
            t = k / 12
            # A quadratic through the corner reads as the game's soft squared curve.
            px = (1 - t) ** 2 * (x + ux * r) + 2 * t * (1 - t) * x + t ** 2 * (x + vx * r)
            py = (1 - t) ** 2 * (y + uy * r) + 2 * t * (1 - t) * y + t ** 2 * (y + vy * r)
            out.append((px, py))
    if closed:
        out.append(out[0])
    return out


def to_pixels(x, y, margin, height):
    return ((x + SHEAR * y) * SCALE + margin, height - (y * SCALE + margin))


def sweep(canvas, line, margin, height, closed_join):
    half = STROKE / 2
    for (x0, y0), (x1, y1) in zip(line, line[1:]):
        length = math.hypot(x1 - x0, y1 - y0)
        if length < 1e-6:
            continue
        nx, ny = -(y1 - y0) / length * half, (x1 - x0) / length * half
        quad = [(x0 + nx, y0 + ny), (x1 + nx, y1 + ny), (x1 - nx, y1 - ny), (x0 - nx, y0 - ny)]
        pts = np.array([to_pixels(px, py, margin, height) for px, py in quad], dtype=np.int32)
        cv2.fillConvexPoly(canvas, pts, 255, lineType=cv2.LINE_8)
    # The joints: a disc in the sheared space is an ellipse, drawn as a polygon.
    joints = line[1:-1] if not closed_join else line
    for x, y in joints:
        circle = [(x + half * math.cos(a), y + half * math.sin(a))
                  for a in np.linspace(0, 2 * math.pi, 28, endpoint=False)]
        pts = np.array([to_pixels(px, py, margin, height) for px, py in circle], dtype=np.int32)
        cv2.fillConvexPoly(canvas, pts, 255, lineType=cv2.LINE_8)


def draw_glyph(width, strokes):
    pen = TTGlyphPen(None)
    margin = 400
    height = (CAP + 800) * SCALE
    canvas = np.zeros((height, int((width + 900) * SCALE)), dtype=np.uint8)
    for stroke in strokes:
        sweep(canvas, centre_line(stroke, width), margin, height, stroke[-1] == "closed")
    contours, hierarchy = cv2.findContours(canvas, cv2.RETR_CCOMP, cv2.CHAIN_APPROX_NONE)
    for contour, info in zip(contours, hierarchy[0]):
        approx = cv2.approxPolyDP(contour, EPSILON, True)[:, 0, :]
        points = [(int(round((px - margin) / SCALE)), int(round((height - py - margin) / SCALE)))
                  for px, py in approx]
        is_hole = info[3] >= 0
        area = sum(a[0] * b[1] - b[0] * a[1] for a, b in zip(points, points[1:] + points[:1]))
        # TrueType fills clockwise outlines and cuts counter-clockwise holes.
        if (area > 0) != is_hole:
            points.reverse()
        pen.moveTo(points[0])
        for point in points[1:]:
            pen.lineTo(point)
        pen.closePath()
    return pen.glyph()


def main():
    output = Path(sys.argv[1]) if len(sys.argv) > 1 else Path(__file__).resolve().parents[2] / "assets/fonts/daybreak-latin.ttf"
    glyphs = {".notdef": TTGlyphPen(None).glyph(), "space": TTGlyphPen(None).glyph()}
    metrics = {".notdef": (500, 0), "space": (360, 0)}
    cmap = {32: "space"}
    extra = int(SHEAR * CAP)
    for char, (width, strokes) in GLYPHS.items():
        name = f"u{ord(char):04X}"
        glyphs[name] = draw_glyph(width, strokes)
        metrics[name] = (width + GAP + extra // 3, 0)
        cmap[ord(char)] = name
        if char.isalpha():
            cmap[ord(char.lower())] = name  # unicase, like the game's lettering

    builder = FontBuilder(UPM, isTTF=True)
    builder.setupGlyphOrder(list(glyphs))
    builder.setupCharacterMap(cmap)
    builder.setupGlyf(glyphs)
    glyf = builder.font["glyf"]
    builder.setupHorizontalMetrics({name: (adv, glyf[name].xMin if glyf[name].numberOfContours else 0)
                                    for name, (adv, _) in metrics.items()})
    builder.setupHorizontalHeader(ascent=900, descent=-250)
    builder.setupNameTable({"familyName": "Daybreak Latin", "styleName": "Regular"})
    builder.setupOS2(sTypoAscender=900, sTypoDescender=-250, usWinAscent=900, usWinDescent=250)
    builder.setupPost(italicAngle=-math.degrees(math.atan(SHEAR)))
    output.parent.mkdir(parents=True, exist_ok=True)
    builder.save(output)
    print(f"{output}: {len(glyphs)} glyphs")


if __name__ == "__main__":
    main()
