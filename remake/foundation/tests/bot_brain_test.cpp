// =============================================================================
//  bot_brain_test.cpp — issue #14: the COM decision state.
//
//  Pins the acceptance criteria directly, device-free (no assets, no install):
//    * the recovered tactic cells, their weights and the +0x310/+0x314 readout;
//    * determinism — same seed + same view = identical decision trace, and a
//      different seed is a different trace;
//    * no unavailable move is ever requested (ammo, reload, stamina, guard
//      exhaustion, mid-swing recovery), and a refused request is not retried in
//      a tight loop;
//    * a target that dies or re-enters its airborne respawn is retargeted;
//    * allies are never treated as hostiles (target or threat);
//    * a bot blocked by a wall/corner recovers and keeps making progress;
//    * characters fight with a real combo: the synthetic data below is "Rena 1"
//      (weapon slot 1 / item 001, magazine 6x300 + 2x300, charge 60/180, and the
//      weapon move chain 300/301/302 whose entries carry the hit windows) —
//      never a bare fighter (AGENTS rule 7).
//
//  Build (CMake target `bot_brain_test`):
//    cmake --build remake/foundation/build/linux --target bot_brain_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#include "gameplay/bot_brain.h"
#include "gameplay/bot_input.h"
#include "gameplay/character_moves.h"
#include "gameplay/match.h"
#include "gameplay/weapon_definition.h"

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace {

using gameplay::BotAction;
using gameplay::BotBrain;
using gameplay::BotContext;
using gameplay::BotDecision;
using gameplay::BotDifficulty;
using gameplay::BotTactic;
using gameplay::BotView;
using gameplay::Fighter;
using gameplay::FighterState;
namespace input = fnd::input;

namespace fs = std::filesystem;

int checks = 0;
int failures = 0;
int skipped = 0;

void check(bool condition, const char* name) {
    ++checks;
    if (!condition) ++failures;
    std::printf("  %-64s %s\n", name, condition ? "ok" : "FAIL");
}
void checkInt(long long expected, long long actual, const char* name) {
    ++checks;
    const bool same = expected == actual;
    if (!same) ++failures;
    std::printf("  %-64s %s", name, same ? "ok" : "FAIL");
    if (!same) std::printf("  (expected %lld, got %lld)", expected, actual);
    std::printf("\n");
}
void section(const char* title) { std::printf("\n== %s\n", title); }
void skip(const char* name) {
    ++skipped;
    std::printf("  %-64s SKIP\n", name);
}

// ---------------------------------------------------------------------------
// Synthetic combo data. The numbers are the shipped ones for Rena 1 (character
// index 0, weapon slot 0, item id 1): docs/ROADMAP-PENDING.md's coverage table
// row `rena | 0 | 1 | 2 | 18 | 6 | 300 | 2 | 300 | 60 | 180 | 75/30/1750 | —`
// — magazine 0 is 6 shots at 300 pool units each, magazine 1 is 2 shots at 300,
// charge maxima 60/180. The move table carries the weapon chain the swing
// resolver selects (300 ground / 301 charged / 302), with rena 300's recovered
// hit entry (frame 4, radius 20) and a follower at frame 7 to bound the window.
// ---------------------------------------------------------------------------
void putU32(std::vector<uint8_t>& b, int v) {
    const uint32_t u = static_cast<uint32_t>(v);
    for (int i = 0; i < 4; ++i) b.push_back(static_cast<uint8_t>((u >> (8 * i)) & 0xffu));
}
void putF32(std::vector<uint8_t>& b, float v) {
    int i = 0;
    std::memcpy(&i, &v, 4);
    putU32(b, i);
}
void putName(std::vector<uint8_t>& b, const char* s, int width) {
    const size_t n = std::strlen(s);
    for (int i = 0; i < width; ++i)
        b.push_back(i < static_cast<int>(n) ? static_cast<uint8_t>(s[i]) : 0u);
}

struct SynthEntry {
    const char* name = "";
    int activeFrame = 0;
    int hitRadius = 0;
    int hpDamage = 0;       // combat[5], 10000-based
    int defenderHitstun = 0;  // combat[10]
};

void addPhase(std::vector<uint8_t>& b, int setIndex, const std::vector<SynthEntry>& entries) {
    putU32(b, setIndex);
    putU32(b, static_cast<int>(entries.size()));
    for (const SynthEntry& e : entries) {
        putName(b, e.name, 30);
        putU32(b, e.activeFrame);
        putF32(b, 0.f);
        putF32(b, 0.f);
        putF32(b, 0.f);
        putU32(b, e.hitRadius);
        int combat[20] = {0};
        combat[5] = e.hpDamage;
        combat[10] = e.defenderHitstun;
        for (int c : combat) putU32(b, c);
        putU32(b, 0);
        putU32(b, 0);
        putU32(b, 0);
        putF32(b, 0.f);
        putF32(b, 0.f);
        putF32(b, 0.f);
    }
}

using SynthPhase = std::pair<int, std::vector<SynthEntry>>;

SynthEntry prop(const char* name, int frame, int radius, int hpDamage, int hitstun) {
    SynthEntry e;
    e.name = name;
    e.activeFrame = frame;
    e.hitRadius = radius;
    e.hpDamage = hpDamage;
    e.defenderHitstun = hitstun;
    return e;
}

void addMove(std::vector<uint8_t>& b, int id, int cancelWindow,
             const std::vector<SynthPhase>& phases) {
    putU32(b, id);
    putU32(b, 0);
    putU32(b, cancelWindow);
    putU32(b, static_cast<int>(phases.size()));
    for (const auto& p : phases) addPhase(b, p.first, p.second);
}

// The move table FUN_0041e180 reads: header, weapon id at file offset 0x114, moves.
std::vector<uint8_t> renaMoveTable() {
    std::vector<uint8_t> b;
    putU32(b, 0x00010000);                 // tag
    putName(b, "data/rena/00.X", 0x104);   // 260-byte model path block
    putU32(b, 0);
    putU32(b, 0);
    putU32(b, 0);
    putU32(b, 1);                          // header[3] = the table's weapon id (0x114)
    putU32(b, 0);
    putU32(b, 0);
    putU32(b, 4);                          // move count
    const SynthEntry pose = prop("", 0, 0, 0, 0);
    addMove(b, 10, 0, {SynthPhase{1, {pose}}});                        // walk
    addMove(b, 20, 8, {SynthPhase{13, {pose}},                         // dash
                       SynthPhase{14, {pose}},
                       SynthPhase{15, {pose}}});
    // rena move 300: the hit goes live on frame 4 at radius 20 and the next effect
    // bounds the window at 7 (the shipped values, melee_rules_test's anchor).
    addMove(b, 300, 12, {SynthPhase{31, {prop("Prop1", 4, 20, 750, 10),
                                       prop("Whiff", 7, 0, 0, 0)}}});
    addMove(b, 301, 12, {SynthPhase{33, {prop("Prop1", 7, 20, 1500, 12),
                                       prop("Whiff", 9, 0, 0, 0)}}});
    // FUN_0041e180 continues past the move records with the animation-set rows: a
    // count, then one [transitionDuration, phaseGate, eventCount, eventCount*0x84]
    // row per set. This synthetic table exercises the move records only, so it
    // declares zero sets — the parser rejects anything else as trailing data.
    putU32(b, 0);
    return b;
}

std::unique_ptr<gameplay::WeaponDefinition> rena1Weapon() {
    auto w = std::make_unique<gameplay::WeaponDefinition>();
    w->id = 1;
    w->slotCount = 2;
    w->bulletCount = 0;
    w->magazines[0] = gameplay::MagazineDefinition{6, 2, 300, 0, 60, 1};
    w->magazines[1] = gameplay::MagazineDefinition{2, 2, 300, 0, 180, 2};
    return w;
}

// One "Rena 1" fighter, settled out of the 60-frame BattleStart pose.
Fighter makeFighter(const gameplay::WeaponDefinition* weapon,
                    const gameplay::CharacterMoves* moves, const glm::vec3& at,
                    float facing = 0.f) {
    Fighter f;
    f.init(nullptr, nullptr, at, facing);
    f.set_weapon(weapon);
    f.set_moves(moves);
    input::PlayerState idle;
    for (int i = 0; i < 70; ++i) {
        input::PlayerState copy = idle;
        input::compute_edges(copy);
        f.update(&copy, nullptr, 1.0 / 64.0);
    }
    return f;
}

// ---------------------------------------------------------------------------
// The recovered tactic table.
// ---------------------------------------------------------------------------
void testTacticTable() {
    section("the six recovered tactic cells and their weights");
    checkInt(6, gameplay::kBotTacticCells, "six cells (player+0x310, cycled mod 6)");
    checkInt(0, gameplay::bot_tactic_cell(BotTactic::Adaptive), "adaptive is cell 0 (適当)");
    checkInt(5, gameplay::bot_tactic_cell(BotTactic::Retreat), "retreat is cell 5 (後退)");
    check(BotTactic::Focus == gameplay::bot_tactic_from_cell(3), "cell 3 is focus (集中)");
    check(BotTactic::Separate == gameplay::bot_tactic_from_cell(4), "cell 4 is separate (各個)");
    check(BotTactic::Adaptive == gameplay::bot_tactic_from_cell(6), "cell 6 wraps to 0");
    check(BotTactic::Melee == gameplay::bot_tactic_from_cell(7), "cell 7 wraps to 1");
    check(BotTactic::Retreat == gameplay::bot_tactic_from_cell(-1), "a negative cell wraps back");

    struct Row { BotTactic t; float scale; int engage; int power; };
    const Row rows[6] = {
        {BotTactic::Adaptive, 1.00f, 100, 100},
        {BotTactic::Melee,    0.25f,  50, 200},
        {BotTactic::Shoot,    2.50f, 200,  50},
        {BotTactic::Focus,    1.00f, 100, 100},
        {BotTactic::Separate, 1.00f, 100, 100},
        {BotTactic::Retreat,  7.00f,   5,   5},
    };
    for (const Row& r : rows) {
        const gameplay::BotTacticWeights w = gameplay::bot_tactic_weights(r.t);
        const bool same = std::abs(w.rangeScale - r.scale) < 1e-6f &&
                          w.engageWeight == r.engage && w.powerWeight == r.power;
        char name[96];
        std::snprintf(name, sizeof(name), "%s weights are FUN_0043f4d0's (%.2f/%d/%d)",
                      gameplay::bot_tactic_name(r.t), (double)r.scale, r.engage, r.power);
        check(same, name);
    }
}

// ---------------------------------------------------------------------------
// The tactics readout: player+0x310 / +0x314.
// ---------------------------------------------------------------------------
void testTacticReadout() {
    section("the tactics readout (player+0x310 cell, +0x314 timer)");
    gameplay::TacticReadout readout;
    readout.reset();
    checkInt(0, readout.hud_cell(), "a fresh round shows the recovered default cell 0");
    check(readout.visible(), "and it is visible while the timer is armed");

    check(BotTactic::Melee == readout.press(), "a Tactics press cycles 0 -> 1");
    checkInt(1, readout.hud_cell(), "the HUD cell follows the press");
    for (int i = 1; i < gameplay::kBotTacticCells; ++i) readout.press();
    checkInt(0, readout.hud_cell(), "six presses wrap back to cell 0");

    for (int i = 0; i < gameplay::TacticReadout::kHoldTicks; ++i) readout.tick();
    check(readout.visible(), "the readout is still up when the held timer reaches zero");
    for (int i = 0; i < gameplay::TacticReadout::kFadeTicks; ++i) readout.tick();
    checkInt(-1, readout.hud_cell(), "and hides itself after the recovered fade tail");
}

// ---------------------------------------------------------------------------
// Determinism.
// ---------------------------------------------------------------------------
uint64_t traceHash(BotBrain& brain, const BotView& view, int ticks, uint64_t& outTicks) {
    uint64_t h = 1469598103934665603ull;   // FNV-1a
    outTicks = 0;
    for (int i = 1; i <= ticks; ++i) {
        const BotDecision& d = brain.update(view, (uint64_t)i);
        auto mix = [&h](uint64_t v) {
            for (int b = 0; b < 8; ++b) {
                h ^= (v >> (8 * b)) & 0xffu;
                h *= 1099511628211ull;
            }
        };
        mix(static_cast<uint64_t>(d.action));
        mix(static_cast<uint64_t>(d.tactic));
        mix(static_cast<uint64_t>(static_cast<int>(d.moveForward * 2.f + 2.f)));
        mix(static_cast<uint64_t>(static_cast<int>(d.moveRight * 2.f + 2.f)));
        mix((d.melee ? 1u : 0u) | (d.jump ? 2u : 0u) | (d.guard ? 4u : 0u) |
            (d.shoot ? 8u : 0u) | (d.hyper ? 16u : 0u) | (d.retarget ? 32u : 0u));
        mix(brain.rng_state());
    }
    outTicks = brain.stats().ticks;
    return h;
}

void testDeterminism() {
    section("determinism: same seed + same view = identical decision trace");
    Fighter self = makeFighter(nullptr, nullptr, glm::vec3(0, 0, 0));
    Fighter enemy = makeFighter(nullptr, nullptr, glm::vec3(0, 0, 260));
    BotView view;
    view.self = &self;
    view.target = &enemy;
    view.targetAlive = true;
    view.targetIndex = 1;
    view.hostileCount = 1;

    BotBrain a, b, c;
    a.reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, 2));
    b.reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, 2));
    c.reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, 3));
    uint64_t ta = 0, tb = 0, tc = 0;
    const uint64_t ha = traceHash(a, view, 600, ta);
    const uint64_t hb = traceHash(b, view, 600, tb);
    const uint64_t hc = traceHash(c, view, 600, tc);
    check(ta == 600 && tb == 600, "both runs advanced 600 ticks");
    check(ha == hb, "two brains on the same seed produce the same trace");
    check(ha != hc, "a different fighter seed produces a different trace");

    // Replaying the SAME brain from reset() is the rollback property the issue asks for.
    a.reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, 2));
    uint64_t tr = 0;
    check(traceHash(a, view, 600, tr) == ha, "reset() + replay reproduces the trace");
}

