# HUD fonts vector survey (Phase 5, multi-resolution groundwork)

> Status: **WIP — adopted delivery, not hand-finished.** Whole-sheet vectors
> (`hud-vectors/sheets/`) are a second agent's delivery, kept verbatim with
> its pipeline and compare plates; the previous per-glyph set was removed on
> adoption (git history keeps it). No hand pass has happened yet: any curve
> the tracing oversimplified, and any terminal/join that should be
> geometrically true, still wants an SVG-capable image editor. WARNING:
> `pipeline/build_all.py` regenerates the sheets from scratch, so hand edits
> inside `sheets/*.svg` are overwritten on rebuild — there is no hand-tuned
> guard in that pipeline yet. Until one lands, hand work lives outside the
> regen path: edit a copy, or finish a sheet and do not rebuild it.
>
> No product code touched (`src/`, `tests/` unchanged); everything here is
> docs plus a generator script. Binding constraints from
> `remake/docs/decisions.md` D1–D6 were checked: no `.X` handling involved
> (D3), no comment-policy surface (D5 — no `remake/` code), no scope change
> (D6). Game art is read from the local gitignored install and never
> committed.

## 0. Method

Every claim below was re-derived offline from the shipped bundles, not from
screenshots: `data/object/p00.cnv`, `P01.cnv`, `p02.cnv`, `p03.cnv`,
`system.cnv`, `data/chat/name_p1.cnv`, `data/network/number.cnv`, decoded per
the header `remake/tools/asset-tools/cnv_convert.py` documents (byte 0 =
bpp, +5 u32 height, +9 u32 width, +13 u32 compressed, +17 pixels, 32bpp
BGRA, rows top-down). One orientation gotcha is recorded so the next reader
does not re-discover it: `cnv_convert.py`'s `.bmp` output is vertically
flipped relative to the atlas coordinates `BATTLE-HUD-SPEC.md` and
`src/ui/hud_atlas.h` use (raw CNV rows are already top-down; the BMP writer
flips). Colors are brightest-interior-texel samples off the 32-bit data
(AA rims excluded); geometry is measured ink bounding boxes unless marked
SPEC (quoted from `BATTLE-HUD-SPEC.md`).

The in-battle HUD carries **no GDI text at all** — BATTLE-HUD-SPEC.md §4
(byte search: no LIMIT/CHARGE/STAMINA/OYASHIRO/com string in
`DaybreakDX.exe`; the ＭＳ ゴシック face at VA 0x6a49d8 serves result/chat
only). So "HUD text" = the bitmap lettering surveyed here.

## 1. Element survey

### 1a. P00 digit rows (the vectorized set — `HudFont` in `hud_atlas.h`)

| Element | Atlas source | Ink box | Sampled ink | Closest open match | Artifact |
|---|---|---|---|---|---|
| Big white `0`–`7` | P00 cells 64x64 from (0,0), 8/row (SPEC §3, `BigWhite` base (0,0) perRow 8, leading −28) | ~34x21 (cell (0,1) ink x[27,60] y[3,23]; SPEC: glyphs 36–41 x 27) | fill `#FFFFFF`, no outline (AA only) | **Nunito Black Italic** (OFL-1.1) — closest skeleton: extra-bold, true italic, rounded terminals. Gaps: original is wider with flat-cut bar terminals (`2/3/5` tops, `7` bar); not pixel-identical | `svg/digit-white-{0..9,pct,slash}.svg` |
| Big white `8 9 % /` | P00 row 1: `8`=(0,1), `9`=(1,1), `%`=(5,1)=(320,64), `/`=(6,1) (cells (2..4,1),(7,1) empty — verified) | same family | `#FFFFFF` | as above | same set |
| Big red `0`–`9 %` | P00 band y118–215 (SPEC §3); traced boxes (d*64,118,+64,+64), `8/9` y175–239, `%` (320,182,384,246) | same family | core `#FF0000` | as above, red ink | `svg/digit-red-*.svg` |
| Small green `0`–`9 + - . %` | P00 32x32 cells from (0,245), 15/row (`SmallGreen` base (0,256) perRow 15, leading −4; SPEC: 27x21 pitch 32) | 27x21 (SPEC) | core `#1BFFA1` | as above at small size | `svg/digit-green-*.svg` |
| Small yellow `0`–`9 + - . %` | P00 one row down (`SmallYellow` base (0,288), leading 0, pitch 32 — the 28px-pitch guess fails at cell 6, `hud_sprite_table.cpp` pins 32) | 27x21 | core `#FFFF28` | as above | `svg/digit-yellow-*.svg` |

