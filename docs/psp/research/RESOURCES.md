# PSP version — resources map

*Higurashi Daybreak Portable Mega Edition* (ULJM05557). **Evidence:** static reading of the ISO, the
pack and the decrypted executable. File offsets cited are into the decrypted `EBOOT.BIN`. The
enumeration scripts and the full path list are kept locally under `local-data/harness/psp/`
(`notes/pack_paths.txt`, `scripts/enumerate_paths.py`). No game data is reproduced here.

## 1. ISO layout

| Path | LBA | Bytes | What |
|---|---|---|---|
| `PSP_GAME/SYSDIR/EBOOT.BIN` | 48 | 2,711,920 | encrypted PRX (decrypts to 2,711,572) |
| `PSP_GAME/SYSDIR/BOOT.BIN` | 54752 | 2,711,572 | |
| `PSP_GAME/SYSDIR/UPDATE/*` | | | firmware update, irrelevant |
| `PSP_GAME/USRDIR/_pack/gzpack.pck` | 72848 | 326,807,872 | **all game data** |
| `PSP_GAME/USRDIR/bgm/*.at3` | | | music (ATRAC3), loose |
| `PSP_GAME/ICON0.PNG`, `PIC1.PNG`, `PARAM.SFO` | | | XMB |

## 2. `gzpack.pck`

```
u32 count                                   (10772)
count × { u32 name_hash, u32 csize, u32 offset, u32 unk }   from byte 4, sorted by name_hash
gzip payloads at pack_start + offset, csize bytes each
name_hash = zlib.crc32(path, 0xFFFFFFFF)    path without a leading slash, e.g. "g3d/chrm19.gmo"
```

Nothing is encrypted. The hash cannot be reversed, so names come from guessing: 7305 of the
10772 entries are named. The unnamed ones are 2763 `se/*.vag`, about 550 adventure `.buf`, 146 GIMs
(480×272 screens, small text plates), 2 prop GMOs and 4 small tables. **Every character, weapon,
moveset, select/VS, cut-in, voice and effect file is named.**

## 3. How paths are spelled

- Character, weapon, moveset and effect paths are **literal strings** in `.rodata`. The 19×4 weapon
  resource table at `0x1b18a0` points at them, and the costume table `0x1b3060` points at the models.
  No `chr%02d` format exists.
- The only `%s` image formats are `/gra/gim/select/%s.gim` (file `0x1ccf44`; it serves select
  **and** VS art) and `/gra/gim/result/%s.gim`. Each has its name pool beside it.
- Sound: `/se/se%03d.vag` (shared SE), `/se/W%02d_%02d_%03d.vag` (voice, middle field = voice
  bank 00–23), `/bgm/%s.at3`, `/movie/%s.pmf`, `/adv/D%02d_%d.buf`.
- Romanisation differs between families: `bustup_sion`/`ci_shion`, `bustup_natsumi`/`vs_enter_natumi`,
  `bustup_hanyuu`/`vs_enter_hanyu`, `ooishi`. Try every spelling.

## 4. Character numbering

File numbers 01–19; the code uses 0-based indices (file − 1). **Not the PC order.**

| PSP | Name | PC index | | PSP | Name | PC index |
|---|---|---|---|---|---|---|
| 01 | rena | 0 | | 11 | takano | 7 |
| 02 | keiichi | 2 | | 12 | chie | 11 |
| 03 | mion | 1 | | 13 | kasai | 12 |
| 04 | rika | 4 | | 14 | akane | 13 |
| 05 | satoko | 3 | | 15 | natumi | 15 |
| 06 | shion | 5 | | 16 | hanyu | 14 |
| 07 | irie | 10 | | **17** | **satoshi** | new |
| 08 | akasaka | 9 | | **18** | **miyoko** | new |
| 09 | ohishi | 8 | | **19** | **okonogi** | new |
| 10 | tomitake | 6 | | | | |

There are three independent sources:

- `.atp` values against the PC combat records (margins are wide; Akasaka is assigned by elimination
  because his weapons were rebalanced).
- Byte-identical weapon models (§6).
- The select-screen load order in `FUN_000c9ed4`.

## 5. Per-character files

| Pattern | What |
|---|---|
| `g3d/chrNNk.gmo` | mesh per costume `k` = 0..8 |
| `g3d/chrmNN[x].gmo` | skeleton + 76 motion takes (30 fps); per weapon `x` for some characters |
| `g3d/chrtNN.gim` | head atlas: 10 unique 64×64 INDEX4 pictures stored twice (20 pictures) — 8 expressions, hair, scalp |
| `g3d/wpnNN<x>[rN].gmo` | weapon models (unweighted meshes with `locator_*` bones) |
| `activity/chrNNx.acs`, `.acv`; `assault/chrNNx.atp` | moveset of weapon `x` = a..d ([DATA-TABLES](DATA-TABLES.md)) |
| `activity/chrNNx_voice.pck`, `_se.pck`, `_eff.pck` | voice (VAG), SE (VAG), effect models (GMO) per weapon |
| `activity/chr5Nx_voice.pck`, `chr6Nx_voice.pck` | second voice bank for files 07–10, 13 (→ 57–60, 63) and 17, 19 (→ 67, 69) |
| `activity/chrNN_eff.pck` | named by the resource table, **absent for all 19** |

