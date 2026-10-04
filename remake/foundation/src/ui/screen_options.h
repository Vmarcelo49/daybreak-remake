#pragma once
#include "ui/screen.h"
#include "input/input.h"
namespace ui {
// FUN_00404a50's label order; the remake-only heavy action follows the original rows.
inline constexpr fnd::input::Action kBindingRowActions[] = {
    fnd::input::Up, fnd::input::Down, fnd::input::Left, fnd::input::Right,
    fnd::input::Jump, fnd::input::AttackA, fnd::input::Shoot, fnd::input::LockSwitch,
    fnd::input::Special, fnd::input::Guard, fnd::input::Tactics, fnd::input::Pause,
    fnd::input::AttackB
};
std::unique_ptr<Screen> makeOptionsScreen(SpriteRenderer&, std::string&);
std::unique_ptr<Screen> makeKeyConfigScreen(SpriteRenderer&, std::string&);
}
