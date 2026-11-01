#!/usr/bin/env python3
"""
Put a new head on a PC body already bound to the PSP skeleton (psp_fit_body.py).

    blender --background --factory-startup --python psp_head_okonogi.py -- \
        --x2blend <X2Blend checkout> --kasai kasai/00.X --body body.blend --texture okonogi.png --out head.blend

The shape starts from Kasai's head, the PC's own low poly and painted face, reshaped towards Okonogi: a
rounder crown, a wider jaw and a ponytail. The body keeps its neck, and the head sits over it, as the PC's
heads do on their shirts. Kasai's data comes from the user's install, so nothing of it is in this repository.
"""
import argparse
import sys
from math import cos, pi, sin

import bmesh
import bpy
from mathutils import Vector

HEAD_SCALE = 1.2
FACE_MATERIAL = "一顔"
HAIR_MATERIAL = "一髪の毛03"
WEIGHT_MAP = {"Bip01_Head": "head", "Bip01_Neck": "neck", "Bip01_Spine1": "spine2", "Bip01_Spine": "spine2"}

# Rings down the ponytail: (sideways, up, back) from the head joint, radius, weight on the hair bone.
# It hangs to his left, as in the portraits.
PONYTAIL = [
    ((0.0, 9.0, 14.5), 2.6, 0.0),
    ((0.2, 8.0, 16.5), 2.6, 0.0),
    ((0.8, 5.5, 18.5), 3.5, 0.3),
    ((2.2, 0.0, 20.0), 3.9, 0.8),
    ((4.0, -6.0, 19.5), 3.0, 1.0),
    ((5.5, -11.5, 18.0), 1.6, 1.0),
    ((6.2, -15.0, 16.5), 0.2, 1.0),
]
PONYTAIL_SIDES = 6
# UV boxes in the head texture, 0..1 with v up: the back of the hair, and the painted band.
PONYTAIL_UV = (0.66, 0.30, 0.90, 0.98)
BAND_UV = (0.545, 0.92, 0.60, 0.975)


def to_y_up(v):
    return Vector((v[0], v[2], -v[1]))


def smooth(t):
    t = max(0.0, min(1.0, t))
    return t * t * (3 - 2 * t)


def reshape(x, up, back):
    """Kasai to Okonogi, on head-relative coordinates in Kasai's own units."""
    # The crown: Kasai's flat top becomes a dome, narrower the higher it goes.
    crown = smooth((up - 19.0) / 12.0)
    x *= 1.0 - 0.20 * crown
    up -= 1.2 * crown * (abs(back - 2.0) / 14.0)
    # The jaw is wider and heavier below the mouth, and tapers back in at the chin.
    jaw = smooth((8.0 - up) / 6.0) * smooth((up + 2.0) / 4.0)
    x *= 1.0 + 0.10 * jaw
    return x, up, back


def read_kasai(obj, head_joint):
    data = obj.data
    slot = next(i for i, m in enumerate(data.materials) if m.name.startswith(FACE_MATERIAL))
    uv = data.uv_layers[0].data
    corner_normals = data.corner_normals
    groups = {g.index: g.name for g in obj.vertex_groups}
    remap, coords, weights, faces, uvs, normals = {}, [], [], [], [], []
    for poly in data.polygons:
        if poly.material_index != slot:
            continue
        face = []
        for loop in poly.loop_indices:
            index = data.loops[loop].vertex_index
            if index not in remap:
                remap[index] = len(coords)
                vertex = data.vertices[index]
                local = vertex.co - head_joint
                x, up, back = reshape(local.x, local.z, local.y)
                coords.append(Vector((x, up, -back)) * HEAD_SCALE)
                totals = {}
                for g in vertex.groups:
                    name = WEIGHT_MAP[groups[g.group]]
                    totals[name] = totals.get(name, 0.0) + g.weight
                weights.append(totals)
            face.append(remap[index])
            uvs.append(tuple(uv[loop].uv))
            normals.append(to_y_up(corner_normals[loop].vector))
        faces.append(face)
    return coords, weights, faces, uvs, normals


def add_ponytail(coords, weights, faces, uvs, normals):
    start = len(coords)
    for centre, radius, hair in PONYTAIL:
        for side in range(PONYTAIL_SIDES):
            a = 2 * pi * side / PONYTAIL_SIDES
            # Flattened front to back, like a lock of hair and not a pipe.
            offset = Vector((cos(a) * radius, 0.0, sin(a) * radius * 0.75))
            coords.append(Vector((centre[0], centre[1], -centre[2])) + offset)
            weights.append({"head": 1.0 - hair, "downhair1": hair} if hair else {"head": 1.0})
    rings = len(PONYTAIL)
    for ring in range(rings - 1):
        box = BAND_UV if ring == 0 else PONYTAIL_UV
        for side in range(PONYTAIL_SIDES):
            next_side = (side + 1) % PONYTAIL_SIDES
            a = start + ring * PONYTAIL_SIDES + side
            b = start + ring * PONYTAIL_SIDES + next_side
            c = start + (ring + 1) * PONYTAIL_SIDES + next_side
            d = start + (ring + 1) * PONYTAIL_SIDES + side
            faces.append([d, c, b, a])
            for corner_ring, corner_side in ((ring + 1, side), (ring + 1, side + 1), (ring, side + 1), (ring, side)):
                u = box[0] + (box[2] - box[0]) * corner_side / PONYTAIL_SIDES
                v = box[3] - (box[3] - box[1]) * corner_ring / (rings - 1)
                uvs.append((u, v))
                normals.append(Vector((0, 0, 0)))


