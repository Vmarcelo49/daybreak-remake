#pragma once
#include "keiichi_air_melee.hpp"
#include "character_dispatch.hpp"
namespace daybreak {
struct ChasingAirMeleePolicy {
 float minimum_vertical=-6,maximum_vertical=3,initial_speed=11,minimum_angle=-25,maximum_angle=30,turn_step=4;
 float phase1_turn_step=2,phase2_turn_step=2,pitch_bias=20,initial_pitch_bias=20,first_target_bias=10;
 double initial_distance_squared=490000,attack_distance_squared=30000;
 int initial_strength=150,minimum_strength=110,strength_decay=3;
 int gravity_after=5,landing_after=10,approach_after=12,approach_timeout=25,phase2_turn_until=0,phase2_turn_strength_condition=0;
 int effect=62,voice_frame=0,strike_begin=(-2147483647-1),strike_end=7;
 int initial_contact_capacity=1;
 int pitch_recovery_after=25;
 bool skip_attack_frames=false,strike_enabled=false,phase1_moving_increment=false,clear_contact_on_hit=false;
 bool decay_before_velocity=false;
};
inline ChasingAirMeleePolicy chasing_air_melee_policy(unsigned character,unsigned weapon){
 character_action_dispatch(character,weapon);
 ChasingAirMeleePolicy p;
 if(character==1){if(weapon==1){p.initial_speed=12;p.initial_strength=170;p.turn_step=5;}return p;}
 if(character!=0)throw std::invalid_argument("Chasing air melee policy not recovered");
 p.strike_enabled=true;
 p.minimum_vertical=-3;p.initial_speed=12.5f;p.minimum_angle=-30;p.maximum_angle=50;p.turn_step=3;
 p.initial_distance_squared=1000000;p.attack_distance_squared=weapon==2?490000:40000;
 p.initial_strength=weapon==2?140:230;p.minimum_strength=weapon==2?140:125;p.strength_decay=4;p.approach_after=10;
 p.effect=weapon==1?63:62;
 if(weapon==2){p.gravity_after=50;p.landing_after=55;p.voice_frame=32;p.strike_begin=32;p.strike_end=39;p.skip_attack_frames=true;}
 return p;
}
struct ChasingAirMeleeEffects : KeiichiAttack300Effects {bool activate=false;int frame_override=-1;};
// Mion/Rena state320. +ec is the air tick count, carried in air.ticks;
// frame_override must be applied to BOTH clocks before the normal tail tick.
inline ChasingAirMeleeEffects advance_chasing_air_melee(const ChasingAirMeleePolicy& p,KeiichiAirMelee& air,KeiichiAttack300& s,const KeiichiAttack300Input& in,float height){
 ChasingAirMeleeEffects out;
 if(in.animation_complete){out.next_state=43;air.pitch=0;return out;}
 if(air.gravity==0)air.gravity=.5f;
 if(s.phase==2&&s.frame>p.gravity_after)air.vertical-=air.gravity;
 if(s.phase==2&&s.frame>p.landing_after&&in.grounded){out.next_state=329;s.speed=air.vertical=air.pitch=0;return out;}
 if(p.clear_contact_on_hit&&in.contact)out.clear_contact=true;
 auto degrees=[](float y,float x){const double radians=std::atan2(double(y),double(x));volatile float turns=float(static_cast<long double>(radians)/3.1415927410125732421875L);volatile float result=turns*180.f;return float(result);};
 auto angle=[&](){return degrees(air.vertical,s.speed);};
 const bool first=s.phase==0&&s.frame==0;
 if(first){
  s.movement_angle=0;s.moving=s.contact_seen=0;air.ticks=0;air.strength=0;
  out.activate=out.initialize=out.clear_contact=true;out.contact_capacity=p.initial_contact_capacity;air.vertical=std::clamp(air.vertical,p.minimum_vertical,p.maximum_vertical);s.speed=p.initial_speed;
  if(in.distance_squared<p.initial_distance_squared){air.strength=p.initial_strength;approach_battle_offset(s.offset,0,180);}
  air.pitch=angle()+p.initial_pitch_bias;air.pivot=70;
 }
 ++air.ticks;
 if(s.phase<2&&air.strength>0){
  const float target_angle=degrees(height,float(std::sqrt(in.distance_squared)))+10.f;
  float current=first?target_angle+(p.first_target_bias-10.f):angle();
  if(current>target_angle)current=std::max(target_angle,current-5);
  if(current<target_angle)current=std::min(target_angle,current+5);
  current=std::clamp(current,p.minimum_angle,p.maximum_angle);
  if(p.decay_before_velocity)air.strength=std::max(p.minimum_strength,air.strength-p.strength_decay);
  const float magnitude=float(air.strength)*.1f;
  s.speed=legacy_trig(current,false)*magnitude;air.vertical=legacy_trig(current,true)*magnitude;
  air.pitch=angle()+p.pitch_bias;air.pivot=70;approach_battle_offset(s.offset,0,p.turn_step);
  if(!p.decay_before_velocity)air.strength=std::max(p.minimum_strength,air.strength-p.strength_decay);
 }
 if(s.phase==1){
  if(p.phase1_moving_increment)++s.moving;
  approach_battle_offset(s.offset,0,p.phase1_turn_step);
  if(s.frame>p.approach_after&&(double(float(in.distance_squared))+double(height)*height<p.attack_distance_squared||s.frame>p.approach_timeout||air.strength==0)){out.next_phase=2;return out;}
 }
 if(s.phase==2){
  if(s.frame<p.phase2_turn_until&&
     (p.phase2_turn_strength_condition==0||(p.phase2_turn_strength_condition==1&&air.strength>0)||
      (p.phase2_turn_strength_condition==2&&air.strength==1)))
   approach_battle_offset(s.offset,0,p.phase2_turn_step);
  if(p.skip_attack_frames&&s.frame==13){s.frame=22;out.frame_override=22;}
  if(p.skip_attack_frames&&s.frame<32)approach_battle_offset(s.offset,0,2);
  if(s.frame==p.voice_frame){
   out.effect=p.effect;out.voice=1;out.voice_argument=10;
   if(in.distance_squared<40000.&&std::abs(s.offset)<30)for(unsigned i=0;i<3;++i)if(in.voice_flags[i]==1){out.voice=i==0?0:i==1?15:5;out.voice_argument=12;break;}
  }
  if(s.frame>p.pitch_recovery_after){if(air.pitch>0)air.pitch=std::max(0.f,air.pitch-5);if(air.pitch<0)air.pitch=std::min(0.f,air.pitch+5);}
 }
 out.strike=p.strike_enabled&&s.phase==2&&s.frame>=p.strike_begin&&s.frame<=p.strike_end;return out;
}
}
