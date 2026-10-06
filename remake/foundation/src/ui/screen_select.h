#pragma once
#include <array>
#include "ui/screen.h"
#include "ui/frontend_state.h"

namespace ui {
// FUN_00409340: controller state differs from the selected panel's stored choices.
enum class SelectPhase { Team = 0, Controller = 1, Character = 2, Weapon = 3, Hypermode = 4, Ready = 8 };
enum class SelectAction { None, Changed, Back, Stage };
inline constexpr int kSelectRosterX[16] = {0,-2,-1,0,1,-1,-1,-2,0,1,2,2,1,0,3,-3};
inline constexpr int kSelectRosterY[16] = {6,4,5,4,5,3,1,2,2,3,4,2,1,0,3,3};
inline constexpr int kSelectRosterOrder[16] = {14,15,13,12,6,11,8,7,9,5,10,3,1,4,2,0};
inline constexpr int kSelectCostumes[16] = {5,5,3,5,5,5,2,4,2,2,3,3,1,2,4,5};

class SelectMenu {
public:
    explicit SelectMenu(FrontendState& state) : state_(state) {}
    SelectAction update(const ScreenInput& in, int controller = 0);
    SelectAction updateFrame(const ScreenInput& in, int* sound = nullptr);
    SelectPhase phase(int controller = 0) const { return phase_[controller]; }
    int cursor(int controller = 0) const { return cursor_[controller]; }
    // The character phase's free cursor (FUN_00409340 case 2, +0x3cd8/+0x3ce8), in the
    // roster's own units — the same space as kSelectRosterX[i]*48 and kSelectRosterY[i]*36,
    // which is what the selection radii and the magnet measure against.
    float cursorX(int controller = 0) const { return cursorX_[controller]; }
    float cursorY(int controller = 0) const { return cursorY_[controller]; }
    int panel(int controller = 0) const;
    int owner(int panel) const;
    void tick();
private:
    FrontendState& state_;
    std::array<SelectPhase,4> phase_{};
    std::array<int,4> cursor_{{0,-1,-1,-1}}, cooldown_{};
    std::array<float,4> cursorX_{}, cursorY_{};
};
class SelectScreen final : public Screen {
public:
    SelectScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
    ScreenId update(const ScreenInput& in) override;
    void draw(SpriteRenderer& batch) const override;
    const char* name() const override { return "select"; }
    bool loaded() const;
    std::string takeVoice() override { std::string voice; voice.swap(voice_); return voice; }
    int takeSound() override { int sound=sound_; sound_=-1; return sound; }
private:
    FrontendState& state_;
    SelectMenu menu_;
    SpriteRenderer& batch_;
    std::unique_ptr<Screen> stage_;
    int shared_[10]{}, portraits_[16]{}, chibi_[16]{}, costumes_[16]{}, weapons_[16]{};
    unsigned frames_ = 0;
    int sound_ = -1;
    std::string voice_;
};
std::unique_ptr<Screen> makeSelectScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
}
