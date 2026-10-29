// P2-7 (2e) slice 1 — the locomotion adapter in OBSERVE mode, behind --native-actions=rena0.
//
// This is the first slice the owner ordered: locomotion behind the flag, with the clock and
// state ownership resolved (PILOT-SEAM §16) and adapter equivalence plus flag-off
// restoration demonstrated before any combat family is added.
//
// Observe mode changes NO decision. Every function reads the fighter through a const
// reference and writes nothing, so a run with the flag must produce the same gameplay as a
// run without it; the flag only adds a per-tick comparison line and a summary. Wiring the
// adapter's proposals into the fighter is slice 2 and needs the owner's approval of this
// slice's evidence first.
//
// The comparison mirrors the offline differential's semantics (tests/rena0_differential_test.cpp):
// the pre-step sample plus the input that was applied give the body its view, and the body's
// proposal is checked against the post-step reality — state row, bound animation set and the
// phase clock. Speed and turn-step equivalence stay with the offline differential (313
// compared ticks), which owns the deeper decision-level comparison; this adapter reports what
// the real runtime can check cheaply and exactly.
#pragma once

#include "gameplay/character_moves.h"
#include "gameplay/animation_period.h"
#include "gameplay/fighter.h"
#include "gameplay/held_axis.h"
#include "gameplay/match.h"
#include "gameplay/native/rena0_mode_gauges.h"
#include "gameplay/native/rena0_ground_shot_observation.h"
#include "gameplay/native/rena0_guard_observation.h"
#include "gameplay/native/rena0_resolver.h"
#include "input/input.h"

#include <cmath>
#include <cstddef>
#include <map>
#include <string>

