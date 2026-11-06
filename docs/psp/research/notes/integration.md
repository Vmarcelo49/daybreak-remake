# PSP fighters (core character indices 16, 17, 18) — integration map

Branch `feat/91-psp-characters`, HEAD `3a6eaf14`. Written by static reading only: **nothing was
built or run for this note**. Every claim is a `file:line` I read; where I infer, I say so.
Adresses/`FUN_` names in comments are the vendored core's own.

Vocabulary used below:

* **roster index** — the small integer the *product* and the *core's roster tables* use
  (`gameplay::kCharacterDirs`, `daybreak::character_names`, `sim::Slot::character`).
* **dispatch key** — the `{character, weapon}` pair that selects *which recovered update body*
  runs (`character_dispatch.hpp`). Today the two are the same integer. The single most useful
  observation in this note is that they do not have to be (§7).
* **combo** — one `{character, weapon}` pair. 46 exist.

Today the only thing that agrees on "who is who" is that three tables happen to be the same
16-entry list in the same order:
`core/character_names.hpp:6`, `src/battle/weapon_definition.h:178-184`,
`src/frontend/screen_select.h:22-25` (diamond coordinates). `battle.h:14-15` claims the core's
order *differs* from `kCharacterDirs`; it does not — the two lists are byte-identical today. The
comment is stale, and it is the kind of stale that makes somebody insert a mapping that is not
needed.

---

## 1. Core inputs per actor

### 1.1 The load chain, in call order

`sim::Battle::Impl` (`src/battle/battle.cpp:103-160`) owns everything; its constructor is `:127-158`:

| Member | Constructor | Reads per actor |
|---|---|---|
| `assets` (`AssetSearchPath`) | `battle.cpp:127` via `mount_assets` (`:81-92`) | `daybreak07/04/00.dat` mounts, or a loose tree |
| `roster` (`LocalBattleRoster`) | `battle.cpp:128` via `make_roster` (`:51-79`) | nothing; validates `weapon < weapon_count(character)` (`:54-56`) |
| `projectiles` (`LocalNormalProjectiles`) | `battle.cpp:129`, ctor `core/local_normal_projectiles.hpp:91` | `data/bullet/<item>/<NNN>.dat` + the item's `.dat`, keyed by **(item, registration)**, not character |
| `effects` (`BattleVisualEffects`) | `battle.cpp:130`, ctor `core/battle_visual_effects.hpp:114` | `data/effect/%03u.dat` + its model, keyed by **effect registration**, not character |
| `files` (`BasicBattleRosterAssets`) | `battle.cpp:131` → `core/basic_battle_roster_assets.hpp:21-24` | **the per-character load** — see below |
| `combat` (`DevelopmentAnimatedCombat`) | `battle.cpp:132` → `core/development_animated_combat.hpp:625` | consumes the assets + bindings only |
| `collision` | `battle.cpp:133` | stage only |
| `voices` | `battle.cpp:141-145` | `data/voice/<name>/<category>/NNN.wav` per slot |
| `cpu` | `battle.cpp:136` (`cpu.configure(roster)`) | owners only |

`BasicBattleRosterAssets` → `load_battle_roster_assets` (`core/basic_battle_roster_assets.hpp:8-20`):

1. `:11` every binding must match the roster slot **exactly**, else
   `std::invalid_argument("Roster/action binding mismatch")`.
2. `:15` `load_character_asset_files(search, character, weapon, option)`.
3. `:16` `BattleActorAssets(files.model, files.frames, weapon_item)`.

`load_character_asset_files` (`core/character_asset_files.hpp:14-34`) is the whole PC data contract:

| Line | What it needs |
|---|---|
| `:15` | `character < character_names.size()` **and** `weapon < (character<14 ? 3 : 2)`, else `std::out_of_range("Invalid character/weapon")` |
| `:16` | `variant <= 5` (costume; `option` in the roster) |
| `:17-18` | `data/<name>/<NN>.dat` where NN is the **weapon slot**, zero-padded |
| `:23-24` | weapon item id lives **inside the DAT** (`parameters[3]`; must be ≤127); item at `data/item/%03u.dat` |
| `:28-29` | model name is a 260-byte string inside the DAT; path `data/<name>/<model>` (or `data/<name>_<A+variant>/<model>`) |
| `:30` | `compressed_x` → `expand_x` (MSZIP) |

`BattleActorAssets` (`core/battle_actor_assets.hpp:27-61`) turns those two byte vectors into the
runtime asset. `BattleActionBinding` (`core/battle_action_binding.hpp:13-20`) picks the policy:

```
basic_battle_action(c,w):  dispatch = character_action_dispatch(c,w)      // THROWS for 16-18
                           c==0 -> rena_melee, c==1 -> mion_counter,
                           c==2 -> keiichi_basic, else -> roster_shared
```

`character_action_dispatch` (`core/character_dispatch.hpp:56`) is a linear search of a
**constexpr `std::array<CharacterDispatch,46>`** (`:8-55`) and throws
`std::out_of_range("Unknown character action dispatch")` when the pair is absent. This one call is
reached from `basic_battle_action` **before any branch**, so *no binding whatsoever can be built for
character 16-18 until the table or that call changes* (§4/§7).

`LocalBattleRoster` (`core/local_battle_roster.hpp:11-23`) is plain data. `BattleCpuDriver`
(`core/battle_cpu_driver.hpp:14-102`) needs only `roster.owner` plus, per frame,
`combat.action_binding(i).character/.weapon` (`:82, :97`) → `advance_roster_cpu`.

`BattleVoiceInventory` (`core/battle_voice_inventory.hpp:30-59`) is constructed for every battle
(`battle.cpp:145`) and `configure(i, character, item, option, style)` is called per slot
(`:147-149`). Nothing validates at configure time; the throw is at **read** time:
`names()` → `battle_voice_root()` (`:23-28`) → `if(character>=character_names.size()) throw
std::out_of_range("Battle voice character")`. `names()` is called from
`Battle::Impl::collect_events` (`battle.cpp:257-266`), which runs **unguarded inside `step()`**
(`battle.cpp:318`). So a new index 16-18 crashes the tick with an uncaught exception the first
time any voice is queued — not a graceful degradation.

### 1.2 Every place the core assumes a character range

Two families. **(A) hard gates** that throw / read out of bounds. **(B) soft gates** that only
change behaviour (usually fine for a new index, sometimes silently wrong).

#### (A) Hard gates — these break for 16-18

