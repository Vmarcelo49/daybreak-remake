// anim_sets_dump.cpp — dev-only: dump, per animation set, which bones it animates.
// Used to find base (full-body) vs overlay (arms-only) sets for the B2 composite.
//
//   g++ -std=c++17 -O1 -I src -I third_party/glm tools/anim_sets_dump.cpp -o /tmp/asd
//   /tmp/asd <path-to-00.X>

#define XMODEL_IMPLEMENTATION
#include "assets/xmodel.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: %s <file.X>\n", argv[0]);
        return 1;
    }
    xm::Model m = xm::loadFile(argv[1]);
    if (m.frames.empty()) {
        std::fprintf(stderr, "no frames loaded from %s\n", argv[1]);
        return 2;
    }

    std::printf("frames=%zu anims=%zu ticksPerSecond=%.0f\n", m.frames.size(),
                m.anims.size(), (double)m.ticksPerSecond);

    // Bone categories of interest (Biped names).
    auto cat = [](const std::string& n) -> const char* {
        if (n.rfind("Bip00_", 0) == 0) {
            if (n.find("Thigh") != std::string::npos) return "LEG";
            if (n.find("Calf") != std::string::npos) return "LEG";
            if (n.find("Foot") != std::string::npos) return "LEG";
            return "ROOT";
        }
        if (n == "Bip01_Pelvis" || n == "Bip01_Spine" || n == "Bip01_Spine1" ||
            n == "Bip01_Spine2" || n == "Bip01_Neck" || n == "Bip01_Head")
            return "TORSO";
        if (n.find("UpperArm") != std::string::npos || n.find("Forearm") != std::string::npos ||
            n.find("Hand") != std::string::npos || n.find("Prop") != std::string::npos)
            return "ARM";
        return "OTHER";
    };

    for (size_t s = 0; s < m.anims.size(); ++s) {
        const xm::AnimSet& a = m.anims[s];
        std::vector<int> fr;
        for (const xm::Channel& c : a.channels)
            if (c.frame >= 0 && std::find(fr.begin(), fr.end(), c.frame) == fr.end())
                fr.push_back(c.frame);
        std::sort(fr.begin(), fr.end());

        int leg = 0, arm = 0, torso = 0, root = 0, other = 0;
        for (int f : fr) {
            const char* c = cat(m.frames[(size_t)f].name);
            if (!std::strcmp(c, "LEG")) ++leg;
            else if (!std::strcmp(c, "ARM")) ++arm;
            else if (!std::strcmp(c, "TORSO")) ++torso;
            else if (!std::strcmp(c, "ROOT")) ++root;
            else ++other;
        }
        std::printf("[%3zu] %-10s dur=%6.1f ch=%4zu bones=%zu (leg=%d arm=%d torso=%d root=%d oth=%d)\n",
                    s, a.name.c_str(), (double)a.duration, a.channels.size(), fr.size(), leg,
                    arm, torso, root, other);
    }
    return 0;
}
