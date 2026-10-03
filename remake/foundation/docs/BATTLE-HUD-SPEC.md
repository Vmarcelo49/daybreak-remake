# Original battle-HUD specification (Phase 3, fidelity target `battle-hud.webp`)

Evidence base: `DaybreakDX.exe` (base 0x400000; .text 0x401000-0x6a0fff, .rdata 0x6a1000-0x6b6fff,
.data 0x6b7000-0x6d9d07 — `research/binary_data/metadata.txt`) and the bundles in
`Higurashi-Daybreak/daybreak0*.dat`. Every claim below is either a `FUN_` address with a
`research/decompiled/` file:line, an executable offset, or a pixel measurement of the print.

The HUD atlases are **game assets and are not committed**: this document names them, gives
their sub-rects, and says how to reproduce every dump with the tools already in the repo
(`remake/tools/asset-tools/extract_dat.py` lists/extracts bundle entries and
`cnv_convert.py` decodes a `.cnv`), so a reader can re-measure anything here without
trusting a screenshot.

**Coordinate convention.** All HUD coordinates are *screen pixels in the 800x600 frame*,
scaled by `param_4` and offset by the viewport origin `(param_2, param_3)`:
`x_screen = coord * scale + vpLeft`, `y_screen = coord * scale + vpTop`.
Single-player ⇒ `scale = 1.0`, `vpLeft = vpTop = 0` (`FUN_0063a130` @0x0063a130,
research/decompiled/FUN_0063a130.c:33-38 sets `local_8 = 1.0` when `DAT_006cfba0 == 1`,
else 0.5; the viewport rect comes from `SetRect(local_4c,0,0,800,600)` at
research/decompiled/FUN_006396f0.c:38).

**Print vs frame.** `battle-hud.webp` is 798x606 — a capture of the 800x600 frame with a
**(-2, +6) px offset**: `game = (print_x + 2, print_y - 6)`. Verified exactly on two
independent 230-px-wide fills (HP fill predicted (505,565)-(735,579), measured print
(503,571)-(733,585); MAIN fill predicted (623,471)-(783,477), measured print (621,477)-(781,483)).

---

## 1. The draw path

| Function | Address | Role | Evidence |
|---|---|---|---|
| `FUN_006396f0` | 0x006396f0 | battle frame render; builds viewport rects (800x600 for 1P) and calls the per-slot HUD | FUN_006396f0.c:38, :102-105, :185 |
| `FUN_0063a130` | 0x0063a130 | per-slot HUD orchestrator; picks `scale` (1.0 / 0.5), calls the two HUD drawers | FUN_0063a130.c:33-38, :56-61 |
| `FUN_00643230` | 0x00643230 | **per-fighter** HUD: alert balloon, `com` bar, overhead HP, targeting brackets; projects the fighter's world point | FUN_00643230.c:56-58 (`x = (clip.x/clip.w)*400 + 400`, `y = (-clip.y/clip.w)*300 + 300`), :74-78 |
| `FUN_00644150` | 0x00644150 | **corner HUD**: both balloon%/LIMIT readouts, the two balloon sprites, the OYASHIRO fan gauge + fill + MAX, the boxed tactics label, STAMINA, MAIN, CHARGE, HP, the top-centre counter | FUN_00644150.c (218 lines, whole function) |
| `FUN_00642510` | 0x00642510 | creates every HUD sub-rect sprite from the atlases (the "sprite table") | FUN_00642510.c:25-68 |
| `FUN_00642a00` | 0x00642a00 | per-player HUD sprite slots (`hud+0x2b4 + i*0xac`) | FUN_00642a00.c:24-41 |
| `FUN_00642c50` | 0x00642c50 | picks the gauge-fill colour sheet by team | FUN_00642c50.c:27-60 |
| `FUN_006429c0` | 0x006429c0 | frees the 9 P-atlas sprites | FUN_006429c0.c:12-14 |
| `FUN_00633ca0` | 0x00633ca0 | battle-scene init: loads `data/object/system.bmp`, `P04/P05/P08/P09`, 10 trails, 7 auras; calls `FUN_00642510` once and `FUN_00642a00` 4x; creates the GDI text object | FUN_00633ca0.c:39-99, :106-111 |

Sprite drawing primitives (all take the sprite in ECX; `pivot` = params 7/8 of `FUN_00655b20`):

* `FUN_00655d60(sprite, x, y)` — quad top-left `= (x - pivotX*scaleX, y - pivotY*scaleY)`,
  quad size `= (srcW*scaleX, srcH*scaleY)`. Scale set by `FUN_00408250(sprite, s)`
  (writes sprite+0x84/0x88 = fields [0x21],[0x22]). Evidence: FUN_00655d60.c:15-20,
  FUN_00408250.c:10-11.
* `FUN_00655830(sprite, x, y, cellX, cellY)` — same, but the source rect is offset by
  `(cellX*cellW, cellY*cellH)`. Evidence: FUN_00655830.c:15-25.
* `FUN_00645250(sprite, x, y)` — gauge fill, clipped to `value/max` (`fVar2`); mode 0 grows
  right, mode 1 grows up, mode 2 grows left. Evidence: FUN_00645250.c:15-46.
* `FUN_00645690(sprite, x, y, s)` = `FUN_00408250(s)` + `FUN_00645250`. FUN_00645690.c:10-11.
* `FUN_00431b20/FUN_00431b50/FUN_00431ce0` — number / cell draws anchored at `(x, y)`.
  FUN_00431b50.c:22-53, FUN_00431ce0.c:13-14.

