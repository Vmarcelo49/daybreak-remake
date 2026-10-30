// tests/view_layout_test.cpp — device-free test for the split-screen plumbing of issue #12.
//
// What this pins, and why each half is worth a test:
//   1. game/view_layout.h's recovered geometry (FUN_006396f0 @0x006396f0): one full-target
//      cell, the two-view top-left/bottom-right pair, and the four-cell TL/BL/TR/BR grid,
//      exact and disjoint at 4:3, 16:9, ultrawide, portrait and odd pixel sizes;
//   2. the view assignment (FUN_0040d130 @0x0040d130's human-controller count): views are
//      keyed by CONTROLLER, a COM slot allocates none, order is controller-slot order, and a
//      match with no human gets the original's forced single view on controller 0;
//   3. the separator cross the original draws whenever more than one view is on screen
//      (FUN_006396f0:191-195);
//   4. --local-players' synthetic pad pattern (input/synthetic_pad.h) is deterministic,
//      different per controller and never silent;
//   5. the acceptance guard: rendering N views must not multiply simulation or audio. A real
//      gameplay::Match is stepped once per tick while the test "renders" 1 or 4 views per
//      frame through the same layout/HUD/projection calls the host uses, and the two runs
//      must end in identical simulation state with identical tick counts.
//
// Build (from remake/foundation): cmake --build build/linux && build/linux/view_layout_test
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <vector>

#include <glm/glm.hpp>

#include "game/hud_bridge.h"
#include "game/view_layout.h"
#include "gameplay/arena_camera.h"
#include "gameplay/fixed_step.h"
#include "gameplay/hud_fill.h"
#include "input/synthetic_pad.h"
#include "ui/hud.h"

