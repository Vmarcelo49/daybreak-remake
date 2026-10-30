#pragma once
// FUN_0041e180: NN.dat move IDs address rows; section tags address controller sets.
// Timed entries are bone-local state/hitboxes, not effect names. Trailer entries
// are texture intervals. Full widths, consumers and ambiguities: docs/ANIMATION-DATA-AUDIT.md.

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
#include "battle/combat_record.h"

namespace gameplay {

struct TextureEvent {
    int start = 0;
    int end = 0;
    int repeat = 0;
    std::string source;
    std::string replacement;
    bool active(int elapsed) const {
        const int frame = repeat > 0 ? elapsed % repeat : elapsed;
        return start <= frame && frame < end;
    }
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
    const MoveEntry* record_at(int elapsed) const {
        if (!entryCount) return nullptr;
        int index = 0;
        while (index + 1 < entryCount && entries[index + 1].activeFrame <= elapsed)
            ++index;
        return &entries[index];
    }
};

struct CharacterMove {
    int  id           = 0;
    int  priority     = 0; // destination row+0 compared with current row+4
    int  cancelThreshold = 0;
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
    // The NN.dat body carries an item id but no roster id; the asset loader supplies
    // the character directory so class callbacks stay bound to a verified combo.
    void set_character_index(int index) { m_characterIndex = index; }
    int  character_index() const { return m_characterIndex; }

    int  count() const { return m_count; }
    const CharacterMove* find(int moveId) const;
    bool has(int moveId) const { return find(moveId) != nullptr; }
    // The table's own weapon id (header dword 3, file offset 0x114): NN is the
    // weapon slot and the id agrees with kWeaponIds in all 46 shipped files.
    // 0 when unloaded. Lets callers check they joined the right combo.
    int  weapon_id() const { return m_weaponId; }
    int  animation_set_count() const { return m_animationSetCount; }
    const std::vector<TextureEvent>& texture_events(int setIndex) const;
    const std::string& model_name() const { return m_modelName; }
    // Retained raw header words with no runtime consumer yet: the leading format tag and
    // the six words after the model name (mode thresholds/durations per the audit, not
    // fully consumed). Kept so the file's own declaration order survives re-parsing; do
    // not assign them a meaning the corpus has not established.
    int format_tag() const { return m_formatTag; }
    const int* header_values() const { return m_header; }
    // Raw animation-set +0x1c/+0x20 values, or -1 when the index is absent. The
    // first seeds an eligible class blend; the second gates elapsed-count advance.
    int  animation_set_transition_duration(int setIndex) const;
    int  animation_set_phase_gate(int setIndex) const;
    int  cancel_threshold(int moveId) const; // row+4; not a frame count
    // First-phase set index for a move, or -1 when the move is absent or phaseless —
    // the value FUN_00421100 binds (issue #26: move 20 → 13, move 10 → 1).
    int  first_set_index(int moveId) const;

    static constexpr int kMaxMoves = 512;
    static constexpr int kMaxAnimationSets = 512;

    // Replace one row's phase-0 record list with a single caller-supplied record, so a test
    // can drive the real contact path with a record shape the shipped file may not put in
    // that row. Deliberately narrow: only phase 0, only one entry, and it is a no-op for a
    // move the table does not carry. Production code never calls this — the melee and
    // projectile paths read the parsed rows.
    bool install_move_phase0_record(int moveId, const MoveEntry& record) {
        // Same lookup the readers use, so the two can never disagree about which row an id
        // names; the const_cast is the one place this table hands out a mutable row.
        CharacterMove* move = const_cast<CharacterMove*>(find(moveId));
        if (!move || move->sectionCount < 1) return false;
        move->phases[0].entries[0] = record;
        move->phases[0].entryCount = 1;
        return true;
    }

private:
    void release() noexcept;
    std::vector<CharacterMove> m_moves;
    int           m_count = 0;
    int           m_weaponId = 0;   // header dword 3 (file offset 0x114)
    int           m_characterIndex = -1;  // supplied by the directory-based asset loader
    int           m_animationSetCount = 0;
    int           m_animationSetTransitionDuration[kMaxAnimationSets]{};
    int           m_animationSetPhaseGate[kMaxAnimationSets]{};
    std::vector<TextureEvent> m_textureEvents[kMaxAnimationSets];
    std::string m_modelName;
    int m_formatTag = 0;
    int m_header[6]{};
    bool          m_loaded = false;
};

}  // namespace gameplay
