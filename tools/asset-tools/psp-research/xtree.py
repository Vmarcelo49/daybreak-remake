"""Print the Frame hierarchy (names only) of a binary .X, to compare rigs."""
import struct, sys
sys.path.insert(0, '.')
from xdump import tokens, NAMES

def parse(d):
    toks = list(tokens(d))
    i = 0
    in_tpl = False
    depth = 0
    out = []
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
        out.append((kind, val)); i += 1
    return out

def main():
    d = open(sys.argv[1], 'rb').read()
    toks = parse(d)
    i = 0
    n = len(toks)
    names = []
    def walk(depth):
        nonlocal i
        while i < n:
            kind, val = toks[i]
            if kind == 11:
                i += 1; return
            if kind == 10:
                i += 1; walk(depth + 1); continue
            if kind == 1 and i + 1 < n and toks[i+1][0] in (10, 1):
                tname = val.decode('ascii', 'replace')
                i += 1
                inst = ''
                if toks[i][0] == 1:
                    inst = toks[i][1].decode('ascii', 'replace'); i += 1
                names.append((tname, inst))
                depth_hint = None
                continue
            i += 1
    walk(0)
    types = [t for t, _ in names]
    print('objects:', len(names), 'frame-ish:', types.count('Frame'))
    for t, inst in names:
        if t == 'Frame' and inst:
            print(inst)

main()
