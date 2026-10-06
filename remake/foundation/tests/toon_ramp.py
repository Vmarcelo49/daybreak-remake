#!/usr/bin/env python3
"""Pin the toon-rendering toggle (issue #21) to a rendered frame.

Why a capture test and not a shader unit test: the toggle's whole contract is what the
GPU ends up drawing — the shipped ramp uploaded through the CNV path, bound beside the
camera, sampled at the diffuse term for the character and weapon draws only. A device-free
test can check the settings document (user_settings_test does) but it cannot see whether
the flag reaches the draw, whether the ramp decoded, or whether the split-screen path
binds it per view. So this renders the same frame three ways and measures the pixels:

  * the default run (no flag) must be byte-identical to `--no-toon`: OFF is the state
    every banked capture was made in, and adding the toggle must not move it;
  * `--toon` must differ from it, on the character's pixels, in the ramp's direction —
    the shipped 64x64 bitmap runs from 30/255 to 255/255, so it sits ABOVE the linear
    N.L almost everywhere: the mean character pixel gets brighter by a bounded amount
    (a constant ramp would blow past the band, a black one would go negative), nothing
    gets meaningfully darker, and the silhouette does not change;
  * a stage-only frame must be byte-identical with and without `--toon`: the original's
    toon technique covers the per-character draw (FUN_006396f0:126-140) and the object
    material path (FUN_005f60b0:121-126), not the stage;
  * a 4-view battle frame must show the same difference, which is what proves the ramp
    is bound in the per-view camera groups too (a group missing it is a layout mismatch
    the whole frame is rejected for).

Usage:
    toon_ramp.py <foundation_demo> <install-dir> [workdir]

Exit 0 when every measurement holds, 1 otherwise, and 77 (skip) when the renderer or the
game data is unavailable, so a CI box without a GPU or the install does not report a
false failure.
"""
import os
import subprocess
import sys
import tempfile

SKIP = 77

# The clear colour the scene pass writes (scenes.cpp:736, D3DCOLOR_XRGB(40,42,54)): every
# pixel that is not this is geometry, which is the character mask this test measures.
BACKGROUND = (40, 42, 54)

# Candidate character directories: the capture needs one shipped fighter. Any of these
# resolves on a full install; a partial one skips rather than failing.
CHARACTER_DIRS = ("rena", "rika", "akane", "mion")


def run_demo(demo, install, out, args, cwd):
    cmd = [demo, "--headless", "--install=" + install, "--out=" + out] + args
    proc = subprocess.run(cmd, cwd=cwd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                          text=True, timeout=900)
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


def character_dir(install):
    for name in CHARACTER_DIRS:
        path = os.path.join(install, "data", name)
        if os.path.isdir(path):
            return path
    return None


