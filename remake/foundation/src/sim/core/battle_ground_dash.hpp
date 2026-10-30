#pragma once
#include "battle_steering.hpp"
#include <array>
#include <algorithm>
#include <stdexcept>
namespace daybreak {
// 41dcb0 seeds fifteen zero input frames.41efe0 appends, pops oldest, then
// scans independently in forward/back/left/right order; later matches win.
struct BattleDashHistory {
 std::array<std::array<int,2>,15> frames{};
 unsigned push(int x,int z){
  std::move(frames.begin()+1,frames.end(),frames.begin());frames.back()={x,z};
  unsigned command=0;
  for(unsigned dir=1;dir<=4;++dir){
   const unsigned axis=dir<=2?1:0;const int sign=(dir==1||dir==3)?-1:1;unsigned stage=0;
   for(const auto& f:frames){if(f[axis]==sign&&stage==2)command=dir;else if(f[axis]==0&&stage==1)stage=2;else if(f[axis]==sign&&stage==0)stage=1;}
  }
  return command;
 }
};
inline bool battle_ground_dash_state(unsigned state){return state==20||state==23||state==24||state==27||state==28;}
struct BattleGroundDash {
 unsigned state=20,phase=0,frame=0,hold_ticks=0;int gauge=1000,x=0,z=0;
 bool complete=false,grounded=true;float speed=0,offset=0,movement=0,height=0,turn_step=0;
};
struct BattleGroundDashStep {int state=-1,phase=-1,effect=-1;bool hold_clock=false;unsigned extra_ticks=0,step_count=0;};
struct BattleGroundDashTuning {
 int drain=10;float forward=15,side=20,back=14.5f,forward_brake=.75f,side_brake=.5f,side_min=13,side_stop=.95f,back_stop=1.25f;
 bool reset_forward=true,extra_side_ticks=true;
 unsigned side_tick_period=10;int forward_last_tick=-1;bool footstep_sounds=true;int extra_side_phase=-1;bool reset_back=true;float forward_turn=4;unsigned forward_hold_frame=1,forward_hold_limit=15,foot_period=22,foot_first=6,foot_second=17;int forward_initial_effect=-1;
};
inline BattleGroundDashTuning mion_ground_dash_tuning(unsigned weapon){
 if(weapon>2)throw std::invalid_argument("Mion dash weapon");
 return {weapon==2?10:8,weapon==1?15.f:14.f,weapon==1?19.f:18.f,weapon==0?15.f:weapon==1?14.f:13.f,.5f,.5f,12.f,.7f,1.f,false,false};
}
// Common Keiichi ground dash bodies in46a190/473610/47b940.
inline BattleGroundDashStep advance_battle_ground_dash(BattleGroundDash& s,const BattleGroundDashTuning& tuning={}){
 if(!battle_ground_dash_state(s.state))throw std::invalid_argument("Ground dash state");
 BattleGroundDashStep out;
 if(s.complete){out.state=s.state==20?(!s.grounded?43:0):s.state==23?0:s.height>10?43:0;return out;}
 if(!s.grounded){out.state=s.state==20?30:43;return out;}
 if(s.phase<2){s.gauge=std::max(0,s.gauge-tuning.drain);if(s.state==23||s.state==24)approach_battle_offset(s.offset,0,20);}
 if(s.state==20){
  if(s.phase==1&&tuning.footstep_sounds){if(s.frame%tuning.foot_period==tuning.foot_first)out.effect=5;if(s.frame%tuning.foot_period==tuning.foot_second)out.effect=6;}
  if(s.phase==0&&s.frame==0){s.movement=s.offset=0;s.speed=tuning.forward;s.hold_ticks=0;out.effect=tuning.forward_initial_effect;}
  if(s.phase==1){s.turn_step=tuning.forward_turn;if(tuning.reset_forward)s.speed=tuning.forward;steer_battle_offset(s.offset,s.x,s.z,tuning.forward_turn);if(tuning.forward_last_tick>=0?int(s.frame)>tuning.forward_last_tick:((!s.x&&!s.z)||s.gauge<1)){out.phase=2;return out;}}
  if(s.phase==2){s.turn_step=0;s.speed=std::max(0.f,s.speed-tuning.forward_brake);if(s.frame==tuning.forward_hold_frame&&s.hold_ticks<tuning.forward_hold_limit){++s.hold_ticks;out.hold_clock=true;}}
 }else if(s.state==23||s.state==24){
  const float direction=s.state==23?-90.f:90.f;
  if(s.phase==0&&s.frame==0){++out.step_count;s.offset=0;s.movement=direction;s.speed=tuning.side;}
  if(s.phase==1)s.movement=direction;
  if(s.phase<2)s.speed=std::max(tuning.side_min,s.speed-tuning.side_brake);
  if(s.phase==2)s.speed=std::max(0.f,s.speed-tuning.side_stop);
  if(tuning.extra_side_ticks&&(tuning.extra_side_phase<0||s.phase==unsigned(tuning.extra_side_phase))&&s.frame%tuning.side_tick_period==0)out.extra_ticks=1;
 }else {
  if(s.phase==0&&s.frame==0){++out.step_count;s.offset=0;s.movement=180;s.speed=tuning.back;}
  if(s.phase==1){s.turn_step=0;if(tuning.reset_back)s.speed=tuning.back;s.movement=180;}
  if(s.phase==2)s.speed=std::max(0.f,s.speed-tuning.back_stop);
 }
 return out;
}
}
