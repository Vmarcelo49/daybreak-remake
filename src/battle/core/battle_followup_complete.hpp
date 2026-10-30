#pragma once
#include "battle_followup.hpp"
#include "battle_death_tail.hpp"
namespace daybreak {
// Entire already-dead followup branch through the common death tail.
// Entry is after death-state selection; caller has confirmed nonpositive HP
// and that the victim was not alive before this hit. Angles must be bounded.
template<class ScoreHost,class EventHost>
void complete_battle_followup(BattleFollowupState& actor,BattleDeathTail& tail,BattleTeamScore& teams,unsigned team,std::uint32_t limit,std::uint32_t extra,std::uint8_t permitted,std::uint32_t mode,std::uint8_t network,std::uint32_t attacker,std::uint32_t victim,float heading,float impact,ScoreHost& score_host,EventHost& events){
    apply_battle_followup(actor,teams,team,limit,extra,permitted,mode,network,attacker,victim,score_host,events);
    finish_hit_death(tail,mode,heading,impact);
}
}
