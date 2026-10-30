#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace daybreak {
// Original 005ff3d0 cases 20..80. Registration 0/10 uses the shared motion
// handler; the other registrations are one DAT-selected state machine.
inline bool item7_projectile_registration(unsigned item,unsigned registration){
 return item==7&&registration>=20&&registration<=80&&registration%10==0;
}
template<class Host> bool tick_item7_projectile(KeiichiNormalProjectile& s,
                                                unsigned registration,Host& host){
 if(s.released)return false;
 if(!item7_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item7 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 if(registration==20||registration==30){
  if(age==0){
   s.speed=70.f;s.capacity.fill(1);s.scratch_e8=0;
   s.scratch_ec=s.scratch_f0=60;s.scratch_f4=0;
   s.scale.fill(2.f);
   if(registration==20)s.scratch_f8=0;
   else host.trail(s,2,50.f,90,1,0);
  }
  if(registration==20){
   if(projectile_signed(s.scratch_f8)==0){
    s.speed-=3.f;
    if(s.speed<20.f){s.speed=20.f;s.scratch_f8=1;
     host.trail(s,0,20.f,30,1,0);}
   }
   if(projectile_signed(s.scratch_f8)==1){s.speed+=.75f;if(s.speed>50.f)s.speed=50.f;}
  }else{s.speed-=2.5f;if(s.speed<30.f)s.speed=30.f;}
  s.scratch_ec+=2u;s.scratch_f0-=2u;
  if(projectile_signed(s.scratch_f0)<0)s.scratch_f0=0;
  if(projectile_signed(s.scratch_ec)>120)s.scratch_ec=120;
  if((s.offset>90.f||s.offset< -90.f)&&age>15)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   if(s.scratch_f4==0){
    const float step=float(projectile_signed(s.scratch_f0))*.05f+
                     float(projectile_signed(s.scratch_ec))*.005f;
    if(s.pitch-host.target_elevation(s)>1.f)s.pitch-=step;
    if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=step;
    if(std::fabs(s.pitch-host.target_elevation(s))<1.f)s.scratch_f4=1;
   }
   if(s.scratch_f4==1){
    const float step=registration==20?.3f:.4f;
    if(s.pitch-host.target_elevation(s)>1.f)s.pitch-=step;
    if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=step;
   }
   approach_battle_offset(s.offset,0.f,registration==20?.2f:.35f);
  }
  if(age>300||host.stage_collision(s)==1||projectile_contacts(s)!=0){
   host.child(s,4,0,0,false);host.sound(s,74);return finish();
  }
  return advance();
 }
 if(registration==40){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}
  if(age>51)return finish();
  return advance();
 }
 if(registration==50){
  if(age==0){s.speed=60.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  if(age==120){s.position=host.target_position(s);s.position[1]+=1000.f;}
  if(age==121){s.pitch=host.target_elevation(s);s.offset=0;
   host.trail(s,0,10.f,20,1,0);}
  if(age>120&&host.stage_collision(s)==1){host.visual_child(s,8);return finish();}
  return advance();
 }
 if(registration==60){
  if(age==0){s.speed=30.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  if(age<30){s.speed-=3.f;if(s.speed<0)s.speed=0;}
  if(age>29&&age<300&&projectile_signed(s.scratch_ec)<1){
   if(age==30)host.trail(s,0,10.f,30,1,0);
   s.speed=60.f;
   if(age%40==0)host.sound(s,99);
   if(age%20==0){
    s.scratch_f0=180;const float step=float(projectile_signed(s.scratch_f0))*.5f;
    approach_battle_offset(s.offset,0.f,step);
    if(s.pitch-host.target_elevation(s)>3.f)s.pitch-=step;
    if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step;
    s.scratch_ec=5;
   }
   const auto target=host.target_position(s);
   const float y=s.position[1]-target[1];
   if(host.target_horizontal_distance_squared(s)+y*y<360000.f&&s.scratch_e8==0)
    s.scratch_e8=1;
   const auto state=host.owner_state(s);
   if((state>103&&state<200)||(state>203&&state<300)){
    s.frame=300;return advance();
   }
  }
  if(projectile_signed(s.scratch_ec)>0){
   s.speed=0;
   const auto target=host.target_position(s);
   const float y=s.position[1]-target[1];
   if(host.target_horizontal_distance_squared(s)+y*y<360000.f&&s.scratch_e8==0)
    s.scratch_e8=1;
   if(projectile_signed(s.scratch_e8)>0){
    ++s.scratch_e8;
    if(projectile_signed(s.scratch_e8)<30){
     approach_battle_offset(s.offset,0.f,180.f);
     s.pitch=host.target_elevation(s);
    }
    if(s.scratch_e8==40){host.sound(s,80);host.child(s,7,0,0,false);}
    if(s.scratch_e8==60)s.frame=300;
   }
   if(s.scratch_e8==0)--s.scratch_ec;
  }
  if(projectile_signed(s.frame)>300){
   s.pitch=90.f-float(host.random_word()%20u);s.speed=80.f;
   if(projectile_signed(s.frame)>640)return finish();
  }
  return advance();
 }
 if(registration==70){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){s.speed=40.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;}
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
   if((projectile_contacts(s)&2)||host.stage_collision(s)==1)return finish();
  }
  s.scratch_ec+=2u;if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0)
   approach_battle_offset(s.offset,0.f,float(projectile_signed(s.scratch_ec))*.0025f);
  if(age==30){s.frame=20;return true;}
  if(age>240)return finish();
  return advance();
 }
 // Registration 80 is a visual lifetime holder: no frame-service callback.
 if(age==0){s.speed=0;s.scratch_e8=0;++s.frame;}
 ++s.scratch_e8;
 if(projectile_signed(s.scratch_e8)<241)return true;
 return finish();
}
} // namespace daybreak
