#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Source handlers 6006b0, 61d920, 61e580, 6251d0 and 631390. Historical item8
// fixtures retain this partial adapter; production dispatch uses the complete
// item8_projectile.hpp switch first. Other item-specific routes remain separate.
inline bool roster_child_family_registration(unsigned item,unsigned registration){
 return (item==8&&(registration==0||registration==60||registration==70||registration==80||
                   registration==90||registration==100||registration==110||
                   registration==120||registration==130))||
        (item==31&&(registration==0||registration==30||registration==60||registration==70))||
        (item==32&&(registration==0||registration==140||registration==150))||
        (item==37&&(registration==0||registration==10||registration==20||registration==120))||
        (item==45&&(registration==0||registration==10||registration==20));
}
template<class Host> bool tick_roster_child_family_projectile(
    KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(!roster_child_family_registration(item,registration))
  throw std::invalid_argument("Unsupported child-family projectile registration");
 const auto age=projectile_signed(s.frame);
 auto contact=projectile_contacts(s);
 auto finish=[&](){s.released=true;return false;};
 if(item==8&&registration==0){
  if(age==0){s.speed=30.f;s.capacity.fill(1);s.scale.fill(.5f);normal_projectile_direct_velocity(s);}
  approach_battle_offset(s.offset,0.f,.1f);
  s.velocity[1]-=.3f;
  if(host.stage_collision(s)==1&&s.velocity[1]<0){s.velocity[1]=-s.velocity[1];if(s.velocity[1]>6.f)s.velocity[1]=6.f;}
  if(age>90||contact!=0){host.effect(s,105);host.child(s,8,0,0,false);return finish();}
 }else if(item==8&&(registration==60||registration==70||registration==80||registration==130)){
  if(age==0){s.speed=0;s.scale.fill(.5f);s.capacity.fill(registration==70?0:1);s.velocity[1]=0;}
  if(age>51)return finish();
 }else if(item==8&&registration==90){
  // 6006b0 case 5a: a falling seed rests on stage contact, then blooms.
  if(age==0){s.speed=35.f;normal_projectile_direct_velocity(s);s.capacity.fill(1);s.scratch_e8=0;}
  if(s.scratch_e8==0){s.velocity[1]-=.75f;s.rotation[2]+=20.f;}
  if(s.scratch_e8==0&&host.stage_collision(s)==1){
   s.rotation[2]=0;s.pitch=0;s.speed=0;s.velocity.fill(0);s.scratch_e8=1;
  }
  if(projectile_signed(s.scratch_e8)>0){
   ++s.scratch_e8;
   if(s.scratch_e8==90){host.sound(s,108);host.child(s,10,0,40.f,false);}
   if(s.scratch_e8==300)return finish();
  }
  if(age>1800)return finish();
 }else if(item==8&&registration==100){
  // The seed's child expands into a contact volume and fades after 150 ticks.
  if(age==0){
   s.scale.fill(0);s.speed=0;s.pitch=0;s.velocity[1]=0;
   s.scratch_e8=255;s.scratch_ec=0;s.capacity.fill(0);
   normal_projectile_direct_velocity(s);
  }
  if(s.scratch_ec==0){
   if(s.scale[0]>=1.f){s.scale.fill(1.f);s.scratch_ec=1;s.capacity.fill(5);}
   else for(auto& axis:s.scale)axis+=.05f;
  }
  if(projectile_signed(s.scratch_ec)>0){
   if(s.scratch_ec%10==0)s.contacts.fill(0);
   ++s.scratch_ec;
  }
  if(projectile_signed(s.scratch_ec)>150){
   s.capacity.fill(0);s.scratch_e8-=15;
   if(projectile_signed(s.scratch_e8)<0)return finish();
  }
  host.alpha(s,s.scratch_e8&255u);
 }else if(item==8&&(registration==110||registration==120)){
  if(contact&0x100){reflect_normal_projectile(s);contact=projectile_contacts(s);}
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   s.scale.fill(2.f);s.speed=10.f;host.trail(s,2,10.f,20,1,0);
   s.capacity.fill(1);s.scratch_e8=0;
  }
  s.speed+=registration==110?1.5f:2.25f;
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.05f);
   const float elevation=host.target_elevation(s);
   if(s.pitch-elevation>3.f)s.pitch-=.05f;
   if(s.pitch-elevation< -3.f)s.pitch+=.05f;
  }
  if(age>90||contact!=0||host.stage_collision(s)==1){
   host.child(s,7,0,0,false);host.sound(s,105);return finish();
  }
 }else if((item==31&&(registration==0||registration==30))||(item==32&&registration==0)){
  if(contact&0x100){reflect_normal_projectile(s);contact=projectile_contacts(s);}
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f)s.pitch=target;
    if(s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=item==31?(registration==30?60.f:42.5f):35.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_f0=0;
   host.trail(s,item==31&&registration==30?2u:0u,item==31?60.f:50.f,10,1,0);
   if(item==31)host.visual_child(s,7);
  }
  s.scratch_f0=std::min(item==31?60u:100u,s.scratch_f0+1);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float turn=float(projectile_signed(s.scratch_f0))*(item==31?(registration==30?.02f:.01f):.002f);
   approach_battle_offset(s.offset,0.f,turn);
   const float target=host.target_elevation(s);
   const float elevation=float(projectile_signed(s.scratch_f0))*(item==31?(registration==30?.02f:.01f):.0005f);
   if(s.pitch-target>1.f)s.pitch-=elevation;
   if(s.pitch-target< -1.f)s.pitch+=elevation;
  }
  if(item==31&&contact!=0){host.sound(s,214);return finish();}
  if(age>240||host.stage_collision(s)==1||contact!=0){
   if(item==32){host.visual_child(s,14);host.visual_child(s,15);}
   return finish();
  }
 }else if(item==31&&(registration==60||registration==70)){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);s.scale.fill(.05f);s.speed=0;}
  const float step=legacy_trig(float(age*3),false)*.025f;
  for(auto& axis:s.scale)axis+=step;
  if(age>6){const int alpha=projectile_signed(s.scratch_e8)-10;
   if(alpha<0){s.scratch_e8=0;return finish();}s.scratch_e8=unsigned(alpha);}
  host.alpha(s,s.scratch_e8&255u);
 }else if(item==32&&registration==140){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);
   s.speed=0;s.scale[0]=1.f;s.scale[2]=2.f;}
  s.scale[0]=std::max(0.f,s.scale[0]-.05f);
  if(age>10){const int alpha=projectile_signed(s.scratch_e8)-20;
   if(alpha<0){s.scratch_e8=0;return finish();}s.scratch_e8=unsigned(alpha);}
  const unsigned a=s.scratch_e8&255u;host.color(s,a,a,a,255);
 }else if(item==32&&registration==150){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);s.speed=0;}
  s.scale.fill(1.f+legacy_trig(float(age*4),true));
  if(age>3){const int alpha=projectile_signed(s.scratch_e8)-20;
   if(alpha<0){s.scratch_e8=0;return finish();}s.scratch_e8=unsigned(alpha);}
  const unsigned a=s.scratch_e8&255u;host.color(s,a,a,a,255);
 }else if(item==37&&(registration==0||registration==10||registration==20)){
  if(age==0){s.speed=30.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  const int state=host.owner_state(s);
  if((state>103&&state<200)||(state>203&&state<300)||age>300){
   host.visual_child(s,13);return finish();
  }
  if(age<30)s.speed=std::max(2.f,s.speed-2.f);
  else{
   s.speed=60.f;
   // 6251d0 cases 0/10/20 share their launch and owner-interrupt logic.
   // The two charged variants converge on opposite 45-degree offsets.
   approach_battle_offset(s.offset,registration==10?-45.f:registration==20?45.f:0.f,180.f);
   s.pitch=host.target_elevation(s);
   if(age==60)host.trail(s,0,30.f,60,1,0);
   if(age%40==0)host.effect(s,99);
   if(host.target_distance_squared(s)<360000.f){host.child(s,12,0,0,false);return finish();}
  }
 }else if(item==37&&registration==120){
  if(age==0){s.speed=0;s.scratch_e8=s.scratch_ec=0;s.scratch_f0=180;}
  const int state=host.owner_state(s);
  if((state>103&&state<200)||(state>203&&state<300)){
   host.visual_child(s,13);return finish();
  }
  if(age<15){approach_battle_offset(s.offset,0.f,180.f);s.pitch=host.target_elevation(s);}
  if(age==15){host.effect(s,80);host.child(s,3,0,0,false);}
  if(age==120){host.retarget_owner(s);host.visual_child(s,13);return finish();}
 }else if(item==45&&registration==0){
  if(contact&0x100){reflect_normal_projectile(s);contact=projectile_contacts(s);}
  if(age==0){
   const float target=host.target_elevation(s);
   if(s.pitch-target<10.f&&s.pitch-target> -10.f)s.pitch=target;
   else if(s.pitch-target>=10.f)s.pitch-=10.f;
   else s.pitch+=10.f;
   approach_battle_offset(s.offset,0.f,5.f);
   s.scratch_e8=0;host.visual_child(s,2);s.speed=80.f;s.capacity.fill(1);
  }
  if(s.scratch_e8==0&&(contact!=0||host.stage_collision(s)==1||age>180)){
   s.scratch_e8=1;s.speed=0;
  }
  if(s.scratch_e8==1){for(auto& axis:s.scale)axis-=.1f;
   if(s.scale[0]<0)return finish();}
 }else if(item==45&&registration==10){
  if(contact&0x100){reflect_normal_projectile(s);contact=projectile_contacts(s);}
  if(age==0){
   const float target=host.target_head_elevation(s);
   const float delta=s.pitch-target;
   if(delta<10.f&&delta> -10.f)s.pitch=target;
   else if(delta>=10.f)s.pitch-=10.f;
   else s.pitch+=10.f;
   approach_battle_offset(s.offset,0.f,5.f);
   s.scratch_e8=0;host.visual_child(s,2);s.speed=150.f;s.capacity.fill(1);
  }
  if(s.scratch_e8==0){
   if(age%5==0)host.visual_child(s,10);
   if(contact!=0||host.stage_collision(s)==1||age>180){s.scratch_e8=1;s.speed=0;}
  }
  if(s.scratch_e8==1){for(auto& axis:s.scale)axis-=.1f;
   if(s.scale[0]<0)return finish();}
 }else if(item==45&&registration==20){
  s.speed=0;if(age>5)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
