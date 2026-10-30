import numpy as np, cv2
from scipy.optimize import least_squares
from polish import *

def body_geometry(a, bbox):
    x, y, w, h = bbox
    A = a[..., 3]
    sil = np.zeros(A.shape, bool); sil[y:y + h, x:x + w] = A[y:y + h, x:x + w] >= 100
    cnts, _ = cv2.findContours(sil.astype(np.uint8), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE)
    c = max(cnts, key=cv2.contourArea)[:, 0, :]
    c = c[c[:, 1] < y + h * 0.80]                    # ignora o nó (parte de baixo)
    (cx, cy), (MA, ma), ang = cv2.fitEllipse(c.reshape(-1, 1, 2).astype(np.float32))
    ell = np.zeros(A.shape, np.uint8)
    cv2.ellipse(ell, ((cx, cy), (MA, ma), ang), 1, -1)
    return sil, ell.astype(bool)

def fit_body(a, pix, nstops=5, K=4, seed=0):
    ys, xs = np.nonzero(pix)
    rng = np.random.default_rng(seed)
    idx = rng.choice(len(xs), size=min(5000, len(xs)), replace=False)
    px, py, col = xs[idx] + .5, ys[idx] + .5, a[ys[idx], xs[idx], :3].astype(float)
    x0, x1, y0, y1 = px.min(), px.max(), py.min(), py.max()
    W_, H_ = x1 - x0, y1 - y0
    c0 = np.array([x0 + .55 * W_, y0 + .38 * H_]); R0 = .75 * W_
    r = np.hypot(px - c0[0], py - c0[1]) / R0
    offs = np.linspace(0, 1, nstops)
    base0 = np.array([np.median(col[(r >= o - .12) & (r <= o + .12)], 0) if ((r >= o - .12) & (r <= o + .12)).any() else col.mean(0) for o in offs])
    ns = nstops * 3

    def model(p, px, py, k_):
        cx, cy, R = p[:3]
        base = p[3:3 + ns].reshape(nstops, 3)
        t = np.clip(np.hypot(px - cx, py - cy) / max(R, 10), 0, 1)
        out = np.stack([np.interp(t, offs, base[:, c]) for c in range(3)], 1)
        for k in range(k_):
            bx, by, sg, am, rr, g, b = p[3 + ns + 7 * k: 3 + ns + 7 * (k + 1)]
            al = np.clip(am, 0, 1) * np.exp(-((px - bx) ** 2 + (py - by) ** 2) / (2 * max(sg, 4) ** 2))
            out = out * (1 - al[:, None]) + np.array([rr, g, b])[None] * al[:, None]
        return out
    p = np.r_[c0, R0, base0.ravel()]
    p = least_squares(lambda q: (model(q, px, py, 0) - col).ravel(), p, max_nfev=80).x
    for k in range(K):                                  # blobs gulosos: um por vez onde o resíduo é maior
        res = col - model(p, px, py, k)
        gx = np.clip(((px - x0) / W_ * 8).astype(int), 0, 7); gy = np.clip(((py - y0) / H_ * 8).astype(int), 0, 7)
        best, bc = -1, None
        for i in range(8):
            for j in range(8):
                sel = (gx == i) & (gy == j)
                if sel.sum() < 15: continue
                m = np.linalg.norm(res[sel].mean(0))
                if m > best: best, bc = m, (i, j, sel)
        i, j, sel = bc
        bx, by = x0 + (i + .5) / 8 * W_, y0 + (j + .5) / 8 * H_
        target = np.median(col[sel], 0)
        p = np.r_[p, bx, by, .14 * W_, .6, target]
        p = least_squares(lambda q: (model(q, px, py, k + 1) - col).ravel(), p, max_nfev=120).x
    rms = float(np.sqrt(np.mean((model(p, px, py, K) - col) ** 2)))
    base = p[3:3 + ns].reshape(nstops, 3)
    stops = ''.join(f'<stop offset="{o:.3f}" stop-color="{hexc(c)}"/>' for o, c in zip(offs, base))
    return (p[0], p[1], p[2]), stops, [p[3 + ns + 7 * k: 3 + ns + 7 * (k + 1)] for k in range(K)], rms

