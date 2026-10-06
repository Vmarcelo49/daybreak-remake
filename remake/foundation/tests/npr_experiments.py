#!/usr/bin/env python3
"""Pin the NPR experiment harness (issue #25) to rendered frames.

Issue #25 is an experiment issue: the techniques it adds are hypotheses, and the evidence
for or against each one is a capture. That makes this test the harness's other half — for
every technique it asserts the SPECIFIC visual property the technique claims, not merely
that pixels changed:

  A  the default frame and --npr=off are byte-identical: OFF is the state every banked
     capture was made in, and the whole harness is additive or it is a regression;
  B  the hard 2-band arm quantises the character's luminance to a handful of levels while
     the soft and 3-band arms keep more (a step, not a gradient), and the 3-band arm's
     darkest band is darker than the 2-band's;
  C  the shadow tint moves the SHADOWED pixels towards the tint's hue and leaves the LIT
     ones alone — the point of tinting the diffuse term rather than the whole lit colour;
  D  the character key light brightens the character (it is an added term, never a
     replacement) and the two arms put that brightness in different places;
  E  the secondary normals change the surface shading without moving the silhouette by a
     pixel (the experiment's whole claim: coarser lighting, same mesh);
  F  the generated mask changes the band boundary relative to the same curve with the mask
     pinned neutral (mask:0), which is the control arm;
  G/H the specular and rim add light and nothing else: no pixel gets darker;
  I  the outline width scales the rim: a wider hull adds silhouette pixels, a thinner one
     removes them, and the recovered 1.0 is the frame --toon already produced;
  #27 every arm's OWN parameter is probed at an extreme and must change the frame: an arm
     that renders byte-identical to its control there is a silent no-op, and the arms that
     are inert today are named in KNOWN_INERT with the reason and the issue that owes the
     fix (so a no-op cannot pass as a subtle improvement, and the list must shrink when a
     fix lands - an arm that starts drawing again fails here).

Every measurement is against a frame captured in the same run of the same binary with the
same camera, pose and stage, so the only variable is the flag.

Usage:
    npr_experiments.py <foundation_demo> <install-dir> [workdir]

Exit 0 when every measurement holds, 1 otherwise, and 77 (skip) when the renderer or the
game data is unavailable, so a CI box without a GPU or the install does not report a false
failure.
"""
import os
import subprocess
import sys
import tempfile

SKIP = 77

# The clear colour the scene pass writes (scenes.cpp:736, D3DCOLOR_XRGB(40,42,54)): every
# pixel that is not this is geometry.
BACKGROUND = (40, 42, 54)

# 800x600 is the original's own canvas, which is what the outline constants are sized for.
SIZE = "800x600"

CHARACTER_DIRS = ("rena", "rika", "akane", "mion")

# ---------------------------------------------------------------------------------------
# The no-op check (issue #27): every arm is probed at an EXTREME of its own parameter, and
# an arm whose extreme renders byte-identical to its control is a silent no-op - it must
# not be able to pass as a subtle improvement. An arm that IS inert today is listed in
# KNOWN_INERT with the reason and the issue that owes the fix; the run prints it every
# time, and an arm that starts drawing again FAILS here so the list cannot rot - it has to
# shrink when the fix lands. Probes are (label, on-args, control-args).
#
# The close-up probes run on the scene this file has always used (800x600, character only).
# The fight probes run the same arms inside a real match frame, because an arm can be alive
# in a stage-less close-up and dead in a scene that draws a stage first - that is issue
# #27's E finding, and its pair (H, which reaches) is the control that proves the fight
# path itself is alive.
# ---------------------------------------------------------------------------------------
CLOSE_NOOP_PROBES = [
    ("B bands hard, neutral tint", ["--npr=bands:hard,shadow:none"], []),
    ("B bands soft 0.06, neutral tint", ["--npr=bands:soft,shadow:none"], []),
    ("B bands soft width 0.30, neutral tint", ["--npr=bands:soft,soft:0.3,shadow:none"], []),
    ("B bands soft width 1.00, neutral tint", ["--npr=bands:soft,soft:1.0,shadow:none"], []),
    ("B bands three, neutral tint", ["--npr=bands:three,shadow:none"], []),
    ("C shadow tint, default", ["--npr=bands:soft,shadow"], ["--npr=bands:soft,shadow:none"]),
    ("C shadow tint, saturated", ["--npr=bands:soft,shadow:#ff00ff"],
     ["--npr=bands:soft,shadow"]),
    ("D key light, camera-relative", ["--npr=bands:soft,shadow,key:cam"],
     ["--npr=bands:soft,shadow"]),
    ("D key light, character-relative", ["--npr=bands:soft,shadow,key:fixed"],
     ["--npr=bands:soft,shadow"]),
    ("D key strength 1.5", ["--npr=bands:soft,shadow,key:cam,keystr:1.5"],
     ["--npr=bands:soft,shadow,key:cam"]),
    ("E secondary normals (close-up)", ["--npr=normals"], []),
    ("F mask scale 1, neutral tint", ["--npr=bands:hard,shadow:none,mask:1"],
     ["--npr=bands:hard,shadow:none,mask:0"]),
    ("G specular", ["--npr=spec"], []),
    ("G specular strength 2", ["--npr=spec,specstr:2"], ["--npr=spec"]),
    ("H rim light", ["--npr=rim"], []),
    ("H rim strength 2", ["--npr=rim,rimstr:2"], ["--npr=rim"]),
    ("I outline width 2 over --toon", ["--toon", "--npr=outline:2"], ["--toon"]),
]