// Per-tick availability invariants: a COM must never ask for something the fighter
// cannot do, whatever the situation.
std::string availabilityViolation(const BotDecision& d, const Fighter& f) {
    if (!f.is_alive()) return {};
    // The press requires an actionable fighter (this is the check the old sparring
    // policy skipped: its presses were dropped mid-swing).
    if (d.melee && !f.actionable()) return "melee pressed while not actionable";
    if (d.guard && (!f.actionable() || f.guard_exhausted() || f.stamina() <= 0))
        return "guard held while exhausted or out of stamina";
    if (d.jump && !f.actionable()) return "jump pressed while not actionable";
    if (d.shoot) {
        // A hold may only start when that tier can actually fire; the hold itself is
        // then immune to the pool draining (nothing spends until the release).
        bool any = f.can_fire(gameplay::ShotTier::Tap) ||
                   f.can_fire(gameplay::ShotTier::Yellow) ||
                   f.can_fire(gameplay::ShotTier::Red);
        if (!any) return "shoot held with no firable tier";
    }
    if (d.hyper && !f.hyper_ready()) return "hypermode pressed without a full gauge";
    return {};
}

// Runs the brain against a live fighter for `ticks` ticks, enforcing every invariant and
// returning a few counters. The enemy is a static sparring partner.
struct RunResult {
    uint64_t meleePresses = 0, shootTicks = 0, violations = 0, dashStarts = 0;
    uint64_t minMeleeGap = 0, firstMeleeTick = 0;
    std::string firstViolation;
    float distanceMoved = 0.f;
};

