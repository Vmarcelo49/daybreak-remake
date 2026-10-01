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
- **Review: just started.** Only a handful of functions are
  `reviewed`/`locked` (WinMain, LoadNextScene, CommonInit, entry…);
  ~3,180 remain `unreviewed`. The long tail is naming/review work.
- **Recomp pipeline: implemented and verified** (`ingest →
  generate_recomp → coverage_report`; re-verified after the
  `research/` move).
- **Product: `remake/` is now the primary codebase.** The old `mvp/`
  experiment was ported (P0–P4) and retired — see
  `remake/docs/decisions.md` and `remake/docs/port-from-mvp-plan.md`.

## Snapshot (from `coverage.json`, 2026-07-02 vintage)

| Metric | Value |
|---|---|
| Functions in binary | 4,092 |
| Decompiled | 3,191 (77.98%) |
| Reviewed / locked | ~5 (+18 with extraction suggestions) |
| Unreviewed | ~3,168 |
| Decomp errors | 0 |

## Completed analyses (with reports)

| Phase | Result | Report |
|---|---|---|
| 9 — scene dispatch table | **Disproved**: `0x006a16c0` is a config struct, not a table; real dispatch is the `LoadNextScene` switch + 13 mapped callees | `research/binary_data/scene_table/FASE9_REPORT.md` |
| 11/11b — multiplayer | DirectPlay 8 (client/server/peer), 26 named candidates, full menu-dispatcher map | `research/binary_data/network_analysis/FASE11*.md` |
| Render pipeline | D3D9/D3DX init chain, render loop, title renderer mapped | `research/binary_data/render_pipeline/FASE*.md` |
| 12 — anti-analysis | Clean binary, no intentional anti-debug | `research/binary_data/anti_analysis/FASE12_REPORT.md` |

## Next steps

| # | Who | Action |
|---|---|---|
| 1 | Local agent | Process `unreviewed` batches, starting at `hot_spots` in `coverage.json` |
| 2 | Operator | Promote reviewed suggestions (`suggested → reviewed`) |
| 3 | Anyone | Deep-dive open clusters (e.g. `FUN_006604xx` game-send funcs) |
| 4 | Remake dev | Pull RE findings into `remake/` (effect technique binding is the known gap) |

## Archive note

The MCP tunnel era (sessions, URLs, deploy keys, FileVault paths) is
documented in `docs/archive/` for reproducibility. Paths referencing
`/home/z/...` in archived docs mean "the operator's old machine" —
current checkout lives wherever this repo is.
