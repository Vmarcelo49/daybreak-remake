#pragma once
// The pre-round countdown (issue #47) — the screen the VS intro hands over to
// (screen_vs.cpp:59 returns ScreenId::Battle, which the app's factory turns into this).
//
// The original's phase is NOT a black screen: FUN_00634760 @0x634760 sets the round phase
// and FUN_00635d40:62-83 hands over to the fight after three frames while arming each
// view's centre sting for 0x3c = 60 frames at scale 6.0 shrinking to 1.0 — the arena is
// the live scene while the digit animates over it. The app therefore builds the match when
// the VS intro ends (the Battle screen's factory runs enterFrontendBattle -> initScene ->
// initMatch), renders the battle scene under this screen and holds combat/input until
// `ready` turns true. Fighters fall and animate during this phase. This screen draws
// NO background quad of its own: it is an overlay,
// composited by ui::drawScreenOverlay over the scene pass.
//
// TIMING (issue #13, kept by issue #47): the code that walks the three P09 digits is not
// in the corpus, so the port keeps its documented three-second countdown — three cells,
// one per `tickRate` — a PORT RULE, not recovered behaviour. Issue #47 changes the phase's
// background and its relationship to the match, not the duration.
//
// Art: P09's three cells (0,0,192,256), (192,0,192,256) and (384,0,128,256), registered by
// FUN_00633ca0 @0x633ca0 with pivots (96,128), (96,128) and (64,128), drawn at the frame
// centre. The roster captions under the digit are the port's own (issue #13): the round's
// settings and every participant, never a bare fighter (AGENTS.md rule 7).
#include <memory>
#include <string>
#include <vector>

#include "ui/screen.h"
#include "ui/text.h"

namespace ui {

// The countdown's own clock. `done()` gates combat and player actions; the entrance
// descent runs before it, without advancing the round clock.
class CountdownClock {
public:
    explicit CountdownClock(int tickRate) : tickRate_(tickRate > 0 ? tickRate : 1) {}
    void tick() { ++frame_; }
    int frame() const { return frame_; }
    int tickRate() const { return tickRate_; }
    int frames() const { return 3 * tickRate_; }
    bool done() const { return frame_ >= frames(); }
    // The P09 digit cell drawn this frame: 0 = "3", 1 = "2", 2 = "1". Clamped, so a frame
    // past the end names the last cell instead of reading past the sheet.
    int cell() const {
        return frame_ < tickRate_ ? 0 : (frame_ < 2 * tickRate_ ? 1 : 2);
    }

private:
    int frame_ = 0;
    int tickRate_ = 60;
};

// One line of the battle state shown under the digit (issue #13): the round's settings,
// then one line per participant. `blue` is the team colour the line draws in
// (ui::kHudLimitLeft for side 0, ui::kHudLimitRight for side 1).
struct CountdownLine {
    std::string text;
    bool        blue = true;
};

struct CountdownInfo {
    int                        tickRate = 60;
    std::string                settings;   // e.g. "TIME 60s   BALLOON 40% / 40%"
    std::vector<CountdownLine> roster;     // one entry per participant, in panel order
};

// The screen itself. Public (unlike the other screens' classes) because the host test
// drives the REAL screen: with no device the P09 sheet cannot upload, so the factory below
// refuses it, and a test that could only see a stand-in could not assert what this screen
// pushes. tests/countdown_overlay_test.cpp is that caller.
class CountdownScreen final : public Screen {
public:
    CountdownScreen(SpriteRenderer& batch, const CountdownInfo& info, bool& ready,
                    std::string& error);
    // False when the digit sheet did not upload. The captions are independent of it (a
    // missing font only drops the text), which is why the factory's refusal keys on the
    // sheet alone — the same rule this screen had before it moved out of main.cpp.
    bool loaded() const { return sheet_ >= 0; }
    ScreenId update(const ScreenInput&) override;
    const char* name() const override { return "countdown"; }
    void draw(SpriteRenderer& batch) const override;
    // The clock the gate reads. Exposed for the same reason as the class.
    const CountdownClock& clock() const { return clock_; }

private:
    CountdownClock             clock_;
    bool&                      ready_;
    std::vector<CountdownLine> roster_;
    std::vector<TextLayout>    rosterLayout_;
    int                        sheet_ = -1;
    TextLayer                  text_;
    TextLayout                 settingsLayout_;
    mutable int                bitmapSlot_ = -1;
    int                        textSlot_ = -1;
};

// Fails (returning null; `error` names the missing asset) when the digit sheet cannot be
// uploaded, exactly as the other screen factories do. Sets `ready` when the clock ends.
std::unique_ptr<Screen> makeCountdownScreen(SpriteRenderer& batch, const CountdownInfo& info,
                                            bool& ready, std::string& error);

}  // namespace ui
