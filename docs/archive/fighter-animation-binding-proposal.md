# Fighter animation binding proposal (from the Rena #71 audit)

2026-10-13 · Rena+0/+1/+2 audit vehicle: `rena_animation_audit_test`
(218 checks green, install-backed, no live parity claimed).

## Problem

The clip a fighter plays is resolved in at least six places that can
disagree with each other:

- `state_move_id()` / `state_to_move_id()` map port states to NN.dat rows;
- `dash_move_for()` infers dash rows from raw input direction;
- `resolve_attack_move()` picks bounded attack candidates;
- `rena_dash_admission()` (pure helper, tested, **not wired**) maps
  history commands to the same dash rows with the opposite side mapping;
- `try_switch_animation()` binds the row's phase tag, falling back to set 0;
- `refresh_state_move()` / `advance_animation_phase()` advance the phase cursor.

Two audit findings prove the scatter is load-bearing, not stylistic:

1. **Side-dash mirror (fixed 2026-10-13).** `dash_move_for` mapped Left -> 23 /
   Right -> 24 while every admission switch maps history command 3 (x=-1,
   Left) -> row 24 and command 4 (x=+1, Right) -> row 23
   (`FUN_00445ee0:86-95`; donor `rena_dash.hpp:11`,
   `battle_roster_air_dash_admission.hpp:8`). Gameplay prints showed Left
   playing set 22 (`Anim-102`) instead of set 19 (`Anim-105`). The pure
   helper already had it right; the product path did not read it.
2. **Silent fallbacks.** Rena+1/+2 air dash binds no row (`dash_move_for`
   returns -1 off Rena+0) and plays set 0 with the fallback flag — correct
   per current evidence, but nothing forces a future editor to notice.
   Reaction row 103 carries `0xCCCCCCCC` priority/cancel words in all three
   shipped NN.dat files while binding sets `[95, 27]` fine; any logic that
   reads those words for reactions would inherit garbage.

## Proposal: one pure binding function

Add `gameplay/animation_binding.h` with a single pure resolver:

```cpp
struct AnimationBinding {
    int move = -1;        // NN.dat row, or -1 when no selector covers the state
    int set = 0;          // animation set index to bind
    bool fallback = false;
    const char* reason = nullptr;  // "missing-row", "missing-set", "no-selector"
};

AnimationBinding resolve_animation_binding(
    const CharacterMoves* moves, int characterIndex, int weaponId,
    FighterState state, int dashMove, int attackMove, int shotMove,
    int jumpMove, int phase);
```

Rules, in order:

1. Rows come only from NN.dat presence (`find()` + `first_set_index() >= 0`)
   and the recovered selectors (history-command mapping for dashes,
   dispatcher tables for attacks/shots, jump chain by physics). No
   direction->row inference tables beside the command map.
2. Sets come only from the row's phase tag (`phase_set_index(phase)`),
   bounds-checked against the model; anything else is a named fallback.
3. `Fighter` computes the binding once per update, stores it, and
   `try_switch_animation()` only applies the stored binding. Phase
   advancement reads the same stored move.
4. Fallback reasons are first-class test surface: the audit asserts exact
   `(move, set)` where recovered and asserts the named reason where open
   (e.g. Rena+1/+2 air dash today).

## Migration (no behavior change first)

1. Extract the resolver with the audit test pinning current behavior.
2. Route `dash_move_for` through the history-command map (share the table
   with `rena_dash_admission` instead of duplicating it).
3. Replace the `state_move_id` + `state_to_move_id` split with the resolver.
4. Keep the Guard hold-clip rule verbatim (recovered: a block binds nothing).

## Non-goals

- No live-parity claims; the audit is automated verification only (#71 boxes
  still need live matches compared against the original).
- No other characters: the resolver is combo-agnostic but only Rena rows are
  pinned; other combos keep today's paths until audited.
- No projectile/dash-motion changes; those gaps stay where they are
  (matrix §6, iteration log).
