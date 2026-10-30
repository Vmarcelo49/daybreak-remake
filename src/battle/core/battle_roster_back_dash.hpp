#pragma once
#include "battle_ground_dash.hpp"
#include "character_dispatch.hpp"
namespace daybreak {
inline BattleGroundDashTuning roster_back_dash_tuning(unsigned character,unsigned weapon,bool boosted=false){
 character_action_dispatch(character,weapon);
 struct Profile{unsigned character,weapon;int drain;float speed,stop;};
 static constexpr Profile profiles[]={
 {0,0,12,14.5f,1.0f},
 {0,1,12,14.5f,1.0f},
 {0,2,12,14.5f,1.0f},
 {1,0,8,15.0f,1.0f},
 {1,1,8,14.0f,1.0f},
 {1,2,10,13.0f,1.0f},
 {2,0,10,14.5f,1.25f},
 {2,1,10,14.5f,1.25f},
 {2,2,10,14.5f,1.25f},
 {3,0,12,15.5f,1.0f},
 {3,1,12,15.5f,1.0f},
 {3,2,12,15.5f,1.0f},
 {4,0,6,12.5f,1.0f},
 {4,1,6,12.5f,1.0f},
 {4,2,6,14.5f,1.0f},
 {5,0,12,15.5f,1.0f},
 {5,1,12,15.5f,1.0f},
 {5,2,12,15.5f,1.0f},
 {6,0,10,13.5f,1.0f},
 {6,1,10,13.5f,1.0f},
 {6,2,10,13.5f,1.0f},
 {7,0,8,14.0f,1.0f},
 {7,1,8,14.0f,1.0f},
 {7,2,8,14.0f,1.0f},
 {8,0,12,13.5f,1.0f},
 {8,1,12,13.5f,1.0f},
 {8,2,12,13.5f,1.0f},
 {9,0,10,15.0f,1.0f},
 {9,1,10,15.0f,1.0f},
 {9,2,10,15.0f,1.0f},
 {10,0,8,13.5f,1.0f},
 {10,1,8,13.5f,1.0f},
 {10,2,8,13.5f,1.0f},
 {11,0,10,14.75f,1.25f},
 {11,1,10,14.75f,1.25f},
 {11,2,10,14.75f,1.25f},
 {12,0,10,13.0f,1.0f},
 {12,1,10,13.0f,1.0f},
 {12,2,10,13.0f,1.0f},
 {13,0,14,18.5f,1.0f},
 {13,1,14,18.5f,1.0f},
 {13,2,14,18.5f,1.0f},
 {14,0,6,17.5f,1.0f},
 {14,1,6,15.5f,1.0f},
 {15,0,12,14.5f,1.0f},
 {15,1,12,14.5f,1.0f}
 };
 for(const auto& p:profiles)if(p.character==character&&p.weapon==weapon){BattleGroundDashTuning t;t.drain=p.drain;t.back=p.speed;t.back_stop=p.stop;if(character==14&&weapon==1){t.reset_back=false;if(boosted)t.back=17.5f;}return t;}
 throw std::invalid_argument("Unknown back dash configuration");
}
}
