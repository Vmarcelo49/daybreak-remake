#pragma once
#include "battle_rena_ordinary_melee.hpp"
namespace daybreak {
struct BattleRenaFollowupEffects : BattleRenaOrdinaryEffects {int contact_mode=-1;};
// Original states301/302. Weapon1 has no state302 branch in 448220.
inline BattleRenaFollowupEffects advance_battle_rena_followup_melee(unsigned weapon,unsigned state,KeiichiAttack300& s,const KeiichiAttack300Input& in,float& gravity,float& turn_step){
 character_action_dispatch(0,weapon);
 if((state!=301&&state!=302)||(weapon==1&&state==302))throw std::invalid_argument("Unknown Rena followup melee state");
 BattleRenaFollowupEffects out;
 if(in.animation_complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;gravity=.5f;return out;}
 if(s.contact_seen){out.contact_mode=2;if(s.frame<(state==301?8:12))approach_battle_offset(s.offset,0.f,20.f);}
 unsigned contact=in.contact;
 if(s.frame==0){
  s.movement_angle=0;out.clear_contact=out.reset_capacity=true;contact=0;
  if(weapon==1)s.speed=10;
  if(s.phase==0)out.activate=out.initialize=true;
 }
 if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
 if(s.frame==(state==301?3:10)){
  out.effect=state==301?(weapon==1?67:61):(weapon==0?62:67);
  out.voice=state==301&&weapon!=1?2:3;out.voice_argument=10;
 }
 if(state==301){
  if(weapon==1){if(s.frame==8){s.speed=0;turn_step=0;}}
  else {if(s.frame==1){s.speed=10;turn_step=0;}if(s.frame==16){s.speed=0;turn_step=0;}}
 }else if(weapon==0){
  if(s.frame==0){s.speed=15;turn_step=0;}if(s.frame==17){s.speed=0;turn_step=0;}
 }else {
  if(s.frame<12)s.speed=0;
  if(s.frame==12){s.speed=10;turn_step=0;}if(s.frame==22){s.speed=0;turn_step=0;}
 }
 out.strike=state==301?s.frame>=10&&s.frame<=16:s.frame>=12&&s.frame<=17;
 return out;
}
}
