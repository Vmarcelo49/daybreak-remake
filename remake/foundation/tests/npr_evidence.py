#!/usr/bin/env python3
"""NPR experiment evidence (issue #27): contact sheets and region-restricted metrics.

Issue #25 delivered the `--npr` harness and a recommendation, and issue #27 rejected the
EVIDENCE behind it: the A/B prints look identical at a glance, only one resolution was
tested (800x600 bind pose), and "N pixels changed" cannot tell "the technique is subtle"
from "the technique is not running". This tool produces the evidence the acceptance list
asks for. It is a REPORT, not a gate: it exits 0 unless a capture itself fails.

  1. a contact sheet per technique: the three played resolutions side by side
     (640x360 / 960x540 / 1920x1080, native scale, same camera/pose/scene/lighting),
     off/on beside each other, plus zoomed crops of the face, the hair and the torso and
     the same face region magnified out of the 640x360 frame;
  2. region-restricted metrics per technique (silhouette rim, face, hair, torso, the whole
     figure, the pixels the arm actually touched, the background) with the before/after
     mean luminance and mean RGB, so a hue shift that keeps luminance is still measured;
  3. a no-op sanity check per technique: the technique's own parameter swept to its
     extremes (`shadow:#ff00ff`, `bands:soft,soft:1.0`, `specstr:2`, `mask:-1`, ...) at
     960x540. An arm whose parameter is ignored renders every sweep step byte-identical -
     which is the difference between "subtle" and "not running";
  4. one gameplay-distance frame per kept technique (`--versus`, stage01, arena camera,
     960x540) and one 4-view 2v2 capture (`--screen=battle --local-players=4`).

The scene is the #25 §2 one, with the combo rule honoured: **Rena 0** (竜宮レナ + 愛用の
鉈, `data/rena/00.x` + `data/item/01.x`), bind pose, no stage (so the background is the
pass's clear colour and the character mask is exact), `--camera=bounds`. `bounds` and not
`auto` because auto framing (distance = 2 x the bounds radius) clips the top of a weaponed
fighter's hair at 16:9 - measured 333 px of hair on the frame's first row at 1080p.

Nothing here changes the renderer: the tool runs the committed demo and measures its PPM
output. The NPR arms are PORT-SIDE EXPERIMENTS with no RE provenance and this file
inherits that label.

Usage:
    npr_evidence.py --demo <foundation_demo> --install <game dir> --outdir <evidence dir>
                    [--workdir <scratch>] [--only id,id] [--quick]

The evidence directory keeps the ../npr-evidence layout (captures/, logs/) and gains
metrics.json + metrics.md. Pass --only to re-render a subset of the sheets.
"""

import argparse
import hashlib
import json
import os
import subprocess
import sys
import time

import numpy as np
from PIL import Image, ImageDraw, ImageFont

# ---------------------------------------------------------------------------------------
# Scene, sizes and the measurement rule.
# ---------------------------------------------------------------------------------------

# The clear colour the scene pass writes (D3DCOLOR_XRGB(40,42,54)): with no stage behind
# the fighter every pixel that is not this is geometry.
CLEAR = (40, 42, 54)
BACKGROUND = np.array(CLEAR, dtype=np.int32)

# The three resolutions the issue names. All 16:9 and exact multiples, so a region defined
# as a fraction of the frame is the same piece of surface at each one.
RESOLUTIONS = (("640x360", 640, 360), ("960x540", 960, 540), ("1920x1080", 1920, 1080))
REF_W, REF_H = 1920, 1080

# The combo every close-up recipe binds: Rena's slot-0 weapon (kWeaponIds[0][0] = 1,
# data/item/01.x = 愛用の鉈). Rule 7: a capture recipe names both halves.
COMBO = "Rena 0 (favourite cleaver)"
CHARACTER_REL = "data/rena:0"
WEAPON_REL = "data/item/01.x"

CLOSE_ARGS = ("--no-anim", "--camera=bounds", "--frames=3")
GAMEPLAY_ARGS = ("--versus", "--camera=arena", "--frames=300")
GAMEPLAY_STAGE_REL = "data/stage01"
GAMEPLAY_ENEMY_REL = "data/mion:0"          # Mion 0: コテ拳銃, data/item/04.x
FOUR_ARGS = ("--screen=battle", "--local-players=4", "--frames=300")

# The one fully visible fighter in the versus frame at 300 frames is Mion (P2) at
# 250..320 x 150..250 of 960x540. A rectangle and not a mask - a stage fills the frame, so
# no character mask exists there - which is why it is reported as a magnitude with the box
# drawn on the sheet, never as a share of a figure.
GAMEPLAY_BOX = (250, 150, 320, 250)

# The metric regions, measured on the 1920x1080 control frame of the close-up scene and
# stored as fractions of the frame so the same piece of surface is measured at every
# resolution (the three sizes are exact multiples and share the world camera). The boxes
# are drawn on the sheets, so a reader can check what each one covers:
#   face  the eyes, nose and mouth, between the fringe and the chin
#   hair  the fringe and the top of the head above the eyebrows
#   torso the collar, the chest of the shirt and the arms that hold the cleaver
REGION_BOXES_1080P = {
    "face":  (890, 250, 1045, 370),
    "hair":  (874, 174, 1063, 250),
    "torso": (880, 350, 1050, 500),
}
REGIONS = {name: (x0 / REF_W, y0 / REF_H, x1 / REF_W, y1 / REF_H)
           for name, (x0, y0, x1, y1) in REGION_BOXES_1080P.items()}
# The skirt: one flat material over a smooth surface, which is where a band that really
# flattens the shading would show one value (see shadow_flatness()).
SKIRT_PATCH_1080P = (880, 500, 1080, 660)

# The silhouette rim: figure pixels within this many pixels of the figure's edge. Scaled
# with the frame so the band is the same piece of the character at every resolution (the
# recovered toon hull is ~1.1 px at 800x600, i.e. ~0.66/1.0/2.0 px here, so 2/3/6 px is a
# few hull widths).


def rim_radius(height):
    return max(2, int(round(0.006 * height)))


# Report thresholds. PORT-SIDE EVIDENCE RULE, not recovered and not a renderer constant:
# a technique "reads" when either a tenth of the figure's pixels move by 8/255 or more, or
# the figure's mean colour moves by 3/255; an arm is "obvious" at its extremes at 15% /
# 4/255. Both raw numbers are printed everywhere so a reader can apply their own bar.
READS_VISIBLE_SHARE = 0.10
READS_MEAN_DE = 3.0
OBVIOUS_VISIBLE_SHARE = 0.15
OBVIOUS_MEAN_DE = 4.0
VISIBLE_CHANNEL_DELTA = 8

# ---------------------------------------------------------------------------------------
# The arms. `off` and `on` are the extra argv of the two frames of a sheet; a control frame
# shared by several sheets is captured once and reused.
# ---------------------------------------------------------------------------------------

TOON = ("--toon",)

TECHNIQUES = [
    dict(id="B", label="B bands - soft 0.06 (the curve alone, neutral tint)",
         off=(), on=("--npr=bands:soft,shadow:none",),
         question="the band curve: the doc's claim is that it replaces the shadowed side "
                  "of a surface with one flat value"),
    dict(id="C", label="C coloured shadow (the default violet-grey tint)",
         off=("--npr=bands:soft,shadow:none",), on=("--npr=bands:soft,shadow",),
         question="the shadowed side tinted instead of grey; only the diffuse term"),
    dict(id="D", label="D character key light (camera-relative)",
         off=("--npr=bands:soft,shadow",), on=("--npr=bands:soft,shadow,key:cam",),
         question="an added key light that follows the camera"),
    dict(id="E", label="E secondary lighting normals",
         off=(), on=("--npr=normals",),
         question="the generated coarse normals light the surface instead of the mesh's"),
    dict(id="F", label="F generated shadow mask (over bands:hard, tinted)",
         off=("--npr=bands:hard,shadow,mask:0",), on=("--npr=bands:hard,shadow,mask:1",),
         question="the generated per-vertex mask moves the band boundary"),
    dict(id="G", label="G stylized hard-threshold specular",
         off=(), on=("--npr=spec",),
         question="a drawn highlight on the hair and the metal"),
    dict(id="H", label="H character rim light",
         off=(), on=("--npr=rim",),
         question="a fresnel edge on the character's silhouette"),
    dict(id="I", label="I outline width x2 (over the recovered toon row)",
         off=TOON, on=TOON + ("--npr=outline:2",),
         question="the recovered hull drawn wider"),
    dict(id="STACK", label="the recommended stack (--npr=on)",
         off=(), on=("--npr=on",),
         question="everything the #25 recommendation keeps, together"),
    dict(id="STACK_toon", label="the stack over the recovered toon row",
         off=TOON, on=TOON + ("--npr=on",),
         question="what the recommended state would look like in the product"),
]

