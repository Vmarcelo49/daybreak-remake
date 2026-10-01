// =============================================================================
//  projectile.cpp — see projectile.h for provenance.
// =============================================================================
#include "gameplay/projectile.h"

#include <cmath>

#include "gameplay/fighter.h"
#include "physics/raycast.h"

namespace daybreak::gameplay {

void ProjectilePool::clear() {
    for (auto& s : m_shots)  s.alive = false;
    for (auto& s : m_sparks) s.alive = false;
}

bool ProjectilePool::spawn(const D3DXVECTOR3& pos, const D3DXVECTOR3& dir,
                           ShotTier tier, const void* owner) {
    const ShotParams p = shot_params(tier);
    for (auto& s : m_shots) {
        if (s.alive) continue;
        s.alive = true;
        s.tier  = tier;
        s.pos   = pos;
        s.vel   = dir * p.speed;
        s.age   = 0.0f;
        s.life  = p.lifeSec;
        s.owner = owner;
        return true;
    }
    return false;
}

void ProjectilePool::spawn_spark(const D3DXVECTOR3& pos, float life) {
    for (auto& s : m_sparks) {
        if (s.alive) continue;
        s.alive = true;
        s.pos   = pos;
        s.age   = 0.0f;
        s.life  = (life > 0.0f) ? life : 0.3f;
        return;
    }
}

void ProjectilePool::update(double dt, Fighter* fighters, int fighterCount,
                            D3DXFRAME* tamaRoot) {
    const float step = static_cast<float>(dt);

    for (auto& s : m_shots) {
        if (!s.alive) continue;
        const ShotParams p = shot_params(s.tier);

        s.age += step;
        if (s.age >= p.lifeSec) {
            s.alive = false;
            continue;
        }

        const D3DXVECTOR3 prev = s.pos;
        s.pos += s.vel * step;

        // Wall check on the projectile channel: segment-cast the step just
        // taken so fast shots cannot tunnel through thin tama geometry.
        if (tamaRoot) {
            D3DXVECTOR3 stepVec = s.pos - prev;
            const float stepLen = D3DXVec3Length(&stepVec);
            if (stepLen > 0.0001f) {
                D3DXVECTOR3 dir = stepVec / stepLen;
                const physics::RaycastHit hit = physics::raycast_model(
                    tamaRoot, prev, dir, stepLen);
                if (hit.hit) {
                    s.alive = false;
                    spawn_spark(hit.point, 0.3f);
                    continue;
                }
            }
        }

        // Fighter hits: XZ-radius check, consistent with try_melee_hit
        // (the arena plays flat until jumping/fly lands — no jump state yet).
        // Downed fighters are skipped: hitting them is Overkill (milestone 7).
        for (int i = 0; i < fighterCount; ++i) {
            Fighter& f = fighters[i];
            if (&f == s.owner || !f.is_alive()) continue;
            const D3DXVECTOR3& fp = f.position();
            const float dx = fp.x - s.pos.x;
            const float dz = fp.z - s.pos.z;
            if (dx * dx + dz * dz > p.hitRadius * p.hitRadius) continue;
            s.alive = false;
            f.take_damage(p.damage);
            spawn_spark(s.pos, 0.35f);
            break;
        }
    }

    for (auto& sp : m_sparks) {
        if (!sp.alive) continue;
        sp.age += step;
        if (sp.age >= sp.life) sp.alive = false;
    }
}

int ProjectilePool::live_shots() const {
    int n = 0;
    for (const auto& s : m_shots) n += s.alive ? 1 : 0;
    return n;
}

void ProjectilePool::draw_cube(IDirect3DDevice9* device,
                               const D3DXVECTOR3& center,
                               float halfExtent, D3DCOLOR color) {
    struct V {
        float x, y, z;
        D3DCOLOR c;
    };
    static constexpr DWORD kFvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;
    const float h = halfExtent;
    // 12 triangles, 36 vertices (two per face, outward winding is irrelevant:
    // culling is off for debug cubes).
    const V v[36] = {
        {center.x-h, center.y-h, center.z-h, color},
        {center.x-h, center.y+h, center.z-h, color},
        {center.x+h, center.y+h, center.z-h, color},
        {center.x-h, center.y-h, center.z-h, color},
        {center.x+h, center.y+h, center.z-h, color},
        {center.x+h, center.y-h, center.z-h, color},
        {center.x-h, center.y-h, center.z+h, color},
        {center.x+h, center.y+h, center.z+h, color},
        {center.x-h, center.y+h, center.z+h, color},
        {center.x-h, center.y-h, center.z+h, color},
        {center.x+h, center.y-h, center.z+h, color},
        {center.x+h, center.y+h, center.z+h, color},
        {center.x-h, center.y-h, center.z-h, color},
        {center.x-h, center.y-h, center.z+h, color},
        {center.x-h, center.y+h, center.z+h, color},
        {center.x-h, center.y-h, center.z-h, color},
        {center.x-h, center.y+h, center.z+h, color},
        {center.x-h, center.y+h, center.z-h, color},
        {center.x+h, center.y-h, center.z-h, color},
        {center.x+h, center.y+h, center.z+h, color},
        {center.x+h, center.y-h, center.z+h, color},
        {center.x+h, center.y-h, center.z-h, color},
        {center.x+h, center.y+h, center.z-h, color},
        {center.x+h, center.y+h, center.z+h, color},
        {center.x-h, center.y+h, center.z-h, color},
        {center.x-h, center.y+h, center.z+h, color},
        {center.x+h, center.y+h, center.z+h, color},
        {center.x-h, center.y+h, center.z-h, color},
        {center.x+h, center.y+h, center.z+h, color},
        {center.x+h, center.y+h, center.z-h, color},
        {center.x-h, center.y-h, center.z-h, color},
        {center.x+h, center.y-h, center.z+h, color},
        {center.x-h, center.y-h, center.z+h, color},
        {center.x-h, center.y-h, center.z-h, color},
        {center.x+h, center.y-h, center.z-h, color},
        {center.x+h, center.y-h, center.z+h, color},
    };
    device->SetFVF(kFvf);
    device->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 12, v, sizeof(V));
}

