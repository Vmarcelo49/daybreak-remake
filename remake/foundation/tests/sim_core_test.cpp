// The vendored simulation behind sim::Battle (docs/DIRECTION.md, M1): every legal combo runs,
// and the digest is both repeatable and sensitive. This proves execution on real game data,
// tier 4 at most: nothing here says the behaviour matches the original.
#include "sim/battle.h"
#include "sim/script.h"

#include <climits>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <set>
#include <sstream>
#include <string>

#include "core_prelude.h"
#include "legacy_trig.hpp"

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

sim::BattleConfig match(const std::string& game, int character, int weapon, std::uint32_t seed = 1) {
    sim::BattleConfig config;
    config.gameDir = game;
    config.seed = seed;
    config.slots[0] = {character, weapon, true};
    config.slots[1] = {(character + 5) % 14, 0, true};
    config.slots[2] = {(character + 7) % 14, 1, true};
    config.slots[3] = {(character + 9) % 14, 2, true};
    return config;
}

std::uint64_t run(const sim::BattleConfig& config, unsigned ticks, const std::vector<sim::ScriptSpan>& script = {}) {
    sim::Battle battle(config);
    for (unsigned t = 0; t < ticks; ++t) battle.step(sim::script_inputs(script, t));
    return battle.hash();
}

std::vector<sim::ScriptSpan> script_from(const std::string& text) {
    std::istringstream in(text);
    return sim::parse_script(in);
}

void test_every_combo_runs(const std::string& game) {
    int combos = 0;
    for (int c = 0; c < sim::character_count(); ++c) {
        for (int w = 0; w < sim::weapon_count(c); ++w) {
            ++combos;
            const std::string label = sim::character_name(c) + "+" + std::to_string(w);
            try {
                sim::Battle battle(match(game, c, w));
                std::set<unsigned> states;
                bool moved = false;
                const auto start = battle.actor(0).position;
                for (unsigned t = 0; t < 1200; ++t) {
                    battle.step({});
                    states.insert(battle.actor(0).state);
                    moved |= battle.actor(0).position != start;
                }
                check(moved, label + " moved");
                check(states.size() >= 5, label + " reached several rows, got " + std::to_string(states.size()));
            } catch (const std::exception& error) {
                check(false, label + " threw: " + error.what());
            }
        }
    }
    check(combos == 46, "the roster is 46 legal combos");
}

void test_determinism(const std::string& game) {
    const auto config = match(game, 0, 0);
    const auto first = run(config, 1800);
    check(first == run(config, 1800), "the same match repeats exactly");
    check(first != run(match(game, 0, 0, 2), 1800), "a different seed changes the match");
    check(first != run(config, 1799), "the digest covers the last tick");
}

// The seeded mutation: one button, one slot, one tick must reach the digest. Without this a
// digest that ignored the match would pass the repeat check above.
void test_input_sensitivity(const std::string& game) {
    auto config = match(game, 0, 0);
    config.slots[0].cpu = false;
    const std::string base = "0 300 360 z=-1\n";
    const auto baseline = run(config, 900, script_from(base));
    check(baseline == run(config, 900, script_from(base)), "a scripted match repeats exactly");
    check(baseline != run(config, 900, script_from(base + "0 400 401 melee\n")),
          "a one-tick melee press changes the match");
    check(baseline != run(config, 900), "the script reaches the match at all");
}

// Idle opponents: a CPU could hit Rena mid-script and cost a press, which would make this a
// test of the match instead of the input path.
void test_scripted_rena_reaches_her_rows(const std::string& game) {
    auto config = match(game, 0, 0);
    for (auto& slot : config.slots) slot.cpu = false;
    sim::Battle battle(config);
    const auto script = script_from("0 300 310 melee\n0 500 510 shoot\n0 700 710 jump\n");
    std::set<unsigned> states;
    unsigned lastAttackFrame = 0;
    bool attackClockRan = false;
    for (unsigned t = 0; t < 900; ++t) {
        battle.step(sim::script_inputs(script, t));
        const sim::ActorState rena = battle.actor(0);
        states.insert(rena.state);
        if (rena.state == 300) {
            attackClockRan |= rena.frame > lastAttackFrame;
            lastAttackFrame = rena.frame;
        }
    }
    check(states.count(300) == 1, "a melee press reaches row 300");
    check(attackClockRan, "the row's frame clock is visible through the snapshot");
    check(states.count(400) == 1, "a shot press reaches row 400");
    check(states.count(40) == 1, "a jump press reaches row 40");
}

