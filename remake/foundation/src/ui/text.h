#pragma once
// CJK-capable text layer: in-process TrueType rasterization, one fetched font.
//
// Why this exists: the 5x7 atlas in ui/font.h cannot draw Japanese, and the banked
// reference frames need it — the in-battle HUD carries the label `適当`
// (battle-hud.webp, battle-stamina.webp, ko-moment.webp) and the title menu is six
// Japanese items (`ストーリー`, `対戦`, `通信対戦`, `環境設定`, `操作設定`, `終了`).
// Option B of docs/CJK-TEXT.md (decided 2026-10-02): rasterize one OFL Japanese font
// in-process with stb_truetype so Linux, Windows/Wine and the browser share ONE
// rasterizer — the byte-identical capture discipline every phase's evidence rests on.
// The bitmap atlas stays, unchanged, as the no-font fallback.
//
// What the original game does, and what this layer ports (docs/CJK-TEXT.md §1):
//   FUN_0065d870 (0x0065d870) CreateFontA(height, ..., FW_BOLD, ..., SHIFTJIS_CHARSET,
//     OUT_TT_PRECIS, ..., PROOF_QUALITY, VARIABLE_PITCH|FF_SWISS, facename) then
//     GetTextMetricsA for tmAscent (object +0x24). The face is configuration, and the
//     OS owns rasterization — exactly what cannot be reproduced identically across
//     targets, hence a fetched font here instead of a system one.
//   FUN_0065d9a0 (0x0065d9a0) GetGlyphOutlineA(hdc, glyph, 5 /*GGO_GRAY4_BITMAP*/,
//     &metrics, size, buffer, &matrix) into the game's OWN glyph bitmap: gmBlackBoxX/Y
//     give the tile size, the returned stride is `size / gmBlackBoxY & ~3`, and
//     gmptGlyphOrigin.x / (ascent - gmptGlyphOrigin.y) give the placement relative to
//     the pen and the line's ascent. This port takes the same four numbers from
//     stbtt_GetGlyphHMetrics + stbtt_GetGlyphBitmapBox.
//   FUN_0065dad0 (0x0065dad0) the string walker: Shift-JIS in, glyphs out into a
//     zero-filled bitmap, with inline control codes. This port reproduces that walker
//     over UTF-8 (the port's string encoding everywhere else) — see parseColorRuns()
//     and layout() for the exact semantics, including what `\e` does.
//
// Layout arithmetic is INTEGER on purpose (kFixedOne = 1/64 texel). Positions, advances
// and widths accumulate as integers and convert to pixels with one correctly rounded
// multiply per coordinate, so no floating-point accumulation can make two targets
// disagree. loadFont() documents the rest of the determinism contract.
//
// Two metric modes, because the reference frames were rendered by GDI and GDI's
// arithmetic is not stb_truetype's:
//   loadFont()      — size the face by stb's "pixel height" (ascent..descent). Generic
//                     TrueType metrics; advances stay fractional.
//   loadFontChain() — size every face by the LOGFONT cell height the reference passes
//                     to CreateFontIndirect, and reproduce what GDI then reports:
//                     advances rounded to whole pixels (GetCharWidth32A) and the first
//                     baseline at tmAscent - tmExternalLeading below the origin (where
//                     D3DXFont's DrawText puts it). Measured against the banked DX9
//                     frames in tests/hud_text_test.cpp.
//
// This header is GPU-free like ui/font.h: measurement, rasterization and atlas
// generation are host-side code, unit-tested without a device. Uploading the atlas is
// one SpriteRenderer::addTexture of atlasRGBA() (RGBA8, top-down, straight alpha,
// white RGB + coverage in alpha — the same conventions as ui::buildAtlasRGBA).
#include <cstdint>
#include <map>
#include <string>
#include <vector>

#include "ui/font.h"   // bitmap fallback: glyph geometry, atlas layout, utf8Next

