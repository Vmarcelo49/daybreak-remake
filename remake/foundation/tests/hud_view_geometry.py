#!/usr/bin/env python3
"""Pin that a split-screen cell's HUD is drawn from ITS OWN view's geometry (issue #56).

Why the existing capture test cannot see this: `hud_cell_scale.py` measures each cell's probe
markers, and every pass pushes those at IDENTICAL coordinates in its own view's space — so
whichever view's vertex data a cell ends up reading, the probe still lands on that cell's own
corner. It pins the view -> target mapping and is structurally blind to which view's vertices
a pass read.

What it could not see: one SpriteRenderer hands every pass in a frame the same vertex buffer,
and every `render()` call wrote that buffer at offset 0. All of a frame's queue writes land
before its single submission, so a pass reads the LAST pass's geometry plus the tail of the
longest earlier one. In a four-view frame the separator pass (2 quads) is written last, so
every HUD pass read the separator bars for its first two quads and the last HUD view's
geometry for the rest. Each cell's own reticles were replaced by whichever view wrote last.

This script therefore asserts on the RETICLE, whose anchor is a per-view number: the demo's
own `[split]` report prints every participant's ring anchor in each view's cell pixels (the
same value `composeFighters` draws it at). Enemies use red ink, allies green; the active
player has no reticle. For each other participant whose anchor lands inside its view's cell,
the team-colored reticle must be in the frame at that anchor. Under the defect it is not: it is at
another view's anchor (26-44 px away in this recipe) or nowhere at all.

Usage:
    hud_view_geometry.py <foundation_demo> <install-dir> [workdir]

Exit 0 when every view's reticles sit on that view's own anchors, 1 otherwise, and 77 (skip)
when the renderer or the install is unavailable, so a CI box without a GPU or the game data
does not report a false failure.
"""
import os
import re
import subprocess
import sys
import tempfile

SKIP = 77

# The capture frame and size of the four-view recipe: the countdown holds the round for 180
# ticks, so this is match frame 120 — four fighters spread over the stage, each view's HUD
# carrying four distinct ring anchors, which is what makes the per-view difference readable.
FRAMES = 300
WIDTH, HEIGHT = 960, 540
# An anchor nearer than this to a cell edge is not asserted: the reticle is drawn AROUND its
# anchor, so a clipped one cannot be counted honestly. The cell's own two corners are the
# split-screen separator's, so the margin also keeps the frame's own separator lines out.
MARGIN = 40
# Red reticle ink is counted in this square around an anchor. Measured: a drawn reticle puts
# 80-160 pure-red pixels inside it, an absent one 0-8 (the stage's own reds are neither this
# saturated nor this dense).
RADIUS = 20
MIN_RETICLE_PIXELS = 30
# Pure red: the P03 row 1 ring cell's own ink is (255,0,0). The stage art has reds, but they
# are darker and never form a 30-pixel block at a ring anchor.
def is_red(r, g, b):
    return r > 180 and g < 70 and b < 70


def run_demo(demo, install, out, args, cwd, timeout=900):
    cmd = [demo, "--headless", "--no-devices", "--install=" + install, "--out=" + out] + args
    proc = subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          text=True, timeout=timeout)
    if proc.returncode != 0 or "RESULT: ok" not in proc.stdout:
        return None
    return proc.stdout


def read_ppm(path):
    with open(path, "rb") as handle:
        data = handle.read()
    if not data.startswith(b"P6"):
        return None
    fields = []
    i = 2
    while len(fields) < 3:
        while i < len(data) and data[i:i + 1].isspace():
            i += 1
        if data[i:i + 1] == b"#":
            while data[i:i + 1] not in (b"\n", b""):
                i += 1
            continue
        start = i
        while i < len(data) and not data[i:i + 1].isspace():
            i += 1
        fields.append(int(data[start:i]))
    i += 1
    w, h, _ = fields
    return w, h, data[i:i + w * h * 3]


VIEW_RE = re.compile(r"\[split\] view (\d+): .* "
                     r"cell=\((-?[\d.]+),(-?[\d.]+),(-?[\d.]+),(-?[\d.]+)\)")
RING_RE = re.compile(r"\[split\]   p(\d+) .* role=(\w+).* visible=(\d+) "
                     r".* ring=\((-?[\d.]+),(-?[\d.]+)\)")


