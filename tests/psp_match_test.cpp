// The three PSP fighters play whole matches (issue #91, plan decisions D-2 and D-3a). Each of the
// twelve combos fights a rotating PC opponent from the start of a round to the result, a PSP-vs-PSP
// match runs, a scripted human drives each fighter, and one match is rewound and replayed to prove
// the PSP data does not break rollback. Tier 4 at most: it proves the simulation runs on real game
// data, not that the behaviour matches the PSP.
//
// Data: $DAYBREAK_PSP_DATA (a prepared psp-data tree) or $DAYBREAK_PSP_RAW (the raw PSP
// .acs/.acv/.atp), which this test converts itself into a temporary tree. Without either, it skips.
// The fighters' own 00.X is Track A's conversion; until it exists the dispatch combo's PC model is
// copied under the fighter's name, which is enough for a simulation (skeleton and animations).
#include "battle/battle.h"
#include "battle/script.h"
#include "psp/psp_moveset.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

int failures = 0, checks = 0;
void check(bool condition, const std::string& name) {
    ++checks;
    if (!condition) {
        ++failures;
        std::printf("FAIL: %s\n", name.c_str());
    }
}

std::string find_game() {
    namespace fs = std::filesystem;
    if (const char* configured = std::getenv("GAME_DIR"))
        if (fs::exists(fs::path(configured) / "daybreak00.dat")) return configured;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        for (const auto& candidate : {path, path / "Higurashi-Daybreak"})
            if (fs::exists(candidate / "daybreak00.dat")) return candidate.string();
        if (path == path.parent_path()) return {};
    }
}

// The raw PSP files, either asserted directly or as the study dumped them (separators replaced).
std::string find_raw() {
    namespace fs = std::filesystem;
    const auto usable = [](const fs::path& root) {
        return fs::exists(root / "activity" / "chr17a.acs") ||
               fs::exists(root / "activity_chr17a.acs");
    };
    if (const char* configured = std::getenv("DAYBREAK_PSP_RAW"))
        if (usable(configured)) return configured;
    for (auto path = fs::current_path();; path = path.parent_path()) {
        if (usable(path / "local-data/harness/psp/dump")) return (path / "local-data/harness/psp/dump").string();
        if (path == path.parent_path()) return {};
    }
}

std::string find_tree(const std::string& game) {
    namespace fs = std::filesystem;
    const auto usable = [](const fs::path& root) {
        return fs::exists(root / "data" / "satoshi" / "00.dat");
    };
    if (const char* configured = std::getenv("DAYBREAK_PSP_DATA"))
        if (usable(configured)) return configured;
    if (usable(fs::path(game) / "psp-data")) return (fs::path(game) / "psp-data").string();
    return {};
}

constexpr unsigned kTimeLimit = 40, kRoundCap = kTimeLimit * 60u + 600u;

// The rows a fighter reached, so the report can say it both swung and shot.
bool is_melee_row(unsigned state) { return (state >= 300 && state <= 341); }
bool is_shot_row(unsigned state) {
    return (state >= 350 && state <= 362) || (state >= 400 && state <= 412) ||
           (state >= 422 && state <= 423) || (state >= 450 && state <= 461);
}

struct MatchReport {
    bool finished = false;
    int winner = -1;
    unsigned ticks = 0;
    std::array<long long, 4> dealt{}, taken{};
    std::array<int, 4> meleeRows{}, shotRows{};
    std::string error;
};

// One round of a real match, driven to the result. Rule values and stage are the product's
// defaults; the time limit is set so a round always ends and the awards resolve.
MatchReport play(const std::string& game, const std::string& tree, const sim::BattleConfig& start,
                 const std::vector<sim::ScriptSpan>& script = {}) {
    MatchReport report;
    try {
        sim::BattleConfig config = start;
        config.gameDir = game;
        config.pspDataDir = tree;
        config.timeLimitSeconds = kTimeLimit;
        sim::Battle battle(config);
        std::array<std::set<unsigned>, 4> states;
        while (report.ticks < kRoundCap) {
            battle.step(sim::script_inputs(script, report.ticks));
            ++report.ticks;
            for (unsigned i = 0; i < 4; ++i) states[i].insert(battle.actor(i).state);
            if (battle.match_finished()) break;
        }
        report.finished = battle.match_finished();
        report.winner = battle.match_state().winner;
        for (unsigned i = 0; i < 4; ++i) {
            const sim::ActorTotals totals = battle.totals(i);
            report.dealt[i] = totals.damageDealt;
            report.taken[i] = totals.damageTaken;
            report.meleeRows[i] = int(std::count_if(states[i].begin(), states[i].end(), is_melee_row));
            report.shotRows[i] = int(std::count_if(states[i].begin(), states[i].end(), is_shot_row));
        }
    } catch (const std::exception& error) {
        report.error = error.what();
    }
    return report;
}

