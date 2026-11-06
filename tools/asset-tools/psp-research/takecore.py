"""Rig-agnostic motion signatures for the PC (.X) and PSP (.GMO) skeletons.

Both sides are reduced to the same shape:
    local rotation q(t) per bone, sampled at NORMALISED clip time u in [0, 1],
    expressed as a delta from that rig's own bind pose, and (optionally) resolved
    to character space by forward kinematics.

Keeping the delta relative to each rig's own bind pose is what lets a PC set and a
PSP take be compared although the two rest poses differ (PC arms at ~45 deg, PSP T-pose).
"""
import math

# PC bone -> PSP bone. Names on both sides come from the shipped files.
BONE_MAP = [
    ("Bip00_Pelvis", "spine1", 1.0),
    ("Bip01_Spine", "spine2", 1.0),
    ("Bip01_Neck", "neck", 0.6),
    ("Bip01_Head", "head", 0.6),
    ("Bip01_L_Clavicle", "leftcollar", 0.5),
    ("Bip01_L_UpperArm", "leftshoulder", 1.0),
    ("Bip01_L_Forearm", "leftelbow", 1.0),
    ("Bip01_L_Hand", "lefthand", 0.7),
    ("Bip01_R_Clavicle", "rightcollar", 0.5),
    ("Bip01_R_UpperArm", "rightshoulder", 1.0),
    ("Bip01_R_Forearm", "rightelbow", 1.0),
    ("Bip01_R_Hand", "righthand", 0.7),
    ("Bip00_L_Thigh", "lefthip", 1.0),
    ("Bip00_L_Calf", "leftknee", 1.0),
    ("Bip00_L_Foot", "leftfoot", 0.7),
    ("Bip00_R_Thigh", "righthip", 1.0),
    ("Bip00_R_Calf", "rightknee", 1.0),
    ("Bip00_R_Foot", "rightfoot", 0.7),
]

# ---------------------------------------------------------------- quaternions
def qmul(a, b):
    ax, ay, az, aw = a
    bx, by, bz, bw = b
    return (aw * bx + ax * bw + ay * bz - az * by,
            aw * by - ax * bz + ay * bw + az * bx,
            aw * bz + ax * by - ay * bx + az * bw,
            aw * bw - ax * bx - ay * by - az * bz)


def qconj(q):
    return (-q[0], -q[1], -q[2], q[3])


def qnorm(q):
    n = math.sqrt(sum(c * c for c in q)) or 1.0
    return tuple(c / n for c in q)


def qangle(a, b):
    """Geodesic angle between two rotations, radians in [0, pi]."""
    d = abs(sum(x * y for x, y in zip(qnorm(a), qnorm(b))))
    return 2.0 * math.acos(min(1.0, max(-1.0, d)))


def qslerp(a, b, k):
    a, b = qnorm(a), qnorm(b)
    d = sum(x * y for x, y in zip(a, b))
    if d < 0:
        b = tuple(-x for x in b)
        d = -d
    if d > 0.9995:
        return qnorm(tuple(x + (y - x) * k for x, y in zip(a, b)))
    th = math.acos(min(1.0, d))
    s = math.sin(th)
    wa, wb = math.sin((1 - k) * th) / s, math.sin(k * th) / s
    return tuple(x * wa + y * wb for x, y in zip(a, b))


def mat3(m):
    """The 3x3 rotation out of a row-major 4x4 laid out as 16 consecutive floats."""
    return [m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10]]


def quat_from_rowvec(m):
    """Rotation quaternion from a D3D row-vector 3x3 (row major, v' = v*M).

    `m` is a 3x3 as 9 floats; use `mat3` first when it comes from a 4x4.
    """
    r = [[m[0], m[1], m[2]], [m[3], m[4], m[5]], [m[6], m[7], m[8]]]
    # transpose to the column-vector convention used by quat_from_matrix
    t = [[r[j][i] for j in range(3)] for i in range(3)]
    tr = t[0][0] + t[1][1] + t[2][2]
    if tr > 0:
        s = math.sqrt(tr + 1.0) * 2
        return qnorm(((t[2][1] - t[1][2]) / s, (t[0][2] - t[2][0]) / s,
                      (t[1][0] - t[0][1]) / s, 0.25 * s))
    if t[0][0] > t[1][1] and t[0][0] > t[2][2]:
        s = math.sqrt(1.0 + t[0][0] - t[1][1] - t[2][2]) * 2
        return qnorm((0.25 * s, (t[0][1] + t[1][0]) / s, (t[0][2] + t[2][0]) / s,
                      (t[2][1] - t[1][2]) / s))
    if t[1][1] > t[2][2]:
        s = math.sqrt(1.0 + t[1][1] - t[0][0] - t[2][2]) * 2
        return qnorm(((t[0][1] + t[1][0]) / s, 0.25 * s, (t[1][2] + t[2][1]) / s,
                      (t[0][2] - t[2][0]) / s))
    s = math.sqrt(1.0 + t[2][2] - t[0][0] - t[1][1]) * 2
    return qnorm(((t[0][2] + t[2][0]) / s, (t[1][2] + t[2][1]) / s, 0.25 * s,
                  (t[1][0] - t[0][1]) / s))


