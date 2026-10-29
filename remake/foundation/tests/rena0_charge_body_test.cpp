// P2-7 (2e) charge family — offline checks for the recovered charge-gauge bodies.
//
// The gauge bodies are small integer rules, so the cases pin the parts that are easy to get
// wrong and expensive to notice: the mode and blocked gates, the three divisors (90 attacker,
// 133 victim mode 0, 225 victim mode 2), the limit clamp, the notify ids (6 attacker, 5 victim
// mode 0) and the wraparound integer semantics the bundle preserves.
//
// Data-free by construction: scalars in, effects out, no install and no Match.
#include "gameplay/native/rena0_charge_observation.h"

#include <cstdio>
#include <stdexcept>
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
    std::puts("P2-7 charge family — recovered charge-gauge bodies, offline checks");

    std::puts("\n== attacker, mode 1 ==");
    {
        native::Rena0AttackCharge s;
        const auto fx = native::advance_rena0_attack_charge(s, 90, 100, 0);
        checkEq(100, s.charge, "base*scale/90 adds exactly the scaled amount");
        check(fx.notified.empty(), "no notification below the limit");
        checkEq(0, s.ready, "ready stays clear below the limit");
    }
    {
        native::Rena0AttackCharge s;
        s.limit = 50;
        const auto fx = native::advance_rena0_attack_charge(s, 90, 100, 3);
        checkEq(50, s.charge, "reaching the limit clamps the gauge");
        checkEq(1, s.ready, "reaching the limit latches ready");
        checkEq(1, (long long)fx.notified.size(), "reaching the limit notifies once");
        checkEq(6, fx.notified.empty() ? -1 : fx.notified[0], "the attacker notification id is 6");
    }
    {
        native::Rena0AttackCharge s;
        s.mode = 0;
        const auto fx = native::advance_rena0_attack_charge(s, 900, 100, 0);
        checkEq(0, s.charge, "mode 0 is not the attacker's mode");
        check(fx.notified.empty(), "a wrong mode notifies nothing");
    }
    {
        native::Rena0AttackCharge s;
        s.blocked = 1;
        native::advance_rena0_attack_charge(s, 900, 100, 0);
        checkEq(0, s.charge, "a blocked attacker accumulates nothing");
    }
    {
        native::Rena0AttackCharge s;
        s.charge = 1000;
        s.limit = 1000;
        native::advance_rena0_attack_charge(s, 900, 100, 0);
        checkEq(1000, s.charge, "a full gauge stays clamped");
    }

    std::puts("\n== victim, modes 0 and 2 ==");
    {
        native::Rena0HitCharge s;
        native::advance_rena0_hit_charge(s, 133, 100, 100, 100, 0);
        checkEq(100, s.charge0, "mode 0 divides by 133");
        checkEq(0, s.charge2, "mode 0 leaves the mode-2 gauge alone");
    }
    {
        native::Rena0HitCharge s;
        s.mode = 2;
        native::advance_rena0_hit_charge(s, 225, 100, 100, 100, 0);
        checkEq(100, s.charge2, "mode 2 divides by 225");
        checkEq(0, s.charge0, "mode 2 leaves the mode-0 gauge alone");
    }
    {
        native::Rena0HitCharge s;
        native::advance_rena0_hit_charge(s, 133, 100, 50, 100, 0);
        checkEq(50, s.charge0, "the defense factor scales the gain");
    }
    {
        native::Rena0HitCharge s;
        native::advance_rena0_hit_charge(s, 133, 100, 100, 50, 0);
        checkEq(50, s.charge0, "the modifier factor scales the gain");
    }
    {
        native::Rena0HitCharge s;
        s.mode = 3;
        native::advance_rena0_hit_charge(s, 9000, 100, 100, 100, 0);
        checkEq(0, s.charge0 + s.charge2, "an unknown mode accumulates nothing");
    }
    {
        native::Rena0HitCharge s;
        s.blocked0 = 1;
        native::advance_rena0_hit_charge(s, 9000, 100, 100, 100, 0);
        checkEq(0, s.charge0, "mode 0's blocked flag stops its accumulation");
        s.blocked0 = 0;
        s.blocked2 = 1;
        s.mode = 2;
        native::advance_rena0_hit_charge(s, 9000, 100, 100, 100, 0);
        checkEq(0, s.charge2, "mode 2's blocked flag stops its accumulation");
    }
    {
        native::Rena0HitCharge s;
        s.limit = 40;
        const auto fx = native::advance_rena0_hit_charge(s, 133, 100, 100, 100, 7);
        checkEq(40, s.charge0, "mode 0 clamps at its limit");
        checkEq(1, (long long)fx.notified.size(), "mode 0 notifies on arrival");
        checkEq(5, fx.notified.empty() ? -1 : fx.notified[0], "the victim notification id is 5");
    }
    {
        native::Rena0HitCharge s;
        s.mode = 2;
        s.limit = 40;
        const auto fx = native::advance_rena0_hit_charge(s, 225, 100, 100, 100, 7);
        checkEq(40, s.charge2, "mode 2 clamps at its limit");
        check(fx.notified.empty(), "mode 2 notifies nothing on arrival (only mode 0 does)");
    }
    {
        native::Rena0HitCharge s;
        s.charge0 = 1000;
        native::advance_rena0_hit_charge(s, 9000, 100, 100, 100, 0);
        checkEq(1000, s.charge0, "a full victim gauge stays clamped");
    }

    std::puts("\n== the preserved integer semantics ==");
    {
        checkEq(-2, native::charge_multiply(-1, 2), "the multiply keeps its signed result");
        bool threw = false;
        try {
            native::charge_divide(5, 0);
        } catch (const std::domain_error&) {
            threw = true;
        }
        check(threw, "dividing by zero faults rather than returning a value");
        threw = false;
        try {
            native::charge_divide(std::numeric_limits<std::int32_t>::min(), -1);
        } catch (const std::domain_error&) {
            threw = true;
        }
        check(threw, "the original's INT_MIN / -1 fault is preserved");
    }

    if (failures) {
        std::fprintf(stderr, "RENA0_CHARGE_BODY: FAIL (%d of %d checks)\n", failures, checks);
        return 1;
    }
    std::printf("RENA0_CHARGE_BODY: PASS (%d checks, skips=0)\n", checks);
    return 0;
}
