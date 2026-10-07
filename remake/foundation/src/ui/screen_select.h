#pragma once
#include <array>
#include "ui/screen.h"
#include "ui/frontend_state.h"

namespace ui {
// FUN_00409340: controller state differs from the selected panel's stored choices.
enum class SelectPhase { Team = 0, Controller = 1, Character = 2, Weapon = 3, Hypermode = 4, Ready = 8 };
enum class SelectAction { None, Changed, Back, Stage };
inline constexpr int kSelectRosterX[16] = {0,-2,-1,0,1,-1,-1,-2,0,1,2,2,1,0,3,-3};
inline constexpr int kSelectRosterY[16] = {6,4,5,4,5,3,1,2,2,3,4,2,1,0,3,3};
inline constexpr int kSelectRosterOrder[16] = {14,15,13,12,6,11,8,7,9,5,10,3,1,4,2,0};
inline constexpr int kSelectCostumes[16] = {5,5,3,5,5,5,2,4,2,2,3,3,1,2,4,5};

// The select scene's ENTRY reveal (issue #43). FUN_004090a0:24-26 ramps each of the 16 roster
// slots' float at scene+0x3d50+i*4 from 0 to 1 in steps of 0.1 — the same loop also stands in
// FUN_0041bae0:37-40 — and slot i may only start once the scene tick has passed i+5: the
// constructor zeroes the array and the tick (FUN_00408330:0x408c96/0x408eff), so slot i takes
// its first step on tick i+6, the slots start one tick apart, and the last of them settles on
// tick 30.
//
// The draw consumes it at FUN_0040b2b0:96-104 as a PAIR: FUN_0040da60 @0x40da60 (value[i],
// 2.0-value[i]) writes sprite+0x84 and sprite+0x88, and the sprite quad builder FUN_00655830
// @0x65583f-0x6558db reads them as the x and y SCALE of the quad about its pivot:
//     x0 = x - pivotX*sx,  w = srcW*sx,   y0 = y - pivotY*sy,  h = srcH*sy
// (it then subtracts its half-pixel bias _DAT_006a24d0 = 0.5; this port's sprite batch omits
// that bias for every sprite, so the reveal does too). The pair is therefore not an offset: at
// value v the sprite is v times as wide and (2-v) times as tall, and both ends meet at 1.0.
//
// FUN_0040da60 is called on the roster objects at scene+0x150c+i*0xa0, whose `i%02d.bmp`
// textures and 80x128 pivot (40,80) are set in FUN_00408330:0x408be7-0x408c14 from the handles
// at scene+0x4c — the 16 chibi icons of the diamond, which is where this port applies it. The
// draw's own cell argument is issue #44's half (selectChibiCell below); this struct is the
// transform.
struct SelectReveal {
    static constexpr float kStep = .1f;     // 0x3dcccccd, _DAT_006a1984
    static constexpr float kSettled = 1.f;  // 0x3f800000, _DAT_006a16d0
    static constexpr int kStagger = 5;      // slot i waits for tick > i + 5

