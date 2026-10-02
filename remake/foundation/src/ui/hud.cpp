#include "ui/hud.h"

#include <cstdio>
#include <vector>

namespace ui {
namespace {

// The cell height the DX9 HUD asks D3DXCreateFontA for (remake/src/render/hud.cpp:18:
// `D3DXCreateFontA(device, 22, 0, FW_BOLD, ...)`). Positive height is the cell, not the
// character, which is exactly why the em has to be derived rather than passed.
constexpr float kHudCellHeightPx = 22.f;

// Whole-file read; `found` distinguishes "no such font" (fall back to the bitmap atlas)
// from an empty file (which loadFontChain rejects with a message).
std::vector<uint8_t> readFile(const std::string& path, bool& found) {
    found = false;
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return {};
    std::fseek(f, 0, SEEK_END);
    const long n = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    std::vector<uint8_t> bytes;
    if (n > 0) {
        bytes.resize((size_t)n);
        found = std::fread(bytes.data(), 1, (size_t)n, f) == (size_t)n;
    }
    std::fclose(f);
    return found ? bytes : std::vector<uint8_t>{};
}

// Reads one face of the chain from the first root that has it.
std::vector<uint8_t> readFontFile(const char* name, bool& found) {
    for (const char* const* root = fontSearchRoots(); root && *root; ++root) {
        std::vector<uint8_t> bytes = readFile(std::string(*root) + name, found);
        if (found) return bytes;
    }
    found = false;
    return {};
}

// The reference's chain, in fallback order. Latin first because that is the face the
// banked frames were rendered with; the CJK face is second because Arial has no
// Japanese glyphs and the hypermode label is Japanese — GDI answers that with font
// linking, this chain with the next face. The Latin face is required: without it the
// HUD keeps the bitmap atlas, since a CJK-only chain would silently re-render every
// verified Latin label in a face the reference never used.
bool loadHudChain(TextLayer& layer, const HudFontFiles& files, std::string& error) {
    bool found = false;
    std::vector<uint8_t> latin = readFontFile(files.latin, found);
    if (!found) return false;   // no font fetched: the bitmap atlas is the answer
    FontChain chain;
    chain.push_back(FontFace{std::move(latin), kHudCellHeightPx});
    if (files.cjk && *files.cjk) {
        std::vector<uint8_t> cjk = readFontFile(files.cjk, found);
        if (found) chain.push_back(FontFace{std::move(cjk), kHudCellHeightPx});
    }
    return layer.loadFontChain(chain, error);
}

}  // namespace

HudRects computeHudLayout(int viewW, int viewH) {
    const float W = (float)viewW, H = (float)viewH;
    HudRects l;
    // Top corners: balloon % over LIMIT, left and right (scenes.cpp: x=20 and
    // x=W-120, y=8 and y=34).
    l.balloonL = UiRect{20.f, 8.f, 0.f, 0.f};
    l.limitL = UiRect{20.f, 34.f, 0.f, 0.f};
    l.balloonR = UiRect{W - 120.f, 8.f, 0.f, 0.f};
    l.limitR = UiRect{W - 120.f, 34.f, 0.f, 0.f};
    // Bottom-right P1 block: MAIN / CHARGE stocks, the C-hold tier meter above
    // them, and HP on top. Offsets from the right/bottom edges, as surveyed.
    l.mainText = UiRect{W - 220.f, H - 104.f, 0.f, 0.f};
    l.mainBar = UiRect{W - 220.f, H - 80.f, 180.f, 12.f};
    l.chargeText = UiRect{W - 220.f, H - 62.f, 0.f, 0.f};
    l.chargeBar = UiRect{W - 220.f, H - 38.f, 180.f, 12.f};
    l.holdBar = UiRect{W - 220.f, H - 118.f, 180.f, 8.f};
    l.hpText = UiRect{W - 220.f, H - 140.f, 0.f, 0.f};
    l.hpBar = UiRect{W - 180.f, H - 140.f, 160.f, 14.f};
    // The DX9 path draws an unlabelled yellow "0" in the top-left corner every frame
    // (scenes.cpp:829). It is not tied to any game state and looks like a leftover, but
    // it is in all three banked frames — a frame-parity port reproduces it.
    l.markerText = UiRect{4.f, 4.f, 0.f, 0.f};
    // Bottom-left hypermode gauge (spec §3.4).
    l.hyperText = UiRect{20.f, H - 40.f, 0.f, 0.f};
    l.hyperBar = UiRect{20.f, H - 64.f, 180.f, 12.f};
    // Centred stamina pair, shown only while spent (dash/guard/airborne).
    l.staminaText = UiRect{W * 0.5f - 100.f, H - 60.f, 0.f, 0.f};
    l.staminaBar = UiRect{W * 0.5f - 100.f, H - 38.f, 200.f, 12.f};
    // KO sting: horizontally centred band at y=220 (DX9 centered(220, 100)).
    l.koCenterX = W * 0.5f;
    l.koY = 220.f;
    return l;
}

void pushText(SpriteRenderer& batch, int atlasTexture, const char* text, float x, float y,
              float scale, UiColor color) {
    if (atlasTexture < 0 || !text || !*text) return;
    std::vector<TextQuad> glyphs;
    layoutText(text, x, y, scale, glyphs);
    for (const TextQuad& g : glyphs)
        batch.pushTextured(atlasTexture, UiRect{g.x, g.y, g.w, g.h},
                           UiRect{g.u0, g.v0, g.u1 - g.u0, g.v1 - g.v0}, color);
}

void pushTextCentered(SpriteRenderer& batch, int atlasTexture, const char* text, float centerX,
                      float y, float scale, UiColor color) {
    if (atlasTexture < 0 || !text || !*text) return;
    std::vector<TextQuad> glyphs;
    layoutTextCentered(text, centerX, y, scale, glyphs);
    for (const TextQuad& g : glyphs)
        batch.pushTextured(atlasTexture, UiRect{g.x, g.y, g.w, g.h},
                           UiRect{g.u0, g.v0, g.u1 - g.u0, g.v1 - g.v0}, color);
}

bool HudComposer::uploadFont(SpriteRenderer& batch, std::string& error) {
    if (atlas_ >= 0 || textAtlas_ >= 0) return true;
    std::string fontError;
    if (loadHudChain(text_, HudFontFiles{}, fontError)) {
        // Warm every ASCII glyph the HUD can print, so the atlas uploaded here is the one
        // the frames compose against: a tile added later would move every tile's UV
        // denominator and force the refresh below mid-frame.
        for (uint32_t cp = 32; cp < 127; ++cp) {
            const char one[2] = {(char)cp, '\0'};
            text_.layout(one);
        }
        if (!refreshTextAtlas(batch, error)) return false;
        return true;
    }
    if (!fontError.empty()) {
        // A font that is present but unusable is a fetch problem (a truncated download),
        // not a missing asset: say so and still draw, because a HUD without labels is
        // worse than one in the fallback face.
        std::fprintf(stderr, "[fnd::ui] hud font chain rejected (%s); using the bitmap atlas\n",
                     fontError.c_str());
    }
    std::vector<uint8_t> rgba;
    uint32_t w = 0, h = 0;
    buildAtlasRGBA(rgba, w, h);
    atlas_ = batch.addTexture(w, h, rgba.data(), error);
    return atlas_ >= 0;
}

bool HudComposer::refreshTextAtlas(SpriteRenderer& batch, std::string& error) {
    if (!textAtlasOk_) return false;
    if (textAtlas_ >= 0 && text_.atlasRevision() == textAtlasRevision_) return true;
    const std::vector<uint8_t>& rgba = text_.atlasRGBA();
    const uint32_t w = text_.atlasWidth(), h = text_.atlasHeight();
    if (rgba.size() < (size_t)w * h * 4) {
        error = "text atlas is smaller than its declared size";
        textAtlasOk_ = false;
        return false;
    }
    if (textAtlas_ < 0) {
        textAtlas_ = batch.addTexture(w, h, rgba.data(), error);
        if (textAtlas_ < 0) {
            textAtlasOk_ = false;
            return false;
        }
    } else if (!batch.updateTexture(textAtlas_, w, h, rgba.data(), error)) {
        // The tiles' UVs no longer match the texture, and a stale sample would smear
        // glyphs across the HUD; labels stop instead, which is this class's contract for
        // every text failure.
        textAtlasOk_ = false;
        return false;
    }
    textAtlasRevision_ = text_.atlasRevision();
    return true;
}

void HudComposer::drawText(SpriteRenderer& batch, const char* text, float x, float y,
                           UiColor color) {
    if (!text || !*text || !textAtlasOk_) return;
    if (textAtlas_ < 0) {
        pushText(batch, atlas_, text, x, y, kHudTextScale, color);
        return;
    }
    // No colour argument: the HUD's labels carry no `\c` runs, so one tint covers the
    // string exactly as it does on the bitmap path.
    std::string error;
    const TextLayout laid = text_.layout(text);
    if (!refreshTextAtlas(batch, error)) return;
    std::vector<GlyphQuad> glyphs;
    text_.buildQuads(laid, x, y, 1.f, glyphs);
    for (const GlyphQuad& g : glyphs)
        batch.pushTextured(textAtlas_, UiRect{g.x, g.y, g.w, g.h},
                           UiRect{g.u0, g.v0, g.u1 - g.u0, g.v1 - g.v0}, color);
}

void HudComposer::drawTextCentered(SpriteRenderer& batch, const char* text, float centerX,
                                   float y, UiColor color) {
    if (!text || !*text || !textAtlasOk_) return;
    if (textAtlas_ < 0) {
        pushTextCentered(batch, atlas_, text, centerX, y, kHudTextScale, color);
        return;
    }
    std::string error;
    const TextLayout laid = text_.layout(text);
    if (!refreshTextAtlas(batch, error)) return;
    std::vector<GlyphQuad> glyphs;
    // The bitmap layer centres the block on centerX (ui::layoutTextCentered); the font
    // layer starts from a pen, so the block's measured width is what moves.
    text_.buildQuads(laid, centerX - laid.width(1.f) * 0.5f, y, 1.f, glyphs);
    for (const GlyphQuad& g : glyphs)
        batch.pushTextured(textAtlas_, UiRect{g.x, g.y, g.w, g.h},
                           UiRect{g.u0, g.v0, g.u1 - g.u0, g.v1 - g.v0}, color);
}

void HudComposer::bar(SpriteRenderer& batch, const UiRect& r, float frac, UiColor fill) {
    // Back at full width, fill truncated to whole pixels — the DX9 Hud::bar
    // shape, including drawing nothing extra when the fill rounds to zero.
    batch.pushSolid(r, kHudBarBack);
    const int fw = barFillWidth((int)r.w, frac);
    if (fw > 0) batch.pushSolid(UiRect{r.x, r.y, (float)fw, r.h}, fill);
}

void HudComposer::compose(SpriteRenderer& batch, const HudState& st, const HudRects& layout) {
    char buf[256];
    // Top corners: balloon % over LIMIT (%.0f%% / LIMIT %.0f%% per side).
    std::snprintf(buf, sizeof buf, "%.0f%%", st.balloon[0]);
    drawText(batch, buf, layout.balloonL.x, layout.balloonL.y, kHudWhite);
    std::snprintf(buf, sizeof buf, "LIMIT %.0f%%", st.limit);
    drawText(batch, buf, layout.limitL.x, layout.limitL.y, kHudLimitLeft);
    std::snprintf(buf, sizeof buf, "%.0f%%", st.balloon[1]);
    drawText(batch, buf, layout.balloonR.x, layout.balloonR.y, kHudWhite);
    std::snprintf(buf, sizeof buf, "LIMIT %.0f%%", st.limit);
    drawText(batch, buf, layout.limitR.x, layout.limitR.y, kHudLimitRight);

    drawText(batch, "0", layout.markerText.x, layout.markerText.y, kHudMarkerText);

    // Bottom-right P1 block. The RELOAD tag rides the MAIN label between
    // volleys; the hold meter only exists while C is held.
    std::snprintf(buf, sizeof buf, "%d MAIN%s", st.mainWhole, st.reloading ? " RELOAD" : "");
    drawText(batch, buf, layout.mainText.x, layout.mainText.y, kHudWhite);
    bar(batch, layout.mainBar, st.mainFrac, kHudMainFill);
    std::snprintf(buf, sizeof buf, "%d CHARGE", st.chargeWhole);
    drawText(batch, buf, layout.chargeText.x, layout.chargeText.y, kHudWhite);
    bar(batch, layout.chargeBar, st.chargeFrac, kHudChargeFill);
    if (st.holdVisible) bar(batch, layout.holdBar, st.holdFrac, st.holdColor);
    drawText(batch, "HP", layout.hpText.x, layout.hpText.y, kHudWhite);
    bar(batch, layout.hpBar, st.hp / 100.f, kHudHpFill);

    // Bottom-left hypermode gauge: aura-coloured while active, grey otherwise;
    // the label gains seconds-left, READY (S), or nothing per mode state.
    if (st.hyperActive) {
        std::snprintf(buf, sizeof buf, "%s %.0fs", st.hyperName.c_str(), st.hyperSecondsLeft);
        drawText(batch, buf, layout.hyperText.x, layout.hyperText.y, st.hyperAura);
        bar(batch, layout.hyperBar, st.hyperGauge, st.hyperAura);
    } else if (st.hyperReady) {
        std::snprintf(buf, sizeof buf, "%s  READY (S)", st.hyperName.c_str());
        drawText(batch, buf, layout.hyperText.x, layout.hyperText.y, kHudHyperReadyText);
        bar(batch, layout.hyperBar, st.hyperGauge, kHudHyperIdleFill);
    } else {
        drawText(batch, st.hyperName.c_str(), layout.hyperText.x, layout.hyperText.y, kHudWhite);
        bar(batch, layout.hyperBar, st.hyperGauge, kHudHyperIdleFill);
    }

    // Contextual stamina pair.
    if (st.staminaVisible) {
        drawText(batch, "STAMINA", layout.staminaText.x, layout.staminaText.y, kHudWhite);
        bar(batch, layout.staminaBar, st.staminaFrac, kHudStaminaFill);
    }

    // KO sting: steady while visible (the DX9 path shows it for a fixed 2 s
    // window); any blink is the caller's clock, not composer state.
    if (st.koVisible)
        drawTextCentered(batch, "KO!", layout.koCenterX, layout.koY, kHudKoText);
}

}  // namespace ui
