// The vendored admission bodies against the original's own answers (docs/DIRECTION.md, M2).
//
// The bundle's evidence/ tables come from its author's Unicorn run of the pinned DaybreakDX.exe:
// every combo's vtable slot-7 handler, called on real DAT phase/flag contexts under synthetic
// input (reference/original_tools/probe_roster_input_cancels.py). This replays the same contexts
// through our compiled bodies and compares the requested state. That is original code under
// controlled input, not a natural match, and the tables sample contexts rather than cover them.
#include "core_prelude.h"
#include "shoot_native_control.hpp"
#include "slot7_native_control.hpp"

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace {
namespace fs = std::filesystem;
using namespace daybreak;

struct Scenario { int jumpHeld, jumpReleased, meleeHeld, meleeReleased, shootReleased, x, z, dash; };

// probe_roster_input_cancels.py, in its field order.
const std::map<std::string, Scenario> kScenarios = {
    {"shot_melee_release", {0, 0, 0, 1, 1, 0, 0, 0}},
    {"shot_third_melee", {0, 0, 3, 0, 1, 0, 0, 0}},
    {"guard_third_melee", {1, 0, 3, 0, 0, 0, 0, 0}},
    {"melee_release", {0, 0, 0, 1, 0, 0, 0, 0}},
    {"shot_release", {0, 0, 0, 0, 1, 0, 0, 0}},
    {"dash_neutral", {0, 0, 0, 0, 0, 0, 0, 0}},
    {"dash_melee_third", {0, 0, 3, 0, 0, 0, 0, 0}},
    {"dash_melee_forward", {0, 0, 3, 0, 0, 0, 1, 0}},
    {"dash_melee_side", {0, 0, 3, 0, 0, 1, 0, 0}},
    {"dash_melee_back", {0, 0, 3, 0, 0, 0, -1, 0}},
    {"dash_shot_release", {0, 0, 0, 0, 1, 0, 0, 0}},
    {"dash_shot_back", {0, 0, 0, 0, 1, 0, -1, 0}},
    {"dash_shot_melee", {0, 0, 3, 0, 1, 0, 1, 0}},
    {"dash_jump_third", {3, 0, 0, 0, 0, 0, 0, 0}},
    {"dash_jump_release", {0, 1, 0, 0, 0, 0, 0, 0}},
    {"dash_jump_shot", {3, 0, 0, 0, 1, 0, 0, 0}},
    {"dash_guard_melee", {1, 0, 3, 0, 0, 0, 0, 0}},
    {"dash_forward_command", {0, 0, 0, 0, 0, 0, 1, 1}},
    {"dash_back_command", {0, 0, 0, 0, 0, 0, -1, 2}},
    {"dash_melee_release", {0, 0, 0, 1, 0, 0, 0, 0}},
    {"dash_shot_forward", {0, 0, 0, 0, 1, 0, 1, 0}},
    {"dash_shot_side", {0, 0, 0, 0, 1, 1, 0, 0}},
    {"dash_shot_side_left", {0, 0, 0, 0, 1, -1, 0, 0}},
};

std::vector<std::string> split(const std::string& line, char separator) {
    std::vector<std::string> out;
    std::stringstream stream(line);
    for (std::string field; std::getline(stream, field, separator);) out.push_back(field);
    return out;
}

fs::path find_evidence() {
    const fs::path relative = ".local-analysis/porting-support/DaybreakPortingSupport-20261010/evidence";
    for (auto path = fs::current_path();; path = path.parent_path()) {
        if (fs::exists(path / relative)) return path / relative;
        if (path == path.parent_path()) return {};
    }
}

struct Tally {
    int cases = 0, agree = 0, requests = 0, requestsAgree = 0;
    std::map<std::string, int> firstMismatches;
};

// weaponShift replays each row on another weapon: the negative control, which must disagree.
Tally replay(const fs::path& contexts, const fs::path& original, int weaponShift = 0) {
    std::map<std::string, std::string> priorities;
    std::ifstream contextFile(contexts);
    std::string line;
    std::getline(contextFile, line);
    for (; std::getline(contextFile, line);) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        const auto f = split(line, '\t');
        priorities[f[0] + "/" + f[1] + "/" + f[2] + "/" + f[3] + "/" + f[4] + "/" + f[5]] = f[6] + "|" + f[7];
    }

    Tally tally;
    int selected = -1;
    Slot7NativeServices services;
    services.invoke = [&](const Slot7NativeEvent& event, Slot7BodyContext&) {
        if (event.address == 0x421080 || event.address == 0x4211f0) selected = event.args.at(0);
        return 0;
    };
    auto body = std::make_unique<Slot7BodyContext>(services);
    std::ifstream originalFile(original);
    std::getline(originalFile, line);
    for (; std::getline(originalFile, line);) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        const auto f = split(line, '\t');
        const int character = std::stoi(f[0]), weapon = std::stoi(f[1]), state = std::stoi(f[2]), phase = std::stoi(f[3]),
                  frame = std::stoi(f[4]);
        const auto flags = static_cast<std::uint32_t>(std::stoul(f[5]));
        const Scenario& s = kScenarios.at(f[6]);
        const int expected = std::stoi(f[7]);
        const auto context = split(priorities.at(f[0] + "/" + f[1] + "/" + f[2] + "/" + f[3] + "/" + f[4] + "/" + f[5]), '|');

        Slot7BodyContext& n = *body;
        n.w.fill(0);
        n.partner.fill(0);
        n.events.clear();
        n.frame_flags = flags;
        const auto set = [&](unsigned offset, int value) { n.w.at(offset / 4) = value; };
        for (const auto& pair : split(context[1], ',')) {
            const auto kv = split(pair, ':');
            set(0x880 + static_cast<unsigned>(std::stoi(kv[0])) * 28, std::stoi(kv[1]));
        }
        set(0x880 + static_cast<unsigned>(state) * 28 + 4, std::stoi(context[0]));
        set(0xadec, state); set(0xadf4, phase); set(0xae04, frame);
        set(0x278, s.x); set(0x27c, s.z);
        set(0x280, s.jumpHeld); set(0x284, s.meleeHeld);
        set(0x2b0, s.jumpReleased); set(0x2b4, s.meleeReleased); set(0x2b8, s.shootReleased);
        set(0x830, s.dash); set(0x6dc, 8); set(0x834, 1000);
        n.set_byte(0x84, 1);
        selected = -1;
        const int limit = character < 14 ? 3 : 2;
        dispatch_slot7_body(n, static_cast<unsigned>(character), static_cast<unsigned>((weapon + weaponShift) % limit));

        ++tally.cases;
        if (expected >= 0) ++tally.requests;
        if (selected == expected) {
            ++tally.agree;
            if (expected >= 0) ++tally.requestsAgree;
        } else if (tally.firstMismatches.size() < 12) {
            tally.firstMismatches[line] = selected;
        }
    }
    return tally;
}

