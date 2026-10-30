# UI verification — historical Track U scratch run

This records the pre-integration scratch verification, not the current UI status.
The checks ran from a disposable `/tmp/ui_verify` directory and did not change a
shared build file. At that point they compiled selected `src/ui/*` files directly
against `webgpu.h`; the UI was subsequently integrated into `daybreak`
(`CMakeLists.txt:99-132`, `src/main.cpp:5091-5176,6207-6212`).

## Commands (exact)

```bash
F=$(git rev-parse --show-toplevel)
W=$F/build/linux/_deps/wgpu-linux-x86_64-release-src/include
g++ -std=gnu++17 -DWEBGPU_BACKEND_WGPU -Wall -Wextra \
  -I$F/src -isystem $W -isystem $W/webgpu \
  -o /tmp/ui_verify/ui_check /tmp/ui_verify/main.cpp \
  $F/src/ui/sprite.cpp $F/src/ui/font.cpp $F/src/ui/hud.cpp \
  $F/src/ui/fallback.cpp $F/src/gpu/gpu.cpp \
  -L$F/build/linux -lwgpu_native -Wl,-rpath,$F/build/linux
cd /tmp/ui_verify && ./ui_check
```

(`gpu.cpp` links for `gpu::createShaderModule`/`createBuffer`, the same
dependency the proposed `foundation_ui → foundation` link declares.)

## Observed output

```
host checks done
HOST OK
gpu: backend=Vulkan
batch: 78 quads, 0 dropped
coverage: 72565 px of 120000 (60.47%) luminance 0.067..1.000
wrote /tmp/ui_verify/out.ppm
RESULT: ok
```

Zero warnings under `-Wall -Wextra`. Before the fix, the run caught a real
bug: the sampler descriptor left `maxAnisotropy` at 0 and wgpu-native's
validator aborted `wgpuDeviceCreateSampler` (`Invalid anisotropic clamp: 0.
Must be at least 1`); `sprite.cpp` now sets 1 like the scene renderer.

## What was checked

Host-side (no device, deterministic):

- `barFillWidth`: halves, clamps both ends, sub-pixel fractions draw nothing,
  zero width — the DX9 `(int)(w*frac)` truncation reproduced exactly.
- `pixelsToNdc`: corners map to (∓1,±1), centre to origin — agrees with the
  `ui_wgsl` mapping by construction.
- `clipToScissor`: disabled clip yields the viewport; negative/overflowing
  rects clamp; fully-off and zero-area clips drop the quad.
- `measureText`/`glyphSupported`/`utf8Next`: exact monospace extents
  (`"MAIN"` = 24 px at scale 1), multiline extents, empty string, CJK and
  malformed bytes advance exactly one cell as `?`.
- `layoutText`/`layoutTextCentered`: one quad per glyph, 15x21 px glyphs at
  scale 3, UVs inside the atlas, centred block starts at `centerX - width/2`.
- `buildAtlasRGBA`: 128x48 RGBA, ink-pixel count sane, `'A'` bar row inked,
  space cell empty, glyph RGB white (tint carries the colour).
- `computeHudLayout`: 800x600 anchors equal the surveyed DX9 constants
  (balloon `(20,8)`/`(W-120,8)`, main bar `(W-220,H-80,180x12)`, HP bar
  `(W-180,H-140,160x14)`, hyper bar `(20,H-64,180x12)`, stamina centred,
  KO at `(W/2,220)`); a 400x300 viewport tracks.
- `buildDiagLines`/`computeDiagPanel`: healthy 3-line form, error shows its
  first line truncated to 60 chars, panel pads the longest line, tiny surfaces
  clamp the panel instead of covering the frame.

GPU (headless wgpu-native → Vulkan/RADV, no surface, 400x300 offscreen):

- `SpriteRenderer::init`, font atlas upload, and a synthetic 8x8 checker
  upload (standing in for a decoded CNV) all succeed; 78-quad HUD batch records
  with 0 drops.
- Orientation probe (white 20x20 at pixels 10,10) reads back at top-left:
  the y-flip is correct.
- Scissor probe (full-frame red, left-half clip) paints only the left half:
  `SetScissorRect` needs no per-backend flip, as designed.
- Composed battle HUD (balloon/LIMIT, MAIN/CHARGE + hold tier, HP, active
  OYASHIRO gauge, stamina, KO sting) + checker sprite read back at 60.47%
  coverage, luminance 0.067..1.000; `/tmp/ui_verify/out.ppm` shows corner
  labels, bottom bars, centred stamina and the corner sprite in place.

## Historical gaps (status at the scratch run)

These are not statements of current verification status: the run predated
in-engine HUD/menu integration and the later CJK/runtime-caption work. Current
cross-target, live-run, font, and visual-verification limits are tracked in
[`RELEASE-CHECKLIST.md`](RELEASE-CHECKLIST.md) and the per-target build records.

- No in-engine frame, HUD-over-3D capture, or byte-identical target pair was
  checked by this scratch run.
- Only wgpu-native/Vulkan executed; web/Dawn and Windows/Wine were not exercised
  by this scratch test.
- Glyph aesthetics and colour fidelity were judged numerically, not against the
  reference images.
- This run used the bitmap layer only; CJK support was not exercised.
- No frame-time or performance claim was measured.
