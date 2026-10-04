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
    menu.update(right); CHECK(state.timeLimit == 240);
    menu.update(right); CHECK(state.timeLimit == 0);
    menu.update(left); CHECK(state.timeLimit == 240);
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
}
