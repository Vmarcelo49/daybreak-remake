// P2-7 (2e) charge family — the mode-gauge state the port does not have yet.
//
// The recovered rules live in `rena0_charge_observation.h` (attacker mode 1 at
// 0x63844e..0x6384fa; victim modes 0/2 at 0x6382d9..0x63844e). This header is the *state*
// those rules accumulate into, with the two things the port's own comment says are missing
// (`fighter.cpp:1254-1262`): the original's mode gauges are the **+0x838/+0x840/+0x83C**
// counters, and the record's **combat[5]/[6]** columns feed them
// (FUN_00637950's sites 0x638321 / 0x6383e6 / 0x638493) — columns the port parses but
// deliberately leaves unread because its own `gain_gauge` feeds the *hypermode bar*, a
// different mechanic with a different consumer.
//
// The limits are per-character and already available: they are the actor DAT's six header
// dwords, which `CharacterMoves::parse` reads and `header_values()` exposes — `[0]` limit0,
// `[1]` duration0, `[4]` limit1, `[5]` duration1 (`development_animated_combat.hpp:642`).
// The scaling inputs are the hit record's `combat[5]` (victim base) and `combat[6]` (attacker
// base), the match's charge scale (shipped default 100) and the damage chain's defense and
// modifier (default 100 each when nothing modifies them).
#pragma once

#include "gameplay/native/rena0_charge_observation.h"

#include <cstdint>

namespace gameplay::native {

struct Rena0ModeGaugeLimits {
    std::uint32_t limit0 = 0;
    std::uint32_t duration0 = 0;
    std::uint32_t limit1 = 0;
    std::uint32_t duration1 = 0;
};

// The six actor DAT header dwords, in the layout the parser already reads.
inline Rena0ModeGaugeLimits rena0_mode_gauge_limits(const int* headerValues) {
    Rena0ModeGaugeLimits out;
    if (!headerValues) return out;
    out.limit0 = static_cast<std::uint32_t>(headerValues[0]);
    out.duration0 = static_cast<std::uint32_t>(headerValues[1]);
    out.limit1 = static_cast<std::uint32_t>(headerValues[4]);
    out.duration1 = static_cast<std::uint32_t>(headerValues[5]);
    return out;
}

// One actor's three gauges, exactly as `BattleSpecialGauges` holds them, minus the
// presentation and host fields this pilot does not need yet.
struct Rena0ModeGauges {
    Rena0ModeGaugeLimits limits;
    std::uint32_t mode = 0;  // the wire mode (+0x318): Oyashiro 0, Friendship 1, Kakera 2
    std::uint32_t charge0 = 0, charge1 = 0, charge2 = 0;
    std::uint32_t ready1 = 0;
    bool active0 = false, active1 = false, active2 = false;
    long long notify5 = 0;  // victim-side arrivals (mode 0)
    long long notify6 = 0;  // attacker-side arrivals (mode 1)

    // A landed hit: the victim side accumulates through mode 0/2, the attacker side through
    // mode 1. The mode gates live in the adapted bodies, so these only build their inputs.
    void on_victim_hit(std::int32_t victimBase, std::int32_t chargeScale, std::int32_t defense,
                       std::int32_t modifier) {
        Rena0HitCharge victim;
        victim.mode = mode;
        victim.blocked0 = active0 ? 1u : 0u;
        victim.blocked2 = active2 ? 1u : 0u;
        victim.charge0 = charge0;
        victim.charge2 = charge2;
        victim.limit = limits.limit0;
        const Rena0ChargeEffects victimEffects =
            advance_rena0_hit_charge(victim, victimBase, chargeScale, defense, modifier, 0);
        charge0 = victim.charge0;
        charge2 = victim.charge2;
        notify5 += static_cast<long long>(victimEffects.notified.size());
    }

