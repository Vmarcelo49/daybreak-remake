#pragma once
// The closed pilot's --native-actions=rena0 path around one match step. Removed at M5.
#include <cstdio>
#include <string>

#include "gameplay/match.h"
#include "gameplay/native/rena0_pilot_adapter.h"

namespace gameplay::native {

struct Rena0PilotRun {
    Rena0PilotObserver observer;
    // Slice 2's driving policy, attached to P1 only while the flag is on.
    Rena0PilotLocomotion locomotion;
    Rena0ShotObservation shot;
    Rena0GuardObservation guard;
    Rena0PilotGuard guardPolicy;
    Rena0GuardRecord guardRecord;
    bool shotModelCleared = false;  // the shot body's item-model clear, latched per shot
    Rena0PilotShotPolicy shotPolicy;
    Rena0PilotMeterPolicy meterPolicy;  // the unified meter marker
    Rena0PilotSample sample{};

    // True when P1 is the pilot combo on this tick and the flag is on.
    bool before_step(Match& match, const input::PlayerState* const* inputs, bool enabled) {
        // P2-7 (2e) slice 1: the pilot observes P1 on the match tick. The sample is read before
        // the step and the comparison after it, and nothing here writes to the fighter — observe
        // mode must not change a single decision (see rena0_pilot_adapter.h).
        const bool pilotObserve = enabled && inputs[0] != nullptr &&
                                  is_rena0_pilot_combo(match.fighter(0));
        // Slice 2: with the flag on, P1 (and only P1) consults the recovered body for its
        // locomotion state proposal and walk speed. Attached here, before the step, so the state
        // machine and the movement update see it on this same tick.
        if (pilotObserve) {
            locomotion.set_input(inputs[0]);
            match.fighter(0).set_pilot_locomotion(&locomotion);
            // The guard gate rides the same flag and applies to the pilot fighter as the victim.
            match.fighter(0).set_pilot_guard(&guardPolicy);
            // The Guard state binds no record, so the pilot supplies the recovered guard row's
            // guard-capable record for the predicate to read.
            guardRecord.set_moves(match.fighter(0).moves());
            match.fighter(0).set_pilot_guard_motion(&guardRecord);
            match.fighter(0).set_pilot_shot(&shotPolicy);
            // The unified meter rides the same flag: P1 reads and writes the single
            // 0..1000 word while it is attached.
            match.fighter(0).set_pilot_meter(&meterPolicy);
            // The mode gauges' limits are the actor DAT's header dwords, which the move table
            // already carries (Rena+0: limit0 850, duration0 900, limit1 850, duration1 900).
            if (const CharacterMoves* moves = match.fighter(0).moves())
                observer.modeGauges.limits =
                    rena0_mode_gauge_limits(moves->header_values());
        } else {
            // Match transitions can retain Fighter storage; no policy may leak to another combo
            // or remain attached after the pilot input domain is left.
            match.fighter(0).set_pilot_locomotion(nullptr);
            match.fighter(0).set_pilot_guard(nullptr);
            match.fighter(0).set_pilot_guard_motion(nullptr);
            match.fighter(0).set_pilot_shot(nullptr);
            match.fighter(0).set_pilot_meter(nullptr);
        }
        sample = pilotObserve ? sample_rena0_pilot_tick(match.fighter(0)) : Rena0PilotSample{};
        return pilotObserve;
    }

    void after_step(Match& match, const input::PlayerState* const* inputs, const MatchFrame& f) {
        const Rena0PilotSample& pilotSample = sample;
    Rena0PilotDetail detail;
    const char* cls = observe_rena0_tick(pilotSample, match.fighter(0),
                                                          *inputs[0], observer, &detail);
    const char* meleeCls = observe_rena0_melee(
        pilotSample, match.fighter(0), *inputs[0], observer);
    std::fprintf(stderr, "[rena0-pilot] tick=%lld state=%d class=%s phase %d->%d want %d elapsed %d->%d "
                "want %d duration=%d hold=%d transition=%d\n",
                observer.ticks, (int)match.fighter(0).state(), cls,
                detail.beforePhase, detail.afterPhase, detail.wantPhase, detail.beforeElapsed,
                detail.afterElapsed, detail.wantElapsed, detail.duration,
                detail.hold ? 1 : 0, detail.transition ? 1 : 0);
    if (meleeCls)
        std::fprintf(stderr, "[rena0-pilot] melee tick=%lld row=%d class=%s\n",
                     observer.ticks, (int)match.fighter(0).attack_move_id(), meleeCls);
    if (const char* guardCls = observe_rena0_guard(
            pilotSample, match.fighter(0), *inputs[0], f, observer, guard);
        guardCls && std::string(guardCls) != "guard-ok")
        std::fprintf(stderr, "[rena0-pilot] guard tick=%lld state=%d class=%s\n",
                     observer.ticks, (int)match.fighter(0).state(), guardCls);
    feed_rena0_mode_gauges(f, match, 0, observer);
    // The recovered shot body clears both held item-model slots on the frame it fires
    // (frame 12, port tick 13). Row 400 is the row the adapted body models; the other
    // shot rows have their own programmes and are named unadapted by the observer.
    // The recovered shot body re-asserts its clear every frame from its fire to the end of
    // the action, so the latch lives on App: this block runs once per frame, and a local
    // would reset before the next derivation reads it.
    if (match.fighter(0).shot_move_id() != 400) {
        shotModelCleared = false;
    } else if (f.shotFired[0]) {
        shotModelCleared = true;
    }
    shotPolicy.set_cleared(shotModelCleared);
    if (const char* shotCls = observe_rena0_shot(
            pilotSample, match.fighter(0), f, &match, observer, shot);
        shotCls && std::string(shotCls) != "shot-ok")
        std::fprintf(stderr, "[rena0-pilot] shot tick=%lld row=%d class=%s\n",
                     observer.ticks, (int)match.fighter(0).shot_move_id(), shotCls);
    }
};

}  // namespace gameplay::native
