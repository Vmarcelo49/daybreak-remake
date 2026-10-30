#pragma once
// render/shot_visual.h — what a shot draws while it is in flight (issue #32).
//
// WHAT THE ORIGINAL DRAWS, RECOVERED. The in-flight projectile is a real .X model, and
// the file that describes the shot names it:
//
//   1. `data/bullet/<weaponId>/<type>.dat` opens with a u32 tag and a 260-byte model
//      block. FUN_005f8510 reads both (live original 0x005f8556-0x005f8598), joins the
//      block to the bullet's own directory (`wsprintfA("%s%s", dir, block)`, 0x005f85b7)
//      and calls FUN_0064d940 with the bullet's per-variant model object in ECX
//      (0x005f85c7: `MOV ECX,[EBP+0x10]`), i.e. `itemdef + 0x3c + variant*0x9c`. A failed
//      load aborts the file (0x005f85d6), so the block is load-bearing, not a comment.
//   2. The shot spawn FUN_005f8d50 (`IMUL EAX,EAX,0x9c` at 0x005f8dbb, `ADD EAX,[ECX+0x3c]`
//      at 0x005f8dc4) pushes that same object as the third argument of the shot ctor.
//   3. FUN_005f9090 (the shot ctor, vtable 0x6a4814) stores it at `shot+0x120`
//      (0x005f90f0). The bullet's id, sprite definition and record container land beside
//      it at +0x150/+0x124/+0x128, and the owner fighter at +0x38.
//   4. The shot's render FUN_005f60b0 (vtable slot 0x6a4814+0x20, reached from the
//      per-frame object walk FUN_00435c20 @0x00435c90) composes the model's matrix at
//      `model+0x5c` from the shot's own scale (+0x70/0x74/0x78, 0x005f6185-0x005f618f),
//      rotation and position (+0x14/0x18/0x1c), then draws it (0x005f640f) with the blend
//      its record's +0x7c selects (0x005f63c2).
//
// So the visual is NOT the impact effect and NOT a trail: it is the bullet's own model,
// shipped inside the bullet's directory (e.g. data/bullet/007/50.X is the syringe of
// 007's syringe row, data/bullet/001/03.X the nata of Rena's throw; the row NAMES are
// external/UI labels, not shipped strings -- see ROADMAP-PENDING). The port
// reads the same block through gameplay::BulletParameter::modelName.
//
// WHAT IS STILL A PORT RULE — the AIM. FUN_005f60b0 rotates the model with
// `D3DXMatrixRotationYawPitchRoll(+0x2c, +0x30, +0x34)` (0x005f6206) and then, unless the
// record's +0x28 says otherwise, a `RotationZ` from the shot's direction vector
// (+0x3c/+0x40, 0x005f62f0; 0x005f62b2 is the zero-direction fallback that rotates by
// +0x6c) and a `RotationY` from +0x5c/+0x64 (0x005f6329) — i.e. the model's authored +X
// axis is aimed by a pitch about Z and a yaw about Y. That CONVENTION is recovered (and the
// shipped projectiles agree: the dart, the syringe and the beams are all authored long
// along +X). WHICH direction a given weapon's shot holds is written by that weapon's own
// update function (FUN_005f7be0 dispatches on the item id to 46 of them,
// 0x5f91c0..0x6322d0), including the YawPitchRoll triple — per-weapon state written by the
// handler, not a per-bullet field. projectile_behavior.h now records the recovered
// item-001 rules; other handlers still use provisional velocity tuning. Stationary
// secondary models retain their emission direction and their own rotation.
//
// glm only: this header is device-free and unit-tested (tests/effect_catalog_test.cpp).
#include <cmath>
#include <algorithm>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace game {

// The model matrix a shot's card is drawn with: the recovered convention (the model's
// authored +X axis aimed along `vel`, pitch applied first) at the shot's own position.
// PORT RULE for the direction source — see the header note. A shot with no velocity keeps
// the model's authored orientation rather than inventing a facing.
inline glm::mat4 shotModelMatrix(const glm::vec3& pos, const glm::vec3& vel,
                                const glm::vec3& ownRotation = {}) {
    glm::mat4 m = glm::translate(glm::mat4(1.f), pos);
    const float len = std::sqrt(vel.x * vel.x + vel.y * vel.y + vel.z * vel.z);
    // The original's own order (FUN_005f60b0: RotationZ then RotationY), which is what
    // makes +X the forward axis: Rz(pitch) then Ry(yaw) sends (1,0,0) to
    // (cos p cos y, sin p, -cos p sin y) = d.
    if (len > 0.f) {
        const glm::vec3 d = vel / len;
        const float pitch = std::asin(std::clamp(d.y,-1.f,1.f));
        const float yaw = std::atan2(-d.z,d.x);
        m = glm::rotate(m,yaw,glm::vec3(0.f,1.f,0.f));
        m = glm::rotate(m,pitch,glm::vec3(0.f,0.f,1.f));
    }
    // FUN_005f60b0 applies the shot's own YawPitchRoll before direction aiming.
    m = glm::rotate(m, ownRotation.y, glm::vec3(0.f,1.f,0.f));
    m = glm::rotate(m, ownRotation.x, glm::vec3(1.f,0.f,0.f));
    m = glm::rotate(m, ownRotation.z, glm::vec3(0.f,0.f,1.f));
    return m;
}

}  // namespace game
