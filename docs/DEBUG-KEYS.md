# In-battle debug keys

The original's battle scene has test keys, and the port carries them on the vendored core. This
document is the recovered map, the gate, what the port adds, and how a tool uses them. The code is
`Battle::apply_debug_keys` ([`battle.cpp`](../src/battle/battle.cpp)) for the effects,
[`match.inc`](../src/app/match.inc) for the physical keys, and
[`debug_tools.h`](../src/battle/debug_tools.h) for the schedule and the report line. Checks:
`test_debug_keys` in [`sim_core_test.cpp`](../tests/sim_core_test.cpp).

To test a character + weapon combo with them, use the `combo-test` skill
(`.agents/skills/combo-test/SKILL.md`).

## 1. The keys

| key | effect | evidence |
|---|---|---|
| **F1** | full health for all four, both balloons to 0 | recovered: `FUN_00634f60:171-183` |
| **F2** | every COM stops deciding; a stopped COM takes no input | recovered: `:148-155` |
| **F3** | COMs decide again; a human slot is never handed to the CPU | recovered: `:156-170` |
| **F4** | every fighter's hypermode gauge to its limit, by the fighter's mode | recovered: `:184-204` |
| **F5** | refills every magazine | port rule |
| **F6** | prints one report line per fighter to stdout | port rule |
| **F7** | freezes or resumes the battle | port rule |
| **F8** | while frozen, runs one tick | port rule |

F1 to F4 are recovered code (tier 2) for what the original does and a tier 4 test for what the port
does. They run in the original's order, F2, F3, F1, F4, and re-apply while held, as the original's
do. F5 to F8 do not exist in the original: they are here to debug, and nothing about the original
follows from them.

### The gate

```c
if (DAT_006cfce9 == '\0') { /* all four keys */ }
```

`DAT_006cfce9` is written by the title screen's item switch (`FUN_00410f60:105-120`): item 0 (story)
sets `1`, every other item sets `0`. So the keys are live in a versus battle and dead in story. They
also sit inside the un-paused branch.

The port keeps both: `Battle::apply_debug_keys` ignores them in story mode and while paused. **Port
rule:** they are dead online too, since a key pressed on one machine would desynchronize the others.

### What the addresses are

- `scene+0x12b0` and `+0x12bc` are the two sides' balloon percentages: entries of 12 bytes at
  `scene+0x12ac` and `+0x12b8`, credited by `FUN_00639650` and read by `FUN_00635d40` to name the
  round's winner.
- `[fighter+0x7a4]` and `+0x7a8` are health and maximum health. `10000` is full.
- `[fighter+0x860]` is the CPU enable flag. `FUN_0041efa0:10` initializes it, `FUN_00417200:47` sets it
  when the roster assigns a COM slot, `FUN_00421730:10` gates the decision on it, and
  `FUN_00634f60:60-73` zeroes a slot's input while it is clear.
- `DAT_006cfaf8` to `fb04` is the per-slot controller array; 4 is a COM.
- F4 reads the mode byte `[fighter+0x318]`: `1` sets `+0x83c = +0x32c`, `2` sets `+0x840 = +0x324`,
  anything else sets `+0x838 = +0x324`.

Escape is also read by `FUN_00634f60:50-52` as the battle's leave flag. The port keeps Escape as its
pause key (`docs/PAUSE.md`), so it is not one of these.

## 2. Options

Both `daybreak --match` and `simctl` take a schedule. A scheduled key lands right after its tick, in
both programs, so they stay comparable.

```
--debug-keys=f2@0,f4@300     hold a key on one tick; f1 to f6, simctl spells it --debug-keys f2@0
--no-debug-keys              daybreak: ignore the physical keys, for a windowed capture
--plan=<file>                daybreak --match: drive every slot from a plan, as simctl --script does
--special-mode=<m>           every fighter's hypermode: 0 Oyashiro, 1 Friendship, 2 Kakera
--view-fighter=<n>           daybreak --match: draw this fighter's own view, 0 to 3
--hash-log=<file>            one "tick state_hash" line per tick; simctl and daybreak write the same
```

`simctl` also takes `--events <file|->`, which logs what changes in a run (rows, health, trap level,
hypermode, status on and off, new bullets), and `--bullets C:W`, which prints the bullets a combo's
data declares. Bullet names are raw CP932; pipe them through `iconv -f cp932`.

The report line reads:

```
t=301 slot=0 satoko+1 row=0/0/246 hp=10000 gauge=1000 cpu=0 hyper=0 850/850 rounds=10,4 trap=0(63) status=0,0,0,0,0,0,0,0
```

`row` is state, phase and frame; `850/850` is the hypermode gauge over its limit; `trap` is Satoko 1's
level and timer; `status` is the eight hit status durations.

## 3. Things that catch a test

- Commands are blocked during the round's opening, until about tick 180, so a chord pressed earlier is
  lost. Keep the first attack past tick 200.
- `--match` defaults to hypermode 0 and `simctl` to 1, so a hash comparison needs the same
  `--special-mode` on both.
- The hypermode chord is `melee shoot` together. Kakera (2) has no chord: it starts on its own at the
  blow that would have killed.
