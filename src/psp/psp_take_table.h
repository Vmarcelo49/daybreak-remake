#pragma once
// Which PSP motion take a PC move plays, per PSP fighter (issue #91, docs/psp/COMBAT.md §3.1).
//
// A PSP fighter runs its dispatch combo's recovered rows, and those rows name PC animation sets.
// A PC set is one *phase* of a move and a PSP take is a whole move, so the pairing is made at the
// move level: one take (or one frame span of it) per PC state, and the state's phases play
// consecutive slices of that span (psp_moveset.cpp, plan_psp_animation). A state absent here
// takes the documented fallback there: the usable take whose length is nearest the state's own.
//
// The rows are derived findings, not game data, so they are tracked. Every row is a port rule
// (evidence tier 6). `source` names what it rests on:
//   label     the take's visual label in the take study (take_labels.tsv), at the confidence
//             given; "high"/"medium"/"low" are the study's own words
//   kin       no take carries this move; the nearest labelled kind stands in (named in the row)
//   hold      no take carries this move and none is close; idle stands in so the fighter does
//             not play a knockdown for a shot. Pose is wrong, timing is the PC body's
//
// PSP take indices are the 0-based motion index in chrmNN.gmo, which the converted 00.X keeps
// as animation sets 0..75 (src/psp/psp_model.cpp, reverse document order).
#include <cstdint>

