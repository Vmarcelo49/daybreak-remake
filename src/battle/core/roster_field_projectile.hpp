#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace daybreak {
// Item 17 / registration 0: persistent field whose first contact advances the
// owner's three-stage rank. Recovered from DaybreakDX.exe VA 60a980 case 0.
template<class Host> bool tick_roster_field_projectile(KeiichiNormalProjectile& s,Host& host){
 if(s.released)return false;
 if(unsigned(s.item)!=17)throw std::invalid_argument("Unsupported field projectile item");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(projectile_contacts(s)&0x100){s.contacts.fill(0);s.capacity.fill(1);}
 if(age==0){
  host.target_refresh(s);
  s.speed=0;s.capacity.fill(0);s.contacts.fill(0);s.scratch_e8=0;
 }
 if(age==60)s.capacity.fill(1);
 if(projectile_contacts(s)!=0){
  ++s.scratch_e8;
  if(s.scratch_e8==1){
   s.scratch_ec=host.field_rank_increment(s);
   if(s.contacts[s.target]==0)host.target_refresh(s);
  }
  const unsigned rank=s.scratch_ec;
  if(rank==1||rank==2){
   const unsigned fade_after=rank==1?70u:90u;
   if(s.scratch_e8<fade_after)approach_battle_offset(s.offset,0.f,180.f);
   const unsigned cadence=rank==1?10u:30u;
   if(s.scratch_e8>10&&s.scratch_e8<=fade_after&&s.scratch_e8%cadence==0){
    host.sound(s,rank==1?72u:80u);
    auto child=s;child.position[1]+=70.f;
    host.child(child,rank==1?9u:10u,0.f,host.field_target_pitch(s),true);
   }
  }else if(rank==3){
   if(s.scratch_e8==1){
    s.scratch_f0=std::uint32_t(std::lrint(host.field_target_pitch(s)));
    approach_battle_offset(s.offset,0.f,180.f);
   }
   if(s.scratch_e8%15u==0&&s.scratch_e8<=90u){
    if(s.scratch_e8==15u)host.sound(s,82u);
    auto child=s;child.position[1]+=70.f;
    host.child(child,11u,0.f,float(projectile_signed(s.scratch_f0)),true);
   }
  }
  if((rank==1&&s.scratch_e8>70u)||(rank>=2&&s.scratch_e8>90u)){
   if(s.scale[0]<=0.f)return finish();
   for(auto& axis:s.scale)axis-=.05f;
  }
 }
 if(age>7200)return finish();
 ++s.frame;host.advance_frame(s);return true;
}

// The three active field emissions use DAT registrations 90, 100 and 110.
// Source: VA 60a980 cases 5a, 64 and 6e. Their contact/expiry rules differ.
template<class Host> bool tick_roster_field_child_projectile(KeiichiNormalProjectile& s,
 unsigned registration,Host& host){
 if(s.released)return false;
 if(unsigned(s.item)!=17||(registration!=90&&registration!=100&&registration!=110))
  throw std::invalid_argument("Unsupported field child projectile registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(registration!=110&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration==110){
  if(age==0){
   s.scale.fill(1.5f);s.speed=.01f;s.scratch_e8=s.scratch_ec=0;
   s.capacity.fill(1);
  }
  ++s.scratch_e8;s.scratch_ec+=2u;
  if(age==41)return finish();
 }else{
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=50.f;s.capacity.fill(1);
   if(registration==100)s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
  }
  if(registration==90){
   if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0){
    approach_battle_offset(s.offset,0.f,.01f);
    const float target=host.target_elevation(s);
    if(s.pitch-target>3.f)s.pitch-=.01f;
    if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=.01f;
   }
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>90)return finish();
  }else{
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
    if((projectile_contacts(s)&2)!=0||host.stage_collision(s)==1)return finish();
   }
   s.scratch_ec=std::min(s.scratch_ec+1u,60u);++s.scratch_f0;
   if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0)approach_battle_offset(s.offset,0.f,.1f);
   if(age==30){s.frame=20;return true;}
   if(s.scratch_f0>180u)return finish();
  }
 }
 ++s.frame;host.advance_frame(s);return true;
}

// Item 17 DAT slots 6, 7, 8 and 18: falling traps, their impact field, and
// the delayed three-way parent. Source: 0060a980 cases 3c, 46, 50 and b4.
template<class Host> bool tick_roster_field_secondary_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(unsigned(s.item)!=17||(registration!=60&&registration!=70&&
    registration!=80&&registration!=180))
  throw std::invalid_argument("Unsupported field secondary projectile registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(registration==80){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}
  if(age>51)return finish();
 }else if(registration==60||registration==70){
  if(age==0){
   s.scale.fill(registration==60?.25f:.5f);
   s.speed=0;s.capacity.fill(0);s.scratch_e8=0;
   normal_projectile_direct_velocity(s);s.velocity[1]=0;
  }
  if(s.scratch_e8==0){
   s.velocity[1]-=.5f;
   if(host.stage_collision(s)==1){
    s.capacity.fill(1);s.velocity.fill(0);s.speed=0;s.scratch_e8=1;
   }
  }
  if(age>(registration==60?300:600)||projectile_contacts(s)!=0){
   if(registration==70){host.sound(s,115);host.child(s,8,0,0,false);}
   return finish();
  }
 }else{
  if(age==0){s.speed=5;s.capacity.fill(1);s.scratch_e8=0;s.scale.fill(1.5f);}
  if(age==1){normal_projectile_direct_velocity(s);s.velocity[1]=0;}
  if(s.scratch_e8==0)s.velocity[1]-=.5f;
  if(host.stage_collision(s)==1&&s.scratch_e8==0){
   s.velocity.fill(0);s.speed=0;s.scratch_e8=1;
  }
  if(age==600){
   host.child(s,19,0,0,false);host.child(s,20,0,0,false);
   host.child(s,21,0,0,false);host.sound(s,157);
   return finish();
  }
 }
 ++s.frame;host.advance_frame(s);return true;
}

// The delayed parent (registration 180) emits these three distinct DAT fields.
// Source: 0060a980 cases be, c8 and d2; the 200 variant loops its visual frame.
template<class Host> bool tick_roster_field_burst_projectile(
 KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(unsigned(s.item)!=17||(registration!=190&&registration!=200&&registration!=210))
  throw std::invalid_argument("Unsupported field burst projectile registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(age==0){
  s.rotation[0]=s.rotation[1]=0;s.rotation[2]=-s.pitch;
  s.speed=0;s.velocity[1]=0;s.scratch_e8=0;s.scratch_ec=255;
  if(registration!=210)s.capacity.fill(1);
  s.scale.fill(registration==190?4.5f:registration==200?6.5f:6.f);
 }
 if(registration==190||registration==200){
  const float delta=registration==190?
   (s.scale[0]>=6.f?.005f:.5f):(s.scale[0]>=10.f?.0035f:.25f);
  for(auto& axis:s.scale)axis+=delta;
  ++s.scratch_e8;
  if(s.scratch_e8>20){
   s.capacity.fill(0);
   if(registration==190||s.scratch_e8>30){
    s.scratch_ec-=5;
    if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}
   }
  }
  host.alpha(s,s.scratch_ec&255u);
  if(registration==200&&age==17){s.frame=1;return true;}
 }else{
  for(auto& axis:s.scale)axis+=1.f;
  if(age>60){
   s.capacity.fill(0);s.scratch_ec-=15;
   if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}
  }
  host.alpha(s,s.scratch_ec&255u);
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
