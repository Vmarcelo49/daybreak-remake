// P2-5 (2c) — offline body tests for the recovered Rena+0 bodies, independent of product
// integration. Nothing here drives Match or Fighter: each case feeds explicit scalars to a
// recovered body and checks what the body proposes, so a body-level regression is caught
// without the production path in the loop (DIRECTION.md §4 Phase 2 2c).
//
// Expectations cite addressed code or the bundle body, named per case. This test is
// data-free: the locomotion projection under src/gameplay/native/ is header-only and takes
// scalars, so no install and no fixture file are involved.
#include "gameplay/native/rena0_locomotion_observation.h"

#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <vector>

namespace {
namespace native = gameplay::native;

int checks = 0, failures = 0;

void check(bool ok, const char* name) {
    ++checks;
    if (!ok) ++failures;
    std::printf("  %-64s %s\n", name, ok ? "ok" : "FAIL");
}

void checkEq(long long expected, long long got, const char* name) {
    ++checks;
    const bool ok = expected == got;
    if (!ok) ++failures;
    std::printf("  %-64s %s", name, ok ? "ok" : "FAIL");
    if (!ok) std::printf(" (expected %lld, got %lld)", expected, got);
    std::printf("\n");
}

void checkNear(double expected, double got, const char* name, double tol = 1e-4) {
    ++checks;
    const bool ok = std::abs(expected - got) < tol;
    if (!ok) ++failures;
    std::printf("  %-64s %s", name, ok ? "ok" : "FAIL");
    if (!ok) std::printf(" (expected %g, got %g)", expected, got);
    std::printf("\n");
}

native::Rena0LocomotionInput in(std::int32_t state, std::int32_t phase, std::int32_t frame,
                                std::int32_t secondary, std::int32_t x, std::int32_t z,
                                std::int32_t grounded, std::int32_t stop, std::int32_t slow,
                                std::int32_t duration, bool hold) {
    return native::Rena0LocomotionInput{state, phase, frame, secondary, x, z, grounded,
                                        stop, slow, duration, hold};
}

native::Rena0LocomotionMotion motion(float speed = 0.f, float vertical = 0.f, float gravity = .5f,
                                     float movement = 0.f, float offset = 0.f, float turn = 0.f,
                                     std::int32_t gauge = 0, std::int32_t direction = 10) {
    return native::Rena0LocomotionMotion{speed, vertical, gravity, movement, offset, turn,
                                         gauge, direction};
}

// --- idle: FUN_0043ffc0 case 0 (:84-107) -------------------------------------------------
void idleCases() {
    {
        auto m = motion(9.f, 3.f, .5f, 7.f, 44.f, 6.f, 300, 4);
        const auto out = native::advance_rena0_locomotion_observation(m, in(0, 0, 5, 9, 0, 0, 1, 0, 0, 100, false));
        checkEq(0, out.state, "idle stays idle with no input");
        checkEq(native::kRena0NoProposal, out.next_state, "idle proposes no state change");
        check(out.tail, "idle runs the common tail");
        checkEq(6, out.frame, "idle increments the frame clock (5 -> 6)");
        checkEq(10, out.secondary, "idle increments the secondary clock (9 -> 10)");
        checkNear(0.0, m.speed, "idle clears speed (:85)");
        checkNear(0.0, m.vertical, "idle clears vertical (:86)");
        checkEq(340, m.gauge, "idle refills the gauge by 40 (:88)");
        checkEq(10, m.direction, "idle resets the direction category (:97)");
        checkNear(0.0, m.turn, "idle clears the turn step (:93)");
    }
    {
        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 0.f, 1000, 10);
        const auto out = native::advance_rena0_locomotion_observation(m, in(0, 0, 0, 0, 1, 0, 1, 0, 0, 100, false));
        checkEq(10, out.state, "idle admits walk on held input (:103-105)");
        checkEq(10, out.next_state, "the proposal names the walk state");
        check(!out.tail, "a state transition does not run the tail");
        checkEq(0, out.frame, "a transition resets the frame clock");
        checkEq(0, out.secondary, "a transition resets the secondary clock");
        checkEq(1000, m.gauge, "the gauge refill clamps at 1000 (:94-96)");
    }
    {
        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 0.f, 0, 10);
        const auto out = native::advance_rena0_locomotion_observation(m, in(0, 0, 0, 0, 0, 0, 0, 0, 0, 100, false));
        checkEq(native::kRena0StateAirborne, out.state, "losing the ground proposes the airborne state (:98-101)");
        checkEq(native::kRena0StateAirborne, out.next_state, "the airborne proposal names state 43");
        checkNear(0.5, m.gravity, "losing the ground sets gravity 0.5 (:99)");
        check(!out.tail, "the airborne proposal does not run the tail");
    }
}

