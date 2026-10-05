# Asset catalog — stages, characters, costumes, weapons

> **Why this file exists.** The on-disk asset names are *misleading* and have
> already cost us days twice (`stage21` read as "stage 21"; the DX9 scene
> named `title` read as the title screen). This catalog replaces guessing:
> every entry below carries an **explicit human name**, the **on-disk
> identifier(s)** it maps to, an **evidence tier**, and the **trap** worth
> knowing. Where a name could not be established, the entry says
> `unresolved` and lists what was ruled out. **A wrong confident name is
> worse than an honest gap** — do not "fill in" an unresolved row from
> plausibility.
>
> All paths are written relative to the repo root, e.g.
> `Higurashi-Daybreak/data/stage01/`. Line-level provenance for the RE
> claims is given as `FUN_xxxxxx` / file offset so it can be re-checked.

---

## 0. Evidence tiers

Used explicitly in every table, strongest first:

| Tier | Meaning |
|---|---|
| `RE` | An address or `FUN_xxxxxx` in `research/decompiled/`, or a Shift-JIS/ASCII string inside the shipped data (`.X` texture names, `.ini`, `.txt`, bundle entry names). In-file strings are the strongest available signal — the schoolyard was pinned this way. |
| `print` | A reference capture in `remake/docs/reference/*.webp` that shows the name/likeness. Sub-case: a **shipped select-screen texture** that the capture is a photograph *of* — `data/select/{NN,iNN,cosNN,wNN}.cnv`, `data/talk/cNN-*.cnv`. These are the source art, so they are stronger than a capture; they are filed under `print` because they are images, not strings. |
| `filename` | Inferred from the asset path/naming convention only. **Unverified** — flagged inline. |

Two supporting techniques are used and named where they apply:
**render-and-look** (headless one-frame renders of a stage/character via the
foundation demo) and **texture-set clustering** (grouping stages by the
Shift-JIS texture names inside their `.X` files).

## 0.1 Which copy the game actually loads

The game reads **bundles first**: `Higurashi-Daybreak/daybreak00..07.dat`
in numeric order, **first match wins, case-insensitively**; the extracted
tree `Higurashi-Daybreak/data/` is the fallback
(`remake/foundation/src/assets/asset_source.{h,cpp}`,
`dat_bundle.{h,cpp}`; container format documented in
`remake/tools/asset-tools/extract_dat.py`). `daybreak03.dat` is absent from
this install.

Measured on this install (entry tables read directly, no extraction):

| Fact | Value |
|---|---|
| Distinct asset names across bundles | 11 261 |
| Files in the extracted tree | 11 248 |
| Names present **only** in bundles | 16 (13 `movie/*.mpg` + `movie/thumbs.db` + `data/voice/{akane,keiichi}/フォルダリスト.txt` ×2, the last two 0 bytes) |
| Names present **only** in the tree | 3 |
| Same name, **different byte size** in bundle vs tree | **214** |

So "the tree and the bundle are the same data" is false. Where a row below
matters and the two copies disagree, the table says so. The two divergences
that actually bite:

* `data/stage06/*` — the tree copy is **not** the shipped stage:
  `stage06/00.x` bundle 20 055 B vs tree 195 860 B; `stage06/01.x` bundle
  1 364 210 B vs tree 493 715 B; `stage06/env.dat` bundle **84 B** vs tree
  **156 B** (and only the bundle carries `stage06/env.ini`). `stage16` has
  no such divergence. Anything measured off the tree for `stage06` is
  suspect.
* Per-character data — e.g. `data/akane/00.x` bundle 10 965 964 B vs tree
  11 406 170 B, and the eye textures (`一目*.cnv`, `ひぐらし目.cnv`) ship at
  131 089 B in a bundle and 32 785 B in the tree. The character texture
  names listed in §3 were read from the **tree** copies; the *names* are
  stable across both, the byte sizes are not.

`data/rika/01.X` is the parent's measured example of the same effect
(9 675 158 B from bundles vs 9 893 738 B from the tree).

---

## 1. Stages

### 1.1 The naming scheme (this is the whole trick)

`data/stageNN/` is a **two-digit code, not a stage number**:

```
stageNN     N = time of day        N = scene
            0 = day                1 = schoolyard (Hinamizawa branch school, 校庭)
            1 = sunset / dusk      2 = village + rice paddies
            2 = night              3 = shrine grounds
                                   4 = mountain stream
                                   5 = riverbed / dumping ground
                                   6 = shrine, second area (upper / boarded floor)
```

Evidence for the split, all `RE` + render:

* **Texture-set clustering.** The Shift-JIS texture names inside each
  stage's `0N.X`…`06.X` are *identical strings* for the pairs
  `01/11/21`, `02/12`, `03/13`, `04/14`, `05/15`, `06/16` (md5 of the
  sorted name set matches exactly). So the second digit groups scenes and
  the first digit is a variant of the same scene — the sub-models differ in
  bytes but reference the same texture vocabulary.
* **`env.dat` fog colour** (dwords at offsets 8/12/16 = R/G/B, per
  `readEnv()` in `remake/foundation/src/assets/scene.h:253`, which mirrors
  `FUN_00650a30`). For **every** pair the `1x` variant turns
  red-dominant relative to its `0x` sibling, and `stage21` is near-black
  blue with a 6× shorter fog distance:

  | scene | `0x` fog RGB | `1x` fog RGB | `21` |
  |---|---|---|---|
  | 1 (schoolyard) | 77,100,120 | 90,50,47 | 15,20,50 (fogEnd 60 000 → 10 000) |
  | 2 (village) | 72,86,93 | 90,50,47 | — |
  | 3 (shrine) | 120,170,200 | 150,40,30 | — |
  | 4 (stream) | 130,190,185 | 150,40,30 | — |
  | 5 (riverbed) | 77,100,120 | 90,50,47 | — |
  | 6 (shrine upper) | 120,170,200 | 150,40,30 | — |

* **Render-and-look** (headless frame per stage). `stage01` = bright blue
  sky, school + village; `stage11` = the same buildings under an
  **orange/red sunset sky**; `stage21` = the same buildings under a **near
  black-blue night sky**; `stage02` = paddies/thatched roofs in daylight;
  `stage12` = the same paddies under an orange sky.

### 1.2 The 13 stage directories

| On-disk dir | Explicit name | Scene | Time of day | Evidence | Reference print |
|---|---|---|---|---|---|
| `data/stage01` | `schoolyard_day` | Hinamizawa branch school — **schoolyard** (雛見沢分校 校庭) | day (昼) | `RE`: the only scene whose texture set is the *complete* schoolyard set — 校庭砂05 / 校庭砂草小02 / 校庭芝08 / 校庭芝生中間9 (yard ground), 校舎ミニ窓02 / **校舎影02** (school building), 焼却炉05 (incinerator), 水飲み場小0 (water fountain), プレハブ壁05, 小屋板, マンホール, ガードレール03, くさむら. `print`: `stage-select-school.webp` names the stage 雛見沢分校 校庭 with variation 昼 over a school-building thumbnail. Render: daylight. | `stage-select-school.webp` |
| `data/stage11` | `schoolyard_sunset` | same schoolyard | sunset / dusk | `RE`: identical texture name set to `stage01`; fog RGB 77,100,120 → 90,50,47. Render: orange sky over the same buildings. | none |
| `data/stage21` | `schoolyard_night` | same schoolyard | **night** | `RE`: identical texture name set to `stage01`; fog RGB 15,20,50 and fogEnd 10 000 (vs 60 000). Render: dark blue night. | none |
| `data/stage02` | `village_paddies_day` | village + rice paddies (田圃 / 畑 / 藁葺き屋根 / 民家平屋 / ドブ板 / パイロン / 田園遠景 / 家遠景) | day | `RE`: textures. **Also references part of the school set** (校庭砂05, 校庭芝08, 校庭芝生中間9, 校舎ミニ窓02, 水飲み場小0) — the branch school is visible from here; see §1.3. Render: paddies + thatched houses, blue sky. | none |
| `data/stage12` | `village_paddies_sunset` | same village | sunset | `RE`: identical texture set to `stage02`; fog → 90,50,47. Render: orange sky over the paddies. | none |
| `data/stage03` | `shrine_grounds_day` | Furude-shrine grounds — torii, outdoor offering box, lanterns, cedars (鳥居1a/1b, 外賽銭箱1a, 赤灯籠, 灯篭石1, 杉林, 幕, 白壁, 神社模様) | day | `RE`: textures. Render: dark cedar grove + gravel. | none |
| `data/stage13` | `shrine_grounds_sunset` | same | sunset | `RE`: identical texture set; fog → 150,40,30. | none |
| `data/stage04` | `mountain_stream_day` | mountain stream / river in forest (川, 川砂利, 水飛沫, 白樺, シダ01, 山道, 沢石) | day | `RE`: textures. Render: dirt path + stone wall. | none |
| `data/stage14` | `mountain_stream_sunset` | same | sunset | `RE`: identical texture set; fog → 150,40,30. | none |
| `data/stage05` | `riverbed_dump_day` | riverside flats with dumped objects (1-river, river, riverside, kanban01/02 signboards, カーネル01, テレビ02, 白棚01, ドラム缶, パイロン, `fklift`) | day | `RE`: textures. Render: dry field with rusted debris. | none |
| `data/stage15` | `riverbed_dump_sunset` | same | sunset | `RE`: identical texture set; fog → 90,50,47. | none |
| `data/stage06` | `shrine_upper_day` | shrine complex seen from above, with the town/school below (鳥居1a/1b, 本体メイン, 本体屋根**赤**, 本体階段柱/石m, 杉林, 灯篭石1, 白壁, 神社模様, **床板**, **町**, **雲上01**) | day | `RE`: textures — the shrine vocabulary of scene 3 **plus** a high vantage set (床板 floor boards / 町 the town / 雲上01 above the clouds) **plus** the schoolyard ground and 校舎ミニ窓02 / 焼却炉05 / 水飲み場小0 from scene 1. So this is the shrine looking down over the school and village, not a separate indoor area. Tree `env.dat` is 156 B; **the bundle copy differs** (84 B) — see §0.1. | none |
| `data/stage16` | `shrine_upper_sunset` | same | sunset | `RE`: identical texture set to `stage06`; fog → 150,40,30. | none |

### 1.3 Stage traps

* **`stage21` is not "stage 21".** It is scene 1 (the schoolyard) at
  **night**, and it is the stage the DX9 remake hardcodes — which is why
  every comparison frame for days was the night variant while the reference
  prints show the day one. The day variant of the same scene is
  `stage01`; the sunset one is `stage11`. `stage12` is the **village** at
  sunset (scene 2), not the schoolyard.
* **There is no `stage22`…`stage26`.** Only scene 1 got a night variant.
  A loader that loops `stageNN` for N = 21…26 will fail on the tree.
* **`NNb.X` is not "model NN, version b".** `FUN_004011f0` loads
  `data/stageNN/%02d.x` for i = 0..7, **or `%02db.x` when the config byte
  `stage+0x2c` is set** — an alternative *sub-model set* for the same stage,
  selected by a flag. Where the pair is byte-identical (`stage21/01.X` vs
  `01b.X`, `stage04/04.X` vs `04b.X`) the flag is a no-op. `stage01`,
  `stage02`, `stage04` and `stage11` also have sub-models whose `b` partner
  is *absent* (`stage01` has no `03b.X`), so a `b`-set load must tolerate
  misses.
