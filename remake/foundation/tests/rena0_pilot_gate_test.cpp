// Rena+0 pilot regression: equipped-combo attachment safety, the unified meter's dash
// gate, and the recovered empty-tap voice through production Match/Fighter.
//
// Case A — the unified meter gates the dash on the pilot path. With a full meter both
// flag settings enter row 20/set 13; the pilot drains the unified word (meter -12) while
// flag-off drains the legacy stamina. With the meter empty the pilot refuses the recovered
// `0 < +0x834` gate while flag-off (legacy stamina full) still admits — the refusal the
// inert second counter could never produce.
//
// Case B — empty magazine tap. Source: the adapted body's release branch
//   (`0 < released < 20 && primary rounds == 0`) requests ONE voice (`FUN_00422560(slot,0x18,
//   10,1)` = vocabulary index 24) and the empty-shot statistic, inside the wrapper whose
//   `+0x834 < 1` term excludes the ordinary admission — so it enters NO shot row
//   (slot7_native_bodies_20260929.hpp:172-182). The flag-off port returns from can_fire before
//   any voice. The unowned statistic is deliberately not published through a Fighter field
//   (PILOT-SEAM.md §26).
//
// Case C — that same release window, which the port had no counter for: a 19-frame hold is
//   inside `released < 20` and still voices; a 20-frame hold is outside it and must be silent.
//   Both stay out of any shot row. Seeding the cap to 21 makes this fail, so the boundary is
//   load-bearing.
//
// Case D — the pilot right side-dash clock. Row 23's recovered body adds a second increment
//   when the entering phase clock (+0xae04) is divisible by 9, including zero; the common tail
//   adds one more (FUN_0043ffc0.c:288-291 and :2439-2443; bundle
//   dash_native_bodies_20260929.hpp:215-232). With the row's 7/12/24 thresholds and the strict
//   `threshold < elapsed` exit, the pilot right dash samples clock 2 on entry, binds set 23 on
//   one-based update 7, set 24 on update 18 and Idle on update 39. Both controller tracks carry
//   the primary clock (elapsed * 0.016). Left and flag-off keep the old single increment; their
//   extended timing is deliberately not asserted (PILOT-EVIDENCE-CONTRACT V3-22).
//
// The test attaches/detaches the pilot policies directly, which is the same mechanism
// --native-actions=rena0 uses in main.cpp; it does not need the CLI flag. Device-free and
// silent. Data-free checkouts exit 77 (Skipped, never a pass).
#include "combo_fixture.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "gameplay/move_behavior.h"
#include "gameplay/native/rena0_pilot_adapter.h"

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
namespace input = fnd::input;

void require(bool ok, const char* message) {
    if (!ok) throw std::runtime_error(message);
}
void require(bool ok, const std::string& message) {
    if (!ok) throw std::runtime_error(message);
}

// One tick of the production path. `inputs[0]` is the scripted P1; the opponent is fed nullptr,
// which is the product's COM-off shape rather than an all-false pad.
gameplay::MatchFrame step(gameplay::Match& match, input::PlayerState& actor) {
    input::compute_edges(actor);
    const input::PlayerState* inputs[gameplay::kMatchFighterCount] = {&actor, nullptr, nullptr, nullptr};
    return match.step(inputs, gameplay::FixedStep::seconds);
}

void startup(gameplay::Match& match, input::PlayerState& actor, test::Combo& combo, int& ticks) {
    int guard = 0;
    while ((!match.fighter(0).actionable() || !match.fighter(1).actionable()) && guard < 512) {
        step(match, actor);
        ++guard;
    }
    require(guard > 0 && guard < 512, "normal Match startup did not become actionable");
    require(match.fighter(0).moves() == &combo.moves && match.fighter(0).weapon() == &combo.weapon,
            "the production fighter did not retain the equipped Rena+0 data");
    require(!match.fighter(0).airborne() && match.fighter(0).action_state() == 0 &&
                match.fighter(0).bound_move_id() == 0,
            "startup must settle grounded idle row 0");
    ticks = guard;
}

