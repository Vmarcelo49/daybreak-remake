"""Numeric profile of every take: is it airborne, is it lying down, does it loop.

    blender -b --factory-startup -P measure_takes.py -- --rig <gmo> --out <tsv> [--step 1]

Samples the posed rig frame by frame (no rendering) and writes one row per take:

  frames        length in frames
  root_y/z      the `root` bone's position at the first / last frame, file units
  net_dx/dy/dz  last minus first
  y_min y_max   the root's vertical range
  foot_min      lowest of the two foot bones over the take (0 = on the ground)
  foot_max      highest foot bone (a jump lifts both feet)
  air_frames    frames where BOTH feet are above `--air` units (25 default)
  head_min/max  head bone height
  pitch0/pitch1/pitchmin/pitchmax   torso pitch: angle of (neck - root) from vertical,
                degrees, 0 = upright, 90 = horizontal, >90 = upside down
  loops         first frame's pose equals the last frame's pose (root within 1 unit and
                every sampled bone rotation within 1 degree)
"""
import argparse
import math
import sys

import bpy
from mathutils import Vector

sys.path.insert(0, "/home/marcelo/Projects/daybreak-remake/tools/asset-tools")
import gmo_blender as G  # noqa: E402


def pitch_of(armature):
    root = armature.pose.bones["root"].matrix.translation
    neck = armature.pose.bones["neck"].matrix.translation
    up = Vector((0.0, 1.0, 0.0))          # file +Y is up
    d = (neck - root)
    if d.length < 1e-6:
        return 0.0
    return math.degrees(math.acos(max(-1.0, min(1.0, d.normalized().dot(up)))))


def pose_vector(armature, names):
    out = []
    for name in names:
        bone = armature.pose.bones[name]
        m = bone.matrix
        out.extend([m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2],
                    m[2][0], m[2][1], m[2][2], m[3][0], m[3][1], m[3][2]])
    return out


def main():
    argv = sys.argv[sys.argv.index("--") + 1:]
    ap = argparse.ArgumentParser()
    ap.add_argument("--rig", required=True)
    ap.add_argument("--mesh", required=True, help="the mesh GMO: the bind pose lives there")
    ap.add_argument("--out", required=True)
    ap.add_argument("--step", type=int, default=1)
    ap.add_argument("--air", type=float, default=25.0)
    a = ap.parse_args(argv)

    rig = G.parse_gmo(open(a.rig, "rb").read())
    # The bind pose and the bone axes come from the mesh file, as in render_takes.py.
    rest = G.Rest(G.parse_gmo(open(a.mesh, "rb").read()))
    scene = bpy.context.scene
    for obj in list(bpy.data.objects):
        bpy.data.objects.remove(obj)
    scene.render.fps = 30
    armature, names = G.build_armature(rig, rest, scene.collection)
    armature.animation_data_create()
    bones = [b.name for b in rig.bones]
    watch = [n for n in ("root", "neck", "head", "leftfoot", "rightfoot", "lefttoe1", "righttoe1",
                         "lefthand", "righthand") if n in armature.pose.bones]
    header = ("take_index\ttake_name\tframes\troot_z0\troot_y0\troot_z1\troot_y1\t"
              "net_dx\tnet_dy\tnet_dz\ty_min\ty_max\tx_min\tx_max\tz_min\tz_max\t"
              "foot_min\tfoot_max\tair_frames\t"
              "head_min\thead_max\tpitch0\tpitch1\tpitch_min\tpitch_max\t"
              "reach_fwd\thand_speed\tfoot_speed\tloops")
    rows = []
    for index, motion in enumerate(rig.motions):
        if not motion.bindings:
            continue
        action, slot, _ = G.build_action(motion, rig, rest, armature, names)
        armature.animation_data.action = action
        armature.animation_data.action_slot = slot
        start, end = int(motion.range[0]), int(motion.range[1])
        samples = []
        for frame in range(start, end + 1, a.step):
            scene.frame_set(frame)
            root = armature.pose.bones["root"].matrix.translation.copy()
            feet = [armature.pose.bones[n].matrix.translation.y for n in
                    ("leftfoot", "rightfoot") if n in armature.pose.bones]
            head = armature.pose.bones["head"].matrix.translation.y
            hands = [armature.pose.bones[n].matrix.translation.copy() for n in
                     ("lefthand", "righthand") if n in armature.pose.bones]
            neck = armature.pose.bones["neck"].matrix.translation.copy()
            samples.append({"f": frame, "root": root, "feet": feet, "head": head,
                            "pitch": pitch_of(armature), "hands": hands, "neck": neck})
        scene.frame_set(start)
        first = pose_vector(armature, watch)
        scene.frame_set(end)
        last = pose_vector(armature, watch)
        loops = 1 if max(abs(x - y) for x, y in zip(first, last)) < 0.02 else 0
        air = 0
        for s in samples:
            if s["feet"] and min(s["feet"]) > a.air:
                air += 1
        # Arm behaviour: `reach_fwd` is how far forward of the root a hand gets (a thrust or
        # a swing reaches well forward); `hand_speed` is the fastest one-frame hand travel,
        # in file units per frame, which separates a strike from a held guard or a sway.
        reach_fwd, hand_speed, foot_speed = 0.0, 0.0, 0.0
        for s in samples:
            for hand in s["hands"]:
                reach_fwd = max(reach_fwd, hand.z - s["root"].z)
        for prev, cur in zip(samples, samples[1:]):
            for a_hand, b_hand in zip(prev["hands"], cur["hands"]):
                hand_speed = max(hand_speed, (b_hand - a_hand).length)
            for a_foot, b_foot in zip(prev["feet"], cur["feet"]):
                foot_speed = max(foot_speed, abs(b_foot - a_foot))
        s0, s1 = samples[0], samples[-1]
        rows.append((index, motion.name, end - start + 1,
                     s0["root"].z, s0["root"].y, s1["root"].z, s1["root"].y,
                     s1["root"].x - s0["root"].x, s1["root"].y - s0["root"].y,
                     s1["root"].z - s0["root"].z,
                     min(s["root"].y for s in samples), max(s["root"].y for s in samples),
                     min(s["root"].x for s in samples), max(s["root"].x for s in samples),
                     min(s["root"].z for s in samples), max(s["root"].z for s in samples),
                     min(min(s["feet"]) for s in samples if s["feet"]),
                     max(max(s["feet"]) for s in samples if s["feet"]),
                     air,
                     min(s["head"] for s in samples), max(s["head"] for s in samples),
                     s0["pitch"], s1["pitch"],
                     min(s["pitch"] for s in samples), max(s["pitch"] for s in samples),
                     reach_fwd, hand_speed, foot_speed, loops))
        armature.animation_data.action = None
        print(f"take {index:2d} {motion.name:16s} air {air:3d} "
              f"foot {rows[-1][16]:6.1f}..{rows[-1][17]:6.1f} "
              f"pitch0/1 {rows[-1][21]:4.0f}/{rows[-1][22]:4.0f} loops {loops}")

    with open(a.out, "w") as f:
        f.write(header + "\n")
        for r in rows:
            f.write(("%d\t%s\t%d\t" + "%.2f\t" * 15 + "%d\t" + "%.2f\t" * 2 +
                     "%.1f\t" * 5 + "%.2f\t" * 2 + "%d\n") % r)
    print("wrote", a.out)


if __name__ == "__main__":
    main()
