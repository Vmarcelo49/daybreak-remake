// Held directional axes as the original's dispatcher reads them.
//
// Shared by the legacy decision path and the P2-7 pilot adapter so the two cannot drift: the
// admission branches read these axes, and a pilot view built with a different sign convention
// would compare against a question the port never asked. The D-pad wins over the stick, and
// SDL's positive-Y-down convention flips for the forward axis (fighter.cpp's original note).
#pragma once

#include "input/input.h"

namespace gameplay {

// Held directional axes as the original's dispatcher reads them: the D-pad wins
// over the stick, and SDL's positive-Y-down convention flips for the forward axis.
inline int held_axis_x(const input::PlayerState* input) {
    if (!input) return 0;
    const int digital = (input->down[input::Action::Right] ? 1 : 0) -
                        (input->down[input::Action::Left] ? 1 : 0);
    if (digital) return digital;
    if (input->stick_x > input::kStickDeadzone) return 1;
    if (input->stick_x < -input::kStickDeadzone) return -1;
    return 0;
}

inline int held_axis_z(const input::PlayerState* input) {
    if (!input) return 0;
    const int digital = (input->down[input::Action::Up] ? 1 : 0) -
                        (input->down[input::Action::Down] ? 1 : 0);
    if (digital) return digital;
    if (input->stick_y < -input::kStickDeadzone) return 1;
    if (input->stick_y > input::kStickDeadzone) return -1;
    return 0;
}

}  // namespace gameplay
