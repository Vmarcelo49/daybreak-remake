#include "gameplay/legacy_battle.h"

#include "gameplay/combat_record.h"

namespace gameplay {

static_assert(game::kMaxLiveShots == ProjectilePool::kMaxShots);
static_assert(game::kShotCubeSize == Projectile::kCubeSize);

void LegacyBattle::for_each_shot(const std::function<void(const game::ShotView&)>& visit) const {
    for (const Projectile& p : m_match.shots().shots()) {
        if (!p.alive) continue;
        game::ShotView view;
        for (int i = 0; i < fighter_count() && i < game::kMatchFighterCount; ++i)
            if (p.owner == &m_match.fighter(i)) { view.owner = i; break; }
        view.bulletRow = p.bulletRow;
        view.pos = p.pos;
        view.color = p.color();
        view.modelMatrix = p.model_matrix();
        const auto* record = p.record();
        view.billboard = record && (record->stateFlags & 0x1000);
        view.tint = record ? record->combat[19] : 0;
        view.controller = p.model ? &p.controller : nullptr;
        view.textureOverrides = p.texture_overrides();
        visit(view);
    }
}

void LegacyBattle::for_each_spark(const std::function<void(const game::SparkView&)>& visit) const {
    for (const Spark& s : m_match.shots().sparks()) {
        if (!s.alive) continue;
        visit({s.pos, s.size(), s.color()});
    }
}

}  // namespace gameplay