namespace ui {

// Straight-alpha colour. FUN_0065dad0 keeps the text colour in three bytes (object
// +0x20/+0x21/+0x22) and composes D3DCOLOR_ARGB(0x03, r, g, b) per pixel; alpha here is
// the caller's tint alpha, since the atlas carries coverage, not colour.
struct TextColor {
    uint8_t r = 255, g = 255, b = 255, a = 255;
};

inline bool operator==(TextColor a, TextColor b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}
inline bool operator!=(TextColor a, TextColor b) { return !(a == b); }

// FUN_0065e450 (0x0065e450): one hex digit, and 0 for everything else — including the
// terminator. That "0" is why a truncated `\c` yields a defined (if surprising) colour
// instead of an error.
int hexDigit(uint8_t c);

// Layout fixed point: 1 design texel = 64 units. Integer arithmetic everywhere.
inline constexpr int32_t kFixedOne = 64;

// Design units -> pixels. One correctly rounded multiply: `scale / 64` is exact
// (division by a power of two) and the integer->float conversion is exact for any
// plausible coordinate (< 2^24). No accumulation, so no target-dependent drift.
inline float pixels(int32_t v64, float scale) { return (float)v64 * (scale / 64.f); }

// ---------------------------------------------------------------------------
// String model (FUN_0065dad0)
// ---------------------------------------------------------------------------

// One maximal run of *rendered* code points sharing one colour. `byteOffset` is the
// run's first glyph byte and `byteLength` reaches the end of its last glyph, so a run
// can contain control bytes (a newline does not break a run — the original's `\n` resets
// the pen, not the colour); control bytes between two differently coloured runs belong
// to no run: for `a\cFF0000b` run 0 is byte 0 and run 1 is byte 9.
struct ColorRun {
    size_t    byteOffset = 0;
    size_t    byteLength = 0;
    TextColor color{};
    int       glyphs = 0;
};

struct ColorRuns {
    std::vector<ColorRun> runs;
    TextColor             finalColor{};   // colour in effect when the walk ended
    size_t                consumed = 0;   // bytes walked, clamped to strlen
    int                   newlines = 0;
};

// Walks `text` exactly as FUN_0065dad0 does and reports its colour runs:
//   `\c` + six hex digits -> RRGGBB for the following run (FUN_0065e450 per digit;
//       the escape always consumes `c` + 6 bytes, so a short tail swallows the rest);
//   `\e` -> back to `defaultColor` (the original reloads the object's +0x20/+0x21/
//       +0x22 bytes, i.e. the colour the string started with — not "no colour");
//   `\n` -> line break (the walker resets local_10 to 1 and adds the line height; the
//       original also decrements a line budget at +0x144 and truncates the string when
//       it runs out — the port has no line budget, like the bitmap layer);
//   any other `\X`, and any `\` followed by a multi-byte character, consumes only the
//       backslash (FUN_0065e3a0 returns bVar1 >= 2 for a two-byte code, so no command
//       matches) and re-reads the character, which then renders normally;
//   a trailing `\` consumes the backslash and ends the walk (the original reads the
//       NUL after it and stops).
// Bytes at or past the terminator count as hex 0: the original reads past the NUL
// there, this port does not, so a malformed `\c` is defined here instead of depending
// on adjacent memory. The byte count consumed and the stop position still match.
ColorRuns parseColorRuns(const char* text, TextColor defaultColor = {});

// ---------------------------------------------------------------------------
// Layout
// ---------------------------------------------------------------------------

// Which atlas a quad's UVs index. The caller owns two uploads: Font = this layer's
// atlasRGBA(), Bitmap = ui::buildAtlasRGBA()'s (the HUD's existing atlas).
enum class GlyphSource : uint8_t { Font = 0, Bitmap = 1 };

// One glyph quad in viewport pixels. Same geometry fields as ui::TextQuad (font.h), plus the
// per-glyph colour the `\c` codes produce and the atlas the UVs belong to.
struct GlyphQuad {
    float       x = 0.f, y = 0.f, w = 0.f, h = 0.f;
    float       u0 = 0.f, v0 = 0.f, u1 = 0.f, v1 = 0.f;
    TextColor   color{};
    GlyphSource source = GlyphSource::Bitmap;
};

// A laid-out string in design units (the layer's integer space). Scale is applied by
// the caller, once per coordinate — the same pattern as the bitmap font, where the
// 5x7 design is multiplied by the caller's scale.
struct TextLayout {
    struct Item {
        uint32_t    cp = 0;
        int32_t     x64 = 0, y64 = 0;   // glyph box top-left, design units from the origin
        int32_t     advance64 = 0;      // pen advance (a space advances, it has no box)
        TextColor   color{};
        GlyphSource source = GlyphSource::Bitmap;
        bool        substituted = false;   // no glyph -> the '?' cell, advance unchanged
    };
    std::vector<Item> items;        // one per advancing code point, spaces included
    int32_t width64 = 0;            // widest line, design units
    int32_t lastLine64 = 0;         // last line's pen advance
    int32_t lineHeight64 = 0;
    int32_t ascent64 = 0;           // 0 with no font: the bitmap cell IS the line box
    int lines = 0;
    int substituted = 0;

