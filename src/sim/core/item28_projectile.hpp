#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original 0061adb0. Registration 0 uses the shared simple-shot branch and
// registration 50 is an immediate release; the other DAT slots live here.
inline bool item28_projectile_registration(unsigned item,unsigned registration){
 return item==28&&((registration>=10&&registration<=40&&registration%10==0)||
                  (registration>=60&&registration<=110&&registration%10==0));
}
template<class Host> bool tick_item28_projectile(KeiichiNormalProjectile& s,
                                                  unsigned registration,Host& host){
 if(s.released)return false;
 if(!item28_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item28 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 if((registration==10||registration==20)&&(projectile_contacts(s)&0x100))
  reflect_normal_projectile(s,registration==10?3:1);
 if(registration==10||registration==20){
  if(age==0){
   s.scratch_e8=0;
   s.speed=registration==10?80.f:50.f;
   s.capacity.fill(registration==10?3:1);
   if(registration==10){s.scratch_ec=0;s.scale={1.f,3.f,1.f};}
  }
  if(registration==10&&(projectile_contacts(s)&1)){
   if(projectile_signed(s.scratch_ec)<10){s.speed=0; ++s.scratch_ec;return true;}
   s.scratch_ec=0;s.contacts.fill(0);
  }
  if(host.stage_collision(s)==1||age>(registration==10?10:30)){
   s.capacity.fill(0);
   if(registration==10){
    s.scale[0]-=.2f;s.scale[1]-=1.f;s.scale[2]-=.2f;
    if(s.scale[1]<=0.f)return finish();
   }else{
    for(auto& axis:s.scale)axis-=.1f;
    if(s.scale[2]<=0.f)return finish();
   }
  }
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,.25f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>3.f)s.pitch-=.1f;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=.1f;
  }
  return advance();
 }
 if(registration==30){
  if(age==0)s.speed=0;
  if(age>15)return finish();
  s.scratch_ec=std::min(30u,s.scratch_ec+1);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,float(projectile_signed(s.scratch_ec))*.033f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>3.f)s.pitch-=.5f;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=.5f;
  }
  s.speed-=1.f;if(s.speed<20.f)s.speed=20.f;
  return advance();
 }
 if(registration==40){
  if(age==0){s.scratch_e8=0;s.speed=50.f;s.scale={1.f,1.f,3.f};s.capacity.fill(1);}
  if(host.stage_collision(s)==1||age>5){
   s.capacity.fill(0);s.scale[0]-=.2f;s.scale[1]-=.2f;s.scale[2]-=.6f;
   if(s.scale[1]<=0.f)return finish();
  }
  return advance();
 }
 if(registration==60||registration==70){
  if(age==0){s.speed=20.f;s.capacity.fill(1);s.scratch_e8=0;}
  if(s.scratch_e8==0&&age<20)approach_battle_offset(s.offset,0.f,2.f);
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,.3f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>3.f)s.pitch-=.3f;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=.3f;
  }
  if(host.stage_collision(s)==1||age>120){
   s.capacity.fill(0);
   for(auto& axis:s.scale)axis-=.1f;
   if(s.scale[0]<=0.f)return finish();
  }
  return advance();
 }
 if(registration==80&&age>29)return finish();
 // 90/100/110 contain no case body in the original switch.
 return advance();
}
} // namespace daybreak
