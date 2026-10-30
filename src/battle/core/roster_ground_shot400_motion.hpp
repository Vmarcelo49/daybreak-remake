#pragma once
#include "battle_steering.hpp"
#include "roster_ground_shot400_motion_schedule.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <stdexcept>

namespace daybreak {

inline std::uint32_t roster_shot400_motion_key(unsigned character,unsigned weapon,unsigned phase,unsigned frame){
 return character<<24|weapon<<16|phase<<8|frame;
}

// Returns the original handler's frame-counter advance. The caller owns the
// animation clock and handles scratch-dependent holds for specific fighters.
inline int advance_roster_ground_shot400_motion(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,float& speed,float& offset,float& movement){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1))
  throw std::invalid_argument("Unsupported roster state400 motion binding");
 const auto key=roster_shot400_motion_key(character,weapon,phase,frame);
 const auto first=std::lower_bound(std::begin(roster_shot400_motion_runs),std::end(roster_shot400_motion_runs),key,
  [](const RosterShot400MotionRun& run,std::uint32_t value){
   return roster_shot400_motion_key(run.character,run.weapon,run.phase,run.last)<value;
  });
 if(first==std::end(roster_shot400_motion_runs)||
    roster_shot400_motion_key(first->character,first->weapon,first->phase,first->first)>key)return 1;
 const auto& run=*first;
 switch(run.speed_mode){
  case RosterShot400SpeedMode::Keep:break;
  case RosterShot400SpeedMode::Brake:speed=std::max(0.f,speed-run.speed_value);break;
  case RosterShot400SpeedMode::Set:speed=run.speed_value;break;
 }
 switch(run.angle_mode){
  case RosterShot400AngleMode::Keep:break;
  case RosterShot400AngleMode::ResetMovement:movement=0;break;
  case RosterShot400AngleMode::ZeroOffset:offset=0;break;
  case RosterShot400AngleMode::ZeroAndReset:offset=0;movement=0;break;
  case RosterShot400AngleMode::Approach:approach_battle_offset(offset,0.f,run.turn1);break;
  case RosterShot400AngleMode::ApproachReset:approach_battle_offset(offset,0.f,run.turn1);movement=0;break;
  case RosterShot400AngleMode::Preserve:approach_battle_offset_preserving_movement(offset,movement,run.turn1);break;
  case RosterShot400AngleMode::PreserveSnap:{
   float delta=offset;if(delta< -180.f)delta+=360.f;if(delta>180.f)delta-=360.f;
   approach_battle_offset(offset,0.f,run.turn1);
   movement+=std::clamp(delta,-run.turn1,run.turn1);
   if(movement>180.f)movement-=360.f;if(movement< -180.f)movement+=360.f;
   break;
  }
  case RosterShot400AngleMode::DoublePreserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);
   break;
 }
 return run.frame_delta;
}

}
