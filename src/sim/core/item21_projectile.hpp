#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original 00611e30 item 21 DAT registrations 20..110. Registrations 0/10
// share the fade implementation in roster_dynamic_fade_projectile.hpp.
inline bool item21_projectile_registration(unsigned item,unsigned registration){
 return item==21&&registration>=20&&registration<=110&&registration%10==0;
}
template<class Host> bool tick_item21_projectile(KeiichiNormalProjectile& s,
                                                 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item21_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item21 registration");
 const int age=projectile_signed(s.frame);
 const auto finish=[&](){s.released=true;return false;};
 const auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 const auto target_birth=[&](){
  const int state=host.target_state(s);
  if((state>117&&state<122)||state==221){
   const float target=host.target_elevation(s);
   if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
  }
 };
 const auto disable_far_steering=[&](){
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
 };
 const auto track_pitch=[&](float step){
  if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=step;
  if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
 };
 if((registration==20||registration==30||registration==60)&&
    (projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration==20||registration==30||registration==60){
  const unsigned direct_after=registration==20?40u:60u;
  const float steer_step=registration==20?.2f:.3f;
  if(age==0){
   target_birth();
   if(registration==30)host.trail(s,0,60.f,25,1,0);
   s.speed=registration==20?50.f:registration==30?75.f:65.f;
   s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   if(registration!=20)s.scale.fill(1.f);
  }
  disable_far_steering();
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,steer_step);
   track_pitch(steer_step);
  }
  if(age==int(direct_after)){
   s.scratch_e8=1;
   normal_projectile_direct_velocity(s);
  }
  if(age>int(direct_after))s.velocity[1]-=.15f;
  if(age>480||host.stage_collision(s)==1)return finish();
  return advance();
 }
 if(registration==40){
  if(age==0){s.speed=0;s.capacity.fill(0);s.scratch_e8=0;s.scratch_ec=255;s.scale.fill(.7f);}
  const int faded=projectile_signed(s.scratch_ec)-20;
  s.scratch_ec=std::uint32_t(faded);
  if(faded<0){s.scratch_ec=0;return finish();}
  host.alpha(s,s.scratch_ec&255u);
  if(age==20)return true;
  return advance();
 }
 if(registration==50||registration==100){
  if(age==0){host.visual_child(s,1);s.speed=registration==50?30.f:50.f;s.capacity.fill(1);}
  if(registration==100&&age>240){host.child(s,8,0.f,0.f,false);return finish();}
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.child(s,8,0.f,0.f,false);return finish();
  }
  if(age>int(registration==50?90:240))return finish();
  return advance();
 }
 if(registration==70){
  if(age==0){s.speed=40.f;s.capacity.fill(1);host.visual_child(s,4);s.scratch_e8=s.scratch_ec=0;}
  s.scratch_ec=std::min(s.scratch_ec+3u,100u);
  if(age%2==0)host.visual_child(s,7);
  disable_far_steering();
  if(s.scratch_e8==0&&age>0){
   const float step=float(projectile_signed(s.scratch_ec))*.005f;
   approach_battle_offset(s.offset,0.f,step);
   track_pitch(step);
  }
  if(age>480||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.child(s,3,0.f,0.f,false);host.sound(s,0x4a);return finish();
  }
  return advance();
 }
 if(registration==80){
  if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}
  if(age>51)return finish();
  return advance();
 }
 if(registration==90){if(age>5)return finish();return advance();}
 if(registration==110){if(age>29)return finish();return advance();}
 throw std::logic_error("Unreachable item21 registration");
}
} // namespace daybreak
