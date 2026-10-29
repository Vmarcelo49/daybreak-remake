// F1-3 deterministic offline fixtures for the Rena+0 pilot (DIRECTION.md §4 Phase 1).
//
// A fixture is a text file (tests/fixtures/rena0/*.fixture) recording combo, spawn,
// collision scope, per-tick inputs and the expected observables of the F1-2 contract.
// This runner drives the PRODUCTION Match/Fighter path over the real combo data and
// checks each expectation; it is not a second simulation engine. Input tokens reuse
// `input::parse_script_line`, the same vocabulary as the scripted `--script` runs.
//
// Expectations must cite recovered code or an independent artifact in the fixture's own
// header comment; a value that only reflects current port behaviour is a tier-6 port
// rule and has to be labelled as such there.
//
// Format (docs/PILOT-EVIDENCE-CONTRACT.md §8):
//   combo <character> <weapon>       required, exactly one
//   seed <uint32>                    required; must be SimulationRng::kDefaultSeed today
//   spawn <slot> <x> <y> <z>         slot 0 = actor, slot 1 = neutral equipped dummy
//   collision open-field             required; staged is not implemented yet
//   input <tick> <TOKEN...>          tokens as in --script ('-' releases all)
//   expect <tick> <field> <value>    fields listed in evalExpectation below
// Fixtures never force a state: startup is stepped normally from BattleStart.
#include "combo_fixture.h"
#include "gameplay/fixed_step.h"
#include "gameplay/native/rena0_pilot_adapter.h"
#include "rena0_fixture.h"
#include "gameplay/match.h"
#include "input/input.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
namespace input = fnd::input;
using rena0fix::Expectation;
using rena0fix::Fixture;
using rena0fix::parseFixture;

constexpr double kFloatTol = 1e-3;

double near(double a, double b) { return std::abs(a - b) < kFloatTol; }

// The enforcement copy of the acceptance scope: DIRECTION.md §4 Phase 2's target cases
// and the contract's §2b acceptance observables. It is deliberately independent of
// MANIFEST.txt so that deleting a line from either one fails here instead of shrinking the
// denominator. Update both together.
// Contract v3 requires each case/fixture pair, not merely a case label: the four dashes,
// melee variants and pilot/legacy guard comparison must not replace one another.
const std::pair<const char*, const char*> kRequiredCases[] = {
    {"idle", "rena0-idle-walk-turn-stop.fixture"},
    {"walk", "rena0-idle-walk-turn-stop.fixture"},
    {"ground-dashes", "rena0-ground-dash-left.fixture"},
    {"ground-dashes", "rena0-ground-dash-right.fixture"},
    {"ground-dashes", "rena0-ground-dash-up.fixture"},
    {"ground-dashes", "rena0-ground-dash-down.fixture"},
    {"jump-landing", "rena0-jump-chain.fixture"},
    {"air-dash", "rena0-air-dash-left.fixture"},
    {"tap-shot", "rena0-tap-shot.fixture"},
    {"charge-levels", "rena0-charge-hold.fixture"},
    {"melee-string", "rena0-melee-ground-300.fixture"},
    {"melee-string", "rena0-melee-back-310.fixture"},
    {"melee-string", "rena0-melee-lateral-311.fixture"},
    {"melee-string", "rena0-melee-air-320.fixture"},
    {"melee-string", "rena0-melee-forward-dash-330.fixture"},
    {"melee-string", "rena0-melee-lateral-dash-331.fixture"},
    {"melee-string", "rena0-melee-air-dash-332.fixture"},
    {"guard", "rena0-guard-hold.fixture"},
    {"hit", "rena0-hit-ground-300.fixture"},
    {"ko", "rena0-ko-ground-300.fixture"},
    {"guard-gate", "rena0-guard-gate-pilot.fixture"},
    {"guard-gate", "rena0-guard-gate-legacy.fixture"},
    {"shot-gauge", "rena0-powered-shot.fixture"},
    {"shot-gauge", "rena0-shot-recovery.fixture"},
    {"round-timeout", "rena0-round-timeout.fixture"},
    {"idle-refill", "rena0-idle-refill.fixture"},
    {"single-hover", "rena0-single-hover.fixture"},
    {"jump-climb", "rena0-jump-climb.fixture"},
    {"air-turn", "rena0-air-turn.fixture"},
    {"attack-empty-meter", "rena0-attack-empty-meter.fixture"}};
