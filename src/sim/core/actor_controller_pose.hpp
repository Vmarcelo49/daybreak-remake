#pragma once
#include "actor_animation_service.hpp"
#include "actor_sampled_pose.hpp"
#include "actor_controller_srt.hpp"
#include <map>
namespace daybreak {
// Native controller mixtures normalize weights and use normalized linear
// quaternion accumulation with antipodal correction (DLL retained oracle).
struct ActorSrtMix {
 float weight=0;
 ActorSrt sum{};
 void add(const ActorSrt& value,float amount){
  if(!(amount>0))return;
  float sign=1;
  if(weight>0){float dot=0;for(unsigned i=0;i<4;++i)dot+=sum.rotation[i]*value.rotation[i];if(dot<0)sign=-1;}
  for(unsigned i=0;i<3;++i){sum.scale[i]+=value.scale[i]*amount;sum.translation[i]+=value.translation[i]*amount;}
  for(unsigned i=0;i<4;++i)sum.rotation[i]+=value.rotation[i]*(amount*sign);
  weight+=amount;
 }
 ActorSrt value()const{
  if(!(weight>0))throw std::logic_error("Empty actor controller mixture");
  auto result=sum;
  for(unsigned i=0;i<3;++i){result.scale[i]/=weight;result.translation[i]/=weight;}
  float squared=0;for(auto q:result.rotation)squared+=q*q;
  if(!(squared>0))throw std::runtime_error("Degenerate actor quaternion mixture");
  const float length=std::sqrt(squared);for(auto& q:result.rotation)q/=length;
  return result;
 }
};
inline LegacyMatrix compose_actor_srt(const ActorSrt& value){
 auto q=value.rotation;q[3]=-q[3];auto result=quaternion_matrix_scalar24(q);
 for(unsigned r=0;r<3;++r){for(unsigned c=0;c<3;++c)result[r*4+c]*=value.scale[r];result[12+r]=value.translation[r];}
 return result;
}
inline double actor_controller_key_time(float seconds,double ticks,unsigned last_key){
 double time=double(seconds);
 // The set period is rounded to FLOAT seconds; X key times remain source ticks.
 const double period=last_key?double(float(double(last_key)/ticks)):0;
 if(period>0){time=std::fmod(time,period);if(time<0)time+=period;}
 return time*ticks;
}
inline ActorSkeleton evaluate_actor_controller_pose(const ActorSkeleton& base,const ActorAnimationService& service,
 const std::map<unsigned,XAnimationKeys>& animations,const std::map<unsigned,unsigned>& last_keys,double ticks,float spine_yaw){
 // base is the retained output pose on later evaluations. Sparse sets
 // leave unnamed matrices intact, as the native D3DX controller does.
 auto pose=base;
 for(unsigned layer=0;layer<2;++layer){
  const auto& channel=service.channels[layer];std::vector<unsigned> active;
  for(unsigned id=0;id<256;++id)if(channel.tracks[id].weight>0)active.push_back(id);
  if(active.size()==1){
   const auto id=active[0];const auto time=actor_controller_key_time(channel.position[id],ticks,last_keys.at(id));
   for(const auto& track:animations.at(id).tracks)if(actor_animation_channel(track.bone)==layer){
    const auto bone=pose.find(track.bone);if(!bone)throw std::runtime_error("Controller references unknown actor bone");
    pose.bones[bone].local=compose_actor_controller_srt(sample_actor_controller_srt(actor_controller_times(track,ticks),actor_controller_keys(track),time/ticks,ticks));
   }
  }else if(!active.empty()){
   std::vector<ActorControllerSrtMix> mixes(pose.bones.size());
   for(auto id:active){const auto time=actor_controller_key_time(channel.position[id],ticks,last_keys.at(id));
    for(const auto& track:animations.at(id).tracks)if(actor_animation_channel(track.bone)==layer){
     const auto bone=pose.find(track.bone);if(!bone)throw std::runtime_error("Controller mixture references unknown actor bone");
     mixes[bone].add(sample_actor_controller_srt(actor_controller_times(track,ticks),actor_controller_keys(track),time/ticks,ticks),channel.tracks[id].weight);
    }
   }
   for(unsigned bone=1;bone<mixes.size();++bone)if(mixes[bone].weight>0)pose.bones[bone].local=compose_actor_controller_srt(mixes[bone].value());
  }
 }
 pose.update();apply_actor_spine_yaw(pose,spine_yaw);return pose;
}
}
