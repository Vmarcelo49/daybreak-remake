"""Render a filmstrip of every non-empty motion take of one PSP character rig.

    blender -b --factory-startup -P render_takes.py -- \
        --rig <dump>/g3d/chrm17.gmo --mesh <dump>/g3d/chr170.gmo \
        --out <frames dir> --manifest <manifest.json> [--frames 6] [--engine BLENDER_WORKBENCH]

Reuses the repository importer (tools/asset-tools/gmo_blender.py) for the GMO parse,
the armature, the skinned mesh and the per-take action, so the pose math is the one the
importer's own self-check validates. One image per sampled frame, 160x200 by default,
orthographic right-profile view: file +Z (the model's forward) points to image right and
file +Y (up) points up, with a ground line at y=0 and a vertical tick at z=0 as
references. Frames are named <rig>_<take index:02d>_<k>.png.

Empty takes (the `Dummy` slots, no curves) are listed in the manifest but not rendered.
"""
import argparse
import json
import math
import os
import sys

import bpy
from mathutils import Vector

sys.path.insert(0, "/home/marcelo/Projects/daybreak-remake/tools/asset-tools")
import gmo_blender as G  # noqa: E402

UNIT = 0.01          # the importer scales the file's units by this
FRAME_MARGIN = 1.0


def scene_setup(engine, width, height):
    scene = bpy.context.scene
    for obj in list(bpy.data.objects):
        bpy.data.objects.remove(obj)
    scene.render.engine = engine
    scene.render.fps = 30
    scene.render.resolution_x, scene.render.resolution_y = width, height
    scene.render.resolution_percentage = 100
    scene.render.film_transparent = False
    if engine == 'BLENDER_WORKBENCH':
        shading = scene.display.shading
        shading.light = 'STUDIO'
        shading.studio_light = 'Default'
        shading.color_type = 'MATERIAL'
        shading.show_shadows = False
        shading.show_cavity = True
        shading.cavity_type = 'BOTH'
        shading.show_object_outline = True
        shading.object_outline_color = (0.05, 0.05, 0.06)
        scene.display.render_aa = 'FXAA'
    elif engine == 'CYCLES':
        scene.cycles.samples = 8
        scene.cycles.device = 'CPU'
    world = bpy.data.worlds.new("world")
    world.use_nodes = True
    world.node_tree.nodes["Background"].inputs[0].default_value = (0.82, 0.84, 0.88, 1)
    scene.world = world
    scene.view_settings.view_transform = 'Standard'
    return scene


def add_box(scene, name, lo, hi, colour):
    mesh = bpy.data.meshes.new(name)
    x0, y0, z0 = lo
    x1, y1, z1 = hi
    verts = [(x0, y0, z0), (x1, y0, z0), (x1, y1, z0), (x0, y1, z0),
             (x0, y0, z1), (x1, y0, z1), (x1, y1, z1), (x0, y1, z1)]
    faces = [(0, 1, 2, 3), (4, 5, 6, 7), (0, 1, 5, 4), (2, 3, 7, 6), (1, 2, 6, 5), (3, 0, 4, 7)]
    mesh.from_pydata(verts, [], faces)
    mesh.update()
    obj = bpy.data.objects.new(name, mesh)
    obj.color = colour
    scene.collection.objects.link(obj)
    return obj


def make_camera(scene, ortho, center):
    data = bpy.data.cameras.new("camera")
    data.type = 'ORTHO'
    data.ortho_scale = ortho
    camera = bpy.data.objects.new("camera", data)
    scene.collection.objects.link(camera)
    scene.camera = camera
    # Right profile: the camera sits on the model's right (-X) and looks towards +X, so
    # file +Z (forward) runs to image right and file +Y (up) runs up.
    camera.location = (center[0] - 20.0, center[1], center[2])
    direction = Vector((1.0, 0.0, 0.0))
    camera.rotation_euler = direction.to_track_quat('-Z', 'Y').to_euler()
    return camera


def take_frames(motion, count):
    start, end = motion.range
    if count <= 1:
        return [start]
    return [start + (end - start) * i / (count - 1) for i in range(count)]


