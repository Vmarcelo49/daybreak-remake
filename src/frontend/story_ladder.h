#pragma once
// frontend/story_ladder.h — a story team's six fights, data/scenario/team<NN>.dat.
//
// FUN_00648f30 reads the file and FUN_006492f0 sets up each fight. The file is two little-endian
// ints (the team), six rows of five ints (two enemies, stage, music track, script id), then the
// ending movie's path as a C string. Character numbers are kCharacterDirs' indices.
#include <array>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace ui {

inline constexpr int kStoryTeams = 10;
inline constexpr int kStoryFights = 6;

struct StoryFight {
    std::array<int, 2> enemies{{0, 0}};
    int stage = 0, music = 0, script = 0;
};

struct StoryLadder {
    bool active = false;  // DAT_006cfce9
    int team = 0;
    std::array<int, 2> members{{0, 0}};
    std::array<StoryFight, kStoryFights> fights{};
    std::string endingMovie;
    int fight = 0;  // DAT_006cfbc4
    int part = 0;   // DAT_006cfbc5: 0 before the battle, 1 after it

    const StoryFight& current() const { return fights[fight]; }
    std::string scriptPath() const;
};

// `random` stands in for FUN_0065d150. False when the file is too short.
bool parseStoryLadder(const std::vector<uint8_t>& bytes, int team,
                      const std::function<uint32_t()>& random, StoryLadder& out);

// The enemy's weapon slot for this fight (FUN_006492f0:27-44). Rena and Rika draw from their first
// two weapons, since the third is their alternate persona, which only team 7's last fight uses.
int storyEnemyWeapon(int team, int fight, int character, uint32_t randomValue);

}  // namespace ui