const std::pair<const char*, const char*> kRequiredFields[] = {
    {"state", "rena0-idle-walk-turn-stop.fixture"},
    {"state_enum", "rena0-melee-ground-300.fixture"},
    {"airborne", "rena0-jump-chain.fixture"},
    {"anim_row", "rena0-idle-walk-turn-stop.fixture"},
    {"anim_set", "rena0-jump-chain.fixture"},
    {"phase", "rena0-idle-walk-turn-stop.fixture"},
    {"elapsed", "rena0-idle-walk-turn-stop.fixture"},
    {"x", "rena0-idle-walk-turn-stop.fixture"},
    {"y", "rena0-jump-climb.fixture"},
    {"z", "rena0-idle-walk-turn-stop.fixture"},
    {"step", "rena0-idle-walk-turn-stop.fixture"},
    {"turn_deg", "rena0-idle-walk-turn-stop.fixture"},
    {"turn_deg", "rena0-air-turn.fixture"},
    {"stamina", "rena0-guard-hold.fixture"},
    {"dash_row", "rena0-ground-dash-left.fixture"},
    {"air_dash_context", "rena0-air-dash-left.fixture"},
    {"shot_row", "rena0-tap-shot.fixture"},
    {"shot_tier", "rena0-tap-shot.fixture"},
    {"shot_fired", "rena0-tap-shot.fixture"},
    {"shot_bullet_row", "rena0-tap-shot.fixture"},
    {"shot_bullet_row", "rena0-powered-shot.fixture"},
    {"shot_bullet_row", "rena0-shot-recovery.fixture"},
    {"shots", "rena0-tap-shot.fixture"},
    {"main_whole", "rena0-tap-shot.fixture"},
    {"charge_tier", "rena0-charge-hold.fixture"},
    {"yellow_hold_sec", "rena0-charge-hold.fixture"},
    {"red_hold_sec", "rena0-charge-hold.fixture"},
    {"attack_row", "rena0-melee-ground-300.fixture"},
    {"swing_started", "rena0-melee-ground-300.fixture"},
    {"melee_active", "rena0-melee-ground-300.fixture"},
    {"melee_recovery", "rena0-hit-ground-300.fixture"},
    {"swing_hits", "rena0-hit-ground-300.fixture"},
    {"melee_hit", "rena0-hit-ground-300.fixture"},
    {"melee_victim", "rena0-hit-ground-300.fixture"},
    {"guard_started", "rena0-guard-hold.fixture"},
    {"guard_exhausted", "rena0-guard-hold.fixture"},
    {"charge_gauge", "rena0-powered-shot.fixture"},
    {"charge_gauge", "rena0-shot-recovery.fixture"},
    {"charge_gauge", "rena0-idle-refill.fixture"},
    {"dummy_hp", "rena0-hit-ground-300.fixture"},
    {"dummy_alive", "rena0-ko-ground-300.fixture"},
    {"dummy_ko", "rena0-ko-ground-300.fixture"},
    {"dummy_respawned", "rena0-ko-ground-300.fixture"},
    {"round_over", "rena0-round-timeout.fixture"},
    {"round_end", "rena0-round-timeout.fixture"},
    {"balloon1", "rena0-round-timeout.fixture"},
    {"dummy_static", "rena0-idle-walk-turn-stop.fixture"}};

// Per-observable tolerance, kept in step with the contract's §2b table: positions and
// displacements carry accumulation noise, the hold-seconds are exact data-derived values
// so they get a tighter bound, and an angle in degrees is compared at 1e-2.
double toleranceFor(const std::string& field) {
    if (field == "yellow_hold_sec" || field == "red_hold_sec") return 1e-4;
    if (field == "turn_deg") return 1e-2;
    return kFloatTol;
}

// Authoring aid for `trace`: the row of the newest live P1 shot (-1 when none) and how many
// of P1's shots are live. The powered 402 branch is only visible through the launched row.
int newest_shot_row(const gameplay::Match& match) {
    int row = -1;
    for (const gameplay::Projectile& shot : match.shots().shots())
        if (shot.alive && shot.owner == &match.fighter(0)) row = shot.bulletRow;
    return row;
}

int live_p1_shots(const gameplay::Match& match) {
    int live = 0;
    for (const gameplay::Projectile& shot : match.shots().shots())
        if (shot.alive && shot.owner == &match.fighter(0)) ++live;
    return live;
}

