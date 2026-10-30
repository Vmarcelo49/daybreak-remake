#pragma once
#include "item9_13_projectiles.hpp"
namespace daybreak {
inline bool item11_projectile_registration(unsigned item,unsigned reg){return item==11&&reg<=110&&reg%10==0;}
inline bool item22_projectile_registration(unsigned item,unsigned reg){return item==22&&reg<=160&&reg%10==0;}
// Original66b668 _ftol returns a signed64 result; only EAX is stored at af60.
inline std::int32_t item22_integer_coordinate(float value){
 const double number=std::trunc(double(value));
 if(!std::isfinite(number)||number<-9223372036854775808.0||number>=9223372036854775808.0)return 0;
 return projectile_signed(std::uint32_t(std::uint64_t(std::int64_t(number))));
}
template<class Host> void item11_22_spark(KeiichiNormalProjectile& s,Host& host,unsigned slot,unsigned range,float center){
 const float z=float(host.random_word()%range)-center,x=float(host.random_word()%range)-center;
 host.particle_offset(s,slot,x,0,z);
}
inline void item11_22_wave(KeiichiNormalProjectile& s,float angle,float amount){
 const float growth=legacy_trig(angle,false)*amount;for(auto& axis:s.scale)axis+=growth;
}
template<class Host> bool item11_22_owner_field(KeiichiNormalProjectile& s,Host& host,unsigned slot){
 const auto age=projectile_signed(s.frame);s.position=host.owner_position(s);s.pitch=0;s.rotation[0]+=1;
 if(age==0){s.scale[0]=s.scale[2]=0;s.scratch_f8=0;}
 // Original threshold2 and replacement3 are deliberately different.
 if(s.scale[2]>=2.f)s.scale[0]=s.scale[2]=3.f;
 else{const float growth=legacy_trig(float(projectile_signed(s.frame*3u)),true)*.15f;s.scale[0]+=growth;s.scale[2]+=growth;}
 if(age%5==0){s.capacity.fill(1);s.contacts.fill(0);}
 if(age%10==0)item11_22_spark(s,host,slot,300,150);
 if(host.owner_state(s)==370&&host.owner_phase(s)==0)s.scratch_f8=1;
 if(age<301&&projectile_signed(s.scratch_f8)<1)s.scale[1]=legacy_trig(float(projectile_signed(s.frame*6u)),true)*.25f+.75f;
 else{s.capacity.fill(0);s.scale[1]-=.1f;if(s.scale[1]<=0){s.released=true;return false;}}
 return true;
}
template<class Host> bool tick_item11_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item11_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item11 registration");
 auto finish=[&](){s.released=true;return false;};const auto age=projectile_signed(s.frame);
 if((reg==0||reg==60)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==60||reg==10||reg==70||reg==80){
  const bool fast=reg==10||reg==70;
  if(age==0){
   item9_13_birth_aim(s,host);
   if(fast)host.particle_offset(s,2,0,0,0);
   if(reg==60)host.trail(s,0,10.f,20,1,0);
   if(reg==70)host.trail(s,2,60.f,30,1,0);
   if(reg==80)host.trail(s,4,120.f,30,1,0);
   if(fast||reg==80)s.scale.fill(3);
   s.speed=reg==0?35.f:reg==60?45.f:reg==80?40.f:50.f;s.scratch_e8=0;s.scratch_ec=reg==80?0:40;s.capacity.fill(1);
  }
  if(reg==80&&age%5==0)host.particle_offset(s,2,0,0,0);
  ++s.scratch_ec;
  if(reg==10){if(projectile_signed(s.scratch_ec)<100)s.scratch_ec=100;}
  else if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&(fast||(age>10&&age<180))){
   const float ec=float(projectile_signed(s.scratch_ec));
   approach_battle_offset(s.offset,0.f,ec*(reg==0||reg==60?.0025f:reg==70?.005f:.002f));
   if(fast)item9_13_pitch_step(s,host,3.f,ec*(reg==10?.0015f:.0035f));
  }
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1||(fast&&age==(reg==10?120:240))){
   if(reg==10)host.child_position(s,3,0,0,0);
   if(reg==70){host.particle_offset(s,3,0,0,0);host.particle_offset(s,4,0,0,0);}
   if(reg==80)host.child_position(s,9,0,0,0);
   return finish();
  }
  if(!fast&&age>120)return finish();
 }else if(reg==20){
  if(age==0)s.scale.fill(.15f);s.speed=0;
  item11_22_wave(s,float(projectile_signed(s.frame*3u)),.05f);if(age>28)return finish();
 }else if(reg==30||reg==90){
  if(age==0){s.capacity.fill(reg==30?1:0);s.contacts.fill(0);s.scale.fill(1);s.scratch_e8=255;}
  item11_22_wave(s,float(projectile_signed(s.frame*3u)),reg==30?.2f:.4f);
  if(age==6)s.capacity.fill(0);
  if(age>10){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  host.alpha(s,s.scratch_e8&255u);if(age>30)return finish();
 }else if(reg==40){
  s.pitch=0;s.rotation[0]+=1;s.scale[0]=s.scale[2]=2;
  if(age%5==0){s.capacity.fill(1);s.contacts.fill(0);item11_22_spark(s,host,5,400,200);}
  if(age<241)s.scale[1]=legacy_trig(float(projectile_signed(s.frame*6u)),true)*.25f+.75f;
  else{s.capacity.fill(0);s.scale[1]-=.1f;if(s.scale[1]<=0)return finish();}
 }else if(reg==50){
  if(age==0){s.speed=float(host.random_word()%20u)*.1f+2;s.pitch=90;}
  if(age>59)return finish();
 }else if(reg==100){if(!item11_22_owner_field(s,host,5))return false;}
 // Registration110: original default, no explicit switch case.
 ++s.frame;host.advance_frame(s);return true;
}
template<class Host> bool tick_item22_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item22_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item22 registration");
 auto finish=[&](){s.released=true;return false;};const auto age=projectile_signed(s.frame);
 if((reg==0||reg==10)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==10){
  if(age==0){s.speed=reg==0?35.f:55.f;s.scratch_e8=0;s.scratch_ec=40;s.capacity.fill(1);if(reg==10)s.scale.fill(2);}
  if(age==1)normal_projectile_direct_velocity(s);
  s.velocity[1]-=reg==0?.15f:.2f;s.scratch_ec+=reg==0?1u:4u;
  if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>600){host.child_position(s,reg==0?4:5,0,0,0);host.sound(s,159);return finish();}
  s.velocity[0]=legacy_trig(s.heading+s.offset,false)*s.speed;s.velocity[2]=legacy_trig(s.heading+s.offset,true)*s.speed;
 }else if(reg==20||reg==30){
  if(age==0){
   if(reg==30)host.trail(s,0,20.f,30,1,0);
   approach_battle_offset(s.offset,0,10);s.speed=reg==20?40.f:35.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   if(reg==20){s.scratch_f0=0;host.particle_offset(s,13,0,0,0);}s.scale.fill(2);
  }
  if(age==(reg==20?0:1))normal_projectile_direct_velocity(s);
  if(reg==30&&age%5==0)host.particle_offset(s,13,0,0,0);
  if(reg==20&&s.velocity[1]>30)s.velocity[1]=30;s.velocity[1]-=.5f;
  if(age>800||projectile_contacts(s)!=0||host.stage_collision(s)==1){host.sound(s,74);host.child_position(s,reg==20?6:7,0,0,0);return finish();}
  const float distance=host.target_horizontal_distance(s)*.05f;
  if(distance<s.speed)s.speed=distance;
  if(s.offset<90&&s.offset>-90&&s.speed<distance&&s.velocity[1]<0&&s.speed<-s.velocity[1]){
   s.speed+=2.5f;if(-s.velocity[1]<s.speed)s.speed=-s.velocity[1];
  }
  if(s.speed<40.f-float(age))s.speed=40.f-float(age);
  s.speed=std::max(0.f,std::min(40.f,s.speed));
  if(s.scratch_e8==0){if(s.offset>1){s.offset-=1;if(s.offset<1)s.offset=0;}if(s.offset<-1){s.offset+=1;if(s.offset>-1)s.offset=0;}}
  if(s.speed<=-s.velocity[1]&&s.velocity[1]<0){
   ++s.scratch_f0;if(projectile_signed(s.scratch_f0)>60)s.scratch_f0=60;
   if(s.offset>1){s.offset-=float(projectile_signed(s.scratch_f0))*.5f;if(s.offset<1)s.offset=0;}
   if(s.offset<-1){s.offset+=float(projectile_signed(s.scratch_f0))*.1f;if(s.offset>-1)s.offset=0;}
  }
  s.velocity[0]=legacy_trig(s.heading+s.offset,false)*s.speed;s.velocity[2]=legacy_trig(s.heading+s.offset,true)*s.speed;
 }else if(reg>=40&&reg<=70){
  if(age==0){s.capacity.fill(1);s.contacts.fill(0);s.scale.fill(reg==40?.15f:reg==50?.3f:reg==60?.5f:1.f);s.scratch_e8=255;}
  item11_22_wave(s,float(age)*(reg==40?4.f:3.f),reg==50?.075f:reg==70?.2f:.1f);
  if(age==6)s.capacity.fill(0);
  if(age>10){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  host.alpha(s,s.scratch_e8&255u);if(age>30)return finish();
 }else if(reg==80||reg==90){
  s.pitch=0;s.rotation[0]+=1;if(age==0)s.scale[0]=s.scale[2]=0;
  if(s.scale[2]>=(reg==80?2.f:3.f))s.scale[0]=s.scale[2]=reg==80?2.f:3.f;
  else{const float growth=legacy_trig(float(age)*3.f,reg==90)*.2f;s.scale[0]+=growth;s.scale[2]+=growth;}
  if(age%5==0){s.capacity.fill(1);s.contacts.fill(0);item11_22_spark(s,host,10,400,200);}
  if(age<241)s.scale[1]=legacy_trig(float(age)*6.f,true)*.25f+.75f;
  else{s.capacity.fill(0);s.scale[1]-=.1f;if(s.scale[1]<=0)return finish();}
 }else if(reg==100){
  if(age==0){s.speed=float(host.random_word()%20u)*.1f+2;s.pitch=90;}
  if(age>59)return finish();
 }else if(reg==110||reg==150){
  host.store_owner_field_position(s);
  if(age==0){s.speed=25;s.scratch_e8=0;}
  if(reg==110){
   if(s.scratch_e8==0){s.speed-=.5f;if(s.speed<3){s.speed=3;s.scratch_e8=1;host.child_position(s,12,0,0,0);}}
   if(s.scratch_e8==1){s.offset=0;item9_13_pitch_step(s,host,1.f,.05f);}
   if(s.scratch_e8==2)return finish();
   if(age>1200||host.owner_field_exit(s)==1){host.request_owner_field_exit(s);s.scratch_e8=2;}
  }else{
   if(age==1)normal_projectile_direct_velocity(s);
   if(age%5==0)host.particle_offset(s,13,0,0,0);s.velocity[1]-=.5f;
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1){host.sound(s,74);host.child_position(s,16,0,0,0);return finish();}
   if(age>300)return finish();
  }
 }else if(reg==120||reg==160){
  if(reg==120)s.position=host.owner_field_position(s);
  if(age%105==0)host.sound(s,154);s.rotation[0]+=1;
  if(age==0){s.scale[0]=s.scale[2]=0;s.scratch_e8=0;if(reg==160){s.speed=3;s.pitch=0;}}
  if(reg==120)s.pitch=0;
  if(s.scratch_e8==0){if(s.scale[2]>=3){s.scale[0]=s.scale[2]=3;s.scratch_e8=1;}else{s.scale[0]+=reg==120?.1f:.3f;s.scale[2]+=reg==120?.1f:.3f;}}
  if(age%5==0&&s.scratch_e8==1){s.capacity.fill(1);s.contacts.fill(0);}
  if(reg==160&&projectile_signed(s.scratch_e8)<2){s.offset=0;s.pitch=host.target_elevation(s);}
  if(age%5==0&&s.scratch_e8==1)item11_22_spark(s,host,10,600,300);
  if((age<1201&&host.owner_field_exit(s)!=1)||projectile_signed(s.scratch_e8)>1){
   if(projectile_signed(s.scratch_e8)<2)s.scale[1]=legacy_trig(float(age)*6.f,true)*.25f+.75f;
  }else s.scratch_e8=2;
  if(s.scratch_e8==2){s.capacity.fill(0);s.scale[1]-=.1f;if(s.scale[1]<=0)return finish();}
 }else if(reg==130){
  if(age==0)s.scale.fill(.15f);s.speed=0;item11_22_wave(s,float(projectile_signed(s.frame*3u)),.05f);if(age>28)return finish();
 }else if(reg==140){if(!item11_22_owner_field(s,host,10))return false;}
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
