# PILOT-SEAM — the Rena+0 pilot's seam spec (P2-1, increment 1: locomotion)

**Status: in progress.** P2-1 increment 1 (locomotion seam) and P2-4 increment 1
(actor-context mapping for those fields: §7-§9) are recorded; the attack/shot/guard/hit/KO
bodies are increment 2 and are still uncounted. This is P2-1's first increment: the seam of the body the
F1-5 experiment selected — the recovered **slot-6 State0/State10 locomotion control**
for Rena+0 — quantified field by field. The pilot's attack, shot, guard, hit and KO
bodies are **not counted yet**; increment 2 must finish them before P2-1 can answer
`DIRECTION.md` §4 2a's Option A/B trigger. Nothing here is an integration: the
resolver is P2-6 and it waits on the P2-0a/P2-0b gates.

Sources: the bundle's `roster_locomotion_native_control.hpp` + `battle_roster_walk.hpp`,
`battle_walk_motion.hpp`, `battle_steering.hpp`; the addressed decompilation
`research/decompiled/FUN_0043ffc0.c` (cases 0/10 at :84-179, common tail :2439-2447);
the port's own `Fighter`/`Match`; and the observation-only projection in
`src/gameplay/native/rena0_locomotion_observation.h`.

## 1. Fields the selected body reads or writes

Ownership column: `product` = an existing product field can supply it; `partial` = a
product field exists but with different semantics or domain; `unmapped` = no product
field, supplied only as an explicit fixture/scenario input (§4).