// --- walk: FUN_0043ffc0 case 10 (:110-179) ----------------------------------------------
void walkCases() {
    {
        auto m = motion(0.f, 0.f, .5f, 5.f, 0.f, 0.f, 100, 10);
        const auto out = native::advance_rena0_locomotion_observation(m, in(10, 0, 3, 4, 1, 0, 1, 0, 0, 100, false));
        checkEq(10, out.state, "walk stays in walk while input is held");
        checkNear(7.2, m.speed, "walking speed is the recovered 7.2 (:167)");
        checkEq(3, m.direction, "right input selects category 3 (:121-133)");
        checkNear(19.0, m.turn, "a direction change resets the turn step to 20 then decays (:121-166)");
        checkEq(140, m.gauge, "walk refills the gauge by 40 (:168-176)");
        checkNear(0.0, m.movement, "walk zeroes the movement channel (:177)");
        checkEq(4, out.frame, "walk increments the frame clock");
    }
    {
        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 20.f, 100, 3);
        const auto out = native::advance_rena0_locomotion_observation(m, in(10, 0, 4, 4, 0, -1, 1, 0, 0, 100, false));
        checkEq(0, m.direction, "forward input selects category 0");
        checkNear(19.0, m.turn, "a category change resets the step to 19 after the decay");
        checkEq(10, out.state, "forward input keeps the walk state");
        check(out.tail, "a held walk runs the tail");
    }
    {
        // Release: the body proposes Idle without clearing the incoming speed, which the
        // F1-5 probe also recorded as a Walk->Idle divergence from the port's own clearing.
        auto m = motion(7.2f, 0.f, .5f, 0.f, -19.f, 8.f, 400, 3);
        const auto out = native::advance_rena0_locomotion_observation(m, in(10, 0, 4, 4, 0, 0, 1, 0, 0, 100, false));
        checkEq(native::kRena0StateIdle, out.state, "walk returns to idle when input is released (:116-119)");
        checkEq(native::kRena0StateIdle, out.next_state, "the release proposal names the idle state");
        check(!out.tail, "the release transition does not run the tail");
        checkEq(0, out.frame, "the release transition resets the frame clock");
    }
    {
        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 0.f, 100, 10);
        const auto out = native::advance_rena0_locomotion_observation(m, in(10, 0, 5, 5, 1, 0, 1, 256, 0, 100, false));
        checkEq(10, out.state, "a nonzero stop word suppresses the body (:28)");
        check(!out.tail, "the stop word also suppresses the tail");
        checkEq(5, out.frame, "the stop word leaves the frame clock untouched");
        checkNear(0.0, m.speed, "the stop word leaves speed untouched");
        checkEq(100, m.gauge, "the stop word leaves the gauge untouched");
    }
    {
        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 0.f, 100, 3);
        const auto out = native::advance_rena0_locomotion_observation(m, in(10, 2, 5, 7, 1, 0, 1, 0, 0, 3, false));
        checkEq(3, out.phase, "strict completion bumps the phase when duration < frame and hold is clear (:2442)");
        checkEq(3, out.next_phase, "the completion proposal names the new phase");
        checkEq(0, out.frame, "completion resets the frame clock");
        checkEq(0, out.secondary, "completion resets the secondary clock");
    }
    {
        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 0.f, 100, 3);
        const auto out = native::advance_rena0_locomotion_observation(m, in(10, 2, 5, 7, 1, 0, 1, 0, 5, 3, true));
        checkEq(105, m.gauge, "the slow status refills by 5 instead of 40 (:87-93)");
        checkEq(2, out.phase, "a held gate stops the phase from completing (:2442)");
        checkEq(6, out.frame, "the held gate still advances the frame clock");
    }
}

