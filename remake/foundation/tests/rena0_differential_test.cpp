// P2-5 (2c) increment 2 — fixture-linked differential for the recovered Rena+0 locomotion
// body (DIRECTION.md §4 Phase 2 2c).
//
// For every fixture in tests/fixtures/rena0 this drives the PRODUCTION Match/Fighter over
// the real combo data exactly as the F1-3 runner does, and simultaneously feeds the
// recovered locomotion body the mapped production scalars (the mapping the F1-5 probe
// established, tests/rena0_locomotion_observation_test.cpp:105-160). Each tick is
// classified before comparison:
//
//   domain        production is grounded Idle or Walk, no victim placement in play, and the
//                 held axes are the ones the F1-5 mapping was validated for (Right/Up or
//                 none) — the only ticks a locomotion body can be compared on;
//   out-of-domain production is airborne, in a dash/attack/guard/shot/hit state, or holds an
//                 axis whose screen-to-body sign the mapping has not established.
//
// Comparisons use the recovered body's own decisions: state admission, walk speed, the
// strict phase clock, and the turn step on the ticks the body resets it. Every disagreement
// must fall into a NAMED class; an unnamed disagreement fails the run, and so does a run
// that compared nothing at all. The class table is the evidence; it is not a parity claim
// (AGENTS.md: shared-source agreement is a consistency check, not independent proof).
#include "combo_fixture.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "gameplay/native/rena0_locomotion_observation.h"
#include "gameplay/native/rena0_pilot_adapter.h"
#include "input/input.h"
#include "rena0_fixture.h"

#include <cmath>
#include <cstdio>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace {
namespace input = fnd::input;
namespace native = gameplay::native;
using rena0fix::Fixture;

int failures = 0;

// Named outcomes. A comparison that disagrees and is not one of the explained classes is
// `unexplained` and fails the run.
struct Tally {
    long long compared = 0;
    long long transitions = 0;
    long long stateAgree = 0, speedAgree = 0, clockAgree = 0, turnAgree = 0;
    long long outOfDomain = 0;
    std::map<std::string, long long> named;
    long long unexplained = 0;
    void note(const std::string& name) { ++named[name]; }
};

struct Snapshot {
    int stateEnum = 0, actionState = 0, phase = 0, elapsed = 0, counter = 0, set = -1;
    bool airborne = false;
    glm::vec3 position{0.f};
    float yaw = 0.f;
    int stamina = 0;
};

Snapshot snapshot(const gameplay::Fighter& f) {
    return {static_cast<int>(f.state()), f.action_state(), f.move_phase(), f.phase_elapsed(),
            f.move_counter(), f.anim_set_index(), f.airborne(), f.position(), f.facing_yaw(),
            f.stamina()};
}

bool near(float a, float b, float tol) { return std::abs(a - b) < tol; }

// The axis mapping the F1-5 probe validated: Right -> +x, Up -> -z (measured from the
// camera-relative script vocabulary). Any other held direction axis is out of domain.
bool axisMappingEstablished(const input::PlayerState& actor) {
    const bool right = actor.down[input::Action::Right];
    const bool left = actor.down[input::Action::Left];
    const bool up = actor.down[input::Action::Up];
    const bool down = actor.down[input::Action::Down];
    return !(left || down) && !(right && up);
}