// Numbers out of one JSONL row: the traces are flat apart from "events", so a key search is enough.
double field(const std::string& row, const char* key, double fallback = 0) {
    const std::string needle = std::string("\"") + key + "\":";
    const auto at = row.find(needle);
    return at == std::string::npos ? fallback : std::strtod(row.c_str() + at + needle.size(), nullptr);
}

std::string number_text(double value) {
    char text[32];
    std::snprintf(text, sizeof text, "%.3f", value == 0 ? 0.0 : value);
    return text;
}

bool is_transition(const std::string& event) { return event.rfind("next_", 0) == 0; }

// Two trace fields say nothing about the body. Its fire_world x and z are zero because the
// emulated cosine table was zeroed (core/roster_ground_shot400_world.hpp records this), and a
// fire_attachment reached through FUN_00434fd0 carries the emulated actor's address, 0x1001000.
std::string comparable(const std::string& event) {
    auto fields = split(event, ',');
    if (fields[0] == "fire_world") fields[2] = fields[4] = "x";
    if (fields[0] == "fire_attachment" && fields[5] == number_text(0x1001000)) fields[5] = number_text(0);
    std::string out;
    for (const auto& value : fields) out += (out.empty() ? "" : ",") + value;
    return out;
}

// The trace's event list, one normalised string per event. Bone lookups and visibility have no
// counterpart in the body, which resolves bones through its host.
std::vector<std::string> trace_events(const std::string& row) {
    std::vector<std::string> events;
    auto at = row.find("\"events\":[");
    if (at == std::string::npos) return events;
    at += 10;
    while (at < row.size() && row[at] == '[') {
        const auto end = row.find(']', at);
        std::string out;
        for (const auto& token : split(row.substr(at + 1, end - at - 1), ',')) {
            if (!out.empty()) out += ',';
            out += token.front() == '"' ? token.substr(1, token.size() - 2) : number_text(std::strtod(token.c_str(), nullptr));
        }
        if (out.rfind("bone_lookup", 0) != 0 && out.rfind("model_visible", 0) != 0) events.push_back(comparable(out));
        at = end + 1;
        if (at < row.size() && row[at] == ',') ++at;
    }
    return events;
}

