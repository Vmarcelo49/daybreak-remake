#!/usr/bin/env python3
"""Trace the battle HUD's bitmap text into resolution-independent SVGs.

WHY this exists: every in-battle HUD word is texture art, not text
(BATTLE-HUD-SPEC.md section 4: no LIMIT/CHARGE/STAMINA/OYASHIRO string occurs
in DaybreakDX.exe, only the glyph art in data/object/P00..P03.cnv). The
current port therefore cannot "re-font" the HUD - it must either keep
sampling the 512x512 game atlases (which blur past 800x600) or carry a
vector future of the lettering. This script produces that future's first
artifacts: potrace-traced outlines of every HUD glyph, color-matched to
sampled atlas hex, with 1x/4x PNG previews proving they scale.

WHAT it does: decode the shipped .cnv sheets (the same layout
remake/tools/asset-tools/cnv_convert.py documents: byte 0 = bpp, +5 u32
height, +9 u32 width, +13 u32 compressed, +17 pixel data, 32bpp BGRA),
cut the glyph cells named in src/ui/hud_atlas.h's font table
(FUN_00642510 @0x00642510 builds the fonts, FUN_00431b50 @0x00431b50 lays
the right-aligned runs), threshold each cell to a mask, upscale 3x and
trace with potrace, then emit one .svg per glyph plus preview renders
via rsvg-convert at native cell size (1x) and 4x.

Game data is NEVER committed: the script reads the local install through
DAYBREAK_DATA (default: the repo's gitignored Higurashi-Daybreak/data
tree, resolved relative to this file) and writes only the traced SVGs
and their previews next to itself. Needs: python3 + PIL, potrace,
rsvg-convert (both are stock distro packages).

Usage:
    python3 trace_hud.py            # writes svg/ and previews/ beside itself
    DAYBREAK_DATA=/path/to/data python3 trace_hud.py
"""

import os
import struct
import subprocess
import sys

try:
    from PIL import Image, ImageFilter
except ImportError:
    sys.exit("trace_hud: need PIL (python3-pil)")

HERE = os.path.dirname(os.path.abspath(__file__))
DATA = os.environ.get(
    "DAYBREAK_DATA",
    os.path.normpath(os.path.join(HERE, "..", "..", "..", "..",
                                  "Higurashi-Daybreak", "data")),
)
SVG_DIR = os.path.join(HERE, "svg")
PREV_DIR = os.path.join(HERE, "previews")
UPSCALE = 3  # trace at 3x for smoother beziers; SVG scales back down


def decode_cnv(path):
    """Raw .cnv image -> PIL RGBA, top-down. Uncompressed 32bpp only."""
    with open(path, "rb") as f:
        d = f.read()
    bpp = d[0]
    h = struct.unpack_from("<I", d, 5)[0]
    w = struct.unpack_from("<I", d, 9)[0]
    comp = struct.unpack_from("<I", d, 13)[0]
    if bpp != 32 or comp != 0:
        raise ValueError("%s: only uncompressed 32bpp supported (%d/%d)"
                         % (path, bpp, comp))
    px = d[17:17 + w * h * 4]
    # 32bpp BGRA per BATTLE-HUD-SPEC.md section 7 (cnv_convert.py agrees);
    # rows are top-down: P00's green digit band lands at y245-276, which is
    # where hud_atlas.h's SmallGreen base (0,256) says it is.
    img = Image.frombytes("RGBA", (w, h), bytes(px), "raw", "BGRA")
    return img


def mask_of(cell, thresh=100, mode="flat"):
    """Cell RGBA -> bilevel mask for potrace (ink BLACK, ground white:

    potrace traces the black pixels, so the glyph ink maps to 0).
    mode "flat" thresholds the luminance (single-ink art on black);
    mode "edge" traces the FIND_EDGES response instead, which is how the
    multi-color P03 badge cells (yellow fill, orange rim, white dashes on
    one plate) become one outline plate."""
    g = cell.convert("RGB").convert("L")
    if mode == "edge":
        g = g.filter(ImageFilter.FIND_EDGES)
    return g.point(lambda v: 0 if v >= thresh else 255)