# ------------------------------------------------------------------- rig side
class Rig:
    """A skeleton plus a set of clips, reduced to delta rotation samples.

    bones: {name: (parent name, rest local quaternion)}
    clips: [{'name', 'index', 'duration_frames', 'tracks': {bone: [(t, quat)]}}]
    """
    def __init__(self, bones, clips, source=""):
        self.bones = bones
        self.clips = clips
        self.source = source
        self._glob = {}

    def local_at(self, clip, bone, u):
        tr = clip["tracks"].get(bone)
        if not tr:
            return self.bones[bone][1]
        dur = clip["duration"]
        t = u * dur
        if t <= tr[0][0]:
            return tr[0][1]
        for (t0, q0), (t1, q1) in zip(tr, tr[1:]):
            if t < t1:
                k = 0.0 if t1 <= t0 else (t - t0) / (t1 - t0)
                return qslerp(q0, q1, k)
        return tr[-1][1]

    def global_rest(self, bone):
        key = ("rest", bone)
        if key in self._glob:
            return self._glob[key]
        parent, rest = self.bones[bone][0], self.bones[bone][1]
        q = self.global_rest(parent) if parent in self.bones else (0, 0, 0, 1)
        self._glob[key] = qmul(q, rest)
        return self._glob[key]

    def global_at(self, clip, bone, u):
        parent = self.bones[bone][0]
        q = self.global_at(clip, parent, u) if parent in self.bones else (0, 0, 0, 1)
        return qmul(q, self.local_at(clip, bone, u))

    def local_t_at(self, clip, bone, u):
        tr = clip.get("ttracks", {}).get(bone)
        rest = self.bones[bone][2]
        if not tr:
            return rest
        dur = clip["duration"]
        t = u * dur
        if t <= tr[0][0]:
            return tr[0][1]
        for (t0, p0), (t1, p1) in zip(tr, tr[1:]):
            if t < t1:
                k = 0.0 if t1 <= t0 else (t - t0) / (t1 - t0)
                return tuple(a + (b - a) * k for a, b in zip(p0, p1))
        return tr[-1][1]

    def pos_at(self, clip, bone, u):
        """Global (character space) position of the bone origin."""
        q = self.local_at(clip, bone, u)
        t = self.local_t_at(clip, bone, u)
        parent = self.bones[bone][0]
        if parent not in self.bones:
            return t
        pq = self.global_at(clip, parent, u)
        pp = self.pos_at(clip, parent, u)
        r = qrot(pq, t)
        return (pp[0] + r[0], pp[1] + r[1], pp[2] + r[2])

    def body_frame(self, clip, u, side):
        role = BODY_BONES[side]
        hip = self.pos_at(clip, role["root"], u)
        hl = self.pos_at(clip, role["hip_l"], u)
        hr = self.pos_at(clip, role["hip_r"], u)
        up = self.pos_at(clip, role["up"], u)
        ex = _norm(_vec_sub(hr, hl))
        ey = _norm(_vec_sub(up, hip))
        ez = _norm(_cross(ex, ey))
        ey = _norm(_cross(ez, ex))
        span = math.sqrt(_dot(_vec_sub(up, hip), _vec_sub(up, hip))) or 1.0
        return hip, (ex, ey, ez), span

    def pos_signature(self, clip, samples, side, bones=None):
        """Joint positions in the body frame, scaled by hips->neck, per (bone, u)."""
        feats = []
        for u_i in range(samples):
            u = u_i / (samples - 1)
            hip, (ex, ey, ez), span = self.body_frame(clip, u, side)
            for pc_bone, psp_bone, weight in (bones or BONE_MAP):
                bone = pc_bone if side == "pc" else psp_bone
                if bone not in self.bones:
                    continue
                d = _vec_sub(self.pos_at(clip, bone, u), hip)
                feats.append((pc_bone, u, weight,
                              (_dot(d, ex) / span, _dot(d, ey) / span, _dot(d, ez) / span)))
        return feats

    def angle_signature(self, clip, samples, side):
        """Joint-angle trajectory: flexion at knee/elbow/etc. from global positions only.

        Angles between limb segments are independent of bone roll, rest pose and body
        scale, so a PC set and a PSP take remain comparable although the rigs disagree
        on all three.
        """
        role = JOINTS[side]
        names = [role[k] for k in ANGLE_JOINTS]
        present = [n in self.bones for n in names]
        out = []
        for ui in range(samples):
            u = ui / (samples - 1)
            p = {}
            for key in ANGLE_JOINTS:
                b = role[key]
                p[key] = self.pos_at(clip, b, u) if b in self.bones else None
            for name, weight in ANGLES:
                tags = ("l", "r") if "$" in name[0] + name[1] + name[2] else (None,)
                for side_tag in tags:
                    keys = [k if side_tag is None else k.replace("$", side_tag) for k in name]
                    if any(p.get(k) is None for k in keys):
                        continue
                    v = _joint_angle(p, keys)
                    label = keys[1]
                    out.append((label, u, weight, v))
        return out

    def signature(self, clip, mode, samples, bones=None):
        """Flat feature vector: list of (bone, u, value)."""
        out = []
        for pc_bone, psp_bone, weight in (bones or BONE_MAP):
            bone = pc_bone if pc_bone in self.bones else psp_bone
            if bone not in self.bones:
                continue
            for i in range(samples):
                u = i / (samples - 1)
                if mode == "local":
                    d = qmul(qconj(self.bones[bone][1]), self.local_at(clip, bone, u))
                elif mode == "var":
                    # rotation magnitude since the clip's own first sample: invariant to a
                    # constant per-bone basis change (bone roll) on either rig
                    q0 = self.local_at(clip, bone, 0.0)
                    q1 = self.local_at(clip, bone, u)
                    d = qmul(q1, qconj(q0))
                    out.append((pc_bone, u, weight, qangle(d, (0, 0, 0, 1)) / math.pi))
                    continue
                elif mode == "global":
                    d = qmul(self.global_at(clip, bone, u), qconj(self.global_rest(bone)))
                else:  # "angle": rotation magnitude only, axis/orientation invariant
                    d = qmul(qconj(self.bones[bone][1]), self.local_at(clip, bone, u))
                    out.append((pc_bone, u, weight, qangle(d, (0, 0, 0, 1)) / math.pi))
                    continue
                out.append((pc_bone, u, weight, d))
        return out