FIGHT_NOOP_PROBES = [
    ("E secondary normals in a fight scene", ["--npr=normals"], []),
    ("H rim light in a fight scene", ["--npr=rim"], []),
]

KNOWN_INERT = {
    "B bands hard, neutral tint":
        "#27: the curve only weights the shadow tint, so with a neutral tint "
        "mix(tint, white, w) is white for every w (model_wgsl.h:385) and the frame is "
        "byte-identical to no band at all",
    "B bands soft 0.06, neutral tint": "#27: as above - the 'band' never bands the shading",
    "B bands soft width 0.30, neutral tint": "#27: the width only shapes the tint weight",
    "B bands soft width 1.00, neutral tint": "#27: the width only shapes the tint weight",
    "F mask scale 1, neutral tint":
        "#27: the mask only moves the band edge, and the band edge is invisible while the "
        "tint is neutral (model_wgsl.h:383)",
    "E secondary normals in a fight scene":
        "#27: the renderer caches ONE pipeline per pass, so a scene that draws its stage "
        "first never takes the NPR vertex entry (scene_renderer.cpp, boundPipelines) - the "
        "close-up probe above proves the technique itself draws",
}


def noop_check(run, probes, scene, scene_label, failures, tmp):
    """Probe every arm at an extreme; an identity is a no-op unless KNOWN_INERT names it."""
    inert_seen, probed = [], 0
    for label, on_args, off_args in probes:
        on_path = os.path.join(tmp, "noop_on.ppm")
        off_path = os.path.join(tmp, "noop_off.ppm")
        if (run(on_path, scene + on_args) is None or run(off_path, scene + off_args) is None):
            failures.append("the no-op probe '%s' (%s) did not render" % (label, scene_label))
            continue
        probed += 1
        with open(on_path, "rb") as handle:
            on_bytes = handle.read()
        with open(off_path, "rb") as handle:
            off_bytes = handle.read()
        if on_bytes == off_bytes:
            if label in KNOWN_INERT:
                inert_seen.append(label)
            else:
                failures.append("NO-OP: '%s' (%s) renders byte-identical to its control: the "
                                "arm's own parameter is not reaching the picture"
                                % (label, scene_label))
        elif label in KNOWN_INERT:
            failures.append("'%s' now differs from its control: the arm draws again, so "
                            "remove it from KNOWN_INERT" % label)
    print("  #27 no-op check (%s): %d arms probed at an extreme, %d known inert"
          % (scene_label, probed, len(inert_seen)))
    for label in inert_seen:
        print("    KNOWN INERT %s - %s" % (label, KNOWN_INERT[label]))


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


def luminance(pixel):
    return 0.2126 * pixel[0] + 0.7152 * pixel[1] + 0.0722 * pixel[2]


