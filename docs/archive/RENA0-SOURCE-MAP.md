# Rena+0 source map in the Ginkiha bundle

This is a **navigation inventory**, not a port plan, completeness claim, or
original-runtime comparison. It records static source references in the ignored
bundle at `.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/`. All paths
below are relative to that bundle's `source/src/` directory. No bundle file was
changed, no executable was run, and no behaviour was accepted by making this map.

The scope is **Rena+0 only**: character index `0`, weapon slot `0`. The roster
identity is explicit in `character_dispatch.hpp:9` (constructor `0x0064c840`,
vtable `0x006a4e10`, update `0x0043ffc0`). `character_names.hpp:6` names the
asset directory `rena`. `character_asset_files.hpp:13-26` constructs
`data/rena/00.dat` for weapon slot 0 and reads the item ID from that DAT's
parameter 3 before constructing `data/item/%03u.dat`; the item ID is not
established merely by searching for `weapon==0` in source. The repo's F1-5
install-backed record reports loading `data/rena/00.dat` with item 001
(`DIRECTION-STATUS.md`, F1-5 work log); this inventory did not rerun that check.

## How this inventory was made

- Enumerated `battle_rena*` and `rena_*` filenames.
- Searched the bundle's C++ source for `rena`/`Rena`, explicit character-0 and
  weapon-0 conditions, and generated `*_body_0_0_*` functions.
- Followed callers from the normal graphical entry point through roster loading,
  action binding, the combat frame, action dispatch, and item-1 projectile tick.
- Checked dispatch predicates before treating a generated body as Rena+0 code.

A text match is a lead, not proof that a path executes for Rena+0. Conversely,
shared code selected by DAT rows or a generic dispatch may affect Rena+0 without
spelling its name or indices. The graphs below are **static call routes**;
conditionals and actual DAT contents determine which route runs on a frame.

## Files whose names identify Rena

These 13 files cover all `battle_rena*` and `rena_*` filenames in the exported
`source/src/` tree. Most contain branches for weapons 0, 1, and 2; their entire
contents must not be attributed to Rena+0.

| File | Rena+0 role or entry |
|---|---|
| `battle_rena_melee.hpp` | `rena_melee_action_state` and `advance_rena_melee`; routes the 300 family, 320, 329-334, 340-341 (`:14-53`). |
| `battle_rena_melee_admission.hpp` | 300-family selection; weapon-0 continuation conditions for 301→302 and 340→341 (`:7,27-29`). |
| `battle_rena_ground_melee.hpp` | Routes ordinary, follow-up, and directional ground melee (`:7-12`). |
| `battle_rena_ordinary_melee.hpp` | State-300 ordinary melee; weapon-0 effects and steering (`:14,37,47`). |
| `battle_rena_followup_melee.hpp` | 301/302 follow-up; weapon-0 branch (`:6,21-27`). |
| `battle_rena_directional_melee.hpp` | 310/311 directional melee; weapon-0 motion and effect branches (`:7,39-45`). |
| `battle_rena_ground_dash.hpp` | 329-331 dash melee; weapon-0 branch (`:6,34`). |
| `battle_rena_landing_melee.hpp` | 340/341 landing melee (`:7`). |
| `battle_rena_ground_shot.hpp` | State 400; weapon-0 branch begins at `:36`, with ordered model, sound, voice, shot and projectile requests. The host performs magazine and spawn work (`:20-24`). |
| `battle_rena_mobile_shooting.hpp` | Rena+0 states 401-409, 450, 460 (`:10-12`) and ordered projectile requests. Its `rena_mobile_input` defaults (`:22-50`) have no runtime caller; the live path builds the profile from loaded data (`development_animated_combat.hpp:2576-2589`). |
| `battle_rena_full_charge.hpp` | For weapon 0, recognizes 350, 360, 370, 469 (`:14-20`); its weapon-0 action branches begin at `:93`, `:98`, and `:130`. |
| `rena_dash.hpp` | Air-dash step and ground-dash tuning by weapon; weapon-0 speed branch (`:14-20`). |
| `rena_projectile_switches.hpp` | `tick_item1_projectile` for the item-1 projectile family (`:4`). Reached through the item dispatcher described below. |

