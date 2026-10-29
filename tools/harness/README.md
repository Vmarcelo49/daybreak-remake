# harness — tier-1 evidence from the original executable

Phase 1 of [`docs/DIRECTION.md`](../../docs/DIRECTION.md) §4. This directory holds
the tooling that records what the **original** `DaybreakDX.exe` actually does, so
the port's behaviour can be compared field by field instead of argued about.

## Why the harness spawns the game itself

`/proc/sys/kernel/yama/ptrace_scope` is `1` on this machine, so a process may only
read the memory of its **descendants**. Wine's loader forks the game and exits,
which reparents the game to `systemd --user`; attaching to an already-running game
is therefore denied (`EPERM`), and that is the failure mode to expect if you try.

`orig_capture.py` sets `prctl(PR_SET_CHILD_SUBREAPER, 1)` before spawning Wine, so
the orphaned game reparents to *the harness* and `process_vm_readv` is permitted.
No `sudo`, no `setcap`, no sysctl change. Verified 2026-10-14:

- VA `0x400000` reads back `MZ` / `PE\0\0` and the first 0x100 bytes are
  byte-identical to the on-disk executable;
- `DAT_006cfae0`, the four actor pointers (`FUN_006348b0:13`), reads as `0,0,0,0`
  at the title screen — correct, and proof the address is live.

## Operational facts learned on this machine (2026-10-14)

- **The game window's `WM_CLASS` is `daybreakdx.exe`**, not the Win32 class
  `HigurashiDaybreak` (Wine sets `WM_CLASS` from the executable). Title is
  `…ver1.11`. `xdotool search --onlyvisible --class daybreakdx` finds it, and
  `windowactivate --sync` makes it the active window; the tools check that the
  active window is the game before typing.
- **The original runs at ~60-63 Hz here** (Wine + DXVK). Measured in a live battle
  twice: slot 0's animation tick at actor `+0xae04` went `192 -> 505` over 5.00 s
  (62.5 Hz), and later three live actors advanced ~94 per 1.5 s (62.7-63.3 Hz).
  *Correction:* an earlier note in this file claimed ~1 fps, inferred from a
  confirm field that stayed latched for a second. That inference was **wrong** —
  the latch was scene state, not a frame period. The measurement above supersedes
  it, and independently supports the 60 Hz decision (D15).
- **Still hold keys across a frame.** `xdotool key` is a ~10 ms press/release,
  which spans only ~0.6 of a 60 Hz frame and is often missed; a held key is
  sampled reliably. Evidence: of three un-held presses, exactly one appeared as a
  pulse in `DAT_006cae94`.
- **Keys do reach the game's DirectInput state**: a held `Z` produced
  `slot 0 [0x08] 0 -> 1 -> 0` in `DAT_006cae94` (field `[2]`, the documented
  confirm edge), which is both the proof of delivery and the fastest way to test
  input plumbing.
- **`pika` reads the original without being its ancestor.** With
  `cap_sys_ptrace=eip` on `~/.local/bin/pika`, the daemon (`pika serve`) reads the
  detached game process directly (`pika read <pid> <addr>` shows `MZ` at
  `0x400000`). Without the capability, only a descendant-spawning harness can
  read it.
- **Timing-based menu driving is unsafe.** At ~1 fps the opening movie finishes
  on its own; a `Z` intended to skip it then lands on the *title* and selects
  ストーリー. Input must be **state-driven** — which is why the current-scene
  variable is being hunted (below).

## Opening the game: skip the movie with exactly one press (proven 2026-10-14)

`tools/harness/open_skip.py`:

```
launch -> wait for the process -> wait 2 s -> press Z ONCE -> screenshot
```

That lands on the main menu with ストーリー highlighted (evidence:
`local-data/harness/shots/open-skip.png`). **The single press is the whole
trick.** Two attempts failed before it, both by pressing Z more than once:

- pressing Z every second after the window appeared — the first presses hit the
  movie, the later ones hit the *title* and started story mode;
- gating the presses on frame-to-frame **motion** (movie = moving, title = still):
  measured scores at the title were 13-40, so the gate never closed and the loop
  kept pressing into story mode.

So: one press, then no input until the menu step.

## Reaching a battle (proven 2026-10-14)

With the owner's documented flow and every press **held ~2 s**, the original went
from the title menu to a live battle:

```
Z (skip movie)  DOWN  Z          -> team select (青組/赤組)
Z Z Z Z Z                        -> red team, Rena, weapon 0, hypermode, 1P
UP  Z                            -> match settings
UP  Z                            -> start match
```

Verified at each step by screenshot (`import -window <id>`), which is the state
signal that replaced the missing scene variable. On arrival `DAT_006cfae0` held
four live actors and the harness read them:

**Caveat on `+0xae04`:** it is an animation frame index, not a monotonic uptime
counter — it advances ~63 Hz while an animation plays, resets when the animation
changes (an idle actor sat at `30` for many seconds), and therefore wraps rather
than climbing forever. Use it to *pace* and to *detect* animation changes; never
as a total frame count.

