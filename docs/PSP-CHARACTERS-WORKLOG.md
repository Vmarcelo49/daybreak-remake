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
