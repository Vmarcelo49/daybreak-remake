#pragma once
// Portable bitmap font: the replacement for the DX9 D3DX font path.
//
// Why a bitmap: D3DXCreateFont("Arial") needs a Windows font stack — Wine
// often lacks CJK fonts and the DX9 remake itself is ASCII-only for now (its
// KO sting prints "KO!" until JP text lands). An embedded monospace 5x7 atlas
// renders every HUD string the reference uses on Linux, Windows and the web
// with no OS dependency, and text measurement becomes exact arithmetic instead
// of a font-metric query.
//
// Coverage: printable ASCII 32..126 (digits, uppercase mode names like
// FRIENDSHIP/OYASHIRO/KAKERA, labels like MAIN/CHARGE/HP/STAMINA/LIMIT,
// "KO!", "%", "READY (S)"). Anything else — including Shift-JIS-derived names
// that did not resolve to ASCII — advances as '?' so layout never shifts under
// an unknown codepoint. CJK text is explicitly out of scope (see UI-DESIGN).
//
// This header is GPU-free on purpose: measurement, UTF-8 decoding and atlas
// generation are deterministic host-side code, unit-tested without a device.
// Upload is one SpriteRenderer::addTexture of buildAtlasRGBA output.
#include <cstdint>
#include <string>
#include <vector>

namespace ui {

// Cell geometry in texels at scale 1. Advance 6 keeps 1 px side bearings so
// adjacent glyphs never touch; line height 8 keeps 1 px between rows.
inline constexpr int kGlyphW = 5;
inline constexpr int kGlyphH = 7;
inline constexpr int kGlyphAdvance = 6;
inline constexpr int kLineHeight = 8;

// Atlas: 16 columns x 6 rows of 8x8 cells holding codepoints 32..127.
inline constexpr int kAtlasCols = 16;
inline constexpr int kAtlasCell = 8;
inline constexpr uint32_t kAtlasW = 128;
inline constexpr uint32_t kAtlasH = 48;

// True for codepoints with a real cell in the atlas.
inline bool glyphSupported(uint32_t cp) { return cp >= 32 && cp < 127; }

// Top-left of a supported codepoint's cell in the atlas, in pixels — the atlas geometry above
// applied once, so the bitmap layout and the text layer cannot place a glyph differently.
inline void atlasCellOrigin(uint32_t cp, float& x, float& y) {
    const uint32_t idx = cp - 32;
    x = (float)((idx % kAtlasCols) * kAtlasCell);
    y = (float)((idx / kAtlasCols) * kAtlasCell);
}

// Decodes one UTF-8 codepoint, advancing `p`. Malformed bytes yield U+FFFD
// (unsupported, so drawn as '?') rather than stopping the line.
uint32_t utf8Next(const char*& p);

struct TextExtent {
    float width = 0.f;    // widest line, pixels at the requested scale
    float height = 0.f;   // lines * kLineHeight * scale
    int   lines = 0;
};

// Pixel extent of `text` at `scale` (scale 3 ~= the DX9 22 px font: 7*3 = 21).
// '\n' starts a new line; NUL or nullptr ends the string. Deterministic:
// unsupported codepoints advance exactly one cell, like '?'.
TextExtent measureText(const char* text, float scale);

// One glyph quad in atlas UV space (0..1 over the 128x48 atlas).
struct TextQuad {
    float x, y, w, h;          // destination pixels
    float u0, v0, u1, v1;      // atlas UVs
};

// Lays `text` out at (x, y) top-left, appending one quad per glyph. Control
// characters other than '\n' are skipped without advancing.
void layoutText(const char* text, float x, float y, float scale,
                std::vector<TextQuad>& out);
// Centered variant: the whole block is centred on `centerX`.
void layoutTextCentered(const char* text, float centerX, float y, float scale,
                        std::vector<TextQuad>& out);

// Builds the uploadable atlas: white RGB, glyph coverage in alpha, top-down,
// stride = width * 4 — the layout SpriteRenderer::addTexture expects.
void buildAtlasRGBA(std::vector<uint8_t>& rgba, uint32_t& w, uint32_t& h);

// Raw 5-bit rows, top row first, bit 4 = leftmost pixel. 95 entries for
// codepoints 32..126 in order.
extern const uint8_t kFontGlyphs[95][7];

}  // namespace ui