    // One fixed tick of the scene's per-frame update. `sceneTick` is the scene's own counter
    // (SelectScreen::frames_), incremented before this runs exactly as FUN_004090a0:9 does.
    void tick(int sceneTick) {
        for (int i = 0; i < 16; ++i)
            if (value[(size_t)i] < kSettled && i + kStagger < sceneTick) value[(size_t)i] += kStep;
    }
    float scaleX(int slot) const { return value[(size_t)slot]; }
    float scaleY(int slot) const { return 2.f - value[(size_t)slot]; }
    // The draw's own `bVar1` (FUN_0040b2b0:100): this slot is still mid-reveal. It picks the
    // flashing cell below and is the same test the ramp's guard uses.
    bool revealing(int slot) const { return value[(size_t)slot] < kSettled; }
    std::array<float, 16> value{};
};

// The cell FUN_0040b2b0's roster loop draws a chibi from, as (column, row) of the `i%02d`
// sheet's 80x128 grid, which the idle cycle already proves is 3 wide x 2 tall. Line numbers are
// research/decompiled/FUN_0040b2b0.c (the loop is :96-131; the live original's copy is :97-133)
// unless the live original is named.
//
//   * A slot one of the four panels has selected draws the idle cycle — the original's
//     `iVar8 = (tick % 40) / 10; cell = (iVar8 + 1) % 3, (iVar8 + 1) / 3` at :107-112, i.e.
//     cells (1,0) (2,0) (0,1) (1,1) over 40 ticks — at y + 150. That is a property of the
//     PANEL match, not of the ramp, so a selected slot keeps the cycle while it reveals.
//   * Any other slot draws `(local_2c, bVar1)` from the branch's else (:123-130, the call at
//     :128-129) with `local_2c` = 2 while the value is < 1.0 and 0 after, and `bVar1` the same
//     test: cell (2,1) while revealing, cell (0,0) once settled, at y + 160.
//
// The white is the CELL, not a tint: FUN_00655830 has no colour parameter at all, and its
// param_4/param_5 are this column and row — they only build the quad's UVs
// (`u = col * stepU + baseU`, `v = row * stepV + baseV`; :24-31 in research/decompiled, :21-28
// in the live original). Measured on this install, cell (2,1) of `data/select/i00.cnv` (and
// i01/i07/i15) is 100 % opaque white with mean RGB 255,255,255, where the other five cells are
// the coloured chibi frames.
struct SelectChibiCell {
    int col = 0, row = 0;
};
inline SelectChibiCell selectChibiCell(bool selected, int sceneTick, bool revealing) {
    if (selected) {
        const int cell = (sceneTick % 40) / 10 + 1;
        return SelectChibiCell{cell % 3, cell / 3};
    }
    return revealing ? SelectChibiCell{2, 1} : SelectChibiCell{0, 0};
}

// The scene's entry white flash (issue #44, criterion 2). FUN_0040b2b0's own tail — :466-475 in
// research/decompiled/FUN_0040b2b0.c, :480-489 in the live original — draws a full-screen
// 800x600 quad through FUN_00651860(0, 0, 800.0, 600.0, alpha8 << 24 | 0xffffff) over two tick
// windows of the scene's own counter that meet at the peak:
//
//     tick 25..34:  alpha8 = (tick - 25) * 24 + 15  ->   15, 39, ... 231   (rise, '\x18')
//     tick 35..54:  alpha8 = (55 - tick) * 12 + 15  ->  255, 243, ...  27   (fall, '\f')
//
// so it is drawn on exactly ticks 25..54 (30 ticks), is fully opaque on tick 35 alone, and is
// the RGB the call spells out: `| 0xffffff` is WHITE. It is not the black cross-fade — that
// one is FUN_0040b1f0:23-24's bare `(byte)(scene+0x3c42) << 24`, which the port already has as
// ScreenStack's 25-frame fade, and the issue's candidate globals (DAT_006cfba0 /
// (&DAT_006cfba4)[...]) are the participating human slots, not an alpha (FUN_0040d130:108-111).
//
// The byte casts in the original are exact over these windows (15..255, no wrap), so the
// arithmetic here is the same values without them.
struct SelectFlash {
    static constexpr int kFirst = 25;      // window B opens: 0x18 < tick < 0x23, alpha 15
    static constexpr int kPeak = 35;       // window A opens: 0x22 < tick < 0x37, alpha 255
    static constexpr int kLast = 54;       // 0x37 is the first tick with no quad
    static constexpr int kUpStep = 24;     // window B's '\x18'
    static constexpr int kDownStep = 12;   // window A's '\f'
    static constexpr int kBias = 15;       // the '+ 0xf' both windows carry
    static int alpha8(int tick) {
        if (tick < kFirst || tick > kLast) return 0;
        if (tick < kPeak) return (tick - kFirst) * kUpStep + kBias;
        return (kLast + 1 - tick) * kDownStep + kBias;
    }
    // What the draw pushes: that alpha over the 800x600 canvas, in the call's white.
    static UiColor color(int tick) { return UiColor{1.f, 1.f, 1.f, alpha8(tick) / 255.f}; }
};

// FUN_00655830's quad for a sprite drawn with an independent x/y scale (see SelectReveal).
// spriteDst() in ui/sprite.h is the uniform-scale form the batch's pushSprite uses — the
// FUN_00655d60 path, which FUN_00408250's single value feeds.
inline UiRect scaledSpriteDst(float x, float y, float srcW, float srcH, float pivotX,
                              float pivotY, float scaleX, float scaleY) {
    return UiRect{x - pivotX * scaleX, y - pivotY * scaleY, srcW * scaleX, srcH * scaleY};
}

// The phase-row slide (issue #43). FUN_00409340:589-595 — its own tail, after the phase switch
// — restarts 0x3cc4[controller] at 300.0 (0x43960000) whenever that controller's phase changed
// during the update, then takes 20.0 (_DAT_006a16c4) off it while it is still above 0.0
// (_DAT_006a16c8). FUN_0040b2b0 reads it at 0x40c09f-0x40c0c4 as
//     (1 - 2*(panel < 2)) * 0x3cc4[owner(panel)]
// and adds it to the x of that panel's header and phase rows: a phase change starts the left
// column's rows 300 px to the LEFT of their place and the right column's 300 px to the right,
// and both travel inward in 20 px steps — 280, 260, ... 0 over the 15 ticks after the change.
// The rows keep their own per-row +8 px stagger on top of it.
struct SelectRowSlide {
    static constexpr float kStart = 300.f;  // 0x43960000
    static constexpr float kStep = 20.f;    // _DAT_006a16c4
    std::array<float, 4> offset{};

