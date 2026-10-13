#pragma once

#include <array>

namespace gameplay {

struct RenaDashInput {
    int weaponSlot = -1; // Rena+0/+1/+2: 0/1/2
    int currentState = 0;
    unsigned command = 0; // FUN_0041efe0 order: forward/back/left/right = 1..4
    bool grounded = true;
    int gauge = 0; // fighter +0x834 action gauge; not stamina or actor +0x7f4 status
    bool normalFlag = false; // current NN record flags28 & 0x100
    unsigned contact = 0; // bit 0 = connected hit
    int currentCancelThreshold = 0;
};

struct RenaDashRows {
    // Candidate first priorities indexed by command-1: 1→20, 2→27, 3→24, 4→23.
    std::array<int, 4> firstPriority{};
    std::array<bool, 4> present{};
};

struct RenaDashAdmission {
    int state = -1;
    bool airborne = false;
};

inline constexpr int rena_dash_ground_candidate(unsigned command) {
    switch (command) {
    case 1: return 20;
    case 2: return 27;
    case 3: return 24;
    case 4: return 23;
    default: return -1;
    }
}

// FUN_00445ee0 / FUN_0044d850 / FUN_0043ded0 dash-admission order, ported
// separately from the dash body. The airborne return is row 30, but its priority
// gate still reads the corresponding ground-direction row from the source.
inline RenaDashAdmission rena_dash_admission(const RenaDashInput& in,
                                              const RenaDashRows& rows) {
    if (in.weaponSlot < 0 || in.weaponSlot > 2 || in.command < 1 || in.command > 4 ||
        in.gauge <= 0 || !in.normalFlag)
        return {};

    const bool hit = in.currentState > 299 && in.currentState < 350 &&
                     (in.contact & 1u) != 0;
    if (in.weaponSlot != 2 && in.command == 2 && in.grounded &&
        in.currentState != 320 && hit)
        return {28, false};

    const unsigned candidateIndex = in.command - 1u;
    if (!rows.present[candidateIndex]) return {};
    const bool priorityGate = in.currentCancelThreshold <= rows.firstPriority[candidateIndex];
    if (!priorityGate && !(in.weaponSlot != 1 && in.command == 2 && hit)) return {};
    return {in.grounded ? rena_dash_ground_candidate(in.command) : 30, !in.grounded};
}

} // namespace gameplay
