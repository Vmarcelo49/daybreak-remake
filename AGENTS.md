# AGENTS.md — daybreak-decomp

> Read this first, then [`docs/DIRECTION.md`](docs/DIRECTION.md). You are in a
> repo with **two halves**: a playable remake and a reverse-engineering corpus.
> This file is the map, the enforcement point and the permanent rules;
> `docs/DIRECTION.md` describes the current direction.

## What this project is

Decompilation **and** remake of Higurashi Daybreak (`DaybreakDX.exe`,
Twilight Frontier / 07th Expansion, PE32 x86). End goal: a playable modern port.

**No binary-level matching:** we neither link nor reproduce the original's code,
and byte-identity with it is not a goal. The target is faithful **behaviour**.
Original-runtime parity is a separate claim, requiring original-runtime evidence.
A claim that cannot name its evidence tier, scope and limitations is not a result.

## Current state (2026-11-04)

**Playable, locally and online, with no known blocker.** The native build runs the whole loop: title,
story, versus, character select, battle, results, options and network play. 1.0.0 is the
first stable release, and the game updates itself from then on.

| Area | State | Where |
|---|---|---|
| Combat | The vendored reference core is the only authority (M5 closed). Original-runtime parity: **not verified** | `src/battle/core/`, wrapper `src/battle/` |
| Story | Dialogue, ladder, retry, game over, endings, staff roll | `src/frontend/story_*`, `screen_story*` |
| Language | Menus and HUD in English or Japanese. Dialogue is still Japanese | `src/ui/sheet_locale.*`, `assets/locale/en.txt`, `docs/TRANSLATION-INVENTORY.md` |
| Options and settings | Our own settings file, never the original's | `src/frontend/screen_options.cpp`, `docs/USER-SETTINGS.md` |
| Texture packs | Read from beside the executable; extractor and verifier exist. Download and prompt wait for a pack | `docs/TEXTURE-PACKS.md`, `tools/asset-tools/texture_pack.py` |
| Web | Builds, fights and finishes a match: the round's end and its result screen are part of the match group since #88. Not in CI since 0.2.1, where its build stalled | `docs/BUILD-web.md`, `webdelivery/` |
| Online | Menus, lobby, shared selection, rollback and room codes exist; real-network play has begun, and open issues track remaining problems | `docs/ONLINE-PLAN.md`, `src/net/`, `src/frontend/screen_online.cpp`, `server/` |
| Not built | macOS | |

Open issues are on GitHub (`Vmarcelo49/daybreak-remake`), and they are the current bug list.

## Where to find things

