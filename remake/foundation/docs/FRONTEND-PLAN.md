# Front-end plan — menus and non-battle screens

Implementation plan for the game's front end (everything that is not the battle
screen), derived from the original executable and the reference prints. It is
written to be followed screen by screen: for each print it says what the screen
is, which `FUN_xxxxxx` draws and updates it, which assets it needs, whether its
labels are GDI text or atlas art, and how a finished screen is verified against
its print.

**Evidence base.** `DaybreakDX.exe` v1.11 (image base 0x400000; `.text`
0x401000–0x6a0fff, `.rdata` 0x6a1000–0x6b6fff, `.data` 0x6b7000–0x6d9d07 —
`research/binary_data/metadata.txt`), the decompiled corpus in
`research/decompiled/`, the raw sections in `research/binary_data/pe_extract/`,
the shipped assets under `Higurashi-Daybreak/` (local install, never committed),
and the prints in `remake/docs/reference/*.webp`.

Every claim below is one of: a `FUN_` with a `research/decompiled/` file:line, a
byte offset / address in the executable, a named shipped asset (decoded and
looked at), or a measurement of a print. Anything I could not find is marked
**not found** in the text; §7 collects them.

## 0. How to read this document

### 0.1 Reproducing the evidence

* **Decompiled source**: `research/decompiled/FUN_xxxxxx.c` — one file per
  function, with the address in the header comment. Annotated copies from the
  extraction phase (`*_06_top_dispatchers.c`, `*_06_top_hubs.c`,
  `LoadNextScene.c`, `*_loadnextcallee.c`) carry the same code with a better
  name.
* **Strings**: `.rdata` is byte-identical to its file image, so a string's file
  offset equals its virtual address. `research/binary_data/pe_extract/
  section_.rdata.bin` (VA 0x6a1000) can be walked for NUL-terminated
  ASCII/Shift-JIS strings; `research/binary_data/strings/filter_*.txt` hold the
  ASCII path tables the pipeline already extracted. Every "the exe does not
  contain string X" claim in §4 was made this way and can be re-run.
* **Code → string xrefs**: search `.text`
  (`research/binary_data/pe_extract/section_.text.bin`, VA 0x401000) for the
  4-byte little-endian address of the string. That is how the font sites in §4
  and the owner of `data/stage%02d` were found.
* **Data tables**: `.data` is also file-offset == VA (0x6b7000). §2.9 and §5.2
  quote dwords/bytes read straight out of it.
* **Assets**: `Higurashi-Daybreak/data/...`. `.cnv` = 17-byte header + 4-byte
  BGRA pixels **top-down**; `remake/foundation/src/assets/cnv.h` documents the
  fields and the trap that field 1 is *not* reliably the width. A throwaway
  decoder in `/tmp` is enough to look at any of them; nothing from the install
  may be copied into the repo.
* **Bundles**: the game loads `daybreak00..07.dat` first, case-insensitively,
  first match wins, and falls back to the extracted tree
  (`remake/foundation/src/assets/asset_source.{h,cpp}`). §3.2 lists, per asset,
  the bundle that carries it (entry tables read directly).

### 0.2 Scope decisions this plan inherits (not re-litigated)

* **D6** (`remake/docs/decisions.md`): offline versus + **LAN netplay** are the
  focus; DirectPlay is replaced, not ported. The original's netplay screens are
  therefore **specified and deferred**, not scheduled here — they belong to the
  netplay track (`remake/foundation/docs/FULL-REPLACEMENT-PLAN.md` §7). The one
  piece of them this plan does schedule is the **soft-keyboard widget**, because
  name entry is not netplay-specific.
* **Opening video is stubbed**: a `VideoPlayer` already exists on both trees
  (`remake/src/render/video_player.*`, `remake/foundation/src/audio/video.h`);
  this plan keeps the opening as a stub screen and does not re-do it.
* **Story mode stays loadable, not a focus** (D6). Its scenes are identified in
  §2.17 only far enough to keep the scene table honest.
* **No code in this document.** It is a plan; §5 names the files a track adds.

### 0.3 Corrections to existing documents (read before you trust them)

1. **Scene ids.** `remake/src/core/scenes.h` (header comment) still carries the
   retired `mvp/` mapping *"TITLE=0, SELECT=1, VS_LOAD=2, BATTLE=3, CONNECT=7,
   BATTLE_RUN=8"*. The real table is the factory `FUN_004020a0`, ids 0x00–0x15,
   and the real transitions are in §1.2. The stale mapping should not be reused.
2. **The title background.** `remake/docs/reference/README.md` says the title
   menu's background is `data/select/bg00`. It is not: `data/select/bg00.cnv`
   decodes to the four 青組/赤組 diamond panels (§2.3), and the title scene
   loads its own three assets — `data/title/back00.cnv` is the shrine-approach
   photo with the stone lanterns, exactly the print's background
   (`FUN_00410d60.c:28-33`).
3. **The DX9 remake's `Scene_Title`** draws the select-screen background —
   that is a remake naming artefact, not the original's title
   (`remake/docs/placeholders.md` §13). Original scene 1 is the real title.
4. **"6 items at y≈280, 45px stride"** (reference README) is a print estimate.
   The items are atlas art with their own cell geometry (§2.1); use the RE
   numbers, and re-measure the print for the anchor check.
5. **`.cnv` width/height fields are not trustworthy** — `data/network/nback0*.cnv`
   and `data/object/勝利画面土台.cnv` carry their fields in the opposite order
   from `data/select/bg00.cnv`; `cnv.h` already documents the same class of
   problem for `data/object/勝利バー.cnv`. Decode with the sibling `.bmp` or
   with the draw code's expectations, never with the header alone.

---

## 1. Screen inventory and flow

### 1.1 The prints → screens → original implementation

| # | print | what it is | original owner (RE) |
|---|---|---|---|
| 1 | `title-menu.webp` | main menu: logo, shrine background, six JP items | **scene 1** (`FUN_00410d60` ctor, `FUN_00410f60` update, `FUN_004114f0` draw) |
| 2 | `opening-frame-01.webp` | OP movie, letterboxed | **scene 0** (`FUN_00404eb0`, `movie/op.mpg`) |
| 3 | `team-select.webp` | select screen, four 青組/赤組 diamond panels + chibi roster, 決定/戻る | **scene 3 page 0** (`FUN_00408330`, `FUN_004090a0`, `FUN_00409340`, `FUN_0040b2b0`) |
| 4 | `char-select-rena.webp` | same screen, a panel filled with portrait + nameplate | **scene 3 page 0**, state 0 → 2 of `FUN_00409340` |
| 5 | `weapon-select-rena.webp` | WEAPON SELECT panel (name + flavour text over the portrait) | **scene 3 page 0**, `FUN_0040d700` + `data/select/wNN.cnv` |
| 6 | `hypermode-select.webp` | HYPERMODE SELECT panel (mode name + description) | **scene 3 page 0**, `data/select/P01.cnv` names + `P02.cnv` descriptions |
| 7 | `controller-select.webp` | CONTROLLER SELECT (PLAYER / COM per slot) | **scene 3 page 0**, `data/select/P02.cnv` PLAYER/com cells |
| 8 | `ready-confirm.webp` | 準備完了！ stamp + 1P/2P tag, 決定/戻る | **scene 3 page 0**, state 8 of `FUN_00409340`; `data/select/P01.cnv` 準備完了 cells |
| 9 | `stage-select-random.webp` | STAGE SELECT: ランダム default, `?` thumbnail | **scene 3 page 1** (`FUN_0040acb0`, `FUN_0040cd00`) |
| 10 | `stage-select-school.webp` | STAGE SELECT + BATTLE SETTING (5 knobs + 戦闘開始/戻る) | **scene 3 page 1**, same two functions |
| 11 | `controller-setup.webp` | 操作設定: 5 pages, full binding table | **scene 7** (`FUN_00403eb0`, `FUN_00404220`, `FUN_00404a50`) |
| 12 | `option-screen.webp` | 描画と音量の設定: 3 pages, 4 toggles + 4 sliders | **scene 6** (`FUN_00402890`, `FUN_00402be0`, `FUN_00403470`) |
| 13 | `vs-intro.webp` | VS sting: portraits slide in, animated VS | **scene 9** (`FUN_004115f0`, `FUN_00411ae0`, `FUN_00411cb0`) |
| 14 | `battle-hud.webp` | in-battle HUD | battle module (`remake/foundation/docs/BATTLE-HUD-SPEC.md`) |
| 15 | `battle-stamina.webp` | contextual STAMINA bar | battle module, same HUD functions |
| 16 | `ammo-bar.webp` | MAIN counter close-up (proportional fill) | battle module, `FUN_00645250`/`FUN_00645690` fill path |
| 17 | `ko-moment.webp` | 撃破！ sting + balloon inflate + `+N%` | battle module (`FUN_00633ca0` loads `data/object/P09`), trigger not read |
| 18 | `result-victory.webp` | 青組 大勝利 fullscreen sting | battle module (`FUN_00633ca0` loads `P05`/`P08`) |
| 19 | `result-quote.webp` | winner art + quote text box, Z advances | `FUN_00635d40` result phase, sub-phase 0 |
| 20 | `result-report.webp` | 本日の活動報告 ranking + earned titles | `FUN_00635d40` later phases + title objects (§2.15) |
| 21 | `netplay-menu.webp` | 通信対戦 menu (host/connect/name/delay/port/chat) | **scene 11** (`FUN_00412110`, `FUN_00412ac0`, `FUN_00413bb0`) — deferred (D6) |
| 22 | `netplay-lobby.webp` | room: member list, CHAT, GUIDELINE | **scene 12** (`FUN_00414750`, `FUN_00414d30`, `FUN_004151f0`) — deferred (D6) |
| 23 | `soft-keyboard.webp` | grid keyboard for name/IP entry | **scene 13** (`FUN_00419f10`, `FUN_0041a260`, `FUN_0041a5a0`) + `data/chat/name_p1.cnv` grid — widget scheduled, host screen deferred |

### 1.2 The flow, as the RE proves it

The original is a scene stack with **one owner of the transition**: the main
loop calls the current scene's vtable slot 3 (update), whose **return value is
the next scene id**, and hands it to the scene switcher.

* Main loop: `FUN_00657ef0.c:36-47` — `uVar3 = (**(code**)(*(int*)scene + 0xc))()`
  (slot 3), then `FUN_00657c80(uVar3)`; when the frame is drawn it calls slot 1
  (`+4`).
* Switcher: `FUN_00657c80.c:12-63` — if the requested id differs from the
  current one (`DAT_006b77b8`, set at `:63`), it runs a **25-frame fade**
  (`:33-49`, alpha `(counter*10+5) << 24` via `FUN_00650d50`), destroys the old
  scene (`:51-57`) and constructs the new one through the App's vtable slot 2
  (`:58`) = **the scene factory `FUN_004020a0`**.
* Factory: `FUN_004020a0_06_top_dispatchers.c:39-305` — `switch(scene_id)` with
  one constructor per id 0x00–0x15 (0x16+ falls to `default` and returns null =
  quit). The factory's own table entry is at `.rdata` 0x6a5614 inside the App
  vtable 0x6a560c = `[FUN_00402060, FUN_00402080, FUN_004020a0]`
  (`FUN_0064d780.c:11`).
* Boot: `FUN_0064d250_entry_sub.c:96-118` — window, then bundles
  `daybreak00/02/04/05/06/07.dat`, then the app object and the loop.

Transitions I could read directly (update function → returned id):