## Other files that literally mention Rena

The case-insensitive `rena`/`Rena` search found **35 C++ files** in total. The
13 above have Rena in their names. The other 22 are grouped here so the next
reader can distinguish runtime ownership from comments, diagnostics, and
weapon-1/2 exceptions.

| Group | Files and why they surfaced |
|---|---|
| Identity, scene, diagnostics | `character_names.hpp` (name), `battle_action_binding.hpp` (Rena policy), `development_animated_combat.hpp` (live action routes), `runtime_main.cpp` (selection smoke), `runtime_battle.hpp` (render fixtures), `battle_network_runtime.cpp` and `battle_runtime_options.hpp` (diagnostic smoke/options). |
| Related action/control | `battle_attack300_motion.hpp`, `battle_chasing_air_melee.hpp`, `dash_melee_native_control.hpp`, `directional_melee_native_control.hpp`, `remaining_melee_native_control.hpp`, `roster_ground_melee.hpp`, `roster_full_charge_admission.hpp`, `roster_walk_shot_admission.hpp`, `roster_weapon_trail_policy.hpp`, `actor_animation_service.hpp`, `battle_victory_identity.hpp`. Check each actual branch: some mentions are about Rena+1 or Rena+2 only. |
| Projectile and CPU | `remaining_roster_projectiles.hpp` (item-1 dispatcher), `projectile_asset_files.hpp` (Rena weapon-1 asset comment), `roster_cpu_decisions.hpp` (`advance_rena_0` and character-0 CPU dispatch). |
| False positive for Rena bodies | `shoot_native_bodies_20260929.hpp` says on line 1 that its generated State400-469 bodies are **non-Rena**. Its Rena text match is not a Rena+0 shooting body. |

## Explicit Rena+0 selectors outside Rena-named files

| Route | Source location | What the selector establishes |
|---|---|---|
| Actor identity | `character_dispatch.hpp:9`; `battle_action_binding.hpp:13-15` | `(0,0)` exists, and character 0 selects the `rena_melee` action policy. |
| Asset identity | `character_asset_files.hpp:13-26` | `data/rena/00.dat` supplies frame/animation data and points to the item DAT. |
| Locomotion | `roster_locomotion_native_control.hpp:26-57` | Shared State 0/10 body includes a `(0,0)` late-vertical rule at `:41`. |
| Jump and air dash | `battle_jump_motion.hpp:29`; `battle_roster_air_dash.hpp:7`; `roster_air_dash_cancels.hpp:9,16` | Rena+0 landing-gravity, air-dash and cancel branches. |
| Shot/admission | `roster_ground_shot_admission.hpp:21`; `roster_walk_shot_admission.hpp:15-20`; `roster_full_charge_admission.hpp:7,16`; `battle_empty_shot.hpp:9` | Character-0 or `(0,0)` admission and empty-magazine cases. |
| Melee/recovery | `battle_dash_melee.hpp:20`; `battle_dash_followup.hpp:42`; `battle_chasing_air_melee.hpp:21`; `roster_state341.hpp:17,43,53,61` | Shared policies with character-0 and weapon-0 branches. |
| Presentation | `held_weapon_pose.hpp:14-15` | Rena+0 model hiding at State 400 and a Rena weapon-0 State-350 branch. |

Searching for `weapon==0` alone is **not** a Rena+0 inventory: many such rows
refer to other characters, and zero-valued member initializers are not combo
selectors. The entries above were filtered by character, an owning Rena-specific
function, or an actual dispatch path.

## Generated bodies keyed to character 0, weapon 0

The generated-body naming convention encodes `character_weapon_state`. These
are the `*_body_0_0_*` definitions found in exported headers, not a claim that
every state is reached in the selected match:

