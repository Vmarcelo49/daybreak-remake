#pragma once
#include "battle_rena_ordinary_melee.hpp"
#include "keiichi_air_melee.hpp"
#include "battle_dash_recovery.hpp"
namespace daybreak {
inline BattleRenaOrdinaryEffects advance_rena_ground_dash(unsigned weapon,unsigned state,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float& turn,int& gauge,bool slowed){
 character_action_dispatch(0,weapon);
 if(state!=329&&state!=330&&state!=331)throw std::invalid_argument("Rena ground dash state not recovered");
 BattleRenaOrdinaryEffects out;
 if(state==329){
  BattleDashRecovery recovery{air.vertical,air.gravity,s.speed,s.movement_angle,turn,gauge};
  out.next_state=advance_battle_dash_recovery(recovery,0,weapon,in.animation_complete,slowed);
  air.vertical=recovery.vertical;air.gravity=recovery.gravity;s.speed=recovery.speed;s.movement_angle=recovery.movement_angle;turn=recovery.turn_step;gauge=recovery.gauge;return out;
 }
 if(in.animation_complete){out.next_state=0;return out;}
 const bool hopping=state==330&&weapon==1;
 if(!in.grounded&&(!hopping||s.phase==0||s.phase==3)){out.next_state=43;air.gravity=.5f;return out;}
 if(hopping&&in.grounded&&(s.phase==1||s.phase==2)&&air.vertical<0){out.next_phase=3;s.speed=air.vertical=0;return out;}
 unsigned contact=in.contact;
 if(s.phase==0&&s.frame==0){
  out.initialize=out.activate=out.clear_contact=out.reset_capacity=true;contact=0;s.moving=0;
  if(state==331){
   s.offset=s.movement_angle;air.strength=in.distance_squared<(weapon==1?640000.:810000.)?1:0;
   if(weapon!=2)s.speed=air.strength==1?20.f:17.5f;
  }
  s.movement_angle=0;
 }
 if(!hopping&&(contact&2)){out.next_state=392;out.clear_contact=true;return out;}
 auto voice=[&](int ordinary,double distance_limit){
  out.voice=ordinary;out.voice_argument=10;
  if(in.distance_squared<distance_limit&&std::abs(s.offset)<30.f)for(unsigned i=0;i<3;++i)if(in.voice_flags[i]==1){out.voice=i==0?0:i==1?15:5;out.voice_argument=12;break;}
 };
 if(state==330){
  if(weapon==0){
   if(s.phase==0||s.phase==1)approach_battle_offset(s.offset,0,5);
   if(s.phase==1){s.speed=30;turn=0;}
   if(s.phase==2){s.speed=std::max(0.f,s.speed-2);if(s.frame==6){voice(2,40000);out.effect=62;}}
   out.strike=s.phase==2&&s.frame>5&&s.frame<10;
  }else if(weapon==1){
   if(s.phase==0){s.speed=std::max(0.f,s.speed-.5f);approach_battle_offset(s.offset,0,5);}
   if(s.phase==1&&s.frame==0){s.speed=15;air.vertical=15;air.gravity=.75f;voice(3,40000);}
   if(s.phase==1)s.speed=std::max(0.f,s.speed-.5f);
   if(s.phase==1||s.phase==2)air.vertical-=air.gravity;
   out.strike=(s.phase==0&&s.frame>10)||(s.phase==1&&s.frame<20);
  }else{
   if(s.frame<28)approach_battle_offset(s.offset,0,3);
   s.speed=std::max(0.f,s.speed-(s.frame<28?1.5f:2.f));
   if(s.frame==28){s.speed=40;voice(3,160000);out.effect=62;}
   out.strike=s.frame>=28&&s.frame<=34;
  }
 }else if(weapon!=2){
  if(s.phase<2&&air.strength==1)approach_battle_offset(s.offset,0,20);
  if(s.phase==2&&s.frame<10&&air.strength==1)approach_battle_offset(s.offset,0,10);
  if(s.phase==1&&s.frame>2&&(in.distance_squared<90000.||air.strength==0)){out.next_phase=2;return out;}
  if(s.phase>1)s.speed=std::max(0.f,s.speed-.5f);
  if(s.phase==2&&s.frame==10){out.voice=2;out.voice_argument=10;}
 }else{
  if(s.frame<21&&air.strength==1)approach_battle_offset_preserving_movement(s.offset,s.movement_angle,10);
  if(s.frame>103||s.frame<36)s.speed=std::max(0.f,s.speed-.75f);
  if(s.frame==35){out.voice=3;out.voice_argument=10;s.speed=10;s.movement_angle=0;}
  if(s.frame>=26&&s.frame<=109){approach_battle_offset(s.offset,0,2);out.strike=true;}
 }
 return out;
}
}