// The presentation requests --sim=core delivers: a match with CPUs fires, sounds and speaks, and
// every request resolves to something the presentation can use.
void test_presentation_events(const std::string& game) {
    sim::Battle battle(match(game, 1, 0));
    size_t effects = 0, sounds = 0, voices = 0, shots = 0, unknownRows = 0, trails = 0;
    bool badVoicePath = false;
    for (unsigned t = 0; t < 3600; ++t) {
        battle.step({});
        const sim::BattleEvents& events = battle.events();
        effects += events.effects.size();
        sounds += events.sounds.size();
        voices += events.voices.size();
        for (const auto& voice : events.voices) badVoicePath |= voice.path.rfind("data/voice/", 0) != 0;
        battle.for_each_projectile([&](const sim::ProjectileState& p) {
            ++shots;
            unknownRows += p.row < 0;
        });
    }
    check(effects > 0, "a match requests effects");
    check(sounds > 0, "a match requests sounds");
    check(voices > 0, "a match requests voices");
    check(!badVoicePath, "voices resolve to shipped paths");
    check(shots > 0, "a match has live projectiles");
    check(unknownRows == 0, "every projectile maps back to a weapon row");
    // Only melee weapons ask for trails, so this names a combo that swings: Shion+2.
    sim::Battle swinger(match(game, 5, 2));
    for (unsigned t = 0; t < 2400; ++t) {
        swinger.step({});
        for (unsigned hand = 0; hand < 2; ++hand) trails += swinger.hand_trail(0, hand).active;
    }
    check(trails > 0, "a melee weapon draws trails");
    const sim::MatchState state = battle.match_state();
    check(state.limit[0] == 100.f && state.limit[1] == 100.f, "the score limit defaults to 100");
}

// The round decides itself: the clock runs out and the core names a winner, then its result
// screen opens, which draws from the RNG and must not throw.
void test_round_end(const std::string& game) {
    auto config = match(game, 0, 0);
    config.timeLimitSeconds = 10;
    sim::Battle battle(config);
    bool decided = false, ready = false;
    for (unsigned t = 0; t < 3000 && !ready; ++t) {
        battle.step({});
        decided = decided || battle.match_state().winner >= 0;
        ready = battle.match_state().finished;
    }
    check(decided, "the time limit decides a winner");
    check(ready, "and the result screens become ready");
    bool titlesChosen = false;
    for (unsigned t = 0; t < 2000 && !titlesChosen; ++t) {
        battle.step({});
        titlesChosen = battle.match_state().awardsReady;
    }
    check(titlesChosen, "the core chooses the earned titles");
    check(battle.match_state().timed, "the round reports its clock");
}

void test_invalid_combos_are_rejected(const std::string& game) {
    const auto rejected = [&](int character, int weapon) {
        try {
            sim::Battle battle(match(game, character, weapon));
        } catch (const std::invalid_argument&) {
            return true;
        }
        return false;
    };
    check(rejected(14, 2), "character 14 has no third weapon");
    check(rejected(0, 3), "weapon slot 3 does not exist");
    check(rejected(16, 0), "character 16 does not exist");
}

// PATCHES.md, 2026-10-30. Ohishi+2's row 463 really does hand the trig call a pitch near 2^32,
// and _ftol2 (FUN_0066b668) keeps the low 32 bits of a 64-bit FISTP.
void test_trig_takes_the_ftol_path() {
    using daybreak::legacy_trig;
    const float wrapped = 4294967296.f;  // angle*10 has low 32 bits of zero
    check(legacy_trig(wrapped, false) == legacy_trig(0.f, false), "a pitch of 2^32 reads table entry 0, not a throw");
    check(legacy_trig(-wrapped, false) == legacy_trig(0.f, false), "and so does its negative");
    check(legacy_trig(1e30f, false) == legacy_trig(0.f, false), "past 2^63 FISTP is indefinite, low word 0");
    check(legacy_trig(90.f, false) == legacy_trig(-90.f, false), "ordinary angles keep their symmetry");
}

void test_script_parser() {
    const auto spans = script_from("# comment\n\n1 5 9 x=-1 jump guard # trailing\n");
    check(spans.size() == 1, "comments and blank lines are skipped");
    const auto inside = sim::script_inputs(spans, 8), after = sim::script_inputs(spans, 9);
    check(inside[1].x == -1 && inside[1].buttons == (sim::Jump | sim::Guard), "a span applies inside its window");
    check(after[1].x == 0 && after[1].buttons == 0, "the end tick is exclusive");
    bool threw = false;
    try {
        script_from("0 5 9 kick\n");
    } catch (const std::runtime_error&) {
        threw = true;
    }
    check(threw, "an unknown token fails loudly");
}

}  // namespace

int main() {
    test_script_parser();
    test_trig_takes_the_ftol_path();
    const std::string game = find_game();
    if (game.empty()) {
        std::puts("SIM_CORE: skipped, no game install");
        return 77;
    }
    test_invalid_combos_are_rejected(game);
    test_presentation_events(game);
    test_round_end(game);
    test_determinism(game);
    test_input_sensitivity(game);
    test_scripted_rena_reaches_her_rows(game);
    test_every_combo_runs(game);
    std::printf("SIM_CORE: %s (%d checks, %d failed)\n", failures ? "FAIL" : "ok", checks, failures);
    return failures ? 1 : 0;
}
