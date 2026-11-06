# 2D art for porting Satoshi (chr17), Miyoko (chr18), Okonogi (chr19)

Static reading only: nothing was committed, no branch was switched, no tracked file was
edited. All extracted bytes and decoded PNGs live under ignored `local-data/harness/psp/`.

This note answers four questions: where the PSP 2D art lives, how it decodes, which PSP image
feeds which PC asset, and how the 19-slot roster relates to the remake's 16-slot grid.

---

## 1. Reaching the art

`PSP_GAME/USRDIR/_pack/gzpack.pck` sits at ISO LBA 72848 (byte 72848*2048 = 149192704).
It holds 10772 entries: `u32 count`, then `count * 16` rows of
`{u32 crc32(path, 0xFFFFFFFF), u32 csize, u32 offset_rel_pack, u32 unk}`; payloads are gzip
(occasionally stored). Paths carry **no** leading slash.

Two ways in, both used here:

* **Literal paths.** `EBOOT.dec` contains 1515 fully spelled `/...` path strings; 1449 of them
  resolve in the pack. That gives the whole `gra/cutin/` family (152 files), `g3d/`, `activity/`,
  `assault/`, and most single-instance UI art. List: `notes/literal_hit.txt`.
* **Format string + name pool.** Only two `%s.gim` format strings exist in the binary:
  `/gra/gim/result/%s.gim` @ `0x1ccccc` and **`/gra/gim/select/%s.gim` @ `0x1cd004`**. The
  select-screen pool follows the second one as plain strings (`0x1cd01c`-`0x1ce1d0`) and names
  every select **and** VS image. Both families resolve 100 %:

  ```
  gra/gim/select/%s.gim   bustup_<name>, vs_enter_<name>, vs_bg*, vs_label*, vs_cursor2_*,
                          vs_head_icon, char_name, costume, weapon, new_weapon, bukibase,
                          icon_on, icon_off, cursor__roll, button_*, st_bg0/1, st_cursor2,
                          st_info_mes01, st_label_*, config*, yajirushi__anm_l/r
  ```

The VS screen's 40 images are **not** in a `vs/` directory — they live in `gra/gim/select/`
behind the same format string. That is the single most useful fact for anyone re-deriving this.

Regenerate everything with:

```bash
python3 local-data/harness/psp/scripts/extract_art.py          # dump + decode the art set
python3 local-data/harness/psp/scripts/gim.py --selftest DIR   # decode every GIM under DIR
python3 local-data/harness/psp/scripts/gim.py --info FILE      # block tree + descriptor
```

---

## 2. The art inventory (all 19 roster characters)

Roster order is authoritative and recovered from code, not guessed: `FUN_000c9ed4` loads each
select bust-up into a fixed texture-bank slot via `FUN_000d6c1c(1, slot, ...)`, and the slots
run consecutively from `0x0b`:

| char index (0-based) | chr file | bank slot | `bustup_` name | `vs_enter_` name | cut-in prefix |
|---|---|---|---|---|---|
| 0 | chr01 | 0x0b | rena | rena | rena |
| 1 | chr02 | 0x0c | keiichi | keiichi | keiichi |
| 2 | chr03 | 0x0d | mion | mion | mion |
| 3 | chr04 | 0x0e | rika | rika | rika |
| 4 | chr05 | 0x0f | satoko | satoko | satoko |
| 5 | chr06 | 0x10 | sion | shion | shion |
| 6 | chr07 | 0x11 | irie | *(none)* | irie |
| 7 | chr08 | 0x12 | akasaka | akasaka | akasaka |
| 8 | chr09 | 0x13 | ooishi | ooishi | ooishi |
| 9 | chr10 | 0x14 | tomitake | tomitake | tomitake |
| 10 | chr11 | 0x15 | takano | *(none)* | takano |
| 11 | chr12 | 0x16 | chie | chie | chie |
| 12 | chr13 | 0x17 | kasai | kasai | kasai |
| 13 | chr14 | 0x18 | akane | akane | akane |
| 14 | chr15 | 0x19 | natsumi | natumi | natsumi |
| 15 | chr16 | 0x1a | hanyuu | hanyu | hanyuu |
| **16** | **chr17** | **0x1b** | **satoshi** | **satoshi** | **satoshi** |
| **17** | **chr18** | **0x1c** | **miyoko** | **miyoko** | **miyoko** |
| **18** | **chr19** | **0x1d** | **okonogi** | **okonogi** | **okonogi** |
| — | — | 0x1e / 0x1f | akane_2 / hanyuu_2 | hanyu_2 | — |

