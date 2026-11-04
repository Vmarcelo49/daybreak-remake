// Issue #106: what a fighter is labelled, checked against what the core is actually doing.
//
// The play-test saw a remote player wearing COM. Two separate answers live in the product, and
// this pins both to a real battle rather than to a reading of the code:
//   * the battle's own verdict, `FighterView::cpuDriven()` — the core replaced that fighter's
//     input with a CPU decision on its last tick, which is exactly "nobody is playing this seat
//     on this machine";
//   * the seat, `ui::Participant::remote()` / `participantLabel()`, which the VS hand-off fills.
// A human seat, local or on another machine, is never CPU-driven; a configured COM is, from the
// first tick; a human slot handed to the CPU is, from the tick the hand-off lands.
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

// Two humans (slots 0 and 3) and two COMs (slots 1 and 2), as a 2v2 with one person on each side.
sim::BattleConfig mixedConfig(const std::string& game) {
    sim::BattleConfig config;
    config.gameDir = game;
    for (int i = 0; i < 4; ++i) config.slots[i] = {i, 0, i == 1 || i == 2};
    config.timeLimitSeconds = 30;
    return config;
}

// The four seats as the online hand-off leaves them on one machine: peers 0 and 1 took panels 0
// and 2, this is peer 1's machine, and panels 1 and 3 are COMs.
ui::FrontendState onlineState() {
    ui::FrontendState online;
    online.slots[0] = {0, 0, 0, 0, 0, false};
    online.slots[2] = {4, 0, 0, 0, 1, false};
    online.slots[1] = {1, 0, 0, 0, 4, false};
    online.slots[3] = {2, 0, 0, 0, 4, false};
    return online;
}

void test_online_labels(const std::string& game) {
    sim::CoreBattle battle;
    battle.start(mixedConfig(game), {}, {});

    ui::FrontendState online = onlineState();
    net::MatchPlan plan;
    ui::onlineHandoff(online.slots, plan, 1);
    ui::Participant roster[ui::kParticipantCount];
    const int count = ui::buildParticipants(online.slots.data(), roster);
    check(count == 4, "the selection yields four seats");
    // Each roster entry's fighter is its panel here: the roster is in panel order, which is the
    // order the launch fills the core's slots in.
    for (int i = 0; i < count; ++i) roster[i].fighter = roster[i].panel;

    check(roster[0].remote() && !roster[0].human(), "panel 0 is another machine's player");
    check(roster[2].local && roster[2].human(), "panel 2 is this machine's player");

    // The humans hold a real chord on every tick — the core owns their input bank, which is what
    // made the first cut of this fix label them COM.
    sim::Inputs inputs{};
    inputs[0].buttons = sim::Melee;
    inputs[3].buttons = sim::Jump;
    for (int t = 0; t < 8; ++t) battle.advance(inputs);

    check(battle.fighter(1).cpuDriven() && battle.fighter(2).cpuDriven(),
          "a configured COM is CPU-driven");
    check(!battle.fighter(0).cpuDriven() && !battle.fighter(3).cpuDriven(),
          "a human holding a chord is not CPU-driven");
    check(std::strcmp(ui::participantLabel(roster[0], battle.fighter(0).cpuDriven()), "1P") == 0,
          "a player on another machine keeps their name while they hold a chord here");
    // A two-player room reads 1P on both human seats: the original's vocabulary has no name for
    // another machine, which is the label #106 asked to stop being COM.
    check(std::strcmp(ui::participantLabel(roster[2], battle.fighter(3).cpuDriven()), "1P") == 0,
          "this machine's player is 1P");
    check(std::strcmp(ui::participantLabel(roster[3], battle.fighter(2).cpuDriven()), "COM") == 0,
          "a seat the CPU plays is COM");

    // Online, a player whose machine drops is handed to the CPU, here and on every peer.
    battle.hand_slot_to_cpu(0);
    for (int t = 0; t < 4; ++t) battle.advance(inputs);
    check(battle.fighter(0).cpuDriven(), "a human slot handed to the CPU is CPU-driven");
    check(std::strcmp(ui::participantLabel(roster[0], battle.fighter(0).cpuDriven()), "COM") == 0,
          "the seat a departed player leaves behind is named COM");
    check(!battle.fighter(3).cpuDriven(), "the other human seat is untouched by the hand-off");
}

// Offline, two people on one machine: the HUD tag must show their own seats, never COM. This is
// the case the first cut of the fix broke, because Battle::step tags every slot's carrier.
void test_offline_two_humans(const std::string& game) {
    sim::BattleConfig config;
    config.gameDir = game;
    config.slots[0] = {0, 0, false};
    config.slots[2] = {1, 0, false};
    config.slots[1] = {2, 0, true};
    config.slots[3] = {3, 0, true};
    config.timeLimitSeconds = 30;
    sim::CoreBattle battle;
    battle.start(config, {}, {});

    ui::FrontendState offline;
    offline.slots[0] = {0, 0, 0, 0, 0, false};
    offline.slots[2] = {1, 0, 0, 0, 1, false};
    ui::Participant roster[ui::kParticipantCount];
    const int count = ui::buildParticipants(offline.slots.data(), roster);
    check(count == 2, "a 1v1 yields two seats");

    sim::Inputs inputs{};
    inputs[0].buttons = sim::Melee;
    inputs[1].buttons = sim::Shoot;
    for (int t = 0; t < 8; ++t) battle.advance(inputs);

    // The tag cell each panel's fighter draws with, by the rule the HUD uses.
    check(ui::seatCell(roster[0], battle.fighter(0).cpuDriven()) == 0, "local 1P tags 1P");
    check(ui::seatCell(roster[1], battle.fighter(2).cpuDriven()) == 1, "local 2P tags 2P");
    check(battle.fighter(1).cpuDriven() && battle.fighter(3).cpuDriven(),
          "the offline COMs are CPU-driven");
}

}  // namespace

int main() {
    const std::string game = find_game();
    if (game.empty()) {
        std::printf("SKIP: no install\n");
        return 77;
    }
    test_online_labels(game);
    test_offline_two_humans(game);
    if (failures) {
        std::printf("net_seat_label_test: %d failure(s)\n", failures);
        return 1;
    }
    std::puts("net_seat_label_test: seats and the core's CPU agree");
    return 0;
}
