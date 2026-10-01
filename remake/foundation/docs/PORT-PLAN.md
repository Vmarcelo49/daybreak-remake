# WebGPU port completion plan

This is the remaining-work plan for finishing the Daybreak renderer port on
`feat/webgpu-groundwork`. It covers foundation-adjacent systems only. Full
gameplay/netplay, story mode, and DX9 removal are separate decisions and are not
claimed here. `webgpu-mvp/` and `webgpu-spike/` remain untouched retirement-bound
prototypes until the port work they informed is complete.

## Non-goals

- No verification on macOS by us. Code should stay portable where that is free,
  but macOS execution is explicitly out of scope unless external users provide it.
- No edits to `remake/src/` by this track. Another agent owns that tree; the
  foundation may read DX9/remake behavior as reference, but integration happens on
  the foundation side.
- No game data committed. Local extracted game files stay ignored.
- No DX9 removal. D2 keeps DX9 buildable as the A/B reference until parity passes.

## Standing rules

- Preserve the layering contract: `gpu/` includes only `webgpu.h`; `platform/`
  knows nothing about WebGPU except `surface.{h,cpp}`; `render/` is the other
  permitted WebGPU consumer.
- Keep the backend swappable: no Dawn-only or wgpu-only behavior in shared code
  except the small documented `#if` differences.
- Verify natively where assets exist: Linux and Windows/Wine offscreen captures,
  coverage/luminance numbers, byte-identical checks where claimed.
- Web asset work stays local-only. The browser can run preloaded verification data,
  but no copyrighted data enters the repository.
- Shared integration files are parent-owned until a track is ready to merge:
  `CMakeLists.txt`, `src/main.cpp`, `README.md`, top-level decisions.
- One `#if` per real platform difference; no speculative compatibility shims.
- Proof beats prose: every completed workstream ends with commands run, observed
  output, artifacts, and explicit “not verified” items.

## Track R — renderer parity toward the D2 gate

Owner files: `src/render/*`, `src/shaders/model*.h`, `docs/RENDER-*.md`.
Read-only elsewhere except reported integration patches.

1. R1 — material technique routing. Replace/augment the provisional shadow-name
   heuristic with the real effect/material technique signal where it is actually
   known. Keep the name heuristic only for explicitly unverified cases, and label it.
2. R2 — effect passes. Implement additive blending, unculled passes, and effect
   draw ordering/sorting as required by observed effect assets. Add representative
   trail/aura captures; do not claim all effects.
3. R3 — decal correctness. Prevent double-darkening where decals overlap, matching
   the DX9 stencil behavior if required; verify shadow cards against a DX9 frame,
   not merely that multiply blending is enabled.
4. R4 — texture/material fidelity. Add mipmaps if sampling needs them; wire
   specular/emissive/power only if the original shades them, otherwise document why
   they stay parsed-but-unused.
5. R5 — camera path. Keep the current framing heuristic for verification captures,
   but add the game/arena camera path needed for an actual in-game frame. The D2
   gate is a matching frame, not a pretty capture.

Acceptance: representative stage/character/weapon/animation captures, byte-identical
Linux/Windows where claimed, plus explicit notes for effect cases that remain out
of scope.

## Track U — 2D/UI/HUD layer

Owner files: new `src/ui/*`, `src/shaders/ui_*.h`, `docs/UI-*.md`.
Read-only elsewhere except reported integration patches.

1. U1 — sprite/quad batch. Textured 2D quads with alpha blending, texture upload
   from CNV/BMP-backed images, scissor/viewport-safe coordinates.
2. U2 — text. Replace the D3DX font path with a portable font/text renderer and
   verify representative HUD strings/labels.
3. U3 — HUD composition. HP/LIMIT-style bars, meters, labels and layout rules from
   the DX9 reference; provide captures/metrics, not just code.
4. U4 — debug and fallback UI. Minimal diagnostics path that works when assets or
   fonts are unavailable.

Acceptance: HUD elements render in the same frame pipeline verification captures,
with pixel/coverage evidence where headless capture supports it.

## Track W — web runtime assets and pixel verification

Owner files: `docs/WEB-ASSETS.md`, new web-asset runtime helpers if needed,
browser verification notes. Parent retains `CMakeLists.txt` and `main.cpp`
integration until the design is accepted.

1. W1 — runtime delivery design. Compare embedded subset, Emscripten preload
   packaging, HTTP fetch/streaming, and IndexedDB/cache behavior. Choose the
   production path for a real release, not only verification.
2. W2 — browser asset proofs. Extend web verification beyond console/scene stats
   toward pixel evidence, within headless-canvas limits; use offscreen readback or
   another supported capture method where available.
3. W3 — web asset constraints. Document size/memory, CORS/HTTPS/localhost behavior,
   subset strategy, licensing/data handling, and what still cannot run in-browser.

Acceptance: a real release asset path is specified and the verified subset is
narrow; local-only test data remain out of git.

## Track M — media and input modules

Owner files: new `src/audio/*`, `src/input/*`, `docs/MEDIA-*.md`, isolated tests.
No `main.cpp` integration until parent accepts the interfaces.

1. M1 — audio inventory and backend. Survey SFX/BGM/movie-audio needs from the
   remake reference, then implement SDL3 audio playback/streaming behind a small
   interface. Verify Linux/Windows/web with attention to browser autoplay unlock.
2. M2 — video decision. Survey `.mpg` playback needs and decide implement/stub;
   do not silently omit it.
3. M3 — input mapping. Keyboard/gamepad mapping behind a small interface, with
   web gamepad caveats documented. No gameplay wiring here.
4. M4 — media/input tests where deterministic: decode/stream/format/unit checks,
   not subjective playback claims.

Acceptance: working modules with interfaces, tests/metrics, and explicit platform
caveats; integration happens through the parent.

## Merge order

1. Independent modules and docs land first: new `src/ui/*`, `src/audio/*`,
   `src/input/*`, web runtime helpers, shaders, per-track docs.
2. Parent integrates shared seams: `CMakeLists.txt`, `src/main.cpp`, README,
   top-level verification table.
3. Parent reruns the three-target matrix and asset captures before each commit.
4. Retirement of `webgpu-mvp/` and `webgpu-spike/` happens only after the port
   work they informed is complete and merged.

## Current checkpoint

- Linux and Windows/Wine render textured stages/characters/weapons with
  byte-identical captures where claimed.
- Web builds and runs; local preload renders a real character scene with textures
  resolved. Web pixel proof and production asset delivery remain open.
- D2 gate is not passed: the frame must still match the original, which needs
  effects, the 2D pass and the game camera.
