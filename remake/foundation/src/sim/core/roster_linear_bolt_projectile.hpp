#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// Original handlers 605d60, 607b50 and 62f180. Weapon DAT chooses the
// registration and mesh; these constants and event order come from the EXE.
struct RosterLinearBoltRule {
 float initial_speed, acceleration, speed_cap, initial_scale, trail_length;
 unsigned expiry_age, trail_count, impact_sound;
 bool allow_contact_one, aim_on_birth, scratch_counter;
};
inline bool roster_linear_bolt_rule(unsigned item,unsigned registration,RosterLinearBoltRule& out){
 if(item==13&&registration==90){
  out={40.f,.5f,70.f,0.f,10.f,240,20,160,false,false,false};return true;
 }
 if(item==13&&registration==160){
  out={40.f,0.f,0.f,0.f,0.f,180,0,160,false,true,false};return true;
 }
 if(item==14&&registration==10){
  out={60.f,0.f,0.f,0.f,0.f,120,0,0,true,false,false};return true;
 }
 if(item==14&&registration==20){
  out={85.f,0.f,0.f,0.f,10.f,120,20,0,true,false,false};return true;
 }
 if(item==43&&registration==100){
  out={120.f,0.f,0.f,4.f,60.f,240,60,201,false,false,true};return true;
 }
 return false;
}
inline bool roster_linear_bolt_registration(unsigned item,unsigned registration){
 RosterLinearBoltRule ignored{};return roster_linear_bolt_rule(item,registration,ignored);
}
template<class Host> bool tick_roster_linear_bolt_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 RosterLinearBoltRule rule{};
 if(!roster_linear_bolt_rule(unsigned(s.item),registration,rule))
  throw std::invalid_argument("Unsupported linear-bolt projectile registration");
 if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
 const int age=projectile_signed(s.frame);
 if(age==0){
  if(rule.aim_on_birth){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
  }
  if(rule.initial_scale>0.f)s.scale.fill(rule.initial_scale);
  if(rule.trail_count)host.trail(s,0,rule.trail_length,rule.trail_count,1,0);
  s.speed=rule.initial_speed;s.capacity.fill(1);
  if(rule.scratch_counter){s.scratch_e8=0;s.scratch_ec=40;}
 }
 if(rule.acceleration!=0.f){
  s.speed+=rule.acceleration;
  if(rule.speed_cap<s.speed)s.speed=rule.speed_cap;
 }
 if(rule.scratch_counter){
  ++s.scratch_ec;
  if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
 }
 const auto contact=projectile_contacts(s);
 const bool blocked=contact!=0&&(!rule.allow_contact_one||contact!=1);
 if(age>int(rule.expiry_age)||blocked||host.stage_collision(s)==1){
  if(rule.impact_sound&&(contact&0x80)){
   host.child(s,14,0,0,false);host.sound(s,rule.impact_sound);
  }
  s.released=true;return false;
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
