# Project decisions (binding)

Recorded 2026-10-01. These override any conflicting notes elsewhere in
`docs/` or roadmaps. Update this file — not scattered
comments — when a decision changes.

## D1 — `mvp/` retired; `remake/` is the only codebase

- The old `mvp/` tree (`<project>/mvp/`) was frozen, ported per
  `docs/port-from-mvp-plan.md`, then **deleted** (2026-10-01). All new
  code is written in `remake/foundation/` (`src/`, `tests/`, `scripts/`) —
  the DX9 `remake/src/` was deleted in the Phase 5 cutover (D2 reversal).
  `remake/{scripts,tools,assets,docs}/` keep the surviving tooling and
  evidence.
- What survives from `mvp/`: the relocated tooling
  (`tools/asset-tools/`, `tools/hook-tracer/`, `assets/shaders/`),
  the ported engine/scene/texture work, and the RE constants now
  cited in code comments. The decomp translations themselves live on
  in `research/decompiled/` and `research/binary_data/` — consult those,
  not `mvp/`, for `FUN_xxxxxx` provenance.
- Rationale: two active codebases split effort and drift; the remake
  (real gameplay stack) is the strictly better foundation
  (see comparison notes in chat, 2026-10-01).

## D2 — The renderer migrated to WebGPU; DX9 was the reference until parity (reversed 2026-10-02 — see the reversal below)

> **Reversed 2026-10-02.** The gate passed against the corrected visual
> target (the original's prints, plan §6a) and DX9 was dropped in the
> Phase 5 cutover; the reversal, with measured evidence, is at the end of
> this section. The text below is the decision as taken, kept as the
> record.

- **Supersedes the 2026-10-01 text** that read "DirectX 9 stays. No
  renderer migration." and claimed dropping DX9 was *not possible*. That
  claim was tested and disproven (evidence below), so the direction is
  now the opposite one.
- Target: **SDL3 + `webgpu.h`**, with the backend chosen per platform —
  **wgpu-native** on native targets, **emdawnwebgpu** on the web
  (`foundation/CMakeLists.txt:17`). One `CMakeLists.txt` serves all three
  targets; the web/native split is confined to the platform layer and the
  frame loop (`foundation/src/platform/{surface,web_pack}.cpp`,
  `foundation/src/gpu/gpu.cpp`, plus the web asset bootstrap in
  `foundation/src/main.cpp:1732`).
- **Record — superseded 2026-10-02 (reversal below).** The pre-cutover
  text read: "DX9 is not deleted … until it passes, DX9 is the shipping
  renderer." No longer true: the cutover deleted `remake/src/`,
  `remake/CMakeLists.txt`, `remake/build.sh` and `remake/cmake/`
  (`foundation/docs/FULL-REPLACEMENT-PLAN.md` §8), and the A/B reference
  is the frozen `tests/parity-baseline/` bank plus the original's prints.
- Evidence, as recorded at decision time in the now-deleted prototype
  (`webgpu-spike/FINDINGS.md`, archived in `3fea431`, deleted in `5a63db3`
  — read it with `git show 3fea431:webgpu-spike/FINDINGS.md`):
  - Linux/Wayland, real GPU, wgpu-native: surface, capabilities,
    configure, 60/60 frames presented, FIFO available.
  - Web (Emscripten + emdawnwebgpu): `RESULT: ok` in Chromium; the
    browser presents, and FIFO is the only present mode it offers.
  - Windows: Dawn linked from MinGW and ran; wgpu-native cross-compiled
    earlier the same day rendered under Wine byte-identically to Linux.
  - macOS: **unverified** — no Mac available. Dawn ships macos x64 and
    aarch64 prebuilts and `sdl3webgpu` has the Metal path, but nothing
    has been executed. Do not claim it works.
- Spike-era finding, kept in the record: Dawn (at least the
  `chromium/7187` prebuilt) rejects `WGPUSurfaceSourceWaylandSurface`, so
  it was a poor native backend on a Wayland desktop; wgpu-native handles
  Wayland and is the native backend (`foundation/CMakeLists.txt:17`). Not
  a live constraint — Dawn is only the web backend now.
- Rationale: D3DX9 is deprecated, drags `d3dx9_43.dll` and Wine-specific
  behaviour, and blocks the Linux/macOS/web targets this port exists to
  reach.

### D2 reversal — 2026-10-02: the gate has passed, DX9 is dropped

- **Why now.** The gate D2 named was "a matching in-game frame", and the
  visual target was corrected (plan §6a, owner) to the **original's own
  screens**, not the unfinished DX9 remake's frames. The WebGPU path now
  renders those:
  - title screen **RMSE 0.015970** against `docs/reference/title-menu.webp`
    (ink IoU 0.975 items / 0.980 logo / 0.974 selected row — the print is
    itself a capture at (+1,+5), `tests/title_bands.py:9-12`, and the masks
    land at (0,0) after that correction; residual is the print's own ~2%
    darkening plus webp ringing);
  - battle frame with the camera fitted from the prints: player pixel
    height **314 vs the print's 313** (0.997 of target), residuals 0.0 px on
    the four measured rows that over-determine the geometry;
  - HUD element bands **0.33–0.40 → 0.09–0.19** against
    `battle-hud.webp` (hp 0.3604 → 0.1118, main 0.3788 → 0.0951, charge
    0.4038 → 0.0944, fan gauge 0.3867 → 0.1910, every band now better than
    the 0.2755 scene-only floor).
- **What was dropped.** The DX9 tree and its build: `remake/src/`,
  `remake/CMakeLists.txt`, `remake/build.sh`, `remake/launch_daybreak.sh`,
  `remake/cmake/`, the DX9 visual-suite fixtures under `remake/tests/`, and
  the `webgpu-mvp/` / `webgpu-spike/` prototypes. Full list and what was
  deliberately kept: `foundation/docs/FULL-REPLACEMENT-PLAN.md` §8.
- **What replaces the A/B reference.** (a) The **banked reference bank**
  `tests/parity-baseline/` (33 cases / 36 captures, 47 logs, manifest +
  hashes) — now a **frozen archive**: `regen.sh` needs the deleted
  `build/daybreak.exe`, so it documents provenance, it does not regenerate;
  and (b) the original's **23 prints** in `docs/reference/`, which are the
  appearance target.
- **The DX9 behavioural oracle's role is retained as records.** The
  gameplay trace A/B (`compare_match_traces.py`) still runs against the
  banked DX9 logs, and the DX9 remake's quirks the port deliberately pins
  (the one-way guard state, the unclamped camera A/B) stay documented and
  tested. What ends is the ability to produce *new* DX9 frames: any new
  behavioural claim now has to come from the original.
- Rollback point: tag `pre-webgpu-cutover` (`37ed31d`), kept until the
  release after the cutover. This supersedes the "DX9 is not deleted"
  bullet above; everything else D2 records (backend choice, per-platform
  verification state, macOS unverified) still stands.

## D3 — Original `.X` files are used directly. No conversion pipeline.

- **Unchanged by D2.** The asset *layer* is the same on every backend:
  `loadStage`/`loadCharacter`/`loadWeapon` consume the originals as
  shipped — the foundation decodes all 728 `.X` files (three encodings),
  the `.cnv` images and the Shift-JIS texture references with no
  conversion step (`foundation/src/assets/xmodel.h`, `cnv.h:61`; the
  corpus proof — 728/728 `.X`, 5051/5051 `.cnv` — is archived in
  `3fea431:webgpu-mvp/README.md`, and `.X` is re-measured in
  `foundation/docs/RENDER-MATERIALS.md:36,43`), for exactly the reasons
  below. Delivery differs — native reads the `.dat` bundles/disk, the web
  build fetches per-pack files from an extracted tree
  (`foundation/src/platform/web_pack.cpp`, `foundation/scripts/make_pack.py`)
  — and a browser run with game data is still unverified
  (`ROADMAP-PENDING.md` §G1).
- Character/stage/collision meshes ship as `.X` in three encodings
  (`0302txt`, `0303bin`, `0303bzip`); the semantics to reproduce are the
  original loader's (`D3DXLoadMeshHierarchyFromXInMemory` frame trees,
  `ID3DXAnimationController` sets, skin weights, Biped rigs —
  `FUN_0064d940`), and the foundation's own parser and controller subset
  do that with no D3DX linked (`foundation/src/assets/xmodel.h:205-226`).