`bustup_*` and `vs_enter_*` spell four characters differently (`sion`/`shion`,
`hanyuu`/`hanyu`, `natsumi`/`natumi`) — guess one spelling and you get a false "missing". The
`vs_enter_` pool also carries two names outside the 19-roster (`kyosuke`, `miyo`); they are
unused by the roster and the pool order is **not** roster order (Irie and Takano have a bust-up
but no `vs_enter_` image at all).

Ten families exist per character:

| family | path | pixel size | format | role |
|---|---|---|---|---|
| select portrait | `gra/gim/select/bustup_<n>.gim` | 224 x 130 (h 130/136), **two poses** side by side | index8+256, or rgba4444 | select portrait / VS art source |
| VS entry art | `gra/gim/select/vs_enter_<n>.gim` | 176 x 132/136, **one pose** | index8+256 | VS screen |
| roster head icons | `gra/gim/select/icon_on.gim`, `icon_off.gim` | 192 x 240 = **4 x 5 grid of 48x48**, 19 used | index8+256 | select/VS/HUD icon |
| name plates | `gra/gim/select/char_name.gim` | 256 x 240 = **4 x 5 grid of 64x48**, 19 used | index4, 16 colours | nickname / name plate |
| cut-ins | `gra/cutin/ci_<n>_01..06.gim`, `ci_<n>_sub01/sub02.gim` | 480 x 96 (480 x 80 sub) | rgba5551 / rgba4444 / index8 | cut-in (8 per character) |
| VS FX / logos | `gra/gim/select/vs_enter_vs.gim` 400x256, `vs_bg0/1.gim` 480x272, `vs_bg_blue/red`, `vs_bg_thunder`, `vs_bg_impact`, `vs_bg_center` | — | index8/index4/4444 | VS backdrop + impact |
| VS name cells | `gra/gim/select/vs_enter_chara_name00/01.gim` | 160 x 320 and 160 x 385 | index4 | VS name strips |
| select background | `gra/gim/select/st_bg0.gim`, `st_bg1.gim` | 480 x 272 | index8+256 | "キャラクター選択 / SELECT CHARACTER" |
| roster icon (VS) | `gra/gim/select/vs_head_icon.gim` | 160 x 64 | index4 | VS team head row |
| battle HUD | `gra/gim/ongame/{meter,moji,scope,syouri,caution}.gim` | 256x256 / 512x256 / 400x256 | index8 / **dxt5** / rgba4444 | HUD meters, victory, KO |

There is **no per-character battle-HUD face image** on the PSP either — the in-battle identity
comes from `icon_on`/`char_name` and the ongame sheets, not a dedicated face bitmap.

---

## 3. The GIM decoder (`scripts/gim.py`)

Standalone (stdlib only: `struct`, `zlib`, no PIL). Handles GIM, TGA (uncompressed + RLE,
24/32 bpp) and PNG (8-bit grey/RGB/RGBA/palette, non-interlaced) for reading, and writes PNG.
Exposed as a library and as a CLI (`--info`, `--selftest`, `-i` to pick the image inside a GIM).

### Format, as recovered from the shipped files

Block chain (all values little-endian, blocks form one **flat** sequence):

```
block header (16 bytes)
  +0x00 u16 id            1 Block, 2 Root, 3 Picture, 4 Image, 5 Palette, 6 Sequence, 0xFF FileInfo
  +0x02 u16 reserved      always 0
  +0x04 u32 size          this header .. end of the block (containers span their children)
  +0x08 u32 next_rel      next block = this_offset + next_rel  (0 ends the chain)
  +0x0C u32 data_rel      payload = this_offset + data_rel     (0x10 for every shipped block)
```

