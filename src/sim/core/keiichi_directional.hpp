#pragma once
#include <algorithm>
#include <stdexcept>
#include "keiichi_attack300.hpp"
namespace daybreak {
struct KeiichiDirectionalInput {bool complete=false,grounded=true,jump=false;double distance_squared=0;unsigned contact=0;};
// 46a190/473610/47b940 states310/311 have identical bodies.
inline KeiichiAttack300Effects advance_keiichi_directional(unsigned state,KeiichiAttack300& s,const KeiichiDirectionalInput& in){
 KeiichiAttack300Effects out;
 if(in.complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;return out;}
 unsigned contact=in.contact;
 if(state==310){
  if(s.phase==0&&s.frame==0){s.movement_angle=0;s.moving=0;approach_battle_offset(s.offset,0,180);out.initialize=out.clear_contact=true;contact=0;}
  if(s.phase==0){approach_battle_offset(s.offset,0,20);s.speed=25;}
  if(s.phase==1){approach_battle_offset(s.offset,0,20);if(in.distance_squared<90000.||s.frame>6){out.next_phase=2;return out;}}
  if(s.phase==2){
   if(s.frame<6)approach_battle_offset(s.offset,0,15);
   if(s.frame==5)s.speed=0;
   if(s.frame==4){out.effect=62;out.voice=2;out.voice_argument=10;}
   if(s.frame>12&&(contact&1)&&in.jump){out.next_state=40;return out;}
  }
 }else if(state==311){
  if(s.phase==0){s.speed=std::max(0.f,s.speed-1.5f);if(s.frame<14)approach_battle_offset(s.offset,0,15);if(s.frame<32)approach_battle_offset(s.offset,0,10);}
  if(s.frame==0){out.clear_contact=out.initialize=true;contact=0;}
  if(s.frame==19){out.effect=62;out.voice=3;out.voice_argument=10;}
  if(s.frame==14){s.movement_angle=0;s.speed=30;}
  if(s.frame==32)s.speed=0;
  out.strike=s.frame>=16&&s.frame<=29;
 }else throw std::invalid_argument("Unsupported directional melee");
 if(contact&2){out.next_state=392;out.clear_contact=true;}
 return out;
}
}
