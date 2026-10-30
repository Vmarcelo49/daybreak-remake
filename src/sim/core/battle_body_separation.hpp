#pragma once
#include "battle_world.hpp"
#include <cmath>
namespace daybreak {
// 6394c0 after4202b0/420880 for all actors. No team, HP or hitstop filter.
// Displacement uses42cb50, so stage walls constrain each half independently.
template<class Wall> void separate_battle_bodies(BattleWorld& world,Wall& wall){
 for(unsigned a=0;a<4;++a)for(unsigned b=a+1;b<4;++b){
  auto& first=world.actors[a];auto& second=world.actors[b];
  if(first.motion.blocked||second.motion.blocked)continue; // +aecc proxy
  float x=first.position[0]-second.position[0],z=first.position[2]-second.position[2];
  float distance=std::sqrt(x*x+z*z);const float height=std::abs(first.position[1]-second.position[1]);
  if(distance==0){x=1;distance=1;} // Original leaves effective separation at59 here.
  const float reciprocal=1.f/distance;x*=reciprocal;z*=reciprocal;
  if(distance<60.f&&height<60.f){
   const float half=(60.f-distance)/2.f;
   world.move_horizontal(a,{x*half,0,z*half},wall);
   world.move_horizontal(b,{-x*half,0,-z*half},wall);
  }
 }
}
}
