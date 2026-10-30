#pragma once
// The deterministic press patterns the --local-players verification flag feeds to local
// controllers that have no attached pad (issue #12; the menu half added for issue #13's
// title-to-results run).
//
// WHY it exists: a headless run needs input for N controllers, and the only device such a
// run has is the keyboard (controller 0). The host applies these patterns to a pad-less
// controller's tick input once per SIMULATION TICK, after the device sample, so what a run
// produces does not depend on the render frame rate and a real pad always wins. Controller 0
// is the keyboard and is never overridden (a headless run drives it with --script=).
//
// It is synthetic input and is reported as such: it is not physical-pad evidence, and no
// claim about real controllers rides on it.
//
// Both patterns are pure functions of (controller, tick): deterministic across runs and
// platforms, different per controller so independent views cannot be mistaken for one view
// drawn twice, and never empty so a fighter always has something to do.
#include <cstdint>

namespace fnd::input {

struct SyntheticPadState {
    bool up = false, down = false, left = false, right = false;
    bool melee = false, shoot = false, jump = false, guard = false, lock = false;
    bool confirm = false, cancel = false;   // menu buttons (Jump / AttackA in the front end)
    bool any() const {
        return up || down || left || right || melee || shoot || jump || guard || lock ||
               confirm || cancel;
    }
};

// `tick` is the match's 1-based 60 Hz tick. Windows are short enough to read as taps and
// long enough to survive a render that samples held state once per tick.
//
// `lockTaps` is opt-in (`--lock-taps`) and OFF by default. Its LockSwitch tap re-picks
// every view's COMBAT target every ~4 s — a real gesture (issue #51: it never re-points a
// camera), but one a viewer of an evidence run cannot tell apart from churn: four views
// each cycling their targets reads as "the fight keeps changing its mind". Gameplay is
// otherwise unaffected (a played battle only re-targets when a human asks), and the flag
// keeps the per-view gesture path exercised when a run is specifically about it.
inline SyntheticPadState syntheticPadState(int controller, uint64_t tick, bool lockTaps = false) {
    SyntheticPadState s;
    const uint64_t phase = (uint64_t)(controller < 0 ? 0 : controller);
    // Movement: three 64-tick blocks of approach (screen up, which is toward the opponent
    // for a camera behind the fighter) then one block stepping sideways, offset per
    // controller so two views never walk the same way. The fighters have to reach each
    // other for a run to show hits at all.
    const uint64_t block = tick / 64 + phase;
    if (block % 4 != 3) {
        s.up = true;
    } else if ((tick / 128 + phase) % 2 == 0) {
        s.left = true;
    } else {
        s.right = true;
    }
    s.melee = ((tick + phase * 11) / 48) % 3 == 1;
    s.shoot = ((tick + phase * 17) / 64) % 3 == 2;
    s.jump  = (tick + phase * 23) % 128 < 3;
    s.guard = (tick + phase * 29) % 160 < 4;
    s.lock  = lockTaps && (tick + phase * 31) % 256 < 2;   // opt-in per-view target switch
    return s;
}

// The panel a pad-less controller starts on. SelectMenu's cursor starts at `c + (c > 1)` and
// its grid maps a cursor position to a panel with `pos % 3 + pos / 3 * 2`, so this is the
// panel whose slot tells the host whether the controller still has a character to pick.
inline int syntheticMenuStartPanel(int controller) {
    if (controller < 0 || controller > 3) return -1;
    const int pos = controller + (controller > 1 ? 1 : 0);
    return pos % 3 + pos / 3 * 2;
}

// The SELECT-screen pattern: `tick` counts ticks since the selection screen appeared.
// Each pad-less controller walks ITS OWN panel — Team -> Character -> Weapon -> Hypermode ->
// Controller -> Ready (screen_select.cpp's phases) — lands the roster cursor on a different
// character per panel, steers its cursor to the OK cell (row 0, column 2: screen_select.cpp's
// `panel(c) = pos%3 + pos/3*2` grid, where column 2 is the action column), and then keeps
// confirming so the stage page, VS, the countdown and the results all advance. Offsets are per
// controller (12 ticks apart) so the panels do not race each other.
//
// The walk runs on every select entry, because entering the select scene starts an empty
// selection (ui::FrontendState::beginSelection, FUN_00408330:143-158): a rematch round's screen
// is as fresh as the first round's. The roster nudge therefore always moves the ROSTER cursor,
// which only happens in the character phase this walk reaches; the conditional nudge it
// replaced existed because a re-entered screen kept the previous round's picks, and its nudge
// then moved the CURSOR instead — it pushed controller 2 onto the Back cell (`pos == 5`), whose
// confirm leaves to the title (measured on a rematch run, which ended at the title instead of
// the second round).
//
// The roster nudge is a HOLD, not a tap: the character phase's cursor slides at a fixed rate
// while a direction is down (FUN_00409340:239-244 — 4.0 units/tick horizontally, 3.0/tick
// vertically, on the SIGN of the stick) and the <20-unit magnet (FUN_00409340:257-270) pulls a
// one-tick tap straight back onto the character it started on. Each panel holds its own axis
// for the ticks its target needs — one diamond step is 12 ticks either way (48/4.0 = 36/3.0),
// so a two-cell reach is 24 — and lands EXACTLY on:
//   controller 1 -> character 2 Keiichi (one column left, one row up: 12 + 12)
//   controller 2 -> character 4 Rika    (one column right, one row up: 12 + 12)
//   controller 3 -> character 1 Mion    (two columns left, two rows up: 24 + 24)
// The same four picks the one-tick version documented (0/2/4/1 = Rena/Keiichi/Rika/Mion), each
// with weapon slot 0 — a character+weapon combo, never a bare fighter.
inline SyntheticPadState syntheticMenuPadState(int controller, uint64_t tick) {
    SyntheticPadState s;
    if (controller < 0 || controller > 3) return s;
    const uint64_t base = 4 + (uint64_t)controller * 12;
    if (tick < base) return s;
    const uint64_t t = tick - base;
    // Controller 0 is the keyboard, driven by the run's own script: it never nudges. The hold
    // comes after the team confirm at t == 0 (which opens the character phase) and finishes
    // well before the panel walk's next confirm, so no direction is down in another phase.
    const uint64_t holdStart = 4;
    const uint64_t reach = controller == 3 ? 24 : 12;
    const uint64_t holdEnd = holdStart + reach;
    const uint64_t upEnd = holdEnd + reach;
    if (controller >= 1 && t >= holdStart && t < holdEnd) {
        if (controller == 2) s.right = true; else s.left = true;
        return s;
    }
    if (controller >= 1 && t >= holdEnd && t < upEnd) {
        s.up = true;
        return s;
    }
    switch (t) {
        // The team confirm, then the four that leave character -> weapon -> hypermode ->
        // controller -> ready. The gap after t == 0 is the roster hold above.
        case 0: case 60: case 68: case 76: case 84:
            s.confirm = true;
            break;
        // Cursor to the OK cell from the start cell `c + (c > 1)`. The grid's axes are
        // swapped (screen_select.cpp: left/right cycle the row, up/down the column): 1 starts
        // on row 0 column 1 (one down), 2 and 3 start on row 1 (right, then down; 2 is one
        // column further left).
        case 104:
            s.right = controller >= 2;
            break;
        case 108:
            s.down = true;
            break;
        case 110:
            s.down = controller == 2;
            break;
        default:
            // After the panel walk, one confirm every 40 ticks: the first accepted OK press
            // opens the stage page (which controller 0's script configures — only its row 7
            // starts the match), and the rest walk VS -> battle -> results -> selection.
            if (t >= 152 && (t - 152) % 40 == 0) s.confirm = true;
            break;
    }
    return s;
}

}  // namespace fnd::input