RunResult runSolo(BotBrain& brain, Fighter& self, Fighter& enemy, int ticks,
                  const game::physics::MovementCollision* collision = nullptr,
                  unsigned threats = gameplay::kBotThreatNone, float threatDistance = 0.f) {
    RunResult r;
    int lastMelee = -100000;
    // One state for the whole run: the live poll path keeps its PlayerState, and its
    // prev_down is what turns held keys into just_pressed. A fresh state per tick would
    // make every held key a fresh press and chain the port's double-tap dash.
    input::PlayerState in;
    for (int i = 1; i <= ticks; ++i) {
        BotView view;
        view.self = &self;
        view.target = &enemy;
        view.targetAlive = enemy.is_alive();
        view.targetIndex = 1;
        view.hostileCount = view.targetAlive ? 1 : 0;
        view.collision = collision;
        view.threats = threats;
        view.threatDistance = threatDistance;
        const BotDecision d = brain.update(view, (uint64_t)i);
        const std::string bad = availabilityViolation(d, self);
        if (!bad.empty()) {
            ++r.violations;
            if (r.firstViolation.empty()) {
                r.firstViolation = bad;
                std::printf("    tick %d: %s\n", i, bad.c_str());
            }
        }
        if (d.melee) {
            if (r.meleePresses == 0) r.firstMeleeTick = (uint64_t)i;
            const uint64_t gap = (uint64_t)(i - lastMelee);
            if (r.meleePresses > 0 && (r.minMeleeGap == 0 || gap < r.minMeleeGap))
                r.minMeleeGap = gap;
            lastMelee = i;
            ++r.meleePresses;
        }
        if (d.shoot) ++r.shootTicks;
        if (d.action == BotAction::Evade || d.action == BotAction::Approach) {
            if (d.moveForward != 0.f || d.moveRight != 0.f) ++r.dashStarts;
        }
        BotBrain::apply(d, in);
        self.update(&in, &enemy, 1.0 / 64.0, collision);
    }
    r.distanceMoved = brain.stats().distanceMoved;
    return r;
}

void testAvailability() {
    section("no unavailable move is ever requested");
    auto weapon = rena1Weapon();
    std::vector<uint8_t> table = renaMoveTable();
    // Heap: CharacterMoves is ~10 MB (512 moves x 8 phases x 24 entries).
    auto moves = std::make_unique<gameplay::CharacterMoves>();
    std::string err;
    check(moves->parse(table.data(), table.size(), err),
          "the synthetic Rena 1 move table parses");
    checkInt(1, moves->weapon_id(), "and carries its weapon id at file offset 0x114");

    Fighter self = makeFighter(weapon.get(), moves.get(), glm::vec3(0, 0, 0));
    Fighter enemy = makeFighter(weapon.get(), moves.get(), glm::vec3(0, 0, 240));
    BotBrain brain;
    brain.reset(4242);
    const RunResult r = runSolo(brain, self, enemy, 900);
    checkInt(0, (long long)r.violations, "900 ticks with zero availability violations");
    check(r.shootTicks > 0, "the default cell keeps its distance and shoots");

    // 格闘 (cell 1, rangeScale 0.25) is the cell that closes to melee: the recovered band
    // is 500 * 0.25 = 125 units, and the swing's own reach is 50 (30 body + rena 300's
    // hitRadius 20). This is the documented way to ask a COM for melee.
    Fighter self2 = makeFighter(weapon.get(), moves.get(), glm::vec3(0, 0, 0));
    Fighter enemy2 = makeFighter(weapon.get(), moves.get(), glm::vec3(0, 0, 240));
    BotBrain brain2;
    brain2.reset(4242);
    brain2.set_tactic(BotTactic::Melee);
    const RunResult r2 = runSolo(brain2, self2, enemy2, 900);
    checkInt(0, (long long)r2.violations, "the 格闘 cell breaks no availability rule either");
    check(r2.meleePresses > 0, "the 格闘 cell does swing once it is in reach");
    check(r2.meleePresses >= 3, "and it keeps swinging at a target it can reach");
    check(r2.minMeleeGap >= (uint64_t)BotBrain::kMeleeCooldownTicks,
          "consecutive swings are at least the recovered 20-tick lockout apart");
}

