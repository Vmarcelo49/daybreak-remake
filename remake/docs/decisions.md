# Project decisions (binding)

Recorded 2026-10-01. These override any conflicting notes elsewhere in
`docs/` or roadmaps. Update this file — not scattered
comments — when a decision changes.

## D1 — `mvp/` retired; `remake/` is the only codebase

- The old `mvp/` tree (`<project>/mvp/`) was frozen, ported per
  `docs/port-from-mvp-plan.md`, then **deleted** (2026-10-01). All new
  code is written here in `remake/` (`src/`, `scripts/`, `tools/`).
- What survives from `mvp/`: the relocated tooling
  (`tools/asset-tools/`, `tools/hook-tracer/`, `assets/shaders/`),
  the ported engine/scene/texture work, and the RE constants now
  cited in code comments. The decomp translations themselves live on
  in `<project>/decompiled/` and `binary_data/` — consult those, not
  `mvp/`, for `FUN_xxxxxx` provenance.
- Rationale: two active codebases split effort and drift; the remake
  (real gameplay stack) is the strictly better foundation
  (see comparison notes in chat, 2026-10-01).

## D2 — The renderer migrates to WebGPU. DX9 is the reference until parity.

- **Supersedes the 2026-10-01 text** that read "DirectX 9 stays. No
  renderer migration." and claimed dropping DX9 was *not possible*. That
  claim was tested and disproven (evidence below), so the direction is
  now the opposite one.
- Target: **SDL3 + `webgpu.h`**, with the backend chosen per platform —
  **wgpu-native** on native targets, **emdawnwebgpu** on the web. One
  `CMakeLists.txt` serves both; the only source differences are in the
  presentation layer (six of them, all one-liners).
- **DX9 is not deleted.** It stays buildable and remains the A/B
  reference until the WebGPU path renders a complete in-game frame
  (stage + characters + HUD) that matches it. That frame is the gate;
  until it passes, DX9 is the shipping renderer.
- Evidence (built and run, not argued — `webgpu-spike/FINDINGS.md`):
  - Linux/Wayland, real GPU, wgpu-native: surface, capabilities,
    configure, 60/60 frames presented, FIFO available.
  - Web (Emscripten + emdawnwebgpu): `RESULT: ok` in Chromium; the
    browser presents, and FIFO is the only present mode it offers.
  - Windows: Dawn linked from MinGW and ran; wgpu-native cross-compiled
    earlier the same day rendered under Wine byte-identically to Linux.
  - macOS: **unverified** — no Mac available. Dawn ships macos x64 and
    aarch64 prebuilts and `sdl3webgpu` has the Metal path, but nothing
    has been executed. Do not claim it works.
- Known obstacle: Dawn (at least the `chromium/7187` prebuilt) rejects
  `WGPUSurfaceSourceWaylandSurface`, so it is a poor native backend on a
  Wayland desktop. wgpu-native handles Wayland.
- Rationale: D3DX9 is deprecated, drags `d3dx9_43.dll` and Wine-specific
  behaviour, and blocks the Linux/macOS/web targets this port exists to
  reach.

## D3 — Original `.X` files are used directly. No conversion pipeline.

- **Unchanged by D2.** The asset path is the same on every backend: the
  originals are loaded as shipped. `webgpu-mvp/` decodes all 728 `.X`
  files (three encodings), all 5051 `.cnv` images and the Shift-JIS
  texture references with no conversion step, for exactly the reasons
  below.
- Character/stage/collision meshes ship as `.X` in three encodings
  (`0302txt`, `0303bin`, `0303bzip`) with `D3DXLoadMeshHierarchyFromXInMemory`
  frame trees, `ID3DXAnimationController` sets, skin weights, Biped rigs.
- The single production asset path is:
  `bundle → decrypt → XModel::load_from_memory → live animation`.
  There is **no conversion step** (no glTF/FBX export into the build):
  converters bake down animation blending/track setup the game relies on
  and would cost more effort than using the originals.
- Loader parity targets (from `docs/reverse-engineering.md`): InMemory
  variant, mesh flags `0x220`, 2 anim tracks bound
  at load. (Note: `0x220` is `D3DXMESH_VB_MANAGED | D3DXMESH_IB_MANAGED`
  per `d3dx9mesh.h`, not the `32BIT | NPATCHES` this line originally
  claimed — no NPatch templates exist in the shipped assets.)

## D4 — mvp hook status (do not plan around the README)

- `mvp/hook/README.md` describes inline patching with direct/archive/
  hybrid modes. The shipped `daybreak_hook.c` (v11) **patches nothing** —
  it is a `CreateFileA` tracer + log. The `daybreak_launcher.exe`
  injector itself works.
- Treat the hook as a **dev/RE tracing tool**, not a runtime asset
  feature. If runtime loose-file loading is ever needed, it will be
  re-implemented in the remake — not revived in `mvp/`.

## D5 — Comment/code-quality policy (remake)

- Comments must explain **why** or cite RE provenance
  (`FUN_xxxxxx`, binary address, `docs/reverse-engineering.md` section).
- Delete comments that restate the code, dead-code blocks kept
  "just in case", and stale milestone chatter. No behavior changes
  while cleaning (cleanup pass running, 2026-10-01).

## D6 — Scope: versus + LAN netplay first (2026-10-01)

- The focus is **offline versus** (split-screen, bots) and **LAN
  netplay**. Full spec: `docs/game-spec.md`.
- This supersedes the old roadmap's blanket "no online/netcode" ban:
  DirectPlay 8 is still replaced, not ported, but a LAN-first netcode
  (deterministic lockstep over UDP) is in scope.
- Story mode stays loadable but is not the focus (no branching, saves,
  or localization). Non-goals listed in `game-spec.md` §5 stand.
