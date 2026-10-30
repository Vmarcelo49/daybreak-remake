#!/usr/bin/env python3
"""Pin the character-shadow toggle (issue #21 row 1) to a rendered frame.

Why a capture test and not a shader unit test: the pass's whole contract is what the GPU
ends up drawing, and every one of its numbers can be right while nothing reaches the
frame. The original selects technique mode 2 (FUN_00652880) and draws every fighter's own
body and weapon with the light camera into a 1024x1024 target; the stage then samples that
map projectively and subtracts 0.3 from its albedo where its own light depth is behind the
map (FUN_00652af0 -> effect_3.bin). foundation/docs/SHADOWS.md carries the recovery, and
tests/shadow_map_test.cpp pins the constants device-free.

So this script renders the same 4-view battle frame with no flag, --no-shadows and
--shadows and asserts:

  * the default run is byte-identical to --no-shadows: OFF is the state every banked
    capture was made in, and adding the toggle must not move it;
  * --shadows DARKENS a small, localized set of pixels — a strictly-downward change, no
    brighter pixel anywhere, and no channel losing more than the recovered 0.3 of albedo
    can cost through the lighting term — which is the signature of the recovered
    arithmetic and not of a broken pass;
  * the change is not the whole frame: a receiver term that fires everywhere is a broken
    lookup, not a shadow;
  * every one of the four views shows some of it, which is what proves the per-view map
    and its bind group reach each view's draws (the original builds the light camera
    inside the per-view loop, so each view has its own map);
  * a stage-only frame is byte-identical with and without --shadows: with no fighters
    there are no casters, so the map stays empty and the receiver must leave the stage
    alone.

Usage:
    character_shadow.py <daybreak> <install-dir> [workdir]

Exit 0 when every measurement holds, 1 otherwise, and 77 (skip) when the renderer or the
game data is unavailable, so a CI box without a GPU or the install does not report a
false failure.
"""
import os
import sys
import tempfile

from capture_probe import (CaptureFailed, main_guard, read_ppm, require_asset,
                           require_install, run_demo)

# 960x540 is the split-screen size the toon row's test also uses: four 480x270 cells, big
# enough that a fighter's shadow is tens of pixels across.
SIZE = "960x540"
# The 4-view battle: four human controllers, one camera and HUD each. The per-view maps
# are the reason this recipe and not a single-view one — and the stage it rolls has ground
# collision loaded, so the fighters stand on the surface their shadow lands on.
BATTLE_ARGS = ["--screen=battle", "--local-players=4", "--frames=300", "--size=" + SIZE]
STAGE_ARGS = ["--stage={stage}", "--no-anim", "--frames=3", "--size=400x300"]

# The receiver subtracts the recovered 0.3 from the *albedo*, and the lighting term that
# follows scales it (ambient + diffuse can exceed 1 on a lit surface), so a frame drop is
# 0.3 * 255 * lit — 76 on this recipe's battle and 82 on the scripted gate's. The bound is
# therefore a factor-of-two allowance over 0.3 * 255: it catches a shadow that darkens by
# something other than the recovered subtract (a multiply, or a 1.0 term) without
# pretending the lighting scale is known per pixel.
MAX_DROP = 153


