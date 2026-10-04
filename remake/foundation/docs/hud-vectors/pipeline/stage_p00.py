import numpy as np
from polish import *
from balloon import balloon_svg
a = load('hud/p00.png'); H, W = a.shape[:2]
defs, under, erase = [], '', np.zeros((H, W), bool)
for k, bb in enumerate([(21, 335, 150, 163), (213, 335, 150, 163)]):
    d, svg, rms, er = balloon_svg(a, bb, f'bl{k}')
    print(f'balão {k}: rms corpo = {rms:.1f}')
    defs += d; under += svg; erase |= er
# o resto do sheet (fontes, dígitos pequenos, MAX, LIMIT) continua via vtracer
inner = vtrace(a, erase)
svg = assemble(W, H, defs, '', inner, over=under)   # balões por cima da área já apagada
open('all/p00_new.svg', 'w').write(svg)
print('KB', len(svg) // 1024)