| # | Site | Form | What happens at 16-18 |
|---|---|---|---|
| A1 | `core/character_names.hpp:6` | `array<string_view,16>` | the index does not exist |
| A2 | `core/character_dispatch.hpp:56` (table `:8-55`) | linear search of 46 rows, throws | throws `out_of_range` — kills `basic_battle_action`, `advance_roster_cpu:6438`, `roster_ground_melee_profile:73`, `roster_walking_speed:8`, `roster_full_shot.hpp:116`, `roster_air_shot*`, `battle_jump_motion:22`, `battle_victory_identity:10`, `roster_ground_shot_admission:15`, `roster_walk_shot_admission:13`, … |
| A3 | `core/character_asset_files.hpp:15` | `character>=character_names.size() \|\| weapon>=(character<14?3:2)` | throws `out_of_range("Invalid character/weapon")` |
| A4 | `core/battle_voice_inventory.hpp:24` | `character>=character_names.size()` | throws, uncaught, inside `step()` |
| A5 | `core/battle_jump_motion.hpp:22` | `character>=16 \|\| weapon>=…` throws | state 40-43 jump tuning unreachable |
| A6 | `core/battle_victory_identity.hpp:10-13` | `character>=16` throws; builds `data/win/%02u%c.cnv` | round end throws; also **persona ids 16/17 are already taken** (Rena/Rika weapon 2, `:13`) |
| A7 | `core/local_battle_roster.hpp:30` | `player_character>=16` throws | default-roster helper (dormant in the product, `battle.cpp:49-80` builds its own) |
| A8 | `core/roster_ground_melee.hpp:52,73-74` | `RosterGroundMeleeTuning[16][3]` indexed `[character][weapon]` after the dispatch guard | OOB read if the dispatch guard learns 16-18 but this table does not |
| A9 | `core/battle_roster_walk.hpp:11,28` | `speeds[16][3]` same pattern | OOB read / garbage walk speed |
| A10 | `core/roster_ground_shot_admission.hpp:20-40` | `groups[16][3]`, `forward_gates[16][3]`, `[character][weapon]` | OOB read |
| A11 | `core/local_selection_slots.hpp:8` | `local_option_counts[16]`, indexed by character (`:26, :53`) | OOB read in the *dormant* core select state machine |
| A12 | `core/local_character_cursor.hpp:5-6` | `selection_x/y[16]` | OOB in the dormant state machine |
| A13 | `core/roster_cpu_decisions.hpp:6441-6482` | `switch(character*3+weapon)`, `default: throw` | `advance_roster_cpu` throws; also the `*3` encoding is a **3-weapon** assumption (weapon 3 aliases the next character) |
| A14 | `core/local_selection_slots.hpp:62` and `:90` | `character[slot]>=14 ? 2 : 3`, `random.next()%16` | wrong count / never selects 16-18 |
| A15 | `core/local_battle_roster.hpp:36,38,50,51,53` | `%16`, `character<14?3:2`, `local_option_counts[character]` | never selects 16-18; OOB if forced |
| A16 | `src/battle/battle.cpp:36-42` | `character_count()` = names size; `weapon_count()` = `character<14?3:2` | 19 characters would get **2** weapons for 16-18 |
| A17 | `src/battle/battle.cpp:45` | `character_name()` throws | every log line, `simctl`'s JSON (`simctl.cpp:250`) |
| A18 | `src/battle/battle.cpp:54-56, 779` | `weapon_count` validation | "not a legal combo" |

#### (B1) Hard gates, second family — the per-combo bodies are *throwing contracts*

The recovered per-combo code does not fall back: a pair it does not know **throws
`std::invalid_argument`**, and the callers are unguarded (they are the per-row arms of the
per-slot loop). So this family is not "loses a recovered behaviour", it is "the match dies the
first time the fighter enters that row". Reached unconditionally for any `data_driven_preview`
slot:

| Site | Guard | Caller |
|---|---|---|
| `core/roster_air_shot.hpp:58` | `character<3\|\|character>15\|\|weapon>2\|\|(character>=14&&weapon>1)\|\|state∉{402,408}` | `development_animated_combat.hpp:2856` (rows 402/408) |
| `core/roster_full_shot.hpp:116`, `roster_full_shot_motion.hpp:34` | same shape, state ∈ {350,360} | `:2931` |
| `core/roster_charge_shot.hpp:40` | state ∈ {450,460} | `:2868`-region |
| `core/roster_directional_shot.hpp:40` | state ∈ 404..407 | `:2846` |
| `core/roster_ground_shot400.hpp:106` | state 400 | row 400 |
| `core/roster_ground_shot400_motion.hpp:19` | row-400 motion | `roster_shot400_motion_key` |
| `core/roster_shot401.hpp:19` | state 401 | `:2833-2838` |
| `core/roster_ground_shot_admission.hpp:15` | `(character>0&&character<3)\|\|character>=16\|\|weapon>2\|\|(character>=14&&weapon>1)` | short-release shot admission |
| `core/roster_walk_shot_admission.hpp:13` | same | walking shot admission |
| `core/roster_directional_melee.hpp:322` | `character_action_dispatch` + state∉{310,311} | state 310/311 |
| `core/roster_ground_dash_melee.hpp:38,57` | `default: throw "Unrecovered ground dash entry"` over `switch(character)` | states 330/331 |
| `core/battle_roster_air_dash.hpp:53` | final `throw "Invalid air dash configuration"` after ~46 `if(character==N&&weapon==M)` lines | air dash |
| `core/battle_dash_melee.hpp:62` | `default: throw "Unrecovered state332 character/weapon"` | state 332 |
| `core/battle_leap_melee.hpp:9` | `state∉{332,334}` | leap |
| `core/battle_rebound_melee.hpp:15,35` | rebound families, `character∉{1,10,12}` | rebound |
| `core/keiichi_air_melee.hpp:61` | `character∉{0,2,5,11,15}` — "Unrecovered dive family" | dive |
| `core/roster_state341.hpp:32,38` | unsupported binding / DAT phase | state 341 |
| `core/roster_followup_shot303.hpp:27`, `roster_ground_shot_followup420.hpp:15` | `character!=11` | followups |
| `core/battle_chasing_air_melee.hpp:20-21` | `character!=0 && character!=1` throws | chasing air melee |
| `core/roster_secondary_charge.hpp:25`, `roster_shot401_clock.hpp:21`, `roster_ground_shot400_clock.hpp:17`, `roster_shot401_world.hpp:11` | `character==N` ladders with no default | state clocks |

That list is a **floor** (`grep -c 'Unsupported\|Unrecovered'` in `roster_*`/`battle_*` = 50+ call
sites). Practically: a brand-new index 16 cannot be pushed through the existing roster_shared rows
at all — it throws within the first second of a fight.

#### (B2) Soft gates — where a new index genuinely degrades instead

Only these return early / `default:break`:

| Site | Behaviour |
|---|---|
| `core/roster_weapon_visual_policy.hpp:26` (`:440` `default:break`) | characters ≥3 get the switch; an unmapped key emits no prop commands — cosmetics only |
| `core/roster_weapon_trail_policy.hpp:23,36` (`:1095` `default:break`) | same for trails |
| `core/roster_directional_melee.hpp:50` `default:return false` | airborne admission |
| `core/actor_sampled_pose.hpp:49` | no spine bone → no spine yaw |
| `core/development_animated_combat.hpp:651` | `if(base_.find(bone))` — no prop bone, no attachment |
| `core/development_animated_combat.hpp:330,801,834-846` | `character<3` / `character==5` / `character==15` branch bodies simply do not apply |

One more shape worth naming because it is *silent*: `switch(character*3+weapon)` with
`default:break` (`roster_weapon_visual_policy.hpp:30`, `roster_weapon_trail_policy.hpp:40`,
`shoot_native_field_types_20260929.hpp:5`) — and with `default:throw`
(`roster_cpu_decisions.hpp:6441`). All four encode 16×3 in one integer, so **weapon slot 3 aliases
the next character's slot 0** if the encoding is ever extended naively.

Scale: **633** `character==N` / `character!=N` comparison sites across **66** files in
`src/battle/core/`, plus **158** reads of `action_binding(slot).character` (112 of them
`action_binding(...).character`, 46 `binding.character`). Any change to the identity space has to
answer for all of them at once, which is the argument for *not* changing the identity space (§7).

---

## 2. What the core needs from a model

### 2.1 `BattleActorAssets` — members and their readers

`core/battle_actor_assets.hpp:13-62`. Written once by the constructor; immutable afterwards.