```
0  opening movie        FUN_00404ff0  → 0 (stay) | 1 (title)
1  TITLE                FUN_00410f60  → 4 | 3 | 0x0b | 6 | 7 | 0x16 (quit) | 1 (stay)
2  movie family (2nd)   FUN_004053d0  → 0x15 | stay            [not identified, §7]
3  SELECT (2 pages)     FUN_004090a0  → 9 (page 1 confirm) | 1 (back) | 3 (stay)
4  prologue movie       FUN_00405650  → 5 | 4 (stay)
5  story team select    FUN_00406310  → 8 | 5 (stay)
6  OPTIONS              FUN_00402be0  → 1 (back)
7  KEY CONFIG           FUN_00404220  → 7 (stay) | 1 (back)
8  story ADV/talk       FUN_0040eb30  → 5 | 9 | 2 | 0x15
9  VS INTRO             FUN_00411ae0  → 9 (animating) | 10 (after loading the stage)
10 BATTLE               FUN_00403b70  → 10 (stay) | 0x14 (game over) | 8 | 3
11 NETPLAY MENU         FUN_00412ac0  → 0x0c | 0x0d | 0x0b | 1
12 NETPLAY LOBBY        FUN_00414d30  → 0x0b | stay
13 NETPLAY (name/IP)    FUN_0041a260  → 0x0b | stay
14,15,16,17,18,19 story-mode support scenes (out of scope, §2.17)
20 GAME OVER            FUN_00403d70  → 0x14 (retry-ish: stays 20) | 1 (title)
21 STAFF ROLL           FUN_0040e0b0  → 0x15 (stay) | 1 (title)
```

So the title's six items map to ids one-for-one, proved by the item order in
the menu atlas (§2.1):

```
ストーリー  → 4  prologue movie  → 5  story team select → 8 story ADV → …
対戦        → 3  SELECT page 0 (team/character/weapon/hypermode/PLAYER-COM/ready)
                    → page 1 (STAGE SELECT + BATTLE SETTING) → 9 VS INTRO
                        → 10 BATTLE → 3 (rematch/back to select) | 20 GAME OVER
通信対戦    → 0x0b NETPLAY MENU → 0x0c LOBBY | 0x0d name/IP screen
環境設定    → 6  OPTIONS       → 1 (title)
操作設定    → 7  KEY CONFIG    → 1 (title)
終了        → 0x16 = no scene  → quit
```

Two facts worth stating because they are easy to get wrong:

* **The battle is not a "menu scene"**: scene 10 is a 4-byte stub object
  (`FUN_00403ae0`, vtable 0x6a142c); the battle itself lives in the engine
  module (`FUN_00648f30` battle init, `FUN_00648ad0`/`FUN_006492f0` stage loads
  — the two sites that reference `data/stage%02d`, `.text` 0x648b06 and
  0x649520), and the HUD/result/chat subsystems are the 0x63xxxx block.
* **The select flow is one scene with per-slot sub-states**, not five scenes:
  `FUN_00409340` (scene 3, `param_1+0x3c90+slot*4` = per-slot state) and
  `FUN_00406850` (scene 5, `param_1+0x2e98+slot*4`) are the two implementations.
  Screens 3–8 of the table above are states of one screen.

### 1.3 What a 1P-vs-COM and a 2P match actually need

For **1P vs COM** and **2P** the click path is:

```
Boot → Opening (stub) → TITLE → SELECT page 0 (team → character → weapon
     → hypermode → PLAYER/COM → ready) → SELECT page 1 (stage + 5 settings)
     → VS INTRO → BATTLE → RESULT (sting → quote → report) → SELECT page 0
```

Required screens: **title, select page 0, select page 1, VS intro, battle
(already built), result**. Optional / deferrable:

| screen | 1P vs COM | 2P | verdict |
|---|---|---|---|
| options (scene 6) | no | no | needed for volume; defer the toon/shadow toggles |
| key config (scene 7) | no | no | binding reference is already encoded in `input/input.h`; screen is a luxury |
| netplay menu/lobby (11/12) | no | no | deferred (D6 → netplay track) |
| soft keyboard (13) | no | no | needed only when player names are editable — schedule as a widget, host screen deferred |
| opening (0) / prologue (4) | no | no | stub, already exists |
| story ADV (8), story select (5), scenes 14–19 | no | no | story mode, out of focus (D6) |
| game over (20) / staff roll (21) | yes (20) | yes (20) | game over is reachable from the battle (`return 0x14`); staff roll is story-end only |

### 1.4 Screen inventory, the implementation view

23 prints → **14 distinct screens** (the duplicates are states of one screen):
title; opening; prologue; select (6 panel states); stage+battle settings; key
config; options; VS intro; battle (the HUD, stamina and ammo prints plus the KO
beat are one screen); result (3 beats); netplay menu; netplay lobby; soft
keyboard; story select.

RE coverage of those 14: **12 have a located draw function with coordinates read**
(title, opening, prologue, select, stage+settings, key config, options, VS intro,
battle, netplay menu, netplay lobby, story select), **1 is mixed** (result:
victory and quote located, the report's composition is not), and **1 is partial**
(soft keyboard: host scene and grid assets located, the widget function was not
isolated). Per-print accounting is in §2.18.

---

## 2. RE evidence per screen

### 2.0 The shared machinery

Everything below uses these; they are the real API of the original front end.

**Frame contract.** update = vtable slot 3, returns the next scene id; draw =
vtable slot 1; slot 0 = destructor; slot 2 = a shared `ret` stub (0x691c40).
Evidence: `FUN_00657ef0.c:36-47`, and every scene vtable in `.rdata`
(e.g. scene 3 at 0x6a1974, scene 5 at 0x6a16b4, scene 1 at 0x6a1bdc).

**Draw guard.** All draw functions begin with `FUN_00650f40()` / `FUN_00650f70()`
and wrap the sprite calls in `FUN_00650fd0()`; scene 3's draw also sets two
D3D render states through `DAT_006d16f8` (`FUN_0040b1f0.c:12-19`).

**Sprite primitives** (sprite object in ECX, so the decompiler shows the call
without it):

| function | meaning | evidence |
|---|---|---|
| `FUN_006560c0(path)` | load an image into a sprite object | `FUN_00410d60.c:28-33` |
| `FUN_006556c0(spr,srcX,srcY,cellW,cellH,dstW,dstH)` | single-cell atlas, destination size | `FUN_006556c0.c:13-38` |
| `FUN_00655b20(spr,srcX,srcY,cellW,cellH,…)` | region + cell grid (UV step = cell/tex) | `FUN_00655b20.c:13-45` |
| `FUN_00655af0(spr,x,y,w,h)` | `FUN_00655b20` with zero pivot — full-screen images | `FUN_00410d60.c:34` |
| `FUN_00655830(spr,x,y,cellX,cellY)` | draw cell (cellX,cellY) at (x,y) | `FUN_00655830.c:15-35` |
| `FUN_00655d60(spr,x,y)` | draw the configured quad at (x,y) | `FUN_00655d60.c:15-38` |
| `FUN_004082f0(spr,rgba)` | tint (writes the four vertex colours) | `FUN_004082f0.c:6-12` |
| `FUN_00408250(spr,f)` | scale factor (sprite+0x84/0x88 = fields [0x21],[0x22]) | `FUN_00408250.c:6-10` |
| `FUN_00431b20(v,x,y,scale,mode)` | draw the decimal number `v` from the digit atlas | BATTLE-HUD-SPEC.md §1 |
| `FUN_00431ce0(x,y,scale,cell,?)` | draw one cell (`%`, `∞`, unit glyphs) | used at `FUN_0040cd00.c:50-59` |
| `FUN_00431a50`/`FUN_00431b50` | text/number helpers shared with the HUD | BATTLE-HUD-SPEC.md §1 |

**Input.** Per-slot input structs at `DAT_006cae94`, stride 0x19 dwords
(100 bytes), one per player slot; fields observed:

| field | meaning | evidence |
|---|---|---|
| `[0]` | left/right (−1/0/+1) | `LoadNextScene.c:51-58` |
| `[1]` | up/down (−1/0/+1) | `LoadNextScene.c:59-66` |
| `[2]` | 決定 / confirm (edge) | `FUN_00406850_loadnextcallee.c:120`, `FUN_00409340.c:114` |
| `[3]` | 戻る / cancel (edge) | `FUN_00406850_loadnextcallee.c:140`, `FUN_00409340.c:100` |
| `[5]` | a per-slot restriction flag (story mode) | `FUN_00406850_loadnextcallee.c:81` |
| `[8]` | a second confirm button on the select screen | `FUN_00409340.c:128` |

`FUN_00403aa0(v)` is the "is positive / absolute" helper used to test a
direction; `FUN_0064aed0(n)` plays a system SE (0 = 決定, 1 = 戻る,
2 = cursor move, 3 = lock/ready). DirectInput scancodes are tested directly with
`FUN_006586d0(code)`: 0x1c Enter, 0x39 Space, 0xc8/0xd0 arrows up/down,
0xcb/0xcd left/right, 0x38/0xb8 Alt — and 0x1c + Alt calls `FUN_0064ad70()`
(Alt+Enter fullscreen), in every menu (`FUN_00410f60.c:17-21`,
`FUN_004090a0.c:18-22`).

**Menus accept the pad too**: the title update merges all four slots' input
into four counters (`FUN_00410f60.c:81-100`) so a pad confirm works from any
slot. The remake's `input/input.h` already encodes the 13-action layout
(`Jump` doubles as menu confirm — `remake/foundation/src/input/input.h:28`).

---

### 2.1 `title-menu.webp` — the main menu (scene 1)

* **What it is**: logo top-centre, shrine-approach background, six Japanese
  items; the highlighted item is the white variant.
* **Draw**: `FUN_004114f0` (scene 1 vtable slot 1, vtable 0x6a1bdc). It returns
  1 and draws the three sprites configured in the constructor.
* **Assets and geometry**: `FUN_00410d60.c:28-36`
  - `data/title/back00.bmp` → `FUN_00655af0(spr,0,0,800,600)` (full-frame);
  - `data/title/logo.bmp` → `FUN_00655b20(spr,0,0,0x200,300,0x100,0)`;
  - `data/title/title.bmp` → `FUN_006556c0(spr,0,0,0xc0,0x30,0x60,0)`.
  Decoded, `title.cnv` is a 6-row × 2-column sheet of the six items
  (ストーリー / 対戦 / 通信対戦 / 環境設定 / 操作設定 / 終了), one column white
  (selected) and one column dark (unselected), cells 192×48. `logo.cnv` is the
  ひぐらしデイブレイク logo; `back00.cnv` is the shrine approach.
* **Update and input**: `FUN_00410f60.c:101-148`
  - selection index at `+0x1f0`, six items, `(i+1)%6` / `(i+5)%6`
    (`:138-145`), cursor SE `FUN_0064aed0(2)`;
  - the vertical counter is `+0x1f8` (accumulated from arrows/keys, `:32-65`);
  - confirm is `+0x1fc == 1` (`:101`), SE `FUN_0064aed0(0)`;
  - the item switch (`:106-134`) returns the next scene id as in §1.2.
* **Text strategy**: **atlas art**. No `FUN_00656190` call and no font creation
  anywhere in scene 1's functions (the five `ＭＳ ゴシック` sites are listed in
  §4.2); the six labels are pixels in `data/title/title.cnv`.
* **Bundle**: `daybreak00.dat` (back00/logo/title are also in `daybreak04.dat`;
  00 wins).
* **Gaps**: the exact anchor/stride of the six item cells is set inside
  `FUN_004114f0`, which I read but did not transcribe line by line; print
  measurement (§6.3) is the cheap way to land it.

### 2.2 `opening-frame-01.webp` — OP movie (scene 0), prologue (scene 4)

* **What it is**: `movie/op.mpg` letterboxed (the bars are in the video, per the
  reference README's note). Scene 4 is `movie/prologue.mpg` (the ストーリー
  entry).
