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

## What is stored (schema version 3)

```ini
version = 3

[display]
fullscreen = false
resolution = desktop          # or WxH, e.g. 1920x1080

[render]
toon = false                  # the Options screen's toon-rendering row (issue #21)

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

* `resolution` is the user's **choice** from the Options resolution row, not the
  window's current size: `desktop` means "follow the display". A window drag, a
  startup pixel-size event or a fullscreen transition moves the live selection but
  never rewrites this key (`ui::FrontendSettings::resolutionChoice`).
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
| 2 | issue #10 removed the port-invented heavy action, so the rows are 12 entries | migrated: every value read as v2 wrote it, `toon` takes its default (off), nothing dropped, **no warning** (a context line) |
| 3 | issue #21 added `[render] toon` | current |

Migration is per document, never partial: the version line decides how the binding rows are
read, and the next save writes the current version. The `[render]` section itself is read
whatever the version line says, so a hand-edited file is not rejected for naming a key this
build knows. A version this build cannot migrate (4 and up) is rejected whole.

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
(`usesUserConfig` in `main.cpp`).

## Verification

* `user_settings_test` (device-free): defaults, round trip, versioning, malformed and
  hostile files, value ranges, paths (including a path with spaces), the atomic write
  (no temp leftovers, no clobbering on failure, owner-only mode), the resolution
  fallback, the controller-placement policy, and both migrations (a v1 row losing the
  removed heavy binding with one warning, a v2 document keeping every value and gaining
  `toon` at its default with none).
* `frontend_config_test`: the document ↔ live-settings seam, including the resolution
  choice rule and the toon toggle's round trip through `applyUserSettings` /
  `toUserSettings`.
* End to end, with an isolated `XDG_CONFIG_HOME`: first launch → change a volume →
  saved → restart loads it and does not rewrite the file → one step from the loaded
  value (40 → 45) proves the value was applied. Recovery was exercised with a garbage
  file, `version = 99`, a truncated file, a NUL byte, a config path that is a regular
  file (unwritable), a config directory with spaces, and a stored resolution the
  display does not offer.
