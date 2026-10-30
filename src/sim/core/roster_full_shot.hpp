#pragma once
#include "roster_full_shot_motion.hpp"
#include "roster_full_shot_completion_schedule.hpp"
#include "roster_full_shot_schedule.hpp"
#include "roster_full_shot_visit_schedule.hpp"
#include "roster_full_shot_fall_schedule.hpp"
#include "roster_full_shot_land_schedule.hpp"
#include "roster_ground_shot400.hpp"
#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace daybreak {

inline std::uint64_t roster_full_shot_visit_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned visit){
 return (std::uint64_t(character)<<56)|(std::uint64_t(weapon)<<48)|
        (std::uint64_t(state)<<32)|(std::uint64_t(phase)<<24)|
        (std::uint64_t(frame)<<16)|visit;
}

inline bool roster_full_shot_continues_falling(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame){
 switch(character){
  case 4:return (weapon==0||weapon==2)&&phase==0;
  case 5:return weapon==0&&phase<=1;
  case 6:return weapon==2&&phase==1;
  case 11:return weapon==2&&phase<=3;
  case 13:return weapon==2&&phase<=2;
  case 14:return weapon<=1&&phase==0;
  default:return false;
 }
}

inline bool roster_full_shot_fall_callback_override(unsigned character,unsigned weapon,
 unsigned phase){
 return (character==5&&weapon==0&&phase==1)||
        (character==6&&weapon==2&&phase==1)||
        (character==13&&weapon==2&&phase==2);
}

inline bool roster_full_land_guard_applies(RosterLandGuard guard,float vertical,float gravity){
 return guard==RosterLandGuard::Always||
        (guard==RosterLandGuard::Negative&&vertical<0)||
        (guard==RosterLandGuard::BelowGravity&&vertical<gravity);
}

inline const RosterLandMotionRun* roster_full_land_motion(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,float vertical,float gravity){
 const auto key=roster_shot400_key(character,weapon,phase,frame);
 const auto row=std::lower_bound(std::begin(roster_full_land_motion_runs),
  std::end(roster_full_land_motion_runs),key,
  [](const RosterLandMotionRun& run,std::uint32_t value){
   return roster_shot400_key(run.character,run.weapon,run.phase,run.last)<value;
  });
 if(row==std::end(roster_full_land_motion_runs)||
    roster_shot400_key(row->character,row->weapon,row->phase,row->first)>key||
    !roster_full_land_guard_applies(row->guard,vertical,gravity))return nullptr;
 return row;
}

inline float roster_full_land_value(RosterLandMode mode,float normal,float initial,
 float incoming_gravity){
 switch(mode){
  case RosterLandMode::Normal:return normal;
  case RosterLandMode::Keep:return initial;
  case RosterLandMode::Zero:return 0;
  case RosterLandMode::Quarter:return initial*.25f;
  case RosterLandMode::Half:return initial*.5f;
  case RosterLandMode::BrakeHalf:return std::max(0.f,initial-.5f);
  case RosterLandMode::Brake075:return std::max(0.f,initial-.75f);
  case RosterLandMode::MinusGravity:return initial-incoming_gravity;
  case RosterLandMode::MinusHalf:return initial-.5f;
  case RosterLandMode::Minus035:return initial-.35f;
  case RosterLandMode::SetMinusTenth:return -.1f;
  case RosterLandMode::SetMinus035:return -.35f;
  default:throw std::logic_error("Invalid landed motion field");
 }
}

inline int roster_full_land_frame_delta(RosterLandMode mode,int normal,unsigned frame){
 switch(mode){
  case RosterLandMode::Normal:return normal;
  case RosterLandMode::Same:return 0;
  case RosterLandMode::Next:return 1;
  case RosterLandMode::Fixed0:return -int(frame);
  case RosterLandMode::Fixed10:return 10-int(frame);
  default:throw std::logic_error("Invalid landed frame field");
 }
}

inline bool roster_full_land_low_callback(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,float vertical,float gravity){
 const auto key=roster_shot400_key(character,weapon,phase,frame);
 const auto row=std::lower_bound(std::begin(roster_full_land_callback_thresholds),
  std::end(roster_full_land_callback_thresholds),key,
  [](const RosterLandCallbackThreshold& entry,std::uint32_t value){
   return roster_shot400_key(entry.character,entry.weapon,entry.phase,entry.frame)<value;
  });
 return row!=std::end(roster_full_land_callback_thresholds)&&
        roster_shot400_key(row->character,row->weapon,row->phase,row->frame)==key&&
        roster_full_land_guard_applies(row->guard,vertical,gravity);
}

