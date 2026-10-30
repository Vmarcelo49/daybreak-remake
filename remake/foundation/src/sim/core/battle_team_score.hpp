#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>
namespace daybreak {
struct BattleTeamScore {
    std::array<std::uint32_t,2> score{},label{},notification_cache{};
};
// 0x639650: two valid team slots. Callback bodies/serialization are external.
template<class Host> void add_battle_team_score(BattleTeamScore& s,unsigned team,std::uint32_t delta,std::uint8_t network_mode,Host& host){
    if(team>=2)throw std::out_of_range("Battle score team");
    s.score[team]+=delta;
    host.changed(std::uint8_t(s.label[team]),delta);
    if(network_mode==1){
        s.notification_cache[0]=std::uint16_t(s.score[0]);s.notification_cache[1]=std::uint16_t(s.score[1]);
        host.send(std::uint16_t(s.notification_cache[0]),std::uint16_t(s.notification_cache[1]));
    }
}
}