| Actor | Meaning | Port owner today | Ownership |
|---|---|---|---|
| `+0xadec` | numeric action state (0 idle, 10 walk, …) | `Fighter::action_state()` | product |
| `+0xadf4` | move phase/section | `Fighter::move_phase()` | product |
| `+0xae04` | per-phase frame clock | `Fighter::phase_elapsed()` | partial (port resets at section bind, body resets on transition) |
| `+0xae08` | second clock (paired with `+0xae04`) | none — probe used the move counter as a labelled proxy | **unmapped** |
| `+0xade4` + `+0x20` | phase duration and hold/gate | move table phase + `animation_set_phase_gate()`, rig set duration | partial (duration derived from the rig, not the original's pointer chain) |
| `+0x278` / `+0x27c` | stick words — **sign only** | `PlayerState::down[]` / `stick_x,stick_y` | product |
| `+0x84` | grounded flag | `!Fighter::airborne()` | product |
| `+0xa0` | blocking word (any nonzero blocks the update) | none | **unmapped** |
| `+0x7f4` | status gate selecting the +5 refill over +40 | none (`Fighter::hit_status_duration(6)` is the nearest) | **unmapped** |
| `+0x54` | horizontal speed (u/tick) | `Fighter::move_speed()` | partial (attack-body channel vs walk displacement) |
| `+0x40` | vertical speed | `m_vy` (private) | partial |
| `+0x58` | gravity | `FighterConstants::kGravity` | partial |
| `+0x60` | movement channel (zeroed by the walk) | none | **unmapped** |
| `+0x64` | heading offset, degrees, ±180 | none — the port steers `facing_yaw` (radians, absolute) | **unmapped** (angle ownership differs) |
| `+0x874` | turn step (reset 20, decay 1, floor 1) | `m_walkTurnRate` | partial (same numbers, different storage/lifetime) |
| `+0x834` | battle gauge 0..1000, +40 clear / +5 slow, clamp 1000 | none directly (probe used `stamina × 10` as a labelled proxy) | **unmapped** |
| `+0xe8` | direction-category latch (0..7, 10 = none) | none | **unmapped** |

Counted: **17 fields — 4 product, 6 partial, 7 unmapped.**

## 2. Services the body invokes

| Service | What it does | Pilot treatment |
|---|---|---|
| `0x4212f0` | frame cursor / phase-asset advance | **legacy owns** (the probe deliberately does not call it) |
| `0x421080` / `0x421100` | bind move/phase and re-bind the animation set | **legacy owns** (`Fighter::set_state`, `try_switch_animation`) |
| `0x421780` (via `0x42db10`) | eight-direction steering toward the offset target | arithmetic reproduced in the probe; the caller still owns the angle |
| the state dispatcher (`FUN_0043ffc0`'s caller, `FUN_00634f60`) | per-fighter update order | **legacy owns** (`Match::step`) |

Counted: **4 services — 3 left with the legacy path, 1 reproduced (arithmetic only).**

## 3. Effects the body returns

Proposed `state`, `phase`, `frame`, `secondary`, `next_state`, `next_phase` and a
`tail` flag (whether the common `+0xae04/+0xae08` tail ran). The probe returns them
without applying any.

## 4. No silent zeroes

The seven unmapped fields are not zeroed and not invented. Each is either an explicit
fixture/scenario input with a recorded assumption (`stop`, `slow`, `secondary` proxy,
`gauge` proxy, angle seeds) or a named dependency that blocks authoritative use
(`+0x60` movement, `+0x64` offset ownership, `+0xe8` category storage, `+0x7f4`
status). `DIRECTION.md` §4 2b (P2-4) turns this table into per-field provenance with
update order and previous-input semantics.

## 5. Glue estimate (locomotion only)

Measured, not guessed: the observation-only projection is **291 lines including
comments** (`src/gameplay/native/rena0_locomotion_observation.h`), of which ~150 are
code; the F1-5 mapping from product fields happens in ~20 lines of test code; the
steering helpers are ~40 lines. On that basis the locomotion seam is a **small
adapter over scalars** and does not require the reference actor/services layer.

**Option A/B trigger (`DIRECTION.md` §4 2a): not yet answerable.** Locomotion alone
needs no reference machinery, which favours Option A, but the pilot's attack/shot/
guard/hit/KO bodies are uncounted, and those are where the reference's services
(RNG draw order, targeting, hit/contact, projectile lifecycle) would appear. P2-1
stays open until increment 2 counts them; if they require most of the reference
actor/services, the row's instruction is to stop and present Option B.

## 6. Known gaps carried into the seam

From the F1-2 inventory (contract §5 item 3), the pilot cases still lack observables
for: per-shot identity and lifecycle, attacker-side contact records, the applied
hitstun length, per-channel animation clocks and blend state, landing/takeoff/apex
events, a per-fighter tick index, per-shot spawn source, and per-slot hit-status
power. `Match` also exposes no RNG seeding (P2-2), so a fixture cannot inject a seed.

## 7. Update order (P2-4)

Confirmed reading order in the production path:

1. `Match::step` — paused check; `m_economy.tick(dt)` (`match.cpp:168`).
2. `m_locks.step(aliveAtStart)` with liveness as of the tick's start (`match.cpp:176`).
3. Per fighter, in panel order (`match.cpp:190`): the aim/lock target is resolved, then
   the `ShootingContext` is published (RNG pointer, COM lateral word, the three voice
   latches computed from the *previous* tick's state), and only then
   `m_fighters[i].update(inputs[i], …)` (`match.cpp:203-233`).
4. `Fighter::update` — hypermode/overlay/flash maintenance, then **1** state-timer
   decrement (`fighter.cpp:432`), **2** state machine and input admission
   (`:462`), **3** movement (`:547`), **5** stamina (`:583`), **5b** vertical motion
   (`:601`), then the animation binding for the resulting state.
5. Post-fighter passes: projectiles/contact and economy credits (`match.cpp:261,283`).

A recovered locomotion body belongs at step 3-4's boundary: it reads the previous
tick's clocks and this tick's input, and proposes `state/phase/frame/secondary`. The
F1-5 observer deliberately runs it on a **pre-update** snapshot, so its output can
never feed back into the same tick.

## 8. Previous-input semantics (P2-4)

`input::compute_edges` runs once per tick, after device reads or a script override,
and defines the edge contract the bodies and the port share (`input.h:60-70`):
`just_pressed = down && !prev_down`, `just_released = !down && prev_down`,
`prev_down` copied afterwards, and a **2-tick `press_timer`** armed on each press. A
fixture or scripted run therefore derives edges exactly like a live poll, which is
why the F1-3 fixtures reuse `parse_script_line` rather than synthesising edges. Each
fighter owns its own `PlayerState`; `Match::step` hands the same object to the fighter
it belongs to. The locomotion body reads only the **signs** of the stick words
(`+0x278`/`+0x27c`), and the port supplies them from `down[]` or `stick_x/stick_y`
with the documented up-is-`-Y` convention.

## 9. Per-field provenance mapping (P2-4 increment 1)

Disposition of each field from §1: `existing` = an existing product field supplies it
(translations noted), `accessor` = the data exists but is private and needs a read
path, `new` = a justified new field the resolver would own, `unresolved` = a named
dependency that blocks authoritative use of that channel. **No field is silently
zeroed.**

| Actor | Disposition | Detail / justification |
|---|---|---|
| `+0xadec` state | existing | `action_state()`; the caller translates Idle→0, Walk→10 (others rejected) |
| `+0xadf4` phase | existing | `move_phase()`; the original advances it through `FUN_00421100`, the port through its move rows |
| `+0xae04` frame | existing | `phase_elapsed()`; the body resets it on transition, the port on section bind — the F1-5 probe records the divergence rather than hiding it |
| `+0xae08` secondary | **unresolved** (candidate `new`) | no product twin; the probe's move-counter use is a labelled proxy. Decide: a resolver-owned paired clock, or the animation controller's own clock |
| `+0xade4` duration/gate | existing | rig set duration rounded through the original 0.016 s unit + `animation_set_phase_gate()`; the original reads a pointer chain, so the derivation is a documented approximation |
| `+0x278`/`+0x27c` x,z | existing | `PlayerState::down[]`/`stick_x,stick_y`; sign only |
| `+0x84` grounded | existing | `!airborne()` |
| `+0xa0` stop | **unresolved** | no product equivalent and the word's other meanings are unknown; must stay an explicit scenario input |
| `+0x7f4` slow | **unresolved** | `hit_status_duration(6)` is nearest but not the same gate; blocks the +5 refill branch |
| `+0x54` speed | accessor | `move_speed()` is the attack-body channel (u/tick); walk displacement currently lives only inside `update_movement`, so a read path is needed |
| `+0x40` vertical | accessor | `m_vy` is private; a read path is needed if the resolver drives vertical motion |
| `+0x58` gravity | existing | `FighterConstants::kGravity` |
| `+0x60` movement | **unresolved** | semantics not recovered; zeroed by the walk body, no product twin |
| `+0x64` offset | **unresolved** | angle ownership differs: the port steers an absolute `facing_yaw` in radians, the original a degrees offset in ±180. Someone must own the angle |
| `+0x874` turn | accessor | `m_walkTurnRate` carries the same reset/decay/floor numbers but a different lifetime |
| `+0x834` gauge | **unresolved** | battle gauge 0..1000 with +40/+5 refill has no product twin; `stamina × 10` was a labelled proxy only. Blocks authoritative refill |
| `+0xe8` category | **new** | small latch (0..7, 10 = none) with no product storage; a resolver-owned field, unless the original site is recovered first |

Counted: **7 existing, 3 accessor, 1 justified-new, 6 unresolved** (the `+0xae08`
candidate keeps its unresolved mark until decided). Service ownership is §2: the
legacy path keeps the frame cursor, the bind/phase service and the dispatcher; the
resolver would own only the steering arithmetic and the proposal values.

## 10. Increment 2, first cut: the Rena-specific bodies (shot and melee admission)

The bundle carries **13 Rena-named bodies** (~950 lines total): `battle_rena_ground_shot`
(82), `battle_rena_mobile_shooting` (246), `battle_rena_full_charge` (173),
`rena_projectile_switches` (96), `battle_rena_ground_dash` (65),
`battle_rena_directional_melee` (53), `battle_rena_melee` (53),
`battle_rena_ordinary_melee` (53), `battle_rena_landing_melee` (37),
`battle_rena_followup_melee` (36), `battle_rena_melee_admission` (34),
`rena_dash` (22), `battle_rena_ground_melee` (15). Two of them read directly:

**`battle_rena_ground_shot.hpp` — State 400 for all three Rena weapons.** Its seam is
scalars plus *ordered events*, not an object graph:

| Aspect | Finding |
|---|---|
| Input | `complete`, `grounded`, `special`, `rounds`, `elevation`, `heading`, `position[3]` (`:17`) |
| Motion state | `phase`, `frame`, `pitch`, `speed`, `offset`, `movement`, `gravity` (`:16`) |
| Output | `next_state` plus an ordered `std::vector<RenaShotEvent>` (`:18`) |
| Event kinds | `activate, melee_statistics, shot_statistics, model, sound, voice, attachment_projectile, world_projectile, clear_contact, contact_capacity, strike` (`:9`) |
| Services it calls | `approach_battle_offset`/`..._preserving_movement` (steering), `BattleRandom::next()`, `legacy_trig` (`:38-72`) |
| Host responsibilities | the file states them: actual magazine admission and resource/attachment resolution happen at each projectile request (`:22-23`), voice resolution at the ordered call (`:12-14`) |
| Combo variation | one function with `weapon==0/1/2` branches (`:36-76`), **not** a 46-way dispatch |

**`battle_rena_melee_admission.hpp` — the 300-family selector.** Pure scalars in
(`weapon, state, phase, grounded, held, released, x, z, flags, priority, special, ready,
contact`) out (a move id such as 331/330/332/320, or -1), gated by a caller-supplied
`Priority first(next)` predicate; the comment records that the DAT supplies each target
state's limit (`:5-7`).

**Dependencies verified:** `battle_random.hpp` is the same recovered MT19937 the port
already carries (`1812433253u*(…)` init, re-seed **5489** at `index==625`) — so P2-2's
"port already has the RNG" is confirmed for the shot bodies, with draw order still the
thing that matters. `legacy_trig.hpp` is the orientation helper the port mirrors with
`glm::sin/cos` in its own convention.

**Corrected false positive:** an earlier grep flagged "world/registry/manager" machinery
in the shot bodies; that match was the `world_projectile` *event kind* (`:9,:72`), not a
world object. No actor registry, projectile manager or asset loader is referenced.

**Provisional Option A/B judgement for these two families: Option A.** They need scalars,
the recovered RNG, a trig helper, steering arithmetic, a data-supplied limit/priority
callback and an event sink — not the reference actor/services core. The real seam cost
sits on the **host side**: magazine admission, contact capacity, attachment and world
projectile spawning, and voice ordering are the adapter's work, and those are exactly the
Phase 2 services the pilot must supply.

**Still uncounted (increment 2 remainder):** guard, hit/KO/downed reactions,
jump/air-dash/landing, the charge and mobile-shooting bodies' per-frame services, and
`rena_projectile_switches`. A parallel enumerator was despatched for the wider sweep and
had not reported when this section was written; its findings will be reconciled here by
spot-checking claims against the files rather than accepted wholesale.

## 11. Increment 2 remainder: the other families, and the Option A/B split

Bounded enumeration (names and line counts; the two large generated families noted as
such). Files live under the bundle's `source/src/`.

| Family | Bodies | Size | Seam character |
|---|---|---|---|
| Guard | `guard_native_control` (59), `battle_guard_motion` (36), `battle_hit_guard` (20) | 115 lines | scalars + motion, same shape as locomotion |
| Hit / damage / KO | ~14 shared bodies, e.g. `battle_common_hit_motion` (193), `battle_damage_pipeline` (36), `battle_damage_scaling` (33), `battle_damage_outcome` (30), `battle_hit_*` (11-18) | ~400 lines | damage pipeline over scalars; outcome/cancellation tables |
| Jump / landing / air dash | `battle_jump_motion` (74), `jump_native_control` (47), `air_melee_native_control` (42), `battle_roster_air_dash` (55), `battle_air_dash` (18), `roster_air_dash_cancels` (25), `battle_air_hit_landing` (13) | ~300 lines | scalars + motion; the **generated** `jump_native_bodies_20260929.hpp` is 19,727 lines of tables |
| Air shot | `roster_air_shot_schedule` (1,401), `roster_air_shot_round_schedule` (1,442), `roster_air_shot_visit_round_schedule` (488), `roster_air_shot_motion_schedule` (260) | 3,591 lines | generated per-round **schedule tables** — data, not logic |
| Charge | `battle_rena_full_charge` (173), `full_charge_native_control`, `full_charge_native_bodies_20260929`, `full_charge_aim` | — | **needs `BattleWorld`** (see below) |

**The finding that matters for `DIRECTION.md` §4 2a.** `full_charge_native_world.inc.hpp`
does not merely mention a world — it reads one:

```
void record_native_full_charge_stat(const BattleWorld& world, unsigned slot, bool shooting)
  const auto& a = world.actors.at(slot);
  const auto target = a.relationships.secondary_target;
  ... world.actors.at(target).relationships.secondary_target == slot ...
std::array<float,4> selected_weapon_socket(const BattleWorld& world, unsigned slot, unsigned hand)
  ... actor_bone_world(world, slot, bone) ... transform_actor_point(point, ...)
```
(`full_charge_native_world.inc.hpp:23-43`)

So that body expects a world holding **actors, per-actor relationships (secondary
target) and bone/weapon-socket transforms**, plus a statistics table — the reference
actor/services layer, in bounded form.

**Option A/B evaluation, per family (P2-1's answer so far):** mixed, not "most".

| Group | Needs | Judgement |
|---|---|---|
| Locomotion (increment 1) | scalars + 4 services, 3 legacy-owned | Option A, small |
| Ground shot, melee admission (increment 2) | scalars + RNG + trig + steering + an event sink; host owns admission/spawn/voice | Option A |
| Guard, hit/damage/KO, jump, air dash | scalars + motion + damage tables | Option A, likely small (their per-file services not yet counted) |
| Air shot schedules, jump bodies | generated tables (19.7k + 3.6k lines) | data; the host-side scheduling remains to be counted |
| **Full charge (a Phase 2 target case: charge levels)** | `BattleWorld` façade: actors, relationships, bone transforms, weapon sockets, statistics | **Option A only with a bounded world façade, or this case is deferred/re-scoped** |

Counted so far: **13 Rena-named bodies (~950 lines) + ~40 shared/generated bodies**; the
pilot's core locomotion/shot/melee path needs no world, while the charge case does. This
is the concrete choice `DIRECTION.md` §4 2a asks to be presented rather than absorbed:
build a bounded `BattleWorld` façade for the charge case, or keep charge out of the
pilot's first scope. It is recorded as `QUESTIONS.md` Q18 and needs the owner.

## 12. Owner decision on the route (2026-10-16): Option A with a bounded façade

**Decision (owner, `QUESTIONS.md` Q18): Option A, with a `BattleWorld` façade bounded by
what the charge body needs — it must not grow past that; if it does, stop and re-present.**

Façade size, taken from the only reads found (`full_charge_native_world.inc.hpp:23-43`):

| Requirement | Bounded shape | Already available in the port |
|---|---|---|
| `world.actors.at(slot)` | a 2-4 slot actor array | `Match::fighter(i)`, `Match::config().fighterCount` |
| `relationships.secondary_target` | one target index per actor | `TargetLocks` (`target_lock.h:116`) holds per-fighter lock/aim selection |
| `actor_bone_world(world, slot, bone)` | bone world transform per actor | `main.cpp`'s match rig worlds (`app.worlds[matchRig[i]]`, used for aura/attachment frames) |
| `selected_weapon_socket(world, slot, hand)` | weapon socket transform (2 hands) | the existing attachment/weapon-slot transform path used for muzzle points (`match.h` muzzle/shot points) |
| statistics table | `attacks_at_primary_target` counters | `Fighter::stats()` (`fighter.h:658`) already carries per-fighter counters |

So the façade is expected to be a **thin adapter over data the port already has**, not a new
world subsystem; the bounded scope is the five rows above and nothing else. The control
point for growth is explicit: any sixth requirement is a stop-and-re-present event, not an
extension.

## 13. Host-side count completed (P2-1 closes)

The remaining host-side question was whether the air-shot and jump families drag in the
reference machinery the way the charge body does. Measured on the files themselves:

| File | Lines | `BattleWorld` / `world.` / `actors.at` / `actor_bone` / `weapon_socket` hits |
|---|---:|---:|
| `roster_air_shot_schedule.hpp` | 1,401 | **0** |
| `roster_air_shot_round_schedule.hpp` | 1,442 | **0** |
| `roster_air_shot_visit_round_schedule.hpp` | 488 | **0** |
| `roster_air_shot_motion_schedule.hpp` | 260 | **0** |
| `roster_air_shot.hpp` | 127 | **0** |
| `jump_native_control.hpp` | 47 | **0** |
| `battle_jump_motion.hpp` | 74 | **0** |
| `battle_air_dash.hpp` | 18 | **0** |

Their entry points are self-contained `advance_roster_*` functions over their own
schedules and scalars, and no service taking a `world` is called from them. **The charge
family is the only one of the pilot's families that needs the bounded façade**; everything
else is scalars, the recovered RNG, trig, steering, generated tables and event sinks.

**P2-1 result:** the seam for the Rena+0 pilot is, in total, three groups —

1. **scalars + services already owned by the port** (locomotion, guard, hit/damage/KO,
   jump, air dash, air shot, ground shot, melee admission);
2. **generated tables** consumed as data (jump bodies 19,727 lines; air-shot schedules
   3,591 lines), which an adapter reads rather than interprets;
3. **one bounded world façade** for the charge body, sized to the five requirements in
   §12 with the owner's growth rule.

That is not "most of the reference actor/services", so the §4 2a Option B trigger does
**not** fire, and the owner's Option A decision (Q18) is consistent with the count.

## 14. Increment 2: actor context for the shot, melee, guard, hit and jump bodies (P2-4)

**Finding first: part of this seam is already paid in the port.** Two adapted
counterparts exist and are cited here as reuse, not as new work:

| Port file | What it already implements | Note |
|---|---|---|
| `src/gameplay/melee_admission.h` | the recovered **Rena/Mion melee admission** — `rena_melee_admission(AttackAdmissionInput, AttackAdmissionTable)` with the `cancelThreshold <= to->priority` gate read from `character_moves` | recorded gap in its own comment: the `boosted` (armed+ready) chain arm is modelled only for Mion; Rena's is unrecovered |
| `src/gameplay/move_behavior.h` | the recovered **shot programmes** as data ops, e.g. `MoveOp::Recharge` with +40, or +5 when actor word `+0x1fd` is set, and the fixed-tick emission rows (401/403/405/406/407/408/409/450/469) | this file is in the plan's REPLACE list (`DIRECTION.md` §7): evidence of what the port already encodes, not a file to extend |

### Shot body (`battle_rena_ground_shot.hpp`) field map

| Body field | Product counterpart | Disposition |
|---|---|---|
| `weapon` | `character_index()` + the bound weapon slot | existing, translated |
| `complete` | no direct accessor; the port clears `m_shotMoveId` on leaving the Shoot states (`fighter.cpp:1053`) | accessor needed if the body drives the exit; today the state machine owns it |
| `grounded` | `!airborne()` (`fighter.h:870`) | existing |
| `special` | `shoot_gate_powered()` (`fighter.h:783`, actor `+0x845`/`+0x848`) | existing |
| `rounds` | `main_whole()` (`fighter.h:907`) and the magazine objects | existing |
| `elevation` | derived from the aim target (`Match::aim_target`, `TargetLocks`) | **computed, not stored** — the resolver must derive it |
| `heading` | `facing_yaw()` (`fighter.h:865`) | existing |
| `position[3]` | `position()` (`fighter.h:864`) | existing |
| `phase`, `frame` | `move_phase()`, `phase_elapsed()` (`fighter.h:763-764`) | partial: the port's shot row binds when the shot fires (`fighter.cpp:2488`), not at the press |
| `pitch` | `body_pitch()` (`fighter.h:773`, degrees) | existing |
| `speed` | `move_speed()` (`fighter.h:767`, u/tick, the attack channel) | existing |
| `gravity` | `attack_gravity()` (`fighter.h:772`, u/tick^2, -1 = unowned) | existing |
| `offset`, `movement` | none | **unresolved**, shared with the locomotion seam (§9, §12) |

### Shot body event kinds -> port surfaces

| Body event | Port counterpart | Disposition |
|---|---|---|
| `activate` | state entry / `MatchFrame::swingStarted`-style edges | partial |
| `melee_statistics`, `shot_statistics` | magazine admission and `apply_weapon_ammo` (`fighter.cpp:215`); `can_fire(tier)`, `reload_ok()` | existing host-side |
| `model` | `draws_item_model()`, `trail_item_model()`, the prop-slot state | existing |
| `sound` | `MatchFrame::soundEffectId[i]` (`match.h:125`) | existing |
| `voice` | `MatchFrame::shotVoice[i]`/`shotVoiceAlternative[i]` (`match.h:115-116`) plus `meleeVoice*` | existing |
| `attachment_projectile`, `world_projectile` | `fire_shot(...)` and the `ProjectilePool` (`projectile.h:187`); muzzle/anchor resolution | existing host-side |
| `clear_contact`, `contact_capacity` | `contact_disabled()` (`fighter.h:776`); no capacity counter | **capacity semantics unresolved** |
| `strike` | the melee contact/volume path (`MeleeSwing`, `already_hit_this_swing`) | existing |

### Melee admission body field map

| Body field | `AttackAdmissionInput` member | Disposition |
|---|---|---|
| `weapon` | `weaponSlot` | existing |
| `state`, `phase` | `state`, `phase` | existing |
| `grounded` | `grounded` | existing |
| `x`, `z` | `x` (lateral sign), `z` (forward sign) | existing |
| `flags & 0x100` | `normalFlag` | existing |
| `contact` | `contact` (1 hit, 2 guarded) | existing |
| `special`, `ready` | `boosted` | **named unresolved** for Rena (the file's own comment) |
| `priority` + `first(next)` | `CharacterMove::priority` and the `cancelThreshold <= priority` gate | existing |
| `held`, `released` | the input edge contract (§8) — the port consults edges in the state machine, not in the admission struct | existing, different layer |

### Update order and service ownership

The shot row binds when the shot actually fires (`fighter.cpp:2488`) and is cleared when
the fighter leaves the Shoot states (`fighter.cpp:1053`), so a shot body's `phase/frame`
are the **shot programme's** clock, not the locomotion clock. Admission (magazines,
`can_fire`, `reload_ok`) and projectile spawning stay host-side, matching the recovery:
the body *requests*, the host resolves (`battle_rena_ground_shot.hpp:22-23`). Voice and
sound ordering is the host's, published per fighter per tick through `MatchFrame`.

Counted for increment 2: **7 shot-body fields existing, 2 computed/derived, 2 unresolved;
9 melee-admission fields existing, 1 named gap; 9 of 11 event kinds mapped, 1 partial and
1 unresolved.** No field is silently zeroed, and any *new* requirement discovered at the
resolver (P2-6) must be added to this table under §12's growth rule.

**Unresolved carried forward:** `offset`/`movement` (shared with locomotion), the
Rena `boosted` chain arm, contact-capacity semantics, `elevation` derivation, and the
statistics ops' admission order.

## 15. The resolver (P2-6)

`src/gameplay/native/rena0_resolver.h` is the single binding owner §12 asked for. It takes a
host-filled scalar view (the §14 fields, never a `Fighter` reference) and returns explicit
move/phase/set with a reason on every path:

| Entry point | Answers | Named failures |
|---|---|---|
| `resolve_rena0_set` | row + phase -> animation set, bounds-checked against the rig | `no-move-row`, `no-move-table`, `move-row-absent`, `phase-set-unbound`, `set-out-of-model-bounds` |
| `resolve_rena0_locomotion` | the recovered body picks the state, the row follows | `not-a-locomotion-state`, `airborne-set-unresolved` |
| `resolve_rena0_admission` | the recovered admission picks the row | `admission-refused`, `armed-special-unrecovered` |
| `resolve_rena0_weapon` | the equipped weapon id (two-halves rule) | `weapon-unbound`, `weapon-data-absent` |

It satisfies §12's bounded-façade requirements by naming rather than hiding the unresolved
seam items: `boostedGap` marks an armed+ready view in the 299 < state < 350 window (the
port's recorded admission gap), `airborne-set-unresolved` refuses to invent an airborne
clip, and the gauge/`offset`/`movement` dependencies stay unowned instead of being zeroed.

**It is deliberately unwired**: nothing under `src/` includes it, and
`tests/rena0_resolver_test.cpp` walks the tree and fails if that changes, so the legacy
default path and the other 45 combos are untouched. Integration behind the flag is 2e and
waits for the owner's contract approval.

## 16. Clock and state ownership for the 2e locomotion slice (owner-ordered first slice)

The owner's order for 2e is explicit: locomotion behind the flag first, **resolving clock
and state ownership**, with adapter equivalence and flag-off restoration demonstrated
before any combat family is added. This section is that resolution.

Today the port owns all of it: `Fighter::update_state_machine` (`fighter.cpp:788`) decides
Idle/Walk/Airborne, `Fighter::update_movement` (`:930-990`) applies the walk speed from
`locomotion(m_moves)->walk / dt` and the yaw turn (`m_walkTurnRate` reset to 20, decayed to
1, clamped in degrees), and `Fighter::advance_animation_phase` (`:1744`) advances the phase
clock. The recovered body decides the same things from scalars: state admission, strict
phase completion, the turn step, the 7.2 walk speed and the gauge refill.

| Decision | Owner today | Slice 1 (observe) | Slice 2 (drive) |
|---|---|---|---|
| Idle/Walk/Airborne transition | port state machine | port; the adapter only compares | adapter proposes, port applies |
| Phase clock (frame/secondary/completion) | `advance_animation_phase` | port; adapter compares | adapter's completion drives the port's phase |
| Turn step (20 reset, decay, floor 1) | `update_movement` | port; adapter compares | adapter's step feeds the port's yaw |
| Walk speed 7.2 | `update_movement` | port; adapter compares | adapter's speed feeds the port's velocity |
| Position integration, collision, animation binding | port | port (unchanged) | **port stays the owner**: the adapter never integrates |
| Gauge refill / `+0x834` | port | not compared (declared unsupported, §2b of the contract) | not compared |

**Slice 1 — observe mode behind the flag (done 2026-10-16).** `--native-actions=rena0` is in
the CLI (`Options`, `main.cpp`), and the match tick samples P1 before the step
(`sample_rena0_pilot_tick`) and compares after it (`observe_rena0_tick` in
`src/gameplay/native/rena0_pilot_adapter.h`). It mutates nothing: the sample is read through
a `const Fighter&` and the adapter writes only its own observer. Diagnostics go to **stderr**
so stdout stays gameplay-only.

Measured on the scripted locomotion recipe
(`tests/scripts/locomotion-walk-turn.txt`, 240 frames): **180 in-domain ticks, 180 agreed,
0 disagreed**; 60 out-of-domain ticks, each with a named reason (59 `not-a-locomotion-state`
during BattleStart and the guard-free idle stretches, 1 `entry-state-not-locomotion`).
Flag-off restoration: the same command with and without the flag produces **byte-identical
stdout** apart from the wall-clock frame timing lines, and a **byte-identical rendered
capture** (240 frames, same `--out` path). Rollback is removing the flag.

Two clock facts were measured rather than assumed, and both corrected the harness:

* A state transition enters the new phase whose clock already reads **1** on that same
  update: `Fighter::enter_phase` zeroes it and `advance_animation_phase` runs afterwards
  (`fighter.cpp:1759-1800`). The body proposes a reset to 0 for the *next* update, so the
  live comparison expects 1 on the transition tick — the offline differential sees the same
  boundary from the other side.
* **Locomotion sets carry the phase gate**, and a gated set returns before the period
  comparison (`fighter.cpp:1760-1761`), so the port's walk/idle phase clock never completes:
  measured 35 → 36 where the clip's duration is 35. The body is fed the port's own
  `animation_set_phase_gate`, so the two agree by construction here; an ungated completion is
  reported as `phase-completion-unobserved` instead of being asserted.

**A mapping correction from this slice:** `move_counter` is **not** a per-tick clock. It is a
move-program data counter (`MoveOp::CounterSet`/`Counter`, `fighter.cpp:1960-1961`), read by
`kGateCounter*` gates (`:2168-2186`) and the aim spread (`:2224`). The F1-5 probe's
`secondary = move_counter` was therefore a proxy, and the body's `secondary` has **no
established port counterpart**; the live adapter does not compare it and prints that note on
every pilot run. Nothing about the acceptance contract changes — the secondary clock is not
an acceptance field (§2 of the contract), so the approved revision stands untouched.

**Slice 2 — drive mode (done 2026-10-16).** With the flag on, P1 and only P1 carries a
`Fighter::PilotLocomotion` policy: the recovered body answers the **Idle/Walk state
proposal** (`update_state_machine`) and the **walk speed** (`update_movement`), returning -1
outside the locomotion domain so dashes, attacks and airborne ticks keep the legacy answer.
The port keeps position integration, collision, animation binding, the turn step and the
phase clock.

**Why the turn and the clock are not driven:** the port already encodes the recovered turn
rule (20 reset, decay to a floor of 1, clamped in degrees — `fighter.cpp:974-979`, measured
equal to the body by F1-5 and by the offline differential's 313/313 turn agreement), and the
phase clock's convention is the port's own (`enter_phase` then advance; gated locomotion sets
never complete). Driving either would add a second implementation of identical behaviour, not
a recovered one; §16's table records them as port-owned with that reason.

Measured: **181 drive ticks** on the scripted locomotion recipe (the body answered the state
and speed questions), the observer still at **180 in-domain / 180 agreed / 0 disagreed**, and
the flagged run remains **byte-identical to the legacy run** on stdout (apart from wall-clock
timing lines) and on the rendered capture. The drive path is **load-bearing, not dead
wiring**: mutating the policy to always propose idle changes the rendered capture and makes
the observer report 136 disagreements — so a divergent body would be caught, not silently
accepted. Flag-off attaches no policy at all (`m_pilotLocomotion` stays null and both hooks
are skipped), which is why the default path is unchanged.

**Not in these slices:** the combat families (melee, shot, charge, guard, hit, KO). Each is
added on its own with its offline expectations, event checks and scripted scenarios. The
20 fixtures and the 11/11 target-case matrix establish *observable* coverage of the port's
behaviour; they do **not** establish recovered-body coverage for every family, and the
owner's review says so explicitly.

## 17. The melee family in the pilot (P2-7, first combat family)

Added the way the owner ordered: offline expectations, event checks and a scripted scenario
first, then the runtime comparison.

**Offline expectations** already existed and stay the authority: the admission body test
(`tests/rena0_admission_body_test.cpp`, 24 checks against the real move table) and the F1-3
melee fixtures (the whole 300-family string plus hit and KO).

**Event checks** are the port's own and unchanged by the flag: the melee fixtures pin
`swingStarted`, `meleeHit`, `meleeVictim` and the damage, and the flagged run's events are
byte-identical to the unflagged run (below).

**Runtime comparison and scripted scenario.** `observe_rena0_melee` asks the recovered
admission the same question the port asked on every **fresh admission** (a tick where the port
bound a melee row it did not hold before) and compares the two rows.
`tests/scripts/melee-ground-300.txt` drives four presses — neutral, neutral (chain), walking,
and back-held — and the measured result is **4/4 agreed**: rows 300, 301, 302 and 310, with
the flagged run's stdout and rendered capture byte-identical to the unflagged run. The suite
carries the same comparison across the fixture set: **9 fresh admissions, 9 agreed**.

**Finding: the default path already drives melee from the recovered admission.** The port
calls `attack_admission_recovered` and builds `AttackAdmissionInput` from its own state
(`fighter.cpp:467-475`, `:1604-1612`), so for this family the pilot's contribution is
verification and gap-naming (the `boosted` arm, `armed-special-unrecovered`), not a new
driving path. That is why the flag changes nothing here — and why the equivalence check is
the right evidence rather than a new mechanism.

**Finding: the admission axes are facing-relative, and the pilot adapter had them inverted.**
The port's dispatcher reads `held_axis_x`/`held_axis_z`, where **Up is +1 and Down is −1**
(`fighter.cpp:136-158`), so the recovered admission's back branch (`z < 0`) is a **Down**
press. The pilot adapter's first version mapped Down to +1 and reported a false mismatch on
the back-held fixture; the helpers now live in one shared header (`src/gameplay/held_axis.h`)
used by both the legacy dispatcher and the adapter, so the two cannot drift, and the suite
went from 8/9 to **9/9**. The locomotion observer's own `z` sign (Up → −1, from the F1-5
probe) is the *body's* convention and is not validated against the port's dispatcher; the
locomotion checks do not depend on it, and any future direction-dependent driving must adopt
the shared helpers first.

## 18. The shot family in the pilot (P2-7, second combat family)

**The body is now adapted**, which this family needed first: unlike melee (where the port
already calls the recovered admission), the ground-shot body had no port-side counterpart.
`src/gameplay/native/rena0_ground_shot_observation.h` reproduces the bundle's
`battle_rena_ground_shot.hpp` for **weapon slots 0 and 1**, with its ordered event list as the
output, and adapts the two steering helpers it uses (`approach_battle_offset`,
`approach_battle_offset_preserving_movement`) with the bundle's `42dc20` note.

**Offline event checks** — the family's interesting content is the order in which the original
publishes its requests, and `tests/rena0_shot_body_test.cpp` pins it from scalars alone
(36 checks, data-free, never skips):

| Frame (weapon 0) | Published, in order |
|---|---|
| 0 | `activate` only; offset approaches its target by 20 |
| 1-11 | nothing; phase 0 decays the speed by 0.5 per frame |
| 12 | `model` (-1, slot 0), `model` (-1, slot 1), `sound` 70, `shot_statistics`, `voice` 27 (**30 on the last round**), `attachment` 0 (6 when armed), pitch = elevation clamped to ±30 |
| 13+ | the two `model` requests repeat; nothing else |
| `complete` | proposes state 0, publishes nothing |
| airborne | proposes state 43, sets gravity 0.5, publishes nothing |

Weapon 1 is adapted too (its first frame publishes `activate`, `melee_statistics`,
`clear_contact`, `contact_capacity` and the strike request; frame 7 speed 45; frame 15
`sound` 67 + `voice` 29; frame 18 `sound` 77 + `shot_statistics` + one attachment, or **two**
attachments when armed; the strike window is frames 8-18).

**Named refusal, not a silent gap:** weapon 2's scatter is the only caller of `legacy_trig`
and its 3600-entry cosine table, which is not adapted, so `weapon == 2` **throws** with that
reason. Rena+0 is weapon slot 0 — the pilot combo — so the pilot's path is complete while the
gap stays visible.

**Guard extended:** the resolver test's scan now also requires the recovered observation
bodies (`rena0_locomotion_observation.h`, `rena0_ground_shot_observation.h`) to be included
only from `native/`, mutation-verified.

**Live comparison (done).** `observe_rena0_shot` advances the recovered body once per tick
while the port holds a shot row, owning the body's `frame` clock (the body reads it and never
advances it), and compares the three correspondences the seam can defend: the **fire tick**
(the body's frame-12 `shot_statistics`/projectile request against `MatchFrame::shotFired[0]` /
`shotsSpawned`), the **sound id** (`soundEffectId[0]`) and the **voice id**
(`shotVoice[0]`/`shotVoiceAlternative[0]`). Measured on
`tests/scripts/shot-ground-400.txt` (two taps and one held press): **98 shot ticks, fire 2/2,
sound 2/2, voice 2/2, 0 disagreements**, with the flagged run's stdout and rendered capture
byte-identical to the unflagged run. The suite carries the same comparison on the tap-shot
fixture: **fire 1/1, sound 1/1, voice 1/1**.

Not compared, and named as such: the projectile positions, the pitch (its `elevation` input is
the derived value the seam lists as computed) and the model requests.

**Row guard — the body models state 400 only.** The walking and dash shots (401/403/405-408)
and the charges (450/469) have their own programmes, so a bound row other than 400 is reported
as `shot-row-unadapted` instead of being compared against the wrong body. The live run shows
exactly that: the held press reaches a charged row and is named, while the two taps match on
all three channels.

**Charge levels** remain the port's own path, pinned offline by `rena0-charge-hold.fixture`
(tiers, `yellow_hold_sec` 0.5 s, `red_hold_sec` 3.5 s → the Red boundary at update 210) and
declared unsupported for `charge_gauge` (contract §2b). The charge rows' bodies are **not**
adapted; the pilot names them rather than guessing.

## 19. The guard family in the pilot (P2-7, third combat family)

**The body is adapted:** `src/gameplay/native/rena0_guard_observation.h` reproduces the
bundle's `battle_guard_motion.hpp` (the original's `438310`), with states 390
(preparation/hold/release), 391 (successful guard) and 392 (the attacker's recoil). Its two
steering helpers now come from a shared header (`src/gameplay/native/rena0_steering.h`), which
the shot body uses too, so the two cannot drift.

**Offline checks** (`tests/rena0_guard_body_test.cpp`, 26 checks, data-free, never skips) pin
the transition logic that is this body's actual content:

| Condition | Body's answer |
|---|---|
| state 390, phase 0, frame 0 | speed 0, contact flags cleared, `clear_contacts` requested, offset approaches by 20 |
| phase 1, both guard buttons held | the guard gauge drains **10 per frame** |
| phase 1, either button released, or gauge 0 | proposes phase 2 |
| phase 1, a guarding contact with gauge left | proposes **391** and clears the contacts |
| phase 1, a guarding contact with gauge 0 | no 391 |
| phase 2 | speed decays by 1 per frame |
| 391/392, phase 0, frame 0 | speed −15, hold counter reset then counted (the frame's own ramp makes it −14) |
| 391, phase < 2, contact | holds the guard |
| 391, hold counter past 20 | proposes phase 1 |
| 392 | ramps speed by 1 per frame while its phases last |
| complete / airborne | proposes 0 / 43 (391 in the air proposes **103**), gravity 0.5 |

**A units caveat kept explicit:** the body's `gauge` is 0..1000 drained 10 per frame, while
the port's stamina is 0..100 and was measured at 25 per second. The two are not
interchangeable and the gauge economy is already unresolved (contract §2b declares
`charge_gauge` unsupported), so this module exposes the body's own numbers and never claims
they are the port's. The live comparison will therefore compare state/phase/contact decisions,
not the gauge.

**Live comparison (done).** `observe_rena0_guard` advances the guard body while the port is
in `Guard` and compares the two facts both sides have. Measured on
`tests/scripts/guard-hold-live.txt` + `guard-attacker.txt` (P1 guards from update 70 to 200,
P2 swings three times from inside reach): **118 guard ticks, 3 guard starts, 2/2 guarded
contacts agreed, 0 disagreements**, with the flagged run's stdout and rendered capture
byte-identical to the unflagged run. The timeline shows the port's own path: `Guard` →
`Hit` on each landing (updates 116 and 176) → back to `Guard`, then Idle on the release at
200; the third swing lands after the release and reports no block, which is the unguarded
contrast. The suite carries the comparison on the guard fixture (**240 guard ticks, 0
disagreements**).

**Finding: the port's guard is coarser than the recovered body, and its damage gate is a
provisional port rule.** The port binds **no** clip or phase for `Guard`
(`state_has_animation_selector` returns −1 for it), so the body's phases 0/1/2, its 390/391/392
rows and its 20-frame hold counter have **no port counterpart** — recorded as
`guard-granularity-unrepresented`. What the port does have is recovered on the attacker side:
a guarded contact switches the attacker to the 392 recoil row through `rena_guard_exit_row`
(`fighter.cpp:1829-1836`). On the victim side the damage gate is explicitly **PROVISIONAL**:
`take_damage` reduces a guarded hit to 20% with a comment saying the original's guard damage
gate is unmapped (`fighter.cpp:1228-1235`, "the original's guard damage gate is unmapped — see
the unresolved guard selector in `state_to_move_id()`"). The body's own gauge is also not the
port's stamina (0..1000 at 10/frame versus 0..100 at 25/s), so an empty-gauge release cannot be
compared with an exhausted-stamina release — `guard-gauge-units-unresolved`.

**Hit and KO are not adapted, and that is deliberate.** The bundle spreads them across a
pipeline (`battle_damage_pipeline.hpp`, `battle_hit_damage.hpp`, `battle_death_motion.hpp`,
`battle_first_death.hpp`, and more), which is a larger adaptation than one round should start
without the owner's steer. Their observables are already pinned where the contract needs them:
`rena0-hit-ground-300.fixture` (contact at 15, the recovered 8 HP) and `rena0-ko-ground-300`
(KO registered at 16, victim left at 1 HP, no respawn), with `koCredits`/`overkillHits`/
`pending_ko` declared unsupported in §2b. The guard body's own 391/392 paths are exercised by
the offline checks; the live guard scenario (including a guarding contact) is next.

## 20. The recovered guard damage gate (owner-ordered investigation)

The owner asked for the victim-side guard gate to be established before closing 2e, because it
changes HP and therefore KO outcomes. It is established, from existing addressed research —
no new binary analysis was needed.

**Predicate (tier 2).** The bundle's `battle_hit_guard.hpp` reproduces it and the repo's own
listing confirms it at `FUN_00637950` (0x637950), lines 185-192: a hit is guarded when

* the impact angle relative to the victim's facing is within **±45°**, unless the victim
  carries flag **0x2000** (guard from any angle), **and**
* the victim carries flag **0x400** (guard-capable), **and**
* the attack does **not** carry flag **8** (unblockable).

The guarded path then writes the contact word **2**, ORs **0x100** into it when the victim
carries flag **0x8000**, decrements `remaining`, calls `FUN_0042c800(2)` (the attacker's 392
reaction the port already implements) and increments the guard counter at `+0xaf30`.

**Outcome (tier 2, the decisive part): a guarded melee hit applies NO HP damage.** The
guarded branch is `FUN_00637950`'s `else` at lines 541-552, and it contains no damage call —
none of the `FUN_00435990` damage path, no health write and no statistics update that the
not-guarded branch performs. Blocking is absolute for a melee hit; only the guard bookkeeping
and the attacker's recoil happen.

**This makes the port's current rule wrong, not merely provisional.** `take_damage` reduces a
guarded hit to 20% (`fighter.cpp:1228-1235`, its own comment calling the gate unmapped), and
the port's predicate is also coarser than the recovered one: it tests only
`victim.state() == Guard` (`match.cpp:270-272`) and ignores the ±45° impact angle, the
victim's 0x400/0x2000 flags and the unblockable attack flag 8.

**Implemented behind the flag (2026-10-16).** `Fighter::PilotGuard` is the policy, attached
to the **victim**; both melee damage sites in `try_melee_hit` (the data-driven record path and
the recovered-hitbox path) go through one helper, so a guarded hit never reaches `take_damage`
and therefore applies no damage and no stun. The adapter's `Rena0PilotGuard` answers the
predicate as far as the port can express it: the victim's `0x400` term is stood in for by the
port's own `Guard` state (the port's note says the word's builder is unlocated and it keeps its
own key), the angle term is applied in the port's convention (the victim must face the attacker
within 45°), and the victim's `0x2000` and the attacker's unblockable flag `8` are **not
expressible** from port data and are therefore **not applied** — named, not guessed. The
predicate is asked only after a hit lands, so it can never change whether a swing connects.

**Fixtures (two, differing only by one directive).**
`rena0-guard-gate-pilot.fixture` uses `dummy_guard 1` + `pilot rena0-guard` and pins the
recovered outcome: a guarded hit leaves the dummy at **100 HP** with `melee_hit` reported and no
KO. `rena0-guard-gate-legacy.fixture` uses only `dummy_guard 1` and pins the legacy default:
**99 HP**, i.e. the provisional 20% rule floored at 1. Together they are the flag-off
restoration evidence at fixture level.

**Live evidence.** The guard scenario (P1 guards updates 70-200, P2 swings three times from
inside reach) now reports `guard gate asked=3 guarded=2 not-guarding=1 outside-angle=0`: the two
guarded hits are blocked by the recovered gate, the third lands after P1's release and takes the
full 8. P1 ends at **92 HP** (0 + 0 + 8) where the legacy path would end at 90 (1 + 1 + 8 from
the fixture-pinned rule), and the flagged and unflagged captures now **differ** — as they must.

**This is the pilot's first behaviour-changing feature.** Locomotion, melee admission and the
shot path all agreed with the legacy path; the guard gate deliberately does not. So for guard
scenarios "flag-off restoration" means **the legacy behaviour is unchanged** (the legacy fixture
still shows 99 and the unflagged capture is unchanged from before), not "identical output" —
and the difference between the two fixtures and the two captures *is* the evidence.

**Scope note:** the two guard-gate fixtures are **not** acceptance cases. They are reported as
unreferenced extras by the manifest, so the approved v2 acceptance scope (11 target cases plus
the timed-round row) is untouched; promoting them into the contract would be a v3 decision for
the owner.

## 21. 2f — evidence and rollback check (P2-8)

Run 2026-10-16 against the approved contract v2 (`sha256 c5df9931…`, reviewed content).
**No cleanup happens here** (2h waits for the owner's 2g verdict), and acceptance stays **0/46**
until that verdict.

### 1. The approved coverage matrix, run

`RENA0_FIXTURES: PASS (22 fixtures, 60 Hz, 21 case rows, 39 acceptance fields, 7 unsupported
declared, 2 unreferenced extras, skips=0)`. That is the eleven DIRECTION.md §4 Phase 2 target
cases plus the timed-round row, every acceptance field of §2b mapped to a fixture that asserts
it, the seven unsupported fields declared with reasons, and the two guard-gate fixtures
reported as extras — deliberately outside the approved scope.

Offline body evidence, all green: locomotion 53 checks, admission 24, shot 36, guard 26,
resolver 48 (including the pilot-path scans), and the F1-5 probe.

### 2. Binding, state, motion and events, compared

| Comparison | Result |
|---|---|
| Fixture-linked differential (binding, clock, turn, speed) | **315 in-domain ticks**, no unexplained divergence |
| Locomotion observer (live) | 180 in-domain ticks, **180 agreed** |
| Melee admission (live / suite) | **4/4** live rows (300, 301, 302, 310); **11/11** in the suite |
| Shot (live / suite) | fire **2/2**, sound **2/2**, voice **2/2**; suite fire/sound/voice **1/1** |
| Guard (live / suite) | **2/2** guarded contacts, 130 guard ticks; suite 240 ticks, 0 disagreements |
| Guard gate (live) | asked 3, **guarded 2**, not-guarding 1, outside-angle 0 |

### 3. Provenance

| Claim | Tier | Artifact |
|---|---|---|
| Acceptance observables and their transitions | 4 (+2) | the 22 fixtures, each citing an address or a recovered artifact in its header |
| Locomotion control (7.2, turn reset/decay/floor, state proposal, gauge refill) | 2 | `rena0_locomotion_observation.h` (bundle body), `FUN_0043ffc0` |
| Melee admission rows | 2 (+4) | `melee_admission.h` (the port's adaptation), `battle_rena_melee_admission.hpp`, the admission body test against the real table |
| Shot programme events | 2 | `rena0_ground_shot_observation.h` from `battle_rena_ground_shot.hpp` |
| Guard body 390/391/392 | 2 | `rena0_guard_observation.h` from `battle_guard_motion.hpp` |
| Guard predicate and the zero-damage outcome | 2 | `FUN_00637950` (0x637950), guarded `else` at the listing's 541-552; `battle_hit_guard.hpp`; fighter.h's guard note |
| Guard gate under the flag | 4 | `rena0-guard-gate-pilot` (100 HP) vs `rena0-guard-gate-legacy` (99 HP), one directive apart |
| Flag plumbing and rollback | 4 | the four live A/B runs, the resolver test's scans, `main.cpp`'s flag site |
| Original binary identity | — | `DaybreakDX.exe` sha256 `27e61475…` re-verified 2026-10-16 |

### 4. Unresolved limits, named

`offset`/`movement` channels; the armed+ready ("boosted") melee chain arm; contact-capacity
semantics; `elevation` derivation; the statistics admission order; `move_counter` is a
program counter, not a clock (so the body's `secondary` has no counterpart); the airborne
cycle's clip resolution; the guard body's phases, 390/391/392 rows and 20-frame hold counter
have no port counterpart; the guard predicate's `0x2000` and unblockable-flag-8 terms are not
expressible; the guard gauge is not the port's stamina; weapon 2's shot branch needs the
legacy cosine table and is not adapted; the hit/KO damage pipeline is not adapted; and the
contract's seven unsupported fields (`charge_gauge`, `koCredits`, `overkillHits`, `pending_ko`,
`charge_whole`, `round_over_side`, `kos`).

### 5. Rollback: flag-off restores the baseline, with no global resolver change

| Scenario | Deterministic stdout | Rendered capture |
|---|---|---|
| Locomotion (240 frames) | **identical** | **identical** |
| Melee (260 frames) | **identical** | **identical** |
| Shot (260 frames) | **identical** | **identical** |
| Guard (260 frames) | differs **only** in the HP fields (`hp=90` → `hp=92`); `hits=3`, `shots=0`, `sparks=0`, `fx events=3` identical | differs |

The guard difference is the intended one and is fully accounted for: two guarded hits now deal
0 instead of `max(1, 8/5)` = 1 each. The flag-off baseline itself is unchanged from before the
gate existed — `rena0-guard-gate-legacy.fixture` still pins 99 HP, and the unflagged capture is
the same one the pre-gate runs produced.

**No global resolver change:** with the flag off no pilot policy is attached at all (both hook
sites test a null policy), and the resolver test's scans walk the tree and fail if the resolver,
the adapter or any recovered observation body is included from outside `native/` and the flag
site — mutation-verified in both directions. Rollback is therefore removing the flag; after 2h
the recorded pre-cleanup revision is the fallback.

**What 2f does not claim:** original-runtime parity (that needs tier-1 traces), and acceptance —
the matrix is evidence for the owner's 2g verdict, not a green result.

## 22. Pending-verdict gaps and the v3 proposal (owner-ordered closure plan)

The owner reviewed the 2f evidence on 2026-10-16 and **kept 2g pending**: the slice is working
and reversible, but the approved Rena+0 scope is not yet established to a green standard, and
red was rejected because the method did not fail. **2h cleanup must not start and the freeze
must not lift while the verdict is pending.** The owner's instruction: finish or explicitly
re-scope the load-bearing cases, then repeat 2f against the resulting approved contract. This
section is that proposal; each item needs the owner's choice before it is either built or
written into a v3 contract.

### Gap 1 — charge and hit/KO bodies remain on the port path

Their observables are pinned by fixtures (charge tiers and hold-seconds; contact at 15 with the
recovered 8 HP; KO at 16 with 1 HP left and no respawn), but the *bodies* are not adapted, so
the pilot does not drive them.

* **(1a) Adapt them.** The bundle carries `battle_attack_charge.hpp`, `battle_hit_charge.hpp`
  and the full-charge body sets, plus a damage/death pipeline (`battle_damage_pipeline.hpp`,
  `battle_hit_damage.hpp`, `battle_death_motion.hpp`, `battle_first_death.hpp`, and more).
  Charge looks like one round; the damage/death pipeline is several, and it would touch the
  frozen decision path behind the flag.
* **(1b) Re-scope explicitly.** v3 states that charge and hit/KO remain port-owned for the
  pilot, with the fixtures as their only evidence and the tier-6 items named — an exclusion,
  not a silent denominator change.

### Gap 2 — shot projectile positions and model requests

Progress this round: fire, sound and voice were already compared; the **projectile pitch is now
compared too and agrees 2/2** on the shot scenario. Two parts remain.

* **Model requests.** The body requests a model clear on each slot (id −1) from frame 12
  onward; the port's per-slot binding (`trail_item_model`) never reads −1 during a shot, so the
  naive mapping disagrees on every such tick — measured **0/148**. That makes the *mapping*
  unverified, not the port wrong, so the observer counts it and never gates on it. Options:
  **(2a)** investigate what the body's `model` request corresponds to in the port (a prop slot,
  a draw gate) before asserting anything; **(2b)** v3 records it as an unverified mapping with
  the measured count.
* **Projectile positions.** The spawn point is host-resolved from the rig's anchors; the body
  does not compute it, so verifying it needs **tier-1 original-runtime evidence**. Options:
  **(2c)** leave it as a named limit — the plan allows original-runtime parity to remain
  unverified — or **(2d)** treat it as required evidence, which is a different, larger task.

### Gap 3 — the guard predicate's proxy and flags, and its fixtures

The zero-damage outcome is source-backed (tier 2) and implemented behind the flag, and the live
predicate applies the recovered ±45° angle term. It uses the port's own `Guard` state as a proxy
for the victim's `0x400` term and **cannot express** the victim's `0x2000` or the attacker's
unblockable flag `8`, because the builder of those words (`[actor+0x10]+0x28` / `+0x2c`) is not
located. The two guard-gate fixtures are extras, outside approved v2.

* **(3a) Locate the word builder** with focused binary analysis (the owner's earlier steer
  allows it), which would make all three flag terms expressible and remove the proxy.
* **(3b) Re-scope** the flag terms explicitly in v3, keeping the proxy and the two
  inexpressible flags as named exclusions.
* **(3c) Promote the two guard-gate fixtures** into the contract as acceptance cases (a v3
  scope addition), so the gate's evidence sits inside the approved scope either way.

### What the owner chose (2026-10-16)

* **Gap 1 → (1a) + explicit re-scope.** Adapt the **charge** bodies; the hit/KO
  damage-and-death pipeline is **explicitly re-scoped out** of v3 by name, with the hit and KO
  fixtures as its only evidence and the tier-6 items recorded.
* **Gap 2 → (2a) + (2c).** Run **one bounded investigation** into what the body's `model`
  clear request corresponds to in the port before asserting anything; the projectile **spawn
  positions stay a named limit** (they need tier-1 evidence the plan allows to remain
  unverified).
* **Gap 3 → (3a) + (3c).** Locate the **flag words' builder** with focused binary analysis so
  the victim's `0x400`/`0x2000` and the attacker's unblockable `8` become expressible and the
  proxy goes away; and **promote the two guard-gate fixtures into v3** so the gate's evidence
  sits inside the approved scope.

**The working order from here:** (i) adapt the charge bodies with their offline expectations,
event checks and a scripted scenario; (ii) the bounded `model`-mapping investigation; (iii) the
focused binary analysis for the flag words; (iv) write **contract v3** with the charge cases,
the promoted guard-gate fixtures, the hit/KO pipeline exclusion, the model-mapping outcome and
the spawn-position limit; (v) put v3 to the owner; (vi) re-run the approved matrix and the four
live comparisons, repeat 2f against the approved v3, and only then put 2g back to the owner.
The verdict stays pending and the freeze stays in force throughout — no 2h cleanup.

## 23. The charge family in the pilot (gap 1a, first increment)

The owner chose **(1a)**: adapt the charge bodies. Doing so split the request into two very
different things, and that split is itself the finding.

**Adapted now: the charge-gauge bodies.** `src/gameplay/native/rena0_charge_observation.h`
reproduces the bundle's `battle_attack_charge.hpp` (original 0x63844e..0x6384fa, attacker mode
1) and `battle_hit_charge.hpp` (0x6382d9..0x63844e, victim modes 0 and 2) plus the shared
integer helpers of `battle_damage_scaling.hpp` — the wraparound multiply, the fault-checked
divide and the bit-reinterpreted sign. `tests/rena0_charge_body_test.cpp` pins them in **29
data-free checks**: the mode and blocked gates, the three divisors (**90** attacker, **133**
victim mode 0, **225** victim mode 2), the defense and modifier factors, the limit clamp, the
notification ids (**6** attacker, **5** victim mode 0 — and mode 2 notifies nothing), and the
preserved integer semantics including the original's `INT_MIN / -1` fault.

These bodies are exactly what the contract's unsupported `charge_gauge` needed: the gauge
economy's accumulation rules, recovered with addresses.

**Not adapted, with the reason: the charge *move* bodies.** States 350-362 live in the bundle's
`full_charge_native_bodies_20260929.hpp`, which is **generated decompiler output** (its own
header says "generation alone is not parity proof"), and Rena+0's slice is a single 40-line
function, `full_charge_body_0_0_351`, that is a thin wrapper over host calls — it clears a word,
binds item models 0 and 1 to the two slots, and calls two host services. There is little
recovered *decision* content to drive, and the port's charge rows are already its own
data-driven programmes (`move_behavior.h`) pinned by `rena0-charge-hold.fixture` (tiers,
`yellow_hold_sec` 0.5 s, `red_hold_sec` 3.5 s, the Red boundary at update 210). The hand-written
control header (`full_charge_native_control.hpp`) is the context/services layer, not a body.

**The correspondence question, answered (2026-10-16).** The adapted gauge bodies and the
port's `charge_gauge` are **two different gauges**, and the port's gap is not where the contract
said it was.

* The adapted bodies (`battle_attack_charge` / `battle_hit_charge`: damage adds `base*scale/90`
  attacker-side or `/133` (mode 0) / `/225` (mode 2) victim-side, clamped at a limit, notifying
  6 and 5) belong to the **special gauge** — the bundle's `BattleSpecialGauges.charge0/charge2`,
  which the special body *consumes*. Its port counterpart is the **hyper gauge** (`m_gauge`,
  0..1). The port refills that gauge (`MoveOp::Gauge`'s dash-recovery refill, `startGauge`) but
  **never accumulates it from damage**, which is exactly what these bodies describe.
* The port's `charge_gauge` (`m_chargeGauge`) is the **+0x834 shot gauge**, and its refill *is*
  implemented: `MoveOp::Recharge` adds **+40**, or **+5** while hit-status slot 6 is live, capped
  at 1000 (`fighter.cpp:2030-2036`, on the dash-recovery rows 403/409/469). What the port lacks
  is a **spend path**: `m_chargeGauge` is only reset to 1000, refilled toward 1000, and read by
  two charged-attack gates (`fighter.cpp:1608`, `:2991`) — nothing ever decrements it. A gauge
  that starts full and is never spent cannot be observed to move, which is the real reason §2b
  declares it unsupported. The recorded reason ("the +0x834 refill semantics stay unresolved")
  is therefore **too pessimistic about the refill and silent about the spend**.

**The owner chose both (2026-10-16):** implement the damage-based **special-gauge
accumulation** behind the flag, and find the **+0x834 spend rule** with focused analysis so
`charge_gauge` can move from unsupported to asserted. The implementation spec is recovered in
full — and it comes with one hard data dependency.

**Spec (from `battle_special_gauges.hpp`, one actor owning three gauges):**

| Piece | Rule |
|---|---|
| Selection | `mode & 0xff` picks the contact path: 0 (charge0/limit0), 1 (charge1/limit1, attacker side), 2 (charge2, uses duration0) |
| Accumulation | the adapted bodies, fed by `victim_state()`/`attacker_state()` (which pass the mode, the active flags as the blocked flags, the charges and the limit) and written back by `store_victim`/`store_attacker` |
| Consumption | `tick`: mode 0 → `--charge0` while active0; mode 1 → `--charge1` while active1; mode 2 → `movement_gauge++` up to 1000 and **health −7 per tick** while active2, ending below health 9 |
| Activation | chords: mode 0 needs melee and shoot in 1..2, an action window, and `charge0 >= limit0`; mode 1 needs the same chord shape, an action outside 100..299, and `charge1 >= limit1` |
| Refill step | active2 → 2, active0 → 1, active1 → 3, otherwise 1 |
| Durations | `begin0` sets `charge0 = duration0`; `begin1` sets `charge1 = duration1`; `begin2` sets `charge2 = duration0` and restores health to 10000; a hit-recovery mode-0 variant uses its own duration |

**The dependency — corrected 2026-10-16: it is already satisfied.** The four values are the
actor DAT's six header dwords (`DAT108..11f`, `assets[i]->parameters[0,1,4,5]`), and the port
**already parses and exposes them**: `CharacterMoves::parse` reads them as the six header dwords
and `header_values()` returns them (`character_moves.h:98`), with index 3 being the weapon id
that `weapon_id()` already uses. The file is the same `data/<char>/NN.dat` the combo loader
feeds to `moves.parse` (`tests/combo_fixture.h:42`). Read independently from the shipped data,
**Rena+0 is `limit0 = 850`, `duration0 = 900`, `limit1 = 850`, `duration1 = 900`** (header
`[850, 900, 0, 1, 850, 900]`). My previous note that the port parses no such table was wrong —
it parses the table, it simply never used these values for the special gauge.

**The mode mapping is also already documented in the port.** `fighter.h:185-191` records that
the executable's own mode word (`+0x318`) numbers **Oyashiro 0, Friendship 1, Kakera 2** (the
opposite of the port's UI enum), and — directly relevant here — that **value 0 fills the
victim-side gauge by taking damage** ("param_3 takes the HP in FUN_00637950, so value 0 fills by
taking damage"). That is exactly the adapted **mode 0** rule (`charge0 += base*scale/133 ×
defense/100 × modifier/100`, clamped at `limit0`, notifying 5).

**Correction (same day): the target is NOT the port's `m_gauge`, and the port already
accumulates something from damage.** Two of my earlier statements were wrong, and the port's own
comment at `fighter.cpp:1254-1262` says so explicitly:

* the port **does** accumulate its hypermode bar from damage — `gain_gauge(amount ×
  fillPerDamageDealt)` for the attacker and `gain_gauge(amount × fillPerDamageTaken)` for the
  victim (`fighter.cpp:1263-1265`) — so "the port never accumulates it from damage" was false;
* but that bar (`m_gauge`, the player-selected **hypermode** gauge) is a **different mechanic**
  from the original's, and the port says so: the original's mode gauges are the
  **+0x838/+0x840/+0x83C** counters, "0..100 counters with their own thresholds", accumulated at
  `FUN_00637950`'s sites **0x638321 / 0x6383e6 / 0x638493** by the record's **combat[5]/[6]**
  columns — which the port **deliberately leaves unread** ("routing the recovered columns into
  it would report the right number through the wrong system… Until the port has the mode-gauge
  accumulators, the damage-derived hyper credit below stands and the record's columns stay
  unread"). Those unread columns are the `gaugeGainA`/`gaugeGainB` provisional aliases in
  `combat_record.h`.

So the adapted bodies' true target is a **mode-gauge state the port does not have yet**, with
the port's own comment naming the exact original write sites, and the actor parameters
(850/900) giving the limits. Implementing it behind the flag therefore means: add the mode-gauge
counters, feed them from the record's combat[5]/[6] columns through the adapted rules, and
compare — while the hypermode bar keeps its own, separate credit.

**Order of work from here:** (i) the accumulation's inputs — the recovered rule wants `base`,
`scale`, `defense` and `modifier`, the port carries the record's **combat[5]/[6]** columns
unread (`gaugeGainA`/`gaugeGainB`) and the per-actor multipliers in the damage path, and the
`charge_scale` is the match's own `match_charge_scale_` (shipped default **100**); (ii) add the
mode-gauge counters behind the flag, feed them through the adapted rules and compare; (iii) the
+0x834 spend-rule analysis; (iv) v3. The parameter and mode blockers are cleared, and the port's
own comment supplies the original's write sites, so (ii) is now a design-and-code step rather
than a data one.

### 23a. The mode-gauge state, built on the shipped parameters (2026-10-16)

`src/gameplay/native/rena0_mode_gauges.h` adds the state the port lacks: the three counters
(`charge0`/`charge1`/`charge2`), the two limits and durations taken from the actor DAT's header
dwords, the `ready1` latch and the two notification counters (ids 5 and 6). `on_hit` builds the
adapted bodies' inputs from the hit record's columns and writes the results back, so the mode
gates, the divisors, the clamps and the notifications all run exactly as adapted.

`tests/rena0_mode_gauge_test.cpp` (install-backed, 17 checks, **77 = skip, never a pass**) pins
two things nothing else can:

* **the shipped parameters**, read through the parser's own accessor: Rena+0's `limit0 = 850`,
  `duration0 = 900`, `limit1 = 850`, `duration1 = 900`, with the same header block still
  carrying the weapon id the parser already uses;
* **the state's behaviour**: the victim gauge adds `base*scale/133` and clamps at the shipped
  850 notifying id 5 once; the attacker gauge adds `base*scale/90` and clamps at 850 notifying
  id 6 once; **the modes are exclusive** (mode 0 leaves the attacker gauge alone, mode 1 leaves
  the victim's); mode 2 accumulates its own gauge at `/225`; and an active mode 0 blocks further
  victim accumulation.

**Input mapping, named:** `victim_charge_base` is the hit record's `combat[5]` and
`attacker_charge_base` its `combat[6]` — the columns the port parses as `hpDamage`/`reflectDamage`
(provisional aliases) and deliberately leaves unread, per its own comment at
`fighter.cpp:1254-1262`; the scale is the match's `charge_scale` (shipped 100), and `defense`/
`modifier` are the damage chain's factors (100 each when nothing modifies them). The bundle
reads the two bases from the record's `0x44`/`0x48` (`actor_frame_hit.hpp:10`).

**Still to do before this drives anything:** the live wiring needs the attacker's hit record at
the contact site — the port exposes `attack_move_id()` but not the record's columns — so the
next step is the smallest accessor that hands the pilot `combat[5]`/`combat[6]` for a landed
hit, then the comparison runs on real hits and the consumption side (`tick`: mode 0/1 decrement,
mode 2's movement and health drain) follows.

### 23b. The mode gauges run on real hits (2026-10-16)

The accessor landed: `Fighter::MeleeChargeBases` (`victim` = the record's `combat[5]`,
`attacker` = `combat[6]`) is captured at the one place a data-driven hit lands in
`try_melee_hit`, exposed by `melee_charge_bases()`, and the legacy swing path records zeros
because a swing carries no record columns. `feed_rena0_mode_gauges` then feeds the pilot
fighter's own gauges from the hits the frame reports — its attacker gauge when it landed the
hit, its victim gauge when it took one — with the limits taken from the pilot's own move table
(`header_values()`), and the mode from its hypermode's **wire** value.

**Evidence, on real hits through the fixture-linked differential:**
`victim-hits=0 attacker-hits=4 charge0=0 charge1=220 notify5=0 notify6=0 (limits 850/850)`.
Four landed hits advanced the attacker gauge to 220 — 55 per hit, which is the record's
`combat[6]` of 50 through `50*100/90` with the integer division the adapted body performs —
while the victim gauge correctly stayed at zero because the port's default mode is
**Friendship (wire 1)**, and the victim path is mode 0/2 only. Neither gauge reached its shipped
limit of 850, so neither notified, exactly as the bodies say.

**A finding worth naming:** the port's default mode is wire 1, so out of the box the
*victim-side* accumulation (mode 0, Oyashiro — the one the port's own comment says "fills by
taking damage") is off, and the attacker-side (mode 1) is on. That is consistent with the
original, where mode 0 is a *selected* mode rather than the default, and it is why the live
guard scenario reports `victim-hits=3` with `charge0=0`: the three hits landed on the pilot, but
the pilot was not in the mode that accumulates from them.

**What this is and is not:** the port has no consumer for these gauges — its `gain_gauge` feeds
the hypermode bar, deliberately, per its own note — so this is *observation* of the recovered
rules running on real hits, not a comparison against a port behaviour. The offline test (§23a)
pins the rules and the shipped parameters; this pins that they run live with real record data.
The consumption side (`tick`: mode 0/1 decrement, mode 2's movement and health drain) is next,
and it needs a consumer decision the owner's v3 scope will carry.

### 23c. The recovered special-gauge control, complete (2026-10-16)

`Rena0ModeGauges` now carries the whole recovered control surface, not just the accumulation:

| Piece | What it does | Pinned by |
|---|---|---|
| `begin0` / `begin1` | fill the gauge from the shipped `duration0` / `duration1` and mark the mode active | 2 checks |
| `begin2` | restores health to the original's **10000**, fills from `duration0`, marks mode 2 active | 2 checks |
| `accepts_mode0_chord` / `accepts_mode1_chord` | the admission chords: both buttons in 1..2, the mode's action window, and the gauge **at its limit** | 6 checks |
| `refill_step` | active2 → 2, active0 → 1, active1 → 3, otherwise 1 | 2 checks |
| `tick` | mode 0/1 spend one per tick and end at zero; mode 2 advances the movement gauge to its **1000** clamp and drains health by **7** a tick, ending itself below 9 (setting health to 1) or below 1 | 12 checks |

The offline test is now **44 checks** (was 17) and still install-backed, so the limits it clamps
at are the shipped ones (850/850 with durations 900/900 for Rena+0), and a data-free run still
exits 77 — a skip, never a pass.

**What is still deliberately not done:** nothing in the pilot *activates* a mode, so the
consumption path never runs live — `tick` is pinned offline and named as unexercised in the
runtime, which is honest rather than implying coverage. Its inputs (`health`, the movement
gauge) are the caller's by design: this state observes the original's rules and never writes
the port's fighters. The consumer decision — whether the pilot should drive these gauges at all,
and through what — is exactly what v3 must carry, alongside the +0x834 spend rule.

### 23d. The +0x834 spend rule, found (gap 1b, 2026-10-16)

The owner's second charge item was to find the +0x834 spend rule so `charge_gauge` becomes
observable. **It is in the existing addressed research — no fresh binary work was needed** —
and the complete rule set for the field is now:

| Direction | Rule | Where |
|---|---|---|
| Reset | `[actor+0x834] = 1000` | `FUN_004219a0:19` |
| Refill, slow | `if ([+0x834] < 1000) ++[+0x834]` — **+1 per tick** | `FUN_0041f580:97-98`, `FUN_00508a60:58-59` |
| Refill, move op | the `MoveOp::Recharge` +40 (or +5 with hit-status slot 6), capped at 1000 — **already implemented in the port** (`fighter.cpp:2030-2036`, rows 403/409/469) | recovered move data |
| **Spend** | **action 402 (0x192) costs 500**, requiring more than 499 | `FUN_00508a60:84-90` |

The spend's own preconditions, read from the listing: the actor's `+0x830` word must be **4**;
the gauge must be positive; the target's action id (`[[+0xade0]+4]`) must be at or below
`[+0xb04]`, or one of `0x27`/`0x13`/`0x59` with `FUN_0042c7b0() == 0`; and bit **0x100** of the
actor's `[[+0x10]+0x28]` word must be set. Then, in order: a `+0x84` flag routes to action
`0x17` instead; the current action must be **`0x192`** or it routes to `0x1e`; and only then,
with the gauge above 499, does it subtract **500** and route to `0x1e`.

**Why this matters:** action 402 is a real port row — `move_behavior.h:487-489`, the **air
tap**, whose powered case is literally `case 0x192`, and the ground tap's counterpart is row 400
(`rena0-tap-shot.fixture` records both: "the ground tap binds move 400… the air tap is 402"). The
spend therefore lands on the **powered tap shot** — the charged projectile attack — which is
exactly the reading the field's name suggests and the reason the port gates charged admission on
it (`m_chargeGauge <= 0`). So `charge_gauge` is observable: start at the
1000 reset, spend 500 on the powered 402, and a second one is refused at 500 ≤ 499 — which is
exactly the gate the port already reads (`m_chargeGauge <= 0` at `fighter.cpp:1608` and `:2991`)
without ever moving the value. The port is also missing the **+1/tick** refill, so the field's
recovery is now complete on both sides: reset, two refill paths and one spend, all with
addresses.

**Next step:** implement the spend and the slow refill **behind the flag**, then a fixture or
scenario that watches 1000 → 500 → (refused), which is what lets v3 promote `charge_gauge` from
"unsupported" to asserted instead of carrying it as an exclusion.

### 23e. The +0x834 spend, implemented and reachability-pinned (2026-10-16)

`Fighter::PilotCharge` carries the recovered spend, and it is applied at the exact place the
port's powered branch lives — `case MoveOp::Launch`, when the rule's gate is `kGatePowered`, the
current attack move is **402** and the gauge is above **499**: `m_chargeGauge -= 500`
(`FUN_00508a60:84-90`). Nothing else about the default path changed: the policy is null unless
the pilot flag attaches it, and the three unchanged scenarios (locomotion, melee, shot) are still
byte-identical in capture **and** deterministic stdout with the flag off.

**Reachability, and why the first attempt observed nothing.** The spend did not fire in the
air-tap scenario — and that is *correct*: the port's `kGatePowered` is
`m_hyperActive && m_hypermode == Hypermode::Oyashiro && m_shooting.aimHold`
(`fighter.h:849-851`), and its own note says a fighter running Friendship or Kakera never takes
a powered branch, "which is source behavior and not a gap". The pilot's scripts run Friendship,
so the air taps took the **normal** branch (they still threw their items — the enemy lost 27 HP
— and the pilot's shot observer reported nothing because the 402 body is not adapted, which is
the `shot-row-unadapted` class). So the spend is implemented, and the scenario that can observe
it must first be in Oyashiro hypermode with an aim hold.

**What that needs, precisely:** the gauge full (the port's `try_activate_hypermode` requires
`m_gauge >= 1.0f`), the mode selected as **Oyashiro** (wire 0), an activation, and a shooting
context with `aimHold` set — the last of which the fixture runner does not publish today. The
good news is that the fixture vocabulary already carries a **`charge_gauge`** observable
(`rena0_fixture_test.cpp:107`), so once a `hyper`-setup directive exists the promotion is a
fixture: gauge 1000 → one powered air tap → `charge_gauge 500` → a second → `0`, with the
third finding nothing to spend.

**Named, not guessed:** the spend's `+0x830 == 4` mode word, the target-action condition on
`[[+0xade0]+4]` and bit `0x100` of the actor's `[[+0x10]+0x28]` word are not expressible from
port data and are not applied; and the **+1/tick refill** (`FUN_0041f580:97-98`,
`FUN_00508a60:58-59`) is identified but its enclosing condition is not, so it is deliberately
not implemented rather than approximated.

### 23f. The gauge's spend is observed and pinned (2026-10-16)

> **Superseded 2026-10-22 (Q19).** The spend pinned below was misattributed: `FUN_00508a60`'s
> `−500` is a directional air-dash cancel out of 402 into state 30 in another combo's selector,
> not Rena's powered shot, and the production deduction has been removed. The fixture shown here
> no longer exists; it was replaced by `rena0-powered-shot.fixture` and
> `rena0-shot-recovery.fixture` (see §29 and the contract's V3-1). The `hyper` directive and
> `Match::cycle_aim_selection` described here are still in use, and the `+40`-on-403 refill
> observation was correct.

`rena0-charge-spend.fixture` is the state the spend can fire in, and it passes:

```
hyper oyashiro                       # gauge full, Oyashiro selected, aim selection armed
input 0 SPECIAL                      # the real activation edge (fighter.cpp:843)
input 4 JUMP / input 10 SHOOT        # the air tap, whose 402 action runs its powered launch
expect 25 charge_gauge 500           # the spend
expect 40 charge_gauge 500           # held while the action still runs
expect 66 charge_gauge 1000          # the air recovery's own recovered Recharge (+40/tick on 403)
input 90 JUMP / input 96 SHOOT       # a second powered tap
expect 112 charge_gauge 500          # spent again, not to zero
```

Two harness pieces made it possible, both of them seams rather than new behaviour: a `hyper
oyashiro` fixture directive (fills the gauge, selects the mode, arms the aim selection — the
activation stays a scripted SPECIAL press, so nothing bypasses the runtime path), and
`Match::cycle_aim_selection`, which reuses the lock's own `cycle_enemy` rule because the offline
runner has no way to press the lock input.

**Two corrections found by running it, both mine:** the spend hook first tested
`attack_move_id()`, which is `-1` for an air tap because the tap is a **shot**, not a melee
attack — the recovered action id belongs to `shot_move_id()`. And the fixture's first shape
expected the second tap to reach zero, but the port's own recovered `Recharge` rule refills
**+40 a tick** on the air recovery row 403, so the gauge is back at its cap before a second tap
can spend twice. The fixture now pins that interaction instead of my assumption.

**Why this matters for v3:** `charge_gauge` — declared **unsupported** in the approved v2
contract — is now **asserted by a passing fixture** with the recovered spend, the recovered
refill and the recovered activation gate. (The refill and the activation gate stand; the "spend"
half does not — see this section's superseded notice.) Promoting it (and the guard-gate pair, and this
fixture) is a v3 scope decision for the owner; it is deliberately left as an unreferenced extra
until then, exactly like the two guard-gate fixtures.

### 23g. Gap 2a closed: the shot body's `model` request, mapped and driven (2026-10-16)

The owner's gap-2 investigation is answered, and the answer is that the port was **one guard away
from expressing a behaviour it already understood**.

**The mapping.** The body's `model(id, slot)` request writes the bundle host's per-fighter
**held-model pair** (`development_animated_combat.hpp:2542`: `rena_held_models[i].at(slot) =
event.id`), which is initialised to `{0, 1}` and reset to `{0, 1}` on an attack-state change
(`:2493`). The port's counterpart is `m_trailItemModel`, initialised `{0, 1}` in
`FUN_0043ffc0`'s prologue (`fighter.cpp:1816`) — and its **consumer already implements the
clear**: `itemModel < 0` resets the trail (`fighter.cpp:751-755`). Only the **writer** refused
it (`MoveOp::PropModel` required `model >= 0`), which is exactly why the naive comparison
measured **0/148**.

**What was done.** The writer now accepts a negative model (behaviour-neutral: no shipped row
carries one — only Rena+1's 450/460, which bind model 2), and the pilot drives the clear behind
the flag. Driving it took three corrections, each found by measuring:

* the hook first tested `attack_move_id()`, which is `-1` for a shot — the recovered action id
  belongs to `shot_move_id()`;
* a one-shot write to `m_trailItemModel` does not survive, because the port **re-derives the
  slots every tick** from the move's trail binding (`fighter.cpp:1898-1903`), so the clear had
  to become part of that derivation (`Fighter::PilotShot::clears_item_models()`, consulted only
  when the pilot attaches the policy);
* the latch reset every frame because the pilot block runs once per frame from a function, so it
  now lives on `App`.

**Result:** the comparison went **0/148 → 144/148**. The residual four are a **one-tick lead**:
the body emits its clear from its frame 12 while the port's fire lands on tick 13, so on one
tick per shot the body has cleared and the port has not. That is named, not papered over.

**Stated plainly:** the clear has **no visible pixel effect at 640x360** in this scenario (the
flag-on capture is byte-identical to the flag-off one), so it is verified by *state* — the
observer's per-slot comparison — not by the capture. The three unchanged scenarios remain
byte-identical in capture and deterministic stdout with the flag off.

### 23h. Gap 3a, first pass: what the guard's flag words actually are (2026-10-16)

The owner asked for focused binary analysis so the guard predicate's proxy can go away. The
question was narrowed first, and the answer is better than a button mapping: **the three flag
terms are data fields, not inputs.**

**Established from the bundle's own pipeline, in three hops** (all cited, all in the local
bundle):

* `battle_hit_pipeline.hpp:23` calls `direct_and_guard_battle_hit(..., input.stagger.flags,
  input.attack_flags, ...)` — so the predicate's `victim_flags` is the **stagger input's**
  flags and `attack_flags` is the pre-damage input's;
* `actor_frame_hit.hpp:8` sets `p.pre.attack_flags = f.flags2c` — the **attacker's hit
  record** word at `+0x2c`. Bit 8 is the unblockable term, and the port **already parses that
  word** as `MoveEntry::attackFlags` (`combat_record.h:21`, read right after `combat[20]`);
* `development_animated_combat.hpp:3922` sets `p.pre.stagger.flags =
  live_body_contact_frame(v).flags28` — the **victim's live body contact frame** word at
  `+0x28`, which is where bits `0x400` (guard-capable), `0x2000` (guard from any angle) and
  `0x8000` (the contact-word OR) live.

**What that means for the predicate:** the attacker's term is expressible *today* from data the
port already has — no proxy needed. The victim's term is a per-frame data word of the victim's
current body frame, which is why the port's `Guard`-state proxy was a reasonable stand-in and
why it is not the same thing.

**Binary work done, saved under `local-data/harness/`** (binary pinned at
`sha256 27e61475…`): masked byte searches for the writes — no immediate-OR site exists for the
`+0x28` word with those masks, 31 stores to `+0x28` and 24 to `+0x2c` in total, and the one
function that writes both (`FUN_00427f40`) turns out to be a **record copy constructor**
(`memcpy` of `+0x28..+0x3c`), which is consistent with the words being copied data rather than
computed flags. Its three call sites (`0x427f1b`, `0x428017`, `0x42822b`, inside
`FUN_00427fe0`) drive a table-iteration copy through `FUN_004250c0`/`FUN_004260b0`.

**The remaining question, named:** where the port's parsed data carries the victim's **live body
contact frame** and its `flags28`. The port's `MoveEntry` flags sit at record offsets `0x82`/
`0x86` (its own `stateFlags`/`attackFlags`), which is the *hit* record, not the live body frame
the guard reads — so the two must not be conflated. `rena_dash_admission.h:13` already refers to
"current NN record flags28 & 0x100", so the port has *some* notion of that word; locating its
true source is the next bounded step, and it is what would let the predicate drop the proxy
entirely.

### 23i. Gap 3a closed: the guard's flags are the live records' words (2026-10-16)

The remaining question from §23h — where the victim's frame word lives — is answered, and the
answer is that **the port already parses both words and the proxy can go away**.

`CharacterMove::phases[].record_at(elapsed)` is the port's **live frame record** for the
current tick — exactly what the bundle's `live_body_contact_frame(v)` names — and its
`MoveEntry::stateFlags`/`attackFlags` are the two words the predicate reads. The new
install-backed `rena0_guard_flags_test` establishes that from the shipped data instead of from
a reconstruction: it walks every record of Rena+0 and reports

```
walked 276 records of Rena+0
guard-capable 0x400: 6 (first row 390); any-angle 0x2000: 0;
contact-OR 0x8000: 0; unblockable 8: 8 (first row 350)
```

Two things make that decisive rather than suggestive:

* the first record carrying `0x400` is **row 390** — the guard row whose body this pilot already
  adapted (`battle_guard_motion.hpp`, rows 390/391/392) — so the bit's meaning is confirmed by
  the row it appears in, not only by the predicate that reads it;
* the first record carrying **bit 8** is row **350**, an attack row.

And the two terms the pilot had recorded as "not expressible" are in fact **expressible but
unused by this combo**: `0x2000` and `0x8000` appear **zero** times in Rena+0's 276 records. So
nothing was inexpressible about the port's data — those bits simply never occur for Rena+0,
which is also why the port's behaviour never needed them.

**What the predicate becomes** (next step, and a v3 item): read the victim's and attacker's
**live records** rather than the port's `Guard` state proxy —

```
guarded = (|relative| <= 45° || (victimRecord->stateFlags & 0x2000))
          && (victimRecord->stateFlags & 0x400)
          && !(attackerRecord->attackFlags & 8)
```

That removes the proxy, expresses all three terms, and needs no new parsing — the records are
already reachable through the port's own accessor.

### 23j. The guard predicate now reads the recovered records (gap 3a implementation, 2026-10-16)

The proxy is gone. `Rena0PilotGuard::guards_hit` reads the victim's and attacker's **live frame
records** — `current_move_record()`, the same accessor the port's own dash admission uses for the
`flags28` word — and applies the recovered predicate verbatim:

```
guarded = (|relative| <= 45° || (victimRecord->stateFlags & 0x2000))
          && (victimRecord->stateFlags & 0x400)
          && !(attackRecord->attackFlags & 8)
```

All three terms are now expressed, and its diagnostics name each refusal (`no-record`,
`not-guard-capable`, `unblockable`, `outside-angle`) so a silent gate is impossible.

**One honest bridge.** The port's Guard state binds no clip or phase — its own note says so
(`state_move_id()` returns `-1` for Guard) — so a *human* fighter guarding has no live record for
the predicate to read. Running it that way first broke the guard fixtures (`dummy_hp` 99 instead
of 100), which is exactly the kind of thing that must be caught by measurement: the predicate
was right and the port had nothing to hand it. `Fighter::PilotGuardMotion` is the bridge — the
pilot supplies the recovered guard row's guard-capable record (`Rena0GuardRecord`, row 390, the
standing guard whose body this pilot already adapted), and the predicate prefers the victim's own
live record whenever the port binds one. The guard's own animation granularity (phases and the
20-frame hold counter) remains the named limit it was.

**Evidence after the change:**

| Check | Result |
|---|---|
| `rena0-guard-gate-pilot.fixture` | PASS, `asked=1 guarded=1 no-record=0` (100 HP) |
| `rena0-guard-gate-legacy.fixture` | PASS (99 HP, the legacy path untouched) |
| Live guard scenario | `asked=3 guarded=2 no-record=0 not-guard-capable=1`, P1 at **92 HP** (0+0+8) |
| Flag off vs on | capture differs; stdout differs **only** in the HP fields (90 → 92) |
| Locomotion / melee / shot with the flag off | capture **and** deterministic stdout identical |
| Suite | **82 tests, 0 failures**; differential 357 in-domain ticks, no unexplained divergence |

The `not-guard-capable` hit is the third swing, after P1's release — the predicate declining on
the recovered data rather than on a state proxy.

## 24. 2f repeated against the current evidence (P2-8, unattended run 2026-10-16)

The owner asked for the gaps to be finished or re-scoped and then for 2f to be repeated. This is
that repeat, run against the **approved v2** matrix plus everything closed since §21. Anything
that only becomes acceptance under the **proposed v3** is labelled as such and is *not* counted
here; acceptance stays **0/46**, the verdict stays pending, and no cleanup has started.

### 1. The approved matrix, run

`RENA0_FIXTURES: PASS (23 fixtures, 60 Hz, 21 case rows, 39 acceptance fields, 7 unsupported
declared, 3 unreferenced extras, skips=0)` — the eleven target cases plus the timed-round row,
every §2b acceptance field mapped to a fixture that asserts it, the seven unsupported fields
declared with reasons, and the three pilot extras (the two guard-gate fixtures and the
charge-spend fixture) reported as extras. **Those three are v3-dependent**: under v2 they are
not acceptance cases, which is exactly what "3 unreferenced extras" means.

Offline bodies, all green: locomotion 53, admission 24, shot 36, guard 26, **charge 29**,
**mode gauges 44**, **guard flags 4**, resolver 48 (including the pilot-path scans).

### 2. Binding, state, motion and events, compared

| Comparison | Result |
|---|---|
| Fixture-linked differential | **357 in-domain ticks**, no unexplained divergence |
| Locomotion (live) | 200 compared, **200 agreed** |
| Melee admission (live / suite) | 33 compared, **33 agreed** (11/11 in the suite) |
| Shot (live / suite) | 99 compared, **99 agreed**; fire 2/2, sound 2/2, voice 2/2 |
| Guard (live / suite) | 62 compared, **62 agreed**; 2/2 guarded contacts, 240 suite ticks |
| Mode gauges (differential) | attacker-hits 4, `charge1` **220** (55 per hit from column 50 through `50*100/90`) |
| Guard predicate (live) | asked 3, **guarded 2**, no-record 0, not-guard-capable 1 |
| Shot model requests | **144/148** agreed (was 0/148); the four are a one-tick lead |

### 3. Provenance

| Claim | Tier | Artifact |
|---|---|---|
| Acceptance observables and transitions | 4 (+2) | the fixtures, each citing an address or a recovered artifact (24 fixtures / 25 case rows / 44 fields after the Q19 correction) |
| Locomotion, melee admission, shot, guard bodies | 2 | `rena0_*_observation.h` from the cited bundle bodies |
| Charge gauge bodies | 2 | `battle_attack_charge.hpp` (0x63844e-0x6384fa), `battle_hit_charge.hpp` (0x6382d9-0x63844e) |
| Special-gauge control and parameters | 2 + 4 | `battle_special_gauges.hpp`; the actor DAT's header dwords via `header_values()` |
| `charge_gauge`'s launch and recovery | 2 | powered 402 emits row 7 with no subtraction (`FUN_0043ffc0.c:2009-2014`, `battle_rena_mobile_shooting.hpp:216-221`); row 403 adds 40/tick clamped at 1000 (`FUN_0043ffc0.c:2021-2040`). **Corrected 2026-10-22:** the former `FUN_00508a60:84-90` "spend" entry was a dash-cancel in another selector (Q19) |
| Guard predicate words | 2 + 4 | `FUN_00637950` lines 185-192; `rena0_guard_flags_test` (row 390 / row 350) |
| Shot model clear | 2 | `battle_rena_ground_shot.hpp:37` + the port's own consumer semantics |
| Flag plumbing and rollback | 4 | the four live A/B runs, the resolver scans |
| Original binary identity | — | `DaybreakDX.exe` sha256 `27e61475…`, re-verified this run |

### 4. Unresolved limits, named

`offset`/`movement` channels; the boosted melee arm; contact capacity; `elevation` derivation;
the statistics admission order; `move_counter`; the airborne cycle; the guard body's phases and
20-frame hold counter (the port binds no Guard record, so the pilot supplies row 390's
guard-capable record); the **+1/tick gauge refill** (identified, enclosing condition not
established); weapon 2's shot branch; the shot's spawn **positions** (tier-1 evidence); the
**hit/KO damage-and-death pipeline** (excluded by the owner's choice, fixtures as its only
evidence); the charge **move bodies** (generated stubs); and the contract's remaining
unsupported fields.

### 5. Rollback: flag-off restores the baseline, with no global resolver change

| Scenario | Deterministic stdout | Rendered capture |
|---|---|---|
| Locomotion | **identical** | **identical** |
| Melee | **identical** | **identical** |
| Shot | **identical** | **identical** |
| Guard | differs **only** in the HP fields (`hp=90` → `hp=92`); `hits=3`, `shots=0`, `sparks=0`, `fx events=3` identical | differs |

The guard difference remains the intended one — two guarded hits at zero damage instead of
`max(1, 8/5)` = 1 each — now produced by the **data-backed predicate** rather than a state proxy.
No global resolver change: with the flag off no pilot policy is attached, and the resolver's
scans (mutation-verified both ways) keep the resolver, adapter and observation bodies out of the
default path.

### 6. What this repeat does *not* claim

It does not claim acceptance: the three new cases and the `charge_gauge` promotion need the
**proposed v3** to be approved first, and until then they are extras and the field is still
listed unsupported. It does not claim original-runtime parity. And it does not change the
verdict: **2g stays the owner's**, with the pilot still experimental, freeze list A in force and
no cleanup started.

## 25. The dash-admission case, mapped end to end (P2-1/P2-4 continuation)

Section 24 left two bounded recovered-body/port differences open
([`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md), "Production `Match`/`Fighter` comparisons"). This
section pays the seam work the first one needs: one required pilot case — **grounded forward dash
admission** — traced from the equipped actor and item data through input, admission, the
requested state and the forbidden service, with every field's owner named and every value read
from the pinned install. The second difference (empty tap) is mapped in §26. Nothing here is an
integration yet; §27 records what the pilot flag then drives.

### 25.1 Identity: the body *is* the recovered selector

`slot7_body_0_0` is not a paraphrase. Its head (`slot7_native_bodies_20260929.hpp:10-65`) is
line-for-line the decompiled `FUN_00445ee0`'s head (`research/decompiled/FUN_00445ee0.c:12-60`):
the `w[0xa2]!=0` magazine charge, the three `100` modifier stores, `FUN_00435560(1)`, the
`+0x7f4`/`+0x7e0`/`+0x7e4` status overrides, the `0x846`/`0x844`/`0x845` rename arms and the
`+0x834 < 1000` `+1`. The command-1 dash branch (`:66-74`) is `FUN_00445ee0.c:62-70`, with
`n.w[0x2ac]` = `*(int *)(param_1 + 0xab0)`, `n.current_priority()` = `*(int *)(*(int *)(param_1
+ 0xade0) + 4)`, and `n.frame_flags` = `*(uint *)(*(int *)(param_1 + 0x10) + 0x28)`. So the body
is a **tier-2 recovered-code source** for this case, and the bundle's own `slot7_native_world.inc.hpp`
is only the host composition that lets it run. Named gap: the repo holds no reviewed decompilation
of `FUN_0041efe0`/`FUN_0041dcb0` (the command producer), so that half is bundle-source only —
`research/decompiled/FUN_0041efe0.c` was located during this pass and does corroborate the
command word (its `param_1[0x20c]` writes at lines 126/145/163/181 are the same four command
values), but it is not yet a reviewed symbol and is cited as located, not as endorsed.

### 25.2 Field map for the case

`w[K]` is the body's array index (`n.w[0x2ac]` = actor byte `0xab0`); the bridge writes by byte
offset (`slot7_native_world.inc.hpp:90-109`). Values in the "installed" column are read from
`data/rena/00.dat` (`sha256 acbd92ec…`) through the existing DAT workbench parser in this pass.

| Body word | Byte | Meaning | Port owner | Disposition | Installed value |
|---|---|---|---|---|---|
| `0x9e`/`0x9f` | `0x278`/`0x27c` | input axes, lateral/forward (ramped signed) | `PlayerState::down[Left/Right]`, `down[Up/Down]` | **product**, different domain | schedule is `Up, release, Up` (probe) |
| — | `0x830` | dash command word (1 fwd, 2 back, 3 left, 4 right) | none — the port's `m_lastTap[]` + `kDoubleTapSec` is a **named stand-in** | **(c) unresolved** | command `1` for this schedule (bundle helper + `FUN_0041efe0`) |
| `0xa0` | `0x280` | jump-held count | `input.down[Jump]` | **partial** | 0 |
| `0xa1` | `0x284` | melee-held count | `input.down[AttackA]` | **partial** | 0 |
| `0xa2` | `0x288` | shoot-held count | `input.down[Shoot]` | **partial** | 0 |
| `0xac`/`0xad` | `0x2b0`/`0x2b4` | jump/melee **released** counts | `compute_edges` `just_released` carries a bool, not a count | **partial** (not on this branch) | — |
| byte `0x84` | `0x84` | grounded byte | `!Fighter::airborne()` | **product** | 1 |
| `0x20d` | `0x834` | fighter charge/special gauge 0..1000 | `Fighter::charge_gauge()` (`m_chargeGauge`) | **product** | **0 (injected)** |
| `0x20c` | `0x830` | see above | see above | **(c)** | 1 |
| `0x2ac` | `0xab0` | priority **A** of destination row 20 | `CharacterMoves::find(20)->priority` | **product** | 0 |
| `current_priority()` | `0xadf4`→row | priority **B** of the current row | `find(action_state())->cancelThreshold` | **product** | 0 (row 0) |
| `frame_flags` | — | current frame's `flags28` | `current_move_record()->stateFlags` | **product** | `0x100` |
| `0x2b7b`/`0x2b7d` | `0xadec`/`0xadf4` | current action row / phase | `action_state()` / `move_phase()` | **product** | 0 / 0 |
| `0x2` | `0x8` | actor slot (voice receiver tag) | the `Fighter`'s match index | **product** | 0 |

Parser cross-check of the four compared words: row 0 A/B `0/0`, row 20 A/B `0/5`, row 400 A `40`,
phase-0 `flags28` `0x100` for rows 0/10/20/23/24/27 (rows 11/12 carry **zero** phases; row 28 is
the back-dash *cancel* row with all three phases flag-free; row 30 opens `0x200`). The port's
`stateFlags`/`priority`/`cancelThreshold` parse therefore equals the source table for this case
(`character_moves.cpp:82-101`).

### 25.3 The service the case uses, and the one it does not

The command-1 grounded branch calls exactly one service: `FUN_00421080(0x14)`
(`slot7_native_bodies_20260929.hpp:70`) = event kind `N`, address `0x421080`
(`slot7_native_control.hpp:70`), dispatched **synchronously** (`:59-63`). The host then
(`slot7_native_world.inc.hpp:36-51`) validates row 20 against the actor DAT, calls
`admit_remaining_melee_state(20)` → the `state_frames_` lookup and, for this state, the
attack-state arm (`development_animated_combat.hpp:1036`), binds the pose
(`bind_actor_animation_state(slot,20)` → set `state_frames_[20][0]`), and rewrites the bank's
state/phase/frame words. **The body does not bind the animation set itself**: it requests the
state and the host binds the row's phase-0 set. Verified against the install: row 20 phase 0's
`animation_index` is **13**, which is the set the production port binds on the same transition.

Not called on this branch: `FUN_0042c7b0` (event `R`, command-2 arms only), the magazine helpers
`FUN_00435560`/`FUN_0043f3e0` (head only), and `Y`/`A`/`V`/`v`/`P`/`T`/`Z`.

### 25.4 Where the port answers the same question

| Question | Recovered | Port today |
|---|---|---|
| Is this a dash request? | command word `+0x830 == 1` (and 2/3/4) | `m_lastTap[dir]` within `kDoubleTapSec` (0.30 s = 18 ticks at 60 Hz) and `just_pressed[dir]`, `fighter.cpp:828-838` |
| Which row? | command 1..4 → 20/27/24/23 grounded (`:66-116`, corroborated by `battle_roster_air_dash_admission.hpp:8`) | `dash_move_for(dir)`: Up 20, Down 27, Left 24, Right 23 (`fighter.cpp:1678-1702`) |
| Admission gate | `0 < +0x834` **and** `current_priority() <= priority_A(20)` **and** `flags28 & 0x100` and grounded | `programmed ? m_stamina <= 0 : m_stamina < kDashStamina` (`fighter.cpp:2945`); the priority-A comparison and the `0x100` window are **not** evaluated |
| Immediate state | `FUN_00421080(20)` → host binds state + phase-0 set in the same call | `set_state(FighterState::Run)` then `try_switch_animation()` resolves the set on the same tick (`fighter.cpp:2983-2990`) |

**CORRECTION (2026-10-22, owner observation + code re-check).** The paragraph that stood here
claimed a real recovered/port difference at gauge zero and said the port "drains the gauge
nowhere". Both were wrong, and the owner's observation — that in the original *only the stamina
meter interacts with a dash* — is what exposed it:

* `+0x834` **is the stamina meter**, and this port already applies the recovered dash rule to
  `m_stamina` at 1/10 scale. The recovered body's 12/tick drain
  (`dash_native_bodies_20260929.hpp:53`) is `LocomotionDefinition::dashDrain` **1.20** for Rena+0
  (`move_behavior.h`), applied at `fighter.cpp:1872`; the body's phase-1 exit at `+0x834 < 1`
  (`:96`) is the port's `m_stamina <= 0` exit at `:1883`; and the programmed gate at `:2951` is
  already `m_stamina <= 0 → refuse`, i.e. the recovered `0 < +0x834`.
* The measured "difference" was therefore an **injected-state artefact**: the probe forced
  `set_charge_gauge(0)` while stamina stayed at 100, a state the original cannot produce because
  the two port counters are one original resource.
* The pilot's `dash_gauge_refuses` consult has been **removed**. It read a counter that does not
  drain during a dash, so it could only disagree with the resource the port uses. The test now
  asserts the opposite and truer invariants: the recovered 12/tick equals `dashDrain × 10`,
  flag-on and flag-off enter the same row 20/set 13, a dash moves neither port counter's *charge*
  channel, and the seeded wrong gate (expecting the charge gauge to block) must fail.

What survives from this section as a genuine, still-open gap: the priority-A comparison and the
`flags28 & 0x100` window that the recovered branch also tests are **not** evaluated by
`try_dash` — they pass for the tested pair, so they change nothing here, but they are a real
difference for a case that depends on them. The command word `+0x830` likewise stays a named
stand-in for the port's double-tap history.

### 25.5 Two further dash facts this pass established, named rather than fixed

1. **The dash drains `+0x834` — the stamina meter — and the port already does it.** The
   grounded dash bodies decrement `w[0x20d]` by **12** per tick while `w[0x2b7d] < 2`, clamped
   at 0: `dash_native_bodies_20260929.hpp:53` (state 20), `:180` (23), `:290` (24), `:387` (27);
   state 30 (air) uses **11** and a further **3** in an inner arm (`:554`, `:572`), and the
   forward body ends phase 1 when the value reaches 0 (`:96`). The port's `m_stamina` is the same
   resource at 1/10 scale: `dashDrain` **1.20** (= 12 × 0.1) drained at `fighter.cpp:1872` for
   `m_phaseIndex < 2`, with the same phase exit at `:1883`. The one thing the port adds on top is
   a flat `kDashStamina` 20 trigger spend **for non-programmed dashes only** (`:2966-2972`), which
   is a port rule with no recovered counterpart — recorded, not defended. What remains genuinely
   unmodelled on this field is its **refill** side: the recovered `+40`/`+5` and `+1`/tick rates
   would be `4`/`0.5`/`0.1` per tick at the port's scale, while `m_stamina` regenerates at
   `kStaminaRegenSec` 60/s = 1/tick (`fighter.cpp:567`), and the separate `m_chargeGauge` carries
   the raw 0..1000 refill instead. That split is the port's two-models-of-one-resource problem,
   named in `PILOT-EVIDENCE-CONTRACT.md` V3-6 and deferred to the post-verdict cleanup.
2. **The dash's admission ceiling is a real comparison the port does not make.** `current_priority()
   <= priority_A(next)` passes trivially for the tested pair (0 ≤ 0), so it cannot change this
   case; it is recorded so a later case that does depend on it is not surprised.

### 25.6 What this map does not claim

It does not claim the dash *motion*, the drain, the phase-1 exit, the command word or the
port's double-tap window reproduce the original. It claims the case's admission question, its
fields, its one service and its one decision point are identified, that three of the four
compared values are read from the pinned install, that the body is the recovered function for
this combo, and that the one gate the port evaluates comes from a different field than the
source's. Original-runtime parity remains **not verified**.

## 26. The empty-magazine tap, mapped (the second recovered/port difference)

The second bounded difference in [`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md) is the same shape
as §25: the adapted body services a release the port drops on the floor. One voice, one
statistic, no state — and the wrapper that produces it is the reason the port's existing gauge
gate does not cover the case.

### 26.1 The branch, and the wrapper that makes it reachable

`slot7_body_0_0:172` opens the wrapper

```
(w[0xa0]==0 || w[0xa1]==0) || (w[0x20d] < 1) || (byte(0x84)==0 || w[0xcca] < current_priority())
  || ((frame_flags & 0x100) == 0)
```

and everything under it runs when the ordinary shot admission is *not* available — including
`w[0x20d] < 1`, the empty gauge. Inside it, `:178-182` is

```
0 < w[0xae] && w[0xae] < 0x14 && w[0x1b7] == 0
  -> FUN_00422560(w[0x2], 0x18, 10, 1)      // one voice, id 24
  -> w[0x2bd3] += 1                          // empty_shots, byte 0xaf4c
```

with **no `return`**: the body continues into the melee, jump and guard admissions, and the
shot-row branch at `:259` (`0 < w[0x1b7]`) is unreachable on this pass. So an empty tap is a
serviced refusal: a voice and a statistic, no state request, no magazine mutation, no
projectile. The published release counter is the previous frame's held shoot count
(`battle_human_input.hpp:31-37`; the host's twin at `development_animated_combat.hpp:1687-1688`),
so a one-tick press publishes 1 and satisfies the `1..19` window — the same shape
`local-data/harness/shot_release_rena0_probe.cpp` verified earlier.

Field census for the branch, all reads except the statistic:

| Body word | Byte | Meaning | Port owner | Disposition |
|---|---|---|---|---|
| `0xa0`/`0xa1` | `0x280`/`0x284` | jump-held / melee-held counts | `input.down[Jump]` / `down[AttackA]` | **partial** |
| byte `0x84` | `0x84` | grounded | `!airborne()` | **product** |
| `0x20d` | `0x834` | charge gauge (the wrapper's `< 1` term) | `Fighter::charge_gauge()` | **product** |
| `0xcca` | `0x3328` | priority **A** of row 390 | `find(390)->priority` | **product** (unused on this pass) |
| `current_priority()` | — | priority **B** of the current row | `find(action_state())->cancelThreshold` | **product** |
| `frame_flags` | — | current frame's `flags28` | `current_move_record()->stateFlags` | **product** |
| `0xae` | `0x2b8` | published release count | `compute_edges` gives `just_released`, a bool | **partial**; the branch's `1..19` window is what a one-tick tap satisfies |
| `0x1b7` | `0x6dc` | primary magazine rounds | `main_whole()` / `m_shootingMagazines[0].rounds` | **product** |
| `0x1c8`/`0x1cc` | `0x720`/`0x730` | secondary rounds / charge stage | the second `ShootingMagazine` | **product** (unused on this pass) |
| `0x2` | `0x8` | actor slot (voice tag) | the `Fighter`'s match index | **product** |
| `0x2bd3` | `0xaf4c` | `empty_shots` statistic | **no owner** — `CombatStats` is `{kos, deaths, damageDealt, damageTaken}` | **(c) unowned** |

The service is kind `v` at `0x422560`; the host derives the alternate-voice flag from
`active0||active1||active2` (`slot7_native_world.inc.hpp:60-63`), and the voice inventory's own
bank selection may pick a further choice — neither is modelled by the pilot, which publishes the
body's `id`/`priority` on the port's existing cue.

### 26.2 Why the port cannot reach it today

`Fighter::fire_shot` (`fighter.cpp`) returns from `can_fire` when the primary magazine reads
zero, before `m_shootingVoice` is ever set. Measured, reproduced this pass: six funded taps take
the real item-001 magazine 6 → 0 and a seventh one-tick tap reports `shotRequest=-1`, `voice=-1`,
`ammo=0`, `shotsSpawned=0`, with the saved log byte-identical to the recorded
`empty_shot_probe_v3.log` (`sha256 7c219504…`). The recovered body's answer for the same
conditions is one voice (`id 24`, `priority 10`, tag = slot) and one statistic increment.

Two properties of the port make this a hook and not a rewrite: the voice channel already exists
and is drained once per tick (`m_shootingVoice` → `take_shooting_voice()` → `MatchFrame::shotVoice[]`,
`match.cpp:289-291`), and the statistic has no owner at all, so publishing a number for it would
be inventing a field. The pilot therefore answers **only the voice half**; the statistic stays a
named unowned output (§2b's unsupported list is the right home for it, not a new `Fighter` member).

### 26.3 What is compared, and what is not

Compared by the pilot gate test: the voice id on the empty tap, the absence of any shot row, the
absence of a spawn, and the unchanged magazine — for the pilot path and, unchanged, for the
flag-off path. Not compared: the host's alternate-bank selection, the voice inventory's
choice resolution, the statistic, and whether the ordered voice arrives audibly. The observed
`row=0` on the empty tap is not a claim that the original's state is 0 (the wrapper's whole point
is that no state was requested); the compared fact is that no **shot row** was bound.

The empty-shot path's own sensitivity case lives in the same offline fixture as §25's:
`local-data/harness/rena0_slot7_gate_probe.cpp` (`sha256 b23bddd9…`)
asserts the voice's full argument tuple `(tag, 0x18, 10, 1)` and the statistic, and its
`--seed-wrong-gate` run must fail.

## 27. The pilot gate, implemented and pinned (P2-7 2e continuation)

§25 and §26 mapped the two differences; this section records what the pilot flag now drives and
what the evidence for it is. The two refusals are **entry-time decisions** — both were answered at
the port's existing decision point, with one method added to an interface the pilot already
owned, so no second permanent decision path exists and nothing is decided twice per tick.

### 27.1 The change, by file

| File | Change | Flag-off effect |
|---|---|---|
| `src/gameplay/fighter.h` | `PilotShot::empty_shot_voice()` (default `-1` = no opinion). The `dash_gauge_refuses` member this pass first added was **removed** — see the correction in §25.4 | none: the remaining hook is a virtual default consulted only through a non-null pointer |
| `src/gameplay/fighter.cpp` | one consultation in `fire_shot`'s `!can_fire` branch (the empty-tap voice). The `try_dash` consultation was removed with the member above | none: `m_pilotShot` is null with no policy attached, so the block is skipped and every legacy expression is unchanged |
| `src/gameplay/native/rena0_pilot_adapter.h` | `Rena0PilotChargePolicy` (the named pilot policy) and `Rena0PilotShotPolicy::empty_shot_voice()` = the body's voice id 24 | not compiled into the default path's behaviour |
| `src/main.cpp` | the pilot attaches the named charge policy instead of the bare base struct | none |
| `CMakeLists.txt` | registers `rena0_pilot_gate_test` (label `asset;feasibility`, `SKIP_RETURN_CODE 77`) | none |

Deliberately **not** published: the empty-shot statistic (`+0xaf4c`) has no port owner and is not
invented as a `Fighter` member. Deliberately **not** implemented here: the recovered dash gauge
drain (12/tick and its phase exit, §25.5 item 1) — a continuous effect with its own tuning rules,
recorded rather than approximated. Deliberately **not** claimed: that the port's double-tap
history (0.30 s window) reproduces the source's 15-frame command history; the port's window is a
named stand-in and its exact length is a separate question.

### 27.2 Evidence

| Check | Result |
|---|---|
| Offline recovered-body fixture, correct gate (`local-data/harness/rena0_slot7_gate_probe.cpp`, `sha256 b23bddd9…`) | **PASS**, 3 runs byte-identical |
| Same fixture with a **deliberately wrong gate** (`--seed-wrong-gate`) | **exit 1** — `gauge-positive command-1 dash must request state 20`; the comparison is sensitive to this gate |
| Production port, pilot path (`rena0_pilot_gate_test`) | dash resource pinned as stamina: the recovered 12/tick equals `dashDrain × 10`, flag-on and flag-off both enter row 20/set 13, and no dash touches the charge counter; empty tap → voice 24 with no shot row, no spawn, magazine untouched |
| Production port, **flag-off** in the same run | gauge 0 → row 20/set 13, stamina 98 (the recorded discrepancy reproduced exactly); empty tap → no voice. Both are asserted, so the flag-off control is part of the test rather than a separate claim |
| Same test with a **deliberately wrong expectation** (`--seed-wrong-gate`) | **exit 1** at the pilot refusal assertion |
| Repeatability | 3 runs of `rena0_pilot_gate_test` byte-identical stdout |
| Scripted port runs, flag-off vs flag-on (`melee-ground-300`, `locomotion-walk-turn`, `shot-ground-400`, `--headless --out`, 260 frames) | rendered captures **byte-identical**; the only stdout differences are the capture path and wall-clock timing lines (`RESULT: ok` on all six runs) |
| Full suite | `ctest`: **83/83 passed, 0 skipped** |

The scripted runs exercise the pilot's locomotion drive and leave the flag-off path untouched:
locomotion 200/200 compared (201 drive ticks), melee 33/33 (35), shot 99/99 (100), each with 0
disagreements. The two new refusals need the specific conditions (gauge 0, empty magazine) that
the dedicated test supplies, which is why it exists alongside them.

### 27.3 Limitations, named

Artifacts: `tests/rena0_pilot_gate_test.cpp` `sha256 d5f6e8bb…` (stdout
`b48456d4…`), `local-data/harness/rena0_slot7_gate_probe.cpp` `sha256 b23bddd9…`.

**Scope of the dash gate.** The source requires `0 < +0x834` on all four command arms, but the
pilot's consultation sits in `try_dash`'s `programmed` arm, which is the forward row 20 the port
adapts. The side (23/24) and back (27) dashes keep the legacy stamina gate on both flag settings,
because this port has no adapted body for those rows; extending the gate there is a separate
change with its own evidence. A side dash at gauge 0 is therefore still admitted on the pilot
path, and that is a named limit, not an oversight.

Tier 2 (the adapted body and its located decompilation) plus tier 4 (install-backed port checks).
The bundle's `/N` host composition is not the port's host, and the offline fixture's inactive
words are stated assumptions, not a reconstructed live actor. Not established: original-runtime
parity for either refusal; the dash drain or the command word (§25.5); the empty-shot statistic;
the voice bank/choice resolution behind the published id; and whether these two refusals are the
only entry-time differences in the slot-7 body — the remaining families are still §22's named
limits. The pilot gate test is an addition to the 2e comparison set, not a new acceptance case;
adding it to the contract's required set is a v3 decision for the owner.

## 28. 2f repeated against the v3 candidate (P2-8)

The owner asked for the v3 gate items to be finished or re-scoped and then for 2f to be repeated.
§25-§27 closed the two recalled refusals and mapped them; this section is the repeat, run on the
current source. Anything that only becomes acceptance under the **proposed v3** is labelled and
is *not* counted as accepted: **acceptance stays 0/46, the verdict stays the owner's, freeze list
A stands and no cleanup has started.**

### 28.1 The matrix, both manifests, from the current source

> **Historical snapshot (2026-10-16), superseded 2026-10-22.** The runner no longer accepts a
> scratch manifest with any name, and the approved v3 set is now **24 fixtures / 25 case rows /
> 44 fields / 6 unsupported** after the Q19 correction. The mutation results below describe the
> pre-approval state and are kept as the record; the current enforcement is in §29.

`rena0_fixture_test` reads its manifest from the directory it is handed, so the approved v2 file
and the proposed v3 list are the same runner and the same fixtures:

| Set | Manifest | Result | 3-run stdout |
|---|---|---|---|
| approved v2 | `tests/fixtures/rena0/MANIFEST.txt` | `PASS (23 fixtures, 60 Hz, **21 case rows, 39 acceptance fields, 7 unsupported declared, 3 unreferenced extras**, skips=0)` | byte-identical (`fce0e063…`) |
| proposed v3 | scratch dir + `MANIFEST-v3-proposed.txt` | `PASS (23 fixtures, 60 Hz, **24 case rows, 40 acceptance fields, 6 unsupported declared, 0 unreferenced extras**, skips=0)` | byte-identical (`4c8063be…`) |

The two logs differ in exactly the summary line, which is the point: the approved denominator has
not moved, and the revision's whole delta is three case rows plus one promoted field.

**Fail-closed on the new rows (mutations, scratch copies, tracked files untouched).** Deleting the
`charge_gauge` assertions from the spend fixture while its manifest line stands → `exit 1`,
`'rena0-charge-spend.fixture' does not assert field 'charge_gauge'` (the manifest's own field
check). Deleting the `case shot-gauge-spend` line → the run passes with `23 case rows`, i.e. the
proposed case row is *not yet* double-guarded by the runner's own constant — the runner's
`kRequiredCases`/`kRequiredFields` are the **v2** lists, so promoting the three rows into them is
part of the post-approval diff, not something this report may pre-empt. Recorded in §28.5.

### 28.2 The other evidence, re-run

| Check | Result |
|---|---|
| Offline bodies | 8/8 pass (locomotion 53, admission 24, shot 36, guard 26, charge 29, mode gauges 44, guard flags **12** (was 4), resolver 48) |
| Fixture-linked differential | `357 in-domain ticks, no unexplained divergence, skips=0` |
| Live locomotion (260 frames) | 200 compared, **200 agreed**, 201 drive ticks, 0 disagreements |
| Live melee (260 frames) | 33 compared, **33 agreed**, 35 drive ticks |
| Live shot (260 frames) | 99 compared, **99 agreed**, 100 drive ticks |
| Live guard pair (P1 guards, P2 attacks, 260 frames) | predicate `asked=3 guarded=2 no-record=0 not-guard-capable=1`; P1 ends at 92 HP with the flag on, 90 without |
| Pilot gate test | dash resource pinned as stamina (drain equivalence, flag-on/flag-off agreement, charge counter untouched); empty tap voices 24 with no row/spawn/ammo change; flag-off controls asserted in the same run |
| Full suite | `ctest` **83/83 passed, 0 skipped** |
| Seeded failures (intended, not passes) | `rena0_pilot_gate_test --seed-wrong-gate` and `rena0_slot7_gate_probe --seed-wrong-gate`, both exit 1 |

### 28.3 Rollback: flag-off restores the baseline

| Scenario | Rendered capture | Deterministic stdout |
|---|---|---|
| locomotion | **byte-identical** | **identical** |
| melee | **byte-identical** | **identical** |
| shot | **byte-identical** | **identical** |
| guard pair | differs | differs **only** in the HP fields (`hp=90` → `hp=92`) and the two `[split]` lines that print them; `hits=3`, `shots=0`, `sparks=0`, `fx events=3`, frames, balloon, BGM and `roundOver` identical |
| guard-attacker alone (P1 is the attacker, so the victim-side predicate is never asked) | **byte-identical** | **identical**; predicate `asked=0` |

The guard pair's difference is the intended one and is now produced by the data-backed predicate
rather than a state proxy. Repeatability of that pair: two repeats, one capture hash, one
stdout hash. No global resolver change: with the flag off no pilot policy is attached, and the
resolver test's scans still fail if any default-path file includes the resolver or the adapter.

### 28.4 Verdict criteria, evidence, and what is *not* claimed

| Criterion (`DIRECTION.md` §4 2g) | Evidence this round | Status |
|---|---|---|
| Repeatability | both manifests 3× byte-identical; guard pair 2×; suite green | met |
| Correctness | every expectation cited to addressed code or pinned DAT; the new refusals cite the adapted body **and** the located `FUN_00445ee0`; no invented load-bearing field (`+0xaf4c` stays unowned) | met for the accepted scope |
| Coverage | v2: 11 of 11 target cases; v3 candidate adds the guarded contact and the gauge spend | met for v2; the three v3 rows await approval |
| Seam and cost | §25-§27 field maps; hit/KO pipeline measured per stage; spawn point re-scoped; the generated-body layer measured at 1,815 bodies / 46-of-46 combos for the four core families | met |
| Test sensitivity | two seeded wrong-gate failures outside ctest, plus the manifest mutation above | met |
| Reversibility | flag-off identical for locomotion/melee/shot, guard differing only in HP; both controls asserted inside the gate test | met |
| Honesty | adapter/source equivalence, install-backed behaviour and original-runtime parity are reported separately; **no tier-1 trace exists**, so parity is *not verified* for any case | met |

Not claimed: acceptance (the three new rows and the `charge_gauge` promotion need the v3
signature), original-runtime parity, whole-game equivalence, that the port's dash **drain** or the
shot **spawn point** reproduce the original (both named approximations), or that the newly
promoted rows are load-bearing against the runner's own constant list (§28.1).

### 28.5 What is left, and it is one signature

Everything in the objective's list is either closed or explicitly re-scoped with its cost named:
the charge-gauge promotion and the three cases exist and run; the hit/KO pipeline is measured
(pure arithmetic core, bone/DAT-phase plumbing, one actor-services island) and recommended as the
owner's recorded exclusion; the shot spawn point is attributed to its real owner and declared an
approximation rather than asserted; the guard predicate and its "inexpressible" terms are pinned;
and the owner's completeness hypothesis has a measured counter-number.

**The remaining work is owner-only:** approve, amend or reject the v3 candidate
([`PILOT-EVIDENCE-CONTRACT.md`](PILOT-EVIDENCE-CONTRACT.md) V3-1…V3-5), which also decides
whether the three rows move into the runner's own required lists (§28.1's second mutation). Until
then the pilot is complete as an experiment and the scoreboard is unchanged.

## 29. Independent readiness check after v3 approval (2026-10-22)

**Supersedes §28.4's correctness/readiness verdict and §28.5's “one signature” claim.**
The owner approved the contract, not the truth of an erroneous source attribution. The current
12 pilot suites passed before this audit, but that alone did not establish acceptance safety.

### Done and reproduced

Three destructive *scratch* mutations passed the old runner (all exit 0): remove the legacy
comparison fixture and manifest row, replace the recovered guard case with plain guard-hold,
and rename the mandatory manifest to a decoy `.txt`. The runner now requires every approved
case/fixture pair independently and opens only `MANIFEST.txt`. A permanent seven-mutation
CTest regression rejects those three plus right-dash removal, `charge_gauge` declaration
removal, the powered-shot case's removal, and redirecting the required hit-damage observable
to a guard fixture while removing its hit-fixture assertion. Both case/fixture and
field/fixture pairs are independently checked.

The guard case's no-stun assertion now inspects the victim on the contact tick when the
recovered predicate accepts the contact; Guard must be retained, and at least one accepted
contact is required. This adds enforcement of an existing claim, not a new damage pipeline.

The CLI attachment site now uses `is_rena0_pilot_combo`: loaded character-0 actor metadata,
item 001 and valid equipped item data are required. Outside that domain all pilot pointers are
detached. Safety tests cover missing actor/item halves, a wrong character and an invalid item;
no other combo's gameplay was implemented.

### The source error, and the owner-approved correction that closed it

The audit found `PilotCharge` deducting 500 on a powered row-402 emission, with v3's required
fixture asserting it. The cited code did not say that: the **Rena+0** body
`FUN_0043ffc0.c:1968-2020` selects item row 1/7 on frame 13 with no `+0x834` subtraction
(helper: `battle_rena_mobile_shooting.hpp:216-221`), while `FUN_00508a60.c:76-114` charges a
directional **dash-cancel** out of 402 into state **30**, with matching generated statements in
`slot7_body_5_1:6466-6501` rather than Rena's selector. A scratch copy changing only the
expectations to 1000 failed at tick 25 (1000 expected, 500 observed) — the integration
difference, not a rebaseable number.

**Owner approved the correction (Q19, 2026-10-22), and it is implemented:**

- the `PilotCharge` interface, its `Rena0PilotChargePolicy` and the `MoveOp::Launch` deduction
  are **deleted**; the powered 402 launch now simply emits its shot;
- the removed case is replaced by two source-backed required cases —
  `rena0-powered-shot.fixture` (launches **bullet row 7**, `charge_gauge` unchanged, and a new
  `shot_bullet_row` observable separates it from the ordinary ground tap's row 0) and
  `rena0-shot-recovery.fixture` (the row-403 recovery's **+40/tick** with the 1000 clamp,
  `FUN_0043ffc0.c:2021-2040`). The recovery fixture starts from a below-cap gauge, which is a
  harness affordance and is labelled as one: with the misattributed spend gone the product has
  no path that lowers this counter, so the refill is otherwise unobservable;
- coverage did not shrink: 23 → **24** fixtures, 24 → **25** case rows, 40 → **44** asserted
  fields, 6 unsupported unchanged, and the enforcement regression grew to seven mutations;
- the empty-ammo release window the audit flagged as unverified is now implemented against the
  body's own condition (`0 < released < 20`, `slot7_native_bodies_20260929.hpp:172-182`): a
  held-frame counter replaced the collapsed seconds field, and the pilot regression pins 19
  frames voicing and 20 frames silent, flag-on and flag-off. Seeding the cap to 21 makes the
  20-frame assertion fail, so the boundary is load-bearing rather than decorative.

The duplicate stamina channels remain unsynchronized and are **not** covered by that answer:
the source HUD reads the very same `gauge` field (`runtime_battle.hpp:2221`), so matching drain
constants alone cannot prove the current split-counter integration. Further source-backed
coupling work cannot be relegated to ordinary post-green dead-code cleanup without a scope
decision.

### Limits and exact next action

No original runtime was launched; this is source-backed correction plus install-backed port
testing. V3 approval remains recorded with the Q19 correction applied, acceptance remains 0/46,
and 2h/other combos remain frozen. Verification after the correction: full current-source build
succeeded; **84/84 CTest suites passed, zero failures/skips**, the focused pilot campaign passed
**13/13**, the seven acceptance mutations are rejected, the 20-frame voice boundary is proven
load-bearing by a seeded off-by-one, and the diagnostic `--seed-wrong-gate` run still exits 1 by
design. No fresh captures or original-runtime observations were produced.

Next: no further source-correctness blocker is recorded for this slice. What remains before a
green recommendation is the owner's decision — the pilot verdict itself, and separately what to
do about the split stamina/resource channels, which is a frozen-path change and not a
post-green cleanup. A subagent model-routing limitation is recorded in Q20; no child was falsely
represented as GPT-6 Luna, and the coordinator directly read the source citations used here.

## 30. Scoping the split resource: one recovered meter, two port counters (2026-10-22)

Owner request: scope the `+0x834` split before deciding. This section **is the scope**, not an
implementation; nothing in the frozen decision path was changed to produce it.

### 30.1 What the recovered code actually does with the field

`+0x834` is one actor word with range **0..1000**. It is the HUD's stamina strip
(`runtime_battle.hpp:2221` → `battle_hud_draw_list.hpp:62-64` fills `stamina/1000`), and the
same word is spent, refilled, gated and clamped by the action bodies:

| Rule | Value | Citation (per-combo bodies; counts are over all 46) |
|---|---|---|
| dash, states 20/23/24/27/28 | **−12/tick**, clamp 0 | `dash_native_bodies_20260929.hpp:53,180,290,387`; Rena+0's five bodies all use `-0xc` |
| dash, state 30 (air) | **−11** and **−3** in an inner arm | same file; Rena+0 state 30 = `['-0xb','-3']` |
| other dash-family rows | −3, −5…−15 | 276 clamp-0 sites across the roster's dash bodies |
| guard 390, phase 1 | **−10/tick**; phase exits when the word reaches 0 | `guard_native_control.hpp:38-42` (`m.gauge = max(0, m.gauge-10)`, `!m.gauge` → phase 2) |
| jump rows | −10, and −4/−6/−12 on other rows | `jump_native_bodies_20260929.hpp:133` etc. |
| shoot rows | −5, −11 | `shoot_native_bodies_20260929.hpp` |
| recovery rows (403 and family) | **+40**, or **+5** when hit-status slot 6 is set, clamp 1000 | `FUN_0043ffc0.c:2021-2040`; 228 of each across the bodies |
| mode-2 special active | **+1/tick**, clamp 1000 | `FUN_0041f580.c:97-98`; `slot7_native_bodies_20260929.hpp:63` (46 sites) |
| dash / melee admission | must be **> 0** | `FUN_00445ee0.c` (dash arms), `slot7_native_bodies:68-104` |
| shot admission | must be **> 0** | `FUN_00445ee0.c:172` (`+0x834 < 1` excludes the ordinary arm) |
| directional dash-cancel out of 402 | **−500** | `FUN_00508a60.c:76-114`; the two Rena selectors that carry it are *not* Rena+0 (Q19) |

**No passive refill was found.** `FUN_0041f580`'s only unconditional `+1` is behind the mode-2
special flag, and every other refill in the bodies is attached to a recovery row. A grounded
"wait and recover" rule is **not** in the recovered update.

### 30.2 What the port does today

Two counters, never synchronized, at two different scales:

| Behaviour | Port | Effective per tick | Source-equivalent | Status |
|---|---|---|---|---|
| dash drain | `dashDrain` 1.20 (Rena+0) | 1.20 | 1.2 | correct for 5 of 6 dash states; **air dash (30) uses 1.2 where the source uses 1.1 or 0.3** |
| guard drain | `kGuardDrainSec` 25/s | 0.4167 | 1.0 | **2.4× too slow** — `rena0-guard-hold.fixture` pins `stamina 75` at tick 59 and `guard_exhausted 1` at tick **245**; the recovered rate exhausts in ~100 ticks |
| grounded regen | `kStaminaRegenSec` 60/s | 1.0 | none | **port rule with no recovered counterpart** |
| recovery +40/+5 | `MoveOp::Recharge` | +40 (raw) | +4 at 1/10 | right number, **wrong counter**: it lands on `m_chargeGauge`, which nothing drains |
| mode-2 +1/tick | absent | 0 | 0.1 | missing |
| jump launch | `kJumpStamina` 10 per leap (legacy only) | −10 event | none — no body charges a launch spend | **port rule, pilot path removed it**; row 40 refills +40 on the launch tick instead |
| hover drain | `kFlyDrainSec` 30/s (legacy) | 0.5 | −10/tick while gravity reads zero | pilot path uses the recovered row-41 hover rate (−10; Rena+0, variants named); legacy keeps its port rule |
| legacy dash trigger spend | `kDashStamina` 20 | −20 event | none | port rule, non-programmed dashes only |
| dash / melee / shot admission | `m_chargeGauge <= 0` | — | `> 0` | **unreachable**: no product path lowers this counter, so the gates never fire |
| HUD | `stamina()/100` | — | `g/1000` | shape right, live counter's numbers |

**The sharpest consequence:** the counter that gates attacks is provably inert, and the counter
that drains has no refill. A battle-length run keeps `m_chargeGauge` pinned at 1000, so the
recovered "you cannot attack with an empty meter" rule can never fire in this port, while the
HUD bar refills four times slower than the recovered rows would make it.

### 30.3 Options

**A — one meter, source-shaped (recommended).** Replace both with a single `int` 0..1000 in
`Fighter`; `stamina()` keeps returning `meter/10` so the HUD and observers do not change shape;
delete `m_chargeGauge`. Rates become the recovered integers: dash −12/−11/−3 per state, guard
−10 per phase-1 tick, recovery +40/+5 clamped at 1000, mode-2 +1/tick, no passive regen.
Implement behind `--native-actions=rena0` first so the blast radius stays the pilot, and
generalise at Phase 3.
*Sites:* ~17 in `fighter.cpp`, 6 constants + 3 members/accessors in `fighter.h`, 2 in `main.cpp`,
4 test files, 1 fixture, plus a contract amendment because `stamina` is an **asserted acceptance
field** whose pinned values change.
*Cost:* one focused change of the size of the guard/shot slices already accepted.
*Risk:* medium. It changes observable pilot behaviour (guard exhaustion ~2.4× faster, a real
low-meter refusal, a dash that visibly recovers), and it edits frozen files.
*Rollback:* flag off — the legacy path is untouched, exactly as with the other pilot slices.
*Unknowns it cannot close:* the state-30 air-dash split (−11 vs −3) needs a branch decision; the
fly drain needs a citation or must stay labelled a port rule.

**B — mirror writes.** Keep both counters and write each through the other at 10:1.
~6 sites, no behavioural redesign, but it institutionalises two sources of truth and violates
the "no permanent shims" rule. Acceptable only as a stopgap with an expiry, not recommended.

**C — document only.** Keep today's behaviour, record the table above as a known limit and let
the verdict proceed. Cheapest, but leaves an invented load-bearing refill rule and an inert
admission gate inside the pilot's accepted path, which is what the 2g correctness criterion is
meant to catch.

### 30.4 Recommendation and what approval would authorise

Recommend **A, behind the pilot flag**, in one reviewed change, together with the contract
amendment that re-pins the `stamina` expectations it changes. That keeps the pilot honest —
the meter it asserts is then the meter the source has — and it retires the largest remaining
mechanism-level divergence instead of deferring it into a cleanup whose scope was never agreed.

Approval should say, concretely: *unify the meter for Rena+0 behind the flag, re-pin the affected
`stamina` expectations, keep the legacy path intact, and record the fly drain and the state-30
branch as named limits if they cannot be closed in the same change.* Because this edits frozen
files, it also needs an owner exception row in `EXCEPTIONS.md` (dated, expiring, naming
`fighter.cpp`/`fighter.h`/`main.cpp` and the pilot tests) — this document cannot write that row.

### 30.5 What this scope does not claim

It does not claim the original's meter behaves identically in match conditions (no tier-1 trace),
does not decide what a 500-unit dash-cancel means for the other combos, and does not touch the
hit/KO or spawn-point exclusions. It is a source-backed statement of one mechanism and three
bounded ways to close it.

### 30.6 Implementation record (2026-10-23, owner-approved option A)

Implemented exactly as §30.4 scoped, behind the pilot flag:

- `Fighter` carries `m_actionMeter` (0..1000), authoritative only when a `PilotMeter`
  policy is attached — by `--native-actions=rena0` for Rena+0, and by the acceptance
  runner for its fixtures. `stamina()` reads `meter/10` on the pilot path (the HUD
  fraction is now exactly the source's `g/1000`); `charge_gauge()` reads the meter;
  `set_charge_gauge()` writes both stores so the test seam doubles as the meter injector.
  The default path reads and writes the legacy pair exactly as before.
- **Standing refill (added 2026-10-23, binary-backed):** executor case 0
  (`FUN_0043ffc0`) adds **+40/tick** (5 with hit-status slot 6), clamped at 1000, on any
  tick that was already standing before input. Every other figure below is in addition.
- Rates are the recovered integers at every call site, each with its citation: dash
  −12 (grounded states) / −11 (air 30), guard −10/tick with exit at 0, jump launch
  row-40 refill +40 and landing-transition +40 (one tick of the row-44 rule),
  hover −10/tick while gravity reads zero (row 41; Rena+0, combo variants named),
  recovery +40/+5 clamped at 1000, mode-2 +1/tick, standing +40/tick, and no launch
  spend (no jump body charges one; the row-41 spends are all hover-gated).
- Measured, not assumed: the gate test pins exactly one −12 drain on the admission tick
  (1000 → 988), pilot refusal with flag-off admission at empty meter, and the seeded
  wrong-gate (admitted-at-zero) failing; guard exhaustion lands at tick **99** as the
  source rate predicts; the standing refill climbs 440 → 560 → 680 at +40/tick and clamps at 1000
  (idle-refill fixture); the jump-chain fixture pins 900 → 980 on the launch tick and
  the clamp on landing; the recovery fixture pins its tail from a 400 start.
- Verification: full current-source build, **84/84 CTest suites, zero failures/skips**;
  focused pilot campaign **13/13**; seven-mutation fail-closed regression all rejected;
  `git diff --check` clean. No other combo's behaviour changes: every new branch is
  behind the pilot policy, and the four non-pilot `charge_gauge`/`stamina` test readers
  run the legacy path unchanged.
- Carried-forward limits, narrowed by the correction: the state-30 −3 inner arm (port
  has no state-30 frame clock); row-41 combo spend variants (port knows only its own
  hover); jump-row durations beyond the port's single launch tick and the single
  landing tick; guard phase granularity; legacy fly rate off the pilot path;
  Kakera mapping for the mode-2 refill. The contract amendment is V3-8 (extended
  below); the re-pinned values are acceptance expectations again, not observations.
