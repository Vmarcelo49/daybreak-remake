#pragma once
// Battle HUD sprite atlas: the .cnv -> texture -> sub-rect pipeline the original's
// HUD draws through.
//
// WHY this exists: every bar, every number and every label of the in-battle HUD is
// texture art, not text. BATTLE-HUD-SPEC.md §4 records the evidence — a byte search
// of DaybreakDX.exe finds no LIMIT/CHARGE/STAMINA/OYASHIRO/com string at all, only
// the glyph art in data/object/P00..P03.cnv — so the DX9 remake's Arial labels and
// flat bars cannot be corrected by adjusting fonts; they have to be replaced by the
// game's own sub-rect sprites. This file is that replacement's asset half.
//
// Provenance of every constant here (base 0x400000, .text 0x401000-0x6a0fff):
//   * FUN_00642510 @0x00642510 creates the static sub-rect sprites (atlas rect +
//     pivot per FUN_00655b20 call) and the number fonts; FUN_00642a00 @0x00642a00
//     creates the per-player bar/fill slots; FUN_00642c50 @0x00642c50 points the
//     fill slots at their values and overwrites the fan-gauge slots.
//   * FUN_00644150 @0x00644150 draws the corner HUD: (505,565) HP, (55,488) fan,
//     (623,471) MAIN, (597,517) CHARGE, (702,443)/(676,489) the counts, the two
//     balloon readouts and balloons, (400,517) STAMINA, (216,520) the boxed
//     command label.
//   * FUN_00643230 @0x00643230 and the drawer at 0x00643e38 draw the per-fighter
//     HUD: the targeting ring, the target's com bar (frame + lag/live fills + the
//     1P/2P/3P/com tag) and the P06 off-screen alert markers.
//   * FUN_0063a130 @0x0063a130 draws the round stings centred at (400,300).
//   * FUN_00655b20 @0x00655b20 is the sprite ABI (rect + pivot), FUN_00655d60
//     @0x00655d60 the draw, FUN_00655c0 @0x006556c0 the cell-rect variant,
//     FUN_00645250 @0x00645250 the clipped gauge fill, FUN_00431a50/00431b20/
//     00431ce0 the number fonts and their two draw calls.
//
// Bytes come from fnd::assets::assetSource() and never from a filesystem path: the
// exe resolves data/object/*.bmp through its bundle list (FUN_00653540 @0x00653540
// walks it, FUN_00662f70 probes a name, first match wins; FUN_006560c0 @0x006560c0
// is the loader that maps .bmp to the shipped .cnv), and P01.cnv is a live case
// where that order decides the pixels — daybreak00.dat and daybreak04.dat ship
// different bytes. asset_source.cpp owns the order, so this file only asks it.
#include <cstdint>
#include <string>

#include "ui/sprite.h"

