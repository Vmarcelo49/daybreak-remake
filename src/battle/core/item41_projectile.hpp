#pragma once
#include "item11_22_projectiles.hpp"
namespace daybreak {
// Takano2: complete original0062b830 switch. The three sparse DAT groups
// are registrations, rather than indices in the owner's57-slot bullet table.
inline bool item41_projectile_registration(unsigned item,unsigned reg){
 return item==41&&reg%10==0&&(reg<=240||(reg>=300&&reg<=360)||(reg>=400&&reg<=460)||(reg>=500&&reg<=560));
}
template<class Host> void item41_birth_aim(KeiichiNormalProjectile& s,Host& host){
 const auto state=host.target_state(s);
 if((state>=118&&state<=121)||state==221){
  // These unusual inequalities are present in the original machine code.
  if(s.pitch-host.target_elevation(s)<10)s.pitch=host.target_elevation(s);
  if(-10<s.pitch-host.target_elevation(s))s.pitch=host.target_elevation(s);
 }
}
template<class Host> void item41_aim_angles(KeiichiNormalProjectile& s,Host& host){
 const auto aim=host.owner_aim(s);
 const float x=s.position[0]-aim[0],y=s.position[1]-aim[1],z=s.position[2]-aim[2];
 // The original rounds the squared X component, then the X/Z sum to float
 // before sqrt, and stores both angles before constructing the direction.
 const float sum=float(double(z)*z+float(double(x)*x));
 s.turn_rate=float(std::sqrt(double(sum)));
 s.orbit_angle=float(std::atan2(double(y),double(s.turn_rate))/3.1415927410125732421875*180.0);
 s.orbit_radius=float(std::atan2(double(x),double(z))/3.1415927410125732421875*180.0);
}
template<class Host> void item41_owner_shot(KeiichiNormalProjectile& s,Host& host,unsigned slot,float yaw_offset=0,float pitch_offset=0){
 host.owner_controller_shot(s,slot,host.owner_aim(s),90-s.orbit_radius+yaw_offset,s.orbit_angle+pitch_offset);
}
template<class Host> bool tick_item41_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item41_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item41 registration");
 const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if((reg==0||reg==10||reg==40||reg==140)&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 auto birth=[&](float speed,bool aim=true){if(aim)item41_birth_aim(s,host);s.speed=speed;s.scratch_e8=s.scratch_f0=s.scratch_f4=s.scratch_f8=0;s.scratch_ec=40;s.capacity.fill(1);};
 auto impact=[&](unsigned slot){if(s.contacts.at(s.target)==0)host.target_refresh(s);host.child_position(s,slot,0,0,0);return finish();};
 if(reg==0||reg==10){
  if(age==0)birth(reg==0?65.f:75.f);
  if(age==1){normal_projectile_direct_velocity(s);s.pitch=0;}
  if(reg==0||s.scratch_f8==0){
   s.velocity[1]-=.1f;approach_battle_offset(s.offset,0,reg==0?.1f:.2f);
   if(projectile_contacts(s)!=0){if(reg==0)s.capacity.fill(0);return impact(reg==0?17:19);}
   if(host.stage_collision(s)==1){host.child_position(s,reg==0?16:18,0,0,0);return finish();}
  }
  if(age>180)return finish();
 }else if(reg==20){if(age==0)s.capacity.fill(1);s.speed=0;if(age>14)return finish();}
 else if(reg==30){
  if(age==0){item41_birth_aim(s,host);s.speed=120;s.capacity.fill(1);}
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1){host.child_position(s,2,0,0,0);return finish();}if(age>240)return finish();
 }else if(reg==40||reg==140){
  if(age==0)birth(60);
  if(s.scratch_f8==0){if(projectile_contacts(s)!=0)return impact(21);if(host.stage_collision(s)==1){host.child_position(s,20,0,0,0);return finish();}}
  if(age>150)return finish();
 }else if(reg==50||reg==130){
  if(age==0){s.speed=40;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;}
  s.scratch_ec+=reg==50?3u:1u;const int limit=reg==50?60:100;if(projectile_signed(s.scratch_ec)>limit)s.scratch_ec=unsigned(limit);
  if(age%2==0)host.particle_offset(s,7,0,0,0);if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(reg==50&&s.scratch_e8==0&&age>0){const float step=float(projectile_signed(s.scratch_ec))*.0075f;approach_battle_offset(s.offset,0,step);item9_13_pitch_step(s,host,3,step);}
  if(age>480||projectile_contacts(s)!=0||host.stage_collision(s)!=0){host.child_position(s,6,0,0,0);host.sound(s,74);return finish();}
 }else if(reg==60){if(age==0){s.speed=0;s.velocity[1]=0;s.scale.fill(1);s.capacity.fill(1);}if(age>51)return finish();}
 else if(reg==70){if(age>29)return finish();}
 else if(reg==80){if(age==0){birth(60);normal_projectile_direct_velocity(s);}s.velocity[1]-=.4f;if(host.stage_collision(s)==1){host.child_position(s,22,0,0,0);return finish();}if(age>150)return finish();}
 else if(reg==90){if(age==0){s.scale={1.5f,3,3};s.speed=.01f;s.scratch_e8=s.scratch_ec=0;s.capacity.fill(1);}++s.scratch_e8;s.scratch_ec+=2;if(age==41)return finish();}
 else if(reg==110||reg==150){
  if(age==0){s.speed=250;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=s.scratch_f4=0;}
  if(reg==110){approach_battle_offset(s.offset,0,.1f);item9_13_pitch_step(s,host,1,.1f);}
  if(projectile_contacts(s)!=0||host.stage_collision(s)!=0){host.particle_offset(s,12,0,0,0);return finish();}if(age==120)return finish();
 }else if(reg==120){if(age==0)s.scale.fill(.05f);s.speed=0;item11_22_wave(s,float(projectile_signed(s.frame*3u)),.5f);if(age>28)return finish();}
 else if(reg>=160&&reg<=220){
  if(age==0){s.scratch_f4=s.scratch_f8=0;s.speed=0;if(reg>=200)s.pitch=0;if(reg==220){s.scratch_e8=s.scratch_f0=0;s.scratch_ec=40;}}
  if(reg==170||reg==190||reg==210){
   s.rotation[0]+=5;if(s.scale[0]<=.5f)s.scale.fill(.5f);else for(auto& axis:s.scale)axis-=.5f;
   s.position=host.target_position(s);s.position[1]+=85;
  }
  const auto counter=projectile_signed(s.scratch_f4);const int cadence=reg==180||reg==190?30:60;
  if(counter%cadence==0)host.sound(s,195);
  if(reg==160||reg==180){
   if(counter%2==0&&counter>=0&&counter<(reg==160?56:61)){
    item41_aim_angles(s,host);const auto spread=reg==160?16u:4u;const float pitch=float(int(host.random_word()%spread)-int(spread/2));
    const float yaw=float(int(host.random_word()%spread)-int(spread/2));
    item41_owner_shot(s,host,3,yaw+(reg==180?float(counter-60)-30:0.f),pitch);
   }
   if(counter==60)s.scratch_f8=4;
  }else if(reg==220){
   if(counter>59&&counter%10==0)host.child_offset(s,9,0,10000,0,0,-s.pitch-90);
   if(counter>120)return finish();
  }else if(counter==(reg==200?60:180)){
   item41_aim_angles(s,host);item41_owner_shot(s,host,reg==170?11:reg==190?15:reg==200?13:5);s.scratch_f8=4;
  }
  ++s.scratch_f4;if(reg!=220&&s.scratch_f8==4)return finish();
 }else if(reg==230){
  s.position=host.owner_position(s);s.pitch=0;s.rotation[0]+=1;
  if(age==0){s.scale[0]=s.scale[2]=0;s.scratch_f8=0;}
  if(s.scale[2]>=2)s.scale[0]=s.scale[2]=3;else{s.scale[0]+=legacy_trig(float(projectile_signed(s.frame*3u)),true)*.15f;s.scale[2]+=legacy_trig(float(projectile_signed(s.frame*3u)),true)*.15f;}
  if(age%5==0){s.capacity.fill(1);s.contacts.fill(0);}
  if(age%10==0){const float z=float(int(host.random_word()%300u)-150),x=float(int(host.random_word()%300u)-150);host.particle_offset(s,24,x,0,z);}
  if(host.owner_state(s)==370&&host.owner_phase(s)==0)s.scratch_f8=1;
  if(age<301&&projectile_signed(s.scratch_f8)<1)s.scale[1]=legacy_trig(float(projectile_signed(s.frame*6u)),true)*.25f+.75f;
  else{s.capacity.fill(0);s.scale[1]-=.1f;if(s.scale[1]<=0)return finish();}
 }else if(reg==240){if(age==0){s.speed=float(host.random_word()%20u)*.1f+2;s.pitch=90;}if(age>59)return finish();}
 else if(reg>=300&&reg<=360){
  if(age==0){birth(60);normal_projectile_direct_velocity(s);}s.velocity[1]-=.1f;
  if(s.scratch_f8==0){if(projectile_contacts(s)!=0)return impact(50+(reg-300)/10);if(host.stage_collision(s)==1){host.child_position(s,40+(reg-300)/10,0,0,0);return finish();}}
  if(age>120)return finish();
 }else if(reg>=400&&reg<=460){
  if(age==0){s.scratch_f4=s.scratch_f8=0;s.speed=0;s.pitch=0;}
  const auto counter=projectile_signed(s.scratch_f4);if(counter%60==0)host.sound(s,195);
  if(counter==int(reg-400)){item41_aim_angles(s,host);item41_owner_shot(s,host,13);}
  ++s.scratch_f4;if(projectile_signed(s.scratch_f4)>59)return finish();
 }else if(reg>=500&&reg<=560){
  if(age==0){s.scratch_f4=s.scratch_f8=0;s.speed=0;s.pitch=0;}
  s.rotation[0]+=5;if(s.scale[0]<=.5f)s.scale.fill(.5f);else for(auto& axis:s.scale)axis-=.5f;
  s.position=host.target_position(s);s.position[1]+=85;
  const auto counter=projectile_signed(s.scratch_f4);if(counter%60==0)host.sound(s,195);
  if(counter==int(reg*2-820)){item41_aim_angles(s,host);item41_owner_shot(s,host,5);s.scratch_f8=4;}
  ++s.scratch_f4;if(s.scratch_f8==4)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
// Original54ef50 initialization and54efb0 slot7 prefix. Hitstop does not gate
// this prefix; the owner root, rather than pad direction, drives the spring.
inline void initialize_item41_owner_aim(std::array<float,3>& aim,std::array<float,2>& velocity,const std::array<float,3>& position){aim=position;aim[1]+=2500;velocity.fill(0);}
inline void advance_item41_owner_aim(std::array<float,3>& aim,std::array<float,2>& velocity,const std::array<float,3>& position){
 for(unsigned n=0;n<2;++n){const unsigned axis=n*2;
  if(position[axis]<aim[axis]){velocity[n]-=.05f;if(velocity[n]<-4)velocity[n]=-4;}
  if(aim[axis]<position[axis]){velocity[n]+=.05f;if(velocity[n]>4)velocity[n]=4;}
  aim[axis]+=velocity[n];
 }
}
}
