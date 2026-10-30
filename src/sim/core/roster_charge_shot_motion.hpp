#pragma once
#include "battle_steering.hpp"
#include "roster_charge_shot_motion_schedule.hpp"
#include <algorithm>
#include <cstdint>
#include <iterator>

namespace daybreak {

inline std::uint64_t roster_charge_shot_motion_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame){
 return (std::uint64_t(character)<<48)|(std::uint64_t(weapon)<<40)|
        (std::uint64_t(state)<<24)|(std::uint64_t(phase)<<16)|frame;
}

inline int advance_roster_charge_shot_motion(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,float& speed,float& offset,
 float& movement,float& vertical,float& gravity){
 // Character 13 / weapon 2 returns to landing recovery before its grounded
 // charge phases continue if the incoming vertical velocity is negative.
 if(character==13&&weapon==2&&state==450&&phase>=1&&vertical<0){
  vertical=0;gravity=0;return 0;
 }
 const auto key=roster_charge_shot_motion_key(character,weapon,state,phase,frame);
 const auto first=std::lower_bound(std::begin(roster_charge_shot_motion_runs),
  std::end(roster_charge_shot_motion_runs),key,
  [](const RosterChargeShotMotionRun& run,std::uint64_t value){
   return roster_charge_shot_motion_key(run.character,run.weapon,run.state,run.phase,run.last)<value;
  });
 if(first==std::end(roster_charge_shot_motion_runs)||
    roster_charge_shot_motion_key(first->character,first->weapon,first->state,first->phase,first->first)>key){
  // Character 5 weapon 0 waits for its projectile in phase 1, so the frame
  // clock can run beyond the 0..99 shared schedule. Original frames 100..300
  // continue the same brake/gravity behavior as frame 99.
  if(character==5&&weapon==0&&phase==1&&frame>=100){
   if(state==450)speed=std::max(0.f,speed-.5f);
   else if(state==460)vertical-=gravity;
  }
  return 1;
 }
 const auto& run=*first;
 switch(run.speed_mode){
  case RosterChargeShotSpeedMode::Keep:break;
  case RosterChargeShotSpeedMode::Set:speed=run.speed_a;break;
  case RosterChargeShotSpeedMode::Brake:speed=std::max(0.f,speed-run.speed_a);break;
  case RosterChargeShotSpeedMode::BrakeFloor:speed=std::max(run.speed_b,speed-run.speed_a);break;
  case RosterChargeShotSpeedMode::Scale:speed*=run.speed_a;break;
  case RosterChargeShotSpeedMode::Add:speed+=run.speed_a;break;
  case RosterChargeShotSpeedMode::SymmetricBrake:
   speed=speed<0?std::min(0.f,speed+run.speed_a):std::max(0.f,speed-run.speed_a);break;
  case RosterChargeShotSpeedMode::ThresholdBrakeFloor:
   if(speed>=run.speed_b)speed=std::max(run.speed_c,speed-run.speed_a);break;
  case RosterChargeShotSpeedMode::NegativeRecovery:
   speed=speed<0?std::min(0.f,speed+run.speed_a):0.f;break;
  case RosterChargeShotSpeedMode::SignedRecoil:
   speed-=speed>0?run.speed_a:speed==0?run.speed_b:run.speed_c;break;
 }
 switch(run.angle_mode){
  case RosterChargeShotAngleMode::Keep:break;
  case RosterChargeShotAngleMode::ResetMovement:movement=0;break;
  case RosterChargeShotAngleMode::ZeroAndReset:offset=0;movement=0;break;
  case RosterChargeShotAngleMode::Approach:approach_battle_offset(offset,0.f,run.turn1);break;
  case RosterChargeShotAngleMode::ApproachReset:
   approach_battle_offset(offset,0.f,run.turn1);movement=0;break;
  case RosterChargeShotAngleMode::Preserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);break;
  case RosterChargeShotAngleMode::DoublePreserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);break;
 }
 switch(run.gravity_mode){
  case RosterChargeShotGravityMode::Keep:break;
  case RosterChargeShotGravityMode::Set:gravity=run.gravity_value;break;
  case RosterChargeShotGravityMode::ZeroSet:if(gravity==0)gravity=run.gravity_value;break;
 }
 vertical=run.vertical_factor*vertical+run.vertical_gravity*gravity+run.vertical_constant;
 return run.frame_delta;
}
}
