// ui/screen_title.cpp — scene 1: the three sheets and FUN_00410f60's cursor machine.
// The header carries the provenance; this file is the transcription.
#include "ui/screen_title.h"

#include <cstdio>

#include "ui/hud_atlas.h"

namespace ui {

TitleAction TitleMenu::update(const ScreenInput& in) {
    // FUN_00410f60.c:101-135 tests confirm first: a confirmed item returns its scene id
    // and the cursor does not also move on that frame.
    if (in.confirm) return TitleAction::Activated;
    // Up is tested before down (FUN_00410f60.c:47-65 reads 0xc8 before 0xd0), so a frame
    // that holds both moves up.
    if (in.up) {
        selected_ = (selected_ + kTitleItemCount - 1) % kTitleItemCount;   // :142-145
        return TitleAction::Moved;
    }
    if (in.down) {
        selected_ = (selected_ + 1) % kTitleItemCount;   // :138-141
        return TitleAction::Moved;
    }
    return TitleAction::None;
}

TitleScreen::TitleScreen(SpriteRenderer& batch, std::string& error) {
    // All three loads are attempted, like FUN_00410d60.c:28-33: the first failure is
    // kept so the caller's message names a real asset.
    for (const TitleAsset& asset : kTitleAssets) {
        std::string failure;
        if (!uploadCnvSheet(batch, asset.stem, sheets_[(int)asset.sheet], failure) &&
            error.empty())
            error = failure;
    }
}

bool TitleScreen::loaded() const {
    for (int slot : sheets_)
        if (slot < 0) return false;
    return true;
}

ScreenId TitleScreen::update(const ScreenInput& in) {
    const TitleAction action = menu_.update(in);
    sound_ = action == TitleAction::Moved ? 2 : (action == TitleAction::Activated ? 0 : -1);
    if (action != TitleAction::Activated) return ScreenId::Title;

    const TitleEntry& entry = kTitleEntries[menu_.selected()];
    if (entry.next == ScreenId::Quit || screenAvailable(entry.next)) return entry.next;

    // Story and network scenes remain outside this offline front-end track (D6).
    std::printf("[title] item %d %s -> scene 0x%02x: no screen yet, staying on the title\n",
                menu_.selected(), entry.label, (int)entry.next);
    return ScreenId::Title;
}

void TitleScreen::draw(SpriteRenderer& batch) const {
    // FUN_004114f0.c:17-22's order: background, logo, then the six item cells. The cell
    // column is the selection (0 white = selected, 1 dark = not), which is what
    // FUN_00655830's third argument `selected != i` selects in the original.
    batch.pushSprite(sheets_[(int)TitleSheet::Back], kTitleBackSrc, 0.f, 0.f, 0.f, 0.f);
    batch.pushSprite(sheets_[(int)TitleSheet::Logo], kTitleLogoSrc, kTitleLogoPivotX,
                     kTitleLogoPivotY, kTitleLogoX, kTitleLogoY);
    for (int i = 0; i < kTitleItemCount; ++i) {
        const UiRect src{kTitleItemSrc.x + (menu_.selected() == i ? 0.f : kTitleItemSrc.w),
                         kTitleItemSrc.y + kTitleItemStride * (float)i, kTitleItemSrc.w,
                         kTitleItemSrc.h};
        batch.pushSprite(sheets_[(int)TitleSheet::Items], src, kTitleItemPivotX, kTitleItemPivotY,
                         kTitleItemX, kTitleItemStride * (float)i + kTitleItemY0);
    }
}

std::unique_ptr<Screen> makeTitleScreen(SpriteRenderer& batch, std::string& error) {
    std::unique_ptr<TitleScreen> screen(new TitleScreen(batch, error));
    if (!screen->loaded()) {
        if (error.empty())
            error = "title: one of data/title/{back00,logo,title} did not load";
        return nullptr;
    }
    return screen;
}

}  // namespace ui
