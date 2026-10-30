#pragma once
#include "keiichi_attack300.hpp"
#include <stdexcept>
#include <algorithm>
namespace daybreak {
// Mion4582a0/461810/44fa10 ground melee. Caller owns clocks and DAT contacts.
inline bool mion_melee_state(unsigned state){return state==300||state==301||(state>=310&&state<=312)||state==340||state==341;}
struct MionMeleeEffects : KeiichiAttack300Effects {bool activate=false,reset_capacity=false;int camera=-1;};
inline MionMeleeEffects advance_mion_melee(unsigned state,unsigned weapon,KeiichiAttack300& s,const KeiichiAttack300Input& in){
 if(!mion_melee_state(state)||weapon>2)throw std::invalid_argument("Mion melee policy");
 MionMeleeEffects out;
 if(in.animation_complete){out.next_state=0;return out;}
 if(!in.grounded){if(state==301&&s.speed>10)s.speed=10;out.next_state=43;return out;}
 unsigned contact=in.contact;
 if(state==340||state==341){
  if(s.phase==0&&s.frame==0){out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;contact=0;s.movement_angle=0;s.speed=state==341&&weapon==1?16.f:15.f;if(state==340)s.contact_seen=0;}
  if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
  if(state==340&&contact&&!s.contact_seen)s.contact_seen=1;
  if(s.frame==8){out.effect=61;out.voice=state==340?2:3;out.voice_argument=10;}
  if(s.frame<8&&(state==340||s.contact_seen==1))approach_battle_offset(s.offset,0,state==340?(weapon==1?30.f:25.f):20.f);
  if(s.phase==0)s.speed=std::max(0.f,s.speed-1.f);
  return out;
 }
 if(state>=310){
  if(s.phase==0&&s.frame==0)out.activate=out.initialize=true;
  if(state==310){
   if(s.phase==0&&s.frame==0){s.movement_angle=0;out.clear_contact=out.reset_capacity=true;contact=0;s.moving=0;s.speed=weapon==1?19.f:17.5f;approach_battle_offset(s.offset,0,180);}
   if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
   if(s.phase==0)approach_battle_offset(s.offset,0,20);
   if(s.phase==1){approach_battle_offset(s.offset,0,15);if(in.distance_squared<40000){out.next_phase=2;return out;}}
   if(s.phase==2&&s.frame<15){approach_battle_offset(s.offset,0,5);s.speed=std::max(0.f,s.speed-1.5f);}
   if(s.phase==2&&s.frame==12){out.effect=60;out.voice=3;out.voice_argument=10;}
  }else {
   if(s.frame<10)approach_battle_offset(s.offset,0,weapon==1?20.f:18.f);
   if(s.frame==0){s.speed=0;s.movement_angle=0;out.clear_contact=out.reset_capacity=true;contact=0;approach_battle_offset(s.offset,0,180);}
   if(state==311){
    if(s.frame==5)s.speed=weapon==1?20.f:15.f;
    if(s.frame==9){out.voice=1;out.voice_argument=10;}
    if(s.frame==16)s.speed=0;
   }else {
    if(s.frame==0)s.speed=weapon==1?18.f:16.5f;
    if(s.frame==12){out.effect=61;out.voice=2;out.voice_argument=10;}
    if(s.frame>13)s.speed=std::max(0.f,s.speed-3.f);
   }
   if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
  }
  return out;
 }
 if(state==300){
  if(s.phase==0&&s.frame==0){
   out.activate=out.initialize=out.clear_contact=true;contact=0;
   approach_battle_offset(s.offset,0,180);s.movement_angle=0;s.moving=1;s.contact_seen=0;
   s.speed=in.distance_squared<360000?(weapon==1?19.f:17.f):(weapon==1?15.f:14.f);
  }
  if(contact&&!s.contact_seen)s.contact_seen=1;
  if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
  if(s.phase<2&&s.moving==1)approach_battle_offset(s.offset,0,weapon==1?5.f:4.f);
  if(s.phase==1&&(in.distance_squared<20000||!s.moving||s.frame>15)){out.next_phase=2;return out;}
  if(s.phase==2&&s.frame==0){out.effect=60;out.voice=1;out.voice_argument=10;
   if(in.distance_squared<40000&&std::abs(s.offset)<30){for(unsigned i=0;i<3;++i)if(in.voice_flags[i]==1){out.voice=i==0?0:i==1?15:5;out.voice_argument=12;break;}}
  }
  if(s.phase==2&&s.frame==2)s.speed=0;
 }else {
  if(s.contact_seen){out.camera=2;if(s.frame<8)approach_battle_offset(s.offset,0,15);if(s.frame>16&&s.frame<28)approach_battle_offset(s.offset,0,5);}
  if(s.phase==0&&s.frame==0){out.activate=out.initialize=out.clear_contact=true;contact=0;s.movement_angle=0;s.speed=30;}
  if(s.frame==10)s.speed=0;
  if(s.frame==16){out.initialize=out.clear_contact=true;contact=0;s.movement_angle=0;s.speed=30;}
  if(s.frame==29){out.effect=61;out.voice=2;out.voice_argument=10;s.speed=0;}
  if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
  if(s.frame<16){s.speed=std::max(0.f,s.speed-1);if(s.frame==3)out.effect=61;}
 }
 return out;
}
}
