// P2-7 (2e) shot family — the recovered Rena ground-shot body, adapted for offline
// observation with attribution.
//
// Adapted from the local bundle's `battle_rena_ground_shot.hpp` (DaybreakRebuild-20261010),
// which the owner's 2026-10-14 licence note allows vendoring with attribution. The body is
// reproduced faithfully, including the ORDERED event list the original publishes; only the
// host-side plumbing changed:
//
//   * the event sink is a returned `std::vector` instead of a callback, so a test can pin the
//     ordering without a host;
//   * `BattleRandom` is not bound: the recovered body uses it only in weapon 2's scatter,
//     which is not adapted (see below), so no RNG service is needed here;
//   * `character_action_dispatch(0, weapon)`'s result is unused by the body (the original's
//     dispatch side effects live in the host), so it is a documented no-op here;
//   * `legacy_trig` and its 3600-entry cosine table are NOT adapted. Weapon 2's scatter is the
//     only caller, so `weapon == 2` fails loudly with that reason instead of returning a
//     silent empty result. Rena+0 is weapon slot 0, the pilot combo.
//
// This is an observation module: it takes scalars and returns what the recovered body would
// do. It is not wired to the default path (see tests/rena0_resolver_test.cpp's scan).
#pragma once

#include "gameplay/native/rena0_steering.h"

#include <algorithm>
#include <array>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace gameplay::native {

// The recovered event kinds, in the bundle's spelling.
enum class Rena0ShotEventKind {
    activate,
    melee_statistics,
    shot_statistics,
    model,
    sound,
    voice,
    attachment_projectile,
    world_projectile,
    clear_contact,
    contact_capacity,
    strike,
};

struct Rena0ShotEvent {
    Rena0ShotEventKind kind = Rena0ShotEventKind::activate;
    int id = 0;
    int slot = 0;
    std::array<float, 3> position{};
    float yaw = 0.f;
    float pitch = 0.f;
    // The host resolves this predicate at the ordered voice call: a preceding projectile
    // request can consume rounds before the original reads the count.
    bool voice_current_rounds = false;
    int voice_other = -1;
};

struct Rena0GroundShotMotion {
    int phase = 0;
    int frame = 0;
    int pitch = 0;
    float speed = 0.f;
    float offset = 0.f;
    float movement = 0.f;
    float gravity = 0.f;
};

struct Rena0GroundShotInput {
    bool complete = false;
    bool grounded = true;
    bool special = false;
    int rounds = 0;
    float elevation = 0.f;
    float heading = 0.f;
    std::array<float, 3> position{};
};

struct Rena0GroundShotEffects {
    int next_state = -1;
    std::vector<Rena0ShotEvent> events;
};

// State 400's body after the common update prelude (model slots 0/1 and strike off). The
// ordered requests are intentional: weapon 2 counts ten secondary shots but not its leading
// attachment request, and weapon 1 can request two projectiles for one shot-statistics call.
// The host performs the actual magazine admission and resource resolution per request.
inline Rena0GroundShotEffects advance_rena0_ground_shot(unsigned weapon,
                                                        Rena0GroundShotMotion& s,
                                                        const Rena0GroundShotInput& in) {
    Rena0GroundShotEffects out;
    if (in.complete) {
        out.next_state = 0;
        return out;
    }
    if (!in.grounded) {
        out.next_state = 43;
        s.gravity = .5f;
        return out;
    }
    if (weapon > 1)
        throw std::invalid_argument(
            "Rena+2's shot branch needs the legacy cosine table (legacy_trig), which is not "
            "adapted; the pilot combo is weapon slot 0");

    const auto emit = [&](Rena0ShotEventKind kind, int id = 0, int slot = 0) {
        out.events.push_back(Rena0ShotEvent{kind, id, slot});
    };
    const auto attachment = [&](int bullet, float pitch = 0.f) {
        Rena0ShotEvent e{Rena0ShotEventKind::attachment_projectile, bullet, 0};
        e.pitch = pitch;
        out.events.push_back(e);
    };
    const auto round_voice = [&](int other) {
        Rena0ShotEvent e{Rena0ShotEventKind::voice, in.rounds == 1 ? 30 : other, 10};
        e.voice_current_rounds = true;
        e.voice_other = other;
        out.events.push_back(e);
    };
    const bool first = s.phase == 0 && s.frame == 0;
    if (first) {
        emit(Rena0ShotEventKind::activate);
        if (weapon == 1) emit(Rena0ShotEventKind::melee_statistics);
    }
    if (weapon == 0) {
        if (s.frame > 11) {
            emit(Rena0ShotEventKind::model, -1, 0);
            emit(Rena0ShotEventKind::model, -1, 1);
        }
        if (s.frame < 12) approach_battle_offset(s.offset, 0.f, 20.f);
        if (s.phase == 0) s.speed = std::max(0.f, s.speed - .5f);
        if (s.frame == 12) {
            emit(Rena0ShotEventKind::sound, 70);
            s.pitch = std::clamp(int(in.elevation), -30, 30);
            emit(Rena0ShotEventKind::shot_statistics);
            round_voice(27);
            attachment(in.special ? 6 : 0, float(s.pitch));
        }
    } else {
        if (s.frame < 15) approach_battle_offset(s.offset, 0.f, 20.f);
        if (s.phase == 0) {
            if (s.frame == 0) {
                s.movement = 0.f;
                emit(Rena0ShotEventKind::clear_contact);
                emit(Rena0ShotEventKind::contact_capacity, 1);
            }
            approach_battle_offset(s.offset, 0.f, 15.f);
            s.speed = std::max(0.f, s.speed - .5f);
        }
        if (s.frame == 7) s.speed = 45.f;
        if (s.frame == 15) {
            emit(Rena0ShotEventKind::sound, 67);
            emit(Rena0ShotEventKind::voice, 29, 10);
            s.speed = 0.f;
        }
        if (s.frame == 18) {
            emit(Rena0ShotEventKind::sound, 77);
            emit(Rena0ShotEventKind::shot_statistics);
            if (in.special) {
                attachment(0);
                attachment(9);
            } else {
                attachment(6);
            }
        }
        emit(Rena0ShotEventKind::strike, s.frame >= 8 && s.frame <= 18 ? 1 : 0);
    }
    return out;
}

// The bundle's own convenience overload ignores the event list; kept so a caller that only
// wants the state proposal cannot accidentally drop the events silently.
inline int advance_rena0_ground_shot_next_state(unsigned weapon, Rena0GroundShotMotion& s,
                                                const Rena0GroundShotInput& in) {
    return advance_rena0_ground_shot(weapon, s, in).next_state;
}
}  // namespace gameplay::native