def distance(sig_a, sig_b, samples):
    """Weighted mean feature distance between two signatures of equal shape."""
    tot = wsum = 0.0
    for (bone, u, w, va), (_, _, _, vb) in zip(sig_a, sig_b):
        if isinstance(va, float):
            d = abs(va - vb)          # angle mode: feature already in [0,1]
        else:
            d = qangle(va, vb) / math.pi
        tot += w * d
        wsum += w
    return tot / wsum if wsum else 1.0


# ------------------------------------------------------------------- loaders
def load_pc(path):
    import xanim
    roots = xanim.parse(open(path, "rb").read())
    frames = xanim.frame_table(roots)
    bones = {}
    for name, (parent, m) in frames.items():
        if not name or m is None:
            continue
        bones[name] = (parent, quat_from_rowvec(mat3(m)), (0.0, 0.0, 0.0))
    if "Bip00" not in bones:
        bones["Bip00"] = (None, (0, 0, 0, 1), (0.0, 0.0, 0.0))
    file_sets = xanim.animation_sets(roots)
    n = len(file_sets)
    clips = []
    for ctrl in range(n):
        s = file_sets[n - 1 - ctrl]      # the loader stores the array reversed
        tracks, ttracks = {}, {}
        first = last = None
        for bone, keys in s["tracks"].items():
            if bone not in bones:
                continue
            ks, ts = [], []
            for t, m in keys:
                ks.append((float(t), quat_from_rowvec(mat3(m))))
                ts.append((float(t), (m[12], m[13], m[14])))
            tracks[bone] = ks
            ttracks[bone] = ts
            lo, hi = ks[0][0], ks[-1][0]
            first = lo if first is None else min(first, lo)
            last = hi if last is None else max(last, hi)
        dur = max(1e-6, (last or 0) - (first or 0))
        for bone in tracks:
            base = tracks[bone][0][0]
            tracks[bone] = [(t - (first or 0), q) for t, q in tracks[bone]]
        clips.append({"name": "set %d (%s)" % (ctrl, s["name"]), "index": ctrl,
                      "ticks": (last or 0) - (first or 0), "tracks": tracks,
                      "ttracks": ttracks,
                      "keys": [len(v) for v in tracks.values()][:1], "duration": dur,
                      "frames": ((last or 0) - (first or 0)) / 76.8})
    return Rig(bones, clips, source=path)


