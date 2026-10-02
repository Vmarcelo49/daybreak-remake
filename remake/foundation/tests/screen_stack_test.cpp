// =============================================================================
//  screen_stack_test.cpp — host test for the front-end screen stack (ui/screen.h)
//  and the title menu's cursor machine (ui/screen_title.h).
//
//  No WebGPU device, no window, no game data: the stack's factory is injected, so
//  every transition runs against fake screens, and the title's cursor machine is
//  arithmetic over the RE'd constants. Runs anywhere.
//
//    ctest -R screen_stack_test
//
//  What it pins, and why each one is worth pinning:
//    * the fade schedule of FUN_00657c80 (alpha (n*10+5)<<24, pinned at 0xff000000
//      from n = 0x18) — the one thing a mid-transition capture can disagree about;
//    * the transition timeline frame by frame: 25 frames to the swap, 25 back;
//    * the factory's null result meaning "no scene: quit"
//      (FUN_00657c80.c:58 + FUN_00657ef0.c:44-46), which is also how 終了 leaves;
//    * the title's item order and the six scene ids FUN_00410f60.c:106-134 returns
//      (story 4, versus 3, netplay 0x0b, options 6, keyconfig 7, quit 0x16);
//    * the cursor wrap, (i+1)%6 down / (i+5)%6 up, and up's priority over down
//      (FUN_00410f60.c:47-65 tests 0xc8 before 0xd0);
//    * the three draw anchors FUN_00410d60.c:34-36 + FUN_004114f0.c:17-22 produce,
//      through the same spriteDst() the sprite batch uses.
// =============================================================================

#include <cstdio>
#include <memory>
#include <string>
#include <vector>

#include "ui/screen.h"
#include "ui/screen_title.h"
#include "ui/sprite.h"