std::vector<std::string> body_events(const std::vector<ShootNativeEvent>& raw) {
    std::vector<std::string> events;
    const auto i = [](std::int32_t value) { return number_text(value); };
    const auto f = [](std::int32_t value) { return number_text(remaining_real(static_cast<unsigned>(value))); };
    for (const auto& e : raw) {
        const auto& a = e.args;
        switch (e.address) {
            case 0x434a70: events.push_back("set_model," + i(a[0]) + "," + i(a[1])); break;
            case 0x434bd0: events.push_back("model_flush"); break;
            case 0x434b30: events.push_back("model_update"); break;
            case 0x421080: events.push_back("next_state," + i(a[0])); break;
            case 0x421100: events.push_back("next_phase," + i(a[0])); break;
            case 0x4230e0: events.push_back("attack_count"); break;
            case 0x423000: events.push_back("start_animation"); break;
            case 0x422900: events.push_back("stop_animation"); break;
            case 0x42c8b0: events.push_back("effect," + i(a[0]) + ",0x42c8b0"); break;
            case 0x42c880: events.push_back("effect," + i(a[0]) + ",0x42c880"); break;
            case 0x4223d0: events.push_back("voice," + i(a[0]) + ",0x4223d0"); break;
            case 0x422240: events.push_back("voice," + i(a[0]) + ",0x422240"); break;
            case 0x422490: events.push_back("voice," + i(a[0]) + ",0x422490"); break;
            // FUN_00434fd0 was not stubbed under the emulator: it reaches 0x435000 with attachment 0.
            case 0x434fd0: events.push_back("fire_attachment," + i(0) + "," + i(a[0]) + "," + f(a[1]) + "," + f(a[2]) + "," + i(a[3])); break;
            case 0x435000: events.push_back("fire_attachment," + i(a[0]) + "," + i(a[1]) + "," + f(a[2]) + "," + f(a[3]) + "," + i(a[4])); break;
            case 0x435220: events.push_back("fire_hand," + i(a[1]) + "," + f(a[2]) + "," + f(a[3])); break;
            case 0x435450: events.push_back("fire_world," + i(a[0]) + "," + f(a[1]) + "," + f(a[2]) + "," + f(a[3]) + "," + f(a[4]) + "," + f(a[5])); break;
            default: break;
        }
    }
    for (auto& event : events) event = comparable(event);
    return events;
}

struct BodyTally {
    int rows = 0, agree = 0, transitionRows = 0, combos = 0;
    std::vector<std::string> noBody;
    std::map<std::string, int> byField, byCombo;
    std::vector<std::string> first;
};

