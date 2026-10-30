#pragma once
#include "keiichi_attack300.hpp"
#include "legacy_trig.hpp"
#include "battle_dash_transition.hpp"
#include <algorithm>
namespace daybreak {
// 46a190/473610/47b940 state320. Persistent +f0 chase strength and +58 gravity.
struct KeiichiAirMelee {
 int strength=0;unsigned ticks=0;
 float vertical=0,gravity=0,pitch=0,pivot=0;
};
inline KeiichiAttack300Effects advance_keiichi_air_melee(KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float height_difference){
 KeiichiAttack300Effects out;
 if(in.animation_complete){out.next_state=43;air.pitch=0;return out;}
 if(air.gravity==0)air.gravity=.5f;
 if(s.phase==2&&s.frame>10){
  air.vertical-=air.gravity;
  if(in.grounded){out.next_state=329;s.speed=air.vertical=air.pitch=0;return out;}
 }
 constexpr float pi=3.1415927410125732421875f;
 auto angle=[&](){return float(std::atan2(double(air.vertical),double(s.speed))/double(pi)*180.);};
 const bool first=s.phase==0&&s.frame==0;
 if(first){
  s.movement_angle=0;s.moving=s.contact_seen=0;air.ticks=0;air.strength=0;
  out.initialize=out.clear_contact=true;air.vertical=std::clamp(air.vertical,-3.f,3.f);s.speed=11.5f;
  if(in.distance_squared<810000.){air.strength=225;approach_battle_offset(s.offset,0,180);}
  air.pitch=angle()+20;air.pivot=70;
 }
 ++air.ticks;
 if(s.phase<2&&air.strength>0){
  const float target_angle=float(std::atan2(double(height_difference),double(float(std::sqrt(in.distance_squared))))/double(pi)*180.+10.);
  float current=first?target_angle:angle();
  if(current>target_angle)current=std::max(target_angle,current-5);
  if(current<target_angle)current=std::min(target_angle,current+5);
  current=std::clamp(current,-30.f,55.f);
  const float magnitude=float(air.strength)*.1f;
  s.speed=legacy_trig(current,false)*magnitude;air.vertical=legacy_trig(current,true)*magnitude;
  air.pitch=angle()+20;air.pivot=70;approach_battle_offset(s.offset,0,4);
  air.strength=std::max(140,air.strength-4);
 }
 if(s.phase==1){
  approach_battle_offset(s.offset,0,3);
  if(s.frame>10&&(double(float(in.distance_squared))+double(height_difference)*height_difference<40000.||s.frame>20||air.strength==0)){out.next_phase=2;return out;}
 }
 if(s.phase==2){
  if(s.frame==0){
   out.effect=62;out.voice=1;out.voice_argument=10;
   if(in.distance_squared<40000.&&std::abs(s.offset)<30)for(unsigned i=0;i<3;++i)if(in.voice_flags[i]==1){out.voice=i==0?0:i==1?15:5;out.voice_argument=12;break;}
  }
  if(s.frame>25){if(air.pitch>0)air.pitch=std::max(0.f,air.pitch-5);if(air.pitch<0)air.pitch=std::min(0.f,air.pitch+5);}
 }
 out.strike=s.phase==2&&s.frame<8;return out;
}
struct KeiichiDashMeleeEffects {
 KeiichiAttack300Effects action;
 bool disable_contact=false,sound_request=false; // 422490(3,0,10,0), not423d0 voice selection.
 bool reset_contact_capacity=false;
};
// State332: 46a190/473610/47b940. Early exits use the shared original policy.
inline KeiichiDashMeleeEffects advance_keiichi_dash_melee(KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float height_difference,unsigned weapon=0,unsigned character=2){
 if(character!=0&&character!=2&&character!=5&&character!=11&&character!=15)throw std::invalid_argument("Unrecovered dive family");
 KeiichiDashMeleeEffects out;auto& action=out.action;
 const auto transition=battle_dash_transition(character,weapon,s.phase,in.grounded,in.animation_complete);
 if(transition.handled){
  apply_battle_dash_transition_motion(transition,air.pitch,s.speed,air.vertical,air.gravity);
  action.next_state=transition.state;return out;
 }
 if(s.phase==0)approach_battle_offset(s.offset,0,5);
 if(s.phase==0&&s.frame==0){action.initialize=action.clear_contact=true;s.speed=s.movement_angle=air.vertical=0;}
 if(s.phase==1){
  // 46cdee..46ce28 compares signed offset<90, then abs(boolean). Not abs(offset).
  if(s.offset<90)approach_battle_offset(s.offset,0,1);
  if(s.frame==0){
   out.sound_request=true;
   constexpr float pi=3.1415927410125732421875f;
   const float angle=std::clamp(float(std::atan2(double(height_difference),double(float(std::sqrt(in.distance_squared))))/double(pi)*180.),-20.f,-5.f);
   const float launch_speed=character==5?32.5f:25.f;
   s.speed=legacy_trig(angle,false)*launch_speed;air.vertical=legacy_trig(angle,true)*launch_speed;
   air.pitch=std::min(0.f,float(std::atan2(double(air.vertical),double(s.speed))/double(pi)*180.+10.));air.pivot=70;
  }
  if(character!=2&&in.contact){
   air.pitch=0;air.vertical=10;s.speed=-7;air.gravity=.35f;
   action.next_state=334;action.clear_contact=true;out.reset_contact_capacity=true;return out;
  }
  if(s.frame>22)out.disable_contact=true;
  if(s.frame>40){action.next_phase=2;s.speed=10;return out;}
 }
 if(s.phase==2||(s.phase==1&&s.frame>22)){
  if(s.phase==2){if(air.pitch>0)air.pitch=std::max(0.f,air.pitch-5);if(air.pitch<0)air.pitch=std::min(0.f,air.pitch+5);}
  if(air.gravity==0)air.gravity=.5f;
  air.vertical-=air.gravity;s.speed=std::max(0.f,s.speed);
 }
 return out;
}
}
