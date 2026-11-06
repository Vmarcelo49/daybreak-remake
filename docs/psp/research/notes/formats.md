# Higurashi Daybreak Portable — pack, formats and the three PSP-only fighters

Study of `PSP_GAME/USRDIR/_pack/gzpack.pck` from *Higurashi Daybreak Portable Mega Edition*
(ULJM05557) and of the decrypted `EBOOT.BIN`. Everything below is **static reading of the
PSP build**: it says nothing about the PC game at runtime, and field meanings are inferred
unless an address or a file offset is given.

Evidence tiers used here (see `AGENTS.md`): tier 3 = original static prints / file bytes;
tier 6 = inference from those bytes. Nothing here is a runtime observation.

| Item | Value |
|---|---|
| ISO | `Higurashi_Daybrake_Portable_Mega_Edition_JPN_PSP-Caravan.iso`, 931,201,024 bytes, sha256 `170b8a8e1aa546f549809243d68dd4c34e33f69e682ab669e820180830a7160c` |
| pack | `PSP_GAME/USRDIR/_pack/gzpack.pck` at LBA 72848 (= byte 149,192,704), 326,807,872 bytes |
| pack index | u32 count = **10772**, then 10772 × 16-byte rows `{u32 name_hash, u32 csize, u32 offset, u32 unk}`, sorted by hash |
| payload | gzip stream at `pack + offset`, `csize` bytes |
| `name_hash` | `zlib.crc32(path_bytes, 0xFFFFFFFF)`, path **without** a leading slash |
| EBOOT | decrypted with pspdecrypt, 2,711,572 bytes, sha256 `80363ff749cfb7aee216f8390eff6f5a873b5d51c2dcf804be6cd30094608597`, PRX image base 0 |
| inflation | whole pack inflates to 514,006,581 bytes |

**Resolved so far: 7305 of 10772 entries** (see `pack_paths.txt`, one line per path with
uncompressed size, sha256 of the inflated payload and the packed size). Every hash relevant
to characters, weapons, movesets, select/VS art, voices, effects and the shared tables is
resolved. What is left unnamed is 2763 `/se/*.vag` audio files, ~550 adventure script
`.buf`s and 146 small GIMs (see §1.4).

Scripts: `local-data/harness/psp/scripts/` (`psppack.py`, `enumerate_paths.py`,
`classify.py`, `gim_report.py`, `export_art.py`, `gmo_report.py`, `gmo_tree.py`,
`vertex_census.py`, `tables_report.py`, `pck_report.py`, `identify_chars.py`).
Extracted files: `local-data/harness/psp/dump/`, decoded PNGs: `local-data/harness/psp/png/`.

---

## 1. Naming patterns (a)

### 1.1 The surprise: there are almost no format strings for character files

