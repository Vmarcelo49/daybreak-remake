---
name: combo-test
description: Test one Higurashi Daybreak character + weapon combo on the remake, without a person at the keyboard. Use when asked to check, study or debug how a combo, its traps, bullets, statuses or hypermode behave ("teste a Satoko 1", "is Rena 2's shot right?"), or to reproduce a report about a specific weapon.
---

# Testing a combo

A combo is a character and a weapon, named `Name N` (`Satoko 1` is her second weapon). There is no
bare fighter: every run binds both. Read `AGENTS.md` first for the rules this sits under, and
`docs/DEBUG-KEYS.md` for every option named here.

The method: read what the original's code and the combo's data say should happen, write down the
input as a plan, run it, and compare the log against the prediction. A run on its own proves nothing
about the original, so the prediction comes first.

Keep every run headless and silent: `--headless --no-audio`, never a window on the owner's desktop.
Everything below assumes `./build.sh linux`, and `GAME` standing for the game install folder.

## 1. Read what the combo should do

Character indices: 0 rena, 1 mion, 2 keiichi, 3 satoko, 4 rika, 5 shion, 6 tomitake, 7 takano,
8 ohishi, 9 akasaka, 10 irie, 11 chie, 12 kasai, 13 akane, 14 hanyu, 15 natumi.

```bash
build/linux/simctl --game "$GAME" --bullets satoko:1 | iconv -f cp932 -t utf8
```

That lists the bullets the data declares, with radius, damage and status. `data/item/<NNN>.ini` in the
install has the same rows with their comments.

For the behaviour, `src/battle/core/character_dispatch.hpp` names the handler for the character and
weapon, and `research/decompiled/FUN_<address>.c` holds it. The input function usually follows the
handler. Write down the prediction with its addresses: which input, which row, which bullet, what it
does. Load the `reverse-engineer-anything` skill only when the corpus does not answer a bounded
question.

## 2. Write a plan

Plans live in `tests/combos/<combo>-<what>.plan`. Keep the ones that show something: they are the
project's record of how to reach a behaviour.

```
# What this plan shows, and which --debug-keys it needs.
# Expect in --events: what the prediction says.
0 70 545 z=-1          # slot, from tick, to tick (exclusive), tokens
0 565 595 shoot
```

Tokens: `x=N`, `z=N`, `jump`, `melee`, `shoot`, `target`, `guard`, `tactics`. `z=-1` is forward. `melee
shoot` together is the hypermode chord.

Commands are blocked until about tick 180, so a chord or attack goes after tick 200.

## 3. Run it and read the log

```bash
build/linux/simctl --game "$GAME" --roster satoko:1:human rena:0 rena:0 mion:0 --stage 21 \
  --special-mode 0 --ticks 1500 --debug-keys f2@0 \
  --script tests/combos/satoko1-status-traps.plan --events -
```

Slots 0 and 1 are one team and 2 and 3 the other. `f2@0` stops the COMs so nothing moves but the plan.
Other useful keys: `f4@150` fills the hypermode gauge, `f1@T` restores health, `f5@T` refills
magazines, `f6@T` prints a report line of every fighter.

`--events -` prints rows, health, trap level, hypermode, status on and off, and new bullets, each with
its tick. Compare with the prediction. To cover the variants, change one thing per run: the direction
held, `--special-mode` 0, 1 and 2, or the enemy.

A status or a level that never comes usually means the plan is wrong, not the game: the enemy was
pushed out of the trap's radius, or a press fell inside the opening's blocked ticks. Read the plan's
geometry before suspecting the core.

## 4. See it

Capture the same run in the real game, on the fighter whose view matters:

```bash
build/linux/daybreak --headless --no-audio --match --install="$GAME" --stage="$GAME/data/stage21" \
  --sim-roster="$GAME/data/satoko@1,$GAME/data/rena@0,$GAME/data/rena@0,$GAME/data/mion@0" \
  --plan=tests/combos/satoko1-status-traps.plan --debug-keys=f2@0 --special-mode=0 \
  --view-fighter=2 --frames=1000 --size=640x360 --out=<scratchpad>/view.ppm
```

`--frames` is the tick the picture lands on, so take it from the `--events` log. Look at the picture:
a capture exists to be looked at. It stays in the scratchpad.

To be sure the picture shows the run you logged, give both programs `--hash-log` and `cmp` the files.
Same roster, stage, plan, keys and `--special-mode`, or they differ from the first tick.

## 5. Keep it and report it

- If a plan demonstrates something worth holding, add it to `test_saved_combo_plans` in
  `tests/sim_core_test.cpp`, so CTest keeps it true.
- Name the evidence tier of every claim. Reading `FUN_` code is tier 2 for what the original does. A
  `simctl` run is tier 4 for what the port does. A capture is tier 5. None of them is original-runtime
  parity, and a run matching the code is a consistency check, not proof about the original.
- Say what was not run: which variants, which enemies, which inputs.
- A disagreement with the recovered code is a bug in the wrapper or a core patch to cite in
  `src/battle/core/PATCHES.md`. Never hand-write combat around it.
- Each investigation gets the attempt ceiling in `AGENTS.md`: past it, stop and report what is missing.
