# Overview — daybreak-decomp

Decompilation and remake of **Higurashi Daybreak** (`DaybreakDX.exe`,
Twilight Frontier / 07th Expansion, PE32 x86, image base `0x00400000`,
4,092 functions).

This repo has **two halves** with different rules:

| Half | Path | Goal | Rule of thumb |
|---|---|---|---|
| **Product** | the repository root | Playable modern port (C++17, SDL3 + WebGPU: `webgpu.h`, wgpu-native native, emdawnwebgpu web; Linux/Windows/web) | All new game code goes here — build with `./build.sh {deps,linux,windows,web}`; see `docs/decisions.md` D1–D6 |
| **Research** | `research/` | Reverse-engineering evidence + readable-C pipeline | Nothing here runs the game; `research/recomp/` is never hand-edited |

## Repo map

```
daybreak-decomp/
├── README.md / INDEX.md / INDEX.json   entry map + generated index
├── docs/                               English docs (you are here)
│   ├── overview.md                     this file
│   ├── pipeline.md                     how research artifacts flow
│   ├── status.md                       living status + metrics
│   ├── conventions.md                  C / style / commit conventions
│   ├── agents/                         guides for automation agents
│   ├── reports/                        findings summaries
│   └── archive/                        original Portuguese docs (historical)
├── research/                           RE artifacts (see pipeline.md)
│   ├── binary_data/    upstream evidence: per-function JSON store,
│   │                   strings, types, callgraph, phase reports
│   ├── decompiled/     raw mass dump: one .c per function (read-only)
│   ├── recomp/         generated readable C (never edit by hand)
│   ├── symbols/        source of truth: names, types, notes
│   ├── progress/       coverage metrics (official)
│   ├── tools/          ingest → generate_recomp → coverage_report
│   ├── extraction_phases/  raw phase dumps + prioritization JSONs
│   └── evidence/           DX9 parity bank (history only), NPR evidence, and
│                           assets/shaders/effect_*.bin: the original's effect bytecode
├── src/, tests/, CMakeLists.txt        SDL3 + WebGPU product (C++17; Linux/Windows/web)
├── tools/launch_original.sh            run the original exe under Wine
├── tools/{asset-tools,hook-tracer}/    .dat/.cnv tools; original-exe hook tracer
├── Higurashi-Daybreak/                 local game install (gitignored)
└── .github/                            index Action (see INDEX.md header)
```

## How research flows (one paragraph)

Ghidra/MCP dumps land in `research/binary_data/` (per-function JSON).
The mass dump is materialized as one `.c` per function in
`research/decompiled/`. `research/tools/ingest.py` tracks content hashes
into `research/symbols/functions.json` (the only source of truth for
names). `research/tools/generate_recomp.py` combines dump + symbols into
readable C in `research/recomp/`. `research/tools/coverage_report.py`
scores it all into `research/progress/coverage.json` — the official
metric. Full version in `docs/pipeline.md`.

## Key findings (condensed)

- **Entry**: CRT `entry` (`0x0066c906`) → `WinMain` (`0x0064d250`,
  window class `"HigurashiDaybreak"`, fixed 800×600) → `CommonInit`
  (`0x00543c70`: D3D device, DirectInput, audio).
- **Scene dispatch is a switch, not a table**: the `0x006a16c0`
  hypothesis was disproved — it is a config struct
  (`SceneDispatcherConfig`: `LoadNextScene` pointer + UI floats + asset
  paths). Real dispatch is `switch(*(pGameState + 0x2e18))` inside
  `LoadNextScene` (`0x00406310`): title / select / VS-load / battle.
- **Render**: D3D9 + D3DX (25 mapped calls), `.x` meshes via
  `D3DXLoadMeshHierarchyFromXInMemory`, collision is `D3DXIntersect`
  ray-vs-mesh only, 10 embedded D3DX effects (relocated to the remake
  at `research/evidence/assets/shaders/`).
- **Network**: DirectPlay 8 (not Winsock), ~27 functions, client/server/
  peer modes. Replaced, not ported, in the remake (out of scope).
- **Binary is clean**: no anti-debug, no packing (verified, phase 12).
- **Coverage ceiling**: ~3,191 of 4,092 functions are decompilable; the
  rest are thunks/externals/stubs Ghidra cannot process.

## Where to go next

- New here? Read `docs/pipeline.md`, then `docs/status.md`.
- Writing game code? Read `docs/decisions.md`, then work in `src/`.
- Driving the original for comparison? `tools/launch_original.sh`.
- Automating RE work? `docs/agents/`.
- Old Portuguese docs? `docs/archive/` (historical, superseded by `docs/`).
