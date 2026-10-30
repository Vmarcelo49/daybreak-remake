// The vendored simulation behind sim::Battle (docs/DIRECTION.md, M1): every legal combo runs,
// and the digest is both repeatable and sensitive. This proves execution on real game data,
// tier 4 at most: nothing here says the behaviour matches the original.
#include "sim/battle.h"
#include "sim/script.h"

#include <climits>
#include <cmath>
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

    // Hypermode activation: the chord starts row 500 and its notice reaches a local player.
    auto human = match(game, 0, 0);
    human.slots[0].cpu = false;
    human.slots[0].specialMode = 0;
    for (size_t i = 1; i < 4; ++i) human.slots[i].cpu = false;
    sim::Battle activation(human);
    bool enteredRow500 = false, voiceOrSound = false;
    for (unsigned t = 0; t < 300; ++t) {
        if (t == 190) activation.fill_special_for_test();
        sim::Inputs inputs{};
        if (t >= 200 && t < 204) inputs[0].buttons = sim::Melee | sim::Shoot;
        activation.step(inputs);
        enteredRow500 |= activation.actor(0).state == 500;
        for (const auto& sound : activation.events().sounds) voiceOrSound |= sound.actor == 0 && t >= 200;
    }
    check(enteredRow500, "the chord with a full meter starts the activation row");
    check(voiceOrSound, "and the activation asks for its sound");
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

// FUN_0043ffc0 case 0x15e writes +0x684 on every update of Rena+0's row 350: clip 0 from the
// start, even on a whiff, so the Hyper EX's camera plays. Leaving the row clears it.
void test_rena_ex_camera(const std::string& game) {
    auto config = match(game, 0, 0);
    for (auto& slot : config.slots) slot.cpu = false;
    config.slots[0].specialMode = 0;
    sim::Battle battle(config);
    bool inRow = false, clipDuringRow = false, clearedAfter = false;
    bool ordinaryBefore = false, animatedDuringRow = false, anchoredOnRena = true;
    for (unsigned t = 0; t < 1200; ++t) {
        if (t == 190) battle.fill_special_for_test();
        sim::Inputs inputs{};
        if ((t >= 200 && t < 204) || (t >= 540 && t < 544)) inputs[0].buttons = sim::Melee | sim::Shoot;
        battle.step(inputs);
        const sim::ActorState rena = battle.actor(0);
        const sim::CameraPose camera = battle.camera(0);
        if (!inRow && t > 100) ordinaryBefore |= !camera.animated;
        if (rena.state == 350) {
            inRow = true;
            clipDuringRow |= rena.actionCamera == 0;
            animatedDuringRow |= camera.animated;
            // Clips stay close to their anchor, while the target stands far across the stage.
            const float dx = camera.eye[0] - rena.position[0], dz = camera.eye[2] - rena.position[2];
            if (camera.animated && std::sqrt(dx * dx + dz * dz) > 1000.f) anchoredOnRena = false;
        } else if (inRow) {
            clearedAfter |= rena.actionCamera == -1;
        }
    }
    check(inRow, "the chord during the mode reaches row 350");
    check(clipDuringRow, "row 350 asks for camera clip 0 without a hit");
    check(ordinaryBefore, "the ordinary follow runs before the EX");
    check(animatedDuringRow, "and the EX's clip drives the camera");
    check(anchoredOnRena, "with the eye orbiting Rena, not the target (FUN_006333b0)");
    check(clearedAfter, "and the camera request ends with the row");
}

// What the battle HUD reads: fractions stay in range, the ghost trails the HP after a hit, and a
// survivor is never reported at zero.
void test_hud_values(const std::string& game) {
    sim::Battle battle(match(game, 0, 0));
    bool inRange = true, ghostAbove = false, popup = false;
    for (unsigned t = 0; t < 3600; ++t) {
        battle.step({});
        for (unsigned slot = 0; slot < 4; ++slot) {
            const sim::ActorState actor = battle.actor(slot);
            ghostAbove |= actor.delayedHp > actor.hp;
            for (const sim::MagazineState& magazine : battle.magazines(slot))
                inRange = inRange && magazine.fill >= 0.f && magazine.fill <= 1.f && magazine.charge >= 0.f && magazine.charge <= 1.f;
            const float fan = battle.special(slot).fraction;
            inRange = inRange && fan >= 0.f && fan <= 1.f;
        }
        popup |= battle.match_state().scoreDeltaTicks[0] > 0 || battle.match_state().scoreDeltaTicks[1] > 0;
    }
    check(inRange, "every HUD fraction stays within 0..1");
    check(ghostAbove, "the HP ghost trails above the live HP after a hit");
    check(popup, "a score change arms the popup");
}

