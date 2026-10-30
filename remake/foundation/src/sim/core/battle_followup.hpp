#pragma once
#include "battle_team_score.hpp"
#include "battle_actor_resource.hpp"
namespace daybreak {
struct BattleFollowupState {
    std::uint32_t points=0,last_attacker=0;
    std::uint8_t attacker_c9=0,attacker_b8=0,defeated=0;
};
// 0x638e0d..0x638ef6 orchestration. Score host handles changed/send;
// event host handles notify(attacker,victim) and event(10).
// Common HP/heading tail follows separately. Host callbacks are synchronous.
template<class ScoreHost,class EventHost>
void apply_battle_followup(BattleFollowupState& actor,BattleTeamScore& teams,unsigned team,std::uint32_t limit,std::uint32_t extra,std::uint8_t permitted,std::uint32_t mode,std::uint8_t network,std::uint32_t attacker,std::uint32_t victim,ScoreHost& score_host,EventHost& events){
    if(!permitted)return;
    if(team>=2)throw std::out_of_range("Battle followup team");
    const auto delta=extra+1u;
    add_battle_team_score(teams,team,delta,network,score_host);
    actor.points+=delta;
    if(remaining_battle_resource(limit,teams.score[team])<=0){
        mark_battle_defeated(limit,teams.score[team],actor.defeated);
        if(mode==2){
            actor.attacker_c9=1;actor.attacker_b8=1;actor.last_attacker=attacker;
            if(network==1)events.notify(std::uint8_t(attacker),std::uint8_t(victim));
        }
    }
    events.event(10);
}
}