    // The original's own order: set 300.0 on a change and take the first step in the SAME
    // call, so the change tick already draws at 280.
    void step(int controller, bool phaseChanged) {
        if (phaseChanged) offset[(size_t)controller] = kStart;
        if (offset[(size_t)controller] > 0.f) offset[(size_t)controller] -= kStep;
    }
    float offsetFor(int controller) const { return offset[(size_t)controller]; }
};

// 1.0 - 2*(panel < 2), the sign FUN_0040b2b0:0x40c09f-0x40c0b4 gives the owner's offset by
// the panel's column.
inline float rowSlideOffset(float offset, int panel) { return (panel < 2 ? -1.f : 1.f) * offset; }

class SelectMenu {
public:
    explicit SelectMenu(FrontendState& state) : state_(state) {}
    SelectAction update(const ScreenInput& in, int controller = 0);
    SelectAction updateFrame(const ScreenInput& in, int* sound = nullptr);
    SelectPhase phase(int controller = 0) const { return phase_[controller]; }
    int cursor(int controller = 0) const { return cursor_[controller]; }
    // The character phase's free cursor (FUN_00409340 case 2, +0x3cd8/+0x3ce8), in the
    // roster's own units — the same space as kSelectRosterX[i]*48 and kSelectRosterY[i]*36,
    // which is what the selection radii and the magnet measure against.
    float cursorX(int controller = 0) const { return cursorX_[controller]; }
    float cursorY(int controller = 0) const { return cursorY_[controller]; }
    int panel(int controller = 0) const;
    int owner(int panel) const;
    // Whether this controller's free cursor is off the diamond: the 50-unit outer pass
    // (FUN_00409340:272-286) finds no icon. Off the grid the panel's portrait rolls random
    // characters and a confirm takes the one showing — see updatePanel.
    bool cursorOffGrid(int controller = 0) const;
    // What a panel's PORTRAIT shows. Off the diamond this is the rolling character, which is
    // deliberately NOT the slot's own: the chibi draw animates every character any slot
    // matches (FUN_0040b2b0:106-131 tests the confirmed field), so writing the roll into the
    // slot made all sixteen chibis twitch as it cycled. The roll gets its own field and the
    // slot keeps meaning "the cursor is on this one, or it is confirmed".
    int shown(int panel) const {
        return state_.slots[panel].character >= 0 ? state_.slots[panel].character : rolled_[panel];
    }
    void tick();
    // The phase-row slide of the controller that owns a panel — FUN_0040b2b0 indexes 0x3cc4 by
    // the owner; rowSlideOffset() turns it into the panel's own signed x.
    float rowSlide(int controller = 0) const { return slide_.offsetFor(controller); }
private:
    SelectAction updatePanel(const ScreenInput& in, int controller);
    FrontendState& state_;
    std::array<SelectPhase,4> phase_{};
    std::array<int,4> cursor_{{0,-1,-1,-1}}, cooldown_{};
    std::array<float,4> cursorX_{}, cursorY_{};
    // The off-diamond roll's own display character per panel, in panel order (not controller
    // order): `shown()` falls back to it while the slot has no live pick. See shown().
    //
    // -1, NOT 0: it is "nothing has been rolled here yet", and 0 is a real character (Rena).
    // Value-initialising this to 0 made every empty panel's portrait show Rena from the moment
    // the screen opened, before any cursor moved.
    std::array<int,4> rolled_{{ -1, -1, -1, -1 }};
    SelectRowSlide slide_;
};
class SelectScreen final : public Screen {
public:
    SelectScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
    ScreenId update(const ScreenInput& in) override;
    void draw(SpriteRenderer& batch) const override;
    const char* name() const override { return "select"; }
    bool loaded() const;
    std::string takeVoice() override { std::string voice; voice.swap(voice_); return voice; }
    int takeSound() override { int sound=sound_; sound_=-1; return sound; }
private:
    FrontendState& state_;
    SelectMenu menu_;
    SpriteRenderer& batch_;
    std::unique_ptr<Screen> stage_;
    int shared_[10]{}, portraits_[16]{}, chibi_[16]{}, costumes_[16]{}, weapons_[16]{};
    // FUN_004090a0:24-26 scales the 16 roster icons in as the scene opens; frames_ IS the
    // scene's tick counter (the draw's chibi idle cycle is the original's tick % 40 / 10).
    SelectReveal reveal_;
    unsigned frames_ = 0;
    int sound_ = -1;
    std::string voice_;
};
std::unique_ptr<Screen> makeSelectScreen(SpriteRenderer& batch, FrontendState& state, std::string& error);
}