The paths this study expected to brute-force — `g3d/chr%02d%d.gmo`, `%s/chr%02d%c.acs` —
**do not exist in the EBOOT**. `grep -abo` finds no `chr%02d`, no `wpn%02d`, no `%s/chr`.
Every character, weapon and effect path is a **literal string** in `.rodata`, and the
per-(character, weapon) resource table (the plan's `0x1b18a0`, stride 0x50, 19 × 4 slots)
points at those literals. That table's string pool is laid out in *field order*, which is why
walking the pool reconstructs each combo's file list exactly (§3).

The only graphic/sound paths built at run time are these two, and both are visible with their
`%s` pool next to them:

| String | File offset | What it is |
|---|---|---|
| `/gra/gim/select/%s.gim` | 1888260 (0x1CCF44) | select **and** VS screen art; `%s` is taken from the name pool at 1888284..1888688 |
| `/gra/gim/result/%s.gim` | 1887436 | result screen; `%s` from `PLAYER` (1887376), `COM%d` (1887384), `button` (1887392), `hanko` (1887400), `key_word` (1887408), `back` (1887420), `back_2` (1887428) |

The `%s` pool for the select/VS screen, in file order (offset → literal):

```
1888284 cursor__roll        1888496 bustup_mion      1888628 bustup_sion
1888300 icon_off            1888508 bustup_miyoko    1888640 bustup_takano
1888312 icon_on             1888524 bustup_natsumi   1888656 bustup_tomitake
1888320 button_ok_off       1888540 bustup_okonogi   1888672 bustup_akane_2
1888336 button_return_off2  1888556 bustup_ooishi    1888688 bustup_hanyuu_2
1888356 button_ok_on        1888572 bustup_rena     1888704 costume
1888372 button_return_on2   1888584 bustup_rika     1888712 weapon
1888392 bustup_akane        1888596 bustup_satoko   1888720 new_weapon
1888408 bustup_akasaka      1888612 bustup_satoshi  1888732 char_name
1888424 bustup_chie         1888628 (see above)     1888744 bukibase
1888436 bustup_hanyuu                              1888756 yajirushi__anm_l
1888452 bustup_irie                                1888776 yajirushi__anm_r
1888464 bustup_kasai
1888480 bustup_keiichi
```

Note the romanisation: `sion` (not shion), `ooishi`, `hanyuu`/`hanyu`, `natsumi`/`natumi`.
The same file mixes them — `bustup_sion` vs `/gra/cutin/ci_shion_01.gim`, `bustup_natsumi`
vs `vs_enter_natumi` — so every spelling variant has to be tried.

The pool has only **19 `bustup_*` names + 2 variants** and 24 `vs_enter_*` names, and they
are not in character-number order. The VS set is 22 files:
`vs_enter_{akane,akasaka,chie,hanyu,hanyu_2,kasai,keiichi,kyosuke,mion,miyo,miyoko,natumi,
okonogi,ooishi,rena,rika,satoko,satoshi,shion,vs,chara_name00,chara_name01}`. `miyo` and
`natumi` are the extra spellings of miyoko/natsumi, and `kyosuke` has art but is not a
playable character.

### 1.2 Format strings that do exist

| String | File offset | What it builds |
|---|---|---|
| `/g3d/chr%02d%d.gmo`-equivalents | — | literal: `/g3d/chrNNk.gmo`, NN 01..19, k = costume digit 0..8 (1875280..1877072) |
| `/g3d/chrmNNx.gmo` | 1860464..1874424 | skeleton + motions per character/weapon; `NNx` (a-d) for 01,03..06,11,14,15 and bare `NN` for the rest |
| `/g3d/chrtNN.gim` | 1860484..1874440 | head-picture atlas, one per character |
| `/activity/chrNNx.acv` `.acs`, `/assault/chrNNx.atp` | interleaved in the same pool | moveset tables per weapon |
| `/activity/chrNNx_voice.pck`, `_se.pck`, `_eff.pck` | same pool | per-weapon voice / sound-effect / effect-model containers |
| `/activity/chrNN_eff.pck` | same pool | shared effect container; **absent from the pack** (see §7) |
| `/activity/chr5Nx_voice.pck`, `/activity/chr6Nx_voice.pck` | same pool | second voice bank for characters 07,08,09,10,13 (→57..60,63) and 17,19 (→67,69) |
| `/se/se%03d.vag` | 1889688 | shared sound effect |
| `/se/W%02d_%02d_%03d.vag` | 1970054+0x? = 1889704 | voice; the middle field is the **voice bank 00..23** |
| `/se/%s.vag` | 1954504 | generic |
| `/bgm/%s.at3`, `/bgm/%s%s.at3` | 1955024, 1849896 | BGM (`bm%02d`, 1889680) |
| `/movie/%s.pmf` | 1900908 | movies |
| `/gra/gim/adv/obj_%s` | 1954484 | adventure sprite; names are `<char>_<n>[r].gim`, `backNN.gim` |
| `/adv/%s` | 1877880, 1885924 | adventure scripts |
| `/adv/win_cord_%02d_%02d.buf`, `_%02d_%02d_%02d`, `_batu_%02d_%02d`, `_14_%02d` | 1877800..1877952 | window coordinates |
| `/adv/D%02d_%d.buf`, `/adv/load_D%02d_%d.buf`, `/adv/load_%s` | 1885948, 1885968, 1885932 | scene script + its loader (`D01..D84`, `_0`/`_1`) |
| `disc0:/PSP_GAME/USRDIR%%s` | 1877228 | pack prefix |
| `SCENE_%s` | 1880860 | scene names (`TITLE`, `VS_SELECT`, `VS_ENTER`, `RESULT`, …at 1880532..1880848) |
| `IMG%d`, `BODY%d`, `EYE%d_%d`, `MOUTH%d_%d`, `SPECIAL%d_%d`, `UP%d`, `UP%d_%d`, `SEL_N%d`, `SEL_S%d` | 1981272..1982460 | UI sprite names inside a 2D sprite set (select/HUD), not file names |
| `face.00.tga`..`face.07.tga`, `hair_a.tga`, `head.tga` | 1859376..1859484 | the texture slot names a `chrtNN` container maps into the model |

### 1.3 How the enumeration was done

`enumerate_paths.py` builds ~224k candidates from four sources and hashes them against the
index: (1) every literal path in the EBOOT, (2) every identifier in the EBOOT appended to
`/gra/gim/{select,result}/%s.gim`, (3) generated families (`chrNNk`, `chrm`, `chrt`, `wpn`,
`eff`, `map`, `acs/acv/atp`, `_voice/_se/_eff.pck`, `se/seNNN`, `se/WNN_NN_NNN`, `bgm/bmNN`),
(4) the EBOOT's own `%`-formats with every plausible index. Resolution went 3906 → 4786 →
7305 as families were widened; **the voice bank range 0..23 was the single biggest win**
(the first attempt assumed 0..9).

### 1.4 What is still unnamed (3467 hashes)

| Kind | Count | Notes |
|---|---|---|
| VAG audio | 2763 | `/se/*.vag` under names outside the tried ranges; not needed for the fighters |
| `.buf` adventure scripts | ~552 | the `D##_#`/`win_cord`/`load_` families did not cover them all |
| GIM | 146 | 480×272 full-screen art, 168×132 and 272×440 portraits, and small 162×25 / 122×25 / 146×11 text plates |
| GMO | 2 | 33,376 and 33,428 bytes, 15 bones, 1 motion, 9 meshes, `locator_root` — a map/prop model |
| misc | 4 | table-shaped, small |

Everything character-facing is named: all 19 × chrNNk models, all `chrm`/`chrt`, all 76
`.acs`/`.acv`/`.atp` triples, all weapon GMOs the table mentions, all `_voice`/`_se`/`_eff`
containers, and all select/VS/cut-in art.

---

## 2. PC cast ↔ PSP number mapping (b)

Three independent measurements, all agreeing.

### 2.1 `.atp` against the PC `.dat` combat records (quantitative)

`identify_chars.py`. The plan measured `word0 = combat[0]/1000`, `word1 = combat[5]/100`,
`word2 = combat[6]/100` and the id map `PC 300→row 107, 301→109, 302→110, 310→112, 311→114,
320→163, 330→124, 331→126, 332→167, 340→172, 341→174`. For each PC character's three
weapon DATs (`Higurashi-Daybreak/data/<char>/NN.dat`, parsed with the layout in
`src/battle/combat_record.h`) and each PSP `chrNNx.atp`, that map gives up to 33 compare
points; the score is the number of matching `(combat0, combat5, combat6)` triples.

Result (`notes/identify_chars.txt`, section B2; best number, then next best):

| PC character | PSP no. | score | runner-up |
|---|---|---|---|
| rena | **01** | 23 | 7 (no. 15) |
| keiichi | **02** | 31 | 22 (no. 17) |
| mion | **03** | 18 | 11 (no. 6) |
| rika | **04** | 21 | 12 (no. 11) |
| satoko | **05** | 27 | 18 (no. 18) |
| shion | **06** | 33 | 15 (no. 12) |
| irie | **07** | 24 | 11 (no. 12) |
| ohishi | **09** | 6 | 3 (no. 7) |
| tomitake | **10** | 27 | 20 (no. 19) |
| takano | **11** | 20 | 13 (no. 3) |
| chie | **12** | 32 | 18 (no. 2) |
| kasai | **13** | 21 | 9 (no. 10) |
| akane | **14** | 30 | 6 (no. 19) |
| natumi | **15** | 18 | 7 (no. 1) |
| hanyu | **16** | 14 | 10 (no. 4) |
| akasaka | **08** | *by elimination* | — |

Akasaka's weapons `a`–`c` were rebalanced (as the plan says), so his `.atp` matches nothing
well (best 9, at no. 07, which irie owns with 24). With 01–07 and 09–16 measured and
17/18/19 fixed by the plan, **08 is the only number left, so akasaka = 08**.

A second, id-map-free measurement (section C, triple-set overlap over all records) picks the
same character number first for 14 of 16 characters.

### 2.2 Shared weapon art (byte-identical files)

The pack contains weapon models that are **byte-identical across characters**:

| Duplicate pair | sha256 | Reads as |
|---|---|---|
| `g3d/wpn17d.gmo` == `g3d/wpn02a.gmo` | `cbdd7de5f6ef…` | Satoshi's weapon d is character 02's weapon-a model = **Keiichi's bat** (the plan's "a second bat, Keiichi's texture") → 02 = Keiichi ✅ |
| `g3d/wpn19dr1.gmo` == `g3d/wpn06cr1.gmo` | `e33858ffd127…` | Okonogi's weapon d right-hand model is character 06's weapon-c model = **Shion's whip** → 06 = Shion ✅ |
| `g3d/wpn19dr2.gmo` == `g3d/wpn06cr2.gmo` | `c4f578a1e1a2…` | same, second part |
| `activity/chr69a_voice.pck` == `chr19a_voice.pck` | `5ccb47312da8…` | Okonogi's "second bank" is a duplicate |
| `activity/chr16a.acv` == `chr16c.acv`; `chr16*_voice.pck` all equal | — | Natsumi's shared data |
| `activity/chr18a.acv` == `chr18c.acv` == `chr18d.acv`; `chr18a/b/c.atp` all equal | — | **Miyoko's four weapons share one `.acv` and one `.atp`** |
| `activity/chr19c.acv` == `chr19d.acv` | — | |

