#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <stdexcept>

namespace daybreak {
// Original 00607b50 registrations 30..110. The DAT's first three routes
// (0,10,20) retain their already recovered simple/linear-bolt handlers.
inline bool item14_projectile_registration(unsigned item,unsigned registration){
 return item==14&&registration>=30&&registration<=110&&registration%10==0;
}
template<class Host> bool tick_item14_projectile(KeiichiNormalProjectile& s,
                                                 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item14_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item14 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 if(registration==30||registration==40){
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   s.speed=60.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   s.scale.fill(2.f);
  }
  if(s.scratch_ec==0){
   s.speed-=registration==30?1.75f:1.5f;
   if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
   approach_battle_offset(s.offset,0.f,registration==30?.01f:.5f);
   if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=.25f;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=.25f;
   if(s.speed<=0.f||host.stage_collision(s)==1){
    s.scratch_ec=1;s.speed=0.f;host.retarget_owner(s);
    s.capacity.fill(1);s.contacts.fill(0);
    return advance(); // Original switch break skips the same-tick restart.
   }
  }
  if(projectile_signed(s.scratch_ec)>0){
   ++s.scratch_ec;
   s.speed+=registration==30?1.5f:.5f;
   const float limit=registration==30?45.f:35.f;
   if(s.speed>limit)s.speed=limit;
   approach_battle_offset(s.offset,0.f,180.f);
   s.pitch=host.target_elevation(s);
   if(host.target_distance_squared(s)<10000.f)return finish();
  }
  if(age>180)return finish();
  return advance();
 }
 if(registration==50){
  if(age==0)s.speed=0.f;
  for(auto& axis:s.scale)axis-=.1f;
  if(s.scale[0]<0.f)return finish();
  return advance();
 }
 if(registration==60){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){host.trail(s,2,20.f,25,1,0);s.speed=60.f;s.capacity.fill(1);}
  if(age>180)return finish();
  if(host.stage_collision(s)==1){host.child(s,7,0,0,false);return finish();}
  return advance();
 }
 if(registration==70){
  if(age==0){s.speed=0.f;s.velocity[1]=0.f;s.capacity.fill(0);s.scratch_e8=0;}
  if(age>26&&projectile_signed(s.scratch_e8)<3){
   ++s.scratch_e8;s.frame=18;return true;
  }
  if(age==52)return finish();
  return advance();
 }
 // Registrations 80..110 have no explicit case in 00607b50. The original
 // still advances the script clock and animation; a generic 240-tick expiry
 // would introduce behavior absent from this handler.
 return advance();
}
} // namespace daybreak
