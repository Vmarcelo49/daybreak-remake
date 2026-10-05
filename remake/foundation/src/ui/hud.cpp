#include "ui/hud.h"

#include <cstdio>
#include <vector>

namespace ui {
namespace {

// Retain the banked DX9 HUD's 22 px caption cell before viewport scaling.
constexpr float kHudCellHeightPx = 22.f;

// One balloon corner, both halves of FUN_00644150's loop over `side` (0 left, 1
// right): the growing balloon sprite, the LIMIT label + its value at half scale, the
// big white percentage readout with its '%' glyph, and — while the corner's change
// pulse runs — the small green popup riding the balloon's top edge. The anchors are
// the .rdata immediates 0x6a3298/0x6a4c8c (balloon x, 85/715), 0x6a2c70 (balloon y,
// 140), 0x6a19b8/0x6a1c80 (label x, 70/700), 0x6a16e8 (readout x, 110) and
// 0x6a4c88/0x6a4c90/0x6a4c84 (right/left LIMIT x, 740/138/768).
void composeBalloonCorner(const HudAtlas& atlas, SpriteRenderer& batch, const HudState& st,
                          int side, const BattleHudLayout& layout) {
    const float balloonX = side == 0 ? 85.f : layout.width-85.f;
    const float labelX = side == 0 ? 70.f : layout.width-100.f;
    const float readoutX = side == 0 ? 110.f : layout.width-60.f;
    const float limitX = side == 0 ? 138.f : layout.width-32.f;
    const float pct = st.balloon[side] < 0.f ? 0.f : st.balloon[side];
    const int pulse = st.balloonPulse[side];
    atlas.draw(batch, side == 0 ? HudIcon::BalloonLeft : HudIcon::BalloonRight, balloonX, 140.f,
               hudBalloonScale(pct, pulse));
    atlas.draw(batch, HudIcon::LimitLabel, labelX, 110.f);
    atlas.number(batch, HudFont::BigWhite, (int)(pct + 0.5f), readoutX, 80.f);
    atlas.glyph(batch, HudFont::BigWhite, 5, 1, readoutX, 78.f);   // '%', cell (5,1)
    atlas.number(batch, HudFont::BigWhite, (int)(st.limit + 0.5f), limitX, 110.f, 0.5f);
    atlas.glyph(batch, HudFont::BigWhite, 5, 1, limitX, 110.f, 0.5f);
    // 0x644d5b: the popup exists only while the pulse runs, at (x, 30 + pulse/2) — it
    // slides up as the pulse counts down. Small green font: digits 0..9, then
    // '+'/'-'/'.'/'%' at cells 10..13, 28 px per step (32 + the font's -4 leading).
    if (pulse > 0) {
        const float y = 30.f + (float)pulse * 0.5f;
        const int value = st.balloonPulseValue[side];
        atlas.number(batch, HudFont::SmallGreen, value, readoutX, y);
        // FUN_00431b50's sign cell: the popup's call passes flag 1 (0x644d93), which
        // draws one more cell past the digits — the '+' for a positive value, the '-'
        // for a negative one — where the next digit would have gone. FUN_00431ce0
        // places a named cell four pixels left of its argument, hence the +4.
        int digits = 1;
        for (int v = value < 0 ? -value : value; v >= 10; v /= 10) ++digits;
        atlas.glyph(batch, HudFont::SmallGreen, value < 0 ? 11 : 10, 0,
                    readoutX - 28.f - 28.f * (float)digits + 4.f, y);
        atlas.glyph(batch, HudFont::SmallGreen, 13, 0, readoutX, y);
    }
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
    // Retain the reference's 80 px offset above viewport center (y=220 at 800x600).
    l.koCenterX = W * 0.5f;
    l.koY = H*.5f-80.f;
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
    if (loadCaptionFont(text_, kHudCellHeightPx, fontError)) {
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
        // Keep labels available when the caption face is missing or unusable.
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
    drawCaptionLayout(batch,text_,laid,textAtlas_,atlas_,x,y,1.f,color);
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
    drawCaptionLayout(batch,text_,laid,textAtlas_,atlas_,centerX-laid.width(1.f)*.5f,y,1.f,color);
}

void HudComposer::bar(SpriteRenderer& batch, const UiRect& r, float frac, UiColor fill) {
    // Back at full width, fill truncated to whole pixels — the DX9 Hud::bar
    // shape, including drawing nothing extra when the fill rounds to zero.
    batch.pushSolid(r, kHudBarBack);
    const int fw = barFillWidth((int)r.w, frac);
    if (fw > 0) batch.pushSolid(UiRect{r.x, r.y, (float)fw, r.h}, fill);
}

bool HudComposer::ensureBattleAtlas(SpriteRenderer& batch) {
    if (battleTried_) return battleAtlas_.ready();
    battleTried_ = true;
    std::string error;
    if (battleAtlas_.upload(batch, error)) {
        std::fprintf(stderr, "[fnd::ui] battle HUD atlases loaded (P00/P01/P02 via assetSource)\n");
        return true;
    }
    // Missing game data is the normal asset-less case, not an error: say which sheet
    // and keep the text HUD, so a capture without an install still renders a HUD.
    std::fprintf(stderr, "[fnd::ui] battle HUD atlases unavailable (%s); text HUD in use\n",
                 error.c_str());
    return false;
}

void HudComposer::composeBattle(SpriteRenderer& batch, const HudState& st, const BattleHudLayout& layout) {
    // Edge anchors retain FUN_00644150's margins at the reference resolution.
    const UiColor white = kHudWhite;
    const int frame = st.hudFrame;

    // HP: frame 0x6c7f60 @0x644187, the lagging ghost fill (hud+0x40c, P02 (0,496))
    // at 0x6441cc, then the live fill. Below 2500/10000 (0x6441de) the live fill
    // alternates its slot every 15 frames — slot 0 (P02 (0,480)) and slot 1
    // (P02 (256,480), the pale ramp) — which is the original's low-HP flash.
    battleAtlas_.draw(batch, HudIcon::HpFrame, layout.hp.x, layout.hp.y, 1.f, 0.f, white);
    battleAtlas_.fill(batch, HudIcon::HpFillGhost, st.hpLag / 100.f, layout.hp.x, layout.hp.y);
    const bool lowHp = st.hp < 25.f;
    const bool flashOn = lowHp && ((frame % 0x1e) / 0xf) != 0;
    battleAtlas_.fill(batch, flashOn ? HudIcon::HpFillPale : HudIcon::HpFill, st.hp / 100.f,
                      layout.hp.x, layout.hp.y);

    // OYASHIRO fan gauge: frame 0x64428d at (55,488), gradient fill through
    // FUN_00645690 (scale + FUN_00645250) at the same anchor, MAX label at (64,534)
    // once charged (0x6443e6), and the hypermode caption at (183,548) whose row is
    // hud+0x318 (0x644859). The original picks the fill cell by hud+0x318 (team 0
    // here, FUN_00642c50 @0x00642cf8-0x642e5b) and, while charged, alternates the
    // pair on (frame % 0x1e) / 0xf (0x6446b0) — the same counter as the HP flash.
    battleAtlas_.draw(batch, HudIcon::FanFrame, layout.fan.x, layout.fan.y, 1.f, 0.f, white);
    const float gauge = st.hyperGauge < 0.f ? 0.f : (st.hyperGauge > 1.f ? 1.f : st.hyperGauge);
    if (st.hyperActive || st.hyperReady) {
        battleAtlas_.fill(batch, ((frame % 0x1e) / 0xf) != 0 ? HudIcon::FanFillReadyAlt
                                                             : HudIcon::FanFillReady,
                          gauge, layout.fan.x, layout.fan.y);
    } else {
        battleAtlas_.fill(batch, HudIcon::FanFillCharging, gauge, layout.fan.x, layout.fan.y);
    }
    if (st.hyperReady && !st.hyperActive) battleAtlas_.draw(batch, HudIcon::MaxLabel, layout.maxLabel.x, layout.maxLabel.y);
    battleAtlas_.cell(batch, HudIcon::FanCaption, 0, st.hyperRow, layout.fanCaption.x, layout.fanCaption.y, 1.f, 0.f, white);

    // STAMINA: frame 0x6ca5a0 @0x64476d at (400,517) and the fill slot hud+0x4b8
    // (P01 (320,0,107,6), pivot (53,3) — it grows right from the frame's centre).
    // The original's gate is the fill's own value, hud+0x834 < 1000 (0x644758), i.e.
    // the bar is shown exactly while stamina is not full.
    if (st.staminaFrac < 1.f) {
        battleAtlas_.draw(batch, HudIcon::StaminaFrame, layout.stamina.x, layout.stamina.y, 1.f, 0.f, white);
        battleAtlas_.fill(batch, HudIcon::StaminaFill, st.staminaFrac, layout.stamina.x, layout.stamina.y);
    }

    // Boxed tactics/command label (0x6448ad): P03 (0,0,128,64) pivot (64,32), cell
    // (v % 4, v / 4) of hud+0x310, at (216,520); hud+0x314 adds to the scale, and a
    // negative cell index hides it (0x6447d7).
    if (st.commandCell >= 0) {
        const float cmdScale = st.commandScale > 0.f ? st.commandScale + 1.f : 1.f;
        battleAtlas_.cell(batch, HudIcon::CommandLabel, st.commandCell % 4, st.commandCell / 4,
                          layout.command.x, layout.command.y, cmdScale, 0.f, white);
    }

    // MAIN and CHARGE: frame, count, then fill (0x6448e5 / 0x64491d / 0x64495d /
    // 0x64499d / 0x6449ef / 0x644ac8). The fill strip switches to the grey slot when
    // the stock is empty, which is the count's only effect on the bar.
    battleAtlas_.draw(batch, HudIcon::MainFrame, layout.main.x, layout.main.y, 1.f, 0.f, white);
    battleAtlas_.draw(batch, HudIcon::ChargeFrame, layout.charge.x, layout.charge.y, 1.f, 0.f, white);
    battleAtlas_.number(batch, HudFont::BigWhite, st.mainWhole, layout.mainCount.x, layout.mainCount.y);
    battleAtlas_.number(batch, HudFont::BigWhite, st.chargeWhole, layout.chargeCount.x, layout.chargeCount.y);
    battleAtlas_.fill(batch, st.mainWhole > 0 ? HudIcon::MainFill : HudIcon::MainFillEmpty,
                      st.mainFrac, layout.main.x, layout.main.y);
    if (st.chargeWhole > 0) {
        battleAtlas_.fill(batch, HudIcon::ChargeFill, st.chargeFrac, layout.charge.x, layout.charge.y);
        // The C-held tier meter rides the CHARGE pill's lower half (0x644b0d /
        // 0x644b48 at y 525). HudState carries the tier as its resolved colour
        // (game/hud_bridge.h): the two real tiers are the surveyed red and yellow,
        // and the idle grey is not a tier at all, so it draws nothing.
        if (st.holdVisible && st.holdColor.r > 0.9f)
            battleAtlas_.fill(batch, st.holdColor.g > 0.6f ? HudIcon::ChargeTierYellow
                                                          : HudIcon::ChargeTierRed,
                              st.holdFrac, layout.chargeTier.x, layout.chargeTier.y);
    } else {
        battleAtlas_.fill(batch, HudIcon::ChargeFillEmpty, st.chargeFrac, layout.charge.x, layout.charge.y);
    }

    // Both balloon corners (0x644bfc-0x644e25), left then right.
    composeBalloonCorner(battleAtlas_, batch, st, 0, layout);
    composeBalloonCorner(battleAtlas_, batch, st, 1, layout);

    // Render-FPS counter, top-right (FUN_006396f0 @0x6396f0: DAT_006d18a4
    // right-aligned at x=800, y=0, scale 0.5). Always drawn in battle — no
    // gate surrounds the call — in the small yellow P00 row. The split-screen caller
    // keeps it in the first view only, because the original draws it once, outside its
    // view loop (FUN_006396f0:203-210).
    if (st.showFps)
        battleAtlas_.number(batch, HudFont::SmallYellow, st.fps, layout.fps.x, layout.fps.y, 0.5f);
}

void HudComposer::composeFighters(SpriteRenderer& batch, const HudState& st, const BattleHudLayout& layout) {
    const UiColor white = kHudWhite;
    for (int i = 0; i < kHudFighterCount; ++i) {
        const HudFighterHud& f = st.fighters[i];
        // FUN_00643230:67-96: the ring's column (local_30) and row (local_28). Row 0 is the
        // black "action running" ring, row 2 the green "this fighter has a lock" ring, row 1
        // the plain red one; column 2 is the blinking hyper ring, drawn while the fighter's
        // hyper mode is up and it has neither a lock nor an action. The shipped P03 rows are
        // black (0,128), red (0,256) and green (0,384) — BATTLE-HUD-SPEC §10's "red =
        // target" reading was the plain ring; the lock ring is the green one.
        int col = 0;
        int row = f.acting ? 0 : (f.locked ? 2 : 1);
        if (f.hyper && !f.acting && !f.locked) {
            col = 2;
            // FUN_00643230:73-77 blinks between rows 0 and 1 every 15 frames when the
            // fighter's +0x848 flag is clear; the port has no +0x848, so it takes the
            // blinking branch (a labelled port rule).
            row = (st.hudFrame % 0x1e) / 0xf;
        }
        const auto ring = hudRingTransform(st.hudFrame, f.ringPulse);
        if (f.visible) {
            // EVERY active fighter gets a ring — the original draws FUN_00643230 once per
            // fighter slot (FUN_006396f0:126-147) — which is what keeps an ally or an
            // opponent readable in a 2v2.
            battleAtlas_.cell(batch, HudIcon::Ring, col, row, f.ringX, f.ringY, ring.scale,
                              ring.firstDeg, white);
            // The view's OWN fighter gets the second, counter-rotating ring while it has no
            // lock of its own (local_31, FUN_00643230:97-102).
            if (f.role == HudFighterRole::Owner && !f.locked)
                battleAtlas_.cell(batch, HudIcon::Ring, col, row, f.ringX, f.ringY, ring.scale,
                                  ring.secondDeg, white);
        }
        // The target's com bar (the drawer at 0x643fa7): frame, the lagging fill
        // (hud+0xb0 = P01 (320,352,80,6)) then the live one (hud+0x4 =
        // P01 (320,320,80,6)), both pivot (40,3) so they grow right from the bar's
        // left edge, and the tag cell at (+24,+16) — 1P/2P/3P in row 0, 4P/com in row
        // 1, the red copies four rows down (0x64408c). The tag is the panel's controller,
        // so a 2v2 shows at a glance who is human and who is COM.
        if (f.visible && f.target) {
            battleAtlas_.draw(batch, HudIcon::ComBarFrame, f.barX, f.barY, 1.f, 0.f, white);
            battleAtlas_.fill(batch, HudIcon::ComBarFillGhost, f.hpLag, f.barX, f.barY);
            battleAtlas_.fill(batch, HudIcon::ComBarFill, f.hp, f.barX, f.barY);
            battleAtlas_.cell(batch, HudIcon::TagCell, f.slot % 3, f.slot / 3 + 4 * f.tagSheet,
                              f.barX + 24.f, f.barY + 16.f, 1.f, 0.f, white);
        }
        // The off-screen alert marker (0x643722-0x6437d0): the pale P06 pentagon on
        // the screen edge the fighter went off, at (400,64) top, (400,536) bottom,
        // (64,300) left, (736,300) right. It is the only cue an off-screen participant
        // has, so it is drawn for every roster entry that carries a direction.
        if (f.alertDir >= 0 && f.alertDir < 4) {
            const float ax = f.alertDir == 2 ? 64.f : (f.alertDir == 3 ? layout.width-64.f : layout.width*.5f);
            const float ay = f.alertDir == 0 ? 64.f : (f.alertDir == 1 ? layout.height-64.f : layout.height*.5f);
            battleAtlas_.draw(batch, HudIcon::AlertPale, ax, ay, 1.f, 0.f, white);
        }
    }
}

void HudComposer::compose(SpriteRenderer& batch, const HudState& st) {
    const auto battle = computeBattleHudLayout(batch.viewportW(),batch.viewportH());
    batch.setCanvasTransform(battle.scale);
    struct ResetTransform { SpriteRenderer& batch; ~ResetTransform() { batch.resetCanvasTransform(); } } reset{batch};
    const auto layout = computeHudLayout(int(battle.width),int(battle.height));
    // Art first: when the game's own sheets are there, the original's composition is
    // the whole HUD. Everything the DX9 text path draws beyond it (the RELOAD gate
    // tag, the unlabelled corner "0", the "READY (S)" hint) is that path's own
    // invention and is deliberately not mixed in — a frame is either the original's
    // HUD or the remake's stand-in, never half of each.
    if (ensureBattleAtlas(batch)) {
        composeFighters(batch, st, battle);
        // The round stings sit between the fighters and the corners: FUN_0063a130
        // @0x63a4b4 draws them centred at (400,300) at the viewport scale times a
        // per-slot float. The port draws the KO sting at the 0.5 the spec measured on
        // the print; the scale/alpha tween the original runs is the caller's to add
        // by scaling this call, not something the composer can invent.
        if (st.koVisible) battleAtlas_.draw(batch, HudIcon::KoSting, battle.ko.x, battle.ko.y, 0.5f);
        composeBattle(batch, st, battle);
        return;
    }
    // New linked glyphs can grow the atlas and change queued quads' UV denominator.
    if (textAtlas_ >= 0) text_.layout(st.hyperName.c_str());
    char buf[256];
    auto rightLabel = [&](const char* value, const UiRect& anchor, UiColor color) {
        const float width = textAtlas_ >= 0 ? text_.layout(value).width(1.f)
                                            : measureText(value,kHudTextScale).width;
        drawText(batch,value,anchor.x+100.f-width,anchor.y,color);
    };
    // Top corners: balloon % over LIMIT (%.0f%% / LIMIT %.0f%% per side).
    std::snprintf(buf, sizeof buf, "%.0f%%", st.balloon[0]);
    drawText(batch, buf, layout.balloonL.x, layout.balloonL.y, kHudWhite);
    std::snprintf(buf, sizeof buf, "LIMIT %.0f%%", st.limit);
    drawText(batch, buf, layout.limitL.x, layout.limitL.y, kHudLimitLeft);
    std::snprintf(buf, sizeof buf, "%.0f%%", st.balloon[1]);
    rightLabel(buf,layout.balloonR,kHudWhite);
    std::snprintf(buf, sizeof buf, "LIMIT %.0f%%", st.limit);
    rightLabel(buf,layout.limitR,kHudLimitRight);

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
