#pragma once
#include "battle_rebound_melee.hpp"
namespace daybreak {
struct BattleLeapMeleeEffects : BattleReboundMeleeEffects {int positional_sound=-1;};
// Character8, all three weapons: state332 leap and state334 early landing.
// Unlike the rebound family, state334 here is a grounded recovery handler.
inline BattleLeapMeleeEffects advance_battle_leap_melee(unsigned state,unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,int& gauge,float& turn_step,bool slowed){
 character_action_dispatch(8,weapon);
 if(state!=332&&state!=334)throw std::invalid_argument("Unrecovered leap melee state");
 BattleLeapMeleeEffects out;
 if(state==334){
  if(in.animation_complete){out.next_state=0;return out;}
  air.gravity=air.vertical=s.movement_angle=turn_step=s.speed=0;
  gauge=std::min(1000,gauge+(slowed?5:40));return out;
 }
 const auto transition=battle_dash_transition(8,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){
  apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);
  out.next_state=transition.state;out.next_phase=transition.phase;out.positional_sound=transition.positional_sound;return out;
 }
 if(s.phase==0)approach_battle_offset(s.offset,0,20);
 if(s.phase==1)approach_battle_offset(s.offset,0,2);
 if(s.phase<2)air.vertical-=air.gravity;
 if(s.phase==2){
  s.speed=std::max(0.f,s.speed-1);
  if(!in.grounded){out.next_state=43;air.gravity=.5f;return out;}
 }
 // Launch initialization follows gravity and is skipped by an early landing.
 if(s.phase==0&&s.frame==0){
  out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;
  s.speed=17.5f;air.vertical=15;s.movement_angle=0;air.gravity=1;
 }
 return out;
}
}
