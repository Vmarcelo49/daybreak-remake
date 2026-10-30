#pragma once
#include "character_dispatch.hpp"
namespace daybreak {
// Slot7 ordinary-input branch only. Caller must preserve earlier dash/special
// returns. Some original guards test gauge; others enter even at zero gauge.
inline bool battle_guard_requires_gauge(unsigned character,unsigned weapon){
 bool valid=false;for(const auto& entry:character_dispatch)if(entry.character==character&&entry.weapon==weapon)valid=true;
 if(!valid)throw std::out_of_range("Empty-shot character/weapon");
 return (character==0&&(weapon==0||weapon==2))||(character==1&&weapon==0)||
        (character==2&&(weapon==0||weapon==2))||character==15;
}
inline bool battle_ordinary_guard_gate(unsigned character,unsigned weapon,bool chord,bool grounded,
 int gauge,unsigned flags,int priority,int guard_priority){
 return chord&&grounded&&(flags&0x100)&&priority<=guard_priority&&
        (!battle_guard_requires_gauge(character,weapon)||gauge>0);
}
inline bool battle_empty_shot_event(int released,int rounds,bool guard_gate){
 return !guard_gate&&released>0&&released<20&&rounds==0;
}
}
