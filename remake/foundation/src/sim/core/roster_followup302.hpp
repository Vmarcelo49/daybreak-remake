#pragma once
#include "character_dispatch.hpp"
#include "keiichi_followup.hpp"
#include <algorithm>

namespace daybreak {

// Original state302 update handlers use one motion kernel with a small number
// of fighter-specific clock events. -1 means that the event is absent.
struct RosterFollowup302Profile {
 float initial_speed=-1,clock_speed=0,deceleration=0;
 int clock_set=-1,clock_stop=-1,decelerate_from=-1;
 int effect_frame=-1,effect_id=-1;
 bool clear_speed_at_frame0=false;
};

inline RosterFollowup302Profile roster_followup302_profile(unsigned character,unsigned weapon){
 character_action_dispatch(character,weapon);
 switch(character){
  case 4:
   if(weapon==2)return {-1,25,4,13,-1,23,13,63,true};
   return {};
  case 5:return {-1,30,0,12,20,-1,12,62,false};
  case 9:return {15,0,0,-1,12,-1,10,62,false};
  case 11:return {-1,30,0,7,19,-1,18,62,false};
  case 13:return {-1,15,0,1,14,-1,10,62,true};
  case 14:
   if(weapon==1)return {22.5f,0,4,-1,-1,13,7,60,false};
   return {};
  case 15:return {-1,25,0,10,22,-1,17,62,true};
  default:return {};
 }
}

inline KeiichiFollowupEffects advance_roster_followup302(
 unsigned character,unsigned weapon,KeiichiFollowup& state,const KeiichiFollowupInput& input){
 const auto profile=roster_followup302_profile(character,weapon);
 const float incoming_speed=state.speed;
 auto effects=advance_keiichi_followup(state,input);
 if(effects.next_state>=0)return effects;
 // Keiichi's frame-2 boost and frame-15 stop are not shared roster behavior.
 state.speed=incoming_speed;
 effects.effect=effects.voice=-1;effects.voice_argument=0;
 if(state.frame==0&&profile.clear_speed_at_frame0)state.speed=0;
 if(state.frame==0&&profile.initial_speed>=0&&
    (state.phase==0||(character==9&&state.phase==2)))
  state.speed=character==14&&weapon==1&&input.distance_squared>=640000.
   ?20.f:profile.initial_speed;
 if(character==14&&weapon==1&&state.phase==1){
  if(state.frame==0&&input.distance_squared>=640000.)state.speed=20;
  if((input.distance_squared<40000.&&state.frame>=3)||state.frame>=21)
   effects.next_phase=2;
 }
 if(state.frame==profile.clock_set)state.speed=profile.clock_speed;
 if(state.frame==profile.clock_stop)state.speed=0;
 if(profile.decelerate_from>=0&&state.frame>=profile.decelerate_from&&
    !(character==14&&weapon==1&&state.phase!=2))
  state.speed=std::max(0.f,state.speed-profile.deceleration);
 if(state.frame==profile.effect_frame&&!(character==14&&weapon==1&&state.phase!=2)){
  effects.effect=profile.effect_id;
  effects.voice=3;effects.voice_argument=10;
 }
 return effects;
}

} // namespace daybreak
