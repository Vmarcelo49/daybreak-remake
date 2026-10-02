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
//     pivot per FUN_00655b20 call) and the number fonts.
//   * FUN_00642a00 @0x00642a00 creates the per-player bar/fill slots at
//     hud+0x2b4+i*0xac; FUN_00642c50 @0x00642c50 re-points the fill slots and
//     overwrites slots 4..6 with the fan-gauge gradient cells.
//   * FUN_00644150 @0x00644150 draws them: (505,565) HP, (55,488) fan, (623,471)
//     MAIN, (597,517) CHARGE, (702,443) and (676,489) the two counts.
//   * FUN_00655b20 @0x00655b20 is the sprite ABI (rect + pivot), FUN_00655d60
//     @0x00655d60 the draw, FUN_00645250 @0x00645250 the clipped gauge fill,
//     FUN_00431a50/00431b20 the number font and its draw.
//
// Bytes come from fnd::assets::assetSource() and never from a filesystem path: the
// exe resolves data/object/*.bmp through its bundle list in daybreak00..07 order
// (FUN_00653540 @0x00653540 walks it, FUN_00662f70 probes a name, first match wins;
// FUN_006560c0 @0x006560c0 is the loader that maps .bmp to the shipped .cnv), and
// P01.cnv is a live case where that order decides the pixels — daybreak00.dat ships
// sha1 6830e6ee (fan captions baked into the fan sprite, which is what the reference
// print shows) and daybreak04.dat ships 6ebc4967 (captions split out, captions
// renamed). asset_source.cpp already implements the order, so this file only asks it.
#include <cstdint>
#include <string>

#include "ui/sprite.h"

