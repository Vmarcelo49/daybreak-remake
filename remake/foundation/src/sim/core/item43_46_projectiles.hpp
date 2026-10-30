#pragma once
#include "item11_22_projectiles.hpp"
namespace daybreak {
// Full original switches: Irie2 0062f180 and Akane2 006322d0.
inline bool item43_projectile_registration(unsigned item,unsigned reg){return item==43&&reg<=150&&reg%10==0;}
inline bool item46_projectile_registration(unsigned item,unsigned reg){return item==46&&reg<=70&&reg%10==0;}

template<class Host> bool tick_item43_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item43_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item43 registration");
 const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if((reg<=30||reg==100)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg<=30||reg==100){
  if(age==0){
   if(reg!=100)item9_13_birth_aim(s,host);
   if(reg==20){host.particle_offset(s,15,0,0,0);approach_battle_offset(s.offset,0,5);}
   if(reg>=20)s.scale.fill(4);
   s.speed=reg==0?55.f:reg==10?75.f:reg==20?70.f:reg==30?85.f:120.f;s.capacity.fill(1);
   if(reg>=20){s.scratch_e8=0;s.scratch_ec=reg==30?60:40;}
   if(reg==10)host.trail(s,0,10,20,1,0);
   if(reg==30)host.trail(s,0,30,30,1,0);
   if(reg==100)host.trail(s,0,60,60,1,0);
  }
  if(reg>=20){
   ++s.scratch_ec;const unsigned maximum=reg==30?120:100;
   if(projectile_signed(s.scratch_ec)>int(maximum))s.scratch_ec=maximum;
   if(reg==30&&age%5==0)host.particle_offset(s,15,0,0,0);
   if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
   if(reg!=100&&s.scratch_e8==0){
    const float ec=float(projectile_signed(s.scratch_ec));approach_battle_offset(s.offset,0,ec*.0015f);
    item9_13_pitch_step(s,host,3,ec*.0025f);
   }
  }
  // Registration10 emits a contact effect before the expiry test; the other
  // branches emit it only from inside their release path.
  auto impact=[&](){if(projectile_contacts(s)&0x80){host.child_position(s,14,0,0,0);host.sound(s,201);}};
  if(reg==10)impact();
  if(age>(reg==0?180:240)||projectile_contacts(s)!=0||host.stage_collision(s)==1){if(reg!=10)impact();return finish();}
 }else if(reg==50){
  if(age==0){s.speed=10;s.offset=float(host.random_word()%360u);s.pitch=float(host.random_word()%360u);}
  for(auto& axis:s.scale)axis-=.1f;if(s.scale[2]<=0)return finish();
 }else if(reg==60||reg==110){
  if(age==0&&reg==110)s.capacity.fill(1);if(age>51)return finish();
 }else if(reg==70||reg==90){
  if(reg==90)s.position=host.owner_position(s);s.pitch=0;s.rotation[0]+=1;
  if(age==0){s.scale[0]=s.scale[2]=0;if(reg==90)s.scratch_f8=0;}
  const float maximum=reg==70?3.f:4.5f;
  if(s.scale[2]>=maximum)s.scale[0]=s.scale[2]=maximum;
  else{const float angle=reg==70?float(age)*3.f:float(projectile_signed(s.frame*3u));const float growth=legacy_trig(angle,true)*(reg==70?.2f:.3f);s.scale[0]+=growth;s.scale[2]+=growth;}
  if(age%(reg==70?5:30)==0){s.capacity.fill(1);s.contacts.fill(0);}
  if(age%10==0)item11_22_spark(s,host,8,reg==70?400:800,reg==70?200.f:400.f);
  // 43/90 reads owner+ae04 (animation frame), unlike Takano's phase test.
  if(reg==90&&host.owner_state(s)==370&&host.owner_animation_frame(s)==0)s.scratch_f8=1;
  if(age<(reg==70?241:301)&&(reg==70||projectile_signed(s.scratch_f8)<1))s.scale[1]=legacy_trig(reg==70?float(age)*6.f:float(projectile_signed(s.frame*6u)),true)*.25f+.75f;
  else{s.capacity.fill(0);s.scale[1]-=.1f;if(s.scale[1]<=0)return finish();}
 }else if(reg==80){
  if(age==0){s.scale.fill(.5f);s.speed=float(host.random_word()%20u)*.1f+2;s.rotation[1]=float(host.random_word()%360u);s.pitch=90;}
  s.rotation[1]+=2;if(age>59)return finish();
 }else if(reg==120){
  if(age==0){s.scale.fill(.5f);s.scratch_e8=255;}
  item11_22_wave(s,float(age)*3,.1f);if(age==6)s.capacity.fill(0);
  if(age>2){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  host.alpha(s,s.scratch_e8&255u);if(age%5==0)item11_22_spark(s,host,8,200,100);
  if(age>30)return finish();
 }else if(reg==140){
  s.pitch=0;s.rotation[0]+=1;if(age==0)s.scale.fill(.5f);
  if(age%5==0)item11_22_spark(s,host,8,200,100);
  if(age>0){s.capacity.fill(0);s.scale[1]-=.025f;s.scale[0]+=.05f;s.scale[2]+=.05f;if(s.scale[1]<=0)return finish();}
 }else if(reg==150){
  if(age==0)s.scale.fill(.15f);s.speed=0;item11_22_wave(s,float(projectile_signed(s.frame*3u)),.05f);if(age>28)return finish();
 }
 // Original40/130 have no explicit case: preserve only the cursor advance.
 ++s.frame;host.advance_frame(s);return true;
}

template<class Host> bool tick_item46_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item46_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item46 registration");
 const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if(reg>=10&&reg<=40&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==70){
  if(age==0){s.speed=0;s.scratch_e8=255;}
  if(age>10){s.scratch_e8-=40;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  host.alpha(s,s.scratch_e8&255u);if(age>15)return finish();
 }else if(reg==10||reg==20||reg==30){
  if(age==0){
   if(reg==10)item9_13_birth_aim(s,host);
   s.speed=reg==20?40.f:60.f;s.capacity.fill(1);s.scale.fill(reg==10?2.f:1.5f);
   if(reg!=10){s.scratch_e8=s.scratch_ec=0;s.rotation[1]=60;}
  }
  if(host.stage_collision(s)==1||age>(reg==10?10:30)){
   s.capacity.fill(0);for(auto& axis:s.scale)axis-=reg==10?.2f:.1f;if(s.scale[0]<=0)return finish();
  }
 }else if(reg==40){
  if(age==0){s.ground_motion=true;s.wall_contact=false;s.speed=60;s.capacity.fill(99);s.scratch_e8=s.scratch_ec=0;s.rotation[1]=45;}
  ++s.scratch_e8;if(projectile_signed(s.scratch_e8)>10){s.scratch_e8=0;s.contacts.fill(0);}
  if(s.scratch_e8==0&&age>0)approach_battle_offset(s.offset,0,1);
  if(age%2==0){host.particle_offset(s,5,0,0,0);host.particle_offset(s,6,0,0,0);}
  if(!s.surface_flag){s.velocity[1]-=.5f;++s.scratch_ec;if(projectile_signed(s.scratch_ec)>20)return finish();}
  else s.velocity[1]=0;
  if(age>120){s.capacity.fill(0);return finish();}
 }else if(reg==50){
  if(age==0){s.rotation[1]=float(host.random_word()%50u)-25;s.rotation[2]=float(host.random_word()%50u)-25;}
  s.scale[0]*=.8f;s.scale[1]+=.1f;s.scale[2]*=.8f;if(s.scale[2]<.05f)return finish();
 }else if(reg==60){
  if(age==0){s.capacity.fill(1);s.contacts.fill(0);s.scale.fill(.5f);s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);}
  item11_22_wave(s,float(age)*4,.1f);if(age==6)s.capacity.fill(0);
  if(age>10){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  const auto color=s.scratch_e8&255u;host.color(s,color,color,color,255);if(projectile_signed(s.scratch_e8)<1)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
