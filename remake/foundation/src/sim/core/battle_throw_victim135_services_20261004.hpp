#pragma once
#include "battle_throw_victim135.hpp"
#include <array>
#include <stdexcept>

namespace daybreak {
// Original 4a9c40/4b4090/4bc040 state135. The already recovered movement
// remains in battle_throw_victim135.hpp; this adapter restores the missing
// weapon-pool births, contact services, impact presentation and paired clocks.
// The actor's existing weapon visual policy owns the preceding M0/M1/L calls.
struct ThrowVictim135PresentationInput {
 unsigned weapon=0,phase=0,frame=0,second_frame=0,duration=0,phase_count=1;
 bool hold=true,blocked=false,wall=false,grounded=false;
 int x=0,z=0;
 float impact_horizontal=0,impact_vertical=0,heading=0;
 std::array<float,3> position{};
};
struct ThrowVictim135PresentationEvent {
 char kind=0;unsigned id=0;
 std::array<float,3> position{};float yaw=0,pitch=0;
};
struct ThrowVictim135Presentation {
 std::array<ThrowVictim135PresentationEvent,12> events{};unsigned count=0;
 unsigned state=135,phase=0,frame=0,second_frame=0;
 bool tail=false;
 BattleThrowVictim135Transition transition{};
 void push(char kind,unsigned id,std::array<float,3> position={},float yaw=0,float pitch=0){
  if(count==events.size())throw std::logic_error("State135 presentation event overflow");
  events[count++]={kind,id,position,yaw,pitch};
 }
};
inline ThrowVictim135Presentation advance_throw_victim135_presentation(
 BattleThrowVictim135& motion,const ThrowVictim135PresentationInput& in){
 ThrowVictim135Presentation out;out.phase=in.phase;out.frame=in.frame;out.second_frame=in.second_frame;
 if(in.blocked)return out;
 if(in.weapon>2)throw std::out_of_range("State135 weapon");
 if(in.frame==0){
  const unsigned slot=in.weapon==0?15u:in.weapon==1?23u:13u;
  auto origin=in.position;origin[1]+=85.f;
  out.push('W',slot,origin,in.heading+motion.heading_offset);
  out.push('W',slot+1,origin,in.heading+motion.heading_offset);
  out.push('C',0);out.push('Q',1);
 }
 out.push('C',0);out.push('Q',1);
 out.transition=advance_battle_throw_victim135(motion,in.frame,in.wall,in.grounded,
  in.x,in.z,in.impact_horizontal,in.impact_vertical);
 if(out.transition.state){
  out.state=out.transition.state;out.phase=out.frame=out.second_frame=0;
  if(out.state==113){
   out.push('P',10,in.position,in.heading);out.push('E',40);out.push('N',113);
  }else{
   out.push('N',119);out.push('E',40);
   out.push('P',300,in.position,in.heading);out.push('P',310,in.position,in.heading);
  }
  return out;
 }
 // The common handler tail increments AE04 and AE08 before 4212f0.
 out.tail=true;++out.frame;++out.second_frame;out.push('I',out.phase);
 if(out.frame>in.duration&&!in.hold&&out.phase+1<in.phase_count){
  ++out.phase;out.frame=out.second_frame=0;out.push('H',out.phase);
 }
 return out;
}
}
