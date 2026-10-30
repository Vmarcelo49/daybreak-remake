# Translation inventory

What a translation of the menus and the HUD has to replace. Read from the install's sheets on
2026-10-30, by eye, so counts are approximate. The netplay sheets (`data/network`, `data/chat`) were
not read: netplay is not built.

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
| `select/P02` | Balloon size rows, three hypermode descriptions | 5 |
| `select/p03` | Sixteen character names | 16 |
| `select/w00`..`w15` | Three weapon names and descriptions each, two on the last two | 92 |
| `select/pbg00` | Stage names, ランダム, 昼, 夕, 夜 | 10 |
| `teamselect/p00`, `p01` | Ten pairs of names and ten team names | 20 |
| `teamselect/add0`, `add1` | Unlock notices. Nothing shows them today, since all teams are open | 12 |
| `config/0001`, `0002`, `0003` | Options title, rows and help lines | 25 |
| `keyconfig/0000`, `0004` | Key config title, rows and help lines | 26 |

About 235 strings. Rows drawn in two states appear twice on the sheet. `object/gameover` and the
English labels (`CHARACTER SELECT`, `PAUSE`, `STAMINA`, `OVER KILL!!`) can stay. The key names in
`keyconfig/0001` need only a few, such as 漢字 and カナ.

## Text outside images

| Source | Text | About |
|---|---|---|
| `data/scenario/D*.txt` | Story dialogue | 983 lines |
| `data/scenario/win/*.txt` | Victory quotes | 570 files |
| Runtime captions | The port's own result and pause text | Not counted |
| `DaybreakDX.exe` | The earned titles, read from its table (VA `0x6b7308`) | Not counted |
| Movies | `prologue`, `e00`..`e09`, the staff rolls. Any burned-in text stays | Not checked |
| Voices | All Japanese. Subtitles are the dialogue itself | Stay |

## What the data implies

- `assets/locale/en.txt` keeps the original's cell layout, so the code's coordinates do not change.
- A translated label has to fit a cell sized for two to five Japanese glyphs, and weapon
  descriptions are two dense lines. Some translations will have to be short.
