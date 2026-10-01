// =============================================================================
//  arena_camera.cpp — see arena_camera.h for design rationale.
// =============================================================================
#include "arena_camera.h"

#include <algorithm>
#include <cmath>
#include <cstdio>

#include "physics/raycast.h"

namespace daybreak {

ArenaCamera::ArenaCamera() {
    D3DXMatrixIdentity(&m_view);
    D3DXMatrixIdentity(&m_proj);
    m_eye    = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_target = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    m_up     = D3DXVECTOR3(0.0f, 1.0f, 0.0f);  // Y-up world
}

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
    m_activeIdx = index;
}

void ArenaCamera::cycle_target(bool forward) {
    if (m_pool.empty()) return;
    int n = static_cast<int>(m_pool.size());
    int start = m_activeIdx;
    int i = start;
    for (int steps = 0; steps < n; ++steps) {
        i = forward ? (i + 1) % n : (i - 1 + n) % n;
        if (m_pool[i] && m_pool[i]->alive) {
            m_activeIdx = i;
            return;
        }
    }
    // No alive fighters found — keep the current target.
}

CameraTarget* ArenaCamera::active_target() const {
    if (m_activeIdx < 0 || m_activeIdx >= static_cast<int>(m_pool.size())) {
        return nullptr;
    }
    return m_pool[m_activeIdx];
}

D3DXVECTOR3 ArenaCamera::compute_desired_eye(const CameraTarget* t) const {
    if (!t) return D3DXVECTOR3(0.0f, 0.0f, kHeightOffset);

    // The camera sits 45° to the side of the target's facing direction
    // (gives a 3/4 view rather than directly behind).
    float angle = t->facing_yaw - kBaselineZRotation + m_orbitNudge;

    // XZ is the horizontal plane, Y is up.
    const float dist = (m_distOverride >= 0.0f) ? m_distOverride : kDistanceOffset;
    const float height = (m_heightOverride >= 0.0f) ? m_heightOverride : kHeightOffset;
    float dx = -std::sin(angle) * dist;
    float dz = -std::cos(angle) * dist;
    float dy = height;

    return D3DXVECTOR3(t->position.x + dx,
                       t->position.y + dy,
                       t->position.z + dz);
}

void ArenaCamera::update(double /*dt*/, D3DXFRAME* collisionFrame) {
    CameraTarget* t = active_target();
    if (!t) {
        // No target — keep the view static.
        return;
    }

    // Target position is the fighter's position (slightly above ground).
    m_target = D3DXVECTOR3(t->position.x, t->position.y + 50.0f, t->position.z);

    D3DXVECTOR3 desiredEye = compute_desired_eye(t);

    // Collision: raycast from target toward desired eye against collision_camera.
    // If the ray hits something before reaching the desired eye, clamp the
    // eye to the hit point (so the camera doesn't see through walls).
    //
    // This is a simplified version of the original game's two-pass raycast
    // (RE section 14.4).  The original does:
    //   1. raycast target → desiredEye
    //   2. if hit, raycast hitPoint → desiredEye (to refine)
    //   3. lerp eye toward the final position
    // We skip step 2 for now — the spring lerp in step 3 handles smoothing.
    if (collisionFrame) {
        D3DXVECTOR3 rayDir = desiredEye - m_target;
        float desiredDist = D3DXVec3Length(&rayDir);
        if (desiredDist > 0.0001f) {
            D3DXVec3Normalize(&rayDir, &rayDir);
            auto hit = physics::raycast_model(collisionFrame, m_target, rayDir,
                                               desiredDist);
            if (hit.hit && hit.dist < desiredDist) {
                // Clamp eye to slightly before the hit point.
                float clampDist = std::max(0.0f, hit.dist - 20.0f);
                m_eye = D3DXVECTOR3(
                    m_target.x + rayDir.x * clampDist,
                    m_target.y + rayDir.y * clampDist,
                    m_target.z + rayDir.z * clampDist);
                m_lastHitDist = hit.dist;
                m_hitLastFrame = true;
            } else {
                // Lerp factor 0.1 = ~10% per frame at 60fps → smooth follow.
                m_eye = D3DXVECTOR3(
                    m_eye.x + (desiredEye.x - m_eye.x) * 0.1f,
                    m_eye.y + (desiredEye.y - m_eye.y) * 0.1f,
                    m_eye.z + (desiredEye.z - m_eye.z) * 0.1f);
                m_lastHitDist = kMaxRaycastDist;
                m_hitLastFrame = false;
            }
        }
    } else {
        m_eye = D3DXVECTOR3(
            m_eye.x + (desiredEye.x - m_eye.x) * 0.1f,
            m_eye.y + (desiredEye.y - m_eye.y) * 0.1f,
            m_eye.z + (desiredEye.z - m_eye.z) * 0.1f);
    }

    m_up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

    D3DXMatrixLookAtLH(&m_view, &m_eye, &m_target, &m_up);
}

D3DXMATRIX ArenaCamera::proj_matrix(int viewport_w, int viewport_h) const {
    float aspect = (viewport_h > 0)
        ? static_cast<float>(viewport_w) / static_cast<float>(viewport_h)
        : 1.0f;
    D3DXMATRIX p;
    D3DXMatrixPerspectiveFovLH(&p, kFovY, aspect, kNearClip, kFarClip);
    return p;
}

} // namespace daybreak
