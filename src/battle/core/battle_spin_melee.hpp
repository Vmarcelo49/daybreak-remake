#pragma once
#include "battle_leap_melee.hpp"
namespace daybreak {
// Character9 state332, all weapons. +30 is roll; +f0 holds the launch-time
// distance gate. It must not be recomputed while spinning.
inline BattleLeapMeleeEffects advance_battle_spin_melee(unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float& roll){
 character_action_dispatch(9,weapon);BattleLeapMeleeEffects out;
 const auto transition=battle_dash_transition(9,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){
  apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);
  out.next_state=transition.state;out.next_phase=transition.phase;return out;
 }
 if(s.phase==0){
  s.speed=12.5f;
  if(s.frame==0)air.strength=in.distance_squared<640000.?1:0;
  if(air.strength==1)approach_battle_offset(s.offset,0,4);
 }
 if(s.phase==0&&s.frame==0){
  out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;
  s.movement_angle=air.vertical=0;
 }
 if(s.phase==1){
  roll+=5;
  if(s.frame==0){out.voice=3;out.voice_argument=10;}
  if(air.strength==1)approach_battle_offset(s.offset,0,4);
  if(s.frame%15==0)out.positional_sound=64;
  if(s.frame>60){out.next_state=43;return out;}
  air.vertical-=.2f;
 }
 if(s.phase==2){roll=0;s.speed=std::max(0.f,s.speed-.35f);}
 return out;
}
}
