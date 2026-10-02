// =============================================================================
//  hud_text_test.cpp — the HUD's text metrics against the banked DX9 frames.
//
//  Device-free: no WebGPU, no window, no SDL. It needs ONE file at run time, the
//  fetched Latin face, and SKIPs cleanly (exit 0) without it, the way text_test.cpp
//  skips without the CJK font.
//
//  Why these numbers and not others. The reference HUD builds its font with
//  D3DXCreateFontA(device, 22, 0, FW_BOLD, 1, FALSE, DEFAULT_CHARSET,
//  OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", ...)
//  (remake/src/render/hud.cpp:18) and lays text out through ID3DXFont::DrawTextA. Under
//  the Wine prefix the frames were banked in (remake/tools/wine-prefix, driven by
//  tests/visual/run.sh) fontconfig resolves "Arial" to Liberation Sans, FW_BOLD selects
//  the Bold face, and lfHeight 22 — a positive height, i.e. the CELL — becomes em 20.
//  Everything asserted below was read off that stack rather than derived:
//
//    * GetCharWidth32A at lfHeight 22 returns the kGdiAdvance table (probed by building
//      CreateFontIndirectA + the same lf and asking GDI). It is whole pixels, and it is
//      NOT round(hmtx * 20 / 2048) for every glyph: 'I' is 6 where the exact value is
//      5.56, 'M' is 17 where it is 16.66. Reproducing the table is what keeps a label
//      from drifting a pixel per few glyphs.
//    * GetTextMetricsA reports tmHeight 22, tmAscent 18, tmDescent 4,
//      tmExternalLeading 1, and the banked frames put every label's cap-height ink rows
//      at rect.top + 3 — i.e. the baseline is at tmAscent - tmExternalLeading = 17 and
//      the cap-height box is 14 rows above it (GGO blackbox 14 high). It is NOT
//      tmAscent (18, one row lower) and not the raw (hhea ascent - lineGap) scaled
//      (17.45 px, half a row of blur).
//    * every glyph quad lands one pixel left of the pen the advances produce. All six
//      labels in gameplay-tapshot measure that offset (sub-pixel profile correlation:
//      +0.90..+1.05 px before, 0.00 after), and it comes from the rasterizer, not the
//      layout: GDI's own DrawTextA puts the ink where the layout says. Wine's builtin
    // the DLL next to the executable
//      D3DXFont's placement differs in.
//
//  Final line: "HUDTEXT: ok (n checks)" or "HUDTEXT: FAIL (n of m checks failed)".
//  Exit 0 on ok, 1 on any mismatch. Every mismatch prints expected vs got.
// =============================================================================
#include "ui/font.h"
#include "ui/text.h"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

int g_failures = 0;
int g_checks = 0;

void check(bool ok, const std::string& what) {
    ++g_checks;
    if (!ok) {
        ++g_failures;
        std::printf("FAIL: %s\n", what.c_str());
    }
}
void checkEq(long long got, long long want, const std::string& what) {
    check(got == want, what + " (expected " + std::to_string(want) + ", got " +
                           std::to_string(got) + ")");
}

void fail(const std::string& what) {
    ++g_failures;
    std::printf("FAIL: %s\n", what.c_str());
}

bool readFile(const fs::path& p, std::vector<uint8_t>& out) {
    std::ifstream f(p, std::ios::binary);
    if (!f) return false;
    out.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
    return !out.empty();
}

// Walks up from `start` looking for `rel`, so the test runs from the repo root, from
// the build directory and from anywhere ctest puts it.
fs::path findUpwards(const fs::path& start, const fs::path& rel) {
    fs::path dir = start;
    for (int i = 0; i < 8 && !dir.empty(); ++i) {
        const fs::path cand = dir / rel;
        if (fs::exists(cand)) return cand;
        if (dir == dir.parent_path()) break;
        dir = dir.parent_path();
    }
    return {};
}

// ---------------------------------------------------------------------------
// The reference's own metric tables, straight from the Win32 probes.
// ---------------------------------------------------------------------------

