#pragma once
// gameplay/bot_brain.h — the COM participant's decision state (issue #14).
//
// WHY THIS REPLACES THE SPARRING POLICY: the old gameplay/bot_input.h walked at the
// opponent and pressed melee/shoot/special on fixed frame modulos. It matched nothing in
// the binary, ignored collision, ammo, stamina and the partner, and its presses were
// dropped by the state machine whenever the fighter was busy — the "repeatedly uses
// unavailable moves" failure the issue names.
//
// WHAT IS RECOVERED (research/decompiled, addresses as cited; branches re-checked with
// `objdump -d -M intel` on Higurashi-Daybreak/DaybreakDX.exe when the decompiled text was
// ambiguous):
//
//   * A COM participant is an ordinary player object driven by a per-character AI class.
//     FUN_006492f0:14-38 picks that class with the shared MT19937 (FUN_0065d150): slots 2
//     and 3 draw `rng % 3`, reduced to `% 2` for characters 0 (rena) and 4 (rika), and
//     FUN_00649790(command=characterId, kind) builds the object from the class table at
//     0x6a4e10. The think implementations are FUN_0043f4d0, FUN_00447730 (byte-identical
//     to 0x43f4d0), FUN_0044efd0 and FUN_00460d90.
//
//   * THE TACTIC CELL. Player +0x310 is a 6-valued cell and +0x314 its HUD timer.
//     FUN_0041f580:291-295 cycles it `(cell + 1) % 6` on the Tactics press, mirrors it
//     onto player 0's cell and sets +0x314 = 2.0f (0x40000000). FUN_004201a0:13-15
//     drains +0x314 by 0.2/frame to -6.0; FUN_00644150:92-96 fades the readout with it.
//     The six cells are the HUD's boxed labels (ui/hud.cpp CommandLabel cells 0..5, drawn
//     as `cell % 4, cell / 4`). FUN_00421730:11 resets the cell to 0 at round start and
//     FUN_0063c2a0 case 0x2d writes it from a character script.
//
//   * THE PER-CELL WEIGHTS, read verbatim from FUN_0043f4d0:22-63 into three locals:
//       cell 0 (適当 unrestricted)  rangeScale 1.0  engageWeight 100  powerWeight 100
//       cell 1 (格闘 melee)         rangeScale 0.25 engageWeight  50  powerWeight 200
//       cell 2 (射撃 shooting)      rangeScale 2.5  engageWeight 200  powerWeight  50
//       cell 3 (集中 focus)         unchanged
//       cell 4 (各個 separate)      unchanged
//       cell 5 (後退 retreat)       rangeScale 7.0  engageWeight   5  powerWeight   5
//     `engageWeight` percent-gates the movement/attack branch (:235 `rng % 100 < w`),
//     `powerWeight` the in-range dash/charge branch (:194, inside `dist² < 250000`), and
//     `rangeScale` scales the 500-unit advance re-roll (`250000 * c² <= dist²`, :154) —
//     the distance at which the AI stops advancing: 125 units on 格闘, 500 on 適当, 1250
//     on 射撃, 3500 on 後退.
//
//   * THE DECISION INPUTS the think function reads, all recovered:
//       - squared XZ distance to its current target: FUN_0042d980 (its own +0x14/+0x1c
//         against the +0x38 target pointer) = dx² + dz²;
//       - the distance to the first surface along the line to that target, kept in
//         player+0x80: FUN_0042cc90 builds the direction from the angle to the target
//         (FUN_0042da80, degrees) and walks the mesh list with D3DXIntersect
//         (FUN_0042d2c0), keeping the smallest hit distance and defaulting to 10000.0.
//         The think function uses it as "is the target behind something" (:240
//         `dist² < blockDist²`);
//       - the airborne flag +0x84, the current move id +0xadec, the 0..1000 resource
//         +0x834 (gates `0x28a < +0x834` and `500 < +0x834` at :79,116) and the three
//         mode latches +0x844/+0x845/+0x846;
//       - the shared MT19937 FUN_0065d150 for every probability gate.
//
//   * THE DECISION OUTPUTS: a 3×3 movement direction in +0x278/+0x27c that FUN_00421780
//     maps onto eight 45° yaw steps for FUN_0042db10 to turn the fighter toward; attack
//     requests in +0x284/+0x288 (the act function consumes one and writes 0x14 = 20 back
//     into it at FUN_0043ded0:140-141 — a 20-tick re-request lockout, mirrored here as
//     kMeleeCooldownTicks); a retarget request in +0x28c; a shot request in +0x2b8
//     (0..19, consumed at FUN_0043ded0:159-210); a dash/charge selector in +0x830 (1..4
//     → air dash moves 0x14/0x17/0x18/0x1b, ground jump-forward 0x1e, FUN_0043ded0:61-107);
//     and four jitter timers:
//       +0x864 ∈ [-200,199] lateral strafe, re-rolled when it crosses 0 (:105-141);
//       +0x868 ∈ [-240,59] | [-60,239] advance/retreat, the sign chosen by the
//         rangeScale-scaled distance test (:142-181); a negative timer writes +0x27c = -1
//         (yaw 0 — toward the target) and a positive one +0x27c = +1 (:130 vs :166);
//       +0x86c ∈ [10,129] airborne reposition, armed at 1% when airborne, far, and the
//         resource high (:78-96, :182-188);
//       +0x870 ∈ [180,359] | [0,179] power-attack window (:93-104).
//
//   * TARGET SELECTION IS THE AI'S OWN. FUN_00421c80 (called by the think function for
//     cells 0/1/2/5) measures the squared distance to players 0 and 1, prefers whichever
//     is not busy (+0x7ac is the action counter), and writes +0x28c = 1 only when the pick
//     differs from its own +0x300: a retarget REQUEST. Cells 3 (集中) and 4 (各個) compare
//     the AI's +0x300 with player 0's and request a switch when they are equal (各個) or
//     different (集中). Control never transfers between fighters — issue #14's roadmap
//     finding; the tag/tactics voice keys are partner callouts, not a swap.
//
// WHAT IS A PORT RULE (provisional, labelled at each site):
//   * The original steers by absolute yaw (FUN_00421780/FUN_0042db10). This port's
//     fighters are lock-on facing-relative (#8): screen-up is the facing, which the match
//     keeps on the target. The brain emits the SAME intent — forward/back along the
//     target line, lateral strafe — through the port's four direction keys, and probes
//     the world direction that intent resolves to.
//   * The original has no path search: its only obstacle input is the +0x80 line
//     distance. The directional probes, the rotation search and the bounded stuck
//     recovery here are the port's answer to "must not remain blocked at a wall or
//     corner", built on the #7 collision sweeps.
//   * The ammo/stamina/reload/guard-exhaustion gates are the port's resource model
//     (issues #6/#9); the original gates on +0x834 and per-move cancel windows instead.
//   * DIFFICULTY: the original has no difficulty setting — it draws one of three AI
//     classes at random per COM slot (FUN_006492f0:14-38). BotDifficulty is a documented
//     port policy; Standard is the default and the only one the host uses.
//
// DETERMINISM: every random draw comes from this brain's own gameplay::MatchRng, seeded
// from the match seed and the fighter index. update() is a pure function of (state, view,
// tick) at the fixed 64 Hz tick — no clock, no frame time, no allocation.
#include <cstdint>

