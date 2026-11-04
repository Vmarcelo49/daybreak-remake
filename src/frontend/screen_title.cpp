// frontend/screen_title.cpp — scene 1: the three sheets and FUN_00410f60's cursor machine.
// The header carries the provenance; this file is the transcription.
#include "frontend/screen_title.h"

#include <cstdio>

#include <SDL3/SDL.h>

#include "frontend/menu_panel.h"
#include "hud/hud_atlas.h"

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
    // The notice is text, which the original title has none of; the face is best-effort so
    // a missing font never costs the player the menu.
    std::string faceError;
    faceLoaded_ = face_.load(batch, 64.f, faceError, "Goldman-Bold.ttf",
                             kCaptionFallbackFile);
    if (!faceLoaded_) {
        std::fprintf(stderr, "[title] update notice text unavailable: %s\n",
                     faceError.c_str());
    }
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
    if (notice_.visible()) {
        if (noticeFocus_) {
            if (in.up || in.cancel) {
                noticeFocus_ = false;
                notice_.focus(false);
                sound_ = 1;
                return ScreenId::Title;
            }
            const UpdateNoticeAction chosen = notice_.update(in);
            switch (chosen) {
                case UpdateNoticeAction::Update:
                    notice_.hide();
                    return ScreenId::Update;
                case UpdateNoticeAction::Notes:
                    openUrl(notice_.notice().notes.c_str());
                    sound_ = 0;
                    break;
                case UpdateNoticeAction::Later:
                    notice_.hide();
                    noticeFocus_ = false;
                    notice_.focus(false);
                    sound_ = 1;
                    break;
                case UpdateNoticeAction::Skip:
                    noticeFocus_ = false;
                    notice_.focus(false);
                    sound_ = 0;
                    break;
                case UpdateNoticeAction::None:
                    break;
            }
            return ScreenId::Title;
        }
        // Down from the last title item moves into the notice; the title menu keeps its
        // own machine until then (the task's "does not steal input").
        if (in.down && menu_.selected() == kTitleItemCount - 1 &&
            updateNoticeChoiceCount(notice_.notice()) > 0) {
            noticeFocus_ = true;
            notice_.focus(true);
            sound_ = 2;
            return ScreenId::Title;
        }
    }
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
    //
    // The background is the one sheet the live backdrop replaces (issue #98): the stage is
    // drawn under this batch by the host, and an 800x600 opaque sprite would hide it. The
    // original's draw has no such switch, so this is a port addition, labelled as such.
    if (!backdropLive_)
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
    if (notice_.visible()) drawNotice(batch);
}

void TitleScreen::drawNotice(SpriteRenderer& batch) const {
    const UpdateNotice& notice = notice_.notice();
    const int choices = updateNoticeChoiceCount(notice);
    // A banner over the logo (owner review): large, centred, unmissable, and clear of the
    // menu cells that start at y=285.
    constexpr float kLeft = 70.f, kRight = 730.f, kTop = 36.f;
    const float height = choices > 0 ? 176.f : 96.f;
    // Nearly opaque: the banner sits over the logo, and a translucent panel let the bright
    // logo glyphs through the text (owner review).
    batch.pushSolid({kLeft, kTop, kRight - kLeft, height},
                    UiColor{0.03f, 0.04f, 0.09f, 1.f});
    batch.pushSolid({kLeft, kTop, kRight - kLeft, 3.f}, kGold);
    if (!faceLoaded_) return;
    const auto text = [&](const char* value, float y, float size, UiColor colour) {
        const float width = face_.width(value) * size / 64.f;
        face_.draw(batch, value, 400.f - width / 2.f, y, size / 64.f, colour, 1.2f);
    };
    text(updateNoticeLine(notice).c_str(), kTop + 18.f, 24.f, kWhite);
    if (choices == 0) return;
    // Two centred rows of two large choices, each with the same highlight the menus use.
    const int perRow[2] = {2, 2};
    for (int row = 0; row < 2; ++row) {
        float total = 0.f;
        for (int i = 0; i < perRow[row]; ++i) {
            const int choice = row * 2 + i;
            total += face_.width(updateNoticeChoiceLabel(notice, choice)) * 20.f / 64.f;
        }
        total += 40.f * (perRow[row] - 1);
        float x = 400.f - total / 2.f;
        const float y = kTop + 74.f + row * 54.f;
        for (int i = 0; i < perRow[row]; ++i) {
            const int choice = row * 2 + i;
            const char* label = updateNoticeChoiceLabel(notice, choice);
            const float width = face_.width(label) * 20.f / 64.f;
            const bool selected = noticeFocus_ && notice_.selected() == choice;
            if (selected) batch.pushSolid({x - 10.f, y - 6.f, width + 20.f, 34.f}, kHighlight);
            face_.draw(batch, label, x, y, 20.f / 64.f, selected ? kWhite : kPale, 1.2f);
            x += width + 40.f;
        }
    }
}

std::unique_ptr<Screen> makeTitleScreen(SpriteRenderer& batch, std::string& error) {
    std::unique_ptr<TitleScreen> screen(new TitleScreen(batch, error));
    if (!screen->loaded()) {
        // Keep the asset-level reason (it names the file that missed) and add the one
        // thing a user can act on: which folder to point the port at.
        if (error.empty()) error = "the title screen art did not load";
        error += " — point the port at your Higurashi Daybreak folder, e.g. "
                 "--install=\"/path/to/Higurashi-Daybreak\"";
        return nullptr;
    }
    return screen;
}

}  // namespace ui
