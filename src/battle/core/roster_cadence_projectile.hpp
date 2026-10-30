#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {

// Original item handlers 616aa0, 617470 and 626f30. The three parents emit
// short-lived DAT registrations every third script visit. Item25's seven
// asset-backed descendants use the same 617470 handler and keep their own
// contact, steering, trail and fade rules. Visual lifetimes bound pool usage.
inline bool roster_cadence_projectile_registration(unsigned item,unsigned registration){
 return (item==24&&(registration==0||registration==70))||
        (item==25&&registration<=80&&registration%10==0)||
        (item==38&&(registration==0||registration==10||registration==20||registration==30));
}
template<class Host> bool tick_roster_cadence_projectile(
    KeiichiNormalProjectile& s,unsigned registration,Host& host){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(!roster_cadence_projectile_registration(item,registration))
  throw std::invalid_argument("Unsupported cadence projectile registration");
 if((registration==0||(item==38&&registration==10)||(item==25&&(registration==10||registration==20||
     registration==30||registration==70)))&&(projectile_contacts(s)&0x100))
  reflect_normal_projectile(s,item==25?(registration==20||registration==30?1:
                            registration==70?4:5):1);
 if(item==24&&registration==0){
  if(s.frame==0){s.speed=50.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;s.scale.fill(0.f);}
  if(s.frame%3==0)host.visual_child(s,7);
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.1f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=.1f;
   if(s.pitch-target< -1.f)s.pitch+=.1f;
  }
  if(projectile_signed(s.frame)>30||host.stage_collision(s)==1){s.released=true;return false;}
 }else if(item==25&&(registration==0||registration==10)){
  const bool charged=registration==10;
  if(s.frame==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
   if(charged)host.trail(s,2,40.f,15,1,0);
   s.scratch_f4=55;s.capacity.fill(charged?5:4);
   s.scratch_e8=s.scratch_f0=0;s.scratch_ec=charged?40:0;
  }
  if(s.frame%3==0)host.visual_child(s,8);
  if(projectile_contacts(s)!=0){
   if(projectile_signed(s.scratch_f0)<5){s.speed=1.f;++s.scratch_f0;return true;}
   s.scratch_f0=0;s.speed=float(projectile_signed(s.scratch_f4));s.contacts.fill(0);
  }
  s.scratch_f4=std::uint32_t(std::max(30,projectile_signed(s.scratch_f4)-(charged?1:2)));
  s.speed=float(projectile_signed(s.scratch_f4));
  s.scratch_ec=std::uint32_t(std::min(charged?90:60,projectile_signed(s.scratch_ec)+(charged?2:1)));
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float step=float(projectile_signed(s.scratch_ec))*(charged?.01f:.007f);
   approach_battle_offset(s.offset,0.f,step);
   const float target=host.target_elevation(s);
   if(s.pitch-target>3.f)s.pitch-=step;
   if(s.pitch-target< -3.f)s.pitch+=step;
  }
  if(projectile_signed(s.frame)>(charged?240:300)||host.stage_collision(s)==1){s.released=true;return false;}
 }else if(item==25&&(registration==20||registration==30)){
  const bool large=registration==30;
  if(s.frame==0){
   s.scale.fill(large?1.f:.75f);s.speed=large?70.f:50.f;
   s.capacity.fill(1);s.scratch_e8=0;
   host.trail(s,large?2:0,10.f,large?50:40,1,0);
  }
  s.speed=std::max(25.f,s.speed-1.5f);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,large?.3f:.1f);
   const float target=host.target_elevation(s),step=large?.1f:.05f;
   if(s.pitch-target>1.f)s.pitch-=step;
   if(s.pitch-target< -1.f)s.pitch+=step;
  }
  if(projectile_signed(s.frame)>300||host.stage_collision(s)==1){s.released=true;return false;}
 }else if(item==25&&registration==40){
  if(s.frame==0)s.capacity.fill(1);
  if(projectile_signed(s.frame)>51){s.released=true;return false;}
 }else if(item==25&&registration==50){
  if(s.frame==0){s.scale.fill(.5f);s.speed=0;s.capacity.fill(1);s.scratch_e8=255;}
  const float growth=legacy_trig(float(projectile_signed(s.frame))*4.f,false)*.1f;
  for(auto& axis:s.scale)axis+=growth;
  if(s.frame>0)s.scratch_e8=std::uint32_t(std::max(0,projectile_signed(s.scratch_e8)-13));
  if(projectile_signed(s.frame)>20){s.released=true;return false;}
  host.alpha(s,s.scratch_e8&255u);
 }else if(item==25&&registration==60){
  if(s.frame==0){s.speed=90.f;s.capacity.fill(1);}
  const auto contact=projectile_contacts(s);
  if(projectile_signed(s.frame)>120||(contact!=0&&contact!=1)||
     host.stage_collision(s)==1){s.released=true;return false;}
 }else if(item==25&&registration==70){
  if(s.frame==0){
   s.speed=50.f;host.trail(s,2,40.f,15,1,0);s.capacity.fill(4);
   s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
  }
  s.speed=std::max(30.f,s.speed-1.f);
  if(projectile_contacts(s)!=0){
   if(projectile_signed(s.scratch_f0)<5){s.speed=1.f;++s.scratch_f0;return true;}
   s.scratch_f0=0;s.speed=35.f;s.contacts.fill(0);
  }
  s.scratch_ec=std::uint32_t(std::min(30,projectile_signed(s.scratch_ec)+1));
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   const float step=float(projectile_signed(s.scratch_ec))*.009f;
   approach_battle_offset(s.offset,0.f,step);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=step;
   if(s.pitch-target< -1.f)s.pitch+=step;
  }
  if(projectile_signed(s.frame)>240||host.stage_collision(s)==1){s.released=true;return false;}
 }else if(item==38&&(registration==0||registration==10)){
  const bool charged=registration==10;
  if(s.frame==0){
   s.turn_rate=0;s.scratch_e8=0;s.speed=charged?40.f:35.f;s.capacity.fill(1);
   if(charged)host.trail(s,2,200.f,25,1,0); // 5f7450 tracked visual surrogate.
  }
  s.speed=std::max(25.f,s.speed-.25f);
  if(!charged&&s.frame%3==0)host.visual_child(s,3);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   s.turn_rate=std::min(.6f,s.turn_rate+.01f);
   approach_battle_offset(s.offset,0.f,(charged?1.25f:.75f)+s.turn_rate);
   const float target=host.target_elevation(s);
   const float step=s.turn_rate*.5f+(charged?.3f:.2f);
   if(s.pitch-target>1.f)s.pitch-=step;
   if(s.pitch-target< -1.f)s.pitch+=step;
  }
  if(host.stage_collision(s)==1||projectile_contacts(s)!=0||projectile_signed(s.frame)>180){
   host.sound(s,0x69);host.child(s,2,0,0,false);s.released=true;return false;
  }
 }else if(item==24&&registration==70){
  if(s.frame==0){
   s.scale.fill(.7f);
   s.rotation[2]=float(host.random_word()%30u)-15.f;
   s.rotation[1]=float(host.random_word()%30u)-15.f;
   s.rotation[0]=float(host.random_word()%360u);
  }
  if(projectile_signed(s.frame)>14){s.released=true;return false;}
 }else if(item==25&&registration==80){
  if(s.frame==0){
   s.scale.fill(.4f);
   s.rotation[2]=float(host.random_word()%20u)-10.f;
   s.rotation[1]=float(host.random_word()%20u)-10.f;
   s.rotation[0]=float(host.random_word()%360u);
  }
  if(projectile_signed(s.frame)>14){s.released=true;return false;}
 }else if(item==38&&registration==30){
  if(s.frame==0){
   s.scale.fill(float(host.random_word()%10u)*.1f+1.f);
   s.rotation[1]=float(host.random_word()%360u);
  }
  if(projectile_signed(s.frame)>29){s.released=true;return false;}
 }else if(item==38&&registration==20){
  if(s.frame==0){s.scale.fill(.5f);s.speed=0;s.velocity[1]=0;s.capacity.fill(1);}
  if(projectile_signed(s.frame)>51){s.released=true;return false;}
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
