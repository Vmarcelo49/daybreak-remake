#pragma once
#include "item41_projectile.hpp"
namespace daybreak {
template<class Host> bool tick_item12_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if(reg==0||reg==10||reg==20||reg==30||reg==50){
  if(age==0){s.speed=1;s.capacity.fill(1);s.scratch_e8=0;s.scale.fill(reg<=10?2.f:20.f);}
  if(age==4){s.speed=0;s.capacity.fill(0);return finish();}for(auto& axis:s.scale)axis-=reg<=10?.4f:3.f;if(s.scale[2]<=0)return finish();
 }else if(reg==40){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.capacity.fill(1);s.scratch_e8=255;}
  item11_22_wave(s,float(projectile_signed(s.frame*4u)),.2f);if(age>0){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  if(age>20)return finish();host.alpha(s,s.scratch_e8&255u);
 }
 ++s.frame;host.advance_frame(s);return true;
}
template<class Host> bool tick_item42_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if((reg==50||reg==60)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==10||reg==20||reg==30){
  if(reg==0)host.collision_geometry(s);if(reg==20)host.stage_collision(s);
  if(age==0){s.speed=1;s.capacity.fill(1);s.scratch_e8=0;s.scale.fill(reg==20?4.f:2.f);}
  if(age==4){s.speed=0;s.capacity.fill(0);return finish();}
  if((reg==0&&age>0||reg==20)&&projectile_contacts(s)!=0){
   const float radius=host.collision_radius(s),horizontal=host.target_horizontal_distance_squared(s);
   if(reg==0)s.turn_rate=horizontal;
   const auto target=host.target_position(s);const float y=target[1]-s.position[1];
   if((reg==20?horizontal:float(double(y)*y+s.turn_rate))<radius*radius&&s.scratch_e8==0){
    const float x=target[0]-s.position[0],height=y+100,z=target[2]-s.position[2];host.child_offset(s,reg==0?1:3,x,height,z,0,0);
    if(reg==20)host.particle_offset_direction(s,4,x,height,z,0,0);++s.scratch_e8;
   }
  }
  for(auto& axis:s.scale)axis-=reg==20?.8f:.4f;if(s.scale[2]<=0)return finish();
 }else if(reg==40){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.capacity.fill(1);s.scratch_e8=255;}item11_22_wave(s,float(projectile_signed(s.frame*4u)),.2f);
  if(age>0){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}if(age>20)return finish();host.alpha(s,s.scratch_e8&255u);
 }else if(reg==50||reg==60){
  if(age==0){item41_birth_aim(s,host);s.scale=reg==50?std::array<float,3>{6,1,1}:std::array<float,3>{1.5f,.5f,.5f};s.speed=reg==50?65.f:85.f;s.capacity.fill(1);}
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){host.particle_offset(s,8,0,0,0);return finish();}if(age>180)return finish();
 }else if(reg==70){s.speed=0;if(age>5)return finish();}
 else if(reg==80){if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);}if(age>4){s.scratch_e8-=50;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}host.alpha(s,s.scratch_e8&255u);}
 else if(reg==90){if(age==0){s.scale.fill(5);s.speed=float(host.random_word()%20u)*.1f+2;s.rotation[1]=float(host.random_word()%360u);s.pitch=90;}if(age>29)return finish();}
 ++s.frame;host.advance_frame(s);return true;
}
template<class Host> bool tick_item25_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if((reg<=30&&reg%10==0||reg==70)&&(projectile_contacts(s)&0x100)){reflect_normal_projectile(s);s.capacity.fill(reg<=10?5:reg==70?4:1);}
 if(reg==0||reg==10){
  if(age==0){item41_birth_aim(s,host);if(reg==10)host.trail(s,2,40,15,1,0);s.scratch_f4=55;s.capacity.fill(reg==0?4:5);s.scratch_e8=s.scratch_f0=0;s.scratch_ec=reg==0?0:40;}
  if(age%3==0)host.particle_offset(s,8,0,0,0);
  if(projectile_contacts(s)!=0){if(projectile_signed(s.scratch_f0)<5){s.speed=1;++s.scratch_f0;return true;}s.scratch_f0=0;s.speed=float(projectile_signed(s.scratch_f4));s.contacts.fill(0);}
  s.scratch_f4-=reg==0?2u:1u;if(projectile_signed(s.scratch_f4)<30)s.scratch_f4=30;s.speed=float(projectile_signed(s.scratch_f4));
  s.scratch_ec+=reg==0?1u:2u;if(projectile_signed(s.scratch_ec)>int(reg==0?60:90))s.scratch_ec=reg==0?60:90;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;if(s.scratch_e8==0){const float step=float(projectile_signed(s.scratch_ec))*(reg==0?.007f:.01f);approach_battle_offset(s.offset,0,step);item9_13_pitch_step(s,host,3,step);}
  if(age>int(reg==0?300:240)||host.stage_collision(s)==1)return finish();
 }else if(reg==20||reg==30){
  if(age==0){s.scale.fill(reg==20?.75f:1.f);s.speed=reg==20?50.f:70.f;s.capacity.fill(1);s.scratch_e8=0;host.trail(s,reg==20?0:2,10,reg==20?40:50,1,0);}
  s.speed-=1.5f;if(s.speed<25)s.speed=25;if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){approach_battle_offset(s.offset,0,reg==20?.1f:.3f);item9_13_pitch_step(s,host,1,reg==20?.05f:.1f);}if(age>300||host.stage_collision(s)==1)return finish();
 }else if(reg==40){if(age==0)s.capacity.fill(1);if(age>51)return finish();}
 else if(reg==50){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.capacity.fill(1);s.scratch_e8=255;}item11_22_wave(s,float(age)*4,.1f);
  if(age>0){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}if(age>20)return finish();host.alpha(s,s.scratch_e8&255u);
 }else if(reg==60){if(age==0){s.speed=90;s.capacity.fill(1);}if(age>120||(projectile_contacts(s)!=0&&projectile_contacts(s)!=1)||host.stage_collision(s)==1)return finish();}
 else if(reg==70){
  if(age==0){s.speed=50;host.trail(s,2,40,15,1,0);s.capacity.fill(4);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
  s.speed-=1;if(s.speed<30)s.speed=30;
  if(projectile_contacts(s)!=0){if(projectile_signed(s.scratch_f0)<5){s.speed=1;++s.scratch_f0;return true;}s.scratch_f0=0;s.speed=35;s.contacts.fill(0);}
  ++s.scratch_ec;if(projectile_signed(s.scratch_ec)>30)s.scratch_ec=30;if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){const float step=float(projectile_signed(s.scratch_ec))*.009f;approach_battle_offset(s.offset,0,step);item9_13_pitch_step(s,host,1,step);}if(age>240||host.stage_collision(s)==1)return finish();
 }else if(reg==80){if(age==0){s.scale.fill(.4f);s.rotation[2]=float(host.random_word()%20u)-10;s.rotation[1]=float(host.random_word()%20u)-10;s.rotation[0]=float(host.random_word()%360u);}if(age>14)return finish();}
 ++s.frame;host.advance_frame(s);return true;
}
}
