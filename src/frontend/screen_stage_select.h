#pragma once
#include "frontend/screen.h"
#include "frontend/frontend_state.h"

namespace ui {
enum class StageAction { None, Start, Back };
// FUN_0040acb0: eight rows; random stage suppresses the variation row.
class StageMenu {
public:
    explicit StageMenu(FrontendState& state) : state_(state) {}
    StageAction update(const ScreenInput& input);
    int row() const { return row_; }
    bool backSelected() const { return back_; }
    // FUN_00408330 writes byte 1 at dword offset 0xf64 (=0x3d90); school adds it to 2.
    static int variationCount(int stage) { return stage == 1 ? 3 : 2; }
private:
    FrontendState& state_;
    int row_ = 0;
    bool back_ = false;
};
std::unique_ptr<Screen> makeStageSelectScreen(SpriteRenderer& batch, FrontendState& state,
                                             std::string& error);
}