std::string evalExpectation(const gameplay::Match& match, const gameplay::CharacterMoves& moves,
                            const gameplay::MatchFrame& frame, bool dummyStatic, const Expectation& e,
                            const glm::vec3& previousPosition, float previousYaw) {
    const gameplay::Fighter& f = match.fighter(0);
    const double v = e.value;
    // One branch per observable, no duplicates. Ints/enums/bools compare exactly and
    // report exp/got; floats use kFloatTol and report both values. `anim_row` also
    // requires the clip not to be the fallback, and `anim_set` pins a raw set index.
    auto exact = [&](const char* name, long long got) {
        return v == (double)got ? std::string()
                                : name + std::string(" exp ") + std::to_string((long long)v) +
                                      " got " + std::to_string(got);
    };
    auto boolean = [&](const char* name, bool got) {
        return (v != 0.0) == got ? std::string() : name + std::string(" exp ") +
            std::to_string((int)(v != 0.0)) + " got " + std::to_string((int)got);
    };
    auto real = [&](const char* name, double got) {
        const double tol = toleranceFor(name);
        return std::abs(v - got) < tol
                   ? std::string()
                   : name + std::string(" exp ") + std::to_string(v) + " got " + std::to_string(got) +
                         " (tol " + std::to_string(tol) + ")";
    };
    if (e.field == "state") return exact("state", f.action_state());
    if (e.field == "state_enum") return exact("state_enum", (long long)f.state());
    if (e.field == "phase") return exact("phase", f.move_phase());
    if (e.field == "elapsed") return exact("elapsed", f.phase_elapsed());
    if (e.field == "dash_row") return exact("dash_row", f.dash_move_id());
    if (e.field == "shot_row") return exact("shot_row", f.shot_move_id());
    if (e.field == "shot_tier") return exact("shot_tier", (long long)f.last_shot_tier());
    if (e.field == "attack_row") return exact("attack_row", f.attack_move_id());
    if (e.field == "charge_tier") return exact("charge_tier", (long long)f.charge_tier());
    if (e.field == "charge_gauge") return exact("charge_gauge", f.charge_gauge());
    if (e.field == "main_whole") return exact("main_whole", f.main_whole());
    if (e.field == "shots") return exact("shots", frame.shotsSpawned);
    if (e.field == "swing_hits") return exact("swing_hits", f.swing_hit_count());
    if (e.field == "melee_victim") return exact("melee_victim", frame.meleeVictim[0]);
    if (e.field == "hp") return exact("hp", f.hp());
    if (e.field == "stamina") return exact("stamina", f.stamina());
    if (e.field == "dummy_hp") return exact("dummy_hp", match.fighter(1).hp());
    if (e.field == "ko_credit") return exact("ko_credit", frame.koCredits[0]);
    if (e.field == "round_end") return exact("round_end", (long long)match.economy().roundEnd());
    if (e.field == "x") return real("x", (double)f.position().x);
    if (e.field == "z") return real("z", (double)f.position().z);
    // Height above the spawn floor: the recovered jump has no altitude cap, so a case
    // that climbs for many ticks must show y rising past the old 420-unit port limit.
    if (e.field == "y") return real("y", (double)f.position().y);
    if (e.field == "yellow_hold_sec") return real("yellow_hold_sec", (double)f.yellow_hold_sec());
    if (e.field == "red_hold_sec") return real("red_hold_sec", (double)f.red_hold_sec());
    if (e.field == "balloon1") return real("balloon1", (double)match.economy().balloon(1));
    if (e.field == "airborne") return boolean("airborne", f.airborne());
    if (e.field == "air_dash_context") return boolean("air_dash_context", f.air_dash_context());
    if (e.field == "melee_active") return boolean("melee_active", f.melee_in_active());
    if (e.field == "melee_recovery") return boolean("melee_recovery", f.melee_in_recovery());
    if (e.field == "swing_started") return boolean("swing_started", frame.swingStarted[0]);
    if (e.field == "shot_fired") return boolean("shot_fired", frame.shotFired[0]);
    if (e.field == "shot_bullet_row") {
        // The item row the newest live shot carries. The recovered 402 body picks row 7 on the
        // powered branch and row 1 otherwise (FUN_0043ffc0.c:2009-2014, :1961-1965), so this is
        // the observable that separates them; -1 means no live shot of P1's.
        int row = -1;
        for (const gameplay::Projectile& shot : match.shots().shots())
            if (shot.alive && shot.owner == &f) row = shot.bulletRow;
        return exact("shot_bullet_row", row);
    }
    if (e.field == "guard_started") return boolean("guard_started", frame.guardStarted[0]);
    if (e.field == "guard_exhausted") return boolean("guard_exhausted", f.guard_exhausted());
    if (e.field == "melee_hit") return boolean("melee_hit", frame.meleeHit[0]);
    if (e.field == "dummy_alive") return boolean("dummy_alive", match.fighter(1).is_alive());
    if (e.field == "dummy_pending_ko") return boolean("dummy_pending_ko", match.fighter(1).pending_ko());
    if (e.field == "dummy_ko") return boolean("dummy_ko", match.economy().koAt(1) >= 0.0);
    if (e.field == "dummy_respawned") return boolean("dummy_respawned", frame.respawned[1]);
    if (e.field == "round_over") return boolean("round_over", match.economy().roundOver());
    if (e.field == "dummy_static") return boolean("dummy_static", dummyStatic);
    if (e.field == "anim_row") {
        const int row = (int)v;
        if (f.anim_set_index() == moves.first_set_index(row) && !f.anim_fallback()) return "";
        return "anim_row " + std::to_string(row) + " exp set " +
               std::to_string(moves.first_set_index(row)) + " got " +
               std::to_string(f.anim_set_index()) + (f.anim_fallback() ? " (fallback)" : "");
    }
    if (e.field == "anim_set") {
        if (v == f.anim_set_index() && !f.anim_fallback()) return "";
        return "anim_set exp " + std::to_string((int)v) + " got " +
               std::to_string(f.anim_set_index()) + (f.anim_fallback() ? " (fallback)" : "");
    }
    if (e.field == "step") return real("step", (double)glm::length(f.position() - previousPosition));
    if (e.field == "turn_deg")
        return real("turn_deg", glm::degrees((double)std::remainder(f.facing_yaw() - previousYaw,
                                                                    glm::two_pi<float>())));
    return "unknown field '" + e.field + "'";
}

