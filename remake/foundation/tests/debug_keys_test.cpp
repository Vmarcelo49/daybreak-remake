// =============================================================================
//  debug_keys_test.cpp — issue #48: the original's in-battle debug keys.
//
//  THE RECOVERED MAP (FUN_00634f60; the table with the DIK codes, the addresses and the gate
//  is in gameplay/debug_keys.h and docs/DEBUG-KEYS.md):
//    Esc 0x01  scene+0x4a40 = 1 — the battle's leave flag
//    F2  0x3c  [fighter+0x860] = 0 for all four — the COM/AI enable flag
//    F3  0x3d  [fighter+0x860] = 1 only where `3 <` the slot's controller/type field
//    F1  0x3b  scene+0x12b0/+0x12bc = 0 (the two sides' balloon percentages) and HP/max HP
//              = 10000 for all four
//    F4  0x3e  one gauge per fighter, chosen by its per-slot +0x318 byte
//
//  WHAT THIS DRIVES, and why in two halves:
//    * the gameplay-level effects go through gameplay::applyDebugKeys, device-free, over a
//      hand-built Match — every key's state change, F3's ownership rule over the whole
//      ownership/pre-state matrix, and the GATE (enabled == false must change nothing,
//      whatever the key set says);
//    * the acceptance criteria are measured through the PRODUCT's own fixed-step path:
//      src/main.cpp is compiled into this TU (SDL_MAIN_HANDLED, the shape
//      lock_switch_camera_test uses) and tickMatch() is called once per SIMULATION tick,
//      with --debug-keys' scripted taps as the injection — a headless run has no window and
//      no key events, and #49 measured that the front end's battle panel does not take the
//      input scripts, so a tick-keyed tap is the only injection that provably lands.
//      That is where "F2 freezes a COM, F3 resumes it, the human slot keeps playing", F1,
//      F4 and Escape's leave request are measured.
//
//  No GPU, no window, no device and no game install: the match runs with the historical null
//  models/weapons, as in the other data-free gameplay tests. No character+weapon combo is
//  bound here and none is claimed (AGENTS rule 7): the damage calls are state injection and
//  every measurement is of a debug key's own write or of the movement/attack state it stopped,
//  never of a combat outcome. The combos fight in the asset-backed half — a live 2v2 on
//  data/stage03 with Rena 0 / Mion 0 / Mion 0 / Rika 0 (three of them on controllers 0-2 and
//  Rika 0 the COM) — which is the docs/RELEASE-CHECKLIST.md recipe run with --debug-keys=
//  and DAYBREAK_DEBUG_KEYS=1.
//
//  Build (the CMake target is `debug_keys_test`):
//    cmake --build remake/foundation/build/linux --target debug_keys_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================

#define SDL_MAIN_HANDLED 1
#include "../src/main.cpp"
// main.cpp sets SDL_MAIN_USE_CALLBACKS, so SDL_main.h renames `main` for the rest of this
// TU. This file is the entry point, so take the name back (same as the other two tests that
// compile the app in).
#undef main

#include <cmath>
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

void checkInt(long long expected, long long actual, const std::string& what) {
    ++g_checks;
    if (expected != actual) {
        ++g_failures;
        std::printf("  FAIL %s: expected %lld, got %lld\n", what.c_str(), expected, actual);
    }
}

void checkFloat(double expected, double actual, const std::string& what) {
    ++g_checks;
    if (std::fabs(expected - actual) > 1e-6) {
        ++g_failures;
        std::printf("  FAIL %s: expected %.6f, got %.6f\n", what.c_str(), expected, actual);
    }
}

void section(const char* title) { std::printf("\n-- %s\n", title); }

// One tick's attack evidence for a fighter: an attack or fire state, or a live projectile it
// owns. Both are things a fighter that is not being driven at all cannot produce.
int fighterAttackingOrFiring(const App& app, int fighter) {
    if (fighter < 0) return 0;   // run() passes -1 when a phase observes nobody
    const gameplay::FighterState s = app.legacyBattle.match().fighter(fighter).state();
    int n = (s == gameplay::FighterState::AttackA || s == gameplay::FighterState::AttackC ||
             s == gameplay::FighterState::ShootA || s == gameplay::FighterState::ShootB ||
             s == gameplay::FighterState::ShootC || s == gameplay::FighterState::ShotFinal)
                ? 1
                : 0;
    for (const gameplay::Projectile& p : app.legacyBattle.match().shots().shots())
        if (p.alive && p.owner == &app.legacyBattle.match().fighter(fighter)) ++n;
    return n;
}

