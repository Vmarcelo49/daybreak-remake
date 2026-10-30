#pragma once
#include "battle_steering.hpp"
#include "roster_directional_motion_schedule.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>

namespace daybreak {

inline std::uint64_t roster_directional_motion_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame){
 return (std::uint64_t(character)<<48)|(std::uint64_t(weapon)<<40)|
        (std::uint64_t(state)<<24)|(std::uint64_t(phase)<<16)|frame;
}

inline int advance_roster_directional_shot_motion(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,float& speed,float& offset,float& movement){
 const auto key=roster_directional_motion_key(character,weapon,state,phase,frame);
 const auto first=std::lower_bound(std::begin(roster_directional_motion_runs),
  std::end(roster_directional_motion_runs),key,
  [](const RosterDirectionalMotionRun& run,std::uint64_t value){
   return roster_directional_motion_key(run.character,run.weapon,run.state,run.phase,run.last)<value;
  });
 if(first==std::end(roster_directional_motion_runs)||
    roster_directional_motion_key(first->character,first->weapon,first->state,first->phase,first->first)>key)return 1;
 const auto& run=*first;
 switch(run.speed_mode){
  case RosterDirectionalSpeedMode::Keep:break;
  case RosterDirectionalSpeedMode::Set:speed=run.speed_value;break;
  case RosterDirectionalSpeedMode::BrakePositive:speed=std::max(0.f,speed-run.speed_value);break;
  case RosterDirectionalSpeedMode::BrakeReverse:speed=speed<0?std::min(0.f,speed+run.speed_value):0.f;break;
 }
 switch(run.angle_mode){
  case RosterDirectionalAngleMode::Keep:break;
  case RosterDirectionalAngleMode::ResetMovement:movement=0;break;
  case RosterDirectionalAngleMode::SetMovement180:movement=180;break;
  case RosterDirectionalAngleMode::Approach:approach_battle_offset(offset,0.f,run.turn1);break;
  case RosterDirectionalAngleMode::Preserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);break;
  case RosterDirectionalAngleMode::ApproachReset:
   approach_battle_offset(offset,0.f,run.turn1);movement=0;break;
  case RosterDirectionalAngleMode::ApproachSet180:
   approach_battle_offset(offset,0.f,run.turn1);movement=180;break;
  case RosterDirectionalAngleMode::ApproachSet90:
   approach_battle_offset(offset,0.f,run.turn1);movement=90;break;
  case RosterDirectionalAngleMode::ApproachSetMinus90:
   approach_battle_offset(offset,0.f,run.turn1);movement=-90;break;
  case RosterDirectionalAngleMode::ApproachThenPreserve:
   approach_battle_offset(offset,0.f,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);break;
 }
 return run.frame_delta;
}
}