    float width(float scale) const { return pixels(width64, scale); }
};

// ---------------------------------------------------------------------------
// Font chain
// ---------------------------------------------------------------------------

// One face of a fallback chain: the font bytes plus the LOGFONT cell height
// (lfHeight) the reference asked CreateFontIndirect for. `cellHeightPx` is what fixes
// the em — em = cellHeight * unitsPerEm / (ascent - descent), rounded — so it is an
// input to the metrics, not a cosmetic size.
struct FontFace {
    std::vector<uint8_t> bytes;
    float                cellHeightPx = 22.f;
};

// TrueType/OpenType faces the layer can draw, searched in order: the first face whose
// cmap has a code point supplies its glyph and advance. That is the port's stand-in
// for GDI font linking, where one logical font is backed by several faces and a
// character the primary lacks is served by the linked one.
using FontChain = std::vector<FontFace>;

// Repo-relative directories holding the fetched fonts (scripts/fetch_deps.sh writes
// them under the foundation's third_party/fonts/), nullptr-terminated. One list, so the
// HUD and the tests cannot disagree about where a pinned font lives; the callers decide
// what to resolve them against (the HUD uses the working directory, the tests also walk
// up from argv[0]). Nothing here is committed.
const char* const* fontSearchRoots();

// ---------------------------------------------------------------------------
// Glyph cache + dynamic atlas
// ---------------------------------------------------------------------------

struct GlyphInfo {
    int32_t advance64 = 0;                    // from the font's hmtx, integer design units
    int     x0 = 0, y0 = 0, x1 = 0, y1 = 0;   // bitmap box, baseline-relative, design px
    int     tileX = 0, tileY = 0;             // atlas origin; tile is (x1-x0) x (y1-y0)
    bool    present = false;                  // the font has a glyph for this code point
    bool    hasBitmap = false;                // ... and it produced ink (space does not)
};

class TextLayer {
public:
    TextLayer() = default;
    ~TextLayer();
    TextLayer(const TextLayer&) = delete;
    TextLayer& operator=(const TextLayer&) = delete;

