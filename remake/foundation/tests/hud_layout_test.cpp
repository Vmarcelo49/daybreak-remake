#include "ui/hud.h"
#include "game/hud_bridge.h"
#include <cmath>
#include <cstdio>

#define CHECK(x) do { if (!(x)) { std::fprintf(stderr,"line %d: %s\n",__LINE__,#x); return 1; } } while (0)
bool near(float a, float b) { return std::abs(a-b) < .002f; }
int main() {
    const auto original = ui::computeBattleHudLayout(800,600);
    CHECK(near(original.hp.x,505) && near(original.hp.y,565));
    CHECK(near(original.main.x,623) && near(original.charge.x,597));
    CHECK(near(original.stamina.x,400) && near(original.stamina.y,517));
    CHECK(near(original.ko.x,400) && near(original.ko.y,300));
    for (const auto size : {ui::UiViewport{800,600}, {1920,1080}, {3440,1440},
                            {1080,1920}, {1373,777}, {640,480}}) {
        const auto layout = ui::computeBattleHudLayout(size.w,size.h);
        CHECK(near(layout.width*layout.scale,size.w));
        CHECK(near(layout.height*layout.scale,size.h));
        CHECK(near(layout.width-layout.hp.x,295));
        CHECK(near(layout.height-layout.hp.y,35));
        CHECK(near(layout.ko.x*layout.scale,size.w*.5f));
        CHECK(near(layout.ko.y*layout.scale,size.h*.5f));
        CHECK(near(layout.fps.x*layout.scale,size.w));
        CHECK(layout.hp.x > layout.stamina.x && layout.fan.x < layout.stamina.x);
        float x = 0, y = 0;
        ui::hudProjectClip(0,0,x,y,layout.width,layout.height);
        CHECK(near(x*layout.scale,size.w*.5f) && near(y*layout.scale,size.h*.5f));
        ui::hudProjectClip(1,-1,x,y,layout.width,layout.height);
        CHECK(near(x*layout.scale,size.w) && near(y*layout.scale,size.h));
        const float identity[16] = {1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1};
        CHECK(game::projectHudPoint(identity,.25f,-.5f,0,x,y,layout.width,layout.height));
        CHECK(near(x*layout.scale,size.w*.625f) && near(y*layout.scale,size.h*.75f));
    }
    const auto invalid = ui::computeBattleHudLayout(0,0);
    CHECK(invalid.scale == 1 && invalid.width == 800 && invalid.height == 600);

    // Split-screen views (issue #12): the same anchor rules applied inside each view's own
    // cell, which is where FUN_0063a130 draws a view's HUD — at the cell's origin and, for
    // more than one view, at the 0.5 scale its :49-51 selects. The layout is view-LOCAL: a
    // cell's anchors depend on its size, never on where the cell sits on the target.
    for (const auto cell : {ui::UiViewport{400,300},   // 800x600 four-cell (the original's)
                            ui::UiViewport{960,540},   // 1920x1080 four-cell
                            ui::UiViewport{1720,720},  // 3440x1440 four-cell (ultrawide)
                            ui::UiViewport{540,960},   // 1080x1920 four-cell (portrait)
                            ui::UiViewport{686,388}}) {
        const auto layout = ui::computeBattleHudLayout(cell.w,cell.h);
        CHECK(near(layout.width*layout.scale,cell.w));
        CHECK(near(layout.height*layout.scale,cell.h));
        CHECK(layout.width >= 800.f - .001f || cell.w < 800.f);
        CHECK(layout.height >= 600.f - .001f || cell.h < 600.f);
        // Every anchor the composer uses must land inside the view it draws into.
        for (const auto& anchor : {layout.hp, layout.fan, layout.maxLabel, layout.fanCaption,
                                   layout.stamina, layout.command, layout.main, layout.charge,
                                   layout.mainCount, layout.chargeCount, layout.ko}) {
            CHECK(anchor.x >= 0.f && anchor.x <= layout.width + .001f);
            CHECK(anchor.y >= 0.f && anchor.y <= layout.height + .001f);
        }
        // Centre anchors are the centre OF THE VIEW (the KO sting and the marker origin).
        CHECK(near(layout.ko.x*layout.scale,cell.w*.5f));
        CHECK(near(layout.ko.y*layout.scale,cell.h*.5f));
        // Edge anchors stay on the view's own edges, which is what keeps a split-screen
        // HUD from drifting into a neighbour's cell.
        CHECK(near(layout.hp.x*layout.scale,cell.w - 295.f*layout.scale));
        CHECK(near(layout.hp.y*layout.scale,cell.h - 35.f*layout.scale));
        CHECK(near(layout.fps.x*layout.scale,float(cell.w)));
    }
    // The original's own split-screen scale: a 400x300 view is exactly half of 800x600
    // (FUN_006396f0's quadrant cells + FUN_0063a130's local_8 = 0.5).
    const auto quadrant = ui::computeBattleHudLayout(400,300);
    CHECK(quadrant.scale == .5f && quadrant.width == 800.f && quadrant.height == 600.f);
    // A view's anchors do not depend on its origin on the target.
    const auto cellA = ui::computeBattleHudLayout(960,540);
    const auto cellB = ui::computeBattleHudLayout(960,540);
    CHECK(near(cellA.hp.x,cellB.hp.x) && near(cellA.ko.y,cellB.ko.y));

    // Issue #13: every active participant keeps a marker on screen. The off-screen alert
    // edge is a port rule (the original's marker art and its four positions are recovered,
    // 0x643722-0x6437d0, but not the rule that picks one): the nearest edge of the logical
    // view, and the bottom edge for a fighter behind the eye.
    {
        ui::HudFighterHud fighter;
        fighter.visible = true;
        fighter.ringX = 400.f; fighter.ringY = 300.f;
        CHECK(ui::hudAlertDirection(fighter,800.f,600.f) == -1);
        fighter.ringX = -20.f;
        CHECK(ui::hudAlertDirection(fighter,800.f,600.f) == 2);
        fighter.ringX = 900.f;
        CHECK(ui::hudAlertDirection(fighter,800.f,600.f) == 3);
        fighter.ringX = 400.f; fighter.ringY = -40.f;
        CHECK(ui::hudAlertDirection(fighter,800.f,600.f) == 0);
        fighter.ringY = 700.f;
        CHECK(ui::hudAlertDirection(fighter,800.f,600.f) == 1);
        fighter.visible = false;
        fighter.ringX = 400.f; fighter.ringY = 300.f;
        CHECK(ui::hudAlertDirection(fighter,800.f,600.f) == 1);
        // An absent view has no markers at all.
        CHECK(ui::hudAlertDirection(fighter,0.f,0.f) == -1);
    }
    std::puts("hud_layout_test: adaptive anchors and projection ok");
}