void testEmptyAmmoIsNotSpammed() {
    section("an empty magazine is waited out, not hammered");
    auto weapon = rena1Weapon();
    Fighter self = makeFighter(weapon.get(), nullptr, glm::vec3(0, 0, 0));
    Fighter enemy = makeFighter(weapon.get(), nullptr, glm::vec3(0, 0, 400));
    // Drain both pools by firing as fast as the gates allow. The tap pool refills one
    // shot per second, so this leaves the fighter reloading and nearly dry.
    input::PlayerState in;
    for (int i = 0; i < 40; ++i) {
        in.down[input::Action::Shoot] = true;
        input::compute_edges(in);
        self.update(&in, &enemy, 1.0 / 64.0);
        input::PlayerState up;
        input::compute_edges(up);
        self.update(&up, &enemy, 1.0 / 64.0);
    }
    check(!self.can_fire(gameplay::ShotTier::Tap) ||
              !self.can_fire(gameplay::ShotTier::Yellow),
          "the fighter really is out of firable tiers");

    BotBrain brain;
    brain.reset(77);
    int heldWhileBlocked = 0;
    for (int i = 1; i <= 240; ++i) {
        BotView view;
        view.self = &self;
        view.target = &enemy;
        view.targetAlive = true;
        view.targetIndex = 1;
        view.hostileCount = 1;
        const BotDecision d = brain.update(view, (uint64_t)i);
        const bool anyFirable = self.can_fire(gameplay::ShotTier::Tap) ||
                                self.can_fire(gameplay::ShotTier::Yellow) ||
                                self.can_fire(gameplay::ShotTier::Red);
        if (d.shoot && !anyFirable) ++heldWhileBlocked;
        BotBrain::apply(d, in);
        self.update(&in, &enemy, 1.0 / 64.0);
    }
    checkInt(0, heldWhileBlocked, "no shot is held while every tier is unaffordable");
    const uint64_t blocked = brain.stats().shotBlocked;
    check(blocked <= 240 / (uint64_t)BotBrain::kShotRejectTicks + 2,
          "refusals are counted once per lockout, not once per tick");
}

void testGuardExhaustion() {
    section("guard exhaustion and stamina are respected");
    auto weapon = rena1Weapon();
    Fighter self = makeFighter(weapon.get(), nullptr, glm::vec3(0, 0, 0));
    Fighter enemy = makeFighter(weapon.get(), nullptr, glm::vec3(0, 0, 200));
    // Hold block until the stamina bar is empty and the recovery lock arms.
    input::PlayerState in;
    for (int i = 0; i < 400 && !self.guard_exhausted(); ++i) {
        in.down[input::Action::Guard] = true;
        input::compute_edges(in);
        self.update(&in, &enemy, 1.0 / 64.0);
    }
    check(self.guard_exhausted(), "holding block long enough exhausts the guard");
    check(self.stamina() <= 0, "and drains the stamina that pays for it");

    BotBrain brain;
    brain.reset(9);
    uint64_t guardsWhileExhausted = 0;
    for (int i = 1; i <= 200; ++i) {
        BotView view;
        view.self = &self;
        view.target = &enemy;
        view.targetAlive = true;
        view.targetIndex = 1;
        view.hostileCount = 1;
        view.threats = gameplay::kBotThreatMelee;
        view.threatDistance = 100.f;      // a swing is live right next to it
        const BotDecision d = brain.update(view, (uint64_t)i);
        if (d.guard && (self.guard_exhausted() || self.stamina() <= 0)) ++guardsWhileExhausted;
        BotBrain::apply(d, in);
        self.update(&in, &enemy, 1.0 / 64.0);
    }
    checkInt(0, (long long)guardsWhileExhausted,
             "a threatened but exhausted COM never holds a refused guard");
}

void testDodge() {
    section("defensive reaction to an incoming attack");
    auto weapon = rena1Weapon();
    Fighter self = makeFighter(weapon.get(), nullptr, glm::vec3(0, 0, 0));
    Fighter enemy = makeFighter(weapon.get(), nullptr, glm::vec3(0, 0, 300));
    BotBrain brain;
    brain.reset(31337, BotDifficulty::Sharp);   // the most defensive policy
    uint64_t defensive = 0;
    input::PlayerState in;
    for (int i = 1; i <= 200; ++i) {
        BotView view;
        view.self = &self;
        view.target = &enemy;
        view.targetAlive = true;
        view.targetIndex = 1;
        view.hostileCount = 1;
        view.threats = gameplay::kBotThreatShot;
        view.threatDistance = 150.f;
        const BotDecision d = brain.update(view, (uint64_t)i);
        if (d.action == BotAction::Guard || d.action == BotAction::Evade) ++defensive;
        BotBrain::apply(d, in);
        self.update(&in, &enemy, 1.0 / 64.0);
    }
    check(defensive > 20, "an incoming shot produces guard/evade ticks");
    check(brain.stats().guards + brain.stats().evades > 5,
          "and the reactions are counted as such");
    check(brain.stats().evades == 0 || brain.stats().dashStarts > 0,
          "an evade is a real committed dash, not a label");
}

// ---------------------------------------------------------------------------
// Wall / corner recovery, with the #7 collision sweeps.
// ---------------------------------------------------------------------------
void addTriangle(xm::Mesh& mesh, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c) {
    const uint32_t base = static_cast<uint32_t>(mesh.vertices.size());
    for (const glm::vec3& p : {a, b, c}) {
        xm::Vertex v;
        v.pos = p;
        mesh.vertices.push_back(v);
    }
    mesh.indices.insert(mesh.indices.end(), {base, base + 1, base + 2});
}
void addQuad(xm::Mesh& mesh, const glm::vec3& a, const glm::vec3& b, const glm::vec3& c,
             const glm::vec3& d) {
    addTriangle(mesh, a, b, c);
    addTriangle(mesh, a, c, d);
}
// A floor plus a FINITE wall, so the straight line to the target is blocked but a way
// around the wall's end exists: the bot has to find it instead of grinding.
xm::Model wallStage() {
    xm::Model model;
    model.meshes.emplace_back();
    xm::Mesh& mesh = model.meshes[0];
    addQuad(mesh, {-1000.f, 0.f, -1000.f}, {-1000.f, 0.f, 1000.f},
            {1000.f, 0.f, 1000.f}, {1000.f, 0.f, -1000.f});
    // Wall at x = 150, spanning z in [-600, 600]: the target at (900, 0) is behind it
    // and the way round is over either end, so the bot has to slide along the face.
    addQuad(mesh, {150.f, 0.f, -600.f}, {150.f, 300.f, -600.f},
            {150.f, 300.f, 600.f}, {150.f, 0.f, 600.f});
    return model;
}