// A bare four-fighter match (2v2, no models): what the key effects act on directly, and the
// object the product fixture below also builds. The round cannot end inside a test: no time
// limit and the widest balloon the settings allow, so the measurements below never run past
// the round-over transition the host would take.
// One synthetic combo for every match this file builds. Static because MatchConfig holds
// POINTERS into it and Match copies the config, so the fixture must outlive the matches
// (AGENTS rule 7: a stepped battle is never an unequipped one).
const test::synthetic::Combo& matchCombo() {
    static const test::synthetic::Combo combo;
    return combo;
}

void resetMatch(gameplay::Match& match, float gauge0 = 0.0f) {
    gameplay::MatchConfig config;
    config.fighterCount = 4;
    config.side[0] = config.side[2] = 0;
    config.side[1] = config.side[3] = 1;
    config.spawn[0] = glm::vec3(0.f);
    config.spawn[1] = glm::vec3(2000.f, 0.f, 0.f);
    config.spawn[2] = glm::vec3(0.f, 0.f, 2000.f);
    config.spawn[3] = glm::vec3(2000.f, 0.f, 2000.f);
    config.timeLimit = 0;
    config.balloonSize[0] = config.balloonSize[1] = gameplay::kBalloonSizeMax;
    config.startGauge[0] = gauge0;
    matchCombo().bind(config, 4);
    const xm::Model* models[4] = {};
    xm::Controller* animations[4] = {};
    match.reset(config, models, animations, nullptr, nullptr);
    match.economy().setLogFile(nullptr);
}