sim::BattleConfig cpu_match(int psp_character, int psp_weapon, const std::array<sim::Slot, 3>& others,
                            std::uint32_t seed) {
    sim::BattleConfig config;
    config.seed = seed;
    config.stage = 21;
    config.slots[0] = {psp_character, psp_weapon, true};
    for (unsigned i = 0; i < 3; ++i) config.slots[i + 1] = others[i];
    return config;
}

void report_combo(const std::string& label, const MatchReport& report) {
    if (!report.error.empty()) {
        std::printf("%-22s THREW: %s\n", label.c_str(), report.error.c_str());
        return;
    }
    std::printf("%-22s ticks %4u  winner %d  damage %lld/%lld  rows melee %d shot %d\n", label.c_str(),
                report.ticks, report.winner, report.dealt[0], report.taken[0], report.meleeRows[0],
                report.shotRows[0]);
}

// The rotating PC opponents: one arm of the cast per combo, so the PSP data meets every kind of
// recovered body (melee, counter, gun, trap) rather than one.
const std::array<std::array<sim::Slot, 3>, 4> kOpponents{{
    {{{2, 0, true}, {3, 0, true}, {0, 1, true}}},
    {{{5, 2, true}, {9, 0, true}, {6, 1, true}}},
    {{{11, 0, true}, {13, 1, true}, {15, 0, true}}},
    {{{1, 0, true}, {7, 2, true}, {12, 0, true}}},
}};

void test_twelve_combos(const std::string& game, const std::string& tree) {
    for (int character = sim::character_count(); character < sim::character_count() + sim::psp_character_count();
         ++character) {
        for (int weapon = 0; weapon < sim::weapon_count(character); ++weapon) {
            const std::string label = sim::character_name(character) + "+" + std::to_string(weapon);
            const auto& others = kOpponents[std::size_t(character - sim::character_count() + weapon) % kOpponents.size()];
            // Two rounds with different seeds: which row a CPU picks is chaotic, so "this fighter
            // swings and shoots" is a claim about capability, not about one particular match.
            const MatchReport first = play(game, tree, cpu_match(character, weapon, others, 1 + unsigned(weapon)));
            const MatchReport second = play(game, tree, cpu_match(character, weapon, others, 11 + unsigned(weapon)));
            // The control: the very combo whose recovered code the PSP fighter runs, in the same
            // slot against the same opponents. Whatever the borrowed body cannot do here (a
            // matchup it cannot reach, a row family its CPU never selects) is not the port's debt;
            // D-2's claim is exactly "as capable as the dispatched combo".
            const auto [control_character, control_weapon] = sim::dispatch_combo(character, weapon);
            sim::BattleConfig control_config = cpu_match(character, weapon, others, 1 + unsigned(weapon));
            control_config.slots[0] = {control_character, control_weapon, true};
            const MatchReport control = play(game, tree, control_config);
            std::printf("%-22s control %s+%d damage %lld melee %d shot %d\n", "",
                        sim::character_name(control_character).c_str(), control_weapon, control.dealt[0],
                        control.meleeRows[0], control.shotRows[0]);
            report_combo(label, first);
            report_combo("  second seed", second);
            check(first.error.empty() && second.error.empty(), label + " ran without throwing");
            if (!first.error.empty() || !second.error.empty()) continue;
            check(control.error.empty(), label + " control ran without throwing");
            for (const MatchReport* run : {&first, &second}) {
                check(run->finished, label + " reached the result");
                check(run->winner >= 0, label + " ended with a winner");
                check(run->taken[0] > 0, label + " took damage: " + std::to_string(run->taken[0]));
                const long long opponentDamage = run->dealt[1] + run->dealt[2] + run->dealt[3];
                check(opponentDamage > 0, label + " saw the PC side deal damage: " + std::to_string(opponentDamage));
            }
            const long long dealt = std::max(first.dealt[0], second.dealt[0]);
            check(dealt > 0 || control.dealt[0] == 0, label + " dealt damage: " + std::to_string(dealt));
            check(std::max(first.meleeRows[0], second.meleeRows[0]) > 0 || control.meleeRows[0] == 0,
                  label + " reached a melee row");
            check(std::max(first.shotRows[0], second.shotRows[0]) > 0 || control.shotRows[0] == 0,
                  label + " reached a shot row");
        }
    }
}

