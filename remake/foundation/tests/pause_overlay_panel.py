#!/usr/bin/env python3
"""Pin the pause overlay's rendered pixels (issue #50).

Why a capture test and not a layout test: the layout rule (ui/pause_layout.h) and the
overlay's own batching were both "correct" while the defect was live — the quads it pushed
carried the right geometry, and `beginFrame` did clear its queue. What was wrong was the
renderer it pushed them into: one SpriteRenderer hands every pass in a frame the same vertex
buffer written at offset 0, and all of a frame's writes land before its single submission, so
the overlay's pass read the BATTLE HUD's vertices. Its dim quad came out as the first
fighter's reticle quad drawn with the 1x1 white fallback (the human's "white rectangle is the
targeting image"), its opening quads ghosted the HUD's art, and the overlay's own title
disappeared. Only a rendered frame can see that; this script measures one.

Usage:
    pause_overlay_panel.py <foundation_demo> <install-dir> [workdir]

Every measurement is taken against a reference frame of the SAME match state captured one
frame earlier without --pause-overlay, which is what makes the numbers readable: outside the
panel the paused frame is the frozen frame times the 0.55 dim, and the panel is the extra
darkening on top of it. Both runs print their match frame, and the script skips rather than
fails when they disagree (a pacing change, not a defect).

Asserted, at 960x540, 1920x1080 and in a 4-view split at 960x540:

  * no solid-white block: no connected white cluster that is at least a ninth of the frame
    tall AND wide. The defect's quad was 156x157 px at 960x540; the HUD's own white ink
    (glyphs, the stamina/HP fills, the bars) never reaches that shape.
  * a translucent backing panel is present, and it is the text block plus its margin: the
    panel's mask (pixels darker than the plain dim by more than rounding) forms one
    rectangle whose width is its widest drawn line plus that margin, the title and the menu's
    line bands sit inside it, and the same mask on two unpaused frames finds nothing.
  * the menu is legible and canvas-derived: the title's ink height and the panel's width at
    1920x1080 are about twice the 960x540 ones, and the 4-view split — one overlay over the
    whole target — measures the same as the single view at that size.
  * the clocks are frozen (issue #15 / criterion 5, from the capture path): the same pause
    captured 60 frames later is byte-identical.

Exit 0 when every check holds, 1 otherwise, and 77 (skip) when the renderer or the install is
unavailable, so a CI box without a GPU or the game data does not report a false failure.
"""
import os
import subprocess
import sys
import tempfile

SKIP = 77
# The match frame the recipes pause at, and the frontend's countdown in capture frames. The
# harness steps one logic tick per frame and holds the round for 180 ticks, so the pause
# lands on capture frame N + 181 and its same-state reference is N + 180; both runs' own
# "match: N frames" line proves it before anything is measured.
PAUSE_FRAME = 300
COUNTDOWN = 180
# A pixel is menu ink when every channel is at least this bright: the title and rows are
# white and 0.85 grey (217), while the dimmed stage's stone sits near 180.
INK_MIN = 210
# The dim the overlay puts over the frozen frame (main.cpp) and the rounding slack the
# comparison allows.
DIM = 0.45
SLACK = 6
# A white block must span this fraction of the frame in BOTH dimensions to count as one.
WHITE_SHAPE_FRACTION = 1.0 / 9.0


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


def white_block(px, w, h):
    """Largest connected white cluster that is wide AND tall, or None.

    The 1x1 white fallback texture over the reticle's quad is ~156x157 px at 960x540; the
    HUD's own white parts are text-sized or one bar thick, so requiring the cluster to span
    a ninth of both axes separates them without a magic area.
    """
    min_w, min_h = w * WHITE_SHAPE_FRACTION, h * WHITE_SHAPE_FRACTION
    pts = set()
    for y in range(h):
        row = y * w * 3
        for x in range(w):
            o = row + x * 3
            if px[o] >= 250 and px[o + 1] >= 250 and px[o + 2] >= 250:
                pts.add((x, y))
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
        bw, bh = max(xs) - min(xs) + 1, max(ys) - min(ys) + 1
        if bw >= min_w and bh >= min_h:
            return (min(xs), min(ys), bw, bh, len(comp))
    return None


