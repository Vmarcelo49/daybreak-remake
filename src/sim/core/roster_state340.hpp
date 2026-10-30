#pragma once
#include "keiichi_attack300.hpp"
#include "roster_state340_schedule.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {

// Recovered landing-combo motion. The frame policy is compressed from all
// 46 original slot-6 handlers rather than guessed from one character.
inline KeiichiAttack300Effects advance_roster_state340(
 unsigned character,unsigned weapon,KeiichiAttack300& motion,
 const KeiichiAttack300Input& input){
 KeiichiAttack300Effects out;
 if(input.animation_complete){out.next_state=0;return out;}
 if(!input.grounded){
  motion.gravity=.5f;
  if(character==15){motion.speed=10.f;motion.vertical=0.f;}
  out.next_state=43;return out;
 }
 const RosterState340Step* step=nullptr;
 for(const auto& candidate:roster_state340_steps){
  if(candidate.character!=character||candidate.weapon!=weapon||candidate.phase!=motion.phase)continue;
  step=&candidate;
  if(motion.frame<=candidate.last)break;
 }
 if(!step)throw std::invalid_argument("Unsupported state340 binding or DAT phase");
 if(step->speed_mode==1)motion.speed=step->speed_value;
 else if(step->speed_mode==2)motion.speed=std::max(0.f,motion.speed-step->speed_value);
 if(step->offset_mode==1)motion.offset=step->offset_value;
 else if(step->offset_mode==2)approach_battle_offset(motion.offset,0.f,step->offset_value);
 if(step->movement_mode==1)motion.movement_angle=step->movement_value;
 out.effect=step->effect;out.voice=step->voice;
 if(out.voice>=0)out.voice_argument=10;
 out.initialize=out.clear_contact=step->initialize;
 return out;
}

} // namespace daybreak
