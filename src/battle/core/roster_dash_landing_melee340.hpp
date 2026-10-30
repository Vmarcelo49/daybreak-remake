#pragma once
#include "roster_ground_dash_melee.hpp"

namespace daybreak {
// Character4 weapons0/1, slot-6 handlers 484be0/492f70, state340.
inline KeiichiAttack300Effects advance_roster_dash_landing_melee340(
 unsigned character,unsigned weapon,KeiichiAttack300& action,
 const KeiichiAttack300Input& input){
 character_action_dispatch(character,weapon);
 if(character!=4||weapon>=2)throw std::invalid_argument("Unsupported state340 binding");
 KeiichiAttack300Effects out;
 if(input.animation_complete){out.next_state=0;return out;}
 if(!input.grounded){out.next_state=43;action.gravity=.5f;return out;}
 if(action.phase==0&&action.frame==0){
  out.initialize=out.clear_contact=true;
  action.movement_angle=0;action.contact_seen=0;
 }
 if(action.phase==0){
  approach_battle_offset(action.offset,0,5.f);
  if(action.frame==4)action.speed=15.f;
  if(action.frame==10){
   out.effect=61;
   const auto voice=roster_ground_dash_voice(2,input,action.offset);
   out.voice=voice.id;out.voice_argument=voice.argument;
  }
 }else if(action.phase==1)approach_battle_offset(action.offset,0,1.f);
 else if(action.phase==2)action.speed=std::max(0.f,action.speed-.75f);
 return out;
}
}
