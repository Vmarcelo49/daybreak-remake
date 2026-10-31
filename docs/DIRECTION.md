# Direction — the reference core behind our engine

Approved by the owner on 2026-10-30, replacing the 2026-10-14 offline-first plan (whose
pilot closed green the same day; see [`SCOREBOARD.md`](SCOREBOARD.md)). Measurements and
reasoning: [`reports/reference-core-plan-2026-10-30.md`](reports/reference-core-plan-2026-10-30.md).

## 1. The plan in one paragraph

Stop translating combat by hand. Vendor the simulation from Ginkiha's `DaybreakRebuild` as
one library, unmodified where possible, and make it the only authority for battle behaviour.
Our engine keeps everything around it: SDL3 + WebGPU rendering, audio, input, front end,
settings and packaging. No Windows, Direct3D or DirectSound code from the bundle comes across.

## 2. Evidence position

- The core runs on real data for 46/46 combos, deterministically, without a window. That is
  execution evidence (tier 5), **not** evidence that it matches the original.
- The bundle's author reports one bounded comparison of four combos with its coverage gate
  still false, and calls full compatibility unproven.
- Agreement between the core and code adapted from it is a consistency check. Independent
  checks are `research/decompiled`, the bundle's original-derived tables and traces, the
  prints, and owner observation.
- Frame-perfect original-game control, new capture platforms, save states and emulator
  projects remain outside this plan.

## 3. Architecture

```
input ─► sim::Battle (wrapper) ─► vendored core
                 │  one-way read after each tick
                 ▼
         game::BattleView ─► renderer, HUD, audio, camera
```

| Location | Role |
|---|---|
| `src/battle/core/` | Vendored files, attributed. Every local change is listed in its `src/battle/core/PATCHES.md`. Generated bodies are never reformatted |
| `src/battle/battle.{h,cpp}` | The only product code that includes the core. Owns the update order recovered in `RuntimeBattle::update` |
| `game::BattleView` (M3) | The read interface the product consumes |
| `src/battle/simctl.cpp` | Headless runs, scripted input and per-tick traces |

Roster indices at the `sim::` boundary are the core's (`src/battle/core/character_names.hpp`), which differ
from our data-directory order. Every combo is still a character **and** a weapon.

## 4. Milestones

Each one ends with something an agent can run and check without a human or a window, except
where marked. The task list is [`DIRECTION-STATUS.md`](DIRECTION-STATUS.md).

| # | Deliverable | Done when |
|---|---|---|
| **M1** | `foundation_sim` in CMake and a headless `simctl` with scripted input and per-tick JSONL traces | `simctl` runs any roster and script; CTest pins 46/46 runs and determinism; a seeded mutation changes the hash |
| **M2** | Trust report: fuzzed input, invariants, a state coverage map per combo, and comparison with the bundle's original-derived tables and traces and with `research/decompiled` on a sample | Report lists covered and unreached states, every crash or soft-lock, and each disagreement. Crashes and soft-locks are fixed in `PATCHES.md` or named |
| **M3** | `game::BattleView` extracted over the **legacy** path, no behaviour change | All current tests pass; `src/app/main.cpp` and the renderer read gameplay only through the view |
| **M4** | Core backend behind `--sim=core`: fighters, weapons, stage collision, input, projectiles, effects, HUD, audio | Scripted captures show correct poses on Rena+0, then all 46 load and fight. **Owner playtest** on a chosen set |
| **M5** | Core becomes the default; the legacy path is deleted in its own reviewed commit | Owner approves after playtest; full front-end loop passes; pre-cleanup revision recorded |
| **M6** | Product work: story, netplay, ARM and web, polish | Ordered by the owner after M5 |

**M1 to M5 are closed. The project is in M6**, where the owner orders the work directly. The
priority is online: [`ONLINE-PLAN.md`](ONLINE-PLAN.md).

The separate Rena+0 cleanup (old step 2h) is skipped: M5 removes the legacy path as a whole.

## 5. What is kept and retired

| Keep from our engine | Take from Ginkiha | Retire at M5, not before |
|---|---|---|
| `platform`, `gpu`, `render`, `shaders` | Simulation closure and the seven body modules | `fighter.{h,cpp}` |
| `assets`, `audio`, `movie` | Hit, damage, guard, knockdown and projectile pipelines | `move_behavior.h`, `melee_admission.h`, `shot_launch.h` |
| `input`, `settings`, `ui`, front end | CPU driver and decisions | `bot_brain`, `bot_input` |
| Packaging and release tooling | Match flow, awards, status and gauge logic | `match`, `projectile`, `match_economy`, as replaced |
| Tests not coupled to `Fighter` | Camera and HUD logic, evaluated against ours | `native/`, `ginkiha_tables.h` and the coupled tests, once replaced |
| `research/` as an independent check | Later: story, dialogue and network protocols | |

M5 removed the legacy path; its last revision is `e9347627`. Bundle code is vendored with
attribution; original game assets are never
committed.

## 6. Verification and reporting

Evidence ordering: original runtime observations > addressed recovered original code >
original prints or owner observation > install-backed automated tests > captures of our
build > provisional port rules. A build is not verification. A capture is not a live run. A
skip is not a pass.

**The metric is `N/46 running under --sim=core`**, reported from M4 with coverage and open
disagreements beside it. Original-runtime parity stays a separate column and is `not
verified` until original-runtime evidence exists. The per-rule contract work
([`PILOT-EVIDENCE-CONTRACT.md`](archive/PILOT-EVIDENCE-CONTRACT.md)) ended with M4.

## 7. Stop rules

| Risk | Response |
|---|---|
| The core is dense and hard to read | Keep it behind the wrapper; document what we learn; patch narrowly |
| The core is wrong in places | M2 finds what it can; fixes cite evidence and go in `src/battle/core/PATCHES.md` |
| A hidden platform or global dependency appears | M1 and M3 surface it; patch or stop and ask |
| Pose mapping fails in M4 | Stop and re-plan before more wiring. M4 starts with Rena+0 poses alone |
| Hash stable only per architecture | Accepted for now; re-test before promising cross-platform netplay |

Stop and ask if M2 finds the core broadly unusable, or if M3 shows the product cannot be
separated from `Fighter` without rewriting the front end.

No original code patching, global desktop input or unannounced desktop takeover. Original
runs obey the binary pin and repository safety rules in [`../AGENTS.md`](../AGENTS.md). Use
`--no-audio` for remake verification.
