#include "ui/screen_countdown.h"

#include "ui/caption.h"
#include "ui/hud.h"
#include "ui/hud_atlas.h"

namespace ui {

CountdownScreen::CountdownScreen(SpriteRenderer& batch, const CountdownInfo& info, bool& ready,
                                 std::string& error)
    : clock_(info.tickRate), ready_(ready), roster_(info.roster),
      rosterLayout_(info.roster.size()) {
    uploadCnvSheet(batch, "data/object/P09", sheet_, error);
    if (!loadCaptionFont(text_, 18.f, error)) return;
    settingsLayout_ = text_.layout(info.settings.c_str());
    for (size_t i = 0; i < roster_.size(); ++i)
        rosterLayout_[i] = text_.layout(roster_[i].text.c_str());
    textSlot_ = batch.addTexture(text_.atlasWidth(), text_.atlasHeight(),
                                 text_.atlasRGBA().data(), error);
}

ScreenId CountdownScreen::update(const ScreenInput&) {
    clock_.tick();
    // The gate, not a transition: `ready` is the app's own flag (frontendBattleReady), and
    // the hand-over it triggers is what starts the round. This screen keeps asking for the
    // id it already is, which the stack reads as "stay".
    if (clock_.done()) ready_ = true;
    return ScreenId::Battle;
}

void CountdownScreen::draw(SpriteRenderer& batch) const {
    // Deliberately NO background quad (issue #47): the app renders the live battle scene
    // underneath and composites this draw over it, so an opaque full-canvas solid here is
    // exactly the black countdown the issue reports.
    const int n = clock_.cell();
    const float w = n == 2 ? 128.f : 192.f;
    batch.pushSprite(sheet_, {n * 192.f, 0, w, 256}, w / 2, 128, 400, 300, .5f);
    if (textSlot_ < 0) return;
    drawCaptionLayout(batch, text_, settingsLayout_, textSlot_, bitmapSlot_, 40.f, 40.f, .8f,
                      kHudWhite, 2.f);
    for (size_t i = 0; i < roster_.size(); ++i)
        drawCaptionLayout(batch, text_, rosterLayout_[i], textSlot_, bitmapSlot_, 40.f,
                          70.f + 26.f * (float)i, .8f,
                          roster_[i].blue ? kHudLimitLeft : kHudLimitRight, 2.f);
}

std::unique_ptr<Screen> makeCountdownScreen(SpriteRenderer& batch, const CountdownInfo& info,
                                            bool& ready, std::string& error) {
    auto screen = std::make_unique<CountdownScreen>(batch, info, ready, error);
    if (!screen->loaded()) return nullptr;
    return screen;
}

}  // namespace ui