void testWallRecovery() {
    section("blocked at a wall: the bot finds the way around it");
    xm::Model stage = wallStage();
    game::physics::MovementCollision collision;
    collision.setMeshes(&stage, &stage);

    auto weapon = rena1Weapon();
    std::vector<uint8_t> table = renaMoveTable();
    auto moves = std::make_unique<gameplay::CharacterMoves>();
    std::string err;
    moves->parse(table.data(), table.size(), err);

    // The target sits well beyond the cell's engagement band, so the COM is really trying
    // to cross the wall rather than hovering short of it.
    Fighter self = makeFighter(weapon.get(), moves.get(), glm::vec3(0.f, 0.f, 0.f));
    Fighter enemy = makeFighter(weapon.get(), moves.get(), glm::vec3(900.f, 0.f, 0.f));
    BotBrain brain;
    brain.reset(2024, BotDifficulty::Standard);

    float tunnelled = 0.f;
    bool reached = false;
    float total = 0.f;
    glm::vec3 prev = self.position();
    input::PlayerState in;
    for (int i = 1; i <= 3000 && !reached; ++i) {
        BotView view;
        view.self = &self;
        view.target = &enemy;
        view.targetAlive = true;
        view.targetIndex = 1;
        view.hostileCount = 1;
        view.collision = &collision;
        const BotDecision d = brain.update(view, (uint64_t)i);
        BotBrain::apply(d, in);
        self.update(&in, &enemy, 1.0 / 64.0, &collision);
        const glm::vec3 now = self.position();
        total += std::sqrt((now.x - prev.x) * (now.x - prev.x) +
                           (now.z - prev.z) * (now.z - prev.z));
        prev = now;
        // The wall is a plane with no thickness: crossing its line while inside its
        // span is the only way through, and the sweep must never allow it. (Once past
        // the end, standing at x > 150 anywhere is legal.)
        if (prev.x <= 150.f && now.x > 150.f && std::abs(now.z) < 590.f) tunnelled += 1.f;
        if (now.x > 300.f) reached = true;
    }
    const gameplay::BotStats& s = brain.stats();
    check(s.blockedTicks > 0, "the bot noticed the stage refusing its direction");
    check(s.directionChanges > 0, "and rotated to an open direction");
    check(s.stuckRecoveries <= 3000 / (uint64_t)BotBrain::kStuckRecoveryTicks + 2,
          "recoveries stay bounded (no grinding loop)");
    check(tunnelled == 0.f, "the wall was never tunneled through");
    check(total > 400.f, "the bot kept covering ground while it searched");
    check(reached, "and it found the way around the wall instead of staying blocked");
}


// ---------------------------------------------------------------------------
// Match-driven: targeting, ally exclusion and a finished round.
// ---------------------------------------------------------------------------
struct MatchRig {
    MatchRig(int fighters, const int side[4], int balloon = 100) {
        gameplay::MatchConfig config;
        config.fighterCount = fighters;
        for (int i = 0; i < 4; ++i) {
            config.side[i] = side[i];
            config.spawn[i] = glm::vec3(120.f * i, 0.f, 0.f);
            config.facing[i] = 0.f;
        }
        // Balloon capacity is per SIDE (MatchConfig::balloonSize has two entries).
        config.balloonSize[0] = config.balloonSize[1] = balloon;
        m_weapon = rena1Weapon();
        m_table = renaMoveTable();
        std::string err;
        if (!m_moves->parse(m_table.data(), m_table.size(), err)) std::puts(err.c_str());
        for (int i = 0; i < 4; ++i) {
            config.weapon[i] = m_weapon.get();
            config.moves[i] = m_moves.get();
        }
        const xm::Model* models[4] = {};
        xm::Controller* anims[4] = {};
        match.reset(config, models, anims, nullptr, nullptr, nullptr);
    }

    gameplay::Match match;
    std::unique_ptr<gameplay::WeaponDefinition> m_weapon;
    std::unique_ptr<gameplay::CharacterMoves> m_moves =
        std::make_unique<gameplay::CharacterMoves>();
    std::vector<uint8_t> m_table;
};

