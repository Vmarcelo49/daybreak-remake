#pragma once
#include "asset_search_path.hpp"
#include "development_animated_combat.hpp"
#include "x_compression.hpp"
#include "x_animation_keys.hpp"
#include "actor_animation_settings.hpp"
#include "actor_animation_clock.hpp"
#include "battle_effect_animation.hpp"
#include "legacy_normalize.hpp"
#include <algorithm>
#include <cstdio>
#include <map>
#include <memory>

namespace daybreak {
// 42eba0 loads data/effect/%03d.dat; manager vtable+8 (42f5e0) maps an
// effect registration to group=id/10 and its per-group X model.
// 436090 fixes the first frame of variant ordinal id%10; 436150 uses that
// frame's render flags and the group's texture events throughout its lifetime.
struct BattleVisualEffectAsset {
 unsigned registration=0,duration=0;
 std::string dat_path,model_path;
 std::vector<std::uint8_t> model;
 XAnimationKeys animation;
 ActorSkeleton skeleton;
 std::vector<unsigned> animation_bones;
 std::vector<BattleEffectSrtTrack> sampled_animation;
 ActorFrameFile variants;ActorAnimationSection settings;
 std::size_t animation_trailing_bytes=0;
 double ticks_per_second=4800;unsigned last_key=0;
 const ActorFrameData& render_frame()const{
  const auto& variant=variants.states.at(registration%10);
  return variant.phases.at(0).frames.at(0);
 }
};
inline BattleVisualEffectAsset load_battle_visual_effect_asset(AssetSearchPath& search,unsigned registration){
 if(registration>=1000)throw std::invalid_argument("Effect registration outside original manager table");
 const unsigned group=registration/10;
 BattleVisualEffectAsset result;result.registration=registration;
 char path[64];std::snprintf(path,sizeof path,"data/effect/%03u.dat",group);result.dat_path=path;
 const auto data=search.read(result.dat_path).bytes;
 result.variants=read_actor_frame_data(data,false);
 result.settings=read_actor_animation_settings(data,result.variants.consumed,1);
 // Original42eec0 consumes one record regardless of the declared count and
 // leaves any later records unread (several supplied DAT files contain them).
 result.animation_trailing_bytes=data.size()-result.settings.consumed;
 // Validate the group's registered base record. A dynamic request may name
 // an unregistered ordinal; spawn rejects it without aborting the match.
 (void)result.variants.states.at(0).phases.at(0).frames.at(0);
 if(data.size()<264)throw std::runtime_error("Truncated effect DAT: "+result.dat_path);
 const auto end=std::find(data.begin()+4,data.begin()+264,0);
 if(end==data.begin()+264||end==data.begin()+4)throw std::runtime_error("Invalid effect model name: "+result.dat_path);
 const std::string model(data.begin()+4,end);
 if(model.find('/')!=std::string::npos||model.find('\\')!=std::string::npos||model.find(':')!=std::string::npos)
  throw std::runtime_error("Effect model leaves its DAT directory");
 result.model_path="data/effect/"+model;result.model=search.read(result.model_path).bytes;
 if(compressed_x(result.model))result.model=expand_x(result.model);
 const auto roots=XObjectReader(result.model).read();
 result.skeleton=ActorSkeleton::decode(roots);result.skeleton.update();
 result.ticks_per_second=actor_ticks_per_second(roots);
 for(auto object=roots.rbegin();object!=roots.rend();++object)if(object->type=="AnimationSet"&&!object->reference){
  result.animation=read_x_animation_keys(*object);break;
 }
 for(const auto& track:result.animation.tracks){
  const auto bone=result.skeleton.find(track.bone);
  if(!bone)throw std::runtime_error("Effect animation references unknown frame: "+track.bone);
  if(std::find(result.animation_bones.begin(),result.animation_bones.end(),bone)!=result.animation_bones.end())
   throw std::runtime_error("Duplicate effect animation output: "+track.bone);
  result.animation_bones.push_back(bone);result.sampled_animation.push_back(decode_battle_effect_animation(track,result.ticks_per_second));
  result.last_key=std::max(result.last_key,track.keys.back().time);
 }
 // 42eec0: controller AnimationSet(0).GetPeriod / float .016, truncated.
 result.duration=actor_animation_frame_count(result.last_key,result.ticks_per_second);
 return result;
}
inline double battle_visual_effect_key_time(const BattleVisualEffectAsset& asset,unsigned frame){
 // 436150 stores float(age)*float(.016) before 64ebc0 SetTrackPosition.
 volatile float age=float(projectile_signed(frame));volatile float seconds=age*.01600000075995922088623046875f;
 return secondary_animation_loop_key_time(seconds,asset.ticks_per_second,asset.last_key);
}
inline ActorSkeleton sample_battle_visual_effect_pose(const BattleVisualEffectAsset& asset,unsigned frame,std::vector<unsigned>* cursors=nullptr){
 auto pose=asset.skeleton;const double time=battle_visual_effect_key_time(asset,frame);
 if(cursors)cursors->resize(asset.sampled_animation.size());
 for(unsigned i=0;i<asset.animation.tracks.size();++i)
  pose.bones[asset.animation_bones[i]].local=sample_battle_effect_animation(asset.sampled_animation[i],time,asset.ticks_per_second,cursors?&(*cursors)[i]:nullptr);
 update_secondary_animation_world(pose);return pose;
}
// Retained raw-key inspection helper. Rendering uses the sampled hierarchy below.
inline const LegacyMatrix* battle_visual_effect_bone(const BattleVisualEffectAsset& asset,const std::string& bone,unsigned frame){
 for(const auto& track:asset.animation.tracks)if(track.bone==bone){
  double time=actor_animation_key_time(projectile_signed(frame),asset.ticks_per_second);
  if(asset.last_key)time=std::fmod(time,double(asset.last_key));
  auto key=std::upper_bound(track.keys.begin(),track.keys.end(),time,[](double t,const XMatrixKey& sample){return t<sample.time;});
  if(key!=track.keys.begin())--key;
  return &key->matrix;
 }
 return nullptr;
}
class BattleVisualEffects {
 AssetSearchPath* search_;
 std::map<unsigned,std::shared_ptr<const BattleVisualEffectAsset>> assets_;
public:
 struct Live {unsigned registration=0,owner=0,frame=0;std::array<float,3> position{};float heading=0;
  std::shared_ptr<const BattleVisualEffectAsset> asset;float pitch=0;std::array<float,3> direction{{1,0,0}};
  mutable ActorSkeleton pose_cache;mutable unsigned pose_frame=0;mutable bool pose_valid=false;
  mutable std::vector<unsigned> pose_cursors;
  const ActorSkeleton& sampled_pose()const{
   if(!pose_valid||pose_frame!=frame){pose_cache=sample_battle_visual_effect_pose(*asset,frame,&pose_cursors);pose_frame=frame;pose_valid=true;}
   return pose_cache;
  }
 };
 std::vector<Live> live;
 unsigned spawned=0,released=0,skipped_unregistered=0;
 explicit BattleVisualEffects(AssetSearchPath& search):search_(&search){}
 const std::shared_ptr<const BattleVisualEffectAsset>& asset_for(unsigned registration){
  const auto found=assets_.find(registration);if(found!=assets_.end())return found->second;
  auto loaded=std::make_shared<const BattleVisualEffectAsset>(load_battle_visual_effect_asset(*search_,registration));
  return assets_.emplace(registration,std::move(loaded)).first->second;
 }
 bool spawn_direction(unsigned registration,unsigned owner,const std::array<float,3>& position,const std::array<float,3>& direction,float heading=0,float pitch=0){
  char path[64];std::snprintf(path,sizeof path,"data/effect/%03u.dat",registration/10);
  if(registration>=1000||!search_->contains(path)){++skipped_unregistered;return false;}
  const auto& asset=asset_for(registration);
  if(registration%10>=asset->variants.states.size()){++skipped_unregistered;return false;}
  live.push_back({registration,owner,0,position,heading,asset,pitch,actor_controller_normalize3(direction)});++spawned;return true;
 }
 bool spawn(unsigned registration,unsigned owner,const std::array<float,3>& position,float heading=0,float pitch=0){
  const float cp=legacy_trig(pitch,false);
  return spawn_direction(registration,owner,position,{legacy_trig(heading,false)*cp,legacy_trig(pitch,true),legacy_trig(heading,true)*cp},heading,pitch);
 }
 void spawn_requests(const DevelopmentAnimatedCombat& combat){
  for(const auto& request:combat.effect_requests){
   if(request.direction)spawn_direction(request.id,request.actor,request.position,*request.direction);
   else spawn(request.id,request.actor,request.position,request.heading,request.pitch);
  }
 }
 void advance(const BattleWorld* world=nullptr){
  for(auto& effect:live){
   if(world&&effect.registration/10==36)effect.position=world->actors.at(effect.owner).position;
   ++effect.frame;
  }
  const auto end=std::remove_if(live.begin(),live.end(),[&](const Live& effect){
   if(projectile_signed(effect.frame)<projectile_signed(effect.asset->duration))return false;++released;return true;});
  live.erase(end,live.end());
 }
};
}
