// =============================================================================
//  projectile.cpp — see projectile.h for provenance and the port notes.
//
//  Faithful translation of remake/src/gameplay/projectile.cpp: same order of
//  operations, same numbers, same iteration order (fixed arrays, index order —
//  the trace must be a pure function of the pool state and dt).
// =============================================================================
#include "gameplay/projectile.h"

#include <cmath>

#include "gameplay/fighter.h"
#include "physics/raycast.h"

namespace gameplay {

void ProjectilePool::clear() {
    for (auto& s : m_shots)  s.alive = false;
    for (auto& s : m_sparks) s.alive = false;
}

bool ProjectilePool::spawn(const glm::vec3& pos, const glm::vec3& dir,
                           ShotTier tier, Fighter* owner) {
    // Damage and hit radius come from the firing fighter's weapon when it bound one
    // (data/bullet/<id>/<type>.dat, via FUN_005f8510's verbatim block); otherwise the
    // shared provisional table. Speed and lifetime are provisional for every weapon:
    // they are absent from every shipped record (see the coverage table). Every tier
    // above Tap draws the charged (level-2) block, including the EX.
    const ShotParams p = owner ? owner->shot_params_for(tier) : shot_params(tier);
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

void ProjectilePool::spawn_spark(const glm::vec3& pos, float life) {
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
                            const xm::Model* tamaModel,
                            const game::physics::ModelIndex* tamaIndex,
                            const int* fighterSides) {
    const float step = static_cast<float>(dt);

    for (auto& s : m_shots) {
        if (!s.alive) continue;
        const ShotParams p = s.owner ? s.owner->shot_params_for(s.tier)
                                   : shot_params(s.tier);

        s.age += step;
        if (s.age >= p.lifeSec) {
            s.alive = false;
            continue;
        }

        const glm::vec3 prev = s.pos;
        s.pos += s.vel * step;

        // Wall check on the projectile channel: segment-cast the step just
        // taken so fast shots cannot tunnel through thin tama geometry.
        if (tamaModel && tamaIndex) {
            const glm::vec3 stepVec = s.pos - prev;
            const float stepLen = glm::length(stepVec);
            if (stepLen > 0.0001f) {
                const glm::vec3 dir = stepVec / stepLen;
                const game::physics::RayHit hit = game::physics::raycastModel(
                    *tamaModel, *tamaIndex, prev, dir, stepLen);
                if (hit.hit) {
                    s.alive = false;
                    spawn_spark(hit.point, 0.3f);
                    continue;
                }
            }
        }

        // Fighter hits: XZ-radius check, consistent with try_melee_hit
        // (the arena plays flat until jumping/fly lands — no jump state yet).
        // A DOWNED fighter is a valid target here: the original's shot path credits
        // Overkill (+1 to the victim's own side) and still consumes the shot
        // (FUN_00637950 @0x638e0d-0x638e37), while its melee path credits nothing and
        // never offers a dead candidate (FUN_00639160 @0x63938d-0x639393).
        int ownerSide = -1;
        if (fighterSides)
            for (int i = 0; i < fighterCount; ++i)
                if (&fighters[i] == s.owner) { ownerSide = fighterSides[i]; break; }
        // The blow's hit category is the RAW record +0x64 dword of the bullet block the
        // shot was fired with (FUN_00637950 @0x638c26); the victim's own reaction move
        // is derived from it by FUN_0063ba80. A weapon with no bound block keeps 0,
        // which takes that function's default branch.
        int hitCategory = 0;
        if (s.owner) {
            const BulletParameter* bullet =
                s.owner->bullet_parameter(s.tier == ShotTier::Tap ? 1 : 2);
            if (bullet) hitCategory = bullet->hitResolutionField64;
        }
        for (int i = 0; i < fighterCount; ++i) {
            Fighter& f = fighters[i];
            if (&f == s.owner || (ownerSide >= 0 && fighterSides[i] == ownerSide)) continue;
            const glm::vec3& fp = f.position();
            const float dx = fp.x - s.pos.x;
            const float dz = fp.z - s.pos.z;
            if (dx * dx + dz * dz > p.hitRadius * p.hitRadius) continue;
            s.alive = false;
            f.take_damage(p.damage, s.owner, -1, hitCategory, /*shot=*/true);
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

}  // namespace gameplay
