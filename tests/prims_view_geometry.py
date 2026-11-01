#!/usr/bin/env python3
"""Pin that a split-screen cell's debug overlay is drawn with ITS OWN view (issue #61).

What was wrong: `render::DebugPrims` gave every pass of a frame the same vertex buffer at
offset 0 AND the same `viewProj` uniform slot at offset 0. A frame records all of its
passes into one command buffer and submits once, so every write happened before the
submission and every pass read the LAST pass's vertices and the LAST view's matrix. In a
four-view frame that put one view's crosses in all four cells, at the same cell-local
pixel, while the cameras of those cells looked at different fighters.

The oracle: the demo prints, per view, where each cross belongs in that view's own cell
(`[prims] view N: cell=... target=... desired=...`), projected with the same `viewProj` the
pass received — the same kind of per-view evidence `[split]`'s ring anchors are for
hud_view_geometry.py. This suite is not satisfied with "the crosses moved": a cell drawing
another view's matrix still lands somewhere plausible.

Why the cyan cross, and why some cells are allowed to be empty: the cyan cross marks
`app.arenaDesired`, the arena camera's own eye, and the follow cameras of a match look
mostly BELOW it. In this recipe its own projection lands above three cells and behind the
fourth, so a correct frame draws it in one cell only — the defect's "same cross in every
cell" was itself the artefact. Hence a two-sided verdict over four cells:

  * a cell whose own projection is on-screen (or within VISIBLE of an edge, where an arm of
    the cross can still reach in) must carry cyan at that point, and every cyan pixel of
    the cell must belong to that cross (within REACH of it);
  * a cell whose own projection is further outside than that must carry no cyan at all.

The second half is what the defect violated, and the first half keeps the suite from
passing by drawing nothing.

Usage:
    prims_view_geometry.py <daybreak> <install-dir> [workdir]

Exit 0 when every verdict holds, 1 otherwise, and 77 (skip) when the renderer or the
install is unavailable, so a box without a GPU adapter or the game data does not report a
false failure.
"""
import os
import re
import sys
import tempfile

from capture_probe import (CaptureFailed, main_guard, read_ppm, require_install,
                           run_demo)

# The four-view recipe: match frame 300. Four fighters spread over the stage, so the four
# follow cameras differ by hundreds of world units and a shared matrix cannot hide.
FRAMES = 300
WIDTH, HEIGHT = 960, 540
# A projected centre this far outside a cell can still put pixels inside it, because the
# cross is arms, not a dot: the measured stub at frame 300 starts 7.5 px above its cell and
# covers 8 px of it.
VISIBLE = 30.0
# A cell's own cross must have a pixel this close to its projected centre — the arms meet
# there, so a drawn cross covers the centre itself.
SLACK = 6.0
# All of a cell's cyan must lie this far from its own centre, so a cross drawn for another
# view cannot satisfy this cell's check.
REACH = 60.0
# Pure cyan: the debug pass writes kCyan (0x00FFFF) with full alpha over the frame, so a
# drawn cross is exactly that. The stage's blues (sky, water, cloth) are never this
# saturated in green and blue at once; measured, a sky sample is about (100,150,220).
def is_cyan(r, g, b):
    return r <= 40 and g >= 200 and b >= 200


VIEW_RE = re.compile(r"\[prims\] view (\d+): cell=\((-?[\d.]+),(-?[\d.]+),(-?[\d.]+),(-?[\d.]+)\) "
                     r"target=(\(-?[\d.]+,-?[\d.]+\)|-) desired=(\(-?[\d.]+,-?[\d.]+\)|-)")
POINT_RE = re.compile(r"\((-?[\d.]+),(-?[\d.]+)\)")
PASSES_RE = re.compile(r"debug prims : .*?(\d+) pass\(es\)")


def parse_report(log):
    """{view: {"cell": (x, y, w, h), "desired": (x, y) or None}} from the demo's own line.

    `desired` is None when the demo reports `-`: the point is at or behind that view's eye,
    so the view draws no cross at all.
    """
    views = {}
    for line in log.splitlines():
        m = VIEW_RE.match(line)
        if not m:
            continue
        point = POINT_RE.match(m.group(7))
        views[int(m.group(1))] = {
            "cell": tuple(float(m.group(i)) for i in range(2, 6)),
            "desired": (float(point.group(1)), float(point.group(2))) if point else None,
        }
    return views


def passes(log):
    m = PASSES_RE.search(log)
    return int(m.group(1)) if m else 0


def cyan_pixels(px, frame_w, frame_h, cell):
    """Every cyan pixel of one cell, in cell-local pixels."""
    ox, oy, cw, ch = cell
    x0, y0 = max(0, int(ox)), max(0, int(oy))
    x1, y1 = min(frame_w, int(ox + cw)), min(frame_h, int(oy + ch))
    out = []
    for y in range(y0, y1):
        row = y * frame_w * 3
        for x in range(x0, x1):
            off = row + x * 3
            if is_cyan(px[off], px[off + 1], px[off + 2]):
                out.append((x - ox, y - oy))
    return out


