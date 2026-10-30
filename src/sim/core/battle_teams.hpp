#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
struct BattleTeam {std::uint32_t id=0,value=0,resource=0;};
struct BattleTeamMember {unsigned team=0;std::uint32_t own_resource=0,opponent_resource=0;};
struct BattleTeams {std::array<BattleTeam,2> teams;std::array<BattleTeamMember,4> members;};
// 0x634980 through 0x634bc7. Caller owns characters and their relationship
// containers. Follow with the per-character camera setup in the original tail.
template<class Host> void initialize_battle_teams(BattleTeams& state,const std::array<std::uint32_t,2>& resources,Host& host){
    for(unsigned i=0;i<2;++i)state.teams[i]={i,0,resources[i]};
    for(unsigned i=0;i<4;++i)state.members[i]={i/2,resources[i/2],resources[1-i/2]};
    for(unsigned i=0;i<4;++i)for(unsigned j=0;j<4;++j)if(i!=j){
        if(state.members[i].team==state.members[j].team)host.add_ally(i,j);
        else host.add_opponent(i,j);
    }
}
}
