# PSP fighters in combat

Satoshi, Miyoko and Okonogi (roster indices 16, 17, 18) fight in the same simulation as the PC
cast, through `sim::Battle` and `simctl`. This document records what they are made of: which PC
combo's recovered code each one runs (plan decision D-2), what the converter writes into the PC
game's own data layout (D-3a), and every rule that is a port rule rather than recovered behaviour.

Companion documents: [`docs/PSP-CHARACTERS-PLAN.md`](../PSP-CHARACTERS-PLAN.md) (the plan),
[`docs/PSP-CHARACTERS-WORKLOG.md`](../PSP-CHARACTERS-WORKLOG.md) (decisions and the log).

## 1. Two identities per fighter

A PC combo is one thing: `{character, weapon}` names both the fighter and the recovered update body
that runs it. A PSP fighter needs two, because the PSP's own `Fighter` state machine is not ported:

| identity | fields | selects |
|---|---|---|
| **roster pair** | `BattleActionBinding::roster_character`, `roster_weapon` | `data/<name>/0W.dat`, `data/item/NNN.dat`, the voice bank, the victory identity and portrait |
| **dispatch pair** | `BattleActionBinding::character`, `weapon` | the recovered update body, the `[16][3]` tuning tables, `switch(character*3+weapon)`, the CPU decisions, weapon visuals and trails |

For all 46 PC combos the two are equal, so nothing the 46 combos read changed. A PSP fighter keeps
its roster pair and borrows a dispatch pair, which is the only way past the ~50 per-combo bodies
that throw `Unsupported`/`Unrecovered` for a pair they do not know (`advance_battle_animated_combat`
calls them from unguarded arms of the per-slot loop).

Why borrow at all: on the PSP a move is data read by one `Fighter`; on the PC a move is code, one
body per combo. Writing the PSP `Fighter` here would be a second combat engine, and its hit
geometry, bullets, input and stats tables are only partly decoded. Borrowing gives a fighter that
plays whole matches on the core's collision, damage, gauges and CPU. The cost is that a PSP fighter
moves like the PC combo it borrows, and that cost is what the tests measure against that combo.

Identity stays 16 wide for the PC cast: `character_names`, `sim::character_count()`, the `[16][3]`
tables and the `character*3+weapon` switches are untouched. The three PSP entries live in
`src/battle/core/psp_roster.hpp` with four weapon slots each, and `sim::psp_character_count()`,
`sim::character_name()`, `sim::weapon_count()`, `sim::dispatch_combo()` and
`data/item/101.dat .. 112.dat` reach them.

## 2. The dispatch pair, per weapon

Characters follow the moveset study (nearest older moveset): **Satoshi → Keiichi (2)**,
**Miyoko → Satoko (3)**, **Okonogi → Tomitake (6)**.

Weapon slot: **0 for all twelve combinations**. Measured, not assumed — for each PSP weapon the
eleven moves whose PC-state ↔ PSP-row pairing the study established (§3.1) give an `.atp` power
vector; the same eleven PC states give the dispatch character's damage bases; the table is the
least-squares distance to each of that character's three PC weapon slots:

| PSP weapon | Keiichi 0 / 1 / 2 | Satoko 0 / 1 / 2 | Tomitake 0 / 1 / 2 | chosen |
|---|---|---|---|---|
| 17a Satoshi bat | 1.142 / 1.169 / 1.142 | — | — | Keiichi 0 |
| 17b Satoshi present | 0.906 / 0.939 / 0.906 | — | — | Keiichi 0 |
| 17c Satoshi umbrella | 1.596 / 1.568 / 1.596 | — | — | Keiichi 0 |
| 17d Satoshi second bat | 0.583 / 0.634 / 0.583 | — | — | Keiichi 0 |
| 18a–18d Miyoko | — | 2.156 / 2.156 / 2.156 | — | Satoko 0 |
| 19a Okonogi scissors | — | — | 1.307 / 1.307 / 1.307 | Tomitake 0 |
| 19b Okonogi handgun | — | — | 1.268 / 1.268 / 1.268 | Tomitake 0 |
| 19c Okonogi stretch hand | — | — | 1.307 / 1.307 / 1.307 | Tomitake 0 |
| 19d Okonogi whip | — | — | 0.935 / 0.935 / 0.935 | Tomitake 0 |

