#pragma once
#include "battle_steering.hpp"
#include <algorithm>
namespace daybreak {
// Keiichi state30: all three weapon handlers have the same body.
struct BattleAirDash {unsigned phase=0,frame=0,hold_ticks=0;int gauge=1000,x=0,z=0;bool held=false,grounded=false,complete=false;float speed=0,vertical=0,turn=0,offset=0,gravity=0,movement=0;};
struct BattleAirDashStep {int state=-1,phase=-1,effect=-1;};
inline BattleAirDashStep advance_battle_air_dash(BattleAirDash& s,float dash_speed=15.5f,int drain=9,bool clear_landing_gravity=false,float turn_step=2.f,unsigned drain_phases=3,bool reset_speed=true){
 BattleAirDashStep out;
 if(s.complete){s.gravity=.5f;out.state=43;return out;}
 if(s.phase<drain_phases){s.gauge-=drain;if(s.phase<2){if(s.held){s.vertical=std::min(8.f,s.vertical+.5f);s.gauge-=3;}else s.vertical=std::max(0.f,s.vertical-.5f);}s.gauge=std::max(0,s.gauge);}
 if(s.phase==0&&s.frame==0){s.speed=dash_speed;s.vertical=0;s.turn=60;s.hold_ticks=0;s.movement=0;}
 if(s.phase==1&&s.frame==0&&s.hold_ticks==0)out.effect=2;
 if(s.phase==1){s.turn=turn_step;if(reset_speed)s.speed=dash_speed;++s.hold_ticks;if(s.hold_ticks>5&&((!s.x&&!s.z)||s.gauge<1)){out.phase=2;return out;}}
 if(s.phase==2){s.gravity=.5f;s.vertical-=s.gravity;if(s.grounded){if(clear_landing_gravity)s.gravity=0;s.vertical=0;out.state=44;return out;}}
 steer_battle_offset(s.offset,s.x,s.z,s.turn);return out;
}
}
