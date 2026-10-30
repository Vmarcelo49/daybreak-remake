#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleHitScalingSetup{std::uint32_t attack_stop,victim_stop,long_stop,modifier;};
// Original 0x6384fa..0x6385bb. Nonzero divisor required.
inline BattleHitScalingSetup setup_battle_hit_scaling(std::uint32_t attack_stop,std::uint32_t victim_stop,std::uint32_t count,std::int32_t divisor,std::int32_t team_modifier){
 const std::int32_t base=count==0?100:count==1?70:count==2?50:33;
 auto amount=damage_divide(base*100,divisor);amount=damage_divide(damage_multiply(amount,team_modifier),100);
 return {attack_stop,victim_stop,damage_signed(victim_stop)>=60?victim_stop:0,std::uint32_t(amount)};
}
}
