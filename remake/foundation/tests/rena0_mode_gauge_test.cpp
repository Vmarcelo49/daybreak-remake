// P2-7 (2e) charge family — the mode-gauge state against the real actor parameters.
//
// Two things are checked here that nothing else can: that the per-character limits the
// recovered rules clamp at are the values the shipped actor DAT actually carries (read through
// the parser's own `header_values()`), and that the accumulated state behaves as the adapted
// bodies describe when fed a sequence of hits — including the clamps and the two notification
// ids the port has no accumulator for yet.
//
// Install-backed: the limits come from `data/rena/00.dat`, so a data-free run exits 77 and is
// reported Skipped, never a pass.
#include "combo_fixture.h"
#include "gameplay/native/rena0_mode_gauges.h"

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
    if (test::gameInstall().empty()) {
        std::puts("SKIP: no game install reachable; the mode-gauge limits are actor data (not a pass)");
        return 77;
    }
    try {
        test::Combo combo;
        std::string error;
        if (!combo.load(0, 0, error)) throw std::runtime_error("Rena+0 data unavailable: " + error);
        const native::Rena0ModeGaugeLimits limits =
            native::rena0_mode_gauge_limits(combo.moves.header_values());
        std::puts("P2-7 charge family — mode-gauge state against the shipped actor parameters");

        std::puts("\n== the shipped limits (data/<char>/NN.dat, header dwords 0/1/4/5) ==");
        checkEq(850, limits.limit0, "Rena+0's victim-side limit is the shipped 850");
        checkEq(900, limits.duration0, "Rena+0's mode-0 duration is the shipped 900");
        checkEq(850, limits.limit1, "Rena+0's attacker-side limit is the shipped 850");
        checkEq(900, limits.duration1, "Rena+0's mode-1 duration is the shipped 900");
        checkEq(1, combo.moves.header_values()[3], "the same block still carries the weapon id the parser uses");

        std::puts("\n== accumulation into the state, mode 0 (Oyashiro: victim side) ==");
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 0;
            g.on_hit(133, 90, 100, 100, 100);
            checkEq(100, g.charge0, "a victim hit adds base*scale/133");
            checkEq(0, g.charge1, "mode 0 leaves the attacker gauge alone (the modes are exclusive)");
            checkEq(0, g.notify5 + g.notify6, "nothing notifies below the limits");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 0;
            for (int i = 0; i < 20; ++i) g.on_hit(133, 0, 100, 100, 100);
            checkEq(850, g.charge0, "the victim gauge clamps at the shipped 850");
            checkEq(1, g.notify5, "reaching the limit notifies id 5 exactly once");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 1;  // Friendship: the attacker path is mode 1
            for (int i = 0; i < 20; ++i) g.on_hit(0, 90, 100, 100, 100);
            checkEq(850, g.charge1, "the attacker gauge clamps at the shipped 850");
            checkEq(1, g.notify6, "reaching the limit notifies id 6 exactly once");
            checkEq(0, g.charge0, "mode 1 leaves the victim gauge alone");
        }

        std::puts("\n== the mode gates reach the state ==");
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 2;  // Kakera: the victim path is mode 2, so charge0 must not move
            g.on_hit(225, 0, 100, 100, 100);
            checkEq(0, g.charge0, "mode 2 does not accumulate the mode-0 gauge");
            checkEq(100, g.charge2, "mode 2 accumulates its own gauge at /225");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 1;  // Friendship: the attacker path
            g.on_hit(0, 90, 100, 100, 100);
            checkEq(100, g.charge1, "mode 1 accumulates the attacker gauge");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 0;
            g.active0 = true;  // the special is running: the victim gauge is blocked
            g.on_hit(133, 0, 100, 100, 100);
            checkEq(0, g.charge0, "an active mode 0 blocks further victim accumulation");
        }

        std::puts("\n== activation, chords and the refill step ==");
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 0;
            g.begin0();
            checkEq(900, g.charge0, "begin0 fills the gauge from the shipped duration0");
            check(g.active0, "begin0 marks mode 0 active");
            checkEq(1, g.refill_step(), "an active mode 0 refills at step 1");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 2;
            std::uint32_t health = 40;
            g.begin2(health);
            checkEq(10000, health, "begin2 restores health to the original's 10000");
            checkEq(900, g.charge2, "begin2 fills its gauge from duration0");
            checkEq(2, g.refill_step(), "an active mode 2 refills at step 2");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 0;
            g.charge0 = limits.limit0;
            check(g.accepts_mode0_chord(50, 1, 2), "mode 0 accepts its chord at the limit");
            check(!g.accepts_mode0_chord(50, 0, 2), "the chord needs both buttons");
            check(!g.accepts_mode0_chord(120, 1, 2), "the chord refuses a blocked action window");
            g.charge0 = limits.limit0 - 1;
            check(!g.accepts_mode0_chord(50, 1, 2), "the chord needs the gauge at its limit");
            g.charge0 = limits.limit0;
            g.mode = 1;
            g.charge1 = limits.limit1;
            check(g.accepts_mode1_chord(50, 1, 2), "mode 1 accepts its chord in its action window");
            check(!g.accepts_mode1_chord(200, 1, 2), "mode 1 refuses an action inside 100..299");
        }

        std::puts("\n== the consumption tick ==");
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 0;
            g.begin0();
            std::uint32_t health = 10000;
            int movement = 0;
            for (int i = 0; i < 5; ++i) g.tick(health, movement);
            checkEq(895, g.charge0, "mode 0 spends one per tick");
            checkEq(10000, health, "mode 0 does not touch health");
            for (int i = 0; i < 895; ++i) g.tick(health, movement);
            checkEq(0, g.charge0, "mode 0 spends down to zero");
            check(!g.active0, "mode 0 ends when its gauge reaches zero");
            checkEq(0, movement, "mode 0 does not move the movement gauge");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 1;
            g.begin1();
            std::uint32_t health = 10000;
            int movement = 0;
            g.tick(health, movement);
            checkEq(899, g.charge1, "mode 1 spends one per tick from duration1");
            checkEq(10000, health, "mode 1 does not touch health");
        }
        {
            native::Rena0ModeGauges g;
            g.limits = limits;
            g.mode = 2;
            std::uint32_t health = 10000;
            g.begin2(health);
            int movement = 0;
            g.tick(health, movement);
            checkEq(9993, health, "mode 2 drains health by 7 a tick");
            checkEq(1, movement, "mode 2 advances the movement gauge");
            health = 10;
            g.tick(health, movement);
            checkEq(3, health, "mode 2 keeps draining above the boundary");
            g.tick(health, movement);
            checkEq(1, health, "crossing below 9 sets health to 1");
            check(!g.active2, "mode 2 ends itself at the boundary");
            checkEq(0, g.charge2, "the ending clears its gauge");
            movement = 1000;
            g.active2 = true;
            g.tick(health, movement);
            checkEq(1000, movement, "the movement gauge clamps at 1000");
            health = 0;
            g.active2 = true;
            g.tick(health, movement);
            check(!g.active2, "health below 1 also ends mode 2");
        }

        if (failures) {
            std::fprintf(stderr, "RENA0_MODE_GAUGE: FAIL (%d of %d checks)\n", failures, checks);
            return 1;
        }
        std::printf("RENA0_MODE_GAUGE: PASS (%d checks, skips=0)\n", checks);
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