* **Sub-model numbering is per-stage, not global.** `stage02` has no
  `04b.X`; `stage04` starts at `07.X`/`07b.X`; `stage05`/`stage15` use
  `05.X`. What exists is whatever the stage ships — the loader walks
  00..07 and skips holes.
* **Case is inconsistent**: `stage04` and `stage14` store
  `collision_camera.x` lowercase, the other stages `.X`. Harmless on the
  bundles and on Windows (case-folding lookup) but fatal on a case-sensitive
  filesystem without a fallback.
* **Scene names for 2–6 are descriptive, not the game's own names.** Only
  scene 1's name (雛見沢分校 校庭) is read off a shipped screen. I found
  **no** stage-name string table in the exe, the tree or the bundles: the
  `.exe` contains no Shift-JIS character/stage names at all (verified by
  scanning for `雛見沢`, `分校`, `校庭`, `ランダム`, `竜宮`, `園崎`, … — zero
  hits), and the only in-file stage identifiers are the texture names used
  above. Treat `village_paddies_*`, `shrine_*`, `mountain_stream_*`,
  `riverbed_dump_*` as *our* names, and do not quote them as the game's.
* **The branch school is visible from more than one scene, so `校庭`/`校舎`
  textures alone do not identify a stage.** Measured distribution of the
  school textures: scene 1 has the full set (`校庭砂05`, `校庭砂草小02`,
  `校庭芝08`, `校庭芝生中間9`, `校舎ミニ窓02`, **`校舎影02`**, `焼却炉05`,
  `水飲み場小0`); scene 2 has the ground, the window and the fountain but
  **not** `校舎影02` / `焼却炉05`; scene 6 has the ground, the window, the
  incinerator and the fountain (it is the shrine looking down over the
  school); scenes 3, 4 and 5 have only `水飲み場小0` (an incidental shared
  texture) or nothing. Scene 1 is therefore the *schoolyard arena* because
  it carries the arena furniture (incinerator, water fountain, prefab wall,
  shed, manhole, guardrail, asphalt) together with the building — not
  because it is the only scene that mentions the school.
* **Time-of-day labels**: 昼 (day) is read off `stage-select-school.webp`.
  The sunset and night labels the select screen uses for the variation row
  were **not** captured — the row exists and shows 昼, so other values
  exist, but I have no print of them. `sunset`/`night` are our names for
  the measured lighting, with the fog-colour and render evidence above.

### 1.4 Directories that are **not** stages

| Dir | What it is | Evidence |
|---|---|---|
| `data/camera/` | Camera models. **Two files only**: `01.X` (8 084 B) and `a01.X` (4 875 B). The exe has exactly one camera path literal, `"data/camera/01.x"` — so `01.X` is the battle camera; nothing in the exe's `data/...` literals references `a01.X`, so its role is **unresolved** (an alternate camera, or an unused/superseded asset). | `RE`: path literals `"data/camera/01.x"`; dir listing |
| `data/object/` | **HUD / system sprite atlas**, not stage objects. `p00`–`p13` are UI art: `p00` digit + `%` glyphs and the blue/red team balloons, `p01`/`p02`/`p12` gauge frames and bars, `p03` HUD circular gauges, `p04` 撃沈！/開始！, `p05` 青組 大勝利, `p06` hit sparks, `p08` 赤組 大勝利, `p09` 3‑2‑1 countdown + 撃破！, `p13` a grey pad. Plus `logo.cnv`, `system.cnv`, 勝利バー.cnv, 勝利画面土台.cnv. | `print`/render: converted and inspected each icon | 
| `data/aura/` | **Shared effect models**: `00.X`–`06.x`, loaded as `"data/aura/%02d.x"`. Textures name them: `マズルフラッシュ(.2/.3)` (muzzle flash), `hitblue0000`, `hitC01`–`hitC05` (hit sparks), `炎上オーラ` (burning aura), `バケツ` (bucket). Not stages. | `RE`: path literal + texture names |
| `data/effect/` | Effect definitions, `"data/effect/%03d.dat"`. Not stages. | `RE`: path literal |
| `data/trail/` | Trail billboards, `"data/trail/%02d.bmp"`. Not stages. | `RE`: path literal |
| `data/bullet/` | Projectile/effect bundles — see §5. Not stages. | `RE` |

---

## 2. Characters

### 2.1 The character *index* (0–15) is a first-class identifier

Several shipped asset families are keyed by a character index `NN` ∈ 0…15,
**not** by the folder name. All of these use the same index order (verified
by reading the images/text and matching them to dialogue):

```
data/select/NN.cnv      character face portrait      (16 files, 00..15)
data/select/iNN.cnv     select-grid chibi sprite     (16 files)
data/select/cosNN.cnv   costume-panel icon           (16 files)
data/select/wNN.cnv     weapon-select text atlas     (16 files: 3 weapon names + blurbs)
data/talk/cNN-M.cnv     story standing portrait      (only NN = 00..13; M = pose)
data/win/NNa.cnv, NNb.cnv   victory art              (per index)
data/voice/%s..         voice sets, by folder name   (not by index)
```

`data/select/NN.cnv` is loaded by the literal `"data/select/%02d.bmp"`;
`i`/`cos`/`w` by `"data/select/i%02d.bmp"` / `cos%02d` / `w%02d`.

### 2.2 Index → character (the authoritative table)

Every row except 15 is pinned by a *name* appearing in shipped data or a
print; 15 is by elimination plus its own texture name.

