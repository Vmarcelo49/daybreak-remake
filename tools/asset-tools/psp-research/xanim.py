"""Minimal binary .X object-tree reader + animation extraction (PC install models).

Reuses the tokenizer in `xdump.py` (the shipped files are "xof 0303bin"). Builds the
nested object tree so `AnimationSet` and `Frame` subtrees can be read without the
product's C++ reader. Key times are D3DX animation ticks; `AnimTicksPerSecond` (when
present) gives the rate, and the shipped models key one frame at 80 ticks.

    root   = xanim.parse(open(path, 'rb').read())
    frames = xanim.frame_table(root)      # {bone: (parent, local 16 floats)}
    sets   = xanim.animation_sets(root)   # [{'name','tracks':{bone:[(t, 16 floats)]}}]
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from xdump import tokens  # noqa: E402


class Obj:
    __slots__ = ("type", "name", "values", "children", "inline")

    def __init__(self, type_, name=""):
        self.type = type_
        self.name = name
        self.values = []
        self.children = []
        self.inline = []

    def __repr__(self):
        return "Obj(%s,%r,%d children)" % (self.type, self.name, len(self.children))


def _text(v):
    if isinstance(v, bytes):
        return v.split(b"\0", 1)[0].decode("cp932", "replace")
    return str(v)


def parse(data):
    toks = list(tokens(data))
    i, n = 0, len(toks)
    depth = 0
    in_template = False
    roots, stack = [], []
    while i < n:
        kind, val = toks[i]
        if kind == 31 and depth == 0 and not in_template:
            in_template = True
            i += 1
            continue
        if in_template:
            if kind == 10:
                depth += 1
            elif kind == 11:
                depth -= 1
                if depth <= 0:
                    depth = 0
                    in_template = False
            i += 1
            continue
        if kind == 1:
            nk = toks[i + 1][0] if i + 1 < n else None
            if nk == 1 and i + 2 < n and toks[i + 2][0] == 10:
                obj, i = Obj(_text(val), _text(toks[i + 1][1])), i + 3
            elif nk == 10:
                obj, i = Obj(_text(val)), i + 2
            else:
                if stack:
                    stack[-1].inline.append(_text(val))
                i += 1
                continue
            (stack[-1].children if stack else roots).append(obj)
            stack.append(obj)
            continue
        if kind == 10:  # bare braces: an object with no type (a bone reference)
            obj = Obj("")
            (stack[-1].children if stack else roots).append(obj)
            stack.append(obj)
            i += 1
            continue
        if kind == 11:
            if stack:
                stack.pop()
            i += 1
            continue
        if stack:
            stack[-1].values.append((kind, val))
        i += 1
    return roots


def frame_table(roots):
    """{bone: (parent name, local matrix as 16 floats)} from the Frame hierarchy."""
    out, parents = {}, {}

    def walk(obj, parent):
        for ch in obj.children:
            if ch.type == "Frame":
                parents[ch.name] = parent
                walk(ch, ch.name)

    def collect(obj):
        for ch in obj.children:
            if ch.type == "Frame":
                mat = None
                for f in ch.children:
                    if f.type == "FrameTransformMatrix":
                        mat = [float(x) for _, v in f.values if _ == 7 for x in v][:16]
                out[ch.name] = (parents.get(ch.name), mat)
                collect(ch)

    for r in roots:
        if r.type == "Frame":
            parents[r.name] = None
            walk(r, r.name)
            collect(r)
    return out


def animation_sets(roots):
    return [_as(r) for r in roots if r.type == "AnimationSet"]


def ticks_per_second(roots):
    for r in roots:
        if r.type == "AnimTicksPerSecond":
            ints = [v for k, v in r.values if k == 3]
            if ints:
                return int(ints[0])
    return None


def _as(obj):
    tracks = {}
    for anim in obj.children:
        if anim.type != "Animation":
            continue
        bone = None
        keys = []
        for ch in anim.children:
            if ch.type == "AnimationKey":
                ints = [v for k, v in ch.values if k == 3]
                lists = [v for k, v in ch.values if k == 7]
                times = [v[0] for k, v in ch.values if k == 6][1:]
                for t, L in zip(times, lists):
                    row = [float(x) for x in L]
                    keys.append((int(t), row))
            elif ch.inline:
                bone = ch.inline[0]
            elif ch.name:
                bone = ch.name
        if bone and keys:
            tracks[bone] = keys
    return {"name": obj.name, "tracks": tracks}


def main():
    path = sys.argv[1]
    roots = parse(open(path, "rb").read())
    sets = animation_sets(roots)
    frames = frame_table(roots)
    print("%s: %d AnimationSet, %d frames, ticks/s %s"
          % (path, len(sets), len(frames), ticks_per_second(roots)))
    print("frames:", ", ".join(sorted(frames)))
    for s in sets[:3] + sets[-2:]:
        t0 = sorted(s["tracks"])[:4]
        print("set %-10s tracks=%-3d keys=%s %s"
              % (s["name"], len(s["tracks"]),
                 sorted({len(k) for k in s["tracks"].values()}), t0))


if __name__ == "__main__":
    main()
