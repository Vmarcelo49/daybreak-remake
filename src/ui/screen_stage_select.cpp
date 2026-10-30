#include "ui/screen_stage_select.h"
#include "ui/hud_atlas.h"

namespace ui {
namespace {
int wrap(int value, int count) { return (value + count) % count; }
int stepped(int value, int delta, int low, int high, int step) {
    return low + wrap((value - low) / step + delta, (high - low) / step + 1) * step;
}
class StageSelectScreen final : public Screen {
public:
    StageSelectScreen(SpriteRenderer& batch, FrontendState& state, std::string& error)
        : state_(state), menu_(state) {
        const char* stems[] = {"data/select/sbg00", "data/select/pbg00", "data/select/pbg01",
                               "data/select/pbg02", "data/select/p01", "data/select/p02"};
        for (int i = 0; i < 6; ++i) {
            std::string failure;
            if (!uploadCnvSheet(batch, stems[i], sheets_[i], failure) && error.empty())
                error = failure;
        }
    }
    bool loaded() const { for (int slot : sheets_) if (slot < 0) return false; return true; }
    const char* name() const override { return "stage"; }
    ScreenId update(const ScreenInput& input) override {
        const int oldRow = menu_.row();
        const auto action = menu_.update(input);
        sound_ = action == StageAction::Start ? 0 : action == StageAction::Back ? 1 :
                 oldRow != menu_.row() || input.left || input.right ? 2 : -1;
        if (action == StageAction::Back) state_.stagePage = false;
        return action == StageAction::Start ? ScreenId::VsIntro : ScreenId::Select;
    }
    int takeSound() override { const int sound = sound_; sound_ = -1; return sound; }
    void draw(SpriteRenderer& batch) const override {
        batch.pushSprite(sheets_[0], {0, 0, 800, 600}, 0, 0, 0, 0);
        // FUN_00408330 configures 320x64 names and 250x50 thumbnail cells.
        batch.pushSprite(sheets_[menu_.row() == 0 ? 1 : 3], {0, state_.stage * 64.f, 320, 64}, 160, 32, 175, 125);
        if (state_.stage)
            batch.pushSprite(sheets_[menu_.row() == 1 ? 1 : 3], {384, (state_.variation + 1) * 64.f, 128, 64},
                             64, 32, 175, 175);
        const int column = state_.stage ? (state_.stage - 1) / 3 : 0;
        const int row = state_.stage ? (state_.stage - 1) % 3 * 3 + state_.variation : 9;
        batch.pushSprite(sheets_[2], {column * 250.f, row * 50.f, 250, 50}, 125, 25, 575, 150);
        for (int i = 0; i < 5; ++i)
            batch.pushSprite(sheets_[i < 3 ? 4 : 5],
                             {menu_.row() == i + 2 ? 0.f : 256.f, (i < 3 ? i + 5 : i - 3) * 64.f,
                              256, 64}, 128, 32, 175, 275 + i * 50.f);
        batch.pushSprite(sheets_[4], {0, menu_.row() == 7 && !menu_.backSelected() ? 0.f : 64.f,
                                     256, 64}, 128, 32, 275, 550);
        batch.pushSprite(sheets_[4], {384, menu_.row() == 7 && menu_.backSelected() ? 64.f : 128.f,
                                     128, 64}, 64, 32, 525, 550);
        const int values[] = {state_.timeLimit, state_.health, state_.gauge,
                              state_.blueBalloon, state_.redBalloon};
        for (int i = 0; i < 5; ++i) {
            const float y = 255 + i * 50.f;
            if (i == 0 && values[i] == 0) glyph(batch, 14, 530, y);
            else {
                int value = values[i];
                float x = 536;
                do { glyph(batch, value % 10, x, y); x -= 44; value /= 10; } while (value);
                if (i) glyph(batch, 13, 580, y);
            }
        }
    }
private:
    void glyph(SpriteRenderer& batch, int cell, float x, float y) const {
        // FUN_00431a50 / FUN_00408330: 64x64, eight columns, -20 pitch adjustment.
        batch.pushSprite(sheets_[4], {(cell % 8) * 64.f, 192 + (cell / 8) * 64.f, 64, 64},
                         0, 0, x, y);
    }
    FrontendState& state_;
    StageMenu menu_;
    int sound_ = -1;
    int sheets_[6] = {-1, -1, -1, -1, -1, -1};
};
}
StageAction StageMenu::update(const ScreenInput& input) {
    const int dx = input.left ? -1 : input.right ? 1 : 0;
    if (dx) {
        switch (row_) {
        case 0:
            state_.stage = wrap(state_.stage + dx, 7);
            if (state_.stage != 1 && state_.variation == 2) state_.variation = 1;
            break;
        case 1: state_.variation = wrap(state_.variation + dx, variationCount(state_.stage)); break;
        case 2: state_.timeLimit = wrap(state_.timeLimit + dx * 60, 300); break;
        case 3: state_.health = stepped(state_.health, dx, 50, 200, 25); break;
        case 4: state_.gauge = stepped(state_.gauge, dx, 50, 200, 25); break;
        case 5: state_.blueBalloon = stepped(state_.blueBalloon, dx, 40, 200, 20); break;
        case 6: state_.redBalloon = stepped(state_.redBalloon, dx, 40, 200, 20); break;
        case 7: back_ = !back_; break;
        }
    } else if (input.up || input.down) {
        const int dy = input.up ? -1 : 1;
        row_ = wrap(row_ + dy, 8);
        if (row_ == 1 && state_.stage == 0) row_ += dy;
    } else if (input.confirm && row_ == 7) {
        return back_ ? StageAction::Back : StageAction::Start;
    } else if (input.cancel) return StageAction::Back;
    return StageAction::None;
}
std::unique_ptr<Screen> makeStageSelectScreen(SpriteRenderer& batch, FrontendState& state,
                                             std::string& error) {
    auto screen = std::make_unique<StageSelectScreen>(batch, state, error);
    if (!screen->loaded()) return nullptr;
    return screen;
}
}
