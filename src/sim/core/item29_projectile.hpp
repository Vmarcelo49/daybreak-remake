#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original 0061b8e0: Natsumi weapon0's complete DAT registration switch.
inline bool item29_projectile_registration(unsigned item,unsigned registration){
 return item==29&&registration<=90&&registration%10==0;
}
template<class Host> bool tick_item29_projectile(KeiichiNormalProjectile& s,
 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item29_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item29 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto aim_on_birth=[&](){
  const int target=host.target_state(s);
  if((target>117&&target<122)||target==221)s.pitch=host.target_elevation(s);
 };
 if(registration<=40&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration==0||registration==20){
  const float step=registration==0?.1f:.05f;
  if(age==0){
   s.speed=registration==0?47.f:45.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   aim_on_birth();
  }
  s.scratch_ec=std::uint32_t(std::min(75,projectile_signed(s.scratch_ec)+1));
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,registration==0?.1f:.05f);
   if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=step;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
  }
  const auto contact=projectile_contacts(s);
  if(age>240||(contact!=0&&contact!=1)||host.stage_collision(s)==1)return finish();
 }else if(registration==10){
  if(age==0)return finish();
 }else if(registration<=40){
  if(age==0){
   aim_on_birth();host.trail(s,0,10.f,20,1,0);s.speed=55.f;s.capacity.fill(1);
  }
  if(age>240||projectile_contacts(s)!=0||host.stage_collision(s)==1)return finish();
 }else if(registration==50||registration==60){
  s.speed=0;s.velocity[1]=0;
  if(age==0)s.scratch_e8=255;
  if(age>0){
   const int alpha=projectile_signed(s.scratch_e8)-10;
   s.scratch_e8=std::uint32_t(std::max(0,alpha));
   if(alpha<0)return finish();
  }
  host.alpha(s,s.scratch_e8&255u);
 }else if(registration==70){
  if(age==0){s.speed=0;s.scratch_e8=255;}
  if(age>10)s.scratch_e8=std::uint32_t(std::max(0,projectile_signed(s.scratch_e8)-40));
  host.alpha(s,s.scratch_e8&255u);
  if(age>15)return finish();
 }else{
  if(age==0){s.speed=registration==80?7.f:5.f;s.scratch_e8=255;s.scratch_f8=0;}
  if(age==1)normal_projectile_direct_velocity(s);
  s.velocity[1]-=.4f;
  if(host.stage_collision(s)==1)s.scratch_f8=1;
  if(age>60||projectile_signed(s.scratch_f8)>0){
   s.capacity.fill(0);
   const int alpha=projectile_signed(s.scratch_e8)-13;
   s.scratch_e8=std::uint32_t(std::max(0,alpha));
   if(alpha<0)return finish();
   host.alpha(s,s.scratch_e8&255u);
  }
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
