#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleHitCharge{std::uint32_t mode,blocked0,blocked2,charge0,charge2,limit;};
// Original 0x6382d9..0x63844e; host notification precedes mode-0 clamp.
template<class Host> void apply_battle_hit_charge(BattleHitCharge& s,std::int32_t base,std::int32_t scale,std::int32_t defense,std::int32_t modifier,std::uint32_t victim,Host& host){
 const auto mode=std::uint8_t(s.mode);if(mode!=0&&mode!=2)return;
 if(std::uint8_t(mode==0?s.blocked0:s.blocked2))return;
 auto& charge=mode==0?s.charge0:s.charge2;if(damage_signed(charge)>=damage_signed(s.limit))return;
 auto amount=damage_divide(damage_multiply(base,scale),mode==0?133:225);
 amount=damage_divide(damage_multiply(amount,defense),100);
 amount=damage_divide(damage_multiply(amount,modifier),100);charge+=std::uint32_t(amount);
 if(damage_signed(charge)>=damage_signed(s.limit)){if(mode==0)host.notify(victim,5);charge=s.limit;}
}
}
