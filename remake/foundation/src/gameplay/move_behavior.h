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
// Rika weapon 1 (handler 0x492f70) — shot rules recovered from the reference bodies
// shoot_body_4_1_{400,402,450,460} (bundle reference/source). Her tap is a repeating
// schedule, not a single anchor: the bodies fire while (tick>11 && scratch<30) on even
// scratch ticks, i.e. ticks 12,14,...,40 (15 shots; usage matrix agrees per phase).
// Our rule model has no modulo, so the window is written as 15 explicit tick rules —
// verbose but exact; each matches one measured fire tick. Row 0 for the tap window is
// established through the item table (usage slot 0 = registration file 0), not the body
// (whose 004230e0 call carries no row). Charge rows 2/5 (tick 10) and 3/6 (tick 30)
// are explicit in the bodies; aim-only rows 4/7 have no flag field here and are skipped.
// No Hide rules: the prop calls' 2/3/-1 semantics are illegible (bundle RESPONSE §2).
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
    // 450 ground charge1: 18 deg turn through tick 9 (L23485-88).
    {450,-1,0,9,MoveOp::Turn,18.f},
    // 450 twin salvos, no-aim primary branch: rows 2+5 at tick 10 (L23495-548),
    // rows 3+6 at tick 30 (L23549-577); ~30-tick freeze at tick 30 (L23666-70).
    {450,-1,10,10,MoveOp::Launch,2.f,0.f,40.f},
    {450,-1,10,10,MoveOp::Launch,5.f,0.f,40.f},
    {450,-1,30,30,MoveOp::Launch,3.f,0.f,40.f},
    {450,-1,30,30,MoveOp::Launch,6.f,0.f,40.f},
    {450,-1,30,30,MoveOp::Hold,30.f},
    // 460 air charge1: same twin-salvo shape (L23750-803, L23804-832, L23921-24).
    {460,-1,0,9,MoveOp::Turn,18.f},
    {460,-1,10,10,MoveOp::Launch,2.f,0.f,40.f},
    {460,-1,10,10,MoveOp::Launch,5.f,0.f,40.f},
    {460,-1,30,30,MoveOp::Launch,3.f,0.f,40.f},
    {460,-1,30,30,MoveOp::Launch,6.f,0.f,40.f},
    {460,-1,30,30,MoveOp::Hold,30.f},
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
inline constexpr MoveRule kMion2Rules[] = {
    // Mion weapon 2 (handler 0x44fa10): the ground tap fires ONE row-0 shot at
    // entry-tick 10 through a clock jump to 18 (ticks 11-17 never execute) — the
    // frame-18 usage anchor is that same single shot, so no second rule. Charges are
    // 10-shot bursts rows 2 at ticks 15..60 step 5; phase-1 turn, gravity tails and
    // one-shot halves have no MoveRule op and are skipped.
    // 400 ground tap: overlapping turns 15 deg (0-9) + 10 deg (0-18), bleed 1.5/tick
    // through tick 17, single launch row 0 at entry-tick 10, stall 10 at tick 23.
    {400,-1,0,9,MoveOp::Turn,15.f},
    {400,-1,0,18,MoveOp::Turn,10.f},
    {400,-1,0,17,MoveOp::Decelerate,1.5f},
    {400,-1,10,10,MoveOp::Launch,0.f,0.f,40.f},
    {400,-1,23,23,MoveOp::Hold,10.f},
    // 402 air tap: turns 15 deg (0-13) + 10 deg (0-18), single launch row 0 at 18,
    // stall 10 at 23. No bleed (one-shot halve + gravity tail skipped).
    {402,-1,0,13,MoveOp::Turn,15.f},
    {402,-1,0,18,MoveOp::Turn,10.f},
    {402,-1,18,18,MoveOp::Launch,0.f,0.f,40.f},
    {402,-1,23,23,MoveOp::Hold,10.f},
    // 450 ground charge1: 20 deg turn phase 0, bleed 1.5/tick, burst rows 2 at 15..60.
    {450,0,0,9999,MoveOp::Turn,20.f},
    {450,-1,0,9999,MoveOp::Decelerate,1.5f},
    {450,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,20,20,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,25,25,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,30,30,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,35,35,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,40,40,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,45,45,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,50,50,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,55,55,MoveOp::Launch,2.f,0.f,45.f},
    {450,-1,60,60,MoveOp::Launch,2.f,0.f,45.f},
    // 460 air charge1: 20 deg turn phase 0, burst rows 2 at 15..60 (no bleed).
    {460,0,0,9999,MoveOp::Turn,20.f},
    {460,-1,15,15,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,20,20,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,25,25,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,30,30,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,35,35,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,40,40,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,45,45,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,50,50,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,55,55,MoveOp::Launch,2.f,0.f,45.f},
    {460,-1,60,60,MoveOp::Launch,2.f,0.f,45.f},
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
    if (binding->handler == 0x43ffc0) return &rena;
    if (binding->handler == 0x4582a0) return &mion;
    if (binding->handler == 0x492f70) return &rika;
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
    if (binding->handler == 0x484be0) return &rika0;
    return nullptr;
}
} // namespace gameplay
