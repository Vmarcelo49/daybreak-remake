# daybreak-remake

Decompilation **and** remake of **Higurashi Daybreak** (`DaybreakDX.exe`,
Twilight Frontier / 07th Expansion).

<img width="2560" height="1395" alt="image" src="https://github.com/user-attachments/assets/64fe73d2-a2a7-4e61-aae6-7d9167c0c874" />


## Two halves

| | `remake/` — the product | `research/` — the evidence |
|---|---|---|
| What | C++17 + SDL3 + WebGPU (`webgpu.h`: wgpu-native natively, emdawnwebgpu on the web) in `remake/foundation/`, built for Linux, Windows and the web. Linux has a recorded playable release gate, but four capture recipes need recalibration after issue #63 changed the stage-page default; Windows/Wine reaches title and battle but faults on rematch (issue #57). Browser title and live match run on software WebGPU with a local `/data` preload, but the `?pack=` path fails (issue #58); browser visual parity, hardware rendering and macOS execution remain unverified. See `remake/foundation/docs/RELEASE-CHECKLIST.md` §5.2 and `remake/foundation/docs/ROADMAP-PENDING.md` §G | 3,191 decompiled functions, readable-C pipeline, RE reports |
| Start | `remake/foundation/README.md`, then `remake/docs/decisions.md` | `docs/overview.md`, then `docs/pipeline.md` |
| Rules | Game code only; the original `.X`/`.cnv`/`.dat` load exactly as shipped; the renderer is SDL3 + WebGPU since the Phase 5 cutover (DX9 dropped 2026-10-02) | `recomp/` never hand-edited; `symbols/` is truth |

## Layout

```
daybreak-remake/
├── AGENTS.md / README.md               the two-halves map + hard rules (read first), then this map
├── INDEX.md / INDEX.json               generated index (python3 .github/scripts/generate_index.py; index Action on push)
├── docs/                               English docs
│   ├── overview.md                     repo map + key findings
│   ├── pipeline.md                     how research artifacts flow
│   ├── status.md                       living status (metric: progress/coverage.json)
│   ├── conventions.md                  C / style / commit rules
│   ├── agents/                         guides for automation agents
│   ├── reports/summary.md              findings in English
│   └── archive/                        original Portuguese docs (historical)
├── research/                           RE artifacts + pipelines
│   ├── binary_data/    upstream evidence (function JSONs, strings, reports)
│   ├── decompiled/     raw dump, one .c per function (read-only)
│   ├── recomp/         generated readable C (never edit by hand)
│   ├── symbols/        source of truth (names, types, notes)
│   ├── progress/       coverage metrics (official)
│   ├── tools/          ingest → generate_recomp → coverage_report
│   └── extraction_phases/  raw phase dumps + prioritization data
├── remake/                             the product, and the evidence it is measured against
│   ├── foundation/                     SDL3 + WebGPU product (build.sh deps|linux|windows|web)
│   ├── docs/                           decisions.md, game-spec.md, reference/ (prints of the ORIGINAL)
│   ├── tests/parity-baseline/          frozen DX9 reference bank — the behavioural A/B
│   └── tools/                          asset-tools/ (dat, sjis), hook-tracer/ (hooks the original exe)
├── tools/launch_original.sh            run the original exe under Wine
├── Higurashi-Daybreak/                 local game install (gitignored)
└── .github/                            index Action
```

## Current status

Intro movie, Main menu, character select, and the overall program loop works
Combat and animations are broken on almost all the cast

## Original binary summary

| Field | Value |
|---|---|
| Binary | `DaybreakDX.exe`, PE32 x86, image base `0x00400000` |
| Functions | 4,092 in binary · 3,191 decompilable (~78%) · review in progress |
| Renderer | D3D9 + D3DX + DirectInput8, fixed 800×600, `"HigurashiDaybreak"` |
| Scene dispatch | `LoadNextScene` (`0x00406310`), switch on `pGameState+0x2e18` |
| Network | DirectPlay 8 (documented, not ported) |
| Binary hygiene | Clean — no packing, no anti-debug |


## License

Reverse-engineering artifacts are for **research and educational
purposes only**. The original binary and game assets remain property of
their respective copyright holders. Remake source is original work —
see `remake/` docs.