    // Takes ownership of the font bytes (stb_truetype keeps offsets into them, not a
    // copy). `pixelHeight` is the design size in whole texels — the size glyphs are
    // rasterized at, and the unit the caller's scale multiplies: load at 21 and draw at
    // scale 1 to match the HUD's 21 px bitmap text at scale 3, or load at 7 and draw at
    // scale 3. Integer design sizes keep the metric math exact. This is the single-face
    // generic-TrueType mode; loadFontChain() is the reference's.
    //
    // Determinism contract, per docs/CJK-TEXT.md §4 (Linux == Windows == web):
    //   * metrics: hmtx/hhea values are integers; advance64 = round(v * px * 64 / em)
    //     with integer round-half-away-from-zero, so advances are identical everywhere;
    //   * no hinting: stb_truetype has no bytecode interpreter, so the outline is used
    //     as-is; the only grid effect is the integer bitmap box;
    //   * no subpixel positioning: the box/bitmap calls run with zero subpixel offsets,
    //     so a tile is a pure function of (font bytes, pixelHeight, glyph index);
    //   * packing is a pure function of the request sequence (256-wide shelves, 1 px
    //     padding, height doubling): same sequence, same atlas bytes.
    // What could still break it: the rasterizer's internal single-precision math if a
    // compiler contracts `a*b+c` into an FMA differently per target (GCC defaults to
    // -ffp-contract=fast; baseline x86-64 and wasm have no FMA, aarch64 does), x87
    // excess precision on 32-bit x86, FTZ/DAZ differences in denormal handling, and a
    // different font file — hence the pinned sha256 in fetch_deps.sh. Never build this
    // TU with -ffast-math. The test hashes the atlas, so such a divergence is caught
    // rather than silently banked.
    //
    // The bytes are trusted input: stb_truetype does no range checking on malformed
    // fonts (its own banner says so), so verify the pinned hash at fetch time.
    bool loadFont(std::vector<uint8_t> fontData, float pixelHeight, std::string& error);

    // The reference's metric mode (see the header comment). Every face is sized from
    // its own cell height, advances are whole pixels exactly as GetCharWidth32A reports
    // them, and the first baseline sits at the primary face's tmAscent minus its
    // tmExternalLeading — where the DX9 HUD's DrawText lands. The atlas is rasterized
    // from the same bytes either way; only the metric arithmetic differs.
    //
    // An empty chain, an unparsable face, or one with no usable vertical metrics fails
    // the call and leaves the layer bitmap-only, so the no-font contract below is the
    // single fallback for every failure.
    bool loadFontChain(const FontChain& chain, std::string& error);

    void unloadFont();
    bool fontLoaded() const { return !faces_.empty(); }
    const char* mode() const { return fontLoaded() ? "truetype" : "bitmap-only"; }
    // The design size in whole texels the layer rasterizes at: loadFont's pixel height,
    // or the em loadFontChain derived from the cell height.
    float pixelHeight() const { return (float)designPx_; }
    size_t faceCount() const { return faces_.size(); }
    // Font units per em of the face that supplies `cp`, or 0 when no face does.
    int faceUnitsPerEm(uint32_t cp) const;

    // ASCII from the font (default) or from the bitmap atlas. The switch exists to land
    // one CJK label without re-rasterizing every verified Latin HUD label in the same
    // step; with no font loaded everything is bitmap either way.
    void setFontAscii(bool on) { fontAscii_ = on; }
    bool fontAscii() const { return fontAscii_; }

    // Parses, measures and rasterizes: every glyph the string needs is in the cache and
    // in the atlas when this returns, so one upload after the last layout() of a frame
    // is enough. Unsupported code points advance one bitmap cell as '?' (ui/font.h's
    // rule), so layout never shifts under an unknown character. Control bytes below
    // 0x20 other than '\n' are skipped without advancing, exactly like ui::layoutText.
    TextLayout layout(const char* text, TextColor color = {});

    // Turns a layout into quads at (originX, originY), scaled by `scale`; boxes with no
    // ink (spaces) are skipped. Quads come out in the caller's batch order.
    void buildQuads(const TextLayout& l, float originX, float originY, float scale,
                    std::vector<GlyphQuad>& out) const;

    // True when the font has a glyph for `cp` (false without a font, and for a code
    // point the font omits). Cheap: no rasterization, no cache entry.
    bool hasGlyph(uint32_t cp) const;

