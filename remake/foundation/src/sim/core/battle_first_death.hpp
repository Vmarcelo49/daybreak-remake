#pragma once
#include "battle_followup.hpp"
#include "battle_death_tail.hpp"
#include "battle_hit_death_score.hpp"
namespace daybreak {
struct BattleFirstDeathStats {std::uint32_t kills=0,deaths=0,word7b8=0;};
// 0x638cad through common tail. Caller has confirmed a newly lethal hit.
template<class ScoreHost,class EventHost>
void complete_first_hit_death(BattleFollowupState& actor,BattleFirstDeathStats& stats,BattleDeathTail& tail,BattleTeamScore& teams,unsigned team,std::uint32_t limit,std::uint32_t extra,std::uint32_t mode,std::uint8_t network,std::uint32_t attacker,std::uint32_t victim,float heading,float impact,ScoreHost& score_host,EventHost& events){
    add_battle_team_score(teams,team,hit_death_score(tail.health,extra),network,score_host);
    events.event(9);
    mark_battle_defeated(limit,teams.score[team],actor.defeated);
    if(mode==2){actor.attacker_c9=1;actor.attacker_b8=1;actor.last_attacker=attacker;++stats.kills;++stats.deaths;if(network==1)events.notify(std::uint8_t(attacker),std::uint8_t(victim));}
    stats.word7b8=0;
    finish_hit_death(tail,mode,heading,impact);
}
}