def panel_mask(px, w, h, ref):
    """Pixels the overlay's panel darkened beyond the plain dim, as (count, bbox).

    The panel is drawn over the already-dimmed frame, so against the same state's un-dimmed
    pixels it is everything darker than DIM * reference by more than rounding. A count of 0
    means no panel (or no overlay at all).
    """
    count = 0
    x0, y0, x1, y1 = w, h, -1, -1
    for y in range(h):
        row = y * w * 3
        for x in range(w):
            o = row + x * 3
            if (px[o] < ref[o] * DIM - SLACK and px[o + 1] < ref[o + 1] * DIM - SLACK and
                    px[o + 2] < ref[o + 2] * DIM - SLACK):
                count += 1
                if x < x0: x0 = x
                if y < y0: y0 = y
                if x > x1: x1 = x
                if y > y1: y1 = y
    if x1 < 0:
        return 0, (0, 0, 0, 0)
    return count, (x0, y0, x1, y1)


def dim_matches(px, w, h, ref, rect, min_fraction=0.90, tol=24):
    """Outside the panel, is the paused frame the reference times the dim?

    Sampled on a 4-pixel grid to keep the pass cheap. The exceptions are the HUD's own
    pixels — drawn over the dim, so brighter than the model — and the one tick of fighter
    motion between the pair; measured, 95 % of the samples agree within +-24 of 255 at
    960x540. The floor is 90 % so a wholesale replacement of the frame (which would leave
    almost nothing agreeing) cannot pass.
    """
    x0, y0, x1, y1 = rect
    ok = total = 0
    for y in range(0, h, 4):
        row = y * w * 3
        for x in range(0, w, 4):
            if x0 <= x <= x1 and y0 <= y <= y1:
                continue
            o = row + x * 3
            total += 1
            if (abs(px[o] - ref[o] * DIM) <= tol and
                    abs(px[o + 1] - ref[o + 1] * DIM) <= tol and
                    abs(px[o + 2] - ref[o + 2] * DIM) <= tol):
                ok += 1
    return total > 0 and ok >= total * min_fraction


def ink_in(px, w, h, rect):
    """Menu ink inside a rect: (bbox, bands), one band per drawn line.

    A band is a run of rows with at least 15 ink pixels — a drawn line's own rows. It
    carries its x extent, because a band is what "the text inside the panel" means here: in
    a 4-view frame the battle HUD of the other cells is drawn OVER the panel (the overlay's
    pass comes first), so the panel's ink bbox can reach its edges with HUD pixels that are
    not the menu's.
    """
    x0, y0, x1, y1 = rect
    per_row = {}
    ix0, iy0, ix1, iy1 = w, h, -1, -1
    for y in range(y0, y1 + 1):
        row = y * w * 3
        for x in range(x0, x1 + 1):
            o = row + x * 3
            if px[o] >= INK_MIN and px[o + 1] >= INK_MIN and px[o + 2] >= INK_MIN:
                per_row[y] = per_row.get(y, 0) + 1
                if x < ix0: ix0 = x
                if y < iy0: iy0 = y
                if x > ix1: ix1 = x
                if y > iy1: iy1 = y
    bands = []
    current = None
    for y in range(y0, y1 + 1):
        if per_row.get(y, 0) >= 15:
            if current is None:
                current = [y, y, x1, x0]
            current[1] = y
            row_start = y * w * 3 + x0 * 3
            for x in range(x0, x1 + 1):
                o = row_start + (x - x0) * 3
                if px[o] >= INK_MIN and px[o + 1] >= INK_MIN and px[o + 2] >= INK_MIN:
                    if x < current[2]: current[2] = x
                    if x > current[3]: current[3] = x
        elif current is not None:
            bands.append(tuple(current))
            current = None
    if current is not None:
        bands.append(tuple(current))
    bbox = (ix0, iy0, ix1, iy1) if ix1 >= 0 else None
    return bbox, bands


def capture(demo, install, workdir, tag, args):
    out = os.path.join(workdir, tag + ".ppm")
    log = run_demo(demo, install, out, args, workdir)
    if log is None:
        return None
    ppm = read_ppm(out)
    if ppm is None:
        return None
    return {"tag": tag, "log": log, "ppm": ppm}


def pause_args(size, extra=()):
    return ["--screen=battle", "--pause-overlay=%d" % PAUSE_FRAME,
            "--frames=%d" % (PAUSE_FRAME + COUNTDOWN + 1), "--size=" + size] + list(extra)


