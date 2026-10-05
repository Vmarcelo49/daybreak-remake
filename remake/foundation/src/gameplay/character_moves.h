#pragma once
// character_moves.h — one character's move table, parsed from `data/<char>/NN.dat`.
//
// Device-free, and the same record format weapon_definition.cpp already reads for
// data/bullet/<id>/<type>.dat: FUN_0041e180 (0x41e180) and FUN_005f8510 (0x5f8510) are
// the same reader twice. That is why one parser covers both.
//
// FILE LAYOUT, in FUN_0041e180's own read order:
//   u32  tag                (:61)
//   260-byte model path block (:62, 0x104)
//   u32  x6                 (:99-104) — +0x324,+0x328,+0x32C,+0x330 plus two locals
//   u32  moveCount          (:106, local_14)
//   moveCount x {
//     u32  moveId           (:109)  — indexes player+0x880 + id*0x1C (FUN_00421080:15)
//     u32  recordFlags      (:111)
//     u32  cancelWindow     (:112)  - see the correction below: a CANCEL WINDOW,
//                                not a duration. The duration is at phase+0x1C,
//                                which this parser does not reach.
//     u32  sectionCount     (:113)
//     sectionCount x {
//       u32  sectionTag     (:116)
//       u32  entryCount     (:117)
//       entryCount x {              the 0x80-byte effect record, in FILE order
//         char name[30]             (:120)
//         u32  v04                 (:122)
//         f32  v0c, v10, v14       (:123-125)
//         u32  hitRadius           (:126)  record +0x24
//         i32  combat[20]          (:127)  0x50 bytes verbatim -> record +0x30
//         u32  v28, v2c, v08       (:129-131)
//         f32  v18, v1c, v20       (:132-134)
//       }
//     }
//   }
//
// VERIFIED against the shipped data, not assumed: parsing
// Higurashi-Daybreak/data/rena/00.dat yields 122 move records whose ids are 0, 10, 11,
// 12, 20, 23, 24, 27, 28, 30, 40..45, 100..113, ... up to 503 - the families
// gameplay/fighter.h documents (walks 20/23/24/27, the 0x28-0x2D group, shots
// 300/301/302).
//
// CORRECTION: record +0x04 is NOT a phase duration. It is a file-loaded constant with
// no writer anywhere in the binary's .text, only ever read as a threshold against a
// frame budget (35 sites in FUN_0043ded0, e.g. `move[4] <= player[0xce0]`) - i.e. a
// CANCEL WINDOW. The real per-phase duration lives at phase+0x1C, which this parser does
// not reach. An earlier draft called +0x04 a frame count and argued it from the shot
// chain's 20/30/50 progression; that argument is WITHDRAWN - 20/30/50 is as consistent
// with a cancel threshold as with a duration.

// WHAT IS NOT HERE, and matters for melee: moves 40/41/42 — the jump chain
// (section tags [2]/[3,4]/[5,43], issue #26), not the melee chain they were mistaken
// for — have an all-zero combat block (and 0x2B is not a melee hit at all: it is the
// universal cancel-out move, started from ~2000 sites). Real melee reach, damage and
// window lengths live in the 300-family weapon phases (Prop/Toe-bone entries with
// non-zero combat) and the per-character handler virtuals this port does not execute.
// gameplay/melee_rules.h therefore treats every melee number as an explicit port rule
// and says so, rather than inventing geometry that looks recovered.

#include <cstddef>
#include <cstdint>
#include <string>

