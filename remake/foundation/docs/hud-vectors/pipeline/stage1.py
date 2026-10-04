import numpy as np
from polish import *
# ---- p02: 13 formas com gradiente
a = load('hud/p02.png')
lab, comps = components(a[...,3] > 8)
comps = [c for c in comps if c[5] > 200]
defs, shapes, erase, errs = gradient_objects(a, lab, comps, 'g', nst=8)
print('p02 formas', len(comps), 'erro rms por forma:', [round(e,1) for e in errs])
H, W = a.shape[:2]
svg = assemble(W, H, defs, ''.join(shapes), vtrace(a, erase))
open('all/p02_new.svg','w').write(svg)
im = render(svg, width=W*2); im2 = Image.open('hud/p02.png').convert('RGBA').resize((W*2,H*2), Image.NEAREST)
# diferença média entre original e vetor (premult sobre cinza)
bg = Image.new('RGBA', im.size, (128,128,128,255))
A = bg.copy(); A.alpha_composite(im2); B = bg.copy(); B.alpha_composite(im)
d = np.abs(np.array(A).astype(int)-np.array(B).astype(int)).mean()
print('diff média p02 (0-255):', round(d,2))
side = Image.new('RGB', (W*4+20, H*2), (70,90,110))
side.paste(A.convert('RGB'), (0,0)); side.paste(B.convert('RGB'), (W*2+20,0)); side.save('all/cmp_p02_new.png')
