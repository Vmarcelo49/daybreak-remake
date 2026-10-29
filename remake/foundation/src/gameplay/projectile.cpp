#include "gameplay/projectile.h"

#include <cmath>

#include "gameplay/fighter.h"
#include "gameplay/combat_volume.h"
#include "gameplay/projectile_behavior.h"
#include "game/shot_visual.h"
#include "physics/raycast.h"

namespace gameplay {

const MoveEntry* Projectile::record() const {
    return parameter && !parameter->phases.empty()
        ? parameter->phases.front().record_at(elapsed) : nullptr;
}

glm::mat4 Projectile::model_matrix() const {
    const auto* current = record();
    return game::shotModelMatrix(pos,current && (current->stateFlags & 0x4000)
                                     ? glm::vec3(0.f) : aimDirection,ownRotation);
}

std::vector<std::pair<std::string,std::string>> Projectile::texture_overrides() const {
    std::vector<std::pair<std::string,std::string>> result;
    if (!parameter) return result;
    // FUN_005f8510 appends every trailer interval to the variant's one material
    // vector; FUN_005f60b0 tests it against total shot age, not a fighter phase.
    for (const auto& set : parameter->animationSets)
        for (const auto& event : set.textures)
            if (event.active(elapsed)) result.emplace_back(event.source,event.replacement);
    return result;
}

namespace {
void advancePose(Projectile& shot) {
    // FUN_005f75a0 walks only the first section's timed records; rendering
    // (FUN_005f60b0) positions track 0 at the same total-age counter.
    shot.elapsed = shot.ticks;
    shot.controller.setTrackPosition(0,shot.elapsed*kOriginalAnimationTick);
}

void moveShot(Projectile& shot, float step) {
    const auto* behavior = shot.behavior;
    if (!behavior) { shot.pos += shot.vel*step; return; }
    if (behavior->gravity > 0.f) {
        if (shot.ticks == 1) shot.vel.y = behavior->launchVertical / step;
        if (shot.ticks > 0) shot.vel.y -= behavior->gravity / step;
    } else {
        if (shot.target && shot.homing && behavior->turn + behavior->turnBase + behavior->turnDecay > 0.f) {
            const glm::vec3 offset = shot.target->position() - shot.pos;
            const float desiredYaw = std::atan2(offset.x,offset.z);
            const float difference = std::remainder(desiredYaw-shot.yaw,glm::two_pi<float>());
            if (std::abs(difference) > glm::half_pi<float>()) shot.homing = false;
            if (shot.homing) {
                const float rate = glm::radians(behavior->turn + behavior->turnBase +
                    behavior->turnDecay * std::max(0,behavior->turnCounter-shot.ticks-1));
                shot.yaw += std::clamp(difference,-rate,rate);
                const float desiredPitch = std::atan2(offset.y,std::hypot(offset.x,offset.z));
                const float pitchDifference = desiredPitch-shot.pitch;
                if (std::abs(pitchDifference) > glm::radians(behavior->pitchDeadZone))
                    shot.pitch += std::copysign(rate,pitchDifference);
            }
        }
        shot.vel = glm::vec3(std::sin(shot.yaw)*std::cos(shot.pitch),std::sin(shot.pitch),
                              std::cos(shot.yaw)*std::cos(shot.pitch)) * (shot.speed/step);
    }
    shot.pos += shot.vel*step;
}
} // namespace

void ProjectilePool::clear() {
    for (auto& s : m_shots)  s.alive = false;
    for (auto& s : m_sparks) s.alive = false;
    m_visualRandom.seed();
}

bool ProjectilePool::spawn(const glm::vec3& pos, const glm::vec3& dir,
                           ShotTier tier, Fighter* owner, int bulletRow, Fighter* target) {
    // Exact rows carry their own model, variant and pool capacity. A custom
    // caller without a row keeps the explicitly legacy tier tuning.
    const ShotParams p = owner ? owner->shot_params_for_row(tier, bulletRow) : shot_params(tier);
    const auto* weapon = owner ? owner->weapon() : nullptr;
    const BulletDefinition* definition = weapon && bulletRow >= 0 && bulletRow < weapon->bulletCount
                                            ? &weapon->bullets[bulletRow] : nullptr;
    if (definition) {
        int count = 0;
        for (const auto& shot : m_shots)
            count += shot.alive && shot.owner == owner && shot.bulletRow == bulletRow;
        if (count >= definition->poolCapacity) return false;
    }
    for (auto& s : m_shots) {
        if (s.alive) continue;
        s = Projectile{};
        s.alive = true;
        s.tier  = tier;
        s.pos   = pos;
        s.vel   = dir * p.speed;
        s.age   = 0.0f;
        s.life  = p.lifeSec;
        s.owner = owner;
        s.bulletRow = bulletRow;
        s.parameter = owner ? (bulletRow >= 0 ? owner->bullet_row(bulletRow)
                                             : owner->bullet_parameter(tier == ShotTier::Tap ? 1 : 2)) : nullptr;
        s.parameters = p;
        s.impactEffect = s.parameter ? s.parameter->impactEffect : -1;
        s.target = target;
        s.model = owner ? owner->bullet_model(bulletRow) : nullptr;
        s.behavior = definition ? projectileBehavior(weapon->id,definition->paramId()) : nullptr;
        s.yaw = std::atan2(dir.x,dir.z);
        s.pitch = std::atan2(dir.y,std::hypot(dir.x,dir.z));
        s.aimDirection = dir;
        if (s.behavior) {
            s.speed = s.behavior->speed;
            s.hitsRemaining.fill(s.behavior->hitsPerVictim);
            s.pauseRemaining = s.behavior->contactPause;
            s.ownRotation.x = glm::radians(s.behavior->modelPitch);
            s.ownRotation.z = glm::radians(s.behavior->modelRoll);
            if (s.behavior->randomYaw) s.ownRotation.y = glm::radians(float(m_visualRandom()%360));
        }
        if (s.model && s.parameter && !s.parameter->phases.empty()) {
            s.controller.bind(s.model);
            s.controller.setAnimation(0);
        }
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
    if (!(step > 0.f)) return;
    m_contactCount = 0;  // this update's contacts only (issue #16)
    struct Emission { glm::vec3 position, direction; ShotTier tier; Fighter* owner; int row; Fighter* target; };
    std::vector<Emission> emissions;
    const auto emit = [&](const Projectile& shot, int row, const glm::vec3& position) {
        if (row >= 0) emissions.push_back({position,shot.aimDirection,shot.tier,shot.owner,row,shot.target});
    };

    for (auto& s : m_shots) {
        if (!s.alive) continue;
        const ShotParams& p = s.parameters;

        s.age += step;
        if (s.behavior ? s.ticks > s.behavior->lifetime : s.age >= p.lifeSec) {
            s.alive = false;
            continue;
        }

        const glm::vec3 prev = s.pos;
        if (s.behavior && s.behavior->secondaryInterval > 0 &&
            s.ticks % s.behavior->secondaryInterval == 0) emit(s,s.behavior->secondaryRow,s.pos);
        // FUN_005f91c0 returns before advancing the age/record cursor while a
        // red nata's contact pause counts down; hit budgets survive the reset.
        if (s.behavior && s.contactPending && s.behavior->contact == ProjectileContact::Pause) {
            if (s.pauseRemaining > 0) {
                --s.pauseRemaining;
                s.vel = glm::vec3(0.f);
                continue;
            }
            s.speed = s.behavior->resumeSpeed;
            s.pauseRemaining = s.behavior->repeatPause;
            s.contactPending = false;
            s.contactedVictims = 0;
        }
        if (s.behavior && s.ticks == 0) s.vel = s.aimDirection * (s.speed/step);
        moveShot(s,step);
        if (glm::dot(s.vel,s.vel) > 0.f) s.aimDirection = glm::normalize(s.vel);
        ++s.ticks;
        advancePose(s);
        const MoveEntry* record = s.model ? s.record() : nullptr;
        // FUN_005f6710 uses velocity-aligned local anchors directly. The bone,
        // visual YawPitchRoll and billboard flags affect rendering, not this hull.
        const glm::mat4 collisionMatrix = game::shotModelMatrix(s.pos,s.aimDirection);
        const auto anchor = [&](const std::array<float,3>& local) {
            return glm::vec3(collisionMatrix*glm::vec4(local[0],local[1],local[2],1.f));
        };

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
                    if (s.behavior) emit(s,s.behavior->wallRow,hit.point);
                    s.alive = false;
                    spawn_spark(hit.point, 0.3f);
                    continue;
                }
            }
        }