struct PilotPolicies {
    gameplay::native::Rena0PilotShotPolicy shot;
    gameplay::native::Rena0PilotMeterPolicy meter;
    void attach(gameplay::Fighter& fighter) {
        fighter.set_pilot_shot(&shot);
        fighter.set_pilot_meter(&meter);
    }
};

struct DashRun {
    int startup = 0;
    int releaseRow = -1;   // row held on the tap's release tick
    int dashRow = -1;      // action row held on the second press
    int dashCandidate = -1; // Fighter::dash_move_id(): -1 when NO dash was admitted
    int dashSet = -1;
    int gauge = -1;
    int stamina = -1;
    int staminaAtStart = -1;
    int recoveredDrainEquivalent = -1;  // dashDrain * 10, the recovered 12/tick
};

// Up, release, Up with the charge gauge pinned to `gauge` before the input.
DashRun dashRun(test::Combo& combo, int gauge, bool pilot) {
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.spawn[0] = {0.f, 0.f, 0.f};
    config.spawn[1] = {0.f, 0.f, 2000.f};
    const xm::Model* models[gameplay::kMatchFighterCount] = {&combo.model, &combo.model};
    xm::Controller* controllers[gameplay::kMatchFighterCount] =
        {combo.controller(), combo.controller()};
    for (int i = 0; i < 2; ++i) {
        config.moves[i] = &combo.moves;
        config.weapon[i] = &combo.weapon;
    }
    match.reset(config, models, controllers, nullptr, nullptr, nullptr);
    match.set_ai_enabled(1, false);
    match.economy().setLogFile(nullptr);
    PilotPolicies policies;
    if (pilot) policies.attach(match.fighter(0));

    input::PlayerState actor{};
    DashRun run;
    startup(match, actor, combo, run.startup);
    auto& fighter = match.fighter(0);
    fighter.set_charge_gauge(gauge);
    require(fighter.charge_gauge() == gauge, "charge gauge injection failed");
    // On the pilot path the setter writes the unified word, so gauge 0 IS meter 0 and
    // the recovered gate refuses; the positive-stamina precondition only applies to
    // the full-meter runs below.
    if (gauge > 0) {
        require(fighter.stamina() > 0.f, "the dash case needs positive stamina");
        run.staminaAtStart = fighter.stamina();
    }
    // Diagnostic scale check against a port rule table, not shipped DAT or independent
    // evidence for the source field's identity. Actual coupling remains a named seam gap.
    const auto* locomotionDef = gameplay::locomotion(&combo.moves);
    require(locomotionDef != nullptr, "Rena+0 has no recovered locomotion row");
    run.recoveredDrainEquivalent =
        static_cast<int>(std::lround(locomotionDef->dashDrain * 10.0f));

    actor.down[input::Action::Up] = true;
    step(match, actor);
    actor.down[input::Action::Up] = false;
    step(match, actor);
    run.releaseRow = fighter.action_state();
    actor.down[input::Action::Up] = true;
    step(match, actor);
    run.dashRow = fighter.action_state();
    run.dashCandidate = fighter.dash_move_id();
    run.dashSet = fighter.anim_set_index();
    run.gauge = fighter.charge_gauge();
    run.stamina = static_cast<int>(fighter.stamina());
    return run;
}

struct DashClockSample {
    int phase = -1;
    int set = -1;
    int elapsed = -1;
    int state = -1;
    bool running = false;
    int gauge = -1;
    double x = 0.0;
    double track0 = -1.0;
    double track1 = -1.0;
};

struct DashClockRun {
    int startup = 0;
    std::vector<DashClockSample> ticks;  // one-based dash updates, entry first
};

