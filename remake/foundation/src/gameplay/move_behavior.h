#pragma once

#include "gameplay/weapon_definition.h"
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

enum class MoveOp { Speed, Decelerate, Turn, Approach, Launch, Hold, ActionCamera, Hide, Active };
struct MoveRule {
    int move, phase, first, last;
    MoveOp operation;
    float value;
    float second = 0.f;
    float third = 0.f;
};

// Original FUN_0043ffc0. Inclusive tick intervals; phase -1 means all phases.
// Launch.value is an ITEM ROW, never a model number, animation set or magazine.
// Hide/Active are the attachment slot 0..1 operands of FUN_00434a70 and FUN_00434b30: the
// executor re-binds slot0<-prop0 and slot1<-prop1 and deactivates both at the top of every
// frame (0x43fff4/0x440006/0x440014), so Hide lasts only while its ticks keep matching and
// Active must be re-asserted on every tick of its window. Active is also what grows the
// weapon ribbon: FUN_0042fff0 reads the prop's own active latch (prop+0x38), so a tick
// outside the window decays it instead.
inline constexpr MoveRule kNataRules[] = {
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
    // through tick 11 (FUN_0042db10), launch item row 0 at tick 12 (0x4448d6).
    {400,0,0,9999,MoveOp::Decelerate,.5f},
    {400,0,0,11,MoveOp::Turn,20.f},
    {400,-1,12,9999,MoveOp::Hide,0.f},
    {400,-1,12,9999,MoveOp::Hide,1.f},
    {400,0,12,12,MoveOp::Launch,0.f,0.f,30.f},
    // 402 air tap: hide from tick 13 (tick>12), launch item row 1 at tick 13
    // (0x444c7a CMP [this+0xae04],0xd). 400 fires at 12 and 402 at 13.
    {402,-1,13,9999,MoveOp::Hide,0.f},
    {402,-1,13,9999,MoveOp::Hide,1.f},
    {402,0,13,13,MoveOp::Launch,1.f,0.f,30.f},
    // 450 first charge: turn 18 deg through tick 9, launch row 2 at tick 13.
    {450,0,0,9999,MoveOp::Decelerate,.5f},
    {450,0,0,9,MoveOp::Turn,18.f},
    {450,0,13,13,MoveOp::Launch,2.f,0.f,45.f},
    // 460 air charge: turn 18 deg through tick 9, launch row 2 at tick 12.
    {460,0,0,9,MoveOp::Turn,18.f},
    {460,0,12,12,MoveOp::Launch,2.f,0.f,45.f},
    // 360/370 second charge: the ten-update freeze is PHASE 2 tick 13, inside the same
    // phase-2 branch as the tick-2 red launches (360: 0x443aef and 370: 0x443e8b both
    // sit after the 0xadf4==2 gate). Placing it in phase 0 froze the wrong phase.
    {360,-1,0,9999,MoveOp::Decelerate,.75f},
    {360,2,13,13,MoveOp::Hold,10.f},
    {360,2,2,2,MoveOp::Launch,11.f,70.f,40.f},
    {360,2,2,2,MoveOp::Launch,12.f,-70.f,40.f},
    {370,-1,0,9999,MoveOp::Decelerate,.75f},
    {370,2,13,13,MoveOp::Hold,10.f},
    {370,-1,14,9999,MoveOp::Hide,0.f},
    {370,-1,14,9999,MoveOp::Hide,1.f},
    {370,2,2,2,MoveOp::Launch,11.f,70.f,40.f},
    {370,2,2,2,MoveOp::Launch,12.f,-70.f,40.f},
};