Nesting is **not** in the chain — the Root's `next_rel` already steps onto its own first child.
Nesting is only implied by `size`, and the decoder derives depth from size containment.

Image/Palette payload is a 48-byte descriptor:

```
+0x00 u16 header_size    0x30
+0x02 u16 unused         0
+0x04 u16 format         0 5650, 1 5551, 2 4444, 3 8888, 4 INDEX4, 5 INDEX8,
                         6 INDEX16, 7 INDEX32, 8 DXT1, 9 DXT3, 10 DXT5
                         (0x108/0x109/0x10A are the same three DXT layouts, "EXT" spelling)
+0x06 u16 pixel_order    0 linear, 1 PSP-swizzled
+0x08 u16 width          texels; for a Palette the entry count
+0x0A u16 height         1 for a Palette
+0x0C u16 bits_per_pixel
+0x0E u16 pitch_align    always 16
+0x10 u16 height_align   1 for linear images, 8 for swizzled ones
+0x12 u16 dimension_count 2
+0x14/0x16 u16 reserved   0
+0x18 u32 index_rel_start
+0x1C u32 first_plane_rel_start   0x40: payload = descriptor_start + this
+0x20 u32 total_size              descriptor length + pad + plane bytes
+0x24 u32 plane_mask
+0x28..0x2E  u16 level_type, level_count, frame_type, frame_count
```

### The one non-obvious rule — the padded pitch is the real row

`pitch = align(width_bytes, 16)` and `stored_height = align(height, height_align)`, and
`pitch * stored_height` equals `total_size - first_plane_rel_start` on every shipped file.

**The tail of each padded row carries live artwork, not slack.** Decoding the *declared* width
against the padded pitch shears the picture. Read `pitch` bytes per row, contiguous, i.e. the
decoded image is `pitch / bytes_per_pixel` texels wide:

| file | header says | pitch | really is |
|---|---|---|---|
| `bustup_satoshi.gim` | 220 x 130 | 224 | **224 x 130**, two poses |
| `vs_enter_satoshi.gim` | 168 x 132 | 176 | **176 x 132**, one pose |
| `bustup_keiichi.gim` | 220 x 130 | 448 (16 bpp) | **224 x 136** |
| `st_bg0.gim` | 480 x 272 | 480 | 480 x 272 (no padding, unchanged) |
| `char_name.gim` | 256 x 240 | 128 (4 bpp) | 256 x 240 |

So **decoded width = align(declared width, 16)** (in texels; halve the byte pitch twice for
16 bpp, double it for 4 bpp). `GimImage.visible_width` keeps the header's number for callers
that want to crop the padded columns away.

PSP swizzle is the classic chunk layout — 16-byte x 8-row chunks in column-major chunk order,
`offset = ((y/8) * (pitch/16) + x_bytes/16) * 128 + (y%8)*16 + x_bytes%16`. Note the row index
is part of the *chunk address*; adding `y*pitch` on top double-counts it and silently shrinks
the output buffer.

Palettes are `palette.width` entries of `palette.bpp` bits — usually RGBA8888 (256 x 1), but
`vs_enter_vs.gim` ships an RGBA4444 palette, so the entry size must come from the descriptor.

### Verification

* `--selftest dump/art` — **259 GIMs decode, 0 failures**, across index4, index8, 4444, 5551,
  DXT5, linear and swizzled, padded and unpadded pitch.
* `extract_art.py` — **218 assets fetched, 0 missing**; the whole art set for all 19 characters.
* Visual confirmation with an image reader: `art/st_bg0.png` (select background, pixel-exact
  Japanese logo), `art/icon_on.png` (4x5 head icons), `art/vs_enter_rena.png` (168->176 px
  portrait), `art/bustup_keiichi.png`, `art/hanko.png` (padded-pitch 16 bpp, 29x29 stamp),
  `art/char_name.png` (19 name plates), `art/bustup_satoshi.png`, `art/bustup_miyoko.png`,
  `art/bustup_okonogi.png` (the three new fighters, two poses each — blonde Satoshi, blonde
  Miyoko in a pink shirt, Okonogi in his tan coat and yellow tie).