// The attenuation needs world positions on the cues: a cue at the origin or on the listener
// would stay at full volume whatever the fighters do.
void test_positional_sounds(const std::string& game) {
    sim::BattleConfig config = match(game, 0, 0);
    config.slots[0].cpu = false;  // one human means one view, the case that positions voices
    sim::Battle battle(config);
    size_t positional = 0, positionalVoices = 0, starts = 0;
    float farthest = 0.f;
    bool startPositional = false, voiceAtHead = true;
    for (unsigned t = 0; t < 3600; ++t) {
        battle.step({});
        const std::array<float, 3> listener = battle.actor(0).position;
        for (const auto& sound : battle.events().sounds) {
            if (!sound.positional) continue;
            ++positional;
            const float dx = sound.position[0] - listener[0], dy = sound.position[1] - listener[1] - 150.f, dz = sound.position[2] - listener[2];
            farthest = std::max(farthest, std::sqrt(dx * dx + dy * dy + dz * dz));
        }
        for (const auto& voice : battle.events().voices) {
            const sim::ActorState speaker = battle.actor(static_cast<unsigned>(voice.actor));
            const bool start = voice.path.find("/battlestart/") != std::string::npos;
            starts += start;
            startPositional |= start && voice.positional;
            positionalVoices += voice.positional;
            voiceAtHead = voiceAtHead && (!voice.positional || std::fabs(voice.position[1] - speaker.position[1] - 145.f) < .01f);
        }
    }
    check(starts == 1, "only the human's start line plays");
    check(!startPositional, "and it is not positional");
    check(positionalVoices > 0, "attack voices are positional with one view");
    check(voiceAtHead, "at the speaker's head");
    check(positional > 0, "a match requests positional sounds");
    check(farthest > 500.f, "and they carry world positions away from the listener");
}

// FUN_00635d40 case 1, as battle_startup.hpp keeps it: three digits of 60 ticks while everyone
// falls from the spawn with commands locked, then the start notice and free movement.
void test_round_start(const std::string& game) {
    sim::BattleConfig config = match(game, 0, 0);
    config.slots[0].cpu = false;
    sim::Battle battle(config);
    const float spawnY = battle.actor(0).position[1];
    const std::array<float, 3> spawn = battle.actor(0).position;
    sim::Inputs held{};
    held[0].x = 1;
    std::vector<int> seen;
    bool movedDuringCount = false;
    float lowest = spawnY;
    for (unsigned t = 0; t < 179; ++t) {
        battle.step(held);
        const int type = battle.notice(0).type;
        if (type >= 0 && (seen.empty() || seen.back() != type)) seen.push_back(type);
        const auto at = battle.actor(0).position;
        movedDuringCount |= at[0] != spawn[0] || at[2] != spawn[2];
        lowest = std::min(lowest, at[1]);
    }
    check(seen == std::vector<int>({3, 4, 5}), "the digits 3, 2, 1 play from the first tick");
    check(lowest < spawnY - 1.f, "the fighters fall during the count");
    check(!movedDuringCount, "and held input does not move them");
    for (unsigned t = 0; t < 120; ++t) {
        battle.step(held);
        const int type = battle.notice(0).type;
        if (type >= 0 && seen.back() != type) seen.push_back(type);
    }
    check(seen.back() == 6, "the start notice follows the digits");
    const auto after = battle.actor(0).position;
    check(after[0] != spawn[0] || after[2] != spawn[2], "held input moves the fighter once the count ends");
}

// The core's HUD state the view draws: the tactic a human gives its CPU ally, the round clock,
// the reticle and the direction warnings.
void test_hud_state(const std::string& game) {
    sim::BattleConfig config = match(game, 0, 0);
    config.slots[0].cpu = false;
    config.timeLimitSeconds = 60;
    sim::Battle battle(config);
    float pulse = 0.f;
    for (unsigned t = 0; t < 200; ++t) battle.step({});
    const int before = battle.cpu_command(0, pulse);
    check(before >= 0, "a human with a CPU ally has a tactic to give");
    check(battle.cpu_command(1, pulse) == -1, "a CPU seat shows none");
    sim::Inputs press{};
    press[0].buttons = sim::Tactics;
    battle.step(press);
    battle.step(press);
    battle.step(press);
    check(battle.cpu_command(0, pulse) == (before + 1) % 6, "one held press cycles the tactic once");
    check(pulse > 0.f, "and pulses its cell");
    check(battle.match_state().timed && battle.match_state().remainingTicks > 0, "the round has a clock");
    bool warned = false, ringed = false;
    for (unsigned t = 0; t < 1800; ++t) {
        battle.step({});
        for (const sim::DirectionWarning& w : battle.direction_warnings(0))
            warned |= w.state != 0 && w.direction >= 0 && w.direction <= 3;
        ringed |= battle.lock_ring(0).target >= 0;
    }
    check(warned, "incoming locks raise a direction warning");
    check(ringed, "the view has a reticle target");
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
    test_rena_ex_camera(game);
    test_hud_values(game);
    test_positional_sounds(game);
    test_round_start(game);
    test_hud_state(game);
    test_determinism(game);
    test_input_sensitivity(game);
    test_scripted_rena_reaches_her_rows(game);
    test_every_combo_runs(game);
    std::printf("SIM_CORE: %s (%d checks, %d failed)\n", failures ? "FAIL" : "ok", checks, failures);
    return failures ? 1 : 0;
}
