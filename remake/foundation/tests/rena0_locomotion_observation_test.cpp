#include "combo_fixture.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "gameplay/native/rena0_locomotion_observation.h"

#include <cmath>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>

namespace {
namespace input = fnd::input;
namespace native = gameplay::native;
using gameplay::FighterState;

void require(bool ok, const char* message) {
    if (!ok) throw std::runtime_error(message);
}
bool near(float a, float b) { return std::abs(a - b) < 1e-4f; }
bool walkingSpeedMatches(float speed) { return near(speed, 7.19999981f); }

struct Snapshot {
    int state, phase, elapsed, counter, set, stamina, hp;
    glm::vec3 position;
    float yaw;
    bool fallback;
    bool operator==(const Snapshot& b) const {
        return std::tie(state, phase, elapsed, counter, set, stamina, hp, position.x,
                        position.y, position.z, yaw, fallback) ==
               std::tie(b.state, b.phase, b.elapsed, b.counter, b.set, b.stamina, b.hp,
                        b.position.x, b.position.y, b.position.z, b.yaw, b.fallback);
    }
};
Snapshot snapshot(const gameplay::Fighter& f) {
    return {f.action_state(), f.move_phase(), f.phase_elapsed(), f.move_counter(),
            f.anim_set_index(), f.stamina(), f.hp(), f.position(), f.facing_yaw(),
            f.anim_fallback()};
}
using Trace = std::vector<Snapshot>;
using Observation = std::tuple<int, int, int, int, int, int, bool,
                               float, float, float, float, float, float, int, int>;
struct Run {
    Trace legacy;
    std::vector<Observation> proposals;
};

Run run(test::Combo& combo, bool observe, bool mutate) {
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
    // No stage collision service: this case is explicitly open-field, not a
    // modification of the historical standalone capture defaults.
    match.reset(config, models, controllers, nullptr, nullptr, nullptr);
    // COM off for the opponent only. A live human slot keeps the AI flag at its
    // reset value; the flag publishes the COM's lateral decision word and no
    // locomotion branch reads it (match.cpp:209-213).
    match.set_ai_enabled(1, false);
    match.economy().setLogFile(nullptr);  // keep economy lines out of the test log
    input::PlayerState actor{};
    // A COM-off slot is fed no input at all (match.h:255-256), which is the shape
    // the neutral dummy has in a live match.
    const fnd::input::PlayerState* inputs[gameplay::kMatchFighterCount] =
        {&actor, nullptr, nullptr, nullptr};
    require(match.fighter(0).state() == FighterState::BattleStart,
            "reset must enter BattleStart, never force Idle");
    // Neutrality is pinned from the reset, so a startup-time move cannot hide.
    const auto dummySpawn = match.fighter(1).position();
    const float dummyYaw = match.fighter(1).facing_yaw();
    int startup = 0;
    while ((!match.fighter(0).actionable() || !match.fighter(1).actionable()) && startup < 512) {
        input::compute_edges(actor);
        match.step(inputs, gameplay::FixedStep::seconds);
        ++startup;
    }
    require(startup > 0 && startup < 512, "normal startup failed");
    for (int i = 0; i < 2; ++i) {
        const auto& f = match.fighter(i);
        require(f.state() == FighterState::Idle && !f.airborne(), "startup must settle grounded Idle");
        require(f.moves() == &combo.moves && f.weapon() == &combo.weapon && f.model() == &combo.model,
                "both participants must retain real equipped Rena+0 data");
    }
    std::printf("case observe=%d startup=%d cadence=%d dt=%.9f\n",
                observe, startup, gameplay::FixedStep::tickRate, gameplay::FixedStep::seconds);
    const auto dummyPosition = match.fighter(1).position();
    // Explicit observer-only seeds, not invented Fighter fields. See the draft
    // contract for unresolved +60/+64/+874/+878 and resource correspondence.
    native::Rena0LocomotionMotion motion{0.f, 0.f, .5f, 0.f, 0.f, 0.f, 1000, 10};
    Run trace;
    glm::vec3 displacement(0.f);
    int observedWalks = 0;
    for (int tick = 0; tick < 32; ++tick) {
        actor.down[input::Action::Right] = tick >= 4 && tick < 16;
        actor.down[input::Action::Up] = tick >= 16 && tick < 28;
        input::compute_edges(actor);
        const auto before = snapshot(match.fighter(0));
        const auto& fighter = match.fighter(0);
        if (observe) {
            const int set = fighter.anim_set_index();
            require(set >= 0 && static_cast<size_t>(set) < combo.model.anims.size(), "missing bound rig set");
            const auto& clip = combo.model.anims[static_cast<size_t>(set)];
            require(combo.model.ticksPerSecond > 0.f, "invalid rig clock");
            const int duration = static_cast<int>(std::nearbyint(
                clip.duration / combo.model.ticksPerSecond / .016f));
            // Stop and slow are explicit no-stop/normal-refill fixture assumptions.
            // Stamina*10 and move_counter are diagnostic proxies, not proven actor
            // resource / +AE08 mappings. Legacy clocks are read, never overwritten.
            native::Rena0LocomotionInput mapped{before.state, before.phase, before.elapsed, before.counter,
                actor.down[input::Action::Right] ? 1 : 0,
                actor.down[input::Action::Up] ? -1 : 0, !fighter.airborne(),
                0, 0, duration, combo.moves.animation_set_phase_gate(set) != 0};
            motion.speed = glm::length(displacement);
            motion.vertical = displacement.y;
            motion.gauge = before.stamina * 10;
            const auto proposed = native::advance_rena0_locomotion_observation(motion, mapped);
            trace.proposals.emplace_back(proposed.state, proposed.phase, proposed.frame,
                proposed.secondary, proposed.next_state, proposed.next_phase, proposed.tail,
                motion.speed, motion.vertical, motion.gravity, motion.movement, motion.offset,
                motion.turn, motion.gauge, motion.direction);
            const bool moving = mapped.x || mapped.z;
            const int expectedState = moving ? 10 : 0;
            require(proposed.state == expectedState, "source idle/walk admission mismatch");
            require(motion.gauge == 1000, "source saturated refill mismatch");
            require(near(motion.vertical, 0.f), "source grounded vertical mismatch");
            if (expectedState != before.state) {
                require(!proposed.tail && proposed.frame == 0 && proposed.secondary == 0 &&
                        proposed.phase == 0 && proposed.next_state == expectedState,
                        "source transition must reset paired clocks without tail");
            } else {
                require(proposed.tail, "source stable locomotion must execute tail");
                const bool phaseEnd = duration < before.elapsed + 1 && !mapped.hold;
                require(proposed.frame == (phaseEnd ? 0 : before.elapsed + 1) &&
                        proposed.secondary == (phaseEnd ? 0 : before.counter + 1) &&
                        proposed.phase == before.phase + (phaseEnd ? 1 : 0),
                        "source paired clock/strict phase completion mismatch");
            }
            if (before.state == 0) require(near(motion.speed, 0.f), "source Idle clears speed");
            if (before.state == 10 && moving) {
                ++observedWalks;
                const float checkedSpeed = mutate ? motion.speed + 1.f : motion.speed;
                require(walkingSpeedMatches(checkedSpeed), "source Rena+0 walk speed mismatch (seed detected)");
                if (tick == 5 || tick == 16) require(near(motion.turn, 19.f), "source direction change resets then decays turn");
                if (tick == 5) require(near(motion.offset, -19.f), "source Right steering sign/step mismatch");
                if (tick == 16) require(near(motion.offset, -71.f), "source Up turn must approach zero by 19 degrees");
                require(motion.direction == (mapped.x ? 3 : 0), "source direction category mismatch");
            }
            if (tick == 4 || tick == 5 || tick == 16 || tick == 28)
                std::printf("  tick=%d before=%d proposed=%d speed=%.5f offset=%.5f turn=%.1f phase=%d frame=%d secondary=%d\n",
                            tick, before.state, proposed.state, motion.speed, motion.offset,
                            motion.turn, proposed.phase, proposed.frame, proposed.secondary);
        }
        const auto frame = match.step(inputs, gameplay::FixedStep::seconds);
        const auto after = snapshot(match.fighter(0));
        displacement = after.position - before.position;
        const bool moving = tick >= 4 && tick < 28;
        require(after.state == (moving ? 10 : 0), "production idle/walk/stop transition mismatch");
        // action_state() collapses Guard/Hit/KO/BattleStart/Shoot onto the same 0
        // as Idle, so the stop ticks pin the state enum as well.
        if (!moving) require(match.fighter(0).state() == FighterState::Idle,
                             "production stop ticks must be genuinely Idle, not a collapsed 0");
        require(!match.fighter(0).airborne(), "production unexpectedly airborne");
        require(after.set == combo.moves.first_set_index(moving ? 10 : 0) && !after.fallback,
                "production must bind real move row 0/10 without fallback");
        // 7.2 units per update is the addressed constant (FUN_0043ffc0:167,
        // 0x40e66666) and is cadence-independent; fighter.cpp:968 divides the same
        // recovered walk value by dt, so the step is the source number at any rate.
        require(moving ? near(glm::length(displacement), 7.2f) : near(glm::length(displacement), 0.f),
                "production movement/stop mismatch");
        // The turn is a claim, not log decoration: the direction change resets the
        // step to 20 and decrements before the clamp (fighter.cpp:974-979), and the
        // recovered row stores the same reset (FUN_0043ffc0:121-160).
        if (tick == 4) require(near(after.yaw - before.yaw, glm::radians(19.f)), "production first walk turn must be +19 degrees");
        if (tick == 16) require(near(after.yaw - before.yaw, -glm::radians(19.f)), "production reversal turn must be -19 degrees");
        require(match.fighter(1).position() == dummyPosition &&
                near(match.fighter(1).facing_yaw(), dummyYaw) &&
                match.fighter(1).state() == FighterState::Idle,
                "neutral equipped dummy moved or acted");
        require(match.fighter(1).position() == dummySpawn, "dummy moved during the sequence");
        require(frame.shotsSpawned == 0 && !frame.meleeHit[0] && !frame.meleeHit[1], "unexpected combat event");
        if (tick == 4 || tick == 5 || tick == 16 || tick == 28)
            std::printf("  legacy tick=%d state=%d set=%d displacement=%.5f yaw=%.5f phase=%d frame=%d counter=%d\n",
                        tick, after.state, after.set, glm::length(displacement), after.yaw,
                        after.phase, after.elapsed, after.counter);
        trace.legacy.push_back(after);
        trace.legacy.push_back(snapshot(match.fighter(1)));
    }
    require(!observe || observedWalks == 23, "required walk/turn observations missing");
    return trace;
}

void stoppedWordCase() {
    native::Rena0LocomotionMotion motion{8.f, 3.f, .5f, 12.f, 45.f, 7.f, 345, 3};
    const native::Rena0LocomotionInput mapped{10, 2, 17, 19, 1, 0, 1, 256, 0, 100, true};
    const auto result = native::advance_rena0_locomotion_observation(motion, mapped);
    require(result.state == 10 && result.phase == 2 && result.frame == 17 && result.secondary == 19 &&
            result.next_state == native::kRena0NoProposal &&
            result.next_phase == native::kRena0NoProposal &&
            !result.tail && motion.speed == 8.f && motion.vertical == 3.f && motion.gauge == 345 &&
            motion.offset == 45.f && motion.turn == 7.f,
            "nonzero stop WORD must suppress body, not truncate to byte");
}

// The refill arithmetic (FUN_0043ffc0:87-96): +40 normally, +5 while the +0x7f4
// status is active, clamped at 1000. The in-match observer is saturated at 1000
// by design, so these explicit cases are what actually pin the arithmetic.
void refillCases() {
    const struct {
        std::int32_t gauge, slow, expected;
        const char* name;
    } cases[] = {
        {100, 0, 140, "clear status refills by 40"},
        {100, 1, 105, "slow status refills by 5"},
        {995, 0, 1000, "refill clamps at 1000"},
    };
    for (const auto& c : cases) {
        native::Rena0LocomotionMotion motion{0.f, 0.f, .5f, 0.f, 0.f, 0.f, c.gauge, 10};
        const native::Rena0LocomotionInput mapped{0, 0, 0, 0, 0, 0, 1, 0, c.slow, 100, false};
        native::advance_rena0_locomotion_observation(motion, mapped);
        require(motion.gauge == c.expected, c.name);
    }
}

// Strict phase completion and the +0xade4 gate (FUN_0043ffc0:2439-2447, whose
// transition reset is FUN_00421080 -> FUN_00421100). No production tick in the
// grounded sequence crosses a phase boundary, so this branch is pinned here.
void phaseCompletionCases() {
    {
        native::Rena0LocomotionMotion motion{0.f, 0.f, .5f, 0.f, 0.f, 0.f, 1000, 10};
        const native::Rena0LocomotionInput mapped{10, 2, 5, 7, 1, 0, 1, 0, 0, 3, false};
        const auto result = native::advance_rena0_locomotion_observation(motion, mapped);
        require(result.tail && result.phase == 3 && result.next_phase == 3 &&
                result.frame == 0 && result.secondary == 0,
                "strict completion must bump the phase and reset both clocks");
    }
    {
        native::Rena0LocomotionMotion motion{0.f, 0.f, .5f, 0.f, 0.f, 0.f, 1000, 10};
        const native::Rena0LocomotionInput mapped{10, 2, 5, 7, 1, 0, 1, 0, 0, 3, true};
        const auto result = native::advance_rena0_locomotion_observation(motion, mapped);
        require(result.tail && result.phase == 2 && result.next_phase == native::kRena0NoProposal &&
                result.frame == 6 && result.secondary == 8,
                "gated phase (hold) must not complete past its duration");
    }
    {
        native::Rena0LocomotionMotion motion{0.f, 0.f, .5f, 0.f, 0.f, 0.f, 1000, 10};
        const native::Rena0LocomotionInput mapped{0, 0, 3, 2, 0, 0, 0, 0, 0, 100, false};
        const auto result = native::advance_rena0_locomotion_observation(motion, mapped);
        require(result.state == native::kRena0StateAirborne &&
                result.next_state == native::kRena0StateAirborne && motion.gravity == 0.5f &&
                result.frame == 0 && result.secondary == 0,
                "losing ground must propose the airborne state and gravity");
    }
}
} // namespace

