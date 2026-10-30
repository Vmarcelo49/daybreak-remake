#pragma once
#include "mion_charged_projectile.hpp"
namespace daybreak {
inline bool mion_full_charge_projectile_registration(unsigned item,unsigned r){
 return item==2?(r==50||r==70||r==80):item==4?r==20:item==35&&(r==40||r==80||r==90);
}
template<class Host> bool tick_mion_full_charge_projectile(KeiichiNormalProjectile& s,unsigned r,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);if(!mion_full_charge_projectile_registration(item,r))throw std::runtime_error("Unsupported Mion full-charge projectile");
 auto finish=[&](){s.released=true;return false;};
 // The original reflection dispatch admits pistol50; water20 and laser
 // full-charge registrations bypass it. Shared reflection has its own oracle.
 if(item==2&&r==50&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(item==2&&r==50){
  if(s.frame==0){
   host.visual_child(s,7);s.speed=80;s.capacity.fill(1);s.scale={3.5f,1,1};
   const int target=host.target_state(s);
   if((target>117&&target<122)||target==221){if(s.pitch-host.target_elevation(s)<10)s.pitch=host.target_elevation(s);if(s.pitch-host.target_elevation(s)>-10)s.pitch=host.target_elevation(s);}
  }
  if(projectile_signed(s.frame)>240||host.stage_collision(s)==1){host.child(s,8,0,0,false);return finish();}
 }else if(item==2&&r==70){if(projectile_signed(s.frame)>5)return finish();
 }else if(item==2&&r==80){
  if(s.frame==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360);}
  if(projectile_signed(s.frame)>4){s.scratch_e8-=50;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}
  host.color(s,s.scratch_e8&255,255,255,255);
 }else if(item==4||r==40||r==80){
  if(s.frame==0){s.scale=item==4?std::array<float,3>{1.5f,1.5f,1.5f}:r==40?std::array<float,3>{1,4,4}:std::array<float,3>{1,.1f,.1f};s.speed=.01f;s.scratch_e8=s.scratch_ec=0;s.capacity.fill(item==35&&r==80?0:1);}
  ++s.scratch_e8;s.scratch_ec+=2;if(s.frame==41)return finish();
 }else{
  if(s.frame==0){s.scale={1,4,4};s.speed=.3f;s.scratch_e8=255;s.scratch_ec=0;s.capacity.fill(1);}
  s.scale[1]+=.15f;s.scale[2]+=.15f;
  if(projectile_signed(s.frame)>20){s.scratch_e8-=20;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}
  host.color(s,s.scratch_e8&255,s.scratch_e8&255,s.scratch_e8&255,255);
  if(projectile_signed(s.frame)>30)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
}
