#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"

namespace daybreak {
// Explicit cases in 5fb000/5fd170/60ea90/620e20 which the earlier dispatcher
// sent to narrower normal/charged families. Registration numbers are DAT IDs,
// not a common classification of gameplay shots versus visual scene objects.
inline bool item2_5_18_34_projectile_registration(unsigned item,unsigned reg){
 return (item==2&&reg==60)||(item==5&&(reg==30||reg==40||reg==80))||
        (item==18&&(reg==10||reg==30||reg==50||reg==110))||
        (item==34&&(reg==10||reg==30||reg==80));
}
template<class Host> void early_projectile_birth_pitch(KeiichiNormalProjectile& s,Host& h){
 const auto target=h.target_state(s);
 if((target>117&&target<122)||target==221){
  if(s.pitch-h.target_elevation(s)<10.f)s.pitch=h.target_elevation(s);
  if(s.pitch-h.target_elevation(s)>-10.f)s.pitch=h.target_elevation(s);
 }
}
template<class Host> bool tick_item2_5_18_34_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& h){
 if(s.released)return false;
 const auto item=unsigned(s.item);
 if(!item2_5_18_34_projectile_registration(item,reg))
  throw std::runtime_error("Unsupported item2/5/18/34 projectile registration");
 // Preserve each handler's prefix, including Shovel registration10. Reflection
 // changes both the queried target and the contact/capacity fields.
 if((item==2||(item==5&&reg!=80)||(item==18&&reg==10)||(item==34&&reg==10))&&
    (projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 const auto age=projectile_signed(s.frame);
 if(item==2){ // 5fb000 case60
  if(age==0){h.visual_child(s,7);s.speed=50;s.capacity.fill(1);s.scratch_e8=0;early_projectile_birth_pitch(s,h);}
  if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0&&age>0){
   approach_battle_offset(s.offset,0,1);
   if(s.pitch-h.target_elevation(s)>3)s.pitch-=.5f;
   if(s.pitch-h.target_elevation(s)< -3)s.pitch+=.5f;
  }
  if(age>240||projectile_contacts(s)!=0||h.stage_collision(s)==1){
   h.child(s,8,0,0,false);s.released=true;return false;
  }
 }else if(item==5){
  if(reg==80){ // 5fd170 case80: short visual; preserve speed/capacity.
   if(age==0){s.scale.fill(.7f);s.rotation[2]=float(h.random_word()%30u)-15;
    s.rotation[1]=float(h.random_word()%30u)-15;s.rotation[0]=float(h.random_word()%360u);}
   if(age>14){s.released=true;return false;}
  }else{
   if(age==0){
    early_projectile_birth_pitch(s,h);s.speed=reg==30?55.f:50.f;s.capacity.fill(1);
    if(reg==30){s.scratch_e8=s.scratch_ec=0;h.trail(s,0,60,15,1,0);}
    else{h.trail(s,1,120,30,1,0);s.scratch_e8=s.scratch_ec=0;s.scale.fill(.8f);}
   }
   ++s.scratch_ec;
   if(reg==40&&age%5==0)h.visual_child(s,8);
   const auto cap=reg==30?120:90;
   if(projectile_signed(s.scratch_ec)>cap)s.scratch_ec=unsigned(cap);
   if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0){
    const float turn=reg==30?.35f:float(projectile_signed(s.scratch_ec))*.015f;
    const float pitch_step=reg==30?.25f:float(projectile_signed(s.scratch_ec))*.0025f;
    const float pitch_limit=reg==30?3.f:1.f;
    approach_battle_offset(s.offset,0,turn);
    if(s.pitch-h.target_elevation(s)>pitch_limit)s.pitch-=pitch_step;
    if(s.pitch-h.target_elevation(s)< -pitch_limit)s.pitch+=pitch_step;
   }
   // This script loops its age at10 before contact/stage queries and before
   // the DAT cursor service; free flight still runs in the separate pass.
   if(reg==40&&age==10){s.frame=1;return true;}
   const auto flags=projectile_contacts(s);
   if(age>(reg==30?240:480)||(flags!=0&&flags!=1)||h.stage_collision(s)==1){s.released=true;return false;}
  }
 }else if(item==18){
  if(reg==10){ // 60ea90 case10
   if(age==0){early_projectile_birth_pitch(s,h);s.speed=52.5f;s.capacity.fill(1);
    s.scratch_e8=s.scratch_ec=0;s.scale.fill(2);}
   s.rotation[0]+=25;
   if(age%3==0)h.visual_child(s,11);
   ++s.scratch_ec;if(projectile_signed(s.scratch_ec)>75)s.scratch_ec=75;
   if(s.offset>90||s.offset< -90)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0){
    approach_battle_offset(s.offset,0,.3f);
    if(s.pitch-h.target_elevation(s)>3)s.pitch-=.3f;
    if(s.pitch-h.target_elevation(s)< -3)s.pitch+=.3f;
   }
   const auto flags=projectile_contacts(s);
   if(age>240||(flags!=0&&flags!=1)||h.stage_collision(s)==1){s.released=true;return false;}
  }else if(reg==30){ // 60ea90 case30; 42c8b0 is location SE, not a graphic FX.
   if(age==0){approach_battle_offset(s.offset,0,10);s.speed=44.5f;s.capacity.fill(1);
    s.scratch_e8=s.scratch_ec=0;h.trail(s,3,60,25,1,0);}
   if(age==1)normal_projectile_direct_velocity(s);
   s.velocity[1]-=.5f;
   if(age>800||projectile_contacts(s)!=0||h.stage_collision(s)==1){
    h.sound(s,74);h.child(s,5,0,0,false);s.released=true;return false;
   }
   s.scratch_ec+=3;if(projectile_signed(s.scratch_ec)>70)s.scratch_ec=70;
   if(s.scratch_e8==0){
    const float step=float(projectile_signed(s.scratch_ec))*.01f;
    if(s.offset>1)s.offset-=step;if(s.offset< -1)s.offset+=step;
   }
   s.velocity[0]=legacy_trig(s.heading+s.offset,false)*s.speed;
   s.velocity[2]=legacy_trig(s.heading+s.offset,true)*s.speed;
  }else if(reg==50){ // 60ea90 case50: pulse, capacity cutoff, alpha fade.
   if(age==0){s.pitch=0;s.capacity.fill(1);s.contacts.fill(0);s.scale.fill(1.5f);s.scratch_e8=255;}
   for(int axis=2;axis>=0;--axis)s.scale[unsigned(axis)]+=legacy_trig(float(age)*3,false)*.2f;
   if(age==6)s.capacity.fill(0);
   if(age>10){s.scratch_e8-=13;if(projectile_signed(s.scratch_e8)<0)s.scratch_e8=0;}
   h.alpha(s,s.scratch_e8&255u);
   if(age>30){s.released=true;return false;}
  }else{ // 60ea90 case110
   if(age==0){s.speed=0;s.rotation[2]=10;}
   if(age>13){s.released=true;return false;}
  }
 }else{
  if(reg==10){ // 620e20 case10
   if(age==0){s.scale.fill(.5f);for(auto& a:s.rotation)a=float(h.random_word()%360u);
    s.speed=45;s.capacity.fill(1);s.scratch_e8=0;}
   if(age==1)normal_projectile_direct_velocity(s);
   s.scratch_e8+=50;s.velocity[1]-=.4f;
   if(h.stage_collision(s)==1||projectile_contacts(s)!=0||age>180){s.released=true;return false;}
  }else if(reg==30){ // 620e20 case30
   if(age==0){s.scale.fill(.75f);for(auto& a:s.rotation)a=float(h.random_word()%360u);
    approach_battle_offset(s.offset,0,10);s.speed=30;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
   if(age==0)normal_projectile_direct_velocity(s);
   approach_battle_offset(s.offset,0,.1f);s.velocity[1]-=.25f;
   if(age>800||projectile_contacts(s)!=0||h.stage_collision(s)==1){
    h.sound(s,176);
    for(unsigned i=0;i<12;++i){s.scratch_f0=h.random_word()%360u;s.scratch_ec=h.random_word()%40u;
     h.child(s,4,float(s.scratch_f0),float(s.scratch_ec)+30,true);}
    s.released=true;return false;
   }
  }else{ // 620e20 case80
   if(age==0)s.speed=30;
   if(age==1)normal_projectile_direct_velocity(s);
   s.velocity[1]-=.5f;
   if(age>60){s.released=true;return false;}
  }
 }
 ++s.frame;h.advance_frame(s);return true;
}
}
