#pragma once
#include "item11_22_projectiles.hpp"
namespace daybreak {
// Full switches 0060a980 (Satoko1) and 00628a50 (Ohishi2).
inline bool item17_projectile_registration(unsigned item,unsigned reg){return item==17&&reg<=240&&reg%10==0;}
inline bool item39_projectile_registration(unsigned item,unsigned reg){return item==39&&reg<=270&&reg%10==0;}
inline void item17_field_growth(KeiichiNormalProjectile& s){
 if(s.scale[0]>=1)s.scale.fill(1);else for(auto& axis:s.scale)axis+=.05f;
}
template<class Host> void item17_rain_pattern(KeiichiNormalProjectile& s,Host& host,unsigned rank){
 const auto counter=projectile_signed(s.scratch_e8);
 if(counter!=1&&counter!=6&&counter!=11)return;
 std::array<float,3> delta;
 if(rank==3){const auto target=host.target_position(s);for(unsigned n=0;n<3;++n)delta[n]=target[n]-s.position[n];host.sound(s,108);}
 else{
  if(counter==1){const auto target=host.target_position(s);s.turn_rate=target[0]-s.position[0];s.orbit_angle=target[1]-s.position[1];s.orbit_radius=target[2]-s.position[2];}
  delta={s.turn_rate,s.orbit_angle,s.orbit_radius};
 }
 const unsigned slot=rank==1?12:rank==2?13:14;const float y=delta[1]+(rank==3?0.f:450.f);
 auto child=[&](float x,float z){host.child_offset(s,slot,x,y,z,0,0);};
 if(counter==1)child(delta[0],delta[2]);
 else if(counter==6){child(delta[0]+80,delta[2]+80);child(delta[0]+80,delta[2]-80);child(delta[0]-80,delta[2]+80);child(delta[0]-80,delta[2]-80);}
 else{child(delta[0]+160,delta[2]+0);child(delta[0]-160,delta[2]-0);child(delta[0]-0,delta[2]+160);child(delta[0]-0,delta[2]-160);}
}
template<class Host> bool tick_item17_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item17_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item17 registration");
 const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if(projectile_contacts(s)&0x100){
  if(reg<=50){s.contacts.fill(0);s.capacity.fill(1);}
  else if(reg==90||reg==100)reflect_normal_projectile(s);
 }
 if(reg<=50){
  if(age==0){host.target_refresh(s);s.speed=0;s.capacity.fill(0);s.contacts.fill(0);s.scratch_e8=0;if(reg>=30)s.scale.fill(0);}
  if(age==60)s.capacity.fill(1);
  if(reg>=30)item17_field_growth(s);
  if(projectile_contacts(s)!=0){
   ++s.scratch_e8;
   if(s.scratch_e8==1){s.scratch_ec=host.field_rank_increment(s);if(s.contacts.at(s.target)==0)host.target_refresh(s);}
   const auto counter=projectile_signed(s.scratch_e8);const unsigned rank=s.scratch_ec;
   if(reg<=10){
    if(rank==1||rank==2){
     const int limit=rank==1?70:90,cadence=rank==1?10:30;
     if(counter<limit)approach_battle_offset(s.offset,0,180);
     if(counter%cadence==0&&counter>10&&counter<limit+1){host.sound(s,rank==1?72:80);host.child_offset(s,rank==1?9:10,0,70,0,0,host.field_target_pitch(s));}
    }else if(rank==3){
     if(counter==1){s.scratch_f0=std::uint32_t(item22_integer_coordinate(host.field_target_pitch(s)));approach_battle_offset(s.offset,0,180);}
     if(counter%15==0&&counter<91){if(counter==15)host.sound(s,82);host.child_offset(s,11,0,70,0,0,float(projectile_signed(s.scratch_f0)));}
    }
    if((rank==1&&counter>70)||((rank==2||rank==3)&&counter>90)){if(s.scale[0]<=0)return finish();for(auto& axis:s.scale)axis-=.05f;}
   }else if(reg<=30){
    if(rank>=1&&rank<=3){item17_rain_pattern(s,host,rank);if(counter>10)return finish();}
   }else if(rank==1||rank==2){
    if(counter==20){host.sound(s,rank==1?110:113);host.child_offset(s,rank==1?15:16,0,70,0,-s.offset,host.field_target_pitch(s));}
    if(counter>70)return finish();
   }else if(rank==3){if(counter==10){host.sound(s,157);host.child_position(s,17,0,0,0);}if(counter>10)return finish();}
  }
  if(age>7200)return finish();
 }else if(reg==60||reg==70){
  if(age==0){s.scale.fill(reg==60?.25f:.5f);s.speed=0;s.capacity.fill(0);s.scratch_e8=0;normal_projectile_direct_velocity(s);s.velocity[1]=0;}
  if(s.scratch_e8==0){s.velocity[1]-=.5f;if(host.stage_collision(s)==1){s.capacity.fill(1);s.velocity.fill(0);s.speed=0;s.scratch_e8=1;}}
  if(age>(reg==60?300:600)||projectile_contacts(s)!=0){if(reg==70){host.sound(s,115);host.child_position(s,8,0,0,0);}return finish();}
 }else if(reg==80||reg==170){
  if(age==0){s.scale.fill(reg==80?.5f:1.5f);s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}if(age>51)return finish();
 }else if(reg==90||reg==100){
  if(age==0){item9_13_birth_aim(s,host);s.speed=50;s.capacity.fill(1);if(reg==100)s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
  if(reg==90){
   if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0){approach_battle_offset(s.offset,0,.01f);item9_13_pitch_step(s,host,3,.01f);}
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1)return finish();if(age>90)return finish();
  }else{
   if((projectile_contacts(s)!=0||host.stage_collision(s)==1)&&((projectile_contacts(s)&2)!=0||host.stage_collision(s)==1))return finish();
   ++s.scratch_ec;++s.scratch_f0;if(projectile_signed(s.scratch_ec)>60)s.scratch_ec=60;
   if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;if(s.scratch_e8==0)approach_battle_offset(s.offset,0,.1f);
   // Cursor is forward-only; this return deliberately skips lifetime and advance.
   if(age==30){s.frame=20;return true;}if(projectile_signed(s.scratch_f0)>180)return finish();
  }
 }else if(reg==110){
  if(age==0){s.scale.fill(1.5f);s.speed=.01f;s.scratch_e8=s.scratch_ec=0;s.capacity.fill(1);}++s.scratch_e8;s.scratch_ec+=2;if(age==41)return finish();
 }else if(reg==120||reg==130){
  if(age==0){if(reg==130){s.scale.fill(1.5f);s.rotation[2]=180;}normal_projectile_direct_velocity(s);s.pitch=0;s.speed=0;s.velocity[1]=-20;s.capacity.fill(1);s.scratch_e8=0;s.contacts.fill(0);}
  s.velocity[1]-=.5f;
  if(reg==120){
   if((projectile_contacts(s)!=0||host.stage_collision(s)==1)&&s.scratch_e8==0){s.capacity.fill(0);s.velocity[1]=5;s.scratch_e8=1;}
   if(projectile_signed(s.scratch_e8)>0){++s.scratch_e8;if(projectile_signed(s.scratch_e8)>120)return finish();}
  }else{
   if(host.stage_collision(s)==1&&s.scratch_e8==0)return finish();if(projectile_contacts(s)!=0&&s.scratch_e8==0)return finish();
   if(projectile_signed(s.scratch_e8)>0){++s.scratch_e8;if(projectile_signed(s.scratch_e8)>300)return finish();}
  }
 }else if(reg==140){
  if(age==0){s.scale.fill(.25f);s.speed=0;s.pitch=0;s.velocity[1]=0;s.scratch_e8=255;s.capacity.fill(1);normal_projectile_direct_velocity(s);}
  for(auto& axis:s.scale)axis+=.02f;s.velocity[1]=20;if(age>15)return finish();
  if(age>5){s.scratch_e8-=25;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}host.alpha(s,s.scratch_e8&255u);
 }else if(reg==150||reg==160){
  if(age==0){s.scale.fill(reg==150?10.f:4.f);if(reg==160)s.speed=60;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
  s.speed=legacy_trig(float(projectile_signed(s.frame*3u)),false)*(reg==150?50.f:60.f);if(age==30)s.capacity.fill(0);if(age==60)return finish();
 }else if(reg==180){
  if(age==0){s.speed=5;s.capacity.fill(1);s.scratch_e8=0;s.scale.fill(1.5f);}if(age==1){normal_projectile_direct_velocity(s);s.velocity[1]=0;}
  if(s.scratch_e8==0)s.velocity[1]-=.5f;
  if(host.stage_collision(s)==1&&s.scratch_e8==0){s.velocity.fill(0);s.speed=0;s.scratch_e8=1;}
  if(age==600){for(unsigned slot:{19u,20u,21u})host.child_position(s,slot,0,0,0);host.sound(s,157);return finish();}
 }else if(reg>=190&&reg<=210){
  if(age==0){s.rotation={0,0,-s.pitch};s.speed=0;s.velocity[1]=0;s.scratch_e8=0;s.scratch_ec=255;if(reg!=210)s.capacity.fill(1);s.scale.fill(reg==190?4.5f:reg==200?6.5f:6.f);}
  const float growth=reg==210?1.f:s.scale[0]>=(reg==190?6.f:10.f)?(reg==190?.005f:.0035f):(reg==190?.5f:.25f);for(auto& axis:s.scale)axis+=growth;
  if(reg!=210){
   ++s.scratch_e8;const auto counter=projectile_signed(s.scratch_e8);
   if(counter>20){s.capacity.fill(0);if(reg==190||counter>30){s.scratch_ec-=5;if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}}
  }else if(age>60){s.capacity.fill(0);s.scratch_ec-=15;if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}
  host.alpha(s,s.scratch_ec&255u);
  // Unlike39/230,200 updates the lifetime/alpha BEFORE rewinding.
  if(reg==200&&age==17){s.frame-=16;return true;}
 }else if(reg>=220){
  if(age==0){s.scratch_f4=s.scratch_f8=0;s.speed=0;s.scale.fill(0);}
  const auto state=host.owner_state(s);if(state!=135&&state!=186)return finish();s.pitch=0;item17_field_growth(s);
  if(state==186){std::array<float,3> position;float heading,offset;
   if(host.owner_linked_pose(s,position,heading,offset)){s.heading=heading;s.offset=offset;const float angle=90-(heading+offset),radius=reg==220?135.f:125.f;s.position={legacy_trig(angle,true)*radius+position[0],position[1]+(reg==220?90.f:50.f),legacy_trig(angle,false)*radius+position[2]};}
  }else{s.heading=host.owner_heading(s);s.pitch=host.owner_pitch(s);s.offset=host.owner_offset(s);s.position=host.owner_position(s);s.position[1]+=85;}
 }
 ++s.frame;host.advance_frame(s);return true;
}
template<class Host> bool tick_item39_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 if(s.released)return false;
 if(!item39_projectile_registration(unsigned(s.item),reg))throw std::invalid_argument("Unsupported item39 registration");
 const auto age=projectile_signed(s.frame);auto finish=[&](){s.released=true;return false;};
 if(reg>=50&&reg<=80&&(projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(reg==0||reg==180)return finish();
 if(reg==10||reg==20){
  if(age==0){approach_battle_offset(s.offset,0,5);s.speed=reg==10?45.f:55.f;s.capacity.fill(1);s.scratch_e8=0;}
  if(age==1)normal_projectile_direct_velocity(s);if(age<120)approach_battle_offset(s.offset,0,.1f);s.velocity[1]-=.2f;
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0||age>180){host.child_position(s,reg==10?3:4,0,0,0);host.sound(s,71);return finish();}
 }else if(reg==30||reg==40){
  if(age==0){if(reg==40){s.scale.fill(3);s.speed=0;s.velocity[1]=0;}s.capacity.fill(1);}if(age>51)return finish();
 }else if(reg>=50&&reg<=80){
  if(age==0){item9_13_birth_aim(s,host);approach_battle_offset(s.offset,0,5);s.speed=reg==50?45.f:reg==60?55.f:reg==70?40.f:52.5f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;if(reg>=70)s.scale.fill(2);if(reg==60)host.trail(s,0,60,15,1,0);}
  if(reg<=60){if(age==1)normal_projectile_direct_velocity(s);s.velocity[1]-=.2f;}else{s.rotation[0]+=25;if(reg==80&&age%3==0)host.particle_offset(s,9,0,0,0);}
  ++s.scratch_ec;const unsigned limit=reg==50?100:reg==60?120:75;if(projectile_signed(s.scratch_ec)>int(limit))s.scratch_ec=limit;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){const float step=reg<=60?.1f:reg==70?.2f:.3f;approach_battle_offset(s.offset,0,step);if(reg>=70)item9_13_pitch_step(s,host,3,step);}
  const auto contact=projectile_contacts(s);if(age>240||(contact!=0&&contact!=1)||host.stage_collision(s)==1)return finish();
 }else if(reg==90){if(age==0){s.speed=0;s.rotation[2]=10;}if(age>13)return finish();}
 else if(reg==100||reg==110){
  if(age==0){approach_battle_offset(s.offset,0,5);s.speed=50;s.capacity.fill(1);s.scratch_e8=0;}if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(age>10||projectile_contacts(s)!=0||host.stage_collision(s)==1){host.child_position(s,reg==100?12:13,0,0,0);return finish();}
 }else if(reg==120||reg==130){
  if(age==0){s.speed=0;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scale.fill(reg==120?2.f:3.f);}
  host.particle_offset(s,14,0,0,0);if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(age>(reg==120?60:120))s.scratch_ec=1;
  if(s.scratch_ec==1){s.capacity.fill(0);for(auto& axis:s.scale)axis-=.1f;if(s.scale[2]<=0)return finish();}
 }else if(reg==140){
  if(age==0){s.speed=20;s.offset=float(std::int16_t(host.random_word()%360u));s.pitch=float(std::int16_t(host.random_word()%360u));s.scratch_e8=0;s.capacity.fill(0);}
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1)return finish();if(age>15)return finish();
 }else if(reg==150){
  if(age==0){item9_13_birth_aim(s,host);host.particle_offset(s,17,0,0,0);s.speed=53.5f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=s.scratch_f4=0;}
  if(host.stage_collision(s)==1)s.scratch_f4=1;++s.scratch_ec;++s.scratch_f0;if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){approach_battle_offset(s.offset,0,.1f);item9_13_pitch_step(s,host,3,.05f);}
  if(projectile_signed(s.scratch_f0)>480||host.stage_collision(s)==1){s.scratch_f4=1;s.capacity.fill(0);s.speed=0;}
  if(s.scratch_f4==1){for(auto& axis:s.scale)axis-=.1f;if(s.scale[0]<=0)return finish();}
  if(age==60){s.frame=40;return true;}
 }else if(reg==160||reg==260){
  if(age==0){s.scale=reg==160?std::array<float,3>{1.5f,.25f,.25f}:std::array<float,3>{1.5f,1.5f,1.5f};s.speed=.01f;s.scratch_e8=s.scratch_ec=0;s.capacity.fill(1);if(reg==160)host.particle_offset(s,17,0,0,0);}
  ++s.scratch_e8;s.scratch_ec+=2;if(age==41)return finish();
 }else if(reg==170){
  if(age==0){s.scratch_e8=255;s.rotation[1]=float(host.random_word()%360u);s.scale.fill(.05f);s.speed=0;}
  item11_22_wave(s,float(projectile_signed(s.frame*3u)),.025f);if(age>6){s.scratch_e8-=10;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}host.alpha(s,s.scratch_e8&255u);
 }else if(reg==190){
  if(age==0){s.scale.fill(1);s.speed=60;s.scratch_e8=255;s.scratch_ec=s.scratch_f0=0;s.capacity.fill(1);}
  s.frame=1;++s.scratch_ec;s.speed-=.5f;if(s.speed<10)s.speed=10;const unsigned shade=s.scratch_e8&255u;host.color(s,shade,shade,shade,255);for(auto& axis:s.scale)axis+=.05f;
  if(projectile_signed(s.scratch_ec)>45||host.stage_collision(s)==1||projectile_contacts(s)!=0){s.capacity.fill(0);s.scratch_f0=1;}
  if(projectile_signed(s.scratch_f0)>0){s.scratch_e8-=5;if(projectile_signed(s.scratch_e8)<0){s.scratch_e8=0;return finish();}}
 }else if(reg==200){
  if(age==0){s.scale.fill(2);s.speed=40;s.capacity.fill(1);s.velocity[1]=40;}if(age>60||host.stage_collision(s)==1||projectile_contacts(s)!=0)return finish();
 }else if(reg==210){
  if(age==0){item9_13_birth_aim(s,host);s.speed=65;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scale.fill(1);}
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;if(s.scratch_e8==0){approach_battle_offset(s.offset,0,.3f);item9_13_pitch_step(s,host,3,.3f);}
  if(age==60){s.scratch_e8=1;normal_projectile_direct_velocity(s);}if(age>60)s.velocity[1]-=.15f;if(age>480||host.stage_collision(s)==1)return finish();
 }else if(reg==220){
  if(age==0){item9_13_birth_aim(s,host);s.speed=5;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;}
  s.scale.fill(legacy_trig(float(age)*30,true)*.05f+.5f);++s.scratch_ec;s.speed+=.25f;if(s.speed>40)s.speed=40;if(projectile_signed(s.scratch_ec)>100)s.scratch_ec=100;
  if(s.offset>90||s.offset<-90)s.scratch_e8=0xffffffffu;if(s.scratch_e8==0&&age>0){const float step=float(projectile_signed(s.scratch_ec))*.002f;approach_battle_offset(s.offset,0,step);item9_13_pitch_step(s,host,3,step);}
  if(age>480||projectile_contacts(s)!=0||host.stage_collision(s)==1){for(unsigned slot:{23u,24u,25u})host.child_position(s,slot,0,0,0);host.sound(s,157);return finish();}
 }else if(reg>=230&&reg<=250){
  if(age==0){s.rotation={0,0,-s.pitch};s.speed=0;s.velocity[1]=0;s.scratch_e8=0;s.scratch_ec=255;s.scale.fill(reg==230?8.f:reg==240?4.5f:6.f);if(reg!=250)s.capacity.fill(reg==230?0:1);}
  const float growth=reg==250?1.f:s.scale[0]>=(reg==230?14.f:10.f)?(reg==230?.005f:.0035f):(reg==230?.5f:.25f);for(auto& axis:s.scale)axis+=growth;
  if(reg==230){
   if(age==17){s.frame-=16;return true;}++s.scratch_e8;const auto counter=projectile_signed(s.scratch_e8);if(counter>10&&counter%5==0&&counter<120){s.capacity.fill(1);s.contacts.fill(0);}
   if(counter>120){s.scratch_ec-=5;s.capacity.fill(0);if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}
  }else if(reg==240){++s.scratch_e8;const auto counter=projectile_signed(s.scratch_e8);if(counter>20){s.capacity.fill(0);if(counter>90){s.scratch_ec-=5;if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}}}
  else if(age>60){s.capacity.fill(0);s.scratch_ec-=15;if(projectile_signed(s.scratch_ec)<0){s.scratch_e8=0;return finish();}}host.alpha(s,s.scratch_ec&255u);
 }else if(reg==270){if(age==0){s.speed=0;s.capacity.fill(1);s.scratch_e8=0;s.scale={7,12,7};}if(age==30){s.speed=0;s.capacity.fill(0);return finish();}}
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
