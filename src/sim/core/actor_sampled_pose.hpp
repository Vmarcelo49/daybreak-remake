#pragma once
#include "actor_key_pose.hpp"
#include "actor_srt.hpp"
#include "actor_keyframe_interpolation.hpp"
#include "legacy_quaternion_matrix.hpp"
namespace daybreak {
// Source-key interpolation clamps at each track's endpoints. Callers apply
// animation-set periods where needed; controller blending remains separate.
inline LegacyMatrix sample_actor_matrix(const XMatrixTrack& track,double time,double ticks=0) {
    if(!std::isfinite(time)||track.keys.empty())throw std::runtime_error("Invalid sample time or empty track");
    // Native X keys store FLOAT seconds; integer source ticks are not the runtime key clock.
    const double query=ticks>0?time/ticks:time;
    auto key_time=[&](const XMatrixKey& key){return ticks>0?double(float(double(key.time)/ticks)):double(key.time);};
    auto hi=std::lower_bound(track.keys.begin(),track.keys.end(),query,
        [&](const XMatrixKey& key,double t){return key_time(key)<t;});
    if(hi==track.keys.end())return compose_actor_keyframe(decompose_actor_key_srt(track.keys.back().matrix));
    if(hi==track.keys.begin()||key_time(*hi)==query)return compose_actor_keyframe(decompose_actor_key_srt(hi->matrix));
    const auto& lo=*(hi-1);
    const float t=float((query-key_time(lo))/(key_time(*hi)-key_time(lo)));
    return compose_actor_keyframe(interpolate_actor_key_srt(decompose_actor_key_srt(lo.matrix),decompose_actor_key_srt(hi->matrix),t));
}
inline void apply_actor_sampled_pose(ActorSkeleton& skeleton,const XAnimationKeys& animation,double time){
    std::vector<std::pair<unsigned,LegacyMatrix>> updates;
    for(const auto& track:animation.tracks){
        auto id=skeleton.find(track.bone);
        if(!id)throw std::runtime_error("Animation references unknown bone");
        if(std::any_of(updates.begin(),updates.end(),[&](const auto& u){return u.first==id;}))throw std::runtime_error("Duplicate bone animation track");
        updates.emplace_back(id,sample_actor_matrix(track,time));
    }
    for(const auto& update:updates)skeleton.bones[update.first].local=update.second;
    skeleton.update();
}
// 64ddd0 registers Bip01* outputs with controller1, every other bone with0.
// Two independent sampled channels; original crossfade weights remain separate work.
inline unsigned actor_animation_channel(const std::string& name){return name.compare(0,5,"Bip01")==0?1u:0u;}
inline void apply_actor_channel_pose(ActorSkeleton& skeleton,const XAnimationKeys& lower,double lower_time,const XAnimationKeys& upper,double upper_time){
 for(unsigned channel=0;channel<2;++channel){
  const auto& animation=channel?upper:lower;const double time=channel?upper_time:lower_time;
  for(const auto& track:animation.tracks)if(actor_animation_channel(track.bone)==channel){
   const auto id=skeleton.find(track.bone);if(!id)throw std::runtime_error("Channel animation references unknown bone");
   skeleton.bones[id].local=sample_actor_matrix(track,time);
  }
 }
 skeleton.update();
}
// 420b30 builds Ry(+pi * actor68 /180);64e360 calls23780 on Spine's
// LOCAL matrix before combining with its parent. This is not a world-space yaw.
inline void apply_actor_spine_yaw(ActorSkeleton& skeleton,float degrees){
 const auto spine=skeleton.find("Bip01_Spine");if(!spine)return;
 volatile float product=degrees*3.1415927410125732421875f;volatile float radians=product/180.f;
 const float c=float(std::cos(double(radians))),s=float(std::sin(double(radians)));
 const LegacyMatrix rotation{c,0,-s,0,0,1,0,0,s,0,c,0,0,0,0,1};
 skeleton.bones[spine].local=multiply_matrix_simd_order(skeleton.bones[spine].local,rotation);
 skeleton.update();
}
}