def strip_keiichi_head(body):
    """Drop the old head from the body mesh, and keep the neck, which carries little head weight."""
    data = body.data
    head_group = body.vertex_groups["head"].index
    slots = {i for i, m in enumerate(data.materials) if m.name in (FACE_MATERIAL, HAIR_MATERIAL)}
    hair_slots = {i for i, m in enumerate(data.materials) if m.name == HAIR_MATERIAL}
    head_weight = [next((g.weight for g in v.groups if g.group == head_group), 0.0) for v in data.vertices]
    doomed = {p.index for p in data.polygons if p.material_index in slots and
              (p.material_index in hair_slots or max(head_weight[v] for v in p.vertices) > 0.4)}
    mesh = bmesh.new()
    mesh.from_mesh(data)
    mesh.faces.ensure_lookup_table()
    bmesh.ops.delete(mesh, geom=[mesh.faces[i] for i in doomed], context='FACES_ONLY')
    loose = [v for v in mesh.verts if not v.link_faces]
    bmesh.ops.delete(mesh, geom=loose, context='VERTS')
    mesh.to_mesh(data)
    mesh.free()
    data.update()
    return len(doomed)


def build_head(armature, kasai_material, texture, coords, weights, faces, uvs, normals, joint):
    mesh = bpy.data.meshes.new("okonogi_head")
    mesh.from_pydata([tuple(joint + c) for c in coords], [], faces)
    mesh.update()
    layer = mesh.uv_layers.new(name="UVMap")
    for loop, uv in enumerate(uvs):
        layer.data[loop].uv = uv
    image = bpy.data.images.load(texture)
    image.pack()
    material = kasai_material.copy()
    material.name = "okonogi_head"
    for node in material.node_tree.nodes:
        if node.type == 'TEX_IMAGE':
            node.image = image
    mesh.materials.append(material)
    mesh.polygons.foreach_set("use_smooth", [True] * len(mesh.polygons))
    mesh.update()
    # The file's normals keep the PC's facets. The ponytail has none, so it takes its own smooth ones.
    computed = [c.vector.copy() for c in mesh.corner_normals]
    mesh.normals_split_custom_set([n if n.length else computed[i] for i, n in enumerate(normals)])
    obj = bpy.data.objects.new("okonogi_head", mesh)
    bpy.context.scene.collection.objects.link(obj)
    for index, per_bone in enumerate(weights):
        for bone, w in per_bone.items():
            group = obj.vertex_groups.get(bone) or obj.vertex_groups.new(name=bone)
            group.add([index], w, 'REPLACE')
    obj.parent = armature
    obj.modifiers.new("Armature", 'ARMATURE').object = armature
    return obj


def main():
    argv = sys.argv[sys.argv.index("--") + 1:]
    parser = argparse.ArgumentParser()
    parser.add_argument("--x2blend", required=True)
    parser.add_argument("--kasai", required=True)
    parser.add_argument("--body", required=True)
    parser.add_argument("--texture", required=True)
    parser.add_argument("--out", required=True)
    args = parser.parse_args(argv)

    sys.path.insert(0, args.x2blend)
    from x2blend import build

    bpy.ops.wm.open_mainfile(filepath=args.body)
    armature = next(o for o in bpy.data.objects if o.type == 'ARMATURE')
    our_actions = set(bpy.data.actions)
    body = next(o for o in bpy.data.objects if o.type == 'MESH' and any(m.name == FACE_MATERIAL for m in o.data.materials))
    for old in ("eye", "hair"):
        bpy.data.objects.remove(bpy.data.objects[old])
    ours = set(bpy.data.objects)
    print("removed", strip_keiichi_head(body), "head faces from the body")

    build.import_file(args.kasai)
    kasai_armature = next(o for o in bpy.data.objects if o.type == 'ARMATURE' and o not in ours)
    kasai = next(o for o in bpy.data.objects if o not in ours and o.type == 'MESH' and
                 any(m and m.name.startswith(FACE_MATERIAL) for m in o.data.materials))
    head_joint = kasai_armature.data.bones["Bip01_Head"].head_local.copy()
    coords, weights, faces, uvs, normals = read_kasai(kasai, head_joint)
    add_ponytail(coords, weights, faces, uvs, normals)
    joint = armature.data.bones["head"].head_local.copy()
    armature.data.bones["downhair1"].use_deform = True
    kasai_material = next(m for m in kasai.data.materials if m.name.startswith(FACE_MATERIAL))
    head = build_head(armature, kasai_material, args.texture, coords, weights, faces, uvs, normals, joint)
    print("head", len(head.data.vertices), "verts", len(head.data.polygons), "faces")

    for leftover in [o for o in bpy.data.objects if o not in ours and o is not head]:
        bpy.data.objects.remove(leftover)
    for action in [a for a in bpy.data.actions if a not in our_actions]:
        bpy.data.actions.remove(action)
    bpy.data.orphans_purge(do_recursive=True)
    bpy.ops.wm.save_as_mainfile(filepath=args.out)
    print("saved", args.out)


if __name__ == "__main__":
    main()