| You need | Read |
|---|---|
| How to build and how the code is organized | `DEVELOPMENT.md`. `README.md` is for players: keep it plain, and keep its tested list true |
| Current direction | `docs/DIRECTION.md` |
| Open work and completed changes | GitHub issues and git history |
| Binding product decisions | `docs/decisions.md` (D1–D15) |
| The core and its changes | `src/battle/core/README.md`, `PATCHES.md`, `MANIFEST.sha256` |
| Regression hashes | `bash tools/fingerprints.sh $PWD/build/linux/simctl $PWD/build/linux/daybreak <outdir> tests/scripts`. Expected on 2026-11-04: SIM `746ce7a9cbe6e44a`, `941f3dcd7a679d74`, `f19e8d6d58c37151`; PIX `ff54a85d`, `1fc12c64`, `9ecda8ec` (title720 moved with issue #98's live title; title4p photographs the selection, not the title). On 2026-11-04 the CPU's `rsqrtss` estimate was replaced by an exactly rounded `1/sqrt` for issue #107, which moved the second and third SIM and title4p: those two were only ever true on one CPU vendor. A deliberate behaviour change moves them; say so in its report |
| Builds and release | `docs/BUILD-*.md`, `docs/RELEASE-CHECKLIST.md`. CI runs when `VERSION` changes on `main` (`.github/workflows/build.yml`) |
| Assets and paths | `docs/ASSET-CATALOG.md`; moved paths in `docs/PATHS.md` |
| Testing a character + weapon combo, debug keys | The `combo-test` skill (`.agents/skills/combo-test/SKILL.md`), `docs/DEBUG-KEYS.md`, saved plans in `tests/combos/` |
| Original-binary questions | The skill routing below |
| Research corpus | `docs/pipeline.md`, `docs/conventions.md` |

### Precedence — old documents are evidence, not instructions

Documents in this repo were written under superseded plans, and many still tell
the reader to continue the old per-character hand-port. Those instructions are
**retired**: only the owner and this file say what to work on.

| Document | Still good for | Never authorizes |
|---|---|---|
| `docs/archive/ginkiha-*.md` | what the reference recovered, per-combo findings, the acceptance bar | "next execution" orders, "advance to Mion", per-combo port plans |
| `docs/ROADMAP-PENDING.md` | issue IDs, measured limits, an item's status | choosing work; its "next dig" and suggestion lines |
| `docs/ANIMATION-SETS.md`, `docs/ANIMATION-DATA-AUDIT.md`, `docs/LIVE-DEBUG.md`, `docs/EFFECTS-*.md`, `docs/GAME-CAMERA.md`, `docs/SHADOWS.md` | original-behaviour evidence, and what the port does today | new feature work, new selector/table work |
| `docs/decisions.md` | binding decisions and historical rationale; read before touching the product tree | new decisions — the owner adds those |
| `docs/archive/PILOT-EVIDENCE-CONTRACT.md`, `docs/archive/PILOT-SEAM.md` | what the pilot established, addressed findings, seam facts | new contract or per-rule work |
| `research/evidence/parity-baseline/README.md` + the bank | history: what the deleted DX9 tree captured, and what it could not | a fidelity oracle — its fighters bound zero animation sets |
| `docs/archive/FULL-REPLACEMENT-PLAN.md`, `docs/archive/port-from-mvp-plan.md`, `docs/archive/roadmap.md`, `docs/archive/**` | history and rationale | anything current |
| `docs/archive/status.md`, historical handoffs in `docs/archive/`, `docs/agents/**` | research history and conventions | product work orders |

**Do not read the whole documentation tree "for context"**: that is how agents re-implement a
retired plan. Use the table above.

Path moves are mapped once in [`docs/PATHS.md`](docs/PATHS.md) — use it instead of
the historical text of an archived document.

Track current bugs and work in GitHub issues. Report changes, checks and limitations
with the task; use [`docs/QUESTIONS.md`](docs/QUESTIONS.md) only when the owner cannot
be reached for a required decision. The old scoreboard, work log and freeze exceptions
are historical records in `docs/archive/`, not current gates.

## Original-binary skill routing

For a task that requires original compiled-binary evidence, load the
`reverse-engineer-anything` skill and follow its **REA CLI / Ghidra** workflow.
Use existing addressed research first; obtain fresh, focused binary evidence
where a pilot seam, fixture expectation or demonstrated discrepancy requires it.
Source-only adaptation, fixture implementation and port tests use ordinary
repository tools; they do not require REA.

- Pin the original binary hash before analysis; never borrow addresses from the
  skill's examples for another game.
- Prefer one known function or bounded question over a whole-game survey. Save
  complete Evidence under ignored `local-data/harness/`; validate command status,
  Evidence operation and target identity before using the result. Cite relevant
  addresses and derived findings in tracked reports, not raw decompiler dumps.
- Separate instruction/code observations, inferred field meanings and unresolved
  indirect calls. Static evidence supports source-backed expectations, not
  original-runtime parity. `rea trace` follows static references, not execution.
- Reuse saved results and avoid concurrent writers to a shared snapshot cache or
  unnecessary parallel Ghidra imports.
- Loading this skill does **not** authorize launching the original, runtime
  instrumentation, frame-perfect input automation, analysis-annotation changes,
  installing tools or configuring integrations. Those require separately scoped
  owner authorization and remain subject to repository safety rules.

## Evidence tiers

Every verification claim names its tier; the highest one wins:

1. **original runtime observation/trace** — strongest for the behaviour actually
   observed; sampled reads are not coherent per-update traces by default;
2. **recovered original code** with an address (`FUN_xxxxxx`, field offsets);
3. **original static prints** (`docs/reference/`) or **owner observation**;
4. **install-backed automated test** against the real game data;
5. **capture of our own build** (`--out`);
6. **port rule** — provisional, labelled as such in code and in the report.

**"Built" is not "verified". A capture is not a live run (D9). A skip is not a
pass.** A tier-6 rule is never presented as recovered behaviour, and a tier-5
capture never substitutes for a tier-1 trace. Shared-source body and adapter
agreement is a consistency check, not independent original proof. Report missing
or skipped cases honestly rather than treating them as passed.

## The two halves

| | the product (`src/`, `tests/`, the root) | `research/` (evidence) |
|---|---|---|
| Language | C++17, SDL3 + WebGPU (D2) | C11 dumps, Python pipeline, JSON |
| Rule | **All new game code goes here** | Nothing here runs the game |
| Entry docs | `DEVELOPMENT.md` → `docs/decisions.md` | `docs/overview.md` → `docs/pipeline.md` |
| Build | `./build.sh deps` (once), then `./build.sh {linux,windows,web}` | `python3 research/tools/coverage_report.py` (no deps) |

## Comment policy

In the product tree, explain *why* and cite reverse-engineering provenance
(`FUN_xxxxxx`, addresses). Avoid restatement comments and dead code.

## Mandatory full diff review before every commit

Full diff review before EVERY commit — not optional, with no size exemption.
Read both `git diff` and `git diff --cached`, and review every changed file for
unused code, temporary diagnostics, repeated logic, and stale or unhelpful comments.
Fix findings or explicitly justify keeping them before committing.

## Original-binary work

- **Pin before comparing.** `sha256sum` the install's `DaybreakDX.exe` and require
  `27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`. Any other
  hash means **stop**: no comparison, no original-side trace, no "probably the same
  build". Record the verified hash next to every original-side result.
- **Never patch the original's code.** Inline `JMP rel32`/trampoline patching
  crashed in the hook-tracer's v1–v10; the shipped DLL logs file opens and patches
  nothing. Static file reading is permitted within an authorised task. Live
  attachment and game-data writes need separately scoped owner authorization;
  they are not expected Phase 1 work. For approved writes, record every field
  and value, and never write instruction bytes. Read-only code protection is not
  permission to build an original-game input controller.
- **Muting is courtesy, not a rule.** The owner's position (2026-10-14):
  `--no-audio` exists so verification does not disturb whoever is using the
  machine; audio itself is fine. Use the remake's mute flags as before, and do
  not spend effort building a silent-launch path for the original.
- **Input injection** targets the specific game process or window — never the
  owner's active desktop session (no global keystroke/mouse synthesis) — and the
  first run is announced to the owner beforehand.
- The original launches through `tools/launch_original.sh`, which reads `GAME_DIR`,
  `INJECTOR` and `WINE`. Do not hardcode install paths anywhere.

## Quiet testing

All agent-launched remake verification must be silent. Pass `--no-audio` to manual
smoke, capture and scripted runs; the host also mutes verification and bounded
`--frames` runs. Do not use `--with-audio` unless the owner explicitly requests an
audible listening test, and mute flags must not change saved volume settings. CTest
forces SDL's dummy audio driver, including for backend tests and child processes.
Original-side runs may be audible; muting there is convenience only (above).

## Common commands

```bash
./build.sh deps && ./build.sh linux
ctest --test-dir build/linux --output-on-failure            # default tier, a few minutes
ctest --test-dir build/linux -L slow --output-on-failure    # before a release
ctest --test-dir build/linux -L frontend -LE slow           # one area you touched; see DEVELOPMENT.md
                                                            # frontend|hud|battle|net|render|data|settings|platform
./tools/launch_original.sh            # the original, under Wine
python3 research/tools/coverage_report.py
```

Read `ctest`'s own summary rather than any count written in a document — every
added suite moves the denominator. Measured counts, the full command set and the
list that skips without game data are in `DEVELOPMENT.md` and
`docs/RELEASE-CHECKLIST.md` §2.

## Conventions (short)

Prefixes: `feat/fix/docs/chore/refactor/recomp:/symbols:`. C11 in research
(`PascalCase` funcs, `FUN_<addr>` until reviewed); C++17 in the product. Full
rules: `docs/conventions.md`.

## Git

- `main` is the integration branch; `recomp-auto` belongs to the pipeline — stay
  out of it. This replaces "main is the only branch in normal use": short-lived
  topic branches are fine, **long-lived parallel refactor branches are not**. The
  `refactor/*` and `fix/*` worktrees that sat 198–223 commits behind were the
  evidence for why; they were removed on 2026-10-16 (owner-reviewed: every tip was
  already an ancestor of `main`, zero unique commits, all worktrees clean), and the
  recorded listing is in [`docs/archive/DIRECTION-STATUS.md`](docs/archive/DIRECTION-STATUS.md) P0-2.
- **Never force push.**
- **Never** `reset --hard`, `clean -fd`, `checkout .`, or delete a branch or
  worktree without first listing its unique commits (`git log main..<branch>`) and
  showing the owner. This governs **git state**, not source files: deleting a
  REPLACE file at its gate is an ordinary edit inside a reviewed commit.
- **An uncommitted diff is never discarded.** It is committed in reviewable parts,
  or left exactly as found.
- Push scope: `research/decompiled`, `research/binary_data`, reviewed
  `research/symbols`, `research/progress`, docs, and reviewed source/tests/runtime
  caption assets under the product tree.
- Never commit: game files, keys, `*.full.json`, build outputs
  (`build/`), fetched dependencies (`third_party/`), ignored local leftovers of the
  retired layout, and `.local-analysis/`.

## Local-only (present on disk, absent from git)

`Higurashi-Daybreak/` (the game install), the fetched `third_party/` sources and
fonts (`./build.sh deps`), `build/`, any ignored local leftovers of the retired layout
(the owner deletes them), and `.local-analysis/`. Gyrotrope Black is bundled source
under `assets/fonts/`, not a fetched dependency.

**`.local-analysis/`** holds the external reverse-engineer's bundles
(`DaybreakRebuild-20261010`, `balance-reference-v0.10`,
`DaybreakPortingSupport-20261010`) and generated analysis. It is ignored via
`.gitignore`; it was previously covered only by `.git/info/exclude`, which a fresh
clone does not carry.

- Review every staged path before committing. Adapted bundle code follows the
  resolved permission below; raw analysis dumps and game assets stay untracked.
- **Licence: resolved 2026-10-14.** The owner holds full permission from the
  bundle's author, and this project's own licence is open ("use what you want").
  Bundle **code** (bodies, control headers, spine, dispatch, tables, catalogs,
  traces) may be adapted and **vendored into tracked files with attribution**
  under `src/battle/core/`. Bundle **game assets**
  (`data/**` DAT/X/CNV, textures, models, audio) remain the original rights
  holders' and are **never committed** — the author could license his
  reconstruction, not the original art.
- Keep the local bundles unchanged as provenance/reference material. Only the
  platform-free simulation closure is vendored; the bundle's Windows, Direct3D and
  DirectSound code never comes across.

Don't reference absolute local paths in committed docs.
