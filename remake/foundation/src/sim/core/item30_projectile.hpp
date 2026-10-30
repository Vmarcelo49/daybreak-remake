#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original 0061c410: the complete item-30 DAT registration switch. The owner
// actor is deliberately distinct from the aimed-at actor: 20..50 orbit the
// owner, and 20/30 release immediately only when that owner's HP is depleted.
inline bool item30_projectile_registration(unsigned item,unsigned registration){
 return item==30&&registration<=110&&registration%10==0;
}
template<class Host> bool tick_item30_projectile(KeiichiNormalProjectile& s,
                                                 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item30_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item30 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 auto fade=[&](){for(auto& axis:s.scale)axis-=.1f;return s.scale[0]<=0.f;};
 if(registration==0||registration==10){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s,3);
  if(age==0){
   s.speed=35.5f;s.rotation[1]=260.f;s.rotation[2]=10.f;
   s.capacity.fill(3);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f)s.pitch=host.target_elevation(s);
    if(s.pitch-host.target_elevation(s)>-10.f)s.pitch=host.target_elevation(s);
   }
  }
  if(registration==10&&age%2==0)host.visual_child(s,10);
  if(projectile_contacts(s)!=0&&
     projectile_signed(++s.scratch_f0)>4){s.scratch_f0=0;s.contacts.fill(0);}
  s.scratch_ec=std::uint32_t(std::min(75,projectile_signed(++s.scratch_ec)));
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.2f);
   if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=.2f;
   if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=.2f;
  }
  const auto contact=projectile_contacts(s);
  if(age>240||(contact!=0&&contact!=1))return finish();
  if(host.stage_collision(s)==1){host.child(s,registration==0?8:9,0,0,false);return finish();}
  return advance();
 }
 if(registration>=20&&registration<=50){
  if(age==0){s.speed=0.f;s.capacity.fill(1);s.scratch_e8=s.scratch_f0=0;}
  if(projectile_contacts(s)!=0&&projectile_signed(++s.scratch_f0)>30){
   s.scratch_f0=0;s.contacts.fill(0);s.capacity.fill(1);
  }
  if(registration>=40&&age%4==1)host.visual_child(s,11);
  s.scratch_e8=std::uint32_t(std::min(150,projectile_signed(s.scratch_e8)+5));
  const bool short_lived=registration<=30;
  const bool owner_dead=host.owner_health(s)<1;
  if(age>(short_lived?180:300)||(short_lived&&owner_dead)){
   if(short_lived)s.capacity.fill(0);else s.contacts.fill(0);
   if(fade()||owner_dead)return finish();
  }
  const auto owner=host.owner_position(s);
  const float angle=float(age*9+(registration==30||registration==50?180:0));
  const float radius=float(projectile_signed(s.scratch_e8));
  s.position[1]=owner[1]+70.f;
  s.position[0]=owner[0]+radius*legacy_trig(angle,false);
  s.position[2]=owner[2]+radius*legacy_trig(angle,true);
  return advance();
 }
 if(registration==60){
  if(age==0){s.speed=40.f;s.rotation[2]=float(host.random_word()%20u)-10.f;}
  if(projectile_contacts(s)!=0&&projectile_signed(++s.scratch_f0)>4){
   s.scratch_f0=0;s.contacts.fill(0);
  }
  if(age%4==1)host.visual_child(s,11);
  s.speed-=5.f;
  if(s.speed<1.f){s.speed=1.f;s.capacity.fill(1);}
  if(age>240){s.contacts.fill(0);if(fade()||host.owner_health(s)<1)return finish();}
  return advance();
 }
 if(registration==70){
  if(age==0){
   s.speed=5.f;s.capacity.fill(10);s.scratch_e8=s.scratch_ec=0;
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f)s.pitch=host.target_elevation(s);
    if(s.pitch-host.target_elevation(s)>-10.f)s.pitch=host.target_elevation(s);
   }
  }
  if(s.scale[2]<2.f)for(auto& axis:s.scale)axis+=.1f;
  if(projectile_contacts(s)!=0&&projectile_signed(++s.scratch_e8)>5){
   s.scratch_e8=0;s.contacts.fill(0);
  }
  if(age>90)return finish();
  return advance();
 }
 if(registration==80||registration==90){
  if(age==0){
   s.speed=.1f;s.rotation[1]=260.f;s.rotation[2]=10.f;
   s.capacity.fill(registration==80?3:5);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
  }
  if(registration==90&&age%2==0)host.visual_child(s,10);
  if(projectile_contacts(s)!=0&&projectile_signed(++s.scratch_f0)>4){
   s.scratch_f0=0;s.contacts.fill(0);
  }
  const auto contact=projectile_contacts(s);
  if(age>(registration==80?90:180)||(contact!=0&&contact!=1)){
   s.capacity.fill(0);if(fade())return finish();
  }
  return advance();
 }
 if(age==0){
  if(registration==110)s.rotation[0]=float(host.random_word()%360u);
  s.rotation[2]=float(host.random_word()%20u)-10.f;
  s.rotation[1]=registration==100?260.f:0.f;
 }
 if(age>13)return finish();
 return advance();
}
} // namespace daybreak