// Four PSP fighters in one match: the dispatch pairs do not collide, and the result still resolves.
void test_psp_only(const std::string& game, const std::string& tree) {
    sim::BattleConfig config;
    config.seed = 7;
    config.stage = 21;
    const int first = sim::character_count();
    config.slots[0] = {first, 0, true};
    config.slots[1] = {first + 1, 1, true};
    config.slots[2] = {first + 2, 2, true};
    config.slots[3] = {first, 3, true};
    const MatchReport report = play(game, tree, config);
    std::printf("%-22s ticks %4u  winner %d  damage %lld/%lld  rows melee %d shot %d\n", "psp-vs-psp",
                report.ticks, report.winner, report.dealt[0], report.taken[0], report.meleeRows[0],
                report.shotRows[0]);
    check(report.error.empty(), "psp vs psp ran without throwing");
    if (report.error.empty()) {
        check(report.finished && report.winner >= 0, "psp vs psp ended with a winner");
        for (unsigned i = 0; i < 4; ++i) check(report.dealt[i] > 0, "psp vs psp slot " + std::to_string(i) + " dealt damage");
    }
}

// A human hand per fighter: walk up, swing, shoot, guard and jump, over and over for the whole round: a hand that keeps
// attacking while the CPU closes in, so every row family is reached many times. The plan is written
// out as text because that is the format tests/combos/*.plan uses.
std::vector<sim::ScriptSpan> human_plan(unsigned ticks) {
    std::string text;
    const std::array<const char*, 2> sideways{{"-1", "1"}};
    for (unsigned cycle = 0, at = 20; at + 300 < ticks; ++cycle, at += 300) {
        const std::string x = sideways[cycle % sideways.size()];
        std::array<char, 512> block{};
        std::snprintf(block.data(), block.size(),
                      "0 %u %u z=-1 x=%s\n"      // close the distance, sweeping both sides
                      "0 %u %u melee\n"          // a measured swing
                      "0 %u %u z=-1\n"
                      "0 %u %u shoot\n"          // hold the shot through its release
                      "0 %u %u guard\n"          // guard a counter
                      "0 %u %u jump\n"           // and leave the ground once
                      "0 %u %u melee\n",
                      at, at + 40, x.c_str(), at + 45, at + 80, at + 80, at + 130, at + 135, at + 185,
                      at + 190, at + 220, at + 225, at + 232, at + 240, at + 275);
        text += block.data();
    }
    std::istringstream in(text);
    return sim::parse_script(in);
}

void test_human_per_fighter(const std::string& game, const std::string& tree) {
    for (int character = sim::character_count(); character < sim::character_count() + sim::psp_character_count();
         ++character) {
        const std::string label = sim::character_name(character) + "+0 human";
        sim::BattleConfig config;
        config.seed = 3;
        config.stage = 21;
        config.slots[0] = {character, 0, false};  // slot 0 is the scripted human
        config.slots[1] = {2, 0, true};
        config.slots[2] = {3, 1, true};
        config.slots[3] = {6, 0, true};
        const MatchReport report = play(game, tree, config, human_plan(kRoundCap));
        std::printf("%-22s ticks %4u  winner %d  damage %lld/%lld  rows melee %d shot %d\n", label.c_str(),
                    report.ticks, report.winner, report.dealt[0], report.taken[0], report.meleeRows[0],
                    report.shotRows[0]);
        check(report.error.empty(), label + " ran the script without throwing");
        if (report.error.empty()) {
            check(report.dealt[0] > 0, label + " dealt damage");
            check(report.meleeRows[0] > 0, label + " reached a melee row");
            check(report.shotRows[0] > 0, label + " reached a shot row");
        }
    }
}

void test_determinism(const std::string& game, const std::string& tree) {
    sim::BattleConfig config = cpu_match(sim::character_count(), 0, kOpponents[0], 11);
    config.gameDir = game;
    config.pspDataDir = tree;
    config.timeLimitSeconds = kTimeLimit;
    const auto digest = [&](const sim::BattleConfig& which, unsigned ticks) {
        sim::Battle battle(which);
        for (unsigned t = 0; t < ticks; ++t) battle.step({});
        return battle.hash();
    };
    const auto first = digest(config, 1200);
    check(first == digest(config, 1200), "the same PSP match repeats exactly");
    sim::BattleConfig other = config;
    other.seed = 12;
    check(first != digest(other, 1200), "a different seed changes the PSP match");
}

