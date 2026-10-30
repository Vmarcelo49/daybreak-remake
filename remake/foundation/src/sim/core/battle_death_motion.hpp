#pragma once
#include "battle_steering.hpp"
#include "battle_magazine.hpp"
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>

namespace daybreak {
// 00428510 states191..199 and 4219a0. Admission services remain synchronous
// world operations; the body owns their call order and both native clocks.
struct BattleDeathMotion {
 unsigned state=191,phase=0,frame=0,second_frame=0,duration=0;
 bool hold=false,grounded=false;
 float speed=0,gravity=0,movement=0,turn=0,offset=0,heading=0;
 std::array<float,3> position{},velocity{};
 unsigned scratch=0,down=0,down_timer=0,invincible=0;
 unsigned health=0,delayed_health=0,gauge=0,bonus=0;
 std::array<unsigned,9> status{};
 std::array<std::uint8_t,16> reset_flags{};
 std::array<BattleMagazine,2> magazines{};
 std::uint8_t changed=0;
 int last_owner=-1;
};
inline int death_signed(unsigned n){int r;std::memcpy(&r,&n,4);return r;}
inline bool battle_death_motion_state(unsigned state){return state>=191&&state<=199;}
template<class Host> bool respawn_battle_death_motion(BattleDeathMotion& s,Host& h){
 if(h.remaining(s)<=0)return false;
 s.health=s.delayed_health=10000;s.down=s.down_timer=0;s.invincible=30;
 s.gauge=1000;s.bonus=0;s.reset_flags.fill(0);s.status.fill(0);
 s.velocity.fill(0);s.speed=0;s.changed=1;
 h.spawn(s);h.reload(s);h.state(s,194);return true;
}
template<class Host> void advance_battle_death_motion(BattleDeathMotion& s,Host& h){
 if(!battle_death_motion_state(s.state))throw std::runtime_error("Unsupported death state");
 s.last_owner=-1;
 const bool first=s.phase==0&&s.frame==0;
 auto settle=[&](){
  if(s.speed>0){s.speed-=.25f;if(s.speed<0)s.speed=0;}
  if(s.speed<0){s.speed+=.25f;if(s.speed>0)s.speed=0;}
 };
 switch(s.state){
 case 191:
  if(!s.grounded){s.velocity[1]=0;h.state(s,195);return;}
  if(first){s.scratch=0;s.speed=-20;}
  if(s.phase==1){
   s.down=100;s.invincible=30;s.down_timer=0;++s.scratch;
   if(death_signed(s.scratch)>30&&h.remaining(s)>0){h.respawn(s);return;}
  }
  settle();break;
 case 192:case 193:case 197:
  if(!s.grounded){h.state(s,195);s.velocity[1]=0;return;}
  if(first){s.movement=0;s.speed=s.state==192?-20.f:s.state==197?-15.f:0.f;s.turn=0;}
  s.speed+=s.state==192?.5f:1.5f;if(s.speed>0)s.speed=0;
  if(s.phase==1&&death_signed(++s.scratch)>30&&h.remaining(s)>0){
   h.state(s,194);s.changed=1;h.spawn(s);s.velocity[1]=0;h.respawn(s);return;
  }
  break;
 case 194:
  if(first)h.voice(s,h.remaining(s)<21?17u:26u,30,0,false);
  if(s.grounded&&s.velocity[1]<=0){h.state(s,44);s.velocity[1]=0;s.invincible=60;return;}
  s.turn=1;s.gravity=.5f;s.velocity[1]-=s.gravity;h.steer(s);break;
 case 195:
  if(first)s.movement=0;
  if(s.grounded&&s.velocity[1]<0){
   s.velocity[1]=0;h.particle(s,300);h.particle(s,310);h.state(s,196);h.sound(s,40);return;
  }
  s.gravity=.3f;s.velocity[1]-=s.gravity;break;
 case 196:
  if(!s.grounded){s.velocity[1]=0;h.state(s,195);return;}
  if(first)s.scratch=0;
  settle();
  if(s.phase==1){s.down=100;s.invincible=30;s.down_timer=0;++s.scratch;
   if(death_signed(s.scratch)>30){h.respawn(s);return;}
  }
  break;
 case 198:case 199:
  if(first){h.voice(s,10,30,0,true);s.movement=s.turn=0;s.speed=-30;s.velocity[1]=20;s.gravity=.3f;}
  if(s.grounded&&s.velocity[1]<0){
   s.velocity[1]=0;h.particle(s,300);h.particle(s,310);h.state(s,196);h.sound(s,40);return;
  }
  if(s.velocity[1]<6&&s.phase==1){h.phase(s,2);return;}
  s.velocity[1]-=s.gravity;if(s.speed< -4)s.speed+=.25f;break;
 }
 ++s.frame;++s.second_frame;h.clock(s);
 if(death_signed(s.duration)<death_signed(s.frame)&&!s.hold)h.phase(s,s.phase+1);
}
}
