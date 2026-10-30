#pragma once
#include "battle_damage_pipeline.hpp"
#include "battle_hit_effects.hpp"
#include "battle_hit_query.hpp"
namespace daybreak {
struct BattleNormalHitState{BattleHitReaction reaction{};BattlePreDamageState pre{};BattleHitResolution result{};BattleActionState action{};};
struct BattleNormalHitContact{BattleContactVector primary{},secondary{},start{},end{};std::uint32_t shape=0;BattleHitContacts contacts{};};
// Original normal-hit branch 0x637fd8 onward. Caller has excluded support/guard.
// The same contacts drive both effect position and secondary-contact damage reduction.
template<class Effects,class Charge,class Score,class Events,class Animation>
bool apply_battle_normal_hit(BattleNormalHitState& s,BattleRandom& random,BattleTeamScore& teams,const BattleNormalHitContact& contact,const BattlePreDamageInput& input,BattleHitParameters hit,std::uint32_t effect,std::uint32_t reaction,Effects& effects,Charge& charge,Score& score,Events& events,Animation& animation){
 if(!contact.contacts.any())return false;
 if(input.victim_team>=2)throw std::out_of_range("Battle victim team");
 if(!input.damage_divisor)throw std::domain_error("Original damage divisor is zero");
 const auto point=battle_hit_contact(contact.primary,contact.secondary,contact.start,contact.end,contact.shape,contact.contacts.primary,contact.contacts.secondary);
 emit_battle_hit_effects(s.reaction,random,point,input.victim_id,effect,reaction,hit.network,effects);
 hit.reduce_large=contact.contacts.secondary;
 apply_battle_damage_and_action(s.pre,s.result,s.action,teams,input,hit,charge,score,events,animation);
 return true;
}
}
