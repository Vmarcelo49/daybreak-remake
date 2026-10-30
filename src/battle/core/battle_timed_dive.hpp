#pragma once
#include "battle_steep_dive.hpp"
namespace daybreak {
struct BattleTimedDiveEffects : BattleSteepDiveEffects {bool sound_request=false;};
// Character7 state332: no animation-complete gate; misses end in state339.
inline BattleTimedDiveEffects advance_battle_timed_dive(unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float height){
 BattleTimedDiveEffects out;
 const auto transition=battle_dash_transition(7,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);out.next_state=transition.state;return out;}
 const bool first=s.phase==0&&s.frame==0;
 if(first){
  out.activate=out.initialize=out.clear_contact=out.reset_capacity=true;
  s.moving=0;s.speed=s.movement_angle=air.vertical=0;
  if(weapon!=1)out.frame_override=6;
 }
 if(s.phase==0)approach_battle_offset(s.offset,0,5);
 if(s.phase==1){
  ++s.moving;
  if(s.frame==0){
   out.sound_request=true;
   constexpr float pi=3.1415927410125732421875f;
   const float angle=std::clamp(float(std::atan2(double(height),double(float(std::sqrt(in.distance_squared))))/double(pi)*180.),-35.f,-5.f);
   const float speed=weapon==1?20.f:25.f;
   s.speed=legacy_trig(angle,false)*speed;air.vertical=legacy_trig(angle,true)*speed;
   const double radians=std::atan2(double(air.vertical),double(s.speed));
   volatile float turns=float(static_cast<long double>(radians)/3.1415927410125732421875L);
   volatile float degrees=turns*180.f;
   air.pitch=std::min(0.f,float(degrees)+5.f);air.pivot=70;
  }
  if(in.contact){out.next_state=334;return out;}
  if(s.moving>(weapon==1?45:30)){out.next_state=339;s.speed=10;return out;}
 }
 return out;
}
}
