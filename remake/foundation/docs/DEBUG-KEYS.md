# In-battle debug keys (issue #48)

The original's battle scene has five test keys. This document is the recovered map, the gate
they sit behind, and what each one does in this port — written down so nobody has to
re-derive it. The code is [`gameplay/debug_keys.h`](../src/gameplay/debug_keys.h) (the
effects), [`main.cpp`](../src/main.cpp) (the fixed-step sampling and the injection) and
[`tests/debug_keys_test.cpp`](../tests/debug_keys_test.cpp) (the checks).

## 1. The recovered map — `FUN_00634f60`

Every key is read with `FUN_006586d0(dik)`, the DirectInput key-state helper, so the codes
are DIK scancodes. The keys are read once per battle frame, in this order, and every effect
is idempotent (a held key re-applies each frame).

| key | DIK | recovered effect (address in `FUN_00634f60`) |
|---|---|---|
| **Escape** | `0x01` | `:50-52` — sets `scene+0x4a40 = 1`, the battle's leave/abort flag |
| **F2** | `0x3c` | `:148-155` — `[fighter+0x860] = 0` for **all four** slots: the COM/AI enable flag, so a COM stops moving and attacking |
| **F3** | `0x3d` | `:156-170` — `[fighter+0x860] = 1` **only** where `3 < DAT_006cfaf8/fafc/fb00/fb04` (the per-slot controller/type array): a human slot is never handed to the AI |
| **F1** | `0x3b` | `:171-183` — `scene+0x12b0 = 0` and `scene+0x12bc = 0`, then `[fighter+0x7a8] = [fighter+0x7a4] = 10000` for all four slots (max HP and HP at once) |
| **F4** | `0x3e` | `:184-204` — every fighter's gauge, chosen by its per-slot byte `[fighter+0x318]`: `1` → `+0x83c = +0x32c`, `2` → `+0x840 = +0x324`, otherwise `+0x838 = +0x324` |

### The gate

```c
if (DAT_006cfce9 == '\0') { /* all four keys */ }
```

`DAT_006cfce9` is written by the **title screen's item switch**
(`FUN_00410f60:105-120`): item 0 (**story**) sets `1`, item 1 (**versus**) sets `0`, every
other item sets `0`. So the keys are live in a versus/free battle and dead in story mode —
which is where a player or a tester meets them.

### What the addresses are

* `scene+0x12b0` / `+0x12bc` are the two sides' **balloon percentages**, not an unknown
  counter: the balloon entries are 12 bytes each at `scene+0x12ac` / `+0x12b8`
  (`+0x00` side, `+0x04` balloon %, `+0x08` capacity), `FUN_00639650` credits the `+0x04`,
  and `FUN_00635d40` reads both to name the round's winner. The wiki's own description of F1
  — "max HP for everyone + both balloons to 0%" — agrees.
* `[fighter+0x7a4]` / `[fighter+0x7a8]` are HP and max HP. `10000` is the original's full
  capacity, i.e. this port's `Fighter::max_hp()` (the port's `kMaxHP` is 100, the same value
  at ×100 — see the `UNIT:` note in `main.cpp`'s result record).
* `[fighter+0x860]` is the AI enable flag. `FUN_0041efa0:10` initializes it
  (`1 - (type != -2)`) and `FUN_00417200:47` sets it to 1 when the roster assigns a COM
  slot; `FUN_00421730:10` gates the AI's own decision on it, and `FUN_00634f60:60-73`
  zeroes a slot's whole input block while it is clear.
* `DAT_006cfaf8…fb04` is the per-slot controller/type array the selection screen fills
  (`FUN_0040d130:70` writes `4` for an unset/COM slot, `:88` copies a human panel's
  controller, `:108` tests `< 4`). **4 is COM** in this port too
  (`ui/frontend_state.h`).

## 2. What the port does (port rules are labelled)

### 2.1 The gate: "always active in a battle"

The port has no story mode, so the faithful equivalent is **always active in a battle**: the
keys are sampled inside `tickMatch`, which is the only place a battle ticks. The recovered
`DAT_006cfce9` therefore has no port counterpart and is not invented.

