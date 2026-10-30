import numpy as np, itertools
from polish import *
a = load('hud/p09.png'); H, W = a.shape[:2]
A = a[..., 3].astype(float) / 255
outside = np.load('all/p09_outside.npy'); barrier = np.load('all/p09_barrier.npy'); rgb0 = a[..., :3].astype(int)
bb = np.zeros((H, W), bool); bb[300:455, 232:392] = True
S = bb & ~outside & ~barrier & (rgb0[..., 0] >= 20) & (rgb0[..., 1] < rgb0[..., 0] * 0.5)
S = ndi.binary_closing(S, structure=np.ones((3, 3), bool), iterations=1)
lab_s, n_s = ndi.label(S)
for i in range(1, n_s + 1):
    if (lab_s == i).sum() < 40: S[lab_s == i] = False
S = ndi.binary_fill_holes(S) & ~barrier

# ---- halo: máscara alpha>0.5 deslocada por k px, blur sigma
Hm = A > 0.5
def halo_svg(k, sig, extra=''):
    m = Hm if k == 0 else (ndi.distance_transform_edt(~Hm) <= k) if k > 0 else (ndi.distance_transform_edt(Hm) > -k)
    d = mask_path(m.astype(float), None, blur=0.9, alphamax=1.2, opttol=1.0)
    return (f'<filter id="hb" x="-20%" y="-20%" width="140%" height="140%" color-interpolation-filters="sRGB">'
            f'<feGaussianBlur stdDeviation="{sig}"/></filter><path d="{d}" fill="#000" filter="url(#hb)"/>'), d
best = None
for k, sig in itertools.product([0, 1, 2, 3], [2, 3, 4, 5]):
    g, _ = halo_svg(k, sig)
    im = np.array(render(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}">{g}</svg>', width=W)).astype(float)
    e = np.abs(im[..., 3] / 255 - A)[outside].mean()
    if best is None or e < best[0]: best = (e, k, sig)
print('halo melhor (erro alpha médio, k, sigma):', best)

# ---- overlay vermelho do 破 (glow interno: vermelho nas bordas, preto no centro)
rgb = a[..., :3].astype(float)
PS = mask_path(S.astype(float), None, blur=0.7, alphamax=1.0)
PC = mask_path(ndi.binary_dilation(S, iterations=2).astype(float), None, blur=0.7, alphamax=1.0)
def red_svg(w, sig, col='#ff0000'):
    return (f'<clipPath id="po"><path d="{PC}"/></clipPath>'
            f'<filter id="rb" x="-20%" y="-20%" width="140%" height="140%" color-interpolation-filters="sRGB"><feGaussianBlur stdDeviation="{sig}"/></filter>'
            f'<g clip-path="url(#po)"><path d="{PC}" fill="#000"/><path d="{PS}" fill="none" stroke="{col}" stroke-width="{w}" stroke-linejoin="round" filter="url(#rb)"/></g>')
core = ndi.binary_erosion(S, iterations=3)
rb = None
for w, sig in itertools.product([14, 18, 22, 28], [2, 3, 4, 5]):
    im = np.array(render(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}">{red_svg(w, sig)}</svg>', width=W)).astype(float)
    e = np.abs(im[..., :3] - rgb)[core].mean()
    if rb is None or e < rb[0]: rb = (e, w, sig)
print('vermelho melhor (erro rgb, w, sigma):', rb)

# ---- montagem
halo_g, _ = halo_svg(1, 5)
red_g = red_svg(rb[1], rb[2])
erase = outside | (S & ~barrier) | ((rgb[..., 0] > 80) & (rgb[..., 0] > 2 * rgb[..., 1]) & ~barrier)
svg = assemble(W, H, [], halo_g + red_g, vtrace(a, erase))
open('all/p09_new.svg', 'w').write(svg)
print('KB', len(svg) // 1024)
