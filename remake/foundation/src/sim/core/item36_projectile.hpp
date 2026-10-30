#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace daybreak {
// Original 00622ab0, Shion weapon2: all eighteen original DAT registrations.
inline bool item36_owner_keeps_projectile(unsigned state){
 return state==400||state==401||state==402||(state>=420&&state<=423);
}
inline bool item36_projectile_registration(unsigned item,unsigned registration){
 return item==36&&registration<=170&&registration%10==0;
}

template<class Host> bool tick_item36_projectile(KeiichiNormalProjectile& s,
 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item36_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item36 registration");
 const auto age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 const bool rotating=(registration>=20&&registration<=50)||
                     (registration>=70&&registration<=120);
 if(rotating&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration==0||registration==10){
  const bool charged=registration==10;
  if(age==0){
   const int target=host.target_state(s);
   if((target>117&&target<122)||target==221){
    if(s.pitch-host.target_elevation(s)<10.f)s.pitch=host.target_elevation(s);
    if(s.pitch-host.target_elevation(s)>-10.f)s.pitch=host.target_elevation(s);
   }
   host.trail(s,charged?1:0,20.f,10,1,0);
   approach_battle_offset(s.offset,0.f,10.f);
   s.speed=charged?120.f:80.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=s.scratch_f4=0;s.orbit_radius=0;
   host.child_position(s,6,0,0,0);s.scale.fill(2.f);
  }
  std::array<float,3> aim{};
  for(unsigned axis=0;axis<3;++axis)aim[axis]=s.position[axis]+s.velocity[axis]*40.f;
  host.owner_projectile_aim(s,aim);
  if(!item36_owner_keeps_projectile(host.owner_state(s)))return finish();
  if(s.scratch_ec==0){
   if(charged&&age%4==0)host.particle_offset(s,17,0,0,0);
   s.speed-=charged?4.f:3.f;
   const auto contact=projectile_contacts(s);
   if(s.speed<=0.f||contact!=0||host.stage_collision(s)==1){
    s.speed=0;
    if(contact&1u)s.scratch_ec=1;
    else{s.scratch_ec=2;host.retarget_owner(s);host.owner_signal(s,1);}
   }
  }
  if(s.scratch_ec==1){
   s.capacity.fill(0);s.speed=std::max(0.f,s.speed-1.f);++s.scratch_e8;
   if(s.scratch_e8==20){
    const int x=host.owner_input_x(s);
    if(x==0){
     s.scratch_ec=2;host.child_offset(s,charged?15:13,0,0,0,180.f,0);
     host.retarget_owner(s);host.owner_signal(s,1);
    }else host.owner_signal(s,x<0?2:3);
   }
   const unsigned state=host.owner_state(s);
   if((state==420||state==422)&&host.owner_animation_frame(s)==15){
    s.scratch_ec=3;host.child_offset(s,charged?16:14,0,0,0,90.f,0);host.retarget_owner(s);
   }
   if((state==421||state==423)&&host.owner_animation_frame(s)==15){
    s.scratch_ec=5;host.child_offset(s,charged?16:14,0,0,0,-90.f,0);host.retarget_owner(s);
   }
  }
  if(s.scratch_ec==2){
   s.capacity.fill(0);s.speed=100.f;
   approach_battle_offset(s.offset,0.f,180.f);s.pitch=host.target_elevation(s);
   if(host.target_distance_squared(s)<10000.f&&projectile_signed(s.scratch_f4)>1)return finish();
   ++s.scratch_f4;
  }
  if(s.scratch_ec==3||s.scratch_ec==5){
   s.offset+=s.scratch_ec==3?90.f:-90.f;
   s.scratch_ec=s.scratch_ec==3?4u:6u;s.speed=100.f;s.capacity.fill(0);
   s.pitch=host.target_elevation(s);
   s.orbit_radius=std::min(180.f,s.orbit_radius+6.f);
   approach_battle_offset(s.offset,0.f,s.orbit_radius);
  }
  // Separate original tests: the first side-return visit steers twice.
  if(s.scratch_ec==4||s.scratch_ec==6){
   s.pitch=host.target_elevation(s);s.orbit_radius=std::min(180.f,s.orbit_radius+6.f);
   approach_battle_offset(s.offset,0.f,s.orbit_radius);
   if(host.target_distance_squared(s)<10000.f&&projectile_signed(s.scratch_f4)>1)return finish();
   ++s.scratch_f4;
  }
 }else if(registration==60){
  if(age==0)s.speed=0;
  if(!item36_owner_keeps_projectile(host.owner_state(s)))return finish();
  const auto aim=host.owner_aim(s);
  const float dx=aim[0]-s.position[0],dy=aim[1]-s.position[1],dz=aim[2]-s.position[2];
  const float horizontal=dx*dx+dz*dz;
  s.scale={std::sqrt(horizontal+dy*dy)/107.f,.5f,.5f};
  s.position=host.owner_right_hand(s);
  constexpr float pi=3.1415927410125732f;
  s.offset=float(std::atan2(double(aim[2]-s.position[2]),double(aim[0]-s.position[0]))/pi*180.0)-s.heading;
  s.pitch=float(std::atan2(double(aim[1]-s.position[1]),double(std::sqrt(horizontal)))/pi*180.0);
 }else if(rotating){
  const bool large=registration==40||registration==50;
  if(age==0){
   s.speed=large?90.f:60.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   s.scale.fill(large?3.5f:2.5f);
   s.rotation[1]=registration==20||registration==40||registration==90?-45.f:
                 registration==30||registration==50||registration==100?45.f:
                 registration==70?-30.f:registration==80?30.f:registration==110?-60.f:60.f;
  }
  s.speed=std::max(5.f,s.speed-(registration==20||registration==30?4.f:2.f));
  const int lifetime=registration==20?40:registration==30?24:registration==50?44:60;
  if(host.stage_collision(s)==1||age>lifetime){
   s.speed-=3.f;s.capacity.fill(0);for(auto& axis:s.scale)axis-=.5f;
   if(s.scale[0]<=0.f)return finish();
  }
 }else if(registration>=130&&registration<=160){
  if(age==0){s.speed=1.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scale.fill(2.5f);}
  if(age==1)s.speed=registration==150?90.f:registration==160?120.f:60.f;
  if(host.stage_collision(s)==1||age>6){
   s.speed-=3.f;s.capacity.fill(0);for(auto& axis:s.scale)axis-=.5f;
   if(s.scale[0]<=0.f)return finish();
  }
 }else if(registration==170){
  if(age==0){
   s.scale.fill(.7f);s.rotation[2]=float(host.random_word()%30u)-15.f;
   s.rotation[1]=float(host.random_word()%30u)-15.f;s.rotation[0]=float(host.random_word()%360u);
  }
  if(age>14)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak