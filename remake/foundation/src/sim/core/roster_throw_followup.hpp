#pragma once
#include "battle_throw.hpp"
#include "keiichi_ground_shot.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {

inline bool roster_throw_parent_contact_state(unsigned character,unsigned weapon,
 unsigned state,unsigned phase){
 return (character==8&&weapon==1&&phase==2&&
         (state==350||state==360||state==450||state==460))||
        (character==15&&weapon==0&&phase==1&&(state==350||state==360));
}

inline bool roster_throw_followup_state(unsigned character,unsigned weapon,unsigned state){
 return (character==8&&weapon==1&&(state==351||state==451||state==461||state==462))||
        (character==15&&weapon==0&&state==351);
}

struct RosterThrowFollowup {
 GroundShotEffects shot{};
 int next_phase=-1,frame_delta=1;
 int capture_state=-1,victim_state=-1,damage_state=-1;
 int damage=0;
 bool bind_prop2=false,release=false;
 BattleThrowRelease release_data{};
};

// 004ccc00 / 005e2af0. The capture and damage requests act on the paired
// victim through 422950/422ab0/422bd0; they are not attacker transitions.
inline RosterThrowFollowup advance_roster_throw_followup(unsigned character,unsigned weapon,
 unsigned state,unsigned phase,unsigned frame,bool complete,bool grounded,
 float& speed,float& offset,float& movement,float& vertical,float& gravity){
 if(!roster_throw_followup_state(character,weapon,state))
  throw std::invalid_argument("Unsupported roster throw follow-up");
 RosterThrowFollowup out;out.shot.attack_calls=0;out.shot.count_attack=false;
 if(character==8){
  if(complete){out.shot.next_state=(state==461||state==462)?451:grounded?0:43;out.frame_delta=0;return out;}
  if(state==461){
   if(grounded&&vertical<0){out.shot.next_state=451;vertical=0;out.frame_delta=0;}
   else vertical-=.5f;
   return out;
  }
  if(state==462){speed=movement=vertical=gravity=0;return out;}
  if(state==351){
   if(phase>1&&!grounded){out.shot.next_state=43;gravity=.5f;
    out.frame_delta=0;return out;}
   if(phase==0){
    approach_battle_offset(offset,180.f,5.f);
    if(frame==1){out.shot.voice=32;out.shot.voice_priority=20;}
    if(frame==18){movement=180.f;vertical=75.f;}
    else if(frame>18)vertical-=2.f;
   }else if(phase==1){
    vertical-=2.f;
    if(!grounded)speed=0;
    if(grounded&&vertical<0){
     out.release=true;out.release_data={121,196,5000,1,0.f,0.f,0.f};
     out.shot.effect=133;out.shot.fire=true;out.shot.bullet_slot=3;
     out.shot.origin=GroundShotOrigin::AttachmentZero;
     out.next_phase=2;out.frame_delta=0;vertical=0;
    }
   }else if(phase==2)speed=0;
   return out;
  }
  // State451 is the ground follow-up of the weapon-1 charge grab.
  if(phase==0){
   if(frame==0){speed=0;out.shot.effect=132;}
   if(frame==6)out.capture_state=189;
  }else if(phase==1){
   speed=std::max(0.f,speed-.5f);movement=0;
   if(frame>=76){out.next_phase=2;out.frame_delta=0;}
  }else if(phase==2){
   if(frame==0){speed=0;offset=0;}
   if(frame==3){
    out.shot.voice=33;out.shot.voice_priority=20;out.shot.voice_choice=0;out.release=true;
    out.release_data={133,198,3500,1,180.f,3500.f,500.f};
   }
  }
  if(!grounded&&(phase!=0||frame!=0))vertical-=.1f;
  return out;
 }
 // Natsumi weapon 0 state351: throw, repeated held damage, release.
 if(complete){out.shot.next_state=0;out.frame_delta=0;return out;}
 if(phase==0){
  if(grounded){speed=std::max(0.f,speed-2.f);vertical=0;}
  else vertical-=1.f;
  if(frame==6){out.victim_state=188;
   if(!grounded||speed!=0)out.frame_delta=0;}
  if(frame==7)out.bind_prop2=true;
 }else if(phase==1){
  if(frame%9==3){out.damage_state=188;out.damage=500;out.shot.effect=22;}
  if(frame>117){out.next_phase=2;out.frame_delta=0;}
 }else if(phase==2&&frame==43){
  out.release=true;out.release_data={113,198,2500,1,180.f,3500.f,0.f};
  out.shot.effect=225;
 }
 return out;
}

} // namespace daybreak
