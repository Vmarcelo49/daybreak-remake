"""Print the top-level token sequence of the first few Mesh objects in a binary .X."""
import sys
sys.path.insert(0, '.')
from xdump import tokens, NAMES

d = open(sys.argv[1], 'rb').read()
toks = list(tokens(d))
depth = 0
in_tpl = False
shown = 0
want = int(sys.argv[2]) if len(sys.argv) > 2 else 2
i = 0
inside = None
while i < len(toks):
    kind, val = toks[i]
    if kind == 31 and depth == 0:
        in_tpl = True; i += 1; continue
    if in_tpl:
        if kind == 10: depth += 1
        elif kind == 11:
            depth -= 1
            if depth == 0: in_tpl = False
        i += 1; continue
    if kind == 1 and i + 1 < len(toks) and toks[i+1][0] == 10:
        name = val.decode('ascii', 'replace')
        if name in ('Mesh', 'AnimationKey', 'SkinWeights', 'MeshNormals', 'Animation',
                    'AnimationSet', 'Material', 'TextureFilename', 'AnimTicksPerSecond'):
            shown += 1
            if shown <= want or name != 'Mesh':
                print('\n== %s (depth %d)' % (name, depth))
                inside = depth + 1
            else:
                inside = None
        else:
            inside = None
        i += 2
        depth += 1
        continue
    if kind == 10:
        depth += 1; i += 1; continue
    if kind == 11:
        depth -= 1
        if inside is not None and depth < inside: inside = None
        i += 1; continue
    if inside is not None and depth == inside:
        line = NAMES.get(kind, str(kind))
        if isinstance(val, bytes):
            line += ' ' + repr(val[:24])
        elif isinstance(val, tuple):
            line += ' n=%d %s' % (len(val), str(val[:6]))
        else:
            line += ' ' + str(val)
        print('   ', line)
    i += 1