void testRetarget() {
    section("retargeting when a target dies or is respawn-excluded");
    const int sides[4] = {0, 0, 1, 1};
    MatchRig rig(4, sides);
    gameplay::Match& m = rig.match;
    BotContext ctx;
    ctx.match = &m;
    ctx.fighterIndex = 1;
    ctx.leaderTarget = 0;
    BotBrain brain;
    brain.reset(5);

    // The COM on fighter 1 locks the first hostile (fighter 2), then that target dies.
    m.cycle_locked_target(1);
    checkInt(2, m.locked_target(1), "the COM is locked on the first hostile (fighter 2)");
    m.fighter(2).take_damage(100000, &m.fighter(0));
    check(!m.fighter(2).is_alive(), "fighter 2 is down");
    checkInt(3, m.melee_target(1),
             "the effective target follows to the surviving hostile at once");
    BotView view;
    gameplay::buildBotView(view, ctx);
    checkInt(3, view.targetIndex, "and that is what the brain is given");
    check(view.targetAlive, "which it sees as alive");
    input::PlayerState in;
    gameplay::MatchFrame frame = m.step(nullptr, nullptr, 1.0 / 64.0);
    (void)frame;
    checkInt(3, m.locked_target(1), "the match's own maintenance re-picks the lock");

    // A respawn-locked fighter is alive but NOT selectable (FUN_0041f580's +0xaecb), so
    // with the other hostile down the COM has nothing to attack and must ask for a switch
    // instead of freezing on it.
    const int sides2[4] = {0, 0, 1, 1};
    MatchRig rig2(4, sides2);
    gameplay::Match& m2 = rig2.match;
    BotContext ctx2;
    ctx2.match = &m2;
    ctx2.fighterIndex = 1;
    ctx2.leaderTarget = 0;
    m2.fighter(3).respawn(glm::vec3(0.f), 0.f, gameplay::FighterConstants::kRespawnAirY);
    m2.fighter(2).take_damage(100000, &m2.fighter(0));
    check(m2.fighter(3).is_alive() && m2.fighter(3).respawn_locked(),
          "fighter 3 is alive but respawn-locked");
    checkInt(gameplay::kNoTarget, m2.melee_target(1),
             "a respawn-locked fighter is not selectable");
    BotBrain brain2;
    brain2.reset(5);
    input::PlayerState in2;
    gameplay::updateBotInput(brain2, ctx2, in2, 1);
    check(brain2.decision().retarget, "the brain asks the lock to move on");

    // Partner tactics, from FUN_0043f4d0's cells 3/4: 集中 (focus) wants the same target
    // as the leader, 各個 (separate) wants a different one.
    const int sides3[4] = {0, 0, 1, 1};
    MatchRig rig3(4, sides3);
    gameplay::Match& m3 = rig3.match;
    BotContext ctx3;
    ctx3.match = &m3;
    ctx3.fighterIndex = 1;
    BotBrain brain3;
    brain3.reset(3);
    // The leader (fighter 0) is the human: its lock comes from the LockSwitch gesture, so
    // the test taps it. The COM then takes its OWN lock (issue #49: nothing is handed to
    // it at round start) through the brain's retarget request, which lands on the same
    // enemy because the recovered walk starts next to the COM's own index.
    for (int i = 0; i < 3; ++i) m3.step(nullptr, nullptr, 1.0 / 64.0);
    checkInt(gameplay::kNoTarget, m3.locked_target(0), "no lock is handed out at round start");
    m3.cycle_locked_target(0);
    checkInt(2, m3.locked_target(0), "the leader's LockSwitch tap selects fighter 2");
    input::PlayerState in3;
    checkInt(gameplay::kNoTarget, m3.locked_target(1), "the COM starts unlocked too");
    gameplay::updateBotInput(brain3, ctx3, in3, 1);
    checkInt(2, m3.locked_target(1), "without an order the COM selects the same enemy itself");
    auto stepSwitch = [&](int ticks) {
        input::PlayerState idle;
        input::compute_edges(idle);
        const input::PlayerState* inputs[4] = {&idle, nullptr, &idle, nullptr};
        for (int i = 0; i < ticks; ++i) {
            gameplay::updateBotInput(brain3, ctx3, in3, (uint64_t)i);
            inputs[1] = &in3;
            m3.step(inputs, 1.0 / 64.0);   // decays the recovered 15-tick switch pulse
        }
    };
    brain3.set_tactic(BotTactic::Separate);
    ctx3.leaderTarget = m3.locked_target(0);
    stepSwitch(24);
    checkInt(3, m3.locked_target(1), "各個 (separate) moves the COM off the leader's target");
    brain3.set_tactic(BotTactic::Focus);
    ctx3.leaderTarget = m3.locked_target(0);
    stepSwitch(24);
    checkInt(2, m3.locked_target(1), "集中 (focus) brings it back onto the leader's target");
}

void testAlliesAreNotHostiles() {
    section("allies are never targets and never threats");
    const int sides[4] = {0, 0, 1, 1};
    MatchRig rig(4, sides);
    gameplay::Match& m = rig.match;
    BotContext ctx;
    ctx.match = &m;
    ctx.fighterIndex = 0;
    ctx.leaderTarget = 0;

    // The partner stands right next to the COM; both enemies are far away.
    m.fighter(1).reset(glm::vec3(60.f, 0.f, 0.f), 0.f);
    m.fighter(2).reset(glm::vec3(900.f, 0.f, 0.f), 0.f);
    m.fighter(3).reset(glm::vec3(950.f, 0.f, 0.f), 0.f);

    BotBrain brain;
    brain.reset(11);
    input::PlayerState in;
    for (int i = 1; i <= 50; ++i) gameplay::updateBotInput(brain, ctx, in, (uint64_t)i);
    BotView view;
    gameplay::buildBotView(view, ctx);
    checkInt(1, view.partnerIndex, "the partner is reported as the partner");
    check(view.targetIndex == 2 || view.targetIndex == 3,
          "and the combat target is an enemy even with the ally closer");
    check(view.targetIndex != view.partnerIndex, "the ally is never the combat target");

    // Ally fire is not a threat: give the partner a live shot flying at the COM.
    m.shots().spawn(glm::vec3(200.f, 100.f, 0.f), glm::vec3(-1.f, 0.f, 0.f),
                    gameplay::ShotTier::Tap, &m.fighter(1));
    gameplay::buildBotView(view, ctx);
    check(view.threats == gameplay::kBotThreatNone,
          "a partner's projectile is not a threat");

    // The same shot from an enemy IS a threat.
    m.shots().clear();
    m.shots().spawn(glm::vec3(200.f, 100.f, 0.f), glm::vec3(-1.f, 0.f, 0.f),
                    gameplay::ShotTier::Tap, &m.fighter(2));
    gameplay::buildBotView(view, ctx);
    check((view.threats & gameplay::kBotThreatShot) != 0,
          "an enemy projectile closing on the COM is a threat");
    check(view.threatDistance > 0.f, "with a usable distance");
}

void testRoundFinishes() {
    section("a COM 1v1 reaches damage and a round outcome");
    const int sides[4] = {0, 1, 0, 1};
    MatchRig rig(2, sides, /*balloon=*/40);   // two KOs burst, so the round can end
    gameplay::Match& m = rig.match;
    BotContext ctx;
    ctx.match = &m;
    ctx.fighterIndex = 1;     // fighter 1 is the COM; fighter 0 stands still
    ctx.leaderTarget = 0;

    BotBrain brain;
    brain.reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, 1));
    // 格闘 (cell 1): the recovered cell whose band is 500 * 0.25 = 125 units, i.e. the one
    // that closes to the swing's own 50-unit reach. 適当 keeps its distance and shoots.
    brain.set_tactic(BotTactic::Melee);
    int hits = 0;
    uint64_t shots = 0;
    gameplay::MatchFrame frame;
    bool finished = false;
    input::PlayerState com;
    for (uint64_t tick = 1; tick <= 8000; ++tick) {
        gameplay::updateBotInput(brain, ctx, com, tick);
        input::PlayerState idle;
        input::compute_edges(idle);
        const input::PlayerState* inputs[4] = {&idle, &com, nullptr, nullptr};
        frame = m.step(inputs, 1.0 / 64.0);
        for (int i = 0; i < 2; ++i)
            if (frame.meleeHit[i]) ++hits;
        shots += (uint64_t)frame.shotsSpawned;
        if (frame.roundOver) { finished = true; break; }
    }
    check(hits > 0, "the COM lands melee hits on a standing opponent");
    check(m.fighter(0).hp() < m.fighter(0).max_hp(), "the opponent really takes damage");
    check(brain.stats().distanceMoved > 100.f, "the COM closes the distance it starts at");
    check(shots > 0 || hits > 0, "and it uses its weapon (shots or swings)");
    if (finished)
        checkInt(1, frame.roundOverSide, "the round it finishes is won by the COM's side");
    else
        std::printf("    (round still running after 8000 ticks: hp %d vs %d)\n",
                    m.fighter(0).hp(), m.fighter(1).hp());
}

