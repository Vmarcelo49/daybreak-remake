#pragma once
#include "keiichi_ground_shot.hpp"
#include <algorithm>
#include <cmath>
#include <vector>

namespace daybreak {
// Character11 weapons0/1, original slot-6 handlers 551410/55be80.
// Both regular and active-mode projectile slots follow controlled x86 visits.
inline GroundShotEffects advance_roster_ground_shot_followup420(
 unsigned character,unsigned weapon,unsigned phase,unsigned frame,
 bool complete,bool grounded,bool boosted,unsigned rounds,float elevation,
 float& speed,float& offset,
 std::vector<GroundShotEffects>& requests){
 if(character!=11||weapon>1)throw std::invalid_argument("Unsupported shot420 binding");
 requests.clear();GroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){out.next_state=43;return out;}
 if(phase==0){
  if(frame==0)out.started=true;
  if(frame<(weapon==0?25u:22u))approach_battle_offset(offset,0.f,10.f);
  speed=std::max(0.f,speed-.5f);
 }
 if(frame==(weapon==0?25u:22u)){
  out.effect=weapon==0?141:162;
  out.voice=weapon==0?(rounds<3?30:28):(rounds==1?30:27);
  out.fire=true;out.bullet_slot=weapon==0?(boosted?2u:1u):(boosted?1u:0u);
  out.pitch=std::clamp(float(std::nearbyint(elevation)),-30.f,30.f);
  out.attack_calls=weapon==0?2u:1u;
  if(weapon==0){
   out.origin=GroundShotOrigin::World;out.origin_height=75.f;
   out.world_forward_x=out.world_forward_z=10.f;
   out.world_lateral=40.f;requests.push_back(out);
   out.world_lateral=-40.f;requests.push_back(out);
  }
 }
 return out;
}
}
