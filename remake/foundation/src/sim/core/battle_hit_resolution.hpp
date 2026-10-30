#pragma once
#include "battle_hit_damage.hpp"
#include "battle_hit_survival.hpp"
#include "battle_hit_death_entry.hpp"
#include "battle_first_death.hpp"
#include "battle_followup_complete.hpp"
namespace daybreak {
struct BattleHitResolution {
    BattleDamageTotals totals;
    BattleHitSurvival survival;
    BattleFollowupState followup;
    BattleFirstDeathStats death_stats;
    BattleDeathTail tail;
    std::uint32_t current_state=0,bonus_used=0;
};
struct BattleHitParameters {
    std::int32_t base=0,modifier=100,attack=100,defense=100,hit_count_gate=1;
    bool reduce_large=false,targeted=true;
    std::uint32_t death_flags=0,requested_death=0,team=0,limit=100,mode=2,attacker_id=0,victim_id=1;
    std::uint8_t followup_permitted=0,network=0;
    float heading=0,impact_heading=0;
};
// 0x638a18..0x638f84 composition. Caller has already accepted a hit and
// applied earlier status effects. Totals owns input HP; survival owns pending
// state/transition; tail owns heading offset. Role statistics use distinct fields even on self-hit.
template<class ScoreHost,class EventHost>
void resolve_battle_hit(BattleHitResolution& s,BattleTeamScore& teams,const BattleHitParameters& p,ScoreHost& score_host,EventHost& events){
    if(p.team>=2)throw std::out_of_range("Battle hit team");
    const auto damage=apply_hit_damage_prefix(s.totals,p.base,p.modifier,p.attack,p.defense,p.reduce_large,p.targeted,p.hit_count_gate);
    s.survival.health=s.totals.health;s.survival.was_alive=damage.was_alive;
    apply_hit_survival(s.survival);
    s.tail.health=s.survival.health;s.tail.transition=s.survival.transition;
    if(damage_signed(s.survival.health)<=0){
        const auto entry=enter_hit_death(std::uint8_t(s.survival.flag84),p.death_flags,p.requested_death,s.current_state,s.bonus_used);
        s.survival.next_state=entry.next_state;s.bonus_used=entry.bonus_used;
        if(damage.was_alive)complete_first_hit_death(s.followup,s.death_stats,s.tail,teams,p.team,p.limit,entry.extra,p.mode,p.network,p.attacker_id,p.victim_id,p.heading,p.impact_heading,score_host,events);
        else complete_battle_followup(s.followup,s.tail,teams,p.team,p.limit,entry.extra,p.followup_permitted,p.mode,p.network,p.attacker_id,p.victim_id,p.heading,p.impact_heading,score_host,events);
    }
    s.totals.health=s.tail.health;s.survival.health=s.tail.health;s.survival.transition=s.tail.transition;
}
}
