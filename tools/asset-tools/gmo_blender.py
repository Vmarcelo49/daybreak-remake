#!/usr/bin/env python3
"""
Import a PSP GMO skeleton with its motions, and a GMO mesh, into Blender, with no animation bake.
Each key in the file becomes one key on an F-curve, at the same frame.

    blender --background --factory-startup --python gmo_blender.py -- \
        --rig chrm19.gmo --mesh chr190.gmo --gim chrt19.gim --out okonogi.blend

Format, read from Higurashi Daybreak Portable's files (docs/PSP-CHARACTERS-PLAN.md):
  chunk   u16 type, u16 header size, u32 size; 0x8000 in the type marks a short chunk with no name
  0x0004  bone: 0x8041 parent, 0x8048 translate, 0x804b quaternion (xyzw), 0x8044 blend bones,
          0x8045 their offset matrices (row vectors)
  0x000b  motion: 0x80b1 frame range, 0x80b2 fps, 0x80b3 (bone, target chunk type, 0, fcurve)
  0x000c  fcurve: u32 format, dimensions, key count, 0, then (frame, values) per key.
          The low nibble of format is 0 constant, 1 linear, 4 slerp
  0x0007  vertices: u32 PSP vertex type, count, 2 more, then the vertices. Weights are u8, 128 = 1
  0x0006  mesh: 0x8061 material, 0x8062 palette into the blend bones, 0x8066 draws
          (arrays, mode, count, repeat, first); a draw's strips follow each other in the arrays

Bones are rebuilt as bind × C, where C is a fixed rotation pointing +Y along the bone. The pose
value for a file value L is then C⁻¹ · R⁻¹ · L · C, with R the bind pose relative to the parent. For
a rotation-and-translation bone that splits into one formula per channel, each linear in the key's
components, so one key stays one key.
"""
import argparse
import math
import struct
import sys

import bpy
from mathutils import Matrix, Quaternion, Vector

CONSTANT, LINEAR = 0, 1
TARGET_TRANSLATE, TARGET_ROTATE = 0x48, 0x4b
CONTAINERS = (2, 3, 4, 5, 6, 8, 9, 0xa, 0xb)
LEAF_BONE_LENGTH = 3.0
# chrtNN.gim holds 10 pictures: 8 expressions, then hair, then the scalp with the ear. Read on Okonogi's.
HEAD_PICTURES = {"__face": 0, "__hair": 8, "__head": 9}


def walk(data, start, end):
    """Yields (type, header, size, offset) for the chunks directly inside the range."""
    while start + 8 <= end:
        kind, header = struct.unpack_from("<HH", data, start)
        size = struct.unpack_from("<I", data, start + 4)[0]
        if size < 8 or start + size > end:
            raise ValueError(f"bad GMO chunk at {start:#x}")
        yield kind, header, size, start
        start += size


def chunk_name(data, offset, header):
    return data[offset + 16:offset + header].split(b"\0", 1)[0].decode("ascii", "replace")


def floats(data, offset, count):
    return struct.unpack_from(f"<{count}f", data, offset)


class Bone:
    def __init__(self, name):
        self.name = name
        self.parent = -1
        self.t = Vector((0, 0, 0))
        self.q = Quaternion()
        self.blend_refs = []
        self.offsets = []


class Curve:
    def __init__(self, data, offset, header, size):
        self.format, self.dimensions, count = struct.unpack_from("<3I", data, offset + header)
        self.keys = []
        at = offset + header + 16
        for _ in range(count):
            values = floats(data, at, self.dimensions + 1)
            self.keys.append((values[0], values[1:]))
            at += 4 * (self.dimensions + 1)

    @property
    def mode(self):
        return self.format & 15

    def sample(self, frame):
        keys = self.keys
        if frame <= keys[0][0]:
            return keys[0][1]
        for (t0, v0), (t1, v1) in zip(keys, keys[1:]):
            if frame < t1:
                if self.mode == 0:
                    return v0
                k = (frame - t0) / (t1 - t0)
                if self.mode == 4:
                    a = Quaternion((v0[3], v0[0], v0[1], v0[2]))
                    b = Quaternion((v1[3], v1[0], v1[1], v1[2]))
                    if a.dot(b) < 0:
                        b.negate()
                    q = a.slerp(b, k)
                    return (q.x, q.y, q.z, q.w)
                return tuple(x + (y - x) * k for x, y in zip(v0, v1))
        return keys[-1][1]


