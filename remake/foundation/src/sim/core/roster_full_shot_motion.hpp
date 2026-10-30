#pragma once
#include "battle_steering.hpp"
#include "roster_full_shot_motion_schedule.hpp"
#include "roster_full_shot_visit_exits.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
#include <iterator>
#include <stdexcept>

namespace daybreak {

struct RosterFullShotMotionClock {
 unsigned character=0,weapon=0,state=0,phase=0;
 bool rising_shot_started=false;
 bool frame_hold_toggle=false;
 bool has_action_start=false;
 unsigned ticks=0;
 std::array<unsigned,100> visits{};
};

inline std::uint64_t roster_full_shot_motion_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame){
 return (std::uint64_t(character)<<48)|(std::uint64_t(weapon)<<40)|
        (std::uint64_t(state)<<24)|(std::uint64_t(phase)<<16)|frame;
}

// Motion part of original 350/360 handlers. Projectile callbacks, magazine
// admission and animation-completion exits are separate from these transforms.
inline int advance_roster_full_shot_motion(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,float& speed,float& offset,
 float& movement,float& vertical,float& gravity,RosterFullShotMotionClock& clock,
 bool falling=false){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1)||
    (state!=350&&state!=360))throw std::invalid_argument("Unsupported roster full-shot motion binding");
 if(clock.character!=character||clock.weapon!=weapon||clock.state!=state||clock.phase!=phase){
  clock={};clock.character=character;clock.weapon=weapon;clock.state=state;clock.phase=phase;
 }
 const unsigned visit=frame<clock.visits.size()?clock.visits[frame]++:0;
 // The rising blade aborts before its ordinary transform if it has begun
 // descending. The ground portal checks the velocity after gravity instead.
 if(!falling&&character==11&&weapon==2&&state==350&&phase>=1&&vertical<0){
  vertical=gravity=0;return 0;
 }
 if(!falling&&character==13&&weapon==2&&state==350&&phase==2&&vertical-gravity<0){
  approach_battle_offset(offset,0.f,1.f);
  speed=vertical=gravity=0;return 10-int(frame);
 }
 const auto key=roster_full_shot_motion_key(character,weapon,state,phase,frame);
 const auto first=std::lower_bound(std::begin(roster_full_motion_runs),std::end(roster_full_motion_runs),key,
  [](const RosterFullMotionRun& run,std::uint64_t value){
   return roster_full_shot_motion_key(run.character,run.weapon,run.state,run.phase,run.last)<value;
  });
 if(first==std::end(roster_full_motion_runs)||
    roster_full_shot_motion_key(first->character,first->weapon,first->state,first->phase,first->first)>key)
  return 1;
 const auto& run=*first;
 const float incoming_vertical=vertical,incoming_gravity=gravity;
 switch(run.speed_mode){
  case RosterFullSpeedMode::Keep:break;
  case RosterFullSpeedMode::Set:speed=run.speed_a;break;
  case RosterFullSpeedMode::Brake:speed=std::max(0.f,speed-run.speed_a);break;
  case RosterFullSpeedMode::Scale:speed*=run.speed_a;break;
  case RosterFullSpeedMode::Add:speed+=run.speed_a;break;
  case RosterFullSpeedMode::ThresholdBrakeFloor:
   if(speed>=run.speed_b)speed=std::max(run.speed_c,speed-run.speed_a);break;
  case RosterFullSpeedMode::NegativeRecovery:
   speed=speed<0?std::min(0.f,speed+run.speed_a):0.f;break;
  case RosterFullSpeedMode::AsymmetricBrake:
   speed=speed<0?std::min(0.f,speed+run.speed_b):std::max(0.f,speed-run.speed_a);break;
  case RosterFullSpeedMode::ClampMax:speed=std::min(speed,run.speed_a);break;
  case RosterFullSpeedMode::NegativeFloorRecovery:
   speed=std::min(run.speed_a,speed+run.speed_b);break;
 }
 switch(run.angle_mode){
  case RosterFullAngleMode::Keep:break;
  case RosterFullAngleMode::ResetMovement:movement=0;break;
  case RosterFullAngleMode::ZeroOffset:offset=0;break;
  case RosterFullAngleMode::ZeroAndReset:offset=movement=0;break;
  case RosterFullAngleMode::Approach:approach_battle_offset(offset,0.f,run.turn1);break;
  case RosterFullAngleMode::ApproachReset:
   approach_battle_offset(offset,0.f,run.turn1);movement=0;break;
  case RosterFullAngleMode::Preserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);break;
  case RosterFullAngleMode::ApproachBelow90:
   if(offset<90.f)approach_battle_offset(offset,0.f,run.turn1);break;
  case RosterFullAngleMode::DoublePreserve:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);break;
  case RosterFullAngleMode::ApproachThenPreserve:
   approach_battle_offset(offset,0.f,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);break;
  case RosterFullAngleMode::PreserveThenApproach:
   approach_battle_offset_preserving_movement(offset,movement,run.turn1);
   approach_battle_offset(offset,0.f,run.turn2);break;
  case RosterFullAngleMode::ResetThenPreserve:
   movement=0;approach_battle_offset_preserving_movement(offset,movement,run.turn1);break;
  case RosterFullAngleMode::ResetThenApproachThenPreserve:
   movement=0;approach_battle_offset(offset,0.f,run.turn1);
   approach_battle_offset_preserving_movement(offset,movement,run.turn2);break;
 }
 switch(run.gravity_mode){
  case RosterFullGravityMode::Keep:break;
  case RosterFullGravityMode::Set:gravity=run.gravity_value;break;
  case RosterFullGravityMode::ZeroSet:if(gravity==0)gravity=run.gravity_value;break;
 }
 if(run.vertical_mode==RosterFullVerticalMode::Clamp3ThenGravity)
  vertical=vertical==0?-gravity:std::clamp(vertical,-3.f,3.f);
 else vertical=run.vertical_factor*vertical+
       run.vertical_gravity*(run.vertical_mode==RosterFullVerticalMode::Before?incoming_gravity:gravity)+
       run.vertical_constant;
 // Original scratch+f8 changes the later airborne barrage from its isolated
 // per-frame launch impulse to ordinary gravity integration after frame15.
 if(character==4&&weapon==1&&state==360&&phase==0){
  if(frame>=16&&clock.rising_shot_started)vertical=incoming_vertical-gravity;
  if(frame==15)clock.rising_shot_started=true;
 }
 int delta=run.frame_delta;
 if(character==13&&weapon==0&&phase==0&&frame>=51&&frame<80){
  delta=clock.frame_hold_toggle?1:0;
  clock.frame_hold_toggle=!clock.frame_hold_toggle;
 }else if(character==15&&weapon==0&&state==360&&phase==1){
  if(++clock.ticks>20)delta=0;
 }else if(character==15&&weapon==1&&phase==0&&(frame==16||frame==43)){
  delta=clock.frame_hold_toggle?1:0;
  clock.frame_hold_toggle=!clock.frame_hold_toggle;
 }
 // Most long holds end on a fixed visit to the same animation frame. Source
 // handlers use actor scratch+f8/+e8; this table compresses their exit counts.
 if(frame<clock.visits.size()){
  const auto visit_key=[](unsigned c,unsigned w,unsigned s,unsigned p,unsigned f,unsigned v){
   return (std::uint64_t(c)<<56)|(std::uint64_t(w)<<48)|
          (std::uint64_t(s)<<32)|(std::uint64_t(p)<<24)|
          (std::uint64_t(f)<<8)|v;
  };
  const auto key=visit_key(character,weapon,state,phase,frame,visit);
  const auto row=std::lower_bound(std::begin(roster_full_visit_exits),
   std::end(roster_full_visit_exits),key,
   [&](const RosterFullVisitExit& entry,std::uint64_t value){
    return visit_key(entry.character,entry.weapon,entry.state,entry.phase,entry.frame,entry.visit)<value;
   });
  if(row!=std::end(roster_full_visit_exits)&&
     visit_key(row->character,row->weapon,row->state,row->phase,row->frame,row->visit)==key)
   delta=int(row->after)-int(frame);
 }
 if(character==9&&weapon==2&&state==360&&phase==0&&frame==32&&visit==15){
  vertical-=.25f;gravity=.5f;
 }
 // The airborne wire volley opens its post-hold recovery after its sixteenth
 // visit to frame32. Isolated frame33+ probes have no such prior scratch.
 if(character==9&&weapon==2&&state==360&&phase==0&&frame>=33&&frame<100&&
    clock.visits[32]>15)delta=1;
 return delta;
}
} // namespace daybreak