// GetCharWidth32A and GetCharABCWidthsA for lfHeight 22 / FW_BOLD / "Arial" (==
// Liberation Sans Bold), the whole printable ASCII range. Transcribed from the probe, so
// 'V' = 13 and 'W' = 19 are data: the exact hmtx values are 13.2 and 19.5, and rounding
// the second one the other way is a pixel per 'W'.
struct GdiChar {
    char ch;
    int  advance;   // GetCharWidth32A — whole pixels
    int  a;         // GetCharABCWidthsA's A spacing — where the ink box starts
};
const GdiChar kGdi[] = {
    {' ',  6,  0},
    {'!',  7,  1},
    {'"',  9,  1},
    {'#', 11,  0},
    {'$', 11,  0},
    {'%', 18,  0},
    {'&', 14,  0},
    {'\'',  5,  1},
    {'(',  7,  1},
    {')',  7,  0},
    {'*',  8,  0},
    {'+', 12,  0},
    {',',  6,  1},
    {'-',  7,  0},
    {'.',  6,  1},
    {'/',  6,  0},
    {'0', 11,  0},
    {'1', 11,  1},
    {'2', 11,  0},
    {'3', 11,  0},
    {'4', 11,  0},
    {'5', 11,  0},
    {'6', 11,  0},
    {'7', 11,  0},
    {'8', 11,  0},
    {'9', 11,  0},
    {':',  7,  1},
    {';',  7,  1},
    {'<', 12,  0},
    {'=', 12,  0},
    {'>', 12,  0},
    {'?', 12,  0},
    {'@', 20,  1},
    {'A', 14,  0},
    {'B', 14,  1},
    {'C', 14,  0},
    {'D', 14,  1},
    {'E', 13,  1},
    {'F', 12,  1},
    {'G', 16,  0},
    {'H', 14,  1},
    {'I',  6,  1},
    {'J', 11,  0},
    {'K', 14,  1},
    {'L', 12,  1},
    {'M', 17,  1},
    {'N', 14,  1},
    {'O', 16,  0},
    {'P', 13,  1},
    {'Q', 16,  0},
    {'R', 14,  1},
    {'S', 13,  0},
    {'T', 12,  0},
    {'U', 14,  1},
    {'V', 13,  0},
    {'W', 19,  0},
    {'X', 13,  0},
    {'Y', 13,  0},
    {'Z', 12,  0},
    {'[',  7,  1},
    {'\\',  6,  0},
    {']',  7,  0},
    {'^', 12,  0},
    {'_', 11, -1},
    {'`',  7,  0},
    {'a', 11,  0},
    {'b', 12,  1},
    {'c', 11,  0},
    {'d', 12,  0},
    {'e', 11,  0},
    {'f',  7,  0},
    {'g', 12,  0},
    {'h', 12,  1},
    {'i',  6,  1},
    {'j',  6, -1},
    {'k', 11,  1},
    {'l',  6,  1},
    {'m', 18,  1},
    {'n', 12,  1},
    {'o', 12,  0},
    {'p', 12,  1},
    {'q', 12,  0},
    {'r',  8,  1},
    {'s', 11,  0},
    {'t',  7,  0},
    {'u', 12,  1},
    {'v', 11,  0},
    {'w', 16, -1},
    {'x', 11,  0},
    {'y', 11,  0},
    {'z', 10,  0},
    {'{',  8,  0},
    {'|',  6,  1},
    {'}',  8,  0},
    {'~', 12,  0},
};

const GdiChar* gdi(char c) {
    for (const GdiChar& g : kGdi)
        if (g.ch == c) return &g;
    return nullptr;
}

// The HUD's own labels, at the anchors computeHudLayout derives for 800x600
// (scenes.cpp: the DrawText rect's left/top is the pen and the line's top).
struct Label {
    const char* text;
    int         penX, penY;
};
const Label kHudLabels[] = {
    {"0%", 20, 8},         {"LIMIT 100%", 20, 34}, {"0%", 680, 8},      {"LIMIT 100%", 680, 34},
    {"0", 4, 4},           {"HP", 580, 460},       {"5 MAIN", 580, 496}, {"2 CHARGE", 580, 538},
    {"FRIENDSHIP", 20, 560},
};