bool runFixture(const Fixture& fx, std::string& error) {
    if (fx.seed != gameplay::SimulationRng::kDefaultSeed) {
        // Match resets its own stream and exposes no seeding entry point yet (P2-2 asks
        // which RNG the bodies expect); a non-default fixture seed cannot be honoured, so
        // it fails loudly instead of silently running the default stream.
        error = "fixture seed " + std::to_string(fx.seed) + " is not SimulationRng::kDefaultSeed (" +
                std::to_string(gameplay::SimulationRng::kDefaultSeed) + "); Match exposes no seeding yet";
        return false;
    }
    test::Combo combo;
    if (!combo.load(fx.character, fx.weapon, error)) return false;
    if (combo.moves.character_index() != fx.character) { error = "combo identity mismatch"; return false; }

    gameplay::Match match;
    gameplay::MatchConfig config;
    config.spawn[0] = fx.spawn[0];
    config.spawn[1] = fx.spawn[1];
    config.startHP[1] = fx.dummyStartHp;
    config.timeLimit = fx.timeLimit;
    const xm::Model* models[gameplay::kMatchFighterCount] = {&combo.model, &combo.model};
    xm::Controller* controllers[gameplay::kMatchFighterCount] = {combo.controller(), combo.controller()};
    for (int i = 0; i < 2; ++i) {
        config.moves[i] = &combo.moves;
        config.weapon[i] = &combo.weapon;
    }
    match.reset(config, models, controllers, nullptr, nullptr, nullptr);  // open-field: no collision
    // P2-7 meter family: the acceptance runner drives Rena+0 on the unified word, exactly
    // as --native-actions=rena0 does live. The legacy guard-gate fixture below pins the
    // damage rule, which the meter does not touch, so it stays valid under the policy.
    gameplay::native::Rena0PilotMeterPolicy pilotMeterPolicy;
    match.fighter(0).set_pilot_meter(&pilotMeterPolicy);
    // After reset, because reset() restores the cap. This is the only way a fixture can observe
    // the recovery rule: the product has no path that lowers the gauge (Q19 removed the
    // misattributed powered-shot deduction).
    if (fx.chargeGaugeSet) match.fighter(0).set_charge_gauge(fx.chargeGauge);
    match.set_ai_enabled(1, false);
    match.economy().setLogFile(nullptr);
    input::PlayerState actor{};
    // The dummy's slot takes no input by default (the DX9 scene's shape). A guarded-contact
    // fixture needs it holding Guard, which is the port's own guard key.
    input::PlayerState dummyInput{};
    if (fx.dummyGuard) dummyInput.down[input::Action::Guard] = true;
    const input::PlayerState* inputs[gameplay::kMatchFighterCount] = {
        &actor, fx.dummyGuard ? &dummyInput : nullptr, nullptr, nullptr};
    // P2-7 (2e): the recovered guard gate, attached to the victim exactly as the pilot flag
    // does in main.cpp. Without this directive the fixture pins the legacy path instead.
    gameplay::native::Rena0PilotGuard pilotGuardPolicy;
    gameplay::native::Rena0GuardRecord pilotGuardRecord(match.fighter(1).moves());
    if (fx.pilotGuard) {
        match.fighter(1).set_pilot_guard(&pilotGuardPolicy);
        // The dummy guards through the port's Guard state, which binds no record, so the pilot
        // hands the predicate the recovered guard row's guard-capable record.
        match.fighter(1).set_pilot_guard_motion(&pilotGuardRecord);
    }
    // P2-7 charge family: the powered shooting branch needs Oyashiro active with an aim hold
    // (fighter.h's shoot_gate_powered). The aim hold is armed here; the activation itself is a
    // real SPECIAL press the fixture scripts (fighter.cpp:843).
    if (fx.hyperOyashiro) {
        match.fighter(0).set_hyper_gauge(1.0f);
        match.fighter(0).set_hypermode(gameplay::Hypermode::Oyashiro);
        match.cycle_aim_selection(0, true);
    }
    int startup = 0;
    while ((!match.fighter(0).actionable() || !match.fighter(1).actionable()) && startup < 512) {
        input::compute_edges(actor);
        match.step(inputs, gameplay::FixedStep::seconds);
        ++startup;
    }
    if (startup == 0 || startup >= 512) { error = "startup did not settle"; return false; }
    const glm::vec3 dummyOrigin = match.fighter(1).position();

    std::map<long long, std::vector<const Expectation*>> byTick;
    for (const auto& e : fx.expects) byTick[e.tick].push_back(&e);

    std::printf("  %-44s combo=%d/%d startup=%d expects=%zu\n", fx.name.c_str(), fx.character,
                fx.weapon, startup, fx.expects.size());
    uint32_t mask = 0;
    long long sampled = 0;
    glm::vec3 previous = match.fighter(0).position();
    float previousYaw = match.fighter(0).facing_yaw();
    for (long long tick = 0; tick <= fx.maxTick; ++tick) {
        if (const auto it = fx.inputs.find(tick); it != fx.inputs.end()) mask = it->second;
        for (int action = 0; action < input::ActionCount; ++action)
            actor.down[action] = (mask & (1u << action)) != 0;
        if (fx.placeOnActive && match.fighter(0).melee_in_active())
            test::Combo::placeAtAttack(match.fighter(0), match.fighter(1));
        input::compute_edges(actor);
        const glm::vec3 before = previous;
        const float beforeYaw = previousYaw;
        const long long guardedBefore = pilotGuardPolicy.guarded;
        const gameplay::MatchFrame frame = match.step(inputs, gameplay::FixedStep::seconds);
        ++sampled;
        // V3's guarded-contact case promises no stun as well as no damage. HP alone cannot
        // detect a zero-damage take_damage call that still switches the victim into Hit.
        if (fx.pilotGuard && pilotGuardPolicy.guarded > guardedBefore &&
            match.fighter(1).state() != gameplay::FighterState::Guard) {
            error = "tick " + std::to_string(tick) +
                    ": recovered guarded contact did not retain Guard (no-stun contract)";
            return false;
        }
        for (long long place : fx.placeTicks)
            if (place == tick) test::Combo::placeAtAttack(match.fighter(0), match.fighter(1));
        previous = match.fighter(0).position();
        previousYaw = match.fighter(0).facing_yaw();
        const bool dummyStatic = match.fighter(1).position() == dummyOrigin;
        for (long long traced : fx.traceTicks)
            if (traced == tick) {
                const gameplay::Fighter& a0 = match.fighter(0);
                const gameplay::Fighter& d1 = match.fighter(1);
                std::printf("    trace tick=%lld state=%d set=%d row=%d active=%d recov=%d hit=%d victim=%d "
                            "swing_hits=%d phase=%d elapsed=%d x=%.3f y=%.3f z=%.3f hp=%d alive=%d pko=%d ko=%d "
                            "respawn=%d credit0=%d credit1=%d overkill0=%d balloon1=%.1f gauge=%d tier=%d "
                            "main=%d yhold=%.4f rhold=%.4f round_over=%d round_end=%d "
                            "hyper=%d hyperwire=%d aimhold=%d shotrow=%d bullet=%d live=%d\n",
                            tick, (int)a0.state(), a0.anim_set_index(), a0.attack_move_id(),
                            a0.melee_in_active() ? 1 : 0, a0.melee_in_recovery() ? 1 : 0,
                            frame.meleeHit[0] ? 1 : 0, frame.meleeVictim[0], a0.swing_hit_count(),
                            a0.move_phase(), a0.phase_elapsed(), (double)a0.position().x,
                            (double)a0.position().y, (double)a0.position().z, d1.hp(),
                            d1.is_alive() ? 1 : 0,
                            d1.pending_ko() ? 1 : 0, match.economy().koAt(1) >= 0.0 ? 1 : 0,
                            frame.respawned[1] ? 1 : 0, frame.koCredits[0], frame.koCredits[1],
                            frame.overkillHits[0], (double)match.economy().balloon(1),
                            a0.charge_gauge(), (int)a0.charge_tier(), a0.main_whole(),
                            (double)a0.yellow_hold_sec(), (double)a0.red_hold_sec(),
                            match.economy().roundOver() ? 1 : 0, (int)match.economy().roundEnd(),
                            a0.hyper_active() ? 1 : 0, gameplay::hypermode_wire_value(a0.hypermode()),
                            match.aim_holds(0) ? 1 : 0, a0.shot_move_id(),
                            newest_shot_row(match), live_p1_shots(match));
            }
        if (const auto it = byTick.find(tick); it != byTick.end()) {
            for (const Expectation* e : it->second) {
                const std::string problem =
                    evalExpectation(match, combo.moves, frame, dummyStatic, *e, before, beforeYaw);
                if (!problem.empty()) {
                    error = "line " + std::to_string(e->line) + ": tick " + std::to_string(tick) + " " + problem;
                    return false;
                }
            }
        }
    }
    // Sampling identity: one step per tick index, no catch-up and no interpolation.
    // A future refactor that steps differently must fail here rather than age the
    // fixture silently.
    if (sampled != fx.maxTick + 1) {
        error = "sampled " + std::to_string(sampled) + " updates for ticks 0.." +
                std::to_string(fx.maxTick) + "; the fixture domain is one step per tick";
        return false;
    }
    if (fx.pilotGuard && pilotGuardPolicy.guarded == 0) {
        error = "pilot guard fixture never exercised a recovered guarded contact";
        return false;
    }
    std::printf("  %-44s sampled=%lld updates\n", fx.name.c_str(), sampled);
    if (fx.pilotGuard)
        std::printf("    guard gate asked=%lld guarded=%lld no-record=%lld not-guard-capable=%lld "
                    "unblockable=%lld outside-angle=%lld\n",
                    pilotGuardPolicy.calls, pilotGuardPolicy.guarded, pilotGuardPolicy.no_record,
                    pilotGuardPolicy.not_guard_capable, pilotGuardPolicy.unblockable,
                    pilotGuardPolicy.outside_angle);
    return true;
}
}  // namespace

