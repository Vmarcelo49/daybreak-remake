// gameplay/arena_camera.cpp — see arena_camera.h for the port's contract and why each
// piece of state exists. Structure follows the reference line for line so the two can
// be diffed; the comments mark the two places where the reference's control flow is
// load-bearing (the degenerate-segment early-out and the blocked/unblocked asymmetry).
#include "gameplay/arena_camera.h"

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>

namespace gameplay {

void ArenaCamera::set_target_pool(const std::vector<CameraTarget*>& fighters) {
    m_pool = fighters;
    // If the current target is no longer in the pool, pick the first alive.
    if (m_activeIdx < 0 || m_activeIdx >= static_cast<int>(m_pool.size()) ||
        !m_pool[m_activeIdx] || !m_pool[m_activeIdx]->alive) {
        for (size_t i = 0; i < m_pool.size(); ++i) {
            if (m_pool[i] && m_pool[i]->alive) {
                m_activeIdx = static_cast<int>(i);
                return;
            }
        }
        m_activeIdx = -1;
    }
}

void ArenaCamera::set_active_target(int index) {
    if (index < 0 || index >= static_cast<int>(m_pool.size())) return;
    if (!m_pool[index] || !m_pool[index]->alive) return;
    if (m_activeIdx == index) return;
    m_activeIdx = index;
    armRetarget();
}

void ArenaCamera::cycle_target(bool forward) {
    if (m_pool.empty()) return;
    const int n = static_cast<int>(m_pool.size());
    // The reference walks from m_activeIdx; with no active target (-1) a forward walk
    // starts at 0 and a backward one at n-2, which is kept because the parity traces
    // depend on which fighter a first press lands on.
    int i = m_activeIdx;
    for (int steps = 0; steps < n; ++steps) {
        i = forward ? (i + 1) % n : (i - 1 + n) % n;
        if (m_pool[i] && m_pool[i]->alive) {
            // A cycle that lands back where it started (one fighter, or every other one
            // dead) is not a retarget and arms no boost — that is what keeps a 1v1's
            // banked trace on the reference's 10% blend.
            if (i != m_activeIdx) armRetarget();
            m_activeIdx = i;
            return;
        }
    }
    // No alive fighters found — keep the current target.
}

float ArenaCamera::followBlend() const {
    return m_retargetTicks > 0 ? kRetargetBlend : kFollowBlend;
}

CameraTarget* ArenaCamera::active_target() const {
    if (m_activeIdx < 0 || m_activeIdx >= static_cast<int>(m_pool.size())) {
        return nullptr;
    }
    return m_pool[m_activeIdx];
}

glm::vec3 ArenaCamera::compute_desired_eye(const CameraTarget* t) const {
    if (!t) return glm::vec3(0.0f, 0.0f, m_preset.height);

    // The eye math has one implementation in the tree — render::arenaViewProj, which is
    // the same formula as the reference's (angle = facing - π/4 + nudge, XZ horizontal,
    // the offset subtracted so the camera sits behind the fighter at the preset's
    // azimuth). Its view/proj are the same glm calls update()/proj_matrix() make, so
    // reading .eye out of it is exact; the aspect argument only feeds matrices that are
    // discarded here. The nudge carries the difference between the render helper's π/4
    // baseline and the preset's, so no second copy of the azimuth math exists.
    if (m_recoveredFollow) {
        // V3-15: the recovered normal follow needs the rig and its lock-on anchor, and
        // owns its whole eye/aim derivation — present it the same params the
        // reconstruction uses so projection/clip stay shared.
        render::ArenaCameraParams p;
        p.fovY       = m_preset.fovY;
        p.nearClip   = m_preset.nearClip;
        p.farClip    = m_preset.farClip;
        return render::arenaRecoveredFollow(t->position, m_followAnchor, p, 1.0f).eye;
    }

    render::ArenaCameraParams p;
    p.heightOffset   = effective_height();
    p.distanceOffset = effective_distance();
    p.orbitNudge     = m_orbitNudge + (kRenderBaselineOrbit - m_preset.baselineOrbit);
    return render::arenaViewProj(*t, p, 1.0f).eye;
}

void ArenaCamera::update(double /*dt*/, const CollisionQuery& collision) {
    CameraTarget* t = active_target();
    if (!t) {
        // No target — keep the view static. The reference returns before touching the
        // aim, the up vector or the view matrix, so they keep their previous values.
        return;
    }

    // The aim is the fighter's position raised by the preset's aim height, not the
    // position itself (the remake raised it 50; the original aims at her neck).
    m_target = glm::vec3(t->position.x, t->position.y + m_preset.aimHeight, t->position.z);

    glm::vec3 desiredEye = compute_desired_eye(t);
    if (m_actionRig && m_actionClip >= 0 && static_cast<size_t>(m_actionClip) < m_actionRig->anims.size()) {
        // FUN_00633140 / FUN_006333b0: camera/01.x Box01/Box02 offsets.
        // The source transforms (1,0,0), not the origin, at elapsed * 0.016.
        m_actionController.setTrackPosition(0, m_actionTime);
        m_actionController.setTrackPosition(1, m_actionTime);
        std::vector<glm::mat4> pose;
        m_actionController.evalWorld(pose);
        const int eye = m_actionRig->findFrame("Box01");
        const int aim = m_actionRig->findFrame("Box02");
        const glm::mat4 rotation = glm::rotate(glm::mat4(1.f), m_actionYaw + glm::pi<float>(), glm::vec3(0.f,1.f,0.f));
        if (eye >= 0 && aim >= 0) {
            desiredEye = m_actionPosition + glm::vec3(rotation * pose[static_cast<size_t>(eye)] * glm::vec4(1.f,0.f,0.f,1.f));
            const glm::vec3 desiredAim = m_actionOpponent + glm::vec3(rotation * pose[static_cast<size_t>(aim)] * glm::vec4(1.f,0.f,0.f,1.f));
            // FUN_00633220 smooths action eye/aim at 0.2/0.3, independently of
            // the normal orbit follow blend and collision clamp.
            const auto smooth = [](const glm::vec3& previous, const glm::vec3& desired, float blend) {
                const float distance = glm::length(desired - previous);
                return distance <= 2.f || distance > 10000.f ? desired : glm::mix(previous, desired, blend);
            };
            m_eye = smooth(m_eye, desiredEye, .2f);
            m_target = smooth(m_previousActionAim, desiredAim, .3f);
            m_previousActionAim = m_target;
            const float period = m_actionRig->anims[static_cast<size_t>(m_actionClip)].duration / m_actionRig->ticksPerSecond;
            if (m_actionTime < period) m_actionTime += .016f;
            m_up = glm::vec3(0.f,1.f,0.f);
            m_view = glm::lookAtLH(m_eye, m_target, m_up);
            return;
        }
    }

    if (collision.collision) {
        const glm::vec3 leg = desiredEye - m_target;
        const float     desiredDist = glm::length(leg);
        // A degenerate segment leaves the eye untouched — not even the lerp runs. The
        // reference nests this guard inside the collision branch (arena_camera.cpp:109),
        // so the no-collision path below lerps unconditionally.
        if (desiredDist > 0.0001f) {
            // queryClamp is the reference's raycast plus its own hit test
            // (hit.dist < segment length), so `hit` is exactly the reference's
            // blocked/unblocked branch condition.
            const game::CameraClampResult hit =
                collision.collision->queryClamp({m_target, desiredEye});
            if (hit.hit) {
                // Blocked: snap to just before the blocker in this same call. The
                // reference does not smooth the blocked path (arena_camera.cpp:113-121).
                const glm::vec3 dir = leg / desiredDist;
                const float clampDist = std::max(0.0f, hit.hitDist - kCollisionMargin);
                m_eye = m_target + dir * clampDist;
            } else {
                m_eye = render::arenaSmoothEye(m_eye, desiredEye, followBlend());
            }
        }
    } else {
        // No collision frame configured: the follow lerp, nothing else.
        m_eye = render::arenaSmoothEye(m_eye, desiredEye, followBlend());
    }

    // The retarget boost is a per-call window, so it is consumed after the lerp that
    // used it (see followBlend).
    if (m_retargetTicks > 0) --m_retargetTicks;

    m_up   = glm::vec3(0.0f, 1.0f, 0.0f);
    m_view = glm::lookAtLH(m_eye, m_target, m_up);
}

void ArenaCamera::set_external_pose(const glm::vec3& eye, const glm::vec3& target, float fovY, float nearPlane) {
    m_eye = eye;
    m_target = target;
    m_up = glm::vec3(0.f, 1.f, 0.f);
    if (eye != target) m_view = glm::lookAtLH(m_eye, m_target, m_up);
    m_preset.fovY = fovY;
    m_preset.nearClip = nearPlane;
    m_preset.farClip = 150000.f;  // FUN_00633860
}

glm::mat4 ArenaCamera::proj_matrix(int viewport_w, int viewport_h) const {
    // The aspect is the viewport's, not the original's constant 4/3: the original's own
    // D3DXMatrixPerspectiveFovLH call passes 4/3 because its window was 800x600, and a
    // foundation capture at another size must not be stretched to match a constant.
    const float aspect = (viewport_h > 0)
        ? static_cast<float>(viewport_w) / static_cast<float>(viewport_h)
        : 1.0f;
    return glm::perspectiveLH_ZO(m_preset.fovY, aspect, m_preset.nearClip, m_preset.farClip);
}

}  // namespace gameplay
