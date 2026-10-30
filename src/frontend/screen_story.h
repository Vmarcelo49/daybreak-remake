#pragma once
#include <memory>
#include <string>

#include "frontend/screen.h"

namespace ui {

struct FrontendState;

// Scene 8, the story dialogue (FUN_0040e720, FUN_0040eb30, FUN_0040f130).
std::unique_ptr<Screen> makeStoryScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);

}  // namespace ui
