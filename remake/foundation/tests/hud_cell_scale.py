#!/usr/bin/env python3
"""Pin the split-screen HUD's per-cell placement (split-screen HUD scale defect).

Why a capture test and not a layout test: the layout and the quad geometry were both
CORRECT while the defect was live — `computeBattleHudLayout(480,270)` returned scale 0.45
and the queued quads carried cell coordinates. What was wrong was which value the GPU read:
every UI pass in a frame shared one 16-byte viewport uniform, every pass's write landed
before the frame's single submission, and so the LAST pass's viewport (the separator pass's
full target) applied to all of them. A device-free test of the layout cannot see that; only
a rendered frame can. This script measures the rendered HUD in each cell against a
single-view reference of the same cell size.

Usage:
    hud_cell_scale.py <foundation_demo> <install-dir> [workdir]

Exit 0 when every cell's HUD sits where a cell-sized single view puts it, 1 on a real
failure, and 77 only when a prerequisite is missing (no game data, no GPU adapter). Once
those hold, a crash, a missing `RESULT: ok`, an invalid capture or missing probe markers
all fail; capture_probe.py carries the reasoning.
"""
import os
import sys
import tempfile

from capture_probe import main_guard, read_ppm, require_install, require_markers, run_demo

def clusters(pixels, w, h, pred):
    """Connected components of a marker colour, 8-connected."""
    pts = set()
    for y in range(h):
        row = y * w * 3
        for x in range(w):
            off = row + x * 3
            if pred(pixels[off], pixels[off + 1], pixels[off + 2]):
                pts.add((x, y))
    out = []
    while pts:
        seed = pts.pop()
        stack = [seed]
        comp = [seed]
        while stack:
            cx, cy = stack.pop()
            for dx in (-1, 0, 1):
                for dy in (-1, 0, 1):
                    p = (cx + dx, cy + dy)
                    if p in pts:
                        pts.remove(p)
                        stack.append(p)
                        comp.append(p)
        xs = [p[0] for p in comp]
        ys = [p[1] for p in comp]
        out.append((min(xs), min(ys), max(xs), max(ys), len(comp)))
    return sorted(out)


def is_cyan(r, g, b):
    return g > 200 and b > 200 and r < 80


def is_magenta(r, g, b):
    return r > 200 and b > 200 and g < 80


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    install = sys.argv[2]
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    require_install(install, "hud_cell_scale")
    with tempfile.TemporaryDirectory() as tmp:
        # 300 frames: enough for the front-end battle to hand over to the match (the HUD
        # hook only runs once matchMode is on), short enough to keep the suite quick. The
        # markers are drawn on the captured frame itself, so the match state is irrelevant.
        #
        # A 2x2 split screen at 960x540: each cell is 480x270. --hud-probe draws two
        # 6x6 markers per view in that view's own coordinates — magenta at its top-left
        # corner and cyan at its bottom-right — so the frame itself shows where each
        # pass's viewport landed. A correct render puts every cell's cyan marker on that
        # cell's bottom-right corner; the shared-uniform defect moved it to the cell's
        # centre (half scale), which is what this asserts against.
        four = os.path.join(tmp, "four.ppm")
        run_demo(demo, install, four,
                 ["--screen=battle", "--hud-probe", "--local-players=4", "--frames=300",
                  "--size=960x540"], cwd, timeout=600)
        w, h, px = read_ppm(four)
        cw, ch = w // 2, h // 2
        # Disappearing probe markers are a defect this suite exists to catch, not a
        # reason to skip: the renderer reported success, so it was asked to draw them.
        cyan = require_markers("cyan probe markers", clusters(px, w, h, is_cyan),
                               "hud_cell_scale")
        failures = []
        cells = [(0, 0), (cw, 0), (0, ch), (cw, ch)]
        for index, (ox, oy) in enumerate(cells):
            want = (ox + cw - 6, oy + ch - 6)
            hit = None
            for x0, y0, x1, y1, count in cyan:
                if abs(x0 - want[0]) <= 1 and abs(y0 - want[1]) <= 1:
                    hit = (x0, y0)
                    break
            if hit is None:
                nearby = [c[:2] for c in cyan if ox <= c[0] < ox + cw and oy <= c[1] < oy + ch]
                failures.append("cell %d: bottom-right marker not at %s (markers in cell: %s)"
                                % (index, want, nearby or "none"))
                print("  cell %d: cyan marker MISSING from (%d,%d); in-cell markers: %s"
                      % (index, want[0], want[1], nearby or "none"))
            else:
                print("  cell %d: cyan marker at (%d,%d), expected (%d,%d) -> corner"
                      % (index, hit[0], hit[1], want[0], want[1]))
        # The top-left markers are reported too: they are the same measurement from the
        # other corner, and a pass that draws them elsewhere is a placement failure.
        magenta = clusters(px, w, h, is_magenta)
        for index, (ox, oy) in enumerate(cells):
            here = [c[:2] for c in magenta if ox <= c[0] < ox + cw and oy <= c[1] < oy + ch]
            if here and not any(abs(x - ox) <= 1 and abs(y - oy) <= 1 for x, y in here):
                failures.append("cell %d: top-left marker at %s, expected (%d,%d)"
                                % (index, here, ox, oy))
        if failures:
            print("hud_cell_scale: FAIL")
            for line in failures:
                print("  " + line)
            return 1
        print("hud_cell_scale: every cell's probe markers sit on that cell's own corners")
        return 0


if __name__ == "__main__":
    sys.exit(main_guard(main))