---

## 4. What the remake draws today

### Select screen — `src/frontend/screen_select.cpp`, `screen_select.h`

10 shared sheets (`screen_select.cpp:356`) plus four per-character sheets (`:365-368`):

| PC asset | size | cells | drawn at |
|---|---|---|---|
| `data/select/NN.cnv` 00-15 | 256 x 256 | **one** portrait, pivot (128,256) bottom-centre | `:430` |
| `data/select/iNN.cnv` 00-15 | 256 x 256 | **80 x 128** chibi, 3 wide x 2 tall (6 cells) | `:448` |
| `data/select/cosNN.cnv` 00-15 | 256 x 256 | 80 x 128, 3 x 2 | `:460` |
| `data/select/wNN.cnv` 00-15 | 512 x 512 | 256 x 64, one row per weapon (8) | `:461` |
| `data/select/p03.cnv` | 512 x 512 | **256 x 64** name plate, cell `(char/8, char%8)` -> **16 cells only** | `:459` |
| `data/select/{bg00,bg01,sbg00}.cnv` | 800 x 600 | full background | `:425` |
| `data/select/{p00,P01,P02}.cnv` | 512 x 512 | UI atlas (cursor 128x128, headers 320x32, tags 256x64...) | `:436-507` |
| `data/select/{s1p..s4p}.cnv` | 400 x 600 | four player-column panels | — |

### VS screen — `src/frontend/screen_vs.cpp`

`data/vs/vs01.cnv` (top 800x300 band), `vs02.cnv` (bottom 800x300 band), `vs03.cnv` (256x256
logo, `:90`), `data/select/p03.cnv` for the name cell `(char/8, char%8, 256, 64)` (`:69`), and
`data/select/NN.cnv` for the portrait, drawn 256x256 at pivot (128,256) with the blue team
mirrored (`:84`).

### Battle HUD — `src/hud/`

