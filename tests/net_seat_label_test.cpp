// Issue #106: what a fighter is labelled, checked against what the core is actually doing.
//
// The play-test saw a remote player wearing COM. Two separate answers live in the product, and
// this pins both to a real battle rather than to a reading of the code:
//   * the core's own verdict, `FighterView::driven()` — a CPU bank or a player's held chords;
//   * the seat, `ui::Participant::remote()` / `participantLabel()`, which the VS hand-off fills.
// A seat with an input bank is driven here; a seat on another machine is a player even
// without one; a fighter nobody plays must read COM in the labels and have no bank.
// Tier 4 at most: our own build, and nothing about the original, which has no online mode.
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "battle/core_battle.h"
#include "frontend/participants.h"

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
    ui::FrontendSlot slots[4];
    slots[0].character = 0;
    slots[0].controller = 0;
    slots[2].character = 4;
    slots[2].controller = 1;
    slots[1].character = 1;
    slots[3].character = 2;
    for (ui::FrontendSlot& slot : slots) {
        slot.peer = slot.controller < 4 ? slot.controller : -1;
        slot.local = slot.controller == 1;
        slot.controller = slot.local ? 0 : 4;
    }
    ui::Participant roster[ui::kParticipantCount];
    const int count = ui::buildParticipants(slots, roster);
    check(count == 4, "the selection yields four seats");

    // Which core slot each panel's roster entry is, as the host's launch does it.
    int fighterOf[4] = {0, 1, 2, 3};
    for (int i = 0; i < count; ++i) roster[i].fighter = fighterOf[roster[i].panel];

    check(std::strcmp(ui::participantLabel(roster[0]), "1P") == 0, "a player on another machine is 1P, not COM");
    check(std::strcmp(ui::participantLabel(roster[2]), "1P") == 0, "this machine's player is 1P");
    check(std::strcmp(ui::participantLabel(roster[1]), "COM") == 0 &&
          std::strcmp(ui::participantLabel(roster[3]), "COM") == 0, "a fighter nobody plays is COM");

    // The core has prepared no bank for anyone yet, so nothing here is driven.
    check(!battle.fighter(0).driven(), "an untouched fighter has no bank");
    check(roster[0].remote() && roster[0].human(), "the remote seat is a human that this machine does not drive");

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
