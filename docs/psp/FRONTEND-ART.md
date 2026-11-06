# PSP frontend art — the select and VS screens

The three fighters that only exist in *Higurashi Daybreak Portable Mega Edition* — Satoshi Houjou,
Miyoko Tanashi and Okonogi — join the remake's roster as indices **16, 17 and 18**. This document
is the **contract** for the art those two screens read: exactly which files, which sizes and which
cell layouts, who writes them, and what the screens do when one is missing.

Companion documents: [`../PSP-CHARACTERS-WORKLOG.md`](../PSP-CHARACTERS-WORKLOG.md) (D-1 and D-3a,
the binding decisions), [`../PSP-CHARACTERS-PLAN.md`](../PSP-CHARACTERS-PLAN.md) (the track plan),
and the raw studies in ignored `local-data/harness/psp/notes/` (`art.md` §2–§7 for the PSP side,
`integration.md` §4 for every product site that assumed sixteen characters).

Nothing here is tracked: the art belongs to the rights holders. The extractor and this document's
reference generator read the player's own copy and write beside the executable.

---

## 1. Where the files live, and which source wins

Every sheet in §2 is an ordinary game path — `data/select/16.cnv` — read through the product's one
asset seam, `fnd::assets::AssetSource` (`src/assets/asset_source.*`). The converted PSP data is an
**extra loose-file root** mounted on that seam:

```cpp
// src/assets/asset_source.h
bool mountDataRoot(const std::string& dir);      // false when `dir` is not a folder
void clearDataRoots();
const std::vector<std::string>& dataRoots() const;
```

`read()` / `exists()` / `listDir()` consult, in this order:

1. the install's `daybreakXX.dat` bundles (the game's own data always wins);
2. the path the caller passed, verbatim (an absolute path, or an extracted tree);
3. the mounted roots, by install-relative key — `data/select/16.cnv` finds
   `<root>/data/select/16.cnv`, and `listDir("data/select")` lists the root's files when no bundle
   has that directory;
4. the case-folded filesystem probe (non-Windows, no bundles).

So no reader learns a second path syntax: the converter writes the game's own paths, and every
existing loader finds the new files by asking for the name it already asks for.

**Who mounts it.** `SDL_AppInit` (`src/app/main.cpp`, next to the texture packs):

* `--psp-data=<dir>` mounts exactly that folder, and a folder that is not one is a startup error
  (`psp-data: "<dir>" is not a folder`) — the same rule `--install=` follows.
* A **non-verification** run also mounts `<dir of the executable>/psp-data` when it exists.
* A **verification run** (any `--headless`, `--out`, `--script`, `--match`, `--list`, … launch)
  mounts only the folder it names, because a capture must not be moved by something that happens
  to sit next to the binary. This is the rule the texture packs already follow, and it is
  measured: with `psp-data/` beside the binary, `title4p` still hashes
  `9ecda8ec78fb136072ac54a9aba35b3231520eef9d4562c760a90d8c23b7bc27`.

Mounting is also what turns the three on: `gameplay::rosterCharacterCount()` is 19 while the PSP
data is mounted and 16 otherwise (`gameplay::setPspRosterMounted`, `src/battle/weapon_definition.h`).
No mount, no new characters, and every screen draws exactly the pixels it drew before.

## 2. The files the two screens read for indices 16–18

All four families follow the PC sheets they replace, so the screens need no per-character branch:

| File | Size | Cells | Read by |
|---|---|---|---|
| `data/select/NN.cnv` | **256 × 256** | one portrait, pivot bottom-centre (128, 256) | select panel portrait (scaled ×1), VS portrait (scaled ×1) |
| `data/select/iNN.cnv` | **256 × 256** | 3 columns × 2 rows of **80 × 128**, cell (col, row) at (col·80, row·128) | the select diamond's chibi icon |
| `data/select/cosNN.cnv` | **256 × 384** | 3 columns × **3** rows of **80 × 128**, row-major from (0, 0) | the costume icon (cell `costume`, `screen_select.cpp`) |
| `data/select/wNN.cnv` | **512 × 256** | 4 rows of **256 × 64**, row = weapon slot a–d; two columns of 256 × 64 per row | the weapon row list (column 0) and the plate under it (column 1) |

