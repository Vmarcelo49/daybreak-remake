// P2-6 (2d) — the single binding owner for the Rena+0 pilot seam.
//
// The recovered bodies under this directory answer "what does the character do"; this
// resolver answers "which port move row, phase and animation set does that correspond to,
// and if it does not correspond, why not". Every path returns an explicit reason, so the
// pilot can never present a silent zero as a resolution (DIRECTION.md §4 Phase 2 2d).
//
// UNWIRED BY DESIGN. Nothing outside tests/ includes this header: the legacy default path
// is unchanged and the other 45 combos are not rerouted. tests/rena0_resolver_test.cpp
// asserts that, so a future edit that wires the resolver in without the owner's approval
// fails the suite instead of slipping through. Integration behind a flag is 2e.
//
// Dependencies the seam records as unresolved are named here rather than guessed:
//   * the armed+ready ("boosted") melee chain arm is not modelled by the port's admission
//     (melee_admission.h's own recorded gap), so a view with `armedSpecial` inside the
//     299 < actionState < 350 window is reported as `boostedGap`;
//   * the airborne cycle's clip resolution is unresolved, so an airborne locomotion view
//     returns no row with `airborne-set-unresolved` rather than an invented set;
//   * the locomotion body itself is observation-only (PILOT-SEAM §7-§9).
#pragma once

#include "assets/xmodel.h"
#include "gameplay/character_moves.h"
#include "gameplay/melee_admission.h"
#include "gameplay/native/rena0_locomotion_observation.h"
#include "gameplay/weapon_definition.h"

#include <cstddef>