### 2.3 Art

The `chrtNN.gim` head atlases decode to 64×64 eye/brow plates (`png/sheets/heads.png`).
The eye colours agree with the measurement for the cases they can settle — 01 blue (Rena),
02 dark violet (Keiichi), 03 teal (Mion, green-haired like Shion) — and `chrt09` is the aged,
grey-browed, tan face (Ohishi). `chrt17`/`chrt18` are blonde, `chrt19` is a hard-eyed tan
face (Okonogi), as expected. Only the last two are load-bearing, since 17/18/19 were given;
the rest is corroboration, not measurement.

### 2.4 The mapping, stated

```
PSP 01 rena      05 satoko    09 ohishi    13 kasai     17 satoshi
PSP 02 keiichi  06 shion     10 tomitake  14 akane     18 miyoko
PSP 03 mion     07 irie      11 takano    15 natumi    19 okonogi
PSP 04 rika     08 akasaka   12 chie      16 hanyu
```

**This is not the PC roster order.** On PC (`src/battle/weapon_definition.h`,
`kCharacterDirs`) the order is rena, mion, keiichi, satoko, rika, shion, tomitake, takano,
ohishi, akasaka, irie, chie, kasai, akane, hanyu, natumi. The PSP swaps keiichi↔mion,
rika↔satoko and moves irie up to 07, so **a port cannot use the PC index as the PSP number**.
In code the PSP index is 0-based: number 17 → index 16, which is what the plan's `Fighter`
code uses.

---

## 3. The three new fighters: complete file inventory (c)

Every path below is in `pack_paths.txt` with its sha256. Sizes are uncompressed bytes.

### 3.1 Satoshi Houjou — PSP 17 (5 costumes)

| File | Bytes | Note |
|---|---|---|
| `g3d/chrm17.gmo` | 1,142,984 | skeleton + **76 motion takes**, 68 bones |
| `g3d/chrt17.gim` | 22,996 | 10 unique head pictures ×2 copies, INDEX4 64×64 |
| `g3d/chr170..174.gmo` | 88,116 / 89,288 / 96,012 / 91,020 / 90,108 | **5 costumes**, 68 bones each |
| `g3d/wpn17a.gmo` | 5,420 | weapon a model |
| `g3d/wpn17b.gmo` | 11,900 | weapon b model |
| `g3d/wpn17c.gmo` | 6,900 | weapon c model |
| `g3d/wpn17d.gmo` | 6,144 | **not in the resource table**; byte-identical to `wpn02a` (§2.2) |
| `activity/chr17{a,b,c,d}.acs` | 3,784 / 3,640 / 3,768 / 3,656 | moveset event lists |
| `activity/chr17{a,b,c,d}.acv` | 41,416 / 37,800 / 41,908 / 40,352 | hit/shape tables |
| `assault/chr17{a,b,c,d}.atp` | 51,816 ×4 | attack parameter tables |
| `activity/chr17{a,b,c,d}_voice.pck` | 1,061,504 / 1,046,976 / 1,061,504 / 1,049,408 | a==c |
| `activity/chr67{a,b,c,d}_voice.pck` | 1,081,152 / 1,066,624 / 1,081,152 / 1,069,056 | **second voice bank, unique files** |
| `activity/chr17{a,b,c,d}_se.pck` | 66,560 / 45,440 / 52,032 / 71,232 | |
| `activity/chr17{a,b,c,d}_eff.pck` | 97,216 / 259,968 / 82,432 / 82,432 | c==d |
| `activity/chr17_eff.pck` | — | **does not exist** (the table names it, the pack has no such hash) |

