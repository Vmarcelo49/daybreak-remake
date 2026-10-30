#pragma once
#include <memory>
#include <string>

#include "frontend/screen.h"

namespace ui {

struct FrontendState;

// Scene 8, the story dialogue (FUN_0040e720, FUN_0040eb30, FUN_0040f130).
std::unique_ptr<Screen> makeStoryScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
// Scene 5, the team select.
std::unique_ptr<Screen> makeStoryTeamScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
// A lost story fight's prompt, over the battle (FUN_00635d40 case 3, FUN_0063aee0 case 3).
std::unique_ptr<Screen> makeStoryRetryScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
// Scene 0x14 (FUN_00403c60, FUN_00403d70).
std::unique_ptr<Screen> makeGameOverScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
// Loads team `team`'s ladder into the state, at its first fight.
bool beginStoryTeam(FrontendState& state, int team, std::string& error);

}  // namespace ui