namespace gameplay::native {

// The pilot flag names one equipped combo, not whichever actor happens to occupy P1.
inline bool is_rena0_pilot_combo(const Fighter& fighter) {
    const CharacterMoves* moves = fighter.moves();
    const WeaponDefinition* weapon = fighter.weapon();
    return moves && weapon && weapon->valid() && moves->character_index() == 0 &&
           moves->weapon_id() == 1 && weapon->id == moves->weapon_id();
}

struct Rena0PilotObserver {
    long long ticks = 0;        // every observed tick
    long long driven = 0;       // ticks the pilot policy answered for the fighter
    long long meleeCompared = 0;   // fresh melee admissions the recovered body was asked about
    long long meleeAgreed = 0;
    long long meleeDisagreed = 0;
    long long shotTicks = 0;       // ticks the recovered shot body was advanced on
    long long shotFireCompared = 0;
    long long shotFireAgreed = 0;
    long long shotSoundCompared = 0;
    long long shotSoundAgreed = 0;
    long long shotVoiceCompared = 0;
    long long shotVoiceAgreed = 0;
    long long shotDisagreed = 0;
    long long shotModelCompared = 0;   // body `model` requests vs the port's per-slot binding
    long long shotModelAgreed = 0;
    long long shotBulletCompared = 0;  // attachment requests vs the spawned projectile
    long long shotBulletAgreed = 0;
    // P2-7 charge family: the pilot fighter's mode gauges, fed from the hits the frame reports.
    // The port has no consumer for them (its gain_gauge feeds the hypermode bar), so this is
    // observation, not a comparison: the counters show the recovered rules running on real hits.
    Rena0ModeGauges modeGauges;
    long long gaugeVictimHits = 0;
    long long gaugeAttackerHits = 0;
    long long guardTicks = 0;      // ticks the recovered guard body was advanced on
    long long guardStarts = 0;
    long long guardBlocks = 0;     // guarded contacts the port reported
    long long guardBlockAgreed = 0;
    long long guardDisagreed = 0;
    long long compared = 0;     // in-domain ticks
    long long outOfDomain = 0;  // ticks with a named reason
    long long agreed = 0;
    long long disagreed = 0;
    std::map<std::string, long long> classes;  // one entry per outcome class
    void note(const char* name) { ++classes[name]; }
};

// The pre-step values the body's view is built from (PILOT-SEAM §14's fields).
struct Rena0PilotSample {
    FighterState state = FighterState::Idle;
    int phase = 0;
    int elapsed = 0;
    int counter = 0;
    int set = -1;
    bool airborne = false;
    bool actionable = false;
    int actionState = 0;    // the port's collapsed action state (the admission's `state`)
    int attackMoveId = -1;  // the melee row bound before this tick, -1 when none
    int shotMoveId = -1;    // the shot row bound before this tick, -1 when none
};

inline Rena0PilotSample sample_rena0_pilot_tick(const Fighter& f) {
    return {f.state(), f.move_phase(), f.phase_elapsed(), f.move_counter(), f.anim_set_index(),
            f.airborne(), f.actionable(), f.action_state(), f.attack_move_id(),
            f.shot_move_id()};
}

// Why a tick did not agree, for the log line: a mismatch must be diagnosable from the run
// itself, not from a debugger.
struct Rena0PilotDetail {
    int beforePhase = 0, afterPhase = 0, wantPhase = 0;
    int beforeElapsed = 0, afterElapsed = 0, wantElapsed = 0;
    int duration = 0;
    bool hold = false;
    bool transition = false;
};

// Compare one tick. Returns the class name for the caller to log; "ok" is an agreeing
// in-domain tick. Never writes to `after`, and only reads `before`/`input`.
inline const char* observe_rena0_tick(const Rena0PilotSample& before, const Fighter& after,
                                      const input::PlayerState& input, Rena0PilotObserver& obs,
                                      Rena0PilotDetail* detail = nullptr) {
    ++obs.ticks;
    const CharacterMoves* moves = after.moves();
    const xm::Model* model = after.model();
    if (!moves || !model) {
        ++obs.outOfDomain;
        obs.note("no-bound-data");
        return "no-bound-data";
    }
    // Domain: the fighter ends the tick grounded in Idle or Walk, and the only held axes are
    // the ones the F1-5 mapping established (Right -> +x, Up -> -z).
    const FighterState state = after.state();
    // State 44 is compared, not skipped: while the landing window is open the fighter IS on
    // row 44, and the binding is checkable against the row itself (V3-42).
    if (state == FighterState::Idle && after.landing_ticks() > 0) {
        const CharacterMove* landing = moves->find(44);
        const int wantSet = landing ? landing->phase_set_index(0) : -1;
        if (wantSet < 0) {
            ++obs.outOfDomain;
            obs.note("landing-row-unbound");
            return "landing-row-unbound";
        }
        ++obs.compared;
        if (after.anim_set_index() != wantSet) {
            ++obs.disagreed;
            obs.note("landing-binding");
            return "landing-binding";
        }
        // Counted like any other agreement, so the totals close (compared == agreed + disagreed
        // + out-of-domain) instead of leaving the landing ticks unaccounted.
        ++obs.agreed;
        obs.note("ok");
        return "ok";
    }
    const bool locomotion = state == FighterState::Idle || state == FighterState::Walk;
    if (!locomotion) {
        ++obs.outOfDomain;
        obs.note("not-a-locomotion-state");
        return "not-a-locomotion-state";
    }
    if (after.airborne()) {
        ++obs.outOfDomain;
        obs.note("airborne-set-unresolved");
        return "airborne-set-unresolved";
    }
    const bool right = input.down[input::Action::Right];
    const bool up = input.down[input::Action::Up];
    if (input.down[input::Action::Left] || input.down[input::Action::Down] || (right && up)) {
        ++obs.outOfDomain;
        obs.note("axis-mapping-unestablished");
        return "axis-mapping-unestablished";
    }
    // The pre-step state must itself be a locomotion entry state; the body has no view for
    // anything else (its own validator rejects it).
    if (before.state != FighterState::Idle && before.state != FighterState::Walk) {
        ++obs.outOfDomain;
        obs.note("entry-state-not-locomotion");
        return "entry-state-not-locomotion";
    }
    const int set = before.set;
    const int duration = (set >= 0 && static_cast<std::size_t>(set) < model->anims.size() &&
                          model->ticksPerSecond > 0.f)
                             ? gameplay::animation_period_frames(*model, set)
                             : 0;
    Rena0ResolverView view;
    view.weaponSlot = 0;  // unused by the locomotion path; the weapon row is P2-6's own check
    view.actionState = static_cast<int>(before.state);
    view.stateEnum = static_cast<int>(before.state);
    view.phase = before.phase;
    view.elapsed = before.elapsed;
    view.counter = before.counter;
    view.grounded = !before.airborne;
    view.actionable = before.actionable;
    view.inputX = right ? 1 : 0;
    view.inputZ = up ? -1 : 0;
    view.duration = duration;
    view.hold = moves->animation_set_phase_gate(set) != 0;
    view.gauge = after.stamina() * 10;  // the seam's diagnostic proxy, not compared here
    ++obs.compared;

    const Rena0Resolution r = resolve_rena0_locomotion(view, moves, model);
    const int expectRow = (right || up) ? 10 : 0;
    if (r.moveId != expectRow) {
        ++obs.disagreed;
        obs.note("state-admission");
        return "state-admission";
    }
    // The binding: at the fighter's own phase the resolver's set must be the set the fighter
    // is actually bound to. A move whose phase has no set is a named gap, not a mismatch.
    const CharacterMove* move = moves->find(expectRow);
    const int expectSet = move ? move->phase_set_index(before.phase) : -1;
    if (expectSet < 0) {
        ++obs.outOfDomain;
        obs.note("phase-set-unbound");
        return "phase-set-unbound";
    }
    if (after.anim_set_index() != expectSet) {
        ++obs.disagreed;
        obs.note("binding-mismatch");
        return "binding-mismatch";
    }
    // The clock, as measured in the live run rather than assumed:
    //   * a tick that changes state enters the new phase, whose clock reset reads 1 on that
    //     same update (Fighter::enter_phase zeroes it, then advance_animation_phase runs);
    //   * a stable tick advances by one and does NOT complete when the set carries the
    //     phase gate — `animation_set_phase_gate(set) != 0` returns before the period
    //     comparison (fighter.cpp:1759-1761), which is exactly the walk/idle case here.
    // The body feeds on the port's own gate (`hold`), so the two agree by construction on
    // that point. A predicted completion on an ungated set is therefore a case this run has
    // not measured yet: it is named, not guessed.
    // `move_counter` is deliberately NOT compared: it is a move-program data counter
    // (MoveOp::CounterSet/Counter, kGateCounter gates, aim spread), not a per-tick clock, so
    // the body's `secondary` has no established port counterpart. See the note in the summary.
    const bool transition = state != before.state;
    const bool predictedCompletion = duration < before.elapsed + 1 && !view.hold;
    if (!transition && predictedCompletion) {
        ++obs.disagreed;
        obs.note("phase-completion-unobserved");
        if (detail) {
            detail->beforePhase = before.phase;
            detail->afterPhase = after.move_phase();
            detail->beforeElapsed = before.elapsed;
            detail->afterElapsed = after.phase_elapsed();
            detail->duration = duration;
            detail->hold = view.hold;
        }
        return "phase-completion-unobserved";
    }
    const int wantPhase = transition ? 0 : before.phase;
    const int wantElapsed = transition ? 1 : before.elapsed + 1;
    if (detail) {
        detail->beforePhase = before.phase;
        detail->afterPhase = after.move_phase();
        detail->wantPhase = wantPhase;
        detail->beforeElapsed = before.elapsed;
        detail->afterElapsed = after.phase_elapsed();
        detail->wantElapsed = wantElapsed;
        detail->duration = duration;
        detail->hold = view.hold;
        detail->transition = transition;
    }
    if (after.move_phase() != wantPhase || after.phase_elapsed() != wantElapsed) {
        ++obs.disagreed;
        obs.note("phase-clock");
        return "phase-clock";
    }
    ++obs.agreed;
    obs.note("ok");
    return "ok";
}
// Melee admission, observed the same way: a fresh admission is a tick where the port bound a
// melee row it did not hold before. The recovered admission is asked the same question from the
// pre-step sample and the tick's input, and the two answers are compared. The port's selector
// keeps branches the admission struct does not carry (the press-edge rules live in the input
// selector), so a mismatch here is a finding about that boundary, not automatically a defect.
inline const char* observe_rena0_melee(const Rena0PilotSample& before, const Fighter& after,
                                       const input::PlayerState& input, Rena0PilotObserver& obs) {
    const int bound = after.attack_move_id();
    if (bound < 0 || bound == before.attackMoveId) return nullptr;  // no fresh admission
    const CharacterMoves* moves = after.moves();
    const xm::Model* model = after.model();
    if (!moves || !model) return nullptr;
    ++obs.meleeCompared;
    Rena0ResolverView view;
    view.weaponSlot = 0;  // the pilot combo is Rena+0; a weapon row would come from the slot
    view.actionState = before.actionState;
    view.stateEnum = static_cast<int>(before.state);
    view.phase = before.phase;
    view.grounded = !before.airborne;
    view.actionable = true;  // the port only admits from its actionable window
    // The port's own axis convention (held_axis.h, shared with the legacy dispatcher): the
    // recovered admission's back branch is z < 0, which is a Down press here — a naive
    // screen-axis mapping asked the wrong question and reported a false mismatch.
    view.inputX = held_axis_x(&input);
    view.inputZ = held_axis_z(&input);
    view.contact = 0;
    const Rena0Resolution r = resolve_rena0_admission(view, moves, model);
    if (r.moveId == bound) {
        ++obs.meleeAgreed;
        return "melee-ok";
    }
    ++obs.meleeDisagreed;
    if (r.moveId < 0) {
        obs.note(r.boostedGap ? "melee-armed-special-unrecovered" : "melee-refused");
        return r.boostedGap ? "melee-armed-special-unrecovered" : "melee-refused";
    }
    obs.note("melee-admission");
    return "melee-admission";
}

// The recovered shot body's own clock for the live comparison. The body reads `frame` and
// never advances it (the host owns that clock), so this state advances it once per tick while
// the port holds a shot row. Alignment is measured, not assumed: the body's frame 12 is the
// tick the original publishes its projectile request, and the port's own fire tick is what it
// is compared against.
struct Rena0ShotObservation {
    Rena0GroundShotMotion motion;
    bool active = false;
};

// Compare one tick of a live shot. Returns nullptr when no shot is in flight; otherwise the
// class name. Only the correspondences the seam can defend are compared (the fire tick, the
// sound id and the voice id); the projectile positions, the pitch (whose `elevation` input is
// a derived value the seam lists as computed) and the model requests are not compared and are
// counted as such.
inline const char* observe_rena0_shot(const Rena0PilotSample& before, const Fighter& after,
                                      const gameplay::MatchFrame& frame, const gameplay::Match* match,
                                      Rena0PilotObserver& obs, Rena0ShotObservation& state) {
    const int bound = after.shot_move_id();
    if (bound < 0) {
        state.active = false;
        return nullptr;
    }
    // The adapted body models state 400, the plain ground shot. Other shot rows (the walking
    // and dash shots 401/403/405-408, the charges 450/469) have their own programmes, so they
    // are named here rather than compared against the wrong body.
    if (bound != 400) {
        state.active = false;
        ++obs.outOfDomain;
        obs.note("shot-row-unadapted");
        return "shot-row-unadapted";
    }
    if (!state.active) {
        // A fresh shot: the body starts its own clock at frame 0 on the tick the port binds.
        state.motion = Rena0GroundShotMotion{};
        state.active = true;
    }
    Rena0GroundShotInput in;
    in.complete = false;  // the port clearing the row is what ends the shot
    in.grounded = !after.airborne();
    in.special = after.shoot_gate_powered();
    in.rounds = after.main_whole();
    in.elevation = 0.f;  // derived by the port's aim layer; not compared (see the header note)
    in.heading = after.facing_yaw();
    in.position = {after.position().x, after.position().y, after.position().z};
    ++obs.shotTicks;
    const Rena0GroundShotEffects fx = advance_rena0_ground_shot(0, state.motion, in);
    const char* result = "shot-ok";
    for (const auto& e : fx.events) {
        if (e.kind == Rena0ShotEventKind::sound) {
            ++obs.shotSoundCompared;
            if (frame.soundEffectId[0] == e.id) {
                ++obs.shotSoundAgreed;
            } else {
                ++obs.shotDisagreed;
                obs.note("shot-sound");
                result = "shot-sound";
            }
        } else if (e.kind == Rena0ShotEventKind::voice) {
            ++obs.shotVoiceCompared;
            if (frame.shotVoice[0] == e.id || frame.shotVoiceAlternative[0] == e.id) {
                ++obs.shotVoiceAgreed;
            } else {
                ++obs.shotDisagreed;
                obs.note("shot-voice");
                result = "shot-voice";
            }
        } else if (e.kind == Rena0ShotEventKind::model) {
            // The body requests a model clear on a slot (id -1) from frame 12 onward. The port's
            // per-slot binding (`trail_item_model`) never reads -1 during a shot, so the naive
            // mapping disagrees on every such tick (measured 0/148 on the shot scenario). That
            // makes the MAPPING unverified, not the port wrong: the body's `model` request may
            // mean something the port expresses elsewhere (a prop slot, a draw gate), and
            // asserting my guess would freeze it. Counted and named, never a failure.
            ++obs.shotModelCompared;
            if (after.trail_item_model(e.slot) == -1) ++obs.shotModelAgreed;
        } else if (e.kind == Rena0ShotEventKind::attachment_projectile) {
            // The body's request carries the bullet id and the pitch the host must use. The
            // spawn POSITION is host-resolved from the rig's anchors and is not compared here:
            // verifying it needs original-runtime evidence (recorded as a 2f limit).
            if (match) {
                const gameplay::Projectile* newest = nullptr;
                for (const gameplay::Projectile& p : match->shots().shots())
                    if (p.alive && p.owner == &after) newest = &p;
                if (newest) {
                    ++obs.shotBulletCompared;
                    if (std::abs(newest->pitch - e.pitch) <= 1.f) {
                        ++obs.shotBulletAgreed;
                    } else {
                        ++obs.shotDisagreed;
                        obs.note("shot-bullet-pitch");
                        result = "shot-bullet-pitch";
                    }
                }
            }
        } else if (e.kind == Rena0ShotEventKind::shot_statistics) {
            // The original publishes the statistics request and the projectile request on the
            // same frame; the port reports the shot as fired and spawns into the pool. One
            // comparison per fire tick, taken on the statistics event.
            {
                ++obs.shotFireCompared;
                if (frame.shotFired[0] || frame.shotsSpawned > 0) {
                    ++obs.shotFireAgreed;
                } else {
                    ++obs.shotDisagreed;
                    obs.note("shot-fire-tick");
                    result = "shot-fire-tick";
                }
            }
        }
    }
    // A port fire with no body request is the other half of the same comparison.
    if ((frame.shotFired[0] || frame.shotsSpawned > 0) && fx.events.empty()) {
        ++obs.shotFireCompared;
        ++obs.shotDisagreed;
        obs.note("shot-fire-unscheduled");
        result = "shot-fire-unscheduled";
    }
    ++state.motion.frame;
    return result;
}

// The recovered guard body's session for the live comparison. The port's guard is a state
// plus a stamina drain with NO phases and no 390/391/392 rows (fighter.cpp:1695-1697 binds no
// clip for Guard), so only the two facts both sides have are compared:
//   * a guarded contact must make the recovered body propose 391 (`MatchFrame::blocked`), and
//   * a guard start is visible on both sides (`MatchFrame::guardStarted`).
// Named, not compared: the body's phases and its 20-frame hold counter have no port
// counterpart (`guard-granularity-unrepresented`), and the body's 0..1000 gauge is not the
// port's 0..100 stamina (`guard-gauge-units-unresolved`), so an empty-gauge release cannot be
// compared with an exhausted-stamina release.
struct Rena0GuardObservation {
    Rena0GuardMotion motion;
    bool active = false;
};

inline const char* observe_rena0_guard(const Rena0PilotSample& before, const Fighter& after,
                                       const input::PlayerState& input,
                                       const gameplay::MatchFrame& frame,
                                       Rena0PilotObserver& obs, Rena0GuardObservation& state) {
    const bool guardHeld = input.down[input::Action::Guard];
    if (after.state() != FighterState::Guard) {
        // A guarded contact lands here: the port reads the guard BEFORE the damage call and
        // the same call stuns the victim out of Guard (match.cpp:265-280), so the block report
        // and the exit arrive on one tick. The body's session is advanced with the contact so
        // its 391 proposal is compared on the tick that matters.
        if (frame.blocked[0] && state.active) {
            state.motion.contact_flags = 2u;
            const Rena0GuardStep step = advance_rena0_guard(state.motion);
            ++obs.guardBlocks;
            if (step.state == 391) {
                ++obs.guardBlockAgreed;
            } else {
                ++obs.guardDisagreed;
                obs.note("guard-block-mismatch");
                state.active = false;
                return "guard-block-mismatch";
            }
        }
        state.active = false;
        return nullptr;
    }
    if (!state.active) {
        state.motion = Rena0GuardMotion{};
        state.active = true;
        ++obs.guardStarts;
    }
    ++obs.guardTicks;
    state.motion.grounded = !after.airborne();
    state.motion.button_a = guardHeld;
    state.motion.button_b = guardHeld;
    state.motion.contact_flags = frame.blocked[0] ? 2u : 0u;
    const Rena0GuardStep step = advance_rena0_guard(state.motion);
    ++state.motion.frame;
    if (frame.blocked[0]) {
        ++obs.guardBlocks;
        if (step.state == 391) {
            ++obs.guardBlockAgreed;
        } else {
            ++obs.guardDisagreed;
            obs.note("guard-block-mismatch");
            return "guard-block-mismatch";
        }
    }
    if (!guardHeld && after.state() == FighterState::Guard) {
        // The port checks the release at the top of its own update (fighter.cpp:428), so a
        // held state after a release means it did not act on it this tick.
        ++obs.guardDisagreed;
        obs.note("guard-release-not-taken");
        return "guard-release-not-taken";
    }
    return "guard-ok";
}

// P2-7 (2e) shot family: the pilot's item-model clear. The recovered shot body clears both
// held slots on every frame after its frame 11, and the port re-derives the slots each tick, so
// the driver keeps the answer and the fighter's derivation consults it.
class Rena0PilotShotPolicy final : public Fighter::PilotShot {
public:
    void set_cleared(bool cleared) { m_cleared = cleared; }
    bool clears_item_models() const override { return m_cleared; }
    // The recovered empty-tap voice (PILOT-SEAM.md §26): the adapted slot-7 release branch
    // requests `FUN_00422560(slot, 0x18, 10, 1)` — voice vocabulary index 24 — and no state.
    // The port's funded taps voice the shot program's own ids, so this id is the body's.
    int empty_shot_voice() const override { return 24; }

private:
    bool m_cleared = false;
};

// P2-7 (2e) meter family: the unified action meter. The policy carries no rates —
// the recovered integers live at the Fighter call sites with their citations — it is
// the attachment marker that selects the unified 0..1000 word over the legacy pair.
class Rena0PilotMeterPolicy final : public Fighter::PilotMeter {};

// The recovered guard predicate, as far as the port can express it today.
//
// Recovered: `(|bearing - facing| <= 45 || (victimword & 0x2000)) && (victimword & 0x400)
// && !(attackerword & 8)` (fighter.h's guard note; the bundle's `battle_hit_guard.hpp`;
// `FUN_00637950`'s guarded `else`). Expressibility:
//   * the victim's 0x400 is stood in for by the port's own Guard state — the port keeps its
//     own guard key because the word's builder is unlocated (fighter.h's note says so);
//   * the angle term is applied, in the port's convention: `facing_yaw()` points at the
//     opponent, so the check is that the victim faces the attacker within 45 degrees;
//   * the victim's 0x2000 (guard from any angle) and the attacker's unblockable flag 8 are
//     NOT expressible from port data and are therefore NOT applied — named, not guessed.
// The recovered guard row, whose records carry the guard-capable word the predicate reads.
// `battle_guard_motion.hpp` adapts rows 390/391/392; row 390 is the standing guard.
inline constexpr int kRena0GuardRow = 390;

// P2-7 (2e): the port binds no record for the Guard state, so the pilot hands the predicate the
// recovered row's guard-capable record. The record is looked up once and cached; the guard's own
// animation granularity (phases and the 20-frame hold counter) remains the named limit it was.
class Rena0GuardRecord final : public Fighter::PilotGuardMotion {
public:
    Rena0GuardRecord() = default;
    explicit Rena0GuardRecord(const CharacterMoves* moves) : m_moves(moves) {}
    void set_moves(const CharacterMoves* moves) {
        m_moves = moves;
        m_resolved = false;
        m_record = nullptr;
    }

