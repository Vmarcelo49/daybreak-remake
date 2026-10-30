# Reference-core plan (proposal, 2026-10-30)

**Status: proposal, awaiting owner approval.** Until then [`../DIRECTION.md`](../DIRECTION.md)
remains the plan. Nothing here has been integrated.

## 1. The proposal in one paragraph

Stop translating combat by hand. Vendor the simulation from Ginkiha's `DaybreakRebuild`
as one library, unmodified where possible, and make it the only authority for battle
behaviour. Our engine keeps everything around it: SDL3 + WebGPU rendering, audio, input,
front end, settings and packaging. This is `DIRECTION.md` §3 Option B, narrowed to the
platform-free simulation; none of the bundle's Windows, Direct3D or DirectSound code comes
across.

## 2. What was measured

Measured on 2026-10-30 against the local bundle, unchanged, and the local install. The spike
sources are in the ignored `local-data/harness/reference-core-spike/`.

| Question | Result |
|---|---|
| Is the simulation platform-free? | Closure of `local_normal_projectiles.hpp` (which includes `development_animated_combat.hpp`): 423 files, 283,754 lines. External headers: only `xmmintrin.h` and `zlib.h` |
| Does it build on Linux? | Yes, with g++ 16 and clang, after forcing `<cstring>`, `<climits>`, `<set>` and `<cstdint>`. The six body modules rebuilt with the forced `<cstring>` took 12.5 s wall in parallel at `-O1` |
| Does it run on real data? | Yes. A headless harness following `RuntimeBattle::update`'s order ran a 3,600-tick 2v2 CPU match on the install's archives |
| Does it cover the roster? | 46/46 combos ran 2,400 ticks without an exception, with varied opponents and stages |
| Is it fast? | 40x real time at g++ `-O1`, 75x at clang `-O2` |
| Is it deterministic? | Same hash on repeat, and with g++ `-O1`, g++ `-O2` and clang `-O2`; a different seed gives a different hash. The hash covers position, heading, state and HP per tick. One machine and architecture only |
| Do scripted inputs reach real rows? | A crude Rena+0 script reached 23 states, including 300, 400, 40-44, 101, 113, 118-121, 124 and 128 |
| Can it live beside our code? | Yes. It linked in one binary with `foundation_gameplay` without symbol conflicts |
| Does the skeleton map to our model? | Rena+0: all 78 port frame names exist among the core's 79 bones. The first six show a +1 index offset (a root at 0). The other 45 combos were not compared |
| Is other logic platform-free too? | Also external-header free or SSE-only: HUD draw list, status HUD, result composition, award selector, animated camera, story scenario, dialogue script, scene protocol |
| What blocks ARM and WebAssembly? | SSE, used in only two simulation headers: `actor_controller_srt.hpp` and `actor_skin.hpp` |

**What this does not show.** It shows the code runs, repeats and covers the roster. It does
not show that it matches the original. The author's own report records one bounded comparison
of four combos, with its coverage gate still false, and calls full compatibility unproven.
No original runtime was executed for this proposal.

## 3. What we reuse

| Keep from our engine | Take from Ginkiha | Retire at cutover (M5), not before |
|---|---|---|
| `platform`, `gpu`, `render`, `shaders` | Simulation closure and the seven body modules | `fighter.{h,cpp}` (5,711 lines) |
| `assets` (`.X`, archives), `audio`, `movie` | Hit, damage, guard, knockdown, projectile pipelines | `move_behavior.h`, `melee_admission.h`, `shot_launch.h` |
| `input`, `settings`, `ui`, front end | CPU driver and decisions | `bot_brain`, `bot_input` |
| Packaging and release tooling | Match flow, awards, status and gauge logic | `match`, `projectile`, `match_economy`, as replaced |
| The 37 test files not coupled to `Fighter` | Camera and HUD logic, evaluated against ours | `native/` (1,849 lines) and `ginkiha_tables.h` |
| `research/` as an independent check | Later: story, dialogue and network protocols | 31 coupled test files (24,927 lines), once replaced |

The recent hand work is not wasted. The port's combat tests and addressed reads become
independent checks to run against the core; any disagreement is a finding to resolve.

## 4. Architecture

```
input ─► sim::Battle (wrapper) ─► vendored core
                 │  one-way read after each tick
                 ▼
         game::BattleView ─► renderer, HUD, audio, camera
```

- `remake/foundation/src/sim/core/`: the vendored files with attribution, plus a `PATCHES.md`
  listing every local change. Generated bodies are never reformatted.
- `remake/foundation/src/sim/battle.{h,cpp}`: the only file that includes the core. It owns
  the update order, currently spread through `RuntimeBattle::update`.
