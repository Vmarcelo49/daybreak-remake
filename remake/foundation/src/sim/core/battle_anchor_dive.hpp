#pragma once
#include "battle_leap_melee.hpp"
#include "battle_target_position.hpp"
namespace daybreak {
// Character4 weapon2, state332. Target must be virtual+4 selector2 (spine),
// not the target root. Keep the selected position explicit at the boundary.
inline BattleLeapMeleeEffects advance_battle_anchor_dive(KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,const std::array<float,3>& origin,const std::array<float,3>& target_spine){
 BattleLeapMeleeEffects out;
 const auto transition=battle_dash_transition(4,2,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);out.next_state=transition.state;return out;}
 if(s.phase==0&&s.frame==0)out.activate=out.initialize=true;
 if(s.phase==0)approach_battle_offset(s.offset,0,5);
 if(s.phase==0&&s.frame==0){s.moving=0;s.speed=s.movement_angle=air.vertical=0;out.clear_contact=out.reset_capacity=true;}
 if(s.phase==1){
  if(s.frame==0){
   out.voice=2;out.voice_argument=10;
   const float angle=std::clamp(battle_target_elevation(origin,target_spine),-20.f,-5.f);
   s.speed=legacy_trig(angle,false)*25.f;air.vertical=legacy_trig(angle,true)*25.f;
   const double radians=std::atan2(double(air.vertical),double(s.speed));
   volatile float turns=float(static_cast<long double>(radians)/3.1415927410125732421875L);
   volatile float degrees=turns*180.f;
   air.pitch=std::min(0.f,float(degrees)+10.f);air.pivot=70;
  }
  if(in.contact){air.vertical=s.speed=air.gravity=0;out.next_state=334;out.clear_contact=out.reset_capacity=true;return out;}
  if(s.frame>20){s.moving=0;out.next_phase=2;return out;}
 }
 if(s.phase==2&&++s.moving>10){s.moving=0;out.next_phase=3;s.speed=10;return out;}
 if(s.phase>1){air.vertical-=air.gravity;s.speed=std::max(0.f,s.speed);}
 return out;
}
}
