#pragma once
#include "battle_leap_melee.hpp"
namespace daybreak {
struct BattleSteepDiveEffects : BattleLeapMeleeEffects {int frame_override=-1;};
inline BattleSteepDiveEffects advance_battle_steep_dive(unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float height){
 BattleSteepDiveEffects out;
 const auto transition=battle_dash_transition(6,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){
  apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);
  out.next_state=transition.state;out.frame_override=transition.frame;return out;
 }
 if(s.phase==0)approach_battle_offset(s.offset,0,5);
 if(s.phase==0&&s.frame==0){
  out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;
  s.speed=s.movement_angle=air.vertical=0;
 }
 if(s.phase==1){
  approach_battle_offset(s.offset,0,1);
  if(s.frame==0){
   out.voice=3;out.voice_argument=10;
   constexpr float pi=3.1415927410125732421875f;
   const float angle=std::clamp(float(std::atan2(double(height),double(float(std::sqrt(in.distance_squared))))/double(pi)*180.),-35.f,-20.f);
   const float speed=weapon==0?21.f:20.f;
   s.speed=legacy_trig(angle,false)*speed;air.vertical=legacy_trig(angle,true)*speed;
   // Original x87 single-precision control rounds the division before *180.
   const double radians=std::atan2(double(air.vertical),double(s.speed));
   volatile float turns=float(static_cast<long double>(radians)/3.1415927410125732421875L);
   volatile float degrees=turns*180.f;
   air.pitch=std::min(0.f,float(degrees));air.pivot=70;
  }
  if(s.frame>45){out.next_phase=2;return out;}
 }
 if(s.phase>1){
  if(air.pitch>0)air.pitch=std::max(0.f,air.pitch-5);
  if(air.pitch<0)air.pitch=std::min(0.f,air.pitch+5);
  if(air.gravity==0)air.gravity=.5f;
  air.vertical-=air.gravity;s.speed=std::max(0.f,s.speed);
 }
 return out;
}
}