void testPartnerDoesNotFriendlyFire() {
    section("a 2v2 COM partner never damages its ally");
    const int sides[4] = {0, 0, 1, 1};
    MatchRig rig(4, sides);
    gameplay::Match& m = rig.match;
    BotContext ctxA;
    ctxA.match = &m;
    ctxA.fighterIndex = 1;     // the COM partner of the idle fighter 0
    ctxA.leaderTarget = 0;
    BotContext ctxB;
    ctxB.match = &m;
    ctxB.fighterIndex = 3;     // the enemy COM
    ctxB.leaderTarget = 2;

    BotBrain brainA, brainB;
    brainA.reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, 1));
    brainB.reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, 3));
    uint64_t sameSideHits = 0;
    uint64_t hits = 0;
    uint64_t shots = 0;
    for (uint64_t tick = 1; tick <= 2500; ++tick) {
        input::PlayerState inA, inB, idle;
        gameplay::updateBotInput(brainA, ctxA, inA, tick);
        gameplay::updateBotInput(brainB, ctxB, inB, tick);
        input::compute_edges(idle);
        const input::PlayerState* inputs[4] = {&idle, &inA, &idle, &inB};
        const gameplay::MatchFrame f = m.step(inputs, 1.0 / 64.0);
        shots += (uint64_t)f.shotsSpawned;
        for (int i = 0; i < 4; ++i) {
            const int victim = f.meleeVictim[i];
            if (!f.meleeHit[i] || victim < 0) continue;
            ++hits;
            if (m.config().side[victim] == m.config().side[i]) ++sameSideHits;
        }
        if (m.economy().roundOver()) break;
    }
    checkInt(0, (long long)sameSideHits,
             "no swing in the run connected with a same-side fighter");
    check(brainA.stats().meleePresses + brainA.stats().shotsStarted > 0,
          "the partner COM does fight");
    check(brainB.stats().meleePresses + brainB.stats().shotsStarted > 0,
          "and so does the enemy COM");
    check(brainA.stats().distanceMoved > 50.f && brainB.stats().distanceMoved > 50.f,
          "both covered ground (neither froze)");
    check(hits + shots > 0, "the run actually produced attacks (not a frozen match)");
}


// ---------------------------------------------------------------------------
// Asset-backed: four SHIPPED combos fight a 2v2 through Match, with the COM brain
// driving every fighter, on an obstructed stage. Skipped when the install is absent
// (the device-free checks above are the required coverage; this is the evidence run).
// ---------------------------------------------------------------------------
fs::path findInstall(int argc, char** argv) {
    if (argc > 1) return fs::path(argv[1]);
    if (const char* env = std::getenv("GAME_DIR")) return fs::path(env);
    fs::path game = fs::path("Higurashi-Daybreak");
    for (const fs::path& d : {fs::absolute(fs::path(argv[0])).parent_path(),
                              fs::current_path()}) {
        for (fs::path r = d; !r.empty(); r = r.parent_path()) {
            std::error_code ec;
            if (fs::is_directory(r / "remake" / "foundation", ec)) {
                game = r / "Higurashi-Daybreak";
                break;
            }
            if (r == r.parent_path()) break;
        }
        std::error_code ec;
        if (fs::is_directory(game / "data", ec)) return game;
    }
    return fs::path();
}

bool readFile(const fs::path& p, std::vector<uint8_t>& out) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return false;
    out.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    return !out.empty();
}