    void on_attacker_hit(std::int32_t attackerBase, std::int32_t chargeScale) {
        Rena0AttackCharge attacker;
        attacker.mode = mode;
        attacker.blocked = active1 ? 1u : 0u;
        attacker.charge = charge1;
        attacker.limit = limits.limit1;
        attacker.ready = ready1;
        const Rena0ChargeEffects attackerEffects =
            advance_rena0_attack_charge(attacker, attackerBase, chargeScale, 0);
        charge1 = attacker.charge;
        ready1 = attacker.ready;
        notify6 += static_cast<long long>(attackerEffects.notified.size());
    }

    // Both sides at once, for a caller that owns both actors (the offline tests do).
    void on_hit(std::int32_t victimBase, std::int32_t attackerBase, std::int32_t chargeScale,
                std::int32_t defense, std::int32_t modifier) {
        on_victim_hit(victimBase, chargeScale, defense, modifier);
        on_attacker_hit(attackerBase, chargeScale);
    }

    // --- the recovered control around the gauges (battle_special_gauges.hpp) ---------------
    //
    // Activation: the caller owns admission, the action transition and notification 7; these
    // are the primitives (the original's 421fe0 / 4220e0 / 422160). Mode 2 restores health.
    void begin0() {
        charge0 = limits.duration0;
        active0 = true;
    }
    void begin1() {
        charge1 = limits.duration1;
        active1 = true;
    }
    void begin2(std::uint32_t& health) {
        health = 10000;
        charge2 = limits.duration0;
        active2 = true;
    }

    // The chords that admit an activation: melee and shoot both in 1..2, an action window, and
    // the gauge already at its limit. `action` is the actor's action id.
    bool accepts_mode0_chord(int action, unsigned melee, unsigned shoot) const {
        return (mode & 255u) == 0 && !active0 && !active1 && !active2 && melee > 0 && melee < 3 &&
               shoot > 0 && shoot < 3 &&
               (action < 118 || (action > 129 && action < 180) ||
                (action > 199 && action < 218) || (action > 229 && action < 280)) &&
               charge_signed(charge0) >= charge_signed(limits.limit0);
    }
    bool accepts_mode1_chord(int action, unsigned melee, unsigned shoot) const {
        return (mode & 255u) == 1 && !active0 && !active1 && !active2 && melee > 0 && melee < 3 &&
               shoot > 0 && shoot < 3 && (action < 100 || action > 299) &&
               charge_signed(charge1) >= charge_signed(limits.limit1);
    }

    // The per-tick refill step the original uses when a gauge is being restored.
    unsigned refill_step() const { return active2 ? 2u : active0 ? 1u : active1 ? 3u : 1u; }

    // The consumption tick (original 41f73c..41f8e3, outside the hitstop gate). Mode 0 and 1
    // spend their gauge down; mode 2 advances the movement gauge toward 1000 and drains health
    // by 7 a tick, ending itself when health would fall below 9 (and setting it to 1) or is
    // already below 1. `health` and `movementGauge` are the caller's, because this state is an
    // observation of the original's rules, not a port behaviour: the pilot never writes them.
    void tick(std::uint32_t& health, int& movementGauge) {
        const std::uint32_t wireMode = mode & 255u;
        if (wireMode == 0) {
            if (active0) {
                --charge0;
                if (charge_signed(charge0) <= 0) {
                    charge0 = 0;
                    active0 = false;
                }
            }
        } else if (wireMode == 1) {
            if (active1) {
                --charge1;
                if (charge_signed(charge1) <= 0) {
                    charge1 = 0;
                    active1 = false;
                }
            }
        } else if (wireMode == 2) {
            if (active2) {
                if (movementGauge < 1000) ++movementGauge;
                if (charge_signed(health) < 1) {
                    charge2 = 0;
                    active2 = false;
                } else if (charge_signed(health) < 9) {
                    health = 1;
                    charge2 = 0;
                    active2 = false;
                } else {
                    health -= 7;
                }
            }
        }
    }
};
}  // namespace gameplay::native
