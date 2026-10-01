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

## D2 — DirectX 9 stays. No renderer migration.

- The game renders through **Direct3D 9 + D3DX9** (`d3dx9_43.dll`,
  June 2010 redist). Dropping DX9 is **not possible** (D1 discussion,
  2026-10-01).
- Contain the deprecation risk by keeping all D3DX usage behind the
  existing seams (`XModel`, renderer helpers) — but there is no plan to
  replace the renderer.

## D3 — Original `.X` files are used directly. No conversion pipeline.

- Character/stage/collision meshes ship as `.X` in three encodings
  (`0302txt`, `0303bin`, `0303bzip`) with `D3DXLoadMeshHierarchyFromXInMemory`
  frame trees, `ID3DXAnimationController` sets, skin weights, Biped rigs.
- The single production asset path is:
  `bundle → decrypt → XModel::load_from_memory → live animation`.
  There is **no conversion step** (no glTF/FBX export into the build):
  converters bake down animation blending/track setup the game relies on
  and would cost more effort than using the originals.
- Loader parity targets (from `docs/reverse-engineering.md`): InMemory
  variant, mesh flags `0x220` (`32BIT | NPATCHES`), 2 anim tracks bound
  at load.

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