def ref_args(size, extra=()):
    return ["--screen=battle", "--frames=%d" % (PAUSE_FRAME + COUNTDOWN),
            "--size=" + size] + list(extra)


def check_case(name, demo, install, tmp, size, extra, failures):
    """One paused frame against its same-state reference: panel, text and white control."""
    paused = capture(demo, install, tmp, name + "-paused", pause_args(size, extra))
    ref = capture(demo, install, tmp, name + "-ref", ref_args(size, extra))
    if paused is None or ref is None:
        return None
    if "[pause] paused (--pause-overlay)" not in paused["log"]:
        failures.append("%s: the run never entered the pause" % name)
        return None
    if ("match: %d frames" % PAUSE_FRAME) not in paused["log"] or \
       ("match: %d frames" % PAUSE_FRAME) not in ref["log"]:
        print("  %s: the pause and its reference are not the same match frame, skipped" % name)
        return None
    w, h, px = paused["ppm"]
    rw, rh, rpx = ref["ppm"]
    if (w, h) != (rw, rh):
        failures.append("%s: reference size differs" % name)
        return None
    block = white_block(px, w, h)
    if block:
        failures.append("%s: a %dx%d solid-white block at (%d,%d) (%d px); the overlay is "
                        "drawing the HUD's reticle quad white again"
                        % (name, block[2], block[3], block[0], block[1], block[4]))

    count, rect = panel_mask(px, w, h, rpx)
    fraction = count / float(w * h)
    # The panel is "sized to the text" (ui/pause_layout.h), so this floor tracks the text. It
    # was 5% while the block carried the binding footer — the widest line, and the one that ran
    # past a 4:3 frame; without it the panel is legitimately smaller (measured 8% single-view
    # and 2.93% in a four-view frame, where the same panel sits over a busier background). The
    # check still catches a MISSING panel, which is what it is for.
    if fraction < 0.02 or rect[2] <= rect[0] or rect[3] <= rect[1]:
        failures.append("%s: no backing panel (only %.2f%% of the frame is darker than the "
                        "dim)" % (name, fraction * 100.0))
        return None
    bbox, bands = ink_in(px, w, h, rect)
    print("  %s: panel %dx%d at (%d,%d), %.0f%% of the frame darkened, %d text band(s)"
          % (name, rect[2] - rect[0] + 1, rect[3] - rect[1] + 1, rect[0], rect[1],
             fraction * 100.0, len(bands)))
    # The title and the four rows are 5 bands. There is no binding footer any more: it was the
    # widest line, so it set the panel's width and ran past a 4:3 frame (the human's report).
    # The band count is a floor rather than an equality because two adjacent rows can merge
    # into one band at a size where the pitch is small relative to the glyphs.
    if len(bands) < 4:
        failures.append("%s: %d text band(s) inside the panel; the title and the four rows "
                        "are at least 4 once no two merge" % (name, len(bands)))
        return None
    if bbox is None:
        failures.append("%s: no menu ink inside the panel" % name)
        return None
    title = bands[0][1] - bands[0][0] + 1
    widest = max(b[3] - b[2] + 1 for b in bands)
    title_x0, title_x1 = bands[0][2], bands[0][3]
    print("  %s: title %d px at x %d..%d, widest line %d px, panel %d px wide"
          % (name, title, title_x0, title_x1, widest, rect[2] - rect[0] + 1))
    if title_x0 <= rect[0] or title_x1 >= rect[2]:
        failures.append("%s: the title is not inside the panel" % name)
    # Sized to the text: the panel is the block plus a margin, so it cannot be much wider
    # than its widest line (measured 1.05 at both sizes) and never narrower.
    ratio = (rect[2] - rect[0] + 1) / float(max(1, widest))
    if not 1.0 <= ratio <= 1.5:
        failures.append("%s: the panel is %.2fx its widest line; it should be the text plus "
                        "a small margin" % (name, ratio))
    floor = int(16 * h / 540.0)
    if title < floor:
        failures.append("%s: the title's ink is %d px tall; %d rows of frame should give at "
                        "least %d" % (name, title, h, floor))
    if not dim_matches(px, w, h, rpx, rect):
        failures.append("%s: outside the panel the paused frame is not the frozen frame under "
                        "the 55%% dim" % name)
    return {"size": (w, h), "rect": rect, "bbox": bbox, "bands": bands, "title": title,
            "count": count, "paused": paused, "ref": ref}


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    # Absolute: the demo runs with `cwd` below (a temp dir), so a relative install would
    # resolve against that instead of against where the caller found it.
    install = os.path.abspath(sys.argv[2])
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    if not os.path.exists(os.path.join(install, "data")):
        print("pause_overlay_panel: no game data at %s, skipped" % install)
        return SKIP
    failures = []
    with tempfile.TemporaryDirectory() as tmp:
        small = check_case("960x540", demo, install, tmp, "960x540", (), failures)
        if small is None:
            # A measured failure and a missing renderer both leave nothing to compare; the
            # failures list is what tells them apart, so a capture that ran and failed to
            # show a panel reports FAIL instead of hiding behind the skip code.
            if failures:
                print("pause_overlay_panel: FAIL")
                for line in failures:
                    print("  " + line)
                return 1
            print("pause_overlay_panel: headless renderer or game data unavailable, skipped")
            return SKIP

        # The overlay's own pixels, negatively: the panel mask must find nothing on two
        # unpaused frames, so a "panel" cannot be scene noise the paused frame happens to
        # darken. Frames one apart, like the paused pair.
        noise = capture(demo, install, tmp, "noise-a",
                        ["--screen=battle", "--frames=%d" % (PAUSE_FRAME + COUNTDOWN),
                         "--size=960x540"])
        noise2 = capture(demo, install, tmp, "noise-b",
                         ["--screen=battle", "--frames=%d" % (PAUSE_FRAME + COUNTDOWN + 1),
                          "--size=960x540"])
        if noise is not None and noise2 is not None:
            nw, nh, npx = noise["ppm"]
            noise_count, _ = panel_mask(npx, nw, nh, noise2["ppm"][2])
            noise_fraction = noise_count / float(nw * nh)
            print("  960x540: two unpaused frames differ by %.3f%% of the panel mask"
                  % (noise_fraction * 100.0))
            if noise_fraction > 0.02:
                failures.append("960x540: the panel mask fires on two unpaused frames "
                                "(%.1f%%), so it is not measuring the overlay"
                                % (noise_fraction * 100.0))

        big = check_case("1920x1080", demo, install, tmp, "1920x1080", (), failures)
        split = check_case("4view-960x540", demo, install, tmp, "960x540",
                           ("--local-players=4",), failures)
        if big is not None:
            ratio = big["title"] / float(max(1, small["title"]))
            width_ratio = (big["rect"][2] - big["rect"][0]) / \
                          float(max(1, small["rect"][2] - small["rect"][0]))
            print("  1080p/540p: title x%.2f, panel width x%.2f" % (ratio, width_ratio))
            if not 1.7 <= ratio <= 2.3 or not 1.7 <= width_ratio <= 2.3:
                failures.append("1920x1080: the menu did not scale with the canvas "
                                "(title x%.2f, panel x%.2f)" % (ratio, width_ratio))
        if split is not None:
            same = (abs((split["rect"][2] - split["rect"][0]) -
                        (small["rect"][2] - small["rect"][0])) <= 4 and
                    abs((split["rect"][3] - split["rect"][1]) -
                        (small["rect"][3] - small["rect"][1])) <= 4)
            print("  4-view at 960x540: panel matches the single view at that size: %s"
                  % ("yes" if same else "no"))
            if not same:
                failures.append("4-view 960x540: the overlay's panel differs from the single "
                                "view's at the same target")

        # The freeze: the paused ticks step no match state, so 60 frames later is the same
        # bytes (issue #15's contract, measured from the capture path).
        later = capture(demo, install, tmp, "960x540-later",
                        ["--screen=battle", "--pause-overlay=%d" % PAUSE_FRAME,
                         "--frames=%d" % (PAUSE_FRAME + COUNTDOWN + 61), "--size=960x540"])
        if later is None:
            failures.append("960x540: the later paused capture failed")
        elif later["ppm"][2] != small["paused"]["ppm"][2]:
            failures.append("960x540: the paused frame changed 60 frames after the pause; the "
                            "clocks are not frozen")
        else:
            print("  960x540: the pause is byte-identical 60 frames later (clocks frozen)")

    if failures:
        print("pause_overlay_panel: FAIL")
        for line in failures:
            print("  " + line)
        return 1
    print("pause_overlay_panel: panel, text scale, split screen, freeze and the white-block "
          "control all measured")
    return 0


if __name__ == "__main__":
    sys.exit(main())