- `game::BattleView`: the read interface the product consumes. Today `main.cpp` has 170
  `gameplay::` uses, reads about 45 `Fighter` methods and calls 17 `Match` methods; that
  list sizes the interface.
- Bones: the renderer takes the core's `render_pose` through a name-based map, built once per
  rig and checked at load, never by assumed index.
- Effects, sound and voice: the core's request queues (`effect_requests`, `sound_requests`,
  `voice_requests`) are translated to our effect and audio systems.

## 5. Milestones

Each one ends with something an agent can run and check without a human or a window, except
where marked.

| # | Deliverable | Done when |
|---|---|---|
| **M1** | `foundation_sim` in CMake, plus a headless `simctl` CLI with scripted input and per-tick JSONL traces | `simctl` runs any roster and script; CTest pins 46/46 runs and determinism; a seeded mutation changes the hash |
| **M2** | Trust report: fuzzed input, invariants and a state coverage map per combo, plus comparison with the bundle's original-derived tables and traces and with `research/decompiled` on a sample | Report lists covered and unreached states, every crash or soft-lock, and each disagreement. Crashes and soft-locks are fixed in `PATCHES.md` or named |
| **M3** | `game::BattleView` extracted over the **legacy** path, no behaviour change | All current tests pass; `main.cpp` and renderer read gameplay only through the view |
| **M4** | Core backend behind `--sim=core`: fighters, weapons, stage collision, input, projectiles, effects, HUD, audio | Scripted captures show correct poses on Rena+0, then all 46 load and fight. **Owner playtest** on a chosen set |
| **M5** | Core becomes the default; legacy deleted in its own reviewed commit | Owner approves after playtest; full front-end loop passes; pre-cleanup revision recorded |
| **M6** | Product work from the frozen list: story, netplay, ARM and web, polish | Ordered by the owner after M5 |

The largest pieces are M3 and M4. Much battle presentation logic sits in `runtime_battle.hpp`
(2,297 lines) mixed with Direct3D, so weapon poses, trails and camera wiring must be
translated by hand into the wrapper or the renderer.

## 6. Why an agent can own this

- **Fast loop:** a full match in about a second, so one session can run thousands of
  scenarios instead of asking someone to play.
- **Own verification:** fuzzing, invariants, coverage maps and trace diffs need no display
  and no real-time control. Captures through `--out` cover visual checks.
- **One authority:** a behaviour question has one place to look, in place of two decision
  paths and 61 pilot mentions inside `fighter.cpp`.
- **Small surface:** new code is the wrapper, the view and the adapters. The core is read and
  patched, not rewritten.
- **Shorter records:** progress is one status table and `PATCHES.md`, not per-rule contract
  amendments.

What still needs the owner: playtests, feel, and rulings on disagreements that evidence
cannot settle.

## 7. Evidence rules

1. Evidence tiers stay. A core run is a capture of our build (tier 5), not original behaviour.
2. Agreement between the core and code adapted from it is a consistency check, not proof.
3. Independent checks are `research/decompiled`, the bundle's original-derived tables and
   traces, the prints, and owner observation.
4. Every core change cites its evidence and goes in `PATCHES.md`.
5. The metric becomes **N/46 running under `--sim=core`**, with coverage and open disagreements
   beside it. Original-runtime parity stays a separate column.

## 8. Risks and stop rules

| Risk | Response |
|---|---|
| The core is dense and hard to read (a 4,038-line integration header, offset-named fields) | Keep it behind the wrapper; document what we learn; patch narrowly |
| The core is wrong in places | M2 finds what it can; fixes go in `PATCHES.md`. Not fully preventable without original traces |
| A hidden platform or global dependency appears | M1 and M3 surface it. `application_battle_random.hpp` needs Windows only for its startup seed, and the spike seeds directly |
| Render adapter costs more than expected | M4 starts with Rena+0 poses alone. If poses cannot be mapped, stop and re-plan before more wiring |
| Hash is stable only per architecture | Accept for now. It matters for netplay, so re-test at M6 before promising cross-platform play |
| Legacy and core drift during migration | No new behaviour on the legacy path after approval; only fixes needed to keep it running |
| Repository size | About 284,000 vendored lines, no game assets. Acceptable; licence permission is already recorded |

Stop and ask if M2 finds the core broadly unusable, or if M3 shows the product cannot be
separated from `Fighter` without a rewrite of the front end.

## 9. Owner decisions

1. Approve this direction: the core becomes the authority, replacing Option A.
2. Approve the metric in §7.5 and retire the per-rule contract work after M4.
3. Decide what happens to 2h: this plan skips the separate Rena+0 cleanup and deletes all of
   the legacy path at M5.

On approval, `DIRECTION.md` is rewritten around this plan, `AGENTS.md`'s freeze lists and
bundle rule are aligned, and M1 starts.
