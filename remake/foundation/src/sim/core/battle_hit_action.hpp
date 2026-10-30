#pragma once
#include "battle_hit_resolution.hpp"
#include "battle_action_transition.hpp"
namespace daybreak {
template<class Host> void apply_selected_hit_action(BattleActionState& action,std::uint32_t transition,std::uint32_t selected,Host& host){
    if(std::uint8_t(transition))change_battle_action(action,selected,host);
}

// Adds 0x638f84..0x638f98 and the recovered 0x421080 action update.
// Action state is authoritative for the actor's current state before the hit.
template<class ScoreHost,class EventHost,class ActionHost>
void resolve_and_apply_battle_hit(BattleHitResolution& hit,BattleActionState& action,BattleTeamScore& teams,const BattleHitParameters& p,ScoreHost& score,EventHost& events,ActionHost& animation){
    hit.current_state=action.state;
    resolve_battle_hit(hit,teams,p,score,events);
    apply_selected_hit_action(action,hit.survival.transition,hit.survival.next_state,animation);
    hit.current_state=action.state;
}
}
