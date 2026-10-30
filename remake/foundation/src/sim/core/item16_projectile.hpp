#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace daybreak {
// Original 006095c0: Akane weapon0's complete DAT registration switch.
// The script keeps target steering and shrinking tails alive after contacts.
inline bool item16_projectile_registration(unsigned item,unsigned registration){
 return item==16&&registration<=90&&registration%10==0;
}
template<class Host> bool tick_item16_projectile(KeiichiNormalProjectile& s,
 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item16_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item16 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto shrink=[&](){s.capacity.fill(0);for(auto& axis:s.scale)axis-=.1f;};
 auto pitch_steer=[&](float step){
  if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=step;
  if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
 };
 if(registration<=80&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration<=30){
  if(age==0){
   const int target=host.target_state(s);
   if((target>117&&target<122)||target==221)s.pitch=host.target_elevation(s);
   s.scratch_e8=0;
   if(registration==10||registration==30)s.scratch_ec=0;
   s.speed=registration==0?35.f:registration==10?45.f:registration==20?50.f:70.f;
   s.capacity.fill(1);
   if(registration>=20)s.scale.fill(1.5f);
  }
  const int terminal=registration==0?30:registration==20?25:60;
  if(host.stage_collision(s)==1||age>terminal){
   shrink();
   if(s.scale[registration==0||registration==20?2:0]<=0.f)return finish();
  }
  const bool decelerating=registration==10||registration==30;
  if(decelerating)s.scratch_ec=std::uint32_t(std::min(30,projectile_signed(s.scratch_ec)+1));
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   const float step=decelerating?float(projectile_signed(s.scratch_ec))*.033f:.25f;
   approach_battle_offset(s.offset,0.f,step);
   pitch_steer(decelerating?.5f:.1f);
  }
  if(decelerating){
   s.speed-=registration==10?.5f:1.f;
   s.speed=std::max(s.speed,registration==10?20.f:35.f);
  }
 }else if(registration<=70){
  const bool fast=registration>=60;
  if(age==0){
   s.speed=fast?40.f:20.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   s.rotation[1]=registration==40||registration==60?45.f:-45.f;
  }
  if(fast)s.speed=std::max(30.f,s.speed-1.f);
  if(s.scratch_ec==0&&age<20){
   approach_battle_offset(s.offset,0.f,fast?3.f:2.f);
   if(std::abs(s.offset)<1.f)s.scratch_ec=1;
  }
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,fast?.4f:.3f);
   pitch_steer(.3f);
  }
  if(host.stage_collision(s)==1||age>90){
   shrink();if(s.scale[0]<=0.f)return finish();
  }
 }else if(registration==80){
  if(age==0){
   s.rotation[1]=float(host.random_word()%360u);
   s.speed=100.f;s.capacity.fill(1);s.scratch_e8=0;s.scale={2.f,1.f,4.f};
  }
  s.speed-=3.f;
  if(host.stage_collision(s)==1||age>5){
   if(age>10)s.capacity.fill(0);
   s.scale[0]-=.2f;s.scale[1]-=.1f;s.scale[2]-=.4f;
   if(s.scale[0]<=0.f)return finish();
  }
 }else{
  if(age==0)s.speed=0;
  if(age>15)return finish();
  s.scratch_ec=std::uint32_t(std::min(30,projectile_signed(s.scratch_ec)+1));
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,float(projectile_signed(s.scratch_ec))*.033f);
   pitch_steer(.5f);
  }
  s.speed=std::max(20.f,s.speed-1.f);
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
