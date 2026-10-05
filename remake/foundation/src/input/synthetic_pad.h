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

// `tick` is the match's 1-based 64 Hz tick. Windows are short enough to read as taps and
// long enough to survive a render that samples held state once per tick.
//
// `lockTaps` is opt-in (`--lock-taps`) and OFF by default. Its LockSwitch tap retargets the
// camera every ~4 s in every view — a real gesture, but one a viewer of an evidence run
// cannot tell apart from a camera defect: four views each sweeping between fighters reads as
// "the camera keeps switching target". Gameplay is unaffected either way (a played battle
// never retargets itself), and the flag keeps the per-view retarget path exercised when a
// run is specifically about it.
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

// The SELECT-screen pattern: `tick` counts ticks since the selection screen appeared.
// Each pad-less controller walks ITS OWN panel — Team -> Character -> Weapon -> Hypermode ->
// Controller -> Ready (screen_select.cpp's phases) — nudges the roster cursor a different
// number of times so the four picks are not the same character, steers its cursor to the OK
// cell (row 0, column 2: screen_select.cpp's `panel(c) = pos%3 + pos/3*2` grid, where column
// 2 is the action column), and then keeps confirming so the stage page, VS, the countdown and
// the results all advance. Offsets are per controller (12 ticks apart) so the panels do not
// race each other.
inline SyntheticPadState syntheticMenuPadState(int controller, uint64_t tick) {
    SyntheticPadState s;
    if (controller < 0 || controller > 3) return s;
    const uint64_t base = 4 + (uint64_t)controller * 12;
    if (tick < base) return s;
    const uint64_t t = tick - base;
    // Roster nudge: one sequence per controller so the four panels land on distinct
    // characters that also GEAR UP on this install. The selection diamond's one- and
    // two-press neighbours of character 0 are 2 (left), 3 (up) and 4 (right), then
    // 1 (left,left), 5 (left,up) and 10 (right,right); the slot-0 item join fails loudly for
    // Satoko (3), Oishi (8), Akasaka (9), Irie (10), Chie (11), Hanyu (14) and Takano (7)
    // today, so the four panels take 0 Rena, 2 Keiichi, 4 Rika and 1 Mion, all verified.
    if (t == 4 || t == 6) {
        switch (controller) {
            case 1: s.left = t == 4; break;
            case 2: s.right = t == 4; break;
            case 3: s.left = true; break;
            default: break;
        }
        if (s.any()) return s;
    }
    switch (t) {
        case 0: case 12: case 20: case 28: case 36:   // the five panel confirms
            s.confirm = true;
            break;
        // Cursor to the OK cell from the start cell `c + (c > 1)`. The grid's axes are
        // swapped (screen_select.cpp: left/right cycle the row, up/down the column): 1 starts
        // on row 0 column 1 (one down), 2 and 3 start on row 1 (right, then down; 2 is one
        // column further left).
        case 56:
            s.right = controller >= 2;
            break;
        case 60:
            s.down = true;
            break;
        case 62:
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
