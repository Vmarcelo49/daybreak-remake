#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
// 0x638cad..0x638d25. Caller has confirmed death of a previously live actor.
inline std::uint32_t hit_death_score(std::uint32_t health,std::uint32_t extra){
    auto over=damage_divide(damage_signed(0u-health),500);
    if(over>5)over=5;
    if(damage_signed(health)<-3500)++over;
    if(damage_signed(health)<-4500)++over;
    return std::uint32_t(over)+extra+20u;
}
}
