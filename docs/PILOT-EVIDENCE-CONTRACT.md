# Rena+0 pilot — minimal independent contract (v2, **approved** 2026-10-16 for the stated Rena+0 scope)

**Status: APPROVED 2026-10-16 by the repo owner, for the stated Rena+0 pilot scope only.**
Reviewed content: `sha256 c5df99313725d80ee1ba9ae8d7161d4ca252512349ac65e962f37730565a18c6` — the identifier of the revision the owner approved. This
status block and the title are metadata added afterwards; the acceptance content is unchanged,
verified by reconstructing it from this file (revert the title and this block) and hashing to the
same value. The file's own hash is deliberately not recorded here: any edit would invalidate it.

The owner's earlier review items, kept as the record of what was fixed: The owner reviewed candidate v1 and withheld approval pending:
(1) a fail-closed required-case set, (2) every acceptance field mapped to a case or declared
unsupported, (3) one consistent tolerance per observable, and (4) companion documents that
agree with the candidate. §2b, §8 and §9 record the fixes; approval is the owner's to give. F1-2 drafted it; F1-7 froze
this candidate; P2-0b is the approval gate, and only the owner approves. The F1-2 content is: our own
observable field set, sampling domain, provenance, tolerances and exclusions,
assembled because those fields are observable and pilot-relevant — **not** a
reconstruction of the reference's unpublished 59-field schema (Q5's superseded
implication, [`DIRECTION.md`](DIRECTION.md) §4 Phase 1 steps 3 and 6). Covered and uncovered cases are explicit in §10; a change to any acceptance field,
unit, tolerance or exclusion after approval needs a version bump (§7). Nothing here may be cited
as acceptance before that.

**Owner's approval condition (2026-10-16):** approval waits until the Phase 1 and Phase 2
gaps are closed, focusing on **sampling verification** (this document's §11) and **proper
documentation** (this contract, [`PILOT-SEAM.md`](PILOT-SEAM.md) and the task rows).
Recording the condition is not approval.

Companion document: [`PILOT-SEAM.md`](PILOT-SEAM.md) — the seam spec and per-field
dispositions that §2's observables map onto.

Combo: **Rena+0 only** (`character_index()==0`, weapon slot 0, item 001). Data
identity: `data/rena/00.dat` + `data/item/001.dat` + the rig the move table names
(`00.x`, 124 sets), all read through the production asset loader.

## 1. Sampling domain

| Item | Value |
|---|---|
| Compared object | the production `Match`/`Fighter` path (`foundation_gameplay`), device-free |
| Domain | one row per fighter per simulation tick; slot order as `Match::fighter(i)` |
| Cadence | `FixedStep::tickRate` = **60 Hz**, `seconds` = 1/60; F1-9 asserts it (D15) |
| Tick origin | the case's first step after `Match::reset`; startup is stepped normally, never forced |
| Per case | `Match::reset` (config spawn/facing/hypermode/gauge/HP, weapon, moves) then `FixedStep::seconds` steps |
| Inputs | explicit `PlayerState` per fighter, `compute_edges` once per tick; previous-input semantics are the port's edge contract |
| Collision | declared per case: open-field (no movement-collision provider) or staged; never changed by this contract |
| RNG | `SimulationRng`, seed `kDefaultSeed` 5489 = the original's `0x1571`, reset per case (see §3) |
| Fighters | the case's actor(s) plus a neutral equipped dummy fed `nullptr` input where the case needs an opponent |

## 2. Minimal field set

Role `A` = acceptance field (a required case may fail on it); `D` = diagnostic
(feeding the report, never a pass/fail by itself). Tolerance: `exact` for
int/enum/bool/count; a float uses the **per-observable absolute tolerance in §2b**, which
is the value the runner applies; `n/a` = excluded from comparison. `[R?]` = port accessor whose own comment cites recovered code
(`FUN_`/actor offset); `[P]` = port-only. Units: `UNSTATED` is recorded as
unstated, never guessed. Actor offsets and per-field dispositions for the locomotion
seam are in [`PILOT-SEAM.md`](PILOT-SEAM.md) §1 and §9; a field listed here as
acceptance-observable does not imply the body's own channel for it is mapped.

| Family | Observable (accessor) | Unit | Provenance | Role/tol |
|---|---|---|---|---|
| locomotion | `Fighter::state()` | enum | port labels; move ids at actor `+0xadec` (`fighter.h:868`) [R?] | A / exact |
| locomotion | `Fighter::action_state()` | enum row | `fighter.h:551`; row is actor `+0xadec` [R?] | A / exact |
| locomotion | `Fighter::position()` | u (world, Y-up) | `fighter.h:864`; unit at `game/fighter_pose.h:19-20` [P] | A / 1e-3 (§2b) |
| locomotion | `Fighter::facing_yaw()` | rad | `fighter.h:865,936` [P] | A / delta in degrees at 1e-2 (§2b) |
| locomotion | `Fighter::airborne()` | bool | `fighter.h:870`; `m_grounded:1100` [P] | A / exact |
| locomotion | `Fighter::anim_set_index()` / `anim_fallback()` | index / bool | `fighter.h:876-882`; tag from move table row [R?] | A / exact |
| locomotion | `Fighter::move_phase()` / `phase_elapsed()` | count / tick | `fighter.h:763-764` [R?] | A / exact |
| locomotion | `Fighter::move_speed()` | u-per-tick | `fighter.h:767`; ranges `:242-244` [R?] | D / 1e-3 |
| dash | `Fighter::dash_move_id()` | enum (20/23/24/27 ground, 30 air) | `fighter.h:556`; `dash_move_for:1215` [R?] | A / exact |
| dash | `Fighter::air_dash_context()` | bool | `fighter.h:553` [R?] | A / exact |
| dash | stamina spend during dash/guard | count 0..100 | `fighter.h:867`; constants `:247-306` [P] | A / exact |
| jump | jump-chain rows via `anim_set_index()` (40→41→42) | index | `fighter.h:1219-1223` (live `FUN_0043ffc0` cases 0x28/0x29/0x2a) [R?] | A / exact |
| jump | landing/takeoff/apex **edges** | — | **not exposed** (§5 item 3); derived from the `airborne()` falling edge | D / derived |
| shot | `Fighter::shot_move_id()` (Rena+0: ground tap 400, air tap 402) | enum | `fighter.h:560`; `MoveProgram::shot` [R?] | A / exact |
| shot | `Fighter::last_shot_tier()` | enum Tap/Yellow/Red/Ex | `fighter.h:607`; labels provisional `projectile.h:62-71` [P] | A / exact |
| shot | `MatchFrame::shotFired[i]` / `shotsSpawned` | bool / count | `match.h:131,99-100` [P] | A / exact |
| shot | `MatchFrame::shotPoints[i]` | u | `match.h:134-135` [P] | D / 1e-3 |
| charge | `Fighter::charge_gauge()` | 0..1000 | `fighter.h:620,721`; `FUN_004219a0:19`, `FUN_0041dcb0:66`, `FUN_0041f580:96-99`, `FUN_00508a60:91` [R?] | **D — unsupported**: reads 1000 at rest and does not move under SPECIAL or shooting, so no case asserts it (§2b lists it as unsupported) |
| charge | `Fighter::charge_tier()` | enum | `fighter.h:911`; `fighter.cpp:2874-2880` [R?] | A / exact |
| charge | `yellow_hold_sec()` / `red_hold_sec()` | seconds | `fighter.h:614-615`; `30/tickRate` from `FUN_0043f3e0` [R?], explicit PORT RULE `:609-613` | A / 1e-4 (asserted: 0.5 and 3.5) |
| charge | `main_whole()` / `charge_whole()` | count | `fighter.h:905-908` [P] | A / exact |
| melee | `Fighter::attack_move_id()` (300/310/311/320/330/331/332) | enum | `fighter.h:545`; `FUN_00445ee0` + admission dispatcher [R?] | A / exact |
| melee | `melee_in_active()` / `melee_in_recovery()` | bool | `fighter.h:757-762`; `FUN_0063b470` window [R?] | A / exact |
| melee | `swing_hit_count()` | count | `fighter.h:740-744` [P] | A / exact |
| melee | `MatchFrame::swingStarted[i]`, `meleeHit[i]`, `meleeVictim[i]` | bool / index | `match.h:102-103,110` [P] | A / exact |
| melee | `preview_melee_swing()` damage/hitstun/radius | HP / tick / u | `fighter.h:318-328,815-817,821-823`; radius `FUN_0063b470` [R?] | D / exact |
| guard | `state()==Guard`, `guardStarted[i]`, `guard_exhausted()` | enum / bool | `fighter.h:755,868`; `match.h:142`; predicate `FUN_00637950` blocked branch `fighter.h:127-141` [R?] | A / exact |
| guard | `MatchFrame::blocked[i]` | bool | `match.h:145`; **explicitly provisional** (port 20% block) | D / exact |
| hit | `hp()`, `is_alive()`, `take_damage()` result | HP 0..100 (original ×100) | `fighter.h:443-447,657,866,869`; `FUN_00639160`/`FUN_00637950` offsets [R?] | A / exact |
| hit | `MatchFrame::koCredits[i]` / `overkillHits[i]` / `respawned[i]` | count / bool | `match.h:88,97-98` [R?] | `respawned[i]` A / exact; **`koCredits`/`overkillHits` D — unsupported** (0 on both indices through update 100 after a KO; §2b) |
| hit | applied hitstun length | tick | **not exposed** (§5 item 3); `m_stateTimer` has no accessor | excluded |
| KO | `Fighter::pending_ko()` | bool | `fighter.h:483` [R?] | **D — unsupported**: read 0 for the victim at and after the KO tick; the KO is signalled through `MatchEconomy::koAt` (§2b) |
| KO | `MatchEconomy::koAt()` / `kos(side)` | seconds / count | `match_economy.h:297,314-316`; `kRespawnSec` labelled port rule `:105` [P] | A / exact |
| KO | `roundOver` / `roundOverSide` / `roundEnd()` | bool / side / enum | `match.h:89-92`; `match_economy.h:303-310`; `FUN_00635d40` [R?] | A / exact |
| driver | `FixedStep::tickRate` / `seconds` | Hz / s | `fixed_step.h:13,17-19`; D15 | A / exact |
| driver | `SimulationRng` draw count per case | count | `simulation_rng.h:38-51`; `FUN_0065d150`/`FUN_0065d0c0` [R?] | D / exact |


## 2b. Acceptance map: every field to its case, or declared unsupported (owner item 2)

Enforced by `tests/fixtures/rena0/MANIFEST.txt` and by the runner's own independent
required lists, so neither a deleted fixture, a deleted manifest line nor a removed
assertion can shrink this scope silently (§8). Tolerances here are the ones the runner
actually applies (owner item 3): ints, enums and bools compare **exactly**; floats use the
stated absolute tolerance.

| Acceptance field (§2) | Fixture field | Required fixture | Tolerance |
|---|---|---|---|
| `action_state()` | `state` | `rena0-idle-walk-turn-stop` | exact |
| `state()` | `state_enum` | `rena0-melee-ground-300`, `rena0-guard-hold` | exact |
| `position()` | `x`, `z`, `step` | `rena0-idle-walk-turn-stop` | 1e-3 |
| `facing_yaw()` | `turn_deg` (delta; absolute yaw not asserted) | `rena0-idle-walk-turn-stop` | 1e-2 deg |
| `airborne()` | `airborne` | `rena0-jump-chain` | exact |
| `anim_set_index()`/`anim_fallback()` | `anim_row`, `anim_set` | `rena0-idle-walk-turn-stop`, `rena0-jump-chain` | exact |
| `move_phase()`/`phase_elapsed()` | `phase`, `elapsed` | `rena0-idle-walk-turn-stop` | exact |
| `dash_move_id()` | `dash_row` | `rena0-ground-dash-left` | exact |
| `air_dash_context()` | `air_dash_context` | `rena0-air-dash-left` | exact |
| `stamina()` | `stamina` | `rena0-guard-hold` | exact |
| jump-chain rows | `anim_row`, `anim_set` | `rena0-jump-chain` | exact |
| `shot_move_id()` | `shot_row` | `rena0-tap-shot` | exact |
| `last_shot_tier()` | `shot_tier` | `rena0-tap-shot` | exact |
| `shotFired[i]`/`shotsSpawned` | `shot_fired`, `shots` | `rena0-tap-shot` | exact |
| `charge_tier()` | `charge_tier` | `rena0-charge-hold` | exact |
| `yellow_hold_sec()`/`red_hold_sec()` | same names | `rena0-charge-hold` | 1e-4 s |
| `main_whole()` | `main_whole` | `rena0-tap-shot` | exact |
| `attack_move_id()` | `attack_row` | `rena0-melee-ground-300` (+ the six variants) | exact |
| `melee_in_active()`/`melee_in_recovery()` | `melee_active`, `melee_recovery` | `rena0-melee-ground-300`, `rena0-hit-ground-300` | exact |
| `swing_hit_count()` | `swing_hits` | `rena0-hit-ground-300` | exact |
| `swingStarted`/`meleeHit`/`meleeVictim` | `swing_started`, `melee_hit`, `melee_victim` | `rena0-melee-ground-300`, `rena0-hit-ground-300` | exact |
| Guard state / `guardStarted` / `guard_exhausted` | `state_enum`, `guard_started`, `guard_exhausted` | `rena0-guard-hold` | exact |
| `hp()`/`is_alive()`/damage | `dummy_hp`, `dummy_alive`, `melee_hit` | `rena0-hit-ground-300`, `rena0-ko-ground-300` | exact |
| `respawned[i]` | `dummy_respawned` | `rena0-ko-ground-300` | exact |
| `koAt()` | `dummy_ko` | `rena0-ko-ground-300` | exact |
| `roundOver`/`roundEnd()` | `round_over`, `round_end` | `rena0-round-timeout` | exact |
| balloon economy | `balloon1` | `rena0-round-timeout` | 1e-3 |
| dummy neutrality | `dummy_static` | `rena0-idle-walk-turn-stop` | exact |
| `FixedStep::tickRate`/`seconds` | — | asserted by `fixed_step_test` (F1-9), outside the fixture runner | exact |

**Declared unsupported (diagnostic/excluded, with the reason):** `charge_gauge` (static at
1000 under SPECIAL and shooting), `koCredits` and `overkillHits` (0 across both indices
through update 100 after a KO), `pending_ko` (0 for the victim at and after the KO tick),
`charge_whole`, `round_over_side` and `kos` (their asserted representatives cover the
signal). The same list is in `MANIFEST.txt` as `unsupported` lines, and the runner reports
the count on every run.

## 3. Determinism and RNG policy

`SimulationRng` reproduces the original's MT19937 (tempering `FUN_0065d150`, init
`FUN_0065d0c0` with `0x1571` = 5489). The **algorithm, draw order within a body and
modulo ranges** are what it reproduces; **stream position cannot match**, because the
original draws from one global stream in its own frame order and this port does not
attempt bit-parity (`simulation_rng.h:18-21`). Therefore: every case resets the
stream (`Match::reset` → `m_rng.reset()`), the seed is recorded with the result, and
any output whose value depends on cross-actor draw order is **diagnostic only**.
`modulo(0)` consumes nothing, so an unset spread may not advance the stream
(`simulation_rng.h:47-51`).

## 4. Expected transitions and events (source-backed where cited)

| Case | Expectation | Source |
|---|---|---|
| idle → walk → stop | 0 → 10 on held direction, 10 → 0 on release; row-0/row-10 clips, no fallback; zero displacement when stopped | `FUN_0043ffc0` cases 0/10; verified by the F1-5 probe (appendix) |
| walk step | 7.2 u/update, cadence-independent | `FUN_0043ffc0:167` (`0x40e66666`) |
| ground dashes | Left→24, Right→23, Up→20, Down→27 | `FUN_00445ee0:86-95`; `dash_move_for` |
| jump | 40 → 41 → 42 chain, landing derived from the `airborne()` edge | `FUN_0043ffc0` 0x28/0x29/0x2a |
| tap shot | ground 400 / air 402, one `shotFired` edge, `shotsSpawned` ≥ 1 | `Fighter::shot_move_id`; `MoveProgram::shot` |
| charge | Yellow at 30 updates, Red at 30 + the bound `chargeThreshold`, gauge +40 (or +5 while status slot 6 is active), clamped 1000 | `FUN_0043f3e0`; `fighter.h:721` |
| melee | 300/310/311/320/330/331/332 by input context; once-per-victim-per-swing | admission dispatcher; `fighter.h:740-744` |
| guard | Guard state while held; stamina drains 25/s; `guardStarted` edge; `blocked` provisional | `fighter.h:304,127-141` |
| hit | `take_damage` returns Hit/Overkill/Ko; credits and overkill reported per frame; HP scale ×100 | `FUN_00639160`, `FUN_00637950` |
| KO | `pending_ko` once, economy `koAt`/`kos`, respawn lock, round end by burst or timeout | `match_economy.h:297-310` |

## 5. Exclusions and uncovered cases

Excluded from acceptance (recorded, never silently dropped):

1. **Original-runtime parity of any field** — no coherent original per-update trace
   exists (F1-1 report item 6). Sampled reads and synthetic-fixture handler traces
   are not substitutes.
2. **Stream-position-dependent outputs** — see §3.
3. **Fields the port does not expose today** (from the F1-2 inventory): per-shot
   projectile identity and lifecycle records; attacker-side contact records (move id,
   phase, tick at contact); the hitstun length actually applied; per-channel
   animation clocks and blend state; landing/takeoff/apex events; a per-fighter tick
   index; per-shot spawn source (move row, muzzle slot); per-slot hit-status power.
   A case that cannot be checked without one of these records it as a named gap
   rather than inventing an accessor.
4. **The author's 59-field schema, field names and defined/raw classification** —
   not shipped (F1-1 items 1-4); this contract is ours and does not reproduce it.
5. **`blocked[i]` and effect/voice provenance** — provisional port rules; diagnostic.
6. **Multi-actor and environmental interactions** beyond what each case declares.

## 6. Evidence tiers

Per claim: install-backed automated test = tier 4; addressed recovered code cited
above = tier 2 expectations (source-backed, not runtime); port accessors and
provisional rules = tier 6; the two bundle traces = synthetic-fixture handler
evidence, not runtime. Shared-source agreement between the port and the bundle is a
consistency check only.

## 7. Change policy

This candidate v2 is frozen for re-review and only the owner approves it
(P2-0b). After approval, any change to an acceptance field, unit, tolerance or
exclusion needs a **version bump and owner approval** — never a quiet adjustment to
reach green ([`DIRECTION.md`](DIRECTION.md) §4 Phase 1 step 6).

## 8. Fixture format and runner (F1-3)

Fixtures are plain text under `remake/foundation/tests/fixtures/rena0/`, one case per
file, run device-free against the production `Match`/`Fighter` by
`tests/rena0_fixture_test.cpp` (not a second engine). Input tokens are the repo's own
`--script` vocabulary through `input::parse_script_line`
(`src/input/input.h:133-146`), so fixtures and scripted runs cannot drift apart.

| Directive | Meaning |
|---|---|
| `combo <character> <weapon>` | required; the real `NN.dat` + item + rig identity |
| `seed <uint32>` | required; today must equal `SimulationRng::kDefaultSeed` (5489) |
| `spawn <slot> <x> <y> <z>` | slot 0 actor, slot 1 neutral equipped dummy |
| `collision open-field` | required; staged fixtures are not implemented |
| `input <tick> <TOKEN...>` | per-tick input mask; `-` releases all |
| `expect <tick> <field> <value>` | one assertion at that tick |
| `place_at_attack <tick\|active>` | move the dummy onto the attacker's **posed attack volume** via `test::Combo::placeAtAttack`, the helper the device-free melee tests use (`active` = on every tick the swing is active) |
| `dummy_start_hp <n>` | `MatchConfig::startHP[1]`, the port's own launch-time injection |
| `trace <tick>` | **authoring aid only**: prints the tick's key fields instead of asserting, so anchors can be read off one run; tracked fixtures must not depend on its output |

| `expect` field | Derivation |
|---|---|
| `state` | `Fighter::action_state()` (numeric row) |
| `anim_row <n>` | current set == `first_set_index(n)` **and** not `anim_fallback()` |
| `phase`, `elapsed` | `move_phase()`, `phase_elapsed()` |
| `dash_row` | `dash_move_id()` |
| `airborne`, `hp`, `stamina` | the matching accessors |
| `x`, `z` | world position components (u) |
| `step` | displacement magnitude on that update (u) |
| `turn_deg` | signed yaw change on that update, wrapped to ±180° |
| `dummy_static` | dummy position unchanged from its reset spawn |
| `anim_set <n>` | the raw bound set index (pins a chain link whose move-row identity is unresolved) |
| `state_enum <n>` | `Fighter::state()` as its enum value (needed because `action_state()` collapses Guard/Hit/KO onto 0) |
| `shot_row` | `Fighter::shot_move_id()` |
| `shots`, `shot_fired` | `MatchFrame::shotsSpawned`, `shotFired[0]` (one-frame edge) |
| `guard_started`, `melee_hit` | `MatchFrame::guardStarted[0]`, `meleeHit[0]` (one-frame edges) |
| `attack_row` | `Fighter::attack_move_id()` (300-family entry) |
| `charge_tier`, `charge_gauge` | `Fighter::charge_tier()` (Tap 0 / Yellow 1 / Red 2), `charge_gauge()` (0..1000) |
| `melee_active`, `swing_started` | `Fighter::melee_in_active()`, `MatchFrame::swingStarted[0]` |
| `dummy_hp` | `Match::fighter(1).hp()` |
| `dummy_ko`, `dummy_respawned` | `MatchEconomy::koAt(1) >= 0`, `MatchFrame::respawned[1]` |
| `ko_credit` | `MatchFrame::koCredits[0]` (see the open question on the KO row of §10) |

