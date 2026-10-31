#include "frontend/menu_panel.h"

#include <algorithm>
#include <cmath>
#include <vector>

#include "assets/asset_source.h"
#include "assets/cnv.h"

namespace ui {

bool uploadBackground(SpriteRenderer& batch, const char* stem, std::initializer_list<UiRect> holes, int& slot, std::string& error) {
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(std::string(stem) + ".cnv", bytes)) {
        error = std::string(stem) + ".cnv is in no open bundle and on no filesystem path";
        return false;
    }
    xm::CnvImage image = xm::decodeCnvImage(bytes.data(), bytes.size());
    const int w = (int)image.width, h = (int)image.height;
    for (const UiRect& hole : holes) {
        const int x0 = std::max(0, (int)hole.x), x1 = std::min(w, (int)(hole.x + hole.w));
        const int y0 = std::max(1, (int)hole.y), y1 = std::min(h - 1, (int)(hole.y + hole.h));
        for (int x = x0; x < x1; ++x) {
            const uint8_t* above = image.rgba.data() + ((size_t)(y0 - 1) * w + x) * 4;
            const uint8_t* below = image.rgba.data() + ((size_t)y1 * w + x) * 4;
            for (int y = y0; y < y1; ++y) {
                const float t = (y - y0 + 1.f) / (y1 - y0 + 1.f);
                uint8_t* p = image.rgba.data() + ((size_t)y * w + x) * 4;
                for (int c = 0; c < 4; ++c) p[c] = (uint8_t)std::lround(above[c] * (1.f - t) + below[c] * t);
            }
        }
    }
    slot = batch.addTexture(image.width, image.height, image.rgba.data(), error);
    return slot >= 0;
}

bool PanelScreen::loadFace(SpriteRenderer& batch, std::string& error) {
    return face_.load(batch, kFaceCell, error, "Goldman-Bold.ttf", kCaptionFallbackFile);
}

}  // namespace ui