namespace {

using ui::Screen;
using ui::ScreenId;
using ui::ScreenInput;
using ui::ScreenStack;

int g_checks = 0;
int g_failed = 0;

void checkInt(const char* what, long long want, long long got) {
    ++g_checks;
    if (want == got) {
        std::printf("  [ok]   %s = %lld\n", what, got);
    } else {
        std::printf("  [FAIL] %s: want %lld, got %lld\n", what, want, got);
        ++g_failed;
    }
}

void checkFloat(const char* what, float want, float got) {
    ++g_checks;
    if (want == got) {
        std::printf("  [ok]   %s = %.1f\n", what, (double)got);
    } else {
        std::printf("  [FAIL] %s: want %.1f, got %.1f\n", what, (double)want, (double)got);
        ++g_failed;
    }
}

void checkTrue(const char* what, bool ok) {
    ++g_checks;
    if (ok) {
        std::printf("  [ok]   %s\n", what);
    } else {
        std::printf("  [FAIL] %s\n", what);
        ++g_failed;
    }
}

// A screen that always returns one id: "stay" when that is its own, otherwise it asks
// the stack for a transition on the first frame it is updated.
struct FakeScreen : Screen {
    ScreenId returns;
    explicit FakeScreen(ScreenId r) : returns(r) {}
    ScreenId update(const ScreenInput&) override { return returns; }
    void draw(ui::SpriteRenderer&) const override {}
    const char* name() const override { return "fake"; }
};

// The fade overlay's alpha, as FUN_00657c80.c:16-49 computes it.
void testFadeSchedule() {
    std::printf("fade schedule (FUN_00657c80.c:16-49):\n");
    checkInt("frame 0 -> no overlay", 0, ScreenStack::fadeAlpha8(0));
    checkInt("frame 1 -> (1*10+5)", 15, ScreenStack::fadeAlpha8(1));
    checkInt("frame 2 -> (2*10+5)", 25, ScreenStack::fadeAlpha8(2));
    checkInt("frame 23 -> (23*10+5)", 235, ScreenStack::fadeAlpha8(23));
    // 0x18 is the switch to a pinned 0xff000000, so 24 is 255 and not 245.
    checkInt("frame 24 -> pinned 0xff000000", 255, ScreenStack::fadeAlpha8(24));
    checkInt("frame 25 (the swap frame) -> pinned", 255, ScreenStack::fadeAlpha8(25));
    checkInt("kFadeFrames is 0x19", 0x19, ScreenStack::kFadeFrames);
}

// The whole switcher: request, 25 fade-out frames, the swap, 25 fade-in frames.
void testTransitionTimeline() {
    std::printf("\ntransition timeline:\n");
    std::vector<ScreenId> built;
    auto factory = [&](ScreenId id) -> std::unique_ptr<Screen> {
        built.push_back(id);
        return std::make_unique<FakeScreen>(id == ScreenId::Title ? ScreenId::Select : id);
    };

    ScreenStack stack;
    std::string error;
    checkTrue("begin(Title) with a working factory", stack.begin(ScreenId::Title, factory, error));
    checkInt("factory calls after begin", 1, (long long)built.size());
    checkInt("current after begin", (long long)ScreenId::Title, (long long)stack.current());
    checkInt("no overlay after begin", 0, stack.fadeFrame());

    const ScreenInput nothing;
    for (int frame = 1; frame <= 25; ++frame) {
        stack.update(nothing);
        if (frame < 25) {
            checkInt("fade-out frame alpha index", frame, stack.fadeFrame());
            checkInt("still on the old screen through the fade", (long long)ScreenId::Title,
                     (long long)stack.current());
        }
    }
    checkInt("fade frame after 25 updates", 25, stack.fadeFrame());
    checkInt("factory calls after the swap", 2, (long long)built.size());
    checkInt("factory was asked for Select", (long long)ScreenId::Select, (long long)built[1]);
    checkInt("current after the swap", (long long)ScreenId::Select, (long long)stack.current());

    for (int frame = 1; frame < 25; ++frame) {
        stack.update(nothing);
        checkInt("fade-in frame alpha index", 25 - frame, stack.fadeFrame());
    }
    stack.update(nothing);
    checkInt("overlay gone 25 frames after the swap", 0, stack.fadeFrame());
    checkTrue("still running", !stack.finished());
}

// 終了 returns 0x16, the factory has no such scene, and the main loop reads the null
// scene as quit (FUN_00657c80.c:58, FUN_00657ef0.c:44-46).
void testQuit() {
    std::printf("\nquit path:\n");
    std::vector<ScreenId> built;
    auto factory = [&](ScreenId id) -> std::unique_ptr<Screen> {
        built.push_back(id);
        if (id == ScreenId::Quit) return nullptr;
        return std::make_unique<FakeScreen>(ScreenId::Quit);
    };
    ScreenStack stack;
    std::string error;
    checkTrue("begin(Title)", stack.begin(ScreenId::Title, factory, error));
    checkTrue("not finished yet", !stack.finished());

    const ScreenInput nothing;
    for (int frame = 0; frame < 25; ++frame) stack.update(nothing);
    checkInt("factory calls", 2, (long long)built.size());
    checkInt("factory was asked for Quit", (long long)ScreenId::Quit, (long long)built[1]);
    checkTrue("finished once the factory returned no scene", stack.finished());
    checkInt("current id after quit", (long long)ScreenId::Quit, (long long)stack.current());

    // A failed begin keeps the factory's message and reports itself finished, which is
    // what --screen with an unimplemented id hits.
    ScreenStack other;
    std::string why = "scene 0x03 has no screen yet";
    auto none = [](ScreenId) -> std::unique_ptr<Screen> { return nullptr; };
    checkTrue("begin(Select) fails", !other.begin(ScreenId::Select, none, why));
    checkTrue("the factory's error survives", why == "scene 0x03 has no screen yet");
    checkTrue("a failed begin is finished", other.finished());
}

// FUN_004020a0's table, as the port has it: only the title has a constructor, and an
// id without one is an error — except 0x16, which is the factory's own `default` and
// means "leave" (FUN_00657c80.c:58 + FUN_00657ef0.c:44-46). This is the check that a
// 終了 confirm does not leave a spurious error behind.
void testFactoryTable() {
    std::printf("\nfactory table (FUN_004020a0):\n");
    ui::SpriteRenderer batch;   // no device: only the id table is exercised
    std::string error;
    checkTrue("title is available", ui::screenAvailable(ScreenId::Title));
    checkTrue("select is not built yet", !ui::screenAvailable(ScreenId::Select));
    checkTrue("quit is not a screen", !ui::screenAvailable(ScreenId::Quit));
    checkTrue("makeScreen(Quit) returns no screen", !ui::makeScreen(ScreenId::Quit, batch, error));
    checkTrue("quitting leaves no error behind", error.empty());
    error.clear();
    checkTrue("makeScreen(Select) returns no screen",
              !ui::makeScreen(ScreenId::Select, batch, error));
    checkTrue("an unbuilt id names itself", error == "scene 0x03 has no screen yet");
}

// The six items, in the atlas' row order, and the ids FUN_00410f60.c:106-134 returns.
void testTitleEntries() {
    std::printf("\ntitle items (FUN_00410f60.c:106-134):\n");
    checkInt("six items", 6, ui::kTitleItemCount);
    checkInt("story -> 4", 0x04, (long long)ui::kTitleEntries[0].next);
    checkInt("versus -> 3", 0x03, (long long)ui::kTitleEntries[1].next);
    checkInt("netplay -> 0x0b", 0x0b, (long long)ui::kTitleEntries[2].next);
    checkInt("options -> 6", 0x06, (long long)ui::kTitleEntries[3].next);
    checkInt("keyconfig -> 7", 0x07, (long long)ui::kTitleEntries[4].next);
    checkInt("quit -> 0x16", 0x16, (long long)ui::kTitleEntries[5].next);
    checkInt("item enum order: Story", 0, (long long)ui::TitleItem::Story);
    checkInt("item enum order: Quit", 5, (long long)ui::TitleItem::Quit);
}

void testTitleCursor() {
    std::printf("\ntitle cursor (FUN_00410f60.c:138-145):\n");
    ui::TitleMenu menu;
    checkInt("starts on item 0", 0, menu.selected());

    ScreenInput down;
    down.down = true;
    checkInt("down is a move", (long long)ui::TitleAction::Moved, (long long)menu.update(down));
    checkInt("down -> item 1", 1, menu.selected());

    for (int i = 0; i < 5; ++i) menu.update(down);
    checkInt("five downs from item 1", 0, menu.selected());

    ScreenInput up;
    up.up = true;
    menu.update(up);
    checkInt("up from 0 wraps to 5", 5, menu.selected());
    menu.update(up);
    checkInt("up again -> 4", 4, menu.selected());

    // FUN_00410f60.c:47-65 reads 0xc8 (up) before 0xd0 (down), so up wins.
    ScreenInput both;
    both.up = true;
    both.down = true;
    menu.update(both);
    checkInt("up wins over down", 3, menu.selected());

    ScreenInput confirm;
    confirm.confirm = true;
    const int before = menu.selected();
    checkInt("confirm is an activation", (long long)ui::TitleAction::Activated,
             (long long)menu.update(confirm));
    checkInt("confirm does not move the cursor", before, menu.selected());
    checkInt("nothing with no input", (long long)ui::TitleAction::None,
             (long long)menu.update(ScreenInput{}));
}

// The draw anchors, through the same spriteDst() the batch uses:
//   back  FUN_00655af0(spr,0,0,800,600) -> (0,0) 800x600
//   logo  FUN_00655b20(spr,0,0,0x200,300,0x100,0), drawn at (400,-20)
//   items FUN_006556c0(spr,0,0,0xc0,0x30,0x60,0), drawn at x=400, y=i*48+285
void testDrawAnchors() {
    std::printf("\ntitle draw anchors (FUN_00410d60.c:34-36, FUN_004114f0.c:17-22):\n");
    const ui::UiRect back = ui::spriteDst(0.f, 0.f, ui::kTitleBackSrc.w, ui::kTitleBackSrc.h,
                                         0.f, 0.f);
    checkFloat("back left", 0.f, back.x);
    checkFloat("back top", 0.f, back.y);
    checkFloat("back width", 800.f, back.w);
    checkFloat("back height", 600.f, back.h);

    const ui::UiRect logo = ui::spriteDst(ui::kTitleLogoX, ui::kTitleLogoY, ui::kTitleLogoSrc.w,
                                          ui::kTitleLogoSrc.h, ui::kTitleLogoPivotX,
                                          ui::kTitleLogoPivotY);
    checkFloat("logo left (400 - 256)", 144.f, logo.x);
    checkFloat("logo top", -20.f, logo.y);
    checkFloat("logo width", 512.f, logo.w);
    checkFloat("logo height", 300.f, logo.h);

    const ui::UiRect item0 = ui::spriteDst(ui::kTitleItemX, ui::kTitleItemY0, ui::kTitleItemSrc.w,
                                           ui::kTitleItemSrc.h, ui::kTitleItemPivotX,
                                           ui::kTitleItemPivotY);
    checkFloat("item 0 left (400 - 96)", 304.f, item0.x);
    checkFloat("item 0 top", 285.f, item0.y);
    checkFloat("item cell width", 192.f, item0.w);
    checkFloat("item cell height", 48.f, item0.h);
    const ui::UiRect item5 = ui::spriteDst(ui::kTitleItemX, 5.f * ui::kTitleItemStride +
                                                                 ui::kTitleItemY0,
                                           ui::kTitleItemSrc.w, ui::kTitleItemSrc.h,
                                           ui::kTitleItemPivotX, ui::kTitleItemPivotY);
    checkFloat("item 5 top (5*48+285)", 525.f, item5.y);
    // The selected column is 0 (white) and the other is 1 (dark): FUN_00655830's
    // third argument in FUN_004114f0.c:20 is `selected != i`.
    checkFloat("selected column x", 0.f, ui::kTitleItemSrc.x);
    checkFloat("unselected column x", 192.f, ui::kTitleItemSrc.x + ui::kTitleItemSrc.w);
}

// The CLI contract of --screen.
void testParseScreenId() {
    std::printf("\n--screen parsing:\n");
    ScreenId id = ScreenId::Quit;
    checkTrue("title by name", ui::parseScreenId("title", id) && id == ScreenId::Title);
    checkTrue("1 by decimal", ui::parseScreenId("1", id) && id == ScreenId::Title);
    checkTrue("0x01 by hex", ui::parseScreenId("0x01", id) && id == ScreenId::Title);
    checkTrue("screen:title", ui::parseScreenId("screen:title", id) && id == ScreenId::Title);
    checkTrue("scene-title", ui::parseScreenId("scene-title", id) && id == ScreenId::Title);
    checkTrue("quit by name", ui::parseScreenId("quit", id) && id == ScreenId::Quit);
    checkTrue("0x16 by hex", ui::parseScreenId("0x16", id) && id == ScreenId::Quit);
    checkTrue("netplay by name", ui::parseScreenId("netplay", id) && id == ScreenId::NetplayMenu);
    checkTrue("garbage is rejected", !ui::parseScreenId("titel", id));
    checkTrue("empty is rejected", !ui::parseScreenId("", id));
    checkTrue("a trailing word is rejected", !ui::parseScreenId("1 x", id));
}

}  // namespace

int main() {
    std::printf("front-end screen stack + title menu (device-free)\n\n");
    testFadeSchedule();
    testTransitionTimeline();
    testQuit();
    testFactoryTable();
    testTitleEntries();
    testTitleCursor();
    testDrawAnchors();
    testParseScreenId();
    std::printf("\nchecks: %d, failures: %d\n", g_checks, g_failed);
    std::printf("SCREEN_STACK: %s\n", g_failed == 0 ? "ok" : "FAIL");
    return g_failed == 0 ? 0 : 1;
}
