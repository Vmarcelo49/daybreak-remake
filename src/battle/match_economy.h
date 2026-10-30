#pragma once
// Match economy: per-side balloon %, the per-side LIMIT (balloon capacity), the KO
// clock and the KO/Overkill credits — the state Scene_Gameplay kept as m_balloon[2],
// m_limit, m_koAt[2], m_stingUntil and advanced in its update() bookkeeping block
// (remake/src/core/scenes.cpp:701-721; reset at 562-563 and 592-593). Lifted out of
// the DX9 scene so the SDL3+WebGPU path runs and host-tests it with no device, and so
// the HUD values become a pure function of economy + fighters.
//
// RECOVERED FROM THE ORIGINAL (issue #11). The battle scene is a global singleton at
// 0x6cafec — its four fighter pointers live at scene+0x129c..0x12a8 and every fighter
// points back at it through [fighter+0x23c], set once at 0x41d9c2 — and this file's
// state is its:
//
//   scene+0x12ac  balloon entry 0, scene+0x12b8 entry 1 — 12 bytes each:
//                 +0x00 int side, +0x04 int balloon %, +0x08 int capacity
//                 (FUN_00634980 @0x6349a2-0x6349df, wired to the fighters through
//                 [fighter+0xc] at @0x6349e8-0x634a3e; the credit is
//                 FUN_00639650 @0x639650: `entry.value += amount`, entry picked by
//                 the VICTIM's side)
//   scene+0x43c4  balloon capacity, blue      ─┐ the 青/赤チーム風船サイズ battle
//   scene+0x43c8  balloon capacity, red       ─┘ settings; default 100 at
//                 FUN_00633ca0 @0x634432-0x634452, range 40..200 step 20 in
//                 FUN_0040acb0 @0x40af57-0x40afe2
//
// CAPACITY GROWTH: there is none inside a round. The battle state machine mutates
// scene+0x43c8 exactly once, in its case 4 (FUN_00635d40 @0x63691c-0x63692b:
// `if (cap_red > 0x46) cap_red -= 5`), and that branch is the between-rounds
// transition — it runs the battle reset (FUN_00634760), re-wires the balloon entries
// (FUN_00634980), resets all four fighters (FUN_0041dcb0 x4) and drops the phase back
// to 1. So the red side's capacity SHRINKS by 5% per continued round (a multi-round
// handicap creep) and never grows. This port plays one round per match, so the rule is
// recorded but NOT implemented; a campaign/rematch flow must add it (UNRESOLVED, with
// the site above as the starting point).
//   scene+0x43d4  time limit in SECONDS (0 = ∞), scene+0x43d8 its frame countdown
//                 (FUN_00634760 @0x6347d1-0x6347dd: countdown = limit * 0x3c)
//   scene+0x442c  the winning side, scene+0x4424 the losing slot (result indexing)
//
// The rules this class reproduces, each with its site:
//  * a burst is `balloon >= capacity`, computed as `capacity - balloon < 1` by
//    FUN_00421930 (0x421930, @0x42194e-0x421955) and tested per KO'd fighter in
//    FUN_00635d40 (@0x6370dc-0x6370e3);
//  * the timed round compares BALLOONS LOWER-FIRST, then total remaining HP, then the
//    generator — FUN_00635d40 @0x636e90-0x636fd0. There is NO draw exit;
//  * a KO credits the victim's OWN side with 20 + an overkill bonus + a one-shot
//    reaction bonus (FUN_00639160 @0x639399-0x6393c6 for melee, FUN_00637950
//    @0x638cad-0x638d35 for shots);
//  * a hit on a fighter that is already down (HP <= 0 before the hit) credits exactly
//    +1 to that fighter's side — the Overkill rule (FUN_00637950 @0x638e0d-0x638e37,
//    the `[victim+0x7a4] > 0 before` branch);
//  * a downed fighter only comes back while its side still has balloon headroom:
//    FUN_004219a0 (0x4219a0, @0x4219aa-0x4219bd) returns false and restores nothing
//    when `capacity - balloon < 1`.
//
// PROVISIONAL / PORT RULES, listed here rather than hidden:
//  * the original credits the balloon inside the frame that dealt the damage and ends
//    the round on the NEXT frame's scan (the per-frame flag fighter+0xaeca is cleared
//    at the end of each frame: FUN_00634f60 @0x6353ef-0x635401 calls FUN_004201a0,
//    which zeroes it at @0x42029c). This class detects the burst in the same update()
//    call that credits it, because update() IS the port's single end-of-frame step;
//    the winning side is unaffected, the round-over frame is one earlier;
//  * the countdown is kept in seconds (the port runs a 60 Hz fixed step, so a limit of
//    N seconds lasts N seconds) while the original counts frames; the ORDER — timeout
//    decided before any KO/respawn bookkeeping — is preserved;
//  * kRespawnSec below is the port's single KO clock. The original instead runs the
//    KO move's phases and respawns 30 frames into the second one
//    (FUN_00428510 @0x42a14d-0x42a17d: `[fighter+0xe8] + 1 > 0x1e`), a mechanism this
//    port cannot express without the KO move's per-phase durations.
//
// std only: no SDL, no WebGPU, no glm.
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <string>

