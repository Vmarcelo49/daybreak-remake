// ui/hud_atlas.cpp — the battle HUD's sheet loader and sprite table.
// Header comment carries the provenance; this file is the transcription.
#include "ui/hud_atlas.h"

#include <cstdio>
#include <vector>

#include "assets/asset_source.h"
#include "assets/cnv.h"

namespace ui {
namespace {

// Sheet spelling: FUN_006560c0 takes the .bmp name the exe asks for and the
// archives ship .cnv, so both are probed, .cnv first (an extracted tree keeps
// .cnv too; a .bmp beside it would be a conversion, which the project does not do).
const char* kSheetNames[(int)HudSheet::Count] = {"P00", "P01", "P02"};

}  // namespace

bool HudAtlas::upload(SpriteRenderer& batch, std::string& error) {
    if (ready()) return true;
    int loaded[(int)HudSheet::Count] = {-1, -1, -1};
    for (int i = 0; i < (int)HudSheet::Count; ++i) {
        const std::string stem = std::string("data/object/") + kSheetNames[i];
        // Bundle-first through assetSource(): read() walks daybreak00..07 in the
        // exe's order and falls back to the filesystem only when no bundle has the
        // entry, so a bundle install and an extracted tree both resolve, and the
        // copy the game itself would read wins. P01 is the case that proves the
        // order matters (see the header).
        std::vector<uint8_t> bytes;
        if (!fnd::assets::assetSource().read(stem + ".cnv", bytes) &&
            !fnd::assets::assetSource().read(stem + ".bmp", bytes)) {
            error = stem + ".cnv is in no open bundle and on no filesystem path";
            return false;
        }
        xm::CnvImage image;
        try {
            image = xm::decodeCnvImage(bytes.data(), bytes.size());
        } catch (const std::exception& e) {
            error = stem + ".cnv: " + e.what();
            return false;
        }
        loaded[i] = batch.addTexture(image.width, image.height, image.rgba.data(), error);
        if (loaded[i] < 0) {
            error = stem + ".cnv upload failed: " + error;
            return false;
        }
    }
    for (int i = 0; i < (int)HudSheet::Count; ++i) sheets_[i] = loaded[i];
    return true;
}

bool HudAtlas::draw(SpriteRenderer& batch, HudIcon icon, float x, float y, UiColor tint) const {
    const HudSprite& s = hudSprite(icon);
    const int tex = sheet(s.sheet);
    if (tex < 0) return false;
    return batch.pushSprite(tex, s.src, s.pivotX, s.pivotY, x, y, tint);
}

bool HudAtlas::fill(SpriteRenderer& batch, HudIcon icon, float frac, float x, float y,
                    FillMode mode, UiColor tint) const {
    const HudSprite& s = hudSprite(icon);
    const int tex = sheet(s.sheet);
    if (tex < 0) return false;
    return batch.pushFill(tex, s.src, s.pivotX, s.pivotY, frac, mode, x, y, tint);
}

bool HudAtlas::number(SpriteRenderer& batch, int value, float x, float y, UiColor tint) const {
    const int tex = sheet(HudSheet::P00);
    if (tex < 0) return false;
    HudDigit digits[10];
    const int n = hudDigitRun(value, x, y, digits);
    bool any = false;
    for (int i = 0; i < n; ++i)
        any |= batch.pushSprite(tex, digits[i].src, 0.f, 0.f, digits[i].x, digits[i].y, tint);
    return any;
}

}  // namespace ui