**Complete layout constant table, `0x6a4c90 .. 0x6a4cd8`** (19 floats; each value occurs exactly
once in `.rdata` and is referenced only from `FUN_00644150`, so this is the HUD's whole anchor set):

| addr | value | used for |
|---|---|---|
| 0x6a4c90 | 138.0 | x anchor, `LIMIT n%` readout (left) |
| 0x6a4c94 | 78.0  | y anchor, `n%` readout (left) |
| 0x6a4c98 | 525.0 | (top-centre counter / unused in 1P path) |
| 0x6a4c9c | 676.0 | x anchor, CHARGE count |
| 0x6a4ca0 | 489.0 | y anchor, CHARGE count |
| 0x6a4ca4 | 702.0 | x anchor, MAIN count |
| 0x6a4ca8 | 443.0 | y anchor, MAIN count |
| 0x6a4cac | 597.0 | MAIN/CHARGE bar anchor x |
| 0x6a4cb0 | 623.0 | MAIN bar anchor x |
| 0x6a4cb4 | 471.0 | MAIN bar anchor y |
| 0x6a4cb8 | 216.0 | x anchor, tactics/command indicator |
| 0x6a4cbc | 520.0 | y anchor, tactics/command indicator |
| 0x6a4cc0 | 517.0 | STAMINA bar anchor y |
| 0x6a4cc4 | 183.0 | x anchor, boxed tactics label |
| 0x6a4cc8 | 548.0 | y anchor, boxed tactics label |
| 0x6a4ccc | 534.0 | y anchor, MAX label |
| 0x6a4cd0 | 488.0 | OYASHIRO gauge anchor y |
| 0x6a4cd4 | 505.0 | HP bar anchor x |
| 0x6a4cd8 | 565.0 | HP bar anchor y |
| 0x6a2abc | 55.0  | OYASHIRO gauge anchor x |
| 0x6a16d4 | 400.0 | STAMINA bar anchor x |
| 0x6acf4c | 64.0  | MAX label anchor x |

---

## 2. Element table

Rect columns: **print** = measured on `battle-hud.webp`; **frame** = `print + (2, -6)`, i.e. the
800x600 coordinate a WebGPU implementation must hit. "art"/"text" = whether the element is
texture art or GDI text (see §4).

| # | Element | Purpose | print rect | frame rect | art/text | Asset + address |
|---|---|---|---|---|---|---|
| 1 | `0%` readout, left | own balloon fill % | (41,90)-(160,111) | (43,84)-(162,105) | art | P00 digit set; `FUN_00644150` anchor (110,80) — FUN_00644150.c:149-151 |
| 2 | `LIMIT 100%`, left | own balloon limit (lose above it) | (29,110)-(151,129) | (31,104)-(153,123) | art | P00 (digits at scale 0.5) + P00 `LIMIT` label (399,330)-(454,341); anchors (138,110) scale 0.5 — FUN_00644150.c:152-153 |
| 3 | `0%` readout, right | enemy balloon fill % | (701,90)-(769,111) | (703,84)-(771,105) | art | mirrored; anchor (740,80) — FUN_00644150.c:164-168 |
| 4 | `LIMIT 100%`, right | enemy balloon limit | (659,110)-(781,129) | (661,104)-(783,123) | art | mirrored; anchor (768,110) scale 0.5 — FUN_00644150.c:169-170 |
| 5 | Blue balloon (left) | own balloon, grows with damage | visible tip (70,118)-(95,150) | (72,112)-(97,144) | art | P00 (0,320,192,192) pivot (96,160); anchor (85,140), y = 30 + value/2 — FUN_00644150.c:155-157; sprite 0x6ca460 |
| 6 | Pink balloon (right) | enemy balloon | visible tip (699,116)-(734,150) | (701,110)-(736,144) | art | P00 (192,320,192,192) pivot (96,160); anchor (715,140) — FUN_00644150.c:172-174; sprite 0x6ca500 |
| 7 | Counter `181`, top-right | frame/`DAT_006cf3c4` counter (README calls it FPS) | (759,6)-(795,18) | (761,0)-(797,12) | art | P00 **yellow** small digits; **draw site unresolved** — see §6 Q1 |
| 8 | Alert balloon `!` | "this fighter is targeting you" | (377,46)-(421,91) | (379,40)-(423,85) | art | P06 (0,128,128,128) = pale pentagon; sprite 0x6c78f8 (pivot 64,64) — FUN_00642510.c:60; drawn in `FUN_00643230` |
| 9 | `com` bar | target's HP strip, centre-top | (356,96)-(439,110) | (358,90)-(441,104) | art | P03/P01 sheets; drawn in `FUN_00643230`; pale inner fill measured (358,102)-(421,107) |
| 10 | Targeting brackets, red | lock-on ring around the target | (366,136)-(431,201) | (368,130)-(433,195) | art | P03 ring sheet: sprite 0x6c7d58 (base (0,128), 128x128 cells) / 0x6c7e98 (base (128,128)); red ring cell atlas (0,256,128,128); drawn in `FUN_00643230` |
| 11 | Overhead HP bar + nameplate | each fighter's HP over the head | not separable in this print | — | art | `FUN_00643230`; projected at `(clip*400+400, -clip*300+300)` + 70.0 world units up (FUN_00643230.c:56-58) |
| 12 | OYASHIRO fan gauge (frame) | hypermode/limit gauge, bottom-left | (42,481)-(300,597) | (44,475)-(302,591) | art | P01 (0,256,300,128) pivot (45,21); anchor (55,488); sprite 0x6c7cb8 — FUN_00642510.c:45, FUN_00644150.c:29 |
| 13 | Gauge gradient fill | fills the fan | inside #12 (empty at 0%) | — | art | P02 (0,0,256,96) / P12 (0,0,256,96); per-player slots `hud+0x610+i*0xac`, `FUN_00642c50` selects the colour cell — FUN_00644150.c:35/46, FUN_00642c50.c:29-31 |
| 14 | Boxed `適当` label | tactics/command readout | (153,509)-(274,543) | (155,503)-(276,537) | art | **P03 (0,0,128,64) pivot (64,32)**, cells 128x64, sprite `0x6ca140` (`FUN_00642510` @0x642993-0x6429ae, `.c:68`), anchor **(216,520)** = `.rdata` 0x6a4cb8/0x6a4cbc (`FUN_00644150.c:102-104`, @0x644859-0x6448ad), cell from `hud+0x310` (col = v mod 4, row = v div 4) -> quad (152,488), art (153,502)-(278,539). Print match: mean |diff| 0.00 |
| 15 | `MAX` label | gauge full | not visible (0%) | — | art | P00 (384,384,128,128) pivot (64,64); anchor (64,534); sprite 0x6c7b78 — FUN_00644150.c:42 |
| 16 | STAMINA bar | dash/jump/block stamina | not visible in this print | — | art | P01 (64,0,192,64) pivot (96,32) frame + P02 (0,480,230,14) fill; anchor (400,517); sprites 0x6ca5a0 / slot 0x2b4 — FUN_00644150.c:88-89 |
| 17 | `MAIN` bar + `main` word | shots loaded | outline (611,470)-(786,492); fill (621,477)-(781,483) | outline (613,464)-(788,486); fill (623,471)-(783,477) | art | P01 (64,128,192,64) pivot (96,32) = 0x6ca6e0; fill = a 160x6 P01 strip (slot +0x768/+0x814/+0x8c0/+0x96c = atlas (320,128)/(320,64)/(320,144)/(320,80)); anchor (623,471) — FUN_00642510.c:47, FUN_00644150.c:107, slot table §8 |
| 18 | `6` MAIN count | ammo count | (650,435)-(700,470) | (652,429)-(702,464) | art | P00 white digit set; anchor (702,443) right-aligned — FUN_00644150.c:110 |
| 19 | `CHARGE` bar + word | charge stock | outline (589,519)-(766,546); fill (597,523)-(755,529) | outline (591,513)-(768,540); fill (599,517)-(757,523) | art | P01 (64,64,192,64) pivot (96,32) = 0x6ca780; fill = P01 (320,96,160,5)…; anchor (597,517) — FUN_00642510.c:47, FUN_00644150.c:109 |
| 20 | `2` CHARGE count | charge count | (630,485)-(680,515) | (632,479)-(682,509) | art | P00 white digits; anchor (676,489) — FUN_00644150.c:112 |
| 21 | `HP` bar (frame) | own HP | (495,564)-(748,600) | (497,558)-(750,594) | art | P01 (32,192,256,64) pivot (13,25); anchor (505,565); sprite 0x6c7f60 — FUN_00642510.c:43, FUN_00644150.c:23 |
| 22 | `HP` fill (yellow→orange) | HP value | (503,571)-(733,585) | (505,565)-(735,579) | art | P02 (0,480,230,14) at 1:1 (230x14); drawn twice (value + lag ghost) — FUN_00644150.c:25,27 |
| 23 | Hypermode name caption (OYASHIRO) | hypermode label inside the fan | art (196,558)-(298,569) | — | art | P01 (0,384+32*hmode,128,32), sprite `0x6c7df8` (`FUN_00642510.c:53`, @0x64276f-0x642789), anchor (183,548) = 0x6a4cc4/0x6a4cc8, hmode = `hud+0x318`; `FUN_00644150.c:48/66/84` (@0x644443/0x6445c4/0x644745). Rows: 0 OYASHIRO, 1 FRIENDSHIP, 2 KAKERA |
| 24 | STAMINA/command centre overlay | contextual | not visible | anchor (400,300)/(400,200)/(400,400) | art | FUN_0063a130.c:84-98 |
| 25 | KO sting `撃破!` | KO banner | not in this print (see `ko-moment.webp`) | — | art | P09 (0,256,512,256) → 256x128 at 1:1; sprite in FUN_00633ca0.c:77 |
| 26 | Round countdown `3 2 1` | pre-battle | not in this print | — | art | P09 (0,0,192,256),(192,0,192,256),(384,0,128,256) → 96x128 / 96x128 / 64x128 — FUN_00633ca0.c:79-81 |
| 27 | Team-victory stings | result | not in this print | — | art | P05 (blue 青組/大勝利), P08 (red 赤組/大勝利) — FUN_00633ca0.c:83-86 |
| 28 | Battle-start sting `開始!` | round start | not in this print | — | art | P04 (0,288,512,192) → 256x96 — FUN_00633ca0.c:78 |
| 29 | `OVER KILL!!` / `DOWN!` / `PAUSE` / `もう一度挑戦しますか？` / `はい` / `いいえ` / `本日の活動報告` / `1P 2P 3P 4P com` | pause + result overlays | not in this print | — | art | `data/object/system.cnv` (512x512) — FUN_00633ca0.c:89-95 |
| 30 | Soft oval glow + crosshair | screen overlay (P13) | not visible | full-screen quad | art | P13 (0,0,512,512); sprite 0x6ca280 (pivot 0,0) — FUN_00642510.c:56 |
| 31 | Violet/grey horizontal band at y≈65-90 | **NOT a HUD element** | — | — | — | It is the schoolyard wall in the 3D scene: the same colours appear at x=600 in the same rows and no layout constant in `0x6a4c90..0x6a4cd8` sits there |

### Numbers in the print that the RE does not cover

* **Counter `181` (print (759,6)-(795,18), yellow).** `FUN_00644150.c:177-198` draws a
  `DAT_006cf3c4`-derived counter at three x anchors 416 / 428 / 442 with y = 10, gated by
  `DAT_006cf3c0 != 0`, and `(DAT_006cf3c4 + 0x3b) / 0x3c` as the value. That is a *top-centre*
  position, not the top-right corner of the print. Not resolved; see §6 Q1.
* **`com` bar and brackets** are drawn from the *projected* target position
  (`FUN_00643230`), not from fixed constants — a spec must reproduce the projection
  (`x = (clip.x/clip.w)*400 + 400`) and the 70.0 world-unit lift, not a fixed rect.

---

## 3. Asset inventory

Bundle read order matters: `AssetSource` resolves the **first** matching entry in
precedence order (earliest-registered archive wins; `remake/foundation/src/assets/dat_bundle.cpp`).
The exe asks for
`data/object/*.bmp` but the archives ship `*.cnv` — the loader maps the extension
(`FUN_006560c0` @0x006560c0 → `FUN_00656c80`; `cnv` header reverse-engineered from
`FUN_00665e70`, documented in `remake/tools/asset-tools/cnv_convert.py`). **Two of these
entries exist in more than one bundle with different bytes** (§6 Q2).

Dumped to PNG for inspection during the investigation (32bpp RGBA); reproduce with the recipe in §7.
CNV layout: byte 0 = bpp, +1 u32 field1, +5 u32 height, +9 u32 width, +13 u32 compressed,
+17 pixel data; bpp>=24 stores 4 bytes/px BGRA.

| entry | bundle | bytes | offset | pixels | what it looks like |
|---|---|---|---|---|---|
| `data/object/P00.cnv` | daybreak00.dat | 1048593 | 1348472243 | 512x512x32 | **digit + balloon atlas.** Row y0-28: white outlined digits `0`-`7` (glyphs 36-41 x 27, x at 23/101/153/217/282/344/410/474). Row y55-90: white `8` `9` `%` `/`. Row y118-155: red `0`-`7`. Row y175-215: red `8` `9` `%`. Row y245-276: **small** green `0-9 + - . %` (27x21, pitch 32). Row y280-308: small yellow `0-9 + - . %`. (399,330)-(454,341): small `LIMIT` word. (25,337)-(167,494): blue balloon 142x157. (217,337)-(359,494): pink balloon 142x157. (392,404)-(504,486): `MAX` 112x82 |
| `data/object/P01.cnv` | daybreak00.dat | 1048593 | 1347423650 | 512x512x32 | **labelled bars + fan gauges + tags + thin ramps.** (93,11)-(228,49) `STAMINA` pill+bar; (66,72)-(254,118) `CHARGE`; (66,138)-(254,177) `MAIN`; (31,199)-(289,245) `HP`; (31,260)-(289,382) **OYASHIRO** fan (label baked in at its bottom-right); (26,370)-(289,510) **FRIENDSHIP** fan; x320-512: thin gradient strips at y 0 (107x6), 64/80/96/112/128/144 (160x5-6), 320/333/336/349/352 (80x6); (363,207)-(469,241) blue `1P 2P 3P / 4P com`; (363,466)-(468,495) red `1P 2P 3P / 4P com`; (340,265)-(365,278) small capsule |
| `data/object/P01.cnv` | **daybreak04.dat** | 1048593 | 921095646 | 512x512x32 | **different bytes** (sha1 6ebc4967 vs 6830e6ee): same bars, but the fan captions are split out — `OYASHIRO` (8,378), `FRIENDSHIP` (8,414), `KAKERA` (8,450) as separate captions, and a third fan. Dumped as `dx_P01.png` |
| `data/object/P02.cnv` | daybreak00.dat | 1048593 | 1346375057 | 512x512x32 | **gauge gradient fills + HP ramps.** 2 cols x 5 rows of quarter-fan gradients, cells 230x91 at (col*256, row*96): (0,0) magenta, (1,0) green→teal, (0,1) pink, (1,1) yellow-green, (0,2) purple→blue, (1,2) pale-yellow→mint, (0,3) crimson→violet, (1,3) green→teal, (0,4) pale lavender, (1,4) cyan→pale blue. Bottom y480-494: (0,480,230,14) red→yellow→orange (the **HP fill**) and (256,480,230,14) pale lavender |
| `data/object/P03.cnv` | daybreak00.dat | 1048593 | 1345326464 | 512x512x32 | **command labels + brackets + arrows.** Row 1 (y13-52, 4 cells of 128): yellow boxed `適当`, red boxed `格闘`, orange boxed `射撃`, green boxed `集中`. Row 2 (y77-116, 2 cells): green boxed `各個`, cyan/blue boxed (two kanji, low contrast — likely `後退`, unconfirmed). y128-512: 128x128 cells — rings and direction arrows. Rings (atlas bbox, 4 arcs each): dark grey (30,157)-(98,226); black (277,148)-(363,235); **red (30,285)-(98,354)**; blue (283,282)-(357,357); green (30,412)-(98,483). Arrow cells: grey x128-256 y128-256, red x128-256 y256-384, green x128-256 y384-512, blue x384-512 y128-256, pale blue x384-512 y256-384 |
| `data/object/P04.cnv` | daybreak00.dat | 1048593 | 1344277871 | 512x512x32 | `撃破!` (0,0,512,256) and `開始!` (0,288,512,192): huge kanji, white outline + red fill + black drop shadow |
| `data/object/P05.cnv` | daybreak00.dat | 1048593 | 1343229278 | 512x512x32 | blue team stings: `青組` (0,0,512,256), `大勝利` (0,256,512,256) |
| `data/object/P06.cnv` | daybreak00.dat | 262161 | 1342967117 | 256x256x32 | **alert balloons**: yellow starburst `!` (0,0,128,128), red starburst `!` (128,0,128,128), pale pentagon `!` (0,128,128,128) |
| `data/object/P08.cnv` | daybreak00.dat | 1048593 | 1341918524 | 512x512x32 | red team stings: `赤組` / `大勝利` (same rects as P05) |
| `data/object/P09.cnv` | daybreak00.dat | 1048593 | 1340869931 | 512x512x32 | `3` (0,0,192,256), `2` (192,0,192,256), `1` (384,0,128,256), `撃破!` (0,256,512,256) |
| `data/object/p12.cnv` | daybreak04.dat | 1048593 | 921095646 | 512x512x32 | **DX-era second gradient set** for the fan gauge: gold/yellow and green/cyan variants, same cell grid as P02; bottom bars dark-red→yellow and pale |
| `data/object/p13.cnv` | daybreak04.dat | 1048593 | 920047053 | 512x512x24 | soft white oval glow on black with a thin crosshair — full-screen overlay |
| `data/object/system.cnv` | daybreak00.dat | 1048593 | 1339821338 | 512x512x32 | pause/result message atlas: `OVER KILL!!` (0,0,512,64), `DOWN!` (0,64,256,64), `PAUSE` (256,64,256,64), `もう一度挑戦しますか？` (0,128,416,64), `はい`/`いいえ` (0,192,256,64), `本日の活動報告` (0,320,288,64), `1P` (0,384,64,32), `1P 2P 3P 4P com` row |
| `data/object/勝利バー.cnv` | daybreak00.dat | 2097 | 1339819241 | 260x2x32 | 2-px-tall horizontal gradient strip; loaded as `&DAT_006a4944` = `data/object/勝利バー.bmp` (FUN_00633ca0.c:41) and cut into (0,0,256,1) + (255,0,1,1) at FUN_00633ca0.c:87-88 — a 1-px bar/pixel source |
| `data/object/logo.cnv` | daybreak00.dat | 262161 | 1349520836 | 256x256x32 | game logo (used by the result screen, `FUN_00647e00.c:88`) |
| `data/object/勝利画面土台.cnv` | daybreak00.dat | 1920017 | — | 800x600x24 | "victory screen base" full-screen backdrop — result screen, not battle HUD |
| `data/object/gameover.cnv` | daybreak00.dat | 1920017 | 1349782997 | 800x600x24 | game-over screen — result, not battle HUD |
| `data/directX/toon.cnv` | daybreak00.dat | 16401 | 1449949557 | 64x64x24 | toon-shading ramp (loaded as `data/directx/toon.bmp`, FUN_00650410.c:19) — renderer, not HUD |

**Assets with no identified HUD use** (flagged, not silently dropped):
`data/object/logo.cnv`, `data/object/gameover.cnv`, `data/object/勝利画面土台.cnv` (result screens);
`data/object/p13.cnv` (loaded and given a full-screen sprite 0x6ca280 but no draw site in
`FUN_00644150` — presumably a screen effect); `data/object/P04/P05/P08/P09` (round stings, only
used through `FUN_00633ca0`'s sprite setup, not the corner HUD).

**Elements whose art was NOT found in any bundle:** none — every element of `battle-hud.webp`
maps to art above. The one *provenance* gap is #14 (§6 Q2).

---

## 4. Text spec

**There is no GDI text in the battle HUD.** Every label in `battle-hud.webp` is texture art:

* A byte search of `DaybreakDX.exe` finds **no** occurrence of `LIMIT` (0), `CHARGE` (0),
  `STAMINA` (0), `OYASHIRO` (0), `com\0` (0), `適当` (0), `格闘` (0), `射撃` (0), `集中` (0),
  `各個` (0). The single `MAIN` hit (file offset 0x2ac15a = VA 0x6ac15a) is inside
  `DOMAIN error\r\n` from the CRT string table, and the single `HP\0` hit (file offset 0xe8990 =
  VA 0x4e8990) is the operand bytes of a `jmp rel32` — both false positives.
  By contrast `ＭＳ ゴシック` (the GDI face, CP932 `82 6C 82 72 20 …`) occurs 5 times, one of them
  at VA 0x6a49d8 — the battle scene's font. So the label *strings* are genuinely absent while the
  font *is* present: the HUD words are art, the font serves something else.
* All of those words are visible as glyph art in `P00`/`P01`/`P03` (§3).
* `CJK-TEXT.md` §2 asserts the in-battle HUD is "mostly Latin" GDI text plus the `適当` string.
  **That is wrong for the battle HUD** — it is right for the menus and result screens, where the
  GDI path is used. The `ui::TextLayer` requirement stands for menus/results, not for battle.

**The battle scene's GDI text object** (created but not used for the HUD):
`FUN_00633ca0.c:106` `FUN_0065d6f0(DAT_006d1850)` → `scene+0xf78`;
`FUN_00633ca0.c:110` `FUN_0065d7e0(&DAT_006a49d8, 0x1e, 0xff, 0xff, 0xff)` — face
`DAT_006a49d8` = CP932 `82 6C 82 72 20 83 53 83 56 83 62 83 4E` = **`ＭＳ ゴシック`** (MS Gothic),
height `0x1e` = 30, colour white; `FUN_00633ca0.c:111`
`CPane::SetBorders(*(CPane **)(param_1 + 0xf78), 0x2a8, 5, 0, 7)` = (680, 5, 0, 7).
Its consumers are `FUN_00634520` (battle teardown, FUN_00634520.c:44-46), `FUN_00635d40`
(result screen) and `FUN_0063c2a0` — none of them the in-battle HUD.

**The `適当` label's box geometry** (the CJK element a text layer would have to draw, if the
implementation chooses text over art):

| property | value |
|---|---|
| measured print rect | (153,509)-(274,543) — 122x35 of yellow pixels |
| frame rect | (155,503)-(276,537) |
| atlas source | `data/object/P03.cnv` row-1 cell 0, atlas rect (1,13)-(127,52) — 126x39 |
| cell geometry | 128x128 cell at atlas (0,0); drawn at 1:1 = 128x128 screen px |
| RE draw site | `FUN_00644150.c:48` `FUN_00655830(183, 548, 0, cell)` — anchor (183,548), cell index from `hud+0x318` |
| glyph colours | fill `#FFD400`-ish yellow, white inner highlight, black outline (sampled mean of the box pixels: R>200, G>150, B<100) |
| flanking boxes | the two small rounded boxes either side of `適当` contain a single horizontal dash each — they are part of the same texture, **not** font glyphs (confirmed at 4x zoom of the print and in the atlas) |

Recommended implementation: **draw the atlas cell**, not a font glyph. If a `TextLayer` string is
wanted anyway, the label is `適当` (CP932 `93 4B 93 96`) at 128x39 cell geometry, yellow on black
outline.

---

## 5. Priority list

Ordered by visible difference from the foundation's current HUD (plain Arial-bold text + flat
bars), largest first. "Size" = what a track must produce.

