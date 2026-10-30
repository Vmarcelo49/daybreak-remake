#pragma once
#include "character_dispatch.hpp"

namespace daybreak {
// Slot-7 state30 fast cancels. The original handlers share the phase/priority
// gates, but only these bindings select the dedicated 408/332 routes.
inline bool roster_air_dash_fast_shot(unsigned character,unsigned weapon,unsigned phase,bool directional){
 character_action_dispatch(character,weapon);
 return (phase<2&&((character==0&&weapon==0)||(character==2&&weapon==0)||character==15))||
        (character==4&&weapon<2&&phase==1&&directional);
}
inline bool roster_air_dash_fast_melee(unsigned character,unsigned weapon,unsigned phase,bool directional){
 character_action_dispatch(character,weapon);
 if(phase>=2)return false;
 if(character==15)return phase==1;
 if(character==0)return weapon<2&&phase==1;
 if(!directional)return false;
 if(character==4)return weapon==2;
 if(phase!=1)return false;
 switch(character){
 case 2:case 3:case 5:case 6:case 7:case 8:case 9:case 11:return true;
 default:return false;
 }
}
}