// ---------------------------------------------------------------------------
// Part 1: the five keys on the match itself (the recovered state changes).
// ---------------------------------------------------------------------------
void testKeyEffects() {
    section("F2/F3: the AI-enable flag and F3's ownership rule");
    {
        gameplay::Match match;
        resetMatch(match);
        // The original's initialized value (FUN_0041efa0:10): every slot starts enabled.
        for (int i = 0; i < 4; ++i) check(match.ai_enabled(i), "the flag starts enabled");
        // F2's write is the recovered one: all four slots, ownership untested.
        const bool com[4] = {false, false, true, true};
        gameplay::DebugKeysHeld f2;
        f2.f2 = true;
        check(!gameplay::applyDebugKeys(match, f2, com), "F2 is not a leave request");
        for (int i = 0; i < 4; ++i)
            check(!match.ai_enabled(i), "F2 clears [fighter+0x860] for slot " +
                                           std::to_string(i));

        gameplay::DebugKeysHeld f3;
        f3.f3 = true;
        gameplay::applyDebugKeys(match, f3, com);
        check(!match.ai_enabled(0) && !match.ai_enabled(1),
              "F3 left the two human slots disabled (a human is never handed to the AI)");
        check(match.ai_enabled(2) && match.ai_enabled(3), "F3 re-enabled both COM slots");
    }

    // The whole matrix, not one example: for every ownership mask and every starting flag
    // state, F3 sets exactly the owned slots and moves no other slot's flag.
    {
        int violations = 0;
        for (int mask = 0; mask < 16; ++mask) {
            for (int start = 0; start < 16; ++start) {
                gameplay::Match match;
                resetMatch(match);
                bool owned[4];
                for (int i = 0; i < 4; ++i) {
                    owned[i] = (mask >> i) & 1;
                    match.set_ai_enabled(i, ((start >> i) & 1) != 0);
                }
                gameplay::DebugKeysHeld f3;
                f3.f3 = true;
                gameplay::applyDebugKeys(match, f3, owned);
                for (int i = 0; i < 4; ++i) {
                    const bool want = owned[i] ? true : (((start >> i) & 1) != 0);
                    if (match.ai_enabled(i) != want) ++violations;
                }
            }
        }
        checkInt(0, violations,
                 "F3 over all 16 ownership x 16 pre-state combinations: exactly the COM "
                 "slots enabled, no human slot's flag moved");
    }

    section("F1: HP to full and both balloon counters to 0");
    {
        gameplay::Match match;
        resetMatch(match);
        // A damaged fighter, a KO'd one, and a credited balloon: real state for the key to
        // move, not a default-constructed match.
        match.fighter(2).take_damage(30, &match.fighter(0));
        match.fighter(3).take_damage(1000, &match.fighter(0));
        match.step(nullptr, nullptr, gameplay::FixedStep::seconds);
        checkInt(70, match.fighter(2).hp(), "fighter 2 is damaged");
        checkInt(0, match.fighter(3).hp(), "fighter 3 is down");
        check(match.economy().balloon(1) > 0.0f,
              "the KO credited the victim's side (FUN_00639650's own side)");
        const float display1 = match.economy().balloonDisplay(1);

        const bool com[4] = {false, false, false, false};
        gameplay::DebugKeysHeld f1;
        f1.f1 = true;
        gameplay::applyDebugKeys(match, f1, com);
        for (int i = 0; i < 4; ++i) {
            checkInt(match.fighter(i).max_hp(), match.fighter(i).hp(),
                     "F1 restores slot " + std::to_string(i) + " to full HP");
        }
        checkFloat(0.0, match.economy().balloon(0), "F1 zeroes side 0's balloon");
        checkFloat(0.0, match.economy().balloon(1), "F1 zeroes side 1's balloon");
        // The original's two stores write the raw counter, not the eased display value or
        // the credit popup, so the HUD's readout (which reads the raw value) is what moves.
        checkFloat(display1, match.economy().balloonDisplay(1),
                   "F1 leaves the eased display value alone");
    }

    section("F4: the meters the port models, all below full first");
    {
        gameplay::Match match;
        resetMatch(match, 0.25f);
        checkFloat(0.25, match.fighter(0).hyper_gauge(), "the fixture starts below full");
        check(!match.fighter(0).hyper_ready(), "and hypermode is not ready");
        // Spend MAIN (a tap) and CHARGE (a yellow hold) through the fighter's own fire path,
        // so the meters F4 is about are genuinely not full.
        fnd::input::PlayerState input;
        auto tick = [&]() {
            fnd::input::compute_edges(input);
            const fnd::input::PlayerState* inputs[4] = {&input, nullptr, nullptr, nullptr};
            match.step(inputs, gameplay::FixedStep::seconds);
        };
        for (int i = 0; i < 90; ++i) tick();     // out of the round-start pose (60 frames)
        input.down[fnd::input::Shoot] = true;
        for (int i = 0; i < 2; ++i) tick();      // a tap: the tier that draws MAIN
        input.down[fnd::input::Shoot] = false;
        tick();
        check(match.fighter(0).main_frac() < 1.0f, "the tap spent MAIN");
        for (int i = 0; i < 20; ++i) tick();     // out of the firing/reload window
        input.down[fnd::input::Shoot] = true;
        for (int i = 0; i < 40; ++i) tick();     // 0.625 s: the yellow window
        input.down[fnd::input::Shoot] = false;
        tick();                                   // the release fires the held tier
        check(match.fighter(0).charge_frac() < 1.0f, "the charged tier spent CHARGE");
        check(match.fighter(0).hyper_gauge() < 1.0f, "the hyper gauge is still short");

        const bool com[4] = {false, false, false, false};
        gameplay::DebugKeysHeld f4;
        f4.f4 = true;
        gameplay::applyDebugKeys(match, f4, com);
        for (int i = 0; i < 4; ++i) {
            checkFloat(1.0, match.fighter(i).main_frac(),
                       "F4 fills slot " + std::to_string(i) + "'s MAIN pool");
            checkFloat(1.0, match.fighter(i).charge_frac(),
                       "F4 fills slot " + std::to_string(i) + "'s CHARGE pool");
            checkFloat(1.0, match.fighter(i).hyper_gauge(),
                       "F4 fills slot " + std::to_string(i) + "'s hypermode gauge");
        }
        check(match.fighter(0).hyper_ready(), "and hypermode is ready after F4");
    }

    section("Escape: the leave request, and nothing else");
    {
        gameplay::Match match;
        resetMatch(match);
        const bool com[4] = {true, true, true, true};
        gameplay::DebugKeysHeld esc;
        esc.escape = true;
        check(gameplay::applyDebugKeys(match, esc, com), "Escape asks to leave");
        for (int i = 0; i < 4; ++i)
            check(match.ai_enabled(i), "Escape leaves the AI flag alone");
        checkInt(gameplay::FighterConstants::kMaxHP, match.fighter(0).hp(),
                 "Escape leaves HP alone");
    }

    section("the gate: with the keys switched off nothing changes");
    {
        gameplay::Match match;
        resetMatch(match, 0.5f);
        match.fighter(1).take_damage(20, &match.fighter(0));
        match.step(nullptr, nullptr, gameplay::FixedStep::seconds);
        match.set_ai_enabled(2, false);
        const int hp[4] = {match.fighter(0).hp(), match.fighter(1).hp(),
                           match.fighter(2).hp(), match.fighter(3).hp()};
        const float balloon0 = match.economy().balloon(0);
        const float main0 = match.fighter(0).main_frac();
        const float gauge0 = match.fighter(0).hyper_gauge();
        const bool ai[4] = {match.ai_enabled(0), match.ai_enabled(1),
                            match.ai_enabled(2), match.ai_enabled(3)};

        gameplay::DebugKeysHeld all;
        all.escape = all.f1 = all.f2 = all.f3 = all.f4 = true;
        const bool com[4] = {false, false, true, true};
        check(!gameplay::applyDebugKeys(match, all, com, /*enabled=*/false),
              "a disabled gate does not even report the leave request");
        for (int i = 0; i < 4; ++i) {
            checkInt(hp[i], match.fighter(i).hp(), "gated: HP unchanged");
            check(match.ai_enabled(i) == ai[i], "gated: the AI flag unchanged");
        }
        checkFloat(balloon0, match.economy().balloon(0), "gated: the balloon unchanged");
        checkFloat(main0, match.fighter(0).main_frac(), "gated: MAIN unchanged");
        checkFloat(gauge0, match.fighter(0).hyper_gauge(), "gated: the hyper gauge unchanged");

        // ...and the same key set with the gate open does move all of it, so the check above
        // is not passing because the keys are inert for some other reason.
        check(gameplay::applyDebugKeys(match, all, com, /*enabled=*/true),
              "the same set with the gate open reports the leave");
        // F2's clear and F3's ownership-gated re-enable land in the recovered order, so the
        // COM slots end up enabled again while the human slot F2 cleared stays cleared —
        // the combination is also the shortest proof that F3 did not undo F2 everywhere.
        check(!match.ai_enabled(0), "and does apply F2 (the human slot stays disabled)");
        check(match.ai_enabled(2) && match.ai_enabled(3),
              "and F3 re-enables the COM slots in the same tick's key set");
        checkFloat(0.0, match.economy().balloon(0), "and does apply F1");
        checkFloat(1.0, match.fighter(0).hyper_gauge(), "and does apply F4");
    }
}

