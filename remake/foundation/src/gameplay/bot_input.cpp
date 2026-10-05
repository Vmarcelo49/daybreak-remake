// gameplay/bot_input.cpp — the host seam: Match state → BotView → input. See
// gameplay/bot_input.h; no decision is made here.
#include "gameplay/bot_input.h"

#include <cmath>

namespace gameplay {
namespace {

float xz_distance(const glm::vec3& a, const glm::vec3& b) {
    const float dx = a.x - b.x, dz = a.z - b.z;
    return std::sqrt(dx * dx + dz * dz);
}

}  // namespace

void buildBotView(BotView& view, const BotContext& ctx) {
    view = BotView{};
    if (!ctx.match) return;
    Match& m = *ctx.match;
    const int count = m.config().fighterCount;
    const int self_index = ctx.fighterIndex;
    if (self_index < 0 || self_index >= count) return;

    const Fighter& self = m.fighter(self_index);
    view.self = &self;
    // The stage channel the fighters themselves move through (issue #7), so the probes
    // answer exactly what the movement sweep will do.
    view.collision = ctx.collision ? ctx.collision : m.collision();
    view.leaderTarget = ctx.leaderTarget;

    // The combat target: the fighter's own lock when it is a living hostile, else the
    // nearest living hostile. Match::melee_target applies exactly that rule, excludes
    // allies unconditionally and skips a fighter still in its airborne respawn re-entry
    // (FUN_0041f580's +0xaecb), which is what the brain must retarget around.
    const int target = m.melee_target(self_index);
    if (target != kNoTarget) {
        view.targetIndex = target;
        view.target = &m.fighter(target);
        view.targetAlive = view.target->is_alive();
    }

    for (int j = 0; j < count; ++j) {
        if (j == self_index) continue;
        const bool ally = m.config().side[j] == m.config().side[self_index];
        if (ally) {
            if (view.partnerIndex < 0 && m.fighter(j).is_alive()) {
                view.partnerIndex = j;
                view.partner = &m.fighter(j);
                view.partnerAlive = true;
            }
        } else if (m.fighter(j).is_alive()) {
            ++view.hostileCount;
        }
    }

    // Threats: a hostile projectile already closing on this fighter, and an enemy whose
    // swing is live within its reach. Ally fire is never a threat — that is the same
    // exclusion the projectile pool and the melee pass apply.
    float nearest = 0.f;
    for (const Projectile& p : m.shots().shots()) {
        if (!p.alive || p.owner == nullptr) continue;
        int owner = -1;
        for (int j = 0; j < count; ++j)
            if (p.owner == &m.fighter(j)) { owner = j; break; }
        if (owner < 0 || m.config().side[owner] == m.config().side[self_index]) continue;
        const glm::vec3 d = self.position() - p.pos;
        if (d.x * p.vel.x + d.z * p.vel.z <= 0.f) continue;   // flying away from us
        const float dist = std::sqrt(d.x * d.x + d.z * d.z);
        if (dist > BotBrain::kThreatHorizon) continue;
        if (nearest == 0.f || dist < nearest) {
            nearest = dist;
            view.threats |= kBotThreatShot;
        }
    }
    for (int j = 0; j < count; ++j) {
        if (j == self_index) continue;
        if (m.config().side[j] == m.config().side[self_index]) continue;
        const Fighter& enemy = m.fighter(j);
        if (!enemy.is_alive()) continue;
        if (enemy.state() != FighterState::AttackA || !enemy.melee_in_active()) continue;
        const float dist = xz_distance(enemy.position(), self.position());
        if (dist > FighterConstants::kMeleeRange * 1.2f) continue;
        if (nearest == 0.f || dist < nearest) {
            nearest = dist;
            view.threats |= kBotThreatMelee;
        }
    }
    view.threatDistance = nearest;
}

void updateBotInput(BotBrain& brain, const BotContext& ctx, fnd::input::PlayerState& input,
                    uint64_t tick) {
    BotView view;
    buildBotView(view, ctx);
    const BotDecision& decision = brain.update(view, tick);

    // The brain only REQUESTS a switch: the lock table is the match's, and the recovered
    // 15-tick pulse protects a fresh selection from being re-picked (FUN_0041f580:218),
    // exactly as it does for the viewer's own tap.
    if (decision.retarget && ctx.match && ctx.match->lock_pulse(ctx.fighterIndex) == 0)
        ctx.match->cycle_locked_target(ctx.fighterIndex);

    BotBrain::apply(decision, input);
}

}  // namespace gameplay