def character_pixels(frame):
    """(index, pixel) for every pixel that is not the clear colour."""
    w, h, px = frame
    out = []
    for i in range(0, len(px), 3):
        p = (px[i], px[i + 1], px[i + 2])
        if p != BACKGROUND:
            out.append((i, p))
    return out


# The patch the band metrics read: a 40x40 block of the character's SKIRT, whose
# material is one flat colour under a smooth surface. A whole-character level count
# measures the texture and the albedo, not the curve; one smooth surface is where a band
# is a band. The framing is identical across the arms (the same --camera auto framing, and
# the harness prints it), so the patch is the same piece of surface in every frame.
PATCH = (360, 400, 40, 40)


def patch_levels(frame, quant=3.0):
    """Distinct quantised luminance levels inside PATCH, over non-background pixels."""
    w, h, px = frame
    x0, y0, pw, ph = PATCH
    levels = set()
    for y in range(y0, min(y0 + ph, h)):
        for x in range(x0, min(x0 + pw, w)):
            i = (y * w + x) * 3
            p = (px[i], px[i + 1], px[i + 2])
            if p == BACKGROUND:
                continue
            levels.add(int(luminance(p) / quant))
    return len(levels)


def patch_spread(frame):
    """Max minus min luminance inside PATCH: a band has one level, a gradient has many."""
    w, h, px = frame
    x0, y0, pw, ph = PATCH
    lo, hi = 256.0, -1.0
    for y in range(y0, min(y0 + ph, h)):
        for x in range(x0, min(x0 + pw, w)):
            i = (y * w + x) * 3
            p = (px[i], px[i + 1], px[i + 2])
            if p == BACKGROUND:
                continue
            v = luminance(p)
            lo = min(lo, v)
            hi = max(hi, v)
    return (hi - lo) if hi >= lo else 0.0


def patch_darkest(frame):
    """The darkest character pixel in the frame: where the lowest band lands."""
    lo = 256.0
    for _, p in character_pixels(frame):
        lo = min(lo, luminance(p))
    return lo if lo <= 255.0 else 0.0


def mean_rgb(pixels):
    if not pixels:
        return (0.0, 0.0, 0.0)
    n = float(len(pixels))
    return (sum(p[0] for p in pixels) / n, sum(p[1] for p in pixels) / n,
            sum(p[2] for p in pixels) / n)


def compare(on_path, off_path):
    """Per-pixel comparison of two frames of the same scene."""
    on, off = read_ppm(on_path), read_ppm(off_path)
    if on is None or off is None or on[:2] != off[:2]:
        return None
    w, h, a = off
    _, _, b = on
    stats = {"off_px": 0, "on_px": 0, "added": 0, "lost": 0, "changed": 0,
             "darker": 0, "brighter": 0, "delta": 0.0}
    for i in range(0, len(a), 3):
        pa = (a[i], a[i + 1], a[i + 2])
        pb = (b[i], b[i + 1], b[i + 2])
        off_here = pa != BACKGROUND
        on_here = pb != BACKGROUND
        if off_here:
            stats["off_px"] += 1
            # The brighter/darker split is only meaningful on pixels that are surface in
            # BOTH frames. A technique that widens the silhouette (the outline, a rim)
            # adds pixels whose value is by definition not comparable with the background
            # they replaced, and counting those as "darkened" made every additive term
            # look like it removed light.
            if on_here:
                if pa != pb:
                    stats["changed"] += 1
                    d = luminance(pb) - luminance(pa)
                    stats["delta"] += d
                    if d < -0.5:
                        stats["darker"] += 1
                    elif d > 0.5:
                        stats["brighter"] += 1
            else:
                stats["lost"] += 1
        if on_here:
            stats["on_px"] += 1
            if not off_here:
                stats["added"] += 1
    return stats