int main(int argc, char** argv) {
    const bool mutate = argc == 2 && std::string(argv[1]) == "--seed-wrong-speed";
    if (argc > 1 && !mutate) return 2;
    try {
        // A data-free checkout skips (ctest SKIP_RETURN_CODE 77, never an F1-5
        // pass). An install that is present but unreadable stays a hard failure,
        // so missing/mismatched combo data cannot hide behind the skip.
        if (test::gameInstall().empty()) {
            std::puts("SKIP: no game install reachable; F1-5 requires the real Rena+0 data (not a pass)");
            return 77;
        }
        test::Combo combo;
        std::string error;
        require(combo.load(0, 0, error), ("required Rena+0 data unreadable: " + error).c_str());
        require(combo.moves.character_index() == 0 && combo.moves.weapon_id() == 1, "wrong combo identity");
        std::printf("Rena+0 data/rena/00.dat item=001 rig=%s sets=%zu open-field observation-only\n",
                    combo.moves.model_name().c_str(), combo.model.anims.size());
        stoppedWordCase();
        refillCases();
        phaseCompletionCases();
        require(!walkingSpeedMatches(8.19999981f), "negative predicate failed to reject wrong walk speed");
        const auto first = run(combo, true, mutate);
        const auto repeat = run(combo, true, false);
        const auto baseline = run(combo, false, false);
        require(first.legacy == repeat.legacy && first.proposals == repeat.proposals,
                "production or recovered proposal repeatability mismatch after reset");
        require(first.legacy == baseline.legacy, "observation changed production gameplay or clocks");
        std::puts("PASS: 32 updates x 3 reset cases; refill/phase-completion/airborne/stop-word cases; "
                  "repeatability/noninterference; wrong-speed sensitivity; skips=0");
        return 0;
    } catch (const std::exception& error) {
        std::fprintf(stderr, "FAIL: %s; a required F1-5 case cannot be skipped or silently passed\n", error.what());
        return 1;
    }
}