Weapons (from the EBOOT records): a = `wpn17a`, b = `wpn17b`, c = `wpn17c`, d = no string in
the table.

### 3.2 Miyoko Tanashi — PSP 18 (7 costumes)

| File | Bytes |
|---|---|
| `g3d/chrm18.gmo` | 919,836 (76 takes, 77 bones) |
| `g3d/chrt18.gim` | 22,996 |
| `g3d/chr180..186.gmo` | 91,720 / 93,536 / 87,072 / 84,980 / 91,620 / 87,984 / 97,848 (**7 costumes**) |
| `activity/chr18{a,b,c,d}.acs` | 3,416 / 3,528 / 3,512 / 3,512 |
| `activity/chr18{a,b,c,d}.acv` | 37,604 / 37,676 / 37,604 / 37,604 (**a == c == d**) |
| `assault/chr18{a,b,c,d}.atp` | 51,816 ×4 (**a == b == c**) |
| `activity/chr18{a,b,c,d}_voice.pck` | 785,088 / 790,272 / 785,216 / 786,752 |
| `activity/chr18{a,b,c,d}_se.pck` | 71,744 / 97,920 / 61,120 / 54,912 |
| `activity/chr18{a,b,c,d}_eff.pck` | 186,560 / 570,816 / 184,320 / 312,256 |
| weapons | **none** — no `wpn18*` string in the table and no `wpn18*` hash in the pack |

Miyoko is the one fighter with no weapon model at all; her four weapons must be invisible
props or her `.acv`/`.atp` carries everything. The plan already flagged this (her code is at
`0x68aa4`).

### 3.3 Okonogi — PSP 19 (3 costumes)

| File | Bytes | Note |
|---|---|---|
| `g3d/chrm19.gmo` | 706,440 | 76 takes, 77 bones |
| `g3d/chrt19.gim` | 22,996 | |
| `g3d/chr190..192.gmo` | 92,012 / 89,432 / 91,032 | **3 costumes** |
| `g3d/wpn19ar1.gmo` / `wpn19ar2.gmo` | 9,656 / 7,508 | weapon a, two parts |
| `g3d/wpn19b.gmo` | 10,000 | weapon b |
| `g3d/wpn19cr1.gmo` / `wpn19cr2.gmo` | 10,472 / 7,972 | weapon c, two parts |
| `g3d/wpn19dr1.gmo` / `wpn19dr2.gmo` | 9,936 / 7,532 | **not in the table**; == `wpn06cr1`/`cr2` |
| `activity/chr19{a,b,c,d}.acs` | 3,464 / 3,448 / 3,480 / 3,384 | |
| `activity/chr19{a,b,c,d}.acv` | 38,060 / 39,088 / 38,060 / 38,060 | **c == d** |
| `assault/chr19{a,b,c,d}.atp` | 51,816 ×4, all different | |
| `activity/chr19{a,b,c,d}_voice.pck` | 776,832 / 796,480 / 776,832 / 771,584 | a == c |
| `activity/chr69{a,b,c,d}_voice.pck` | 776,832 / 796,480 / 776,832 / 771,584 | **identical to the 19 set, file for file** |
| `activity/chr19{a,b,c,d}_se.pck` | 61,440 / 51,264 / 51,968 / 49,280 | |
| `activity/chr19{a,b,c,d}_eff.pck` | 265,984 / 48,384 / 281,344 / 281,344 | c == d |

### 3.4 Select / VS / portrait / cut-in / name-plate art (all GIM)

`gra/gim/select/<name>.gim`, decoded by `gim_report.py` + `export_art.py` to
`local-data/harness/psp/png/`. Contact sheets: `png/sheets/{bustups,vs_enter,heads,
cutin_new3,new3_vs_bustup,names_chara_name00,names_chara_name01}.png`.

| Kind | Files for the three | Format |
|---|---|---|
| select-screen bust-up, 2 pictures (open/closed eyes) | `bustup_satoshi.gim` 30,436 B, `bustup_miyoko.gim` 30,436 B, `bustup_okonogi.gim` 30,436 B | GIM, **2 pictures**, 220×130, pixel fmt 5 = INDEX8, bpp 8, order 0 (linear), pitch align 16, palette fmt 3 = RGBA8888, 256 entries |
| VS-intro face, 2 pictures | `vs_enter_satoshi.gim` 24,552 B, `vs_enter_miyoko.gim` 24,552 B, `vs_enter_okonogi.gim` 24,548 B | GIM, 2 pictures, 168×132, INDEX8, palette RGBA8888 256 |
| VS name plates | **shared atlas**: `vs_enter_chara_name00.gim` (25,964 B) and `vs_enter_chara_name01.gim` (31,164 B) | GIM 144×320 / 144×385, INDEX4 4bpp, palette RGBA8888 16 entries. `chara_name01` holds 12 plates including 北条悟史 (Satoshi), 田無美代子 (Miyoko), 小此木 (Okonogi); `chara_name00` holds the other 10 |
| VS screen furniture | `vs_enter_vs.gim` 103,120 B (赤組勝利/青組勝利/開始/撃破 + VS logo), `vs_bg0/1`, `vs_bg_{blue,center,impact,red,thunder}`, `vs_cursor2_{b,r}`, `vs_head_icon.gim`, `vs_info_mes01.gim`, `vs_label_{akagumi,aogumi,com_b,com_r,player_b,player_r}` | GIM, INDEX4/INDEX8 + RGBA8888 palettes |
| cut-ins (6 + 2 sub per character) | `gra/cutin/ci_{satoshi,miyoko,okonogi}_{01..06,sub01,sub02}.gim` = 8 files each, 24 total | GIM 480×96, INDEX8, palette RGBA8888 256 |
| in-model head pictures | `g3d/chrt{17,18,19}.gim` | GIM, **20 pictures = 10 unique × 2**, 64×64, INDEX4 4bpp, swizzled (order 1), palette RGBA8888 16 |
| shared name atlas for the figure/select UI | `gra/gim/select/char_name.gim` 31,072 B | GIM 256×240, INDEX4, palette 16 |
| HUD | `gra/gim/ongame/{meter,moji,syouri,scope,caution,pause_*}.gim` — shared, no per-character HUD face |
| model textures | body = **TGA inside the GMO** (`chr17__body`, `chr18__body`, `chr19__body`, 16 KB colour-mapped TGA); head/face/hair = pictures inside `chrt{17,18,19}.gim` |

