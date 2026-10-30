#pragma once
#include "battle_camera_viewports.hpp"
namespace daybreak {
//The actor's source call selects the backend independently of its voice bank.
inline bool battle_voice_alternate_route(unsigned source){
 return source==0x4223d0||source==0x422490;
}
inline unsigned battle_voice_bank(unsigned character,unsigned item,bool active){
 return unsigned(character==14&&item==32&&active); //41e180 ownsAEB4 only here.
}
inline unsigned battle_voice_layout_byte(const LocalBattleRoster& roster,unsigned scene_phase=0){
 return unsigned(battle_camera_viewports(roster,scene_phase==2?0:scene_phase).fullscreen);
}
}