The three slots of one PC character share one melee damage profile, so the metric separates only
Keiichi's slots (and then by 0.03 on 17c, which is noise). Two further pieces of evidence agree with
slot 0:

* **Byte-identical weapon models.** PSP `g3d/wpn17d.gmo` is PSP `wpn02a.gmo` (Keiichi's bat) and PSP
  `wpn19dr1/2.gmo` are PSP `wpn06cr1/2.gmo` (Shion's whip); Satoshi's fourth weapon *is* Keiichi's
  weapon-a model, and the PSP resource table itself leaves `chr17d`/`chr19d` pointing at it.
* **Melee vs shot.** All four Satoshi weapons are held objects and all four Okonogi weapons are
  swung or fired in the hand, while the `.atp` of one fighter's four weapons populate the same
  shared row vocabulary (`94..176`) — the PSP's own shot pseudo-rows (340/341) are populated in
  *none* of the twelve, so the split that matters on the PC side (melee rows vs the 350/360/400
  shot family) is not measurable from `.acs`/`.atp`. Miyoko's coin and candy are the one clearly
  projectile-flavoured set, and Satoko 0 is the trap/curved-shot weapon of the pair.

Sharing one dispatch slot also means the twelve fighters differ only where the PSP data differs,
which is exactly D-2's claim. A later refinement can change the table in `psp_roster.hpp` alone.

## 3. What comes from the PSP and what is borrowed

`src/psp/psp_moveset.{h,cpp}` converts one weapon at a time at extraction time (Track A's extractor
calls it; `tools/psp_moveset_convert.cpp` and `tests/psp_match_test.cpp` call the same function):

```
in    activity/chrNNx.acs  .acv  assault/chrNNx.atp      the PSP moveset
in    data/<dispatch>/0W.dat, data/item/NNN.dat          the borrowed PC combo, read from the install
out   data/<name>/0W.dat                                 frame table in the PC layout
out   data/item/NNN.dat (101..112)                       the weapon item, under the PSP id
```

The frame table starts as the dispatch combo's own, so every PC state the borrowed code addresses
already exists with a valid animation and hit record. Eleven moves are then overwritten from the PSP
data — the ones whose PC-state ↔ PSP-row pairing the study measured:

| PC state | PSP row | | PC state | PSP row |
|---|---|---|---|---|
| 300 | 107 | | 320 | 163 |
| 301 | 109 | | 330 | 124 |
| 302 | 110 | | 331 | 126 |
| 310 | 112 | | 332 | 167 |
| 311 | 114 | | 340 | 172 |
| | | | 341 | 174 |

Everything else — idle, walk, run, guard, hurt reactions, jump, the shot rows 350/360/400-412,
hypermode entries, the state priority windows — keeps the dispatch combo's behaviour. The PSP rows
the borrowed code has no state for (Satoshi's 226-237 and so on) are read and reported but cannot
be ported without the PSP's own row→state semantics.

| what | source | tier |
|---|---|---|
| damage `combat[0]` = `.atp[hid]+0x00 × 1000`, `combat[5]` = `+0x04 × 100`, `combat[6]` = `+0x08 × 100`, `combat[8]` = `+0x14` byte 3 | PSP `.atp` record of the row's handler (`atp[acv.S4[row]]`, not `atp[row]`) | 3/6: the plan measured 330/459, 97%, 98% and 95% agreement over 44 PC combos; re-checked exactly on PSP `01a` row 107 against Keiichi's state 300 |
| damage scale `+0x90` multiplies the power | PSP `.atp` | 2 (`FUN_000690ec`) |
| hit volume: a sphere at the weapon bone, radius 110 | PSP `bin/chr.fpd` `def[+0x3c] + def[+0x40]` = 60 + 50 for every combination | 2 for the formula (`FUN_0006a8cc`), 6 for the unit identity below |
| hit time | PSP `.acv` §2 record times (the row's window list) | 2 for "the time field is what the row timer compares" (`FUN_00069824`); 6 for the frame conversion |
| animation set per phase | a slice of the PSP take its state plays (`src/psp/psp_take_table.h`), appended to the model after the 76 takes | 6: the PSP's row→motion table (`FUN_0001a228`) is undecoded; the takes are chosen from the visual take labels, §3.2 |
| animation settings per set (blend, hold, texture events) | the dispatch combo's record for the PC set a slice replaces | 6: keeps the borrowed rows' phase timing; the PSP has no such record |
| magazines, bullet list, bullet models | the dispatch combo's item | 6: PSP magazine numbers are undecoded and its bullet motion is not decoded at all |
| every other row, every tuning table, the whole row machine | the dispatch combo | 6 (this is D-2 itself) |

### 3.1 The conversion rules that needed a decision

**Units.** The PSP authors distances in centimetres; the PC cast is also authored at 1 unit = 1 cm
(a PC adult's bind-pose top is 177-182 units). The PSP hit sphere therefore transfers as 110 units
of the PC's `extent`, and the PC record is written as shape 0 (a sphere centred on the record's bone,
`battle_hit_query.hpp`) anchored on `Bip01_Prop1`, the bone the PC rig hangs a weapon on.

**Time.** The PSP ticks at 30 Hz with one motion frame per tick; the PC row timers count frames of
0.016 s (62.5 Hz, `actor_animation_clock.hpp`). PSP times are multiplied by 40/19.2 ≈ 2.0833. A
window timed beyond the phase's own animation length would never open (the row timer advances the
phase first), so the converted times are proportional-mapped inside 85% of the phase's length.

**Animation index.** A phase names an animation set by index, and the load path throws for one the
model does not register (`battle_actor_assets.hpp`, `animations_.at`). The borrowed table's indices
are the dispatch PC model's (124 sets); a PSP fighter's own model has 76 takes. So every phase is
re-pointed, and the unit of the pairing is the *move*, not the set: a PC set is one phase of a move
(about a quarter of a second), a PSP take is a whole move (about a second), and the per-set
similarity study found no reliable one-to-one match at that granularity
(`local-data/harness/psp/notes/take_map.md` §6).

The rule, in `plan_psp_animation` (`src/psp/psp_moveset.cpp`):

1. **Each PC state plays one take**, or one span of it, from the tracked table
   `src/psp/psp_take_table.h` (§3.2).
2. **Its phases play consecutive slices** of that span, each as long as its share of the state: the
   PC set it replaces, measured on the dispatch PC model. A single-phase state plays the whole span.
   Slices share their boundary key, so a phase ends on the pose the next one starts from.
3. **Each slice is a new animation set**, appended by the model converter after the takes. Sets
   0..75 stay exactly PSP take 0..75; set 76+i is slice i. Identical slices (same take, span and
   settings) are written once: 220-228 sets per fighter, under the core's 256.
4. **A slice keeps its PC set's settings record** (blend frames, hold flag, texture events), so the
   borrowed rows advance phases exactly when they did on the PC model: the row timer moves to the
   next phase once the phase's tick counter passes its set's length, and that length is the slice's.
5. **A state the table does not name** takes the usable take nearest its own length (ties to the
   lower index): never an empty or placeholder take, never `index % take_count`. Two to five states
   per fighter end up here — rows the borrowed code reaches rarely or never (132, 232, 339, 342,
   413, 135, 186, 452). The plan logs every one.

The plan is a contract between two converters, so `daybreak --extract-psp` makes it once, before
the models, and hands the same plan to the model converter (which writes the slices) and the
moveset converter (which writes the phase values and the settings section). The moveset converter
refuses a fighter's own `00.X` without a plan, and checks that the model registers exactly the
plan's set count. Without the PC install there is nothing to plan over; the extractor then writes
the models with their 76 takes alone and skips the movesets, as before.

A tree built by `tools/psp_moveset_convert` alone has no converted model: it copies the dispatch
combo's PC model in as a stand-in and keeps the borrowed indices, which are valid for it. That is a
simulation-only tree.

### 3.2 The take table

`src/psp/psp_take_table.h`, one table per fighter, one row per PC state: the take, an optional key
frame span, and the evidence. Built from the visual take labels
(`local-data/harness/psp/notes/take_labels.tsv`) — every row a port rule, its label's confidence in
the row. The movement basics are shared on all three rigs: idle 13, walk 15, the jump as spans of
take 0 (crouch 0-10, takeoff and rise 10-30, apex and fall 30-48, landing 48-64, read off the root
height curve), light flinches 1/2, launches 5, face-down 9, down/KO 6, getup 12, the round-start drop
22. Attacks use each fighter's labelled attack takes: swing 10, lunge/thrust 26, dash lunge 25, air
attack 33 (Satoshi, Okonogi); Miyoko has only the swing, so her other attacks are its kin rows.

No take is labelled as a guard or as a shot. Satoshi's single upper-body-only take (48) stands in for
both, which suits rows layered over walking legs; Miyoko and Okonogi hold their idle on the ground
and their air idle (32, 49) in the air. Those rows say so (`kin`, `hold`). Satoshi's takes 52-60 are
static placeholders and are excluded from the fallback.

**Hit points.** The PSP's `maxHp` is 8500 (Satoshi, Miyoko) and 11000 (Okonogi); the core's fighters
have 10000. Damage is written 1:1, so a PSP fighter's effective time-to-KO against the PC cast is
longer than it was on the PSP. Relative balance between the twelve is preserved, and no rule table
is invented.

## 4. Where the tree is mounted

`psp-data/` is a second asset directory, mounted **after** the install's archives
(`AssetSearchPath` reads the mounts first, then indexed directories), so a PC name can never be
shadowed by the converted tree and the PSP files only fill its gaps. The simulation looks for it in
`BattleConfig::pspDataDir`, then `$DAYBREAK_PSP_DATA`, then `<install>/psp-data`; the product sets
the field from the root its own `AssetSource` mounted (`--psp-data=<dir>`, or `psp-data/` beside the
executable outside verification runs). Nothing here converts at runtime.

The two halves name the same roster twice, on purpose: the core cannot include the product's tables,
so `src/battle/core/psp_roster.hpp` holds the indices, the four slots, the item ids and the dispatch
pairs for the simulation, while `src/battle/weapon_definition.h`'s `kPspRoster` and its
`roster*` accessors hold the directory names, the display names, the item ids and the
"is it mounted" gate for the screens. The item range 101..112 is a contract between them.

## 5. Verification, and what it does not prove

`tests/psp_match_test.cpp` (CTest `psp_match_test`, default tier, skips without PSP data) runs each
of the twelve combos through a full CPU-vs-CPU round twice, with a rotating PC opponent set; the
same round again with the **dispatch combo itself** in slot 0 as a control; one four-PSP match; a
scripted human round per fighter (walk, jump, melee, shot, guard); a determinism repeat and a
rollback stress on a PSP match. Per round it asserts no throw, the result reached, a winner, both
sides dealing damage, and the PSP fighter taking damage; per combo, that it dealt damage and reached
a melee row and a shot row — unless the control also failed to, which is the D-2 comparison and is
printed rather than silently accepted.

Tier 4 at most: it proves the simulation runs on real game data, both casts together, to the results
screen. It says nothing about whether a PSP fighter behaves like the PSP. Not covered here, in
order of what would change the rules most:

1. **The PSP `Fighter` state machine** (rows, cancels, velocities, `.acv` §1/§3) is not ported, so
   the row a button selects is still the borrowed combo's.
2. **Hit geometry beyond the sphere**: the `.acv` §2 records also carry movement and row-transition
   data (`combat.md` §1.2) which is not applied.
3. **Bullets**: PSP bullet motion, homing and spawn are undecoded; a PSP fighter fires the dispatch
   combo's bullets. Missing `data/bullet/<item>/` files fall back to the core's basic projectile,
   the same fallback the shipped PC archives already need for two of their own holes.
4. **The PSP motion per row** (`FUN_0001a228`). The poses come from the PSP's own takes now, but
   which take a move plays is the visual label's judgement (§3.2), not the PSP's own selection.
   Guard and shots have no labelled take at all.
5. **The render side**: a PSP fighter draws with whatever art Track A/E produce. Nothing in
   `docs/psp/COMBAT.md` covers rendering.

## 6. The product's match path

`startCoreBattle` (`src/app/scene.inc`) hands the simulation the same converted root its
`AssetSource` mounted, resolves each fighter with `sim::character_index` (19-wide) and each weapon
with the product's own `roster*` accessors, so `--match --psp-data=<dir>
--sim-roster=<install>/data/satoshi@0,...` plays a real match with a PSP fighter in it. Verified as
a capture (tier 5): `RESULT: ok` over 600 frames, and the same command without `--psp-data` fails
cleanly at the rig load instead of throwing inside the battle.
