#pragma once
#include "asset_search_path.hpp"
#include "battle_camera_view.hpp"
#include "battle_effect_animation.hpp"
#include "actor_animation_clock.hpp"
#include <algorithm>
#include <cmath>
#include <limits>

namespace daybreak {

// 632cd0 loads data/camera/01.x and retains the combined Box01/Box02 frames.
// 6333b0 reads them after both cloned D3DX controller tracks are set to the
// same selected animation and time. This asset contains six serialized sets.
struct BattleAnimatedCameraAsset {
 struct Track {unsigned bone=0;BattleEffectSrtTrack keys;};
 struct Set {std::vector<Track> tracks;unsigned last_key=0;float period=0;std::string name;};
 ActorSkeleton base;
 std::vector<Set> sets;
 unsigned eye_bone=0,look_bone=0;
 double ticks_per_second=4800;

 static BattleAnimatedCameraAsset decode(const std::vector<std::uint8_t>& bytes){
  BattleAnimatedCameraAsset result;
  const auto roots=XObjectReader(bytes).read();
  result.base=ActorSkeleton::decode(roots);result.base.update();
  result.eye_bone=result.base.find("Box01");result.look_bone=result.base.find("Box02");
  if(!result.eye_bone||!result.look_bone)throw std::runtime_error("Camera X lacks Box01/Box02");
  result.ticks_per_second=actor_ticks_per_second(roots);
  for(const auto& object:roots)if(object.type=="AnimationSet"&&!object.reference){
   const auto animation=read_x_animation_keys(object);Set set;set.name=animation.name;
   for(const auto& track:animation.tracks){
    const auto bone=result.base.find(track.bone);
    if(!bone)throw std::runtime_error("Camera animation references unknown frame");
    for(const auto& prior:set.tracks)if(prior.bone==bone)throw std::runtime_error("Duplicate camera animation frame");
    set.last_key=std::max(set.last_key,track.keys.back().time);
    set.tracks.push_back({bone,decode_battle_effect_animation(track,result.ticks_per_second)});
   }
   set.period=float(double(set.last_key)/result.ticks_per_second);
   result.sets.push_back(std::move(set));
  }
  if(result.sets.empty())throw std::runtime_error("Camera X has no animation sets");
  // The bundled D3DX9_25 X loader registers this file's AnimationSets in
  // reverse root-object order: native index0 is serialized Anim-6, not Anim-1.
  std::reverse(result.sets.begin(),result.sets.end());
  return result;
 }
 static BattleAnimatedCameraAsset load(AssetSearchPath& assets){
  return decode(assets.read("data/camera/01.x").bytes);
 }
 ActorSkeleton sample(unsigned index,float seconds)const{
  const auto& set=sets.at(index);if(!std::isfinite(seconds))throw std::runtime_error("Invalid camera animation time");
  // D3DXPLAY_LOOP=0 wraps the FLOAT-second period stored by X ingestion.
  const double tick=secondary_animation_loop_key_time(seconds,ticks_per_second,set.last_key);
  auto pose=base;
  for(const auto& track:set.tracks)pose.bones[track.bone].local=sample_battle_effect_animation(track.keys,tick,ticks_per_second);
  update_secondary_animation_world(pose);return pose;
 }
};

struct BattleAnimatedCameraState {
 int animation=-1;bool active=false,special=false;
 float time=0,end=0,yaw=0;
 // 633140 always writes yaw, including an invalid animation request. A new
 // valid index or a transition from ordinary mode resets the track position.
 void select(int requested,float heading_plus_offset,const BattleAnimatedCameraAsset& asset){
  volatile float offset=heading_plus_offset+90.f;
  volatile float product=-offset*3.1415927410125732421875f;
  yaw=product/180.f;
  if((requested!=animation||!active)&&requested>=0&&unsigned(requested)<asset.sets.size()){
   animation=requested;active=true;special=false;time=0;end=asset.sets[unsigned(requested)].period;
  }
 }
 // 6331e0. The original clears the selected index and animated byte; special
 // byte95 is also cleared if it was set by the separate held-actor route.
 void clear(){animation=-1;active=false;special=false;}
 // 633220 tests time before adding .016 and deliberately does not clamp.
 void advance(){if(active&&time<end){volatile float next=time+.01600000075995922088623046875f;time=next;}}
};

// 6333b0: Transform (1,0,0) by the two combined X frame matrices, rotate
// around Y by camera+88, and translate by camera+18 smoothed anchor.
inline BattleCameraView animated_battle_camera_view(const BattleAnimatedCameraAsset& asset,
 const BattleAnimatedCameraState& state,const std::array<float,3>& smoothed_anchor){
 if(!state.active||state.animation<0||unsigned(state.animation)>=asset.sets.size())
  throw std::logic_error("Animated camera selection unavailable");
 const auto pose=asset.sample(unsigned(state.animation),state.time);
 const float c=float(std::cos(double(state.yaw))),s=float(std::sin(double(state.yaw)));
 auto point=[&](unsigned bone){const auto& m=pose.bones[bone].world;
  volatile float x=m[0]+m[12],y=m[1]+m[13],z=m[2]+m[14];
  volatile float rx=x*c+z*s,rz=-x*s+z*c;
  return std::array<float,3>{smoothed_anchor[0]+rx,smoothed_anchor[1]+y,smoothed_anchor[2]+rz};
 };
 return {point(asset.eye_bone),point(asset.look_bone)};
}
}
