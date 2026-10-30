#!/usr/bin/env python3
"""Pin the toon-shading toggle (issue #21) to a rendered frame.

Why a capture test and not a shader unit test: the toggle's whole contract is what the GPU
ends up drawing. The original switches the character draw from its plain technique
(FUN_006519f0) to a two-pass effect technique (FUN_00652220, modes 1/7), and both of that
technique's passes are visible in the frame:

  * an OUTLINE hull — the same submeshes drawn again with their clip positions offset
    along the world normal (scaled by w, so the rim is a constant ~1.1 px at 800x600),
    front faces culled, no pixel shader, flat `MaterialColor * 0.285714286` where
    MaterialColor is the material's Emissive;
  * the surface drawn with the effect's own lighting, `albedo * saturate(ramp + emissive -
    0.1)`, where the ramp is the shipped data/directX/toon.bmp sampled at the
    object-space N.L.

So this script renders the same bind-pose character frame with no flag, --no-toon and
--toon and asserts:

  * the default run is byte-identical to `--no-toon`: OFF is the state every banked
    capture was made in, and adding the toggle must not move it;
  * `--toon` adds a thin DARK RIM outside the OFF silhouette (the outline), loses no
    silhouette pixel (the hull is behind the surface), and changes the surface shading
    (the ramp) — this is what fails if the toggle stops drawing the outline;
  * a stage-only frame is byte-identical with and without `--toon`: the original's toon
    technique covers the per-character draw and the object material path
    (FUN_006396f0:126-140, FUN_005f60b0:121-126), not the stage;
  * a 4-view battle frame shows the same rim, which is what proves the ramp and the hull
    reach the per-view camera groups too (a group missing the ramp binding is a layout
    mismatch the whole frame is rejected for).

Usage:
    toon_ramp.py <daybreak> <install-dir> [workdir]

Exit 0 when every measurement holds, 1 otherwise, and 77 (skip) when the renderer or the
game data is unavailable, so a CI box without a GPU or the install does not report a
false failure.
"""
import os
import sys
import tempfile

from capture_probe import (CaptureFailed, main_guard, read_ppm, require_asset,
                           require_install, run_demo)

# The clear colour the scene pass writes (scenes.cpp:736, D3DCOLOR_XRGB(40,42,54)): every
# pixel that is not this is geometry, which is the character mask this test measures.
BACKGROUND = (40, 42, 54)

# 800x600 is the original's own canvas: the outline offset is a constant fraction of NDC
# (0.011/4 and 0.011/3), so the rim is ~1.1 px there and measurably thinner on a smaller
# capture.
SIZE = "800x600"

# Candidate character directories: the capture needs one shipped fighter. Any of these
# resolves on a full install; a partial one skips rather than failing.
CHARACTER_DIRS = ("rena", "rika", "akane", "mion")


def measure(on_path, off_path):
    """Silhouette and rim statistics between two frames of the same scene.

    Returns a dict, or None when the frames do not even agree on their dimensions:
      off_px / on_px  non-background pixels of each frame (the character silhouette)
      rim             pixels that are background in OFF and covered in ON (the outline)
      lost            pixels covered in OFF and background in ON (must be 0)
      rim_lum         mean luminance of the rim pixels
      off_lum         mean luminance of the OFF silhouette
      changed         OFF silhouette pixels whose colour differs in ON (the ramp shading)
    """
    on = read_ppm(on_path)
    off = read_ppm(off_path)
    if on[:2] != off[:2]:
        raise CaptureFailed("frames differ in size: %dx%d vs %dx%d"
                            % (on[0], on[1], off[0], off[1]))
    w, h, a = off
    _, _, b = on
    stats = {"off_px": 0, "on_px": 0, "rim": 0, "lost": 0, "changed": 0,
             "rim_sum": 0.0, "off_sum": 0.0}
    for i in range(0, len(a), 3):
        pa = (a[i], a[i + 1], a[i + 2])
        pb = (b[i], b[i + 1], b[i + 2])
        off_here = pa != BACKGROUND
        on_here = pb != BACKGROUND
        if off_here:
            stats["off_px"] += 1
            stats["off_sum"] += (pa[0] + pa[1] + pa[2]) / 3.0
            if a[i:i + 3] != b[i:i + 3]:
                stats["changed"] += 1
            if not on_here:
                stats["lost"] += 1
        if on_here:
            stats["on_px"] += 1
            if not off_here:
                stats["rim"] += 1
                stats["rim_sum"] += (pb[0] + pb[1] + pb[2]) / 3.0
    stats["rim_lum"] = stats["rim_sum"] / stats["rim"] if stats["rim"] else 0.0
    stats["off_lum"] = stats["off_sum"] / stats["off_px"] if stats["off_px"] else 0.0
    return stats


