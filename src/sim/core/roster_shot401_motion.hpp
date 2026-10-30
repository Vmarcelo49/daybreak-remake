#pragma once
#include "battle_steering.hpp"
#include "roster_shot401_motion_schedule.hpp"
#include "roster_ground_shot400.hpp"
#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace daybreak {

inline int advance_roster_shot401_motion(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,float& speed,float& offset,float& movement){
 const auto key=roster_shot400_key(character,weapon,phase,frame);
 const auto first=std::lower_bound(std::begin(roster_shot401_motion_runs),
  std::end(roster_shot401_motion_runs),key,
  [](const RosterShot401MotionRun& run,std::uint32_t value){
   return roster_shot400_key(run.character,run.weapon,run.phase,run.last)<value;
  });
 if(first==std::end(roster_shot401_motion_runs)||
    roster_shot400_key(first->character,first->weapon,first->phase,first->first)>key)return 1;
 const auto& run=*first;
 switch(run.speed_mode){
  case RosterShot401SpeedMode::Keep:break;
  case RosterShot401SpeedMode::Brake:speed=std::max(0.f,speed-run.speed_value);break;
  case RosterShot401SpeedMode::Set:speed=run.speed_value;break;
 }
 switch(run.angle_mode){
  case RosterShot401AngleMode::Keep:break;
  case RosterShot401AngleMode::ResetMovement:movement=0;break;
  case RosterShot401AngleMode::Approach:approach_battle_offset(offset,0.f,run.turn1);break;
  case RosterShot401AngleMode::Preserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);break;
  case RosterShot401AngleMode::ApproachSet180:
   approach_battle_offset(offset,0.f,run.turn1);movement=180;break;
  case RosterShot401AngleMode::DoublePreserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);break;
 }
 return run.frame_delta;
}

}
