#pragma once
#include "battle_timed_dive_followup.hpp"
namespace daybreak {
// Original state334 across all46 configurations. The state number denotes
// several different actions; preserve the character/weapon-specific gates.
inline BattleTimedDiveFollowupEffects advance_battle_dash_followup(unsigned character,unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,int& gauge,float& turn_step,bool slowed,unsigned state=334){
 character_action_dispatch(character,weapon);
 if(state==339){
  if(character==7)return advance_battle_timed_dive_followup(339,weapon,air,s,in);
  BattleTimedDiveFollowupEffects out;
  // Character 10's DAT includes 339, but its original slot-6 handler has
  // no 339 case: it performs only the common animation tail.
  if(character==10)return out;
  if(character!=6&&character!=9)throw std::invalid_argument("Unknown state339 binding");
  if(in.grounded&&air.vertical<0.f){out.next_state=44;air.vertical=0.f;
   if(character==9&&weapon!=2)air.gravity=0.f;return out;}
  air.gravity=.5f;air.vertical-=air.gravity;
  if(s.frame>20)out.next_state=43;
  return out;
 }
 if(state!=334)throw std::invalid_argument("Unknown dash followup state");
 if(character==7)return advance_battle_timed_dive_followup(334,weapon,air,s,in);
 BattleTimedDiveFollowupEffects out;
 if(character==8){
  const auto result=advance_battle_leap_melee(334,weapon,air,s,in,gauge,turn_step,slowed);
  static_cast<BattleReboundMeleeEffects&>(out)=result;return out;
 }
 if(character==4&&weapon==2){
  out.camera=2;
  if(s.phase==0&&s.frame==0)out.clear_contact=out.reset_capacity=out.initialize=true;
  if(in.grounded&&air.vertical<=0){out.next_state=333;air.vertical=0;return out;}
  if(s.phase==1&&s.frame==0){out.voice=3;out.voice_argument=10;air.gravity=.45f;air.vertical=10;s.speed=-7;}
  if(s.phase==2&&s.frame>10){out.next_state=43;return out;}
  air.vertical-=air.gravity;return out;
 }
 if(character!=5&&character!=11&&s.phase==0&&air.vertical<6){out.next_phase=1;return out;}
 if(in.grounded&&air.vertical<=0){
  out.next_state=333;air.vertical=0;
  if((character==11&&weapon!=1)||(character==15&&weapon==1))air.gravity=0;
  return out;
 }
 if((character==6||character==9||character==15||(character==0&&weapon!=1))&&air.gravity==0)air.gravity=.5f;
 air.vertical-=air.gravity;return out;
}
}