namespace ui {

// The shipped HUD sheets, named as FUN_00642510 asks for them (P00.bmp -> P00.cnv).
// P09 carries the round stings; it is loaded because the KO sting is a state the
// match simulation already has (MatchEconomy's KO window), not a transient the port
// would have to invent.
enum class HudSheet : uint8_t { P00 = 0, P01, P02, P03, P06, P09, P04, P05, P08, P12, Count };

// The sprites the implemented elements draw. The name after the comment is the
// exe's own static sprite (or HUD-object slot) the numbers were read from.
enum class HudIcon : uint8_t {
    HpFrame,             // 0x6c7f60  P01 (32,192,256,64)  pivot (13,25)
    MainFrame,           // 0x6ca6e0  P01 (64,128,192,64)  pivot (16,29)
    ChargeFrame,         // 0x6ca780  P01 (64,64,192,64)   pivot (16,27)
    FanFrame,            // 0x6c7cb8  P01 (0,256,300,128)  pivot (45,21)
    MaxLabel,            // 0x6c7b78  P00 (384,384,128,128) pivot (64,64)
    HpFill,              // hud+0x2b4 P02 (0,480,230,14)   normal HP ramp
    HpFillPale,          // hud+0x360 P02 (256,480,230,14) low-HP flash variant
    HpFillGhost,         // hud+0x40c P02 (0,496,230,14)   lagging HP ghost
    MainFill,            // hud+0x768 P01 (320,128,160,6)  blue, count > 0
    MainFillEmpty,       // hud+0x8c0 P01 (320,144,160,6)  grey, count == 0
    ChargeFill,          // hud+0x814 P01 (320,64,160,6)   teal, count > 0
    ChargeFillEmpty,     // hud+0x96c P01 (320,80,160,6)   grey, count == 0
    ChargeTierYellow,    // hud+0xa18 P01 (320,96,160,5)   C-held tier meter, low
    ChargeTierRed,       // hud+0xac4 P01 (320,112,160,5)  C-held tier meter, high
    FanFillCharging,     // hud+0x564 P02 (0,0,230,91)     team 0, gauge filling
    FanFillReady,        // hud+0x610 P02 (0,288,230,91)   team 0, gauge charged
    FanFillReadyAlt,     // hud+0x6bc P02 (0,384,230,91)   its alternating pair
    FanCaption,          // 0x6c7df8  P01 (0,384,128,32)   row = hypermode (0..2)
    // Balloon corners (FUN_00644150 @0x644bfc-0x644e25).
    BalloonLeft,         // 0x6ca460  P00 (0,320,192,192)   pivot (96,160)
    BalloonRight,        // 0x6ca500  P00 (192,320,192,192) pivot (96,160)
    LimitLabel,          // 0x6ca640  P00 (384,320,96,32)   pivot (56,8)
    // STAMINA and the boxed tactics/command label (@0x64476d, @0x6448ad).
    StaminaFrame,        // 0x6ca5a0  P01 (64,0,192,64)     pivot (96,32)
    StaminaFill,         // hud+0x4b8 P01 (320,0,107,6)      pivot (53,3)
    CommandLabel,        // 0x6ca140  P03 (0,0,128,64)       pivot (64,32)
    // Per-fighter HUD (FUN_00643230 @0x643431, @0x6439db; the target-bar drawer
    // @0x643fa7).
    // P03 carries the reticle as a PAIR of adjacent 128-px cells per column: the circle,
    // then the four outward triangles. This entry names the CIRCLE; the counter-rotating
    // second copy is the next column along (hud.h's hudRingSecondCellColumn, issue #55).
    Ring,                // 0x6c7d58  P03 (0,128,128,128)    pivot (64,64)
    ComBarFrame,         // 0x6ca0a0  P01 (320,192,192,64)   pivot (96,32)
    ComBarFill,          // hud+0x4   P01 (320,320,80,6)     pivot (40,3)
    ComBarFillGhost,     // hud+0xb0  P01 (320,352,80,6)     pivot (40,3)
    TagCell,             // 0x6c7ad8  P01 (320,256,64,32)    pivot (32,16)
    AlertPale,           // 0x6c78f8  P06 (0,128,128,128)    pivot (64,64)
    AlertHot,            // draw_battle_direction_hud: P06 (0,0,128,128), its pair one cell along
    ComBarFrameAlly,     // draw_battle_overhead_hud: the ally's frame and strips
    ComBarFillAlly,
    ComBarFillGhostAlly,
    // Round sting (FUN_0063a130 @0x63a4b4, sprite scene+0x7f8).
    KoSting,             // scene+0x7f8 P09 (0,256,512,256)  pivot (256,128)
    NoticeThree,         // 633ca0 bindings, 63a130: the startup digits and start, the respawn
    NoticeTwo,           // notices, and the P05/P08 win and lose glyphs of phase 3
    NoticeOne,
    NoticeStart,
    NoticeRevive,
    NoticeReviveAlt,
    ResultBlueMain,
    ResultBlueSecond,
    ResultRedMain,
    ResultRedSecond,
    Count,
};

// FUN_006560c0's loader for one sheet: `stem` is the path the exe asks for
// ("data/title/title"), the .cnv spelling it ships as is probed first and the .bmp an
// extracted tree may carry second. The bytes come from assetSource() (bundle-first, the
// exe's own order) and are decoded by xm::decodeCnvImage, the foundation's one CNV
// decoder; `slot` receives the uploaded texture id (>= 0) on success. The front-end
// screens load through this too (ui/screen_title.cpp), so ui/ has ONE bundle-first CNV
// path per screen family rather than one per screen; HudAtlas::upload is the HUD's user.
bool uploadCnvSheet(SpriteRenderer& batch, const char* stem, int& slot, std::string& error);
// P13 multiplies the scene by its RGB (FUN_00643230 mode 3). The batch only blends by alpha, so
// the mask uploads as black with alpha 1 - luminance, which gives the same result for a grey mask.
bool uploadMultiplyMask(SpriteRenderer& batch, const char* stem, int& slot, std::string& error);

// One entry of the original's sprite table: the atlas sub-rect (FUN_00655b20's
// params 2..5) and the pivot (its params 6..7).
struct HudSprite {
    HudSheet sheet = HudSheet::P00;
    UiRect   src{};              // atlas pixels
    float    pivotX = 0.f, pivotY = 0.f;
};

// FUN_00642510's static sprites, then FUN_00642a00's slots in slot order and
// FUN_00642c50's fan-gauge overwrite — transcribed in the order of the HudIcon
// enum, which the static_assert below pins. Data only (no device, no asset), so
// the table is constexpr and a host test can check it directly.
inline constexpr HudSprite kHudSprites[] = {
    /* HpFrame          */ {HudSheet::P01, {32.f, 192.f, 256.f, 64.f}, 13.f, 25.f},
    /* MainFrame        */ {HudSheet::P01, {64.f, 128.f, 192.f, 64.f}, 16.f, 29.f},
    /* ChargeFrame      */ {HudSheet::P01, {64.f, 64.f, 192.f, 64.f}, 16.f, 27.f},
    /* FanFrame         */ {HudSheet::P01, {0.f, 256.f, 300.f, 128.f}, 45.f, 21.f},
    /* MaxLabel         */ {HudSheet::P00, {384.f, 384.f, 128.f, 128.f}, 64.f, 64.f},
    /* HpFill           */ {HudSheet::P02, {0.f, 480.f, 230.f, 14.f}, 0.f, 0.f},
    /* HpFillPale       */ {HudSheet::P02, {256.f, 480.f, 230.f, 14.f}, 0.f, 0.f},
    /* HpFillGhost      */ {HudSheet::P02, {0.f, 496.f, 230.f, 14.f}, 0.f, 0.f},
    /* MainFill         */ {HudSheet::P01, {320.f, 128.f, 160.f, 6.f}, 0.f, 0.f},
    /* MainFillEmpty    */ {HudSheet::P01, {320.f, 144.f, 160.f, 6.f}, 0.f, 0.f},
    /* ChargeFill       */ {HudSheet::P01, {320.f, 64.f, 160.f, 6.f}, 0.f, 0.f},
    /* ChargeFillEmpty  */ {HudSheet::P01, {320.f, 80.f, 160.f, 6.f}, 0.f, 0.f},
    /* ChargeTierYellow */ {HudSheet::P01, {320.f, 96.f, 160.f, 5.f}, 0.f, 0.f},
    /* ChargeTierRed    */ {HudSheet::P01, {320.f, 112.f, 160.f, 5.f}, 0.f, 0.f},
    // FUN_00642c50's team-0 cells: (0,0) while the gauge fills, (0,288)/(0,384) as the
    // two charged colours, which the original alternates on (frame % 0x1e) / 0xf
    // (0x6446b0) exactly as it does the low-HP HP ramp.
    /* FanFillCharging  */ {HudSheet::P02, {0.f, 0.f, 230.f, 91.f}, 0.f, 0.f},
    /* FanFillReady     */ {HudSheet::P02, {0.f, 288.f, 230.f, 91.f}, 0.f, 0.f},
    /* FanFillReadyAlt  */ {HudSheet::P02, {0.f, 384.f, 230.f, 91.f}, 0.f, 0.f},
    // FUN_00655690-created, so pivot (0,0); the three rows are OYASHIRO (0x644859's
    // cell row = hud+0x318) in daybreak04's P01, the copy assetSource() resolves.
    /* FanCaption       */ {HudSheet::P01, {0.f, 384.f, 128.f, 32.f}, 0.f, 0.f},
    /* BalloonLeft      */ {HudSheet::P00, {0.f, 320.f, 192.f, 192.f}, 96.f, 160.f},
    /* BalloonRight     */ {HudSheet::P00, {192.f, 320.f, 192.f, 192.f}, 96.f, 160.f},
    /* LimitLabel       */ {HudSheet::P00, {384.f, 320.f, 96.f, 32.f}, 56.f, 8.f},
    /* StaminaFrame     */ {HudSheet::P01, {64.f, 0.f, 192.f, 64.f}, 96.f, 32.f},
    /* StaminaFill      */ {HudSheet::P01, {320.f, 0.f, 107.f, 6.f}, 53.f, 3.f},
    /* CommandLabel     */ {HudSheet::P03, {0.f, 0.f, 128.f, 64.f}, 64.f, 32.f},
    /* Ring             */ {HudSheet::P03, {0.f, 128.f, 128.f, 128.f}, 64.f, 64.f},
    /* ComBarFrame      */ {HudSheet::P01, {320.f, 192.f, 192.f, 64.f}, 96.f, 32.f},
    /* ComBarFill       */ {HudSheet::P01, {320.f, 320.f, 80.f, 6.f}, 40.f, 3.f},
    /* ComBarFillGhost  */ {HudSheet::P01, {320.f, 352.f, 80.f, 6.f}, 40.f, 3.f},
    /* TagCell          */ {HudSheet::P01, {320.f, 256.f, 64.f, 32.f}, 32.f, 16.f},
    /* AlertPale        */ {HudSheet::P06, {0.f, 128.f, 128.f, 128.f}, 64.f, 64.f},
    /* AlertHot         */ {HudSheet::P06, {0.f, 0.f, 128.f, 128.f}, 64.f, 64.f},
    /* ComBarFrameAlly  */ {HudSheet::P01, {320.f, 448.f, 192.f, 64.f}, 96.f, 32.f},
    /* ComBarFillAlly   */ {HudSheet::P01, {320.f, 333.f, 80.f, 6.f}, 40.f, 4.f},
    /* ComBarFillGhostA */ {HudSheet::P01, {320.f, 349.f, 80.f, 6.f}, 40.f, 4.f},
    /* KoSting          */ {HudSheet::P09, {0.f, 256.f, 512.f, 256.f}, 256.f, 128.f},
    /* NoticeThree      */ {HudSheet::P09, {0.f, 0.f, 192.f, 256.f}, 96.f, 128.f},
    /* NoticeTwo        */ {HudSheet::P09, {192.f, 0.f, 192.f, 256.f}, 96.f, 128.f},
    /* NoticeOne        */ {HudSheet::P09, {384.f, 0.f, 128.f, 256.f}, 64.f, 128.f},
    /* NoticeStart      */ {HudSheet::P04, {0.f, 256.f, 512.f, 256.f}, 256.f, 128.f},
    /* NoticeRevive     */ {HudSheet::P04, {0.f, 0.f, 512.f, 256.f}, 256.f, 128.f},
    /* NoticeReviveAlt  */ {HudSheet::P04, {0.f, 288.f, 512.f, 192.f}, 256.f, 96.f},
    /* ResultBlueMain   */ {HudSheet::P05, {0.f, 0.f, 512.f, 256.f}, 256.f, 128.f},
    /* ResultBlueSecond */ {HudSheet::P05, {0.f, 256.f, 512.f, 256.f}, 256.f, 128.f},
    /* ResultRedMain    */ {HudSheet::P08, {0.f, 0.f, 512.f, 256.f}, 256.f, 128.f},
    /* ResultRedSecond  */ {HudSheet::P08, {0.f, 256.f, 512.f, 256.f}, 256.f, 128.f},
};
static_assert(sizeof(kHudSprites) / sizeof(kHudSprites[0]) == (size_t)HudIcon::Count,
              "sprite table and HudIcon must stay in step");

inline const HudSprite& hudSprite(HudIcon icon) { return kHudSprites[(size_t)icon]; }

// The two number fonts FUN_00642510 builds. `base` is the first cell's atlas rect;
// `perRow` cells are laid out from it, `leading` is FUN_00431a50's last argument
// (the gap between cells, negative).
//
// FUN_00431a50 @0x431a50 creates 12 cells per font, so a digit's cell is
// (d % perRow, d / perRow); the glyphs past the digits are addressed by FUN_00431ce0
// and are the same cells: big (5,1) is '%' at atlas (320,64), small (13,0) is '%' at
// (416,256) — P00's second white row is "8 9 … % /" and its small rows end
// "… + - . %" (verified against the shipped P00.cnv).
struct HudFontSpec {
    HudSheet sheet;
    UiRect   base;        // atlas rect of cell 0
    int      perRow;
    float    leading;     // 0xc1e00000 = -28.0f for the big fonts, 0xc0800000 = -4.0f small
};

enum class HudFont : uint8_t { BigWhite = 0, SmallGreen, SmallYellow, Count };

inline constexpr HudFontSpec kHudFonts[] = {
    /* BigWhite   0x6c8000 */ {HudSheet::P00, {0.f, 0.f, 64.f, 64.f}, 8, -28.f},
    /* SmallGreen 0x6c9050 */ {HudSheet::P00, {0.f, 256.f, 32.f, 32.f}, 15, -4.f},
    /* SmallYellow          */ {HudSheet::P00, {0.f, 288.f, 32.f, 32.f}, 15, 0.f},
};
static_assert(sizeof(kHudFonts) / sizeof(kHudFonts[0]) == (size_t)HudFont::Count,
              "font table and HudFont must stay in step");

inline const HudFontSpec& hudFont(HudFont f) { return kHudFonts[(size_t)f]; }

// One digit of a right-aligned run: the P00 cell and where its top-left goes.
struct HudDigit {
    UiRect src;
    float  x = 0.f, y = 0.f, scale = 1.f;
};

// FUN_00431b50 @0x431b50: lays `value` out right-aligned at (x, y) into `out` (at
// least 10 entries) and returns how many were written. The run starts one cell left
// of the anchor (`x - scale*cellW`) and steps left by (cellW + leading)*scale, which
// is why the LIMIT readout's "100" ends on its anchor. Pure arithmetic over the
// font's own constants, so the number layout is unit-testable without a device.
inline int hudDigitRun(HudFont font, int value, float x, float y, float scale, HudDigit* out) {
    const HudFontSpec& f = hudFont(font);
    const float cw = f.base.w;
    int v = value < 0 ? -value : value;
    float cx = x - scale * cw;   // FUN_00431b50's `x - scale*cellW`
    int n = 0;
    for (; n < 10; ++n) {
        const int d = v % 10;
        out[n].src = UiRect{f.base.x + (float)(d % f.perRow) * cw,
                            f.base.y + (float)(d / f.perRow) * f.base.h, cw, f.base.h};
        out[n].x = cx;
        out[n].y = y;
        out[n].scale = scale;
        if (v < 10) {
            ++n;
            break;
        }
        v /= 10;
        cx -= (cw + f.leading) * scale;
    }
    return n;
}

// The uploaded battle sheets plus the draw calls the HUD composer uses. Upload is
// all-or-nothing: a frame that mixes one sheet's art with another's absence is
// worse than the text HUD, which stays the fallback (see HudComposer::compose).
class HudAtlas {
public:
    // Resolves and uploads every sheet through assetSource() (bundle-first, the
    // exe's own order), decoding each .cnv with xm::decodeCnvImage — the foundation's
    // one CNV decoder (assets/cnv.h), not a second one. `error` carries the failing
    // sheet and reason; the caller logs it once and falls back.
    bool upload(SpriteRenderer& batch, std::string& error);
    // A source rect the sprite table does not name: FUN_00655830 picks the fan's cells by mode.
    bool drawRect(SpriteRenderer& batch, HudSheet sheet, const UiRect& src, float x, float y) const;
    bool fillRect(SpriteRenderer& batch, HudSheet sheet, const UiRect& src, float frac, float x, float y) const;