* **Draw**: `FUN_004051b0` (scene 0) and `FUN_00405750` (scene 4) — the shared
  movie blit pair; `FUN_00404eb0` loads `movie/op.mpg`, `FUN_00405520` loads
  `movie/prologue.mpg`, and `FUN_00404ff0` selects the BGM
  (`data/bgm/title.ogg` / `data/bgm/titlesemi.ogg`).
* **Update**: `FUN_00404ff0` returns 0 (stay) or 1 (title) — skip/end;
  `FUN_00405650` returns 5 after the prologue.
* **Text strategy**: n/a (video).
* **Verdict for the plan**: **stub** — the existing `VideoPlayer` is enough.
* **Bundle**: `movie/*.mpg` are **bundle-only** (`daybreak02.dat`), which is why
  the extracted tree has no `data/movie` equivalent (ASSET-CATALOG §0.1).

### 2.3 `team-select.webp` — the select screen, team panels (scene 3 page 0)

* **What it is**: the shared select background; four diamond panels, one per
  player slot (0/2 = 青組, 1/3 = 赤組), each showing the team kanji until a
  character is chosen; the chibi roster grid in the middle; 決定 / 戻る at the
  bottom; a red outline cursor on the focused panel.
* **Draw**: `FUN_0040b2b0` (478 lines, scene 3 page-0 draw), dispatched from
  `FUN_0040b1f0.c:14-20` (`if (scene+0x3c41 == 0) FUN_0040b2b0(); else
  FUN_0040cd00();`).
* **Player-slot geometry**: `FUN_0040b2b0.c:35-58` anchors each of the four
  slots at `((slot/2)*400 + 200, (slot%2)*300 + 300)` and **mirrors** the x = 600
  column with `FUN_0040da60(±1.0, 1.0)` (`:52-56`) — the blue and red diamonds
  are two art cells reused four times, two of them flipped.
  **Measured on the print** (`team-select.webp`, 801×604; blue/red fill masks,
  3-px sampling): the four diamond fills sit at
  TL blue x 0–399 y 3–294 · TR red x 400–787 y 9–300 ·
  BL blue x 6–399 y 302–593 · BR red x 400–790 y 305–590, i.e. centres
  ≈ (200,150) / (595,150) / (200,450) / (595,450). The code's x anchors match
  those centres exactly (200 and 600); the y anchors read from the code (300 and
  600) are consistently **150 px below** the measured centres, which is a pivot
  or quadrant-origin difference to reconcile before coding — this is the one
  piece of geometry in this document that is not yet nailed (§7).
* **Panels**: `data/select/bg00.cnv` decodes to exactly the print's four
  diamonds (blue, red / blue, red with 青組/赤組 kanji). `data/select/bg01.cnv`
  is the diamond *window mask* over the sky/ground photo; `data/select/sbg00.cnv`
  is the stage-select page background (§2.9).
* **Assets loaded by the constructor**: `FUN_00408330.c:72-142` —
  `bg00`, `bg01`, `sbg00` (`:72-76`, each set to 800×600 at `:100-102`),
  `p00`…`p03` (UI frames, headers, names, 決定/戻る, `:78-82`, cell configs
  `:106-125`), `pbg00`…`pbg02` (combo help / stage thumbnails / stage names,
  `:84-88`), `s1p`…`s4p` (the 1P–4P tags, `:92-98`, 400×300 cells at
  `:103-105`), `%02d` ×16 (portraits, 256×256 → 128×256, `:126-131`),
  `i%02d` ×16 (chibi grids, 80×128 cells → 40×80, `:132-136`), `cos%02d` ×16
  (costume icons, `:137-140`), plus `data/bgm/select01.ogg`. Per-slot state
  words are initialised at `:143-154` (`+0x3d08` character and `+0x3d28` mode
  start at −1 = unset).
  **Case trap**: the code spells these `data/select/p01.bmp` / `p02.bmp` in
  lowercase; the shipped files are `P01.cnv` / `P02.cnv`. The original's loader
  is case-insensitive (ASSET-CATALOG §7 trap 20) and ours must be too.
* **Input**: page-0 dispatch `FUN_004090a0.c:47-59` loops all four slots through
  `FUN_00409340(slot)`; `DAT_006caeb8 == 1` (a global "any slot confirmed")
  gates the page advance.
* **Text strategy**: **atlas art** — 青組/赤組 are cells of `data/select/bg00.cnv`;
  決定/戻る and the numeric glyphs of `data/select/P01.cnv`; the
  CHARACTER/WEAPON/COSTUME/HYPERMODE/CONTROLLER/STAGE SELECT headers and the
  arrows of `data/select/p00.cnv`; the 16 character names of
  `data/select/p03.cnv`. No font is created in scene 3 (`FUN_00408330`,
  `FUN_004090a0`, `FUN_00409340`, `FUN_0040b2b0`, `FUN_0040cd00`, `FUN_0040d130`
  contain no `FUN_00656190`/`FUN_0065d870` call — §4.2).
* **Bundle**: `daybreak00.dat`.
* **Gaps**: the panel-level anchor table (which cell of `bg00`/`p0x` goes to
  which corner, and the cursor outline cells) is inside `FUN_0040b2b0`, which I
  read in part; the mirror trick above plus print measurement pins it.

### 2.4 `char-select-rena.webp` — character select (scene 3 page 0, state 0→2)

* **What it is**: as above, but the focused slot's panel has become the chosen
  character's portrait + nameplate (竜宮レナ) and the small red cell cursor sits
  on the chibi; hovering a chibi plays its animation.
* **Per-slot state machine**: `FUN_00409340` (587 lines) —
  `param_1+0x3c90+slot*4` = state:
  - `switch` at `:45`; **state 0** = character picking. Confirm
    (`local_c[2] == 1`, `:114`) claims the slot
    (`0x3c80[local_8*4] = param_2`) and sets `0x3c90[slot] = 2`.
  - **state 2** (`:301-331`): if the character is still unset
    (`0x3d08[slot] < 0`) it is randomised (`rand % 0x10`), with the weapon
    (`rand % 3`, or `% 2` for the two-weapon characters, `:307-313`), then
    `FUN_0040d700(slot, charIdx)` (`:323`) loads that character's weapon atlas,
    then the state becomes 4 or 3 (`:316-320`).
  - Cancel (`local_c[3] == 1`, `:100`) clears character/costume/hypermode for
    the slot and returns the panel to the team state.
  - Entry voice: `FUN_00649770(charIdx)` feeds
    `data/voice/entry/%s.wav` (`FUN_00409340.c:187-214`, which also covers the
    `%sB`, `%s_C%02d`, `%s_B%02d`, `%sB_B%02d` variants; the parallel scene 5
    implementation is `FUN_00406850_loadnextcallee.c:132-138`).
* **Chibi grid**: the 16 per-character grids are drawn as sprites; each
  `iNN.cnv` decodes to a 256×256 sheet of six 80×128 chibi cells (3 columns ×
  2 rows), configured `FUN_006556c0(spr,0,0,0x50,0x80,0x28,0x50)`
  (`FUN_00408330.c:132-136`) = 80×128 source drawn at 40×80. The **roster
  positions** of those 16 cells inside `FUN_0040b2b0` are the one piece of this
  screen not yet transcribed (§7); scene 5's `FUN_004072b0` has the analogous
  grid formula for its own 14-slot table and is a useful template, but the
  tables differ (§2.17).
* **Chibi cell selection / animation**: cells are picked from a frame counter
  (`FUN_004072b0.c:56-58` in the scene-5 twin: `(frames%0x28)/10` → `(n+1)%3`
  and `(n+1)/3`), i.e. the hover animation is a 3-cell cycle of the same sheet.
* **Text strategy**: **atlas art** (nameplate = a cell of `data/select/p03.cnv`,
  which decodes to the 16 character names in roster order — which also
  cross-validates the character index table in
  `remake/docs/ASSET-CATALOG.md` §"char_index"; p03's order is 竜宮レナ,
  園崎魅音, 前原圭一, 北条沙都子, 古手梨花, 園崎詩音, 富竹ジロウ, 鷹野三四,
  大石蔵人, 赤坂衛, 入江京介, 知恵留美子, 葛西辰由, 園崎茜, 羽入, 公由夏美).

### 2.5 `weapon-select-rena.webp` — weapon/costume select (state 3 of `FUN_00409340`)

* **What it is**: WEAPON SELECT header, weapon list with △▽, flavour text over
  the portrait, the chibi costume updating live.
* **Weapon text atlas**: `FUN_0040d700.c:13-20` —
  `wsprintfA("data/select/w%02d.bmp", charIdx)` then
  `FUN_006556c0(spr,0,0,0x100,0x40,0x80,0x20)`: a 512×512 sheet of 256×64 cells,
  drawn at 128×32. Decoded, `w00.cnv` holds **three weapons' name/type/description
  blocks** (愛用の鉈 / ナタ系の武器 / レナの武器 + description in the right
  column) — the print's flavour text is these pixels.
* **Navigation**: up/down changes the weapon; left/right changes the costume.
  The costume cycle bound is the byte table `DAT_006b71c0`
  (`FUN_00406850_loadnextcallee.c:218-231`), read as "shipped costume
  directories − 1"; my dump of the table is
  `[5,5,3,5,5,5,2,4,2,2,3,3,1,2,4,5]` for character indices 0…15 (matching
  ASSET-CATALOG §2.6, including its off-by-one caveat).
* **Text strategy**: **atlas art** (the weapon names/descriptions are pixels in
  `wNN.cnv`).
* **Gaps**: which `wNN` cell index maps to which weapon line (the code draws
  cells of a 2-column sheet) was not transcribed; the atlas content is
  unambiguous, the indices are one read of `FUN_00409340`'s draw path away.

### 2.6 `hypermode-select.webp` — hypermode select (state 4)

* **What it is**: HYPERMODE SELECT header, the three modes with name and
  description (恐怖のオヤシロモード / 友情のタッグモード / 機嫌のカケラモード).
* **Where the art is**: `data/select/P01.cnv` decodes to the three mode
  **names** (plus 戦闘開始, 準備完了！, the digit strip, `%`, `∞`,
  制限時間/体力値/ゲージ増加量, 決定/戻る, ON/OFF) and `data/select/P02.cnv` to
  the three mode **descriptions** (plus 青/赤チーム風船サイズ, 1P–4P, com,
  RANDAM, the three PLAYER variants, 今日の主役). Both are the shared UI atlas
  pair, loaded by both select scenes as `data/select/p01.bmp` / `p02.bmp`
  (`FUN_00408330.c:80-82`, `FUN_004057c0.c:68-75`) — see the case trap in §2.3.
* **State**: scene 5's draw shows the panel grammar in `FUN_004072b0.c:201-228`
  — a three-item picker (`(0x2e30[slot] + i) % 3`, three rows 20 px apart) with
  a header cell and a selected-cell draw. The mode value is stored to
  `0x2e70[slot]`, which `LoadNextScene.c:104-105` copies into
  `DAT_006cfb48[slot]`, and `FUN_0040d130.c:81` writes it as `rand % 3` for
  auto-filled slots.
* **Text strategy**: **atlas art**.
* **Gaps**: the mode-name cells' (cellX,cellY) and the panel's anchor set are in
  the draw function but were not transcribed; the atlas identity is certain.

### 2.7 `controller-select.webp` — PLAYER / COM per slot (state 1)

* **What it is**: CONTROLLER SELECT header, PLAYER/COM toggle with △▽, and a
  summary of the slot's character / weapon / mode.
* **State and input**: `FUN_00406850_loadnextcallee.c:110-149` — a **two-item**
  cycle (`(0x2e30[slot] + 2 + dy) & 1`, `:114-118`), confirm writes
  `0x2e40[slot]` (`:123-127`) — that value is **4 for COM** and the slot index
  for a human, which is exactly the `DAT_006cfaf8 == 4` "unset = COM" convention
  the battle side reads (`LoadNextScene.c:108-121`), and it plays the entry voice
  (`:132-138`).
