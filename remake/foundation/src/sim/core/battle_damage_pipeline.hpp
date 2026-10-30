#pragma once
#include "battle_pre_damage.hpp"
#include "battle_hit_resolution.hpp"
#include "battle_hit_action.hpp"
namespace daybreak {
// Connects 0x638287..0x638f84, including owner==victim; collision/effects precede this.
// Pre-damage input owns shared attack/actor values. resolution owns HP and statistics.
template<class ChargeHost,class ScoreHost,class EventHost>
void apply_battle_damage_pipeline(BattlePreDamageState& pre,BattleHitResolution& result,BattleTeamScore& teams,const BattlePreDamageInput& input,BattleHitParameters hit,ChargeHost& charge_host,ScoreHost& score_host,EventHost& events){
 if(input.victim_team>=2)throw std::out_of_range("Battle victim team");
 const float original_impact=pre.stagger.impact; // Original bp-30 is preserved before rear-hit adjustment.
 prepare_battle_hit_damage(pre,input,charge_host);
 hit.modifier=damage_signed(pre.stagger.modifier);hit.attack=damage_signed(input.attack_power);hit.defense=input.defense;hit.hit_count_gate=damage_signed(input.stagger.gate);
 hit.death_flags=input.stagger.flags;hit.requested_death=input.stagger.state64;hit.team=input.victim_team;hit.attacker_id=input.attacker_id;hit.victim_id=input.victim_id;
 hit.heading=input.stagger.heading;hit.impact_heading=original_impact;
 hit.followup_permitted=std::uint8_t(pre.stagger.staggered); // Original bp-29.
 result.current_state=input.stagger.current_state;
 result.survival.variant=pre.victim_charge.mode;result.survival.active=pre.victim_charge.blocked2;result.survival.charge=pre.victim_charge.charge2;result.survival.threshold=pre.victim_charge.limit;
 result.survival.flag84=input.grounded_for_death<0?input.stagger.flag84:std::uint32_t(input.grounded_for_death);result.survival.next_state=pre.stagger.selected;result.survival.transition=pre.stagger.transition;
 result.tail.offset=pre.stagger.offset;result.death_stats.word7b8=pre.stagger.accum;
 resolve_battle_hit(result,teams,hit,score_host,events);
 pre.stagger.selected=result.survival.next_state;pre.stagger.transition=result.survival.transition;
 pre.stagger.offset=result.tail.offset;pre.stagger.accum=result.death_stats.word7b8;
}
}

namespace daybreak {
// Includes final 0x638f84..0x638f98 action gate. Current action is authoritative.
template<class ChargeHost,class ScoreHost,class EventHost,class ActionHost>
void apply_battle_damage_and_action(BattlePreDamageState& pre,BattleHitResolution& result,BattleActionState& action,BattleTeamScore& teams,BattlePreDamageInput input,BattleHitParameters hit,ChargeHost& charge,ScoreHost& score,EventHost& events,ActionHost& animation){
 input.stagger.current_state=action.state;
 apply_battle_damage_pipeline(pre,result,teams,input,hit,charge,score,events);
 apply_selected_hit_action(action,result.survival.transition,result.survival.next_state,animation);
 result.current_state=action.state;
}
}
