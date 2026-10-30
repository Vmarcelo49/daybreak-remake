#pragma once
#include "battle_damage_scaling.hpp"
#include <vector>
#include <stdexcept>
namespace daybreak {
enum class HanyuuTimeStopEventKind {Activate,TrailOff,Voice,AlternateVoice,Sound,TimeStop,State,Phase};
struct HanyuuTimeStopEvent {HanyuuTimeStopEventKind kind;int value=0,argument=0;};
struct HanyuuTimeStopBody {
 unsigned state=350,phase=0,primary=0,secondary=0,e8=0,ec=0,f0=0;
 float speed=0,vertical=0,gravity=0,movement=0;
};
struct HanyuuTimeStopEffects {bool tail=false;unsigned cursor_frame=0;std::vector<HanyuuTimeStopEvent> events;};
// Original5cb6a0 State350/360, including the two independent AE04/AE08
// rewinds at16 and the no-clock hold at33. 4221e0 writes+828, never+a0.
inline HanyuuTimeStopEffects advance_hanyuu_time_stop_body(HanyuuTimeStopBody& s,
 bool complete,unsigned lower_duration,bool hold,unsigned stop=0){
 HanyuuTimeStopEffects out;if(stop)return out;
 if(s.state!=350&&s.state!=360)throw std::invalid_argument("Invalid Hanyuu time-stop State");
 auto emit=[&](HanyuuTimeStopEventKind kind,int value=0,int argument=0){out.events.push_back({kind,value,argument});};
 if(complete){s.state=s.state==350?0:43;emit(HanyuuTimeStopEventKind::State,int(s.state));s.primary=s.secondary=s.phase=0;return out;}
 if(s.primary==0){
  emit(HanyuuTimeStopEventKind::Activate);s.movement=0;
  if(s.state==360)emit(HanyuuTimeStopEventKind::AlternateVoice,32,20);
  emit(HanyuuTimeStopEventKind::TrailOff);s.speed=s.vertical=0;
  if(s.state==360)s.gravity=.5f;
  s.e8=s.ec=s.f0=0;
  if(s.state==350)emit(HanyuuTimeStopEventKind::Voice,32,15);
 }
 if(s.primary==25){emit(HanyuuTimeStopEventKind::Sound,216);emit(HanyuuTimeStopEventKind::TimeStop,360);}
 if(s.primary==16){++s.e8;if(damage_signed(s.e8)<70){--s.primary;--s.secondary;return out;}s.e8=0;}
 if(s.primary==33){++s.e8;if(damage_signed(s.e8)<(s.state==350?10:30))return out;s.e8=0;}
 ++s.primary;++s.secondary;out.tail=true;out.cursor_frame=s.primary;
 if(damage_signed(lower_duration)<damage_signed(s.primary)&&!hold){
  ++s.phase;s.primary=s.secondary=0;emit(HanyuuTimeStopEventKind::Phase,int(s.phase));
 }
 return out;
}
}