| # | Element | Why first | Size |
|---|---|---|---|
| 1 | **Sprite/atlas pipeline for `.cnv`** (P00/P01/P02/P03/P06) | Nothing else can land without it; the container and the 32bpp BGRA path are already documented | **assets found** (5 entries, ~3.6 MB), **layout known** (`FUN_00642510` table), ~1 sprite struct + sub-rect UVs |
| 2 | **Bottom-right cluster**: MAIN bar + count, CHARGE bar + count, HP frame + yellow fill | The single largest area of flat-colour error in the gate frame; all four are pure art with exact anchors | **assets found**, **layout known** — anchors (623,471) (597,517) (505,565), counts (702,443) (676,489); small |
| 3 | **OYASHIRO fan gauge** (frame + gradient fill) | The most distinctive silhouette in the print; the foundation draws nothing like it | **assets found** (P01 (0,256,300,128) + P02 fills), **layout known** — anchor (55,488); medium (needs the clipped-fill draw, `FUN_00645250`) |
| 4 | **Balloon `0%` / `LIMIT 100%` readouts + balloon sprites, both corners** | Four labels + two growing sprites, mirrored; the corner composition is very visible | **assets found**, **layout known** — anchors (110,80) (138,110) (740,80) (768,110) (85,140) (715,140); medium (number rendering + the `y = 30 + value/2` balloon growth) |
| 5 | **Boxed `適当` tactics label** | The CJK element the owner flagged; currently absent | **assets found** (P03 cell), **layout partially unresolved** (§6 Q2); small once resolved |
| 6 | **Targeting brackets + `com` bar + alert balloon** (per-fighter) | Needs the world→screen projection and per-fighter state, not just corner constants | **assets found** (P03 rings, P06 balloons), **layout known for the projection** (`FUN_00643230.c:56-58`); medium |
| 7 | **Round stings**: `3 2 1`, `開始!`, `撃破!`, `赤組/青組 大勝利` | Large full-screen art, but they are transients — the gate frame does not contain them | **assets found** (P09/P04/P05/P08), **layout known** (`FUN_00633ca0.c:77-86`); medium |
| 8 | **STAMINA bar** + the (216,520) command indicator | Contextual, absent from the gate frame | **assets found**, **layout known** — anchors (400,517) and (216,520); small |
| 9 | **`OVER KILL!!`/`DOWN!`/`PAUSE` overlays** | Pause/message path, separate from battle | **assets found** (`system.cnv`), **layout known** (`FUN_00633ca0.c:89-95`); small |

