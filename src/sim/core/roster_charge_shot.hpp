#pragma once
#include "roster_charge_shot_motion.hpp"
#include "roster_charge_shot_round_schedule.hpp"
#include "roster_charge_shot_secondary_schedule.hpp"
#include "roster_charge_shot_visit_round_schedule.hpp"
#include "roster_charge_shot_schedule.hpp"
#include "roster_ground_shot400.hpp"
#include <array>
#include <cstdint>
#include <stdexcept>

namespace daybreak {

struct RosterChargeShotClock {
 unsigned character=0,weapon=0,state=0,phase=0;
 std::array<unsigned,100> visits{};
};

inline std::uint64_t roster_charge_shot_round_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned rounds){
 return (std::uint64_t(character)<<56)|(std::uint64_t(weapon)<<48)|
        (std::uint64_t(state)<<32)|(std::uint64_t(phase)<<24)|
        (std::uint64_t(frame)<<16)|rounds;
}
inline std::uint64_t roster_charge_shot_visit_round_key(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned visit,unsigned rounds){
 return (std::uint64_t(character)<<56)|(std::uint64_t(weapon)<<48)|
        (std::uint64_t(state)<<32)|(std::uint64_t(phase)<<24)|
        (std::uint64_t(frame)<<16)|(std::uint64_t(visit)<<8)|rounds;
}