// tmAscent - tmExternalLeading at the HUD's size, and the cap-height ink box the HUD's
// glyphs share (GGO blackbox height 14).
constexpr int kBaselinePx = 17;
constexpr int kCapHeightPx = 14;
// The reference's glyph quads land one pixel left of the pen (see the header).
constexpr int kReferenceOriginShiftPx = -1;

// ---------------------------------------------------------------------------

std::string describe(char c, int index) {
    return std::string("'") + c + "' (glyph " + std::to_string(index) + ")";
}

}  // namespace

int main(int argc, char** argv) {
    fs::path fontPath;
    if (argc > 1 && argv[1][0]) fontPath = fs::path(argv[1]);
    const char* env = std::getenv("FOUNDATION_LATIN_FONT");
    if (fontPath.empty() && env && *env) fontPath = fs::path(env);
    if (fontPath.empty()) {
        static const char* kFile = "LiberationSans-Bold.ttf";
        for (const char* const* root = ui::fontSearchRoots(); root && *root; ++root) {
            fontPath = findUpwards(fs::current_path(), fs::path(*root) / kFile);
            if (fontPath.empty())
                fontPath = findUpwards(fs::absolute(argv[0]).parent_path(),
                                       fs::path(*root) / kFile);
            if (!fontPath.empty()) break;
        }
    }

    std::vector<uint8_t> fontBytes;
    if (fontPath.empty() || !readFile(fontPath, fontBytes)) {
        std::printf("SKIP: no Latin face at '%s'\n",
                    fontPath.empty() ? "(unset)" : fontPath.string().c_str());
        std::printf("      pass one as argv[1], set FOUNDATION_LATIN_FONT, or fetch the "
                    "pinned font into third_party/fonts/ (see fetch_deps.sh)\n");
        std::printf("HUDTEXT: skip\n");
        return 0;
    }
    std::printf("font: %s\n      %zu bytes\n", fontPath.string().c_str(), fontBytes.size());

    // ---------------------------------------------------------------- 1. the chain
    std::printf("\n== 1. the reference's chain (cell height 22)\n");
    ui::TextLayer layer;
    std::string err;
    check(!layer.fontLoaded(), "a fresh layer must report no font");
    ui::FontChain chain;
    chain.push_back(ui::FontFace{fontBytes, 22.f});
    if (!layer.loadFontChain(chain, err)) {
        fail("loadFontChain failed: " + err);
        std::printf("HUDTEXT: FAIL (%d of %d checks failed)\n", g_failures, g_checks);
        return 1;
    }
    check(layer.fontLoaded(), "the chain must load");
    checkEq(layer.faceCount(), 1, "one face in the chain");
    checkEq((long long)layer.pixelHeight(), 20,
            "lfHeight 22 is an em of 20 px (round(22 * 2048 / 2288))");
    checkEq(layer.faceUnitsPerEm('0'), 2048, "units per em of the face serving '0'");
    std::printf("chain: faces=%zu em=%.0f px mode=%s\n", layer.faceCount(), layer.pixelHeight(),
                layer.mode());

    // ------------------------------------------------- 2. the advance table
    std::printf("\n== 2. GetCharWidth32A parity (whole-pixel advances)\n");
    int advanceChecked = 0;
    for (const GdiChar& g : kGdi) {
        // '\\' is FUN_0065dad0's escape byte, so a lone one consumes itself and draws
        // nothing (documented in text.h); every other printable code point is one glyph.
        if (g.ch == '\\') {
            checkEq((long long)layer.layout("\\").items.size(), 0,
                    "a lone backslash is the escape byte, not a glyph");
            continue;
        }
        const ui::TextLayout l = layer.layout(std::string(1, g.ch).c_str());
        if (l.items.size() != 1) {
            fail(std::string("one item expected for '") + g.ch + "'");
            continue;
        }
        checkEq(l.items[0].advance64 / ui::kFixedOne, g.advance,
                std::string("advance of '") + g.ch + "'");
        ++advanceChecked;
    }
    std::printf("checked %d glyph advances against the GDI table\n", advanceChecked);

    // The exact value differs from the table for these two, which is the point: a
    // metric model that skipped GDI's rounding would pass everything else.
    const struct { char ch; int hmtxAdvance; } kRounded[] = {{'I', 569}, {'M', 1706}};
    for (const auto& r : kRounded) {
        const int exact64 = (int)std::lround((double)r.hmtxAdvance * 20.0 / 2048.0 * ui::kFixedOne);
        const ui::TextLayout l = layer.layout(std::string(1, r.ch).c_str());
        check(l.items[0].advance64 == (int64_t)std::lround((double)exact64 / ui::kFixedOne) *
                                           ui::kFixedOne,
              std::string("'") + r.ch + "' must use GDI's rounded advance, not the exact one");
    }

    // ------------------------------------------------- 3. pen and placement
    std::printf("\n== 3. layout positions and quad placement\n");
    for (const Label& label : kHudLabels) {
        const ui::TextLayout l = layer.layout(label.text);
        checkEq((long long)l.items.size(), (long long)std::strlen(label.text),
                std::string(label.text) + ": one item per byte");

        // Where the advances put each glyph (the GDI pen + A table), then where the
        // reference's rasterizer actually draws it. `pen` stays relative to the line
        // origin, which is the space TextLayout reports; the quads are viewport pixels.
        int pen = 0;
        std::vector<ui::GlyphQuad> quads;
        layer.buildQuads(l, (float)label.penX, (float)label.penY, 1.f, quads);
        size_t q = 0;
        for (size_t i = 0; i < l.items.size(); ++i) {
            const GdiChar* g = gdi((char)l.items[i].cp);
            if (!g) {
                fail(std::string("no GDI row for '") + (char)l.items[i].cp + "' in " + label.text);
                continue;
            }
            checkEq(l.items[i].x64 / ui::kFixedOne, pen + g->a,
                    describe(g->ch, (int)i) + " ink box origin in \"" + label.text + "\"");
            if (g->ch != ' ') {
                if (q >= quads.size()) {
                    fail(std::string("missing quad for '") + g->ch + "' in " + label.text);
                } else {
                    checkEq((long long)quads[q].x,
                            label.penX + pen + g->a + kReferenceOriginShiftPx,
                            describe(g->ch, (int)i) + " drawn x in \"" + label.text + "\"");
                    checkEq((long long)quads[q].y, label.penY + kBaselinePx - kCapHeightPx,
                            describe(g->ch, (int)i) + " drawn y in \"" + label.text + "\"");
                    ++q;
                }
            }
            pen += g->advance;
        }
        std::printf("  %-12s pen %3d -> %3d  width %3.0f px\n", label.text, label.penX,
                    label.penX + pen, l.width(1.f));
    }

    // The baseline check above only covers cap-height glyphs; '%' and 'Q' overshoot, so
    // pin the two that decide the ascent on their own.
    for (const char* s : {"0", "L", "H"}) {
        const ui::TextLayout l = layer.layout(s);
        checkEq(l.items[0].y64 / ui::kFixedOne, kBaselinePx - kCapHeightPx,
                std::string("baseline offset of '") + s + "'");
    }

    // --------------------------------------------- 4. the chain is a chain
    std::printf("\n== 4. fallback chain\n");
    {
        // A second face that cannot serve anything must not disturb the first: the
        // chain resolves in order and the cached glyphs keep their metrics.
        ui::TextLayer two;
        ui::FontChain c2;
        c2.push_back(ui::FontFace{fontBytes, 22.f});
        c2.push_back(ui::FontFace{fontBytes, 22.f});
        std::string e2;
        check(two.loadFontChain(c2, e2), "a two-face chain must load: " + e2);
        checkEq(two.faceCount(), 2, "two faces in the chain");
        const ui::TextLayout a = layer.layout("LIMIT 100%");
        const ui::TextLayout b = two.layout("LIMIT 100%");
        check(a.width64 == b.width64, "a redundant second face must not move the line");
        for (size_t i = 0; i < a.items.size(); ++i)
            check(a.items[i].x64 == b.items[i].x64,
                  "a redundant second face must not move glyph " + std::to_string(i));
        std::printf("  duplicate chain: width %d == %d\n", a.width64, b.width64);
    }

    // ------------------------------------- 5. no font -> today's HUD, bit for bit
    std::printf("\n== 5. no font -> the bitmap layer, bit for bit\n");
    {
        ui::TextLayer plain;
        static const char* kStrings[] = {"0%", "LIMIT 100%", "5 MAIN", "2 CHARGE", "HP",
                                         "FRIENDSHIP", "", "0"};
        int compared = 0;
        for (const char* s : kStrings) {
            const ui::TextLayout l = plain.layout(s);
            const ui::TextExtent e = ui::measureText(s, 1.f);
            check(std::fabs(l.width(1.f) - e.width) < 1e-6f,
                  std::string("no font: width of \"") + s + "\" must equal ui::measureText");
            std::vector<ui::TextQuad> want;
            std::vector<ui::GlyphQuad> got;
            ui::layoutText(s, 0.f, 0.f, 1.f, want);
            plain.buildQuads(l, 0.f, 0.f, 1.f, got);
            check(want.size() == got.size(),
                  std::string("no font: quad count of \"") + s + "\" must match ui::layoutText");
            for (size_t i = 0; i < want.size() && i < got.size(); ++i) {
                check(want[i].x == got[i].x && want[i].y == got[i].y && want[i].w == got[i].w &&
                          want[i].h == got[i].h && want[i].u0 == got[i].u0 &&
                          want[i].v0 == got[i].v0 && want[i].u1 == got[i].u1 &&
                          want[i].v1 == got[i].v1,
                      std::string("no font: quad ") + std::to_string(i) + " of \"" + s +
                          "\" must be bit-for-bit ui::layoutText");
            }
            compared += (int)want.size();
        }
        std::printf("  %zu strings, %d quads compared against ui::layoutText\n",
                    sizeof kStrings / sizeof *kStrings, compared);
    }

    // ------------------------------------- 6. the atlas is a pure function
    std::printf("\n== 6. atlas determinism\n");
    {
        // The same chain and the same request sequence must give the same atlas bytes on
        // every target; this is the in-process half (text_test.cpp hashes the CJK layer's
        // atlas for the cross-target half, and the rasterizer is the same code).
        ui::TextLayer a, b;
        std::string ea, eb;
        check(a.loadFontChain(ui::FontChain{ui::FontFace{fontBytes, 22.f}}, ea),
              "atlas run A must load: " + ea);
        check(b.loadFontChain(ui::FontChain{ui::FontFace{fontBytes, 22.f}}, eb),
              "atlas run B must load: " + eb);
        for (const Label& label : kHudLabels) a.layout(label.text);
        for (const Label& label : kHudLabels) b.layout(label.text);
        check(a.atlasRGBA().size() == b.atlasRGBA().size(), "same atlas size");
        check(a.atlasRGBA() == b.atlasRGBA(), "same atlas bytes from the same request order");
        check(a.atlasRevision() == b.atlasRevision(), "same atlas revision");
        checkEq((long long)a.cachedGlyphs(), (long long)b.cachedGlyphs(), "same cached glyphs");
        std::printf("  atlas %ux%u, %zu glyphs, revision %llu\n", a.atlasWidth(),
                    a.atlasHeight(), a.cachedGlyphs(), (unsigned long long)a.atlasRevision());
    }

    // ------------------------------------- 7. the fallback path is reachable
    std::printf("\n== 7. negative cases\n");
    {
        ui::TextLayer broken;
        std::string be;
        check(!broken.loadFontChain({}, be) && !broken.fontLoaded(),
              "an empty chain must be rejected");
        check(!be.empty(), "a rejected chain must set an error string");
        check(!broken.loadFontChain(ui::FontChain{ui::FontFace{{0x5A, 0x5A, 0x5A}, 22.f}}, be),
              "a garbage face must be rejected");
        check(std::strcmp(broken.mode(), "bitmap-only") == 0,
              "a rejected chain must leave the layer bitmap-only");
        check(broken.cachedGlyphs() == 0, "a rejected chain must leave no cached glyph");
        std::printf("  empty chain -> error=\"%s\"\n", be.c_str());
    }

    if (g_failures == 0) {
        std::printf("\nHUDTEXT: ok (%d checks)\n", g_checks);
        return 0;
    }
    std::printf("\nHUDTEXT: FAIL (%d of %d checks failed)\n", g_failures, g_checks);
    return 1;
}
