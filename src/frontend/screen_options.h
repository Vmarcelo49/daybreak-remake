#pragma once
#include "frontend/screen.h"
#include "input/input.h"
namespace ui {
// FUN_00404a50's label order — the original's twelve bindable actions, with no
// remake-only row: the heavy stand-in is gone (issue #10).
inline constexpr fnd::input::Action kBindingRowActions[] = {
    fnd::input::Up, fnd::input::Down, fnd::input::Left, fnd::input::Right,
    fnd::input::Jump, fnd::input::AttackA, fnd::input::Shoot, fnd::input::LockSwitch,
    fnd::input::Special, fnd::input::Guard, fnd::input::Tactics, fnd::input::Pause
};
std::unique_ptr<Screen> makeOptionsScreen(SpriteRenderer&, std::string&);
std::unique_ptr<Screen> makeKeyConfigScreen(SpriteRenderer&, std::string&);
}