* **Draw**: `FUN_004072b0.c:174-200` — the summary panel draws a header cell and
  two state cells at `(610, slot*300+110)` and `(610, slot*300+130)`, i.e. the
  PLAYER/com pair from `data/select/P02.cnv`; the full slot summary (character
  portrait, weapon line, mode line) is `FUN_004072b0.c:91-234` at x = 730/610.
* **Text strategy**: **atlas art**.
* **1P/2P tags**: `FUN_004072b0.c:235-242` draws `data/select/s1p.cnv` at
  (336,550) and `s2p.cnv` at (464,550) — the 1P/2P badges of the prints.

### 2.8 `ready-confirm.webp` — slot locked

* **What it is**: the 準備完了！ stamp and the player tag over the portrait, with
  決定 highlighted.
* **State 8**: `FUN_00406850_loadnextcallee.c:205-213` — a counter at
  `0x2eac+slot*4` is initialised to 4.0 (`:130`) and decays by 0.2 per frame
  (`:212`); when it reaches 1.0 the slot unlocks (`0x2e98[slot] = 0`,
  `0x2e90[slot] = -1`) and SE 3 plays.
* **Cancel semantics** (the print's note "X deselects back to character pick"):
  `case 3` (`:165-175`) and `case 4` (`:198-203`) both restore the previous
  panel state and clear the slot's `0x2e40/0x2e60/0x2e90` fields — cancel is
  slot-contextual, exactly as the reference README records.
* **Art**: the 準備完了！ cells live in `data/select/P01.cnv` (decoded), the
  1P/2P tags in `s1p/s2p.cnv`.
* **Text strategy**: **atlas art**.

### 2.9 `stage-select-random.webp` / `stage-select-school.webp` — page 1

These two prints are one screen: the second page of scene 3.

* **Page switch**: `FUN_004090a0.c:33-43` — `0x3c40` = current page, `0x3c41` =
  previous, `0x3c42` = a page-transition fade byte stepping by 0x0f. Page 0
  draws `FUN_0040b2b0`, page 1 draws `FUN_0040cd00`
  (`FUN_0040b1f0.c:14-20`). Confirm on page 1 returns **9** = VS intro
  (`FUN_004090a0.c:65-68`); 戻る returns 1 = title (`:70-76`).
* **Row input**: `FUN_0040acb0.c:36-120` — the focused row is
  `scene+0x3c78`, **8 rows**, `(row + 8 + dy) % 8` (`:105-110`); left/right
  edits the focused row (`*piVar3 = ±1`); the 戦闘開始/戻る row 7 toggles
  `0x3c7c` and confirm either starts (`0x3c44 = 1`) or goes back to page 0
  (`:120+`).
* **The five battle settings and their exact domains** (all from
  `FUN_0040acb0.c:44-104`; the globals are in `.data`):

| row | label (art) | global | step | range | wrap |
|---|---|---|---|---|---|
| 0 | stage (pbg02 names) | `scene+0x3d48` | ±1, `% 7` | 7 entries, **0 = ランダム** | cyclic |
| 1 | variation (昼/夕方/夜) | `scene+0x3d4c` | ±1 | `% 2` by default; `% (count + 2)` where the count byte is at `scene+0x3d90` (one of the per-slot dword arrays initialised in `FUN_00408330.c:143-154`) when `stage == 1` | cyclic |
| 2 | 制限時間 | `DAT_006cf3c0` | 60 | 0,60,120,180,240 (`% 300`) | **0 = ∞** |
| 3 | 体力値 | `DAT_006cf3b8` | 25 | 50…200 (clamp `:62-68`) | wraps 50↔200 |
| 4 | ゲージ増加量 | `DAT_006cf3bc` | 25 | 50…200 (`:69-75`) | wraps |
| 5 | 青チーム風船サイズ | `DAT_006cf3b0` | 20 | 40…200 (`:76-82`) | wraps |
| 6 | 赤チーム風船サイズ | `DAT_006cf3b4` | 20 | 40…200 (`:83-89`) | wraps |
| 7 | 戦闘開始 / 戻る | `scene+0x3c7c` | toggle | 0 = start, 1 = back | — |

  This is the complete answer to the reference README's "Range/step TODO"
  entries: HP and gauge move in 25 % steps over 50–200 %, the balloon sizes in
  20 % steps over 40–200 %, the time limit in 60 s steps with 0 = ∞.
* **Draw, with coordinates** (`FUN_0040cd00.c:13-60`; every value below is the
  float constant in the code, converted):
  - **stage name** cell `(0, stage)` at (175, 125); **variation** cell
    `(0, var+1)` at (175, 175) — drawn only when `stage != 0`
    (`:17-20`);
  - **stage thumbnail** at (575, 150): cell `(0, 9)` for ランダム (`stage == 0`),
    else `((stage−1)/3, ((stage−1)%3)*3 + var)` (`:21-27`).
    `data/select/pbg01.cnv` decodes to that thumbnail sheet **including the `?`
    cell** used by the ランダム case;
  - **row labels** at x = 175, y = 275, 325, 375, 425, 475, cells `(row−2)`
    chosen from two sprites (the second continues at cell 0/1 — `:28-32`), with
    `cellX = (row != focused)` as the **focus highlight**;
  - **numeric readouts** at x = 600, y = 255 (制限時間), 305 (体力値),
    355 (ゲージ増加量), 405 (青), 455 (赤) via
    `FUN_00431b20(value, x, y, 1.0, 0)`, each followed by the `%` glyph
    `FUN_00431ce0(x, y, 1.0, 5, 1)`; when `DAT_006cf3c0 == 0` the time row draws
    the `∞` cell 6 at (550, 255) instead (`:33-53`, the `∞`/`%` cells are in
    `data/select/P01.cnv`);
  - **決定** at (275, 550) and **戻る** at (525, 550), cellY from the row-7
    toggle (`:35-43`);
  - `data/select/sbg00.cnv` is the page background and **already contains the
    `STAGE SELECT` and `BATTLE SETTING` headers** (decoded — those two headers
    need no separate draw);
  - `DAT_006cfdb0 != 0` (netplay) additionally positions a text window
    (`FUN_00646870(100.0)`, `FUN_00646500(208, 520)`, `FUN_0040cd00.c:55-58`).
* **Text strategy**: **atlas art** for every label; the numbers are drawn from
  the digit strip in `data/select/P01.cnv` through `FUN_00431b20`. No font in
  this path (§4.2).
* **Bundle**: `daybreak00.dat` (`sbg00`, `pbg01`, `pbg02`, `P01`, `P02`).

### 2.10 `controller-setup.webp` — 操作設定 (scene 7)

* **What it is**: five pages (`data/keyconfig/0000..0004`, the constructor loops
  `0..4`: `FUN_00403eb0.c:33-34`) showing the binding table: 1P keyboard on the
  left, pads 2–4 on the right.
* **Draw**: `FUN_00404a50.c:22-60` — the binding grid is drawn at
  `x = 272 + 64 + col*64`, `y = 128 + row*32` (8 columns), with cells selected
  from the page atlas; the two `FUN_00655d60` calls at `:23`/`:60` bracket it.
* **Update**: `FUN_00404220` (returns 7 or 1).
* **Text strategy**: **atlas art** — the page images carry the key names; no
  font and no text call in scene 7's functions.
* **Bundle**: `daybreak00.dat`.
* **Gaps**: the page-index state field and the exact cell indices per row were
  not transcribed; the grid geometry above is read from the draw.

### 2.11 `option-screen.webp` — 描画と音量の設定 (scene 6)

* **What it is**: three pages (`data/config/0001..0003`,
  `FUN_00402890.c:33-34`) with four toggles and four volume sliders plus 終了.
* **Draw**: `FUN_00403470.c:16-53` — **nine rows** at x = 176 (labels) and
  x = 368/464 (ON/OFF columns), y = 128, 160, 192, 224, 256, 272, 288, 304, 320;
  the cursor arrow is drawn at x = 145 with cell `(row > 2) + row`
  (`:33-34`).
* **The settings and their globals** (`FUN_00403470.c:25-53`):

| element | global | values |
|---|---|---|
| toggle 1 (toon rendering) | `DAT_006cfcec` | on/off cells |
| toggle 2 (shadows) | `DAT_006cfcea` | on/off |
| toggle 3 (texture res) | `DAT_006cfceb` | on/off |
| toggle 4 (window/fullscreen) | `DAT_006cfced` | on/off |
| master volume | `scene+0x3ec` (u16) | slider fill `(v−60)/40*160 + 368` |
| music volume | `DAT_006cfcf4` | same formula |
| voice volume | `DAT_006cfcfc` | same formula |
| SFX volume | `DAT_006cfcf8` | same formula |

  The slider track is 160 px wide starting at x = 368 and saturates below 60
  (`FUN_00403470.c:36-53`) — the print's 0 %…100 % end labels are baked into
  `data/config/0001.cnv`.
* **Update**: `FUN_00402be0` (page state + row/column editing; returns 1 on
  back).
* **Text strategy**: **atlas art** (row labels are the page image; ON/OFF and
  the slider ends are page art).
* **Bundle**: `daybreak00.dat`.

### 2.12 `vs-intro.webp` — VS sting (scene 9)

* **What it is**: portraits slide in from the sides, stop, and the animated VS
  fires in the centre; skippable into the battle.
* **Draw**: `FUN_00411cb0` (103 lines):
  - two full-width bands, `FUN_00655f70(0,0,800,300)` (blue team) and
    `FUN_00655f70(0,300,800,600)` (red team) at `:21-22`;
  - four portraits at (150,200), (200,250), (600,350), (650,400) — versus path,
    `:28-50` — each cell picked from an 8-column sheet as
    `(charIndex/8, charIndex%8)`; the story path (`DAT_006cfdb0 != 0`) draws two
    instead, at y = 160 and 240;
  - the four **player names** under the portraits through the cell-string
    drawer `FUN_00646bd0` at (50,180), (100,260), (500,370), (550,450)
    (`:75-84`) — see §4.2: names are atlas cells, not text;
  - assets: `data/vs/vs01..03.bmp` + `data/select/%02d.bmp` + `p03.bmp`
    (`FUN_004115f0.c:28-33`); `vs03.cnv` decodes to the VS logo art.
* **Update**: `FUN_00411ae0.c:11-51`
  - the four slide offsets (`+0x5d0…+0x5dc`) decay by 30/20 px per frame to 0
    (`:12-21`);
  - `data/bgm/vs.ogg` starts at frame 0 (`:35-37`);
  - after 0x5a (90) frames the VS animation alpha steps down
    (`+0x5e0 -= 0.25`, `:28-31`) and at ≤1.0 the scene sets `+0x5cc = 1`
    (`:24-27`);
  - then it loads the stage — `FUN_006492f0()` (story, `DAT_006cfce9 == 1`) or
    `FUN_00648ad0()` (versus) (`:40-45`) — and **returns 10**, the battle.
* **Text strategy**: none (all art).
* **Bundle**: `daybreak00.dat` (art), `daybreak05.dat` (`vs.ogg`).
* **Note for the plan**: this is the cheapest bridge screen — 51 lines of update
  logic, fully read, and it is what turns "menus" into "the battle we already
  have".

### 2.13 `battle-hud.webp` / `battle-stamina.webp` / `ammo-bar.webp`

Already specified at spec quality in `remake/foundation/docs/BATTLE-HUD-SPEC.md`
(§1 draw path table: `FUN_006396f0`, `FUN_0063a130`, `FUN_00643230`,
`FUN_00644150`, `FUN_00642510`; the full 19-float anchor table at
0x6a4c90–0x6a4cd8; the print offset convention). This plan does not repeat it;
it only records that **these three prints are one screen** (the battle), that
`ammo-bar` is the MAIN counter's proportional fill (`FUN_00645250` clipping,
per the same document), and that `battle-stamina` confirms the contextual
STAMINA bar and the ally overhead grammar.