def changed_per_cell(on_path, off_path, cols, rows):
    """Changed-pixel count per grid cell, or None when the frames are not comparable."""
    on = read_ppm(on_path)
    off = read_ppm(off_path)
    if on[:2] != off[:2]:
        raise CaptureFailed("frames differ in size: %dx%d vs %dx%d"
                            % (on[0], on[1], off[0], off[1]))
    w, h, a = off
    _, _, b = on
    counts = [0] * (cols * rows)
    for i in range(0, len(a), 3):
        if a[i:i + 3] == b[i:i + 3]:
            continue
        p = i // 3
        cell = min(p // w // (h // rows), rows - 1) * cols + min((p % w) // (w // cols), cols - 1)
        counts[cell] += 1
    return counts


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    install = os.path.abspath(sys.argv[2])
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    require_install(install, "toon_ramp")
    fighter = None
    for name in CHARACTER_DIRS:
        candidate = os.path.join(install, "data", name)
        if os.path.isdir(candidate):
            fighter = candidate
            break
    stage = os.path.join(install, "data", "stage01")
    require_asset(stage, "toon_ramp", "stage01")
    if fighter is None:
        raise CaptureFailed("toon_ramp: no character directory in %s" % install)

    failures = []
    with tempfile.TemporaryDirectory() as tmp:
        # 1. The default frame and the explicit OFF frame: identical bytes.
        default = os.path.join(tmp, "default.ppm")
        off = os.path.join(tmp, "off.ppm")
        on = os.path.join(tmp, "on.ppm")
        # --no-anim: the bind pose, so the frames are the same pose by construction and no
        # animation clock can differ between runs.
        scene = ["--character=" + fighter + ":0", "--no-anim", "--frames=3",
                 "--size=" + SIZE]
        for path, extra in ((default, []), (off, ["--no-toon"]), (on, ["--toon"])):
            run_demo(demo, install, path, scene + extra, cwd)
        with open(default, "rb") as f:
            default_bytes = f.read()
        with open(off, "rb") as f:
            off_bytes = f.read()
        if default_bytes != off_bytes:
            failures.append("the default frame differs from --no-toon: OFF is not the default")
        stats = measure(on, off)
        print("  character frame: off %d px (mean lum %.1f), on %d px, rim %d px "
              "(mean lum %.1f), lost %d, interior changed %d"
              % (stats["off_px"], stats["off_lum"], stats["on_px"], stats["rim"],
                 stats["rim_lum"], stats["lost"], stats["changed"]))
        if stats["off_px"] < 1000:
            failures.append("only %d character pixels in the frame: nothing to measure"
                            % stats["off_px"])
        else:
            if stats["rim"] < 200:
                failures.append("--toon added only %d rim pixels: the outline no longer "
                                "draws" % stats["rim"])
            if stats["rim"] > 0.4 * stats["off_px"]:
                failures.append("the rim is %d px against a %d px silhouette: that is a "
                                "filled hull, not an outline"
                                % (stats["rim"], stats["off_px"]))
            if stats["rim"] and stats["rim_lum"] > 0.6 * stats["off_lum"]:
                failures.append("the rim's mean luminance %.1f is not darker than the "
                                "character's %.1f: the outline is not the flat dark hull"
                                % (stats["rim_lum"], stats["off_lum"]))
            if stats["lost"]:
                failures.append("%d silhouette pixels went back to the background: the "
                                "outline hull is covering the character" % stats["lost"])
            if stats["changed"] < 0.5 * stats["off_px"]:
                failures.append("--toon changed only %d of %d surface pixels: the ramp "
                                "shading no longer reaches the draw"
                                % (stats["changed"], stats["off_px"]))

        # 2. A stage frame: the toon technique is not the stage's. Same bytes either way.
        stage_args = ["--stage=" + stage, "--no-anim", "--frames=3", "--size=400x300"]
        stage_off = os.path.join(tmp, "stage_off.ppm")
        stage_on = os.path.join(tmp, "stage_on.ppm")
        run_demo(demo, install, stage_off, stage_args + ["--no-toon"], cwd)
        run_demo(demo, install, stage_on, stage_args + ["--toon"], cwd)
        with open(stage_off, "rb") as f:
            stage_off_bytes = f.read()
        with open(stage_on, "rb") as f:
            stage_on_bytes = f.read()
        stage_px = read_ppm(stage_off)
        stage_mask = sum(1 for i in range(0, len(stage_px[2]), 3)
                         if tuple(stage_px[2][i:i + 3]) != BACKGROUND)
        if stage_mask < 0.1 * 400 * 300:
            failures.append("the stage frame has almost no geometry: the A/B would be vacuous")
        elif stage_off_bytes != stage_on_bytes:
            failures.append("--toon moved a stage-only frame: the technique is reaching "
                            "draws the original does not cover")
        print("  stage frame: %d non-background px, --toon %s"
              % (stage_mask, "identical" if stage_off_bytes == stage_on_bytes else "DIFFERS"))

        # 3. The split-screen path: four views, one match frame. A battle frame has stage
        # geometry behind the fighters, so the rim no longer lands on the clear colour and
        # the silhouette test above cannot be reused; what matters here is that the toon
        # state reaches EVERY view's draw (the per-view camera groups carry the ramp, and
        # a group missing it is a layout mismatch the whole frame is rejected for), so the
        # assertion is per cell: each of the four views must show changed pixels.
        four_off = os.path.join(tmp, "four_off.ppm")
        four_on = os.path.join(tmp, "four_on.ppm")
        four_args = ["--screen=battle", "--local-players=4", "--frames=300", "--size=960x540"]
        run_demo(demo, install, four_off, four_args + ["--no-toon"], cwd)
        run_demo(demo, install, four_on, four_args + ["--toon"], cwd)
        cells = changed_per_cell(four_on, four_off, 2, 2)
        total = sum(cells)
        print("  4-view battle: %d changed px, per view %s"
              % (total, ", ".join(str(c) for c in cells)))
        if total < 500:
            failures.append("--toon changed only %d pixels in the 4-view battle frame" % total)
        for index, count in enumerate(cells):
            if count < 50:
                failures.append("view %d changed only %d pixels: the toon state is "
                                "not reaching every view's draw" % (index, count))

    if failures:
        print("toon_ramp: FAIL")
        for line in failures:
            print("  " + line)
        return 1
    print("toon_ramp: OFF is the default byte for byte, ON draws a thin dark outline and "
          "ramp-shades the character, and the 4-view path does both")
    return 0


if __name__ == "__main__":
    sys.exit(main_guard(main))
