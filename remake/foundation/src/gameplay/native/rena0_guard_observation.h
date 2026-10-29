// P2-7 (2e) guard family — the recovered guard body, adapted for offline observation with
// attribution.
//
// Adapted from the local bundle's `battle_guard_motion.hpp` (DaybreakRebuild-20261010), which
// the owner's 2026-10-14 licence note allows vendoring with attribution. States 390/391/392 in
// the original's `438310`: 390 is preparation/hold/release, 391 a successful guard, 392 the
// attacker's recoil after being guarded. Effects, audio and the animation-counter advance stay
// caller-owned in the original, and they stay caller-owned here.
//
// Only the host-side plumbing differs from the bundle: the returned step is a struct rather
// than a brace list, and the steering helper comes from the shared `rena0_steering.h`.
//
// The body's `gauge` (0..1000, drained 10 per frame in phase 1) is NOT the port's stamina
// (0..100, measured at 25 per second). The two are not interchangeable, and the gauge economy
// is already an unresolved seam item (contract §2b declares `charge_gauge` unsupported), so
// this module exposes the body's own numbers and never claims they are the port's.
#pragma once

#include "gameplay/native/rena0_steering.h"

#include <algorithm>
#include <cstdint>

namespace gameplay::native {

struct Rena0GuardMotion {
    std::uint32_t state = 390;
    std::uint32_t phase = 0;
    std::uint32_t frame = 0;
    std::uint32_t hold_count = 0;
    std::uint32_t contact_flags = 0;
    int gauge = 1000;
    bool grounded = true;
    bool complete = false;
    bool button_a = false;
    bool button_b = false;
    float speed = 0.f;
    float vertical = 0.f;
    float gravity = 0.f;
    float offset = 0.f;
};

struct Rena0GuardStep {
    int state = -1;            // -1 = no state proposal
    int phase = -1;            // -1 = no phase proposal
    bool clear_contacts = false;
};

inline Rena0GuardStep advance_rena0_guard(Rena0GuardMotion& p) {
    if (p.complete) {
        if (!p.grounded) {
            p.gravity = .5f;
            return {43, -1, false};
        }
        return {0, -1, false};
    }
    if (!p.grounded) {
        p.gravity = .5f;
        return {p.state == 391 ? 103 : 43, -1, false};
    }
    if (p.state == 390) {
        if (p.phase == 1) p.gauge = std::max(0, p.gauge - 10);
        bool clear = false;
        if (p.phase == 0 && p.frame == 0) {
            p.speed = 0.f;
            p.contact_flags = 0;
            clear = true;
        }
        if (p.phase == 0) approach_battle_offset(p.offset, 0.f, 20.f);
        if (p.phase == 1 && (!p.gauge || !p.button_a || !p.button_b)) return {-1, 2, false};
        if ((p.contact_flags & 2u) && p.gauge > 0) return {391, -1, true};
        if (p.phase == 2) p.speed = std::max(0.f, p.speed - 1.f);
        return {-1, -1, clear};
    }
    if (p.state == 391 || p.state == 392) {
        if (p.phase == 0 && p.frame == 0) {
            p.speed = -15.f;
            p.hold_count = 0;
        }
        if (p.state == 391 && p.phase < 2 && (p.contact_flags & 2u)) return {391, -1, true};
        if (p.phase == 0 && ++p.hold_count > 20) return {-1, 1, false};
        if (p.phase < (p.state == 391 ? 3u : 2u)) p.speed = std::min(0.f, p.speed + 1.f);
    }
    return {};
}
}  // namespace gameplay::native