        // A DOWNED fighter is a valid target here: the original's shot path credits
        // Overkill (+1 to the victim's own side) and still consumes the shot
        // (FUN_00637950 @0x638e0d-0x638e37), while its melee path credits nothing and
        // never offers a dead candidate (FUN_00639160 @0x63938d-0x639393).
        int ownerSide = -1;
        int ownerIndex = -1;
        if (fighterSides)
            for (int i = 0; i < fighterCount; ++i)
                if (&fighters[i] == s.owner) { ownerSide = fighterSides[i]; break; }
        // The owner's index is what the audio/effect event needs (issue #16), and it is
        // valid without fighterSides: a lone --match pool passes none.
        for (int i = 0; i < fighterCount; ++i)
            if (&fighters[i] == s.owner) { ownerIndex = i; break; }
        // FUN_00637950 consumes the current record, not the first launch record.
        int hitCategory = 0;
        if (s.owner) {
            const BulletParameter* bullet =
                s.parameter;
            if (bullet) hitCategory = bullet->hitResolutionField64;
        }
        for (int i = 0; i < fighterCount; ++i) {
            Fighter& f = fighters[i];
            if (&f == s.owner || (ownerSide >= 0 && fighterSides[i] == ownerSide)) continue;
            if (s.behavior && (i >= 4 || s.hitsRemaining[static_cast<size_t>(i)] <= 0 ||
                              (s.contactedVictims & (1u << i)))) continue;
            if (record) {
                if (!record->has_combat()) continue;
                const auto body = f.hitbox_debug();
                if (!combatVolumeHits(anchor(record->anchor),anchor(record->endAnchor),
                                       record->collisionShape != 0,static_cast<float>(record->hitRadius),
                                       body.anchors[0],body.anchors[1])) continue;
            } else {
                const glm::vec3& fp = f.position();
                const float dx = fp.x-s.pos.x, dz = fp.z-s.pos.z;
                if (dx*dx+dz*dz > p.hitRadius*p.hitRadius) continue;
            }
            // FUN_00637950 latches a result and spends a per-victim allowance;
            // the weapon handler, not the collision test, decides retirement.
            // FUN_00637950's status loop uses attackFlags bits (0x40 << slot)
            // after contact has passed collision/target filters. Its slot-6 pair is
            // record.combat[1] (power) and record.combat[2] (duration), written to
            // victim+0x818/+0x7f4. This is the producer consumed by Rena recovery.
            if (record && (static_cast<unsigned>(record->attackFlags) & 0x1000u))
                f.apply_hit_status(6, record->combat[2], record->combat[1]);
            const bool blocked = f.state() == FighterState::Guard;
            if (s.behavior) {
                --s.hitsRemaining[static_cast<size_t>(i)];
                s.contactedVictims |= 1u << i;
                s.contactPending = true;
                if (blocked && s.behavior->contact == ProjectileContact::StopOnBlock) s.alive = false;
            } else s.alive = false;
            if (m_contactCount < static_cast<int>(m_contacts.size())) {
                ShotContact& c = m_contacts[static_cast<size_t>(m_contactCount++)];
                c.shooter = ownerIndex;
                c.victim  = i;
                c.point   = s.pos;
                c.effect  = record ? record->combat[16] : s.impactEffect;
            }
            const int damage = record ? static_cast<int>(record->baseDamage *
                                    (float(f.max_hp())/20000.f) + .5f) : p.damage;
            // A shot's record carries the same launch words as a swing's (+0x87c/+0x878,
            // 0x638633/0x638645), so an uncharged bullet reacts the same way.
            f.take_damage(damage,s.owner,record ? record->defenderHitstun : -1,
                            record ? record->reactionMove : hitCategory,/*shot=*/true,
                            record ? static_cast<float>(record->combat[17]) * 0.01f : 0.f,
                            record ? static_cast<float>(record->combat[18]) * 0.01f : 0.f);
            spawn_spark(s.pos, 0.35f);
            if (!s.alive) break;
        }
    }

    // FUN_005f6fd0 emits an exact item row through the owner's manager. Defer
    // allocation so a reused slot cannot advance a newborn twice in one update.
    for (const auto& emission : emissions)
        spawn(emission.position,emission.direction,emission.tier,emission.owner,emission.row,emission.target);

    for (auto& sp : m_sparks) {
        if (!sp.alive) continue;
        sp.age += step;
        if (sp.age >= sp.life) sp.alive = false;
    }
}

int ProjectilePool::live_shots() const {
    return static_cast<int>(
        std::count_if(m_shots.begin(), m_shots.end(),
                      [](const Projectile& s) { return s.alive; }));
}

}  // namespace gameplay
