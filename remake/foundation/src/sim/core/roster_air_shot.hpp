#pragma once
#include "roster_air_shot_motion.hpp"
#include "roster_air_shot_round_schedule.hpp"
#include "roster_air_shot_visit_round_schedule.hpp"
#include "roster_air_shot_schedule.hpp"
#include "roster_ground_shot400.hpp"
#include <array>
#include <cstdint>
#include <stdexcept>

namespace daybreak {

struct RosterAirShotClock {
 unsigned character=0,weapon=0,state=0,phase=0;
 std::array<unsigned char,100> visits{};
};

inline std::uint64_t roster_air_shot_round_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned rounds){
 return (std::uint64_t(character)<<56)|(std::uint64_t(weapon)<<48)|
        (std::uint64_t(state)<<32)|(std::uint64_t(phase)<<24)|
        (std::uint64_t(frame)<<16)|rounds;
}
inline std::uint64_t roster_air_shot_visit_round_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned visit,unsigned rounds){
 return (std::uint64_t(character)<<56)|(std::uint64_t(weapon)<<48)|
        (std::uint64_t(state)<<32)|(std::uint64_t(phase)<<24)|
        (std::uint64_t(frame)<<16)|(std::uint64_t(visit)<<8)|rounds;
}

inline bool roster_air_shot408_ignores_boundary(unsigned character,unsigned weapon){
 return character==4||(character==5&&weapon==1)||(character==8&&weapon>=1)||
        character==10||character==13||character==14;
}

inline bool roster_air_shot402_ignores_landing(unsigned character,unsigned weapon,unsigned phase,float vertical){
 if((character==3&&weapon==1)||(character==9&&weapon==0))return vertical>=0;
 if(character==5&&weapon==2&&phase<2)return true;
 if(character==8&&weapon==1&&phase==0)return true;
 if(character==9&&weapon==2&&phase<2)return true;
 if(character==13&&weapon==2)return true;
 return false;
}
inline bool roster_air_shot402_lands_at_start(unsigned character,unsigned weapon,unsigned phase){
 return (character==6&&weapon==2&&phase==0)||
        (character==8&&weapon==2&&phase==0)||
        (character==9&&((weapon==1&&phase==0)||(weapon==2&&phase==2)))||
        (character==10&&phase==0)||
        (character==12&&((weapon==0)||(phase==0)));
}

// Recovered original x86 callbacks and motion for DAT-backed air states402/408.
inline GroundShotEffects advance_roster_air_shot(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned rounds,bool complete,bool grounded,
 RosterAirShotClock& clock,std::vector<GroundShotEffects>& requests,
 int& next_phase,int& frame_delta,float& speed,float& offset,float& movement,
 float& vertical,float& gravity,unsigned projectile_trigger=0,bool boosted=false){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1)||
    (state!=402&&state!=408))throw std::invalid_argument("Unsupported roster air-shot binding");
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
 next_phase=-1;frame_delta=1;
 if(complete&&(state==402||!roster_air_shot408_ignores_boundary(character,weapon))){
  out.next_state=43;return out;
 }
 if(grounded){
  if(state==408&&frame>0&&!roster_air_shot408_ignores_boundary(character,weapon)){
   out.next_state=409;return out;
  }
  if(state==402&&(frame>0||roster_air_shot402_lands_at_start(character,weapon,phase))){
   if(character==8&&weapon==1&&phase==1){next_phase=2;return out;}
   if(!roster_air_shot402_ignores_landing(character,weapon,phase,vertical)){
    out.next_state=403;return out;
   }
  }
 }
 if(clock.character!=character||clock.weapon!=weapon||clock.state!=state||clock.phase!=phase||frame==0){
  clock={};clock.character=character;clock.weapon=weapon;clock.state=state;clock.phase=phase;
 }
 if(state==402)out=advance_roster_shot_schedule(roster_shot402_events,character,weapon,phase,frame,requests,next_phase);
 else out=advance_roster_shot_schedule(roster_shot408_events,character,weapon,phase,frame,requests,next_phase);
 frame_delta=advance_roster_air_shot_motion(character,weapon,state,phase,frame,
  speed,offset,movement,vertical,gravity);
 const auto round_key=roster_air_shot_round_key(character,weapon,state,phase,frame,rounds);
 const auto round_row=std::lower_bound(std::begin(roster_air_shot_round_ranges),
  std::end(roster_air_shot_round_ranges),round_key,
  [](const RosterAirShotRoundRange& row,std::uint64_t value){
   return roster_air_shot_round_key(row.character,row.weapon,row.state,row.phase,row.frame,row.max_rounds)<value;
  });
 if(round_row!=std::end(roster_air_shot_round_ranges)&&
    roster_air_shot_round_key(round_row->character,round_row->weapon,round_row->state,
     round_row->phase,round_row->frame,round_row->min_rounds)<=round_key){
  requests.clear();
  out=decode_roster_shot_events(roster_air_shot_round_events+round_row->event_begin,
   roster_air_shot_round_events+round_row->event_begin+round_row->event_count,
   phase,frame,requests,next_phase);
  frame_delta=round_row->frame_delta;
 }
 if(frame<clock.visits.size()){
  const unsigned visit=clock.visits[frame]++;
  const auto key=roster_air_shot_visit_round_key(character,weapon,state,phase,frame,visit,rounds);
  const auto first=std::lower_bound(std::begin(roster_air_shot_visit_round_ranges),
   std::end(roster_air_shot_visit_round_ranges),key,
   [](const RosterAirShotVisitRoundRange& row,std::uint64_t value){
    return roster_air_shot_visit_round_key(row.character,row.weapon,row.state,row.phase,row.frame,row.visit,row.max_rounds)<value;
   });
  if(first!=std::end(roster_air_shot_visit_round_ranges)&&
     roster_air_shot_visit_round_key(first->character,first->weapon,first->state,
      first->phase,first->frame,first->visit,first->min_rounds)<=key){
   requests.clear();
   out=decode_roster_shot_events(roster_air_shot_visit_round_events+first->event_begin,
    roster_air_shot_visit_round_events+first->event_begin+first->event_count,
    phase,frame,requests,next_phase);
   frame_delta=first->frame_delta;
  }
 }
 // Original Shion2 50aea0 case402 reads actor+f8 after its callbacks.
 // Phase0/frame0 clears the word; states422/423 are the air side returns.
 if(character==5&&weapon==2&&state==402&&phase<2&&!(phase==0&&frame==0)){
  if(projectile_trigger==1)next_phase=2;
  else if(projectile_trigger==2)out.next_state=422;
  else if(projectile_trigger==3)out.next_state=423;
 }
 if(character==5&&weapon==2&&state==402&&boosted)
  for(auto& shot:requests)if(shot.bullet_slot==0)shot.bullet_slot=1;
 return out;
}
}