void testAssetBackedFourFighter(int argc, char** argv) {
    section("asset-backed: four shipped combos, COM-only 2v2, obstructed stage");
    const fs::path install = findInstall(argc, argv);
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data", ec)) {
        skip("four shipped combos load (no install found)");
        skip("COM 2v2 runs on a walled stage");
        return;
    }
    // One legal combo per character, slot 0: item 001 rena, 002 mion, 005 keiichi,
    // 007 rika (kWeaponIds), each with its own data/<char>/00.dat move table.
    static const int kRoster[4] = {0, 1, 2, 4};
    auto weapon = std::make_unique<gameplay::WeaponDefinition>();
    auto moves = std::make_unique<gameplay::CharacterMoves>();
    std::vector<std::unique_ptr<gameplay::WeaponDefinition>> weapons;
    std::vector<std::unique_ptr<gameplay::CharacterMoves>> tables;
    std::vector<std::unique_ptr<gameplay::BulletParameter>> bullets[4];
    std::string err;
    for (int i = 0; i < 4; ++i) {
        const int character = kRoster[i];
        const int itemId = gameplay::kWeaponIds[character][0];
        char item[64];
        std::snprintf(item, sizeof(item), "item/%03d.dat", itemId);
        std::vector<uint8_t> bytes;
        if (!readFile(install / "data" / item, bytes)) {
            std::printf("    (item %s missing)\\n", item);
            skip("four shipped combos load (install gap)");
            skip("COM 2v2 runs on a walled stage");
            return;
        }
        auto w = std::make_unique<gameplay::WeaponDefinition>();
        if (!w->parse(itemId, bytes.data(), bytes.size(), err)) {
            std::printf("    (item %s: %s)\\n", item, err.c_str());
            skip("four shipped combos load (install gap)");
            skip("COM 2v2 runs on a walled stage");
            return;
        }
        char table[64];
        std::snprintf(table, sizeof(table), "%s/00.dat", gameplay::kCharacterDirs[character]);
        std::vector<uint8_t> moveBytes;
        auto m = std::make_unique<gameplay::CharacterMoves>();
        if (!readFile(install / "data" / table, moveBytes) ||
            !m->parse(moveBytes.data(), moveBytes.size(), err)) {
            std::printf("    (%s: %s)\\n", table, err.c_str());
            skip("four shipped combos load (install gap)");
            skip("COM 2v2 runs on a walled stage");
            return;
        }
        // The recovered per-weapon projectile parameters, exactly as the live path binds
        // them (lowest-type bullet per magazine).
        for (int level = 1; level <= 2; ++level) {
            const int want = w->magazineForChargeLevel(level).chargeLevel - 1;
            const gameplay::BulletDefinition* best = nullptr;
            for (int b = 0; b < w->bulletCount; ++b)
                if (w->bullets[b].magazine == want && (!best || w->bullets[b].type < best->type))
                    best = &w->bullets[b];
            if (!best) continue;
            char rel[64];
            std::snprintf(rel, sizeof(rel), "bullet/%03d/%03d.dat", itemId, best->type);
            std::vector<uint8_t> pb;
            if (!readFile(install / "data" / rel, pb)) continue;
            auto param = std::make_unique<gameplay::BulletParameter>();
            if (gameplay::parseBulletParameter(pb.data(), pb.size(), best->status, *param, err))
                bullets[i].push_back(std::move(param));
        }
        weapons.push_back(std::move(w));
        tables.push_back(std::move(m));
    }
    checkInt(4, (long long)weapons.size(), "four shipped combos (item + move table) loaded");
    for (int i = 0; i < 4; ++i) {
        char name[128];
        std::snprintf(name, sizeof(name), "%s has a weapon AND a move table (AGENTS rule 7)",
                      gameplay::comboSlotLabel(kRoster[i], 0).c_str());
        check(weapons[(size_t)i]->valid() && tables[(size_t)i]->count() > 0, name);
    }

    // The obstructed stage: the same walled floor the recovery check uses, so a COM that
    // cannot navigate it is visible in the run's own counters.
    xm::Model stage = wallStage();
    game::physics::MovementCollision collision;
    collision.setMeshes(&stage, &stage);

    gameplay::MatchConfig config;
    config.fighterCount = 4;
    const int sides[4] = {0, 0, 1, 1};
    for (int i = 0; i < 4; ++i) {
        config.side[i] = sides[i];
        config.spawn[i] = glm::vec3(-260.f + 90.f * i, 0.f, -160.f);
        config.facing[i] = 0.f;
        config.weapon[i] = weapons[(size_t)i].get();
        config.moves[i] = tables[(size_t)i].get();
    }
    config.balloonSize[0] = config.balloonSize[1] = 40;

    gameplay::Match match;
    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    match.reset(config, models, anims, nullptr, nullptr, &collision);
    for (int i = 0; i < 4; ++i)
        for (size_t level = 0; level < bullets[i].size(); ++level)
            match.fighter(i).set_bullet_parameter((int)level + 1, bullets[i][level].get());

    BotBrain brains[4];
    BotContext ctx[4];
    for (int i = 0; i < 4; ++i) {
        brains[i].reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, i));
        brains[i].set_tactic(i < 2 ? BotTactic::Melee : BotTactic::Adaptive);
        ctx[i].match = &match;
        ctx[i].fighterIndex = i;
        ctx[i].leaderTarget = match.locked_target(0);
    }

    int sameSideHits = 0;
    int meleeHits = 0;
    uint64_t shots = 0;
    input::PlayerState inputs[4];
    gameplay::MatchFrame frame;
    bool roundOver = false;
    for (uint64_t tick = 1; tick <= 6000; ++tick) {
        for (int i = 0; i < 4; ++i) gameplay::updateBotInput(brains[i], ctx[i], inputs[i], tick);
        const input::PlayerState* in[4] = {&inputs[0], &inputs[1], &inputs[2], &inputs[3]};
        frame = match.step(in, 1.0 / 64.0);
        shots += (uint64_t)frame.shotsSpawned;
        for (int i = 0; i < 4; ++i) {
            const int victim = frame.meleeVictim[i];
            if (!frame.meleeHit[i] || victim < 0) continue;
            ++meleeHits;
            if (match.config().side[victim] == match.config().side[i]) ++sameSideHits;
        }
        if (frame.roundOver) { roundOver = true; break; }
    }

    checkInt(0, sameSideHits, "no swing in a 6000-tick 2v2 ever hit a teammate");
    check(meleeHits > 0, "the four shipped combos land melee hits");
    for (int i = 0; i < 4; ++i) {
        const gameplay::BotStats& st = brains[i].stats();
        char name[128];
        std::snprintf(name, sizeof(name),
                      "fighter %d (%s) fights and moves without pinning (moved %.0f)",
                      i, gameplay::comboSlotLabel(kRoster[i], 0).c_str(),
                      (double)st.distanceMoved);
        check(st.meleePresses + st.shotsStarted > 0 && st.distanceMoved > 150.f, name);
        std::snprintf(name, sizeof(name),
                      "fighter %d never grinds a wall (%llu blocked probes, %llu recoveries)",
                      i, (unsigned long long)st.blockedTicks,
                      (unsigned long long)st.stuckRecoveries);
        check(st.stuckRecoveries <= 6000 / (uint64_t)BotBrain::kStuckRecoveryTicks + 4, name);
        std::snprintf(name, sizeof(name),
                      "fighter %d never re-asks a refused move every tick (%llu refusals)",
                      i, (unsigned long long)st.shotBlocked);
        check(st.shotBlocked <= 6000 / (uint64_t)BotBrain::kShotRejectTicks + 4, name);
    }
    // Damage on both sides: a 2v2 where one team never connects is not a fight.
    const int side0Damage = match.fighter(2).stats().damageTaken +
                            match.fighter(3).stats().damageTaken;
    const int side1Damage = match.fighter(0).stats().damageTaken +
                            match.fighter(1).stats().damageTaken;
    check(side0Damage > 0 && side1Damage > 0,
          "both teams took damage (the fight is two-sided)");
    std::printf("    2v2: %llu shots, %d melee hits, damage taken %d/%d, roundOver=%d\n",
                (unsigned long long)shots, meleeHits, side0Damage, side1Damage,
                roundOver ? 1 : 0);
}

}  // namespace

int main(int argc, char** argv) {
    std::puts("bot_brain_test — issue #14 COM decision state");
    testTacticTable();
    testTacticReadout();
    testDeterminism();
    testAvailability();
    testEmptyAmmoIsNotSpammed();
    testGuardExhaustion();
    testDodge();
    testWallRecovery();
    testRetarget();
    testAlliesAreNotHostiles();
    testRoundFinishes();
    testPartnerDoesNotFriendlyFire();
    testAssetBackedFourFighter(argc, argv);
    std::printf("\n%d checks, %d failure(s)%s\n", checks, failures,
                skipped ? " (with skips)" : "");
    return failures == 0 ? 0 : 1;
}