// ---------------------------------------------------------------------------
// Part 2: the criteria through the product's own tickMatch.
// ---------------------------------------------------------------------------
// A live front-end 2v2 with one COM (the four-view recipe's shape): panels 0..3, controllers
// 0,1,2 human and 4 (COM) on panel 3. tickMatch is the product's own per-tick path, so the
// key sampling, the fixed-step boundary, the COM input build and the leave request are all
// the shipped ones.
struct Fixture {
    App app;

    Fixture() {
        resetMatch(app.legacyBattle.match(), 0.0f);
        app.frontendMatch = true;
        app.battleLaunch.fighterCount = 4;
        const int controller[4] = {0, 1, 2, 4};
        for (int i = 0; i < 4; ++i) {
            app.battleLaunch.fighters[i].panel = i;
            app.frontend.slots[i].controller = controller[i];
        }
        // initMatch's COM seeding, verbatim: one RNG stream per fighter from the match seed.
        for (int i = 0; i < 4; ++i)
            app.botBrains[i].reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, i));

        // The per-view state initMatch builds (one view per human controller): the camera
        // pool over app.arenaTargets, each following its own fighter.
        std::vector<gameplay::CameraTarget*> pool;
        for (int i = 0; i < 4; ++i) pool.push_back(&app.arenaTargets[i]);
        app.matchViewCount = 3;
        for (int v = 0; v < app.matchViewCount; ++v) {
            game::MatchView& view = app.matchViews[v];
            view = game::MatchView{};
            view.controller = v;
            view.fighter = v;
            view.followed = v;
            view.camera.set_target_pool(pool);
            view.camera.set_active_target(v);
        }
    }

    // One simulation tick with one controller's held set (the frame loop feeds tickInput the
    // same way; driveSyntheticLocalPads writes down[] and calls compute_edges per tick).
    bool tick(int controller = -1, fnd::input::Action action = fnd::input::ActionCount) {
        for (int c = 0; c < 4; ++c) {
            fnd::input::PlayerState& in = app.tickInput[c];
            for (int a = 0; a < fnd::input::ActionCount; ++a) in.down[a] = false;
            if (c == controller && action < fnd::input::ActionCount) in.down[action] = true;
            fnd::input::compute_edges(in);
        }
        return tickMatch(app, gameplay::FixedStep::seconds);
    }

    void tap(int dik, uint64_t tick) {
        app.opts.debugKeyTaps.push_back(DebugKeyTap{tick, dik});
    }

    // One measured window of the product's own ticks: how far the observed fighter moved, how
    // many ticks it spent in an attack/fire state or owned a live shot, and the COM brain's
    // decision count at the end (a brain that is not applied must not be ticked at all).
    struct Window {
        float    moved = 0.f;
        int      events = 0;
        uint64_t brainTicks = 0;
    };

    // `ticks` simulation ticks, one per iteration: `moveCtl` holds Right and `attackCtl`
    // swings on every 20th tick, which is how the two human slots play through the battle
    // above. A negative controller takes no input that tick. `eventSkip` leaves the first
    // ticks out of the event count — a projectile fired just before F2 is still in flight and
    // is not a new attack.
    Window run(int ticks, int observed, int moveCtl, int attackCtl, int eventSkip = 0) {
        Window w;
        glm::vec3 prev = pos(observed);
        for (int i = 0; i < ticks; ++i) {
            if (attackCtl >= 0 && i % 20 == 0) tick(attackCtl, fnd::input::AttackA);
            else if (moveCtl >= 0) tick(moveCtl, fnd::input::Right);
            else tick(-1);
            w.moved += glm::length(pos(observed) - prev);
            prev = pos(observed);
            if (i >= eventSkip) w.events += fighterAttackingOrFiring(app, observed);
        }
        w.brainTicks = app.botBrains[3].stats().ticks;
        return w;
    }

    // run() passes -1 when a phase observes nobody; fighter(-1) is out of bounds.
    glm::vec3 pos(int fighter) const {
        return fighter < 0 ? glm::vec3(0.f) : app.legacyBattle.match().fighter(fighter).position();
    }
};

