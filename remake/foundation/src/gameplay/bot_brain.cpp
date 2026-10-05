// gameplay/bot_brain.cpp — the COM decision state. See bot_brain.h for the recovered
// evidence (addresses, offsets, the six tactic cells and their weights) and for the list
// of provisional port rules.
#include "gameplay/bot_brain.h"

#include <algorithm>
#include <cmath>

namespace gameplay {
namespace {

float xz_distance(const glm::vec3& a, const glm::vec3& b) {
    const float dx = a.x - b.x, dz = a.z - b.z;
    return std::sqrt(dx * dx + dz * dz);
}

// The eight intents the recovered +0x278/+0x27c pair can express (FUN_00421780 maps them
// onto the eight 45° yaw steps). Ordered as the port's (forward, right) pairs.
struct Intent { float forward; float right; };
constexpr Intent kIntent8[8] = {
    { 1.f,  0.f}, { 1.f,  1.f}, { 0.f,  1.f}, {-1.f,  1.f},
    {-1.f,  0.f}, {-1.f, -1.f}, { 0.f, -1.f}, { 1.f, -1.f},
};

}  // namespace

BotTactic bot_tactic_from_cell(int cell) {
    return static_cast<BotTactic>(((cell % kBotTacticCells) + kBotTacticCells) %
                                  kBotTacticCells);
}

const char* bot_tactic_name(BotTactic t) {
    switch (t) {
        case BotTactic::Adaptive: return "adaptive";
        case BotTactic::Melee:    return "melee";
        case BotTactic::Shoot:    return "shoot";
        case BotTactic::Focus:    return "focus";
        case BotTactic::Separate: return "separate";
        case BotTactic::Retreat:  return "retreat";
    }
    return "adaptive";
}

// FUN_0043f4d0:22-63: the three locals each cell assigns before the RNG gates run.
BotTacticWeights bot_tactic_weights(BotTactic t) {
    switch (t) {
        case BotTactic::Melee:   return {0.25f,  50, 200};
        case BotTactic::Shoot:   return {2.5f,  200,  50};
        case BotTactic::Retreat: return {7.0f,    5,   5};
        case BotTactic::Focus:
        case BotTactic::Separate:
        case BotTactic::Adaptive:
        default:                 return {1.0f,  100, 100};
    }
}

// PROVISIONAL, see bot_brain.h: the original randomises one of three AI classes per COM
// slot (FUN_006492f0:14-38) instead of offering a difficulty.
BotTuning bot_tuning(BotDifficulty d) {
    switch (d) {
        case BotDifficulty::Relaxed: return {24,  60, 40, 25};
        case BotDifficulty::Sharp:   return { 6, 130, 90, 75};
        case BotDifficulty::Standard:
        default:                     return {12, 100, 70, 50};
    }
}

const char* bot_action_name(BotAction a) {
    switch (a) {
        case BotAction::Idle:       return "idle";
        case BotAction::Approach:   return "approach";
        case BotAction::Retreat:    return "retreat";
        case BotAction::Strafe:     return "strafe";
        case BotAction::Reposition: return "reposition";
        case BotAction::Jump:       return "jump";
        case BotAction::Guard:      return "guard";
        case BotAction::Evade:      return "evade";
        case BotAction::Melee:      return "melee";
        case BotAction::Shoot:      return "shoot";
        case BotAction::Hyper:      return "hyper";
    }
    return "idle";
}

void BotBrain::reset(uint64_t seed, BotDifficulty difficulty) {
    m_rng.set_state(seed);
    m_tactic = BotTactic::Adaptive;
    m_difficulty = difficulty;
    m_decision = BotDecision{};
    m_stats = BotStats{};
    m_strafeTicks = m_advanceTicks = m_airTicks = m_powerTicks = 0;
    m_meleeCooldown = m_shotCooldown = m_retargetCooldown = m_planTicks = 0;
    m_guardTicks = m_dashPhase = m_dashDir = 0;
    m_dashAction = BotAction::Evade;
    m_shotHoldTicks = 0;
    m_releasePending = false;
    m_shotTier = ShotTier::Tap;
    m_intentForward = m_intentRight = 0.f;
    m_navForward = m_navRight = 0.f;
    m_navTicks = 0;
    m_planAction = BotAction::Idle;
    m_navAction = BotAction::Idle;
    m_blockedTicks = 0;
    m_slideSide = 0;
    m_haveLastPos = false;
    m_lastPos[0] = m_lastPos[1] = m_lastPos[2] = 0.f;
    m_axisValue[0] = m_axisValue[1] = 0.f;
    m_lastAxisChange[0] = m_lastAxisChange[1] = 0;
}

void BotBrain::set_difficulty(BotDifficulty d) { m_difficulty = d; }

void BotBrain::set_tactic(BotTactic t) {
    if (m_tactic == t) return;
    m_tactic = t;
    // A new cell is a new plan, and the power-attack window belonged to the old one.
    m_planTicks = 0;
    m_powerTicks = 0;
}

void BotBrain::apply(const BotDecision& d, fnd::input::PlayerState& in) {
    for (bool& down : in.down) down = false;
    if (d.moveRight < -0.5f) in.down[fnd::input::Left]  = true;
    if (d.moveRight >  0.5f) in.down[fnd::input::Right] = true;
    if (d.moveForward >  0.5f) in.down[fnd::input::Up]   = true;
    if (d.moveForward < -0.5f) in.down[fnd::input::Down] = true;
    in.down[fnd::input::AttackA] = d.melee;
    in.down[fnd::input::Jump]    = d.jump;
    in.down[fnd::input::Guard]   = d.guard;
    in.down[fnd::input::Shoot]   = d.shoot;
    in.down[fnd::input::Special] = d.hyper;
    fnd::input::compute_edges(in);
}

glm::vec3 BotBrain::world_dir(const BotView& v, float right, float forward) const {
    // The port's lock-on basis (fighter.cpp facing_relative): screen-up is the facing.
    const float yaw = v.self ? v.self->facing_yaw() : 0.f;
    const float fx = std::sin(yaw), fz = std::cos(yaw);
    return glm::vec3(fz * right + fx * forward, 0.f, -fx * right + fz * forward);
}

// How much of a step in `dir` the stage actually allows. The swept move slides along
// walls (physics/raycast.h), so the projection onto the requested direction is what says
// "this way is open": a slide around a corner still projects most of its length.
float BotBrain::probe_progress(const BotView& v, const glm::vec3& dir, float distance) const {
    if (!v.collision || !v.self || distance <= 0.f) return distance;
    const glm::vec3 from = v.self->position();
    const glm::vec3 want = from + dir * distance;
    const game::physics::MovementResult r =
        v.collision->move(from, want, !v.self->airborne());
    const float dx = r.position.x - from.x, dz = r.position.z - from.z;
    return dx * dir.x + dz * dir.z;
}

ShotTier BotBrain::pick_shot_tier(const Fighter& self, float dist) const {
    // PORT RULE. The recovered shot request is a 0..19 charge value (+0x2b8, consumed at
    // FUN_0043ded0:159-210), not a tier id, so which of the port's three tiers a distance
    // calls for is design. Far shots take the strongest tier its own stock can pay for.
    if (dist > 600.f && self.can_fire(ShotTier::Red))    return ShotTier::Red;
    if (dist > 250.f && self.can_fire(ShotTier::Yellow)) return ShotTier::Yellow;
    if (self.can_fire(ShotTier::Tap))    return ShotTier::Tap;
    if (self.can_fire(ShotTier::Yellow)) return ShotTier::Yellow;
    if (self.can_fire(ShotTier::Red))    return ShotTier::Red;
    return ShotTier::Tap;
}

int BotBrain::hold_ticks(const Fighter& self, ShotTier tier) const {
    if (tier == ShotTier::Tap) return 1;
    const float seconds = (tier == ShotTier::Red) ? self.red_hold_sec() : self.yellow_hold_sec();
    const int ticks = static_cast<int>(std::ceil(seconds * (float)kTicksPerSecond)) + 3;
    return std::max(2, ticks);
}

bool BotBrain::run_dash_commitment() {
    // The port's double tap, three ticks: press the direction, release, press again. The
    // second press is what try_dash() chains on (fighter.cpp's kDoubleTapSec window).
    if (m_dashPhase == 0) return false;
    const bool press = (m_dashPhase == 1 || m_dashPhase == 3);
    if (press) {
        m_decision.moveRight   = (m_dashDir == 2) ? -1.f : (m_dashDir == 3 ? 1.f : 0.f);
        m_decision.moveForward = (m_dashDir == 0) ?  1.f : (m_dashDir == 1 ? -1.f : 0.f);
        m_decision.action = m_dashAction;
    }
    ++m_dashPhase;
    if (m_dashPhase > 3) {
        m_dashPhase = 0;
        ++m_stats.dashStarts;
    }
    return true;
}

bool BotBrain::run_shot_commitment(const BotView& v) {
    if (m_shotHoldTicks > 0) {
        m_decision.action = BotAction::Shoot;
        m_decision.tier   = m_shotTier;
        m_decision.shoot  = true;
        if (--m_shotHoldTicks == 0) m_releasePending = true;
        apply_nav(v);   // charging is mobile: keep closing/opening while it holds
        return true;
    }
    if (!m_releasePending) return false;
    // The release tick: the fighter's state machine calls try_fire() when the key is up.
    // can_fire() here is exactly the gate fire_shot() applies on this same tick, so a
    // refused release is counted and locked out instead of retried.
    m_releasePending = false;
    m_decision.action = BotAction::Shoot;
    m_decision.tier   = m_shotTier;
    m_decision.shoot  = false;
    if (v.self && v.self->can_fire(m_shotTier)) {
        ++m_stats.shotsFired;
        m_shotCooldown = kShotSpacingTicks;
    } else {
        ++m_stats.shotBlocked;
        m_shotCooldown = kShotRejectTicks;
    }
    apply_nav(v);
    return true;
}

bool BotBrain::run_guard_commitment(const BotView& v) {
    if (m_guardTicks <= 0) return false;
    // Release as soon as the fighter cannot hold the block any more (issue #6: the
    // exhaustion latch only clears on a release). Holding through it would pin the
    // fighter in the exhausted state, which is the stuck-player bug that fix removed.
    if (!v.self || !v.self->actionable() || v.self->guard_exhausted() ||
        v.self->stamina() <= 0) {
        m_guardTicks = 0;
        return false;
    }
    m_decision.action = BotAction::Guard;
    m_decision.guard  = true;
    --m_guardTicks;
    return true;
}

const BotDecision& BotBrain::update(const BotView& view, uint64_t tick) {
    compute(view, tick);
    stabilise_movement(tick);
    return m_decision;
}

// The decision half of a tick. Every path fills m_decision and returns; the key
// stabiliser runs afterwards, once, in update().
void BotBrain::compute(const BotView& view, uint64_t tick) {
    (void)tick;   // the recovered timers count ticks, so no absolute clock is needed
    m_decision = BotDecision{};
    m_decision.tactic = m_tactic;
    ++m_stats.ticks;

    const Fighter* self = view.self;
    if (!self || !self->is_alive()) {
        m_decision.action = BotAction::Idle;
        return;
    }

    // ---- timers (the recovered jitter windows step one per tick) ----
    if (m_meleeCooldown > 0)    --m_meleeCooldown;
    if (m_shotCooldown > 0)     --m_shotCooldown;
    if (m_retargetCooldown > 0) --m_retargetCooldown;
    if (m_strafeTicks > 0) --m_strafeTicks; else if (m_strafeTicks < 0) ++m_strafeTicks;
    if (m_advanceTicks > 0) --m_advanceTicks; else if (m_advanceTicks < 0) ++m_advanceTicks;
    if (m_airTicks > 0)   --m_airTicks;
    if (m_powerTicks > 0) --m_powerTicks;

    // Progress bookkeeping for the acceptance evidence ("no bot stuck"): the distance
    // this fighter actually covered, whatever the reason.
    if (m_haveLastPos) {
        m_stats.distanceMoved +=
            xz_distance(self->position(), glm::vec3(m_lastPos[0], m_lastPos[1], m_lastPos[2]));
    }
    m_lastPos[0] = self->position().x;
    m_lastPos[1] = self->position().y;
    m_lastPos[2] = self->position().z;
    m_haveLastPos = true;

    const bool hasTarget = view.target != nullptr && view.targetAlive;
    const float dist = hasTarget ? xz_distance(self->position(), view.target->position()) : 0.f;
    // The reach of the swing this fighter would press right now, kept for the per-tick
    // overrun stop in apply_nav (the plan's own copy is only re-read every reactionTicks).
    m_lastDist = hasTarget ? dist : 0.f;
    m_lastReach = self->melee_reach(self->state() == FighterState::Run, self->airborne());

    // ---- target maintenance (FUN_00421c80 and cells 3/4) ----
    // The brain only REQUESTS: the host owns the lock table and applies the recovered
    // cycle, bounded by its 15-tick pulse (target_lock.h).
    bool wantSwitch = false;
    if (view.hostileCount > 0) {
        if (!hasTarget) {
            wantSwitch = true;
        } else if (view.leaderTarget >= 0 && view.hostileCount > 1) {
            // 各個 separates from the leader, 集中 concentrates on its target
            // (FUN_0043f4d0:46-57).
            if (m_tactic == BotTactic::Separate && view.targetIndex == view.leaderTarget)
                wantSwitch = true;
            if (m_tactic == BotTactic::Focus && view.targetIndex != view.leaderTarget)
                wantSwitch = true;
        }
    }
    if (wantSwitch && m_retargetCooldown == 0) {
        m_decision.retarget = true;
        m_retargetCooldown = kRetargetCooldownTicks;
        ++m_stats.retargets;
    }

    // ---- commitments own the tick while they run ----
    if (run_dash_commitment()) return;
    if (run_guard_commitment(view)) return;
    // A swing is a single-tick press, so it is evaluated EVERY tick rather than at plan
    // boundaries (the original's think function runs every tick too): a target that steps
    // into reach between two plans must still be hit. It may interrupt a charge hold —
    // the state change drops the charge, which is what a player's attack does as well.
    if (try_melee(view, dist)) {
        m_shotHoldTicks = 0;
        m_releasePending = false;
        return;
    }
    if (run_shot_commitment(view)) return;

    // ---- plan ----
    if (m_planTicks <= 0) {
        plan(view, dist);
        m_planTicks = std::max(1, bot_tuning(m_difficulty).reactionTicks);
        m_navTicks = 0;   // a new plan re-probes its own direction
    }
    --m_planTicks;

    // ---- navigation (probes the stage; may replace the intent) ----
    navigate(view);
}

// PORT RULE, and a load-bearing one: the port's dash is a DOUBLE TAP of the same direction
// key inside kDoubleTapSec (0.30 s, fighter.cpp), and a COM writes the keys directly. The
// recovered lateral jitter flips that key every couple of hundred ticks, but the plan
// window (12 ticks) re-emits the axes at plan boundaries, so a key could be released and
// pressed again 12 ticks later — a dash the brain never asked for. Measured before this
// guard: a bot pinned against a wall was in the committed Run state at almost every
// sample, dashing into the wall instead of sliding around it.
//
// The guard therefore holds an axis' previous key until the double-tap window has passed
// since that axis last changed, so only run_dash_commitment()'s deliberate tap-gap-tap can
// chain. It never stops a movement: it only delays a direction change by at most 21 ticks.
void BotBrain::stabilise_movement(uint64_t tick) {
    float* axis[2] = {&m_decision.moveForward, &m_decision.moveRight};
    for (int a = 0; a < 2; ++a) {
        float& want = *axis[a];
        if (m_dashPhase != 0) {   // the deliberate dash owns the keys this tick
            m_axisValue[a] = want;
            m_lastAxisChange[a] = tick;
            continue;
        }
        if (want == m_axisValue[a]) continue;
        if (tick - m_lastAxisChange[a] < (uint64_t)kKeyFlipTicks) {
            want = m_axisValue[a];   // too soon to move that key again: keep the old one
            continue;
        }
        m_axisValue[a] = want;
        m_lastAxisChange[a] = tick;
    }
}

// The melee press: the recovered reach of the swing it would start (FUN_0063b470's
// bodyRadius + the move's hitRadius) is the ONLY range test, and the cell's engage weight
// still gates it, so a 後退 COM does not suddenly brawl. A refused press (mid-move) is
// counted and locked out instead of retried on the next tick.
bool BotBrain::try_melee(const BotView& v, float dist) {
    if (!v.self || !v.target || !v.targetAlive) return false;
    if (m_meleeCooldown > 0) return false;
    const Fighter& self = *v.self;
    const BotTacticWeights w = bot_tactic_weights(m_tactic);
    const BotTuning tune = bot_tuning(m_difficulty);
    const int engage = std::min(100, w.engageWeight * tune.engageScale / 100);
    if ((int)m_rng.below(100) >= engage) return false;

    // The FULL reach (bodyRadius + the move's hitRadius) is what try_melee_hit() tests, so
    // the press uses it as-is; the movement stop keeps the 0.9 margin so the COM settles
    // just inside the window instead of at its edge.
    const bool dashAttack = self.state() == FighterState::Run;
    const float reach = self.melee_reach(dashAttack, self.airborne());
    if (dist > reach) return false;
    if (!self.actionable()) {
        ++m_stats.meleeBlocked;
        m_meleeCooldown = 4;
        return false;
    }
    m_decision.melee = true;
    m_decision.action = BotAction::Melee;
    m_meleeCooldown = kMeleeCooldownTicks;
    m_planAction = BotAction::Melee;
    ++m_stats.meleePresses;
    return true;
}

void BotBrain::plan(const BotView& v, float dist) {
    ++m_stats.plans;
    const Fighter& self = *v.self;
    const BotTacticWeights w = bot_tactic_weights(m_tactic);
    const BotTuning tune = bot_tuning(m_difficulty);
    m_decision.action = BotAction::Idle;

    const bool hasTarget = v.target != nullptr && v.targetAlive;

    // The recovered advance/retreat re-roll (FUN_0043f4d0:142-181): the threshold scales
    // with rangeScale and a far target biases the timer positive (advance).
    if (m_advanceTicks == 0 && hasTarget) {
        const float limit = kAdvanceRange * w.rangeScale;
        const int roll = m_rng.below(300);
        m_advanceTicks = (dist > limit) ? roll - 60 : roll - 240;
    }
    if (m_strafeTicks == 0) m_strafeTicks = m_rng.below(400) - 200;
    // The two ARMING rolls below are per-TICK in the original (its think function runs
    // every tick) while this port re-plans every `reactionTicks`, so the bound is divided
    // by the plan window to keep the same per-tick rate — and with it the window's duty
    // cycle, which is what makes the AI use it at all: 1/450 per tick over 180..359 ticks
    // means the recovered power window is open better than half the time. Rolling once per
    // 450 PLANS instead opened it about once every 90 s and the COM never dashed in.
    const int window = std::max(1, tune.reactionTicks);
    // The recovered airborne reposition window (FUN_0043f4d0:78-96): airborne, far, a
    // high resource, at 1%.
    if (m_airTicks == 0 && self.airborne() && dist > kAirRange &&
        self.hyper_gauge() > 0.65f && m_rng.below(std::max(1, 100 / window)) == 1)
        m_airTicks = m_rng.below(120) + 10;
    // The recovered power-attack window (+0x870, :93-104).
    if (m_powerTicks == 0 && hasTarget && dist < kPowerRange &&
        m_rng.below(std::max(1, 450 / window)) == 0)
        m_powerTicks = m_rng.below(180) + 180;

    // The movement intent, from the recovered timer signs (+0x868 < 0 → +0x27c = +1,
    // :130; +0x868 > 0 → +0x27c = -1, :166; FUN_00421780 maps the -1 onto the forward
    // step of the same basis the port's Up key uses, so a positive timer advances).
    // Computed BEFORE the actions because charging is mobile in this port (fighter.cpp:
    // the charge accumulates without leaving the state) and a COM that stands still to
    // charge never closes. 後退 (rangeScale 7) keeps the line open; 格闘 (0.25) closes it.
    const bool dashAttack = self.state() == FighterState::Run;
    const float reach = self.melee_reach(dashAttack, self.airborne()) * 0.9f;
    float forward = (m_advanceTicks > 0) ? 1.f : (m_advanceTicks < 0 ? -1.f : 0.f);
    float right = (m_strafeTicks < 0) ? -1.f : (m_strafeTicks > 0 ? 1.f : 0.f);
    if (!hasTarget) forward = 0.f;
    // A retreating cell must not be dragged forward by the jitter: its whole point is the
    // distance it keeps.
    if (w.rangeScale > 1.0f && forward > 0.f) forward = 0.f;
    if (w.rangeScale < 1.0f && forward < 0.f) forward = 0.f;
    // PORT RULE: a COM that keeps walking while its target is already inside its swing
    // overruns it and bounces back and forth (measured: it crossed a 240-unit gap eleven
    // times in 900 ticks and never pressed). The recovered walk is a distance band, not a
    // footsies rule, so this only stops the forward push once the swing can already
    // connect and leaves the lateral jitter alone.
    if (hasTarget && dist <= reach) forward = 0.f;
    // PORT RULE: outside the cell's engagement band the jitter is dropped and the advance
    // is forced. The recovered timer is a biased random walk around the band edge
    // (500 * rangeScale, FUN_0043f4d0:154) that can spend up to 240 ticks — seconds of
    // walking — heading away from a target it has already lost, because only the re-roll
    // looks at the distance. A COM that never comes back cannot finish a match, which is
    // this issue's acceptance test; inside the band the recovered walk is untouched.
    const float band = kAdvanceRange * w.rangeScale;
    if (hasTarget && dist > band * 1.6f) {
        forward = 1.f;
        right = 0.f;
    } else if (hasTarget && w.rangeScale > 1.0f && dist < band * 0.5f) {
        forward = -1.f;   // 射撃/後退 keep their line even when the jitter says otherwise
    }
    m_intentForward = forward;
    m_intentRight = right;
    m_planAction = (forward > 0.f) ? BotAction::Approach
                 : (forward < 0.f) ? BotAction::Retreat
                 : (right != 0.f)  ? BotAction::Strafe : BotAction::Idle;

    // ---- defence first ----
    if (hasTarget && v.threats != kBotThreatNone && v.threatDistance > 0.f &&
        v.threatDistance < kThreatHorizon && self.actionable()) {
        if (!self.guard_exhausted() && self.stamina() > 0 &&
            (int)m_rng.below(100) < tune.guardWeight) {
            m_guardTicks = 14;
            ++m_stats.guards;
            m_intentForward = 0.f;   // a held block is not a moving action
            m_intentRight = 0.f;
            run_guard_commitment(v);   // take this tick rather than waiting for the next
            m_planAction = BotAction::Guard;
            return;
        }
        if ((int)m_rng.below(100) < tune.evadeWeight && m_dashPhase == 0 &&
            self.stamina() >= (int)FighterConstants::kDashStamina) {
            // A committed dash leaves the swing; the navigation probe rotates the
            // direction if the stage is in the way.
            m_dashDir = (m_rng.below(2) == 0) ? 2 : 3;   // Left / Right
            m_dashAction = BotAction::Evade;
            m_dashPhase = 1;
            ++m_stats.evades;
            run_dash_commitment();
            m_planAction = BotAction::Evade;
            return;
        }
    }

    // ---- offence ----
    // The press itself is try_melee()'s (every tick); what is planned here is the
    // committed approach. The in-range power branch is FUN_0043f4d0:194's
    // `rng % 100 < powerWeight` gate, and the engage gate below is :235's.
    const int engage = std::min(100, w.engageWeight * tune.engageScale / 100);
    const int power = std::min(100, w.powerWeight * tune.engageScale / 100);
    if (hasTarget && (int)m_rng.below(100) < engage) {
        // The dash is a LUNGE, so it only starts from outside the swing (a committed dash
        // runs its locked direction for kDashFrames at 900 u/s — roughly 280 units — and
        // from inside the reach it would carry the COM straight past its target) and never
        // while one is already committed.
        if (m_powerTicks > 0 && dist < kPowerRange && dist > reach * 2.f &&
            self.actionable() && self.state() != FighterState::Run &&
            self.stamina() >= (int)FighterConstants::kDashStamina && m_dashPhase == 0 &&
            (int)m_rng.below(100) < power) {
            m_dashDir = 0;   // Up = forward
            m_dashAction = BotAction::Approach;
            m_dashPhase = 1;
            run_dash_commitment();
            m_planAction = BotAction::Approach;
            return;
        }
    }

    // ---- shooting ----
    // Outside the swing's reach, inside the cell's engagement band (a target beyond it is
    // closed on first: firing locks the fighter in its 20-tick firing pose, so a COM that
    // shoots at any range never arrives), with the line to the target actually open, and
    // with the fighter's own legal tiers. The line test is the recovered player+0x80 sense
    // (FUN_0042cc90's ray toward the target): a shot into a wall the position probe cannot
    // see would only lock the fighter in its firing pose again. can_fire() is the gate
    // fire_shot() applies, so a request is never silently lost. The movement intent above
    // is KEPT: the charge is mobile, so a COM closes while it charges.
    const float los = std::max(kProbeDistance, std::min(dist, 600.f));
    const bool lineOpen =
        hasTarget && probe_progress(v, world_dir(v, 0.f, 1.f), los) >= los * 0.7f;
    // PORT RULE for 格闘 (rangeScale < 1): taps only, and only while still outside the
    // band. The original's shot request is one of the acts of its movement branch
    // (+0x2b8), so a melee AI keeps it light; the port's charge-and-release costs the
    // fighter a 20-tick firing pose plus the hold, which would keep a brawler out of its
    // own 50-unit reach. Everything else uses the full tiers.
    const bool meleeCell = w.rangeScale < 1.0f;
    const float shootBand = meleeCell ? band * 1.5f : band * 1.6f;
    if (lineOpen && dist <= shootBand && dist > reach && m_shotHoldTicks == 0 &&
        !m_releasePending && m_shotCooldown == 0 && self.actionable()) {
        const ShotTier tier = meleeCell ? ShotTier::Tap : pick_shot_tier(self, dist);
        if (self.can_fire(tier)) {
            m_shotTier = tier;
            m_shotHoldTicks = hold_ticks(self, tier);
            ++m_stats.shotsStarted;
            run_shot_commitment(v);
            m_planAction = BotAction::Shoot;
            return;
        }
        // The gate said no: wait out the reload/recharge instead of asking every tick.
        ++m_stats.shotBlocked;
        m_shotCooldown = kShotRejectTicks;
    }

    // ---- hypermode ----
    // The port's own gauge rule (hyper_ready) with the recovered shape: the original's
    // think gates its committed moves on the 0..1000 resource (+0x834) and only commits
    // when the target is close. Which cell fires it is not recovered.
    if (hasTarget && self.hyper_ready() && self.actionable() && dist < kHyperRange) {
        m_decision.hyper = true;
        ++m_stats.hypers;
        m_intentForward = 0.f;
        m_intentRight = 0.f;
        m_planAction = BotAction::Hyper;
        return;
    }
}

void BotBrain::navigate(const BotView& v) {
    // A dash carries its own locked direction (the fighter commits to m_dashDir), so the
    // navigation must not fight it.
    if (m_dashPhase != 0) return;

    // The recovered airborne reposition (+0x86c): hold jump to climb toward a target
    // above, release to fall back to one below.
    if (m_airTicks > 0 && v.self && v.self->airborne() && v.target) {
        m_decision.action = BotAction::Reposition;
        m_decision.jump = v.target->position().y > v.self->position().y;
        return;
    }

    apply_nav(v);
    m_decision.action = m_navAction;
}

// The probed movement half, shared by the plan's own tick and by the commitments that
// may move while they run (a charge hold).
void BotBrain::apply_nav(const BotView& v) {
    if (m_navTicks <= 0) {
        choose_nav(v);
        m_navTicks = std::max(4, bot_tuning(m_difficulty).reactionTicks / 2);
    }
    --m_navTicks;
    m_decision.moveForward = m_navForward;
    m_decision.moveRight   = m_navRight;
    // The per-tick half of the overrun stop: the moment the target is inside the swing,
    // the forward push ends, so the plan window cannot carry the COM past it.
    if (m_lastDist > 0.f && m_lastReach > 0.f && m_lastDist <= m_lastReach * 0.9f)
        m_decision.moveForward = 0.f;
}

// Probes the intent's world direction and, when the stage refuses it, searches the
// eight-way table for an open one. PORT RULE: the original has no path search — its only
// obstacle input is the +0x80 line distance (FUN_0042cc90) — so the rotation order and
// the bounded recovery here are the port's answer to the issue's "must not remain blocked
// at a wall or corner", built on the #7 sweeps.
void BotBrain::choose_nav(const BotView& v) {
    m_navForward = m_intentForward;
    m_navRight = m_intentRight;
    m_navAction = m_planAction;
    if (m_intentForward == 0.f && m_intentRight == 0.f) return;

    const float open = kProbeDistance * kProbeOpenFraction;
    const bool targetOpen = probe_progress(v, world_dir(v, 0.f, 1.f), kProbeDistance) >= open;
    if (targetOpen) m_slideSide = 0;   // the way to the target is clear again

    if (probe_progress(v, world_dir(v, m_intentRight, m_intentForward), kProbeDistance) >= open) {
        m_blockedTicks = 0;
        return;
    }

    // Blocked. Rotate around a reference direction, KEEPING the side that worked: a wall is
    // followed in one direction rather than re-rolled every probe, which would slide back
    // and forth along the same face and never clear its end (measured: 3000 ticks of that
    // never reached a target behind a 1200-unit wall). The first choice is the RNG's, so
    // two bots in the same corner do not both turn the same way.
    ++m_stats.blockedTicks;
    ++m_blockedTicks;
    // When the TARGET line is what is blocked, rotate that (walk around the obstacle);
    // when only the plan's own intent is blocked, rotate the intent. The reference's index
    // in the recovered eight-way table is the rotation's origin.
    const float refRight   = targetOpen ? m_intentRight : 0.f;
    const float refForward = targetOpen ? m_intentForward : 1.f;
    int ref = 0;
    for (int i = 0; i < 8; ++i)
        if (kIntent8[i].right == refRight && kIntent8[i].forward == refForward) { ref = i; break; }
    const int side = (m_slideSide != 0) ? m_slideSide : ((m_rng.below(2) == 0) ? 1 : -1);
    for (int step = 1; step < 8; ++step) {
        const int idx = ((ref + step * side) % 8 + 8) % 8;
        const Intent& in = kIntent8[idx];
        if (probe_progress(v, world_dir(v, in.right, in.forward), kProbeDistance) >= open) {
            m_navForward = in.forward;
            m_navRight = in.right;
            m_slideSide = side;
            ++m_stats.directionChanges;
            m_blockedTicks = 0;
            return;
        }
    }

    // Every probed direction is closed: this is a corner. The bounded recovery jumps (the
    // recovered +0x86c shape) and forces a re-plan, so a bot cannot grind against a wall
    // without the trace showing it.
    if (m_blockedTicks >= kStuckRecoveryTicks) {
        if (v.self && !v.self->airborne() && v.self->actionable() &&
            v.self->stamina() >= (int)FighterConstants::kJumpStamina) {
            m_decision.jump = true;
            m_navAction = BotAction::Jump;
            ++m_stats.jumps;
        }
        ++m_stats.stuckRecoveries;
        m_blockedTicks = 0;
        m_slideSide = 0;   // pinned: try the other side of the corner next
        m_planTicks = 0;   // a different plan may want a different direction
    }
}

}  // namespace gameplay
