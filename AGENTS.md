# AGENTS.md — daybreak-decomp

> Read this first. You are in a repo with **two halves**: a playable
> remake and a reverse-engineering corpus. They have different rules.
> This file is the map; zone docs carry the details.

## What this project is

Decompilation **and** remake of Higurashi Daybreak (`DaybreakDX.exe`,
Twilight Frontier / 07th Expansion, PE32 x86). End goal: a playable
modern port. No bit-matching against the original binary is attempted.

## The two halves

| | `remake/` (product) | `research/` (evidence) |
|---|---|---|
| Language | C++23, SDL2 + D3D9 → SDL3 + WebGPU (D2) | C11 dumps, Python pipeline, JSON |
| Rule | **All new game code goes here** | Nothing here runs the game |
| Entry docs | `remake/README.md` → `remake/docs/decisions.md` | `docs/overview.md` → `docs/pipeline.md` |
| Build | `remake/scripts/fetch_deps.sh` (once), then `remake/build.sh` | `python3 research/tools/coverage_report.py` (no deps) |

## Hard rules (violations = reverted work)

1. **Never hand-edit `research/recomp/`.** Generated output; edits are
   overwritten. Source of truth is `research/symbols/`.
2. **`remake/` keeps the original `.X` files — no conversion pipeline.**
   The renderer is **migrating to WebGPU** (D2, reversed 2026-10-01):
   SDL3 + `webgpu.h`, wgpu-native on native targets and emdawnwebgpu on
   the web. DX9 stays buildable as the A/B reference until the WebGPU
   path renders a matching in-game frame. Binding decisions in
   `remake/docs/decisions.md` (read D1–D6 before touching `remake/`).
3. **`mvp/` is gone.** Retired 2026-10-01 after its contents were ported.
   Don't recreate it; decomp provenance lives in `research/`.
4. **Comment policy in `remake/src/`:** explain *why*, cite RE provenance
   (`FUN_xxxxxx`, addresses). No restatement comments, no dead code.
5. **Run `coverage_report.py` before committing** research changes.
6. **Full diff review before EVERY commit** — see the section below.
   Not optional, no size exemption.

## MANDATORY — full diff review before EVERY commit

Read `git diff` **and** `git diff --cached`. This step cannot be skipped,
no matter how small the change. Review every changed file for:

- **Unused code** — dead branches, unused includes/members/functions left
  behind by the edit.
- **Debug helpers that are no longer useful** — temporary log lines,
  traces, fingerprints, counters added while investigating; remove them
  or gate them behind an env flag if genuinely valuable.
- **Repeated logic** — duplicated blocks that should be unified into one
  helper or loop.
- **Verbose and useless comments** — comments narrating obvious code,
  stale references to removed code, or long-winded explanations of what
  the diff already shows.

Fix everything found (or explicitly justify keeping it) before
committing. A skipped review is a process violation.

## Map

```
daybreak-decomp/
├── README.md / AGENTS.md (this file) / INDEX.md+INDEX.json (generated)
├── docs/            English docs: overview, pipeline, status,
│                    conventions, agents/, reports/, archive/ (old PT docs)
├── research/        binary_data/ (evidence) · decompiled/ (raw dump, read-only)
│                    recomp/ (generated) · symbols/ (truth) · progress/ (metrics)
│                    tools/ (ingest→generate→coverage) · extraction_phases/
├── remake/          src/{core,render,file_parser,gameplay,physics,input,maps,audio,assets}/
│                    tools/{asset-tools,hook-tracer}/ assets/shaders/ docs/ tests/
│                    foundation/   SDL3 + WebGPU base; builds Linux/Windows/web (D2)
├── tools/launch_original.sh   run the ORIGINAL exe under Wine (repo-root relative)
├── Higurashi-Daybreak/        local game install — gitignored, never commit
└── .github/                   index Action (regenerates INDEX on push)
```

## Common commands

```bash
# Remake
./remake/build.sh                                   # cross-compile Linux→Win x64
./remake/build.sh --clean                           # wipe build/ after a move
./remake/build.sh -dat daybreak00.dat -list         # inspect a bundle (needs game .dats)
./tools/launch_original.sh                          # drive the original under Wine

# Research (all offline, stdlib-only Python)
python3 research/tools/ingest.py --full
python3 research/tools/generate_recomp.py
python3 research/tools/coverage_report.py
grep -rl "pattern" research/decompiled/*.c
python3 .github/scripts/generate_index.py           # refresh INDEX.md/json
```

## Conventions (short)

Prefixes: `feat/fix/docs/chore/refactor/recomp:/symbols:`.
C11 in research (`PascalCase` funcs, `FUN_<addr>` until reviewed);
C++23 in remake. Full rules: `docs/conventions.md`.

## Git

`main` is the only branch in normal use (plus `recomp-auto` for the
pipeline — stay out). Push scope: `research/decompiled`,
`research/binary_data`, reviewed `research/symbols`, `research/progress`,
docs. Never commit: `research/recomp/`, game files, keys, `*.full.json`,
anything under `remake/build/` or `remake/tools/` toolchain dirs.

## Local-only (present on disk, absent from git)

`Higurashi-Daybreak/` (4.4GB game install), `remake/tools/` toolchain
(MinGW/Python/SDL — re-fetch via `remake/scripts/fetch_deps.sh`),
`remake/build/`. Don't reference absolute local paths in committed docs.