| Header | Rena+0 definitions | Dispatch/host |
|---|---|---|
| `slot7_native_bodies_20260929.hpp:3` | `slot7_body_0_0` | `dispatch_slot7_body` selects case 0 at `:18922`; world bridge in `slot7_native_world.inc.hpp:10`. |
| `dash_native_bodies_20260929.hpp:3-512` | 20, 23, 24, 27, 28, 30 | `dash_native_control.hpp:23-28`; `development_animated_combat.hpp:1225,2070-2072`. |
| `jump_native_bodies_20260929.hpp:3-323` | 40-44 | `jump_native_control.hpp:35-40`; `development_animated_combat.hpp:1195,2074-2076`. |
| `remaining_melee_native_bodies_20260929.hpp:408-797` | 332-334, 340-341 | `remaining_melee_native_control.hpp:138-153`; `development_animated_combat.hpp:2367-2380`. This shared-body route is checked before attributing those states solely to `advance_rena_melee`. |
| `full_charge_native_bodies_20260929.hpp:3` | 351 | Binding case `351` at `:13804`; bridge in `full_charge_native_world.inc.hpp:16,109`. State 351 is distinct from the Rena-named 350/360/370/469 helper. |

## Static call routes around Rena+0

### Selection to combat update

```text
runtime_main.cpp:293                Runtime creates battle scene
  -> runtime_battle.hpp:1141-1142    load_basic_battle_roster_assets;
                                     construct DevelopmentAnimatedCombat
  -> basic_battle_roster_assets.hpp:22
  -> battle_action_binding.hpp:13-15 basic_battle_action(0, 0)
  -> character_dispatch.hpp:9       original update identity 0x0043ffc0

runtime_main.cpp:186-205            local input calls RuntimeBattle::update
  -> runtime_battle.hpp:1648         selected frame update
  -> runtime_battle.hpp:1675-1679    move_with_projectile_scripts
  -> development_animated_combat.hpp:1543
  -> development_animated_combat.hpp:1691  slot-7 admission
  -> slot7_native_world.inc.hpp:10
  -> slot7_native_bodies_20260929.hpp:18922  slot7_body_0_0
```

With native slot 7 enabled, a recovered action binding, a weapon item, and an
eligible actor, `development_animated_combat.hpp:1689-1692` calls that slot-7
body and continues the admission loop. The later hand-written admission block
therefore does not establish Rena+0's effective admission order on this path.
The next body dispatch is conditional on state and ownership. Optional native
shooting, full charge and special strike checks come before shared dash and
jump at `development_animated_combat.hpp:2060-2076`; guard and locomotion at
`:2220,2256`; remaining melee at `:2367-2380`; and Rena-specific melee,
350/360/370/469, State 400, and mobile shooting at `:2482-2591`.
`shoot_native_world.inc.hpp:8` gates its generated shooting bodies through
`shoot_native_body_binding`; the generated file is explicitly non-Rena. Do not
route Rena+0 State 400 through it just because the state number overlaps.

### Inside Rena+0's generated slot 7

`slot7_body_0_0` spans `slot7_native_bodies_20260929.hpp:3-398`. These are
**conditional requests visible in generated source**, not proof that all
branches are reachable with shipped Rena+0 data:

| Source span | Admission group |
|---|---|
| `:10-65` | Magazine/mode setup and combat modifiers. |
| `:66-119` | Dash commands, including ground states 20/23/24/27/28 and air 30. |
| `:121-170` | Special-mode activation and state requests, with a partner check on one path. |
| `:172-305` | Charge, ground, air, and moving-shot requests, including 400, 401/402, 405-408, 450/460 and 360/370. |
| `:308-395` | Melee, recovery, jump, air-dash and guard requests, including the 300 family and guard 390. |

The body tests current state, input counters, priority rows, frame flags,
contact, ammunition and special-mode words. `Slot7BodyContext::event` calls its
world service **before the generated body continues**
(`slot7_native_control.hpp:59-63`). The `(0,0)` body uses `N` (state/pose
admission), `R` (contact query), `A` (special activation), `V`/`v` (voice), and
`P` (partner snapshot), mapped in `slot7_native_world.inc.hpp:20-77`.
Magazine helpers `FUN_0043f3e0` and `FUN_00435560` mutate its bank directly
(`slot7_native_control.hpp:79-86`); they are not world callbacks. The source
body does not call the available `Y`, `T` or `Z` callbacks in this span.

### Melee helper tree