So the art the port needs for these three exists and is complete: a select bust-up, a VS-intro
face, seven cut-ins, VS name plates, and the in-model head atlases. There is **no PNG and no
separate portrait TGA**: every menu-side image is GIM; the only TGAs are the colour-mapped
body textures embedded in the costume GMOs. (The pack's only three PNGs are the save-data
icons `data/ICON0.PNG`, `data/INST_ICON0.PNG`, `data/PIC1.PNG`.)

Notable: `chrtNN.gim` really holds **10 distinct pictures** (the plan's "8 expressions, hair,
scalp" matches indices 0..7, 8, 9), but the container stores them **twice**, so an importer
that assumes 10 pictures silently reads palettes/records it never uses.

---

## 4. `.acs`, `.acv`, `.atp` (d)

All three share an outer 16-byte header; the fourth word tells the reader which shape follows.

```
u32 bytes_total      (= file size)
u32 version          (.acs 1 or 2, .acv 1/2/4, .atp 1 or 2)
u32 bytes - 8        (not in the v2/v4 variants, see 4.3)
u32 n                (.acs/.atp: record/row count, normally 350; .acv: section count, 4)
```

### 4.1 `.acs` — the event list, 350 rows

Verified: the rows tile the file exactly (`n = 350`, ends at EOF) in every one of the 76 files.

```
0x00  header (16 bytes)
0x10  350 × row, back to back; row = { u32 row_bytes, u32 items, item[items] }
      row_bytes = 8 + 8*items   (empty row = {8, 0})
      item = { f32 time (frames at 30 fps), u32 code }
```
Example (`activity/chr19a.acs` row 108): 7 items, `0x82000001@0`, `0x8400002b@0`,
`0x81000001@0`, `0x800002ff@0`, `0x83080000@4`, `0x02000000@8`, `0x01000000@8`.

71 distinct codes over all 76 files, in 7 families:
`0x8000_0x__` (152 + 82 + 60 + 109 + 298 + 4 + 164 + 4 + 7 + 4 + 6 uses),
`0x8100_00__` (205/102), `0x8200_00__` (213/106), `0x8308_00__` (0x00/03/06/09/0c/0f/12/13/51
with 59..406 uses each), `0x8400_00__` (many, `0x84000000` 1207 uses plus 0x15..0xe4),
`0x01000000` (307) and `0x02000000` (319). The plan's "only `0x80000401` and `0x840000e4` are
exclusive to the new characters" still holds (4 and 7 uses).

**Populated rows.** Per weapon, the number of rows with items runs 11..65. Only **11 rows are
populated in every one of the 76 combos**:

```
16, 17, 108, 109, 110, 172, 173, 174, 175, 176, 177
```
Those are the shared/common movement rows (idle, walk, guard, get-up, …): rows 16/17 carry a
single `0x800004ff` at t=0; 108/109/110 and 172..177 carry the `0x8000_01xx`/`0x8000_02xx`
entry codes, a `0x84…` action, a `0x8308…` wait and `0x81/0x82` pairs.

Rows beyond that set for the new fighters (i.e. their own moves):

| file | populated | rows | rows beyond the common 11 |
|---|---|---|---|
| chr17a | 44 | 33 | 99,116-119,128-131,164,168,179,181,193,195,197,201,205,207,225,227,229,231,233,235,237,286,327,328,329,336,337,339 |
| chr17b | 32 | 21 | same minus 179,229-235,286,336-339 |
| chr17c | 43 | 32 | as a, minus 179 |
| chr17d | 33 | 22 | as b, plus 179 |
| chr18a | 38 | 27 | 98-100,116-119,124,129-131,164,168,179,181,193,195,197,199,201,205,207,219,225,227,237,283 |
| chr18b | 45 | 34 | as a plus 185,187,189,191,209,211,213,215 |
| chr18c | 44 | 33 | as b minus 179 |
| chr18d | 45 | 34 | as b plus 112 |
| chr19a | 35 | 24 | 116-119,128-131,164,167,181,185,187,189,191,193,195,197,199,201,207,225,227,236 |
| chr19b | 40 | 29 | as a plus 226,228,230,232,234,285 |
| chr19c | 36 | 25 | as a plus 179,237 |
| chr19d | 36 | 25 | as c |

Union over all combos: 136 rows (98..239, 251, 282..286, 322..339).

Header variants: `chr16b.acs` is **version 2** and 7,104 bytes (vs 3,496) — the v2 file
carries a second copy of the row block; it is the only `.acs` with version ≠ 1.

### 4.2 `.atp` — the attack parameters, 350 × 148

```
0x00  header (16 bytes; version 2 moves the payload to 0x18)
0x10  n × record, n from header word 3 (normally 350), record = (file - payload)/n
```
For the standard file: `n = 350`, record = **148 bytes = 37 words**, all zero except the
populated rows. A record's low words are the ones the plan matched to the PC:

| word | meaning (from the plan, re-verified on 76 files) |
|---|---|
| 0 (f32) | `combat[0] / 1000` — e.g. 1.5 for combat[0]=1500 |
| 1 (f32) | `combat[5] / 100` |
| 2 (f32) | `combat[6] / 100` |
| 5, byte 3 | `combat[8]` |
| 6 | small integer (8 in the sample rows) |
| 7, 8 (f32) | 10.0 / 13.0 in the sample rows |
| 9 | bitfield `0x00200000` in the sample rows |
| 34, 35, 36 | 1, 0xed, 1.0 in the sample rows |

Populated rows per weapon: 33 for most, up to 72. **No row is populated in every combo**, so
the attack rows are per-weapon. The common core is
`94,95,96,99,102,107..110,112..119,124..131,163,164,167,168,170,172,174,176`; the new three
add, per weapon: chr17a/c `226,229,231..237,259..262,285,286,328,329,339`; chr19d
`226..237,285,286`; chr19b `207,227`.

Variants: `chr16b.atp` is **version 2**, payload at 0x18, 296-byte records (2 × 148);
`chr16d.atp` has header count **120** and 272-byte records, and its populated rows start at
72, 75, 80, 81 — a different row numbering from every other file. `chr16d` is Natsumi's
fourth weapon.

### 4.3 `.acv` — collision/shape data, 4 sections × 350 rows

Version 1 (74 of 76 files, incl. all four weapons of the new three):

```
0x00  header {u32 size, u32 1, u32 size-8, u32 4}
0x10  section[0] … section[3]; section = { u32 section_bytes, u32 rows }
      rows run from section+8 and the section ends at section + section_bytes
      row = { u32 row_bytes, u32 count, payload[count] }   payload = (row_bytes-8)/count bytes
```
Reading exactly 350 rows from each section lands exactly on the section end and the four
sections land exactly on EOF — verified on all 74.

| section | rows | row shape | content |
|---|---|---|---|
| 0 | 350, **all 350 used** | 1 item × 8 bytes per row (a few rows 2/3/4 items: 437 items over 350 rows in chr19a) | per-move pair of 32-bit values; 27 distinct first words, 30 distinct second words per file (values like `0x528bb2c9`, `0x523a43b7`, and float-looking `0x40400000`=3.0, `0x41200000`=10.0). Semantics **not decoded** |
| 1 | 350, **57..115 used** | item = **164 bytes** | The hit/collision records. Per weapon: chr17a 92, 17b 62, 17c 91, 17d 86; chr18 all 57; chr19a/c/d 66, 19b 69. A 164-byte item reads as a float (`25`, `8`, `23`, …) followed by two ~80-byte (20-float) blocks that contain `-5000`, `1e12`, `3.14159`, `-50`, `2`, `-10`, `25`, `4`. Inner field layout **not decoded** |
| 2 | **2 rows** | row 0 = 350 × 16-byte entries; row 1 = 350 × 4-byte (u16,u16) pairs | two 350-entry tables |
| 3 | 350, all used | 4 bytes per row, no per-row header | a 350-entry `(u16, u16)` pair table, mostly `(2i, 2i+1)` with `0xffff` = none |

Section-1 size tracks the weapon's attack count (66 used rows ↔ 33 populated `.atp` rows →
two 164-byte records per attack), so `.acv` §1 is the hit geometry the `.atp` row describes.