---

## 6. Open questions

1. **Where is the top-right counter (`181`) drawn?** `FUN_00644150.c:177-198` is the only
   `DAT_006cf3c4`-based counter, and it anchors at (416,10)/(428,10)/(442,10) — top-centre,
   gated on `DAT_006cf3c0 != 0`, value `(DAT_006cf3c4 + 0x3b) / 0x3c`. The print's `181` is at
   frame (761,0)-(797,12) in the **yellow** small digits. Ruled out: `FUN_00644150`'s three
   anchors (wrong x, wrong digit colour); `FUN_0064c1e0` (called from FUN_00644150.c:213 when
   `DAT_006cfdb0 == 2`) — not yet read. **Next step:** read `FUN_0064c1e0` (0x0064c1e0) and
   `FUN_00431b50`'s real signature (the decompiler's parameter mapping contradicts its call
   sites: the call passes the value first, the body uses the second parameter as the value).
2. **[RESOLVED 2026-10-03] The boxed `適当` label's sprite provenance.** The conflict came
   from attributing the `(183,548)` draw to the label. The label is **not** a `P01` sprite.

   * **Boxed `適当` = static sprite `0x6ca140` = `data/object/p03.cnv` (0,0,128,64), pivot
     (64,32)**, cells 128x64. Created at the *end* of `FUN_00642510` — disassembly
     @0x642993-0x6429ae (`push 0x20; push 0x40; push 0x40; push 0x80; push 0; push 0;
     push [0x6c7f44]; mov ecx,0x6ca140; call 0x6556c0`), decompiled `FUN_00642510.c:68`
     (the file's last line). Constructor semantics: `FUN_006556c0.c:15-28`.
   * **Draw site** `FUN_00644150.c:102-104` / disassembly @0x644859-0x6448ad:
     `FUN_00655830(216*scale + vpLeft, 520*scale + vpTop, v mod 4, v div 4)` with
     `v = (int8)hud+0x310` (anchors `.rdata` 0x6a4cb8 = 216.0f, 0x6a4cbc = 520.0f; arg3 =
     cell column, arg4 = cell row, `FUN_00655830.c:15-21`). Cell values: 0 `適当`
     (yellow), 1 `格闘`, 2 `射撃`, 3 `集中`, 4 `各個`, 5 `後退`.
   * **Anchor arithmetic**: pivot (64,32) gives quad origin (152,488) at 1P scale; the
     cell's art is (1,14)-(126,51), i.e. **(153,502)-(278,539)** — the measured print box
     (155,503)-(276,537) within the antialiased rim. The print quad against `P03`
     (0,0,128,64) measures mean |diff| **0.00**; the same search over every other atlas in
     every bundle scores 38-100.
   * **Atlas**: `data/object/p03.cnv` ships in **`daybreak00.dat` only** (1,048,593 B,
     entry offset 1,345,326,464, sha1 `103c62a7...`).
   * The **`(183,548)` anchor is a different element**: static sprite `0x6c7df8` = `P01`
     **(0,384,128,32)** (`FUN_00642510.c:53`, @0x64276f-0x642789) is the **hypermode name
     caption**, drawn with cell row = `hud+0x318` (0 `OYASHIRO`, 1 `FRIENDSHIP`, 2 `KAKERA`)
     at `FUN_00644150.c:48/66/84` (@0x644443/0x6445c4/0x644745). In `battle-hud.webp` that
     is the `OYASHIRO` word at frame (196,558)-(298,569). The (-28,-45) gap was therefore an
     artefact of comparing the *tactics label* with the *caption's* anchor.
   * **Which `P01` the print used**: **`daybreak04.dat`'s** (sha1 `6ebc4967...`, entry
     offset 922,144,239), not `daybreak00.dat`'s (`6830e6ee...`). Fan quad and caption quad
     mean |diff| are 3.20 / 2.65 for the DX atlas against 10.39 / 100.51 for the 2006 one.
     Reason: the exe registers daybreak07, then **04**, then **00** (0x64d4d4 / 0x64d4ee /
     0x64d4fe) and the earlier-registered archive wins a duplicate name — which is why
     `assets/dat_bundle.cpp`'s bundle order is precedence order, not file-number order.
   * **Build**: `daybreakdx_111s.exe` is not a build — it is an LHA self-extracting patch
     (7-Zip: `Type = Lzh`, payload at 28162) whose payload `DaybreakDX.exe`
     (sha1 `f009a521...`) and `daybreak07.dat` (`eb315a27...`) are byte-identical to the
     installed files. The 2006 `daybreak.exe` is excluded: it holds no
     `P01 (0,384,128,32)` sprite and no 183.0f/548.0f anchors, so it cannot draw the
     print's caption. The prints are the corpus `DaybreakDX.exe` v1.11.

