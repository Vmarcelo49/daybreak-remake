#pragma once
#include "keiichi_ground_shot.hpp"
#include <stdexcept>

namespace daybreak {

// State361/362 recovery shared by the full-charge handlers that request it.
// Character5/weapon0 has a falling/landing recovery. Ohishi and Natsumi have
// separate held-victim landing routes; the remaining routes immobilize.
inline GroundShotEffects advance_roster_full_shot_followup(unsigned character,
 unsigned weapon,unsigned state,unsigned frame,bool complete,bool grounded,
 int& frame_delta,float& speed,float& movement,float& vertical,float& gravity){
 const bool air_recovery=character==5&&weapon==0&&state==361;
 const bool ohishi_held_landing=character==8&&weapon==1&&state==361;
 const bool natsumi_held_landing=character==15&&weapon==0&&state==361;
 const bool fixed_recovery=(character==7&&weapon==1&&state==361)||
                       (character==8&&weapon==2&&state==362)||
                       (character==11&&weapon==0&&state==361);
 if(!air_recovery&&!ohishi_held_landing&&!natsumi_held_landing&&!fixed_recovery)
  throw std::invalid_argument("Unsupported roster full-shot recovery");
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
 frame_delta=1;
 if(ohishi_held_landing||natsumi_held_landing){
  if(grounded&&vertical<0){out.next_state=ohishi_held_landing?351:469;
   vertical=0;if(ohishi_held_landing)speed=0;else gravity=0;
   frame_delta=0;return out;}
  if(natsumi_held_landing){if(gravity==0)gravity=.5f;vertical-=gravity;
   if(frame>20){out.next_state=43;frame_delta=0;}}
  else vertical-=.5f;
  return out;
 }
 if(complete){out.next_state=air_recovery?43:0;frame_delta=0;
  if(air_recovery)gravity=.5f;
  return out;
 }
 if(air_recovery){
  if(grounded){out.next_state=469;vertical=gravity=0;frame_delta=0;return out;}
  if(frame==0){speed*=.5f;movement=0;gravity=.5f;}
  vertical-=gravity;
  return out;
 }
 speed=movement=vertical=gravity=0;
 return out;
}

} // namespace daybreak
