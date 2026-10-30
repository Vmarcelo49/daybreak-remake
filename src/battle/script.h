#pragma once
// A scripted input plan for sim::Battle: plain text, one held span per line.
//
//   # slot from to  tokens...      `to` is exclusive
//   0 0 60 z=-1                    walk forward for a second
//   0 70 74 melee
//
// Tokens: x=N, z=N, jump, melee, shoot, target, guard. Spans on one slot merge.
#include "battle/battle.h"

#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace sim {

struct ScriptSpan {
    unsigned slot = 0, from = 0, to = 0;
    bool setX = false, setZ = false;
    SlotInput input;
};

inline std::vector<ScriptSpan> parse_script(std::istream& in) {
    std::vector<ScriptSpan> spans;
    std::string line;
    for (int number = 1; std::getline(in, line); ++number) {
        const auto fail = [&](const std::string& why) {
            throw std::runtime_error("script line " + std::to_string(number) + ": " + why);
        };
        if (const auto hash = line.find('#'); hash != std::string::npos) line.erase(hash);
        std::istringstream words(line);
        ScriptSpan span;
        if (!(words >> span.slot)) continue;
        if (!(words >> span.from >> span.to) || span.slot > 3 || span.to <= span.from) fail("expected slot from to");
        for (std::string token; words >> token;) {
            if (token.rfind("x=", 0) == 0) { span.input.x = std::stoi(token.substr(2)); span.setX = true; }
            else if (token.rfind("z=", 0) == 0) { span.input.z = std::stoi(token.substr(2)); span.setZ = true; }
            else if (token == "jump") span.input.buttons |= Jump;
            else if (token == "melee") span.input.buttons |= Melee;
            else if (token == "shoot") span.input.buttons |= Shoot;
            else if (token == "target") span.input.buttons |= Target;
            else if (token == "guard") span.input.buttons |= Guard;
            else fail("unknown token '" + token + "'");
        }
        spans.push_back(span);
    }
    return spans;
}

inline Inputs script_inputs(const std::vector<ScriptSpan>& spans, unsigned tick) {
    Inputs inputs{};
    for (const ScriptSpan& span : spans) {
        if (tick < span.from || tick >= span.to) continue;
        SlotInput& out = inputs[span.slot];
        if (span.setX) out.x = span.input.x;
        if (span.setZ) out.z = span.input.z;
        out.buttons |= span.input.buttons;
    }
    return inputs;
}

}  // namespace sim