`NN` is the two-digit roster index: `16.cnv`, `i16.cnv`, `cos16.cnv`, `w16.cnv`, and the same for
`17` and `18`.

**The iNN cell order is the screen's own**, not a new one: cell (0,0) is the settled icon, cells
(1,0) (2,0) (0,1) (1,1) are the idle cycle a selected character animates, and **cell (2,1) must be
100 % opaque white** — that is the flash the entry reveal shows while a slot's ramp is below 1.0
(`SelectChibiCell` in `src/frontend/screen_select.h` documents all six).

**The cosNN third row exists for Miyoko.** The PSP gives her seven costume variants
(`chr180`–`chr186`), the PC's own cos sheets hold six cells, so the three new sheets are one row
taller and the screen's `(costume % 3, costume / 3)` addresses them without a special case.

**The name plates are not in this contract.** The PC sixteen have a 256 × 64 cell each in the
shared `data/select/p03.cnv` (2 columns × 8 rows), which the install ships and the locale file
repaints. Indices 16–18 are outside that atlas, so both screens draw their names with the caption
face instead (`src/ui/caption.h`, `src/frontend/roster_name.h`) and take the English spelling from
`assets/locale/en.txt` (`select/name`, indexed by roster index). The PSP's own name plates
(`gra/gim/select/char_name.gim`, 64 × 48 per character) are **not used**: they are baked Japanese,
and the rest of the port localises names.

### Costume counts

`kSelectCostumes[16..18] = {5, 7, 3}` — the PSP's own model counts (`chr170`–`chr174`,
`chr180`–`chr186`, `chr190`–`chr192`). Selecting costume *k* launches `data/<dir>:<k>`, which needs
`psp-data/data/<dir>/0k.dat` from the extractor (D-3a). Until those files exist the launch is the
clear failure in §5, exactly as it is for the fighters themselves.

### Weapon item ids

`101…112`: Satoshi a–d = 101–104, Miyoko a–d = 105–108, Okonogi a–d = 109–112
(`gameplay::kPspRoster`, `kPspItemIdFirst = 101`). The PC's shipped ids are 1–46, so the range
cannot collide with anything the install has. The extractor writes `psp-data/data/item/101.dat` …
`112.dat` at those ids; the launch reads exactly the id the roster table gives.

## 3. The select diamond's three new cells

`kSelectRosterX/Y` (`src/frontend/screen_select.h`) are the diamond's cells in a 48 × 36 pitch
lattice. The original's sixteen keep their values bit-identically; the three are **appended**:

| Index | Cell | Position (px) | Distance to the nearest icon |
|---|---|---|---|
| 16 Satoshi | (−1, 7) | (−48, 252) | 60 (to (0,6) and (0,8)) |
| 17 Miyoko | (1, 7) | (48, 252) | 60 (same) |
| 18 Okonogi | (0, 8) | (0, 288) | 60 (to (−1,7) and (1,7)) |

They hang **below** the diamond's bottom vertex (0,6), in the empty middle column between the two
lower panels, and each is 60 units or more from every other icon. That distance is a requirement,
not taste: the recovered selection passes (`FUN_00409340:272-286`) are a 30-unit pass that overrides
a < 50-unit fallback, both taking the FIRST icon in roster order, so two icons one lattice step
apart (48 px across, 36 px down) leave a band where the cursor keeps naming the earlier roster
index. The art study's suggested (−1,6), (1,6), (2,5) sit 36–48 units from an existing icon —
(−1,6) and (1,6) are 48 from (0,6), (2,5) is 36 from (2,4) and 48 from (1,5) — i.e. inside that
band, which is why the pendant below was used instead.