// --- requirement enforcement: the body's own validators ---------------------------------
void validationCases() {
    struct Case { const char* name; native::Rena0LocomotionInput input; };
    const std::vector<Case> bad = {
        {"state 1 (a port label) is rejected", in(1, 0, 0, 0, 1, 0, 1, 0, 0, 10, false)},
        {"state 43 is not an entry state", in(43, 0, 0, 0, 1, 0, 1, 0, 0, 10, false)},
        {"grounded must be 0 or 1", in(10, 0, 0, 0, 1, 0, 2, 0, 0, 10, false)},
    };
    for (const auto& c : bad) {
        auto m = motion();
        bool threw = false;
        try {
            native::advance_rena0_locomotion_observation(m, c.input);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        check(threw, c.name);
    }
    {
        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 0.f, 2000, 10);
        bool threw = false;
        try {
            native::advance_rena0_locomotion_observation(m, in(0, 0, 0, 0, 0, 0, 1, 0, 0, 10, false));
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        check(threw, "an out-of-domain gauge is rejected, not clamped silently");
    }
}

// --- invariant sweep: the body's own output space over the input space ------------------
void invariantSweep() {
    long long cases = 0, violations = 0;
    const std::int32_t states[] = {0, 10};
    const std::int32_t axes[] = {-1, 0, 1};
    for (std::int32_t state : states)
        for (std::int32_t x : axes)
            for (std::int32_t z : axes)
                for (std::int32_t grounded : {0, 1})
                    for (std::int32_t stop : {0, 1})
                        for (std::int32_t slow : {0, 1})
                            for (bool hold : {false, true})
                                for (std::int32_t frame : {0, 3, 7})
                                    for (std::int32_t direction : {10, 0, 3, 7}) {
                                        auto m = motion(0.f, 0.f, .5f, 0.f, 0.f, 0.f, 500, direction);
                                        const auto out = native::advance_rena0_locomotion_observation(
                                            m, in(state, 1, frame, 2, x, z, grounded, stop, slow, 3, hold));
                                        ++cases;
                                        if (!(out.state == 0 || out.state == 10 || out.state == 43)) ++violations;
                                        if (!(m.direction >= 0 && m.direction <= 7) &&
                                            m.direction != native::kRena0DirectionNone) ++violations;
                                        if (!(m.gauge >= 0 && m.gauge <= 1000)) ++violations;
                                        if (!(m.turn >= 0.f && m.turn <= 20.f)) ++violations;
                                        if (!(out.frame >= 0 && out.secondary >= 0 && out.phase >= 0)) ++violations;
                                        if (stop != 0 && out.tail) ++violations;
                                    }
    std::printf("  %-64s %s (%lld cases, %lld violations)\n",
                "invariant sweep over the input space", violations == 0 ? "ok" : "FAIL", cases, violations);
    ++checks;
    if (violations != 0) ++failures;
    check(cases == 2 * 3 * 3 * 2 * 2 * 2 * 2 * 3 * 4, "the sweep covered the whole cross product");
}
}  // namespace

int main() {
    std::puts("P2-5 offline body tests — recovered Rena+0 locomotion body (explicit inputs)");
    std::puts("\n== idle ==");
    idleCases();
    std::puts("\n== walk ==");
    walkCases();
    std::puts("\n== validators ==");
    validationCases();
    std::puts("\n== invariants ==");
    invariantSweep();
    if (failures) {
        std::fprintf(stderr, "RENA0_BODY: FAIL (%d of %d checks)\n", failures, checks);
        return 1;
    }
    std::printf("RENA0_BODY: PASS (%d checks, skips=0)\n", checks);
    return 0;
}
