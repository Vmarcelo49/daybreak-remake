#pragma once
// One local player's view of a live match (issue #12).
//
// WHAT the original keeps per view, and why this struct is keyed the same way:
// FUN_006396f0 @0x006396f0 renders split-screen by controller, not by fighter. It writes
// the view's controller index to game+0x44b4 (:110) and then uses
// `game + 0x454e + controller * 0x160` — four 0x160-byte contexts starting at game+0x454c,
// whose first byte is that view's "hide the HUD" flag (read at +0x454c in FUN_0063a130
// @0x0063a130:53) — as the context it draws with, and passes the same controller index
// plus the cell origin to the HUD drawer (`FUN_0063a130(game, controller, rect.left,
// rect.top)`, :185-186, whose 0.5 HUD scale for more than one view is at :49-51).
//
// This struct is that per-view context, ported: the camera that follows the controller's
// own fighter, the lock bookkeeping its own LockSwitch gestures drive, and the HUD state
// filled from that fighter's own resources. It holds no simulation state: the match is
// stepped once per tick (D9) and every view only reads it.
#include <glm/glm.hpp>

#include "gameplay/arena_camera.h"   // gameplay::ArenaCamera (per-view camera)
#include "ui/hud.h"                  // ui::HudState (the per-view HUD frame)

namespace game {

struct MatchView {
    // Controller slot that owns this view and the fighter it renders. Both are indices in
    // different spaces: controller 0..3 or -1 for none, fighter
    // 0..fighterCount-1 in MatchConfig order.
    int controller = -1;
    int fighter = -1;

    // The view's own camera. Each view starts following its own fighter
    // (FUN_006396f0 case 1 pins the single human's camera to its controller at :50) and
    // cycles independently after that.
    gameplay::ArenaCamera camera;
    int                   followed = -1;   // camera's active target (fighter index)

    // Render interpolation: the eye/aim the previous tick ended with. `primed` marks the
    // first tick, which has no earlier view to interpolate from.
    glm::vec3 previousEye{0.f};
    glm::vec3 previousTarget{0.f};

    // This view's HUD frame: its own fighter's resources, its own target ring, projected
    // through its own camera at render time (D8).
    ui::HudState hud;

    bool active() const { return controller >= 0 && fighter >= 0; }
};

}  // namespace game