All three are also inside the free cursor's own clamps (x ∈ [−200, 200], y ∈ [−60, 300];
`FUN_00409340:246-251`), so the stick can put the cursor exactly on each icon and the magnet then
holds it there. `tests/select_psp_test.cpp` pins the distances, the clamps, the appended order and
the sixteen original cells.

**Draw order** is `kSelectRosterOrder`, whose original sixteen entries are untouched and which
appends 16, 17, 18 — so the three are drawn last and nothing about the sixteen's reveal timing
moves (slot *i* still takes its first 0.1 step on tick *i*+6; the three follow the same rule, a
port extension, so slot 18 settles on tick 33 instead of 30).

**Captures.** `tests/scripts/psp-select.txt` drives one 1v1 selection onto Satoshi and starts a
match, which is how the screens were inspected:

```bash
./build/linux/daybreak --headless --no-audio --install=Higurashi-Daybreak \
  --psp-data=psp-data --screen=title --script=tests/scripts/psp-select.txt \
  --frames=200 --size=800x600 --out=select.ppm     # the diamond with all 19 icons
./build/linux/daybreak ... --frames=800 --size=800x600 --out=vs.ppm   # the VS screen
```

## 4. Generating the art: `tools/asset-tools/psp_select_art.py`

The reference generator. It reads the PSP's own 2D art and writes the files in §2 as CNV images
(`src/assets/cnv.h`: 17-byte header, then BGRA rows top-down — the product's one texture container,
so no PNG path and no texture pack is involved).

```bash
python3 tools/asset-tools/psp_select_art.py --iso=<Higurashi PSP.iso> --out=psp-data
python3 tools/asset-tools/psp_select_art.py --pack=<PSP_GAME/USRDIR/_pack/gzpack.pck>
python3 tools/asset-tools/psp_select_art.py --dump=<dir of extracted gra/gim/select/*.gim>
```

`--preview=<dir>` also writes PNG copies for the eye; `--only=17` builds one character. The dump
studied for the PSP notes has ISO sha256 `170b8a8e1aa546f549809243d68dd4c34e33f69e682ab669e82018
0830a7160c`, but the tool only needs *a* good dump: the pack is resolved by the ISO's own directory
tree, and entries by `crc32(path, 0xFFFFFFFF)`.

What it reads, and what it can honestly produce:

| Output | PSP source | Transform |
|---|---|---|
| `NN.cnv` | `gra/gim/select/vs_enter_<name>.gim` (176 × 132, one pose) | alpha-bounds crop, uniform box-filter resize to fit 256 × 256, pasted **bottom-centre** |
| `iNN.cnv` | `gra/gim/select/icon_on.gim` — 4 × 5 grid of 48 × 48, roster order | the character's cell (index = roster index), isolated specks dropped, resized to ≈64 × 60, drawn on a procedurally drawn green floor tile in each of the five art cells; cell (2,1) filled white |
| `cosNN.cnv` | the same icon | the same cell, repeated once per costume cell, `kSelectCostumes` cells used |
| `wNN.cnv` | *(nothing)* | place-holder plates: seven-segment slot letter (A–D) in column 0, the item id in column 1 |

**The three place-holders are honest limitations, not recovered layout.** The PSP has no chibi
body, no per-costume picture and no per-weapon picture: its own select screen is a list of text
names beside those 48 × 48 icons (`gra/gim/select/costume.gim` and `weapon.gim` are text atlases).
So the PC's chibi/costume/weapon cells cannot be reproduced from PSP art at all. Each generated
cell says so where it is drawn in the tool, and Track A may replace any of them: the contract is
the size and the cell grid, not the picture.

The portrait *is* the PSP's own art and needs no disclaimer: `vs_enter_<name>.gim` is the image the
PSP's versus screen shows for that character.