There is **no per-character sprite sheet in the HUD**. `hud_atlas.h` loads the shared
`data/object/P00..P12.cnv` sheets only (HP frame `P01 (32,192,256,64)`, command label
`P03 (0,0,128,64)`, ring, tags...), and per-fighter identity on the HUD is caption text
(`hud.h`'s caption face). The only per-character *image* outside the select/VS screens is the
result screen's `data/win/%02d%c.cnv` (512 x 512) and the `p03` name cell it reuses.

### What is missing for 17/18/19

`data/select/17.cnv`, `18.cnv`, `19.cnv` and `data/win/17*`, `18*`, `19*` **do not exist**
(the install ships exactly `00..15` portraits, `i00..i15`, `cos00..i15`, `w00..w15`, and
`p03` has room for exactly 16 name cells). So all three new fighters need new files, and
`p03` must grow (512x512 -> 512x704, or a second name sheet) before the VS screen can name them.

---

## 5. Asset map — PC need -> PSP source -> transform

Poses: the PSP `bustup_*` sheet holds **two** poses (neutral | alt) in one 224x130
image, left and right halves of roughly 112 px each. The PC needs one pose per file, so crop.

| PC asset | PSP source | transform |
|---|---|---|
| `data/select/NN.cnv` select portrait + VS portrait (256x256, pivot bottom-centre) | `gra/gim/select/vs_enter_<n>.gim` (176x132, one pose, whole body incl. shoulders) | crop to the alpha bounds, scale 176 -> 256 wide (x1.45), paste into 256x256 anchored **bottom-centre** (pivot 128,256), transparent fill |
| (alternative, better framing for 17-19) | `gra/gim/select/bustup_<n>.gim` right or left 110x130 half | crop one ~112x130 half, scale x2.3 to 256 wide, anchor bottom-centre |
| `data/select/iNN.cnv` chibi (256x256, 3x2 of 80x128) | `gra/gim/select/icon_on.gim` 48x48 head cell #(n) (`icon_off` = dimmed state) | **not a like-for-like replacement** — the PC cell is a full 80x128 chibi body, the PSP icon is a 48x48 head. Either upscale the head into cell (0,0) of an otherwise transparent 80x128 (acceptable: the draw only shows the head anyway) or keep the PSP chibi models out of scope |
| `data/select/cosNN.cnv` costume icons | `gra/gim/select/costume.gim` (256x256, index4) | the PSP costume sheet is shared, not per-character; slice the cells matching the character's costume count |
| `data/select/wNN.cnv` weapons | `gra/gim/select/weapon.gim` (256x304, index4) + `bukibase.gim` (146x15) | same shared-sheet slice; weapon rows are already 256 wide |
| `data/select/p03.cnv` name cell (256x64, cell (n/8, n%8)) | `gra/gim/select/char_name.gim` cell #n, **64x48** | crop 64x48, scale x4 to 256x192 (or x2 to 128x96 and let the 256x64 cell letterbox); paste into a 512x512 sheet -> **must become 512x704** to hold 19 cells |
| VS name strips | `gra/gim/select/vs_enter_chara_name00/01.gim` (160x320 / 160x385, index4) | already per-character strips; slice by row |
| VS backdrop source | `gra/gim/select/vs_bg0.gim` / `vs_bg1.gim` (480x272) | scale 480x272 -> 800x600 (x1.667, y2.2) or letterbox; the PC uses vs01/vs02 as 800x300 bands |
| VS logo | `gra/gim/select/vs_enter_vs.gim` (400x256) | scale to the 256x256 `vs03` draw |
| VS portraits for 17-19 | `vs_enter_satoshi/miyoko/okonogi.gim` (176x132) | as the select portrait row |
| cut-ins | `gra/cutin/ci_<n>_0X.gim` 480x96, `_sub` 480x80 | already 480 wide; scale to the 800x600 canvas or keep at native and place |
| select background | `gra/gim/select/st_bg0.gim` / `st_bg1.gim` (480x272) | this is the PSP's own select screen; the PC has its own 800x600 `sbg00`, so **not needed** |

**Size relationship to state once:** the PSP canvas is 480x272, the PC canvas 800x600. The
horizontal factor is 800/480 = **1.667**; the vertical factors differ per element because the
PSP art is authored for a 272-tall screen and the PC for 600 — so anything full-bleed needs a
non-uniform stretch (1.667 x 2.206), while sprite art (portraits, icons, name plates) must be
resized by a single factor off its own pixel size to avoid distortion. A 176x132 PSP portrait
into the PC's 256x256 pivot-bottom cell is x1.45 uniform.

---

## 6. Roster layout: 19 PSP slots vs the remake's 16

The remake's diamond is three parallel `constexpr` tables in
`src/frontend/screen_select.h:22-24` — `kSelectRosterX[16]`, `kSelectRosterY[16]` (units of
**48 px horizontally, 36 px vertically**, `screen_select.h:176`) and `kSelectRosterOrder[16]`.
Those are 16 slots; three more fighters need three more slots, and the tables are `[16]`
fixed-size so they must grow together (`kSelectCostumes[16]` at `:25` is the fourth).

**What the PSP stores.** The PSP does *not* need a coordinate table for its roster: it ships the
icons **already packed** as the 4 x 5 grid of `gra/gim/select/icon_on.gim` / `icon_off.gim`
(192 x 240, 48 x 48 cells, 19 used), and `char_name.gim` packs the name plates the same way
(4 x 5 of 64 x 48). Whatever the PSP's drawer does per frame, the roster *order* is the packed
order — i.e. character `k` is cell `(k % 4, k / 4)`. The authoritative order itself is not in a
coordinate table but in the loader `FUN_000c9ed4` @ `0x000c9ed4`, whose texture-bank slots
`0x0b + k` give index -> bust-up name directly (table in §2); the string pool it reads is at
`0x1ccfc8`-`0x1cd0d0` and the format string at `0x1ccf44`.

I did **not** locate a 19-entry icon-position table in `EBOOT.dec`'s rodata. A scan for
19- or 38-element small-integer arrays over `0x1c0000`-`0x240000` produced one 16-pair `int16`
candidate at `0x1e04f0` (`(-4,-1),(0,0),(-3,-1),(1,0),(2,0),(-2,-1),(3,0),(-1,-1),(-3,-1),
(1,0),(-4,-1),(0,0),(3,0),(-1,-1),(2,0),(-2,-1)`) — that is 16 pairs, not 19, and its shape
does not read as a diamond, so it is **not** claimed as the layout. Treat the PSP's on-screen
diamond as still unrecovered; it is also unnecessary, because the packing order is known.

**Recommendation for the three extra slots.** Do not guess PSP positions — extend the remake's
own diamond. `kSelectRosterX/Y` currently use x in `-3..3` and y in `0..6`; three free-looking
positions adjacent to the existing shell are `(-1,6)`, `(1,6)` and `(2,5)` (each within the
current 48/36 unit bounds and outside the 50-unit selection radius of its neighbours if placed
one unit further out), and `kSelectRosterOrder` must be re-sorted so the three new characters
are reachable in the same order the PSP lists them (indices 16, 17, 18 = Satoshi, Miyoko,
Okonogi). `kSelectCostumes[16]` (same line block, `screen_select.h:25`, mean 3.4 over the 16)
needs real counts for the three. Note the PSP select art does **not** give them directly: only
`akane` and `hanyuu` ship a second bust-up (`bustup_akane_2`, `bustup_hanyuu_2`, bank slots
0x1e/0x1f), and Satoshi/Miyoko/Okonogi ship exactly one each — so the PSP costume count has to
come from `activity/`/`assault/` data, not from the select art. Do not copy a number from the
art.

---

## 7. Recommendation: decode at runtime or convert at extraction?

**Convert once, ship PNG (or a re-packed CNV), do not make the game read GIM.**

Reasons, in order of weight:

1. **GIM is dead weight in the product tree.** The remake already owns one texture container
   (`src/assets/cnv.h`) with a verified decoder, a texture cache keyed by material name
   (`TextureCache`), a texture-pack override path, and a web path that shares it. Adding a
   second container means a second decoder, a second cache, a second pack-override story and a
   second thing to keep working on WebGPU. The PSP art is not going to change.
2. **The art needs a transform anyway.** Every mapped asset in §5 is cropped, scaled, re-anchored
   or re-packed into a different cell grid. Decoding GIM at runtime would only move the decode
   step; the crop/scale/repack still has to happen, and doing it once offline keeps the runtime
   free of per-character layout special cases (the padded-pitch quirk in §3 would otherwise have
   to be re-implemented in C++ from a notes file).
3. **`psp-data/` would be a third asset root.** The game already resolves `data/**` through
   `assetSource()` (bundle-first, filesystem otherwise) and texture packs beside the executable.
   A `psp-data/` root would sit outside that, so the "which pixels win" question (already
   settled once for `P01.cnv`, see `hud_atlas.h`) would need a new precedence rule.

The counter-argument — provenance and re-extraction — is real but is served better by keeping
`gim.py` + `extract_art.py` + this note in the corpus: the conversion is reproducible from the
ISO in one command, so nothing is lost by shipping only the output.

Concretely: add the three portraits as `data/select/17.cnv`, `18.cnv`, `19.cnv` and the three
name cells into a grown `p03` (512x704), generated by a script under `tools/asset-tools/` that
runs `gim.py` over the ISO and the transforms in §5. Keep the intermediate PNGs untracked (the
art is the rights holders', per AGENTS.md).

---

## 8. Open items

* **PSP select-screen icon coordinates** are not recovered (§6). Not needed: the 4x5 packing
  order gives index -> cell.
* **`vs_enter_` is missing for Irie and Takano** (indices 6 and 10). If they are ever ported,
  their VS art must come from the `bustup_` sheet.
* **`scope.gim` (`gra/gim/ongame/`) is DXT5**; the decoder implements DXT1/3/5 but the result
  was not visually re-checked against a known-good DXT reference.
* **PC name cells are 256x64 while PSP name plates are 64x48** — a 4:3 vs 4:1 aspect mismatch.
  The PSP plate is a two-line Japanese name; the PC cell is a single wide plate. Scaling x4
  vertically over-sharpens; x2.67 horizontally is the honest match. Decide once, when the
  three plates are cut.