```text
development_animated_combat.hpp:2482-2484  advance_rena_melee
  -> battle_rena_melee.hpp:19-53
      -> battle_rena_ground_melee.hpp:7       300/301/302/310/311
      -> battle_chasing_air_melee.hpp         320
      -> battle_rena_ground_dash.hpp:6       329/330/331
      -> battle_dash_melee.hpp                332
      -> battle_dash_recovery.hpp             333
      -> battle_dash_followup.hpp             334
      -> battle_rena_landing_melee.hpp:7      340/341
```

The body loop may take the generated remaining-melee route for a supported
state before reaching the Rena-named helper (`development_animated_combat.hpp:
2367-2380`). This is a source-order warning for the agent checking actual
ownership; the diagram is not a runtime trace.

### Shooting to projectile lifecycle

```text
development_animated_combat.hpp:2492-2531  Rena full-charge family
  -> battle_rena_full_charge.hpp:49

development_animated_combat.hpp:2532-2561  State 400
  -> battle_rena_ground_shot.hpp:24
  -> ordered host event callback: model, voice, statistics, projectile request

development_animated_combat.hpp:2562-2626  mobile shooting
  -> battle_rena_mobile_shooting.hpp:81

runtime_battle.hpp:1672-1679             spawn requests; advance projectile scripts
  -> local_normal_projectiles.hpp:481    remaining-roster pool tick
  -> remaining_roster_projectiles.hpp:12 item 1
  -> rena_projectile_switches.hpp:4     tick_item1_projectile

runtime_battle.hpp:1692                  resolve combat/projectile contacts
```

The body callback can request a projectile while the host may reject it at
magazine admission; `battle_rena_ground_shot.hpp:20-24` explicitly separates
those operations. File presence or a shot-event row alone does not prove a
projectile was born, contacted a target, or dealt damage.

For State 400, `development_animated_combat.hpp:2540-2558` passes an ordered
callback to the body. The callback reaches
`append_actor_projectile_request` (`:931-960`), which reads the item bullet row,
consumes its magazine if applicable, resolves the attachment socket and only
then queues a request. The pool's later spawn can still fail. For mobile
shooting, the live caller reads bullet/magazine metadata and phase durations
from the loaded item and actor DATs (`:2576-2589`); the convenience defaults in
`rena_mobile_input` are not the production profile. `local_normal_projectiles.hpp:
513-525` resolves contacts after the projectile script/motion passes.

## Second-pass Rena+0 coverage boundary

The installed `data/rena/00.dat` has **122 state rows**: 16 in `0-99`, 65 in
`100-299`, 24 in `300-399`, 13 in `400-499`, and 4 in `500-503`. The
33 literal slot-7 targets, from 46 `FUN_00421080` call sites, are only a subset
of those rows; they are enumerated under **The slot-7 request set** below. A
conservative walk of local quoted `#include` statements from
`development_animated_combat.hpp` reaches
**343 files**, only 12 with `rena` in the filename. This is a syntactic
dependency count, not the number of files executed by Rena+0. It explains why
the 13 named files and 35 literal-name matches cannot be a complete port
inventory.

### The one live admission owner

As the route diagram above notes, with `enable_native_slot7`, a recovered action
binding and a non-empty `actor_assets(i).weapon_item`,
`development_animated_combat.hpp:1690-1693` calls `advance_native_slot7_body`
and `continue`s. For Rena+0 in the F1-5 configuration (`data/rena/00.dat`, item
001) that generated body is therefore the **only live admission owner**. The
admission block that follows (`:1694-2038`) is the **fallback** path, taken only
when the slot-7 body is disabled, the actor is not recovered, or the item did
not load; the handler chain resumes at `:2054`. The fallback contains `rena_dash_admission` (`:1807`),
`start_special_chord` (`:1748,1838`), `roster_awakened_strike_state` (`:1841`),
the ordinary guard gate (`:1754,1849`), `roster_full_charge_admission`
(`:1870`), the ground/walk shot table (`:1914-1918`),
`roster_followup_shot303_admission` (`:1968`), `rena_melee_admission` (`:1986`),
`roster_ground_dash_melee_admission` (`:2000`) and
`roster_ground_combo_admission` (`:2023`). None of those hand-written admission
tables is cover for this combo while the slot-7 body runs: on this path they are
never reached.