// The author's state-400 traces: the original handler under Unicorn with forced phases and
// frames, scratch kept within a phase, RNG fixed at 5, zero target elevation and its services
// stubbed (generate_roster_ground_shot_oracle.py). Replayed on the same bank through the compiled
// shot bodies. Those stubs make FUN_00421080/FUN_00421100 inert in the original run, while the
// body's own versions take effect, so a row that transitions is compared up to the transition
// and its motion and scratch are not. Rena's hand-written shots have no generated body.
// fixedRandom other than the emulator's 5 is the negative control.
BodyTally replay_shot_traces(const fs::path& trace, unsigned fixedRandom = 5) {
    BodyTally tally;
    std::ifstream file(trace);
    std::string line;
    int lastCombo = -1;
    bool skip = false;
    ShootNativeServices services;
    services.invoke = [](const ShootNativeEvent&, ShootBodyContext&) { return 0; };
    ShootNativeInput input;
    input.random = [fixedRandom] { return fixedRandom; };
    // The harness's fake animation: 100000 frames long, so no row completes on its own.
    ShootNativePhase longPhase{};
    longPhase.duration = 100000;
    ShootNativeDat dat{};
    for (unsigned state = 0; state < 1000; ++state) dat[state] = std::vector<ShootNativePhase>(8, longPhase);
    input.dat = &dat;
    input.animation_metadata = [&](int) { return longPhase; };
    auto bank = std::make_unique<std::array<std::int32_t, 0x2be0>>();
    while (std::getline(file, line)) {
        const int character = static_cast<int>(field(line, "character")), weapon = static_cast<int>(field(line, "weapon"));
        const int phase = static_cast<int>(field(line, "phase")), frame = static_cast<int>(field(line, "frame"));
        const int combo = character * 10 + weapon;
        const std::string label = std::to_string(character) + "+" + std::to_string(weapon);
        if (combo != lastCombo) {
            lastCombo = combo;
            skip = !shoot_native_body_binding(static_cast<unsigned>(character), static_cast<unsigned>(weapon), 400);
            if (skip) tally.noBody.push_back(label); else ++tally.combos;
        }
        if (skip) continue;
        input.character = static_cast<unsigned>(character);
        input.weapon = static_cast<unsigned>(weapon);
        input.state = 400;
        input.duration = 100000;
        input.hold = 0;
        ShootBodyContext n(input, services);
        const auto setReal = [&](unsigned offset, float value) { (*bank)[offset / 4] = remaining_bits(value); };
        if (frame == 0) {
            bank->fill(0);
            (*bank)[0x834 / 4] = 1000;
            setReal(0x54, 10.f); setReal(0x64, 30.f); setReal(0x60, 90.f); setReal(0x58, .25f); setReal(0x40, 0.f);
        }
        n.w = *bank;
        n.w[0xadec / 4] = 400; n.w[0xadf4 / 4] = phase; n.w[0xae04 / 4] = frame; n.w[0xae08 / 4] = frame + 3;
        n.w[0x6dc / 4] = static_cast<int>(field(line, "rounds"));
        if (line.find("\"secondary_rounds\"") != std::string::npos) n.w[0x720 / 4] = static_cast<int>(field(line, "secondary_rounds"));
        n.w[0x284 / 4] = static_cast<int>(field(line, "melee_held"));
        n.w[0x2b4 / 4] = static_cast<int>(field(line, "melee_released"));
        const auto setByte = [&](unsigned offset, unsigned value) {
            auto word = static_cast<std::uint32_t>(n.w[offset / 4]);
            const unsigned shift = (offset % 4) * 8;
            word = (word & ~(255u << shift)) | ((value & 255u) << shift);
            n.w[offset / 4] = static_cast<std::int32_t>(word);
        };
        setByte(0x84, static_cast<unsigned>(field(line, "grounded")));
        setByte(0x845, static_cast<unsigned>(field(line, "active")));
        setByte(0x848, static_cast<unsigned>(field(line, "special_flag")));
        std::string thrown;
        try {
            dispatch_shoot_body(n, input.character, input.weapon, 400);
        } catch (const std::exception& error) {
            thrown = error.what();
        }
        ++tally.rows;
        auto expected = trace_events(line), actual = body_events(n.out.events);
        const auto cut = [](std::vector<std::string>& events) {
            const auto end = std::find_if(events.begin(), events.end(), is_transition);
            const bool found = end != events.end();
            if (found) events.erase(end + 1, events.end());
            return found;
        };
        const bool transition = cut(expected);
        cut(actual);
        if (transition) ++tally.transitionRows;
        const auto real = [&](unsigned offset) { return remaining_real(static_cast<unsigned>(n.w[offset / 4])); };
        const auto near = [](double a, double b) { return std::abs(a - b) < 1e-3; };
        std::string wrong;
        if (!thrown.empty()) wrong = "threw";
        else if (actual != expected) wrong = "events";
        else if (!transition) {
            if (!near(real(0x54), field(line, "speed"))) wrong = "speed";
            else if (!near(real(0x64), field(line, "offset"))) wrong = "offset";
            else if (!near(real(0x60), field(line, "movement"))) wrong = "movement";
            else if (!near(real(0x58), field(line, "gravity"))) wrong = "gravity";
            else if (n.w[0xe8 / 4] != field(line, "scratch_e8") || n.w[0xec / 4] != field(line, "scratch_ec") ||
                     n.w[0xf0 / 4] != field(line, "scratch_f0") || n.w[0xf8 / 4] != field(line, "scratch_f8")) wrong = "scratch";
            else if (n.w[0xae04 / 4] != field(line, "frame_after")) wrong = "frame";
        }
        if (wrong.empty()) {
            ++tally.agree;
        } else {
            ++tally.byField[wrong];
            if (tally.byCombo[label]++ < 1 && tally.first.size() < 24) {
                std::string detail = label + " p" + std::to_string(phase) + " f" + std::to_string(frame) + " " + wrong + (thrown.empty() ? "" : " (" + thrown + ")");
                if (wrong == "events") {
                    detail += "\n    original:";
                    for (const auto& event : expected) detail += " [" + event + "]";
                    detail += "\n    core:    ";
                    for (const auto& event : actual) detail += " [" + event + "]";
                } else {
                    detail += " speed " + number_text(real(0x54)) + "/" + number_text(field(line, "speed")) +
                              " e8 " + std::to_string(n.w[0xe8 / 4]) + "/" + number_text(field(line, "scratch_e8")) +
                              " ec " + std::to_string(n.w[0xec / 4]) + "/" + number_text(field(line, "scratch_ec")) +
                              " f0 " + std::to_string(n.w[0xf0 / 4]) + "/" + number_text(field(line, "scratch_f0")) +
                              " f8 " + std::to_string(n.w[0xf8 / 4]) + "/" + number_text(field(line, "scratch_f8"));
                }
                tally.first.push_back(detail);
            }
        }
        *bank = n.w;
    }
    return tally;
}

}  // namespace

