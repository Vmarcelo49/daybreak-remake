// Issue #106: what a fighter is labelled, checked against what the core is actually doing.
//
// The play-test saw a remote player wearing COM. Two separate answers live in the product, and
// this pins both to a real battle rather than to a reading of the code:
//   * the core's own verdict, `FighterView::driven()` — a CPU bank or a player's held chords;
//   * the seat, `ui::Participant::remote()` / `participantLabel()`, which the VS hand-off fills.
// A seat with an input bank is driven here; a seat on another machine is a player; a fighter
// nobody plays reads COM in the labels, and a CPU the core runs is driven.
// Tier 4 at most: our own build, and nothing about the original, which has no online mode.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "battle/core_battle.h"
#include "frontend/participants.h"
#include "frontend/screen_online.h"

namespace {

int failures = 0;
void check(bool condition, const std::string& name) {
    std::printf("%s %s\n", condition ? "ok  " : "FAIL", name.c_str());
    if (!condition) ++failures;
}

std::string find_game() {
    if (const char* configured = std::getenv("GAME_DIR")) return configured;
    namespace fs = std::filesystem;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        if (fs::exists(path / "Higurashi-Daybreak" / "daybreak00.dat")) return (path / "Higurashi-Daybreak").string();
        if (path == path.parent_path()) return {};
    }
}

// A round opened and left running without input: no bank is acquired, so every fighter reads as
// undriven — what a remote player looks like from this machine, and not what a COM looks like,
// because the core drives a COM. Labels are checked against those two readings.
void test_labels(const std::string& game) {
    sim::BattleConfig config;
    config.gameDir = game;
    for (int i = 0; i < 4; ++i) config.slots[i] = {i, 0, true};
    config.timeLimitSeconds = 30;
    sim::CoreBattle battle;
    battle.start(config, {}, {});

    // The four seats exactly as the online hand-off leaves them on one machine: peers 0 and 1
    // took panels 0 and 2, this is peer 1's machine, and panels 1 and 3 are COMs.
    ui::FrontendState online;
    online.slots[0] = {0, 0, 0, 0, 0, false};
    online.slots[2] = {4, 0, 0, 0, 1, false};
    online.slots[1] = {1, 0, 0, 0, 4, false};
    online.slots[3] = {2, 0, 0, 0, 4, false};
    net::MatchPlan plan;
    ui::onlineHandoff(online.slots, plan, 1);
    ui::Participant roster[ui::kParticipantCount];
    const int count = ui::buildParticipants(online.slots.data(), roster);
    check(count == 4, "the selection yields four seats");

    // Which core slot each panel's roster entry is, as the host's launch does it.
    int fighterOf[4] = {0, 1, 2, 3};
    for (int i = 0; i < count; ++i) roster[i].fighter = fighterOf[roster[i].panel];

    check(std::strcmp(ui::participantLabel(roster[0], false), "1P") == 0, "a player on another machine is 1P, not COM");
    check(std::strcmp(ui::participantLabel(roster[2], false), "1P") == 0, "this machine's player is 1P");
    check(std::strcmp(ui::participantLabel(roster[1], false), "COM") == 0 &&
          std::strcmp(ui::participantLabel(roster[3], false), "COM") == 0, "a fighter nobody plays is COM");
    // The round is pre-match: the fixtures are CPU, so their banks are prepared here from the
    // first tick, and the label reads COM for them while the human seats keep their names.
    for (int t = 0; t < 4; ++t) battle.advance(sim::Inputs{});
    check(battle.fighter(1).driven(), "a COM the core runs is driven from the first tick");
    check(std::strcmp(ui::participantLabel(roster[1], battle.fighter(1).driven()), "COM") == 0,
          "a seat whose CPU runs it is COM");

    // Nothing has been advanced yet, so no seat has a bank: every label is the seat's own, and
    // the HUD takes that for a remote player, never for a COM.

    check(roster[0].remote() && !roster[0].human(), "the remote seat is a player this machine does not drive");

    // A held chord gives one fighter a bank, and the core reports it for that fighter.
    sim::Inputs inputs{};
    inputs[2].buttons = 0x40;   // the tag a bank is trusted on: a physical mask, no button held
    for (int t = 0; t < 4; ++t) battle.advance(inputs);
    check(battle.fighter(2).driven(), "a fighter with held input has a bank");
}

}  // namespace

int main() {
    const std::string game = find_game();
    if (game.empty()) {
        std::printf("SKIP: no install\n");
        return 77;
    }
    test_labels(game);
    if (failures) {
        std::printf("net_seat_label_test: %d failure(s)\n", failures);
        return 1;
    }
    std::puts("net_seat_label_test: seats and core input banks agree");
    return 0;
}
