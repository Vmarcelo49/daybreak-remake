#pragma once
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>
namespace daybreak {
// Character state40..43 in 0x438310. Caller owns animation clocks and state changes.
struct BattleJumpMotion {
 unsigned state=40,phase=0,frame=0,held_ticks=0,button_ticks=0;
 int gauge=1000,x=0,z=0;
 bool grounded=true,animation_complete=false,slow_recovery=false;
 float speed=0,vertical=0,gravity=0,offset=0;
};
// State40..43 constants recovered from all 46 original update handlers.
// The launch value is weapon-independent; state41 and state42 can steer at
// different rates even for the same fighter.
struct BattleJumpTuning {
 float launch=12.f,ascent_speed=6.f,ascent_turn=1.f,falling_turn=1.f;
 int hover_gauge_cost=10;
 bool falling_speed_control=false,reset_landing_gravity=false;
};
inline BattleJumpTuning battle_roster_jump_tuning(unsigned character,unsigned weapon){
 if(character>=16||weapon>=(character<14?3u:2u))throw std::out_of_range("Invalid jump fighter/weapon");
 BattleJumpTuning tuning;
 if(character==1||character==7||character==8||character==10||character==12)tuning.launch=10.5f;
 if(character==5)tuning.launch=15.5f;
 if(character==3||character==4||character==14){tuning.ascent_speed=5.f;tuning.ascent_turn=3.f;}
 if(character==4||character==14)tuning.falling_turn=3.f;
 if((character==4&&weapon!=2)||character==14)tuning.falling_speed_control=true;
 if(character==0&&weapon==0)tuning.reset_landing_gravity=true;
 if(character==4)tuning.hover_gauge_cost=weapon==2?6:4;
 if(character==8)tuning.hover_gauge_cost=12;
 return tuning;
}
inline void advance_battle_falling_horizontal(float& speed,float& offset,int x,int z,const BattleJumpTuning& tuning){
 if(tuning.falling_speed_control){
  if(x||z)speed=std::min(6.f,speed+.2f);
  else speed=std::max(0.f,speed-.2f);
 }
 steer_battle_offset(offset,x,z,tuning.falling_turn);
}
// Returns requested state, or zero when the current state continues.
inline unsigned advance_battle_jump(BattleJumpMotion& p,const BattleJumpTuning& tuning){
 if(p.state==40){
  if(p.animation_complete)return 41;
  p.gauge=std::min(1000,p.gauge+(p.slow_recovery?5:40));
  p.gravity=0;p.speed=0;steer_battle_offset(p.offset,p.x,p.z,18.f);return 0;
 }
 if(p.state==41){
  if(p.phase==0&&p.frame==0){p.vertical=tuning.launch;p.held_ticks=0;if(p.x||p.z)p.speed=6.f;}
  if(p.vertical<6.f&&p.phase==1)return 42;
 }
 if(p.state>=41&&p.state<=43){
  if(p.grounded&&p.vertical<=0){p.vertical=0;if(p.state==43&&tuning.reset_landing_gravity)p.gravity=0;return 44;}
  if(p.state==43&&p.gravity==0)p.gravity=.5f;
  p.vertical=p.vertical-p.gravity;
  if(p.state==41){
   ++p.held_ticks;
   if(p.gravity==0)p.gauge=std::max(0,p.gauge-tuning.hover_gauge_cost);
   if(!p.button_ticks)p.held_ticks=0;
   if(!p.held_ticks||p.held_ticks>99||p.gauge<1)p.gravity=.5f;
  }else if(!p.button_ticks||p.button_ticks>59)p.gravity=.5f;
  if(p.state!=43){
   if(p.x||p.z)p.speed=std::min(p.state==41?tuning.ascent_speed:6.f,p.speed+.2f);
   else p.speed=std::max(0.f,p.speed-.2f);
  }
  if(p.state==43)advance_battle_falling_horizontal(p.speed,p.offset,p.x,p.z,tuning);
  else steer_battle_offset(p.offset,p.x,p.z,p.state==41?tuning.ascent_turn:tuning.falling_turn);
 }
 return 0;
}
inline unsigned advance_battle_jump(BattleJumpMotion& p,float launch_speed=12.f){
 BattleJumpTuning tuning;tuning.launch=launch_speed;return advance_battle_jump(p,tuning);
}
}
