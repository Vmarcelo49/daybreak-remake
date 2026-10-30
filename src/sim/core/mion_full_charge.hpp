#pragma once
#include "mion_charge_shot.hpp"
namespace daybreak {
struct MionFullCharge {int ticks=0,interval=0,duration=0,pitch=0,hold=0;float gravity=0;};
struct MionFullChargeEffects : MionChargeEffects {unsigned statistics=0;std::vector<int> voice_arguments;};
//350/360 in4582a0/461810/44fa10. Full-charge actor bodies only;
// caller owns individual magazine admission and shared actor clocks.
template<class Random> MionFullChargeEffects advance_mion_full_charge(MionFullCharge& s,
 unsigned weapon,unsigned state,unsigned phase,unsigned frame,bool complete,bool grounded,
 float& speed,float& offset,float& movement,float& vertical,float elevation,int primary_rounds,unsigned shoot_held,Random&& random){
 if(weapon>2||(state!=350&&state!=360))throw std::invalid_argument("Unsupported Mion full charge");
 const bool air=state==360;MionFullChargeEffects out;
 if((!air||weapon==0)&&complete){out.next_state=air?43:0;return out;}
 if(!air&&!grounded){s.gravity=.5f;out.next_state=43;return out;}
 auto voice=[&](int id,int service,std::vector<int> args){out.voice=id;out.voice_service=service;out.voice_arguments=std::move(args);};
 auto turn=[&](float step){if(weapon==2)turn_air_shot(offset,movement,step);else approach_battle_offset(offset,0,step);};
 auto bullet=[&](unsigned slot,float yaw,float pitch){out.bullets.push_back({slot,yaw,pitch,out.models[0]});};
 if(air||phase<2||(phase==2&&frame<10)){out.models[0]=4;out.models[1]=-1;}
 if(phase==0&&frame==0){
  out.activate=true;speed=0;s.ticks=air||weapon==0?0:60;s.interval=s.duration=0;
  if(weapon==0){s.hold=0;if(!air)s.pitch=0;voice(33,2,{33,20,0});out.sounds.push_back(76);}
  if(air){vertical=-.5f;if(weapon!=0)s.gravity=.5f;if(weapon==1)out.sounds.push_back(76);}
 }
 if(weapon==0){
  if(s.ticks<10){++s.ticks;turn(18);if(!air)speed=std::max(0.f,speed-.5f);}else if(!air)speed=0;
 }else if(air){if(s.ticks<10){++s.ticks;turn(20);}}
 else if(phase==0){turn(20);speed=frame<10?std::max(0.f,speed-.5f):0.f;}
 if(phase==1){
  if(weapon==0){
   turn(1);++s.interval;++s.hold;
   if(frame>60&&s.interval>3&&s.duration<100){
    s.pitch=std::clamp(int(elevation),-30,30);out.sounds.push_back(75);s.interval=0;++s.duration;++out.statistics;
    volatile float pitch=float(int(random()%50)-10)*.1f;pitch=pitch+float(s.pitch);volatile float yaw=float(int(random()%50)-25)*.1f;bullet(5,yaw,pitch);
   }
   if((s.hold>100&&shoot_held!=0)||s.hold>390){out.next_phase=2;return out;}
  }else if(weapon==1){
   if(frame==0){voice(air?32:33,3,{air?32:33,3,air?10:20,0});out.statistics=5;if(!air)out.sounds.push_back(76);}
   if(frame<20)turn(1);++s.ticks;++s.interval;if(primary_rounds<=0)++s.duration;
   if(frame>=30&&frame<=60&&frame%5==0){
    if(frame==30){out.sounds.push_back(82);s.pitch=int(elevation);}s.pitch=std::clamp(s.pitch,-30,30);s.interval=0;bullet(2,0,float(s.pitch));
   }
   if(++s.duration>130){out.next_phase=2;return out;}
  }else{
   if(frame==0){voice(33,3,{33,3,20,0});out.statistics=5;}
   ++s.ticks;++s.interval;if(frame<10)turn(2);
   if(frame%5==0&&frame>9&&frame<91){
    if(frame==10){out.sounds.push_back(181);s.pitch=int(elevation);}s.pitch=std::clamp(s.pitch,-30,30);s.interval=0;bullet(8,0,float(s.pitch));
   }
   if(frame%5==0&&frame>89&&frame<121){if(frame==(air?60u:90u))out.sounds.push_back(182);bullet(4,0,float(s.pitch));}
   if(frame%5==0&&frame>89&&frame<141)bullet(9,0,float(s.pitch));
   if(++s.duration>190){out.next_phase=2;return out;}
  }
 }
 if(air&&phase>=2){vertical-=s.gravity;if(weapon==0)s.gravity=.5f;if(grounded&&vertical<0)out.next_state=361;}
 return out;
}
}
