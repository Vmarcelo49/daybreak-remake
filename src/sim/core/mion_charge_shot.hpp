#pragma once
#include "keiichi_ground_shot.hpp"
#include <vector>
namespace daybreak {
inline bool mion_charge_shooting_state(unsigned state){return state==350||state==360||state==361||(state>=450&&state<=454)||state==460||state==469;}
struct MionChargeShot {int pitch=0,shots=0,spread_pitch=0,hold=0;float gravity=0;};
struct MionChargeBullet {unsigned slot=0;float yaw=0,pitch=0;int model=0;};
struct MionChargeEffects {
 int next_state=-1,next_phase=-1,voice=-1,voice_service=0;
 bool activate=false,hold_clock=false,recover_gauge=false;
 int models[2]={0,1};
 std::vector<int> sounds;
 std::vector<MionChargeBullet> bullets;
};
// Ground450 for three weapons and pistol451..454. Request order is retained:
// water uses15 separate spawns, laser draws pitch before yaw. The host owns
// magazine admission, activation422900 and actual voice/sound services.
template<class Random> MionChargeEffects advance_mion_ground_charge(MionChargeShot& s,
 unsigned weapon,unsigned state,unsigned phase,unsigned frame,bool complete,bool grounded,
 float& speed,float& offset,float& movement,float elevation,int rounds,bool special,Random&& random){
 if(weapon>2||!(state==450||(weapon==0&&state>=451&&state<=454)))throw std::invalid_argument("Unsupported Mion ground charge");
 MionChargeEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){out.next_state=43;s.gravity=.5f;return out;}
 if(phase==0&&frame==0)out.activate=true;
 if(weapon==0){
  if(state==450){if(frame<17)approach_battle_offset(offset,0,25);if(frame>20)speed=std::min(0.f,speed+.35f);}
  if(state==451){if(frame<17)approach_battle_offset(offset,0,10);else if(frame<26)approach_battle_offset(offset,0,4);}
  if(state==452){if(frame<14)approach_battle_offset(offset,0,9);else if(frame<26)approach_battle_offset(offset,0,4);}
  if(state==453&&frame<20)approach_battle_offset(offset,0,10);
  if(state==454&&frame<10)approach_battle_offset(offset,0,9);
  if((state==451||state==452)&&frame>23)speed=std::max(0.f,speed-.5f);
  if(state==453&&frame>37)speed=std::max(0.f,speed-.5f);
  if(state==454&&frame>37)speed=std::min(0.f,speed+.5f);
  out.models[0]=frame<(state==453?21u:18u)?2:3;out.models[1]=-1;
  if(state!=452&&frame>(state==450?47u:50u)){out.models[0]=0;out.models[1]=1;}
  if(frame==0){movement=state==451?-90.f:state==452?90.f:state==453?180.f:0.f;speed=state==450||state==454?0.f:10.f;if(state<=452)s.hold=0;}
  if(frame==(state==453?20u:17u)){
   out.voice=rounds==1?30:29;out.voice_service=state==450&&rounds!=1?1:2;
   if(state==450){movement=0;speed-=15;}
   if(state==451||state==452){movement=state==451?-135.f:135.f;speed=15;}
   if(state==453)speed=15;
   if(state==454){speed=-10;out.models[0]=3;out.models[1]=-1;}
   s.pitch=std::clamp(int(elevation),state==453?-55:-40,state==453?55:state==450?45:40);
   out.sounds.push_back(73);out.bullets.push_back({special?3u:2u,0,float(s.pitch),out.models[0]});
  }
  if(state<=452&&frame==23&&s.hold<(state==450?30:20)){++s.hold;out.hold_clock=true;}
  return out;
 }
 out.models[0]=2;out.models[1]=-1;
 if(weapon==1){
  if(frame<17)turn_air_shot(offset,movement,25);
  if(frame>0)speed=std::max(0.f,speed-.35f);
  if(frame==17){
   out.voice=29;out.voice_service=2;movement=0;speed-=15;out.sounds={81,75};
   s.spread_pitch=std::clamp(int(elevation),-45,45);s.shots=0;
   for(unsigned i=0;i<15;++i){volatile float pitch=float(int(random()%100)-50)*.1f;pitch=pitch+float(s.spread_pitch);volatile float yaw=float(int(random()%200)-100)*.1f;out.bullets.push_back({special?5u:1u,yaw,pitch,2});}
  }
 }else {
  if(phase==0&&frame==0)s.hold=0;
  if(phase==0)turn_air_shot(offset,movement,20);
  speed=speed<0?std::min(0.f,speed+1.5f):std::max(0.f,speed-1.5f);
  if(phase==1){
   if(s.hold<10)turn_air_shot(offset,movement,.5f);
   if(frame==0){out.voice=29;out.voice_service=2;movement=0;}
   if(frame>=15&&frame%5==0&&s.hold<10&&rounds>0){
    s.spread_pitch=std::clamp(int(elevation),-45,45);out.sounds.push_back(180);s.shots=0;++s.hold;
    volatile float pitch=float(int(random()%80)-40)*.1f;pitch=pitch+float(s.spread_pitch);volatile float yaw=float(int(random()%100)-50)*.1f;
    out.bullets.push_back({special?3u:2u,yaw,pitch,2});
   }
   if(frame>100)out.next_phase=2;
  }
 }
 return out;
}
inline MionChargeEffects advance_mion_charge_landing(MionChargeShot& s,bool complete,
 float& speed,float& movement,float& vertical){
 MionChargeEffects out;
 if(complete){out.next_state=0;return out;}
 s.gravity=0;speed=movement=vertical=0;out.recover_gauge=true;return out;
}
template<class Random> MionChargeEffects advance_mion_air_charge(MionChargeShot& s,
 unsigned weapon,unsigned phase,unsigned frame,bool complete,bool grounded,
 float& speed,float& offset,float& movement,float& vertical,float elevation,int rounds,bool special,Random&& random){
 if(weapon>2)throw std::invalid_argument("Unsupported Mion air charge");
 MionChargeEffects out;
 if(complete){out.next_state=43;return out;}
 if(grounded&&vertical<0){out.next_state=469;return out;}
 if(phase==0&&frame==0){out.activate=true;if(weapon!=1)s.hold=0;if(weapon==2)vertical=speed=0;}
 out.models[0]=2;out.models[1]=-1;
 if(weapon==0){
  if(frame<15)turn_air_shot(offset,movement,15);
  if(frame>=18)out.models[0]=3;
  if(frame>50){out.models[0]=0;out.models[1]=1;}
  if(frame==17){
   out.voice=rounds==1?30:29;out.voice_service=2;movement=0;speed=-10;vertical=5;
   s.pitch=std::clamp(int(elevation),-40,40);out.sounds.push_back(73);
   out.bullets.push_back({special?3u:2u,0,float(s.pitch),out.models[0]});
  }
  s.gravity=.5f;vertical-=s.gravity;
  if(frame==23&&s.hold<20){++s.hold;out.hold_clock=true;}
 }else if(weapon==1){
  if(frame<17)turn_air_shot(offset,movement,20);
  if(frame==17){
   out.voice=29;out.voice_service=2;movement=0;speed-=10;vertical=5;out.sounds={81,81};
   s.spread_pitch=int(elevation);if(s.spread_pitch<-30)s.spread_pitch=-45;if(s.spread_pitch>30)s.spread_pitch=45;s.shots=0;
   for(unsigned i=0;i<15;++i){volatile float pitch=float(int(random()%100)-50)*.1f;pitch=pitch+float(s.spread_pitch);volatile float yaw=float(int(random()%200)-100)*.1f;out.bullets.push_back({special?5u:1u,yaw,pitch,2});}
  }
  s.gravity=.5f;vertical-=s.gravity;
 }else{
  if(phase==0)turn_air_shot(offset,movement,20);
  if(phase==1){
   if(s.hold<10)turn_air_shot(offset,movement,.5f);
   if(frame==0){out.voice=29;out.voice_service=2;movement=0;}
   if(frame>=15&&frame%5==0&&s.hold<10&&rounds>0){
    out.sounds.push_back(180);s.spread_pitch=std::clamp(int(elevation),-45,45);s.shots=0;++s.hold;
    volatile float pitch=float(int(random()%80)-40)*.1f;pitch=pitch+float(s.spread_pitch);volatile float yaw=float(int(random()%100)-50)*.1f;
    out.bullets.push_back({special?3u:2u,yaw,pitch,2});
   }
   if(frame>100){out.next_phase=2;return out;}
  }
  s.gravity=.5f;if(phase==2)vertical-=s.gravity;
 }
 return out;
}
}
