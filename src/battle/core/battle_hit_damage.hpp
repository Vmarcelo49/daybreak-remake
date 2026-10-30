#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
// 0x638a18..0x638b9c, after hit eligibility and status effects.
inline BattleDamageApplied apply_hit_damage_prefix(BattleDamageTotals& s,std::int32_t base,std::int32_t modifier,std::int32_t attack,std::int32_t defense,bool reduce_large,bool targeted,std::int32_t hit_count_gate){
    BattleDamageApplied r;r.was_alive=damage_signed(s.health)>0;
    auto damage=damage_divide(damage_multiply(base,modifier),100);
    damage=damage_divide(damage_multiply(damage,attack),100);
    r.amount=damage_divide(damage_multiply(damage,defense),100);
    if(base>=10000&&reduce_large)r.amount=damage_divide(r.amount,3);
    s.health-=std::uint32_t(r.amount);if(damage_signed(s.health)<0)r.excess=damage_signed(0u-s.health);
    const auto credit=std::uint32_t(r.amount)-std::uint32_t(r.excess);const unsigned i=targeted?0:1;
    s.victim_damage[i]+=credit;s.attacker_damage[i]+=credit;
    if(hit_count_gate>0){++s.victim_hits[i];++s.attacker_hits[i];}return r;
}
}