Rules: startup is stepped normally from BattleStart (never forced); an unknown directive
or `expect` field is a failure, not a skip; a data-free checkout exits 77 and is reported
Skipped, never a pass. Tolerances are per observable and are the ones §2b states: ints,
enums and bools exactly, floats at the §2b absolute tolerance (`x`/`z`/`step`/`balloon1`
1e-3, the hold-seconds 1e-4, `turn_deg` 1e-2 degrees), reported with the tolerance in the
failure message.

**Body tests are not acceptance cases (P2-5).** `rena0_body_test` and
`rena0_admission_body_test` exercise recovered bodies with explicit scalars, independent of
Match/Fighter; their checks are supporting evidence for the seam and must not be counted
into this contract's case or field totals. Acceptance remains the 20 fixtures and the §2b
fields, enforced by the manifest.

**Fail-closed acceptance set (owner item 1).** `MANIFEST.txt` names the required fixtures,
the twelve case rows and the acceptance fields with the fixture that must assert each; the
runner also carries its **own** required lists (the eleven §4 Phase 2 cases and the §2b
observables) so neither file can shrink the scope alone. The run fails when a listed
fixture is missing, when a required case or acceptance field is no longer declared, when a
fixture stops asserting a field it is supposed to assert, or when the manifest itself is
missing. Unreferenced extra fixtures are allowed and counted as extras — an extra fixture
cannot shrink coverage, only add to it. Verified by mutation: deleting a required fixture
fails with `required fixture … is missing`, deleting a `field` line fails with `no longer
declares the acceptance field 'shots'`, deleting a required `case` line fails with `no
longer declares the required target case 'ko'`, and removing the assertion itself fails
with `does not assert field 'shots'`. A fixture's own header comment must cite the code or artifact behind each
expectation, and must label values that only record current port behaviour as such.

`seed`: `Match` resets its own stream and exposes no seeding entry point, so a fixture
naming any other seed **fails loudly** rather than silently running the default stream
(P2-2 asks which RNG the bodies expect).


### Commands (F1-6: no manual steps)

```bash
cmake --build remake/foundation/build/linux --target rena0_fixture_test rena0_locomotion_observation_test -j 4
ctest --test-dir remake/foundation/build/linux --output-on-failure -R '^rena0_(fixture|locomotion_observation)'
```

Exit codes: `0` all fixtures and the F1-5 probe pass; `1` a fixture or expectation
failed; `77` no game install reachable — CTest reports it Skipped, which is never a
pass. Neither case needs a device, a window, audio or the original game.

