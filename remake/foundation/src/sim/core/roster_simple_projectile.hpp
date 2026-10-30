#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <stdexcept>

namespace daybreak {
// Registration-zero scripts grouped by their shared birth and terminal rules.
// Source VAs: 5fbf20, 605750, 605d60, 607b50, 6085e0, 6095c0,
// 616810, 619ad0, 61adb0, 620290, 628a50, 62e5d0, 62f180, 6305b0.
// Other registrations stay separate.
inline bool roster_simple_projectile_item(unsigned item){
 switch(item){case 3:case 12:case 13:case 14:case 15:case 16:case 23:
              case 27:case 28:case 33:case 39:case 42:case 43:case 44:return true;
             default:return false;}
}
inline bool roster_simple_projectile_registration(unsigned item,unsigned registration){
 return (registration==0&&roster_simple_projectile_item(item))||
        (item==16&&registration==20)||(item==27&&(registration==10||registration==30))||
        (item==42&&(registration==10||registration==30))||
        (item==44&&registration==70);
}
template<class Host> bool tick_roster_simple_projectile(KeiichiNormalProjectile& s,Host& host,unsigned registration=0){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(!roster_simple_projectile_registration(item,registration))
  throw std::invalid_argument("Unsupported simple roster projectile registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 if(item==44&&registration==70){ // Original 6305b0 case 0x46.
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){s.speed=75.f;s.capacity.fill(1);s.scratch_e8=0;}
  if(age>180||projectile_contacts(s)!=0||host.stage_collision(s)==1)return finish();
  ++s.frame;host.advance_frame(s);return true;
 }
 if(item==27&&registration==30){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);}
  if(age>4){
   const int alpha=projectile_signed(s.scratch_e8)-50;
   if(alpha<0){s.scratch_e8=0;return finish();}
   s.scratch_e8=unsigned(alpha);
  }
  host.alpha(s,s.scratch_e8&255u);
  ++s.frame;host.advance_frame(s);return true;
 }
 if(item==16&&registration==20){ // 6095c0 case 0x14: fast shot, then shrinking tail.
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   s.scratch_e8=0;s.speed=50.f;s.capacity.fill(1);s.scale.fill(1.5f);
  }
  if(host.stage_collision(s)==1||age>25){
   s.capacity.fill(0);for(auto& axis:s.scale)axis-=.1f;
   if(s.scale[2]<0.f)return finish();
  }
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,.25f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=.1f;
   if(s.pitch-target< -1.f)s.pitch+=.1f;
  }
  ++s.frame;host.advance_frame(s);return true;
 }
 if(item==27&&registration==10){ // 619ad0 case 0x0a: enhanced shot.
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   approach_battle_offset(s.offset,0.f,5.f);
   s.scale={1.5f,.5f,.5f};s.speed=65.f;s.capacity.fill(1);
  }
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){host.child(s,3,0,0,false);return finish();}
  if(age>180)return finish();
  ++s.frame;host.advance_frame(s);return true;
 }
 if(item==23||item==39)return finish();
 if(item==3||item==33){
  if(age==0){s.speed=0;s.velocity[1]=0;s.capacity.fill(1);if(item==33)s.scale.fill(3.f);}
  if(age>(item==3?51:30))return finish();
 }else if(item==12||item==42){
  if(item==42&&registration==0)host.collision_geometry(s);
  if(age==0){s.speed=1;s.capacity.fill(1);s.scratch_e8=0;s.scale.fill(2.f);}
  if(age==4){s.speed=0;s.capacity.fill(0);return finish();}
  if(item==42&&registration==0&&age>0&&projectile_contacts(s)!=0&&s.scratch_e8==0){
   const float radius=host.collision_radius(s);
   if(host.target_distance_squared(s)<radius*radius){
    auto child=s;child.position=host.target_position(s);child.position[1]+=100.f;
    host.child(child,1,0,0,false);++s.scratch_e8;
   }
  }
  for(auto& axis:s.scale)axis-=.4f;
  if(s.scale[2]<0.f)return finish();
 }else if(item==15){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){s.scale={1.f,.6f,.6f};s.speed=40.f;s.capacity.fill(1);}
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){host.visual_child(s,3);return finish();}
  s.speed-=.25f;
  if(age>60)return finish();
 }else if(item==16||item==28){
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){
   if(item==16){
    const int state=host.target_state(s);
    if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   }
   s.scratch_e8=0;s.speed=item==16?35.f:60.f;s.capacity.fill(1);
   if(item==28)s.scale={1.f,3.f,1.f};
  }
  if(host.stage_collision(s)==1||age>(item==16?30:10)){
   s.capacity.fill(0);
   if(item==16){for(auto& axis:s.scale)axis-=.1f;if(s.scale[2]<=0.f)return finish();}
   else{s.scale[0]-=.2f;s.scale[1]-=1.f;s.scale[2]-=.2f;if(s.scale[1]<=0.f)return finish();}
  }
  if((s.offset>90.f||s.offset< -90.f))s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0.f,.25f);
   const float target=host.target_elevation(s);
   const float threshold=item==28?3.f:1.f;
   if(s.pitch-target>threshold)s.pitch-=.1f;
   if(s.pitch-target< -threshold)s.pitch+=.1f;
  }
 }else{
  if(projectile_contacts(s)&0x100)reflect_normal_projectile(s);
  if(age==0){
   if(item!=27){
    const int state=host.target_state(s);
    if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   }else{
    const int state=host.target_state(s);
    if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
    approach_battle_offset(s.offset,0.f,5.f);s.scale={6.f,1.f,1.f};
   }
   s.speed=item==13?35.f:item==43?55.f:45.f;
   s.capacity.fill(1);
   if(item==14||item==44)s.scratch_e8=0;
  }
  const auto contact=projectile_contacts(s);
  const bool blocked=contact!=0&&(item!=14||contact!=1);
  const int expiry=item==14?60:180;
  if(item==27){
   if(blocked||host.stage_collision(s)==1){host.child(s,3,0,0,false);return finish();}
   if(age>expiry)return finish();
  }else if(age>expiry||blocked||host.stage_collision(s)==1)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
