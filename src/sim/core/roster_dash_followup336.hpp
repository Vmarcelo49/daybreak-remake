#pragma once
#include "keiichi_attack300.hpp"
#include <stdexcept>

namespace daybreak {
// Character 11's three weapons share the state336 body in the original
// slot-6 handlers 551410, 55be80 and 566a40.
inline KeiichiAttack300Effects advance_roster_dash_followup336(
 unsigned character,unsigned weapon,KeiichiAttack300& action,
 const KeiichiAttack300Input& input){
 if(character!=11||weapon>2)throw std::invalid_argument("Unsupported followup336 binding");
 KeiichiAttack300Effects out;
 if(input.animation_complete){out.next_state=0;return out;}
 if(action.phase==0&&!input.grounded){action.gravity=.5f;out.next_state=43;return out;}
 if(action.phase==0&&action.frame==0){
  out.initialize=out.clear_contact=true;
  action.speed=0.f;action.movement_angle=0.f;
  approach_battle_offset(action.offset,0.f,10.f);
 }
 if(action.phase==1&&action.frame==0){
  action.speed=10.f;action.vertical=27.5f;
 }
 if(action.phase>0){
  action.vertical-=1.25f;
  if(input.grounded&&action.vertical<0.f){
   out.next_state=44;action.gravity=0.f;action.vertical=0.f;
  }
 }
 return out;
}
}