Fixtures present (F1-3, twenty): `rena0-idle-walk-turn-stop` (state admission and clip rows
from `FUN_0043ffc0:84-179`, 7.2 u/update from `:167`, turn reset from `:121-166`),
`rena0-ground-dash-left`/`-right` (rows 24/23 from `FUN_00445ee0:86-95`),
`rena0-jump-chain` (chain 40→41→42 from `FUN_0043ffc0` cases 0x28/0x29/0x2a plus the
landing edge), `rena0-guard-hold` (Guard state, edge and the 25/s drain from
`fighter.h:304`) and `rena0-tap-shot` (row 400 bound by update 12 and the shot spawning
on update 13 = the body's frame 12). Added since: `rena0-ground-dash-up`/`-down` (rows 20/27),
`rena0-air-dash-left` (row 30 after a jump and a double tap), `rena0-melee-ground-300`
(the ground entry, its `AttackA` state and the active window) and `rena0-charge-hold`
(Tap → Yellow at the cited 30 updates → Red in updates 206-212). Added since: `rena0-hit-ground-300` (the 300 swing
connecting through the posed-volume placement, 8 HP) and `rena0-ko-ground-300` (one lethal
hit on a dummy launched at 8 HP). Added since: the remaining 300-family variants
`rena0-melee-back-310`, `-lateral-311`, `-forward-dash-330`, `-air-320`,
`-lateral-dash-331` and `-air-dash-332` (331/332 were **new** evidence, not previously
asserted by any test). Every §4 Phase 2 target case now has at least one fixture, plus a
`rena0-round-timeout` case for the timed-round path.

Findings recorded while extending the set: `red_hold_sec` is **3.5 s** (so the Red boundary
is update **210**, tightening the earlier 206-212 window) and `yellow_hold_sec` is 0.5 s,
both matching the cited `30/tickRate` formula; the **round clock also runs during the
60-update BattleStart**, so `time_limit 1` expires before a fixture's tick 0 and the timed
fixture needs a 2-second limit with the transition between updates 59 and 60; and
`charge_gauge` never moves under SPECIAL or shooting, which is why it is declared
unsupported in §2b.

Sensitivity, run and recorded: an edited copy with `expect 4 step 8.2` fails as
`tick 4 step exp 8.200000 got 7.200000` (exit 1), and `expect 4 anim_row_typo 10`
fails as `unknown field 'anim_row_typo'` (exit 1). Both mutations were made in `/tmp`
copies; the tracked fixtures are unmodified.


## 9. Repeatability and sensitivity report (F1-4)

Campaign run 2026-10-16 against the F1-3 fixtures on this revision, all device-free.
Mutations were made in `/tmp` copies; the tracked fixtures and the runner are
unmodified.

| Check | Expected | Observed |
|---|---|---|
| Tracked set run 3x | identical output, exit 0 | stdout **byte-identical**, exit 0/0/0; `RENA0_FIXTURES: PASS (3 fixtures, 60 Hz, skips=0)` |
| Wrong **input**: `input 4 RIGHT` → `LEFT` | the same comparison catches it | `tick 4 turn_deg exp 19.000000 got -19.000000`, exit 1 |
| Wrong **output**: `expect 4 step 7.2` → `8.2` | caught | `tick 4 step exp 8.200000 got 7.200000`, exit 1 |
| Unknown expectation field `anim_row_typo` | rejected, not ignored | `unknown field 'anim_row_typo'`, exit 1 |
| Missing `seed` | required field cannot be omitted | `missing seed`, exit 1 |
| Missing `collision` | required scope cannot be omitted | `missing collision scope`, exit 1 |
| Missing `combo` | identity cannot be omitted | `missing combo`, exit 1 |
| No `expect` line | an empty case is not a pass | `no expectations`, exit 1 |
| Empty fixture directory | a missing required case is not a pass | `no .fixture files under …`, exit 1 |
| One good + one bad fixture | a failure cannot hide beside a pass | `RENA0_FIXTURES: FAIL (1 of 2)`, exit 1 |

The F1-5 probe carries its own repeatability evidence (three reset cases, legacy and
proposal traces equal, observation-off equal) and its seeded wrong-speed failure
(exit 1) in Appendix A. Denominator policy: the only skip is the no-install case
(exit 77, reported Skipped and **never** counted as a pass); a required case that
cannot run fails.

## 10. Coverage matrix of the §4 Phase 2 target cases (F1-8)

Status: **covered** = an F1-3 fixture asserts it; **partial** = existing install-backed
tests exercise it but no fixture records its expectations; **uncovered** = neither.
Tiers per the repository ordering. Original-runtime parity is **not verified for any
case** — no coherent original per-update trace exists (F1-1 item 6).

| # | Target case | Status | Evidence today | Tier | Named gap |
|---|---|---|---|---|---|
| 1 | Idle | covered | `rena0-idle-walk-turn-stop.fixture` (state 0, step 0, row-0 clip) | 4 + 2 (`FUN_0043ffc0:84-179`) | — |
| 2 | Walk | covered | same fixture (state 10, row-10 clip, 7.2 u/update, ±19° turn) | 4 + 2 (`:167`, `:121-166`) | analog stick walk not covered |
| 3 | Ground dashes | **covered** | four fixtures pin rows 24/23/20/27 with their row clips and grounded state | 4 + 2 (`FUN_00445ee0:86-95`) | dash *cancels* and dash-length variants are not covered |
| 4 | Jump / landing | **covered** | `rena0-jump-chain.fixture`: row 40 at update 0, row 41 at 4-6, a further chain set at 10, row 42 at 30, airborne at 47, landed at 48 | 4 + 2 (`FUN_0043ffc0` 0x28/0x29/0x2a) | the chain is **phase-driven, not apex-driven** (the physics apex is update 24 while row 42 starts by 30 and covers most of the flight); the update-10 chain row's identity is unresolved and asserted by raw set index; landing is still a derived edge, not an event (§5 item 3) |
| 5 | Air dash | **covered** | `rena0-air-dash-left.fixture`: airborne at 11, row 30 and its clip at 14 after a jump and a double tap | 4 + 2 | air-dash **cancels** are still uncovered (the bundle's own capture missed them too) |
| 6 | Tap shot | **covered** | `rena0-tap-shot.fixture`: row 400 bound by update 12, `shots`/`shot_fired` on update 13 — the State-400 body's frame 12 once the press is frame 0 | 4 + 2 (`battle_rena_ground_shot.hpp:40-44`) | no per-shot identity or lifecycle record (§5 item 3); only the single tap, not the charge levels |
| 7 | Charge levels | **covered** | `rena0-charge-hold.fixture`: Tap at 0, Yellow at 30 with `yellow_hold_sec` **0.5 s**, still Yellow at 205, `red_hold_sec` **3.5 s** and Red at the matching update **210** | 4 + 2 (`FUN_0043f3e0`, `fighter.cpp:2727-2735`) | the charge→shot hand-off is not covered, and `charge_gauge` is **declared unsupported** (§2b): it reads 1000 at rest and does not move under SPECIAL or shooting, so the seam's `+0x834` mapping stays unresolved |
| 8 | 300-family melee string | **covered** | all seven entries have fixtures: ground 300 (clip, `AttackA` = enum 3, `swing_started`), back-held 310, lateral 311, air 320, forward-dash 330, lateral-dash 331 and air-dash 332 (the last two were new evidence); `rena0-hit-ground-300`/`-ko-ground-300` cover contact | 4 + 2 | **Finding, not a coverage gap:** the same row 300 reports its melee active window at updates **14-19 with the opponent within reach** and **25-30 with it out of reach** — same six-update length, shifted eleven updates — measured with held and tap inputs alike, so the distance is the factor, not the input or the placement. The plausible cause (an approach phase skipped when the target is already in reach) is a **hypothesis**, established neither by addressed code nor by the bundle; the audit test asserts rows, not windows, so it cannot see this |
| 9 | Guard | **covered** | `rena0-guard-hold.fixture`: `guard_started` edge, `state_enum 6` while held, and a full second of held guard costing exactly 25 of 100 stamina | 4 + 2 (`fighter.h:304`) | `blocked[i]` stays provisional (§5 item 5); guard-break/exhaustion and the recovered button predicate are not covered |
| 10 | Hit | **covered** | `rena0-hit-ground-300.fixture`: with the dummy on the attacker's posed volume (the `place_at_attack active` pattern the device-free melee tests use) the swing is active over updates 14-19, the contact lands at 15 and removes the recovered **8 HP** (100 → 92) | 4 + 2 (`FUN_00639160`, `tests/damage_scale_test.cpp:195`) | the applied **hitstun length** is still not exposed (§5 item 3), so a Hit case pins damage but not stun; the earlier spawn-distance blocker is resolved by placement, not by weakening the test |
| 11 | KO | **covered** | `rena0-ko-ground-300.fixture`: one recovered 8 HP hit on a dummy launched at 8 HP — contact at 15, the economy registers the KO at 16, the victim is left at **1 HP** and stays `is_alive()` while `pending_ko` reads 0, and no respawn happens on the contact update; `rena0-round-timeout.fixture` covers the round ending through `RoundEnd::Timeout` (enum 2) | 4 + 2 | the KO clock is still a labelled port rule (`match_economy.h:105`); `koCredits`/`overkillHits`/`pending_ko` are **declared unsupported** in §2b with their measured reasons, so no case claims them |

Cross-case: cadence and RNG policy are pinned (§1, §3; F1-9 asserts the number), and
no case carries original-runtime parity. Required coverage therefore stands at
**11 of 11 target cases covered / 0 partial / 0 uncovered-because-untested**, plus a
twelfth case row for the timed-round path — with the open questions above recorded as
findings and the unsupported fields declared rather than claimed — partial cases are the next
fixtures to write, and the gaps above are the reason a case can be partial rather
than quietly accepted.


## 11. Sampling model and verification (owner-priority)

What is sampled, and what is deliberately not:

| Aspect | Rule |
|---|---|
| Tick domain | the fixture runner calls `Match::step` **once per tick index**; the live host instead drives `FixedStep` with bounded catch-up (≤ 8 ticks per render), so a comparison is made in the fixed-step domain, never the render domain |
| Sampled instant | end-of-tick values (after the step), so an expectation at tick *t* sees exactly *t+1* steps since tick 0 |
| Sampling rate | `FixedStep::tickRate` = 60 Hz, recorded per run and asserted by F1-9 |
| Not sampled | sub-tick values, interpolated presentation transforms (`alpha`), wall-clock time, render frames, and any original-side state — sampled original reads are a different evidence class and are not part of this contract |
| Identity | the runner counts its own updates and fails if the count differs from `maxTick + 1`; the count is printed (`sampled=N updates`) so a log shows the domain it covered |
| Missing case | an absent data install exits 77 (Skipped, never a pass); an empty fixture set fails |

Recorded sampling checks (2026-10-16, `/tmp` copies, tracked fixtures untouched):

| Check | Observed |
|---|---|
| Tick anchor shifted one earlier (`expect 3 state 10`) | `tick 3 state exp 10 got 0` — expectations are anchored to the tick they name |
| Wrong per-tick value on a walk tick (`expect 13 step 0`) | `tick 13 step exp 0.000000 got 7.200002` — the walk tick's own value, and the float is why the fixture tolerance is 1e-3 |
| Two contradictory expectations on one tick | both evaluated; `tick 4 state exp 0 got 10` |
| Sampled count | `rena0-idle-walk-turn-stop` reports `sampled=32 updates` for ticks 0..31 |
| 13-fixture set, 3 runs | byte-identical output, exit 0 (`PASS (13 fixtures, 60 Hz, skips=0)`) |
| 19-fixture set, 3 runs | byte-identical output, exit 0 (`PASS (19 fixtures, 60 Hz, skips=0)`) |
| 20-fixture set (v2), 3 runs | byte-identical output, exit 0 (`PASS (20 fixtures, 60 Hz, 21 case rows, 39 acceptance fields, 7 unsupported declared, 0 unreferenced extras, skips=0)`) |
| Required fixture deleted | `required fixture 'rena0-ko-ground-300.fixture' is missing`, exit 1 |
| `field shots` line deleted from the manifest | `no longer declares the acceptance field 'shots'`, exit 1 |
| `case ko` line deleted from the manifest | `no longer declares the required target case 'ko'`, exit 1 |
| Assertion removed from a fixture | `'rena0-tap-shot.fixture' does not assert field 'shots'`, exit 1 |
| Unreferenced extra fixture added | exit 0, reported as an extra (extras cannot shrink coverage) |

The count assertion guards against a future refactor that steps the loop differently; it
is not a present-risk check. Honest limit: the fixtures sample the port's fixed-step
domain only, so they can never establish anything about the original's update timing —
that remains "not verified" for every case.

---

# Appendix A — F1-5 probe record (unchanged)

## Execution and scope

The device-free `rena0_locomotion_observation_test` links the production
`foundation_gameplay` library. It loads Rena weapon slot 0 (`data/rena/00.dat`),
item 001 and the move table's named original rig through the production asset
loader. Both fighters are equipped Rena+0; the opponent is fed no input at all
(`nullptr`), the product's COM-off shape, rather than all-false input. The test
keeps the repository's data-free CI invariant: with no reachable install it exits
77 and `SKIP_RETURN_CODE 77` makes CTest report it Skipped, which is **never** an
F1-5 pass — the recorded F1-5 result below is from a run with the real install
present. An install that is present but whose combo data is unreadable still
fails hard (verified: exit 1 with an empty `daybreak00.dat`), so missing or
mismatched data cannot hide behind the skip.

Each case resets a Match, supplies distinct animation controllers, and steps
BattleStart to actionable grounded Idle normally. The cadence is
`FixedStep::seconds` / `FixedStep::tickRate`: **60 Hz**, 0.0166667 s, applied by
P0-10. The probe was run at both the old 64 Hz and the shipped 60 Hz and passes
unchanged: `startup` stays 60 updates because it is a tick count, and the walk
step/turn assertions are cadence-independent. Inputs and their previous
states are explicit; edges use `compute_edges` once per update.

Open-field only: no stage mesh or movement-collision provider is attached.
Standalone scripted/`--out` collision defaults are unchanged. No window, audio
device, renderer or original executable is launched. No RNG-dependent action
is requested; Match resets its existing deterministic stream each case.

## Observation mappings and limitations

The attributed compact reconstruction under `src/gameplay/native/` proposes
outputs from a pre-update snapshot. Nothing is applied to Fighter, Match or its
animation controller. The normal path alone owns phase, elapsed time and binding.

| Input | Mapping / limitation |
|---|---|
| State | Fighter numeric action state, restricted to 0/10. `action_state()` collapses Guard/Hit/KO/BattleStart/Shoot onto the same 0 as Idle, so stop ticks additionally pin the `FighterState` enum |
| Grounded | Inverse of Fighter airborne flag |
| x/z | Digital Right−Left / Down−Up; no analog case covered |
| phase/frame | Legacy move phase / phase elapsed; diagnostic clock correspondence only |
| secondary | Legacy move counter; correspondence to original +AE08 unresolved |
| duration/hold | Bound rig set period rounded using original 0.016 s animation unit; move table phase gate; not a fixed-step cadence assertion |
| stop | Explicit no-stop fixture assumption after normal startup, not proof of original +A0 mapping; stopped-body fixture separately checks a nonzero word |
| slow | Explicit normal-refill fixture assumption; original slow-resource timer mapping unresolved |
| gauge | Stamina ×10 diagnostic proxy for 0..1000 resource; original refill semantics are not proved by saturated stamina |
| speed | Previous observed displacement magnitude in units/update; legacy move-speed attack channel is not walk displacement |
| vertical | Grounded displacement Y, only zero in the exercised grounded scope |
| gravity/movement/offset/turn/direction | Explicit observer-only fixture seeds/carry, not hidden product fields; original +60/+64/+874/+878 correspondence unresolved |

Observer angles are degrees, legacy body yaw is radians and target-relative.
The observer retains its proposed angle/turn/direction between observations;
this does not make it an authoritative simulation or a product angle mapping.
Resource, stop, angle and paired-clock uncertainties block using these outputs
authoritatively, but do not prevent observing the explicit conditions.
`TODO(question 16)` in [QUESTIONS.md](QUESTIONS.md) records the next bounded mapping decision.

Observed discrepancies: at update 4, the Idle→Walk proposal clears speed and
resets clocks to 0; legacy moves 7.2 units and reports elapsed frame 1. At update
28, the Walk→Idle proposal retains incoming speed and resets clocks; legacy stops
translation and reports frame 1. The diagnostic move-counter proxy stays 0 while
the proposed secondary clock increments to 1. Observer offset and legacy body yaw
have different sign/basis and update domains and are not compared as equivalent.

## Expected results and evidence

Reconstruction provenance: DaybreakRebuild-20261010 by Ginkiha,
`roster_locomotion_native_control.hpp`, `battle_roster_walk.hpp`,
`battle_walk_motion.hpp` and `battle_steering.hpp`. The selected Rena+0 state
slot-6 update handler is FUN_0043ffc0 (bundle dispatch metadata); FUN_00445ee0 is the input selector, not that update body. Steering helpers cite FUN_00421780 / FUN_0042db10.
This is attributed reconstructed code, not the complete generated combat body
and not freshly verified compiled-binary evidence. Existing addressed research
[FUN_0043ffc0:84–179](../research/decompiled/FUN_0043ffc0.c#L84-L179)
independently supports state admission, the 0x40e66666 speed constant, direction
category at actor +0xe8, turn reset 20/decrement/floor 1 and refill 40/5. The
[common tail](../research/decompiled/FUN_0043ffc0.c#L2439-L2447) supports paired
clock increments and strict phase completion; the transition/completion reset of
those clocks and of the phase is `FUN_00421080` → `FUN_00421100`, cited for the
proposal's reset semantics rather than taken from bundle convention. This reuses
addressed research; no new REA query or original execution was needed.

Required sequence: idle (4 updates), Right walk (12), Up turn (12), release/stop
(4). Repeat on reset, then repeat with observation disabled. Assertions require
0→10 on held direction, 10→0 on release, grounded equipped actors, real row
0/10 clip binding without fallback, no movement during idle/stop, movement while
walking/turning, the exact 7.2 units/update production step at any cadence, the
+19°/−19° production turn on the walk entry and the reversal, an unchanged neutral
dummy position **and yaw from the reset onward**, and identical per-update
production snapshots with/without observation. Observer tail increments and
transition clock reset, Rena speed 7.2 units/update, turn-step reset 20 then decay
with the −19°/−71° steering offsets, no-proposal and stop-word suppression are
pinned explicitly. The in-match resource channel is saturated at 1000 by design,
so the refill arithmetic is pinned by explicit cases instead of that value:
100/clear → 140, 100/slow → 105, 995/clear → 1000. Strict phase completion
(`duration < frame && !hold` → phase+1 with both clocks reset), the gated `hold`
counter-case, and losing-ground → airborne + gravity 0.5 are explicit cases too,
because no production update in this sequence crosses a phase boundary.
Legacy numeric agreement is diagnostic, **not an original-behaviour oracle**.

Exact equality applies to repeated snapshots in this same build/process;
source numeric comparisons use 1e-4 tolerance. A deliberate wrong walk speed
must fail the same source expectation predicate. A separately invoked seeded
failure mode must exit nonzero. A skipped (no-install) run and any required
failed case are not a passing F1-5 result.

Artifact revisions for the recorded F1-5 run (sha256):
`rena0_locomotion_observation.h` `20434618eff87f3d7fe687ae52c3e83e9e68d08837d09a34b57995d73c92c399`;
`rena0_locomotion_observation_test.cpp` `e429d43304c5ce19cc1ff3c1003ddec739402dc7ba80b00be9e7ad5bd047b486`;
`remake/foundation/CMakeLists.txt` `a898a3d9500c3ca3727497df5696ea220f340e3dde6334ce2473bbb1731928d7`;
this file `237e7c77f25e8ad3e629cadeeefe8ed3fbcc5805685281e35babe59aca0f2fd2`.
The independent review below is hash-pinned to the previous revisions
(header `20434618…`, test `d1375351…`, CMake `d66d9ded…`, contract `1cfc46f6…`);
the only later changes added the explicit refill/phase/airborne cases, the
`SKIP_RETURN_CODE 77` path and comment/doc wording, which is what the recorded run
executed.

Evidence tiers: install-backed product checks (tier 4), addressed reconstruction
expectations (tier 2 attribution, not new binary verification), and provisional
mapping assumptions (tier 6) are distinct. Shared-source agreement proves
consistency only. No tier-1 original runtime parity, renderer appearance,
collision behaviour, attack/jump/dash/guard/KO coverage, full combat seam
feasibility, contract approval or pilot verdict is established.

## Commands

```bash
cmake --build remake/foundation/build/linux --target rena0_locomotion_observation_test -j 4
ctest --test-dir remake/foundation/build/linux --output-on-failure -R '^rena0_locomotion_observation'
./remake/foundation/build/linux/rena0_locomotion_observation_test
./remake/foundation/build/linux/rena0_locomotion_observation_test --seed-wrong-speed
```

The last command is expected to fail, not a passing production case. These
commands are silent by construction (no audio backend); CTest also uses the
repository's quiet test environment. Results and remaining questions are recorded
in [DIRECTION-STATUS.md](DIRECTION-STATUS.md) and [QUESTIONS.md](QUESTIONS.md).


---

# v3 — APPROVED 2026-10-22 by the repo owner

> **2026-10-22 re-audit, then owner-approved correction (Q19).** The re-audit found the original
> `shot-gauge-spend` expectation contradicted by the Rena+0 source: its cited `FUN_00508a60`
> subtraction is a directional air-dash cancel out of state 402 into state 30, in another
> combo's selector, and Rena's own executor emits the powered shot without spending the gauge.
> The owner approved replacing that case rather than keeping a mislabelled port rule. The
> `shot-gauge` case below is the replacement, and the production deduction was **removed**.
> Denominate change: 23 → 24 fixtures, 24 → 25 case rows, 40 → 44 fields; the removed case's
> coverage obligation is carried by two source-backed fixtures, so nothing was dropped. See
> V3-7 for the correction record.

**Status: APPROVED 2026-10-22, for the stated Rena+0 scope.** Reviewed content: the v3 section as
it stood at approval, `sha256 12bd62ec73543fc62d440c0981acb43a4063c0820e3fd5840d69e8915def376d`;
erratum **V3-6** below is the only later edit and changes no acceptance field, tolerance or
exclusion. Everything above this line is the approved **v2**
(`sha256 c5df99313725d80ee1ba9ae8d7161d4ca252512349ac65e962f37730565a18c6` for the reviewed
content), which v3 supersedes. Acceptance stays **0/46** and the pilot verdict stays with the
owner: approving a contract version is not a verdict. No cleanup may start while the verdict is
pending.

## V3-1. Scope additions (new acceptance cases)

The owner approved three promotions on 2026-10-16 (gaps 1-3 of the pending verdict):

| New case | Fixture(s) | What it asserts | Tier |
|---|---|---|---|
| guard gate | `rena0-guard-gate-pilot.fixture` | a guarded melee contact applies **no damage and no stun** under the recovered predicate — 100 HP, no KO | 2 + 4 |
| guard gate, legacy pin | `rena0-guard-gate-legacy.fixture` | the same contact without the flag still shows the legacy 20%-floored rule (99 HP) — the flag-off restoration pin | 4 |
| shot gauge, powered launch (**replaced 2026-10-22, Q19**) | `rena0-powered-shot.fixture` | the powered air tap (action 402) fires **bullet row 7** — `FUN_0043ffc0.c:2009-2014` selects it from the held-aim pair — and performs **no** shot-gauge subtraction: `charge_gauge` stays at its 1000 cap on the launch tick and through the action | 2 + 4 |
| shot gauge, recovery (**replaced 2026-10-22, Q19**) | `rena0-shot-recovery.fixture` | the recovered row-403 recovery adds **40/tick** and clamps at 1000 (`FUN_0043ffc0.c:2021-2040`), observed from a below-cap start (a harness affordance, since the product has no spend path): 900 → 940 → 980 → 1000, then held | 2 + 4 |

Consequently `charge_gauge` moves out of §2b's **declared unsupported** list and becomes an
asserted field, with the reason for its former status corrected below. The 2026-10-22 correction
also asserts `shot_bullet_row`, the launched item row that separates the powered launch from the
ordinary one. `koCredits`, `overkillHits`, `pending_ko`, `charge_whole`, `round_over_side` and
`kos` stay unsupported.

## V3-2. Explicit exclusions (re-scoped by the owner, named rather than silent)

| Excluded | Why, with the evidence that bounds it |
|---|---|
| the hit/KO **damage-and-death pipeline** | the owner's choice (1b), now measured rather than assumed. The pipeline is ~250 lines of genuinely portable integer arithmetic over flat scalars (S3-S8-selection: `battle_hit_pipeline.hpp:11-28` → `battle_damage_pipeline.hpp:8-35` → `battle_hit_resolution.hpp:27-40`, zero actor lookups, zero virtual calls), but it is fed by two things the port does not have in that form: a **named-bone world matrix per DAT frame** plus the victim's `Bip01_Head`/`Bip01_Spine` spheres at radius 30 (`development_animated_combat.hpp:1465-1470,3894`), and a **DAT phase/duration/hold table** for every reaction row the attacker's fields `0x64`/`0x68` can name (`development_animated_combat.hpp:1333-1342` throws without it). Its damage chain reads the live `+0x7c8`/`+0x7cc` combat modifiers, whose neutral values (100 attack × 100 defense) the port hard-codes, and the melee power the accepted fixture exercises is the shipped **1500** (`states[81].phases[2].frames[1]`, state 300's only nonzero damage frame — every other frame of that row, and all of state 400, carry zero damage). Excluded by name, with the fixtures as its evidence and the port's chain labelled an approximation. **One concrete lead is recorded rather than resolved:** the port's melee chain applies the attacker modifier (`power×attack/100×defense/100×100/scene`), while the addressed dump cited at its own head for the *melee* path shows `power×defense/100×100/scene` with no attack term — a structural difference that the neutral-100 value makes numerically invisible here. Confirming it needs the addressed function re-read, not a guess |
| shot **spawn positions** | the owner's choice (2c), now measured rather than assumed. No recovered body computes the point: the generated layer has no projectile event at all (the `slot7` host handles only `A/N/P/R/T/v/V/Y/Z`), and the request structs carry no position — `RenaShotEvent::position` is left default and only the pitch is set. The point is composed by the host at one site, `append_actor_projectile_request` (`development_animated_combat.hpp:958`): `point` (zero for state 400/402, because those states clear the held model at the firing frame; the item's `attachments[0].socket_offset` otherwise) transformed by the **`Bip01_Prop1`** bone matrix, with heading `actor.heading + offset + yaw` and a clamped pitch. So the coordinate is reproducible offline in principle — `data/item/001.dat` contributes only a 3-int socket offset and `data/bullet/001/*.dat` contributes nothing positional — but it is **not what this port does today**: it spawns at a fixed `(forward 60, up 100)` offset (`fighter.h:279-280`). The fields stand as **excluded and unasserted**, and the port's fixed offset is named an approximation, not an equivalent. Closing it would be a rig-anchored spawn change of its own with new cases, and it would have to ride the pilot flag because it changes behaviour |
| the **+1/tick gauge refill** | the enclosing condition is now identified, not assumed: the adapted body's head refills `+0x834` by 1 (capped 1000) exactly when the mode-2 special is active — `slot7_native_bodies_20260929.hpp:52-64`, with `byte(0x846)` = `active2` (`slot7_native_world.inc.hpp:98,116`) and the same mode-2 spend/limit rules the pilot already pins (`battle_special_gauges.hpp:38-44`). It is a bounded unit with its own reachability, so it stays a named exclusion for v3 rather than being implemented now |
| the **+1/tick gauge refill** | identified (`FUN_0041f580:97-98`, `FUN_00508a60:58-59`) but its enclosing condition is not established, so it is deliberately not implemented rather than approximated |
| the guard's **animation granularity** | the port binds no clip or phase for `Guard` (`state_move_id()` returns `-1`, with its own note); the pilot supplies the recovered row's guard-capable record so the predicate can read the flags, and the phases/hold-counter granularity stays a named limit |
| the charge **move bodies** (states 350-362) | generated decompiler output whose own header warns that generation is not parity proof; Rena+0's slice is a 40-line host-call wrapper with no decision content to drive, so the port's data-driven charge rows and `rena0-charge-hold.fixture` remain its evidence |

## V3-3. Provenance corrections

* **The guard predicate's words are data, not inputs.** `FUN_00637950`'s guarded `else`
  (listing lines 185-192) reads `[[victim+0x10]+0x28]` for `0x400`/`0x2000`/`0x8000` and
  `[[attacker+0x10]+0x2c]` for bit 8. The bundle's pipeline names them —
  `battle_hit_pipeline.hpp:23` (`input.stagger.flags`, `input.attack_flags`),
  `actor_frame_hit.hpp:8` (the attacker's record word `flags2c`),
  `development_animated_combat.hpp:3922` (`live_body_contact_frame(v).flags28`) — and the port
  already parses both as `MoveEntry::stateFlags`/`attackFlags`, reachable through
  `current_move_record()`. The shipped data confirms the meaning rather than merely permitting
  it: of Rena+0's 276 records, the first carrying `0x400` is **row 390** (the standing guard
  whose body the pilot adapted) and the first carrying bit 8 is **row 350** (an attack row);
  `0x2000` and `0x8000` occur **zero** times in her 276 records. The earlier claim that two of
  the terms were "not expressible from port data" is therefore withdrawn: all four are
  expressible, the predicate is now a pure function of them (`decide_rena0_guard`) and is pinned
  offline for every combination, and the two zero-count terms are **unreachable with this combo's
  shipped records** rather than unimplemented — a data fact, verified by the same test rather than
  asserted. The port's `Guard` state proxy is gone. One limit stays named: the bundle's
  `0x8000` (contact-word OR) term is not read by this predicate, and this combo has no record that
  would exercise it.
* **`charge_gauge`'s former reason was wrong in one direction and silent in another.** Its
  refill *is* implemented (`MoveOp::Recharge`, +40 or +5 with hit-status slot 6, capped at 1000,
  on rows 403/409/469); what the port lacked was a **spend**, now implemented behind the flag
  (action 402, −500, requiring more than 499). The field is observable and asserted by the new
  fixture.

## V3-4. Evidence the revision rests on

| Area | Evidence |
|---|---|
| charge bodies | `rena0_charge_body_test` (29 checks: the mode and blocked gates, divisors 90/133/225, defense and modifier factors, clamps, notification ids 6 and 5, the preserved `INT_MIN / -1` fault) |
| special-gauge control | `rena0_mode_gauge_test` (44 install-backed checks: the shipped limits 850/850 with durations 900/900, accumulation, mode exclusivity, the chords, `refill_step`, and the consumption tick including mode 2's health drain) |
| live gauge accumulation | differential `attacker-hits=4 charge1=220` — 55 per hit from the record's column 50 through `50*100/90` |
| guard flags | `rena0_guard_flags_test` (12 checks: 276 records; `0x400` in 6, first row 390; bit 8 in 8, first row 350; `0x2000`/`0x8000` in none) |
| guard predicate | the decision is now a pure function (`decide_rena0_guard`) pinned offline for all four terms: any-angle guards from behind, the 45-degree bound inclusive inside, bit 8 defeats it, a row without `0x400` cannot guard. Live: `asked=3 guarded=2 no-record=0 not-guard-capable=1`, P1 at 92 HP; fixtures `asked=1 guarded=1 no-record=0` (100 HP) and legacy 99 HP |
| shot model mapping | the body's `model(-1, slot)` clear is the port's per-slot held item model, whose consumer already implements it (`itemModel < 0` resets the trail); the writer's guard was relaxed (behaviour-neutral: no shipped row carries a negative model) and the pilot drives the clear, taking the comparison from **0/148 to 144/148** — the residual four being a one-tick lead of the body's clear over the port's fire |
| dash admission gate | `rena0_pilot_gate_test`: gauge 0 refuses the dash on the pilot path (`dash_move_id() == -1`) while the funded gauge still enters row 20/set 13; offline fixture `rena0_slot7_gate_probe` passes and **fails under a deliberately wrong gate** |
| empty-magazine tap | the same test: voice 24 published with no shot row, no spawn and an unchanged magazine; still silent with the flag off. The statistic `+0xaf4c` stays unowned and undeclared |
| flag-off restoration | locomotion, melee and shot byte-identical in capture **and** deterministic stdout; the guard scenario differs **only** in the HP fields (90 → 92); the dash and empty-tap controls are asserted **inside** `rena0_pilot_gate_test` rather than in a separate run |
| suite | **83 tests, 0 failures, 0 skips**; fixture-linked differential 357 in-domain ticks, no unexplained divergence; scripted locomotion/melee/shot 200/200, 33/33, 99/99 with 0 disagreements |
| the proposed matrix itself | the approved fixtures run against a scratch copy of the **v3 manifest** (`local-data/harness/MANIFEST-v3-proposed.txt`): `PASS (23 fixtures, 60 Hz, 24 case rows, 40 acceptance fields, 6 unsupported declared, 0 unreferenced extras, skips=0)`, byte-identical over 3 runs. The tracked v2 manifest still reports `21 case rows, 39 fields, 7 unsupported, 3 extras`, so the approved denominator has not moved |

## V3-5. What approval would change, and how to run it

On approval: the acceptance denominator gains the three new cases, `charge_gauge` becomes an
asserted field, the exclusions above become contract text rather than findings, and the 2f report
is repeated against v3 before the verdict returns to the owner. Nothing here changes the
reported **0/46** until then, and no cleanup may start while the verdict is pending.

The revision is **already executable** without touching the approved file: the runner reads the
manifest from the directory it is given, so a scratch directory holding the fixture links and
`MANIFEST-v3-proposed.txt` runs the proposed set. The measured result of that run is in V3-4
(`24 case rows, 40 acceptance fields, 6 unsupported declared, 0 unreferenced extras`), against
the approved v2 manifest's `21 case rows, 39 acceptance fields, 7 unsupported, 3 extras`.

> **Erratum 2026-10-22.** This paragraph describes the pre-approval procedure and is no longer
> how the runner works: it now requires the file to be named exactly `MANIFEST.txt`, because the
> free `.txt` fallback let a decoy file rescue a missing manifest (V3-7). The approval this
> section anticipated happened on the same date, and V3-1's `shot-gauge-spend` row was replaced
> by the owner-approved correction; the current set is 24 fixtures / 25 case rows / 44 fields.

**What approving this does not do.** It does not change the scoreboard (still `0/46`), does not
lift freeze list A, does not start 2h, and does not assert original-runtime parity. It fixes the
acceptance set the pilot is judged against; the verdict stays the owner's.


## V3-6. Erratum after approval (2026-10-22): the dash resource is stamina

Approved with the owner's observation that **in the original game nothing but the stamina meter
interacts with a dash**. Checked against the recovered code and this port, that observation is
right and one sentence of V3-2's history (and of the pilot's first dash fix) was wrong.

* **The recovered `+0x834` dash gate *is* the stamina meter.** The adapted dash bodies require
  `0 < +0x834` and drain it 12/tick (`slot7_native_bodies_20260929.hpp:66-74`,
  `dash_native_bodies_20260929.hpp:53`). This port already applies exactly that rule to
  `m_stamina`, at 1/10 scale: the recovered 12/tick is `LocomotionDefinition::dashDrain` **1.20**
  for Rena+0, and the body's phase-1 exit at `+0x834 < 1` is the port's `m_stamina <= 0`
  (`fighter.cpp:1872,1883`). The programmed forward dash already refuses at `m_stamina <= 0`
  (`fighter.cpp:2951`).
* **The earlier "gauge-0 dash discrepancy" was an injected-state artefact,** not a behaviour
  difference. It was measured by forcing `Fighter::set_charge_gauge(0)` while stamina stayed at
  100 — a state the original cannot be in, because the two port counters are one original
  resource. The pilot's `PilotCharge::dash_gauge_refuses` gate added in the first pass has been
  **removed**: it read a counter that does not drain during a dash, so it could only disagree
  with the resource the port actually uses. The empty-magazine tap voice from the same pass is
  unaffected and stays (the owner confirms Rena says she has to wait — voice id 24).
* **No acceptance change.** No field, tolerance or case in V3-1 is touched; the dash gate was a
  2e comparison, not a v3 case. What changes is the *meaning* recorded for `+0x834`, and the
  removal of a redundant pilot-only gate.
* **Recorded, not fixed:** the port still carries two counters for that one resource
  (`m_stamina` 0..100 and `m_chargeGauge` 0..1000). Its regen rates differ (1/tick versus the
  recovered +40/tick at 1/10 = 4/tick), so in natural play the charge counter tends to sit at
  1000 while stamina is the live one. Unifying them is a change to the frozen decision path and
  belongs to the post-verdict cleanup, not to this pilot.

## V3-7. Readiness re-audit (2026-10-22): approval is not a passing verdict

**Corrections to the readiness claim, not an unapproved change to acceptance scope:**

- Exact case/fixture pairs are now independently required by the runner. Before this fix,
  deleting the legacy guard fixture plus its manifest row passed at 22 fixtures, replacing the
  pilot guard case with guard-hold also passed, and `DECOY.txt` rescued a missing `MANIFEST.txt`.
  All three are now rejected, along with missing right-dash and promoted-field rows, by an
  automated mutation regression. Field-to-fixture identities are independently required too:
  redirecting `dummy_hp` to the guard case cannot remove its required assertion from the hit
  fixture. The seven mutations cover both binding directions. Scratch runs must also name
  their file `MANIFEST.txt`; the historical V3-5 description of accepting an arbitrary `.txt`
  was unsafe and no longer applies.
- The existing no-stun promise is now checked at the contact update: when the recovered guard
  predicate accepts a hit, the victim must retain Guard; a pilot guard fixture must exercise
  at least one such contact. The previous HP/KO assertions alone did not establish no stun.
- Pilot attachment now requires the actual loaded Rena actor, slot-0 item identity 001 and
  valid item data; policies are detached outside that domain. Previously the flag alone could
  attach them to any P1. This is a freeze/safety fix, not another-combo implementation.
- **Q19 — resolved 2026-10-22.** The re-audit showed the required `shot-gauge-spend`
  expectation was contradicted source provenance: Rena+0's executor
  (`FUN_0043ffc0.c:1968-2020`) and the recovered helper
  (`battle_rena_mobile_shooting.hpp:216-221`) select bullet 1/7 at frame 13 without `−500`,
  while the cited `FUN_00508a60.c:76-114` subtracts 500 during a directional dash cancel
  from state 402 into state **30**, and its matching statements live in another combo's
  selector (`slot7_body_5_1`, generated lines 6466-6501). A scratch run with source-corrected
  `1000` expectations failed at tick 25 (`expected 1000, got 500`), which is what triggered
  the report. The owner approved the correction; `PilotCharge` and its deduction were
  **deleted**, and the case was replaced by the two source-backed fixtures in V3-1
  (`rena0-powered-shot.fixture`, `rena0-shot-recovery.fixture`). Coverage was not reduced:
  the removed case's obligation is carried by both replacements plus a new asserted field
  (`shot_bullet_row`), and the denominator moved 24 → 25 case rows and 40 → 44 fields.
- V3-6's scale arithmetic is not proof that both resource channels are integrated. The
  bundle directly sends `combat_->gauge[actor]` to `hud.stamina` (`runtime_battle.hpp:2221`),
  while our two counters remain independently updated. The diagnostic dash test compares
  port constants/flag settings, not depletion, refill or cross-action source equivalence.

**Empty-ammo release window (added in the same correction).** The recovered empty-tap branch
tests the held-frame count (`0 < released < 20`, `slot7_native_bodies_20260929.hpp:172-182`),
which the port could not express because a bound weapon pins its hold-seconds field to one tick.
A held-frame counter now feeds that test, and the pilot regression pins both sides of the
boundary: 19 frames still voice, 20 frames are silent, and both stay out of any shot row.
Seeding the cap to 21 makes the 20-frame assertion fail, so the check is load-bearing.

The owner-approved v3 remains recorded, with Q19's correction applied. A source-backed green
recommendation still needs an honest decision about the split-resource limitation; it is not
merely waiting for a rubber-stamp 2g verdict. No original-runtime parity follows from any of
these tests.

## V3-8. Meter unification amendment (2026-10-23): one source-shaped word behind the pilot flag

Owner approved Option A (Q21, 2026-10-23). The split `m_stamina`/`m_chargeGauge` pair is
replaced, on the pilot path only, by one 0..1000 `m_actionMeter` carrying the recovered
integer rates. The default (flag-off) path is byte-for-byte the old behaviour.

**What the pilot path now does** (`fighter.cpp`, all sites cite their source):
- dash: gate `meter <= 0` refuses for every dash arm (no flat trigger spend); per-tick
  drain −12 for states 20/23/24/27/28 **while the phase is below 2** (the recovery phase
  spends nothing — see V3-25), −11 for air state 30 on every update of its three-section
  row;
- guard: −10/tick while Guard, exit + exhausted at 0;
- recovery rows: +40, or +5 with hit-status slot 6, clamped at 1000;
- mode-2 special active: +1/tick (gated on port Kakera == wire value 2 — mapping named);
- no passive refill (none exists in `FUN_0041f580` outside the mode-2 flag);
- melee/shot admission read the meter, so the recovered "no attack with an empty meter"
  gate can fire for the first time;
- jump leap spends the modal −100; fly drain keeps its port rate, routed to the meter.

**Re-pinned expectations — denominator unchanged** (24 fixtures / 25 case rows / 44 asserted
fields / 6 unsupported / 0 extras): `rena0-guard-hold.fixture` now expects `stamina 40`
(not 75) at tick 59 and `guard_exhausted 1` at tick **99** (not 245) — the recovered rate
exhausts in ~100 ticks, and the run confirms it exactly. The shot fixtures now observe the
scripted jump's own costs (−100 leap, one −5 hold-fly tick on the launch tick's physics), so
the 900 start reads 795 and the recovery lands 835/875/915/955/995, clamping at tick 54.
The gate test's Case A asserts admission at full meter on both paths, pilot refusal with
flag-off admission at empty meter, and exactly one −12 drain on the admission tick
(1000 → 988); the seeded wrong-gate now asserts the admitted-at-zero shape and fails.

**Named limits carried forward, not closed:** the state-30 −3 inner arm (the port has no
state-30 frame clock); jump row variants (−4/−6/−12 vs the modal −10 the trigger can see);
guard phase granularity (drain runs every Guard tick); the fly drain stays a port rule with
no citation; the Kakera mapping for the mode-2 refill. The HUD fraction is unchanged in
shape and now exact in value (`meter/1000`).

## V3-8, supplement (2026-10-23): the jump-row correction inside the pilot meter

Manual validation caught what the fixtures could not state: with the meter unified, an
exhausted guard never refilled, and the first implementation had invented a modal −100
leap spend while leaving the recovered jump refills unimplemented. Re-reading every
jump-body writer shows the actual shape, and it is uniform across all 46 combos:

- no jump body charges a launch spend — the row-41 spends (−10 modal; −4/−6/−12 by
  combo) all share the gate `gravity == 0`, i.e. they are the **hover** drain, not a
  per-leap cost. The modal −100 has been deleted from the pilot path (legacy keeps it).
- rows 40 (launch) and 44 (landing) refill +40 (+5 with hit-status slot 6), clamped at
  1000, every tick they are bound. The port binds its launch row for exactly one tick,
  so the pilot applies one +40 on the launch tick (`m_jumpStartup`) and one +40 on the
  Jump→Idle landing transition. **The landing row itself is bound now** (V3-42): row 44
  plays for its own 22 frames, and because it refills at the same +40 the port's Idle
  also adds, the meter timing recorded here does not move — the window is animation-only.
- the port's hold-to-fly is the hover counterpart, so on the pilot path it now drains
  the recovered −10/tick (launch tick excluded — that tick belongs to the row-40
  refill), where the legacy path keeps its 30/s port rule.

Re-pins (denominator unchanged): jump-chain gains a below-cap start pinning 900 → 940
on launch and 940 → 980 on landing; the shot fixtures return to reading the 1000 cap
through the launch (no spend, +40 clamped) with the recovery tail 980 → 1000, clamp at
tick 50. The soft-lock the first revision created — meter 0 with no reachable refill —
is closed the way the source closes it: jumping and landing refill.

## V3-9. The ordinary refill, found in the binary (2026-10-23)

Manual play found the meter never coming back. Two earlier revisions were wrong about why,
and both were corrected by reading the shipped code rather than reasoning about it:

- V3-8 claimed "no passive refill exists". **False.** The Rena+0 executor's **case 0** — the
  standing/idle handler of `FUN_0043ffc0` — adds `0x28` (40) to `+0x834` every tick, or 5
  while hit-status slot 6 is set, clamped at 1000, **before input handling**. That is the
  refill a player sees. Evidence: `rea decompile DaybreakDX.exe 0x0043ffc0`
  (`in_ECX[0x20d] = in_ECX[0x20d] + 0x28` immediately under `case 0:`), binary pinned at
  `27e61475…`. `FUN_0041f580`'s gated `+1` and the row 40/44/403 refills are additional.
- V3-8 supplement then implemented only the row refills, leaving idle dead. **Also
  incomplete.** The standing rule is now implemented.
- One tick runs exactly one executor case, so a tick that leaves standing takes that row's
  rule instead. The port's state changes after the meter section, so the rule reads the
  pre-input state (`stateBeforeInput`) as well; without that, launch and landing ticks
  double-refilled.

Coverage grew again rather than being trimmed: **25 fixtures / 26 case rows / 45 asserted
fields** (6 unsupported, 0 extras), with a new required `idle-refill` case that holds Guard
from below cap, releases, and pins the +40 climb and the 1000 clamp. It is proven
load-bearing — deleting the refill branch fails three fixtures.

## V3-10. One hover per airtime (2026-10-23, owner report)

Owner report: in the original, jumping and floating works **once per airtime**; releasing the
jump button and pressing again does not double-jump or keep floating — the fighter falls or
takes another air action. This is a **global** rule, not a Rena-specific one.

**Evidence (binary, pinned `27e61475…`):** `rea decompile DaybreakDX.exe 0x00445ee0` shows the
jump-row admission (`FUN_00421080(0x28)`) inside a branch requiring the grounded byte
`0x84 != '\0'`; the airborne branch of the same dispatcher offers only dash/attack rows and
never returns to row 40. The air chain (`0x28 -> 0x29 -> 0x2a`, rows 40/41/42) therefore runs
once, driven by its own phase clocks (`0x2b7d` phase, `0x2b81` section elapsed), with the hover
a phase of that chain rather than a re-enterable mode.

**Port defect:** `wantFly` was `input->down[Jump] && state == Jump && m_flyLeft > 0` — a time
budget that resumed on every press, so a released-then-repressed button kept climbing.

**Fix:** one latch, `m_hoverSpent`, armed the moment the button is **not** held while airborne
and cleared only on landing / new airtime. A held button still climbs for the whole budget —
the latch arms on release, not on the first hover tick (an early version armed it on entry and
stopped the continuous climb; caught by the existing flight test).

Coverage: new required `single-hover` case — jump, hold, release, press again, and the fighter
lands on schedule instead of floating on. Proven load-bearing: with the latch removed the
fixture reports `airborne exp 0 got 1` at the landing tick. Matrix **26 fixtures / 27 case
rows / 45 fields / 6 unsupported / 0 extras**.

## V3-11. Jump height is bounded by the meter, not by an altitude cap (2026-10-23)

Owner report: holding jump should climb higher; the only limit should be stamina. Correct, and
the port had two defects behind it.

**Source (pinned `27e61475…`), Rena+0 executor case 0x29 — row 41's climb:**
`vy (+0x15)` **accumulates +0.2/tick, capped at 6.0/tick**, and every climbing tick spends
**10** of the action meter (`+0x20d -= 10`); the sustained-climb gravity term stays 0 until
`0x3a == 0 || 0x3a > 99 || meter < 1`. **There is no altitude ceiling anywhere in the air
chain.** `FUN_00421bd0`, which the port's comment cited as a "flight cap", only writes spawn
X/Z and a fixed `0x447a0000` = 1000.0 respawn Y — the same constant the port already reads as
`kRespawnAirY`. The citation was wrong, and the cap was an invention.

**Defects fixed on the pilot path:**
- `wantFly` overwrote `vy` with the constant `kFlyRise` (12/tick) every tick, so holding the
  button neither accelerated nor outlasted anything. It now accelerates toward 6/tick.
- A hard `kFlyMaxAlt` 420-unit position clamp stopped every jump regardless of the meter. The
  pilot path no longer applies it (the legacy path keeps it until its own gate).

Measured after the fix, holding jump from a full meter: y = 246 (tick 40), 366 (60), **468 (80)**
— i.e. past the old 420 cap — with the meter at 280 at the apex, and the descent beginning as
it empties. That is the reported rule exactly.

Coverage: new required `jump-climb` case pins the height curve and the meter-at-apex, plus a
new `y` observable (the fixture vocabulary only had x/z). Proven load-bearing: restoring the
cap reports `y exp 468 got 402`. Matrix **27 fixtures / 28 case rows / 46 fields / 6
unsupported / 0 extras**. The tap-jump chain re-pinned with it: a released jump now decays
from 12/tick and lands at tick 25 instead of the old 48, which came from pinning vy at 12.

## V3-12. The climb had a time budget, not the meter (2026-10-23)

Owner screenshot: holding jump stopped with roughly a quarter of the STA‌MINA bar still full. The
arithmetic named the culprit exactly: `kFlyTimeSec` 1.2 s = **72 ticks** of climb × 10 meter/tick
= **720 spent**, leaving **28%** — the bar in the image.

**Source:** row 41's climb (case `0x29`) has no duration and no altitude test. It ends only when
the button is released or the meter hits zero (`0x20d < 1`); the accumulated counter `0x3a` feeds
the gravity restore, not a cap. So the meter is the only limit, as the owner said twice.

**Fix (pilot path):** the 1.2 s budget no longer gates the climb — the meter does
(`m_actionMeter > 0`). The legacy path keeps its budget until its own gate.

Measured after: y = 246 (tick 40), 366 (60), 486 (80), 606 (100) and **peaking at 621** as the
meter reaches 0 at ~tick 100, then falling (436 by tick 140). Correcting this also exposed that
the climb had continued past meter zero (726) with the earlier gate, which the new assertions
catch (`y exp 621 got 726` when the meter gate is removed).

`jump-climb` is now the required case for this mechanic: it pins the height curve, the meter at
the apex and the zero crossing. Matrix unchanged at **27 fixtures / 28 case rows / 46 fields**.

**Unrelated, recorded:** `device_isolation_test` is intermittently red under `ctest -j 4` and
green serially and alone; it exercises synthetic-pad title navigation and does not touch jump
physics. The pre-existing uncommitted one-line edit in `synthetic_pad.h` (a 64→60 Hz comment)
made it deterministic in one probe, so the flakiness looks timing-sensitive rather than caused by
this work. Left untouched, reported rather than silently repaired.

## V3-13. The airborne turn (2026-10-23)

Owner report: jumping and pressing Left/Right should rotate the character like the ground does.
Correct — the port had **no airborne turn at all**: its turn block only ran in the `Walk` state,
so a direction held mid-air moved the body without rotating it.

**Source:** the airborne movement branch (`FUN_00428510` @`0x428d9b`) writes
`[actor+0x874] = 0x40000000` (**2.0 degrees/tick**) and calls `FUN_00421780`, which turns the yaw
toward the input's compass bearing by at most that step (`FUN_0042db10`'s bounded turn). Read
from the disassembly, not the decompiler: `mov DWORD PTR [ecx+0x874],0x40000000` immediately
precedes `call 0x421780`.

