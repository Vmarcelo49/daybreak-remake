#pragma once
#include "frontend/story_ladder.h"
#include <array>
#include <cstdint>
#include <memory>
#include <string>

namespace ui {
// FUN_00409340 panel geometry: 0/1 blue, 2/3 red. The 1v1 match uses upper panels.
inline constexpr int kFrontendBattleSlots[2] = {0, 2};
// FUN_0040d130 copies these choices into DAT_006cfb28/38/48/4c; controller 4 is COM.
struct FrontendSlot {
    int character = -1, weapon = 0, hypermode = 0, costume = 0, controller = 4;
    bool ready = false;
};
struct ResultSlotStats { int kos = 0, deaths = 0, damageDealt = 0, damageTaken = 0; };
struct OnlineContext;
struct FrontendState {
    // Online play's room, while there is one. Native builds only (frontend/screen_online.h).
    std::shared_ptr<OnlineContext> online;
    // Why the last room or selection ended, for the online screens to say.
    std::string onlineMessage;
    // Online, how many machines' players the selection screen must wait for. 0 offline.
    int onlineHumans = 0;
    // Entering (or re-entering) the select scene. The original destroys the current scene and
    // constructs the next one through the factory on every switch (FUN_00657c80:51-58), and
    // scene 3's own constructor initialises every per-slot field the scene owns: cursor
    // +0x3c48, character +0x3c58, panel owner +0x3c80, controller phase +0x3c90, owned panel
    // +0x3ca0, controller +0x3cf8, weapon +0x3d08, hypermode +0x3d18, costume +0x3d28, ready
    // +0x3d38 and the per-slot mode flags +0x3cb0/+0x3cd4 to unset, plus the stage page flag
    // +0x3c40 and the stage pair +0x3d48/+0x3d4c to 0 (FUN_00408330:143-158; the corpus and the
    // live original on the Ghidra bridge agree). Nothing per-slot is read back from anywhere:
    // a battle->select return (FUN_00403b70 returns 3) is as clean as a title->select entry.
    //
    // Deliberately NOT touched, because the original keeps it outside the scene: the stage
    // page's settings (time limit DAT_006cf3c0, HP DAT_006cf3b8, gauge DAT_006cf3bc, balloons
    // DAT_006cf3b0/006cf3b4), the RNG, the round's outcome data, and the penalty flag
    // DAT_006cfdf1 (issue #20).
    void beginSelection() {
        slots = {};
        stage = 0;
        variation = 0;
        stagePage = false;
    }
    std::array<FrontendSlot, 4> slots{};
    // FRONTEND-PLAN §5.2: values are percentages, seconds, and a 0=random stage index.
    // timeLimit 0 is INFINITE, and it is the original's default: DAT_006cf3c0 sits in .data's
    // bss tail (past the raw data, so the loader zeroes it) and the only write to it anywhere
    // is the menu's own cycle (FUN_0040acb0:53), so the game opens on "no limit". The port
    // shipped 180 — the third stop of five, a port choice, not a recovered value.
    // FUN_0040cd00:44 branches on `== 0` to draw the infinity glyph, which the row already does.
    int stage = 0, variation = 0, timeLimit = 0, health = 100, gauge = 100;
    int blueBalloon = 100, redBalloon = 100;
    bool stagePage = false;
    // Seeded locally so captures and scripted menu runs reproduce FUN_0040d130's random choices.
    uint32_t randomState = 0x6d2b79f5u;
    uint32_t nextRandom() {
        randomState = randomState * 1664525u + 1013904223u;
        return randomState >> 8;
    }
    // --story names one script for scene 8 to play alone; otherwise the ladder chooses.
    std::string storyScript;
    StoryLadder story;
    int resultWinner = 0;
    std::array<ResultSlotStats, 4> resultStats{};
    // Outcome numbers the result screen's quote rule reads (issue #20): the round's balloon
    // margin and whether BOTH winners ended below half HP (FUN_00635d40:288-318), plus the
    // match frame the quote alternative is picked from. The host measures them when the round
    // resolves; they are outcome data, not settings.
    int resultMargin = 0;
    bool resultWinnersHurt = false;
    uint64_t matchFrame = 0;
    // SESSION state, never persisted (issue #19 owns permanent settings; the original keeps
    // these in process globals too):
    //   resultTitleText — the earned title each panel's fighter ended the round with, as the
    //                   original's own name text (FUN_00430880's index into the table at VA
    //                   0x6b7308, resolved by the host);
    //   penaltyDecided— the original's per-player penalty flag DAT_006cfdf1, set when a player
    //                   earns the penalty title (FUN_00635d40:377-380) and cleared when the
    //                   panel is COM (FUN_0040d130:99-101). The port keys it by PANEL, which is
    //                   a local player's stable identity (the original keys it by netplay slot
    //                   and remembers the slot's panel in DAT_006cfdd9).
    std::array<std::string, 4> resultTitleText{};
    std::array<bool, 4> penaltyDecided{{false, false, false, false}};
};
}