int main(int argc, char** argv) {
    const std::string dir = argc > 1 ? argv[1] : "tests/fixtures/rena0";
    // Scratch campaigns copy the required MANIFEST.txt alongside the fixtures; an unrelated
    // text file must never rescue a missing acceptance manifest.
    if (test::gameInstall().empty()) {
        std::puts("SKIP: no game install reachable; F1-3 fixtures need the real Rena+0 data (not a pass)");
        return 77;
    }
    try {
        std::vector<std::string> paths;
        for (const auto& entry : std::filesystem::directory_iterator(dir))
            if (entry.path().extension() == ".fixture") paths.push_back(entry.path().string());
        std::sort(paths.begin(), paths.end());
        if (paths.empty()) throw std::runtime_error("no .fixture files under " + dir);
        std::vector<Fixture> fixtures;
        for (const auto& path : paths) fixtures.push_back(parseFixture(path));

        // Fail-closed acceptance set: the manifest names the fixtures, cases and acceptance
        // fields that must exist and be asserted. A missing fixture, a case with no fixture,
        // or an acceptance field nobody asserts is a failure here rather than a smaller
        // denominator later.
        const std::string manifestPath = dir + "/MANIFEST.txt";
        std::ifstream manifest(manifestPath);
        if (!manifest) throw std::runtime_error("missing acceptance manifest " + manifestPath);
        std::map<std::string, const Fixture*> byName;
        for (const auto& fx : fixtures) byName[fx.name] = &fx;
        int caseCount = 0, fieldCount = 0, unsupportedCount = 0, extras = 0;
        std::set<std::string> referenced;
        std::set<std::pair<std::string, std::string>> declaredFields;
        std::set<std::pair<std::string, std::string>> declaredCases;
        std::string line;
        int lineNo = 0;
        while (std::getline(manifest, line)) {
            ++lineNo;
            if (const size_t hash = line.find('#'); hash != std::string::npos) line.erase(hash);
            std::istringstream ls(line);
            std::string directive, a, b;
            if (!(ls >> directive)) continue;
            if (directive == "case" || directive == "field") {
                if (!(ls >> a >> b))
                    throw std::runtime_error(manifestPath + ":" + std::to_string(lineNo) +
                                             ": " + directive + " needs two arguments");
                const auto it = byName.find(b);
                if (it == byName.end())
                    throw std::runtime_error(manifestPath + ":" + std::to_string(lineNo) +
                                             ": required fixture '" + b + "' is missing");
                referenced.insert(b);
                if (directive == "case") {
                    ++caseCount;
                    if (!declaredCases.emplace(a, b).second)
                        throw std::runtime_error(manifestPath + ": duplicate case/fixture pair '" +
                                                 a + "' / '" + b + "'");
                } else {
                    ++fieldCount;
                    if (!declaredFields.emplace(a, b).second)
                        throw std::runtime_error(manifestPath + ": duplicate field/fixture pair");
                    if (it->second->assertedFields.count(a) == 0)
                        throw std::runtime_error(manifestPath + ":" + std::to_string(lineNo) +
                                                 ": '" + b + "' does not assert field '" + a + "'");
                }
            } else if (directive == "unsupported") {
                ++unsupportedCount;
            } else {
                throw std::runtime_error(manifestPath + ":" + std::to_string(lineNo) +
                                         ": unknown directive '" + directive + "'");
            }
        }
        for (const auto& fx : fixtures)
            if (referenced.count(fx.name) == 0) ++extras;
        if (caseCount == 0 || fieldCount == 0)
            throw std::runtime_error(manifestPath + ": no cases or fields declared");
        for (const auto& required : kRequiredCases)
            if (declaredCases.count({required.first, required.second}) == 0)
                throw std::runtime_error(std::string("the manifest no longer declares the required ") +
                                         "case/fixture pair '" + required.first + "' / '" +
                                         required.second + "'");
        for (const auto& required : kRequiredFields)
            if (declaredFields.count({required.first, required.second}) == 0)
                throw std::runtime_error(std::string("the manifest no longer declares the acceptance ") +
                                         "field '" + required.first + "' for fixture '" +
                                         required.second + "'");

        int failed = 0;
        for (const auto& fx : fixtures) {
            std::string error;
            if (runFixture(fx, error)) {
                std::printf("  %-44s PASS\n", fx.name.c_str());
            } else {
                std::fprintf(stderr, "  %-44s FAIL: %s\n", fx.name.c_str(), error.c_str());
                ++failed;
            }
        }
        if (failed) {
            std::fprintf(stderr, "RENA0_FIXTURES: FAIL (%d of %zu)\n", failed, fixtures.size());
            return 1;
        }
    std::printf("RENA0_FIXTURES: PASS (%zu fixtures, %d Hz, %d case rows, %d acceptance fields, "
                    "%d unsupported declared, %d unreferenced extras, skips=0)\n",
                    fixtures.size(), gameplay::FixedStep::tickRate, caseCount, fieldCount,
                    unsupportedCount, extras);
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "FAIL: %s\n", error.what());
        return 1;
    }
}