Style note (all four rows): one extra-bold oblique grotesque with rounded
joins, ~15° slant, oval `0`, open `4`, flat-bar `7`, double-lobed `8`.
The three small-row colors are the team/readout coding (green = own-side
balloon popup, yellow = FPS counter `HudFont::SmallYellow` at (800,0,0.5)
per ROADMAP-PENDING.md D1).

### 1b. HUD label words (baked into bar/balloon art)

| Element | Atlas source | Ink box | Sampled ink | Closest open match |
|---|---|---|---|---|
| `LIMIT` | P00 sprite (384,320,96,32) pivot (56,8) (`LimitLabel`); ink x16–69 y13–19 = **54x7 px** | 54x7 | `#FFFFFF` | **Liberation Sans Bold + faux italic** (Liberation license; the regular is already fetched at `third_party/fonts/LiberationSans-Bold.ttf`). Grotesque bold-oblique skeleton matches; only the italic face still needs fetching |
| `MAIN` word | P01 bar art ~(185,138,252,162), white italic caps top-right of the MAIN bar | ~caps 12px | `#FFFFFF` | same Liberation-italic treatment |
| `CHARGE` word | P01 ~(180,74,252,98) | ~caps 12px | `#FFFFFF` | same |
| `HP` word | P01 ~(228,199,286,221) | ~caps 12px | `#FFFFFF` | same |
| `STAMINA` pill text | P01 (95,12,225,48) | caps ~20px | `#FFFFFF` | same |
| `OYASHIRO` caption | P01 daybreak04 copy (8,376,132,410) 32px rows, row = `hud+0x318` (SPEC §6 Q2) | caps ~14px | `#FFFFFF` | same |
| `MAX` | P00 (392,404,504,486) pivot (64,64) (`MaxLabel`), drawn at (64,534) | 112x82 art | vertical gradient `#FF5A0F` (top) → `#FF2A07` (bottom) + `#FFFFFF` rim ~2px + black outer (column profile measured) | digit-family skeleton (Nunito Black Italic) + gradient/rim in shader; traced as `svg/word-max.svg` silhouette |
| `1P 2P 3P / 4P com` tags | P01 blue (363,207,469,241) / red (363,466,468,495) (`TagCell` 64x32 cells) | 64x32 cells | white on blue/red chips | same Liberation-italic treatment; not traced (chip + text composite) |
| `com` bar word | `system.cnv` `1P 2P 3P 4P com` row (SPEC §6 Q7; print's `com` is white/pale — sheet choice unresolved) | — | — | same; blocked on the Q7 sheet question, no trace yet |

### 1c. Tactics/command cells (P03 — the CJK element)

| Element | Atlas source | Ink box | Sampled inks | Closest open match |
|---|---|---|---|---|
| Boxed `適当/格闘/射撃/集中/各個/後退` | P03 (0,0,128,64) pivot (64,32) (`CommandLabel`), cells 128x64, index = `hud+0x310` col = v mod 4 row = v div 4 (SPEC §6 Q2) | badge 126x39 art (1,13,127,52) | badge fill `#FFF050`, rim orange ~`#FF9000`, kanji core `#FDF96A`, flanking dash boxes white (dashes are texture, not glyphs — BATTLE-HUD-SPEC.md §4) | **M PLUS Rounded 1c Bold** (OFL) for the kanji skeleton + yellow/orange treatment; rounded heaviness matches the badge feel better than Noto CJK. Recommendation below keeps the badge as art |
| Alert `!` (P06), rings, arrows | P06/P03 cells — symbols, not text | — | — | out of scope (icon art) |

### 1d. Sting / system lettering (`system.cnv`, P04/P05/P08/P09)

| Element | Atlas source | Sampled ink | Closest open match |
|---|---|---|---|
| `OVER KILL!!` | system.cnv (0,0,512,64) | core `#FF1000`, yellow-white hot top, white rim, black shade — same chrome build as MAX | digit-family skeleton (Nunito Black Italic); traced silhouette `svg/sting-overkill.svg` |
| `DOWN!` | system.cnv (0,64,256,64) | core `#00FF00` + same chrome | same; `svg/sting-down.svg` |
| `PAUSE` | system.cnv (256,64,256,64) | periwinkle `#A0B0F0` + same chrome | same; `svg/sting-pause.svg` |
| `もう一度挑戦しますか？ / はい / いいえ / 本日の活動報告` | system.cnv rows y128–384 | heavy black rounded gothic + white rim | **Noto Sans CJK JP Bold** (OFL, same family as the fetched Regular) via `TextLayer`; not traced (unbounded reuse in menus) |
| `3 2 1 / 撃破! / 開始! / 赤組 青組 大勝利` | P09/P04/P05/P08 (SPEC §5 item 7) | white outline + red fill + black shade (SPEC §3) | same chrome approach as stings; not traced yet (transients, need `Match` round state first — ROADMAP-PENDING.md D3) |

### 1e. Chat / name font (ROADMAP-PENDING.md E6)

| Element | Atlas source | Geometry | Sampled ink | Closest open match |
|---|---|---|---|---|
| Name grid (`name_p1.cnv` + `name_p1s/name_p2/name_p2s` variants) | `data/chat/name_p1.cnv` 512x512; 16 cols x 12 rows of 32px cells: digits/symbols, A–Z, a–z, hiragana x5 rows, katakana x5 rows, symbols; names stored as (cellX,cellY) pairs via `FUN_00646bd0` (FRONTEND-PLAN.md §2.16) | 32px cells, thin gothic caps ~16px | `#FFFFFF` core, grey (~`#606060`) rim | **Noto Sans CJK JP Regular (OFL) — already fetched**, via the existing `TextLayer::loadFontChain` path. The grid *look* (soft-keyboard widget, `src/ui/soft_keyboard.*` per FRONTEND-PLAN.md:1097) stays atlas art; editable *names* are ordinary codepoints the TTF covers. No trace needed — a 192-cell trace would duplicate what the font already does |
| Netplay `number.cnv` | `data/network/number.cnv` 256x256: white digits + `接続中` + `接続に失敗` + red IP-entry dashes/frame | small white caps | `#FFFFFF`, red `#FF0000` dashes | same Noto CJK treatment; digits join the P00 digit program |
| GDI provenance | `FUN_0065d870` CreateFontA FW_BOLD SHIFTJIS, face `ＭＳ ゴシック` (CJK-TEXT.md §1) | — | — | Noto Sans CJK JP is the standard OFL substitute for MS Gothic; Liberation Sans Bold Italic substitutes the Latin side |

## 2. Vector source art (`docs/hud-vectors/`)

> Status: **WIP — adopted delivery, not hand-finished.** The whole-sheet
> vectors below are a second agent's delivery (`vendor/hud_vetorizado_v2.zip`,
> kept verbatim as reference, sha256 `e45a01b5…3102`), adopted because they
> beat the previous per-glyph traces on every axis that matters here:
> true straight edges at high magnification, fitted multi-stop gradients
> (balloons, MAX/sting chrome), glow bars, and full kana menu rows the old
> set had punted to TTF. The previous per-glyph set (`svg/`, `previews/`,
> `trace_hud.py`) was removed on adoption; git history keeps it.
>
> **Hand-edit warning:** `pipeline/build_all.py` regenerates the sheets from
> scratch, so hand edits inside `sheets/*.svg` are overwritten on rebuild —
> there is no hand-tuned guard in that pipeline yet (one is wanted: skip
> sheets carrying a marker, same convention as before). Until it lands, hand
> work lives outside the regen path: edit a copy, or finish a sheet and do
> not rebuild it.