class Motion:
    def __init__(self, name):
        self.name = name
        self.range = (0.0, 0.0)
        self.fps = 30.0
        self.bindings = []
        self.curves = []


class Model:
    def __init__(self):
        self.bones, self.motions, self.arrays, self.meshes = [], [], [], []
        self.materials, self.textures = [], []


def parse_bone(data, offset, header, size):
    bone = Bone(chunk_name(data, offset, header))
    for kind, _, _, at in walk(data, offset + header, offset + size):
        if kind == 0x8041:
            bone.parent = struct.unpack_from("<I", data, at + 8)[0] & 0xfff
        elif kind == 0x8048:
            bone.t = Vector(floats(data, at + 8, 3))
        elif kind == 0x804b:
            x, y, z, w = floats(data, at + 8, 4)
            bone.q = Quaternion((w, x, y, z))
        elif kind == 0x8044:
            count = struct.unpack_from("<I", data, at + 8)[0]
            bone.blend_refs = [r & 0xfff for r in struct.unpack_from(f"<{count}I", data, at + 12)]
        elif kind == 0x8045:
            count = struct.unpack_from("<I", data, at + 8)[0]
            for i in range(count):
                m = floats(data, at + 12 + i * 64, 16)
                # Stored for row vectors; mathutils multiplies column vectors.
                bone.offsets.append(Matrix([m[0:4], m[4:8], m[8:12], m[12:16]]).transposed())
    return bone


def parse_motion(data, offset, header, size):
    motion = Motion(chunk_name(data, offset, header))
    for kind, sub_header, chunk_size, at in walk(data, offset + header, offset + size):
        if kind == 0x80b1:
            motion.range = floats(data, at + 8, 2)
        elif kind == 0x80b2:
            motion.fps = floats(data, at + 8, 1)[0]
        elif kind == 0x80b3:
            bone, target, _, curve = struct.unpack_from("<4I", data, at + 8)
            motion.bindings.append((bone & 0xfff, target, curve & 0xfff))
        elif kind == 0xc:
            motion.curves.append(Curve(data, at, sub_header, chunk_size))
    return motion


def vertex_layout(vtype):
    """The PSP GE's vertex layout: weights, UV, colour, normal, position, aligned to the largest."""
    sizes = {0: 0, 1: 1, 2: 2, 3: 4}
    at, largest = 0, 1

    def place(item, count):
        nonlocal at, largest
        if not item:
            return None
        at = (at + item - 1) & ~(item - 1)
        start = at
        at += item * count
        largest = max(largest, item)
        return start

    weight_kind = (vtype >> 9) & 3
    weight_count = ((vtype >> 14) & 7) + 1
    weights = place(sizes[weight_kind], weight_count)
    uv_kind = vtype & 3
    uv = place(sizes[uv_kind], 2)
    place({0: 0, 4: 2, 5: 2, 6: 2, 7: 4}[(vtype >> 2) & 7], 1)
    normal_kind = (vtype >> 5) & 3
    normal = place(sizes[normal_kind], 3)
    position_kind = (vtype >> 7) & 3
    position = place(sizes[position_kind], 3)
    stride = (at + largest - 1) & ~(largest - 1)
    if weight_kind != 1 or uv_kind != 3 or normal_kind != 1 or position_kind != 3:
        raise ValueError(f"unhandled vertex type {vtype:#x}")
    return weights, weight_count, uv, normal, position, stride


