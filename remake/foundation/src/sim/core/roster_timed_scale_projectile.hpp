#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// Three source handlers (605750, 611260, 61d920) use age-controlled
// lifetime and scale. Registration-specific constants come from those cases;
// DAT selects the registration and its model/contact frames.
enum class RosterTimedScaleMode { early_shrink, stationary_hold, signal_fade, late_shrink };
struct RosterTimedScaleRule {
 RosterTimedScaleMode mode;
 float speed;
 std::array<float,3> scale;
 std::array<float,3> scale_step;
 unsigned terminal_age;
 bool seed_capacity;
 bool seed_scale=true;
};
inline bool roster_timed_scale_rule(unsigned item,unsigned registration,RosterTimedScaleRule& out){
 using M=RosterTimedScaleMode;
 if(item==12&&(registration==10||registration==20||registration==30||registration==50)){
  const bool small=registration==10;
  out={M::early_shrink,1.f,{small?2.f:20.f,small?2.f:20.f,small?2.f:20.f},
       {small?.4f:3.f,small?.4f:3.f,small?.4f:3.f},4,true};
  return true;
 }
 if(item==20&&registration==70){
  out={M::stationary_hold,0.f,{.5f,.5f,.5f},{0,0,0},20,true};return true;
 }
 if(item==20&&registration==90){
  out={M::signal_fade,.01f,{1.f,.5f,.5f},{0.f,.1f,.1f},0,false};return true;
 }
 if(item==31&&(registration==10||registration==20||registration==40||registration==50)){
  out={M::late_shrink,42.5f,{2.f,2.f,2.f},{.1f,.1f,.1f},90,true,
       registration!=20};return true;
 }
 return false;
}
inline bool roster_timed_scale_projectile_registration(unsigned item,unsigned registration){
 RosterTimedScaleRule ignored{};return roster_timed_scale_rule(item,registration,ignored);
}
template<class Host> bool tick_roster_timed_scale_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 RosterTimedScaleRule rule{};
 if(!roster_timed_scale_rule(unsigned(s.item),registration,rule))
  throw std::invalid_argument("Unsupported timed-scale projectile registration");
 const int age=projectile_signed(s.frame);
 const auto finish=[&](){s.released=true;return false;};
 if(age==0){
  s.speed=rule.speed;if(rule.seed_scale)s.scale=rule.scale;
  if(rule.seed_capacity)s.capacity.fill(1);
  if(rule.mode==RosterTimedScaleMode::early_shrink)s.scratch_e8=0;
  if(rule.mode==RosterTimedScaleMode::stationary_hold)s.velocity[1]=0;
 }
 switch(rule.mode){
 case RosterTimedScaleMode::early_shrink:
  if(age==int(rule.terminal_age)){s.speed=0;s.capacity.fill(0);return finish();}
  for(unsigned axis=0;axis<3;++axis)s.scale[axis]-=rule.scale_step[axis];
  if(s.scale[2]<=0.f)return finish();
  break;
 case RosterTimedScaleMode::stationary_hold:
  if(age>int(rule.terminal_age))return finish();
  break;
 case RosterTimedScaleMode::signal_fade:
  if(age>0)s.scratch_ec=1;
  if(s.scratch_ec==1){
   s.speed=.01f;s.capacity.fill(0);
   for(unsigned axis=0;axis<3;++axis)s.scale[axis]-=rule.scale_step[axis];
   if(s.scale[2]<=0.f)return finish();
  }
  break;
 case RosterTimedScaleMode::late_shrink:
  s.speed-=3.f;if(s.speed<3.f)s.speed=3.f;
  if(age>int(rule.terminal_age)){
   s.capacity.fill(0);
   // Original writes Z, Y, X in that order; retain that order for rounding.
   for(int axis=2;axis>=0;--axis)s.scale[axis]-=rule.scale_step[axis];
   if(s.scale[2]<=0.f)return finish();
  }
  break;
 }
 ++s.frame;host.advance_frame(s);return true;
}
}