Layout:

* `sheets/p00.svg p01/p02/p03/p06/p09/system.svg` — the seven HUD sheets as
  whole-sheet vectors in native 512 atlas coordinates (directly cuttable by
  the `hud_atlas.h` boxes when the SDF bake needs glyphs). Compare plates
  in `comparacoes/cmp_*.png` are original-vs-vector at 2x (original left,
  vector right); p00 measures ~4.8/255 mean-abs — AA/threshold, not
  structure.
* `pipeline/` — the generator: per-sheet recipes (`stage_p00.py`
  `stage_p01.py` `stage_p03.py` `stage_p09.py`, `stage1.py`), shared helpers
  (`polish.py`: potrace tracing, fitted multi-stop `linearGradient`s with
  RMS error, glow bars, vtracer multicolor; `balloon.py`: radial-gradient
  balloons with least-squares-fitted blobs), `cmp.py` (plate builder +
  diff metric), `build_all.py` (runs everything), `vectorize_sprites.py`
  (two-layer sprite tracer), `LEIAME.txt` (upstream notes, PT-BR).
  Needs: the 7 sheet PNGs as `hud/*.png` inputs (decode the
  `data/object/*.cnv` with the game's own decoder — e.g. the PNG set
  previously shipped alongside), plus `potracer vtracer resvg-py
  opencv-python-headless numpy scipy pillow`. Regen here was NOT
  re-executed (resvg-py absent); the committed sheets/plates are the
  delivered artifacts, verified by direct render + diff, not rebuilt.