    const MoveEntry* guard_record() const override {
        if (m_resolved) return m_record;
        m_resolved = true;
        const CharacterMove* move = m_moves ? m_moves->find(kRena0GuardRow) : nullptr;
        if (!move) return nullptr;
        for (int phase = 0; phase < move->sectionCount && !m_record; ++phase) {
            const MovePhase& p = move->phases[phase];
            for (int entry = 0; entry < p.entryCount; ++entry) {
                if (p.entries[entry].stateFlags & 0x400) {
                    m_record = &p.entries[entry];
                    break;
                }
            }
        }
        return m_record;
    }

private:
    const CharacterMoves* m_moves = nullptr;
    mutable bool m_resolved = false;
    mutable const MoveEntry* m_record = nullptr;
};

// The recovered guard decision as a pure function of the four terms the original reads, so the
// predicate can be pinned offline against `FUN_00637950`'s guarded branch without constructing a
// live Fighter:
//
//   guarded = (|relative| <= 45 || (victimFlags & 0x2000)) && (victimFlags & 0x400)
//             && !(attackFlags & 8)
//
// Outcome report for the same four terms, so a live run can say *why* it answered.
enum class Rena0GuardOutcome { guarded, no_record, not_guard_capable, unblockable, outside_angle };

inline Rena0GuardOutcome decide_rena0_guard(unsigned victimFlags, unsigned attackFlags,
                                           float relativeDegrees) {
    if ((victimFlags & 0x400u) == 0) return Rena0GuardOutcome::not_guard_capable;
    if ((attackFlags & 8u) != 0) return Rena0GuardOutcome::unblockable;
    if ((victimFlags & 0x2000u) != 0) return Rena0GuardOutcome::guarded;
    if (std::abs(relativeDegrees) > 45.f) return Rena0GuardOutcome::outside_angle;
    return Rena0GuardOutcome::guarded;
}

class Rena0PilotGuard final : public Fighter::PilotGuard {
public:
    // Diagnostics for the pilot log: how often the predicate was asked and why it answered the
    // way it did. A gate that never fires must be visible, not assumed.
    mutable long long calls = 0;
    mutable long long guarded = 0;
    mutable long long no_record = 0;          // a side has no live frame record to read
    mutable long long not_guard_capable = 0;  // the victim's record lacks 0x400
    mutable long long unblockable = 0;        // the attacker's record carries bit 8
    mutable long long outside_angle = 0;      // 0x2000 absent and the angle is past 45 degrees

