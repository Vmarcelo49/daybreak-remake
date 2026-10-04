#!/usr/bin/env python3
"""
vectorize_sprites.py - transforma sprites em pixel art (PNG com alpha) em SVG limpo.

Como funciona:
  1. Acha cada glifo/sprite na imagem (componentes conectados do canal alpha,
     com dilatação pra juntar pedaços, tipo o "%" ou o "i").
  2. Pra cada um, gera DUAS máscaras:
       - silhueta  (alpha)               -> camada de baixo, cor do contorno
       - preenchimento (cor clara/canal) -> camada de cima
  3. Cada máscara é ampliada (bicúbica) e borrada de leve, o que dissolve
     os "degraus" dos pixels, e depois binarizada em 0.5.
  4. potrace transforma a máscara em curvas Bézier.
  5. Salva um SVG por glifo (+ opcionalmente uma folha com todos).

Dependências:
  pip install potracer opencv-python-headless numpy pillow

Exemplos:
  # fonte branca com contorno preto
  python vectorize_sprites.py p00.png -o out --fill lum --fill-color "#ffffff" \
         --region 0 0 512 128

  # fonte vermelha (usa o canal R como preenchimento)
  python vectorize_sprites.py p00.png -o out_red --fill r --fill-color "#ff0000" \
         --region 0 128 512 128
"""
import argparse
import os

import cv2
import numpy as np
import potrace
from PIL import Image


def upscale(arr, s):
    return cv2.resize(arr.astype(np.float32), None, fx=s, fy=s,
                      interpolation=cv2.INTER_CUBIC)


def smooth_mask(arr, s, blur, thr=0.5):
    # o blur proporcional ao upscale é o que tira o serrilhado do pixel art
    f = cv2.GaussianBlur(upscale(arr, s), (0, 0), s * blur)
    return f > thr


def trace_mask(mask, s, fill, turd, alphamax, opttol):
    # potrace trata True como "tinta"; o ~ é porque a polaridade dele é invertida
    # em relação ao que a gente quer com potracer
    bm = potrace.Bitmap(~mask)
    plist = bm.trace(turdsize=turd,
                     turnpolicy=potrace.POTRACE_TURNPOLICY_MINORITY,
                     alphamax=alphamax, opticurve=True, opttolerance=opttol)
    d = []
    for c in plist:
        sp = c.start_point
        d.append(f"M{sp.x / s:.2f},{sp.y / s:.2f}")
        for seg in c.segments:
            if seg.is_corner:
                d.append(f"L{seg.c.x / s:.2f},{seg.c.y / s:.2f}"
                         f"L{seg.end_point.x / s:.2f},{seg.end_point.y / s:.2f}")
            else:
                d.append(f"C{seg.c1.x / s:.2f},{seg.c1.y / s:.2f} "
                         f"{seg.c2.x / s:.2f},{seg.c2.y / s:.2f} "
                         f"{seg.end_point.x / s:.2f},{seg.end_point.y / s:.2f}")
        d.append("Z")
    return f'<path fill="{fill}" fill-rule="evenodd" d="{"".join(d)}"/>'


def fill_weight(rgb, a, mode):
    """Quão 'preenchimento' é cada pixel (0..1). O contorno escuro dá ~0."""
    if mode == "lum":
        w = rgb.mean(-1)
    else:
        w = rgb[..., "rgb".index(mode)]
    return a * w


def find_glyphs(alpha, merge, min_area):
    mask = (alpha > 20).astype(np.uint8)
    if merge > 0:
        k = cv2.getStructuringElement(cv2.MORPH_RECT, (merge * 2 + 1,) * 2)
        grouped = cv2.dilate(mask, k)
    else:
        grouped = mask
    n, _, st, _ = cv2.connectedComponentsWithStats(grouped, connectivity=8)
    boxes = []
    for i in range(1, n):
        x, y, w, h, _ = st[i]
        # área real (sem a dilatação) pra descartar sujeira
        if mask[y:y + h, x:x + w].sum() >= min_area:
            boxes.append((x, y, w, h))
    # ordem de leitura: linhas de cima pra baixo, esquerda pra direita
    boxes.sort(key=lambda b: (round(b[1] / 16), b[0]))
    return boxes