# The sanity sweeps (acceptance item 3): one parameter at a time, its extremes included.
# The first step is the control the delta columns and the identity check are measured
# against. `claim` names the steps that must NOT be identical to the control for the arm's
# own claim to hold, and says what an identity there means - a claim that fails is a
# measured statement, not a guess. `pairs` are step-to-step comparisons the arm's own
# argument needs (e.g. "hard against soft at the shipped width").
SWEEPS = [
    dict(id="B-curve", label="B - the band curve at the shipped width, tinted and neutral",
         steps=[("off (no flag)", ()),
                ("hard, tinted", ("--npr=bands:hard,shadow",)),
                ("hard, neutral tint", ("--npr=bands:hard,shadow:none",)),
                ("soft 0.06, tinted", ("--npr=bands:soft,shadow",)),
                ("soft 0.06, neutral tint", ("--npr=bands:soft,shadow:none",)),
                ("three, tinted", ("--npr=bands:three,shadow",)),
                ("three, neutral tint", ("--npr=bands:three,shadow:none",))],
         claim=dict(indices=[2, 4, 6],
                    holds="the curve multiplies the shading itself, so it changes the "
                          "picture with the shadow tint held neutral",
                    fails="the curve only selects how much of the shadow TINT is applied: "
                          "with a neutral tint mix(tint, white, w) is white for every w, so "
                          "the frame is byte-identical and the 'band' never bands the "
                          "shading (model_wgsl.h:385)"),
         pairs=[(1, 2, "hard tinted against hard neutral"),
                (3, 4, "soft 0.06 tinted against soft 0.06 neutral"),
                (5, 6, "three tinted against three neutral"),
                (1, 3, "hard against soft 0.06, both tinted")],
         expect="the three curves must draw different pictures, and the curve must be what "
                "draws them - not the tint it multiplies"),
    dict(id="B-softness", label="B - the softness parameter soft:<f> (neutral tint)",
         steps=[("off (no flag)", ()),
                ("hard (no softness)", ("--npr=bands:hard,shadow:none",)),
                ("soft 0.02", ("--npr=bands:soft,soft:0.02,shadow:none",)),
                ("soft 0.06 (default)", ("--npr=bands:soft,soft:0.06,shadow:none",)),
                ("soft 0.30", ("--npr=bands:soft,soft:0.3,shadow:none",)),
                ("soft 1.00", ("--npr=bands:soft,soft:1.0,shadow:none",)),
                ("soft 1.00, default tint", ("--npr=bands:soft,soft:1.0,shadow",))],
         claim=dict(indices=[1, 2, 3, 4, 5],
                    holds="the width moves the terminator, so every width changes the "
                          "picture",
                    fails="the width has no effect on the picture at all: the smoothstep "
                          "only shapes the tint weight, which is invisible while the tint "
                          "is neutral"),
         pairs=[(3, 5, "soft 0.06 against soft 1.00, both with a neutral tint"),
                (5, 6, "soft 1.00 neutral against soft 1.00 tinted")],
         expect="each width must move the terminator further than the last"),
    dict(id="C-tint", label="C - the shadow tint shadow:<#rrggbb>",
         steps=[("none (neutral)", ("--npr=bands:soft,shadow:none",)),
                ("default #dbc0c7", ("--npr=bands:soft,shadow",)),
                ("saturated #ff00ff", ("--npr=bands:soft,shadow:#ff00ff",))],
         claim=dict(indices=[1, 2],
                    holds="the tint colours the shadowed side, so it changes the picture",
                    fails="the tint is ignored"),
         expect="the tinted shadow must move hue, and a saturated tint obviously so"),
    dict(id="D-arm", label="D - the key arm key:fixed|cam",
         steps=[("off", ("--npr=bands:soft,shadow",)),
                ("fixed", ("--npr=bands:soft,shadow,key:fixed",)),
                ("cam", ("--npr=bands:soft,shadow,key:cam",))],
         claim=dict(indices=[1, 2],
                    holds="the key adds light, so both arms change the picture",
                    fails="the key is not drawing"),
         pairs=[(1, 2, "the two key arms against each other")],
         expect="the two arms are different lights and both add light"),
    dict(id="D-strength", label="D - the key strength keystr:<f> (key:cam)",
         steps=[("0", ("--npr=bands:soft,shadow,key:cam,keystr:0",)),
                ("0.35 (default)", ("--npr=bands:soft,shadow,key:cam",)),
                ("1.5", ("--npr=bands:soft,shadow,key:cam,keystr:1.5",))],
         claim=dict(indices=[1, 2],
                    holds="the brightness follows the strength, so each step changes the "
                          "picture",
                    fails="the strength parameter is ignored"),
         expect="the brightness must follow the strength"),
    dict(id="E-normals", label="E - the secondary normals normals|nonormals",
         steps=[("off", ()), ("nonormals", ("--npr=nonormals",)),
                ("normals", ("--npr=normals",))],
         claim=dict(indices=[2],
                    holds="lighting the secondary stream re-shades the surface",
                    fails="the secondary normals never reach the lighting"),
         expect="lighting the secondary stream must visibly re-shade the surface"),
    dict(id="F-mask", label="F - the generated mask scale mask:<f>",
         steps=[("mask 0, neutral tint (the control)", ("--npr=bands:hard,shadow:none,mask:0",)),
                ("mask 1, neutral tint", ("--npr=bands:hard,shadow:none,mask:1",)),
                ("mask -1, tinted", ("--npr=bands:hard,shadow,mask:-1",)),
                ("mask 0, tinted", ("--npr=bands:hard,shadow,mask:0",)),
                ("mask 1, tinted", ("--npr=bands:hard,shadow,mask:1",)),
                ("mask 3, tinted", ("--npr=bands:hard,shadow,mask:3",))],
         claim=dict(indices=[1],
                    holds="the mask moves the band boundary, so with a neutral tint it still "
                          "moves the picture",
                    fails="the mask only moves the edge of the tint weight: with a neutral "
                          "tint it renders identically, so it cannot hold a band that the "
                          "shader never draws (model_wgsl.h:383)"),
         pairs=[(3, 4, "mask 0 against mask 1, both tinted"),
                (4, 5, "mask 1 against mask 3, both tinted")],
         expect="the scale must move the boundary, and inversion must move it the other way "
                "- with a neutral tint as well as with the shipped one"),
    dict(id="G-spec", label="G - the specular strength/tint",
         steps=[("off", ()),
                ("0.35 (default)", ("--npr=spec",)),
                ("tint #ff00ff, str 2", ("--npr=spec,spectint:#ff00ff,specstr:2",))],
         claim=dict(indices=[1, 2],
                    holds="the highlight draws and grows with the strength",
                    fails="the specular term is not drawing"),
         expect="the highlight must grow with the strength and take the tint"),
    dict(id="H-rim", label="H - the rim strength/tint",
         steps=[("off", ()),
                ("0.30 (default)", ("--npr=rim",)),
                ("tint #00ff00, str 2", ("--npr=rim,rimtint:#00ff00,rimstr:2",))],
         claim=dict(indices=[1, 2],
                    holds="the rim draws and grows with the strength",
                    fails="the rim term is not drawing"),
         expect="the rim must grow with the strength and take the tint"),
    dict(id="I-outline", label="I - the outline width scale (--toon)",
         steps=[("--toon alone (the recovered width)", TOON),
                ("outline 0.25", TOON + ("--npr=outline:0.25",)),
                ("outline 1.0", TOON + ("--npr=outline:1",)),
                ("outline 2", TOON + ("--npr=outline:2",)),
                ("outline 3", TOON + ("--npr=outline:3",))],
         claim=dict(kind="identical", indices=[2],
                    holds="1.0 is the recovered width: byte-identical to --toon alone",
                    fails="the scale moved the recovered width"),
         pairs=[(0, 1, "0.25 against the recovered width"),
                (0, 3, "2 against the recovered width"),
                (3, 4, "3 against 2")],
         expect="a wider hull must widen the rim, a thinner one must thin it, and 1.0 must "
                "be --toon alone"),
]

