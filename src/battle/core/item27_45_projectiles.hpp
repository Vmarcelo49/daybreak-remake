#pragma once
#include "item11_22_projectiles.hpp"
namespace daybreak {
inline bool item27_projectile_registration(unsigned item,unsigned reg){return item==27&&reg<=140&&reg%10==0;}
inline bool item45_projectile_registration(unsigned item,unsigned reg){return item==45&&reg<=120&&reg%10==0;}
// Original42dac0(3), not the ordinary spine point(2).
template<class Host> void item45_birth_head_aim(KeiichiNormalProjectile& s,Host& host){
 if(s.pitch-host.target_head_elevation(s)<10&&s.pitch-host.target_head_elevation(s)>-10)s.pitch=host.target_head_elevation(s);
 if(s.pitch-host.target_head_elevation(s)>=10)s.pitch-=10;
 if(s.pitch-host.target_head_elevation(s)<=-10)s.pitch+=10;
}
template<class Host> bool tick_item27_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item27_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item27 registration");
 const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if((reg==0||reg==10||reg==140)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==10||reg==140){
  if(age==0){item9_13_birth_aim(s,host);approach_battle_offset(s.offset,0,5);s.scale=reg==10?std::array<float,3>{1.5f,.5f,.5f}:std::array<float,3>{6,1,1};s.speed=reg==10?65.f:45.f;s.capacity.fill(1);}
  // Contact/stage is tested even when already expired; expiry alone has no impact visual.
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){host.particle_offset(s,3,0,0,0);return finish();}
  if(age>180)return finish();
 }else if(reg==20){s.speed=0;if(age>5)return finish();}
 else if(reg==30){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);}
  if(age>4){s.scratch_e8-=50;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}
  host.alpha(s,s.scratch_e8&255u);
 }else if(reg==40||reg==50||reg==130){
  if(age==0){s.scale.fill(2);s.capacity.fill(1);host.particle_offset(s,7,0,0,0);s.scratch_e8=s.scratch_ec=0;s.scratch_f0=host.random_word()%10u;host.trail(s,reg==40?5:2,40,reg==40?40:20,1,0);s.speed=55;}
  s.speed-=2;
  // Original50/130 compare against f0+25 but replace with f0+20.
  if(s.speed<float(projectile_signed(s.scratch_f0))+25)s.speed=float(projectile_signed(s.scratch_f0))+(reg==40?25.f:20.f);
  s.scratch_ec+=2;if(projectile_signed(s.scratch_ec)>150)s.scratch_ec=150;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){const float ec=float(projectile_signed(s.scratch_ec));approach_battle_offset(s.offset,0,ec*(reg==40?.003f:.004f));item9_13_pitch_step(s,host,1,ec*(reg==40?.002f:.0025f));}
  if(age>480||projectile_contacts(s)!=0||host.stage_collision(s)==1){host.child_position(s,6,0,0,0);host.sound(s,74);return finish();}
 }else if(reg==60){if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}if(age>51)return finish();}
 else if(reg==70||reg==80){if(age>(reg==70?5:29))return finish();}
 else if(reg==90){
  if(age==0){item9_13_birth_aim(s,host);s.speed=5;s.capacity.fill(1);host.particle_offset(s,7,0,0,0);s.scratch_e8=s.scratch_ec=0;}
  s.scale.fill(legacy_trig(float(age)*30,true)*.05f+.5f);++s.scratch_ec;s.speed+=.25f;if(s.speed>40)s.speed=40;
  if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){const float ec=float(projectile_signed(s.scratch_ec));approach_battle_offset(s.offset,0,ec*.002f);item9_13_pitch_step(s,host,3,ec*.002f);}
  if(age>480||projectile_contacts(s)!=0||host.stage_collision(s)==1){for(unsigned slot:{10u,11u,12u})host.child_position(s,slot,0,0,0);host.sound(s,157);return finish();}
 }else if(reg==100||reg==110||reg==120){
  if(age==0){s.rotation={0,0,-s.pitch};s.speed=0;s.velocity[1]=0;s.scratch_e8=0;s.scratch_ec=255;s.scale.fill(reg==100?8.f:reg==110?4.5f:6.f);if(reg!=120)s.capacity.fill(reg==100?0:1);}
  const float growth=reg==120?1.f:s.scale[0]>=(reg==100?14.f:10.f)?(reg==100?.005f:.0035f):(reg==100?.5f:.25f);
  for(auto& axis:s.scale)axis+=growth;
  if(reg==100){
   // Original rewinds the script counter and returns without DAT cursor advance.
   if(age==17){s.frame-=16;return true;}
   ++s.scratch_e8;const auto e8=projectile_signed(s.scratch_e8);
   if(e8>10&&e8%5==0&&e8<120){s.capacity.fill(1);s.contacts.fill(0);}
   if(e8>120){s.scratch_ec-=5;s.capacity.fill(0);if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}
  }else if(reg==110){
   ++s.scratch_e8;const auto e8=projectile_signed(s.scratch_e8);if(e8>20){s.capacity.fill(0);if(e8>90){s.scratch_ec-=5;if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}}
  }else if(age>60){s.capacity.fill(0);s.scratch_ec-=15;if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}
  host.alpha(s,s.scratch_ec&255u);
 }
 ++s.frame;host.advance_frame(s);return true;
}
template<class Host> bool tick_item45_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item45_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item45 registration");
 const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if((reg==0||reg==10||reg==30||reg==40||reg==60||reg==110||reg==120)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==10||reg==120){
  if(age==0){if(reg==120)item9_13_birth_aim(s,host);else item45_birth_head_aim(s,host);approach_battle_offset(s.offset,0,5);s.scratch_e8=0;host.particle_offset(s,2,0,0,0);s.speed=reg==10?150.f:80.f;s.capacity.fill(1);}
  if(s.scratch_e8==0){
   if(reg==10&&age%5==0)host.particle_offset(s,10,0,0,0);
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>180){s.scratch_e8=1;s.speed=0;}
  }
  if(s.scratch_e8==1){for(auto& axis:s.scale)axis-=.1f;if(s.scale[0]<=0)return finish();}
 }else if(reg==20||reg==50){s.speed=0;if(age>5)return finish();}
 else if(reg==30||reg==40||reg==60||reg==110){
  if(age==0){if(reg!=60)item45_birth_head_aim(s,host);s.scratch_e8=0;host.particle_offset(s,reg<=40?2:7,0,0,0);s.speed=reg==30?150.f:reg==40?225.f:reg==60?500.f:200.f;s.capacity.fill(1);}
  if((reg==60||reg==110)&&age==1)s.capacity.fill(1);
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>180){host.particle_offset(s,reg<=40?9:8,0,0,0);return finish();}
 }else if(reg>=70&&reg<=100){
  if(age==0)s.scale.fill(.05f);s.speed=0;
  item11_22_wave(s,float(projectile_signed(s.frame*3u)),reg==70?.2f:reg==100?.025f:.5f);
  if(age>(reg==70?10:reg==90?5:28))return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
