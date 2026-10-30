#pragma once
#include "character_dispatch.hpp"
#include "keiichi_followup.hpp"
#include <algorithm>

namespace daybreak {

struct RosterFollowup301Profile {
 float start_speed=-1,clock_speed=0,deceleration=0;
 int clock_set=-1,clock_stop=-1,decelerate_from=-1;
 int effect_frame=-1,effect_id=-1,second_effect_frame=-1,second_effect_id=-1;
 bool restart_each_phase=false;
};

inline RosterFollowup301Profile roster_followup301_profile(unsigned character,unsigned weapon){
 character_action_dispatch(character,weapon);
 switch(character){
  case 3:return {0,20,0,13,34,-1,8,61,34,40,true};
  case 4:
   if(weapon==2)return {0,25,4,6,-1,17,8,62,-1,-1,true};
   return {0,15,0,6,17,-1,8,62,-1,-1,true};
  case 5:return {30,0,0,-1,6,-1,4,61,-1,-1,true};
  case 6:return {0,15,.75f,14,-1,15,15,61,-1,-1,true};
  case 7:return {15,10,1,19,33,0,4,61,28,62,false};
  case 8:return {-1,25,0,12,24,-1,18,62,-1,-1,false};
  case 9:return {20,0,0,-1,6,-1,9,61,-1,-1,true};
  case 10:return {15,0,1,-1,-1,0,11,61,-1,-1,true};
  case 11:return {30,0,0,-1,8,-1,6,61,-1,-1,true};
  case 12:return {15,10,0,7,15,-1,8,61,-1,-1,false};
  case 13:return {0,30,0,8,14,-1,9,61,-1,-1,true};
  case 14:
   return {0,weapon==0?22.5f:18.5f,weapon==0?2.f:1.5f,12,-1,17,8,62,-1,-1,true};
  case 15:return {-1,25,0,10,17,-1,12,61,-1,-1,false};
  default:throw std::out_of_range("Dedicated fighter has no preview follow-up profile");
 }
}

inline KeiichiFollowupEffects advance_roster_followup301(
 unsigned character,unsigned weapon,KeiichiFollowup& state,const KeiichiFollowupInput& input){
 const auto profile=roster_followup301_profile(character,weapon);
 const float incoming_speed=state.speed;
 auto effects=advance_keiichi_followup(state,input);
 if(effects.next_state>=0)return effects;
 state.speed=incoming_speed;
 effects.effect=effects.voice=-1;effects.voice_argument=0;
 if(state.frame==0&&profile.start_speed>=0&&
    (state.phase==0||profile.restart_each_phase))state.speed=profile.start_speed;
 if(profile.decelerate_from>=0&&state.frame>=profile.decelerate_from&&
    !(character==7&&state.frame>=19))
  state.speed=std::max(0.f,state.speed-profile.deceleration);
 if(state.frame==profile.clock_set)state.speed=profile.clock_speed;
 if(state.frame==profile.clock_stop)state.speed=0;
 if(state.frame==profile.effect_frame){effects.effect=profile.effect_id;effects.voice=2;effects.voice_argument=10;}
 if(state.frame==profile.second_effect_frame){effects.effect=profile.second_effect_id;effects.voice=3;effects.voice_argument=10;}
 return effects;
}

} // namespace daybreak
