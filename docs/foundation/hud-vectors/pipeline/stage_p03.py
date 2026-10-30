import numpy as np, itertools
from polish import *
a = load('hud/p03.png'); H, W = a.shape[:2]
R, G, B, A = [a[..., k].astype(int) for k in range(4)]
reg = np.zeros(A.shape, bool); reg[125:260, 280:512] = True
whiteglow = (R > 235) & (G > 235) & (B > 235) & (A > 5) & reg
core = (A > 200) & ~whiteglow & reg & ((R + G + B) < 600)
core_d = ndi.binary_dilation(core, iterations=1)
Af = A / 255.0
# silhueta do núcleo (contorno preto + azul) -> forma do halo
dt = ndi.distance_transform_edt(~core)
def halo(k, sig, op):
    m = (dt <= k).astype(float)
    d = mask_path(m, None, blur=0.7, alphamax=1.1)
    return (f'<filter id="hg" x="-30%" y="-30%" width="160%" height="160%" color-interpolation-filters="sRGB"><feGaussianBlur stdDeviation="{sig}"/></filter>'
            f'<path d="{d}" fill="#fff" opacity="{op}" filter="url(#hg)"/>')
cmp_mask = reg & ~core_d
best = None
for k, sig, op in itertools.product([0, 1, 2, 3, 4], [2, 3, 4, 5], [.7, .8, .9, 1.0]):
    g = halo(k, sig, op)
    im = np.array(render(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}">{g}</svg>', width=W)).astype(float)
    e = np.abs(im[..., 3] / 255 - Af)[cmp_mask].mean()
    if best is None or e < best[0]: best = (e, k, sig, op)
print('halo melhor (erro alpha, k, sigma, opacidade):', best)
g = halo(*best[1:])
erase = whiteglow
svg = assemble(W, H, [], g, vtrace(a, erase))
open('all/p03_new.svg', 'w').write(svg)
print('KB', len(svg) // 1024)
