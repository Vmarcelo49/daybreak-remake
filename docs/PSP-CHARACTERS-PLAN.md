# PSP characters plan

The owner ordered this on 2026-10-31: bring the three fighters that only exist in *Higurashi Daybreak
Portable Mega Edition* (PSP, ULJM05557) to this port. They are Satoshi Houjou, Miyoko Tanashi and
Okonogi, each with four weapons, so 12 combos. Only the study below exists; nothing is built. Do the
steps in order: each ends with something that can be run and checked, except where marked.

## Decisions

From the owner, 2026-10-31:

| Question | Decision |
|---|---|
| Project rules | "Esse caso é especial então nenhuma regra se aplica a ele." See below for what this overrides |
| Data | Nothing is converted to `.dat`. An extractor collects only what we need and leaves it as raw, decoded files |
| Source | The player supplies their own PSP ROM. Nothing from it goes into git or into a release |
| Art | Changed the same day: the PSP's own models, scaled to a height that fits the PC cast. Remaking them in the PC's style is cancelled for now, as too much work, and may return later. See [the parked attempt](#parked-okonogi-in-the-pcs-style) |

So this plan may do what these would otherwise forbid: hard rule 2 and D3 (no conversion, `.X` only),
D14 and the ban on hand-written combat (the core as the only combat authority). The exception covers
this plan only. It does not change the rules for the 46 existing combos, whose regression hashes must
not move.

Chosen here, and easy to change:

- The extracted folder is `psp-data/`, found beside the executable, as texture packs are.
- The extractor checks each file it collects against a tracked SHA-256 list, not the ISO's hash, so
  any good dump works. The dump studied has sha256
  `170b8a8e1aa546f549809243d68dd4c34e33f69e682ab669e820180830a7160c`, 931,201,024 bytes.
- The port's tracked files hold paths and hashes only.
- Dialogue and story for the three are out of this plan until versus works.

## What the study found

Static reading of the PSP data and of its decrypted executable, on 2026-10-31. Nothing was run. This is
evidence about the PSP build. It says nothing about the original PC game at runtime, and the meanings
of table fields below are inferred unless an address is given.

**The pack.** `PSP_GAME/USRDIR/_pack/gzpack.pck` holds a u32 count (10772), then 16-byte rows of
`name_hash, csize, offset, unknown` sorted by hash, then gzip payloads. It is compressed, not encrypted.
`name_hash = zlib.crc32(path, 0xFFFFFFFF)`, with the path written without its leading slash, so a known
path is enough to find a file. Reading these files does not need the executable.

**What each fighter needs.** Character files are numbered 17 Satoshi, 18 Miyoko, 19 Okonogi; in code the
index is 0-based, so 16, 17, 18.

| File | What it is |
|---|---|
| `g3d/chrmNN.gmo` | Skeleton and motions, one file for all four weapons. 76 chunks at 30 fps |
| `g3d/chrNNk.gmo` | Mesh per costume (5, 7 and 3). The model the port draws |
| `g3d/chrtNN.gim` | 10 head pictures on Okonogi's: 8 expressions, hair, scalp. The body's texture is a TGA inside `chrNNk.gmo` |
| `activity/chrNNx.acs`, `.acv`, `assault/chrNNx.atp` | The moveset of weapon `x` (`a` to `d`) |
| `activity/chrNNx_voice.pck`, `chrNNx_se.pck`, `chrNNx_eff.pck` | Voices, sound effects, effects. Satoshi and Okonogi also have `chr6Nx_voice.pck` |
| `g3d/wpn17[a-d].gmo`, `wpn19ar[12]`, `wpn19b`, `wpn19cr[12]`, `wpn19dr[12]` | Weapon models. The pack has no `wpn18` by that pattern, and the `d` rows of the table name no weapon |

Shared by everyone: `activity/static_param.bin`, `bin/bullet_attack_data.bin`, `bin/com_param.bin`,
`bin/chr.fpd`, `bin/gauge_data.bin`, `bin/shot_data.bin`.

That list is 118 files and 26.9 MB once inflated: Satoshi 11.3, Miyoko 6.6, Okonogi 8.8, shared 0.2. The
table also names `chrNN_eff.pck`, which the pack does not have. Portraits and select-screen art are
extra and not counted.

| Character | a | b | c | d |
|---|---|---|---|---|
| Satoshi | 愛用のバット | プレゼントのクマ | 安物の傘 | a second bat (`wpn_bat`, Keiichi's texture) |
| Miyoko | 奇跡の10円玉 | お子様ランチの旗 | ハートキャンディー | unnamed |
| Okonogi | 枝きりバサミ | ハンドガン | のびのびハンド | a whip (Shion's texture) |

**The executable.** Decrypted with John-K/pspdecrypt, sha256
`80363ff749cfb7aee216f8390eff6f5a873b5d51c2dcf804be6cd30094608597`. RTTI names survive.

- There is one `Fighter` class and one `Bullet` class. No class per character or per weapon.
- `0x1b08f4` is a table of 350 row handlers, chosen by row through `FUN_000654ac`, never by character.
  192 of them fall into one generic runner, `FUN_00077cd8`. The per-tick loop is `FUN_0006adcc`.
- `0x1b18a0` (`FUN_0005d4c0`) is the per-weapon resource table, stride 0x50, 19 × 4 slots, with no code
  pointers. `0x1b3060` lists costumes, 19 × 9.
- Code that names a character: at least 88 comparisons in 30 functions, and the new three in about 9
  places (`0x5e09c`, `0x64514`, `0x62e5c`, `0x6390c`, `0x69ef0`, `0x68aa4`, and the mask in `0x65d10`).
  Those counts come from a text search of the decompile, so they are a floor.
- The fighter's code is about 118 KB (`0x5d000`–`0x7c000`, by address range). The PC's per-combo update
  handlers span about 1.75 MB.

**The moveset tables.** 350 rows each, about 94 KB per weapon. `.acs` rows are lists of
`(float time, u32 code)`, with 71 distinct codes in 7 families. Only `0x80000401` and `0x840000e4` are
exclusive to the new characters. `chr16b` and `chr16d` use other header versions of `.acv`.

**The PC and the PSP share numbers.** Measured on 11 moves across 44 PC combos:

| PSP `.atp` field | PC record | Agreement |
|---|---|---|
| word 0 | `combat[0] / 1000` | 330 of 459 samples |
| word 1 | `combat[5] / 100` | 97% of those 330 |
| word 2 | `combat[6] / 100` | 98% of those 330 |
| byte 3 of word 5 | `combat[8]` | 95% of those 330 |

The move map was chosen from words 0 to 2, so those rows are partly circular; `combat[8]` is the
independent check. PC id to PSP row: 300→107, 301→109, 302→110, 310→112, 311→114, 320→163, 330→124,
331→126, 332→167, 340→172, 341→174. Hit timing is not confirmed: 11 of 42. Akasaka and Oishi's weapons
`a`–`c` were rebalanced.

Each new fighter has a nearest older moveset, though none is a clone: Satoshi near Keiichi, Miyoko near
Satoko, Okonogi near Tomitake.

**What this means.** On PC the behaviour of a move is code, one body per combo. On the PSP it is data
read by one fighter. So converting tables to `.dat` could never carry the moves by itself, and 12 bodies
are not needed either: one is.

## Architecture

```
player's ISO ──> extractor ──> psp-data/   raw files, hash-checked
                                  ▼
renderer          the PSP's mesh, skeleton, motions and textures, scaled per fighter
                                  ▼
src/battle/core/  one PSP fighter body, reading .acs/.acv/.atp from psp-data/
                  sharing the core's collision, damage and gauge with the 46 existing combos
```

**The body.** A port of the PSP `Fighter` state machine, citing addresses, as one new body in the core.
It must fight the existing combos in one deterministic simulation.

**The art.** Everything drawn comes from `psp-data/`, so no art is tracked and the PC install is not
involved. These models will look different from the PC's; the owner accepts that for now.

**Height.** The PSP draws its whole cast close to one size, on two skeletons (head joint 108.4 or 114.8),
while the PC separates adults from children. Heights are the bind-pose top of the mesh, hair included, in
file units; the PSP's come from `chrNN0.gmo`, the PC's from each `00.X`.

| PC | Top | | PSP | Top |
|---|---|---|---|---|
| Akasaka, Ohishi, Irie, Tomitake, Kasai | 177–182 | | Okonogi | 155.8 |
| Akane, Chie, Keiichi, Takano | 146–153 | | Miyoko | 151.9 |
| Mion, Shion, Natsumi, Rena | 140–144 | | Satoshi | 149.5 |
| Satoko, Rika | 128–133 | | | |

Starting scales, to be judged by the owner's eye beside the cast:

| Fighter | Target top | Scale | Why |
|---|---|---|---|
| Okonogi | 178 | 1.14 | With the PC's grown men |
| Satoshi | 145 | 0.97 | A boy, under Keiichi and over his sister Satoko |
| Miyoko | 130 | 0.86 | A child, with Rika and Satoko |

The scale is on the drawn model only. Whether hit shapes and movement scale with it is open: it changes how
the fighter plays, so step 4's measure and step 5's fights decide it, not the look.

## Steps

### 1. Extractor

A C++ tool in the product, since players have no Python: `daybreak --extract-psp <iso>`, later reachable
from the menus. It reads the ISO, the pack and the file list, writes `psp-data/`, checks hashes and
refuses a dump that fails with a plain message.

Check: run it on the owner's ISO; every file on the list arrives with the right hash. Without an ISO,
the test skips, and says so.

### 2. Readers

Read a GMO mesh, skeleton and motions, GIM and TGA textures and VAG audio, from `psp-data/`.

Check: an install-backed test plays each of the three skeletons through all its animated slots
(Satoshi 52, Miyoko 38, Okonogi 41) with no bad bone or NaN.

### 3. Okonogi drawn in the port

The renderer draws the PSP's mesh and textures on its skeleton, in a real motion, at the scale in the height
table. His expressions are the `chrtNN.gim` pictures. `tools/asset-tools/gmo_blender.py` is the reference for
the format: its import of these files matches a separate calculation from their raw values to 0.0018 units at
keys over 9 takes, which checks the import against the file, not against the game. It reads the first
costumes of the three new fighters; the other costumes are not tried, and `chr030` and `chr040` use vertex
types it does not handle yet. Which take is the idle is not known, and the 84 curves on the
`wapon_controll_*` bones (target `0x42`) were left out.

Check: a capture of Okonogi beside the PC cast, for the owner's eye on style and height.

### 4. The control

Build the PSP fighter body and run the PSP's Keiichi `a` on it, using data the PC also has, against core
Keiichi 0. Compare hits, damage, timing and movement over scripted fights.

Check: a measured difference per move. **This decides the plan.** If the body is far from the core on a
combo where we know the answer, nothing it does for a new combo can be trusted.

### 5. Okonogi plays

Okonogi + each weapon, in a battle against the existing roster, with his PSP model. This needs the
roster limits raised: `kCharacterCount` 16→19 and `kWeaponSlots` 3→4 in `src/battle/weapon_definition.h`,
used by 9 product files, and the select screen.

Check: a fight script per weapon, the regression hashes for the 46 combos unchanged, and the owner plays.

### 6. Satoshi and Miyoko

Both on their PSP models, at their scales. Miyoko has no weapon models in the PSP's table, so read her
code first: she appears at `0x68aa4`.

Check: as in step 5.

### 7. The rest

CPU (`bin/com_param.bin`), voices and effects if not yet in, select-screen art, and a story route if the
owner wants one. For online, both players need the same `psp-data/`, which the peers' bundle hash has to
cover.

## Risks and open points

- **Fidelity has no PC reference.** The new three never existed on PC, so step 4's measure is the only
  bridge, and anything beyond it needs the PSP itself under an emulator, which is not in this plan.
- **Two skeletons.** PC bones are `Bip00_*` and `Bip01_*`; PSP bones are `head`, `lefthand` and so on,
  with hair chains and no `Prop1`. PC-side hit records anchored on `Bip01_Prop1` do not carry over.
- **Scale and play.** A fighter drawn at 1.14 whose hits stay at 1.0 may look wrong, and one whose hits
  scale plays differently from the PSP. See the height section.
- **Hit geometry.** Where a PSP hit's shape and anchor live (probably `.acv`) has not been read.
- **Motion rate.** PSP motions are 30 fps; the sim is 60 Hz.
- **Decompile limits.** The study's Ghidra run had no Allegrex language pack. 1 of 855 functions in the
  fighter range has undecoded instructions, but vector math may read wrong elsewhere.
- **Ordering.** [`ONLINE-PLAN.md`](ONLINE-PLAN.md) stays the priority for everything but what the owner
  starts here by name.

## Parked: Okonogi in the PC's style

Cancelled on 2026-10-31 as too much work for now, and kept for a possible return. The owner's verdict on the
first head: funny, but players would probably not like it. Everything was seen in Blender stills, never in
the game.

The owner puts the problem mainly in the texture, and a next try starts here: the eyes are much too wide,
the hair could be simpler, and the join between the top of the forehead and the head looks deformed.

The method: Keiichi's PC body bound to the PSP skeleton, with a head reshaped from Kasai's PC head and a new
texture painted on Kasai's UV layout.

- **The PC model in Blender.** The owner's [X2Blend](https://github.com/Vmarcelo49/X2Blend) was rewritten
  with its own pure Python `.X` reader and imports the file's keys without a rebake: commit `a4d3b13` on that
  repository's `python-rewrite` branch, pushed but not merged into its `main`.
- **The bind.** `tools/asset-tools/psp_fit_body.py` plays all 42 of Okonogi's actions on Keiichi's body with
  no bake. The skeletons are close in proportion; the real difference is the rest pose, arms at 45 degrees on
  the PC and a T on the PSP. So each limb segment is scaled to the PSP length and a rigid transform per bone
  takes it onto the PSP bone at the skin. Worst 0.0015 units at keys over 9 takes against the raw file, and
  no tearing beside the PSP fighter in 5 takes. The PC's fist is one shape, so the finger bones past
  `finger1` move nothing; a weapon in the hand was not tried.
- **The head.** `tools/asset-tools/psp_head_okonogi.py` and `okonogi_face_paint.py`: rounder crown, wider
  jaw, 454 faces, a ponytail on the PSP's `downhair1` bone, a 128 pixel texture. No expressions, because the
  eye is painted, and the clothes are still Keiichi's. These tools read the user's install, so they hold no
  game art.

The built files contain PC and PSP art, so they stay in the ignored `.local-analysis/okonogi-art/`:
`okonogi_head.blend` (the whole fighter, with its 42 actions), `keiichi_on_psp_rig.blend`, `okonogi.blend`
(the PSP fighter as imported), the texture, the review sheets, the owner's portrait references, and in
`rebuild/` the three PSP files and the review scripts. A fresh clone will not have them.

## Reading the executable again

1. `pspdecrypt` on `PSP_GAME/SYSDIR/EBOOT.BIN`. It is a PRX whose image starts at address 0.
2. Patch `e_type` to 2 for the import. Take function starts from `.eh_frame`: 4121 FDEs.
3. Ghidra headless with `-processor MIPS:LE:32:default`, seed those starts as functions, then decompile
   each. `rea` refuses this ELF: its Allegrex profile wants static `ET_EXEC` with a MIPS ABI flags record.

Decompiler dumps stay out of git; cite addresses.