3. **Exact pivot semantics of `FUN_00655b20` params 7/8.** The model
   "quad top-left = (x - param7, y - param8), size = srcW x srcH at scale" reproduces the HP fill
   and the MAIN fill **exactly** and the OYASHIRO frame within ~4 px, but several sprites carry
   params 7/8 that are *not* half the source size (e.g. 0x6c7f60 = src 256x64 with (13,25)), so
   they are pivots rather than destination sizes. Confirm against the two remaining unexplained
   draws in `FUN_00644150` (the (216,520) cell draw and the `FUN_00645250` at (55,488)).
4. **`FUN_00644150`'s arguments.** The decompiler's `__thiscall` mapping is internally
   inconsistent (`FUN_00643200.c:10` forwards three args to a four-parameter function;
   `FUN_0063a130.c:60` puts a *float* viewport coordinate in ECX). The immediates inside
   `FUN_00644150` are unambiguous and are what the table above uses; the *entry* convention
   (which register holds the HUD struct) still needs one disassembly pass from `FUN_0063a130`.
5. **Which digit set is which.** P00 has four sets (two large: white y0-28/y55-90 and red
   y118-155/y175-215; two small: green y245-276 and yellow y280-308). The print uses small glyphs
   for `0%`/`100%` (measured 28x21) but they render white, and no *white small* set was found in
   P00. Either a fifth set exists outside the bands scanned, or `FUN_00431b50` recolours.
   **Next step:** scan P00 bands y 210-250 and y 308-330 at glyph level.
