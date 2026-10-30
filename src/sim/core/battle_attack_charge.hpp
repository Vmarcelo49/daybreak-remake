#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleAttackCharge{std::uint32_t mode,blocked,charge,limit,ready;};
// Original 0x63844e..0x6384fa, attacker mode 1.
template<class Host> void apply_battle_attack_charge(BattleAttackCharge& s,std::int32_t base,std::int32_t scale,std::uint32_t attacker,Host& host){
 if(std::uint8_t(s.mode)!=1||std::uint8_t(s.blocked)||damage_signed(s.charge)>=damage_signed(s.limit))return;
 s.charge+=std::uint32_t(damage_divide(damage_multiply(base,scale),90));
 if(damage_signed(s.charge)>=damage_signed(s.limit)){host.notify(attacker,6);s.ready=1;s.charge=s.limit;}
}
}