### 2.14 `ko-moment.webp` — 撃破！ sting

* **Art located**: `FUN_00633ca0` loads `data/object/system.bmp`,
  `P04`, `P05`, `P08`, `P09` (plus `data/trail/%02d.bmp`,
  `data/aura/%02d.x`, 勝利バー) — evidence: the string block at `.rdata`
  0x6a492a–0x6a49b0 is referenced from `FUN_00633ca0` (the 勝利バー reference is
  at `.text` 0x633cf1). `P09.cnv` decodes to the `3 2 1` countdown and the
  `撃破！` sting, so the KO presentation's art and the match countdown are the
  same atlas.
* **Text strategy**: art (the 撃破！ glyphs are pixels, and
  `remake/foundation/docs/CJK-TEXT.md` §2 already records this).
* **Gaps**: the trigger/draw call sequence for the sting inside the battle frame
  renderer was **not read**; the presentation itself is documented in the
  reference README (sting → inflate → `+N%` readout → respawn).

### 2.15 `result-victory.webp` / `result-quote.webp` / `result-report.webp`

One sequence, owned by the battle module (not by the scene factory).

* **Victory sting**: `FUN_00633ca0` also loads `data/object/P05` (青組 大勝利)
  and `P08` (赤組 大勝利) — corresponding to the two-layer team-name-then-phrase
  animation the reference README describes for the sting.
