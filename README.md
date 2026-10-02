# daybreak-decomp

Decompilation **and** remake of **Higurashi Daybreak** (`DaybreakDX.exe`,
Twilight Frontier / 07th Expansion).

## Which half do you want?

| | `remake/` — the product | `research/` — the evidence |
|---|---|---|
| What | Playable C++23 remake (SDL2 + D3D9, migrating to SDL3 + WebGPU per D2) | 3,191 decompiled functions, readable-C pipeline, RE reports |
| Start | `remake/README.md`, then `remake/docs/decisions.md` | `docs/overview.md`, then `docs/pipeline.md` |
| Rules | Game code only; original `.X` stay, renderer migrating to WebGPU | `recomp/` never hand-edited; `symbols/` is truth |

## Layout

```
daybreak-decomp/
├── README.md / INDEX.md / INDEX.json   this map + generated index
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
├── remake/                             the remake (own README + docs)
├── tools/launch_original.sh            run the original exe under Wine
├── Higurashi-Daybreak/                 local game install (gitignored)
└── .github/                            index Action
```

## Target summary

| Field | Value |
|---|---|
| Binary | `DaybreakDX.exe`, PE32 x86, image base `0x00400000` |
| Functions | 4,092 in binary · 3,191 decompilable (~78%) · review in progress |
| Renderer | D3D9 + D3DX + DirectInput8, fixed 800×600, `"HigurashiDaybreak"` |
| Scene dispatch | `LoadNextScene` (`0x00406310`), switch on `pGameState+0x2e18` |
| Network | DirectPlay 8 (documented, not ported) |
| Binary hygiene | Clean — no packing, no anti-debug |

## Quick commands

```bash
# RE pipeline (after dump changes)
python3 research/tools/ingest.py --full
python3 research/tools/generate_recomp.py
python3 research/tools/coverage_report.py   # run before committing

# Search the evidence offline
grep -r "pattern" research/binary_data/strings/
grep -l "pattern" research/decompiled/*.c

# Rebuild the repo index
python3 .github/scripts/generate_index.py

# Build the remake (one-time toolchain fetch first)
./remake/scripts/fetch_deps.sh && ./remake/build.sh

# Run the original for side-by-side comparison
./tools/launch_original.sh
```

## Conventions

Commit prefixes (`feat/fix/docs/chore/refactor/recomp:/symbols:`), C11
style, and push scope are defined in `docs/conventions.md`. The short
version: never hand-edit `research/recomp/`; `research/symbols/` needs
human review for promotion; run `coverage_report.py` before pushing.

## License

Reverse-engineering artifacts are for **research and educational
purposes only**. The original binary and game assets remain property of
their respective copyright holders. Remake source is original work —
see `remake/` docs.
