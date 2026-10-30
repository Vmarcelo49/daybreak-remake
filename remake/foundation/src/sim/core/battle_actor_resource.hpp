#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
// 0x421930 / 0x421960. Inputs resolve world team limit and actor team usage.
inline std::int32_t remaining_battle_resource(std::uint32_t limit,std::uint32_t used){return damage_signed(limit-used);}
inline std::int32_t mark_battle_defeated(std::uint32_t limit,std::uint32_t used,std::uint8_t& defeated){defeated=1;return remaining_battle_resource(limit,used);}
}
