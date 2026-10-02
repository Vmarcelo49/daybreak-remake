#include "ui/text.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <new>

// stb_truetype: public domain, single header, vendored at third_party/stb
// (same class of dependency as stb_vorbis.c). Exactly one TU in the program defines
// the implementation, and this is it. STBTT_STATIC keeps the vendor symbols out of
// the link namespace, so a caller that includes the header for something else cannot
// collide with this TU; the pragma keeps its unused public entry points from tripping
// -Wall -Wextra.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-function"
#define STBTT_STATIC
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#pragma GCC diagnostic pop

namespace ui {
namespace {

using FontInfo = stbtt_fontinfo;

// Same 16 x 6 grid of 8x8 cells as ui/font.cpp's file-local cellOrigin, over the
// constants font.h exports — kept in step by construction.
void bitmapCell(uint32_t cp, float& cx, float& cy) {
    const uint32_t idx = cp - 32;
    cx = (float)((idx % kAtlasCols) * kAtlasCell);
    cy = (float)((idx / kAtlasCols) * kAtlasCell);
}

// The FUN_0065dad0 walker. One step is either a rendered code point (with the colour in
// effect) or a line break; escapes and control bytes are consumed inside next(), so
// callers never see them. Shared by layout() and parseColorRuns() on purpose: the
// string model exists once.
class Walker {
public:
    struct Step {
        uint32_t  cp = 0;
        size_t    offset = 0;   // first byte of this step in the source
        size_t    bytes = 0;    // bytes this step consumed
        TextColor color{};
        bool      newline = false;
    };

    Walker(const char* text, size_t len, TextColor defaultColor)
        : text_(text), len_(len), default_(defaultColor), color_(defaultColor) {}

    bool next(Step& s) {
        for (;;) {
            if (i_ >= len_) return false;
            const uint8_t b = (uint8_t)text_[i_];
            if (b == '\n') {
                s = Step{};
                s.cp = '\n';
                s.offset = i_;
                s.bytes = 1;
                s.color = color_;
                s.newline = true;
                ++i_;
                return true;
            }
            if (b == '\\') {
                const size_t j = i_ + 1;
                // A trailing backslash: the original reads the NUL as the "next
                // character", draws nothing and the loop ends.
                if (j >= len_) {
                    i_ = len_;
                    return false;
                }
                const uint8_t c = (uint8_t)text_[j];
                // FUN_0065e3a0 returns the byte length of the next character and only
                // the single-byte branch (bVar1 < 2) can match a command.
                if (c < 0x80) {
                    if (c == 'c') {
                        color_ = hexColor(j + 1);
                        i_ = std::min(len_, j + 7);
                        continue;
                    }
                    if (c == 'e') {
                        color_ = default_;
                        i_ = j + 1;
                        continue;
                    }
                    if (c == 'n') {
                        s = Step{};
                        s.cp = '\n';
                        s.offset = i_;
                        s.bytes = 2;
                        s.color = color_;
                        s.newline = true;
                        i_ = j + 1;
                        return true;
                    }
                }
                // Unknown escape (or a multi-byte code after the backslash): only the
                // backslash is consumed, so the next character renders normally.
                i_ = j;
                continue;
            }
            const size_t start = i_;
            const char* p = text_ + i_;
            const uint32_t cp = utf8Next(p);
            i_ = (size_t)(p - text_);
            if (cp < 0x20) continue;   // other controls vanish without advancing (font.h)
            s = Step{};
            s.cp = cp;
            s.offset = start;
            s.bytes = i_ - start;
            s.color = color_;
            return true;
        }
    }

    size_t    pos() const { return i_; }
    TextColor color() const { return color_; }

private:
    // FUN_0065dad0 reads six raw bytes after `\c` and feeds each to FUN_0065e450. Bytes
    // past the terminator (which the original would read out of bounds) count as 0.
    TextColor hexColor(size_t k) const {
        TextColor c;
        c.r = (uint8_t)((hexDigit(byteAt(k)) << 4) | hexDigit(byteAt(k + 1)));
        c.g = (uint8_t)((hexDigit(byteAt(k + 2)) << 4) | hexDigit(byteAt(k + 3)));
        c.b = (uint8_t)((hexDigit(byteAt(k + 4)) << 4) | hexDigit(byteAt(k + 5)));
        c.a = 255;
        return c;
    }
    uint8_t byteAt(size_t k) const { return k < len_ ? (uint8_t)text_[k] : 0; }

