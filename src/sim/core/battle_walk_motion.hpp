#pragma once
#include "battle_steering.hpp"
namespace daybreak {
// 438310 state10: direction category changes set +874=7, speed=2.5,
// relative angle +60=0, then the eight-direction 421780 steering call.
struct BattleWalkMotion {int direction=10;float step=0;};
inline void advance_battle_walk(BattleWalkMotion& s,int x,int z,float& speed,float& offset,bool keiichi=false,float walking_speed=7.f){
 if(!x&&!z){s.direction=10;s.step=0;speed=0;return;}
 const int direction=z<0?(x>0?1:x<0?2:0):z>0?(x>0?5:x<0?7:6):(x>0?3:4);
 if(direction!=s.direction){s.direction=direction;s.step=keiichi?20.f:7.f;}
 // 46a190 state10 (Keiichi weapon0): reset to 20, then decay before steering.
 if(keiichi)s.step-=1.f;
 if(s.step<1.f)s.step=1.f;
 speed=keiichi?walking_speed:2.5f;steer_battle_offset(offset,x,z,s.step);
}
}