def distance_outside(point, cw, ch):
    """How far a cell-local point lies outside the cell; 0 when it is inside."""
    x, y = point
    return max(0.0 - x, x - cw, 0.0 - y, y - ch, 0.0)


def clamp_to_cell(point, cw, ch):
    x, y = point
    return min(max(x, 0.0), cw), min(max(y, 0.0), ch)


def verdict(cell, desired, ink):
    """(kind, note, problems) for one view. `ink` is its cyan pixels, cell-local.

    "presence" means this view's own projection lands on its cell, so the cross must be
    there; "absence" means it lands too far outside for an arm to reach in, so the cell must
    be clean. The note is what the run reported, for the log either way.
    """
    _, _, cw, ch = cell
    if desired is None:
        if ink:
            return ("absence", "behind the eye, but %d cyan pixel(s) are in the cell, first at "
                    "(%.0f,%.0f)" % (len(ink), ink[0][0], ink[0][1]), ["stray cyan"])
        return "absence", "behind the eye; no cyan drawn", []
    outside = distance_outside(desired, cw, ch)
    if outside > VISIBLE:
        if ink:
            return ("absence", "its own projection is %.0f px outside the cell, but %d cyan "
                    "pixel(s) are in it, first at (%.0f,%.0f)"
                    % (outside, len(ink), ink[0][0], ink[0][1]), ["stray cyan"])
        return "absence", "its own projection is %.0f px outside the cell; no cyan drawn" % outside, []

    # The cross is arms around a centre, and the cell may clip an arm, so the centre is
    # clamped into the cell before asking whether the drawn ink is this view's own.
    ax, ay = clamp_to_cell(desired, cw, ch)
    problems = []
    near = min(((x - ax) ** 2 + (y - ay) ** 2) ** .5 for x, y in ink) if ink else None
    if near is None:
        problems.append("no cyan at its own projected centre (%.1f,%.1f)" % (ax, ay))
    elif near > SLACK:
        problems.append("nearest cyan is %.1f px from its own projected centre (%.1f,%.1f), "
                        "allowed %.0f" % (near, ax, ay, SLACK))
    far = [(x, y) for x, y in ink if ((x - ax) ** 2 + (y - ay) ** 2) ** .5 > REACH]
    if far:
        problems.append("%d cyan pixel(s) lie beyond %.0f px of this view's own centre, "
                        "e.g. (%.0f,%.0f)" % (len(far), REACH, far[0][0], far[0][1]))
    note = ("cyan on its own centre" if not problems else
            "cyan is not where this view puts it")
    return "presence", note, problems


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    install = sys.argv[2]
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    require_install(install, "prims_view_geometry")
    with tempfile.TemporaryDirectory() as tmp:
        out = os.path.join(tmp, "four.ppm")
        log = run_demo(demo, install, out,
                       ["--screen=battle", "--local-players=4", "--debug-prims",
                        "--camera=arena", "--frames=%d" % FRAMES,
                        "--size=%dx%d" % (WIDTH, HEIGHT)], cwd)
        w, h, px = read_ppm(out)
        views = parse_report(log)
        # The view report is this suite's index: a run that renders four views must report
        # four, so a short list is a failure rather than "nothing to measure".
        if len(views) < 4:
            raise CaptureFailed("the run reported %d views, expected 4" % len(views))

        total_passes = passes(log)
        failures = []
        if total_passes < len(views):
            failures.append("the frame recorded %d prims pass(es) for %d views: each view's "
                            "overlay needs its own pass" % (total_passes, len(views)))

        presence = 0
        for v in sorted(views):
            cell = views[v]["cell"]
            ink = cyan_pixels(px, w, h, cell)
            kind, note, problems = verdict(cell, views[v]["desired"], ink)
            if kind == "presence":
                presence += 1
            print("  view %d: cell=(%.0f,%.0f,%.0f,%.0f) desired=%s cyan=%d -> %s: %s"
                  % (v, cell[0], cell[1], cell[2], cell[3],
                     "-" if views[v]["desired"] is None else
                     "(%.1f,%.1f)" % views[v]["desired"], len(ink), kind, note))
            if problems:
                failures.extend("view %d: %s" % (v, problem) for problem in problems)

        # A recipe whose cross is on-screen nowhere would assert only absences, and could not
        # tell this fix from "the overlay draws nothing". Fail rather than pass vacuously.
        if presence == 0:
            failures.append("no view draws its own cyan cross inside its cell at frame %d: the "
                            "recipe has drifted, so this run cannot show the overlay following "
                            "each view" % FRAMES)

        if failures:
            print("prims_view_geometry: FAIL")
            for line in failures:
                print("  " + line)
            return 1
        print("prims_view_geometry: every cell's overlay follows that cell's own view "
              "(%d view(s), %d prims pass(es))" % (len(views), total_passes))
        return 0


if __name__ == "__main__":
    sys.exit(main_guard(main))
