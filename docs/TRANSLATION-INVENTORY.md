# Translation inventory

What a translation of the menus and the HUD has to replace. Read from the install's sheets on
2026-10-30, by eye, so counts are approximate. The netplay sheets (`data/network`, `data/chat`) were
not read in that survey. Online play has since been built using port-owned screens.

## Text inside images

| Sheet | Text | About |
|---|---|---|
| `title/title` | ストーリー, 対戦, 通信対戦, 環境設定, 操作設定, 終了, each in two states | 6 |
| `object/p03` | Tactics: 適当, 格闘, 射撃, 集中, 各個, 護衛 (second row read at low resolution) | 6 |
| `object/p04`, `p05`, `p08`, `p09` | Notices: 撃沈!, 開始!, 青組, 赤組, 大勝利, 撃破! | 6 |
| `object/system` | もう一度挑戦しますか?, はい, いいえ, 本日の活動報告 | 4 |
| `object/logo` | 切断しますか?, はい, いいえ, for netplay | 3 |
| `select/p00` | The three hypermode names | 3 |
| `select/P01` | 戦闘開始, 準備完了!, 決定, 戻る, 制限時間, 体力値, ゲージ増加量 | 7 |
| `select/P02` | Two balloon size labels, each in two states, and three hypermode descriptions | 7 cells |
| `select/p03` | Sixteen character names | 16 |
| `select/w00`..`w15` | Three weapon names and descriptions each, two on the last two | 92 |
| `select/pbg00` | Stage names, ランダム, 昼, 夕, 夜 | 10 |
| `teamselect/p00`, `p01` | Ten pairs of character names and ten team names | 30 cells |
| `teamselect/add0`, `add1` | Unlock notices. Nothing shows them today, since all teams are open | 12 |
| `config/0001`, `0002`, `0003` | Options title, rows and help lines; only `0001` is loaded by the port | 25 |
| `keyconfig/0000`, `0004` | Key config title, rows and help lines; only `0000` is loaded by the port | 26 |

About 235 strings. Rows drawn in two states appear twice on the sheet. `object/gameover` and the
English labels (`CHARACTER SELECT`, `PAUSE`, `STAMINA`, `OVER KILL!!`) can stay. The key names in
`keyconfig/0001` need only a few, such as 漢字 and カナ.

## Text outside images

| Source | Text | About |
|---|---|---|
| `data/scenario/D*.txt` | Story dialogue | 983 lines — now translated; see #99 below |
| `data/scenario/win/*.txt` | Victory quotes | 570 files, 1,291 lines — now translated; see #99 below |
| Runtime captions | The port's own result and pause text | Not counted |
| `DaybreakDX.exe` | The earned titles, read from its table (VA `0x6b7308`) | Not counted |
| Movies | `prologue`, `e00`..`e09`, the staff rolls. Any burned-in text stays | Not checked |
| Voices | All Japanese. Subtitles are the dialogue itself | Stay |

## Issue #96: initial coverage assessment

This is a source and locale-file inventory, **not a screen-by-screen verification**. A sheet
having English entries does not prove every Japanese pixel is covered. A maintained source-cell
manifest checks all locale entries against the current draw-site audit; a real-asset test checks
that every listed cell changes when localized. Sampled English/Japanese captures compare visible
regions on title, select, stage, story team, options, controls and online; a source test checks
literal bilingual captions. These checks do not cover every state or detect all Japanese pixels.

