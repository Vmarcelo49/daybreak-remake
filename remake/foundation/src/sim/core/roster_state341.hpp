#pragma once
#include "keiichi_attack300.hpp"
#include "roster_state341_schedule.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {

// Shared motion evaluator for the original roster's state341 handlers.
// Per-binding frame commands are generated from the original executable;
// airborne landing families are explicit original control branches.
inline KeiichiAttack300Effects advance_roster_state341(
 unsigned character,unsigned weapon,KeiichiAttack300& motion,
 const KeiichiAttack300Input& input){
 KeiichiAttack300Effects out;
 if(input.animation_complete){out.next_state=0;return out;}
 const bool airborne_motion=(character==0&&weapon==0&&motion.phase>=1&&motion.phase<=2)||
  (character==3&&motion.phase<2)||
  (character==5&&(motion.phase==1||motion.phase==2))||
  (character==8&&motion.phase<2);
 if(!input.grounded&&!airborne_motion){
  motion.gravity=.5f;
  if(character==15){motion.speed=10.f;motion.vertical=0.f;}
  out.next_state=43;return out;
 }
 const RosterState341Step* step=nullptr;
 for(const auto& candidate:roster_state341_steps){
  if(candidate.character!=character||candidate.weapon!=weapon||candidate.phase!=motion.phase)continue;
  step=&candidate;
  if(motion.frame<=candidate.last)break;
 }
 if(!step)throw std::invalid_argument("Unsupported state341 binding or DAT phase");
 bool landing=false;
 if(step->vertical_mode==3){
  if(!airborne_motion||
     !(step->speed_mode==3&&(character==0||character==3||character==5)||
       step->speed_mode==0&&character==8&&motion.phase==1))
   throw std::invalid_argument("Unknown state341 motion branch");
  motion.vertical-=motion.gravity;
  landing=input.grounded&&motion.vertical<0.f;
  if(landing){
   motion.vertical=0.f;
   out.next_phase=character==0||character==5?3:2;
   if(character==8){/* original preserves horizontal speed and gravity */}
   else if(character==0)motion.speed=0.f;
   else {motion.speed=motion.gravity=0.f;if(character==3)out.effect=40;}
  }
 }else{
  if(step->speed_mode==1)motion.speed=step->speed_value;
  else if(step->speed_mode==2)motion.speed=std::max(0.f,motion.speed-step->speed_value);
  if(step->vertical_mode==1)motion.vertical=step->vertical_value;
  else if(step->vertical_mode==2){
   if(((character==0&&weapon==0)||character==5)&&motion.phase==3)
    motion.vertical-=motion.gravity;
   else motion.vertical+=step->vertical_value;
  }
 }
 if(step->offset_mode==1)motion.offset=step->offset_value;
 else if(step->offset_mode==2)approach_battle_offset(motion.offset,0.f,step->offset_value);
 if(step->movement_mode==1)motion.movement_angle=step->movement_value;
 if(character==0&&weapon==0&&motion.phase==1&&motion.frame==0)motion.gravity=.75f;
 if(character==3&&motion.phase==0&&motion.frame==8)motion.gravity=1.f;
 if(character==5&&motion.phase==1&&motion.frame==0)motion.gravity=1.25f;
 if(character==8&&motion.phase==0&&motion.frame==10)motion.gravity=.6f;
 if(landing)return out;
 out.effect=step->effect;out.voice=step->voice;
 if(out.voice>=0)out.voice_argument=10;
 out.initialize=out.clear_contact=step->initialize;
 return out;
}

} // namespace daybreak