    // Cached font glyph, or nullptr when it was never requested. Bitmap-sourced code
    // points (ASCII with setFontAscii(false), and every '?' substitution) have no entry
    // here: they live in the bitmap atlas.
    const GlyphInfo* glyphInfo(uint32_t cp) const;

    // Test seam, and the dump a future baked atlas (option C of CJK-TEXT.md §3) would
    // need: the atlas tile as (x1-x0) * (y1-y0) coverage bytes, row-major, top-down.
    std::vector<uint8_t> glyphCoverage(uint32_t cp) const;

    // Uploadable atlas: RGBA8, top-down, stride = width * 4, white RGB + coverage in
    // alpha, unused texels (0,0,0,0) — the same conventions as buildAtlasRGBA.
    // atlasRevision() changes whenever the bytes do (new tile or growth), which is the
    // caller's signal to re-upload.
    const std::vector<uint8_t>& atlasRGBA() const { return atlas_; }
    uint32_t atlasWidth() const { return atlasW_; }
    uint32_t atlasHeight() const { return atlasH_; }
    uint64_t atlasRevision() const { return revision_; }
    size_t cachedGlyphs() const { return cache_.size(); }
    size_t atlasFullDrops() const { return atlasFullDrops_; }

private:
    // 1/64 px per font unit, carried as the exact rational num/den: the scale is an
    // integer ratio, so no target can disagree about a glyph's advance.
    struct Face {
        std::vector<uint8_t> data;
        void*                info = nullptr;   // stbtt_fontinfo*, allocated on load
        int32_t              scaleNum = 0;
        int32_t              scaleDen = 1;
    };

    struct Resolved {
        int32_t     advance64 = 0;
        int         x0 = 0, y0 = 0, w = 0, h = 0;
        int         tileX = 0, tileY = 0;
        GlyphSource source = GlyphSource::Bitmap;
        bool        substituted = false;
    };

    Resolved resolve(uint32_t cp);
    const GlyphInfo* rasterizeFontGlyph(uint32_t cp);
    bool placeTile(int w, int h, int& tileX, int& tileY);
    void growAtlas();
    void resetAtlas();
    // Clears every face and resets the layer to the bitmap-only metric state.
    void clearFaces();
    // Parses and appends one face; the caller sets the metric scale.
    bool addFace(std::vector<uint8_t> bytes, std::string& error);
    // First face whose cmap covers `cp`, or nullptr. The chain order is the fallback
    // order, and it is fixed once loaded, so a glyph cached under `cp` stays valid.
    const Face* faceFor(uint32_t cp) const;

    std::vector<Face> faces_;                 // chain order; [0] is the primary

    bool fontAscii_ = true;   // ASCII: font when loaded, else bitmap
    int  designPx_ = 0;
    bool gdiMetrics_ = false;                 // whole-pixel advances (reference mode)
    int32_t originOffset64_ = 0;              // per-quad x offset (reference placement)
    // Defaults are the no-font state, so a default-constructed layer already lays text
    // out like the bitmap font (line height 8, no ascent) before loadFont() is called.
    int32_t ascent64_ = 0;
    int32_t lineHeight64_ = kLineHeight * kFixedOne;

    std::map<uint32_t, GlyphInfo> cache_;     // ordered: a deterministic dump order

    // 256 x 256 initially (256 KB), grown by doubling the height. Wide enough for any
    // glyph at the supported design sizes (a CJK tile is about 1.3 * designPx).
    static constexpr uint32_t kLayerAtlasW = 256;
    static constexpr uint32_t kLayerAtlasH0 = 256;
    static constexpr uint32_t kLayerAtlasMaxH = 4096;
    std::vector<uint8_t> atlas_;              // RGBA8, white + coverage in alpha
    uint32_t atlasW_ = 0, atlasH_ = 0;
    uint32_t packX_ = 0, packY_ = 0, packShelfH_ = 0;
    uint64_t revision_ = 0;
    size_t   atlasFullDrops_ = 0;
};

}  // namespace ui
