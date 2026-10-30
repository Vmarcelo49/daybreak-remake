#pragma once
#include "battle_damage_outcome.hpp"
namespace daybreak {
// Outcome health is authoritative at entry. Totals health is synchronized before
// arithmetic and after lethal handling. Original nonlethal handling may preserve
// negative HP when the victim was already dead.
// Distinct attacker/victim records; aliasing actors remains unverified.
template<class Host> std::int16_t apply_direct_damage(BattleDamageOutcomeState& state,BattleDamageTotals& totals,std::int16_t base,std::int32_t attack,std::int32_t defense,std::int32_t divisor,bool targeted,std::int16_t death_state,std::uint8_t nonlethal,Host& host){
    totals.health=state.health;
    const auto applied=apply_direct_damage_prefix(totals,base,attack,defense,divisor,targeted);
    state.health=totals.health;
    const auto result=finish_direct_damage(state,applied.was_alive!=0,death_state,nonlethal,host);
    totals.health=state.health;
    return result;
}
}
