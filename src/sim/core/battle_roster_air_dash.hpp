#pragma once
#include "battle_air_dash.hpp"
#include "character_dispatch.hpp"
namespace daybreak {
inline BattleAirDashStep advance_roster_air_dash(BattleAirDash& s,unsigned character,unsigned weapon,bool boosted=false){
 character_action_dispatch(character,weapon);
 if(character==0&&weapon==0)return advance_battle_air_dash(s,16.5f,11,false,2.0f);
 if(character==0&&weapon==1)return advance_battle_air_dash(s,16.5f,11,false,2.0f);
 if(character==0&&weapon==2)return advance_battle_air_dash(s,11.5f,14,true,2.0f);
 if(character==1&&weapon==0)return advance_battle_air_dash(s,14.5f,7,false,2.0f);
 if(character==1&&weapon==1)return advance_battle_air_dash(s,14.5f,7,false,2.0f);
 if(character==1&&weapon==2)return advance_battle_air_dash(s,13.0f,9,false,2.0f);
 if(character==2&&weapon==0)return advance_battle_air_dash(s,15.5f,9,false,2.0f);
 if(character==2&&weapon==1)return advance_battle_air_dash(s,15.5f,9,false,2.0f);
 if(character==2&&weapon==2)return advance_battle_air_dash(s,15.5f,9,false,2.0f);
 if(character==3&&weapon==0)return advance_battle_air_dash(s,13.5f,12,false,2.0f);
 if(character==3&&weapon==1)return advance_battle_air_dash(s,13.5f,12,false,2.0f);
 if(character==3&&weapon==2)return advance_battle_air_dash(s,13.0f,13,false,2.0f);
 if(character==4&&weapon==0)return advance_battle_air_dash(s,11.0f,5,false,4.0f);
 if(character==4&&weapon==1)return advance_battle_air_dash(s,11.0f,5,false,4.0f);
 if(character==4&&weapon==2)return advance_battle_air_dash(s,16.5f,11,false,3.0f);
 if(character==5&&weapon==0)return advance_battle_air_dash(s,16.5f,11,false,2.0f);
 if(character==5&&weapon==1)return advance_battle_air_dash(s,16.5f,11,false,2.0f);
 if(character==5&&weapon==2)return advance_battle_air_dash(s,16.5f,11,false,2.0f);
 if(character==6&&weapon==0)return advance_battle_air_dash(s,15.5f,11,false,2.0f);
 if(character==6&&weapon==1)return advance_battle_air_dash(s,15.0f,11,false,2.0f);
 if(character==6&&weapon==2)return advance_battle_air_dash(s,15.5f,11,false,2.0f);
 if(character==7&&weapon==0)return advance_battle_air_dash(s,14.25f,7,false,2.0f);
 if(character==7&&weapon==1)return advance_battle_air_dash(s,14.25f,9,false,2.0f);
 if(character==7&&weapon==2)return advance_battle_air_dash(s,14.25f,7,false,2.0f);
 if(character==8&&weapon==0)return advance_battle_air_dash(s,12.75f,10,false,2.0f);
 if(character==8&&weapon==1)return advance_battle_air_dash(s,12.75f,10,false,2.0f);
 if(character==8&&weapon==2)return advance_battle_air_dash(s,12.75f,10,false,2.0f);
 if(character==9&&weapon==0)return advance_battle_air_dash(s,15.0f,9,false,2.0f);
 if(character==9&&weapon==1)return advance_battle_air_dash(s,15.0f,9,false,2.0f);
 if(character==9&&weapon==2)return advance_battle_air_dash(s,15.0f,9,false,2.0f);
 if(character==10&&weapon==0)return advance_battle_air_dash(s,14.0f,9,false,2.0f);
 if(character==10&&weapon==1)return advance_battle_air_dash(s,14.0f,9,false,2.0f);
 if(character==10&&weapon==2)return advance_battle_air_dash(s,14.0f,9,false,2.0f);
 if(character==11&&weapon==0)return advance_battle_air_dash(s,15.25f,8,false,2.0f);
 if(character==11&&weapon==1)return advance_battle_air_dash(s,15.25f,8,false,2.0f);
 if(character==11&&weapon==2)return advance_battle_air_dash(s,15.25f,8,false,2.0f);
 if(character==12&&weapon==0)return advance_battle_air_dash(s,13.0f,9,false,2.0f);
 if(character==12&&weapon==1)return advance_battle_air_dash(s,13.0f,9,false,2.0f);
 if(character==12&&weapon==2)return advance_battle_air_dash(s,13.0f,9,false,2.0f);
 if(character==13&&weapon==0)return advance_battle_air_dash(s,13.5f,9,false,2.0f);
 if(character==13&&weapon==1)return advance_battle_air_dash(s,13.5f,9,false,2.0f);
 if(character==13&&weapon==2)return advance_battle_air_dash(s,13.5f,9,false,2.0f);
 if(character==14&&weapon==0)return advance_battle_air_dash(s,15.5f,7,false,4.0f);
 if(character==15&&weapon==0)return advance_battle_air_dash(s,16.5f,8,false,2.0f);
 if(character==15&&weapon==1)return advance_battle_air_dash(s,16.5f,8,false,2.0f);
 if(character==14&&weapon==1)return advance_battle_air_dash(s,boosted?16.f:14.5f,boosted?7:8,false,boosted?10.f:2.f,2,false);
 throw std::invalid_argument("Invalid air dash configuration");
}
}
