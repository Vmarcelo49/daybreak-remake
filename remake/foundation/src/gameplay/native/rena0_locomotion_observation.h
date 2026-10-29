#pragma once
// native/rena0_locomotion_observation.h — observation-only Rena+0 projection of the
// recovered slot-6 State0/State10 locomotion body (0x0043ffc0). F1-5 probe: the caller
// feeds mapped inputs, the function returns what the body would propose, and nothing is
// applied to the Fighter or to the legacy decision path.
//
// ATTRIBUTION — adapted from the external bundle
// `.local-analysis/daybreak-rebuild/DaybreakRebuild-20261010/source/src/`:
// roster_locomotion_native_control.hpp:25-56, battle_roster_walk.hpp:6-33,
// battle_walk_motion.hpp:7-15, battle_steering.hpp:7-29 (code adaptation with attribution
// permitted, AGENTS.md "Local-only"). Cross-checked against the addressed original in
// `research/decompiled/FUN_0043ffc0.c`: prologue :28-30, cases 0/10 :84-179, common tail :2439-2443.
//
// NARROWING — Rena+0 only (body 0x0043ffc0, ctor 0x0064c840, vtable 0x006a4e10): no
// character/weapon field, no 46-row dispatch table, no roster speed table. This combo
// takes the step-reset family (category change -> turn 20 = 0x41a00000, decay 1/update,
// floor 1, :121-166) and State10 walking speed is the literal 7.2f (0x40e66666, :167),
// not a table lookup. State10 zeroes +0x40 only after the airborne/no-input early returns
// (:111-120); +0xa0 is a blocking word tested in the prologue (:28-30). 0x4212f0,
// 0x421080/0x421100 and 0x421780 are NOT called: only the steering arithmetic is
// reproduced, so the caller keeps clock and phase ownership.
//
// FIELD MAP (+offset -> field -> owner; @ = FUN_0043ffc0.c)
//  +0xadec state     caller-translated legacy state: 0 idle, 10 walk (@:35,84,110);
//                    production FighterState::Idle=0/Walk=1 differs.
//  +0xadf4 phase     caller-mapped; the original advances it via FUN_00421100(phase+1)
//                    (@:2443), so next_phase is only a proposal the caller binds.
//  +0xae04 frame / +0xae08 secondary  caller-mapped clocks, +1 each tail (@:2439-2440).
//  +0xade4 duration  caller-mapped pointer: duration at +0, hold/gate at +0x20 (@:2442).
//  +0x278/+0x27c x,z caller-mapped stick words; only the sign is read (@:121-166).
//  +0x84 grounded    `!Fighter::airborne()`, normalized to 0/1 (@:98,111).
//  +0xa0 stop        UNMAPPED: fixture assumption (@:28).
//  +0x7f4 slow       UNMAPPED: fixture assumption, selects +5 over +40 (@:87-93).
//  +0xe8 direction   category latch (10 = none) = `param_1[0x3a]` (@:97,121-166).
//  +0x834 gauge      caller-mapped proxy (stamina*10), labelled a proxy (@:87-96).
//  +0x54 speed, +0x40 vertical, +0x58 gravity, +0x60 movement, +0x64 offset, +0x874 turn
//                    in/out fixture scalars; production has no per-tick twins. offset is
//                    DEGREES (`facing_yaw()` is radians; the +/-180 check is not a units
//                    check).
//
// LIMITS — the author's capture covers combos 15/0, 11/1, 8/1 and 14/1 only
// (docs/VALIDATION.md) with a false coverage gate, so this projection is source-backed
// for Rena+0, never runtime-validated for it.

#include <cmath>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace gameplay::native {

inline constexpr std::int32_t kRena0StateIdle = 0;       // +0xadec
inline constexpr std::int32_t kRena0StateWalk = 10;      // +0xadec
inline constexpr std::int32_t kRena0StateAirborne = 43;  // 0x2b proposal on losing ground
inline constexpr std::int32_t kRena0DirectionNone = 10;  // +0xe8 with no input
inline constexpr std::int32_t kRena0NoProposal = -1;     // next_state/next_phase: none
inline constexpr float kRena0State10WalkSpeed = 7.2f;    // 0x40e66666, :167

// roster_locomotion_native_control.hpp:20-22: the original adds 32-bit and
// reinterprets the bits, which is not a signed overflow-free add.
inline std::int32_t rena0_locomotion_add(std::int32_t value, std::uint32_t delta) {
    const auto bits = std::uint32_t(value) + delta;
    std::int32_t result;
    std::memcpy(&result, &bits, 4);
    return result;
}