`--no-debug-keys` switches them off; the keys are **on by default**. That default is the
faithful one (the original's keys are live in a versus battle) and it costs nothing to the
"off stays byte-identical" rule, because every verification run ignores the physical devices
(issue #29) — `key_down()` reads `false` for every key, so no capture can move. The switch
exists for the one run that does read devices in a capture (`--devices --out=`, a windowed
recipe), where a stray F-key would otherwise silently change the frame.

### 2.2 The fixed-step boundary

The keys are sampled **once per simulation tick**, at the top of `tickMatch`, on the tick
whose number is `app.matchFrame` (1-based) — the same clock the banked captures and the
input scripts use — and the effect lands on that same tick. A tick-keyed key is what makes a
capture reproducible (D9); a per-frame poll in the view pass
(`updateMatchViews`) would not be.

Consequences worth knowing:

* the tick is the unit of the injection: `--debug-keys=f2@300` holds F2 on tick 300 alone,
  which every effect here makes enough;
* while the battle is **paused** `tickMatch` does not run, so F1-F4 and Escape are not read.
  That matches the original for F1-F4 (`FUN_00634f60`'s four keys sit inside the un-paused
  branch) and differs for Escape, which the original reads *before* its pause gate. Issue
  #15's pause is not this issue's to change, so the port keeps its own gate and says so.

### 2.3 The keys in the port

| key | port effect |
|---|---|
| **Escape** | the recovered leave request (`scene+0x4a40 = 1`), resolved by the host through the same path #15's "Return to selection" row uses |
| **F2** | `Match::set_ai_enabled(i, false)` for all four slots; the host then feeds a disabled **COM** slot `App::neutralInput` instead of its brain's decision (the original's zeroed input block), and does not tick the brain at all |
| **F3** | `Match::set_ai_enabled(i, true)` for the slots whose panel controller is `>= 4` (`gameplay::kComControllerType`), i.e. the port's `3 < DAT_006cfaf8…`; the loop is guarded and the post-condition is checked in every build, so a human slot's flag can never move |
| **F1** | `MatchEconomy::reset_balloons()` (both sides) and `Fighter::restore_full_hp()` for all four |
| **F4** | `Fighter::fill_gauges()` for all four — see the selector note below |

The AI flag lives on **`Match`**, next to the lock table: it is per-fighter battle state that
the original keeps on the character object, it is reset with the battle
(`Match::reset` → all four enabled, the original's initialized value), and a capture
reproduces it from the same tick-keyed key script the rest of the simulation is a function
of. The host is its only reader, and only for a slot no controller owns — which is exactly
what keeps F3's ownership rule true.

Two mappings are port rules, because the port has no counterpart for what the original
carries:

* **F4's selector.** The original fills ONE of three gauges per fighter, chosen by the
  per-slot `+0x318` byte (written at load by `FUN_0064ab30` from `scene+0x5328`, through
  `FUN_0041dc80`). The port has no such byte, so F4 fills **every meter it models**, which is
  the union of the original's three arms. The arm each meter corresponds to is evidence-pinned:
  `+0x838` is written by the level-1 attack start (`FUN_00421fe0`) → the port's MAIN pool,
  `+0x83c` by the level-2 start (`FUN_004220e0`) → CHARGE, and `+0x840` by the hyper
  activation (`FUN_00422160`, which also restores HP) → the hypermode gauge. The wiki's "F4
  maxes Hypermode" is the third arm.
* **F1's HP unit.** The original writes the absolute `10000`. The port writes the fighter's
  own full capacity (`max_hp()`, `100` in the original's units for a default battle and
  scaled by the battle's HP setting) and leaves `max_hp()` alone: in the port that field IS
  the battle's configured capacity, not a value a debug key should rewrite.

### 2.4 Escape's second binding

Escape is the recovered leave **and** issue #15's "Escape opens the pause menu instead of
quitting the process" (`docs/PAUSE.md`). The pause binding is #15's and is not this issue's to
change, so the port splits them by where the pause exists: in a session where the pause menu
is available — a plain interactive battle, `battlePauseAvailable()` — the physical Escape
stays the pause key and the recovered leave is reached through the menu's return row; in
every other battle (a capture, a `--frames` run, the standalone harness) Escape is the
original's key again. A **scripted tap is never redirected**: `--debug-keys=esc@T` is the
injection the evidence uses.

## 3. Using them

```
--no-debug-keys            make the five keys inert (see 2.1)
--debug-keys=f2@300,f3@600 KEY@TICK list: the key is held on that 1-based
                           simulation tick alone (f1 f2 f3 f4 esc)
```

A headless run has no window and no key events, so the scripted list is how an evidence run
injects a key; #49 measured that the input scripts do not reach a front-end battle's human
panel, so nothing else was assumed to work.

`DAYBREAK_DEBUG_KEYS=1` prints one evidence line per fighter per tick — controller, AI flag,
position, HP, the three meters, the fighter's state and its swing/shot events. It is behind
an environment variable because it is one line per fighter per tick and no other run wants
that volume.

Worked example (a live four-fighter battle, one COM on panel 3, F2 at tick 400 and F3 at
900 — see `RELEASE-CHECKLIST.md` §3 for the recipe form):

```bash
DAYBREAK_DEBUG_KEYS=1 ./build/linux/foundation_demo --install=<game-dir> \
  --screen=battle --local-players=3 --debug-keys=f2@400,f3@900 \
  --headless --out=/tmp/debugkeys.ppm --size=960x540 --frames=1400
```

## 4. Not covered

* The pause key itself (#15) and `leaveBattleTo`.
* What the original does with `scene+0x4a40` after it is set — the port takes the leave the
  same frame's tick returns, before the round-over transition, because an abort has no result
  screen. The original's ordering against its own round machine is not recovered.
* The two edge fields `FUN_00634f60:60-73` preserves across its input-block memset
  (`+0x28c`, `+0x298`): the port's neutral input carries no edges at all, which is the same
  observable result (nothing is held and nothing new is pressed).
