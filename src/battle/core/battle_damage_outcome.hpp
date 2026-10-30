#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleDamageOutcomeState {
    std::uint32_t health=0,state=0,variant=0,active=0,threshold=0,charge=0;
    std::uint32_t mode=0,network_mode=0,attacker_id=0,victim_id=0,team=0;
    std::uint32_t attacker_flag_c9=0,attacker_flag_b8=0,last_attacker=0,kills=0,deaths=0,word7b8=0;
};
// Tail of 0x639160. Host preserves ordered external effects; packet serialization
// and the bodies of score/event/defeat handlers are separate contracts.
template<class Host> std::int16_t finish_direct_damage(BattleDamageOutcomeState& s,bool was_alive,std::int16_t death_state,std::uint8_t nonlethal,Host& host){
    if(damage_signed(s.health)>0)return -1;
    if(nonlethal){if(was_alive)s.health=1;return -1;}
    const bool extra=s.state!=198&&s.state!=199&&(death_state==198||death_state==199);
    if(std::uint8_t(s.variant)==2&&std::uint8_t(s.active)==0&&was_alive&&damage_signed(s.charge)>=damage_signed(s.threshold)){
        s.health=1;return 503;
    }
    if(was_alive){
        const auto over=damage_divide(damage_signed(0u-s.health),1000);
        host.score(s.team,std::uint32_t(over)+20u+std::uint32_t(extra));
        host.event(9);host.defeat();
        if(s.mode==2){
            s.attacker_flag_c9=1;s.attacker_flag_b8=1;s.last_attacker=s.attacker_id;++s.kills;++s.deaths;
            if(std::uint8_t(s.network_mode)==1)host.notify(std::uint8_t(s.attacker_id),std::uint8_t(s.victim_id));
        }
        s.word7b8=0;
    }
    s.health=s.mode==2?0:1;return death_state;
}
}