    // False until every sheet is up; the composer reads it as "draw the art HUD".
    bool ready() const {
        for (int s : sheets_)
            if (s < 0) return false;
        return true;
    }
    int  sheet(HudSheet s) const { return sheets_[(int)s]; }

    // FUN_00655d60 at the sprite's pivot-anchored position, `scale` = FUN_00408250
    // and `rotDeg` = FUN_006451f0 (the ring is the only HUD sprite that rotates).
    bool draw(SpriteRenderer& batch, HudIcon icon, float x, float y, float scale = 1.f,
              float rotDeg = 0.f, UiColor tint = {}) const;
    // FUN_00645250: the same anchor, `frac` of the rect drawn, growing right (the
    // only mode the HUD's bars and the fan gauge use; the modes exist in sprite.h).
    bool fill(SpriteRenderer& batch, HudIcon icon, float frac, float x, float y,
              FillMode mode = FillMode::Right, UiColor tint = {}) const;
    // FUN_00655830: one cell of a cell-rect sprite. The cell pitch FUN_006556c0 stores
    // is the sprite's own rect (srcW/texW), so cell (cx, cy) is the atlas rect offset
    // by (cx*src.w, cy*src.h) — that is why P03's ring rows are 128 px apart and the
    // tag rows 32.
    bool cell(SpriteRenderer& batch, HudIcon icon, int cellX, int cellY, float x, float y,
              float scale = 1.f, float rotDeg = 0.f, UiColor tint = {}) const;
    // FUN_00431b20: `value`'s digits, right-aligned at (x, y).
    bool number(SpriteRenderer& batch, HudFont font, int value, float x, float y,
                float scale = 1.f, UiColor tint = {}) const;
    // FUN_00431ce0: one font cell at `x + scale*leading` (the leading is why the
    // readout's '%' sits four pixels left of its anchor at scale 1).
    bool glyph(SpriteRenderer& batch, HudFont font, int cellX, int cellY, float x, float y,
               float scale = 1.f, UiColor tint = {}) const;

private:
    int sheets_[(int)HudSheet::Count] = {-1, -1, -1, -1, -1, -1};
};

}  // namespace ui
