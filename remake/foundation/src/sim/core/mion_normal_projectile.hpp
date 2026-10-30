#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
namespace daybreak {
inline bool mion_projectile_item(KeiichiProjectileItem item){return item==KeiichiProjectileItem::MionPistols||item==KeiichiProjectileItem::MionWater||item==KeiichiProjectileItem::MionLaser;}
// 5fb000,5fc6f0,621d60: normal400 projectiles, special replacements, and their
// muzzle/impact children. Host owns DAT clocks/contacts and effect presentation.
template<class Host> bool tick_mion_normal_projectile(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);const bool pistol=item==2,water=item==4,laser=item==35;
 if(!mion_projectile_item(s.item))throw std::runtime_error("Unsupported Mion projectile item");
 auto finish=[&](){s.released=true;return false;};
 if(laser&&registration==40){
  if(s.frame==0){s.scale={1,4,4};s.speed=.01f;s.scratch_e8=s.scratch_ec=0;s.capacity.fill(1);}
  ++s.scratch_e8;s.scratch_ec+=2;
  if(s.frame==41)return finish();
 }else if((pistol&&registration==70)||(water&&registration==30)||(laser&&registration==50)){
  if(laser)s.scale.fill(3);
  if(projectile_signed(s.frame)>5)return finish();
 }else if(pistol&&registration==80){
  if(s.frame==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360);}
  if(projectile_signed(s.frame)>4){s.scratch_e8-=50;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}
  // Original5fafc0 changes material alpha; retained as a presentation request.
  host.alpha(s,unsigned(s.scratch_e8)&255u);
 }else {
  if(registration!=0&&registration!=(water?40u:10u))throw std::runtime_error("Unsupported Mion projectile registration");
  const bool special=registration!=0;
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  auto aim=[&](){const int target=host.target_state(s);if((target>117&&target<122)||target==221){if(s.pitch-host.target_elevation(s)<10)s.pitch=host.target_elevation(s);if(s.pitch-host.target_elevation(s)>-10)s.pitch=host.target_elevation(s);}};
  auto muzzle=[&](unsigned slot){host.visual_child(s,slot);};
  if(s.frame==0){
   if(!pistol)aim();
   if(water&&special)s.scale.fill(2);
   muzzle(pistol?7u:water?3u:5u);
   s.speed=pistol?(special?75.f:50.f):water?(special?47.5f:42.5f):(special?75.f:60.f);
   s.capacity.fill(1);
   if(pistol){if(special)s.scratch_e8=s.scratch_ec=0;aim();}
   else {s.scratch_e8=s.scratch_ec=s.scratch_f0=0;if(!water||!special)s.scratch_f4=0;if(laser&&special){s.scale[1]=s.scale[2]=2.5f;}}
  }
  auto steer=[&](){
   if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0){
    const float turn=pistol?.01f:water&&special?.3f:.1f;
    const float pitch=pistol?.01f:water&&special?.1f:.05f;
    approach_battle_offset(s.offset,0,turn);
    if(s.pitch-host.target_elevation(s)>3)s.pitch-=pitch;
    if(s.pitch-host.target_elevation(s)< -3)s.pitch+=pitch;
   }
  };
  if(pistol){
   if(special){++s.scratch_ec;if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;}
   if(!special)steer();
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1){host.child(s,8,0.f,0.f,false);return finish();}
   if(special)steer();
   if(projectile_signed(s.frame)>90)return finish();
  }else if(water){
   if((projectile_contacts(s)!=0||host.stage_collision(s)==1)&&((projectile_contacts(s)&2)||host.stage_collision(s)==1)){
    if(special)s.scratch_f0=1;else s.scratch_f4=1;
   }
   ++s.scratch_ec;if(!special)++s.scratch_f0;
   if(projectile_signed(s.scratch_ec)>(special?100:60))s.scratch_ec=special?100:60;
   steer();
   if((special?projectile_signed(s.frame):projectile_signed(s.scratch_f0))>180||(special?s.scratch_f0:s.scratch_f4)==1){
    s.capacity.fill(0);s.scale[0]-=special?.2f:.15f;s.scale[1]-=.2f;s.scale[2]-=.2f;
    if(s.scale[0]<=0)return finish();
   }
   if(s.frame==30){s.frame=20;return true;}
  }else {
   if(host.stage_collision(s)==1)s.scratch_f4=1;
   ++s.scratch_ec;++s.scratch_f0;steer();
   if(projectile_signed(s.scratch_f0)>480||host.stage_collision(s)==1){s.scratch_f4=1;s.capacity.fill(0);s.speed=0;}
   if(s.scratch_f4==1){for(auto& scale:s.scale)scale-=.1f;if(s.scale[0]<=0)return finish();}
   if(s.frame==60){s.frame=40;return true;}
  }
 }
 ++s.frame;host.advance_frame(s);return true;
}
}
