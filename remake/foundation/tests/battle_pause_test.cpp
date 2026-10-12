// Issue #15's pause semantics, device-free: the match must not advance while paused, a
// held button must not survive the pause as a stale edge, and the menu must resolve to the
// four documented choices. No SDL, no window, no assets.
#include "gameplay/battle_pause.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "input/tick_input.h"

#include <cstdio>
#include <string>
#include "synthetic_combo.h"

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

// A two-fighter match with no models: the same shape fixed_step_test drives, which is
// enough for timers, states and the pause gate (nothing here needs a mesh).
struct Fixture {
    gameplay::Match match;
    test::synthetic::Combo m_combo;
    fnd::input::PlayerState input;

    Fixture() {
        gameplay::MatchConfig config;
        config.fighterCount = 2;
        config.spawn[1] = glm::vec3(500, 0, 0);
        // AGENTS rule 7: this fixture steps a live battle, so it binds a character AND a
        // weapon. Synthetic, so the suite still runs without game data (audit finding H).
        m_combo.bind(config, 2);
        const xm::Model* models[4] = {};
        xm::Controller* animations[4] = {};
        match.reset(config, models, animations, nullptr, nullptr);
        match.economy().setLogFile(nullptr);
    }

    // One authoritative tick with P1's current input (P2 stays a dummy, as in the
    // standalone path).
    gameplay::MatchFrame tick() {
        fnd::input::compute_edges(input);
        const fnd::input::PlayerState* inputs[4] = {&input, nullptr, nullptr, nullptr};
        return match.step(inputs, gameplay::FixedStep::seconds);
    }

    void clearInput() {
        for (bool& down : input.down) down = false;
        fnd::input::compute_edges(input);
    }
};

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

    std::printf("\n-- a paused match does not advance: no timer, no economy, no respawn clock\n");
    {
        Fixture f;
        // Run a live second so there is real state to freeze, then KO fighter 1 and let the
        // respawn clock start.
        for (int i = 0; i < 64; ++i) f.tick();
        f.match.fighter(1).take_damage(f.match.fighter(1).max_hp(), &f.match.fighter(0));
        f.tick();
        check(f.match.economy().koAt(1) >= 0.0, "fighter 1 is down with a running KO clock");
        const double elapsed = f.match.economy().elapsed();
        const double timeLeft = f.match.economy().timeLeft();
        const float balloon = f.match.economy().balloon(0);
        const int hp0 = f.match.fighter(0).hp();
        const int hp1 = f.match.fighter(1).hp();
        const float stamina = f.match.fighter(0).stamina();
        const glm::vec3 position = f.match.fighter(0).position();
        const gameplay::FighterState state = f.match.fighter(0).state();
        const double koAt = f.match.economy().koAt(1);
        const int shots = f.match.shots().live_shots();

        f.match.set_paused(true);
        // A held attack plus a direction: nothing may move, and the 3 s KO clock must not
        // run, so the fighter cannot respawn while paused however long the pause lasts.
        f.input.down[fnd::input::AttackA] = true;
        f.input.down[fnd::input::Right] = true;
        for (int i = 0; i < 600; ++i) {
            const gameplay::MatchFrame frame = f.tick();
            checkInt("a paused step reports an empty frame", 0, frame.shotsSpawned);
            check(!frame.roundOver && !frame.respawned[0] && !frame.respawned[1],
                  "a paused step reports no respawn and no round end");
        }
        checkFloat("economy elapsed is frozen", elapsed, f.match.economy().elapsed());
        checkFloat("the round countdown is frozen", timeLeft, f.match.economy().timeLeft());
        checkFloat("the balloon is frozen", balloon, f.match.economy().balloon(0));
        checkFloat("the KO clock is frozen", koAt, f.match.economy().koAt(1));
        checkInt("no respawn was credited while paused", 0, f.match.economy().respawns(1));
        checkInt("hp is frozen", hp0, f.match.fighter(0).hp());
        checkInt("the downed fighter's hp is frozen", hp1, f.match.fighter(1).hp());
        checkFloat("stamina is frozen", stamina, f.match.fighter(0).stamina());
        check(f.match.fighter(0).position() == position, "position is frozen");
        check(f.match.fighter(0).state() == state, "the state machine is frozen");
        checkInt("no shot was fired while paused", shots, f.match.shots().live_shots());
        check(f.match.fighter(0).state() != gameplay::FighterState::AttackA,
              "a held attack did not start while paused");

        // Resume: the same input is still held, and because the edge was consumed during
        // the pause it must not fire now either. The tick after that (a fresh press) must.
        f.match.set_paused(false);
        f.tick();
        check(f.match.fighter(0).state() != gameplay::FighterState::AttackA,
              "a held melee button does not fire on resume");
        const double elapsedAfter = f.match.economy().elapsed();
        check(elapsedAfter > elapsed, "the economy advances again after resume");
        checkFloat("by exactly one tick", elapsed + gameplay::FixedStep::seconds, elapsedAfter);
        f.clearInput();
        f.tick();
        f.input.down[fnd::input::AttackA] = true;
        f.tick();
        check(f.match.fighter(0).state() == gameplay::FighterState::AttackA,
              "a fresh press after resume does start an attack");
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
