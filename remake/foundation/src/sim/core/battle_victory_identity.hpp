#pragma once
#include <array>
#include <cstdio>
#include <stdexcept>
#include <string>
namespace daybreak {
// 635d40 case4/substate0: weapon2 changes Rena/Rika's script identity and portrait suffix.
struct BattleVictoryIdentity {unsigned script_character;std::string portrait;};
inline BattleVictoryIdentity battle_victory_identity(unsigned character,unsigned weapon){
 if(character>=16||weapon>=(character<14?3u:2u))throw std::invalid_argument("Invalid victory roster identity");
 const bool alternate=weapon==2&&(character==0||character==4);
 char path[64];std::snprintf(path,sizeof path,"data/win/%02u%c.cnv",character,alternate?'b':'a');
 return {alternate?(character==0?16u:17u):character,path};
}
inline std::array<BattleVictoryIdentity,2> battle_victory_team(unsigned team,const std::array<unsigned,4>& characters,const std::array<unsigned,4>& weapons){
 if(team>1)throw std::invalid_argument("Invalid victory team");
 return {{battle_victory_identity(characters[team*2],weapons[team*2]),battle_victory_identity(characters[team*2+1],weapons[team*2+1])}};
}
}
