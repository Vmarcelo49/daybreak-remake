# UI layer design (Track U, library-ready, unintegrated)

Library code for the 2D/UI/HUD pass: textured quads, portable text, battle HUD
composition and fallback diagnostics. It compiles against the same headers as
`render/` but is **not wired into `CMakeLists.txt` or `main.cpp`** — the
integration snippet lives in `UI-INTEGRATION.md` for the parent to apply.

Files (the track's whole surface):

| File | Contents |
|---|---|
| `src/ui/sprite.h` / `sprite.cpp` | `SpriteRenderer` batch + pixel math (`barFillWidth`, `clampClip`, `clipToScissor`, `pixelsToNdc`) |
| `src/ui/font.h` / `font.cpp` | Embedded 5x7 bitmap font: measure, layout, atlas build (no WebGPU, no OS fonts) |
| `src/ui/hud.h` / `hud.cpp` | `HudState`, `computeHudLayout`, `HudComposer` (battle HUD) |
| `src/ui/fallback.h` / `fallback.cpp` | `FallbackOverlay`: asset-less diagnostics panel |
| `src/shaders/ui_wgsl.h` | Pixel-space textured-quad WGSL (`shaders::kUiWGSL`) |

## DX9 reference survey (read-only, nothing modified)

- `remake/src/render/hud.h` / `hud.cpp` — battle HUD via `D3DXFont` (Arial 22 px
  bold) + `D3DXSprite` bars. `bar()` clamps the fraction, draws the back quad
  at full width, then the fill truncated to `(int)(w * frac)`; `begin()` uses
  `D3DXSPRITE_ALPHABLEND`; text goes through `DrawTextA` with `DT_NOCLIP`.
  ASCII-only by admission (Wine often lacks CJK fonts); the KO sting is `"KO!"`.
- `remake/src/render/ui_image.cpp` — image quads as `XYZRHW` + `DIFFUSE` +
  `TEX1` triangle strips with lighting and Z disabled and
  `SRCALPHA`/`INVSRCALPHA` blending.
- `remake/src/core/scenes.cpp` (~lines 818–893) — the actual battle layout this
  track reproduces: balloon % + LIMIT top corners, MAIN/CHARGE + HP
  bottom-right, hypermode gauge bottom-left, contextual stamina, centred KO
  sting. Every anchor and colour in `hud.h` is transcribed from those call
  sites; the mapping table is below.
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
| `text(4,4,…,"0")` | **Omitted**: single-character debug residue, no gameplay meaning |

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
following the `render/` precedent in `README.md`'s layering rules. The proposed
link is `foundation_ui → foundation + glm`, mirroring `foundation_render`.

No backend `#if` appears in `ui/`: the code never presents (the one real
`wgpu-native` vs Dawn difference lives in `gpu.cpp`'s `endFrame`), uses only
core buffer/texture/pass calls, and takes the viewport from the caller each
frame. `font.*` is WebGPU-free by construction and unit-testable without a
device.

## Deliberate cuts

- **CJK text.** Out of scope like the DX9 ASCII-only stand-in: unsupported
  codepoints advance as `?` so layout never shifts. A shaped-text shaper would
  be a separate track, not a quiet extension of this one.
- **No animation/tween state.** KO sting visibility, hold-meter tiers and gauge
  smoothing are caller clocks; the composer is a pure function of its args.
- **No texture-format negotiation.** RGBA8 only; CNV/BMP decoding stays with
  the asset layer, which already produces that layout.
- **No capture helper in the library.** Offscreen readback needs the
  instance-event loop that `gpu::readBuffer` owns; duplicating it in `ui/`
  would split that knowledge. Verification captures compose `render()` with
  `gpu::readBuffer` from the caller (the scratch test does exactly this).
