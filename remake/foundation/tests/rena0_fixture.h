// Shared fixture parser for the Rena+0 offline tests.
//
// The F1-3 acceptance runner (rena0_fixture_test.cpp) and the P2-5 fixture-linked
// differential (rena0_differential_test.cpp) read the same fixture files, so the format is
// parsed in exactly one place. See docs/PILOT-EVIDENCE-CONTRACT.md §8 for the format.
//
// This is a test-only header: it drives nothing and owns no product behaviour.
#pragma once

#include "input/input.h"

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <glm/glm.hpp>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace rena0fix {
namespace input = fnd::input;

struct Expectation {
    long long tick = 0;
    std::string field;
    double value = 0.0;
    int line = 0;
};

struct Fixture {
    std::string name;
    int character = -1, weapon = -1;
    unsigned seed = 0;
    bool seedSet = false;
    glm::vec3 spawn[2] = {glm::vec3(0.f), glm::vec3(0.f, 0.f, 2000.f)};
    bool collisionSet = false;
    std::map<long long, uint32_t> inputs;  // tick -> action bitmask
    std::vector<Expectation> expects;
    std::set<std::string> assertedFields;  // for the manifest's field-coverage check
    std::vector<long long> placeTicks;  // place the dummy at the attacker's posed volume
    bool placeOnActive = false;          // keep it there while the swing is active
    std::vector<long long> traceTicks;   // authoring aid: print the tick's key fields
    int dummyStartHp = 100;             // MatchConfig::startHP[1]
    int timeLimit = 0;                  // MatchConfig::timeLimit (0 = untimed)
    bool dummyGuard = false;            // hold the Guard action on the dummy's input
    bool pilotGuard = false;            // attach the recovered guard gate to the dummy
    bool hyperOyashiro = false;         // full gauge, Oyashiro selected and activated
    int  chargeGauge = 1000;            // MatchConfig leaves the shot gauge at its 1000 cap
    bool chargeGaugeSet = false;        // `charge_gauge` directive: a starting value below the cap
    long long maxTick = 0;
};

[[noreturn]] void fail(const Fixture& f, int line, const std::string& what) {
    throw std::runtime_error(f.name + ":" + std::to_string(line) + ": " + what);
}

Fixture parseFixture(const std::string& path) {
    std::ifstream in(path);
    if (!in) throw std::runtime_error("cannot open " + path);
    Fixture f;
    f.name = std::filesystem::path(path).filename().string();
    std::string line;
    int lineNo = 0;
    while (std::getline(in, line)) {
        ++lineNo;
        if (const size_t hash = line.find('#'); hash != std::string::npos) line.erase(hash);
        std::istringstream ls(line);
        std::string directive;
        if (!(ls >> directive)) continue;
        if (directive == "combo") {
            if (!(ls >> f.character >> f.weapon)) fail(f, lineNo, "combo needs character and weapon");
        } else if (directive == "seed") {
            if (!(ls >> f.seed)) fail(f, lineNo, "seed needs a value");
            f.seedSet = true;
        } else if (directive == "spawn") {
            int slot = 0;
            glm::vec3 at(0.f);
            if (!(ls >> slot >> at.x >> at.y >> at.z) || slot < 0 || slot > 1)
                fail(f, lineNo, "spawn needs slot 0/1 and x y z");
            f.spawn[slot] = at;
        } else if (directive == "collision") {
            std::string mode;
            if (!(ls >> mode)) fail(f, lineNo, "collision needs a mode");
            if (mode != "open-field") fail(f, lineNo, "only open-field fixtures are implemented");
            f.collisionSet = true;
        } else if (directive == "input") {
            long long tick = 0;
            std::string tokens;
            if (!(ls >> tick) || tick < 0) fail(f, lineNo, "input needs a non-negative tick");
            std::getline(ls, tokens);
            uint64_t frame = 0;
            uint32_t mask = 0;
            if (!input::parse_script_line((std::to_string(tick) + tokens).c_str(), frame, mask))
                fail(f, lineNo, "input line did not parse");
            f.inputs[tick] = mask;
            f.maxTick = std::max(f.maxTick, tick);
        } else if (directive == "place_at_attack") {
            // `place_at_attack active` mirrors the device-free melee tests: the victim is
            // kept on the attacker's posed volume on every tick the swing is active
            // (tests/damage_scale_test.cpp:184-185, tests/fighter_script_test.cpp:761).
            std::string when;
            if (!(ls >> when)) fail(f, lineNo, "place_at_attack needs a tick or 'active'");
            if (when == "active") {
                f.placeOnActive = true;
            } else {
                const long long tick = std::atoll(when.c_str());
                if (tick < 0 || std::to_string(tick) != when)
                    fail(f, lineNo, "place_at_attack tick must be non-negative or 'active'");
                f.placeTicks.push_back(tick);
                f.maxTick = std::max(f.maxTick, tick);
            }
        } else if (directive == "dummy_guard") {
            int on = 0;
            if (!(ls >> on) || (on != 0 && on != 1)) fail(f, lineNo, "dummy_guard needs 0 or 1");
            f.dummyGuard = on != 0;
        } else if (directive == "hyper") {
            std::string what;
            if (!(ls >> what) || what != "oyashiro")
                fail(f, lineNo, "hyper needs 'oyashiro' (the only mode whose powered branch exists)");
            f.hyperOyashiro = true;
        } else if (directive == "pilot") {
            std::string what;
            if (!(ls >> what) || what != "rena0-guard")
                fail(f, lineNo, "pilot needs 'rena0-guard' (the recovered guard gate)");
            f.pilotGuard = true;
        } else if (directive == "charge_gauge") {
            // Starting shot gauge, so the recovery rule's +40/clamp is observable. The product
            // caps the value at 1000 and only ever raises it on a recovery row, so a fixture
            // that needs to see the refill has to begin below the cap.
            if (!(ls >> f.chargeGauge) || f.chargeGauge < 0 || f.chargeGauge > 1000)
                fail(f, lineNo, "charge_gauge needs 0..1000");
            f.chargeGaugeSet = true;
        } else if (directive == "time_limit") {
            if (!(ls >> f.timeLimit) || f.timeLimit < 0) fail(f, lineNo, "time_limit needs seconds");
        } else if (directive == "dummy_start_hp") {
            if (!(ls >> f.dummyStartHp) || f.dummyStartHp < 0 || f.dummyStartHp > 100)
                fail(f, lineNo, "dummy_start_hp needs 0..100");
        } else if (directive == "trace") {
            // Authoring aid only: prints the tick's key fields instead of asserting, so a
            // fixture's anchors can be read off one run rather than bisected.
            long long tick = 0;
            if (!(ls >> tick) || tick < 0) fail(f, lineNo, "trace needs a non-negative tick");
            f.traceTicks.push_back(tick);
            f.maxTick = std::max(f.maxTick, tick);
        } else if (directive == "expect") {
            Expectation e;
            e.line = lineNo;
            if (!(ls >> e.tick >> e.field >> e.value)) fail(f, lineNo, "expect needs tick, field and value");
            f.expects.push_back(e);
            f.assertedFields.insert(e.field);
            f.maxTick = std::max(f.maxTick, e.tick);
        } else {
            fail(f, lineNo, "unknown directive '" + directive + "'");
        }
    }
    if (f.character < 0 || f.weapon < 0) throw std::runtime_error(f.name + ": missing combo");
    if (!f.seedSet) throw std::runtime_error(f.name + ": missing seed");
    if (!f.collisionSet) throw std::runtime_error(f.name + ": missing collision scope");
    if (f.expects.empty()) throw std::runtime_error(f.name + ": no expectations");
    return f;
}

}  // namespace rena0fix