// Original x86 callbacks, both ammunition ranges and scratch visits for
// DAT-backed charge states450/460. Boundary exits are handled separately.
inline GroundShotEffects advance_roster_charge_shot(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,unsigned primary_rounds,unsigned secondary_rounds,bool complete,bool grounded,
 RosterChargeShotClock& clock,std::vector<GroundShotEffects>& requests,
 int& next_phase,int& frame_delta,float& speed,float& offset,float& movement,
 float& vertical,float& gravity,unsigned projectile_finished=0,
 unsigned melee_held=0,unsigned melee_released=0){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1)||
    (state!=450&&state!=460))throw std::invalid_argument("Unsupported roster charge-shot binding");
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;
 next_phase=-1;frame_delta=1;
 if(complete){
  out.next_state=state==460||(character==13&&weapon==2)?43:0;
  if(state==450&&character==13&&weapon==1)gravity=0;
  if(state==460&&character==15&&weapon==1)gravity=.5f;
  frame_delta=0;return out;
 }
 if(state==450&&!grounded&&!(character==13&&weapon==2)){
  out.next_state=43;gravity=.5f;frame_delta=0;return out;
 }
 if(character==13&&weapon==2&&state==450&&phase>=1&&vertical<0){
  out.next_state=469;vertical=0;gravity=0;frame_delta=0;return out;
 }
 if(state==460&&grounded){
  if(character==13&&weapon==1&&phase==1){
   if(frame==20){next_phase=3;frame_delta=0;return out;}
   out.next_state=450;next_phase=3;vertical=0;frame_delta=0;return out;
  }
  if(character==15&&weapon==0&&phase==2){
   out.next_state=469;vertical=gravity=0;frame_delta=0;return out;
  }
  if((character==9&&weapon==2&&phase==1)||
     (character==13&&weapon==1&&phase==3)||
     (frame>=11&&character==8&&weapon==1&&phase==2)||
     (frame>=26&&character==9&&weapon==2&&phase==0)){
   out.next_state=469;vertical=0;frame_delta=0;return out;
  }
  if(frame>0){
   if(character==6&&weapon==2&&phase==0){
    out.next_state=469;frame_delta=0;return out;
   }
  }
  if(vertical<0){
   if(character==13&&weapon==2&&phase>=1){
    out.next_state=469;vertical=gravity=0;frame_delta=0;return out;
   }
   if(character==14&&weapon==1){
    out.next_state=469;vertical=gravity=0;frame_delta=0;return out;
   }
   const bool ignore=(character==8&&weapon==1)||
    (character==9&&((weapon==1)||(weapon==2&&phase==0)))||
    (character==6&&weapon==2&&phase==0)||
    (character==13&&((weapon==1&&phase!=3)||(weapon==2&&phase==0)))||
    (character==15&&weapon==0&&(phase==0||phase==1));
   if(!ignore){
    out.next_state=469;if(character==11&&weapon==1)gravity=.5f;
    frame_delta=0;return out;
   }
  }
 }
 if(character==5&&weapon==0&&phase==1&&projectile_finished){
  const float incoming_vertical=vertical;
  advance_roster_charge_shot_motion(character,weapon,state,phase,frame,
   speed,offset,movement,vertical,gravity);
  gravity=.5f;vertical=state==460?incoming_vertical-.5f:incoming_vertical;
  next_phase=2;frame_delta=state==450?0:1;return out;
 }
 if(clock.character!=character||clock.weapon!=weapon||clock.state!=state||clock.phase!=phase||frame==0){
  clock={};clock.character=character;clock.weapon=weapon;clock.state=state;clock.phase=phase;
 }
 if(state==450)out=advance_roster_shot_schedule(roster_shot450_events,character,weapon,phase,frame,requests,next_phase);
 else out=advance_roster_shot_schedule(roster_shot460_events,character,weapon,phase,frame,requests,next_phase);
 frame_delta=advance_roster_charge_shot_motion(character,weapon,state,phase,frame,
  speed,offset,movement,vertical,gravity);
 const auto round_key=roster_charge_shot_round_key(character,weapon,state,phase,frame,primary_rounds);
 const auto round_row=std::lower_bound(std::begin(roster_charge_shot_round_ranges),
  std::end(roster_charge_shot_round_ranges),round_key,
  [](const RosterChargeShotRoundRange& row,std::uint64_t value){
   return roster_charge_shot_round_key(row.character,row.weapon,row.state,row.phase,row.frame,row.max_rounds)<value;
  });
 if(round_row!=std::end(roster_charge_shot_round_ranges)&&
    roster_charge_shot_round_key(round_row->character,round_row->weapon,round_row->state,
     round_row->phase,round_row->frame,round_row->min_rounds)<=round_key){
  requests.clear();
  out=decode_roster_shot_events(roster_charge_shot_round_events+round_row->event_begin,
   roster_charge_shot_round_events+round_row->event_begin+round_row->event_count,
   phase,frame,requests,next_phase);
  frame_delta=round_row->frame_delta;
 }
 unsigned visit=0;
 if(frame<clock.visits.size()){
  visit=clock.visits[frame]++;
  // Original air charge repeats frames 8..10 three times; on the fourth
  // visit to frame 10 it starts the recovery with a fixed vertical impulse.
  if(character==9&&weapon==0&&state==460&&phase==0&&frame==10&&visit==3){
   vertical=-.5f;gravity=.5f;
  }
  const auto key=roster_charge_shot_visit_round_key(character,weapon,state,phase,frame,visit,primary_rounds);
  const auto first=std::lower_bound(std::begin(roster_charge_shot_visit_round_ranges),
   std::end(roster_charge_shot_visit_round_ranges),key,
   [](const RosterChargeShotVisitRoundRange& row,std::uint64_t value){
    return roster_charge_shot_visit_round_key(row.character,row.weapon,row.state,
     row.phase,row.frame,row.visit,row.max_rounds)<value;
   });
  if(visit<256&&first!=std::end(roster_charge_shot_visit_round_ranges)&&
     roster_charge_shot_visit_round_key(first->character,first->weapon,first->state,
      first->phase,first->frame,first->visit,first->min_rounds)<=key){
   requests.clear();
   out=decode_roster_shot_events(roster_charge_shot_visit_round_events+first->event_begin,
    roster_charge_shot_visit_round_events+first->event_begin+first->event_count,
    phase,frame,requests,next_phase);
   frame_delta=first->frame_delta;
  }
 }
 const auto secondary_key=roster_charge_shot_round_key(character,weapon,state,phase,frame,secondary_rounds);
 const auto secondary_row=std::lower_bound(std::begin(roster_charge_shot_secondary_ranges),
  std::end(roster_charge_shot_secondary_ranges),secondary_key,
  [](const RosterChargeShotSecondaryRange& row,std::uint64_t value){
   return roster_charge_shot_round_key(row.character,row.weapon,row.state,row.phase,row.frame,row.max_rounds)<value;
  });
 if(visit==0&&secondary_row!=std::end(roster_charge_shot_secondary_ranges)&&
    roster_charge_shot_round_key(secondary_row->character,secondary_row->weapon,secondary_row->state,
     secondary_row->phase,secondary_row->frame,secondary_row->min_rounds)<=secondary_key){
  requests.clear();
  out=decode_roster_shot_events(roster_charge_shot_secondary_events+secondary_row->event_begin,
   roster_charge_shot_secondary_events+secondary_row->event_begin+secondary_row->event_count,
   phase,frame,requests,next_phase);
  frame_delta=secondary_row->frame_delta;
 }
 // Character 12's second magazine holds this frame. Its scratch counter
 // emits effect 208 once after 29 repeated visits.
 if(character==12&&weapon==2&&state==450&&phase==0&&frame==15&&
    secondary_rounds>0&&visit>0){
  frame_delta=0;
  if(visit==29)out.effect=208;
 }
 // 5c8e7f..5c8ec6: a melee press reaching its third frame or a short
 // release advances the charged object even while magazine two is loaded.
 if(character==12&&weapon==2&&state==450&&phase==0&&frame==15&&
    (melee_held==3||(melee_released>0&&melee_released<3)))frame_delta=24;
 // Character 13 weapon 1 switches its staged charge on a held melee button.
 // The airborne frame-20 landing branch takes priority over this input.
 if(character==13&&weapon==1&&phase==1&&frame>=3&&melee_held>0&&
    (state==450||frame!=20)){
  requests.clear();out={};out.attack_calls=0;out.count_attack=false;
  out.next_state=state==460?460:-1;next_phase=2;frame_delta=0;
 }
 if(state==460&&grounded&&character==13&&weapon==1&&phase==2&&frame>=26&&vertical<0){
  out.next_state=469;frame_delta=0;
 }
 return out;
}
}