| slot | actor | `+0xae04` tick | `+0xadf4` phase |
|---|---|---|---|
| 0 | `0x086be378` | 152 → 216 in 1 s | 0 |
| 1 | `0x11632fa8` | 6 → 46 in 1 s | 0 → 1 |
| 2 | `0x133c33b8` | 2 → 58 in 1 s | 0 → 1 |
| 3 | `0x15ea3668` | 17 (idle) | 0 |

That is the tier-1 field read working **inside a battle** — the thing Phase 1
exists to produce.

## Finding the current-scene variable (open)

**Status: not found.** The coarse-phase candidate at `0x1afcc78` suggested itself
twice (a delta scan and a pika filter chain both landed on it) and was then
**falsified**: `0x1afcc78 + 0x2e18` read `0` both at the title and at team select
after a verified transition, and the same struct held wildly churning values
(`39050032`, `0`, `39050064`) at its `+0x2e14`. Also note the filter chain that
found it was unsound — scanning for `0` makes `increased` mean merely "became
non-zero", so it selected pixel buffers (`0x0253F4D0` = teal ARGB), not counters.

What works instead, and is enough: **screenshot verification at each step plus the
actor array as the "we are in a battle" signal.**


`LoadNextScene` (`0x00406310`) switches on `pGameState + 0x2e18` and increments a
per-frame counter at `+0x2e14`, but the struct is a **stack local** of the entry
function, so it has no static address. The scene ids the switcher consumes are the
values each scene's update returns (`FRONTEND-PLAN.md` §1.2: 1 title, 3 select,
9 VS intro, 10 battle).

Tools, in the order they were tried:

| Tool | Method | Result |
|---|---|---|
| `find_gamestate.py` | scan for a dword advancing ~60/s with small neighbours | many false positives; the game does not run at 60 fps here, which is why |
| `find_scene.py` | same candidates, then watch `+0x2e18` while keys are sent | candidates never changed — the un-held keys were not delivered |
| `find_scene_diff.py` | hash every writable page across the movie→title transition, no input at all | 411k small dwords changed: the scene's own animation drowns a raw diff |
| `probe_input.py` | watch `DAT_006cae94` while keys are sent | **proved input delivery** and the hold-across-a-frame rule |
| `pika` | capability-backed value scans with `filter` between screens | the current approach: scan at one screen, transition, filter by the next screen's id |

## Usage

```bash
# Record the title screen for 20 s and write JSONL
python3 tools/harness/orig_capture.py --seconds 20 --out local-data/harness/title.jsonl

# Drive the documented menu flow into a battle, then record it
python3 tools/harness/orig_capture.py --seconds 60 \
    --keys "boot:12,down:1,confirm:2,confirm:3,confirm:6" \
    --out local-data/harness/battle.jsonl
```

`--keys` is `name:seconds` steps executed in order after boot: `down`, `up`,
`left`, `right`, `confirm` (Enter), `cancel`. The flow is not guessed — it is from
the RE'd scene table in `remake/foundation/docs/FRONTEND-PLAN.md`:
title items in atlas order are ストーリー / 対戦 / 通信対戦 / 環境設定 / 操作設定 /
終了 (`title.cnv`, six 192×48 cells), the cursor is `+0x1f0`, confirm is
`+0x1fc == 1`, and the 対戦 item (second) returns scene 3 → page 1 confirm → scene
9 (VS intro) → scene 10 (battle). Input scancodes the original tests directly:
`0x1c` Enter, `0x39` Space, `0xc8/0xd0` up/down, `0xcb/0xcd` left/right.

Keys go through `xdotool` **XTEST** events, which Wine's X11 driver turns into
DirectInput state. The game window is activated first and the active window is
checked, so keystrokes are aimed at the game and not at whatever else is on the
desktop.

## Address map

Every address here is evidence, not a guess; keep the provenance comment when
adding rows.

| Address | Meaning | Source |
|---|---|---|
| `0x400000` | PE image base (file-mapped; image bytes are readable at their VAs) | `/proc/<pid>/maps`, 2026-10-14 |
| `0x006cfae0` | `DAT_006cfae0`: four actor pointers, slot 0..3 | `research/decompiled/FUN_006348b0.c:13` |
| actor `+0xae04` | animation tick | `catalogs/timing-hooks.json` (7,741 sites, all `disp 0xae04`) |
| actor `+0xadf4` | animation phase | `docs/agents/animation-system-handoff.md` |

`0x006cae94` (per-slot input structs, stride 100 bytes) is the next row to add;
it is where `[2] = confirm`, `[3] = cancel`, `[0]/[1] = direction`
(`FRONTEND-PLAN.md` §"Input") — needed only if we inject input by memory instead
of by key.

## Not this tool's job

- It never patches the original's **code** (`docs/DIRECTION.md` §"Original-binary
  work"). Data writes, if ever needed, get recorded in the trace.
- It is not the differ. Port-side comparison lives with the port
  (`TRACE-SCHEMA.md`, once P1-1 freezes the schema).
