#include "ui/hud.h"

#include <cstdio>

namespace ui {

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
    if (atlas_ >= 0) return true;
    std::vector<uint8_t> rgba;
    uint32_t w = 0, h = 0;
    buildAtlasRGBA(rgba, w, h);
    atlas_ = batch.addTexture(w, h, rgba.data(), error);
    return atlas_ >= 0;
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
    pushText(batch, atlas_, buf, layout.balloonL.x, layout.balloonL.y, kHudTextScale, kHudWhite);
    std::snprintf(buf, sizeof buf, "LIMIT %.0f%%", st.limit);
    pushText(batch, atlas_, buf, layout.limitL.x, layout.limitL.y, kHudTextScale, kHudLimitLeft);
    std::snprintf(buf, sizeof buf, "%.0f%%", st.balloon[1]);
    pushText(batch, atlas_, buf, layout.balloonR.x, layout.balloonR.y, kHudTextScale, kHudWhite);
    std::snprintf(buf, sizeof buf, "LIMIT %.0f%%", st.limit);
    pushText(batch, atlas_, buf, layout.limitR.x, layout.limitR.y, kHudTextScale,
             kHudLimitRight);

    // Bottom-right P1 block. The RELOAD tag rides the MAIN label between
    // volleys; the hold meter only exists while C is held.
    std::snprintf(buf, sizeof buf, "%d MAIN%s", st.mainWhole, st.reloading ? " RELOAD" : "");
    pushText(batch, atlas_, buf, layout.mainText.x, layout.mainText.y, kHudTextScale, kHudWhite);
    bar(batch, layout.mainBar, st.mainFrac, kHudMainFill);
    std::snprintf(buf, sizeof buf, "%d CHARGE", st.chargeWhole);
    pushText(batch, atlas_, buf, layout.chargeText.x, layout.chargeText.y, kHudTextScale,
             kHudWhite);
    bar(batch, layout.chargeBar, st.chargeFrac, kHudChargeFill);
    if (st.holdVisible) bar(batch, layout.holdBar, st.holdFrac, st.holdColor);
    pushText(batch, atlas_, "HP", layout.hpText.x, layout.hpText.y, kHudTextScale, kHudWhite);
    bar(batch, layout.hpBar, st.hp / 100.f, kHudHpFill);

    // Bottom-left hypermode gauge: aura-coloured while active, grey otherwise;
    // the label gains seconds-left, READY (S), or nothing per mode state.
    if (st.hyperActive) {
        std::snprintf(buf, sizeof buf, "%s %.0fs", st.hyperName.c_str(), st.hyperSecondsLeft);
        pushText(batch, atlas_, buf, layout.hyperText.x, layout.hyperText.y, kHudTextScale,
                 st.hyperAura);
        bar(batch, layout.hyperBar, st.hyperGauge, st.hyperAura);
    } else if (st.hyperReady) {
        std::snprintf(buf, sizeof buf, "%s  READY (S)", st.hyperName.c_str());
        pushText(batch, atlas_, buf, layout.hyperText.x, layout.hyperText.y, kHudTextScale,
                 kHudHyperReadyText);
        bar(batch, layout.hyperBar, st.hyperGauge, kHudHyperIdleFill);
    } else {
        pushText(batch, atlas_, st.hyperName.c_str(), layout.hyperText.x, layout.hyperText.y,
                 kHudTextScale, kHudWhite);
        bar(batch, layout.hyperBar, st.hyperGauge, kHudHyperIdleFill);
    }

    // Contextual stamina pair.
    if (st.staminaVisible) {
        pushText(batch, atlas_, "STAMINA", layout.staminaText.x, layout.staminaText.y,
                 kHudTextScale, kHudWhite);
        bar(batch, layout.staminaBar, st.staminaFrac, kHudStaminaFill);
    }

    // KO sting: steady while visible (the DX9 path shows it for a fixed 2 s
    // window); any blink is the caller's clock, not composer state.
    if (st.koVisible)
        pushTextCentered(batch, atlas_, "KO!", layout.koCenterX, layout.koY, kHudTextScale,
                         kHudKoText);
}

}  // namespace ui