void testCriteriaThroughTickMatch() {
    section("F2 freezes every COM while the human slots keep playing");
    Fixture f;
    // Phase 1: 400 ticks of a live battle. Controller 1 walks right every tick; controller 0
    // swings on every 20th, so both human slots are visibly playing.
    const Fixture::Window live = f.run(800, 3, 1, 0);
    std::printf("  measured: before F2 the COM moved %.1f units over 800 ticks, %d attack/fire "
                "ticks, %llu brain ticks\n", (double)live.moved, live.events,
                (unsigned long long)live.brainTicks);
    check(live.moved > 100.f, "before F2 the COM moves");
    check(live.brainTicks > 0, "and its brain is deciding");

    // Phase 2: F2 on the very next tick, then 400 ticks of measurement.
    f.tap(gameplay::kDikF2, f.app.matchFrame + 1);
    f.tick(-1);   // the F2 tick itself
    check(!f.app.legacyBattle.match().ai_enabled(3), "the COM slot's AI flag is off on F2's own tick");
    {
        // A shot the COM fired BEFORE F2 keeps flying and its firing state keeps the fighter
        // sliding for a few ticks (the port's velocity decay; the original's F2 zeroes the
        // input block, not the velocity or the projectile pool), so the exact freeze is
        // measured once that has run out — 60 ticks later.
        f.run(60, -1, -1, -1);
        const uint64_t brainBefore = f.app.botBrains[3].stats().ticks;
        const Fixture::Window frozen = f.run(400, 3, 1, 0);
        std::printf("  measured: with F2 the COM moved %.2f units over the next 400 ticks, "
                    "%d attack/fire ticks, brain ticks %llu -> %llu\n", (double)frozen.moved,
                    frozen.events, (unsigned long long)brainBefore,
                    (unsigned long long)frozen.brainTicks);
        checkFloat(0.0, frozen.moved,
                   "F2 froze the COM: EXACTLY 0 units over the next 400 ticks");
        checkInt(0, frozen.events,
                 "and it held no attack/fire state and owned no live shot");
        checkInt((long long)brainBefore, (long long)f.app.botBrains[3].stats().ticks,
                 "and its brain was not ticked at all");
    }
    // F2's write is the recovered one: all four slots. The human slots are driven by their
    // controllers, so their flag is never consulted — and they keep playing.
    check(!f.app.legacyBattle.match().ai_enabled(0) && !f.app.legacyBattle.match().ai_enabled(1) &&
              !f.app.legacyBattle.match().ai_enabled(2),
          "F2 also cleared the human slots' flags (the recovered write is all four)");
    {
        const Fixture::Window walk = f.run(100, 1, 1, -1);
        const Fixture::Window swing = f.run(100, 0, -1, 0);
        std::printf("  measured: while the flag was cleared a human slot moved %.1f units over "
                    "100 ticks and the other held %d attack ticks\n", (double)walk.moved,
                    swing.events);
        check(walk.moved > 100.f, "a human slot still moved while its flag was cleared");
        check(swing.events > 0, "and the other human's swings still started");
    }

    section("F3 re-enables exactly the COM slots, and a human slot stays human");
    f.tap(gameplay::kDikF3, f.app.matchFrame + 1);
    f.tick(-1);   // the F3 tick itself
    check(f.app.legacyBattle.match().ai_enabled(3), "F3 re-enabled the COM slot");
    check(!f.app.legacyBattle.match().ai_enabled(0) && !f.app.legacyBattle.match().ai_enabled(1) &&
              !f.app.legacyBattle.match().ai_enabled(2),
          "and did not hand any human slot to the AI");
    {
        const Fixture::Window resumed = f.run(100, 3, 1, 0);
        std::printf("  measured: after F3 the COM moved %.1f units over 100 ticks, %d "
                    "attack/fire ticks, %llu brain ticks\n", (double)resumed.moved,
                    resumed.events, (unsigned long long)resumed.brainTicks);
        check(resumed.moved > 100.f, "the COM is moving again after F3");
        check(resumed.brainTicks > 0, "its brain is deciding again too");
        check(resumed.events > 0, "and it is attacking again");
    }
    check(!f.app.legacyBattle.match().ai_enabled(2), "the other human slot is still not AI-driven");

    section("F1 and F4 change the state the HUD reads");
    {
        // A fresh battle, nobody fighting: the keys' own effect, measured without a brawl.
        Fixture q;
        q.run(120, -1, -1, -1);   // out of the round-start pose, into the live battle
        q.app.legacyBattle.match().fighter(1).take_damage(60, &q.app.legacyBattle.match().fighter(0));
        q.app.legacyBattle.match().fighter(2).take_damage(1000, &q.app.legacyBattle.match().fighter(0));
        q.tick(-1);   // let the KO credit reach the balloon
        checkInt(40, q.app.legacyBattle.match().fighter(1).hp(), "fighter 1 is damaged");
        checkInt(0, q.app.legacyBattle.match().fighter(2).hp(), "fighter 2 is down");
        check(q.app.legacyBattle.match().economy().balloon(0) > 0.f, "the balloon moved with the KO");
        std::printf("  measured: before F1 slot 1 hp=%d/%d, slots 2/3 hp=%d,%d, balloons "
                    "%.0f/%.0f\n", q.app.legacyBattle.match().fighter(1).hp(), q.app.legacyBattle.match().fighter(1).max_hp(),
                    q.app.legacyBattle.match().fighter(2).hp(), q.app.legacyBattle.match().fighter(3).hp(),
                    (double)q.app.legacyBattle.match().economy().balloon(0),
                    (double)q.app.legacyBattle.match().economy().balloon(1));
        const float display = q.app.legacyBattle.match().economy().balloonDisplay(0);
        q.tap(gameplay::kDikF1, q.app.matchFrame + 1);
        q.tick(-1);
        for (int i = 0; i < 4; ++i)
            checkInt(q.app.legacyBattle.match().fighter(i).max_hp(), q.app.legacyBattle.match().fighter(i).hp(),
                     "F1 restored slot " + std::to_string(i) + " to full");
        checkFloat(0.0, q.app.legacyBattle.match().economy().balloon(0), "F1 zeroed the balloons");
        std::printf("  measured: after F1 slot 1 hp=%d/%d, slots 2/3 hp=%d,%d, balloons "
                    "%.0f/%.0f\n", q.app.legacyBattle.match().fighter(1).hp(), q.app.legacyBattle.match().fighter(1).max_hp(),
                    q.app.legacyBattle.match().fighter(2).hp(), q.app.legacyBattle.match().fighter(3).hp(),
                    (double)q.app.legacyBattle.match().economy().balloon(0),
                    (double)q.app.legacyBattle.match().economy().balloon(1));
        checkFloat(display, q.app.legacyBattle.match().economy().balloonDisplay(0),
                   "F1 left the HUD's eased display value to the economy");

        // Drain MAIN and CHARGE through the fighter's own fire path: a tap draws MAIN, a
        // hold past the yellow threshold draws CHARGE.
        q.tick(0, fnd::input::Shoot);
        q.tick(0, fnd::input::Shoot);
        q.tick(-1);                                // the release fires the tap
        for (int i = 0; i < 20; ++i) q.tick(-1);   // out of the firing state, into recharge
        check(q.app.legacyBattle.match().fighter(0).main_frac() < 1.f, "the tap spent MAIN");
        for (int i = 0; i < 45; ++i) q.tick(0, fnd::input::Shoot);
        q.tick(-1);                                // the release fires the charged tier
        for (int i = 0; i < 20; ++i) q.tick(-1);
        check(q.app.legacyBattle.match().fighter(0).charge_frac() < 1.f, "the charged tier spent CHARGE");
        // The gauge the fight left alone is put below full through the same launch-time seam
        // the visual suite uses, so the "before" arm of F4's check is not a full bar.
        q.app.legacyBattle.match().fighter(0).set_hyper_gauge(0.25f);
        checkFloat(0.25, q.app.legacyBattle.match().fighter(0).hyper_gauge(), "the hyper gauge starts short");
        std::printf("  measured: before F4 main=%.3f charge=%.3f hyper=%.3f\n",
                    (double)q.app.legacyBattle.match().fighter(0).main_frac(),
                    (double)q.app.legacyBattle.match().fighter(0).charge_frac(),
                    (double)q.app.legacyBattle.match().fighter(0).hyper_gauge());
        q.tap(gameplay::kDikF4, q.app.matchFrame + 1);
        q.tick(-1);
        checkFloat(1.0, q.app.legacyBattle.match().fighter(0).main_frac(), "F4 filled MAIN");
        checkFloat(1.0, q.app.legacyBattle.match().fighter(0).charge_frac(), "F4 filled CHARGE");
        checkFloat(1.0, q.app.legacyBattle.match().fighter(0).hyper_gauge(), "F4 filled the hypermode gauge");
        std::printf("  measured: after F4 main=%.3f charge=%.3f hyper=%.3f (HUD hyper=%.3f)\n",
                    (double)q.app.legacyBattle.match().fighter(0).main_frac(),
                    (double)q.app.legacyBattle.match().fighter(0).charge_frac(),
                    (double)q.app.legacyBattle.match().fighter(0).hyper_gauge(),
                    (double)q.app.matchViews[0].hud.hyperGauge);
        check(q.app.legacyBattle.match().fighter(0).hyper_ready(), "so hypermode is ready");
        // The HUD values tickMatch pushed for the views are what the composer draws.
        const ui::HudState& hud = q.app.matchViews[0].hud;
        checkFloat(1.0, hud.hyperGauge, "the HUD's hyper bar reads full after F4");
        checkInt(q.app.legacyBattle.match().fighter(0).main_whole(), hud.mainWhole,
                 "the HUD's MAIN stocks are the fighter's own");
        checkInt(q.app.legacyBattle.match().fighter(0).charge_whole(), hud.chargeWhole,
                 "the HUD's CHARGE stocks are the fighter's own");
        // Every measurement above is a LIVE battle: if the fixture's round had ended, the host
        // would have left for the result screen and the numbers would be of a frozen match.
        check(!q.app.legacyBattle.match().economy().roundOver(),
              "the round stayed live (no time limit, 200% balloons)");
    }

    section("Escape: tickMatch reports the leave on exactly its own tick");
    {
        Fixture e;
        const uint64_t at = 60;
        e.tap(gameplay::kDikEscape, at);
        int leaves = 0;
        uint64_t leaveTick = 0;
        for (uint64_t t = 1; t <= 120; ++t) {
            if (e.tick(-1)) {
                ++leaves;
                leaveTick = t;
            }
        }
        checkInt(1, leaves, "Escape asks to leave once, not on every tick after it");
        checkInt((long long)at, (long long)leaveTick, "and on the tick the tap named");
        checkInt(120, (long long)e.app.matchFrame,
                 "and the tick it landed on simulated like any other");
    }

    section("Escape's two bindings: the pause owns it only where the pause is available");
    {
        Fixture p;
        p.app.matchMode = true;   // the host's flag for a live battle
        p.app.matchInput.note_key(fnd::input::sdl3::kScEscape, true);
        check(!sampleDebugKeys(p.app, 1).escape,
              "an interactive battle's Escape is issue #15's pause key, not the leave");
        p.app.opts.out = "/tmp/never-written.ppm";   // a capture: no pause there
        check(sampleDebugKeys(p.app, 1).escape,
              "a capture's Escape is the recovered leave again");
        p.app.opts.out.clear();
        p.tap(gameplay::kDikEscape, 7);
        check(sampleDebugKeys(p.app, 7).escape,
              "a scripted tap is never redirected, wherever it runs");
        check(!sampleDebugKeys(p.app, 8).escape, "and holds on its own tick alone");
        p.app.matchInput.note_key(fnd::input::sdl3::kScEscape, false);
    }

    section("the gate through the product: --no-debug-keys");
    {
        Fixture g;
        g.run(120, -1, -1, -1);
        g.app.opts.noDebugKeys = true;
        const uint64_t at = g.app.matchFrame + 1;
        g.tap(gameplay::kDikF1, at);
        g.tap(gameplay::kDikF2, at);
        g.tap(gameplay::kDikF3, at);
        g.tap(gameplay::kDikF4, at);
        g.tap(gameplay::kDikEscape, at);
        g.app.legacyBattle.match().fighter(2).take_damage(1000, &g.app.legacyBattle.match().fighter(0));
        g.tick(-1);   // let the KO credit reach the balloon
        const int hp1 = g.app.legacyBattle.match().fighter(1).hp();
        const float gauge = g.app.legacyBattle.match().fighter(0).hyper_gauge();
        const float main = g.app.legacyBattle.match().fighter(0).main_frac();
        const float balloon = g.app.legacyBattle.match().economy().balloon(0);
        for (int t = 0; t < 30; ++t) check(!g.tick(-1), "a gated Escape never asks to leave");
        checkInt(hp1, g.app.legacyBattle.match().fighter(1).hp(), "gated: F1 did not restore HP");
        for (int i = 0; i < 4; ++i)
            check(g.app.legacyBattle.match().ai_enabled(i), "gated: F2 did not clear the flag");
        checkFloat(gauge, g.app.legacyBattle.match().fighter(0).hyper_gauge(), "gated: F4 changed no gauge");
        checkFloat(main, g.app.legacyBattle.match().fighter(0).main_frac(), "gated: MAIN unchanged");
        checkFloat(balloon, g.app.legacyBattle.match().economy().balloon(0), "gated: the balloon unchanged");
    }

    section("the injection itself: --debug-keys parses to tick-keyed taps");
    {
        std::vector<DebugKeyTap> taps;
        std::string error;
        check(parseDebugKeys("f2@300,F3@600,esc@900,f1@1,f4@2", taps, error),
              "the tap list parses");
        checkInt(5, (long long)taps.size(), "five taps");
        checkInt(300, (long long)taps[0].tick, "the first tap's tick");
        check(taps[0].dik == gameplay::kDikF2 && taps[1].dik == gameplay::kDikF3 &&
                  taps[2].dik == gameplay::kDikEscape && taps[3].dik == gameplay::kDikF1 &&
                  taps[4].dik == gameplay::kDikF4,
              "and its key, as the recovered DIK scancode (case-insensitive, esc for escape)");
        taps.clear();
        check(!parseDebugKeys("f2", taps, error), "a tap without a tick is rejected");
        check(!parseDebugKeys("f9@10", taps, error), "an unknown key is rejected");
        check(!parseDebugKeys("f2@0", taps, error), "tick 0 is rejected (ticks are 1-based)");
    }
}

