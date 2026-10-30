#pragma once
#include "battle_spin_melee.hpp"
#include "battle_double_leap_melee.hpp"
#include "battle_steep_dive.hpp"
#include "battle_timed_dive.hpp"
#include "battle_anchor_dive.hpp"
namespace daybreak {
enum class BattleDashFamily {unrecovered,rebound,tracking_rebound,leap,double_leap,spin,keiichi_dive,steep_dive,timed_dive,anchor_dive};
// State332 coverage only. This is not an admission table for complete fighters.
inline BattleDashFamily battle_dash_family(unsigned character,unsigned weapon){
 character_action_dispatch(character,weapon);
 if(character==1||character==10||character==12)return BattleDashFamily::rebound;
 if(battle_tracking_rebound_configuration(character,weapon))return BattleDashFamily::tracking_rebound;
 if(character==8)return BattleDashFamily::leap;
 if(character==3)return BattleDashFamily::double_leap;
 if(character==9)return BattleDashFamily::spin;
 if(character==6)return BattleDashFamily::steep_dive;
 if(character==7)return BattleDashFamily::timed_dive;
 if(character==4&&weapon==2)return BattleDashFamily::anchor_dive;
 if(character==0||character==2||character==5||character==11||character==15)return BattleDashFamily::keiichi_dive;
 return BattleDashFamily::unrecovered;
}
struct BattleDashMeleeEffects : BattleDoubleLeapEffects {bool disable_contact=false,sound_request=false;int frame_override=-1;bool advance_after_frame_override=false;};
struct BattleDashTargetPoints {std::array<float,3> origin{},target_spine{};};
// Preserve all family-specific requests for the host: magazine update precedes
// transitions, positional_sound is a service request, and continue_after_phase
// requires the remainder of the same update after changing the DAT phase.
inline BattleDashMeleeEffects advance_battle_dash_melee(unsigned character,unsigned weapon,KeiichiAirMelee& air,KeiichiAttack300& motion,const KeiichiAttack300Input& input,float height,float& roll,const BattleDashTargetPoints* points=nullptr){
 BattleDashMeleeEffects out;
 switch(battle_dash_family(character,weapon)){
 case BattleDashFamily::anchor_dive:
  if(!points)throw std::invalid_argument("State332 requires target selector2 position");
  static_cast<BattleLeapMeleeEffects&>(out)=advance_battle_anchor_dive(air,motion,input,points->origin,points->target_spine);break;
 case BattleDashFamily::timed_dive:{
  const auto result=advance_battle_timed_dive(weapon,air,motion,input,height);
  static_cast<BattleLeapMeleeEffects&>(out)=result;out.frame_override=result.frame_override;out.sound_request=result.sound_request;
  out.advance_after_frame_override=result.frame_override>=0;break;
 }
 case BattleDashFamily::steep_dive:{
  const auto result=advance_battle_steep_dive(weapon,air,motion,input,height);
  static_cast<BattleLeapMeleeEffects&>(out)=result;out.frame_override=result.frame_override;break;
 }
 case BattleDashFamily::rebound:
  static_cast<BattleReboundMeleeEffects&>(out)=advance_battle_rebound_dash(character,weapon,air,motion,input);break;
 case BattleDashFamily::tracking_rebound:
  static_cast<BattleReboundMeleeEffects&>(out)=advance_battle_tracking_rebound(character,weapon,air,motion,input);break;
 case BattleDashFamily::leap:{
  // State332 never changes recovery gauge or turn_step; state334 is separate.
  int gauge=0;float turn_step=0;
  static_cast<BattleLeapMeleeEffects&>(out)=advance_battle_leap_melee(332,weapon,air,motion,input,gauge,turn_step,false);break;
 }
 case BattleDashFamily::double_leap:
  static_cast<BattleDoubleLeapEffects&>(out)=advance_battle_double_leap(weapon,air,motion,input);break;
 case BattleDashFamily::spin:
  static_cast<BattleLeapMeleeEffects&>(out)=advance_battle_spin_melee(weapon,air,motion,input,roll);break;
 case BattleDashFamily::keiichi_dive:{
  const auto result=advance_keiichi_dash_melee(air,motion,input,height,weapon,character);
  static_cast<KeiichiAttack300Effects&>(out)=result.action;
  out.activate=result.action.initialize;out.reset_capacity=result.reset_contact_capacity||result.action.initialize;
  out.disable_contact=result.disable_contact;out.sound_request=result.sound_request;break;
 }
 default:throw std::invalid_argument("Unrecovered state332 character/weapon");
 }
 return out;
}
}
