#include <cstdio>
#define CHECK(x) do { if (!(x)) { std::fprintf(stderr, "failure: %s\n", #x); return 1; } } while (0)
#include "ui/screen_stage_select.h"
#include "ui/screen_vs.h"
int main() {
    ui::FrontendState state;
    ui::StageMenu menu(state);
    ui::ScreenInput down; down.down = true;
    ui::ScreenInput up; up.up = true;
    ui::ScreenInput left; left.left = true;
    ui::ScreenInput right; right.right = true;
    menu.update(down); CHECK(menu.row() == 2);
    menu.update(up); CHECK(menu.row() == 0);
    menu.update(right); CHECK(state.stage == 1);
    menu.update(down); CHECK(menu.row() == 1);
    menu.update(left); CHECK(state.variation == 2);
    menu.update(up); menu.update(right);
    CHECK(state.stage == 2 && state.variation == 1);
    menu.update(down); menu.update(right); CHECK(state.variation == 0);
    menu.update(down);
    // The default is INFINITE, and 0 is how the row spells it. DAT_006cf3c0 lives in .data's
    // bss tail — past the raw data, so the loader zeroes it — and the only write to it anywhere
    // is this menu's own cycle (FUN_0040acb0:53), so the original opens on "no limit". The port
    // shipped 180 (the third of five stops) until that was measured against the binary.
    CHECK(state.timeLimit == 0);
    menu.update(right); CHECK(state.timeLimit == 60);
    menu.update(right); CHECK(state.timeLimit == 120);
    menu.update(right); CHECK(state.timeLimit == 180);
    menu.update(right); CHECK(state.timeLimit == 240);
    menu.update(right); CHECK(state.timeLimit == 0);      // the five stops wrap
    menu.update(left);  CHECK(state.timeLimit == 240);
    menu.update(down); state.health = 50;
    menu.update(left); CHECK(state.health == 200);
    menu.update(right); CHECK(state.health == 50);
    menu.update(down); state.gauge = 200;
    menu.update(right); CHECK(state.gauge == 50);
    menu.update(down); state.blueBalloon = 40;
    menu.update(left); CHECK(state.blueBalloon == 200);
    menu.update(down); state.redBalloon = 200;
    menu.update(right); CHECK(state.redBalloon == 40);
    menu.update(down); ui::ScreenInput confirm; confirm.confirm = true;
    CHECK(menu.update(confirm) == ui::StageAction::Start);
    menu.update(right); CHECK(menu.update(confirm) == ui::StageAction::Back);
    ui::ScreenInput cancel; cancel.cancel = true;
    CHECK(menu.update(cancel) == ui::StageAction::Back);
    ui::VsTimeline timeline;
    for (int i = 0; i < 108; ++i) CHECK(!timeline.update());
    CHECK(timeline.frame() == 108 && timeline.scale() == 1 && timeline.offset(0) == 0);
    CHECK(timeline.update());
    ui::VsTimeline skipped; CHECK(skipped.update(true));
    // Shipped vs.ogg lasts 206720/44100 seconds. The host protects the complete
    // sting at 64 Hz, while the recovered slide/scale still finishes at tick 108.
    ui::VsTimeline withSting(300);
    for (int i = 0; i < 108; ++i) CHECK(!withSting.update());
    CHECK(withSting.scale() == 1 && withSting.offset(0) == 0);
    for (int i = 108; i <= 300; ++i) CHECK(!withSting.update());
    CHECK(withSting.update());
    ui::VsTimeline skippedSting(300); CHECK(skippedSting.update(true));
}
