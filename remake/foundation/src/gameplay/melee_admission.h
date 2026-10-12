#pragma once

// Recovered attack admission for the Rena group (character 0, weapon slots 0/1/2).
//
// Sources: the original dispatchers FUN_00445ee0 (input selector), FUN_0044d850 and
// FUN_0043ded0 (situation selector), read through the Ginkiha implementation
// reference (battle_rena_melee_admission.hpp, roster_walk_shot_admission.hpp,
// roster_ground_shot_admission.hpp, roster_air_dash_cancels.hpp) and cross-checked
// against research/decompiled/FUN_0043ffc0.c / FUN_00448220.c / FUN_00438310.c.
// The donor's numbers matched the handlers everywhere they were compared; the
// handlers stay authoritative on any future disagreement.
//
// The original admits attacks as numeric states through one per-frame dispatcher.
// This header ports that dispatcher's Rena branch onto the port's inputs: the
// fighter supplies its current numeric state, the input edge and axes, the current
// NN record's 0x100 flag, and the melee contact bits; the functions return the row
// the original would select. Weapon families are facts from the dispatcher, so a
// branch absent for a weapon stays absent (e.g. Rena+2 has no 332 air-dash dive and
// Rena+1 has no 302/341/370 branches at all).

#include "gameplay/character_moves.h"

namespace gameplay {

// Whether this combo has a recovered admission table. Only the Rena group so far;
// every other combo keeps its previous bounded candidates (issue #66 owns the rest).
inline bool attack_admission_recovered(int characterIndex) { return characterIndex == 0; }

// What the original's dispatcher reads when an attack edge arrives. `state` is the
// numeric action row: 0 idle, 10 walk, dash rows 20/23/24/27, air rows 40..42, the
// air-dash row 30, or an attack row during a chain press.
struct AttackAdmissionInput {
    int weaponSlot = 0;
    int state = 0;
    int phase = 0;
    bool grounded = true;
    int x = 0;  // lateral held axis (right +1, left -1)
    int z = 0;  // forward axis (toward target +1, away -1)
    bool normalFlag = false;  // state word bit 0x100 (actionable)
    unsigned contact = 0;     // melee contact bits: 1 hit, 2 guarded
};

// Gate on the candidate row: true when the current row's cancel threshold permits
// the transition AND the table ships the row with a phase (a costume that drops the
// row must not resolve — present_move's rule).
struct AttackAdmissionTable {
    const CharacterMoves* moves = nullptr;

    bool gate(int currentId, int next) const {
        if (!moves) return false;
        const CharacterMove* from = moves->find(currentId);
        const CharacterMove* to = moves->find(next);
        if (!from || !to || to->first_set_index() < 0) return false;
        return from->cancelThreshold <= to->priority;
    }
};

// The recovered Rena melee admission (air branch first, then the grounded dash,
// directional, chain and neutral branches). Returns the admitted move id or -1.
// `boosted` (special-gauge active+ready chaining on contact) is deliberately not
// modeled: the port's special-gauge ready semantics for the melee branch are
// unrecovered, so chains honor the 0x100 window only — a recorded gap, not a guess.
inline int rena_melee_admission(const AttackAdmissionInput& in,
                                 const AttackAdmissionTable& table) {
    const AttackAdmissionTable absent{};
    const AttackAdmissionTable& t = table.moves ? table : absent;
    const int state = in.state;
    const bool enabled = in.normalFlag;
    const auto gate = [&](int next) { return t.gate(state, next); };
    const int we = in.weaponSlot;

    if (!in.grounded) {
        // FUN_00445ee0:319-323 — the air-dash row selects the dive kick while the
        // dash still has phases left; Rena+2 has no such branch.
        if (we != 2 && state == 30 && in.phase < 2 && in.normalFlag && gate(332))
            return 332;
        return enabled && gate(320) ? 320 : -1;
    }
    if (in.normalFlag) {
        // Dash-attack branches: forward dash with a lateral input crosses into the
        // side-dash attack; the side dashes pick 330 when back is held, else 331.
        if (state == 20 && in.x != 0 && gate(331)) return 331;
        if (state == 20 && gate(330)) return 330;
        if ((state == 23 || state == 24) && in.z < 0 && gate(330)) return 330;
        if ((state == 23 || state == 24) && gate(331)) return 331;
    }
    // Directional kicks read the held axes, not the 0x100 flag: the original tests
    // them on every actionable press. Weapon 2 may not re-enter the row it holds.
    if (in.z < 0 && (we != 2 || state != 310) && enabled && gate(310)) return 310;
    if (in.x != 0 && (we != 2 || state != 311) && enabled && gate(311)) return 311;
    const bool combo = state == 300 || state == 301 || state == 302 ||
                       state == 340 || state == 341;
    if (we != 2) {
        // Landing/dash-recovery sources select the landing melee; the 340→341
        // follow-up is Rena+0's alone.
        if ((state == 329 || state == 333 || state == 44) && enabled && gate(340))
            return 340;
        if (we == 0 && state == 340 && in.normalFlag && gate(341)) return 341;
        // The neutral chain: 300→301 for weapons 0/1, 301→302 for weapon 0 only
        // (FUN_00448220 has no 302 branch for Rena+1).
        if (state == 300 && in.normalFlag && gate(301)) return 301;
        if (we == 0 && state == 301 && in.normalFlag && gate(302)) return 302;
    }
    if ((we != 2 || state != 300) && enabled && gate(300)) return 300;
    return -1;
}

// Tap-shot state admission (short release, primary magazine). The original's slot-7
// routing for the Rena group: walking selects the mobile shot for weapons 0/1 (the
// iron cleaver keeps the ordinary 400 through the same gate), the dash states select
// the directional shots for weapon 0 and plain 401/400 for the others, and an
// air-dash release with a direction held takes the fast shot for weapon 0 only.
// Charge releases always select 450 ground / 460 air and are not routed here.
inline int rena_tap_shot_state(int weaponSlot, int state, bool grounded) {
    if (!grounded) {
        // The air branch is handled by the caller with the air-dash fast-shot rule;
        // the ordinary air tap is 402 for every Rena weapon.
        return 402;
    }
    const int we = weaponSlot;
    if (state == 10) return we < 2 ? 401 : 400;  // walk gate: 401 for w0/w1, else 400
    if (state == 20) return we == 0 ? 401 : we == 1 ? 401 : 400;
    if (state == 23) return we == 0 ? 405 : we == 1 ? 401 : 400;
    if (state == 24) return we == 0 ? 406 : we == 1 ? 401 : 400;
    if (state == 27) return we == 0 ? 407 : we == 1 ? 401 : 400;
    return 400;
}

// The air-dash fast shot (FUN_00445ee0's 408 branch): only Rena+0 requests it, and
// only while the dash row is still in its first two phases with a direction held.
inline bool rena_air_dash_fast_shot(int weaponSlot, int state, int phase, bool directional) {
    return weaponSlot == 0 && state == 30 && phase < 2 && directional;
}

}  // namespace gameplay