struct MoveProgram {
    const MoveRule* rules = nullptr;
    size_t count = 0;
    int shot[3][2]{}; // tap/first/second charge; ground/air
};
// Slot7 jump-cancel facts recovered for the pilot combo only (bundle evidence TSVs,
// runtime == expected): Rena 0 (handler 0x43ffc0) admits jump out of shot move 400 at
// elapsed frame 20 (destination: state 40); elapsed frame 0 has no request. Shot state
// 401 has no binding in this port yet (charge tiers map to 450/460/360/370), and
// 403/409→400 needs recovery states (plan Fase 3), so the table carries exactly the
// verified row. The sampled frame is a lower bound, not a proven window — bundle
// RESPONSE §3: sampled contexts are not exhaustive interval tables.
struct ShotJumpCancel { int move; int frame; };
inline constexpr ShotJumpCancel kPilotShotJumpCancel[] = {{400, 20}};
// Mion weapon 0 (handler 0x4582a0) — shot rules recovered from the reference bodies
// shoot_body_1_0_{400,402,450,460} (bundle reference/source). Phase/turn/hold values are
// measured in the bodies; each rule below cites its lines. Known gaps, not guesses:
// ph3/row-1 second shot has no variant model here (usage variants 1 AND 3 fire, but the
// port cannot select variants — row 0 is the bound primary); slot7 Hide values 2/3/-1
// and slot-1 halves have no MoveRule field (Hide carries slot 0's unbind window only);
// 450's pitch clamp is asymmetric [-40,+45] but the model clamps symmetric (45 kept);
// counter-to-tick in 402 assumes no reset mid-move; speeds live in item data, never here.
inline constexpr MoveRule kMionRules[] = {
    // 400 ground tap: vertical bleed 0.5/tick + 18 deg turn while the scratch gate
    // holds, ~first 10 ticks (body L52-65, not phase-gated).
    {400,-1,0,9,MoveOp::Decelerate,.5f},
    {400,-1,0,9,MoveOp::Turn,18.f},
    // 400 phase turns: 10 deg in phase 1, 5 in phase 3 (L68, L115).
    {400,1,0,9999,MoveOp::Turn,10.f},
    {400,3,0,9999,MoveOp::Turn,5.f},
    // 400 tap fires item row 0 at tick 2 — the usage anchor (phases 1 and 3 fire at
    // frame 2; the phase-1 row is bound, the phase-3 row-1 variant is not modeled).
    // Pitch clamp of phase 1 is +-30 deg.
    {400,-1,2,2,MoveOp::Launch,0.f,0.f,30.f},
    // 402 air tap: counter-gated turns, 20 deg then 5 past counter 15 (L340-347).
    {402,-1,0,24,MoveOp::Turn,20.f},
    {402,-1,15,24,MoveOp::Turn,5.f},
    // 402 emits rows 0 AND 1 together at counter 15/20/25 (~ticks 14/19/24, L381-396;
    // the only body with a double 004230e0 call). Pitch clamp +-40 deg.
    {402,-1,14,14,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,14,14,MoveOp::Launch,1.f,0.f,40.f},
    {402,-1,19,19,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,19,19,MoveOp::Launch,1.f,0.f,40.f},
    {402,-1,24,24,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,24,24,MoveOp::Launch,1.f,0.f,40.f},
    // 450 ground charge1: 25 deg turn through tick 16 (L1664-1667, highest of the four).
    {450,-1,0,16,MoveOp::Turn,25.f},
    // 450 prop hide: slot 0 unbound ticks 0-47, rebound after (L1672-1686).
    {450,-1,0,47,MoveOp::Hide,0.f},
    // 450 fires item row 0 at tick 17 (L1695-1725).
    {450,-1,17,17,MoveOp::Launch,0.f,0.f,45.f},
    // 450 freeze: ~30-tick stall at tick 23 (L1727-1731).
    {450,-1,23,23,MoveOp::Hold,30.f},
    // 460 air charge1: 15 deg turn through tick 14 (L2284-2287).
    {460,-1,0,14,MoveOp::Turn,15.f},
    // 460 prop hide: slot 0 unbound ticks 0-50 (L2288-2302).
    {460,-1,0,50,MoveOp::Hide,0.f},
    // 460 fires item row 0 at tick 17 (L2305-2336, symmetric clamp +-40).
    {460,-1,17,17,MoveOp::Launch,0.f,0.f,40.f},
    // 460 freeze: ~20-tick stall at tick 23 (L2340-2344).
    {460,-1,23,23,MoveOp::Hold,20.f},
};
inline const MoveProgram* move_program(const CharacterMoves* moves) {
    const auto* binding = locomotion(moves);
    if (!binding) return nullptr;
    static constexpr MoveProgram nata = {kNataRules, std::size(kNataRules),
                                         {{400,402},{450,460},{360,370}}};
    // Mion 0's shot rows are recovered (kMionRules above); her second charge has no
    // shoot body in the bundle (no 360/370 for ch1), so it stays unbound (-1) and the
    // provisional magazine-scan path in fire_shot keeps serving it — today's behavior.
    static constexpr MoveProgram mion = {kMionRules, std::size(kMionRules),
                                         {{400,402},{450,460},{-1,-1}}};
    if (binding->handler == 0x43ffc0) return &nata;
    if (binding->handler == 0x4582a0) return &mion;
    return nullptr;
}
} // namespace gameplay
