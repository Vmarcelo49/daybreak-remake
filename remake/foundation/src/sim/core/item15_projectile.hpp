#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original 006085e0, supplied item15 DAT registrations 10..110.
// Registration zero remains in roster_simple_projectile.hpp.
inline bool item15_projectile_registration(unsigned item,unsigned registration){
 return item==15&&registration>=10&&registration<=110&&registration%10==0;
}
template<class Host> bool tick_item15_projectile(KeiichiNormalProjectile& s,
                                                 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item15_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item15 registration");
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
 const auto track_pitch=[&](float step){
  if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=step;
  if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
 };
 if((registration==10||registration==40||registration==50||
     registration==70||registration==90)&&(projectile_contacts(s)&0x100))
  reflect_normal_projectile(s);
 if(registration==10){
  if(age==0){s.scale={1.f,.6f,.6f};s.speed=40.f;s.capacity.fill(1);}
  if((projectile_contacts(s)&2)||host.stage_collision(s)==1){
   host.visual_child(s,3);return finish();
  }
  s.speed-=.5f;
  if(age>60)return finish();
  return advance();
 }
 if(registration==20){s.speed=0;if(age>5)return finish();return advance();}
 if(registration==30){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);}
  if(age>4){
   const int faded=projectile_signed(s.scratch_e8)-50;
   s.scratch_e8=std::uint32_t(faded);
   if(faded<0){s.scratch_e8=0;return finish();}
  }
  host.alpha(s,s.scratch_e8&255u);
  return advance();
 }
 if(registration==40||registration==50||registration==70){
  const bool heavy=registration==50, aura=registration==70;
  if(age==0){
   target_birth();
   if(!heavy)approach_battle_offset(s.offset,0.f,5.f);
   s.scale.fill(aura?.5f:1.f);
   s.speed=aura?100.f:heavy?75.f:70.f;s.capacity.fill(1);
   host.visual_child(s,6);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=s.scratch_f4=0;
   if(aura)s.scratch_f8=0;
  }
  if(aura&&projectile_signed(s.scratch_f0)%5==0)host.visual_child(s,8);
  ++s.scratch_ec;++s.scratch_f0;
  if(projectile_signed(s.scratch_ec)>60)s.scratch_ec=60;
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   const float step=heavy?.25f:.01f;
   approach_battle_offset(s.offset,0.f,step);
   track_pitch(step);
  }
  if(projectile_signed(s.scratch_f0)>480||host.stage_collision(s)==1){
   s.scratch_f4=1;s.capacity.fill(0);s.speed=0;
  }
  if(s.scratch_f4==1){
   if(!aura)s.speed=0;
   for(auto& axis:s.scale)axis-=aura?.05f:.1f;
   if(s.scale[0]<=0.f)return finish();
  }
  if(heavy&&age==60){s.frame=40;return true;}
  if(aura&&age==60){s.frame=30;return true;}
  return advance();
 }
 if(registration==60){if(age>5)return finish();return advance();}
 if(registration==80){
  if(age==0)s.scale.fill(.05f);
  s.speed=0;
  const float growth=legacy_trig(float(age*3),false)*.025f;
  for(auto& axis:s.scale)axis+=growth;
  if(age>28)return finish();
  return advance();
 }
 if(registration==90){
  if(age==0){
   s.scale.fill(1.f);s.speed=55.f;s.capacity.fill(1);host.visual_child(s,6);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=s.scratch_f4=0;
   normal_projectile_direct_velocity(s);
  }
  s.speed-=1.f;
  if(s.speed<20.f)s.speed=20.f;
  s.velocity[1]-=.5f;
  if(age%2==0)host.visual_child(s,10);
  if(projectile_signed(s.scratch_f0)>400)return finish();
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.sound(s,0x4a);host.visual_child(s,11);return finish();
  }
  return advance();
 }
 if(registration==100){
  if(age==0){
   s.scale.fill(float(host.random_word()%10u)*.1f+1.f);
   s.rotation[1]=float(host.random_word()%360u);
  }
  if(age>29)return finish();
  return advance();
 }
 if(registration==110){
  if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);s.scale.fill(1.75f);}
  if(age>51)return finish();
  return advance();
 }
 throw std::logic_error("Unreachable item15 registration");
}
} // namespace daybreak