def trace_cell(name, cell, fill, thresh=100, turd=4, mode="flat",
               native=None):
    """Threshold, upscale, potrace, and write svg/<name>.svg. Returns path.

    The SVG keeps potrace's own 3x coordinate space (viewBox) so no
    precision is lost; data-native-size records the atlas cell it stands
    for, and rsvg -w/-h (see preview()) does the sizing."""
    m = mask_of(cell, thresh, mode)
    w, h = m.size
    big = m.resize((w * UPSCALE, h * UPSCALE), Image.NEAREST)
    pbm = os.path.join("/tmp", "hudtrace_%s.pbm" % name)
    big.save(pbm)
    r = subprocess.run(
        ["potrace", pbm, "-s", "--turdsize", str(turd),
         "--alphamax", "1.0", "--opttolerance", "0.4", "-o", "-"],
        capture_output=True, check=True, text=True)
    svg = r.stdout
    # potrace emits <g transform="translate(..) scale(..,-..)" ...> with
    # fill="#000000": pin the sampled ink color and record provenance.
    svg = svg.replace("<svg", "<svg data-glyph='%s'" % name, 1)
    svg = svg.replace('fill="#000000"',
                      'fill="%s" data-sampled-ink="%s"' % (fill, fill))
    if native is not None:
        svg = svg.replace("<svg",
                          '<svg data-native-size="%dx%d"' % native, 1)
    out = os.path.join(SVG_DIR, name + ".svg")
    lines = svg.split("\n", 1)
    head = lines[0] + "\n<!-- traced from data/object/P00..P03.cnv via " \
        "docs/hud-vectors/trace_hud.py; fill = sampled atlas ink -->\n"
    with open(out, "w") as f:
        f.write(head + lines[1])
    return out


def compare_strip(sheet_img, box, stems, out_name, scale=4):
    """Original atlas strip over the 4x vector renders: the review plate."""
    o = sheet_img.crop(box)
    o = o.resize((o.width * scale, o.height * scale), Image.NEAREST)
    vecs = []
    for s in stems:
        v = Image.open(os.path.join(PREV_DIR, s + "-4x.png")).convert("RGB")
        vecs.append(v)
    vw = max(v.width for v in vecs)
    comp = Image.new("RGB", (max(o.width, vw), o.height + 8 +
                             sum(v.height for v in vecs)), (0, 0, 0))
    comp.paste(o, (0, 0))
    y = o.height + 8
    for v in vecs:
        comp.paste(v, (0, y))
        y += v.height
    comp.save(os.path.join(PREV_DIR, out_name))


def preview(svg_path, stem, w, h):
    """rsvg-render at native size and 4x; return (1x, 4x) PNG paths."""
    p1 = os.path.join(PREV_DIR, stem + "-1x.png")
    p4 = os.path.join(PREV_DIR, stem + "-4x.png")
    subprocess.run(["rsvg-convert", "-w", str(w), "-h", str(h),
                    "-o", p1, svg_path], check=True)
    subprocess.run(["rsvg-convert", "-w", str(w * 4), "-h", str(h * 4),
                    "-o", p4, svg_path], check=True)
    return p1, p4