def balloon_svg(a, bbox, bid):
    x, y, w, h = bbox
    sil, ell = body_geometry(a, bbox)
    lum = a[..., :3].mean(-1)
    d_in = ndi.distance_transform_edt(sil)
    body = ndi.binary_erosion(ell, iterations=4) & sil & (d_in >= 4)
    fitpix = body & (lum < 170)
    (cx0, cy0, R0), stops, blobs, rms = fit_body(a, fitpix)
    P = mask_path(sil.astype(float), (x, y, w, h), blur=0.7, alphamax=1.1)
    # corpo (preenchimento) = elipse erodida; vtracer fica com contorno, brilhos e nó
    erase_body = body & (lum < 170)
    defs = [f'<radialGradient id="{bid}l" gradientUnits="userSpaceOnUse" cx="{cx0:.1f}" cy="{cy0:.1f}" r="{R0:.1f}">{stops}</radialGradient>',
            f'<clipPath id="{bid}c"><path d="{P}"/></clipPath>']
    layers = f'<path d="{P}" fill="url(#{bid}l)"/>'
    for k, (bx, by, sg, am, r, g, b) in enumerate(blobs):
        sg = max(sg, 3); am = float(np.clip(am, 0, 1)); R = 3 * sg
        st = ''.join(f'<stop offset="{o:.2f}" stop-color="{hexc([r, g, b])}" stop-opacity="{am * np.exp(-0.5 * (3 * o) ** 2):.3f}"/>' for o in (0, .2, .4, .6, .8, 1))
        defs.append(f'<radialGradient id="{bid}r{k}" gradientUnits="userSpaceOnUse" cx="{bx:.1f}" cy="{by:.1f}" r="{R:.1f}">{st}</radialGradient>')
        layers += f'<circle cx="{bx:.1f}" cy="{by:.1f}" r="{R:.1f}" fill="url(#{bid}r{k})"/>'
    # contorno desenhado como traço (limpo e uniforme) por cima do degradê
    layers += f'<path d="{P}" fill="none" stroke="#0b1220" stroke-width="5.6" stroke-linejoin="round"/>'
    # vtracer só para brilhos (claros) e o nó (fora da elipse), alpha forçado a opaco
    ell_big = ndi.binary_dilation(ell, iterations=2)
    yy = np.arange(a.shape[0])[:, None] * np.ones((1, a.shape[1]))
    knot = sil & ~ell_big & (yy > (y + h * 0.6))
    hi = sil & ndi.binary_erosion(ell, iterations=2) & (lum >= 170)
    keep = knot | hi
    crop = a[y - 4:y + h + 4, x - 4:x + w + 4].copy()
    sub_keep = keep[y - 4:y + h + 4, x - 4:x + w + 4]
    crop[..., 3] = np.where(sub_keep, 255, 0)
    crop[crop[..., 3] == 0] = 0
    inner = vtrace(crop)
    content = f'<g transform="translate({x - 4},{y - 4}) scale({1 / SV})">{inner}</g>'
    # brilho branco externo (alpha baixo fora da silhueta)
    glow = (f'<filter id="{bid}g" x="-20%" y="-20%" width="140%" height="140%" color-interpolation-filters="sRGB"><feGaussianBlur stdDeviation="1.1"/></filter>'
            f'<clipPath id="{bid}o"><path clip-rule="evenodd" d="M-2000,-2000H4000V4000H-2000Z{P}"/></clipPath>'
            f'<g clip-path="url(#{bid}o)"><path d="{P}" fill="#fff" stroke="#fff" stroke-width="4" stroke-linejoin="round" opacity="0.8" filter="url(#{bid}g)"/></g>')
    body_grp = f'<g opacity="{156 / 255:.3f}"><g clip-path="url(#{bid}c)">{layers}</g>{content}</g>'
    return defs, glow + body_grp, rms, erase_body | (sil & ~erase_body) | ndi.binary_dilation(sil, iterations=7)
