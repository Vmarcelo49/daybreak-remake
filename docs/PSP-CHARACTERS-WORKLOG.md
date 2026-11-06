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
| A | Extractor: `daybreak --extract-psp <iso>` → `psp-data/`, hash-checked list | subagent | pending |
| B | PSP format study: GMO (mesh/skeleton/motion), GIM/TGA, `.acs/.acv/.atp`, select/VS art | subagents | pending |
| C | PSP executable study: Fighter state machine, row handlers, `.acv` hit geometry | subagents + Ghidra | pending |
| D | Roster expansion: 16→19 characters, slots 3→4, without moving the 46 combos' hashes | subagent | pending |
| E | Renderer: draw a GMO fighter, scaled | subagent | pending |
| F | Core: one PSP fighter body driven by the tables | subagents | pending |
| G | Select + VS screen entries for the three | subagent | pending |
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
