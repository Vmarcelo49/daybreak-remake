#!/usr/bin/env python3
"""
Bind a PC fighter's body to a PSP skeleton, so PSP motions play on it with no bake.

    blender --background --factory-startup --python psp_fit_body.py -- \
        --x2blend <X2Blend checkout> --x keiichi/00.X --rig chrm19.gmo --mesh chr190.gmo --out body.blend

The fit has two stages, and keeps the PC mesh in its own pose:
  1. Lengths. Each limb segment is scaled along itself to the PSP bone's length. Only the mesh changes.
  2. Pose. The PC rests with its arms at 45 degrees and the PSP in a T. A rigid T_i takes each PC segment
     onto its PSP bone. The bone's Blender rest becomes T_i⁻¹ · bind_i, so that when a motion puts the
     skeleton in its PSP rest, the skin matrix is exactly T_i. The PC weights keep working, with no
     destructive repose of the shoulders.

Weights map one to one, except the PC's single spine, which is split over root, spine1 and spine2 by
height. The feet stay flat on the floor in rest, because the PSP ankle sits lower than the PC's.
"""
import argparse
import importlib.util
import os
import sys

import bpy
from mathutils import Matrix, Vector

spec = importlib.util.spec_from_file_location(
    "gmo_blender", os.path.join(os.path.dirname(os.path.abspath(__file__)), "gmo_blender.py"))
gmo = importlib.util.module_from_spec(spec)
spec.loader.exec_module(gmo)


def segments(side_pc, side_psp):
    """(PC bone, PC child, PSP bone, PSP child): one arm or leg."""
    return [
        (f"Bip00_{side_pc}_Thigh", f"Bip00_{side_pc}_Calf", f"{side_psp}hip", f"{side_psp}knee"),
        (f"Bip00_{side_pc}_Calf", f"Bip00_{side_pc}_Foot", f"{side_psp}knee", f"{side_psp}foot"),
        (f"Bip01_{side_pc}_Clavicle", f"Bip01_{side_pc}_UpperArm", f"{side_psp}collar", f"{side_psp}shoulder"),
        (f"Bip01_{side_pc}_UpperArm", f"Bip01_{side_pc}_Forearm", f"{side_psp}shoulder", f"{side_psp}elbow"),
        (f"Bip01_{side_pc}_Forearm", f"Bip01_{side_pc}_Hand", f"{side_psp}elbow", f"{side_psp}hand"),
        (f"Bip01_{side_pc}_Hand", f"Bip01_{side_pc}_Finger0", f"{side_psp}hand", f"{side_psp}finger1"),
    ]


SEGMENTS = [
    ("Bip01_Spine", "Bip01_Neck", "root", "neck"),
    ("Bip01_Neck", "Bip01_Head", "neck", "head"),
] + segments("L", "left") + segments("R", "right")

GROUP_MAP = {
    "Bip00_Pelvis": "root", "Bip01_Neck": "neck", "Bip01_Head": "head",
}
for side_pc, side_psp in (("L", "left"), ("R", "right")):
    GROUP_MAP.update({
        f"Bip00_{side_pc}_Thigh": f"{side_psp}hip", f"Bip00_{side_pc}_Calf": f"{side_psp}knee",
        f"Bip00_{side_pc}_Foot": f"{side_psp}foot", f"Bip00_{side_pc}_Toe0": f"{side_psp}toe1",
        f"Bip01_{side_pc}_Clavicle": f"{side_psp}collar", f"Bip01_{side_pc}_UpperArm": f"{side_psp}shoulder",
        f"Bip01_{side_pc}_Forearm": f"{side_psp}elbow", f"Bip01_{side_pc}_Hand": f"{side_psp}hand",
        f"Bip01_{side_pc}_Finger0": f"{side_psp}finger1",
    })


def to_y_up(v):
    return Vector((v[0], v[2], -v[1]))


def along(direction, scale):
    """Scale by `scale` along the unit `direction`, and leave the cross-section alone."""
    d = direction
    m = Matrix.Identity(4)
    for r in range(3):
        for c in range(3):
            m[r][c] += (scale - 1.0) * d[r] * d[c]
    return m