namespace gameplay::native {

// Host-filled scalars: the subset of PILOT-SEAM §14 this seam needs. Deliberately not a
// Fighter reference, so a test harness can fill it and the pilot path can be the only
// production caller after approval.
struct Rena0ResolverView {
    int weaponSlot = 0;          // NN.dat number IS the weapon slot; -1 = unbound
    int actionState = 0;         // port action_state() (0 collapses Guard/Hit/Shoot onto Idle)
    int stateEnum = 0;           // port state() enum
    int phase = 0;
    int elapsed = 0;
    int counter = 0;
    bool grounded = true;
    bool actionable = false;     // the actor's 0x100 window
    bool meleeActive = false;
    unsigned contact = 0;        // melee contact bits: 1 hit, 2 guarded
    bool armedSpecial = false;   // +0x845 && +0x848
    int inputX = 0;              // held lateral axis, body sign convention
    int inputZ = 0;              // held forward axis, body sign convention
    int stop = 0;                // nonzero stop word suppresses the locomotion body
    int slow = 0;
    int duration = 0;            // bound clip duration in updates
    bool hold = false;           // animation_set_phase_gate(set) != 0
    float speed = 0.f;
    float vertical = 0.f;
    int gauge = 0;
};

enum class Rena0BindingSource { RecoveredAdmission, LocomotionBody, Fallback };

struct Rena0Resolution {
    int moveId = -1;        // resolved move row, -1 when none
    int setId = -1;         // animation set for that row at that phase, -1 when none
    int phase = 0;          // the phase the set was resolved at
    bool boostedGap = false; // the recovered boosted arm would apply but is not modelled
    Rena0BindingSource source = Rena0BindingSource::Fallback;
    const char* reason = "unresolved";  // always set, success or not
};

struct Rena0WeaponResolution {
    int weaponId = -1;
    int slot = -1;
    const char* reason = "weapon-unbound";
};

// Explicit move/phase/set resolution: the single place the pilot seam turns a recovered
// row into a port animation set. Bounds-checked against the model, with reasons that
// distinguish "no data" from "the data says none" from "outside the rig".
inline Rena0Resolution resolve_rena0_set(int moveId, int phase, const CharacterMoves* moves,
                                         const xm::Model* model) {
    Rena0Resolution out;
    out.moveId = moveId;
    out.phase = phase;
    if (moveId < 0) {
        out.reason = "no-move-row";
        return out;
    }
    if (!moves) {
        out.reason = "no-move-table";
        return out;
    }
    const CharacterMove* move = moves->find(moveId);
    if (!move) {
        out.reason = "move-row-absent";
        return out;
    }
    const int set = move->phase_set_index(phase);
    if (set < 0) {
        out.reason = "phase-set-unbound";
        return out;
    }
    if (model && static_cast<std::size_t>(set) >= model->anims.size()) {
        out.reason = "set-out-of-model-bounds";
        return out;
    }
    out.setId = set;
    out.reason = "set-resolved";
    return out;
}

// Locomotion: the recovered body picks the state; the row for that state comes from the
// move table and is bounds-checked against the rig.
inline Rena0Resolution resolve_rena0_locomotion(const Rena0ResolverView& view,
                                                const CharacterMoves* moves,
                                                const xm::Model* model) {
    // Only Idle and Walk are entry states for the recovered locomotion body (its own
    // validator rejects anything else), so anything else is an explicit fallback.
    if (view.stateEnum != 0 && view.stateEnum != 1) {
        Rena0Resolution out;
        out.reason = "not-a-locomotion-state";
        out.source = Rena0BindingSource::Fallback;
        return out;
    }
    Rena0LocomotionMotion motion{view.speed, view.vertical, .5f, 0.f, 0.f, 0.f, view.gauge,
                                 kRena0DirectionNone};
    const Rena0LocomotionInput input{view.stateEnum == 1 ? kRena0StateWalk : kRena0StateIdle,
                                     view.phase, view.elapsed, view.counter, view.inputX,
                                     view.inputZ, view.grounded ? 1 : 0, view.stop, view.slow,
                                     view.duration, view.hold};
    const Rena0LocomotionEffects effects = advance_rena0_locomotion_observation(motion, input);
    if (effects.state == kRena0StateAirborne) {
        // The airborne cycle's clip resolution is a recorded unresolved dependency: name it
        // instead of inventing a set.
        Rena0Resolution out;
        out.phase = effects.phase;
        out.source = Rena0BindingSource::Fallback;
        out.reason = "airborne-set-unresolved";
        return out;
    }
    const int row = effects.state == kRena0StateWalk ? 10 : 0;
    Rena0Resolution out = resolve_rena0_set(row, effects.phase, moves, model);
    out.source = out.setId >= 0 ? Rena0BindingSource::LocomotionBody
                                : Rena0BindingSource::Fallback;
    return out;
}

// Melee admission: the recovered admission chooses the row from the view's own scalars.
inline Rena0Resolution resolve_rena0_admission(const Rena0ResolverView& view,
                                               const CharacterMoves* moves,
                                               const xm::Model* model) {
    Rena0Resolution out;
    // The bundle consults its armed+ready arm inside this window; the port's admission does
    // not model it (melee_admission.h's recorded gap), so say so rather than claim a row.
    if (view.armedSpecial && view.actionState > 299 && view.actionState < 350)
        out.boostedGap = true;
    AttackAdmissionInput in;
    in.weaponSlot = view.weaponSlot;
    in.state = view.actionState;
    in.phase = view.phase;
    in.grounded = view.grounded;
    in.x = view.inputX;
    in.z = view.inputZ;
    in.normalFlag = view.actionable;
    in.contact = view.contact;
    in.boosted = view.armedSpecial;
    AttackAdmissionTable table{moves};
    const int admitted = rena_melee_admission(in, table);
    if (admitted < 0) {
        out.source = Rena0BindingSource::Fallback;
        out.reason = out.boostedGap ? "armed-special-unrecovered" : "admission-refused";
        return out;
    }
    out = resolve_rena0_set(admitted, 0, moves, model);
    out.boostedGap = out.boostedGap || (view.armedSpecial && view.actionState > 299 &&
                                        view.actionState < 350);
    out.source = out.setId >= 0 ? Rena0BindingSource::RecoveredAdmission
                                : Rena0BindingSource::Fallback;
    if (out.setId >= 0) {
        // The row is recovered; the set is a port binding of that row. Both facts matter.
        out.reason = "recovered-admission";
    }
    return out;
}

// The two-halves rule (AGENTS.md hard rule 7): a fighter with no bound weapon is not a
// claim, so an unbound or mismatched slot is a resolution failure with a named reason.
inline Rena0WeaponResolution resolve_rena0_weapon(int slot, const WeaponDefinition* weapon) {
    Rena0WeaponResolution out;
    out.slot = slot;
    if (slot < 0) {
        out.reason = "weapon-unbound";
        return out;
    }
    if (!weapon || !weapon->valid()) {
        out.reason = "weapon-data-absent";
        return out;
    }
    out.weaponId = weapon->id;
    out.reason = "weapon-bound";
    return out;
}
}  // namespace gameplay::native
