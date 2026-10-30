#pragma once
#include "keiichi_ground_shot.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Character 6, weapon 0, states 410-413: original slot-6 handler 00516230.
// The four directions share a projectile but have different launch and brake
// frames. World offsets come from the original EXE's float constants.
inline GroundShotEffects advance_roster_ground_shot_followup410(
 unsigned character,unsigned weapon,unsigned state,unsigned phase,unsigned frame,
 bool complete,bool grounded,bool boosted,unsigned rounds,
 float& speed,float& offset,float& movement){
 if(character!=6||weapon!=0||state<410||state>413)
  throw std::invalid_argument("Unsupported shot410 binding");
 GroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){out.next_state=43;return out;}
 out.started=phase==0&&frame==0;
 if(state==411||state==412){
  if(frame<10)approach_battle_offset(offset,0.f,20.f);
  else if(frame<20)approach_battle_offset(offset,0.f,5.f);
  if(frame>25)speed=std::max(0.f,speed-.5f);
 }else if(state==413){
  if(frame<15)approach_battle_offset(offset,0.f,10.f);
  if(frame>20)speed=std::min(0.f,speed+.5f);
 }else if(frame>25)speed=std::max(0.f,speed-1.f);
 if(frame==0){
  if(state==410){movement=0.f;speed=15.f;}
  else if(state==411||state==412){movement=state==411?-90.f:90.f;speed=12.5f;}
  else {offset=0.f;movement=0.f;speed=-17.5f;}
 }
 if(frame==(state==413?15u:20u)){
  out.fire=true;out.effect=124;out.voice=rounds<2?30:27;
  out.bullet_slot=boosted?1u:0u;
  out.origin=GroundShotOrigin::World;
  out.origin_height=(state==411||state==412)?50.f:100.f;
  out.world_forward_x=out.world_forward_z=state==413?150.f:200.f;
  out.world_lateral=state==411?-100.f:state==412?100.f:0.f;
 }
 return out;
}
}
