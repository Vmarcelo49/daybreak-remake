#pragma once
// The look of the screens that are ours rather than the original's, such as the options and online
// play: panels and one face of type over the original's backgrounds.
#include <initializer_list>
#include <string>

#include "frontend/screen.h"
#include "ui/caption.h"
#include "ui/sheet_locale.h"

namespace ui {

inline constexpr UiColor kWhite{1.f, 1.f, 1.f, 1.f};
inline constexpr UiColor kPale{0.72f, 0.76f, 0.86f, 1.f};
inline constexpr UiColor kGold{1.f, 0.82f, 0.3f, 1.f};
inline constexpr UiColor kPanel{0.03f, 0.04f, 0.09f, 0.72f};
inline constexpr UiColor kHighlight{0.16f, 0.32f, 0.72f, 0.85f};
inline constexpr UiColor kTrack{1.f, 1.f, 1.f, 0.18f};

struct Words { const char* ja; const char* en; };
inline const char* say(const Words& words) { return sheetLanguage().empty() ? words.ja : words.en; }


// The backgrounds carry their old title and rows in the photo: each column blends across the hole.
bool uploadBackground(SpriteRenderer& batch, const char* stem, std::initializer_list<UiRect> holes, int& slot, std::string& error);

class PanelScreen : public Screen {
protected:
    static constexpr float kFaceCell = 64.f;
    bool loadFace(SpriteRenderer& batch, std::string& error);
    void label(SpriteRenderer& batch, const char* value, float x, float y, float size, UiColor color = kWhite) const {
        face_.draw(batch, value, x, y, size / kFaceCell, color, 1.2f);
    }
    float widthOf(const char* value, float size) const { return face_.width(value) * size / kFaceCell; }
    void centred(SpriteRenderer& batch, const char* value, float x, float y, float size, UiColor color = kWhite) const {
        label(batch, value, x - widthOf(value, size) / 2.f, y, size, color);
    }
    // One value between arrows, so every row reads the same way.
    void choice(SpriteRenderer& batch, const char* value, float y, bool selected) const {
        constexpr float kCentre = 540.f, kReach = 130.f;
        centred(batch, value, kCentre, y, 20.f, selected ? kWhite : kPale);
        if (selected) {
            label(batch, "<", kCentre - kReach, y, 20.f, kGold);
            label(batch, ">", kCentre + kReach - 8.f, y, 20.f, kGold);
        }
    }
    void frame(SpriteRenderer& batch, const Words& title, float top, float bottom) const {
        batch.pushSolid({100, top, 600, bottom - top}, kPanel);
        centred(batch, say(title), 400, top + 12.f, 34.f, kGold);
        batch.pushSolid({130, top + 58.f, 540, 2}, kGold);
    }
    void help(SpriteRenderer& batch, const char* value) const {
        batch.pushSolid({0, 548, 800, 36}, kPanel);
        centred(batch, value, 400, 555, 16.f, kPale);
    }
    mutable CaptionText face_;
    int background_ = -1;
};

}  // namespace ui
