#pragma once
#include "keiichi_directional.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {

// Original slot-6 handlers 00503510 (character 5) and 0055be80
// (character 11). Both use the same forward input state, but different
// braking schedules; only character 5 has the held-melee 313 follow-up.
inline KeiichiAttack300Effects advance_roster_forward_melee312(
 unsigned character,unsigned state,KeiichiAttack300& s,
 const KeiichiDirectionalInput& in,unsigned melee_held,unsigned melee_released,
 unsigned& followup_ticks){
 if(character==14&&(state==312||state==313)){
  // Original 5d5120, weapon 1: the two forward strikes share a clock with
  // different steering/braking magnitudes and contact windows.
  KeiichiAttack300Effects out;
  if(in.complete){out.next_state=0;return out;}
  if(!in.grounded){out.next_state=43;s.gravity=.5f;return out;}
  if(s.frame==0){s.speed=s.offset=s.movement_angle=0.f;
   out.initialize=out.clear_contact=true;out.contact_capacity=1;}
  const float turn=state==312?20.f:10.f;
  if(s.frame<(state==312?15u:14u))approach_battle_offset(s.offset,0.f,turn);
  if(s.frame==7)s.speed=35.f;
  if(s.frame==13){out.effect=62;out.voice=state==312?3:2;out.voice_argument=10;}
  if(s.frame>(state==312?18u:15u))s.speed=std::max(0.f,s.speed-(state==312?5.f:6.f));
  if(in.contact&2){out.next_state=392;out.clear_contact=true;}
  return out;
 }
 if((character!=5&&character!=11)||(state!=312&&state!=313)||(state==313&&character!=5))
  throw std::invalid_argument("Unsupported roster forward melee");
 KeiichiAttack300Effects out;
 if(in.complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;if(character==5)s.gravity=.5f;return out;}
 if(state==312){
  if(s.phase==0&&s.frame==0){s.movement_angle=0;s.speed=0;}
  if(s.phase==0&&s.frame==5)s.speed=character==5?-15.f:-20.f;
  if(character==5){
   if(s.frame>24){
    s.speed=std::min(0.f,s.speed+1.f);
    if(melee_held==3||(melee_released>0&&melee_released<3)){
     out.next_state=313;return out;
    }
   }
  }else{
   s.speed+=.5f;
   s.speed=s.frame<28?std::min(15.f,s.speed):std::min(0.f,s.speed);
  }
  if(s.frame<10)approach_battle_offset(s.offset,0.f,20.f);
  return out;
 }
 if(s.phase==0&&s.frame==0){
  s.movement_angle=0;s.speed=30;followup_ticks=0;
  approach_battle_offset(s.offset,0.f,180.f);
  out.initialize=out.clear_contact=true;out.contact_capacity=1;
  out.voice=3;out.voice_argument=10;
 }
 if(in.contact&2){out.next_state=392;out.clear_contact=true;return out;}
 if(s.phase<2){
  approach_battle_offset(s.offset,0.f,4.f);
  if(s.phase==1&&++followup_ticks>15){out.next_phase=2;return out;}
 }else s.speed=std::max(0.f,s.speed-1.f);
 return out;
}

}