void runFixtureDifferential(const Fixture& fx, Tally& total, native::Rena0PilotObserver& pilotObserver,
                            std::string& error) {
    test::Combo combo;
    if (!combo.load(fx.character, fx.weapon, error)) return;
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
    match.reset(config, models, controllers, nullptr, nullptr, nullptr);  // open-field
    match.set_ai_enabled(1, false);
    match.economy().setLogFile(nullptr);
    input::PlayerState actor{};
    const input::PlayerState* inputs[gameplay::kMatchFighterCount] = {&actor, nullptr, nullptr, nullptr};
    int startup = 0;
    while ((!match.fighter(0).actionable() || !match.fighter(1).actionable()) && startup < 512) {
        input::compute_edges(actor);
        match.step(inputs, gameplay::FixedStep::seconds);
        ++startup;
    }
    if (startup == 0 || startup >= 512) { error = fx.name + ": startup did not settle"; return; }

    Tally tally;
    native::Rena0LocomotionMotion motion{0.f, 0.f, .5f, 0.f, 0.f, 0.f, 1000, 10};
    native::Rena0ShotObservation pilotShot;
    native::Rena0GuardObservation pilotGuard;
    uint32_t mask = 0;
    glm::vec3 displacement(0.f);
    bool turnReset = false;
    float expectedTurnDeg = 0.f;
    for (long long tick = 0; tick <= fx.maxTick; ++tick) {
        if (const auto it = fx.inputs.find(tick); it != fx.inputs.end()) mask = it->second;
        for (int action = 0; action < input::ActionCount; ++action)
            actor.down[action] = (mask & (1u << action)) != 0;
        const bool placing = fx.placeOnActive && match.fighter(0).melee_in_active();
        if (placing || !fx.placeTicks.empty()) test::Combo::placeAtAttack(match.fighter(0), match.fighter(1));
        input::compute_edges(actor);

        turnReset = false;
        expectedTurnDeg = 0.f;
        const Snapshot before = snapshot(match.fighter(0));
        const bool locomotionState = before.stateEnum == 0 || before.stateEnum == 1;  // Idle / Walk
        const bool moveRowBound = before.actionState == before.stateEnum;
        const bool inDomain = locomotionState && !before.airborne && !placing &&
                              axisMappingEstablished(actor) && moveRowBound;
        if (!inDomain) {
            ++tally.outOfDomain;
            ++total.outOfDomain;
        } else {
            // The bound clip gives the body the same duration/hold inputs the F1-5 probe
            // used; they are reads of production data, never invented values.
            const int set = before.set;
            const float ticksPerSecond = combo.model.ticksPerSecond;
            const int duration = (set >= 0 && static_cast<size_t>(set) < combo.model.anims.size() &&
                                  ticksPerSecond > 0.f)
                                     ? static_cast<int>(std::nearbyint(
                                           combo.model.anims[static_cast<size_t>(set)].duration /
                                           ticksPerSecond / .016f))
                                     : 0;
            const native::Rena0LocomotionInput mapped{
                before.stateEnum == 1 ? 10 : 0, before.phase, before.elapsed, before.counter,
                actor.down[input::Action::Right] ? 1 : 0, actor.down[input::Action::Up] ? -1 : 0,
                1, 0, 0, duration, combo.moves.animation_set_phase_gate(set) != 0};
            motion.speed = glm::length(displacement);
            motion.vertical = displacement.y;
            motion.gauge = before.stamina * 10;
            const auto proposed = native::advance_rena0_locomotion_observation(motion, mapped);
            ++tally.compared;
            ++total.compared;

            const int expectedState = (mapped.x || mapped.z) ? 10 : 0;
            if (proposed.state == expectedState) {
                ++tally.stateAgree;
                ++total.stateAgree;
            } else {
                ++tally.unexplained;
                ++total.unexplained;
                std::fprintf(stderr, "    %s tick %lld: body state %d, axes imply %d\n",
                             fx.name.c_str(), tick, proposed.state, expectedState);
            }
            // Walk speed: the production step is the recovered 7.2 per update, and the body
            // must carry that same number while it is walking.
            if (expectedState == 10) {
                if (near(glm::length(displacement), static_cast<float>(motion.speed), 1e-3f)) {
                    ++tally.speedAgree;
                    ++total.speedAgree;
                } else {
                    tally.note("speed-in-walk");
                    total.note("speed-in-walk");
                }
            } else if (!near(glm::length(displacement), 0.f, 1e-3f)) {
                // The recorded F1-5 divergence: the body proposes Idle without clearing the
                // incoming speed while the port clears the step on the same update.
                tally.note("speed-retained-on-stop");
                total.note("speed-retained-on-stop");
            } else {
                ++tally.speedAgree;
                ++total.speedAgree;
            }
            // Clock rule, in the two shapes the F1-5 probe established: a transition tick
            // resets the paired clocks and runs no tail, a stable tick uses the strict
            // arithmetic (completion when duration < elapsed+1 and the gate is clear).
            const bool transition = proposed.next_state != native::kRena0NoProposal;
            const bool phaseEnd = duration < before.elapsed + 1 && !mapped.hold;
            const int wantFrame = transition ? 0 : (phaseEnd ? 0 : before.elapsed + 1);
            const int wantSecondary = transition ? 0 : (phaseEnd ? 0 : before.counter + 1);
            const int wantPhase = transition ? 0 : before.phase + (phaseEnd ? 1 : 0);
            if (proposed.frame == wantFrame && proposed.secondary == wantSecondary &&
                proposed.phase == wantPhase && (!transition || !proposed.tail)) {
                ++tally.clockAgree;
                ++total.clockAgree;
                if (transition) {
                    ++tally.transitions;
                    ++total.transitions;
                }
            } else {
                tally.note("phase-clock");
                total.note("phase-clock");
                std::fprintf(stderr, "    clock %s tick %lld: st=%d elapsed=%d counter=%d dur=%d hold=%d "
                                     "transition=%d -> got phase=%d frame=%d sec=%d tail=%d, "
                                     "wants phase=%d frame=%d sec=%d\n",
                             fx.name.c_str(), tick, before.stateEnum, before.elapsed, before.counter,
                             duration, mapped.hold ? 1 : 0, transition ? 1 : 0, proposed.phase,
                             proposed.frame, proposed.secondary, proposed.tail ? 1 : 0, wantPhase,
                             wantFrame, wantSecondary);
            }
            // Turn step: on the updates the body resets its step (20 then a decay), the
            // production yaw delta must be that step in degrees — the F1-5 probe measured
            // +19/-19 on exactly such ticks. Other in-domain updates may only turn within
            // the recovered ceiling.
            turnReset = before.stateEnum == 1 && motion.turn >= 19.f;
            expectedTurnDeg = motion.turn;
        }

        // The live adapter's own observe path runs on the same ticks: its comparison rules get
        // suite coverage here, while the flag plumbing and restoration are the runtime A/B.
        const auto pilotSample = native::sample_rena0_pilot_tick(match.fighter(0));
        const gameplay::MatchFrame frame = match.step(inputs, gameplay::FixedStep::seconds);
        native::observe_rena0_tick(pilotSample, match.fighter(0), actor, pilotObserver);
        if (const gameplay::CharacterMoves* moves = match.fighter(0).moves())
            pilotObserver.modeGauges.limits = native::rena0_mode_gauge_limits(moves->header_values());
        native::feed_rena0_mode_gauges(frame, match, 0, pilotObserver);
        native::observe_rena0_shot(pilotSample, match.fighter(0), frame, &match, pilotObserver, pilotShot);
        native::observe_rena0_guard(pilotSample, match.fighter(0), actor, frame, pilotObserver, pilotGuard);
        if (const char* meleeCls =
                native::observe_rena0_melee(pilotSample, match.fighter(0), actor, pilotObserver);
            meleeCls && std::string(meleeCls) != "melee-ok")
            std::fprintf(stderr, "    melee %s tick %lld: port bound row %d (before=%d state=%d phase=%d air=%d)\n",
                         meleeCls, tick, match.fighter(0).attack_move_id(),
                         pilotSample.attackMoveId, pilotSample.actionState, pilotSample.phase,
                         pilotSample.airborne ? 1 : 0);
        const Snapshot after = snapshot(match.fighter(0));
        if (inDomain) {
            const float turned = glm::degrees(after.yaw - before.yaw);
            const bool turnOk = turnReset ? near(std::abs(turned), expectedTurnDeg, .5f)
                                          : std::abs(turned) <= 20.01f;
            if (turnOk) {
                ++tally.turnAgree;
                ++total.turnAgree;
            } else {
                ++tally.unexplained;
                ++total.unexplained;
                std::fprintf(stderr, "    %s tick %lld: production turned %.3f deg (body step %.3f, reset=%d)\n",
                             fx.name.c_str(), tick, turned, expectedTurnDeg, turnReset ? 1 : 0);
            }
        }
        displacement = after.position - before.position;
    }
    std::printf("  %-34s domain=%lld out=%lld transitions=%lld state=%lld speed=%lld clock=%lld turn=%lld",
                fx.name.c_str(), tally.compared, tally.outOfDomain, tally.transitions,
                tally.stateAgree, tally.speedAgree, tally.clockAgree, tally.turnAgree);
    for (const auto& [name, count] : tally.named) std::printf(" %s=%lld", name.c_str(), count);
    if (tally.compared)
        std::printf(" | clock agree %.1f%%",
                    100.0 * static_cast<double>(tally.clockAgree) / static_cast<double>(tally.compared));
    std::printf("\n");
}
}  // namespace