// Double tap one direction and record the dash's next 39 updates. The trigger tick is
// update 1; no movement or meter value is asserted here.
DashClockRun dashClockRun(test::Combo& combo, bool pilot, input::Action direction) {
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.spawn[0] = {0.f, 0.f, 0.f};
    config.spawn[1] = {0.f, 0.f, 2000.f};
    const xm::Model* models[gameplay::kMatchFighterCount] = {&combo.model, &combo.model};
    xm::Controller* controllers[gameplay::kMatchFighterCount] =
        {combo.controller(), combo.controller()};
    for (int i = 0; i < 2; ++i) {
        config.moves[i] = &combo.moves;
        config.weapon[i] = &combo.weapon;
    }
    match.reset(config, models, controllers, nullptr, nullptr, nullptr);
    match.set_ai_enabled(1, false);
    match.economy().setLogFile(nullptr);
    PilotPolicies policies;
    if (pilot) policies.attach(match.fighter(0));

    input::PlayerState actor{};
    DashClockRun run;
    startup(match, actor, combo, run.startup);
    auto& fighter = match.fighter(0);
    fighter.set_charge_gauge(1000);
    require(fighter.charge_gauge() == 1000, "the dash clock run needs a full charge gauge");
    xm::Controller* controller = controllers[0];
    run.ticks.reserve(39);

    const auto sample = [&] {
        DashClockSample tick;
        tick.phase = fighter.move_phase();
        tick.set = fighter.anim_set_index();
        tick.elapsed = fighter.phase_elapsed();
        tick.state = fighter.action_state();
        tick.running = fighter.state() == gameplay::FighterState::Run;
        tick.gauge = fighter.charge_gauge();
        tick.x = fighter.position().x;
        tick.track0 = controller->trackPosition(0);
        tick.track1 = controller->trackPosition(1);
        run.ticks.push_back(tick);
    };

    actor.down[direction] = true;
    step(match, actor);
    actor.down[direction] = false;
    step(match, actor);
    actor.down[direction] = true;
    step(match, actor);
    const int expectedRow = direction == input::Action::Right ? 23 : 24;
    require(fighter.state() == gameplay::FighterState::Run &&
                fighter.dash_move_id() == expectedRow,
            "a side double tap must enter its recovered dash row");
    sample();
    for (int update = 1; update < 39; ++update) {
        step(match, actor);
        sample();
    }
    return run;
}

struct ExpectedClock {
    int phase;
    int set;
    int elapsed;
    bool running;
};

// One-based updates 1..39. The row's body adds a second tick whenever the entering clock
// is 0/9/18 and the common tail adds one, so the clock is increment-only. The windows are
// the engine's truncating period rule (animation_period.h): 7, 12 and 23 updates for clips
// of 7.29, 12.5 and 23.96 frames — nearest-even rounding would have made the last one 24
// and the row 40.
constexpr ExpectedClock kPilotRightClock[39] = {
    {0, 22, 2, true},  {0, 22, 3, true},  {0, 22, 4, true},  {0, 22, 5, true},
    {0, 22, 6, true},  {0, 22, 7, true},  {1, 23, 0, true},  {1, 23, 2, true},
    {1, 23, 3, true},  {1, 23, 4, true},  {1, 23, 5, true},  {1, 23, 6, true},
    {1, 23, 7, true},  {1, 23, 8, true},  {1, 23, 9, true},  {1, 23, 11, true},
    {1, 23, 12, true}, {2, 24, 0, true},  {2, 24, 2, true},  {2, 24, 3, true},
    {2, 24, 4, true},  {2, 24, 5, true},  {2, 24, 6, true},  {2, 24, 7, true},
    {2, 24, 8, true},  {2, 24, 9, true},  {2, 24, 11, true}, {2, 24, 12, true},
    {2, 24, 13, true}, {2, 24, 14, true}, {2, 24, 15, true}, {2, 24, 16, true},
    {2, 24, 17, true}, {2, 24, 18, true}, {2, 24, 20, true}, {2, 24, 21, true},
    {2, 24, 22, true}, {2, 24, 23, true}, {0, 0, 0, false},
};

