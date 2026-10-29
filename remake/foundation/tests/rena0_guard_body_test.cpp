// P2-7 (2e) guard family — offline checks for the recovered guard body.
//
// The body is small but stateful, and its content is the transition logic: which condition
// moves 390 into 391, when phase 2 is proposed, when the hold counter releases, and what the
// attacker's recoil (392) does to speed. These cases pin all of it from scalars alone (no
// install, no Match), so a change in the adapted body is caught before anything is wired.
//
// Expectations come from the bundle's `battle_guard_motion.hpp` (the original's 438310); the
// body's own `gauge` is its own number and is never presented as the port's stamina.
#include "gameplay/native/rena0_guard_observation.h"

#include <cstdio>
#include <string>

namespace {
namespace native = gameplay::native;

int checks = 0, failures = 0;

void check(bool ok, const std::string& name) {
    ++checks;
    if (!ok) ++failures;
    std::printf("  %-72s %s\n", name.c_str(), ok ? "ok" : "FAIL");
}

void checkEq(long long expected, long long got, const std::string& name) {
    ++checks;
    const bool ok = expected == got;
    if (!ok) ++failures;
    std::printf("  %-72s %s", name.c_str(), ok ? "ok" : "FAIL");
    if (!ok) std::printf(" (expected %lld, got %lld)", expected, got);
    std::printf("\n");
}
}  // namespace

int main() {
    std::puts("P2-7 guard family — recovered guard body (states 390/391/392), offline checks");

    std::puts("\n== 390: preparation, hold and release ==");
    {
        native::Rena0GuardMotion p;
        p.offset = 100.f;
        const auto step = native::advance_rena0_guard(p);
        checkEq(0, (long long)p.speed, "the first frame zeroes the speed");
        checkEq(0, (long long)p.contact_flags, "the first frame clears the contact flags");
        check(step.clear_contacts, "the first frame asks for the contacts to be cleared");
        checkEq(80, (long long)p.offset, "phase 0 approaches the offset by 20 per frame");
        checkEq(-1, step.state, "a held guard proposes no state change");
        checkEq(1000, p.gauge, "phase 0 does not drain the gauge");
    }
    {
        native::Rena0GuardMotion p;
        p.phase = 1;
        p.button_a = true;
        p.button_b = true;
        const auto step = native::advance_rena0_guard(p);
        checkEq(990, p.gauge, "phase 1 drains the guard gauge by 10 per frame");
        checkEq(-1, step.phase, "a live guard proposes no phase change");
    }
    {
        native::Rena0GuardMotion p;
        p.phase = 1;
        p.button_a = true;
        p.button_b = false;
        const auto step = native::advance_rena0_guard(p);
        checkEq(2, step.phase, "releasing either guard button proposes phase 2");
    }
    {
        native::Rena0GuardMotion p;
        p.phase = 1;
        p.button_a = true;
        p.button_b = true;
        p.gauge = 0;
        const auto step = native::advance_rena0_guard(p);
        checkEq(2, step.phase, "an empty gauge proposes phase 2 even while held");
    }
    {
        native::Rena0GuardMotion p;
        p.phase = 1;
        p.button_a = true;
        p.button_b = true;
        p.contact_flags = 2;
        const auto step = native::advance_rena0_guard(p);
        checkEq(391, step.state, "a guarding contact with gauge left becomes the successful guard");
        check(step.clear_contacts, "the 391 transition also clears the contacts");
    }
    {
        native::Rena0GuardMotion p;
        p.phase = 1;
        p.button_a = true;
        p.button_b = true;
        p.gauge = 0;
        p.contact_flags = 2;
        const auto step = native::advance_rena0_guard(p);
        checkEq(-1, step.state, "an empty gauge cannot become the successful guard");
    }
    {
        native::Rena0GuardMotion p;
        p.phase = 2;
        p.speed = 3.f;
        native::advance_rena0_guard(p);
        checkEq(20, (long long)(p.speed * 10.f), "phase 2 decays the speed by 1 per frame");
    }

    std::puts("\n== 391 / 392: the guard and the attacker's recoil ==");
    {
        native::Rena0GuardMotion p;
        p.state = 391;
        const auto step = native::advance_rena0_guard(p);
        // The entry sets -15 and the same frame's ramp adds 1 (phase 0 < 3), so the observable
        // value after one frame is -14.
        checkEq(-14, (long long)p.speed, "the successful guard enters at -15 and ramps to -14 that frame");
        // The reset and the first increment happen in the same call, so the observable value
        // after one frame is 1 — the counter is what releases the guard after 20 frames.
        checkEq(1, (long long)p.hold_count, "the successful guard resets then counts its first hold frame");
        checkEq(-1, step.state, "a held 391 proposes no state change");
    }
    {
        native::Rena0GuardMotion p;
        p.state = 391;
        p.phase = 1;
        p.contact_flags = 2;
        const auto step = native::advance_rena0_guard(p);
        checkEq(391, step.state, "a second contact inside 391 holds the guard");
    }
    {
        // Past frame 0, so the entry reset does not clear the counter first: 20 + 1 > 20.
        native::Rena0GuardMotion p;
        p.state = 391;
        p.frame = 5;
        p.hold_count = 20;
        const auto step = native::advance_rena0_guard(p);
        checkEq(1, step.phase, "a hold longer than 20 frames proposes phase 1");
    }
    {
        native::Rena0GuardMotion p;
        p.state = 391;
        p.hold_count = 20;
        const auto step = native::advance_rena0_guard(p);
        checkEq(-1, step.phase, "the frame-0 entry reset clears the hold counter before it counts");
    }
    {
        native::Rena0GuardMotion p;
        p.state = 392;
        p.phase = 0;
        p.speed = -15.f;
        native::advance_rena0_guard(p);
        checkEq(-140, (long long)(p.speed * 10.f), "the recoil ramps its speed by 1 per frame");
    }
    {
        native::Rena0GuardMotion p;
        p.state = 391;
        p.phase = 3;
        p.speed = -15.f;
        native::advance_rena0_guard(p);
        checkEq(-150, (long long)(p.speed * 10.f), "391 stops ramping once its phases are spent");
    }

    std::puts("\n== completion and losing the ground ==");
    {
        native::Rena0GuardMotion p;
        p.complete = true;
        const auto step = native::advance_rena0_guard(p);
        checkEq(0, step.state, "a completed guard proposes state 0");
    }
    {
        native::Rena0GuardMotion p;
        p.complete = true;
        p.grounded = false;
        const auto step = native::advance_rena0_guard(p);
        checkEq(43, step.state, "a completed guard in the air proposes state 43");
        checkEq(5, (long long)(p.gravity * 10.f), "losing the ground sets gravity 0.5");
    }
    {
        native::Rena0GuardMotion p;
        p.state = 391;
        p.grounded = false;
        const auto step = native::advance_rena0_guard(p);
        checkEq(103, step.state, "an airborne successful guard proposes 103, not 43");
    }

    if (failures) {
        std::fprintf(stderr, "RENA0_GUARD_BODY: FAIL (%d of %d checks)\n", failures, checks);
        return 1;
    }
    std::printf("RENA0_GUARD_BODY: PASS (%d checks, skips=0)\n", checks);
    return 0;
}
