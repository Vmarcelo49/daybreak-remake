// Steering helpers shared by the adapted recovered bodies.
//
// Adapted from the bundle's `battle_steering.hpp` (DaybreakRebuild-20261010) with its own
// notes, including `42dc20`'s: a full turn compensates movement; snapping the final small
// offset does not. Kept in one place so the shot and guard bodies cannot drift apart.
#pragma once

#include <cmath>

namespace gameplay::native {

// Steering, adapted from the bundle's `battle_steering.hpp` (`42dc20` note included): a full
// turn compensates movement, snapping the final small offset does not.
inline void approach_battle_offset(float& offset, float target, float step) {
    volatile float delta = offset - target;
    if (delta < -180.f) delta = delta + 360.f;
    if (delta > 180.f) delta = delta - 360.f;
    if (step <= std::abs(float(delta))) {
        if (delta < 0) {
            volatile float value = step + offset;
            if (value > 180.f) value = value - 360.f;
            offset = value;
        } else if (delta > 0) {
            volatile float value = offset - step;
            if (value < -180.f) value = value + 360.f;
            offset = value;
        }
    } else {
        offset = target;
    }
}

inline void approach_battle_offset_preserving_movement(float& offset, float& movement, float step) {
    float delta = offset;
    if (delta < -180.f) delta += 360.f;
    if (delta > 180.f) delta -= 360.f;
    if (std::abs(delta) < step) {
        offset = 0.f;
        return;
    }
    if (delta < 0) {
        offset += step;
        movement -= step;
        if (offset > 180.f) offset -= 360.f;
        if (movement < -180.f) movement += 360.f;
    } else if (delta > 0) {
        offset -= step;
        movement += step;
        if (offset < -180.f) offset += 360.f;
        if (movement > 180.f) movement -= 360.f;
    }
}

}  // namespace gameplay::native
