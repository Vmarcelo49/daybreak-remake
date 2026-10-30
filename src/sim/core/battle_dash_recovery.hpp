#pragma once
#include "character_dispatch.hpp"
#include <algorithm>
namespace daybreak {
struct BattleDashRecovery {float vertical=0,gravity=0,speed=0,movement_angle=0,turn_step=0;int gauge=0;};
// State333 in all 46 original update handlers. This does not supply state332,
// admission, animation clocks, contacts or the rest of a fighter's policy.
inline bool dash_recovery_preserves_vertical(unsigned character,unsigned weapon){
 character_action_dispatch(character,weapon);
 return (character==8&&weapon==2)||character==10||(character==11&&weapon==1)||character==12||character==13||character==14||(character==15&&weapon==0);
}
inline int advance_battle_dash_recovery(BattleDashRecovery& s,unsigned character,unsigned weapon,bool complete,bool slowed){
 const bool preserve=dash_recovery_preserves_vertical(character,weapon);
 if(complete)return 0; // 4218c0 completion precedes all writes.
 s.gravity=0;if(!preserve)s.vertical=0;s.movement_angle=0;s.turn_step=0;
 if(character==6){s.speed-=.5f;if(s.speed<0)s.speed=0;}else s.speed=0;
 s.gauge=std::min(1000,s.gauge+(slowed?5:40));return -1;
}
}
