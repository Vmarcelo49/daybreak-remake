#pragma once
#include "keiichi_air_melee.hpp"
namespace daybreak {
struct BattleReboundMeleeEffects : KeiichiAttack300Effects {
 bool activate=false,reset_capacity=false;
 bool update_magazine_0_mode_2=false; // Must run before early-return effects.
};
inline bool battle_tracking_rebound_configuration(unsigned character,unsigned weapon){
 return (character==4&&weapon<2)||(character==13&&weapon<3)||(character==14&&weapon<2);
}
// State332's second rebound family. Original ordered bounds (-10 then -2)
// collapse the target-derived vertical velocity to -2, not a [-10,-2] clamp.
inline BattleReboundMeleeEffects advance_battle_tracking_rebound(unsigned character,unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in){
 character_action_dispatch(character,weapon);
 if(!battle_tracking_rebound_configuration(character,weapon))throw std::invalid_argument("Unrecovered tracking rebound family");
 BattleReboundMeleeEffects out;out.update_magazine_0_mode_2=character==13;
 const auto transition=battle_dash_transition(character,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);out.next_state=transition.state;return out;}
 if(s.phase==0&&s.frame==0)out.activate=out.initialize=true;
 if(s.phase==0)approach_battle_offset(s.offset,0,5);
 if(s.phase==0&&s.frame==0){s.moving=0;s.speed=s.movement_angle=air.vertical=0;out.clear_contact=out.reset_capacity=true;}
 if(s.phase==1){
  ++s.moving;s.speed=25;air.vertical=-2;++s.moving;
  if(in.contact){air.vertical=10;s.speed=-7;air.gravity=.35f;out.next_state=334;out.clear_contact=out.reset_capacity=true;return out;}
  if(s.moving>45){s.moving=0;out.next_phase=2;return out;}
 }
 if(s.phase==2&&++s.moving>20){s.moving=0;out.next_phase=3;s.speed=10;return out;}
 if(s.phase>1){air.vertical-=air.gravity;s.speed=std::max(0.f,s.speed);}
 return out;
}
// Original state332 family: character1,10,12, all weapons. The latter two
// deliberately omit 423000 (attack statistics), despite sharing the movement.
inline BattleReboundMeleeEffects advance_battle_rebound_dash(unsigned character,unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in){
 character_action_dispatch(character,weapon);
 if(character!=1&&character!=10&&character!=12)throw std::invalid_argument("Unrecovered rebound dash family");
 BattleReboundMeleeEffects out;
 const auto transition=battle_dash_transition(character,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){
  apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);
  out.next_state=transition.state;return out;
 }
 unsigned contact=in.contact;
 if(s.phase==0&&s.frame==0){out.activate=true;out.initialize=character==1;}
 if(s.phase==0)approach_battle_offset(s.offset,0,5);
 if(s.phase==0&&s.frame==0){s.moving=0;s.speed=s.movement_angle=air.vertical=0;out.clear_contact=out.reset_capacity=true;contact=0;}
 if(s.phase==1){
  ++s.moving;s.speed=25;air.vertical=-8;
  if(contact){air.vertical=10;s.speed=-7;air.gravity=.35f;out.next_state=334;out.clear_contact=out.reset_capacity=true;return out;}
  if(s.moving>30){out.next_phase=2;s.speed=10;return out;}
 }
 if(s.phase>1){air.vertical-=air.gravity;s.speed=std::max(0.f,s.speed);}
 return out;
}
// Shared state334 rebound. Completion is intentionally not checked here.
inline KeiichiAttack300Effects advance_battle_rebound_air(KeiichiAirMelee& air,const KeiichiAttack300& s,const KeiichiAttack300Input& in){
 KeiichiAttack300Effects out;
 if(air.vertical<6&&s.phase==0){out.next_phase=1;return out;}
 if(in.grounded&&air.vertical<=0){out.next_state=333;air.vertical=0;return out;}
 air.vertical-=air.gravity;return out;
}
}
