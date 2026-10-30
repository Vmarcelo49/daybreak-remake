#pragma once
#include "keiichi_ground_shot.hpp"
#include <vector>

namespace daybreak {

struct RosterShot400Clock {
 unsigned countdown=0,shots=0,hold=0;
};

// 5b9680 and 5a7ea0 retain actor scratch across repeated visits to the same
// frame. The ordinary event table describes the first visit; this corrects
// subsequent visits and returns the effective original frame-counter delta.
inline int advance_roster_ground_shot400_clock(unsigned character,unsigned weapon,
 unsigned phase,unsigned frame,unsigned rounds,RosterShot400Clock& clock,
 GroundShotEffects& shot,std::vector<GroundShotEffects>& requests,int default_delta){
 if(character==12&&weapon==1){
  if(phase==0&&frame==0){clock.countdown=5;clock.shots=0;}
  if(phase==0&&frame==10){
   const bool fire=rounds>0&&clock.countdown>4&&clock.shots<2;
   if(!fire){
    requests.clear();shot.fire=false;shot.effect=-1;shot.voice=-1;
    shot.attack_calls=0;shot.count_attack=false;
   }else{
    if(clock.shots)shot.voice=-1; // Voice is emitted only for the first pulse.
    ++clock.shots;clock.countdown=0;
   }
   if(rounds>0&&clock.shots<2){++clock.countdown;return 0;}
   return 16; // 5b9680 writes frame25, then the common clock advances to26.
  }
 }
 if(character==13&&weapon==2){
  if(phase==0&&frame==0)clock.hold=0;
  if(frame==5){
   if(clock.hold<2){++clock.hold;return 0;}
   clock.hold=0;return 1;
  }
  if(frame==19){
   if(clock.hold<30){++clock.hold;return 0;}
   return 1;
  }
 }
 return default_delta;
}

}
