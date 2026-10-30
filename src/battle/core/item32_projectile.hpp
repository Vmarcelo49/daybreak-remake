#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Original 0061e580, character 14 weapon 1. The already recovered child
// family handles registrations 0/140/150; these are the remaining 15 cases.
inline bool item32_projectile_registration(unsigned item,unsigned registration){
 return item==32&&registration<=170&&registration%10==0&&
        registration!=0&&registration!=140&&registration!=150;
}
template<class Host> bool tick_item32_projectile(KeiichiNormalProjectile& s,
                                                  unsigned registration,Host& host){
 if(s.released)return false;
 if(!item32_projectile_registration(unsigned(s.item),registration))
  throw std::invalid_argument("Unsupported item32 registration");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 auto advance=[&](){++s.frame;host.advance_frame(s);return true;};
 const auto contact=projectile_contacts(s);
 if(registration<=50&&contact&0x100)reflect_normal_projectile(s);
 if(registration==10||registration==20){
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   s.speed=registration==10?47.5f:65.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_f0=0;
   host.trail(s,0,60.f,10,1,0);
  }
  s.scratch_f0=std::min(s.scratch_f0+1u,100u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float turn=registration==10?.1f:.5f;
   approach_battle_offset(s.offset,0.f,turn);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=.1f;
   if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=.1f;
  }
  if(age>240||host.stage_collision(s)==1){
   host.visual_child(s,14);host.visual_child(s,15);return finish();
  }
  return advance();
 }
 if(registration==30||registration==40||registration==50){
  if(age==0){
   s.speed=registration==30?50.f:70.f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=s.scratch_f4=s.scratch_f8=0;
   if(registration==30)s.scale.fill(.75f);
   if(registration==50)s.scale.fill(1.25f);
  }
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,registration==30?1.f:1.5f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=.5f;
   if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=.5f;
  }
  if(projectile_contacts(s)&3u){
   s.capacity.fill(0);s.speed=0.f;
   if(registration==30){
    if(s.scratch_f8==0){
     host.visual_child(s,14);host.visual_child(s,15);
     host.child_offset(s,6,0.f,2000.f,0.f,0.f,-s.pitch-90.f);
     host.sound(s,219);return finish();
    }
   }else{
    host.visual_child(s,14);host.visual_child(s,15);
    host.child(s,registration==40?16:17,0,0,false);
    host.sound(s,219);return finish();
   }
  }
  if(age>300||host.stage_collision(s)==1)return finish();
  return advance();
 }
 if(registration==60||registration==70||registration==80){
  if(age==0){
   s.speed=registration==60?90.f:registration==70?75.f:80.f;
   s.capacity.fill(1);
   if(registration==60)s.scale[0]=s.scale[2]=.2f;
  }
  if(age>300||host.stage_collision(s)==1||projectile_contacts(s)!=0){
   host.child(s,9,0,0,false);
   if(registration==60)host.child(s,10,0,0,false);
   host.sound(s,220);return finish();
  }
  return advance();
 }
 if(registration==90){
  if(age==0){s.capacity.fill(1);s.contacts.fill(0);s.scale.fill(.15f);s.scratch_e8=255;}
  const float growth=legacy_trig(float(age*3),false)*.1f;
  for(auto& axis:s.scale)axis+=growth;
  if(age==6)s.capacity.fill(0);
  if(age>5){
   const int alpha=projectile_signed(s.scratch_e8)-13;
   if(alpha<1){s.scratch_e8=0;return finish();}s.scratch_e8=unsigned(alpha);
  }
  const unsigned a=s.scratch_e8&255u;host.color(s,a,a,a,255);
  return advance();
 }
 if(registration==100){
  if(age==0){s.speed=0;s.velocity[1]=0;s.scale.fill(2.f);}
  if(age>30)return finish();
  return advance();
 }
 if(registration==110||registration==130){
  const auto owner_state=host.owner_state(s);
  if(owner_state>349&&owner_state<362){
   const auto owner=host.owner_position(s);
   s.heading=host.owner_heading(s);
   s.offset=host.owner_offset(s);
   if(registration==130)s.offset+=60.f-float(age*6);
   const float angle=s.heading+s.offset;
   s.position={owner[0]+legacy_trig(angle,false)*60.f,owner[1]+70.f,
               owner[2]+legacy_trig(angle,true)*60.f};
  }
  if(age==0){
   s.scale=registration==110?std::array<float,3>{1.f,1.f,1.f}:
                               std::array<float,3>{1.f,.25f,.25f};
   s.speed=registration==110?.01f:0.f;
   s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
   if(registration==110)s.capacity.fill(5);
  }
  if(registration==110&&projectile_contacts(s)!=0&&
     projectile_signed(++s.scratch_f0)>9){s.scratch_f0=0;s.contacts.fill(0);}
  ++s.scratch_e8;s.scratch_ec+=2;
  if(registration==110?age==41:age>20)return finish();
  return advance();
 }
 if(registration==120){
  if(age==0){
   s.scale={1.f,3.f,3.f};s.speed=30.f;s.scratch_e8=255;s.scratch_ec=0;
   s.capacity.fill(1);
  }
  s.scale[1]+=.05f;s.scale[2]+=.05f;
  if(age>26){
   const int alpha=projectile_signed(s.scratch_e8)-20;
   if(alpha<0){s.scratch_e8=0;return finish();}s.scratch_e8=unsigned(alpha);
  }
  const unsigned a=s.scratch_e8&255u;host.color(s,a,a,a,255);
  if(age>41)return finish();
  ++s.frame;return advance(); // Original case 120 increments its frame twice.
 }
 if(registration==160||registration==170){
  s.pitch=0.f;s.rotation[0]+=2.f;
  if(age==0)s.scale[0]=s.scale[2]=0.f;
  const float threshold=registration==160?2.f:3.f;
  const float step=registration==160?.2f:.3f;
  const float growth=s.scale[2]>=threshold?.01f:step;
  s.scale[0]+=growth;s.scale[2]+=growth;
  auto burst=[&](float x,float z){
   host.child_offset(s,6,x,2000.f,z,0.f,-s.pitch-90.f);
  };
  if(age==0){burst(0,0);host.sound(s,219);}
  if(age==10){
   burst(150,0);burst(-150,0);burst(0,150);burst(0,-150);host.sound(s,219);
  }
  if(registration==170&&age==20){
   burst(200,200);burst(-200,200);burst(200,-200);burst(-200,-200);
   host.sound(s,219);
  }
  if(age<61)s.scale[1]=legacy_trig(float(age)*6.f,true)*.1f+1.f;
  else{
   s.capacity.fill(0);s.scale[1]*=.85f;
   s.scale[0]+=.01f;s.scale[2]+=.01f;
   if(s.scale[1]<=.01f)return finish();
  }
  return advance();
 }
 throw std::invalid_argument("Unreachable item32 registration");
}
} // namespace daybreak
