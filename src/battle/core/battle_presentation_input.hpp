#pragma once
#include "battle_input_buttons.hpp"
#include "local_battle_roster.hpp"
namespace daybreak {
//635d40 consumes physical B0..B6, before the actor's logical aliases.
inline constexpr unsigned battle_result_confirmation_buttons=0x7f;
inline unsigned battle_presentation_button_edges(unsigned current,unsigned previous){
 return battle_physical_buttons(current)&~battle_physical_buttons(previous);
}
//634d29 polls viewer+4; viewer+50 is therefore controller B3 (target).
inline bool battle_spectator_view_pressed(unsigned current,unsigned previous){
 return (battle_presentation_button_edges(current,previous)&8u)!=0;
}
//Result controls are controller banks, rather than fighter commands. A shared
//controller's repeated fighter inputs must contribute only one bank.
inline std::array<unsigned,4> local_battle_result_buttons(const LocalBattleRoster& roster,const net::InputChannel::Frame& inputs){
 std::array<unsigned,4> result{};
 for(unsigned c=0;c<4;++c){const int actor=roster.controller_actor[c];if(actor>=0&&actor<4)result[c]=inputs[unsigned(actor)].buttons;}
 //Retain the rebuild's existing local all-CPU/fallback confirmation policy.
 if(roster.fallback_input&&roster.controlled_count)result[0]=inputs.at(roster.controlled_slots[0]).buttons;
 return result;
}
//636ac3 skips unassigned controllers;636b41 ends after the first assigned bank.
inline unsigned local_battle_result_primary_controller(const LocalBattleRoster& roster){
 for(unsigned c=0;c<4;++c)if(roster.controller_actor[c]>=0&&roster.controller_actor[c]<4)return c;
 return 0; //Existing all-CPU/fallback confirmation policy.
}
}
