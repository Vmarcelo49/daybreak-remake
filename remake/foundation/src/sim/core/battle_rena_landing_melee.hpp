#pragma once
#include "battle_rena_followup_melee.hpp"
#include "keiichi_air_melee.hpp"
namespace daybreak {
// 43ffc0/448220/438310 states340/341. Handler availability is distinct
// from input admission; weapon2's ordinary input does not select these states.
inline BattleRenaFollowupEffects advance_rena_landing_melee(unsigned weapon,unsigned state,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float& turn){
 character_action_dispatch(0,weapon);
 if((state!=340&&state!=341)||(weapon==1&&state==341))throw std::invalid_argument("Unknown Rena landing melee state");
 BattleRenaFollowupEffects out;
 if(in.animation_complete){out.next_state=0;return out;}
 if(!in.grounded&&(state==340||s.phase==0||s.phase==3)){out.next_state=43;air.gravity=.5f;return out;}
 const bool first=s.phase==0&&s.frame==0;
 unsigned contact=in.contact;
 if(first){out.activate=out.initialize=true;if(state==340&&weapon!=1)s.contact_seen=0;}
 if(state==340&&weapon!=1&&contact&&!s.contact_seen)s.contact_seen=1;
 out.contact_mode=2;
 if((state==340&&s.frame==0)||(state==341&&first)){s.movement_angle=0;out.clear_contact=out.reset_capacity=true;contact=0;}
 if(state==340){
  if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
  if(s.frame==(weapon==1?12:15)){out.effect=weapon==1?67:61;out.voice=weapon==1?3:2;out.voice_argument=10;}
  if(s.frame<(weapon==1?8:10))approach_battle_offset(s.offset,0,weapon==1?6.f:18.f);
  if(s.frame==0)s.speed=weapon==1?10.f:15.f;
  if(s.frame==15){s.speed=0;turn=0;}
  out.strike=weapon==1?s.frame>=10&&s.frame<=16:s.frame>=16&&s.frame<=24;
 }else{
  if(s.phase==0&&s.frame<5){s.speed=weapon==2?10.f:15.f;if(s.contact_seen==1)approach_battle_offset(s.offset,0,20);}
  if(s.phase==1&&s.frame==0){s.speed=10;air.vertical=18;air.gravity=.75f;turn=0;out.voice=3;out.voice_argument=10;}
  if(s.phase>0){
   air.vertical-=air.gravity;
   if(s.phase<3&&in.grounded&&air.vertical<0){air.vertical=s.speed=0;if(weapon==2)air.gravity=0;out.next_phase=3;return out;}
  }
  out.strike=s.phase==1&&s.frame<20;
 }
 return out;
}
}
