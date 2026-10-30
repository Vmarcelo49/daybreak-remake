#pragma once
#include "weapon_item_data.hpp"
#include "actor_animated_hit.hpp"
#include "actor_animation_clock.hpp"
#include "actor_animation_settings.hpp"
#include "actor_skin.hpp"
#include "prepared_actor_controller_pose.hpp"
#include <map>
#include <memory>
namespace daybreak {
// Immutable after construction; per-actor clocks and cursors live in combat.
// This describes assets only, not the character's action-handler implementation.
struct BattleActorAssets {
 std::shared_ptr<const WeaponItemData> weapon_item;
 ActorSkeleton base_;std::vector<ActorPhaseData> attack_phases_;
 std::map<unsigned,std::array<std::uint32_t,2>> state_priorities_;
 std::map<unsigned,unsigned> animation_durations_,animation_last_keys_;
 std::array<ActorAnimationSettings,256> animation_settings_;
 std::map<unsigned,std::vector<ActorPhaseData>> guard_data_,state_frames_;
 double ticks_per_second_=4800;
 std::map<unsigned,std::vector<unsigned>> recovery_durations_,state_animations_;
 std::map<unsigned,XAnimationKeys> animations_;
 std::array<std::uint32_t,6> parameters{}; // DAT108..11f; special thresholds324/32c
 unsigned idle_animation_=0,registered_animation_count=0,serialized_animation_count=0;
 ActorSkin skin;
 PreparedActorControllerPose prepared_pose;
 BattleActorAssets(const std::vector<std::uint8_t>& model,const std::vector<std::uint8_t>& frames,std::shared_ptr<const WeaponItemData> item=nullptr):weapon_item(std::move(item)){
  auto roots=XObjectReader(model).read();ticks_per_second_=actor_ticks_per_second(roots);base_=ActorSkeleton::decode(roots);base_.update();skin=ActorSkin::decode(roots,base_);
  // d3dx9_25 loader 43c2df prepends sets; 43c409 registers head first.
  // DAT values are zero-based controller indices, never Anim-N suffixes.
  for(unsigned id=0;id<256;++id){animations_[id]={};animation_last_keys_[id]=0;animation_durations_[id]=0;}
  unsigned index=0;
  for(auto it=roots.rbegin();it!=roots.rend();++it)if(it->type=="AnimationSet"&&!it->reference){
   auto keys=read_x_animation_keys(*it);
   //43c2df registers only successfully created sets; no-track X sets are omitted.
   if(keys.tracks.empty())continue;
   if(index>=256)throw std::runtime_error("Too many model animation sets");
   unsigned end=0;for(const auto& track:keys.tracks)end=std::max(end,track.keys.back().time);
   animation_last_keys_[index]=end;animations_[index++]=std::move(keys);
  }
  registered_animation_count=index;
  auto data=read_actor_frame_data(frames);parameters=data.parameters;
  const auto settings=read_actor_animation_settings(frames,data.consumed);serialized_animation_count=unsigned(settings.animations.size());
  animation_settings_=actor_runtime_animation_settings(settings);
  //41e180 fills period metadata only for serialized records;64e8b0 returns0 for missing sets.
  for(unsigned id=0;id<serialized_animation_count;++id)animation_durations_[id]=actor_animation_frame_count(animation_last_keys_.at(id),ticks_per_second_);
  if(animations_.size()>animation_settings_.size())throw std::runtime_error("Too many model animation sets");
  for(const auto& state:data.states){state_frames_[state.id]=state.phases;state_priorities_[state.id]={state.a,state.b};}
  //41e180 binds every DAT row's matrix pointer once, before live cursor use.
  //Keep missing unused rows unbound; a live geometry read reports the error.
  for(auto& state:state_frames_)for(auto& phase:state.second)for(auto& frame:phase.frames)frame.bone_index=base_.find(frame.bone);
  for(const auto& state:state_frames_)if(state.first>=390&&state.first<=392)guard_data_[state.first]=state.second;
  //41e180 clears a fixed state slot before each record; duplicate IDs replace all phases.
  for(const auto& state:state_frames_)for(const auto& phase:state.second)state_animations_[state.first].push_back(phase.value);
  if(state_animations_.count(0)&&!state_animations_[0].empty())idle_animation_=state_animations_[0][0];
  for(const auto& state:state_frames_)if(state.first==118||state.first==119||state.first==120||state.first==124||state.first==128)
   for(const auto& phase:state.second)recovery_durations_[state.first].push_back(animation_durations_.at(phase.value));
  for(const auto& state:state_frames_)if(state.first==300)attack_phases_=state.second;
  for(const auto& phase:attack_phases_)if(phase.frames.empty()||!animations_.count(phase.value))throw std::runtime_error("Invalid attack animation index");
  prepared_pose=PreparedActorControllerPose(base_,animations_,ticks_per_second_);
 }
};
using BattleActorAssetSlots=std::array<std::shared_ptr<const BattleActorAssets>,4>;
inline BattleActorAssetSlots repeated_battle_assets(const std::vector<std::uint8_t>& model,const std::vector<std::uint8_t>& frames){
 auto data=std::make_shared<const BattleActorAssets>(model,frames);return {{data,data,data,data}};
}
}