#include "battle/battle_types.h"
#include "battle/rng.h"

namespace gameplay {

// Two sides, +20% balloon per KO (the 0x14 literal at FUN_00639160 @0x6393b5 and
// FUN_00637950 @0x638d21), LIMIT 100% by default. The +1 that the reference prints as 21%
// is not a constant: it is the reaction bonus below.
inline constexpr int    kSideCount    = 2;
using game::kMatchFighterCount;
// The battle's legal participant count. ONE pair of bounds: Match::reset and
// TargetLocks::reset clamp the configured count to it, and the fighter-indexed flat
// arrays are sized by kMatchFighterCount.
inline constexpr int    kMinFighters  = 2;
inline constexpr int    kMaxFighters  = kMatchFighterCount;
inline constexpr float  kBalloonPerKo = 20.0f;
inline constexpr float  kBalloonLimit = 100.0f;
inline constexpr int    kBalloonSizeMin  = 40;   // FUN_0040acb0 @0x40af60-0x40afe2
inline constexpr int    kBalloonSizeMax  = 200;
inline constexpr int    kBalloonSizeStep = 20;
// The KO presentation window. The original arms a per-fighter triple
// [+0x43e4]/[+0x4404]/[+0x43f4] from two branches of the same scan, and the values
// differ: a fighter that is down and was NOT credited this frame gets 0x5a (90 frames
// = 1.5 s at 60 Hz) with 8.0f and flag 0 — the KO sting, re-armed every such frame
// (FUN_00635d40 @0x6371ba-0x637230) — while the credit frame's headroom branch uses
// 0x78 (120 frames = 2.0 s) with the same 8.0f and flag 1 (@0x637173-0x6371b8, the
// respawn presentation). This port keeps ONE shared window of this length, armed at
// the KO credit; the 0x78 respawn presentation is not modelled separately and is
// listed as an unresolved presentation item in ROADMAP-PENDING.md.
inline constexpr double kKoStingSec   = 1.5;
inline constexpr int    kBalloonDeltaTicks = 60;  // FUN_006431d0's 0x3c readout window
inline constexpr double kRespawnSec   = 3.0;  // port KO clock; see the header note

// The reaction moves the KO bonus and the Overkill window are written in terms of
// (FUN_0063ba80 @0x63ba80 returns them, FUN_00637950 @0x638c6c-0x638c88 and
// FUN_00639160 @0x6392f2-0x639325 compare against them):
//   196 (0xc4) the grounded reaction — a fighter in it counts as already down
//   198 (0xc6) the downed reaction (FUN_0063ba80's default branch)
//   199 (0xc7) the airborne reaction ([victim+0x84] == 0, i.e. the victim is airborne)
inline constexpr int kReactionGrounded = 196;
inline constexpr int kReactionDowned   = 198;
inline constexpr int kReactionAirborne = 199;

// scenes.cpp:708 tested `balloon >= limit`; the original's own predicate is the same
// boundary (FUN_00421930 returns capacity - balloon and the round ends when it is not
// > 0: FUN_00635d40 @0x6370dc-0x6370e3). Lifted so the boundary is testable.
inline constexpr bool balloonBursts(float balloon, float capacity) {
    return balloon >= capacity;
}

// FUN_0063ba80 (0x63ba80): the victim's reaction move for a hit category.
// `category` is the RAW dword at record +0x64 — the exact value the original pushes
// at 0x638c26 — and the function's own switch compares it against small integers
// (0x63babf: `sub eax,0x64; cmp eax,0x83; ja default`), so a bullet's plain 102 maps
// to 192 while a character move's 16.16 spelling of the same number (0x640000) takes
// the default branch. `victimAirborne` is that fighter's own airborne flag;
// `weaponFlag800` is the unrecovered `[attacker+0x10]+0x28 & 0x800` test that returns
// 191. 191 keeps its literal because nothing in the corpus names that flag.
inline constexpr int reactionMoveForHitCategory(int category, bool victimAirborne,
                                                bool weaponFlag800 = false) {
    if (victimAirborne) return kReactionAirborne;
    if (weaponFlag800) return 191;
    switch (category) {
        case 100: case 101: case 200: case 201: return 197;
        case 102: case 202: return 192;
        case 130: case 131: case 230: case 231: return 193;
        default: return kReactionDowned;
    }
}

// The killing blow's reaction bonus: +1 when the blow's reaction move is the downed
// (or airborne) reaction and the victim was not already in one. The melee path
// excludes {198,199} (FUN_00639160 @0x6392f2-0x639325), the shot path also excludes
// the grounded reaction (FUN_00637950 @0x638c42-0x638c8a). `latchFree` is the
// per-life latch at victim+0x84c (set on the first such kill, cleared by the respawn
// at FUN_004219a0 @0x421a08-0x421a0b), which is what keeps the credit one-shot.
//
// MODELLED BUT UNREACHABLE IN A LIVE MATCH, deliberately kept: the third exclusion term
// encodes the original's set and the melee/shot asymmetry, and the test below pins both,
// but this port models the victim's reaction move as one integer (`reaction_move()`,
// which yields kReactionGrounded only in the Knockdown state). NO production path enters
// Knockdown — the grounded reaction is not one of the selectors the port reproduces — so
// the term is always false live. It is NOT a port bug to fix by deleting it: dropping it
// would lose the recovered set, and no unverified change is worth that (see fighter.h's
// reaction_move()).
inline constexpr bool downedReactionBonus(int reactionMove, int victimMove, bool latchFree,
                                          bool shot) {
    const bool victimDown = victimMove == kReactionDowned || victimMove == kReactionAirborne ||
                            (shot && victimMove == kReactionGrounded);
    const bool blowDown = reactionMove == kReactionDowned || reactionMove == kReactionAirborne;
    return latchFree && !victimDown && blowDown;
}

// The balloon a KO adds, in the percentages the HUD prints. `overkillHp` is how far
// the blow drove HP BELOW zero in the port's 0..100 HP units, i.e. `-hpAfter` clamped
// at 0; the field scalars are the original's, which counts HP in 1/100 units
// (max 10000 = 100%):
//   melee (FUN_00639160 @0x639399-0x6393b5): 20 + HP_below/1000
//   shots (FUN_00637950 @0x638cad-0x638d15): 20 + min(HP_below/500, 5), +1 below
//          -3500 and +1 below -4500 (0xfffff254/0xffffee6c = 0xdac/0x1194)
// Dividing the melee term by 100 and the shot term by 100/500 gives the port's units,
// so both branches read as the original's literals scaled by the same HP scale the
// whole port already uses (10000 orig = 100 port).
inline constexpr int kShotOverkillCap = 5;
inline constexpr int kShotOverkillDeepHp = 35;   // 0xdac  = 3500 orig = 35 port
inline constexpr int kShotOverkillDeeperHp = 45; // 0x1194 = 4500 orig = 45 port

inline int koIncrementPercent(int overkillHp, bool reactionBonus, bool shot) {
    const int over = overkillHp > 0 ? overkillHp : 0;
    int bonus;
    if (shot) {
        bonus = std::min(over / 5, kShotOverkillCap);
        if (over > kShotOverkillDeepHp) ++bonus;
        if (over > kShotOverkillDeeperHp) ++bonus;
    } else {
        bonus = over / 10;
    }
    return static_cast<int>(kBalloonPerKo) + bonus + (reactionBonus ? 1 : 0);
}

// Why a round ended. The original has exactly two: FUN_00635d40's timeout decision
// (@0x636e90-0x636fd0) and its balloon-burst scan (@0x6370e3-0x637171).
enum class RoundEnd : int { None = 0, Burst = 1, Timeout = 2 };

// The reference's trace prefix (scenes.cpp:706-719). The *LogLine helpers below
// return the bare message; lines written through MatchEconomy::logFile() carry
// the prefix, so a trace diffed against the DX9 console matches byte for byte.
inline constexpr const char* kTracePrefix = "[daybreak] ";

// Exact formatted trace strings: the reference's own printf conversions (float
// promoted to double, "%.0f"), so the text matches to the digit.
std::string koLogLine(int side, float balloon, float limit);
std::string burstLogLine(int side);
std::string respawnLogLine(int side);
// Issue #11's two new credits; the DX9 build printed neither, so they are additive
// and cannot break the banked trace comparison (which reads cam lines only).
std::string overkillLogLine(int side, float balloon, float limit, int amount);
std::string timeoutLogLine(int winner, float balloon0, float balloon1, int hp0, int hp1);

// What one update() step asks the caller to apply: one respawn per fighter (the
// economy owns no positions) and the round-over transition.
struct MatchStepResult {
    bool respawned[kMatchFighterCount] = {false, false, false, false};
    int  koCredits[kMatchFighterCount] = {0, 0, 0, 0};  // % added by a KO this step
    int  overkillCredits[kMatchFighterCount] = {0, 0, 0, 0};  // hits on a downed body
    bool roundOver = false;
    // The WINNING side (scene+0x442c). The original always produces one: a timed round
    // falls through balloon -> HP total -> generator (FUN_00635d40 @0x636e90-0x636fd0).
    int  roundOverSide = -1;
    RoundEnd roundEnd = RoundEnd::None;
};

class MatchEconomy {
public:
    MatchEconomy() = default;
    // Trace sink; stdout keeps the reference's console output, nullptr silences.
    explicit MatchEconomy(std::FILE* log) : m_log(log) {}

