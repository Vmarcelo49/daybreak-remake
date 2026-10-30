#pragma once
#include "battle_steering.hpp"
#include "roster_air_shot_motion_schedule.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>

namespace daybreak {

inline std::uint64_t roster_air_shot_motion_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame){
 return (std::uint64_t(character)<<48)|(std::uint64_t(weapon)<<40)|
        (std::uint64_t(state)<<24)|(std::uint64_t(phase)<<16)|frame;
}

inline int advance_roster_air_shot_motion(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,float& speed,float& offset,
 float& movement,float& vertical,float& gravity){
 const auto key=roster_air_shot_motion_key(character,weapon,state,phase,frame);
 const auto first=std::lower_bound(std::begin(roster_air_shot_motion_runs),
  std::end(roster_air_shot_motion_runs),key,
  [](const RosterAirShotMotionRun& run,std::uint64_t value){
   return roster_air_shot_motion_key(run.character,run.weapon,run.state,run.phase,run.last)<value;
  });
 if(first==std::end(roster_air_shot_motion_runs)||
    roster_air_shot_motion_key(first->character,first->weapon,first->state,first->phase,first->first)>key)return 1;
 const auto& run=*first;
 switch(run.speed_mode){
  case RosterAirShotSpeedMode::Keep:break;
  case RosterAirShotSpeedMode::Set:speed=run.speed_value;break;
  case RosterAirShotSpeedMode::Brake:speed=std::max(0.f,speed-run.speed_value);break;
  case RosterAirShotSpeedMode::BrakeFloor:speed=std::max(run.speed_floor,speed-run.speed_value);break;
  case RosterAirShotSpeedMode::Scale:speed*=run.speed_value;break;
  case RosterAirShotSpeedMode::Add:speed+=run.speed_value;break;
 }
 switch(run.angle_mode){
  case RosterAirShotAngleMode::Keep:break;
  case RosterAirShotAngleMode::ResetMovement:movement=0;break;
  case RosterAirShotAngleMode::ZeroOffset:offset=0;break;
  case RosterAirShotAngleMode::ZeroAndReset:offset=0;movement=0;break;
  case RosterAirShotAngleMode::Approach:approach_battle_offset(offset,0.f,run.turn1);break;
  case RosterAirShotAngleMode::ApproachReset:
   approach_battle_offset(offset,0.f,run.turn1);movement=0;break;
  case RosterAirShotAngleMode::Preserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);break;
  case RosterAirShotAngleMode::DoublePreserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);break;
 }
 switch(run.gravity_mode){
  case RosterAirShotGravityMode::Keep:break;
  case RosterAirShotGravityMode::Set:gravity=run.gravity_value;break;
  case RosterAirShotGravityMode::ZeroSet:if(gravity==0)gravity=run.gravity_value;break;
 }
 vertical=run.vertical_factor*vertical+run.vertical_gravity*gravity+run.vertical_constant;
 return run.frame_delta;
}
}
