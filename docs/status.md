# Status — living project status

> Updated when reality changes. Metric snapshots below are historical —
> the official metric is always `research/progress/coverage.json`
> (regenerate with `python3 research/tools/coverage_report.py`).
> Previous version (Portuguese): `docs/archive/PROGRESSO.md`.

## Where things stand (2026-10-01)

- **Extraction (Ghidra/MCP): done.** Phases 1–12 complete; the MCP
  tunnel can stay closed. Remaining RE work is offline.
- **Mass decompilation: done.** 3,191 of 4,092 functions decompilable
  (~78%); the rest are thunks/externals/stubs beyond Ghidra's reach
  (the practical ceiling for this binary).
- **Review: still thin.** 48 functions are `reviewed`/`locked` (23
  `D3DX*` + 2 `Direct*` import thunks among them) and 15 carry extraction
  suggestions; 3,106 remain `unreviewed` —
  `research/progress/coverage.json` (2026-10-01). The long tail is
  naming/review work.
- **Recomp pipeline: implemented and verified** (`ingest →
  generate_recomp → coverage_report`; re-verified after the
  `research/` move).
- **Product: `remake/foundation/` is the codebase.** The DX9 tree
  (`remake/src/**`, `remake/CMakeLists.txt`, `remake/build.sh`) was
  deleted in the Phase 5 cutover (2026-10-02, `5a63db3`); the foundation
  is C++17 + SDL3 + WebGPU (`webgpu.h`; wgpu-native native, emdawnwebgpu
  web) and builds Linux/Windows/web with
  `./remake/foundation/build.sh {deps,linux,windows,web}`; the Linux host
  suite has 50 ctest tests (2026-10-06; the Linux CI job runs them on every push
  that touches `remake/foundation/**`, and the asset-dependent ones
  skip without the game data — measured counts in
  `remake/foundation/docs/RELEASE-CHECKLIST.md` §2) and the offline release gate is
  `remake/foundation/docs/RELEASE-CHECKLIST.md`. See `remake/docs/decisions.md`
  D2 (reversed) and
  `remake/foundation/docs/FULL-REPLACEMENT-PLAN.md` §8. The mvp port
  record stays as history (`remake/docs/port-from-mvp-plan.md`; its
  `./build.sh` 17/17 refers to the deleted DX9 build). Only P3.1
  technique binding is still open, and it is tracked in
  `remake/foundation/docs/ROADMAP-PENDING.md`.
- **Product: measured, not asserted.** The foundation renders the title
  screen at RMSE 0.015970 against `remake/docs/reference/title-menu.webp`
  and the battle HUD bands ≤0.19; the frozen DX9 bank in
  `remake/tests/parity-baseline/` stays the behavioural oracle. Browser
  runs with game assets and macOS are unverified. The Linux versus release is
  gated by `remake/foundation/docs/RELEASE-CHECKLIST.md` (two humans, one human
  with COM and four-fighter matches through repeated rounds; Wayland/X11;
  30/60/high-refresh pacing; eight-round stability). Open work:
  `remake/foundation/docs/ROADMAP-PENDING.md`.

## Snapshot (2026-07-02, from `docs/archive/PROGRESSO.md`)

| Metric | Value |
|---|---|
| Functions in binary | 4,092 |
| Decompiled | 3,191 (77.98%) |
| Reviewed / locked | 5 |
| With extraction suggestions | 18 |
| Unreviewed | 3,168 |
| Decomp errors | 0 |

The committed `research/progress/coverage.json` (2026-10-01) now reads
48 reviewed/locked, 15 with extraction suggestions, 3,106 unreviewed,
0 stale. `Decomp errors: 0` is still backed by
`research/extraction_phases/04_decompile_errors.json` (empty array).

## Completed analyses (with reports)

| Phase | Result | Report |
|---|---|---|
| 9 — scene dispatch table | **Disproved**: `0x006a16c0` is a config struct, not a table; real dispatch is the `LoadNextScene` switch + 13 mapped callees | `research/binary_data/scene_table/FASE9_REPORT.md` |
| 11/11b/11c — multiplayer | DirectPlay 8 (client/server/peer), 27-function cluster; 16 named in phase 11, 43 name suggestions over 48 candidates in `research/binary_data/network_analysis/candidates.json`, full menu-dispatcher map | `research/binary_data/network_analysis/FASE11*.md` |
| Render pipeline | D3D9/D3DX init chain, render loop, title renderer mapped | `research/binary_data/render_pipeline/FASE*.md` |
| 12 — anti-analysis | Clean binary, no intentional anti-debug | `research/binary_data/anti_analysis/FASE12_REPORT.md` |

## Next steps

| # | Who | Action |
|---|---|---|
| 1 | Local agent | Process `unreviewed` batches, starting at `hot_spots` in `coverage.json` |
| 2 | Operator | Promote reviewed suggestions (`suggested → reviewed`) |
| 3 | Anyone | Deep-dive open clusters (e.g. `FUN_006604xx` game-send funcs) |
| 4 | Remake dev | Work `remake/foundation/docs/ROADMAP-PENDING.md` (A1 `env.dat` spawn and A2 viewpoint first); effect technique binding is still open (`remake/foundation/docs/RENDER-PASSES.md`:53) |

## Archive note

The MCP tunnel era (sessions, URLs, deploy keys, FileVault paths) is
documented in `docs/archive/` for reproducibility. Paths referencing
`/home/z/...` in archived docs mean "the operator's old machine" —
current checkout lives wherever this repo is.
