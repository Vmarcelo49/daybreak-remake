#pragma once
#include "item41_projectile.hpp"

namespace daybreak {
inline bool item37_owner_interrupted(unsigned state){
 const auto signed_state=projectile_signed(state);
 return (signed_state>=104&&signed_state<200)||(signed_state>=204&&signed_state<300);
}

template<class Host> void item37_orbit_pose(KeiichiNormalProjectile& s,Host& host,float radius){
 const auto owner=host.owner_position(s);
 const float angle=host.owner_heading(s)-90,cosine=legacy_trig(s.orbit_angle,false);
 s.position[0]=cosine*(legacy_trig(angle,false)*radius)+owner[0];
 s.position[1]=legacy_trig(s.orbit_angle,true)*radius+owner[1]+75;
 s.position[2]=cosine*(legacy_trig(angle,true)*radius)+owner[2];
 s.target=host.owner_current_target(s);
 s.heading=host.owner_heading(s);s.offset=host.owner_offset(s);
 s.pitch=std::clamp(host.target_elevation(s),-30.f,30.f);
}

// Complete original006251d0 switch. Rewinding the script counter deliberately
// leaves the animation cursor untouched, as does every original early return.
template<class Host> bool tick_item37_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 const auto age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto stop_visual=[&](bool retarget){
  if(retarget)host.retarget_owner(s);
  host.particle_offset(s,13,0,0,0);return finish();
 };
 if((reg==30||reg==40||reg==50||reg==60||reg==70||reg==90)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==10||reg==20){
  if(age==0){s.speed=30;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  if(item37_owner_interrupted(host.owner_state(s))||age>300)return stop_visual(false);
  if(age<30){s.speed-=2;if(s.speed<2)s.speed=2;}
  if(age>29){
   if(age==60)host.trail(s,0,30,60,1,0);
   s.speed=60;approach_battle_offset(s.offset,reg==0?0.f:reg==10?-45.f:45.f,180);
   s.pitch=host.target_elevation(s);
   if(age%40==0)host.sound(s,99);
   const auto target=host.target_position(s);const float y=s.position[1]-target[1];
   if(y*y+host.target_horizontal_distance_squared(s)<360000){host.child_position(s,12,0,0,0);return finish();}
  }
 }else if(reg==30){
  if(age==0){host.particle_offset(s,10,0,0,0);s.speed=40;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
  if((projectile_contacts(s)!=0||host.stage_collision(s)==1)&&((projectile_contacts(s)&2)!=0||host.stage_collision(s)==1))s.scratch_f0=1;
  if(s.scratch_f0==1){s.speed=0;for(auto& axis:s.scale)axis-=.1f;if(s.scale[0]<=0)return finish();}
  s.scratch_ec+=2;if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0)approach_battle_offset(s.offset,0,float(projectile_signed(s.scratch_ec))*.0025f);
  if(age==30){s.frame=20;return true;}if(age>240)return finish();
 }else if(reg==40||reg==50||reg==60||reg==70){
  if(age==0){s.scale.fill(1);s.capacity.fill(1);item41_birth_aim(s,host);s.speed=42.5f;s.scratch_e8=0;s.scratch_ec=120;s.scratch_f0=0;}
  --s.scratch_ec;if(projectile_signed(s.scratch_ec)<0)s.scratch_ec=0;
  const float step=float(projectile_signed(s.scratch_ec))*.01f;
  if(reg==40||reg==60)s.heading+=step;else s.heading-=step;
  if(age>240||host.stage_collision(s)==1)return finish();
 }else if(reg==80||reg==150){
  if(age==0){s.scratch_e8=s.scratch_ec=0;s.orbit_angle=s.pitch+90;s.orbit_side=90-s.pitch;s.scratch_f8=0;s.speed=0;}
  const auto command=host.owner_projectile_command(s);
  if(reg==150||s.scratch_ec==0){
   if(reg==150)s.scratch_e8=s.frame*7u;else s.scratch_e8+=7;
   if(projectile_signed(s.scratch_e8)>90)s.scratch_e8=90;
   const float sine=legacy_trig(float(projectile_signed(s.scratch_e8)),true);
   float radius;
   if(reg==150){s.scratch_f0=std::uint32_t(std::int32_t(sine*100));radius=float(projectile_signed(s.scratch_f0));}
   else{radius=s.orbit_radius=sine*150;}
   item37_orbit_pose(s,host,radius);
   if(command==1&&s.scratch_f8==0){host.child_position(s,9,0,0,0);s.scratch_f8=1;}
   if(reg==80&&command==2)s.scratch_ec=2;
  }
  if(command==2)return stop_visual(reg==80);
  if(reg==80){const auto state=projectile_signed(host.owner_state(s));if(state>=100&&state<300)return stop_visual(true);}
  else if(item37_owner_interrupted(host.owner_state(s)))return stop_visual(true);
 }else if(reg==90){
  if(age==0){approach_battle_offset(s.offset,0,10);host.particle_offset(s,11,0,0,0);s.speed=60;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=s.scratch_f4=0;s.scale.fill(1);}
  if(host.stage_collision(s)==1&&host.stage_collision(s)==1)s.scratch_f0=1;
  if(s.scratch_f0==1){s.speed=0;for(auto& axis:s.scale)axis-=.05f;if(s.scale[0]<=0)return finish();}
  s.scratch_ec+=2;++s.scratch_f4;if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(age==60){s.frame=40;return true;}if(projectile_signed(s.scratch_f4)>180)return finish();
 }else if(reg==100||reg==110){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);s.scale.fill(.05f);s.speed=0;}
  item11_22_wave(s,float(projectile_signed(s.frame*3u)),.025f);
  if(age>6){s.scratch_e8-=10;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}
  host.alpha(s,s.scratch_e8&255u);
 }else if(reg==120){
  if(age==0){s.speed=0;s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  if(item37_owner_interrupted(host.owner_state(s)))return stop_visual(false);
  if(age<15){approach_battle_offset(s.offset,0,180);s.pitch=host.target_elevation(s);}
  if(age==15){host.sound(s,80);host.child_position(s,3,0,0,0);}
  if(age==120)return stop_visual(true);
 }else if(reg==130){
  if(age==0){s.speed=0;s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  approach_battle_offset(s.offset,0,180);s.pitch=host.target_elevation(s);s.speed=80;
  const auto target=host.target_position(s);const float y=s.position[1]-target[1];
  if(y*y+host.target_horizontal_distance_squared(s)<10000){for(unsigned n=0;n<3;++n)host.particle_offset(s,14,0,0,0);return finish();}
 }else if(reg==140){
  if(age==0){s.pitch=float(host.random_word()%360u);s.offset=float(host.random_word()%360u);s.speed=float(host.random_word()%20u)+2;s.rotation[1]=float(host.random_word()%360u);}
  s.speed*=.95f;if(age>59)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
}
