#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleHitSurvival {
    std::uint32_t health=0,variant=0,active=0,was_alive=0,charge=0,threshold=0,flag84=0,next_state=0,transition=0;
};
// 0x638b9c..0x638c10: preserves all fields when the survival condition fails.
inline void apply_hit_survival(BattleHitSurvival& s){
    if(std::uint8_t(s.variant)!=2||std::uint8_t(s.active)!=0||damage_signed(s.health)>0||!std::uint8_t(s.was_alive)||damage_signed(s.charge)<damage_signed(s.threshold))return;
    s.health=1;s.next_state=std::uint8_t(s.flag84)?502:503;s.transition=1;
}
}
