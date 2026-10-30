#pragma once
#include "mion_melee.hpp"
#include "keiichi_air_melee.hpp"
#include "battle_rebound_melee.hpp"
#include "battle_dash_melee.hpp"
#include "battle_dash_followup.hpp"
#include "battle_chasing_air_melee.hpp"
namespace daybreak {
inline bool mion_mobile_melee_state(unsigned state){return state==320||(state>=329&&state<=334);}
inline MionMeleeEffects advance_mion_air320(unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float height_difference){
 const auto shared=advance_chasing_air_melee(chasing_air_melee_policy(1,weapon),air,s,in,height_difference);
 MionMeleeEffects out;static_cast<KeiichiAttack300Effects&>(out)=shared;out.activate=shared.activate;return out;
}
inline MionMeleeEffects advance_mion_mobile_melee(unsigned state,unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float height){
 if(weapon>2||!mion_mobile_melee_state(state))throw std::invalid_argument("Mion mobile melee state");
 if(state==320)return advance_mion_air320(weapon,air,s,in,height);
 MionMeleeEffects out;unsigned contact=in.contact;
 if(state==334){
  int gauge=0;float turn_step=0; // Mion334 does not change these fields.
  static_cast<KeiichiAttack300Effects&>(out)=advance_battle_dash_followup(1,weapon,air,s,in,gauge,turn_step,false);return out;
 }
 if(state==332){
  float roll=0; // Mion state332 does not access +30.
  const auto shared=advance_battle_dash_melee(1,weapon,air,s,in,height,roll);
  static_cast<KeiichiAttack300Effects&>(out)=shared;out.activate=shared.activate;out.reset_capacity=shared.reset_capacity;return out;
 }
 if(in.animation_complete){out.next_state=0;return out;}
 if(state==329||state==333){air.gravity=air.vertical=s.speed=s.movement_angle=0;return out;}
 if(!in.grounded){out.next_state=43;air.gravity=.5f;return out;}
 if(state==330){
  if(s.phase==0&&s.frame==0){out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;contact=0;s.movement_angle=0;}
  if(s.phase==2){
   if(s.frame==0){out.voice=2;out.voice_argument=10;if(in.distance_squared<40000&&std::abs(s.offset)<30)for(unsigned i=0;i<3;++i)if(in.voice_flags[i]==1){out.voice=i==0?0:i==1?15:5;out.voice_argument=12;break;}}
   s.speed=std::max(0.f,s.speed-2);
  }
  if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
  if(s.phase==0)approach_battle_offset(s.offset,0,10);
  if(s.phase==1){approach_battle_offset(s.offset,0,weapon==1?7.f:5.f);s.speed=20;}
  if(s.phase==2&&s.frame<5)approach_battle_offset(s.offset,0,5);
 }else {
  if(s.frame==0){out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;contact=0;s.offset=s.movement_angle;s.movement_angle=0;s.moving=0;air.strength=in.distance_squared<250000?1:0;s.speed=weapon==1?19.f:17.5f;}
  if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
  if(s.frame<14&&air.strength==1)approach_battle_offset(s.offset,0,weapon==1?22.f:20.f);
  if(s.frame==12){out.effect=61;out.voice=2;out.voice_argument=10;}
  if(s.frame>12)s.speed=std::max(0.f,s.speed-1.5f);
 }
 return out;
}
}