    // Scene_Gameplay::on_enter (scenes.cpp:562-563, 592-593). The capacities are NOT
    // reset here — on_enter does not touch the limit either, and the original's scene
    // constructor is the only thing that writes 100 (FUN_00633ca0 @0x633ce1-0x633cf2).
    void reset();
    // The battle settings -> scene fields: the time limit in seconds and each side's
    // balloon capacity from 青/赤チーム風船サイズ. PORT RULE: out-of-range input is
    // clamped to [40,200]; the settings screen itself WRAPS (below 40 becomes 200,
    // above 200 becomes 40 — FUN_0040acb0 @0x40af60-0x40afe2), which is a UI cycling
    // behaviour the simulation should not inherit. A capacity of 0 or a negative
    // value falls back to the 100 default.
    void set_round_rules(int timeLimit, const int balloonSize[2]);

    // A backend that keeps its own score overwrites the read side each tick; the credit and
    // tick paths below are then unused.
    void mirror(const float balloon[kSideCount], const float capacity[kSideCount], const int delta[kSideCount],
                const int deltaTicks[kSideCount], int winner, int secondsLeft) {
        for (int side = 0; side < kSideCount; ++side) {
            m_balloon[side] = m_balloonDisplay[side] = balloon[side];
            m_capacity[side] = capacity[side];
            m_balloonDelta[side] = delta[side];
            m_balloonDeltaTicks[side] = deltaTicks[side];
        }
        m_roundOverSide = winner;
        m_roundOver = winner >= 0;
        m_timeLimit = secondsLeft;
    }

