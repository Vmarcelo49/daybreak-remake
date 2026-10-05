// gameplay/character_moves.cpp — the data/<char>/NN.dat move table, transcribed from
// FUN_0041e180 (0x41e180). See character_moves.h for the layout, the verification
// against the shipped data, and what is deliberately absent (the melee chain).
#include "gameplay/character_moves.h"

#include <cstring>
#include <new>

namespace gameplay {
namespace {

constexpr int kMaxEntriesPerMove  = 32;   // guards the read against a corrupt count

}  // namespace

CharacterMoves::~CharacterMoves() { release(); }

void CharacterMoves::release() noexcept {
    m_count    = 0;
    m_weaponId = 0;
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
    auto name30 = [&](std::string& out) {
        if (offset + 30 > size) return false;
        const char* p = reinterpret_cast<const char*>(bytes + offset);
        size_t len = 0;
        while (len < 30 && p[len] != '\0') ++len;
        out.assign(p, len);
        offset += 30;
        return true;
    };
    auto f32 = [&]() { float v = 0.f; u32(reinterpret_cast<int&>(v)); return v; };

    int tag = 0;
    if (!u32(tag) || offset + 0x104 > size) {
        error = "character moves: truncated header";
        return false;
    }
    offset += 0x104;
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
    int moveCount = 0;
    if (!u32(moveCount) || moveCount < 0 || moveCount > kMaxMoves) {
        error = "character moves: implausible move count";
        return false;
    }

    for (int mi = 0; mi < moveCount; ++mi) {
        int id = 0, flags = 0, frames = 0, sections = 0;
        if (!u32(id) || !u32(flags) || !u32(frames) || !u32(sections) ||
            id < 0 || id >= kMaxMoves || sections < 0 ||
            sections > CharacterMove::kMaxSections) {
            error = "character moves: truncated move " + std::to_string(mi);
            return false;
        }
        // A duplicate id would make find() ambiguous; the shipped files do not have one.
        if (has(id)) {
            error = "character moves: duplicate move id " + std::to_string(id);
            return false;
        }
        CharacterMove& move = m_moves[m_count];
        move = CharacterMove{};
        move.id = id;
        move.recordFlags = flags;
        move.cancelWindow = frames;
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
            for (int e = 0; e < entryCount; ++e) {
                MoveEntry entry;
                int v04 = 0, radius = 0;
                int combat[20] = {0};
                int v28 = 0, v2c = 0, v08 = 0;
                if (!name30(entry.effectName) || !u32(v04)) {
                    error = "character moves: truncated effect record";
                    return false;
                }
                f32(); f32(); f32();          // v0c, v10, v14 — instance placement
                if (!u32(radius)) {
                    error = "character moves: truncated effect radius";
                    return false;
                }
                for (int c = 0; c < 20; ++c) {
                    if (!u32(combat[c])) {
                        error = "character moves: truncated combat block";
                        return false;
                    }
                }
                if (!u32(v28) || !u32(v2c) || !u32(v08)) {
                    error = "character moves: truncated effect tail";
                    return false;
                }
                f32(); f32(); f32();          // v18, v1c, v20
                entry.activeFrame = v04;
                entry.hitRadius = radius;
                entry.baseDamage      = combat[0x00];
                entry.hpDamage        = combat[0x05];
                entry.reflectDamage   = combat[0x06];
                entry.gaugeGainA      = combat[0x07];
                entry.gaugeGainB      = combat[0x08];
                entry.attackerHitstun = combat[0x09];
                entry.defenderHitstun = combat[0x0a];
                entry.reactionMove    = combat[0x0d];
                entry.chargeTier1Move = combat[0x0e];
                entry.chargeTier2Move = combat[0x0f];
                // The stream is always consumed whole; storage keeps the first entries
                // (the cap covers everything shipped: at most 19 per phase, move 350).
                if (phase.entryCount < MovePhase::kMaxPhaseEntries)
                    phase.entries[phase.entryCount++] = entry;
            }
        }
        ++m_count;
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

int CharacterMoves::cancel_window(int moveId) const {
    const CharacterMove* m = find(moveId);
    return m ? m->cancelWindow : 0;
}

int CharacterMoves::first_set_index(int moveId) const {
    const CharacterMove* m = find(moveId);
    return m ? m->first_set_index() : -1;
}

}  // namespace gameplay