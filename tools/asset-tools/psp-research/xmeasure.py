"""Mean normal direction per mesh, grouped by material texture, for a binary .X."""
import sys
sys.path.insert(0, '.')
from xdump import tokens

d = open(sys.argv[1], 'rb').read()
toks = list(tokens(d))
i = 0
n = len(toks)
in_tpl = False
depth = 0
# object stack of dicts
stack = []
out = []

def emit(depth):
    pass

while i < n:
    kind, val = toks[i]
    if kind == 31 and depth == 0:
        in_tpl = True; i += 1; continue
    if in_tpl:
        if kind == 10: depth += 1
        elif kind == 11:
            depth -= 1
            if depth == 0: in_tpl = False
        i += 1; continue
    if kind == 1 and i + 1 < n and toks[i+1][0] in (10, 1):
        name = val.decode('ascii', 'replace'); i += 1
        inst = ''
        if toks[i][0] == 1:
            inst = toks[i][1].decode('ascii', 'replace'); i += 1
        stack.append({'type': name, 'name': inst, 'values': [], 'children': []})
        if len(stack) > 1:
            stack[-2]['children'].append(stack[-1])
        else:
            out.append(stack[-1])
        i += 1   # OBRACE
        depth += 1
        continue
    if kind == 11:
        if stack: stack.pop()
        depth -= 1; i += 1; continue
    if kind in (2, 3, 6, 7) and stack:
        stack[-1]['values'].append((kind, val))
        i += 1; continue
    i += 1

def numbers(obj):
    ints, floats = [], []
    for kind, val in obj['values']:
        if kind == 6: ints.extend(val)
        elif kind == 7: floats.extend(val)
        elif kind == 3: ints.append(val)
    return ints, floats

def children(obj, type_name):
    return [c for c in obj['children'] if c['type'] == type_name]

def walk_frames(obj, parent_world=None):
    for c in obj['children']:
        if c['type'] == 'Frame':
            yield c
            yield from walk_frames(c)

for mesh in [o for o in walk_frames_all(out)] if False else []:
    pass

meshes = []
def collect(obj):
    for c in obj['children']:
        if c['type'] == 'Mesh': meshes.append(c)
        collect(c)

for root in out:
    if root['type'] == 'Frame':
        collect(root)
    elif root['type'] == 'Mesh':
        meshes.append(root)

for mesh in meshes:
    ints, floats = numbers(mesh)
    nv = ints[0]
    pos = floats[:nv * 3]
    rest = floats[nv * 3:]
    texture = ''
    for ml in children(mesh, 'MeshMaterialList'):
        for mat in children(ml, 'Material'):
            for tf in children(mat, 'TextureFilename'):
                for kind, val in tf['values']:
                    if kind == 2: texture = val
    for mn in children(mesh, 'MeshNormals'):
        ni, nf = numbers(mn)
        count = ni[0]
        normals = nf[:count * 3]
        nz = sum(normals[2::3]) / count
        ny = sum(normals[1::3]) / count
        zc = sum(pos[2::3]) / nv
        print('%-22r n=%5d  mean pos z %+7.1f  mean normal z %+7.2f  y %+7.2f' % (texture, nv, zc, nz, ny))
