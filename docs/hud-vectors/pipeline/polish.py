import io, re
import numpy as np, cv2, potrace, vtracer, resvg_py
from PIL import Image
from scipy import ndimage as ndi

SV = 4      # escala usada no vtracer
PADN = 8    # padding "edge" ao redor da folha (formas que encostam na borda)


def load(path):
    return np.array(Image.open(path).convert('RGBA'))


def render(svg, width=None, zoom=None, bg=None):
    kw = {}
    if width: kw['width'] = width
    if zoom: kw['zoom'] = zoom
    if bg: kw['background'] = bg
    b = resvg_py.svg_to_bytes(svg_string=svg, **kw)
    return Image.open(io.BytesIO(bytes(b))).convert('RGBA')


# ---------------------------------------------------------------- traçado
def path_d(mask_f, ox, oy, s=8, blur=0.5, alphamax=1.0, opttol=0.8):
    """mask_f float 0..1 -> string 'd' em coordenadas da folha (ox,oy = origem do recorte)."""
    up = cv2.resize(mask_f.astype(np.float32), None, fx=s, fy=s, interpolation=cv2.INTER_CUBIC)
    up = cv2.GaussianBlur(up, (0, 0), s * blur)
    bm = potrace.Bitmap(~(up > 0.5))
    pl = bm.trace(turdsize=s * s // 2, turnpolicy=potrace.POTRACE_TURNPOLICY_MINORITY,
                  alphamax=alphamax, opticurve=True, opttolerance=opttol)
    d = []
    f = lambda v, o: f"{v / s + o:.2f}"
    for c in pl:
        sp = c.start_point
        d.append(f"M{f(sp.x, ox)},{f(sp.y, oy)}")
        for seg in c.segments:
            if seg.is_corner:
                d.append(f"L{f(seg.c.x, ox)},{f(seg.c.y, oy)}L{f(seg.end_point.x, ox)},{f(seg.end_point.y, oy)}")
            else:
                d.append(f"C{f(seg.c1.x, ox)},{f(seg.c1.y, oy)} {f(seg.c2.x, ox)},{f(seg.c2.y, oy)} "
                         f"{f(seg.end_point.x, ox)},{f(seg.end_point.y, oy)}")
        d.append("Z")
    return "".join(d)


def mask_path(mask, bbox=None, m=4, **kw):
    """Traça uma máscara (bool/float, tamanho da folha). Faz padding 'edge' pra formas na borda."""
    H, W = mask.shape
    if bbox is None:
        ys, xs = np.nonzero(mask > 0.01)
        bbox = (xs.min(), ys.min(), xs.max() - xs.min() + 1, ys.max() - ys.min() + 1)
    x, y, w, h = bbox
    P = PADN
    mp = np.pad(mask.astype(np.float32), P, mode='edge')
    sub = mp[y + P - m: y + P + h + m, x + P - m: x + P + w + m]
    return path_d(sub, x - m, y - m, **kw)


def components(mask, dil=0):
    m = mask.astype(np.uint8)
    if dil:
        m = cv2.dilate(m, np.ones((2 * dil + 1,) * 2, np.uint8))
    n, lab, st, _ = cv2.connectedComponentsWithStats(m, connectivity=8)
    return lab, [(i, *map(int, st[i])) for i in range(1, n)]


# ---------------------------------------------------------------- gradiente
def hexc(c):
    c = np.clip(np.round(c), 0, 255).astype(int)
    return '#%02x%02x%02x' % tuple(c)


def fit_gradient(a, core, gid, nst=8):
    """Ajusta um linearGradient (multi-stop) às cores dos pixels 'core'. Retorna (defs, erro_rms)."""
    ys, xs = np.nonzero(core)
    cols = a[ys, xs, :3].astype(float)
    px, py = xs + .5, ys + .5
    rng = cols.max(0) - cols.min(0)
    if rng.max() < 5:
        return None, hexc(np.median(cols, 0)), 0.0
    A = np.c_[px, py, np.ones(len(px))]
    coef = np.linalg.lstsq(A, cols, rcond=None)[0]
    G = coef[:2].T                       # 3x2
    _, sv, vt = np.linalg.svd(G)
    dvec = vt[0]
    t = px * dvec[0] + py * dvec[1]
    t0, t1 = t.min(), t.max()
    tn = (t - t0) / max(t1 - t0, 1e-6)
    edges = np.linspace(0, 1, nst + 1)
    stops, pred = [], np.zeros_like(cols)
    cen = np.array([px.mean(), py.mean()])
    tc = cen @ dvec
    for k in range(nst):
        sel = (tn >= edges[k]) & ((tn < edges[k + 1]) | (k == nst - 1))
        if sel.sum() == 0:
            continue
        c = np.median(cols[sel], 0)
        off = 0.0 if k == 0 else (1.0 if k == nst - 1 else float(tn[sel].mean()))
        stops.append((off, c))
        pred[sel] = c
    err = float(np.sqrt(((pred - cols) ** 2).mean()))
    p0 = cen + dvec * (t0 - tc)
    p1 = cen + dvec * (t1 - tc)
    s = ''.join(f'<stop offset="{o:.3f}" stop-color="{hexc(c)}"/>' for o, c in stops)
    d = (f'<linearGradient id="{gid}" gradientUnits="userSpaceOnUse" x1="{p0[0]:.2f}" y1="{p0[1]:.2f}" '
         f'x2="{p1[0]:.2f}" y2="{p1[1]:.2f}">{s}</linearGradient>')
    return d, f'url(#{gid})', err