| State family in Rena+0 DAT | Source owner found | What remains unproved |
|---|---|---|
| Idle/walk `0/10`; dash `20/23/24/27/28/30`; jump `40-44` | Shared locomotion (`roster_locomotion_native_control.hpp:26-57`), six generated Rena+0 dash bodies, five generated jump bodies; selected in `development_animated_combat.hpp:2069-2076,2251-2257`. | Rows `11/12` have **no owner found**: no entry and no handler exists anywhere in the recovered source, as against "not yet identified". Body presence does not establish every input route or motion/contact parity. |
| Reaction `100-299` (65 rows) and landing/hit `45` | `battle_common_hit_motion_state` selects 39 installed reaction-range rows (`battle_common_hit_motion.hpp:32-37`); `battle_death_motion_state` covers nine `191-199` rows; shared recovery bodies own `124/128/187/190` (`shared_recovery_native_20261004.hpp:54-57`, `shared_recovery_bodies_20261004.hpp:388-399`). Contact resolution and reaction loops run through `development_animated_combat.hpp:3283-3372,3914-4033`. | The thirteen flagged rows need no named requester: they are selectable through the attacker DAT fields `0x64`/`0x68`. Nine of them — `117,122-123,125-127,129,132,232` — also have **no handler**, so a selected row falls to the generic reaction tick, which advances the DAT animation but never selects a new state. Whether a shipped Rena+0 attacker frame selects any flagged row is a DAT-content question this bundle cannot settle. See **Ownership verdicts for the flagged rows**. |
| Melee `300-302,310-311,320,329-334,340-341` | Rena dispatcher and shared controls (`battle_rena_melee.hpp:14-53`); generated remaining-melee bodies win for `332-334/340-341` (`development_animated_combat.hpp:2367-2380`), and for Rena+0 they are the only route to those states. | Each branch still needs input/context and event tests. Row `303` has **no owner found for Rena+0**: every reference is character-11/weapon-0 gated and the follow-up handler throws for other combos. |
| Charge/special-melee `350/351/360/370`; guard `390-394`; special entry `500-503` | `battle_rena_full_charge.hpp:14-20` owns 350/360/370; `full_charge_body_0_0_351` exists and the `(0,0)` binding has only case `351` (`full_charge_native_bodies_20260929.hpp:3,13804`). Shared native guard handles 390-392 (`guard_native_control.hpp:4-57`, `development_animated_combat.hpp:962-1000`). The 500 family is admitted through `slot7_native_world.inc.hpp:40-41` and run by the shared special body (`development_animated_combat.hpp:1038,1643-1644,2088-2091`). | State `351` is **handler-only** — a body and binding with no requester; guard `393/394` have **no owner found for Rena+0**. Special-state route presence is still not live coverage. |
| Shooting/recovery `400-409,450,460,469` | State 400 has the Rena ground-shot body; 401-409 and 450/460 use the mobile body; 469 uses the Rena recharge/landing path (`development_animated_combat.hpp:2492-2628`, `battle_rena_mobile_shooting.hpp:10-12`, `battle_rena_full_charge.hpp:87-91`). No generated shooting or special-strike body exists for `(0,0)` at all. | Slot 7 literally requests 400/401/402/405-408/450/460; 403/409 are mobile recovery outcomes and 469 is a landing/recovery outcome. State 404 is **handler-only**: the mobile helper accepts it but nothing requests it. State 400 request, magazine admission, pool birth, script tick and contact remain distinct. |