6. **`FUN_00643230`'s sprite handles and cell indices.** The per-fighter draws use
   `FUN_00655830(x, y, local_30, local_28)` with `local_30 ∈ {0,2}` and `local_28 ∈ {0,1,2}`;
   the sprite is loaded into ECX earlier in the function and was not captured. The bracket/arrow
   cells are known (§3 P03) but which cell index is the red bracket is inferred from the atlas,
   not from the code. **Next step:** disassemble 0x00643230 and capture the `mov ecx,` before each
   `call 0x655830`.
7. **The `com` bar's source sprite and its `com` word.** The word `com` is art in
   `system.cnv` (the `1P 2P 3P 4P com` row, ~(396,297)-(435,310) in P01 is the blue variant);
   the print's `com` is white/pale. Which of the two sheets the battle path uses is unresolved.

---

## 7. Reproducing the measurements

No scratch artefacts are committed and no game art is copied into the repo. Everything in
this document can be re-derived with the tools already here:

| what | how |
|---|---|
| list a bundle's entries | `python3 remake/tools/asset-tools/extract_dat.py` (see its usage) — header-only listing, no full extraction |
| dump one `.cnv` atlas to an image | extract the entry, then `python3 remake/tools/asset-tools/cnv_convert.py <file.cnv> <out.png>` (32bpp; keep RGBA) |
| sub-rect / alpha bounding boxes / connected components | any image tool; the sprite table in §3 already gives the rects, so this is only needed to check a claim |
| measure the print | `remake/docs/reference/battle-hud.webp`, converted to PNG; remember the (-2,+6) print-vs-frame offset from the top of this document |
| print-parity capture vs `battle-hud.webp` (pinned spawn, `ROADMAP-PENDING.md` A2) | `remake/foundation/build/linux/foundation_demo --headless --out=/tmp/bh_p0.ppm --stage=<data>/stage01 --character=<data>/rena --enemy=<data>/mion --match --camera=arena --spawn=-463,200,-2200 --spawn2=-1363,200,-2200 --frames=150 --size=800x600`, then `python3 remake/foundation/tests/hud_bands.py /tmp/bh_p0.ppm --bands scene-floor` (expect 0.2772). Pinned: P1 `points[0]`, P2 `points[1]`; converged eye `(-174,411,-2200)`. `--frames` ≥121 is load-bearing (match eye converges 10%/call from the origin); the `camera arena at ...` log line is the static remake-preset seed, not the rendered match camera (`gameplay::ArenaCamera`, original preset); capturing fixes `--dt` at 1/60, so the run is deterministic; re-check all four spawn configs with `python3 remake/foundation/tests/pin_viewpoint.py` |
| string and address lookups in the exe | `research/tools/` and the PE section map in `research/binary_data/metadata.txt` (VA ↔ file offset) |