def main():
    argv = sys.argv[sys.argv.index("--") + 1:]
    ap = argparse.ArgumentParser()
    ap.add_argument("--rig", required=True)
    ap.add_argument("--mesh", required=True)
    ap.add_argument("--out", required=True)
    ap.add_argument("--manifest", required=True)
    ap.add_argument("--frames", type=int, default=6)
    ap.add_argument("--width", type=int, default=160)
    ap.add_argument("--height", type=int, default=200)
    ap.add_argument("--engine", default="BLENDER_WORKBENCH")
    ap.add_argument("--only", default="", help="comma separated take indices; default all")
    ap.add_argument("--ortho", type=float, default=0.0, help="ortho height in file units")
    a = ap.parse_args(argv)

    rig = G.parse_gmo(open(a.rig, "rb").read())
    mesh_model = G.parse_gmo(open(a.mesh, "rb").read())
    if len(rig.bones) != len(mesh_model.bones):
        raise SystemExit("rig and mesh bone counts differ")
    rest = G.Rest(mesh_model)
    scene = scene_setup(a.engine, a.width, a.height)
    collection = scene.collection
    armature, names = G.build_armature(rig, rest, collection)
    mesh_obj, positions, influences = G.build_mesh(mesh_model, rest, armature, names, {}, collection)
    mesh_obj.color = (0.72, 0.74, 0.80, 1.0)
    # One flat viewport colour per material: the GMO splits body, hair, face and clothing,
    # so a solid render keeps the limbs readable against the torso.
    palette = [(0.86, 0.87, 0.92, 1), (0.52, 0.56, 0.66, 1), (0.96, 0.80, 0.72, 1),
               (0.40, 0.44, 0.52, 1), (0.72, 0.62, 0.52, 1), (0.60, 0.72, 0.60, 1),
               (0.78, 0.66, 0.80, 1), (0.90, 0.90, 0.70, 1)]
    for k, material in enumerate(mesh_obj.data.materials):
        material.diffuse_color = palette[k % len(palette)]
    print(f"materials {len(mesh_obj.data.materials)}")
    armature.color = (0.72, 0.74, 0.80, 1.0)
    print(f"bones {len(rig.bones)} motions {len(rig.motions)} vertices {len(positions)} "
          f"tris {len(mesh_obj.data.polygons)}")

    # Frame the rest pose once, then keep the same window for every take so motion reads
    # as motion. Character height is measured from the mesh, so each rig gets its own.
    # The evaluated mesh is in file space (Y up); matrix_world turns it into the scene's
    # (Z up, +Y = the model's backward).
    depsgraph = bpy.context.evaluated_depsgraph_get()
    evaluated = mesh_obj.evaluated_get(depsgraph)
    tmp = evaluated.to_mesh()
    to_world = mesh_obj.matrix_world
    world = [to_world @ v.co for v in tmp.vertices]
    lo = [min(v[k] for v in world) for k in range(3)]
    hi = [max(v[k] for v in world) for k in range(3)]
    evaluated.to_mesh_clear()
    height = (hi[2] - lo[2]) / UNIT
    ortho = a.ortho or 1.9 * height
    # Vertical centre sits three quarters up the body, so the ground, a knockdown and a
    # full jump all fit in one fixed window.
    center = (0.0, (lo[1] + hi[1]) / 2.0, lo[2] + 0.88 * (hi[2] - lo[2]))
    make_camera(scene, ortho * UNIT, center)
    half_h = ortho * UNIT / 2.0
    half_w = half_h * a.width / a.height
    left, right = center[1] + half_w, center[1] - half_w   # image right is world -Y
    bottom = center[2] - half_h
    # Ground: everything below file y = 0 is filled dark, with a bright horizon line, so
    # "on the ground" and "in the air" are unmistakable. Height ticks at 50-unit steps sit
    # on the image's left edge; the thin vertical line marks file z = 0 (the model origin),
    # so forward/back displacement reads against it.
    add_box(scene, "ground", (-0.6, right, bottom), (0.6, left, 0.0), (0.16, 0.17, 0.20, 1))
    add_box(scene, "horizon", (-0.5, right, -0.01), (-0.45, left, 0.01), (0.85, 0.86, 0.90, 1))
    for level in (50, 100, 150, 200, 250):
        if level * UNIT > bottom + half_h * 2:
            continue
        add_box(scene, f"tick{level}", (-0.4, left - half_w * 0.12, level * UNIT - 0.01),
                (-0.35, left, level * UNIT + 0.01), (0.62, 0.64, 0.70, 1))
    add_box(scene, "origin", (-0.3, -0.01, 0.0), (-0.25, 0.01, center[2] + half_h),
            (0.55, 0.57, 0.62, 1))
    print(f"mesh height {height:.1f} file units, ortho {ortho:.1f}, rest bbox world "
          f"x {lo[0]:.2f}..{hi[0]:.2f} y {lo[1]:.2f}..{hi[1]:.2f} z {lo[2]:.2f}..{hi[2]:.2f}")

    armature.animation_data_create()
    os.makedirs(a.out, exist_ok=True)
    only = {int(x) for x in a.only.split(",") if x.strip()} if a.only else None
    base = os.path.splitext(os.path.basename(a.rig))[0]
    entries = []
    for index, motion in enumerate(rig.motions):
        empty = not motion.bindings
        entry = {"take_index": index, "take_name": motion.name,
                 "start": motion.range[0], "end": motion.range[1],
                 "frames": motion.range[1] - motion.range[0] + 1,
                 "empty": empty, "images": []}
        if empty or (only is not None and index not in only):
            entries.append(entry)
            continue
        action, slot, _skipped = G.build_action(motion, rig, rest, armature, names)
        armature.animation_data.action = action
        armature.animation_data.action_slot = slot
        samples = take_frames(motion, a.frames)
        for k, frame in enumerate(samples):
            whole = math.floor(frame)
            scene.frame_set(whole, subframe=frame - whole)
            path = os.path.join(a.out, f"{base}_{index:02d}_{k}.png")
            scene.render.filepath = path
            bpy.ops.render.render(write_still=True)
            entry["images"].append(path)
            entry.setdefault("sample_frames", []).append(frame)
        armature.animation_data.action = None
        entries.append(entry)
        print(f"take {index:2d} {motion.name:16s} frames {entry['frames']:5.0f} "
              f"curves {len(motion.curves):3d} rendered")

    meta = {"rig": a.rig, "mesh": a.mesh, "base": base, "width": a.width, "height": a.height,
            "ortho_file_units": ortho, "camera_center_world": list(center),
            "mesh_height_file_units": height, "samples_per_take": a.frames,
            "engine": a.engine, "takes": entries}
    with open(a.manifest, "w") as f:
        json.dump(meta, f, indent=1)
    print("wrote", a.manifest)


if __name__ == "__main__":
    main()