These rows are **inventory status, not acceptance coverage**. The 33 slot-7
requests and two bounded body/port comparisons are detailed in
[`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md). In particular, “DAT row
present,” “handler selected,” “body executed in a fixture,” and “integrated
port behavior checked” are different claims. None establishes original-runtime
parity for Rena+0 or authorizes work on another combo.

### The slot-7 request set

`slot7_body_0_0` (`slot7_native_bodies_20260929.hpp:3-398`) has **46
`FUN_00421080` call sites requesting 33 distinct states** — a source
observation counted in the generated body text: `20, 23, 24, 27, 28, 30, 40,
300, 301, 302, 310, 311, 320, 330, 331, 332, 340, 341, 350, 360, 370, 390, 400,
401, 402, 405, 406, 407, 408, 450, 460, 500, 501`. Most requests compare
`current_priority()` against the destination row's priority word, which
`slot7_native_world.inc.hpp:87-88` loads from the DAT into
`n.w[(0x880+state*0x1c)/4]`. The mapping verified from the request branches is:

| Requested states | Priority word in the body |
|---|---|
| 20, 23, 24, 27, 30, 40 | `0x2ac`, `0x2c1`, `0x2c8`, `0x2dd`, `0x2f2`, `0x338` |
| 300, 301, 302, 310, 311, 320 | `0xa54`, `0xa5b`, `0xa62`, `0xa9a`, `0xaa1`, `0xae0` |
| 330, 331, 332, 340, 341 | `0xb26`, `0xb2d`, `0xb34`, `0xb6c`, `0xb73` |
| 350, 360, 370, 390 | `0xbb2`, `0xbf8`, `0xc3e`, `0xcca` |
| 400, 402, 405, 406/407, 408, 450, 460 | `0xd10`, `0xd1e`, `0xd33`, `0xd3a`, `0xd48`, `0xe6e`, `0xeb4` |

Four requests sit outside that list. State 28 is gated by contact and a
current-state range rather than a priority word (`:105-112`). States 500 and 501
are requested through the special-entry path (`:139-142`), gated on mode words
and `n.w[0x3b]`. State 401 has two request sites: `:278` compares against 402's
word `0xd1e`, while `:298` compares against its own `0xd17`. The 407 request at
`:293` likewise reuses 406's `0xd3a`. A branch reusing a neighbouring row's word
is a **code observation about the generated text**, not evidence about which DAT
row it should read. Per-row priority A/B values and phase sets are in
[`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md).

### Ownership verdicts for the flagged rows

"No owner found" below means no recovered source path requests the state and no
handler switch names it. It is **not** a claim that the original can never enter
the state: the bundle does not contain the DAT contents, and a reaction row
selected by the DAT fields described next needs no named requester.

| Row(s) | Verdict | Evidence |
|---|---|---|
| `11`, `12` | **No owner found.** No reference to actor state 11/12 as owner, requester or handler exists in the bundle source; the string matches are character indices and frame numbers. Not "unreachable" — there is no entry and no handler in the source at all. | Targeted search of `source/src/`. |
| `303` | **No owner found for Rena+0.** Every reference is character-11/weapon-0 gated, and the follow-up handler throws for other combos. | `development_animated_combat.hpp:2681,2781`; `roster_followup_shot303.hpp:13`. |
| `351` | **Handler-only.** `full_charge_body_0_0_351` exists and the `(0,0)` binding has only case `351`, but nothing requests it: `slot7_body_0_0` never emits `0x15f`; only `slot7_body_8_1` and `slot7_body_14_1` do, and `advance_rena_full_charge` emits only `0/43/469`. | `full_charge_native_bodies_20260929.hpp:3,13804`; `development_animated_combat.hpp:2063-2065`; `slot7_native_bodies_20260929.hpp:10315,17843`; `battle_rena_full_charge.hpp:88-95,128-129`. |
| `393`, `394` | **No owner found for Rena+0.** The only mentions are a Satoko tail-effect state list and the character-8 ranked binding. | `satoko_field_tail.hpp:11`; `slot7_ranked_bodies_20260929.hpp:1094`. |
| `404` | **Handler-only.** `rena_mobile_shooting_state` accepts it, so the mobile handler runs if 404 is already active, but nothing requests it: the mobile handler emits only `0/43/403/409/469`. | `battle_rena_mobile_shooting.hpp:10,82,144,149,208,211,217,224-225`. |
| `109`-`112` | **DAT-driven entry only.** No named requester and no dedicated handler case found; the row is selectable only through the reaction fields below. | `actor_frame_hit.hpp:11`; `battle_hit_stagger.hpp:16-18`; `development_animated_combat.hpp:3731-3744`. |
| `117`, `122`, `123`, `125`-`127`, `129`, `132`, `232` | **No handler either.** Absent from `battle_common_hit_motion_state` and from every handler switch, so a selected row falls to the generic reaction tick, which advances the DAT animation but never selects a new state. `battle_hit_timers.hpp:10` treats `124-129` specially, but that is a timer effect, not an owner. | `battle_common_hit_motion.hpp:32-37`; `development_animated_combat.hpp:3295-3372`; `battle_hit_timers.hpp:10`. |