def psp_bones(data):
    """[(name, parent index, rest quaternion)] straight from the GMO bone chunks.

    `gmo.py` wraps the transform in stubbed mathutils objects, so the numbers are read
    here directly: 0x8041 parent, 0x8048 translate, 0x804b quaternion.
    """
    import struct
    import gmo
    walk, chunk_name = gmo.MOD.walk, gmo.MOD.chunk_name
    out = []

    def descend(start, end):
        for kind, header, size, at in walk(data, start, end):
            if kind == 4:
                name = chunk_name(data, at, header)
                parent, quat, trans = -1, (0.0, 0.0, 0.0, 1.0), (0.0, 0.0, 0.0)
                for k3, h3, s3, a3 in walk(data, at + header, at + size):
                    if k3 == 0x8041:
                        parent = struct.unpack_from("<I", data, a3 + 8)[0] & 0xfff
                    elif k3 == 0x804b:
                        x, y, z, w = struct.unpack_from("<4f", data, a3 + 8)
                        quat = qnorm((x, y, z, w))
                    elif k3 == 0x8048:
                        trans = struct.unpack_from("<3f", data, a3 + 8)
                out.append((name, parent, quat, trans))
                descend(at + header, at + size)
            elif kind in (2, 3, 5, 8, 9, 10):
                descend(at + header, at + size)
    descend(0x10, len(data))
    return out


def load_psp(path):
    import gmo
    data = open(path, "rb").read()
    model = gmo.MOD.parse_gmo(data)
    bones = {}
    bonelist = psp_bones(data)
    for i, (name, parent, quat, trans) in enumerate(bonelist):
        bones[name] = (bonelist[parent][0] if 0 <= parent < len(bonelist) else None, quat, trans)
    clips = []
    for i, m in enumerate(model.motions):
        tracks, ttracks = {}, {}
        for bone_idx, target, curve_idx in m.bindings:
            if bone_idx >= len(model.bones):
                continue
            name = model.bones[bone_idx].name
            c = m.curves[curve_idx]
            if target == gmo.MOD.TARGET_ROTATE:
                ks = [(float(t), qnorm((v[0], v[1], v[2], v[3]))) for t, v in c.keys]
                if ks:
                    tracks[name] = ks
            elif target == gmo.MOD.TARGET_TRANSLATE:
                ttracks[name] = [(float(t), tuple(v[:3])) for t, v in c.keys]
        dur = max(1e-6, m.range[1] - m.range[0])
        clips.append({"name": m.name, "index": i, "duration": dur,
                      "frames": dur, "tracks": tracks, "ttracks": ttracks})
    return Rig(bones, clips, source=path)


# ------------------------------------------------- joint-position signatures
# Bone-roll and rest-pose differ between the PC and PSP rigs, and a bone's local
# rotation axis is an authoring choice. A joint's position does not depend on either,
# so the position trajectory, expressed in a frame built from the hips, is the
# comparable quantity. Left/right thigh joints give the body frame's X axis and
# hips->neck its Y: both rigs have them.

BODY_BONES = {          # rig bone for each role, per side
    "pc": {"hip_l": "Bip00_L_Thigh", "hip_r": "Bip00_R_Thigh",
           "root": "Bip00_Pelvis", "up": "Bip01_Neck"},
    "psp": {"hip_l": "lefthip", "hip_r": "righthip",
            "root": "spine1", "up": "neck"},
}


def _vec_sub(a, b):
    return (a[0] - b[0], a[1] - b[1], a[2] - b[2])


def _cross(a, b):
    return (a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2], a[0] * b[1] - a[1] * b[0])


def _dot(a, b):
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2]


def _norm(a):
    n = math.sqrt(_dot(a, a)) or 1.0
    return (a[0] / n, a[1] / n, a[2] / n)


def qrot(q, v):
    x, y, z, w = q
    qv = (x, y, z)
    t = _cross(qv, v)
    t = (2 * t[0], 2 * t[1], 2 * t[2])
    c = _cross(qv, t)
    return (v[0] + w * t[0] + c[0], v[1] + w * t[1] + c[1], v[2] + w * t[2] + c[2])