namespace daybreak::psp {

inline constexpr unsigned kPspTakeCount = 76;  // motions in every chrmNN.gmo (formats study)

struct TakeChoice {
    std::uint16_t pc_state;   // the dispatch combo's 00.dat state id
    std::uint8_t psp_take;
    // The key frames of the take this move plays, from..to inclusive (30 Hz PSP frames, clamped
    // to the take's last key); 0/0 is the whole take. Consecutive spans share their boundary key,
    // so one move's end pose is the next one's start pose.
    std::uint8_t from, to;
    const char* source;
};

// Take 0 is one whole jump on every PSP rig: crouch, takeoff, rise, fall, land (labels: "jump
// (full arc)", high). The PC splits a jump into five states, so each gets its span, read off the
// root's height curve in the converted model (Bip00 y over the 64 frames, all three rigs alike:
// it dips to frame 8, rises from 10, peaks at 30 and 44, drops to the ground at 50).
#define DAYBREAK_PSP_JUMP_ROWS                                                         \
    {40, 0, 0, 10, "label high: take 0 0-10, crouch before takeoff (root y falls)"},   \
    {41, 0, 10, 30, "label high: take 0 10-30, takeoff and rise"},                    \
    {42, 0, 30, 48, "label high: take 0 30-48, apex and fall"},                       \
    {43, 0, 40, 48, "label high: take 0 40-48, falling"},                             \
    {44, 0, 48, 64, "label high: take 0 48-64, landing"},                             \
    {329, 0, 48, 64, "label high: take 0 48-64, landing after an air move"},          \
    {333, 0, 48, 64, "label high: take 0 48-64, landing after an air move"},          \
    {403, 0, 48, 64, "label high: take 0 48-64, landing after an air shot"},          \
    {409, 0, 48, 64, "label high: take 0 48-64, landing after an air shot"},          \
    {469, 0, 48, 64, "label high: take 0 48-64, landing"}

// Reactions are shared vocabulary on all three rigs (labels: same index, same shape). States
// 1xx are hits from the front, 2xx their from-behind twins; 191-199 the death rows.
#define DAYBREAK_PSP_REACTION_ROWS                                                          \
    {45, 12, 0, 0, "label high: getup"},                                                    \
    {100, 1, 0, 0, "label medium: light flinch (bend forward)"},                            \
    {101, 1, 0, 0, "label medium: light flinch, body hit"},                                 \
    {102, 2, 0, 0, "label medium: light flinch (crouch)"},                                  \
    {104, 2, 0, 0, "label medium: light flinch"},                                           \
    {105, 5, 0, 0, "label high: launched, lands on back"},                                  \
    {106, 2, 0, 0, "label medium: stagger, flinch stands in"},                              \
    {107, 2, 0, 0, "label medium: stagger, flinch stands in"},                              \
    {108, 2, 0, 0, "label medium: stagger, flinch stands in"},                              \
    {113, 5, 0, 0, "label high: launched, lands on back"},                                  \
    {114, 5, 0, 0, "label high: launched, lands on back"},                                  \
    {115, 9, 0, 0, "label high: knocked face down, slides"},                                \
    {116, 5, 0, 0, "label high: launched, lands on back"},                                  \
    {118, 6, 0, 0, "label medium: down on the ground"},                                     \
    {119, 6, 0, 0, "label medium: down on the ground"},                                     \
    {120, 6, 0, 0, "label medium: lying down"},                                             \
    {121, 6, 0, 0, "label medium: down on the ground"},                                     \
    {123, 6, 0, 0, "label medium: down on the ground"},                                     \
    {128, 12, 0, 0, "label high: getup"},                                                   \
    {130, 1, 0, 0, "label medium: light flinch"},                                           \
    {131, 1, 0, 0, "label medium: light flinch"},                                           \
    {133, 5, 0, 0, "label high: launched (thrown)"},                                        \
    {134, 5, 0, 0, "label high: launched (thrown)"},                                        \
    {187, 5, 0, 0, "label high: launched"},                                                 \
    {188, 6, 0, 0, "label medium: down"},                                                   \
    {189, 6, 0, 0, "label medium: down"},                                                   \
    {190, 5, 0, 0, "label high: launched"},                                                 \
    {191, 6, 0, 0, "label medium: down, KO candidate"},                                     \
    {192, 6, 0, 0, "label medium: down, KO candidate"},                                     \
    {193, 6, 0, 0, "label medium: down, KO candidate"},                                     \
    {194, 22, 0, 0, "label medium: air fall, the round-start drop (BattleStart row 194)"},  \
    {195, 6, 0, 0, "label medium: down, KO candidate"},                                     \
    {196, 6, 0, 0, "label medium: down, KO candidate (Knockdown row 196)"},                 \
    {197, 6, 0, 0, "label medium: down, KO candidate"},                                     \
    {198, 9, 0, 0, "label high: knocked face down"},                                        \
    {199, 9, 0, 0, "label high: knocked face down"},                                        \
    {200, 1, 0, 0, "label medium: light flinch (from behind)"},                             \
    {201, 1, 0, 0, "label medium: light flinch (from behind)"},                             \
    {202, 2, 0, 0, "label medium: light flinch (from behind)"},                             \
    {203, 6, 0, 0, "label medium: down, KO candidate (KO row 203)"},                        \
    {204, 2, 0, 0, "label medium: light flinch (from behind)"},                             \
    {205, 5, 0, 0, "label high: launched (from behind)"},                                   \
    {206, 2, 0, 0, "label medium: stagger (from behind)"},                                  \
    {213, 5, 0, 0, "label high: launched (from behind)"},                                   \
    {214, 5, 0, 0, "label high: launched (from behind)"},                                   \
    {215, 9, 0, 0, "label high: knocked face down (from behind)"},                          \
    {216, 5, 0, 0, "label high: launched (from behind)"},                                   \
    {221, 6, 0, 0, "label medium: down (from behind)"},                                     \
    {230, 1, 0, 0, "label medium: light flinch (from behind)"},                             \
    {231, 1, 0, 0, "label medium: light flinch (from behind)"},                             \
    {233, 5, 0, 0, "label high: launched (thrown, from behind)"},                           \
    {234, 5, 0, 0, "label high: launched (thrown, from behind)"}

// Satoshi (PSP chr17) on Keiichi 0's rows.
inline constexpr TakeChoice kSatoshiTakes[] = {
    {0, 13, 0, 0, "label high: idle/stand"},
    {10, 15, 0, 0, "label medium: walk cycle"},
    {20, 25, 0, 0, "label low: dash/lunge forward"},
    {23, 32, 0, 0, "label medium: side step (lateral)"},
    {24, 32, 0, 0, "label medium: side step (lateral)"},
    {27, 27, 0, 0, "label low: drift back (back dash)"},
    {28, 27, 0, 0, "label low: drift back (back dash)"},
    {30, 16, 0, 0, "label medium: airborne leap (air dash)"},
    DAYBREAK_PSP_JUMP_ROWS,
    DAYBREAK_PSP_REACTION_ROWS,
    {103, 28, 0, 0, "label low: hit reaction (flail), the ordinary Hit row 103"},
    {124, 29, 0, 0, "label medium: roll and get up"},
    {300, 10, 0, 0, "label medium: melee swing"},
    {301, 26, 0, 0, "label medium: melee lunge/thrust (combo 2)"},
    {302, 26, 0, 0, "label medium: melee lunge/thrust (combo 3)"},
    {303, 10, 0, 0, "label medium: melee swing"},
    {310, 26, 0, 0, "label medium: melee lunge/thrust"},
    {311, 33, 0, 0, "label medium: air attack after an air dash"},
    {320, 10, 0, 0, "label medium: melee swing"},
    {330, 25, 0, 0, "label low: dash attack, dash/lunge forward"},
    {331, 26, 0, 0, "label medium: melee lunge/thrust"},
    {332, 33, 0, 0, "label medium: air attack (leap melee)"},
    {334, 33, 0, 0, "label medium: air attack (leap melee)"},
    {340, 33, 0, 0, "label medium: air attack"},
    {341, 34, 0, 0, "label low: second air attack"},
    {370, 10, 0, 0, "label medium: melee swing (special strike)"},
    // Shots and guard: no take is labelled as either, and Satoshi has the one upper-body-only
    // take, which suits a row that layers over walking legs.
    {350, 48, 0, 0, "kin medium: upper-body pose stands in for a charged shot"},
    {360, 48, 0, 0, "kin medium: upper-body pose stands in for a charged shot"},
    {390, 48, 0, 0, "kin medium: upper-body pose stands in for guard"},
    {391, 48, 0, 0, "kin medium: upper-body pose stands in for guard"},
    {392, 48, 0, 0, "kin medium: upper-body pose stands in for guard"},
    {393, 48, 0, 0, "kin medium: upper-body pose stands in for guard"},
    {394, 48, 0, 0, "kin medium: upper-body pose stands in for guard"},
    {400, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {401, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {402, 48, 0, 0, "kin medium: upper-body pose stands in for an air shot"},
    {404, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {405, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {406, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {407, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {408, 48, 0, 0, "kin medium: upper-body pose stands in for an air shot"},
    {410, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {411, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {412, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {450, 48, 0, 0, "kin medium: upper-body pose stands in for a charged shot"},
    {451, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {460, 48, 0, 0, "kin medium: upper-body pose stands in for a charged shot"},
    {461, 48, 0, 0, "kin medium: upper-body pose stands in for a shot"},
    {500, 24, 0, 0, "label low: taunt/gesture (hypermode entry)"},
    {501, 24, 0, 0, "label low: taunt/gesture (hypermode entry)"},
    {502, 24, 0, 0, "label low: taunt/gesture (hypermode entry)"},
    {503, 24, 0, 0, "label low: taunt/gesture (hypermode entry)"},
};

// Miyoko (PSP chr18) on Satoko 0's rows. She has one labelled attack take (10) and no lunge, side
// step or air attack, which is why several of her rows are kin rows.
inline constexpr TakeChoice kMiyokoTakes[] = {
    {0, 13, 0, 0, "label high: idle/stand"},
    {10, 15, 0, 0, "label medium: walk cycle"},
    {20, 25, 0, 0, "label low: dash/lunge forward"},
    {23, 4, 0, 0, "kin medium: duck/dodge stands in for a side dash"},
    {24, 4, 0, 0, "kin medium: duck/dodge stands in for a side dash"},
    {27, 27, 0, 0, "label low: drift back (back dash)"},
    {28, 27, 0, 0, "label low: drift back (back dash)"},
    {30, 17, 0, 0, "label low: airborne leap (air dash)"},
    DAYBREAK_PSP_JUMP_ROWS,
    DAYBREAK_PSP_REACTION_ROWS,
    {103, 2, 0, 0, "label medium: light flinch, the ordinary Hit row 103"},
    {124, 30, 0, 0, "label medium: roll and get up"},
    {300, 10, 0, 0, "label medium: melee swing"},
    {301, 10, 0, 0, "label medium: melee swing (combo 2; she has one swing)"},
    {302, 10, 0, 0, "label medium: melee swing (combo 3; she has one swing)"},
    {303, 10, 0, 0, "label medium: melee swing"},
    {310, 25, 0, 0, "label low: dash/lunge forward"},
    {311, 22, 0, 0, "kin medium: air fall/dive stands in for an air attack"},
    {320, 10, 0, 0, "label medium: melee swing"},
    {330, 25, 0, 0, "label low: dash attack, dash/lunge forward"},
    {331, 25, 0, 0, "label low: dash/lunge forward"},
    {332, 16, 0, 0, "kin low: airborne leap stands in for a leap melee"},
    {334, 16, 0, 0, "kin low: airborne leap stands in for a leap melee"},
    {340, 22, 0, 0, "kin medium: air fall/dive stands in for an air attack"},
    {341, 22, 0, 0, "kin medium: air fall/dive stands in for an air attack"},
    {370, 10, 0, 0, "label medium: melee swing (special strike)"},
    {350, 13, 0, 0, "hold: no shot take labelled; idle"},
    {360, 13, 0, 0, "hold: no shot take labelled; idle"},
    {390, 13, 0, 0, "hold: no guard take labelled; idle"},
    {391, 13, 0, 0, "hold: no guard take labelled; idle"},
    {392, 13, 0, 0, "hold: no guard take labelled; idle"},
    {393, 13, 0, 0, "hold: no guard take labelled; idle"},
    {394, 13, 0, 0, "hold: no guard take labelled; idle"},
    {400, 13, 0, 0, "hold: no shot take labelled; idle"},
    {401, 13, 0, 0, "hold: no shot take labelled; idle"},
    {402, 32, 0, 0, "label medium: air idle, for an air shot"},
    {404, 13, 0, 0, "hold: no shot take labelled; idle"},
    {405, 13, 0, 0, "hold: no shot take labelled; idle"},
    {406, 13, 0, 0, "hold: no shot take labelled; idle"},
    {407, 13, 0, 0, "hold: no shot take labelled; idle"},
    {408, 32, 0, 0, "label medium: air idle, for an air shot"},
    {410, 13, 0, 0, "hold: no shot take labelled; idle"},
    {411, 13, 0, 0, "hold: no shot take labelled; idle"},
    {412, 13, 0, 0, "hold: no shot take labelled; idle"},
    {450, 13, 0, 0, "hold: no shot take labelled; idle"},
    {451, 13, 0, 0, "hold: no shot take labelled; idle"},
    {460, 32, 0, 0, "label medium: air idle, for an air charged shot"},
    {461, 32, 0, 0, "label medium: air idle, for an air shot"},
    {500, 26, 0, 0, "label medium: taunt/gesture (hypermode entry)"},
    {501, 26, 0, 0, "label medium: taunt/gesture (hypermode entry)"},
    {502, 26, 0, 0, "label medium: taunt/gesture (hypermode entry)"},
    {503, 26, 0, 0, "label medium: taunt/gesture (hypermode entry)"},
};

// Okonogi (PSP chr19) on Tomitake 0's rows.
inline constexpr TakeChoice kOkonogiTakes[] = {
    {0, 13, 0, 0, "label high: idle/stand"},
    {10, 15, 0, 0, "label medium: walk cycle"},
    {20, 25, 0, 0, "label low-medium: dash/lunge forward"},
    {23, 47, 0, 0, "label medium: side step (lateral)"},
    {24, 48, 0, 0, "label medium: side step (lateral, the other side)"},
    {27, 27, 0, 0, "label low: drift back (back dash)"},
    {28, 27, 0, 0, "label low: drift back (back dash)"},
    {30, 22, 0, 0, "kin medium: air fall/dive stands in for an air dash"},
    DAYBREAK_PSP_JUMP_ROWS,
    DAYBREAK_PSP_REACTION_ROWS,
    {103, 2, 0, 0, "label medium: light flinch, the ordinary Hit row 103"},
    {124, 12, 0, 0, "kin high: getup stands in for a roll (no roll take labelled)"},
    {300, 10, 0, 0, "label medium: melee swing"},
    {301, 26, 0, 0, "label low-medium: melee lunge/thrust (combo 2)"},
    {302, 26, 0, 0, "label low-medium: melee lunge/thrust (combo 3)"},
    {303, 10, 0, 0, "label medium: melee swing"},
    {310, 26, 0, 0, "label low-medium: melee lunge/thrust"},
    {311, 33, 0, 0, "label low-medium: air attack after an air dash"},
    {320, 10, 0, 0, "label medium: melee swing"},
    {330, 25, 0, 0, "label low-medium: dash attack, dash/lunge forward"},
    {331, 26, 0, 0, "label low-medium: melee lunge/thrust"},
    {332, 33, 0, 0, "label low-medium: air attack (leap melee)"},
    {334, 33, 0, 0, "label low-medium: air attack (leap melee)"},
    {340, 33, 0, 0, "label low-medium: air attack"},
    {341, 33, 0, 0, "label low-medium: air attack"},
    {370, 10, 0, 0, "label medium: melee swing (special strike)"},
    {350, 13, 0, 0, "hold: no shot take labelled; idle"},
    {360, 13, 0, 0, "hold: no shot take labelled; idle"},
    {390, 13, 0, 0, "hold: no guard take labelled; idle"},
    {391, 13, 0, 0, "hold: no guard take labelled; idle"},
    {392, 13, 0, 0, "hold: no guard take labelled; idle"},
    {393, 13, 0, 0, "hold: no guard take labelled; idle"},
    {394, 13, 0, 0, "hold: no guard take labelled; idle"},
    {400, 13, 0, 0, "hold: no shot take labelled; idle"},
    {401, 13, 0, 0, "hold: no shot take labelled; idle"},
    {402, 49, 0, 0, "label low-medium: air idle, for an air shot"},
    {404, 13, 0, 0, "hold: no shot take labelled; idle"},
    {405, 13, 0, 0, "hold: no shot take labelled; idle"},
    {406, 13, 0, 0, "hold: no shot take labelled; idle"},
    {407, 13, 0, 0, "hold: no shot take labelled; idle"},
    {408, 49, 0, 0, "label low-medium: air idle, for an air shot"},
    {410, 13, 0, 0, "hold: no shot take labelled; idle"},
    {411, 13, 0, 0, "hold: no shot take labelled; idle"},
    {412, 13, 0, 0, "hold: no shot take labelled; idle"},
    {450, 13, 0, 0, "hold: no shot take labelled; idle"},
    {451, 13, 0, 0, "hold: no shot take labelled; idle"},
    {460, 49, 0, 0, "label low-medium: air idle, for an air charged shot"},
    {461, 49, 0, 0, "label low-medium: air idle, for an air shot"},
    {500, 13, 0, 0, "hold: no taunt take labelled; idle (hypermode entry)"},
    {501, 13, 0, 0, "hold: no taunt take labelled; idle (hypermode entry)"},
    {502, 13, 0, 0, "hold: no taunt take labelled; idle (hypermode entry)"},
    {503, 13, 0, 0, "hold: no taunt take labelled; idle (hypermode entry)"},
};

#undef DAYBREAK_PSP_JUMP_ROWS
#undef DAYBREAK_PSP_REACTION_ROWS

// Takes the fallback must never pick: Satoshi's 52-60 are static placeholders (curves, no motion;
// labels: "static"). Takes with no curves at all (1 frame) are excluded by length, not listed.
inline constexpr std::uint8_t kSatoshiUnusableTakes[] = {52, 53, 54, 55, 56, 57, 58, 59, 60};

struct FighterTakes {
    const TakeChoice* rows;
    unsigned count;
    const std::uint8_t* unusable;
    unsigned unusable_count;
};
// Indexed by psp_character_index: 0 Satoshi, 1 Miyoko, 2 Okonogi.
inline constexpr FighterTakes kFighterTakes[] = {
    {kSatoshiTakes, sizeof kSatoshiTakes / sizeof kSatoshiTakes[0], kSatoshiUnusableTakes,
     sizeof kSatoshiUnusableTakes / sizeof kSatoshiUnusableTakes[0]},
    {kMiyokoTakes, sizeof kMiyokoTakes / sizeof kMiyokoTakes[0], nullptr, 0},
    {kOkonogiTakes, sizeof kOkonogiTakes / sizeof kOkonogiTakes[0], nullptr, 0},
};

}  // namespace daybreak::psp