| Member | Built from | Read where |
|---|---|---|
| `weapon_item` | `data/item/NNN.dat` (`character_asset_files.hpp:23-25`) | magazines + prop selection at `development_animated_combat.hpp:646-653`; `selected_held_weapon_models` `:853`; projectile spawn cost `battle_magazine`; `Battle::magazines()` |
| `base_` (`ActorSkeleton`) | `ActorSkeleton::decode(XObjectReader(model))` `:28` | pose seed `:660, :1373`; throw bone `:3814`; hit skeleton `:3900`; attachment bone check `:651` |
| `attack_phases_` | `state_frames_[300]` `:58` | **must be non-empty** — `:59` throws `Invalid attack animation index`; `development_animated_combat.hpp:655` throws `Unsupported development action phase layout` |
| `state_frames_` (`map<state, vector<ActorPhaseData>>`) | DAT states `:48` | the whole row/animation/hit machine — 35 sites; `at()` throws `out_of_range` for a missing row (`:1023, :1038, :766, :1074, :1134, :1179, :788`) |
| `state_priorities_` | DAT `state.a/b` `:48` | combo admission (`roster_ground_combo_admission.hpp`), first-priority lookups |
| `animation_settings_` `array<…,256>` | `read_actor_animation_settings` `:43-44` | blend durations per set (`actor_animation_service.hpp:19-23`), texture events (`:756`) |
| `animations_` `map<unsigned,XAnimationKeys>` | `AnimationSet` objects registered in **reverse document order**, skipping empty sets, index `< 256` else throw `:31-41` | key sampling; `animations_.at(phase.value)` throws for a missing index |
| `animation_last_keys_`, `animation_durations_` | `:38-46` | period/row length (`:46`, `state_animations_` recovery timings `:56-57`) |
| `state_animations_`, `recovery_durations_` | `:54-57` | animation→state lookups, recovery lengths |
| `guard_data_` | states 390-392 `:52` | guard row (`:1170`, `.at()` throws) |
| `ticks_per_second_` | `actor_ticks_per_second(roots)` `:28` — **from the .X** | every time conversion, 13 sites |
| `parameters[6]` | DAT dwords +4.. | special-gauge limits/durations `:644`, CPU thresholds (`battle_cpu_driver.hpp:88`), `parameters[3]` is the weapon item id |
| `idle_animation_` | `state_animations_[0][0]` `:55` | `bind_both` at match start `:658` |
| `skin` (`ActorSkin`) | `ActorSkin::decode(roots, base_)` `:28` | **defined at `:1335` (`actor_skin(slot)`) and called from nowhere.** The simulation does not use the skin. |
| `prepared_pose` | `PreparedActorControllerPose(base_, animations_, ticks)` `:60` | per-frame pose `update_prepared_actor_controller_pose` (`:826`) — the **only** pose source for the product |
| `registered_animation_count`, `serialized_animation_count` | `:41, :43` | not read outside the constructor |

Order dependency that matters: `:51` resolves every DAT hit record's bone **by name**
(`frame.bone_index = base_.find(frame.bone)`). A name absent from the skeleton silently binds
`0` (the root) — `ActorSkeleton::find` returns 0 for a miss (`actor_skeleton.hpp:30-35`), and the
comment at `:49-50` accepts that ("a live geometry read reports the error"). So a hit record naming
a PSP bone on a PC skeleton, or vice versa, does not throw at load: it puts every hitbox at the
root, which reads as "the fighter cannot hit anything".

### 2.2 Bone-name lookups (the "Bip01" surface)

`grep -c 'Bip01' src/battle/core` = **473 occurrences**, in: `shoot_native_world.inc.hpp`,
`battle_aura.hpp`, `projectile_model_animation.hpp`, `projectile_manager_services.hpp`,
`full_charge_native_bodies_20260929.hpp`, `held_weapon_pose.hpp`,
`full_charge_native_world.inc.hpp`, `shoot_native_bodies_20260929.hpp`, `actor_sampled_pose.hpp`,
`development_animated_combat.hpp`. The load-bearing ones:

| Site | Lookup | Consequence for a `head`/`lefthand` skeleton |
|---|---|---|
| `core/actor_sampled_pose.hpp:35` | `actor_animation_channel(name)` = `name.starts_with("Bip01") ? 1 : 0` | **every PSP bone becomes channel 0**, channel 1 (upper body) has no tracks. Layer-1 binds then write nothing, so the walk-shot layer (`development_animated_combat.hpp:770-788`, `upper_only`) loses the attack animation while walking |
| `core/actor_sampled_pose.hpp:49` | `find("Bip01_Spine")` for spine yaw | no spine yaw (`actor+68`); `:49` returns silently |
| `core/held_weapon_pose.hpp:9-10` | `find(slot ? "Bip01_Prop2" : "Bip01_Prop1")`, then `if(!bone) throw "Weapon attachment bone missing"` (`find` returns 0 on a miss, so the guard fires) | **would throw** — but the function has **no caller** in the core today, so it is inert |
| `core/development_animated_combat.hpp:651` | `character==15 ? "Bip01_Prop2" : "Bip01_Prop1"`, guarded by `if(base_.find(bone))` | prop attachment disabled — cosmetic |
| `core/projectile_manager_services.hpp:67-70` | `"Bip01_R_Hand"`, throws `Projectile owner right hand bone missing` | **throws** for any projectile that reads the owner's hand |
| `core/shoot_native_world.inc.hpp:51` | `"Bip01_R_Hand"`/`"Bip01_L_Hand"`, throws `Unknown shooting bone handle` | throws inside the shooting body |
| `core/battle_aura.hpp:8-10` | 11 names (`Bip00`, `Bip01_Head`, `Bip01_Spine`, …) | aura hit-region matrices; `battle_status_aura` selects by state, then reads bone matrices by index |
| `src/render/aura_attach.h:34-44` | the same 11 names on the **product** rig, plus `resolveAuraAttach` | `found` < 11 → fewer aura instances, logged (`scene.inc:896-901`); not fatal |
| `src/app/match.inc:703` | `findFrame("Bip01_Spine")` etc. for status cards | silently skipped |
| `src/assets/scene.h:422-428, 465-477` | `Bip01_Prop1`/`Prop2` attachment | weapon props do not attach (a warning is printed) |

`shoot_native_bodies_20260929.hpp` and `full_charge_native_bodies_20260929.hpp` call
`n.FUN_0064e6c0("Bip01_R_Hand")` many times — those are the compiled bodies and are on the same
hook, but they only run for the combos that have them.

### 2.3 Can `BattleActorAssets` be synthesised from a non-.X source?

**Yes — but only through the constructor, and only by giving it bytes.**

* There is exactly one constructor (`:27`) and it is user-declared, so the type is **not
  default-constructible and not aggregate-initialisable**. `prepared_pose` alone cannot be built
  without a skeleton + animation map + tick rate (`prepared_actor_controller_pose.hpp:17-24`).
* The constructor is a **pure function of two `std::vector<std::uint8_t>`**:
  `XObjectReader(model).read()` (`x_objects.hpp:9-56`, a binary tokenizer, no file/format
  assumption beyond the token stream) and `read_actor_frame_data(frames)` +
  `read_actor_animation_settings(frames)` (`actor_frame_data.hpp:14-29`,
  `actor_animation_settings.hpp:16-33` — plain little-endian readers, no header magic check).
* Therefore **a GMO→(X token stream, DAT frame table) writer fed to the existing constructor is not
  a core change at all.** The minimum content that satisfies every load-time check:
  1. `Frame` objects named as the hit/animation tracks expect, each with a
     `FrameTransformMatrix` (`x_frame.hpp:7-17`); optionally `Mesh` objects (an empty skin is fine).
  2. `AnimationSet` objects, at least for every `phase.value` used by `state_frames_[300]`
     (`:59`), registered in reverse document order (`:33`).
  3. A DAT frame table with `parameters[6]` (`parameters[3]` = the weapon item id), the states the
     rows need, **state 300 non-empty**, state 0 for the idle, and the animation-settings section
     whose `consumed` must equal the buffer length in the asset-file path
     (`character_asset_files.hpp:21`) — the `BattleActorAssets` ctor itself does not check it.
* `DevelopmentAnimatedCombat(const std::vector<uint8_t>& model, const std::vector<uint8_t>& frames,
  bool keiichi)` (`development_animated_combat.hpp:622-623`) already shows the byte-level entry
  point tests use.
* The only thing that forces a core edit is if you insist on **filling the members directly**
  instead of emitting bytes: that needs a `=default` ctor plus a `finalize()` that rebuilds
  `prepared_pose` and re-resolves `bone_index`. That is a §1-style change to a vendored header and
  would need a `PATCHES.md` entry; emitting bytes needs neither.

