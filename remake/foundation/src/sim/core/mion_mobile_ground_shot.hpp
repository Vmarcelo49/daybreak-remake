#pragma once
#include "mion_air_shot.hpp"
namespace daybreak {
inline bool mion_mobile_ground_shot_state(unsigned state){return state==401||(state>=404&&state<=407)||(state>=410&&state<=412);}
struct MionMobileGroundShotEffects : MionAirShotEffects {int attachment_model=-1;};
//401/404..407/410..412 in the three original Mion updates.
inline MionMobileGroundShotEffects advance_mion_mobile_ground_shot(MionGroundShot& s,unsigned weapon,unsigned state,
 unsigned phase,unsigned frame,bool complete,bool grounded,float& speed,float& offset,float& movement,
 float elevation,int rounds,int release,int x,int z,bool special){
 if(weapon>2||!mion_mobile_ground_shot_state(state))throw std::invalid_argument("Unsupported Mion mobile ground shot");
 MionMobileGroundShotEffects out;
 if(complete){out.next_state=0;return out;}
 if(!grounded){s.gravity=.5f;out.next_state=43;return out;}
 if(phase==0&&frame==0)out.activate=true;
 auto fire=[&](unsigned count,int limit,unsigned special_slot,int sound){
  s.ticks=std::clamp(int(elevation),-limit,limit);out.pitch=float(s.ticks);out.fire=true;out.shot_count=count;
  out.bullet_slot=special?special_slot:0;out.sound=sound;
 };
 if(state==401||state>=410){
  const unsigned turn_end=weapon==0||state==401?15:14;
  if(frame<turn_end)approach_battle_offset(offset,0,20);else if(state>=411)approach_battle_offset(offset,0,4);
  if(frame==0){
   speed=8;movement=state==401?180.f:state==410?0.f:(state==411?-1.f:1.f)*(z<0?45.f:z>0?135.f:90.f);
   if(weapon!=0)s.shots=0;
  }
  if(frame==15){out.voice=rounds<(weapon==2?2:3)?30:27;fire(2,40,weapon==0?1:4,weapon==0?72:weapon==2&&state==401?179:80);}
  if(weapon==0){
   if(frame>29&&rounds>1&&release>0&&release<10)out.next_state=x>0?411:x<0?412:z<0?410:z>0?401:-1;
  }else {
   if(frame==28)speed=0;
   if(frame>29){if(s.shots<1){++s.shots;out.hold_clock=true;}else s.shots=0;}
  }
  return out;
 }
 if(weapon<2){
  if(state==405||state==406){if(frame<10)approach_battle_offset(offset,0,10);else if(frame<26)approach_battle_offset(offset,0,6);}
  else if(state==407&&frame<10)approach_battle_offset(offset,0,9);
  if(frame>26)speed=std::max(0.f,speed-.5f);
  if(frame==0){movement=state==404?0.f:state==405?-90.f:state==406?90.f:180.f;speed=10;}
  const bool shot=weapon==1?frame==10:state==407?(frame==5||frame==10||frame==15):(frame==10||frame==15||frame==20);
  if(shot){if(frame==10)out.voice=rounds<(weapon==0?7:3)?30:28;fire(2,state==407?40:30,weapon==0?1:4,weapon==0?72:80);}
 }else {
  if(frame<(state==407?21u:18u))turn_air_shot(offset,movement,state==404?10.f:state==407?17.f:12.f);
  if(frame>(state==404||state==407?37u:23u))speed=state==404?std::min(0.f,speed+.5f):std::max(0.f,speed-.5f);
  if(frame==0){movement=state==404?0.f:state==405?-90.f:state==406?90.f:180.f;speed=state==404?0.f:10.f;if(state==405||state==406)s.hold=0;}
  if(frame==(state==407?20u:17u)){
   out.voice=rounds==1?30:28;
   if(state==404){speed=-10;out.attachment_model=3;}
   else {speed=15;if(state==405||state==406)movement=state==405?-135.f:135.f;}
   fire(1,state==407?55:40,1,179);
  }
  if((state==405||state==406)&&frame==23&&s.hold<10){++s.hold;out.hold_clock=true;}
 }
 return out;
}
// Ground release dispatch. A valid forward-dash gate with neutral axes consumes
// the input without falling through, matching the original early return.
struct MionGroundShotAdmission {int state=-1;float offset_delta=0;bool consumed=false;};
template<class Priority> MionGroundShotAdmission mion_ground_shot_admission(unsigned weapon,unsigned current,int priority,int x,int z,Priority first){
 if(current==20&&priority<=first(404)){if(z)return {404,0};if(x>0)return {405,90};if(x<0)return {406,-90};return {-1,0,true};}
 if(current==23&&priority<=first(405))return {405,0};
 if(current==24&&priority<=first(406))return {406,0};
 if(current==27&&priority<=first(406))return {407,0};
 if(priority>first(400))return {};
 if(current==10&&weapon!=2){
  if(x>0&&(weapon==0||priority<=first(411)))return {411,0};
  if(x<0&&(weapon==0||priority<=first(412)))return {412,0};
  if(z<0&&(weapon==0||priority<=first(410)))return {410,0};
  if(z>0&&(weapon==0||priority<=first(401)))return {401,0};
 }
 return {400,0};
}
}
