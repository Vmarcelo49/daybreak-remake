# AGENTS.md — daybreak-decomp

> Read this first, then [`docs/DIRECTION.md`](docs/DIRECTION.md). You are in a
> repo with **two halves**: a playable remake and a reverse-engineering corpus.
> This file is the map, the enforcement point and the permanent rules;
> `DIRECTION.md` owns the plan.

## What this project is

Decompilation **and** remake of Higurashi Daybreak (`DaybreakDX.exe`,
Twilight Frontier / 07th Expansion, PE32 x86). End goal: a playable modern port.

**No binary-level matching:** we neither link nor reproduce the original's code,
and byte-identity with it is not a goal. The target is faithful **behaviour**.
Progress is measured as in [`docs/DIRECTION.md`](docs/DIRECTION.md) §6. Original-runtime
parity is a separate claim, requiring original-runtime evidence. A claim that
cannot name its evidence tier, scope and limitations is not a result.

## Work mandate

**The plan is [`docs/DIRECTION.md`](docs/DIRECTION.md)** — it owns the milestones. Read it
before choosing anything; if you were handed a task, check it against the plan first.
The Rena+0 pilot closed green on 2026-10-30, and its method-acceptance rules no longer
gate work.

### Frozen work — this list is the single source of truth

`DIRECTION.md` links here instead of repeating this list, so the two cannot drift apart.

**A. Hand-written combat — deleted at M5.** Do not bring it back. Behaviour changes belong
in the core, cited and listed in `src/battle/core/PATCHES.md`. The last revision with the old
path is `e9347627`.

