#include "ui/screen_vs.h"
#include <cstdio>
#include "ui/hud_atlas.h"
namespace ui {
namespace {
class VsScreen final : public Screen {
public:
    VsScreen(SpriteRenderer& batch, const FrontendState& state, std::string& error) : state_(state) {
        const char* stems[] = {"data/vs/vs01", "data/vs/vs02", "data/vs/vs03", "data/select/p03"};
        for (int i = 0; i < 6; ++i) {
            char portrait[64];
            if (i >= 4) std::snprintf(portrait, sizeof(portrait), "data/select/%02d",
                                      state.slots[kFrontendBattleSlots[i - 4]].character < 0 ? 0 : state.slots[kFrontendBattleSlots[i - 4]].character);
            std::string failure;
            if (!uploadCnvSheet(batch, i < 4 ? stems[i] : portrait, sheets_[i], failure) && error.empty())
                error = failure;
        }
    }
    bool loaded() const { for (int slot : sheets_) if (slot < 0) return false; return true; }
    const char* name() const override { return "vs"; }
    ScreenId update(const ScreenInput& input) override {
        // Confirm skip is a port extension; FUN_00411ae0 has no input branch.
        return timeline_.update(input.confirm) ? ScreenId::Battle : ScreenId::VsIntro;
    }
    void draw(SpriteRenderer& batch) const override {
        batch.pushTextured(sheets_[0], {0,0,800,300}, {0,0,1,1}, {});
        batch.pushTextured(sheets_[1], {0,300,800,300}, {0,0,1,1}, {});
        const float nameX[] = {150,650}, nameY[] = {200,400};
        const float portraitX[] = {600,200};
        for (int i = 0; i < 2; ++i) {
            const int character = state_.slots[kFrontendBattleSlots[i]].character < 0 ? 0 : state_.slots[kFrontendBattleSlots[i]].character;
            batch.pushSprite(sheets_[3], {(character / 8) * 256.f, (character % 8) * 64.f,256,64},
                             128,32,nameX[i],nameY[i]);
        }
        for (int i = 0; i < 2; ++i) {
            const float x = portraitX[i] + (i == 0 ? -timeline_.offset(0) : timeline_.offset(3));
            uint32_t w = 0, h = 0;
            if (batch.textureSize(sheets_[i+4], w, h)) {
                const float u = 256.f / w, v = 256.f / h;
                batch.pushTextured(sheets_[i+4], {x-128, (i == 0 ? 295.f : 600.f)-256,256,256},
                                   {i == 0 ? u : 0.f,0,i == 0 ? -u : u,v}, {});
            }
        }
        if (timeline_.frame() > 90)
            batch.pushSprite(sheets_[2], {0,0,256,256},128,128,400,300,timeline_.scale(),
                             (timeline_.scale()-1)*42);
    }
private:
    const FrontendState& state_;
    VsTimeline timeline_;
    int sheets_[6] = {-1,-1,-1,-1,-1,-1};
};
}
std::unique_ptr<Screen> makeVsScreen(SpriteRenderer& batch, FrontendState& state, std::string& error) {
    auto screen = std::make_unique<VsScreen>(batch,state,error);
    if (!screen->loaded()) return nullptr;
    return screen;
}
}
