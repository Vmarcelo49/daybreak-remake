# User settings — where they live, what is stored, how they recover

Issue #19. This is the port's own persistence layer: the original keeps its settings
in a flat binary `config.dat` beside the executable, and two of that file's properties
are deliberately not copied. Read this before changing the schema, the file location or
the controller policy.

## Where the file is

`$XDG_CONFIG_HOME/daybreak-decomp/settings.conf`, or `~/.config/daybreak-decomp/settings.conf`
when `$XDG_CONFIG_HOME` is unset. The XDG base-directory rule is applied literally: only
an **absolute** `$XDG_CONFIG_HOME` counts, so a relative or empty value falls back to
`$HOME/.config` and cannot redirect the write into the working directory. With neither
variable set the port runs with defaults and writes nothing.

Nothing is ever written into the game install or the checkout. The original writes
`config.dat` next to its own executable (`CreateFileA("config.dat", …)` in
`FUN_006486c0` @0x6486c0 / `FUN_006488d0` @0x6488d0), which is exactly what the issue
forbids for the port.

Delete the file to reset everything to its defaults; there is no separate reset file.

## What is stored (schema version 7)

```ini
version = 7

[game]
install_dir = /home/u/Games/Higurashi-Daybreak   # absolute; empty = none remembered
language = en                 # menus and HUD; empty = the game's own Japanese

[network]
name = PLAYER                 # what other players see, up to 12 plain characters
port = 37564                  # the UDP port a hosted room listens on
input_delay = 2               # frames, 0 to 8
last_host =                   # the address last joined

[display]
fullscreen = false
resolution = desktop          # or WxH, e.g. 1920x1080

[render]
toon = false                  # the Options screen's toon-rendering row (issue #21)
shadows = false               # character shadow-map row (issue #21, row 1)

[audio]
master = 100                  # 0..100, one per bus
music = 100
voice = 100
sfx = 100

[bindings]
keyboard = 82, 81, 80, 79, 27, -1, 7, 6, 29, 22, 20, 4, 26
pad1 = 11, 12, 13, 14, 2, -1, 0, 3, 1, 10, 4, 9, 6
pad2 = …
pad3 = …
pad4 = …

[controllers]
pad1_guid = 030000005e0400008e02000000007801
pad1_name = Xbox Wireless Controller
pad2_guid =
…
```