void checkRightDashClock(const DashClockSample& got, const ExpectedClock& want, int update) {
    const std::string prefix = "right dash update " + std::to_string(update) + ": ";
    require(got.phase == want.phase, prefix + "phase expected " + std::to_string(want.phase) +
                                         ", got " + std::to_string(got.phase));
    require(got.set == want.set, prefix + "set expected " + std::to_string(want.set) + ", got " +
                                     std::to_string(got.set));
    require(got.elapsed == want.elapsed,
            prefix + "phase_elapsed expected " + std::to_string(want.elapsed) + ", got " +
                std::to_string(got.elapsed));
    require(got.running == want.running,
            prefix + (want.running ? "expected the dash still running" : "expected Idle"));
    // FUN_0041f580 samples elapsed * 0.016; both tracks carry that primary clock
    // because the side-dash binds take the hard-bind path, not a class blend.
    const double expectedTrack = want.elapsed * 0.016;
    require(std::abs(got.track0 - expectedTrack) < 1e-6,
            prefix + "track0 expected " + std::to_string(expectedTrack) + ", got " +
                std::to_string(got.track0));
    require(std::abs(got.track1 - expectedTrack) < 1e-6,
            prefix + "track1 expected " + std::to_string(expectedTrack) + ", got " +
                std::to_string(got.track1));
}

struct EmptyTapRun {
    int holdTicks = 0;         // frames the empty press was held before release
    int startup = 0;
    int fundedTaps = 0;
    int fundedVoice = -1;      // the first funded tap's voice id
    int pitchedTicks = 0;      // ticks from the last funded release to ammo 0
    int emptyVoice = -1;       // MatchFrame::shotVoice[0] on the empty tap's release
    int emptyRow = -1;         // action_state on that tick
    int emptyShotRequest = -1; // shot_move_id on that tick
    int emptyAmmo = -1;
    int emptySpawns = 0;
};

// Spend the primary magazine with funded taps, then take a seventh, empty one held for
// `holdTicks` frames: the recovered release branch's `0 < released < 20` window is only
// observable by varying that number.
EmptyTapRun emptyTapRun(test::Combo& combo, bool pilot, int gauge, int holdTicks) {
    gameplay::Match match;
    gameplay::MatchConfig config;
    config.spawn[0] = {0.f, 0.f, 0.f};
    config.spawn[1] = {0.f, 0.f, 2000.f};
    const xm::Model* models[gameplay::kMatchFighterCount] = {&combo.model, &combo.model};
    xm::Controller* controllers[gameplay::kMatchFighterCount] =
        {combo.controller(), combo.controller()};
    for (int i = 0; i < 2; ++i) {
        config.moves[i] = &combo.moves;
        config.weapon[i] = &combo.weapon;
    }
    match.reset(config, models, controllers, nullptr, nullptr, nullptr);
    match.set_ai_enabled(1, false);
    match.economy().setLogFile(nullptr);
    PilotPolicies policies;
    if (pilot) policies.attach(match.fighter(0));

    input::PlayerState actor{};
    EmptyTapRun run;
    startup(match, actor, combo, run.startup);
    auto& fighter = match.fighter(0);
    fighter.set_charge_gauge(gauge);
    require(fighter.main_whole() == 6, "expected the equipped item 001 six-round primary");
    require(fighter.charge_gauge() > 0, "the funded taps need a positive charge gauge");

    // `holdTicks` frames down, then the release frame that services the press. The source's
    // release count is the number of held frames (battle_human_input.hpp:31-37).
    const auto tap = [&](int frames, gameplay::MatchFrame& releaseFrame) {
        actor.down[input::Action::Shoot] = true;
        for (int i = 0; i < frames; ++i) step(match, actor);
        actor.down[input::Action::Shoot] = false;
        releaseFrame = step(match, actor);
    };

    // Funded taps until the primary is empty; each one waits for its own recovery, so the
    // measured spend is the shot program's, not this test's timing.
    for (int shot = 1; shot <= 6 && fighter.main_whole() > 0; ++shot) {
        gameplay::MatchFrame release{};
        const int before = fighter.main_whole();
        tap(1, release);
        if (run.fundedVoice < 0) run.fundedVoice = release.shotVoice[0];
        int waited = 0;
        while (fighter.main_whole() == before && waited < 240) {
            actor.down[input::Action::Shoot] = false;
            step(match, actor);
            ++waited;
        }
        require(fighter.main_whole() == before - 1, "a funded tap did not spend exactly one round");
        run.fundedTaps = shot;
        run.pitchedTicks = waited;
        int settle = 0;
        while (!fighter.actionable() && settle < 240) {
            actor.down[input::Action::Shoot] = false;
            step(match, actor);
            ++settle;
        }
        require(settle < 240, "the shot state never returned to actionable");
    }
    require(fighter.main_whole() == 0, "six funded taps must exhaust the primary magazine");

    gameplay::MatchFrame release{};
    run.holdTicks = holdTicks;
    tap(holdTicks, release);
    run.emptyVoice = release.shotVoice[0];
    run.emptySpawns = release.shotsSpawned;
    run.emptyRow = fighter.action_state();
    run.emptyShotRequest = fighter.shot_move_id();
    run.emptyAmmo = fighter.main_whole();
    return run;
}
}  // namespace