int main() {
    const fs::path evidence = find_evidence();
    if (evidence.empty()) {
        std::puts("SIM_ORACLE: skipped, no porting-support bundle");
        return 77;
    }
    int failures = 0;
    const std::pair<const char*, const char*> tables[] = {
        {"roster-input-cancel-contexts-20260928.tsv", "roster-input-cancels-original-20260928.tsv"},
        {"roster-ground-shot-input-contexts-20260928.tsv", "roster-ground-shot-input-original-20260928.tsv"},
    };
    for (const auto& [contexts, original] : tables) {
        const Tally tally = replay(evidence / contexts, evidence / original);
        std::printf("%s: %d/%d agree; state requests %d/%d\n", original, tally.agree, tally.cases, tally.requestsAgree, tally.requests);
        for (const auto& [row, got] : tally.firstMismatches) std::printf("  original [%s] core %d\n", row.c_str(), got);
        failures += tally.cases - tally.agree;
        if (tally.cases == 0) ++failures;
    }
    const Tally control = replay(evidence / tables[0].first, evidence / tables[0].second, 1);
    std::printf("negative control, wrong weapon: %d/%d agree\n", control.agree, control.cases);
    if (control.agree == control.cases) ++failures;

    for (const char* name : {"roster-ground-shot400-continuity-extended.jsonl", "roster-ground-shot400-special-extended.jsonl"}) {
        const BodyTally tally = replay_shot_traces(evidence.parent_path() / "traces" / name);
        std::printf("%s: %d/%d agree over %d combos, %d compared up to a transition; no shot body:", name, tally.agree, tally.rows,
                    tally.combos, tally.transitionRows);
        for (const auto& label : tally.noBody) std::printf(" %s", label.c_str());
        std::puts("");
        for (const auto& [wrong, count] : tally.byField) std::printf("  %s: %d\n", wrong.c_str(), count);
        for (const auto& [combo, count] : tally.byCombo) std::printf("  combo %s: %d\n", combo.c_str(), count);
        for (const auto& row : tally.first) std::printf("  %s\n", row.c_str());
        failures += tally.rows - tally.agree;
        if (tally.rows == 0) ++failures;
    }
    const BodyTally wrongRandom = replay_shot_traces(evidence.parent_path() / "traces" / "roster-ground-shot400-continuity-extended.jsonl", 6);
    std::printf("negative control, wrong RNG value: %d/%d agree\n", wrongRandom.agree, wrongRandom.rows);
    if (wrongRandom.agree == wrongRandom.rows) ++failures;
    std::printf("SIM_ORACLE: %s\n", failures ? "FAIL" : "ok");
    return failures ? 1 : 0;
}
