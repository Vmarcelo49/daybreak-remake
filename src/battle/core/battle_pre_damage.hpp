#pragma once
#include "battle_friendly_hit.hpp"
#include "battle_hit_charge.hpp"
#include "battle_attack_charge.hpp"
#include "battle_hit_scaling_setup.hpp"
#include "battle_hit_stagger.hpp"
#include "battle_hit_status.hpp"
namespace daybreak {
struct BattlePreDamageState {
 BattleFriendlyHit friendly{};BattleHitCharge victim_charge{};BattleAttackCharge attacker_charge{};
 BattleHitScalingSetup stops{};BattleHitStagger stagger{};BattleHitStatus status{};
};
struct BattlePreDamageInput {
 std::uint32_t attacker_id=0,victim_id=1,attacker_team=0,victim_team=1,team_modifier=100;
 std::int32_t victim_charge_base=0,attacker_charge_base=0,charge_scale=100,defense=100,damage_divisor=100;
 std::uint32_t attack_stop=0,victim_stop=0,attack_flags=0,status_duration=0,status_power=0,attack_power=100;
 // -1 preserves legacy adapter behavior; explicit value supplies actor +84 for death/survival.
 std::int32_t grounded_for_death=-1;
 BattleHitStaggerInput stagger{};
};
// Composition of 0x638287..0x638a18. Notification callbacks must not mutate battle state.
// The attacker and victim charge representations must describe the same mode on self-hit.
template<class Host> void prepare_battle_hit_damage(BattlePreDamageState& s,const BattlePreDamageInput& p,Host& host){
 apply_battle_friendly_hit(s.friendly,p.attacker_team==p.victim_team,p.attacker_id==p.victim_id,p.team_modifier);
 apply_battle_hit_charge(s.victim_charge,p.victim_charge_base,p.charge_scale,p.defense,damage_signed(s.friendly.modifier),p.victim_id,host);
 apply_battle_attack_charge(s.attacker_charge,p.attacker_charge_base,p.charge_scale,p.attacker_id,host);
 // Scaling uses the count before the new stagger increments it.
 s.stops=setup_battle_hit_scaling(p.attack_stop,p.victim_stop,s.stagger.count,p.damage_divisor,damage_signed(s.friendly.modifier));
 s.stagger.modifier=s.stops.modifier;
 apply_battle_hit_stagger(s.stagger,p.stagger);
 apply_battle_hit_status(s.status,p.attack_flags,p.status_duration,p.status_power,p.attack_power);
 // Final damage must consume stagger.modifier, which can differ from stops.modifier.
}
}
