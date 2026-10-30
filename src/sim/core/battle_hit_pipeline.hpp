#pragma once
#include "battle_normal_hit.hpp"
#include "battle_hit_support.hpp"
#include "battle_hit_direction.hpp"
namespace daybreak {
struct BattleHitPipelineState{BattleNormalHitState normal{};std::uint32_t healed_total=0,last_owner=0,guard_count=0;std::array<std::uint32_t,4> victim_cooldowns{};};
struct BattleHitPipelineInput{BattlePreDamageInput pre{};BattleHitParameters hit{};BattleNormalHitContact geometry{};BattleHitDirection direction{};std::uint32_t blocked=0,extent=0,victim_target_id=0,effect=0,reaction=0;};
enum class BattleHitPath{miss,support,guard,normal};
// Shared state adapter for original 0x637960 onward. Finite coordinates/angles.
//637950 admits projectile self-hit via DAT0x10000; callbacks must not mutate battle state.
template<class Host> BattleHitPath apply_battle_hit_pipeline(BattleHitPipelineState& s,BattleRandom& random,BattleTeamScore& teams,const BattleHitPipelineInput& p,Host& host){
 auto& n=s.normal;auto input=p.pre;const bool same=input.attacker_team==input.victim_team;
 BattleHitEligibility gate{input.attacker_id,input.victim_id,input.attack_flags,n.pre.stagger.invincible,p.blocked,n.reaction.cooldown,n.reaction.remaining,p.extent,std::uint32_t(same),input.team_modifier,input.stagger.gate,n.result.totals.health,std::uint32_t(p.hit.targeted),p.victim_target_id,n.pre.stagger.offset};
 BattleHitGeometry g;for(unsigned i=0;i<3;++i){g.primary[i]=p.geometry.primary[i];g.secondary[i]=p.geometry.secondary[i];g.start[i]=p.geometry.start[i];g.end[i]=p.geometry.end[i];}g.shape=p.geometry.shape;
 auto contacts=query_battle_hit(gate,g);if(!contacts.any())return BattleHitPath::miss;
 BattleHitSupport support{n.reaction.cooldown,n.reaction.remaining,n.result.totals.health,s.healed_total,n.pre.status.duration[1],n.pre.status.duration[2]};
 if(apply_battle_hit_support(support,same,input.attack_flags,input.team_modifier,input.status_duration)){
  n.reaction.cooldown=support.cooldown;n.reaction.remaining=support.remaining;n.result.totals.health=support.health;s.healed_total=support.healed_total;n.pre.status.duration[1]=support.effect_7e0;n.pre.status.duration[2]=support.effect_7e4;
  return BattleHitPath::support;
 }
 BattleHitGuard guard{n.action.word_684,s.last_owner,n.reaction.cooldown,n.reaction.remaining,s.guard_count,{}};
 for(unsigned i=0;i<4;++i)guard.victim_cooldowns[i]=s.victim_cooldowns[i];float impact,relative;
 bool guarded=direct_and_guard_battle_hit(guard,p.direction,input.stagger.heading,n.pre.stagger.offset,input.attacker_id,input.stagger.flags,input.attack_flags,impact,relative);
 n.action.word_684=guard.word684;s.last_owner=guard.last_owner;
 if(guarded){n.reaction.cooldown=guard.cooldown;n.reaction.remaining=guard.remaining;s.guard_count=guard.guard_count;for(unsigned i=0;i<4;++i)s.victim_cooldowns[i]=guard.victim_cooldowns[i];return BattleHitPath::guard;}
 n.pre.stagger.impact=impact;input.stagger.relative=relative;auto contact=p.geometry;contact.contacts=contacts;
 apply_battle_normal_hit(n,random,teams,contact,input,p.hit,p.effect,p.reaction,host,host,host,host,host);return BattleHitPath::normal;
}
}
