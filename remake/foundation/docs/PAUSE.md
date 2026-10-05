# Battle pause — the recovered freeze, and the port's menu

Issue #15. The input vocabulary and the binding screen already carried a `Pause` action
(keyboard W, pad Start by default, rebindable); nothing in the battle read it, and Escape
killed the process. This is what the pause is, what it freezes, and which runs may use it.

## What is recovered (cite, don't invent)

The original has a pause flag and a second toggle, both cleared by the battle reset:

| What | Where |
|---|---|
| pause flag `scene+0x4430`, second toggle `scene+0x4431` | cleared by `FUN_00634760` @0x634877 / @0x634881 |
| the toggle | `FUN_00634f60` @0x634fb3-0x635006 |
| offline-mode gate (`DAT_006cfdb0 == 0`) | @0x634fb3-0x634fbc |
| live-round gate (`scene+0x4a3c == 2`) | @0x634fc2-0x634fcc |
| the player's pause action (`[fighter+0x29c] == 1`) | @0x634fdf-0x634fe6 |
| the pause cue, system SE `0x11` (`FUN_0064aed0`) | @0x634fe8-0x634fef |
| the flag flip (`1 - (x != 0)`) | @0x634ff4-0x635006 |
| the prompt/banner switch: any of the fighter's 7 action slots flips `0x4431` | @0x63500c-0x635064 |
| **the freeze**: the frame counter `scene+0x1c` and the whole battle update are skipped | @0x635093-0x6350aa |
| the banner: the `PAUSE` cell of `data/object/system.cnv` (256,64,256,64) drawn at (400,300) | `FUN_0063a130` @0x63a08c-0x63a0b8 |

Two consequences worth stating: the original keeps **reading input while paused** (the
toggle sits before the gate), which is what lets a player resume; and it freezes everything
the gate wraps — fighter updates, the round machine `FUN_00635d40`, the balloon easing
`FUN_006430f0` and the camera/FX tail — not just the fighters.

## What is a port feature

The original's pause UI is the banner plus a もう一度挑戦しますか？ / はい / いいえ rematch
prompt from the same atlas. The **four-row readable menu** — Resume, Rematch, Return to
selection, Quit to desktop — and its captions are the port's own, because the issue asks for
readable, rebindable controls and the original has no return-to-selection row (leaving a
battle goes through its result scene there). The standalone `--match` harness has no
selection screen behind it, so its menu is three rows (Resume / Rematch / Quit).

## What freezes

`Match::set_paused` gates the authoritative step: a paused `Match::step` returns an empty
frame and touches nothing — no economy tick, no fighter tick, no respawn clock, no
projectile motion, no FX event — and `dt` is dropped rather than accumulated. The host also
skips its own per-tick work (`tickMatch`: the frame counter, COM decisions, HUD values,
camera update, animation clock), so the presented frame is frozen, and the fixed-step clock
is **not advanced at all** while paused: paused wall time can never become catch-up ticks.

Measured (temporary per-frame instrumentation, since removed): a live battle paused for
12 s of wall time printed `matchFrame=39 alpha=0.3728 eye=(0.00,176.47,-124.08)
target=(0.00,338.00,0.00)` identically on every sampled frame.

## Input

* The paused ticks keep draining the device queues at the same cadence they would during
  play. That is what makes a button held across the pause produce **no** edge on resume,
  while a fresh press still works.
* Menu keys: Up/Down choose, Jump confirms, AttackA backs out (Resume), Pause toggles back
  out — the same vocabulary the other menus use.
* The overlay's key hints are read from the **current bindings** (P1 keyboard plus the
  pausing player's pad), so a rebind shows up without a second table.
* Escape opens the pause in a live battle instead of quitting the process; inside the menu
  it resumes. Menu screens and every capture/replay path keep Escape's old behaviour.

## Focus loss and disconnected controllers

* Focus loss drops held keys (#6's Guard-safety fix) and **pauses a live offline battle**,
  so a match cannot keep running — and keep taking damage — while the player cannot see or
  control it. Regaining focus does not auto-resume; the player resumes deliberately. A
  *scripted* run is left alone: its script owns the pause state, and a stray focus event
  must not make a recipe non-deterministic.
* A disconnected pad already reads as released (`Backend::poll` clears a removed device's
  held state, so a mid-hold removal becomes one `just_released`, not a stuck hold), and the
  pause action is bound to the keyboard by default and is rebindable — so a player whose pad
  dies can always reach the menu.

## Audio

* Gameplay SFX (`SfxBus::Sfx`, channels 16..31) are stopped when the pause begins; no new
  cue can start because the match does not step, and a pause is not a mixer pause (one-shots
  do not resume).
* BGM keeps playing: the original's pause path plays SE 0x11 and never touches the music
  stream.
* The pause cue is the recovered system SE 0x11 (`data/sysse/017`), played on the UI bus.
* Voices are not cut (they are short, and the original does not touch them).
* The full expectation was handed to the #16 (combat audio) agent; it must not add pause
  policy of its own.

## Which runs may pause

Only a live offline battle that is not a capture or a bounded run:

```cpp
app.matchMode && app.opts.out.empty() && !app.opts.headless && app.opts.frames == 0
```

so `--match`, `--versus`, `--hud-test`, `--screen=battle` captures, `--out`/`--headless`
runs and every `--frames` run keep their historical behaviour and are byte-identical with
the pause unused (verified: the four parity recipes produce identical PPMs with and without
a user config and never mention the pause).

A scripted standalone `--match` run needs one extra piece: its script is indexed by the
match frame, which freezes with the pause, so the paused ticks advance
`App::pauseScriptAdvance`, which is added to that clock. It is zero for every run that never
pauses, so the banked traces keep their frame-for-frame script mapping.

## Verification

* `battle_pause_test` (device-free, 1276 checks): the frozen economy, KO and respawn clocks;
  a held button producing no shot or attack while paused and none on resume, while a fresh
  press still does; the `TickInput` drain rule; the menu's rows, wrap and choices.
* Asset-backed, `--screen=battle`: pause mid-attack → resume; pause → Rematch → VS → the
  **same stage** → a fresh battle; Rematch again; pause → Return to selection → the Select
  screen; quit through the menu with a clean exit (`RESULT: ok`). The scene/asset counts are
  identical every cycle (13 models, 63 meshes, 50006 vertices, 152 textures), i.e. repeated
  re-entry does not grow anything.
* Asset-backed, mid-respawn (needs the damage fix from `feat/fix-damage-scale`):
  `KO! side=1` → pause inside the 3 s window → **600 paused ticks (three times the window)
  with no respawn** → resume → `side 1 respawned` → quit. Log order is the evidence.
* Focus-loss auto-pause and the disconnected-pad path are policy plus the existing backend
  behaviour; a physical pad replug and real hardware audio were not exercised here.