    // The recovered predicate, read from the LIVE frame records — the words the original reads
    // at `[[actor+0x10]+0x28]` (victim) and `[[actor+0x10]+0x2c]` (attacker), which this port
    // parses as `MoveEntry::stateFlags` / `attackFlags` and reaches through
    // `current_move_record()`. `FUN_00637950`'s guarded `else` (listing lines 185-192):
    //
    //   guarded = (|relative| <= 45 || (victimFlags & 0x2000)) && (victimFlags & 0x400)
    //             && !(attackFlags & 8)
    //
    // Provenance, established from the shipped data rather than assumed: the first record of
    // Rena+0 carrying 0x400 is **row 390**, the guard row whose body this pilot adapted, and the
    // first carrying bit 8 is row 350, an attack row; 0x2000 and 0x8000 appear in none of her
    // 276 records (rena0_guard_flags_test). The port's earlier stand-in — its own `Guard` state
    // — is therefore gone: all three terms now come from the records themselves.
    bool guards_hit(const Fighter& victim, const Fighter& attacker) const override {
        ++calls;
        // The victim's own live record first; when the port binds none (the Guard state), the
        // pilot's guard motion supplies the recovered row's record instead.
        const MoveEntry* victimRecord = victim.current_move_record();
        if (!victimRecord && victim.pilot_guard_motion())
            victimRecord = victim.pilot_guard_motion()->guard_record();
        const MoveEntry* attackRecord = attacker.current_move_record();
        if (!victimRecord || !attackRecord) {
            ++no_record;
            return false;
        }
        // The angle term, in the port's convention: `facing_yaw()` points at the opponent, so the
        // check is that the victim faces the attacker within 45 degrees. A coincident pair has no
        // bearing at all, which the original's own difference would also fail to resolve.
        const glm::vec3 toAttacker = attacker.position() - victim.position();
        float relative = 180.f;
        if (std::abs(toAttacker.x) >= 1e-4f || std::abs(toAttacker.z) >= 1e-4f) {
            const float bearing = std::atan2(toAttacker.x, toAttacker.z);
            relative = glm::degrees(std::remainder(victim.facing_yaw() - bearing, glm::two_pi<float>()));
        }
        switch (decide_rena0_guard(victimRecord->stateFlags, attackRecord->attackFlags, relative)) {
            case Rena0GuardOutcome::guarded: ++guarded; return true;
            case Rena0GuardOutcome::not_guard_capable: ++not_guard_capable; return false;
            case Rena0GuardOutcome::unblockable: ++unblockable; return false;
            case Rena0GuardOutcome::outside_angle: ++outside_angle; return false;
            case Rena0GuardOutcome::no_record: break;
        }
        ++no_record;
        return false;
    }
};

// P2-7 charge family: feed the pilot fighter's mode gauges from the hits the frame reports.
// Only the pilot fighter's own hits count: when it is the attacker its attacker gauge advances,
// when it is the victim its victim gauge does, each with the record columns its own hit carried.
inline void feed_rena0_mode_gauges(const gameplay::MatchFrame& frame, const gameplay::Match& match,
                                   int pilotIndex, Rena0PilotObserver& obs) {
    const gameplay::Fighter& pilot = match.fighter(pilotIndex);
    obs.modeGauges.mode = static_cast<std::uint32_t>(
        gameplay::hypermode_wire_value(pilot.hypermode()));
    const gameplay::Fighter::MeleeChargeBases& bases = pilot.melee_charge_bases();
    // The record's charge scale is the match's own (shipped default 100); defense and modifier
    // are the damage chain's factors, 100 each when nothing modifies them.
    constexpr std::int32_t kChargeScale = 100, kDefense = 100, kModifier = 100;
    if (frame.meleeHit[pilotIndex]) {
        obs.modeGauges.on_attacker_hit(bases.attacker, kChargeScale);
        ++obs.gaugeAttackerHits;
    }
    for (int i = 0; i < gameplay::kMatchFighterCount; ++i) {
        if (frame.meleeHit[i] && frame.meleeVictim[i] == pilotIndex) {
            obs.modeGauges.on_victim_hit(bases.victim, kChargeScale, kDefense, kModifier);
            ++obs.gaugeVictimHits;
        }
    }
}

// Slice 2's driving half: the policy the fighter consults when the flag is on. It answers
// the two locomotion questions the seam assigns to the recovered body and returns -1 for
// anything outside the locomotion domain, so a dash, attack or airborne tick keeps the legacy
// answer. The pilot feeds it the tick's input before the step.
class Rena0PilotLocomotion final : public Fighter::PilotLocomotion {
public:
    void set_input(const input::PlayerState* input) {
        m_input = input;
        m_countedThisTick = false;
    }
    Rena0PilotObserver& observer() { return m_observer; }
    const Rena0PilotObserver& observer() const { return m_observer; }

