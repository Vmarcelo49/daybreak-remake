# WebGPU port completion plan (post-cutover record)

This is the remaining-work plan for finishing the Daybreak renderer port on
`main`. The product is `remake/foundation/` (SDL3 + WebGPU, C++17,
`CMAKE_CXX_STANDARD 17`, 13 ctest tests). It covers foundation-adjacent
systems only. Full gameplay/netplay and story mode are separate decisions
and are not claimed here. `webgpu-mvp/` and `webgpu-spike/` were deleted in
the Phase 5 cutover (2026-10-02) after the port work they informed landed;
`remake/src/` was deleted in the same cutover, as was the DX9 tree.

## Non-goals

- No verification on macOS by us. Code should stay portable where that is free,
  but macOS execution is explicitly out of scope unless external users provide it.
- No edits outside the track's owner files without the parent. (History: a
  separate `remake/src/` tree existed before the Phase 5 cutover and was
  owned by another agent; it has since been deleted.)
- No game data committed. Local extracted game files stay ignored.
- No DX9 tree. DX9 was dropped in the Phase 5 cutover (2026-10-02); the A/B
  reference is now the banked evidence in `remake/tests/parity-baseline/`
  plus the original's prints in `remake/docs/reference/`, not a buildable
  binary. (History: D2 kept DX9 buildable as the A/B reference until then.)

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
- Shared integration files are parent-owned: `CMakeLists.txt`,
  `src/main.cpp`, `README.md`, top-level decisions. Landed seams already
  wire `--audio-test`/`--audio-file`/`--input-test`/`--hud-test`/`--screen`/
  `--versus`/`--match` through `src/main.cpp` into `foundation_media`,
  `foundation_game` and `foundation_gameplay`.
- One `#if` per real platform difference; no speculative compatibility shims.
- Proof beats prose: every completed workstream ends with commands run, observed
  output, artifacts, and explicit “not verified” items.

## Track R — renderer parity toward the D2 gate (in progress on main)

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

## Track U — 2D/UI/HUD layer (landed in skeleton; fidelity open)

Owner files: new `src/ui/*`, `src/shaders/ui_*.h`, `docs/UI-*.md`.
Read-only elsewhere except reported integration patches.

Status (post-cutover): the screen stack and HUD composition have landed —
`src/ui/screen.{h,cpp}` + `screen_title` with `--screen=title` wired in
`src/main.cpp`, and the HUD composer with the atlas-art battle path.
What remains is fidelity work, not scaffolding:

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

## Track W — web runtime assets and pixel verification (fetch + cache landed)

Owner files: `docs/WEB-ASSETS.md`, new web-asset runtime helpers if needed,
browser verification notes. Parent retains `CMakeLists.txt` and `main.cpp`
integration until the design is accepted.

Status (post-cutover): the fetch→`/packs/` loader plus IDBFS persistence
have landed (`src/platform/web_pack.cpp` via `scripts/make_pack.py`,
`?pack=` handling in `src/main.cpp`). What remains is the release
hardening below:

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

## Track M — media and input modules (backends landed; callers pending)

Owner files: new `src/audio/*`, `src/input/*`, `docs/MEDIA-*.md`, isolated tests.
`main.cpp` integration has landed (`--audio-test`/`--audio-file`,
`--input-test` via `runAudioTest`/`runInputTest`).

Status (post-cutover): `src/audio/audio_engine.cpp` +
`src/input/input_backend.cpp` compile into `foundation_media` and the
harness seams above exercise them. What remains is caller-side work, not
the backends themselves:

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

## Merge order (post-cutover: complete)

1. Independent modules and docs landed: `src/ui/*`, `src/audio/*`,
   `src/input/*`, web runtime helpers, shaders, per-track docs.
2. Parent integrated the shared seams: `CMakeLists.txt`, `src/main.cpp`,
   README, top-level verification table.
3. Parent reruns the three-target matrix and asset captures before each commit.
4. Retirement of `webgpu-mvp/` and `webgpu-spike/` is done — both trees
   were deleted in the Phase 5 cutover, as were `remake/src/` and the DX9
   tree.

## Current checkpoint (on `main`)

- Linux and Windows/Wine render textured stages/characters/weapons with
  byte-identical captures where claimed.
- Web builds and runs; the fetch→`/packs/` loader with IDBFS caching
  resolves real scenes, and local preload renders a real character scene
  with textures resolved. Production asset hardening (OPFS alternative,
  range requests, BGM/movie streaming) remains open.
- Screens, HUD composition and the playable `--match` simulation have
  landed (`src/ui/screen*.{h,cpp}`, HUD composer, `src/gameplay/*`).
- D2 gate is not passed: the frame must still match the original's prints
  in `remake/docs/reference/` (checked against the banked evidence in
  `remake/tests/parity-baseline/`), which needs effects, the remaining 2D
  fidelity and the game camera.
