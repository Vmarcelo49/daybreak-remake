#pragma once

// A synthetic character+weapon pair for Match-based tests that must run with no game
// data. AGENTS rule 7 makes an unequipped Match a false claim ("a bare fighter is a
// false claim, not a simplification"), so a test that resets a Match and then steps,
// damages or drives it has to bind a character AND a weapon. This header supplies both
// from in-memory bytes, so the suite stays data-free and CI-runnable.
//
// The numbers are the shipped ones for Rena's slot-0/slot-1 shape (item id 1): the
// move table carries the weapon chain the swing resolver selects (300 ground / 301
// charged) with rena 300's recovered hit entry (frame 4, radius 20) and a follower at
// frame 7 to bound the window, and the weapon carries magazine 0 = 6 shots at 300 pool
// units, magazine 1 = 2 at 300, charge maxima 60/180.
//
// It is deliberately NOT a load of the install's bytes: a suite that needs the real
// data skips without it (see capture_probe.py's rule and the install-backed fixtures in
// combo_fixture.h). This one is for suites that must always execute.

#include "gameplay/character_moves.h"
#include "gameplay/match.h"
#include "gameplay/weapon_definition.h"

#include <cstdint>
#include <cstring>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace test::synthetic {

inline void putU32(std::vector<std::uint8_t>& b, int v) {
    const std::uint32_t u = static_cast<std::uint32_t>(v);
    for (int i = 0; i < 4; ++i) b.push_back(static_cast<std::uint8_t>((u >> (8 * i)) & 0xffu));
}

inline void putF32(std::vector<std::uint8_t>& b, float v) {
    int i = 0;
    std::memcpy(&i, &v, 4);
    putU32(b, i);
}

inline void putName(std::vector<std::uint8_t>& b, const char* s, int width) {
    const std::size_t n = std::strlen(s);
    for (int i = 0; i < width; ++i)
        b.push_back(i < static_cast<int>(n) ? static_cast<std::uint8_t>(s[i]) : 0u);
}

struct SynthEntry {
    const char* name = "";
    int activeFrame = 0;
    int hitRadius = 0;
    int hpDamage = 0;        // synthetic neutral pool damage (base power is twice this)
    int defenderHitstun = 0; // combat[10]
};

inline SynthEntry prop(const char* name, int frame, int radius, int hpDamage, int hitstun) {
    SynthEntry e;
    e.name = name;
    e.activeFrame = frame;
    e.hitRadius = radius;
    e.hpDamage = hpDamage;
    e.defenderHitstun = hitstun;
    return e;
}

inline void addPhase(std::vector<std::uint8_t>& b, int setIndex,
                     const std::vector<SynthEntry>& entries) {
    putU32(b, setIndex);
    putU32(b, static_cast<int>(entries.size()));
    for (const SynthEntry& e : entries) {
        putName(b, e.name, 30);
        putU32(b, e.activeFrame);
        putF32(b, 0.f);
        putF32(b, 0.f);
        putF32(b, 0.f);
        putU32(b, e.hitRadius);
        int combat[20] = {0};
        combat[0] = e.hpDamage * 2;
        combat[10] = e.defenderHitstun;
        for (int c : combat) putU32(b, c);
        putU32(b, 0);
        putU32(b, 0);
        putU32(b, 0);
        putF32(b, 0.f);
        putF32(b, 0.f);
        putF32(b, 0.f);
    }
}

using SynthPhase = std::pair<int, std::vector<SynthEntry>>;

inline void addMove(std::vector<std::uint8_t>& b, int id, int cancelThreshold,
                    const std::vector<SynthPhase>& phases) {
    putU32(b, id);
    putU32(b, 0);
    putU32(b, cancelThreshold);
    putU32(b, static_cast<int>(phases.size()));
    for (const auto& p : phases) addPhase(b, p.first, p.second);
}

// The move table FUN_0041e180 reads: header, weapon id at file offset 0x114, moves.
inline std::vector<std::uint8_t> moveTable() {
    std::vector<std::uint8_t> b;
    putU32(b, 0x00010000);                 // tag
    putName(b, "data/rena/00.X", 0x104);   // 260-byte model path block
    putU32(b, 0);
    putU32(b, 0);
    putU32(b, 0);
    putU32(b, 1);                          // header[3] = the table's weapon id (0x114)
    putU32(b, 0);
    putU32(b, 0);
    putU32(b, 4);                          // move count
    const SynthEntry pose = prop("", 0, 0, 0, 0);
    addMove(b, 10, 0, {SynthPhase{1, {pose}}});                        // walk
    addMove(b, 20, 8, {SynthPhase{13, {pose}},                         // dash
                       SynthPhase{14, {pose}},
                       SynthPhase{15, {pose}}});
    // rena move 300: the hit goes live on frame 4 at radius 20 and the next effect
    // bounds the window at 7 (the shipped values, melee_rules_test's anchor).
    addMove(b, 300, 12, {SynthPhase{31, {pose, prop("Prop1", 4, 20, 750, 10),
                                       prop("Whiff", 7, 0, 0, 0)}}});
    addMove(b, 301, 12, {SynthPhase{33, {pose, prop("Prop1", 7, 20, 1500, 12),
                                       prop("Whiff", 9, 0, 0, 0)}}});
    putU32(b, 124);
    for (int i = 0; i < 124; ++i) {
        putU32(b, 0);
        putU32(b, 0);
        putU32(b, 0);
    }
    return b;
}

inline std::unique_ptr<gameplay::WeaponDefinition> weapon() {
    auto w = std::make_unique<gameplay::WeaponDefinition>();
    w->id = 1;
    w->slotCount = 2;
    w->bulletCount = 0;
    w->magazines[0] = gameplay::MagazineDefinition{6, 2, 300, 0, 60, 1};
    w->magazines[1] = gameplay::MagazineDefinition{2, 2, 300, 0, 180, 2};
    return w;
}

// A parsed pair, ready to hand to MatchConfig::{moves,weapon}. Parse errors are fatal
// here by construction (the bytes are ours), so the caller can treat a constructed
// Combo as usable.
struct Combo {
    gameplay::CharacterMoves moves;
    std::unique_ptr<gameplay::WeaponDefinition> weapon;
    bool ok = false;
    std::string error;

    Combo() {
        const std::vector<std::uint8_t> bytes = moveTable();
        ok = moves.parse(bytes.data(), bytes.size(), error);
        weapon = synthetic::weapon();
        ok = ok && weapon != nullptr;
    }
    // Bind every slot of a MatchConfig to this one combo: a mirror match, which is all
    // these tests need and keeps the fixture single-sourced.
    void bind(gameplay::MatchConfig& config, int fighterCount) const {
        for (int i = 0; i < fighterCount; ++i) {
            config.moves[i] = &moves;
            config.weapon[i] = weapon.get();
        }
    }
};

} // namespace test::synthetic
