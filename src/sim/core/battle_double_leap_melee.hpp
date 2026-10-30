#pragma once
#include "battle_leap_melee.hpp"
namespace daybreak {
struct BattleDoubleLeapEffects : BattleLeapMeleeEffects {bool continue_after_phase=false;};
// Character3 state332. Phase2's second landing changes phase immediately and
// continues through phase3 in the same update. Caller must preserve that order.
inline BattleDoubleLeapEffects advance_battle_double_leap(unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in){
 character_action_dispatch(3,weapon);BattleDoubleLeapEffects out;
 const auto transition=battle_dash_transition(3,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){out.next_state=transition.state;return out;}
 if(s.phase==0&&s.frame==0)out.activate=out.initialize=true;
 if(s.phase==0){
  approach_battle_offset(s.offset,0,10);s.speed=air.vertical=0;air.gravity=.75f;
  out.clear_contact=out.reset_capacity=true;s.moving=0;
 }
 if(s.phase==1){
  if(s.frame==0){out.voice=3;out.voice_argument=10;}
  approach_battle_offset(s.offset,0,10);s.speed=14.5f;
  if(s.frame>4){out.next_phase=2;return out;}
 }
 if(s.phase==2){
  if(s.frame%10==0)out.positional_sound=61;
  air.vertical-=air.gravity;
  if(in.grounded&&air.vertical<0){
   if(s.moving==0){out.initialize=out.clear_contact=out.reset_capacity=true;s.moving=1;air.vertical=15;}
   else {out.next_phase=3;out.continue_after_phase=true;s.phase=3;s.frame=0;air.vertical=air.gravity=0;}
  }
 }
 if(s.phase<3)approach_battle_offset(s.offset,0,2);
 if(s.phase==3){
  s.speed=std::max(0.f,s.speed-.65f);
  if(!in.grounded){out.next_state=43;return out;}
 }
 return out;
}
}