def parse_arrays(data, offset, header):
    vtype, count = struct.unpack_from("<II", data, offset + header)
    weights, weight_count, uv, normal, position, stride = vertex_layout(vtype)
    base = offset + header + 16
    out = []
    for i in range(count):
        v = base + i * stride
        out.append({
            "weights": data[v + weights:v + weights + weight_count],
            "uv": floats(data, v + uv, 2),
            "normal": struct.unpack_from("<3b", data, v + normal),
            "position": floats(data, v + position, 3),
        })
    return out


def parse_mesh(data, offset, header, size):
    mesh = {"material": 0, "palette": [], "draws": []}
    for kind, _, _, at in walk(data, offset + header, offset + size):
        if kind == 0x8061:
            mesh["material"] = struct.unpack_from("<I", data, at + 8)[0] & 0xfff
        elif kind == 0x8062:
            count = struct.unpack_from("<I", data, at + 8)[0]
            mesh["palette"] = list(struct.unpack_from(f"<{count}I", data, at + 12))
        elif kind == 0x8066:
            mesh["draws"].append(struct.unpack_from("<5I", data, at + 8))
    return mesh


def parse_gmo(data):
    if data[:11] != b"OMG.00.1PSP":
        raise ValueError("not a GMO")
    model = Model()

    def descend(start, end):
        for kind, header, size, at in walk(data, start, end):
            if kind == 4:
                model.bones.append(parse_bone(data, at, header, size))
            elif kind == 0xb:
                model.motions.append(parse_motion(data, at, header, size))
            elif kind == 7:
                model.arrays.append(parse_arrays(data, at, header))
            elif kind == 6:
                model.meshes.append(parse_mesh(data, at, header, size))
            elif kind == 8:
                refs = [struct.unpack_from("<I", data, a + 8)[0] & 0xfff
                        for k, h, s, b in walk(data, at + header, at + size) if k == 9
                        for k2, _, _, a in walk(data, b + h, b + s) if k2 == 0x8091]
                model.materials.append((chunk_name(data, at, header), refs[0] if refs else -1))
            elif kind == 0xa:
                # 0x8013 is a u32 size and a whole TGA file; textures without one live in other files.
                tga = [data[a + 12:a + s] for k, _, s, a in walk(data, at + header, at + size) if k == 0x8013]
                model.textures.append((chunk_name(data, at, header), tga[0] if tga else None))
            elif kind in CONTAINERS:
                descend(at + header, at + size)

    descend(0x10, len(data))
    return model


def gim_colour(pixel, kind):
    if kind == 0:
        return (pixel & 31) * 255 // 31, ((pixel >> 5) & 63) * 255 // 63, ((pixel >> 11) & 31) * 255 // 31, 255
    if kind == 1:
        return ((pixel & 31) * 255 // 31, ((pixel >> 5) & 31) * 255 // 31, ((pixel >> 10) & 31) * 255 // 31,
                255 if pixel >> 15 else 0)
    if kind == 2:
        return (pixel & 15) * 17, ((pixel >> 4) & 15) * 17, ((pixel >> 8) & 15) * 17, (pixel >> 12) * 17
    raise ValueError(f"GIM colour format {kind}")