// battle_steering.hpp:7-15 (0x42db10). `volatile` is kept from the bundle: these
// locals are the single-precision rounding points of the original.
inline void rena0_approach_offset(float& offset, float target, float step) {
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

// battle_steering.hpp:25-29 (0x421780): sign tests only, so a caller may pass the
// stick word or a normalized +/-1 without changing the result.
inline void rena0_steer_offset(float& offset, std::int32_t x, std::int32_t z, float step) {
    if (x < 0) rena0_approach_offset(offset, z < 0 ? 45.f : z == 0 ? 90.f : 135.f, step);
    else if (x == 0) {
        if (z < 0) rena0_approach_offset(offset, 0.f, step);
        else if (z > 0) rena0_approach_offset(offset, 180.f, step);
    } else rena0_approach_offset(offset, z < 0 ? -45.f : z == 0 ? -90.f : -135.f, step);
}

// All original inputs are required fields, with no default arguments and no member
// initializers: a missing or half-specified input must not compile.
struct Rena0LocomotionInput {
    std::int32_t state;      // +0xadec: 0 idle or 10 walk
    std::int32_t phase;      // +0xadf4
    std::int32_t frame;      // +0xae04
    std::int32_t secondary;  // +0xae08
    std::int32_t x;          // +0x278, sign only
    std::int32_t z;          // +0x27c, sign only
    std::int32_t grounded;   // +0x84, normalized 0/1
    std::int32_t stop;       // +0xa0 word, nonzero blocks (fixture assumption)
    std::int32_t slow;       // +0x7f4 status gate (fixture assumption)
    std::int32_t duration;   // +0xade4 -> int, phase period
    bool hold;               // +0xade4 -> +0x20, phase gate

    Rena0LocomotionInput(std::int32_t state_, std::int32_t phase_, std::int32_t frame_,
                         std::int32_t secondary_, std::int32_t x_, std::int32_t z_,
                         std::int32_t grounded_, std::int32_t stop_, std::int32_t slow_,
                         std::int32_t duration_, bool hold_)
        : state(state_), phase(phase_), frame(frame_), secondary(secondary_), x(x_), z(z_),
          grounded(grounded_), stop(stop_), slow(slow_), duration(duration_), hold(hold_) {}
};

// Carried control state, seeded by the caller and read back: production has no
// per-tick equivalent for these channels.
struct Rena0LocomotionMotion {
    float speed;             // +0x54
    float vertical;          // +0x40
    float gravity;           // +0x58
    float movement;          // +0x60
    float offset;            // +0x64, degrees
    float turn;              // +0x874, turn step
    std::int32_t gauge;      // +0x834
    std::int32_t direction;  // +0xe8 walk category latch; 10 when unset

    Rena0LocomotionMotion(float speed_, float vertical_, float gravity_, float movement_,
                          float offset_, float turn_, std::int32_t gauge_,
                          std::int32_t direction_)
        : speed(speed_), vertical(vertical_), gravity(gravity_), movement(movement_),
          offset(offset_), turn(turn_), gauge(gauge_), direction(direction_) {}
};

struct Rena0LocomotionEffects {
    std::int32_t state;       // resulting +0xadec
    std::int32_t phase;       // resulting +0xadf4
    std::int32_t frame;       // resulting +0xae04
    std::int32_t secondary;   // resulting +0xae08
    std::int32_t next_state;  // proposed +0xadec, kRena0NoProposal when unchanged
    std::int32_t next_phase;  // proposed +0xadf4, kRena0NoProposal when unchanged
    bool tail;                // the common AE04/AE08 tail ran

    Rena0LocomotionEffects(std::int32_t state_, std::int32_t phase_, std::int32_t frame_,
                           std::int32_t secondary_, std::int32_t next_state_,
                           std::int32_t next_phase_, bool tail_)
        : state(state_), phase(phase_), frame(frame_), secondary(secondary_),
          next_state(next_state_), next_phase(next_phase_), tail(tail_) {}
};

inline void require_rena0(bool ok, const char* what) {
    if (!ok) throw std::invalid_argument(what);
}

// Explicit-field validation. The state check is the bundle's own guard
// (roster_locomotion_native_control.hpp:28) and the numeric ranges are recovered
// writer domains; the float checks are finiteness only, so they catch an unmapped
// or indeterminate channel without inventing a physical bound.
inline void validate_rena0_locomotion_input(const Rena0LocomotionInput& in) {
    require_rena0(in.state == kRena0StateIdle || in.state == kRena0StateWalk,
                  "Rena0 locomotion: state must be 0 (idle) or 10 (walk)");
    require_rena0(in.grounded == 0 || in.grounded == 1,
                  "Rena0 locomotion: grounded must be normalized to 0/1");
    require_rena0(in.phase >= 0 && in.frame >= 0 && in.secondary >= 0,
                  "Rena0 locomotion: phase/frame/secondary must be non-negative tick counts");
    require_rena0(in.duration >= 0, "Rena0 locomotion: duration must be non-negative");
    require_rena0(in.slow >= 0, "Rena0 locomotion: slow (+0x7f4) must be non-negative");
}

inline void validate_rena0_locomotion_motion(const Rena0LocomotionMotion& m) {
    require_rena0(std::isfinite(m.speed) && std::isfinite(m.vertical) &&
                      std::isfinite(m.gravity) && std::isfinite(m.movement) &&
                      std::isfinite(m.offset) && std::isfinite(m.turn),
                  "Rena0 locomotion: motion channels must be finite");
    require_rena0(m.offset >= -180.f && m.offset <= 180.f,
                  "Rena0 locomotion: offset (+0x64) is degrees within +/-180");
    require_rena0(m.turn >= 0.f && m.turn <= 20.f,
                  "Rena0 locomotion: turn (+0x874) outside the recovered step domain");
    require_rena0(m.gauge >= 0 && m.gauge <= 1000,
                  "Rena0 locomotion: gauge (+0x834) outside the recovered 0..1000 domain");
    require_rena0(m.direction == kRena0DirectionNone || (m.direction >= 0 && m.direction <= 7),
                  "Rena0 locomotion: direction (+0xe8) must be 0..7 or 10");
}

// battle_walk_motion.hpp:7-15 projected to Rena+0. Precondition: x or z is nonzero,
// because the caller reaches this only after the no-input early return.
inline void rena0_state10_walk(Rena0LocomotionMotion& motion, std::int32_t x, std::int32_t z) {
    // :121-166 — category from the axis signs, z<0 tested first.
    const int direction = z < 0 ? (x > 0 ? 1 : x < 0 ? 2 : 0)
                         : z > 0 ? (x > 0 ? 5 : x < 0 ? 7 : 6)
                                 : (x > 0 ? 3 : 4);
    // Preserve the bundle's float decay. The addressed decompiler represents
    // float stores through an int-typed actor pointer; that spelling alone does
    // not establish numeric integer truncation in the compiled implementation.
    float step = motion.turn;
    if (direction != motion.direction) {
        motion.direction = direction;
        step = 20.f;
    }
    step -= 1.f;
    if (step < 1.f) step = 1.f;
    motion.turn = step;
    motion.speed = kRena0State10WalkSpeed;
    rena0_steer_offset(motion.offset, x, z, step);
}

// roster_locomotion_native_control.hpp:25-56 projected to Rena+0. Returns the
// proposed clock/state values; the caller observes them and applies nothing.
inline Rena0LocomotionEffects advance_rena0_locomotion_observation(
    Rena0LocomotionMotion& motion, const Rena0LocomotionInput& in) {
    validate_rena0_locomotion_input(in);
    validate_rena0_locomotion_motion(motion);

    // :28-30 — the prologue tests the +0xa0 word and returns before any write, so
    // the returned state/phase/clocks start as the current actor values.
    Rena0LocomotionEffects out{in.state, in.phase, in.frame, in.secondary,
                               kRena0NoProposal, kRena0NoProposal, false};
    if (in.stop != 0) return out;

    const auto propose_state = [&](std::int32_t next) {
        out.state = next;
        out.next_state = next;
        out.phase = 0;
        out.frame = 0;
        out.secondary = 0;
    };
    // :87-93, :168-173 — +0x834 gains 40, or 5 while the +0x7f4 status is set,
    // clamped upward (:94-96).
    const auto refill = [&]() {
        motion.gauge = rena0_locomotion_add(motion.gauge, in.slow > 0 ? 5u : 40u);
        if (motion.gauge > 1000) motion.gauge = 1000;
    };

    if (in.state == kRena0StateIdle) {
        // :84-97 — State0 writes +0x54, +0x40, the gauge, +0x874 and the category,
        // but not +0x60 movement, +0x64 offset or contact history.
        motion.speed = 0.f;
        motion.vertical = 0.f;
        refill();
        motion.turn = 0.f;
        motion.direction = kRena0DirectionNone;
        if (in.grounded == 0) {  // :98-101
            motion.gravity = 0.5f;
            propose_state(kRena0StateAirborne);
            return out;
        }
        if (in.x != 0 || in.z != 0) {  // :102-105
            propose_state(kRena0StateWalk);
            return out;
        }
    } else {
        // State10 (:110). The bundle's early +0x40 write does not run for this
        // combo: +0x40 is zeroed after both early returns, at :120.
        if (in.grounded == 0) {  // :111-115
            motion.gravity = 0.5f;
            propose_state(kRena0StateAirborne);
            return out;
        }
        if (in.x == 0 && in.z == 0) {  // :116-119
            propose_state(kRena0StateIdle);
            return out;
        }
        motion.vertical = 0.f;                   // :120
        rena0_state10_walk(motion, in.x, in.z);  // :121-178
        refill();                                // :167-176
        motion.movement = 0.f;                   // :177
    }

    // :2439-2440 — the common tail increments +0xae04 and +0xae08. 0x4212f0 is
    // not called here; the phase-change service of :2443 neither.
    out.frame = rena0_locomotion_add(out.frame, 1u);
    out.secondary = rena0_locomotion_add(out.secondary, 1u);
    out.tail = true;
    // :2442 — bump while the phase duration is behind the clock and the gate is open.
    if (in.duration < out.frame && !in.hold) {
        out.phase = out.next_phase = rena0_locomotion_add(out.phase, 1u);
        out.frame = out.secondary = 0;
    }
    return out;
}

}  // namespace gameplay::native
