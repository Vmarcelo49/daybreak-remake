#pragma once
#include "keiichi_ground_shot.hpp"
namespace daybreak {
inline bool keiichi_walk_shot_state(unsigned state){return state>=410&&state<=412;}
struct KeiichiWalkShot {bool stopped=false;int direction=0;float turn=0;unsigned lower_tick=0;};
inline GroundShotEffects advance_keiichi_walk_shot(KeiichiWalkShot& s,unsigned state,unsigned phase,unsigned frame,
 bool complete,bool grounded,int x,int z,float& speed,float& offset,float& movement,float elevation,unsigned rounds,bool special){
 if(!keiichi_walk_shot_state(state))throw std::invalid_argument("Walking shot state");
 GroundShotEffects out;
 if(complete){out.next_state=(x||z)?10:0;return out;}
 if(!grounded){out.next_state=43;return out;}
 if(frame==0){s.stopped=false;s.turn=0;}
 if(frame>20){
  const bool moving=x||z;
  if(!moving&&!s.stopped){s.stopped=true;s.lower_tick=0;s.direction=0;s.turn=20;}
  else if(moving){
   if(s.stopped){s.stopped=false;s.lower_tick=0;}
   const int direction=z<0?(x>0?1:x<0?2:0):z>0?(x>0?5:x<0?7:6):(x>0?3:4);
   if(direction!=s.direction){s.direction=direction;s.turn=20;}
  }
 }
 speed=s.stopped?0.f:6.f;
 if(frame>12){s.turn=std::max(1.f,s.turn-1.f);steer_battle_offset(offset,x,z,s.turn);}
 if(phase==0&&frame==0){out.started=true;movement=0;}
 if(frame==(state==412?14u:13u)){
  out.fire=true;out.effect=86;out.voice=rounds==1?30:27;out.bullet_slot=special?3u:0u;
  const int low=state==410?-40:state==411?20:-100,high=state==410?40:state==411?100:-20;
  out.yaw=float(std::clamp(int(-offset),low,high));out.pitch=float(std::clamp(int(elevation),-40,40));
 }
 return out;
}
}