**Fix (pilot path):** the airborne branch turns `m_facing` toward the input direction at
2 degrees/tick. Measured: `turn_deg` is −2.0 per tick holding Left and +2.0 holding Right, for as
long as the direction is held. New required `air-turn` case pins both directions; removing the
branch reports `turn_deg exp -2 got 0`. Matrix **28 fixtures / 29 case rows / 47 fields**.

### Camera: the eye geometry is a reconstruction, and its constants are misattributed

Reported alongside: the camera does not behave correctly on the vertical axis when jumping. Two
things were established, and the second changes what "fix the camera" means.

**Measured (headless match, `DAYBREAK_CAMINFO`):** the eye *does* translate vertically with the
fighter — p1.y 200 → 620 moved the eye 410 → 813. Eye and aim rise by the same amount, so the
view angle barely changes: the camera follows by translation and never tilts. That is a
consequence of the formula (`eye = pos + (…, heightOffset, …)`, `aim = pos + (0, 50, 0)`), not a
bug in the follow state.

**The constants do not mean what the port says.** `render/arena_camera.h` declares
`heightOffset = 300` (citing `0x6a1720`) and `distanceOffset = 800` (citing `0x6a4928`). In
`FUN_006507c0` — the function the camera doc cites — those two floats are the **near and far
plane offsets** of the perspective projection, applied to the eye→aim *distance*:

```
6508ae:  fadd DWORD PTR ds:0x6a4928     ; + 800.0  → far
6508bb:  fsub DWORD PTR ds:0x6a1720     ; - 300.0  → near
```

disassembled at the `D3DXMatrixPerspectiveFovLH` call site. So 300 and 800 are depth-plane
clamps, not the eye's height or orbit radius, and the eye geometry has **no recovered basis** to
compare against. Tuning those numbers cannot make the camera faithful; the real battle-camera
function has to be identified first. Recorded as a scoped follow-up rather than guessed at.

## V3-14. Camera scoping: the follow is recovered, and the port never had it (2026-10-23)

Owner-approved scoping pass. Result: the normal match camera's follow math **is** recoverable, the
port has no equivalent of it, and three of the port's "camera" numbers were misattributed.

### What each cited function actually is

| Function | Port believed | Actually |
|---|---|---|
| `FUN_006507c0` | camera update | camera **renderer**: builds `LookAtLH` + `PerspectiveFovLH` and binds shader constants; computes no follow |
| `FUN_0042cb50` | camera collision | **fighter push-apart**: `FUN_006394c0` calls it to separate two fighters closer than 60 units horizontally *and* vertically |
| `0x6a1720` (300.0) | camera height offset | **near-plane** offset (`local_48 - 300` at the `PerspectiveFovLH` site) *and* the camera reset's eye Z (`FUN_006616d0`: eye = (0,0,300)) |
| `0x6a4928` (800.0) | camera distance offset | **far-plane** offset (`local_48 + 800`), same call site |

Disassembled at `0x6508ae` (`fadd ds:0x6a4928`) and `0x6508bb` (`fsub ds:0x6a1720`).

### The recovered follow — `FUN_006333b0`, `mode95 == 0 && mode94 == 0`

`mode94 != 0` is the camera **action animation** path the port already models (`Box01`/`Box02`).
The normal follow, which the port does not have at all, is:

```
delta  = target - cameraPos            (FUN_0042dfd0 over +0x18)
dist   = |delta|                       (3D)
hdist  = sqrt(dx^2 + dz^2)
offset = (dx, dy - 120, dz)            // the -120 vertical bias
scale  = clamp([+0x78] / |offset|, max 1.5)
eye.x  = camX - dx
eye.y  = camY + dist*0.03 + 140 - (dy - 120)
eye.y  = min(eye.y, camY + 200 - (dy - 120))     // vertical clamp
eye.z  = camZ - dz
aim.x  = dx ; aim.z = dz
aim.y  = camY + 20 - dist*0.2
```

**This is why the port's vertical follow is wrong.** The port uses a flat `heightOffset = 300` and
`aim = position + 50`. Because both eye and aim carry the fighter's `y` unchanged, the view
translates with a jump and never tilts. The recovered rule instead makes the eye's height depend on
the follow distance (`140 + 0.03*dist`), keeps the aim just `20 - 0.2*dist` above the camera rig,
and clamps the eye against a `+200` ceiling — so raising the fighter changes the eye→aim *angle*,
which is the tilt the owner expected.

Measured on the port today (`DAYBREAK_CAMINFO`): fighter y 200 → 620 moved the eye 410 → 813,
i.e. exactly one-for-one, no tilt.

### Still unrecovered (named, not guessed)