**B. Product roadmap — frozen until M5 closes:** web delivery, netplay, story mode, movies,
macOS, extra renderer options, 3v3/4v4 (issues #58–#61, #3; roadmap G1/G2/E1–E3/H). The
owner orders this work in M6.

Frame-perfect original-game control, a new capture/replay platform and save-state or
emulator projects are outside this plan, not fallback tasks.

### Is your task allowed? Ask these three, in order

1. Is it a step of a milestone in `docs/DIRECTION.md` §4, in order?
2. Is it an owner exception in [`docs/EXCEPTIONS.md`](docs/EXCEPTIONS.md), unexpired,
   with a scope that names your files?
3. Is it a fix required by a **concrete, cited** failure — a named test or `simctl`
   scenario with its field/event and tick? "Required" without that evidence does not qualify.

If none is true: **stop and ask**. Do not infer a task from an old report, a TODO,
a "next steps" list, or a milestone table. A task that fails these three is drift,
and drift is reverted work no matter how well it is executed.

### Stop and ask — including unattended work

- Write the question in [`docs/QUESTIONS.md`](docs/QUESTIONS.md) in its format, and
  mark the affected claim `TODO(question NN)` in code or docs.
- Then take the next task that passes the three questions, or **end the session**
  with a blocker note there. Never invent work to stay busy.
- Ask *before acting* if a step would touch the owner's live desktop session,
  inject input anywhere other than this repo's own game process, or reach outside
  the repository.

### Attempt ceilings

Each focused investigation gets **3 attempts or 2 hours**, whichever comes
first; only the owner raises it (`docs/EXCEPTIONS.md`). Past it, stop, report the
missing capability and ask or re-scope. Do not restart the same investigation
under new task names or automatically descend into DLLs, memory writers or
screen-replay tooling. This is not a two-hour budget for a whole milestone.
Unproven original automation is never required.

### Precedence — old documents are evidence, not instructions

Documents in this repo were written under superseded plans, and many still tell
the reader to continue the old per-character hand-port. Those instructions are
**retired**: when a document disagrees with `DIRECTION.md` about what to work on,
`DIRECTION.md` wins — no exceptions, no "but this file says".

| Document | Still good for | Never authorizes |
|---|---|---|
| `docs/reports/ginkiha-*.md` | what the reference recovered, per-combo findings, the acceptance bar | "next execution" orders, "advance to Mion", per-combo port plans |
| `docs/ROADMAP-PENDING.md` | issue IDs, measured limits, an item's status | choosing work; its "next dig" and suggestion lines |
| `ANIMATION-SETS.md`, `ANIMATION-DATA-AUDIT.md`, `LIVE-DEBUG.md`, `EFFECTS-*.md`, `GAME-CAMERA.md`, `SHADOWS.md` (under `docs/`) | original-behaviour evidence, and what the port does today | new feature work, new selector/table work |
| `docs/decisions.md` | binding decisions and historical rationale; read before touching the product tree | new decisions — the owner adds those |
| `docs/PILOT-EVIDENCE-CONTRACT.md`, `docs/PILOT-SEAM.md` | what the pilot established, addressed findings, seam facts | new contract or per-rule work |
| `research/evidence/parity-baseline/README.md` + the bank | history: what the deleted DX9 tree captured, and what it could not | a fidelity oracle — its fighters bound zero animation sets |
| `docs/archive/FULL-REPLACEMENT-PLAN.md`, `docs/archive/port-from-mvp-plan.md`, `docs/archive/roadmap.md`, `docs/archive/**` | history and rationale | anything current |
| `docs/status.md`, `docs/agents/**` | research pipeline, conventions | product work orders |

**Do not read the whole documentation tree "for context"** — that is how agents
re-implement a retired plan. Route by task: any task → this file, then
`DIRECTION.md` and its task list `docs/DIRECTION-STATUS.md`; the core →
`src/battle/core/README.md`; original-binary questions → the skill routing
below; research corpus → `docs/pipeline.md`,
`docs/conventions.md`; release/platform → `docs/RELEASE-CHECKLIST.md`,
which is also where current status lives.

Status goes to four places and nowhere else: [`docs/DIRECTION-STATUS.md`](docs/DIRECTION-STATUS.md)
(the task list and the work reports), [`docs/SCOREBOARD.md`](docs/SCOREBOARD.md)
(the one metric and verdicts), [`docs/QUESTIONS.md`](docs/QUESTIONS.md)
(blockers) and [`docs/EXCEPTIONS.md`](docs/EXCEPTIONS.md) (owner overrides), under
the plan in `DIRECTION.md`. Do not open other ledgers or progress documents.

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
  unnecessary parallel Ghidra imports. The normal attempt ceiling still applies.
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
capture never substitutes for a tier-1 trace. Acceptance under the approved
coverage contract is distinct from original-runtime parity. Shared-source body
and adapter agreement is a consistency check, not independent original proof.
Required missing or skipped cases block acceptance; contract exclusions and
changes need owner approval, never a silent denominator reduction.

## The two halves

| | the product (`src/`, `tests/`, the root) | `research/` (evidence) |
|---|---|---|
| Language | C++17, SDL3 + WebGPU (D2) | C11 dumps, Python pipeline, JSON |
| Rule | **All new game code goes here** | Nothing here runs the game |
| Entry docs | `README.md` → `docs/decisions.md` | `docs/overview.md` → `docs/pipeline.md` |
| Build | `./build.sh deps` (once), then `./build.sh {linux,windows,web}` | `python3 research/tools/coverage_report.py` (no deps) |

## Hard rules (violations = reverted work)

1. **Never hand-edit `research/recomp/`.** Generated output; edits are overwritten.
   Source of truth is `research/symbols/`.
2. **The product keeps the original `.X` files — no conversion pipeline.** The
   renderer is **SDL3 + WebGPU** (D2): `webgpu.h`, wgpu-native natively and
   emdawnwebgpu on the web, built from the repository root. DX9 was dropped in the
   Phase 5 cutover (2026-10-02) and its tree is deleted, so
   `research/evidence/parity-baseline/` is **history and framing evidence only**, not
   the appearance or behaviour target. Appearance references are the original's prints
   in `docs/reference/`. Read `docs/decisions.md` (D1–D14) before touching the
   product tree.
3. **`mvp/` is gone.** Retired 2026-10-01 after its contents were ported. Don't
   recreate it; decomp provenance lives in `research/`.
4. **Comment policy in the product tree:** explain *why*, cite RE provenance (`FUN_xxxxxx`,
   addresses). No restatement comments, no dead code.
5. **Run `coverage_report.py` before committing** research changes.
6. **Full diff review before EVERY commit** — see below. Not optional, no size
   exemption.
7. **Character+weapon combos, never bare fighters.** Every attack is a weapon attack
   (issue #26): battles, traces and tests bind a character AND a weapon (move table
   + item data). A bare fighter is a false claim, not a simplification — tests that
   exercise one without the other are rejected. Name combos as Name+N (`Rena 1` is
   her second weapon) or Name+Weapon (`Keiichi Invincible Iron`; atlas names in
   `docs/ASSET-CATALOG.md` §3.2). In code the helper is
   `gameplay::comboSlotLabel`; NN.dat number IS the weapon slot and file offset
   `0x114` carries the weapon id (verified 46/46 against `kWeaponIds`). A roster
   fighter that ends up with no weapon fails the launch loudly — only unknown
   (custom) characters fall back with a warning.

## MANDATORY — full diff review before EVERY commit

Read `git diff` **and** `git diff --cached`. This step cannot be skipped, no matter
how small the change. Review every changed file for:

- **Unused code** — dead branches, unused includes/members/functions left behind.
- **Debug helpers that are no longer useful** — temporary log lines, traces,
  fingerprints, counters added while investigating; remove them or gate them behind
  an env flag if genuinely valuable.
- **Repeated logic** — duplicated blocks that should be unified into one helper.
- **Verbose and useless comments** — comments narrating obvious code, stale
  references to removed code, or long-winded explanations of what the diff shows.

Fix everything found (or explicitly justify keeping it) before committing. A
skipped review is a process violation.

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
ctest --test-dir build/linux --output-on-failure
./tools/launch_original.sh            # the original, under Wine
python3 research/tools/coverage_report.py
```

Read `ctest`'s own summary rather than any count written in a document — every
added suite moves the denominator. Measured counts, the full command set and the
list that skips without game data are in `README.md` and
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
  recorded listing is in [`docs/DIRECTION-STATUS.md`](docs/DIRECTION-STATUS.md) P0-2.
- **Never force push.**
- **Never** `reset --hard`, `clean -fd`, `checkout .`, or delete a branch or
  worktree without first listing its unique commits (`git log main..<branch>`) and
  showing the owner. This governs **git state**, not source files: deleting a
  REPLACE file at its gate is an ordinary edit inside a reviewed commit
  (`DIRECTION.md` §7).
- **An uncommitted diff is never discarded.** It is committed in reviewable parts,
  or left exactly as found.
- Push scope: `research/decompiled`, `research/binary_data`, reviewed
  `research/symbols`, `research/progress`, docs, and reviewed source/tests/runtime
  caption assets under the product tree.
- Never commit: `research/recomp/`, game files, keys, `*.full.json`, build outputs
  (`build/`), fetched dependencies (`third_party/`), the leftover local toolchain
  trees under `remake/tools/`, and `.local-analysis/`.
- Full diff review before every commit — see above.

## Local-only (present on disk, absent from git)

`Higurashi-Daybreak/` (the game install), the fetched `third_party/` sources and
fonts (`./build.sh deps`), `build/`, the toolchain trees under `remake/tools/` that
predate the flattening, and `.local-analysis/`. Gyrotrope Black is bundled source
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
