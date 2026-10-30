#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// Full original switches: Ohishi0 006020f0 and Irie0 00605d60.
inline bool item9_projectile_registration(unsigned item,unsigned registration){
 return item==9&&registration<=100&&registration%10==0;
}
inline bool item13_projectile_registration(unsigned item,unsigned registration){
 return item==13&&registration<=190&&registration%10==0;
}
template<class Host> void item9_13_birth_aim(KeiichiNormalProjectile& s,Host& host){
 const auto state=host.target_state(s);
 if((state>117&&state<122)||state==221){
  if(s.pitch-host.target_elevation(s)<10.f)s.pitch=host.target_elevation(s);
  if(s.pitch-host.target_elevation(s)>-10.f)s.pitch=host.target_elevation(s);
 }
}
template<class Host> void item9_13_pitch_step(KeiichiNormalProjectile& s,Host& host,float threshold,float step){
 if(s.pitch-host.target_elevation(s)>threshold)s.pitch-=step;
 if(s.pitch-host.target_elevation(s)<-threshold)s.pitch+=step;
}

template<class Host> bool tick_item9_projectile(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!item9_projectile_registration(unsigned(s.item),registration))throw std::invalid_argument("Unsupported item9 registration");
 auto finish=[&](){s.released=true;return false;};
 const auto age=projectile_signed(s.frame);
 if((registration==0||registration==30||registration==60)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(registration==0||registration==30){
  if(age==0){
   if(registration==30)host.trail(s,0,60.f,15,1,0);
   s.speed=registration==0?42.5f:62.5f;s.capacity.fill(1);
   s.scratch_e8=s.scratch_f0=s.scratch_f4=0;s.scale[1]=s.scale[2]=registration==0?2.f:4.f;
   approach_battle_offset(s.offset,0.f,5.f);item9_13_birth_aim(s,host);
  }
  ++s.scratch_f0;if(projectile_signed(s.scratch_f0)>120)s.scratch_f0=120;
  if(s.offset>90.f||s.offset<-90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,registration==0?.15f:.2f);
   item9_13_pitch_step(s,host,1.f,.1f);
  }
  const auto contact=projectile_contacts(s);
  if(projectile_signed(s.scratch_f0)>119||(contact!=0&&contact!=1)||host.stage_collision(s)==1)s.scratch_f4=1;
  if(s.scratch_f4==1){
   s.speed=0;s.capacity.fill(0);s.scale[0]-=.15f;s.scale[1]-=.2f;s.scale[2]-=.2f;
   if(s.scale[0]<=0.f)return finish();
  }
 }else if(registration==10||registration==40){
  if(age==0){s.speed=40.f;s.capacity.fill(1);s.scratch_e8=0;}
  if(age==1){normal_projectile_direct_velocity(s);s.velocity[1]=10.f;}
  s.velocity[1]-=registration==10?.75f:.5f;
  if(registration==10)s.speed=std::max(15.f,s.speed-.5f);
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0){
   host.child_position(s,registration==10?2:5,0,0,0);host.child_position(s,7,0,0,0);host.sound(s,115);return finish();
  }
  if(age>1800)return finish();
 }else if(registration==20||registration==50){
  if(age==0){s.speed=0;s.capacity.fill(1);s.scratch_e8=0;s.scale.fill(registration==20?4.f:8.f);}
  if(age==4){s.speed=0;s.capacity.fill(0);return finish();}
  for(auto& axis:s.scale)axis-=registration==20?.4f:.8f;
  if(s.scale[2]<=0.f)return finish();
 }else if(registration==60){
  if(age==0){s.speed=45.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scale.fill(2.f);}
  ++s.scratch_ec;if(projectile_signed(s.scratch_ec)>75)s.scratch_ec=75;
  if(s.offset>90.f||s.offset<-90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){approach_battle_offset(s.offset,0.f,.2f);item9_13_pitch_step(s,host,1.f,.2f);}
  if(age>240||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   if(projectile_contacts(s)&1)host.child_position(s,10,0,0,0);
   return finish();
  }
 }else if(registration==70){
  if(age==0){s.scale.fill(.5f);s.speed=0;s.capacity.fill(1);s.scratch_e8=255;}
  const float growth=legacy_trig(float(projectile_signed(s.frame<<2)),false)*.2f;
  for(auto& axis:s.scale)axis+=growth;
  if(age>0){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  if(age>20)return finish();host.alpha(s,s.scratch_e8&255u);
 }else if(registration==80){
  if(age==0){s.speed=0;s.capacity.fill(1);s.scratch_e8=0;s.scale={7.f,12.f,7.f};}
  if(age==30){s.speed=0;s.capacity.fill(0);return finish();}
 }else if(registration==100){
  if(age==0){s.scale.fill(1.5f);s.speed=0;host.bind_model_root_bone(s,"Bip00");}
  if(age==300)return finish();
 }
 // Original registration90 has no explicit case and only advances.
 ++s.frame;host.advance_frame(s);return true;
}

