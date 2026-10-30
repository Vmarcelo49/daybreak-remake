#pragma once
#include "legacy_snapshot_animation.hpp"

namespace daybreak {
//DAT/model adapter shared by every roster/weapon slot. This does not admit a
//combat state or evaluate bones while applying a network packet.
//Assets is the immutable BattleActorAssets interface; keeping the adapter
//generic also permits a controlled DAT table fixture without a renderer.
template<class Assets> inline void configure_legacy_snapshot_assets(LegacySnapshotAnimationActor& actor,unsigned character,unsigned weapon,const Assets& assets){
 actor.animation.configure(character,weapon,assets.animation_settings_);
 actor.period.fill(0); //Unloaded native4231c0 records have cap0.
 for(const auto& entry:assets.animation_durations_){
  if(entry.first>=256)throw std::out_of_range("Native snapshot model animation count");
  actor.period[entry.first]=legacy_snapshot_signed(entry.second);
 }
 for(unsigned id=0;id<256;++id)actor.hold[id]=assets.animation_settings_[id].hold_phase;
}
template<class Assets> inline bool resolve_legacy_snapshot_tracks(const LegacySnapshotAnimationActor& actor,const Assets& assets,std::array<unsigned,2>& output){
 std::array<unsigned,2> result{};
 for(unsigned layer=0;layer<2;++layer){const unsigned body=layer==1?0u:1u;
  if(actor.state[body]<0)return false;
  const auto found=assets.state_frames_.find(unsigned(actor.state[body]));
  if(found==assets.state_frames_.end()||actor.phase[body]>=found->second.size())return false;
  auto id=found->second[actor.phase[body]].value;if(id>=256)return false;result[layer]=id;
 }
 output=result;return true;
}
template<class Assets> inline bool step_legacy_snapshot_assets(LegacySnapshotAnimationActor& actor,const Assets& assets){
 std::array<unsigned,2> selected;if(!resolve_legacy_snapshot_tracks(actor,assets,selected))return false;
 actor.step(selected);return true;
}
template<class Assets> inline std::map<std::string,std::string> legacy_snapshot_texture_remaps(const LegacySnapshotAnimationActor& actor,const Assets& assets){
 std::array<unsigned,2> selected;
 if(!resolve_legacy_snapshot_tracks(actor,assets,selected))throw std::out_of_range("Native snapshot DAT state/phase");
 //41f91f resolves PRIMARY state/phase, independently of the bound ID.
 return actor_texture_remaps(assets.animation_settings_[selected[1]],actor.frame[0]);
}
}
