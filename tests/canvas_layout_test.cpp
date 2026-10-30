#include "ui/sprite.h"

#include <cmath>
#include <cstdio>

namespace {
int failures = 0;
void check(bool ok, const char* message) {
    if (!ok) {
        ++failures;
        std::printf("FAIL: %s\n", message);
    }
}
bool near(float a, float b) { return std::fabs(a - b) < .001f; }
void checkFit(uint32_t width, uint32_t height, float scale, float x, float y) {
    const auto fit = ui::fitCanvas({width, height});
    check(near(fit.scale, scale) && near(fit.x, x) && near(fit.y, y), "canvas fit");
    const auto bounds = ui::transformRect({0.f, 0.f, 800.f, 600.f}, fit);
    check(near(bounds.x * 2.f + bounds.w, float(width)), "horizontal centering");
    check(near(bounds.y * 2.f + bounds.h, float(height)), "vertical centering");
    check(near(bounds.w / bounds.h, 4.f / 3.f), "uniform 4:3 scaling");
    check(bounds.x >= 0.f && bounds.y >= 0.f && bounds.x + bounds.w <= width + .001f &&
              bounds.y + bounds.h <= height + .001f, "canvas remains inside viewport");
}
}

int main() {
    checkFit(800, 600, 1.f, 0.f, 0.f);
    checkFit(1920, 1080, 1.8f, 240.f, 0.f);
    checkFit(3440, 1440, 2.4f, 760.f, 0.f);
    checkFit(1080, 1920, 1.35f, 0.f, 555.f);
    checkFit(1373, 777, 1.295f, 168.5f, 0.f);

    ui::UiQuad sprite;
    sprite.dst = {20.f, 30.f, 100.f, 50.f};
    sprite.rotCx = 70.f;
    sprite.rotCy = 55.f;
    sprite.rotDeg = 45.f;
    sprite.uv = {.1f, .2f, .3f, .4f};
    sprite.texture = 5;
    sprite.clip = {true, -10.f, 10.f, 100.f, 80.f};
    const auto fit = ui::fitCanvas({1920, 1080});
    const auto result = ui::transformQuad(sprite, fit, {true, 0.f, 0.f, 800.f, 600.f});
    check(near(result.dst.x, 276.f) && near(result.dst.y, 54.f) &&
              near(result.dst.w, 180.f) && near(result.dst.h, 90.f), "sprite destination scales");
    check(near(result.rotCx, 366.f) && near(result.rotCy, 99.f) && result.rotDeg == 45.f,
          "rotation anchor scales with sprite");
    check(result.uv.x == sprite.uv.x && result.uv.y == sprite.uv.y &&
              result.uv.w == sprite.uv.w && result.uv.h == sprite.uv.h &&
              result.texture == sprite.texture, "source texture coordinates stay unchanged");
    check(result.clip.enabled && near(result.clip.x, 240.f) && near(result.clip.y, 18.f) &&
              near(result.clip.w, 162.f) && near(result.clip.h, 144.f),
          "logical clip intersects canvas and transforms once");
    const auto unclipped = ui::transformQuad(ui::UiQuad{}, fit);
    check(!unclipped.clip.enabled, "battle quads without clips remain unclipped");
    const auto menuClip = ui::transformQuad(ui::UiQuad{}, fit, {true, 0.f, 0.f, 800.f, 600.f});
    check(menuClip.clip.enabled && near(menuClip.clip.x, 240.f) &&
              near(menuClip.clip.w, 1440.f), "unclipped menu quads preserve black bars");
    const auto outside = ui::intersectClip({true, 900.f, 0.f, 100.f, 100.f},
                                          {true, 0.f, 0.f, 800.f, 600.f});
    check(outside.enabled && outside.w == 0.f, "off-canvas animation is clipped away");
    const auto minimized = ui::fitCanvas({0, 0});
    check(minimized.scale == 0.f && minimized.x == 0.f && minimized.y == 0.f,
          "zero viewport avoids division by zero");
    std::printf("CANVAS: %s\n", failures ? "FAIL" : "ok");
    return failures ? 1 : 0;
}