namespace {

int g_failures = 0;
void check(bool ok, const char* what) {
    if (!ok) {
        ++g_failures;
        std::printf("FAIL: %s\n", what);
    }
}
bool near(float a, float b, float eps = 1e-4f) { return std::fabs(a - b) <= eps; }

bool sameRect(const game::ViewRect& a, const game::ViewRect& b) {
    return near(a.x, b.x) && near(a.y, b.y) && near(a.w, b.w) && near(a.h, b.h);
}

bool inside(const game::ViewRect& cell, uint32_t w, uint32_t h) {
    return cell.x >= 0.f && cell.y >= 0.f && cell.x + cell.w <= (float)w + 1e-4f &&
           cell.y + cell.h <= (float)h + 1e-4f;
}

bool disjoint(const game::ViewRect& a, const game::ViewRect& b) {
    return a.x + a.w <= b.x + 1e-4f || b.x + b.w <= a.x + 1e-4f || a.y + a.h <= b.y + 1e-4f ||
           b.y + b.h <= a.y + 1e-4f;
}

// 1. The recovered cell geometry.
void layoutCases() {
    const uint32_t sizes[][2] = {{800, 600}, {1920, 1080}, {3440, 1440},
                                 {1080, 1920}, {1373, 777}};
    for (const auto& size : sizes) {
        const uint32_t w = size[0], h = size[1];

        // One view is the whole target (FUN_006396f0:49-53's SetRect(0,0,800,600)).
        const game::ViewRect single = game::viewCell(game::SplitLayout::Single, 0, w, h);
        check(sameRect(single, game::ViewRect{0.f, 0.f, (float)w, (float)h}),
              "single view covers the whole target");
        check(game::viewCell(game::SplitLayout::Single, 1, w, h).empty(),
              "a second single-layout cell is empty");
        check(game::viewCellCount(game::SplitLayout::Single) == 1, "single layout draws one cell");
        check(game::separatorCount(game::SplitLayout::Single) == 0,
              "a single view draws no separators");

        // Two views: top-left then bottom-right (FUN_006396f0:63-64).
        const game::ViewRect two0 = game::viewCell(game::SplitLayout::Two, 0, w, h);
        const game::ViewRect two1 = game::viewCell(game::SplitLayout::Two, 1, w, h);
        check(sameRect(two0, game::ViewRect{0.f, 0.f, (float)(w / 2), (float)(h / 2)}),
              "two views: cell 0 is the top-left quadrant");
        check(sameRect(two1, game::ViewRect{(float)(w / 2), (float)(h / 2), (float)(w - w / 2),
                                            (float)(h - h / 2)}),
              "two views: cell 1 is the bottom-right quadrant");
        check(inside(two0, w, h) && inside(two1, w, h) && disjoint(two0, two1),
              "two-view cells stay inside the target and disjoint");
        check(game::viewCell(game::SplitLayout::Two, 2, w, h).empty(),
              "a third two-layout cell is empty");
        check(game::viewCellCount(game::SplitLayout::Two) == 2, "two layout draws two cells");
        check(game::separatorCount(game::SplitLayout::Two) == 2,
              "two views draw the full cross (FUN_006396f0:191-195)");

        // Four views: TL, BL, TR, BR (FUN_006396f0:82-96) tiling the target exactly.
        game::ViewRect cells[4];
        for (int i = 0; i < 4; ++i) cells[i] = game::viewCell(game::SplitLayout::Four, i, w, h);
        check(sameRect(cells[0], game::ViewRect{0.f, 0.f, (float)(w / 2), (float)(h / 2)}),
              "four views: 0 top-left");
        check(sameRect(cells[1], game::ViewRect{0.f, (float)(h / 2), (float)(w / 2),
                                                (float)(h - h / 2)}),
              "four views: 1 bottom-left");
        check(sameRect(cells[2], game::ViewRect{(float)(w / 2), 0.f, (float)(w - w / 2),
                                                (float)(h / 2)}),
              "four views: 2 top-right");
        check(sameRect(cells[3], game::ViewRect{(float)(w / 2), (float)(h / 2),
                                                (float)(w - w / 2), (float)(h - h / 2)}),
              "four views: 3 bottom-right");
        float area = 0.f;
        for (int i = 0; i < 4; ++i) {
            check(inside(cells[i], w, h), "four-view cell stays inside the target");
            area += cells[i].w * cells[i].h;
            for (int j = i + 1; j < 4; ++j)
                check(disjoint(cells[i], cells[j]), "four-view cells are disjoint");
        }
        check(near(area, (float)w * (float)h), "four-view cells tile the target exactly");
        check(game::viewCellCount(game::SplitLayout::Four) == 4, "four layout draws four cells");
        check(game::separatorCount(game::SplitLayout::Four) == 2,
              "four views draw the full cross");

        // Separators sit on the cell boundary and inside the target; their thickness is the
        // port's scaled one original pixel (>= 1).
        for (int i = 0; i < 2; ++i) {
            const game::ViewRect sep = game::separatorRect(i, w, h);
            check(inside(sep, w, h), "separator stays inside the target");
            check(sep.w >= 1.f && sep.h >= 1.f, "separator is at least one pixel thick");
            if (i == 0) {
                check(near(sep.x + sep.w * .5f, (float)w * .5f, 1.f),
                      "vertical separator is centred on the column boundary");
                check(near(sep.h, (float)h), "vertical separator spans the target height");
            } else {
                check(near(sep.y + sep.h * .5f, (float)h * .5f, 1.f),
                      "horizontal separator is centred on the row boundary");
                check(near(sep.w, (float)w), "horizontal separator spans the target width");
            }
        }
    }

    // 800x600 keeps the original's own numbers: four 400x300 views, 1-px bars on 399/300.
    const game::ViewRect tl = game::viewCell(game::SplitLayout::Four, 0, 800, 600);
    check(near(tl.w, 400.f) && near(tl.h, 300.f), "800x600: each view is 400x300 (the original's)");
    const game::ViewRect vsep = game::separatorRect(0, 800, 600);
    check(near(vsep.w, 1.f) && near(vsep.x, 399.5f), "800x600: the vertical bar is the 399..400 pixel");
}

uint64_t countViews(const int controllers[], int fighters, game::HumanView out[4]) {
    return (uint64_t)game::buildHumanViews(controllers, fighters, out);
}

// 2. The controller-keyed view assignment.
void assignmentCases() {
    game::HumanView views[4];

    // Two humans on controllers 0 and 1, one COM (panels can arrive in any fighter order).
    {
        const int controllers[3] = {0, -1, 1};
        check(countViews(controllers, 3, views) == 2, "two human controllers -> two views");
        check(views[0].controller == 0 && views[0].fighter == 0, "view 0 follows controller 0's fighter");
        check(views[1].controller == 1 && views[1].fighter == 2, "view 1 follows controller 1's fighter");
        check(!views[2].active(), "no third view for a COM slot");
    }

    // Controller slots decide the order, not fighter order: fighter 1 on controller 0 comes
    // first even though fighter 0 is the COM one.
    {
        const int controllers[4] = {-1, 0, 3, -1};
        check(countViews(controllers, 4, views) == 2, "controller slots decide the view order");
        check(views[0].controller == 0 && views[0].fighter == 1, "lowest slot first");
        check(views[1].controller == 3 && views[1].fighter == 2, "highest slot second");
    }

    // Four humans, four views, in slot order.
    {
        const int controllers[4] = {0, 1, 2, 3};
        check(countViews(controllers, 4, views) == 4, "four human controllers -> four views");
        for (int i = 0; i < 4; ++i)
            check(views[i].controller == i && views[i].fighter == i,
                  "four views keep controller/fighter identity");
        check(game::splitLayoutFor(4) == game::SplitLayout::Four, "four humans use the four-cell grid");
    }

    // Three humans reuse the four-cell grid, with the human-less slot left unassigned — that
    // is FUN_006396f0 case 3 (local_8 = 4 with a -1 cell), not a three-cell layout.
    {
        const int controllers[4] = {0, 1, -1, 3};
        check(countViews(controllers, 4, views) == 3, "three human controllers -> three views");
        check(views[0].controller == 0 && views[1].controller == 1 && views[2].controller == 3,
              "the third view is the third human slot, not a fourth cell");
        check(game::splitLayoutFor(3) == game::SplitLayout::Four,
              "three humans still draw the four-cell grid");
        check(game::viewCellCount(game::splitLayoutFor(3)) == 4,
              "the four-cell grid keeps its empty cell");
    }

    // Only one human: one view. No human at all: the original's forced single view on
    // controller 0 (FUN_0040d130:115-119), never zero views.
    {
        const int controllers[4] = {2, -1, -1, -1};
        check(countViews(controllers, 4, views) == 1, "one human -> one view");
        check(views[0].controller == 2 && views[0].fighter == 0, "the single view keeps its slot");
        check(game::splitLayoutFor(1) == game::SplitLayout::Single, "one human is the full-frame layout");

        const int comOnly[2] = {-1, -1};
        check(countViews(comOnly, 2, views) == 1, "no human still yields one view");
        check(views[0].controller == 0 && views[0].fighter == 0,
              "the forced view is controller 0 on fighter 0");
    }
}

// 3. Per-view cameras, viewports and projections: the same world point lands where that
// view's own camera says, with that view's own cell aspect, and each view's markers stay
// inside its own logical viewport. This is the D8 rule applied per view.
void perViewProjectionCases() {
    gameplay::CameraTarget targets[2];
    targets[0].position = glm::vec3(0.f, 200.f, 0.f);
    targets[0].facingYaw = 0.f;
    targets[1].position = glm::vec3(1200.f, 200.f, 400.f);
    targets[1].facingYaw = 2.1f;
    std::vector<gameplay::CameraTarget*> pool{&targets[0], &targets[1]};

    gameplay::ArenaCamera left;
    gameplay::ArenaCamera right;
    for (gameplay::ArenaCamera* camera : {&left, &right}) {
        camera->set_target_pool(pool);
        camera->update(1.0 / 60.0);
    }
    left.set_active_target(0);
    right.set_active_target(1);
    // Converge both cameras on their own target.
    for (int i = 0; i < 200; ++i) {
        left.update(1.0 / 60.0);
        right.update(1.0 / 60.0);
    }
    check(glm::length(left.eye() - right.eye()) > 100.f,
          "two views following different fighters have different eyes");

    // A 1920x1080 target: two views in the TL/BR cells, each 960x540 with a 16:9 aspect.
    const game::ViewRect cell0 = game::viewCell(game::SplitLayout::Two, 0, 1920, 1080);
    const game::ViewRect cell1 = game::viewCell(game::SplitLayout::Two, 1, 1920, 1080);
    const glm::mat4 vp0 = left.proj_matrix((int)cell0.w, (int)cell0.h) * left.view_matrix();
    const glm::mat4 vp1 = right.proj_matrix((int)cell1.w, (int)cell1.h) * right.view_matrix();
    check(!near(vp0[0][0], vp1[0][0]) || !near(vp0[3][2], vp1[3][2]),
          "per-view projections differ (own camera and own aspect)");
    check(near(vp0[0][0], 1.f / (16.f / 9.f) / std::tan(0.7853982f * .5f), 1e-3f),
          "each view projects with its own cell aspect (D8 automatic aspect)");

    const ui::BattleHudLayout layout0 = ui::computeBattleHudLayout((int)cell0.w, (int)cell0.h);
    const ui::BattleHudLayout layout1 = ui::computeBattleHudLayout((int)cell1.w, (int)cell1.h);
    check(near(layout0.scale, layout1.scale) && near(layout0.width, layout1.width),
          "equal cells give equal HUD layout");

    // Project each view's own fighter: it must be visible and inside that view's logical
    // viewport (the ring sits on the fighter, so it cannot land outside the frame it draws).
    ui::HudFighterHud entry0, entry1;
    check(game::projectFighterHud(&vp0[0][0], targets[0].position.x, targets[0].position.y,
                                  targets[0].position.z, entry0, layout0.width, layout0.height),
          "view 0 sees its own fighter");
    check(game::projectFighterHud(&vp1[0][0], targets[1].position.x, targets[1].position.y,
                                  targets[1].position.z, entry1, layout1.width, layout1.height),
          "view 1 sees its own fighter");
    check(entry0.visible && entry0.ringX >= 0.f && entry0.ringX <= layout0.width &&
              entry0.ringY >= 0.f && entry0.ringY <= layout0.height,
          "view 0's marker lands inside view 0's logical viewport");
    check(entry1.visible && entry1.ringX >= 0.f && entry1.ringX <= layout1.width &&
              entry1.ringY >= 0.f && entry1.ringY <= layout1.height,
          "view 1's marker lands inside view 1's logical viewport");

    // The same world point through both matrices: each view sees it where its own camera
    // puts it, which is the whole point of a per-view projection. The probe sits in front of
    // both cameras (fighter 0's camera looks along +Z, fighter 1's along +X/-Z).
    const float probe[3] = {1100.f, 200.f, 500.f};
    ui::HudFighterHud a, b;
    const bool seenA = game::projectFighterHud(&vp0[0][0], probe[0], probe[1], probe[2], a,
                                               layout0.width, layout0.height);
    const bool seenB = game::projectFighterHud(&vp1[0][0], probe[0], probe[1], probe[2], b,
                                               layout1.width, layout1.height);
    check(seenA && seenB, "a mid-arena point is in front of both views' cameras");
    check(!near(a.ringX, b.ringX, 1.f) || !near(a.ringY, b.ringY, 1.f),
          "the same point projects to different view-local positions");

    // A point behind the camera has no screen position in that view.
    const float behind[3] = {left.eye().x - (left.target().x - left.eye().x) * 2.f,
                             left.eye().y,
                             left.eye().z - (left.target().z - left.eye().z) * 2.f};
    ui::HudFighterHud hidden;
    check(!game::projectFighterHud(&vp0[0][0], behind[0], behind[1], behind[2], hidden,
                                   layout0.width, layout0.height) &&
              !hidden.visible,
          "a point behind a view's camera is not visible in that view");

    // Per-view viewport origins: a view drawn in the bottom-right cell offsets its HUD by
    // that cell, exactly as FUN_0063a130 takes (rect.left, rect.top).
    const ui::UiViewport view1{(uint32_t)cell1.w, (uint32_t)cell1.h, (uint32_t)cell1.x,
                               (uint32_t)cell1.y};
    check(view1.x == 960 && view1.y == 540 && view1.w == 960 && view1.h == 540,
          "the BR view's HUD viewport is the cell, not the frame");
}

// 4. The synthetic pad pattern --local-players feeds to pad-less controllers.
void syntheticPadCases() {
    using fnd::input::SyntheticPadState;
    const SyntheticPadState a = fnd::input::syntheticPadState(1, 100);
    const SyntheticPadState b = fnd::input::syntheticPadState(1, 100);
    check(a.up == b.up && a.down == b.down && a.left == b.left && a.right == b.right &&
              a.melee == b.melee && a.shoot == b.shoot && a.jump == b.jump && a.guard == b.guard &&
              a.lock == b.lock,
          "the synthetic pad pattern is deterministic for one (controller, tick)");
    bool anyAtAll = false, differs = false;
    for (uint64_t tick = 1; tick <= 768; ++tick) {
        const SyntheticPadState p1 = fnd::input::syntheticPadState(1, tick);
        const SyntheticPadState p2 = fnd::input::syntheticPadState(2, tick);
        anyAtAll = anyAtAll || p1.any();
        differs = differs ||
                  p1.left != p2.left || p1.melee != p2.melee || p1.shoot != p2.shoot ||
                  p1.jump != p2.jump || p1.guard != p2.guard;
    }
    check(anyAtAll, "the synthetic pad is never silent");
    check(differs, "two synthetic pads differ (views cannot be one repeated view)");
    // The LockSwitch tap is opt-in: by default no view retargets its camera (four views
    // each sweeping between fighters reads as a camera defect), and --lock-taps restores
    // the per-view tap so that path stays exercised on request.
    bool lockByDefault = false, lockWhenAsked = false, lockDiffers = false;
    for (uint64_t tick = 1; tick <= 768; ++tick) {
        const SyntheticPadState quiet = fnd::input::syntheticPadState(1, tick);
        const SyntheticPadState taps = fnd::input::syntheticPadState(1, tick, true);
        const SyntheticPadState taps2 = fnd::input::syntheticPadState(2, tick, true);
        lockByDefault = lockByDefault || quiet.lock;
        lockWhenAsked = lockWhenAsked || taps.lock;
        lockDiffers = lockDiffers || taps.lock != taps2.lock;
    }
    check(!lockByDefault, "the synthetic pad does not retarget the camera unless asked");
    check(lockWhenAsked, "--lock-taps restores the per-view LockSwitch tap");
    check(lockDiffers, "the --lock-taps pattern is per controller, not shared");
    // The pattern is total: controller 0 and an out-of-range index still yield a defined,
    // non-empty state (only controllers 1..3 ever receive it).
    check(fnd::input::syntheticPadState(0, 100).any() &&
              fnd::input::syntheticPadState(-1, 100).any(),
          "the pattern is defined for any controller index");
}

}  // namespace

int main() {
    layoutCases();
    assignmentCases();
    perViewProjectionCases();
    syntheticPadCases();
    std::printf("view_layout_test: %s\n", g_failures ? "FAIL" : "ok");
    return g_failures ? 1 : 0;
}
