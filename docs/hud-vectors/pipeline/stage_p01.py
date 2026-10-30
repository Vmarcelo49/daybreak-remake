import numpy as np
from polish import *
a = load('hud/P01.png'); H, W = a.shape[:2]
PARAMS = dict(ds=6, ss=2.4, cw=3, cs=1.2, co=0.8)

# 1) barras de gradiente (coluna da direita, x>=316)
lab, comps = components(a[..., 3] > 8)
grads = [c for c in comps if c[1] >= 316 and c[4] <= 13 and c[3] >= 80]
gdefs, gshapes, erase, errs = gradient_objects(a, lab, grads, 'pg', nst=8)
print('barras de gradiente:', len(grads), 'erro rms:', [round(e, 1) for e in errs])

# 2) barras creme com glow
bars = find_cream_shapes(a)
print('barras creme:', [b[1] for b in bars])
white = (a[..., 3] > 200) & (a[..., :3].min(-1) > 200)       # texto branco dos rótulos
keep = ndi.binary_dilation(white, iterations=3)
under, cdefs = [], []
for k, (filled, bbox, ring) in enumerate(bars):
    if bbox[3] < 40:   # barras retangulares: usa o retângulo da linha creme (+1px nas pontas, onde a linha é fraca)
        ys, xs = np.nonzero(ring)
        filled = np.zeros_like(filled)
        filled[ys.min():ys.max() + 1, xs.min() - 1:xs.max() + 2] = True
    P = mask_path(filled, bbox, blur=0.45, alphamax=0.9)
    under.append(bar_group(P, f'bar{k}', **PARAMS))
    zone = ndi.binary_dilation(filled, iterations=26)
    erase |= zone & ~keep
under_svg = ''.join(under)

svg = assemble(W, H, gdefs, under_svg + ''.join(gshapes), vtrace(a, erase))
open('all/p01_new.svg', 'w').write(svg)
print('KB', len(svg) // 1024)
