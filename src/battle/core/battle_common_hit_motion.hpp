#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <vector>

namespace daybreak {
// The live victim-state branches of 00428510. Collision, DAT phase selection
// and presentation are supplied by the caller; the handler owns their order.
struct BattleCommonHitMotion {
 unsigned state=0,phase=0,frame=0,second_frame=0,duration=0,phase_count=1;
 bool complete=false,hold_phase=false,grounded=false,wall_contact=false;
 std::uint8_t back_flag=0,first_voice=0;
 bool jump=false,melee=false,shoot=false;
 int x=0,z=0;
 float speed=0,vertical=0,gravity=0,movement=0,turn_step=0,offset=0,model_pitch=0;
 float impact_horizontal=0,impact_vertical=0;
 std::uint32_t scratch=0,status0=0,down=0,invincible=0,count=0,accum=0;
 int last_hit_owner=0;
 std::array<std::uint16_t,4> contacts{};
 std::array<std::int32_t,4> capacity{};
};
enum class CommonHitEventKind {state,phase,sound,voice,particle};
struct CommonHitEvent {CommonHitEventKind kind;int value=0,priority=0,choice=0;};
struct BattleCommonHitEffects {
 std::vector<CommonHitEvent> events;
 int next_state=-1,next_phase=-1;
 bool clock_advanced=false;
 unsigned steering_calls=0;
};
inline int common_hit_signed(std::uint32_t value){int result;std::memcpy(&result,&value,4);return result;}
inline bool battle_common_hit_motion_state(unsigned state){
 return state==45||(state>=100&&state<=108)||(state>=113&&state<=116)||
  (state>=118&&state<=121)||state==130||state==131||state==133||state==134||
  state==188||state==189||(state>=200&&state<=206)||
  (state>=213&&state<=216)||state==221||state==230||state==231||state==233||state==234;
}
inline BattleCommonHitEffects advance_battle_common_hit_motion(BattleCommonHitMotion& s){
 s.last_hit_owner=-1; //Common entry clears actor+7d4, independently of state.
 BattleCommonHitEffects e;
 auto state=[&](unsigned value){e.next_state=int(value);e.events.push_back({CommonHitEventKind::state,int(value)});};
 auto phase=[&](unsigned value){e.next_phase=int(value);e.events.push_back({CommonHitEventKind::phase,int(value)});};
 auto sound=[&](unsigned id){e.events.push_back({CommonHitEventKind::sound,int(id)});};
 auto voice=[&](unsigned id,unsigned priority=20,unsigned choice=0){e.events.push_back({CommonHitEventKind::voice,int(id),int(priority),int(choice)});};
 auto particle=[&](unsigned id){e.events.push_back({CommonHitEventKind::particle,int(id)});};
 auto ground_voice=[&](){if(s.state>=200&&s.back_flag==1)voice(6,25,1);else voice(8);};
 auto flight_voice=[&](){
  if(s.state==115||s.state==215){voice(9);s.first_voice=true;}
  else if(s.state>=200&&s.back_flag==1)voice(6,25,1);
  else if(!s.first_voice){voice(9);s.first_voice=true;}else voice(8);
 };
 auto settle=[&](){
  if(s.speed>0){s.speed-=.25f;if(s.speed<0)s.speed=0;}
  if(s.speed<0){s.speed+=.25f;if(s.speed>0)s.speed=0;}
 };
 const bool first=s.phase==0&&s.frame==0;
 const int frame=common_hit_signed(s.frame);
 switch(s.state){
 case 45:
  if(s.complete){state(0);return e;}
  if(s.frame==0){voice(23);s.invincible=s.count=s.down=s.accum=0;}
  if(frame<26){s.vertical-=1.f;if(s.speed< -10.f)s.speed+=.5f;}else s.vertical=0;
  if(s.frame==0){s.movement=0;s.speed=-25.f;s.vertical=12.5f;}
  if(s.frame==25&&!s.grounded)return e;
  if(s.frame==26)s.speed=0;
  break;
 case 100:case 101:case 102:case 200:case 201:case 202:
  if(s.complete){state(0);return e;}
  if(!s.grounded){
   if(s.state==202){state(103);return e;}
   s.vertical=0;
   if(s.state>=200){s.gravity=.3f;state(203);}else state(103);
   return e;
  }
  if(s.frame==0){ground_voice();s.movement=s.turn_step=0;s.speed=(s.state>=200?1.f:-1.f)*((s.state==102||s.state==202)?20.f:25.f);}
  if(s.state<200){s.speed+=(s.state==102?.5f:1.5f);if(s.speed>0)s.speed=0;}
  else {s.speed-=(s.state==202?.5f:1.5f);if(s.speed<0)s.speed=0;}
  break;
 case 103:case 203:
  if(first)s.vertical=0;
  if(s.speed>5.f){s.speed-=.25f;if(s.speed<5.f)s.speed=5.f;}
  if(s.speed< -5.f){s.speed+=.25f;if(s.speed> -5.f)s.speed=-5.f;}
  s.gravity=.3f;s.vertical-=s.gravity;
  if(s.grounded&&s.vertical<0){s.vertical=0;state(s.state==103?118:119);return e;}
  break;
 case 104:case 204:
  if(s.complete){state(0);return e;}
  if(!s.grounded&&common_hit_signed(s.phase)>0){if(s.state==104)s.vertical=0;state(s.state==104?103:203);return e;}
  if(first){voice(31);sound(33);s.movement=s.speed=0;}
  if(s.phase==0&&frame>60){phase(1);s.speed=s.state==104?-15.f:15.f;return e;}
  if(s.state==104){s.speed+=1.5f;if(s.speed>0)s.speed=0;}
  else {s.speed-=1.5f;if(s.speed<0)s.speed=0;}
  break;
 case 105:case 205:
  if(first){voice(31);sound(33);s.movement=s.speed=s.vertical=0;}
  if(s.phase==0&&frame>60){phase(1);s.speed=(s.state==105?-s.impact_horizontal:s.impact_horizontal)*.01f;s.vertical=s.impact_vertical*.01f;s.gravity=.3f;return e;}
  if(s.state==105&&s.phase==1&&s.frame==0)s.gravity=.3f;
  if(s.grounded&&s.vertical<0&&common_hit_signed(s.phase)>0){
   s.vertical=0;state(s.state==105?118:119);sound(40);particle(300);particle(310);return e;
  }
  if(common_hit_signed(s.phase)>0)s.vertical-=s.gravity;
  if(s.state==105){if(s.speed< -4.f)s.speed+=.25f;}else if(s.speed>4.f)s.speed-=.25f;
  break;
 case 106:case 206:
  if(s.frame==0){voice(11,20,1);sound(36);s.movement=s.speed=s.turn_step=0;s.vertical=9.f;s.gravity=.6f;}
  if(!s.status0){state(43);return e;}
  if(s.grounded&&s.vertical<0){if(s.state==106){state(107);s.vertical=0;}else{s.vertical=0;state(107);}return e;}
  s.vertical-=s.gravity;if(s.speed>0)s.speed=0;
  break;
 case 107:
  if(!s.status0){state(0);return e;}
  if(!s.grounded){state(108);s.vertical=0;return e;}
  if(s.frame==0){s.movement=s.turn_step=0;}
  s.turn_step=2.f;
  //421780 steering is applied by the adapter at this event's original point.
  ++e.steering_calls;
  s.speed=20.f;
  break;
 case 108:
  if(!s.status0){state(43);return e;}
  if(s.grounded){state(107);s.vertical=0;return e;}
  if(s.frame==0){s.gravity=.5f;s.vertical=s.turn_step=0;}
  s.vertical-=s.gravity;if(s.speed>10.f)s.speed=10.f;
  break;
 case 113:case 114:case 115:case 116:
 case 213:case 214:case 215:case 216:
  if(first){
   //216 intentionally uses the front sign, as in native0042a89e.
   flight_voice();s.movement=s.turn_step=0;
   s.speed=((s.state<200||s.state==216)?-s.impact_horizontal:s.impact_horizontal)*.01f;
   s.vertical=s.impact_vertical*.01f;s.gravity=(s.state==116||s.state==216)?1.f:.3f;
  }
  if(s.grounded&&s.vertical<0){
   if(s.state<200&&common_hit_signed(s.down)<100&&s.jump){state(45);s.invincible=1;s.vertical=s.speed=0;return e;}
   // Front115 clears vertical before its particle calls; other front states
   // and the back states have their own original ordering.
   if(s.state==115||s.state>=200)s.vertical=0;
   particle(300);particle(310);s.vertical=0;state(s.state<200?118:119);sound(40);return e;
  }
  if(s.vertical<6.f&&s.phase==1&&(s.state!=115||frame%17==0)){phase(2);return e;}
  s.vertical-=s.gravity;
  if(s.state==213||s.state==214||s.state==215){if(s.speed>4.f)s.speed-=(s.state==214?.5f:.25f);}
  else if(s.speed< -4.f)s.speed+=(s.state==114?.5f:.25f);
  if(s.phase==3&&s.state!=115&&s.state!=215)return e;
  break;
 case 118:case 119:case 120:case 121:case 221:case 134:case 234:
  if(s.complete){state(s.state==120?((s.x||s.z)?124:128):120);return e;}
  if(!s.grounded){
   if(s.state==134){s.vertical=0;s.gravity=.5f;state(103);return e;}
   if(s.state==234){state(203);return e;}
   s.vertical=0;state(s.speed<=0?103:203);return e;
  }
  if((s.state==121||s.state==221)&&s.frame==0){voice(8);s.speed=(s.state==121?-s.impact_horizontal:s.impact_horizontal)*.01f;}
  if((s.state==134||s.state==234)&&s.frame==0){s.movement=s.turn_step=0;s.speed=s.state==134?-20.f:20.f;}
  if(s.state==134){s.speed+=.5f;if(s.speed>0)s.speed=0;}
  else if(s.state==234){s.speed-=.5f;if(s.speed<0)s.speed=0;}
  else settle();
  break;
 case 130:case 131:case 230:case 231:
  if(s.complete){state(0);return e;}
  if(!s.grounded){state(103);s.vertical=0;return e;}
  if(s.frame==0){ground_voice();s.movement=s.speed=s.turn_step=0;}
  s.speed+=1.f;if(s.speed>0)s.speed=0;
  break;
 case 133:case 233:
  if(first){s.movement=0;s.contacts.fill(0);s.capacity.fill(1);s.speed=(s.state==133?-s.impact_horizontal:s.impact_horizontal)*.01f;s.turn_step=0;s.vertical=s.impact_vertical*.01f;s.gravity=.3f;s.scratch=0;}
  if(s.grounded&&s.vertical<0){
   s.vertical=0;s.speed*=.5f;state(s.state==133?118:119);sound(40);particle(300);particle(310);return e;
  }
  if(common_hit_signed(s.phase)<2){
   ++s.scratch;
   if(common_hit_signed(s.scratch)>59){phase(2);s.scratch=0;return e;}
   if(s.wall_contact){particle(10);sound(40);state(113);s.impact_horizontal=s.state==133?20.f:-20.f;s.impact_vertical=6.f;s.model_pitch=0;return e;}
  }
  if(s.phase==2){
   s.gravity=.3f;
   if(s.state==133){s.speed+=.25f;if(s.speed> -4.f)s.speed=-4.f;}
   else {s.speed-=.25f;if(s.speed<4.f)s.speed=4.f;}
   s.vertical-=s.gravity;
  }
  break;
 case 188:
  if(frame<40){s.frame=s.second_frame=40;return e;}
  if(s.frame==55){--s.frame;--s.second_frame;}
  break;
 case 189:s.frame=s.second_frame=17;return e;
 default:break;
 }
 ++s.frame;++s.second_frame;e.clock_advanced=true;
 if(common_hit_signed(s.duration)<common_hit_signed(s.frame)&&!s.hold_phase)phase(s.phase+1);
 return e;
}
}
