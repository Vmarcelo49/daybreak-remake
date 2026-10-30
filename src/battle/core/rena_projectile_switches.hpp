#pragma once
#include "item41_projectile.hpp"
namespace daybreak {
// Full5f91c0/5fbf20/620290 switches; original defaults deliberately advance.
template<class Host> bool tick_item1_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 const bool normal_reflection=reg==0||reg==10||reg==40||reg==60||reg==70||reg==90||reg==130||reg==140;
 if((normal_reflection||reg==110||reg==120)&&(projectile_contacts(s)&0x100)){reflect_normal_projectile(s);if(!normal_reflection)s.capacity.fill(5);}
 if(reg==0||reg==10||reg==60||reg==70){
  if(age==0){s.speed=reg<=10?37.5f:45.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;if(reg==60)s.rotation[2]=20;item41_birth_aim(s,host);}
  if(reg>=60&&age%2==0)host.particle_offset(s,reg==60?15:16,0,0,0);
  ++s.scratch_ec;if(projectile_signed(s.scratch_ec)>int(reg<=10?75:120))s.scratch_ec=reg<=10?75:120;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){approach_battle_offset(s.offset,0,reg<=10?.2f:float(projectile_signed(s.scratch_ec))*.01f+.25f);item9_13_pitch_step(s,host,3,reg<=10?.2f:.25f);}
  if(age>240||(projectile_contacts(s)!=0&&projectile_contacts(s)!=1)||host.stage_collision(s)==1){if(host.stage_collision(s)==1)host.child_position(s,5,0,0,0);return finish();}
 }else if(reg==20||reg==80){
  if(age==0){s.speed=25;s.capacity.fill(1);s.scratch_e8=0;}
  if(age==1){normal_projectile_direct_velocity(s);s.velocity[1]=10;}
  if(reg==20)s.scratch_e8+=50;s.velocity[1]-=.3f;if(reg==80)approach_battle_offset(s.offset,0,2);
  if(host.stage_collision(s)==1){host.child_position(s,reg==20?3:10,0,0,0);host.sound(s,71);return finish();}if(age>1800)return finish();
 }else if(reg==30||reg==100){if(age==0){s.capacity.fill(1);if(reg==100){s.scale.fill(3);s.speed=0;s.velocity[1]=0;}}if(age>51)return finish();}
 else if(reg==40||reg==90||reg==130||reg==140){
  if(age==0){s.speed=reg<=90?30.f:25.f;s.capacity.fill(1);s.rotation[1]=reg==40?45.f:reg==90?-45.f:reg==130?60.f:-60.f;s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
  ++s.scratch_ec;if(s.speed>30)s.speed=30;if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(projectile_signed(s.scratch_f0)<2){
   if(s.scratch_f0==0){if(std::abs(s.offset)<3)s.scratch_f0=1;if(std::abs(s.offset)>90)s.scratch_f0=2;approach_battle_offset(s.offset,0,reg==140?2.5f:3.f);item9_13_pitch_step(s,host,1,2);}
   if(s.scratch_f0==1){if(std::abs(s.offset)>90)s.scratch_f0=2;approach_battle_offset(s.offset,0,float(projectile_signed(s.scratch_ec))*(reg<=90?.0035f:.004f));item9_13_pitch_step(s,host,1,float(projectile_signed(s.scratch_ec))*.005f);}
  }
  if(age>480||projectile_contacts(s)!=0||host.stage_collision(s)==1){if(host.stage_collision(s)==1)host.child_position(s,5,0,0,0);return finish();}
 }else if(reg==50){
  s.speed=0;s.velocity[1]=0;if(age==0)s.scratch_e8=255;
  if(age>0){s.scratch_e8-=10;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}host.alpha(s,s.scratch_e8&255u);
 }else if(reg==110||reg==120){
  if(age==0){s.rotation[1]=reg==110?45.f:-45.f;s.speed=45;s.capacity.fill(5);s.scratch_e8=0;s.scratch_ec=50;s.scratch_f0=5;s.contacts.fill(0);}
  if(age%2==0)host.particle_offset(s,17,0,0,0);
  if(projectile_contacts(s)!=0){if(projectile_signed(s.scratch_f0)>0){s.speed=0;--s.scratch_f0;return true;}s.speed=60;s.contacts.fill(0);s.scratch_f0=10;}
  --s.scratch_ec;if(projectile_signed(s.scratch_ec)<0)s.scratch_ec=0;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){const float counter=float(projectile_signed(s.scratch_ec)),step=counter*.005f+.05f;approach_battle_offset(s.offset,0,step);
   if(s.pitch-host.target_elevation(s)>3)s.pitch-=step;
   if(s.pitch-host.target_elevation(s)<-3){const float product=float(double(counter)*.005);const float upward=float(double(product)+.05000000074505806);s.pitch+=upward;}
  }
  if(age>240||host.stage_collision(s)==1){if(host.stage_collision(s)==1)host.child_position(s,5,0,0,0);return finish();}
 }else if(reg==150||reg==160||reg==170){if(age==0){s.speed=0;if(reg==170)s.rotation[0]=float(host.random_word()%360u);if(reg==160)s.rotation[1]=90;else s.rotation[2]=35;}if(age>13)return finish();}
 ++s.frame;host.advance_frame(s);return true;
}
template<class Host> bool tick_item3_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if(reg==0){if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}if(age>51)return finish();}
 else if(reg==10||reg==30){
  if(age==0){s.speed=float(host.random_word()%80u)*.1f+4;s.capacity.fill(1);s.scratch_e8=0;}
  if(age==1){normal_projectile_direct_velocity(s);s.velocity[1]=float(host.random_word()%40u)*.1f+8;}
  s.scratch_e8+=50;s.velocity[1]-=.3f;if(host.stage_collision(s)==1){host.child_position(s,reg==10?2:4,0,0,0);host.sound(s,78);return finish();}if(age>1800)return finish();
 }else if(reg==20||reg==40){
  if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);s.scratch_e8=0;if(reg==40)s.scale.fill(1.5f);}
  if(age>26&&projectile_signed(s.scratch_e8)<int(reg==20?7:15)){++s.scratch_e8;s.frame=18;return true;}if(age==52)return finish();
 }else if(reg==50){
  if(age==0){normal_projectile_direct_velocity(s);s.speed=legacy_trig(s.pitch,false)*10;s.velocity[1]=legacy_trig(s.pitch,true)*17.5f;s.capacity.fill(1);s.scratch_e8=0;}
  if(host.stage_collision(s)==1)return finish();s.velocity[1]-=.75f;if(age>1800)return finish();
 }else if(reg==60||reg==90){if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);s.scale.fill(reg==60?3.f:6.f);}if(age>30)return finish();}
 else if(reg==70){
  if(age==0){s.scale.fill(2);s.speed=0;s.velocity[1]=0;s.pitch=0;s.capacity.fill(1);}
  if(age<20){const float pitch=float(host.random_word()%20u)+60,yaw=float(host.random_word()%5u)+float(projectile_signed(s.frame*13u));host.child_offset(s,3,0,0,0,yaw,pitch);}if(age>51)return finish();
 }else if(reg==80){
  if(age==0){s.speed=25;normal_projectile_direct_velocity(s);s.capacity.fill(1);s.scratch_e8=0;}
  if(s.scratch_e8==0){s.velocity[1]-=.35f;s.rotation[2]+=20;}
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0){host.child_position(s,7,0,0,0);host.sound(s,71);return finish();}if(age>1800)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
template<class Host> bool tick_item33_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if((reg==40||reg==50)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==20){if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);s.scale.fill(reg==0?3.f:4.f);}if(age>30)return finish();}
 else if(reg==10||reg==30){
  if(age==0){s.speed=reg==10?20.f:35.f;s.capacity.fill(1);s.scratch_e8=255;if(reg==30)s.scale.fill(.5f);}if(age==1)normal_projectile_direct_velocity(s);s.velocity[1]-=1;
  if(host.stage_collision(s)==1)return finish();if(age>60){s.capacity.fill(0);s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}host.alpha(s,s.scratch_e8&255u);}
 }else if(reg==40||reg==50){
  if(age==0){s.speed=reg==40?20.f:25.f;s.capacity.fill(5);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;s.scale.fill(0);}
  if(projectile_contacts(s)!=0){++s.scratch_f0;if(projectile_signed(s.scratch_f0)>2){s.scratch_f0=0;s.contacts.fill(0);}}
  if(age%3==0)host.particle_offset(s,6,0,0,0);if(s.scratch_e8==0){approach_battle_offset(s.offset,0,.2f);item9_13_pitch_step(s,host,1,.1f);}
  if(age>int(reg==40?90:180)||host.stage_collision(s)==1)return finish();
 }else if(reg==60){if(age==0){s.scale.fill(1.5f);s.rotation[2]=float(host.random_word()%30u)-15;s.rotation[1]=float(host.random_word()%30u)-15;s.rotation[0]=float(host.random_word()%360u);}if(age>14)return finish();}
 else if(reg==70){
  if(age==0){s.speed=45;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;item41_birth_aim(s,host);}
  if(age%2==0)host.particle_offset(s,16,0,0,0);++s.scratch_ec;if(projectile_signed(s.scratch_ec)>120)s.scratch_ec=120;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;if(s.scratch_e8==0){approach_battle_offset(s.offset,0,float(projectile_signed(s.scratch_ec))*.01f+.25f);item9_13_pitch_step(s,host,3,.25f);}
  if(age>240||(projectile_contacts(s)!=0&&projectile_contacts(s)!=1)||host.stage_collision(s)==1){if(host.stage_collision(s)==1)host.child_position(s,5,0,0,0);return finish();}
 }else if(reg==80){
  if(age==0){s.scale.fill(3);s.speed=45;s.capacity.fill(1);s.scratch_e8=0;}approach_battle_offset(s.offset,0,.01f);if(age%6==0)host.particle_offset(s,11,0,0,0);
  if(host.stage_collision(s)==1){host.child_position(s,9,0,0,0);host.sound(s,173);return finish();}if(age>600)return finish();
 }else if(reg==90){if(age==0){s.scale.fill(4);s.speed=0;s.velocity[1]=0;}if(age>51)return finish();}
 else if(reg==110){if(age==0){s.scale.fill(3);s.speed=0;s.rotation[2]=25;}if(age>13)return finish();}
 ++s.frame;host.advance_frame(s);return true;
}
}
