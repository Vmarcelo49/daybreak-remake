#include "frontend/story_ladder.h"

#include <algorithm>
#include <cstdio>
#include <utility>

namespace ui {
namespace {

constexpr size_t kPrefixBytes = (2 + 5 * kStoryFights) * 4;

int intAt(const std::vector<uint8_t>& bytes, size_t index) {
    const uint8_t* p = bytes.data() + index * 4;
    return static_cast<int>(static_cast<uint32_t>(p[0]) | static_cast<uint32_t>(p[1]) << 8 |
                            static_cast<uint32_t>(p[2]) << 16 | static_cast<uint32_t>(p[3]) << 24);
}

}  // namespace

std::string StoryLadder::scriptPath() const {
    char path[64];
    std::snprintf(path, sizeof path, "data/scenario/D%02d-%d.txt", current().script, part);
    return path;
}

bool parseStoryLadder(const std::vector<uint8_t>& bytes, int team,
                      const std::function<uint32_t()>& random, StoryLadder& out) {
    if (bytes.size() < kPrefixBytes) return false;
    out = StoryLadder{};
    out.team = team;
    out.members = {intAt(bytes, 0), intAt(bytes, 1)};

    // Rows 1..3 change places, except on teams 1, 5 and 6; the first and last two stay.
    std::array<int, kStoryFights> order{{0, 1, 2, 3, 4, 5}};
    if (team != 1 && team != 5 && team != 6) {
        for (int i = 0; i < 16; ++i) {
            const uint32_t a = random(), b = random();
            std::swap(order[a % 3 + 1], order[b % 3 + 1]);
        }
    }
    for (int row = 0; row < kStoryFights; ++row) {
        const size_t at = 2 + static_cast<size_t>(row) * 5;
        StoryFight& fight = out.fights[order[row]];
        fight.enemies = {intAt(bytes, at), intAt(bytes, at + 1)};
        fight.stage = intAt(bytes, at + 2);
        fight.music = intAt(bytes, at + 3);
        fight.script = intAt(bytes, at + 4);
    }
    const auto text = bytes.begin() + static_cast<std::ptrdiff_t>(kPrefixBytes);
    out.endingMovie.assign(text, std::find(text, bytes.end(), uint8_t{0}));
    return true;
}

int storyEnemyWeapon(int team, int fight, int character, uint32_t randomValue) {
    if (team == 7 && fight == 5) return 2;
    return static_cast<int>(randomValue % (character == 0 || character == 4 ? 2u : 3u));
}

}  // namespace ui
