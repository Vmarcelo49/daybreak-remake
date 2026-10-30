#pragma once
#include <array>
#include <cstdint>
#include <vector>
namespace daybreak {
struct BattleRelationships {
    std::vector<std::uint32_t> allies,opponents;
    std::vector<std::array<std::uint32_t,3>> opponent_records;
    std::uint32_t target=0,secondary_target=0,target_index=0,heading_offset_bits=0;
    std::uint8_t mode=0;
    std::uint32_t shared_link=0;
};
// 0x421730. IDs are host-owned handles; shared_link identifies the other
// character's shared field, not a copied value from that field.
inline void add_battle_ally(BattleRelationships& s,std::uint32_t other,std::uint8_t other_flag,std::uint32_t other_shared_field){
    if(other_flag)s.mode=0;
    s.allies.push_back(other);s.shared_link=other_shared_field;
}
// 0x421670. Facing calculation 0x42dd90 is injected until recovered.
template<class FaceTarget> void add_battle_opponent(BattleRelationships& s,std::uint32_t other,FaceTarget face_target){
    s.opponents.push_back(other);
    s.target=s.opponents.front();s.secondary_target=s.opponents.front();
    // Original 0x423940 initializes only word 2 of the temporary record.
    // Zero the two indeterminate words instead of reproducing stack garbage.
    s.opponent_records.push_back({0,0,0});
    face_target(s);
    s.target_index=0;s.target=s.opponents.front();s.secondary_target=s.opponents.front();s.heading_offset_bits=0;
}
}