// DAT-roster full-charge actions on their ordinary ground/air path. The
// callback sequence comes from the original handler; the motion clock also
// reproduces reachable repeated frames and scratch-dependent volleys.
inline GroundShotEffects advance_roster_full_shot(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned primary_rounds,bool complete,
 bool grounded,
 RosterFullShotMotionClock& clock,std::vector<GroundShotEffects>& requests,
 int& next_phase,int& frame_delta,float& speed,float& offset,float& movement,
 float& vertical,float& gravity,unsigned shoot_held=0,
 unsigned shoot_released=0,unsigned melee_held=0,unsigned melee_released=0){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1)||
    (state!=350&&state!=360))throw std::invalid_argument("Unsupported roster full-shot binding");
 next_phase=-1;frame_delta=1;
 const bool falling=state==350&&!grounded;
 const bool landing=state==360&&grounded;
 // The rising blade aborts before checking animation completion.
 if(!falling&&character==11&&weapon==2&&state==350&&phase>=1&&vertical<0){
  GroundShotEffects out;out.next_state=469;out.attack_calls=0;out.count_attack=false;
  vertical=gravity=0;frame_delta=0;return out;
 }
 if(complete){
  const auto key=roster_full_shot_motion_key(character,weapon,state,phase,frame);
  const auto row=std::lower_bound(std::begin(roster_full_shot_completion_runs),
   std::end(roster_full_shot_completion_runs),key,
   [](const RosterFullShotCompletionRun& run,std::uint64_t value){
    return roster_full_shot_motion_key(run.character,run.weapon,run.state,run.phase,run.last)<value;
   });
  if(row!=std::end(roster_full_shot_completion_runs)&&
     roster_full_shot_motion_key(row->character,row->weapon,row->state,row->phase,row->first)<=key){
   GroundShotEffects out;out.next_state=row->next_state;
   out.attack_calls=0;out.count_attack=false;next_phase=row->next_phase;
   if(row->subtract_gravity)vertical-=gravity;
   if(row->gravity_half)gravity=.5f;
   frame_delta=row->fixed_after<0?0:int(row->fixed_after)-int(frame);
   return out;
  }
 }
 if(falling&&!roster_full_shot_continues_falling(character,weapon,phase,frame)){
  GroundShotEffects out;out.next_state=43;out.attack_calls=0;out.count_attack=false;
  if(character==9&&weapon>=1)speed*=.25f;
  if(character==13&&weapon==2&&phase==3)vertical=0;
  gravity=.5f;frame_delta=0;return out;
 }
 // Character-11 weapon-1 releases its charge on an actor-side button-up
 // duration of 1..19 ticks. This branch precedes ordinary callbacks and
 // motion, but follows animation completion and ground-contact exits.
 if(character==11&&weapon==1&&phase<=1&&
    ((state==350&&grounded)||(state==360&&!grounded))&&
    !complete&&shoot_released>=1&&shoot_released<=19&&
    frame>=(phase==0?26u:state==350?31u:21u)){
  GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
  next_phase=int(phase)+1;frame_delta=0;return out;
 }
 // The weapon-2 barrage has a 301-frame handler phase even though its DAT
 // animation lists only 16 frames. The original repeats these callbacks past
 // the 0..99 independent schedule window; only a grounded actor exits phase1.
 if(character==6&&weapon==2&&phase==1&&frame>=100){
  GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
  if(frame%20==0)out.effect=232;
  if(grounded){
   if(frame%3==0){
    GroundShotEffects projectile;projectile.fire=true;projectile.bullet_slot=9;
    projectile.origin=GroundShotOrigin::World;projectile.yaw=-offset;
    requests.push_back(projectile);out.fire=true;
   }
   if(frame>=301){next_phase=2;frame_delta=0;}
  }else vertical-=.5f;
  return out;
 }
 if(clock.character!=character||clock.weapon!=weapon||clock.state!=state||
    clock.phase!=phase||(frame==0&&clock.visits[0])){
  clock={};clock.character=character;clock.weapon=weapon;clock.state=state;clock.phase=phase;
 }
 if(frame==0)clock.has_action_start=true;
 const auto visit=frame<clock.visits.size()?clock.visits[frame]:0u;
 const bool fall_override=falling&&roster_full_shot_fall_callback_override(character,weapon,phase);
 const auto land_run=landing?roster_full_land_motion(character,weapon,phase,frame,vertical,gravity):nullptr;
 const bool land_low=landing&&roster_full_land_low_callback(character,weapon,phase,frame,vertical,gravity);
 auto out=landing&&land_low?
  advance_roster_shot_schedule(roster_full_land_low_events,character,weapon,phase,frame,requests,next_phase):
  landing?
   advance_roster_shot_schedule(roster_full_land_high_events,character,weapon,phase,frame,requests,next_phase):
  fall_override?
  advance_roster_shot_schedule(roster_full_shot_fall_events,character,weapon,phase,frame,requests,next_phase):
  state==350?
   advance_roster_shot_schedule(roster_shot350_events,character,weapon,phase,frame,requests,next_phase):
   advance_roster_shot_schedule(roster_shot360_events,character,weapon,phase,frame,requests,next_phase);
 const auto key=roster_full_shot_visit_key(character,weapon,state,phase,frame,visit);
 const auto first=std::lower_bound(std::begin(roster_full_shot_visit_overrides),
  std::end(roster_full_shot_visit_overrides),key,
  [](const RosterFullShotVisitOverride& row,std::uint64_t value){
   return roster_full_shot_visit_key(row.character,row.weapon,row.state,
    row.phase,row.frame,row.visit)<value;
  });
 if(!fall_override&&!land_run&&clock.has_action_start&&first!=std::end(roster_full_shot_visit_overrides)&&
    roster_full_shot_visit_key(first->character,first->weapon,first->state,
     first->phase,first->frame,first->visit)==key){
  requests.clear();
  out=decode_roster_shot_events(roster_full_shot_visit_events+first->event_begin,
   roster_full_shot_visit_events+first->event_begin+first->event_count,
   phase,frame,requests,next_phase);
 }
 // This landed volley uses world yaw0, independent of actor steering. The
 // table was observed at offset30, so its relative -30 must track offset.
 if(landing&&character==6&&weapon==2&&phase==1)
  for(auto& request:requests)if(request.origin==GroundShotOrigin::World)
   request.yaw=-offset;
 // The two primary-magazine exceptions collapse to shared threshold rules.
 if(character==4&&weapon==1&&phase==0&&frame>=15&&out.voice==30&&primary_rounds>=11)
  out.voice=27;
 if(character==5&&weapon==2&&phase==0&&frame==12&&out.voice==29&&primary_rounds==1)
  out.voice=30;
 const float incoming_speed=speed,incoming_offset=offset,incoming_movement=movement;
 const float incoming_vertical=vertical,incoming_gravity=gravity;
 frame_delta=advance_roster_full_shot_motion(character,weapon,state,phase,frame,
  speed,offset,movement,vertical,gravity,clock,falling);
 if(falling&&character==6&&weapon==2&&phase==1)vertical=incoming_vertical-.5f;
 if(falling&&character==13&&weapon==2&&phase==2&&incoming_speed>=8)
  speed=std::max(10.f,incoming_speed-.5f);
 if(land_run){
  speed=roster_full_land_value(land_run->speed,speed,incoming_speed,incoming_gravity);
  offset=roster_full_land_value(land_run->offset,offset,incoming_offset,incoming_gravity);
  movement=roster_full_land_value(land_run->movement,movement,incoming_movement,incoming_gravity);
  vertical=roster_full_land_value(land_run->vertical,vertical,incoming_vertical,incoming_gravity);
  gravity=roster_full_land_value(land_run->gravity,gravity,incoming_gravity,incoming_gravity);
  frame_delta=roster_full_land_frame_delta(land_run->frame,frame_delta,frame);
 }
 // The grounded character-12 weapon-2 charge waits for scratch+f8 to count
 // down from 60 at frame15. Once ready, the original handler tests the actor
 // input counters directly: shooting resumes through frame16; melee skips to
 // frame39. Melee wins if both inputs qualify on the same call.
 if(character==12&&weapon==2&&state==350&&phase==0&&frame==15&&
    !falling&&(visit>=59||!clock.has_action_start)){
  if(shoot_held==3||(shoot_released>=1&&shoot_released<=2))frame_delta=1;
  if(melee_held==3||(melee_released>=1&&melee_released<=2))frame_delta=24;
 }
 return out;
}

} // namespace daybreak