Shared files: `activity/static_param.bin` (732), `bin/chr.fpd` (27,968 = 76 × 0x170),
`bin/bullet_attack_data.bin` (119,184 = 764 × 0x9c), `bin/shot_data.bin` (6,600 = 330 × 0x14),
`bin/com_param.bin` (18,744), `bin/gauge_data.bin` (912; no reader found).

## 6. The three new fighters

| | Satoshi (17) | Miyoko (18) | Okonogi (19) |
|---|---|---|---|
| Costumes | 5: `chr170..174` | 7: `chr180..186` | 3: `chr190..192` |
| Skeleton | `chrm17`, 68 bones | `chrm18`, 77 bones | `chrm19`, 77 bones (with `tail1..4`) |
| Weapon a | 愛用のバット, `wpn17a` | 奇跡の10円玉, no model | 枝きりバサミ, `wpn19ar1/ar2` |
| Weapon b | プレゼントのクマ, `wpn17b` | お子様ランチの旗, no model | ハンドガン, `wpn19b` |
| Weapon c | 安物の傘, `wpn17c` | ハートキャンディー, no model | のびのびハンド, `wpn19cr1/cr2` |
| Weapon d | no table entry; `wpn17d` == `wpn02a` (Keiichi's bat) | unnamed, no model | no table entry; `wpn19dr1/dr2` == `wpn06cr1/cr2` (Shion's whip) |
| Moveset sharing | — | `.acv` a == c == d; `.atp` a == b == c | `.acv` c == d |
| Voice | `chr17x` + unique `chr67x` | `chr18x` | `chr19x` (`chr69x` duplicates it) |

No `wpn18*` exists anywhere in the pack.

## 7. 2D art

All menu art is GIM. Sizes below are the true decoded sizes (see the pitch rule in §8).

| Family | Files | Size, format |
|---|---|---|
| Select bust-up | `gra/gim/select/bustup_<name>.gim` (19 + `akane_2`, `hanyuu_2`) | 224×130, 2 poses side by side, INDEX8 |
| VS face | `gra/gim/select/vs_enter_<name>.gim` (no irie, takano; extra `kyosuke`, `miyo`) | 176×132, INDEX8 |
| Select icons | `icon_on.gim`, `icon_off.gim` | 192×240 = 4×5 cells of 48×48, roster order |
| Name plates | `char_name.gim` (4×5 of 64×48); `vs_enter_chara_name00/01.gim` (INDEX4) | 01 holds 北条悟史 / 田無美代子 / 小此木 |
| VS furniture | `vs_enter_vs`, `vs_bg0/1`, `vs_bg_{blue,red,center,impact,thunder}`, `vs_head_icon`, `vs_label_*`, `vs_cursor2_*` | |
| Select furniture | `st_bg0/1`, `costume`, `weapon`, `new_weapon`, `bukibase`, `button_*`, `yajirushi__anm_*` | |
| Cut-ins | `gra/cutin/ci_<name>_{01..06,sub01,sub02}.gim` | 480×96 (sub 480×80), INDEX8 |
| Result | `gra/gim/result/{PLAYER,COM%d,button,hanko,key_word,back,back_2}.gim` | |
| HUD | `gra/gim/ongame/{meter,moji,syouri,scope,caution,pause_*}.gim` | shared, no per-character face; `scope` is DXT5 |

## 8. Containers

**GIM.** Pixel formats 5650, 5551, 4444, 8888, INDEX4/8/16/32 and DXT1/3/5 (`0x108–0x10a`
aliases) occur. Order 1 means swizzled (16-byte × 8-row tiles). Two rules matter:

- **The padded row pitch is the real width.** Pixels past the declared width hold live art, so the
  decoded width is `align(width, 16)` texels. Example: `bustup_satoshi` declares 220 but is 224.
- The swizzle chunk address already includes the row, so adding `y*pitch` again counts it twice.

**TGA.** Each body texture is a colour-mapped TGA stored inside its costume GMO, in chunk `0x8013`.

**GMO.** `OMG.00.1PSP` magic, then chunks `{u16 type, u16 header_size, u32 size}`, with the payload at
`header_size`. Chunk types:

- `0x0003` model
- `0x0004` bone (`0x8041` parent, `0x8048` translate, `0x804b` quaternion, `0x8044/45` blend bones and
  offsets)
- `0x0006` mesh, `0x0007` vertex array (`u32 type, u32 count`)
- `0x0008` material, `0x000a` texture, `0x000b` motion (`0x80b1` range, `0x80b2` fps, `0x80b3` bone/target/curve)
- `0x000c` curve (format low nibble: 0 constant, 1 linear, 4 slerp)

Vertex types: the character meshes are `0x2001d3a3` (8 u8 weights, stride 32), and the weapons are
`0x180011a3` (unweighted, stride 24). A few models use u16 or f32 weights (`chr030/040/056`). The
local census lists all 28 types.

**PCK.** `u32 count` + `count × {u32 id, u32 payload_bytes, u32 offset}` + a NUL-padded name table +
payloads. `payload_bytes` excludes the payload's own header, so it is not a block length.

- Voice and SE payloads are VAG (`VAGp`, PSP ADPCM). Ids are shared across characters, but each
  pack maps an id to its own VAG.
- Effect payloads are GMO (`g3d/effNNN.gmo`).

**VAG.** A standard PSP ADPCM container.