| Idx | Folder | Japanese | Romanisation | Evidence | Trap / note |
|---|---|---|---|---|---|
| 00 | `data/rena` | 竜宮レナ | Ryūgū Rena | `print`: `weapon-select-rena.webp` shows 愛用の鉈 + 竜宮レ… nameplate, and `data/select/w00.cnv` contains exactly that blurb. `RE`: `data/talk/c00-*` = orange-haired girl; scenario `D01` has her かぁいい lines. Hair texture レナ髪の毛16. | — |
| 01 | `data/mion` | 園崎魅音 | Sonozaki Mion | `RE`: scenario `D18`/`D60` — the **elder** twin (idx 05 calls her お姉). Portrait `data/select/01.cnv` = green hair, sailor uniform with red ribbon. | See the mion/shion texture trap in §2.4. |
| 02 | `data/keiichi` | 前原圭一 | Maebara Keiichi | `RE`: `D01-0.txt` — idx 02 speaks 「レナ、リミッター解除だ！お持ち帰りを許可するぜ！！」. `data/select/w02.cnv` first weapon = 転校生のバット (transfer student's bat). | — |
| 03 | `data/satoko` | 北条沙都子 | Hōjō Satoko | `RE`: `D01-0.txt` haughty ojou line; weapon atlas `w03` contains **沙都子**のトラップ講座 — her name inside the weapon list. | — |
| 04 | `data/rika` | 古手梨花 | Furude Rika | `RE`: `D01-0.txt` 「……にぱ～☆」; `w04` = ritual implements (儀式用の鍬 / 祭具殿の鎌). | — |
| 05 | `data/shion` | 園崎詩音 | Sonozaki Shion | `RE`: `D18-0.txt` — idx 05 says 「ねぇお姉」 (younger twin); `D60` references her カンヅメ (cage) backstory. | — |
| 06 | `data/tomitake` | 富竹ジロウ | Tomitake Jirō | `RE`: `D39`/`D58` (always paired with Takano); `w06` = camera / 霊能写真撮影機 / サブマシンガン; texture 富竹眼鏡 (his glasses). Portrait has cap + glasses. | — |
| 07 | `data/takano` | 鷹野三四 | Takano Miyo | `RE`: `D58-0.txt` idx 07 is addressed as 鷹野さん; `w07` = 毒薬入り注射器 / 毒ガススプレー缶 / 支援用発信機. | — |
| 08 | `data/ohishi` | 大石蔵人 | Ōishi Kuraudo | `RE`: `D43` 「しつこい刑事たち」, `D59` 「署までご同行願いますよ」; `w08` = 愛用の拳銃 / 押収品倉庫; texture 大石髪の毛. | Folder is `ohishi` (not `oishi`). |
| 09 | `data/akasaka` | 赤坂衛 | Akasaka Mamoru | `RE`: `D43-1.txt` arrest line (道路交通法違反…逮捕します), always paired with Ōishi; `w09` = 波動/空手/刹那の極意書 (hand-to-hand secret manuals). | — |
| 10 | `data/irie` | 入江京介 | Irie Kyōsuke | `RE`: `w10` names him three times — 入江特製医療セット / 入院セット / 応援セット; `D51`/`D55` pair him with Chie as 先生方; texture 入江髪の毛. | — |
| 11 | `data/chie` | 知恵留美子 | Chie Rumiko | `RE`: `D34-0.txt` 「はぅ？知恵先生だー。」 and `D29` 「……知恵も…」; `w11` = 授業用T字定規 / コンパス / チョーク. | Given name first in the JP convention used by the game (`知恵 留美子`); `data/` folder uses the given name. |
| 12 | `data/kasai` | 葛西辰由 | Kasai Tatsuya | `RE`: `D59-0.txt` — Ōishi names him in full: 「園崎茜さん、葛西辰由さん。」. `w12` = ショットガン / マシンガン / スナイパーライフル. Texture 葛西眼鏡. | — |
| 13 | `data/akane` | 園崎茜 | Sonozaki Akane | `RE`: `D06-0.txt` self-introduction 「園崎ママ、園崎茜！ただいま見参ー！！」 and `D59` naming. `w13` = 無銘 / 玉弾き / 居合い刀 (she is a swordswoman in kimono). | Mion's and Shion's **mother** — 「おばさん」 in dialogue. |
| 14 | `data/hanyu` | 羽入 | Hanyu | `RE`: texture 羽入髪の毛; `w14` = 神の世界 / 鬼狩柳桜 (the god's world / the demon-slaying sword — unambiguously the god character). Folder link **by elimination**, like index 15. `print`: `data/select/14.cnv` = purple-haired girl in a red/white miko outfit. | Only **2** weapons, not 3. No `data/talk/c14-*`. |
| 15 | `data/natumi` | 夏美 | **Natsumi** | `RE`: texture 夏美髪の毛 names her. `w15` = おかーさんの包丁 / おばーちゃんの鎌. Folder link **by elimination**: the other 15 indices are name-pinned (§2.2) and there are exactly 16 character folders, so the one remaining folder takes the one remaining index. | Romanised **Kunrei-shiki** (`natumi`, tu = つ); searching for "natsumi" finds nothing. Only 2 weapons. **Surname unresolved** — no family name for 夏美 appears anywhere I searched. |

### 2.3 Model files inside a character folder

* The unsuffixed folder holds the **`.dat` descriptors**: `data/<char>/NN.dat`,
  built by `FUN_0041e180` as `"data/%s/%02d.dat"`. Each `.dat` begins with a
  dword `4` followed by a **260-byte NUL-padded model name** — the `.X` to
  load. The `.X` itself is **not** implied by the number.
* The `.X` numbering inside a folder is a **variant slot within one
  costume**, not a character index and not a LOD — and *which* file a slot
  loads is the name inside that slot's `.dat`, so the number does not always
  equal the slot (`rika/02.dat` names `00.X`). In a **base** folder the
  variants are texture-only: `data/rena/00.X`, `01.X`, `02.X` all report the
  same 4 meshes / 1964 vertices but render with different textures (`00`/`01` =
  white top with blue collar, `02` = yellow top). In a **costume** folder they
  can differ in geometry as well — `data/rena_B/01.X` = 5 meshes / 2050 verts
  but `data/rena_B/00.X` and `02.X` = 6 / 2124. Equal mesh counts do **not**
  mean "same model", and unequal ones do not mean "different costume".
* The **`.dat` index is the character's weapon slot 0–2** (resolved; it was
  open in the first edition of this file). It is *not* a LOD, pose or damage
  state, and it is not the costume. The chain, from the exe:

  1. `FUN_0064ab30` (VMA `0x64ab30`) loads one character per player slot and
     passes `FUN_0041e180(name, dat_index, ?, costume, ?)`; `dat_index` is the
     dword read at `obj + 0x5318 + slot*4` (`0x64ab94`, `0x64abec`). `obj` is
     the global scene object at **`0x6ca820`** (`mov $0x6ca820,%ecx` before the
     call, e.g. `0x406821`, `0x411c8d`), so the field is the global
     `0x6cfb38[slot]`.
  2. `LoadNextScene` fills that array from the **select screen's per-player
     weapon index**: `0x4066c8` stores `pGameState + 0x2e60 + slot*4` into
     `0x6cfb38[slot]`. The same loop stores `pGameState + 0x2e80` (a *different*
     selector, the costume) into `0x6cfb4c[slot]` = `obj + 0x532c`, which is
     `FUN_0041e180`'s costume argument — the `_B`…`_F` switch. For a random
     character the weapon slot is `rand() % 3` (`0x406736`) and the costume is
     forced to 0 (`0x406704`); the enemy team's slots 2 and 3 get their random
     weapon index in `FUN_006492f0` (`0x6493e7`, `0x64943b`, writing
     `obj + 0x5320` / `obj + 0x5324`, i.e. elements 2 and 3 of the same array).
  3. `FUN_0041e180` builds `data/%s/%02d.dat` with that index
     (`FUN_0041e180.c:58`) and reads a dword at file offset **0x114** — the
     **weapon id**, which it hands to `FUN_00433eb0` (`FUN_0041e180.c:227`),
     the function that opens `data/item/%03d.dat` (`FUN_00433eb0.c:51`).
     §3.3 is the resulting mapping.

  Consequence for a loader: the model variant is *per weapon slot* — the
  character is drawn with the `.X` its `<slot>.dat` names, so `rena` shows
  `00.x` with weapon 1, `01.X` with weapon 2 and `02.X` with weapon 3. The
  variants differ only in texture (measured), so a loader that ignores the
  index still gets correct geometry and the wrong textures.
* `.dat` → `.X` for the first slot (measured, tree copies):

  | char | 00.dat | 01.dat | 02.dat | | char | 00.dat | 01.dat | 02.dat |
  |---|---|---|---|---|---|---|---|---|
  | rena | 00.x | 01.X | 02.X | | rika | **01.X** | 01.X | 00.X |
  | mion | 00.X | 01.X | 01.X | | hanyu | **01.X** | 01.X | — |
  | natumi | 00.x | 00.x | — | | satoko | 00.X | 00.X | 00.X |
  | keiichi | 00.X | 00.X | 00.X | | others (akane, akasaka, chie, irie, kasai, ohishi, shion, takano, tomitake) | 00.X | 00.X | 00.X |

  `rika` and `hanyu` are the ones that break the "`.dat NN` → `NN.X`"
  assumption; a loader that guesses `%02d.X` gets the wrong model for both.
* Decoded `.X` filename case varies (`00.x` lowercase for `rena/00.dat`,
  `natumi/*`, `tomitake/*`). Harmless with a case-folding source; note it.

### 2.4 The `_B` … `_F` sibling folders are **costume slots**

`RE`, two independent confirmations:

* The original's loader, `FUN_0041e180`, switches the *directory* on the
  costume argument: `data/%s/%s` (0), `data/%s_B/%s` (1), `data/%s_C/%s`
  (2), `data/%s_D/%s` (3), `data/%s_E/%s` (4), `data/%s_F/%s` (5). So the
  letter is an **ordinal costume slot 0–5**, and the `.dat` (with the model
  name) always lives in the **unsuffixed** folder.
* The remake's `loadCharacter()` mirrors it from the jump table at
  `0x41ef86`; render logs confirm `--character=…/rena:0..5` resolve to
  `data/rena`, `rena_B`, `rena_C`, `rena_D`, `rena_E`, `rena_F`.

Consequences a reader must not get wrong:

* **Costume letters are not a shared vocabulary.** Rendering showed
  `rena_B` = **nurse** outfit, `rena_C` = gym kit, `rena_D` = school
  swimsuit, `rena_E` = frilled dark dress, `rena_F` = casual hoodie/shorts;
  `satoko_B` = **casual** (pink top + shorts), `satoko_C` = gym kit,
  `satoko_D` = school swimsuit, `satoko_E` = one-piece swimsuit,
  `satoko_F` = **maid**. So `_B` is *not* "nurse" — never key anything on
  the letter alone.
* Costume slots **can add geometry**, not just swap textures: `rena_B`
  reports 5 meshes / 2050 vertices against base `rena`'s 4 / 1964.
* A costume slot can be missing. Census of costume directories per
  character (0 = unsuffixed, so 6 = all slots present):

  | char | slots | char | slots | char | slots | char | slots |
  |---|---|---|---|---|---|---|---|
  | kasai | **1** (no costume) | mion | 6 | akane | 3 | chie | 4 |
  | akasaka | 2 | natumi | 6 | irie | 3 | hanyu | 5 |
  | ohishi | 2 | rena | 6 | keiichi | 4 | takano | 5 |
  | tomitake | 2 | rika | 6 | satoko | 6 | shion | 6 |

  Total 67 slot-directories. A UI that offers 6 costumes to everyone is
  wrong for 10 of the 16 characters.
* **All 67 slot-directories ship.** Measured against the *bundle* entry tables,
  not the tree: every costume directory's model file is present in a bundle
  (`data/rena_c/00.x`, `data/ohishi_b/00.x`, …), nearly all of them in
  `daybreak04.dat`. `data/ohishi_b/` is the bundle's own spelling — the
  bundle carries `data/ohishi_b/00.x` lowercase, so this is not a tree
  artifact.
* The **`.dat` descriptor is never inside a costume directory**:
  `data/ohishi_b/` has no `00.dat`. The loader always opens
  `data/<char>/NN.dat` and takes only the *model* from the costume directory.
  A census that counts `.dat` files per directory therefore sees 3 in
  `data/rena/` and 0 in `data/rena_C/` — that is correct, not a hole.
* Two **Photoshop source files ship** (bundle and tree): `data/keiichi/ひぐらし目.psd`
  and `data/ohishi_b/服2.psd`. Dead weight — no loader should read them.
* The **frill texture** is a reliable marker of the frilled/maid slot, and
  that slot sits **wherever the character's list puts it**:
  `フリル02.bmp` appears in `akane_B`, `chie_C`, `hanyu_E`, `keiichi_D`,
  `mion_E`, `natumi_E`, `rena_E`, `rika_F`, `satoko_F`, `shion_E`,
  `takano_D`. The other five characters (akasaka, irie, kasai, ohishi,
  tomitake) have no frill slot.
* **`ohishi_b` is lowercase**, its siblings are not. The exe asks for
  `data/%s_B/...`; this only works because both the Windows filesystem and
  the bundle lookup (`__stricmp` at `0x00663c20`) fold case. On a
  case-sensitive path with an exact-match resolver it breaks. Do **not**
  "fix" the folder name by editing the install, and do not treat the letter
  case as meaningful.

### 2.5 The folder-name trap that is *not* what it looks like

`data/mion/` (the base costume) references a texture named
**`詩音髪の毛05.bmp`** — *Shion's* hair — while `data/mion_B/` references
`魅音髪の毛05.bmp` (Mion's). The obvious conclusion "so `data/mion` is
Shion" is **not supported**: the two files are **byte-identical**
(md5 `48fcd6cd49cfbb9d61815122764b25c0`), i.e. one texture under two names.
Likewise `data/shion/詩音髪の毛.cnv` == `data/shion_B/詩音髪の毛05.cnv`
(md5 `975512c1dba0095b18f9efc787b7a4f8`). These are grayscale shading
masks, not identity badges.

**Rule:** texture *names* inside a model folder are weak identity evidence;
only counts once corroborated (dialogue, portraits, atlases). The identity
of `data/mion` as Mion rests on the **folder name**, the **voice folder
`data/voice/mion/`** and the index order (01 = elder twin per `D18`), not
on this texture.

### 2.6 Costume identification — all 67 slots

Every one of the 67 slot-directories is identified below from **two shipped
sources that agree row for row**:

* **render-and-look** — one headless frame per slot:
  `foundation_demo --headless --character=<install>/data/<char>:<N> --frames=1
  --out=… --size=512x512`, N = 0…5. `N` is the *ordinal* slot and the loader
  appends the letter itself — passing an already-suffixed directory
  (`…/data/rena_C:2`) loads **nothing**. The demo resolves assets
  **bundle-first** and prints the directory it resolved, e.g.
  `scene …/data/rena_C: 1 model(s), 3 meshes, 1779 vertices`; each slot's model
  file was confirmed present in a bundle (§2.4), so these are the shipped
  outfits, not tree copies. That log line is also where the geometry column
  comes from.
* **the shipped costume-icon atlas `data/select/cosNN.cnv`** — one 256×256
  sprite sheet per character index holding a **3×2 grid of chibi figures, one
  cell per costume slot in slot order** (cell 0 top-left … cell 5
  bottom-right). Like the other `.cnv` art it is stored bottom-up — `-flip` it
  before reading. Slots a character does not have are padded with a
  **byte-identical copy of cell 0**: counting distinct cells (by
  bounding-box-normalised pixel diff) gives 1 for `kasai`, 2 for
  `tomitake`/`ohishi`/`akasaka`, 3 for `irie`/`akane`, 4 for `chie`/`keiichi`,
  5 for `hanyu`/`takano` and 6 for the other six — **exactly the §2.4 directory
  census for all 16 characters**. So "the atlas has six cells" must never be
  read as "this character has six costumes".

Outfit names are ours (`print` tier: what the render shows, corroborated by the
matching chibi cell). `Δ` is against that character's slot 0.

**What the geometry column measures.** Each row is the model that slot N
actually loads when *both* selectors are N — the costume directory's copy of
the `.X` that slot's `.dat` names (`--character=<install>/data/<char>:N` drives
both, §2.3). Geometry is a property of the (costume, weapon slot) pair, not of
the costume alone: `data/rena_B` loads 5 meshes / 2050 verts for weapon slot 1
(`01.X`) but 6 / 2124 for slots 0 and 2 (`00.X` / `02.X`). Within a *base*
folder the variants are texture-only (`rena/00.X` = `01.X` = `02.X` =
4 / 1964). A preview that always loads `00.X` therefore looks right for the
default costume and wrong for several others.

| Slot dir | Outfit (what the render shows) | Meshes / verts (Δ) |
|---|---|---|
| `data/rena/` | school uniform — white sailor top, blue collar, blue pleated skirt | 4 / 1964 |
| `data/rena_B` | nurse — white dress + white cap | 5 / 2050 (+1 / +86) |
| `data/rena_C` | gym kit — white T-shirt + shorts | 3 / 1779 (−1 / −185) |
| `data/rena_D` | navy school swimsuit | 3 / 1807 (−1 / −157) |
| `data/rena_E` | dark frilled dress (フリル slot) | 4 / 2240 (+276) |
| `data/rena_F` | casual — blue/white top + shorts | 4 / 2034 (+70) |
| `data/mion/` | school uniform — white top, yellow tie, pink pleated skirt | 4 / 2096 |
| `data/mion_B` | casual — yellow T-shirt, blue jeans, white shirt tied at the waist | 4 / 1972 (−124) |
| `data/mion_C` | gym kit | 3 / 1856 (−1 / −240) |
| `data/mion_D` | navy school swimsuit | 3 / 1896 (−1 / −200) |
| `data/mion_E` | dark frilled dress (フリル slot) | 4 / 2327 (+231) |
| `data/mion_F` | casual — white top + red shorts | 4 / 1999 (−97) |
| `data/keiichi/` | school — white shirt + dark trousers | 3 / 1958 |
| `data/keiichi_B` | casual — dark red tank top, green shorts, red sneakers | 3 / 1935 (−23) |
| `data/keiichi_C` | gym kit — white T-shirt + navy shorts | 3 / 1953 (−5) |
| `data/keiichi_D` | **maid** — black dress, white apron, headdress (フリル slot) | 6 / 2532 (+3 / +574) |
| `data/satoko/` | green dress (default) | 4 / 1889 |
| `data/satoko_B` | casual — pink top + blue shorts | 3 / 1851 (−1 / −38) |
| `data/satoko_C` | gym kit | 3 / 1750 (−1 / −139) |
| `data/satoko_D` | navy school swimsuit | 3 / 1774 (−1 / −115) |
| `data/satoko_E` | blue one-piece swimsuit | 3 / 1935 (−1 / +46) |
| `data/satoko_F` | **maid** — black dress, white apron, headdress (フリル slot) | 5 / 2284 (+1 / +395) |
| `data/rika/` | school uniform — white top, red ribbon, dark skirt | 4 / 1965 |
| `data/rika_B` | green dress (casual) | 4 / 1749 (−216) |
| `data/rika_C` | gym kit | 3 / 1653 (−1 / −312) |
| `data/rika_D` | navy school swimsuit | 3 / 1590 (−1 / −375) |
| `data/rika_E` | shrine-maiden style — white top + crimson hakama | 3 / 1685 (−1 / −280) |
| `data/rika_F` | dark frilled dress (フリル slot) | 4 / 2069 (+104) |
| `data/shion/` | school uniform — white sailor top + navy pleated skirt | 4 / 2326 |
| `data/shion_B` | casual — cream striped sleeveless top, dark olive buttoned skirt, black pumps | 3 / 2134 (−1 / −192) |
| `data/shion_C` | gym kit | 3 / 2081 (−1 / −245) |
| `data/shion_D` | navy school swimsuit | 3 / 2098 (−1 / −228) |
| `data/shion_E` | dark frilled dress (フリル slot) | 4 / 2528 (+202) |
| `data/shion_F` | casual — white top + navy shorts | 4 / 2319 (−7) |
| `data/tomitake/` | default — cap, olive tank top, light trousers, glasses | 4 / 1637 |
| `data/tomitake_B` | green military-style uniform — jacket, shirt, tie (**provisional** label; the chibi cell shows epaulettes/medals) | 3 / 2006 (−1 / +369) |
| `data/takano/` | green cardigan, pink shirt, dark trousers | 4 / 1882 |
| `data/takano_B` | nurse — white dress + cap | 4 / 1903 (+21) |
| `data/takano_C` | black beret, dark jacket/coat, shorts, black knee-high socks (**provisional** label "winter/coat") | 7 / 2136 (+3 / +254) |
| `data/takano_D` | dark frilled dress (フリル slot) | 4 / 2236 (+354) |
| `data/takano_E` | pink two-piece swimsuit (bikini) | 3 / 1818 (−1 / −64) |
| `data/ohishi/` | default — grey shirt, red tie, red suspenders, khaki trousers, white shoes | 2 / 1681 |
| `data/ohishi_b` | blue yukata (directory name is lowercase, §2.4) | 3 / 1606 (+1 / −75) |
| `data/akasaka/` | default — cream jacket, dark shirt, blue trousers | 3 / 1886 |
| `data/akasaka_B` | blue yukata | 3 / 1930 (+44) |
| `data/irie/` | white lab coat + dark trousers (doctor) | 6 / 2060 |
| `data/irie_B` | casual — pale yellow shirt + light trousers | 4 / 1776 (−2 / −284) |
| `data/irie_C` | sports/cheer jersey — red body, white sleeves, white trousers (**provisional** label) | 4 / 1787 (−2 / −273) |
| `data/chie/` | white sleeveless dress / apron dress | 4 / 2229 |
| `data/chie_B` | dark navy long-sleeve dress, white collar, white cross armband — nurse-style (**provisional**) | 4 / 2344 (+115) |
| `data/chie_C` | dark frilled dress (フリル slot) | 4 / 2477 (+248) |
| `data/chie_D` | white two-piece swimsuit (bikini) | 3 / 2061 (−1 / −168) |
| `data/kasai/` | black suit + sunglasses — the only slot this character has | 4 / 1472 |
| `data/akane/` | black kimono + blue obi | 8 / 2195 |
| `data/akane_B` | dark frilled dress (フリル slot) | 5 / 2344 (−3 / +149) |
| `data/akane_C` | dark two-piece swimsuit (bikini) | 3 / 1931 (−5 / −264) |
| `data/hanyu/` | shrine maiden — white top + red hakama | 5 / 2266 |
| `data/hanyu_B` | school uniform — light blue sailor top + red plaid skirt | 6 / 2249 (+1 / −17) |
| `data/hanyu_C` | gym kit | 4 / 1976 (−1 / −290) |
| `data/hanyu_D` | navy school swimsuit | 4 / 1993 (−1 / −273) |
| `data/hanyu_E` | light-blue frilled dress (フリル slot) | 5 / 2471 (+205) |
| `data/natumi/` | white dress with orange trim and ribbon | 4 / 2185 |
| `data/natumi_B` | pink camisole top + navy plaid skirt | 4 / 2053 (−132) |
| `data/natumi_C` | gym kit | 3 / 1908 (−1 / −277) |
| `data/natumi_D` | navy school swimsuit | 3 / 1976 (−1 / −209) |
| `data/natumi_E` | dark frilled dress (フリル slot) | 4 / 2411 (+226) |
| `data/natumi_F` | casual — light top + red shorts | 4 / 2185 (±0) |

What the table establishes beyond the names:

* **The フリル slot is a family, not one outfit.** All 11 characters whose slot
  carries `フリル02.bmp` render as a frilled dress: `rena_E`, `mion_E`,
  `shion_E`, `rika_F`, `takano_D`, `chie_C`, `akane_B`, `natumi_E` (dark) and
  `hanyu_E` (light blue) — plus two **maid** variants with a white apron and
  headdress, `satoko_F` and `keiichi_D`. The texture is the reliable marker;
  the letter is not (§2.4).
* **A costume is a geometry change, not only a texture change.** The 67 slots
  run 2–8 meshes and 1472–2532 vertices. The largest are `akane` slot 0
  (8 meshes, kimono), `takano_C` (7), and `irie` slot 0 / `hanyu_B` /
  `keiichi_D` (6). Slot 0 is **not** the heaviest model for most characters —
  13 of 16 by vertex count and 6 of 16 by mesh count — so "default = the full
  model" is wrong.
* **Four rows are provisional** and marked above: the render shows the outfit,
  but the *label* is ours and another reading is possible — `chie_B`
  (nurse-style dark dress), `takano_C` (dark beret/coat), `irie_C`
  (sports/cheer jersey), `tomitake_B` (green military-style uniform). Every
  other row is unambiguous in the render **and** matches its chibi cell.
* **Costume index 0 is the unsuffixed directory**, not `_B`: the select
  screen's costume index maps 0 → `data/<char>/`, 1 → `data/<char>_B/` …
  5 → `data/<char>_F/` (`FUN_0041e180.c:68-86`). Do not "fix" a UI by
  shifting the list by one.

---

## 3. Weapons

### 3.1 How weapons are stored (and the answer to "is it in the character folder?")

**No.** A weapon is **never** a mesh inside `data/<char>/`. The chain is:

1. `data/item/NNN.dat` — weapon definitions, loaded as `"data/item/%03d.dat"`
   (`%03d` = the weapon id). There are 46: `001.dat` … `046.dat`. **The id is
   not picked by the UI directly**: it is a dword at offset **`0x114`** of the
   character's own `data/<char>/<weapon_slot>.dat`, read by `FUN_0041e180`
   (`FUN_0041e180.c:99-106`: re-open, seek `0x108` via `FUN_00653960.c:11`,
   then seven 4-byte reads) and handed to `FUN_00433eb0`
   (`FUN_0041e180.c:227`), which opens the item file. §3.3 is the resulting
   46-way mapping; §2.3 explains why the character `.dat` index is the weapon
   slot and not a LOD or pose.
2. `data/item/NNN.ini` — **plain-text** parameters for ids **001–028**
   (029–046 have none, in the tree *and* in every bundle — not a missing
   extraction). The `.ini` carries `bulletType`, `weaponType`,
   `gageTextureName`, `gageHeight0/1`, per-slot `[weaponN]` with
   `XFileName` + `TextureName` + attach offsets (`mx/my/mz`, `x1/y1/z1`),
   `[MagazineN]` ammo/reload/charge, and **`[BulletN]` records whose
   Shift-JIS trailing comments name the attack** (e.g. `[Bullet0];通常ナタ投げ横回転`).
   These comments are the single most useful string source for weapons — with
   two caveats: the `.ini` is a developer export that the engine never opens
   (the `.dat` is the shipped form of the same parameters), and for ids 009,
   013 and 026 its `XFileName` list is **stale** against the `.dat` that ships
   — see trap #22.
3. `data/item/NN.X` — the **held weapon meshes** (63 files: `00.X`–`80.X`,
   mixed case, plus `katana*.cnv` / `M870012.cnv` / `mp5.cnv` /
   `スタンガン.cnv` / `アイアン.cnv` / `ウォーターガン.cnv` / `ＲＰＧ.cnv` …).
   `"data/item/%s"` is a path literal in the exe.
4. `data/bullet/NNN/MMM.dat` — **projectile/impact bundles**, built by
   `FUN_005f80c0` as `"data/bullet/%03d/%03d.dat"` (inner file number =
   bulletId / 10). 46 directories `001`–`046`, each holding `000.dat` …
   `0NN.dat` **whose headers name a `.X` inside that bullet dir** (e.g.
   `data/bullet/001/000.dat` names `"03.X"`, not `"00.X"`) plus the effect
   `.cnv`s. The `.ini`'s `bulletType` equals the number of `[BulletN]`
   rows and selects this group.
5. **Attachment**: the weapon model hangs off the character rig's
   `Bip01_Prop1` (primary) / `Bip01_Prop2` frames; the per-weapon local offset
   (`mx/my/mz`, `x1/y1/z1`) is read from the item's own `.dat` by
   `FUN_00433eb0`. Not parsed by the remake — a weapon currently sits at the
   attachment bone itself.

So: **weapons are separate assets** (`data/item/` + `data/bullet/`), bound
to a character by a table, attached to a prop bone. The character `.X`
files contain only body/face/hair/cloth meshes.

### 3.2 The weapon list, by owner (the game's own names)

Source: `data/select/wNN.cnv`, the **shipped weapon-select text atlas** for
character index NN — 16 files, each holding that character's weapon names
and flavour text as rendered glyphs. Verified against the capture: the
panel in `remake/docs/reference/weapon-select-rena.webp` reads
**愛用の鉈** + 「血糊びの浮いた愛用の鉈 / 切れ味は鈍いが殺傷力は抜群！」, and
`data/select/w00.cnv` contains exactly that, over the 竜宮レナ nameplate.
Tier: `print` (shipped select texture — the source the capture shows).

Order in each cell = the select screen's weapon order (▲▼), which is also the
character's `.dat` index order (§2.3). **46 weapons total** for 16 characters:
indices 0–13 have three each, 14 and 15 have two. That 46 equals the 46
`data/item/NNN.dat` — a useful cross-check, but the *ids* are **not** in this
order (they run by weapon slot, not by character); §3.3 gives the id for each
row of this table.

| Idx | Owner | Weapon 1 | Weapon 2 | Weapon 3 |
|---|---|---|---|---|
| 00 | 竜宮レナ Rena | 愛用の鉈 *(favourite cleaver)* | 刃こぼれした斧 *(chipped axe)* | 鉄塊鉈 *(iron-lump cleaver)* |
| 01 | 園崎魅音 Mion | コテ拳銃 *(handgun)* | 特注の水鉄砲 *(custom water gun)* | 暴徒鎮圧放水銃 *(riot water cannon)* |
| 02 | 前原圭一 Keiichi | 転校生のバット *(transfer student's bat)* | 無敵アイアン *(invincible iron)* | 証拠隠滅シャベル *(evidence-disposal shovel)* |
| 03 | 北条沙都子 Satoko | 特選花火セット *(special fireworks set)* | 沙都子のトラップ講座 *(Satoko's trap course)* | 誘導花火セット *(guided fireworks set)* |
| 04 | 古手梨花 Rika | 儀式用の鍬 *(ceremonial hoe)* | 村鋭女用モップ *(mop)* | 祭具殿の鎌 *(sickle from the ritual storehouse)* |
| 05 | 園崎詩音 Shion | ゴシックナイフ *(gothic knife)* | 改造スタンガン *(modified stun gun)* | 地下祭具殿の鎌 *(sickle, underground storehouse)* |
| 06 | 富竹ジロウ Tomitake | サバイバルカメラ *(survival camera)* | 霊能写真撮影機 *(psychic photo camera)* | サブマシンガン *(submachine gun)* |
| 07 | 鷹野三四 Takano | 毒薬入り注射器 *(poison syringe)* | 毒ガススプレー缶 *(poison-gas spray can)* | 支援用発信機 *(support transmitter)* |
| 08 | 大石蔵人 Ōishi | 愛用の拳銃 *(favourite handgun)* | ハイパーアーム *(hyper arm)* | 押収品倉庫 *(confiscated-goods warehouse)* |
| 09 | 赤坂衛 Akasaka | 波動の極意書 *(wave secret manual)* | 空手の極意書 *(karate secret manual)* | 刹那の極意書 *(setsuna secret manual)* |
| 10 | 入江京介 Irie | 入江特製医療セット *(Irie's medical kit)* | 入江特製入院セット *(Irie's hospitalisation kit)* | 入江特製応援セット *(Irie's support kit)* |
| 11 | 知恵留美子 Chie | 授業用T字定規 *(classroom T-square)* | 授業用コンパス *(classroom compass)* | 授業用チョーク *(classroom chalk)* |
| 12 | 葛西辰由 Kasai | ショットガン | マシンガン | スナイパーライフル |
| 13 | 園崎茜 Akane | 無銘 *(unsigned sword)* | 玉弾き *(ball-deflector)* | 居合い刀 *(iaidō sword)* |
| 14 | 羽入 Hanyu | 神の世界 *(the god's world)* | 鬼狩柳桜 *(Onigari-no-Ryūō)* | — |
| 15 | 夏美 Natsumi | おかーさんの包丁 *(mum's kitchen knife)* | おばーちゃんの鎌 *(grandma's sickle)* | — |

Two of these are worth calling out because they name their owner inside a
*weapon* row — useful when a data row is all you have: `w03` contains
**沙都子**のトラップ講座 and `w10` contains **入江**特製… ×3.

### 3.3 Weapon ids ↔ (owner, weapon slot): resolved

**All 46 ids are pinned.** The mapping is in the character `.dat` files
themselves: each `data/<char>/NN.dat` carries the weapon id as a dword at
offset **`0x114`** (`FUN_0041e180.c:99-106` reads it, `:227` hands it to
`FUN_00433eb0`), and `NN` is the select screen's weapon slot (§2.3). Reading
that field out of all 46 files gives a **bijection onto 1…46** — no id claimed
twice, none missing, none out of range:

* ids **1–16** = weapon slot **0** of character indices 00–13
* ids **17–28** = weapon slot **1** of the same 14
* ids **29–32** = the two weapons each of Natsumi (29, 30) and Hanyu (31, 32)
* ids **33–46** = weapon slot **2** of the same 14

There is **no exe-side (character, slot) → id table to dump**, which is why
the first edition could not find one: `FUN_00433eb0` is the item *loader*
(`FUN_00433eb0.c:51` opens `data/item/%03d.dat` with the id it is handed), and
the id itself ships in the character `.dat`. Searching the exe for the 14
three-id triples (e.g. rena's 1/3/33 as little-endian dwords) finds nothing —
the expected result for a data-driven chain, not a missing table.

14 × 3 + 2 × 2 = 46, matching the 46 item files and the 46 names in §3.2. The
names below are the shipped weapon-select atlas names for that (owner, slot)
(`print`, §3.2); the corroboration column is `RE` string evidence from the
id's own files.

| id | Owner (char_index) | Slot | Weapon (atlas name) | Corroboration |
|---|---|---|---|---|
| 001 | rena (00) | 0 | 愛用の鉈 | `.ini`: 通常ナタ投げ / 必殺鉈; mesh `01.x` material `nata` + 鉈02.bmp |
| 002 | mion (01) | 0 | コテ拳銃 | `.ini`: ハンドガン / バズーカ / ガトリング + 覚醒; mesh `04.x` = a Tokarev pistol (トカレフ02.bmp) |
| 003 | rena (00) | 1 | 刃こぼれした斧 | `.ini`: 斧爆破 / ガソリン飛沫 / ケンタ砲; mesh `11.x` material `ono` (斧) |
| 004 | mion (01) | 1 | 特注の水鉄砲 | `.ini`: 通常水ショット / 収束水流砲; meshes `05.x`/`10.x`/`13.x` 水鉄砲.bmp / ウォーターガン.bmp |
| 005 | keiichi (02) | 0 | 転校生のバット | `.ini`: フルスイング打法 / バスター衝撃波; mesh `02.x` 金属バット08.bmp |
| 006 | shion (05) | 0 | ゴシックナイフ | `.ini` comments empty; mesh `14.x` material `knife` + ナイフ.bmp |
| 007 | rika (04) | 0 | 儀式用の鍬 | `.ini` names her: **梨花**ビームα / チャージショット; mesh `15.x` material `kuwa` (鍬) + 鍬.bmp |
| 008 | satoko (03) | 0 | 特選花火セット | `.ini`: ロケット花火 / パラシュート / まきびし; **no held mesh** (thrown fireworks) |
| 009 | ohishi (08) | 0 | 愛用の拳銃 | `.ini`: ハンドガン / **手錠投げ** (handcuffs); mesh `46.x` トカレフ02.bmp |
| 010 | akasaka (09) | 0 | 波動の極意書 | `.ini`: 波動弾 / 必殺波動弾; **no held mesh** (bare hands) |
| 011 | takano (07) | 0 | 毒薬入り注射器 | `.ini`: 毒注射弾 / 致死毒注射器; mesh `25.x` 注射器.bmp |
| 012 | tomitake (06) | 0 | サバイバルカメラ | `.ini` names him: **富竹**フラッシュカーニバル / 広域フラッシュ; mesh `16.x` カメラ.bmp |
| 013 | irie (10) | 0 | 入江特製医療セット | `.ini`: 注射器キャノン / 回復フィールド; meshes `26.x`/`45.x` 注射器Ｂ.bmp |
| 014 | chie (11) | 0 | 授業用T字定規 | `.ini`: 定規 / 火葬定規; mesh `42.x` 定規2.bmp |
| 015 | kasai (12) | 0 | ショットガン | `.ini`: ショットガン弾丸 / 狙撃弾丸; mesh `20.x` material `M870` + M870012.bmp |
| 016 | akane (13) | 0 | 無銘 | `.ini`: 交差剣閃 / 連閃 / ヨコウェーブ; meshes `30`–`32.x` material `katana` |
| 017 | satoko (03) | 1 | 沙都子のトラップ講座 | `.ini`: 設置ショット罠 / トラップ LV1–3 / 地球破壊爆弾; **no held mesh** (placed traps) |
| 018 | keiichi (02) | 1 | 無敵アイアン | `.ini`: クラブ投げ / 爆裂アイアン; mesh `40.x` アイアン.bmp (an iron bar) |
| 019 | rika (04) | 1 | 村鋭女用モップ | `.ini`: スプレー / 「汚物は消毒ですよ」; mesh `35.x` モップ.bmp + 催涙スプレー (36–38.x) |
| 020 | shion (05) | 1 | 改造スタンガン | `.ini` comments empty; mesh `41.x` スタンガン.bmp |
| 021 | tomitake (06) | 1 | 霊能写真撮影機 | `.ini`: フェイタルフレーム / 角材 / フレーム残像; mesh `44.x` カメラ02.bmp + `24.x` 角材01.bmp |
| 022 | takano (07) | 1 | 毒ガススプレー缶 | `.ini`: ガス弾小 / 毒ガス領域 / 必殺毒ガス種; mesh `25.x` (shared injector model) |
| 023 | ohishi (08) | 1 | ハイパーアーム | `.ini`: 通常投げ消費 / チャージ消費 / スタングレネード; **no held mesh** (the arm is the weapon) |
| 024 | akasaka (09) | 1 | 空手の極意書 | `.ini`: 風圧弾 / 竜口拳 / 真空波; **no held mesh** (bare hands) |
| 025 | chie (11) | 1 | 授業用コンパス | `.ini`: コンパス / 分度器 / 必殺ドリルキャノン; no distinct mesh (generic gun props) |
| 026 | irie (10) | 1 | 入江特製入院セット | `.ini`: メス左 / 右 / 拡散医療砲; meshes `47.x`/`48.x` 注射器C.bmp |
| 027 | kasai (12) | 1 | マシンガン | `.ini`: マシンガン弾丸 / ミサイルランチャー; mesh `28.x` material `tompson` (Thompson) |
| 028 | akane (13) | 1 | 玉弾き | `.ini`: 突き / 居合 / 縮地; meshes `21`–`23.x` material `katana` + katana.bmp |
| 029 | natumi (15) | 0 | おかーさんの包丁 | mesh `50.x` material `houtyou` (包丁) — a kitchen knife |
| 030 | natumi (15) | 1 | おばーちゃんの鎌 | mesh `53.x` のこぎり.bmp — the *mesh* is a saw; the display name is the atlas's |
| 031 | hanyu (14) | 0 | 神の世界 | **no held mesh** |
| 032 | hanyu (14) | 1 | 鬼狩柳桜 | mesh `52.x` textures **鬼狩.bmp / 鬼狩エフェクト02.bmp** — the mesh names the weapon |
| 033 | rena (00) | 2 | 鉄塊鉈 | mesh `102.x` material `nata` (鉈) + ドラゴン鉈.bmp — a heavy cleaver |
| 034 | keiichi (02) | 2 | 証拠隠滅シャベル | mesh `103.x` = shaft + blade; it reuses the kitchen-knife material/texture |
| 035 | mion (01) | 2 | 暴徒鎮圧放水銃 | mesh `05.x` ウォーターガン.bmp — a water gun |
| 036 | shion (05) | 2 | 地下祭具殿の鎌 | meshes `54.x` ×2 + `55.x` textured **鞭.bmp** (whip) — a segmented chain; the display name is a sickle |
| 037 | rika (04) | 2 | 祭具殿の鎌 | mesh `51.x` material `kuwa` + **鎌.bmp** — a sickle |
| 038 | satoko (03) | 2 | 誘導花火セット | **no held mesh** |
| 039 | ohishi (08) | 2 | 押収品倉庫 | meshes `12.x` (一斗缶, a can), `00.x` (バケツ, bucket / `kyatatu`), `40.x` (アイアン, iron bar), `41.x` (スタンガン) — a pile of confiscated junk |
| 040 | akasaka (09) | 2 | 刹那の極意書 | **no held mesh** |
| 041 | takano (07) | 2 | 支援用発信機 | no distinct mesh (shares `25.x`) |
| 042 | tomitake (06) | 2 | サブマシンガン | mesh `59.x` material `mp5` + mp5.bmp — a submachine gun |
| 043 | irie (10) | 2 | 入江特製応援セット | mesh `78.x` 注射器Ｄ.bmp — a syringe |
| 044 | chie (11) | 2 | 授業用チョーク | no distinct mesh (shares `42.x`, the ruler) |
| 045 | kasai (12) | 2 | スナイパーライフル | mesh `79.x` + **ドラグノフ.bmp** (Dragunov) — a scoped rifle |
| 046 | akane (13) | 2 | 居合い刀 | meshes `56`–`58.x` material `katana` + katana02.bmp — a katana |

**Two independent string sources agree with the pairing**, and neither was
used to *derive* it:

1. **The `.ini`'s own attack names** (`[BulletN];…`) describe the weapon's
   behaviour for 26 of the 28 ids that ship an `.ini` (006 and 020 have empty
   comment lists, and 029–046 have no `.ini` at all — see §3.1). The names
   land on the right owner: 手錠投げ (throwing handcuffs) on 009 = the
   detective's 愛用の拳銃; **梨花**ビームα on 007 = Rika; **富竹**フラッシュ
   カーニバル on 012; 設置ショット罠 / トラップ LV1–3 on 017; コンパス /
   分度器 on 025; ショットガン / 狙撃 on 015; マシンガン / ミサイル on 027.
   Where an id was pinned before this pass, the new mapping never contradicts
   it.
2. **The item mesh's material and `TextureFilename` strings** — the shipped
   `.dat` names the meshes and the meshes name themselves: M870012.bmp on 015,
   `tompson` on 027, mp5.bmp on 042, ドラグノフ on 045, 水鉄砲 on 004,
   スタンガン on 020, 注射器 on 011, カメラ on 012, 定規2 on 014, `katana` on
   016/028/046, 鎌 on 037, `houtyou` (包丁) on 029, 鬼狩 on 032, and
   バケツ / 一斗缶 / アイアン / スタンガン on 039. Rendering the meshes agrees
   (`102.X` = a heavy cleaver, `50.X` = a kitchen knife, `51.X` = a sickle,
   `05.X` = a water gun, `59.X` = an SMG, `79.X` = a scoped rifle).
   **But a mesh is not an owner key**: `08.X` (ＲＰＧ) and `09.X` (ガトリング)
   are generic props referenced by twelve different ids — see trap #23.
3. **The eight ids that name no mesh at all are exactly the eight atlas
   entries for a thrown, placed or bare-handed weapon**: 008 and 038
   (fireworks sets), 017 (trap course), 023 (hyper arm), 024 and 040 (karate /
   setsuna manuals), 031 (the god's world) and 010 (wave manual). 8 for 8 —
   a weapon you never hold is a weapon with no `XFileName`.

**What this corrects.** The first edition inferred *002 = Ōishi's 押収品倉庫*
from 002's multi-gun contents (`ハンドガン` / `バズーカ` / `ガトリング`, five
mesh slots). That is wrong twice over. 002 lives in `data/mion/00.dat`, so it
is **Mion's コテ拳銃** — a Tokarev-pattern pistol whose charge "awakens" into
the bazooka and gatling modes (`gageTextureName = mion_gage.bmp`) — and the
real **039** is the junk pile (can, bucket, iron bar, stun gun), which is what
押収品倉庫 means. Ōishi's three are 009 (Tokarev) / 023 (no held mesh) / 039
(junk pile) = 愛用の拳銃 / ハイパーアーム / 押収品倉庫 in atlas order, and
Mion's are 002 (handgun) / 004 (water gun) / 035 (water gun) =
コテ拳銃 / 特注の水鉄砲 / 暴徒鎮圧放水銃.

Two residual soft spots, stated rather than papered over: the **display
names** for 041 (支援用発信機), 044 (授業用チョーク) and 025 (授業用コンパス)
rest on the atlas alone — their meshes are shared or generic — and the mapping
assumes the atlas's row order *is* the select order. That assumption is what
the row-for-row corroboration above tests: for every character, `.dat` slot 0
and slot 1 both land on the atlas rows the `.ini`/mesh strings describe, so
the order is not in doubt; only the three atlas-only names above would move if
it were.

### 3.4 Reproducing the id mapping

No exe disassembly is needed for the mapping itself — the ids are in the data:

```python
import struct, glob, os
for char in ("rena","mion","keiichi","satoko","rika","shion","tomitake","takano",
             "ohishi","akasaka","irie","chie","kasai","akane","hanyu","natumi"):
    for f in sorted(glob.glob(f"Higurashi-Daybreak/data/{char}/*.dat")):
        slot = int(os.path.basename(f)[:2])          # 0,1,2 = the weapon slot
        wid  = struct.unpack_from("<I", open(f,"rb").read(), 0x114)[0]
        print(f"{wid:03d} <- {char} slot {slot}")
```

* This reads the **tree** copy for convenience. The same field was read out of
  **every bundle copy of these files** — 87 copies of the 46 `.dat`s across
  `daybreak00.dat` (28), `daybreak04.dat` (46) and `daybreak07.dat` (13), via
  the XOR-decoded entry tables as in `remake/tools/asset-tools/extract_dat.py`
  — and matches the tree value in all 87. The character `.dat` *sizes* differ
  between bundle and tree (§0.1); this field does not.
* The `.dat` layout used: dword version (`4`) at 0, 260-byte model name at 4,
  then at `0x108`/`0x10c`/`0x110`/`0x114`/`0x118`/`0x11c`/`0x120` the seven
  dwords `FUN_0041e180` reads after seeking to `0x108`; `0x114` is the weapon
  id and `0x120` is the count of the per-bone records that follow.
* Mesh and texture names for an id come from `data/item/NNN.dat` (ASCII
  strings: the gage `.bmp`, then `XFileName`/`TextureName` pairs), and the
  meshes' own texture names from the `.X` files — uncompressed ones with a
  `TextureFilename` regex, MSZIP ones (`xof 0303bzip0032`) via
  `webgpu-mvp/tools/x2txt.py` (its `convert()` returns the text form; do not
  edit `research/recomp/`, and do not run `generate_recomp.py`).

---

## 4. Trap list

Every identifier below has a wrong naive reading. This is the section to
read before writing new code or docs.

| # | Identifier | Naive reading (**wrong**) | Correct reading | Evidence |
|---|---|---|---|---|
| 1 | `data/stage21` | "stage 21" | **schoolyard at night** — scene 1, night variant. The DX9 remake hardcodes it, so all its frames are night while the prints show day. | texture set == `stage01`; fog RGB 15,20,50 + fogEnd 10 000; render |
| 2 | `data/stage01` / `data/stage11` | "stage 1" / "stage 11" | scene **1** (schoolyard) at **day** / **sunset**. `stage12` is scene **2** (village) at sunset, not the schoolyard. | §1.1 |
| 3 | `data/title/` (the DX9 scene literally named `title`) | the title screen | draws only `data/select/bg00.cnv`, the shared **select-screen panel background**. The real menu background is the shrine (`title-menu.webp`). | `remake/docs/reference/README.md`; path literals |
| 4 | `data/<char>_B` … `_F` | separate characters | **costume slots 1…5** of one character. The loader `FUN_0041e180` switches the dir on a costume index 0–5. | §2.4 |
| 5 | `data/ohishi_b` | a typo, or a different naming scheme | costume slot 1 of Ōishi, lowercase. Works because bundle lookup folds case (`__stricmp` `0x00663c20`) and Windows folds case. | dir census; §2.4 |
| 6 | `stageNN/NNb.X` | "version b of model NN" | an **alternative sub-model set** selected by the config byte `stage+0x2c` (`FUN_004011f0`) — not a second model, and sometimes byte-identical to its partner or simply absent. | `research/decompiled/FUN_004011f0.c` |
| 7 | `data/item/NNN.dat` | numbered by character, 3 per character | **not in character order** — 001 = Rena's cleaver, 002 = a multi-gun set, 003 = Rena's axe. | §3.3 |
| 8 | `data/<char>/NN.dat` | "the NN-th model of this character" | a **descriptor** whose 260-byte field *names* the `.X`; the number is a variant index, and `rika`/`hanyu` resolve to `01.X`, not `NN.X`. | §2.3 |
| 9 | `data/<char>/NN.X` | LOD / pose / damage variant | **texture variant of one costume** — identical geometry (rena: 4 meshes / 1964 verts for all three) with different textures. | render; parent's measurement |
| 10 | `data/mion/詩音髪の毛05.cnv` | "`data/mion` is really Shion" | the texture is **byte-identical** to `data/mion_B/魅音髪の毛05.cnv` — one file, two names. Texture names are weak identity evidence. | md5 `48fcd6cd…` both |
| 11 | `data/natumi` | "Natumi" | 夏美 = **Natsumi**; the folder uses Kunrei-shiki romanisation (tu = つ). Same family of spelling as `ohishi` for 大石. | texture 夏美髪の毛 |
| 12 | `data/object/p00…p13` | stage objects / stage thumbnails | **HUD and system UI sprites** — team balloons, gauges, digit glyphs, 青組大勝利 / 赤組大勝利 / 撃沈 / 開始 / 撃破 / 3‑2‑1. | converted and inspected |
| 13 | `data/aura/` | a character's aura | shared **effect models** (`"data/aura/%02d.x"`): muzzle flashes, hit sparks, burning aura, bucket. | exe path literal + texture names |
| 14 | `data/camera/` | a stage | camera models; the exe has exactly one literal, `"data/camera/01.x"`. `a01.X` is unreferenced by any `data/...` literal — role unresolved. | exe literals |
| 15 | the "40+ named animation sets" in `remake/docs/placeholders.md` §5 | an existing doc that is wrong (the suspicion) | The executable holds a 39-entry ASCII **voice-cue key** table at **VMA 0x6b73c0 = file offset 0x2b73c0**, 16-byte stride: `attackA/B/C`, `attackKO`, `backattack`, `backdamage`, `battlestart`, `damage`, `damagedown`, `damageKO`, `fire`, `guard`, `guarded`, `HPcheck`, `intercept`, `missdamage`, `nearLose`, `nearWin`, `oyashiro`, `oyashiroB`, `poison`, `provoke`, `recovery`, `reloadNG`, `reloadOK`, `revival`, `shotA/B/C`, `shotFinal`, `spark`, `specialA/B/C`, `tactics`, `tagback`, `tagfront`, `tagOK`, `thank`. `FUN_00431e70` uses these keys to construct `data/voice/<char>/<key>/%03d.wav`; the strings do not establish gameplay-state, animation, projectile-tier, or tag-swap meanings. Every shipped character `.X` names its `AnimationSet`s `Anim-1` … `Anim-124` (124 sets, `data/rena/00.X`, `rena_B/00.X`, `rika/01.X` all identical in this respect) with per-bone tracks `Anim-Bip00`, `Anim-Bip00_Pelvis`, `Anim-Bone06`, … The exe binds animation indices from each character's `.dat`. | measured: exe dump at 0x2b73c0; `FUN_00431e70`; `AnimationSet` name extraction |
| 16 | the address `0x6b73c0` | a file offset you can seek to | it is a **VMA**. `.data` sits at VMA 0x6b7000 / file 0x2b7000, so the file offset is **0x2b73c0**. Seeking to 0x6b73c0 finds nothing. | `objdump -h DaybreakDX.exe` |
| 17 | `data/stage06/*` in the tree | the shipped stage | the **tree copy differs from the bundle** (`00.x` 195 860 vs 20 055 B, `env.dat` 156 vs 84 B). Bundles win, so the tree copy is not what runs. | bundle entry tables; §0.1 |
| 18 | "the extracted tree is the game's data" | true | **214 names** have different sizes in a bundle than in the tree; 16 names ship only in bundles. Read via the asset source, not the tree. | §0.1 |
| 19 | `data/voice/` suffixes | `_B` like the model folders | voice uses **`data/voice/%s`** and **`data/voice/%sB`** (no underscore) in one path literal and `%s_B` / `%s_C` in others. The model folders use `_B`; the voice folders mostly do not. Two conventions for the same idea. | exe path literals |
| 20 | `data/select/P01.cnv` | consistent casing | capital `P`, while `p02.cnv`, `p03.cnv` are lowercase. Third case inconsistency in the tree (with `ohishi_b` and `NN.x`/`NN.X`). | dir listing |
| 21 | stages 1, 2 and 6 | three different places | all three reference the branch school's textures; scene 6 is the shrine looking **down over** the school and town (床板 / 町 / 雲上01), scenes 1 and 2 are the schoolyard and the paddies below it. Distinguishing them by "does it mention 校庭" does not work — see §1.3. | texture sets |
| 22 | `data/item/NNN.ini` | "the weapon parameters the engine reads" | a **developer export**, not a runtime file: only 28 of the 46 ids ship one (001–028, tree *and* bundles), the engine opens only `NNN.dat`, and for **009 / 013 / 026 the `.ini`'s `XFileName` list is stale** against the shipped `.dat` (009: `04.x` vs `46.x`; 013: `08.x` vs `45.x`; 026: `07.x`/`08.x` vs `47.x`/`48.x`). Take meshes from the `.dat`, attack names from the `.ini`. | compared all 28 pairs: 25 agree, 3 do not |
| 23 | a weapon's mesh, or `gageTextureName` | "this names the owner" | neither does. `08.X` (ＲＰＧ) and `09.X` (ガトリング) are **generic props referenced by twelve ids**, and the four gage textures are gauge *styles*. Reading 002's Tokarev/RPG/gatling contents as Ōishi's 押収品倉庫 is exactly this trap: 002 is Mion's コテ拳銃 and 039 (can / bucket / iron bar / stun gun) is the warehouse. Owner = the folder whose `<slot>.dat` carries the id. | §3.3 |
| 24 | `data/select/cosNN.cnv` | "a costume icon; 16 files = 16 costumes" | one **3×2 chibi grid per character index**, one cell per costume slot in slot order, stored bottom-up (`-flip`). Unused slots are padded with a **byte-identical copy of cell 0** — measured: kasai 1 distinct cell, tomitake/ohishi/akasaka 2, irie/akane 3, chie/keiichi 4, hanyu/takano 5, six characters 6. Counting cells over-counts; the file index is the character, never a costume. | §2.6 |
| 25 | exe byte table at VMA `0x6b71c0` (file `0x2b71c0`) | "the per-character costume count" | it is the **select screen's costume-cycle bound**: `0x4071a9`/`0x4071ee`/`0x40720e` divide the costume index (`pGameState + 0x2e80`) by `table[char]`, so the reachable indices are `0 … table-1`. The values are `[5,5,3,5,5,5,2,4,2,2,3,3,1,2,4,5]` — the shipped directory count **minus one** for 11 of 16 characters (so e.g. `rena_F` is unreachable through that cycle) and the full count for kasai/irie/akasaka/ohishi/tomitake. It agrees with neither the directories nor the atlas (which agree with each other). Do not use it as a costume count; see §6. | disassembly `0x40718a-0x407226`; §2.6 census |
| 26 | `data/<char>/NN.dat` | "the NN-th weapon of this character" | `NN` is the **weapon slot** (0–2) chosen in the select screen, and the *item id* is a separate dword at `0x114`. Reading the index as the id asks for `data/item/000.dat`, which does not exist. | §2.3, §3.3 |
| 27 | `data/<char>_B/00.dat` | "each costume folder carries its own descriptor" | costume folders carry **no `.dat` at all** (measured across all 67); the descriptor always comes from `data/<char>/NN.dat` and only the *model* is fetched from the costume folder. This is why `data/ohishi_b/` (lowercase) works despite having no `.dat`. | §2.4 |
| 28 | `data/keiichi/ひぐらし目.psd`, `data/ohishi_b/服2.psd` | "an asset the game reads" | **Photoshop source files** that ship in the bundles and the tree. No exe path literal or data file references them. | bundle entry tables; literal scan |

---

## 5. Naming convention going forward

Stop using raw directory names in code, comments and docs. Use these.

**Stages** — `<scene>_<timeofday>`; time of day is one of `day`,
`sunset`, `night`.

```
schoolyard_day       = data/stage01     schoolyard_sunset = data/stage11   schoolyard_night = data/stage21
village_paddies_day  = data/stage02     village_paddies_sunset = data/stage12
shrine_grounds_day   = data/stage03     shrine_grounds_sunset  = data/stage13
mountain_stream_day  = data/stage04     mountain_stream_sunset = data/stage14
riverbed_dump_day    = data/stage05     riverbed_dump_sunset   = data/stage15
shrine_upper_day     = data/stage06     shrine_upper_sunset    = data/stage16
```

Where the game's own stage name is known, carry both: the schoolyard is
`schoolyard` = 雛見沢分校 校庭; the other scene names are ours (§1.3). In
code, prefer a symbolic constant over a literal directory name so the
`stageNN` → scene mapping lives in exactly one place.

**Characters** — `snake_case` romanisation of the *given* name as used by the
`data/` folder, plus the full Japanese name where a human reads it:

```
rena = data/rena      竜宮レナ (Ryūgū Rena)
mion = data/mion      園崎魅音      shion = data/shion   園崎詩音
keiichi = data/keiichi  前原圭一    satoko = data/satoko  北条沙都子
rika = data/rika      古手梨花      hanyu = data/hanyu   羽入
tomitake = data/tomitake  富竹ジロウ   takano = data/takano  鷹野三四
ohishi = data/ohishi  大石蔵人      akasaka = data/akasaka  赤坂衛
irie = data/irie      入江京介      chie = data/chie   知恵留美子
kasai = data/kasai    葛西辰由      akane = data/akane   園崎茜
natumi = data/natumi  夏美 (Natsumi)
```

**Costumes** — `costume = default | B | C | D | E | F`, an ordinal into the
character's own list, mapping straight onto the directory suffix:

```
costume=default -> data/<char>/      costume=B -> data/<char>_B/   … costume=F -> data/<char>_F/
```

Never write "the nurse costume" as `_B`; write
`costume=B  # ナース服 (measured)`. Always state the character, because the
letter means different outfits for different characters (§2.4).

**Characters in an index-keyed context** — say `char_index`, never
"character number", and never confuse it with a folder name or a `.X`
number:

```
char_index = 0..15   # the select-screen order; keys data/select/{NN,iNN,cosNN,wNN}.cnv,
                     # data/talk/cNN-*.cnv, data/win/NNa|b.cnv
```

**Weapons** — `<owner>/weapon<slot>` with the Japanese name in the label, plus
the `data/item/NNN.dat` id wherever a file has to be named:

```
rena/weapon0  = 001 愛用の鉈          rena/weapon1  = 003 刃こぼれした斧
irie/weapon0  = 013 入江特製医療セット  chie/weapon1  = 025 授業用コンパス
hanyu/weapon1 = 032 鬼狩柳桜
```

(slot order = the select screen's ▲▼ order = the character `.dat` index order,
§3.2/§3.3; a two-weapon character has no `weapon2` — Hanyu and Natsumi only.
Never key on the id's numeric order: it runs by weapon slot, not by character,
so 001/002/003 are not one character's three weapons.)

**Stage sub-models** — `submodel <i>` plus `alternate=true|false` for the
`b` set; never call the `b` file "model NN b".

**Rule of thumb:** any time a new name is needed, it must be written down
here with its evidence tier before it is used in code.

---

## 6. Unresolved entries

Counted honestly; each row lists what was ruled out so the next attempt does
not repeat it.

| # unresolved | What | Why unresolved / what was ruled out |
|---|---|---|
| 5 | Game-official names for stage scenes 2–6 (`village_paddies`, `shrine_grounds`, `mountain_stream`, `riverbed_dump`, `shrine_upper`) | No string table exists: the exe holds **no** Shift-JIS stage/character names (scanned `雛見沢`, `分校`, `校庭`, `ランダム`, `竜宮`, `園崎`, `神社`, `田`, `村`, … — zero hits); the tree and bundles hold no stage-name file. Ruled out: `data/scenario/*.txt` (dialogue only, no stage names), `data/object/p*` (HUD, not thumbnails), `data/scenario/teamNN.dat` (39 dwords, values 0–38 — not stage names). |
| 2 | The select screen's own labels for the sunset and night variations | The variation row exists and shows 昼 (`stage-select-school.webp`); no capture of the other values. Ruled out: no variation-name string anywhere in the data. |
| 1 | Which `stageNN` the `stage-select-school.webp` print is actually showing | The print carries the name and the 昼 variation but **not** the id. `stage01` is the best fit (day variant; the full schoolyard set incl. `校舎影02` + `焼却炉05` + arena furniture, matching the print's school-building thumbnail), but scenes 2 and 6 also reference school textures, so the binding is inference, not read-off. |
| 1 | The exact in-fiction split between scene 3 (`shrine_grounds`, offering box / curtain / red lanterns) and scene 6 (`shrine_upper`, floor boards / red roof / town below) | Both are the shrine complex with a shared texture vocabulary and distinct sets; the vantage reading of scene 6 is inferred from 床板/町/雲上01 plus the render, and `stage06`'s tree copy diverges from the bundle. |
| 4 | Costume rows identified but **provisional** — `data/chie_B` (nurse-style dark dress), `data/takano_C` (black beret + dark coat), `data/irie_C` (sports/cheer jersey), `data/tomitake_B` (green military-style uniform) | The render is unambiguous about the *garment* and its `cosNN.cnv` chibi cell agrees, but the label is ours and a second reading is defensible: chie_B's white cross armband could be a school-nurse or a matron dress; takano_C's coat could be a raincoat or a winter coat; irie_C's red jersey could be a cheer, baseball or PE top; tomitake_B's jacket could be a suit rather than a uniform. Recorded as seen rather than guessed — §2.6. |
| 1 | Why the select screen's costume cycle cannot reach the **last** costume of 11 characters | The cycle bound is the exe byte table at `0x6b71c0` (read at `0x4071a9`/`0x4071ee`/`0x40720e` inside `FUN_00406850`), which is *shipped costume directories − 1* for rena, mion, keiichi, satoko, rika, shion, takano, chie, akane, hanyu and natumi (so `rena_F` is unreachable through it) and the full count for kasai, irie, akasaka, ohishi, tomitake. Either those last slots are reached another way (unlock, another menu) or the table is off by one in this build. The directories and `data/select/cosNN.cnv` agree with each other and are the authority for what *exists*; what the menu *offers* is unresolved. |
| 4 | `data/camera/a01.X` (role), whether the `a` prefix is a variant flag, and the value of the config byte `stage+0x2c` that switches the `b` sub-model set | Only `"data/camera/01.x"` is referenced by an exe literal; the `b`-set flag byte is documented in `scene.h` from `FUN_004011f0` but I did not trace what writes it. |
| 1 | Surname of 夏美 (index 15 / `data/natumi`) | Only the given name appears (texture `夏美髪の毛`, and no dialogue — index 15 has no `data/talk` portraits and no scenario lines). The folder name is the only romanisation source. |
| 2 | The index ↔ folder link for indices **14** (`hanyu`) and **15** (`natumi`) | By elimination: 14 of the 16 indices are name-pinned and there are exactly 16 character folders, so the two left take the two remaining indices. Corroborated for 14 by the weapon semantics (神の世界 / 鬼狩柳桜) and for 15 by the given-name texture 夏美髪の毛, but **not** read off a shipped index+name pair. |
| 1 | A **texture-based** identity check for the Sonozaki twins (unresolved as a method, not as an identity) | The twins' identities are settled by folder name, voice folder and twin-age dialogue (`D18`), but *not* by the textures: `mion/詩音髪の毛05.cnv` and `mion_B/魅音髪の毛05.cnv` are byte-identical (md5 `48fcd6cd…`), so no texture-name test can tell the folders apart. Do not try to re-derive it from textures. |

**Total unresolved: 22 items**
(5 + 2 + 1 + 1 + 4 + 1 + 4 + 1 + 2 + 1). The two families that dominated the
first edition are **closed**: the 55 unidentified costume slots (§2.6) and the
31 unpinned weapon ids (§3.3), plus the `.dat` variant question — the index is
the weapon slot (§2.3). What is left is small and specific. No row in this
document is filled in from plausibility.

---

## 7. What was checked, and how

So the next agent can re-run instead of re-deriving:

* **Bundle vs tree.** Read the entry tables of `daybreak00,01,02,04,05,06,07.dat`
  directly (uint16 count + `count × 0x10c` XOR-decoded entries) and diffed
  against an `os.walk` of `Higurashi-Daybreak/data/` — §0.1. No extraction
  was performed, so no game bytes were copied.
* **In-file strings.** Stage and character identity came from
  `TextureFilename` strings inside `.X` files. For uncompressed
  (`xof 0303bin`) assets the framing is
  `TextureFilename\n\x00\x02\x00` + 4-byte LE length + CP932 bytes —
  a plain regex over the raw file. For MSZIP assets
  (`xof 0303bzip0032`) convert first with `webgpu-mvp/tools/x2txt.py`.
* **Path literals as an inventory.** `grep -rho '"data/[^"]*"' research/decompiled/*.c`
  gave the authoritative list of asset families (`data/stage` (via
  `%s/%02d.x`, `%s/%02db.x`, `%s/env.dat`), `data/item/%03d.dat`,
  `data/bullet/%03d/%03d.dat`, `data/aura/%02d.x`, `data/effect/%03d.dat`,
  `data/trail/%02d.bmp`, `data/camera/01.x`, `data/select/…`, `data/win/%02da|b.bmp`,
  `data/talk`, `data/voice/%s[BC]`, …) — cheaper and more complete than
  guessing directories.
* **Shift-JIS scans.** Targeted `bytes.find('…'.encode('cp932'))` over the
  exe and the data tree for ~90 candidate terms (stage/place names,
  character names, weapon words, costume words). This is what disproved the
  existence of any exe-side name table. A naive CP932 "printable run" scan of
  the exe `.text` is useless — executable code decodes to kanji; do not
  repeat it.
* **Render-and-look.** One headless frame per stage (`--stage=`), one per
  costume slot (`--character=<install>/data/<name>:<N>`, N = 0…5 — the *base*
  directory plus the ordinal; an already-suffixed directory loads nothing),
  one per weapon mesh (`--model=<install>/data/item/NN.X`), plus the
  `data/select` and `data/object` icons converted with
  `remake/tools/asset-tools/cnv_convert.py` and viewed. All 13 stages, all 16
  index portraits, weapon/costume icon sheets, **all 67 costume slots** (a
  chibi-cell ↔ render comparison per character), and the 18 weapon meshes whose
  own names were not decisive.
* **The costume-icon atlas as a second source.** `data/select/cosNN.cnv` is a
  256×256, 3×2 chibi grid per character index, one cell per costume slot,
  stored bottom-up. Convert with `cnv_convert.py`, `-flip`, split into six
  cells, and compare the cells **after normalising each figure to its own ink
  bounding box** — a raw pixel diff between cells reports large differences for
  identical figures that sit at different offsets in their cell. Unused slots
  are byte-identical to cell 0, which is how the per-character costume count is
  read off the atlas. Cross-checked against the §2.4 directory census: 16/16
  characters agree.
* **The exe as a data source.** `objdump -d Higurashi-Daybreak/DaybreakDX.exe`
  (VMA → file offset = `vma − 0x400000`, `.data` at VMA 0x6b7000) is what
  resolved the item-id chain: the scene object is the global `0x6ca820`, its
  weapon-slot array is `0x6cfb38[4]` (`obj+0x5318`), filled from
  `pGameState + 0x2e60` in `LoadNextScene` (`0x4066c8`), while the costume
  selector is `pGameState + 0x2e80` → `obj+0x532c` (`0x4066f6`). Static tables
  worth dumping again: `0x6b710c` (team composition per scenario),
  `0x6b71c0` (costume-cycle bound), `0x6b7100` (scenario → `teamNN.dat`).
* **The character `.dat` as a key–value file.** dword `4` at 0, 260-byte model
  name at 4, then seven dwords at `0x108…0x120` (weapon id at `0x114`) and a
  per-bone record array whose count is at `0x120`. Read the same field from the
  bundle copies to confirm the tree copy is not a variant — §3.4 has the code.
* **The item `.dat` / `.X` pair as an identity oracle.** `data/item/NNN.dat`
  holds ASCII `XFileName`/`TextureName` pairs; the meshes those name carry
  their own `Material` names and `TextureFilename` strings (M870012.bmp,
  `tompson`, mp5.bmp, ドラグノフ, 鎌, 包丁, 鬼狩, …). This is the second,
  independent source in §3.3 — and the place where "a mesh names the owner"
  was disproved (trap #23).
* **Select-screen text atlases.** `data/select/wNN.cnv` are 512×512 text
  atlases drawn bottom-up; convert, `-flip`, crop the text band and upscale
  (~3–4×) to read. This is the source of §3.2 and of the weapon-blurb check
  against `weapon-select-rena.webp`.

* **Dialogue as an identity oracle.** `data/scenario/D*-*.txt` are CP932
  plain text with `character cNN-M.bmp` + `front N` + a line. Cross-indexing
  names mentioned against speaker indices, plus self-introductions
  (`D06-0.txt`: 「園崎ママ、園崎茜！」; `D59-0.txt`: 「園崎茜さん、葛西辰由さん。」;
  `D34-0.txt`: 「知恵先生だー。」), is what pinned indices 06–13.
* **Verification of a prior doc.** `remake/docs/placeholders.md` §5 was
  re-derived from data rather than trusted — see trap #15. It is
  substantially correct; what needed fixing was the *nature* of the 39
  names (exe state keys, not model animation sets).

### Not copied, not modified

No game asset bytes, screenshots or extracted files were added to the repo.
Scratch work for the pass that closed §2.6 and §3.3 (renders, montages, bundle
reads, item-mesh conversions) stayed under `/tmp`; the only derived files
inside the install are the `.bmp`s that `cnv_convert.py` writes next to the
`data/select` `.cnv`s, which §7 of the first edition already documents. This
document is the only repo file that pass changed; the stage/character work of
the first edition is untouched. `remake/src/file_parser/x_model_loader.cpp`
was not touched, no `research/` file was touched, and `generate_recomp.py` was
not run.