    // One frame of the clock, exactly scenes.cpp:610. Call once per frame, before
    // update(): it also advances the recovered balloon presentation (the popup timer
    // and the ±0.5%/frame inflate of FUN_006430f0 @0x6430f0).
    void tick(double dt);

    // --- credits the scene reports before update() runs -------------------------
    // A fighter died this frame. `overkillHp` is how far below zero the killing blow
    // drove its HP (in the port's HP units), `reactionBonus` the downed-reaction +1
    // and `shot` whether the blow came from a projectile. Without a note the KO still
    // credits the default 20 — the legacy shared path that binds no move table.
    void note_death(int fighter, int overkillHp = 0, bool reactionBonus = false,
                    bool shot = false);
    // A hit landed on a fighter that was already down (Overkill). One call per hit;
    // each adds exactly +1 to that fighter's side (FUN_00637950 @0x63748e-0x6374a0).
    void note_overkill_hit(int fighter);

    // The bookkeeping block (scenes.cpp:701-721; FUN_00635d40's case 2 and the
    // original's ordering), in the original's own order:
    //   1. the timed round: when the limit is reached, the LOWER balloon wins, then
    //      the higher HP total, then the generator (FUN_00635d40 @0x636e90-0x636fd0);
    //   2. per fighter: a just-died fighter is credited on its OWN side and its KO
    //      clock stamped; a KO'd fighter whose clock has run out respawns, but only
    //      while its side still has balloon headroom (FUN_004219a0 @0x4219aa-0x4219bd).
    // `fighterCount` is how many slots are live; slots past it are ignored, so an
    // unused panel can never be credited. `hp` is optional (nullptr skips the HP
    // tiebreak); its scale does not matter, the tiebreak compares two sums.
    MatchStepResult update(const bool alive[kSideCount], const int hp[kSideCount] = nullptr);
    MatchStepResult update(const bool alive[kMatchFighterCount],
                           const int side[kMatchFighterCount], int fighterCount,
                           const int hp[kMatchFighterCount] = nullptr);

