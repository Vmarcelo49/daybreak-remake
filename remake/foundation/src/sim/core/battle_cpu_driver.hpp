#pragma once
#include "battle_cpu_frame.hpp"
#include "battle_action_binding.hpp"
#include "roster_cpu_decisions.hpp"
#include "local_battle_roster.hpp"
#include "battle_world.hpp"
#include "battle_frame_tail.hpp"
#include "battle_phase_services.hpp"
#include "battle_damage_scaling.hpp"
namespace daybreak {
struct BattleCpuSpecialState {int timer838=0,timer83c=0;bool active844=false,active845=false;};
// Ordinary local CPU scheduling. Special-mode gauge producers/commands remain
// explicit state, not inferred from health or substituted thresholds.
struct BattleCpuDriver {
 BattleCpuFrame frame;
 bool network_mode=false; //native6cfdb0==1 command-to-HUMAN voice branch.
 std::array<int,4> assigned_owners{{4,4,4,4}};
 std::array<KeiichiCpuState,4> states{};
 std::array<int,4> commands{};
 std::array<float,4> command_display_scale{}; //314; presentation decay not yet rendered
 std::array<BattleCpuSpecialState,4> special{};
 std::array<unsigned,4> decisions{};
 void configure(const LocalBattleRoster& roster){
  assigned_owners=roster.owner;
  command_display_scale.fill(-10.f); //41dcb0 actor314=c1200000
  for(unsigned i=0;i<4;++i)frame.enabled[i]=roster.owner[i]>=4;
  if(roster.fallback_input)frame.enabled.at(roster.controlled_slots[0])=false;
  //41dcb0 CPU0/human-1, then421730 resets own mode0 for a CPU ally.
  for(unsigned i=0;i<4;++i)commands[i]=frame.enabled[i]||frame.enabled[i^1]?0:-1;
 }
 //417200/419ca0 set860 only. Preserve864..870,310/314 and the action;
 //the native CPU starts from the same acquired bank the HUMAN last used.
 template<class Handoff> void set_actor_owners(const std::array<int,4>& owners,Handoff handoff){
  for(unsigned i=0;i<4;++i){const bool enabled=owners[i]>=4,was_cpu=assigned_owners[i]>=4;
   // A repeated ownership snapshot never writes native860. An actual
   // departure writes1 even after a released F2; no global stop latch exists.
   if(enabled!=was_cpu){if(enabled)handoff(i,frame.slots[i]);frame.enabled[i]=enabled;}
   assigned_owners[i]=owners[i];
  }
 }
 void stop_keyboard_cpu(){frame.enabled.fill(false);}
 void resume_keyboard_cpu(const std::array<int,4>& owners){
  //635684..6356E1 stores1 for CPU owners only; neither controller handoff
  //nor a store to a HUMAN actor belongs to F3.
  for(unsigned i=0;i<4;++i)if(owners[i]>=4)frame.enabled[i]=true;
 }
 // FUN_004201a0 eases the command-emphasis scale by 0.2 per tick until -6.
 // Values at or below zero render at ordinary size in FUN_00644150.
 void advance_command_presentation(){
  for(auto& pulse:command_display_scale)if(pulse>-6.f)pulse-=.2f;
 }
 void advance_common_presentation(std::array<std::array<std::uint8_t,16>,4>& flags){
  for(unsigned actor=0;actor<4;++actor)if(advance_battle_command_emphasis(command_display_scale[actor]))flags[actor][12]=1;
 }
 //635239/6352bd/63512e clear the PERSISTENT acquired CPU bank, before bodies.
 void gate_acquired_frame(const BattlePhaseAdmission& admission){
  for(unsigned actor=0;actor<4;++actor)if(frame.enabled[actor]&&admission.blocks_commands(actor)){
   auto& input=frame.slots[actor];input.x=input.z=0;input.held.fill(0);input.released.fill(0);input.target=input.dash=0;input.auxiliary.fill(0);
  }
 }
 template<class Voice> void apply_acquired_command(const BattleWorld& world,unsigned actor,unsigned age,std::int32_t health,Voice voice){
  const auto& allies=world.actors.at(actor).relationships.allies;if(allies.empty())return;
  const unsigned ally=allies[0];
  advance_battle_ally_command(actor,ally,age,frame.enabled.at(ally),network_mode,health,
   commands.at(actor),commands.at(ally),command_display_scale.at(actor),voice);
 }
 //41f580 after action/target passes: bit32 is an acquisition-time count==1 pulse.
 void apply_command_requests(const BattleWorld& world,const net::InputChannel::Frame& inputs,unsigned actor_mask=15){
  for(unsigned i=0;i<4;++i){
   if(!(actor_mask&(1u<<i))||!(inputs[i].buttons&32)||frame.enabled[i]||commands[i]<0)continue;
   const auto& allies=world.actors[i].relationships.allies;if(allies.empty())continue;
   const unsigned ally=allies[0];if(!frame.enabled.at(ally))continue;
   commands[i]=(commands[i]+1)%6;commands[ally]=commands[i];command_display_scale[i]=2.f;
  }
 }
 template<class Combat,class Query> const BattleCpuFrame& advance(Combat& combat,BattleWorld& world,const Query& query){
  struct Random {Combat& combat;std::uint32_t next(){return combat.next_battle_random();}} random{combat};
  for(unsigned i=0;i<4;++i)if(frame.enabled[i]){
   auto& actor=world.actors[i];const auto& r=actor.relationships;
   const auto& target=world.actors.at(r.target).position;
   auto squared=[&](unsigned slot){const auto& p=world.actors.at(slot).position;volatile float dx=actor.position[0]-p[0],dz=actor.position[2]-p[2];volatile float xx=dx*dx,zz=dz*dz;return float(xx+zz);};
   RosterCpuContext context;context.weapon=combat.action_binding(i).weapon;context.command=commands[i];
   context.action=int(combat.current_action_state(i));context.gauge=combat.gauge[i];context.grounded=actor.grounded!=0;
   // Slot5 reads both actor-owned gauges/flags directly, regardless of mode.
   context.special844=combat.special_gauges[i].active0;context.timer838=damage_signed(combat.special_gauges[i].charge0);
   context.special845=combat.special_gauges[i].active1;context.timer83c=damage_signed(combat.special_gauges[i].charge1);
   context.field_rank=damage_signed(combat.field_contact_rank[i]);context.field_rank_timer=damage_signed(combat.field_contact_rank_timer[i]);
   context.threshold324=damage_signed(combat.actor_assets(i).parameters[0]);context.threshold32c=damage_signed(combat.actor_assets(i).parameters[4]);
   context.obstacle_distance=query.query(actor.position,target,actor.heading).distance;context.distance_squared=squared(r.target);
   //42cd21..42cd27 publishes the CPU ray's distance to actor+80. Later
   // horizontal movement replaces it only when that movement actually runs.
   actor.collision_distance=context.obstacle_distance;
   context.target_index=r.target_index;context.ally_target_index=world.actors.at(r.allies.at(0)).relationships.target_index;
   context.nearest_target_request=cpu_nearest_target_request(r.target_index,combat.targeting[i].cooldown,
    {squared(r.opponents.at(0)),squared(r.opponents.at(1))},
    {damage_signed(combat.stagger[r.opponents[0]].invincible),damage_signed(combat.stagger[r.opponents[1]].invincible)});
   advance_roster_cpu(combat.action_binding(i).character,states[i],frame.slots[i],context,random);
   ++decisions[i];
  }
  return frame;
 }
};
}
