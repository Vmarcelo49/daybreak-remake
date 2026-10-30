// Issue #15's pause semantics, device-free: a held button must not survive the pause as a
// stale edge, and the menu must resolve to the four documented choices. No SDL, no window,
// no assets. pause_overlay_panel pins that a paused battle stays frozen.
#include "battle/battle_pause.h"
#include "battle/fixed_step.h"
#include "input/tick_input.h"

#include <cstdio>
#include <string>

namespace {

int g_checks = 0;
int g_failures = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("  FAIL %s\n", what.c_str());
    }
}

void checkInt(const std::string& what, long long expected, long long actual) {
    ++g_checks;
    if (expected != actual) {
        ++g_failures;
        std::printf("  FAIL %s: expected %lld, got %lld\n", what.c_str(), expected, actual);
    }
}

void checkFloat(const std::string& what, double expected, double actual) {
    ++g_checks;
    const double diff = expected - actual;
    if (diff > 1e-9 || diff < -1e-9) {
        ++g_failures;
        std::printf("  FAIL %s: expected %.6f, got %.6f\n", what.c_str(), expected, actual);
    }
}

}  // namespace

int main() {
    std::printf("\n-- the menu: four rows, cancel resumes, confirm takes the row\n");
    {
        gameplay::PauseMenu menu;
        checkInt("the default row is Resume", 0, menu.row);
        checkInt("four rows in a front-end battle", 4,
                 gameplay::kPauseRowsWithSelection);
        checkInt("Resume on a stray confirm",
                 (int)gameplay::PauseChoice::Resume,
                 (int)menu.update(false, false, true, false));
        menu.reset();
        checkInt("down moves to Rematch", (int)gameplay::PauseChoice::None,
                 (int)menu.update(false, true, false, false));
        checkInt("row 1", 1, menu.row);
        checkInt("confirm takes Rematch", (int)gameplay::PauseChoice::Rematch,
                 (int)menu.update(false, false, true, false));
        menu.update(false, true, false, false);
        checkInt("confirm takes Return to selection", (int)gameplay::PauseChoice::ReturnToSelection,
                 (int)menu.update(false, false, true, false));
        menu.update(false, true, false, false);
        checkInt("confirm takes Quit", (int)gameplay::PauseChoice::Quit,
                 (int)menu.update(false, false, true, false));
        menu.update(false, true, false, false);
        checkInt("down wraps to Resume", 0, menu.row);
        menu.update(true, false, false, false);
        checkInt("up wraps to the last row", 3, menu.row);
        checkInt("cancel is Resume whatever the row is", (int)gameplay::PauseChoice::Resume,
                 (int)menu.update(false, false, false, true));
        // The labels the overlay prints; row 0 must be the one a stray confirm takes.
        check(std::string(gameplay::pauseRowLabel(0, 4)) == "Resume", "row 0 label");
        check(std::string(gameplay::pauseRowLabel(1, 4)) == "Rematch", "row 1 label");
        check(std::string(gameplay::pauseRowLabel(2, 4)) == "Return to selection", "row 2 label");
        check(std::string(gameplay::pauseRowLabel(3, 4)) == "Quit to desktop", "row 3 label");
        check(std::string(gameplay::pauseRowLabel(99, 4)) == "Resume",
              "an out-of-range row is Resume");
        // The standalone harness has no selection screen: three rows, last row quits.
        gameplay::PauseMenu standalone;
        standalone.rows = gameplay::kPauseRowsStandalone;
        checkInt("three rows without a selection screen", 3, standalone.rows);
        standalone.update(false, true, false, false);
        checkInt("row 1 is still Rematch", (int)gameplay::PauseChoice::Rematch,
                 (int)standalone.update(false, false, true, false));
        standalone.update(false, true, false, false);
        checkInt("the last row quits, there is no return row", (int)gameplay::PauseChoice::Quit,
                 (int)standalone.update(false, false, true, false));
        standalone.update(false, true, false, false);
        checkInt("and it wraps", 0, standalone.row);
        check(std::string(gameplay::pauseRowLabel(2, 3)) == "Quit to desktop",
              "row 2 of three is quit");
        check(std::string(gameplay::pauseRowLabel(2, 4)) == "Return to selection",
              "row 2 of four is the return row");
    }

    std::printf("\n-- TickInput: draining while paused is what kills the stale edge\n");
    {
        fnd::input::TickInput queue;
        fnd::input::PlayerState held;
        held.down[fnd::input::AttackA] = true;
        fnd::input::compute_edges(held);
        queue.sample(held);
        check(queue.consume().just_pressed[fnd::input::AttackA], "the press edge fires once");
        // The pause drains the queue exactly like the host's paused ticks do.
        for (int frame = 0; frame < 30; ++frame) {
            queue.sample(held);
            const fnd::input::PlayerState drained = queue.consume();
            check(!drained.just_pressed[fnd::input::AttackA],
                  "a held button produces no edge while paused");
        }
        const fnd::input::PlayerState resumed = queue.consume();
        check(!resumed.just_pressed[fnd::input::AttackA], "and none on resume");
        check(resumed.down[fnd::input::AttackA], "the button still reads as held");
        // Releasing and pressing again is a new edge.
        fnd::input::PlayerState released;
        fnd::input::compute_edges(released);
        queue.sample(released);
        queue.consume();
        queue.sample(held);
        check(queue.consume().just_pressed[fnd::input::AttackA], "a fresh press is a fresh edge");
    }

    std::printf("\n-- paused wall time never becomes catch-up ticks\n");
    {
        // The host's rule: while paused it does not call advance() at all, so the clock
        // never sees the paused span. Prove the shape with the clock itself: feeding the
        // paused span is what WOULD replay it, and not feeding it is what the host does.
        gameplay::FixedStep clock;
        clock.advance(gameplay::FixedStep::seconds);   // one tick consumed, remainder 0
        const int replayed = clock.advance(300.0);     // a five-minute stall, if it were fed
        checkInt("a fed stall would replay its ticks (bounded by maxCatchUp)",
                 gameplay::FixedStep::maxCatchUp, replayed);
        gameplay::FixedStep pausedClock;
        pausedClock.advance(gameplay::FixedStep::seconds);
        checkInt("not feeding the pause yields no ticks at all", 0, pausedClock.advance(0.0));
        checkFloat("and the phase stays where the pause began", 0.0, pausedClock.alpha());
    }

    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failures);
    if (g_failures == 0) std::printf("BATTLE_PAUSE: ok\n");
    return g_failures == 0 ? 0 : 1;
}