void ProjectilePool::render(IDirect3DDevice9* device) {
    if (!device) return;

    // Debug cubes are unlit + uncullled; sparks additionally fade via alpha.
    DWORD prevLighting = TRUE, prevCull = D3DCULL_CCW, prevBlend = FALSE;
    device->GetRenderState(D3DRS_LIGHTING, &prevLighting);
    device->GetRenderState(D3DRS_CULLMODE, &prevCull);
    device->GetRenderState(D3DRS_ALPHABLENDENABLE, &prevBlend);
    device->SetRenderState(D3DRS_LIGHTING, FALSE);
    device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

    for (const auto& s : m_shots) {
        if (!s.alive) continue;
        draw_cube(device, s.pos, 16.0f, shot_params(s.tier).color);
    }

    device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
    device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    for (const auto& sp : m_sparks) {
        if (!sp.alive) continue;
        // Grow + fade over life (expanding flash reads as an impact).
        const float t = sp.age / sp.life;
        const int alpha = static_cast<int>(255.0f * (1.0f - t));
        const D3DCOLOR c = D3DCOLOR_ARGB(alpha, 255,
                                        static_cast<int>(240.0f - 120.0f * t), 120);
        draw_cube(device, sp.pos, 14.0f + 46.0f * t, c);
    }

    device->SetRenderState(D3DRS_ALPHABLENDENABLE, prevBlend);
    device->SetRenderState(D3DRS_CULLMODE, prevCull);
    device->SetRenderState(D3DRS_LIGHTING, prevLighting);
}

} // namespace daybreak::gameplay
