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
    std::puts("hud_layout_test: adaptive anchors and projection ok");
}
