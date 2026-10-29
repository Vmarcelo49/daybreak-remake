// P2-7 (2e) charge family — the recovered charge-gauge bodies, adapted for offline observation
// with attribution.
//
// Adapted from the local bundle's `battle_attack_charge.hpp` (original 0x63844e..0x6384fa,
// attacker mode 1), `battle_hit_charge.hpp` (0x6382d9..0x63844e, victim modes 0 and 2) and the
// shared integer helpers of `battle_damage_scaling.hpp`. The owner's 2026-10-14 licence note
// allows vendoring bundle code with attribution.
//
// SCOPE, stated plainly: these are the *gauge* bodies — the accumulation rules behind the
// charge/special gauge, which the contract currently declares unsupported (`charge_gauge`,
// §2b: "reads 1000 at rest and does not move under SPECIAL or shooting"). The charge *move*
// bodies (states 350-362) live in the bundle's `full_charge_native_bodies_20260929.hpp`, which
// is generated decompiler output whose Rena+0 body (`full_charge_body_0_0_351`) is a thin
// wrapper over host calls; those are NOT adapted here, and the port's charge rows stay on its
// own data-driven path (`move_behavior.h`), pinned by `rena0-charge-hold.fixture`.
//
// Only the host plumbing differs from the bundle: the `notify(id)` callbacks become the
// returned event ids, so a test can pin them without a host.
#pragma once

#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <vector>

namespace gameplay::native {

// The bundle's integer semantics, kept exactly: the multiply wraps as unsigned, the divide is
// a plain signed division that faults where the original would, and "signed" is a bit
// reinterpretation rather than a cast.
inline std::int32_t charge_signed(std::uint32_t bits) {
    std::int32_t n = 0;
    std::memcpy(&n, &bits, 4);
    return n;
}
inline std::int32_t charge_multiply(std::int32_t a, std::int32_t b) {
    return charge_signed(std::uint32_t(a) * std::uint32_t(b));
}
inline std::int32_t charge_divide(std::int32_t a, std::int32_t b) {
    if (!b || (a == std::numeric_limits<std::int32_t>::min() && b == -1))
        throw std::domain_error("the original's integer division would fault here");
    return a / b;
}

// Attacker mode 1: a landed attack adds base*scale/90 to the attacker's gauge, and reaching
// the limit notifies id 6, latches `ready` and clamps.
struct Rena0AttackCharge {
    std::uint32_t mode = 1;
    std::uint32_t blocked = 0;
    std::uint32_t charge = 0;
    std::uint32_t limit = 1000;
    std::uint32_t ready = 0;
};

struct Rena0ChargeEffects {
    std::vector<int> notified;  // the host notifications, in order
};

inline Rena0ChargeEffects advance_rena0_attack_charge(Rena0AttackCharge& s, std::int32_t base,
                                                      std::int32_t scale, int attacker) {
    Rena0ChargeEffects out;
    if (std::uint8_t(s.mode) != 1 || std::uint8_t(s.blocked) ||
        charge_signed(s.charge) >= charge_signed(s.limit))
        return out;
    s.charge += std::uint32_t(charge_divide(charge_multiply(base, scale), 90));
    if (charge_signed(s.charge) >= charge_signed(s.limit)) {
        out.notified.push_back(6);  // host.notify(attacker, 6)
        s.ready = 1;
        s.charge = s.limit;
    }
    (void)attacker;  // the bundle passes it through to the host; the id is what is recovered
    return out;
}

// Victim modes 0 and 2: taking a hit adds to the victim's gauge, mode 0 dividing by 133 and
// mode 2 by 225, with the same limit clamp. Mode 0's arrival notifies id 5.
struct Rena0HitCharge {
    std::uint32_t mode = 0;
    std::uint32_t blocked0 = 0;
    std::uint32_t blocked2 = 0;
    std::uint32_t charge0 = 0;
    std::uint32_t charge2 = 0;
    std::uint32_t limit = 1000;
};

inline Rena0ChargeEffects advance_rena0_hit_charge(Rena0HitCharge& s, std::int32_t base,
                                                   std::int32_t scale, std::int32_t defense,
                                                   std::int32_t modifier, int victim) {
    Rena0ChargeEffects out;
    const auto mode = std::uint8_t(s.mode);
    if (mode != 0 && mode != 2) return out;
    if (std::uint8_t(mode == 0 ? s.blocked0 : s.blocked2)) return out;
    auto& charge = mode == 0 ? s.charge0 : s.charge2;
    if (charge_signed(charge) >= charge_signed(s.limit)) return out;
    auto amount = charge_divide(charge_multiply(base, scale), mode == 0 ? 133 : 225);
    amount = charge_divide(charge_multiply(amount, defense), 100);
    amount = charge_divide(charge_multiply(amount, modifier), 100);
    charge += std::uint32_t(amount);
    if (charge_signed(charge) >= charge_signed(s.limit)) {
        if (mode == 0) out.notified.push_back(5);  // host.notify(victim, 5)
        charge = s.limit;
    }
    (void)victim;
    return out;
}
}  // namespace gameplay::native