    // --- state the flow and the HUD read back ---
    float  balloon(int side) const { return m_balloon[side]; }
    // F1 (issue #48): the original zeroes the two balloon counters at scene+0x12b0/+0x12bc
    // (FUN_00634f60:173-174). Those ARE these percentages — the balloon entries at
    // scene+0x12ac/+0x12b8 are 12 bytes of {side, balloon %, capacity}, FUN_00639650 credits
    // the +0x04 and FUN_00635d40 reads it to name the round's winner — so the key zeroes both
    // sides and the HUD's corners read 0 immediately. The credit popup (hud+0x78e0/+0x78e8)
    // and the eased `balloonDisplay` value are NOT touched, matching the two raw stores.
    void reset_balloons() { m_balloon[0] = 0.0f; m_balloon[1] = 0.0f; }
    // The animated value the original's own % readout formats (FUN_006430f0 eases
    // hud+0x78f0 toward the real value by 0.5 per frame; the KO'd side therefore
    // visibly inflates over ~42 frames).
    float  balloonDisplay(int side) const { return m_balloonDisplay[side]; }
    // The last credit's amount and its 60-frame readout (FUN_006431d0 @0x6431d0 sets
    // both); ticks counts down once per tick().
    int    balloonDelta(int side) const { return m_balloonDelta[side]; }
    int    balloonDeltaTicks(int side) const { return m_balloonDeltaTicks[side]; }
    // Per-side balloon capacity — the LIMIT the HUD prints next to each corner's %.
    float  capacity(int side) const { return m_capacity[side]; }
    // The left corner's LIMIT, which is the single value the DX9 layout's HUD carried
    // (scenes.cpp kept one m_limit for both corners). Equal capacities make it exact.
    float  limit() const { return m_capacity[0]; }
    double koAt(int fighter) const { return m_koAt[fighter]; }  // -1 = alive
    double stingUntil() const { return m_stingUntil; }    // -1 = never stung
    double elapsed() const { return m_elapsed; }
    // scenes.cpp:889 (m_elapsed < m_stingUntil): strict, so the sting is gone
    // exactly at stingUntil.
    bool   koStingActive() const { return m_elapsed < m_stingUntil; }
    bool   roundOver() const { return m_roundOver; }
    // The WINNING side, or -1 before the round ends. main.cpp used to invert this
    // (the DX9 port reported the burst side); the recovered value is the winner
    // (scene+0x442c), which is also what the original's result indexing reads
    // (scene+0x4424 = winner << 1, scene+0x4428 = winner * 2 + 1, FUN_00635d40
    // @0x636f3a-0x636fd0).
    int    roundOverSide() const { return m_roundOverSide; }
    RoundEnd roundEnd() const { return m_roundEnd; }
    // Single-counted credit audit: KOs, Overkill hits and respawns per side. A
    // complete match must satisfy kos(0)+kos(1) == deaths + the scripted credits, and
    // no KO may ever be credited twice.
    int    kos(int side) const { return m_kos[side]; }
    int    overkills(int side) const { return m_overkills[side]; }
    int    respawns(int side) const { return m_respawns[side]; }
    // Timed-round state: the limit in seconds (0 = ∞) and what is left of it.
    int    timeLimit() const { return m_timeLimit; }
    double timeLeft() const { return m_timeLimit > 0 ? m_timeLeft : 0.0; }
    bool   timed() const { return m_timeLimit > 0; }
    // The deterministic generator the tiebreak consumes (battle/rng.h). Seeding it
    // makes a replayed match resolve the same tie.
    MatchRng&       rng()       { return m_rng; }
    const MatchRng& rng() const { return m_rng; }
    void   set_rng_seed(uint64_t seed) { m_rng.set_state(seed); }