- the `+0x18` rig update (`FUN_0042dec0`) that turns the deltas above into world positions;
- the `mode95 != 0` alternate follow;
- ~~the value of `[camera+0x78]`~~ — **resolved (V3-15's later entry, confirmed 2026-10-29): a
  float distance of exactly 300.0, one store (`FUN_00632e10` @`0x632e1a`, reached from the
  per-camera constructor and the reset loop) and two reads: the follow scale numerator
  (`FUN_006333b0` @`0x63374b`) and the stage-obstruction ray's range (`FUN_00633930` @`0x6339ef`).
  No other writer exists in the corpus, so the value is statically settled;**
- the projection modes (`FUN_00661740`): `(π/4, 4:3, near 50, far 150000)` and a second
  `(0.1122, 4:3, near 100, far 150000)` selected by the byte at `+0x95`.

Implementing the recovered follow is a real change to shared presentation state with no fixture
gating it yet, so it is **scoped here and not implemented**: it needs the rig chain first, and it
should land behind the pilot flag with its own capture-based check.

## V3-15. The normal camera follow, recovered instruction by instruction (2026-10-23)

Follow-up to V3-14. `FUN_006333b0`'s normal branch (`+0x95 == 0 && +0x94 == 0`) is now fully
recovered: every instruction and every constant below was read from the disassembly of the pinned
binary (`27e61475…`), not inferred from the decompiler's C.

### Field roles on the camera object (`in_ECX`)

| Field | Role |
|---|---|
| `+0x18` | camera rig position (the anchor the view is built around) |
| `+0x48` | eye anchor (the position the eye is derived from) |
| `+0x30/0x34/0x38` | **output** eye |
| `+0x60/0x64/0x68` | **output** aim |
| `+0x78` | camera distance constant (numerator of the final scale) |
| `+0x94` | rig/animation-driven follow select |
| `+0x95` | projection select |

### The computation

`delta = [cam+0x48] − [cam+0x18]` (`FUN_0042dfd0` is `this − param`, confirmed at `0x42dfdd`:
`fld [eax+8]; fsub [ecx+8]`), then:

```
dist = |delta|                                  ; 3D
if (dist < 800.0) {                             ; 0x6a4928
    if (dist < 400.0) {                         ; 0x6a16d4
        delta *= (400.0 / dist) / 2.0;          ; 0x6a19d0 = 2.0
        dist   = 400.0;
    } else {
        delta *= dist / 800.0;
    }
}
D = delta                                       ; aim basis
V = D - (0, 120.0, 0)                           ; 0x6a170c = the vertical bias
scale = clamp([cam+0x78] / |V|, max 1.5)        ; 0x6a24cc = 1.5
V *= scale
eye.x = camPos.x - V.x
eye.y = camPos.y + 140.0 + dist*0.03 - V.y      ; 0x6a2c70 = 140.0, 0x6a4924 = 0.03
eye.y = min(eye.y, camPos.y + 200.0 - V.y)      ; 0x6a16d8 = 200.0
eye.z = camPos.z - V.z
aim   = camPos + D ; aim.y += 20.0 - dist*0.2   ; 0x6a16c4 = 20.0
```

Every constant was decoded from `.rdata`: `0x6a16c4`=20.0, `0x6a16d4`=400.0, `0x6a16d8`=200.0,
`0x6a170c`=120.0, `0x6a19d0`=2.0, `0x6a24cc`=1.5, `0x6a2c70`=140.0, `0x6a4924`=0.03,
`0x6a4928`=800.0.

### Why this fixes the reported symptom

The eye's height is `camY + 140 + 0.03*dist − V.y` while the aim's is `camY + 20 − 0.2*dist`
plus the aim basis. Because `V` carries the `−120` bias and is rescaled by the distance-dependent
`scale`, the eye→aim **angle changes with the rig/target geometry** — so a jump changes the pitch.
The port's `eye = pos + 300`, `aim = pos + 50` moves both by the same `y` and can never tilt.

Note `0x6a4928` (800.0) and `0x6a1720` (300.0) are used **both** as plane offsets in the renderer
and as a distance threshold / reset value here; the port's error was treating them as the eye's
height and orbit radius, which they never are.

### A fourth misattribution: the 45° "orbit"

The port's `kBaselineOrbit = π/4` (cited as `0x6aac70`, "baseline Z-rotation (45°) for camera")
is not an orbit either. In `FUN_006507c0` it appears as
`D3DXMatrixRotationZ(-atan2(dy,dz) - 0.7853982)` inside a chain of
`RotationZ → Scaling(0.8,0.8,1) → Translation(0.7,-0.7,0)` applied to a 2D overlay before two
shader constants are bound. The recovered follow (above) contains **no orbit term at all**: the
eye lies along the rig→target axis, so the camera looks straight down the lock-on bearing.

### Still open

`[cam+0x78]`'s value is **no longer open** — it is 300.0 with a single store site and two reads
(see the corrected line above); the V3-16 entry below implements it. What remains open is the
writers of `+0x18`/`+0x48` in the scene, which are named, not guessed.

## V3-16. Recovered follow implemented behind the pilot flag (2026-10-23)

`render::arenaRecoveredFollow` now implements V3-15's formula verbatim, with the one missing
constant resolved: **`[camera+0x78] = 300.0`**, written once by the camera's default-init
`FUN_00632e10` at `0x632e1a` (`mov DWORD PTR [eax+0x78],0x43960000`). Two independent lookups
found the same store and the same "written once, no setter" property, and the coordinator
re-read the instruction directly.

**Wiring.** `gameplay::ArenaCamera::set_recovered_follow(true)` + `set_follow_anchor(...)`, enabled
from `main.cpp` only when `--native-actions=rena0` and the followed fighter is the Rena+0 pilot
combo. The default framing and every capture pinned to it keep using `render::arenaViewProj`; the
whole suite still passes (**84/84**) because nothing else changed path.

**Verification.** `tests/arena_camera_test.cpp` gained a `recoveredFollowCases()` section
(123 checks, 0 failures) that pins the formula's outputs term by term *and* asserts the behaviour
this was for: holding the anchor fixed while raising the rig by 300 units changes the eye→aim
pitch by more than 0.02 rad. The old flat `height 300 / aim +50` camera cannot do that — which was
the owner's report.

Live trace after the change, holding jump from a full meter (`DAYBREAK_CAMINFO`, pilot flag on):

| fighter y | 200 | 512 | 839 | 200 |
|---|---|---|---|---|
| eye y | 435 | 694 | 1042 | 507 |

### The anchor is settled: it is the lock-on target (tier 2)

The open link in the draft of this entry is now closed. The camera updater picks the anchor right
before the follow (`FUN_006358c0`, `0x635ab6`–`0x635b2c`) from two fighter positions, and
**neither is the local player**:

```
635ab9: cmp DWORD PTR [eax+0x304],0x0     ; actor+0x304 = pending/ally selection
635ac0: jl  0x635af4                      ; < 0 -> primary branch
  ; >= 0 : anchor = allyContainer[0].position   (FUN_00658a10 on actor+0x2f0, then +0x14)
635af4: push 0x0
635af9: mov edx,DWORD PTR [ecx+0x300]     ; actor+0x300 = the lock-on TARGET index
635b09: call 0x658a10                     ; container element at that index
635b10: add eax,0x14                      ; element + 0x14 = its world position
635b27: call 0x632e70                     ; -> camera+0x48 = that position
```

`actor+0x300` is the field this project already documents as the fighter's target selection
(written by `FUN_00421e30`), so the primary branch's anchor is exactly **the locked opponent's
position** — which is what the port feeds it. The port's `locked_target(view.followed)` wiring is
therefore recovered behaviour, not an assumption.

**Rig, likewise proven.** `FUN_00632ed0` stores the raw actor position at `+0x24/+0x28/+0x2c`,
builds the camera's own point into `+0xc/+0x10/+0x14`, and copies that into
**`+0x18/+0x1c/+0x20`** (the tuple the follow reads) when forced — and the updater passes force
(`0x634c2f: push 0x1`). So `+0x18` is the followed fighter's position, as wired.

**The `+0x304 >= 0` ally branch is not a gap (closed 2026-10-29, V3-41):** it takes the anchor
from the same-team container at `actor+0x2f0`, index 0 — and in a two-fighter match on different
teams that container is empty, so the only non-negative writer never fires, `+0x304` stays `-1`
and the branch cannot be reached. The port models the primary branch only, which is the whole of
it for the pilot; with no lock at all it falls back to a point 600 units along the facing, still
a port constant.

## V3-17. The camera anchor is +0x300 (aim), not +0x304 (combat lock) — owner report (2026-10-23)

Owner report after the first live look at V3-16: the camera felt much closer to the original, but
the **initial targeting was wrong** — a manual change-target press was needed before the view
found its opponent.

**Cause: a wrong field in the wiring, not in the formula.** The port keeps two selections apart,
and they start at different values:

| Field | Meaning | Round-reset value |
|---|---|---|
| `+0x300` | aim selection — what the camera and the firing predicate look at | **0** |
| `+0x304` | combat lock / ally selection (`FUN_00421f30`) | **−1** |

Both come from the fighter reset `FUN_0041dcb0` (called for all four fighters at round start):
`in_ECX[0xc0] = 0` and `in_ECX[0xc1] = -1`, i.e. byte offsets `+0x300 = 0` and `+0x304 = -1`.

V3-16 wired the follow anchor to `Match::locked_target()` — the `+0x304` combat lock — which is
`-1` at round start, so the camera fell back to the facing ray until a gesture installed a lock.
The recovered camera branch (V3-16) reads `container[actor+0x300]`, so the anchor must come from
the aim layer: it now uses `Match::aim_target()`, which is the same selection the camera's bearing
already used two lines above, and resolves to the living hostile through the recovered fallback
pick even before any gesture.

**Reconciliation, labelled:** the raw `+0x300` is `0` for *every* fighter at reset, which for
player 0 is its own index and would degenerate the follow (`dist → 0`). The port therefore reads
it through `aim_target()`, which prefers a targetable selection and otherwise the recovered
fallback pick, rather than taking the stored integer literally. That is a port reconciliation of a
field whose index space is not established here, not recovered behaviour.

Verified: with no input at all, the eye now sits on the p1→p2 axis from the opening frames
(`cam eye=(-166,407,-2200)` against `p1=(-463,200,-2200)`, `p2=(-1363,200,-2200)`) instead of
behind the player on the facing ray. Serial suite **84/84**; pilot matrix unchanged.

## V3-18. Melee does not spend or require the meter — owner report (2026-10-23)

Owner report: normal attacks were refused when the meter was empty, which does not happen in the
original. The owner's description of the meter's scope — **blocking, dashes, jump and air dash** —
matches the binary.

**The port's gate was an over-read.** `admit_attack_move` refused every press at
`meter <= 0`, citing "every recovered arm gates on `0 < +0x834` (lines 63/69/76/86/96/104) and the
ordinary arm's no-attack path also tests `+0x834 < 1` (line 172)". Read line by line in
`FUN_00445ee0`, that does not hold:

- every explicit `0 < +0x834` test guards a **dash or jump** arm — its lines 59/65/72/82/92/100
  bind moves `0x14`/`0x1e`/`0x28` and the `+0x830` dash selector, and 441/449 are the jump arms;
- the single `+0x834 < 1` (line 168) is one term of a **disjunction** that routes the press into
  the SHOT path:
  `if (++0x280 == 0 || +0x284 == 0 || (+0x834 < 1 || ...)) { <shot handling> }`.
  An empty meter selects the shot branch; it never refuses the melee admission, which continues
  after that block.

**Fix:** the gauge condition is removed from `admit_attack_move`. The dash gate in `try_dash`
(`meter <= 0`) and the jump/hover gates are unchanged — they are the recovered ones. `fire_shot`
gates on ammunition, not on this meter, and was untouched.

**Coverage.** `tests/melee_admission_test.cpp` case (9) is the load-bearing guard: it sets the
gauge to 0 with no refill in play, and it failed on the old expectation before the correction and
now asserts that the press is admitted, enters `AttackA` and spends no gauge. New fixture
`rena0-attack-empty-meter` pins the pilot-path observable. Its own header records the limit that
the standing refill (+40/tick) lands on the same tick, so that fixture alone does not distinguish
the two rules — the unit case does. Matrix **29 fixtures / 30 case rows / 47 fields**.

## V3-19. Guard has an animation; the right sidestep's row mapping is correct (2026-10-23)

Owner report: the right grounded sidestep plays a blocking-looking clip, and blocking shows no
animation at all.

### Blocking: it does have a stance, and the port was not playing it

The port's `state_move_id()` returned `-1` for `Guard` with the comment "Guard binds nothing; see
`state_has_animation_selector` for the recovered block path", so the state held whatever clip was
already playing — in practice the **idle** clip (measured: `guard -> anim_idx=0 name=Anim-124`).
That is the "no animation" the owner saw.

The claim itself is only half right. The block *branch* of the damage function `FUN_00637950` does
bind no move — verified again here: its `else` arm writes the hit registry (`= 2`), the `0x100`
marker, decrements a counter and calls `FUN_0042c800(2)`, which is just "fill the 4-slot registry
with 2". But the guard **stance** is a state of its own in the character DAT:

| row | meaning | Rena+0 clips |
|---|---|---|
| 390 | guard preparation / hold / release | 60, 61, 63 |
| 391 | successful guard | 77, 62, 63 |
| 392 | attacker's recoil after being guarded | 64, 65 |
| 393 | (guard family) | 110, 111, 113 |

(Read from the parsed DAT through `CharacterMoves`; the bundle's `battle_guard_motion.hpp` names
the same three states and confirms 390 `phase 1` drains `gauge -10` per tick and exits on a
released button — the drain the port already models.)

**Fix, deliberately split:** the port binds row 390's opening clip at the animation seam
(`try_switch_animation`'s no-selector branch) but does **not** adopt the 390 *move body*. Adopting
it was tried first and broke blocking: that body is a two-button chord (`button_a && button_b`)
whose phase 1 exits as soon as a button is missing, so running it drops the stance — the guard
fixture caught it immediately (`dummy_hp exp 100 got 99`, a guarded hit landing). Guard now plays
set 60 and still blocks.

### The right sidestep's row is not mis-wired

Checked rather than assumed, because "wrong clip" and "wrong row" look identical on screen:

- `FUN_00445ee0` routes `+0x830 == 3 -> 0x18` (row 24) and `+0x830 == 4 -> 0x17` (row 23);
- the bundle's command detector (`battle_ground_dash.hpp`) derives them as
  `axis = dir <= 2 ? 1 : 0`, `sign = (dir == 1 || dir == 3) ? -1 : 1`, so **3 = x(−1) = Left**
  and **4 = x(+1) = Right**;
- therefore Right → row 23, which the DAT fills with clips **22, 23, 24** (Left's row 24 fills
  19, 20, 21).

So the port sends Right to the right row and plays the clip the DAT pairs with it. Set 22 is
**not** a guard clip (the guard family is 60/61/63/77/62/64/65/110..), so the pose the owner read
as "blocking" is row 23's own startup clip. Whether that clip is the correct artwork for a right
sidestep is a **data/art question, not a routing bug**, and it is left open rather than guessed:
the port's set indices come straight from NN.dat, and no evidence here says which shipped clip
should replace it.

### Follow-up: binding the clip was not enough (owner: "still incorrect")

Measured live with a temporary probe on `bind_animation_set` (`--native-actions=rena0`, guard held
from frame 70): the state really does bind `state=6 move=-1 set->60 pilot=1` — but consecutive
captures of the guard differed by only **0.9%** of pixels, i.e. the stance was bound and **frozen**.
Binding a clip does not animate it when no move body advances its sections, so the owner's "no
animation at all" was still true in the only sense that matters: nothing moved.

Fix: the stance now steps through row 390's own section order — preparation clip, then the hold
clip — advancing when the **preparation clip's own duration** has elapsed (read from the bound
DAT; no invented constant). Captures now differ by **8.8%** between the two phases. Row 390's
third section (the release) **is** reachable — a release in the hold section enters it as a
phase, not a state exit (V3-40) — but the port cannot play it yet: its Guard leaves the state on
release, so there is no window to bind set 63 into.

Coverage: `melee_rules_test`'s guard section (was "guard keeps the walk clip") now pins row 390's
opening clip and its persistence, for both the walk→guard and stand→guard entries;
`rena0-guard-gate-pilot` still proves a guarded hit deals no damage.

### Right sidestep: not reproducible as a wiring fault, needs one observation

Live probe of a right double-tap: `state=2 move=23 set->22` then `set->23` — the row and clips the
DAT pairs with it. Two more checks ruled out the obvious causes:

- set 22 is **not** the guard art: at a fixed frame, set 22 differs from guard sets 60 and 61 by
  24.0% / 24.6% of pixels, i.e. about as much as the left-dash set 19 does (24.3% / 25.3%) —
  there is no clustering of 22 with the guard family;
- the index space is consistent (Rena's model carries 124 clips; every referenced set is in range).

So the routing and the clip are both what the shipped data says, and the pose the owner reads as
"blocking" is row 23's own startup artwork. Which shipped clip *should* stand in for a right
sidestep is a data/art question with no evidence in hand, so it is left open rather than guessed.
The one observation that would settle it: whether the LEFT sidestep looks correct. If left is right
and right is not, the suspect is row 23's art; if both look wrong, the command-to-side mapping is
the suspect after all and needs a different probe.

### V3-19b. The guard's hold flag — the actual cause of "no animation" (2026-10-23)

Owner stopped the two-at-once work and asked for the block first, with a screenshot of the
original: Rena holds her weapon and the stance **loops**.

The Ginkiha bundle carries a complete guard implementation
(`development_animated_combat.hpp`, `battle_guard_motion.hpp`, `actor_frame_cursor.hpp`). Its
advancement rule is the answer:

```cpp
// development_animated_combat.hpp:2245
else if (++guard_tick[i] > data.animation_durations_.at(phase.value)
         && g.phase + 1 < phases.size()
         && !data.animation_settings_.at(phase.value).hold_phase) { ++guard_phase[i]; guard_tick[i] = 0; }
```

A phase advances only after its clip's own duration **and** only when that clip does not declare
`hold_phase`. A clip with `hold_phase` set stays on screen and its animation loops — the looping
stance in the screenshot.

**The port had already parsed that flag and never used it.** The per-set record is
`(blend_frames, hold_phase, event_count)` (`actor_animation_settings.hpp:27`); the port reads the
same three words as `transitionDuration, phaseGate, eventCount` and exposes the middle one as
`animation_set_phase_gate()` with the comment "the second gates elapsed-count advance". So the
data was there and the rule was simply not applied: the guard bound one clip and nothing advanced
or held it.

**Fix:** the stance advances through row 390's sections when the current clip's duration has
elapsed **and** `animation_set_phase_gate(current) == 0`; a hold phase stays. Measured on a live
pilot match with Guard held: prep→hold transition changes 2.7% of pixels, the hold is stable
(0.3–0.5%), and the stance ends when the meter empties (the −10/tick drain), which is the
recovered exit. Row 390's release section stays unreached because the port's Guard leaves the
state on release; V3-40 records exactly where the original puts it (phase 2, set 63) and why it
is not implemented yet.

Tier: the *rule* is recovered (bundle mirrors the shipped format field-for-field and cites the
state numbers); the field's presence in the port's own parse is verifiable in-tree. No originality
claim beyond that.

### V3-19c. Why the guard was still static: two clock bugs, not the art (2026-10-23)

Owner: "Pressing the button now plays a frame of the blocking animation, but it is static."

The clip was right and the phase rule was right; the **clock** was wrong twice.

1. **The playhead was driven by the move clock.** The per-tick animation update sets the track
   position from `m_moveElapsedTicks`, which only a running move advances. Guard runs no move, so
   the position sat at 0 forever. The original drives the guard from its own counter
   (`actor_animation_key_time(guard_tick, ticks_per_second)`); the port now sets the guard's track
   position from `m_guardTicks` and wraps it inside the clip's length, which is what lets a hold
   phase loop.
2. **The stance reset ran on every held tick.** The guard entry branch tests `input->down[Guard]`,
   so it fires each frame the button is held; resetting `m_guardClip`/`m_guardPhase`/`m_guardTicks`
   there wiped the stance every tick. Now edge-gated on the state actually changing.

**Units, which was the third mistake:** `anim.duration` is in the model's X tick scale
(`xmodel.h` declares 4800 per second for these clips), not seconds. Comparing it directly against
elapsed seconds meant the prep phase never ended.

Measured after the fix, live pilot match with Guard held:

| event | value |
|---|---|
| prep clip (row 390 phase 0 = set 60) | ~7 ticks |
| then hold clip (phase 1 = set 61, `hold_phase = 1`) | loops, period ~0.167 s |
| hold clock | wraps 0.048 → 0.041 → 0.028 → 0.015 |

Row 390's release section (set 63, `hold_phase = 0`) is still unreached because the port's Guard
leaves the state on release — the original enters a third phase instead (V3-40), which needs the
stance's cancellation rules before it can be played.

Honest note on appearance: frame-to-frame change over the hold is small (0.5–0.9% of pixels),
because set 61 is a subtle stance loop. The mechanism is verified correct against the recovered
rule; whether the shipped loop is as lively as the owner expects is an art judgement that this
evidence cannot settle.

### V3-20. Guard is a grounded stance — no air block (2026-10-23)

Owner report: the original does not allow blocking in the air; the port did.

The port's guard entry tested only the held button, the exhaustion latch and the meter, so an
airborne press entered `Guard` and started the `-10`/tick drain. Both sides now test grounding:

- **entry**: `input->down[Guard] && m_grounded && !m_guardExhausted && meter > 0` — an airborne
  press neither enters the stance nor spends the meter;
- **exit**: the stance also ends when the fighter leaves the ground, alongside the existing two
  exits (button released, meter empty). So a guard cannot survive into an aerial.

`fighter_script_test` previously asserted the opposite ("airborne Guard entered" = true); it now
asserts the refusal, that the fighter stays airborne, and that the refused press drains no
stamina — with the stamina baseline captured before the press, so the check is a real comparison
rather than a tautology. Tier: owner observation (3) for the rule; the port change is mechanical.

### V3-21. Side-dash timing: measured, two concrete defects found, not yet fixed (2026-10-23)

> **Superseded in part by V3-22, V3-23 and V3-24.** The phase lengths below are the
> *declared* clip periods; the body advances its clock more than once per update
> (V3-22), the movement speed was a constant rather than the recovered profile
> (V3-23), and the missing "pose" was a sparse clip composed over the retained pose
> (V3-24). Read those before trusting any conclusion in this entry.

Owner: the right sidestep's animation is correct but its **timing** is wrong (the original advances
sooner), and **neither** side step has a recovery animation. Owner confirms the LEFT is otherwise
correct.

Measured phase data (parsed DAT, both rows):

| row | phase 0 | phase 1 | phase 2 |
|---|---|---|---|
| 23 (right) | set 22, 7 ticks | set 23, 12 ticks | set 24, 24 ticks |
| 24 (left)  | set 19, 7 ticks | set 20, 12 ticks | set 21, 24 ticks |

The two rows are **identical in structure and duration**, so the right/left difference the owner
sees cannot come from the row data — and the owner's own diagnosis (correct art, wrong timing)
agrees: both sides run the same clock.

Live probe of both dashes (`DBG_DASH` on `bind_animation_set`, removed afterwards):

| side | binds |
|---|---|
| right | `state=2 move=23` → `set->22` → at state tick 13 `phase=1 set->23` |
| left  | `state=2 move=24` → `set->19` → at state tick 13 `phase=1 set->20` |

Two defects, both confirmed:

1. **Phase 2 never binds on either side.** No `set->24` / `set->21` appears, so the recovery
   section the owner asked for is never played — the row leaves Run after phase 1.
2. **Phase 0 takes 13 state ticks against a 7-tick clip.** That is the "taking too long" the owner
   measured against the original. `advance_animation_phase` gates on
   `animation_period_frames(clip) >= m_moveElapsedTicks`, so a 7-update clip
   should advance at 7; it advances at 13, so the elapsed counter is losing ticks (the
   `m_holdAnimation` hold on a transition tick is the obvious suspect, but that alone does not
   account for six).

Not fixed in this pass: the cause of the missing ticks needs one more instrumented run on
`m_moveElapsedTicks`/`m_holdAnimation` per tick, and guessing the recovery's exit would risk the
dash's own movement model. Recorded here so the next pass starts from the measurement instead of
from the symptom.

#### V3-21b. Where the side dash stops (instrumented, one more step named)

Three instrumented runs on a right side dash (all probes removed afterwards):

1. **The phase clock itself is correct.** `[p]` printed `move=23 phase=0 th=7 elapsed=1..8` then
   `phase=1 th=12 elapsed=1..12` — i.e. phase 0 ends on schedule (8 ticks for a 7-tick clip, the
   `thr >= elapsed` off-by-one) and phase 1 gets its full 12.
2. **Run never leaves through `set_state`.** A `set_state` probe filtered on leaving `Run`
   produced **no output at all**, so nothing transitions the state out of the dash.
3. **The advance call stops.** An entry probe on `advance_animation_phase` filtered to move 23
   printed up to `phase=1 elapsed=11` and then no more — so the per-tick animation block stops
   being reached while the state is still `Run`.

So the dash is not timing out and not being cancelled by a state change: the update simply stops
calling the animation/phase step partway through phase 1, which is why phase 2 (set 24, `set 21`
on the left) never binds and there is no recovery clip. The next step is to find what returns
early between the state update and that block — the remaining budget did not cover it, and the
dash's movement completion is the obvious place to look (`move_behavior.h`'s `dash*` fields and
any early return in `update()` guarded by a dash completion test).

