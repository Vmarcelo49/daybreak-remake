#pragma once

#include "gameplay/weapon_definition.h"
#include <array>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace gameplay {

// FUN_00433eb0's 0x44-byte magazine is round-counted; reloadTime is a refill
// threshold, not a cost paid when selecting a shot tier.
struct ShootingMagazine {
    std::uint32_t mode = 0, capacity = 0, reloadThreshold = 0, shotInterval = 0;
    std::uint32_t refillStep = 1, rounds = 0, reloadProgress = 0, cooldown = 0;
    std::uint32_t initialHold = 0, laterHold = 0, chargeStage = 0, flags = 0, display = 0;
    std::uint32_t chargeThreshold = 0, maxChargeStage = 0;

    static ShootingMagazine from_definition(const MagazineDefinition& definition) {
        ShootingMagazine result;
        result.mode = static_cast<std::uint32_t>(definition.type);
        result.capacity = result.rounds = static_cast<std::uint32_t>(definition.num);
        result.reloadThreshold = static_cast<std::uint32_t>(definition.reloadTime);
        result.shotInterval = result.cooldown = static_cast<std::uint32_t>(definition.intervalTime);
        result.chargeThreshold = static_cast<std::uint32_t>(definition.chargeMax);
        result.maxChargeStage = static_cast<std::uint32_t>(definition.chargeLevel);
        result.display = result.mode == 1 || result.mode == 2
            ? result.rounds * result.reloadThreshold : result.rounds;
        return result;
    }

    float fraction() const {
        const bool incremental = mode == 1 || mode == 2;
        const double maximum = incremental ? double(capacity) * reloadThreshold : capacity;
        const double current = incremental ? double(rounds) * reloadThreshold + reloadProgress : rounds;
        return maximum > 0 ? static_cast<float>(std::clamp(current / maximum, 0.0, 1.0)) : 0.f;
    }

    // Mid-match weapon replacement preserves stock fill (port swap policy).
    void preserve_fraction(float fraction) {
        const double total = std::clamp(fraction, 0.f, 1.f) * double(capacity);
        rounds = static_cast<std::uint32_t>(total);
        reloadProgress = mode == 1 || mode == 2
            ? static_cast<std::uint32_t>((total - rounds) * reloadThreshold) : 0;
    }

    // FUN_0043f3e0 charges only a non-empty magazine. The common tick consumes
    // the hold flag, so callers must assert it anew on every held logic update.
    std::uint32_t charge() {
        if (rounds == 0) return 0;
        flags = (flags & 0xffffff00u) | 1u;
        if (chargeStage == 0) {
            ++initialHold;
            if (signed_word(initialHold) > 29) {
                if (maxChargeStage == 1) {
                    chargeStage = maxChargeStage;
                    initialHold = 30;
                } else ++chargeStage;
            }
        } else if (signed_word(maxChargeStage) > 1) {
            ++laterHold;
            if (signed_word(laterHold) >= signed_word(chargeThreshold)) {
                if (signed_word(chargeStage + 1u) < signed_word(maxChargeStage)) {
                    laterHold = 0;
                    ++chargeStage;
                } else {
                    chargeStage = maxChargeStage;
                    laterHold = chargeThreshold;
                }
            }
        }
        return chargeStage;
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

    bool can_consume() const {
        return rounds != 0 && signed_word(cooldown) >= signed_word(shotInterval);
    }

    // FUN_00435920: mutation precedes pool creation, even if that creation fails.
    bool consume() {
        if (!can_consume()) return false;
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
// FUN_00435450: row+8 selects the 0x44-byte magazine before pool creation.
// Invalid metadata is an error, while any negative index is an unmetered row.
inline bool admit_shooting_row(const WeaponDefinition& weapon, int row,
                               std::array<ShootingMagazine, 2>& magazines) {
    if (row < 0 || row >= weapon.bulletCount || !weapon.bullets)
        throw std::out_of_range("shooting callback item row");
    const int magazine = weapon.bullets[row].magazine;
    if (magazine < 0) return true;
    if (magazine >= static_cast<int>(magazines.size()))
        throw std::out_of_range("shooting callback magazine index");
    return magazines[static_cast<size_t>(magazine)].consume();
}
} // namespace gameplay
