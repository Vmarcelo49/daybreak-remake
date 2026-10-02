# CJK text: what the original does, and the three ways to replace it

Phase 1 decision item (`FULL-REPLACEMENT-PLAN.md` §4: "CJK decision. ASCII
bitmap cannot do HUD Japanese … decide early even if implementation lands
later"). This document is the evidence and the options. The decision itself
is recorded at the bottom once made.

## 1. What the original game actually does (RE evidence)

Text is GDI, not D3DX. Three functions carry the whole path:

- `FUN_0065d870` (0x0065d870) — creates the font:
  `CreateFontA(height, 0, 0, 0, 700 /*FW_BOLD*/, italic, 0, 0, 0x80
  /*SHIFTJIS_CHARSET*/, 4 /*OUT_TT_PRECIS*/, 0, 2 /*PROOF_QUALITY*/,
  0x31 /*VARIABLE_PITCH|FF_SWISS*/, facename)`, then `GetTextMetricsA` for the
  ascent. The face name is a string the game supplies at object offset 0xc —
  it is configuration, not a hardcoded D3DX font.
- `FUN_0065d9a0` (0x0065d9a0) — rasterizes one glyph:
  `GetGlyphOutlineA(hdc, glyph, 5, &metrics, size, buffer, &matrix)`, i.e. the
  GDI outline rasterizer fills the game's **own** glyph bitmap, which is then
  uploaded like any other texture.
- `FUN_0065dad0` (0x0065dad0) — the string renderer: Shift-JIS input, walk via
  `FUN_0065e3a0` (next character, multi-byte aware), with in-string control
  codes — `\c` followed by six hex digits sets the text colour
  (`FUN_0065e450` = hex digit), `\e` another command. It renders into a
  zero-filled bitmap (`memset(w*h*bpp/8)`).

So the original is: **system font (GDI, SHIFTJIS charset, bold swiss) →
outline rasterized by the OS into a glyph cache → composed with Shift-JIS
strings and inline colour codes.** It does not ship a font, does not ship
glyph sheets, and does not use `ID3DXFont` anywhere (`ID3DXFont`/`DrawTextA`
have zero hits in `research/decompiled/`; only this GDI path).

## 2. What that means for text on screen (evidence: banked reference frames)

Read against `remake/docs/reference/*.webp` (the ground-truth captures):

- **In-battle HUD**: mostly Latin — `LIMIT 100%`, `MAIN`, `CHARGE`, `HP`,
  `STAMINA`, `com`, `0%`, `OYASHIRO` — **plus at least one CJK string**: the
  label `適当` (`battle-hud.webp`, `battle-stamina.webp`, `ko-moment.webp`,
  bottom-left above the OYASHIRO bar; what it labels is not yet RE'd, the
  glyphs are what matters here). The rounded boxes flanking it are
  **button-icon art**, not font glyphs: at 400% zoom each box contains a
  dash, not a character. They are textures and need no font work.
- **`撃破!`** (KO banner) is a large styled graphic, also art, not font text.
- **Menus** (`hypermode-select.webp` and friends) are dense Japanese —
  `恐怖のオヤシロモード`, `自分がダメージを受けた後で発動`, `決定`, `戻る`.
- **Result screens** (`result-report.webp`) are a full page of Japanese
  dialogue with player-name lines.
- The original's own window title arrives as Shift-JIS mojibake in the
  reference capture (`battle-stamina.webp`), which is the same path showing
  through: Shift-JIS bytes rendered by a non-Japanese text stack.

Consequence for the plan: the `--versus` D2 gate frame **does** contain CJK
(`適当`), so an ASCII-only bitmap font cannot match it. The Phase 1 warning
was correct; the mitigation is this decision, not a Phase 2 blocker — Phase 2
can build the HUD with the Latin labels and the correct label geometry, and
the CJK string lands with this decision's implementation in Phase 3.

## 3. The three options

### A. Platform system fonts (closest to the original's own mechanism)

Windows: GDI/DirectWrite as today. Linux: fontconfig + a rasterizer
(FreeType) or fontconfig-driven glyph lookup. Web: browser font stack via
canvas `measureText`/`fillText` into an atlas.

- Pro: same *kind* of source as the original (the OS picks the face), no font
  shipped, handles unbounded text (result dialogue, names).
- Con: **three backends**, and — decisive for this project — **no
  cross-target determinism**. The byte-identical Linux-vs-Wine discipline
  (§4 of the plan, used for every capture claim so far) is impossible when
  Linux native rasterizes with fontconfig/FreeType and Wine rasterizes with
  GDI. Env-dependent face availability is exactly the failure the DX9 HUD
  already hit (`remake/src/render/hud.h`: "Wine often lacks CJK fonts").

### B. In-process TrueType rasterization from one fetched font

Vendor `stb_truetype` (public domain, single header — the same class of
dependency as the rest of `third_party/`), fetch one OFL-licensed Japanese
font (e.g. Noto Sans CJK JP) through `scripts/fetch_deps.sh` — **fetched,
never committed**, like SDL3 and wgpu-native — and rasterize glyphs on demand
into the existing UI atlas path. Keep the Shift-JIS decoder and the `\c`
colour-code semantics from `FUN_0065dad0` so strings render as the game means
them. ASCII bitmap stays as the zero-dependency fallback.

- Pro: **one code path on Linux, Windows and web** → captures stay
  byte-identical, which is what every previous phase's evidence rests on.
  Works on the web, where the browser's CJK coverage cannot be guaranteed
  (already verified that the web build can fetch asset packs over HTTP).
  Unbounded text works. No game data or licensed font in git.
- Con: adds one vendored header + one fetched font to the toolchain. Glyph
  shapes will not be pixel-identical to the original's MS-PGothic-ish GDI
  rendering — but neither would option A on Linux, and the plan's standard is
  a matching frame, not matching font hinting.

### C. Baked glyph atlas (subset)

Generate a glyph atlas offline from the same font, covering exactly the
strings the port uses (census from the RE corpus), commit the atlas (a few KB
for the HUD's handful of CJK labels; larger for menus).

- Pro: smallest, fastest, fully deterministic, no runtime font code.
- Con: breaks on unbounded text — result dialogue and player names are
  dynamic; anything outside the subset renders as boxes. Needs a regeneration
  step whenever strings change, and the census must come from game text,
  which is not in git.

## 4. Recommendation

**B**, for one reason that outweighs the others: it is the only option that
keeps Linux native, Windows/Wine and the browser on **the same rasterizer**,
and this plan's entire verification method ("byte-identical where
determinism is claimed") depends on that. C stays available as a Phase 3
optimization for the HUD's fixed labels if atlas cost ever matters — it can be
layered on top of B without changing the interface. A is rejected for the
three-backend divergence, not for fidelity.

Fallback rule for any option: if the font or rasterizer is unavailable, the
existing ASCII bitmap draws (no hard dependency), and `ui/fallback.h`'s
degraded path keeps a frame renderable — the same rule the texture path
already follows.

## 5. Decision

**Decided 2026-10-02 (user): option B — in-process TrueType rasterization
from one fetched OFL CJK font, ASCII bitmap as fallback.** Rationale as in §4:
one rasterizer across Linux/Windows/web keeps the byte-identical capture
discipline that every phase's evidence rests on; the font is fetched like the
other third-party dependencies and never committed; `stb_truetype` is
public-domain and single-header, the same class as the existing vendored deps.
Concretely: vendor `stb_truetype.h` under `third_party/`, fetch Noto Sans CJK
JP (OFL) in `scripts/fetch_deps.sh` alongside SDL3/wgpu-native, rasterize into
the existing UI atlas (`src/ui/`), port the Shift-JIS walk and `\c` colour
codes from `FUN_0065dad0`, and keep `ui/fallback.h`'s degraded path when the
font is absent.

Implementation lands in Phase 3, in the plan's order — Phase 2 builds the HUD
with the Latin labels, reserving the `適当` label position from the reference
frames. Option C may later be layered on for the HUD's fixed strings if atlas
cost matters (it needs no interface change); option A is rejected — three
backends cannot produce the cross-target determinism this project verifies
with.