    std::FILE* logFile() const { return m_log; }
    void setLogFile(std::FILE* f) { m_log = f; }

private:
    void log(const std::string& line);
    // side -> summed HP over its fighters (the timeout's second key). Returns false
    // when no HP array was supplied.
    bool sideHpTotals(const bool alive[kMatchFighterCount],
                      const int side[kMatchFighterCount], int fighterCount,
                      const int hp[kMatchFighterCount], int out[kSideCount]) const;
    MatchStepResult updateImpl(const bool alive[kMatchFighterCount],
                               const int side[kMatchFighterCount], int fighterCount,
                               const int hp[kMatchFighterCount]);

    float  m_balloon[kSideCount] = {0.0f, 0.0f};
    float  m_balloonDisplay[kSideCount] = {0.0f, 0.0f};
    int    m_balloonDelta[kSideCount] = {0, 0};
    int    m_balloonDeltaTicks[kSideCount] = {0, 0};
    float  m_capacity[kSideCount] = {kBalloonLimit, kBalloonLimit};
    int    m_timeLimit = 0;      // seconds; 0 = ∞ (scene+0x43d4)
    double m_timeLeft = 0.0;     // seconds left (scene+0x43d8 in frames originally)
    double m_koAt[kMatchFighterCount] = {-1.0, -1.0, -1.0, -1.0};
    double m_stingUntil = -1.0;
    double m_elapsed = 0.0;
    // No reference counterpart: DX9 leaves the scene on the burst frame.
    bool   m_roundOver = false;
    int    m_roundOverSide = -1;
    RoundEnd m_roundEnd = RoundEnd::None;
    // Pending credits, armed by note_*() and consumed by the next update().
    struct DeathNote {
        bool armed = false;
        int  overkillHp = 0;
        bool reactionBonus = false;
        bool shot = false;
    };
    DeathNote m_death[kMatchFighterCount];
    int    m_overkillHits[kMatchFighterCount] = {0, 0, 0, 0};
    int    m_kos[kSideCount] = {0, 0};
    int    m_overkills[kSideCount] = {0, 0};
    int    m_respawns[kSideCount] = {0, 0};
    MatchRng m_rng{};
    std::FILE* m_log = stdout;
};

}  // namespace gameplay
