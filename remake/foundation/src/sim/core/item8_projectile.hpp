#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <stdexcept>

namespace daybreak {
// Original 006006b0, Satoko weapon0: complete supplied DAT switch. Child XYZ
// offsets and angular offsets are separate original services.
inline bool item8_projectile_registration(unsigned item,unsigned registration){
 return item==8&&registration<=160&&registration%10==0;
}
template<class Host> bool tick_item8_projectile(KeiichiNormalProjectile& s,
 unsigned registration,Host& host){
 if(s.released)return false;
 if(!item8_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item8 registration");
 const auto age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if((registration==110||registration==120)&&(projectile_contacts(s)&0x100))
  reflect_normal_projectile(s);
 if(registration==0||registration==10){
  if(age==0){
   s.speed=30.f;s.capacity.fill(1);s.scale.fill(.5f);
   normal_projectile_direct_velocity(s);s.ground_motion=true;s.wall_contact=false;
  }
  approach_battle_offset(s.offset,0.f,.1f);s.velocity[1]-=.3f;
  if(host.stage_collision(s)==1&&s.velocity[1]<0){
   s.velocity[1]=-s.velocity[1];if(s.velocity[1]>6.f)s.velocity[1]=6.f;
  }
  if(age>90||projectile_contacts(s)!=0||s.wall_contact){
   host.sound(s,105);host.child_position(s,8,0,0,0);return finish();
  }
 }else if(registration==20||registration==30){
  if(age==0){
   s.speed=40.f;s.capacity.fill(1);s.scratch_e8=0;
   host.trail(s,2,10.f,10,1,0);s.scale.fill(2.f);
  }
  if((registration==20&&age>25)||(registration==30&&age==25)){
   host.sound(s,105);const unsigned yaw=host.random_word()%360u;
   if(registration==30)s.scratch_e8=yaw;
   host.child_offset(s,registration==20?4:5,0,0,0,float(yaw),0);
   if(registration==30)host.child_offset(s,5,0,0,0,float(yaw)+180.f,0);
   host.particle_offset(s,7,0,0,0);return finish();
  }
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.sound(s,115);host.child_position(s,7,0,0,0);return finish();
  }
 }else if(registration==40||registration==50){
  if(age==0){
   s.speed=registration==40?2.f:20.f;s.capacity.fill(1);s.scratch_e8=0;
   normal_projectile_direct_velocity(s);if(registration==40)s.pitch=0;
  }
  if(registration==50){
   if(age==1){s.pitch=0;s.velocity[1]=0;}
   s.speed-=.5f;if(s.speed<2.f)s.speed=2.f;
  }
  s.velocity[1]-=.05f;if(s.velocity[1]<-4.f)s.velocity[1]=-4.f;
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0||age>600){
   host.child_position(s,8,0,0,0);host.sound(s,105);return finish();
  }
  if(s.offset>1.f)s.offset-=1.f;
  if(s.offset<-1.f)s.offset+=1.f;
  s.velocity[0]=legacy_trig(s.heading+s.offset,false)*s.speed;
  s.velocity[2]=legacy_trig(s.heading+s.offset,true)*s.speed;
 }else if(registration==60||registration==70||registration==80||registration==130){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.velocity[1]=0;s.capacity.fill(registration==70?0:1);}
  if(age>51)return finish();
 }else if(registration==90){
  if(age==0){s.speed=35.f;normal_projectile_direct_velocity(s);s.capacity.fill(1);s.scratch_e8=0;}
  if(s.scratch_e8==0){s.velocity[1]-=.75f;s.rotation[2]+=20.f;}
  if(s.scratch_e8==0&&host.stage_collision(s)==1){
   s.rotation[2]=s.pitch=s.speed=0;s.velocity.fill(0);s.scratch_e8=1;
  }
  if(projectile_signed(s.scratch_e8)>0){
   ++s.scratch_e8;
   if(s.scratch_e8==90){host.sound(s,108);host.child_position(s,10,0,40.f,0);}
   if(s.scratch_e8==300)return finish();
  }
  if(age>1800)return finish();
 }else if(registration==100){
  if(age==0){
   s.scale.fill(0);s.speed=s.pitch=s.velocity[1]=0;s.scratch_e8=255;s.scratch_ec=0;
   s.capacity.fill(0);normal_projectile_direct_velocity(s);
  }
  if(s.scratch_ec==0){
   if(s.scale[0]>=1.f){s.scale.fill(1.f);s.scratch_ec=1;s.capacity.fill(5);}
   else for(auto& axis:s.scale)axis+=.05f;
  }
  if(projectile_signed(s.scratch_ec)>0){
   if(projectile_signed(s.scratch_ec)%10==0)s.contacts.fill(0);
   ++s.scratch_ec;
  }
  if(projectile_signed(s.scratch_ec)>150){
   s.capacity.fill(0);s.scratch_e8-=15;
   if(projectile_signed(s.scratch_e8)<0)return finish();
  }
  host.alpha(s,s.scratch_e8&255u);
 }else if(registration==110||registration==120){
  if(age==0){
   const int target=host.target_state(s);
   if((target>117&&target<122)||target==221){
    if(s.pitch-host.target_elevation(s)<10.f)s.pitch=host.target_elevation(s);
    if(s.pitch-host.target_elevation(s)>-10.f)s.pitch=host.target_elevation(s);
   }
   s.scale.fill(2.f);s.speed=10.f;host.trail(s,2,10.f,20,1,0);
   s.capacity.fill(1);s.scratch_e8=0;
  }
  s.speed+=registration==110?1.5f:2.25f;
  if(s.offset>90.f||s.offset<-90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.05f);
   if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=.05f;
   if(s.pitch-host.target_elevation(s)<-3.f)s.pitch+=.05f;
  }
  if(age>90||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.child_position(s,7,0,0,0);host.sound(s,105);return finish();
  }
 }else{
  if(age==0){s.scratch_f4=s.scratch_f8=0;s.speed=0;s.scale.fill(0);}
  const unsigned owner_state=host.owner_state(s);
  if(owner_state!=135&&owner_state!=186)return finish();
  s.pitch=0;
  auto grow=[&](){
   if(s.scale[0]>=1.f)s.scale.fill(1.f);
   else for(auto& axis:s.scale)axis+=.05f;
  };
  if(registration!=140||owner_state==186)grow();
  if(owner_state==186){
   std::array<float,3> position{};float heading=0,offset=0;
   if(host.owner_linked_pose(s,position,heading,offset)){
    s.heading=heading;s.offset=offset;
    const float angle=90.f-(s.heading+s.offset),distance=registration==140?135.f:125.f;
    s.position={legacy_trig(angle,true)*distance+position[0],
                position[1]+(registration==140?90.f:50.f),
                legacy_trig(angle,false)*distance+position[2]};
   }
  }else{
   if(registration==140)grow();
   s.heading=host.owner_heading(s);s.offset=host.owner_offset(s);s.pitch=host.owner_pitch(s);
   s.position=host.owner_position(s);s.position[1]+=85.f;
  }
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