# Which techniques the gameplay-distance sheet is produced for: the ones whose evidence
# passes the sanity check and the region metrics (acceptance item 4). Filled in after the
# review; re-run with --only gameplay after editing.
GAMEPLAY_FOR = ("E", "D", "C", "H", "G", "STACK")

FONT_CACHE = {}


def font(size):
    if size not in FONT_CACHE:
        FONT_CACHE[size] = ImageFont.load_default(size=size)
    return FONT_CACHE[size]


# ---------------------------------------------------------------------------------------
# Frames.
# ---------------------------------------------------------------------------------------

def read_ppm(path):
    with open(path, "rb") as handle:
        data = handle.read()
    if not data.startswith(b"P6"):
        raise RuntimeError("%s is not a binary PPM" % path)
    fields, i = [], 2
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
    return np.frombuffer(data[i:i + w * h * 3], dtype=np.uint8).reshape(h, w, 3)


def sha256(path):
    digest = hashlib.sha256()
    with open(path, "rb") as handle:
        for block in iter(lambda: handle.read(1 << 20), b""):
            digest.update(block)
    return digest.hexdigest()


class Frame:
    """One captured PPM plus everything measured about it."""

    def __init__(self, name, path):
        self.name = name
        self.raw = read_ppm(path)
        self.height, self.width = self.raw.shape[:2]
        self.array = self.raw.astype(np.int32)
        self.mask = character_mask(self.array)
        self.digest = sha256(path)

    def image(self):
        return Image.fromarray(self.raw)


class Rig:
    """Runs the committed demo; every capture goes through here."""

    def __init__(self, demo, install, workdir, logs_dir):
        self.demo = os.path.abspath(demo)
        self.install = os.path.abspath(install)
        self.workdir = os.path.abspath(workdir)
        self.logs_dir = os.path.abspath(logs_dir)
        self.frames = {}
        self.commands = {}
        os.makedirs(self.workdir, exist_ok=True)
        os.makedirs(self.logs_dir, exist_ok=True)

    def redact(self, text):
        """Committed artifacts name the scene, not this machine's directories (AGENTS.md:
        no absolute local paths in committed files). The placeholders are the repo-relative
        forms the other recipes use, so a command can still be copied and run."""
        for path, placeholder in ((self.install, "Higurashi-Daybreak"),
                                  (self.demo, "remake/foundation/build/linux/foundation_demo"),
                                  (self.workdir, "<workdir>")):
            text = text.replace(path, placeholder)
        return text

    def close_scene(self, extra):
        return ["--character=%s/%s" % (self.install, CHARACTER_REL),
                "--weapon=%s/%s" % (self.install, WEAPON_REL)] + list(CLOSE_ARGS) + list(extra)

    def run(self, name, argv, size):
        """Capture one frame; `name` + `size` identify it and are reused when repeated."""
        key = (name, size)
        if key in self.frames:
            return self.frames[key]
        path = os.path.join(self.workdir, "%s_%s.ppm" % (name, size))
        cmd = [self.demo, "--headless", "--install=" + self.install,
               "--out=" + path, "--size=" + size] + list(argv)
        proc = subprocess.run(cmd, cwd=self.workdir, stdout=subprocess.PIPE,
                              stderr=subprocess.STDOUT, text=True, timeout=3600)
        # The demo spams one line per frame when a weapon attachment frame is unusable;
        # keep the log but fold those into one line so the committed logs stay readable.
        lines, folded = [], 0
        for line in proc.stdout.splitlines():
            if "attachment frame" in line:
                folded += 1
                continue
            lines.append(line)
        if folded:
            lines.append("[%d repeated 'attachment frame unusable' lines folded]" % folded)
        log = "\n".join(lines) + "\n"
        if proc.returncode != 0 or "RESULT: ok" not in proc.stdout:
            raise RuntimeError("%s failed (exit %d)\n%s" % (" ".join(cmd), proc.returncode,
                                                            log[-4000:]))
        with open(os.path.join(self.logs_dir, "%s_%s.log" % (name, size)), "w") as handle:
            handle.write(self.redact("# %s\n%s" % (" ".join(cmd), log)))
        frame = Frame(name, path)
        self.frames[key] = frame
        self.commands.setdefault(name + "_" + size, self.redact(" ".join(cmd)))
        return frame


# ---------------------------------------------------------------------------------------
# Measurement.
# ---------------------------------------------------------------------------------------

def character_mask(array):
    """Every pixel that is not the pass's clear colour."""
    return np.abs(array - BACKGROUND).sum(axis=2) != 0


def region_masks(shape, width, height):
    """The metric regions as boolean masks at this frame size."""
    out = {}
    for name, (fx0, fy0, fx1, fy1) in REGIONS.items():
        x0, y0 = int(round(fx0 * width)), int(round(fy0 * height))
        x1, y1 = int(round(fx1 * width)), int(round(fy1 * height))
        box = np.zeros(shape, dtype=bool)
        box[y0:y1, x0:x1] = True
        out[name] = box
    return out


def rim_band(mask, radius):
    """Pixels of `mask` within `radius` pixels of its own edge (Chebyshev)."""
    eroded = mask.copy()
    for _ in range(radius):
        shifted = eroded
        for dy in (-1, 0, 1):
            for dx in (-1, 0, 1):
                if dx == 0 and dy == 0:
                    continue
                eroded = eroded & np.roll(np.roll(shifted, dy, axis=0), dx, axis=1)
    return mask & ~eroded


def luminance(array):
    return 0.2126 * array[:, :, 0] + 0.7152 * array[:, :, 1] + 0.0722 * array[:, :, 2]


def region_row(sel, off, on, delta, max_delta, d_lum):
    count = int(sel.sum())
    if count == 0:
        return dict(px=0)
    md = max_delta[sel]
    dl = d_lum[sel]
    drgb = delta[sel].astype(np.float64)
    return dict(
        px=count,
        changed=int((md > 0).sum()),
        visible=int((md >= VISIBLE_CHANNEL_DELTA).sum()),
        visible_share=float((md >= VISIBLE_CHANNEL_DELTA).mean()),
        mean_lum_off=float(luminance(off)[sel].mean()),
        mean_lum_on=float(luminance(on)[sel].mean()),
        mean_dlum=float(dl.mean()),
        mean_abs_dlum=float(np.abs(dl).mean()),
        mean_de=float(np.sqrt((drgb ** 2).sum(axis=1)).mean()),
        max_abs_drgb=[int(np.abs(drgb[:, c]).max()) for c in range(3)],
        mean_drgb=[float(drgb[:, c].mean()) for c in range(3)],
        mean_rgb_off=[float(off[sel][:, c].mean()) for c in range(3)],
        mean_rgb_on=[float(on[sel][:, c].mean()) for c in range(3)],
    )


def compare(off, on):
    """Region-restricted comparison of two frames of the same scene.

    Every row is restricted to the pixels that are geometry in at least one of the two
    frames, so a region is never diluted by the background and an additive rim cannot
    smuggle the background it replaced into a mean. `affected` is descriptive: it is the
    set the arm actually moved, reported with its share of the figure, because a mean over
    the whole figure hides a technique that only touches a small area - and its size is
    never the readability claim (the region rows are).
    """
    if off.array.shape != on.array.shape:
        raise RuntimeError("frames differ in size: %s vs %s" % (off.name, on.name))
    height, width = off.array.shape[:2]
    mask = off.mask | on.mask
    delta = on.array - off.array
    max_delta = np.abs(delta).max(axis=2)
    d_lum = luminance(on.array) - luminance(off.array)
    boxes = region_masks(mask.shape, width, height)
    rim = rim_band(mask, rim_radius(height))
    # Every region but the background is intersected with the figure: a region must never
    # be diluted by the pixels around it. The background row is the complement, and it is
    # the leak check - a character-only technique must not move a pixel of it.
    regions = {
        "whole": (mask, True),
        "rim": (rim, True),
        "interior": (mask & ~rim, True),
        "face": (boxes["face"], True),
        "hair": (boxes["hair"], True),
        "torso": (boxes["torso"], True),
        "affected": (max_delta > 0, True),
        "background": (~mask, False),
    }
    rows = {name: region_row(region & mask if clip else region, off.array, on.array, delta,
                             max_delta, d_lum)
            for name, (region, clip) in regions.items()}
    whole = rows["whole"]
    if whole.get("px"):
        rows["affected"]["share_of_figure"] = (rows["affected"].get("px", 0) / whole["px"])
    return dict(identical=bool(np.array_equal(off.raw, on.raw)), regions=rows,
                size=[width, height], sha256_off=off.digest, sha256_on=on.digest)


def shadow_flatness(neutral, tinted, patch=SKIRT_PATCH_1080P):
    """Is the tinted shadow ONE flat value (the doc's band claim) or still a gradient?

    The set is the pixels the tint moved, inside a patch of one flat material (the skirt)
    so the albedo is constant and the spread is the LIGHTING's spread. A real band would
    collapse the spread; a tint that multiplies an unbanded gradient keeps it (scaled by
    the tint's own luminance factor).
    """
    x0, y0, x1, y1 = patch
    sel = np.zeros(neutral.mask.shape, dtype=bool)
    sel[y0:y1, x0:x1] = True
    sel &= neutral.mask & tinted.mask
    sel &= (np.abs(tinted.array - neutral.array).max(axis=2) > 0)
    if sel.sum() < 50:
        return dict(px=int(sel.sum()))
    lo = luminance(neutral.array)[sel]
    ln = luminance(tinted.array)[sel]
    quantum = 2.0
    spread_off = float(np.percentile(lo, 95) - np.percentile(lo, 5))
    spread_on = float(np.percentile(ln, 95) - np.percentile(ln, 5))
    return dict(
        px=int(sel.sum()),
        lum_off_p5_p95=[float(np.percentile(lo, 5)), float(np.percentile(lo, 95))],
        lum_on_p5_p95=[float(np.percentile(ln, 5)), float(np.percentile(ln, 95))],
        spread_off=spread_off, spread_on=spread_on,
        spread_ratio=float(spread_on / spread_off) if spread_off > 0 else None,
        levels_off=int(len(np.unique(np.round(lo / quantum)))),
        levels_on=int(len(np.unique(np.round(ln / quantum)))),
    )


def verdict(rows, visible_share=READS_VISIBLE_SHARE, mean_de=READS_MEAN_DE):
    """Reads / reads-where-it-lands / below the bar, from the measured region rows.

    A technique that only touches part of the figure (a key light lights the faces the key
    can reach) is judged twice: the whole-figure bar above, and the same bar over the set
    it actually moved - reported with that set's share of the figure, so a tiny set cannot
    pass as a big one.
    """
    whole = rows["whole"]
    if whole.get("px", 0) == 0 or whole.get("changed", 0) == 0:
        return "no-op (byte-identical frames)"
    if whole["visible_share"] >= visible_share or whole["mean_de"] >= mean_de:
        return "reads"
    affected = rows.get("affected", {})
    share = affected.get("px", 0) / whole["px"]
    if (share >= 0.05 and affected.get("mean_de", 0) >= 2 * mean_de
            and affected.get("visible_share", 0) >= 0.5):
        return ("reads where it lands (%.1f%% of the figure, dE %.1f) but below the "
                "whole-figure bar" % (100 * share, affected["mean_de"]))
    return "below the bar"


def obvious(rows):
    whole = rows["whole"]
    if whole.get("changed", 0) == 0:
        return False
    return (whole["visible_share"] >= OBVIOUS_VISIBLE_SHARE
            or whole["mean_de"] >= OBVIOUS_MEAN_DE)


def box_metrics(off, on, box):
    """One rectangle of a frame, compared - for the fight scenes, where a figure mask is
    not available (a stage fills the frame). The box is drawn on the sheet and its numbers
    include whatever is behind the fighter, so it is a magnitude, not a share of a figure.
    """
    height, width = off.array.shape[:2]
    x0, y0, x1, y1 = (int(round(box[0] * width / 960)), int(round(box[1] * height / 540)),
                      int(round(box[2] * width / 960)), int(round(box[3] * height / 540)))
    sel = np.zeros((height, width), dtype=bool)
    sel[max(0, y0):min(height, y1), max(0, x0):min(width, x1)] = True
    delta = on.array - off.array
    return region_row(sel, off.array, on.array, delta, np.abs(delta).max(axis=2),
                      luminance(on.array) - luminance(off.array))


def metric_line(name, row):
    if not row.get("px"):
        return "%-10s (no pixels)" % name
    return ("%-10s px=%6d  visible=%5.1f%%  dL=%+6.2f  dE=%5.2f  L %6.2f -> %6.2f"
            % (name, row["px"], 100.0 * row["visible_share"], row["mean_dlum"],
               row["mean_de"], row["mean_lum_off"], row["mean_lum_on"]))


# ---------------------------------------------------------------------------------------
# Sheets.
# ---------------------------------------------------------------------------------------

INK = (22, 24, 32)
PANEL_BG = (16, 17, 22)
LABEL = (235, 236, 242)
DIM = (150, 154, 166)
ACCENT = (255, 214, 120)
REGION_COLOURS = {"face": (255, 96, 96), "hair": (120, 230, 120), "torso": (255, 220, 90)}
GAP = 10
CAPTION_H = 26


def panel(source, crop=None, zoom=1):
    image = source.image() if isinstance(source, Frame) else source
    if crop is not None:
        image = image.crop(crop)
    if zoom != 1:
        image = image.resize((image.width * zoom, image.height * zoom), Image.NEAREST)
    return image


def compose(title, subtitle, rows, out_path, footer=None):
    """rows: list of list of (image, label); caption above each panel, left aligned.

    A label may carry a second line after a newline (the measurement note), which is drawn
    dimmer under the panel's name - short panels cannot fit both on one line.
    """
    laid_out, sheet_h = [], 0
    for row in rows:
        row_w, row_h = 0, 0
        for image, label in row:
            lines = label.split("\n") if label else []
            cap = 0 if not lines else CAPTION_H + 20 * (len(lines) - 1)
            row_w += image.width + GAP
            row_h = max(row_h, image.height + cap)
        laid_out.append((row, row_w - GAP, row_h))
        sheet_h += row_h + GAP
    sheet_w = max([w for _, w, _ in laid_out] + [1000])
    head = 34 + 26 + (30 if footer else 0) + GAP
    canvas = Image.new("RGB", (sheet_w, sheet_h + head), INK)
    draw = ImageDraw.Draw(canvas)
    draw.text((GAP, 8), title, font=font(22), fill=LABEL)
    draw.text((GAP, 36), subtitle, font=font(17), fill=DIM)
    y = head
    for row, _, row_h in laid_out:
        x = 0
        for image, label in row:
            lines = label.split("\n") if label else []
            cap = 0 if not lines else CAPTION_H + 20 * (len(lines) - 1)
            for index, line in enumerate(lines):
                draw.text((x + 2, y + index * 20), line, font=font(17),
                          fill=ACCENT if index == 0 else DIM)
            canvas.paste(image, (x, y + cap))
            x += image.width + GAP
        y += row_h + GAP
    if footer:
        for index, line in enumerate(footer.split("\n")):
            draw.text((GAP, y - 6 + index * 20), line, font=font(16), fill=DIM)
    canvas.save(out_path, optimize=True)
    return out_path


def figure_crop(frame, pad_fraction=0.08):
    ys, xs = np.nonzero(frame.mask)
    if len(xs) == 0:
        return (0, 0, frame.width, frame.height)
    pad = int(round(pad_fraction * frame.height))
    return (max(0, int(xs.min()) - pad), max(0, int(ys.min()) - pad),
            min(frame.width, int(xs.max()) + 1 + pad), min(frame.height, int(ys.max()) + 1 + pad))


def region_crop(width, height, name):
    fx0, fy0, fx1, fy1 = REGIONS[name]
    return (int(round(fx0 * width)), int(round(fy0 * height)),
            int(round(fx1 * width)), int(round(fy1 * height)))


def difference_image(off, on, crop, shrink=1, gain=8):
    """|on-off| per pixel at a fixed gain (so panels compare) - a locator, not a claim.

    A fixed gain keeps the panels comparable between sheets: a no-op pair is black, and a
    strong technique saturates. The pair's own max channel delta is printed in the label.
    """
    a = np.asarray(off.image().crop(crop)).astype(np.int32)
    b = np.asarray(on.image().crop(crop)).astype(np.int32)
    delta = np.abs(a - b)
    image = Image.fromarray(np.clip(delta * gain, 0, 255).astype(np.uint8))
    if shrink != 1:
        image = image.resize((image.width // shrink, image.height // shrink), Image.LANCZOS)
    return image, int(delta.max()) if delta.size else 0


def regions_panel(frame, scale=2):
    """The figure with the metric regions drawn on it (what the numbers read)."""
    crop = figure_crop(frame)
    image = frame.image().crop(crop)
    arr = np.asarray(image).copy()
    mask = frame.mask[crop[1]:crop[3], crop[0]:crop[2]]
    rim = rim_band(mask, rim_radius(frame.height))
    arr[rim] = (0.45 * arr[rim] + 0.55 * np.array([255, 60, 60])).astype(np.uint8)
    image = Image.fromarray(arr)
    draw = ImageDraw.Draw(image)
    for name, (fx0, fy0, fx1, fy1) in REGIONS.items():
        box = (fx0 * REF_W - crop[0], fy0 * REF_H - crop[1],
               fx1 * REF_W - crop[0] - 1, fy1 * REF_H - crop[1] - 1)
        draw.rectangle(box, outline=REGION_COLOURS[name], width=2)
    if scale != 1:
        image = image.resize((image.width // scale, image.height // scale), Image.LANCZOS)
    return image


def technique_sheet(rig, technique, out_path):
    """The contact sheet of one technique: three resolutions, off/on, plus crops."""
    label, off_args, on_args = technique["label"], list(technique["off"]), list(technique["on"])
    rows, per_resolution = [], {}
    small_pair = []
    for size, width, height in RESOLUTIONS:
        off = rig.run("off_" + technique["id"], rig.close_scene(off_args), size)
        on = rig.run("on_" + technique["id"], rig.close_scene(on_args), size)
        per_resolution[size] = compare(off, on)
        crop = figure_crop(off)
        pair = [(panel(off, crop), "%s OFF  %s" % (size, " ".join(off_args) or "(no flag)")),
                (panel(on, crop), "%s ON   %s" % (size, " ".join(on_args)))]
        if size == "1920x1080":
            rows.append(pair)
        else:
            small_pair += pair
    rows.insert(0, small_pair)
    off_big = rig.run("off_" + technique["id"], rig.close_scene(off_args), "1920x1080")
    on_big = rig.run("on_" + technique["id"], rig.close_scene(on_args), "1920x1080")
    off_small = rig.run("off_" + technique["id"], rig.close_scene(off_args), "640x360")
    on_small = rig.run("on_" + technique["id"], rig.close_scene(on_args), "640x360")
    crop_row = []
    for name in ("face", "hair", "torso"):
        crop = region_crop(off_big.width, off_big.height, name)
        crop_row += [(panel(off_big, crop, 2), "%s x2 OFF" % name),
                     (panel(on_big, crop, 2), "%s x2 ON" % name)]
    rows.append(crop_row)
    crop = region_crop(off_small.width, off_small.height, "face")
    locator, max_delta = difference_image(off_big, on_big, figure_crop(off_big), 2)
    rows.append([(panel(off_small, crop, 4), "face x4 OFF (640x360)"),
                 (panel(on_small, crop, 4), "face x4 ON (640x360)"),
                 (regions_panel(off_big, 2), "metric regions"),
                 (locator, "difference x8 (max %d/255)" % max_delta)])
    comparison = per_resolution["1920x1080"]
    whole = comparison["regions"]["whole"]
    subtitle = ("%s | combo %s | bind pose, no stage, --camera=bounds | OFF sha256 %s | "
                "ON sha256 %s" % (technique["question"], COMBO,
                                  comparison["sha256_off"][:16], comparison["sha256_on"][:16]))
    footer = ("%s\nverdict at 1080p: %s   (figure %d px; visible %.1f%%, dL %+.2f, dE %.2f)"
              % (label, verdict(comparison["regions"]), whole["px"],
                 100.0 * whole["visible_share"], whole["mean_dlum"], whole["mean_de"]))
    compose(label, subtitle, rows, out_path, footer=footer)
    return dict(label=label, question=technique["question"], off=off_args, on=on_args,
                per_resolution=per_resolution, verdict=verdict(comparison["regions"]))


def sweep_sheet(rig, sweep, out_path):
    """One parameter swept to its extremes at 960x540 (acceptance item 3).

    The first step is the control. Every later step is measured against it, the steps the
    sweep's `claim` names are checked for a byte-identical frame (a claim that fails is a
    measurement), and the `pairs` the arm's own argument needs are compared directly.
    """
    frames, results, panels = [], [], []
    for index, (step_label, step_args) in enumerate(sweep["steps"]):
        frame = rig.run("sweep_%s_%s" % (sweep["id"], step_label.replace(" ", "_")),
                        rig.close_scene(step_args), "960x540")
        frames.append(frame)
        comparison = compare(frames[0], frame)
        whole = comparison["regions"]["whole"]
        results.append(dict(step=step_label, args=list(step_args),
                            identical=(index > 0 and comparison["identical"]),
                            obvious=obvious(comparison["regions"]) and index > 0,
                            regions=comparison["regions"], sha256=frame.digest))
        if index == 0:
            note = "reference"
        elif comparison["identical"]:
            note = "IDENTICAL"
        else:
            note = "vis %.1f%% dL %+.2f dE %.2f" % (100.0 * whole["visible_share"],
                                                    whole["mean_dlum"], whole["mean_de"])
            if obvious(comparison["regions"]):
                note = "OBVIOUS " + note
        panels.append((panel(frame, figure_crop(frames[0])),
                       "%s\n%s" % (step_label, note)))
    last = len(sweep["steps"]) - 1
    zoom_row = []
    for index, tag in ((0, "control"), (last, "last step")):
        for region in ("face", "torso"):
            crop = region_crop(frames[index].width, frames[index].height, region)
            zoom_row.append((panel(frames[index], crop, 2), "%s %s x2" % (tag, region)))
    rows = [panels, zoom_row]
    claim = sweep.get("claim")
    claim_steps = [results[i] for i in claim["indices"]] if claim else []
    if claim and claim.get("kind") == "identical":
        broken = [r for r in claim_steps if not r["identical"]]
    else:
        broken = [r for r in claim_steps if r["identical"]]
    statements = []
    if broken:
        statements.append("CLAIM FAILS - %s: %s"
                          % (", ".join(r["step"] for r in broken), claim["fails"]))
    elif claim_steps:
        statements.append("claim holds: %s" % claim["holds"])
    pairs = []
    for first, second, description in sweep.get("pairs", []):
        comparison = compare(frames[first], frames[second])
        whole = comparison["regions"]["whole"]
        pairs.append(dict(first=sweep["steps"][first][0], second=sweep["steps"][second][0],
                          description=description, identical=comparison["identical"],
                          regions=comparison["regions"]))
        pairs[-1] = dict(pairs[-1], label="%s: %s (visible %.1f%%, dE %.2f)"
                         % (description, "identical" if comparison["identical"] else "differs",
                            100.0 * whole["visible_share"], whole["mean_de"]))
    identical = [r for r in results[1:] if r["identical"]]
    if identical:
        statements.append("byte-identical to the control: "
                          + ", ".join(r["step"] for r in identical))
    compose(sweep["label"],
            "sweep at 960x540 | %s | expected: %s"
            % ("Rena 0, bind pose, no stage, --camera=bounds", sweep["expect"]),
            rows, out_path, footer="\n".join(statements + [p["label"] for p in pairs]))
    return dict(label=sweep["label"], expectation=sweep["expect"],
                verdict="; ".join(statements) or "no step differs from the control",
                steps=[dict(step=r["step"], args=r["args"], identical_to_first=r["identical"],
                            obvious=r["obvious"], sha256=r["sha256"], regions=r["regions"])
                       for r in results],
                pairs=pairs)


def gameplay_sheet(rig, technique, out_path):
    """One gameplay-distance frame of a kept technique (--versus, arena camera)."""
    base = ["--stage=%s/%s" % (rig.install, GAMEPLAY_STAGE_REL),
            "--character=%s/%s" % (rig.install, CHARACTER_REL),
            "--enemy=%s/%s" % (rig.install, GAMEPLAY_ENEMY_REL)] + list(GAMEPLAY_ARGS)
    off = rig.run("gp_off_" + technique["id"], base + list(technique["off"]), "960x540")
    on = rig.run("gp_on_" + technique["id"], base + list(technique["on"]), "960x540")
    comparison = compare(off, on)
    fighter = box_metrics(off, on, GAMEPLAY_BOX)
    box = (GAMEPLAY_BOX[0] - 30, GAMEPLAY_BOX[1] - 30,
           GAMEPLAY_BOX[2] + 20, GAMEPLAY_BOX[3] + 20)
    # The fight area at native scale and not the whole frame: the HUD is a fifth of the
    # frame and none of it is what a shading technique changes, while the pixels are what
    # the evidence set pays for. The full-frame recipe is in metrics.json either way.
    area = (int(0.20 * off.width), int(0.15 * off.height),
            int(1.00 * off.width), int(0.95 * off.height))
    rows = [[(panel(off, area), "OFF  %s (the fight area, native scale)"
              % (" ".join(technique["off"]) or "(no flag)")),
             (panel(on, area), "ON   %s" % " ".join(technique["on"]))],
            [(panel(off, box, 4), "OFF x4: the P2 box the numbers read"),
             (panel(on, box, 4), "ON x4: the same box")]]
    compose("gameplay distance - %s" % technique["label"],
            "stage01 (schoolyard_day) | Rena 0 vs Mion 0 | --versus --camera=arena, 300 "
            "frames, 960x540 | OFF sha256 %s | ON sha256 %s"
            % (comparison["sha256_off"][:16], comparison["sha256_on"][:16]),
            rows, out_path,
            footer="whole frame: %s\nP2 box %s: %s\nverdict: %s"
                   % (metric_line("whole", comparison["regions"]["whole"]), GAMEPLAY_BOX,
                      metric_line("box", fighter), verdict(comparison["regions"])))
    return dict(label=technique["label"], comparison=comparison, fighter_box=fighter,
                verdict=verdict(comparison["regions"]))


# Which arms the fight-scene reach check probes, in the form the #25 recommendation keeps
# them, and at which frames. Two frames, because one frame's pose can leave a
# condition-triggered arm (the three-band core fires only below N.L < 0.25) with nothing to
# do, which would read as "the arm is dead" when it is only idle. An arm that renders
# identically to its control at BOTH frames is not reaching the fight's draws.
REACH_FRAMES = (150, 300)
REACH_ARMS = [
    ("E secondary normals", ["--npr=normals"], []),
    ("C shadow tint", ["--npr=bands:soft,shadow"], ["--npr=bands:soft,shadow:none"]),
    ("B soft bands, neutral tint", ["--npr=bands:soft,shadow:none"], []),
    ("B three bands, neutral tint", ["--npr=bands:three,shadow:none"], []),
    ("D key:cam", ["--npr=bands:soft,shadow,key:cam"], ["--npr=bands:soft,shadow"]),
    ("F mask 1, neutral tint", ["--npr=bands:hard,shadow:none,mask:1"],
     ["--npr=bands:hard,shadow:none,mask:0"]),
    ("G specular", ["--npr=spec"], []),
    ("H rim", ["--npr=rim"], []),
    ("I outline x2", ["--toon", "--npr=outline:2"], ["--toon"]),
]


def slug(args):
    """A stable file/log stem for an argv list, so captures are shared when args repeat."""
    text = "_".join(args) or "none"
    return "".join(c if c.isalnum() else "-" for c in text).strip("-")[:60]


def reach_sheet(rig, out_path):
    """Which arms reach a real fight scene at all (--versus, stage01, arena camera).

    The close-up sheets measure a stage-less bind pose: an arm that is inert there and an
    arm that is inert in a fight are different defects, and this is the check that tells
    them apart. A row that is byte-identical to its control at every probed frame does not
    reach the product's draws.
    """
    results = []
    rows = []
    lines = ["arm | frames %s | result"
             % "/".join(str(f) for f in REACH_FRAMES)]
    for label, on_args, off_args in REACH_ARMS:
        per_frame, dead = {}, True
        for frames in REACH_FRAMES:
            base = ["--stage=%s/%s" % (rig.install, GAMEPLAY_STAGE_REL),
                    "--character=%s/%s" % (rig.install, CHARACTER_REL),
                    "--enemy=%s/%s" % (rig.install, GAMEPLAY_ENEMY_REL),
                    "--versus", "--camera=arena", "--frames=%d" % frames, "--size=960x540"]
            off = rig.run("reach_off_%d_%s" % (frames, slug(off_args)), base + off_args,
                          "960x540")
            on = rig.run("reach_on_%d_%s" % (frames, slug(on_args)), base + on_args,
                         "960x540")
            comparison = compare(off, on)
            per_frame[frames] = dict(identical=comparison["identical"],
                                     changed=comparison["regions"]["whole"]["changed"],
                                     visible=comparison["regions"]["whole"]["visible"],
                                     sha256_off=comparison["sha256_off"],
                                     sha256_on=comparison["sha256_on"])
            dead = dead and comparison["identical"]
        results.append(dict(label=label, on=on_args, off=off_args, per_frame=per_frame,
                            dead=dead))
        lines.append("%s | %s | %s"
                     % (label, " | ".join(
                         "IDENTICAL" if per_frame[f]["identical"]
                         else "%d px changed" % per_frame[f]["changed"]
                         for f in REACH_FRAMES),
                        "NOT REACHED" if dead else "reaches"))
    table = Image.new("RGB", (1400, 26 * len(lines) + 12), PANEL_BG)
    draw = ImageDraw.Draw(table)
    for index, line in enumerate(lines):
        draw.text((10, 7 + index * 26), line, font=font(18),
                  fill=ACCENT if "NOT REACHED" in line else LABEL)
    rows.append([(table, None)])
    # The visual: the one fully visible fighter (Mion), magnified, with the box the numbers
    # use drawn on it, for the dead arm and for one that reaches.
    focus = rig.run("reach_off_300_%s" % slug([]),
                    ["--stage=%s/%s" % (rig.install, GAMEPLAY_STAGE_REL),
                     "--character=%s/%s" % (rig.install, CHARACTER_REL),
                     "--enemy=%s/%s" % (rig.install, GAMEPLAY_ENEMY_REL),
                     "--versus", "--camera=arena", "--frames=300", "--size=960x540"],
                    "960x540")
    box = (GAMEPLAY_BOX[0] - 30, GAMEPLAY_BOX[1] - 30, GAMEPLAY_BOX[2] + 20, GAMEPLAY_BOX[3] + 20)
    def focus_frame(horizon_args):
        return rig.run("reach_on_%d_%s" % (horizon_args[0], slug(horizon_args[1])),
                       ["--stage=%s/%s" % (rig.install, GAMEPLAY_STAGE_REL),
                        "--character=%s/%s" % (rig.install, CHARACTER_REL),
                        "--enemy=%s/%s" % (rig.install, GAMEPLAY_ENEMY_REL),
                        "--versus", "--camera=arena", "--frames=%d" % horizon_args[0],
                        "--size=960x540"] + horizon_args[1], "960x540")

    visual = [(panel(focus, box, 4), "P2 x4, the measured box"),
              (panel(focus_frame((300, ["--npr=normals"])), box, 4),
               "P2 x4, E on: identical"),
              (panel(focus_frame((300, ["--npr=rim"])), box, 4),
               "P2 x4, H (rim) on: differs")]
    rows.append(visual)
    compose("reach into a fight scene (--versus, stage01, 960x540)",
            "the same arms as the close-up sheets, measured where the product draws them: "
            "a stage first, then the fighters. NOT REACHED is an arm the fight never sees.",
            rows, out_path)
    return dict(arms=results, frames=list(REACH_FRAMES),
                dead=[r["label"] for r in results if r["dead"]])


def fourview_sheet(rig, out_path):
    """The 4-view 2v2 frame: off/on, every cell magnified, plus the repeat-run hash."""
    off = rig.run("four_off", list(FOUR_ARGS) + ["--npr=off"], "960x540")
    on = rig.run("four_on", list(FOUR_ARGS) + ["--npr=on"], "960x540")
    repeat = rig.run("four_off_repeat", list(FOUR_ARGS) + ["--npr=off"], "960x540")
    comparison = compare(off, on)
    cw, ch = off.width // 2, off.height // 2
    cells = []
    for index, (ox, oy) in enumerate(((0, 0), (cw, 0), (0, ch), (cw, ch))):
        box = (ox, oy, ox + cw, oy + ch)
        cells += [(panel(off, box, 2), "cell %d OFF x2" % index),
                  (panel(on, box, 2), "cell %d ON x2" % index)]
    rows = [[(off.image(), "OFF  --npr=off (the 4-view frame)"),
             (on.image(), "ON   --npr=on")],
            cells[:4], cells[4:]]
    compose("4-view 2v2 (--screen=battle --local-players=4)",
            "front-end roster on stage03 (Rena 0, Mion 0, Mion 0, Rika 0), 300 frames, "
            "960x540 | OFF sha256 %s | ON sha256 %s | repeat OFF sha256 %s"
            % (comparison["sha256_off"][:16], comparison["sha256_on"][:16],
               repeat.digest[:16]),
            rows, out_path,
            footer="frame-wide: %s\ndeterministic on a repeat run: %s"
                   % (metric_line("whole", comparison["regions"]["whole"]),
                      "yes" if off.digest == repeat.digest else "NO - do not quote this "
                      "frame as evidence"))
    return dict(comparison=comparison, repeat_sha256=repeat.digest,
                deterministic=off.digest == repeat.digest)


def howto_sheet(control, out_path):
    """The scene, the regions and the metric definitions on one sheet."""
    rows = [[(panel(control, figure_crop(control)), "the close-up scene: %s, bind pose, no "
              "stage, --camera=bounds, %dx%d" % (COMBO, control.width, control.height)),
             (regions_panel(control, 1), "the metric regions (rim red / face / hair / torso)"),
             (panel(control, region_crop(control.width, control.height, "face"), 3),
              "face x3")]]
    lines = [
        "regions   rim = figure pixels within %d px of the silhouette at this size (the "
        "band scales with the frame;" % rim_radius(control.height),
        "          the recovered toon hull is ~2 px here); face / hair / torso = the boxes "
        "drawn above; background = every pixel that is not geometry.",
        "columns   px = pixels in the region; visible = share moving by >= %d/255 in a "
        "channel; dL = mean luminance change (on - off);" % VISIBLE_CHANNEL_DELTA,
        "          dE = mean RGB distance; L off -> L on. `affected` (metrics.md) is the "
        "set the arm moved, with its share of the figure.",
        "verdicts  READS at %.0f%% visible or dE %.1f over the whole figure; OBVIOUS at an "
        "arm's extremes at %.0f%% / dE %.1f."
        % (100 * READS_VISIBLE_SHARE, READS_MEAN_DE, 100 * OBVIOUS_VISIBLE_SHARE,
           OBVIOUS_MEAN_DE),
        "          Both are a PORT-SIDE evidence rule for this report, not a renderer "
        "constant; every raw number is printed so another bar can be applied.",
        "offsets   the difference x4 panel is a locator for where a pair differs, not "
        "evidence that the difference reads - the native and zoomed panels are that.",
    ]
    strip = Image.new("RGB", (max(sum(p.width for p, _ in rows[0]) + 2 * GAP, 1600),
                              24 * len(lines) + 14), PANEL_BG)
    draw = ImageDraw.Draw(strip)
    for index, line in enumerate(lines):
        draw.text((10, 7 + index * 24), line, font=font(17), fill=LABEL)
    rows.append([(strip, None)])
    compose("how to read these sheets (issue #27 evidence)",
            "every frame is the committed demo, headless: foundation_demo --headless "
            "--install=<game> --character=<game>/data/rena:0 --weapon=<game>/data/item/01.x "
            "--no-anim --camera=bounds --frames=3 --size=<WxH> --out=<file.ppm>",
            rows, out_path)
    return out_path


# ---------------------------------------------------------------------------------------
# Report.
# ---------------------------------------------------------------------------------------

def summarise(report):
    """The human-readable metrics.md: one block per technique and sweep."""
    out = []
    out.append("# NPR evidence, issue #27 - measured\n")
    out.append("Generated %s by `remake/foundation/tests/npr_evidence.py`. Every number "
               "below is a measurement of a committed-demo capture; the recipes are in "
               "`metrics.json` (`commands`) and beside each capture under `logs/`.\n"
               % report["generated"])
    out.append("Scene: **%s** - 竜宮レナ with 愛用の鉈 (`data/rena/00.x` + "
               "`data/item/01.x`) - bind pose, no stage, `--camera=bounds`."
               % report["combo"])
    out.append("Thresholds (a port-side evidence rule, not a renderer constant): READS at "
               "%.0f%% visible or dE %.1f; OBVIOUS at %.0f%% / dE %.1f.\n"
               % (100 * report["thresholds"]["reads_visible_share"],
                  report["thresholds"]["reads_mean_de"],
                  100 * report["thresholds"]["obvious_visible_share"],
                  report["thresholds"]["obvious_mean_de"]))
    determinism = report.get("determinism", {})
    out.append("Renderer determinism (the control frame captured twice at 1920x1080): "
               "sha256 %s, %s.\n"
               % (determinism.get("sha256", "?")[:16],
                  "identical" if determinism.get("reproducible") else "DIFFERENT"))
    out.append("## Techniques (close-up, 1920x1080 unless stated)\n")
    for key, data in sorted(report["techniques"].items()):
        comparison = data["per_resolution"]["1920x1080"]
        out.append("### %s\n" % data["label"])
        out.append("OFF `%s`  ON `%s`\n" % (" ".join(data["off"]) or "(no flag)",
                                            " ".join(data["on"])))
        out.append("verdict: **%s**\n" % data["verdict"])
        out.append("| region | px | visible | dL | dE | L off | L on |")
        out.append("|---|---|---|---|---|---|---|")
        for name in ("whole", "rim", "interior", "face", "hair", "torso", "affected",
                     "background"):
            row = comparison["regions"].get(name, {})
            if not row.get("px"):
                continue
            out.append("| %s | %d | %.1f%% | %+.2f | %.2f | %.2f | %.2f |"
                       % (name, row["px"], 100 * row["visible_share"], row["mean_dlum"],
                          row["mean_de"], row["mean_lum_off"], row["mean_lum_on"]))
        for size in sorted(data["per_resolution"]):
            row = data["per_resolution"][size]["regions"]["whole"]
            out.append("\n%s: figure %d px, visible %.1f%%, dL %+.2f, dE %.2f%s"
                       % (size, row.get("px", 0), 100 * row.get("visible_share", 0),
                          row.get("mean_dlum", 0), row.get("mean_de", 0),
                          " (byte-identical)" if data["per_resolution"][size]["identical"]
                          else ""))
        out.append("")
    out.append("## Sanity sweeps (960x540, the arm's own parameter at its extremes)\n")
    for key, data in sorted(report["sweeps"].items()):
        out.append("### %s\n" % data["label"])
        out.append("expected: %s\n" % data["expectation"])
        out.append("**%s**\n" % data["verdict"])
        out.append("| step | args | vs the control | visible | dL | dE |")
        out.append("|---|---|---|---|---|---|")
        for step in data["steps"]:
            row = step["regions"]["whole"]
            out.append("| %s | `%s` | %s | %.1f%% | %+.2f | %.2f |"
                       % (step["step"], " ".join(step["args"]) or "(no flag)",
                          "identical" if step["identical_to_first"]
                          else ("obvious" if step["obvious"] else "changed"),
                          100 * row.get("visible_share", 0), row.get("mean_dlum", 0),
                          row.get("mean_de", 0)))
        out.append("")
        for pair in data.get("pairs", []):
            row = pair["regions"]["whole"]
            out.append("- %s: %s, visible %.1f%%, dL %+.2f, dE %.2f"
                       % (pair["description"],
                          "byte-identical" if pair["identical"] else "differs",
                          100 * row.get("visible_share", 0), row.get("mean_dlum", 0),
                          row.get("mean_de", 0)))
        out.append("")
    if report.get("flatness"):
        out.append("## Is the tinted shadow one flat value? (the B band claim)\n")
        out.append("The set is the pixels the tint moved inside a patch of one flat "
                   "material (the skirt, %s at 1080p), so the spread is the lighting's "
                   "spread and not the albedo's. A band that replaces the shadowed side "
                   "with one value collapses it; a tint that multiplies an unbanded "
                   "gradient keeps it.\n" % (report["scene"]["skirt_patch"],))
        out.append("| arm | shadow px | spread off | spread on | ratio | levels off -> on |")
        out.append("|---|---|---|---|---|---|")
        for tag, data in sorted(report["flatness"].items()):
            if not data.get("px"):
                continue
            out.append("| %s | %d | %.2f | %.2f | %.3f | %d -> %d |"
                       % (tag, data["px"], data["spread_off"], data["spread_on"],
                          data["spread_ratio"], data["levels_off"], data["levels_on"]))
        out.append("")
    if report.get("gameplay"):
        out.append("## Gameplay distance (--versus, stage01, arena camera, 960x540)\n")
        out.append("The `whole` row is the whole FRAME (a stage fills it, so there is no "
                   "figure mask); the `P2 box` row is the rectangle around Mion, the one "
                   "fully visible fighter, drawn on each sheet.\n")
        for key, data in sorted(report["gameplay"].items()):
            row = data["comparison"]["regions"]["whole"]
            fighter = data.get("fighter_box", {})
            out.append("- %s: %s - whole frame visible %.2f%%, dL %+.3f, dE %.2f; "
                       "P2 box visible %.1f%%, dL %+.2f, dE %.2f"
                       % (key, data["verdict"], 100 * row.get("visible_share", 0),
                          row.get("mean_dlum", 0), row.get("mean_de", 0),
                          100 * fighter.get("visible_share", 0), fighter.get("mean_dlum", 0),
                          fighter.get("mean_de", 0)))
        out.append("")
    if report.get("reach"):
        out.append("## Does the arm reach a fight scene at all? (--versus, stage01)\n")
        out.append("The close-up sheets are a stage-less bind pose. These rows are the "
                   "same arms where the product draws them - a stage first, then the "
                   "fighters - so an arm that is byte-identical to its control at every "
                   "probed frame is one the fight never sees.\n")
        out.append("| arm | on | %s |"
                   % " | ".join("frame %d" % f for f in report["reach"]["frames"]))
        out.append("|---|%s|" % ("---|" * len(report["reach"]["frames"])))
        for arm in report["reach"]["arms"]:
            cells = []
            for frames in report["reach"]["frames"]:
                data = arm["per_frame"][str(frames)] if str(frames) in arm["per_frame"] \
                    else arm["per_frame"][frames]
                cells.append("**IDENTICAL**" if data["identical"]
                             else "%d px changed" % data["changed"])
            out.append("| %s | `%s` | %s |" % (arm["label"], " ".join(arm["on"]),
                                               " | ".join(cells)))
        out.append("")
    if report.get("fourview"):
        comparison = report["fourview"]["comparison"]
        row = comparison["regions"]["whole"]
        out.append("## 4-view 2v2\n")
        out.append("- frame-wide: visible %.1f%%, dL %+.2f, dE %.2f; byte-identical on a "
                   "repeat run: %s\n" % (100 * row.get("visible_share", 0),
                                         row.get("mean_dlum", 0), row.get("mean_de", 0),
                                         "yes" if report["fourview"]["deterministic"] else "NO"))
    return "\n".join(out) + "\n"


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("--demo", required=True)
    parser.add_argument("--install", required=True)
    parser.add_argument("--outdir", default="remake/tests/npr-evidence/issue-27")
    parser.add_argument("--workdir", default="/tmp/npr-evidence-work")
    parser.add_argument("--only", default="", help="comma-separated technique/sweep ids")
    parser.add_argument("--quick", action="store_true",
                        help="close-up sheets only (no gameplay and no 4-view)")
    args = parser.parse_args()

    if not os.path.isdir(os.path.join(args.install, "data")):
        print("npr_evidence: no game data at %s" % args.install, file=sys.stderr)
        return 2
    only = set(part.strip() for part in args.only.split(",") if part.strip())
    captures = os.path.join(args.outdir, "captures")
    logs = os.path.join(args.outdir, "logs")
    os.makedirs(captures, exist_ok=True)
    started = time.time()
    rig = Rig(args.demo, args.install, args.workdir, logs)

    report = dict(generated=time.strftime("%Y-%m-%d %H:%M:%S"), combo=COMBO,
                  scene=dict(close=" ".join(CLOSE_ARGS), gameplay=" ".join(GAMEPLAY_ARGS),
                             four=" ".join(FOUR_ARGS), character=CHARACTER_REL,
                             weapon=WEAPON_REL, regions=REGION_BOXES_1080P,
                             skirt_patch=SKIRT_PATCH_1080P,
                             rim_radius={"%dx%d" % (w, h): rim_radius(h)
                                         for _, w, h in RESOLUTIONS}),
                  thresholds=dict(reads_visible_share=READS_VISIBLE_SHARE,
                                  reads_mean_de=READS_MEAN_DE,
                                  obvious_visible_share=OBVIOUS_VISIBLE_SHARE,
                                  obvious_mean_de=OBVIOUS_MEAN_DE,
                                  visible_channel_delta=VISIBLE_CHANNEL_DELTA),
                  techniques={}, sweeps={}, gameplay={}, fourview=None, flatness={})
    # An incremental run (--only) must not throw away the sections it did not render: the
    # report on disk is merged, so a re-run of one sheet keeps every other sheet's numbers.
    metrics_path = os.path.join(args.outdir, "metrics.json")
    if os.path.exists(metrics_path):
        with open(metrics_path) as handle:
            previous = json.load(handle)
        for key in ("techniques", "sweeps", "gameplay", "flatness", "commands"):
            merged = previous.get(key) or {}
            merged.update(report.get(key) or {})
            report[key] = merged
        for key in ("fourview", "reach", "determinism"):
            report[key] = report.get(key) or previous.get(key)

    control = rig.run("off_B", rig.close_scene([]), "1920x1080")
    repeat = rig.run("off_B_repeat", rig.close_scene([]), "1920x1080")
    report["determinism"] = dict(sha256=control.digest, sha256_repeat=repeat.digest,
                                 reproducible=control.digest == repeat.digest)
    howto_sheet(control, os.path.join(captures, "HOWTO-scene-and-regions.png"))

    for technique in TECHNIQUES:
        if only and technique["id"] not in only:
            continue
        out = os.path.join(captures, "close-%s.png" % technique["id"])
        report["techniques"][technique["id"]] = technique_sheet(rig, technique, out)
        print("sheet %s" % out)

    for sweep in SWEEPS:
        if only and sweep["id"] not in only:
            continue
        out = os.path.join(captures, "sanity-%s.png" % sweep["id"])
        report["sweeps"][sweep["id"]] = sweep_sheet(rig, sweep, out)
        print("sheet %s" % out)

    # The band claim, measured on one flat material: is the tinted shadow ONE value?
    if not only or "B" in only or "flatness" in only:
        neutral = rig.run("off_B", rig.close_scene([]), "1920x1080")
        for tag, band_flags in (("hard, default tint", ("--npr=bands:hard,shadow",)),
                                ("soft 0.06, default tint", ("--npr=bands:soft,shadow",)),
                                ("soft 1.00, default tint",
                                 ("--npr=bands:soft,soft:1.0,shadow",)),
                                ("three, default tint", ("--npr=bands:three,shadow",))):
            frame = rig.run("flat_" + tag.replace(" ", "_").replace(",", ""),
                            rig.close_scene(band_flags), "1920x1080")
            report["flatness"][tag] = shadow_flatness(neutral, frame)

    if not args.quick:
        wanted = only.intersection({"gameplay", "fourview"})
        for technique in TECHNIQUES:
            if technique["id"] not in GAMEPLAY_FOR:
                continue
            if only and technique["id"] not in only and not wanted:
                continue
            out = os.path.join(captures, "gameplay-%s.png" % technique["id"])
            report["gameplay"][technique["id"]] = gameplay_sheet(rig, technique, out)
            print("sheet %s" % out)
        if not only or "fourview" in only:
            out = os.path.join(captures, "fourview-2v2.png")
            report["fourview"] = fourview_sheet(rig, out)
            print("sheet %s" % out)
        if not only or "reach" in only:
            out = os.path.join(captures, "reach-versus.png")
            report["reach"] = reach_sheet(rig, out)
            print("sheet %s" % out)

    # Merged, not assigned: an --only run must keep the recipes of the sheets it did not
    # render, the same way the sections above do.
    commands = report.get("commands") or {}
    commands.update(rig.commands)
    report["commands"] = commands
    report["elapsed_s"] = round(time.time() - started, 1)
    with open(os.path.join(args.outdir, "metrics.json"), "w") as handle:
        json.dump(report, handle, indent=1, sort_keys=True)
    with open(os.path.join(args.outdir, "metrics.md"), "w") as handle:
        handle.write(summarise(report))
    print("wrote %s and metrics.md (%.1f s)" % (os.path.join(args.outdir, "metrics.json"),
                                                report["elapsed_s"]))
    return 0


if __name__ == "__main__":
    sys.exit(main())
