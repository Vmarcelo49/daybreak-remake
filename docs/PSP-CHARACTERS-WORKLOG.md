# PSP characters — work log (issue #91)

Branch: `feat/91-psp-characters`. The plan is [`PSP-CHARACTERS-PLAN.md`](PSP-CHARACTERS-PLAN.md);
this file is the running record of what was done, by whom, and why. Newest entries at the bottom
of each section.

## Success criteria (owner, issue #91 task)

1. Satoshi, Miyoko and Okonogi are selectable on the character select screen.
2. They appear on the VS screen.
3. They can be played through whole matches (start → KO/time → results).

## Tooling installed (local only, nothing tracked)

Under `~/tools/psp/` (no sudo needed): Temurin JDK 25, Ghidra 12.2 + kotcrab `ghidra-allegrex`
v21.6 (Allegrex language and PSP PRX loader, which the earlier study lacked), John-K
`pspdecrypt` built from source. `source ~/tools/psp/env.sh` puts them on PATH.

- `EBOOT.BIN` decrypted to sha256 `80363ff7…0608597`, identical to the plan's.
- Ghidra output goes to `local-data/harness/psp/` (ignored). Decompiler dumps are never tracked.

## Facts confirmed this session

- ISO 9660; `PSP_GAME/USRDIR/_pack/gzpack.pck` at LBA 72848, 326,807,872 bytes.
- Pack: u32 count (10772), then `count` rows of `{u32 name_hash, u32 csize, u32 offset, u32 unk}`
  starting at byte 4, offset relative to the pack start, payload gzip.
  `name_hash = crc32(path, 0xFFFFFFFF)` (zlib's crc32 seeded with 0xFFFFFFFF), no leading slash.
  Verified by inflating `g3d/chrm19.gmo` (`OMG.00.1` magic), `activity/chr19a.acs/.acv`,
  `assault/chr19a.atp`, `bin/com_param.bin`, `activity/static_param.bin`.
- The plan's `g3d/chrNNk.gmo` is a pattern: `chr19k.gmo` does not exist; the costume number
  replaces `k` (e.g. `chr190.gmo`). To be enumerated.

## Plan of record (coordinator)

The issue's numbered steps, compressed to what the success criteria need, in dependency order:

| # | Work | Owner | State |
|---|---|---|---|
| A | Extractor: `daybreak --extract-psp=<iso>` → `psp-data/`, hash-checked list, models, art, movesets | Track A + D | **done, merged** |
| B | PSP format study: GMO (mesh/skeleton/motion), GIM/TGA, `.acs/.acv/.atp`, select/VS art | studies | **done** (`docs/psp/research/`) |
| C | PSP executable study: `Fighter`, row handlers, hit geometry, bullets, input | studies | **done** (`docs/psp/research/CODE-MAP.md`) |
| D | Roster expansion: 16→19 characters, slots 3→4, without moving the 46 combos' hashes | Track B | **done, merged** |
| E | Renderer: draw a GMO fighter, scaled | Track A | **done, merged** |
| F | Combat: a PSP fighter playing its own data in whole matches | Track C | **done, merged** |
| G | Select + VS + result screen entries for the three | Track B | **done, merged** |
| H | Whole-match test per combo, fingerprints unchanged | coordinator | pending |

## Design decisions (to be restated in the final report)

D-1 **Roster indices.** The three join after the PC sixteen as product/core indices 16 Satoshi,
17 Miyoko, 18 Okonogi, with four weapon slots each (a–d). The existing tables (`kWeaponIds`,
`character_names`, `sim::character_count()`) keep their meaning for 0–15; the new three are
reached through a separate "PSP roster" table and accessors. *Why:* the 46 combos'
regression hashes, `sim_core_test`'s `combos == 46` and every `[16][3]` table stay literally
true, so "the PC cast did not move" is checkable rather than argued.

D-2 **Combat: borrow a recovered PC body, drive it with PSP data.** A PSP fighter's action
binding names a *dispatch* pair (a PC combo whose recovered row code runs) separately from its
roster pair. The rows run over assets built from the PSP files: PSP skeleton and motions, rows
and timings from `.acs`/`.acv`, damage from `.atp`. Nearest movesets from the study: Satoshi →
Keiichi, Miyoko → Satoko, Okonogi → Tomitake. *Why:* the core has ~50 per-combo bodies that
throw for an unknown pair, and 633 `character==N` sites. A from-scratch PSP `Fighter` body
needs the hit geometry and bullet logic, which the static study has not decoded. Borrowing
gives a fighter that plays through whole matches with the PC engine's guaranteed-consistent
collision, damage, gauges and CPU. Fidelity to the PSP's own move logic is the cost, and
is reported as such (tier 6, port rule).

D-3 **Assets as bytes into the existing constructors.** The PSP model and frame table are
converted in memory to the core's inputs (a binary `.X` token stream and a DAT frame table),
so `BattleActorAssets` and the renderer's `.X` loader need no new path. *Why:* both readers
are pure functions of byte vectors. One converter feeds sim and renderer the same skeleton,
which `core_battle.cpp`'s frame/bone equality check requires.

D-3a (revises D-3) **Converted files in PC layout, one more mount.** The extractor converts the
PSP data into the PC game's own formats, at PC paths, under `psp-data/`: `data/<name>/00.X`
(binary `.X`, PSP skeleton and the 76 motions as animation sets), `data/<name>/0N.dat` (frame
tables written from `.acs`/`.acv`/`.atp`), `data/item/NNN.dat` for weapons, and select/VS
sheets as `.cnv`. Both the core's `AssetSearchPath` and the product's `AssetSource` mount
`psp-data/` after the install. *Why:* every reader already exists and is tested. The files
can be inspected, diffed and unit-tested. The web build's loose-file mount
(`index_directory`) is the same mechanism. Nothing converts at runtime.

D-4 **Extraction converts once.** `daybreak --extract-psp <iso>` reads the pack, checks each
needed file against a tracked SHA-256 list, and writes `psp-data/` beside the executable:
the raw PSP files the converters read, plus the 2D art already converted to the remake's
sheet layout. *Why:* the remake has one texture path (CNV + texture packs), and every PSP
image must be cropped and repacked anyway (art study, `notes/art.md`). Nothing from the ISO
is tracked or shipped.

## Log

### 2026-11-06 — tooling and decompile

- Installed the PSP tool chain under `~/tools/psp` (above). Ghidra 12.2 needs JDK 25.
- Ghidra import with the Allegrex PRX loader, then `.eh_frame` seeding (4190 FDEs, 2444 new
  functions): **6441 functions**, **855** in the fighter range `0x5d000–0x7c000`, matching the
  plan's count. Every address the plan names is a function start. Dump in
  `local-data/harness/psp/decomp/` (`_index.txt` = `addr name size`, one `.c` per function).
- File offset of a virtual address in `EBOOT.dec` = vaddr + 0xc0 (`.text` 0x40 → 0x100,
  `.rodata` 0x18d0c0 → 0x18d180, `.data` 0x1e3a80 → 0x1e3b40).
- 89 RTTI class names survive (`7Fighter`, `6Bullet`, `8Magazine`, `12ModeVSSelect`,
  `26CharSelectFaceImageManager`, `11ModeVSEnter`, `13FighterObject`, …).
- Owner, mid-task: document the PSP version thoroughly (resources, code, data) for later use.
  That map lives in [`docs/psp/`](psp/README.md); raw notes and dumps stay in ignored
  `local-data/harness/psp/`.
- Baseline fingerprints on this branch before any product change match AGENTS.md: SIM
  `746ce7a9cbe6e44a`, `941f3dcd7a679d74`, `f19e8d6d58c37151`; PIX `ff54a85d`, `1fc12c64`,
  `9ecda8ec`. These must not move.
- Dispatched four studies in parallel: pack/format survey, product/core integration map,
  PSP `Fighter` state machine, PSP select/VS/HUD art. Their raw notes go to
  `local-data/harness/psp/notes/`; the reviewed result goes to `docs/psp/`.

### 2026-11-06 — pack and format survey (subagent)

Raw: `local-data/harness/psp/notes/formats.md`, `pack_paths.txt` (7305 of 10772 hashes named).
Corrections to the plan:

- **The PSP numbers its cast differently from the PC.** 01 rena, 02 keiichi, 03 mion, 04 rika,
  05 satoko, 06 shion, 07 irie, 08 akasaka, 09 ohishi, 10 tomitake, 11 takano, 12 chie,
  13 kasai, 14 akane, 15 natumi, 16 hanyu, 17 satoshi, 18 miyoko, 19 okonogi. Measured from
  `.atp` against the PC records; confirmed by byte-identical weapon models (`wpn17d` =
  `wpn02a`, Keiichi's bat; `wpn19dr1/2` = `wpn06cr1/2`, Shion's whip).
- No `%d`-formatted character paths exist: each path is a literal pointed to by the 19×4
  resource table at `0x1b18a0`.
- Costumes: Satoshi 5 (`chr170..174`), Miyoko 7 (`chr180..186`), Okonogi 3 (`chr190..192`).
  Motions `chrm17/18/19`, 76 takes each.
- No `wpn18*` exists. `chr17d`/`chr19d` have no weapon in the table, but the pack holds copies.
- 2D art exists for select and VS: `gra/gim/select/bustup_<name>.gim` (220×130 INDEX8),
  `vs_enter_<name>.gim` (168×132), cut-ins `gra/cutin/ci_<name>_*.gim`, names in the shared
  `vs_enter_chara_name01.gim`. No per-character battle HUD face.
- `.acs` = 16-byte header + 350 rows of `{bytes, n, (f32 time, u32 code)[n]}`. Only 11 rows are
  in every combo (16, 17, 108–110, 172–177). `.atp` = 350×148-byte records (except Hanyu b/d).
  `.acv` = 4 sections; section 1 (164-byte items) is the hit geometry.
- `gmo_blender.py` parses all 15 new costumes and the 3 motion files, but no weapon GMO
  (vertex type `0x180011a3`).
- `.pck` = `count` + `{id, bytes, offset}` + names; voice/se payloads are VAG, eff payloads GMO.

### 2026-11-06 — PSP `Fighter` study (subagent)

Raw: `local-data/harness/psp/notes/fighter.md` (945 lines, addressed), `notes/rowtable.tsv`.

- One `Fighter` class, 30 Hz tick (`FUN_0006adcc`), one motion frame per tick. A row change is
  `FUN_00068aa4`: `.acv` §4 maps row → handler id, `0x1b08f4[id]` is the handler (479 entries);
  192 are thin wrappers over the generic runner `FUN_00077cd8` with baked row arguments.
- `.acv` sections: §1 row program `{f32 time, u32 flags}`, §2 164-byte timed records (hit
  windows; **shape and anchor not decoded**), §3 chain/cancel tables, §4 row → handler id.
- `.acs` codes: `0x8000xxxx` register, `0x8308xxxx` sound/voice, `0x8400xxxx` effect. The two
  "new-only" codes are ordinary: `0x80000401` is Miyoko's, `0x840000e4` is Okonogi's handgun
  muzzle flash.
- `.atp` record 0x94 bytes: +0 power (PC `combat[0]/1000`), +4/+8 PC `combat[5]/[6]/100`,
  +0x14 byte 3 = PC `combat[8]`, +0x88 relation mask, +0x8c motion id.
- The new three use the standard containers (Natsumi's are the odd ones). Their populated rows
  share one vocabulary: 33 core rows, plus 25 extra for Satoshi a, 2 for Miyoko a, 2 for
  Okonogi b.
- Character-specific code that touches the new three: a weapon-node transform for Okonogi a/c
  (`0x5e09c`, `0x64514`); Satoshi is in the effect-0x84 mask (`0x65d10`); `setRow` specials
  for index 0x11 (Miyoko).
- **Unknown:** hit geometry, bullet motion and spawn, `shot_data.bin`, the button layout.

### 2026-11-06 — build tracks dispatched

Three worktrees off `feat/91-psp-characters`, merged back by the coordinator:

| Track | Branch / worktree | Scope |
|---|---|---|
| A | `feat/91-psp-a`, `../dbr-psp-a` | `--extract-psp`, hash list, GMO/GIM → binary `.X` + textures under `psp-data/` |
| B | `feat/91-psp-b`, `../dbr-psp-b` | product roster of 19, `psp-data/` mount in `AssetSource`, select/VS screens and art |
| C | `feat/91-psp-c`, `../dbr-psp-c` | core: dispatch pair in the action binding, `psp-data/` mount in the core, `.acs/.acv/.atp` → `0W.dat` + item dats, whole-match tests |

Contracts fixed between tracks:

- Indices 16 Satoshi, 17 Miyoko, 18 Okonogi; directories `satoshi`, `miyoko`, `okonogi`.
- PSP weapon item ids 101–112 (Satoshi a–d 101–104, Miyoko 105–108, Okonogi 109–112).
- Converted bone names: PSP `root`→`Bip01`, `spine1`→`Bip01_Spine`, `spine2`→`Bip01_Spine1`,
  `neck`→`Bip01_Neck`, `head`→`Bip01_Head`, limbs → the PC's `Bip01_L_*`/`Bip01_R_*`,
  `weapon_r`→`Bip01_Prop1`, `weapon_l`→`Bip01_Prop2`; others keep their PSP names. Animation
  set *i* is PSP take *i*.
- Follow-up study (hit geometry, bullets, input map) running → `notes/combat.md`.

### 2026-11-06 — combat study (subagent; it failed after writing its deliverable)

Raw: `local-data/harness/psp/notes/combat.md` (668 lines, addressed).

- The hit test is a sphere: attacker weapon/bone node to victim hip bone `<= def[0x40+4i] + 60.0`.
  The per-combo `def` block is `bin/chr.fpd[(char*4+weapon)*0x170]`.
- A row's attack record is `atp[acv.S4[row]]`, not `atp[row]`.
- Damage = `atk[0x00] * atk[0x90] * def[0x28|0x2c] * buffs`. Max HP = `def[0x00]`: Satoshi and
  Miyoko 8500, Okonogi 11000.
- Bullets: `shot_data[bullet_attack_data[id][0x90]] = {speed, ±angle}`. The bullet update,
  magazine numbers, and the physical-button → bit map are **not decoded** (§10).

### 2026-11-06 — Track B: the roster carries 19 on the front end

Branch `feat/91-psp-b`. The three are now *selectable* and *visible*; their combat and their 3D
model stay with tracks C/E/F, and a launch without their data reports one clear error instead of
crashing. The contract for their art is [`psp/FRONTEND-ART.md`](psp/FRONTEND-ART.md).

- **Roster (D-1).** `gameplay::kCharacterCount`/`kWeaponSlots`/`kWeaponIds`/`kCharacterDirs` and
  `sim::character_count()` still mean the PC 16 × 3. The three live in their own table
  (`kPspRoster`, `PspRosterEntry`) behind `rosterCharacterCount()` (19 while `psp-data` is mounted,
  16 otherwise), `rosterCharacterDir`, `rosterWeaponCount` (4 for 16..18), `rosterWeaponItemId`,
  `rosterCharacterIndexForDir`, and `comboSlotLabel`/`weaponSlotForItem` now answer over the whole
  roster. **Item ids 101–112** (Satoshi a–d 101–104, Miyoko 105–108, Okonogi 109–112) — clear of the
  PC's shipped 1–46, and the ids Track A/C write `data/item/NNN.dat` at. Dir names `satoshi`,
  `miyoko`, `okonogi`.
- **The mount (D-3a).** `fnd::assets::AssetSource::mountDataRoot(dir)` adds a loose-file root
  consulted after the install's bundles; `read("data/select/16.cnv")` then finds
  `<root>/data/select/16.cnv`, and `--psp-data=<dir>` names the root. A verification run mounts
  only the folder it names, so a `psp-data` beside the binary cannot move a capture — measured:
  `title4p` stays `9ecda8ec…` with `build/linux/psp-data` present.
- **Select screen.** The four diamond tables are 19 entries; the original sixteen are
  bit-identical and the three are appended at (−1,7), (1,7) and (0,8), below the diamond's bottom
  vertex — 60+ units from every other icon, because the recovered 30-unit pass overrides a <50-unit
  fallback and a lattice-step neighbour keeps the cursor on the earlier index (the art study's
  (−1,6), (1,6), (2,5) are 36–48 units from one, i.e. inside that band). Costumes 5/7/3. Art for
  16..18 is optional per file: a missing sheet draws nothing and logs, where the PC sixteen still
  refuse the screen. Names outside the `p03` 2×8 atlas are drawn with the caption face from
  `assets/locale/en.txt` (`select/name`), in Japanese from the roster table otherwise.
- **VS screen.** The portrait is optional for a PSP participant and the name cell is the same
  caption path (its own 40 px face, so it matches the atlas art's weight).
- **Launch.** `frontend_launch.cpp`'s hardcoded `16`s and raw `kWeaponIds` indexing are gone;
  `participants.h`'s unguarded `kWeaponIds` is a bounds-checked roster id. A PSP fighter whose
  `data/item/NNN.dat` does not exist yet stops the run with
  `RESULT: front end: cannot read data/item/101.dat (Satoshi 0)`.
- **Result screen.** Win art for 16–18 has no PSP source (`gra/gim/result/` is shared UI only), so
  a PSP winner's result screen refuses with the missing path named. Win *scripts* stop at id 17 and
  16/17 are already Rena's and Rika's personas, so a PSP winner gets **no** script path —
  `planWinnerQuote` returns empty rather than reading another character's line.
- **Kept on 16, on purpose.** Random COM fill and the off-diamond random roll (a random seat must
  not fail a launch on data that does not exist yet), online selection (peers are not guaranteed
  the same `psp-data`; the bundle hash does not cover it), and story mode.
- **Art.** `tools/asset-tools/psp_select_art.py` generates the four sheet families from the player's
  ISO (`psp-data/`, ignored), with the GIM decoder and the padded-pitch rule copied from the art
  study. Chibi/costume/weapon cells are documented place-holders: the PSP ships no chibi body, no
  per-costume and no per-weapon picture.
- **Checks.** `asset_source_mount_test` (new, `data`), `psp_roster_test` and `select_psp_test` (new,
  `frontend`), `locale_coverage_test` extended for the runtime-text names. Regression unchanged:
  SIM `746ce7a9cbe6e44a`, `941f3dcd7a679d74`, `f19e8d6d58c37151`; PIX `ff54a85d`, `1fc12c64`,
  `9ecda8ec`.

### 2026-11-06 — coordinator: Track B merged

- Reviewed captures of the select diamond (19 icons) and the VS screen with Satoshi: both correct.
- Asked for and merged the result-screen follow-up: win portraits `data/win/16a–18a.cnv` come from
  the bust-up's second pose. A missing PSP portrait or quote degrades instead of refusing.
- **D-5 (Track B, accepted).** The three's icons hang below the diamond at (−1,7), (1,7), (0,8),
  not at the art study's (−1,6), (1,6), (2,5). *Why:* the recovered 30/50-unit selection passes
  would have kept naming an existing neighbour at those spots, which `select_psp_test` measures.
- **D-6 (Track B, accepted).** Random COM fill, the off-diamond roll, story mode and online stay
  on the PC sixteen. *Why:* a random seat must never pick a fighter whose data the player has not
  extracted, and the online bundle hash does not cover `psp-data/`, so peers could desync.

### 2026-11-06 — Track C: the three fighters play whole matches (subagent)

**What now exists.** Roster indices 16 Satoshi, 17 Miyoko, 18 Okonogi (four weapons each, item ids
`data/item/101..112.dat`) are loadable and playable through `sim::Battle` and `simctl`, in any slot,
against any PC combination, to the results screen. `simctl` takes `satoshi:0`..`okonogi:3`.
[`docs/psp/COMBAT.md`](psp/COMBAT.md) is the reference: the dispatch choice per weapon, what is PSP
data, what is borrowed, and every port rule with its tier.

**D-2 implemented as two identities in one binding.** `BattleActionBinding::character/weapon` is the
*dispatch* pair (the combo whose recovered rows run); `roster_character/roster_weapon` is the
*identity* (assets, voice, victory). The 46 PC combos keep them equal, so the ~158 dispatch reads,
the four `character*3+weapon` switches, the three `[16][3]` tables and the ~50 throwing per-combo
bodies needed no edit; only three identity readers moved. One core file added
(`psp_roster.hpp`), six patched, all in `src/battle/core/PATCHES.md`. `character_names`,
`sim::character_count()` and `sim_pose_test`'s sweep are untouched, and the six fingerprints did not
move: SIM `746ce7a9cbe6e44a`, `941f3dcd7a679d74`, `f19e8d6d58c37151`; PIX `ff54a85d`, `1fc12c64`,
`9ecda8ec`.

**Dispatch pairs.** Characters from the moveset study; weapon slot 0 for all twelve, because the
three PC slots of one character share one melee damage profile on the eleven measured moves (a
least-squares table is in COMBAT.md §2) and PSP `wpn17d` is byte-identical to Keiichi's bat anyway.

**D-3a implemented as a converter, not a loader.** `src/psp/psp_moveset.{h,cpp}` turns one weapon's
`.acs`/`.acv`/`.atp` plus the dispatch combo's own `.dat`/item into `data/<name>/0W.dat` and
`data/item/NNN.dat` in the PC layout; `daybreak`'s extractor (Track A) will call the same function,
and `tools/psp_moveset_convert.cpp` builds a whole tree by hand. `psp-data/` mounts after the
install's archives (`BattleConfig::pspDataDir`, `$DAYBREAK_PSP_DATA`, `<install>/psp-data`).

**Two findings that changed the rules.** (1) The `.atp` record of a row is `atp[acv.S4[row]]`, not
`atp[row]` (hit/bullet study, `notes/combat.md` §1.3); the converter indexes it that way. (2) The
first cut picked each phase's animation set by the PSP row's own length. That shortened every attack
row against the borrowed body's timing and cost the fighters most of their damage (Okonogi 0-6k
where the dispatch combo dealt 6-13k). A phase's animation length *is* its row timer, so the set is
now the dispatch combo's own index whenever the model has it, and only an index the model lacks is
remapped, to the set of nearest length. With that, the twelve combos deal damage in the dispatch
combo's own range.

**Verification.** `tests/psp_match_test.cpp` (CTest `psp_match_test`, default tier, skips without PSP
data): every combo plays two full CPU-vs-CPU rounds against a rotating PC opponent set with the
*dispatch combo itself* as the control, one four-PSP match, a scripted human round per fighter
(walk, jump, melee, shot, guard), a determinism repeat and a rollback stress (2821 rewinds agree).
Dated measurement of the twelve combos is in the track's report; the limits are COMBAT.md §5.

**Known and deliberate.** PSP voices are silent (VAG in `.pck`); the item's magazines and bullets
stay the dispatch combo's; PSP bullet motion is undecoded; the animation per row is a placeholder
until `FUN_0001a228` is read; the PSP's `maxHp` (8500/11000) is not applied, the core's 10000 is the
authority. Each is labelled a port rule in COMBAT.md rather than presented as recovered behaviour.


### 2026-11-06 — Track C merged with Track B, and the product's match path

Merged `feat/91-psp-characters` (Tracks A/B's work) into `feat/91-psp-c`. One conflict, in this
file: both sides had appended entries, so both are kept and Track C's sits last. Nothing in
Track B's source conflicted with Track C's; the seams lined up because both used the same contract
(`data/item/101..112.dat`, the three directory names, `psp-data/` after the install).

- **The product's match path now plays a PSP fighter.** `startCoreBattle` passes the root its own
  `AssetSource` mounted into `BattleConfig::pspDataDir`, resolves fighters with
  `sim::character_index` (19-wide) and resolves weapons with Track B's `roster*` accessors
  (`rosterCharacterIndexForDir`, `rosterWeaponCount`, `rosterWeaponItemId`) instead of the
  PC-16-only forms. `--match --psp-data=<psp-data> --sim-roster=<install>/data/satoshi@0,...`
  reaches `RESULT: ok` over 600 frames (tier 5 capture); without `--psp-data` the same command
  fails cleanly at the rig load rather than throwing inside the battle.
- **Two identities, one contract.** The simulation's roster table is
  `src/battle/core/psp_roster.hpp`; the screens' is `src/battle/weapon_definition.h`'s `kPspRoster`.
  Both name the same directories and the same item ids, which is now written down in
  [`docs/psp/COMBAT.md`](psp/COMBAT.md) §4.
- The full default ctest tier and the six fingerprints were re-run on the merged tree.

### 2026-11-06 — coordinator: Track C merged

Reviewed the core diff: 1 new + 6 patched core files, each with a `PATCHES.md` entry. For a PC
combo the dispatch pair equals the roster pair, so the 46 combos cannot be affected; the
fingerprints confirm it. Merged as `7a562201`.

- **D-2 as built.** `BattleActionBinding.character/weapon` *is* the dispatch pair, and the new
  `roster_character/roster_weapon` is identity. *Why:* this routes ~158 dispatch reads, four
  `character*3+weapon` switches, three `[16][3]` tables and ~50 throwing bodies with no edit. Only
  three identity readers moved.
- **D-7 dispatch weapon = slot 0 for all twelve.** Least-squares over the 11 measured moves cannot
  separate one PC character's three slots (they share a melee damage profile). PSP `wpn17d` is
  Keiichi's weapon-a model.
- **D-8 PSP HP not applied.** Damage goes in 1:1 against the core's 10000 per fighter, so all
  fighters stay on one scale. A PSP fighter's time-to-kill is not the PSP's (tier 6, port rule).
- **D-9 victory personas 19/20/21.** 16 and 17 are Rena's and Rika's weapon-2 personas; 18 is left
  as a visible gap.
- Known limits: silent voices (VAG in `.pck`), and the per-row animation is the borrowed combo's.
  Until Track A's model lands, the converter copies the dispatch combo's PC model under the PSP
  name.

### 2026-11-06 — Track A: the extractor and the PSP models

`feat/91-psp-a`, merged with `feat/91-psp-characters` (Track B, then Track C's integration).
Commits: the extractor, the GMO→`.X` conversion, the two-reader test, then the merge.

- **The extractor works on the owner's ISO and nothing else is needed.** `--extract-psp <iso>
  [--psp-data <dir>] [--install <game>]` reads the ISO9660 image, finds
  `PSP_GAME/USRDIR/_pack/gzpack.pck`, inflates the 143 files [`assets/psp/manifest.txt`] lists,
  checks each against the tracked SHA-256 and writes `psp-data/psp/<pack path>`, then runs the
  converters. 21.7 MB of raw payloads in 0.6 s. It runs before SDL, the GPU and the settings: it
  is the one run that writes files. Evidence: tier 4 (`psp_model_test`) and tier 5 (a run on the
  owner's dump; the count, sizes and hashes were also cross-checked against the pack's own index
  read by the local Python reader).
- **The raw list is one tracked file**, paths + sizes + SHA-256 of the inflated payloads, so any
  good dump works and no game bytes enter git. `psp-data/` is ignored. Evidence: tier 3, the
  bytes; the seam is `psp/psp_extract.h`'s converter list, which Track C's moveset converter now
  occupies — its frame tables read the converted `00.X`, so the extractor produces the whole
  tree in one command.
- **Conversion: GMO → the port's binary `.X`** ([`docs/psp/MODEL-CONVERSION.md`](psp/MODEL-CONVERSION.md)).
  15 costumes (5/7/3), 68 or 77 bones, 4 skinned meshes each, all 76 takes as animation sets, and
  the textures decoded from the embedded TGA and the `chrtNN.gim` head atlas. Both readers accept
  every file, which is the point: the renderer draws `xm::loadModel`'s output and the simulation
  reads the core's `XObjectReader`'s, from the same bytes (D-3a).
- **Three port rules** (tier 6, stated as such): bone names become the PC rigs' where the core
  looks a name up (the hand bones throw without them; the `Bip01` prefix is the core's
  upper-body channel); takes are written in reverse file order because both readers register sets
  back to front, so index *i* is PSP take *i*; and the fighter's draw scale plus a half turn
  about Y sit on the root frame. The half turn was **measured**, not assumed: with
  `--camera=front` a PC fighter faces the camera and a converted PSP one showed its back, and
  `chr190.gmo`'s face mesh agrees (z +9.9, mean normal +0.9 in z).
- **Two frame-side details a whole match taught** (tier 5): the mesh-owning frame must be written
  unnamed, because a PC frame table anchors a no-hitbox state on an empty bone name and the core
  turns an unresolvable name into bone 0 and throws; and an empty take must be a two-key hold,
  because a set's length is its last key time and a single key is a zero-length animation the row
  timers divide by.
- **Found, and handed to Track C: their frame tables' set indices are out of range** for a
  76-set model. Only the eleven converted moves remap a phase value; every other state keeps the
  dispatch combo's index (valid for its 124 sets), so satoshi 67 phases in 42 states, miyoko 70,
  okonogi 73 (states 350/360, 400–412, 450/460 among them) point past the end and binding those
  rows throws. Measured with the converted model in place: `psp_match_test` fails 5/178 (shot
  rows unreachable); with the older PC stand-in model it passes 178/178. The fix is a clamp over
  every state, in `psp_moveset.cpp`.
- Also unchanged and still true: the 46 PC combos did not move. The six fingerprints on the
  merged tree are the values in `AGENTS.md`.

### 2026-11-06 — coordinator: Track A merged; integration status

Merged `feat/91-psp-a` (`d702d463`). On the integration branch, `daybreak --extract-psp=<iso>
--psp-data=<dir> --install=<game>` writes the raw files, 15 converted costumes (`.X` + `.cnv`
textures), `data/<name>/0W.dat` and `data/item/101–112.dat`. Reviewed captures: the three
fighters are correctly skinned beside PC Keiichi at plan scale, and Satoshi fights in a match.

Remaining gaps against the success criteria, in order:

1. **Animation index remap** (Track C, in progress). With the real 76-take model, states that
   kept the dispatch rig's index (350/360/400–412/450/460) throw, so shot rows are unreachable.
2. **Which PSP take plays for which PC state.** A per-set similarity study failed its own
   known-answer test: a PC set is a *phase* (median 0.25 s) while a PSP take is a *move*
   (median 1.0 s). Same take index ≈ same move across PSP characters (31/40, 24/37, 14/39 vs 2.5%
   chance). Next step: label the takes visually (subagent running) and map at the **move** level,
   PC state → PSP take.
3. **Front-end art from the C++ extractor.** Today only `tools/asset-tools/psp_select_art.py`
   makes the select/VS/win sheets. A player has no Python, so the extractor must write them.
4. Weapons in hand (unweighted GMO vertex type), voices (VAG), expressions: polish, not criteria.

### 2026-11-06 — PSP take labels (subagent)

Rendered every take of `chrm17/18/19` (and PSP Keiichi `chrm02`) as 6-frame filmstrips and
labelled them by eye. Results kept locally: `notes/take_labels.tsv`, contact sheets in
`local-data/harness/psp/takes/`.

- Takes 0–12 read identically on all four rigs: jump arc, hit flinches, knockdowns, turn, getup.
- Basics: idle 13, walk 15, run 11/14, brake 19, air fall 22, air attack 33, dash 25, swing 10,
  thrust 26.
- No held guard was found, and victory is only a candidate (43). Satoshi 52–60 are static
  placeholders.
- `chrm18/19` root curves sit in a rotated bone frame; the label tables use model space.
- **D-10.** Animation is mapped at the *move* level: PC state → one PSP take, with the phases
  sliced inside it. *Why:* a PC set is a phase while a PSP take is a whole move, so per-set
  similarity failed its own known-answer test. Labels from a human-style visual read are the
  best static evidence, and each table row carries its label confidence (tier 6).

### 2026-11-06 — Track D: the extractor writes the front-end sheets (subagent)

`daybreak --extract-psp=<iso> --psp-data=<dir> --install=<game>` now writes the five sheet families
the select, VS and result screens read for indices 16–18 — `data/select/NN.cnv`, `iNN.cnv`,
`cosNN.cnv`, `wNN.cnv` and `data/win/16a..18a.cnv` — so a player with no Python gets them from the
one command that converts the models and the frame tables. The contract did not move:
[`psp/FRONTEND-ART.md`](psp/FRONTEND-ART.md) §2 is unchanged, and §4 now describes the C++ path.

- **Port, not a rewrite.** `src/psp/psp_select_art.cpp` is `tools/asset-tools/psp_select_art.py` in
  C++, registered as the extractor's `select art` converter (`models`, `select art`, `movesets`). It reads
  only `psp-data/psp/gra/gim/select/` and writes CNV through Track A's own writer, so nothing new
  decodes or encodes at run time. The costume counts and the weapon item ids come from the two
  tables that already own them (`psp::pspFighters()`, `daybreak::psp_item_id`), not a third copy.
- **The GIM decoder needed one rule it did not have.** The padded row pitch is the real row
  ([`psp/research/RESOURCES.md`](psp/research/RESOURCES.md) §8): `vs_enter_satoshi` declares 168
  columns and is 176 wide, `bustup_satoshi` declares 220 and is 224, and there is live art in the
  padding. `psp::decodeGim` now decodes `align(width, align)` texels (`src/psp/gim.cpp`); before it,
  a portrait lost its right 8 columns — a shoulder and a sleeve — and a bust-up its right 4.
  INDEX8, INDEX4 and the palette association were checked against the same reference and are
  correct as they were: the head atlas (`chrt17.gim`, INDEX4 and swizzled) decodes to a clean face,
  which is what Track A's fighter captures already show.
- **D-11: the Python tool stays, as the reference.** It defined the sheets and is what the screens
  were judged against, and it keeps the two entry points a player's extractor has no use for:
  `--dump=<dir>` (build from an already extracted tree, no ISO) and `--preview=<dir>` (PNG copies
  for the eye). It is not required to play and it is not the supported path — the extractor is.
  Nothing was removed, and `--iso` still works on it for A/B work.
- **The two agree byte for byte, measured.** On the owner's dump, all fifteen sheets from
  `--extract-psp` and from `psp_select_art.py --iso` are identical: 0 differing bytes, max diff 0,
  mean diff 0.000000, over five families × three characters (262,144–1,048,576 bytes each). That is
  stronger than this track's bar ("any good deterministic filter") and it is the property that
  makes the screens' pixels independent of which generator wrote them. The resampling is the
  reference's box filter with its arithmetic reproduced: premultiplied alpha, integer division,
  round-half-to-even, and the spec-dropping neighbour count that reads the buffer it is mutating.
- **New test, install-backed (tier 4).** `tests/psp_select_art_test.cpp` (CTest
  `psp_select_art_test`, default tier, label `data`, skips with 77 without `DAYBREAK_PSP_ISO`)
  extracts, then reads every sheet through the product's own CNV decoder and checks the size and the
  alpha in the cells the screens draw from: the portrait reaching the bottom row and the middle
  column, the five chibi art cells drawn and cell (2,1) fully opaque white, the costume cells up to
  the contract's count (5/7/3) drawn and the rest empty, a slot letter and an item id in all four
  weapon rows, the win figure ending on the 492 baseline and reaching the quote band — and that the
  extraction report names all fifteen files. Negative check: with one costume count changed to 6 the
  test fails on `costume cell 5 is empty`, so the assertions are not vacuous.
- **Captures, tier 5, from the extractor's tree only.** `daybreak --extract-psp` wrote
  `local-data/harness/psp/trackD-psp-data` (ignored) and every capture run names exactly that
  folder with `--psp-data`, so no Python output and nothing beside the binary could have
  contributed: the select diamond with all 19 icons and Satoshi's portrait in the blue panel
  (`--frames=200`, `trackD_select.png`), the VS screen with his `vs_enter` art beside Keiichi's PC
  portrait (`--frames=800`, `trackD_vs.png`), and the result screen of a 1v1 he won, his bust-up
  portrait cut at the chest by the quote band (`--screen=result --result-winner=satoshi:0
  --frames=200`, `trackD_result.png`), all in `local-data/harness/psp/captures/`. The install ships
  no `data/select/16*.cnv` and no `data/win/16a.cnv`, so those pixels can only come from the new
  converter.
- **Player-facing side.** `--help` documents the extraction run properly now (what it writes, where,
  why `--install` matters) and gained a real `-h, --help` that prints it and exits 0; before, the
  flag was an "unknown option" line. `README.md` has a plain "PSP characters" section: run once with
  your own ISO, keep `psp-data` beside the game, delete it whenever. `docs/psp/README.md`'s own
  command example used the space form (`--extract-psp /path`), which the parser rejects; fixed
  there and in the header comment that repeated it.
- **Unchanged.** The 46 PC combos: SIM `746ce7a9cbe6e44a`, `941f3dcd7a679d74`, `f19e8d6d58c37151`;
  PIX `ff54a85d`, `1fc12c64`, `9ecda8ec`. The default ctest tier passes with `DAYBREAK_PSP_ISO` set,
  so the PSP suites exercise rather than skip.
- **Known limits.** Two implementations of one transform, kept identical by hand — FRONTEND-ART.md
  §7 says so, and nothing checks it automatically because that would need Python on a player's
  machine. The chibi, costume and weapon cells are still place-holders and the win portrait is still
  the bust-up's smiling pose, both as §4 documents: this track made them reachable without Python,
  not better.

### 2026-11-06 — Track C: every phase plays the fighter's own take

**Defect (found by Track A with the real model).** `psp_match_test` failed 5 of 178 on a tree whose
`00.X` is the PSP fighter's own: Satoshi 0 and Okonogi 0 never reached a shot row, Miyoko 0 dealt no
damage. The converter re-pointed phases only for the eleven converted attacks; every other state kept
the dispatch combo's set index, valid for its 124-set PC model and out of range for the 76-take PSP
one (67-73 phases per fighter, including the whole shot family 350-461). `animations_.at()` threw, so
those rows were unreachable. Reproduced on a fresh extraction before the fix.

**Fix, at the move level** ([`COMBAT.md`](psp/COMBAT.md) §3.1). A PC state plays one PSP take (or one
span of it), and its phases play consecutive slices of that span in proportion to the PC sets they
replace. The slices are extra animation sets the model converter appends after the 76 takes, so sets
0..75 remain PSP take 0..75; each slice carries its PC set's settings record, so the borrowed rows
advance phases when they always did. The pairing is the tracked table `src/psp/psp_take_table.h`,
filled from the visual take labels (`take_labels.tsv`), one row per state with its label confidence.
An unlisted state takes the usable take nearest its length — never an empty or placeholder take,
never `% take_count`. One plan per fighter, made once per extraction and shared by both converters;
the moveset converter refuses a fighter's own model without it.

**Why not the per-set table.** The PC-set → PSP-take similarity study (`take_map.md`) failed its own
known-answer test; a PC set is a phase (≈0.25 s) and a take a whole move (≈1 s), so the pairing
cannot be made at set granularity.

**Also found.** Satoko 0's table repeats two state ids (311, 331), so the plan is keyed by record,
not id. Tracks A and B both declared `Options::pspData` for the same folder; one field now serves
both (7ec34e44).

**Verification.** On a fresh `--extract-psp` with the PC install: every phase of all twelve tables
names a set the model registers, none of zero length, and each model's set count equals its plan's
(220 Satoshi, 228 Miyoko, 224 Okonogi). `psp_match_test` 178/178 on that tree, and 178/178 on the
dispatch-model stand-in tree. `psp_model_test` passes. Fingerprints unchanged: SIM `746ce7a9cbe6e44a`,
`941f3dcd7a679d74`, `f19e8d6d58c37151`; PIX `ff54a85d`, `1fc12c64`, `9ecda8ec`.

**Open.** No take is labelled as a guard or a shot: Satoshi uses his one upper-body take for both,
Miyoko and Okonogi hold idle (air idle in the air). Which take a move plays is a label's judgement,
not the PSP's own row→motion selection, which is still undecoded (`FUN_0001a228`).

### 2026-11-06 — coordinator: Track C's take plan merged, integration complete

- Track C's fix: every phase now plays a *slice* of the fighter's own PSP take. The plan
  (`src/psp/psp_take_table.h`) maps PC state → PSP take from the visual labels, appends the
  slices after the 76 takes, and falls back to the nearest usable length (never `% take_count`).
- Conflict in `src/psp/psp_convert.cpp` resolved by hand: Track D's `select art` converter keeps
  its place between models and movesets in Track C's plan-driven pipeline.
- `psp_match_test` reaches 178/178 with the real PSP models and the dispatch-stand-in tree.
- **D-12 (Track C, accepted).** Guard and shot rows have no labelled PSP take. Satoshi uses take 48
  (his one upper-body take) for both; Miyoko and Okonogi hold idle (air idle in the air).
  *Why:* no take is a held guard or a firing pose, so an idle hold shows the fighter is aiming or
  blocking without claiming a pose the data does not have. Recorded as tier 6.
- **D-13 (Track C, accepted).** Take choices are label judgements, not the PSP's own row→motion
  selection (`FUN_0001a228` stays undecoded). Each row of the tracked table says which label it
  came from and its confidence.

### 2026-11-06 — coordinator verification on the merged branch

All tracks merged into `feat/91-psp-characters`. Verified on the merged tree, with the extractor
run from the owner's ISO into `psp-data/`:

| Check | Result |
|---|---|
| Extraction | 143 raw files hash-verified, 114 converted (models, textures, sheets, 24 moveset files), ~0.6 s |
| Default ctest (`-LE slow`) | 94/95 pass; the one failure is the local `build/package/` leftovers, see below |
| PSP suites with data | `psp_match_test` 178/178, `psp_model_test` and `psp_select_art_test` pass with the ISO |
| Fingerprints | SIM `746ce7a9cbe6e44a`, `941f3dcd7a679d74`, `f19e8d6d58c37151`; PIX `ff54a85d`, `1fc12c64`, `9ecda8ec` — exact |
| Product match, each fighter | all three reach `roundOver=1` with a winner in a CPU-vs-CPU match |
| Product match, all 12 weapons | all twelve launch and play (fixed the `--sim-roster …@slot` parse for the PSP roster) |

- `update_crosscheck_test` fails only because `build/package/` still holds three 0.1.0 zips with no
  `package-manifest.txt` at their root: the Python tool refuses them, the C++ reader accepts them.
  With an empty artifact root the same test passes 41/41, and no update code changed on this branch.
- **D-14 (accepted limitation).** The four weapon slots of a PSP fighter differ in their converted
  frame tables and take plan, but play *almost* identically today: the item file is the dispatch
  combo's (cloned under the PSP id) and the PSP's weapon-specific `.atp` rows land in states the
  borrowed body rarely enters. The slots are selectable and playable; the differences are in
  animation and in a handful of hit records. Named as a D-2 cost, not hidden.

### 2026-11-06 — coordinator: end-to-end check through the real front end

Ran the actual menu path with the PSP data mounted and `tests/scripts/psp-select.txt` (P1 picks
Satoshi and confirms):

```
title (0) → select (34) → vs (624) → battle seats HCCC on data/stage12 (60 s) → result (3893)
```

The battle renders with Satoshi's own model and bat, the HUD, and the opponent. So the three are
reachable through the shipped UI, not only through the simulation API.

Captures kept locally (`local-data/harness/psp/captures/`): `final-select-800.png` (19 icons),
`psp-vs-satoshi.png` / `trackD_vs.png` (VS), `final-flow-battle-3000.png` (a real fight),
`final-match-*.png` (match mode).

### 2026-11-06 — chibi art (exploration, owner continues)

The PSP ships no chibi art, so the select screen's chibi/costume/weapon cells are documented
place-holders. I explored generating style-matched chibis for the three with the owner's local
image stack (`gen.sh`/`edit.sh`, Qwen-Image-2.1 + the anime LoRA, reference-image edits) and the
`image_generate` tool. A first pass produced usable Satoshi sheets (5 pose cells + the white
flash cell in the 3×2 layout, and 4 costume cells) that sit convincingly beside the PC chibis; see
`local-data/harness/psp/chibi/mock/select200.png`. **Nothing is tracked and nothing is wired in:**
the owner stopped the run and will continue it. Turning it into shipped art needs two decisions
from the owner: whether AI-made art is tracked in `assets/psp/chibi/` (or generated once into
`psp-data/`), and which pose set to keep.

---

# PARKED (owner, 2026-11-06)

The owner played the build and the result is not good enough to ship. **This branch is parked for
the future; do not continue the port here without a new order.** The branch is pushed so the work
is not lost. Everything below this line is the state as handed over.

## The owner's findings, from playing the build

1. **Shadows are wrong: the new characters render black.** The PC cast receives the stage's
   lighting and shadowing normally, the three do not. Not investigated. The first places to look:
   the converted model's normals and how the mesh is bound (`src/psp/psp_model.cpp`, the
   `xm::Model` it writes), the skinned-normal path, and the outline/NPR passes in
   `src/render/npr_normals.h` and `shadow_map.h` — the converted `.X` is the only model in the
   build that did not come from the original data, so it is the first suspect.
2. **The animations are wrong.** The owner's read is that the PSP's animation indexing is different
   or that we interpreted it wrongly. This matches what the study found: the PSP's row→motion
   selection (`FUN_0001a228`) was never decoded, so `src/psp/psp_take_table.h` maps PC state → PSP
   take from *visual labels*, not from the game's own rule. The labels are honest but the mapping is
   a hand judgement (tier 6), so wrong takes in the wrong states are expected. Fixing this properly
   means decoding that function, not re-labelling.
3. **Okonogi holds the wrong weapon: a camera instead of the scissors.** This is the documented
   D-14 limit showing: the hand prop comes from the *borrowed* combo's item — Okonogi borrows
   Tomitake, whose weapon is the camera. The PSP weapon models were never converted (their GMO
   vertex type `0x180011a3` has no reader), so no PSP weapon can be drawn in the hand at all.

## What remains to be done, in the order that would matter

1. Decode the PSP's row→motion selection, then rebuild `psp_take_table.h` from it instead of labels.
2. Find and fix the black shading: normals/skinning in the converted model, or the shadow pass's
   treatment of it.
3. Convert the PSP weapon GMOs (add the unweighted vertex type to the GMO→`.X` converter) and hang
   them on the PROPS bones; Miyoko needs a decision (she has no weapon model in the PSP data).
4. Then, and only then, the rest: voices (VAG), expressions (the head atlas), the real PSP item
   data (today every PSP weapon wears the dispatch combo's item), and the 12 combos' differentiation
   (D-14).

## What was saved

- `docs/psp/research/` — the PSP version map (resources, data tables, code map) and, in
  [`notes/`](psp/research/notes/), the complete study notes, the per-row table, the take labels and
  the 7305 named pack entries.
- `tools/asset-tools/psp-research/` — the Python readers that produced all of it.
- [`psp/research/LOCAL-DATA.md`](psp/research/LOCAL-DATA.md) — what was left on disk, where, and
  how to regenerate it.
