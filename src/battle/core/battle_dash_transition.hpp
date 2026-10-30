#pragma once
#include "character_dispatch.hpp"
namespace daybreak {
struct BattleDashTransition {
 bool handled=false,clear_pitch=false,clear_speed=false,clear_vertical=false;
 bool clear_gravity=false,set_fall_gravity=false;
 int state=-1,phase=-1,frame=-1,positional_sound=-1;
};
inline void apply_battle_dash_transition_motion(const BattleDashTransition& transition,float& pitch,float& speed,float& vertical,float& gravity){
 if(transition.clear_pitch)pitch=0;
 if(transition.clear_speed)speed=0;
 if(transition.clear_vertical)vertical=0;
 if(transition.clear_gravity)gravity=0;
 if(transition.set_fall_gravity)gravity=.5f;
}
// Early exits of state332 only. Call before its movement/attack body; callers
// still own pre-handler services (notably character13 magazine update).
inline BattleDashTransition battle_dash_transition(unsigned c,unsigned w,unsigned phase,bool grounded,bool complete){
 character_action_dispatch(c,w);BattleDashTransition out;
 const bool pitch=c==0||c==2||c==5||c==11||c==15;
 if(c!=7&&complete){out.handled=true;out.state=(c==3||c==8||c==9)?0:43;out.clear_pitch=pitch;return out;}
 if(c==3){if(!grounded&&phase>2){out.handled=true;out.state=43;}return out;}
 if(c==8){
  if(grounded&&phase<2){out.handled=true;out.clear_vertical=out.clear_gravity=true;
   if(phase==0)out.state=334;else {out.phase=2;out.positional_sound=40;}}
  return out;
 }
 if(c==9){
  if(grounded&&phase<2){out.handled=true;out.phase=2;out.clear_speed=out.clear_vertical=true;out.clear_gravity=w!=0;}
  else if(!grounded&&phase==2){out.handled=true;out.state=43;out.set_fall_gravity=true;}
  return out;
 }
 const unsigned minimum=(c==1||c==4||c==10||c==12||c==13||c==14)?2:1;
 if(!grounded||phase<minimum)return out;
 out.handled=true;out.state=333;out.clear_pitch=pitch;out.clear_vertical=true;
 out.clear_speed=c!=6;out.clear_gravity=c==6||c==7||c==11||(c==15&&w==1);
 if(c==6)out.frame=24;
 return out;
}
}
