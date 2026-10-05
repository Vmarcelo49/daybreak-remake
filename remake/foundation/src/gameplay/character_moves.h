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

// WHAT IS NOT HERE, and matters for melee: moves 40/41/42 — the melee chain every
// character ships - have an all-zero combat block (and 0x2B is not a melee hit at
// all: it is the universal cancel-out move, started from ~2000 sites). So melee
// reach,
// damage and window lengths are NOT in the character move table; they live in the
// per-character move scripts this port does not execute. gameplay/melee_rules.h therefore
// treats every melee number as an explicit port rule and says so, rather than inventing
// geometry that looks recovered.

#include <cstddef>
#include <cstdint>
#include <string>

namespace gameplay {

// One entry of a move's phase list. Same field names and same (offset - 0x30) / 4 blob
// indexing as gameplay::BulletParameter, because it is the same record.
struct MoveEntry {
    std::string effectName;
    int hitRadius       = 0;   // record +0x24
    int baseDamage      = 0;   // combat[0x00]
    int hpDamage        = 0;   // combat[0x05]
    int reflectDamage   = 0;   // combat[0x06]
    int gaugeGainA      = 0;   // combat[0x07]
    int gaugeGainB      = 0;   // combat[0x08]
    int attackerHitstun = 0;   // combat[0x09]
    int defenderHitstun = 0;   // combat[0x0a]
    int reactionMove    = 0;   // combat[0x0d] — FUN_0063ba80's hit-reaction category
    int chargeTier1Move = 0;   // combat[0x0e]
    int chargeTier2Move = 0;   // combat[0x0f]

    // A move entry with no combat block is decorative (a pose, a trail, a sound). The
    // melee chain is entirely made of these, which is the whole reason melee geometry
    // cannot be read from here.
    bool has_combat() const { return hpDamage != 0 || baseDamage != 0 || hitRadius != 0; }
};

struct CharacterMove {
    int  id           = 0;
    int  recordFlags  = 0;
    int  cancelWindow = 0;  // record +0x04: a CANCEL-WINDOW threshold, not a duration
    int  sectionCount = 0;
    // Fixed-size, allocation-free after parse(): the shipped set never exceeds 8.
    static constexpr int kMaxSections = 8;
    static constexpr int kMaxEntries  = 8;
    MoveEntry entries[kMaxEntries]{};
    int       entryCount = 0;
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
    // Phase frames for a move, or 0 when absent — the caller decides whether 0 means
    int  cancel_window(int moveId) const;   // record +0x04: NOT a duration
    int  phase_frames(int moveId) const;

    static constexpr int kMaxMoves = 512;

private:
    void release() noexcept;
    CharacterMove m_moves[kMaxMoves]{};
    int           m_count = 0;
    bool          m_loaded = false;
};

}  // namespace gameplay