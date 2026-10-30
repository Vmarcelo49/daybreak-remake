#pragma once
#include "keiichi_ground_shot.hpp"
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace daybreak {

// FUN_00435450 receives explicit world coordinates. The old callback fixture
// had a zeroed trigonometric table, so its x/z arguments lost these distances.
// Recovered from the same original handlers with the initialized cosine table.
inline void apply_roster_shot400_world_geometry(unsigned character,unsigned weapon,
 bool boosted,float elevation,std::vector<GroundShotEffects>& requests){
 unsigned index=0;
 for(auto& shot:requests){
  if(shot.origin!=GroundShotOrigin::World)continue;
  float forward=0,height=0,lateral=0,origin_yaw=0;
  int pitch_limit=40;
  switch(character){
   case 3:
    if(weapon==2){forward=100;height=70;lateral=index%2?50.f:-50.f;}
    break;
   case 4:
    if(weapon==0){forward=10;height=boosted?(index<2?100.f:40.f):70.f;
     lateral=index%2?-50.f:50.f;}
    break;
   case 5:
    if(weapon==0){forward=50;height=70;pitch_limit=30;}
    break;
   case 6:
    if(weapon<2){forward=50;height=weapon==0?150.f:125.f;
     if(weapon==0)pitch_limit=0;}
    break;
   case 8:
    if(weapon==1&&boosted){forward=100;height=80;pitch_limit=0;}
    break;
   case 9:
    if(weapon==2){forward=100;height=80;pitch_limit=0;}
    break;
   case 10:
    forward=100;height=100;
    if(weapon==0){if(index==1)origin_yaw=11;else if(index==2)origin_yaw=-11;}
    else if(weapon==2){if(index==1)origin_yaw=30;else if(index==2)origin_yaw=-30;}
    break;
   case 13:
    if(weapon==0){forward=20;height=70;pitch_limit=30;}
    else if(weapon==2){forward=100;height=70;pitch_limit=0;}
    break;
   case 14:
    if(weapon<2){forward=70;height=70;
     if(weapon==1&&boosted)lateral=index%2?-50.f:50.f;}
    break;
  }
  if(forward==0)throw std::invalid_argument("Unrecovered state400 world muzzle");
  shot.origin_height=height;
  shot.world_forward_x=shot.world_forward_z=forward;
  shot.world_lateral=lateral;
  shot.world_yaw=origin_yaw;
  shot.world_actor_heading_only=character==3&&weapon==2;
  shot.pitch=float(std::clamp(int(elevation),-pitch_limit,pitch_limit));
  ++index;
 }
}

}