#include <glm/glm.hpp>

#include "gameplay/fighter.h"
#include "gameplay/rng.h"
#include "input/input.h"
#include "physics/raycast.h"

namespace gameplay {

// The recovered tactic cells (player+0x310, FUN_0041f580:291-295), in HUD cell order.
enum class BotTactic : int {
    Adaptive = 0,   // 適当
    Melee    = 1,   // 格闘
    Shoot    = 2,   // 射撃
    Focus    = 3,   // 集中
    Separate = 4,   // 各個
    Retreat  = 5,   // 後退
};

inline constexpr int kBotTacticCells = 6;

// Cell index → HUD cell (ui::HudIcon::CommandLabel): identity by construction, which is
// what makes the readout and the decision one value rather than two.
inline int bot_tactic_cell(BotTactic t) { return static_cast<int>(t); }
BotTactic bot_tactic_from_cell(int cell);
const char* bot_tactic_name(BotTactic t);   // ASCII label for traces/logs

// The three recovered per-cell numbers (FUN_0043f4d0:22-63).
struct BotTacticWeights {
    float rangeScale;   // distance multiplier for the advance/retreat re-roll
    int   engageWeight; // percent gate on the movement/attack branch
    int   powerWeight;  // percent gate on the in-range dash/charge branch
};
BotTacticWeights bot_tactic_weights(BotTactic t);

// PROVISIONAL difficulty policy (the original randomises one of three AI classes per COM
// slot instead — FUN_006492f0). `reactionTicks` is how long one plan is held,
// `engageScale` a percent multiplier on the recovered weights, and guardWeight/evadeWeight
// the defensive chances per defended tick.
enum class BotDifficulty : int { Relaxed = 0, Standard = 1, Sharp = 2 };

struct BotTuning {
    int reactionTicks;
    int engageScale;
    int guardWeight;
    int evadeWeight;
};
BotTuning bot_tuning(BotDifficulty d);

// The per-fighter brain seed. Two COMs sharing a stream would decide in lockstep (a
// trace shows it immediately as mirrored bots), and the whole match must still replay
// from one seed, so the fighter index is mixed in with the same splitmix64 finalizer
// gameplay/rng.h uses.
inline uint64_t bot_seed(uint64_t matchSeed, int fighterIndex) {
    uint64_t z = matchSeed + 0x9e3779b97f4a7c15ull * static_cast<uint64_t>(fighterIndex + 1);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;
    return z ^ (z >> 31);
}

// What one update may read. Everything is borrowed for the call; the brain keeps no
// pointers past update().
struct BotView {
    const Fighter* self    = nullptr;
    const Fighter* target  = nullptr;   // this fighter's selected hostile, or null
    const Fighter* partner = nullptr;   // same-side partner (2v2), or null
    bool  targetAlive  = false;
    bool  partnerAlive = false;
    int   targetIndex  = -1;   // fighter index of `target`, -1 when none
    int   partnerIndex = -1;
    int   leaderTarget = -1;   // the viewer/leader's locked target, for cells 3/4
    int   hostileCount = 0;    // living hostiles, so a switch is only asked for when
                               // there is somewhere to switch to
    // The nearest hostile threat inside the horizon: a live projectile aimed at this
    // fighter, or an enemy already swinging at it. 0 when there is none.
    float    threatDistance = 0.f;
    unsigned threats        = 0;   // BotThreat bits
    // The stage's movement collision (issue #7). Null means "no stage geometry": the
    // brain then moves in a straight line with no avoidance, which is what a
    // collision-less stage does anyway.
    const game::physics::MovementCollision* collision = nullptr;
};

enum : unsigned {
    kBotThreatNone  = 0u,
    kBotThreatShot  = 1u << 0,
    kBotThreatMelee = 1u << 1,
};

// What the brain chose. The HUD/trace reads action/tactic; the host applies the input
// half through BotBrain::apply().
enum class BotAction : int {
    Idle = 0,      // nothing to do (no live target, or the fighter cannot act)
    Approach,      // close the distance
    Retreat,       // open the distance
    Strafe,        // lateral jitter while holding the line
    Reposition,    // airborne re-position (the recovered +0x86c window)
    Jump,          // leap (vault / escape)
    Guard,         // hold block
    Evade,         // dash away from an incoming attack
    Melee,         // a swing is being requested
    Shoot,         // a charge-and-release is running
    Hyper,         // activating hypermode
};
const char* bot_action_name(BotAction a);

struct BotDecision {
    BotAction  action      = BotAction::Idle;
    BotTactic  tactic      = BotTactic::Adaptive;
    float      moveForward = 0.f;   // -1 away … +1 toward the target (port screen-up)
    float      moveRight   = 0.f;   // -1 left … +1 right
    bool       melee  = false;      // press melee this tick
    bool       jump   = false;      // hold/press jump this tick
    bool       guard  = false;      // hold guard this tick
    bool       shoot  = false;      // hold shoot this tick (the release fires)
    bool       hyper  = false;      // press special this tick
    bool       retarget = false;    // ask the host to cycle this fighter's lock
    ShotTier   tier   = ShotTier::Tap;
};

// Counters for the run log and the acceptance evidence. Never read by a decision.
struct BotStats {
    uint64_t ticks = 0;
    uint64_t plans = 0;
    uint64_t meleePresses = 0;
    uint64_t meleeBlocked = 0;     // in range but not actionable: the press was withheld
    uint64_t shotsStarted = 0;
    uint64_t shotBlocked  = 0;     // wanted to fire, no stock or reloading
    uint64_t shotsFired   = 0;     // releases issued with the gate open
    uint64_t dashStarts = 0;
    uint64_t jumps = 0;
    uint64_t guards = 0;
    uint64_t evades = 0;
    uint64_t hypers = 0;
    uint64_t retargets = 0;
    uint64_t blockedTicks = 0;     // the wanted direction made no progress
    uint64_t stuckRecoveries = 0;  // the bounded recovery fired
    uint64_t directionChanges = 0;
    float    distanceMoved = 0.f;
};

class BotBrain {
public:
    // `seed` must be the match seed plus the fighter index: two COMs sharing a seed would
    // decide identically, which a trace would show as mirrored bots.
    void reset(uint64_t seed, BotDifficulty difficulty = BotDifficulty::Standard);

