#pragma once
#include "roster_directional_shot_motion.hpp"
#include "roster_directional_shot_schedule.hpp"
#include "roster_directional_round_schedule.hpp"
#include "roster_directional_visit_round_schedule.hpp"
#include "roster_ground_shot400.hpp"
#include <array>
#include <cstdint>
#include <stdexcept>

namespace daybreak {

struct RosterDirectionalShotClock {
 unsigned character=0,weapon=0,state=0,phase=0;
 std::array<unsigned char,66> visits{};
};

inline std::uint64_t roster_directional_round_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned rounds){
 return (std::uint64_t(character)<<56)|(std::uint64_t(weapon)<<48)|
        (std::uint64_t(state)<<32)|(std::uint64_t(phase)<<24)|
        (std::uint64_t(frame)<<16)|rounds;
}
inline std::uint64_t roster_directional_visit_round_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned visit,unsigned rounds){
 return (std::uint64_t(character)<<56)|(std::uint64_t(weapon)<<48)|
        (std::uint64_t(state)<<32)|(std::uint64_t(phase)<<24)|
        (std::uint64_t(frame)<<16)|(std::uint64_t(visit)<<8)|rounds;
}

inline bool roster_directional_ignores_boundary(unsigned character,unsigned weapon,unsigned state){
 return (character==5&&weapon==1)||(character==8&&(weapon==2||weapon==1&&state!=404));
}

// Original x86 callback and movement path for DAT-backed directional shooting.
inline GroundShotEffects advance_roster_directional_shot(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned rounds,bool complete,bool grounded,
 RosterDirectionalShotClock& clock,std::vector<GroundShotEffects>& requests,
 int& next_phase,int& frame_delta,float& speed,float& offset,float& movement){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1)||state<404||state>407)
  throw std::invalid_argument("Unsupported roster directional shot binding");
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
 next_phase=-1;frame_delta=1;
 if(complete&&!roster_directional_ignores_boundary(character,weapon,state)){
  out.next_state=character==8&&weapon==1&&state==404?43:0;return out;
 }
 if(!grounded&&!(character==5&&weapon==1||character==8&&(weapon==1||weapon==2))){
  out.next_state=43;return out;
 }
 if(clock.character!=character||clock.weapon!=weapon||clock.state!=state||clock.phase!=phase||frame==0){
  clock={};clock.character=character;clock.weapon=weapon;clock.state=state;clock.phase=phase;
 }
 switch(state){
  case 404:out=advance_roster_shot_schedule(roster_shot404_events,character,weapon,phase,frame,requests,next_phase);break;
  case 405:out=advance_roster_shot_schedule(roster_shot405_events,character,weapon,phase,frame,requests,next_phase);break;
  case 406:out=advance_roster_shot_schedule(roster_shot406_events,character,weapon,phase,frame,requests,next_phase);break;
  case 407:out=advance_roster_shot_schedule(roster_shot407_events,character,weapon,phase,frame,requests,next_phase);break;
 }
 const auto round_key=roster_directional_round_key(character,weapon,state,phase,frame,rounds);
 const auto round_row=std::lower_bound(std::begin(roster_directional_round_ranges),
  std::end(roster_directional_round_ranges),round_key,
  [](const RosterDirectionalRoundRange& row,std::uint64_t value){
   return roster_directional_round_key(row.character,row.weapon,row.state,row.phase,row.frame,row.max_rounds)<value;
  });
 if(round_row!=std::end(roster_directional_round_ranges)&&
    roster_directional_round_key(round_row->character,round_row->weapon,round_row->state,
     round_row->phase,round_row->frame,round_row->min_rounds)<=round_key){
  requests.clear();
  out=decode_roster_shot_events(roster_directional_round_events+round_row->event_begin,
   roster_directional_round_events+round_row->event_begin+round_row->event_count,
   phase,frame,requests,next_phase);
 }
 frame_delta=advance_roster_directional_shot_motion(character,weapon,state,phase,frame,speed,offset,movement);
 if(frame<clock.visits.size()){
  const unsigned visit=clock.visits[frame]++;
  const auto key=roster_directional_visit_round_key(character,weapon,state,phase,frame,visit,rounds);
  const auto first=std::lower_bound(std::begin(roster_directional_visit_round_ranges),
   std::end(roster_directional_visit_round_ranges),key,
   [](const RosterDirectionalVisitRoundRange& row,std::uint64_t value){
    return roster_directional_visit_round_key(row.character,row.weapon,row.state,row.phase,
     row.frame,row.visit,row.max_rounds)<value;
   });
  if(first!=std::end(roster_directional_visit_round_ranges)&&
     roster_directional_visit_round_key(first->character,first->weapon,first->state,
      first->phase,first->frame,first->visit,first->min_rounds)<=key){
   requests.clear();
   out=decode_roster_shot_events(roster_directional_visit_round_events+first->event_begin,
      roster_directional_visit_round_events+first->event_begin+first->event_count,
      phase,frame,requests,next_phase);
   frame_delta=first->frame_delta;
  }
 }
 return out;
}
}