* `vendor/hud_vetorizado_v2.zip` — the delivery exactly as received.
* `comparacoes/` — the delivered original-vs-vector plates (kept as the
  review record; re-runnable via `pipeline/cmp.py` once inputs exist).

Fidelity notes (honest): digits render clean straights and flat-cut
terminals at 16x — verify on any `cmp_*.png` digit row. Gradients are
fitted multi-stop approximations with recorded RMS (see `fit_gradient`),
not sampled LUTs; glow/rim treatments are parametric re-builds. Kana menu
rows are traced letterforms, same WIP status as everything else.

## 3. Recommendation: SDF-atlas first, TTF chain already covers the rest

| Option | Plug-in seam | Verdict |
|---|---|---|
| **(a) SDF-atlas pipeline** (bake whole-sheet vectors to signed-distance cells at build, sample in the HUD shader) | `HudAtlas::upload` gains the SDF sheet; `number()`/`glyph()` keep their signatures — same `hud_atlas.h` boxes (cut glyphs out of `sheets/` the same way), same `hudDigitRun` layout the `hud_sprite_table` test pins; only the texture bytes and the sampler change. `ready()` fallback (text HUD) is untouched | **Recommended for the digit rows + LIMIT/MAX/words.** Exact letterforms (traced, not approximated), one pipeline for all scales, tiny seam, and the SDF smoothstep absorbs the 1px threshold rims. Next: a `bake_sdf.py` (sheet SVG → distance field via rsvg renders) + one `pushSdfSprite` path in `ui/sprite.h` + a shader branch |
| **(b) stb_truetype-loaded TTFs** (Nunito Black Italic / M PLUS Rounded 1c Bold fetched like Noto into `third_party/fonts/`) | `TextLayer::loadFontChain` — zero new code, CJK-TEXT.md option B already decided and landed | **Recommended for everything unbounded**: chat names, result/report text, stings-if-ever-dynamic. Rejected for the fixed HUD lettering: Nunito is close but visibly not the game's cut (width, terminals), and the chrome/gradient/rim treatments would still need custom layering per element |
| **(c) hand/SVG paths as runtime textures** (rasterize per size) | `HudAtlas::draw/cell` with a second sheet set | Rejected as the steady state: per-size raster Uploads + no SDF smoothing = the blur problem returns at every new resolution. The SVGs stay as the *source* plates (checked in, reviewable), not the runtime |

Concrete next steps, in order: (1) `bake_sdf.py` + SDF sampler behind the existing `ready()` fallback (no parity risk — fallback stays until the SDF render matches); (2) hand-tune pass in an SVG editor over `sheets/` (see WIP status in §2); (3) fetch Nunito Black Italic + M PLUS Rounded 1c Bold into `third_party/fonts/` for label-prototype work only; (4) leave the P03 badge and name grid as atlas art (E6 widget renders cells, TTF renders names).

## 4. Open questions (no Wine/GPU needed for any of this)

1. `FUN_00431b50` recolor question (SPEC §6 Q5: print's small `%` renders white, no white-small set in P00) — the trace program assumes ink color is a draw-time tint; if a fifth set exists the base boxes change. One band scan (y210–250, y308–330) settles it.
2. The print `com` word's sheet (SPEC §6 Q7: P01 blue/red tag vs system.cnv row) — decides which `com` art gets traced.
3. Whether `FUN_00431ce0`'s `%` draw (at `x + scale*leading`) wants the traced `%` cell or a re-hung advance — layout, not lettering; `hudDigitRun` already pins the arithmetic.
4. Blocked-with-reason: none. Nothing here needed the game running (all offline), and no GPU capture was used.