def shifted_pixels(on_path, off_path, mask_path):
    """Mean rgb of the pixels that moved, split by whether they got darker or lighter.

    `mask_path` is the control frame whose silhouette decides which pixels belong to the
    character, so a technique that adds a rim does not smuggle rim pixels into the mean.
    """
    on, off = read_ppm(on_path), read_ppm(off_path)
    mask = read_ppm(mask_path)
    if on is None or off is None or mask is None or on[:2] != off[:2] or on[:2] != mask[:2]:
        return None
    w, h, a = off
    _, _, b = on
    _, _, m = mask
    dark, light = [], []
    for i in range(0, len(a), 3):
        if (m[i], m[i + 1], m[i + 2]) == BACKGROUND:
            continue
        pa = (a[i], a[i + 1], a[i + 2])
        pb = (b[i], b[i + 1], b[i + 2])
        if pa == pb:
            continue
        (dark if luminance(pb) < luminance(pa) else light).append(pb)
    return (mean_rgb(dark), len(dark)), (mean_rgb(light), len(light))


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        return 2
    demo = os.path.abspath(sys.argv[1])
    install = os.path.abspath(sys.argv[2])
    cwd = os.path.abspath(sys.argv[3]) if len(sys.argv) > 3 else os.getcwd()
    if not os.path.exists(os.path.join(install, "data")):
        print("npr_experiments: no game data at %s, skipped" % install)
        return SKIP
    fighter = None
    for name in CHARACTER_DIRS:
        candidate = os.path.join(install, "data", name)
        if os.path.isdir(candidate):
            fighter = candidate
            break
    # A fight frame needs two roster fighters, and rule 7 says a combo, never a bare
    # fighter: the versus path attaches each character's slot-0 weapon itself.
    enemy = None
    for name in ("mion",) + CHARACTER_DIRS:
        candidate = os.path.join(install, "data", name)
        if os.path.isdir(candidate) and candidate != fighter:
            enemy = candidate
            break
    stage = os.path.join(install, "data", "stage01")
    if fighter is None or not os.path.isdir(stage):
        print("npr_experiments: no character or stage directory in %s, skipped" % install)
        return SKIP

    failures = []
    with tempfile.TemporaryDirectory() as tmp:
        scene = ["--character=" + fighter + ":0", "--no-anim", "--frames=3",
                 "--size=" + SIZE]
        cache = {}

        def capture(name, extra):
            if name in cache:
                return cache[name]
            path = os.path.join(tmp, name + ".ppm")
            if run_demo(demo, install, path, scene + extra, cwd) is None:
                return None
            cache[name] = path
            return path

        # --- A. OFF is the default, byte for byte -----------------------------------
        base = capture("base", [])
        off = capture("off", ["--npr=off"])
        if base is None or off is None:
            print("npr_experiments: headless renderer unavailable, skipped")
            return SKIP
        with open(base, "rb") as f:
            base_bytes = f.read()
        with open(off, "rb") as f:
            off_bytes = f.read()
        if base_bytes != off_bytes:
            failures.append("--npr=off differs from the default frame: OFF is not the "
                            "default rendering")

        base_frame = read_ppm(base)
        base_px = character_pixels(base_frame)
        if len(base_px) < 1000:
            failures.append("only %d character pixels in the frame: nothing to measure"
                            % len(base_px))
            print("npr_experiments: FAIL")
            for line in failures:
                print("  " + line)
            return 1
        print("  A baseline: %d character px, skirt patch %d levels, spread %.1f"
              % (len(base_px), patch_levels(base_frame), patch_spread(base_frame)))

        # --- B. the banding curves --------------------------------------------------
        hard = capture("hard", ["--npr=bands:hard,shadow"])
        soft = capture("soft", ["--npr=bands:soft,shadow"])
        three = capture("three", ["--npr=bands:three,shadow"])
        if hard and soft and three:
            f_hard, f_soft, f_three = read_ppm(hard), read_ppm(soft), read_ppm(three)
            wide = capture("softwide", ["--npr=bands:soft,soft:0.3,shadow"])
            hard_stats = compare(hard, base)
            soft_stats = compare(soft, base)
            three_stats = compare(three, base)
            print("  B bands: changed px hard %d, soft %d, three %d (of %d)"
                  % (hard_stats["changed"], soft_stats["changed"], three_stats["changed"],
                     hard_stats["off_px"]))
            for label, st in (("hard", hard_stats), ("soft", soft_stats),
                              ("three", three_stats)):
                # A quarter of the silhouette is the bar: the curve reaches the shadowed
                # side of every surface, and the number is well above the ~10% the tint
                # alone would touch if the band term were inert.
                if st["changed"] < 0.25 * st["off_px"]:
                    failures.append("the %s band changed only %d of %d pixels: the curve is "
                                    "not reaching the surface"
                                    % (label, st["changed"], st["off_px"]))
            # How much the CURVE ITSELF matters: hard against soft at the default width,
            # and against a deliberately wide transition. The measured answer is the
            # finding — at 0.06 the two are nearly the same picture on this character
            # (2575 px of 72284), and a 0.3 transition is what separates them (14345 px).
            hs = compare(soft, hard)
            print("  B bands: hard vs soft (width 0.06) %d px, vs width 0.3 %d px"
                  % (hs["changed"], compare(wide, hard)["changed"] if wide else -1))
            if hs["changed"] >= 0.4 * hard_stats["off_px"]:
                failures.append("hard and soft differ on %d px: the smoothstep is not a "
                                "short transition at the default width" % hs["changed"])
            if wide is None or compare(wide, hard)["changed"] < 2 * hs["changed"]:
                failures.append("a 0.3-wide transition does not separate the curves more "
                                "than the 0.06 default: the softness parameter is inert")
            # The third band: it must darken a real region of the shadow side relative to
            # the same curve without it. (Not "the darkest pixel is darker": the outline
            # hull and the alpha-tested texels both reach black on their own, so a
            # minimum-based metric cannot see a band at all.)
            th = compare(three, hard)
            print("  B bands: the 3-band arm is darker than the 2-band on %d px"
                  % th["darker"])
            if th["darker"] < 0.05 * th["off_px"]:
                failures.append("the 3-band arm darkened only %d px against the 2-band "
                                "curve: the third band is not drawing" % th["darker"])
            # It is not perfectly monotone: the lower edge moves with the generated mask,
            # so a few pixels near the boundary land in the upper band's transition
            # instead of the core. The measured share is ~19% of the darkened set, which
            # is a boundary effect and not the band failing to draw — the check is there
            # so a curve that LIGHTENS the shadow side overall still fails.
            if th["brighter"] > 0.3 * th["darker"]:
                failures.append("the 3-band arm lightened %d px against %d darkened: the "
                                "third band is not a darker shadow"
                                % (th["brighter"], th["darker"]))
        else:
            failures.append("a band arm did not render")

        # --- C. colored shadows -----------------------------------------------------
        nomask = capture("nomask", ["--npr=bands:soft,shadow,mask:0"])
        neutral = capture("neutral", ["--npr=bands:soft,shadow:none,mask:0"])
        if nomask and neutral:
            # The control is the SAME curve with a neutral tint, not the baseline: the band
            # edge and the outline are then identical between the two frames and the only
            # variable left is the colour, which is what this experiment is about.
            split = shifted_pixels(nomask, neutral, neutral)
            if split is None:
                failures.append("the shadow-tint frames are not comparable PPMs")
            else:
                (dark_rgb, n_dark), (light_rgb, n_light) = split
                print("  C shadow: %d px darkened to rgb(%.0f,%.0f,%.0f), %d lightened to "
                      "rgb(%.0f,%.0f,%.0f)"
                      % (n_dark, dark_rgb[0], dark_rgb[1], dark_rgb[2],
                         n_light, light_rgb[0], light_rgb[1], light_rgb[2]))
                if n_dark < 0.1 * len(base_px):
                    failures.append("the shadow tint darkened only %d px: the shadow side "
                                    "is not being tinted" % n_dark)
                # The default tint is the violet-grey (0.86, 0.74, 0.78): red must come
                # out on top, which is what "tinted, not just darkened" means.
                # The control's darkened pixels, for the same curve with a neutral tint:
                # the tint has to move the shadowed side's HUE, and comparing the two arms'
                # shadowed sets is what isolates that from the material colours the
                # character's own textures carry.
                ctrl = shifted_pixels(neutral, base, base)
                if ctrl is None:
                    failures.append("the neutral-tint control is not comparable")
                else:
                    (ctrl_rgb, n_ctrl), _ = ctrl
                    print("  C shadow: neutral-tint control darkened %d px to "
                          "rgb(%.0f,%.0f,%.0f)" % (n_ctrl, ctrl_rgb[0], ctrl_rgb[1],
                                                   ctrl_rgb[2]))
                    # The default tint is (0.86, 0.74, 0.78): its red is the largest and
                    # its green the smallest, so the tinted shadow must shift that way
                    # relative to the neutral one.
                    if dark_rgb[0] / max(dark_rgb[1], 1e-3) <= ctrl_rgb[0] / max(ctrl_rgb[1], 1e-3):
                        failures.append("the shadow tint did not raise the red/green ratio "
                                        "(tinted %.3f against neutral %.3f): the shadowed "
                                        "side is not tinted"
                                        % (dark_rgb[0] / max(dark_rgb[1], 1e-3),
                                           ctrl_rgb[0] / max(ctrl_rgb[1], 1e-3)))
                    if dark_rgb[0] <= dark_rgb[2]:
                        failures.append("the darkened pixels' mean rgb(%.0f,%.0f,%.0f) has no "
                                        "red over blue: the violet-grey tint is not applied"
                                        % dark_rgb)
                if n_light > 0.2 * n_dark:
                    failures.append("%d px got lighter under a shadow-only experiment: the "
                                    "tint is reaching the lit side" % n_light)
        else:
            failures.append("the shadow-tint arm did not render")

        # --- D. character key light -------------------------------------------------
        keyfix = capture("keyfix", ["--npr=bands:soft,shadow,key:fixed"])
        keycam = capture("keycam", ["--npr=bands:soft,shadow,key:cam"])
        if keyfix and keycam:
            fx, cx = compare(keyfix, nomask), compare(keycam, nomask)
            print("  D key: fixed +%d/-%d px, cam +%d/-%d px (brighter/darker)"
                  % (fx["brighter"], fx["darker"], cx["brighter"], cx["darker"]))
            for label, st in (("fixed", fx), ("cam", cx)):
                if st["brighter"] < 0.05 * st["off_px"]:
                    failures.append("the %s key light brightened only %d px: the key is "
                                    "not being added" % (label, st["brighter"]))
                if st["darker"] > 0.2 * st["brighter"]:
                    failures.append("the %s key light darkened %d px against %d brightened: "
                                    "it is replacing the world light, not adding to it"
                                    % (label, st["darker"], st["brighter"]))
            if fx["brighter"] and cx["brighter"]:
                # The two arms must not be the same picture: they light from different
                # directions, which is the whole reason the experiment has two of them.
                diff = compare(keycam, keyfix)
                if diff["changed"] < 0.05 * diff["off_px"]:
                    failures.append("the fixed and camera-relative key arms differ on only "
                                    "%d px: they are the same light" % diff["changed"])
        else:
            failures.append("a key-light arm did not render")

        # --- E. secondary lighting normals ------------------------------------------
        normals = capture("normals", ["--npr=normals"])
        if normals:
            st = compare(normals, base)
            print("  E normals: %d px changed, silhouette added %d lost %d"
                  % (st["changed"], st["added"], st["lost"]))
            if st["changed"] < 0.1 * st["off_px"]:
                failures.append("the secondary normals changed only %d of %d surface px: "
                                "the stream is not reaching the lighting"
                                % (st["changed"], st["off_px"]))
            # The experiment's whole claim: a coarser LIGHTING normal, the same mesh.
            if st["added"] or st["lost"]:
                failures.append("the secondary normals moved the silhouette by %d/%d px: "
                                "they are not lighting-only" % (st["added"], st["lost"]))
        else:
            failures.append("the normals arm did not render")

        # --- G/H. specular and rim add light, never remove it ------------------------
        for label, args in (("spec", ["--npr=spec"]), ("rim", ["--npr=rim"])):
            path = capture(label, args)
            if not path:
                failures.append("the %s arm did not render" % label)
                continue
            st = compare(path, base)
            print("  %s %s: %d px changed, +%d/-%d brighter/darker"
                  % (label.upper(), label, st["changed"], st["brighter"], st["darker"]))
            if st["brighter"] < 0.005 * st["off_px"]:
                failures.append("the %s arm brightened only %d px: the term is not drawing"
                                % (label, st["brighter"]))
            if st["darker"] > 0.1 * st["brighter"]:
                failures.append("the %s arm darkened %d px: it is an additive term and "
                                "must not remove light" % (label, st["darker"]))

        # --- I. outline width -------------------------------------------------------
        toon1 = capture("outline1", ["--toon", "--npr=outline:1"])
        toon2 = capture("outline2", ["--toon", "--npr=outline:2"])
        toonhalf = capture("outlinehalf", ["--toon", "--npr=outline:0.4"])
        plain_toon = capture("toononly", ["--toon"])
        if toon1 and toon2 and toonhalf and plain_toon:
            with open(toon1, "rb") as f:
                o1 = f.read()
            with open(plain_toon, "rb") as f:
                pt = f.read()
            if o1 != pt:
                failures.append("--npr=outline:1 differs from --toon alone: the recovered "
                                "hull width is not the identity of the experiment")
            wide = compare(toon2, toon1)
            thin = compare(toonhalf, toon1)
            print("  I outline: x2 added %d/lost %d px, x0.4 added %d/lost %d px"
                  % (wide["added"], wide["lost"], thin["added"], thin["lost"]))
            if wide["added"] <= wide["lost"]:
                failures.append("a 2x hull did not widen the rim (+%d/-%d px)"
                                % (wide["added"], wide["lost"]))
            if thin["lost"] <= thin["added"]:
                failures.append("a 0.4x hull did not thin the rim (+%d/-%d px)"
                                % (thin["added"], thin["lost"]))
        else:
            failures.append("an outline-width arm did not render")

        # --- the composed stack is not any single arm -------------------------------
        stack = capture("stack", ["--npr=on"])
        if stack:
            st = compare(stack, base)
            print("  stack: %d px changed (+%d/-%d)" % (st["changed"], st["brighter"],
                                                        st["darker"]))
            if st["changed"] < 0.3 * st["off_px"]:
                failures.append("the composed stack changed only %d px" % st["changed"])

        # --- a stage-only frame must not move ---------------------------------------
        stage_args = ["--stage=" + stage, "--no-anim", "--frames=3", "--size=400x300"]
        stage_off = os.path.join(tmp, "stage_off.ppm")
        stage_on = os.path.join(tmp, "stage_on.ppm")
        if (run_demo(demo, install, stage_off, stage_args + ["--npr=off"], cwd) is not None
                and run_demo(demo, install, stage_on, stage_args + ["--npr=on"], cwd)
                is not None):
            with open(stage_off, "rb") as f:
                a = f.read()
            with open(stage_on, "rb") as f:
                b = f.read()
            if a != b:
                failures.append("--npr=on moved a stage-only frame: the experiments are "
                                "reaching draws they do not cover")
            else:
                print("  stage-only frame: identical with the stack on and off")
        else:
            print("  stage-only frame: skipped (stage render unavailable)")

        # --- issue #27: no arm may be a silent no-op --------------------------------
        noop_check(lambda out, args: run_demo(demo, install, out, args, cwd),
                   CLOSE_NOOP_PROBES, scene, "close-up 800x600", failures, tmp)
        # The fight frame needs the match assembly, not the close-up scene: same arms,
        # where the product draws them. 120 frames is enough for the fighters to be on
        # screen and keeps the suite's cost down.
        if enemy is None:
            print("  #27 no-op check (fight scene): skipped, only one character directory")
        else:
            fight_scene = ["--stage=" + stage, "--character=" + fighter + ":0",
                           "--enemy=" + enemy + ":0", "--versus", "--camera=arena",
                           "--frames=120", "--size=960x540"]
            noop_check(lambda out, args: run_demo(demo, install, out, args, cwd),
                       FIGHT_NOOP_PROBES, fight_scene, "fight scene 960x540", failures, tmp)

    if failures:
        print("npr_experiments: FAIL")
        for line in failures:
            print("  " + line)
        return 1
    print("npr_experiments: OFF is the default byte for byte, every technique shows its own "
          "measured property, a stage-only frame never moves, and no arm's parameter is "
          "silently inert (the arms listed KNOWN INERT above are issue #27's open defect)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