* **Result sequence**: `FUN_00635d40` (536 lines) with
  *an outer phase* at `battle+0x4a3c` (cases 1…5, `:60`) and
  *an inner sub-phase* at `battle+0x41e0` (cases 0…5, `:247`):
  - `:266-271` loads `data/win/%02da.bmp` / `%02db.bmp` — the winner's art
    (per character; `win/00a.cnv` decodes to Rena's victory pose);
  - `:323` loads `data/scenario/win/%02d-%02d-%d.txt` and `:346`
    `data/scenario/win/%02d.txt` — **the quote text**, e.g.
    `scenario/win/00-00-1.txt` = 「\cFFCCAAなぜか反撃なかった。\nなんでだろ、だろ？」;
  - `:355` loads `data/voice/win/%s` for the spoken line;
  - `:362`/`:388` build a texture from the string with `FUN_00656190(...)` —
    i.e. **GDI text** (the `ＭＳ ゴシック` font is created in this block, at
    `.text` 0x6343fb inside `FUN_00633ca0`, +0x75b);
  - `:414`, `:430`, `:452`, `:506` read per-player confirm
    (`(&DAT_006cae9c)[slot*0x19 + player]`), which is the "Z advances" beat;
  - `:377-391` award the session titles into `DAT_006cfdf1` /
    `DAT_006cfdd1`.
* **Activity report**: the header 本日の活動報告 and the 1P/2P/3P/4P/com badges
  are art in `data/object/system.cnv` (decoded), the **earned titles are exe
  strings** — 30 Shift-JIS literals at `.rdata` 0x6a2584–0x6a27e0
  (容赦ないひぐらし / 美しいひぐらし / 最終兵器ひぐらし / 一匹狼 / ニュータイプ /
  弾幕はパワー / ひぐらしマスター / Ｌ５患者 / … / 罰ゲーム決定), implemented as
  small title classes (`FUN_0042f6a0`, `FUN_0042f8e0`, `FUN_0042fce0`,
  `FUN_0042fe20`, … with vtables 0x6a2510/0x6a2520/0x6a2574) and consumed
  through the stat system (`FUN_0042e9a0`, `FUN_0042ea20`, called from
  `FUN_00647c10`/`FUN_00647d60`).
* **Text strategy**: **both** — chrome/tags are atlas art, the quote body and
  the title strings are GDI text (`FUN_00656190` with the font created in
  `FUN_00633ca0`). This is the screen that needs the CJK layer first.
* **Bundle**: `daybreak00.dat` (win art, system.cnv, scenario text),
  `daybreak05.dat` (win/lose BGM).
* **Gaps**: the report's own draw function was **not isolated** — the data path
  (titles, `DAT_006cfdd1`, `DAT_006cfdf1`, the confirm handling) is RE'd, the
  composition is not. Plan for it as a small layout job measured from the print
  (`result-report.webp`, 798×601).

### 2.16 `netplay-menu.webp` / `netplay-lobby.webp` / `soft-keyboard.webp` — deferred (D6)

Specified here so the netplay track does not have to re-derive them.

* **Menu (scene 11)** — ctor `FUN_00412110` (object 0x18bc) also **creates the
  MS Gothic font** at `.text` 0x41253c (+0x42c), update `FUN_00412ac0` (returns
  0x0c = lobby, 0x0d = name/IP, 0x0b = itself, 1 = title; formats the IP with
  `"%d.%d.%d.%d"`), draw `FUN_00413bb0` (164 lines; the menu cells at (400,300)
  and the rest from `data/network/menu.cnv`). Assets: `network/nback00`,
  `nback01`, `menu`, `menu2`, `nameMenu`, `number`, `chat/name_p1`, `name_p2`.
  Decoded: `menu.cnv` = the item text (サーバーを立てる / サーバーに接続する /
  〈IPで指定〉/〈一覧から選択〉/ 名前設定 / ディレイ設定 / ポート設定 /
  チャット設定 + OFF/ON), `menu2.cnv` = the per-item description text,
  `nback01.cnv` = the 通信対戦 background, `nback00.cnv` = the shrine background.
  **So the netplay menu's labels are art; only the font it creates is for chat
  and entered text.**
* **Lobby (scene 12)** — ctor `FUN_00414750`, update `FUN_00414d30` (returns
  0b), draw `FUN_004151f0.c:25-60`: up to 8 member rows, each a **name drawn as
  cells** by `FUN_00646bd0(i, 40, i*48 + 112, state)` (`:29-33`) plus a
  selection cell at x = −2 with rows `i*48 + 112`; the CHAT and GUIDELINE box
  markers at (702,112) and (702,336) (`:41-45`); the local player's toggle cells
  at (304,412) and (304,444) (`:53-60`). `nback02.cnv` decodes to the room
  chrome: 部活メンバー募集中, the member lines, the CHAT box, the GUIDELINE box
  (`募集人数 8 / チーム編成 固定 / 戦闘参加メンバー 固定 / 戦闘中チャット OFF`)
  and the hint bar. **Chat message text is GDI**: the chat system `FUN_00645840`
  creates two fonts (`.text` 0x645956, 0x6459eb) and
  `FUN_00645e10`/`FUN_00646110`/`FUN_006463c0`/`FUN_00646460` are the text-window
  update/draw helpers.
* **Soft keyboard (scene 13)** — ctor `FUN_00419f10` (loads `network/nback02`,
  `number`, `menu`, `object`), update `FUN_0041a260`, draw `FUN_0041a5a0`
  (near-identical to the lobby draw).
  **The keyboard *is* the name font**: `data/chat/name_p1.cnv` decodes to the
  full grid in the print — digits/symbols, `A`–`Z`, `a`–`z`, the hiragana rows,
  the katakana rows and the punctuation row — and the grid is what the print
  `soft-keyboard.webp` shows, cell for cell. `data/network/nameMenu.cnv` decodes
  to the action bar (Page / 進む / 戻る / 取消 / 決定) and `data/network/number.cnv`
  to the digits `0–9 . + -` plus the 接続中 / 接続に失敗 messages used for IP and
  port entry.
  **Names are stored as grid coordinates, not as a string**:
  `FUN_00646bd0(index, x, y, state)` draws up to **eight** glyph cells from a
  9-byte-per-player record at `object+0xdf6 + index*9` (`FUN_00646bd0.c:14-25`,
  each byte packed as `(cellY << 4) | cellX`), and the per-player name length is
  `DAT_006cfde1[player]`. The same drawer paints names on the VS intro, the
  lobby, the select screen (`FUN_0040b2b0.c:87`, netplay flag) and the battle
  result/HUD (`FUN_0063a740.c:33-48`).
* **Text strategy**: **both, split by content** — chrome, the keyboard grid and
  *all player names* (8 cells each, anywhere they appear) are art; free text
  (chat messages, the entered IP dotted-quad via the `number` digits) is
  GDI/atlas-digit work. A port should draw names as grid cells exactly as the
  original does; only chat needs the text layer.
* **Gaps**: the widget function that owns the grid cursor was not isolated (the
  grid asset and the host scene are identified); the netplay protocol fields
  (port 37564, `addresslist.txt`, delay 3) are in the prints and the reference
  README, and are the netplay track's input.

### 2.17 The story-mode select (scene 5) — not the prints, still worth knowing

`FUN_004057c0` builds a second, 2-slot select scene from
`data/teamselect/bg00`, `teamselect/p00`/`p01`, `teamselect/t00..t09`,
`select/i00..i13` (14 slots, mapped through the byte table `DAT_006b70f0` at
`.data` 0x6b70f0 = `[2,0,4,3,5,1,7,6,8,9,10,11,12,13]`), `select/s1p`/`s2p`, and
loads the portrait/weapon/costume sheets dynamically per chosen character
(`FUN_00408050.c:16-37`). Its `data/teamselect/bg00.cnv` decodes to the four
diamond windows again but over a **green chibi platform** with the 今日の主役
label — visibly a different screen from the prints, which is how scene 3's
`select/bg00` was pinned as the prints' panel art.

Its per-slot state machine (`FUN_00406850_loadnextcallee.c`) is the cleaner
statement of the shared panel grammar and is worth copying:

```
state 0  character select        confirm → 3            (FUN_00406850:28-109)
state 3  WEAPON   (3 items)      confirm → 4, stores 0x2e60  (:151-176)
state 4  HYPERMODE(3 items)      confirm → 1, stores 0x2e70  (:177-204)
state 1  PLAYER/COM (2 items)    confirm → 8, stores 0x2e40  (:110-149)
state 8  ready/lock (0x2eac 4.0 → 1.0, 0.2/frame) → 0        (:205-213)
```

The weapon/mode assignment is proved by the consumers, not by the names:
`0x2e60 → DAT_006cfb38` (weapon: `rand % 3`, `% 2` for the 2-weapon characters —
`FUN_0040d130.c:74-78`) and `0x2e70 → DAT_006cfb48` (mode: `rand % 3`,
`FUN_0040d130.c:81`).

The cursor navigation tables for the chibi grid are the four byte arrays
`DAT_006b7190` (left), `0x6b719c` (right), `0x6b71a8` (up), `0x6b71b4` (down),
indexed by grid slot — read at `LoadNextScene.c:51-66`. The grid's pixel
geometry is `x = DAT_006b7120[slot]*47 + 112`, `y = DAT_006b7158[slot]*34 + 112`
(`FUN_004072b0.c:86-87`), with the dumps
`x-units = [0,1,3,3,2,0,0,1,2,3,2,3,2,1]`,
`y-units = [0,-1,-1,1,2,2,4,5,6,7,8,9,10,11]`.
**These numbers are scene 5's 14-slot grid**; scene 3's 16-cell roster grid has
its own table inside `FUN_0040b2b0` and is not extracted (§7). They are the same
*machinery* (a slot table + a position table + a chibi-cell table), not the same
numbers, so do not carry one over to the other.

**Scenes 14–19** (`FUN_00417a70`, `FUN_0041b980`, `FUN_004193a0`, `FUN_0041d0f0`,
`FUN_00416800`, `FUN_0041aff0`) are story-mode support scenes (scenario/team
data, entry-voice playback, chapter flow). They are **not RE'd here on purpose**
(D6): their ids, ctors and update returns are in §1.2 so the scene table stays
complete, nothing more.

### 2.18 RE coverage summary

| print | draw function located | input read | text verdict |
|---|---|---|---|
| title-menu | yes `FUN_004114f0` | yes | art |
| opening-frame-01 | yes `FUN_004051b0` | yes (skip) | n/a |
| team-select | yes `FUN_0040b2b0` | yes | art |
| char-select-rena | yes `FUN_0040b2b0` + `FUN_00409340` | yes | art |
| weapon-select-rena | yes (`FUN_0040d700` atlas + `FUN_00409340`) | yes | art |
| hypermode-select | yes `FUN_004072b0` (grammar) | yes | art |
| controller-select | yes `FUN_004072b0:174-200` | yes | art |
| ready-confirm | yes (`FUN_00406850:205-213` + `P01`) | yes | art |
| stage-select-random | yes `FUN_0040cd00` | yes | art + digits |
| stage-select-school | yes `FUN_0040cd00` | yes | art + digits |
| controller-setup | yes `FUN_00404a50` | partial | art |
| option-screen | yes `FUN_00403470` | yes | art |
| vs-intro | yes `FUN_00411cb0` | yes | none |
| battle-hud | yes (BATTLE-HUD-SPEC) | yes | art + GDI |
| battle-stamina | yes (same) | yes | art + GDI |
| ammo-bar | yes (fill path) | n/a | art |
| ko-moment | art located (P09), trigger not | partial | art |
| result-victory | yes `FUN_00633ca0` (P05/P08) | n/a | art |
| result-quote | yes `FUN_00635d40` | yes | **GDI** |
| result-report | partial (`FUN_00635d40` + title objects) | yes | **GDI + art** |
| netplay-menu | yes `FUN_00413bb0` | partial | art (labels); digits for IP/port |
| netplay-lobby | yes `FUN_004151f0` | partial | art chrome + **cell names** + **GDI chat** |
| soft-keyboard | host scene yes, widget not | partial | art grid (which doubles as the name font) |

Counts: **20 of 23 prints have a specific draw function cited**; 3 are partial
(ko-moment's trigger, result-report's composition, soft-keyboard's widget).
By screen: 12 of 14 fully located, 1 mixed (result), 1 partial (soft keyboard).

---

## 3. Assets per screen

### 3.1 The atlas map (verified by decoding)

| asset | what it actually is | size/cells |
|---|---|---|
| `data/select/p00.cnv` | the UI **header/verb** sheet: `CHARACTER SELECT`, `WEAPON SELECT`, `COSTUME SELECT`, `HYPERMODE SELECT`, `CONTROLLER SELECT`, `PLAYER SELECT`, `STAGE SELECT`, `BATTLE SETTING`, △▽, coloured button glyphs | 512×512 |
| `data/select/P01.cnv` | hypermode **names**, 戦闘開始, 準備完了！, the **digit strip**, `%`, `∞`, 制限時間, 体力値, ゲージ増加量, 決定, 戻る, ON/OFF | 512×512 |
| `data/select/P02.cnv` | 青/赤チーム風船サイズ (two sizes each), the three hypermode **descriptions**, `1P 2P 3P 4P`, `com`, `RANDAM`, the three `PLAYER` variants, 今日の主役, the diamond mask | 512×512 |
| `data/select/p03.cnv` | the **16 character names**, one cell each, in roster order | 512×512 |
| `data/select/bg00.cnv` | the four 青組/赤組 **diamond panels** (blue, red / blue, red) | 800×600 |
| `data/select/bg01.cnv` | the diamond-**window mask** over the sky/ground photo | 800×600 |
| `data/select/sbg00.cnv` | the **stage-select page background** incl. the `STAGE SELECT` / `BATTLE SETTING` headers | 800×600 |
| `data/select/pbg00.cnv` | character-pair combo help pages | 512×512 |
| `data/select/pbg01.cnv` | **stage thumbnails** (3-wide sheet, incl. the `?` cell for ランダム) | 512×512 |
| `data/select/pbg02.cnv` | **stage names** (ランダム, 雛見沢分校 校庭, 学校へと続く道, 古手神社 境内, 川沿いの山道, タム建設現場跡地, 古手神社 祭具殿前) + the variation names (昼, 夕方, 夜) | 512×512 |
| `data/select/s1p…s4p.cnv` | the 1P–4P player tags, cells 400×300 (`FUN_00408330.c:103-105`) | 480×500 |
| `data/select/NN.cnv` (00–15) | **character portraits**, 256×256, drawn 128×256 | 256×256 |
| `data/select/iNN.cnv` (00–15) | **chibi sheets**, six 80×128 cells (3×2), drawn 40×80 | 256×256 |
| `data/select/cosNN.cnv` (00–15) | **costume icons**, a 3×2 chibi grid per character (ASSET-CATALOG §2.6) | 256×256 |
| `data/select/wNN.cnv` (00–15) | **weapon text sheets**: 3 weapons × (name/type/description), 256×64 cells | 512×512 |
| `data/title/back00.cnv` | the shrine-approach title background | 800×600 |
| `data/title/logo.cnv` | the ひぐらしデイブレイク logo | 512×512 |
| `data/title/title.cnv` | the **six menu items**, 2 states (white/dark) × 6 rows, 192×48 cells | 512×512 |
| `data/teamselect/bg00.cnv` | story-mode select background (four diamond windows + green chibi platform + 今日の主役) | 800×600 |
| `data/teamselect/p00/p01.cnv` | blue/red slot panels, six 256×160 cells each (teammate info) | 512×512 |
| `data/teamselect/tNN.cnv` (00–09) | team/slot art, 2×2 cells of 256×256 (`FUN_004057c0.c:91-102`) | 512×512 |
| `data/teamselect/add0/add1.cnv` | the result/staff-roll "add" panels (scene 21) | 512×512 |
| `data/config/0001…0003.cnv` | the three option pages (labels + slider tracks + 0 %/100 % ends) | 800×600 |
| `data/keyconfig/0000…0004.cnv` | the five binding-table pages | 800×600 |
| `data/network/*.cnv` | netplay backgrounds (`nback00/01/02`), item text (`menu`), descriptions (`menu2`), soft-keyboard action bar (`nameMenu`), digits + connection messages (`number`), `object` | 800×600 / 512×512 / 256×256 |
| `data/chat/*.cnv` | `chat` = the chat box + 発言 button; `name_p1`/`name_p2` = the **name glyph grid** (the soft keyboard *is* the name font: digits, ASCII, hiragana, katakana, punctuation); `name_p1s`/`name_p2s` = their selected/second variants (the variant role is inference; the grid content is certain) | 512×512 |
| `data/vs/vs01…vs03.cnv` | the VS sting art (03 = the VS logo) | 256×256 |
| `data/win/NNa.cnv` / `NNb.cnv` | per-character victory art (two poses) | 512×512 |
| `data/object/system.cnv` | battle/pause/result system text: `OVER KILL!!`, `DOWN!`, `PAUSE`, もう一度挑戦しますか？, はい/いいえ, 本日の活動報告, 1P–4P, com | 512×512 |
| `data/object/P04/P05/P08/P09.cnv` | 撃沈！/開始！, 青組 大勝利, 赤組 大勝利, `3 2 1` + 撃破！ | 512×512 |
| `data/object/p00/p01/p02/p03/p12/p13.cnv` | HUD digits + `%`, balloons, gauge frames, circular gauges (BATTLE-HUD-SPEC) | — |
| `data/object/勝利バー.cnv` | the victory bar overlay | 2097 B, tiny |
| `data/object/勝利画面土台.cnv` | the victory-screen base overlay | 800×600 |
| `data/object/gameover.cnv` | the game-over art | 800×600 |
| `data/talk/window.cnv` | the ADV message-window frame (story/result text box) | 624017 B |
| `data/scenario/win/NN-MM-K.txt` | per-character **win quotes** with `\cRRGGBB` colour runs and `\n` breaks (570 files) | text |
| `movie/op.mpg`, `movie/prologue.mpg`, `movie/staffroll*.mpg` | opening, prologue, staff roll | video |
| `data/bgm/{title,select01,vs,win,lose}.ogg` | menu/intro/result music | audio |

### 3.2 Per-screen asset list and the bundle that carries it

Bundles are read in numeric order, first match wins; the extracted
`Higurashi-Daybreak/data/` tree is the fallback. The bundle column below was
read straight out of the `.dat` entry tables.

| screen | assets | bundle |
|---|---|---|
| title | `title/back00`, `title/logo`, `title/title`, `bgm/title.ogg` | 00 (art), 05 (bgm) |
| opening / prologue | `movie/op.mpg`, `movie/prologue.mpg` | 02 (bundle-only) |
| select page 0 | `select/bg00`, `bg01`, `p00`–`p03`, `s1p`–`s4p`, `iNN`, `cosNN`, `NN`, `wNN`, `bgm/select01.ogg`, `voice/entry/<char>` (confirm) | 00, 04 (voice), 05 (bgm) |
| select page 1 (stage/settings) | `select/sbg00`, `pbg00`–`pbg02`, `P01`, `P02`, `p00`–`p03` | 00 |
| options | `config/0001`–`0003` | 00 |
| key config | `keyconfig/0000`–`0004` | 00 |
| VS intro | `vs/vs01`–`vs03`, `select/%02d`, `select/p03`, `bgm/vs.ogg` | 00, 05 |
| battle HUD | `object/system`, `p00`–`p04`, `p05`, `p08`, `p09`, `p12`, `p13`, `aura/%02d.x`, `trail/%02d.bmp` | 00 |
| result | `win/NNa`, `win/NNb`, `object/system`, `object/勝利バー`, `object/勝利画面土台`, `scenario/win/*.txt`, `talk/window`, `bgm/{win,lose}.ogg` | 00, 05 |
| game over | `object/gameover` | 00 |
| staff roll | `movie/staffroll*.mpg`, `teamselect/add0/add1` | 02/06 (movies), 00 (art) |
| netplay menu/lobby/soft keyboard | `network/*`, `chat/*` | 00 |
| story select (scene 5) | `teamselect/*`, `select/i00`–`i13`, `s1p`, `s2p`, `p00`–`p03` | 00 |
| story ADV | `talk/window`, `talk/cNN-M`, `talk/backNN`, `scenario/*.txt`, `voice/entry/<char>` | 00 (text/art/voice), 04 (voice variants) |

Notes:
* **Voice extension trap**: the select screen's confirm plays
  `data/voice/entry/%s.wav` (`FUN_00409340.c:187-214`,
  `FUN_00406850_loadnextcallee.c:132-138`) but the shipped assets are
  `data/voice/entry/<char>.cnv` (14 in `daybreak00.dat`, the story cast, plus 60
  `_B`/`_C` variants in `daybreak04.dat`) — audio in the `.cnv` container
  (`remake/foundation/src/assets/cnv.h` documents the audio reading of the same
  header). The loader must reconcile the requested `.wav` with the shipped
  `.cnv`, exactly as it must for the image names. The same pattern holds for
  every character voice (`data/voice/<char>/<event>/NNN.cnv`).
* `data/select/p01.cnv` is stored as **`P01.cnv`** (capital P) in the tree and in
  the bundle — a real case trap (ASSET-CATALOG §7 trap 20); resource lookup is
  case-insensitive in the original (`asset_source`), so match that.
* `data/config/*` starts at **0001**, `data/keyconfig/*` at **0000** — off by one
  between the two screens (`FUN_00402890.c:33-34` vs `FUN_00403eb0.c:33-34`).
* The `.bmp` names in the code are the `.cnv` files in the data (`"data/select/
  p00.bmp"` loads `data/select/p00.cnv`); the tree also ships `.bmp` twins, which
  is what the extracted `data/select/*.bmp` are.

---

## 4. Text strategy

### 4.1 The method

The HUD track lost a rewrite to assuming labels were text. So this section does
not assume: it counts the ways the original can put a glyph on screen and then
checks each screen against them.

1. **Fonts are created in exactly five places.** A font is created by
   `FUN_0065d870(height,…)` with the face string at object offset 0xc; the only
   Japanese face literal in the executable is `ＭＳ ゴシック` at `.rdata`
   0x6a1ae4, 0x6a1cc0, 0x6a49d8, 0x6a4d50, 0x6a4d60. Searching `.text` for
   references to those five addresses gives the five creation sites:

| site | enclosing function | screen |
|---|---|---|
| `.text` 0x40e87f | `FUN_0040e720` | story ADV (scene 8) |
| `.text` 0x41253c | `FUN_00412110` | netplay menu (scene 11) |
| `.text` 0x6343fb | `FUN_00633ca0` | battle/result block (HUD + result) |
| `.text` 0x645956 | `FUN_00645840` | chat (netplay lobby) |
| `.text` 0x6459eb | `FUN_00645840` | chat (second size) |

2. **String drawing exists in exactly nine functions.** The string→texture call
   `FUN_00656190` (which internally uses `FUN_00657170` → `FUN_0065dad0` →
   `FUN_0065d870`/`FUN_0065d9a0`; `CJK-TEXT.md` §1) is called from:
   `FUN_0040f4c0` (story script interpreter, scene 8), `FUN_00412110` (netplay
   menu, scene 11), `FUN_00635d40` (result quote), `FUN_0063c2a0`, and the four
   text-window helpers `FUN_00645e10`, `FUN_00646110`, `FUN_006463c0`,
   `FUN_00646460` (used by scenes 3, 12, 13, 14, 18). **No other function in the
   corpus draws a string.** Note the one *text-like* mechanism that is not text:
   `FUN_00646bd0` draws **player names as eight grid cells** (`§2.16`), which is
   art plus an index, and it is why the VS-intro and lobby nameplates need no
   font.
3. **The executable's string census.** The `.rdata` walk (§0.1) finds 183
   Shift-JIS-containing strings, and **not one menu label**: no ストーリー, 対戦,
   通信対戦, 環境設定, 操作設定, 終了, 決定, 戻る, 制限時間, 体力値,
   ゲージ増加量, 風船サイズ, 準備完了, CHARACTER SELECT, WEAPON SELECT — none of
   them is in the executable. What *is* there is: the GDI face name, the 30
   activity-report titles (0x6a2584–0x6a27e0), ～接続しました～ / ～切断しました～,
  勝利バー (`data/object/勝利バー.bmp`), asset path templates and error strings.

Conclusion: in the original, **a menu label is art unless it is one of the three
text contexts** (the result quote/report, chat, the story ADV). The 23 prints
agree: decoded, the select screens' labels are all pixels in
`data/select/p0*.cnv`, and the option/keyconfig/netplay pages are whole
pre-rendered pages.

### 4.2 Per-screen verdict

| screen | verdict | evidence |
|---|---|---|
| title menu | **atlas art** | items decoded from `title/title.cnv`; no font, no `FUN_00656190` in scene 1 |
| select page 0 (team/char/weapon/hypermode/controller/ready) | **atlas art** | headers/verbs `p00`, digits/決定/戻る/準備完了 `P01`, PLAYER/com/1P–4P/RANDAM/風船 `P02`, names `p03`, weapon text `wNN`; no font in `FUN_00408330`, `FUN_004090a0`, `FUN_00409340`, `FUN_0040b2b0`, `FUN_0040d130` |
| select page 1 (stage + battle settings) | **atlas art + numeric glyph draws** | `sbg00` headers, `pbg01` thumbs, `pbg02` names, `P01` digit strip via `FUN_00431b20`/`FUN_00431ce0` (`FUN_0040cd00.c:44-59`); no font |
| options | **atlas art** | `config/000N` pages; no font in `FUN_00402890`/`FUN_00402be0`/`FUN_00403470` |
| key config | **atlas art** | `keyconfig/000N` pages; no font in `FUN_00403eb0`/`FUN_00404220`/`FUN_00404a50` |
| VS intro | none | all art |
| battle HUD / stamina / ammo / KO | **art + GDI** | art is the atlas family in BATTLE-HUD-SPEC; the GDI string is `適当` (CJK-TEXT §2) plus the HUD's own font created in `FUN_00633ca0` |
| result-victory | art | `P05`/`P08` |
| result-quote | **GDI text** | `data/scenario/win/*.txt` → `FUN_00656190` at `FUN_00635d40.c:362`, font at `FUN_00633ca0`+0x75b |
| result-report | **GDI text + art + cell names** | titles are exe strings (GDI); header/tags are `object/system.cnv`; player names via `FUN_00646bd0` (`FUN_0063a740.c:33-48`) |
| netplay menu | art for the items, digits for IP/port | `menu.cnv` decoded; font created in `FUN_00412110`; IP via `"%d.%d.%d.%d"` |
| netplay lobby | art chrome + **cell names** + **GDI chat** | `nback02.cnv` decoded (部活メンバー募集中/CHAT/GUIDELINE/hint bar); names via `FUN_00646bd0`; chat text via the two fonts in `FUN_00645840` and `FUN_00645e10`/`FUN_00646110` |
| soft keyboard | art grid (which doubles as the **name font**) | `chat/name_p1.cnv` grid = the print cell for cell; `network/nameMenu.cnv` action bar; names stored as grid coordinates (`FUN_00646bd0`) |
| story ADV | **GDI text** | `data/scenario/*.txt` + portraits; font at `FUN_0040e720`+0x15f |

### 4.3 What this means for the track

* **Do not build a text path for the select screens.** The team/character/
  weapon/hypermode/controller/ready/stage screens are pure sprite work plus the
  numeric glyph draws (`FUN_00431b20`/`FUN_00431ce0` → two small helpers over
  the digit strip). A text renderer there buys nothing and invites the HUD
  track's mistake.
* **The CJK layer (`remake/foundation/src/ui/text.{h,cpp}`, decision B in
  `CJK-TEXT.md` §5) is needed for exactly three things**: the result quote/report
  (the first one, because it is in the versus loop), the netplay/chat screens,
  and story mode. The quote text's `\cRRGGBB` and `\n` control codes are already
  the semantics `TextLayer::layout`/`parseColorRuns` implement
  (`remake/foundation/src/ui/text.h:93-123`), and the font-metric mode
  (`loadFontChain`) matches what `FUN_0065dad0` does with `GetCharWidth32A`.
* **Strings must be Shift-JIS-decoded on the way in** (`xm::sjisToUtf8`,
  `remake/foundation/docs/UI-INTEGRATION.md` last note): the scenario files and
  the title strings are Shift-JIS and the text layer takes UTF-8.
* **A menu-label atlas is a first-class asset**, not a fallback: for the select
  screens the atlas *is* the specification, so the atlas loader has to expose
  cell-indexed draws (the foundation's `ui/sprite.h` already has
  `spriteDst(srcW,srcH,pivotX,pivotY,…)` and a `UiRect`/`UiClip` model that
  covers `FUN_00655830`'s cell maths).
* **Player names are cells, not strings** (`FUN_00646bd0`, §2.16): the name font
  is `data/chat/name_p1.cnv` and a name is up to eight `(cellX,cellY)` pairs.
  Anywhere the port shows a player name (VS intro, lobby, result report) it can
  reuse the same grid-cell drawer and needs no CJK glyph for names — which also
  means names stay pixel-identical across Linux/Windows/web for free.

---

## 5. The shared state machine

### 5.1 What the original does, and what to copy

Copy these three properties (they are what makes the front end a *system*
instead of a pile of screens):

1. **One scene, one update function, one return value.** The update returns the
   next scene id (or its own id to stay); the framework owns the fade and the
   construction. `remake/src/core/scene.h` already has this shape
   (`UpdateResult::Transition` + `set_next`), and the foundation's App does not
   need more than the same enum.
2. **A 25-frame fade on every change**, alpha `(n*10+5) << 24`
   (`FUN_00657c80.c:16-49`), with the old scene still running during the fade.
   This is cheap and it is why the prints' transitions look the way they do.
3. **Per-slot sub-states inside the select**, not one scene per panel: the
   select owns `state[slot]` and dispatches (scene 5's table in §2.17 is the
   reference implementation; scene 3's `FUN_00409340` is the 4-slot variant).

Do **not** copy: the global-variable match config scattered across `.data`
(§5.2) — give the port one struct owned by the App and passed to the battle
scene, keeping the same field semantics so the RE mapping stays one-to-one.

### 5.2 The match configuration (what the stage screen produces)

These are the fields the original's select writes and the battle reads. They are
the contract between the front end and the existing battle path.

| field | meaning | domain | writer / reader |
|---|---|---|---|
| slot character | `DAT_006cfaf8[slot]` (int) / `DAT_006cfb28[slot]` | 0–15; **4 = unset → COM with a random character** | `FUN_0040d130.c:71-83`, `LoadNextScene.c:95-121`; read by the battle |
| slot weapon | `DAT_006cfb38[slot]` (int) | 0–2 (0–1 for the two 2-weapon characters) | `FUN_0040d130.c:74-78`; scene 5 `0x2e60` |
| slot hypermode | `DAT_006cfb48[slot]` (byte) | 0–2 (Friendship / Oyashiro / Kakera) | `FUN_0040d130.c:81`; scene 5 `0x2e70` |
| slot costume | `DAT_006cfb4c[slot]` (byte) | 0…`DAT_006b71c0[char]−1` | scene 5 `0x2e80`; table at `.data` 0x6b71c0 |
| humans | `DAT_006cfba0`, `DAT_006cfba4`, `DAT_006cfba8` | count + which side | `LoadNextScene.c:111-121` |
| 制限時間 | `DAT_006cf3c0` | 0 (=∞), 60, 120, 180, 240 | `FUN_0040acb0.c:59-61` |
| 体力値 | `DAT_006cf3b8` | 50…200 step 25 | `FUN_0040acb0.c:62-68` |
| ゲージ増加量 | `DAT_006cf3bc` | 50…200 step 25 | `FUN_0040acb0.c:69-75` |
| 青チーム風船サイズ | `DAT_006cf3b0` | 40…200 step 20 | `FUN_0040acb0.c:76-82` |
| 赤チーム風船サイズ | `DAT_006cf3b4` | 40…200 step 20 | `FUN_0040acb0.c:83-89` |
| stage | `scene+0x3d48` | 0 = ランダム, 1–6 | `FUN_0040acb0.c:53-58`; thumbnails `pbg01`, names `pbg02` |
| stage variation | `scene+0x3d4c` | 0…(count−1); names 昼/夕方/夜 | `FUN_0040acb0.c:64-73` |
| mode flags | `DAT_006cfce9` (story), `DAT_006cfdb0` (netplay), `DAT_006cfbc4` (story chapter byte) | — | title `FUN_00410f60.c:108-119`; VS intro `FUN_00411ae0.c:41-45` |

The existing battle path already consumes the balloon/HP/gauge notions
(`m_balloon`, `m_limit`, `m_startHP`, `m_startGauge` in
`remake/src/core/scenes.h`); the port's `MatchConfig` should carry exactly the
rows above so nothing in the battle track has to change.

### 5.3 Files a track would add

On the WebGPU foundation (the active renderer, D2), inside the existing seams
(`src/ui/`, `src/assets/`, `src/gameplay/`):

| file | contents |
|---|---|
| `src/ui/screen.h`, `src/ui/screen.cpp` | `Screen` base (enter/exit/update/draw, `next_id()`), `ScreenStack`/`ScreenId` enum mirroring the original's ids (0–0x15) and the 25-frame fade |
| `src/ui/menu_atlas.h/.cpp` | typed accessors for the menu sheets: `selectHeader(verb)`, `charName(idx)`, `digitStrip`, `stageName(i)`, `stageThumb(i,var)`, `modeName(i)`, `modeDesc(i)`, `playerCom(state)` — each returning a cell rect from `data/select/p0*.cnv` / `pbg0*.cnv` |
| `src/ui/screens/title.cpp` | scene 1: three sprites + the six-item cursor/confirm machine |
| `src/ui/screens/select.cpp` | scene 3 page 0: the four slot panels, the chibi grid (geometry from §2.17), the per-slot state machine (character → weapon → hypermode → PLAYER/COM → ready) |
| `src/ui/screens/stage_select.cpp` | scene 3 page 1: the eight-row list and its domains (§2.9), writing `MatchConfig` |
| `src/ui/screens/vs_intro.cpp` | scene 9: the 90-frame slide/alpha timeline |
| `src/ui/screens/options.cpp`, `keyconfig.cpp` | scenes 6/7: page + row editing, writing the settings structs |
| `src/ui/screens/result.cpp` | the three beats over `data/win/*`, `object/system.cnv`, `scenario/win/*.txt` (needs `ui/text`) |
| `src/ui/soft_keyboard.h/.cpp` | reusable grid keyboard (`chat/name_p1.cnv` grid + `network/nameMenu.cnv` bar), later hosted by netplay |
| `src/gameplay/match_config.h` | the §5.2 struct + its clamps/steps, unit-testable |
| `src/assets/menu_assets.h` | the manifest of §3.2 (paths, expected cells, bundle order) |

### 5.4 CLI flags that must stay (captures depend on them)

Keep, unchanged, every flag the visual suite already uses; they are how a screen
gets verified headlessly.

* Foundation (`remake/foundation/src/main.cpp:184-217`): `--install=`, `--stage=`,
  `--character=`, `--weapon=`, `--model=`, `--effect=`, `--camera=`, `--size=`,
  `--frames=`, `--anim=`, `--time=`, `--dt=`, `--out=` (PPM capture),
  `--headless`, `--no-textures`, `--unlit`, `--no-anim`, `--hud-test`,
  `--versus`, `--match`, `--script=`, `--script2=`, `--list`,
  `--no-camera-clamp`.
* DX9 A/B reference (`remake/src/main.cpp:378-410`): `-scene`, `-p1`, `-p2`,
  `-hyper`, `-hp`, `-gauge`, `-spawn`, `-spawn2`, `-shot`, `-frames`,
  `-script`.

Add (do not replace): `--screen=<id|name>` to boot a front-end screen directly,
and reuse `--script=` for menu input — the script format already drives menu
navigation (`UP/DOWN/LEFT/RIGHT/JUMP/MELEE` …,
`remake/foundation/src/input/input.h:81-100`), which makes "title → select →
stage → battle" reproducible frame by frame instead of by hand.

### 5.5 How it plugs into the existing App without a rewrite

The foundation's `App` already owns the device, the loaded scene, the HUD/UI
renderer and the capture path; the front end does **not** need a second main
loop:

1. Add the screen stack next to `App` and let it own *what to draw* instead of
   the CLI: `--screen` and `--match` merely choose the initial screen
   (today `--versus`/`--match` choose the initial scene directly — that stays as
   a shortcut).
2. Draw order is already the right one: 3D pass, then
   `ui.beginFrame()` / compose / `ui.render()` in the same encoder
   (`remake/foundation/docs/UI-INTEGRATION.md`), so a menu screen is just a
   compose call with atlas quads on top of a full-screen background sprite.
3. `SceneRenderer::capture` + `--out` + `--frames` already produce a PPM for the
   compare tools; a menu capture therefore needs no new plumbing — only
   `--screen` plus a script.
4. The DX9 tree keeps its own `SceneManager`/`Scene` (it is the A/B reference);
   the front end lands once, in the foundation, and the DX9 tree only needs the
   same `MatchConfig` if a comparison capture of a menu is ever wanted.

---

## 6. Implementation order and verification

### 6.1 Order and rationale

| step | screen(s) | why here |
|---|---|---|
| 1 | **title menu** (scene 1) | 3 assets, one fully-read update function, zero font work, and it is the entry point of every other screen. Lands the screen stack, the atlas accessor and the fade on the cheapest possible content. |
| 2 | **select page 0** — team + character + ready first, then weapon + hypermode + PLAYER/COM | one screen state machine covers **six of the 23 prints**; the panel grammar is read from two independent implementations (`FUN_00409340` 4-slot, `FUN_00406850` 2-slot), and the per-slot state values, the weapon-atlas reload and the COM auto-fill rule are all located. Its one remaining extraction job is the roster grid's own cell table inside `FUN_0040b2b0` (§7). Largest single unlock in the flow. |
| 3 | **select page 1** — STAGE SELECT + BATTLE SETTING | the only screen that produces the match configuration the battle consumes, and its five knobs' domains/steps are fully RE'd (§2.9). It makes the versus loop clickable end to end: title → select → stage → (VS) → battle. |
| 4 | **VS intro** (scene 9) | 51 lines of update, three assets, and it is the piece that hands control to the battle that already exists. Cheap enough to slot in wherever a playable loop is wanted. |
| 5 | **result** (quote first, then report) | the loop's exit; requires the CJK text layer, so it should follow the text work, but the quote is the smallest possible consumer of it (one string per match from `data/scenario/win`). |
| 6 | **options + key config** | isolated, art-only, no flow risk; needed for volume and for binding the pad. |
| 7 | game over (scene 20), then the deferred netplay set | reachable, small; netplay per D6. |

Cheap-and-high-value is steps 1 and 4; expensive-and-high-value is step 2;
step 3 is medium cost with a hard dependency (the battle) already satisfied.

### 6.2 The first three screens to build

1. **Title menu** — cheapest screen in the whole inventory (three
   sprites, six items, one cursor machine) and it is the only screen that proves
   the screen stack, the atlas accessor and the transition fade on content whose
   spec is fully read (`FUN_00410d60`, `FUN_00410f60`, `FUN_004114f0`).
2. **Select page 0** — because team/character/weapon/hypermode/controller/ready
   are **one** screen in the original (§1.2) and it covers the six prints the
   owner's loop passes through. Building it as six scenes would be the single
   most expensive mistake available here.
3. **Select page 1 (stage + battle settings)** — the bridge to the battle screen
   that is already nearly closed: it produces the five settings and the stage,
   and its whole contract (§5.2) is extracted, so this is the step that turns
   "menus exist" into "the game is playable from the title".

### 6.3 Verifying a screen against its print

The instruments exist and are the established ones:

* `remake/foundation/tests/compare_frames.py <print|dx9.png> <foundation.ppm>
  [--out diff.png]` — whole-frame RMSE / coverage / luminance + a difference
  image, for the "does the screen look like the print at all" question.
* `remake/foundation/tests/hud_bands.py <foundation.ppm> [--bands …] [--shapes]`
  — per-element bands in **game coordinates**, cropped from both images without
  resampling, plus the ink-mask IoU with the best integer offset. This is the
  instrument for "did each panel land where the original draws it", and it is
  the one to copy for menus (`--bands` already takes a list; a `--bands
  title_items,select_panels,…` set per screen is the natural extension).
* `remake/tests/visual/run.sh` + `tests/parity-baseline/` — the capture suite and
  the banked DX9 frames; a new screen should get a case there so the A/B
  discipline keeps holding.

**Offset discipline.** Each print is a capture of the 800×600 frame with its own
offset and its own border; the documented, verified example is
`battle-hud.webp` at 798×606 with `game = (print_x + 2, print_y − 6)`
(`BATTLE-HUD-SPEC.md` §"Print vs frame", re-verified in `hud_bands.py`). **Do not
generalize that offset** — the prints differ:

| print | size | print | size |
|---|---|---|---|
| `title-menu` | 803×608 | `option-screen` | 803×601 |
| `team-select` | 801×604 | `controller-setup` | 799×605 |
| `char-select-rena` | 804×601 | `vs-intro` | 799×600 |
| `weapon-select-rena` | 800×602 | `result-quote` | 800×602 |
| `hypermode-select` | 804×603 | `result-report` | 798×601 |
| `controller-select` | 801×604 | `result-victory` | 797×602 |
| `ready-confirm` | 804×607 | `netplay-menu` | 802×599 |
| `stage-select-random` | 800×602 | `netplay-lobby` | 798×599 |
| `stage-select-school` | 802×603 | `soft-keyboard` | 802×598 |
| `battle-hud` | 798×606 | `ko-moment` | 803×606 |

For each screen, the recipe is:

1. Pick **two independent features with known game coordinates** from the RE
   (e.g. for the stage screen: the 575,150 thumbnail and the 275/550 決定 cell;
   for the title: the logo rect and one item cell). Predict their game-space
   positions from the read constants.
2. Measure them in the print. The difference must be the *same* (dx,dy) for both
   — that is the print's offset. Two features is the minimum; a third is the
   check.
3. Bank that offset in the screen's section of the band list, and add the bands.
4. Capture ours with `--screen=<screen> --frames=N --out=<work>/<screen>.ppm`
   (+ `--script=` to reach a sub-state, e.g. two `DOWN`s and a `JUMP` to land on
   the weapon panel), then run `compare_frames.py` for the frame number and
   `hud_bands.py` for the elements.
5. Record the numbers in the doc (or a per-screen spec page if it grows), the way
   `BATTLE-HUD-SPEC.md` records the HUD's.

Per-screen, the check is:

| screen | the two anchors to measure |
|---|---|
| title | logo rect (from `FUN_00410d60.c:35`), one item cell |
| select page 0 | one diamond panel centre (slot geometry §2.3), one chibi cell (§2.17 grid formula) |
| select page 1 | the thumbnail at (575,150), the 決定 cell at (275,550) |
| options | row 0 label (176,128), the master slider's 100 % end |
| key config | the grid origin (336,128) and one binding cell (64×32 pitch) |
| VS intro | portrait rest positions (from `FUN_00411cb0`) at the final frame |
| result | the quote box rect and one title line |
| battle | already banked in `BATTLE-HUD-SPEC.md` |

---

## 7. Where the RE is thin (do these before/while implementing)

1. **Panel anchor tables, not yet transcribed**: `FUN_0040b2b0` (scene 3 page 0)
   and `FUN_004072b0` (scene 5) contain the per-panel cell/anchor sets, including
   scene 3's **16-cell roster grid positions**; the functions are located and
   their structure is read, the constant list is not. This is a mechanical read
   and it is the first task of the select track. Scene 5's numbers are already
   extracted (§2.17) but are a different table — do not reuse them.
2. **`result-report` composition**: the data path (titles, session title arrays,
   confirm handling) is RE'd; the function that lays out the report page is **not
   isolated**. Measure from the print and treat the layout as new work with a
   pixel check.
3. **`ko-moment` trigger**: the sting art is located (`data/object/P09` via
   `FUN_00633ca0`), the call sequence that fires it is not read.
4. **Soft-keyboard widget**: the grid and action-bar assets are identified and
   the host scene is known; the function owning the grid cursor is not isolated.
5. **Stage variation counts**: the count byte at `scene+0x3d90` (one of the
   per-slot dword arrays initialised in `FUN_00408330.c:143-154`) and the default
   2-way cycle have to be reconciled with the three variation names in
   `pbg02.cnv` (昼/夕方/夜); one on-screen cycle capture resolves it (already
   flagged as a TODO in the reference README).
6. **Scenes 2, 14–19 identities**: ids, constructors and update returns are in
   §1.2; what they show is not RE'd, deliberately (story-mode scope, D6).
7. **Scene 5's exact role** is stated from asset identity (its background
   `teamselect/bg00` is a different screen from the prints) and from its return
   value (8 = story ADV). If the owner ever wants the story select in scope,
   treat it as a second select implementation rather than a variant of scene 3.
