#pragma once
#include "keiichi_normal_projectile.hpp"
#include "battle_steering.hpp"
#include <algorithm>
#include <stdexcept>

namespace daybreak {
// DAT-active motion scripts in the original item switch. Source VAs:
// 5fdee0 (6), 5ff3d0 (7), 6020f0 (9), 602ee0 (10), 604400 (11), 611260 (20),
// 6145f0 (22), 6183b0 (26), 62b830 (41). The script runs before movement.
inline bool roster_motion_projectile_registration(unsigned item,unsigned registration){
 return (registration==0&&(item==6||item==7||item==9||item==10||item==11||item==20||item==22||item==26||item==41))||
        (item==6&&(registration==10||registration==20))||
        (item==11&&(registration==10||registration==60))||
        (item==7&&registration==10)||(item==22&&(registration==10||registration==150))||
        (item==41&&registration==10)||
        (item==26&&(registration==10||registration==20||registration==30));
}
template<class Host> bool tick_roster_motion_projectile(KeiichiNormalProjectile& s,Host& host,unsigned registration=0){
 if(s.released)return false;
 const unsigned item=unsigned(s.item);
 if(!roster_motion_projectile_registration(item,registration))
  throw std::invalid_argument("Unsupported roster motion projectile item");
 const int age=projectile_signed(s.frame);
 auto finish=[&](){s.released=true;return false;};
 // Original item20/0 and item26/0 do not enter the reflection preamble.
 // Item20 reflects only registrations20/30 in its item-specific switch.
 if(item!=20&&item!=26&&!(item==6&&registration==10)&&
    !(item==11&&registration==10)&&
    !(item==22&&registration==150)&&
    (projectile_contacts(s)&0x100))reflect_normal_projectile(s);
 if(item==6){
  if(registration==10){
   if(age==0){
    const int state=host.target_state(s);
    if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
    approach_battle_offset(s.offset,0.f,10.f);
    s.speed=55.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
    host.child(s,5,0,0,false);s.scale.fill(2.f);
   }
   if(s.scratch_ec==0){
    s.speed-=2.f;
    if(s.speed<0.f||projectile_contacts(s)!=0||host.stage_collision(s)==1){
     s.speed=0;
     if((projectile_contacts(s)&1)==0){
      s.scratch_ec=2;host.retarget_owner(s);host.owner_signal(s,1);
     }else{s.scratch_ec=1;host.child(s,4,0,0,false);}
    }
   }
   if(s.scratch_ec==1){
    s.capacity.fill(0);s.speed=std::max(2.f,s.speed-5.f);
    ++s.scratch_e8;
    if(projectile_signed(s.scratch_e8)>30){
     s.scratch_ec=2;host.retarget_owner(s);host.owner_signal(s,1);
    }
   }
   if(s.scratch_ec==2){
    if(projectile_contacts(s)&1){host.child(s,7,0,0,false);return finish();}
    s.capacity.fill(0);s.speed=40.f;
    approach_battle_offset(s.offset,0.f,180.f);
    s.pitch=host.target_elevation(s);
    if(host.target_distance_squared(s)<10000.f){
     host.owner_signal(s,3);return finish();
    }
   }
   std::array<float,3> owner_aim{};
   for(unsigned axis=0;axis<3;++axis)owner_aim[axis]=s.position[axis]+s.velocity[axis]*40.f;
   host.owner_projectile_aim(s,owner_aim);
   const unsigned state=host.owner_state(s);
   if((state>99&&state<300)||(state!=450&&state!=460))return finish();
  }else if(registration==20){
   if(age==0){
    const int state=host.target_state(s);
    if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
    s.speed=60.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
    s.scale.fill(1.25f);
   }
   s.rotation[1]+=15.f;
   if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
   s.scratch_f0=std::min(s.scratch_f0+1u,60u);
   if(s.scratch_e8==0)approach_battle_offset(s.offset,0.f,.1f);
   const auto contact=projectile_contacts(s);
   if(s.scratch_ec==0&&(age>60||(contact!=0&&contact!=1)||host.stage_collision(s)==1))s.scratch_ec=1;
   if(s.scratch_ec==1){
    s.speed=2.f;s.capacity.fill(0);
    for(auto& axis:s.scale)axis-=.1f;
    if(s.scale[2]<0.f)return finish();
   }
  }else{
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=35.f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
  }
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  s.scratch_f0=std::min(s.scratch_f0+1u,60u);
  if(s.scratch_e8==0)approach_battle_offset(s.offset,0.f,.1f);
  const auto contact=projectile_contacts(s);
  if(s.scratch_ec==0&&(age>60||(contact!=0&&contact!=1)||host.stage_collision(s)==1))s.scratch_ec=1;
  if(s.scratch_ec==1){
   s.speed=2.f;s.capacity.fill(0);
   for(auto& axis:s.scale)axis-=.1f;
   if(s.scale[2]<=0.f)return finish();
  }
  }
 }else if(item==7){
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=42.5f;s.capacity.fill(1);s.scratch_e8=s.scratch_f0=0;
   host.trail(s,0,10.f,registration==10?60u:20u,1,0);
  }
  s.scratch_f0=std::min(s.scratch_f0+1u,100u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,float(s.scratch_f0)*.001f);
   const float target=host.target_elevation(s);
   const float step=float(s.scratch_f0)*.0005f;
   if(s.pitch-target>1.f)s.pitch-=step;
   if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=step;
  }
  if(age>240||host.stage_collision(s)==1)return finish();
 }else if(item==9){
  if(age==0){
   s.speed=42.5f;s.capacity.fill(1);s.scratch_e8=s.scratch_f0=s.scratch_f4=0;
   s.scale[1]=s.scale[2]=2.f;
   approach_battle_offset(s.offset,0.f,5.f);
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
  }
  s.scratch_f0=std::min(s.scratch_f0+1u,120u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.15f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=.1f;
   if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=.1f;
  }
  const auto contact=projectile_contacts(s);
  if(s.scratch_f0>119u||(contact!=0&&contact!=1)||host.stage_collision(s)==1)s.scratch_f4=1;
  if(s.scratch_f4==1){
   s.speed=0;s.capacity.fill(0);
   s.scale[0]-=.15f;s.scale[1]-=.2f;s.scale[2]-=.2f;
   if(s.scale[0]<=0.f)return finish();
  }
 }else if(item==10){
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=27.5f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;
   host.trail(s,0,60.f,20,1,0);
  }
  s.scratch_f0=std::min(s.scratch_f0+1u,60u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(s.scratch_e8==0){
   approach_battle_offset(s.offset,0.f,.5f);
   const float target=host.target_elevation(s);
   if(s.pitch-target>1.f)s.pitch-=.25f;
   if(s.pitch-host.target_elevation(s)< -1.f)s.pitch+=.25f;
  }
  if(age>120||projectile_contacts(s)!=0||host.stage_collision(s)==1){
   for(unsigned i=0;i<16;++i){
    const float pitch=float(host.random_word()%360u);
    const float yaw=float(host.random_word()%360u);
    host.particle(s,4,yaw,pitch);
   }
   s.scratch_ec=1;return finish();
  }
 }else if(item==11){
  if(registration==10){
   if(age==0){
    const int state=host.target_state(s);
    if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
    host.visual_child(s,2);s.scale.fill(3.f);s.speed=50.f;
    s.capacity.fill(1);s.scratch_e8=0;s.scratch_ec=40;
   }
   s.scratch_ec=std::max(s.scratch_ec+1u,100u);
   if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0){
    const float step=float(projectile_signed(s.scratch_ec));
    approach_battle_offset(s.offset,0.f,step*.002f);
    const float target=host.target_elevation(s);
    if(s.pitch-target>3.f)s.pitch-=step*.0015f;
    if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step*.0015f;
   }
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age==120){
    host.child(s,3,0,0,false);return finish();
   }
  }else if(registration==60){
   if(age==0){
    const int state=host.target_state(s);
    if((state>117&&state<122)||state==221)s.pitch=host.target_elevation(s);
    s.speed=45.f;s.capacity.fill(1);s.scratch_e8=0;s.scratch_ec=40;
    host.trail(s,0,10.f,20,1,0);
   }
   s.scratch_ec=std::min(s.scratch_ec+1u,100u);
   if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
   if(s.scratch_e8==0&&age>10&&age<180){
    const float step=float(projectile_signed(s.scratch_ec));
    approach_battle_offset(s.offset,0.f,step*.005f);
    const float target=host.target_elevation(s);
    if(s.pitch-target>3.f)s.pitch-=step*.0035f;
    if(s.pitch-host.target_elevation(s)< -3.f)s.pitch+=step*.0035f;
   }
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>120)return finish();
  }else{
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=35.f;s.capacity.fill(1);s.scratch_e8=0;s.scratch_ec=40;
  }
  s.scratch_ec=std::min(s.scratch_ec+1u,100u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(age>10&&age<180&&s.scratch_e8==0)
   approach_battle_offset(s.offset,0.f,float(s.scratch_ec)*.0025f);
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>120)return finish();
  }
 }else if(item==20){
  if(age==0){s.scale={2.f,1.f,1.f};s.speed=.01f;s.capacity.fill(1);s.scratch_e8=s.scratch_ec=s.scratch_f0=0;}
  if(host.owner_phase(s)==3)s.scratch_ec=1;
  const auto state=host.owner_state(s);
  if(state!=400&&state!=402){host.child(s,10,0,0,false);return finish();}
  if(projectile_contacts(s)!=0&&++s.scratch_f0>10){s.scratch_f0=0;s.capacity.fill(1);s.contacts.fill(0);}
  if(s.scratch_ec==1){
   s.speed=.01f;s.capacity.fill(0);
   s.scale[0]-=0.f;s.scale[1]-=.1f;s.scale[2]-=.1f;
   if(s.scale[2]<0.f)return finish();
  }
 }else if(item==22){
  if(registration==150){
   // Legacy motion-only fixture adapter. Normal runtime selects the full
   // item22 family first: item11_22_projectiles.hpp stores integer owner
   // coordinates for110/150 and consumes them for120 via manager services.
   if(age==0){s.speed=25.f;s.scratch_e8=0;}
   if(age==1)normal_projectile_direct_velocity(s);
   if(age%5==0)host.visual_child(s,13);
   s.velocity[1]-=.5f;
   if(projectile_contacts(s)!=0||host.stage_collision(s)==1){
    host.sound(s,74);host.child(s,16,0,0,false);return finish();
   }
   if(age>300)return finish();
  }else{
  if(age==0){s.speed=registration==10?55.f:35.f;s.capacity.fill(1);s.scratch_e8=0;s.scratch_ec=40;
   if(registration==10)s.scale.fill(2.f);}
  if(age==1)normal_projectile_direct_velocity(s);
  s.velocity[1]-=registration==10?.2f:.15f;
  s.scratch_ec=std::min(s.scratch_ec+(registration==10?4u:1u),100u);
  if(s.offset>90.f||s.offset< -90.f)s.scratch_e8=0xffffffffu;
  if(projectile_contacts(s)!=0||host.stage_collision(s)==1||age>600){
   host.child(s,registration==10?5u:4u,0,0,false);
   host.sound(s,159);return finish();
  }
  const float angle=s.heading+s.offset;
  s.velocity[0]=legacy_trig(angle,false)*s.speed;
  s.velocity[2]=legacy_trig(angle,true)*s.speed;
  }
 }else if(item==26){
  s.rotation[0]+=(registration==10||registration==30)?-25.f:25.f;
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=registration==20||registration==30?60.f:50.f;
   s.capacity.fill(1);s.scratch_e8=s.scratch_ec=0;
   s.scale.fill(registration==20||registration==30?2.f:1.f);
  }
  bool transitioned=false;
  if(s.scratch_ec==0){
   s.speed-=1.f;
   if(s.speed<=0.f||host.stage_collision(s)==1){
    s.scratch_ec=1;s.speed=0.f;host.retarget_owner(s);
    s.capacity.fill(1);s.contacts.fill(0);transitioned=true;
   }
  }
  if(!transitioned){
   if(s.scratch_ec!=0){
    ++s.scratch_ec;s.speed=std::min(s.speed+1.5f,60.f);
    approach_battle_offset(s.offset,0.f,180.f);
    s.pitch=host.target_elevation(s);
    if(host.target_distance_squared(s)<10000.f)return finish();
   }
   if(age>180)return finish();
  }
 }else{ // item 41
  if(age==0){
   const int state=host.target_state(s);
   if((state>117&&state<122)||state==221){
    const float target=host.target_elevation(s);
    if(s.pitch-target<10.f||s.pitch-target> -10.f)s.pitch=target;
   }
   s.speed=registration==10?75.f:65.f;s.capacity.fill(1);s.scratch_e8=0;s.scratch_ec=40;
   s.scratch_f0=s.scratch_f4=0;
  }
  if(age==1){normal_projectile_direct_velocity(s);s.pitch=0;}
  s.velocity[1]-=.1f;
  approach_battle_offset(s.offset,0.f,registration==10?.2f:.1f);
  if(projectile_contacts(s)!=0){
   if(s.contacts[s.target]==0)host.target_refresh(s);
   if(registration==0)s.capacity.fill(0);
   host.child(s,registration==10?19u:17u,0,0,false);return finish();}
  if(host.stage_collision(s)==1){host.child(s,registration==10?18u:16u,0,0,false);return finish();}
  if(age>180)return finish();
 }
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
