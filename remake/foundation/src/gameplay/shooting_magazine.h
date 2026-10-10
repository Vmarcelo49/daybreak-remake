#pragma once

#include "gameplay/weapon_definition.h"
#include <cstdint>
#include <cstring>

namespace gameplay {

// FUN_00433eb0's 0x44-byte magazine is round-counted; reloadTime is a refill
// threshold, not a cost paid when selecting a shot tier. Keep this separate from
// provisional AmmoStock until request-time admission owns all bound shooting paths.
struct ShootingMagazine {
    std::uint32_t mode = 0, capacity = 0, reloadThreshold = 0, shotInterval = 0;
    std::uint32_t refillStep = 1, rounds = 0, reloadProgress = 0, cooldown = 0;
    std::uint32_t initialHold = 0, laterHold = 0, chargeStage = 0, flags = 0, display = 0;

    static ShootingMagazine from_definition(const MagazineDefinition& definition) {
        ShootingMagazine result;
        result.mode = static_cast<std::uint32_t>(definition.type);
        result.capacity = result.rounds = static_cast<std::uint32_t>(definition.num);
        result.reloadThreshold = static_cast<std::uint32_t>(definition.reloadTime);
        result.shotInterval = result.cooldown = static_cast<std::uint32_t>(definition.intervalTime);
        return result;
    }

    // Original comparisons are signed, while increment/multiply wrap PE32 words.
    static std::int32_t signed_word(std::uint32_t word) {
        std::int32_t result;
        std::memcpy(&result, &word, sizeof(result));
        return result;
    }

    // FUN_00435660 retains reload/cooldown progress and the flags' high word.
    void reset() {
        rounds = capacity;
        initialHold = laterHold = chargeStage = 0;
        flags &= 0xffff0000u;
    }

    // FUN_00435920: mutation precedes pool creation, even if that creation fails.
    bool consume() {
        if (rounds == 0 || signed_word(cooldown) < signed_word(shotInterval)) return false;
        if (rounds == capacity) reloadProgress = 0;
        --rounds;
        cooldown = 0;
        if (rounds == 0) reloadProgress = 0;
        return true;
    }

    // FUN_004356b0 runs once per authoritative tick. Empty mode-2 magazines refill
    // in capacity/2-tick pulses, unlike partially depleted magazines' continuous refill.
    void tick() {
        const auto less = [](std::uint32_t left, std::uint32_t right) {
            return signed_word(left) < signed_word(right);
        };
        if (rounds != 0) flags &= 0xffff00ffu;
        if (mode == 2) {
            if (rounds == 0) {
                ++cooldown;
                if (signed_word(cooldown) >= signed_word(capacity) / 2) {
                    cooldown = 0;
                    reloadProgress += refillStep;
                }
                if (!less(reloadProgress, reloadThreshold)) {
                    rounds = capacity;
                    cooldown = shotInterval;
                    flags = (flags & 0xffff00ffu) | 0x100u;
                }
            } else if (less(rounds, capacity)) {
                reloadProgress += refillStep;
                if (!less(reloadProgress, reloadThreshold)) {
                    ++rounds;
                    reloadProgress = 0;
                }
            }
            display = rounds * reloadThreshold + reloadProgress;
        } else if (mode == 1) {
            if (less(rounds, capacity)) {
                reloadProgress += refillStep;
                if (!less(reloadProgress, reloadThreshold)) {
                    ++rounds;
                    reloadProgress = 0;
                }
            }
            display = rounds * reloadThreshold + reloadProgress;
        } else {
            if (rounds == 0) {
                reloadProgress += refillStep;
                if (!less(reloadProgress, reloadThreshold)) {
                    rounds = capacity;
                    cooldown = shotInterval;
                    flags = (flags & 0xffff00ffu) | 0x100u;
                }
            }
            display = rounds;
        }
        if (less(cooldown, shotInterval)) ++cooldown;
        if ((flags & 0xffu) == 0) initialHold = laterHold = chargeStage = 0;
        else flags &= 0xffffff00u;
    }
};
} // namespace gameplay