    int proposed_state(const Fighter& f) const override {
        const int state = resolve(f);
        if (state < 0) return -1;
        return state;
    }
    float walk_speed_per_tick(const Fighter& f) const override {
        const int state = resolve(f);
        if (state < 0) return -1.f;
        return m_lastSpeed;
    }

private:
    // Runs the recovered body for this fighter and returns its state number, or -1 when the
    // tick is outside the locomotion domain (the legacy answer then stands).
    int resolve(const Fighter& f) const {
        const CharacterMoves* moves = f.moves();
        const xm::Model* model = f.model();
        if (!moves || !model || !m_input) return -1;
        const FighterState state = f.state();
        if (state != FighterState::Idle && state != FighterState::Walk) return -1;
        if (f.airborne()) return -1;
        const bool right = m_input->down[input::Action::Right];
        const bool up = m_input->down[input::Action::Up];
        if (m_input->down[input::Action::Left] || m_input->down[input::Action::Down] ||
            (right && up))
            return -1;
        const int set = f.anim_set_index();
        const int duration = (set >= 0 && static_cast<std::size_t>(set) < model->anims.size() &&
                              model->ticksPerSecond > 0.f)
                                 ? gameplay::animation_period_frames(*model, set)
                                 : 0;
        Rena0ResolverView view;
        view.weaponSlot = 0;
        view.actionState = static_cast<int>(state);
        view.stateEnum = static_cast<int>(state);
        view.phase = f.move_phase();
        view.elapsed = f.phase_elapsed();
        view.counter = f.move_counter();
        view.grounded = true;
        view.actionable = f.actionable();
        view.inputX = right ? 1 : 0;
        view.inputZ = up ? -1 : 0;
        view.duration = duration;
        view.hold = moves->animation_set_phase_gate(set) != 0;
        view.gauge = f.stamina() * 10;
        const Rena0Resolution r = resolve_rena0_locomotion(view, moves, model);
        if (r.moveId < 0) return -1;
        m_lastSpeed = (r.moveId == 10) ? kRena0State10WalkSpeed : 0.f;
        // The fighter asks both questions in one update; count the tick once.
        if (!m_countedThisTick) {
            ++m_observer.driven;
            m_countedThisTick = true;
        }
        return r.moveId == 10 ? 10 : 0;
    }
    const input::PlayerState* m_input = nullptr;
    mutable float m_lastSpeed = 0.f;
    mutable bool m_countedThisTick = false;
    mutable Rena0PilotObserver m_observer;
};
}  // namespace gameplay::native