**Name spelling trap** (from the art study): the pack spells four characters differently in the two
families — `bustup_sion` but `vs_enter_shion`, `bustup_hanyuu` / `vs_enter_hanyu`, `bustup_natsumi`
/ `vs_enter_natumi`. The three this document covers agree everywhere: `satoshi`, `miyoko`,
`okonogi`.

## 5. What happens when a file is missing

The new art is **optional, per character, per file**. That is a deliberate change from the PC
sixteen's rule, where one missing sheet refuses the whole screen:

* `SelectScreen::loaded()` requires the ten shared sheets and all four sheets for indices 0–15,
  exactly as before. For 16–18 a missing sheet logs `[select] data/select/i17.cnv: …` on stderr and
  draws nothing for that one icon.
* `VsScreen::loaded()` requires `data/vs/vs01..03` and `data/select/p03`, and a portrait only for a
  PC participant. A missing PSP portrait leaves that portrait out; the name plate and the combo
  caption still identify the fighter.
* The name plates need the caption font; without it the screens draw no name (the portrait still
  identifies the fighter) and say so on stderr.
* The **battle launch** is where a missing *data* file (as opposed to art) is reported, and it is
  reported once, clearly, instead of crashing:
  `RESULT: front end: cannot read data/item/101.dat (Satoshi 0)`. The same holds for the fighter's
  own `data/<dir>/0k.dat` and model, which the core reports (Track C/E).
* The **result screen** refuses for a PSP winner, because `data/win/16a.cnv` … do not exist and
  have **no PSP source**: `gra/gim/result/` holds only shared UI art (back, button, hanko,
  key_word), no per-character portrait. The screen reports
  `data/win/16a.cnv is in no open bundle and on no filesystem path`. A future track can draw those
  three sheets in the PC style, or compose them from `vs_enter_<name>.gim`; until then a PSP
  fighter's victory portrait is an explicit, named failure rather than a wrong image.
* Win **quotes**: `data/scenario/win/` has scripts only for ids 0–17, and 16/17 are already Rena's
  and Rika's weapon-2 personas. A PSP winner therefore gets **no** script path at all
  (`planWinnerQuote` returns an empty pair), so a PSP fighter can never be shown another
  character's line; the result screen reports "no shipped victory quotation resolved".

## 6. Roster policy the screens and the launch follow

| Question | Answer | Where |
|---|---|---|
| Which characters does the selection offer? | 19 offline when the PSP data is mounted, 16 otherwise; **16 online** until every peer can be guaranteed the same `psp-data` (the plan's step 7) | `ui::selectableRosterCount` |
| May a random CPU pick one of the three? | **No.** The COM fill and the off-diamond random roll stay on the PC sixteen, so a random seat cannot fail a launch on data another track has not produced yet. A deliberate pick still can, and reports it (§5) | `main.cpp` random fill, `screen_select.cpp` rolls |
| Which item id does a slot launch with? | The roster table's: 1–46 for the PC, 101–112 for the three; bounds-checked, 0 when the pair is not one the tables define | `gameplay::rosterWeaponItemId` |
| Does story mode know them? | No. The ladder, the team page and the story fights stay on the PC sixteen | `story_ladder.h`, `screen_story_team.cpp` |
| Does the online bundle hash cover `psp-data`? | Not yet — which is why they are kept out of online selection (§ above). `game_data_hash` hashes the eight `daybreakXX.dat` bundles only | `net/lobby.cpp` |

## 7. Open items

* **Win portraits** for 16–18 have no PSP source (§5). Compose them or draw them in the PC style.
* **Weapon, costume and chibi cells** are place-holders (§4) because the PSP ships no such art.
* **The simultaneous hover bands**: any two icons 48/36 apart share a band where the earlier roster
  index wins. That is the original's own rule and the three new cells avoid it by 60 units; a future
  addition to the diamond must keep the same distance.
* **`psp-data` beside the executable** is the non-verification path and is exercised by an
  interactive launch (the `psp-data : <dir> (3 extra fighter(s))` startup line). Every capture in
  this document names the folder explicitly instead.