namespace gameplay {

// One entry of a phase's effect list. Same field names and same (offset - 0x30) / 4 blob
// indexing as gameplay::BulletParameter, because it is the same record.
struct MoveEntry {
    std::string effectName;
    int activeFrame     = 0;   // record v04: in-phase frame this effect fires on
    int hitRadius       = 0;   // record +0x24
    int baseDamage      = 0;   // combat[0x00]
    int hpDamage        = 0;   // combat[0x05]
    int reflectDamage   = 0;   // combat[0x06]
    int gaugeGainA      = 0;   // combat[0x07]
    int gaugeGainB      = 0;   // combat[0x08]
    int attackerHitstun = 0;   // combat[0x09]
    int defenderHitstun = 0;   // combat[0x0a]
    int reactionMove    = 0;   // combat[0x0d] — FUN_0063ba80's hit-reaction category.
                               // Same file offset BulletParameter calls chargeTier1Move;
                               // the meaning is context-dependent (victim reaction for
                               // a melee hit, shot move id for a bullet).
    int chargeTier1Move = 0;   // combat[0x0e]
    int chargeTier2Move = 0;   // combat[0x0f]

    // A move entry with no combat block is decorative (a pose, a trail, a sound). The
    // locomotion chain is entirely made of these, which is the whole reason melee geometry
    // cannot be read from here.
    bool has_combat() const { return hpDamage != 0 || baseDamage != 0 || hitRadius != 0; }
};

// One phase of a move: the section tag IS the animation set index the original binds
// (FUN_00421100 passes phase[0] to FUN_00421410 for both tracks; FUN_0041f580 reads the
// same word back as the anim-table index — issue #26). Previously the parser discarded
// the tag and flattened the entries, which is what let the wrong move ids hide.
struct MovePhase {
    int setIndex = -1;  // section tag = animation set index (controller index)
    // Fixed-size, allocation-free after parse(): the shipped set peaks at 19 entries in
    // one phase (rena move 350), so 24 holds everything shipped with headroom.
    static constexpr int kMaxPhaseEntries = 24;
    MoveEntry entries[kMaxPhaseEntries]{};
    int       entryCount = 0;
};

struct CharacterMove {
    int  id           = 0;
    int  recordFlags  = 0;
    int  cancelWindow = 0;  // record +0x04: a CANCEL-WINDOW threshold, not a duration
    int  sectionCount = 0;  // file's section count; the length of phases[] below
    // Fixed-size, allocation-free after parse(): the shipped set peaks at 6 sections
    // in one move, so 8 holds everything shipped with headroom.
    static constexpr int kMaxSections = 8;
    MovePhase phases[kMaxSections]{};

    // The set the original binds when it starts this move: the FIRST phase's index
    // (FUN_00421100 binds phase 0 to both tracks; FUN_00421240 rebinds it to track 1
    // on a move change). -1 when the move has no phases.
    int first_set_index() const {
        return sectionCount > 0 ? phases[0].setIndex : -1;
    }
    // Every phase's set index in order, e.g. move 20 → [13, 14, 15] (issue #26 anchor).
    int phase_set_index(int phase) const {
        if (phase < 0 || phase >= sectionCount) return -1;
        return phases[phase].setIndex;
    }
};

class CharacterMoves {
public:
    CharacterMoves() = default;
    ~CharacterMoves();
    CharacterMoves(const CharacterMoves&) = delete;
    CharacterMoves& operator=(const CharacterMoves&) = delete;

    bool parse(const uint8_t* bytes, size_t size, std::string& error);
    bool valid() const { return m_loaded; }

    int  count() const { return m_count; }
    const CharacterMove* find(int moveId) const;
    bool has(int moveId) const { return find(moveId) != nullptr; }
    int  cancel_window(int moveId) const;   // record +0x04: a CANCEL-WINDOW threshold,
                                           // NOT a duration; 0 when the move is absent
    // First-phase set index for a move, or -1 when the move is absent or phaseless —
    // the value FUN_00421100 binds (issue #26: move 20 → 13, move 10 → 1).
    int  first_set_index(int moveId) const;

    static constexpr int kMaxMoves = 512;

private:
    void release() noexcept;
    CharacterMove m_moves[kMaxMoves]{};
    int           m_count = 0;
    bool          m_loaded = false;
};

}  // namespace gameplay