    void set_difficulty(BotDifficulty d);
    BotDifficulty difficulty() const { return m_difficulty; }

    // The standing team order (the recovered +0x310 cell). FUN_0041f580:291-295 mirrors
    // the pressed cell onto player 0, which is the game's only team-wide channel.
    void set_tactic(BotTactic t);
    BotTactic tactic() const { return m_tactic; }

    // One fixed tick. Returns the decision, also kept in decision() for the HUD/trace.
    const BotDecision& update(const BotView& view, uint64_t tick);
    // The recovered double-tap window in ticks (fighter.cpp's kDoubleTapSec is 0.30 s);
    // an axis may not change its key more often than this unless a dash asked for it.
    static constexpr int kKeyFlipTicks = 21;

    const BotDecision& decision() const { return m_decision; }
    const BotStats&    stats() const { return m_stats; }
    // Replay hook: the whole random state, so a test can compare two runs.
    uint64_t rng_state() const { return m_rng.state(); }

    // Writes the decision into a device-free input state and derives its edges, exactly
    // as the live poll path does. Keys the decision does not use are cleared, so a COM
    // never inherits a stale press.
    static void apply(const BotDecision& d, fnd::input::PlayerState& in);

    // ---- the recovered constants, exposed for tests and the trace ----
    static constexpr int   kTicksPerSecond     = 64;
    static constexpr int   kMeleeCooldownTicks = 20;   // FUN_0043ded0:140-141 writes 0x14
    static constexpr int   kRetargetCooldownTicks = 16;  // the +0x30c 15-tick pulse + 1
    static constexpr float kAdvanceRange       = 500.f;  // 250000 = 500² (:154)
    static constexpr float kPowerRange         = 500.f;  // 250000 (:194)
    static constexpr float kAirRange           = 200.f;  // 40000 (:80)
    static constexpr float kThreatHorizon      = 420.f;  // port: guard/evade window
    static constexpr float kHyperRange         = 220.f;  // port: burst reach (Oyashiro)
    static constexpr float kProbeDistance      = 90.f;   // port: one navigation step
    static constexpr float kProbeOpenFraction  = 0.35f;  // port: < this of a step = a wall
    static constexpr int   kStuckRecoveryTicks = 24;     // port: bounded recovery
    static constexpr int   kShotRejectTicks    = 24;     // port: after a refused request
    static constexpr int   kShotSpacingTicks   = 8;      // port: between volleys

private:
    // One planning step: pick the action and the movement intent for the next
    // reactionTicks ticks. Every probability gate lives here.
    void plan(const BotView& v, float dist);
    // The single-tick melee press, evaluated every tick (the original's think runs every
    // tick, so a target that steps into reach between two plans must still be hit).
    bool try_melee(const BotView& v, float dist);
    // The decision half of a tick; update() wraps it with the key stabiliser.
    void compute(const BotView& view, uint64_t tick);
    // Keeps an axis' key from being released and pressed again inside the port's
    // double-tap window, which would fire a dash the brain never asked for.
    void stabilise_movement(uint64_t tick);
    // Turn the intent into a direction the stage actually allows, using the #7 sweeps.
    void navigate(const BotView& v);
    // The probed movement half alone, for commitments that may move while they run (the
    // port's charge hold is mobile).
    void apply_nav(const BotView& v);
    // How far a step in `dir` actually gets (the projection onto it).
    float probe_progress(const BotView& v, const glm::vec3& dir, float distance) const;
    // The port's lock-on basis (fighter.cpp facing_relative): screen-up is the facing.
    glm::vec3 world_dir(const BotView& v, float right, float forward) const;
    // Multi-tick commitments, evaluated before the plan each tick. Each returns true when
    // it owns the tick.
    bool run_dash_commitment();
    bool run_shot_commitment(const BotView& v);
    bool run_guard_commitment(const BotView& v);
    // The probed navigation direction for the current intent (rotates around the blocked
    // one; the bounded recovery lives here).
    void choose_nav(const BotView& v);
    // The shot tier this distance and the fighter's legal stocks allow (port rule).
    ShotTier pick_shot_tier(const Fighter& self, float dist) const;
    // Ticks to hold the shoot key for a tier, from the fighter's own charge thresholds.
    int hold_ticks(const Fighter& self, ShotTier tier) const;