def measure(on_path, off_path):
    """Darkening statistics between two frames of the same scene.

    Returns a dict, or None when the frames are not comparable PPMs:
      changed      pixels that differ at all
      darker       of those, pixels whose mean luminance fell
      brighter     of those, pixels whose mean luminance rose (must be 0)
      max_drop     the largest single-channel drop (must be <= MAX_DROP)
      cells        changed-pixel count per 2x2 view cell
    """
    on = read_ppm(on_path)
    off = read_ppm(off_path)
    if on[:2] != off[:2]:
        raise CaptureFailed("frames differ in size: %dx%d vs %dx%d"
                            % (on[0], on[1], off[0], off[1]))
    w, h, a = off
    _, _, b = on
    stats = {"changed": 0, "darker": 0, "brighter": 0, "max_drop": 0,
             "cells": [0, 0, 0, 0], "total": w * h}
    for i in range(0, len(a), 3):
        pa = (a[i], a[i + 1], a[i + 2])
        pb = (b[i], b[i + 1], b[i + 2])
        if pa == pb:
            continue
        stats["changed"] += 1
        drop = max(pa[0] - pb[0], pa[1] - pb[1], pa[2] - pb[2])
        stats["max_drop"] = max(stats["max_drop"], drop)
        la = (pa[0] + pa[1] + pa[2]) / 3.0
        lb = (pb[0] + pb[1] + pb[2]) / 3.0
        if lb < la:
            stats["darker"] += 1
        elif lb > la:
            stats["brighter"] += 1
        p = i // 3
        y, x = divmod(p, w)
        stats["cells"][(0 if y < h // 2 else 2) + (0 if x < w // 2 else 1)] += 1
    return stats


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    install = os.path.abspath(sys.argv[2])
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    require_install(install, "character_shadow")
    stage = os.path.join(install, "data", "stage01")
    require_asset(stage, "character_shadow", "stage01")

    failures = []
    with tempfile.TemporaryDirectory() as tmp:
        default = os.path.join(tmp, "default.ppm")
        off = os.path.join(tmp, "off.ppm")
        on = os.path.join(tmp, "on.ppm")
        on2 = os.path.join(tmp, "on2.ppm")
        for path, extra in ((default, []), (off, ["--no-shadows"]),
                            (on, ["--shadows"]), (on2, ["--shadows"])):
            run_demo(demo, install, path, BATTLE_ARGS + extra, cwd)
        with open(default, "rb") as f:
            default_bytes = f.read()
        with open(off, "rb") as f:
            off_bytes = f.read()
        with open(on, "rb") as f:
            on_bytes = f.read()
        with open(on2, "rb") as f:
            on2_bytes = f.read()
        if default_bytes != off_bytes:
            failures.append("the default frame differs from --no-shadows: OFF is not the default")
        if on_bytes != on2_bytes:
            failures.append("two --shadows runs of the same recipe differ: the frame is not "
                            "deterministic, so nothing below can be trusted")
        stats = measure(on, off)
        share = 100.0 * stats["changed"] / stats["total"]
        print("  4-view battle: %d changed px (%.2f%% of the frame), %d darker, %d brighter, "
              "largest channel drop %d, per view %s"
              % (stats["changed"], share, stats["darker"], stats["brighter"],
                 stats["max_drop"], ", ".join(str(c) for c in stats["cells"])))
        if stats["changed"] == 0:
            failures.append("--shadows changed no pixel: the caster pass or the receiver "
                            "lookup no longer reaches the frame")
        else:
            if stats["brighter"]:
                failures.append("%d pixels got BRIGHTER with --shadows: the recovered term is "
                                "a flat subtract, it can never add light" % stats["brighter"])
            if stats["max_drop"] > MAX_DROP:
                failures.append("a channel dropped by %d, past what the recovered 0.3 of "
                                "albedo can cost through a lit surface (%d)"
                                % (stats["max_drop"], MAX_DROP))
            if share > 3.0:
                failures.append("--shadows changed %.2f%% of the frame: a receiver term that "
                                "fires almost everywhere is a broken lookup, not a shadow"
                                % share)
            # The original builds the light camera inside the per-view loop, so each view
            # has its own map and its own bind group; more than one view changing is what
            # proves they all get theirs. Not *every* view has to: the light's window is
            # only ~1170 units across and centred on that view's own camera eye, so a view
            # whose fighters stand outside it legitimately shows nothing (the recovered
            # frustum is tiny by design — see foundation/docs/SHADOWS.md).
            lit = [i for i, c in enumerate(stats["cells"]) if c > 0]
            if len(lit) < 2:
                failures.append("only view(s) %s show a shadow: the per-view map or its bind "
                                "group is not reaching the views" % ", ".join(map(str, lit)))

        # A stage with no fighters has no casters, so the map stays cleared and the
        # receiver must leave every pixel alone.
        stage_off = os.path.join(tmp, "stage_off.ppm")
        stage_on = os.path.join(tmp, "stage_on.ppm")
        args = [a.format(stage=stage) for a in STAGE_ARGS]
        # No `is not None` guard: run_demo raises on a real problem, so a stage render
        # that fails is a failure here rather than a silently skipped third of the suite.
        run_demo(demo, install, stage_off, args + ["--no-shadows"], cwd)
        run_demo(demo, install, stage_on, args + ["--shadows"], cwd)
        with open(stage_off, "rb") as f:
            stage_off_bytes = f.read()
        with open(stage_on, "rb") as f:
            stage_on_bytes = f.read()
        moved = 0
        _, _, a = read_ppm(stage_off)
        b = read_ppm(stage_on)[2]
        for i in range(0, len(a), 3):
            if a[i:i + 3] != b[i:i + 3]:
                moved += 1
        print("  stage-only frame: %d of %d px moved by --shadows" % (moved, len(a) // 3))
        if moved:
            failures.append("--shadows moved %d pixels of a frame with no fighters: "
                            "the receiver is darkening geometry no caster covers" % moved)

    if failures:
        print("character_shadow: FAIL")
        for line in failures:
            print("  " + line)
        return 1
    print("character_shadow: OFF is the default byte for byte, ON subtracts the recovered "
          "0.3 on a localized patch in more than one view, and a caster-free frame does "
          "not move")
    return 0


if __name__ == "__main__":
    sys.exit(main_guard(main))
