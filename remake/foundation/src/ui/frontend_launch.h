#pragma once
#include <string>
#include <cstdint>
#include "ui/frontend_state.h"
namespace ui {
const char* frontendCharacterDirectory(int index);
struct FrontendLaunch {
    std::string stage, character, enemy, weapon, enemyWeapon;
    int weaponId = 0, enemyWeaponId = 0;
};
// The current simulation supports two fighters. Reject extra human panels explicitly.
bool frontendLaunch(const FrontendState& state, FrontendLaunch& out, std::string& error, uint32_t seed = 0);
}