class Fit:
    def __init__(self, pc_joints, parents, rest):
        heads = {b.name: rest.bind[i].translation.copy() for i, b in enumerate(rest.bones)}
        self.J = pc_joints
        self.new = dict(pc_joints)
        self.stage1 = {}
        self.pose = {}
        by_pc = {s[0]: s for s in SEGMENTS}
        order = []

        def visit(name):
            if name in order or name not in pc_joints:
                return
            if parents.get(name):
                visit(parents[name])
            order.append(name)

        for name in pc_joints:
            visit(name)
        for name in order:
            parent = parents.get(name)
            shift = self.new[parent] - pc_joints[parent] if parent in self.new and parent else Vector((0, 0, 0))
            # A chain moves as far as its parent's end moved. stage1 of the parent has placed this joint.
            if parent in self.stage1:
                self.new[name] = self.stage1[parent] @ pc_joints[name]
            else:
                self.new[name] = pc_joints[name] + shift
            segment = by_pc.get(name)
            at, now = pc_joints[name], self.new[name]
            if segment:
                child, psp, psp_child = segment[1:]
                d = (pc_joints[child] - at)
                scale = (heads[psp_child] - heads[psp]).length / d.length
                self.stage1[name] = Matrix.Translation(now) @ along(d.normalized(), scale) @ Matrix.Translation(-at)
                rotation = d.normalized().rotation_difference((heads[psp_child] - heads[psp]).normalized())
                self.pose[psp] = (Matrix.Translation(heads[psp]) @ rotation.to_matrix().to_4x4()
                                  @ Matrix.Translation(-now))
            else:
                self.stage1[name] = Matrix.Translation(now - at)
        for side_pc, side_psp in (("L", "left"), ("R", "right")):
            self._foot(side_pc, side_psp, heads)
            self._finger(side_pc, side_psp, heads)
        # The PC's pelvis has no segment of its own: it moves with the spine.
        self.stage1["Bip00_Pelvis"] = self.stage1["Bip01_Spine"]
        # The head stays upright: same orientation in rest, on the PSP's joint.
        now = self.new["Bip01_Head"]
        self.pose["head"] = Matrix.Translation(heads["head"] - now)

    def _foot(self, side_pc, side_psp, heads):
        foot, toe = f"Bip00_{side_pc}_Foot", f"Bip00_{side_pc}_Toe0"
        now = self.new[foot]
        drop = now - self.J[foot]
        ankle = heads[f"{side_psp}foot"]
        # Across the floor the ankle goes to the PSP's; up and down the sole stays where the PC had it.
        move = Vector((ankle.x - now.x, -drop.y, ankle.z - now.z))
        self.pose[f"{side_psp}foot"] = Matrix.Translation(move)
        self.stage1[toe] = self.stage1[foot]

    def _finger(self, side_pc, side_psp, heads):
        hand, finger = f"Bip01_{side_pc}_Hand", f"Bip01_{side_pc}_Finger0"
        self.stage1[finger] = Matrix.Translation(self.new[finger] - self.J[finger])
        d = (self.J[finger] - self.J[hand]).normalized()
        a, b = heads[f"{side_psp}finger1"], heads[f"{side_psp}finger2"]
        rotation = d.rotation_difference((b - a).normalized())
        self.pose[f"{side_psp}finger1"] = (Matrix.Translation(a) @ rotation.to_matrix().to_4x4()
                                           @ Matrix.Translation(-self.new[finger]))


class FitRest(gmo.Rest):
    """The PSP bones with a new bind, T⁻¹ · bind, so the skin matrix at the PSP's rest is T."""

    def __init__(self, mesh_model, fit):
        super().__init__(mesh_model)
        self.psp_bind = list(self.bind)
        self.T = []
        for i, bone in enumerate(self.bones):
            own = fit.pose.get(bone.name)
            self.T.append(own if own is not None else
                          (self.T[bone.parent] if bone.parent >= 0 else Matrix.Identity(4)))
        self.bind = [t.inverted() @ b for t, b in zip(self.T, self.psp_bind)]
        self._set_bone_axes()
        self.deforming_names = set(GROUP_MAP.values()) | {"root", "spine1", "spine2"}
        self.blend_refs = [i for i, b in enumerate(self.bones) if b.name in self.deforming_names]
        self.offsets = [self.bind[i].inverted() for i in self.blend_refs]


def spine_split(position, fit, rest):
    """How the PC's spine weight falls on root, spine1, spine2 at this height along the spine."""
    at = fit.new["Bip01_Spine"]
    d = (fit.new["Bip01_Neck"] - at).normalized()
    stops = []
    for name in ("root", "spine1", "spine2"):
        i = next(k for k, b in enumerate(rest.bones) if b.name == name)
        stops.append((rest.bind[i].translation - at).dot(d))
    t = (position - at).dot(d)
    if t <= stops[0]:
        return {"root": 1.0}
    if t >= stops[2]:
        return {"spine2": 1.0}
    if t < stops[1]:
        k = (t - stops[0]) / (stops[1] - stops[0])
        return {"root": 1 - k, "spine1": k}
    k = (t - stops[1]) / (stops[2] - stops[1])
    return {"spine1": 1 - k, "spine2": k}


