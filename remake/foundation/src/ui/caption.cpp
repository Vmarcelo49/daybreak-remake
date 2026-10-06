#include "ui/caption.h"
#include <fstream>
#include <iterator>
#include <SDL3/SDL.h>

namespace ui {
namespace {
std::vector<uint8_t> fontBytes(const char* file) {
    if (!file || !*file) return {};
    for (auto roots = fontSearchRoots(); *roots; ++roots) {
        std::ifstream stream(std::string(*roots) + file, std::ios::binary);
        if (stream) return {std::istreambuf_iterator<char>(stream), {}};
    }
    if (const char* base = SDL_GetBasePath()) {
        std::ifstream stream(std::string(base)+"assets/fonts/"+file,std::ios::binary);
        if (stream) return {std::istreambuf_iterator<char>(stream), {}};
    }
    return {};
}
}
bool loadCaptionFont(TextLayer& layer, float cellHeight, std::string& error,
                     const char* primary, const char* fallback) {
    auto bytes = fontBytes(primary);
    if (bytes.empty()) {
        // User-facing: the packaged release ships this face in assets/fonts beside the
        // executable (D7), so the fix is to restore the package, not to debug a loader.
        error = std::string("caption font missing: ") + (primary ? primary : "(unset)") +
                " was not found in assets/fonts next to the executable. The package looks "
                "incomplete — unpack the release archive again";
        return false;
    }
    FontChain chain;
    chain.push_back({std::move(bytes), cellHeight});
    bytes = fontBytes(fallback);
    if (!bytes.empty()) chain.push_back({std::move(bytes), cellHeight});
    return layer.loadFontChain(chain, error);
}
bool CaptionText::load(SpriteRenderer& batch, float cellHeight, std::string& error) {
    if (atlas_ >= 0) return true;
    if (!loadCaptionFont(layer_, cellHeight, error)) return false;
    // ASCII captions cannot change atlas dimensions after their first quad is queued.
    for (int cp = 32; cp < 127; ++cp) {
        const char one[] = {static_cast<char>(cp), '\0'};
        layer_.layout(one);
    }
    return refresh(batch, error);
}
bool CaptionText::refresh(SpriteRenderer& batch, std::string& error) {
    if (atlas_ >= 0 && revision_ == layer_.atlasRevision()) return true;
    if (atlas_ < 0)
        atlas_ = batch.addTexture(layer_.atlasWidth(), layer_.atlasHeight(), layer_.atlasRGBA().data(), error);
    else if (!batch.updateTexture(atlas_, layer_.atlasWidth(), layer_.atlasHeight(), layer_.atlasRGBA().data(), error))
        return false;
    if (atlas_ < 0) return false;
    revision_ = layer_.atlasRevision();
    return true;
}
bool CaptionText::prepare(SpriteRenderer& batch, const std::vector<std::string>& lines, std::string& error) {
    for (const auto& line : lines) layer_.layout(line.c_str());
    return refresh(batch, error);
}
void CaptionText::draw(SpriteRenderer& batch, const char* text, float x, float y,
                       float scale, UiColor color, float outline) {
    if (atlas_ < 0 || !text || !*text) return;
    const auto layout = layer_.layout(text);
    std::string error;
    if (!refresh(batch, error)) return;
    drawCaptionLayout(batch,layer_,layout,atlas_,bitmap_,x,y,scale,color,outline);
}
void drawCaptionLayout(SpriteRenderer& batch, const TextLayer& layer, const TextLayout& layout,
                       int fontAtlas, int& bitmapAtlas, float x, float y, float scale,
                       UiColor color, float outline) {
    std::string error;
    std::vector<GlyphQuad> glyphs;
    layer.buildQuads(layout, x, y, scale, glyphs);
    for (const auto& glyph : glyphs) {
        int texture = fontAtlas;
        if (glyph.source == GlyphSource::Bitmap) {
            if (bitmapAtlas < 0) {
                std::vector<uint8_t> pixels; uint32_t w = 0, h = 0;
                buildAtlasRGBA(pixels,w,h);
                bitmapAtlas = batch.addTexture(w,h,pixels.data(),error);
            }
            if (bitmapAtlas < 0) continue;
            texture = bitmapAtlas;
        }
        const UiColor tint{color.r*glyph.color.r/255.f,color.g*glyph.color.g/255.f,
                           color.b*glyph.color.b/255.f,color.a*glyph.color.a/255.f};
        const UiRect bounds{glyph.x, glyph.y, glyph.w, glyph.h};
        const UiRect uv{glyph.u0, glyph.v0, glyph.u1-glyph.u0, glyph.v1-glyph.v0};
        if (outline > 0)
            for (const auto& offset : {UiRect{-outline,0,0,0}, UiRect{outline,0,0,0},
                                       UiRect{0,-outline,0,0}, UiRect{0,outline,0,0}})
                batch.pushTextured(texture, {bounds.x+offset.x,bounds.y+offset.y,bounds.w,bounds.h}, uv, {0,0,0,tint.a});
        batch.pushTextured(texture, bounds, uv, tint);
    }
}
}
