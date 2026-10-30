#pragma once
#include "keiichi_normal_projectile.hpp"
#include <stdexcept>

namespace daybreak {
// Item 20, original 00611260. Registration 0 retains the recovered motion
// handler; 70 and 90 retain the shared timed-scale handler. These are the
// remaining nine registrations from the same twelve-slot weapon DAT.
inline bool item20_projectile_registration(unsigned item,unsigned registration){
 return item==20&&registration<=110&&registration%10==0&&
        registration!=0&&registration!=70&&registration!=90;
}
template<class Host> bool tick_item20_projectile(KeiichiNormalProjectile& s,
                                                 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item20_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item20 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 if(registration==10){
  if(age==0){
   s.scale={2.5f,2.f,2.f};s.speed=.01f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
  }
  if(host.owner_phase(s)==3)s.scratch_ec=1;
  const auto state=host.owner_state(s);
  if(state!=400&&state!=402){host.child(s,11,0,0,false);return finish();}
  if(projectile_contacts(s)!=0&&projectile_signed(++s.scratch_f0)>10){
   s.scratch_f0=0;s.capacity.fill(1);s.contacts.fill(0);
  }
  if(s.scratch_ec==1){
   s.speed=.01f;s.capacity.fill(0);
   s.scale[1]-=.1f;s.scale[2]-=.1f;
   if(s.scale[2]<=0.f)return finish();
  }
  return advance();
 }
 if(registration==20||registration==30){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s,1);
  if(age==0){s.speed=50.f;s.capacity.fill(1);s.scratch_e8=0;}
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(age>10||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.child(s,registration==20?4:5,0,0,false);return finish();
  }
  return advance();
 }
 if(registration==40||registration==50||registration==60){
  if(age==0){
   s.speed=registration==60?.01f:0.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=0;
   s.scale.fill(registration==40?2.f:registration==50?3.f:4.f);
  }
  if(age>=0)host.visual_child(s,8);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(age>(registration==40?60:registration==50?120:0))s.scratch_ec=1;
  if(s.scratch_ec==1){
   s.capacity.fill(0);
   const float step=registration==60?.2f:.1f;
   for(auto& axis:s.scale)axis-=step;
   if(s.scale[2]<=0.f)return finish();
  }
  return advance();
 }
 if(registration==80){
  if(age==0){
   s.speed=20.f;
   s.offset=float(host.random_word()%360u);
   s.pitch=float(host.random_word()%360u);
   s.scratch_e8=0;s.capacity.fill(0);
  }
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>15)
   return finish();
  return advance();
 }
 if(age==0){s.speed=.01f;s.capacity.fill(1);host.color(s,0,255,255,255);}
 if(age>0)return finish();
 return advance();
}
} // namespace daybreak
