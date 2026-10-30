#pragma once
#include "legacy_trig.hpp"
#include <algorithm>

namespace daybreak {
// Character 3's three slot-6 handlers use the same state135 motion. The
// original stores pitch at actor+100, base speed at+108 and model tilt at+2c.
struct BattleThrowVictim135 {
 float speed=0,vertical=0,gravity=.5f,heading_offset=0,pitch=0,base_speed=0;
 float model_pitch=0,pivot=0;
};
struct BattleThrowVictim135Transition {unsigned state=0;float horizontal=0,vertical=0;};

inline BattleThrowVictim135Transition advance_battle_throw_victim135(
 BattleThrowVictim135& s,unsigned frame,bool wall_contact,bool grounded,
 int x,int z,float impact_horizontal,float impact_vertical){
 if(frame==0){
  volatile float horizontal=-impact_horizontal;
  s.speed=horizontal*.01f;s.vertical=impact_vertical*.01f;
  s.base_speed=s.speed;s.pitch=0;s.gravity=.5f;
 }
 if(wall_contact){s.model_pitch=0;return {113,15.f,3.f};}
 // The model tilt is set before the input changes pitch on this tick.
 s.model_pitch=-90.f+s.pitch;s.pivot=70.f;
 if(grounded&&s.vertical<0){
  s.vertical=0;s.speed*=.5f;s.model_pitch=0;
  return {119,0,0};
 }
 if(frame<121){
  if(x<0)s.heading_offset+=1.f;else if(x>0)s.heading_offset-=1.f;
  if(z<0)s.pitch+=1.f;else if(z>0)s.pitch-=1.f;
  s.pitch=std::clamp(s.pitch,-30.f,30.f);
  s.speed=float(double(legacy_trig(s.pitch,false))*double(s.base_speed));
  s.vertical=float(double(legacy_trig(s.pitch,true))*double(s.base_speed));
 }else s.vertical-=s.gravity;
 return {};
}
}
