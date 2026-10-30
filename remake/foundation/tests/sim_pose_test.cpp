// docs/DIRECTION.md, M4: can the core's bones drive our renderer? The core samples its own
// parse of the rig; ours samples through xm::Controller. For every set the scripted fighter binds
// on one channel, both must put each frame in the same place, or the renderer cannot take the
// core's pose.
#include "combo_fixture.h"
#include "sim/battle.h"
#include "sim/script.h"

#include <cstdio>
#include <cstring>
#include <map>
#include <sstream>

namespace {

glm::vec3 translation_of(const sim::Matrix& m) { return {m[12], m[13], m[14]}; }

struct SetResult { int samples = 0; float worst = 0.f; };

}  // namespace

int main() {
    const std::string game = test::gameInstall();
    if (game.empty()) {
        std::puts("SIM_POSE: skipped, no game install");
        return 77;
    }
    int failures = 0;
    test::Combo combo;
    std::string error;
    if (!combo.load(0, 0, error)) {
        std::printf("SIM_POSE: skipped, %s\n", error.c_str());
        return 77;
    }

    // Every combo's rig must line up with the core's bones, frame i at bone i+1.
    for (int c = 0; c < sim::character_count(); ++c) {
        const int data = gameplay::characterIndexForDir(sim::character_name(c));
        for (int w = 0; w < sim::weapon_count(c); ++w) {
            test::Combo other;
            if (data < 0 || !other.load(data, w, error)) {
                std::printf("  %s+%d: rig did not load\n", sim::character_name(c).c_str(), w);
                ++failures;
                continue;
            }
            sim::BattleConfig single;
            single.gameDir = game;
            single.slots.fill({c, w, true});
            sim::Battle rigOnly(single);
            std::vector<std::string> rigNames;
            std::vector<sim::Matrix> rigBones;
            rigOnly.bone_poses(0, rigNames, rigBones);
            int aligned = 0;
            for (size_t f = 0; f < other.model.frames.size() && f + 1 < rigNames.size(); ++f)
                aligned += rigNames[f + 1] == other.model.frames[f].name;
            if (aligned != static_cast<int>(other.model.frames.size()) || rigNames.size() != other.model.frames.size() + 1) {
                std::printf("  %s+%d: %d of %zu frames aligned, %zu bones\n", sim::character_name(c).c_str(), w, aligned,
                            other.model.frames.size(), rigNames.size());
                ++failures;
            }
        }
    }

    sim::BattleConfig config;
    config.gameDir = game;
    config.slots[0] = {0, 0, false};
    config.slots[1] = {1, 0, false};
    config.slots[2] = {2, 0, false};
    config.slots[3] = {3, 0, false};
    sim::Battle battle(config);
    std::istringstream plan("0 300 360 z=-1\n0 400 410 melee\n0 500 510 shoot\n0 700 710 jump\n0 800 860 x=1\n");
    const auto script = sim::parse_script(plan);

    std::vector<std::string> names;
    std::vector<sim::Matrix> bones;
    xm::Controller controller;
    controller.bind(&combo.model);
    std::vector<glm::mat4> ours;
    std::map<unsigned, SetResult> bySet;
    const float kTolerance = 0.1f;  // units; a fighter stands about 150 tall

    for (unsigned t = 0; t < 1000; ++t) {
        battle.step(sim::script_inputs(script, t));
        const sim::ActorAnimation animation = battle.animation(0);
        battle.bone_poses(0, names, bones);
        if (t == 0) {
            int aligned = 0;
            for (size_t f = 0; f < combo.model.frames.size(); ++f)
                aligned += f + 1 < names.size() && names[f + 1] == combo.model.frames[f].name;
            std::printf("frames %zu, core bones %zu, aligned at +1: %d\n", combo.model.frames.size(), names.size(), aligned);
            if (aligned != static_cast<int>(combo.model.frames.size())) ++failures;
        }
        if (animation.lowerSet != animation.upperSet || animation.lowerSet >= combo.model.anims.size()) continue;
        controller.setAnimation(static_cast<int>(animation.lowerSet), true);
        controller.setTrackPosition(0, animation.lowerTime);
        controller.evalWorld(ours);
        SetResult& result = bySet[animation.lowerSet];
        ++result.samples;
        for (size_t f = 0; f < combo.model.frames.size() && f + 1 < bones.size(); ++f) {
            const glm::vec3 delta = translation_of(bones[f + 1]) - glm::vec3(ours[f][3]);
            result.worst = std::max(result.worst, glm::length(delta));
        }
    }
    for (const auto& [set, result] : bySet) {
        std::printf("  set %3u %-14s samples %4d worst %.4f\n", set, combo.model.anims[set].name.c_str(), result.samples, result.worst);
        if (result.worst > kTolerance) ++failures;
    }
    if (bySet.size() < 4) ++failures;
    std::printf("SIM_POSE: %s\n", failures ? "FAIL" : "ok");
    return failures ? 1 : 0;
}