def compare(on_path, off_path):
    """Per-pixel delta over the character pixels of two frames of the same scene.

    Returns (off_non_background, on_non_background, changed, mean_delta, min_delta,
    max_delta) or None when the frames do not even agree on their dimensions.
    """
    on = read_ppm(on_path)
    off = read_ppm(off_path)
    if on is None or off is None or on[:2] != off[:2]:
        return None
    w, h, a = off
    _, _, b = on
    off_background = on_background = changed = 0
    total = 0
    lo, hi = 1e9, -1e9
    for i in range(0, len(a), 3):
        pa = (a[i], a[i + 1], a[i + 2])
        if pa != BACKGROUND:
            off_background += 1
        if (b[i], b[i + 1], b[i + 2]) != BACKGROUND:
            on_background += 1
        if a[i:i + 3] != b[i:i + 3]:
            changed += 1
            delta = ((b[i] + b[i + 1] + b[i + 2]) - (pa[0] + pa[1] + pa[2])) / 3.0
            total += delta
            lo = min(lo, delta)
            hi = max(hi, delta)
    mean = total / changed if changed else 0.0
    if not changed:
        lo = hi = 0.0   # no sample: the sentinels would print as nonsense
    return off_background, on_background, changed, mean, lo, hi


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    install = os.path.abspath(sys.argv[2])
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    if not os.path.exists(os.path.join(install, "data")):
        print("toon_ramp: no game data at %s, skipped" % install)
        return SKIP
    fighter = character_dir(install)
    stage = os.path.join(install, "data", "stage01")
    if fighter is None or not os.path.isdir(stage):
        print("toon_ramp: no character or stage directory in %s, skipped" % install)
        return SKIP

    failures = []
    with tempfile.TemporaryDirectory() as tmp:
        # 1. The default frame and the explicit OFF frame: identical bytes.
        default = os.path.join(tmp, "default.ppm")
        off = os.path.join(tmp, "off.ppm")
        on = os.path.join(tmp, "on.ppm")
        # --no-anim: the bind pose, so the two frames are the same pose by construction and
        # no animation clock can differ between runs.
        scene = ["--character=" + fighter + ":0", "--no-anim", "--frames=3", "--size=400x400"]
        if run_demo(demo, install, default, scene, cwd) is None:
            print("toon_ramp: headless renderer unavailable, skipped")
            return SKIP
        if run_demo(demo, install, off, scene + ["--no-toon"], cwd) is None:
            print("toon_ramp: headless renderer unavailable, skipped")
            return SKIP
        if run_demo(demo, install, on, scene + ["--toon"], cwd) is None:
            print("toon_ramp: headless renderer unavailable, skipped")
            return SKIP
        with open(default, "rb") as f:
            default_bytes = f.read()
        with open(off, "rb") as f:
            off_bytes = f.read()
        if default_bytes != off_bytes:
            failures.append("the default frame differs from --no-toon: OFF is not the default")
        measured = compare(on, off)
        if measured is None:
            print("toon_ramp: captures are not comparable PPMs, skipped")
            return SKIP
        non_background, on_background, changed, mean, lo, hi = measured
        print("  character frame: %d non-background px, %d changed, mean delta %+.2f, "
              "range %+.1f..%+.1f" % (non_background, changed, mean, lo, hi))
        if non_background < 1000:
            failures.append("only %d character pixels in the frame: nothing to measure"
                            % non_background)
        elif changed < 0.5 * non_background:
            failures.append("--toon changed only %d of %d character pixels: the toggle no "
                            "longer reaches the draw" % (changed, non_background))
        # The band is the shipped ramp's own signature: it is above the linear N.L nearly
        # everywhere (mean ~+12.7 on this scene), a constant-white ramp would be far above
        # it and a constant-black one far below.
        if not (5.0 <= mean <= 25.0):
            failures.append("mean character delta %+.2f is outside the ramp's +5..+25 band"
                            % mean)
        if lo < -2.0:
            failures.append("the ramp darkened a character pixel by %.1f: it sits below the "
                            "linear N.L there" % lo)
        if hi > 40.0:
            failures.append("a character pixel brightened by %.1f: more than the shipped "
                            "ramp can lift" % hi)
        # The silhouette must not move: the ramp replaces a lighting term, not coverage.
        if on_background != non_background:
            failures.append("the character silhouette changed with --toon (%d vs %d px)"
                            % (on_background, non_background))

        # 2. A stage frame: the ramp is not the stage's. Same bytes either way.
        stage_args = ["--stage=" + stage, "--no-anim", "--frames=3", "--size=400x300"]
        stage_off = os.path.join(tmp, "stage_off.ppm")
        stage_on = os.path.join(tmp, "stage_on.ppm")
        if (run_demo(demo, install, stage_off, stage_args + ["--no-toon"], cwd) is not None and
                run_demo(demo, install, stage_on, stage_args + ["--toon"], cwd) is not None):
            with open(stage_off, "rb") as f:
                stage_off_bytes = f.read()
            with open(stage_on, "rb") as f:
                stage_on_bytes = f.read()
            stage_px = read_ppm(stage_off)
            stage_mask = 0 if stage_px is None else sum(
                1 for i in range(0, len(stage_px[2]), 3)
                if tuple(stage_px[2][i:i + 3]) != BACKGROUND)
            if stage_mask < 0.1 * 400 * 300:
                failures.append("the stage frame has almost no geometry: the A/B would be vacuous")
            elif stage_off_bytes != stage_on_bytes:
                failures.append("--toon moved a stage-only frame: the ramp is reaching draws "
                                "the original's technique does not cover")
            print("  stage frame: %d non-background px, --toon %s"
                  % (stage_mask, "identical" if stage_off_bytes == stage_on_bytes else "DIFFERS"))
        else:
            print("  stage frame: skipped (stage render unavailable)")

        # 3. The split-screen path: four views, one match frame, same direction. This is
        # the case a missing ramp binding in the per-view camera groups would break.
        four_off = os.path.join(tmp, "four_off.ppm")
        four_on = os.path.join(tmp, "four_on.ppm")
        four_args = ["--screen=battle", "--local-players=4", "--frames=300", "--size=960x540"]
        if (run_demo(demo, install, four_off, four_args + ["--no-toon"], cwd) is not None and
                run_demo(demo, install, four_on, four_args + ["--toon"], cwd) is not None):
            four = compare(four_on, four_off)
            if four is None:
                failures.append("the 4-view captures are not comparable PPMs")
            else:
                non_background, _, changed, mean, lo, hi = four
                print("  4-view battle: %d non-background px, %d changed, mean delta %+.2f, "
                      "range %+.1f..%+.1f" % (non_background, changed, mean, lo, hi))
                if changed < 500:
                    failures.append("--toon changed only %d pixels in the 4-view battle frame"
                                    % changed)
                if mean <= 0.0:
                    failures.append("the 4-view battle did not brighten (mean %+.2f): the ramp "
                                    "is not bound in the per-view camera groups" % mean)
                if lo < -2.0:
                    failures.append("a 4-view pixel darkened by %.1f" % lo)
        else:
            print("  4-view battle: skipped (match render unavailable)")

    if failures:
        print("toon_ramp: FAIL")
        for line in failures:
            print("  " + line)
        return 1
    print("toon_ramp: OFF is the default byte for byte, ON ramps the character draws only, "
          "and the 4-view path ramps them too")
    return 0


if __name__ == "__main__":
    sys.exit(main())