def gradient_objects(a, lab, comps, prefix, nst=8, blur=0.45):
    defs, shapes, erase, errs = [], [], np.zeros(a.shape[:2], bool), []
    for k, (i, x, y, w, h, area) in enumerate(comps):
        sel = lab == i
        alpha = (a[..., 3] / 255.0) * sel
        d = mask_path(alpha, (x, y, w, h), blur=blur, alphamax=0.9)
        core = ndi.binary_erosion(sel & (a[..., 3] > 240), iterations=1)
        if core.sum() < 20:
            core = sel & (a[..., 3] > 240)
        gdef, fill, err = fit_gradient(a, core, f'{prefix}{k}', nst)
        if gdef:
            defs.append(gdef)
        shapes.append(f'<path d="{d}" fill="{fill}"/>')
        erase |= ndi.binary_dilation(sel, iterations=1)
        errs.append(err)
    return defs, shapes, erase, errs


# ---------------------------------------------------------------- barras com glow (P01)
def bar_group(P, cid, ds=6.5, ss=2.6, cw=3.0, cs=1.5, co=0.9, line=2.0):
    """Barra preta com linha creme + glow creme + sombra preta suave."""
    return (
        f'<clipPath id="{cid}"><path d="{P}"/></clipPath>'
        f'<filter id="{cid}s" x="-30%" y="-80%" width="160%" height="260%" color-interpolation-filters="sRGB">'
        f'<feGaussianBlur stdDeviation="{ss}"/></filter>'
        f'<filter id="{cid}c" x="-10%" y="-40%" width="120%" height="180%" color-interpolation-filters="sRGB">'
        f'<feGaussianBlur stdDeviation="{cs}"/></filter>'
        f'<g>'
        f'<path d="{P}" fill="#000" stroke="#000" stroke-width="{2 * ds}" stroke-linejoin="round" filter="url(#{cid}s)"/>'
        f'<path d="{P}" fill="none" stroke="#f6eab2" stroke-width="{cw}" stroke-linejoin="round" opacity="{co}" filter="url(#{cid}c)"/>'
        f'<path d="{P}" fill="#000"/>'
        f'<path d="{P}" fill="none" stroke="#f6eab2" stroke-width="{line}" clip-path="url(#{cid})"/>'
        f'</g>')


def find_cream_shapes(a, xmax=10000):
    R, G, B, A = [a[..., k].astype(int) for k in range(4)]
    cream = (A > 200) & (R > 200) & (R - B > 40) & (R - G < 40) & (G - B < 90)
    cream[:, xmax:] = False
    D = 4
    lab, comps = components(cream, dil=D)
    out = []
    for (i, x, y, w, h, area) in comps:
        ring = cream & (lab == i)
        if ring.sum() < 40:
            continue
        closed = ndi.binary_fill_holes(lab == i)          # 'lab' vem da máscara dilada (fecha fendas)
        filled = ndi.binary_erosion(closed, structure=np.ones((3, 3), bool), iterations=D) | ring
        if filled.sum() < ring.sum() * 1.5:   # sem miolo (barra de gradiente etc.)
            continue
        out.append((filled, (x, y, w, h), ring))
    return out


def vtrace(a, erase=None, **over):
    """Roda o vtracer (multicolor) no sheet ampliado; 'erase' = máscara bool de pixels a apagar."""
    a = a.copy()
    if erase is not None:
        a[erase] = 0
    f = a.astype(np.float32)
    up = cv2.resize(f, None, fx=SV, fy=SV, interpolation=cv2.INTER_CUBIC)
    up = cv2.GaussianBlur(up, (0, 0), SV * 0.45)
    up = np.clip(up, 0, 255).astype(np.uint8)
    up[..., 3] = np.where(up[..., 3] > 110, 255, 0)
    h, w = up.shape[:2]
    kw = dict(colormode='color', hierarchical='stacked', mode='spline', filter_speckle=8,
              color_precision=6, layer_difference=12, corner_threshold=60, length_threshold=4.0,
              splice_threshold=45, path_precision=1)
    kw.update(over)
    svg = vtracer.convert_pixels_to_svg(list(map(tuple, up.reshape(-1, 4))), (w, h), **kw)
    return re.search(r'<svg[^>]*>(.*)</svg>', svg, re.S).group(1)


def assemble(W, H, defs, under, vt_inner, over=''):
    return (f'<svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 {W} {H}" width="{W * SV}" height="{H * SV}">'
            f'<defs>{"".join(defs)}</defs>{under}<g transform="scale({1 / SV})">{vt_inner}</g>{over}</svg>')