- The single production asset path is:
  `bundle → decrypt → xm::loadMemory → live animation`
  (`foundation/src/assets/xmodel.h:267`, `dat_bundle.cpp`).
  There is **no conversion step** (no glTF/FBX export into the build):
  converters bake down animation blending/track setup the game relies on
  and would cost more effort than using the originals.
- Loader parity targets (semantics of the original's loader
  `FUN_0064d940`, `docs/reverse-engineering.md:195`; its flag table at
  :229/:413 is superseded here): InMemory variant, mesh flags `0x220`,
  up to 2 anim tracks bound at load. (Note: `0x220` is
  `D3DXMESH_VB_MANAGED | D3DXMESH_IB_MANAGED` per `d3dx9mesh.h` —
  0x020 / 0x200 — not the `32BIT | NPATCHES` that
  `reverse-engineering.md` still claims; no NPatch templates exist in the
  shipped assets.)

## D4 — mvp hook status (do not plan around the README)

- `tools/hook-tracer/README.md` (the preserved copy of the deleted
  `mvp/hook/README.md`) describes inline patching with direct/archive/
  hybrid modes. The shipped `daybreak_hook.c` (v11) **patches nothing** —
  it is a `CreateFileA` tracer + log (`tools/hook-tracer/daybreak_hook.c:105`).
  The `daybreak_launcher.exe` injector itself works.
- Treat the hook as a **dev/RE tracing tool**, not a runtime asset
  feature. If runtime loose-file loading is ever needed, it will be
  re-implemented in the foundation — not revived in the retired `mvp/`.

## D5 — Comment/code-quality policy (remake)

- Comments must explain **why** or cite RE provenance
  (`FUN_xxxxxx`, binary address, `docs/reverse-engineering.md` section).
- Delete comments that restate the code, dead-code blocks kept
  "just in case", and stale milestone chatter. No behavior changes
  while cleaning (standing policy: `AGENTS.md` rule 4).

## D6 — Scope: versus + LAN netplay first (2026-10-01)

- The focus is **offline versus** (split-screen, bots) and **LAN
  netplay**. Full spec: `docs/game-spec.md`.
- This supersedes the old roadmap's blanket "no online/netcode" ban:
  DirectPlay 8 is still replaced, not ported, but a LAN-first netcode
  (deterministic lockstep over UDP) is in scope.
- Story mode is **not built**: the ids are registered
  (`Prologue`/`StoryTeam`/`StoryAdv`, `foundation/src/ui/screen.h:43-47`)
  but only `Title` has a builder (`foundation/src/ui/screen.cpp:47-48`),
  and story-mode video stays stubbed (`ROADMAP-PENDING.md` §H). No
  branching, saves, or localization is planned. Non-goals listed in
  `game-spec.md` §5 stand.
