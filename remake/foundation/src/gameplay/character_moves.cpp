// gameplay/character_moves.cpp — the data/<char>/NN.dat move table, transcribed from
// FUN_0041e180 (0x41e180). See character_moves.h for the layout, the verification
// against the shipped data, and what is deliberately absent (the melee chain).
#include "gameplay/character_moves.h"

#include <cstring>

namespace gameplay {
namespace {

constexpr int kMaxEntriesPerMove  = 32;   // guards the read against a corrupt count
constexpr int kMaxAnimationEventsPerSet = 4096;

}  // namespace

CharacterMoves::~CharacterMoves() { release(); }

void CharacterMoves::release() noexcept {
    m_moves.clear();
    m_count    = 0;
    m_weaponId = 0;
    m_characterIndex = -1;
    m_animationSetCount = 0;
    for (int i = 0; i < kMaxAnimationSets; ++i) {
        m_animationSetTransitionDuration[i] = 0;
        m_animationSetPhaseGate[i] = 0;
        m_textureEvents[i].clear();
    }
    m_modelName.clear();
    m_formatTag = 0;
    for (int& value : m_header) value = 0;
    m_loaded   = false;
}

bool CharacterMoves::parse(const uint8_t* bytes, size_t size, std::string& error) {
    release();
    if (bytes == nullptr || size < 8) {
        error = "character moves: file too small";
        return false;
    }
    size_t offset = 0;
    auto u32 = [&](int& out) {
        if (offset + 4 > size) return false;
        std::memcpy(&out, bytes + offset, 4);
        offset += 4;
        return true;
    };
    auto name = [&](std::string& out, size_t width) {
        if (offset + width > size) return false;
        const char* p = reinterpret_cast<const char*>(bytes + offset);
        size_t len = 0;
        while (len < width && p[len] != '\0') ++len;
        out.assign(p, len);
        offset += width;
        return true;
    };

    if (!u32(m_formatTag) || !name(m_modelName, 0x104)) {
        error = "character moves: truncated header";
        return false;
    }
    // Six header dwords; index 3 (file offset 0x114) is the table's own weapon
    // id, read on to the item loader (FUN_0041e180.c:99-106 → FUN_00433eb0).
    // NN is the weapon slot, and all 46 shipped files agree with kWeaponIds.
    int headerVals[6] = {0, 0, 0, 0, 0, 0};
    for (int i = 0; i < 6; ++i) {
        if (!u32(headerVals[i])) {
            error = "character moves: truncated header block";
            return false;
        }
    }
    m_weaponId = headerVals[3];
    for (int i = 0; i < 6; ++i) m_header[i] = headerVals[i];
    int moveCount = 0;
    if (!u32(moveCount) || moveCount < 0 || moveCount > kMaxMoves) {
        error = "character moves: implausible move count";
        return false;
    }
    m_moves.reserve(static_cast<size_t>(moveCount));

    for (int mi = 0; mi < moveCount; ++mi) {
        int id = 0, priority = 0, cancel = 0, sections = 0;
        if (!u32(id) || !u32(priority) || !u32(cancel) || !u32(sections) ||
            id < 0 || id >= kMaxMoves || sections < 0 ||
            sections > CharacterMove::kMaxSections) {
            error = "character moves: truncated move " + std::to_string(mi);
            return false;
        }
        // FUN_0041e180 writes each row to player + 0x880 + moveId * 0x1c;
        // repeated IDs therefore replace the earlier row instead of making the
        // whole character table invalid (for example, Rena 02.dat repeats 311).
        int storedIndex = -1;
        for (int i = 0; i < m_count; ++i)
            if (m_moves[i].id == id) storedIndex = i;
        const bool newMove = storedIndex < 0;
        if (newMove) m_moves.emplace_back();
        CharacterMove& move = m_moves[newMove ? m_count : storedIndex];
        move = CharacterMove{};
        move.id = id;
        move.priority = priority;
        move.cancelThreshold = cancel;
        move.sectionCount = sections;
        for (int s = 0; s < sections; ++s) {
            int sectionTag = 0, entryCount = 0;
            if (!u32(sectionTag) || !u32(entryCount) || entryCount < 0 ||
                entryCount > kMaxEntriesPerMove) {
                error = "character moves: truncated section in move " + std::to_string(id);
                return false;
            }
            // The section tag IS the animation set index the original binds for this
            // phase (FUN_00421100/FUN_0041f580 via phase[0] — issue #26).
            MovePhase& phase = move.phases[s];
            phase = MovePhase{};
            phase.setIndex = sectionTag;
            if (entryCount > MovePhase::kMaxPhaseEntries) {
                error = "character moves: phase entry storage exceeded";
                return false;
            }
            for (int e = 0; e < entryCount; ++e) {
                if (!readCombatRecord(bytes, size, offset, phase.entries[e])) {
                    error = "character moves: truncated state record";
                    return false;
                }
                ++phase.entryCount;
            }
        }
        if (newMove) ++m_count;
    }

    // FUN_0041e180 continues past the move records with one animation-set row per
    // controller index. It computes the set period from D3DX, then reads file +0x1c,
    // the +0x20 auto-advance gate, and the timed animation-event records. Retain both
    // timing values and consume the variable event payloads so later rows stay aligned.
    int animationSetCount = 0;
    if (!u32(animationSetCount) || animationSetCount < 0 ||
        animationSetCount > kMaxAnimationSets) {
        error = "character moves: implausible animation-set count";
        return false;
    }
    m_animationSetCount = animationSetCount;
    for (int set = 0; set < animationSetCount; ++set) {
        int transitionDuration = 0, phaseGate = 0, eventCount = 0;
        if (!u32(transitionDuration) || !u32(phaseGate) || !u32(eventCount) ||
            eventCount < 0 || eventCount > kMaxAnimationEventsPerSet) {
            error = "character moves: truncated animation-set row " + std::to_string(set);
            return false;
        }
        m_animationSetTransitionDuration[set] = transitionDuration;
        m_animationSetPhaseGate[set] = phaseGate;
        for (int i = 0; i < eventCount; ++i) {
            TextureEvent event;
            if (!u32(event.start) || !u32(event.end) || !u32(event.repeat) ||
                !name(event.source, 60) || !name(event.replacement, 60)) {
                error = "character moves: truncated texture event";
                return false;
            }
            m_textureEvents[set].push_back(std::move(event));
        }
    }
    if (offset != size) {
        error = "character moves: unexpected trailing data";
        return false;
    }
    m_loaded = true;
    error.clear();
    return true;
}

const CharacterMove* CharacterMoves::find(int moveId) const {
    if (!m_loaded || moveId < 0 || moveId >= kMaxMoves) return nullptr;
    for (int i = 0; i < m_count; ++i)
        if (m_moves[i].id == moveId) return &m_moves[i];
    return nullptr;
}

int CharacterMoves::cancel_threshold(int moveId) const {
    const CharacterMove* m = find(moveId);
    return m ? m->cancelThreshold : 0;
}

int CharacterMoves::first_set_index(int moveId) const {
    const CharacterMove* m = find(moveId);
    return m ? m->first_set_index() : -1;
}

int CharacterMoves::animation_set_phase_gate(int setIndex) const {
    if (!m_loaded || setIndex < 0 || setIndex >= m_animationSetCount) return -1;
    return m_animationSetPhaseGate[setIndex];
}

int CharacterMoves::animation_set_transition_duration(int setIndex) const {
    if (!m_loaded || setIndex < 0 || setIndex >= m_animationSetCount) return -1;
    return m_animationSetTransitionDuration[setIndex];
}

const std::vector<TextureEvent>& CharacterMoves::texture_events(int setIndex) const {
    static const std::vector<TextureEvent> empty;
    return m_loaded && setIndex >= 0 && setIndex < m_animationSetCount
        ? m_textureEvents[setIndex] : empty;
}

}  // namespace gameplay
