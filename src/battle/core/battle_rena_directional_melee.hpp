#pragma once
#include "battle_rena_ordinary_melee.hpp"
#include <algorithm>
namespace daybreak {
// States310/311 in43ffc0,448220,438310. Service order matters: weapon2's
// state311 checks guard contact before frame-zero clearing, unlike the others.
inline BattleRenaOrdinaryEffects advance_battle_rena_directional_melee(unsigned weapon,unsigned state,KeiichiAttack300& s,const KeiichiAttack300Input& in,bool jump_held,float& gravity){
 character_action_dispatch(0,weapon);
 if(state!=310&&state!=311)throw std::invalid_argument("Unknown Rena directional melee state");
 BattleRenaOrdinaryEffects out;
 if(in.animation_complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;gravity=.5f;return out;}
 unsigned contact=in.contact;
 auto guard=[&](){if(contact&2){out.next_state=392;out.clear_contact=true;return true;}return false;};
 auto reset=[&](){s.movement_angle=0;out.clear_contact=out.reset_capacity=true;contact=0;};
 if(state==310){
  if(s.phase==0&&s.frame==0){reset();s.speed=30;s.moving=0;approach_battle_offset(s.offset,0.f,180.f);out.activate=out.initialize=true;}
  if(guard())return out;
  if(weapon==2){
   if(s.frame>5&&s.frame<25)s.speed=std::max(0.f,s.speed-2.f);
   if(s.frame==25)s.speed=-5;
   if(s.frame==47)s.speed=0;
   if(s.frame<30)approach_battle_offset(s.offset,0.f,10.f);
   if(s.frame==25){out.effect=68;out.voice=3;out.voice_argument=10;}
   out.strike=s.frame>=24&&s.frame<=45;
  }else{
   if(s.phase==0)approach_battle_offset(s.offset,0.f,20.f);
   if(s.phase==1){approach_battle_offset(s.offset,0.f,15.f);if(s.frame>=0){out.next_phase=2;return out;}}
   if(s.phase==2){
    s.speed-=1.f;if(s.speed<0||s.frame==5)s.speed=0;
    if(s.frame<5)approach_battle_offset(s.offset,0.f,5.f);
    if(s.frame==4){out.effect=62;out.voice=2;out.voice_argument=10;}
    out.strike=s.frame>=5&&s.frame<=7;
    if(s.frame>12&&(contact&1)&&jump_held){out.next_state=40;return out;}
   }
  }
 }else{
  if(weapon==2&&guard())return out;
  if(weapon==0&&s.phase==0){s.speed=std::max(0.f,s.speed-.2f);if(s.frame<20)approach_battle_offset(s.offset,0.f,10.f);}
  if(s.frame==0){
   s.speed=weapon==2?0:20;reset();approach_battle_offset(s.offset,0.f,180.f);
   if(weapon==1||s.phase==0)out.activate=out.initialize=true;
  }
  if(s.frame==(weapon==2?35:12)){out.effect=weapon==0?62:weapon==1?67:68;out.voice=3;out.voice_argument=10;}
  if(weapon==0){if(s.frame==25)s.speed=0;}
  else if(weapon==1){if(s.frame<10)approach_battle_offset(s.offset,0.f,9.f);if(s.frame>17)s.speed=std::max(0.f,s.speed-2.f);}
  else {if(s.frame==27)s.speed=20;if(s.frame==47)s.speed=0;}
  if(guard())return out;
  out.strike=weapon==1?s.frame>=12&&s.frame<=18:weapon==2&&s.frame>=32&&s.frame<=49;
 }
 return out;
}
}
