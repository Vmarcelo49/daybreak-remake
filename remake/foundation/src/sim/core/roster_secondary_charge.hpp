#pragma once
#include "keiichi_ground_shot.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {

inline bool roster_secondary_charge_state(unsigned character,unsigned weapon,unsigned state){
 return (character==5&&weapon==2&&(state==451||state==461))||
        (character==15&&weapon==0&&(state==451||state==452||state==461||state==462));
}

// Charge callbacks that enter a second DAT state rather than completing the
// parent 450/460 animation. The two actor families come from 50aea0 and
// 5e2af0; projectile admission remains with DevelopmentAnimatedCombat.
inline GroundShotEffects advance_roster_secondary_charge(unsigned character,unsigned weapon,
 unsigned state,unsigned frame,bool complete,bool grounded,bool boosted,
 int& frame_delta,float& speed,float& offset,float& movement,float& vertical,float& gravity){
 if(!roster_secondary_charge_state(character,weapon,state))
  throw std::invalid_argument("Unsupported secondary charge state");
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;frame_delta=1;
 const bool air=state>=460;
 if(complete){out.next_state=air?43:0;frame_delta=0;return out;}
 if(!air&&!grounded){out.next_state=43;gravity=.5f;frame_delta=0;return out;}
 if(character==5){
  if(air&&grounded&&vertical<0){out.next_state=469;frame_delta=0;return out;}
  if(air&&frame==0)gravity=.5f;
  if(air&&frame>25)vertical-=gravity;
  if(!air)speed=std::max(0.f,speed-.5f);
  if(frame<13)approach_battle_offset_preserving_movement(offset,movement,2.f);
  if(frame==7&&!air)frame_delta=6;
  if(frame==13){
   out.effect=184;out.fire=true;out.attack_calls=1;out.count_attack=true;
   out.bullet_slot=boosted?5u:3u;
   out.origin=GroundShotOrigin::World;out.origin_height=100.f;
  }
  return out;
 }
 if(air){
  if(grounded&&frame>30){out.next_state=469;speed=vertical=gravity=0;frame_delta=0;return out;}
  if(frame<17)approach_battle_offset(offset,0.f,5.f);
  if(frame==17)out.voice=state==461?3:39;
  if(!grounded&&frame>30){gravity=.5f;vertical-=gravity;}
  return out;
 }
 if(frame<24)approach_battle_offset(offset,0.f,5.f);
 if((state==451&&frame==1)||(state==452&&frame==0))speed=40.f;
 speed=frame==24?0.f:std::max(0.f,speed-1.5f);
 if(frame==17)out.voice=state==451?29:39;
 return out;
}

} // namespace daybreak
