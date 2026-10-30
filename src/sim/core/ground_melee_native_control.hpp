#pragma once
#include "roster_followup_control.hpp"
#include "roster_ground_melee.hpp"
#include "battle_attack300_motion.hpp"
namespace daybreak {
enum class GroundMeleeKind {Clear,Capacity,Activate,Statistics,Query,Sound,Voice,State,Phase,Projectile};
struct GroundMeleeNativeEvent {GroundMeleeKind kind{};int value=0,argument=0;};
struct GroundMeleeNativeInput : RosterFollowupControlInput {int rank=0;unsigned mine_clock=0;};
struct GroundMeleeNativeEffects {
 int next_state=-1,next_phase=-1,clock=1,tick_delta=0,tick2_delta=0,next_rank=-1;
 std::array<GroundMeleeNativeEvent,16> events{};unsigned count=0;
};
// Original state300 bodies for all46 bindings. Shared data does not imply
// shared scratch predicates, target thresholds, query order or steering.
inline GroundMeleeNativeEffects advance_ground_melee_native_control(RosterNativeScratch& scratch,
 RosterFollowupControlMotion& m,const GroundMeleeNativeInput& in){
 character_action_dispatch(in.character,in.weapon);
 if(in.state!=300)throw std::invalid_argument("Ground melee state300 required");
 GroundMeleeNativeEffects out;unsigned contact=in.contact&65535u;
 const unsigned ch=in.character,we=in.weapon,p=in.phase,f=in.frame;
 const bool first=p==0&&f==0;
 const auto event=[&](GroundMeleeKind kind,int value=0,int argument=0){out.events.at(out.count++)={kind,value,argument};};
 const auto state=[&](int value){event(GroundMeleeKind::State,value);out.next_state=value;out.clock=0;};
 const auto phase2=[&](){event(GroundMeleeKind::Phase,2);out.next_phase=2;out.clock=0;};
 const auto clear=[&](){event(GroundMeleeKind::Clear);contact=0;};
 const auto statistics=[&](){event(GroundMeleeKind::Activate,1);event(GroundMeleeKind::Statistics,1);};
 const auto query=[&](){event(GroundMeleeKind::Query,int(contact));return contact;};
 const auto guard=[&](){if(query()&2u){state(392);clear();return true;}return false;};
 const auto latch=[&](){if(query()!=0&&scratch.ec==0){scratch.ec=1;scratch.known|=2u;}};
 const auto turn=[&](float step){approach_battle_offset(m.offset,0,step);};
 const auto voice=[&](int id,int sound,double threshold){
  event(GroundMeleeKind::Sound,sound);
  const auto selected=in.distance_squared<threshold?battle_melee_voice(id,in.distance_squared,m.offset,in.voice_flags):BattleMeleeVoice{id,10};
  event(GroundMeleeKind::Voice,selected.id,selected.argument);
 };
 if(in.blocked){out.clock=0;return out;}
 if(in.complete){state(0);return out;}
 if(!in.grounded){state(43);if(ch!=2)m.gravity=.5f;if(ch==15){m.speed=std::min(m.speed,10.f);m.vertical=0;}return out;}
 if(first){
  if(ch==1||ch==7||ch==10||ch==12)statistics();
  m.movement=0;clear();event(GroundMeleeKind::Capacity,ch==15&&we==1?3:1);
  scratch.ec=0;scratch.known|=2u;
  if(ch!=0||we!=2){scratch.e8=(ch<3||ch==15)?1:0;scratch.known|=1u;}
  if(ch>=2&&ch<=14){scratch.f0=1;scratch.known|=4u;}
  if(ch==8&&we==2){scratch.f8=0;scratch.known|=16u;}
  if(ch==0)m.speed=we==2?0.f:in.distance_squared>=(we==1?810000.:640000.)?15.f:25.f;
  else if(ch==1)m.speed=in.distance_squared<360000.?(we==1?19.f:17.f):(we==1?15.f:14.f);
  else if(ch==2)m.speed=in.distance_squared<640000.?25.5f:15.5f;
  else if(ch==5)m.speed=in.distance_squared<640000.?27.5f:17.5f;
  else{const auto& profile=roster_ground_melee_profile(ch,we);m.speed=profile.far_distance_squared&&in.distance_squared>=profile.far_distance_squared?profile.far_speed:profile.close_speed;}
  if(ch==1)turn(180);
  if(ch!=1&&ch!=7&&ch!=10&&ch!=12)statistics();
 }
 if(ch==8&&we==2){
  if(query()!=0&&scratch.f8==0&&in.rank==1){event(GroundMeleeKind::Projectile,3);scratch.f8=0;scratch.known|=16u;out.next_rank=0;}
 }
 if(ch==1||ch==7||ch==10||ch==12){latch();if(guard())return out;}
 else{if(guard())return out;latch();}
 if(ch==15&&we==1&&query()!=0)clear();
 if(first&&ch!=1)turn(180);
 if(p<2){
  if(ch==0){if(!first&&(we!=2||p==0))turn(we==2?3.f:20.f);}
  else if(ch==1){if(scratch.e8==1)turn(we==1?5.f:4.f);}
  else if(ch==2)turn(20);
  else if(ch==15){if(!first)turn(20);}
  else if(ch==4&&we==2)turn(20);
  else if(ch==13){if(p==1)turn(7);else if(scratch.f0==1)turn(20);}
  else if(scratch.f0==1){
   float step=0;
   switch(ch){case 3:step=25;break;case 4:step=7;break;case 5:step=p==0?12.f:20.f;break;
    case 6:step=we==0?(p==0?12.f:20.f):15.f;break;case 7:step=we==1?7.f:(p==0?15.f:18.f);break;
    case 8:step=15;break;case 9:step=25;break;case 10:step=7;break;case 11:step=p==0?9.f:20.f;break;
    case 12:step=4;break;case 14:step=we==0?20.f:7.f;break;default:break;
   }turn(step);
  }
 }
 if(ch==5&&p==0&&scratch.f0==1)m.speed=std::max(17.5f,m.speed-.5f);
 if(p==1){
  bool exit=false;
  if(ch==0){exit=we!=2&&(in.distance_squared<90000.||scratch.e8==0||f>10);}
  else if(ch==1)exit=in.distance_squared<20000.||scratch.e8==0||f>15;
  else if(ch==2||ch==15)exit=in.distance_squared<90000.||scratch.e8==0||f>10;
  else if(ch==3){std::uint32_t increment=std::uint32_t(scratch.e8)+1u;std::memcpy(&scratch.e8,&increment,4);scratch.known|=1u;exit=in.distance_squared<(we==2?75000.:90000.)||scratch.f0==0||f>10;}
  else if(ch==4)exit=f>2&&(in.distance_squared<(we==2?40000.:25000.)||scratch.f0==0||f>(we==2?10u:20u));
  else if(ch==5)exit=in.distance_squared<40000.||scratch.f0==0||f>20;
  else if(ch==6)exit=(we==0||f>2)&&(in.distance_squared<90000.||scratch.f0==0);
  else if(ch==7||ch==8||ch==11)exit=in.distance_squared<90000.||scratch.f0==0;
  else if(ch==9)exit=m.speed>0&&(in.distance_squared<60000.||scratch.f0==0||f>20);
  else if(ch==10||ch==13)exit=in.distance_squared<60000.||scratch.f0==0;
  else if(ch==12)exit=scratch.f0==1&&in.distance_squared<60000.;
  else if(ch==14)exit=f>2&&(in.distance_squared<25000.||scratch.f0==0||f>20);
  if(exit){phase2();return out;}
 }
 const auto late_turn=[&](){
  if(ch==0&&we!=2&&f<4&&(we==0?scratch.e8>0:scratch.f0==1))turn(5);
  else if(ch==2&&f<4)turn(10);
  else if(ch==3&&f<10&&scratch.f0==1)turn(15);
  else if(ch==4&&f<3&&scratch.f0==1)turn(7);
  else if(ch==6&&f<8&&scratch.f0==1)turn(we==0?10.f:9.f);
  else if(ch==7&&f<12)turn(we==1?5.f:10.f);
  else if(ch==8&&f<9&&scratch.f0==1)turn(10);
  else if(ch==9&&f<6&&scratch.f0==1)turn(10);
  else if(ch==11&&f<8&&scratch.f0==1)turn(9);
  else if(ch==12&&f<5&&scratch.f0==1)turn(4);
  else if(ch==14&&f<7&&scratch.f0==1)turn(7);
  else if(ch==15&&f<4&&scratch.e8>0)turn(5);
 };
 if(ch==0&&we==2&&p==1){
  if(f==18)voice(3,67,90000.);
  BattleAttack300Motion state{1,f,0,std::uint32_t(scratch.e8),m.speed,m.offset};advance_battle_attack300(state);
  m.speed=state.speed;m.offset=state.offset;scratch.e8=int(state.moving);scratch.known|=1u;
  out.tick_delta=int(state.frame-f);out.tick2_delta=int(state.secondary_frame);
 }
 if(p==2){
  const bool turn_after_voice=ch==0||ch==4||ch==14||ch==15;
  if(!turn_after_voice)late_turn();
  if(ch==0){if(f==0)voice(1,we==0?60:64,90000.);m.speed=std::max(0.f,m.speed-1.5f);}
  else if(ch==1){if(f==0)voice(1,60,40000.);if(f==2){m.speed=0;m.turn=0;}}
  else if(ch==2){if(f==4)voice(1,60,90000.);m.speed=std::max(0.f,m.speed-1.5f);}
  else{
   const auto profile=roster_ground_melee_phase_profile(ch,we);
   const double threshold=ch==4||ch==5||ch==12||ch==14?40000.:ch==9||ch==10||ch==13?60000.:90000.;
   if(f==unsigned(profile.sound_frame))voice(1,profile.sound_id,threshold);
   if(int(f)==profile.boost_frame)m.speed=profile.boost_speed;
   if(int(f)==profile.stop_frame)m.speed=0;
   if(profile.slowdown_start>=0&&int(f)>=profile.slowdown_start)m.speed=std::max(0.f,m.speed-profile.slowdown);
   if(ch==5||(ch==13&&f==8))m.turn=0;
  }
  if(turn_after_voice)late_turn();
  if(((ch==9&&we!=0&&f>25)||(ch==13&&f>40&&(in.direction==3||in.direction==4)&&in.gauge>0))&&query()==0&&in.gauge>0){
   if(in.direction==3){state(24);return out;}
   if(in.direction==4){state(23);return out;}
  }
 }
 // Satoko1's normal tail resets F8; explicit state/phase returns skip it.
 const std::uint32_t tail_clock=in.mine_clock-1u;std::int32_t signed_tail_clock;std::memcpy(&signed_tail_clock,&tail_clock,4);
 if(ch==3&&we==1&&signed_tail_clock<0){scratch.f8=0;scratch.known|=16u;}
 return out;
}
} // namespace daybreak