* `[game] install_dir` (issue #36) is the game folder a run last opened, so **one config
  file owns the install path**: the packaged launcher reads this key and no longer keeps an
  `install.conf` of its own, and a direct binary run honours the remembered folder instead
  of discovering one from scratch. It is a **port** decision, not recovered behaviour — the
  original reads its assets relative to its own executable and has no such setting, and how
  a folder is *discovered* (the launcher's search order) is a separate concern that this key
  does not change. The precedence per run is `--install=` → `$DAYBREAK_INSTALL` → this key →
  the working directory; only a run that opens a folder writes it, and only when the folder
  is **absolute** — `--install=Higurashi-Daybreak` means "here", which is that shell's
  working directory, so it is used but never remembered. An unusable remembered folder
  (moved, deleted, a partial copy) is reported and falls through to the working-directory
  check instead of failing the launch, because it is a hint rather than an instruction. The
  key is always present in the file (empty = nothing remembered): an *absent* key in a
  current document therefore means a hand-edit or a lossy writer, and is warned about.
* `resolution` is the user's **choice** from the Options resolution row, not the
  window's current size: `desktop` means "follow the display". A window drag, a
  startup pixel-size event or a fullscreen transition moves the live selection but
  never rewrites this key (`ui::FrontendSettings::resolutionChoice`).
* `[render] shadows` is the Options row 1 toggle (影の表示): on means the character and
  weapon draws are rendered once more into the recovered light-space shadow map and the
  stage's receiver term subtracts the recovered 0.3 from its albedo where its own light
  depth is behind the map. Off is the shipped default and the state every banked capture
  was made in — a capture hashes exactly as it did before the pass existed — and the row
  flips it live through the same per-frame path as `toon`. `foundation/docs/SHADOWS.md`
  carries the recovery.
* `[render] toon` is the Options row 0 toggle: on means the character and weapon draws use
  the original's toon technique — an outline hull pass plus the effect's own
  `albedo * saturate(ramp + emissive − 0.1)` shading off the shipped
  `data/directX/toon.cnv` ramp. Off is the shipped default and the state every banked
  capture was made in; the row flips it live (the renderer reads the live value every
  frame) and this key is what makes it survive a restart. `ROADMAP-PENDING.md`
  §"Renderer options (issue #21)" carries what the original's global gates and the port
  rules.
* The binding rows are one comma-separated value per action, in `fnd::input::Action`
  order: `up, down, left, right, attack_a, attack_b, guard, shoot, jump, special,
  tactics, lock_switch, pause`. `-1` is unbound. Keyboard values are SDL scancodes,
  pad values SDL gamepad buttons (the numbering the key-config screen prints).
* **Session state is deliberately absent.** Earned titles, result stats, match
  outcomes and punishment-costume flags live only for the session, in the original as
  well; the issue keeps them out of permanent saves, and no key here may name one.

### Schema history and migrations

| Version | Change | A file of this version |
|---|---|---|
| 1 | initial (`up, down, left, right, attack_a, attack_b, guard, …`, 13 entries) | migrated: the removed heavy-melee entry is dropped, every other binding kept, **one warning** |
| 2 | issue #10 removed the port-invented heavy action, so the rows are 12 entries | migrated: every value read as v2 wrote it, `toon` takes its default (off), no folder is remembered, shadows take their default (off), nothing dropped, **no warning** (a context line) |
| 3 | issue #21 added `[render] toon` | migrated: every value kept, `[game] install_dir` takes its default (empty), `shadows` takes its default (off), **no warning** (a context line) |
| 4 | issue #36 added `[game] install_dir` | migrated: every value kept, `shadows` takes its default (off), **no warning** (a context line) |
| 5 | issue #21 row 1 added `[render] shadows` | migrated: every value kept, the language defaults to Japanese |
| 6 | added `[game] language` | migrated: every value kept, `[network]` takes its defaults |
| 7 | added `[network]`, for online play | current |

Migration is per document, never partial: the version line decides how the binding rows are
read, and the next save writes the current version. The `[render]` and `[game]` sections
themselves are read whatever the version line says, so a hand-edited file is not rejected
for naming a key this build knows. A version this build cannot migrate (6 and up) is
rejected whole. A migration never drops a stored value; the only thing an older file cannot
carry is a key that did not exist yet, and that key's default is what the older file meant.

**Why the shadow toggle is v5 and not v4**: issues #36 and #21 row 1 were developed on
separate branches from v3 and each first took v4. #36's v4 shipped first, so it keeps the
slot; the merge moved the shadow toggle to v5 and taught this build to READ a v4 document
(a file written by a #36 build) with its `install_dir` intact and the toggle defaulted off.
## Controller identity policy (port decision)

The original stores bindings per **player** — `config.dat`'s 0xd0-byte block is exactly
four players × thirteen actions × int32 scancodes, and the key-config screen has four
player columns. It has no device identity at all: its pads are per-player button
tables.

The port keeps the per-player model (that is the unit the key-config screen edits and
the unit the original stores) and adds the identity the original lacks, because the
backend used to hand a pad the lowest free slot in **enumeration order** — unplug and
replug two pads and their bindings could swap owners.

* `[controllers] padN_guid` records the SDL GUID of the pad that last used player N.
* On hotplug a pad whose GUID is recorded for a free slot is opened into **that** slot
  (`fnd::input::preferredPadSlot`, `src/input/gamepad_identity.h`); anything else takes
  the lowest free pad slot, which is the enumeration behaviour the backend had before.
* A recorded GUID that is not connected changes nothing: the bindings stay on the
  player slot and remain usable by the keyboard or by the next pad.
* Slot 0 is the keyboard and never takes a pad.

## Load, validation and recovery

The file is read **before** any frontend screen exists (`loadUserSettings` in
`main.cpp`, called from `SDL_AppInit`), so the first frame already uses the user's
volumes and bindings; the display half is applied in `initScreens` once the resolution
list and the SDL callbacks exist (`applyPersistedDisplay`).

| Input | Behaviour |
|---|---|
| No file | First launch: defaults, no message beyond the path |
| Unknown keys in a known section | Ignored with a warning; every other value still applies |
| A value out of range / unparseable | **That key** keeps its default, warning counted, the rest applies |
| `install_dir` empty | The documented "no folder remembered"; no warning |
| `install_dir` relative, or longer than the 480 bytes one line allows | That key keeps its default (the folder is not remembered), warning counted, the rest applies; the run then discovers a folder as it did before |
| `install_dir` missing from a **current** document | Warning: the file should carry it, so nothing is remembered. In an **older** document the migration line says the same thing without a second warning |
| Missing or unsupported `version` | Whole file ignored, defaults, reason printed |
| Unknown section, bad line, NUL byte, >64 KiB, >512-byte line | Whole file ignored, defaults, reason printed |
| Stored resolution the display does not offer | Desktop (index 0); the preference is kept in the file |
| Fullscreen the window manager refuses | Stays windowed; the live state is what gets saved |
| Unwritable / uncreatable config directory | Startup continues with defaults; the failure is reported **once**, then retried at most every 5 s |

"Structure errors reject the whole document, value errors default one key" is the rule:
a hand-edited typo cannot destroy the other settings, and a corrupt file cannot be
applied half-way.

## Atomic writes

`settings::save` writes `settings.conf.tmp` in the **same** directory, `fsync`s it,
`rename`s it over the target and then `fsync`s the directory, so a crash leaves either
the old file or the new one. The temp file is forced to mode 0600 every time (a
leftover temp file from a crashed writer must not decide the final file's mode), and a
failed write removes the temp file and leaves the previous file untouched. The original
truncates `config.dat` in place with `CREATE_ALWAYS`, which is the failure mode this
avoids.

The non-Linux targets (Windows cross-build, web) use the same temp-file + rename shape
through `std::filesystem` without `fsync`; on the web `settings::persistenceSupported()`
is false, so the browser build keeps its settings process-local (IndexedDB/OPFS remains
the open half, `docs/WEB-ASSETS-RUNTIME.md`).

## Which runs use it

Only a plain interactive frontend run reads or writes the file. Every capture, replay
and bounded run ignores it entirely — `--match`, `--versus`, `--hud-test`, `--out`
captures, `--headless`, the asset viewers and anything with `--frames` — so the banked
captures and parity recipes behave identically with and without a user config
(`usesUserConfig` in `main.cpp`). That gate is also what makes the remembered game folder
safe to write: a capture cannot create the file, cannot rewrite it, and cannot be steered by
it, so a capture with no file present stays byte-identical to one taken before the key
existed.

## Verification

* `user_settings_test` (device-free): defaults, round trip, versioning, malformed and
  hostile files, value ranges, paths (including a path with spaces), the atomic write
  (no temp leftovers, no clobbering on failure, owner-only mode), the resolution
  fallback, the controller-placement policy, every migration (a v1 row losing the
  removed heavy binding with one warning; a v2 document keeping every value and gaining
  `toon` and the empty game folder; a v3 document keeping the toon toggle it stored and
  gaining the empty game folder, neither with a warning) and the `[game] install_dir`
  rules (empty = unchosen, absolute kept, relative and over-long refused with one warning
  each, absent in a current document warned about, and a folder the writer cannot store
  written as empty rather than as a line the reader would reject).
* `frontend_config_test`: the document ↔ live-settings seam, including the resolution
  choice rule and the toon toggle's and the remembered folder's round trips through
  `applyUserSettings` / `toUserSettings`.
* `launcher_test.sh`: the launcher's search order, its failure messages, that it writes no
  config file at all, that it reads the remembered folder out of `settings.conf`, that it
  ignores a schema version it does not know, and the one-time migration of a retired
  `install.conf`.
* End to end, with an isolated `XDG_CONFIG_HOME`: first launch → change a volume →
  saved → restart loads it and does not rewrite the file → one step from the loaded
  value (40 → 45) proves the value was applied. Recovery was exercised with a garbage
  file, `version = 99`, a truncated file, a NUL byte, a config path that is a regular
  file (unwritable), a config directory with spaces, and a stored resolution the
  display does not offer. The install precedence was exercised the same way
  (`--install=`/`$DAYBREAK_INSTALL` beating the saved folder, a saved absolute folder
  used by a bare `--screen=title` run, a saved relative folder warned about and falling
  through, nothing saved falling back to the working directory, and a saved folder that
  is gone warned about instead of failing the launch).
