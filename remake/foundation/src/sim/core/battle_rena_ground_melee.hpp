#pragma once
#include "battle_rena_followup_melee.hpp"
#include "battle_rena_directional_melee.hpp"
namespace daybreak {
// Single entry for the recovered ground-melee handlers, not whole-fighter
// admission. State requests still pass through the original input policy.
inline BattleRenaFollowupEffects advance_battle_rena_ground_melee(unsigned weapon,unsigned state,KeiichiAttack300& motion,const KeiichiAttack300Input& input,int scratch_f0,bool jump_held,float& gravity,float& turn_step){
 if(state==301||state==302)return advance_battle_rena_followup_melee(weapon,state,motion,input,gravity,turn_step);
 BattleRenaFollowupEffects out;
 if(state==300)static_cast<BattleRenaOrdinaryEffects&>(out)=advance_battle_rena_ordinary_melee(weapon,motion,input,scratch_f0,gravity);
 else if(state==310||state==311)static_cast<BattleRenaOrdinaryEffects&>(out)=advance_battle_rena_directional_melee(weapon,state,motion,input,jump_held,gravity);
 else throw std::invalid_argument("Rena ground melee handler not recovered");
 return out;
}
}
