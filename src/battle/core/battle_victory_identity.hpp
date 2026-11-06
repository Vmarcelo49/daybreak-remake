#pragma once
#include "psp_roster.hpp"
#include <array>
#include <cstdio>
#include <stdexcept>
#include <string>
namespace daybreak {
// 635d40 case4/substate0: weapon2 changes Rena/Rika's script identity and portrait suffix.
struct BattleVictoryIdentity {unsigned script_character;std::string portrait;};
// Plan D-1: the three PSP fighters (16..18) win matches too, so the guard takes them. Their
// portrait is data/win/%02u of the roster index (16a..18a), which no PC combo uses: the PC
// portraits are 00a..15a plus 00b/04b, and the persona suffixes below. Their *script* personas
// start at 19, not 18: 16 and 17 already mean Rena's and Rika's weapon-2 persona
// (result_quote.h resultPersonaId, tests/result_title_test.cpp pins it), and leaving 18 unused
// keeps an off-by-one from silently reading "the character after the last PC persona".
inline constexpr unsigned psp_victory_persona_first=19;
inline BattleVictoryIdentity battle_victory_identity(unsigned character,unsigned weapon){
 if(!roster_has_character(character)||weapon>=roster_weapon_count(character))throw std::invalid_argument("Invalid victory roster identity");
 const bool alternate=weapon==2&&(character==0||character==4);
 char path[64];std::snprintf(path,sizeof path,"data/win/%02u%c.cnv",character,alternate?'b':'a');
 if(is_psp_character(character))return {psp_victory_persona_first+psp_character_index(character),path};
 return {alternate?(character==0?16u:17u):character,path};
}
inline std::array<BattleVictoryIdentity,2> battle_victory_team(unsigned team,const std::array<unsigned,4>& characters,const std::array<unsigned,4>& weapons){
 if(team>1)throw std::invalid_argument("Invalid victory team");
 return {{battle_victory_identity(characters[team*2],weapons[team*2]),battle_victory_identity(characters[team*2+1],weapons[team*2+1])}};
}
}