## 8. Appendix — per-player HUD sprite slots (`FUN_00642a00`, 0x00642a00)

`FUN_00642a00(hud)` fills `hud+0x2b4 + k*0xac`; `FUN_00644150` indexes them by
`i = (hud->frame % 0x1e) / 0xf` (0 or 1) for the animated fill and by the team index for the
team-coloured fill. Read out of the exe at 0x00642a07-0x00642b9a.

| slot | source | pivot | what it is |
|---|---|---|---|
| +0x2b4 | P02 (0,480,230,14) | (0,0) | HP fill, variant 0 (measured on the print at (505,565), 230x14) |
| +0x360 | P02 (256,480,230,14) | (0,0) | HP fill, variant 1 |
| +0x40c | P02 (0,496,230,14) | (0,0) | HP fill, variant 2 |
| +0x4b8 | P01 (320,0,107,6) | (53,3) | top-centre thin bar (drawn at half size: 53x3) |
| +0x768 | P01 (320,128,160,6) | (0,0) | 160x6 bar strip |
| +0x814 | P01 (320,64,160,6) | (0,0) | 160x6 bar strip |
| +0x8c0 | P01 (320,144,160,6) | (0,0) | 160x6 bar strip |
| +0x96c | P01 (320,80,160,6) | (0,0) | 160x6 bar strip |
| +0xa18 | P01 (320,96,160,5) | (0,0) | 160x5 bar strip |
| +0xac4 | P01 (320,112,160,5) | (0,0) | 160x5 bar strip |
| +0xb70 | P01 (320,320,80,6) | (40,3) | 80x6 bar strip |
| +0xc1c | P01 (320,352,80,6) | (40,3) | 80x6 bar strip |
| +0xcc8 | P01 (320,333,80,6) | (40,4) | 80x6 bar strip (half-height pixels) |
| +0xd74 | P01 (320,349,80,6) | (40,4) | 80x6 bar strip (half-height pixels) |