def convert_mesh(obj, fit, rest, armature, names):
    data = obj.data
    normals = [to_y_up(n.vector) for n in data.corner_normals]
    groups = {g.index: g.name for g in obj.vertex_groups}
    new_weights = []
    for v in data.vertices:
        source = to_y_up(v.co)
        total = sum(g.weight for g in v.groups)
        moved = Vector((0, 0, 0))
        weights = {}
        for g in v.groups:
            name = groups[g.group]
            w = g.weight / total
            moved += (fit.stage1[name] @ source) * w
            weights[name] = w
        out = {}
        for name, w in weights.items():
            if name == "Bip01_Spine":
                for bone, k in spine_split(moved, fit, rest).items():
                    out[bone] = out.get(bone, 0.0) + w * k
            else:
                out[GROUP_MAP[name]] = out.get(GROUP_MAP[name], 0.0) + w
        v.co = moved
        new_weights.append(out)
    data.normals_split_custom_set(normals)
    data.update()
    obj.vertex_groups.clear()
    for mod in list(obj.modifiers):
        obj.modifiers.remove(mod)
    index = {name: i for i, name in enumerate(names)}
    made = {}
    influences = []
    for v, weights in enumerate(new_weights):
        influences.append({index[b]: w for b, w in weights.items()})
        for bone, w in weights.items():
            if bone not in made:
                made[bone] = obj.vertex_groups.new(name=bone)
            made[bone].add([v], w, 'REPLACE')
    obj.parent = armature
    obj.matrix_parent_inverse = Matrix.Identity(4)
    obj.matrix_local = Matrix.Identity(4)
    obj.modifiers.new("Armature", 'ARMATURE').object = armature
    return [tuple(v.co) for v in data.vertices], influences


def main():
    argv = sys.argv[sys.argv.index("--") + 1:]
    parser = argparse.ArgumentParser()
    parser.add_argument("--x2blend", required=True)
    parser.add_argument("--x", required=True)
    parser.add_argument("--rig", required=True)
    parser.add_argument("--mesh", required=True)
    parser.add_argument("--out", required=True)
    parser.add_argument("--render-prefix")
    args = parser.parse_args(argv)

    sys.path.insert(0, args.x2blend)
    from x2blend import build

    for leftover in list(bpy.data.objects):
        bpy.data.objects.remove(leftover)
    build.import_file(args.x)
    pc_armature = next(o for o in bpy.data.objects if o.type == 'ARMATURE')
    meshes = [o for o in bpy.data.objects if o.type == 'MESH']
    joints = {b.name: to_y_up(b.head_local) for b in pc_armature.data.bones}
    parents = {b.name: b.parent.name if b.parent else None for b in pc_armature.data.bones}
    for action in list(bpy.data.actions):
        bpy.data.actions.remove(action)

    rig = gmo.parse_gmo(open(args.rig, "rb").read())
    mesh_model = gmo.parse_gmo(open(args.mesh, "rb").read())
    psp_rest = gmo.Rest(mesh_model)
    fit = Fit(joints, parents, psp_rest)
    rest = FitRest(mesh_model, fit)

    scene = bpy.context.scene
    collection = scene.collection
    for obj in meshes:
        for owner in list(obj.users_collection):
            owner.objects.unlink(obj)
        collection.objects.link(obj)
    for owner in list(pc_armature.users_collection):
        owner.objects.unlink(pc_armature)
    armature, names = gmo.build_armature(rig, rest, collection)
    converted = [(obj, *convert_mesh(obj, fit, rest, armature, names)) for obj in meshes]
    bpy.data.objects.remove(pc_armature)
    scene.render.fps = 30

    armature.animation_data_create()
    built = []
    for motion in rig.motions:
        if motion.bindings:
            action, slot, _ = gmo.build_action(motion, rig, rest, armature, names)
            built.append((motion, action, slot))
    print(f"actions {len(built)}, deforming bones {len(rest.blend_refs)}")

    worst = 0.0
    checked = built[:: max(1, len(built) // 8)]
    for motion, action, slot in checked:
        armature.animation_data.action = action
        armature.animation_data.action_slot = slot
        keys = sorted({k[0] for c in motion.curves for k in c.keys})
        for t in keys[:: max(1, len(keys) // 3)]:
            for obj, positions, influences in converted:
                worst = max(worst, gmo.compare_pose(scene, obj, motion, rig, rest, positions, influences, t))
    print(f"pose against the file's raw values, {len(checked)} takes: worst at keys {worst:.5f}")

    if args.render_prefix:
        armature.animation_data.action = None
        center = (0, 0, 0.85)
        gmo.render(scene, args.render_prefix + "_rest.png", center, 2.0)
        wanted = {"Take 001": 31, "Take 001-0000": 11, "Take 001-0020": 12}
        for motion, action, slot in built:
            if motion.name in wanted:
                armature.animation_data.action = action
                armature.animation_data.action_slot = slot
                scene.frame_set(wanted[motion.name])
                gmo.render(scene, f"{args.render_prefix}_{motion.name.replace(' ', '_')}_{wanted[motion.name]}.png", center, 2.0)
    first = built[0]
    armature.animation_data.action = first[1]
    armature.animation_data.action_slot = first[2]
    scene.frame_start, scene.frame_end = int(first[0].range[0]), int(first[0].range[1])
    scene.frame_set(0)
    bpy.ops.wm.save_as_mainfile(filepath=args.out)
    print("saved", args.out)


if __name__ == "__main__":
    main()
