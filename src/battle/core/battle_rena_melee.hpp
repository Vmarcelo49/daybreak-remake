#pragma once
#include "battle_rena_ground_melee.hpp"
#include "battle_rena_ground_dash.hpp"
#include "battle_rena_landing_melee.hpp"
#include "battle_chasing_air_melee.hpp"
#include "battle_dash_melee.hpp"
#include "battle_dash_followup.hpp"
namespace daybreak {
struct RenaMeleeEffects : BattleRenaFollowupEffects {
 bool disable_contact=false,sound_request=false;
 int frame_override=-1;
 bool advance_after_frame_override=false;
};
inline bool rena_melee_action_state(unsigned state){
 return (state>=300&&state<=302)||(state>=310&&state<=311)||state==320||(state>=329&&state<=334)||state==340||state==341;
}
// Recovered melee dispatch only. This does not admit shooting/special actions
// or make the complete fighter available in the roster.
inline RenaMeleeEffects advance_rena_melee(unsigned weapon,unsigned state,KeiichiAirMelee& air,KeiichiAttack300& motion,const KeiichiAttack300Input& input,bool jump_held,float height,float& turn,int& gauge,bool slowed){
 character_action_dispatch(0,weapon);
 RenaMeleeEffects out;
 if(state==300||state==301||state==302||state==310||state==311){
  static_cast<BattleRenaFollowupEffects&>(out)=advance_battle_rena_ground_melee(weapon,state,motion,input,air.strength,jump_held,air.gravity,turn);
 }else if(state==320){
  // +ec means contact history on the ground and elapsed chase ticks in air.
  // Preserve the same scratch word across state changes instead of maintaining
  // two unrelated counters that diverge at the boundary.
  air.ticks=unsigned(motion.contact_seen);
  const auto next=advance_chasing_air_melee(chasing_air_melee_policy(0,weapon),air,motion,input,height);
  motion.contact_seen=int(air.ticks);
  static_cast<KeiichiAttack300Effects&>(out)=next;out.activate=next.activate;out.reset_capacity=next.initialize;
  out.frame_override=next.frame_override;out.advance_after_frame_override=next.frame_override>=0;
 }else if(state==329||state==330||state==331){
  static_cast<BattleRenaOrdinaryEffects&>(out)=advance_rena_ground_dash(weapon,state,air,motion,input,turn,gauge,slowed);
 }else if(state==332){
  float roll=0; // Rena332 does not access the roll field.
  const auto next=advance_battle_dash_melee(0,weapon,air,motion,input,height,roll);
  static_cast<KeiichiAttack300Effects&>(out)=next;out.activate=next.activate;out.reset_capacity=next.reset_capacity;
  out.disable_contact=next.disable_contact;out.sound_request=next.sound_request;
  out.frame_override=next.frame_override;out.advance_after_frame_override=next.advance_after_frame_override;
 }else if(state==333){
  BattleDashRecovery recovery{air.vertical,air.gravity,motion.speed,motion.movement_angle,turn,gauge};
  out.next_state=advance_battle_dash_recovery(recovery,0,weapon,input.animation_complete,slowed);
  air.vertical=recovery.vertical;air.gravity=recovery.gravity;motion.speed=recovery.speed;motion.movement_angle=recovery.movement_angle;turn=recovery.turn_step;gauge=recovery.gauge;
 }else if(state==334){
  const auto next=advance_battle_dash_followup(0,weapon,air,motion,input,gauge,turn,slowed);
  static_cast<KeiichiAttack300Effects&>(out)=next;out.activate=next.activate;out.reset_capacity=next.reset_capacity;out.contact_mode=next.camera;
 }else if(state==340||state==341){
  static_cast<BattleRenaFollowupEffects&>(out)=advance_rena_landing_melee(weapon,state,air,motion,input,turn);
 }else throw std::invalid_argument("Rena melee state not recovered");
 return out;
}
}