Versions 2 and 4 are the two files the plan flagged: `chr16b.acv` (v2, 74,200 B) and
`chr16d.acv` (v4, 21,664 B). **Neither follows the v1 rule and neither is decoded here.**
Observed: v2 = `{74200, 2, 38408, 4}` and a second complete sub-record starts at 0x9610 with
`{35784, 4, 6168, 350}` whose size lands exactly on EOF, i.e. the file is two concatenated
records; v4 = `{21664, 4, 3992, 242}` with sections beginning immediately at 0x10 (row shape
`{16, 1, …}`) and sub-headers at 0xF98 (`{11824, 242}`). Both belong to character 16, not to
the new three.

### 4.4 Keiichi (PSP 02) vs the new three, side by side

| | chr02a (Keiichi, known PC char) | chr17a | chr18a | chr19a |
|---|---|---|---|---|
| `.acs` size / version / rows | 3,624 / 1 / 350 | 3,784 / 1 / 350 | 3,416 / 1 / 350 | 3,464 / 1 / 350 |
| `.acs` populated rows | 33 | 44 | 38 | 35 |
| `.atp` records | 350 × 148 | 350 × 148 | 350 × 148 | 350 × 148 |
| `.atp` populated | 33 | 53 | 35 | 33 |
| `.acv` version / size | 1 / 36,092 | 1 / 41,416 | 1 / 37,604 | 1 / 38,060 |
| `.acv` §1 used rows | 57 | 92 | 57 | 66 |

The structure is identical; only the row populations differ. Nothing here distinguishes a PC
character's file from a new fighter's — which is the plan's central point: on the PSP the
moves are data, not code.

---

## 5. GMO structure (e)

`tools/asset-tools/gmo_blender.py` is imported outside Blender by `scripts/gmo.py` (bpy and
mathutils stubbed), so everything below is that parser's result, not a second implementation.
`scripts/gmo_tree.py` is the standalone chunk walker for spot checks.

### 5.1 Chunk tree