Note the phase-2 hold rule already exists at `fighter.cpp:2086`
(`m_holdAnimation = m_holdTicks++ < motion->dashHoldLength`, inside `m_phaseIndex == 2`) and can
never fire while phase 2 is unreachable — the bundle's `extra_side_ticks` equivalent. Reaching
phase 2 should therefore also restore the extra side ticks in the same change.

#### V3-21c. FIXED: side dashes were cut by a fixed frame timer (2026-10-23)

Root cause found. `try_dash` ended with

```cpp
m_stateTimer = programmed ? 0 : FighterConstants::kDashFrames;
```

and `programmed` is true only for the **forward** dash (`m_grounded && m_model && dashMove == 20 &&
locomotion(...)`). Every other dash — the side steps 23/24 and the back dash 27 — therefore ran on
`kDashFrames = 20` and was forced back to Idle by the generic state-timer expiry
(`fighter.cpp:420`) before its last section. Measured: a side row is 8 + 11 ticks into phase 1 at
that point, and the observed dash ended at exactly phase 1 elapsed 11 — the 20th tick.

That explains both symptoms in one cause: the animation "taking too long to reach the next part"
(it never reached it) and "no recovery animation" (phase 2, set 24 on the right and set 21 on the
left, was unreachable).

**Fix:** a grounded dash whose recovered row has more than one section is phase-driven
(`m_stateTimer = 0`), so its row's sections run to completion and the dash ends through
`advance_animation_phase`'s last-section branch instead of a frame count. Verified live: the right
side dash now binds **set 22 → 23 → 24**, and phase 2 runs its full 24 ticks.

Two scoping decisions, both deliberate:

- **Grounded only.** Applying it to the air dash (row 30, also multi-section) changed its expiry
  back into Jump — `fighter_script_test` caught it ("air dash expires into Jump" expected 15, got
  2). The air dash keeps `kDashFrames`.
- **Pilot path only.** The COM drives the same fighter class, and with the longer dash its swing
  cadence fell from 3+ to 2 over the bot suite's 900 ticks (`bot_brain_test` caught it). The
  recovered full-length dash is now applied where the recovered rules already apply
  (`m_pilotMeter`); the COM and the legacy path keep the truncated timing. That is a **named
  limit**: the COM's side dash should eventually be phase-driven too, which will need its cadence
  expectations re-derived rather than edited to fit.

Suite 83/83 (excluding the known `device_isolation_test` flake), pilot matrix unchanged.

#### V3-21d. Animation duration units, measured (2026-10-23)

Answering "is `duration` seconds or ticks": it is in the **model's own X tick scale**, and the
model declares `AnimTicksPerSecond = 4800` (`xmodel.h`). So `seconds = duration / 4800` and
`frames at 60 Hz = seconds / 0.016`. Measured on the live binding for the right side dash:

| set | phase | raw duration | seconds | frames @60 Hz |
|---|---|---|---|---|
| 22 | startup | 560 | 0.1167 | 7 |
| 23 | travel | 960 | 0.2000 | 12 |
| 24 | recovery | 1840 | 0.3833 | 24 |

Left mirrors it (19 / 20 / 21 at the same lengths).

The port advances a phase when `elapsed > trunc(seconds / 0.016)` (V3-26), so with these values phase 0
ends after 8 ticks, phase 1 after 13 and phase 2 after 25 — a 46-tick row.

**Open:** the owner reports the pose resting on its last frame for many ticks before the next part.
A whole-frame pixel diff cannot locate that window while the dash is moving the camera — every
sample differed by 36–55% for that reason, so the measurement was inconclusive. Locating the hold
needs a camera-independent measure: the skeleton's pose delta, or a capture with the camera pinned.

### V3-22 — isolated right-dash clock correction (Rena+0, row 23)

Owner-reported blocker: right side-dash travel still looks wrong. The bounded
follow-up traces the complete recovered body rather than selecting clips by eye.
`research/decompiled/FUN_0043ffc0.c:288-291` (case `0x17`) increments both
`+0xae04` and `+0xae08` when the entering primary counter is divisible by 9,
including zero; its common tail increments both again. The attributed bundle's
`dash_native_bodies_20260929.hpp:215-232` agrees. This is tier-2 source evidence,
not an original-runtime trace. Original identity rechecked: SHA-256
`27e61475fbb3ea67f5058e3e0e6e93ad71d16a4d83fa42b02e605913a6a07f02`.

This supersedes V3-21's inference that clip period alone establishes startup
length: the body advances its clock more than once on selected updates. It also
corrects the old phase-2-only description of `extra_side_ticks`; the source's
modulo condition has no phase restriction.

The isolated regression keeps the port's current thresholds 7/12/24 and strict
`threshold < elapsed` exit. Expected one-based dash updates: sample counter 2 on
entry, travel at update 7, recovery at 18, Idle at 40. The previous port trace is
sample 1 and transitions 8/21/46. Sets remain 22/23/24; both controller tracks
sample the same primary clock. The separate original secondary counter remains
an unmapped seam, not a newly implemented field.

Scope: pilot-attached right dash only. Left dash, legacy path, movement speed,
meter drain, duration rounding and last-phase completion stay unchanged. The
full recovered body's 38/39-update exit is NOT the expectation for this isolated
change: it also depends on the distinct completion predicate and unresolved
truncation-versus-rounding evidence. Source-backed follow-ups remain constant
side-dash movement versus recovered braking, and recovery-phase meter drain.
The temporary `DAYBREAK_DASH_TRAVEL_SET` knob is removed with this change. It
swapped the phase's clip, its duration and the playhead rate together, so a
verdict taken under it described speed and sampling density rather than which
frames the clip shows, and it could not A/B the clip alone. Clip selection stays
the row's own tags 22/23/24, which the executed production trace already showed.

Implemented and verified: the regression failed before the runtime change
(entry clock 1) and passes after it (entry 2, transitions 7/18, Idle 40); the
suite is 83/83 excluding the known `device_isolation_test` flake and the fixture
matrix is unchanged at 29/30/47. Visual acceptance remains owner-pending, and
the fixture/acceptance denominator is unchanged: this is supplemental production
regression coverage, not a new accepted contract field.

### V3-23 — side-dash travel distance follows the recovered speed profile

Owner report after V3-22: the timing now reads correctly but the step **covers
roughly twice the original's ground**. The clip was not involved. The row body
seeds **20.0** on the phase's first update and bleeds **0.5** per update while
the phase is below 2 (floor **12.5**), then **0.7** per update in recovery (floor
0) — `FUN_0043ffc0.c:257-286`, case `0x17`; the attributed body
`dash_native_bodies_20260929.hpp:177-214` agrees, and the roster profile carries
the same numbers for both side rows (`battle_roster_side_dash.hpp:9-10`:
drain 12, speed 20, brake 0.5, minimum 12.5, stop 0.7).

The port held `kRunSpeed` (15.0 per update) for every Run update of the row,
which is the same frames at the wrong speed: **600 units over 40 updates** rather
than the profile's **382.9**. Set, phase and clip bindings were already correct,
so this was purely the motion channel — and it is what makes a correct animation
read as sliding, which is why the owner could not separate "travel animation
looks wrong" from "it goes too far".

Implemented pilot-only, for rows 23 and 24 together: both rows carry identical
profile data and share one code path, so fixing one side alone would have made
the two steps visibly asymmetric. The COM and the flag-off path keep the constant
legacy speed. Verified by pinning the row's cumulative travel to 380-386 units
(measured 382.9) with a second assertion that the 600-unit constant cannot
return; suite 83/83 excluding the known flake; fixture matrix unchanged. Tier 2
source-backed, tier 4 install-backed regression; no original-runtime or
visual-parity claim, and the owner's visual verdict is still the acceptance step.

Remaining, deliberately unchanged: the meter still drains on every Run update
instead of only before the recovery phase.

### V3-24 — sparse clips keep the previous pose (the side-step travel fix)

Owner: after V3-22/V3-23 the step's distance matched but its **middle was still
wrong — the left arm sat forward and invisible, where the original holds it back**.
No shipped clip contains that pose, and hunting clips was the wrong search: the
travel clip is **sparse**, and the pose the owner saw is a composition.

