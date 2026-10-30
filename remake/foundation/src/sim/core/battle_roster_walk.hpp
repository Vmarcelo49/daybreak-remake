#pragma once
#include "battle_walk_motion.hpp"
#include "character_dispatch.hpp"
namespace daybreak {
// State10 in the46 dispatch update bodies, recorded in roster-walk-profiles.json.
inline float roster_walking_speed(unsigned character,unsigned weapon,bool awakened=false){
 character_action_dispatch(character,weapon);
 //5D5650..5D568B: Hanyuu1 State10 uses5 when ANY844/845/846
 // is active, otherwise4. The other45 State10 bodies retain their base speed.
 if(character==14&&weapon==1&&awakened)return 5.f;
 static constexpr float speeds[16][3]={
 {7.19999981f,7.19999981f,2.5f},
 {6.5f,7.f,6.5f},
 {7.f,7.f,7.f},
 {7.5f,7.5f,6.f},
 {4.f,4.f,7.5f},
 {8.5f,8.5f,8.5f},
 {6.25f,6.25f,6.25f},
 {6.75f,5.5f,6.75f},
 {6.25f,6.25f,6.25f},
 {7.25f,7.25f,7.25f},
 {6.5f,6.5f,6.5f},
 {6.f,6.f,6.f},
 {6.75f,6.75f,6.75f},
 {4.5f,4.5f,4.5f},
 {4.f,4.f,0.f},
 {7.19999981f,7.19999981f,0.f}
 };return speeds[character][weapon];
}
inline void advance_roster_walk(BattleWalkMotion& s,unsigned character,unsigned weapon,int x,int z,float& speed,float& offset,bool awakened=false){
 const float value=roster_walking_speed(character,weapon,awakened);
 advance_battle_walk(s,x,z,speed,offset,!(character==0&&weapon==2),value);
}
}
