#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
namespace daybreak {
//5fd170 visual registrations70/90 share the factory list but have no capacity.
template<class Host> bool tick_bat_full_charge_visual(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(registration!=70&&registration!=90)throw std::runtime_error("Unsupported Bat full-charge visual");
 if(registration==70&&s.frame>15){for(auto& scale:s.scale)scale-=.1f;if(s.scale[2]<0){s.released=true;return false;}}
 if(registration==90&&s.frame>12){s.released=true;return false;}
 ++s.frame;host.advance_frame(s);return true;
}
//5fd170 registration50.5f6fd0 uses the same factory list with a zero birth ID.
template<class Host> bool tick_bat_full_charge_projectile(KeiichiNormalProjectile& s,Host& host){
 if(s.released)return false;
 if(s.item!=KeiichiProjectileItem::Bat)throw std::runtime_error("Unsupported full-charge projectile");
 if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
 if(s.frame==0){s.speed=52.5f;s.capacity.fill(3);s.scratch_e8=0;host.trail(s,0,200,60,1,0);host.visual_child(s,9);}
 if(projectile_signed(s.frame)%5==0)host.visual_child(s,7);
 s.contacts.fill(0); // Repeated contacts retain remaining capacity, not flags.
 if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
 if(s.scratch_e8==0){
  approach_battle_offset(s.offset,0,.005f);
  if(s.pitch-host.target_elevation(s)>1)s.pitch-=.005f;
  if(s.pitch-host.target_elevation(s)< -1)s.pitch+=.005f;
 }
 if(projectile_signed(s.frame)>480||host.stage_collision(s)==1){s.released=true;return false;}
 ++s.frame;host.advance_frame(s);return true;
}
// 620e20 registration50: Shovel's long homing full-charge projectile.
template<class Host> bool tick_shovel_homing_full_charge_projectile(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(s.item!=KeiichiProjectileItem::Shovel||registration!=50)throw std::runtime_error("Unsupported Shovel charged projectile");
 if(s.frame==0){s.speed=52;s.capacity.fill(3);s.scratch_e8=0;host.trail(s,0,200,60,1,0);host.visual_child(s,9);}
 if(s.frame%5==0)host.visual_child(s,7);
 s.contacts.fill(0);
 if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
 if(s.scratch_e8==0){
  approach_battle_offset(s.offset,0,.005f);
  if(s.pitch-host.target_elevation(s)>1)s.pitch-=.005f;
  if(s.pitch-host.target_elevation(s)< -1)s.pitch+=.005f;
 }
 if(projectile_signed(s.frame)>480||(projectile_contacts(s)!=0&&projectile_contacts(s)!=1)||host.stage_collision(s)==1){s.released=true;return false;}
 ++s.frame;host.advance_frame(s);return true;
}
//620e20 registrations60/70/90: stationary seed, delayed field and pulses.
template<class Host> bool tick_shovel_full_charge_projectile(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(s.item!=KeiichiProjectileItem::Shovel||(registration!=60&&registration!=70&&registration!=90))throw std::runtime_error("Unsupported Shovel full-charge projectile");
 if(registration==60){
  if(s.frame==0){s.speed=0;s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
  for(auto& scale:s.scale)scale-=.05f;if(s.scale[0]<=0)s.scale.fill(0);
  if(s.frame%15==0)host.visual_child(s,9,true); //5f7110 reconstructs relative unit direction.
  if(s.frame==91)host.child(s,7,0,0,true);
  if(projectile_signed(s.frame)>800||projectile_contacts(s)!=0||host.stage_collision(s)==1){s.released=true;return false;}
  if(s.frame>600){for(auto& scale:s.scale)scale-=.05f;if(s.scale[0]<=0){s.released=true;return false;}}
 }else if(registration==70){
  if(s.frame==0){s.scratch_e8=255;s.scratch_ec=0;s.scale={.1f,.15f,.1f};}
  if(s.scale[0]>=2){s.capacity.fill(99);s.scale={2,3,2};}
  else{s.scale[0]+=.1f;s.scale[1]+=.15f;s.scale[2]+=.1f;}
  if(s.frame%30==0)host.effect(s,178);
  // Global contact counter, not per-victim cooldown. Clear flags only on41.
  if(projectile_contacts(s)!=0&&++s.scratch_ec>40){s.scratch_ec=0;s.contacts.fill(0);}
  if(s.frame>510){s.capacity.fill(0);s.scratch_e8-=5;if(projectile_signed(s.scratch_e8)<0){s.released=true;return false;}}
 }else{
  if(s.frame==0){s.capacity.fill(1);s.contacts.fill(0);s.scale.fill(.5f);s.scratch_e8=255;s.rotation[0]=float(host.random_word()%360u);}
  for(auto& scale:s.scale)scale+=legacy_trig(float(s.frame)*4,false)*.1f;
  if(s.frame==6)s.capacity.fill(0);
  if(s.frame>10)s.scratch_e8=unsigned(std::max(0,projectile_signed(s.scratch_e8)-13));
  if(projectile_signed(s.scratch_e8)<1){s.released=true;return false;}
 }
 ++s.frame;host.advance_frame(s);return true;
}
//60ea90 registration60: ballistic ascent, then a single retarget at the apex.
template<class Host> bool tick_iron_full_charge_projectile(KeiichiNormalProjectile& s,Host& host){
 if(s.released)return false;
 if(s.item!=KeiichiProjectileItem::Iron)throw std::runtime_error("Unsupported Iron full-charge projectile");
 if(s.frame==0){s.speed=44.5f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
 if(s.frame==1)normal_projectile_direct_velocity(s);
 if(s.velocity[1]<0&&s.scratch_f0==0){
  //5f6880(1) normalizes velocity/angles, immediately superseded by full
  //180-degree turn, target pitch, speed60 and zero direction below.
  s.angular=true;s.scratch_f0=1;host.effect(s,93);s.velocity.fill(0);
 }
 if(s.scratch_f0==1){s.offset=0;s.pitch=host.target_elevation(s);s.speed=60;s.scratch_f0=2;host.effect(s,93);host.visual_child(s,10);}
 // Stage query is made even during ascent; its result only detonates phase2.
 if(projectile_contacts(s)!=0||(host.stage_collision(s)==1&&projectile_signed(s.scratch_f0)>1)){
  host.effect(s,92);host.child(s,7,0,0,false);s.released=true;return false;
 }
 if(projectile_signed(s.frame)>800){s.released=true;return false;}
 if(s.scratch_f0==2&&s.frame%5==0){host.visual_child(s,8);host.visual_child(s,9);}
 if(s.scratch_f0==0){s.velocity[1]-=.5f;s.velocity[0]=legacy_trig(s.heading+s.offset,false)*s.speed;s.velocity[2]=legacy_trig(s.heading+s.offset,true)*s.speed;}
 ++s.frame;host.advance_frame(s);return true;
}
// Host child(s,slot,yaw,pitch,relative_angles), effect(s,id), random_word()
// preserve spawn order. Angled fragments use5f6ef0, adding parent angles.
template<class Host> bool tick_lobbed_charge_projectile(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 const bool iron=s.item==KeiichiProjectileItem::Iron,shovel=s.item==KeiichiProjectileItem::Shovel;
 if((!iron&&!shovel)||(registration!=20&&registration!=40&&!(iron&&(registration==70||registration==80||registration==90||registration==100))))throw std::runtime_error("Unsupported lobbed charge script");
 if(iron&&registration==80){
  s.speed=45;if(s.frame>12){s.released=true;return false;}
 }else if(iron&&(registration==40||registration==70||registration==90||registration==100)){
  const bool explosion=registration==40||registration==70,full=registration==70||registration==100;
  if(s.frame==0){
   if(explosion){s.pitch=0;s.contacts.fill(0);}else s.speed=0;
   s.capacity.fill(1);s.scale.fill(explosion?(full?1.5f:1.f):(full?.3f:.2f));s.scratch_e8=255;
  }
  const float growth=legacy_trig(float(s.frame)*(explosion?3.f:4.f),false)*(explosion?(full?.3f:.15f):(full?.2f:.1f));
  for(auto& scale:s.scale)scale+=growth;
  if(explosion&&s.frame==6)s.capacity.fill(0);
  if(s.frame>(explosion?10u:0u))s.scratch_e8=unsigned(std::max(0,projectile_signed(s.scratch_e8)-13));
  if(s.frame>(explosion?30u:20u)){s.released=true;return false;}
 }else if(registration==40){ // Shovel fragments620e20 case40
  if(s.frame==0){s.scale.fill(.5f);for(auto& a:s.rotation)a=float(host.random_word()%360u);s.speed=15;s.capacity.fill(1);s.scratch_e8=0;}
  if(s.frame==1)normal_projectile_direct_velocity(s);
  s.scratch_e8+=50;s.velocity[1]-=.5f;
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0||projectile_signed(s.frame)>1800){s.released=true;return false;}
 }else {
  if(s.frame==0){
   if(shovel){s.scale.fill(.5f);for(auto& a:s.rotation)a=float(host.random_word()%360u);}
   approach_battle_offset(s.offset,0,10);s.speed=iron?44.5f:30.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;if(shovel)s.scratch_f0=0;
  }
  if(s.frame==(iron?1u:0u))normal_projectile_direct_velocity(s);
  s.velocity[1]-=iron?.5f:.25f;
  // Registrations20/40 do not reflect, including contacts100.
  if(projectile_signed(s.frame)>800||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   host.effect(s,iron?74u:176u);
   if(iron)host.child(s,4,0,0,false);
   else for(unsigned i=0;i<8;++i){s.scratch_f0=host.random_word()%360u;s.scratch_ec=host.random_word()%40u;host.child(s,4,float(s.scratch_f0),float(s.scratch_ec)+30,true);}
   s.released=true;return false;
  }
  if(iron){
   s.scratch_ec+=3;if(projectile_signed(s.scratch_ec)>70)s.scratch_ec=70;
   if(s.scratch_e8==0){const float step=float(s.scratch_ec)*.01f;if(s.offset>1)s.offset-=step;if(s.offset< -1)s.offset+=step;}
   s.velocity[0]=legacy_trig(s.heading+s.offset,false)*s.speed;s.velocity[2]=legacy_trig(s.heading+s.offset,true)*s.speed;
  }
 }
 ++s.frame;host.advance_frame(s);return true;
}
// 5fd170 registrations10/20. Registration10 is the left-hand preparation
// object;20 is the ordinary charged shot with its original own-trail callback.
template<class Host> bool tick_bat_charged_projectile(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(s.item!=KeiichiProjectileItem::Bat||(registration!=10&&registration!=20))
  throw std::runtime_error("Unsupported charged projectile script");
 if(registration==10){
  if(s.frame==0){s.speed=0;normal_projectile_direct_velocity(s);s.velocity[1]=15;}
  s.velocity[1]-=1.75f;
  if(projectile_signed(s.frame)>18){s.released=true;return false;}
 }else {
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(s.frame==0){
   const auto target=host.target_state(s);
   if((target>117&&target<122)||target==221){
    if(s.pitch-host.target_elevation(s)<10)s.pitch=host.target_elevation(s);
    if(s.pitch-host.target_elevation(s)>-10)s.pitch=host.target_elevation(s);
   }
   s.speed=50;s.capacity.fill(1);host.trail(s,0,80,30,1,0);s.scratch_e8=s.scratch_ec=0;s.scale.fill(.65f);
  }
  ++s.scratch_ec;if(projectile_signed(s.scratch_ec)>90)s.scratch_ec=90;
  if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0,float(s.scratch_ec)*.007499999832361937f);
   const float step=float(s.scratch_ec)*.0024999999441206455f;
   if(s.pitch-host.target_elevation(s)>1)s.pitch-=step;
   if(s.pitch-host.target_elevation(s)< -1)s.pitch+=step;
  }
  // This is the SCRIPT counter, not a monotonic lifetime. The original returns
  // before collision and cursor advance here; free-flight still runs afterwards.
  if(s.frame==10){s.frame=1;return true;}
  const auto contact=projectile_contacts(s);
  if(projectile_signed(s.frame)>480||(contact!=0&&contact!=1)||host.stage_collision(s)==1){s.released=true;return false;}
 }
 ++s.frame;host.advance_frame(s);return true;
}
}
