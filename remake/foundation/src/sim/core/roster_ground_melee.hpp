#pragma once
#include "character_dispatch.hpp"
#include "keiichi_attack300.hpp"
#include <algorithm>
#include <array>
#include <cstdint>

namespace daybreak {

// Original state300 first-frame observations for the DAT-driven roster.
// These configure the shared action loop; other action states are independent.
struct RosterGroundMeleeTuning {
 float close_speed;
 float far_speed;
 std::uint32_t far_distance_squared;
 bool moving;
};

// Original state300 phase-one distance/clock gate and phase-two motion.
// The values come from carrying handler scratch state from phase zero through
// the later phases for all 37 preview-policy character/weapon pairs.
struct RosterGroundMeleePhaseTuning {
 std::uint32_t reach_squared;
 int earliest_phase2_frame,forced_phase2_frame;
 int sound_frame,sound_id;
 int slowdown_start;
 float slowdown;
 int stop_frame,boost_frame;
 float boost_speed;
};

inline RosterGroundMeleePhaseTuning roster_ground_melee_phase_profile(unsigned character,unsigned weapon){
 character_action_dispatch(character,weapon);
 switch(character){
  case 3:return {90000,0,11,12,60,0,weapon==0?1.f:weapon==1?1.75f:.85f,-1,-1,0};
  case 4:return {40000,3,weapon==2?11:21,0,60,2,weapon==2?2.5f:1.5f,-1,-1,0};
  case 5:return {40000,0,21,0,60,0,1.5f,-1,-1,0};
  case 6:return {90000,weapon==0?0:3,-1,8,60,1,1.5f,-1,-1,0};
  case 7:return {90000,0,-1,12,61,0,.75f,-1,-1,0};
  case 8:return {90000,0,-1,9,61,-1,0,10,-1,0};
  case 9:return {62500,0,21,6,60,-1,0,7,4,30};
  case 10:return {62500,0,-1,3,60,4,1.5f,-1,-1,0};
  case 11:return {90000,0,-1,6,60,-1,0,6,-1,0};
  case 12:return {62500,0,-1,5,60,6,1.f,-1,-1,0};
  case 13:return {62500,0,-1,2,60,-1,0,8,-1,0};
  case 14:return {40000,3,21,0,60,8,1.5f,-1,-1,0};
  case 15:return {90000,0,11,3,60,0,1.5f,-1,-1,0};
  default:throw std::out_of_range("Dedicated fighter has no roster phase profile");
 }
}

inline constexpr RosterGroundMeleeTuning roster_ground_melee_tuning[16][3] = {
 // Rena, Mion, and Keiichi stay on their existing dedicated handlers.
 {{0,0,0,false},{0,0,0,false},{0,0,0,false}},
 {{0,0,0,false},{0,0,0,false},{0,0,0,false}},
 {{0,0,0,false},{0,0,0,false},{0,0,0,false}},
 {{20,20,0,false},{20,20,0,false},{17.5f,17.5f,0,false}},
 {{15.5f,14.5f,250000,false},{15.5f,14.5f,250000,false},{24.5f,15.5f,640000,false}},
 {{27,17.5f,640000,false},{27,17.5f,640000,false},{27,17.5f,640000,false}},
 {{25,17.5f,640000,false},{22.5f,16.5f,640000,false},{22.5f,16.5f,640000,false}},
 {{22.5f,14.5f,640000,false},{15,15,0,false},{22.5f,14.5f,640000,false}},
 {{20,14,640000,false},{20,14,640000,false},{20,14,640000,false}},
 {{25,17.5f,640000,false},{25,17.5f,640000,false},{25,17.5f,640000,false}},
 {{20,17,360000,false},{20,17,360000,false},{20,17,360000,false}},
 {{24.5f,17.5f,640000,false},{24.5f,17.5f,640000,false},{24.5f,17.5f,640000,false}},
 {{18.5f,15,490000,false},{18.5f,15,490000,false},{18.5f,15,490000,false}},
 {{27,20,640000,false},{27,20,640000,false},{27,20,640000,false}},
 {{21.5f,15,640000,false},{16.5f,15,250000,false},{0,0,0,false}},
 {{25,15,640000,true},{25,15,640000,true},{0,0,0,false}},
};

inline const RosterGroundMeleeTuning& roster_ground_melee_profile(unsigned character,unsigned weapon) {
 character_action_dispatch(character,weapon); // Reject unsupported roster pairs.
 return roster_ground_melee_tuning[character][weapon];
}

// The original state300 handlers pass actor+6a0 to 434b30/434bd0. Their
// +fc flag (actor+79c) enables linked weapon trails, not DAT hit geometry.
// Most roster state300 actions leave it disabled; do not infer this window
// from Keiichi's sword action for every character.
inline bool roster_ground_melee_linked_trail(unsigned character,unsigned weapon,
                                            int phase,int frame){
 if(phase!=2)return false;
 switch(character){
  case 4:return weapon==2&&frame>=2&&frame<=13;
  case 5:return frame>=2&&frame<=5;
  case 13:return frame>=3&&frame<=10;
  case 15:return frame>=3&&frame<=9;
  default:return false;
 }
}

inline KeiichiAttack300Effects advance_roster_ground_melee(
 unsigned character,unsigned weapon,KeiichiAttack300& state,const KeiichiAttack300Input& input) {
 const auto& tuning=roster_ground_melee_profile(character,weapon);
 const auto phases=roster_ground_melee_phase_profile(character,weapon);
 const float incoming_speed=state.speed;
 auto effects=advance_keiichi_attack300(state,input);
 // 005ed860 state300 opens three linked contact slots for character15's
 // second weapon and consumes each non-guard contact immediately. The shared
 // Keiichi kernel otherwise keeps its single contact flag latched.
 if(character==15&&weapon==1){
  if(effects.initialize)effects.contact_capacity=3;
  if(effects.next_state<0&&input.contact)effects.clear_contact=true;
 }
 if(effects.next_state>=0)return effects;
 effects.strike=roster_ground_melee_linked_trail(character,weapon,state.phase,state.frame);
 if(effects.next_state<0&&!input.animation_complete&&input.grounded&&state.phase==0&&state.frame==0) {
  state.speed=tuning.far_distance_squared&&input.distance_squared>=tuning.far_distance_squared
   ? tuning.far_speed : tuning.close_speed;
  state.moving=tuning.moving;
 }
 if(state.phase==1){
  // Character 3 counts phase-one updates in the original +e8 scratch word.
  // A close target exits immediately; a distant target exits on update 12.
  if(character==3)++state.moving;
  const bool reached=input.distance_squared<double(phases.reach_squared)&&
                     state.frame>=phases.earliest_phase2_frame;
  const bool timed=character==3?state.moving>=12:
   phases.forced_phase2_frame>=0&&state.frame>=phases.forced_phase2_frame;
  effects.next_phase=reached||timed?2:-1;
 }
 if(state.phase==2){
  effects.effect=state.frame==phases.sound_frame?phases.sound_id:-1;
  effects.voice=-1;effects.voice_argument=0;
  if(effects.effect>=0){
   const auto voice=battle_melee_voice(1,input.distance_squared,state.offset,input.voice_flags);
   effects.voice=voice.id;effects.voice_argument=voice.argument;
  }
  state.speed=incoming_speed;
  if(state.frame==phases.boost_frame)state.speed=phases.boost_speed;
  if(state.frame==phases.stop_frame)state.speed=0;
  if(phases.slowdown_start>=0&&state.frame>=phases.slowdown_start)
   state.speed=std::max(0.f,state.speed-phases.slowdown);
 }
 return effects;
}

} // namespace daybreak