def decode_gim(d, frame=0):
    """One picture of a GIM to (width, height, RGBA rows from the top)."""
    pictures = []

    def descend(at, end):
        while at + 16 <= end:
            kind = struct.unpack_from("<H", d, at)[0]
            size, following, inner = struct.unpack_from("<III", d, at + 4)
            if size < 16:
                return
            if kind == 2:
                descend(at + inner, at + size)
            elif kind == 3:
                pictures.append({})
                descend(at + inner, at + size)
            elif kind in (4, 5) and pictures:
                pictures[-1][kind] = at + inner
            at += following or size

    descend(0x10, len(d))
    found = pictures[frame]
    image = found[4]
    _, _, kind, order, w, h, bpp, align = struct.unpack_from("<8H", d, image)
    raw = d[image + struct.unpack_from("<I", d, image + 0x1c)[0]:]
    if order == 1:
        pitch = (((w * bpp + 7) // 8) + 15) & ~15
        out = bytearray(pitch * ((h + 7) & ~7))
        src = 0
        for row in range((h + 7) // 8):
            for x in range(0, pitch, 16):
                for y in range(8):
                    at = (row * 8 + y) * pitch + x
                    out[at:at + 16] = raw[src:src + 16]
                    src += 16
        raw = bytes(out)
    else:
        pitch = (w * bpp + 7) // 8
        if align:
            pitch = (pitch + align - 1) & ~(align - 1)
    palette = []
    if kind in (4, 5):
        pal = found[5]
        _, _, pal_kind, _, pal_width = struct.unpack_from("<5H", d, pal)
        pb = d[pal + struct.unpack_from("<I", d, pal + 0x1c)[0]:]
        for i in range(pal_width):
            palette.append(tuple(pb[i * 4:i * 4 + 4]) if pal_kind == 3
                           else gim_colour(struct.unpack_from("<H", pb, i * 2)[0], pal_kind))
    pixels = bytearray(w * h * 4)
    for y in range(h):
        line = raw[y * pitch:y * pitch + pitch]
        for x in range(w):
            if kind == 3:
                px = line[x * 4:x * 4 + 4]
            elif kind == 5:
                px = palette[line[x]]
            elif kind == 4:
                px = palette[(line[x // 2] >> (4 * (x & 1))) & 15]
            else:
                px = gim_colour(struct.unpack_from("<H", line, x * 2)[0], kind)
            pixels[(y * w + x) * 4:(y * w + x) * 4 + 4] = bytes(px)
    return w, h, bytes(pixels)


def decode_tga(d):
    """A colour-mapped, uncompressed TGA to (width, height, RGBA rows from the top)."""
    id_size, has_map, kind, map_first, map_count, map_bits, _, _, w, h, bpp, descriptor = struct.unpack_from(
        "<3BHHB4H2B", d, 0)
    if has_map != 1 or kind != 1 or bpp != 8 or map_bits not in (24, 32):
        raise ValueError(f"TGA kind {kind}, {bpp} bpp")
    at = 18 + id_size
    step = map_bits // 8
    palette = []
    for i in range(map_count):
        c = d[at + i * step:at + (i + 1) * step]
        palette.append((c[2], c[1], c[0], c[3] if step == 4 else 255))
    at += map_count * step
    rows = [b"".join(bytes(palette[v - map_first]) for v in d[at + y * w:at + (y + 1) * w]) for y in range(h)]
    if not descriptor & 0x20:
        rows.reverse()
    return w, h, b"".join(rows)


def make_image(name, decoded):
    w, h, rgba = decoded
    image = bpy.data.images.new(name, w, h, alpha=True)
    rows = [rgba[y * w * 4:(y + 1) * w * 4] for y in range(h - 1, -1, -1)]
    image.pixels.foreach_set([c / 255 for c in b"".join(rows)])
    image.pack()
    return image


def trs(t, q):
    return Matrix.Translation(t) @ q.to_matrix().to_4x4()


class Rest:
    """The bind pose from the mesh file, and each bone's axis rotation."""

    def __init__(self, mesh_model):
        self.bones = mesh_model.bones
        blender = next(b for b in self.bones if b.blend_refs)
        self.blend_refs = blender.blend_refs
        self.offsets = blender.offsets
        self.bind = []
        inverse = {r: m.inverted() for r, m in zip(self.blend_refs, self.offsets)}
        self.worst_bind_gap = 0.0
        for i, bone in enumerate(self.bones):
            parent = self.bind[bone.parent] if bone.parent >= 0 else Matrix.Identity(4)
            fk = parent @ trs(bone.t, bone.q)
            if i in inverse:
                gap = max(abs(fk[r][c] - inverse[i][r][c]) for r in range(3) for c in range(4))
                self.worst_bind_gap = max(self.worst_bind_gap, gap)
            self.bind.append(inverse.get(i, fk))
        self._set_bone_axes()

    def _set_bone_axes(self):
        self.axis, self.length = [], []
        children = [[] for _ in self.bones]
        for i, bone in enumerate(self.bones):
            if bone.parent >= 0:
                children[bone.parent].append(i)
        for i in range(len(self.bones)):
            ends = [self.bind[i].inverted() @ self.bind[c].translation for c in children[i]]
            ends = [e for e in ends if e.length > 1e-3]
            if ends:
                end = max(ends, key=lambda e: e.length)
                self.axis.append(Vector((0, 1, 0)).rotation_difference(end.normalized()))
                self.length.append(end.length)
            else:
                self.axis.append(Quaternion())
                self.length.append(LEAF_BONE_LENGTH)

    def relative(self, i):
        parent = self.bones[i].parent
        m = self.bind[i] if parent < 0 else self.bind[parent].inverted() @ self.bind[i]
        return m.translation.copy(), m.to_quaternion()


def build_armature(rig, rest, collection):
    data = bpy.data.armatures.new("psp_skeleton")
    obj = bpy.data.objects.new("psp_skeleton", data)
    collection.objects.link(obj)
    # The file's units and Y-up stay in the data, as X2Blend keeps its units.
    obj.scale = (0.01, 0.01, 0.01)
    obj.rotation_euler = (math.pi / 2, 0, 0)
    bpy.context.view_layer.objects.active = obj
    obj.select_set(True)
    bpy.ops.object.mode_set(mode='EDIT')
    edit = []
    deforming = set(rest.blend_refs)
    for i, source in enumerate(rig.bones):
        bone = data.edit_bones.new(source.name)
        bone.length = rest.length[i]
        bind = rest.bind[i]
        bone.matrix = Matrix.Translation(bind.translation) @ (bind.to_quaternion() @ rest.axis[i]).to_matrix().to_4x4()
        bone.use_deform = i in deforming
        edit.append(bone)
    for i, source in enumerate(rig.bones):
        if source.parent >= 0:
            edit[i].parent = edit[source.parent]
    names = [b.name for b in edit]
    bpy.ops.object.mode_set(mode='OBJECT')
    for bone in obj.pose.bones:
        bone.rotation_mode = 'QUATERNION'
    return obj, names


def add_curve(bag, path, index, group, times, values, interpolation):
    curve = bag.fcurves.new(path, index=index, group_name=group)
    points = curve.keyframe_points
    points.add(len(times))
    flat = [0.0] * (2 * len(times))
    flat[0::2] = times
    flat[1::2] = values
    points.foreach_set("co", flat)
    points.foreach_set("interpolation", [interpolation] * len(times))
    curve.update()


def build_action(motion, rig, rest, armature, names):
    action = bpy.data.actions.new(motion.name)
    action.use_fake_user = True
    slot = action.slots.new(id_type='OBJECT', name=armature.name)
    bag = action.layers.new("Keys").strips.new(type='KEYFRAME').channelbag(slot, ensure=True)
    translate, rotate, skipped = {}, {}, 0
    for bone, target, curve in motion.bindings:
        if target == TARGET_TRANSLATE:
            translate[bone] = motion.curves[curve]
        elif target == TARGET_ROTATE:
            rotate[bone] = motion.curves[curve]
        else:
            skipped += 1
    file_keys = sum(len(c.keys) for c in translate.values()) + sum(len(c.keys) for c in rotate.values())
    for i, source in enumerate(rig.bones):
        name = names[i]
        path = f'pose.bones["{name}"]'
        rest_t, rest_q = rest.relative(i)
        to_pose = (rest_q @ rest.axis[i]).inverted()
        c = rotate.get(i)
        if c:
            times = [k[0] for k in c.keys]
            raw = [Quaternion((v[3], v[0], v[1], v[2])) for _, v in c.keys]
            mode = CONSTANT if c.mode == 0 else LINEAR
        else:
            times, raw, mode = [0.0], [source.q], CONSTANT
        values, previous = [], None
        for q in raw:
            p = to_pose @ q @ rest.axis[i]
            # The same rotation either way, but curves must not interpolate through zero.
            if previous is not None and previous.dot(p) < 0:
                p.negate()
            values.append(p)
            previous = p
        for k in range(4):
            add_curve(bag, path + ".rotation_quaternion", k, name, times, [p[k] for p in values], mode)
        c = translate.get(i)
        if c:
            times = [k[0] for k in c.keys]
            raw = [Vector(v) for _, v in c.keys]
            mode = CONSTANT if c.mode == 0 else LINEAR
        else:
            times, raw, mode = [0.0], [source.t], CONSTANT
        values = [to_pose @ (t - rest_t) for t in raw]
        for k in range(3):
            add_curve(bag, path + ".location", k, name, times, [v[k] for v in values], mode)
    action.use_frame_range = True
    action.frame_start, action.frame_end = motion.range[0], max(motion.range[1], 1.0)
    action["gmo_file_keys"] = file_keys
    return action, slot, skipped


def build_mesh(mesh_model, rest, armature, names, images, collection):
    """One object; vertices merge only when position and weights agree, so seams stay sound."""
    table, positions, influences, faces, face_uvs, face_normals, face_materials = {}, [], [], [], [], [], []
    source_to_vertex = {}
    for mesh in mesh_model.meshes:
        for ref, mode, count, repeat, first in mesh["draws"]:
            array_index = ref & 0xfff
            array = mesh_model.arrays[array_index]
            if mode & 0xff not in (3, 4):
                raise ValueError(f"draw mode {mode:#x}")
            strip = mode & 0xff == 4

            def vertex(i):
                source = array[i]
                weights = {}
                for slot, w in enumerate(source["weights"]):
                    if w:
                        bone = rest.blend_refs[mesh["palette"][slot]]
                        weights[bone] = weights.get(bone, 0) + w
                key = (tuple(round(x, 4) for x in source["position"]), tuple(sorted(weights.items())))
                at = table.get(key)
                if at is None:
                    at = table[key] = len(positions)
                    positions.append(source["position"])
                    influences.append(weights)
                source_to_vertex[(array_index, i)] = at
                return at

            for r in range(repeat):
                start = first + r * count
                for k in range(count - 2) if strip else range(0, count - 2, 3):
                    a, b, c = start + k, start + k + 1, start + k + 2
                    if strip and k & 1:
                        a, b = b, a
                    tri = [vertex(a), vertex(b), vertex(c)]
                    if len(set(tri)) < 3:
                        continue
                    faces.append(tri)
                    face_uvs.append([array[x]["uv"] for x in (a, b, c)])
                    face_normals.append([array[x]["normal"] for x in (a, b, c)])
                    face_materials.append(mesh["material"])
    data = bpy.data.meshes.new("psp_mesh")
    data.from_pydata(positions, [], faces)
    uv = data.uv_layers.new(name="UVMap")
    for loop, (u, v) in zip(uv.uv, (p for f in face_uvs for p in f)):
        loop.vector = (u, 1.0 - v)
    for name, ref in mesh_model.materials:
        material = bpy.data.materials.new(name)
        material.use_nodes = True
        shader = material.node_tree.nodes["Principled BSDF"]
        shader.inputs["Roughness"].default_value = 0.9
        image = images.get(ref)
        if image:
            texture = material.node_tree.nodes.new("ShaderNodeTexImage")
            texture.image = image
            texture.interpolation = 'Closest'
            material.node_tree.links.new(texture.outputs["Color"], shader.inputs["Base Color"])
            material.node_tree.links.new(texture.outputs["Alpha"], shader.inputs["Alpha"])
        data.materials.append(material)
    data.polygons.foreach_set("material_index", face_materials)
    normals = [Vector(n).normalized() for f in face_normals for n in f]
    data.polygons.foreach_set("use_smooth", [True] * len(faces))
    data.normals_split_custom_set(normals)
    data.update()
    obj = bpy.data.objects.new("psp_mesh", data)
    collection.objects.link(obj)
    obj.parent = armature
    obj.modifiers.new("Armature", 'ARMATURE').object = armature
    groups = {}
    for v, weights in enumerate(influences):
        for bone, w in weights.items():
            if bone not in groups:
                groups[bone] = obj.vertex_groups.new(name=names[bone])
            groups[bone].add([v], w / 128.0, 'REPLACE')
    return obj, positions, influences


def expected_pose(motion, rig, rest, frame):
    """World matrices from the file's raw values, without Blender's bones."""
    translate = {b: motion.curves[c] for b, t, c in motion.bindings if t == TARGET_TRANSLATE}
    rotate = {b: motion.curves[c] for b, t, c in motion.bindings if t == TARGET_ROTATE}
    world = []
    for i, bone in enumerate(rig.bones):
        t = Vector(translate[i].sample(frame)) if i in translate else bone.t
        if i in rotate:
            x, y, z, w = rotate[i].sample(frame)
            q = Quaternion((w, x, y, z))
        else:
            q = bone.q
        parent = world[bone.parent] if bone.parent >= 0 else Matrix.Identity(4)
        world.append(parent @ trs(t, q))
    return world


def compare_pose(scene, obj, motion, rig, rest, positions, influences, frame):
    whole = math.floor(frame)
    scene.frame_set(whole, subframe=frame - whole)
    graph = bpy.context.evaluated_depsgraph_get()
    evaluated = obj.evaluated_get(graph)
    mesh = evaluated.to_mesh()
    world = expected_pose(motion, rig, rest, frame)
    skin = {r: world[r] @ o for r, o in zip(rest.blend_refs, rest.offsets)}
    worst = 0.0
    for i, (position, weights) in enumerate(zip(positions, influences)):
        total = sum(weights.values())
        p = Vector((0, 0, 0))
        for bone, w in weights.items():
            p += (skin[bone] @ Vector(position)) * (w / total)
        worst = max(worst, (mesh.vertices[i].co - p).length)
    evaluated.to_mesh_clear()
    return worst


def render(scene, path, center, height):
    camera = bpy.data.objects.get("camera")
    if camera is None:
        data = bpy.data.cameras.new("camera")
        data.type = 'ORTHO'
        camera = bpy.data.objects.new("camera", data)
        scene.collection.objects.link(camera)
        scene.camera = camera
        sun = bpy.data.objects.new("sun", bpy.data.lights.new("sun", 'SUN'))
        sun.data.energy = 2.0
        sun.rotation_euler = (math.radians(55), 0, math.radians(-30))
        scene.collection.objects.link(sun)
        world = bpy.data.worlds.new("world")
        world.use_nodes = True
        world.node_tree.nodes["Background"].inputs[0].default_value = (0.75, 0.75, 0.78, 1)
        scene.world = world
        scene.render.engine = 'CYCLES'
        scene.cycles.samples = 16
        scene.cycles.device = 'CPU'
        scene.render.resolution_x, scene.render.resolution_y = 500, 700
    camera.data.ortho_scale = height
    camera.location = (center[0], center[1] - 10, center[2])
    camera.rotation_euler = (math.pi / 2, 0, 0)
    scene.render.filepath = path
    bpy.ops.render.render(write_still=True)


def main():
    argv = sys.argv[sys.argv.index("--") + 1:]
    parser = argparse.ArgumentParser()
    parser.add_argument("--rig", required=True)
    parser.add_argument("--mesh", required=True)
    parser.add_argument("--gim", help="the head texture, used for materials the mesh file does not embed")
    parser.add_argument("--out", required=True)
    parser.add_argument("--render-prefix", help="render a few poses to <prefix>_*.png")
    args = parser.parse_args(argv)

    rig = parse_gmo(open(args.rig, "rb").read())
    mesh_model = parse_gmo(open(args.mesh, "rb").read())
    if len(rig.bones) != len(mesh_model.bones):
        raise SystemExit("rig and mesh have different bone counts")
    print("names that differ:", [(a.name, b.name) for a, b in zip(rig.bones, mesh_model.bones) if a.name != b.name])
    rest = Rest(mesh_model)
    print(f"bones {len(rig.bones)}, blend bones {len(rest.blend_refs)}, "
          f"worst gap between hierarchy and offset matrices {rest.worst_bind_gap:.5f}")

    scene = bpy.context.scene
    collection = scene.collection
    for leftover in list(bpy.data.objects):
        bpy.data.objects.remove(leftover)
    scene.render.fps = 30

    images = {}
    head_file = open(args.gim, "rb").read() if args.gim else None
    for i, (name, tga) in enumerate(mesh_model.textures):
        frame = next((f for suffix, f in HEAD_PICTURES.items() if name.endswith(suffix)), None)
        if tga:
            images[i] = make_image(name, decode_tga(tga))
        elif head_file and frame is not None:
            images[i] = make_image(name, decode_gim(head_file, frame))
        print(f"texture {i} {name}: {'embedded' if tga else f'head file picture {frame}'}")

    armature, names = build_armature(rig, rest, collection)
    mesh_obj, positions, influences = build_mesh(mesh_model, rest, armature, names, images, collection)
    print(f"mesh: {len(positions)} merged vertices, {len(mesh_obj.data.polygons)} triangles")
    totals = [sum(w.values()) for w in influences]
    print(f"weight totals over 128: min {min(totals)} max {max(totals)}")

    armature.animation_data_create()
    built = []
    empty = 0
    skipped = 0
    for motion in rig.motions:
        if not motion.bindings:
            empty += 1
            continue
        action, slot, s = build_action(motion, rig, rest, armature, names)
        skipped += s
        built.append((motion, action, slot))
    print(f"actions {len(built)}, empty takes left out {empty}, non-transform curves left out {skipped}")

    worst_key, worst_mid = 0.0, 0.0
    worst_where = None
    checked = built if len(built) <= 8 else built[:: max(1, len(built) // 8)]
    for motion, action, slot in checked:
        armature.animation_data.action = action
        armature.animation_data.action_slot = slot
        keys = sorted({k[0] for c in motion.curves for k in c.keys})
        for t in keys[:: max(1, len(keys) // 4)]:
            e = compare_pose(scene, mesh_obj, motion, rig, rest, positions, influences, t)
            if e > worst_key:
                worst_key, worst_where = e, (motion.name, t)
        for a, b in list(zip(keys, keys[1:]))[:: max(1, len(keys) // 4)]:
            worst_mid = max(worst_mid, compare_pose(scene, mesh_obj, motion, rig, rest, positions, influences, (a + b) / 2))
    print(f"pose against the file's raw values, {len(checked)} takes: worst at keys {worst_key:.5f} "
          f"at {worst_where}, worst between keys {worst_mid:.5f} (file units; the fighter is about 156 tall)")

    first = built[0]
    armature.animation_data.action = first[1]
    armature.animation_data.action_slot = first[2]
    keys_in = sum(len(c.keys) for c in first[0].curves)
    print(f"{first[0].name}: range {first[0].range}, fps {first[0].fps}, curves {len(first[0].curves)}, file keys {keys_in}")

    if args.render_prefix:
        center = (0, 0, 0.85)
        armature.animation_data.action = None
        render(scene, args.render_prefix + "_rest.png", center, 2.0)
        for motion, action, slot in (built[0], built[1], built[len(built) // 2]):
            armature.animation_data.action = action
            armature.animation_data.action_slot = slot
            frame = (motion.range[0] + motion.range[1]) / 2
            scene.frame_set(int(frame))
            render(scene, f"{args.render_prefix}_{motion.name.replace(' ', '_')}_{int(frame)}.png", center, 2.0)
    armature.animation_data.action = first[1]
    armature.animation_data.action_slot = first[2]
    scene.frame_start, scene.frame_end = int(first[0].range[0]), int(first[0].range[1])
    scene.frame_set(0)
    bpy.ops.wm.save_as_mainfile(filepath=args.out)
    print("saved", args.out)


if __name__ == "__main__":
    main()
