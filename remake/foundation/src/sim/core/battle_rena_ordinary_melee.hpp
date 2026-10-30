#pragma once
#include "keiichi_attack300.hpp"
#include "battle_melee_voice.hpp"
#include "battle_attack300_motion.hpp"
#include "character_dispatch.hpp"
namespace daybreak {
struct BattleRenaOrdinaryEffects : KeiichiAttack300Effects {
 bool activate=false,reset_capacity=false;
 // Extra increments of BOTH +ae04 and +ae08, before the normal handler tail.
 unsigned extra_clock_ticks=0;
};
// 43ffc0/448220/438310 state300. +f0 is independent persistent scratch:
// weapon1 reads it without initializing it here. Do not replace it with +e8.
inline BattleRenaOrdinaryEffects advance_battle_rena_ordinary_melee(unsigned weapon,KeiichiAttack300& s,const KeiichiAttack300Input& in,int scratch_f0,float& gravity){
 character_action_dispatch(0,weapon);
 BattleRenaOrdinaryEffects out;
 if(in.animation_complete){out.next_state=0;return out;}
 if(!in.grounded){out.next_state=43;gravity=.5f;return out;}
 unsigned contact=in.contact;
 const bool first=s.phase==0&&s.frame==0;
 if(first){
  s.movement_angle=0;s.contact_seen=0;
  s.speed=weapon==2?0.f:in.distance_squared>=(weapon==1?810000.:640000.)?15.f:25.f;
  if(weapon!=2)s.moving=1;
  out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;contact=0;
 }
 if(contact&2){out.next_state=392;out.clear_contact=true;return out;}
 if(contact&&!s.contact_seen)s.contact_seen=1;
 if(weapon==2){
  if(s.phase==0){approach_battle_offset(s.offset,0.f,3.f);if(first)approach_battle_offset(s.offset,0.f,180.f);}
 }else{
  if(first)approach_battle_offset(s.offset,0.f,180.f);
  else if(s.phase<2)approach_battle_offset(s.offset,0.f,20.f);
  if(s.phase==1&&(in.distance_squared<90000.||s.moving==0||s.frame>10)){out.next_phase=2;return out;}
 }
 if(s.phase==(weapon==2?1:2)&&s.frame==(weapon==2?18:0)){
  out.effect=weapon==0?60:weapon==1?64:67;
  const auto voice=battle_melee_voice(weapon==2?3:1,in.distance_squared,s.offset,in.voice_flags);
  out.voice=voice.id;out.voice_argument=voice.argument;
 }
 if(weapon==2&&s.phase==1){
  BattleAttack300Motion motion{unsigned(s.phase),unsigned(s.frame),0,unsigned(s.moving),s.speed,s.offset};
  out.strike=advance_battle_attack300(motion);
  s.frame=int(motion.frame);s.moving=int(motion.moving);s.speed=motion.speed;s.offset=motion.offset;
  out.extra_clock_ticks=motion.secondary_frame;
 }else if(weapon!=2&&s.phase==2){
  if(s.frame<4&&(weapon==0?s.moving>0:scratch_f0==1))approach_battle_offset(s.offset,0.f,5.f);
  s.speed-=1.5f;if(s.speed<0)s.speed=0;
 }
 if(weapon!=2)out.strike=s.phase==2&&s.frame>2&&s.frame<11;
 return out;
}
}