```
0x00  12-byte magic "OMG.00.1PSP\0" (+4 pad)
0x10  0x0002 container
        0x0003 container  name "model-0"
          0x8014, 0x8016            fixed leaves (bounding data)
          0x0004 bone ×N            name at +16, then 0x8041 parent, 0x8048 translate,
                                    0x804b quaternion xyzw, 0x8044 blend bones,
                                    0x8045 their offset matrices
          0x0005 bone with mesh     __
            0x0006 mesh ×M              name "mesh-<mat>-<index>",
                                        0x8061 material, 0x8062 palette, 0x8066 draw ×K
            0x0007 array ×A             name "arrays-0-<n>",
                                        payload at chunk+header: u32 vertex type, u32 count
          0x0008 material ×M        name "mtl_<tex>"; child 0x0009 layer with 0x8091 texture ref
          0x000a texture ×T         name; 0x8012 (meta) and 0x8013 = a whole TGA file
          0x000b motion ×K          motion (skeleton files only)
            0x80b1 frame range, 0x80b2 fps(=30), 0x80b3 (bone, target, curve),
            0x000c curve: u32 format, dims, keys; low nibble of format 0=constant 1=linear 4=slerp
```
Chunk header is `{u16 type, u16 header_size, u32 size}`; `header_size` is the payload offset,
so it varies with the name length (0x18 for `model-0`, 0x1c/0x20 for mesh/array chunks). Any
walker must use it rather than assume 0x10.

### 5.2 Does the repository parser handle the new three? Yes, with two gaps

`parse_gmo()` on all 229 character/weapon/effect GMOs of the pack: **153 parse, 76 raise.**

* `g3d/chr17{0..4}.gmo`, `chr18{0..6}.gmo`, `chr19{0..2}.gmo` — all 15 parse (4-7 arrays,
  4 materials, 4 textures each; 68 bones for 17x, 77 for 18x/19x).
* `g3d/chrm17.gmo`, `chrm18.gmo`, `chrm19.gmo` — parse: **76 motions each**.
* `g3d/chrt{17,18,19}.gim` — not GMO; decoded by `decode_gim`, 20 pictures each.
* Fails: `chr030.gmo`, `chr040.gmo`, `chr056.gmo` (the plan's known gap: **u16 or f32 vertex
  weights**), and **all 73 weapon GMOs** — they use an *unweighted* vertex type
  (`0x180011a3`, weight kind 0) that `vertex_layout()` rejects with
  `unhandled vertex type`. So the importer cannot yet show a weapon in a fighter's hand.

### 5.3 Vertex formats actually used (census of 520 GMO files)

`0x1c0013a3`-style types: bits 0-1 UV kind, 2-4 colour, 5-6 normal, 7-8 position, 9-10 weight
component size, 14-16 weight count − 1; the high byte (0x18/0x1c/0x20/0x24/0x28/0x30/0x34/
0x38) is a GMO-side flag that the parser ignores and does not need.

| type | arrays | vertices | layout |
|---|---|---|---|
| `0x180011a3` | 2277 | 306,575 | no weights, f32 UV, u8 normal, f32 pos, stride 24 |
| `0x1c0013a3` | 108 | 25,559 | 1 × u8 weight, stride 28 |
| `0x1c0053a3` | 21 | 3,782 | 2 × u8 weights |
| `0x1c0093a3` | 67 | 9,708 | 3 × u8 weights |
| `0x1c00d3a3` | 44 | 4,676 | 4 × u8 weights |
| `0x200113a3` | 51 | 6,634 | 5 × u8 weights, stride 32 |
| `0x200153a3` | 45 | 5,638 | 6 × u8 weights |
| `0x200193a3` | 77 | 21,476 | 7 × u8 weights |
| `0x2001d3a3` | 110 | 149,543 | 8 × u8 weights (the character meshes) |
| `0x1c0015a3`, `0x200095a3`, `0x280195a3`, `0x2801d5a3` | 2/1/2/2 | 321/108/600/3,012 | **u16 weights**, stride 28..40 → unsupported |
| `0x1c0017a3`, `0x240097a3`, `0x300157a3`, `0x340197a3`, `0x3801d7a3` | 1 each | 150..1,225 | **f32 weights** → unsupported |
| `0x100011a0`, `0x140011b8`, `0x1c0011bb`, `0x200013bb`, `0x240153bb`, `0x2401d3bb`, `0x200011e3` | 72..95 | — | unweighted, some with colour (bgra4444) — weapons/effects |

### 5.4 Bones, motions, textures per fighter

| | bones | motion takes | arrays | materials | textures |
|---|---|---|---|---|---|
| `chrm17.gmo` | 68 | 76 | – | – | – |
| `chr170.gmo` | 68 | – | 5 | 4 (`mtl_chr17__body`, `__head`, `__face`, `__hair`) | `chr17__body` (16,452 B TGA), `chr17__head`, `__face`, `__hair` (external, in `chrt17.gim`) |
| `chrm18.gmo` | 77 | 76 | – | – | – |
| `chr180.gmo` | 77 | – | 4 | 4 | `chr18__body` TGA + 3 external |
| `chrm19.gmo` | 77 | 76 | – | – | – |
| `chr190.gmo` | 77 | – | 4 | 4 | `chr190__body` (16,464 B TGA) + 3 external |

Bone names are the PSP set (`root, spine1, spine2, leftcollar, leftshoulder, leftelbow,
lefthand, leftfinger*, weapon_l, wapon_controll_l, neck, head, uphair*, downhair*, tie*, clothes*,
right*, righthip, leftknee, leftfoot, lefttoe*, *skirt*, tail1..4`) — 68 for Satoshi,
77 for Miyoko/Okonogi including the four-`tail` chain. Motion fps is 30.0 everywhere.

Weapon GMOs are skeletons too: e.g. `wpn01a.gmo` has 6 bones (`RootNode, wpn_nata, nata_a_mesh,
locator_tracks_in, locator_tracks_out, locator_hit00`) plus one 104-vertex unweighted mesh and
one embedded TGA (`wpn01a__nata_tga`, 2,848 B). The `locator_*` bones are what the `.acv`
attack records presumably hang off.

