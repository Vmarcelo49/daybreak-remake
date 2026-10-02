# UI layer (sprite batch, atlas HUD, front-end screens, text)

The 2D/UI/HUD pass: textured quads, the battle HUD's `.cnv` atlas composition,
the front-end screen stack, the CJK-capable text layer and fallback diagnostics.
It is built as `foundation_ui` by `CMakeLists.txt:89-105` and linked into
`foundation_demo`; the seams it hooks are `--hud-test` and `--match`/`--versus`
captures, and `--screen=<id>` for menus (UI-INTEGRATION.md).

Files (the track's whole surface):

| File | Contents |
|---|---|
| `src/ui/sprite.h` / `sprite.cpp` | `SpriteRenderer` batch + pixel math (`barFillWidth`, `clampClip`, `clipToScissor`, `pixelsToNdc`) |
| `src/ui/font.h` / `font.cpp` | Embedded 5x7 bitmap font: measure, layout, atlas build (no WebGPU, no OS fonts) |
| `src/ui/hud.h` / `hud.cpp` | `HudState`, `computeHudLayout`, `HudComposer`: the original's atlas HUD when its sheets resolve, the DX9 text/bars body (the mapping table below) only as the no-atlas fallback |
| `src/ui/hud_atlas.h` / `hud_atlas.cpp` | `HudAtlas` + the one .cnv sheet path (`uploadCnvSheet`): `kHudSprites`/`kHudFonts` transcribed from FUN_00642510/FUN_00431a50, and the FUN_00655d60 / FUN_00645250 / FUN_00655830 / FUN_00431b20 primitives |
| `src/ui/text.h` / `text.cpp` | `TextLayer`: TrueType/CJK rasterization, GDI-metric chain, `\cRRGGBB` runs |
| `src/ui/screen.h` / `screen.cpp` | `ScreenId`, `Screen`, `ScreenStack`, the 25-frame fade, `makeScreen`, `parseScreenId` |
| `src/ui/screen_title.h` / `screen_title.cpp` | scene 1: back00/logo/title sheets and the cursor machine, FUN_00410d60/FUN_00410f60/FUN_004114f0 |
| `src/ui/fallback.h` / `fallback.cpp` | `FallbackOverlay` + `buildDiagLines`/`computeDiagPanel`: asset-less diagnostics panel with host-side sizing; no target wires it into a frame yet |
| `src/shaders/ui_wgsl.h` | Pixel-space textured-quad WGSL (`shaders::kUiWGSL`) |

## Source of the layout (read-only; the DX9 tree is gone)

The constants come from the original, not from a buildable DX9 tree:
`BATTLE-HUD-SPEC.md` carries the FUN_ addresses, the .rdata anchor table
`0x6a4c90..0x6a4cd8` and the print measurements, and
`FUN_00644150`/`FUN_00643230`/`FUN_0063a130`/`FUN_00642510` are in
`research/decompiled/`. The Arial (D3DXFont 22 px bold) labels + `D3DXSprite`
bars body this file drew before the atlases landed is kept only as the
no-game-data fallback, transcribed from the DX9 remake's call sites as recorded
in git history (`remake/src/core/scenes.cpp`, deleted in `5a63db3`) — `bar()`
clamps the fraction, draws the back quad at full width, then the fill truncated
to `(int)(w * frac)`.

- CNV images decode through the same header quirk the foundation documents
  (`cnv.h`): payload size beats declared bpp. `SpriteRenderer::addTexture`
  takes decoded RGBA8 top-down (stride `w*4`) — exactly `xm::CnvImage::rgba` —
  so no conversion sits between decode and upload.

HUD mapping (DX9 call site → this layer):

| DX9 | Here |
|---|---|
| `text(20,8,…"%.0f%%")` / `text(20,34,…"LIMIT …")` and `W-120` mirrors | `HudRects::balloonL/limitL/balloonR/limitR`, `HudState::balloon/limit` |
| `text(W-220,H-104,"%d MAIN%s")` + `bar(…,180,12,main_frac(),90,140,255/20,20,30)` | `mainText/mainBar`, `mainWhole/mainFrac/reloading` |
| `CHARGE` pair + `charge_hold_frac` tier bar at `H-118` | `chargeText/chargeBar/holdBar`, `holdColor` = `kHudTierRed/Yellow/Idle` |
| `text("HP")` + `bar(W-180,H-140,160,14,hp/100,…255,220,60…)` | `hpText/hpBar`, `hp` |
| Hypermode label variants (`"%.0fs"` / `"READY (S)"` / name) + aura/grey bar | `hyperName/hyperGauge/hyperActive/hyperReady/hyperSecondsLeft/hyperAura` |
| `STAMINA` pair at `W/2-100`, shown for Run/Guard/Jump | `staminaVisible/staminaFrac` |
| `centered(220,100,…,"KO!")` while `elapsed < stingUntil` | `koVisible`, `koCenterX/koY` |
| `text(4,4,…,"0")` | `markerText` — the unlabelled yellow "0" is reproduced in the text fallback (hud.cpp:421; all three banked frames carry it), deliberately not in the atlas composition |

The in-battle HUD is 100% sprite art — every bar, number and label, including the
boxed `適当` command label (BATTLE-HUD-SPEC.md §4). The CJK/text layer below is
for menus, the result quote, chat and story mode; `compose()` draws no font glyph
in battle while the atlases are up.

## Conventions

- **Pixels everywhere.** Top-left origin, y down — the DX9 `XYZRHW`
  convention — so surveyed constants transfer verbatim. `ui_wgsl` maps to NDC
  in-shader; `pixelsToNdc` mirrors it for CPU-side math.
- **Immediate mode.** The batch, composer and overlay hold no clock and no
  accumulator: the caller re-pushes every frame from live state, which is what
  makes the layer fit variable-delta frames (pose/animation time never lives
  here). FIFO pacing stays the swapchain's job; the UI pass adds no present.
- **Compose, don't clear.** `SpriteRenderer::render` opens its pass with
  `LoadOp::Load` and no depth attachment, drawing over the 3D frame already in
  the view — the DX9 order (HUD after 3D, same scene). An empty batch records
  nothing, leaving the frame untouched.
- **Blending** is `SrcAlpha`/`OneMinusSrcAlpha` on the pipeline: the
  `D3DXSPRITE_ALPHABLEND` + `UIImage` quad blend.
- **Scissor, not faith.** Per-quad `UiClip` resolves through `clipToScissor`
  to `SetScissorRect`, keeping bars/panels inside their frames on resize.
  WebGPU scissor/viewport origin is top-left (D3D convention) on every backend,
  so no per-backend flip exists — verified empirically, see `UI-VERIFY.md`.
- **One texture format.** RGBA8 for sprites, the font atlas (white with
  coverage in alpha) and the 1x1 white solid fallback: one pipeline draws
  bars, sprites and glyphs.

## Layering and portability

`ui/` consumes `webgpu.h` plus `gpu::createShaderModule` / `gpu::createBuffer`
exactly as `render/` does — the third WebGPU consumer next to `gpu/` itself,
following the `render/` precedent in `README.md`'s layering rules.
`foundation_ui` links `foundation_assets` (the CNV decoder and `assetSource()`),
`foundation` (the gpu helpers) and, privately, `third_party/stb` for the TrueType
rasterizer; `glm` arrives through `foundation_assets`.

No backend `#if` appears in `ui/`: the code never presents (the one real
`wgpu-native` vs Dawn difference lives in `gpu.cpp`'s `endFrame`), uses only
core buffer/texture/pass calls, and takes the viewport from the caller each
frame. `font.*` is WebGPU-free by construction and unit-testable without a
device.

## Deliberate cuts

- **CJK text.** Landed, not cut: `ui/text.{h,cpp}` rasterizes one fetched OFL face
  in-process (stb_truetype; `remake/scripts/fetch_deps.sh` pins Noto Sans CJK JP
  and Liberation Sans Bold) and ports FUN_0065d870/FUN_0065d9a0/FUN_0065dad0's
  walker (Shift-JIS in the original, UTF-8 here) and `\c` colour codes — the
  layer the menus, the result quote, chat and story mode use (docs/CJK-TEXT.md
  §5, option B, 2026-10-02; tests/text_test.cpp). The 5x7 bitmap in `font.*`
  stays as the no-font fallback, where an unsupported codepoint still advances
  as `?`.
- **No animation/tween state.** KO sting visibility, hold-meter tiers and gauge
  smoothing are caller clocks; the composer is a pure function of its args.
- **RGBA8 only, one decoder.** `SpriteRenderer::addTexture` takes decoded RGBA8
  (stride `w*4`), and the .cnv → sheet half is `ui/hud_atlas.cpp`'s
  `uploadCnvSheet`, which asks `assetSource()` for the bytes and decodes through
  `xm::decodeCnvImage` (assets/cnv.h) — the foundation's one CNV decoder, which
  is why `foundation_ui` links `foundation_assets` publicly.
- **No capture helper in the library.** Offscreen readback stays with
  `SceneRenderer::capture`/`captureUi` and its `UiHook`, which is how the demo
  composes HUD-in-capture (`--hud-test`, `--match`) and menus (`--screen`);
  `ui/` never opens a readback of its own.
