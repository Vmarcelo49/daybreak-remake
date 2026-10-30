// hud/hud_atlas.cpp — the .cnv sheet loader (shared with the front-end screens) and the
// battle HUD's sprite table. Header comment carries the provenance; this file is the
// transcription.
#include "hud/hud_atlas.h"

#include <cstdio>
#include <vector>

#include "assets/asset_source.h"
#include "assets/cnv.h"

namespace ui {
namespace {

// Sheet spelling: FUN_006560c0 takes the .bmp name the exe asks for and the
// archives ship .cnv, so both are probed, .cnv first (an extracted tree keeps
// .cnv too; a .bmp beside it would be a conversion, which the project does not do).
const char* kSheetNames[(int)HudSheet::Count] = {"P00", "P01", "P02", "P03", "P06", "P09", "P04", "P05", "P08", "P12"};

}  // namespace

bool uploadCnvSheet(SpriteRenderer& batch, const char* stem, int& slot, std::string& error) {
    const std::string base(stem);
    // Bundle-first through assetSource(): read() walks the archives in the exe's
    // registration order and falls back to the filesystem only when no bundle has
    // the entry, so a bundle install and an extracted tree both resolve, and the
    // copy the game itself would read wins. P01 is the case that proves the order
    // matters (see the header).
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(base + ".cnv", bytes) &&
        !fnd::assets::assetSource().read(base + ".bmp", bytes)) {
        error = base + ".cnv is in no open bundle and on no filesystem path";
        return false;
    }
    xm::CnvImage image;
    try {
        image = xm::decodeCnvImage(bytes.data(), bytes.size());
    } catch (const std::exception& e) {
        error = base + ".cnv: " + e.what();
        return false;
    }
    slot = batch.addTexture(image.width, image.height, image.rgba.data(), error);
    if (slot < 0) {
        error = base + ".cnv upload failed: " + error;
        return false;
    }
    return true;
}

bool uploadMultiplyMask(SpriteRenderer& batch, const char* stem, int& slot, std::string& error) {
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(std::string(stem) + ".cnv", bytes)) {
        error = std::string(stem) + ".cnv is in no open bundle and on no filesystem path";
        return false;
    }
    xm::CnvImage image;
    try {
        image = xm::decodeCnvImage(bytes.data(), bytes.size());
    } catch (const std::exception& e) {
        error = std::string(stem) + ".cnv: " + e.what();
        return false;
    }
    for (size_t i = 0; i + 3 < image.rgba.size(); i += 4) {
        const int luminance = (image.rgba[i] + image.rgba[i + 1] + image.rgba[i + 2]) / 3;
        image.rgba[i] = image.rgba[i + 1] = image.rgba[i + 2] = 0;
        image.rgba[i + 3] = static_cast<uint8_t>(255 - luminance);
    }
    slot = batch.addTexture(image.width, image.height, image.rgba.data(), error);
    return slot >= 0;
}

bool HudAtlas::upload(SpriteRenderer& batch, std::string& error) {
    if (ready()) return true;
    int loaded[(int)HudSheet::Count];
    for (int i = 0; i < (int)HudSheet::Count; ++i) {
        if (!uploadCnvSheet(batch, ("data/object/" + std::string(kSheetNames[i])).c_str(),
                            loaded[i], error))
            return false;
    }
    for (int i = 0; i < (int)HudSheet::Count; ++i) sheets_[i] = loaded[i];
    return true;
}

bool HudAtlas::draw(SpriteRenderer& batch, HudIcon icon, float x, float y, float scale,
                    float rotDeg, UiColor tint) const {
    const HudSprite& s = hudSprite(icon);
    const int tex = sheet(s.sheet);
    if (tex < 0) return false;
    return batch.pushSprite(tex, s.src, s.pivotX, s.pivotY, x, y, scale, rotDeg, tint);
}

bool HudAtlas::drawRect(SpriteRenderer& batch, HudSheet which, const UiRect& src, float x, float y) const {
    const int tex = sheet(which);
    return tex >= 0 && batch.pushSprite(tex, src, 0.f, 0.f, x, y);
}

bool HudAtlas::fillRect(SpriteRenderer& batch, HudSheet which, const UiRect& src, float frac, float x, float y) const {
    const int tex = sheet(which);
    return tex >= 0 && batch.pushFill(tex, src, 0.f, 0.f, frac, FillMode::Right, x, y, UiColor{});
}

bool HudAtlas::fill(SpriteRenderer& batch, HudIcon icon, float frac, float x, float y,
                    FillMode mode, UiColor tint) const {
    const HudSprite& s = hudSprite(icon);
    const int tex = sheet(s.sheet);
    if (tex < 0) return false;
    return batch.pushFill(tex, s.src, s.pivotX, s.pivotY, frac, mode, x, y, tint);
}

bool HudAtlas::cell(SpriteRenderer& batch, HudIcon icon, int cellX, int cellY, float x, float y,
                    float scale, float rotDeg, UiColor tint) const {
    const HudSprite& s = hudSprite(icon);
    const int tex = sheet(s.sheet);
    if (tex < 0) return false;
    const UiRect src{s.src.x + (float)cellX * s.src.w, s.src.y + (float)cellY * s.src.h, s.src.w,
                     s.src.h};
    return batch.pushSprite(tex, src, s.pivotX, s.pivotY, x, y, scale, rotDeg, tint);
}

bool HudAtlas::number(SpriteRenderer& batch, HudFont font, int value, float x, float y,
                      float scale, UiColor tint) const {
    const int tex = sheet(hudFont(font).sheet);
    if (tex < 0) return false;
    HudDigit digits[10];
    const int n = hudDigitRun(font, value, x, y, scale, digits);
    bool any = false;
    for (int i = 0; i < n; ++i)
        any |= batch.pushSprite(tex, digits[i].src, 0.f, 0.f, digits[i].x, digits[i].y,
                                digits[i].scale, 0.f, tint);
    return any;
}

bool HudAtlas::glyph(SpriteRenderer& batch, HudFont font, int cellX, int cellY, float x, float y,
                     float scale, UiColor tint) const {
    const HudFontSpec& f = hudFont(font);
    const int tex = sheet(f.sheet);
    if (tex < 0) return false;
    const UiRect src{f.base.x + (float)cellX * f.base.w, f.base.y + (float)cellY * f.base.h,
                     f.base.w, f.base.h};
    return batch.pushSprite(tex, src, 0.f, 0.f, x + scale * f.leading, y, scale, 0.f, tint);
}

}  // namespace ui