void testSpectatorPause() {
    App app;
    app.frontendMatch = true;
    app.matchMode = true;
    app.battleLaunch.fighterCount = 4;
    // No GPU/audio is needed to exercise the shipped input and pause transitions.
    app.pauseUiReady = true;
    app.pauseSoundTried = true;
    for (int i = 0; i < 4; ++i) {
        app.battleLaunch.fighters[i].panel = i;
        app.frontend.slots[i].controller = 4;
    }
    auto edge = [&](int controller, fnd::input::Action action) {
        for (auto& input : app.tickInput) input = {};
        app.tickInput[controller].just_pressed[action] = true;
    };
    section("issue #64: COM-only pause through the product's input and menu");
    for (int controller = 0; controller < 4; ++controller) {
        edge(controller, fnd::input::Pause);
        check(battlePausePressed(app), "a spectator can open a COM-only pause");
        enterBattlePause(app, "COM-only test");
        check(app.battlePaused && app.legacyBattle.match().paused(), "the authoritative match is paused");
        edge(controller, fnd::input::Down);
        tickBattlePause(app);
        checkInt(1, app.pauseMenu.row, "Down navigates to Rematch");
        edge(controller, fnd::input::Up);
        tickBattlePause(app);
        checkInt(0, app.pauseMenu.row, "Up navigates to Resume");
        edge(controller, fnd::input::Jump);
        tickBattlePause(app);
        check(!app.battlePaused && !app.legacyBattle.match().paused(), "confirm resumes the match");
        enterBattlePause(app, "COM-only toggle test");
        edge(controller, fnd::input::Pause);
        tickBattlePause(app);
        check(!app.battlePaused, "the pause action also resumes");
    }
    app.frontend.slots[2].controller = 1;
    for (int controller = 0; controller < 4; ++controller) {
        edge(controller, fnd::input::Pause);
        check(battlePausePressed(app) == (controller == 1),
              "a human match accepts only its fighter's controller");
    }
    enterBattlePause(app, "human ownership test");
    edge(3, fnd::input::Down);
    tickBattlePause(app);
    checkInt(0, app.pauseMenu.row, "a spectator cannot navigate a human match's pause");
    edge(3, fnd::input::Jump);
    tickBattlePause(app);
    check(app.battlePaused, "a spectator cannot confirm a human match's pause");
    edge(1, fnd::input::Pause);
    tickBattlePause(app);
    check(!app.battlePaused, "the human owner can resume");
    app.frontendMatch = false;
    app.matchInputReady = true;
    edge(0, fnd::input::Pause);
    check(battlePausePressed(app), "standalone retains controller 0");
    edge(1, fnd::input::Pause);
    check(!battlePausePressed(app), "standalone excludes other controllers");
    app.matchInputReady = false;
    edge(0, fnd::input::Pause);
    check(!battlePausePressed(app), "standalone requires input initialization");
    app.frontendMatch = true;
    app.battleLaunch.fighterCount = 0;
    check(!battlePausePressed(app), "an empty launch is not a COM-only battle");
}

}  // namespace

int main() {
    std::printf("debug_keys_test — issue #48's in-battle debug keys (FUN_00634f60)\n");
    testKeyEffects();
    testCriteriaThroughTickMatch();
    testSpectatorPause();
    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failures);
    if (g_failures == 0) std::printf("DEBUG_KEYS: ok\n");
    return g_failures == 0 ? 0 : 1;
}