def vectorize(crop, a_args, pad=2):
    s = a_args.scale
    rgb = crop[..., :3].astype(np.float32) / 255
    a = crop[..., 3].astype(np.float32) / 255
    sil = np.pad(a, pad)
    fil = np.pad(fill_weight(rgb, a, a_args.fill), pad)
    sil_m = smooth_mask(sil, s, a_args.blur)
    fil_m = smooth_mask(fil, s, a_args.blur)
    turd = s * s // 2
    layers = trace_mask(sil_m, s, a_args.outline_color, turd, a_args.alphamax, a_args.opttol)
    layers += trace_mask(fil_m, s, a_args.fill_color, turd, a_args.alphamax, a_args.opttol)
    h, w = a.shape
    W, H = w + 2 * pad, h + 2 * pad
    svg = (f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}" '
           f'width="{W * 8}" height="{H * 8}">{layers}</svg>')
    return svg, W, H


def main():
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument("image")
    p.add_argument("-o", "--out", default="svg_out")
    p.add_argument("--region", nargs=4, type=int, metavar=("X", "Y", "W", "H"),
                   help="só processa essa área da imagem (útil pra separar linhas de cores)")
    p.add_argument("--fill", default="lum", choices=["lum", "r", "g", "b"],
                   help="de onde tirar o preenchimento: luminância ou um canal")
    p.add_argument("--fill-color", default="#ffffff")
    p.add_argument("--outline-color", default="#000000")
    p.add_argument("--scale", type=int, default=8, help="upscale antes de traçar")
    p.add_argument("--blur", type=float, default=0.8,
                   help="suavização (em px originais). Menor = mais fiel/serrilhado, "
                        "maior = mais redondo e contorno mais grosso")
    p.add_argument("--alphamax", type=float, default=1.2,
                   help="0 = só quinas, 1.33 = só curvas")
    p.add_argument("--opttol", type=float, default=1.0,
                   help="tolerância de simplificação das curvas")
    p.add_argument("--merge", type=int, default=2,
                   help="dilatação (px) pra juntar pedaços do mesmo glifo")
    p.add_argument("--min-area", type=int, default=30)
    p.add_argument("--names", help="nomes separados por vírgula, na ordem de leitura "
                                   "(ex: 0,1,2,3,4,5,6,7,8,9)")
    p.add_argument("--sheet", action="store_true", help="também gera sheet.svg")
    args = p.parse_args()

    im = np.array(Image.open(args.image).convert("RGBA"))
    ox, oy = 0, 0
    if args.region:
        x, y, w, h = args.region
        im = im[y:y + h, x:x + w]
        ox, oy = x, y

    boxes = find_glyphs(im[..., 3], args.merge, args.min_area)
    names = args.names.split(",") if args.names else []
    os.makedirs(args.out, exist_ok=True)

    sheet_parts, cursor = [], 0
    for i, (x, y, w, h) in enumerate(boxes):
        name = names[i] if i < len(names) else f"glyph_{i:03d}"
        svg, W, H = vectorize(im[y:y + h, x:x + w], args)
        with open(os.path.join(args.out, f"{name}.svg"), "w") as f:
            f.write(svg)
        if args.sheet:
            inner = svg[svg.index(">") + 1: svg.rindex("</svg>")]
            sheet_parts.append(f'<g id="{name}" transform="translate({cursor},0)">{inner}</g>')
            cursor += W + 2
        print(f"{name}: x={x + ox} y={y + oy} {w}x{h}")

    if args.sheet and sheet_parts:
        with open(os.path.join(args.out, "sheet.svg"), "w") as f:
            f.write(f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {cursor} 40">'
                    + "".join(sheet_parts) + "</svg>")
    print(f"\n{len(boxes)} glifos em {args.out}/")


if __name__ == "__main__":
    main()