def parse_report(log):
    """{view: {"cell": (x, y, w, h), "rings": {participant: (x, y, role, visible)}}} from the
    demo's own per-view evidence line — the values the HUD composition draws with, not a
    guess. Only visible participants other than the active player have rings to measure."""
    views = {}
    current = None
    for line in log.splitlines():
        m = VIEW_RE.match(line)
        if m:
            current = int(m.group(1))
            views[current] = {"cell": tuple(float(m.group(i)) for i in range(2, 6)), "rings": {}}
            continue
        m = RING_RE.match(line)
        if m and current is not None:
            views[current]["rings"][int(m.group(1))] = (float(m.group(4)), float(m.group(5)),
                                                        m.group(2), m.group(3) == "1")
    return views


def ring_pixels(px, w, h, x0, y0, x1, y1, role):
    """Enemy red or ally green ink inside a clamped region of the frame."""
    out = []
    for y in range(max(0, y0), min(h, y1)):
        row = y * w * 3
        for x in range(max(0, x0), min(w, x1)):
            off = row + x * 3
            if (is_red(px[off], px[off + 1], px[off + 2]) if role == "enemy"
                    else px[off + 1] > 180 and px[off] < 70 and px[off + 2] < 70):
                out.append((x, y))
    return out


def count_near(px, w, h, cell, ax, ay, radius, role):
    ox, oy = cell
    return len(ring_pixels(px, w, h, int(ox + ax - radius), int(oy + ay - radius),
                           int(ox + ax + radius) + 1, int(oy + ay + radius) + 1, role))


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    install = sys.argv[2]
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    if not os.path.exists(os.path.join(install, "data")):
        print("hud_view_geometry: no game data at %s, skipped" % install)
        return SKIP
    with tempfile.TemporaryDirectory() as tmp:
        out = os.path.join(tmp, "four.ppm")
        log = run_demo(demo, install, out,
                       ["--screen=battle", "--local-players=4", "--frames=%d" % FRAMES,
                        "--size=%dx%d" % (WIDTH, HEIGHT)], cwd)
        if log is None:
            print("hud_view_geometry: headless renderer unavailable, skipped")
            return SKIP
        got = read_ppm(out)
        if got is None:
            print("hud_view_geometry: capture is not a PPM, skipped")
            return SKIP
        w, h, px = got
        views = parse_report(log)
        if len(views) < 4:
            print("hud_view_geometry: the run did not report four views (%d), skipped"
                  % len(views))
            return SKIP
        cells = {}
        for v, entry in views.items():
            cx, cy, cw, ch = entry["cell"]
            cells[v] = (int(cx), int(cy), int(cw), int(ch))

        failures = []
        measured = 0
        # Every visible non-owner reticle must use this view's own projected anchor.
        for v in sorted(views):
            ox, oy, cw, ch = cells[v]
            for p, (ax, ay, role, visible) in sorted(views[v]["rings"].items()):
                if not visible or role == "owner":
                    continue
                if not (MARGIN <= ax <= cw - MARGIN and MARGIN <= ay <= ch - MARGIN):
                    continue          # clipped by the cell: not a fair measurement
                n = count_near(px, w, h, (ox, oy), ax, ay, RADIUS, role)
                measured += 1
                print("  view %d p%d (%s) anchor=(%.0f,%.0f) ink=%d" % (v, p, role, ax, ay, n))
                if n < MIN_RETICLE_PIXELS:
                    # Whose geometry IS at this anchor instead, if any? Name the nearest
                    # anchor of another view: that is the pass this cell actually read.
                    best = None
                    for wv in sorted(views):
                        for wp, (wx, wy, _, _) in views[wv]["rings"].items():
                            if wv == v and wp == p:
                                continue
                            d = ((wx - ax) ** 2 + (wy - ay) ** 2) ** .5
                            if best is None or d < best[0]:
                                best = (d, wv, wp, wx, wy)
                    where = ("" if best is None or best[0] > 60 else
                             "; the nearest anchor of another view is view %d's p%d at "
                             "(%.0f,%.0f), %.0f px away"
                             % (best[1], best[2], best[3], best[4], best[0]))
                    failures.append(
                        "view %d: no reticle at its own p%d anchor (%.0f,%.0f)%s"
                        % (v, p, ax, ay, where))

        if measured == 0:
            failures.append("the capture contains no measurable ally or enemy reticles")

        if failures:
            print("hud_view_geometry: FAIL")
            for line in failures:
                print("  " + line)
            return 1
        print("hud_view_geometry: every view's reticles sit on that view's own anchors")
        return 0


if __name__ == "__main__":
    sys.exit(main())
