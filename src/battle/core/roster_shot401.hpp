#pragma once
#include "roster_ground_shot400.hpp"
#include "roster_shot401_schedule.hpp"
#include "roster_shot401_world.hpp"

namespace daybreak {

inline bool roster_shot401_ignores_completion(unsigned character,unsigned weapon){
 return (character==8&&weapon==2)||(character==13&&weapon==2)||
        (character==14&&weapon<=1);
}
inline bool roster_shot401_ignores_airborne(unsigned character,unsigned weapon){
 return (character==8&&weapon>=1)||(character==13&&weapon==2)||
        (character==14&&weapon<=1);
}
inline GroundShotEffects advance_roster_shot401(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,bool complete,bool grounded,
 std::vector<GroundShotEffects>& requests,int& next_phase,bool boosted=false,float elevation=0){
 if(character<3||character>15||weapon>2||(character>=14&&weapon>1))
  throw std::invalid_argument("Unsupported roster state401 binding");
 GroundShotEffects out;out.attack_calls=0;out.count_attack=false;next_phase=-1;
 // Original complete/airborne priority sampled at the final DAT phase and at
 // frame12 respectively. Four delayed handlers intentionally do not exit here.
 if(complete&&!roster_shot401_ignores_completion(character,weapon)){out.next_state=0;return out;}
 if(!grounded&&!roster_shot401_ignores_airborne(character,weapon)){out.next_state=43;return out;}
 out=boosted?advance_roster_shot_schedule(roster_shot401_boosted_events,character,weapon,phase,frame,requests,next_phase):
  advance_roster_shot_schedule(roster_shot401_events,character,weapon,phase,frame,requests,next_phase);
 apply_roster_shot401_world_geometry(character,weapon,boosted,elevation,requests);
 return out;
}

}
