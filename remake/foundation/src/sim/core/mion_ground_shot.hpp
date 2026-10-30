#pragma once
#include "keiichi_ground_shot.hpp"
namespace daybreak {
// State400 in4582a0/461810/44fa10. This emits435000 attachment requests;
// the host must perform magazine admission and use the Mion projectile policy.
struct MionGroundShot {
 int ticks=0,shots=0,pitch=0,hold=0;
 float gravity=0;
};
struct MionGroundShotEffects {
 int next_state=-1,next_phase=-1,sound=-1,voice=-1,rewrite_frame=-1;
 bool activate=false,fire=false,hold_clock=false;
 unsigned attachment=0,bullet_slot=0;
};
inline MionGroundShotEffects advance_mion_ground_shot(MionGroundShot& s,unsigned weapon,
 unsigned phase,unsigned frame,bool complete,bool grounded,float& speed,float& offset,float& movement,
 float elevation,int rounds,int shoot_release,bool special){
 if(weapon>2)throw std::invalid_argument("Unsupported Mion ground shot");
 MionGroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){out.next_state=43;s.gravity=.5f;return out;}
 if(phase==0&&frame==0){
  out.activate=true;s.ticks=s.shots=0;
  if(weapon!=1)s.hold=0;
  if(weapon==0)s.pitch=0;
 }
 auto fire=[&](unsigned attachment,int limit){
  ++s.shots;s.pitch=std::clamp(int(elevation),-limit,limit);
  out.fire=true;out.attachment=attachment;out.bullet_slot=special?(weapon==1?4u:1u):0u;
  out.sound=weapon==0?72:weapon==1?80:179;
 };
 if(weapon==2){
  if(frame<19){++s.ticks;turn_air_shot(offset,movement,10);}
  if(frame<10){++s.ticks;turn_air_shot(offset,movement,15);}
  if(frame==10){frame=18;out.rewrite_frame=18;}
  speed=frame<18?std::max(0.f,speed-1.5f):std::min(0.f,speed+.5f);
  if(frame==18){movement=0;speed=-10;out.voice=rounds<2?30:28;fire(0,40);}
  if(frame==23&&s.hold<10){++s.hold;out.hold_clock=true;}
  return out;
 }
 if(s.ticks<10){++s.ticks;approach_battle_offset(offset,0,18);speed=std::max(0.f,speed-.5f);}
 else {speed=0;if(weapon==1&&phase<3)approach_battle_offset(offset,0,5);}
 if(weapon==0){
  if(phase==1||phase==3){
   approach_battle_offset(offset,0,phase==1?10.f:5.f);
   if(frame==2){fire(phase==1?0u:1u,phase==1?30:40);out.voice=rounds==1?30:27;}
   if(frame>6&&shoot_release>0&&shoot_release<10&&s.shots<6&&rounds>0)out.next_phase=phase==1?3:1;
  }
  if(phase==2&&frame==3)out.next_state=0;
 }else {
  if(phase==1){
   if(frame==2){out.voice=rounds<3?30:27;fire(0,40);}
   if(frame==10){out.next_phase=2;return out;}
  }
  if(phase==2&&frame==1&&rounds>0)fire(1,30);
  if((phase==2&&frame>7)||phase==3){
   if(s.shots<1){++s.shots;out.hold_clock=true;}else s.shots=0;
  }
 }
 return out;
}
}
