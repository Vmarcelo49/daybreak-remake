#pragma once
// The deterministic press pattern the --local-players verification flag feeds to local
// controllers that have no attached pad (issue #12).
//
// WHY it exists: a headless split-screen run needs input for N controllers, and the only
// device such a run has is the keyboard (controller 0). The host applies this pattern to a
// pad-less controller's tick input once per SIMULATION TICK, after the device sample, so the
// pattern a run produces does not depend on the render frame rate and a real pad always
// wins. Controller 0 is the keyboard and is never overridden (a headless run drives it with
// --script=).
//
// It is synthetic input and is reported as such: it is not physical-pad evidence, and no
// claim about real controllers rides on it.
//
// The pattern is a pure function of (controller, tick): deterministic across runs and
// platforms, different per controller so independent views cannot be mistaken for one view
// drawn twice, and never empty so a fighter always has something to do.
#include <cstdint>

namespace fnd::input {

struct SyntheticPadState {
    bool up = false, down = false, left = false, right = false;
    bool melee = false, shoot = false, jump = false, guard = false, lock = false;
    bool any() const {
        return up || down || left || right || melee || shoot || jump || guard || lock;
    }
};

// `tick` is the match's 1-based 64 Hz tick. Windows are short enough to read as taps and
// long enough to survive a render that samples held state once per tick.
inline SyntheticPadState syntheticPadState(int controller, uint64_t tick) {
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
    s.lock  = (tick + phase * 31) % 256 < 2;   // a per-view target switch, on purpose
    return s;
}

}  // namespace fnd::input