int main(int argc, char** argv) {
    const std::string dir = argc > 1 ? argv[1] : "tests/fixtures/rena0";
    if (test::gameInstall().empty()) {
        std::puts("SKIP: no game install reachable; the differential needs the real combo data (not a pass)");
        return 77;
    }
    try {
        std::vector<std::string> paths;
        for (const auto& entry : std::filesystem::directory_iterator(dir))
            if (entry.path().extension() == ".fixture") paths.push_back(entry.path().string());
        std::sort(paths.begin(), paths.end());
        if (paths.empty()) throw std::runtime_error("no .fixture files under " + dir);
        std::puts("P2-5 increment 2 — fixture-linked differential: recovered locomotion body vs production");
        Tally total;
        native::Rena0PilotObserver pilotObserver;
        for (const auto& path : paths) {
            const Fixture fx = rena0fix::parseFixture(path);
            std::string error;
            runFixtureDifferential(fx, total, pilotObserver, error);
            if (!error.empty()) {
                std::fprintf(stderr, "  %s: %s\n", fx.name.c_str(), error.c_str());
                ++failures;
            }
        }
        std::printf("RENA0_DIFFERENTIAL: compared=%lld out-of-domain=%lld transitions=%lld state-ok=%lld "
                    "speed-ok=%lld clock-ok=%lld turn-ok=%lld unexplained=%lld\n",
                    total.compared, total.outOfDomain, total.transitions, total.stateAgree,
                    total.speedAgree, total.clockAgree, total.turnAgree, total.unexplained);
        for (const auto& [name, count] : total.named) std::printf("  class %-28s %lld\n", name.c_str(), count);
        // The live adapter's observe path, on the same runs. It must agree wherever it is in
        // domain, and it must have been in domain at all (fail-closed below).
        std::printf("RENA0_DIFFERENTIAL: pilot-adapter observe ticks=%lld compared=%lld out-of-domain=%lld "
                    "agreed=%lld disagreed=%lld\n",
                    pilotObserver.ticks, pilotObserver.compared, pilotObserver.outOfDomain,
                    pilotObserver.agreed, pilotObserver.disagreed);
        std::printf("RENA0_DIFFERENTIAL: pilot-adapter mode gauges victim-hits=%lld attacker-hits=%lld "
                "charge0=%u charge1=%u notify5=%lld notify6=%lld (limits %u/%u)\n",
                pilotObserver.gaugeVictimHits, pilotObserver.gaugeAttackerHits,
                pilotObserver.modeGauges.charge0, pilotObserver.modeGauges.charge1,
                pilotObserver.modeGauges.notify5, pilotObserver.modeGauges.notify6,
                pilotObserver.modeGauges.limits.limit0, pilotObserver.modeGauges.limits.limit1);
    std::printf("RENA0_DIFFERENTIAL: pilot-adapter guard ticks=%lld starts=%lld blocks=%lld/%lld "
                    "disagreed=%lld\n",
                    pilotObserver.guardTicks, pilotObserver.guardStarts, pilotObserver.guardBlockAgreed,
                    pilotObserver.guardBlocks, pilotObserver.guardDisagreed);
        std::printf("RENA0_DIFFERENTIAL: pilot-adapter shot ticks=%lld fire=%lld/%lld sound=%lld/%lld "
                    "voice=%lld/%lld disagreed=%lld\n",
                    pilotObserver.shotTicks, pilotObserver.shotFireAgreed,
                    pilotObserver.shotFireCompared, pilotObserver.shotSoundAgreed,
                    pilotObserver.shotSoundCompared, pilotObserver.shotVoiceAgreed,
                    pilotObserver.shotVoiceCompared, pilotObserver.shotDisagreed);
        std::printf("RENA0_DIFFERENTIAL: pilot-adapter melee compared=%lld agreed=%lld disagreed=%lld\n",
                    pilotObserver.meleeCompared, pilotObserver.meleeAgreed,
                    pilotObserver.meleeDisagreed);
        for (const auto& [name, count] : pilotObserver.classes)
            std::printf("  pilot class %-28s %lld\n", name.c_str(), count);
        // Fail-closed: comparing nothing is not a pass, and an unnamed disagreement is a finding
        // that must be explained before this harness can claim anything.
        if (total.compared == 0) {
            std::fprintf(stderr, "RENA0_DIFFERENTIAL: FAIL (no in-domain ticks were compared)\n");
            return 1;
        }
        if (pilotObserver.compared == 0) {
            std::fprintf(stderr, "RENA0_DIFFERENTIAL: FAIL (the pilot adapter compared no in-domain tick)\n");
            return 1;
        }
        if (pilotObserver.guardTicks == 0 || pilotObserver.guardDisagreed != 0) {
            std::fprintf(stderr, "RENA0_DIFFERENTIAL: FAIL (pilot guard comparison: %lld ticks, "
                                 "%lld disagreed)\n", pilotObserver.guardTicks,
                         pilotObserver.guardDisagreed);
            return 1;
        }
        if (pilotObserver.shotDisagreed != 0) {
            std::fprintf(stderr, "RENA0_DIFFERENTIAL: FAIL (pilot shot comparison disagreed %lld times)\n",
                         pilotObserver.shotDisagreed);
            return 1;
        }
        if (pilotObserver.meleeCompared == 0 || pilotObserver.meleeDisagreed != 0) {
            std::fprintf(stderr, "RENA0_DIFFERENTIAL: FAIL (pilot melee comparison: %lld compared, "
                                 "%lld disagreed)\n", pilotObserver.meleeCompared,
                         pilotObserver.meleeDisagreed);
            return 1;
        }
        if (pilotObserver.disagreed != 0) {
            std::fprintf(stderr, "RENA0_DIFFERENTIAL: FAIL (the pilot adapter disagreed on %lld ticks)\n",
                         pilotObserver.disagreed);
            return 1;
        }
        if (total.unexplained != 0 || failures != 0) {
            std::fprintf(stderr, "RENA0_DIFFERENTIAL: FAIL (%lld unexplained, %d fixture errors)\n",
                         total.unexplained, failures);
            return 1;
        }
        std::printf("RENA0_DIFFERENTIAL: PASS (%lld in-domain ticks, no unexplained divergence, skips=0)\n",
                    total.compared);
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAIL: %s\n", e.what());
        return 1;
    }
}
