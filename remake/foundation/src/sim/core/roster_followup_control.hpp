#pragma once
#include "battle_steering.hpp"
#include "battle_melee_voice.hpp"
#include "roster_native_scratch.hpp"
#include <array>
#include <algorithm>
#include <stdexcept>
namespace daybreak {
// Original slot6 bodies301/302 for the37 shared roster bindings. DAT presence
// does not imply a dedicated body: Tomitake302 uses the common handler.
inline bool roster_followup_control_state(unsigned ch,unsigned weapon,unsigned state){
 if(ch<3||ch>15)return false;
 if(state==301)return true;
 if(state!=302)return false;
 return (ch==4&&weapon==2)||ch==5||ch==9||ch==11||ch==13||(ch==14&&weapon==1)||ch==15;
}
struct RosterFollowupControlInput {
 unsigned character=3,weapon=0,state=301,phase=0,frame=0,contact=0;
 bool complete=false,grounded=true,blocked=false;
 double distance_squared=0;
 std::array<unsigned char,3> voice_flags{};
 int direction=0,gauge=0; // actor+830 double-tap command, +834 boost gauge.
};
struct RosterFollowupControlMotion {
 float speed=0,offset=0,movement=0,vertical=0,gravity=0,turn=0;
 int contact_mode=0;
};
enum class FollowupControlKind {Clear,Capacity,Activate,Statistics,Query,Sound,Voice,State,Phase};
struct FollowupControlEvent {FollowupControlKind kind{};int value=0,argument=0;};
struct RosterFollowupControlEffects {
 int next_state=-1,next_phase=-1,clock=1;
 std::array<FollowupControlEvent,16> events{};unsigned count=0;
};
// Admission, callback order and motion writes follow the native bodies, rather
// than overlaying speed tables on Keiichi's different contact/turn program.
inline RosterFollowupControlEffects advance_roster_followup_control(RosterNativeScratch& scratch,
 RosterFollowupControlMotion& m,const RosterFollowupControlInput& in){
 if(!roster_followup_control_state(in.character,in.weapon,in.state))throw std::invalid_argument("No dedicated roster followup body");
 RosterFollowupControlEffects out;unsigned contact=in.contact;
 const auto event=[&](FollowupControlKind k,int value=0,int argument=0){out.events.at(out.count++)={k,value,argument};};
 const auto next_state=[&](int n){event(FollowupControlKind::State,n);out.next_state=n;out.clock=0;};
 const auto clear=[&](){event(FollowupControlKind::Clear);contact=0;};
 const auto capacity=[&](int n=1){event(FollowupControlKind::Capacity,n);};
 const auto statistics=[&](){event(FollowupControlKind::Activate,1);event(FollowupControlKind::Statistics,1);};
 const auto query=[&](){event(FollowupControlKind::Query,int(contact&65535u));return contact;};
 const auto guard=[&](){if(query()&2u){next_state(392);clear();return true;}return false;};
 const auto sound=[&](int id,int mode=0){event(FollowupControlKind::Sound,id,mode);};
 const auto voice=[&](int id,int priority=10){event(FollowupControlKind::Voice,id,priority);};
 const auto set_speed=[&](float speed,bool stop_turn=true){m.speed=speed;if(stop_turn)m.turn=0;};
 const auto brake=[&](float step,bool stop_turn=false){m.speed=std::max(0.f,m.speed-step);if(stop_turn)m.turn=0;};
 const unsigned ch=in.character,we=in.weapon,f=in.frame,p=in.phase;
 if(in.blocked){out.clock=0;return out;}
 if(in.complete){next_state(0);return out;}
 if(!in.grounded){next_state(43);m.gravity=.5f;if(ch==15){m.speed=std::min(m.speed,10.f);m.vertical=0;}return out;}
 if(ch==14&&we==1&&in.state==302){
  if(p==0&&f==0){
   m.movement=0;clear();capacity();scratch.e8=scratch.ec=0;scratch.f0=1;scratch.known|=7u;
   m.speed=in.distance_squared<640000.?22.5f:20.f;approach_battle_offset(m.offset,0,180);
   statistics();
  }
  if(guard())return out;
  if((query()&65535u)!=0&&scratch.ec==0){scratch.ec=1;scratch.known|=2u;}
  if(p<2&&scratch.f0==1)approach_battle_offset(m.offset,0,7);
  if(p==1&&f>2&&(in.distance_squared<40000.||f>20||scratch.f0==0)){
   out.next_phase=2;event(FollowupControlKind::Phase,2);out.clock=0;return out;
  }
  if(p==2){
   if(f==7){sound(60);const auto v=in.distance_squared<40000.?battle_melee_voice(1,in.distance_squared,m.offset,in.voice_flags):BattleMeleeVoice{1,10};voice(v.id,v.argument);}
   if(f>12)brake(4);
   if(f<7&&scratch.f0==1)approach_battle_offset(m.offset,0,7);
  }
  return out;
 }
 if(scratch.ec!=0){
  m.contact_mode=2;
  unsigned end=10;float step=15;
  if(in.state==301){
   switch(ch){
    case 3:end=8;step=20;break;case 4:end=12;step=10;break;
    case 5:end=7;break;case 6:end=15;break;case 7:end=8;step=we==1?10.f:20.f;break;
    case 8:end=10;step=20;break;case 9:end=8;step=20;break;
    case 10:end=12;break;case 11:end=6;step=25;break;
    case 12:end=8;step=20;break;case 13:end=8;step=25;break;
    case 14:end=12;step=10;break;case 15:end=12;step=20;break;
   }
  }else if(ch==4){end=12;step=10;}else if(ch==15){end=12;step=20;}
  if(f<end){if(ch==5&&in.state==302)m.speed=0;approach_battle_offset(m.offset,0,step);}
  if(ch==7&&f>16&&f<28)approach_battle_offset(m.offset,0,we==1?10.f:15.f);
 }
 if(in.state==301){
  // Takano/Kasai admission is phase0 only; Irie intentionally admits each
  // frame-zero visit. The other bodies reset contacts before recording stats.
  if(ch==7||ch==10||ch==12){
   if(f==0&&(ch==10||p==0)){statistics();m.movement=0;m.speed=15;clear();capacity();}
  }else{
   if(f==0){m.movement=0;clear();capacity(ch==15&&we==1?3:1);
    if(ch==3||ch==4||ch==6||ch==13||ch==14)m.speed=0;
    if(ch==9)m.speed=20;
   }
   if(p==0&&f==0)statistics();
  }
  // These native writes precede the guard query, including their clear.
  if(ch==6&&f==14){m.movement=0;clear();capacity();m.speed=15;}
  if(ch==6&&f>14)brake(.75f);
  if(ch==7){
   if(f==19)m.speed=10;
   if(f==28){event(FollowupControlKind::Statistics,1);m.movement=0;clear();capacity();sound(62);}
   if(f==33)m.speed=0;
   if(f==37)set_speed(0);
  }
  if(ch==10){if(f==11){sound(61);voice(2);}if(f==14)set_speed(0);}
  if(ch==12&&f==7){m.movement=0;clear();capacity();m.speed=10;}
  if(ch==12){if(f==8){sound(61);voice(2);}if(f==15)set_speed(0);}
  if(guard())return out;
  if(ch==15&&we==1&&(query()&65535u)!=0)clear();
  switch(ch){
   case 3:if(f==8){sound(61);voice(3);}if(f==13)set_speed(20);if(f==34){set_speed(0);sound(40,1);}break;
   case 4:if(f==8){sound(62,1);voice(2);}if(f==6)set_speed(we==2?25.f:15.f);
    if(we==2){if(f>=17)brake(4,true);}else if(f==17)set_speed(0);break;
   case 5:if(f==4){sound(61);voice(2);}if(f==0)set_speed(30);if(f==6)set_speed(0);break;
   case 6:if(f==15){sound(61);voice(3);}break;
   case 7:if(f<19){brake(1);if(f==4){sound(61);voice(2);}}break;
   case 8:if(f==18){sound(62);voice(3);}if(f==12)set_speed(25);if(f==24)set_speed(0);break;
   case 9:if(f==9){sound(61);voice(2);}if(f==6)m.speed=0;break;
   case 10:if(f<14)brake(1);break;
   case 11:if(f==6){sound(61);voice(28);}if(f==0)set_speed(30);if(f==8)set_speed(0);break;
   case 12:break;
   case 13:if(f==9){sound(61);voice(2);}if(f==8)set_speed(30);if(f==14)set_speed(0);break;
   case 14:if(f==8){sound(62,1);voice(2);}if(f==12)set_speed(we==0?22.5f:18.5f);if(f>=17)brake(we==0?2.f:1.5f,true);break;
   case 15:if(f==12){sound(61);voice(2);}if(f==10)set_speed(25);if(f==17)set_speed(0);break;
  }
 }else{
  if(ch==4){if(f==0){m.speed=0;m.movement=0;clear();capacity();}if(p==0&&f==0)statistics();}
  else{
   if(p==0&&f==0){statistics();if(ch==9)m.speed=15;}
   if(f==0){m.movement=0;clear();capacity();if(ch==13)m.speed=0;}
  }
  if(ch==4){if(f==13){set_speed(25);sound(63,1);voice(3);}if(f>=23)brake(4,true);}
  if(guard())return out;
  switch(ch){
   case 4:break;
   case 5:if(f==12){sound(62);voice(3);set_speed(30);}if(f==20)set_speed(0);break;
   case 9:if(f==10){sound(62);voice(3);}if(f==12)set_speed(0);break;
   case 11:if(f==18){sound(62);voice(29);}if(f==7)set_speed(30);if(f==19)set_speed(0);break;
   case 13:if(f==10){sound(62);voice(3);}if(f==1)set_speed(15);if(f==14)set_speed(0);
    if(f>40&&in.gauge>0&&(in.direction==3||in.direction==4)){
     if((query()&65535u)==0){next_state(in.direction==3?24:23);return out;}
    }break;
   case 15:if(f==17){sound(62);voice(3);}if(f<10)m.speed=0;if(f==10)set_speed(25);if(f==22)set_speed(0);break;
  }
 }
 return out;
}
} // namespace daybreak
