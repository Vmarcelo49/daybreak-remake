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
};

enum class MoveOp { Speed, Decelerate, Turn, Approach, Launch, Hold, ActionCamera, Hide,
                    Active, Counter, CounterSet, CapturePitch };
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
};

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
    // 400 ground tap: hide from tick 12 (0x444850 JLE on tick<=11), turn 20 deg
    // through tick 11 (FUN_0042db10), launch item row 0 at tick 12 (0x4448d6) normally
    // and row 6 powered (FUN_00434fd0 branch on byte 0x845/word 0x848). Slot-0
    // attachment in both halves; the pitch scratch (±30) is read back same-tick.
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,0,0,11,MoveOp::Turn,20.f},
    {400,-1,12,9999,MoveOp::Hide,0.f},
    {400,-1,12,9999,MoveOp::Hide,1.f},
    {400,0,12,12,MoveOp::Launch,0.f,0.f,30.f,kGateNormal},
    {400,0,12,12,MoveOp::Launch,6.f,0.f,30.f,kGatePowered},
    // 402 air tap: hide from tick 13 (tick>12), launch item row 1 at tick 13
    // (0x444c7a CMP [this+0xae04],0xd) normally and row 7 powered (case 0x192).
    {402,-1,13,9999,MoveOp::Hide,0.f},
    {402,-1,13,9999,MoveOp::Hide,1.f},
    {402,0,13,13,MoveOp::Launch,1.f,0.f,30.f,kGateNormal},
    {402,0,13,13,MoveOp::Launch,7.f,0.f,30.f,kGatePowered},
    // 450 first charge: turn 18 deg through tick 9, launch row 2 at tick 13 (case
    // 0x1c2) normally and row 8 powered, both at FIXED pitch 45 (0x42340000 constant,
    // not the scratch). Typed aim carries the constant; the origin stays slot-0.
    {450,0,0,9999,MoveOp::Decelerate,.5f},
    {450,0,0,9,MoveOp::Turn,18.f},
    {450,0,13,13,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    {450,0,13,13,MoveOp::Launch,8.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    // 460 air charge: turn 18 deg through tick 9, launch row 2 at tick 12 (case 0x1cc)
    // normally and row 8 powered, same fixed 45 pitch.
    {460,0,0,9,MoveOp::Turn,18.f},
    {460,0,12,12,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    {460,0,12,12,MoveOp::Launch,8.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    // 360/370 second charge: the ten-update freeze is PHASE 2 tick 13, inside the same
    // phase-2 branch as the tick-2 red launches (360: 0x443aef and 370: 0x443e8b both
    // sit after the 0xadf4==2 gate). Placing it in phase 0 froze the wrong phase. The
    // freeze is counter-gated (0x3e init at phase0/tick0, +1 per frozen update, return
    // while <10), not a plain hold — same model as Rika's, shorter interval.
    {360,-1,0,9999,MoveOp::Decelerate,.75f},
    {360,0,0,0,MoveOp::CounterSet,0.f},
    {360,2,2,2,MoveOp::Launch,11.f,70.f,40.f},
    {360,2,2,2,MoveOp::Launch,12.f,-70.f,40.f},
    {360,2,13,13,MoveOp::Counter,1.f},
    {360,2,13,13,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,10},
    {370,-1,0,9999,MoveOp::Decelerate,.75f},
    {370,0,0,0,MoveOp::CounterSet,0.f},
    {370,2,2,2,MoveOp::Launch,11.f,70.f,40.f},
    {370,2,2,2,MoveOp::Launch,12.f,-70.f,40.f},
    {370,2,13,13,MoveOp::Counter,1.f},
    {370,2,13,13,MoveOp::Hold,9999.f,0.f,0.f,kGateCounterBelow,10},
    {370,-1,14,9999,MoveOp::Hide,0.f},
    {370,-1,14,9999,MoveOp::Hide,1.f},
};

// Rena weapon 1 (handler 0x448220): the full body is absent from the non-Rena
// body header, so use the separately verified runtime-source helper
// (battle_rena_ground_shot.hpp / battle_rena_mobile_shooting.hpp).
//   state400: `if(f>11&&f<27){scratch_e8+=4;scratch_ec=e8-5+draw()%10; bullet(special?3:1,yaw=ec-30,0)}`
//   — one request per frame 12..26, a 15-shot fan. The COUNT and ROW SPLIT are
//   representable; the per-shot yaw `scratch_ec-30` and the `draw()%10` pitch are not,
//   because there is no per-tick draw service. The rules therefore fire the right
//   number of the right rows on the right frames with the default aim — a documented
//   approximation, not a claim of spread parity.
//   state450: `bullet(special?8:2,0,45)` at frame 13 — a single fixed-pitch attachment
//   shot, both branches representable.
//   state402: grounded phase jump plus a phase-2 frame-5 bullet, plus 460 air.
//   360/370 and 460: no evidence in the runtime source — stay unbound.
inline constexpr MoveRule kRena1Rules[] = {
    // 400 ground tap: one request per frame 12..26, row 1 normal / 3 powered. The
    // fan's spread needs the draw service above, so each shares the default aim.
    {400,0,12,26,MoveOp::Launch,1.f,0.f,0.f,kGateNormal},
    {400,0,12,26,MoveOp::Launch,3.f,0.f,0.f,kGatePowered},
    // 450 charge: single fixed-45 attachment shot at frame 13.
    {450,0,13,13,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
    {450,0,13,13,MoveOp::Launch,8.f,0.f,0.f,kGatePowered,0,
     ShotOriginSpec{},aim_fixed_angles(0.f,45.f)},
};

// Rena weapon 2 (handler 0x438310) — no shoot_body_0_2_* exists in either body header,
// so the handler is the only source (FUN_00438310.c:1729-1800). State 400's phase 1
// fires at tick 35 (0x23) as ONE slot-0 attachment request at fixed angles (rows 0/2)
// followed by a TEN-iteration world ring: rows 1/3, 200 forward and +30 high, each
// iteration drawing its own pitch (`rand%30 + 20`) and yaw (`heading + offset + 90 -
// rand%180`). The ring's pitch is absolute and its yaw is the helper's legacy basis, so
// the rules latch a ZERO pitch base and let the spread supply the whole pitch.
inline constexpr MoveRule kRena2Rules[] = {
    // Phase 0: 10 deg turn while tick under 20 (L1739-1741) and a 2.5 vertical bleed
    // (L1742-1745). The bleed has no MoveOp and stays a recorded gap.
    {400,0,0,19,MoveOp::Turn,10.f},
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
};

// Natsumi weapon 0 (handler 0x5e2af0): the normal ground state400 probe is an
// attachment callback for row 0 at tick 14. Both props are cleared before that callback;
// reassert Hide at the firing tick to select the native bone-origin fallback. This pins only
// the request schedule, not the raw flag, admission/geometry or natural phase reachability.
// State 402 makes an analogous raw call but lacks a normalized callback trace, so stays
// unbound rather than promoting a body-pattern inference to a confirmed air row.
inline constexpr MoveRule kNatsumi0Rules[] = {
    {400,-1,14,9999,MoveOp::Hide,0.f},
    {400,-1,14,9999,MoveOp::Hide,1.f},
    {400,-1,14,14,MoveOp::Launch,0.f,0.f,30.f},
};

struct MoveProgram {
    const MoveRule* rules = nullptr;
    size_t count = 0;
    int shot[3][2]{}; // tap/first/second charge; ground/air
};
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
    {450,-1,17,17,MoveOp::CapturePitch,0.f,45.f,45.f},
    {450,-1,17,17,MoveOp::Launch,1.f,0.f,0.f,kGateNormal,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadBurstJitter,15},
    {450,-1,17,17,MoveOp::Launch,5.f,0.f,0.f,kGatePowered,0,
     origin_attachment_slot(0),aim_stored_pitch(),{},kSpreadBurstJitter,15},
    // 460 air charge: 20 deg turn to tick 16, same burst. The clamp is the compare/assign
    // mismatch — the body tests +-30 and writes +-45 (L4330-4337) — so the snap bound
    // carries it.
    {460,-1,0,16,MoveOp::Turn,20.f},
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
// schedule, not a single anchor: the bodies fire while (tick>11 && scratch<30) on even
// scratch ticks, i.e. ticks 12,14,...,40 (15 shots; usage matrix agrees per phase).
// A counter gate would express that window directly; the 15 explicit tick rules are
// kept because they are already verified and the window's counter starts at tick 12,
// not at move entry. Row 0 for the tap window is established through the item table
// (usage slot 0 = registration file 0), not the body (whose 004230e0 call carries no
// row). The charges' tick-10 pair (rows 2/5) fires in BOTH branches; the tick-30 pair
// is rows 3/6 normally and 4/7 powered, counter-gated and repeated by the freeze — see
// the 450 block below for the line citations. No Hide rules: the prop calls' 2/3/-1
// semantics are illegible (bundle RESPONSE §2).
inline constexpr MoveRule kRikaRules[] = {
    // 400 ground tap: 15 deg turn ticks 0-14 (L21764-67), phase-0 bleed (L21768-71).
    {400,-1,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,12,12,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,14,14,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,16,16,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,18,18,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,20,20,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,22,22,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,24,24,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,26,26,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,28,28,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,30,30,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,32,32,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,34,34,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,36,36,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,38,38,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,40,40,MoveOp::Launch,0.f,0.f,40.f},
    // 402 air tap: 20 deg turn ticks 0-14 (L22077-80), same even-tick window (L22086).
    {402,-1,0,14,MoveOp::Turn,20.f},
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
    {400,0,13,13,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,0,13,13,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {400,0,13,13,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // 402 air tap: 20 deg movement-preserving turn through tick 13, movement cleared
    // at tick 0 and gravity applied (no MoveRule ops — explicit gaps). Same tick-13
    // hand request with the snapped pitch.
    {402,-1,0,13,MoveOp::Turn,20.f},
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
    {400,0,13,13,MoveOp::CapturePitch,0.f,30.f,30.f},
    {400,0,13,13,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {400,0,13,13,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // 402 air tap: 20 deg movement-preserving turn through tick 13 (movement clear
    // and gravity are explicit gaps). Same hand request with the snapped pitch.
    {402,-1,0,13,MoveOp::Turn,20.f},
    {402,0,13,13,MoveOp::CapturePitch,45.f,30.f,30.f},
    {402,0,13,13,MoveOp::Launch,0.f,0.f,0.f,kGateNormal,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    {402,0,13,13,MoveOp::Launch,1.f,0.f,0.f,kGatePowered,0,
     origin_named_bone("Bip01_R_Hand"),aim_stored_pitch()},
    // 450 ground charge: 18 deg turn through tick 19, bleed 0.5. Tick-20 world pair
    // (L10004-10093).
    {450,-1,0,19,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    {450,0,20,20,MoveOp::Launch,9.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range()},
    {450,0,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range()},
    {450,0,20,20,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,0.f,40.f),aim_elevation_plus_range()},
    // 460 air charge: 18 deg movement-preserving turn through tick 19 (entry halve
    // and gravity are explicit gaps). Same pair at height +20.
    {460,-1,0,19,MoveOp::Turn,18.f},
    {460,0,20,20,MoveOp::Launch,9.f,0.f,0.f,kGateNone,0,
     origin_actor_relative(-50.f,0.f,20.f),aim_elevation_plus_range()},
    {460,0,20,20,MoveOp::Launch,2.f,0.f,0.f,kGateNormal,0,
     origin_actor_relative(-50.f,0.f,20.f),aim_elevation_plus_range()},
    {460,0,20,20,MoveOp::Launch,3.f,0.f,0.f,kGatePowered,0,
     origin_actor_relative(-50.f,0.f,20.f),aim_elevation_plus_range()},
};

// Tomitake weapon 2 (handler 0x527880) — shot rules recovered from the reference bodies
// shoot_body_6_2_{400,402,450,460} (bundle reference/source). Twin shots per scheduled
// tick: rows 7+5 in the tap (row 7 is what the traces record: fire_attachment(0,7,...);
// usage slots 5 normal / 6 tag / 7 both map to the same rows), rows 4+0 in the first
// charge (tag rows 6/2 need an aim/tag flag this model has no field for — skipped with
// the same precedent as Mion's row-1 variant). The tap schedule (ticks 15..33 step 3)
// is written tick-explicit like Rika's: our rule model has no modulo.
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
    {400,-1,15,15,MoveOp::Launch,7.f,0.f,45.f},
    {400,-1,15,15,MoveOp::Launch,5.f,0.f,45.f},
    {400,-1,18,18,MoveOp::Launch,7.f,0.f,45.f},
    {400,-1,18,18,MoveOp::Launch,5.f,0.f,45.f},
    {400,-1,21,21,MoveOp::Launch,7.f,0.f,45.f},
    {400,-1,21,21,MoveOp::Launch,5.f,0.f,45.f},
    {400,-1,24,24,MoveOp::Launch,7.f,0.f,45.f},
    {400,-1,24,24,MoveOp::Launch,5.f,0.f,45.f},
    {400,-1,27,27,MoveOp::Launch,7.f,0.f,45.f},
    {400,-1,27,27,MoveOp::Launch,5.f,0.f,45.f},
    {400,-1,30,30,MoveOp::Launch,7.f,0.f,45.f},
    {400,-1,30,30,MoveOp::Launch,5.f,0.f,45.f},
    {400,-1,33,33,MoveOp::Launch,7.f,0.f,45.f},
    {400,-1,33,33,MoveOp::Launch,5.f,0.f,45.f},
    // 402 air tap: disjoint turns 15 deg (0-9) + 5 deg (10-24), same twin schedule.
    {402,-1,0,9,MoveOp::Turn,15.f},
    {402,-1,10,24,MoveOp::Turn,5.f},
    {402,-1,15,15,MoveOp::Launch,7.f,0.f,45.f},
    {402,-1,15,15,MoveOp::Launch,5.f,0.f,45.f},
    {402,-1,18,18,MoveOp::Launch,7.f,0.f,45.f},
    {402,-1,18,18,MoveOp::Launch,5.f,0.f,45.f},
    {402,-1,21,21,MoveOp::Launch,7.f,0.f,45.f},
    {402,-1,21,21,MoveOp::Launch,5.f,0.f,45.f},
    {402,-1,24,24,MoveOp::Launch,7.f,0.f,45.f},
    {402,-1,24,24,MoveOp::Launch,5.f,0.f,45.f},
    {402,-1,27,27,MoveOp::Launch,7.f,0.f,45.f},
    {402,-1,27,27,MoveOp::Launch,5.f,0.f,45.f},
    {402,-1,30,30,MoveOp::Launch,7.f,0.f,45.f},
    {402,-1,30,30,MoveOp::Launch,5.f,0.f,45.f},
    {402,-1,33,33,MoveOp::Launch,7.f,0.f,45.f},
    {402,-1,33,33,MoveOp::Launch,5.f,0.f,45.f},
    // 450 ground charge1: turns 35 deg (0-4) + 0.3 deg (0-29), bleed 1.5/tick,
    // single salvo rows 4+0 at tick 30 after a 15-tick freeze at tick 28.
    {450,-1,0,4,MoveOp::Turn,35.f},
    {450,-1,0,29,MoveOp::Turn,0.3f},
    {450,-1,0,9999,MoveOp::Decelerate,1.5f},
    {450,-1,28,28,MoveOp::Hold,15.f},
    {450,-1,30,30,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,30,30,MoveOp::Launch,0.f,0.f,40.f},
    // 460 air charge1: same shape (no w0x15 bleed of its own — skipped, see above).
    {460,-1,0,4,MoveOp::Turn,35.f},
    {460,-1,0,29,MoveOp::Turn,0.3f},
    {460,-1,28,28,MoveOp::Hold,15.f},
    {460,-1,30,30,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,30,30,MoveOp::Launch,0.f,0.f,40.f},
};
// Keiichi weapon 2 (handler 0x47b940) — shot rules recovered from the reference bodies
// shoot_body_2_2_{400,402,450,460} (bundle reference/source). Dense burst, a fourth
// shape: the tap fires EVERY tick 10..20 (11 consecutive frames, rows 0 normal / 1 tag),
// expressed as one window rule per row — the executor runs matching rules each update,
// so first/last IS the burst (unlike Rika's even-only schedule, which needs tick rules).
// Tag row 1 has no flag field: only the normal row 0 is bound (Mion/Rika/Tomitake
// precedent). Charge rows 2 normal / 3 tag likewise bind row 2 only. Turn verbs db10
// vs dc20 both map to Turn by value (distinction illegible); the w0x10 gravity tails
// and the one-shot w0x15 halve are vertical physics with no MoveRule op — skipped.
inline constexpr MoveRule kKeiichiRules[] = {
    // 400 ground tap: 20 deg turn phase 0 ticks 0-11, bleed 0.5/tick phase 0 open-ended.
    {400,0,0,11,MoveOp::Turn,20.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,10,20,MoveOp::Launch,0.f,0.f,30.f},
    // 402 air tap: same window, turn without phase gate, no bleed.
    {402,-1,0,11,MoveOp::Turn,20.f},
    {402,-1,10,20,MoveOp::Launch,0.f,0.f,30.f},
    // 450 ground charge1: 18 deg turn through tick 12, bleed 0.75/tick, single salvo
    // row 2 at tick 13, clock-rewind stalls +10f at tick 5 and +15f at tick 32 (Hold
    // rules; the per-rule latch in the executor gives each stall its full length).
    {450,-1,0,12,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.75f},
    {450,-1,5,5,MoveOp::Hold,10.f},
    {450,-1,13,13,MoveOp::Launch,2.f,0.f,50.f},
    {450,-1,32,32,MoveOp::Hold,15.f},
    // 460 air charge1: same shape (turn 18, salvo row 2 at 13, stalls at 5/32).
    {460,-1,0,12,MoveOp::Turn,18.f},
    {460,-1,13,13,MoveOp::Launch,2.f,0.f,50.f},
    {460,-1,5,5,MoveOp::Hold,10.f},
    {460,-1,32,32,MoveOp::Hold,15.f},
};
// Chie weapon 2 (handler 0x566a40) — shot rules recovered from the reference bodies
// shoot_body_11_2_{400,402,450,460} (bundle reference/source). Tap bursts run on a
// scratch counter (1 at burst start, fire while scratch%3==1): 400 fires ticks
// 15,18,21,24, 402 fires 17,20,23,26,29 — row 0 normal / 1 tag, only the normal row
// bound (no flag field). Single salvos row 2 at tick 22 (450, pitch fixed 0) and
// tick 15 (460). Turn windows and the phase-0/unconditional bleeds are measured per
// body; gravity tails and the aim pitch ramp have no MoveRule op and are skipped.
inline constexpr MoveRule kChieRules[] = {
    // 400 ground tap: 15 deg turn phase 0 ticks 0-14, bleed 0.5/tick phase 0.
    {400,0,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,18,18,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,21,21,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,24,24,MoveOp::Launch,0.f,0.f,40.f},
    // 402 air tap: 20 deg turn ticks 0-16 (no phase gate), same burst shape at 17+.
    {402,-1,0,16,MoveOp::Turn,20.f},
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,20,20,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,23,23,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,26,26,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,29,29,MoveOp::Launch,0.f,0.f,40.f},
    // 450 ground charge1: 18 deg turn through tick 19, bleed 0.5/tick unconditional,
    // single salvo row 2 at tick 22.
    {450,-1,0,19,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    {450,-1,22,22,MoveOp::Launch,2.f,0.f,30.f},
    // 460 air charge1: 18 deg turn through tick 24, single salvo row 2 at tick 15.
    {460,-1,0,24,MoveOp::Turn,18.f},
    {460,-1,22,22,MoveOp::Launch,2.f,0.f,30.f},
};
// Takano weapon 0 (handler 0x531ce0) — shot rules recovered from the reference bodies
// shoot_body_7_0_{400,402,450,460} (bundle reference/source). Double turn in the tap
// (10 deg ticks 0-17 phaseless + 15 deg phase-0 open) with a phase-0 bleed; three
// single shots row 0 at ticks 12,15,18 (tag row 6 skipped — no flag field). Single
// salvos row 1 at tick 18 (450) and tick 17 (460) with slot-0 Hide windows (10-17 and
// 0-16); the slot1→2 half has no field. No Hold anywhere; gravity tails skipped.
inline constexpr MoveRule kTakanoRules[] = {
    // 400 ground tap: turns 10 deg (0-17) + 15 deg (phase 0), bleed 0.5 phase 0.
    {400,-1,0,17,MoveOp::Turn,10.f},
    {400,0,0,9999,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,12,12,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,18,18,MoveOp::Launch,0.f,0.f,40.f},
    // 402 air tap: turn 20 deg ticks 0-17, same triple row 0 (no bleed — gravity tail).
    {402,-1,0,17,MoveOp::Turn,20.f},
    {402,-1,12,12,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,18,18,MoveOp::Launch,0.f,0.f,40.f},
    // 450 ground charge1: turn 20 deg through tick 16, Hide slot 0 ticks 10-17,
    // single salvo row 1 at tick 18.
    {450,-1,0,16,MoveOp::Turn,20.f},
    {450,-1,10,17,MoveOp::Hide,0.f},
    {450,-1,18,18,MoveOp::Launch,1.f,0.f,40.f},
    // 460 air charge1: turn 15 deg through tick 14, Hide slot 0 ticks 0-16,
    // single salvo row 1 at tick 17.
    {460,-1,0,14,MoveOp::Turn,15.f},
    {460,-1,0,16,MoveOp::Hide,0.f},
    {460,-1,17,17,MoveOp::Launch,1.f,0.f,40.f},
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
    {400,-1,10,10,MoveOp::Launch,2.f,0.f,45.f},
    {400,-1,10,10,MoveOp::Launch,0.f,0.f,45.f},
    {400,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,45.f},
    // 402 air tap: 15 deg turn ticks 0-9, 5 deg ticks 10-24, same twin salvos.
    {402,-1,0,9,MoveOp::Turn,15.f},
    {402,-1,10,24,MoveOp::Turn,5.f},
    {402,-1,10,10,MoveOp::Launch,2.f,0.f,45.f},
    {402,-1,10,10,MoveOp::Launch,0.f,0.f,45.f},
    {402,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,45.f},
    // 450 ground charge1: 20 deg turn through tick 9, fan of four row-4 at tick 18.
    {450,-1,0,9,MoveOp::Turn,20.f},
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,18,18,MoveOp::Launch,4.f,0.f,40.f},
    // 460 air charge1: 15 deg turn through tick 11, fan of four row-4 at tick 17.
    {460,-1,0,11,MoveOp::Turn,15.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
};
// Irie weapon 1 (handler 0x57f600) — shot rules recovered from the reference bodies
// shoot_body_10_1_{400,402,450,460} (bundle reference/source). Twin rows 0+1 at tick 12
// in both taps (tag adds rows 2+3 — no flag field, skipped); single salvos row 4 at
// tick 22 (450) and tick 17 (460). Hide windows carry slot 0 only (slot-1 halves have
// no field). Gravity tails and one-shot velocity sets have no MoveRule op — skipped.
inline constexpr MoveRule kIrieRules[] = {
    // 400 ground tap: 20 deg turn ticks 0-11, bleed 0.5/tick, twin rows 0+1 at 12.
    {400,-1,0,11,MoveOp::Turn,20.f},
    {400,-1,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,12,12,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,12,12,MoveOp::Launch,1.f,0.f,40.f},
    // 402 air tap: same shape (turn via dc20), no bleed.
    {402,-1,0,11,MoveOp::Turn,20.f},
    {402,-1,12,12,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,12,12,MoveOp::Launch,1.f,0.f,40.f},
    // 450 ground charge1: 10 deg turn through tick 19, bleed 0.25/tick, Hide slot 0
    // ticks 0-21, single salvo row 4 at tick 22.
    {450,-1,0,19,MoveOp::Turn,10.f},
    {450,-1,0,9999,MoveOp::Decelerate,.25f},
    {450,-1,0,21,MoveOp::Hide,0.f},
    {450,-1,22,22,MoveOp::Launch,4.f,0.f,30.f},
    // 460 air charge1: 15 deg turn through tick 14, Hide slot 0 ticks 0-16,
    // single salvo row 4 at tick 17.
    {460,-1,0,14,MoveOp::Turn,15.f},
    {460,-1,0,16,MoveOp::Hide,0.f},
    {460,-1,17,17,MoveOp::Launch,4.f,0.f,40.f},
};
// Rika weapon 0 (handler 0x484be0) — shot rules recovered from the reference bodies
// shoot_body_4_0_{400,402,450,460} (bundle reference/source). Twin row-0 shots at tick
// 15 in both taps (tag fires four — no flag field, skipped); twin row-2 salvos at
// ticks 15 AND 25 in both charges (pitch thirds 45/30 ground, 45/40 air — the only
// numeric emission difference between the charges); short freezes at tick 30 after
// the salvos (5 updates ground, 15 air). No Hide anywhere.
inline constexpr MoveRule kRika0Rules[] = {
    // 400 ground tap: 15 deg turn ticks 0-14, bleed 0.5/tick phase 0, twin row 0 @15.
    {400,-1,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    // 402 air tap: 20 deg turn ticks 0-14, same twin @15. No bleed (gravity tail).
    {402,-1,0,14,MoveOp::Turn,20.f},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    // 450 ground charge1: 18 deg turn through tick 9, bleed 0.5/tick, twin row-2
    // salvos at 15 (±5°) and 25 (±10°), freeze 5 at tick 30.
    {450,-1,0,9,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    {450,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,25,25,MoveOp::Launch,2.f,0.f,30.f},
    {450,-1,25,25,MoveOp::Launch,2.f,0.f,30.f},
    {450,-1,30,30,MoveOp::Hold,5.f},
    // 460 air charge1: same salvos (third 45 @15, 40 @25), freeze 15 at tick 30.
    // No bleed (one-shot halve + gravity tail skipped).
    {460,-1,0,9,MoveOp::Turn,18.f},
    {460,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,25,25,MoveOp::Launch,2.f,0.f,40.f},
    {460,-1,25,25,MoveOp::Launch,2.f,0.f,40.f},
    {460,-1,30,30,MoveOp::Hold,15.f},
};
// Rika weapon 2 (handler 0x49d890) — shot rules recovered from the reference bodies
// shoot_body_4_2_{400,402,450,460} (bundle reference/source). Single-tick tap (row 0
// at tick 15, both ground and air) with a same-tick Hold 30; triple row-4 fans at
// tick 10 in both charges, also with same-tick Hold 30. Tag branches (extra shots,
// row 6, asymmetric counts) have no flag field — skipped with the usual precedent.
// The launch-latch in the executor keeps each salvo to one firing per tick.
inline constexpr MoveRule kRika2Rules[] = {
    // 400 ground tap: 15 deg turn ticks 0-14, bleed 0.5/tick phase 0, row 0 at 15.
    {400,-1,0,14,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,15,15,MoveOp::Hold,30.f},
    // 402 air tap: 20 deg turn ticks 0-14, row 0 at 15. No bleed (gravity tail).
    {402,-1,0,14,MoveOp::Turn,20.f},
    {402,-1,15,15,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,15,15,MoveOp::Hold,30.f},
    // 450 ground charge1: 18 deg turn through tick 9, bleed 1.5/tick, fan row 4 x3
    // at tick 10.
    {450,-1,0,9,MoveOp::Turn,18.f},
    {450,-1,0,9999,MoveOp::Decelerate,1.5f},
    {450,-1,10,10,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,10,10,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,10,10,MoveOp::Launch,4.f,0.f,40.f},
    {450,-1,10,10,MoveOp::Hold,30.f},
    // 460 air charge1: same fan (no bleed — one-shot halve + gravity skipped).
    {460,-1,0,9,MoveOp::Turn,18.f},
    {460,-1,10,10,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,10,10,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,10,10,MoveOp::Launch,4.f,0.f,40.f},
    {460,-1,10,10,MoveOp::Hold,30.f},
};
// Satoko weapon 0 (handler 0x4a9c40) — shot rules recovered from the reference bodies
// shoot_body_3_0_{400,402,450,460} (bundle reference/source). Tap salvos of FIVE row-0
// shots at tick 17 (tag fires 8 — no flag field, skipped); charge salvos of TWO row-11
// shots spread by frozen-clock Holds (26 updates @25 for five salvos, 21 for four) —
// the unrolled ticks reproduce the salvo cadence while the Hold reproduces the clock
// freeze, and the per-(rule,phase,tick) launch latch keeps each salvo to one firing.
// Tag row 12, aim ramps, gravity tails and one-shot velocity sets have no MoveRule op.
// Tap thirds use the family aim-clamp standard (40): the measured downward pellet bias
// ([-12,-0.05] normal) is ballistics, not aim — it needs projectile gravity (Fase 3+).
inline constexpr MoveRule kSatokoRules[] = {
    // 400 ground tap: turns 10 deg (0-9, phaseless) + 15 deg (phase 0, open),
    // bleed 0.5/tick phase 0, five row-0 shots at tick 17.
    {400,-1,0,9,MoveOp::Turn,10.f},
    {400,0,0,9999,MoveOp::Turn,15.f},
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    // 402 air tap: 20 deg turn ticks 0-9, Hide slot 0 from tick 16, same five at 17.
    // No bleed (gravity tail skipped).
    {402,-1,0,9,MoveOp::Turn,20.f},
    {402,-1,16,9999,MoveOp::Hide,0.f},
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    // 450 ground charge1: turns 10 deg (0-24) + 2 deg (0-25), bleed 0.5/tick,
    // 26-tick freeze at 25 with twin row-11 salvos at 25,31,37,43,49.
    {450,-1,0,24,MoveOp::Turn,10.f},
    {450,-1,0,25,MoveOp::Turn,2.f},
    {450,-1,0,9999,MoveOp::Decelerate,.5f},
    {450,-1,25,25,MoveOp::Hold,26.f},
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
                                         {{400,402},{450,460},{360,370}}};
    // Mion 0's shot rows are recovered (kMionRules above); her second charge has no
    // shoot body in the bundle (no 360/370 for ch1), so it stays unbound (-1) and the
    // provisional magazine-scan path in fire_shot keeps serving it — today's behavior.
    static constexpr MoveProgram mion = {kMionRules, std::size(kMionRules),
                                         {{400,402},{450,460},{-1,-1}}};
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
    // Rena 2: state 400 only. The combo has no recovered bodies at all, so nothing is
    // claimed for 402/450/460.
    static constexpr MoveProgram rena2 = {kRena2Rules, std::size(kRena2Rules),
                                          {{400,-1},{-1,-1},{-1,-1}}};
    if (binding->handler == 0x438310) return &rena2;
    if (binding->handler == 0x43ffc0) return &rena;
    if (binding->handler == 0x4582a0) return &mion;
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
    if (binding->handler == 0x4a9c40) return &satoko;
    static constexpr MoveProgram rena1 = {kRena1Rules, std::size(kRena1Rules),
                                          {{400,-1},{450,-1},{-1,-1}}};
    static constexpr MoveProgram natsumi0 = {kNatsumi0Rules, std::size(kNatsumi0Rules),
                                              {{400,-1},{-1,-1},{-1,-1}}};
    if (binding->handler == 0x448220) return &rena1;
    if (binding->handler == 0x5e2af0) return &natsumi0;
    if (binding->handler == 0x484be0) return &rika0;
    return nullptr;
}
} // namespace gameplay
