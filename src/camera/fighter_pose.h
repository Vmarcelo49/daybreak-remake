#pragma once
// Live fighter pose provider: what the game layer must supply so the camera
// (and, later, character rendering) can follow the real fighters instead of
// env.dat spawn points.
//
// WHY an interface, not data: fighter positions/facing/animation live in the
// gameplay simulation (remake/src/gameplay/fighter.h — Fighter::position(),
// facing_yaw(), animation state), which the foundation must not own per
// PORT-PLAN.md (no gameplay in shared renderer code). The renderer polls one
// pose per locked-on fighter per frame; prediction, interpolation and the
// lock-on target choice stay game-side. glm + std only: no WebGPU, no SDL.
#include <glm/glm.hpp>

#include "camera/arena_view.h"

namespace game {

// One fighter's camera-relevant state at this frame. `position` is world
// space, Y-up game units (the convention render::ArenaTarget assumes);
// `facingYaw` is the actor yaw about Y (FUN_00420b30 convention, shared with
// ArenaTarget::facingYaw); `animTime` is seconds into the current animation
// set for the renderer-side pose lookup; `alive` lets lock-on skip the dead
// (the reference cycles past dead fighters, arena_camera.h cycle_target).
struct FighterPose {
    glm::vec3 position{0.f};
    float     facingYaw = 0.f;
    float     animTime = 0.f;
    bool      alive = true;
};

// Position/facing/animation-time provider. The gameplay Fighter implements
// this (or the scene adapts it); the camera path reads only through here, so
// the simulation can move under the renderer without either including the
// other. No ownership: pointers/references are borrowed per call.
class IFighterPose {
public:
    virtual ~IFighterPose() = default;
    virtual FighterPose pose() const = 0;
};

// Maps a live pose onto the arena camera's lock-on target: the eye/aim math
// reads position + yaw only (render::arenaViewProj raises the aim 50 units
// itself), so this is a field copy, not gameplay logic. Kept as a free
// function so callers holding plain structs (tests, replays) need no
// provider object.
inline render::ArenaTarget arenaTargetFrom(const FighterPose& p) {
    return render::ArenaTarget{p.position, p.facingYaw};
}

}  // namespace game
