#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// Original 00616810, supplied item23 DAT registrations other than the
// immediate-release 0/10 already handled by the shared families.
inline bool item23_projectile_registration(unsigned item,unsigned registration){
 return item==23&&registration>=20&&registration<=60&&registration%10==0;
}
template<class Host> bool tick_item23_projectile(KeiichiNormalProjectile& s,
                                                 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item23_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item23 registration");
 const int age=projectile_signed(s.frame);
 const auto finish=[&](){s.released=true;return false;};
 if(registration==20||registration==30){
  if(age>int(registration==20?12:51))return finish();
 }else if(registration==40){
  if(age==0){s.speed=15.f;s.capacity.fill(1);s.scratch_e8=0;}
  if(age==1){normal_projectile_direct_velocity(s);s.velocity[1]=15.f;}
  s.velocity[1]-=.5f;
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0){
   host.child(s,5,0,0,false);host.sound(s,0x69);return finish();
  }
  if(age>1800)return finish();
 }else if(registration==50){
  if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}
  if(age>51)return finish();
 }else if(registration==60){
  if(age==0){s.speed=0;s.capacity.fill(1);s.scratch_e8=0;s.scale={7.f,12.f,7.f};}
  if(age==30){s.speed=0;s.capacity.fill(0);return finish();}
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