    MatchRng      m_rng;
    BotTactic     m_tactic = BotTactic::Adaptive;
    BotDifficulty m_difficulty = BotDifficulty::Standard;
    BotDecision   m_decision{};
    BotStats      m_stats{};

    // The recovered jitter timers (+0x864/+0x868/+0x86c/+0x870) and the port's locks.
    int m_strafeTicks   = 0;
    int m_advanceTicks  = 0;
    int m_airTicks      = 0;
    int m_powerTicks    = 0;
    int m_meleeCooldown = 0;
    int m_shotCooldown  = 0;
    int m_retargetCooldown = 0;
    int m_planTicks     = 0;
    int m_guardTicks    = 0;
    // The port's double tap: 1 tap, 2 gap, 3 tap, then back to 0.
    int m_dashPhase = 0;
    int m_dashDir   = 0;   // 0 Up (forward), 1 Down, 2 Left, 3 Right
    BotAction m_dashAction = BotAction::Evade;
    // The charge-and-release cycle.
    int      m_shotHoldTicks = 0;
    bool     m_releasePending = false;
    ShotTier m_shotTier = ShotTier::Tap;
    // This tick's distance to the target and the reach of the swing it would press, for
    // the per-tick overrun stop. 0 when there is no target.
    float m_lastDist = 0.f;
    float m_lastReach = 0.f;
    // The movement intent, after the navigation probes. `m_navTicks` holds a probed
    // direction for a few ticks so a corner does not flip the bot left/right every tick.
    float  m_intentForward = 0.f;
    float  m_intentRight   = 0.f;
    float  m_navForward    = 0.f;
    float  m_navRight      = 0.f;
    int    m_navTicks      = 0;
    BotAction m_planAction = BotAction::Idle;
    BotAction m_navAction  = BotAction::Idle;
    // Bounded stuck recovery (port rule), and the side a wall is being followed on so the
    // slide does not alternate and cancel itself.
    int m_blockedTicks = 0;
    int m_slideSide = 0;
    // Emitted key state per axis (0 forward, 1 lateral) for the stabiliser above.
    float    m_axisValue[2] = {0.f, 0.f};
    uint64_t m_lastAxisChange[2] = {0, 0};
    // Position bookkeeping for the "did it actually move" statistic.
    bool  m_haveLastPos = false;
    float m_lastPos[3] = {0.f, 0.f, 0.f};
};

}  // namespace gameplay