    const char* text_;
    size_t      len_;
    TextColor   default_;
    TextColor   color_;
    size_t      i_ = 0;
};

}  // namespace

int hexDigit(uint8_t c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    return 0;
}

ColorRuns parseColorRuns(const char* text, TextColor defaultColor) {
    ColorRuns out;
    out.finalColor = defaultColor;
    if (!text) return out;

    const size_t len = std::strlen(text);
    Walker w(text, len, defaultColor);
    size_t current = (size_t)-1;
    Walker::Step s;
    while (w.next(s)) {
        if (s.newline) {
            ++out.newlines;
            continue;
        }
        const size_t end = s.offset + s.bytes;
        if (current != (size_t)-1 && out.runs[current].color == s.color) {
            out.runs[current].byteLength = end - out.runs[current].byteOffset;
            ++out.runs[current].glyphs;
            continue;
        }
        ColorRun run;
        run.byteOffset = s.offset;
        run.byteLength = s.bytes;
        run.color = s.color;
        run.glyphs = 1;
        out.runs.push_back(run);
        current = out.runs.size() - 1;
    }
    out.finalColor = w.color();
    out.consumed = std::min(len, w.pos());
    return out;
}

TextLayer::~TextLayer() { unloadFont(); }

bool TextLayer::loadFont(std::vector<uint8_t> fontData, float pixelHeight, std::string& error) {
    unloadFont();
    if (fontData.empty()) {
        error = "text: font data is empty";
        return false;
    }
    const int px = (int)std::lround(pixelHeight);
    if (px < 4 || px > 128) {
        error = "text: design pixel height " + std::to_string(px) + " is outside 4..128";
        return false;
    }
    const int offset = stbtt_GetFontOffsetForIndex(fontData.data(), 0);
    auto* fi = new (std::nothrow) FontInfo();
    if (!fi) {
        error = "text: out of memory allocating the font info";
        return false;
    }
    std::memset(fi, 0, sizeof *fi);
    if (offset < 0 || !stbtt_InitFont(fi, fontData.data(), offset)) {
        delete fi;
        error = "text: stb_truetype cannot parse this font (truncated file, or a TTF/OTF/"
                "CFF variant it does not support)";
        return false;
    }
    int ascent = 0, descent = 0, lineGap = 0;
    stbtt_GetFontVMetrics(fi, &ascent, &descent, &lineGap);
    if (ascent - descent <= 0) {
        delete fi;
        error = "text: font reports no usable vertical metrics (ascent " +
                std::to_string(ascent) + ", descent " + std::to_string(descent) + ")";
        return false;
    }

    fontData_ = std::move(fontData);
    font_ = fi;
    fontLoaded_ = true;
    designPx_ = px;
    ascent_ = ascent;
    descent_ = descent;
    lineGap_ = lineGap > 0 ? lineGap : 0;
    em_ = ascent - descent;
    ascent64_ = unitsToFixed64(ascent_);
    lineHeight64_ = unitsToFixed64(em_ + lineGap_);
    resetAtlas();
    return true;
}

void TextLayer::unloadFont() {
    delete static_cast<FontInfo*>(font_);
    font_ = nullptr;
    fontData_.clear();
    fontData_.shrink_to_fit();
    fontLoaded_ = false;
    designPx_ = 0;
    ascent_ = descent_ = lineGap_ = em_ = 0;
    // With no font the bitmap font is the whole line box: 8 texels of line, no ascent.
    ascent64_ = 0;
    lineHeight64_ = kLineHeight * kFixedOne;
    cache_.clear();
    resetAtlas();
}

void TextLayer::resetAtlas() {
    atlasW_ = kLayerAtlasW;
    atlasH_ = kLayerAtlasH0;
    atlas_.assign((size_t)atlasW_ * atlasH_ * 4, 0);
    packX_ = packY_ = packShelfH_ = 0;
    atlasFullDrops_ = 0;
    ++revision_;
}

void TextLayer::growAtlas() {
    const uint32_t newH = std::min(atlasH_ * 2, kLayerAtlasMaxH);
    if (newH <= atlasH_) return;
    // The stride is unchanged, so every placed tile keeps its coordinates and bytes —
    // only the UV denominator moves, which is why the revision bumps.
    atlas_.resize((size_t)atlasW_ * newH * 4, 0);
    atlasH_ = newH;
    ++revision_;
}

bool TextLayer::placeTile(int w, int h, int& tileX, int& tileY) {
    if (w <= 0 || h <= 0) return false;
    if ((uint32_t)w > atlasW_ || (uint32_t)h > kLayerAtlasMaxH) return false;
    if (packX_ + (uint32_t)w > atlasW_) {
        packX_ = 0;
        packY_ += packShelfH_ + 1;
        packShelfH_ = 0;
    }
    while (packY_ + (uint32_t)h > atlasH_ && atlasH_ < kLayerAtlasMaxH) growAtlas();
    if (packY_ + (uint32_t)h > atlasH_) return false;
    tileX = (int)packX_;
    tileY = (int)packY_;
    packX_ += (uint32_t)w + 1;   // 1 px gutter: no bleed under linear sampling
    if ((uint32_t)h > packShelfH_) packShelfH_ = (uint32_t)h;
    return true;
}

int32_t TextLayer::unitsToFixed64(int v) const {
    if (em_ <= 0) return 0;
    // Integer round-half-away-from-zero: the same result on every target, no FP.
    const int64_t num = (int64_t)v * (int64_t)designPx_ * (int64_t)kFixedOne;
    const int64_t den = (int64_t)em_;
    const int64_t q = num >= 0 ? (num + den / 2) / den : -((-num + den / 2) / den);
    return (int32_t)q;
}

const GlyphInfo* TextLayer::rasterizeFontGlyph(uint32_t cp) {
    auto* fi = static_cast<FontInfo*>(font_);
    GlyphInfo info;
    const int gi = fontLoaded_ ? stbtt_FindGlyphIndex(fi, (int)cp) : 0;
    if (gi == 0) {
        // Unmapped: memoize "absent" so a repeated code point costs one lookup, and let
        // resolve() fall back to the bitmap '?' cell.
        return &cache_.emplace(cp, info).first->second;
    }
    int advanceWidth = 0, lsb = 0;
    stbtt_GetGlyphHMetrics(fi, gi, &advanceWidth, &lsb);
    info.present = true;
    info.advance64 = unitsToFixed64(advanceWidth);
    // Zero subpixel offsets: the tile is a pure function of (font, designPx, glyph), and
    // (x0, y0) is the placement relative to the pen and the baseline — the pair
    // FUN_0065d9a0 stores at +0x28 / +0x2c.
    const float scale = stbtt_ScaleForPixelHeight(fi, (float)designPx_);
    int x0 = 0, y0 = 0, x1 = 0, y1 = 0;
    stbtt_GetGlyphBitmapBox(fi, gi, scale, scale, &x0, &y0, &x1, &y1);
    info.x0 = x0;
    info.y0 = y0;
    info.x1 = x1;
    info.y1 = y1;
    const int w = x1 - x0, h = y1 - y0;
    if (w > 0 && h > 0) {
        int tileX = 0, tileY = 0;
        if (placeTile(w, h, tileX, tileY)) {
            info.tileX = tileX;
            info.tileY = tileY;
            info.hasBitmap = true;
            // stb_truetype writes one coverage byte per pixel and leaves uncovered
            // pixels alone, so the scratch tile is zeroed first. The atlas is RGBA8
            // with straight alpha: white RGB, coverage in alpha (buildAtlasRGBA's
            // convention, so one texture serves every tint). The original's GGO_GRAY4
            // coverage (0..16) went through the same idea at a lower bit depth
            // (FUN_0065dad0: coverage * 14 + 3 into the alpha byte).
            std::vector<uint8_t> cov((size_t)w * h, 0);
            stbtt_MakeGlyphBitmap(fi, cov.data(), w, h, w, scale, scale, gi);
            for (int row = 0; row < h; ++row) {
                uint8_t* dst = atlas_.data() + (((size_t)(tileY + row) * atlasW_) + tileX) * 4;
                const uint8_t* src = cov.data() + (size_t)row * w;
                for (int col = 0; col < w; ++col) {
                    dst[col * 4 + 0] = 0xFF;
                    dst[col * 4 + 1] = 0xFF;
                    dst[col * 4 + 2] = 0xFF;
                    dst[col * 4 + 3] = src[col];
                }
            }
            ++revision_;
        } else {
            ++atlasFullDrops_;   // advance is kept, ink is dropped: never a shifted line
        }
    }
    return &cache_.emplace(cp, info).first->second;
}

const GlyphInfo* TextLayer::glyphInfo(uint32_t cp) const {
    const auto it = cache_.find(cp);
    return it == cache_.end() ? nullptr : &it->second;
}

bool TextLayer::hasGlyph(uint32_t cp) const {
    if (!fontLoaded_) return false;
    return stbtt_FindGlyphIndex(static_cast<const FontInfo*>(font_), (int)cp) != 0;
}

std::vector<uint8_t> TextLayer::glyphCoverage(uint32_t cp) const {
    const GlyphInfo* g = glyphInfo(cp);
    if (!g || !g->hasBitmap) return {};
    const int w = g->x1 - g->x0, h = g->y1 - g->y0;
    std::vector<uint8_t> out((size_t)w * h, 0);
    for (int row = 0; row < h; ++row) {
        const uint8_t* src = atlas_.data() + (((size_t)(g->tileY + row) * atlasW_) + g->tileX) * 4;
        for (int col = 0; col < w; ++col) out[(size_t)row * w + col] = src[col * 4 + 3];
    }
    return out;
}

TextLayer::Resolved TextLayer::resolve(uint32_t cp) {
    Resolved r;
    // A loaded font owns every non-ASCII code point (that is the point of the layer) and
    // owns ASCII too unless the caller asked to keep the bitmap's Latin.
    if (fontLoaded_ && (fontAscii_ || cp >= 0x80)) {
        const GlyphInfo* g = glyphInfo(cp);
        if (!g) g = rasterizeFontGlyph(cp);
        if (g->present) {
            r.advance64 = g->advance64;
            r.x0 = g->x0;
            r.y0 = g->y0;
            r.w = g->x1 - g->x0;
            r.h = g->y1 - g->y0;
            r.tileX = g->tileX;
            r.tileY = g->tileY;
            r.source = GlyphSource::Font;
            return r;
        }
    }
    // Bitmap fallback: the code point's own cell, or '?' for anything unsupported —
    // font.h's rule, one 6 texel cell of advance either way.
    r.source = GlyphSource::Bitmap;
    r.advance64 = kGlyphAdvance * kFixedOne;
    r.substituted = !glyphSupported(cp);
    r.w = kGlyphW;
    r.h = kGlyphH;
    return r;
}

TextLayout TextLayer::layout(const char* text, TextColor color) {
    TextLayout l;
    l.lineHeight64 = lineHeight64_;
    l.ascent64 = ascent64_;
    if (!text || !*text) return l;

    Walker w(text, std::strlen(text), color);
    int32_t pen = 0, lineTop = 0;
    l.lines = 1;
    Walker::Step s;
    while (w.next(s)) {
        if (s.newline) {
            if (pen > l.width64) l.width64 = pen;
            pen = 0;
            lineTop += lineHeight64_;
            ++l.lines;
            continue;
        }
        const Resolved r = resolve(s.cp);
        TextLayout::Item it;
        it.cp = s.cp;
        it.advance64 = r.advance64;
        it.x64 = pen + r.x0 * kFixedOne;
        // Font glyphs hang off the baseline (ascent + the box's y0, i.e. the original's
        // `ascent - gmptGlyphOrigin.y`). Bitmap cells on the same baseline have to sit
        // their 7 texel box on it; with no font loaded they ARE the line box, so they
        // stay at the line top and this layer reduces to ui::layoutText exactly.
        it.y64 = r.source == GlyphSource::Font
                     ? lineTop + ascent64_ + r.y0 * kFixedOne
                     : (fontLoaded_ ? lineTop + ascent64_ - kGlyphH * kFixedOne : lineTop);
        it.color = s.color;
        it.source = r.source;
        it.substituted = r.substituted;
        l.items.push_back(it);
        if (r.substituted) ++l.substituted;
        pen += r.advance64;
    }
    if (pen > l.width64) l.width64 = pen;
    l.lastLine64 = pen;
    return l;
}

void TextLayer::buildQuads(const TextLayout& l, float originX, float originY, float scale,
                           std::vector<GlyphQuad>& out) const {
    for (const TextLayout::Item& it : l.items) {
        int w = 0, h = 0;
        float u0 = 0.f, v0 = 0.f, u1 = 0.f, v1 = 0.f;
        if (it.source == GlyphSource::Font) {
            const GlyphInfo* g = glyphInfo(it.cp);
            if (!g || !g->hasBitmap) continue;   // space, or ink dropped by a full atlas
            w = g->x1 - g->x0;
            h = g->y1 - g->y0;
            u0 = (float)g->tileX / (float)atlasW_;
            v0 = (float)g->tileY / (float)atlasH_;
            u1 = (float)(g->tileX + w) / (float)atlasW_;
            v1 = (float)(g->tileY + h) / (float)atlasH_;
        } else {
            // Bitmap atlas (ui::kAtlasW x ui::kAtlasH), not this layer's: the names are
            // qualified because TextLayer has atlas constants of its own.
            float cx = 0.f, cy = 0.f;
            bitmapCell(it.substituted ? (uint32_t)'?' : it.cp, cx, cy);
            w = kGlyphW;
            h = kGlyphH;
            u0 = cx / (float)ui::kAtlasW;
            v0 = cy / (float)ui::kAtlasH;
            u1 = (cx + (float)kGlyphW) / (float)ui::kAtlasW;
            v1 = (cy + (float)kGlyphH) / (float)ui::kAtlasH;
        }
        GlyphQuad q;
        q.x = originX + pixels(it.x64, scale);
        q.y = originY + pixels(it.y64, scale);
        q.w = (float)w * scale;
        q.h = (float)h * scale;
        q.u0 = u0;
        q.v0 = v0;
        q.u1 = u1;
        q.v1 = v1;
        q.color = it.color;
        q.source = it.source;
        out.push_back(q);
    }
}

}  // namespace ui