# (svg stem, sheet file, atlas box (x0,y0,x1,y1), sampled ink, threshold)
# Boxes are the FUN_00642510 / FUN_00642a00 cells from hud_atlas.h and
# BATTLE-HUD-SPEC.md section 3; inks were sampled off the shipped atlases
# (brightest interior texels; see HUD-FONTS-VECTOR.md section 2).
GLYPHS = (
    # P00 big white digits: 64x64 cells from (0,0), 8/row; row1 = 8 9 % /
    [("digit-white-%d" % d, "object/p00.cnv",
      (d * 64, 0, d * 64 + 64, 64), "#FFFFFF", 100) for d in range(8)]
    + [("digit-white-8", "object/p00.cnv", (0, 64, 64, 128), "#FFFFFF", 100),
       ("digit-white-9", "object/p00.cnv", (64, 64, 128, 128), "#FFFFFF", 100),
       ("digit-white-pct", "object/p00.cnv",
        (320, 64, 384, 128), "#FFFFFF", 100),
       ("digit-white-slash", "object/p00.cnv",
        (384, 64, 448, 128), "#FFFFFF", 100)]
    # P00 big red digits: same grid one band down (y118-215 per SPEC section 3)
    + [("digit-red-%d" % d, "object/p00.cnv",
        (d * 64, 118, d * 64 + 64, 182), "#FF0000", 80) for d in range(8)]
    + [("digit-red-8", "object/p00.cnv",
        (0, 175, 64, 239), "#FF0000", 80),
       ("digit-red-9", "object/p00.cnv",
        (64, 175, 128, 239), "#FF0000", 80),
       ("digit-red-pct", "object/p00.cnv",
        (320, 182, 384, 246), "#FF0000", 80)]
    # P00 small green / yellow: 32x32 cells, 15/row, digits then + - . %
    + [("digit-green-%s" % s, "object/p00.cnv",
        (i * 32, 245, i * 32 + 32, 277), "#1BFFA1", 80)
       for i, s in enumerate("0123456789+-.%")]
    + [("digit-yellow-%s" % s, "object/p00.cnv",
        (i * 32, 280, i * 32 + 32, 312), "#FFFF28", 80)
       for i, s in enumerate("0123456789+-.%")]
    # P00 words: LIMIT label sprite (384,320,96,32), MAX art (392,404,112,82)
    + [("word-limit", "object/p00.cnv",
        (384, 320, 480, 352), "#FFFFFF", 100),
       ("word-max", "object/p00.cnv",
        (392, 404, 504, 486), "#FF5A0F", 80)]
    # P01 bar words (white italic caps baked into the bar art)
    + [("word-main", "object/P01.cnv",
        (185, 138, 252, 162), "#FFFFFF", 100),
       ("word-charge", "object/P01.cnv",
        (180, 74, 252, 98), "#FFFFFF", 100),
       ("word-hp", "object/P01.cnv",
        (228, 199, 286, 221), "#FFFFFF", 100),
       ("word-stamina", "object/P01.cnv",
        (95, 12, 225, 48), "#FFFFFF", 100),
       ("word-oyashiro", "object/P01.cnv",
        (8, 376, 132, 410), "#FFFFFF", 100)]
    # P03 command cells: 128x64, cells 0..5 (SPEC section 6 Q2, hud_atlas.h:77).
    # Traced as edge plates (badge + glyphs + dash boxes as outlines); the
    # two inks are recorded in HUD-FONTS-VECTOR.md (fill #FFF050, rim #FF9000).
    + [("cmd-%d" % i, "object/p03.cnv",
        ((i % 4) * 128, (i // 4) * 64, (i % 4 + 1) * 128, (i // 4) * 64 + 64),
        "#FF9000", 30, "edge") for i in range(6)]
    # system.cnv chrome rows: OVER KILL!! / DOWN! / PAUSE (SPEC section 3).
    + [("sting-overkill", "object/system.cnv",
        (0, 0, 512, 64), "#FF1000", 80),
       ("sting-down", "object/system.cnv",
        (0, 64, 256, 128), "#00FF00", 80),
       ("sting-pause", "object/system.cnv",
        (256, 64, 512, 128), "#A0B0F0", 80)]
)


def main():
    os.makedirs(SVG_DIR, exist_ok=True)
    os.makedirs(PREV_DIR, exist_ok=True)
    cache = {}
    for entry in GLYPHS:
        stem, sheet, box, fill, thresh = entry[:5]
        mode = entry[5] if len(entry) > 5 else "flat"
        if sheet not in cache:
            p = os.path.join(DATA, sheet)
            if not os.path.exists(p):
                # extracted trees keep the lowercase spelling either way
                alt = os.path.join(DATA, sheet.lower())
                p = alt if os.path.exists(alt) else p
            cache[sheet] = decode_cnv(p)
        cell = cache[sheet].crop(box)
        svg = trace_cell(stem, cell, fill, thresh, mode=mode,
                         native=cell.size)
        preview(svg, stem, cell.size[0], cell.size[1])
        key = stem.rsplit("-", 1)[0] if "-" in stem and \
            stem.split("-")[-1].isdigit() else stem.split("-")[0]
        print("traced %-22s box=%s fill=%s mode=%s" % (stem, box, fill, mode))
    p00 = cache["object/p00.cnv"]
    p01 = cache["object/P01.cnv"]
    p03 = cache["object/p03.cnv"]
    sys = cache["object/system.cnv"]
    compare_strip(p00, (0, 0, 512, 64),
                  ["digit-white-%d" % d for d in range(8)],
                  "COMPARE-white-row.png")
    compare_strip(p00, (0, 245, 320, 277),
                  ["digit-green-%s" % s for s in "0123456789"],
                  "COMPARE-green-row.png")
    compare_strip(p00, (0, 280, 320, 312),
                  ["digit-yellow-%s" % s for s in "0123456789"],
                  "COMPARE-yellow-row.png")
    compare_strip(p00, (0, 118, 512, 160),
                  ["digit-red-%d" % d for d in range(8)],
                  "COMPARE-red-row.png")
    for stem, sheet, box in [("word-limit", p00, (384, 320, 480, 352)),
                             ("word-max", p00, (392, 404, 504, 486)),
                             ("word-main", p01, (185, 138, 252, 162)),
                             ("word-hp", p01, (228, 199, 286, 221)),
                             ("cmd-0", p03, (0, 0, 128, 64)),
                             ("sting-overkill", sys, (0, 0, 512, 64)),
                             ("sting-down", sys, (0, 64, 256, 128)),
                             ("sting-pause", sys, (256, 64, 512, 128))]:
        o = sheet.crop(box)
        o = o.resize((o.width * 4, o.height * 4), Image.NEAREST)
        v = Image.open(os.path.join(PREV_DIR, stem + "-4x.png")).convert("RGB")
        comp = Image.new("RGB", (max(o.width, v.width), o.height + 8 + v.height),
                         (0, 0, 0))
        comp.paste(o, (0, 0))
        comp.paste(v, (0, o.height + 8))
        comp.save(os.path.join(PREV_DIR, "COMPARE-%s.png" % stem))
    print("svg: %s  previews: %s" % (SVG_DIR, PREV_DIR))


if __name__ == "__main__":
    main()