| Area | Current coverage / remaining work |
|---|---|
| Title, tactics, notices, retry, selection, weapons, stages, story teams | English entries cover every drawn cell; a source-cell manifest pins the mapping and a real-asset test proves each cell is painted. Visibility was sampled, not exhaustively verified. |
| Options and controls | Port-owned screens use bilingual runtime captions rather than the original sheet labels. Verify their backgrounds and key names. |
| Online | Port-owned online screens use Japanese/English caption pairs, though some error messages are English-only. Original network/chat sheets are not used by reachable screens. Verify all reachable states. |
| `object/logo` disconnect prompt | Excluded: no screen loads the original disconnect-prompt sheet; the port uses its own online UI. |
| `teamselect/add0`, `add1` unlock notices | Excluded: no screen loads them; all story teams are available. |
| Original network/chat name-entry sheets | Excluded: `SoftKeyboard` can load these sheets, but no screen instantiates it; the online UI uses its own text editor. |
| Result earned titles | All 41 indices have English locale entries; Japanese mode retains the installed executable's titles. A test checks every lookup and a report capture shows four fitting in the column; the other labels have not been visually reviewed. |
| Runtime result and pause captions | Port-owned captions are English in both modes; earned titles are translated. The victory quote band is story text and is covered by #99 below. |
| Story dialogue and victory quotes (issue #99) | English mode shows translated lines from the shipped `assets/locale/story_en.json`; Japanese mode shows the install's own lines. The EN/JP toggle is shared with the sheets. Coverage and evidence are recorded below. |
| Original title logo | **Owner-approved exception:** retain the original Japanese game logo as branding in English mode. |
| Movies and voices | **Owner-approved exception:** keep Japanese text burned into original movies. Japanese speech and dialogue subtitles are also outside this issue. |

## Issue #99: dialogue and win screens (owner decision 2026-11-19)

The full English translation **ships in the repository**, as one tracked file:
`assets/locale/story_en.json`, a flat JSON map of 2,274 ASCII keys to ASCII English values. The
lead reviewed it before integration: 0 missing or extra keys, 0 non-ASCII or empty values, and 0
escape-token mismatches against the 690 CP932 source files. No game data, Japanese original,
script or install file enters git, and no file in the install is modified.

### The one route

- `ui::setSheetLanguage` stays the single EN/JP mode owner. On a successful switch it also calls
  `ui::setStoryTranslationLanguage` (`src/ui/story_locale.*`), so `--language`, the saved setting
  and the Options row change menus and story together. Japanese mode loads no translation at all.
- A key is `<path under data/scenario/>#<0-based text ordinal>`: `D01-0.txt#0` for dialogue,
  `win/05-08-4.txt#0` for a victory quote. The ordinal is the index among Text commands (or quote
  lines) in file order — the unit both parsers already emit — so nothing re-reads a script at
  display time.
- `StoryDialogue::runUntilText` substitutes the caption line; the result screen substitutes the
  picked quote-band line. Both call `ui::storyDisplayText(path, ordinal, original)`, which returns
  the English value when active or `original` in Japanese mode, on a missing key, and after a
  missing or malformed file. A missing key is reported once per key, then falls back silently.
- Values keep their `\n`, `\cRRGGBB` and `\e` escapes byte for byte; the existing caption walkers
  already draw them. No rendering code changed, and timing/voices/art still come from the install.

### Coverage

| Source | Source lines | Shipped entries | Evidence |
|---|---:|---:|---|
| `data/scenario/D*.txt` — 120 scripts | 983 dialogue lines | 983 | source-key sweep against the install (tier 4) |
| `data/scenario/win/*.txt` — 570 scripts | 1,291 quote lines | 1,291 | source-key sweep against the install (tier 4) |
| **Total** | **2,274** | **2,274** | `story_translation_test` checks every shipped key resolves |

`story_translation_test` is device-free and game-data-free: it parses the shipped file, checks
that every value is non-empty ASCII, checks that all 2,274 keys resolve, and checks sampled
dialogue and win lines in both modes plus a synthetic script with a missing key.
`story_script_test` adds the install-backed check (tier 4) that all 983 real dialogue commands
and 1,291 real quote entries have an entry. These checks prove key resolution, not that every
translated caption fits its box or reads well; visual sampling remains a human step.

A paired headless capture of the same script (`--screen=storyadv --story=D01-0 --headless
--no-audio --size=800x600 --frames=120 --out=<file>`) shows the opening English line in English
mode and the install's Japanese line in Japanese mode (tier 5, capture of our own build — not a
live run). Caption boxes keep the original's 32-cell wrap, so a long English line can break
mid-word; that is a layout limitation of the unchanged caption path, not a lookup failure.

Seven keys carry the review's `BOTH:` prefix for dual-speaker lines (flagged in the review notes).
They ship verbatim and are drawn as-is; the caption UI has no separate dual-speaker treatment.

### Deliberate omissions (owner-approved)

- **Voices stay Japanese.** Voice files are data, not translated; the dialogue captions are their
  subtitles. No audio was changed.
- **Burned-in movie text stays Japanese.** The prologue, `e00`..`e09` and the staff rolls keep
  their original pixels (the #96 decision).
- **The original title logo stays Japanese** as branding in English mode.
- The exclusions already recorded for #96 (unreachable disconnect prompt, unlock notices,
  original network/chat name-entry sheets) remain excluded.

## What the data implies

- `assets/locale/en.txt` keeps the original's cell layout, so the code's coordinates do not change.
- A translated label has to fit a cell sized for two to five Japanese glyphs, and weapon
  descriptions are two dense lines. Some translations will have to be short.
