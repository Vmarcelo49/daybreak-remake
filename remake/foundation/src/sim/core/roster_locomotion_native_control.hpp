#pragma once
#include "battle_roster_walk.hpp"
#include <cstring>
namespace daybreak {
struct RosterLocomotionNativeInput {
 unsigned character=0,weapon=0;
 std::int32_t state=0,phase=0,frame=0,secondary=0,x=0,z=0;
 std::int32_t grounded=1,stop=0,slow=0,duration=0;
 bool hold=true;
 bool awakened=false;
};
struct RosterLocomotionNativeMotion {
 float speed=0,vertical=0,gravity=0,movement=0,offset=0,turn=0;
 std::int32_t gauge=0,direction=10;
};
struct RosterLocomotionNativeEffects {
 std::int32_t state=0,phase=0,frame=0,secondary=0,next_state=-1,next_phase=-1;
 bool tail=false;
};
inline std::int32_t locomotion_add(std::int32_t value,std::uint32_t delta){
 const auto bits=std::uint32_t(value)+delta;std::int32_t result;std::memcpy(&result,&bits,4);return result;
}
// All46 slot6 State0/10 bodies. The retained walk profile owns only speed
// and steering; admission and the paired AE04/AE08 tail belong to this body.
inline RosterLocomotionNativeEffects advance_roster_locomotion_native(
 RosterLocomotionNativeMotion& motion,const RosterLocomotionNativeInput& in){
 character_action_dispatch(in.character,in.weapon);
 if(in.state!=0&&in.state!=10)throw std::invalid_argument("Native locomotion State");
 RosterLocomotionNativeEffects out{in.state,in.phase,in.frame,in.secondary};
 if(in.stop)return out; // actor+a0 is a word, not a boolean byte.
 const bool keep_vertical=in.character==3&&in.weapon==2;
 const auto refill=[&](){motion.gauge=locomotion_add(motion.gauge,in.slow>0?5u:40u);if(motion.gauge>1000)motion.gauge=1000;};
 const auto state=[&](int next){out.state=out.next_state=next;out.phase=out.frame=out.secondary=0;};
 if(in.state==0){
  motion.speed=0;if(!keep_vertical)motion.vertical=0;
  refill();motion.turn=0;motion.direction=10;
  // State0 does not write movement+60, heading offset, or contact history.
  if(!in.grounded){motion.gravity=.5f;state(43);return out;}
  if(in.x||in.z){state(10);return out;}
 }else{
  const bool late_vertical=(in.character==0&&in.weapon==0)||
   (in.character==13&&in.weapon==1)||(in.character==15&&in.weapon==0);
  if(!keep_vertical&&!late_vertical)motion.vertical=0;
  if(!in.grounded){motion.gravity=.5f;state(43);return out;}
  if(!in.x&&!in.z){state(0);return out;}
  if(!keep_vertical&&late_vertical)motion.vertical=0;
  BattleWalkMotion walk{motion.direction,motion.turn};
  advance_roster_walk(walk,in.character,in.weapon,in.x,in.z,motion.speed,motion.offset,in.awakened);
  motion.direction=walk.direction;motion.turn=walk.step;refill();motion.movement=0;
 }
 out.frame=locomotion_add(out.frame,1);out.secondary=locomotion_add(out.secondary,1);out.tail=true;
 // 4212f0 precedes this phase check. Satoko1 inserts its already recovered
// field tail between the two clock stores and that frame-pointer service.
 if(in.duration<out.frame&&!in.hold){out.phase=out.next_phase=locomotion_add(out.phase,1);out.frame=out.secondary=0;}
 return out;
}
}