The reaction entry mechanism is worth separating by evidence class. **Source
observation:** `bind_actor_frame_hit` copies the attacker frame's `0x64`/`0x68`
words into the hit input (`actor_frame_hit.hpp:11`); `apply_battle_hit_stagger`
selects `state64` when grounded with `down < 100` and `state68` otherwise, then
adds 100 to the selection when the relative angle exceeds 90 degrees
(`battle_hit_stagger.hpp:16-18`); `set_common_hit_action` sets
`reaction_active_` for any state other than `0`/`43` (cleared again for
`103`/`203`), and routes `100-102/200-202` to `ground_hit_state`,
`45/118-121/124/128/221` to `recovery_state`, and `43`/`103`/`203` to
`air_state` (`development_animated_combat.hpp:3731-3744`). **Inferred field
meaning:** the `+100` step selects the back-row partner of a front-row reaction
(1xx → 2xx). **Not settled by this bundle:** whether a shipped Rena+0 attacker
frame actually carries `0x64`/`0x68` values selecting any flagged row; the DAT
contents are not present, and a row reached this way must still resolve a
handler and an animation row.

### Handler coverage and generated-body-only states

Source observation, from the dispatch tables listed above:

- **Generated `*_body_0_0_*` bodies exist only for** dash `20/23/24/27/28/30`,
  jump `40-44`, remaining melee `332/333/334/340/341` and `351`, plus the entry
  owner `slot7_body_0_0` itself. Of these, `351` has no requester, and `41-44`,
  `333` and `334` are not in the slot-7 request set: any entry they have is a
  transition inside another handler or a reaction outcome, not a slot-7
  admission.
- **All 33 requested states have a handler.** Locomotion `0/10` is shared
  (`roster_locomotion_native_control.hpp:26-57`). Melee
  `300/301/302/310/311/320/330/331` runs through the character-0
  `battle_rena_melee.hpp:19-53` families and the shared chasing/directional
  controls, while `332/340/341` use the generated remaining-melee route. Guard
  `390-392` is shared (`guard_native_control.hpp:4-57`,
  `development_animated_combat.hpp:962-1000`). The character-0-only
  `battle_rena_full_charge.hpp:14-20` covers `350/360/370`;
  `battle_rena_ground_shot.hpp` covers `400`; `battle_rena_mobile_shooting.hpp:10-12`
  covers `401/402/405-408/450/460`; the inline `329` branch is at
  `development_animated_combat.hpp:3099-3105`; and the `500`/`501` requests are
  installed as `special_entry` by `slot7_native_world.inc.hpp:40-41` and run by
  the shared special body (`development_animated_combat.hpp:1038,2088-2091`).
  Reaction rows use their own sinks (`battle_common_hit_motion.hpp:32-37`,
  `shared_recovery_native_20261004.hpp:55`).
- **There is no generated shooting body for `(0,0)` at all.**
  `owns_native_shooting(0,*,*)` is always false because
  `shoot_native_body_binding`'s switch starts at combo index 3
  (`shoot_native_bodies_20260929.hpp:97076-97080`); likewise
  `special_strike_native_body_binding(0,0,*)` is false because its lowest key is
  combo index 6 (`special_strike_native_bodies_20261003.hpp:3539-3543`). States
  `400-409/450/460` and the `500` family therefore run only through the shared
  hand-written paths above; do not route them through the generated non-Rena
  shooting file.
- **Dead duplicates are not cover.** The later branches for `332` (`:3066`),
  `334/339` (`:3079`), `333` (`:3085`) and `341` (`:3094`) can never run for
  Rena+0: `development_animated_combat.hpp:2367` takes the generated
  remaining-melee route for those states first and `continue`s.
