#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace gameplay {

// FUN_0041e180 / FUN_005f8510 resolve the name with D3DXFrameFind. The two
// integer vectors become floats via FILD: fighters use the bone (FUN_00420880),
// bullets use velocity alignment without it (FUN_005f6710).
struct MoveEntry {
    std::string boneName;
    int activeFrame = 0;
    std::array<float, 3> anchor{};
    std::array<float, 3> endAnchor{};
    int hitRadius = 0;
    std::array<int, 20> combat{};
    int stateFlags = 0;
    int attackFlags = 0;
    int collisionShape = 0;
    int baseDamage = 0;
    int hpDamage = 0;
    int reflectDamage = 0;
    int gaugeGainA = 0;
    int gaugeGainB = 0;
    int attackerHitstun = 0;
    int defenderHitstun = 0;
    int reactionMove = 0;
    int combatField0E = 0;
    int combatField0F = 0;

    // FUN_00637950's entry test, byte-verified at 0x6379da: `83 7A 24 00` CMP dword
    // [EDX+0x24],0 / `75 05` JNZ over a jump to the epilogue. The contact resolver bails
    // on radius == 0 and does full resolution otherwise — the HP power is NOT part of the
    // gate. combat[0] is read only inside the HP math (0x638a32, 0x638a6e), so a record
    // with radius != 0 and power 0 still contacts and still applies its gauge feed,
    // hitstop, reaction and impact effect; it just deals no HP damage. Comparing `!= 0`
    // (not `> 0`) matches the original, which tests the dword against zero.
    bool has_combat() const { return hitRadius != 0; }
};

inline bool readCombatRecord(const uint8_t* bytes, size_t size, size_t& offset,
                             MoveEntry& out) {
    constexpr size_t kBytes = 30 + 31 * 4;
    if (!bytes || offset > size || size - offset < kBytes) return false;
    out = MoveEntry{};
    size_t nameLength = 0;
    while (nameLength < 30 && bytes[offset + nameLength]) ++nameLength;
    out.boneName.assign(reinterpret_cast<const char*>(bytes + offset), nameLength);
    offset += 30;
    auto word = [&]() {
        const uint32_t value = uint32_t(bytes[offset]) |
            (uint32_t(bytes[offset + 1]) << 8) |
            (uint32_t(bytes[offset + 2]) << 16) |
            (uint32_t(bytes[offset + 3]) << 24);
        offset += 4;
        return static_cast<int32_t>(value);
    };
    out.activeFrame = word();
    for (float& value : out.anchor) value = static_cast<float>(word());
    out.hitRadius = word();
    for (int& value : out.combat) value = word();
    out.stateFlags = word();
    out.attackFlags = word();
    out.collisionShape = word();
    for (float& value : out.endAnchor) value = static_cast<float>(word());
    out.baseDamage = out.combat[0];
    out.hpDamage = out.combat[5];
    out.reflectDamage = out.combat[6];
    out.gaugeGainA = out.combat[7];
    out.gaugeGainB = out.combat[8];
    out.attackerHitstun = out.combat[9];
    out.defenderHitstun = out.combat[10];
    out.reactionMove = out.combat[13];
    out.combatField0E = out.combat[14];
    out.combatField0F = out.combat[15];
    return true;
}

// Original loader 0x41e839 divides GetPeriod by this float before rounding;
// FUN_0041f580 also positions the pose at elapsed * this value.
inline constexpr float kOriginalAnimationTick = 0.016f;

} // namespace gameplay