int main(int argc, char** argv) {
    try {
        // Deliberately wrong expectation for this case's own gate: a seeded run asserts that the
        // CHARGE GAUGE blocked the dash, which the code does not do (it gates on stamina). The
        // seeded run must therefore fail — proof the assertion tests the resource the code
        // consults rather than re-observing whatever the port happens to do.
        const bool seededWrongGate = argc > 1 && std::string(argv[1]) == "--seed-wrong-gate";
        if (test::gameInstall().empty()) {
            std::puts("SKIP: no game install reachable; real equipped Rena+0 data unavailable");
            return 77;
        }
        test::Combo combo;
        std::string error;
        require(combo.load(0, 0, error), "Rena+0 install load failed: " + error);
        require(combo.moves.character_index() == 0 && combo.weapon.id == 1,
                "wrong combo identity for the pilot gate case");
        // No other combo needs loading to verify attachment safety: remove one half of the
        // equipped Rena+0 identity at a time and require the flag's predicate to reject it.
        gameplay::Fighter identityProbe;
        require(!gameplay::native::is_rena0_pilot_combo(identityProbe),
                "an unbound fighter must not enter the pilot");
        identityProbe.set_moves(&combo.moves);
        require(!gameplay::native::is_rena0_pilot_combo(identityProbe),
                "the actor table alone must not enter the pilot");
        identityProbe.set_weapon(&combo.weapon);
        require(gameplay::native::is_rena0_pilot_combo(identityProbe),
                "the real equipped Rena+0 must enter the pilot");
        gameplay::CharacterMoves wrongCharacter;
        wrongCharacter.set_character_index(1);
        identityProbe.set_moves(&wrongCharacter);
        require(!gameplay::native::is_rena0_pilot_combo(identityProbe),
                "another character must not inherit Rena+0 policies");
        identityProbe.set_moves(&combo.moves);
        gameplay::WeaponDefinition invalidWeapon;
        invalidWeapon.id = 1;
        identityProbe.set_weapon(&invalidWeapon);
        require(!gameplay::native::is_rena0_pilot_combo(identityProbe),
                "an item id without loaded item data must not enter the pilot");

        // Case A — the unified meter gates the dash on the pilot path. With a full meter
        // both flag settings enter row 20/set 13; the pilot drains the unified word while
        // flag-off drains the legacy stamina.
        const DashRun legacyFull = dashRun(combo, 1000, false);
        const DashRun pilotFull = dashRun(combo, 1000, true);
        require(legacyFull.recoveredDrainEquivalent == 12,
                "the port's dash drain must be the recovered 12/tick at 1/10 scale");
        require(pilotFull.recoveredDrainEquivalent == 12,
                "the pilot policy must not change the recovered dash drain");
        // Same conditions, both flag settings: the dash is admitted, on the same row and set.
        require(legacyFull.dashRow == 20 && legacyFull.dashCandidate == 20 &&
                    legacyFull.dashSet == 13,
                "flag-off must enter dash row 20/set 13 with a full meter");
        require(pilotFull.dashRow == 20 && pilotFull.dashCandidate == 20 &&
                    pilotFull.dashSet == 13,
                "the pilot path must enter the same dash row/set at full meter");
        require(legacyFull.stamina < legacyFull.staminaAtStart &&
                    pilotFull.stamina < pilotFull.staminaAtStart,
                "both admitted dashes must have drained their resource");
        // The pilot drains the unified word by exactly the recovered -12 on the
        // admission tick (1000 -> 988); flag-off leaves the legacy gauge untouched
        // at 1000 while draining legacy stamina instead.
        require(pilotFull.gauge == 988 && legacyFull.gauge == 1000,
                "the pilot dash must spend exactly one recovered 12-tick drain");
        // With the meter empty the pilot refuses the recovered gate while flag-off
        // (legacy stamina full, legacy gauge inert) still admits.
        const DashRun pilotMeterEmpty = dashRun(combo, 0, true);
        require(pilotMeterEmpty.dashCandidate == -1,
                "the pilot must refuse the dash with an empty meter (recovered 0 < +0x834)");
        const DashRun legacyMeterEmpty = dashRun(combo, 0, false);
        require(legacyMeterEmpty.dashRow == 20 && legacyMeterEmpty.dashCandidate == 20,
                "flag-off keeps the legacy admission: the legacy gauge never drains");
        if (seededWrongGate) {
            // Deliberately wrong gate: expect the dash ADMITTED at meter 0 on the pilot
            // path. The recovered rule refuses it, so this must fail — proof the assertion
            // tests the resource the code consults and not a tautology.
            require(pilotMeterEmpty.dashCandidate == 20,
                    "seeded wrong gate: expected the dash to be admitted with an empty meter");
        }

        // Case B — spend the magazine funded, then tap on empty, pilot and flag-off.
        const EmptyTapRun pilotEmpty = emptyTapRun(combo, true, 1000, 1);
        require(pilotEmpty.fundedTaps == 6, "six funded taps must spend the primary magazine");
        require(pilotEmpty.emptyVoice == 24,
                "the pilot must publish the recovered empty-shot voice (id 24)");
        require(pilotEmpty.emptyRow == 0 && pilotEmpty.emptyShotRequest < 0,
                "an empty tap must not enter or request a shot row");
        require(pilotEmpty.emptyAmmo == 0 && pilotEmpty.emptySpawns == 0,
                "an empty tap must not spawn a projectile or change the magazine");
        // Case C — the recovered release-count window `0 < released < 20`. 19 frames still asks
        // for the voice; 20 is outside the window and asks for nothing, flag-on or flag-off.
        const EmptyTapRun pilotEdged = emptyTapRun(combo, true, 1000, 19);
        require(pilotEdged.emptyVoice == 24 && pilotEdged.holdTicks == 19,
                "a 19-frame empty hold is inside the recovered window and must voice");
        require(pilotEdged.emptyRow == 0 && pilotEdged.emptyShotRequest < 0 &&
                    pilotEdged.emptySpawns == 0,
                "the 19-frame empty hold must still enter no shot row");
        const EmptyTapRun pilotPast = emptyTapRun(combo, true, 1000, 20);
        require(pilotPast.emptyVoice < 0 && pilotPast.holdTicks == 20,
                "a 20-frame empty hold is outside the recovered window and must be silent");
        require(pilotPast.emptyRow == 0 && pilotPast.emptyShotRequest < 0 &&
                    pilotPast.emptySpawns == 0,
                "the 20-frame empty hold must still enter no shot row");

        const EmptyTapRun legacyEmpty = emptyTapRun(combo, false, 1000, 1);
        require(legacyEmpty.fundedTaps == 6 && legacyEmpty.emptyAmmo == 0,
                "flag-off must spend the same six rounds");
        require(legacyEmpty.emptyVoice < 0,
                "flag-off must keep the recorded silent empty tap");
        require(legacyEmpty.emptyRow == 0 && legacyEmpty.emptyShotRequest < 0,
                "flag-off empty tap must stay on idle with no shot row");
        const EmptyTapRun legacyEdged = emptyTapRun(combo, false, 1000, 19);
        require(legacyEdged.emptyVoice < 0,
                "flag-off must stay silent inside the recovered release window too");

        // Case D — the pilot right side-dash clock (row 23). The row's extra increment on
        // clock 0/9/18 plus the common tail's one increment gives 2/3/4... and the strict
        // 7/12/23 windows put the transitions on one-based updates 7, 18 and 39.
        const DashClockRun pilotRight = dashClockRun(combo, true, input::Action::Right);
        require(pilotRight.ticks.size() == 39,
                "the right dash clock must expose the 39 one-based updates");
        require(pilotRight.ticks[0].phase == 0 && pilotRight.ticks[0].set == 22 &&
                    pilotRight.ticks[0].elapsed == 2 && pilotRight.ticks[0].running,
                "pilot right dash entry must sample clock 2 from the recovered extra increment");
        require(pilotRight.ticks[1].elapsed == 3,
                "pilot right dash update 2 must carry clock 2 + 1");
        require(pilotRight.ticks[6].phase == 1 && pilotRight.ticks[6].set == 23 &&
                    pilotRight.ticks[6].elapsed == 0 && pilotRight.ticks[6].running,
                "pilot right dash update 7 must bind travel set 23 with its clock reset");
        require(pilotRight.ticks[17].phase == 2 && pilotRight.ticks[17].set == 24 &&
                    pilotRight.ticks[17].elapsed == 0 && pilotRight.ticks[17].running,
                "pilot right dash update 18 must bind recovery set 24 with its clock reset");
        require(!pilotRight.ticks[38].running &&
                    pilotRight.ticks[38].state ==
                        static_cast<int>(gameplay::FighterState::Idle) &&
                    pilotRight.ticks[38].phase == 0 && pilotRight.ticks[38].set == 0 &&
                    pilotRight.ticks[38].elapsed == 0,
                "pilot right dash update 39 must end the row on Idle");
        for (int update = 1; update <= 39; ++update)
            checkRightDashClock(pilotRight.ticks[static_cast<std::size_t>(update - 1)],
                                kPilotRightClock[update - 1], update);

        // Travel distance. FUN_0043ffc0 case 0x17 seeds 20.0 on the phase's first update
        // and bleeds 0.5/update (floor 12.5) below phase 2, then 0.7/update (floor 0) in
        // recovery, so the row covers ~382.9 units over its updates. Holding the
        // constant kRunSpeed instead covers 600 — the owner's "goes too far" — so this
        // both pins the profile and fails if the old constant returns.
        double travelled = 0.0;
        for (int update = 1; update <= 38; ++update) {
            const double from = update == 1 ? 0.0
                                            : pilotRight.ticks[static_cast<std::size_t>(update - 2)].x;
            travelled += pilotRight.ticks[static_cast<std::size_t>(update - 1)].x - from;
        }
        require(travelled > 380.0 && travelled < 386.0,
                "pilot right dash must cover the recovered ~383 units, got " +
                    std::to_string(travelled));
        require(travelled < 500.0,
                "the constant-speed side dash (600 units) must not come back, got " +
                    std::to_string(travelled));

        // Meter. The row drains -12 per update only while its phase is below 2
        // (FUN_0043ffc0 case 0x17 :257-259); the recovery phase spends nothing, and the
        // row has no meter exit (:229/:418 are the forward and air arms), so it runs to
        // its last update. From a full meter that is 18 drains = 216, ending at 784.
        for (int update = 1; update <= 18; ++update) {
            const int expected = 1000 - 12 * update;
            require(pilotRight.ticks[static_cast<std::size_t>(update - 1)].gauge == expected,
                    "pilot right dash update " + std::to_string(update) +
                        " must drain 12 to " + std::to_string(expected) + ", got " +
                        std::to_string(pilotRight.ticks[static_cast<std::size_t>(update - 1)].gauge));
        }
        require(pilotRight.ticks[18].gauge == 784,
                "the recovery phase must open at 784, got " +
                    std::to_string(pilotRight.ticks[18].gauge));
        for (int update = 19; update <= 39; ++update)
            require(pilotRight.ticks[static_cast<std::size_t>(update - 1)].gauge == 784,
                    "the recovery phase must not drain: update " + std::to_string(update) +
                        " has " + std::to_string(pilotRight.ticks[static_cast<std::size_t>(update - 1)].gauge) +
                        ", expected 784");
        // Negative controls: the isolated fix is row 23 and pilot-only. Left keeps the old
        // single increment, and flag-off right keeps it too; neither extended timing is
        // asserted here.
        const DashClockRun pilotLeft = dashClockRun(combo, true, input::Action::Left);
        require(pilotLeft.ticks[0].phase == 0 && pilotLeft.ticks[0].set == 19 &&
                    pilotLeft.ticks[0].elapsed == 1 && pilotLeft.ticks[0].running,
                "the right-only clock fix must leave the pilot left dash entry at the old clock 1");
        const DashClockRun legacyRight = dashClockRun(combo, false, input::Action::Right);
        require(legacyRight.ticks[0].phase == 0 && legacyRight.ticks[0].set == 22 &&
                    legacyRight.ticks[0].elapsed == 1 && legacyRight.ticks[0].running,
                "the flag-off right dash must keep the old entry clock 1");
        // The flag-off dash keeps the legacy trigger spend: the recovered per-update drain
        // only exists behind the meter policy, so this must not become 988.
        require(legacyRight.ticks[0].gauge == 1000,
                "flag-off must keep the legacy trigger spend, not the recovered drain");

        // Case E — a sparse clip only writes the bones it names. The travel set 23 keys the
        // right arm and the left leg, so the LEFT arm must keep the pose the startup clip
        // left it in instead of snapping back to bind (prepared_actor_controller_pose.hpp:27:
        // "sparse sets leave unnamed matrices intact", the native controller's own rule).
        // Without it the travel phase renders half the body in the mannequin stance, which is
        // the owner's "left arm is forward and not visible" report.
        {
            const int leftArm = combo.model.findFrame("Bip01_L_UpperArm");
            require(leftArm >= 0, "Rena's rig must carry the left upper arm bone");
            xm::Controller* controller = combo.controller();
            controller->bind(&combo.model);
            std::vector<glm::vec3> T, S;
            std::vector<glm::quat> R;
            const auto sample = [&] {
                controller->evalLocal(T, R, S);
                return R[static_cast<std::size_t>(leftArm)];
            };
            const glm::quat bindPose = sample();
            controller->setAnimationBothTracks(22, true);
            controller->setTrackPosition(0, 0.112);
            controller->setTrackPosition(1, 0.112);
            const glm::quat afterStartup = sample();
            controller->setAnimationBothTracks(23, true);
            controller->setTrackPosition(0, 0.05);
            controller->setTrackPosition(1, 0.05);
            const glm::quat duringTravel = sample();
            require(std::abs(glm::dot(afterStartup, bindPose)) < 0.9995f,
                    "the startup clip must move the left arm away from bind, or this proves nothing");
            require(std::abs(glm::dot(duringTravel, afterStartup)) > 0.9995f,
                    "the sparse travel clip must leave the left arm where the startup clip put it");
        }

        std::printf("PASS rena0 pilot gate: dash resource=drain %d/tick (recovered 12 at 1/10), "
                    "flag-off row%d/set%d pilot row%d/set%d, gauge legacy/pilot (%d/%d), stamina %d/%d; "
                    "meter-empty pilot refusal=%d flag-off admission=%d; "                    "empty tap pilot voice=%d row=%d ammo=%d, flag-off voice=%d; "
                    "release window voice 19f=%d 20f=%d; startup=%d/%d\n",
                    legacyFull.recoveredDrainEquivalent, legacyFull.dashRow, legacyFull.dashSet,
                    pilotFull.dashRow, pilotFull.dashSet, legacyFull.gauge, pilotFull.gauge,
                    legacyFull.stamina, pilotFull.stamina, pilotMeterEmpty.dashCandidate,
                    legacyMeterEmpty.dashCandidate, pilotEmpty.emptyVoice,
                    pilotEmpty.emptyRow, pilotEmpty.emptyAmmo, legacyEmpty.emptyVoice,
                    pilotEdged.emptyVoice, pilotPast.emptyVoice,
                    legacyFull.startup, pilotEmpty.startup);
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "FAIL: %s\n", error.what());
        return 1;
    }
}