- **One latent throw.** `remaining_melee_native_state`
  (`remaining_melee_native_control.hpp:37`) also lists `312/313/336/339`, but no
  `remaining_body_0_0_312/313/336/339` exists and
  `dispatch_remaining_melee_body`'s `default:` throws
  `std::invalid_argument("No original remaining melee DAT binding")`
  (`remaining_melee_native_bodies_20260929.hpp:24647`; declared at
  `remaining_melee_native_control.hpp:132`, called at `:153`). No source path
  requests those four states for Rena+0 today, so the live path does not reach
  the throw; a future admission that requests one would make it die with an
  exception instead of falling back.

### Shared and peripheral routes absent from a name search

| Route | Files and current call evidence | Pilot relevance |
|---|---|---|
| Actor and animation assets | `basic_battle_roster_assets.hpp:8-23` loads the equipped combo; `character_asset_files.hpp:14-30` resolves actor DAT, item and model; `battle_actor_assets.hpp:43-60` builds state/phase/priority/animation maps. | Load-bearing for every pilot case. |
| Held models and trails | `roster_weapon_trail_policy.hpp:40-49` has a Rena+0 arm; `development_animated_combat.hpp:918-929` applies commands, and `:848-858` selects held models. | Load-bearing where props, muzzle sockets or attack presentation affect a required case. |
| Voice and effects | `battle_voice_inventory.hpp:23-29,43-54` selects the ordinary `rena` voice root for item 001; `runtime_battle.hpp:1675-1700` delivers voice and advances visual effects. | Required event delivery where the pilot contract observes it; a queued event alone is not audible/visible acceptance. |
| Item-1 projectile family | `projectile_asset_files.hpp:59-63` obtains a registration from each item bullet row; with item 001's variant 0, its 18 rows have registrations `0,10,...,170`. `remaining_roster_projectiles.hpp:7-19` dispatches item 1 into `rena_projectile_switches.hpp`; `local_normal_projectiles.hpp:481,513-525` ticks and resolves contacts. | Gameplay-relevant launch, lifetime and contact need separate checks. |
| CPU, camera, result, network | CPU-enabled slots call `advance_rena_0` through `battle_cpu_driver.hpp:76-98` and `roster_cpu_decisions.hpp:6437-6444`; camera tracking is shared (`runtime_battle.hpp:1689-1692`, `battle_camera_tracking.hpp:15-45`); Rena+0 victory identity uses `data/win/00a.cnv` (`battle_victory_identity.hpp:9-17`); lobby pair validation uses `character_action_dispatch` (`battle_lobby_wire.hpp:45-60`). | Navigation references only. CPU and non-character roadmap work remain parked by `AGENTS.md`/`DIRECTION.md`; these routes do not enlarge the pilot. |

## Remaining questions before integration

This map identifies entry points. It deliberately does **not** conclude that
all Rena+0 branches are complete or that every transitive service has been
catalogued. For each selected action, the reviewing agent can check:

1. Turn the direct-field census into a **per-branch semantic mapping** to the
   port, including prior-input counters and service results. The raw indexes,
   callbacks and literal targets are in
   [`RENA0-SLOT7-AUDIT.md`](RENA0-SLOT7-AUDIT.md); the state-ownership census
   above now names the entry owner and the handler for each requested state, but
   the per-branch meanings and reachability under live input are not
   established.
2. The pinned Rena+0 DAT has rows for all 33 literal slot-7 state requests and
   item 001 has 18 bullet registrations (`RENA0-SLOT7-AUDIT.md`). Check the
   actual gate and requested bullet row per scenario; row presence is not an
   executed admission or a successful launch.
3. Which context fields and synchronous host services each reached body reads,
   writes or calls; reuse the quantified pilot seam in `PILOT-SEAM.md` rather
   than treating this navigation map as that audit.
4. Whether shot requests are admitted, spawned, ticked, contacted and resolved
   by the actual item-1 route. Keep those evidence levels separate.

The current repository plan permits this review for Rena+0. It does not lift
the freeze on the other 45 combos, approve a new contract, or declare the pilot
verdict.

For non-compiling examples of how the recovered decisions might meet the
foundation runtime, see [`RENA0-ADAPTER-MOCKS.md`](RENA0-ADAPTER-MOCKS.md).