`hud+0x610 + i*0xac` (slot 5 onward) is the **team-coloured gauge fill**; it is not written by
`FUN_00642a00` in this build — `FUN_00642c50` writes the colour-specific fill sprites
(FUN_00642c50.c:29-42 for team 0/1, :51-53 for team 2, using P02 cells (0,0)/(256,0) and P12
(0,0)), which is consistent with slot 5 being the fill drawn at (55,488) by FUN_00644150.c:35/46.

HUD state fields referenced by the two HUD drawers (all on the struct pointed to by `scene+0xb70`):

| offset | meaning | evidence |
|---|---|---|
| +0x310 | signed tactics/command cell index (4 x N grid) | FUN_00644150.c:91-104 |
| +0x314 | extra scale for the command indicator | FUN_00644150.c:92-97 |
| +0x318 | team/colour index 0/1/2 | FUN_00644150.c:31,50,68; FUN_00642c50.c:27 |
| +0x324, +0x328, +0x32c, +0x330 | 1P/2P/3P/4P/`com` tag tween targets | FUN_00642c50.c:32-59 |
| +0x6dc, +0x720 | MAIN / CHARGE counts (drawn at (702,443) / (676,489)) | FUN_00644150.c:110,112 |
| +0x6f4..+0x744 | bar value tween objects | FUN_00642c50.c:15-26 |
| +0x7a4 | gauge counter (compared against 0x9c4 = 2500) | FUN_00644150 disasm @0x6441d8 |
| +0x834, +0x838, +0x83c, +0x840 | charge/refill timers (compared against 1000) | FUN_00644150.c:86, FUN_00642c50.c:18-59 |
| +0x844, +0x845, +0x846 | per-team "ready" flags | FUN_00644150.c:33,51,69 |
| +0x848 | blink flag | FUN_00644150.c:57 |
| +0x860 | "not present" flag | FUN_00644150.c:91 |
