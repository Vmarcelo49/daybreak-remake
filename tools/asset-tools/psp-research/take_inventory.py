"""Every motion take of a PSP character rig: frame count and root motion, numerically.

    python3 take_inventory.py chrm17 chrm18 chrm19 chrm02 > <out>.tsv

File axes, measured on the rigs rather than assumed: +Y is up (the root sits at y~78,
hip height), +Z is the model's forward (the toe bone lies at +Z of the foot bone) and +X
is the character's left (lefthand is at +X, righthand at -X). The bone that carries the
character through space is `root` (child of `skelton`); `RootNode` is the object node and
has no curves.

Per take, for the root translation curve:

  dx dy dz   last key minus first key, in file units -- the take's net displacement
  px py pz   peak-to-peak excursion over the take -- how far it actually moved
  path_fwd   arc length of the horizontal (XZ) path, so an in-place cycle reads 0
  path_up    arc length of the vertical (Y) path
  z0 y0      the root's position at the take's first key

A take whose net displacement is zero but whose excursion is not is a cycle that returns
to its start (in-place walk/run, a bob, a crouch). One with a large net displacement
carries the character somewhere (a dash, a fall, a knockback).
"""
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import gmo  # noqa: E402

DUMP = os.path.normpath(os.path.join(HERE, "..", "dump", "g3d"))
TARGET_TRANSLATE = gmo.MOD.TARGET_TRANSLATE


def sample(curve, frame):
    keys = curve.keys
    if frame <= keys[0][0]:
        return keys[0][1]
    for (t0, v0), (t1, v1) in zip(keys, keys[1:]):
        if frame < t1:
            if curve.mode == 0 or t1 <= t0:
                return v0
            k = (frame - t0) / (t1 - t0)
            return tuple(a + (b - a) * k for a, b in zip(v0, v1))
    return keys[-1][1]


def motion_root(model):
    """`root` by name; otherwise the first bone that a take actually translates."""
    named = [i for i, b in enumerate(model.bones) if b.name == "root"]
    if named:
        return named[0]
    for m in model.motions:
        for b, t, _c in m.bindings:
            if t == TARGET_TRANSLATE:
                return b
    return None


def take_rows(model):
    root = motion_root(model)
    rows = []
    for i, m in enumerate(model.motions):
        start, end = m.range
        translate = {b: m.curves[c] for b, t, c in m.bindings if t == TARGET_TRANSLATE}
        rows.append(dict(index=i, name=m.name, start=start, end=end,
                         frames=end - start + 1, curves=len(m.curves),
                         bindings=len(m.bindings), rot_bones=sum(
                             1 for b, t, c in m.bindings if t != TARGET_TRANSLATE),
                         translate_bones=sorted(model.bones[b].name for b in translate),
                         root_curve=translate.get(root)))
    for r in rows:
        c = r.pop("root_curve")
        r.update(dx=0.0, dy=0.0, dz=0.0, px=0.0, py=0.0, pz=0.0,
                 path_fwd=0.0, path_up=0.0, z0=0.0, y0=0.0, keys=0)
        if c is None or not c.keys:
            continue
        r["keys"] = len(c.keys)
        start, end = r["start"], r["end"]
        first = sample(c, start)
        last = sample(c, end)
        r["dx"], r["dy"], r["dz"] = (last[k] - first[k] for k in range(3))
        r["z0"], r["y0"] = first[2], first[1]
        steps = 48
        path = [sample(c, start + (end - start) * j / steps) for j in range(steps + 1)]
        r["px"] = max(p[0] for p in path) - min(p[0] for p in path)
        r["py"] = max(p[1] for p in path) - min(p[1] for p in path)
        r["pz"] = max(p[2] for p in path) - min(p[2] for p in path)
        r["path_fwd"] = sum(((b[0] - a[0]) ** 2 + (b[2] - a[2]) ** 2) ** 0.5
                            for a, b in zip(path, path[1:]))
        r["path_up"] = sum(abs(b[1] - a[1]) for a, b in zip(path, path[1:]))
        # Keys directly, not the resampled path, for the true extremes of the curve.
        values = [k[1] for k in c.keys]
        r["px"] = max(r["px"], max(v[0] for v in values) - min(v[0] for v in values))
        r["py"] = max(r["py"], max(v[1] for v in values) - min(v[1] for v in values))
        r["pz"] = max(r["pz"], max(v[2] for v in values) - min(v[2] for v in values))
    return rows, root


HEADER = ("rig\ttake_index\ttake_name\tstart\tend\tframes\tcurves\trot_bones\tdx\tdy\tdz\t"
          "px\tpy\tpz\tpath_fwd\tpath_up\tz0\ty0\troot_keys\ttranslate_bones")


def main():
    names = sys.argv[1:] or ["chrm17"]
    print(HEADER)
    for name in names:
        model = gmo.parse_gmo(open(os.path.join(DUMP, name + ".gmo"), "rb").read())
        rows, root = take_rows(model)
        print(f"# {name}: bones {len(model.bones)} motions {len(model.motions)} "
              f"root {model.bones[root].name if root is not None else None}", file=sys.stderr)
        for r in rows:
            print("%s\t%d\t%s\t%.1f\t%.1f\t%.0f\t%d\t%d\t%.4f\t%.4f\t%.4f\t%.3f\t%.3f\t%.3f\t"
                  "%.3f\t%.3f\t%.2f\t%.2f\t%d\t%s" % (
                      name, r["index"], r["name"], r["start"], r["end"], r["frames"],
                      r["curves"], r["rot_bones"], r["dx"], r["dy"], r["dz"],
                      r["px"], r["py"], r["pz"], r["path_fwd"], r["path_up"],
                      r["z0"], r["y0"], r["keys"], ",".join(r["translate_bones"])))


if __name__ == "__main__":
    main()
