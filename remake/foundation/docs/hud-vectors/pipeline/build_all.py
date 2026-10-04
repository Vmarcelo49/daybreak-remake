"""Gera os 7 SVGs polidos em all/. Rode na pasta que contém hud/ (os PNGs) e all/."""
import runpy, os, numpy as np
from polish import *
os.makedirs('all', exist_ok=True)
# sheets sem efeitos especiais: só vtracer
for n in ['system', 'p06']:
    a = load(f'hud/{n}.png'); H, W = a.shape[:2]
    open(f'all/{n}_new.svg', 'w').write(assemble(W, H, [], '', vtrace(a)))
# sheets com polimento (gradientes reais, glow/halo/blur como filtros SVG)
for st in ['stage1', 'stage_p01', 'stage_p03', 'stage_p09', 'stage_p00']:
    print('==', st); runpy.run_path(f'{st}.py')
