#pragma once
#include "battle_ground_dash.hpp"
#include "character_dispatch.hpp"
namespace daybreak {
inline BattleGroundDashTuning roster_forward_dash_tuning(unsigned character,unsigned weapon,bool boosted=false){
 character_action_dispatch(character,weapon);
 struct Profile{unsigned character,weapon;int drain;float speed,brake,turn;bool reset;unsigned hold_frame,hold_limit,period,first,second;int last;};
 static constexpr Profile profiles[]={
 {0,0,12,17.0f,0.75f,4.0f,true,1,15,22,6,17,-1},
 {0,1,12,16.5f,0.75f,4.0f,true,1,15,22,6,17,-1},
 {0,2,12,30.0f,2.5f,4.0f,true,1,15,0,0,0,5},
 {1,0,8,14.0f,0.5f,4.0f,false,1,15,22,6,17,-1},
 {1,1,8,15.0f,0.5f,4.0f,false,1,15,22,6,17,-1},
 {1,2,10,14.0f,0.5f,4.0f,false,1,15,22,6,17,-1},
 {2,0,10,15.0f,0.75f,4.0f,true,1,15,22,6,17,-1},
 {2,1,10,15.0f,0.75f,4.0f,true,1,15,22,6,17,-1},
 {2,2,10,15.0f,0.75f,4.0f,true,1,15,22,6,17,-1},
 {3,0,11,17.0f,0.65f,5.5f,true,5,10,22,6,17,-1},
 {3,1,11,17.0f,0.65f,5.5f,true,5,10,22,6,17,-1},
 {3,2,13,14.0f,0.65f,3.0f,true,5,10,22,6,17,-1},
 {4,0,6,10.0f,0.4f,4.0f,true,3,15,48,24,47,-1},
 {4,1,6,10.0f,0.4f,4.0f,true,3,15,48,24,47,-1},
 {4,2,9,16.5f,0.4f,4.0f,true,3,15,48,24,47,-1},
 {5,0,14,20.0f,1.0f,5.0f,true,1,10,22,6,17,-1},
 {5,1,14,20.0f,1.0f,5.0f,true,1,10,22,6,17,-1},
 {5,2,14,20.0f,1.0f,5.0f,true,1,10,22,6,17,-1},
 {6,0,11,16.25f,0.75f,4.0f,true,4,15,22,6,17,-1},
 {6,1,13,16.0f,0.75f,4.0f,true,4,15,22,6,17,-1},
 {6,2,13,16.25f,0.75f,4.0f,true,4,15,22,6,17,-1},
 {7,0,8,13.5f,0.5f,4.0f,true,1,15,22,6,17,-1},
 {7,1,8,13.5f,0.5f,4.0f,true,1,15,22,6,17,-1},
 {7,2,8,13.5f,0.5f,4.0f,true,1,15,22,6,17,-1},
 {8,0,11,11.5f,0.5f,4.0f,true,5,15,36,13,31,-1},
 {8,1,11,11.5f,0.5f,4.0f,true,5,15,36,13,31,-1},
 {8,2,11,11.5f,0.5f,4.0f,true,5,15,36,13,31,-1},
 {9,0,10,15.5f,0.75f,4.0f,true,4,15,22,6,17,-1},
 {9,1,8,15.5f,0.75f,4.0f,true,4,15,22,6,17,-1},
 {9,2,8,15.5f,0.75f,4.0f,true,4,15,22,6,17,-1},
 {10,0,9,13.0f,0.5f,4.0f,true,2,15,36,12,30,-1},
 {10,1,9,13.0f,0.5f,4.0f,true,2,15,36,12,30,-1},
 {10,2,9,13.0f,0.5f,4.0f,true,2,15,36,12,30,-1},
 {11,0,14,22.5f,1.0f,0.25f,true,6,15,0,0,0,-1},
 {11,1,14,22.5f,1.0f,0.25f,true,6,15,0,0,0,-1},
 {11,2,14,22.5f,1.0f,0.25f,true,6,15,0,0,0,-1},
 {12,0,10,12.5f,0.5f,4.0f,true,2,15,22,6,17,-1},
 {12,1,10,12.5f,0.5f,4.0f,true,2,15,22,6,17,-1},
 {12,2,10,12.5f,0.5f,4.0f,true,2,15,22,6,17,-1},
 {13,0,15,22.5f,1.0f,6.0f,false,1,10,22,6,17,-1},
 {13,1,15,22.5f,1.0f,6.0f,false,1,10,22,6,17,-1},
 {13,2,15,22.5f,1.0f,6.0f,false,1,10,22,6,17,-1},
 {14,0,9,14.5f,0.4f,5.0f,true,3,15,0,0,0,-1},
 {14,1,10,13.5f,0.4f,8.0f,false,3,15,0,0,0,-1},
 {15,0,12,17.0f,0.75f,4.0f,true,1,15,22,6,17,-1},
 {15,1,12,17.0f,0.75f,4.0f,true,1,15,22,6,17,-1}
 };
 for(const auto& p:profiles)if(p.character==character&&p.weapon==weapon){BattleGroundDashTuning t;t.drain=p.drain;t.forward=p.speed;t.forward_brake=p.brake;t.forward_turn=p.turn;t.reset_forward=p.reset;t.forward_hold_frame=p.hold_frame;t.forward_hold_limit=p.hold_limit;t.footstep_sounds=p.period!=0;t.foot_period=p.period?p.period:1;t.foot_first=p.first;t.foot_second=p.second;t.forward_last_tick=p.last;if(character==11)t.forward_initial_effect=2;if(character==14&&weapon==1&&boosted){t.forward=15.5f;t.drain=7;}return t;}
 throw std::invalid_argument("Unknown forward dash configuration");
}
}
