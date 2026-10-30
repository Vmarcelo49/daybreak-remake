#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {

// Original item handler 6183b0. DAT registrations are grouped by their
// motion, child spawning and expiry rules instead of separate weapon scripts.
inline bool item26_flight_registration(unsigned item,unsigned registration){
 return item==26&&(registration==40||registration==50||registration==60||
                   registration==70||registration==80||registration==90||
                   registration==100||registration==110||registration==120);
}

template<class Host> bool tick_item26_flight_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!item26_flight_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item26 flight registration");
 const int age=projectile_signed(s.frame);
 if((registration==60||registration==110)&&(projectile_contacts(s)&0x100))
  reflect_normal_projectile(s);
 if(registration==40||registration==50){
  const bool wide=registration==50;
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   approach_battle_offset(s.offset,0.f,10.f);
   s.speed=50.f;s.capacity.fill(1);s.scale.fill(3.f);
   if(wide)host.trail(s,0,50.f,25,1,0);
  }
  approach_battle_offset(s.offset,0.f,.2f);
  const float target=host.target_elevation(s);
  if(s.pitch-target>3.f)s.pitch-=.2f;
  if(s.pitch-target< -3.f)s.pitch+=.2f;
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.particle_offset(s,7,0,0,0);s.released=true;return false;
  }
  if(age>=15&&age<=(wide?20:18)){
   constexpr float narrow_yaw[]={9.f,3.f,-3.f,-9.f};
   constexpr float wide_yaw[]={12.f,8.f,3.f,-3.f,-8.f,-12.f};
   const float yaw=wide?wide_yaw[age-15]:narrow_yaw[age-15];
   host.child(s,11,yaw,0,true);
   if(age==15)host.particle_offset(s,7,0,0,0);
   if(age==(wide?20:18)){s.released=true;return false;}
  }
 }else if(registration==60){
  if(age==0){
   s.speed=35.f;s.capacity.fill(1);s.scratch_e8=s.scratch_f0=0;
   host.trail(s,0,10.f,20,1,0);
  }
  s.scratch_f0=std::min(s.scratch_f0+2u,100u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float step=float(projectile_signed(s.scratch_f0))*.005f;
   approach_battle_offset(s.offset,0.f,step);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=step;
   if(s.pitch-target< -1.f)s.pitch+=step;
  }
  if(age>240||host.stage_collision(s)==1){s.released=true;return false;}
 }else if(registration==70||registration==90){
  if(age==0){
   if(registration==70)s.scale.fill(.5f);
   else s.capacity.fill(1);
  }
  if(age>51){s.released=true;return false;}
 }else if(registration==80||registration==100){
  if(age==0){
   s.speed=45.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   s.scale.fill(2.f);
  }
  if(age==1)normal_projectile_direct_velocity(s);
  s.velocity[1]-=.5f;
  const bool expired=age>800;
  const bool contacted=!expired&&projectile_contacts(s)!=0;
  if(expired||contacted||host.stage_collision(s)==1){
   host.sound(s,registration==80?165:167);
   if(age<801)host.child(s,9,0,0,false);
   s.released=true;return false;
  }
 }else if(registration==110){
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   s.speed=40.f;s.capacity.fill(1);s.scale.fill(2.f);
  }
  approach_battle_offset(s.offset,0.f,.1f);
  const float target=host.target_elevation(s);
  if(s.pitch-target>3.f)s.pitch-=.1f;
  if(s.pitch-target< -3.f)s.pitch+=.1f;
  if(age>20){
   for(int i=0;i<5;++i){
    s.scratch_f0=host.random_word()%20u;
    s.scratch_ec=host.random_word()%20u;
    host.child(s,6,float(s.scratch_f0)-10.f,
                  float(s.scratch_ec)-10.f,true);
   }
   host.particle_offset(s,7,0,0,0);s.released=true;return false;
  }
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.particle_offset(s,7,0,0,0);s.released=true;return false;
  }
 }else if(registration==120){
  s.position=host.owner_position(s);
  s.pitch=0;
  s.rotation[0]+=1.f;
  if(age==0){s.scale[0]=s.scale[2]=0;s.scratch_f8=0;}
  if(s.scale[2]>=1.5f)s.scale[0]=s.scale[2]=1.5f;
  else{
   const float growth=legacy_trig(float(age*3),true)*.1f;
   s.scale[0]+=growth;s.scale[2]+=growth;
  }
  if(age%30==0){s.capacity.fill(1);s.contacts.fill(0);}
  if(host.owner_state(s)==370&&host.owner_animation_frame(s)==0)s.scratch_f8=1;
  if(age<301&&projectile_signed(s.scratch_f8)<1)
   s.scale[1]=legacy_trig(float(age*6),true)*.25f+.75f;
  else{
   s.capacity.fill(0);s.scale[1]-=.1f;
   if(s.scale[1]<0.f){s.released=true;return false;}
  }
 }
 ++s.frame;host.advance_frame(s);return true;
}

} // namespace daybreak
