#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <stdexcept>

namespace daybreak {

// Source handlers 00605d60 and 0062f180 share the long-lived trail shot.
// Registration 100 in item 13 steers and creates child registration 110 at
// termination. Both handlers' registration 110 descendants use the same
// short, contact-independent lifetime rule.
struct RosterTrailSteeringRule {
 float speed,trail_length;
 unsigned trail_count,impact_sound;
 bool steering,short_child;
};
inline bool roster_trail_steering_rule(unsigned item,unsigned registration,
                                      RosterTrailSteeringRule& out){
 if(item==13&&registration==10){out={55.f,10.f,20,160,false,false};return true;}
 if(item==13&&registration==170){out={60.f,10.f,20,160,false,false};return true;}
 if(item==43&&registration==10){out={75.f,10.f,20,201,false,false};return true;}
 if(item==13&&registration==100){out={42.5f,30.f,10,0,true,false};return true;}
 if((item==13||item==43)&&registration==110){out={0,0,0,0,false,true};return true;}
 return false;
}
inline bool roster_trail_steering_registration(unsigned item,unsigned registration){
 RosterTrailSteeringRule ignored{};return roster_trail_steering_rule(item,registration,ignored);
}

template<class Host> bool tick_roster_trail_steering_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 RosterTrailSteeringRule rule{};
 if(!roster_trail_steering_rule(unsigned(s.item),registration,rule))
  throw std::invalid_argument("Unsupported trail-steering projectile registration");
 const int age=projectile_signed(s.frame);
 if(rule.short_child){
  if(age==0)s.capacity.fill(1);
  if(age>51){s.released=true;return false;}
  ++s.frame;host.advance_frame(s);return true;
 }
 if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
 if(age==0){
  if(!rule.steering){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   host.trail(s,0,rule.trail_length,rule.trail_count,1,0);
   s.speed=rule.speed;s.capacity.fill(1);
  }else{
   s.scale.fill(4.f);s.scratch_e8=0;s.scratch_ec=40;
   s.speed=rule.speed;s.capacity.fill(1);
   host.trail(s,0,rule.trail_length,rule.trail_count,1,0);
  }
 }
 if(rule.steering){
  s.speed+=.5f;if(s.speed>70.f)s.speed=70.f;
  ++s.scratch_ec;
  if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float step=float(projectile_signed(s.scratch_ec))*.003f;
   approach_battle_offset(s.offset,0.f,step);
   const float target=host.target_elevation(s);
   if(s.pitch-target>3.f)s.pitch-=step;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
  }
 }else if(projectile_contacts(s)&0x80){
  host.child(s,14,0,0,false);host.sound(s,rule.impact_sound);
 }
 if(age>240||projectile_contacts(s)!=0||host.stage_collision(s)==1){
  if(rule.steering)host.child(s,11,0,0,false);
  s.released=true;return false;
 }
 ++s.frame;host.advance_frame(s);return true;
}

} // namespace daybreak