---

## 6. The `.pck` containers (f)

`activity/chrNNx_voice.pck`, `_se.pck`, `_eff.pck`, plus `chrNN_eff.pck` (absent). 264 `.pck`
files are resolved in total.

```
0x00  u32 count
0x04  count × { u32 id, u32 payload_bytes, u32 file_offset }
      (a NUL-padded name table sits between the index and the first payload)
      then the payloads, back to back, each at its own file_offset
```
`payload_bytes` is slightly smaller than the block (e.g. 1,664-byte block ↔ 1,648 recorded,
76,736 ↔ 76,684), i.e. it excludes the payload's own header — do not use it as a block length.

| file | entries | payloads | contents |
|---|---|---|---|
| `chr19a_voice.pck` | 86 | 53 unique offsets | **VAG** (`VAGp`) audio; the name table lists the source paths, e.g. `se/W05_23_001.vag`, `se/W05_23_005.vag` … |
| `chr19a_se.pck` | 228 | 14 | VAG; names `se/se022.vag`, `se/se043.vag`, … |
| `chr19a_eff.pck` | 252 | 8 | **GMO** effect models; names `g3d/eff048.gmo`, `g3d/eff083.gmo`, … |
| `chr00a_eff.pck` | 287 | 33 | GMO (`g3d/eff0011a.gmo` …) |
| `chr00a_se.pck` | 237 | 28 | VAG |

Ids are shared sound/voice ids (`2740..3123` consecutive in `chr19a_se`), so the same id in
another character's pack maps to a different VAG. The voice name's **middle field is the voice
bank 00..23** — 24 banks for 19 characters — which is why the `se/W%02d_%02d_%03d.vag`
brute force only started finding files once the range covered 0..23.

The VAG format inside is the plain PSP ADPCM container; the entries are not renamed, so a port
can play them through any PSP VAG decoder.

---

## 7. Surprises, and corrections to `docs/PSP-CHARACTERS-PLAN.md`

1. **No `%`-format strings for character/weapon paths.** The plan's `g3d/chr%02d%d.gmo` shape
   is right in *meaning*, but the EBOOT spells all 19 characters out literally. The plan's
   `g3d/chrNNk.gmo` description is confirmed; the `k` is costume 0-8.
2. **The PSP numbering is not the PC numbering** (§2.4). The plan's "07 irie" order is not a
   guess: measured. Anyone porting must map explicitly.
3. **`chr17d`/`chr19d` have no weapon model in the resource table**, yet the pack holds
   `wpn17d.gmo`, `wpn19dr1/dr2.gmo`, byte-identical to `wpn02a.gmo` and `wpn06cr1/cr2.gmo`.
   The table's own record for chr17d/chr19d ends without a `/g3d/wpn…` string, so at runtime
   the model must come from the other character's slot. The plan's "Satoshi's d is Keiichi's
   bat, Okonogi's d is Shion's whip" is exactly right, and the byte identity is the proof.
4. **No shared `chrNN_eff.pck` exists — for any character.** All 19 hashes the resource
   table names (`chr01_eff.pck` … `chr19_eff.pck`) are absent from the pack. Only the per-weapon `chrNNx_eff.pck` files exist, and those carry the effect
   models. The plan's "the table also names `chrNN_eff.pck`, which the pack does not have" is
   true much more widely than for the new three.
5. **Miyoko has no weapon model at all** (`wpn18*` is absent from the pack, confirming the
   plan), and all four of her weapons share one `.acv`/`.atp`.
6. **`chrtNN.gim` holds 10 unique head pictures stored twice (20 GIM pictures)** — an
   importer that assumes 10 will under-read the container.
7. **The repository's GMO importer cannot load any weapon model** (unweighted vertex type) and
   not `chr030/chr040/chr056` (u16/f32 weights). It does load every costume of the three new
   fighters and all three `chrm` skeletons. The plan's note about `chr030`/`chr040` is correct;
   the weapon gap is new.
8. **`.atp` is not always 350 × 148**: version 2 (`chr16b`) puts the payload at 0x18 with
   296-byte records, and `chr16d` has 120 records of 272 bytes with a different row numbering.
9. **`.acv` versions 2 and 4 (chr16b, chr16d) are composites** of two complete sub-records; the
   v1 reader must not be pointed at them.
10. **The voice-bank index is not the character number**: `chr19`'s voice names carry bank 23,
    and 24 banks exist for 19 characters.
11. **`vs_enter_kyosuke.gim` exists** with no corresponding playable character, and
    `vs_enter_miyo.gim`/`vs_enter_natumi.gim` duplicate the `miyoko`/`natsumi` spelling
    variants. Also `gra/gim/select/config_bgm.gim`, `config_map.gim`, `config_map_sozai.gim`,
    `button_battle_start_on/off.gim` resolve from the same pool.

### Reproduction

```bash
cd local-data/harness/psp/scripts
python3 psppack.py            # sanity: three known files inflate
python3 enumerate_paths.py    # 7305 / 10772 resolved -> notes/resolved.tsv
python3 classify.py           # every payload -> notes/all_files.tsv
python3 gim_report.py         # GIM headers     -> notes/gim_report.txt
python3 export_art.py         # PNGs + sheets   -> png/
python3 gmo_report.py         # GMO inventory   -> notes/gmo_report.txt
python3 vertex_census.py      # vertex formats  -> notes/vertex_census.txt
python3 tables_report.py      # acs/acv/atp     -> notes/tables_report.txt
python3 pck_report.py         # pck containers  -> notes/pck_report.txt
python3 identify_chars.py     # PC <-> PSP map  -> notes/identify_chars.txt (needs the PC install)
```