`Anim-101` (the right row's travel tag, set 23) keys **22 channels out of 78
frames** — the right arm chain, the left leg chain, the hands and the prop bones.
It has no left-arm, spine or root channels at all. Four of the rig's 124 sets are
similarly sparse, and they are all dash/quick-pose clips.

The native controller does not rebuild the skeleton from bind between updates. It
keeps the pose and a bound set writes only the bones it names:
`prepared_actor_controller_pose.hpp:27` takes `ActorSkeleton&` and assigns
`pose.bones.at(track.bone).local` per named bone, and `actor_controller_pose.hpp:42`
states the rule — *"base is the retained output pose on later evaluations. Sparse
sets leave unnamed matrices intact, as the native D3DX controller does."*
So during the travel phase the left arm holds the pose the startup clip (set 22)
left it in, and that is the motion the owner recognises.

The port rebuilt every pose from the bind pose (`Controller::evalLocal` called
`bindChannels` per evaluation), so every sparse clip collapsed its unnamed bones to
the mannequin stance. Implemented: `Controller` retains its evaluated local pose and
seeds from it, clearing only when the rig changes. Regression in
`rena0_pilot_gate_test` Case E samples `Bip01_L_UpperArm` — bind, after the startup
clip, then after the sparse travel clip — and requires the travel sample to equal
the startup sample (measured quaternion dot 1.000000) and the startup sample to
differ from bind, so the assertion cannot pass vacuously. Suite 83/83 excluding the
known `device_isolation_test` flake; fixture matrix unchanged at 29/30/47. Tier 2
source-backed, tier 4 install-backed regression; the owner confirmed the live result.

**Also found, and it cost real time:** the object that owns the header's
implementation (`src/assets/assets.cpp`) was **stale** — last built 2026-10-11 while the
tree moved on — so the library kept the old `evalLocal` while a standalone probe
compiled from the same header showed the new one. The dependency itself is sound
(`touch xmodel.h` makes ninja rebuild it), so this is a stale artefact rather than a hole
in the build; a header change that appears inert means suspect the object file. `--out` captures also never exercise this path: for a match, `advanceAnimation`
is skipped in capture mode (`main.cpp:6345`), so every capture I produced drew the
load-time pose and my A/B was blind. Both are recorded as build/verification limits,
not as behaviour.

Two lessons for the pilot record: a clip index is not evidence of clip content (the
same `Anim-NN` name carries different channels in `00.X`, `01.X` and `02.X`), and a
missing animation can be a runtime composition rather than missing data.

### V3-25 — the ground dash spends meter only before its recovery phase

The port drained −12 on **every** Run update of the side and back dash rows, so the
recovery phase — 22 of the row's 40 updates — billed the meter for a phase the body
does not charge. Measured on the right side dash from a full meter: **480 spent
(1000 → 520)** where the source spends **216 (1000 → 784)**.

The recovered condition is a phase guard on the drain, in every ground dash case:

| state | body | drain guard |
|---|---|---|
| 20 forward | `FUN_0043ffc0` case `0x14` `:195` | `+0x2b7d < 2` |
| 23 right | case `0x17` `:257-259` | `+0x2b7d < 2` |
| 24 left | case `0x18` `:309-311` | `+0x2b7d < 2` |
| 27/28 back | cases `0x1b`/`0x1c` `:355` | `+0x2b7d < 2` |
| 30 air | case `0x1e` `:382-383` | `+0x2b7d < 3`, i.e. every section of its three-phase row |

The air dash's extra −3 sits inside `+0x2b7d < 2` and is gated on the word at byte
**+0x280** — `param_1[0xa0]` is word index `0xa0`, not byte `+0xa0`; that byte is the
prologue's freeze word `param_1[0x28]` (`:28-30`), which returns before any body runs.
**+0x280 is the JUMP button's held-frame counter** (see V3-32); this entry left the arm
unimplemented, and V3-32 implements it.

Two related facts settled in the same read, because they decide whether the port needs
more than a guard:

- **No meter exit on the ground dash rows.** Only the forward dash (`:229`) and the air
  dash (`:418`) leave phase 1 on `+0x834 < 1`. States 23/24/27/28 contain no meter test
  beyond the drain and its clamp, so a side or back dash admitted at any positive meter
  runs to its last update even at zero. The port already behaved that way; nothing to
  add, and adding an exit would have been wrong.
- **The drain precedes the clock inside a body visit.** In case `0x17` the order is
  drain `:257-263`, entry seed `:264-269`, movement/speed `:270-286`, the `%9` extra
  `:288-291`, then the common tail's increments, cursor and phase test `:2439-2444`. So
  the drain is charged to the phase the update *entered* with, exactly as the port's own
  order does (`execute_move_program` before `advance_animation_phase`). The two
  transition updates therefore still drain, which is why the count is 18 and not 16.

Regression: `rena0_pilot_gate_test` Case D now samples the meter on every dash update
and requires 988…784 across updates 1-18, then a flat 784 through update 40, with a
flag-off control at 1000. Removing the phase guard fails it with
`the recovery phase must open at 784, got 772`. Suite 83/83 excluding the known
`device_isolation_test` flake; fixture matrix unchanged at 29/30/47. Tier 2 source-backed,
tier 4 install-backed regression; no visual claim.

### V3-26 — the engine truncates the clip period; it does not round

The port computed each phase window with `std::nearbyint(duration / ticksPerSecond /
0.016)`, on the reading that `0x41e839` divides by 0.016 "before x87 rounding". That
reading was wrong, and it was wrong in the expensive direction: it only agrees with the
engine when the period lands on a whole number of updates or on a `.5` tie that rounds
down, so roughly half the clips in the game ran one update too long.

The instruction trail, from the saved `.text` disassembly:

- `0x41e834` calls the `GetPeriod` wrapper, `0x41e839` does `fdiv DWORD PTR ds:0x6a2434`
  (the 0.016 constant), `0x41e83f` calls **`0x66b668`**, and `0x41e84a` stores the `eax`
  result — a plain `int`.
- `0x66b668` is not a bespoke rounding helper. It is the compiler's own float→int
  conversion: it appears at **1148 call sites** in the image, which is only consistent
  with every `(int)float` in the program. Its body (`0x66b668-0x66b6c5`) rounds with
  `fistp`, forms the residual `x - round(x)`, and then corrects it with
  `add ecx,0x7fffffff; sbb eax,0` — the standard carry trick that subtracts one exactly
  when the rounding went up. That is **truncation toward zero**, under any FPU rounding
  mode.
- The recovered bundle states the same rule: `actor_animation_clock.hpp:17-22`,
  `unsigned(period / 0.016f)`.

So a 23.958-frame clip is a **23-update** window, not 24. The rule is now one shared
helper, `gameplay/animation_period.h`, used by `advance_animation_phase`, the
pre-emptive last-section exit, the activation-overlay window and both adapter window
computations — the duplicated arithmetic is gone with it.

A zero window is a real window: the source's test is strict `period < elapsed`, so a clip
that truncates to 0 advances on its first update. The helper therefore returns `-1` for
"cannot be derived" and `0` for a genuine zero, and an existing synthetic half-update case
in `melee_rules_test` now guards that distinction — it failed on the first attempt at this
change, which is what caught the mistake.

Measured blast radius, from the full suite (83 tests):

| what moved | before | after |
|---|---|---|
| Rena+0 right side dash, recovery window | 24 updates | 23 |
| Rena+0 right side dash, row length | 40 updates | **39** |
| Akane+0 move 300, ribbon first active frame | 92 | **91** (in-phase tick 4 unchanged) |
| Akane+0 move 330, ribbon first active frame | 102 | **101** (in-phase tick 11 unchanged) |

The two Akane observations are not pilot cases, so this is the first global rule change
touched by the pilot work; it was applied only with the owner's explicit approval, and the
re-pin is one frame each with the in-phase tick unchanged, which is the signature of the
*preceding* phase getting shorter rather than of a different window shape.

Verify: suite 83/83 excluding the known `device_isolation_test` flake, fixture matrix
unchanged at 29/30/47. Tier 2 (instruction-level) with tier 4 regression coverage. The
tick values stay provisional: `FUN_004218c0` completes on `period <= frame + 1` while the
tail advances on `period < frame`, and whether those two record pointers (`+0xade8` vs
`+0xade4`) hold the same period for a given row is not settled by the corpus.

### V3-27 — a row ends on the completion predicate, one update before the tail rule

V3-26 left one question open: the tail advances a phase on `period < frame`
(`FUN_0043ffc0:2442`) while `FUN_004218c0` completes on `period <= frame + 1`. Read in
full, the predicate is settled and so is the record it reads.

`FUN_004218c0(this)` is exactly:

```
ptr = *(int **)(this + 0xade8);            // the current set's record
if (*ptr <= *(int *)(this + 0xae04) + 1) { // period <= entry frame + 1
    if (FUN_0063bf40() - 1 <= *(int *)(this + 0xadf4)) // sectionCount - 1 <= phase
        return 1;                           // complete
}
return 0;
```

- `FUN_0063bf40` is `return *(undefined4 *)(param_1 + 0x10)`, and `FUN_00421100:15`
  writes that field from the row lookup at every phase change — it is the **section
  count**, so the second condition is "the phase is the row's last".
- `+0xade4` (the tail's record) and `+0xade8` (this predicate's) hold the **same**
  pointer. `FUN_00421410:31` stores `param_1 + set*0xe + 0x1d78` — a per-set record whose
  word 0 is the period and whose `+0x20` is the gate — and that expression does not
  depend on the track index, so track 0 and track 1 point at one record. The earlier
  suspicion that the two sites might read different periods is therefore closed: they
  read the same one and differ only in the comparison.

Consequence: for the last section the row ends when `entry_frame + 1 >= period`, one
update earlier than the between-sections rule would end it. The port took the tail rule
for the last section too, so **every row ran one update long**. Implemented as an explicit
early completion for the last section, using the frame the update entered with (the clock
step is subtracted, and the predicate does not run on a held-clock tick, matching the
body's early `FUN_00421100` return).

Measured: the full suite moves by exactly one assertion — Rena+0's right side dash, 39
updates to **38** — and nothing else in 83 tests changes, which is what a one-update
truncation of the row's end should look like. Reverting the predicate fails the pinned row
with `update 38 must end the row on Idle`. Suite 83/83 excluding the known
`device_isolation_test` flake; fixtures unchanged at 29/30/47. Tier 2 instruction-level.

This also retires the last "provisional" part of the phase clock: window length (V3-26),
between-section advance (strict, unchanged) and row completion (this entry) are now three
separate, individually cited rules.

### Open defect list (owner observation, 2026-10-28)

Reported from live play and recorded before being worked. These are tier 3 (owner
observation): they state what the original does and what the port fails to do, and none of
them is yet backed by a fixture or a recovered rule.

| id | report | current port behaviour | scope |
|---|---|---|---|
| D1 | the side dashes move in a **circular arc toward the targeted enemy**, not along the input direction | `try_dash` fixes one world direction at entry (`m_dashDir = target_relative(±1, 0)`) and integrates a straight line for every Run update | rows 23/24 |
| D2 | an **air dash carries its momentum**; the character should not drop straight down when it ends | the air dash hangs then the normal gravity path takes over with no carried velocity | row 30 |
| D3 | an air dash **points where it was input** | the fighter always faces the target | row 30 |
| D4 | the air dash's extra −3 meter arm | **fixed** in V3-32: `+0x280` is the jump button's held-frame counter, and the arm charges 3 while it is down in phases below 2 | row 30 |

All four were closed: D1 in V3-28, D2 and D3 in V3-29, D4 in V3-32, each with a regression that
fails without its change. This table is kept as the intake record, not as open work.

### V3-28 — D1: the side step arcs toward the target

Owner report (D1): the side dashes travel in a **straight line** in the input direction;
the original moves in a **circular arc toward the targeted enemy**.

The mechanism was already in the source; the port had collapsed it. `FUN_0043ffc0` case
`0x17`/`0x18` writes the movement angle as **±90** (`:265-271`, `0xc2b40000` = −90 for row
23 and `0x42b40000` = +90 for row 24) — a *relative* angle, re-asserted on the phase-1
visit rather than captured once. The basis it is relative to is refreshed every update:
the port's own `m_inputFacing` is that basis (`fighter.cpp` computes it as the bearing to
the opponent before input dispatch, per `FUN_004202b0`/`FUN_0042dd90`). The dash entry
froze `target_relative(±1, 0)` into a world vector and integrated it for the whole row, so
the step could only be straight.

Implemented: `m_dashSide` records the screen axis at admission (+1 row 23, −1 row 24, 0 for
every other dash), and the Run movement step re-derives `target_relative(m_dashSide, 0)`
from the current basis each tick. Because the basis rotates as the fighter slides, the
path bends toward the opponent — a circular arc whose radius is set by the distance to the
target, which is why the effect is subtle at range and pronounced up close.

Measured on the pinned scenario (opponent 2000 units away, +x tap):

| | before | after |
|---|---|---|
| path length | 382.9 | **382.90** (unchanged — same speed profile) |
| displacement along the tap | 382.9 | **380.61** |
| displacement toward the opponent | 0.45 (tap drift only) | **35.80** |

Regression: the gate test now separates path length from displacement and requires
`endZ > 1`, `endX < path − 1` and that the first update still leaves along the tapped
axis. Disabling the per-tick re-derivation fails it with
`the side step must curve toward the target, but z stayed at 0.450308`. Suite 83/83
excluding the known `device_isolation_test` flake; fixtures 29/30/47 unchanged.

Tier 2 for the ±90 write and the basis refresh; tier 3 for the arc's *shape* — the owner's
observation is what establishes that the arc is the intended look, since no fixture or
trace here measures the original's path.

### V3-29 — D2/D3: the air dash points along the input and keeps its momentum

Two owner reports, one state (row 30). Both came from the same reading of the body.

**D3 — it points where it was input.** `FUN_0043ffc0` case `0x1e` sets `+0x18` (movement
angle) to **0** (`:408`), i.e. along the actor's own angle, and then calls
`FUN_00421780()` at the end of **every** update (`:412`, `:427`) with `+0x874` = 60°/tick in
phase 0 (`:408`) and 2°/tick from phase 1 (`:414`). `FUN_00421780` steers the angle at
`+0x64` toward one of **eight compass bearings derived from the held-input words** at
`+0x278`/`+0x27c` — 0, ±45, ±90, ±135, 180 — not toward the target. So the air dash turns
with the stick, and the fighter's heading follows it. The port resolved the direction
against the target axis and left `m_facing` at the target bearing, so she slid sideways
while still facing the enemy.

Implemented: the airborne dash takes its direction from the held axes, sets `m_facing` to
that direction, and re-steers once per update at the body's own rates (60°, then 2°).

**D2 — momentum survives the dash.** Case `0x1e` completes into state 43 (`:379-381`), and
case `0x2b` (state 43) **never writes** the horizontal speed `+0x15` or the movement angle
`+0x18`: it only steers the angle (`+0x874` = 1.0/tick, `:485-486`) and integrates the
vertical. So the dash's horizontal velocity is still there afterwards and the fighter keeps
sliding. The port's airborne movement recomputed velocity from the stick every tick and
zeroed it when nothing was held, which is why she dropped straight down.

Implemented: `m_airDashCarry` keeps the dash's speed and direction through the airborne
state that follows, steering at 1°/tick toward held input, cleared wherever the air dash is
re-armed (landing, respawn, round reset).

**One correction found while reading:** the port's air dash speed was `kAirDashSpeed` =
20.0/tick; the body writes `+0x15` = `0x41840000` = **16.5/tick** (`:407`). The pilot path
now uses the body's value.

Regression (`rena0_pilot_gate_test` Case F): jump, then double tap Right in the air with the
opponent at +z. It requires row 30 with its first set bound, that the actor's yaw differs
from the target bearing by more than 1 rad, and that the fighter covers more than 20 units
horizontally while airborne **after** the dash ends. Reverting the direction/facing work
fails with `facing -0.002520 vs bearing -0.010770`; reverting the momentum carry fails with
`covered 0.000000 units`. Suite 83/83 excluding the known `device_isolation_test` flake;
fixture matrix unchanged at 29/30/47.

Tier 2 for every field and rate; tier 3 for the intended feel. The `+0x280`-gated extra −3
meter arm is untouched and remains D4.

### V3-30 — the air dash's gated travel section, its descent, and its release rule

Found while testing V3-29: the air dash never reached its recovery phase, so its descent and
its completion never ran. Three separate things were wrong, and the 20-update
`kDashFrames` timer was masking all of them.

**1. Row 30's travel set declares the phase gate.** Set 55's `+0x20` hold flag is 1, so the
clock can never advance the phase (`advance_animation_phase` returns on a gated set) and the
completion predicate cannot fire either. The body leaves phase 1 on **its own counter**:
`+0x3a` is zeroed in the phase-0 seed (`:408`), incremented once per phase-1 visit (`:415`),
and the phase advances once `5 < +0x3a` and either no direction is held (`+0x9f == 0 &&
+0x9e == 0`) or the meter is empty (`+0x20d < 1`) — `:416-420`. Holding the stick therefore
*extends* the air dash, which is what makes it steerable; releasing drops it into recovery.

**2. The recovery phase descends.** Phases below 2 subtract 0.5/tick from `+0x10` and floor
it at zero (`:386-390`), so the dash can never sink while it travels — a hang. Phase 2
subtracts `+0x16` with no floor (`:422-424`), i.e. an ordinary fall. The port hung for all
three sections. `kGravity` is 1800 u/s², exactly the body's 0.5 per tick per tick, so the
normal fall is already the recovered rate; only the hang window needed narrowing.

**3. The row was truncated.** `kDashFrames` = 20 cut the dash inside phase 1; the row's three
sections are 10/15/10 = 35 updates. The pilot's airborne dash is now phase-driven, like the
ground ones. Scoped to the pilot path: `fighter_script_test`'s air-dash case attaches no
meter policy and keeps the legacy 20-update window, so it is untouched.

Measured on the pinned scenario: 5 updates of hang in phase 0, a 6-update travel window that
ends on the release rule, then a descent from y = 16.5 to the ground. Regression Case F now
also requires the dash to **descend** (`drop > 2`) and, because the descent lands quickly,
climbs to y > 40 first so the momentum carry of V3-29 still has airborne ticks to observe.

Suite 83/83 excluding the known `device_isolation_test` flake; fixture matrix unchanged at
29/30/47. Tier 2 for the release rule, the descent rates and the section windows.

Still open (D4): the `+0x280`-gated extra −3 meter arm and the *climb* arm of `+0x10` in
phases 0-1 (it rises 0.5/tick, capped at 8.0, when that word is non-zero).

### V3-31 — what the air dash still does not model (D4 and its neighbours)

Cross-check of V3-29/V3-30 against `FUN_0043ffc0` case `0x1e`/`0x2b` and the transcribed
body `.local-analysis/.../dash_native_bodies_20260929.hpp:512-629`. The transcribed body
matches the dump operator for operator, including `0x41840000`, `-0xb`, `0x41000000`,
`0x3f000000` and `0x40000000`, and the phase-0-frame-0 ordering.

Confirmed matching already: the 16.5/tick slide, the 60°/2° steering, the 0.5/tick² fall
(`kGravity` 1800 = 0.5×60²), the phase-1 release on `5 < +0x3a`, and the hang floor.

Open, in priority order:

1. **The climb arm (D4).** Phases below 2 do not merely floor `+0x40` at zero — when the
   word at **byte +0x280** is non-zero they add 0.5/tick up to a **cap of 8.0/tick**, and
   charge an extra **−3 meter** (`:391-396`). So an air dash can *rise*, fast, at extra
   cost. Nothing of this exists in the port, and `+0x280` is still unmapped.
2. **Phase 2 starts from the accumulator.** `:423-425` subtracts 0.5/tick from whatever
   `+0x40` holds, so a dash that exited phases 0–1 at +8 keeps rising for ~16 updates
   before falling. With the climb arm absent the accumulator is always 0, so this is inert
   until item 1 lands — they must ship together.
3. **The ground test exists only in phase 2** (`:426-430` → state `0x2c` = 44, the
   air-landing row). The port's generic collision landing ends the dash in *any* phase and
   goes to Idle, so it never enters a landing row. Fixing this means modelling state 44,
   which is a structural change, not a constant.
4. **The state the dash ends in is not the port's Jump.** `:379-381` completes into state
   43, whose `+0x10`/`+0x16` handling differs (a button word in 1..59 *suspends* gravity,
   `:542-544`) and which has no hover path. The port ends into Jump, which re-enables the
   row-41 hover. The momentum carry of V3-29 is behaviourally right for the slide, but the
   state behind it is not state 43.
5. **State 41's climb is modelled from the wrong field.** `:485-487` suspends gravity while
   the button word sits in 1..59 and `:458` seeds `+0x10` = 12.0; the port's `+0.2/tick`
   climb comes from the *horizontal* `+0x15` ramp at `:495-498`, not a vertical rate. Same
   unmapped word.

Items 1, 2 and 5 are all gated on identifying byte **+0x280**; 3 and 4 are state-model work.
The `battle_air_dash.hpp` tuning defaults (speed 15.5, drain 9) disagree with both the body
and the dump (16.5, 11) — use the transcribed body, and note the port already uses the
body's values.

### V3-32 — D4: +0x280 is the jump button's held counter; the air dash lifts while it is down

The air dash's extra −3 meter arm and its lift were blocked on identifying the word at byte
`+0x280`. It is now settled, and it corrects a mislabel this contract has carried since
V3-25: the field is **not** the `+0xa0` freeze word (`param_1[0x28]`, which returns before
any body runs) but **slot 0 of an 8-word held-input counter array at `+0x280..+0x29c`**,
inside the actor's embedded input object at `+0x240` — `input+0x40`.

- Producer: the per-frame poll `FUN_00657390` (asm `0x657478-0x6574cb`) increments the
  counter while its bound bit is down and zeroes it on release, with **no actor-state gate**;
  its one-frame release mirror is `+0x2b0`. The keyboard branch reads
  `DAT_0061928[key] & 0x80` the same way.
- Admission uses it as a **3-frame press window**: `[0x280] == 3 || 0 < [+0x2b0] < 3`
  (`FUN_00445ee0.c:441/449`, asm `cmp dword [reg+0x280],3` at `0x43f2af`/`0x43f339`) —
  grounded sends the press to row 40, airborne to row 30, i.e. the jump / air-dash button.
- A **hold** stance proves it is a held state rather than an id: row 390 exits on
  `[0x20d] == 0 || [0xa0] == 0 || [0xa1] == 0` (`:1652/1668`, `:1798`).
- Nothing in rows 30/41/42/43 or the admissions writes it, so it can be **non-zero during
  an air dash**: the dash is entered on a press, and holding the button keeps the counter
  climbing (4, 5, …). A tap releases within two frames, zeroes it, and the arm never fires.

The arm itself (`FUN_0043ffc0` case `0x1e` `:385-396`) is therefore simply *hold jump during
the air dash*: while the counter is non-zero and the phase is below 2, the vertical gains
0.5/tick up to a cap of 8.0/tick and the meter pays an extra 3 per update; with the button
up the vertical bleeds 0.5/tick back to zero, which is the hang the port had hard-coded. The
recovery phase then subtracts gravity from whatever the accumulator reached, so a climbing
dash keeps rising for a while after phase 2 opens (V3-31 item 2 — the same code path, now
reachable).

Implemented on the pilot path: the air dash's travel phases now ramp `m_vy` at ±0.5/tick
(cap 8.0/tick = 480 u/s) from the jump-held state and charge 11 + 3 per lifted update.

Measured, holding jump through a dash from 1000 meter: **14 per update in phases 0-1, 11 in
phase 2**, y rising 19.5 → 62.5 by the phase-2 transition and continuing to 85 before the
dash ends — the accumulator carrying over, exactly as `:423-425` describes.

Regression: `rena0_pilot_gate_test` Case F's lift variant requires at least 10 updates at
exactly 14, at least 3 at exactly 11, no update above 14, a rise greater than 5 units, and
that the recovery phase is reached. The transferable lesson: an unmapped field is worth one
bounded census — mislabelling `+0x280` as the `+0xa0` freeze word is what kept this arm out
of the port for three contract entries.

Also fixed by the same finding: `docs/PILOT-SEAM.md:1467` already mapped `0xa0 | 0x280 |
jump-held count | input.down[Jump]`; the contract now agrees with it.

### V3-33 — the empty-tap shot's ring card is drawn with no animation (open, needs owner scope)

Owner report with two screenshots (2026-10-28, tier 3): the effect card that plays on the
empty-tap shot does not match the original. In the original it reads as a soft, bright band;
in the port it reads as separated, hard-edged hoops with dark gaps between them.

Identified, not guessed:

- The card is **`data/effect/01.X`**. Rendering it alone reproduces the port's in-game
  appearance exactly (`--effect=Higurashi-Daybreak/data/effect/01.X`), so the in-game path
  is not substituting a different asset.
- That file is an **MSZIP-compressed** `.X` (`xof 0303bzip0032`; the port's own
  `decompressMSZip` at `assets/xmodel.h:782` documents the block format). Inflated, its
  material names the texture **`渦巻き.bmp`** — "spiral". `data/effect/渦巻き.cnv` exists and
  decodes to vertical fire streaks, and `TextureCache::get` (`assets/cnv.h:304-310`) resolves
  the `.bmp` → `.cnv` swap, so the texture is bound, not missing.
- The card **carries animation**: the inflated stream holds one `AnimationSet`, **10
  `AnimationKey`s and 40 `Frame` references**.
- **The port never plays it.** `SceneRenderer::EffectInstance`
  (`render/scene_renderer.h:386-400`) carries a model matrix, a billboard flag and — for
  projectiles only — a `pose` controller; `main.cpp` pushes effect cards as
  `{c.asset, shotModelMatrix(...)}` with no pose, so every card draws its bind pose. Rendering
  the card at frames 1, 5, 10, 20, 30, 40 and 60 of the demo produces **seven identical
  images**: the effect does not move.

That is a mechanical explanation for the visual difference — a spinning/evolving "spiral"
drawn frozen — and it is consistent with the hoops being visible individually instead of
blending into a band. It is *not* yet proof: no original-side frame trace exists, so the
claim "the original plays this card's animation" rests on the asset carrying keys at all
(tier 2) plus the owner's observation (tier 3), not on observing the original advance it.

Why this needs an owner decision before implementation: the change is in the **shared effect
path**, not the Rena+0 seam. Effect cards are spawned for every combo (muzzle, impacts, hit
cards, hyper aura), so animating them changes the look of the whole game — squarely the kind
of global change this repo requires approval for. The shape would be: `EffectInstance` gains
the card's own pose clock, `main.cpp` advances it from the card's age, and the renderer binds
`pose` for cards the way it already does for projectiles — verified afterwards with a capture
of the same shot.

Open questions for the verdict: (a) implement card animation now, or record and defer;
(b) if implemented, should the clock be the card's own `AnimationSet` rate or the spawn's
lifetime (they are different things and the original may use either).

### V3-34 — effect cards play their animation; the card's lifetime is the clock

Owner decision (2026-10-28): implement card animation now, globally, because a frozen card
is not a Rena+0 defect but a whole-game one — every muzzle flash, impact card and hit flash
is drawn the same way.

**What was wrong.** `SceneRenderer::EffectInstance` carried the instance's model matrix and,
for projectiles only, a live `xm::Controller`. `main.cpp` pushed every effect card as
`{asset, matrix}`, so all cards drew their bind pose. The cards ship animation (the empty-tap
card `data/effect/01.X` carries one `AnimationSet` with 10 keys over 40 frames; the muzzle
card `data/aura/00.x` animates a 1.0 → 0.876 scale), and none of it was played.

**What changed.**

- `EffectInstance` gains `poseWorld`, a pre-evaluated node-matrix array. An effect card lives
  for a few frames and is dropped at the end of the frame, so there is no controller to keep;
  a projectile keeps using `pose`. The renderer accepts either and feeds the same
  `Model::buildPalette`, which already gives an unskinned mesh its own frame matrix
  (`xmodel.h:2051-2055`) — a card's entire animation is that one matrix, and the vertex
  shader's `palette[o + bones]` path covers skinned and unskinned alike
  (`shaders/model_wgsl.h:121-127`).
- `main.cpp` samples each live card once per frame from its own model, at its own age.
- The clock is **recovered (tier 2), not a port rule** — an earlier draft of this entry said
  otherwise and was wrong. The descriptor carries no lifetime of its own:
  `EffectEntry::lifetimeSeconds` is `anims[0].duration / ticksPerSecond`
  (`game/effect_catalog.h`, from `FUN_0042eec0` -> `FUN_0064e8b0(model, 0) / 0.016`), and
  `FUN_00436150` drives the clip with `age * 0.016`. So every card that plays an animation has
  `ttl == animationSeconds`, and `game::cardAnimationSeconds(age, ttl, animSeconds)` reduces to
  `age`: the card plays from its spawn at the animation's own rate — the same rule
  `gameplay/projectile.cpp`'s `advancePose` already used for shot models. The function still
  scales when a caller passes a lifetime that differs from the clip, and that is now the
  guarded case: if a lifetime source ever breaks the equality, the rescale becomes a new rule
  and a non-looping card freezes on its last frame.
- `--no-fx-anim` reproduces the previous bind-pose draw for before/after comparison and
  rollback.

**Verification.**

- Tier 4 (install-backed): `animation_data_test` loads the shipped card, asserts it ships an
  animation with a positive duration, and asserts its pose differs between birth, the middle
  of its life and expiry. Freezing the clock (`return 0.0`) fails both pose checks, so the
  assertions are load-bearing.
- Tier 6 boundary check: the renderer uploads a different palette for an animated card
  (scale 1.5708 → 1.2234 across the muzzle card's life) and `--no-fx-anim` uploads no posed
  palette at all; the instance palette-offset remap matches the template (probed during
  development, probes removed).
- Tier 6 raster check: forcing a card to a fixed mid-animation pose changes the captured
  pixels (`bind=e3a47a0365` vs `mid=a03a3f70db` at the same frame), so the sampled pose does
  reach the raster, not just the palette upload. The plain on/off A/B is identical **only
  because `--out` renders one specific frame and these cards live 1-3 frames**, so it lands
  on the spawn frame where the pose is bind pose.

**What the cards actually animate** (`local-data/harness/card_anim_probe.log`, a probe that
loads a card through the same bundle reader; untracked):

| card | anim | duration | motion |
|---|---|---|---|
| `data/effect/01.X` (the empty-tap ring, texture 渦巻き) | 1 set, 20 frames | 1.333 s | the drawn mesh scales 1.0 → 1.05 → 0.99 → 1.11 and **collapses to 0.158 on Y** by the end |
| `data/aura/00.x` (muzzle starburst) | 1 set, 2 frames | **0.050 s** | scale pops 1.0 → 1.43 → 0.876 |

The muzzle card's animation and its descriptor lifetime agree exactly (0.050 s each) — not a
coincidence, but the construction above: the lifetime *is* the clip's length, which is why the
owner's answer ("use its lifetime") and the recovered rule coincide.

**The ring in the owner's screenshots is not one of these cards.** `data/effect/01.X` is never
added to the scene — no shipped descriptor names it — and V3-35 establishes that the ring is
the shot model `data/bullet/001/06.X` drawn opaque. This entry's animation fix stands on its
own (cards did draw bind pose); it was not that symptom.

**Named limits.** The hyper-mode aura attachment (the eleven attach points) still draws the
bind pose — it is fighter state, not a spawned card, and has no per-instance age; and the
per-card `Controller` is constructed per frame, which is fine at the observed card
populations (peak 1-2 in a shot-heavy run, cap 128) but not free.

**Addendum — `anims[0]` is not a choice.** Every shipped card was enumerated through the same
loader (`data/effect/*.X` and `data/aura/*.X`, 35 files): each carries **exactly one
`AnimationSet`**, and all of them report `ticksPerSecond = 4800`, the same time base the
character clips use. So selecting set 0 is not picking one animation out of several; there is
no second one to pick. Cards with a single *frame* still animate that frame's transform
(`aura/00.x` is 2 frames and scales; `effect/01.X` is 20 frames and 11 meshes), which is why
the animation is a palette matrix even for the smallest card.

### V3-35 — the ring is a BULLET model drawn opaque; V3-33 named the wrong asset

Correction to V3-33, found by an independent audit and confirmed by rendering: the ring in
the owner's screenshots is **not** an effect card. `data/effect/01.X` — the file V3-33 named
— is never added to the scene: no shipped effect descriptor names it (the 22 descriptors name
14.X, 12.X, hit02.X, 05.X, g01.X, 06.X, 07.X, 13.X, 09.X, 10.X, 08.X, 15.X, 16.X, 17.X,
19.X, 20.X, 21.X), so only `--effect=<file>` can show it. The V3-34 animation work is still a
real fix (cards did draw bind pose), but it was not this symptom.

The ring is **`data/bullet/001/06.X`** — weapon slot 001's shot model — and the defect is the
**pass**, not the animation. Rendering that one file two ways proves it: with the model role
(opaque) it is a black quad with rings on it, exactly the port's picture; with the effect role
(additive) it is the glowing ring of the original's picture.

`FUN_005f60b0` is why. It switches on the shot record's `+0x7c` (`:77`) and **every** case
enables alpha blending: 1 sets `ALPHABLENDENABLE` (`:79`), 3 sets it with the technique-8
state and an optional colour (`:91-:99`), 2 and 4 set it with `DESTBLEND = ZERO` and Z off
(`:84-:89`), and the `default` case the shipped shots actually take (`:136-:143`) changes no
state and only picks a technique. Nothing draws a shot surface opaque — the port did, for
every `+0x7c` outside 2/4, and the shipped value is **0** (`combat[19] == 0` on live shots,
probed). That black plate is the symptom.

Fix: a projectile instance now always uses `Pass::Effect`, with `+0x7c` 3/4 still selecting
the unlit technique. Rendered in-game at the same frame, the ring glows additively over the
ground instead of sitting on a black quad.

**Open:** the object at the ring's centre is now over-bright (white) where the original shows
it dark, so the per-record distinction is not simply "all shots additive". `+0x7c` is 0 for
every shot this weapon fires (probed on live shots), so the difference for that object must
come from another field — the candidates are the bullet parameter's own state or the ambient
state the original's `default` case inherits. Until that is settled the Z-off half of cases
2/4 is also unmodelled: the effect pass keeps the depth test and drops only the depth write.

### V3-36 — a shot model holds BOTH the weapon and its glow: the pass is per MESH

The owner's follow-up killed the blanket fix in V3-35: "the effect is correct but now the mesh is
not there — the nata is being thrown, and now there is only the effect."

The reason is the model, not the state. `data/bullet/001/03.X` — the thrown nata — is **one
model with three meshes**:

| mesh | verts | texture | what it is |
|---|---|---|---|
| 0 | 67 | `鉈02` ("nata 02") | the thrown blade |
| 1, 2 | 4 each | `鉈回転エフェクト` ("nata rotation effect") | the glow cards around it |

Drawing the whole model additively made the blade wash out; drawing it opaque put the quads'
black background over the ground. Both are the same file, so no per-model pass can satisfy it.

The glow texture explains why blending is the only lever: `data/bullet/001/鉈回転エフェクト.cnv`
is **alpha 255 on every texel** (measured: min = max = 255), so alpha test cannot cut the black
field and normal alpha blending would paint it. Only additive lets black contribute nothing.

Implemented as a per-mesh split: a mesh that is exactly one quad (4 vertices, 6 indices) inside a
shot model is drawn with the effect pass; everything else keeps the record's own mapping
(`+0x7c` 2/4 additive, 3/4 unlit). This is a **PORT RULE** and it is labelled as one: no recovered
per-mesh blend signal exists — the two meshes' materials differ only in `Power` (32 on the quads,
0 on the blade) with `Specular` zero on both, which is not a blend control. It is the same kind of
geometric routing `setScene` already uses for the billboard verdict, and the survey supports it:
across weapon 001's shot models the weapon is a 67-68 vertex mesh and every glow is a 4-vertex
quad (`06.X` is a lone quad — the pure ring).

Rendered at the same frame: the nata is solid and lit and the ring glows over the ground with no
black plate. Suite 83/83 excluding the known `device_isolation_test` flake; fixture matrix
unchanged at 29/30/47.

**Open:** the geometric split is a rule, not a recovered fact — a quad that is NOT a glow card
would be drawn additively (none found in weapon 001's models, not yet swept across all 46
weapons), and the Z-off half of `+0x7c` cases 2/4 remains unmodelled.

### V3-37 — the Hyper EX attack (row 350) plays its action camera, whiff or not

Owner report, with an original-runtime screenshot: in Hyper mode the Special press fires the
single EX attack (row 350), and that move plays the cinematic camera **whether or not it
connects** — unlike the melee chain, where the camera is a hit effect.

The port never played it. Measured, not assumed: row 350's recovered program had **29 ops and
zero `ActionCamera` ops**, so `action_camera()` stayed 0 for the whole move (probed with the
opponent 2000 units away, so every swing whiffed). Nothing was suppressing it — the op was
missing.

Two things were needed:

- **The rule.** `{350, -1, 0, 9999, MoveOp::ActionCamera, 2.f, 1.f}` — the whole move, firing
  once. `FUN_0043ffc0` case `0x15e` has no contact test around its request, which is why the
  owner sees it on a whiff.
- **An ungated arm.** The executor gated every camera on `m_chainContact`, the latch
  `note_melee_hit` sets. That gate is right for the chain (a whiffed swing must not play it —
  asserted) and wrong for this move, so `MoveRule::second` now means "plays regardless of
  contact" for `ActionCamera` only. The field was unused for this op.

**The clip index is 0, and it is recovered — the earlier tier-3 answer of 5 was wrong.**
`FUN_0043ffc0` case `0x15e` writes the actor's camera-request word **`+0x684`** itself
(`:1437-1442`: `if (param_1[0x3a] == 0) param_1[0x1a1] = 0; else param_1[0x1a1] = 1;`, and
`0x1a1 * 4 = 0x684`; disassembly at `0x443692` / `0x4436a1`, branch on `[eax+0xe8]` at
`0x443686`). That word is the rig's animation-set index: `FUN_006358c0:59-64` tests it for
`< 0` (clear the action camera) and otherwise passes it to `FUN_00633140`, which stores it at
`camera+0x7c` and reads the set period; `FUN_006333b0:83-85` then binds both controller
tracks to it. The rig is `data/camera/01.x`, and the port already reverses its sets the same
way the reference bundle documents, so port index == native index.

So the move requests **set 0 for the whole move** — that is the cinematic the owner sees on a
whiff — and **set 1 from tick `0x33`** only when the late hit latch `+0xe8` is set (armed at
frame `0x32` by `FUN_0042c7b0() & 1`, which ORs the per-slot hit flags the body clears every
tick while the frame is below `0x24`). **No instruction in row 350 writes 5**; the only
`mov [reg+0x684],5` stores in the image belong to another character's state machine.

**Why the owner's pick looked right, and what it exposed.** The port's `ArenaCamera::set_action`
used **0 as its "off" sentinel** (`if (clip > 0)`), so the recovered set 0 was unrepresentable —
the sweep's "set 0" panel was the ordinary camera, native `Anim-6` was never shown, and 5 was
the closest visible framing. That mismatch is now fixed: the sentinel is negative (matching
`+0x684 < 0`), 0 is a real set, and `fighter.cpp`'s four reset sites and the member initialiser
carry `-1`. With set 0 played, the port frames the move close and frontal at the owner's own
height — the same angle as the print — where set 5 was wide and from the wrong side.

PORT RULE that remains: the late switch to set 1 is gated on the port's `m_chainContact`, which
records a hit anywhere in the move, while the original only survives a hit landing in ticks
`0x24..0x32` (it clears the per-slot flags every tick before that). So the port can switch to
set 1 slightly earlier than the original, and never for a hit that landed before tick `0x24`.


Regression, two layers. `rena0_pilot_gate_test` Case G drives the whole sequence — a whiffed
melee swing must leave the camera at **-1**, Hyper activation must not arm it, and the EX press
must put **set 0** on for the move with the opponent out of reach; deleting the rule fails it.
`rena0-hyper-ex-camera.fixture` pins the same path at fixture level, so the acceptance matrix
carries it: `action_camera -1` before the press, `0` on the press tick, `0` while the swing
hangs, with `swing_hits 0` proving nothing connected. Suite 83/83 excluding the known
`device_isolation_test` flake; fixtures 30 / 31 case rows / 49 fields.

### V3-38 — the glow-quad rule, measured across the whole shot corpus

V3-36 split a shot model's pass per mesh: a mesh that is exactly one quad is drawn additively,
everything else keeps the record's `+0x7c` mapping. That was derived from weapon 001 alone, so
it was labelled a port rule. It has now been swept against **every** shipped shot model.

**The corpus** (all `data/bullet/**/*.X`, loaded through the port's own reader):

| | |
|---|---|
| models / meshes | 351 / 515 (0 load failures) |
| quad meshes (4 vertices, 6 indices) | **155**, in 128 models |
| models whose only geometry is a quad | 85 (for example `001/06.X`, the pure ring) |
| distinct quad textures | 19 — flames, flashes, rings, shockwaves, sparks, bubbles, smoke, energy balls |
| models a bullet record names | 116 of the 128 |

**No counter-example exists.** Every quad in the corpus is planar, axis-aligned, unskinned,
one submesh, one material, UV `(0,0)..(1,1)`; 18 of its 19 textures store alpha 255 everywhere
(only `毒泡` has real alpha), and all have 19–84% exact-black texels with a 37–100% black
border — which is why additive is the only blend that hides their backing. The contrast set is
as clean as it gets: the 132 models whose materials are all full-coverage textures contain
**zero** quad meshes. No quad is a solid blade, leaf, shield or opaque billboard, and in the
nine models that mix a card with an object the object is always real geometry (nata 67v,
zippo 68v, rulers 64v/132v, saw 111v) — including `030/03.X`, where the card is mesh 0 and the
weapon mesh 1, so mesh order is not a signal and the rule does not use it.

**What the rule actually changes** is much smaller than the corpus suggests: 125 of the 155
quads sit in models whose every record row is already additive (mode 2/4), so the rule only
flips **17 quads in 10 models** (`001/03`, `001/05`, `001/09`, `003/17`, `014/03`, `025/03`,
`027/03`, `029/09`, `030/03`, `041/01`). Sixteen of those are also saved by the projectile
black-key; `027/03.X` is the one where the quad rule is doing work nothing else does.

**It is under-inclusive, not wrong.** Black-backed glow meshes that are *not* quads — 12v/18i
muzzle-flash and explosion-ring cards, the 158v/672i nata beam, a 60v/324i beam-saber — stay on
the record's own mapping, some of them in modes 0/1, where they would show their black plate.
That is the remaining gap, and it is not fixed here.

Regression: `effect_catalog_test` now sweeps the install and asserts the shape the rule
assumes — no quad in a shot model is skinned, none carries several submeshes, all are planar —
so an asset that breaks the premise fails instead of silently rendering wrong. It reports the
survey (351 models, 155 quads) on every run.

### V3-39 — the depthless half of `+0x7c` cases 2 and 4

`FUN_005f60b0` switches render state on the shot record's `+0x7c`, and two of its cases do more
than pick a blend: case 2 (`:84-89`) and case 4 (`:100-109`) save the current DESTBLEND, set
`ZENABLE = 0`, draw, then restore `ZENABLE = 1`. So those shots are drawn with **no depth test
at all** — over everything the frame has drawn so far, including the stage — while the port kept
the effect pass's depth test and only dropped the depth write.

That is now modelled as a fifth pass, `Pass::EffectNoDepth`: same additive blend as the effect
pass, `depthCompare = Always`, sorted after every other pass so it cannot be occluded. Which
shots take it is the record's own word — `+0x7c` 2 or 4 — so the port needs no new rule: the
mapping the port already had (2/4 -> additive) just carries its second half.

The glow-quad rule from V3-36 is unchanged and stays depth-tested: a quad in a mode 0/1 model
draws additively but is still occluded by the stage, which matches the original, where Z is only
turned off inside cases 2/4.

Suite 83/83 excluding the known `device_isolation_test` flake; a match frame still draws its
four effect cards and the pipeline count grows by the one new pass.

### V3-40 — what row 390 (guard) really does, and why it is still not implemented

The named limit "guard row 390's release section is unreached" now has a full recovered answer.
It is recorded here because implementing it is **not** a local change, and the attempt made on
2026-10-29 was reverted.

**The framing that was wrong.** `FUN_00421100` is the *phase* setter and `FUN_00421080` the
*state* setter, so `FUN_00421100(2)` in case `0x186` (`:1669`, asm `0x443ffd-0x444007`) enters
row 390's **third section** — set 63 — and **keeps the state**. The release is a phase, not a
state exit; "releasing leaves Guard" is the port's shortcut, and the contract's earlier line
`:1964-1965` drew that conclusion from the right addresses.

**The row.** Row 390 is `priority 0`, `cancelThreshold 150`, sections set **60** (prep, gate 0,
transition 10), **61** (hold, gate 1), **63** (release, gate 0). Only the hold section's record
carries `stateFlags 0x400`.

**The exits, exactly** (`:1639-1689`):
| id | condition | target |
|---|---|---|
| E1 | row complete **and** airborne | state `0x2b` (43), `+0x58 = 0.5` |
| E2 | row complete **and** grounded | state `0` (idle) |
| E3 | airborne, row not complete | state `0x2b` (43) |
| E4 | `phase == 1 && (meter == 0 \|\| jump-held == 0 \|\| melee-held == 0)`, tested **after** the −10 drain | `FUN_00421100(2)`: **same state**, phase 2 / set 63 |
| E5 | `(FUN_0042c7b0() & 2) != 0 && meter > 0` | state `0x187` (391), effect `0x46`, SE `0x33` |
| E6 | `phase == 2` | no exit; turn step 0, speed −1/tick |

The drain belongs to phase 1 only (`:1655-1657`), so prep and release cost no meter — the port
drains on every Guard tick, which shorts the stance by the whole preparation window.

**Why the implementation was reverted.** The recovered model keeps the actor in state `0x186`
through the release clip, and the port has no cancellation rule for that window: five suites
encode the current behaviour ("release permits next action immediately"), and the original's
admission gate that would let an attack cancel out of the stance (`cancelThreshold 150` against
each row's priority) is not established here. Shipping the release phase without it turned a
validated guard into a 20-tick lock-out. So the finding is recorded and the behaviour is
unchanged: the port's flat Guard stays, and the release section remains a named limit — now a
*precisely specified* one, with the phase, the clip, the drain window and the five exits above.

**A separate, uncontroversial half was kept:** nothing. The sentinel and camera work in V3-37
are unrelated and stand on their own.

### V3-41 — the camera's ally branch is unreachable in a 1v1, and `+0x304` is not a combat lock

Two camera notes in this contract were carried as open limits. Both are now settled, one of them
by deletion.

**`[cam+0x78]`** is a `float` distance of exactly **300.0** (`0x43960000`), written once by the
camera's default-init `FUN_00632e10` @`0x632e1a` (reached from the per-camera constructor
`FUN_00632c30` and the reset loop `FUN_00634760`), and read twice: as the follow-boom numerator
(`FUN_006333b0` @`0x63374b`, `300 / |V|` clamped to 1.5) and as the stage-obstruction ray's range
(`FUN_00633930` @`0x6339ef`, compared against the ray hit before copying the frame name). No other
writer exists in the corpus. The port already hardcodes it as `kViewDistance`. The "still open"
wording elsewhere in this file is superseded.

**The ally anchor branch (`+0x304 >= 0`) is not a pilot gap and needs no implementation.**
`FUN_006358c0` takes it when the actor's `+0x304` — an index into the **same-team** pointer vector
at `actor+0x2f0` — is non-negative (`:46-58`, asm `0x635ab9` `jl`), and when it does it looks at
**element 0** of that vector, not at the stored index. `FUN_00634980` builds the two vectors by
comparing each pair's team record (`scene+0x12ac` for slots 0/1, `scene+0x12b8` for slots 2/3):
same team → `FUN_00421730` pushes onto `+0x2f0`, different team → `FUN_00421670` pushes onto
`+0x2e0`. So in a two-fighter match on different teams the ally vector is empty, the only
non-negative writer (`FUN_00421f30`, bounds-checked against that vector) never fires, `+0x304`
stays `-1`, and the branch cannot be reached. The same branch exists in the second camera updater
`FUN_0063dad0` with the same condition.

**The two selection offsets, settled from the disassembly (2026-10-29).** The port's notes call
`+0x304` "the locked combat target"; the two containers say otherwise, and the instructions are
unambiguous:

| evidence | what it shows |
|---|---|
| `0x634b75-0x634b96` (`FUN_00634980`, the reset that also builds the cameras) | it compares the two fighters' team records (`[[actor+0xc]]`): **equal** teams → `call 0x421730`, which does `add ecx,0x2f0` — the same-team list |
| `0x634b9d-0x634bb8` | **different** teams → `call 0x421670`, which does `add ecx,0x2e0` — the other-team list |
| `FUN_00421f30` @ `0x421f40` and `0x421f7f` | it bounds-checks and indexes **`+0x2f0`**, then stores the index into `+0x304` |
| `FUN_00421e30` @ `0x421e5d` and `0x421e7d` | it indexes **`+0x2e0`** and stores into `+0x300` |
| `FUN_006358c0` @ `0x635ab9` | the camera's `+0x304 >= 0` branch looks at element 0 of `+0x2f0` |

So **`+0x300` indexes the opponent (other-team) list and `+0x304` the ally (same-team) one**; the
port's `TargetLock::target` — the fighter a fighter attacks and faces — is the `+0x300`
selection, and `FUN_00421f30` is the *ally* writer, not the combat lock's. That is also why the
camera branch is dead in a different-team 1v1 (V3-41 above).

The relabel itself was **reverted**: `target_lock.h` carries six paragraphs of recovered notes
built on the old naming, and rewriting one field's comment while those stay would leave the file
contradicting itself worse than a consistently-wrong label does. `target_lock.h` now records both
readings where the field is declared, and this table is the authority until the file's notes are
rewritten as a whole.

### V3-42 — an air dash that ends airborne falls in state 43, not in the jump chain

The air dash's after-state was a named limit ("completes into the port's Jump, which re-arms the
row-41 hover"). The recovered answer is sharper than the limit, and half of it is now implemented.

**State 43 is a real row.** `FUN_0043ffc0` case `0x1e` completes with `FUN_00421080(0x2b)`
(`:379-381`), the *state* setter, so the fighter enters state 43 — move **43**, whose single
section's tag is **43**, i.e. animation set **43** (800 ticks = 10 frames, gate **1**). The port
reached set 43 eventually, but through the jump chain's falling row 42, whose *first* section is
set **5** (2480 ticks = 32 frames); so after a dash the port played 32 frames of set 5 before set
43 appeared.

**Implemented:** a `m_dashFall` flag set when an air dash completes still airborne, which makes
`jump_chain_move()` return move 43 (and suppresses the row-41 hover, which state 43 does not
have). The air-dash fixture now pins it: `anim_set 43` on the first post-dash update, where the
port previously bound **5**. Removing the binding fails it with `tick 33 anim_set exp 43 got 5`.

**Scope, stated plainly:** this reaches the *programmed* dash — the one whose row 30 advances
through its own sections (`try_dash` marks it phase-driven, which on Rena+0's air row needs the
pilot meter). The default path still ends its dash on the port's `kDashFrames` timer, which the
original does not have; its fall stays on the jump chain and does **not** claim row 43, because
the recovered completion only exists where the sections do.

**Still missing, and specified rather than vague:**

- **State 44, the shared landing row.** `FUN_0043ffc0`'s `if (iVar5 == 0x2c)` body (`:54-81`) is
  move **44** → set **44** (1760 ticks = 22 frames, gate 0): it zeroes speed, movement angle and
  turn, adds 40 (or 5 while status slot 6 is set) to the meter with a 1000 cap, and leaves when
  `FUN_004218c0()` fires — 21 updates of body, the 22nd leaving into state 0. It is shared by
  every air state that touches down (the port's own respawn note at `fighter.cpp:830-831` records
  that move `0xc2` also lands into `0x2c`). The port lands straight into Idle and binds set 0, so
  the landing clip and its ~0.367 s are absent. The observable is exact (`anim_set 44` held 22
  updates) but implementing it means giving `Idle` a landing window, which changes the meter
  refill's start and every `state_enum 0` expectation — a change of its own, not a pin.
- **The turn write.** State 43 writes `+0x874 = 1.0` every update (`:537`) and then steers `+0x64`
  toward the held 8-way bearing (`FUN_00421780`); the port hardcodes 1°/tick only inside the
  carry path, so the steering exists but the field does not.
- **No hover, edge case.** The hover is suppressed in the fall, but the observation window after a
  dash is short enough that no fixture could see the difference (the only honest test would land
  before the climb showed), so this half is specified and untested rather than pinned.

### V3-42 (continued) — the landing row is implemented

State 44's row now plays. It was specified in the entry above and is in place:

- `landing_row_frames()` reads the length from the row itself — move 44's first section set,
  through the shared `animation_period_frames` truncation — so a combo whose landing clip differs
  gets its own number instead of a constant (Rena+0: 1760/4800/0.016 → **22** frames).
- The window opens on the touchdown that lands from `Jump` or from an air dash, and Idle's row
  resolver returns move 44 while it is open.
- It closes by clearing the bound set **and the row clock** before re-resolving. Two things were
  wrong first: `try_switch_animation` returns early while a set is bound (which keeps a state's
  clip stable, and is why the window stuck on set 44), and leaving the clock alone made the
  standing clip start at row 44's last tick (~frame 22) on every landing — the port's own
  `refresh_state_move` and `set_state` both zero that clock for exactly this reason.
- The differential comparator had to learn the same thing: the tick that closes the window is a
  transition in which the state setter restarts the clock, so it is compared as one instead of
  being measured against a row that has already ended.
- The meter is untouched: row 44 refills +40 (or +5 with status slot 6) per update and the port's
  Idle adds the same, so the window is animation-only and no meter expectation moved.

**Pinned:** `rena0-air-dash-left.fixture` — `anim_set 44` at the landing updates and `anim_set 0`
once the window closes; removing the row fails it with `tick 40 anim_set exp 44 got 0`.

**A real port-loop finding came out of it:** the differential comparison treats "Idle" as the
locomotion row, so a fighter playing row 44 inside Idle read as a binding mismatch on 27 ticks.
The adapter now *compares* those ticks — the bound set must be row 44's first section — and it
also models the row's completion, because the tick that closes the window is a transition in
which the state setter restarts the clock. Excluding them would have hidden a checkable quantity
and left the port's own clock reset looking like a one-tick regression.

Still not carried: the row's frame-10 `flags 0x100` record, so the port can still cancel out of
the landing on its first tick. The row's zeroing writes (speed, movement angle, turn, vertical)
have no port field to land in, and state 43's turn write stays unmodelled for the same reason.