JOINTS = {
    "pc": {"thigh_l": "Bip00_L_Thigh", "calf_l": "Bip00_L_Calf", "foot_l": "Bip00_L_Foot",
           "toe_l": "Bip00_L_Toe0", "clav_l": "Bip01_L_Clavicle", "arm_l": "Bip01_L_UpperArm",
           "fore_l": "Bip01_L_Forearm", "hand_l": "Bip01_L_Hand",
           "thigh_r": "Bip00_R_Thigh", "calf_r": "Bip00_R_Calf", "foot_r": "Bip00_R_Foot",
           "toe_r": "Bip00_R_Toe0", "clav_r": "Bip01_R_Clavicle", "arm_r": "Bip01_R_UpperArm",
           "fore_r": "Bip01_R_Forearm", "hand_r": "Bip01_R_Hand",
           "neck": "Bip01_Neck", "head": "Bip01_Head", "pelvis": "Bip00_Pelvis",
           "spine": "Bip01_Spine"},
    "psp": {"thigh_l": "lefthip", "calf_l": "leftknee", "foot_l": "leftfoot",
            "toe_l": "lefttoe1", "clav_l": "leftcollar", "arm_l": "leftshoulder",
            "fore_l": "leftelbow", "hand_l": "lefthand",
            "thigh_r": "righthip", "calf_r": "rightknee", "foot_r": "rightfoot",
            "toe_r": "righttoe1", "clav_r": "rightcollar", "arm_r": "rightshoulder",
            "fore_r": "rightelbow", "hand_r": "righthand",
            "neck": "neck", "head": "head", "pelvis": "spine1",
            "spine": "spine2"},
}
ANGLE_JOINTS = sorted(JOINTS["pc"])

# (three joint keys whose middle one is the vertex, weight)
ANGLES = [
    (("thigh_$", "calf_$", "foot_$"), 1.0),      # knee flexion
    (("foot_$", "toe_$", "calf_$"), 0.7),        # ankle flexion
    (("neck", "thigh_$", "calf_$"), 1.0),        # hip flexion vs torso
    (("arm_$", "fore_$", "hand_$"), 1.0),        # elbow flexion
    (("pelvis", "arm_$", "fore_$"), 1.0),        # shoulder vs torso
    (("clav_$", "thigh_$", "calf_$"), 0.8),      # arm-to-leg opposition
    (("pelvis", "neck", "head"), 0.5),           # neck bend
]


def _joint_angle(p, keys):
    """Angle at p[keys[1]] between p[keys[0]] and p[keys[2]]."""
    a, b, c = p[keys[0]], p[keys[1]], p[keys[2]]
    u = _vec_sub(a, b)
    v = _vec_sub(c, b)
    nu, nv = math.sqrt(_dot(u, u)), math.sqrt(_dot(v, v))
    if nu < 1e-9 or nv < 1e-9:
        return 0.0
    cosv = max(-1.0, min(1.0, _dot(u, v) / (nu * nv)))
    return math.acos(cosv) / math.pi


# ------------------------------------------------------------- shape metric
def shape(sig):
    """Feature vector with each feature's own time-mean removed, plus its amplitude.

    Removing the mean cancels the constant joint-angle offsets the two rigs disagree on
    (a PC arm hangs at another angle than a PSP arm); the amplitude is kept separately
    because it says how much the clip moves at all.
    """
    by = {}
    for b, u, w, v in sig:
        by.setdefault(b, []).append(v)
    mean = {b: sum(v) / len(v) for b, v in by.items()}
    centred = [(b, u, w, v - mean[b]) for b, u, w, v in sig]
    rms = math.sqrt(sum(w * (v - mean[b]) ** 2 for b, u, w, v in sig) /
                    (sum(w for b, u, w, v in sig) or 1.0))
    return centred, rms


def shape_score(sa, sb):
    """(correlation of the centred shapes, amplitude ratio, number of active features)."""
    (ca, ra), (cb, rb) = shape(sa), shape(sb)
    num = suma = sumb = 0.0
    for (_, _, w, va), (_, _, _, vb) in zip(ca, cb):
        num += w * va * vb
        suma += w * va * va
        sumb += w * vb * vb
    corr = num / math.sqrt(suma * sumb) if suma > 1e-12 and sumb > 1e-12 else 0.0
    ratio = rb / ra if ra > 1e-9 else (0.0 if rb < 1e-9 else 99.0)
    return corr, ratio, ra, rb
