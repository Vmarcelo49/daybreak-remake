#pragma once
#include <array>
#include <cstdint>

namespace ui {
// FUN_00409340 panel geometry: 0/1 blue, 2/3 red. The 1v1 match uses upper panels.
inline constexpr int kFrontendBattleSlots[2] = {0, 2};
// FUN_0040d130 copies these choices into DAT_006cfb28/38/48/4c; controller 4 is COM.
struct FrontendSlot {
    int character = -1, weapon = 0, hypermode = 0, costume = 0, controller = 4;
    bool ready = false;
};
struct ResultSlotStats { int kos = 0, deaths = 0, damageDealt = 0, damageTaken = 0; };
struct FrontendState {
    std::array<FrontendSlot, 4> slots{};
    // FRONTEND-PLAN §5.2: values are percentages, seconds, and a 0=random stage index.
    int stage = 0, variation = 0, timeLimit = 180, health = 100, gauge = 100;
    int blueBalloon = 100, redBalloon = 100;
    bool stagePage = false;
    // Seeded locally so captures and scripted menu runs reproduce FUN_0040d130's random choices.
    uint32_t randomState = 0x6d2b79f5u;
    uint32_t nextRandom() {
        randomState = randomState * 1664525u + 1013904223u;
        return randomState >> 8;
    }
    int resultWinner = 0;
    std::array<ResultSlotStats, 4> resultStats{};
};
}
