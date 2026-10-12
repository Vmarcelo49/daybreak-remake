#pragma once

#include "gameplay/weapon_definition.h"
#include "gameplay/shot_launch.h"
#include <iterator>

namespace gameplay {

// FUN_00649790 constructor -> vtable+0x18. These are executable rules, not NN.dat
// fields. Keeping the recovered program separate prevents animation tags or bullet
// rows from being guessed from a port state. Values are original units per update.
struct LocomotionDefinition {
    int character;
    int slot;
    unsigned handler;
    float walk;
    float forwardDash;
    float dashDecay, dashDrain, dashSteer;
    int dashHoldTick, dashHoldLength;
};
inline constexpr LocomotionDefinition kLocomotion[] = {
    {0,0,0x43ffc0,7.2f,17.f,0.75f,1.20f,4.00f,1,15}, {0,1,0x448220,7.2f,16.5f,0.75f,1.20f,4.00f,1,15}, {0,2,0x438310,2.5f,30.f,2.50f,1.20f,4.00f,1,15},
    {1,0,0x4582a0,6.5f,14.f,0.50f,0.80f,4.00f,1,15}, {1,1,0x461810,7.f,15.f,0.50f,0.80f,4.00f,1,15}, {1,2,0x44fa10,6.5f,14.f,0.50f,1.00f,4.00f,1,15},
    {2,0,0x46a190,7.f,15.f,0.75f,1.00f,4.00f,1,15}, {2,1,0x473610,7.f,15.f,0.75f,1.00f,4.00f,1,15}, {2,2,0x47b940,7.f,15.f,0.75f,1.00f,4.00f,1,15},
    {3,0,0x4a9c40,7.5f,17.f,0.65f,1.10f,5.50f,5,10}, {3,1,0x4b4090,7.5f,17.f,0.65f,1.10f,5.50f,5,10}, {3,2,0x4bc040,6.f,14.f,0.65f,1.30f,3.00f,5,10},
    {4,0,0x484be0,4.f,10.f,0.40f,0.60f,4.00f,3,15}, {4,1,0x492f70,4.f,10.f,0.40f,0.60f,4.00f,3,15}, {4,2,0x49d890,7.5f,16.5f,0.40f,0.90f,4.00f,3,15},
    {5,0,0x4f92a0,8.5f,20.f,1.00f,1.40f,5.00f,1,10}, {5,1,0x503510,8.5f,20.f,1.00f,1.40f,5.00f,1,10}, {5,2,0x50aea0,8.5f,20.f,1.00f,1.40f,5.00f,1,10},
    {6,0,0x516230,6.25f,16.25f,0.75f,1.10f,4.00f,4,15}, {6,1,0x51f880,6.25f,16.f,0.75f,1.30f,4.00f,4,15}, {6,2,0x527880,6.25f,16.25f,0.75f,1.30f,4.00f,4,15},
    {7,0,0x531ce0,6.75f,13.5f,0.50f,0.80f,4.00f,1,15}, {7,1,0x53bc00,5.5f,13.5f,0.50f,0.80f,4.00f,1,15}, {7,2,0x545f00,6.75f,13.5f,0.50f,0.80f,4.00f,1,15},
    {8,0,0x4c57f0,6.25f,11.5f,0.50f,1.10f,4.00f,5,15}, {8,1,0x4ccc00,6.25f,11.5f,0.50f,1.10f,4.00f,5,15}, {8,2,0x4d5980,6.25f,11.5f,0.50f,1.10f,4.00f,5,15},
    {9,0,0x4dee70,7.25f,15.5f,0.75f,1.00f,4.00f,4,15}, {9,1,0x4e7680,7.25f,15.5f,0.75f,0.80f,4.00f,4,15}, {9,2,0x4f0040,7.25f,15.5f,0.75f,0.80f,4.00f,4,15},
    {10,0,0x571ca0,6.5f,13.f,0.50f,0.90f,4.00f,2,15}, {10,1,0x57f600,6.5f,13.f,0.50f,0.90f,4.00f,2,15}, {10,2,0x58a6a0,6.5f,13.f,0.50f,0.90f,4.00f,2,15},
    {11,0,0x551410,6.f,22.5f,1.00f,1.40f,0.25f,6,15}, {11,1,0x55be80,6.f,22.5f,1.00f,1.40f,0.25f,6,15}, {11,2,0x566a40,6.f,22.5f,1.00f,1.40f,0.25f,6,15},
    {12,0,0x5b0990,6.75f,12.5f,0.50f,1.00f,4.00f,2,15}, {12,1,0x5b9680,6.75f,12.5f,0.50f,1.00f,4.00f,2,15}, {12,2,0x5c3350,6.75f,12.5f,0.50f,1.00f,4.00f,2,15},
    {13,0,0x595460,4.5f,22.5f,1.00f,1.50f,6.00f,1,10}, {13,1,0x59e630,4.5f,22.5f,1.00f,1.50f,6.00f,1,10}, {13,2,0x5a7ea0,4.5f,22.5f,1.00f,1.50f,6.00f,1,10},
    {14,0,0x5cb6a0,4.f,14.5f,0.40f,0.90f,5.00f,3,15},
    // FUN_005d5120's powered form changes both values; recovered below only for base form.
    {14,1,0x5d5120,4.f,13.5f,0.40f,1.00f,8.00f,3,15},
    {15,0,0x5e2af0,7.2f,17.f,0.75f,1.20f,4.00f,1,15}, {15,1,0x5ed860,7.2f,17.f,0.75f,1.20f,4.00f,1,15},
};

inline const LocomotionDefinition* locomotion(const CharacterMoves* moves) {
    if (!moves) return nullptr;
    const int slot = weaponSlotForItem(moves->character_index(), moves->weapon_id());
    for (const auto& row : kLocomotion)
        if (row.character == moves->character_index() && row.slot == slot) return &row;
    return nullptr;
}

// Rule gates — source-verified predicates, evaluated when the owning rule runs. A rule
// whose gate fails is skipped exactly like a rule outside its tick window, so a gate
// never has to be duplicated into the first/last fields.
//   kGatePowered / kGateNormal — the two halves of the `byte(+0x845) && word(+0x848)`
//     idiom. A body that fires a different row per half pairs its rules so exactly one
//     side runs; 514 of the 841 shoot bodies read the gate and the usage catalog's
//     "tag"/"special" variant is the powered half.
//   kGateCounter / kGateCounterMod / kGateCounterBelow — the move's own counter
//     (MoveOp::Counter), for the counter-gated salvos such as Rika 1's tick-30 pair
//     (`0x3e % 10 == 0`) and the freeze that ends when the counter reaches 60.
//     gateValue carries the modulus or the bound; 0 disables the test.
enum MoveGate : unsigned {
    kGateNone         = 0,
    kGatePowered      = 1u << 0,
    kGateNormal       = 1u << 1,
    kGateCounter      = 1u << 2,
    kGateCounterMod   = 1u << 3,
    kGateCounterBelow = 1u << 4,
    // `0 < w[0x1b7]`: this move has connected. 186 recovered bodies guard a launch or
    // a phase jump on it (the "follow-up on hit" family). The player struct's +0x1b7
    // has no writer in the available corpus, so the port reads its own contact flag and
    // the mapping is by role, not recovered byte-for-byte — labelled, not claimed.
    kGateContact      = 1u << 5,
    // `tick % gateValue == 0`: the repeated-emission cadence Mion 2's charges use
    // (`0xe < tick && tick % 5 == 0`). Combine with first/last for the lower bound.
    kGateTickMod      = 1u << 6,
    // The move's own scratch counter, which the bodies write with write_scratch and
    // which — unlike the phase tick — survives a phase change. Bodies gate repeated
    // emissions on exact values, so this is an equality test on gateValue.
    kGateCounterEquals = 1u << 7,
    // `gateValue2 < counter`: the lower half of a counter window (the bodies write both
    // compares, e.g. Mion 0's 402 turning while `0xe < c < 0x19`).
    kGateCounterAbove  = 1u << 8,
    // The AI's movement direction, word +0x278. Rika 2's tap is the measured user: row 2
    // below 0, row 0 at 0, row 1 above. Human-controlled fighters never have +0x278
    // written, so their slot publishes 0 and they take the row-0 branch.
    kGateDirLeft       = 1u << 9,
    kGateDirNeutral    = 1u << 10,
    kGateDirRight      = 1u << 11,
    // Squared-distance gates for the dash-attack bodies that latch their behavior on
    // how far the target was (Rena 331's strength latch at entry: distance2 < 810000).
    // The caller supplies the live squared distance; -1 means "unknown" and fails both.
    kGateNear          = 1u << 12,
    kGateFar           = 1u << 13,
};

enum class MoveOp { Speed, Decelerate, Turn, Approach, Launch, Hold, ActionCamera, Hide,
                    Active, Counter, CounterSet, CapturePitch, Voice,
                    // The attack-state vertical/body mechanics the original melee bodies
                    // own (FUN_0043ffc0/448220/438310 air fields +40/+58 and the exit
                    // branches). Vertical/Gravity carry the bodies' per-tick units:
                    // vertical is u/tick and gravity u/tick^2, converted at the op site.
                    Vertical,    // set vertical velocity (value u/tick)
                    Gravity,     // set the per-tick^2 fall rate for this move (sticky)
                    LandExit,    // on landing: switch to the row in value
                    LandPhase,   // on landing: enter_phase(value), zero speed/vertical
                    ContactExit, // on melee contact within the window: switch to value
                    JumpCancel,  // contact + held jump: leave into the jump state
                    PhaseExit,   // unconditional enter_phase(value) inside the window
                    ClockSkip,   // advance the phase clock value extra ticks this update
                    Gauge,       // add value thousandths to the special gauge (recovery)
                    // The 403/409/469 recovery bodies' shot-gauge refill (FUN_00448220
                    // cases 0x193/0x199/0x1d5): +0x834 gains 40 thousandths a tick, 5
                    // while a status timer (+0x7f4, producer FUN_0042e110's status family)
                    // is active — the port models no status, so the fast rate is the only
                    // reachable one and the slow branch stays cited, not bound.
                    Recharge,    // add value thousandths to the shot gauge, capped at 1000
                    // The melee voice cue (FUN_004223d0/FUN_00422490 with the small event
                    // ids): value is the ordinary event, rule.voice carries the entry
                    // alternative pair where the body draws one (the 32-family). The
                    // close-target cascade (voices 0/15/5, priority 12) resolves at the
                    // op site from the live distance/bearing.
                    MeleeVoice,
                    // The action bodies' SE request (FUN_0042c8b0 positional /
                    // FUN_0042c880 non-positional): value is the `data/se/%03d.wav` id
                    // (FUN_0064b060 -> FUN_0064ae70 indexes the manager's data/se table
                    // and FUN_0065a260 plays it at the actor position).
                    SoundEffect,
                    // The actor's effect request, a DIFFERENT call from the SE above:
                    // `(*actor + 0xc)(id, x, y, z, heading, pitch)` is the actor-side
                    // FUN_00421aa0, which converts the angles to a direction and forwards
                    // to FUN_00435990 -> the effect manager's create with that pose. The
                    // id indexes data/effect by `id / 10` (FUN_0042eba0's 100 slots), so
                    // 320/340/350 resolve to 032/034/035.dat; `third > 0` is the 350
                    // beats' two rand%40-20 draws, which the op consumes in the body's
                    // order.
                    Effect,
                    // On landing: enter_phase(value) and seek the phase clock to `second`
                    // ticks (Rena+2's 402 late landing: phase 1, clock 25).
                    LandSeek,
                    // Set the phase clock to `value` this update (Rena+2's 350/360
                    // 42->95 jump, written to both the primary and secondary clocks).
                    ClockSeek,
                    // Clamp the phase clock at `value` (Rena+2's 402 phase-0 cap 17: the
                    // clock stops so the row waits for its landing branch).
                    ClockClamp,
                    // Bind attachment slot (value) to item model (second) for this move
                    // (FUN_00434a70; Rena+1's 450/460 bind slot 0 to model 2).
                    PropModel,
                    // Scale the carried speed (value) and vertical (second) at the
                    // window's first tick (Rena+1's 460 halves the entry speed; Rena+2's
                    // air 360 keeps a tenth of both).
                    ScaleMotion,
                    // Cut the melee contact volume while matching (the bodies'
                    // FUN_00434bd0 windows; the posed records stay the default).
                    ContactOff };
enum class ShotVoiceMagazine { Primary, Secondary };
enum class ShotVoiceCompare { Equal, Less };

// FUN_004223d0/FUN_00422490 choose a voice group from the rounds remaining at the cue
// point (`+0x1b7` primary, `+0x1c8` secondary). Event ids follow the recovered 40-name
// table at VA 0x6b73b0; audio owns the names and playback policy.
struct ShotVoiceSpec {
    int event = -1;
    int finalEvent = -1;
    ShotVoiceMagazine magazine = ShotVoiceMagazine::Primary;
    ShotVoiceCompare comparison = ShotVoiceCompare::Equal;
    int rounds = 1;
    int alternativeFirst = -1;
    int alternativeSecond = -1;
    int alternativeSecondPercent = 0;
};

constexpr ShotVoiceSpec shot_voice(int event, int finalEvent = -1,
                                   ShotVoiceMagazine magazine = ShotVoiceMagazine::Primary,
                                   ShotVoiceCompare comparison = ShotVoiceCompare::Equal,
                                   int rounds = 1) {
    return ShotVoiceSpec{event, finalEvent, magazine, comparison, rounds};
}

constexpr ShotVoiceSpec shot_voice_pair(int event, int first, int second,
                                        int secondPercent) {
    ShotVoiceSpec spec;
    spec.event = event;
    spec.alternativeFirst = first;
    spec.alternativeSecond = second;
    spec.alternativeSecondPercent = secondPercent;
    return spec;
}

constexpr int resolve_shot_voice_event(const ShotVoiceSpec& voice,
                                       int primaryRounds, int secondaryRounds) {
    if (voice.finalEvent < 0) return voice.event;
    const int remaining = voice.magazine == ShotVoiceMagazine::Primary
                              ? primaryRounds : secondaryRounds;
    const bool final = voice.comparison == ShotVoiceCompare::Equal
                           ? remaining == voice.rounds : remaining < voice.rounds;
    return final ? voice.finalEvent : voice.event;
}
// CapturePitch latches the target elevation into the move's pitch scratch (the bodies'
// write_scratch of the FUN_0042da80/FUN_0066b668 value). The bodies bound the scratch
// with two independent compares, so the rule states both ends: second is the low
// magnitude (low = -second), third is the high bound. Most clamp symmetrically; Mion
// 0's 450 is asymmetric ([-40, +45]). A nonzero value reproduces the compare/assign
// mismatch instead of clamping (Keiichi's air tap and Mion 1's 460 compare +-30 and
// assign +-45).
// Aggregate order is part of the contract: the tables are positional literals, so the
// fields every rule might set (move/phase/first/last/op/value/second/third/gate/
// gateValue) come before the two spec objects only world-style Launch rules carry.
struct MoveRule {
    int move, phase, first, last;
    MoveOp operation;
    float value;
    float second = 0.f;
    float third = 0.f;
    unsigned gate = kGateNone;
    int gateValue = 0;  // kGateCounterMod/kGateTickMod modulus, kGateCounterBelow bound
    ShotOriginSpec origin{};
    ShotAimSpec aim{};
    // Second counter bound. Declared last so every existing positional literal — which
    // stops at origin/aim — keeps its meaning.
    int gateValue2 = 0;
    // The body's random spread for a Launch rule (see ShotSpreadSpec). Defaulted, so a
    // rule that does not spread consumes no draw.
    ShotSpreadSpec spread{};
    // The bodies wrap some requests in a `for` loop, firing the whole volley inside ONE
    // tick (Mion 1's 450/460 run 15 iterations at tick 17; Rena 2's 400 runs 10). The
    // loop is a property of the request, not of the spread, so it is stated separately —
    // and each iteration draws its own spread, which is what makes the volley a fan.
    int repeats = 1;
    ShotVoiceSpec voice{};
};

// Voice-call timing and gates live in the same rule stream as the move body. The original
// can speak before its request (Rena 1 state400 calls ShotC at tick15; the request is tick18).
constexpr MoveRule voice_rule(int move, int phase, int first, int last,
                              ShotVoiceSpec voice, unsigned gate = kGateNone,
                              int gateValue = 0) {
    MoveRule rule{move, phase, first, last, MoveOp::Voice, 0.f, 0.f, 0.f,
                  gate, gateValue};
    rule.voice = voice;
    return rule;
}

// The melee voice cue (FUN_004223d0(voice, priority)): `event` is the ordinary id,
// and the close-target cascade (voices 0/15/5 at priority 12, FUN_0043ffc0:601-627)
// resolves at the op site from the live distance and battle bearing. `pair`/`percent`
// reproduce the FUN_00422490 choice draws (the 32-family: `rand%100 < percent` picks
// `second`, else `first`).
constexpr MoveRule melee_voice_rule(int move, int phase, int first, int last, int event,
                                    int firstChoice = -1, int secondChoice = -1,
                                    int percent = 0) {
    MoveRule rule{move, phase, first, last, MoveOp::MeleeVoice,
                  static_cast<float>(event)};
    if (firstChoice >= 0) {
        rule.voice.event = event;
        rule.voice.alternativeFirst = firstChoice;
        rule.voice.alternativeSecond = secondChoice;
        rule.voice.alternativeSecondPercent = percent;
    }
    return rule;
}

// A gameplay SE request. `id` is the `data/se/%03d.wav` index the body passes to
// FUN_0042c8b0/0042c880 — a SOUND id, not an entry in data/effect (the effect catalog
// stops at id 40 while these bodies use 60..77 and 170..172, all present under data/se).
constexpr MoveRule sound_effect_rule(int move, int phase, int first, int last, int id) {
    MoveRule rule{move, phase, first, last, MoveOp::SoundEffect, static_cast<float>(id)};
    return rule;
}

// The actor's effect request (a different call — see MoveOp::Effect). `jitter` states
// whether the body draws the two rand%40-20 angles before the request, which is part of
// the RNG contract and must stay off for a beat that passes fixed angles.
constexpr MoveRule effect_rule(int move, int phase, int first, int last, int id,
                               bool jitter = true) {
    MoveRule rule{move, phase, first, last, MoveOp::Effect, static_cast<float>(id),
                  0.f, jitter ? 1.f : 0.f};
    return rule;
}

// The attacker-side guard exit: which Rena melee rows test the contact word's bit 2
// (FUN_0042c7b0() & 2) each tick and hand the attacker to 392. Exhaustive per-file
// scan of every `& 2` site (FUN_0043ffc0:12, FUN_00448220:10, FUN_00438310:13):
//   301/310/311/331/340 — present in all three weapons;
//   302 and 330          — present in weapons 0 and 2, absent from weapon 1
//                          (FUN_00448220 has no 0x12e case at all and no 0x14a guard);
//   300/320/329/332/333/334/341/350 — absent from every weapon.
// Every melee-row exit targets 0x188 (392) and pairs with FUN_0042c800(0); the 0x33
// effect belongs to the 390/391/393/394 exit states, not to these rows.
inline int rena_guard_exit_row(int weaponSlot, int moveId) {
    const bool has = moveId == 301 || moveId == 310 || moveId == 311 ||
                     moveId == 331 || moveId == 340 ||
                     (weaponSlot != 1 && (moveId == 302 || moveId == 330));
    return has ? 392 : -1;
}

// Original FUN_0043ffc0. Inclusive tick intervals; phase -1 means all phases.
// Launch.value is an ITEM ROW, never a model number, animation set or magazine.
// Hide/Active are the attachment slot 0..1 operands of FUN_00434a70 and FUN_00434b30: the
// executor re-binds slot0<-prop0 and slot1<-prop1 and deactivates both at the top of every
// frame (0x43fff4/0x440006/0x440014), so Hide lasts only while its ticks keep matching and
// Active must be re-asserted on every tick of its window. Active is also what grows the
// weapon ribbon: FUN_0042fff0 reads the prop's own active latch (prop+0x38), so a tick
// outside the window decays it instead.
inline constexpr MoveRule kRenaRules[] = {
    {300,0,0,0,MoveOp::Speed,15.f,25.f,640000.f},
    {300,0,0,0,MoveOp::Turn,180.f},
    {300,0,1,9999,MoveOp::Turn,20.f},
    {300,1,0,9999,MoveOp::Turn,20.f},
    {300,1,0,9999,MoveOp::Approach,90000.f,10.f,2.f},
    {300,2,0,9999,MoveOp::Decelerate,1.5f},
    {300,2,0,3,MoveOp::Turn,5.f},
    // 300: phase 2, ticks 3..10 (0x441754 adf4==2, 0x441760 >2, 0x44176c <0xb).
    {300,2,3,10,MoveOp::Active,0.f},
    {300,2,3,10,MoveOp::Active,1.f},
    // 301: ticks 10..16 (0x4418fc >9, 0x441908 <0x11), no phase guard.
    {301,0,1,1,MoveOp::Speed,10.f},
    {301,0,16,16,MoveOp::Speed,0.f},
    {301,-1,10,16,MoveOp::Active,0.f},
    {301,-1,10,16,MoveOp::Active,1.f},
    {301,-1,0,9999,MoveOp::ActionCamera,2.f},
    {301,0,0,7,MoveOp::Turn,20.f,1.f},
    {302,0,0,0,MoveOp::Speed,15.f},
    {302,0,17,17,MoveOp::Speed,0.f},
    // 302: ticks 12..17 (0x441a98 >0xb, 0x441aa4 <0x12), no phase guard.
    {302,-1,12,17,MoveOp::Active,0.f},
    {302,-1,12,17,MoveOp::Active,1.f},
    {302,-1,0,9999,MoveOp::ActionCamera,2.f},
    {302,0,0,11,MoveOp::Turn,20.f,1.f},
    {330,0,0,9999,MoveOp::Turn,5.f},
    {330,1,0,9999,MoveOp::Turn,5.f},
    {330,1,0,9999,MoveOp::Speed,30.f},
    {330,2,0,9999,MoveOp::Decelerate,2.f},
    // 330: phase 2, ticks 6..9 (0x44280e adf4==2, 0x44281a >5, 0x442826 <0xa).
    {330,2,6,9,MoveOp::Active,0.f},
    {330,2,6,9,MoveOp::Active,1.f},
    {340,0,0,0,MoveOp::Speed,15.f},
    {340,0,0,9,MoveOp::Turn,18.f},
    {340,0,15,15,MoveOp::Speed,0.f},
    // 340: ticks 16..24 (0x44311b >0xf, 0x443127 <0x19), no phase guard.
    {340,-1,16,24,MoveOp::Active,0.f},
    {340,-1,16,24,MoveOp::Active,1.f},
    // 310 back kick (directional melee, weapon 0/1 body): the entry snaps 180 and
    // the phase-0 approach is 20, phase 1 approaches 15 and hands straight to
    // phase 2 on its only tick, phase 2 decelerates 1 with the approach closed
    // after frame 5. The body's contact/ribbon span is phase-2 frames 5..7 and the
    // jump-cancel window (frame > 12 on contact, FUN_0043ffc0 case 0x136) leaves
    // into the jump; its effect 62 / voice 2 cues sit at frame 4 (cue block below).
    {310,0,0,0,MoveOp::Speed,30.f},
    {310,0,0,0,MoveOp::Turn,180.f},
    {310,0,0,9999,MoveOp::Turn,20.f},
    {310,1,0,0,MoveOp::Turn,15.f},
    {310,1,0,0,MoveOp::PhaseExit,2.f},
    {310,2,0,9999,MoveOp::Decelerate,1.f},
    {310,2,0,4,MoveOp::Turn,5.f},
    {310,-1,5,7,MoveOp::Active,0.f},
    {310,-1,5,7,MoveOp::Active,1.f},
    {310,2,13,9999,MoveOp::JumpCancel,0.f,kGateContact},
    // 311 side kick (weapon 0): entry speed 20 decaying .2 through phase 0,
    // approach 10 until frame 20, full stop at frame 25.
    {311,0,0,9999,MoveOp::Decelerate,.2f},
    {311,0,0,0,MoveOp::Speed,20.f},
    {311,-1,0,0,MoveOp::Turn,180.f},
    {311,0,0,19,MoveOp::Turn,10.f},
    {311,-1,25,25,MoveOp::Speed,0.f},
    // 320 chase: the body in fighter.cpp owns the arc (ChasePolicy); these rules
    // carry its fall and landing windows — gravity only in phase 2 past tick 5,
    // the landing hands to the 329 recovery past tick 10 (case 0x140's frame>5
    // gravity and frame>10 && grounded exit).
    {320,0,0,0,MoveOp::Gravity,0.f},
    {320,2,6,9999,MoveOp::Gravity,.5f},
    {320,2,11,9999,MoveOp::LandExit,329.f},
    // The 320 body's contact gate (FUN_0043ffc0:985-990; the same guard in all three
    // handlers): the volume is armed by FUN_00434b30 only in phase 2 ticks 0..7 and
    // cut by FUN_00434bd0 on every other tick, including all of phases 0 and 1.
    {320,0,0,9999,MoveOp::ContactOff},
    {320,1,0,9999,MoveOp::ContactOff},
    {320,2,8,9999,MoveOp::ContactOff},
    // 329/333 dash recovery (battle_dash_recovery, character 0): speed, vertical
    // and gravity zero, and the special gauge refills 40/1000 per tick — the
    // slowed rate (5) belongs to the hit-slow state the port does not carry yet.
    // The entry rules carry a one-tick grace: the landing switch lands between a
    // rule pass and the phase clock's increment, so the row's first full rule
    // pass observes elapsed 1, not 0.
    {329,-1,0,1,MoveOp::Speed,0.f},
    {329,-1,0,1,MoveOp::Vertical,0.f},
    {329,-1,0,1,MoveOp::Gravity,0.f},
    {329,-1,0,9999,MoveOp::Gauge,40.f},
    {333,-1,0,1,MoveOp::Speed,0.f},
    {333,-1,0,1,MoveOp::Vertical,0.f},
    {333,-1,0,1,MoveOp::Gravity,0.f},
    {333,-1,0,9999,MoveOp::Gauge,40.f},
    // 331 side dash attack (weapon 0): entry speed 17.5 — 20 when the dash began
    // inside 810000 (the strength latch, held in the move counter), approach 20
    // while latched through phase 1 and 10 through phase 2's first ten ticks.
    // Phase 1 hands to phase 2 past frame 2 either inside 90000 or unlatched,
    // then the approach bleeds .5 a tick.
    {331,0,0,0,MoveOp::Speed,17.5f,20.f,810000.f},
    {331,0,0,0,MoveOp::CounterSet,1.f,0.f,0.f,kGateNear,810000},
    {331,0,0,0,MoveOp::CounterSet,0.f,0.f,0.f,kGateFar,810000},
    {331,0,0,9999,MoveOp::Turn,20.f,kGateCounterEquals,1},
    {331,2,0,9,MoveOp::Turn,10.f,kGateCounterEquals,1},
    {331,1,3,9999,MoveOp::Approach,90000.f,2.f,2.f},
    {331,1,3,9999,MoveOp::Approach,0.f,2.f,2.f,kGateCounterEquals,0},
    {331,2,0,9999,MoveOp::Decelerate,.5f},
    // 334 dash followup: the dive body in fighter.cpp owns the rebound; the
    // landing exits into the 333 recovery (clear_vertical, gravity carried).
    {334,0,0,9999,MoveOp::LandExit,333.f},
    {334,1,0,9999,MoveOp::LandExit,333.f},
    // 341 landing followup (weapon 0): approach 20 on contact through frame 5,
    // the leap at phase 1's first tick (speed 10, vertical 18, gravity .75), and
    // the landing ends in phase 3 with speed and vertical zeroed.
    {341,0,0,4,MoveOp::Speed,15.f},
    {341,0,0,4,MoveOp::Turn,20.f,kGateContact},
    {341,1,0,0,MoveOp::Speed,10.f},
    {341,1,0,0,MoveOp::Vertical,18.f},
    {341,1,0,0,MoveOp::Gravity,.75f},
    {341,1,0,19,MoveOp::Active,0.f},
    {341,1,0,19,MoveOp::Active,1.f},
    {341,1,0,9999,MoveOp::LandPhase,3.f},
    {341,2,0,9999,MoveOp::LandPhase,3.f},
    // 400 ground tap: hide from tick 12 (0x444850 JLE on tick<=11), turn 20 deg
    // through tick 11 (FUN_0042db10), launch item row 0 at tick 12 (0x4448d6) normally
    // and row 6 powered (FUN_00434fd0 branch on byte 0x845/word 0x848). Slot-0
    // attachment in both halves; the pitch scratch (±30) is read back same-tick.
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,0,0,11,MoveOp::Turn,20.f},
    {400,-1,12,9999,MoveOp::Hide,0.f},
    {400,-1,12,9999,MoveOp::Hide,1.f},
    voice_rule(400,0,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {400,0,12,12,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,0,12,12,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {400,0,12,12,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_stored_pitch()},
    // Melee voices and effects (FUN_0043ffc0's tick-guarded call sites, read
    // directly): the ordinary voice ids ride the melee latch; the close-target
    // cascade (voices 0/15/5 at priority 12, FUN_0043ffc0:601-627) reads the
    // pairing-tracker flags FUN_0042e110 arms, which the port does not model —
    // documented at the op site, not guessed here. Effect ids are FUN_0042c880's.
    sound_effect_rule(300,2,0,0,60),
    melee_voice_rule(300,2,0,0,1),
    sound_effect_rule(301,0,3,3,61),
    melee_voice_rule(301,0,3,3,2),
    sound_effect_rule(302,0,10,10,62),
    melee_voice_rule(302,0,10,10,3),
    sound_effect_rule(310,2,4,4,62),
    melee_voice_rule(310,2,4,4,2),
    sound_effect_rule(311,0,12,12,62),
    melee_voice_rule(311,0,12,12,3),
    sound_effect_rule(320,2,0,0,62),
    melee_voice_rule(320,2,0,0,1),
    sound_effect_rule(330,2,6,6,62),
    melee_voice_rule(330,2,6,6,2),
    melee_voice_rule(331,2,10,10,2),
    // 332's entry voice (FUN_0043ffc0 case 0x14c, phase 1 tick 0): event 3 with
    // the FIXED choice 0 through FUN_00422490(3,0,10,0).
    melee_voice_rule(332,1,0,0,3,0),
    sound_effect_rule(340,0,15,15,61),
    melee_voice_rule(340,0,15,15,2),
    melee_voice_rule(341,1,0,0,3),
    // 402 air tap: hide from tick 13 (tick>12), launch item row 1 at tick 13
    // (0x444c7a CMP [this+0xae04],0xd) normally and row 7 powered (case 0x192).
    {402,-1,13,9999,MoveOp::Hide,0.f},
    {402,-1,13,9999,MoveOp::Hide,1.f},
    voice_rule(402,0,13,13,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {402,0,13,13,MoveOp::Launch,1.f,0.f,30.f,kGateNormal},
    {402,0,13,13,MoveOp::Launch,7.f,0.f,30.f,kGatePowered},
    // 402's motion and landing (FUN_0043ffc0 case 0x192, read directly): turn 20
    // toward the target through tick 12 (FUN_0042dc20 — the heading turns while
    // the world motion is preserved; the port's Turn follows the facing, a
    // labeled single-basis approximation), gravity 0.5 armed at entry (the body
    // applies it only when unset) integrating the vertical itself, and the
    // landing past tick 0 hands to the 403 recovery (the tick-0 guard is the
    // rule window's `first`).
    {402,0,0,12,MoveOp::Turn,20.f},
    {402,0,0,0,MoveOp::Gravity,.5f},
    {402,-1,1,9999,MoveOp::LandExit,403.f},
    // 403/409/469 recovery bodies (FUN_0043ffc0 cases 0x193/0x199/0x1d5): speed,
    // vertical, gravity and movement offset zeroed EVERY tick (the cases carry no
    // tick guard), the shot gauge (+0x834) refilling 40 thousandths a tick (5 with a
    // status timer — the status producer is unmodeled, so the fast rate is the only
    // reachable branch), capped at 1000. Completion returns to idle through the
    // period path.
    {403,-1,0,9999,MoveOp::Speed,0.f},
    {403,-1,0,9999,MoveOp::Vertical,0.f},
    {403,-1,0,9999,MoveOp::Gravity,0.f},
    {403,-1,0,9999,MoveOp::Recharge,40.f},
    {409,-1,0,9999,MoveOp::Speed,0.f},
    {409,-1,0,9999,MoveOp::Vertical,0.f},
    {409,-1,0,9999,MoveOp::Gravity,0.f},
    {409,-1,0,9999,MoveOp::Recharge,40.f},
    {469,-1,0,9999,MoveOp::Speed,0.f},
    {469,-1,0,9999,MoveOp::Vertical,0.f},
    {469,-1,0,9999,MoveOp::Gravity,0.f},
    {469,-1,0,9999,MoveOp::Recharge,40.f},
    // 401/405/406 — the walking shot and the lateral dash shots (weapon 0,
    // FUN_00445ee0's slot-7 routing through the mobile reference): the bodies fire
    // the same row-0/6 pair at tick 12 with the ±30 clamp as the ordinary 400,
    // with the mobile hide-after-13 and decelerate shapes; the movement angle
    // (-90/+90) rides the dash direction the port already committed.
    {401,0,0,9999,MoveOp::Decelerate,.25f},
    {401,0,0,11,MoveOp::Turn,20.f},
    {401,-1,14,9999,MoveOp::Hide,0.f},
    {401,-1,14,9999,MoveOp::Hide,1.f},
    voice_rule(401,0,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {401,0,12,12,MoveOp::CapturePitch,0.f,30.f,30.f},
    {401,0,12,12,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {401,0,12,12,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {405,0,0,0,MoveOp::Speed,10.f},
    {405,0,11,9999,MoveOp::Decelerate,.5f},
    {405,0,0,9,MoveOp::Turn,15.f},
    {405,-1,14,9999,MoveOp::Hide,0.f},
    {405,-1,14,9999,MoveOp::Hide,1.f},
    voice_rule(405,0,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {405,0,12,12,MoveOp::CapturePitch,0.f,30.f,30.f},
    {405,0,12,12,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {405,0,12,12,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {406,0,0,0,MoveOp::Speed,10.f},
    {406,0,11,9999,MoveOp::Decelerate,.5f},
    {406,0,0,9,MoveOp::Turn,15.f},
    {406,-1,14,9999,MoveOp::Hide,0.f},
    {406,-1,14,9999,MoveOp::Hide,1.f},
    voice_rule(406,0,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {406,0,12,12,MoveOp::CapturePitch,0.f,30.f,30.f},
    {406,0,12,12,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {406,0,12,12,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_stored_pitch()},
    // 407 back dash shot (weapon 0): tick 13 fires the row-4/row-9 pair at FIXED
    // angles — yaw +75/-75 with pitch 30 — and the powered branch widens to
    // rows 13/14 at yaw ±85 with pitch 20 (the mobile state407 body). The body
    // sets its own speed 10 at tick 0 (0x41200000, cases 0x195/0x196/0x197 — the
    // 405/406 entries above carry the same note) and bleeds 1 a tick past 30
    // (0x1e) on top of the phase-0 0.25 bleed. The VOICE is `+0x1b7 < 3` →
    // ShotFinal (30) else ShotB (28) — FUN_0043ffc0:2246-2251 — not the
    // ordinary 27/Equal-1 pair the first binding carried.
    {407,0,0,0,MoveOp::Speed,10.f},
    {407,0,0,9,MoveOp::Turn,9.f},
    {407,0,0,9999,MoveOp::Turn,15.f},
    {407,0,0,9999,MoveOp::Decelerate,.25f},
    {407,-1,31,9999,MoveOp::Decelerate,1.f},
    {407,-1,14,9999,MoveOp::Hide,0.f},
    {407,-1,14,9999,MoveOp::Hide,1.f},
    voice_rule(407,0,13,13,shot_voice(28,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Less,3)),
    {407,0,13,13,MoveOp::Launch,4.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_fixed_angles(75.f,30.f)},
    {407,0,13,13,MoveOp::Launch,9.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_fixed_angles(-75.f,30.f)},
    {407,0,13,13,MoveOp::Launch,13.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_fixed_angles(85.f,20.f)},
    {407,0,13,13,MoveOp::Launch,14.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_fixed_angles(-85.f,20.f)},
    // 408 air-dash fast shot (weapon 0, the 408.a branch): fires the GROUND
    // rows 0/6 but at tick 12 — one tick before the ordinary 402's rows 1/7 —
    // on the way down from the dash.
    {408,-1,14,9999,MoveOp::Hide,0.f},
    {408,-1,14,9999,MoveOp::Hide,1.f},
    voice_rule(408,0,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {408,0,12,12,MoveOp::CapturePitch,0.f,30.f,30.f},
    {408,0,12,12,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {408,0,12,12,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_stored_pitch()},
    // 450 first charge: turn 18 deg through tick 9, launch row 2 at tick 13 (case
    // 0x1c2) normally and row 8 powered, both at FIXED pitch 45 (0x42340000 constant,
    // not the scratch). Typed aim carries the constant; the origin stays slot-0.
    {450,0,0,9999,MoveOp::Decelerate,.5f},
    {450,0,0,9,MoveOp::Turn,18.f},
    voice_rule(450,0,13,13,shot_voice(28,30,ShotVoiceMagazine::Secondary,
                                     ShotVoiceCompare::Equal,1)),
    {450,0,13,13,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    {450,0,13,13,MoveOp::Launch,8.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    // 460 air charge: turn 18 deg through tick 9, launch row 2 at tick 12 (case 0x1cc)
    // normally and row 8 powered, same fixed 45 pitch.
    {460,0,0,9,MoveOp::Turn,18.f},
    voice_rule(460,0,12,12,shot_voice(28,30,ShotVoiceMagazine::Secondary,
                                     ShotVoiceCompare::Equal,1)),
    {460,0,12,12,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    {460,0,12,12,MoveOp::Launch,8.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    // 460's fall and landing (FUN_0043ffc0 case 0x1cc): the body applies gravity
    // 0.5 to the vertical itself every tick, and a grounded fighter still falling
    // hands to the 469 recovery.
    {460,0,0,0,MoveOp::Gravity,.5f},
    {460,-1,0,9999,MoveOp::LandExit,469.f},
    // 360/370 second charge: the ten-update freeze is PHASE 2 tick 13, inside the same
    // phase-2 branch as the tick-2 red launches (360: 0x443aef and 370: 0x443e8b both
    // sit after the 0xadf4==2 gate). Placing it in phase 0 froze the wrong phase. The
    // freeze is counter-gated (0x3e init at phase0/tick0, +1 per frozen update, return
    // while <10), not a plain hold — same model as Rika's, shorter interval.
    {360,-1,0,9999,MoveOp::Decelerate,.75f},
    {360,0,0,0,MoveOp::CounterSet,0.f},
    // FUN_0043ffc0:1493-1495 settles aim during the first two windup phases.
    {360,0,0,9999,MoveOp::Turn,15.f},
    {360,1,0,9999,MoveOp::Turn,15.f},
    voice_rule(360,2,2,2,shot_voice_pair(32,1,2,51)),
    {360,2,2,2,MoveOp::CapturePitch,0.f,40.f,40.f},
    {360,2,2,2,MoveOp::Launch,11.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-70.f,70.f,70.f),aim_stored_pitch(1.f)},
    {360,2,2,2,MoveOp::Launch,12.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(70.f,70.f,70.f),aim_stored_pitch(-1.f)},
    // The original tests counter<10 BEFORE incrementing and returning. The
    // post-increment Hold therefore accepts 1..10; the following visit resets it.
    {360,2,13,13,MoveOp::Counter,1.f},
    {360,2,13,13,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,11},
    {360,2,13,13,MoveOp::CounterSet,0.f,0.f,0.f,kGateCounterEquals,11},
    {370,-1,0,9999,MoveOp::Decelerate,.75f},
    {370,0,0,0,MoveOp::CounterSet,0.f},
    {370,0,0,9999,MoveOp::Turn,15.f},
    {370,1,0,9999,MoveOp::Turn,15.f},
    voice_rule(370,2,2,2,shot_voice_pair(32,1,2,51)),
    {370,2,2,2,MoveOp::CapturePitch,0.f,40.f,40.f},
    {370,2,2,2,MoveOp::Launch,11.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-70.f,70.f,70.f),aim_stored_pitch(1.f)},
    {370,2,2,2,MoveOp::Launch,12.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(70.f,70.f,70.f),aim_stored_pitch(-1.f)},
    {370,2,13,13,MoveOp::Counter,1.f},
    {370,2,13,13,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,11},
    {370,2,13,13,MoveOp::CounterSet,0.f,0.f,0.f,kGateCounterEquals,11},
    {370,-1,14,9999,MoveOp::Hide,0.f},
    {370,-1,14,9999,MoveOp::Hide,1.f},
    // 370's motion (FUN_0043ffc0 case 0x172, read directly): the entry hang —
    // speed, vertical and gravity all zeroed at phase-0 tick-0 — then the
    // phase-2 tick-2 backflip launch under the already-bound world pair: speed
    // -9.5 (0xc1180000), vertical 10 (0x41200000), gravity .5. The landing hands
    // to 469 like 460's.
    {370,0,0,0,MoveOp::Speed,0.f},
    {370,0,0,0,MoveOp::Vertical,0.f},
    {370,0,0,0,MoveOp::Gravity,0.f},
    {370,2,2,2,MoveOp::Speed,-9.5f},
    {370,2,2,2,MoveOp::Vertical,10.f},
    {370,2,2,2,MoveOp::Gravity,.5f},
    {370,-1,0,9999,MoveOp::LandExit,469.f},
    // 392 guard-knockback (FUN_0043ffc0 case 0x188): entered by the central
    // guard-exit check with speed -15 (0xc1700000) and the movement offset zeroed,
    // the voice 13 at entry (FUN_004223d0(0xd,10,0)), a scratch counter that walks
    // 0 -> 21 over phase 0 and hands to phase 1 the moment it passes 20, and the
    // speed recovering +1 a tick (the negative-aware Decelerate) while phases 0-1
    // run. The attacker's own 0x188 bodies confirm the shape.
    melee_voice_rule(392,0,0,0,13),
    {392,0,0,0,MoveOp::CounterSet,0.f},
    {392,0,0,9999,MoveOp::Counter,1.f},
    {392,0,0,9999,MoveOp::PhaseExit,1.f,0.f,0.f,kGateCounterAbove,0,
     ShotOriginSpec{},ShotAimSpec{},20},
    {392,-1,0,0,MoveOp::Speed,-15.f},
    {392,-1,0,9999,MoveOp::Decelerate,1.f},
    // 350 awakened melee, weapon 0 (FUN_0043ffc0 case 0x15e, read directly and
    // cross-checked with the donor's battle_rena_full_charge.hpp): both props
    // stay hidden for the whole move; voice 32 with the FIXED choice 0 at entry
    // (FUN_00422490(0x20,0,0x14,0)) and voice 33 at frame 56; effect 61 at
    // frames 11/15/19/23/27/31/35/56; the particle scatters at frames 7/15/23/31
    // (id 320) and 7/22/37 (id 350) — two rand%40-20 draws each, the yaw added to
    // the heading+offset, the pitch absolute — plus particle 340 at frame 56;
    // speed 10 at frame 1 and 0 at frame 10; frames 2..9 play twice (the rewind
    // scratch alternates a -1 clock skip, so the parity-gated ClockSkip halves
    // the clock's advance through elapsed 17); frame 70 rewinds to 66 eight
    // times before the move runs out. The contact latch at frame 50 only feeds
    // the +0x684 presentation flag the port does not model.
    {350,-1,0,9999,MoveOp::Hide,0.f},
    {350,-1,0,9999,MoveOp::Hide,1.f},
    // The body cuts the melee contact volume at tick 0 and never re-arms it
    // (FUN_0043ffc0:1392 calls FUN_00434bd0 inside the tick==0 block; there is no
    // FUN_00434b30 in this case): 350's damage is the particle/effect scatter, not a
    // swing. Weapon 1's 350 does keep a window (ticks 21..64, FUN_00448220:1306-1311).
    {350,-1,0,9999,MoveOp::ContactOff},
    melee_voice_rule(350,0,0,0,32,0),
    melee_voice_rule(350,0,56,56,33),
    sound_effect_rule(350,0,11,11,61),
    sound_effect_rule(350,0,15,15,61),
    sound_effect_rule(350,0,19,19,61),
    sound_effect_rule(350,0,23,23,61),
    sound_effect_rule(350,0,27,27,61),
    sound_effect_rule(350,0,31,31,61),
    sound_effect_rule(350,0,35,35,61),
    sound_effect_rule(350,0,56,56,61),
    effect_rule(350,0,7,7,320),
    effect_rule(350,0,15,15,320),
    effect_rule(350,0,23,23,320),
    effect_rule(350,0,31,31,320),
    effect_rule(350,0,7,7,350),
    effect_rule(350,0,22,22,350),
    effect_rule(350,0,37,37,350),
    effect_rule(350,0,56,56,340,false),
    {350,0,1,1,MoveOp::Speed,10.f},
    {350,0,10,10,MoveOp::Speed,0.f},
    // The original's stall (FUN_0043ffc0:1455-1464): while 0 < tick < 10 the +0x3d
    // alternator rewinds BOTH clocks one tick every other update, so body ticks 1..9
    // each run twice. The alternator is the UPDATE count (it keeps toggling through a
    // stall), so it starts at 1 and the first visit of tick 1 is the one that holds;
    // starting at 0 held tick 2 instead and skipped frame 1's replay. It must read 0
    // by tick 70, the state the rewind's `0x3d < 8` gate expects (`CounterSet 0` at
    // tick 10, the first tick past the stall loop).
    {350,0,0,0,MoveOp::CounterSet,1.f},
    {350,0,1,9,MoveOp::Counter,1.f},
    {350,0,1,9,MoveOp::ClockSkip,-1.f,0.f,0.f,kGateCounterMod,2},
    {350,0,10,10,MoveOp::CounterSet,0.f},
    {350,0,70,70,MoveOp::Counter,1.f},
    {350,0,70,70,MoveOp::ClockSeek,66.f,0.f,0.f,kGateCounterBelow,9},
};

// FUN_00448220.c:1666-1721 is the ground TAP: row 6 normally, rows 0 then 9
// powered at tick18. The runtime bridge incorrectly placed the charge fan here.
// The first charge (2148-2185) advances its scratch by four BEFORE each request,
// then adds rand%10-35 to it as a legacy yaw offset; pitch is literal zero.
inline constexpr MoveRule kRena1Rules[] = {
    // ---- melee execution (FUN_00448220, weapon 1) ----
    // 300 ordinary: the weapon-1 body — speed 15/25 switches at 810000 (not the
    // cleaver's 640000), approach 180 at entry then 20 a tick through phase 1,
    // the phase-1 exit, and the phase-2 approach 5 while frame < 4 (the +f0
    // ground-entry latch reads 1 for a grounded entry, development_animated_
    // combat.hpp:917) with the 1.5 bleed.
    {300,0,0,0,MoveOp::Speed,15.f,25.f,810000.f},
    {300,0,0,0,MoveOp::Turn,180.f},
    {300,0,1,9999,MoveOp::Turn,20.f},
    {300,1,0,9999,MoveOp::Turn,20.f},
    {300,1,0,9999,MoveOp::Approach,90000.f,10.f,2.f},
    {300,2,0,3,MoveOp::Turn,5.f},
    {300,2,0,9999,MoveOp::Decelerate,1.5f},
    // 301 followup (weapon 1): speed 10 at entry, full stop and turn released at
    // frame 8; approach 20 on contact through frame 8.
    {301,0,0,0,MoveOp::Speed,10.f},
    {301,-1,8,8,MoveOp::Speed,0.f},
    {301,-1,0,7,MoveOp::Turn,20.f,kGateContact},
    {301,-1,10,16,MoveOp::Active,0.f},
    {301,-1,10,16,MoveOp::Active,1.f},
    // Melee voices and effects (FUN_00448220's tick-guarded call sites, read
    // directly — the same latch/cascade caveats as weapon 0's block).
    sound_effect_rule(300,2,0,0,64),
    melee_voice_rule(300,2,0,0,1),
    sound_effect_rule(301,0,3,3,67),
    melee_voice_rule(301,0,3,3,3),
    sound_effect_rule(310,2,4,4,62),
    melee_voice_rule(310,2,4,4,2),
    sound_effect_rule(311,0,12,12,67),
    melee_voice_rule(311,0,12,12,3),
    sound_effect_rule(320,2,0,0,63),
    melee_voice_rule(320,2,0,0,1),
    melee_voice_rule(330,1,0,0,3),
    melee_voice_rule(331,2,10,10,2),
    melee_voice_rule(332,1,0,0,3,0),
    sound_effect_rule(340,0,12,12,67),
    melee_voice_rule(340,0,12,12,3),
    // 310 back kick: the weapon-0/1 body is shared (see kRenaRules 310).
    {310,0,0,0,MoveOp::Speed,30.f},
    {310,0,0,0,MoveOp::Turn,180.f},
    {310,0,0,9999,MoveOp::Turn,20.f},
    {310,1,0,0,MoveOp::Turn,15.f},
    {310,1,0,0,MoveOp::PhaseExit,2.f},
    {310,2,0,9999,MoveOp::Decelerate,1.f},
    {310,2,0,4,MoveOp::Turn,5.f},
    {310,2,13,9999,MoveOp::JumpCancel,0.f,kGateContact},
    {310,-1,5,7,MoveOp::Active,0.f},
    {310,-1,5,7,MoveOp::Active,1.f},
    // 311 side kick (weapon 1): entry speed 20, approach 9 through frame 10,
    // the 2-a-tick bleed after frame 17.
    {311,-1,18,9999,MoveOp::Decelerate,2.f},
    {311,0,0,0,MoveOp::Speed,20.f},
    {311,-1,0,0,MoveOp::Turn,180.f},
    {311,-1,0,9,MoveOp::Turn,9.f},
    {311,-1,12,18,MoveOp::Active,0.f},
    {311,-1,12,18,MoveOp::Active,1.f},
    // 320 chase: the fighter.cpp body with the weapon-0/1 policy; gravity past
    // tick 5 of phase 2, landing into 329 past tick 10.
    {320,0,0,0,MoveOp::Gravity,0.f},
    {320,2,6,9999,MoveOp::Gravity,.5f},
    {320,2,11,9999,MoveOp::LandExit,329.f},
    // The 320 body's contact gate (FUN_00448220; same phase-2 ticks 0..7 window as
    // the other two handlers).
    {320,0,0,9999,MoveOp::ContactOff},
    {320,1,0,9999,MoveOp::ContactOff},
    {320,2,8,9999,MoveOp::ContactOff},
    // 329/333 dash recovery: zeroed motion, gauge refill 40/1000 a tick.
    {329,-1,0,1,MoveOp::Speed,0.f},
    {329,-1,0,1,MoveOp::Vertical,0.f},
    {329,-1,0,1,MoveOp::Gravity,0.f},
    {329,-1,0,9999,MoveOp::Gauge,40.f},
    {333,-1,0,1,MoveOp::Speed,0.f},
    {333,-1,0,1,MoveOp::Vertical,0.f},
    {333,-1,0,1,MoveOp::Gravity,0.f},
    {333,-1,0,9999,MoveOp::Gauge,40.f},
    // 330 forward dash attack is the HOP (weapon 1): phase-0 bleed .5 with
    // approach 5, the hop at phase 1's first tick — speed 15, vertical 15,
    // gravity .75 — the phase-1 bleed, and the landing inside phases 1/2 ends
    // in phase 3 (FUN_00448220 case 0x14a's hop branch).
    {330,0,0,9999,MoveOp::Decelerate,.5f},
    {330,0,0,9999,MoveOp::Turn,5.f},
    {330,1,0,0,MoveOp::Speed,15.f},
    {330,1,0,0,MoveOp::Vertical,15.f},
    {330,1,0,0,MoveOp::Gravity,.75f},
    {330,1,0,9999,MoveOp::Decelerate,.5f},
    {330,1,0,9999,MoveOp::LandPhase,3.f},
    {330,2,0,9999,MoveOp::LandPhase,3.f},
    // 331 side dash attack (weapon 1): the strength latch reads 640000 (not the
    // weapon-0 810000); the rest of the body is shared.
    {331,0,0,0,MoveOp::Speed,17.5f,20.f,640000.f},
    {331,0,0,0,MoveOp::CounterSet,1.f,0.f,0.f,kGateNear,640000},
    {331,0,0,0,MoveOp::CounterSet,0.f,0.f,0.f,kGateFar,640000},
    {331,0,0,9999,MoveOp::Turn,20.f,kGateCounterEquals,1},
    {331,2,0,9,MoveOp::Turn,10.f,kGateCounterEquals,1},
    {331,1,3,9999,MoveOp::Approach,90000.f,2.f,2.f},
    {331,1,3,9999,MoveOp::Approach,0.f,2.f,2.f,kGateCounterEquals,0},
    {331,2,0,9999,MoveOp::Decelerate,.5f},
    // 334 dash followup: the dive body owns the rebound; landing exits to 333.
    {334,0,0,9999,MoveOp::LandExit,333.f},
    {334,1,0,9999,MoveOp::LandExit,333.f},
    // 340 landing melee (weapon 1): speed 10 at entry, approach 6 through
    // frame 8, stop at 15.
    {340,0,0,0,MoveOp::Speed,10.f},
    {340,0,0,7,MoveOp::Turn,6.f},
    {340,0,15,15,MoveOp::Speed,0.f},
    // ---- shooting (weapon 1) ----
    {400,-1,0,14,MoveOp::Turn,20.f},
    {400,-1,0,0,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,7,7,MoveOp::Speed,45.f},
    voice_rule(400,-1,15,15,shot_voice(29)),
    {400,-1,15,15,MoveOp::Speed,0.f},
    {400,-1,18,18,MoveOp::Launch,6.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,18,18,MoveOp::Launch,0.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,18,18,MoveOp::Launch,9.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    // 401 walking shot (weapon 1, the mobile state401 body): the same 18-tick
    // shape as the ordinary tap, but the powered branch requests ONE row-0
    // attachment (the ground 400 fires rows 0 then 9) and the rush is 30, not
    // the ground tap's 45. The tick-15 voice is the same fixed 29.
    {401,-1,0,14,MoveOp::Turn,20.f},
    {401,-1,0,0,MoveOp::Turn,5.f},
    {401,0,0,9999,MoveOp::Decelerate,.5f},
    {401,-1,7,7,MoveOp::Speed,30.f},
    voice_rule(401,-1,15,15,shot_voice(29)),
    {401,-1,15,15,MoveOp::Speed,0.f},
    {401,-1,18,18,MoveOp::Launch,6.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {401,-1,18,18,MoveOp::Launch,0.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    // FUN_00434a70(0,2)/(1,-1) at the case entry (FUN_00448220:2149-2150): slot 0
    // carries item MODEL 2 and slot 1 is cleared, every tick. The muzzle resolver
    // already used model 2; this is what makes the RENDERED weapon and the ribbon
    // anchors follow it (the model2/prop gap closed for 450 as well as 460).
    {450,-1,0,9999,MoveOp::PropModel,0.f,2.f},
    {450,-1,0,9999,MoveOp::Hide,1.f},
    {450,0,0,0,MoveOp::CounterSet,0.f},
    {450,-1,0,9,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    {450,-1,12,26,MoveOp::Counter,4.f},
    {450,-1,12,26,MoveOp::Launch,1.f,0.f,0.f,kGateNormal,0,
     origin_attachment_model(0,2),aim_stored_pitch(),{},kSpreadRena1Charge},
    {450,-1,12,26,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_model(0,2),aim_stored_pitch(),{},kSpreadRena1Charge},
    // 450's own tick-15 effect (FUN_00448220 case 0x1c2): FUN_0042c8b0(0x3f) at
    // tick 15 inside the 12..26 sweep window.
    sound_effect_rule(450,-1,15,15,63),
    // ---- 402 air tap: the three-phase dive (FUN_00448220 case 0x192, read
    // directly) ----
    // Phase 0 (12 ticks): tick 0 zeroes the speed, the vertical AND the movement
    // offset (+0x18, unmodeled). The vertical then stays 0 because the body never
    // integrates +0x16 in this row, which Gravity(0) states as "this row owns the
    // fall and its rate is zero" (leaving it unset would apply locomotion gravity).
    // Turn 20 toward the target through tick 9 (FUN_0042db10 nudges the battle
    // offset; the port's Turn is the labeled single-basis approximation). Phase 1
    // (1 tick): the dive launch — a body in fighter.cpp sets the vertical to the
    // fixed -40 u/tick and the horizontal closing speed from the target's geometry,
    // clamped [0,10]; no gravity is applied afterwards, so the dive is a
    // constant-velocity drop. Landing during phases 0/1 enters phase 2 with speed
    // and vertical cleared (the body's grounded branch). Phase 2 (35 ticks): effect
    // 67 and voice 29 at tick 0, the row 6 (normal) / rows 0+9 (powered) attachment
    // requests at tick 5 with effect 77. The cleaver keeps a melee contact window
    // (phase 2, ticks 0..5, FUN_00434b30) and the posed-record swing integration for
    // shot states is the recorded gap, as it already was for 401.
    {402,0,0,0,MoveOp::Speed,0.f},
    {402,0,0,0,MoveOp::Vertical,0.f},
    {402,0,0,0,MoveOp::Gravity,0.f},
    {402,0,0,9,MoveOp::Turn,20.f},
    {402,0,0,9999,MoveOp::LandPhase,2.f},
    {402,1,0,9999,MoveOp::LandPhase,2.f},
    sound_effect_rule(402,2,0,0,67),
    voice_rule(402,2,0,0,shot_voice(29)),
    sound_effect_rule(402,2,5,5,77),
    {402,2,5,5,MoveOp::Launch,6.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,2,5,5,MoveOp::Launch,0.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,2,5,5,MoveOp::Launch,9.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    // 403/469 recovery bodies (FUN_00448220 cases 0x193/0x1d5): motion zeroed EVERY
    // tick (no tick guard in the cases), the shot-gauge refill (+40, 5 with a status —
    // unmodeled producer), cap 1000.
    {403,-1,0,9999,MoveOp::Speed,0.f},
    {403,-1,0,9999,MoveOp::Vertical,0.f},
    {403,-1,0,9999,MoveOp::Gravity,0.f},
    {403,-1,0,9999,MoveOp::Recharge,40.f},
    {469,-1,0,9999,MoveOp::Speed,0.f},
    {469,-1,0,9999,MoveOp::Vertical,0.f},
    {469,-1,0,9999,MoveOp::Gravity,0.f},
    {469,-1,0,9999,MoveOp::Recharge,40.f},
    // ---- 460 air charge (FUN_00448220 case 0x1cc, read directly) ----
    // Slot 0 carries item model 2 — FUN_00434a70(0,2) re-binds it EVERY tick, so
    // the visible weapon and the ribbon anchors follow the model-2 muzzle (the
    // rendered-model2 gap this closes). Turn 18 through tick 9; the entry speed
    // halves; the 15-shot sweep window runs ticks 15..29 (0xe < tick < 0x1e) with
    // the 450's counter/yaw shape and effect 63 at tick 15; gravity 0.5 applies
    // to the vertical every tick; the landing hands to 469; completion goes to
    // the air exit.
    {460,-1,0,9999,MoveOp::PropModel,0.f,2.f},
    {460,-1,0,9,MoveOp::Turn,18.f},
    {460,-1,0,0,MoveOp::ScaleMotion,.5f,1.f},
    {460,0,0,0,MoveOp::CounterSet,0.f},
    {460,-1,15,29,MoveOp::Counter,4.f},
    {460,-1,15,29,MoveOp::Launch,1.f,0.f,0.f,kGateNormal,0,
     origin_attachment_model(0,2),aim_stored_pitch(),{},kSpreadRena1Charge},
    {460,-1,15,29,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_model(0,2),aim_stored_pitch(),{},kSpreadRena1Charge},
    sound_effect_rule(460,-1,15,15,63),
    {460,0,0,0,MoveOp::Gravity,.5f},
    {460,-1,0,9999,MoveOp::LandExit,469.f},
    // ---- 360/370 second charge (FUN_00448220 cases 0x168/0x172, read
    // directly) ----
    // 360 (ground): the entry voice 32 with the rand%100 < 50 choice pair
    // (4/3 — FUN_00422490(0x20,4|3,0x14,0)), turn 18 through tick 9, the 1.5
    // bleed, and the tick-16 SINGLE row-8 attachment at fixed pitch 70
    // (0x428c0000) with effect 64 — no powered split. 370 (air): the same
    // voice pair at priority 15 (FUN_00422490's 0xf), the entry speed halved
    // with the vertical zeroed, gravity 0.5, the same tick-16 request, and the
    // landing to 469.
    melee_voice_rule(360,0,0,0,32,3,4,50),
    {360,0,0,9,MoveOp::Turn,18.f},
    {360,0,0,9999,MoveOp::Decelerate,1.5f},
    sound_effect_rule(360,0,16,16,64),
    {360,0,16,16,MoveOp::Launch,8.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,70.f)},
    melee_voice_rule(370,0,0,0,32,3,4,50),
    {370,0,0,9,MoveOp::Turn,18.f},
    {370,0,0,0,MoveOp::ScaleMotion,.5f,0.f},
    {370,0,0,0,MoveOp::Gravity,.5f},
    sound_effect_rule(370,0,16,16,64),
    {370,0,16,16,MoveOp::Launch,8.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,70.f)},
    {370,-1,0,9999,MoveOp::LandExit,469.f},
    // ---- 350 awakened melee, weapon 1 (FUN_00448220 case 0x15e, read
    // directly) ----
    // Effect 68 at frames 25/45/65; approach 25 while frame < 8; speed 8.5 at
    // frame 20 (0x41080000) and 0 at 73; the contact window frames 21..64 (the
    // bodies' FUN_00434b30 span — ContactOff cuts outside it); motion zeroed at
    // entry. No entry voice for this weapon.
    sound_effect_rule(350,0,25,25,68),
    sound_effect_rule(350,0,45,45,68),
    sound_effect_rule(350,0,65,65,68),
    {350,0,0,0,MoveOp::Speed,0.f},
    {350,0,0,7,MoveOp::Turn,25.f},
    {350,0,20,20,MoveOp::Speed,8.5f},
    {350,0,73,73,MoveOp::Speed,0.f},
    {350,0,0,20,MoveOp::ContactOff},
    {350,0,65,9999,MoveOp::ContactOff},
    // 392 guard-knockback (FUN_00448220 case 0x188): the same shape as weapon
    // 0's — voice 13 at entry, speed -15 recovering +1 a tick.
    melee_voice_rule(392,0,0,0,13),
    {392,0,0,0,MoveOp::CounterSet,0.f},
    {392,0,0,9999,MoveOp::Counter,1.f},
    {392,0,0,9999,MoveOp::PhaseExit,1.f,0.f,0.f,kGateCounterAbove,0,
     ShotOriginSpec{},ShotAimSpec{},20},
    {392,-1,0,0,MoveOp::Speed,-15.f},
    {392,-1,0,9999,MoveOp::Decelerate,1.f},
};

// Rena weapon 2 (handler 0x438310) — no shoot_body_0_2_* exists in either body header,
// so the handler is the only source (FUN_00438310.c:1729-1800). State 400's phase 1
// fires at tick 35 (0x23) as ONE slot-0 attachment request at fixed angles (rows 0/2)
// followed by a TEN-iteration world ring: rows 1/3, 200 forward and +30 high, each
// iteration drawing its own pitch (`rand%30 + 20`) and yaw (`heading + offset + 90 -
// rand%180`). The ring's pitch is absolute and its yaw is the helper's legacy basis, so
// the rules latch a ZERO pitch base and let the spread supply the whole pitch.
inline constexpr MoveRule kRena2Rules[] = {
    // ---- melee execution (FUN_00438310, weapon 2) ----
    // Melee voices and effects (FUN_00438310's tick-guarded call sites, read
    // directly — the same latch/cascade caveats as weapon 0's block).
    sound_effect_rule(300,1,18,18,67),
    melee_voice_rule(300,1,18,18,3),
    sound_effect_rule(301,0,3,3,61),
    melee_voice_rule(301,0,3,3,2),
    sound_effect_rule(302,0,10,10,67),
    melee_voice_rule(302,0,10,10,3),
    sound_effect_rule(310,0,25,25,68),
    melee_voice_rule(310,0,25,25,3),
    sound_effect_rule(311,0,35,35,68),
    melee_voice_rule(311,0,35,35,3),
    sound_effect_rule(320,2,32,32,62),
    melee_voice_rule(320,2,32,32,1),
    sound_effect_rule(330,0,28,28,62),
    melee_voice_rule(330,0,28,28,3),
    melee_voice_rule(331,0,35,35,3),
    sound_effect_rule(340,0,15,15,61),
    melee_voice_rule(340,0,15,15,2),
    melee_voice_rule(341,1,0,0,3),
    // 300 ordinary is the standing spin: no approach at speed — offset approach 3
    // a tick through phase 0 (with the 180 snap at entry) — and the weapon-2
    // motion body in phase 1: rush 45 at frame 0 bleeding 2 a tick, the clock
    // running DOUBLE through frames 16..28 (advance_battle_attack300's extra
    // ++frame, mapped to ClockSkip), approach 3 while frame < 19, stop at 35.
    {300,0,0,0,MoveOp::Speed,0.f},
    {300,0,0,0,MoveOp::Turn,180.f},
    {300,0,0,9999,MoveOp::Turn,3.f},
    {300,1,0,0,MoveOp::Speed,45.f},
    {300,1,0,18,MoveOp::Turn,3.f},
    {300,1,0,9999,MoveOp::Decelerate,2.f},
    {300,1,16,28,MoveOp::ClockSkip,1.f},
    {300,1,35,35,MoveOp::Speed,0.f},
    // 310 back kick (weapon 2): the frame-driven body — speed 30 at entry
    // bleeding 2 through frames 6..24, the −5 backward slide at frame 25, full
    // stop at 47, approach 10 through frame 30.
    {310,-1,0,0,MoveOp::Speed,30.f},
    {310,-1,0,0,MoveOp::Turn,180.f},
    {310,-1,6,24,MoveOp::Decelerate,2.f},
    {310,-1,25,25,MoveOp::Speed,-5.f},
    {310,-1,24,45,MoveOp::Active,0.f},
    {310,-1,24,45,MoveOp::Active,1.f},
    {310,-1,47,47,MoveOp::Speed,0.f},
    {310,-1,0,29,MoveOp::Turn,10.f},
    // 311 side kick (weapon 2): the guard test runs before the frame-0 clear in
    // the original; the motion is speed 0 at entry, 20 at frame 27, 0 at 47.
    {311,-1,0,0,MoveOp::Speed,0.f},
    {311,-1,0,0,MoveOp::Turn,180.f},
    {311,-1,27,27,MoveOp::Speed,20.f},
    {311,-1,47,47,MoveOp::Speed,0.f},
    {311,-1,32,49,MoveOp::Active,0.f},
    {311,-1,32,49,MoveOp::Active,1.f},
    // 320 chase (weapon 2): the fighter.cpp body with the fixed-strength policy
    // (140, attack window 490000); gravity only past tick 50 of phase 2, the
    // landing into 329 past tick 55.
    {320,0,0,0,MoveOp::Gravity,0.f},
    {320,2,51,9999,MoveOp::Gravity,.5f},
    {320,2,56,9999,MoveOp::LandExit,329.f},
    // The 320 body's contact gate (FUN_00438310; same phase-2 ticks 0..7 window).
    {320,0,0,9999,MoveOp::ContactOff},
    {320,1,0,9999,MoveOp::ContactOff},
    {320,2,8,9999,MoveOp::ContactOff},
    // 329/333 dash recovery: zeroed motion, gauge refill 40/1000 a tick.
    {329,-1,0,1,MoveOp::Speed,0.f},
    {329,-1,0,1,MoveOp::Vertical,0.f},
    {329,-1,0,1,MoveOp::Gravity,0.f},
    {329,-1,0,9999,MoveOp::Gauge,40.f},
    {333,-1,0,1,MoveOp::Speed,0.f},
    {333,-1,0,1,MoveOp::Vertical,0.f},
    {333,-1,0,1,MoveOp::Gravity,0.f},
    {333,-1,0,9999,MoveOp::Gauge,40.f},
    // 330 forward dash attack (weapon 2): approach 3 through frame 28 with the
    // 1.5 bleed, then the 40 rush at frame 28 bleeding 2.
    {330,-1,0,27,MoveOp::Turn,3.f},
    {330,-1,0,27,MoveOp::Decelerate,1.5f},
    {330,-1,28,9999,MoveOp::Decelerate,2.f},
    {330,-1,28,28,MoveOp::Speed,40.f},
    {330,-1,28,34,MoveOp::Active,0.f},
    {330,-1,28,34,MoveOp::Active,1.f},
    // 331 side dash attack (weapon 2): no speed of its own (the dash's motion
    // carries), the strength latch reads 810000, approach-preserving 10 through
    // frame 20 while latched, the .75 bleeds outside frames 36..103, speed 10 at
    // frame 35, approach 2 through the 26..109 strike window.
    {331,0,0,0,MoveOp::CounterSet,1.f,0.f,0.f,kGateNear,810000},
    {331,0,0,0,MoveOp::CounterSet,0.f,0.f,0.f,kGateFar,810000},
    {331,-1,0,20,MoveOp::Turn,10.f,kGateCounterEquals,1},
    {331,-1,0,35,MoveOp::Decelerate,.75f},
    {331,-1,104,9999,MoveOp::Decelerate,.75f},
    {331,-1,35,35,MoveOp::Speed,10.f},
    {331,-1,26,109,MoveOp::Active,0.f},
    {331,-1,26,109,MoveOp::Active,1.f},
    {331,-1,26,109,MoveOp::Turn,2.f},
    // 340 landing melee (weapon 2): the weapon-0 shape — speed 15, approach 18
    // through frame 10, stop at 15.
    {340,0,0,0,MoveOp::Speed,15.f},
    {340,0,0,9,MoveOp::Turn,18.f},
    {340,0,15,15,MoveOp::Speed,0.f},
    {340,-1,16,24,MoveOp::Active,0.f},
    {340,-1,16,24,MoveOp::Active,1.f},
    // 341 landing followup (weapon 2): speed 10 through frame 5 (approach 20 on
    // contact), the leap (10 up, gravity .75) at phase 1, landing ends phase 3
    // and clears the gravity.
    {341,0,0,4,MoveOp::Speed,10.f},
    {341,0,0,4,MoveOp::Turn,20.f,kGateContact},
    {341,1,0,0,MoveOp::Speed,10.f},
    {341,1,0,0,MoveOp::Vertical,18.f},
    {341,1,0,0,MoveOp::Gravity,.75f},
    {341,1,0,9999,MoveOp::LandPhase,3.f},
    {341,2,0,9999,MoveOp::LandPhase,3.f},
    // ---- shooting (FUN_00438310, weapon 2) ----
    // FUN_00438310:1740-1760: horizontal bleed, then a phase-1 rush at tick25.
    {400,-1,0,19,MoveOp::Turn,10.f},
    {400,0,0,9999,MoveOp::Decelerate,2.5f},
    {400,1,0,0,MoveOp::Speed,0.f},
    {400,1,25,25,MoveOp::Speed,30.f},
    {400,1,35,35,MoveOp::Speed,0.f},
    // FUN_00438310.c:1763-1768: ShotFinal on primary remaining==1, else ShotC.
    voice_rule(400,1,35,35,shot_voice(29,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    // The attachment request carries no pitch and no yaw offset at all.
    {400,1,35,35,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,1,35,35,MoveOp::Launch,2.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,1,35,35,MoveOp::CapturePitch,0.f,0.f,0.f},
    {400,1,35,35,MoveOp::Launch,1.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(0.f,200.f,30.f),aim_stored_pitch(),{},kSpreadRing,10},
    {400,1,35,35,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(0.f,200.f,30.f),aim_stored_pitch(),{},kSpreadRing,10},
    // FUN_00438310.c:2254-2307: ground charge at tick40, hand R, pitch +/-40.
    {450,-1,0,24,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,1.5f},
    // FUN_00438310.c:2272-2281: ShotFinal on secondary remaining==1, else ShotB.
    voice_rule(450,-1,40,40,shot_voice(28,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {450,-1,40,40,MoveOp::CapturePitch,0.f,40.f,40.f},
    {450,-1,40,40,MoveOp::Launch,4.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {450,-1,40,40,MoveOp::Launch,5.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // ---- 402 air tap (FUN_00438310 case 0x192, read directly) ----
    // Phase 0: the entry 180 offset snap, then turn 10 through tick 9; the speed is
    // RE-ASSERTED at 20 every phase-0 frame (the body's write is not tick-gated) and
    // the vertical bleeds 0.5 a tick (the body applies it directly, so Gravity 0.5
    // carries it); the phase clock CLAMPS at 17 — the row waits for its landing
    // branch, not its 76-tick duration. Landing before tick 15 hands to the 403
    // recovery; at 15..17 it enters phase 1 with the clock SEEKING 25 (both clocks in
    // the original — a recorded single-clock approximation) and the vertical cleared.
    // Phase 1: the speed bleeds 1 a tick, and tick 35 fires the attachment rows 0/2
    // plus the TEN-request ring on rows 1/3 — pitch rand%50+30 absolute, yaw
    // 90-rand%180 on the helper's legacy basis — with effect 170 and the final-round
    // voice pair. The 400's world-form ring draws the same yaw shape (kSpreadRing);
    // this one is attachment-based with a wider pitch and needs no CapturePitch (the
    // ring's pitch is the draw itself).
    {402,0,0,0,MoveOp::Turn,180.f},
    {402,0,0,9999,MoveOp::Speed,20.f},
    {402,0,0,9,MoveOp::Turn,10.f},
    {402,0,0,9999,MoveOp::Gravity,.5f},
    {402,0,0,9999,MoveOp::ClockClamp,17.f},
    {402,0,0,14,MoveOp::LandExit,403.f},
    {402,0,15,17,MoveOp::LandSeek,1.f,25.f},
    {402,1,0,9999,MoveOp::Decelerate,1.f},
    sound_effect_rule(402,1,35,35,170),
    voice_rule(402,1,35,35,shot_voice(29,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {402,1,35,35,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,1,35,35,MoveOp::Launch,2.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,1,35,35,MoveOp::Launch,1.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadRingAir,10},
    {402,1,35,35,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadRingAir,10},
    // 403/469 recovery bodies (FUN_00438310 cases 0x193/0x1d5): motion zeroed EVERY
    // tick (no tick guard in the cases), the shot-gauge refill (+40, 5 with a status —
    // unmodeled producer), cap 1000.
    {403,-1,0,9999,MoveOp::Speed,0.f},
    {403,-1,0,9999,MoveOp::Vertical,0.f},
    {403,-1,0,9999,MoveOp::Gravity,0.f},
    {403,-1,0,9999,MoveOp::Recharge,40.f},
    {469,-1,0,9999,MoveOp::Speed,0.f},
    {469,-1,0,9999,MoveOp::Vertical,0.f},
    {469,-1,0,9999,MoveOp::Gravity,0.f},
    {469,-1,0,9999,MoveOp::Recharge,40.f},
    // ---- 460 air charge (FUN_00438310 case 0x1cc, read directly) ----
    // Turn 18 through tick 9; the entry speed halves (the body also dips the
    // vertical 0.5 once at tick 0 — folded into the first fall ticks, a
    // labeled one-line approximation); gravity 0.1 (0x3dcccccd); the tick-36
    // right-hand request rows 4/5 at the ±40-clamped pitch with effect 171
    // (0xab) and the final-round voice pair; the landing hands to 469.
    {460,-1,0,9,MoveOp::Turn,18.f},
    {460,-1,0,0,MoveOp::ScaleMotion,.5f,1.f},
    {460,0,0,0,MoveOp::Gravity,.1f},
    sound_effect_rule(460,-1,36,36,171),
    voice_rule(460,-1,36,36,shot_voice(28,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {460,-1,36,36,MoveOp::CapturePitch,0.f,40.f,40.f},
    {460,-1,36,36,MoveOp::Launch,4.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {460,-1,36,36,MoveOp::Launch,5.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {460,-1,0,9999,MoveOp::LandExit,469.f},
    // ---- 350/360 full charge (FUN_00438310 cases 0x15e/0x168, read directly) ----
    // Ground 350: the entry voice 32 with the rand%100 < 51 pair (0/1 —
    // FUN_00422490(0x20,0|1,0x14,0)); turn 15 through tick 41 (0x2a); the 0.75
    // bleed; the clock JUMP 42->95 (both clocks — the single-clock
    // approximation above); props hidden past tick 116; and the tick-116 world
    // row 8: forward 150, height +70, yaw heading+offset+1, the ±40-clamped
    // pitch, effect 172 (0xac). Air 360: the same shape with the entry speed
    // AND vertical scaled to a tenth (0.1/0.1) and gravity 0.05 (0x3d4ccccd);
    // the landing hands to 469; completion goes to the air exit with gravity
    // 0.5.
    melee_voice_rule(350,0,0,0,32,1,0,51),
    {350,0,0,41,MoveOp::Turn,15.f},
    {350,0,0,9999,MoveOp::Decelerate,.75f},
    {350,0,42,42,MoveOp::ClockSeek,95.f},
    {350,-1,117,9999,MoveOp::Hide,0.f},
    {350,-1,117,9999,MoveOp::Hide,1.f},
    sound_effect_rule(350,0,116,116,172),
    {350,0,116,116,MoveOp::CapturePitch,0.f,40.f,40.f},
    {350,0,116,116,MoveOp::Launch,8.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(0.f,150.f,70.f),aim_stored_pitch(1.f)},
    melee_voice_rule(360,0,0,0,32,1,0,51),
    {360,0,0,0,MoveOp::ScaleMotion,.1f,.1f},
    {360,0,0,0,MoveOp::Gravity,.05f},
    {360,0,0,41,MoveOp::Turn,15.f},
    {360,0,42,42,MoveOp::ClockSeek,95.f},
    sound_effect_rule(360,0,116,116,172),
    {360,0,116,116,MoveOp::CapturePitch,0.f,40.f,40.f},
    {360,0,116,116,MoveOp::Launch,8.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(0.f,150.f,70.f),aim_stored_pitch(1.f)},
    {360,-1,0,9999,MoveOp::LandExit,469.f},
    // 392 guard-knockback (FUN_00438310 case 0x188): the shared shape.
    melee_voice_rule(392,0,0,0,13),
    {392,0,0,0,MoveOp::CounterSet,0.f},
    {392,0,0,9999,MoveOp::Counter,1.f},
    {392,0,0,9999,MoveOp::PhaseExit,1.f,0.f,0.f,kGateCounterAbove,0,
     ShotOriginSpec{},ShotAimSpec{},20},
    {392,-1,0,0,MoveOp::Speed,-15.f},
    {392,-1,0,9999,MoveOp::Decelerate,1.f},
};

// Natsumi weapon 0 (handler 0x5e2af0): the normal ground state400 probe is an
// attachment callback for row 0 at tick 14. Both props are cleared before that callback;
// reassert Hide at the firing tick to select the native bone-origin fallback. This pins only
// the request schedule, not the raw flag, admission/geometry or natural phase reachability.
// State 402 makes an analogous raw call but lacks a normalized callback trace, so stays
// unbound rather than promoting a body-pattern inference to a confirmed air row.
inline constexpr MoveRule kNatsumi0Rules[] = {
    voice_rule(400,-1,14,14,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Equal,1)),
    {400,-1,14,9999,MoveOp::Hide,0.f},
    {400,-1,14,9999,MoveOp::Hide,1.f},
    {400,-1,14,14,MoveOp::Launch,0.f,0.f,30.f},
};

struct MoveProgram {
    const MoveRule* rules = nullptr;
    size_t count = 0;
    int shot[3][2]{}; // tap/first/second charge; ground/air
    // The state-320 chase and state-332 dive bodies are feedback loops (velocity
    // re-derived from the live angle each tick), not static rules: the program
    // points at the recovered per-weapon policy the body runs with. Null = the
    // move has no recovered chase/dive for this combo.
    const struct ChasePolicy* chase = nullptr;
    const struct DivePolicy* dive = nullptr;
};

// State 320's recovered policy (chasing_air_melee for character 0). Speeds and
// strengths are the original's per-tick units; distances are squared like the
// bodies' compares. Sources: FUN_0043ffc0/448220/438310 case 0x140 read through
// the Ginkiha reference; the handlers stay authoritative.
struct ChasePolicy {
    float initialSpeed = 12.5f, minimumVertical = -3.f, maximumVertical = 3.f;
    float minimumAngle = -30.f, maximumAngle = 50.f, turnStep = 3.f, pitchBias = 20.f;
    int initialStrength = 230, minimumStrength = 125, strengthDecay = 4;
    double initialDistance2 = 1000000., attackDistance2 = 40000.;
    int approachAfter = 10, approachTimeout = 25;
    int gravityAfter = 5, landingAfter = 10;
    int voiceFrame = 0;
    bool skipAttackFrames = false;  // weapon 2 jumps frame 13 -> 22 in phase 2
};

constexpr ChasePolicy kRenaChaseW0W1{};
constexpr ChasePolicy kRenaChaseW2{12.5f, -3.f, 3.f, -30.f, 50.f, 3.f, 20.f,
                                   140, 140, 4, 1000000., 490000., 10, 25,
                                   50, 55, 32, true};

constexpr const ChasePolicy* rena_chase_policy(int weaponSlot) {
    // chasing_air_melee_policy(0, weapon): only weapon 2 changes the profile
    // (fixed strength 140, late gravity/landing, the frame skip, effect 63 for w1).
    // Tables at namespace scope so the constexpr MoveProgram aggregates can hold
    // pointers to them.
    switch (weaponSlot) {
        case 0:
        case 1:  return &kRenaChaseW0W1;
        case 2:  return &kRenaChaseW2;
        default: return nullptr;
    }
}

// State 332/334's recovered policy (keiichi_dive + dash followup for character 0;
// the dive body is weapon-independent for this group). FUN_0043ffc0 case 0x14c and
// the 334 tail, read through the Ginkiha reference.
struct DivePolicy {
    float launchSpeed = 25.f;      // character 5 uses 32.5; Rena is 25
    float minimumAngle = -20.f, maximumAngle = -5.f;
    float contactVertical = 10.f, contactSpeed = -7.f, contactGravity = .35f;
    int contactExitState = 334;
    int disableContactAfter = 22;  // phase 1: the hit volume turns off
    int phaseExitFrame = 40;      // phase 1 -> 2 with speed 10
};

constexpr DivePolicy kRenaDive{};

constexpr const DivePolicy* rena_dive_policy(int weaponSlot) {
    return weaponSlot == 0 || weaponSlot == 1 ? &kRenaDive : nullptr;
}

// Ribbon binding/activation are prop-manager callbacks, not part of the
// shot/voice MoveProgram. Akane's handler (FUN_00595460) binds prop0 to item2
// for each supported melee move, while only some move phases/ticks activate
// its ribbon. Keeping these descriptors separate avoids implying that her
// shooting or voice paths are bound. The manager prop slot selects the
// hand/bone; the item model selects anchors and texture.
struct TrailWindow {
    unsigned handler;
    int character, weaponSlot;
    int move, phase, first, last;
    int propSlot;
};
struct TrailBinding {
    unsigned handler;
    int character, weaponSlot;
    int move, propSlot, itemModel;
};
inline constexpr TrailBinding kAkane0TrailBindings[] = {
    {0x595460,13,0,300,0,2}, {0x595460,13,0,301,0,2},
    {0x595460,13,0,302,0,2}, {0x595460,13,0,330,0,2},
    {0x595460,13,0,331,0,2}, {0x595460,13,0,340,0,2},
    {0x595460,13,0,341,0,2},
};
inline constexpr TrailWindow kAkane0TrailWindows[] = {
    // FUN_00595460:300, Prop0<-item2; phase2, ticks 3..10.
    {0x595460,13,0,300,2,3,10,0},
    // The source handles the follow-up rows, but current port input does not reach them.
    {0x595460,13,0,301,-1,10,16,0}, // case 0x12d, ticks 10..16
    {0x595460,13,0,302,-1,10,13,0}, // case 0x12e, ticks 10..13
    // Dash chain windows from cases 0x14a/0x14b.
    {0x595460,13,0,330,2,10,15,0},
    {0x595460,13,0,331,2,7,16,0},
    // Aerial windows from case 0x154 and the nearby 0x155 branch.
    {0x595460,13,0,340,-1,16,24,0},
    {0x595460,13,0,341,-1,17,19,0},
};

inline const TrailBinding* trail_binding(const CharacterMoves* moves, int move,
                                         int propSlot) {
    if (!moves) return nullptr;
    const auto* motion = locomotion(moves);
    const int character = moves->character_index();
    const int weaponSlot = weaponSlotForItem(character, moves->weapon_id());
    for (const auto& row : kAkane0TrailBindings)
        if (row.handler == (motion ? motion->handler : 0u) &&
            row.character == character && row.weaponSlot == weaponSlot &&
            row.move == move && row.propSlot == propSlot)
            return &row;
    return nullptr;
}

inline const TrailWindow* trail_window(const CharacterMoves* moves, int move, int phase,
                                       int tick, int propSlot) {
    if (!moves) return nullptr;
    const auto* motion = locomotion(moves);
    const int character = moves->character_index();
    const int weaponSlot = weaponSlotForItem(character, moves->weapon_id());
    if (!trail_binding(moves,move,propSlot)) return nullptr;
    for (const auto& row : kAkane0TrailWindows)
        if (row.handler == (motion ? motion->handler : 0u) &&
            row.character == character && row.weaponSlot == weaponSlot &&
            row.move == move && (row.phase < 0 || row.phase == phase) &&
            row.first <= tick && tick <= row.last && row.propSlot == propSlot)
            return &row;
    return nullptr;
}

// A mapped shot state has an audited voice policy in this file, including an explicit
// silent policy when its handler has no voice call. Unmapped states retain the generic
// audio fallback because their source voice path has not been bound.
inline bool shot_voice_policy_audited(const MoveProgram* program, int move) {
    if (!program || move < 0) return false;
    for (const auto& tier : program->shot)
        for (int shot : tier)
            if (shot == move) return true;
    return false;
}
// True when the current row carries at least one recovered melee voice cue. The audio
// layer suppresses its fallback swing voice for such rows so the source-timed cue is
// the only one heard (the same audited/fallback split the shot voice uses).
inline bool melee_voice_policy_audited(const MoveProgram* program, int move) {
    if (!program || move < 0) return false;
    for (size_t i = 0; i < program->count; ++i)
        if (program->rules[i].move == move &&
            program->rules[i].operation == MoveOp::MeleeVoice)
            return true;
    return false;
}
// Slot7 jump-cancel facts recovered per combo (bundle evidence TSVs, runtime ==
// expected): jump out of shot move 400 into state 40 admits at (phase 0, frame 20,
// flags 0x100) for Rena 0 and (phase 0, frame 25, flags 0x100) for Rika 1; frame 0 has
// no request anywhere sampled. Shot state 401 has no binding in this port yet (charge
// tiers map to 450/460/360/370), and 403/409→400 needs recovery states (plan Fase 3),
// so the table carries exactly the verified rows. Sampled frames are lower bounds, not
// proven windows — bundle RESPONSE §3: sampled contexts are not exhaustive tables.
struct ShotJumpCancel { unsigned handler; int move; int frame; };
inline constexpr ShotJumpCancel kShotJumpCancel[] = {
    {0x43ffc0, 400, 20},  // Rena 0
    {0x492f70, 400, 25},  // Rika 1
};
// Mion weapon 0 (handler 0x4582a0) — shot rules recovered from the reference bodies
// shoot_body_1_0_{400,402,450,460} (bundle reference/source). Phase/turn/hold values are
// measured in the bodies; each rule below cites its lines. Known gaps, not guesses:
// ph3/row-1 second shot has no variant model here (usage variants 1 AND 3 fire, but the
// port cannot select variants — row 0 is the bound primary); slot7 Hide values 2/3/-1
// and slot-1 halves have no MoveRule field (Hide carries slot 0's unbind window only);
// 450's pitch clamp is asymmetric [-40,+45] but the model clamps symmetric (45 kept);
// counter-to-tick in 402 assumes no reset mid-move; speeds live in item data, never here.
inline constexpr MoveRule kMionRules[] = {
    // Mion weapon 0 (handler 0x4582a0) — shoot_body_1_0_{400,402,450,460}. Every launch
    // is FUN_00435000, so slot and row are both explicit; the powered gate switches the
    // ROW only, never the slot.
    //
    // The bodies carry two different clocks and they must not be confused: the phase
    // tick (`w[0x2b81]`, zeroed by FUN_00421100 on every phase change) is what the
    // per-phase first/last windows below mean, while the scratch counters (`0x3a`,
    // `0x3b`, `0x3e`) are written by the bodies and survive a phase change. Rules whose
    // body reads a scratch counter therefore gate on MoveOp::Counter, not on elapsed.
    //
    // --- 400 ground tap: two firing phases (L3-143) ---
    // Scratch 0x3a ramps 0..9 and turns 18 deg while below 10 (L52-65).
    {400,0,0,0,MoveOp::CounterSet,0.f},
    {400,-1,0,9999,MoveOp::Turn,18.f,0.f,0.f,kGateCounterBelow,10},
    {400,-1,0,9999,MoveOp::Counter,1.f},
    // Phase 1: 10 deg turn (L66), and at per-phase tick 2 one slot-0 request, rows 0/4,
    // with the pitch scratch clamped +-30 (L69-98).
    {400,1,0,9999,MoveOp::Turn,10.f},
    voice_rule(400,1,2,2,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                    ShotVoiceCompare::Equal,1)),
    {400,1,2,2,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,1,2,2,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    {400,1,2,2,MoveOp::Launch,4.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    // Phase 3 is the follow-up on connect: phase 1 jumps straight to it while
    // `6 < tick && 0 < w[0xae] < 10 && fires < 6 && 0 < w[0x1b7]` (L100-104). The hit
    // counter w[0xae] has no port counterpart, so only the contact half is modelled; the
    // port reaches this phase through the DAT's phase advance rather than the jump, so
    // the follow-up lands on the phase boundary instead of the connecting frame.
    {400,3,0,9999,MoveOp::Turn,5.f},
    voice_rule(400,3,2,2,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                    ShotVoiceCompare::Equal,1)),
    {400,3,2,2,MoveOp::CapturePitch,0.f,40.f,40.f},
    {400,3,2,2,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateContact,0,
     origin_attachment_slot(1),aim_stored_pitch()},
    {400,3,2,2,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateContact,0,
     origin_attachment_slot(1),aim_stored_pitch()},
    //
    // --- 402 air tap: three counter-gated volleys (L298-397) ---
    // Scratch 0x3b is zeroed at phase0/tick0 and incremented every frame, so it counts
    // the whole state. Turns read the pre-increment value (20 deg below 25, plus 5 deg
    // inside 15..24, L340-347); the volleys read the post-increment value and fire at
    // 15, 20 and 25 — each on BOTH slots with the SAME row, which is two muzzles rather
    // than two rows, and +-40 pitch.
    {402,0,0,0,MoveOp::CounterSet,0.f},
    {402,-1,0,9999,MoveOp::Turn,20.f,0.f,0.f,kGateCounterBelow,25},
    {402,-1,0,9999,MoveOp::Turn,5.f,0.f,0.f,
     kGateCounterBelow | kGateCounterAbove,25, ShotOriginSpec{}, ShotAimSpec{}, 15},
    {402,-1,0,9999,MoveOp::Counter,1.f},
    voice_rule(402,-1,0,9999,
               shot_voice(28,30,ShotVoiceMagazine::Primary,ShotVoiceCompare::Less,7),
               kGateCounterEquals,15),
    {402,-1,0,9999,MoveOp::CapturePitch,0.f,40.f,40.f,kGateCounterEquals,15},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,15,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,15,
     origin_attachment_slot(1),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,15,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,15,
     origin_attachment_slot(1),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::CapturePitch,0.f,40.f,40.f,kGateCounterEquals,20},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,20,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,20,
     origin_attachment_slot(1),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,20,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,20,
     origin_attachment_slot(1),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::CapturePitch,0.f,40.f,40.f,kGateCounterEquals,25},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,25,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,25,
     origin_attachment_slot(1),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,25,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,25,
     origin_attachment_slot(1),aim_stored_pitch()},
    //
    // --- 450 ground charge: 25 deg turn to tick 16, fire at 17, 30-update freeze ---
    {450,-1,0,16,MoveOp::Turn,25.f},
    voice_rule(450,-1,17,17,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    // The two clamps differ: -40 low, +45 high (L1708-1715).
    {450,-1,17,17,MoveOp::CapturePitch,0.f,40.f,45.f},
    {450,-1,17,17,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    {450,-1,17,17,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    // Freeze at tick 23 while the 0x3e counter is under 30 (L1727-1731).
    {450,0,0,0,MoveOp::CounterSet,0.f},
    {450,0,23,23,MoveOp::Counter,1.f},
    {450,0,23,23,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,30},
    //
    // --- 460 air charge: 15 deg turn to tick 14, fire at 17, 20-update freeze ---
    {460,-1,0,14,MoveOp::Turn,15.f},
    voice_rule(460,-1,17,17,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {460,-1,17,17,MoveOp::CapturePitch,0.f,40.f,40.f},
    {460,-1,17,17,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    {460,-1,17,17,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    // Freeze at tick 23 while 0x3e is under 20 (L2340-2344).
    {460,0,0,0,MoveOp::CounterSet,0.f},
    {460,0,23,23,MoveOp::Counter,1.f},
    {460,0,23,23,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,20},
};
// Mion weapon 1 (handler 0x461810) — shoot_body_1_1_{400,402,450,460} (bundle L2421-2587,
// L2705-2814, L4014-4121, L4271-4376). The taps fire slot 0 then slot 1 (the second only
// on connect). The charges are the bodies' 15-iteration `for` loops at tick 17: every
// iteration fires one slot-0 request and draws its own spread, so the volley is a fan of
// 15 rather than one shot repeated.
inline constexpr MoveRule kMion1Rules[] = {
    // 400: scratch 0x3a ramps 0..9 turning 18 deg, then 5 deg while the phase is below 3.
    {400,0,0,0,MoveOp::CounterSet,0.f},
    {400,-1,0,9999,MoveOp::Turn,18.f,0.f,0.f,kGateCounterBelow,10},
    {400,-1,0,9999,MoveOp::Decelerate,.5f,0.f,0.f,kGateCounterBelow,10},
    {400,-1,0,9999,MoveOp::Counter,1.f},
    {400,0,0,9999,MoveOp::Turn,5.f},
    {400,1,0,9999,MoveOp::Turn,5.f},
    {400,2,0,9999,MoveOp::Turn,5.f},
    // Phase 1 tick 2 fires slot 0, rows 0/4, clamp +-40 (L2504-2520).
    voice_rule(400,1,2,2,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                    ShotVoiceCompare::Less,3)),
    {400,1,2,2,MoveOp::CapturePitch,0.f,40.f,40.f},
    {400,1,2,2,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    {400,1,2,2,MoveOp::Launch,4.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    // Phase 2 tick 1 fires slot 1, rows 0/4, clamp +-30 — but only on connect
    // (`(tick == 1) && (0 < w[0x1b7])`, L2531).
    {400,2,1,1,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,2,1,1,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateContact,0,
     origin_attachment_slot(1),aim_stored_pitch()},
    {400,2,1,1,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateContact,0,
     origin_attachment_slot(1),aim_stored_pitch()},
    // Phases 2 and 3 hold the clock one frame at a time past tick 7 while 0x3b is under 1
    // (L2556-2573) — the counter re-arms, so this is a repeated one-frame hold.
    {400,2,8,9999,MoveOp::Hold,1.f},
    {400,3,0,9999,MoveOp::Hold,1.f},

    // 402: scratch 0x3b counts the state; 18 deg turn while phase 0 and tick under 14.
    {402,0,0,0,MoveOp::CounterSet,0.f},
    {402,0,0,13,MoveOp::Turn,18.f},
    {402,-1,0,9999,MoveOp::Counter,1.f},
    // The single volley is at counter 13 and fires BOTH slots with the same row, +-40.
    voice_rule(402,-1,0,9999,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                        ShotVoiceCompare::Less,3),kGateCounterEquals,13),
    {402,-1,0,9999,MoveOp::CapturePitch,0.f,40.f,40.f,kGateCounterEquals,13},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,13,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateCounterEquals,13,
     origin_attachment_slot(1),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,13,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,-1,0,9999,MoveOp::Launch,4.f,0.f,0.f,kGatePowered | kGateCounterEquals,13,
     origin_attachment_slot(1),aim_stored_pitch()},

    // 450 ground charge: 25 deg turn to tick 16, then the 15-iteration burst at tick 17
    // (L4054-4106). The scratch 0x3d is clamped +-45 and each iteration adds
    // `(rand%100-50)*0.1` to it while the yaw takes `(rand%200-100)*0.1`; the pitch draw
    // comes first. Rows 1 normal / 5 powered.
    {450,-1,0,16,MoveOp::Turn,25.f},
    voice_rule(450,-1,17,17,shot_voice(29)),
    {450,-1,17,17,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,-1,17,17,MoveOp::Launch,1.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadBurstJitter,15},
    {450,-1,17,17,MoveOp::Launch,5.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadBurstJitter,15},
    // 460 air charge: 20 deg turn to tick 16, same burst. The clamp is the compare/assign
    // mismatch — the body tests +-30 and writes +-45 (L4330-4337) — so the snap bound
    // carries it.
    {460,-1,0,16,MoveOp::Turn,20.f},
    voice_rule(460,-1,17,17,shot_voice(29)),
    {460,-1,17,17,MoveOp::CapturePitch,45.f,30.f,30.f},
    {460,-1,17,17,MoveOp::Launch,1.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadBurstJitter,15},
    {460,-1,17,17,MoveOp::Launch,5.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadBurstJitter,15},
};

// Mion weapon 2 (handler 0x44fa10) — shoot_body_1_2_{400,402} (bundle L4442-4573,
// L4689-4802). The two charges are repeated emissions gated on
// `tick > 14 && tick % 5 == 0 && counter < 10 && 0 < w[0x1c8]`, each with the same jitter
// as Mion 1's, so they stay provisional: they need the draw service AND a source for
// +0x1c8, which has no writer in the corpus.
inline constexpr MoveRule kMion2Rules[] = {
    // Mion weapon 2 (handler 0x44fa10) — shoot_body_1_2_{400,402,450,460}. The taps fire
    // slot 0 with the powered gate switching only the ROW (0 -> 1).
    //
    // 400 ground tap: 10 deg while tick under 19 and an extra 15 deg while tick under 10
    // (L4490-4498). The body then FORCE-WRITES its tick counter from 10 to 18
    // (L4500-4503, `write_clock(0x2b81, 0x12)`), so ticks 11..17 never execute and the
    // tick-18 launch block runs on that same frame. The port's elapsed tick is the phase
    // clock, which cannot be written, so the skip is represented by placing the launch on
    // the update the teleport lands on (10) and shifting every later tick window by the
    // same seven updates: the tick-23 freeze below becomes elapsed 15.
    {400,0,0,18,MoveOp::Turn,10.f},
    {400,0,0,9,MoveOp::Turn,15.f},
    {400,0,0,17,MoveOp::Decelerate,1.5f},
    voice_rule(400,0,10,10,shot_voice(28,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Less,2)),
    {400,0,10,10,MoveOp::CapturePitch,0.f,40.f,40.f},
    {400,0,10,10,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    {400,0,10,10,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    // Freeze at body tick 23 while the 0x3e counter is under 10 (L4556-4559) — reached at
    // elapsed 15 because of the skip above.
    {400,0,0,0,MoveOp::CounterSet,0.f},
    {400,0,15,15,MoveOp::Counter,1.f},
    {400,0,15,15,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,10},

    // 402 air tap: 15 deg while tick under 14, then 10 deg while tick under 19
    // (L4731-4737). No teleport here, so the launch is on the tick-18 window itself.
    {402,0,0,13,MoveOp::Turn,15.f},
    {402,0,14,18,MoveOp::Turn,10.f},
    voice_rule(402,0,18,18,shot_voice(28,30,ShotVoiceMagazine::Primary,
                                      ShotVoiceCompare::Less,2)),
    {402,0,18,18,MoveOp::CapturePitch,0.f,40.f,40.f},
    {402,0,18,18,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    {402,0,18,18,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch()},
    // Freeze at tick 23 while 0x3e is under 10 (L4785-4788).
    {402,0,0,0,MoveOp::CounterSet,0.f},
    {402,0,23,23,MoveOp::Counter,1.f},
    {402,0,23,23,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,10},

    // 450/460 charges: repeated emissions while
    // `tick > 14 && tick % 5 == 0 && 0x3e < 10 && 0 < w[0x1c8]` (L6050, L6165), rows 2/3,
    // slot 0, clamp +-45, plus a 0.5 deg per-emission turn while 0x3e is under 10
    // (L6041/L6156). The ten tick windows below are that cadence exactly, and the counter
    // bound is implied by their count. TWO MEASURED GATES ARE NOT MODELLED: the emission
    // carries a `(rand%100-50)*0.1` yaw and a `(rand%80-40)*0.1` pitch jitter whose draw
    // needs the deterministic RNG service, and `w[0x1c8]` has no writer in the corpus so
    // the port cannot evaluate it. The requests are therefore right in count, row, slot,
    // clamp and timing, and identical in direction where the original spreads them.
    {450,0,0,9999,MoveOp::Turn,20.f},
    {450,0,0,9999,MoveOp::Decelerate,1.5f},
    {450,1,15,15,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,20,20,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,25,25,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,30,30,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,35,35,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,40,40,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,45,45,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,50,50,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,55,55,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,1,60,60,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {450,0,0,0,MoveOp::CounterSet,0.f},
    voice_rule(450,1,0,0,shot_voice(29)),
    {450,1,15,15,MoveOp::Counter,1.f},
    {450,1,15,15,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,15,15,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,20,20,MoveOp::Counter,1.f},
    {450,1,20,20,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,20,20,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,25,25,MoveOp::Counter,1.f},
    {450,1,25,25,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,25,25,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,25,25,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,30,30,MoveOp::Counter,1.f},
    {450,1,30,30,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,30,30,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,30,30,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,35,35,MoveOp::Counter,1.f},
    {450,1,35,35,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,35,35,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,35,35,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,40,40,MoveOp::Counter,1.f},
    {450,1,40,40,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,40,40,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,40,40,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,45,45,MoveOp::Counter,1.f},
    {450,1,45,45,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,45,45,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,45,45,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,50,50,MoveOp::Counter,1.f},
    {450,1,50,50,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,50,50,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,50,50,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,55,55,MoveOp::Counter,1.f},
    {450,1,55,55,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,55,55,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,55,55,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,60,60,MoveOp::Counter,1.f},
    {450,1,60,60,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,1,60,60,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {450,1,60,60,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},

    // 460 air charge: same cadence and rows; the turn is phase 0 at 20 deg with the same
    // per-emission 0.5 deg while 0x3e is under 10 (L6150-6158).
    {460,0,0,9999,MoveOp::Turn,20.f},
    {460,1,15,15,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,20,20,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,25,25,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,30,30,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,35,35,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,40,40,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,45,45,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,50,50,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,55,55,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,1,60,60,MoveOp::Turn,.5f,0.f,0.f,kGateCounterBelow,10},
    {460,0,0,0,MoveOp::CounterSet,0.f},
    voice_rule(460,1,0,0,shot_voice(29)),
    {460,1,15,15,MoveOp::Counter,1.f},
    {460,1,15,15,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,15,15,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,20,20,MoveOp::Counter,1.f},
    {460,1,20,20,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,20,20,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,25,25,MoveOp::Counter,1.f},
    {460,1,25,25,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,25,25,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,25,25,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,30,30,MoveOp::Counter,1.f},
    {460,1,30,30,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,30,30,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,30,30,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,35,35,MoveOp::Counter,1.f},
    {460,1,35,35,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,35,35,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,35,35,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,40,40,MoveOp::Counter,1.f},
    {460,1,40,40,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,40,40,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,40,40,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,45,45,MoveOp::Counter,1.f},
    {460,1,45,45,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,45,45,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,45,45,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,50,50,MoveOp::Counter,1.f},
    {460,1,50,50,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,50,50,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,50,50,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,55,55,MoveOp::Counter,1.f},
    {460,1,55,55,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,55,55,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,55,55,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,60,60,MoveOp::Counter,1.f},
    {460,1,60,60,MoveOp::CapturePitch,0.f,45.f,45.f},
    {460,1,60,60,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
    {460,1,60,60,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadEmissionJitter},
};

// Rika weapon 1 (handler 0x492f70) — shot rules recovered from the reference bodies
// shoot_body_4_1_{400,402,450,460} (bundle reference/source). Her tap is a repeating
// schedule, not a single anchor: the body fires while `tick > 11 && scratch < 30` on even
// scratch values, i.e. ticks 12, 14, ..., 40 — fifteen shots, and the usage matrix agrees
// per phase. The scratch only increments INSIDE that window, so it equals `tick - 12` and
// the even test is the tick's own parity: one `kGateCounterMod` rule over the tick window
// replaces the fifteen unrolled anchors, and it is stated before the Counter so it reads
// the pre-increment value the body does. Each shot draws `draw%14 - 7` of LATERAL offset
// first and then `draw%10 - 5` of pitch over the live clamped (+-40) target elevation
// (L21797-21805) — the lateral-first order is what SpreadOrder::LateralThenPitch states,
// and the draw order is pinned by the witness. The row (0) and the hand (`Bip01_L_Hand`)
// both come from the body's own FUN_00435220 call; the older note claiming the row came
// only from the item table was wrong. The charges' tick-10 pair (rows 2/5) fires in BOTH
// branches; the tick-30 pair is rows 3/6 normally and 4/7 powered, counter-gated and
// repeated by the freeze — see the 450 block below for the line citations. No Hide rules:
// the prop calls' 2/3/-1 semantics are illegible (bundle RESPONSE §2).
inline constexpr MoveRule kRikaRules[] = {
    // 400 ground tap: 15 deg turn ticks 0-14 (L21764-67), phase-0 bleed (L21768-71).
    {400,-1,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    // The window is `tick > 11 && scratch < 30` with a fire on EVEN scratch values,
    // and the scratch only increments inside the window — so scratch == tick - 12 and
    // the parity is the tick's own. The Launch is stated BEFORE the Counter so it reads
    // the pre-increment value, which is what the body's fire-then-increment does.
    voice_rule(400,-1,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,11)),
    {400,-1,12,41,MoveOp::Launch,0.f,0.f,0.f,kGateCounterMod,2,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadRika1Tap},
    {400,-1,12,41,MoveOp::Counter,1.f},
    // 402 air tap: 20 deg turn ticks 0-14 (L22077-80), same even-tick window (L22086).
    {402,-1,0,14,MoveOp::Turn,20.f},
    voice_rule(402,-1,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,11)),
    {402,-1,12,12,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,14,14,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,16,16,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,18,18,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,20,20,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,22,22,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,24,24,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,26,26,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,28,28,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,30,30,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,32,32,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,34,34,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,36,36,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,38,38,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,40,40,MoveOp::Launch,0.f,0.f,40.f},
    // 450 ground charge1: 18 deg movement-preserving turn through tick 9
    // (L23458-60), horizontal bleed 0.5/tick clamped at 0 (L23451-55), plus the
    // powered-only 0.1 deg turn while tick < 51 (L23462-65).
    {450,-1,0,9,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(450,0,10,10,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                      ShotVoiceCompare::Less,3)),
    {450,-1,0,50,MoveOp::Turn,.1f,0.f,0.f,kGatePowered},
    // The body seeds a scratch counter at phase0/tick0 (L23446-50) and increments it
    // once per update AFTER the fire checks (L23639), so the counter equals the phase
    // tick until the freeze pins the clock.
    {450,0,0,0,MoveOp::CounterSet,0.f},
    // tick 10 twin pair — rows 2 (+50) and 5 (-50), forward 60, height +70, in BOTH
    // branches (L23507-123). The geometry is stated as typed specs because the legacy
    // adapter carries Rena 0's red-charge shape (forward/height 70, yaw offset +-1 deg),
    // which is not this body's.
    // The body computes the pitch ONCE at tick 10 (FUN_0042da80 -> FUN_0066b668 ->
    // write_scratch(0x3c)) and reads it back for every later salvo, so the capture
    // rule precedes the requests and they all resolve against the latched value.
    {450,0,10,10,MoveOp::CapturePitch,0.f,40.f,40.f},
    {450,-1,10,10,MoveOp::Launch,2.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(50.f,60.f,70.f),aim_stored_pitch()},
    {450,-1,10,10,MoveOp::Launch,5.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-50.f,60.f,70.f),aim_stored_pitch()},
    // tick 30 salvo: rows 3/6 normal (L23536-149), rows 4/7 powered (L23623-236),
    // each gated on `counter > 0 && counter % 10 == 0` (L23534/L23620). The body picks
    // ONE pair per branch, so the normal pair carries kGateNormal as well — without it
    // a powered fighter fires both pairs.
    {450,-1,30,30,MoveOp::Launch,3.f,0.f,0.f,kGateNormal|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(50.f,60.f,70.f),aim_stored_pitch()},
    {450,-1,30,30,MoveOp::Launch,6.f,0.f,0.f,kGateNormal|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(-50.f,60.f,70.f),aim_stored_pitch()},
    {450,-1,30,30,MoveOp::Launch,4.f,0.f,0.f,kGatePowered|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(50.f,60.f,70.f),aim_stored_pitch()},
    {450,-1,30,30,MoveOp::Launch,7.f,0.f,0.f,kGatePowered|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(-50.f,60.f,70.f),aim_stored_pitch()},
    // The freeze: the body returns before write_clock while the post-increment
    // counter is below 60 (L23639-243), which pins the tick at 30 for exactly 30
    // updates. The counter rule must precede this one so the gate reads the
    // post-increment value; the tick-30 salvo then fires at counter 30, 40 and 50 —
    // three pairs, not the single pair the previous rules claimed.
    {450,0,0,9999,MoveOp::Counter,1.f},
    {450,0,30,30,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,60},
    // 460 air charge1: identical row schedule in the same two branches (L23744-232);
    // it clears the horizontal/vertical/gravity channels at phase0/tick0 instead of
    // bleeding, which has no MoveRule op and stays an explicit gap.
    {460,-1,0,9,MoveOp::Turn,18.f},
    voice_rule(460,-1,10,10,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,3)),
    {460,-1,0,50,MoveOp::Turn,.1f,0.f,0.f,kGatePowered},
    {460,0,0,0,MoveOp::CounterSet,0.f},
    // The body computes the pitch ONCE at tick 10 (FUN_0042da80 -> FUN_0066b668 ->
    // write_scratch(0x3c)) and reads it back for every later salvo, so the capture
    // rule precedes the requests and they all resolve against the latched value.
    {460,0,10,10,MoveOp::CapturePitch,0.f,40.f,40.f},
    {460,-1,10,10,MoveOp::Launch,2.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(50.f,60.f,70.f),aim_stored_pitch()},
    {460,-1,10,10,MoveOp::Launch,5.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-50.f,60.f,70.f),aim_stored_pitch()},
    {460,-1,30,30,MoveOp::Launch,3.f,0.f,0.f,kGateNormal|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(50.f,60.f,70.f),aim_stored_pitch()},
    {460,-1,30,30,MoveOp::Launch,6.f,0.f,0.f,kGateNormal|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(-50.f,60.f,70.f),aim_stored_pitch()},
    {460,-1,30,30,MoveOp::Launch,4.f,0.f,0.f,kGatePowered|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(50.f,60.f,70.f),aim_stored_pitch()},
    {460,-1,30,30,MoveOp::Launch,7.f,0.f,0.f,kGatePowered|kGateCounter|kGateCounterMod,10,
     origin_actor_relative(-50.f,60.f,70.f),aim_stored_pitch()},
    {460,0,0,9999,MoveOp::Counter,1.f},
    {460,0,30,30,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,60},
};
// Satoko weapon 1 (handler 0x4b4090) — shoot_body_3_1_{400,402,450,460}. This weapon is a
// PERIODIC world projectile rather than a salvo: a countdown starts at 120, drops one a
// tick, and the request fires whenever it is 1 mod 30 — so in the port's pre-increment
// numbering the shots land on ticks 28, 58, 88, ... Each firing puts ONE world request at
// the actor's own position 50 units UP (`0x42480000`; an earlier note said 600, a mis-read of
// the hex), aimed along the heading with pitch 0, on row 6
// normally and row 7 powered, and it runs in EVERY state. The charges add one request at
// tick 35 (0x23) at the actor's own position with no height, row 0 normal / row 1 powered.
// No MoveRule op: the gravity tail (`w[0x15] -= 1.5`, clamped at 0 in every state) and the
// movement-offset yaw term `w[0x19]`.
//
// kGateCounterMod tests `counter % gateValue == 0`, so the counter starts at 118 rather
// than the body's 120: 118 - 28 = 90 and 90 % 30 == 0 lands on the tick the body's
// 91 % 30 == 1 does.
inline constexpr MoveRule kSatoko1Rules[] = {
    {400,0,0,0,MoveOp::CounterSet,118.f},
    // FUN_004b4090:1731: this tap body calls ShotB on entry, before its first periodic request.
    voice_rule(400,0,0,0,shot_voice(28)),
    {400,-1,1,9999,MoveOp::Counter,-1.f},
    {400,-1,0,9999,MoveOp::Launch,6.f,0.f,0.f,kGateNormal | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
    {400,-1,0,9999,MoveOp::Launch,7.f,0.f,0.f,kGatePowered | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
    // 402 air tap: the same periodic shot with no state-specific change.
    {402,0,0,0,MoveOp::CounterSet,118.f},
    voice_rule(402,0,0,0,shot_voice(28)),
    {402,-1,1,9999,MoveOp::Counter,-1.f},
    {402,-1,0,9999,MoveOp::Launch,6.f,0.f,0.f,kGateNormal | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
    {402,-1,0,9999,MoveOp::Launch,7.f,0.f,0.f,kGatePowered | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
    // 450 ground charge: the tick-35 request, then the periodic one it keeps firing.
    {450,0,0,0,MoveOp::CounterSet,118.f},
    {450,-1,1,9999,MoveOp::Counter,-1.f},
    {450,-1,35,35,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(0.f,0.f,0.f),aim_fixed_angles(0.f,0.f)},
    {450,-1,35,35,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(0.f,0.f,0.f),aim_fixed_angles(0.f,0.f)},
    {450,-1,0,9999,MoveOp::Launch,6.f,0.f,0.f,kGateNormal | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
    {450,-1,0,9999,MoveOp::Launch,7.f,0.f,0.f,kGatePowered | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
    // 460 air charge: the same, and its tick-0 block only zeroes velocities.
    {460,0,0,0,MoveOp::CounterSet,118.f},
    {460,-1,1,9999,MoveOp::Counter,-1.f},
    {460,-1,35,35,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(0.f,0.f,0.f),aim_fixed_angles(0.f,0.f)},
    {460,-1,35,35,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(0.f,0.f,0.f),aim_fixed_angles(0.f,0.f)},
    {460,-1,0,9999,MoveOp::Launch,6.f,0.f,0.f,kGateNormal | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
    {460,-1,0,9999,MoveOp::Launch,7.f,0.f,0.f,kGatePowered | kGateCounterMod,30,
     origin_actor_relative(0.f,0.f,50.f),aim_fixed_angles(0.f,0.f)},
};

// Satoko weapon 2 (handler 0x4bc040) — shot rules recovered from the reference bodies
// shoot_body_3_2_{400,402,450,460} (bundle reference/source). All four bodies request
// through FUN_00435450 with explicit world coordinates, so a Prop1/attachment program
// would lose them: item 38 ships two EMPTY attachment meshes and fifteen bullet
// registrations. The tap pair is the twin at tick 20 — forward 100, lateral -50/+50,
// height +70, yaw on the legacy heading basis, pitch = target elevation clamped
// +-40 — firing row 0 normally and row 1 when the powered gate holds. The gate is
// the roster-wide idiom `byte(+0x845) && word(+0x848)`; see kGatePowered.
//
// Still pending for this combo, deliberately NOT inferred: 450/460's phase-1 tick-6
// single request (row 4 normal / 5 powered) and their charge-side movement — the
// bodies turn 15 while phase<1, the ground charge decelerates 1.5 to zero, the air
// charge scales horizontal/vertical velocity by 0.25 at phase0/tick0 and applies
// gravity in phase2 after 30F, and both initialize a scratch counter at phase0/tick0
// and freeze clock advancement ten updates at tick26. The state400 world aim also
// uses heading + the battle movement offset (source_float(0x19)), which this port does
// not carry, so the fired yaw tracks the heading alone.
inline constexpr MoveRule kSatoko2Rules[] = {
    // 400 ground tap: 15 deg movement-preserving turn through tick 19 (L16494-96),
    // horizontal bleed 0.5/tick clamped at 0 (L16497-16501).
    {400,-1,0,19,MoveOp::Turn,15.f},
    {400,-1,0,9999,MoveOp::Decelerate,.5f},
    // tick 20 twin pair, normal rows then powered rows (L16528-16583).
    voice_rule(400,0,20,20,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                      ShotVoiceCompare::Less,6)),
    {400,0,20,20,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,100.f,70.f),aim_target_elevation(40.f)},
    {400,0,20,20,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(50.f,100.f,70.f),aim_target_elevation(40.f)},
    {400,0,20,20,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,100.f,70.f),aim_target_elevation(40.f)},
    {400,0,20,20,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(50.f,100.f,70.f),aim_target_elevation(40.f)},
    // 402 air tap: 20 deg turn through tick 19 (L16800-802), movement cleared at
    // tick 0 (L16803-805), same twin pair at tick 20.
    {402,-1,0,19,MoveOp::Turn,20.f},
    voice_rule(402,-1,20,20,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,6)),
    {402,-1,20,20,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,100.f,70.f),aim_target_elevation(40.f)},
    {402,-1,20,20,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(50.f,100.f,70.f),aim_target_elevation(40.f)},
    {402,-1,20,20,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,100.f,70.f),aim_target_elevation(40.f)},
    {402,-1,20,20,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(50.f,100.f,70.f),aim_target_elevation(40.f)},
};

// Keiichi weapon 0 (handler 0x46a190) — shot rules recovered from the reference bodies
// shoot_body_2_0_{400,402,450,460} (bundle reference/source). The taps fire ONE hand
// request at tick 13 through FUN_00435220 on Bip01_R_Hand (row 0 normally, row 3
// powered), with the pitch computed, stored and read back in the same tick. The air
// tap snaps the pitch (compare +-30, assign +-45) instead of clamping. The charges
// add a LEFT-hand request at tick 4 (row 1, fixed yaw/pitch 0, unconditional) and an
// attachment request at tick 20 (slot 0, row 2 normally / row 4 powered, stored
// pitch). Both slots stay bound throughout; no Hide rules.
inline constexpr MoveRule kKeiichi0Rules[] = {
    // 400 ground tap: 20 deg turn through tick 13 (FUN_0042db10), bleed 0.5 (L6346-56).
    {400,-1,0,13,MoveOp::Turn,20.f},
    {400,-1,0,9999,MoveOp::Decelerate,.5f},
    // Tick-13 hand request, normal then powered (L6356-79).
    voice_rule(400,0,13,13,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {400,0,13,13,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,0,13,13,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {400,0,13,13,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // 402 air tap: 20 deg movement-preserving turn through tick 13, movement cleared
    // at tick 0 and gravity applied (no MoveRule ops — explicit gaps). Same tick-13
    // hand request with the snapped pitch.
    {402,-1,0,13,MoveOp::Turn,20.f},
    voice_rule(402,0,13,13,shot_voice(28,30,ShotVoiceMagazine::Primary,
                                      ShotVoiceCompare::Equal,1)),
    {402,0,13,13,MoveOp::CapturePitch,45.f,30.f,30.f},
    {402,0,13,13,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {402,0,13,13,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // 450 ground charge: 18 deg turn through tick 19, bleed 0.5. Tick-4 left hand,
    // tick-20 attachment pair (L8368-8406).
    {450,-1,0,19,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    {450,0,4,4,MoveOp::Launch,1.f,0.f,0.f,kGateNone,0,
     origin_named_bone("Bip01_L_Hand"),aim_fixed_angles(0.f,0.f)},
    voice_rule(450,0,20,20,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                      ShotVoiceCompare::Equal,1)),
    {450,0,20,20,MoveOp::CapturePitch,0.f,40.f,40.f},
    {450,0,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {450,0,20,20,MoveOp::Launch,4.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_stored_pitch()},
    // 460 air charge: 18 deg movement-preserving turn through tick 19; entry halve
    // and gravity have no ops (explicit gaps). Same tick-4/tick-20 requests.
    {460,-1,0,19,MoveOp::Turn,18.f},
    {460,0,4,4,MoveOp::Launch,1.f,0.f,0.f,kGateNone,0,
     origin_named_bone("Bip01_L_Hand"),aim_fixed_angles(0.f,0.f)},
    voice_rule(460,0,20,20,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                      ShotVoiceCompare::Equal,1)),
    {460,0,20,20,MoveOp::CapturePitch,0.f,40.f,40.f},
    {460,0,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_stored_pitch()},
    {460,0,20,20,MoveOp::Launch,4.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_stored_pitch()},
};

// Keiichi weapon 1 (handler 0x473610) — shot rules recovered from the reference bodies
// shoot_body_2_1_{400,402,450,460} (bundle reference/source). The taps are the same
// shape as Keiichi 0's (hand R at tick 13, stored pitch) with powered row 1 instead
// of 3. The charges fire TWO world requests at tick 20 — row 9 unconditionally, then
// row 2 normally / row 3 powered — both at forward 0, lateral -50, height +40 ground
// (+20 air), with the range-dependent pitch (base plus dist*40/5000, x0.95 when the
// base is negative).
inline constexpr MoveRule kKeiichi1Rules[] = {
    // 400 ground tap: 20 deg turn through tick 13, bleed 0.5 (L8776-89).
    {400,-1,0,13,MoveOp::Turn,20.f},
    {400,-1,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(400,0,13,13,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {400,0,13,13,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,0,13,13,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {400,0,13,13,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // 402 air tap: 20 deg movement-preserving turn through tick 13 (movement clear
    // and gravity are explicit gaps). Same hand request with the snapped pitch.
    {402,-1,0,13,MoveOp::Turn,20.f},
    voice_rule(402,0,13,13,shot_voice(28,30,ShotVoiceMagazine::Primary,
                                      ShotVoiceCompare::Equal,1)),
    {402,0,13,13,MoveOp::CapturePitch,45.f,30.f,30.f},
    {402,0,13,13,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {402,0,13,13,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // 450 ground charge: 18 deg turn through tick 19, bleed 0.5. Tick-20 world pair
    // (L10004-10093).
    {450,-1,0,19,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(450,0,20,20,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                      ShotVoiceCompare::Equal,1)),
    {450,0,20,20,MoveOp::Launch,9.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range()},
    {450,0,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range()},
    {450,0,20,20,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range()},
    // 460 air charge: 18 deg movement-preserving turn through tick 19 (entry halve
    // and gravity are explicit gaps). Same pair at height +20.
    {460,-1,0,19,MoveOp::Turn,18.f},
    voice_rule(460,0,20,20,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                      ShotVoiceCompare::Equal,1)),
    {460,0,20,20,MoveOp::Launch,9.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-50.f,0.f,20.f),aim_elevation_plus_range()},
    {460,0,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,0.f,20.f),aim_elevation_plus_range()},
    {460,0,20,20,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,0.f,20.f),aim_elevation_plus_range()},
};

// Tomitake weapon 2 (handler 0x527880) — shot rules recovered from the reference bodies
// shoot_body_6_2_{400,402,450,460} (bundle reference/source). Two shots per scheduled
// tick. The tap (L36890-36930) is gated on `scratch % 3 == 0 && 0 < w[0x1b7]` and fires
// row 7 first — lateral 0, pitch 0 — then EITHER row 5 or row 6, chosen by the same
// `byte(+0x845) && word(+0x212)` idiom kGatePowered models (usage slots 5 normal / 6 tag /
// 7 both map to the same rows; row 7 is what the traces record: fire_attachment(0,7,...)).
// The ground tap swaps the two rows' draw moduli — `(draw%12-6)*0.25` of pitch and
// `(draw%6-3)*0.5` of lateral on row 5, `(draw%6-3)*0.25` and `(draw%12-6)*0.25` on row 6 —
// while the air tap uses 6/-3 for both. Elevation clamped +-45. The tap schedule (ticks
// 15..33 step 3) is written tick-explicit like Rika's: our rule model has no modulo.
// The charges (L39390-39440, L39550-39600) are WORLD requests, not attachment ones: the actor's
// position displaced 50 FORWARD (`0x42480000` against the `yaw` table) and 75 UP (`0x42960000`).
// Row 4 fires unconditionally there with LITERAL pitch 0 and lateral 0; then row 0 normally or
// row 2 powered on `byte(+0x845) && word(+0x212)`, at the same origin but with the target
// elevation clamped +-40 as the pitch. So they are `origin_actor_relative(0, 50, 75)`, not the
// default attachment slot with a target-derived pitch. The old note called the tag rows "6/2";
// the body says 4 always plus 2 powered, and the flag is the same idiom the tap uses.
// Turn verbs 0042dc20 vs 0042db10 both map to Turn by value (the distinction's meaning
// is illegible); the w0x10 gravity tails (unclamped, can go negative) are vertical
// physics with no MoveRule op and are skipped — only the floor-0 w0x15 bleeds map to
// Decelerate. Charge-2 stays unbound (-1): bodies 403-414 exist but are out of scope.
inline constexpr MoveRule kTomitakeRules[] = {
    // 400 ground tap: overlapping turns 18 deg (ticks 0-9) + 2 deg (ticks 0-34),
    // horizontal bleed 2.0/tick from tick 1 (L36849-36857).
    {400,-1,0,9,MoveOp::Turn,18.f},
    {400,-1,0,34,MoveOp::Turn,2.f},
    {400,-1,1,9999,MoveOp::Decelerate,2.f},
    // FUN_00527880 calls its tap line only on the first scheduled burst tick.
    voice_rule(400,-1,15,15,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {400,-1,15,15,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,15,15,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround5},
    {400,-1,15,15,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround6},
    {400,-1,18,18,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,18,18,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround5},
    {400,-1,18,18,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround6},
    {400,-1,21,21,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,21,21,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround5},
    {400,-1,21,21,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround6},
    {400,-1,24,24,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,24,24,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround5},
    {400,-1,24,24,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround6},
    {400,-1,27,27,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,27,27,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround5},
    {400,-1,27,27,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround6},
    {400,-1,30,30,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,30,30,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround5},
    {400,-1,30,30,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround6},
    {400,-1,33,33,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {400,-1,33,33,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround5},
    {400,-1,33,33,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeGround6},
    // 402 air tap: disjoint turns 15 deg (0-9) + 5 deg (10-24), same twin schedule.
    {402,-1,0,9,MoveOp::Turn,15.f},
    {402,-1,10,24,MoveOp::Turn,5.f},
    voice_rule(402,-1,15,15,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {402,-1,15,15,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,-1,15,15,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,15,15,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,18,18,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,-1,18,18,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,18,18,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,21,21,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,-1,21,21,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,21,21,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,24,24,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,-1,24,24,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,24,24,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,27,27,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,-1,27,27,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,27,27,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,30,30,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,-1,30,30,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,30,30,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,33,33,MoveOp::Launch,7.f,0.f,0.f,kGateNone,0,
     origin_attachment_slot(0),aim_fixed_angles(0.f,0.f)},
    {402,-1,33,33,MoveOp::Launch,5.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    {402,-1,33,33,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_target_elevation(45.f),{},kSpreadTomitakeAir},
    // 450 ground charge1: turns 35 deg (0-4) + 0.3 deg (0-29), bleed 1.5/tick,
    // single salvo rows 4+0 at tick 30 after a 15-tick freeze at tick 28.
    {450,-1,0,4,MoveOp::Turn,35.f},
    {450,-1,0,29,MoveOp::Turn,0.3f},
    {450,-1,0,9999,MoveOp::Decelerate,1.5f},
    {450,-1,28,28,MoveOp::Hold,15.f},
    {450,-1,30,30,MoveOp::Launch,4.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(0.f,50.f,75.f),aim_fixed_angles(0.f,0.f)},
    {450,-1,30,30,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(0.f,50.f,75.f),aim_target_elevation(40.f)},
    {450,-1,30,30,MoveOp::Launch,2.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(0.f,50.f,75.f),aim_target_elevation(40.f)},
    // 460 air charge1: same shape (no w0x15 bleed of its own — skipped, see above).
    {460,-1,0,4,MoveOp::Turn,35.f},
    {460,-1,0,29,MoveOp::Turn,0.3f},
    {460,-1,28,28,MoveOp::Hold,15.f},
    {460,-1,30,30,MoveOp::Launch,4.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(0.f,50.f,75.f),aim_fixed_angles(0.f,0.f)},
    {460,-1,30,30,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(0.f,50.f,75.f),aim_target_elevation(40.f)},
    {460,-1,30,30,MoveOp::Launch,2.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(0.f,50.f,75.f),aim_target_elevation(40.f)},
};
// Keiichi weapon 2 (handler 0x47b940) — shot rules recovered from the reference bodies
// shoot_body_2_2_{400,402,450,460} (bundle reference/source). Dense burst, a fourth
// shape: the tap fires EVERY tick 10..20 (11 consecutive frames, rows 0 normal / 1 tag),
// expressed as one window rule per row — the executor runs matching rules each update,
// so first/last IS the burst (unlike Rika's even-only schedule, which needs tick rules).
// The powered row IS gated: the body's row branch tests `byte(+0x845) && word(+0x212)`,
// which is kGatePowered, so the tap binds row 0 normal / row 1 powered and the charges rows 2/3
// (below). The charges are WORLD requests (L12186-12217): the actor's position displaced `-50`
// on the PERPENDICULAR axis (`0x42480000` against the `yaw + 90` table) at height +40
// (`0x42200000`), with the elevation latched at tick 13 and clamped +-40 — so they are
// `origin_actor_relative(-50, 0, 40)`, not the attachment adapter they were bound through.
// Their PITCH is not the bare latched elevation: the body then adds a range term,
// `clamp(dist * 40 / 4000, 10, 50)` shrunk by 0.95 when the base is negative (L12172-12184), so
// they aim with aim_elevation_plus_range_keiichi2() — the same shape as Keiichi 1's charges but
// with a different divisor AND different bounds. A stored pitch alone adds 0 where the source
// adds that term.
// Turn verbs db10 vs dc20 both map to
// Turn by value (distinction illegible); the w0x10 gravity tails and the one-shot w0x15
// halve are vertical physics with no MoveRule op — skipped.
inline constexpr MoveRule kKeiichiRules[] = {
    // 400 ground tap (L10331-10456): 20 deg turn while phase 0 and tick under 12, and an
    // eleven-tick SWEEP from tick 10 to 20 (9 < tick < 0x15). Each tick grows scratch 0x3a
    // by 2 and fires one slot-0 request aimed `0x3a - 15 + draw%10` on the yaw with
    // `draw%10 + 5` of pitch over the clamped target elevation (+-30), row 0 normally and
    // row 1 powered. The yaw draw comes FIRST (0x3b <- draw 1, 0x3c <- draw 2).
    {400,0,0,11,MoveOp::Turn,20.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,0,0,0,MoveOp::CounterSet,0.f},
    voice_rule(400,0,10,10,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                     ShotVoiceCompare::Equal,1)),
    {400,-1,10,20,MoveOp::Counter,2.f},
    {400,-1,10,20,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,-1,10,20,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadTapSweep},
    {400,-1,10,20,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadTapSweep},
    // 402 air tap (L10584-10706): the same window and sweep on the movement-preserving
    // turn helper, 20 deg while tick under 12. State 401 (L10457) is the same request
    // with an extra 15 deg phase-0 turn and no state-403 abort; the port binds 402, which
    // is the air-tap slot the other combos use, and leaves 401 unbound.
    {402,-1,0,11,MoveOp::Turn,20.f},
    {402,0,0,0,MoveOp::CounterSet,0.f},
    voice_rule(402,-1,10,10,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Equal,1)),
    {402,-1,10,20,MoveOp::Counter,2.f},
    {402,-1,10,20,MoveOp::CapturePitch,0.f,30.f,30.f},
    {402,-1,10,20,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadTapSweep},
    {402,-1,10,20,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadTapSweep},
    // 450 ground charge1: 18 deg turn through tick 12, bleed 0.75/tick, single salvo
    // row 2 at tick 13, clock-rewind stalls +10f at tick 5 and +15f at tick 32 (Hold
    // rules; the per-rule latch in the executor gives each stall its full length).
    {450,-1,0,12,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.75f},
    {450,-1,5,5,MoveOp::Hold,10.f},
    voice_rule(450,-1,13,13,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {450,-1,13,13,MoveOp::CapturePitch,0.f,40.f,40.f},
    {450,-1,13,13,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range_keiichi2()},
    {450,-1,13,13,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range_keiichi2()},
    {450,-1,32,32,MoveOp::Hold,15.f},
    // 460 air charge1: same shape (turn 18, salvo row 2 at 13, stalls at 5/32).
    {460,-1,0,12,MoveOp::Turn,18.f},
    voice_rule(460,-1,13,13,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {460,-1,13,13,MoveOp::CapturePitch,0.f,40.f,40.f},
    {460,-1,13,13,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range_keiichi2()},
    {460,-1,13,13,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range_keiichi2()},
    {460,-1,5,5,MoveOp::Hold,10.f},
    {460,-1,32,32,MoveOp::Hold,15.f},
};
// Chie weapon 2 (handler 0x566a40) — shot rules recovered from the reference bodies
// shoot_body_11_2_{400,402,450,460} (bundle reference/source). Tap bursts run on a
// scratch counter (1 at burst start, +1 a tick, fire while `counter % 3 == 1`): 400 fires
// ticks 15,18,21,24 while `counter < 11` and 402 fires 17,20,23,26,29 while `counter < 14`.
// Every shot is a `FUN_00435220` request on the posed hand — `Bip01_R_Hand` on the ground
// tap and `Bip01_L_Hand` on the air tap — with the pitch taken from the target elevation
// clamped +-40 and the lateral aiming `counter * 0.5 - 2`, so the burst walks -1.5, 0,
// 1.5, 3.0 (4.5 on the air tap's fifth shot). Row 0 normal / row 1 powered: the row
// branch tests `byte(+0x845) && word(+0x212)` (kGatePowered), while the `w[0x1b7] < 5` /
// `< 6` test beside it only picks the SOUND. The earlier "no flag field" note was wrong. The charges fire one request — row 2 normal / row 3
// powered, lateral 0, on `Bip01_R_Hand`, target elevation clamped +-30 (0x1e, not the tap's
// 40) — at tick 22 on the ground charge and tick 15 on the air one. The 460 rule used to
// sit at tick 22 while this comment said 15; the body's `== 0xf` settles it at 15. Turn
// windows and the phase-0/unconditional bleeds are measured per body; gravity
// tails and the aim pitch ramp have no MoveRule op and are skipped.
inline constexpr MoveRule kChieRules[] = {
    // 400 ground tap: 15 deg turn phase 0 ticks 0-14, bleed 0.5/tick phase 0.
    {400,0,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,15,15,MoveOp::CounterSet,1.f},
    {400,-1,16,9999,MoveOp::Counter,1.f},
    voice_rule(400,-1,15,15,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,5)),
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {400,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {400,-1,18,18,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {400,-1,18,18,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {400,-1,21,21,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {400,-1,21,21,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {400,-1,24,24,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {400,-1,24,24,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    // 402 air tap: 20 deg turn ticks 0-16 (no phase gate), same burst shape at 17+.
    {402,-1,0,16,MoveOp::Turn,20.f},
    {402,-1,17,17,MoveOp::CounterSet,1.f},
    {402,-1,18,9999,MoveOp::Counter,1.f},
    voice_rule(402,-1,17,17,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,6)),
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,17,17,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,20,20,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,20,20,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,23,23,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,23,23,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,26,26,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,26,26,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,29,29,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    {402,-1,29,29,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_L_Hand"),aim_target_elevation(40.f),{},kSpreadChieBurst},
    // 450 ground charge1: 18 deg turn through tick 19, bleed 0.5/tick unconditional,
    // single salvo row 2 at tick 22.
    {450,-1,0,19,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(450,-1,22,22,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,3)),
    {450,-1,22,22,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(30.f)},
    {450,-1,22,22,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(30.f)},
    // 460 air charge1: 18 deg turn through tick 24, single salvo row 2 at tick 15.
    {460,-1,0,24,MoveOp::Turn,18.f},
    voice_rule(460,-1,15,15,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,3)),
    {460,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(30.f)},
    {460,-1,15,15,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(30.f)},
};
// Takano weapon 0 (handler 0x531ce0) — shot rules recovered from the reference bodies
// shoot_body_7_0_{400,402,450,460} (bundle reference/source). Double turn in the tap
// (10 deg ticks 0-17 phaseless + 15 deg phase-0 open) with a phase-0 bleed; three single
// `FUN_00435220` requests on `Bip01_R_Hand` at ticks 12, 15 and 18, each taking the target
// elevation clamped +-40 (L39785-39820). Row 0 normal / row 6 powered: the row branch
// tests `byte(+0x845) && word(+0x212)` (kGatePowered), while the `w[0x1b7] < 4` beside it
// only picks the SOUND. The earlier "no flag field" note here was wrong. The charges fire one slot-0 attachment request at tick 18 (450) and tick 17 (460)
// with the elevation clamped +-40 — row 1 normal / row 7 powered on the same gate — plus
// slot-0 Hide windows (10-17 and 0-16); the slot1→2 half has no field. No Hold anywhere; gravity tails skipped.
inline constexpr MoveRule kTakanoRules[] = {
    // 400 ground tap: turns 10 deg (0-17) + 15 deg (phase 0), bleed 0.5 phase 0.
    {400,-1,0,17,MoveOp::Turn,10.f},
    {400,0,0,9999,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(400,-1,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,4)),
    {400,-1,12,12,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {400,-1,12,12,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {400,-1,15,15,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {400,-1,18,18,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {400,-1,18,18,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    // 402 air tap: turn 20 deg ticks 0-17, same triple row 0 (no bleed — gravity tail).
    {402,-1,0,17,MoveOp::Turn,20.f},
    voice_rule(402,-1,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,4)),
    {402,-1,12,12,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {402,-1,12,12,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {402,-1,15,15,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {402,-1,18,18,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    {402,-1,18,18,MoveOp::Launch,6.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_target_elevation(40.f)},
    // 450 ground charge1: turn 20 deg through tick 16, Hide slot 0 ticks 10-17,
    // single salvo row 1 at tick 18.
    {450,-1,0,16,MoveOp::Turn,20.f},
    {450,-1,10,17,MoveOp::Hide,0.f},
    voice_rule(450,-1,18,18,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {450,-1,18,18,MoveOp::Launch,1.f,0.f,40.f,kGateNormal},
    {450,-1,18,18,MoveOp::Launch,7.f,0.f,40.f,kGatePowered},
    // 460 air charge1: turn 15 deg through tick 14, Hide slot 0 ticks 0-16,
    // single salvo row 1 at tick 17.
    {460,-1,0,14,MoveOp::Turn,15.f},
    {460,-1,0,16,MoveOp::Hide,0.f},
    voice_rule(460,-1,17,17,shot_voice(29)),
    {460,-1,17,17,MoveOp::Launch,1.f,0.f,40.f,kGateNormal},
    {460,-1,17,17,MoveOp::Launch,7.f,0.f,40.f,kGatePowered},
};
// Kasai weapon 1 (handler 0x5b9680) — shot rules recovered from the reference bodies
// shoot_body_12_1_{400,402,450,460} (bundle reference/source). Twin shots rows 2+0
// per burst tick (row 2 always, row 0 normal / row 1 tag — only normal bound); the
// base burst fires at ticks 10 and 15 (cooldown 5, burst count 2), extended bursts
// (usage counts 4/6) need runtime burst state this model has no field for — gap.
// Single salvos of FOUR row-4 fan shots at tick 18 (450) and tick 17 (460); the fan
// offsets have no fields, so the four share one trajectory (count-faithful).
// No phase gates anywhere; no Hold; prop Hide semantics illegible (no rules).
inline constexpr MoveRule kKasaiRules[] = {
    // 400 ground tap: 18 deg turn ticks 0-9, 10 deg exactly at tick 10, bleed 2.0/tick.
    {400,-1,0,9,MoveOp::Turn,18.f},
    {400,-1,10,10,MoveOp::Turn,10.f},
    {400,-1,1,9999,MoveOp::Decelerate,2.f},
    voice_rule(400,-1,10,10,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {400,-1,10,10,MoveOp::Launch,2.f,0.f,45.f},
    {400,-1,10,10,MoveOp::Launch,0.f,0.f,45.f},
    {400,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,45.f},
    // 402 air tap: 15 deg turn ticks 0-9, 5 deg ticks 10-24, same twin salvos.
    {402,-1,0,9,MoveOp::Turn,15.f},
    {402,-1,10,24,MoveOp::Turn,5.f},
    voice_rule(402,-1,10,10,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {402,-1,10,10,MoveOp::Launch,2.f,0.f,45.f},
    {402,-1,10,10,MoveOp::Launch,0.f,0.f,45.f},
    {402,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,45.f},
    // 450 ground charge1: 20 deg turn through tick 9, fan of four row-4 at tick 18.
    {450,-1,0,9,MoveOp::Turn,20.f},
    voice_rule(450,-1,18,18,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,5)),
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    // 460 air charge1: 15 deg turn through tick 11, fan of four row-4 at tick 17.
    {460,-1,0,11,MoveOp::Turn,15.f},
    voice_rule(460,-1,17,17,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,7)),
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
};
// Irie weapon 1 (handler 0x57f600) — shot rules recovered from the reference bodies
// shoot_body_10_1_{400,402,450,460} (bundle reference/source). Both taps fire at tick 12:
// TWO world requests normally, on rows 1 then 0, and FOUR powered, on rows 3, 2, 1 then 0
// (L63286-63302, L63551-63610) — the tag branch ADDS the row-2/3 pair rather than replacing
// the row-0/1 one. The row branch tests `byte(+0x845) && word(+0x212)` (kGatePowered); the
// `w[0x1b7] < 4` beside it only picks the sound, and the "no flag field" note was wrong. Each request sits 100 units out at +-4 degrees of heading with the
// target elevation clamped +-40 (a world pair this port still places through the adapter).
// The charges fire one `FUN_00434fd0` request — row 4 normal / row 5 powered, elevation
// clamped +-30 — at tick 22 (450) and tick 17 (460). Hide windows carry slot 0 only
// (slot-1 halves have no field). Gravity tails and one-shot velocity sets have no MoveRule
// op — skipped.
inline constexpr MoveRule kIrieRules[] = {
    // 400 ground tap: 20 deg turn ticks 0-11, bleed 0.5/tick, twin rows 0+1 at 12.
    {400,-1,0,11,MoveOp::Turn,20.f},
    {400,-1,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(400,-1,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,4)),
    {400,-1,12,12,MoveOp::Launch,1.f,0.f,40.f,kGateNormal},
    {400,-1,12,12,MoveOp::Launch,0.f,0.f,40.f,kGateNormal},
    {400,-1,12,12,MoveOp::Launch,3.f,0.f,40.f,kGatePowered},
    {400,-1,12,12,MoveOp::Launch,2.f,0.f,40.f,kGatePowered},
    {400,-1,12,12,MoveOp::Launch,1.f,0.f,40.f,kGatePowered},
    {400,-1,12,12,MoveOp::Launch,0.f,0.f,40.f,kGatePowered},
    // 402 air tap: same shape (turn via dc20), no bleed.
    {402,-1,0,11,MoveOp::Turn,20.f},
    voice_rule(402,-1,12,12,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,4)),
    {402,-1,12,12,MoveOp::Launch,1.f,0.f,40.f,kGateNormal},
    {402,-1,12,12,MoveOp::Launch,0.f,0.f,40.f,kGateNormal},
    {402,-1,12,12,MoveOp::Launch,3.f,0.f,40.f,kGatePowered},
    {402,-1,12,12,MoveOp::Launch,2.f,0.f,40.f,kGatePowered},
    {402,-1,12,12,MoveOp::Launch,1.f,0.f,40.f,kGatePowered},
    {402,-1,12,12,MoveOp::Launch,0.f,0.f,40.f,kGatePowered},
    // 450 ground charge1: 10 deg turn through tick 19, bleed 0.25/tick, Hide slot 0
    // ticks 0-21, single salvo row 4 at tick 22.
    {450,-1,0,19,MoveOp::Turn,10.f},
    {450,-1,0,9999,MoveOp::Decelerate,.25f},
    {450,-1,0,21,MoveOp::Hide,0.f},
    voice_rule(450,-1,22,22,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {450,-1,22,22,MoveOp::Launch,4.f,0.f,30.f,kGateNormal},
    {450,-1,22,22,MoveOp::Launch,5.f,0.f,30.f,kGatePowered},
    // 460 air charge1: 15 deg turn through tick 14, Hide slot 0 ticks 0-16,
    // single salvo row 4 at tick 17.
    {460,-1,0,14,MoveOp::Turn,15.f},
    {460,-1,0,16,MoveOp::Hide,0.f},
    voice_rule(460,-1,17,17,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Equal,1)),
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f,kGateNormal},
    {460,-1,17,17,MoveOp::Launch,5.f,0.f,40.f,kGatePowered},
};
// Rika weapon 0 (handler 0x484be0) — shot rules recovered from the reference bodies
// shoot_body_4_0_{400,402,450,460} (bundle reference/source). The taps fire TWIN world
// requests at tick 15, TWO on item row 0 normally and FOUR on row 1 powered (L18360-18438);
// the charges fire twin world requests at ticks 15 AND 25, row 2 normally and row 3 powered,
// with the pitch thirds 45/30 ground and 45/40 air (L20797-20941). Short freezes at tick 30
// after the salvos (5 updates ground, 15 air). No Hide anywhere.
//
// The requests are WORLD pairs and the geometry is decoded: each is the actor's own position
// displaced `+-50` ALONG THE FACING (`0x42480000`, L18383-18422) at height +70 (`0x428c0000`),
// which is exactly ActorRelativeOffset(0, forward, height) — the port's `facing_relative(0, R)`
// is the same `(sin(facing), cos(facing)) * R`. The `+-50` term multiplies the table evaluated
// at `yaw + 90` (L18365 `0x42b40000`), which is the PERPENDICULAR axis, while the 10 term
// multiplies the `yaw` table: so the pair is `origin_actor_relative(+-50, 10, 70)`, lateral and
// not forward. (The first binding had the axis inverted; a distance check could not tell the
// two apart because either way the pair is 100 apart.) The tap fires +50 then -50 normally and
// +50/-50/+50/-50 powered. The charges fire twin WORLD requests at ticks 15 and 25 with
// lateral `+-25` (`0x41c80000`), forward 50 (`0x42480000` on the `yaw` table) and height +50,
// and they pass an explicit world yaw and pitch instead of the target elevation: yaw `+-5` with
// pitch 45 at tick 15, and yaw `+-10` with pitch 30 (450) / 40 (460) at tick 25 — the `uVar14`
// assignments. Earlier notes gave the radius as 600 and 50, which was a mis-read of the hex.
//
// The powered branches test `byte(+0x845) && word(+0x212)` — kGatePowered, the idiom the
// rest of the port uses — which the previous binding recorded as "no flag field, skipped".
// The `w[0x1b7] < 3` beside it only picks the sound.
inline constexpr MoveRule kRika0Rules[] = {
    // 400 ground tap: 15 deg turn ticks 0-14, bleed 0.5/tick phase 0, twin row 0 @15.
    {400,-1,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(400,-1,15,15,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(50.f,10.f,70.f),aim_target_elevation(40.f)},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,10.f,70.f),aim_target_elevation(40.f)},
    {400,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(50.f,10.f,70.f),aim_target_elevation(40.f)},
    {400,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,10.f,70.f),aim_target_elevation(40.f)},
    {400,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(50.f,10.f,70.f),aim_target_elevation(40.f)},
    {400,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,10.f,70.f),aim_target_elevation(40.f)},
    // 402 air tap: 20 deg turn ticks 0-14, same twin @15. No bleed (gravity tail).
    {402,-1,0,14,MoveOp::Turn,20.f},
    voice_rule(402,-1,15,15,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(50.f,10.f,70.f),aim_target_elevation(40.f)},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,10.f,70.f),aim_target_elevation(40.f)},
    {402,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(50.f,10.f,70.f),aim_target_elevation(40.f)},
    {402,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,10.f,70.f),aim_target_elevation(40.f)},
    {402,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(50.f,10.f,70.f),aim_target_elevation(40.f)},
    {402,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,10.f,70.f),aim_target_elevation(40.f)},
    // 450 ground charge1: 18 deg turn through tick 9, bleed 0.5/tick, twin row-2
    // salvos at 15 (±5°) and 25 (±10°), freeze 5 at tick 30.
    {450,-1,0,9,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(450,-1,15,15,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,5)),
    {450,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-5.f,45.f)},
    {450,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(5.f,45.f)},
    {450,-1,15,15,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-5.f,45.f)},
    {450,-1,15,15,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(5.f,45.f)},
    {450,-1,25,25,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-10.f,30.f)},
    {450,-1,25,25,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(10.f,30.f)},
    {450,-1,25,25,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-10.f,30.f)},
    {450,-1,25,25,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(10.f,30.f)},
    {450,-1,30,30,MoveOp::Hold,5.f},
    // 460 air charge1: same salvos (third 45 @15, 40 @25), freeze 15 at tick 30.
    // No bleed (one-shot halve + gravity tail skipped).
    {460,-1,0,9,MoveOp::Turn,18.f},
    voice_rule(460,-1,15,15,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,5)),
    {460,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-5.f,45.f)},
    {460,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(5.f,45.f)},
    {460,-1,15,15,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-5.f,45.f)},
    {460,-1,15,15,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(5.f,45.f)},
    {460,-1,25,25,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-10.f,40.f)},
    {460,-1,25,25,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(10.f,40.f)},
    {460,-1,25,25,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-25.f,50.f,50.f),aim_fixed_angles(-10.f,40.f)},
    {460,-1,25,25,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(25.f,50.f,50.f),aim_fixed_angles(10.f,40.f)},
    {460,-1,30,30,MoveOp::Hold,15.f},
};
// Rika weapon 2 (handler 0x49d890) — shot rules recovered from the reference bodies
// shoot_body_4_2_{400,402,450,460} (bundle reference/source). Single-tick tap at tick
// 15 (both ground and air) with a same-tick Hold 30; triple fans at tick 10 in both
// charges — row 4 normally and row 6 powered (L25648-25700), also with same-tick Hold 30.
// The launch-latch in the executor keeps each salvo to one firing per tick.
//
// The tag branch note here was WRONG: the row branch tests `byte(+0x845) && word(+0x212)`,
// the same kGatePowered every other family uses — the `w[0x1b7] < 3` beside it picks the
// sound. Reading the body shows the branch is not the only gap
// (L24384-24453):
//   * the NORMAL branch fires ONE hand request whose ROW is selected by `w[0x9e]` (+0x278):
//     row 2 when it is negative, row 0 at zero, row 1 when positive. That word is the AI's
//     own movement decision — only FUN_0043f4d0/FUN_00447730 write it, both COM routines —
//     so a human slot leaves it at 0 and takes row 0, while a COM strafing left or right
//     takes row 2 or row 1. The kGateDir* bits state exactly those three branches, and
//     each carries kGateNormal too — the direction picks the NORMAL branch's row, while the
//     powered branch fires all three regardless;
//   * the TAG branch fires THREE hand requests, rows 0, 2 and 1 in that order, and needs
//     no selector at all — so it is bound here;
//   * every request passes pitch 0 and lateral 0, although scratch 0x3c is filled with
//     the clamped (+-40) target elevation just above and then never used.
// The tap is a `Bip01_R_Hand` request, not an attachment request.
inline constexpr MoveRule kRika2Rules[] = {
    // 400 ground tap: 15 deg turn ticks 0-14, bleed 0.5/tick phase 0, row 0 at 15.
    {400,-1,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    voice_rule(400,-1,15,15,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {400,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal | kGateDirLeft,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateDirNeutral,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {400,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGateNormal | kGateDirRight,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {400,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {400,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {400,-1,15,15,MoveOp::Hold,30.f},
    // 402 air tap: 20 deg turn ticks 0-14, row 0 at 15. No bleed (gravity tail).
    {402,-1,0,14,MoveOp::Turn,20.f},
    voice_rule(402,-1,15,15,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,3)),
    {402,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGateNormal | kGateDirLeft,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGateNormal | kGateDirNeutral,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {402,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGateNormal | kGateDirRight,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {402,-1,15,15,MoveOp::Launch,2.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {402,-1,15,15,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_fixed_angles(0.f,0.f)},
    {402,-1,15,15,MoveOp::Hold,30.f},
    // 450 ground charge1: 18 deg turn through tick 9, bleed 1.5/tick, fan row 4 x3
    // at tick 10.
    {450,-1,0,9,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,1.5f},
    voice_rule(450,-1,10,10,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,4)),
    {450,-1,10,10,MoveOp::Launch,4.f,0.f,40.f,kGateNormal},
    {450,-1,10,10,MoveOp::Launch,4.f,0.f,40.f,kGateNormal},
    {450,-1,10,10,MoveOp::Launch,4.f,0.f,40.f,kGateNormal},
    {450,-1,10,10,MoveOp::Launch,6.f,0.f,40.f,kGatePowered},
    {450,-1,10,10,MoveOp::Launch,6.f,0.f,40.f,kGatePowered},
    {450,-1,10,10,MoveOp::Launch,6.f,0.f,40.f,kGatePowered},
    {450,-1,10,10,MoveOp::Hold,30.f},
    // 460 air charge1: same fan (no bleed — one-shot halve + gravity skipped).
    {460,-1,0,9,MoveOp::Turn,18.f},
    voice_rule(460,-1,10,10,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,4)),
    {460,-1,10,10,MoveOp::Launch,4.f,0.f,40.f,kGateNormal},
    {460,-1,10,10,MoveOp::Launch,4.f,0.f,40.f,kGateNormal},
    {460,-1,10,10,MoveOp::Launch,4.f,0.f,40.f,kGateNormal},
    {460,-1,10,10,MoveOp::Launch,6.f,0.f,40.f,kGatePowered},
    {460,-1,10,10,MoveOp::Launch,6.f,0.f,40.f,kGatePowered},
    {460,-1,10,10,MoveOp::Launch,6.f,0.f,40.f,kGatePowered},
    {460,-1,10,10,MoveOp::Hold,30.f},
};
// Satoko weapon 0 (handler 0x4a9c40) — shot rules recovered from the reference bodies
// shoot_body_3_0_{400,402,450,460} (bundle reference/source). Tap salvos of FIVE row-0
// shots at tick 17, EIGHT powered, each drawing its own pitch and lateral offset off the
// posed hand; charge salvos of TWO row-11
// shots spread by frozen-clock Holds (26 updates @25 for five salvos, 21 for four) —
// the unrolled ticks reproduce the salvo cadence while the Hold reproduces the clock
// freeze, and the per-(rule,phase,tick) launch latch keeps each salvo to one firing.
// Tag row 12, aim ramps, gravity tails and one-shot velocity sets have no MoveRule op.
// Tap thirds share one CapturePitch (+-40) then one repeated Launch per branch, so the
// draws land in the body's order (pitch, then lateral) rather than per unrolled rule.
// The family aim-clamp standard (40): the measured downward pellet bias
// ([-12,-0.05] normal) is ballistics, not aim — it needs projectile gravity (Fase 3+).
inline constexpr MoveRule kSatokoRules[] = {
    // 400 ground tap: turns 10 deg (0-9, phaseless) + 15 deg (phase 0, open),
    // bleed 0.5/tick phase 0, five row-0 shots at tick 17.
    {400,-1,0,9,MoveOp::Turn,10.f},
    {400,0,0,9999,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,17,17,MoveOp::CapturePitch,0.f,40.f,40.f},
    voice_rule(400,-1,17,17,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,6)),
    {400,-1,17,17,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch(),{},kSpreadSatokoFan5,5},
    {400,-1,17,17,MoveOp::Launch,0.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch(),{},kSpreadSatokoFan8,8},
    // 402 air tap: 20 deg turn ticks 0-9, Hide slot 0 from tick 16, same five at 17.
    // No bleed (gravity tail skipped).
    {402,-1,0,9,MoveOp::Turn,20.f},
    {402,-1,16,9999,MoveOp::Hide,0.f},
    {402,-1,17,17,MoveOp::CapturePitch,0.f,40.f,40.f},
    voice_rule(402,-1,17,17,shot_voice(27,30,ShotVoiceMagazine::Primary,
                                       ShotVoiceCompare::Less,6)),
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch(),{},kSpreadSatokoFan5,5},
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch(),{},kSpreadSatokoFan8,8},
    // 450 ground charge1: turns 10 deg (0-24) + 2 deg (0-25), bleed 0.5/tick,
    // 26-tick freeze at 25 with twin row-11 salvos at 25,31,37,43,49.
    {450,-1,0,24,MoveOp::Turn,10.f},
    {450,-1,0,25,MoveOp::Turn,2.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    {450,-1,25,25,MoveOp::Hold,26.f},
    voice_rule(450,-1,25,25,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,5)),
    {450,-1,25,25,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,25,25,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,31,31,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,31,31,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,37,37,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,37,37,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,43,43,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,43,43,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,49,49,MoveOp::Launch,11.f,0.f,40.f},
    {450,-1,49,49,MoveOp::Launch,11.f,0.f,40.f},
    // 460 air charge1: turns 13 deg (0-9) + 5 deg (0-15), 21-tick freeze at 25 with
    // twin salvos at 25,31,37,43. No bleed.
    {460,-1,0,9,MoveOp::Turn,13.f},
    {460,-1,0,15,MoveOp::Turn,5.f},
    {460,-1,25,25,MoveOp::Hold,21.f},
    voice_rule(460,-1,25,25,shot_voice(29,30,ShotVoiceMagazine::Secondary,
                                       ShotVoiceCompare::Less,5)),
    {460,-1,25,25,MoveOp::Launch,11.f,0.f,40.f},
    {460,-1,25,25,MoveOp::Launch,11.f,0.f,40.f},
    {460,-1,31,31,MoveOp::Launch,11.f,0.f,40.f},
    {460,-1,31,31,MoveOp::Launch,11.f,0.f,40.f},
    {460,-1,37,37,MoveOp::Launch,11.f,0.f,40.f},
    {460,-1,37,37,MoveOp::Launch,11.f,0.f,40.f},
    {460,-1,43,43,MoveOp::Launch,11.f,0.f,40.f},
    {460,-1,43,43,MoveOp::Launch,11.f,0.f,40.f},
};
inline const MoveProgram* move_program(const CharacterMoves* moves) {
    const auto* binding = locomotion(moves);
    if (!binding) return nullptr;
    static constexpr MoveProgram rena = {kRenaRules, std::size(kRenaRules),
                                         {{400,402},{450,460},{360,370}},
                                         rena_chase_policy(0), rena_dive_policy(0)};
    // Mion 0's shot rows are recovered (kMionRules above); her second charge has no
    // shoot body in the bundle (no 360/370 for ch1), so it stays unbound (-1) and the
    // provisional magazine-scan path in fire_shot keeps serving it — today's behavior.
    static constexpr MoveProgram mion = {kMionRules, std::size(kMionRules),
                                         {{400,402},{450,460},{-1,-1}}};
    if (binding->handler == 0x4582a0) return &mion;
    // Rika 1: same unbound second charge (no 360/370 body for ch4 in scope).
    static constexpr MoveProgram rika = {kRikaRules, std::size(kRikaRules),
                                         {{400,402},{450,460},{-1,-1}}};
    // Tomitake 2 (handler 0x527880) — shot rules recovered from the reference bodies
    // shoot_body_6_2_{400,402,450,460} (bundle reference/source). Twin shots per tick:
    // rows 7+5 in the tap (row 7 is what the traces record: fire_attachment(0,7,...)),
    // rows 4+0 in the first charge. Registration slots 5/6/7 map to the same rows.
    // No Hide rules (prop semantics illegible); tag rows 6/2 have no flag field.
    // 402/460 gravity tails (w0x10 channel, unclamped, can go negative) are vertical
    // physics with no MoveRule op — skipped explicitly, unlike the w0x15 horizontal
    // bleeds below which map to Decelerate with their floor-0 clamp.
    static constexpr MoveProgram tomitake = {kTomitakeRules, std::size(kTomitakeRules),
                                            {{400,402},{450,460},{-1,-1}}};
    // Takano 0: same unbound second charge (no 360/370 body for ch7 in scope).
    static constexpr MoveProgram takano = {kTakanoRules, std::size(kTakanoRules),
                                           {{400,402},{450,460},{-1,-1}}};
    // Keiichi 2: same unbound second charge (bodies 403-412/469 exist but unscoped).
    static constexpr MoveProgram keiichi = {kKeiichiRules, std::size(kKeiichiRules),
                                            {{400,402},{450,460},{-1,-1}}};
    // Rena+2's air tap (the clamped-clock 402 with its landing branches), its air
    // charge 460 and the 350-ground/360-air full-charge pair are bound in
    // kRena2Rules now; the ground full-charge release selects 350 through this
    // map exactly as FUN_0043ded0's charge branch does.
    static constexpr MoveProgram rena2 = {kRena2Rules, std::size(kRena2Rules),
                                          {{400,402},{450,460},{350,360}},
                                          rena_chase_policy(2), nullptr};
    if (binding->handler == 0x438310) return &rena2;
    if (binding->handler == 0x43ffc0) return &rena;
    if (binding->handler == 0x492f70) return &rika;
    // Keiichi 0/1: taps and first charges bound; second charge stays provisional.
    static constexpr MoveProgram keiichi0 = {kKeiichi0Rules, std::size(kKeiichi0Rules),
                                             {{400,402},{450,460},{-1,-1}}};
    static constexpr MoveProgram keiichi1 = {kKeiichi1Rules, std::size(kKeiichi1Rules),
                                             {{400,402},{450,460},{-1,-1}}};
    // Mion 1: taps bound; the repeated-emission charges stay -1 so the provisional path
    // serves them until the draw service lands (see the rule comments).
    static constexpr MoveProgram mion1 = {kMion1Rules, std::size(kMion1Rules),
                                          {{400,402},{450,460},{-1,-1}}};
    if (binding->handler == 0x461810) return &mion1;
    if (binding->handler == 0x46a190) return &keiichi0;
    if (binding->handler == 0x473610) return &keiichi1;
    // Satoko 2 (handler 0x4bc040): the tap pair only. 450/460 stay -1 so the
    // provisional magazine-scan path keeps serving the charges exactly as before,
    // which is the documented pending cell for this combo.
    static constexpr MoveProgram satoko2 = {kSatoko2Rules, std::size(kSatoko2Rules),
                                             {{400,402},{-1,-1},{-1,-1}}};
    if (binding->handler == 0x4bc040) return &satoko2;
    if (binding->handler == 0x527880) return &tomitake;
    if (binding->handler == 0x47b940) return &keiichi;
    // Chie 2: same unbound second charge (no 360/370 body for ch11 in scope).
    static constexpr MoveProgram chie = {kChieRules, std::size(kChieRules),
                                        {{400,402},{450,460},{-1,-1}}};
    // Kasai 1: same unbound second charge (bodies 451-454/469 exist but unscoped).
    static constexpr MoveProgram kasai = {kKasaiRules, std::size(kKasaiRules),
                                          {{400,402},{450,460},{-1,-1}}};
    // Irie 1: same unbound second charge (no 360/370 body for ch10 in scope).
    static constexpr MoveProgram irie = {kIrieRules, std::size(kIrieRules),
                                        {{400,402},{450,460},{-1,-1}}};
    // Mion 2: same unbound second charge (bodies 401-417 exist but unscoped).
    static constexpr MoveProgram mion2 = {kMion2Rules, std::size(kMion2Rules),
                                          {{400,402},{450,460},{-1,-1}}};
    // Rika 2: same unbound second charge (bodies 451-453/461 exist but unscoped).
    static constexpr MoveProgram rika2 = {kRika2Rules, std::size(kRika2Rules),
                                          {{400,402},{450,460},{-1,-1}}};
    // Rika 0: same unbound second charge (bodies 403-414 exist but unscoped).
    static constexpr MoveProgram rika0 = {kRika0Rules, std::size(kRika0Rules),
                                          {{400,402},{450,460},{-1,-1}}};
    // Satoko 0: same unbound second charge (state 401 and bodies 403-409 exist but
    // unscoped).
    static constexpr MoveProgram satoko = {kSatokoRules, std::size(kSatokoRules),
                                           {{400,402},{450,460},{-1,-1}}};
    if (binding->handler == 0x566a40) return &chie;
    if (binding->handler == 0x5b9680) return &kasai;
    if (binding->handler == 0x531ce0) return &takano;
    if (binding->handler == 0x57f600) return &irie;
    if (binding->handler == 0x44fa10) return &mion2;
    if (binding->handler == 0x49d890) return &rika2;
    static constexpr MoveProgram satoko1 = {kSatoko1Rules, std::size(kSatoko1Rules),
                                            {{400,402},{450,460},{-1,-1}}};
    if (binding->handler == 0x4b4090) return &satoko1;
    if (binding->handler == 0x4a9c40) return &satoko;
    // Rena+1's air tap is the three-phase 402 dive and its charges are the 450/460
    // sweep pair and the 360/370 row-8 family — all bound in kRena1Rules now.
    static constexpr MoveProgram rena1 = {kRena1Rules, std::size(kRena1Rules),
                                          {{400,402},{450,460},{360,370}},
                                          rena_chase_policy(1), rena_dive_policy(1)};
    static constexpr MoveProgram natsumi0 = {kNatsumi0Rules, std::size(kNatsumi0Rules),
                                              {{400,-1},{-1,-1},{-1,-1}}};
    if (binding->handler == 0x448220) return &rena1;
    if (binding->handler == 0x5e2af0) return &natsumi0;
    if (binding->handler == 0x484be0) return &rika0;
    return nullptr;
}
} // namespace gameplay
