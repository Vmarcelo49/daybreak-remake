#pragma once
#include "ui/sprite.h"
#include "ui/text.h"

namespace ui {
inline constexpr const char* kCaptionFontFile = "gyrotrope-black.otf";
inline constexpr const char* kCaptionFallbackFile = "NotoSansCJKjp-Regular.otf";

bool loadCaptionFont(TextLayer& layer, float cellHeight, std::string& error,
                     const char* primary = kCaptionFontFile,
                     const char* fallback = kCaptionFallbackFile);

void drawCaptionLayout(SpriteRenderer& batch, const TextLayer& layer, const TextLayout& layout,
                       int fontAtlas, int& bitmapAtlas, float x, float y, float scale = 1.f,
                       UiColor color = {}, float outline = 0.f);

// Runtime captions share the chosen face; FUN_0065d870's Japanese glyphs use font linking.
class CaptionText {
public:
    bool load(SpriteRenderer& batch, float cellHeight, std::string& error,
              const char* primary = kCaptionFontFile, const char* fallback = kCaptionFallbackFile);
    // Prepare every frame string before drawing if captions may introduce new Unicode glyphs.
    bool prepare(SpriteRenderer& batch, const std::vector<std::string>& lines, std::string& error);
    void draw(SpriteRenderer& batch, const char* text, float x, float y,
              float scale = 1.f, UiColor color = {}, float outline = 0.f);
    float width(const char* text) { return layer_.layout(text).width(1.f); }
    int atlasTexture() const { return atlas_; }
private:
    bool refresh(SpriteRenderer& batch, std::string& error);
    TextLayer layer_;
    int atlas_ = -1, bitmap_ = -1;
    uint64_t revision_ = 0;
};
}
