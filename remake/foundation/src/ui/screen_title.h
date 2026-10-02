#pragma once
// Scene 1 — the title menu. Assets, geometry and the cursor machine as the RE reads
// them (FRONTEND-PLAN.md §2.1), which is all atlas art: the six labels are pixels in
// data/title/title.cnv, and the plan's §3 is explicit that the exe contains no menu
// label strings and creates no font in scene 1, so there is no text path here.
//
// Evidence, per element:
//   * assets and their sub-rects — FUN_00410d60.c:28-36 (data/title/back00.bmp,
//     logo.bmp, title.bmp; FUN_00655af0/FUN_00655b20/FUN_006556c0 configure them);
//   * draw order and anchors — FUN_004114f0.c:17-22 (background at (0,0), logo at
//     (400,-20), then six cells at x=400 from y=285 with a 48-px stride);
//   * cursor and confirm — FUN_00410f60.c:101-148 (selection at +0x1f0, six items,
//     (i+1)%6 down / (i+5)%6 up, item → scene id at :106-134).
#include <cstdint>
#include <memory>
#include <string>

#include "ui/screen.h"

namespace ui {

// The three sheets FUN_00410d60.c:28-33 loads. `stem` is the path the exe asks for with
// the .bmp extension dropped; uploadCnvSheet() probes the .cnv the archives ship first.
enum class TitleSheet : uint8_t { Back = 0, Logo, Items, Count };

struct TitleAsset {
    TitleSheet  sheet;
    const char* stem;
};
inline constexpr TitleAsset kTitleAssets[] = {
    {TitleSheet::Back, "data/title/back00"},   // 800x600. FUN_00410d60.c:28-29
    {TitleSheet::Logo, "data/title/logo"},     // 512x300 used of 512x512. :30-31
    {TitleSheet::Items, "data/title/title"},   // 2 columns x 6 rows of 192x48. :32-33
};
inline constexpr int kTitleSheetCount = (int)TitleSheet::Count;
static_assert(sizeof(kTitleAssets) / sizeof(kTitleAssets[0]) == (size_t)kTitleSheetCount,
              "asset table and TitleSheet must stay in step");

// FUN_00410d60.c:34-36 configures the three sprites:
//   back  FUN_00655af0(spr,0,0,800,600)          -> rect (0,0,800,600), pivot (0,0)
//   logo  FUN_00655b20(spr,0,0,0x200,300,0x100,0) -> rect (0,0,512,300), pivot (256,0)
//   items FUN_006556c0(spr,0,0,0xc0,0x30,0x60,0)  -> cell (192,48), pivot (96,0)
// (FUN_00655b20.c:11-15 and FUN_006556c0.c:11-15 store params 5/6 as the quad size and
// 7/8 as the pivot; FUN_00655d60.c:15-16 subtracts pivot*scale from the draw position.)
// FUN_004114f0.c:17-22 then draws: back at (0,0), logo at (400,-20), and each item cell
// at x = 400 with its top edge at i*48 + 285 (the 0x43c80000 / 0xc1a00000 literals).
inline constexpr UiRect kTitleBackSrc{0.f, 0.f, 800.f, 600.f};
inline constexpr UiRect kTitleLogoSrc{0.f, 0.f, 512.f, 300.f};
inline constexpr UiRect kTitleItemSrc{0.f, 0.f, 192.f, 48.f};
inline constexpr float  kTitleLogoPivotX = 256.f, kTitleLogoPivotY = 0.f;
inline constexpr float  kTitleItemPivotX = 96.f, kTitleItemPivotY = 0.f;
inline constexpr float  kTitleLogoX = 400.f, kTitleLogoY = -20.f;
inline constexpr float  kTitleItemX = 400.f, kTitleItemY0 = 285.f, kTitleItemStride = 48.f;

// The six items in the atlas' own row order, which is the order the print shows and the
// one the transition table proves (FRONTEND-PLAN.md §1.2). `next` is the scene id
// FUN_00410f60.c:106-134 returns for that row; `label` is a romanisation for logs only —
// the on-screen label is the atlas' pixels, never a string.
enum class TitleItem : int { Story = 0, Versus, Netplay, Options, KeyConfig, Quit, Count };

struct TitleEntry {
    const char* label;
    ScreenId    next;
};
inline constexpr int kTitleItemCount = 6;
inline constexpr TitleEntry kTitleEntries[kTitleItemCount] = {
    {"story", ScreenId::Prologue},         // row 0. FUN_00410f60.c:107-111 (-> 4)
    {"versus", ScreenId::Select},          // row 1. :112-115 (-> 3)
    {"netplay", ScreenId::NetplayMenu},    // row 2. :116-119 (-> 0x0b)
    {"options", ScreenId::Options},        // row 3. :120-122 (-> 6)
    {"keyconfig", ScreenId::KeyConfig},    // row 4. :123-125 (-> 7)
    {"quit", ScreenId::Quit},              // row 5. :126-131 (-> 0x16: no scene, quit)
};
static_assert(sizeof(kTitleEntries) / sizeof(kTitleEntries[0]) == (size_t)kTitleItemCount,
              "entry table and TitleItem must stay in step");

// What one update did, so the caller can play the SE the original plays there (FUN_
// 0064aed0: 0 on confirm, 2 on a cursor move) without the state machine needing an audio
// seam. Audio is not wired on this screen yet; the screen logs the transition instead of
// faking it.
enum class TitleAction : uint8_t { None, Moved, Activated };

// FUN_00410f60.c:138-145's cursor machine, device-free. The original's vertical counter
// (+0x1f8) acts only on the frame it reads exactly +1 or -1, so one press moves exactly
// one item however long it is held — the edges ScreenInput carries.
class TitleMenu {
public:
    TitleAction update(const ScreenInput& in);
    int         selected() const { return selected_; }

private:
    int selected_ = 0;   // FUN_00410d60.c:37: param_1[0x7c] (= +0x1f0) starts at 0
};

// The screen itself: the three uploaded sheets plus the cursor machine. The constructor
// is FUN_00410d60 (object 0x208 bytes, scene 1 of FUN_004020a0's switch); a load failure
// leaves the screen unusable and is reported once through `error`.
class TitleScreen : public Screen {
public:
    TitleScreen(SpriteRenderer& batch, std::string& error);

    ScreenId    update(const ScreenInput& in) override;
    void        draw(SpriteRenderer& batch) const override;
    const char* name() const override { return "title"; }

    // False when one of the three sheets did not resolve, decode or upload. A title
    // without its menu would draw a bare background, so makeTitleScreen() refuses to
    // hand one out rather than presenting a screen the port cannot account for.
    bool loaded() const;

private:
    int       sheets_[kTitleSheetCount] = {-1, -1, -1};
    TitleMenu menu_;
};

// makeScreen(ScreenId::Title)'s constructor. Null (with `error`) when one of the three
// assets is in no bundle, decodes badly, or cannot be uploaded.
std::unique_ptr<Screen> makeTitleScreen(SpriteRenderer& batch, std::string& error);

}  // namespace ui
