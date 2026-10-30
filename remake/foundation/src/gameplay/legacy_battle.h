#pragma once
// game::Battle over the hand-written simulation. Removed with it at M5 (docs/DIRECTION.md).
#include "game/battle_view.h"
#include "gameplay/match.h"

namespace gameplay {

class LegacyBattle final : public game::Battle {
public:
    // The seam for setup and tools that exist only on this path: nothing else may reach it.
    Match& match() { return m_match; }
    const Match& match() const { return m_match; }

    int fighter_count() const override { return m_match.config().fighterCount; }
    int side(int fighter) const override { return m_match.config().side[fighter]; }
    const game::FighterView& fighter(int index) const override { return m_match.fighter(index); }
    const MatchEconomy& economy() const override { return m_match.economy(); }
    int locked_target(int fighter) const override { return m_match.locked_target(fighter); }
    int aim_target(int fighter) const override { return m_match.aim_target(fighter); }
    int lock_pulse(int fighter) const override { return m_match.lock_pulse(fighter); }
    bool ai_enabled(int fighter) const override { return m_match.ai_enabled(fighter); }
    void for_each_shot(const std::function<void(const game::ShotView&)>& visit) const override;
    void for_each_spark(const std::function<void(const game::SparkView&)>& visit) const override;

    game::BattleFrame step(const fnd::input::PlayerState* inputs[game::kMatchFighterCount], double dt) override {
        return m_match.step(inputs, dt);
    }
    void set_paused(bool paused) override { m_match.set_paused(paused); }
    void begin_round_entry() override { m_match.begin_round_entry(); }
    void step_round_entry(double dt) override { m_match.step_round_entry(dt); }
    void cycle_locked_target(int fighter, bool forward) override { m_match.cycle_locked_target(fighter, forward); }
    void lock_ally_target(int fighter) override { m_match.lock_ally_target(fighter); }
    void set_primary_listener_fighter(int fighter) override { m_match.set_primary_listener_fighter(fighter); }

private:
    Match m_match;
};

}  // namespace gameplay
