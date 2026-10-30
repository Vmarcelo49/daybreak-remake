#pragma once
#include <string>
#include <cstdint>
#include <array>
#include "ui/frontend_state.h"
namespace ui {
const char* frontendCharacterDirectory(int index);
struct FrontendLaunch {
    std::string stage, character, enemy, weapon, enemyWeapon;
    int weaponId = 0, enemyWeaponId = 0;
    struct Fighter {
        int panel = -1;
        std::string character, weapon;
        int weaponId = 0;
    };
    // Panel order is the original's 0/1 blue team, 2/3 red team.
    std::array<Fighter, 4> fighters{};
    int fighterCount = 0;
};
// Resolve every selected panel. The legacy character/enemy members remain the
// panel-0/panel-2 view used by the current VS and result screens.
bool frontendLaunch(const FrontendState& state, FrontendLaunch& out, std::string& error, uint32_t seed = 0);
}
