// =============================================================================
//  frontend_lifecycle_test.cpp — what a front-end screen entry may and may not clear
//  (issue #45).
//
//  The selection belongs to the select scene, not to the process. The original destroys the
//  current scene and constructs the next one through the factory on every switch
//  (FUN_00657c80:51-58), and scene 3's constructor initialises every per-slot field it owns
//  (FUN_00408330:143-158), so a title->select round trip and a battle->select return
//  (FUN_00403b70 returns 3 in versus mode) both start with an empty selection.
//
//  What the original keeps in PROCESS globals has to survive that entry: the stage page's
//  time limit DAT_006cf3c0, HP DAT_006cf3b8, gauge DAT_006cf3bc and balloons
//  DAT_006cf3b0/006cf3b4, the RNG, the round's outcome data the results present, the penalty
//  flag DAT_006cfdf1 (issue #20) and the permanent settings document (issue #19).
//
//  No device, no window, no game data: the port's factory ui::makeScreen is driven with a
//  device-less SpriteRenderer, so the screen itself is refused for lack of its atlas AFTER the
//  entry has run, and every assertion is on the FrontendState and the settings singleton the
//  application hands in.
//
//    ctest -R frontend_lifecycle_test
// =============================================================================

#include <cstdio>
#include <memory>
#include <string>

#include "ui/frontend_settings.h"
#include "ui/frontend_state.h"
#include "ui/screen.h"

namespace {

int g_checks = 0;
int g_failed = 0;

void checkTrue(const char* what, bool ok) {
    ++g_checks;
    if (ok) std::printf("  [ok]   %s\n", what);
    else { std::printf("  [FAIL] %s\n", what); ++g_failed; }
}

void checkInt(const char* what, long long want, long long got) {
    ++g_checks;
    if (want == got) std::printf("  [ok]   %s = %lld\n", what, got);
    else { std::printf("  [FAIL] %s: want %lld, got %lld\n", what, want, got); ++g_failed; }
}

// A selection as a player leaves the select scene: four panels picked (character + weapon
// combos, rule 7), a stage page configured, and the session/outcome state a finished round
// leaves behind — the winner the results present, the quote numbers issue #20 reads, the
// penalty flag keyed by panel, and the RNG's position.
void pickAsAPlayerWould(ui::FrontendState& state) {
    state.slots[0] = {4, 1, 2, 3, 0, true};
    state.slots[1] = {2, 0, 1, 4, 1, true};
    state.slots[2] = {12, 0, 0, 0, 2, true};
    state.slots[3] = {1, 1, 2, 1, 3, true};
    state.stage = 5;
    state.variation = 1;
    state.stagePage = true;
    state.timeLimit = 60;
    state.health = 50;
    state.gauge = 100;
    state.blueBalloon = 40;
    state.redBalloon = 40;
    state.randomState = 12345u;
    state.resultWinner = 1;
    state.resultStats[2] = {2, 1, 300, 150};
    state.resultMargin = 21;
    state.resultWinnersHurt = true;
    state.matchFrame = 3600;
    state.resultTitleText[2] = "penalty";
    state.penaltyDecided[2] = true;
}

// Every panel back to FrontendSlot's own defaults: the port's spelling of the unset sentinels
// FUN_00408330:143-158 writes (cursor/-owner/-controller/-weapon/-hypermode/-costume -1, the
// ready and mode flags 0), plus the page and stage fields of the same constructor.
void checkSelectionEmpty(const ui::FrontendState& state) {
    char what[64];
    for (int panel = 0; panel < 4; ++panel) {
        std::snprintf(what, sizeof(what), "panel %d character unset", panel);
        checkInt(what, -1, state.slots[panel].character);
        std::snprintf(what, sizeof(what), "panel %d weapon unset", panel);
        checkInt(what, 0, state.slots[panel].weapon);
        std::snprintf(what, sizeof(what), "panel %d hypermode unset", panel);
        checkInt(what, 0, state.slots[panel].hypermode);
        std::snprintf(what, sizeof(what), "panel %d costume unset", panel);
        checkInt(what, 0, state.slots[panel].costume);
        std::snprintf(what, sizeof(what), "panel %d back to COM", panel);
        checkInt(what, 4, state.slots[panel].controller);
        std::snprintf(what, sizeof(what), "panel %d not ready", panel);
        checkTrue(what, !state.slots[panel].ready);
    }
    checkInt("stage back to random (+0x3d48)", 0, state.stage);
    checkInt("stage variation back to 0 (+0x3d4c)", 0, state.variation);
    checkTrue("the stage page is closed (+0x3c40)", !state.stagePage);
}

// The values the original keeps outside the scene (process globals / the settings document).
void checkSessionSurvives(const ui::FrontendState& state) {
    checkInt("time limit survives", 60, state.timeLimit);
    checkInt("health survives", 50, state.health);
    checkInt("gauge survives", 100, state.gauge);
    checkInt("blue balloon survives", 40, state.blueBalloon);
    checkInt("red balloon survives", 40, state.redBalloon);
    checkInt("the RNG keeps its position", 12345, (long long)state.randomState);
    checkInt("the winning side survives", 1, state.resultWinner);
    checkInt("the round's margin survives", 21, state.resultMargin);
    checkTrue("the winners-hurt flag survives", state.resultWinnersHurt);
    checkInt("the match frame survives", 3600, (long long)state.matchFrame);
    checkInt("the round's stats survive", 300, state.resultStats[2].damageDealt);
    checkTrue("the earned title survives", state.resultTitleText[2] == "penalty");
    checkTrue("the penalty flag survives", state.penaltyDecided[2]);
    checkTrue("the permanent settings survive", ui::frontendSettings().fullscreen);
}

}  // namespace

int main() {
    ui::SpriteRenderer batch;   // no device: a screen that needs art cannot be built
    std::string error;

    // A permanent setting (issue #19's document) is not part of any selection.
    ui::frontendSettings().fullscreen = true;

    ui::FrontendState state;
    pickAsAPlayerWould(state);

    // Leaving the select scene for the title: only the select scene's own construction owns the
    // selection, so entering another screen must leave it alone.
    std::printf("leaving select for the title:\n");
    checkTrue("a title entry builds no screen without a device",
              !ui::makeScreen(ui::ScreenId::Title, batch, state, error));
    checkInt("the picks survive leaving select", 4, state.slots[0].character);
    checkTrue("the stage page survives leaving select", state.stagePage);
    checkSessionSurvives(state);

    // Re-entering is a new scene, so the selection is gone and the session is not.
    std::printf("re-entering select with a previous round's picks:\n");
    const std::unique_ptr<ui::Screen> select =
        ui::makeScreen(ui::ScreenId::Select, batch, state, error);
    checkTrue("the select screen needs its atlas (no device here)", select == nullptr);
    checkSelectionEmpty(state);
    checkSessionSurvives(state);

    // A second entry is the same construction: a selection made after the first entry is
    // cleared by the next one exactly as the first was.
    std::printf("re-entering select a second time:\n");
    pickAsAPlayerWould(state);
    checkInt("the selection is back before the re-entry", 4, state.slots[0].character);
    checkTrue("the second select entry builds no screen without a device",
              !ui::makeScreen(ui::ScreenId::Select, batch, state, error));
    checkSelectionEmpty(state);

    std::printf("\nfrontend_lifecycle_test: %d checks, %d failure(s)\n", g_checks, g_failed);
    return g_failed ? 1 : 0;
}