namespace ui {

// The shipped HUD sheets, named as FUN_00642510 asks for them (P00.bmp -> P00.cnv).
// P03 (command labels/brackets) and P06 (alert balloons) belong to elements the
// spec's priority order puts after this track's; they are not loaded until an
// element samples them, because an unread texture is a megabyte of dead upload.
enum class HudSheet : uint8_t { P00 = 0, P01, P02, Count };

// The sprites the implemented elements draw. The name after the comment is the
// exe's own static sprite (or slot) the numbers were read from.
enum class HudIcon : uint8_t {
    HpFrame,             // 0x6c7f60  P01 (32,192,256,64)  pivot (13,25)
    MainFrame,           // 0x6ca6e0  P01 (64,128,192,64)  pivot (16,29)
    ChargeFrame,         // 0x6ca780  P01 (64,64,192,64)   pivot (16,27)
    FanFrame,            // 0x6c7cb8  P01 (0,256,300,128)  pivot (45,21)
    MaxLabel,            // 0x6c7b78  P00 (384,384,128,128) pivot (64,64)
    HpFill,              // hud+0x2b4 P02 (0,480,230,14)   normal HP ramp
    MainFill,            // hud+0x768 P01 (320,128,160,6)  blue, count > 0
    MainFillEmpty,       // hud+0x8c0 P01 (320,144,160,6)  grey, count == 0
    ChargeFill,          // hud+0x814 P01 (320,64,160,6)   teal, count > 0
    ChargeFillEmpty,     // hud+0x96c P01 (320,80,160,6)   grey, count == 0
    ChargeTierYellow,    // hud+0xa18 P01 (320,96,160,5)   C-held tier meter, low
    ChargeTierRed,       // hud+0xac4 P01 (320,112,160,5)  C-held tier meter, high
    FanFillCharging,     // hud+0x564 P02 (0,0,230,91)     team 0, gauge filling
    FanFillReady,        // hud+0x610 P02 (0,288,230,91)   team 0, gauge charged
    Count,
};

// One entry of the original's sprite table: the atlas sub-rect (FUN_00655b20's
// params 2..5) and the pivot (its params 6..7).
struct HudSprite {
    HudSheet sheet = HudSheet::P00;
    UiRect   src{};              // atlas pixels
    float    pivotX = 0.f, pivotY = 0.f;
};

// FUN_00642510's static sprites, then FUN_00642a00's slots in slot order and
// FUN_00642c50's fan-gauge overwrite of slots 4..6 — transcribed in the order of
// the HudIcon enum, which the static_assert below pins. Data only (no device, no
// asset), so the table is constexpr and a host test can check it directly.
inline constexpr HudSprite kHudSprites[] = {
    /* HpFrame          */ {HudSheet::P01, {32.f, 192.f, 256.f, 64.f}, 13.f, 25.f},
    /* MainFrame        */ {HudSheet::P01, {64.f, 128.f, 192.f, 64.f}, 16.f, 29.f},
    /* ChargeFrame      */ {HudSheet::P01, {64.f, 64.f, 192.f, 64.f}, 16.f, 27.f},
    /* FanFrame         */ {HudSheet::P01, {0.f, 256.f, 300.f, 128.f}, 45.f, 21.f},
    /* MaxLabel         */ {HudSheet::P00, {384.f, 384.f, 128.f, 128.f}, 64.f, 64.f},
    /* HpFill           */ {HudSheet::P02, {0.f, 480.f, 230.f, 14.f}, 0.f, 0.f},
    /* MainFill         */ {HudSheet::P01, {320.f, 128.f, 160.f, 6.f}, 0.f, 0.f},
    /* MainFillEmpty    */ {HudSheet::P01, {320.f, 144.f, 160.f, 6.f}, 0.f, 0.f},
    /* ChargeFill       */ {HudSheet::P01, {320.f, 64.f, 160.f, 6.f}, 0.f, 0.f},
    /* ChargeFillEmpty  */ {HudSheet::P01, {320.f, 80.f, 160.f, 6.f}, 0.f, 0.f},
    /* ChargeTierYellow */ {HudSheet::P01, {320.f, 96.f, 160.f, 5.f}, 0.f, 0.f},
    /* ChargeTierRed    */ {HudSheet::P01, {320.f, 112.f, 160.f, 5.f}, 0.f, 0.f},
    // FUN_00642c50's team-0 cells: (0,0) while the gauge fills, (0,288)/(0,384) as
    // the two charged colours. The composer draws the first of the charged pair; the
    // original alternates them on (frame % 0x1e) / 0xf and owns a clock this layer
    // deliberately does not (see HudComposer::composeBattle).
    /* FanFillCharging  */ {HudSheet::P02, {0.f, 0.f, 230.f, 91.f}, 0.f, 0.f},
    /* FanFillReady     */ {HudSheet::P02, {0.f, 288.f, 230.f, 91.f}, 0.f, 0.f},
};
static_assert(sizeof(kHudSprites) / sizeof(kHudSprites[0]) == (size_t)HudIcon::Count,
              "sprite table and HudIcon must stay in step");

inline const HudSprite& hudSprite(HudIcon icon) { return kHudSprites[(size_t)icon]; }

// The number font FUN_00642510 builds at 0x6c8000 for the MAIN/CHARGE counts:
// FUN_00431a50(P00 texture, 0, 0, 0x40, 0x40, 8, -27.0) creates 12 cells of 64x64
// from (0,0) — row 0 is digits 0..7, row 1 is 8, 9, '%', '/' — with a -27 px
// leading, i.e. a 37 px advance. FUN_00431b50 draws the digits least-significant
// first at `x - cellW`, stepping left, so the run's right edge lands on the anchor.
inline constexpr float kHudDigitCell = 64.f;
inline constexpr float kHudDigitAdvance = 37.f;   // 64 + (-27)

// One digit of a right-aligned run: the P00 cell and where its top-left goes.
struct HudDigit {
    UiRect src;
    float  x = 0.f, y = 0.f;
};

// Lays `value` out right-aligned at (x, y) into `out` (at least 10 entries) and
// returns how many were written. Pure arithmetic over the font's own constants, so
// the number layout is unit-testable without a device. Negative values keep the
// sign handling of the original's `local_9` out of scope: every HUD number is a
// count or a gauge.
inline int hudDigitRun(int value, float x, float y, HudDigit* out) {
    // FUN_00431a50's 8-column grid: digit d lives in cell (d%8, d/8) of the 64x64
    // cells laid out from P00 (0,0), so 0..7 are row 0 and 8, 9 are row 1.
    int v = value < 0 ? -value : value;
    float cx = x - kHudDigitCell;   // FUN_00431b50's `x - scale*cellW`
    int n = 0;
    for (; n < 10; ++n) {
        const int d = v % 10;
        out[n].src = UiRect{(float)((d % 8) * (int)kHudDigitCell),
                            (float)((d / 8) * (int)kHudDigitCell), kHudDigitCell, kHudDigitCell};
        out[n].x = cx;
        out[n].y = y;
        if (v < 10) {
            ++n;
            break;
        }
        v /= 10;
        cx -= kHudDigitAdvance;
    }
    return n;
}

// The uploaded battle sheets plus the draw calls the HUD composer uses. Upload is
// all-or-nothing: a frame that mixes one sheet's art with another's absence is
// worse than the text HUD, which stays the fallback (see HudComposer::compose).
class HudAtlas {
public:
    // Resolves and uploads P00/P01/P02 through assetSource() (bundle-first, the
    // exe's own order), decoding each .cnv with xm::decodeCnvImage — the foundation's
    // one CNV decoder (assets/cnv.h), not a second one. `error` carries the failing
    // sheet and reason; the caller logs it once and falls back.
    bool upload(SpriteRenderer& batch, std::string& error);

    // False until every sheet is up; the composer reads it as "draw the art HUD".
    bool ready() const {
        for (int s : sheets_)
            if (s < 0) return false;
        return true;
    }
    int  sheet(HudSheet s) const { return sheets_[(int)s]; }

    // FUN_00655d60 at the sprite's pivot-anchored position.
    bool draw(SpriteRenderer& batch, HudIcon icon, float x, float y,
              UiColor tint = UiColor{}) const;
    // FUN_00645250: the same anchor, `frac` of the rect drawn, growing right (the
    // only mode the HUD's bars and the fan gauge use; the modes exist in sprite.h).
    bool fill(SpriteRenderer& batch, HudIcon icon, float frac, float x, float y,
              FillMode mode = FillMode::Right, UiColor tint = UiColor{}) const;
    // FUN_00431b20: `value`'s digits, right-aligned at (x, y).
    bool number(SpriteRenderer& batch, int value, float x, float y,
                UiColor tint = UiColor{}) const;

private:
    int sheets_[(int)HudSheet::Count] = {-1, -1, -1};
};

}  // namespace ui