Three model-side facts the core needs regardless of source:
* `ticks_per_second_` comes from the model, and every key time is divided by it
  (`actor_controller_pose.hpp:35-41`). A GMO taken at 30 fps must claim the same tick base the
  PC's `.X` does (4800) or every row's timing shifts.
* Animation **set index** is a positional registration order, not a name
  (`battle_actor_assets.hpp:32-41`; the DAT's `phase.value` is that index). PSP motion "takes" have
  to be renumbered into the DAT's indices, not looked up by name.
* DAT hit records are anchored on a bone name (`:51`) — the `ActorPhaseData` "hit records anchored
  on bones" is exactly `ActorFrameData.bone` + `first/second/extent/shape/flags`
  (`actor_frame_data.hpp:9`), transformed by the bone's world matrix at hit time
  (`actor_frame_geometry.hpp:23-25`).

---

## 3. The `roster_shared` policy

### 3.1 What the policy is

`core/battle_action_binding.hpp:6-11`:

```cpp
enum class BattleActionPolicy { legacy_test, keiichi_basic, mion_counter, rena_melee,
                                roster_shared, data_driven_preview=roster_shared };
struct BattleActionBinding { BattleActionPolicy policy; unsigned character, weapon;
                             std::uint32_t original_update; };
```

`roster_shared` (aka `data_driven_preview`) is what every character ≥3 gets. Two guards in the
combat constructor:
* `development_animated_combat.hpp:639-640` — for `roster_shared` it requires
  `original_update == character_action_dispatch(character,weapon).update` (`:639-640`, so the
  binding's metadata must stay consistent with the table);
* `:643-645` — `legacy_test` is the **only** policy that skips dispatch validation.

### 3.2 What a DAT-backed fighter actually runs

Per tick (`development_animated_combat.hpp:2100-2300`, the per-slot loop) the row number
(`current_action_state`, `:662-664`) selects a body. Which body is a mixture of:

* **generic, data-driven**: movement (`battle_roster_walk.hpp`), the state-10 walk, most of the
  state-row machinery, hit resolution, damage, gauges, magazines, collisions, stage queries,
  projectile *motion*. These read only `state_frames_`, `animations_`, `animation_settings_`,
  `parameters`, and the row number. This is what the plan calls "common movement/melee/shoot rows".
  **Caveat, and it is the load-bearing one:** the common rows do not stand alone. The shot, melee
  and dash rows hand off to a per-combo body that throws for a pair it does not know (§1.2 B1), so
  "generic" means "generic for a pair the tables already contain".
* **table-driven per (character, weapon)**: `roster_ground_melee_tuning[16][3]`,
  `speeds[16][3]`, `groups[16][3]`, `forward_gates[16][3]` — all `[character][weapon]`, all guarded
  by `character_action_dispatch` (A8-A10).
* **branch-driven per (character, weapon)**: 633 `character==N` sites, mostly in
  `roster_directional_melee.hpp` (87), `roster_ground_dash_melee.hpp` (56),
  `battle_roster_air_dash.hpp` (46), `roster_special_strike.hpp` (30), `roster_charge_shot.hpp`
  (27), `roster_walk_shot_admission.hpp` (23), `roster_state341.hpp` (21), `roster_air_shot.hpp`
  (21), `development_animated_combat.hpp` (72). These are the recovered per-combo *differences*.
* **switch(`character*3+weapon`)**: `roster_weapon_visual_policy.hpp:30` (per-frame prop choice,
  425 lines of cases), `roster_weapon_trail_policy.hpp:40` (1 050 lines), `roster_cpu_decisions.hpp:6441`
  (CPU decisions), `shoot_native_field_types_20260929.hpp:5` (`key=(ch*3+we)*1000+state`).
  All four encode **3 weapons and 16 characters in one integer**.
* **item-keyed, character-independent**: the projectile bodies. `projectile_script_dispatch.hpp`
  switches on `item==N` / `registration==N` (e.g. `:73-136`), `remaining_roster_projectiles.hpp:9-22`
  on `item`, `weapon_bullets` reads `data/item/NNN.dat`+`data/bullet/NNN/MMM.dat`
  (`battle.cpp:778-800`). Magazines come from the item file (`weapon_item_data.hpp:19-26`).

### 3.3 Keyed on `binding.character`/`weapon` vs keyed on data

Keyed on the **binding** (identity), i.e. what a new index must answer for:
per-combo row bodies, weapon visuals/trails, CPU decisions, dash recovery
(`battle_dash_recovery.hpp:10`), jump tuning (`battle_jump_motion.hpp:23-31`), air melee profiles
(`roster_air_melee.hpp:20-28`), followup admission (`roster_followup_shot303.hpp:13,20,27`),
shot-400/401 clocks, secondary charge, victory identity, voice bank
(`battle_voice_route.hpp:8-10`, only `character==14&&item==32`).

Keyed on the **data** (so a new index inherits it for free):
all `state_frames_`/`animations_`/`animation_settings_`/`parameters` behaviour, magazines and
bullets (item id), every projectile body (item + registration), effects (registration), damage
scaling, hit/contact/status, gauges, stage, the whole `actor_*` pose pipeline.

### 3.4 Can index 16 behave as "Keiichi weapon 0" in code with other data?

Yes — mechanically it already can, and this is the cheapest lever in the repo:

* Nothing in the combat requires `binding.character == roster.character`. That equality is enforced
  in exactly **one** place, `basic_battle_roster_assets.hpp:11` ("Roster/action binding mismatch"),
  which the product calls (`battle.cpp:130`) but a hand-built `BattleActorAssetSlots` +
  `BattleActionBindings` does not have to go through (`DevelopmentAnimatedCombat` takes them
  directly, `:625`).
* If the binding says `{roster_shared, 2, 0}` while `assets_[i]` is the PSP character's model +
  frame table + weapon item, then: the pose/animation/hit pipeline uses the PSP data
  (`assets_`), while every per-combo branch, table and switch in §3.2 resolves to **Keiichi 0**.
  That is exactly "behave as Keiichi weapon 0 in code, with other data".
* What it costs: Keiichi's rows 300-341 have recovered bodies with their own contact tweaks, so the
  movement/melee timing of the new fighter becomes Keiichi's where the two differ. The PSP plan's
  step 4 ("the PSP's Keiichi `a` on the PSP body against core Keiichi 0") is precisely the
  measurement that would tell you how large that error is.
* What it does **not** fix: `character_names` (A1), the voice inventory (A4), the victory identity
  and product-side art (§4). Those key on the roster index, not the binding.

So the useful decomposition is: **roster index** (data paths, UI, art, voice, victory — must be
extended) vs **capability/dispatch key** (per-combo bodies — can be borrowed). `BattleActionBinding`
has room for both fields today if the roster index is carried separately (it is: `LocalBattleRoster`
and `sim::Slot`).

---

## 4. Product side — everything that assumes 16 × 3

### 4.1 The constants

`src/battle/weapon_definition.h`:

| Line | Name |
|---|---|
| `:173` | `kCharacterCount = 16` |
| `:174` | `kWeaponSlots = 3` |
| `:178-184` | `kCharacterDirs[16]` — selection order **and** `data/` directory name |
| `:191-197` | `kWeaponIds[16][3]` — item id per combo |
| `:200-205` | `weaponSlotForItem(character,itemId)` |
| `:210-219` | `comboSlotLabel` → "Rena 1" |
| `:221-224` | `weaponCountForCharacter` = `character < kCharacterCount-2 ? 3 : 2` |
| `:226-228` | `weaponSlotIsLegal` |

All uses across `src/` and `tests/` (`grep`):

| File:line | Use |
|---|---|
| `src/app/main.cpp:1009` | `kWeaponIds[character][0]` |
| `src/app/main.cpp:1039-1048` | `--local-players` candidate scan over `kCharacterCount`, gated on a **joinable slot-0 item** |
| `src/app/main.cpp:1073-1074` | random COM fill: `fill()%kCharacterCount`, `fill()%weaponCountForCharacter` |
| `src/app/main.cpp:1617-1618` | `kWeaponIds[slot.character][slot.weapon]` for the delivery request |
| `src/frontend/frontend_launch.cpp:14` | **hardcoded `slot.character>=16`** (not `kCharacterCount`) |
| `src/frontend/frontend_launch.cpp:18` | `kWeaponIds[…]` |
| `src/frontend/frontend_launch.cpp:43` | **hardcoded `index < 16`** |
| `src/frontend/screen_select.cpp:14-18` | `static_assert` roster tables == `kCharacterCount` (fires if you change one and not the other) |
| `src/frontend/screen_select.cpp:75` | icon scan bound |
| `src/frontend/screen_select.cpp:142,144` | random roll on off-grid confirm |
| `src/frontend/screen_select.cpp:197,262,276,498` | weapon counts |
| `src/frontend/participants.h:84` | `kWeaponIds[slot.character][slot.weapon]` — **no bounds check** |
| `src/battle/character_moves.cpp:64`, `character_moves.h:87` | `data/<char>/NN.dat` + the id at 0x114 |
| `src/battle/simfuzz.cpp:124-125` | `sim::character_count()` sweep |
| `src/battle/simctl.cpp:58,169-170` | `sim::character_count()` / `character_name()` |
| `tests/combo_fixture.h:42,45,49` | `data/<dir>/NN.dat`, `kWeaponIds`, `data/<dir>/<model>` |
| `tests/sim_pose_test.cpp:37-39` | full sweep of `sim::character_count()` × `weapon_count` |
| `tests/sim_core_test.cpp:67-69` | full sweep, **and `check(combos==46)` at `:93`** |
| `tests/weapon_definition_test.cpp:333,336-340,347-350,367-370,430-431,542-545,596` | asserts 16 characters, 3 slots, hanyu/natumi = 2 |
| `tests/locale_coverage_test.cpp:57` | `weaponCountForCharacter` sweep |
| `tests/participant_layout_test.cpp:39` | `kWeaponIds[0][1]` |
| `tools/audit_attack_flags.cpp:22-56` | `data/<dir>/NN.dat` sweep |

### 4.2 Select screen — `src/frontend/screen_select.{h,cpp}`

* Roster grid: `screen_select.h:22-25` — `kSelectRosterX/Y/Order/Costumes[16]`. Positions are in
  a 48×36 pitch lattice; `screen_select.cpp:70-72` multiplies them. Adding a 17th icon means new
  `(x,y)` cells (the diamond has room — the lattice is sparse) **and** the `static_assert` at
  `:14-18` forces the four tables and `kCharacterCount` to move together.
* Per-character art, loaded at construction (`screen_select.cpp:363-369`, indices 0..15):
  * `data/select/%02d` — portrait (256×256 sheet, drawn at `:430`) **and** the VS portrait (§4.3);
  * `data/select/i%02d` — chibi sheet, 80×128 cells, 3×2 grid, cells walked by
    `selectChibiCell` (`screen_select.h:88-95`), drawn at `:448`;
  * `data/select/cos%02d` — costume icon sheet, 3×2 cells of 80×128 (`:460`);
  * `data/select/w%02d` — **weapon icon sheet, 256×64 per row, one row per weapon** (`:461,500-502`);
  * name text is *not* per character — it is one shared sheet `shared_[5]` (`paths[]` at `:359`,
    cell `{character/8*256, character%8*64, 256, 64}` at `:459,489`): a **2-column × 8-row atlas of
    16 names**. Character 16 is column 2 → outside the texture.
* `SelectScreen::loaded()` (`:373-377`) requires **all four** sheets for **all 16** — so a missing
  `data/select/17` makes the whole screen fail to build, not just one icon.
* `_Order` (`:24`) is the reveal order of the entry animation; `SelectReveal` loops `i<16`
  (`screen_select.h:59-63`) and `SelectScreen::reveal_` is `array<float,16>`.

### 4.3 VS screen

* `src/frontend/screen_vs.cpp:32-33` — portrait `data/select/%02d` per participant, index
  `max(0, character)`; missing → `loaded()` false → `makeVsScreen` returns **null** (`:124`) →
  the screen errors.
* `:69` — name cell `(character/8, character%8)` of `data/select/p03` (`sheets_[3]`, `:16`), same
  2×8 atlas as §4.2. 17-19 need a third column in that sheet.
* `src/frontend/participants.h:84` builds `weaponId` by indexing `kWeaponIds[character][weapon]`
  with no guard. `:186-201` (`kVsSlots`, `vsSlotForSingle`) are participant-count only, so a 3- or
  4-fighter launch is already handled; only the identity/art is character-dependent.
* `comboSlotLabel` (`weapon_definition.h:210-219`) already degrades to `"?"` for
  `character >= kCharacterCount`, so the caption does not crash — it just reads "?".

### 4.4 HUD, result, story, CPU defaults

* **HUD**: no per-character art at all. `grep '"character"' src/hud/*` finds nothing; the HUD is
  shared sheets `P00..P12` (`hud/hud_atlas.h:44-46`) plus the seat tag. Nothing to add.
* **Result screen**: `src/frontend/screen_result.cpp:53` → `data/win/%02u%c.cnv` (one 512×512 sheet
  per character, `b` for the persona variant) via `battle_victory_identity`
  (`core/battle_victory_identity.hpp:12`). Missing sheet → "the winning character's result portrait
  did not load" (`:146`).
* **Win quotes**: `result_quote.h:48-54` `resultPersonaId` maps (Rena,2)→16 and (Rika,2)→17;
  `result_quote.cpp:39-49` builds `data/scenario/win/%02d-%02d-%d.txt` and `%02d.txt`.
  **Indices 16 and 17 are already meaningful here** — a core index of 16 collides with Rena's
  persona. `resultFallbackSingleId` (`result_quote.h:64-71`) hard-codes 16/17 as the fallback.
* **Story**: `story_ladder.h:6` — "Character numbers are kCharacterDirs' indices"; the ladder and
  fights come from `data/scenario/team%02d.dat`. `story_ladder.cpp:54-57` picks the enemy weapon
  (`character==0||character==4 ? 2u : 3u` — a Rena/Rika persona rule, not the 14 boundary).
  `screen_story_team.cpp:29,69` has a 14-entry `kChibiCharacter` table; `:287-291` loads
  `data/select/%02d`, `cos%02d`, `w%02d` per member. The new fighters have no story; the
  requirement stops at versus (§ the plan).
* **CPU defaults / random COM**: `src/app/main.cpp:1073-1074` (fill) and
  `battle.cpp:49-80` (roster); `core/local_battle_roster.hpp:36-40` is the dormant twin.

### 4.5 Online

* `net/lobby.h:26-30` `PlanSlot{character, weapon, costume, specialMode, peer}` is filled from the
  local selection (`frontend/screen_online.cpp:42-43`) and **is not transmitted**:
  `encode_plan` (`net/lobby.cpp:145-164`) carries token/seed/peerCount/peers/names/ready, and the
  comment at `lobby.h:32-35` states the stage, rules and slots come from the selection every peer
  runs. So character indices never cross the wire — a 19-character roster is compatible **as long
  as every peer runs the same build**, which `Refusal::WrongVersion` (`lobby.h:24`) covers.
* `game_data_hash` (`net/lobby.cpp:209-233`) hashes the 8 bundles' sizes + first/last MiB. Game
  data, not the roster; PSP files live beside the executable, so it is unaffected either way.
* `net/netctl.cpp:156` sets `plan.slots[i].character = i` for the stress harness (0-3 only).

### 4.6 Settings

No persisted character index exists. `src/settings/user_settings.*` stores volumes, the player
name ("up to 12 plain ASCII characters", `:594`), language, render toggles. `frontend_state.h:14`
holds `FrontendSlot{character=-1, weapon, hypermode, costume, controller}`, reset by
`FrontendState::beginSelection()` per select-screen entry (`screen_select.cpp:355`, `frontend_state.h:59`), i.e. in memory
only. Nothing to migrate.

### 4.7 Per-character asset path patterns (what a 19th character needs on disk)

| Need | Path | Loader | Fatal if missing |
|---|---|---|---|
| frame table + model name + item id | `data/<dir>/<NN>.dat` | `character_asset_files.hpp:18` | yes (`Asset not found`) |
| model | `data/<dir>/<model-from-dat>` | `:29`; `xm::loadCharacter` `assets/scene.h:187+` | yes |
| weapon item | `data/item/%03u.dat` | `character_asset_files.hpp:24` | yes |
| bullets | `data/bullet/%03u/%03u.dat` | `battle.cpp:798` | no (`continue`) |
| weapon props | `data/item/<meshName>` | `app/scene.inc:469-490` | no (warning) |
| voices | `data/voice/<name>/<category>/NNN.wav` | `battle_voice_inventory.hpp:49-56` | no (empty list) — but `battle_voice_root` **throws** first for an unknown index |
| select portrait | `data/select/%02d` | `screen_select.cpp:365`, `screen_vs.cpp:32` | **yes** (whole screen) |
| chibi | `data/select/i%02d` | `screen_select.cpp:366` | **yes** |
| costume icons | `data/select/cos%02d` | `:367` | **yes** |
| weapon icons | `data/select/w%02d` (one 64-px row per weapon) | `:368` | **yes** |
| name cell | `data/select/p03`, 256×64, `(c/8, c%8)` | `screen_vs.cpp:69`, `screen_select.cpp:459` | no (wrong pixels) |
| result portrait | `data/win/%02u%c.cnv` | `core/battle_victory_identity.hpp:12` | yes at round end |
| win quote | `data/scenario/win/%02d*.txt` | `result_quote.cpp:39-49` | no (falls back) |
| aura/status bones | `Bip01_*` names on the rig | `render/aura_attach.h:34-44` | no (fewer instances) |
| rig for the core pose | `xm::Model` whose frames == core bones + 1 | `core_battle.cpp:143` | **yes** (throws) |

---

## 5. Rendering — how a fighter is drawn today, and what a non-.X model needs

**The path, in order.**

1. `app/scene.inc:19-38` `appendCharacter` → `xm::loadCharacter(base, name, costume, opts)`
   (`src/assets/scene.h:180`, definition `:329`) reads `data/<dir>/<NN>.dat`, takes the model name out of it
   (`readDatModelName`, `:181`), loads the `.X` (MSZIP-aware, `xmodel.h:559+`), resolves textures
   per material through `TextureCache` from the bundle (`.bmp`→`.cnv`), and appends one
   `SceneModel{role="character"}` per character plus one per weapon prop
   (`app/scene.inc:467-490`, called at `:529`; `SceneModel.attachFrame/offHandFrame/propId/ownerRig`,
   `assets/scene.h:74-112`).
2. `app/scene.inc:773-784` `initMatch` finds the four `role=="character"` models in scene order and
   records them as `app.matchRig[0..3]`; `:858-862` binds `app.controllers[rig]` to the model.
3. Per frame, `app/scene.inc:1382-1408` `advanceAnimation`: in a match the rig's own
   `xm::Controller` is **not** advanced; instead
   `app.battle->fighter(f).core_pose(app.worlds[app.matchRig[f]])` (`:1406`) overwrites the world
   matrices, then `app.renderer.updatePose(app.worlds)` (`:1408`).
4. `sim::CoreFighter::core_pose` (`src/battle/core_battle.cpp:140-146`) = `Battle::bone_poses`
   (`src/battle/battle.cpp:726-738`) = `combat.render_pose_view(slot)` (the core's own
   `cached_poses_`, `development_animated_combat.hpp:1364-1369`) → `combine_actor_world_hierarchy`.
   **`if (m_bones.size() != worldOut.size()+1) throw "sim: core skeleton does not match the rig"`
   (`core_battle.cpp:143`)** — the drawn model's frame count must equal the core skeleton's bone
   count, in the same order (frame *i* ↔ bone *i+1*).
5. `render/scene_renderer.cpp:689` `setScene` uploads vertices/indices/textures and builds one
   `DrawItem` per submesh with a palette slice (`MeshRecord`, `scene_renderer.h:558+`);
   `:1014` `updatePose` refills only the palette storage. Skinning is per-vertex
   `Vertex::bones/weights` indexing `Mesh::bones` (`assets/xmodel.h:77-90, 134-150`);
   `Model::buildPalette`/`paletteSize` (`:222-227`) compute the slice. The **palette matrices are
   `worlds[rig]`** — the core pose.
6. Textures: material `Material::texture` (raw Shift-JIS bytes, `xmodel.h:96-114`) resolved by
   `TextureCache` against the bundle; per-frame swaps come from the DAT's animation events
   (`actor_texture_remaps`, `core/actor_animation_settings.hpp:45-53`) via
   `SceneRenderer::TextureOverride` (`match.inc:287-290, 331-340`).
7. Held weapon props: separate `SceneModel`s with `attachFrame` = the character rig's
   `Bip01_Prop1`/`Prop2` (`assets/scene.h:422-428, 465-477`); placed per frame by
   `match.inc:288-315` (`placeAttachedProp`, `item_model_hand`), hidden by
   `setModelVisibility`/`setModelOwners`.
8. Aura/status cards: `render/aura_attach.h` resolves 11 named bones once (`scene.inc:896`), then
   one `EffectInstance` per resolved point (`match.inc:670-700`), plus named-bone status cards
   (`match.inc:701-712`).
9. Shadows/outlines: the character shadow map (group 3, `scene_renderer.h:349-372, 396-405`) is
   driven by `DrawItem::toon` / `receiver` / `Pass`, assigned from the model's role at scene build
   (`assets/scene.h` roles); the toon outline hulls are extra draws in the same list, submitted only
   while the toggle is on (`scene.inc:1334-1337` prints their count). Neither is keyed on the
   character's identity — only on "this is a character/weapon model".

**What a non-.X model would have to provide** — one of:

* **(a) an `xm::Model`** produced by a GMO reader: `frames[]` in the core skeleton's order (names
  are free, but the *count and order* are not), `meshes[]` with `skinned=true`, `Bone{name,frame,
  offset}` per influence and `Vertex::bones/weights`, `materials[]` with a texture name the
  `TextureCache` can resolve, `anims` can stay empty for the renderer in a match (the controller is not advanced), but
  `tests/combo_fixture.h:51-52` rejects a rig with no animation sets and `sim_pose_test` then
  compares frame names (`tests/sim_pose_test.cpp:54-56`), so the test rig needs them; `ticksPerSecond`
  must be non-default only if the GMO's keys are not on the PC's base.
  This keeps `setScene`/`updatePose`/shadows/outlines/props untouched. `SceneModel` needs
  `role="character"` and the correct `attachFrame`/`propId` if weapons hang off it.
* **(b) a new scene source**: `SceneRenderer::setScene` takes an `xm::Scene` and nothing else, so a
  second geometry source means a parallel upload path (`meshes_`/`buffers_`/`MeshRecord`) — much
  larger, and it would have to re-implement the palette, the toon/outline and shadow draws.

The `.X` reader is not the obstacle: `xm::loadMemory` (`assets/xmodel.h`, used by
`app/match.inc:495`) parses from bytes, so a GMO→`xm::Model` builder that fills the structs directly
is the same amount of work as one that emits `.X` bytes, and it does not require implementing the
token writer on the render side too.

---

## 6. Tests and fingerprints

### 6.1 `tools/fingerprints.sh` — the regression oracle

`tools/fingerprints.sh:23-35` `sim_case` runs `simctl --roster <4 combos> --ticks 3600` **twice** and
compares the `"hash"` field (FNV-1a over every tick's actor states, `battle.cpp:317-334`,
`Battle::hash`); `:37-51` `pix_case` renders a screen twice and sha256s the PPM. Cases at `:53-59`:

```
SIM rena-mion-keiichi-satoko    rena:0:human mion:0 keiichi:0 satoko:0
SIM chie-rika-irie-hanyu        chie:1 rika:2 irie:0 hanyu:1
SIM akasaka-natumi-tomitake-shion akasaka:2 natumi:0 tomitake:1 shion:2
PIX battle640 --screen=battle --frames=400 --size=640x360
PIX title720  --screen=title  --frames=200 --size=1280x720
PIX title4p   --screen=title  --local-players=4 --script=tests/scripts/frontend-4p.txt --frames=3500
```

Expected values are in `AGENTS.md` ("Regression hashes"): SIM `746ce7a9cbe6e44a`,
`941f3dcd7a679d74`, `f19e8d6d58c37151`; PIX `ff54a85d`, `1fc12c64`, `9ecda8ec`. **The three SIM
cases plus `battle640` are the 46-combo guarantee** — they touch 12 of the 46 combos and the whole
share of the shared pipeline they exercise. Add a fourth `sim_case` for the new characters rather
than widening these.

Why they can move by accident: `sim_case` seeds from `sim::BattleConfig` defaults and every
`--roster` slot is `cpu` unless `:human`. Two things in `Battle::Impl`'s constructor draw RNG and
are order-sensitive — the voice inventory (`battle.cpp:141-142`, comment "its selection draws from
the battle RNG") and `configure_battle_start(roster.simulation_random)` (`:150`). Inserting
anything that consumes `next()` before those, or changing `roster.option[]`, moves all three SIM
hashes. Extending `character_names` alone does not (it is not read by the RNG path), but
`weapon_count`/`weaponCountForCharacter` changing *does* change `main.cpp:1074`'s COM fill and hence
`title4p`.

### 6.2 Headless whole-match driving — `simctl`

`src/battle/simctl.cpp:20-35` (usage). A whole match is:

```
simctl --game "$GAME" --roster satoko:1:human rena:0 rena:0 mion:0 --stage 21 \
       --special-mode 0 --ticks 1500 --debug-keys f2@0 \
       --script tests/combos/satoko1-status-traps.plan --events -
```

* `--roster C:W[:human]` ×4 (`:62-77`); `C` is a **name** (`sim::character_name`) or a raw index
  (`std::stoi`, `:75`) — so a new character can be driven as `16:0` before `character_names` grows,
  *except* that everything downstream that calls `character_name` (`:250`) will throw.
* `--script` = `src/battle/script.h`: one `slot from to tokens…` span per line (`:12-52`); tokens
  `x=`, `z=`, `jump`, `melee`, `shoot`, `target`, `guard`, `tactics`.
* Output: one JSON line with `state_hash`, `hash`, `phase`, `finished` and per-slot
  `combo/cpu/minHp/states` (`:248-266`). `--trace`, `--hash-log`, `--events` give per-tick detail,
  `--bullets C:W` prints the item's declared bullets.
* `--debug-keys f2@0` stops the CPU (`battle.cpp:741-751`) so a plan drives one slot.

`tests/combos/*.plan` are the saved plans (3 today), referenced by `DAYBREAK_COMBO_DIR`
(`CMakeLists.txt:793`); `tests/sim_core_test.cpp` loads them. The `combo-test` skill
(`.agents/skills/combo-test/SKILL.md`) is the procedure: prediction first, plan, run, compare.

### 6.3 The tests that will fail the moment the roster grows

| Test | Why | CMake |
|---|---|---|
| `tests/sim_core_test.cpp:67-91` | sweeps **every** `sim::character_count()` × `weapon_count` and ends with `check(combos==46, …)` | `:790-795`, `LABELS asset` (default run) |
| `tests/sim_pose_test.cpp:37-60` | same sweep, and requires every combo's rig frames to align with the core skeleton frame-by-frame, `rigNames.size()==frames.size()+1` | `:805-808`, in `DAYBREAK_SLOW_TESTS` (`:1247-1250`) |
| `tests/weapon_definition_test.cpp:333,347-350` | `checkInt(16, kCharacterCount)`, "hanyu has two weapons" | `:737-738` |
| `tests/locale_coverage_test.cpp:57` | `weaponCountForCharacter` sweep against the locale sheet | `:1127-1129` |
| `tests/participant_layout_test.cpp:39` | `kWeaponIds[0][1]` | `:1143-1145` |
| `select_menu_test`, `select_cursor_test`, `select_row_slidein_test`, `stage_vs_test` | the 16-entry tables | `:1147-1150` |
| `sim_frontend_flow` (= `tests/release_flow_check.py … --recipe=com --fighters=4`) | drives title→select→VS→battle→result and asserts the built roster | `:812-815`, area `frontend` |

For a **whole-match product-path test of a new character**, `release_flow_check.py` is the tool: it
takes `--recipe`, `--rounds`, `--frames`, `--fighters`, `--script`, and asserts the scene chain and
the roster the run built (`tests/release_flow_check.py:18-32, 51-130`). A new recipe with
`--local-players` choosing the new character (main.cpp:1039-1048 scans for a joinable slot-0 item)
would cover select → VS → battle → result for it in one run.

---

## 7. Recommendation — the least invasive seams

Ordered by (blocking value / lines touched). The governing idea: **do not widen the identity space
that 633 branch sites, four `character*3+weapon` switches, three `[16][3]` tables and two 2×8 name
atlases already encode. Add a second, narrow identity and keep the old one intact.**

### S1 — a second constructor for `BattleActorAssets` (or a bytes-emitting asset builder)

`core/battle_actor_assets.hpp` is the only place the ".X + DAT" assumption lives. Two options:

* **S1a (no core edit, preferred):** a `psp_asset_bytes` builder in the product that emits (i) a
  minimal `.X` token stream and (ii) a DAT-format frame table, then calls the existing constructor.
  Zero changes under `src/battle/core/`. Blocked only by the effort of a token writer; the readers
  are already pure functions of bytes (§2.3).
* **S1b (small core edit):** add `BattleActorAssets() = default;` plus
  `void finalize()`/`rebuild_prepared_pose()`, record it in `core/PATCHES.md`. ~10 lines, no
  behaviour change to any existing combo (the existing ctor keeps calling it).

Everything below assumes the PSP model becomes an `xm::Model` + `BattleActorAssets` pair; S1 is its
door.

### S2 — decouple the dispatch key from the roster index in `BattleActionBinding`

This is not an optimisation; it is the only way a new index can enter a fight at all. §1.2's B1
family means every shot/dash/melee row throws for a pair it does not know, and those throws are
unguarded arms of the per-slot loop. There are only two ways past them: add ~50 real rows to the
tables and bodies (i.e. port the PSP state machine, S3), or hand the fighter a pair the tables
already contain. S2 is the second.

`core/battle_action_binding.hpp:7-11` already carries `character`/`weapon`/`original_update`.
Add two fields — e.g. `dispatch_character`, `dispatch_weapon` — defaulting to `character`/`weapon`,
and change `basic_battle_action` to take them separately, e.g.
`basic_battle_action(roster_character, roster_weapon, dispatch_character, dispatch_weapon)`.
Then a PSP fighter is `{roster_shared, /*roster*/16, /*weapon*/0, /*dispatch*/2, /*weapon*/0}` and
runs Keiichi 0's recovered rows over PSP data (§3.4). The `original_update` consistency check at
`development_animated_combat.hpp:640` keeps working because it validates the *dispatch* pair.
This is the seam that buys the most for the fewest lines: **one struct + one factory + the ~158
`action_binding(slot).character` reads stay correct**, because they keep reading the dispatch
identity. The roster identity is already available where it is needed
(`roster.character[i]`, `combat.actor_assets(i)`, `sim::Slot`).

Strictly, `local_battle_roster.hpp:11-23` would carry a parallel `dispatch_character[]` array (or
`BattleActionBindings` would be the only carrier — simpler: keep it in the binding).

### S3 — one new body only if S2's measurement fails

PSP plan step 4 exists to test exactly this: run the PSP's own Keiichi `a` through the new assets
and compare against core Keiichi 0. If the difference is small, S2 is the whole answer for
behaviour. If not, the PSP `Fighter` state machine becomes **one** new `BattleActionPolicy` value
(`psp_table_driven`) in `development_animated_combat.hpp`'s per-slot loop — one dispatch site,
next to the `uses_*` predicates at `:667-673`, with `uses_*` returning false for it. The row
handlers it needs are `character_dispatch`-shaped but `.acs`-driven; keep them out of the 46-row
table (new file, e.g. `core/psp_fighter_body.hpp`), so no existing `character_action_dispatch`
call changes.

### S4 — the roster index still has to exist, but only where it is read as data

Minimum set, in dependency order:

1. `core/character_names.hpp:6` — **do not** extend this 16-entry array to 19 blindly. It is the
   core's identity table *and* `sim::character_count()` *and* the `data/` directory names *and* the
   voice roots. Prefer a `roster_character` that is 19 wide with an explicit "loadable?" predicate
   so `sim_core_test`'s 46-combo sweep (`:93`) and `sim_pose_test` can enumerate the PC 16 only.
   Concretely: `character_count()` stays 16 for the DAT roster, and a separate
   `psp_character_count()`/`psp_character_name()` serves the new three — that keeps every existing
   sweep and every expected value untouched.
2. `core/battle_voice_inventory.hpp:23-28` — bound-check `names()` and let a character with no
   voice root return an empty list instead of throwing. ~4 lines, no behaviour change for 0-15
   (they all have roots). This is required regardless of everything else: it throws inside
   `step()`.
3. `core/battle_victory_identity.hpp:10-14` — the guard must accept the new indices, and the
   **persona ids 16/17 must be remapped** (e.g. to 19/20, or to a separate `Persona` enum) because
   `data/scenario/win/16.txt` and `resultPersonaId` already mean Rena's persona
   (`result_quote.h:48-54`, `tests/result_title_test.cpp:43-46` pins it). This is the one place
   where a naive 16→19 index extension is a *silent* data collision, not a crash.
4. `src/battle/battle.cpp:36-45` — `weapon_count` and `character_name` must answer for the new
   indices (4 weapons, PSP names), and `make_roster:54-56` must stop rejecting weapon 3.
5. `core/roster_ground_melee.hpp:52`, `core/battle_roster_walk.hpp:11`,
   `core/roster_ground_shot_admission.hpp:20-40` — a 17th/18th/19th row and a 4th column, or an
   explicit "not in this table" path that returns a neutral tuning instead of indexing. Prefer the
   latter: a per-combo *override map* keyed by the **dispatch** pair, with the `[16][3]` tables
   kept as the fallback for dispatch pairs 0-47.
6. Product: `weapon_definition.h:173-228` — the cleanest shape is a second table
   (`kPspCharacterCount`, `kPspWeaponIds[3][4]`, `kPspCharacterDir[3]`) and a small
   `rosterEntry(index)` accessor, so `kCharacterCount`/`kWeaponSlots`/`kWeaponIds` keep their
   meaning and the 46-combo expectations in `weapon_definition_test.cpp` stay literally true.
   Every product site in §4.1 then reads through the accessor. The `static_assert`
   (`screen_select.cpp:14-18`) becomes "the diamond table covers the union".

### S5 — art and screens (S4 step 6's consumers)

* Select: give the diamond **new cells** for the three (`kSelectRosterX/Y` sized to the union) and
  keep `kSelectRosterOrder`'s reveal for the existing 16; the loop at `screen_select.h:59-63` and
  the four `_` arrays need to be sized from the accessor, not from a literal.
* `SelectScreen::loaded()` (`screen_select.cpp:373-377`) must stop requiring the four sheets for
  every index — require them per **available** character, so a missing PSP sheet disables one icon
  rather than the screen. This is also the correct behaviour for a texture-pack install.
* Name cells: `data/select/p03` is a 2×8 atlas; three more names need a wider sheet **or** a
  separate PSP name sheet with its own cell rule in `screen_vs.cpp:69` and
  `screen_select.cpp:459/489`. Do not move existing cells: `title4p` (`fingerprints.sh:59`) and
  `locale_screen_check` photograph this art.
* `data/select/w%02d` is 3 rows of 64 px; a 4-weapon character needs a 4th row (or a taller sheet
  read with a different stride at `screen_select.cpp:461`).
* Result portrait `data/win/%02u%c.cnv` — only needed if the new fighters can win a match, which
  they can; either supply `16a/17a/18a` (colliding with nobody, since `battle_victory_identity`
  formats the *roster* index there) or make `screen_result.cpp:53` tolerate a missing sheet.

### S6 — the model, on the render side only

`app/scene.inc:19-38` `appendCharacter` is the single place a fighter's scene model enters. A
`psp` branch there that builds an `xm::Scene` with one `SceneModel{role="character"}` from the GMO
reader (frames in the core skeleton's order, skinned meshes with `Bone::frame` into that same
frame array, materials naming TGA/GIM textures) leaves `setScene`/`updatePose`/palette/shadows/
outlines untouched — `core_pose` then drives it exactly like a PC rig, because
`core_battle.cpp:143`'s only requirement is that the frame count equals the core's bone count.
Weapon props: point `attachFrame` at whatever the GMO calls the hand bone, or skip props in v1
(`setModelVisibility`/`ownerRig` already allow zero props).

### What I would tell the next agent to do first

1. Write the PSP `head`/`lefthand` → channel mapping. `actor_sampled_pose.hpp:35` decides
   lower/upper-body layering by the `"Bip01"` prefix, and with PSP names **every** bone is channel
   0, so `bind(1, …)` writes nothing (`development_animated_combat.hpp:770-771`). This is the one
   place where a non-`.X` skeleton silently loses animation, and it is five lines:
   `actor_animation_channel` needs to take the skeleton (or a precomputed per-bone channel) rather
   than the string.
2. Decide S2 before writing any PSP body. If the binding can carry a dispatch pair, the whole
   "which recovered rows does a new fighter run" question disappears and the work becomes data +
   art + S4.
3. Keep `character_count()` at 16 until the new three can be played end to end; add them through a
   parallel accessor. That single choice keeps `sim_core_test`, `sim_pose_test`,
   `weapon_definition_test` and the six fingerprint cases untouched, which is the only way to know
   the 46 combos did not move.

### The five hard couplings, in one place

1. `character_action_dispatch` (`character_dispatch.hpp:56`) throws for 16-18 and is reached from
   `basic_battle_action` before any branch, from `advance_roster_cpu:6438`, from the three `[16][3]`
   tables and from every `roster_*` admission gate.
2. The per-combo bodies are throwing contracts (§1.2 B1): ~50 `throw "Unsupported/Unrecovered …"`
   sites, reached from unguarded arms of the per-slot loop. A new pair cannot be "let through" — it
   has to be given a pair that already exists (S2) or real bodies (S3).
3. `character_names.hpp:6` is simultaneously the identity table, `sim::character_count()`, the
   `data/` directory list and the voice root; `battle_voice_inventory.hpp:24` throws from inside
   `step()`.
4. `BattleActorAssets` has one byte-only constructor, and the core pose must match the drawn rig's
   frame count exactly (`core_battle.cpp:143`).
5. Indices 16 and 17 already mean "Rena's/Rika's persona" in the win-script and result namespace
   (`result_quote.h:48-54`, `core/battle_victory_identity.hpp:13`).