// The online rollback contract on a PSP match: rewinding and replaying through a ring of snapshots
// must end exactly where a battle that never rewound does (tests/rollback_stress_test.cpp's shape).
void test_rollback(const std::string& game, const std::string& tree) {
    constexpr unsigned kRing = 9, kMaxRollback = kRing - 1, kAfterEnd = 120;
    sim::BattleConfig config = cpu_match(sim::character_count() + 2, 1, kOpponents[1], 5);
    config.gameDir = game;
    config.pspDataDir = tree;
    config.timeLimitSeconds = kTimeLimit;
    // Busy hands, so the replay walks the same rows a player would.
    const auto inputs = [](unsigned tick) {
        sim::Inputs out{};
        for (unsigned i = 0; i < 4; ++i) {
            const unsigned bits = ((tick / (11u + i * 3u)) * 2654435761u + i * 40503u) >> 20;
            out[i].x = int(bits & 3u) - 1;
            out[i].z = int((bits >> 2) & 3u) - 1;
            if (bits & 16u) out[i].buttons |= sim::Shoot;
            if (bits & 32u) out[i].buttons |= sim::Melee;
            if ((bits & 192u) == 192u) out[i].buttons |= sim::Jump;
            if ((bits & 768u) == 768u) out[i].buttons |= sim::Guard;
        }
        return out;
    };
    sim::Battle reference(config), rolled(config);
    sim::BattleSnapshot ring[kRing];
    unsigned after = 0, tick = 0, rollbacks = 0;
    bool agree = true;
    for (; after < kAfterEnd && tick < kRoundCap; ++tick) {
        const sim::Inputs now = inputs(tick);
        reference.step(now);
        if (reference.match_finished()) ++after;
        rolled.saveState(ring[tick % kRing]);
        rolled.step(now);
        if (rolled.match_finished()) ++after;
        const unsigned depth = std::min({1 + tick % kMaxRollback, kRing - 1, tick + 1});
        const unsigned from = tick + 1 - depth;
        rolled.loadState(ring[from % kRing]);
        for (unsigned t = from; t <= tick; ++t) rolled.step(inputs(t));
        ++rollbacks;
        if (rolled.hash() != reference.hash() || rolled.stateHash() != reference.stateHash()) agree = false;
    }
    std::printf("%-22s rollbacks %u ticks %u agree %s\n", "psp rollback", rollbacks, tick, agree ? "yes" : "no");
    check(agree, "a rewound PSP match ends where the reference does");
    check(rollbacks > 100, "the rollback stress actually rewound");
}

}  // namespace

int main() {
    const std::string game = find_game();
    if (game.empty()) {
        std::printf("psp_match_test: no game install; skipping\n");
        return 77;
    }
    std::string tree = find_tree(game);
    if (tree.empty()) {
        const std::string raw = find_raw();
        if (raw.empty()) {
            std::printf(
                "psp_match_test: no PSP data. Set DAYBREAK_PSP_DATA to a prepared psp-data tree or "
                "DAYBREAK_PSP_RAW to the raw .acs/.acv/.atp files (daybreak --extract-psp writes "
                "them from the player's ISO); skipping\n");
            return 77;
        }
        const auto temporary = std::filesystem::temp_directory_path() / "daybreak-psp-match-test";
        daybreak::psp::TreeRequest request;
        request.install_dir = game;
        request.raw_dir = raw;
        request.output_dir = temporary.string();
        try {
            const auto prepared = daybreak::psp::prepare_psp_data_tree(request);
            std::printf("psp_match_test: converted %zu files from %s into %s\n", prepared.written.size(),
                        raw.c_str(), temporary.u8string().c_str());
            tree = temporary.u8string();
        } catch (const std::exception& error) {
            std::printf("FAIL: converting the raw PSP data threw: %s\n", error.what());
            return 1;
        }
    } else {
        std::printf("psp_match_test: prepared tree %s\n", tree.c_str());
    }

    test_twelve_combos(game, tree);
    test_psp_only(game, tree);
    test_human_per_fighter(game, tree);
    test_determinism(game, tree);
    test_rollback(game, tree);

    if (failures) {
        std::printf("psp_match_test: %d failure(s) in %d checks\n", failures, checks);
        return 1;
    }
    std::printf("psp_match_test: ok (%d checks)\n", checks);
    return 0;
}
