#include "battle_roster_forward_dash.hpp"
#include "battle_death_motion.hpp"
#include "battle_status_visuals.hpp"
#include "battle_aura.hpp"
#include "battle_roster_back_dash.hpp"
#include "battle_roster_back_dash_admission.hpp"
#include "battle_roster_side_dash.hpp"
#include "battle_roster_air_dash_admission.hpp"
#include "battle_roster_air_dash.hpp"
#include "roster_air_dash_cancels.hpp"
#include "battle_roster_walk.hpp"
#include "rena_dash.hpp"
#include "battle_rena_melee.hpp"
#include "battle_rena_melee_admission.hpp"
#include "keiichi_air_melee.hpp"
#include "roster_air_melee.hpp"
#include "roster_ground_dash_melee_admission.hpp"
#include "roster_ground_dash_melee.hpp"
#include "roster_dash_landing_melee340.hpp"
#include "roster_state340.hpp"
#include "roster_dash_followup336.hpp"
#include "roster_state341.hpp"
#include "battle_empty_shot.hpp"
#include "battle_award_record.hpp"
#include "battle_award_result.hpp"
#include "battle_award_reveal.hpp"
#include "battle_air_dash.hpp"
#include "battle_ground_dash.hpp"
#include "battle_target_position.hpp"
#include "battle_target_distance.hpp"
#include "keiichi_normal_projectile.hpp"
#include "keiichi_ground_shot.hpp"
#include "keiichi_walk_shot.hpp"
#include "keiichi_directional.hpp"
#include "roster_directional_melee.hpp"
#include "roster_forward_melee312.hpp"
#include "keiichi_followup.hpp"
#include "roster_ground_combo_admission.hpp"
#include "item36_followup.hpp"
#include "roster_followup301.hpp"
#include "roster_followup302.hpp"
#include "roster_followup_control.hpp"
#include "ground_melee_native_control.hpp"
#include "dash_melee_native_control.hpp"
#include "air_melee_native_control.hpp"
#include "directional_melee_native_control.hpp"
#include "guard_native_control.hpp"
#include "remaining_melee_native_control.hpp"
#include "roster_followup_shot303.hpp"
#include "roster_ground_shot_followup420.hpp"
#include "roster_ground_shot_followup410.hpp"
#include "roster_ground_shot400.hpp"
#include "roster_ground_shot400_motion.hpp"
#include "roster_ground_shot_admission.hpp"
#include "roster_walk_shot_admission.hpp"
#include "roster_walk_shot_execution.hpp"
#include "roster_locomotion_native_control.hpp"
#include "roster_ground_shot400_clock.hpp"
#include "roster_shot401.hpp"
#include "roster_shot401_motion.hpp"
#include "roster_shot401_clock.hpp"
#include "roster_directional_shot.hpp"
#include "roster_air_shot.hpp"
#include "roster_charge_shot.hpp"
#include "roster_natsumi_charge.hpp"
#include "roster_secondary_charge.hpp"
#include "roster_full_shot.hpp"
#include "hanyuu_time_stop_body.hpp"
#include "jump_native_control.hpp"
#include "dash_native_control.hpp"
#include "shoot_native_control.hpp"
#include "full_charge_native_control.hpp"
#include "special_strike_native_control_20261003.hpp"
#include "battle_sound_mode.hpp"
#include "roster_full_charge_admission.hpp"
#include "slot7_native_control.hpp"
#include "slot7_ranked_bodies_20260929.hpp"
#include <limits>
#include "battle_rena_full_charge.hpp"
#include "battle_rena_ground_shot.hpp"
#include "battle_rena_mobile_shooting.hpp"
#include "held_weapon_pose.hpp"
#include "actor_world_hierarchy.hpp"
#include "roster_weapon_visual_policy.hpp"
#include "roster_weapon_trail_policy.hpp"
#include "roster_full_shot_followup.hpp"
#include "roster_throw_followup.hpp"
#include "battle_contact_ledger.hpp"
#include "battle_body_separation.hpp"
#include "keiichi_attack300.hpp"
#include "roster_ground_melee.hpp"
#include "keiichi_special_strike.hpp"
#include "roster_special_strike.hpp"
#pragma once
#include "legacy_host_battle_mirror.hpp"
#include "legacy_host_battle_events.hpp"
#include "item41_projectile.hpp"
#include "battle_actor_assets.hpp"
#include "battle_action_binding.hpp"
#include "battle_dash_recovery.hpp"
#include "battle_dash_followup.hpp"
#include "actor_animated_hit.hpp"
#include "battle_world.hpp"
#include "battle_input_channel.hpp"
#include "actor_world_pose.hpp"
#include "native_actor_spine_prefix.hpp"
#include "battle_frame_input.hpp"
#include <map>
#include <optional>
#include <functional>
#include "actor_animation_clock.hpp"
#include "actor_animation_settings.hpp"
#include "actor_controller_pose.hpp"
#include "actor_skin.hpp"
#include "battle_attack300_motion.hpp"
#include "battle_jump_motion.hpp"
#include "battle_guard_motion.hpp"
#include "battle_walk_motion.hpp"
#include "battle_hit_timers.hpp"
#include "battle_frame_schedule.hpp"
#include "legacy_client_animation_storage.hpp"
#include "battle_vision_effect.hpp"
#include "battle_air_hit_landing.hpp"
#include "battle_common_hit_motion.hpp"
#include "battle_throw_victim135.hpp"
#include "battle_throw_victim135_services_20261004.hpp"
#include "shared_recovery_native_20261004.hpp"
#include "satoko_field_tail.hpp"
#include "battle_local_result.hpp"
#include "battle_victory_script.hpp"
#include "battle_victory_identity.hpp"
#include "battle_target_selection.hpp"
#include "battle_melee_voice_flags.hpp"
#include "battle_direction_warning.hpp"
#include "battle_cpu_frame.hpp"
#include "battle_cpu_driver.hpp"
#include "battle_special_gauges.hpp"
#include "battle_special_entry.hpp"
#include "battle_special_body.hpp"
#include "battle_throw.hpp"
#include "mion_counter.hpp"
#include "mion_melee.hpp"
#include "mion_melee_admission.hpp"
#include "mion_dash_admission.hpp"
#include "mion_mobile_melee.hpp"
#include "mion_ground_shot.hpp"
#include "mion_air_shot.hpp"
#include "mion_mobile_ground_shot.hpp"
#include "mion_charge_shot.hpp"
#include "mion_charge_admission.hpp"
#include "mion_full_charge.hpp"
#include "battle_direct_damage.hpp"
#include "battle_effect_request.hpp"
#include "battle_texture_animation.hpp"
#include "battle_contact_feedback.hpp"
#include "battle_event_feedback.hpp"
#include "battle_voice_inventory.hpp"
#include "battle_voice_selection.hpp"
#include "battle_startup.hpp"
#include "battle_offline_pause.hpp"
#include "battle_phase_services.hpp"
#include "battle_human_input.hpp"
#include "battle_world_presentation.hpp"
#include "battle_frame_tail.hpp"
#include "keiichi_combat_modifiers.hpp"
namespace daybreak {
struct DevelopmentHitHost{
 LegacyHostBattleEvents* native_host=nullptr;
 std::vector<unsigned> calls;
 std::vector<BattleEffectRequest> visuals;
 BattleContactFeedback feedback;
 BattleScoreFeedback score_feedback;
 void effect(std::int32_t id,const std::array<float,3>& position,const std::array<float,3>& direction,unsigned victim){
  calls.push_back(1);visuals.push_back({victim,unsigned(id),position,0,0,direction});
 }
 void reaction(std::int32_t id,const std::array<float,3>& position,unsigned spatial){calls.push_back(2);feedback.reaction(id,position,spatial);}
 void send_hit(const daybreak::LegacyHitNotification& h){calls.push_back(3);if(native_host)native_host->hit(h);}
 void changed(std::uint8_t label,unsigned delta){calls.push_back(4);score_feedback.changed(label,delta);}
 void send(std::uint16_t,std::uint16_t){}void notify(unsigned actor,unsigned code){if(native_host){if(code<4)native_host->defeat(actor,code);else if(code==5||code==6)native_host->system_sound(code,int(actor));}feedback.notify(actor,code);}
 void event(unsigned code){calls.push_back(5);if(native_host)native_host->system_sound(code);feedback.event(code);}
 unsigned phase(unsigned s,unsigned p){calls.push_back(6);return s*10+p;}
 unsigned frame(unsigned e,unsigned i){return e+i;}unsigned animation(unsigned e){return e+1;}void bind(unsigned,unsigned){}
};

// Per-slot resources use the shared DAT-backed action path, with dedicated Rena
// and Mion branches for recovered character-specific melee and counter behavior.
class DevelopmentAnimatedCombat {
 LegacyHostBattleEvents* native_host_=nullptr;
 friend class LegacyClientBattleServices;
 friend class LegacyBattleEventServices;
#ifdef DAYBREAK_ACTOR_FRAME_FLAGS_PROBE
 friend struct NativeActorFrameFlagsProbe;
#endif
#ifdef DAYBREAK_BODY_CONTACTS_PROBE
 friend struct NativeBodyContactsProbe;
#endif
 LegacyClientAnimationStorage legacy_client_actors_;
 unsigned legacy_client_scene_phase_=2;
 BattleActorAssetSlots assets_;
 BattleActionBindings actions_;bool modern_contacts_=false;std::array<KeiichiAttack300,4> keiichi_motion_{};std::array<bool,4> attack_return_{},native_clock_prepared_{},native_clock_geometry_{};
 BattleFrameSchedule frame_schedule_{};unsigned body_frozen_mask_=0;bool frame_services_prepared_=false;
 std::array<unsigned,4> forward_followup_ticks_{};
 std::array<BattleGuardMotion,4> guard_motion_{};
 std::array<unsigned,4> melee_held_{},melee_released_{},jump_held_{};
 std::array<unsigned,4> human_melee_held_{},human_shoot_held_{},human_jump_held_{};
 std::array<BattleHumanInput,4> human_inputs_{};std::array<bool,4> human_input_active_{};
 std::array<std::array<int,2>,4> cpu_acquired_axes_{};unsigned cpu_acquired_mask_=0;
 bool startup_blocked_this_frame_=false;
 bool scene_services_prepared_=false;
 BattlePhaseAdmission frame_admission_;
 std::array<bool,4> phase_commands_blocked_{};
 net::InputChannel::Frame prepared_scene_inputs_{};
 std::array<bool,4> prepared_attack_suppression_{};bool has_prepared_attack_suppression_=false;
 std::array<BattleWalkMotion,4> walk_motion_{};
 std::array<ActorFrameCursor,4> cursors_{};
 std::array<ActorAnimationService,4> animation_services_{};
 std::array<BattleTextureRemaps,4> cached_texture_remaps_{};
 std::array<unsigned char,4> texture_styles_{};
 std::array<ActorSkeleton,4> cached_poses_{};
 std::array<ActorControllerPoseScratch,4> pose_scratch_{};
 std::array<std::vector<LegacyMatrix>,4> cached_world_bones_{};
 std::array<LegacyMatrix,4> cached_world_{};
 std::array<bool,4> cached_world_ready_{},pose_full_admission_pending_{};
 std::array<std::array<unsigned,2>,4> pose_bound_state_{},pose_bound_phase_{};
 std::array<unsigned,4> pose_lower_walk_state_{{~0u,~0u,~0u,~0u}};
 std::array<bool,4> pose_layered_before_{},pose_body_admission_replayed_{};
 std::array<bool,4> pressed_{},jump_pressed_{},air_transition_{},air_jump_used_{};
 std::array<BattleJumpMotion,4> jump_motion_{};
 std::array<BattleAirDash,4> air_dash_{};
 std::array<BattleDashHistory,4> dash_history_{};
 std::array<unsigned,4> dash_command_cache_{};
 std::array<BattleGroundDash,4> ground_dash_{};
 std::array<KeiichiAirMelee,4> air_melee_{};
 std::array<KeiichiGroundShot,4> ground_shot_{};
 std::array<RosterShot400Clock,4> roster_shot_clock_{};
 std::array<RosterShot401Clock,4> roster_shot401_clock_{};
 std::array<RosterDirectionalShotClock,4> roster_directional_clock_{};
 std::array<RosterAirShotClock,4> roster_air_shot_clock_{};
 std::array<RosterChargeShotClock,4> roster_charge_shot_clock_{};
 std::array<RosterFullShotMotionClock,4> roster_full_shot_clock_{};
 std::array<unsigned,4> roster_shot_trigger_{};
 std::array<unsigned,4> owner_orbit_command_{};
 std::array<int,4> projectile_input_x_{};
 std::array<unsigned,4> roster_charge_trigger_{};
 std::array<unsigned,4> projectile_owner_signal_{};
 std::array<KeiichiWalkShot,4> walk_shot_{};
 std::array<std::array<bool,4>,4> contacted_{};
 std::array<bool,4> reaction_active_{},reaction_pending_{},recovery_from_guard_{};
 std::array<float,4> common_hit_gravity_{};
 std::array<unsigned,4> common_hit_scratch_{},common_hit_second_tick_{};
 std::array<bool,4> common_hit_first_voice_{};
 // +7d4 uses the public status_aura_models bank; +7d8 stays in last_hit.last_owner.
 std::array<BattleThrowVictim135,4> throw_victim135_{};
 BattleRandom random_;BattleTeamScore teams_;DevelopmentHitHost host_;
 std::array<float,2> displayed_team_scores_{};
 std::shared_ptr<const BattleVoiceInventory> voice_inventory_;unsigned voice_human_mask_=15;
 std::array<std::int32_t,4> respawn_bounds_{};
 bool respawn_enabled_=false;
 std::array<bool,4> defeat_events_{};
 std::array<unsigned,4> death_wait_{};
 std::array<unsigned,2> team_limits_{{100,100}}; // Development default, selection UI pending.
 int match_health_divisor_=100,match_charge_scale_=100;

public:
 struct ActorStatistics {
  std::array<unsigned,2> dealt{},received{},hits_dealt{},hits_received{};
  unsigned kills=0,deaths=0;
  // 423000: +af08/af0c issued, +af00/af04 received, split by mutual targeting.
  std::array<unsigned,2> attacks_issued{},attacks_received{};
  unsigned charge_shots=0; // actor+af54: admitted stage1 releases
  unsigned full_charge_shots=0; // actor+af50: admitted stage2 releases
  unsigned attacks_at_primary_target=0,attacks_total=0; // +af10/+af18
  unsigned shooting_attacks=0; // 4230e0 / actor+af14; attacks_total retains the 423000 counter.
  unsigned healed_total=0,friendly_hits=0,guards=0; // actor+aefc/af24/af30
  unsigned followup_points=0; // actor+af38, accepted already-dead followup delta
  unsigned step_starts=0; // actor+af48; side/back step phase0 frame0 only
  unsigned empty_shots=0; // actor+af4c, short normal-shot release with empty magazine
  float target_distance_sum=0,target_height_sum=0; // actor+af40/af44, unnormalized
  unsigned match_ticks=0,airborne_ticks=0; // actor+af58/af5c

 };
 // 635d40 case2 samples every actor before testing the match end conditions.
 // Uses the portable math backend; original CRT/x87 bit equivalence is not asserted.
 void record_match_sample(const BattleWorld& world){
  for(unsigned i=0;i<4;++i){
   const auto& actor=world.actors[i];const auto& target=world.actors.at(actor.relationships.target);
   volatile float dx=actor.position[0]-target.position[0],dz=actor.position[2]-target.position[2];
   volatile float xx=float(std::pow(double(dx),2.));
   volatile float squared=float(std::pow(double(dz),2.)+double(xx));
   auto& s=statistics[i];
   s.target_distance_sum=float(double(s.target_distance_sum)+std::sqrt(double(squared)));
   s.target_height_sum=float(double(s.target_height_sum)+double(target.position[1])-double(actor.position[1]));
   ++s.match_ticks;if(!actor.grounded)++s.airborne_ticks;
  }
 }
 // Both original attack-stat helpers use the actor's first ally, not global slot zero.
 void record_shooting_attack(const BattleWorld& world,unsigned slot,unsigned count){
  const auto& actor=world.actors.at(slot);
  const auto target=actor.relationships.target;
  const unsigned bucket=world.actors.at(target).relationships.target==slot?0:1;
  statistics.at(slot).attacks_issued[bucket]+=count;
  statistics.at(target).attacks_received[bucket]+=count;
  statistics.at(slot).shooting_attacks+=count;
  const auto ally=actor.relationships.allies.empty()?0u:actor.relationships.allies[0];
  if(target==world.actors.at(ally).relationships.target)statistics.at(slot).attacks_at_primary_target+=count;
 }
 void record_melee_attack(const BattleWorld& world,unsigned slot,unsigned count){
  const auto& actor=world.actors.at(slot);const auto target=actor.relationships.target;
  const unsigned bucket=world.actors.at(target).relationships.target==slot?0:1;
  statistics.at(slot).attacks_issued[bucket]+=count;statistics.at(target).attacks_received[bucket]+=count;
  const auto ally=actor.relationships.allies.empty()?0u:actor.relationships.allies[0];
  if(target==world.actors.at(ally).relationships.target)statistics.at(slot).attacks_at_primary_target+=count;
  statistics.at(slot).attacks_total+=count;
 }
 //Full and mobile native branches address the same actor scratch words.
 //Keep them together so switching attacks preserves burst/rewind counters.
 std::array<RenaFullChargeMotion,4> rena_full_charge{};
 std::array<RenaGroundShotMotion,4> rena_ground_shots{};
 std::array<RenaMobileInput,4> rena_mobile_resources{};
 std::array<bool,4> rena_shot_strike{};
 std::array<std::array<int,2>,4> rena_held_models{{{{0,1}},{{0,1}},{{0,1}},{{0,1}}}};
 std::array<std::array<int,2>,4> roster_held_models{{{{0,1}},{{0,1}},{{0,1}},{{0,1}}}};
 std::array<bool,4> roster_held_models_initialized{};
 std::array<RosterWeaponTrailController,4> weapon_visual_controllers{};
 std::array<RosterWeaponTrailEffects,4> weapon_visual_commands{};
 std::array<RosterWeaponTrailInput,4> weapon_visual_inputs{};
 std::array<RosterNativeScratch,4> roster_native_scratch{};
 RosterNativeScratch native_melee_scratch(unsigned slot)const{
  auto result=roster_native_scratch.at(slot);result.e8=keiichi_motion_.at(slot).moving;result.ec=keiichi_motion_.at(slot).contact_seen;result.known|=3u;
  if(action_binding(slot).character<3){result.f0=air_melee_.at(slot).strength;result.known|=4u;}
  const auto& binding=action_binding(slot);
  // Original item6/36 callbacks and these actor bodies share actor+f8.
  // Shion weapon1 uses f8 as a local burst counter instead (503510).
  if((binding.character==3&&binding.weapon==1)||
     (binding.character==5&&(binding.weapon==0||binding.weapon==2))){
   result.f8=damage_signed(projectile_owner_signal_.at(slot));result.known|=16u;
  }
  return result;
 }
 void store_native_melee_scratch(unsigned slot,const RosterNativeScratch& value){
  roster_native_scratch.at(slot)=value;keiichi_motion_.at(slot).moving=value.e8;keiichi_motion_.at(slot).contact_seen=value.ec;
  if(value.known&4u)air_melee_.at(slot).strength=value.f0;
  if(value.known&16u)projectile_owner_signal_.at(slot)=unsigned(value.f8);
 }
 void reset_native_state_metadata(unsigned slot){
  //421080 resets684; its421100 phase admission resetsAE08. Motion/pose
  //admission remains with the existing state owners.
  native_contact_mode.at(slot)=-1;native_melee_second_tick.at(slot)=0;
  air_melee_.at(slot).pitch=0; //421080 resets actor+2c before phase admission.
  native_extra_yaw.at(slot)=native_orientation34.at(slot)=0; // actor+30/+34; pivot+2d8 carries.
  idle_tick.at(slot)=walk_tick.at(slot)=locomotion_phase.at(slot)=locomotion_second_tick.at(slot)=0;
  cursors_.at(slot)={}; //421100 resets ADFC before admitting frame zero.
  pose_full_admission_pending_.at(slot)=true;
 }
 void reset_native_upper_state_metadata(unsigned slot){
  //4211f0/421240: mode and primary admission only. Lower clock, lower
  //animation, pitch and orientation carry across walking-shot entry/return.
  native_contact_mode.at(slot)=-1;cursors_.at(slot)={}; //421240 resets ADFC too.
  pose_full_admission_pending_.at(slot)=true;
 }
 RosterFollowupControlMotion native_followup_motion(const BattleWorld& world,unsigned slot)const{
  const auto& actor=world.actors.at(slot);float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
  return {actor.motion.speed,offset,actor.motion.angles[1],actor.motion.velocity[1],ground_shot_.at(slot).gravity,walk_motion_.at(slot).step,native_contact_mode.at(slot)};
 }
 DashMeleeNativeMotion native_dash_melee_motion(const BattleWorld& world,unsigned slot)const{
  DashMeleeNativeMotion result;static_cast<RosterFollowupControlMotion&>(result)=native_followup_motion(world,slot);
  result.pitch=air_melee_.at(slot).pitch;result.pivot=air_melee_.at(slot).pivot;result.extra68=native_extra68.at(slot);return result;
 }
 void store_native_air_melee_motion(BattleWorld& world,unsigned slot,const AirMeleeNativeMotion& state){
  auto& actor=world.actors.at(slot);auto& action=keiichi_motion_.at(slot);
  action.speed=actor.motion.speed=state.speed;action.offset=state.offset;action.movement_angle=actor.motion.angles[1]=state.movement;
  std::memcpy(&actor.relationships.heading_offset_bits,&state.offset,4);actor.motion.velocity[1]=state.vertical;
  ground_shot_.at(slot).gravity=air_melee_.at(slot).gravity=state.gravity;walk_motion_.at(slot).step=state.turn;
  native_contact_mode.at(slot)=state.contact_mode;air_melee_.at(slot).pitch=state.pitch;air_melee_.at(slot).pivot=state.pivot;native_extra68.at(slot)=state.extra68;
 }
 std::array<std::array<unsigned char,3>,4> melee_voice_flags{};
 std::array<int,4> roster_weapon_visual_ec{}; // Irie1 +ec, shared by full350/360
 std::array<unsigned,4> rena_held_model_state{{~0u,~0u,~0u,~0u}};
 std::array<unsigned,4> shoot_held{},shoot_released{},shoot_release_charge{};
 std::array<unsigned,4> death_bonus_used{}; // actor+84c; reset by respawn4219a0
 // Per-move events, consumed by LocalNormalProjectiles before the next move.
 struct ShotRequest {unsigned actor=0;GroundShotEffects shot;std::array<float,3> position{};float heading=0;unsigned target=0;};
 std::vector<ShotRequest> shot_requests;
 using EffectRequest=BattleEffectRequest;
 std::vector<EffectRequest> effect_requests;
 using SoundRequest=BattleContactSoundRequest;
 std::vector<SoundRequest> sound_requests;
 using VoiceRequest=BattleEventVoiceRequest;
 std::vector<VoiceRequest> voice_requests;
 void configure_native_host_events(LegacyHostBattleEvents& host){
  if(legacy_client_actors_)throw std::logic_error("Client cannot emit host events");
  native_host_=&host;host_.native_host=&host;
  for(unsigned i=0;i<4;++i){special_gauges[i].native_host=&host;special_gauges[i].native_actor=i;}
 }
 void queue_effect(EffectRequest request){if(native_host_)native_host_->effect(request);effect_requests.push_back(std::move(request));}
 void queue_sound(SoundRequest request){
  if(native_host_){if(request.system)native_host_->system_sound(request.id,request.local_only?int(request.actor):-1);
   else native_host_->spatial_sound(request.id,request.position,unsigned(request.mode));}
  sound_requests.push_back(request);
 }
 //4221E0 stores828 before sending28. Decrements/expiry do not re-notify.
 void begin_native_time_stop(unsigned actor,unsigned ticks){time_stop_ticks.at(actor)=ticks;if(native_host_)native_host_->time_stop(actor,ticks);}
 //422ED0 stores flag/computed pitch before sending22;422F40 clears only flag.
 void set_native_manual_aim(unsigned actor,unsigned flag,float pitch){full_charge_manual_flag_.at(actor)=int(flag);if(flag&255u)full_charge_manual_aim_.at(actor)=pitch;if(native_host_)native_host_->manual(actor,flag&255u,pitch);}
 void activate_presentation(unsigned actor){if(native_host_)native_host_->activated(actor);special_gauges.at(actor).activated0=true;}
 void configure_voice_selection(std::shared_ptr<const BattleVoiceInventory> inventory,const std::array<int,4>& owners){
  voice_inventory_=std::move(inventory);voice_human_mask_=0;
  for(unsigned i=0;i<4;++i)if(owners[i]>=0&&owners[i]<4)voice_human_mask_|=1u<<i;
 }
 void queue_voice(VoiceRequest request){
  if(request.actor>=4)throw std::out_of_range("Battle voice actor");
  if(native_host_&&request.recipient>=0)native_host_->voice(request); //before HUMAN selection gate
  const auto& s=special_gauges[request.actor];
  const bool active=request.bank<0?(s.active0||s.active1||s.active2):request.bank!=0;
  if(voice_inventory_){const auto bank=voice_inventory_->bank(request.actor,active);
   resolve_battle_voice_selection(request,bank,unsigned(voice_inventory_->names(request.actor,bank,request.category).size()),random_,voice_human_mask_);
  }
  if(native_host_&&request.recipient<0)native_host_->voice(request); //after local selection, without another RNG draw
  voice_requests.push_back(request);
 }
 struct ShotCallbackVisit {unsigned actor=0;RosterShot400Kind kind{};int value=0;
  unsigned primary_before=0,primary_after=0,attacks_before=0,attacks_after=0;
  bool admitted=false,native_order=false;};
 std::vector<ShotCallbackVisit> shot_callback_visits;
 std::array<GroundShotEffects,4> ground_shot_effects{};
 std::array<BattleStatusTickEffects,4> status_tick_effects{};
 std::array<std::vector<BattleStatusVisualEvent>,4> status_visual_events{};
#ifdef DAYBREAK_STATUS_VISUAL_PROBE
 BattleRandom status_visual_random()const{return random_;}
#endif
 std::array<unsigned,4> shots_attempted{},shots_spawn_requested{};
 std::array<BattleContactLedger,4> contact_ledger{};
 std::array<std::array<BattleMagazine,2>,4> magazines{}; // Per-slot ammo; ground400 consumes on accepted spawn requests.
 std::array<ActorStatistics,4> statistics{};
 BattleAwardResult awards;
 std::array<BattleTargetSelection,4> targeting{};
 std::array<std::vector<BattleDirectionWarning>,4> direction_warnings;
 std::array<BattleTargetAvailability,4> target_availability{};
 std::array<int,4> elapsed{{-1,-1,-1,-1}};
 bool use_recovered_melee_timing=false; // Runtime enables it; old probes retain immediate-edge fixtures.
 std::array<unsigned,4> attack_state{{300,300,300,300}};
 std::array<KeiichiFollowupEffects,4> followup_effects{};
 std::array<RosterFollowupControlEffects,4> followup_control_effects{};
 std::array<bool,4> followup_control_visited{};
 std::array<GroundMeleeNativeEffects,4> ground_melee_control_effects{};
 std::array<bool,4> ground_melee_control_visited{};
 std::array<DashMeleeNativeEffects,4> dash_melee_control_effects{};
 std::array<bool,4> dash_melee_control_visited{};
 std::array<AirMeleeNativeEffects,4> air_melee_control_effects{};
 std::array<bool,4> air_melee_control_visited{};
 std::array<DirectionalMeleeNativeEffects,4> directional_melee_control_effects{};
 std::array<bool,4> directional_melee_control_visited{};
 std::array<GuardNativeEffects,4> guard_native_effects{};
 std::array<GuardNativeMotion,4> guard_native_motion{}; // body output before common facing/physics.
 std::array<bool,4> guard_native_visited{};
 std::array<RemainingMeleeNativeInput,4> remaining_melee_control_input{};
 std::array<RemainingMeleeNativeEffects,4> remaining_melee_control_effects{};
 std::array<RemainingMeleeNativeMotion,4> remaining_melee_control_motion{}; // final native body, before common facing/physics.
 std::array<bool,4> remaining_melee_control_visited{};
 struct RemainingPhaseRecovery {bool active=false;unsigned state=0,requested=0,phase_count=0,recovery_state=0;};
 std::array<RemainingPhaseRecovery,4> remaining_phase_recovery{};
 std::array<float,4> native_extra_yaw{}; // actor+30, used by both420b30 pose branches.
 std::array<float,4> native_orientation34{}; // actor+34; reset proven, other use unproven.
 std::array<unsigned,4> native_melee_second_tick{};
 std::array<int,4> native_contact_mode{{-1,-1,-1,-1}}; // actor+684, also written by the hit pipeline.
 std::array<KeiichiDashMeleeEffects,4> dash_melee_effects{};
 std::array<BattleTimedDiveFollowupEffects,4> dash_followup_effects{};
 std::array<BattleGroundDashStep,4> ground_dash_effects{};
 std::array<unsigned,4> attack_phase{},air_state{},air_phase{},air_tick{};
 std::array<unsigned,4> health{{10000,10000,10000,10000}};
 std::array<unsigned,4> delayed_health{{10000,10000,10000,10000}};
 std::array<unsigned,4> ground_hit_state{},ground_hit_phase{},ground_hit_tick{};
 std::array<unsigned,4> reaction_phase{},reaction_tick{},recovery_move_ticks{};
 std::array<ThrowVictim135Presentation,4> throw_victim135_presentation{};
 std::array<bool,4> throw_victim135_visited{};
 std::array<bool,4> shared_recovery_visited{};
 std::array<std::vector<SharedRecoveryEvent>,4> shared_recovery_events{};
 std::array<unsigned,4> stop_ticks{},recovery_state{},recovery_phase{},recovery_tick{};
 std::array<unsigned,4> time_stop_ticks{},long_stop_ticks{}; // native+828/+82c, separate from+a0.
 std::array<std::uint8_t,4> vision_alpha{}; // actor+824 viewport flash/darkness opacity.
 std::array<int,4> status_aura_models{{-1,-1,-1,-1}}; // native +7d4, written by42e110.
 std::array<BattleHitPipelineState,4> last_hit{};
 std::array<BattleHitPipelineInput,4> geometry{};
 unsigned hits=0,guards=0,prepared_attack_mask=0;
 std::array<KeiichiAttack300Effects,4> attack_effects{};
 BattleLocalResult match;
 BattleStartup startup;
 BattleOfflinePause offline_pause;
 void configure_offline_pause(bool enabled){offline_pause={};offline_pause.enabled=enabled;}
 BattlePhaseNotices phase_notices;
 bool scene_start_music_event=false;
 unsigned scene_phase()const{if(legacy_client_actors_)return legacy_client_scene_phase_;return startup.enabled?battle_scene_phase(startup,match):2;}
 //635d40 follows42e110/slot9 and precedes41f580/movement/contacts.
 void advance_scene_services(const BattleWorld& world,const std::array<unsigned,4>& buttons){
  const unsigned phase=scene_phase();const auto presses=match.input_edges(buttons);
  scene_start_music_event=false;
  if(phase!=1){
   if(match.winner<0)record_match_sample(world);
   std::array<bool,4> defeated=defeat_events_;
   if(startup.enabled)for(unsigned i=0;i<4;++i)defeated[i]=defeated_flags[i]!=0;
   if(native_host_){
    if(phase==2&&match.timed)native_host_->clock(match.remaining_ticks);
    if((phase==4||phase==5)&&match.ready&&match.presentation_phase==5&&!match.presentation_offset){
     if(!awards.ready)throw std::logic_error("Host awards must be finalized before presentation");
     native_host_->awards(awards.ids);
    }
   }
   battle_award_reveal_sounds(match,presses,[&](unsigned id){queue_sound({0,id,{},BattleSoundMode::Plain,false,true,false});});
   const bool was_timed_out=match.timed_out;
   match.advance(team_limits_,teams_.score,defeated,health,random_,presses);defeat_events_={};
   if(match.story_sound>=0)queue_sound({0,unsigned(match.story_sound),{},BattleSoundMode::Plain,false,true,false});
   if(native_host_&&!was_timed_out&&match.timed_out)native_host_->timeout(unsigned(match.winner));
   if(startup.enabled&&phase==2){
    if(match.timed_out)last_defeat_attacker=unsigned(match.winner)*2+1;
    else for(unsigned i=0;i<4;++i){
     if(defeated_flags[i]){
      if(remaining_battle_resource(team_limits_[i/2],teams_.score[i/2])>0){startup.notice_type[i]=1;startup.notice_ticks[i]=120;startup.notice_scale[i]=8;}
      else queue_sound({i,11,{},BattleSoundMode::Plain,false,true,false});
     }else if(defeat_credit_flags[i]){queue_sound({i,8,{},BattleSoundMode::Plain,false,true,true});startup.notice_type[i]=0;startup.notice_ticks[i]=90;startup.notice_scale[i]=8;}
    }
    if(match.winner>=0)phase_notices.begin_finish();
   }else if(startup.enabled&&phase==3&&phase_notices.advance_finish(match.countdown))queue_sound({0,12,{},BattleSoundMode::Plain,false,true,false});
  }
  scene_start_music_event=startup.advance();
 }
 void configure_battle_start(const std::optional<BattleRandom>& state={}){
  if(state)random_=*state;startup.reset();startup_blocked_this_frame_=true;
 }
 std::array<int,4> gauge{{1000,1000,1000,1000}};
 std::array<BattleHitStagger,4> stagger{};
 std::array<BattleHitStatus,4> status{};
 std::array<BattleSpecialGauges,4> special_gauges{};
 std::array<KeiichiCombatModifiers,4> combat_modifiers{}; // input-pass snapshot, before status timer expiry
 std::array<MionCounterMotion,4> mion_counter{};
 std::array<MionGroundShot,4> mion_ground_shots{};
 std::array<MionChargeShot,4> mion_charge_shots{};
 std::array<MionChargeEffects,4> mion_charge_effects{};
 std::array<MionFullCharge,4> mion_full_charges{};
 std::array<MionFullChargeEffects,4> mion_full_charge_effects{};
 std::array<unsigned,4> mion_captures{},mion_releases{},mion_counter_windows{};
 // Original item17 owner+af60/af64: contact rank shared by its field bullets.
 std::array<unsigned,4> field_contact_rank{},field_contact_rank_timer{},satoko_mine_clock{};
 // Original item6/10 writes owner+af60..+af68 while its guided shot lives.
 std::array<std::array<float,3>,4> projectile_owner_aim{};
 std::array<std::array<float,2>,4> projectile_owner_aim_velocity{};
 std::array<bool,4> projectile_owner_aim_initialized{};
 // Takano1 reuses +af60..68 as signed integer coordinates and +af6c as
 // a per-actor-visit stop notification. Other items' float aim is separate.
 std::array<std::array<std::int32_t,3>,4> projectile_owner_integer_field{};
 std::array<unsigned,4> projectile_owner_field_exit{};
 float projectile_owner_pitch(unsigned actor)const{return throw_victim135_.at(actor).pitch;}
 std::array<KeiichiSpecialStrike,4> special_strike{};
 std::array<BattleSpecialEntry,4> special_entry{};
 std::array<BattleSpecialEntryEffects,4> special_entry_effects{};
 std::array<BattleSpecialBodyEffects,4> special_body_effects{};
 std::array<bool,4> special_body_visited{};
 std::array<bool,4> hanyuu_time_stop_visited{};
 std::array<HanyuuTimeStopEffects,4> hanyuu_time_stop_effects{};
 std::array<bool,4> jump_native_visited{};
 std::array<JumpNativeInput,4> jump_native_inputs{};
 std::array<JumpNativeEffects,4> jump_native_effects{};
 std::array<JumpNativeMotion,4> jump_native_motions{};
 std::array<float,4> native_extra68{};
 std::array<bool,4> dash_native_visited{};
 std::array<DashNativeInput,4> dash_native_inputs{};
 std::array<DashNativeEffects,4> dash_native_effects{};
 std::array<DashNativeMotion,4> dash_native_motions{};
 struct SpecialActivationEvent{unsigned slot,notification,voice;};
 std::vector<SpecialActivationEvent> special_activation_events; // runtime consumes local system-SE feedback
 std::array<std::string,4> attachment_bones{}; //41ED66/423530: persistent original Prop1, Natsumi Prop2 binding
 std::array<std::uint8_t,4> capture_modes{},defeated_flags{}; //aed8/aeca
 std::array<unsigned,4> special_button290{}; // Physical chord age; human acquisition and body feedback share the actor controller bank
 std::array<unsigned,4> death_state{},death_phase{},death_tick{};
 std::array<unsigned,4> ninth_status_timer{}; // native+7fc, after the eight attack-owned timers.
 std::array<std::array<std::uint8_t,16>,4> death_reset_flags{}; // native+aeb8..aec7, including independently owned bytes.
 std::array<std::uint8_t,4> defeat_credit_flags{}; // native+aec9, outside respawn reset bytes.
 unsigned last_defeat_attacker=0; // scene+4428 initialized by634760.
 std::array<std::uint8_t,16> native_death_flags(unsigned slot)const{
  auto flags=death_reset_flags.at(slot);
  flags[11]=melee_voice_flags.at(slot)[0];flags[6]=melee_voice_flags.at(slot)[1];flags[1]=melee_voice_flags.at(slot)[2];
  flags[2]=stagger.at(slot).back_flag;flags[3]=common_hit_first_voice_.at(slot);
  flags[8]=std::uint8_t(status.at(slot).newly_applied);flags[10]=std::uint8_t(special_gauges.at(slot).notice_ready1);return flags;
 }
 void store_native_death_flags(unsigned slot,const std::array<std::uint8_t,16>& flags){
  death_reset_flags.at(slot)=flags;
  melee_voice_flags.at(slot)={flags[11],flags[6],flags[1]};
  stagger.at(slot).back_flag=flags[2];common_hit_first_voice_.at(slot)=flags[3]!=0;
  status.at(slot).newly_applied=flags[8];special_gauges.at(slot).notice_ready1=flags[10];
 }
 //634f60: slot9 after42e110, before41f580 timers/gauges; query target+308.
 void advance_native_battle_events(const BattleWorld& world,unsigned slot){
  auto flags=native_death_flags(slot);std::int8_t level;std::memcpy(&level,&flags[5],1);
  BattleEventState state{damage_signed(current_action_state(slot)),damage_signed(health.at(slot)),level,flags[7],flags[0],flags[8],flags[9],flags[10]};
  const auto& actor=world.actors.at(slot);const unsigned ally=actor.relationships.allies.empty()?0u:actor.relationships.allies[0];
  const unsigned target=actor.relationships.target;const auto& binding=action_binding(slot);
  const auto feedback=advance_battle_event_feedback(state,slot,ally,remaining_battle_resource(team_limits_.at(target/2),teams_.score.at(target/2)),binding.character==9&&binding.weapon==0);
  for(const auto& request:feedback.voices)queue_voice(request);
  std::memcpy(&flags[5],&state.level,1);flags[7]=state.flag_bf;flags[0]=state.flag_b8;flags[8]=state.flag_c0;flags[9]=state.flag_c1;flags[10]=state.flag_c2;
  store_native_death_flags(slot,flags);
 }
 struct NativeDeathEvent{char kind;unsigned value;std::array<float,3> position;};
 std::array<std::vector<NativeDeathEvent>,4> death_native_events{};
#ifdef DAYBREAK_DEATH_WORLD_PROBE
 ActorFrameCursor death_frame_cursor(unsigned slot)const{return cursors_.at(slot);}
#endif
#ifdef DAYBREAK_RANKED_WORLD_PROBE
 ActorFrameCursor ranked_frame_cursor(unsigned slot)const{return cursors_.at(slot);}
#endif
 std::array<BattleDeathMotion,4> death_native_motion{};
 std::array<bool,4> death_native_visited{};
 bool enable_native_death=true; // Original428510/4219a0; native body and all46 DAT world composition verified.
 std::array<unsigned,4> walk_tick{};
 std::array<unsigned,4> idle_tick{},locomotion_phase{},locomotion_second_tick{};
 std::array<bool,4> locomotion_native_visited{};
 std::array<RosterLocomotionNativeInput,4> locomotion_native_input{};
 std::array<RosterLocomotionNativeMotion,4> locomotion_native_motion{};
 std::array<RosterLocomotionNativeEffects,4> locomotion_native_effects{};
 // Original actor+68. Keiichi initializes this to0 and does not modify it.
 std::array<float,4> spine_yaw{};
 std::array<bool,4> walking{};
 std::array<unsigned,4> guard_state{},guard_phase{},guard_tick{},guard_flags{};
 DevelopmentAnimatedCombat(const std::vector<std::uint8_t>& model,const std::vector<std::uint8_t>& frames,bool keiichi_attack=false)
 :DevelopmentAnimatedCombat(repeated_battle_assets(model,frames),keiichi_attack){}
 explicit DevelopmentAnimatedCombat(BattleActorAssetSlots assets,bool keiichi_attack=false)
 :DevelopmentAnimatedCombat(std::move(assets),repeated_battle_actions(keiichi_attack)){}
 DevelopmentAnimatedCombat(BattleActorAssetSlots assets,BattleActionBindings actions):assets_(std::move(assets)),actions_(std::move(actions)){
  teams_.label={0,1}; //634980: native display labels, independent of actor/view ownership.
  for(const auto& action:actions_){
   if(action.policy==BattleActionPolicy::keiichi_basic){
    const auto expected=basic_battle_action(action.character,action.weapon);
    if(action.original_update!=expected.original_update)throw std::invalid_argument("Mismatched action dispatch");
    modern_contacts_=true;
   }else if(action.policy==BattleActionPolicy::mion_counter){
    const auto expected=mion_counter_action(action.weapon);if(action.character!=1||action.original_update!=expected.original_update)throw std::invalid_argument("Mismatched Mion counter dispatch");modern_contacts_=true;
   }else if(action.policy==BattleActionPolicy::rena_melee){
    if(action.character!=0||action.original_update!=character_action_dispatch(0,action.weapon).update)throw std::invalid_argument("Mismatched Rena dispatch");modern_contacts_=true;
   }else if(action.policy==BattleActionPolicy::data_driven_preview){
    modern_contacts_=true; // Shared physics/targeting/gauges must not depend on a Mion/Keiichi teammate.
    if(action.original_update!=character_action_dispatch(action.character,action.weapon).update)throw std::invalid_argument("Mismatched preview dispatch");
   }else if(action.policy!=BattleActionPolicy::legacy_test)throw std::invalid_argument("Unknown action policy");
  }
  for(unsigned i=0;i<4;++i)if(assets_[i]){special_gauges[i].limit0=assets_[i]->parameters[0];special_gauges[i].limit1=assets_[i]->parameters[4];special_gauges[i].duration0=assets_[i]->parameters[1];special_gauges[i].duration1=assets_[i]->parameters[5];}
  for(unsigned i=0;i<4;++i)if(assets_[i]&&assets_[i]->weapon_item){
   magazines[i]=assets_[i]->weapon_item->magazines;
   auto& c=weapon_visual_controllers[i];const auto& item=*assets_[i]->weapon_item;
   for(unsigned slot=0;slot<2;++slot)if(slot<item.attachments.size()&&!item.attachments[slot].model.empty()){
    c.selected[slot]=int(slot);c.bound_slot[slot]=int(slot);
   }
  }
  for(unsigned i=0;i<4;++i)if(assets_[i]){
   const std::string bone=action_binding(i).character==15?"Bip01_Prop2":"Bip01_Prop1";
   //64E6C0 returns null for a missing bone; do not invent a root binding.
   if(assets_[i]->base_.find(bone))attachment_bones[i]=bone;
  }
  for(const auto& data:assets_)if(!data||data->attack_phases_.empty())throw std::runtime_error("Unsupported development action phase layout");
  for(unsigned i=0;i<4;++i){auto& service=animation_services_[i];const auto& data=actor_assets(i);
   service.configure(action_binding(i).character,action_binding(i).weapon,data.animation_settings_);
   service.bind_both(data.idle_animation_);
   snapshot_actor_texture_remaps(i);
   cached_poses_[i]=evaluate_actor_controller_pose(data.base_,service,data.animations_,data.animation_last_keys_,data.ticks_per_second_,0);
  }
 }
 unsigned current_action_state(unsigned i)const{
  if(legacy_client_actors_)return std::uint32_t(legacy_client_actors_->at(i).state[0]);
  return death_state.at(i)?death_state[i]:special_entry[i].state?special_entry[i].state:ground_hit_state[i]?ground_hit_state[i]:guard_state[i]?guard_state[i]:air_state[i]?air_state[i]:recovery_state[i]?recovery_state[i]:reaction_active_[i]?last_hit[i].normal.action.state:elapsed[i]<0?(walking[i]?10:0):attack_state[i];
 }
 const BattleActionBinding& action_binding(unsigned slot)const{return actions_.at(slot);}
 bool uses_mion_counter(unsigned slot)const{return action_binding(slot).policy==BattleActionPolicy::mion_counter;}
 bool uses_rena(unsigned slot)const{return action_binding(slot).policy==BattleActionPolicy::rena_melee;}
 // Every roster fighter uses the recovered shared actor pipeline. Character
 // specific branches below override it where their handler has been recovered.
 bool uses_recovered_actor(unsigned slot)const{return action_binding(slot).policy!=BattleActionPolicy::legacy_test;}
 bool uses_keiichi(unsigned slot)const{return action_binding(slot).policy==BattleActionPolicy::keiichi_basic;}
 bool uses_layered_walk_shot(unsigned slot)const{
  if(!keiichi_walk_shot_state(attack_state.at(slot)))return false;
  const auto& binding=action_binding(slot);
  return binding.policy==BattleActionPolicy::keiichi_basic||
   (binding.policy==BattleActionPolicy::data_driven_preview&&
    roster_walk_shot_recovered(binding.character,binding.weapon));
 }
 int projectile_input_x(unsigned slot)const{return projectile_input_x_.at(slot);}
 int actor_input_x(unsigned slot,const net::Input& input)const{return cpu_acquired_mask_&(1u<<slot)?cpu_acquired_axes_.at(slot)[0]:human_input_active_.at(slot)?human_inputs_.at(slot).x():input.x;}
 int actor_input_z(unsigned slot,const net::Input& input)const{return cpu_acquired_mask_&(1u<<slot)?cpu_acquired_axes_.at(slot)[1]:human_input_active_.at(slot)?human_inputs_.at(slot).z():input.z;}
 void handoff_native_cpu_input(unsigned actor,KeiichiCpuInput& acquired){
  auto& human=human_inputs_.at(actor);auto& words=human.controller.words;
  if(human_input_active_.at(actor)){
   acquired.x=human.x();acquired.z=human.z();
   for(unsigned b=0;b<3;++b){acquired.held[b]=controller_signed(words[16+b]);acquired.released[b]=controller_signed(human.released[b]);}
   acquired.target=controller_signed(words[19]);acquired.dash=int(dash_command_cache_[actor]);
   for(unsigned b=0;b<4;++b)acquired.auxiliary[b]=words[20+b];
  }
  words[24]&=0xffffff00u; //414670: disable packed input, do not clear its bank.
 }
#ifdef DAYBREAK_NATIVE_CLIENT_RUNTIME_PROBE
 const BattleHumanInput& native_human_input_probe(unsigned actor)const{return human_inputs_.at(actor);}
#endif
#ifdef DAYBREAK_INPUT_START_PROBE
 friend struct BattleInputStartProbe;
#endif
#ifdef DAYBREAK_FRAME_TAIL_PROBE
 friend struct BattleFrameTailProbe;
#endif
 unsigned owner_orbit_command(unsigned slot)const{return owner_orbit_command_.at(slot);}
 std::array<std::uint32_t,5> common_hit_persistent_words(unsigned slot)const{
  std::uint32_t gravity;const auto value=common_hit_gravity_.at(slot);std::memcpy(&gravity,&value,4);
  return {gravity,common_hit_scratch_.at(slot),common_hit_second_tick_.at(slot),
   unsigned(common_hit_first_voice_.at(slot)),std::uint32_t(status_aura_models.at(slot))};
 }
 unsigned projectile_owner_phase(unsigned i)const{
  if(legacy_client_actors_)return legacy_client_actors_->at(i).phase[0];
  return death_state[i]?death_phase[i]:special_entry[i].state?special_entry[i].phase:ground_hit_state[i]?ground_hit_phase[i]:guard_state[i]?guard_phase[i]:air_state[i]?air_phase[i]:recovery_state[i]?recovery_phase[i]:reaction_active_[i]?reaction_phase[i]:elapsed[i]>=0?attack_phase[i]:locomotion_phase[i];
 }
 unsigned projectile_owner_animation_frame(unsigned i)const{
  if(legacy_client_actors_)return std::uint32_t(legacy_client_actors_->at(i).frame[0]);
  return death_state[i]?death_tick[i]:special_entry[i].state?special_entry[i].frame:ground_hit_state[i]?ground_hit_tick[i]:guard_state[i]?guard_tick[i]:air_state[i]?air_tick[i]:recovery_state[i]?recovery_tick[i]:reaction_active_[i]?reaction_tick[i]:elapsed[i]>=0?unsigned(elapsed[i]):walking[i]?walk_tick[i]:idle_tick[i];
 }
 unsigned persistent_actor_cursor(unsigned slot)const{return cursors_.at(slot).index;}
 LegacyHostMirrorActor native_host_actor(const BattleWorld& world,unsigned slot)const{
  if(legacy_client_actors_)throw std::logic_error("Client cannot export authoritative host state");
  LegacyHostMirrorActor out;const auto& actor=world.actors.at(slot);auto& p=out.snapshot;
  p.position=actor.position;p.heading=actor.heading;std::memcpy(&p.offset,&actor.relationships.heading_offset_bits,4);
  const auto& animation=animation_services_.at(slot);
  //AE0C/AE10 are channel0/1, while ADEC/ADF0 are main/lower states.
  //421240 binds channel1 only. Do not swap animation IDs to match clocks.
  p.body[0]={animation.channels[0].selected,damage_signed(current_action_state(slot)),projectile_owner_phase(slot),damage_signed(projectile_owner_animation_frame(slot))};
  p.body[1]={animation.channels[1].selected,damage_signed(pose_bound_state_[slot][0]),pose_bound_phase_[slot][0],damage_signed(actor_secondary_animation_frame(slot))};
  const auto& trail=weapon_visual_controllers.at(slot);out.weapon=trail.selected;out.trail=std::uint8_t(trail.own);
  out.stop=damage_signed(stop_ticks.at(slot));out.invincible=damage_signed(stagger.at(slot).invincible);
  out.opponent=damage_signed(actor.relationships.target_index);out.ally=targeting.at(slot).ally_index;
  const auto motion=native_dash_melee_motion(world,slot);
  out.pose={motion.pitch,native_extra_yaw.at(slot),native_orientation34.at(slot),native_extra68.at(slot)};out.pivot=motion.pivot;
  for(unsigned j=0;j<8;++j)out.status[j]=damage_signed(status.at(slot).duration[j]);out.status[8]=damage_signed(ninth_status_timer.at(slot));
  const auto& g=special_gauges.at(slot);out.mode=std::uint8_t(g.mode);out.charge={damage_signed(g.charge0),damage_signed(g.charge1),damage_signed(g.charge2)};
  out.health=damage_signed(health.at(slot));out.movement=gauge.at(slot);out.contact=native_contact_mode.at(slot);
  for(unsigned j=0;j<2;++j)out.magazines[j]=damage_signed(magazines.at(slot)[j].rounds);
  const auto& magazine=magazines.at(slot)[1];out.charge_progress={damage_signed(magazine.word1c),damage_signed(magazine.word20)};
  out.manual=(unsigned(full_charge_manual_flag_.at(slot))&255u)!=0;out.manual_pitch=full_charge_manual_aim_.at(slot);return out;
 }
 const ActorAnimationService& animation_service(unsigned slot)const{return legacy_client_actors_?legacy_client_actors_->at(slot).animation:animation_services_.at(slot);}
 const BattleTextureRemaps& render_texture_remaps(unsigned slot)const{return cached_texture_remaps_.at(slot);}
 void configure_actor_texture_styles(const std::array<unsigned char,4>& styles){
  texture_styles_=styles;for(unsigned i=0;i<4;++i)snapshot_actor_texture_remaps(i);
 }
 void snapshot_actor_texture_remaps(unsigned slot){
  // 41f580 freezes DAT events and overrides before 637680 can admit a hit.
  // A skipped time-stop service retains the previous frame's replacements.
  auto& remaps=cached_texture_remaps_[slot];
  unsigned id=animation_services_[slot].channels[1].selected;
  if(legacy_client_actors_){std::array<unsigned,2> selected;
   if(!resolve_legacy_snapshot_tracks(legacy_client_actors_->at(slot),actor_assets(slot),selected))throw std::out_of_range("Native client texture DAT state/phase");
   id=selected[1];
  }
  remaps=battle_texture_remaps(actor_assets(slot).animation_settings_.at(id),damage_signed(projectile_owner_animation_frame(slot)));
  const auto& special=special_gauges[slot];
  if(special.active0||special.active2)remaps[battle_texture_name_key("\x88\xea\x96\xda.bmp")]="\x82\xd0\x82\xae\x82\xe7\x82\xb5\x96\xda.bmp";
  if(texture_styles_[slot]){
   remaps[battle_texture_name_key("\x95\x9e.bmp")]="\x95\x9e" "2.bmp";
   remaps[battle_texture_name_key("\x83\x58\x83\x4a\x81\x5b\x83\x67.bmp")]="\x83\x58\x83\x4a\x81\x5b\x83\x67" "2.bmp";
  }
 }
 std::array<std::uint64_t,4> pose_generation{};
 void bind_actor_animation_state(unsigned slot,unsigned state,unsigned phase=0,bool upper_only=false){
  const auto& data=actor_assets(slot);const auto resolved=reaction_animation_state(slot,state);
  const auto found=data.state_frames_.find(resolved);
  if(found==data.state_frames_.end()||phase>=found->second.size())throw std::out_of_range("Actor animation admission outside DAT");
  const auto id=found->second[phase].value;
  if(!upper_only){animation_services_[slot].bind(0,id);pose_bound_state_[slot][0]=state;pose_bound_phase_[slot][0]=phase;}
  animation_services_[slot].bind(1,id);pose_bound_state_[slot][1]=state;pose_bound_phase_[slot][1]=phase;
  pose_full_admission_pending_[slot]=false;
 }
 void synchronize_actor_animation_admission(unsigned slot){
  const auto state=current_action_state(slot),phase=projectile_owner_phase(slot);
  const bool layered=elapsed[slot]>=0&&uses_layered_walk_shot(slot);
  const bool state_changed=pose_bound_state_[slot][1]!=state;
  const bool changed=state_changed||pose_bound_phase_[slot][1]!=phase;
  if(changed||pose_full_admission_pending_[slot]){
   // 4211f0 keeps lower walking motion, including its counter. A stopped
   // shot returning to10 performs the additional full421080 reset instead.
   const bool upper_only=(layered&&(state_changed||pose_full_admission_pending_[slot]))||
    (state==10&&pose_layered_before_[slot]&&!walk_shot_[slot].stopped);
   bind_actor_animation_state(slot,state,phase,upper_only);
  }
  if(layered){const unsigned lower=walk_shot_[slot].stopped?0u:10u;
   if(!pose_layered_before_[slot])pose_lower_walk_state_[slot]=pose_bound_state_[slot][0];
   if(pose_lower_walk_state_[slot]!=lower){animation_services_[slot].bind(0,actor_assets(slot).state_frames_.at(lower).at(0).value);pose_bound_state_[slot][0]=lower;pose_bound_phase_[slot][0]=0;pose_lower_walk_state_[slot]=lower;}
  }
  pose_layered_before_[slot]=layered;
 }
 unsigned actor_secondary_animation_frame(unsigned slot)const{
  if(legacy_client_actors_)return std::uint32_t(legacy_client_actors_->at(slot).frame[1]);
  if(enable_native_death&&death_state[slot]&&uses_recovered_actor(slot))return native_melee_second_tick[slot];
  if(special_entry[slot].state)return special_entry[slot].secondary_frame;
  if(enable_native_shooting&&owns_native_shooting(slot,current_action_state(slot)))return native_melee_second_tick[slot];
  if(enable_native_full_charge&&owns_native_full_charge(slot,current_action_state(slot)))return native_melee_second_tick[slot];
  if(enable_native_special_strike&&owns_native_special_strike(slot,current_action_state(slot)))return native_melee_second_tick[slot];
  if(uses_recovered_actor(slot)&&dash_native_body_state(current_action_state(slot)))return native_melee_second_tick[slot];
  if(uses_recovered_actor(slot)&&air_state[slot]>=40&&air_state[slot]<=44)return native_melee_second_tick[slot];
  if(action_binding(slot).character==14&&action_binding(slot).weapon==0&&elapsed[slot]>=0&&(attack_state[slot]==350||attack_state[slot]==360))return native_melee_second_tick[slot];
  if(elapsed[slot]>=0&&uses_layered_walk_shot(slot))return walk_shot_[slot].lower_tick;
  if(current_action_state(slot)==0||current_action_state(slot)==10)return locomotion_second_tick[slot];
  if(remaining_melee_control_visited[slot]||guard_native_visited[slot]||ground_melee_control_visited[slot]||
     dash_melee_control_visited[slot]||air_melee_control_visited[slot]||directional_melee_control_visited[slot]||followup_control_visited[slot])return native_melee_second_tick[slot];
  if(ground_hit_state[slot]||recovery_state[slot]||reaction_active_[slot]||air_state[slot]==103||air_state[slot]==203)return common_hit_second_tick_[slot];
  if(uses_rena(slot)&&elapsed[slot]>=0&&(rena_full_charge_actor_state(action_binding(slot).weapon,attack_state[slot])||
     rena_mobile_shooting_state(action_binding(slot).weapon,attack_state[slot])))return rena_full_charge[slot].second_frame;
  // Older owners still expose one clock only. Preserve their current timing;
  // independent AE08 parity for these owners remains a separately tracked gap.
  return projectile_owner_animation_frame(slot);
 }
 void advance_actor_animation_service(unsigned slot){
  synchronize_actor_animation_admission(slot);
  animation_services_[slot].step(damage_signed(projectile_owner_animation_frame(slot)),damage_signed(actor_secondary_animation_frame(slot)));
  snapshot_actor_texture_remaps(slot);
 }
 void refresh_actor_pose_cache(BattleWorld& world){
  // 6358c0: all movement, then actor420880 in slot order, then separation.
  // Binding and track setters never resample bones at the input/shot point.
  for(unsigned i=0;i<4;++i){const auto& data=actor_assets(i);
   //420b30 composes root first: mode1 compensates the PRIOR victim head.
   cached_world_[i]=compute_world_pose(world,i);
   // D3DX updates only outputs named by active tracks. Keep every other
   // local matrix, including prior extra transforms, as64e580/64e360 do.
   update_prepared_actor_controller_pose(cached_poses_[i],animation_services_[i],data.prepared_pose,data.animation_last_keys_,data.ticks_per_second_,native_extra68[i],pose_scratch_[i]);
   combine_actor_world_hierarchy(cached_poses_[i],cached_world_[i],cached_world_bones_[i]);
   cached_world_ready_[i]=true;++pose_generation[i];
   if(world.actors[i].motion.blocked){const auto attachment=held_attachment(world,i);world.actors[i].position={attachment[12],attachment[13],attachment[14]};}
  }
 }
 unsigned projectile_owner_signal(unsigned slot)const{return projectile_owner_signal_.at(slot);}
 void notify_roster_shot_projectile_signal(unsigned slot,unsigned value){
  if(action_binding(slot).character==5&&action_binding(slot).weapon==2)
   projectile_owner_signal_[slot]=value;
  if(action_binding(slot).character==5&&action_binding(slot).weapon==0){
   projectile_owner_signal_[slot]=value;
   if(value==3&&(attack_state[slot]==450||attack_state[slot]==460)&&
      attack_phase[slot]==1&&elapsed[slot]>=0)roster_charge_trigger_[slot]=1;
  }
  if(value>=1&&value<=3&&action_binding(slot).character==5&&
     action_binding(slot).weapon==2&&(attack_state[slot]==400||attack_state[slot]==402)&&elapsed[slot]>=0)
   roster_shot_trigger_[slot]=value;
 }
 void notify_roster_shot_projectile_finished(unsigned slot,unsigned registration){
  if(action_binding(slot).character==5&&action_binding(slot).weapon==0&&registration==10&&
     (attack_state[slot]==450||attack_state[slot]==460)&&attack_phase[slot]==1&&elapsed[slot]>=0)
   roster_charge_trigger_[slot]=1;
 }
 const BattleActorAssets& actor_assets(unsigned slot)const{return *assets_.at(slot);}
 std::array<int,2> selected_held_weapon_models(unsigned slot)const{
  //434a70 owns these slots;421080/contact state changes do not reselect them.
  if(uses_recovered_actor(slot)&&actor_assets(slot).weapon_item)return weapon_visual_controllers.at(slot).selected;
  const auto& binding=action_binding(slot);const auto state=current_action_state(slot);
  if(uses_rena(slot)&&state==rena_held_model_state.at(slot))return rena_held_models.at(slot);
  if(roster_held_models_initialized.at(slot)&&(binding.character>=3||
     (enable_native_shooting&&owns_native_shooting(slot,state))||
     (enable_native_full_charge&&owns_native_full_charge(slot,state))||
     (enable_native_special_strike&&owns_native_special_strike(slot,state))))return roster_held_models.at(slot);
  return held_weapon_models(binding.character,binding.weapon,state,attack_phase.at(slot),
   unsigned(elapsed.at(slot)),special_gauges.at(slot).active1&&special_gauges.at(slot).ready1!=0);
 }
 void prepare_roster_weapon_visuals(const BattleWorld& world,unsigned slot){
  const auto& binding=action_binding(slot);
  const auto& actor=world.actors.at(slot);const auto& data=actor_assets(slot);
  RosterWeaponTrailInput input;input.state=int(current_action_state(slot));
  input.phase=int(projectile_owner_phase(slot));input.frame=int(projectile_owner_animation_frame(slot));
  input.blocked=stop_ticks[slot]!=0;input.grounded=actor.grounded!=0;input.vertical=actor.motion.velocity[1];
  input.rank=int(field_contact_rank.at(slot));input.scratch_ec=roster_weapon_visual_ec.at(slot);input.melee_held=melee_held_.at(slot)!=0;
  input.contact_bits=contact_ledger.at(slot).combined();input.gravity=ground_shot_.at(slot).gravity;
  const auto& target=world.actors.at(actor.relationships.target).position;
  input.target_horizontal_squared=float(battle_target_distance_squared(actor.position,target)); // native42d980, DWORD weapon-trail input store
  input.known_fields=TrailEC|TrailDistanceSquared|TrailContactBits|TrailGravity;
  if(roster_followup_control_state(binding.character,binding.weapon,unsigned(input.state)))input.scratch_ec=keiichi_motion_.at(slot).contact_seen;
  if(input.state==300||input.state==310||input.state==311||input.state==320||input.state==330||input.state==331){
   const auto scratch=native_melee_scratch(slot);input.scratch_e8=scratch.e8;input.scratch_ec=scratch.ec;
   input.scratch_f0=scratch.f0;input.scratch_f4=scratch.f4;input.scratch_f8=scratch.f8;
   input.known_fields|=scratch.known&(TrailE8|TrailEC|TrailF0|TrailF4|TrailF8);
  }
  if(binding.character==2&&input.state==370){input.scratch_f8=int(special_strike.at(slot).held);input.known_fields|=TrailF8;}
  // All F0 visual guards read it only inside their phase1 exit. At other
  // phases its value cannot affect a command. Preserve unknownness inphase1.
  if(input.phase!=1)input.known_fields|=TrailF0;
  if(binding.character==13&&binding.weapon==2&&(input.state==350||input.state==360)&&
     !(input.phase==3&&input.frame==33))input.known_fields|=TrailF8;
  // Keep native model requests in the stream for flag/history ordering.
  // The validated individual0..2 body still owns the public selected getter.
  input.individual_model_body_owned=false;
  const auto& special=special_gauges.at(slot);input.active0=special.active0;input.active1=special.active1;input.active2=special.active2;
  const auto phases=data.state_animations_.find(unsigned(input.state));
  input.body_is_current_DAT=phases!=data.state_animations_.end()&&input.phase>=0&&input.frame>=0&&unsigned(input.phase)<phases->second.size()&&
   unsigned(input.frame)<data.animation_durations_.at(phases->second[unsigned(input.phase)]);
  if(input.body_is_current_DAT)input.complete=unsigned(input.phase)+1==phases->second.size()&&
   unsigned(input.frame)+1>=data.animation_durations_.at(phases->second[unsigned(input.phase)]);
  // Natsumi's six charge states share actual actor scratch words. Other
  // native writers are conservatively invalidated until their body is ported.
  if(binding.character==15&&binding.weapon==0){
   auto& scratch=roster_native_scratch.at(slot);
   if(!input.blocked&&input.body_is_current_DAT&&!input.complete){
    switch(input.state){
     case 351:case 370:scratch.known&=~16u;break;
     case 350:case 360:case 400:case 401:
     case 402:case 404:case 405:case 406:case 407:case 408:scratch.known&=~4u;break;
    }
   }
   input.scratch_f0=scratch.f0;input.scratch_f4=scratch.f4;input.scratch_f8=scratch.f8;
   input.known_fields|=scratch.known&(TrailF0|TrailF4|TrailF8);
  }
  if(binding.character==14&&binding.weapon==1){
   auto& scratch=roster_native_scratch.at(slot);
   if(!input.blocked&&input.body_is_current_DAT&&!input.complete){
    switch(input.state){
     case 336:case 350:case 351:case 360:case 361:
     case 400:case 402:case 404:case 405:case 406:case 407:case 408:
     case 410:case 411:case 412:case 450:case 451:case 460:scratch.known&=~4u;break;
    }
   }
   if(input.state==302){
    input.scratch_f0=scratch.f0;input.known_fields|=scratch.known&TrailF0;
    if(!input.blocked&&input.grounded&&!input.complete&&input.phase==0&&input.frame==0){input.scratch_f0=1;input.known_fields|=TrailF0;}
   }
  }
  weapon_visual_inputs[slot]=input;
  const auto effects=roster_weapon_trail_melee_policy(binding.character,binding.weapon,input);
  weapon_visual_commands[slot]=effects;
  if(!effects.count)return;
  auto& controller=weapon_visual_controllers[slot];
  apply_roster_weapon_trails(controller,effects,[&](int model){
   return data.weapon_item&&unsigned(model)<data.weapon_item->attachments.size()&&!data.weapon_item->attachments[unsigned(model)].model.empty();
  },[](int,int){});
  roster_held_models[slot]=controller.selected;
  roster_held_models_initialized[slot]=true;
 }
 // Original435000/435220/435450: admit ammo at each ordered request, then
 // resolve the real DAT socket/hand before movement and clock advance.
 bool append_actor_projectile_request(BattleWorld& world,unsigned slot,GroundShotEffects shot,
  std::array<float,3> position,float heading,float offset,std::optional<ActorSkeleton>& muzzle,
  std::optional<int> selected_model=std::nullopt,float model_pitch=0,float model_pivot=0){
  const auto& data=actor_assets(slot);const auto& actor=world.actors.at(slot);
  const auto& bullet=data.weapon_item->bullets.at(shot.bullet_slot);
  if(bullet.magazine_index>=0&&!consume_battle_round(magazines[slot].at(unsigned(bullet.magazine_index))))return false;
  if(shot.origin==GroundShotOrigin::ActorSide){
   const float side=actor.heading+90;
   position={actor.position[0]-legacy_trig(side,false)*50,
    actor.position[1]+shot.origin_height,actor.position[2]-legacy_trig(side,true)*50};
  }else if(shot.origin!=GroundShotOrigin::World){
   const ActorSkeleton* muzzle_pose;
   if(uses_recovered_actor(slot))muzzle_pose=&cached_poses_[slot];else {if(!muzzle)muzzle.emplace(render_pose(slot));muzzle_pose=&*muzzle;}
   const bool attachment=shot.origin==GroundShotOrigin::AttachmentZero;
   const auto bone=muzzle_pose->find(attachment?(shot.attachment_slot==1?"Bip01_Prop2":"Bip01_Prop1"):
     shot.origin==GroundShotOrigin::LeftHand?"Bip01_L_Hand":"Bip01_R_Hand");
   if(!bone)throw std::runtime_error("Missing actor projectile muzzle bone");
   std::array<std::int32_t,3> point{};
   //434a70 selects the current model's socket offset. A hidden model(-1)
   // makes435000 transform the bone origin rather than model0's offset.
   if(attachment){
    const int index=selected_model?*selected_model:shot.attachment_model<0?int(shot.attachment_slot):shot.attachment_model;
    if(index>=0){const auto& a=data.weapon_item->attachments.at(unsigned(index));if(!a.model.empty())point=a.socket_offset;}
   }
   const auto transform=actor_bone_world(world,slot,bone);
   const auto p=transform_actor_point(point,transform);position={p[0],p[1],p[2]};heading=actor.heading+offset+shot.yaw;
  }
  shot_requests.push_back({slot,shot,position,heading,actor.relationships.target});++shots_spawn_requested[slot];return true;
 }
 void advance_native_guard_body(BattleWorld& world,const net::InputChannel::Frame& inputs,unsigned i){
  auto& actor=world.actors.at(i);const auto& data=actor_assets(i);
  const auto& phases=data.guard_data_.at(guard_state[i]);const auto& phase=phases.at(guard_phase[i]);
  GuardNativeInput in;in.state=guard_state[i];in.phase=guard_phase[i];in.frame=guard_tick[i];
  in.grounded=actor.grounded;in.jump=(inputs[i].buttons&6)!=0;in.melee=(inputs[i].buttons&5)!=0;
  in.contact=contact_ledger[i].combined();in.complete=in.phase+1==phases.size()&&in.frame+1>=data.animation_durations_.at(phase.value);
  GuardNativeMotion motion;static_cast<RosterFollowupControlMotion&>(motion)=native_followup_motion(world,i);
  motion.gauge=gauge[i];motion.invincible=stagger[i].invincible;auto scratch=native_melee_scratch(i);
  const auto next=advance_guard_native_control(scratch,motion,in);guard_native_effects[i]=next;guard_native_motion[i]=motion;guard_native_visited[i]=true;
  store_native_melee_scratch(i,scratch);gauge[i]=motion.gauge;stagger[i].invincible=motion.invincible;
  actor.motion.speed=motion.speed;actor.motion.angles[1]=motion.movement;actor.motion.velocity[1]=motion.vertical;
  ground_shot_[i].gravity=air_melee_[i].gravity=motion.gravity;walk_motion_[i].step=motion.turn;
  std::memcpy(&actor.relationships.heading_offset_bits,&motion.offset,4);
  for(unsigned n=0;n<next.count;++n){const auto& event=next.events[n];switch(event.kind){
   case GuardNativeKind::Query:break;
   case GuardNativeKind::Clear:contact_ledger[i].clear_flags();break;
   case GuardNativeKind::Sound:queue_sound({i,unsigned(event.value),actor.position});break;
   case GuardNativeKind::Voice:queue_voice({i,unsigned(event.value),unsigned(event.argument),-1,-1,0x4223d0,0});break;
   case GuardNativeKind::Particle:queue_effect({i,unsigned(event.value),{actor.position[0],actor.position[1]+100.f,actor.position[2]},actor.heading+motion.offset});break;
   case GuardNativeKind::State:
    reset_native_state_metadata(i);guard_state[i]=0;guard_flags[i]=0;guard_phase[i]=guard_tick[i]=0;
    elapsed[i]=-1;geometry[i]={};walking[i]=false;walk_tick[i]=0;air_state[i]=0;air_transition_[i]=false;
    if(event.value==43||event.value==103){air_state[i]=unsigned(event.value);air_phase[i]=air_tick[i]=0;}
    else if(event.value>=390)guard_state[i]=unsigned(event.value);
    bind_actor_animation_state(i,unsigned(event.value));
    break;
   case GuardNativeKind::Phase:guard_phase[i]=unsigned(event.value);guard_tick[i]=native_melee_second_tick[i]=0;bind_actor_animation_state(i,guard_state[i],guard_phase[i]);break;
  }}
  // Only the original common break tail advances AE04/AE08. A State/Phase
  // return keeps the admitted frame0 and skips Satoko1's field tail as well.
  if(!next.clock)attack_return_[i]=true;
  else {
   ++guard_tick[i];++native_melee_second_tick[i];
   if(guard_tick[i]>data.animation_durations_.at(phase.value)&&in.phase+1<phases.size()&&!data.animation_settings_.at(phase.value).hold_phase){
    ++guard_phase[i];guard_tick[i]=native_melee_second_tick[i]=0;
    bind_actor_animation_state(i,guard_state[i],guard_phase[i]);
   }
  }
  if(guard_state[i]){ActorFrameCursor cursor;guard_flags[i]=cursor.advance(data.guard_data_.at(guard_state[i]).at(guard_phase[i]),guard_tick[i]).flags28;}
 }
 RemainingMeleeNativeMotion native_remaining_melee_motion(const BattleWorld& world,unsigned slot)const{
  RemainingMeleeNativeMotion result;static_cast<DashMeleeNativeMotion&>(result)=native_dash_melee_motion(world,slot);
  result.yaw=native_extra_yaw.at(slot);result.orientation34=native_orientation34.at(slot);
  result.gauge=damage_signed(gauge.at(slot));result.rank=damage_signed(field_contact_rank.at(slot));
  result.rank_timer=damage_signed(field_contact_rank_timer.at(slot));result.mine_clock=damage_signed(satoko_mine_clock.at(slot));
  result.invincible=damage_signed(stagger.at(slot).invincible);return result;
 }
 void store_native_remaining_melee_motion(BattleWorld& world,unsigned slot,const RemainingMeleeNativeMotion& value){
  // State/Phase requests have already been replayed. Preserve writes following
  // admission, including Tomitake's24 clocks and Ohishi's falling gravity.
  store_native_air_melee_motion(world,slot,static_cast<const DashMeleeNativeMotion&>(value));
  native_extra_yaw.at(slot)=value.yaw;native_orientation34.at(slot)=value.orientation34;
  gauge.at(slot)=value.gauge;field_contact_rank.at(slot)=unsigned(value.rank);
  field_contact_rank_timer.at(slot)=unsigned(value.rank_timer);satoko_mine_clock.at(slot)=unsigned(value.mine_clock);
  stagger.at(slot).invincible=unsigned(value.invincible);
 }
 void admit_shared_recovery_state(unsigned slot,unsigned state){
  if(state!=124&&state!=128)throw std::invalid_argument("Recovery admission state");
  if(!actor_assets(slot).state_frames_.count(state))throw std::out_of_range("Recovery state absent from DAT");
  set_common_hit_action(slot,state,false);
 }
 void admit_remaining_melee_state(unsigned slot,unsigned state){
  reset_native_state_metadata(slot);geometry.at(slot)={};cursors_.at(slot)={};
  elapsed.at(slot)=-1;walking.at(slot)=false;walk_tick.at(slot)=0;
  air_state.at(slot)=guard_state.at(slot)=recovery_state.at(slot)=ground_hit_state.at(slot)=0;
  air_phase.at(slot)=air_tick.at(slot)=guard_phase.at(slot)=guard_tick.at(slot)=guard_flags.at(slot)=0;
  recovery_phase.at(slot)=recovery_tick.at(slot)=0;air_transition_.at(slot)=false;
  reaction_active_.at(slot)=reaction_pending_.at(slot)=false;
  if(state==0)return;
  if(state==10){walking.at(slot)=true;return;}
  if(state==30||(state>=40&&state<=44)||state==103||state==203){air_state.at(slot)=state;return;}
  if(state>=390&&state<=392){guard_state.at(slot)=state;return;}
  if(state==45){recovery_state.at(slot)=state;return;}
  if(!actor_assets(slot).state_frames_.count(state))throw std::runtime_error("Missing native remaining-melee State DAT");
  attack_state.at(slot)=state;attack_phase.at(slot)=0;elapsed.at(slot)=0;
 }
 void advance_native_special_body(BattleWorld& world,unsigned slot){
  auto& actor=world.actors.at(slot);auto& entry=special_entry.at(slot);
  if(stop_ticks[slot])return; // all46 slot6 prefixes test the full+a0 word.
  const unsigned prior_state=entry.state,prior_phase=entry.phase,prior_frame=entry.frame;
  auto scratch=native_melee_scratch(slot);
  entry.elapsed=unsigned(scratch.e8);entry.recovery=scratch.ec!=0;entry.hold=unsigned(scratch.f8);
  BattleSpecialBodyMotion motion{actor.motion.speed,actor.motion.velocity[1],ground_shot_[slot].gravity,
   actor.motion.angles[1],walk_motion_[slot].step,air_melee_[slot].pitch,native_extra_yaw[slot],native_orientation34[slot],
   native_contact_mode[slot],stagger[slot].down,stagger[slot].down_timer,stagger[slot].invincible,status_aura_models[slot]};
  const auto next=advance_battle_special_body(entry,motion,actor_assets(slot),special_gauges[slot],health[slot],actor.grounded!=0,random_);
  special_body_effects[slot]=next;special_entry_effects[slot]=next.entry;special_body_visited[slot]=true;
  //4212f0 sees the incremented old-phase primary before421100 resets it.
  if(next.tail)cursors_[slot].advance(actor_assets(slot).state_frames_.at(prior_state).at(prior_phase),damage_signed(prior_frame+1u));
  for(const auto& event:next.events)switch(event.kind){
   case SpecialBodyEventKind::Particle:queue_effect({slot,unsigned(event.value),actor.position,actor.heading});break;
   case SpecialBodyEventKind::Sound:queue_sound({slot,unsigned(event.value),actor.position});break;
   case SpecialBodyEventKind::Voice:queue_voice({slot,unsigned(event.value),unsigned(event.argument),event.choice,-1,event.choice<0?0x422240u:0x422300u,0});break;
   case SpecialBodyEventKind::ClearContacts:contact_ledger[slot].clear_flags();contacted_[slot]={};break;
   case SpecialBodyEventKind::Capacity:contact_ledger[slot].set_capacity(unsigned(event.value));break;
   case SpecialBodyEventKind::State:admit_remaining_melee_state(slot,unsigned(event.value));bind_actor_animation_state(slot,unsigned(event.value));break;
   case SpecialBodyEventKind::Phase:cursors_[slot]={};bind_actor_animation_state(slot,entry.state,entry.phase);break;
   case SpecialBodyEventKind::Begin:break; // gauges have already consumed the ordered service.
  }
  scratch.e8=damage_signed(entry.elapsed);scratch.f8=damage_signed(entry.hold);scratch.known|=17u;store_native_melee_scratch(slot,scratch);
  actor.motion.speed=motion.speed;actor.motion.velocity[1]=motion.vertical;actor.motion.angles[1]=motion.movement;
  ground_shot_[slot].gravity=air_melee_[slot].gravity=jump_motion_[slot].gravity=motion.gravity;walk_motion_[slot].step=motion.turn;
  air_melee_[slot].pitch=motion.pitch;native_extra_yaw[slot]=motion.yaw;native_orientation34[slot]=motion.orientation;native_contact_mode[slot]=motion.contact_mode;
  stagger[slot].down=motion.down;stagger[slot].down_timer=motion.down_timer;stagger[slot].invincible=motion.invincible;
  status_aura_models[slot]=motion.last_hit_owner;
 }
 void advance_native_locomotion_body(BattleWorld& world,unsigned slot,const net::InputChannel::Frame& inputs){
  const auto& binding=action_binding(slot);auto& actor=world.actors.at(slot);
  const auto state=current_action_state(slot),phase=projectile_owner_phase(slot);
  const auto& data=actor_assets(slot);const auto id=data.state_frames_.at(state).at(phase).value;
  RosterLocomotionNativeInput in{binding.character,binding.weapon,int(state),int(phase),
   damage_signed(projectile_owner_animation_frame(slot)),damage_signed(locomotion_second_tick[slot]),
   actor_input_x(slot,inputs[slot]),actor_input_z(slot,inputs[slot]),actor.grounded,damage_signed(stop_ticks[slot]),
   damage_signed(status[slot].duration[6]),damage_signed(data.animation_durations_.at(id)),data.animation_settings_.at(id).hold_phase!=0};
  const auto& special=special_gauges[slot];in.awakened=special.active0||special.active1||special.active2;
  auto scratch=native_melee_scratch(slot);float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
  RosterLocomotionNativeMotion motion{actor.motion.speed,actor.motion.velocity[1],ground_shot_[slot].gravity,
   actor.motion.angles[1],offset,walk_motion_[slot].step,damage_signed(gauge[slot]),scratch.e8};
  const auto next=advance_roster_locomotion_native(motion,in);
  locomotion_native_input[slot]=in;locomotion_native_motion[slot]=motion;
  locomotion_native_effects[slot]=next;locomotion_native_visited[slot]=true;
  if(!next.tail)attack_return_[slot]=true; //+a0 or State return skips Satoko's tail too.
  actor.motion.speed=motion.speed;actor.motion.velocity[1]=motion.vertical;actor.motion.angles[1]=motion.movement;
  ground_shot_[slot].gravity=air_melee_[slot].gravity=motion.gravity;gauge[slot]=motion.gauge;
  std::memcpy(&actor.relationships.heading_offset_bits,&motion.offset,4);
  scratch.e8=motion.direction;scratch.known|=1u;store_native_melee_scratch(slot,scratch);
  walk_motion_[slot]={motion.direction,motion.turn};
  if(next.next_state>=0){admit_remaining_melee_state(slot,unsigned(next.next_state));bind_actor_animation_state(slot,unsigned(next.next_state));}
  else {
   if(walking[slot])walk_tick[slot]=unsigned(next.frame);else idle_tick[slot]=unsigned(next.frame);
   locomotion_second_tick[slot]=unsigned(next.secondary);
  }
 }
 void advance_native_hanyuu_time_stop_body(BattleWorld& world,unsigned slot){
  auto& actor=world.actors.at(slot);auto scratch=native_melee_scratch(slot);const auto& data=actor_assets(slot);
  const auto state=attack_state[slot],phase=attack_phase[slot];const auto& phases=data.state_frames_.at(state);
  const auto id=phases.at(phase).value;const auto duration=data.animation_durations_.at(id);
  HanyuuTimeStopBody body{state,phase,unsigned(elapsed[slot]),native_melee_second_tick[slot],unsigned(scratch.e8),unsigned(scratch.ec),unsigned(scratch.f0),actor.motion.speed,actor.motion.velocity[1],ground_shot_[slot].gravity,actor.motion.angles[1]};
  auto effects=advance_hanyuu_time_stop_body(body,phase+1u>=phases.size()&&damage_signed(body.primary+1u)>=damage_signed(duration),duration,data.animation_settings_.at(id).hold_phase!=0,stop_ticks[slot]);
  hanyuu_time_stop_visited[slot]=true;hanyuu_time_stop_effects[slot]=effects;
  scratch.e8=damage_signed(body.e8);scratch.ec=damage_signed(body.ec);scratch.f0=damage_signed(body.f0);scratch.known|=7u;store_native_melee_scratch(slot,scratch);
  actor.motion.speed=body.speed;actor.motion.velocity[1]=body.vertical;actor.motion.angles[1]=body.movement;
  ground_shot_[slot].gravity=air_melee_[slot].gravity=body.gravity;
  elapsed[slot]=damage_signed(body.primary);native_melee_second_tick[slot]=body.secondary;
  if(effects.tail)cursors_[slot].advance(phases.at(phase),damage_signed(effects.cursor_frame));
  for(const auto& event:effects.events)switch(event.kind){
   case HanyuuTimeStopEventKind::Activate:activate_presentation(slot);break;
   case HanyuuTimeStopEventKind::TrailOff:{auto& controller=weapon_visual_controllers[slot];controller.own=false;for(auto model:controller.selected)if(model>=0&&model<12)controller.model_trail[model]=false;break;}
   case HanyuuTimeStopEventKind::Voice:case HanyuuTimeStopEventKind::AlternateVoice:queue_voice({slot,unsigned(event.value),unsigned(event.argument),-1,-1,event.kind==HanyuuTimeStopEventKind::Voice?0x422240u:0x4223d0u,0});break;
   case HanyuuTimeStopEventKind::Sound:queue_sound({slot,unsigned(event.value),actor.position});break;
   case HanyuuTimeStopEventKind::TimeStop:begin_native_time_stop(slot,unsigned(event.value));break;
   case HanyuuTimeStopEventKind::State:admit_remaining_melee_state(slot,unsigned(event.value));bind_actor_animation_state(slot,unsigned(event.value));break;
   case HanyuuTimeStopEventKind::Phase:attack_phase[slot]=unsigned(event.value);cursors_[slot]={};bind_actor_animation_state(slot,state,attack_phase[slot]);break;
  }
 }
 void advance_native_remaining_melee_body(BattleWorld& world,unsigned slot,const RemainingMeleeNativeInput& input,RemainingMeleeNativeEffects (*control)(RosterNativeScratch&,RemainingMeleeNativeMotion&,const RemainingMeleeNativeInput&)=advance_remaining_melee_native_control){
  auto scratch=native_melee_scratch(slot);auto motion=native_remaining_melee_motion(world,slot);
  const auto next=control(scratch,motion,input);
  remaining_melee_control_input.at(slot)=input;remaining_melee_control_effects.at(slot)=next;
  remaining_melee_control_motion.at(slot)=motion;remaining_melee_control_visited.at(slot)=true;
  auto& actor=world.actors.at(slot);std::optional<ActorSkeleton> muzzle;
  for(unsigned n=0;n<next.count;++n){const auto& event=next.events[n];const auto& arg=event.args;switch(event.kind){
   case 'A':activate_presentation(slot);break;
   case 'S':record_melee_attack(world,slot,unsigned(arg[0]));break;
   case 'J':shots_attempted.at(slot)+=unsigned(arg[0]);record_shooting_attack(world,slot,unsigned(arg[0]));break;
   case 'C':contact_ledger.at(slot).clear_flags();contacted_.at(slot)={};break;
   case 'Q':contact_ledger.at(slot).set_capacity(unsigned(arg[0]));break;
   case 'R':break; // pure service reads the same ordered ledger; C clears its local view too.
   case 'I':{
    const auto& phases=actor_assets(slot).state_frames_.at(unsigned(arg[0]));
    // Preserve the known Akane332/H3 request for the explicit recovery below.
    if(input.character==13&&input.weapon<3&&arg[0]==332&&arg[1]==3&&phases.size()==3)break;
    cursors_[slot].advance(phases.at(unsigned(arg[1])),arg[2]);break;
   } // Original4212f0, in source order.
   case 'E':queue_sound({slot,unsigned(arg[0]),actor.position,native_battle_sound_mode(unsigned(arg[1]))});break;
   case 'V':
    if(event.address==0x422490)queue_voice({slot,unsigned(arg[1]),unsigned(arg[3]),arg[2],-1,event.address,unsigned(arg[4])&255u});
    else queue_voice({slot,unsigned(arg[1]),unsigned(arg[2]),-1,-1,event.address,unsigned(arg[3])&255u});
    break;
   case 'B':queue_effect({slot,unsigned(arg[0]),
    {remaining_real(unsigned(arg[1])),remaining_real(unsigned(arg[2])),remaining_real(unsigned(arg[3]))},remaining_real(unsigned(arg[4])),0});break;
   case 'W':{
    GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=unsigned(arg[0]);shot.origin=GroundShotOrigin::World;shot.pitch=remaining_real(unsigned(arg[5]));
    append_actor_projectile_request(world,slot,shot,
     {remaining_real(unsigned(arg[1])),remaining_real(unsigned(arg[2])),remaining_real(unsigned(arg[3]))},remaining_real(unsigned(arg[4])),motion.offset,muzzle);break;
   }
   case 'N':admit_remaining_melee_state(slot,unsigned(arg[0]));bind_actor_animation_state(slot,unsigned(arg[0]));break;
   case 'H':
    if(guard_state[slot]){guard_phase[slot]=unsigned(arg[0]);guard_tick[slot]=0;}
    else if(air_state[slot]){air_phase[slot]=unsigned(arg[0]);air_tick[slot]=0;}
    else if(recovery_state[slot]){recovery_phase[slot]=unsigned(arg[0]);recovery_tick[slot]=0;}
    else {attack_phase[slot]=unsigned(arg[0]);if(elapsed[slot]>=0)elapsed[slot]=0;}
    native_melee_second_tick[slot]=0;cursors_[slot]={};
    // Retain the original undefined Akane332/H3 request until its explicit
    // safe-state recovery below; never index an absent DAT animation here.
    if(unsigned(arg[0])<actor_assets(slot).state_frames_.at(current_action_state(slot)).size())bind_actor_animation_state(slot,current_action_state(slot),unsigned(arg[0]));
    break;
   // The validated mixed model/trail policy already owns these setters and
   // their history updates. Retain raw order for evidence without replaying twice.
   case 'M':case 'L':case 'U':case 'K':break;
   default:throw std::logic_error("Unknown native remaining-melee service");
  }}
  store_native_melee_scratch(slot,scratch);store_native_remaining_melee_motion(world,slot,motion);
  native_melee_second_tick[slot]=unsigned(next.tick2);
  if(guard_state[slot]){guard_phase[slot]=unsigned(next.phase);guard_tick[slot]=unsigned(next.frame);
   ActorFrameCursor cursor;guard_flags[slot]=cursor.advance(actor_assets(slot).guard_data_.at(guard_state[slot]).at(guard_phase[slot]),guard_tick[slot]).flags28;}
  else if(air_state[slot]){air_phase[slot]=unsigned(next.phase);air_tick[slot]=unsigned(next.frame);}
  else if(recovery_state[slot]){recovery_phase[slot]=unsigned(next.phase);recovery_tick[slot]=unsigned(next.frame);}
  else if(elapsed[slot]>=0){attack_phase[slot]=unsigned(next.phase);elapsed[slot]=next.frame;}
  else if(current_action_state(slot)==0||current_action_state(slot)==10){
   if(walking[slot])walk_tick[slot]=unsigned(next.frame);else idle_tick[slot]=unsigned(next.frame);
   locomotion_phase[slot]=unsigned(next.phase);locomotion_second_tick[slot]=unsigned(next.tick2);
  }
  if(elapsed[slot]>=0){
   const auto& phases=actor_assets(slot).state_frames_.at(attack_state[slot]);
   if(attack_phase[slot]>=phases.size()){
    // Original421100 never checks the logical phase count. Akane's332 body
    // can requestH3 after21 airborne visits, although all three DATs define
    // only0..2; loader41e180 adds no sentinel. Preserve the native request in
    // diagnostics, then use its own Complete->43 exit instead of reading an
    // undefined backing slot. This is an explicit rebuild bug fix, not a clamp
    // or a claim of native behavior for the undefined access.
    if(input.character!=13||input.weapon>=3||attack_state[slot]!=332||attack_phase[slot]!=3||phases.size()!=3)
     throw std::logic_error("Unsupported remaining-melee native Phase outside actual DAT");
    remaining_phase_recovery[slot]={true,332,3,3,43};
    admit_remaining_melee_state(slot,43);
   }
  }
  // Body owns both clocks even when it keeps the same state. A requested new
  // state never runs its body on this visit; Satoko's within-body H fallthrough
  // and its field tail have already run in the generated control tree.
  attack_return_[slot]=true;attack_effects[slot]={};
 }
 void advance_native_jump_body(BattleWorld& world,unsigned slot,const net::InputChannel::Frame& inputs){
  const auto& binding=action_binding(slot);auto& actor=world.actors.at(slot);const auto& data=actor_assets(slot);
  const auto state=current_action_state(slot),phase=projectile_owner_phase(slot);const auto& phases=data.state_frames_.at(state);const auto id=phases.at(phase).value;
  JumpNativeInput in;in.character=binding.character;in.weapon=binding.weapon;in.state=state;in.phase=phase;in.frame=projectile_owner_animation_frame(slot);in.tick2=native_melee_second_tick[slot];
  in.x=actor_input_x(slot,inputs[slot]);in.z=actor_input_z(slot,inputs[slot]);in.jump=jump_held_[slot];in.stop=stop_ticks[slot];in.grounded=actor.grounded!=0;
  in.slow=damage_signed(status[slot].duration[6]);in.origin=actor.position;in.heading=actor.heading;in.duration=damage_signed(data.animation_durations_.at(id));in.hold=data.animation_settings_.at(id).hold_phase;
  in.complete=phase+1u>=phases.size()&&damage_signed(in.frame+1u)>=in.duration;
  for(const auto& p:phases){in.phase_durations.push_back(damage_signed(data.animation_durations_.at(p.value)));in.phase_holds.push_back(data.animation_settings_.at(p.value).hold_phase);}
  const auto& special=special_gauges[slot];in.active0=special.active0;in.active1=special.active1;in.active2=special.active2;in.ready1=special.ready1;
  JumpNativeMotion motion;static_cast<RemainingMeleeNativeMotion&>(motion)=native_remaining_melee_motion(world,slot);
  motion.extra68=native_extra68[slot];motion.last_hit_owner=status_aura_models[slot];motion.field_exit=damage_signed(projectile_owner_field_exit[slot]);
  auto scratch=native_melee_scratch(slot);const auto out=advance_jump_native_control(scratch,motion,in);
  jump_native_inputs[slot]=in;jump_native_motions[slot]=motion;jump_native_effects[slot]=out;jump_native_visited[slot]=true;
  if(out.tail)cursors_[slot].advance(phases.at(unsigned(out.cursor_phase)),out.cursor_frame);
  std::optional<ActorSkeleton> muzzle;
  for(unsigned n=0;n<out.count;++n){const auto& e=out.events[n];const auto& a=e.args;switch(e.kind){
   case 'N':admit_remaining_melee_state(slot,unsigned(a[0]));bind_actor_animation_state(slot,unsigned(a[0]));break;
   case 'H':air_phase[slot]=unsigned(a[0]);air_tick[slot]=native_melee_second_tick[slot]=0;cursors_[slot]={};bind_actor_animation_state(slot,current_action_state(slot),unsigned(a[0]));break;
   case 'J':shots_attempted[slot]+=unsigned(a[0]);record_shooting_attack(world,slot,unsigned(a[0]));break;
   case 'E':queue_sound({slot,unsigned(a[0]),actor.position,native_battle_sound_mode(unsigned(a[1]))});break;
   case 'W':{GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=unsigned(a[0]);shot.origin=GroundShotOrigin::World;shot.pitch=remaining_real(unsigned(a[5]));
    append_actor_projectile_request(world,slot,shot,{remaining_real(unsigned(a[1])),remaining_real(unsigned(a[2])),remaining_real(unsigned(a[3]))},remaining_real(unsigned(a[4])),motion.offset,muzzle);break;}
   case 'M':case 'L':case 'U':case 'K':break; // existing source-backed model/trail policy owns setter history once.
   default:throw std::logic_error("Unknown native jump body service");
  }}
  store_native_melee_scratch(slot,scratch);store_native_remaining_melee_motion(world,slot,motion);
  jump_motion_[slot].gravity=motion.gravity;native_extra68[slot]=motion.extra68;status_aura_models[slot]=motion.last_hit_owner;projectile_owner_field_exit[slot]=unsigned(motion.field_exit);
  if(out.state>=40&&out.state<=44){air_state[slot]=unsigned(out.state);air_phase[slot]=unsigned(out.phase);air_tick[slot]=unsigned(out.frame);}
  native_melee_second_tick[slot]=unsigned(out.tick2);attack_return_[slot]=true;
 }
 void advance_native_dash_body(BattleWorld& world,unsigned slot,const net::InputChannel::Frame& inputs){
  const auto& binding=action_binding(slot);auto& actor=world.actors.at(slot);const auto& data=actor_assets(slot);
  const auto state=current_action_state(slot),phase=projectile_owner_phase(slot);const auto& phases=data.state_frames_.at(state);const auto id=phases.at(phase).value;
  DashNativeInput in;in.character=binding.character;in.weapon=binding.weapon;in.state=state;in.phase=phase;in.frame=projectile_owner_animation_frame(slot);in.tick2=native_melee_second_tick[slot];
  in.x=actor_input_x(slot,inputs[slot]);in.z=actor_input_z(slot,inputs[slot]);in.jump=jump_held_[slot];in.stop=stop_ticks[slot];in.grounded=actor.grounded!=0;in.floor_height=actor.floor_distance;
  in.slow=damage_signed(status[slot].duration[6]);in.origin=actor.position;in.heading=actor.heading;in.duration=damage_signed(data.animation_durations_.at(id));in.hold=data.animation_settings_.at(id).hold_phase;
  in.complete=phase+1u>=phases.size()&&damage_signed(in.frame+1u)>=in.duration;
  for(const auto& p:phases){in.phase_durations.push_back(damage_signed(data.animation_durations_.at(p.value)));in.phase_holds.push_back(data.animation_settings_.at(p.value).hold_phase);}
  const auto& special=special_gauges[slot];in.active0=special.active0;in.active1=special.active1;in.active2=special.active2;in.ready1=special.ready1;
  DashNativeMotion motion;static_cast<RemainingMeleeNativeMotion&>(motion)=native_remaining_melee_motion(world,slot);
  motion.extra68=native_extra68[slot];motion.last_hit_owner=status_aura_models[slot];motion.field_exit=damage_signed(projectile_owner_field_exit[slot]);motion.dash_count=damage_signed(statistics[slot].step_starts);
  auto scratch=native_melee_scratch(slot);const auto out=advance_dash_native_control(scratch,motion,in);
  dash_native_inputs[slot]=in;dash_native_motions[slot]=motion;dash_native_effects[slot]=out;dash_native_visited[slot]=true;
  if(out.tail)cursors_[slot].advance(phases.at(unsigned(out.cursor_phase)),out.cursor_frame);
  std::optional<ActorSkeleton> muzzle;
  for(unsigned n=0;n<out.count;++n){const auto& e=out.events[n];const auto& a=e.args;switch(e.kind){
   case 'N':admit_remaining_melee_state(slot,unsigned(a[0]));bind_actor_animation_state(slot,unsigned(a[0]));break;
   case 'H':if(current_action_state(slot)==30){air_phase[slot]=unsigned(a[0]);air_tick[slot]=0;}else{attack_phase[slot]=unsigned(a[0]);elapsed[slot]=0;}native_melee_second_tick[slot]=0;cursors_[slot]={};bind_actor_animation_state(slot,current_action_state(slot),unsigned(a[0]));break;
   case 'J':shots_attempted[slot]+=unsigned(a[0]);record_shooting_attack(world,slot,unsigned(a[0]));break;
   case 'E':queue_sound({slot,unsigned(a[0]),actor.position,native_battle_sound_mode(unsigned(a[1]))});break;
   case 'W':{GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=unsigned(a[0]);shot.origin=GroundShotOrigin::World;shot.pitch=remaining_real(unsigned(a[5]));
    append_actor_projectile_request(world,slot,shot,{remaining_real(unsigned(a[1])),remaining_real(unsigned(a[2])),remaining_real(unsigned(a[3]))},remaining_real(unsigned(a[4])),motion.offset,muzzle);break;}
   case 'M':case 'L':case 'U':case 'K':break; // prior model/trail policy owns setter history once.
   default:throw std::logic_error("Unknown native dash body service");
  }}
  store_native_melee_scratch(slot,scratch);store_native_remaining_melee_motion(world,slot,motion);
  jump_motion_[slot].gravity=motion.gravity;native_extra68[slot]=motion.extra68;status_aura_models[slot]=motion.last_hit_owner;projectile_owner_field_exit[slot]=unsigned(motion.field_exit);statistics[slot].step_starts=unsigned(motion.dash_count);
  if(out.state==30){air_state[slot]=30;air_phase[slot]=unsigned(out.phase);air_tick[slot]=unsigned(out.frame);}
  else if(dash_native_body_state(unsigned(out.state))){attack_state[slot]=unsigned(out.state);attack_phase[slot]=unsigned(out.phase);elapsed[slot]=out.frame;}
  native_melee_second_tick[slot]=unsigned(out.tick2);attack_return_[slot]=true;attack_effects[slot]={};
 }
#include "shoot_native_world.inc.hpp"
#include "full_charge_native_world.inc.hpp"
#include "slot7_native_world.inc.hpp"
 bool prepare_native_actor_clock(BattleWorld& world,unsigned a){
  if(shared_recovery_visited[a])return false; // new whole bodies already own both clocks and cursor.
  if(shoot_native_visited[a])return elapsed[a]>=0&&!air_state[a];
  if(dash_native_visited[a])return elapsed[a]>=0&&!air_state[a]; // the full dash body already owns both clocks.
  if(jump_native_visited[a])return false; // whole State40..44 body owns both clocks and all returns.
  if(hanyuu_time_stop_visited[a])return elapsed[a]>=0&&prepare_attack_geometry(world,a);
  if(special_body_visited[a])return false; //428510 owns clocks and returns after N0/N43.
  if(locomotion_native_visited[a])return false; //body clock or State return already handled.
  if(remaining_melee_control_visited[a])return elapsed[a]>=0&&!guard_state[a]&&!air_state[a]&&!recovery_state[a];
  if(guard_native_visited[a])return false; // guard body already owns its clock/return.
  const auto& data=actor_assets(a);const bool skip_attack_clock=attack_return_[a];
  if(stop_ticks[a]||special_entry[a].state||death_state[a]||ground_hit_state[a]||guard_state[a]||recovery_state[a]||reaction_active_[a]||(skip_attack_clock&&elapsed[a]<0))return false;
  // The whole full-charge body already owns support gates and both clocks.
  // Generic grounded cancellation must not override its airborne continuation.
  if(full_charge_native_visited[a]||special_strike_native_visited[a])return elapsed[a]>=0;
  // These counter actions advance their own clock in the handler above.
  if(uses_mion_counter(a)&&(attack_state[a]==370||attack_state[a]==371))return false;
  // Rena's recovered shooting bodies own both counters and their early
  // return/rewind order. The shared clock must not advance them again.
  if(uses_rena(a)&&elapsed[a]>=0&&(rena_full_charge_actor_state(action_binding(a).weapon,attack_state[a])||
    rena_mobile_shooting_state(action_binding(a).weapon,attack_state[a])))return true;
   if(air_transition_[a]){air_transition_[a]=false;return false;}
   if(air_state[a]==30||(air_state[a]>=40&&air_state[a]<=42)){
    const auto& phases=data.state_animations_.at(air_state[a]);
    const auto duration=data.animation_durations_.at(phases.at(air_phase[a]));
    if(++air_tick[a]>duration&&air_phase[a]+1<phases.size()&&!data.animation_settings_.at(phases[air_phase[a]]).hold_phase){++air_phase[a];air_tick[a]=0;}
    return false;
   }
   if(air_state[a]==103||air_state[a]==203)return false; //428510 already owns this clock.
   if(air_state[a]){
    if(air_state[a]==43){
     if(world.actors[a].grounded&&world.actors[a].motion.velocity[1]<0){air_state[a]=44;air_phase[a]=air_tick[a]=0;}
     else ++air_tick[a];
    }else{
     const auto& phases=data.state_animations_.at(44);
     const auto duration=data.animation_durations_.at(phases.at(air_phase[a]));
     if(air_phase[a]+1==phases.size()&&air_tick[a]+1>=duration)air_state[a]=0;
     else if(++air_tick[a]>duration&&air_phase[a]+1<phases.size()&&!data.animation_settings_.at(phases[air_phase[a]]).hold_phase){++air_phase[a];air_tick[a]=0;}
    }
    return false;
   }
   if(elapsed[a]<0){
    // Idle state0 also enters falling state43 when support is lost.
    if(!world.actors[a].grounded&&!reaction_active_[a]){air_state[a]=43;air_phase[a]=air_tick[a]=0;}
    return false;
   }
   // state300's grounded gate precedes all attack work (438310).
   const bool directional_airborne=directional_melee_control_visited[a]||(action_binding(a).policy==BattleActionPolicy::data_driven_preview&&
    roster_directional_airborne_allowed(action_binding(a).character,attack_state[a],
     int(attack_phase[a]),elapsed[a]));
   // The native body already applies its phase-specific support gate before
   // movement. Preserve that decision through the shared clock/contact tail.
   const bool dash_melee_airborne=dash_melee_control_visited[a]||(action_binding(a).policy==BattleActionPolicy::data_driven_preview&&
    roster_ground_dash_melee_airborne_allowed(action_binding(a).character,attack_state[a],
     int(attack_phase[a]),elapsed[a]+1));
   const bool landing_combo_handler=uses_recovered_actor(a)&&
    (attack_state[a]==340||attack_state[a]==341);
   if(!world.actors[a].grounded&&!directional_airborne&&!dash_melee_airborne&&!landing_combo_handler&&!(uses_mion_counter(a)&&mion_mobile_melee_state(attack_state[a]))&&!(attack_state[a]>=350&&attack_state[a]<=362&&action_binding(a).policy==BattleActionPolicy::data_driven_preview)&&!roster_throw_followup_state(action_binding(a).character,action_binding(a).weapon,attack_state[a])&&attack_state[a]!=320&&attack_state[a]!=329&&attack_state[a]!=332&&attack_state[a]!=333&&attack_state[a]!=334&&attack_state[a]!=336&&attack_state[a]!=339&&attack_state[a]!=360&&attack_state[a]!=370&&attack_state[a]!=371&&attack_state[a]!=402&&attack_state[a]!=403&&attack_state[a]!=408&&attack_state[a]!=409&&attack_state[a]!=422&&attack_state[a]!=423&&attack_state[a]!=460&&!(roster_secondary_charge_state(action_binding(a).character,action_binding(a).weapon,attack_state[a])&&attack_state[a]>=460)&&attack_state[a]!=469){elapsed[a]=-1;air_state[a]=43;air_phase[a]=air_tick[a]=0;geometry[a]={};return false;}
   if(!skip_attack_clock){
    if(uses_layered_walk_shot(a))++walk_shot_[a].lower_tick;
    const auto id=attack_phases(a).at(attack_phase[a]).value;
    ++elapsed[a];
    // Shared301/302 bodies also reach the original slot6 tail: AE08 advances
    // beside AE04 before4212f0 and pose/contact evaluation.
    if(ground_melee_control_visited[a]||dash_melee_control_visited[a]||air_melee_control_visited[a]||directional_melee_control_visited[a]||followup_control_visited[a])++native_melee_second_tick[a];
    // Native shared body tails advance4212f0 after both clocks, before the
    // phase check and420880 geometry. Contacts must not select this row late.
    cursors_[a].advance(attack_phases(a).at(attack_phase[a]),elapsed[a]);
    if(attack_phase[a]+1<attack_phases(a).size()&&unsigned(elapsed[a])>data.animation_durations_.at(id)&&!data.animation_settings_.at(id).hold_phase){++attack_phase[a];elapsed[a]=0;native_melee_second_tick[a]=0;cursors_[a]={};}
   }
  return true;
 }

 const ActorSkin& actor_skin(unsigned slot)const{return actor_assets(slot).skin;}
 unsigned reaction_animation_state(unsigned slot,unsigned state)const{
  const auto& data=actor_assets(slot);
  if(data.state_animations_.count(state))return state;
  // The original DAT only supplies character 3's bespoke 186/135 poses.
  // Keep the linked action state and use each other fighter's generic held
  // and launched poses until their exact victim path is recovered.
  if(state==186)return 187;
  if(state==135)return 115;
  throw std::runtime_error("Missing reaction animation");
 }
 const std::vector<ActorPhaseData>& attack_phases(unsigned slot)const{return actor_assets(slot).state_frames_.at(attack_state.at(slot));}
 const ActorFrameData& actor_frame(unsigned slot)const{
  //Slot7 and common flag queries read actor+10; clock-only reselection loses that pointer.
  if(uses_recovered_actor(slot))return live_body_contact_frame(slot);
  unsigned state=0,phase=0,tick=0;
  if(death_state.at(slot)){state=death_state[slot];phase=death_phase[slot];tick=death_tick[slot];}
  else if(special_entry.at(slot).state){state=special_entry[slot].state;phase=special_entry[slot].phase;tick=special_entry[slot].frame;}
  else if(ground_hit_state.at(slot)){state=ground_hit_state[slot];phase=ground_hit_phase[slot];tick=ground_hit_tick[slot];}
  else if(guard_state.at(slot)){state=guard_state[slot];phase=guard_phase[slot];tick=guard_tick[slot];}
  else if(air_state.at(slot)){state=air_state[slot];phase=air_phase[slot];tick=air_tick[slot];}
  else if(recovery_state.at(slot)){state=recovery_state[slot];phase=recovery_phase[slot];tick=recovery_tick[slot];}
  else if(reaction_active_.at(slot)){state=reaction_animation_state(slot,last_hit[slot].normal.action.state);phase=reaction_phase[slot];tick=reaction_tick[slot];}
  else if(elapsed.at(slot)>=0){state=attack_state[slot];phase=attack_phase[slot];tick=unsigned(elapsed[slot]);}
  else if(walking.at(slot)){state=10;phase=locomotion_phase[slot];tick=walk_tick[slot];}
  else {phase=locomotion_phase[slot];tick=idle_tick[slot];}
  ActorFrameCursor cursor;return cursor.advance(actor_assets(slot).state_frames_.at(state).at(phase),tick);
 }
 ActorSkeleton render_pose(unsigned slot)const{
  if(uses_recovered_actor(slot))return cached_poses_.at(slot);
  return sample_current_pose(slot); // Retained legacy-only fixture constructor.
 }
 const ActorSkeleton& render_pose_view(unsigned slot,std::optional<ActorSkeleton>& fallback)const{
  if(uses_recovered_actor(slot))return cached_poses_.at(slot);
  fallback.emplace(sample_current_pose(slot));return *fallback;
 }
 ActorSkeleton sample_current_pose(unsigned slot)const{
  const auto& data=actor_assets(slot);
  auto pose=data.base_;const XAnimationKeys* animation=nullptr;double time=0;bool layered=false;unsigned animation_id=0;
  if(death_state.at(slot)){
   animation_id=data.state_animations_.at(death_state[slot]).at(death_phase[slot]);animation=&data.animations_.at(animation_id);
   time=actor_animation_key_time(death_tick[slot],data.ticks_per_second_);
  }else if(special_entry.at(slot).state){
   const auto& e=special_entry[slot];animation_id=data.state_animations_.at(e.state).at(e.phase);animation=&data.animations_.at(animation_id);time=actor_animation_key_time(e.frame,data.ticks_per_second_);
  }else if(ground_hit_state.at(slot)){
   animation_id=data.state_animations_.at(ground_hit_state[slot]).at(ground_hit_phase[slot]);animation=&data.animations_.at(animation_id);time=actor_animation_key_time(ground_hit_tick[slot],data.ticks_per_second_);
  }else if(guard_state.at(slot)){
   animation_id=data.guard_data_.at(guard_state[slot]).at(guard_phase[slot]).value;animation=&data.animations_.at(animation_id);time=actor_animation_key_time(guard_tick[slot],data.ticks_per_second_);
  }else if(air_state.at(slot)){
   animation_id=data.state_animations_.at(air_state[slot]).at(air_phase[slot]);animation=&data.animations_.at(animation_id);
   time=actor_animation_key_time(air_tick[slot],data.ticks_per_second_);
  }else if(recovery_state.at(slot)){
   animation_id=data.state_animations_.at(recovery_state[slot]).at(recovery_phase[slot]);animation=&data.animations_.at(animation_id);
   time=actor_animation_key_time(recovery_tick[slot],data.ticks_per_second_);
  }else if(reaction_active_.at(slot)){
   animation_id=data.state_animations_.at(reaction_animation_state(slot,last_hit[slot].normal.action.state)).at(reaction_phase[slot]);animation=&data.animations_.at(animation_id);
   time=actor_animation_key_time(reaction_tick[slot],data.ticks_per_second_);
  }else if(elapsed.at(slot)>=0){animation_id=attack_phases(slot).at(attack_phase[slot]).value;animation=&data.animations_.at(animation_id);time=actor_animation_key_time(elapsed[slot],data.ticks_per_second_);layered=uses_layered_walk_shot(slot);}
  else if(walking.at(slot)){
   animation_id=data.state_animations_.at(10).at(0);animation=&data.animations_.at(animation_id);
   time=actor_animation_key_time(walk_tick[slot],data.ticks_per_second_);
  }
  else if(data.animations_.count(data.idle_animation_)){animation_id=data.idle_animation_;animation=&data.animations_.at(animation_id);}
  // The bundled D3DX X loader creates sets with D3DXPLAY_LOOP (0). Keep
  // sampled poses on their animation-set period while a DAT phase holds.
  // Recovery 124/1 lasts up to 150 movement ticks but its set spans 14 frames.
  if(animation){const auto period=data.animation_last_keys_.at(animation_id);if(period){time=std::fmod(time,double(period));if(time<0)time+=period;}}
  if(layered){
   const auto& shot=walk_shot_[slot];const auto id=data.state_animations_.at(shot.stopped?0:10).at(0);
   double lower_time=actor_animation_key_time(shot.lower_tick,data.ticks_per_second_);const auto period=data.animation_last_keys_.at(id);if(period)lower_time=std::fmod(lower_time,double(period));
   apply_actor_channel_pose(pose,data.animations_.at(id),lower_time,*animation,time);
  }else if(animation)apply_actor_sampled_pose(pose,*animation,time);
  apply_actor_spine_yaw(pose,spine_yaw.at(slot));return pose;
 }
 LegacyMatrix world_pose(const BattleWorld& world,unsigned slot)const{
  if(uses_recovered_actor(slot)&&cached_world_ready_.at(slot))return cached_world_.at(slot);
  return compute_world_pose(world,slot);
 }
 LegacyMatrix actor_bone_world(const BattleWorld& world,unsigned slot,unsigned bone)const{
  if(uses_recovered_actor(slot)&&cached_world_ready_.at(slot))return cached_world_bones_.at(slot).at(bone);
  const auto pose=render_pose(slot);std::vector<LegacyMatrix> combined;
  combine_actor_world_hierarchy(pose,world_pose(world,slot),combined);return combined.at(bone);
 }
 const std::vector<LegacyMatrix>& actor_world_bones_view(const BattleWorld& world,unsigned slot,std::vector<LegacyMatrix>& fallback)const{
  if(uses_recovered_actor(slot)&&cached_world_ready_.at(slot))return cached_world_bones_.at(slot);
  const auto pose=render_pose(slot);combine_actor_world_hierarchy(pose,world_pose(world,slot),fallback);return fallback;
 }
 LegacyMatrix compute_world_pose(const BattleWorld& world,unsigned slot)const{
  if(world.actors.at(slot).motion.blocked){
   const auto attachment=held_attachment(world,slot);
   if(capture_modes.at(target_availability.at(slot).paired_actor)!=1)return attachment;
   std::optional<ActorSkeleton> fallback;const auto& pose=render_pose_view(slot,fallback);const auto head=pose.find("Bip01_Head");
   if(!head)throw std::runtime_error("Missing held actor head");
   const auto& h=pose.bones[head].world;
   const LegacyMatrix translation{1,0,0,0,0,1,0,0,0,0,1,0,-h[12],-h[13],-h[14],1};
   return multiply_matrix_scalar24(translation,attachment);
  }
  const auto& actor=world.actors.at(slot);float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
  //420B30 consumes raw actor+2C/+30/+2D8 for every unattached actor.
  //Native bodies and role2 packets own these fields; action-state gates
  //would discard airborne shooting and other recovered body writes.
  if(legacy_client_actors_||uses_recovered_actor(slot))return actor_world_pose(actor.position,actor.heading,offset,air_melee_[slot].pitch,air_melee_[slot].pivot,native_extra_yaw.at(slot));
  const bool thrown=reaction_active_[slot]&&!recovery_state[slot]&&last_hit[slot].normal.action.state==135&&action_binding(slot).character==3;
  if(thrown)return actor_world_pose(actor.position,actor.heading,offset,throw_victim135_[slot].model_pitch,throw_victim135_[slot].pivot,native_extra_yaw.at(slot));
  const bool natsumi_flight=action_binding(slot).character==15&&action_binding(slot).weapon==0&&
   (attack_state[slot]==460||attack_state[slot]==461||attack_state[slot]==462);
  const bool tilted=elapsed.at(slot)>=0&&(attack_state[slot]==320||attack_state[slot]==332||attack_state[slot]==334||attack_state[slot]==339||natsumi_flight||(enable_native_full_charge&&owns_native_full_charge(slot,current_action_state(slot)))||(enable_native_special_strike&&owns_native_special_strike(slot,current_action_state(slot))))&&!death_state[slot]&&!reaction_active_[slot]&&!air_state[slot]&&!guard_state[slot];
  return actor_world_pose(actor.position,actor.heading,offset,tilted?air_melee_[slot].pitch:0,air_melee_[slot].pivot,native_extra_yaw.at(slot));
 }
 LegacyMatrix held_attachment(const BattleWorld& world,unsigned slot)const{
  const auto owner=target_availability.at(slot).paired_actor;
  if(owner>=4||world.actors.at(owner).motion.blocked)throw std::runtime_error("Invalid held actor owner");
  if(attachment_bones.at(owner).empty())return world_pose(world,owner);
  std::optional<ActorSkeleton> fallback;const auto& pose=render_pose_view(owner,fallback);const auto bone=pose.find(attachment_bones.at(owner));
  if(!bone)throw std::runtime_error("Missing attachment bone");
  return actor_bone_world(world,owner,bone);
 }
 void update_held_positions(BattleWorld& world)const{
  for(unsigned i=0;i<4;++i)if(world.actors[i].motion.blocked){
   const auto matrix=held_attachment(world,i);world.actors[i].position={matrix[12],matrix[13],matrix[14]};
  }
 }
 // Local adapters for character handlers. Call at the original handler point;
 // capture selects+308, while release uses the persistent paired actor.
 template<class Wall> bool capture_actor(BattleWorld& world,unsigned actor,std::int16_t state,std::uint8_t mode,const std::string& bone,Wall& wall){
  return run_throw_operation(world,actor,0,{state,0,0,mode,0,0,0},bone,wall)!=0;
 }
 template<class Wall> void damage_held_actor(BattleWorld& world,unsigned actor,std::int16_t state,std::int16_t damage,std::uint8_t scaling,const std::string& bone,Wall& wall){
  run_throw_operation(world,actor,1,{state,0,damage,scaling,0,0,0},bone,wall);
 }
 template<class Wall> std::uint8_t release_held_actor(BattleWorld& world,unsigned actor,const BattleThrowRelease& input,Wall& wall){
  return run_throw_operation(world,actor,2,input,{},wall);
 }
 std::array<std::array<float,4>,2> body_contact_points(const BattleWorld& world,unsigned slot)const{
  std::optional<ActorSkeleton> fallback;const auto& pose=render_pose_view(slot,fallback);const auto head=pose.find("Bip01_Head"),spine=pose.find("Bip01_Spine");
  if(!head||!spine)throw std::runtime_error("Missing body contact bones");
  return {{transform_actor_point({0,0,0},actor_bone_world(world,slot,head)),
           transform_actor_point({-25,0,0},actor_bone_world(world,slot,spine))}};
 }
 std::array<float,3> target_position(const BattleWorld& world,unsigned slot,int selector)const{
  if(selector!=2&&selector!=3)return world.actors.at(slot).position;
  return select_battle_target_position(world.actors.at(slot).position,body_contact_points(world,slot),selector);
 }
 void configure_respawn(const std::array<std::int32_t,4>& bounds){
  if(bounds[2]<=bounds[0]||bounds[3]<=bounds[1])throw std::invalid_argument("Invalid respawn rectangle");
  respawn_bounds_=bounds;respawn_enabled_=true;
 }
 std::array<BattleVictoryIdentity,2> victory_identities()const{
  if(match.winner<0)throw std::logic_error("Victory identities requested before winner");
  std::array<unsigned,4> characters{},weapons{};
  for(unsigned i=0;i<4;++i){
   // Legacy regression constructor has no roster and historically uses Keiichi0.
   const auto& binding=action_binding(i);characters[i]=binding.policy==BattleActionPolicy::legacy_test?2:binding.character;
   weapons[i]=binding.policy==BattleActionPolicy::legacy_test?0:binding.weapon;
  }
  return battle_victory_team(unsigned(match.winner),characters,weapons);
 }
 template<class Exists,class Read> VictoryLine victory_line(Exists exists,Read read){
  if(match.winner<0)throw std::logic_error("Victory line requested before winner");
  const unsigned team=unsigned(match.winner);
  const auto grade=victory_grade(team_limits_[team],teams_.score[team],teams_.score[1-team],health[team*2],health[team*2+1]);
  const auto identities=victory_identities();
  return select_victory_line(identities[0].script_character,identities[1].script_character,grade,random_,exists,read);
 }
 unsigned team_used(unsigned team)const{return teams_.score.at(team);}
 //634F60 keyboard tail: restore both HP banks and actual team expenditure.
 void restore_keyboard_health(){health.fill(10000);delayed_health.fill(10000);teams_.score.fill(0);}
 void fill_keyboard_special(){
  for(auto& g:special_gauges){if((g.mode&255u)==1)g.charge1=g.limit1;
   else if((g.mode&255u)==2)g.charge2=g.limit0;else g.charge0=g.limit0;}
 }
 const BattleScoreFeedback& score_feedback()const{return host_.score_feedback;}
 const std::array<float,2>& displayed_team_scores()const{return displayed_team_scores_;}
#ifdef DAYBREAK_WORLD_PRESENTATION_PROBE
 friend struct BattleWorldPresentationProbe;
#endif
 unsigned team_limit(unsigned team)const{return team_limits_.at(team);}
 BattleRandom simulation_random_state()const{return random_;}
 std::uint32_t next_battle_random(){return random_.next();}
 unsigned chat_input_suppression_mask=0;
 void set_team_limit(unsigned team,unsigned limit){team_limits_.at(team)=limit;}
 void configure_match_values(const std::array<int,4>& values,bool story=false){
  for(unsigned i=0;i<4;++i){
   // 63691c story retry decrements the red limit by5, down to70. These
   // internal values aren't choices in the local/online20-point menu.
   const bool retry_limit=story&&i==3&&values[i]>=70&&values[i]<=100&&values[i]%5==0;
   if(!retry_limit&&(values[i]<(i<2?50:40)||values[i]>200||values[i]%(i<2?25:20)))throw std::invalid_argument("Invalid match rule percentage");
  }
  match_health_divisor_=values[0];match_charge_scale_=values[1];
  team_limits_={unsigned(values[2]),unsigned(values[3])};
 }
 std::array<BattleAwardStatistics,4> award_records()const{return make_battle_award_records(statistics,team_limits_,teams_.score,match.winner);}
 void finalize_awards(){if(awards.ready)return;if(!match.ready)throw std::logic_error("Awards before result preparation");awards.finalize(award_records(),random_);}
 unsigned displayed_health(unsigned slot)const{return unsigned(std::max(0,std::min(10000,damage_signed(health.at(slot)))));}
 unsigned frozen_mask()const{unsigned mask=0;for(unsigned i=0;i<4;++i)if(stop_ticks[i]||death_state[i]||damage_signed(health[i])<=0)mask|=1u<<i;return mask;}
 const BattleFrameSchedule& frame_schedule()const{return frame_schedule_;}
 unsigned owner_script_mask()const{return frame_schedule_.owner_script_mask(time_stop_ticks);}
 void advance_actor_hit_timers(unsigned i){
  auto& value=stagger.at(i);BattleHitTimers timers{};
  timers.timer828=time_stop_ticks[i];timers.long_stop=long_stop_ticks[i];timers.stop=stop_ticks[i];
  timers.state=current_action_state(i);timers.invincible=value.invincible;timers.count=value.count;
  timers.down=value.down;timers.down_timer=value.down_timer;timers.accum=value.accum;timers.accum_timer=value.timer;
  timers.health=health[i];timers.display_health=delayed_health[i];tick_battle_hit_timers(timers);
  time_stop_ticks[i]=timers.timer828;long_stop_ticks[i]=timers.long_stop;stop_ticks[i]=timers.stop;
  delayed_health[i]=timers.display_health;value.invincible=timers.invincible;value.count=timers.count;
  value.down=timers.down;value.down_timer=timers.down_timer;value.accum=timers.accum;value.timer=timers.accum_timer;
 }
 // Slot6 victim handlers and clocks precede projectile scripts and movement.
 template<class Wall,class Floor> void move(BattleWorld& world,const net::InputChannel::Frame& supplied_inputs,Wall& wall,Floor& floor,unsigned fixture_mask=0){
  move_with_projectile_scripts(world,supplied_inputs,wall,floor,[]{},fixture_mask);
 }
 template<class Wall,class Floor,class Scripts> void move_with_projectile_scripts(BattleWorld& world,const net::InputChannel::Frame& supplied_inputs,Wall& wall,Floor& floor,Scripts scripts,unsigned fixture_mask=0,const BattleCpuFrame* cpu=nullptr,BattleCpuDriver* cpu_driver=nullptr,const std::function<void()>& projectile_motion={},const std::function<void(unsigned)>& owner_projectile_motion={},const std::function<void()>& global_projectile_motion={},const std::array<unsigned,4>* presentation_buttons=nullptr,const std::function<void()>& before_scene={},const std::function<void()>& after_scene={},const std::function<void()>& after_pose_cache={}){
  startup_blocked_this_frame_=startup.warming_up();startup.begin_frame();
  frame_admission_={scene_phase(),last_defeat_attacker};scene_services_prepared_=false;
  for(unsigned i=0;i<4;++i)phase_commands_blocked_[i]=startup.enabled?frame_admission_.blocks_commands(i):startup_blocked_this_frame_;
  frame_schedule_=modern_contacts_?make_battle_frame_schedule(time_stop_ticks):BattleFrameSchedule{};
  fixture_mask|=(~frame_schedule_.actor_mask)&15u;
  if(modern_contacts_&&!cached_world_ready_[0])refresh_actor_pose_cache(world);
  pose_body_admission_replayed_.fill(false);
  slot7_native_visited.fill(false);for(auto& events:slot7_native_events)events.clear();for(auto& recoveries:slot7_dat_recoveries)recoveries.clear();
  shot_requests.clear();effect_requests.clear();sound_requests.clear();voice_requests.clear();shot_callback_visits.clear();ground_shot_effects={};special_activation_events.clear();special_entry_effects={};special_body_effects={};special_body_visited.fill(false);weapon_visual_commands={};followup_control_effects={};followup_control_visited.fill(false);ground_melee_control_effects={};ground_melee_control_visited.fill(false);dash_melee_control_effects={};dash_melee_control_visited.fill(false);air_melee_control_effects={};air_melee_control_visited.fill(false);directional_melee_control_effects={};directional_melee_control_visited.fill(false);
  native_clock_prepared_.fill(false);native_clock_geometry_.fill(false);if(modern_contacts_)attack_return_.fill(false);
  locomotion_native_visited.fill(false);locomotion_native_effects={};
  hanyuu_time_stop_visited.fill(false);hanyuu_time_stop_effects={};
  jump_native_visited.fill(false);jump_native_effects={};
  dash_native_visited.fill(false);dash_native_effects={};
  shoot_native_visited.fill(false);shoot_native_effects={};
  full_charge_native_visited.fill(false);full_charge_native_effects={};
  special_strike_native_visited.fill(false);special_strike_native_effects={};
  throw_victim135_visited.fill(false);throw_victim135_presentation={};
  shared_recovery_visited.fill(false);for(auto& events:shared_recovery_events)events.clear();
  guard_native_effects={};guard_native_visited.fill(false);
  death_native_visited.fill(false);for(auto& events:death_native_events)events.clear();
  remaining_melee_control_effects={};remaining_melee_control_visited.fill(false);remaining_phase_recovery={};
  body_attack_points_ready_=false;
  auto inputs=(startup.enabled||match.winner<0)?supplied_inputs:net::InputChannel::Frame{};
  std::array<std::array<std::array<float,4>,2>,4> status_visual_points{};
  std::array<bool,4> status_visual_points_ready{};
  for(unsigned i=0;i<4;++i){
   status_visual_events[i].clear();
   if(battle_status_reaction(current_action_state(i))||std::any_of(status[i].duration.begin(),status[i].duration.end(),[](unsigned n){return n!=0;})){
    status_visual_points[i]=body_contact_points(world,i);status_visual_points_ready[i]=true;
   }
  }
  std::array<unsigned,4> states_before_admission{};for(unsigned i=0;i<4;++i)states_before_admission[i]=current_action_state(i);
  if(!startup.enabled&&match.winner>=0)cpu=nullptr;
  cpu_acquired_mask_=0;
  if(cpu)for(unsigned i=0;i<4;++i)if(cpu->enabled[i]){inputs[i]=cpu_input_levels(cpu->slots[i]);cpu_acquired_axes_[i]={cpu->slots[i].x,cpu->slots[i].z};cpu_acquired_mask_|=1u<<i;}
  //41efe0 owns a mutable actor controller bank. Physical chords, status and
  // phase clears affect the NEXT poll; device-global ages are not actor ages.
  for(unsigned i=0;i<4;++i){
   const bool cpu_actor=cpu&&cpu->enabled[i];
   const bool chat_suppressed=(chat_input_suppression_mask&(1u<<i))&&!cpu_actor;
   human_input_active_[i]=!cpu_actor&&(human_input_active_[i]||(inputs[i].buttons&battle_physical_tag)||chat_suppressed);
   if(human_input_active_[i]){
    auto& human=human_inputs_[i];human.acquire(inputs[i],status[i].duration[3]!=0);if(chat_suppressed)human.suppress_chat();
    //4246c0 copies all ten words unchanged BEFORE the outer phase gate.
    dash_command_cache_[i]=dash_history_[i].push(human.x(),human.z());
    if(startup.enabled)human.gate(frame_admission_,i);
    inputs[i].buttons=(inputs[i].buttons&~63u)|human.buttons();
    inputs[i].x=std::int16_t((human.x()>0)-(human.x()<0));inputs[i].z=std::int16_t((human.z()>0)-(human.z()<0));
    special_button290[i]=human.held(4);
   }else{
    if(cpu_actor)special_button290[i]=cpu->slots[i].auxiliary[0];
    else{
     human_melee_held_[i]=(inputs[i].buttons&1)?human_melee_held_[i]+1:0;
     human_shoot_held_[i]=(inputs[i].buttons&16)?human_shoot_held_[i]+1:0;
     if(startup.enabled)human_jump_held_[i]=(inputs[i].buttons&2)?human_jump_held_[i]+1:0;
    }
    if(startup.enabled)inputs[i]=frame_admission_.gate(inputs[i],i,cpu_actor);
    if(phase_commands_blocked_[i])special_button290[i]=0;
   }
   prepared_attack_suppression_[i]=status[i].duration[3]!=0||phase_commands_blocked_[i];
   if(prepared_attack_suppression_[i])inputs[i].buttons&=~21u;
   projectile_input_x_[i]=actor_input_x(i,inputs[i]);
  }
  if(startup.enabled&&cpu_driver)cpu_driver->gate_acquired_frame(frame_admission_);
  if(cpu)for(unsigned i=0;i<4;++i)if(cpu->enabled[i]){
   human_inputs_[i].acquire_cpu(cpu->slots[i]);
   if(startup.enabled&&frame_admission_.blocks_commands(i))human_inputs_[i].released.fill(0); //phase gates also clear2bc.
   cpu_acquired_axes_[i]={cpu->slots[i].x,cpu->slots[i].z};projectile_input_x_[i]=actor_input_x(i,inputs[i]);
  }
  has_prepared_attack_suppression_=true;
  //634fb3..6350aa: inspect the acquired/merged actor bank, not raw chords.
  BattlePauseCounters pause_counters{};
  if(offline_pause.enabled)for(unsigned i=0;i<4;++i){
   if(human_input_active_[i])for(unsigned b=0;b<8;++b)pause_counters[i][b]=human_inputs_[i].held(b);
   else if(cpu&&cpu->enabled[i]){
    for(unsigned b=0;b<3;++b)pause_counters[i][b]=std::uint32_t(cpu->slots[i].held[b]);
    pause_counters[i][3]=std::uint32_t(cpu->slots[i].target);
    for(unsigned b=0;b<4;++b)pause_counters[i][4+b]=cpu->slots[i].auxiliary[b];
    if(prepared_attack_suppression_[i])pause_counters[i][1]=pause_counters[i][2]=0;
   }
  }
  advance_battle_offline_pause(offline_pause,!native_host_&&!legacy_client_actors_,scene_phase(),pause_counters);
  if(offline_pause.paused){
   // The scene tick store is after6350aa. Undo only its early modern increment.
   if(startup.enabled)--startup.frame;
   frame_services_prepared_=scene_services_prepared_=false;return;
  }
  // Takano2 slot7 aim belongs after the pause gate and before slot6 hitstop.
  for(unsigned i=0;i<4;++i)if(!enable_native_slot7&&(frame_schedule_.actor_mask&(1u<<i))&&action_binding(i).character==7&&action_binding(i).weapon==2){
   if(!projectile_owner_aim_initialized[i]){initialize_item41_owner_aim(projectile_owner_aim[i],projectile_owner_aim_velocity[i],world.actors[i].position);projectile_owner_aim_initialized[i]=true;}
   advance_item41_owner_aim(projectile_owner_aim[i],projectile_owner_aim_velocity[i],world.actors[i].position);
  }
  auto move_actor=[&](unsigned i){
   if(!modern_contacts_)update_world_motion(world,i,wall,floor);
  };
  auto start_special_chord=[&](unsigned i,unsigned current){
   auto& special=special_gauges[i];
   if(special.accepts_mode0_chord(int(current),melee_held_[i],shoot_held[i])){
    special_entry[i]={world.actors[i].grounded?500u:501u,0,0,0,0,current>=100&&current<=299};
    auto scratch=native_melee_scratch(i);scratch.ec=special_entry[i].recovery?1:0;scratch.known|=2u;store_native_melee_scratch(i,scratch);
    elapsed[i]=-1;geometry[i]={};air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
    reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;return true;
   }
   if(special.accepts_mode1_chord(int(current),melee_held_[i],shoot_held[i])){
    special.begin1();melee_held_[i]=shoot_held[i]=special_button290[i]=20;
    const auto ally=world.actors[i].relationships.allies.at(0);const auto& partner=special_gauges[ally];
    const bool together=partner.active1&&damage_signed(partner.duration1-partner.charge1)<120;
    special_activation_events.push_back({i,7,together?35u:36u});
    queue_voice({i,together?35u:36u,30,-1,-1,0x422240,0});return true;
   }
   return false;
  };
  auto start_air_rejump=[&](unsigned i){
   air_jump_used_[i]=true;air_state[i]=40;air_phase[i]=air_tick[i]=0;elapsed[i]=-1;geometry[i]={};
   jump_motion_[i]={};jump_motion_[i].state=40;jump_motion_[i].gauge=gauge[i];
   jump_motion_[i].button_ticks=jump_held_[i];jump_motion_[i].gravity=0;
   world.actors[i].motion.velocity[1]=0;
   guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
   reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;
  };
  for(const auto& input:inputs)if(!net::valid_input(input))throw std::invalid_argument("Invalid local battle input");
  for(unsigned i=0;i<4;++i){
   const auto* direct=cpu&&cpu->enabled[i]?&cpu->slots[i]:nullptr;
   const bool attack_suppressed=prepared_attack_suppression_[i];
   const unsigned previous=melee_held_[i];const bool held=(inputs[i].buttons&1)!=0;
   const unsigned dash_command=phase_commands_blocked_[i]?0:direct?unsigned(direct->dash):human_input_active_[i]?dash_command_cache_[i]:dash_history_[i].push(inputs[i].x,inputs[i].z);
   dash_command_cache_[i]=dash_command;
   melee_held_[i]=attack_suppressed?0:direct?unsigned(direct->held[1]):human_input_active_[i]?human_inputs_[i].held(1):human_melee_held_[i];const unsigned released=attack_suppressed?0:direct?unsigned(direct->released[1]):human_input_active_[i]?human_inputs_[i].released[1]:held?0:previous;
   melee_released_[i]=released;
   const unsigned prior_jump=jump_held_[i];const bool jump_down=(inputs[i].buttons&2)!=0;
   jump_held_[i]=phase_commands_blocked_[i]?0:direct?unsigned(direct->held[0]):human_input_active_[i]?human_inputs_[i].held(0):startup.enabled?human_jump_held_[i]:jump_down?prior_jump+1:0;const unsigned jump_released=phase_commands_blocked_[i]?0:direct?unsigned(direct->released[0]):human_input_active_[i]?human_inputs_[i].released[0]:jump_down?0:prior_jump;
   if(world.actors[i].grounded)air_jump_used_[i]=false;
   // Defer the second-jump path until slot-7-style dash/shoot/melee admission.
   // The original input handlers choose those attacks first when jump is also
   // newly pressed; a direct jump press has no slot-7 state request.
   const bool pending_air_rejump=use_recovered_melee_timing&&!air_jump_used_[i]&&
      jump_held_[i]==1&&!world.actors[i].grounded&&
      air_state[i]>=41&&air_state[i]<=43&&action_binding(i).policy!=BattleActionPolicy::legacy_test&&
      gauge[i]>0&&!(fixture_mask&(1u<<i))&&!stop_ticks[i]&&!death_state[i]&&!special_entry[i].state&&
      !reaction_active_[i]&&!world.actors[i].motion.blocked;
   const unsigned air_rejump_source=pending_air_rejump?current_action_state(i):0;
   if(use_recovered_melee_timing)jump_motion_[i].button_ticks=jump_held_[i];
   const auto previous_shoot=shoot_held[i];shoot_held[i]=attack_suppressed?0:direct?unsigned(direct->held[2]):human_input_active_[i]?human_inputs_[i].held(2):human_shoot_held_[i];
   shoot_released[i]=attack_suppressed?0:direct?unsigned(direct->released[2]):human_input_active_[i]?human_inputs_[i].released[2]:(inputs[i].buttons&16)?0:previous_shoot;shoot_release_charge[i]=0;
   if(!(frame_schedule_.actor_mask&(1u<<i)))continue; //41efe0 acquisition above still visits all actors.
   if(enable_native_slot7&&uses_recovered_actor(i)&&actor_assets(i).weapon_item){
    if(!(fixture_mask&(1u<<i)))advance_native_slot7_body(world,i,inputs,jump_released,wall);
    continue;
   }
   if(action_binding(i).character==14&&action_binding(i).weapon==0&&time_stop_ticks[i])stagger[i].invincible=3; //5d2e60 slot7 prefix.
   // Every recovered state332 family shares the same early airborne-dash
   // melee gate. Keep this ahead of another state30 admission so an attack
   // edge cannot be swallowed by restarting the dash.
   if(air_state[i]==30&&!world.actors[i].grounded&&!uses_recovered_actor(i)&&action_binding(i).policy!=BattleActionPolicy::legacy_test&&
      battle_dash_family(action_binding(i).character,action_binding(i).weapon)!=BattleDashFamily::unrecovered&&
      (inputs[i].x||inputs[i].z)&&(melee_held_[i]==3||(released>0&&released<3))&&
      !(fixture_mask&(1u<<i))&&!stop_ticks[i]&&!death_state[i]&&!special_entry[i].state&&!world.actors[i].motion.blocked){
    const auto current=current_action_state(i);const auto& priorities=actor_assets(i).state_priorities_;
    const int priority=damage_signed(priorities.at(current)[1]);
    if((actor_frame(i).flags28&0x100)&&priority<=damage_signed(priorities.at(332)[0])){
     attack_state[i]=332;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;native_extra_yaw[i]=0;
     air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
     reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
    }
   }
   // 471210 starts charging before its action gates, including hitstop/death.
   if(uses_recovered_actor(i)&&actor_assets(i).weapon_item&&!(fixture_mask&(1u<<i))){
    if((inputs[i].buttons&16)&&!(action_binding(i).character==14&&action_binding(i).weapon==0&&time_stop_ticks[i]))charge_battle_magazine(magazines[i][1]);
    if(shoot_released[i])shoot_release_charge[i]=magazines[i][1].word28;
    combat_modifiers[i]=keiichi_combat_modifiers(status[i].duration[6],status[i].duration[1],status[i].duration[2],special_gauges[i]);
    for(auto& magazine:magazines[i])magazine.refill_step=special_gauges[i].refill_step(); // Before chord admission, as435560.
    if(special_gauges[i].active2&&gauge[i]<1000)++gauge[i]; //471210/479640/482860, distinct from41f580 tail.
   }
   // State135 is a character-3-specific released-grab action in the DAT.
   // Other victims use the common launched pose and cannot issue a new dash
   // while that reaction is active; there is no state135 priority row.
   if(reaction_active_[i]&&last_hit[i].normal.action.state==135)continue;
   if(action_binding(i).policy!=BattleActionPolicy::legacy_test&&world.actors[i].grounded&&dash_command==2&&!(fixture_mask&(1u<<i))&&!stop_ticks[i]&&!death_state[i]&&!special_entry[i].state&&!world.actors[i].motion.blocked){
    const auto current=current_action_state(i);const auto& priorities=actor_assets(i).state_priorities_;
    const int next=roster_back_dash_admission(action_binding(i).character,action_binding(i).weapon,int(current),gauge[i],actor_frame(i).flags28,damage_signed(priorities.at(current)[1]),contact_ledger[i].combined(),damage_signed(priorities.at(27)[0]));
    if(next>=0){attack_state[i]=unsigned(next);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;}
   }
   // All46 native slot7 airborne dash branches precede guard/shoot/melee.
   if(action_binding(i).policy!=BattleActionPolicy::legacy_test&&(!world.actors[i].grounded||dash_command==1||dash_command==3||dash_command==4)&&!(fixture_mask&(1u<<i))&&!stop_ticks[i]&&!death_state[i]&&!special_entry[i].state&&!world.actors[i].motion.blocked){
    const auto current=current_action_state(i);const auto& priorities=actor_assets(i).state_priorities_;
    if(roster_air_dash_admission(action_binding(i).character,action_binding(i).weapon,int(current),dash_command,gauge[i],actor_frame(i).flags28,damage_signed(priorities.at(current)[1]),contact_ledger[i].combined(),[&](unsigned state){return damage_signed(priorities.at(state)[0]);},!world.actors[i].grounded)){
     if(world.actors[i].grounded){attack_state[i]=dash_command==1?20:dash_command==3?24:23;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;air_state[i]=0;}
     else {air_state[i]=30;air_phase[i]=air_tick[i]=0;elapsed[i]=-1;geometry[i]={};}
     guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
    }
   }
   if(uses_mion_counter(i)){
    combat_modifiers[i]=keiichi_combat_modifiers(status[i].duration[6],status[i].duration[1],status[i].duration[2],special_gauges[i]);
    if(!(fixture_mask&(1u<<i))&&!stop_ticks[i]&&!death_state[i]&&!special_entry[i].state&&!world.actors[i].motion.blocked){
     const auto current=current_action_state(i);const auto& priorities=actor_assets(i).state_priorities_;const auto& g=special_gauges[i];
     const int dash=mion_dash_admission(action_binding(i).weapon,int(current),int(dash_command),world.actors[i].grounded,gauge[i],actor_frame(i).flags28,damage_signed(priorities.at(current)[1]),contact_ledger[i].combined(),[&](int id){return damage_signed(priorities.at(unsigned(id))[0]);});
     if(dash>=0){
      elapsed[i]=-1;geometry[i]={};air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
      reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;
      if(dash!=30){attack_state[i]=unsigned(dash);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;}
      else {air_state[i]=30;air_phase[i]=air_tick[i]=0;}
      continue;
     }
     if(start_special_chord(i,current))continue;
     if(accepts_mion_counter(melee_held_[i],shoot_held[i],g.active0||g.active1||g.active2,world.actors[i].grounded,actor_frame(i).flags28,damage_signed(priorities.at(current)[1]),damage_signed(priorities.at(370)[0]))){
      admit_remaining_melee_state(i,370);bind_actor_animation_state(i,370);mion_counter[i]={};
     }else {
      const unsigned flags=actor_frame(i).flags28;const int priority=damage_signed(priorities.at(current)[1]);
      //45f4d0/467d70/456030: guard precedes the ordinary jump branch.
      const bool guard=battle_ordinary_guard_gate(1,action_binding(i).weapon,(inputs[i].buttons&4)!=0,world.actors[i].grounded,damage_signed(gauge[i]),flags,priority,damage_signed(priorities.at(390)[0]));
      if(battle_empty_shot_event(damage_signed(shoot_released[i]),damage_signed(magazines[i][0].rounds),guard))++statistics[i].empty_shots;
      const bool jump=(jump_held_[i]==3||(jump_released>0&&jump_released<3))&&world.actors[i].grounded&&gauge[i]>0&&(flags&0x100)&&(priority<=damage_signed(priorities.at(40)[0])||priority==49||priority==99);
      if(!guard&&(shoot_release_charge[i]==1||shoot_release_charge[i]==2)){
       const int current_phase=elapsed[i]>=0?int(attack_phase[i]):int(air_phase[i]);
       const auto next=mion_charge_admission(action_binding(i).weapon,int(current),current_phase,world.actors[i].grounded,int(shoot_released[i]),int(shoot_release_charge[i]),damage_signed(magazines[i][1].rounds),priority,[&](int id){return damage_signed(priorities.at(unsigned(id))[0]);});
       if(next.state>=0){
        if(next.full_charge)++statistics[i].full_charge_shots;else ++statistics[i].charge_shots;
        mion_full_charges[i]={};mion_full_charges[i].gravity=(current==41||current==42)?jump_motion_[i].gravity:mion_mobile_melee_state(current)?air_melee_[i].gravity:mion_charge_shooting_state(current)?ground_shot_[i].gravity:(current==400||current==402||current==403)?mion_ground_shots[i].gravity:.5f;attack_state[i]=unsigned(next.state);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;mion_charge_shots[i]={};
        air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
       }
      }
      // Short normal releases: airborne402 or weapon-specific ground routes.
      if(!guard&&!world.actors[i].grounded&&(flags&0x100)&&shoot_released[i]>0&&shoot_released[i]<20&&damage_signed(magazines[i][0].rounds)>(action_binding(i).weapon==1?1:0)&&
         !(shoot_release_charge[i]>0&&magazines[i][1].rounds>0)&&priority<=damage_signed(priorities.at(402)[0])){
       const float gravity=(current==41||current==42)?jump_motion_[i].gravity:mion_mobile_melee_state(current)?air_melee_[i].gravity:(current==400||current==402||current==403)?mion_ground_shots[i].gravity:.5f;
       mion_ground_shots[i]={};mion_ground_shots[i].gravity=gravity;
       attack_state[i]=402;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
       reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
      }
      if(!guard&&world.actors[i].grounded&&(flags&0x100)&&shoot_released[i]>0&&shoot_released[i]<20&&damage_signed(magazines[i][0].rounds)>(action_binding(i).weapon==1?1:0)&&
         !(shoot_release_charge[i]>0&&magazines[i][1].rounds>0)){
       const auto next=mion_ground_shot_admission(action_binding(i).weapon,current,priority,inputs[i].x,inputs[i].z,[&](unsigned state){return damage_signed(priorities.at(state)[0]);});
       if(next.consumed)continue;
       if(next.state>=0){
        float offset;std::memcpy(&offset,&world.actors[i].relationships.heading_offset_bits,4);offset+=next.offset_delta;std::memcpy(&world.actors[i].relationships.heading_offset_bits,&offset,4);
        attack_state[i]=unsigned(next.state);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;mion_ground_shots[i]={};
        air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
       }
      }
      if(!guard){
       const int next=mion_melee_admission(int(current),world.actors[i].grounded,int(melee_held_[i]),int(released),inputs[i].x,inputs[i].z,flags,priority,g.active1,g.ready1!=0,contact_ledger[i].combined(),[&](int id){return damage_signed(priorities.at(unsigned(id))[0]);});
       if(next>=0){
        if(current==41||current==42)air_melee_[i].gravity=jump_motion_[i].gravity;else if(!mion_mobile_melee_state(current))air_melee_[i].gravity=.5f;
        attack_state[i]=unsigned(next);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
        reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
       }
      }
      const bool air_dash=(jump_held_[i]==3||(jump_released>0&&jump_released<3))&&!world.actors[i].grounded&&(inputs[i].x||inputs[i].z)&&gauge[i]>0&&(flags&0x100)&&priority<=damage_signed(priorities.at(30)[0]);
      if(guard||jump||air_dash){
       elapsed[i]=-1;geometry[i]={};air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
       reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;
       if(guard){guard_state[i]=390;guard_phase[i]=guard_tick[i]=0;}
       else {air_state[i]=air_dash?30:40;air_phase[i]=air_tick[i]=0;if(!air_dash)jump_motion_[i].gravity=0;}
      }
     }
    }
    if(pending_air_rejump&&current_action_state(i)==air_rejump_source)start_air_rejump(i);
    continue; // Other shooting and specialized recovery/cancel routes remain partial.
   }
   if(uses_rena(i)){
    if((fixture_mask&(1u<<i))||stop_ticks[i]||death_state[i]||special_entry[i].state||world.actors[i].motion.blocked)continue;
    const auto& priorities=actor_assets(i).state_priorities_;const auto current=current_action_state(i);
    const int dash=rena_dash_admission(action_binding(i).weapon,int(current),dash_command,world.actors[i].grounded,gauge[i],actor_frame(i).flags28,damage_signed(priorities.at(current)[1]),contact_ledger[i].combined(),[&](unsigned state){return damage_signed(priorities.at(state)[0]);});
    if(dash==30){
     air_state[i]=30;air_phase[i]=air_tick[i]=0;elapsed[i]=-1;geometry[i]={};
     guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
    }
    if(dash>=0){
     attack_state[i]=unsigned(dash);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
     air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
    }
   }
   if(action_binding(i).policy==BattleActionPolicy::legacy_test||(fixture_mask&(1u<<i))||stop_ticks[i]||death_state[i]||special_entry[i].state||world.actors[i].motion.blocked)continue;
   const auto& priorities=actor_assets(i).state_priorities_;
   const unsigned current=guard_state[i]?guard_state[i]:air_state[i]?air_state[i]:recovery_state[i]?recovery_state[i]:reaction_active_[i]?last_hit[i].normal.action.state:elapsed[i]<0?(walking[i]?10:0):attack_state[i];
   auto first_priority=[&](unsigned state){const auto found=priorities.find(state);return found==priorities.end()?INT_MIN:damage_signed(found->second[0]);};
   const auto current_priority=priorities.find(current);if(current_priority==priorities.end())continue;
   const unsigned flags=actor_frame(i).flags28;const int priority=damage_signed(current_priority->second[1]);
   // Direction-history commands precede guard, shooting and melee in471210.
   const unsigned dash_state=dash_command==1?20:dash_command==2?27:dash_command==3?24:23;
   // The same direction-specific ground priority gates select30 in the air.
   if(use_recovered_melee_timing&&dash_command&&!world.actors[i].grounded&&gauge[i]>0&&(flags&0x100)&&priority<=first_priority(dash_state)){
    air_state[i]=30;air_phase[i]=air_tick[i]=0;elapsed[i]=-1;geometry[i]={};
    guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   // The earlier roster_back_dash_admission branch owns direction 2 for all
   // fighters. Its original per-weapon cancel mask prevents a nonexistent
   // DAT state 28 from being selected by this shared directional fallback.
   if(use_recovered_melee_timing&&dash_command&&dash_command!=2&&world.actors[i].grounded&&gauge[i]>0&&(flags&0x100)&&
      priority<=first_priority(dash_state)){
    attack_state[i]=dash_state;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   if(use_recovered_melee_timing&&start_special_chord(i,current))continue;
   // The original actor input functions admit special modes before
   // guard/shoot/melee. Reload acceleration begins on the next input pass.
   const int awakened_strike=roster_awakened_strike_state(action_binding(i).character,action_binding(i).weapon);
   if(use_recovered_melee_timing&&awakened_strike>=0&&(special_gauges[i].active0||special_gauges[i].active1||special_gauges[i].active2)&&
      melee_held_[i]>0&&melee_held_[i]<3&&shoot_held[i]>0&&shoot_held[i]<3&&world.actors[i].grounded&&
      (flags&0x100)&&actor_assets(i).state_animations_.count(unsigned(awakened_strike))&&priority<=first_priority(unsigned(awakened_strike))){
    attack_state[i]=unsigned(awakened_strike);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;special_strike[i]={};
    if(uses_rena(i))rena_full_charge[i].second_frame=0;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   const bool ordinary_guard=battle_ordinary_guard_gate(action_binding(i).character,action_binding(i).weapon,(inputs[i].buttons&4)!=0,world.actors[i].grounded,damage_signed(gauge[i]),flags,priority,first_priority(390));
   if(use_recovered_melee_timing&&battle_empty_shot_event(damage_signed(shoot_released[i]),damage_signed(magazines[i][0].rounds),ordinary_guard))++statistics[i].empty_shots;
   //479640 omits the positive-gauge gate;471210/482860 retain it.
   if(use_recovered_melee_timing&&!guard_state[i]&&ordinary_guard){
    guard_state[i]=390;guard_phase[i]=guard_tick[i]=0;elapsed[i]=-1;geometry[i]={};
    air_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;continue;
   }
   // 559970/564610: character11's grounded short shot can chain into 420
   // without a 420.a comparison, before its ordinary jump branch.
   if(use_recovered_melee_timing&&action_binding(i).character==11&&
      action_binding(i).weapon<2&&world.actors[i].grounded&&
      (current==400||(action_binding(i).weapon==1&&current==401))&&
      (flags&0x100)&&shoot_released[i]>0&&shoot_released[i]<20&&
      damage_signed(magazines[i][0].rounds)>0){
    attack_state[i]=420;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
    reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   // 471210: stage1 release uses secondary ammo and450.a/460.a, without
   // the ordinary-shot flags100 gate. Three-weapon stage2 routes to350/360 below.
   if(use_recovered_melee_timing&&actor_assets(i).weapon_item){
    const int full_state=roster_full_charge_admission(action_binding(i).character,action_binding(i).weapon,int(current),world.actors[i].grounded,
      damage_signed(shoot_released[i]),damage_signed(shoot_release_charge[i]),damage_signed(magazines[i][1].rounds),priority,first_priority);
    if(full_state>=0){
     if(uses_rena(i)){
      rena_full_charge[i].second_frame=0;
      if(current>=40&&current<=42)ground_shot_[i].gravity=jump_motion_[i].gravity;
      else if(current==30||current==43)ground_shot_[i].gravity=.5f;
      else if(rena_melee_action_state(current))ground_shot_[i].gravity=air_melee_[i].gravity;
     }
     ++statistics[i].full_charge_shots;attack_state[i]=unsigned(full_state);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
     air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
    }
   }
   const unsigned charge_state=world.actors[i].grounded?450:460;
   if(use_recovered_melee_timing&&actor_assets(i).weapon_item&&
      shoot_released[i]>0&&shoot_release_charge[i]==1&&damage_signed(magazines[i][1].rounds)>0&&
      !(current>=100&&current<300)&&priority<=first_priority(charge_state)){
    ++statistics[i].charge_shots;
    attack_state[i]=charge_state;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   //Only bindings with dedicated fast shots use408.a. Rena0 requests408;
   //Rena1/2 compare402.a and request402, including the early air-dash branch.
   const bool early_air_shot=current==30&&roster_air_dash_fast_shot(action_binding(i).character,
    action_binding(i).weapon,air_phase[i],inputs[i].x||inputs[i].z)&&priority<=first_priority(408);
   if(use_recovered_melee_timing&&actor_assets(i).weapon_item&&!world.actors[i].grounded&&
      shoot_released[i]>0&&shoot_released[i]<20&&
      damage_signed(magazines[i][0].rounds)>0&&(flags&0x100)&&(early_air_shot||priority<=first_priority(402))){
    ground_shot_[i].gravity=(current==41||current==42)?jump_motion_[i].gravity:(current==320||current==332)?air_melee_[i].gravity:.5f;
    attack_state[i]=early_air_shot?408:402;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   // Original slot-7 short-release routing is per character and weapon, not
   // only by weapon number. Front/side/back dash states use the 37-pair table.
   // Walking shots retain their separate pose-dependent admission below.
   unsigned ground_shoot_state=400,ground_shoot_gate=400;bool ground_shoot_supported=true,ground_shoot_consumed=false;
   const auto weapon=action_binding(i).weapon;
   // These active shot states do not re-enter an ordinary short shot. The
   // separate recovery states403/409 retain their original shot cancel.
   const bool shot_reentry_forbidden=current==400||current==401||
      (current>=404&&current<=407)||(current>=410&&current<=413);
   const bool original_walk_route=(action_binding(i).character==0||action_binding(i).character>=3)&&current==10;
   if(original_walk_route){
    float offset;std::memcpy(&offset,&world.actors[i].relationships.heading_offset_bits,4);
    const int chosen=roster_walk_shot_admission(action_binding(i).character,weapon,inputs[i].z,offset,priority,first_priority);
    ground_shoot_consumed=chosen<0;
    if(!ground_shoot_consumed)ground_shoot_state=unsigned(chosen);
   }else if((action_binding(i).character==0||action_binding(i).character>=3)&&(current==20||current==23||current==24||current==27)){
    const auto route=roster_ground_shot_admission(action_binding(i).character,weapon,current,inputs[i].x,inputs[i].z);
    ground_shoot_gate=route.priority_state;
    ground_shoot_consumed=route.state<0;
    if(!ground_shoot_consumed)ground_shoot_state=unsigned(route.state);
   }else if(action_binding(i).character==6&&weapon==0&&
            (current==310||current==311||current==340||current==403||current==409)){
    ground_shoot_state=inputs[i].z<0?410u:inputs[i].z>0?413u:
      inputs[i].x>0?411u:inputs[i].x<0?412u:400u;
   }else if(action_binding(i).character==13&&weapon==0&&
            (current==310||current==311||current==340||current==403||current==409)&&inputs[i].z<0){
    ground_shoot_state=ground_shoot_gate=401;
   }else if(current==20){ground_shoot_state=401;ground_shoot_gate=weapon==2?401:402;}
   else if(action_binding(i).character==0&&weapon==1&&
           (current==23||current==24||current==27)){
    ground_shoot_state=401;ground_shoot_gate=current==23?405:406;
   }
   else if(current==23||current==24||current==27){
    if(weapon==2)ground_shoot_state=ground_shoot_gate=401;
    else {ground_shoot_gate=current==23?405:406;ground_shoot_state=current==23?405:current==24?406:407;}
    }else if(current==10&&weapon!=1){
     float offset;std::memcpy(&offset,&world.actors[i].relationships.heading_offset_bits,4);
     ground_shoot_gate=401;
     if(offset>=-100&&offset<=100){if(weapon==2)ground_shoot_state=401;else ground_shoot_state=offset>=40?412:offset<=-40?411:410;}
    }
    // The shared admission family exposes states absent from some roster DATs.
    // Select an existing moving shot for walking, otherwise the ordinary shot.
    if(!ground_shoot_consumed&&!actor_assets(i).state_frames_.count(ground_shoot_state)){
     const unsigned available=ground_shoot_gate==401&&actor_assets(i).state_frames_.count(401)?401u:400u;
     ground_shoot_state=ground_shoot_gate=available;
    }
    // Failed special-movement priority checks fall through to ordinary400 in the original.
    if(!original_walk_route&&(!priorities.count(ground_shoot_gate)||priority>first_priority(ground_shoot_gate))){ground_shoot_state=ground_shoot_gate=400;ground_shoot_consumed=false;ground_shoot_supported=priorities.count(400)!=0;}
   if(use_recovered_melee_timing&&actor_assets(i).weapon_item&&world.actors[i].grounded&&
      ground_shoot_supported&&!shot_reentry_forbidden&&
      shoot_released[i]>0&&shoot_released[i]<20&&damage_signed(magazines[i][0].rounds)>0&&
      (flags&0x100)&&(original_walk_route||priority<=first_priority(ground_shoot_gate))){
    if(ground_shoot_consumed)continue;
    if(keiichi_walk_shot_state(ground_shoot_state)){walk_shot_[i]={};walk_shot_[i].lower_tick=locomotion_second_tick[i];walk_shot_[i].direction=native_melee_scratch(i).e8;}
    attack_state[i]=ground_shoot_state;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   // Character 11's three slot-7 handlers send grounded 331 directly to
   // 336 on a third held melee frame or a short melee release.
   if(use_recovered_melee_timing&&action_binding(i).character==11&&current==331&&
      world.actors[i].grounded&&(flags&0x100)&&
      (melee_held_[i]==3||(melee_released_[i]>0&&melee_released_[i]<3))){
    attack_state[i]=336;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
    reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   if(use_recovered_melee_timing&&roster_followup_shot303_admission(
      action_binding(i).character,action_binding(i).weapon,current,world.actors[i].grounded,
      flags,shoot_released[i],unsigned(std::max(0,damage_signed(magazines[i][0].rounds))))){
    attack_state[i]=303;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
    reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   if(use_recovered_melee_timing&&roster_followup_shot335_admission(
      action_binding(i).character,action_binding(i).weapon,current,world.actors[i].grounded,
      flags,shoot_released[i],unsigned(std::max(0,damage_signed(magazines[i][0].rounds))))){
    attack_state[i]=335;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
    reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
   }
   // 445ee0/44d850/43ded0 test Rena's melee branch after the shooting
   // branches. A simultaneous short shot/melee release must keep the shot.
   if(use_recovered_melee_timing&&uses_rena(i)){
    const auto& special=special_gauges[i];
    const int next=rena_melee_admission(weapon,int(current),int(elapsed[i]>=0?attack_phase[i]:air_phase[i]),
     world.actors[i].grounded,int(melee_held_[i]),int(released),inputs[i].x,inputs[i].z,
     flags,priority,special.active1,special.ready1!=0,contact_ledger[i].combined(),first_priority);
    if(next>=0){
     if(current==41||current==42)air_melee_[i].gravity=jump_motion_[i].gravity;
     attack_state[i]=unsigned(next);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
     air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
     reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;
     continue;
    }
   }
   // Slot-7 ground dash melee is shared by the roster, with three original
   // actor inputs lacking the state-330 option. Shooting retains precedence.
   if(use_recovered_melee_timing){
    const int dash_melee=roster_ground_dash_melee_admission(action_binding(i).character,
     action_binding(i).weapon,int(current),world.actors[i].grounded,int(melee_held_[i]),
     int(released),inputs[i].x,inputs[i].z,flags,priority,first_priority);
    if(dash_melee>=0){
     attack_state[i]=unsigned(dash_melee);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
     air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;
     reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;walking[i]=false;continue;
    }
   }
   // Directional early-dash332 takes precedence over ordinary airborne320.
   const bool dash_attack=current==30&&roster_air_dash_fast_melee(action_binding(i).character,
    action_binding(i).weapon,air_phase[i],inputs[i].x||inputs[i].z)&&
    priority<=first_priority(332)&&(flags&0x100);
   if(use_recovered_melee_timing&&!world.actors[i].grounded&&dash_attack&&(melee_held_[i]==3||(released>0&&released<3))){
    attack_state[i]=332;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;continue;
   }
   if(use_recovered_melee_timing&&!world.actors[i].grounded&&!dash_attack&&(flags&0x100)&&priority<=first_priority(320)&&(melee_held_[i]==3||(released>0&&released<3))){
    attack_state[i]=320;attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;
    air_state[i]=guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;continue;
   }
   if(action_binding(i).character>=2&&!reaction_active_[i]&&!guard_state[i]&&!air_state[i]&&
      (elapsed[i]>=0||use_recovered_melee_timing)){
    const int next=roster_ground_combo_admission(action_binding(i).character,weapon,current,
     world.actors[i].grounded,melee_held_[i],released,inputs[i].x,inputs[i].z,flags,priority,first_priority);
    if(next>=0){
     attack_state[i]=unsigned(next);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};pose_full_admission_pending_[i]=true;continue;
    }
   }
   if(use_recovered_melee_timing&&(jump_held_[i]==3||(jump_released>0&&jump_released<3))&&!world.actors[i].grounded&&(inputs[i].x||inputs[i].z)&&gauge[i]>0&&(flags&0x100)&&priority<=first_priority(30)){
    air_state[i]=30;air_phase[i]=air_tick[i]=0;elapsed[i]=-1;geometry[i]={};
    guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;continue;
   }
   // Ordinary grounded40 entry.
   if(use_recovered_melee_timing&&(jump_held_[i]==3||(jump_released>0&&jump_released<3))&&world.actors[i].grounded&&gauge[i]>0&&(flags&0x100)&&(priority<=first_priority(40)||priority==49||priority==99)){
    air_state[i]=40;air_phase[i]=air_tick[i]=0;elapsed[i]=-1;geometry[i]={};
    guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;reaction_active_[i]=reaction_pending_[i]=false;air_transition_[i]=false;
   }
   if(pending_air_rejump&&current_action_state(i)==air_rejump_source)start_air_rejump(i);
  }
  for(unsigned i=0;i<4;++i){
   if(!slot7_native_visited[i]&&current_action_state(i)!=states_before_admission[i]){
    if(elapsed[i]>=0&&uses_layered_walk_shot(i))reset_native_upper_state_metadata(i);
    else reset_native_state_metadata(i);
   }
   if(modern_contacts_)synchronize_actor_animation_admission(i);
  }
  //634f60: all slot7 admissions, all slot6 action programs/clocks,420850
  // owner-pool scripts,42e110/slot9,41f580 targeting,6358c0 movement.
  // Projectile scripts see same-visit births and pre-motion target positions.
  std::array<unsigned,4> handler_states{};
  const auto frozen=frozen_mask()|fixture_mask;
  body_frozen_mask_=frozen;
  // Physical movement remains deferred until every handler/pool/slot9 finishes.
  for(unsigned i=0;i<4;++i){
   const unsigned active=current_action_state(i);
   handler_states[i]=active;
   // All slot6 model selections precede body callbacks and the animation clock.
   // Keep selected slots through state changes; blocked/hitstop visits preserve
   // the last native selection until the next actual actor handler runs.
   if(enable_native_shooting&&owns_native_shooting(i,active)){
    if(!(frozen&(1u<<i))){advance_native_shooting_body(world,i,inputs,wall);move_actor(i);}continue;
   }
   if(enable_native_full_charge&&owns_native_full_charge(i,active)){
    if(!(frozen&(1u<<i))){advance_native_full_charge_body(world,i,inputs,wall);move_actor(i);}continue;
   }
   if(enable_native_special_strike&&owns_native_special_strike(i,active)){
    if(!(frozen&(1u<<i))){advance_native_special_strike_body(world,i,inputs,wall);move_actor(i);}continue;
   }
   if(!stop_ticks[i]&&!(fixture_mask&(1u<<i)))prepare_roster_weapon_visuals(world,i);
   if(uses_recovered_actor(i)&&dash_native_body_state(active)){
    if(!(frozen&(1u<<i))){advance_native_dash_body(world,i,inputs);move_actor(i);}
    continue;
   }
   if(uses_recovered_actor(i)&&active>=40&&active<=44){
    if(!(frozen&(1u<<i))){advance_native_jump_body(world,i,inputs);move_actor(i);}
    continue;
   }
   if(active==103||active==203){
    //428510 returns after landing admission. Dispatch once from the entry
    //state, so the newly selected118/119 body waits until the next visit.
    if(!(frozen&(1u<<i))){advance_common_hit_handler(world,i,inputs[i]);move_actor(i);}
    continue;
   }
   if(action_binding(i).character==14&&action_binding(i).weapon==0&&elapsed[i]>=0&&(active==350||active==360)){
    if(!(frozen&(1u<<i))){advance_native_hanyuu_time_stop_body(world,i);move_actor(i);}
    continue;
   }
   if(special_entry[i].state){
    if(!(frozen&(1u<<i))){
     advance_native_special_body(world,i);
     move_actor(i);
    }
    continue;
   }
   if(uses_mion_counter(i)&&elapsed[i]>=0&&(attack_state[i]==370||attack_state[i]==371)&&!reaction_active_[i]&&!guard_state[i]&&!death_state[i]){
    if(!(frozen&(1u<<i))){
     auto& a=world.actors[i];auto& m=a.motion;auto& state=mion_counter[i];const auto& data=actor_assets(i);
     state.state=attack_state[i];state.phase=attack_phase[i];state.frame=unsigned(elapsed[i]);state.speed=m.speed;state.vertical=m.velocity[1];state.movement_angle=m.angles[1];state.invincible=stagger[i].invincible;
     auto scratch=native_melee_scratch(i);state.counter_e8=unsigned(scratch.e8);state.counter_f8=unsigned(scratch.f8);
     state.gravity=ground_shot_[i].gravity;state.camera=native_contact_mode[i];
     std::memcpy(&state.offset,&a.relationships.heading_offset_bits,4);
     const auto& phases=data.state_animations_.at(state.state);const auto id=phases.at(state.phase);
     const bool complete=state.phase+1==phases.size()&&state.frame+1>=data.animation_durations_.at(id);
     struct CounterHost {DevelopmentAnimatedCombat& c;BattleWorld& w;unsigned slot;Wall& wall;
      void voice(unsigned category,int choice,unsigned priority,unsigned option){c.queue_voice({slot,category,priority,choice,-1,choice<0?0x4223d0u:0x422490u,option&255u});}
      void sound(unsigned id){c.queue_sound({slot,id,w.actors[slot].position});}
      void spark(){
       // 4582a0/461810/44fa10: vtable+0c(70,x,y+100,z,heading+offset,0).
       const auto& actor=w.actors[slot];float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
       c.queue_effect({slot,70,{actor.position[0],actor.position[1]+100.f,actor.position[2]},actor.heading+offset,0});
       ++c.mion_counter_windows[slot];
      }
      void statistics(){c.activate_presentation(slot);const auto target=w.actors[slot].relationships.secondary_target;const unsigned bucket=w.actors[target].relationships.secondary_target==slot?0:1;
       ++c.statistics[slot].attacks_issued[bucket];++c.statistics[target].attacks_received[bucket];++c.statistics[slot].attacks_total;
       const auto& allies=w.actors[slot].relationships.allies;const auto ally=allies.empty()?0:allies[0];if(target==w.actors[ally].relationships.secondary_target)++c.statistics[slot].attacks_at_primary_target;
      }
      bool capture(){const bool result=c.capture_actor(w,slot,187,1,{},wall);if(result)++c.mion_captures[slot];return result;}
      void release(const BattleThrowRelease& input){c.release_held_actor(w,slot,input,wall);++c.mion_releases[slot];}
     } host{*this,world,i,wall};
     const auto step=advance_mion_counter(state,contact_ledger[i],complete,a.grounded,host);
     m.speed=state.speed;m.velocity[1]=state.vertical;m.angles[1]=state.movement_angle;stagger[i].invincible=state.invincible;
     std::memcpy(&a.relationships.heading_offset_bits,&state.offset,4);
     scratch.e8=damage_signed(state.counter_e8);scratch.f8=damage_signed(state.counter_f8);scratch.known|=17u;store_native_melee_scratch(i,scratch);
     ground_shot_[i].gravity=air_melee_[i].gravity=jump_motion_[i].gravity=state.gravity;
     native_contact_mode[i]=state.camera;
     // 422900 is a one-visit notification, emitted by statistics() above.
     // Body N requests reset metadata AFTER the preceding camera write.
     if(step.next_state>=0){
      admit_remaining_melee_state(i,unsigned(step.next_state));bind_actor_animation_state(i,unsigned(step.next_state));
     }else if(step.next_phase>=0){attack_phase[i]=unsigned(step.next_phase);elapsed[i]=0;native_melee_second_tick[i]=0;cursors_[i]={};bind_actor_animation_state(i,attack_state[i],attack_phase[i]);}
     else if(++elapsed[i]>int(data.animation_durations_.at(id))&&attack_phase[i]+1<phases.size()&&!data.animation_settings_.at(id).hold_phase){++attack_phase[i];elapsed[i]=0;cursors_[i]={};}
     move_actor(i);
    }
    continue;
   }
   unsigned attack_mask=0;
   // death/respawn. Single-pass blocks preserve each stage's early exits.
   do {
    const auto& data=actor_assets(i);
    if(!death_state[i]||stop_ticks[i]||(fixture_mask&(1u<<i)))continue;
    if(enable_native_death&&uses_recovered_actor(i)){advance_native_death_handler(world,i,inputs[i]);move_actor(i);continue;}
    auto& actor=world.actors[i];auto& m=actor.motion;
    const auto state=death_state[i];const bool first=death_phase[i]==0&&death_tick[i]==0;
    bool transition=false;
    auto change=[&](unsigned next){death_state[i]=next;death_phase[i]=death_tick[i]=death_wait_[i]=0;transition=true;};
    if(state==194){
     if(actor.grounded&&m.velocity[1]<=0){
      death_state[i]=0;air_state[i]=44;air_phase[i]=air_tick[i]=0;air_transition_[i]=true;
      m.velocity[1]=0;stagger[i].invincible=60;transition=true;
     }else {
      float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
      steer_battle_offset(offset,inputs[i].x,inputs[i].z,1.f);
      std::memcpy(&actor.relationships.heading_offset_bits,&offset,4);m.velocity[1]-=.5f;
     }
    }else if(state==191||state==192||state==193||state==196||state==197){
     if(!actor.grounded){m.velocity[1]=0;change(195);}
     else {
      if(first){
       if(state!=196)m.speed=state==193?0.f:state==197?-15.f:-20.f;
       if(state==192||state==193||state==197)m.angles[1]=0;
      }
      if(state==191||state==196){
       if(m.speed>0)m.speed=std::max(0.f,m.speed-.25f);
       if(m.speed<0)m.speed=std::min(0.f,m.speed+.25f);
      }else m.speed=std::min(0.f,m.speed+(state==192?.5f:1.5f));
     }
    }else if(state==195||state==198||state==199){
     if(first){
      m.angles[1]=0;
      if(state!=195){m.speed=-30.f;m.velocity[1]=20.f;}
     }
     if(actor.grounded&&m.velocity[1]<0){m.velocity[1]=0;change(196);}
     else if(state!=195&&m.velocity[1]<6.f&&death_phase[i]==1){death_phase[i]=2;death_tick[i]=0;transition=true;}
     else {
      m.velocity[1]-=.3f;
      if(state!=195&&m.speed< -4.f)m.speed+=.25f;
     }
    }
    if(!transition&&state!=194&&death_phase[i]==1&&
       (state==191||state==192||state==193||state==196||state==197)){
     if(death_wait_[i]<31)++death_wait_[i];
     if(death_wait_[i]>30&&respawn_enabled_&&teams_.score[i/2]<team_limits_[i/2]){
      auto spawn=[&](){
       const auto x=random_.next(),z=random_.next();
       actor.position={float(x%(std::uint32_t(respawn_bounds_[2])-std::uint32_t(respawn_bounds_[0])))+float(respawn_bounds_[0]),1000.f,
        float(z%(std::uint32_t(respawn_bounds_[3])-std::uint32_t(respawn_bounds_[1])))+float(respawn_bounds_[1])};
      };
      // 192/193/197 call 421bd0 before 4219a0, which calls it a second time.
      if(state==192||state==193||state==197)spawn();
      target_availability[i].changed=true; // 4219a0 sets transient aecb before41f580.
      for(auto& magazine:magazines[i])reset_battle_magazine(magazine);
      health[i]=delayed_health[i]=10000;gauge[i]=1000;stagger[i].down=stagger[i].down_timer=0;death_bonus_used[i]=0;
      stagger[i].count=stagger[i].accum=stagger[i].timer=0;stagger[i].invincible=30;
      status[i].duration.fill(0);m.velocity={};m.speed=0;spawn();actor.grounded=0;
      change(194);
     }
    }
    if(!transition){
     const auto& phases=data.state_animations_.at(death_state[i]);const auto id=phases.at(death_phase[i]);
     if(++death_tick[i]>data.animation_durations_.at(id)&&death_phase[i]+1<phases.size()&&!data.animation_settings_.at(id).hold_phase){++death_phase[i];death_tick[i]=0;}
    }
    // Exhausted teams retain the final death pose; match-result presentation is pending.
    move_actor(i);
   } while(false);
   // guard and idle gauge. Single-pass blocks preserve each stage's early exits.
   bool native_guard_visit=false;
   do {
    const auto& data=actor_assets(i);
    if((frozen&(1u<<i))||reaction_active_[i])continue;
    // Normal idle/walk/landing recovery (+834); +7f4 slows it from 40 to 5.
    const bool idle_airborne=!world.actors[i].grounded&&!walking[i]&&!air_state[i]&&
                             !recovery_state[i]&&!ground_hit_state[i];
    if(!(uses_recovered_actor(i)&&(current_action_state(i)==0||current_action_state(i)==10))&&
       (world.actors[i].grounded||idle_airborne)&&!guard_state[i]&&elapsed[i]<0&&
       (air_state[i]==44||(!air_state[i]&&!inputs[i].buttons&&
         !(walking[i]&&(!world.actors[i].grounded||(!inputs[i].x&&!inputs[i].z))))))
     gauge[i]=std::min(1000,gauge[i]+(damage_signed(status[i].duration[6])>0?5:40));
    if(!use_recovered_melee_timing&&(inputs[i].buttons&4)&&!guard_state[i]&&elapsed[i]<0&&!air_state[i]&&!reaction_active_[i]&&world.actors[i].grounded){guard_state[i]=390;guard_phase[i]=guard_tick[i]=0;}
    if(!guard_state[i])continue;
    if(uses_recovered_actor(i)){advance_native_guard_body(world,inputs,i);native_guard_visit=true;continue;}
    auto& actor=world.actors[i];auto& g=guard_motion_[i];
    const auto& phases=data.guard_data_.at(guard_state[i]);const auto& phase=phases.at(guard_phase[i]);
    g.state=guard_state[i];g.phase=guard_phase[i];g.frame=guard_tick[i];g.grounded=actor.grounded;
    // The original guard hold checks the jump and melee counters separately.
    // Bit 4 remains an internal alias for probes and the dedicated guard key.
    g.button_a=(inputs[i].buttons&6)!=0;g.button_b=(inputs[i].buttons&5)!=0;g.speed=actor.motion.speed;
    std::memcpy(&g.offset,&actor.relationships.heading_offset_bits,4);
    g.complete=g.phase+1==phases.size()&&g.frame+1>=data.animation_durations_.at(phase.value);
    if(uses_recovered_actor(i))g.contact_flags=contact_ledger[i].combined();
    g.gauge=gauge[i];const auto next=advance_battle_guard(g);
    if(uses_mion_counter(i)&&g.state==391&&g.phase==2&&next.state<0)stagger[i].invincible=45;gauge[i]=g.gauge;
    actor.motion.speed=g.speed;actor.motion.angles[1]=0;actor.motion.velocity[1]=0;
    std::memcpy(&actor.relationships.heading_offset_bits,&g.offset,4);
    const bool guarded_feedback=uses_recovered_actor(i)&&next.state==391&&(g.state==390||g.state==391);
    const auto guard_particle=[&](){queue_effect({i,70,{actor.position[0],actor.position[1]+100.f,actor.position[2]},actor.heading+g.offset});};
    // All46 original slot-6 bodies use particle70 at+y100 (006a16e0).
    //390 emits before State391;391 retrigger emits after State391.
    if(guarded_feedback&&g.state==390)guard_particle();
    if(next.state>=0){
     if(uses_recovered_actor(i))reset_native_state_metadata(i);
     guard_state[i]=0;guard_flags[i]=0;
     if(next.state==43||next.state==103){air_state[i]=unsigned(next.state);air_phase[i]=air_tick[i]=0;}
     else if(next.state>=390){guard_state[i]=unsigned(next.state);guard_phase[i]=guard_tick[i]=0;}
    }else if(next.phase>=0){guard_phase[i]=unsigned(next.phase);guard_tick[i]=0;}
    else if(++guard_tick[i]>data.animation_durations_.at(phase.value)&&g.phase+1<phases.size()&&!data.animation_settings_.at(phase.value).hold_phase){++guard_phase[i];guard_tick[i]=0;}
    if(guarded_feedback){if(g.state==391)guard_particle();queue_sound({i,51,actor.position});}
    // Original Clear follows State/feedback; retain contact during transition.
    if(uses_recovered_actor(i)&&next.clear_contacts)contact_ledger[i].clear_flags();
    if(guard_state[i]){ActorFrameCursor cursor;guard_flags[i]=cursor.advance(data.guard_data_.at(guard_state[i]).at(guard_phase[i]),guard_tick[i]).flags28;}
   } while(false);
   // A guard return never executes the newly admitted idle/air body this visit.
   if(native_guard_visit){move_actor(i);continue;}
   // Native State0/10 owns gauge, motion, admissions and both clocks. A
   //transition returns before the new State body and its clock this visit.
   if(uses_recovered_actor(i)&&(current_action_state(i)==0||current_action_state(i)==10)){
    if(!(frozen&(1u<<i))){advance_native_locomotion_body(world,i,inputs);move_actor(i);}
    continue;
   }
   // action mask. Single-pass blocks preserve each stage's early exits.
   do {
    const bool starting=!use_recovered_melee_timing&&(inputs[i].buttons&1)&&!pressed_[i]&&elapsed[i]<0&&damage_signed(health[i])>0&&!reaction_active_[i]&&!air_state[i]&&world.actors[i].grounded;
    if(elapsed[i]>=0||starting||air_state[i]||guard_state[i])attack_mask|=1u<<i;
   } while(false);
   // walking. Single-pass blocks preserve each stage's early exits.
   do {
    if(frozen&(1u<<i))continue;
    // Earlier slot6 bodies can capture this actor before its own visit.
    // Read the live reaction owner, preserving the motion carried into187.
    if(reaction_active_[i]||(attack_mask&(1u<<i))){walking[i]=false;walk_tick[i]=0;continue;}
    auto& actor=world.actors[i];auto& motion=actor.motion;
    float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
    if(actor.grounded){
     const bool moving=inputs[i].x||inputs[i].z;
     if(walking[i]&&!moving){
      // Original state10 enters state0 and returns before its idle speed,
      // steering clock and gauge work. The following tick runs state0.
      walking[i]=false;walk_tick[i]=0;move_actor(i);continue;
     }
     if(!moving||!walking[i])walk_tick[i]=0;else ++walk_tick[i];walking[i]=moving;
     if(action_binding(i).policy==BattleActionPolicy::legacy_test)advance_battle_walk(walk_motion_[i],inputs[i].x,inputs[i].z,motion.speed,offset);
     else advance_roster_walk(walk_motion_[i],action_binding(i).character,action_binding(i).weapon,inputs[i].x,inputs[i].z,motion.speed,offset,special_gauges[i].active0||special_gauges[i].active1||special_gauges[i].active2);
     motion.angles[1]=0;
     // Character 3 weapon 2's original state0/10 handlers omit the common
     // vertical-speed reset. All other DAT roster configurations reset it.
     if(action_binding(i).character!=3||action_binding(i).weapon!=2)motion.velocity[1]=0;
     std::memcpy(&actor.relationships.heading_offset_bits,&offset,4);
    }else if(!air_state[i]&&!recovery_state[i]&&!ground_hit_state[i]&&
             !special_entry[i].state&&elapsed[i]<0){
     // State0 performs its idle reset before the off-ground transition;
     // state10 changes directly to43 and carries its current velocity.
     if(!walking[i]){
      if(action_binding(i).policy==BattleActionPolicy::legacy_test)
       advance_battle_walk(walk_motion_[i],0,0,motion.speed,offset);
      else advance_roster_walk(walk_motion_[i],action_binding(i).character,action_binding(i).weapon,0,0,motion.speed,offset,special_gauges[i].active0||special_gauges[i].active1||special_gauges[i].active2);
      motion.angles[1]=0;
      if(action_binding(i).character!=3||action_binding(i).weapon!=2)motion.velocity[1]=0;
     }
     walking[i]=false;walk_tick[i]=0;air_state[i]=43;air_phase[i]=air_tick[i]=0;
     move_actor(i);continue;
    }else {walking[i]=false;walk_tick[i]=0;motion.velocity[1]-=.5f;}
    move_actor(i);
   } while(false);
   // attack/air action. Single-pass blocks preserve each stage's early exits.
   do {
    const auto& data=actor_assets(i);
    if(!(attack_mask&(1u<<i))||(frozen&(1u<<i))||reaction_active_[i])continue;
    auto& actor=world.actors[i];auto& motion=actor.motion;
    if(guard_state[i]){move_actor(i);continue;}
    if(air_state[i]==30){
     auto& dash=air_dash_[i];dash.phase=air_phase[i];dash.frame=air_tick[i];dash.x=inputs[i].x;dash.z=inputs[i].z;
     dash.held=(inputs[i].buttons&2)!=0;dash.grounded=actor.grounded;dash.gauge=gauge[i];dash.speed=motion.speed;dash.vertical=motion.velocity[1];
     std::memcpy(&dash.offset,&actor.relationships.heading_offset_bits,4);
     const auto& phases=data.state_animations_.at(30);dash.complete=dash.phase+1==phases.size()&&dash.frame+1>=data.animation_durations_.at(phases[dash.phase]);
     dash.movement=motion.angles[1];const auto& special=special_gauges[i];
     const auto next=action_binding(i).policy==BattleActionPolicy::legacy_test?advance_battle_air_dash(dash):advance_roster_air_dash(dash,action_binding(i).character,action_binding(i).weapon,special.active0||special.active1||special.active2);gauge[i]=dash.gauge;motion.speed=dash.speed;motion.velocity[1]=dash.vertical;motion.angles[1]=dash.movement;
     std::memcpy(&actor.relationships.heading_offset_bits,&dash.offset,4);
     if(next.state>=0){air_state[i]=unsigned(next.state);air_phase[i]=air_tick[i]=0;air_transition_[i]=true;}
     else if(next.phase>=0){air_phase[i]=unsigned(next.phase);air_tick[i]=0;air_transition_[i]=true;}
     move_actor(i);continue;
    }
    if(air_state[i]>=40&&air_state[i]<=42){
     auto& jump=jump_motion_[i];jump.state=air_state[i];jump.phase=air_phase[i];jump.frame=air_tick[i];
     jump.x=inputs[i].x;jump.z=inputs[i].z;jump.grounded=actor.grounded;
     jump.button_ticks=(inputs[i].buttons&2)?std::max(1u,jump.button_ticks):0;
     jump.speed=motion.speed;jump.vertical=motion.velocity[1];
     std::memcpy(&jump.offset,&actor.relationships.heading_offset_bits,4);
     const auto& phases=data.state_animations_.at(jump.state);
     jump.animation_complete=jump.phase+1==phases.size()&&jump.frame+1>=data.animation_durations_.at(phases[jump.phase]);
     jump.slow_recovery=damage_signed(status[i].duration[6])>0;jump.gauge=gauge[i];
     const auto tuning=uses_recovered_actor(i)?battle_roster_jump_tuning(action_binding(i).character,action_binding(i).weapon):BattleJumpTuning{};
     const auto next=advance_battle_jump(jump,tuning);gauge[i]=jump.gauge;
     motion.speed=jump.speed;motion.velocity[1]=jump.vertical;motion.angles[1]=0;
     std::memcpy(&actor.relationships.heading_offset_bits,&jump.offset,4);
     if(next){air_state[i]=next;air_phase[i]=air_tick[i]=0;air_transition_[i]=true;}
     move_actor(i);continue;
    }
    if(air_state[i]){
     if(air_state[i]==44){motion.speed=0;motion.velocity[1]=0;motion.angles[1]=0;}
     else {
      // State43 is common falling motion with roster-specific horizontal control.
      float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
      if(air_state[i]==43){
       const auto tuning=uses_recovered_actor(i)?battle_roster_jump_tuning(action_binding(i).character,action_binding(i).weapon):BattleJumpTuning{};
       advance_battle_falling_horizontal(motion.speed,offset,inputs[i].x,inputs[i].z,tuning);
      }
      else steer_battle_offset(offset,inputs[i].x,inputs[i].z,1.f);
      std::memcpy(&actor.relationships.heading_offset_bits,&offset,4);
      motion.velocity[1]-=.5f;
     }
     move_actor(i);continue;
    }
    // A pending input edge is not state300 yet. update() enters that state;
    // its initialization must run once, on the following movement/handler pass.
    if(uses_recovered_actor(i)&&elapsed[i]<0){motion.speed=0;move_actor(i);continue;}
    const unsigned phase=elapsed[i]<0?0:attack_phase[i];
    const unsigned frame=elapsed[i]<0?0:unsigned(elapsed[i]);
    float offset;std::memcpy(&offset,&actor.relationships.heading_offset_bits,4);
    if(uses_recovered_actor(i)||attack_state[i]==320||attack_state[i]==329||attack_state[i]==332||attack_state[i]==333||attack_state[i]==334||attack_state[i]==339||battle_ground_dash_state(attack_state[i])){
     auto& action=keiichi_motion_[i];action.phase=int(phase);action.frame=int(frame);action.speed=motion.speed;action.offset=offset;
     KeiichiAttack300Input request;
     request.voice_flags=melee_voice_flags[i];
     request.contact=contact_ledger[i].combined();
     request.grounded=actor.grounded;request.animation_complete=phase+1==attack_phases(i).size()&&frame+1>=data.animation_durations_.at(attack_phases(i)[phase].value);
     const auto& target=world.actors.at(actor.relationships.target).position;
     request.distance_squared=battle_target_distance_squared(actor.position,target);
      KeiichiAttack300Effects effect;
      if(uses_recovered_actor(i)&&(remaining_melee_native_state(attack_state[i])||extra_melee_native_body_binding(action_binding(i).character,action_binding(i).weapon,attack_state[i])||slot7_ranked_body_binding(action_binding(i).character,action_binding(i).weapon,attack_state[i]))){
       RemainingMeleeNativeInput in;in.character=action_binding(i).character;in.weapon=action_binding(i).weapon;in.state=attack_state[i];
       in.phase=phase;in.frame=frame;in.tick2=native_melee_second_tick[i];in.contact=request.contact;
       in.complete=request.animation_complete;in.grounded=request.grounded;in.blocked=stop_ticks[i]!=0;
       in.distance_squared=request.distance_squared;in.voice_flags=request.voice_flags;in.direction=int(dash_command_cache_[i]);
       in.held=melee_held_[i];in.released=melee_released_[i];in.jump=jump_held_[i];in.slow=damage_signed(status[i].duration[6]);
       in.active={std::uint8_t(special_gauges[i].active0),std::uint8_t(special_gauges[i].active1),std::uint8_t(special_gauges[i].active2)};
       in.heading=actor.heading;in.height=target[1]-actor.position[1];in.origin=actor.position;
       in.rank_timer=damage_signed(field_contact_rank_timer[i]);in.mine_clock=damage_signed(satoko_mine_clock[i]);
       const auto& phases=attack_phases(i);const auto animation=phases.at(phase).value;
       in.duration=int(data.animation_durations_.at(animation));in.hold=int(data.animation_settings_.at(animation).hold_phase);
       for(const auto& p:phases){in.phase_durations.push_back(int(data.animation_durations_.at(p.value)));in.phase_holds.push_back(int(data.animation_settings_.at(p.value).hold_phase));}
       if(in.character==4&&in.weapon==2&&in.state==332){const auto point=body_contact_points(world,actor.relationships.target)[1];for(unsigned axis=0;axis<3;++axis)in.target_spine[axis]=point[axis];in.target_spine_valid=true;}
       advance_native_remaining_melee_body(world,i,in,slot7_ranked_body_binding(in.character,in.weapon,in.state)?advance_slot7_ranked_control:advance_remaining_melee_native_control);move_actor(i);continue;
      }else if(attack_state[i]==300){
      auto scratch=native_melee_scratch(i);auto state=native_followup_motion(world,i);
      GroundMeleeNativeInput in;in.character=action_binding(i).character;in.weapon=action_binding(i).weapon;in.state=300;
      in.phase=phase;in.frame=frame;in.contact=request.contact;in.complete=request.animation_complete;in.grounded=request.grounded;
      in.blocked=stop_ticks[i]!=0;in.distance_squared=request.distance_squared;in.voice_flags=request.voice_flags;
      in.direction=int(dash_command_cache_[i]);in.gauge=damage_signed(gauge[i]);in.rank=int(field_contact_rank[i]);in.mine_clock=satoko_mine_clock[i];
      const auto next=advance_ground_melee_native_control(scratch,state,in);ground_melee_control_effects[i]=next;ground_melee_control_visited[i]=true;
      store_native_melee_scratch(i,scratch);action.speed=state.speed;action.offset=state.offset;action.movement_angle=state.movement;
      motion.velocity[1]=state.vertical;ground_shot_[i].gravity=air_melee_[i].gravity=state.gravity;walk_motion_[i].step=state.turn;native_contact_mode[i]=state.contact_mode;
      std::optional<ActorSkeleton> muzzle;
      for(unsigned n=0;n<next.count;++n){const auto& event=next.events[n];switch(event.kind){
       case GroundMeleeKind::Clear:contact_ledger[i].clear_flags();contacted_[i]={};break;
       case GroundMeleeKind::Capacity:contact_ledger[i].set_capacity(unsigned(event.value));break;
       case GroundMeleeKind::Activate:activate_presentation(i);break;
       case GroundMeleeKind::Statistics:record_melee_attack(world,i,unsigned(event.value));break;
       case GroundMeleeKind::Sound:queue_sound({i,unsigned(event.value),actor.position});break;
       case GroundMeleeKind::Voice:queue_voice({i,unsigned(event.value),unsigned(event.argument),-1,-1,0x4223d0,0});break;
       case GroundMeleeKind::Projectile:{
        GroundShotEffects shot;shot.fire=true;shot.bullet_slot=unsigned(event.value);shot.origin=GroundShotOrigin::AttachmentZero;
        shot.attachment_slot=0;shot.count_attack=false;
        //Ohishi2's434fd0 precedes this visit's body turn. Use the entry
        //offset with the already selected prefix model/socket.
        append_actor_projectile_request(world,i,shot,actor.position,actor.heading,offset,muzzle,selected_held_weapon_models(i)[0]);
        if(next.next_rank>=0)field_contact_rank[i]=unsigned(next.next_rank);
        break;
       }
       case GroundMeleeKind::Query:case GroundMeleeKind::State:case GroundMeleeKind::Phase:break;
      }}
      elapsed[i]+=next.tick_delta;native_melee_second_tick[i]+=unsigned(next.tick2_delta);
      effect.next_state=next.next_state;effect.next_phase=next.next_phase;
      if(!next.clock)attack_return_[i]=true;
     }else if(attack_state[i]==330||attack_state[i]==331){
      auto scratch=native_melee_scratch(i);auto state=native_dash_melee_motion(world,i);
      DashMeleeNativeInput in;in.character=action_binding(i).character;in.weapon=action_binding(i).weapon;in.state=attack_state[i];
      in.phase=phase;in.frame=frame;in.contact=request.contact;in.complete=request.animation_complete;in.grounded=request.grounded;
      in.blocked=stop_ticks[i]!=0;in.distance_squared=request.distance_squared;in.voice_flags=request.voice_flags;
      in.direction=int(dash_command_cache_[i]);in.gauge=damage_signed(gauge[i]);in.rank=int(field_contact_rank[i]);in.mine_clock=satoko_mine_clock[i];
      const auto next=advance_dash_melee_native_control(scratch,state,in);dash_melee_control_effects[i]=next;dash_melee_control_visited[i]=true;
      store_native_melee_scratch(i,scratch);action.speed=state.speed;action.offset=state.offset;action.movement_angle=state.movement;
      motion.velocity[1]=state.vertical;ground_shot_[i].gravity=air_melee_[i].gravity=state.gravity;walk_motion_[i].step=state.turn;native_contact_mode[i]=state.contact_mode;
      air_melee_[i].pitch=state.pitch;air_melee_[i].pivot=state.pivot;
      std::optional<ActorSkeleton> muzzle;
      for(unsigned n=0;n<next.count;++n){const auto& event=next.events[n];switch(event.kind){
       case DashMeleeKind::Clear:contact_ledger[i].clear_flags();contacted_[i]={};break;
       case DashMeleeKind::Capacity:contact_ledger[i].set_capacity(unsigned(event.value));break;
       case DashMeleeKind::Activate:activate_presentation(i);break;
       case DashMeleeKind::Statistics:record_melee_attack(world,i,unsigned(event.value));break;
       case DashMeleeKind::Sound:queue_sound({i,unsigned(event.value),actor.position});break;
       case DashMeleeKind::Voice:queue_voice({i,unsigned(event.value),unsigned(event.argument),event.mode?event.mode-1:-1,-1,event.mode?0x422490u:0x4223d0u,0});break;
       case DashMeleeKind::SceneObject:queue_effect({i,unsigned(event.value),actor.position,actor.heading});break;
       case DashMeleeKind::Projectile:{
        GroundShotEffects shot;shot.fire=true;shot.bullet_slot=unsigned(event.value);shot.origin=GroundShotOrigin::AttachmentZero;shot.attachment_slot=0;shot.count_attack=false;
        //434fd0 executes before this visit's turn, with the selected prefix model.
        append_actor_projectile_request(world,i,shot,actor.position,actor.heading,offset,muzzle,selected_held_weapon_models(i)[0]);
        if(next.next_rank>=0)field_contact_rank[i]=unsigned(next.next_rank);break;
       }
       case DashMeleeKind::Query:case DashMeleeKind::State:case DashMeleeKind::Phase:break;
      }}
      if(next.frame_override>=0){elapsed[i]=next.frame_override;native_melee_second_tick[i]=unsigned(next.frame_override);cursors_[i]={};}
      effect.next_state=next.next_state;effect.next_phase=next.next_phase;effect.strike=next.strike;
      if(!next.clock)attack_return_[i]=true;
     }else if(attack_state[i]==310||attack_state[i]==311){
      auto scratch=native_melee_scratch(i);auto state=native_dash_melee_motion(world,i);
      DirectionalMeleeNativeInput in;in.character=action_binding(i).character;in.weapon=action_binding(i).weapon;in.state=attack_state[i];
      in.phase=phase;in.frame=frame;in.contact=request.contact;in.complete=request.animation_complete;in.grounded=request.grounded;
      in.blocked=stop_ticks[i]!=0;in.distance_squared=request.distance_squared;in.jump=(inputs[i].buttons&2)!=0;in.mine_clock=satoko_mine_clock[i];in.apply_phase_service=true;
      const auto next=advance_directional_melee_native_control(scratch,state,in);directional_melee_control_effects[i]=next;directional_melee_control_visited[i]=true;
      store_native_melee_scratch(i,scratch);store_native_air_melee_motion(world,i,state);
      for(unsigned n=0;n<next.count;++n){const auto& event=next.events[n];switch(event.kind){
       case DashMeleeKind::Clear:contact_ledger[i].clear_flags();contacted_[i]={};break;
       case DashMeleeKind::Capacity:contact_ledger[i].set_capacity(unsigned(event.value));break;
       case DashMeleeKind::Activate:activate_presentation(i);break;
       case DashMeleeKind::Statistics:record_melee_attack(world,i,unsigned(event.value));break;
       case DashMeleeKind::Sound:queue_sound({i,unsigned(event.value),actor.position});break;
       case DashMeleeKind::Voice:queue_voice({i,unsigned(event.value),unsigned(event.argument),-1,-1,0x4223d0,0});break;
       case DashMeleeKind::SceneObject:queue_effect({i,unsigned(event.value),actor.position,actor.heading});break;
       case DashMeleeKind::Phase:if(next.continue_phase){attack_phase[i]=unsigned(event.value);elapsed[i]=0;native_melee_second_tick[i]=0;cursors_[i]={};action.phase=event.value;action.frame=0;}break;
       case DashMeleeKind::Query:case DashMeleeKind::State:case DashMeleeKind::Projectile:break;
      }}
      if(next.frame_override>=0){elapsed[i]=next.frame_override;native_melee_second_tick[i]=unsigned(next.frame_override);cursors_[i]={};}
      effect.next_state=next.next_state;effect.next_phase=next.continue_phase?-1:next.next_phase;effect.strike=next.strike;
      if(!next.clock)attack_return_[i]=true;
     }else if(attack_state[i]==320){
      auto scratch=native_melee_scratch(i);auto state=native_dash_melee_motion(world,i);
      AirMeleeNativeInput in;in.character=action_binding(i).character;in.weapon=action_binding(i).weapon;in.state=320;
      in.phase=phase;in.frame=frame;in.contact=request.contact;in.complete=request.animation_complete;in.grounded=request.grounded;
      in.blocked=stop_ticks[i]!=0;in.distance_squared=request.distance_squared;in.voice_flags=request.voice_flags;in.height=target[1]-actor.position[1];in.mine_clock=satoko_mine_clock[i];
      const auto next=advance_air_melee_native_control(scratch,state,in);air_melee_control_effects[i]=next;air_melee_control_visited[i]=true;
      store_native_melee_scratch(i,scratch);store_native_air_melee_motion(world,i,state);
      for(unsigned n=0;n<next.count;++n){const auto& event=next.events[n];switch(event.kind){
       case DashMeleeKind::Clear:contact_ledger[i].clear_flags();contacted_[i]={};break;
       case DashMeleeKind::Capacity:contact_ledger[i].set_capacity(unsigned(event.value));break;
       case DashMeleeKind::Activate:activate_presentation(i);break;
       case DashMeleeKind::Statistics:record_melee_attack(world,i,unsigned(event.value));break;
       case DashMeleeKind::Sound:queue_sound({i,unsigned(event.value),actor.position});break;
       case DashMeleeKind::Voice:queue_voice({i,unsigned(event.value),unsigned(event.argument),-1,-1,0x4223d0,0});break;
       case DashMeleeKind::Query:case DashMeleeKind::State:case DashMeleeKind::Phase:case DashMeleeKind::Projectile:case DashMeleeKind::SceneObject:break;
      }}
      if(next.frame_override>=0){elapsed[i]=next.frame_override;native_melee_second_tick[i]=unsigned(next.frame_override);cursors_[i]={};}
      effect.next_state=next.next_state;effect.next_phase=next.next_phase;effect.strike=next.strike;
      if(!next.clock)attack_return_[i]=true;
     }else if(uses_rena(i)&&rena_melee_action_state(attack_state[i])){
      auto& air=air_melee_[i];air.vertical=motion.velocity[1];action.movement_angle=motion.angles[1];
      const auto next=advance_rena_melee(action_binding(i).weapon,attack_state[i],air,action,request,(inputs[i].buttons&2)!=0,target[1]-actor.position[1],walk_motion_[i].step,gauge[i],damage_signed(status[i].duration[6])>0);
      effect=next;motion.velocity[1]=air.vertical;
      if(next.contact_mode>=0)native_contact_mode[i]=next.contact_mode;
      if(next.activate)activate_presentation(i);
      if(next.reset_capacity)contact_ledger[i].set_capacity(1);
      if(next.disable_contact)contact_ledger[i].set_capacity(0);
      elapsed[i]+=int(next.extra_clock_ticks);
      if(next.frame_override>=0){elapsed[i]=next.frame_override;cursors_[i]={};if(!next.advance_after_frame_override)attack_return_[i]=true;}
     }else if(uses_rena(i)&&rena_full_charge_actor_state(action_binding(i).weapon,attack_state[i])){
      rena_held_model_state[i]=attack_state[i];rena_held_models[i]={0,1};
      auto& s=rena_full_charge[i];s.weapon=action_binding(i).weapon;s.state=attack_state[i];s.phase=phase;s.frame=frame;
      if(phase==0&&frame==0)s.second_frame=0;
      const auto animation=attack_phases(i).at(phase).value;s.duration=data.animation_durations_.at(animation);
      s.hold_phase=data.animation_settings_.at(animation).hold_phase!=0;s.complete=request.animation_complete;
      s.blocked=stop_ticks[i]!=0;s.grounded=request.grounded;s.speed=action.speed;s.offset=action.offset;
      s.vertical=motion.velocity[1];s.gravity=ground_shot_[i].gravity;s.movement=motion.angles[1];s.heading=actor.heading;
      s.position=actor.position;s.target=target;s.turn_step=walk_motion_[i].step;
      s.recharge=std::uint32_t(gauge[i]);s.status7f4=status[i].duration[6];s.activated=special_gauges[i].activated0;
      s.contacts=contact_ledger[i].flags;for(unsigned v=0;v<4;++v)s.capacity[v]=damage_signed(contact_ledger[i].remaining[v]);
      const auto next=advance_rena_full_charge(s,[&](){return next_battle_random();});
      if(s.state==350&&action_binding(i).weapon==0)native_contact_mode[i]=int(s.attack_flag); //PATCHES.md: 43ffc0 case 0x15e writes +684 each update.
      action.speed=s.speed;action.offset=s.offset;action.movement_angle=s.movement;
      motion.velocity[1]=s.vertical;ground_shot_[i].gravity=s.gravity;walk_motion_[i].step=s.turn_step;
      gauge[i]=damage_signed(s.recharge);special_gauges[i].activated0=s.activated;
      contact_ledger[i].flags=s.contacts;for(unsigned v=0;v<4;++v)contact_ledger[i].remaining[v]=std::uint32_t(s.capacity[v]);
      std::optional<ActorSkeleton> muzzle;
      for(const auto& event:next.events){
       if(event.kind==RenaFullEventKind::state){bind_actor_animation_state(i,unsigned(event.id));pose_body_admission_replayed_[i]=true;}
       else if(event.kind==RenaFullEventKind::phase){bind_actor_animation_state(i,pose_bound_state_[i][1],unsigned(event.id));pose_body_admission_replayed_[i]=true;}
       else if(event.kind==RenaFullEventKind::model)rena_held_models[i].at(unsigned(event.choice))=event.id;
       else if(event.kind==RenaFullEventKind::activate)activate_presentation(i);
       else if(event.kind==RenaFullEventKind::sound)queue_sound({i,unsigned(event.id),actor.position});
       else if(event.kind==RenaFullEventKind::voice)queue_voice({i,unsigned(event.id),unsigned(event.priority),event.choice,-1,event.choice<0?0x4223d0u:0x422490u,unsigned(event.flag)&255u});
       else if(event.kind==RenaFullEventKind::particle)queue_effect({i,unsigned(event.id),event.position,event.yaw,event.pitch});
       else if(event.kind==RenaFullEventKind::shooting_statistics){++shots_attempted[i];record_shooting_attack(world,i,1);}
       else if(event.kind==RenaFullEventKind::melee_statistics)record_melee_attack(world,i,1);
       else if(event.kind==RenaFullEventKind::world_projectile||event.kind==RenaFullEventKind::attachment_projectile){
        GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=unsigned(event.id);shot.pitch=event.pitch;
        shot.origin=GroundShotOrigin::World;
        if(event.kind==RenaFullEventKind::attachment_projectile){
         shot.origin=GroundShotOrigin::AttachmentZero;shot.yaw=event.yaw;
        }
        append_actor_projectile_request(world,i,shot,event.position,event.yaw,action.offset,muzzle,
         shot.origin==GroundShotOrigin::AttachmentZero?std::optional<int>(rena_held_models[i][shot.attachment_slot]):std::nullopt);
       }
      }
      elapsed[i]=int(s.frame);effect.next_state=next.next_state;effect.next_phase=next.next_phase;
      if(next.next_phase>=0||next.next_state>=0)s.second_frame=0;
      if(!next.clock_advanced)attack_return_[i]=true;
     }else if(uses_rena(i)&&attack_state[i]==400){
      rena_held_model_state[i]=400;rena_held_models[i]={0,1};
      auto& s=rena_ground_shots[i];s.phase=int(phase);s.frame=int(frame);
      s.speed=action.speed;s.offset=action.offset;s.movement=motion.angles[1];s.gravity=ground_shot_[i].gravity;
      const auto& special=special_gauges[i];
      const RenaGroundShotInput in{request.animation_complete,request.grounded,special.active1&&special.ready1!=0,
       damage_signed(magazines[i][0].rounds),battle_target_elevation(actor.position,target),actor.heading,actor.position};
      rena_shot_strike[i]=false;std::optional<ActorSkeleton> muzzle;
      const auto next=advance_rena_ground_shot(action_binding(i).weapon,s,in,random_,[&](const RenaShotEvent& event,const RenaGroundShotMotion& live){
       action.speed=live.speed;action.offset=live.offset;action.movement_angle=live.movement;ground_shot_[i].gravity=live.gravity;
       if(event.kind==RenaShotEventKind::model)rena_held_models[i].at(unsigned(event.slot))=event.id;
       else if(event.kind==RenaShotEventKind::activate)activate_presentation(i);
       else if(event.kind==RenaShotEventKind::melee_statistics)record_melee_attack(world,i,1);
       else if(event.kind==RenaShotEventKind::shot_statistics){++shots_attempted[i];record_shooting_attack(world,i,1);}
       else if(event.kind==RenaShotEventKind::clear_contact)contact_ledger[i].flags.fill(0);
       else if(event.kind==RenaShotEventKind::contact_capacity)contact_ledger[i].set_capacity(unsigned(event.id));
       else if(event.kind==RenaShotEventKind::strike)rena_shot_strike[i]=event.id!=0;
       else if(event.kind==RenaShotEventKind::sound)queue_sound({i,unsigned(event.id),actor.position});
       else if(event.kind==RenaShotEventKind::voice){
        const int id=event.voice_current_rounds?(damage_signed(magazines[i][0].rounds)==1?30:event.voice_other):event.id;
        queue_voice({i,unsigned(id),unsigned(event.slot),-1,-1,0x4223d0,0});
       }else if(event.kind==RenaShotEventKind::world_projectile||event.kind==RenaShotEventKind::attachment_projectile){
        GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=unsigned(event.id);shot.yaw=event.yaw;shot.pitch=event.pitch;
        shot.origin=event.kind==RenaShotEventKind::world_projectile?GroundShotOrigin::World:GroundShotOrigin::AttachmentZero;shot.attachment_slot=unsigned(event.slot);
        append_actor_projectile_request(world,i,shot,event.position,event.yaw,action.offset,muzzle,
         shot.origin==GroundShotOrigin::AttachmentZero?std::optional<int>(rena_held_models[i][shot.attachment_slot]):std::nullopt);
       }
      });
      action.speed=s.speed;action.offset=s.offset;action.movement_angle=s.movement;ground_shot_[i].gravity=s.gravity;
      effect.next_state=next.next_state;
     }else if(uses_rena(i)&&rena_mobile_shooting_state(action_binding(i).weapon,attack_state[i])){
      auto& s=rena_full_charge[i];s.weapon=action_binding(i).weapon;s.state=attack_state[i];s.phase=phase;s.frame=frame;
      //448220 shares E8/EC with the other action bodies, including its
      //450/460 burst counter. Carry the actor words across adapter boundaries.
      auto scratch=native_melee_scratch(i);
      s.scratch_e8=std::uint32_t(scratch.e8);s.scratch_ec=std::uint32_t(scratch.ec);
      if(phase==0&&frame==0)s.second_frame=0;
      const auto animation=attack_phases(i).at(phase).value;s.duration=data.animation_durations_.at(animation);
      s.hold_phase=data.animation_settings_.at(animation).hold_phase!=0;s.complete=request.animation_complete;
      s.blocked=stop_ticks[i]!=0;s.grounded=request.grounded;s.speed=action.speed;s.offset=action.offset;
      s.vertical=motion.velocity[1];s.gravity=ground_shot_[i].gravity;s.movement=motion.angles[1];s.heading=actor.heading;
      s.position=actor.position;s.target=target;s.turn_step=walk_motion_[i].step;
      s.recharge=std::uint32_t(gauge[i]);s.status7f4=status[i].duration[6];s.activated=special_gauges[i].activated0;
      s.contacts=contact_ledger[i].flags;for(unsigned v=0;v<4;++v)s.capacity[v]=damage_signed(contact_ledger[i].remaining[v]);
      auto& in=rena_mobile_resources[i];in={};in.projectile_count=unsigned(data.weapon_item->bullets.size());
      if(in.projectile_count>in.magazine_index.size())throw std::runtime_error("Rena projectile table exceeds native slots");
      for(unsigned b=0;b<in.projectile_count;++b)in.magazine_index[b]=data.weapon_item->bullets[b].magazine_index;
      in.phase_count=unsigned(attack_phases(i).size());
      if(in.phase_count>in.phase_duration.size())throw std::runtime_error("Rena shooting DAT exceeds native phases");
      for(unsigned p=0;p<in.phase_count;++p){const auto id=attack_phases(i)[p].value;
       in.phase_duration[p]=data.animation_durations_.at(id);in.phase_hold[p]=data.animation_settings_.at(id).hold_phase!=0;}
      in.special_active=special_gauges[i].active1;in.special_ready=special_gauges[i].ready1;
      auto resources=[&](){const auto& primary=magazines[i][0];const auto& secondary=magazines[i][1];
       in.primary_rounds=primary.rounds;in.secondary_rounds=secondary.rounds;
       in.primary_reload_timer=primary.reload_progress;in.secondary_reload_timer=secondary.reload_progress;
       in.primary_cooldown=primary.cooldown;in.secondary_cooldown=secondary.cooldown;
       in.primary_capacity=primary.capacity;in.secondary_capacity=secondary.capacity;
       in.primary_interval=primary.shot_interval;in.secondary_interval=secondary.shot_interval;};
      resources();std::optional<ActorSkeleton> muzzle;unsigned muzzle_phase=~0u,muzzle_frame=~0u;
      const auto next=advance_rena_mobile_shooting(s,in,[&](){return next_battle_random();},
       [&](const RenaMobileRequest& r,RenaMobileInput&){
        GroundShotEffects shot;shot.fire=true;shot.count_attack=false;shot.bullet_slot=r.slot;
        shot.yaw=r.yaw;shot.pitch=r.pitch;shot.attachment_slot=r.socket;
        shot.origin=r.kind==RenaMobileRequestKind::world?GroundShotOrigin::World:
         r.kind==RenaMobileRequestKind::bone?GroundShotOrigin::RightHand:GroundShotOrigin::AttachmentZero;
        //421100 can select a new DAT phase inside this visit. Resolve the
        // muzzle from those current counters, before its trailing increment.
        const unsigned saved_phase=attack_phase[i];const int saved_frame=elapsed[i];
        attack_phase[i]=s.phase;elapsed[i]=int(s.frame);
        if(muzzle_phase!=s.phase||muzzle_frame!=s.frame){muzzle.reset();muzzle_phase=s.phase;muzzle_frame=s.frame;}
        const bool accepted=append_actor_projectile_request(world,i,shot,r.position,
         r.kind==RenaMobileRequestKind::world?r.yaw:actor.heading+s.offset+r.yaw,s.offset,muzzle,
         r.kind==RenaMobileRequestKind::attachment?std::optional<int>(r.attachment_model):std::nullopt);
        attack_phase[i]=saved_phase;elapsed[i]=saved_frame;resources();return accepted;
       });
      if(next.dat_phase_unbacked)throw std::runtime_error("Rena shooting requested a phase absent from original DAT");
      scratch.e8=rena_full_signed(s.scratch_e8);scratch.ec=rena_full_signed(s.scratch_ec);
      scratch.known|=3u;store_native_melee_scratch(i,scratch);
      action.speed=s.speed;action.offset=s.offset;action.movement_angle=s.movement;
      motion.velocity[1]=s.vertical;ground_shot_[i].gravity=s.gravity;walk_motion_[i].step=s.turn_step;
      gauge[i]=damage_signed(s.recharge);special_gauges[i].activated0=s.activated;
      contact_ledger[i].flags=s.contacts;for(unsigned v=0;v<4;++v)contact_ledger[i].remaining[v]=std::uint32_t(s.capacity[v]);
      rena_shot_strike[i]=s.strike_active;rena_held_model_state[i]=s.state;rena_held_models[i]=next.model_slots;
      for(const auto& event:next.events){
       if(event.kind==RenaFullEventKind::state){bind_actor_animation_state(i,unsigned(event.id));pose_body_admission_replayed_[i]=true;}
       else if(event.kind==RenaFullEventKind::phase){bind_actor_animation_state(i,pose_bound_state_[i][1],unsigned(event.id));pose_body_admission_replayed_[i]=true;}
       else if(event.kind==RenaFullEventKind::activate)activate_presentation(i);
       else if(event.kind==RenaFullEventKind::sound)queue_sound({i,unsigned(event.id),actor.position});
       else if(event.kind==RenaFullEventKind::voice)queue_voice({i,unsigned(event.id),unsigned(event.priority),event.choice,-1,event.choice<0?0x4223d0u:0x422490u,unsigned(event.flag)&255u});
       else if(event.kind==RenaFullEventKind::shooting_statistics){++shots_attempted[i];record_shooting_attack(world,i,1);}
       else if(event.kind==RenaFullEventKind::melee_statistics)record_melee_attack(world,i,1);
      }
      if(attack_phase[i]!=s.phase)cursors_[i]={};
      attack_phase[i]=s.phase;elapsed[i]=int(s.frame);effect.next_state=next.next_state;
      //The helper already applied phase/counter writes, including Rena2's
      //landing phase1/frame25 followed by the same visit's clock increment.
      attack_return_[i]=true;
     }else if(uses_mion_counter(i)&&mion_mobile_melee_state(attack_state[i])){
      auto& air=air_melee_[i];air.vertical=motion.velocity[1];action.movement_angle=motion.angles[1];
      const auto next=advance_mion_mobile_melee(attack_state[i],action_binding(i).weapon,air,action,request,target[1]-actor.position[1]);effect=next;motion.velocity[1]=air.vertical;
      if(next.activate)activate_presentation(i);
      if(next.reset_capacity)contact_ledger[i].set_capacity(1);
      if((attack_state[i]==329||attack_state[i]==333)&&next.next_state<0)gauge[i]=std::min(1000,gauge[i]+(damage_signed(status[i].duration[6])>0?5:40));
     }else if(uses_mion_counter(i)&&mion_melee_state(attack_state[i])){
      action.movement_angle=motion.angles[1];const auto next=advance_mion_melee(attack_state[i],action_binding(i).weapon,action,request);effect=next;
      if(next.activate)activate_presentation(i);
      if(next.reset_capacity)contact_ledger[i].set_capacity(1);
     }else if(attack_state[i]==370||(attack_state[i]==371&&action_binding(i).character==4)){
      auto& strike=special_strike[i];action.movement_angle=motion.angles[1];
      const auto character=action_binding(i).character;
      if(character==8||character==9)action.vertical=motion.velocity[1];
      const auto next=attack_state[i]==371?advance_roster_grab_followup(strike,action,request):
       advance_roster_special_strike(character,action_binding(i).weapon,strike,action,request);
      if(character==8||character==9||attack_state[i]==371)motion.velocity[1]=action.vertical;
      effect=next.action;
      if(next.capture_requested&&actor.relationships.secondary_target<4&&
         capture_actor(world,i,186,0,{},wall)){
       stagger[i].invincible=30;effect.next_state=371;
      }
      if(attack_state[i]==371){
       stagger[i].invincible=3;
       if(next.release_requested)release_held_actor(world,i,{135,198,0,1,0.f,0.f,4000.f},wall);
      }
      if(next.projectile_slot>=0){
       GroundShotEffects shot;shot.fire=true;shot.bullet_slot=unsigned(next.projectile_slot);
       shot.origin=GroundShotOrigin::World;shot.count_attack=false;
       const float angle=actor.heading+action.offset;
       const std::array<float,3> origin{actor.position[0]+legacy_trig(angle,false)*next.projectile_forward,
        actor.position[1]+next.projectile_height,actor.position[2]+legacy_trig(angle,true)*next.projectile_forward};
       shot_requests.push_back({i,shot,origin,angle,actor.relationships.target});
       ++shots_spawn_requested[i];
      }
      if(strike.hold_clock)attack_return_[i]=true;
      if(strike.magazine_gate>=0)for(auto& magazine:magazines[i])magazine.flags=(magazine.flags&0xffffff00u)|unsigned(strike.magazine_gate);
      if(next.activate)activate_presentation(i); //422900 aec8 signal, separate from attack statistics
     }else if(battle_ground_dash_state(attack_state[i])){
      auto& dash=ground_dash_[i];dash.state=attack_state[i];dash.phase=phase;dash.frame=frame;
      dash.complete=request.animation_complete;dash.grounded=actor.grounded;dash.gauge=gauge[i];dash.x=inputs[i].x;dash.z=inputs[i].z;
      dash.speed=action.speed;dash.offset=action.offset;dash.movement=motion.angles[1];dash.height=actor.floor_distance;dash.turn_step=walk_motion_[i].step;
      const auto next=advance_battle_ground_dash(dash,attack_state[i]==20?roster_forward_dash_tuning(action_binding(i).character,action_binding(i).weapon,special_gauges[i].active0||special_gauges[i].active1||special_gauges[i].active2):(attack_state[i]==27||attack_state[i]==28)?roster_back_dash_tuning(action_binding(i).character,action_binding(i).weapon,special_gauges[i].active0||special_gauges[i].active1||special_gauges[i].active2):(attack_state[i]==23||attack_state[i]==24)?roster_side_dash_tuning(action_binding(i).character,action_binding(i).weapon,attack_state[i],special_gauges[i].active0||special_gauges[i].active1||special_gauges[i].active2):uses_rena(i)?rena_ground_dash_tuning(action_binding(i).weapon):uses_mion_counter(i)?mion_ground_dash_tuning(action_binding(i).weapon):BattleGroundDashTuning{});ground_dash_effects[i]=next;
      walk_motion_[i].step=dash.turn_step;
      statistics[i].step_starts+=next.step_count;
      gauge[i]=dash.gauge;action.speed=dash.speed;action.offset=dash.offset;action.movement_angle=dash.movement;
      effect.next_state=next.state;effect.next_phase=next.phase;effect.effect=next.effect;
      if(next.hold_clock)attack_return_[i]=true;
      elapsed[i]+=int(next.extra_ticks);
    }else if(keiichi_shooting_state(attack_state[i])||
               roster_secondary_charge_state(action_binding(i).character,action_binding(i).weapon,attack_state[i])||
               roster_throw_followup_state(action_binding(i).character,action_binding(i).weapon,attack_state[i])||
               ((attack_state[i]==303||attack_state[i]==335)&&action_binding(i).character==11&&action_binding(i).weapon==0)||
               (attack_state[i]==420&&action_binding(i).character==11&&action_binding(i).weapon<2)||
               (attack_state[i]>=410&&attack_state[i]<=413&&action_binding(i).character==6&&action_binding(i).weapon==0)||
               (action_binding(i).policy==BattleActionPolicy::data_driven_preview&&
                (attack_state[i]==361||attack_state[i]==362))||
               (uses_mion_counter(i)&&mion_charge_shooting_state(attack_state[i]))){
      const float elevation=battle_target_elevation(actor.position,target);
      GroundShotEffects shot;std::vector<GroundShotEffects> charge_requests;int shot_frame_delta=1;
      bool native_shot_callbacks_done=false;
      if(action_binding(i).character==15&&action_binding(i).weapon==0&&natsumi_charge_state(attack_state[i])){
       action.movement_angle=motion.angles[1];auto& air=air_melee_[i];
       NatsumiChargeMotion state{action.speed,action.offset,action.movement_angle,motion.velocity[1],ground_shot_[i].gravity,air.pitch,air.pivot};
       NatsumiChargeInput in;in.state=attack_state[i];in.phase=phase;in.frame=frame;
       in.complete=request.animation_complete;in.grounded=request.grounded;in.contact=request.contact;
       in.boosted=special_gauges[i].active1&&special_gauges[i].ready1!=0;
       in.special_melee_voice=request.voice_flags[2]==1;in.distance_squared=request.distance_squared;
       in.target_elevation=elevation;in.heading=actor.heading;
       const auto next=advance_natsumi_charge(roster_native_scratch[i],in,state,[&](){return next_battle_random();});
       shot.next_state=next.next_state;effect.next_phase=next.next_phase;shot_frame_delta=next.frame_delta;
       std::optional<ActorSkeleton> muzzle;
       for(const auto& event:next.events){
        switch(event.kind){
         case NatsumiChargeEventKind::ClearContacts:contact_ledger[i].clear_flags();break;
         case NatsumiChargeEventKind::Capacity:contact_ledger[i].set_capacity(unsigned(event.value));break;
         case NatsumiChargeEventKind::Activate:activate_presentation(i);break;
         case NatsumiChargeEventKind::AttackStatistics:record_melee_attack(world,i,unsigned(event.value));break;
         case NatsumiChargeEventKind::Effect:queue_sound({i,unsigned(event.value),actor.position});break;
         case NatsumiChargeEventKind::Voice:queue_voice({i,unsigned(event.value),10,-1,-1,0x4223d0,0});break;
         case NatsumiChargeEventKind::Projectile:{
          const auto& spawn=event.projectile;auto p=actor.position;
          const float heading=actor.heading+event.offset;
          if(spawn.origin==GroundShotOrigin::World)p={actor.position[0]+legacy_trig(heading,false)*100,
           actor.position[1]+80,actor.position[2]+legacy_trig(heading,true)*100};
          std::optional<int> model;if(spawn.origin==GroundShotOrigin::AttachmentZero)model=selected_held_weapon_models(i)[0];
          append_actor_projectile_request(world,i,spawn,p,heading+spawn.yaw,event.offset,muzzle,model,event.model_pitch,event.pivot);
          break;
         }
        }
       }
       action.speed=state.speed;action.offset=state.offset;action.movement_angle=state.movement;
       motion.velocity[1]=state.vertical;ground_shot_[i].gravity=state.gravity;air.pitch=state.pitch;air.pivot=state.pivot;
       action.contact_seen=roster_native_scratch[i].ec;
       native_shot_callbacks_done=true;
      }else if(uses_mion_counter(i)&&mion_charge_shooting_state(attack_state[i])){
       action.movement_angle=motion.angles[1];auto& state=mion_charge_shots[i];const auto& special=special_gauges[i];
       auto rng=[&](){return next_battle_random();};const bool boosted=special.active1&&special.ready1!=0;
       MionChargeEffects next;unsigned attack_calls=0;const bool full=attack_state[i]==350||attack_state[i]==360||attack_state[i]==361;
       if(full){
        auto& full_state=mion_full_charges[i];
        if(attack_state[i]==361){next=advance_mion_charge_landing(state,request.animation_complete,action.speed,action.movement_angle,motion.velocity[1]);full_state.gravity=state.gravity;}
        else {auto value=advance_mion_full_charge(full_state,action_binding(i).weapon,attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1],elevation,damage_signed(magazines[i][0].rounds),shoot_held[i],rng);mion_full_charge_effects[i]=value;next=value;attack_calls=value.statistics;}
        state.gravity=full_state.gravity;
       }else {
       next=attack_state[i]==469?advance_mion_charge_landing(state,request.animation_complete,action.speed,action.movement_angle,motion.velocity[1]):attack_state[i]==460?
        advance_mion_air_charge(state,action_binding(i).weapon,phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1],elevation,damage_signed(magazines[i][1].rounds),boosted,rng):
        advance_mion_ground_charge(state,action_binding(i).weapon,attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,elevation,damage_signed(magazines[i][1].rounds),boosted,rng);
        attack_calls=unsigned(next.bullets.size());
       }
       mion_charge_effects[i]=next;shot.next_state=next.next_state;effect.next_phase=next.next_phase;shot.started=next.activate;shot.voice=next.voice;
       if(full&&!mion_full_charge_effects[i].voice_arguments.empty()){
        const auto& args=mion_full_charge_effects[i].voice_arguments;
        if(mion_full_charge_effects[i].voice_service==3&&args.size()>=3){
         shot.voice_choice=args[1];shot.voice_priority=unsigned(std::max(0,args[2]));
        }else if(mion_full_charge_effects[i].voice_service==2&&args.size()>=2)
         shot.voice_priority=unsigned(std::max(0,args[1]));
       }
       for(std::size_t sound=1;sound<next.sounds.size();++sound)
        if(next.sounds[sound]>=0)
         queue_sound({i,unsigned(next.sounds[sound]),actor.position});
       shot.effect=next.sounds.empty()?-1:next.sounds.front();shot.fire=!next.bullets.empty();shot.attack_calls=attack_calls;shot.origin=GroundShotOrigin::AttachmentZero;
       if(full){
        shot.count_attack=false;shots_attempted[i]+=attack_calls;record_shooting_attack(world,i,attack_calls);
       }
       for(const auto& bullet:next.bullets){auto request=shot;request.bullet_slot=bullet.slot;request.yaw=bullet.yaw;request.pitch=bullet.pitch;request.attachment_model=bullet.model;charge_requests.push_back(request);}
       if(next.activate)activate_presentation(i);if(next.hold_clock)attack_return_[i]=true;
       if(next.recover_gauge){walk_motion_[i].step=0;gauge[i]=std::min(1000,gauge[i]+(damage_signed(status[i].duration[6])>0?5:40));}
       ground_shot_[i].gravity=state.gravity;
      }else if(uses_mion_counter(i)&&mion_mobile_ground_shot_state(attack_state[i])){
       action.movement_angle=motion.angles[1];auto& state=mion_ground_shots[i];const auto& special=special_gauges[i];
       const auto next=advance_mion_mobile_ground_shot(state,action_binding(i).weapon,attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,elevation,damage_signed(magazines[i][0].rounds),int(shoot_released[i]),inputs[i].x,inputs[i].z,special.active1&&special.ready1!=0);
       shot.next_state=next.next_state;shot.started=next.activate;shot.fire=next.fire;shot.effect=next.sound;shot.voice=next.voice;shot.bullet_slot=next.bullet_slot;shot.pitch=next.pitch;
       shot.origin=GroundShotOrigin::AttachmentZero;shot.paired_attachments=next.shot_count==2;shot.attack_calls=next.shot_count;shot.attachment_model=next.attachment_model;
       if(next.activate)activate_presentation(i);if(next.hold_clock)attack_return_[i]=true;ground_shot_[i].gravity=state.gravity;
      }else if(uses_mion_counter(i)&&(attack_state[i]==402||attack_state[i]==403)){
       action.movement_angle=motion.angles[1];auto& state=mion_ground_shots[i];const auto& special=special_gauges[i];
       const auto next=advance_mion_air_shot(state,action_binding(i).weapon,attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1],elevation,damage_signed(magazines[i][0].rounds),special.active1&&special.ready1!=0);
       shot.next_state=next.next_state;shot.started=next.activate;shot.fire=next.fire;shot.effect=next.sound;shot.voice=next.voice;
       shot.bullet_slot=next.bullet_slot;shot.pitch=next.pitch;shot.origin=GroundShotOrigin::AttachmentZero;shot.paired_attachments=next.shot_count==2;shot.attack_calls=next.shot_count;
       effect.next_phase=next.next_phase;if(next.activate)activate_presentation(i);if(next.hold_clock)attack_return_[i]=true;
       if(next.recover_gauge){walk_motion_[i].step=0;gauge[i]=std::min(1000,gauge[i]+(damage_signed(status[i].duration[6])>0?5:40));}
       ground_shot_[i].gravity=state.gravity;
      }else if(uses_mion_counter(i)){
       action.movement_angle=motion.angles[1];auto& state=mion_ground_shots[i];const auto& special=special_gauges[i];
       const auto next=advance_mion_ground_shot(state,action_binding(i).weapon,phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,elevation,damage_signed(magazines[i][0].rounds),int(shoot_released[i]),special.active1&&special.ready1!=0);
       shot.next_state=next.next_state;shot.started=next.activate;shot.fire=next.fire;shot.effect=next.sound;shot.voice=next.voice;
       shot.bullet_slot=next.bullet_slot;shot.pitch=float(state.pitch);shot.origin=GroundShotOrigin::AttachmentZero;shot.attachment_slot=next.attachment;
       effect.next_phase=next.next_phase;if(next.activate)activate_presentation(i);
       if(next.rewrite_frame>=0)elapsed[i]=next.rewrite_frame;
       if(next.hold_clock)attack_return_[i]=true;
       ground_shot_[i].gravity=state.gravity;
      }else if((attack_state[i]==303||attack_state[i]==335)&&action_binding(i).character==11&&action_binding(i).weapon==0){
       shot=advance_roster_followup_shot303(11,0,frame,request.animation_complete,
        request.grounded,action.speed,action.offset,elevation);
       if(shot.started)activate_presentation(i);
      }else if(attack_state[i]==420&&action_binding(i).character==11&&action_binding(i).weapon<2){
       shot=advance_roster_ground_shot_followup420(11,action_binding(i).weapon,
        phase,frame,request.animation_complete,request.grounded,
        special_gauges[i].active1&&special_gauges[i].ready1!=0,
        unsigned(std::max(0,damage_signed(magazines[i][0].rounds))),elevation,
        action.speed,action.offset,charge_requests);
       if(shot.started)activate_presentation(i);
      }else if(attack_state[i]>=410&&attack_state[i]<=413&&
                action_binding(i).character==6&&action_binding(i).weapon==0){
       action.movement_angle=motion.angles[1];
       const auto& special=special_gauges[i];
       shot=advance_roster_ground_shot_followup410(6,0,attack_state[i],phase,frame,
        request.animation_complete,request.grounded,special.active1&&special.ready1!=0,
        unsigned(std::max(0,damage_signed(magazines[i][0].rounds))),
        action.speed,action.offset,action.movement_angle);
       if(shot.started)activate_presentation(i);
      }else if(attack_state[i]==400&&action_binding(i).policy==BattleActionPolicy::data_driven_preview){
       int next_phase=-1;
       action.movement_angle=motion.angles[1];
       if(phase==0&&frame==0){roster_shot_trigger_[i]=0;
        if(action_binding(i).character==5&&action_binding(i).weapon==2)projectile_owner_signal_[i]=0;}
       shot=advance_roster_ground_shot400(action_binding(i).character,action_binding(i).weapon,phase,frame,
        request.animation_complete,request.grounded,charge_requests,next_phase,roster_shot_trigger_[i],
        special_gauges[i].active1&&special_gauges[i].ready1!=0,elevation);
       effect.next_phase=next_phase;
       if(next_phase>=0||shot.next_state>=0)roster_shot_trigger_[i]=0;
       if(action_binding(i).character==5&&action_binding(i).weapon==2&&
          (request.animation_complete||!request.grounded))projectile_owner_signal_[i]=0;
       if(!request.animation_complete&&request.grounded){
        const auto& binding=action_binding(i);
        shot_frame_delta=advance_roster_ground_shot400_motion(binding.character,binding.weapon,
         phase,frame,action.speed,action.offset,action.movement_angle);
        shot_frame_delta=advance_roster_ground_shot400_clock(binding.character,binding.weapon,phase,frame,
         damage_signed(magazines[i][0].rounds)>0?unsigned(damage_signed(magazines[i][0].rounds)):0u,
         roster_shot_clock_[i],shot,charge_requests,shot_frame_delta);
        }
       }else if(attack_state[i]==401&&action_binding(i).policy==BattleActionPolicy::data_driven_preview){
        int next_phase=-1;
        action.movement_angle=motion.angles[1];
        const auto& binding=action_binding(i);
        shot=advance_roster_shot401(binding.character,binding.weapon,phase,frame,
         request.animation_complete,request.grounded,charge_requests,next_phase,
         special_gauges[i].active1&&special_gauges[i].ready1!=0,elevation);
        effect.next_phase=next_phase;
        if(shot.next_state<0&&next_phase<0){
         shot_frame_delta=advance_roster_shot401_motion(binding.character,binding.weapon,
         phase,frame,action.speed,action.offset,action.movement_angle);
         shot_frame_delta=advance_roster_shot401_clock(binding.character,binding.weapon,phase,frame,
          damage_signed(magazines[i][0].rounds)>0?unsigned(damage_signed(magazines[i][0].rounds)):0u,
          roster_shot401_clock_[i],shot,charge_requests,shot_frame_delta,
          special_gauges[i].active1&&special_gauges[i].ready1!=0,elevation);
        }
       }else if(attack_state[i]>=404&&attack_state[i]<=407&&
                 action_binding(i).policy==BattleActionPolicy::data_driven_preview){
        int next_phase=-1;
        action.movement_angle=motion.angles[1];
        const auto& binding=action_binding(i);
        shot=advance_roster_directional_shot(binding.character,binding.weapon,
         attack_state[i],phase,frame,unsigned(std::max(0,damage_signed(magazines[i][0].rounds))),
         request.animation_complete,request.grounded,
         roster_directional_clock_[i],charge_requests,next_phase,shot_frame_delta,
         action.speed,action.offset,action.movement_angle);
        effect.next_phase=next_phase;
       }else if((attack_state[i]==402||attack_state[i]==408)&&
                 action_binding(i).policy==BattleActionPolicy::data_driven_preview){
        int next_phase=-1;
        action.movement_angle=motion.angles[1];
        const auto& binding=action_binding(i);
        shot=advance_roster_air_shot(binding.character,binding.weapon,attack_state[i],
         phase,frame,unsigned(std::max(0,damage_signed(magazines[i][0].rounds))),
         request.animation_complete,request.grounded,roster_air_shot_clock_[i],
         charge_requests,next_phase,shot_frame_delta,action.speed,action.offset,
         action.movement_angle,motion.velocity[1],ground_shot_[i].gravity,
         roster_shot_trigger_[i],special_gauges[i].active1&&special_gauges[i].ready1!=0);
        if(binding.character==5&&binding.weapon==2&&attack_state[i]==402&&phase==0&&frame==0){
         roster_shot_trigger_[i]=0;projectile_owner_signal_[i]=0;
        }
        if(next_phase>=0||shot.next_state>=0)roster_shot_trigger_[i]=0;
       effect.next_phase=next_phase;
       }else if((attack_state[i]==450||attack_state[i]==460)&&
                 action_binding(i).policy==BattleActionPolicy::data_driven_preview){
        int next_phase=-1;
        action.movement_angle=motion.angles[1];
        const auto& binding=action_binding(i);
        if(phase==0&&frame==0){roster_charge_trigger_[i]=0;
         if(binding.character==5&&binding.weapon==0)projectile_owner_signal_[i]=0;}
        shot=advance_roster_charge_shot(binding.character,binding.weapon,attack_state[i],
         phase,frame,unsigned(std::max(0,damage_signed(magazines[i][0].rounds))),
         unsigned(std::max(0,damage_signed(magazines[i][1].rounds))),
         request.animation_complete,request.grounded,roster_charge_shot_clock_[i],
         charge_requests,next_phase,shot_frame_delta,action.speed,action.offset,
         action.movement_angle,motion.velocity[1],ground_shot_[i].gravity,roster_charge_trigger_[i],
         melee_held_[i],melee_released_[i]);
        effect.next_phase=next_phase;
       if(binding.character==8&&binding.weapon==1&&phase==2&&
          (contact_ledger[i].combined()&1)&&!request.animation_complete&&shot.next_state<0&&
          capture_actor(world,i,190,0,{},wall)){
        shot={};shot.attack_calls=0;shot.count_attack=false;
        charge_requests.clear();effect.next_phase=-1;
        shot.next_state=attack_state[i]==450?451:461;
       }
       if(next_phase>=0||shot.next_state>=0)roster_charge_trigger_[i]=0;
       }else if(roster_throw_followup_state(action_binding(i).character,
                   action_binding(i).weapon,attack_state[i])){
        action.movement_angle=motion.angles[1];
        const auto next=advance_roster_throw_followup(action_binding(i).character,
         action_binding(i).weapon,attack_state[i],phase,frame,
         request.animation_complete,request.grounded,action.speed,action.offset,
         action.movement_angle,motion.velocity[1],ground_shot_[i].gravity);
        shot=next.shot;shot_frame_delta=next.frame_delta;
        effect.next_phase=next.next_phase;
        if(next.capture_state>=0)capture_actor(world,i,std::int16_t(next.capture_state),0,{},wall);
        if(next.victim_state>=0&&target_availability[i].paired_actor<4)
         enter_throw_action(target_availability[i].paired_actor,unsigned(next.victim_state));
        if(next.bind_prop2)attachment_bones[i]="Bip01_Prop2";
        if(next.damage_state>=0)damage_held_actor(world,i,std::int16_t(next.damage_state),
         std::int16_t(next.damage),1,"Bip01_Prop2",wall);
        if(next.release)release_held_actor(world,i,next.release_data,wall);
       }else if(roster_secondary_charge_state(action_binding(i).character,
                   action_binding(i).weapon,attack_state[i])){
        action.movement_angle=motion.angles[1];
        shot=advance_roster_secondary_charge(action_binding(i).character,
         action_binding(i).weapon,attack_state[i],frame,request.animation_complete,
         request.grounded,special_gauges[i].active1&&special_gauges[i].ready1!=0,
         shot_frame_delta,action.speed,action.offset,action.movement_angle,
         motion.velocity[1],ground_shot_[i].gravity);
       }else if((attack_state[i]==350||attack_state[i]==360)&&
                 action_binding(i).policy==BattleActionPolicy::data_driven_preview){
        int next_phase=-1;
        action.movement_angle=motion.angles[1];
        const auto& binding=action_binding(i);
        // 49d890 holds actor+f4 after frame30/40; its frame0 clears the
        // previous action. Projectile scripts read the prior actor update.
        if(binding.character==4&&binding.weapon==2)
         {if(frame==0)owner_orbit_command_[i]=0;
          else if(frame==30)owner_orbit_command_[i]=1;
         else if(frame==40)owner_orbit_command_[i]=2;}
        // 0053ed0d/0053ee4b notify existing fields after the original early
        // completion/ground exits. Scripts consume this on the next visit.
        if(binding.character==7&&binding.weapon==1&&!request.animation_complete&&
           frame==0&&(attack_state[i]==360||(request.grounded&&phase==0)))
         projectile_owner_field_exit[i]=1;
        shot=advance_roster_full_shot(binding.character,binding.weapon,attack_state[i],
         phase,frame,unsigned(std::max(0,damage_signed(magazines[i][0].rounds))),
         request.animation_complete,request.grounded,
         roster_full_shot_clock_[i],charge_requests,next_phase,shot_frame_delta,
         action.speed,action.offset,action.movement_angle,motion.velocity[1],
         ground_shot_[i].gravity,shoot_held[i],shoot_released[i],
         melee_held_[i],melee_released_[i]);
       effect.next_phase=next_phase;
       if(((binding.character==8&&binding.weapon==1&&phase==2)||
           (binding.character==15&&binding.weapon==0&&phase==1))&&
          (contact_ledger[i].combined()&1)&&!request.animation_complete&&shot.next_state<0&&
          capture_actor(world,i,190,1,{},wall)){
        shot={};shot.attack_calls=0;shot.count_attack=false;
        charge_requests.clear();effect.next_phase=-1;
        if(binding.character==15){attachment_bones[i]="Bip01_Prop2";
         shot.voice=0;}
        shot.next_state=binding.character==8&&attack_state[i]==360?361:351;
       }
       }else if((attack_state[i]==361||attack_state[i]==362)&&
                 action_binding(i).policy==BattleActionPolicy::data_driven_preview){
        action.movement_angle=motion.angles[1];
        const auto& binding=action_binding(i);
        shot=advance_roster_full_shot_followup(binding.character,binding.weapon,
         attack_state[i],frame,request.animation_complete,request.grounded,
         shot_frame_delta,action.speed,action.movement_angle,motion.velocity[1],
         ground_shot_[i].gravity);
      }else if(keiichi_walk_shot_state(attack_state[i])){
       action.movement_angle=motion.angles[1];
       if(action_binding(i).policy==BattleActionPolicy::data_driven_preview&&
          roster_walk_shot_recovered(action_binding(i).character,action_binding(i).weapon))
        shot=advance_roster_walk_shot(action_binding(i).character,action_binding(i).weapon,
         attack_state[i],walk_shot_[i],phase,frame,request.animation_complete,request.grounded,
         inputs[i].x,inputs[i].z,action.speed,action.offset,action.movement_angle,elevation,
         magazines[i][0].rounds,special_gauges[i].active1&&special_gauges[i].ready1!=0,
         random_,charge_requests);
       else shot=advance_keiichi_walk_shot(walk_shot_[i],attack_state[i],phase,frame,
        request.animation_complete,request.grounded,inputs[i].x,inputs[i].z,action.speed,
        action.offset,action.movement_angle,elevation,magazines[i][0].rounds,false);
      }else if(attack_state[i]==403||attack_state[i]==409||attack_state[i]==469){
       if(request.animation_complete)shot.next_state=0;
       else {ground_shot_[i].gravity=0;motion.velocity[1]=0;action.speed=action.movement_angle=0;gauge[i]=std::min(1000,gauge[i]+(damage_signed(status[i].duration[6])>0?5:40));}
      }else if(attack_state[i]==350||attack_state[i]==360){
       action.movement_angle=motion.angles[1];
       if(action_binding(i).weapon==0)shot=advance_bat_full_charge_shot(ground_shot_[i],attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1],elevation);
       else if(action_binding(i).weapon==1)shot=advance_iron_full_charge_shot(ground_shot_[i],attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1]);
       else shot=advance_shovel_full_charge_shot(ground_shot_[i],attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1]);
       if(shot.hold_clock)attack_return_[i]=true;
      }else if(attack_state[i]==450||attack_state[i]==460){
       action.movement_angle=motion.angles[1];
       if(action_binding(i).weapon==0)shot=advance_bat_charge_shot(ground_shot_[i],attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1],elevation,magazines[i][1].rounds,false);
       else shot=advance_lobbed_charge_shot(ground_shot_[i],action_binding(i).weapon,attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,motion.velocity[1],elevation,float(request.distance_squared),magazines[i][1].rounds,false);
       if(shot.hold_clock)attack_return_[i]=true;
      }else if(attack_state[i]==408){
       action.movement_angle=motion.angles[1];
       shot=advance_keiichi_air_dash_shot(ground_shot_[i],phase,frame,request.animation_complete,request.grounded,action.offset,action.movement_angle,motion.velocity[1],elevation,magazines[i][0].rounds,false);
      }else if(attack_state[i]==402){
       action.movement_angle=motion.angles[1];
       shot=advance_keiichi_air_shot(ground_shot_[i],action_binding(i).weapon,phase,frame,request.animation_complete,request.grounded,action.offset,action.movement_angle,motion.velocity[1],elevation,magazines[i][0].rounds,false,random_);
      }else if(attack_state[i]>=404&&attack_state[i]<=407){
       action.movement_angle=motion.angles[1];
       shot=advance_keiichi_directional_shot(ground_shot_[i],action_binding(i).weapon,attack_state[i],phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,elevation,magazines[i][0].rounds,false);
      }else if(attack_state[i]==401){
       action.movement_angle=motion.angles[1];
       shot=advance_keiichi_dash_shot(ground_shot_[i],action_binding(i).weapon,phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,action.movement_angle,elevation,magazines[i][0].rounds,false,random_);
      }else shot=advance_keiichi_ground_shot(ground_shot_[i],action_binding(i).weapon,phase,frame,request.animation_complete,request.grounded,action.speed,action.offset,elevation,magazines[i][0].rounds,false,random_);
      if(action_binding(i).character==3&&action_binding(i).weapon==1&&
         (attack_state[i]==400||attack_state[i]==402)&&request.animation_complete&&shot.next_state==0)satoko_mine_clock[i]=120;
      if(action_binding(i).character==10&&action_binding(i).weapon==1&&
         (attack_state[i]==350||attack_state[i]==360)&&!request.animation_complete&&
         (attack_state[i]==360||request.grounded)){
       if(phase==0&&frame==0)roster_weapon_visual_ec[i]=0;
       // 57f600's frame30 loop resets EC, emits five pairs and leaves EC=5.
       if(frame==30)roster_weapon_visual_ec[i]=5;
      }
      ground_shot_effects[i]=shot;effect.next_state=shot.next_state;
      // The original Kasai handlers 005b0990/005b9680/005c3350 request
      // shotC (29) at priority 20; the other direct shot27..30 calls use 10.
      if(action_binding(i).character==12&&shot.voice==29)shot.voice_priority=20;
      std::optional<ActorSkeleton> muzzle_pose;
      const auto emit_shot=[&](const GroundShotEffects& spawn_shot){
        auto p=actor.position;
        if(spawn_shot.origin==GroundShotOrigin::World){
         const float angle=actor.heading+(spawn_shot.world_actor_heading_only?0.f:action.offset+spawn_shot.yaw)+spawn_shot.world_yaw;
         p={
          actor.position[0]+legacy_trig(angle,false)*spawn_shot.world_forward_x-legacy_trig(angle,true)*spawn_shot.world_lateral,
          actor.position[1]+spawn_shot.origin_height,
          actor.position[2]+legacy_trig(angle,true)*spawn_shot.world_forward_z+legacy_trig(angle,false)*
           (spawn_shot.world_lateral_z_override?spawn_shot.world_lateral_z:spawn_shot.world_lateral)};
        }
        std::optional<int> model;
        if(spawn_shot.origin==GroundShotOrigin::AttachmentZero&&spawn_shot.attachment_slot<2)
         model=spawn_shot.attachment_model>=0?spawn_shot.attachment_model:selected_held_weapon_models(i)[spawn_shot.attachment_slot];
        return append_actor_projectile_request(world,i,spawn_shot,p,
         actor.heading+action.offset+spawn_shot.yaw,action.offset,muzzle_pose,model);
      };
      const auto callback=[&](RosterShot400Kind kind,int value,bool native_order){
       ShotCallbackVisit visit{i,kind,value,magazines[i][0].rounds,0,shots_attempted[i],0,false,native_order};
       switch(kind){
        case RosterShot400Kind::Voice:
         queue_voice({i,unsigned(value),action_binding(i).character==12&&value==29?20u:shot.voice_priority,shot.voice_choice,-1,action_binding(i).character==8&&action_binding(i).weapon==1&&attack_state[i]==451&&value==33?0x422490u:0x4223d0u,0});break;
        case RosterShot400Kind::Effect:queue_sound({i,unsigned(value),actor.position});break;
        case RosterShot400Kind::AttackCount:
         shots_attempted[i]+=unsigned(value);record_shooting_attack(world,i,unsigned(value));break;
        case RosterShot400Kind::Attachment:case RosterShot400Kind::Hand:case RosterShot400Kind::World:
         visit.value=int(charge_requests.at(unsigned(value)).bullet_slot);
         visit.admitted=emit_shot(charge_requests[unsigned(value)]);break;
        default:break;
       }
       visit.primary_after=magazines[i][0].rounds;visit.attacks_after=shots_attempted[i];shot_callback_visits.push_back(visit);
      };
      const bool replayed=native_shot_callbacks_done||replay_roster_shot_callbacks(shot,charge_requests,
       [&](RosterShot400Kind kind,int value){callback(kind,value,true);});
      if(!replayed){
       if(shot.voice>=0)callback(RosterShot400Kind::Voice,shot.voice,false);
       if(shot.effect>=0)callback(RosterShot400Kind::Effect,shot.effect,false);
       if(shot.fire){
        if(shot.count_attack)callback(RosterShot400Kind::AttackCount,int(shot.attack_calls),false);
        // Iron's auxiliary9 precedes main2 and has no extra attack callback.
        for(unsigned n=0;n<(charge_requests.empty()?(shot.auxiliary_slot>=0||shot.paired_attachments?2u:1u):unsigned(charge_requests.size()));++n){
         auto projectile=charge_requests.empty()?shot:charge_requests[n];
         if(shot.auxiliary_slot>=0&&n==0){projectile.bullet_slot=unsigned(shot.auxiliary_slot);projectile.count_attack=false;}
         if(shot.paired_attachments)projectile.attachment_slot=n;
         emit_shot(projectile);
        }
       }
      }
       if((attack_state[i]==400||attack_state[i]==401||attack_state[i]==402||attack_state[i]==408||
           attack_state[i]>=404&&attack_state[i]<=407||attack_state[i]==350||attack_state[i]==360||
           attack_state[i]==361||attack_state[i]==362||
           attack_state[i]==450||attack_state[i]==460||
           roster_secondary_charge_state(action_binding(i).character,
            action_binding(i).weapon,attack_state[i])||
           roster_throw_followup_state(action_binding(i).character,
            action_binding(i).weapon,attack_state[i]))&&
          action_binding(i).policy==BattleActionPolicy::data_driven_preview&&
         shot.next_state<0&&effect.next_phase<0){
       if(shot_frame_delta==0)attack_return_[i]=true;
       else elapsed[i]+=shot_frame_delta-1;
      }
     }else if(attack_state[i]==332){
      auto& air=air_melee_[i];air.vertical=motion.velocity[1];
      const auto& binding=action_binding(i);
      BattleDashTargetPoints target_points;const BattleDashTargetPoints* target_points_ptr=nullptr;
      if(binding.character==4&&binding.weapon==2){
       target_points.origin=actor.position;
       const auto points=body_contact_points(world,actor.relationships.target);
       for(unsigned axis=0;axis<3;++axis)target_points.target_spine[axis]=points[1][axis];
       target_points_ptr=&target_points;
      }
      const auto next=advance_battle_dash_melee(binding.character,binding.weapon,air,action,request,target[1]-actor.position[1],native_extra_yaw[i],target_points_ptr);
      dash_melee_effects[i].action=next;dash_melee_effects[i].disable_contact=next.disable_contact;dash_melee_effects[i].sound_request=next.sound_request;effect=next;motion.velocity[1]=air.vertical;
      if(next.disable_contact)contact_ledger[i].set_capacity(0);
     }else if((attack_state[i]==334||attack_state[i]==339)&&uses_recovered_actor(i)){
      auto& air=air_melee_[i];air.vertical=motion.velocity[1];
      auto& turn_step=walk_motion_[i].step;
      const auto next=advance_battle_dash_followup(action_binding(i).character,action_binding(i).weapon,air,action,request,gauge[i],turn_step,damage_signed(status[i].duration[6])>0,attack_state[i]);
      dash_followup_effects[i]=next;static_cast<KeiichiAttack300Effects&>(effect)=next;motion.velocity[1]=air.vertical;
      if(next.reset_capacity)contact_ledger[i].set_capacity(1);
     }else if(attack_state[i]==333){
      const auto& binding=action_binding(i);
      BattleDashRecovery recovery{motion.velocity[1],air_melee_[i].gravity,action.speed,action.movement_angle,0,gauge[i]};
      effect.next_state=advance_battle_dash_recovery(recovery,binding.character,binding.weapon,request.animation_complete,damage_signed(status[i].duration[6])>0);
      motion.velocity[1]=recovery.vertical;air_melee_[i].gravity=recovery.gravity;action.speed=recovery.speed;action.movement_angle=recovery.movement_angle;gauge[i]=recovery.gauge;
     }else if(attack_state[i]==336&&action_binding(i).character==11){
      action.vertical=motion.velocity[1];action.movement_angle=motion.angles[1];
      effect=advance_roster_dash_followup336(11,action_binding(i).weapon,action,request);
      motion.velocity[1]=action.vertical;air_melee_[i].gravity=action.gravity;
     }else if(attack_state[i]==341&&uses_recovered_actor(i)){
      action.vertical=motion.velocity[1];action.movement_angle=motion.angles[1];
      action.gravity=air_melee_[i].gravity;
      effect=advance_roster_state341(action_binding(i).character,action_binding(i).weapon,action,request);
      motion.velocity[1]=action.vertical;air_melee_[i].gravity=action.gravity;
     }else if(attack_state[i]==329){
      if(request.animation_complete)effect.next_state=0;
      else {air_melee_[i].gravity=0;
       // 4dee70 (character 9, weapon 0) leaves the landing vertical velocity
       // intact; the other 45 actor handlers clear it in state 329.
       if(action_binding(i).character!=9||action_binding(i).weapon!=0)motion.velocity[1]=0;
       action.speed=action.movement_angle=0;gauge[i]=std::min(1000,gauge[i]+(damage_signed(status[i].duration[6])>0?5:40));}
     }else if(action_binding(i).character==5&&action_binding(i).weapon==2&&
               attack_state[i]>=420&&attack_state[i]<=423){
      Item36FollowupState follow{attack_state[i],phase,frame,request.animation_complete,
       request.grounded,action.speed,action.offset,motion.angles[1],motion.velocity[1],ground_shot_[i].gravity};
      const auto next=advance_item36_followup(follow);
      action.speed=follow.speed;
      ground_shot_[i].gravity=follow.gravity;
      effect.next_state=next.next_state;effect.effect=next.effect;
      effect.voice=next.voice;effect.voice_argument=next.voice_argument;
      if(next.shooting_attacks){
       shots_attempted[i]+=next.shooting_attacks;
       record_shooting_attack(world,i,next.shooting_attacks);
      }
     }else if(attack_state[i]==300)effect=action_binding(i).policy==BattleActionPolicy::data_driven_preview?advance_roster_ground_melee(action_binding(i).character,action_binding(i).weapon,action,request):advance_keiichi_attack300(action,request);
     else if(attack_state[i]==340&&action_binding(i).character==4&&action_binding(i).weapon<2)
      effect=advance_roster_dash_landing_melee340(4,action_binding(i).weapon,action,request);
     else if(attack_state[i]==340&&uses_recovered_actor(i)){
      action.vertical=motion.velocity[1];action.gravity=air_melee_[i].gravity;
      action.movement_angle=motion.angles[1];
      effect=advance_roster_state340(action_binding(i).character,action_binding(i).weapon,action,request);
      motion.velocity[1]=action.vertical;air_melee_[i].gravity=action.gravity;
     }
     else if(attack_state[i]==313&&action_binding(i).character==11&&action_binding(i).weapon==1){
      // The original 55be80 slot-6 handler has no state313 body; its DAT
      // animation advances through the common action clock unchanged.
     }
     else if(attack_state[i]==312||attack_state[i]==313){
      const KeiichiDirectionalInput direction_input{request.animation_complete,request.grounded,
       bool(inputs[i].buttons&2),request.distance_squared,request.contact};
      effect=advance_roster_forward_melee312(action_binding(i).character,attack_state[i],action,
       direction_input,melee_held_[i],melee_released_[i],forward_followup_ticks_[i]);
     }
     else if(roster_followup_control_state(action_binding(i).character,action_binding(i).weapon,attack_state[i])){
      auto& scratch=roster_native_scratch[i];scratch=native_melee_scratch(i);
      auto state=native_followup_motion(world,i);
      RosterFollowupControlInput in;in.character=action_binding(i).character;in.weapon=action_binding(i).weapon;
      in.state=attack_state[i];in.phase=phase;in.frame=frame;in.contact=request.contact;
      in.complete=request.animation_complete;in.grounded=request.grounded;in.blocked=stop_ticks[i]!=0;
      in.distance_squared=request.distance_squared;in.voice_flags=request.voice_flags;
      in.direction=int(dash_command_cache_[i]);in.gauge=damage_signed(gauge[i]);
      const auto next=advance_roster_followup_control(scratch,state,in);followup_control_effects[i]=next;followup_control_visited[i]=true;
      action.moving=scratch.e8;action.contact_seen=scratch.ec;action.speed=state.speed;action.offset=state.offset;action.movement_angle=state.movement;
      motion.velocity[1]=state.vertical;ground_shot_[i].gravity=state.gravity;walk_motion_[i].step=state.turn;native_contact_mode[i]=state.contact_mode;
      for(unsigned n=0;n<next.count;++n){const auto& event=next.events[n];switch(event.kind){
       case FollowupControlKind::Clear:contact_ledger[i].clear_flags();contacted_[i]={};break;
       case FollowupControlKind::Capacity:contact_ledger[i].set_capacity(unsigned(event.value));break;
       case FollowupControlKind::Activate:activate_presentation(i);break;
       case FollowupControlKind::Statistics:record_melee_attack(world,i,unsigned(event.value));break;
       case FollowupControlKind::Sound:queue_sound({i,unsigned(event.value),actor.position});break;
       case FollowupControlKind::Voice:queue_voice({i,unsigned(event.value),unsigned(event.argument),-1,-1,0x4223d0,0});break;
       case FollowupControlKind::Query:case FollowupControlKind::State:case FollowupControlKind::Phase:break;
      }}
      effect.next_state=next.next_state;effect.next_phase=next.next_phase;
      if(next.clock==0)attack_return_[i]=true;
     }
     else if(action_binding(i).character==6&&attack_state[i]==302){
      // All three Tomitake302 DATs dispatch to common428510. That state's
      // common body only advances the clock; it has no followup motion/events.
      action.movement_angle=motion.angles[1];
     }
     else {
      KeiichiFollowup follow{attack_state[i],phase,frame,bool(action.contact_seen),action.speed,action.offset,action.movement_angle};
      const auto follow_input=KeiichiFollowupInput{request.animation_complete,request.grounded,request.contact,request.distance_squared};
      const auto preview=action_binding(i).policy==BattleActionPolicy::data_driven_preview;
      const auto next=preview&&attack_state[i]==301
       ?advance_roster_followup301(action_binding(i).character,action_binding(i).weapon,follow,follow_input)
       :preview&&attack_state[i]==302
        ?advance_roster_followup302(action_binding(i).character,action_binding(i).weapon,follow,follow_input)
        :advance_keiichi_followup(follow,follow_input);followup_effects[i]=next;
      action.speed=follow.speed;action.offset=follow.offset;action.movement_angle=follow.movement_angle;
      effect.next_state=next.next_state;effect.next_phase=next.next_phase;effect.initialize=next.initialize;effect.clear_contact=next.clear_contact;effect.strike=next.strike;
      effect.effect=next.effect;effect.voice=next.voice;effect.voice_argument=next.voice_argument;
      if(next.contact_mode>=0)native_contact_mode[i]=next.contact_mode;
      if(next.reset_capacity)contact_ledger[i].set_capacity(1);
     }
     attack_effects[i]=effect;
     const bool upper_walk_return=uses_layered_walk_shot(i)&&effect.next_state==10&&!walk_shot_[i].stopped;
     if(effect.next_state>=0){if(upper_walk_return)reset_native_upper_state_metadata(i);else reset_native_state_metadata(i);}
     if(pose_body_admission_replayed_[i])pose_full_admission_pending_[i]=false;
     else {
      if(effect.next_state>=0){
       if(uses_layered_walk_shot(i)&&effect.next_state==10){
        bind_actor_animation_state(i,10,0,true);
        if(walk_shot_[i].stopped)bind_actor_animation_state(i,10);
       }else bind_actor_animation_state(i,unsigned(effect.next_state));
      }
      if(effect.next_phase>=0){const unsigned target=effect.next_state>=0?unsigned(effect.next_state):attack_state[i];
       const unsigned selected=(attack_state[i]==350||attack_state[i]==360)&&effect.next_state>=0&&target!=350?0u:unsigned(effect.next_phase);
       bind_actor_animation_state(i,target,selected);
      }
     }
     if(effect.voice>=0){
      const auto ch=action_binding(i).character;
      const bool specific=attack_state[i]==332&&(ch==0||ch==2||ch==5||ch==7||ch==11||ch==15);
      queue_voice({i,unsigned(effect.voice),unsigned(std::max(0,effect.voice_argument)),specific?0:-1,-1,specific?0x422490u:0u,0});
     }
     if(effect.effect>=0)queue_sound({i,unsigned(effect.effect),actor.position});
     for(int id:effect.spawned_states)if(id>=0)queue_effect({i,unsigned(id),actor.position,actor.heading});
     motion.speed=action.speed;motion.angles[1]=action.movement_angle;
     std::memcpy(&actor.relationships.heading_offset_bits,&action.offset,4);
     if(effect.initialize){
      contacted_[i]={};contact_ledger[i].set_capacity(1);
      const auto target_id=actor.relationships.target;
      const unsigned bucket=world.actors.at(target_id).relationships.target==i?0:1;
      statistics[i].attacks_issued[bucket]+=effect.attack_statistics_count;
      statistics.at(target_id).attacks_received[bucket]+=effect.attack_statistics_count;
      const auto ally=actor.relationships.allies.empty()?0u:actor.relationships.allies[0]; // legacy contact fixtures may omit relationships
      if(target_id==world.actors.at(ally).relationships.target)statistics[i].attacks_at_primary_target+=effect.attack_statistics_count; //423000 ally0
      statistics[i].attacks_total+=effect.attack_statistics_count;
     }
     if(effect.clear_contact)contact_ledger[i].clear_flags();
     if(effect.contact_capacity>=0)contact_ledger[i].set_capacity(unsigned(effect.contact_capacity));
     // Four original 408 handlers request state30 and phase1 together: the
     // phase belongs to the resumed air dash, not to state408's DAT sequence.
     if(attack_state[i]==408&&effect.next_state==30&&effect.next_phase>=0){
      elapsed[i]=-1;geometry[i]={};attack_return_[i]=true;
      air_state[i]=30;air_phase[i]=unsigned(effect.next_phase);air_tick[i]=0;
      move_actor(i);continue;
     }
     if(attack_state[i]==460&&effect.next_state==450&&effect.next_phase>=0){
      attack_state[i]=450;attack_phase[i]=unsigned(effect.next_phase);elapsed[i]=0;
      cursors_[i]={};geometry[i]={};attack_return_[i]=true;move_actor(i);continue;
     }
     if((attack_state[i]==350||attack_state[i]==360)&&
        action_binding(i).policy==BattleActionPolicy::data_driven_preview&&
        effect.next_state>=0&&effect.next_phase>=0){
      attack_state[i]=unsigned(effect.next_state);
      attack_phase[i]=effect.next_state==350?unsigned(effect.next_phase):0;
      elapsed[i]=0;cursors_[i]={};geometry[i]={};attack_return_[i]=true;
      move_actor(i);continue;
     }
     if(effect.frame_override>=0)elapsed[i]=effect.frame_override;
     if(effect.next_phase>=0){attack_phase[i]=unsigned(effect.next_phase);elapsed[i]=0;native_melee_second_tick[i]=0;cursors_[i]={};attack_return_[i]=true;move_actor(i);continue;}
     if(uses_mion_counter(i)&&effect.next_state>=0&&mion_mobile_ground_shot_state(unsigned(effect.next_state))){attack_state[i]=unsigned(effect.next_state);attack_phase[i]=0;elapsed[i]=0;cursors_[i]={};geometry[i]={};attack_return_[i]=true;move_actor(i);continue;}
     // 421080 enters the requested DAT action state. Keeping a hand-written
     // exception list silently discarded new follow-ups such as 451/461.
     // 390-series guard states have their own clock and enter below.
     if(effect.next_state>=0&&(battle_ground_dash_state(unsigned(effect.next_state))||
        (effect.next_state>=300&&effect.next_state<500&&(effect.next_state<390||effect.next_state>=400)))&&
        data.state_frames_.count(unsigned(effect.next_state))){
      attack_state[i]=unsigned(effect.next_state);attack_phase[i]=0;elapsed[i]=0;
      cursors_[i]={};geometry[i]={};attack_return_[i]=true;move_actor(i);continue;
     }
     const bool native_melee_transition=ground_melee_control_visited[i]||dash_melee_control_visited[i]||
      air_melee_control_visited[i]||directional_melee_control_visited[i]||followup_control_visited[i];
     if(effect.next_state>=0){const bool was_air_melee=directional_melee_control_visited[i]||(uses_mion_counter(i)&&mion_mobile_melee_state(attack_state[i]))||attack_state[i]==320||attack_state[i]==330||attack_state[i]==331||attack_state[i]==332||attack_state[i]==334||attack_state[i]==339||attack_state[i]==402||attack_state[i]==408||battle_ground_dash_state(attack_state[i])||keiichi_walk_shot_state(attack_state[i]);elapsed[i]=-1;geometry[i]={};attack_return_[i]=true;
      //421080/421100 change DAT state without zeroing the body's velocity.
      if(effect.next_state==43||effect.next_state==44||effect.next_state==40||effect.next_state==42||effect.next_state==30){air_state[i]=unsigned(effect.next_state);air_phase[i]=air_tick[i]=0;air_transition_[i]=true;}else if(effect.next_state==392){guard_state[i]=392;guard_phase[i]=guard_tick[i]=0;}else if(!native_melee_transition)motion.speed=0;
      if(effect.next_state==10){walking[i]=true;walk_tick[i]=0;locomotion_phase[i]=0;
       locomotion_second_tick[i]=upper_walk_return?walk_shot_[i].lower_tick:0u;
       walk_motion_[i].direction=walk_shot_[i].direction;walk_motion_[i].step=walk_shot_[i].turn;
       auto scratch=native_melee_scratch(i);scratch.e8=walk_shot_[i].direction;scratch.known|=1u;store_native_melee_scratch(i,scratch);motion.speed=action.speed;}
      if(was_air_melee||native_melee_transition)move_actor(i);
      continue;
     }
     move_actor(i);continue;
    }
    if(action_binding(i).policy==BattleActionPolicy::data_driven_preview){
     // DAT supplies animation/hit geometry, not a character's acceleration program.
     // Do not run Rena's iron-cleaver lunge for unrelated character/weapon pairs.
     motion.speed=0;motion.angles[1]=0;
     if(actor.grounded)motion.velocity[1]=0;else motion.velocity[1]-=.5f;
     move_actor(i);continue;
    }
    if(phase==0){
     motion.speed=0;motion.angles[1]=0;
     approach_battle_offset(offset,0.f,frame==0?180.f:3.f);
    }
    BattleAttack300Motion attack{phase,frame,frame,1,motion.speed,offset};
    advance_battle_attack300(attack);
    motion.speed=attack.speed;
    std::memcpy(&actor.relationships.heading_offset_bits,&attack.offset,4);
    // Finish before movement, matching the state handler's early return.
    if(elapsed[i]>=0&&phase+1==attack_phases(i).size()&&frame+1>=data.animation_durations_.at(attack_phases(i)[phase].value))motion.speed=0;
    if(actor.grounded)motion.velocity[1]=0;else motion.velocity[1]-=.5f;
    move_actor(i);
   } while(false);
   // hit reaction/recovery. Single-pass blocks preserve each stage's early exits.
   do {
    const auto& data=actor_assets(i);
    if(!reaction_active_[i]||(frozen&(1u<<i)))continue;
    auto& actor=world.actors[i];auto& motion=actor.motion;const auto& hit=last_hit[i].normal;
    const auto victim_state=current_action_state(i);
    if(shared_recovery_body_state(action_binding(i).character,victim_state,actor.motion.blocked!=0)){
     advance_shared_recovery_handler(world,i,inputs[i]);move_actor(i);continue;
    }
    if(battle_common_hit_motion_state(victim_state)){
     advance_common_hit_handler(world,i,inputs[i]);move_actor(i);continue;
    }
   if(hit.action.state==187||hit.action.state==186||
      ((hit.action.state==188||hit.action.state==189||hit.action.state==190)&&actor.motion.blocked)){
     const auto& phases=data.state_animations_.at(reaction_animation_state(i,hit.action.state));const auto id=phases.at(reaction_phase[i]);
     if(++reaction_tick[i]>data.animation_durations_.at(id)&&reaction_phase[i]+1<phases.size()&&!data.animation_settings_.at(id).hold_phase){++reaction_phase[i];reaction_tick[i]=0;}
     move_actor(i);continue;
    }
    if(reaction_pending_[i]){
     const float sign=hit.action.state<200?-1.f:1.f;
     volatile float horizontal=sign*hit.pre.stagger.horizontal;
     motion.speed=horizontal*.01f;motion.velocity[1]=hit.pre.stagger.vertical*.01f;motion.angles[1]=0;
     //422BD0 already stores the release offset. The expiry-frame4202B0
     //can compensate it through42DD90 before State135's first body visit.
     //Keep that live value, as the original4AB090/4B54C2/4BD461 read it.
     reaction_pending_[i]=false;
    }
    // Character 3's three slot-6 handlers share a dedicated state135 flight,
    // wall rebound and landing route. Its DAT has one animation phase, so the
    // frame counter continues past the animation's nominal duration.
    if(hit.action.state==135&&action_binding(i).character==3){
     auto& flight=throw_victim135_[i];flight.speed=motion.speed;flight.vertical=motion.velocity[1];
     std::memcpy(&flight.heading_offset,&actor.relationships.heading_offset_bits,4);
     const auto& phases=data.state_frames_.at(135);const auto id=phases.at(reaction_phase[i]).value;
     ThrowVictim135PresentationInput in;in.weapon=action_binding(i).weapon;in.phase=reaction_phase[i];
     in.frame=reaction_tick[i];in.second_frame=common_hit_second_tick_[i];
     in.duration=data.animation_durations_.at(id);in.phase_count=unsigned(phases.size());in.hold=data.animation_settings_.at(id).hold_phase!=0;
     in.wall=actor.collided!=0;in.grounded=actor.grounded!=0;in.x=actor_input_x(i,inputs[i]);in.z=actor_input_z(i,inputs[i]);
     in.impact_horizontal=hit.pre.stagger.horizontal;in.impact_vertical=hit.pre.stagger.vertical;
     in.heading=actor.heading;in.position=actor.position;
     const auto out=advance_throw_victim135_presentation(flight,in);
     //4AB325/4AB32B write the same raw2C/2D8 bank exported by tag1A.
     //Replay State/421080 below afterwards so wall/landing resets win.
     if(uses_recovered_actor(i)){air_melee_[i].pitch=flight.model_pitch;air_melee_[i].pivot=flight.pivot;}
     throw_victim135_presentation[i]=out;throw_victim135_visited[i]=true;
     if(in.frame==0){motion.angles[1]=0;roster_native_scratch[i].e8=0;}
     std::optional<ActorSkeleton> muzzle;
     for(unsigned n=0;n<out.count;++n){const auto& e=out.events[n];switch(e.kind){
      case 'W':{GroundShotEffects shot;shot.fire=true;shot.count_attack=false;
       shot.bullet_slot=e.id;shot.origin=GroundShotOrigin::World;shot.pitch=e.pitch;
       append_actor_projectile_request(world,i,shot,e.position,e.yaw,flight.heading_offset,muzzle);break;}
      case 'C':contact_ledger[i].clear_flags();contacted_[i]={};break;
      case 'Q':contact_ledger[i].set_capacity(e.id);break;
      case 'P':queue_effect({i,e.id,e.position,e.yaw,e.pitch});break;
      case 'E':queue_sound({i,e.id,actor.position,native_battle_sound_mode(0x42c8b0)});break;
      case 'N':set_common_hit_action(i,e.id,e.id==113);break;
      case 'I':cursors_[i].advance(phases.at(in.phase),damage_signed(in.frame+1));break;
      case 'H':cursors_[i]={};bind_actor_animation_state(i,135,e.id);break;
      default:throw std::logic_error("Unknown State135 presentation service");
     }}
     motion.speed=flight.speed;motion.velocity[1]=flight.vertical;
     std::memcpy(&actor.relationships.heading_offset_bits,&flight.heading_offset,4);
     if(out.state==113){
      last_hit[i].normal.pre.stagger.horizontal=stagger[i].horizontal=out.transition.horizontal;
      last_hit[i].normal.pre.stagger.vertical=stagger[i].vertical=out.transition.vertical;
     }
     if(out.tail){reaction_phase[i]=out.phase;reaction_tick[i]=out.frame;common_hit_second_tick_[i]=out.second_frame;}
     else attack_return_[i]=true; // 421080 returns before both clocks and Satoko1's extra tail.
     move_actor(i);continue;
    }
    if(actor.grounded&&motion.velocity[1]<0){
     // 428510 front113/114/115 all read actor+280 (held jump), not melee.
     const unsigned landing_state=battle_air_hit_landing_state(hit.action.state,damage_signed(stagger[i].down),jump_held_[i]!=0);
     if(landing_state==45){
      recovery_state[i]=45;recovery_phase[i]=recovery_tick[i]=0;stagger[i].invincible=1;motion.velocity[1]=motion.speed=0;move_actor(i);continue;
     }
     recovery_state[i]=landing_state;recovery_phase[i]=recovery_tick[i]=0;motion.velocity[1]=0;move_actor(i);continue;
    }
    // 428510 jumps phase1 to phase2 before gravity when vertical speed is below6.
    if(reaction_phase[i]==1&&motion.velocity[1]<6.f&&(hit.action.state!=115||reaction_tick[i]%17==0)){reaction_phase[i]=2;reaction_tick[i]=0;move_actor(i);continue;}
    volatile float vertical=motion.velocity[1]-.3f;motion.velocity[1]=vertical;
    const float deceleration=(hit.action.state==114||hit.action.state==214)?.5f:.25f;
    if(hit.action.state<200&&motion.speed< -4.f){volatile float speed=motion.speed+deceleration;motion.speed=speed;}
    if(hit.action.state>=200&&motion.speed>4.f){volatile float speed=motion.speed-deceleration;motion.speed=speed;}
    // Phase3 holds its pose while physics continues until landing.
    if(reaction_phase[i]!=3||hit.action.state==115||hit.action.state==215){
     const auto& phases=data.state_animations_.at(reaction_animation_state(i,hit.action.state));const auto id=phases.at(reaction_phase[i]);
     if(++reaction_tick[i]>data.animation_durations_.at(id)&&reaction_phase[i]+1<phases.size()&&!data.animation_settings_.at(id).hold_phase){++reaction_phase[i];reaction_tick[i]=0;}
    }
    move_actor(i);
   } while(false);
  }
  //527880 raw68 prefix runs after+A0 and before the State switch. Scalar
  //cases never read68; complete bodies already execute their own prefix.
  //Restore omitted scalar/default visits before clocks/scripts/pose, once.
  for(unsigned i=0;i<4;++i){
   const auto& binding=action_binding(i);
   const bool full_prefix=shoot_native_visited[i]||full_charge_native_visited[i]||special_strike_native_visited[i]||
    jump_native_visited[i]||dash_native_visited[i]||remaining_melee_control_visited[i];
   if(uses_recovered_actor(i)&&binding.character==6&&binding.weapon==2&&!full_prefix&&
      ((frame_schedule_.actor_mask&~fixture_mask)&(1u<<i))&&!stop_ticks[i])advance_native_actor_spine_prefix(native_extra68[i]);
  }
  // Satoko1 reaches4b9a20 only when its handler did not return early.
  for(unsigned i=0;i<4;++i){
   if(action_binding(i).character==3&&action_binding(i).weapon==1&&!(frozen&(1u<<i))&&
       !shared_recovery_visited[i]&&!shoot_native_visited[i]&&!remaining_melee_control_visited[i]&&!jump_native_visited[i]&&!dash_native_visited[i]&&!attack_return_[i]&&current_action_state(i)==handler_states[i]&&satoko_field_tail_state(handler_states[i])){
    if(advance_satoko_field_tail(field_contact_rank[i],field_contact_rank_timer[i],satoko_mine_clock[i],projectile_owner_signal_[i],handler_states[i])){
     queue_sound({i,109,world.actors[i].position});++shots_attempted[i];record_shooting_attack(world,i,1);
     const bool stronger=special_gauges[i].active1&&special_gauges[i].ready1!=0;
     const unsigned slot=stronger?7:6;const auto& bullet=actor_assets(i).weapon_item->bullets.at(slot);
     if(bullet.magazine_index<0||consume_battle_round(magazines[i].at(unsigned(bullet.magazine_index)))){
      GroundShotEffects shot;shot.fire=true;shot.bullet_slot=slot;shot.origin=GroundShotOrigin::World;shot.count_attack=false;
      const auto& a=world.actors[i];shot_requests.push_back({i,shot,{a.position[0],a.position[1]+50,a.position[2]},a.heading+[&](){float offset;std::memcpy(&offset,&a.relationships.heading_offset_bits,4);return offset;}(),a.relationships.target});++shots_spawn_requested[i];
     }
    }
   }
   if(locomotion_native_visited[i]&&locomotion_native_effects[i].tail){
    const auto& next=locomotion_native_effects[i];const auto& phases=actor_assets(i).state_frames_.at(current_action_state(i));
    cursors_[i].advance(phases.at(locomotion_phase[i]),damage_signed(projectile_owner_animation_frame(i)));
    if(next.next_phase>=0){locomotion_phase[i]=unsigned(next.next_phase);cursors_[i]={};bind_actor_animation_state(i,current_action_state(i),locomotion_phase[i]);}
   }
   if(uses_recovered_actor(i)){native_clock_prepared_[i]=true;if(!(frozen&(1u<<i)))native_clock_geometry_[i]=prepare_native_actor_clock(world,i);}
  }
  // Slot7/body counter stores (notably mode1=20) feed the next657390 poll.
  for(unsigned i=0;i<4;++i)if(human_input_active_[i]||(cpu&&cpu->enabled[i])){
   human_inputs_[i].body_counters(jump_held_[i],melee_held_[i],shoot_held[i],special_button290[i]);
   if(cpu_driver&&cpu&&cpu->enabled[i])cpu_driver->frame.slots[i].auxiliary[0]=special_button290[i];
  }
  scripts();
  for(unsigned i=0;i<4;++i)if(frame_schedule_.actor_mask&(1u<<i)){
   if(startup.enabled&&startup.frame==1)queue_voice({i,7,30,-1,-1,0x422560,0,int(i)}); //42e110 prefix, before status/slot9.
   //42e110 prefix: command completion from the PREVIOUS4201a0 visit.
   if(cpu_driver)consume_battle_command_notice(i,cpu_driver->commands[i],death_reset_flags[i][12],
    [&](const VoiceRequest& request){queue_voice(request);});
   const auto& actor=world.actors[i];const auto target=actor.relationships.secondary_target;
   const auto& enemy=world.actors.at(target);float target_offset;
   std::memcpy(&target_offset,&enemy.relationships.heading_offset_bits,4);
   melee_voice_flags[i]=battle_melee_voice_flags(i,targeting[i].ally_index,current_action_state(target),
    last_hit[target].last_owner,enemy.relationships.secondary_target,enemy.heading,target_offset,actor.heading);
   status_aura_models[i]=battle_status_aura(current_action_state(i),projectile_owner_phase(i));
   if(!status_visual_points_ready[i]&&battle_status_reaction(current_action_state(i)))status_visual_points[i]=body_contact_points(world,i);
   const auto& points=status_visual_points[i];
   auto presentation=advance_battle_status_visuals(status[i],current_action_state(i),projectile_owner_animation_frame(i),health[i],random_,
    {points[0][0],points[0][1],points[0][2]},{points[1][0],points[1][1],points[1][2]});
   status_tick_effects[i]=presentation.effects;status_visual_events[i]=std::move(presentation.events);
   for(const auto& event:status_visual_events[i]){
    if(event.kind=='P')queue_effect({i,event.id,event.position,0,0});
    else if(event.kind=='S')queue_sound({i,event.id,world.actors[i].position,native_battle_sound_mode(0x42c8b0)});
   }
   if(enable_native_death&&ninth_status_timer[i])--ninth_status_timer[i]; //42e110 includes native+7fc after the eight attack-owned timers.
   advance_native_battle_events(world,i); //actor_mask, independently of body hitstop.
   if(action_binding(i).character==7&&action_binding(i).weapon==1&&stop_ticks[i]==0)projectile_owner_field_exit[i]=0;
  }
  if(startup.enabled){
   prepared_scene_inputs_=inputs;
   std::array<unsigned,4> buttons{};for(unsigned i=0;i<4;++i)buttons[i]=supplied_inputs[i].buttons;
   if(presentation_buttons)buttons=*presentation_buttons;
   if(before_scene)before_scene();advance_scene_services(world,buttons);scene_services_prepared_=true;
   if(after_scene)after_scene();
  }
  if(modern_contacts_){
   // Each41f580 owns timers, gauges, animation service, reload and targeting.
   // +a0==1 blocks the body, then expires before4202b0 movement this frame.
   for(unsigned i=0;i<4;++i)if(frame_schedule_.actor_mask&(1u<<i)){
    advance_actor_hit_timers(i);special_gauges[i].tick(health[i],gauge[i]);
    advance_actor_animation_service(i);
    if(actor_assets(i).weapon_item)for(auto& magazine:magazines[i])tick_battle_magazine(magazine);
    const auto& actor=world.actors[i];const auto& opponents=actor.relationships.opponents;
    auto& warnings=direction_warnings[i];warnings.resize(opponents.size());
    for(unsigned j=0;j<opponents.size();++j){const unsigned other=opponents[j];const auto& enemy=world.actors.at(other);
     const int incoming=battle_incoming_warning(i,other,enemy.relationships.secondary_target,special_gauges[other].activated0,actor.relationships.secondary_target,
      [&](unsigned recipient,unsigned id){if(voice_human_mask_&(1u<<recipient))
       queue_sound({recipient,id,{},BattleSoundMode::Plain,false,true,true});}); //41fcb3..41fd3c ->64af20
     float angle=0;
     if(incoming){BattleFacing facing;face_battle_target(facing,actor.position[0],actor.position[2],enemy.position[0],enemy.position[2]);angle=facing.heading-actor.heading;}
     advance_battle_direction_warning(warnings[j],incoming,angle);
    }
    auto& target=targeting[i];auto& special=special_gauges[i];
    const unsigned acquired=human_input_active_[i]?human_inputs_[i].held(3):
     cpu&&cpu->enabled[i]?(phase_commands_blocked_[i]?0u:unsigned(cpu->slots[i].target)):
     (inputs[i].buttons&8)?target.held+1:0;
    target.joint_ticks=special.ready1;target.alternate_sound=special.active1;
    advance_battle_target_acquired(world,i,target,acquired,target_availability);
    special.ready1=target.joint_ticks; //848 is the SAME native timer read by boosted bodies.
    if(target.sound>=0&&(voice_human_mask_&(1u<<i)))
     queue_sound({i,unsigned(target.sound),{},BattleSoundMode::Plain,false,true,false}); //64ae10 HUMAN-owned target SE.
    const unsigned command_age=human_input_active_[i]?human_inputs_[i].held(6):cpu&&cpu->enabled[i]?cpu->slots[i].auxiliary[2]:(inputs[i].buttons&32)?1u:0u;
    if(cpu_driver)cpu_driver->apply_acquired_command(world,i,command_age,damage_signed(health[i]),
     [&](const VoiceRequest& request){queue_voice(request);}); //41f580 own tail, before4201a0.
   
   }
   //4201a0 always visits all four actors, even during828 time stop.
   for(auto& target:targeting)advance_battle_target_cooldown(target);
   if(cpu_driver)cpu_driver->advance_common_presentation(death_reset_flags);
   for(unsigned i=0;i<4;++i)advance_battle_vision_alpha(vision_alpha[i],status[i].duration[5],status[i].duration[7]);
   //4201a0 clears aec8 only after every actor's41f580 observed it.
   for(auto& special:special_gauges)special.activated0=false;
   // CPU commands were applied in their own41f580 visits above.
   for(auto& availability:target_availability)availability.changed=false; // 4201a0 follows all41f580 calls.
   if(startup.enabled){defeat_credit_flags.fill(0);defeated_flags.fill(0);defeat_events_={};} //420288/42029c, all actors including time-stop.
   advance_battle_score_presentation(host_.score_feedback,teams_.score,displayed_team_scores_); //6430f0 also runs in selected828 mode.
   for(unsigned i=0;i<4;++i){
    if((frame_schedule_.actor_mask&~fixture_mask)&(1u<<i)){
     world.actors[i].motion.gate=damage_signed(stop_ticks[i]);update_world_motion(world,i,wall,floor);
    }
    //6358c0 interleaves each actor's movement with its owner pool movement.
    if((frame_schedule_.owner_motion_mask&(1u<<i))&&owner_projectile_motion)owner_projectile_motion(i);
   }
   if(frame_schedule_.owner_motion_mask&&projectile_motion)projectile_motion();
   refresh_actor_pose_cache(world);
   snapshot_body_contact_geometry(world); //420880: current DAT points, before weapon history/separation.
   if(after_pose_cache)after_pose_cache(); //420880 weapon history, before separation/contacts.
   separate_battle_bodies(world,wall);
   if(global_projectile_motion)global_projectile_motion(); //6358c0 global6cfa30 follows pose/separation.
   frame_services_prepared_=true;
  }
 }
 void update(BattleWorld& world,const net::InputChannel::Frame& supplied_inputs,const BattleCpuFrame* cpu=nullptr){
  update_with_projectile_contacts(world,supplied_inputs,[](unsigned){},cpu);
 }
 template<class PoolContacts> void update_with_projectile_contacts(BattleWorld& world,const net::InputChannel::Frame& supplied_inputs,PoolContacts pool_contacts,const BattleCpuFrame* cpu=nullptr,const std::array<unsigned,4>* presentation_buttons=nullptr){
  if(offline_pause.paused)return;
  prepared_attack_mask=0;
  std::array<unsigned,4> result_buttons{};for(unsigned i=0;i<4;++i)result_buttons[i]=supplied_inputs[i].buttons;
  if(presentation_buttons)result_buttons=*presentation_buttons;
  if(!scene_services_prepared_)advance_scene_services(world,result_buttons);
  auto inputs=scene_services_prepared_?prepared_scene_inputs_:(match.winner<0?supplied_inputs:net::InputChannel::Frame{});
  if(!scene_services_prepared_){
   if(match.winner<0&&cpu)for(unsigned i=0;i<4;++i)if(cpu->enabled[i])inputs[i]=cpu_input_levels(cpu->slots[i]);
   if(startup_blocked_this_frame_)for(unsigned i=0;i<4;++i)inputs[i]=battle_startup_input(inputs[i],cpu&&cpu->enabled[i]);
  }
  scene_services_prepared_=false;
  // Preserve acquisition-time suppression even if42e110 expired timer1 this tick.
  for(unsigned i=0;i<4;++i)if(has_prepared_attack_suppression_?prepared_attack_suppression_[i]:status[i].duration[3]!=0)inputs[i].buttons&=~21u;
  has_prepared_attack_suppression_=false;
  if(modern_contacts_&&!frame_services_prepared_){
   frame_schedule_=make_battle_frame_schedule(time_stop_ticks);body_frozen_mask_=frozen_mask()|((~frame_schedule_.actor_mask)&15u);
  }
  const auto frozen=modern_contacts_?body_frozen_mask_:frozen_mask();
  if(!modern_contacts_){
  for(auto& ticks:stop_ticks)if(ticks)--ticks;
  for(unsigned i=0;i<4;++i){
   if(frozen&(1u<<i))continue;
   auto& value=stagger[i];BattleHitTimers timers{};
   timers.state=special_entry[i].state?special_entry[i].state:guard_state[i]?guard_state[i]:air_state[i]?air_state[i]:recovery_state[i]?recovery_state[i]:reaction_active_[i]?last_hit[i].normal.action.state:elapsed[i]>=0?attack_state[i]:walking[i]?10:0;
   timers.invincible=value.invincible;timers.count=value.count;timers.down=value.down;timers.down_timer=value.down_timer;timers.accum=value.accum;timers.accum_timer=value.timer;
   timers.health=health[i];timers.display_health=delayed_health[i];
   tick_battle_hit_timers(timers);
   delayed_health[i]=timers.display_health;
   value.invincible=timers.invincible;value.count=timers.count;value.down=timers.down;value.down_timer=timers.down_timer;value.accum=timers.accum;value.timer=timers.accum_timer;
  }
  }else if(!frame_services_prepared_){for(unsigned i=0;i<4;++i)if(frame_schedule_.actor_mask&(1u<<i))advance_actor_hit_timers(i);}
  frame_services_prepared_=false;
  host_.calls.clear();
  for(unsigned a=0;a<4;++a){
   const auto& data=actor_assets(a);
   if(uses_mion_counter(a)){
    if(elapsed[a]>=0&&(attack_state[a]==370||attack_state[a]==371)&&!reaction_active_[a]&&!guard_state[a]&&!death_state[a]&&prepare_attack_geometry(world,a))prepared_attack_mask|=1u<<a;
    else geometry[a]={};
    if(elapsed[a]>=0&&(attack_state[a]==370||attack_state[a]==371))continue;
   }
   const bool jumping=(inputs[a].buttons&2)!=0;
   const bool jump_edge=jumping&&!jump_pressed_[a];jump_pressed_[a]=jumping;
   bool down=(inputs[a].buttons&1)!=0;
   if(frozen&(1u<<a)){
    pressed_[a]=down;
    // 46a190 stops its clock at+a0;637680 still visits actor contacts.
    if(uses_recovered_actor(a)&&elapsed[a]>=0&&!reaction_active_[a]&&
       !guard_state[a]&&!air_state[a]&&prepare_attack_geometry(world,a))prepared_attack_mask|=1u<<a;
    continue;
   }
   if(special_entry[a].state){pressed_[a]=down;continue;}
   if(guard_state[a]){pressed_[a]=down;continue;}
   if(use_recovered_melee_timing)jump_motion_[a].button_ticks=jump_held_[a];
   else if(jumping)++jump_motion_[a].button_ticks;else jump_motion_[a].button_ticks=0;
   if(!use_recovered_melee_timing&&jump_edge&&elapsed[a]<0&&damage_signed(health[a])>0&&!reaction_active_[a]&&!air_state[a]&&world.actors[a].grounded){
    air_state[a]=40;air_phase[a]=air_tick[a]=0;pressed_[a]=down;continue;
   }
   if(!use_recovered_melee_timing&&down&&!pressed_[a]&&elapsed[a]<0&&damage_signed(health[a])>0&&!reaction_active_[a]&&!air_state[a]&&world.actors[a].grounded){attack_state[a]=300;elapsed[a]=0;attack_phase[a]=0;cursors_[a]={};contacted_[a]={};if(uses_keiichi(a)){contact_ledger[a].clear_flags();contact_ledger[a].set_capacity(1);keiichi_motion_[a]={};attack_effects[a]={};pressed_[a]=down;continue;}if(action_binding(a).policy==BattleActionPolicy::data_driven_preview){pressed_[a]=down;continue;}}
   pressed_[a]=down;
   const bool native_action_clock=uses_recovered_actor(a)||attack_state[a]==332||attack_state[a]==333||attack_state[a]==334||attack_state[a]==339||battle_ground_dash_state(attack_state[a]);
   const bool skip_attack_clock=native_action_clock&&attack_return_[a];attack_return_[a]=false;
   if(skip_attack_clock&&elapsed[a]<0)continue;
   if(native_clock_prepared_[a]){if(!native_clock_geometry_[a])continue;}
   else{
   if(air_transition_[a]){air_transition_[a]=false;continue;}
   if(air_state[a]==30||(air_state[a]>=40&&air_state[a]<=42)){
    const auto& phases=data.state_animations_.at(air_state[a]);
    const auto duration=data.animation_durations_.at(phases.at(air_phase[a]));
    if(++air_tick[a]>duration&&air_phase[a]+1<phases.size()&&!data.animation_settings_.at(phases[air_phase[a]]).hold_phase){++air_phase[a];air_tick[a]=0;}
    continue;
   }
   if(air_state[a]==103||air_state[a]==203)continue; //428510 already advanced before scripts.
   if(air_state[a]){
    if(air_state[a]==43){
     if(world.actors[a].grounded&&world.actors[a].motion.velocity[1]<0){air_state[a]=44;air_phase[a]=air_tick[a]=0;}
     else ++air_tick[a];
    }else{
     const auto& phases=data.state_animations_.at(44);
     const auto duration=data.animation_durations_.at(phases.at(air_phase[a]));
     if(air_phase[a]+1==phases.size()&&air_tick[a]+1>=duration)air_state[a]=0;
     else if(++air_tick[a]>duration&&air_phase[a]+1<phases.size()&&!data.animation_settings_.at(phases[air_phase[a]]).hold_phase){++air_phase[a];air_tick[a]=0;}
    }
    continue;
   }
   if(elapsed[a]<0){
    // Idle state0 also enters falling state43 when support is lost.
    if(!world.actors[a].grounded&&!reaction_active_[a]){air_state[a]=43;air_phase[a]=air_tick[a]=0;}
    continue;
   }
   // state300's grounded gate precedes all attack work (438310).
   const bool directional_airborne=directional_melee_control_visited[a]||(action_binding(a).policy==BattleActionPolicy::data_driven_preview&&
    roster_directional_airborne_allowed(action_binding(a).character,attack_state[a],
     int(attack_phase[a]),elapsed[a]));
   // The native body already applies its phase-specific support gate before
   // movement. Preserve that decision through the shared clock/contact tail.
   const bool dash_melee_airborne=dash_melee_control_visited[a]||(action_binding(a).policy==BattleActionPolicy::data_driven_preview&&
    roster_ground_dash_melee_airborne_allowed(action_binding(a).character,attack_state[a],
     int(attack_phase[a]),elapsed[a]+1));
   const bool landing_combo_handler=uses_recovered_actor(a)&&
    (attack_state[a]==340||attack_state[a]==341);
   if(!world.actors[a].grounded&&!directional_airborne&&!dash_melee_airborne&&!landing_combo_handler&&!(uses_mion_counter(a)&&mion_mobile_melee_state(attack_state[a]))&&!(attack_state[a]>=350&&attack_state[a]<=362&&action_binding(a).policy==BattleActionPolicy::data_driven_preview)&&!roster_throw_followup_state(action_binding(a).character,action_binding(a).weapon,attack_state[a])&&attack_state[a]!=320&&attack_state[a]!=329&&attack_state[a]!=332&&attack_state[a]!=333&&attack_state[a]!=334&&attack_state[a]!=336&&attack_state[a]!=339&&attack_state[a]!=360&&attack_state[a]!=370&&attack_state[a]!=371&&attack_state[a]!=402&&attack_state[a]!=403&&attack_state[a]!=408&&attack_state[a]!=409&&attack_state[a]!=422&&attack_state[a]!=423&&attack_state[a]!=460&&!(roster_secondary_charge_state(action_binding(a).character,action_binding(a).weapon,attack_state[a])&&attack_state[a]>=460)&&attack_state[a]!=469){elapsed[a]=-1;air_state[a]=43;air_phase[a]=air_tick[a]=0;geometry[a]={};continue;}
   if(native_action_clock&&!skip_attack_clock){
    if(uses_layered_walk_shot(a))++walk_shot_[a].lower_tick;
    const auto id=attack_phases(a).at(attack_phase[a]).value;
    ++elapsed[a];
    if(ground_melee_control_visited[a]||dash_melee_control_visited[a]||air_melee_control_visited[a]||directional_melee_control_visited[a]||followup_control_visited[a])++native_melee_second_tick[a];
    if(attack_phase[a]+1<attack_phases(a).size()&&unsigned(elapsed[a])>data.animation_durations_.at(id)&&!data.animation_settings_.at(id).hold_phase){++attack_phase[a];elapsed[a]=0;native_melee_second_tick[a]=0;cursors_[a]={};}
   }
   }
   const auto& phase=attack_phases(a).at(attack_phase[a]);
   // 4218c0 completes the final phase at duration <= elapsed + 1.
   if(!native_action_clock&&attack_phase[a]+1==attack_phases(a).size()&&unsigned(elapsed[a]+1)>=data.animation_durations_.at(phase.value)){elapsed[a]=-1;continue;}
   //637680 sends every actor to637950. The contact gate is the current DAT
   // extent at+24, not a hand-written shooting/melee state classification.
   if(!prepare_attack_geometry(world,a))continue;
   if(modern_contacts_)prepared_attack_mask|=1u<<a;
   else resolve_attack_contacts(world,a);
   if(elapsed[a]<0)continue;
   if(native_action_clock||skip_attack_clock)continue; // Keiichi clock already advanced before frame selection. 421100 transition returns before handler clock, not before later movement/contact.
   // 438310 advances both counters an extra tick during lunge frames 16..28.
   if(action_binding(a).policy==BattleActionPolicy::legacy_test&&attack_phase[a]==1&&elapsed[a]>=16&&elapsed[a]<=28)++elapsed[a];
   ++elapsed[a];
   // Common character tail uses a strict duration < counter comparison.
   // DAT hold flag suppresses automatic phase advancement; cancel windows remain pending.
   if(attack_phase[a]+1<attack_phases(a).size()&&unsigned(elapsed[a])>data.animation_durations_.at(phase.value)&&!data.animation_settings_.at(phase.value).hold_phase){
    ++attack_phase[a];elapsed[a]=0;cursors_[a]={};
   }
  }
  if(!modern_contacts_)update_held_positions(world); // Modern420880 snapshot already owns held placement.
  // The full movement path already froze420880 points before separation.
  // Contacts-only callers receive the same snapshot before pool traversal.
  if(modern_contacts_&&!body_attack_points_ready_)snapshot_body_contact_geometry(world);
  // 637680: each original owner's projectile pool precedes that actor's
  // contact traversal. Reflected ownership does not change pool membership.
  for(unsigned a=0;a<4;++a){
   pool_contacts(a);
   //637680 visits every body;637950 reads its LIVE frame extent, not attack class/clock.
   if(uses_recovered_actor(a)||((prepared_attack_mask&(1u<<a))&&elapsed[a]>=0))resolve_attack_contacts(world,a);
  }
  body_attack_points_ready_=false;
 }
 void resolve_projectile_contacts(BattleWorld& world,KeiichiNormalProjectile& bullet,const ActorFrameData& frame,const BattleNormalHitContact& contact,bool reuse_body_points=false){
  if(bullet.released)return;
  BattleHitPipelineInput input{};bind_actor_frame_hit(frame,input);input.geometry=contact;
  if(!reuse_body_points)for(unsigned v=0;v<4;++v)body_points_[v]=body_contact_points(world,v);
  resolve_attack_contacts(world,bullet.owner,&bullet,&input);
 }
private:
 void store_native_death_motion(BattleWorld& world,unsigned i,const BattleDeathMotion& s){
  auto& actor=world.actors[i];auto& m=actor.motion;
  m.speed=s.speed;m.velocity=s.velocity;m.angles[1]=s.movement;actor.position=s.position;
  ground_shot_[i].gravity=common_hit_gravity_[i]=s.gravity;walk_motion_[i].step=s.turn;
  std::memcpy(&actor.relationships.heading_offset_bits,&s.offset,4);
  auto scratch=native_melee_scratch(i);scratch.e8=damage_signed(s.scratch);scratch.known|=1u;
  store_native_melee_scratch(i,scratch);common_hit_scratch_[i]=s.scratch;
  stagger[i].down=s.down;stagger[i].down_timer=s.down_timer;stagger[i].invincible=s.invincible;
  health[i]=s.health;delayed_health[i]=s.delayed_health;gauge[i]=damage_signed(s.gauge);death_bonus_used[i]=s.bonus;
  std::copy(s.status.begin(),s.status.begin()+8,status[i].duration.begin());ninth_status_timer[i]=s.status[8];magazines[i]=s.magazines;
  store_native_death_flags(i,s.reset_flags);target_availability[i].changed=s.changed!=0;
  status_aura_models[i]=s.last_owner; // +7d4 only; preserve the distinct damage owner+7d8.
  death_tick[i]=s.frame;native_melee_second_tick[i]=common_hit_second_tick_[i]=s.second_frame;
 }
 void admit_native_death_state(unsigned i,unsigned value){
  death_state[i]=death_phase[i]=death_tick[i]=0;air_state[i]=air_phase[i]=air_tick[i]=0;
  guard_state[i]=recovery_state[i]=ground_hit_state[i]=0;special_entry[i]={};
  reaction_active_[i]=reaction_pending_[i]=false;elapsed[i]=-1;geometry[i]={};walking[i]=false;air_transition_[i]=false;
  if(battle_death_motion_state(value))death_state[i]=value;
  else if(value==44){air_state[i]=44;air_transition_[i]=true;}
  else throw std::runtime_error("Unexpected original death admission");
  reset_native_state_metadata(i);common_hit_second_tick_[i]=0;bind_actor_animation_state(i,value);
 }
 void advance_native_death_handler(BattleWorld& world,unsigned i,const net::Input& input){
  auto& actor=world.actors[i];auto& m=actor.motion;const auto& data=actor_assets(i);
  BattleDeathMotion s;s.state=death_state[i];s.phase=death_phase[i];s.frame=death_tick[i];s.second_frame=native_melee_second_tick[i];
  const auto& phases=data.state_animations_.at(s.state);const auto id=phases.at(s.phase);
  s.duration=data.animation_durations_.at(id);s.hold=data.animation_settings_.at(id).hold_phase!=0;
  s.grounded=actor.grounded!=0;s.speed=m.speed;s.velocity=m.velocity;s.position=actor.position;s.heading=actor.heading;
  s.gravity=ground_shot_[i].gravity;s.movement=m.angles[1];s.turn=walk_motion_[i].step;
  std::memcpy(&s.offset,&actor.relationships.heading_offset_bits,4);
  auto scratch=native_melee_scratch(i);s.scratch=unsigned(scratch.e8);
  s.last_owner=status_aura_models[i];s.down=stagger[i].down;s.down_timer=stagger[i].down_timer;s.invincible=stagger[i].invincible;
  s.health=health[i];s.delayed_health=delayed_health[i];s.gauge=unsigned(gauge[i]);s.bonus=death_bonus_used[i];s.changed=target_availability[i].changed;
  std::copy(status[i].duration.begin(),status[i].duration.end(),s.status.begin());s.status[8]=ninth_status_timer[i];s.magazines=magazines[i];
  s.reset_flags=native_death_flags(i);
  struct Host {
   DevelopmentAnimatedCombat& c;BattleWorld& world;unsigned slot;const net::Input& input;
   void event(char kind,unsigned value,const BattleDeathMotion& s){c.death_native_events[slot].push_back({kind,value,s.position});}
   int remaining(const BattleDeathMotion& s){
    const int stock=c.respawn_enabled_?damage_signed(c.team_limits_[slot/2]-c.teams_.score[slot/2]):0;
    event('Q',unsigned(stock),s);return stock;
   }
   void state(BattleDeathMotion& s,unsigned value){
    event('N',value,s);c.store_native_death_motion(world,slot,s);c.admit_native_death_state(slot,value);
    s.state=value;s.phase=s.frame=s.second_frame=0;
   }
   void phase(BattleDeathMotion& s,unsigned value){
    event('H',value,s);
    if(value>=c.actor_assets(slot).state_animations_.at(s.state).size())throw std::runtime_error("Original death phase outside DAT");
    c.store_native_death_motion(world,slot,s);s.phase=value;s.frame=s.second_frame=0;
    c.death_phase[slot]=value;c.death_tick[slot]=c.native_melee_second_tick[slot]=c.common_hit_second_tick_[slot]=0;
    c.cursors_[slot]={};c.bind_actor_animation_state(slot,s.state,value);
   }
   void clock(const BattleDeathMotion& s){
    event('A',s.frame,s);c.cursors_[slot].advance(c.actor_assets(slot).state_frames_.at(s.state).at(s.phase),damage_signed(s.frame));
   }
   void steer(BattleDeathMotion& s){steer_battle_offset(s.offset,input.x,input.z,s.turn);}
   void voice(const BattleDeathMotion& s,unsigned id,unsigned priority,unsigned choice,bool alternate){
    event(alternate?'W':'V',id,s);
    // Preserve the source call's identity for the voice consumer. Both helpers
    // currently share its bank selection, as in the retained voice adapter.
    c.queue_voice({slot,id,priority,-1,-1,alternate?0x422240u:0x4223d0u,choice&255u});
   }
   void sound(const BattleDeathMotion& s,unsigned id){event('S',id,s);c.queue_sound({slot,id,s.position});}
   void particle(const BattleDeathMotion& s,unsigned id){event('P',id,s);c.queue_effect({slot,id,s.position,s.heading});}
   void spawn(BattleDeathMotion& s){
    event('X',0,s);
    const auto& b=c.respawn_bounds_;const auto x=c.random_.next(),z=c.random_.next();
    event('G',x,s);event('G',z,s);
    s.position={float(x%(unsigned(b[2])-unsigned(b[0])))+float(b[0]),1000.f,float(z%(unsigned(b[3])-unsigned(b[1])))+float(b[1])};
    world.actors[slot].position=s.position;
   }
   void reload(BattleDeathMotion& s){event('M',0,s);for(auto& magazine:s.magazines)reset_battle_magazine(magazine);}
   void respawn(BattleDeathMotion& s){event('R',0,s);(void)respawn_battle_death_motion(s,*this);}
  } host{*this,world,i,input};
  advance_battle_death_motion(s,host);death_native_motion[i]=s;death_native_visited[i]=true;
  store_native_death_motion(world,i,s);
 }
 void set_common_hit_action(unsigned i,unsigned state,bool pending){
  if(uses_recovered_actor(i))reset_native_state_metadata(i); //421080 includes421100: reset persistent ADFC and paired admission metadata.
  ground_hit_state[i]=air_state[i]=guard_state[i]=recovery_state[i]=0;
  ground_hit_phase[i]=ground_hit_tick[i]=air_phase[i]=air_tick[i]=0;
  recovery_phase[i]=recovery_tick[i]=reaction_phase[i]=reaction_tick[i]=0;
  common_hit_second_tick_[i]=0;elapsed[i]=-1;geometry[i]={};walking[i]=false;walk_tick[i]=0;
  reaction_active_[i]=state!=0&&state!=43;reaction_pending_[i]=pending;air_transition_[i]=false;
  if(state==43){air_state[i]=43;air_transition_[i]=true;}
  else if(state==103||state==203){air_state[i]=state;reaction_active_[i]=false;}
  else if(state==100||state==101||state==102||state==200||state==201||state==202)ground_hit_state[i]=state;
  else if(state==45||state==118||state==119||state==120||state==121||state==124||state==128||state==221)recovery_state[i]=state;
  last_hit[i].normal.action.state=state;
  if(uses_recovered_actor(i))bind_actor_animation_state(i,state);
 }
#include "shared_recovery_world_20261004.inc.hpp"
 void advance_common_hit_handler(BattleWorld& world,unsigned i,const net::Input& input){
  auto& actor=world.actors[i];auto& motion=actor.motion;const auto& data=actor_assets(i);
  BattleCommonHitMotion s;s.state=current_action_state(i);
  unsigned* phase=ground_hit_state[i]?&ground_hit_phase[i]:recovery_state[i]?&recovery_phase[i]:air_state[i]?&air_phase[i]:&reaction_phase[i];
  unsigned* tick=ground_hit_state[i]?&ground_hit_tick[i]:recovery_state[i]?&recovery_tick[i]:air_state[i]?&air_tick[i]:&reaction_tick[i];
  s.phase=*phase;s.frame=*tick;s.second_frame=common_hit_second_tick_[i];
  const auto& phases=data.state_animations_.at(reaction_animation_state(i,s.state));const auto id=phases.at(s.phase);
  s.duration=data.animation_durations_.at(id);s.phase_count=unsigned(phases.size());s.hold_phase=data.animation_settings_.at(id).hold_phase!=0;
  s.complete=s.phase+1==s.phase_count&&s.frame+1>=s.duration;
  s.grounded=actor.grounded!=0;s.wall_contact=actor.collided!=0;s.speed=motion.speed;s.vertical=motion.velocity[1];
  s.gravity=common_hit_gravity_[i];s.movement=motion.angles[1];s.turn_step=walk_motion_[i].step;
  std::memcpy(&s.offset,&actor.relationships.heading_offset_bits,4);
  // Damage already stores actor+64. Movement can compensate it when hitstop
  // expires before this body's first visit; retain that live value.
  if(reaction_pending_[i])reaction_pending_[i]=false;
  s.impact_horizontal=stagger[i].horizontal;s.impact_vertical=stagger[i].vertical;
  if(action_binding(i).policy==BattleActionPolicy::legacy_test){s.impact_horizontal=last_hit[i].normal.pre.stagger.horizontal;s.impact_vertical=last_hit[i].normal.pre.stagger.vertical;}
  s.scratch=common_hit_scratch_[i];s.down=stagger[i].down;s.invincible=stagger[i].invincible;
  s.count=stagger[i].count;s.accum=stagger[i].accum;s.status0=status[i].duration[0];s.back_flag=std::uint8_t(stagger[i].back_flag);s.first_voice=common_hit_first_voice_[i];
  s.jump=jump_held_[i]!=0;s.melee=melee_held_[i]!=0;s.shoot=shoot_held[i]!=0;s.x=input.x;s.z=input.z;
  s.contacts=contact_ledger[i].flags;for(unsigned v=0;v<4;++v)s.capacity[v]=damage_signed(contact_ledger[i].remaining[v]);
  const auto e=advance_battle_common_hit_motion(s);
  if(s.state==107&&e.next_state<0)steer_battle_offset(s.offset,input.x,input.z,s.turn_step);
  motion.speed=s.speed;motion.velocity[1]=s.vertical;motion.angles[1]=s.movement;walk_motion_[i].step=s.turn_step;
  std::memcpy(&actor.relationships.heading_offset_bits,&s.offset,4);common_hit_gravity_[i]=s.gravity;
  common_hit_scratch_[i]=s.scratch;common_hit_first_voice_[i]=s.first_voice!=0;status_aura_models[i]=s.last_hit_owner;
  stagger[i].horizontal=s.impact_horizontal;stagger[i].vertical=s.impact_vertical;
  last_hit[i].normal.pre.stagger.horizontal=s.impact_horizontal;last_hit[i].normal.pre.stagger.vertical=s.impact_vertical;
  stagger[i].down=s.down;stagger[i].invincible=s.invincible;stagger[i].count=s.count;stagger[i].accum=s.accum;
  contact_ledger[i].flags=s.contacts;for(unsigned v=0;v<4;++v)contact_ledger[i].remaining[v]=std::uint32_t(s.capacity[v]);
  *tick=s.frame;common_hit_second_tick_[i]=s.second_frame;
  // 428510 tail calls4212f0 before any421100 phase reset. Early returns do not call it.
  if(e.clock_advanced)cursors_[i].advance(data.state_frames_.at(reaction_animation_state(i,s.state)).at(s.phase),damage_signed(s.frame));
  for(const auto& event:e.events){
   if(event.kind==CommonHitEventKind::state)set_common_hit_action(i,unsigned(event.value),false);
   else if(event.kind==CommonHitEventKind::phase){
    // Native421100 resets the action clocks at phase selection. Supplied DAT
    // phases determine the pose; never create an extra animation phase.
    if(unsigned(event.value)>=phases.size())throw std::runtime_error("Common hit phase outside original DAT");
    *phase=unsigned(event.value);*tick=0;common_hit_second_tick_[i]=0;cursors_[i]={}; //421100 resets ADFC before the new DAT phase.
    if(uses_recovered_actor(i))bind_actor_animation_state(i,current_action_state(i),unsigned(event.value));
   }else if(event.kind==CommonHitEventKind::voice)queue_voice({i,unsigned(event.value),unsigned(event.priority),-1,-1,0x4223d0,unsigned(event.choice)&255u});
   else if(event.kind==CommonHitEventKind::sound)queue_sound({i,unsigned(event.value),actor.position});
   else if(event.kind==CommonHitEventKind::particle)queue_effect({i,unsigned(event.value),actor.position,actor.heading});
  }
 }
 void enter_throw_action(unsigned v,unsigned state){
  if(state!=135&&state!=186&&state!=187&&state!=188&&state!=189&&state!=190&&
     state!=113&&state!=115&&state!=121&&state!=133&&state!=215&&state!=503&&
     (state<191||state>199))throw std::runtime_error("Throw victim action not ported");
  reaction_animation_state(v,state);
  death_state[v]=death_phase[v]=death_tick[v]=death_wait_[v]=0;special_entry[v]={};
  ground_hit_state[v]=air_state[v]=guard_state[v]=recovery_state[v]=0;
  reaction_active_[v]=reaction_pending_[v]=recovery_from_guard_[v]=false;air_transition_[v]=false;
  elapsed[v]=-1;geometry[v]={};walking[v]=false;walk_tick[v]=0;
  if(state==503)special_entry[v]={503,0,0,0,0,false};
  else if(state>=191&&state<=199)death_state[v]=state;
  else {last_hit[v].normal.action.state=state;reaction_active_[v]=true;
   reaction_pending_[v]=state!=187&&state!=186&&state!=188&&state!=189&&state!=190;
   reaction_phase[v]=reaction_tick[v]=0;}
  if(uses_recovered_actor(v)||state==503||(enable_native_death&&battle_death_motion_state(state))){reset_native_state_metadata(v);common_hit_second_tick_[v]=0;bind_actor_animation_state(v,state);}
 }
 template<class Wall> std::uint8_t run_throw_operation(BattleWorld& world,unsigned attacker,unsigned operation,const BattleThrowRelease& input,const std::string& bone,Wall& wall){
  if(attacker>=4)throw std::out_of_range("Throw attacker");
  if(!bone.empty()&&!actor_assets(attacker).base_.find(bone))throw std::runtime_error("Missing throw attachment bone");
  // Validate states before damage/link mutation. Other character-specific victims
  // remain explicit unsupported actions until their handlers are recovered.
  auto supported=[](unsigned state){return state==135||state==186||state==187||state==188||
   state==189||state==190||state==113||state==115||state==121||state==133||
   state==215||state==503||(state>=191&&state<=199);};
  if(!supported(std::uint16_t(input.normal_state))||(operation==2&&!supported(std::uint16_t(input.death_state))))throw std::runtime_error("Throw victim action not ported");
  std::array<BattleThrowActor,4> records{};unsigned action_mask=0;
  for(unsigned i=0;i<4;++i){auto& r=records[i];auto& a=world.actors[i];const auto pair=target_availability[i].paired_actor;
   r.paired=pair<4?&records[pair]:nullptr;r.count=stagger[i].count;r.total=stagger[i].total;r.position=a.position;r.heading=a.heading;
   std::memcpy(&r.offset,&a.relationships.heading_offset_bits,4);r.horizontal=stagger[i].horizontal;r.vertical=stagger[i].vertical;
   r.blocked=std::uint8_t(a.motion.blocked);r.capture_mode=capture_modes[i];r.release_result=defeated_flags[i];
  }
  struct Host {
   DevelopmentAnimatedCombat& c;BattleWorld& world;std::array<BattleThrowActor,4>& records;unsigned attacker;const std::string& bone;Wall& wall;unsigned& mask;
   unsigned slot(BattleThrowActor& a)const{return unsigned(&a-records.data());}
   void attachment(std::uint32_t){c.attachment_bones[attacker]=bone;}
   void capture_notify(BattleThrowActor& a,BattleThrowActor& v,std::uint8_t mode){if(c.native_host_)c.native_host_->capture(slot(a),slot(v),mode);}
   void release_notify(BattleThrowActor& a,BattleThrowActor& v){if(c.native_host_)c.native_host_->release_held(slot(a),slot(v));}
   void action(BattleThrowActor& v,int state){c.enter_throw_action(slot(v),unsigned(state));mask|=1u<<slot(v);}
   void horizontal(BattleThrowActor& v,const std::array<float,3>& delta){const auto i=slot(v);world.actors[i].position=v.position;world.move_horizontal(i,delta,wall);v.position=world.actors[i].position;}
   void facing(BattleThrowActor& v){const auto& target=world.actors.at(world.actors[slot(v)].relationships.target);BattleFacing f{v.heading,v.offset};face_battle_target(f,v.position[0],v.position[2],target.position[0],target.position[2]);v.heading=f.heading;v.offset=f.offset;}
   std::int16_t damage(BattleThrowActor& a,BattleThrowActor& victim,std::int16_t base,std::int16_t death,std::uint8_t nonlethal){
    const auto at=slot(a),v=slot(victim);BattleDamageOutcomeState state;BattleDamageTotals totals;
    state.health=c.health[v];state.state=c.current_action_state(v);const auto& g=c.special_gauges[v];
    state.variant=g.mode;state.active=g.active2;state.threshold=g.limit0;state.charge=g.charge2;state.mode=c.scene_phase();state.network_mode=c.native_host_?1u:0u;state.team=v/2;state.attacker_id=at;state.victim_id=v;
    state.attacker_flag_c9=c.defeat_credit_flags[at];state.attacker_flag_b8=c.death_reset_flags[at][0];state.last_attacker=c.last_defeat_attacker;
    state.kills=c.statistics[at].kills;state.deaths=c.statistics[v].deaths;state.word7b8=c.stagger[v].accum;
    totals.attacker_damage=c.statistics[at].dealt;totals.attacker_hits=c.statistics[at].hits_dealt;totals.victim_damage=c.statistics[v].received;totals.victim_hits=c.statistics[v].hits_received;
    struct Events {Host& h;unsigned v;
     void score(unsigned team,unsigned amount){add_battle_team_score(h.c.teams_,team,amount,0,h.c.host_);}
     void event(unsigned code){h.c.host_.event(code);h.c.sound_requests.push_back({v,code,{},BattleSoundMode::Plain,false,true,false});}
     void defeat(){h.c.defeat_events_[v]=true;h.c.defeated_flags[v]=1;h.records[v].release_result=1;}
     void notify(unsigned at,unsigned victim){if(h.c.native_host_)h.c.native_host_->defeat(at,victim);}
    } events{*this,v};
    const auto result=apply_direct_damage(state,totals,base,damage_signed(c.combat_modifiers[at].attack),damage_signed(c.combat_modifiers[v].received),c.match_health_divisor_,world.actors[at].relationships.secondary_target==v,death,nonlethal,events);
    c.defeat_credit_flags[at]=state.attacker_flag_c9;c.death_reset_flags[at][0]=state.attacker_flag_b8;c.last_defeat_attacker=state.last_attacker;
    c.health[v]=state.health;c.stagger[v].accum=state.word7b8;c.statistics[at].kills=state.kills;c.statistics[v].deaths=state.deaths;
    c.statistics[at].dealt=totals.attacker_damage;c.statistics[at].hits_dealt=totals.attacker_hits;c.statistics[v].received=totals.victim_damage;c.statistics[v].hits_received=totals.victim_hits;
    return result;
   }
  } host{*this,world,records,attacker,bone,wall,action_mask};
  auto& a=records[attacker];std::uint8_t result=0;
  if(operation==0)result=capture_battle_actor(a,records.at(world.actors[attacker].relationships.secondary_target),input.normal_state,input.scaling,bone.empty()?0:1,host);
  else if(operation==1)result=damage_held_battle_actor(a,input.normal_state,input.damage,input.scaling,bone.empty()?0:1,host);
  else result=release_held_battle_actor(a,input,host);
  for(unsigned i=0;i<4;++i){const auto& r=records[i];auto& a=world.actors[i];a.position=r.position;a.heading=r.heading;a.motion.blocked=r.blocked;
   std::memcpy(&a.relationships.heading_offset_bits,&r.offset,4);target_availability[i].restricted=r.blocked!=0;target_availability[i].paired_actor=r.paired?unsigned(r.paired-records.data()):~0u;
   stagger[i].count=r.count;stagger[i].total=r.total;stagger[i].horizontal=r.horizontal;stagger[i].vertical=r.vertical;capture_modes[i]=r.capture_mode;
   if(action_mask&(1u<<i)){last_hit[i].normal.pre.stagger=stagger[i];last_hit[i].normal.pre.stagger.offset=r.offset;}
  }
  return result;
 }
 std::array<std::array<std::array<float,4>,2>,4> body_points_{};
 std::array<BattleNormalHitContact,4> body_attack_points_{};
 bool body_attack_points_ready_=false;
 const ActorFrameData& live_body_contact_frame(unsigned slot)const{
  const auto& data=actor_assets(slot);unsigned state=current_action_state(slot);
  if(!data.state_frames_.count(state))state=reaction_animation_state(slot,state);
  //+10 is a persistent DAT pointer. Rewound clocks do not rewind4212f0's handle.
  return data.state_frames_.at(state).at(projectile_owner_phase(slot)).frames.at(cursors_.at(slot).handle);
 }
 void snapshot_body_contact_geometry(const BattleWorld& world){
  if(!modern_contacts_)return;
  for(unsigned slot=0;slot<4;++slot){
   body_points_[slot]=body_contact_points(world,slot);
   const auto& frame=live_body_contact_frame(slot);
   const auto bone=frame.bone_index;
   if(!bone)throw std::runtime_error("Body frame references missing cached actor bone");
   //420880 transforms even extent0. A later hit replaces+10, but retains+C4/+D4.
   bind_actor_frame_geometry(frame,actor_bone_world(world,slot,bone),body_attack_points_[slot]);
  }
  body_attack_points_ready_=true;
 }
 bool prepare_attack_geometry(BattleWorld& world,unsigned a){
  const auto& data=actor_assets(a);
  const auto& phase=attack_phases(a).at(attack_phase[a]);
   auto cursor=cursors_[a];const auto& frame=cursor.advance(phase,elapsed[a]);
   if(!frame.extent){cursors_[a]=cursor;geometry[a]={};return false;}
   const auto transform=world_pose(world,a);
   if(uses_recovered_actor(a)){
    const auto bone=frame.bone_index;
    if(!bone)throw std::runtime_error("Attack frame references missing cached actor bone");
    auto next=geometry[a];bind_actor_frame_hit(frame,next);
    bind_actor_frame_geometry(frame,actor_bone_world(world,a,bone),next.geometry);
    cursors_[a]=cursor;geometry[a]=next;
   }else {auto skeleton=data.base_;prepare_actor_animated_hit(skeleton,cursors_[a],phase,elapsed[a],data.animations_.at(phase.value),actor_animation_key_time(elapsed[a],data.ticks_per_second_),transform,geometry[a]);}
   return true;
 }
 void resolve_attack_contacts(BattleWorld& world,unsigned a,KeiichiNormalProjectile* projectile=nullptr,const BattleHitPipelineInput* projectile_input=nullptr){
  const auto& pos=projectile?projectile->position:world.actors[a].position;
  auto consume=[&](unsigned v,std::uint16_t flag){if(projectile){projectile->contacts[v]=flag;--projectile->capacity[v];}else contact_ledger[a].consume(v,flag);};
   for(unsigned v=0;v<4;++v){
    if(projectile){if(projectile->contacts[v]||projectile->capacity[v]<=0)continue;}
    //637907 excludes body self only.637950 owns team/HP/flags admission.
    else if(v==a||(uses_recovered_actor(a)?!contact_ledger[a].eligible(v):contacted_[a][v]))continue;
    auto p=projectile?*projectile_input:geometry[a];const auto& victim=world.actors[v].position;
    if(!projectile&&uses_recovered_actor(a)){
     p.geometry=body_attack_points_[a];
     //Read+10 again for EACH victim, after preceding pool/body admissions.
     bind_actor_frame_hit(live_body_contact_frame(a),p);
    }
    if(uses_recovered_actor(a)){p.geometry.primary=body_points_[v][0];p.geometry.secondary=body_points_[v][1];}
    else {p.geometry.primary={victim[0],victim[1]+60,victim[2],1};p.geometry.secondary={victim[0],victim[1]+20,victim[2],1};}
    p.pre.attacker_id=a;p.pre.victim_id=v;p.pre.attacker_team=a/2;p.pre.victim_team=v/2;p.pre.stagger.resistance=combat_modifiers[v].stagger;
    p.pre.attack_power=combat_modifiers[a].attack;p.pre.defense=damage_signed(combat_modifiers[v].received);
    p.pre.damage_divisor=match_health_divisor_;p.pre.charge_scale=match_charge_scale_;
    p.blocked=world.actors[v].motion.blocked; //637995 victim+aecc, distinct from hitstop.
    p.direction.attack_x=pos[0];p.direction.attack_z=pos[2];
    p.direction.victim_x=victim[0];p.direction.victim_z=victim[2];
    p.direction.vector_x=projectile?projectile->velocity[0]:world.actors[a].motion.velocity[0];p.direction.vector_z=projectile?projectile->velocity[2]:world.actors[a].motion.velocity[2];
    p.pre.stagger.heading=world.actors[v].heading;
    p.pre.stagger.flags=uses_recovered_actor(a)?live_body_contact_frame(v).flags28:guard_flags[v];
    BattleHitPipelineState state;state.last_owner=last_hit[v].last_owner;state.normal.pre.status=status[v];state.normal.pre.stagger=stagger[v];state.normal.result.totals.health=health[v];state.normal.reaction.remaining=1;
    p.victim_target_id=world.actors[v].relationships.target; //637a4c DAT8000 applies to body contacts too.
    if(projectile){state.normal.reaction.remaining=unsigned(projectile->capacity[v]);state.normal.reaction.cooldown=projectile->contacts[v];}
    state.normal.pre.victim_charge=special_gauges[v].victim_state();
    state.normal.pre.attacker_charge=special_gauges[a].attacker_state();
    auto& totals=state.normal.result.totals;
    totals.attacker_damage=statistics[a].dealt;totals.attacker_hits=statistics[a].hits_dealt;
    totals.victim_damage=statistics[v].received;totals.victim_hits=statistics[v].hits_received;
    state.normal.result.death_stats.kills=statistics[a].kills;
    state.normal.result.death_stats.deaths=statistics[v].deaths;
    state.healed_total=statistics[a].healed_total;state.guard_count=statistics[v].guards;
    state.normal.pre.friendly.attacker_hits=statistics[a].friendly_hits;
    state.normal.pre.friendly.victim_flag=death_reset_flags[v][7]; //aebf
    state.normal.result.followup.points=statistics[a].followup_points;
    state.normal.result.followup.attacker_c9=defeat_credit_flags[a];
    state.normal.result.followup.attacker_b8=death_reset_flags[a][0];
    state.normal.result.followup.last_attacker=last_defeat_attacker;
    state.normal.result.followup.defeated=defeated_flags[v];
    state.normal.result.bonus_used=death_bonus_used[v];
    p.hit.network=native_host_?1:0;
    p.hit.targeted=(projectile?projectile->target:world.actors[a].relationships.target)==v;
    p.hit.limit=team_limits_[v/2];p.hit.mode=scene_phase(); //updated635d40 phase, not acquisition-time phase.
    p.pre.grounded_for_death=world.actors[v].grounded;
    if(uses_recovered_actor(a))p.pre.stagger.flag84=world.actors[v].grounded;
    state.normal.action.state=current_action_state(v);
    p.pre.stagger.current_state=state.normal.action.state;
    p.pre.stagger.target_same=world.actors[a].relationships.target==v; //638738 attacker+308; independent of projectile target.
    std::memcpy(&state.normal.pre.stagger.offset,&world.actors[v].relationships.heading_offset_bits,4);
    state.normal.action.word_684=std::uint32_t(native_contact_mode[v]);
    host_.visuals.clear();host_.feedback.reset(v);
    const auto path=apply_battle_hit_pipeline(state,random_,teams_,p,host_);
    sound_requests.insert(sound_requests.end(),host_.feedback.sounds.begin(),host_.feedback.sounds.end());
    host_.feedback.sounds.clear();
    // 637fd8..6380c8 ->435990: preserve DAT ID, contact position,
    // unquantized contact direction and victim owner through the renderer.
    // Support/guard/miss branches emit no ordinary impact visual.
    effect_requests.insert(effect_requests.end(),host_.visuals.begin(),host_.visuals.end());
    host_.visuals.clear();
    if(path==BattleHitPath::guard||path==BattleHitPath::normal)native_contact_mode[v]=damage_signed(state.normal.action.word_684);
    if(path==BattleHitPath::support){
     consume(v,0x80);
     health[v]=state.normal.result.totals.health;
     status[v]=state.normal.pre.status;
     statistics[a].healed_total=state.healed_total;
     last_hit[v]=state;
     continue;
    }
    if(path==BattleHitPath::guard){
     statistics[v].guards=state.guard_count;
     if(uses_recovered_actor(a)){consume(v,std::uint16_t(2|((p.pre.stagger.flags&0x8000)?0x100:0)));contact_ledger[v].clear_flags(2);}
     ++guards;last_hit[v]=state;
     //637f51..637fd3 records contact2/capacity and victim statistics only.
     //63776d/63793c then continue to the next victim. Original actor control
     //queries choose391/392 on the following visit, including attacks with
     //no guard query and Mion's counter/rebound. Never replace that policy here.
     if(!uses_recovered_actor(v)){guard_state[v]=391;guard_phase[v]=guard_tick[v]=0;}
     if(projectile)continue;
     contacted_[a][v]=true;
     if(!uses_recovered_actor(a)){elapsed[a]=-1;guard_state[a]=392;guard_phase[a]=guard_tick[a]=0;break;}
     continue;
    }
    if(path==BattleHitPath::normal){
     statistics[a].followup_points=state.normal.result.followup.points;
     death_bonus_used[v]=state.normal.result.bonus_used;
     statistics[a].friendly_hits=state.normal.pre.friendly.attacker_hits;
     death_reset_flags[v][7]=std::uint8_t(state.normal.pre.friendly.victim_flag);
     death_reset_flags[a][0]=state.normal.result.followup.attacker_b8;
     defeat_credit_flags[a]=state.normal.result.followup.attacker_c9;
     last_defeat_attacker=state.normal.result.followup.last_attacker;
     defeated_flags[v]=state.normal.result.followup.defeated;
     special_gauges[v].store_victim(state.normal.pre.victim_charge);
     special_gauges[a].store_attacker(state.normal.pre.attacker_charge);
     if(uses_recovered_actor(a))consume(v,1);
     statistics[a].dealt=totals.attacker_damage;statistics[a].hits_dealt=totals.attacker_hits;
     statistics[v].received=totals.victim_damage;statistics[v].hits_received=totals.victim_hits;
     statistics[a].kills=state.normal.result.death_stats.kills;
     statistics[v].deaths=state.normal.result.death_stats.deaths;
     // A normal hit with no stagger/death N preserves the current body.
     // In particular Mion370's HP0/stagger0 contact freezes an existing392.
     status[v]=state.normal.pre.status;stagger[v]=state.normal.pre.stagger;health[v]=state.normal.result.totals.health;contacted_[a][v]=true;++hits;last_hit[v]=state;
     //638784..6387de stores victim+64 during the normal stagger pass,
     // before HP/death admission. Mirror it now, including nonlethal hits;
     // the next handler still owns its existing pending reaction/clock.
     std::memcpy(&world.actors[v].relationships.heading_offset_bits,&stagger[v].offset,4);
     if(!projectile)stop_ticks[a]=state.normal.pre.stops.attack_stop;
     stop_ticks[v]=state.normal.pre.stops.victim_stop;long_stop_ticks[v]=state.normal.pre.stops.long_stop;
     if(state.normal.result.survival.transition&&(state.normal.action.state==502||state.normal.action.state==503)){
      special_entry[v]={state.normal.action.state,0,0,0,0,false};
      death_state[v]=death_phase[v]=death_tick[v]=death_wait_[v]=0;
      ground_hit_state[v]=air_state[v]=guard_state[v]=recovery_state[v]=0;
      reaction_active_[v]=reaction_pending_[v]=recovery_from_guard_[v]=false;air_transition_[v]=false;
      elapsed[v]=-1;geometry[v]={};walking[v]=false;walk_tick[v]=0;
      reset_native_state_metadata(v);bind_actor_animation_state(v,special_entry[v].state);
     }
     if(special_entry[v].state&&special_entry[v].state!=state.normal.action.state)special_entry[v]={};
     if(damage_signed(health[v])<=0){
      special_entry[v]={};
      defeat_events_[v]=state.normal.result.followup.defeated!=0; //aeca already stored exactly above.
      ground_hit_state[v]=guard_state[v]=guard_flags[v]=0;death_state[v]=state.normal.action.state;death_phase[v]=death_tick[v]=death_wait_[v]=0;
      if(enable_native_death){reset_native_state_metadata(v);common_hit_second_tick_[v]=0;bind_actor_animation_state(v,death_state[v]);}
      // 638ef6..638f84 turns the victim toward the lethal impact before death motion.
      std::memcpy(&world.actors[v].relationships.heading_offset_bits,&stagger[v].offset,4);
      reaction_active_[v]=reaction_pending_[v]=recovery_from_guard_[v]=false;
      air_state[v]=recovery_state[v]=0;air_transition_[v]=false;
      elapsed[v]=-1;geometry[v]={};walking[v]=false;walk_tick[v]=0;
     }
     if(damage_signed(health[v])>0&&state.normal.result.survival.transition&&
        battle_common_hit_motion_state(state.normal.action.state)){
      reaction_animation_state(v,state.normal.action.state);
      set_common_hit_action(v,state.normal.action.state,true);recovery_from_guard_[v]=false;
     }
    }
   }
 }
};
}
