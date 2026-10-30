#pragma once
#include "mion_normal_projectile.hpp"
namespace daybreak {
inline bool mion_charged_projectile_registration(unsigned item,unsigned r){
 return item==2?(r==20||r==30||r==40||r==90||r==100||r==110):item==4?(r==10||r==50):item==35&&(r==20||r==30||r==60||r==70);
}
template<class Host> bool tick_mion_charged_projectile(KeiichiNormalProjectile& s,unsigned r,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);if(!mion_charged_projectile_registration(item,r))throw std::runtime_error("Unsupported Mion charged projectile");
 auto finish=[&](){s.released=true;return false;};
 if(item==2&&(r==20||r==30)){
  const bool special=r==30;
  if(s.frame==0){
   s.speed=40;s.capacity.fill(1);host.visual_child(s,9);
   if(special)host.trail(s,2,200,25,1,0);
   s.scratch_e8=s.scratch_ec=0;
   const int target=host.target_state(s);
   if((target>117&&target<122)||target==221){if(s.pitch-host.target_elevation(s)<10)s.pitch=host.target_elevation(s);if(s.pitch-host.target_elevation(s)>-10)s.pitch=host.target_elevation(s);}
  }
  s.scratch_ec+=special?2u:1u;if(projectile_signed(s.scratch_ec)>(special?150:100))s.scratch_ec=special?150:100;
  if(!special&&s.frame%2==0)host.visual_child(s,10);
  if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&projectile_signed(s.frame)>0){
   volatile float step=float(projectile_signed(s.scratch_ec))*.0075f;
   approach_battle_offset(s.offset,0,step);
   if(s.pitch-host.target_elevation(s)>3)s.pitch-=special?1.f:float(step);
   if(s.pitch-host.target_elevation(s)< -3)s.pitch+=special?1.f:float(step);
  }
  if(projectile_signed(s.frame)>480||projectile_contacts(s)!=0||host.stage_collision(s)==1){host.child(s,special?11:4,0,0,false);host.effect(s,74);return finish();}
 }else if(item==2&&(r==40||r==110)){
  if(s.frame==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);if(r==110)s.scale.fill(1.75f);}
  if(projectile_signed(s.frame)>51)return finish();
 }else if(item==2&&r==90){if(projectile_signed(s.frame)>5)return finish();
 }else if(item==2&&r==100){
  if(s.frame==0){volatile float size=float(host.random_word()%10)*.1f;size=size+1.f;s.scale.fill(float(size));s.rotation[1]=float(host.random_word()%360);}
  if(projectile_signed(s.frame)>29)return finish();
 }else if(item==4){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  const bool special=r==50;
  if(s.frame==0){if(special)s.scale={1.5f,2,2};host.visual_child(s,3);s.speed=special?45.f:40.f;s.scratch_e8=s.scratch_ec=s.scratch_f0=0;s.capacity.fill(1);}
  ++s.scratch_e8;s.scratch_ec+=2;
  if((projectile_contacts(s)!=0||host.stage_collision(s)==1)&&(!special||s.scratch_f0==0)&&((projectile_contacts(s)&2)||host.stage_collision(s)==1))s.scratch_f0=1;
  if(projectile_signed(s.scratch_e8)>90||s.scratch_f0==1){s.capacity.fill(0);s.scale[0]-=special?.15f:.1f;s.scale[1]-=special?.2f:.1f;s.scale[2]-=special?.2f:.1f;if(s.scale[0]<=0)return finish();}
  if(s.frame==30){s.frame=20;return true;}
 }else if(r==20||r==30){
  if(s.frame==0){s.scale={1.5f,r==20?.25f:.5f,r==20?.25f:.5f};s.speed=.01f;s.scratch_e8=s.scratch_ec=0;s.capacity.fill(1);host.visual_child(s,6);}
  ++s.scratch_e8;s.scratch_ec+=2;if(s.frame==41)return finish();
 }else {
  if(s.frame==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360);s.scale.fill(.05f);s.speed=0;if(r==60)host.visual_child(s,7);}
  volatile float growth=legacy_trig(float(projectile_signed(s.frame*3u)),false)*.025f;
  for(auto& v:s.scale)v+=growth;
  if(projectile_signed(s.frame)>6){s.scratch_e8-=10;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}
  host.alpha(s,s.scratch_e8&255);
 }
 ++s.frame;host.advance_frame(s);return true;
}
}


