// Online rollback (docs/ONLINE-PLAN.md, step 2): what a replayed tick tells the presentation.
// Tier 4 at most: agreement with itself, and nothing about the original.
#include "battle/core_battle.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace {

int failures = 0;
void check(bool condition, const std::string& name) {
    if (condition) return;
    ++failures;
    std::printf("FAIL: %s\n", name.c_str());
}

std::string find_game() {
    if (const char* configured = std::getenv("GAME_DIR")) return configured;
    namespace fs = std::filesystem;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        if (fs::exists(path / "Higurashi-Daybreak" / "daybreak00.dat")) return (path / "Higurashi-Daybreak").string();
        if (path == path.parent_path()) return {};
    }
}

sim::Inputs busy_inputs(unsigned tick, unsigned salt) {
    sim::Inputs inputs{};
    for (unsigned i = 0; i < 4; ++i) {
        const unsigned bits = ((tick / (11u + i * 3u) + salt) * 2654435761u + i * 40503u) >> 20;
        inputs[i].x = static_cast<int>(bits & 3u) - 1;
        inputs[i].z = static_cast<int>((bits >> 2) & 3u) - 1;
        if (bits & 16u) inputs[i].buttons |= sim::Shoot;
        if (bits & 32u) inputs[i].buttons |= sim::Melee;
    }
    return inputs;
}

sim::BattleConfig make_config(const std::string& game, bool humans) {
    sim::BattleConfig config;
    config.gameDir = game;
    for (unsigned i = 0; i < 4; ++i) config.slots[i] = {static_cast<int>(i), 0, !humans};
    config.timeLimitSeconds = 30;
    return config;
}

// The events of one frame as text, in the order the presentation gets them.
std::vector<std::string> describe(const game::BattleFrame& frame) {
    std::vector<std::string> out;
    for (const auto& e : frame.effectSpawns) out.push_back("effect " + std::to_string(e.id));
    for (const auto& s : frame.soundCues) out.push_back("sound " + std::to_string(s.id));
    for (const auto& v : frame.voiceCues) out.push_back("voice " + std::to_string(v.fighter) + " " + v.path);
    return out;
}

constexpr unsigned kTicks = 30 * 60 + 2400;  // past the awards, which follow the time limit

// A stressed run reports exactly what a plain one does, tick by tick.
void test_stress_changes_nothing(const std::string& game, bool humans) {
    sim::CoreBattle plain, stressed;
    const std::array<const gameplay::CharacterMoves*, 4> moves{};
    // Any held model draws a ribbon, so every swing moves the trails' history.
    gameplay::WeaponDefinition ribbons;
    ribbons.slotCount = 16;
    for (auto& slot : ribbons.slots) {
        slot.meshName = "ribbon";
        slot.ribbonTip[2] = 30.f;
    }
    const std::array<const gameplay::WeaponDefinition*, 4> weapons{&ribbons, &ribbons, &ribbons, &ribbons};
    plain.start(make_config(game, humans), moves, weapons);
    stressed.start(make_config(game, humans), moves, weapons);
    stressed.set_rollback_stress(8);

    unsigned events = 0, rounds = 0, roundsStressed = 0;
    int maxRibbon = 0;
    for (unsigned t = 0; t < kTicks; ++t) {
        const auto a = plain.advance(busy_inputs(t, 0));
        const auto b = stressed.advance(busy_inputs(t, 0));
        if (describe(a) != describe(b)) {
            check(false, "the events differ at tick " + std::to_string(t));
            return;
        }
        for (int i = 0; i < 4; ++i)
            for (int hand = 0; hand < 2; ++hand) {
                const auto& ribbon = plain.fighter(i).trail(hand);
                const auto& other = stressed.fighter(i).trail(hand);
                maxRibbon = std::max(maxRibbon, ribbon.triangles());
                const auto left = ribbon.vertices(), right = other.vertices();
                bool same = ribbon.triangles() == other.triangles();
                for (size_t v = 0; same && v < left.size(); ++v) same = left[v].pos == right[v].pos;
                if (!same) {
                    check(false, "a trail differs at tick " + std::to_string(t));
                    return;
                }
            }
        events += static_cast<unsigned>(describe(a).size());
        rounds += a.roundOver;
        roundsStressed += b.roundOver;
        if (plain.economy().roundOver() != stressed.economy().roundOver()) {
            check(false, "the round-over state differs at tick " + std::to_string(t));
            return;
        }
    }
    std::printf("humans=%d: %u events, %u round ends, ribbons up to %d triangles\n", humans, events, rounds, maxRibbon);
    check(maxRibbon > 0, "no ribbon was ever drawn");
    check(events > 100, "too few events to mean anything");
    check(rounds == 1, "the round must end once");
    check(roundsStressed == 1, "a stressed round must end once");
}

// A correction shown after a wrong prediction: nothing twice, and nothing real lost.
void test_correction_reports_once(const std::string& game) {
    sim::CoreBattle truth, shown;
    const std::array<const gameplay::CharacterMoves*, 4> moves{};
    const std::array<const gameplay::WeaponDefinition*, 4> weapons{};
    truth.start(make_config(game, true), moves, weapons);
    shown.start(make_config(game, true), moves, weapons);

    constexpr unsigned kLag = 4;
    std::array<sim::CoreBattle::Snapshot, kLag> states;
    std::map<unsigned, std::vector<std::string>> real, reported;
    for (unsigned t = 0; t < kTicks; ++t) real[t] = describe(truth.advance(busy_inputs(t, 0)));

    // Each block of ticks first runs on a prediction, then is corrected before the next block.
    for (unsigned block = 0; block + kLag <= kTicks; block += kLag) {
        for (unsigned k = 0; k < kLag; ++k) {
            shown.save_state(states[k]);
            const auto wrong = describe(shown.advance(busy_inputs(block + k, 1 + block)));
            auto& list = reported[block + k];
            list.insert(list.end(), wrong.begin(), wrong.end());
        }
        shown.load_state(states[0]);
        for (unsigned k = 0; k < kLag; ++k) {
            const auto right = describe(shown.advance(busy_inputs(block + k, 0)));
            auto& list = reported[block + k];
            list.insert(list.end(), right.begin(), right.end());
        }
        // A replay with the same inputs has nothing left to report.
        shown.load_state(states[0]);
        for (unsigned k = 0; k < kLag; ++k)
            check(describe(shown.advance(busy_inputs(block + k, 0))).empty(), "a replayed event was reported twice");
    }
    unsigned missing = 0, total = 0;
    for (const auto& [tick, events] : real) {
        auto left = reported[tick];
        for (const std::string& event : events) {
            ++total;
            const auto found = std::find(left.begin(), left.end(), event);
            if (found == left.end()) ++missing;
            else left.erase(found);
        }
    }
    std::printf("correction: %u real events, %u missing\n", total, missing);
    check(total > 100, "too few real events to mean anything");
    check(missing == 0, "a real event was never reported");
}

}  // namespace

int main() {
    const std::string game = find_game();
    if (game.empty()) {
        std::printf("SKIP: no install\n");
        return 77;
    }
    test_stress_changes_nothing(game, true);
    test_stress_changes_nothing(game, false);
    test_correction_reports_once(game);
    if (failures) {
        std::printf("rollback_presentation_test: %d failure(s)\n", failures);
        return 1;
    }
    std::printf("rollback_presentation_test: ok\n");
    return 0;
}