template<class Host> bool tick_item13_projectile(KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 if(!item13_projectile_registration(unsigned(s.item),registration))throw std::invalid_argument("Unsupported item13 registration");
 auto finish=[&](){s.released=true;return false;};
 const auto age=projectile_signed(s.frame);
 const bool straight=registration==0||registration==10||registration==90||registration==160||registration==170;
 if((straight||registration==100)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(straight){
  if(age==0){
   if(registration!=90)item9_13_birth_aim(s,host);
   if(registration==10||registration==90||registration==170)host.trail(s,0,10.f,20,1,0);
   s.speed=registration==0?35.f:registration==10?55.f:registration==170?60.f:40.f;s.capacity.fill(1);
  }
  if(registration==90)s.speed=std::min(70.f,s.speed+.5f);
  const auto contact=projectile_contacts(s);
  if((registration==10||registration==170)&&(contact&0x80)){host.child_position(s,14,0,0,0);host.sound(s,160);}
  const int expiry=registration==0||registration==160?180:240;
  if(age>expiry||contact!=0||host.stage_collision(s)==1){
   if((registration==0||registration==90||registration==160)&&(contact&0x80)){host.child_position(s,14,0,0,0);host.sound(s,160);}
   return finish();
  }
 }else if(registration==20||registration==30||registration==180||registration==190||registration==100){
  const bool stream=registration==30||registration==190;
  if(age==0){
   if(registration!=100){
    item9_13_birth_aim(s,host);
    if(!stream){host.particle_offset(s,15,0,0,0);approach_battle_offset(s.offset,0.f,5.f);}
   }
   s.scale.fill(4.f);s.speed=registration==100?42.5f:45.f;s.scratch_e8=0;s.scratch_ec=stream?60:40;s.capacity.fill(1);
   if(stream)host.trail(s,0,30.f,30,1,0);
   if(registration==100)host.trail(s,0,30.f,10,1,0);
  }
  ++s.scratch_ec;if(projectile_signed(s.scratch_ec)>(stream?120:100))s.scratch_ec=stream?120:100;
  if(registration==100)s.speed=std::min(70.f,s.speed+.5f);
  if(stream&&age%5==0)host.particle_offset(s,15,0,0,0);
  if(s.offset>90.f||s.offset<-90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float counter=float(projectile_signed(s.scratch_ec));
   const float turn=registration==20?.0035f:registration==30?.006f:registration==100?.003f:registration==180?.065f:.075f;
   const float pitch=registration==20||registration==30?.005f:registration==100?.003f:registration==180?.075f:.01f;
   approach_battle_offset(s.offset,0.f,counter*turn);item9_13_pitch_step(s,host,3.f,counter*pitch);
  }
  if(age>240||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   if(registration==100)host.child_position(s,11,0,0,0);
   else{host.sound(s,160);host.child_position(s,6,0,0,0);if(age<241)host.child_position(s,7,0,0,0);}
   return finish();
  }
 }else if(registration==50){
  if(age==0){s.speed=10.f;s.offset=float(host.random_word()%360u);s.pitch=float(host.random_word()%360u);}
  for(auto& axis:s.scale)axis-=.1f;
  if(s.scale[2]<=0.f)return finish();
 }else if(registration==60||registration==110){
  if(registration==110&&age==0)s.capacity.fill(1);
  if(age>51)return finish();
 }else if(registration==70||registration==130){
  if(registration==130)s.position=host.owner_position(s);
  s.pitch=0;s.rotation[0]+=1.f;
  if(age==0){s.scale[0]=s.scale[2]=0;if(registration==130)s.scratch_f8=0;}
  if(s.scale[2]>=6.f)s.scale[0]=s.scale[2]=6.f;
  else{const float growth=legacy_trig(float(projectile_signed(s.frame*3u)),true)*.4f;s.scale[0]+=growth;s.scale[2]+=growth;}
  if(age%5==0){s.capacity.fill(1);s.contacts.fill(0);}
  if(age%10==0){
   const float z=float(host.random_word()%800u)-400.f,x=float(host.random_word()%800u)-400.f;
   host.particle_offset(s,8,x,0,z);
  }
  if(registration==130&&host.owner_state(s)==370&&host.owner_animation_frame(s)==0)s.scratch_f8=1;
  if(age<(registration==70?241:301)&&(registration==70||projectile_signed(s.scratch_f8)<1))
   s.scale[1]=legacy_trig(float(projectile_signed(s.frame*6u)),true)*.25f+.75f;
  else{s.capacity.fill(0);s.scale[1]-=.1f;if(s.scale[1]<=0.f)return finish();}
 }else if(registration==80){
  if(age==0){s.scale.fill(.5f);s.speed=float(host.random_word()%20u)*.1f+2.f;s.rotation[1]=float(host.random_word()%360u);s.pitch=90.f;}
  s.rotation[1]+=2.f;if(age>59)return finish();
 }else if(registration==120){
  if(age==0){s.scale.fill(.5f);s.scratch_e8=255;}
  const float growth=legacy_trig(float(projectile_signed(s.frame*3u)),false)*.1f;
  for(auto& axis:s.scale)axis+=growth;
  if(age==6)s.capacity.fill(0);
  if(age>2){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
  host.alpha(s,s.scratch_e8&255u);
  if(age%5==0){const float z=float(host.random_word()%200u)-100.f,x=float(host.random_word()%200u)-100.f;host.particle_offset(s,8,x,0,z);}
  if(age>30)return finish();
 }else if(registration==140){
  s.pitch=0;s.rotation[0]+=1.f;if(age==0)s.scale.fill(.5f);
  if(age%5==0){const float z=float(host.random_word()%200u)-100.f,x=float(host.random_word()%200u)-100.f;host.particle_offset(s,8,x,0,z);}
  if(age>0){s.capacity.fill(0);s.scale[1]-=.025f;s.scale[0]+=.05f;s.scale[2]+=.05f;if(s.scale[1]<=0.f)return finish();}
 }else if(registration==150){
  if(age==0)s.scale.fill(.15f);s.speed=0;
  const float growth=legacy_trig(float(projectile_signed(s.frame*3u)),false)*.05f;
  for(auto& axis:s.scale)axis+=growth;
  if(age>28)return finish();
 }
 // Original registration40 has no explicit script branch.
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
