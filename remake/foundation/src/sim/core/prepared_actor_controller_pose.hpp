#pragma once
#include "actor_controller_pose.hpp"
namespace daybreak {
// Immutable X-loader outputs. Keep source-tick keys, native SRT and bone
// indices once, as the original controller does when registering its sets.
struct PreparedActorTrack {
 unsigned bone=0,channel=0;
 double ticks=1;
 std::vector<double> times;
 std::vector<ActorSrt> keys;
 ActorSrt sample_srt(double time,unsigned* cursor=nullptr)const{return sample_actor_controller_srt(times,keys,time,ticks,cursor);}
 LegacyMatrix sample(double time,unsigned* cursor=nullptr)const{return compose_actor_controller_srt(sample_srt(time,cursor));}
};
struct PreparedActorControllerPose {
 std::array<std::vector<PreparedActorTrack>,256> sets;
 PreparedActorControllerPose()=default;
 PreparedActorControllerPose(const ActorSkeleton& skeleton,const std::map<unsigned,XAnimationKeys>& animations,double ticks){
  for(const auto& set:animations){auto& out=sets.at(set.first);out.reserve(set.second.tracks.size());
   for(const auto& track:set.second.tracks){PreparedActorTrack prepared;prepared.bone=skeleton.find(track.bone);prepared.channel=actor_animation_channel(track.bone);prepared.ticks=ticks;
    prepared.times=actor_controller_times(track,ticks);prepared.keys=actor_controller_keys(track);
    out.push_back(std::move(prepared));
   }
  }
 }
};
struct ActorControllerPoseScratch {std::vector<ActorControllerSrtMix> mixes;std::array<std::vector<unsigned>,256> key_cursors;};
inline void update_prepared_actor_controller_pose(ActorSkeleton& pose,const ActorAnimationService& service,
 const PreparedActorControllerPose& prepared,const std::map<unsigned,unsigned>& last_keys,double ticks,float spine_yaw,ActorControllerPoseScratch& scratch){
 for(unsigned layer=0;layer<2;++layer){const auto& channel=service.channels[layer];std::array<unsigned,256> active{};unsigned count=0;
  for(unsigned id=0;id<256;++id)if(channel.tracks[id].weight>0)active[count++]=id;
  if(count==1){const auto id=active[0];const auto time=actor_controller_key_time(channel.position[id],ticks,last_keys.at(id))/ticks;
   const auto& tracks=prepared.sets.at(id);auto& cursors=scratch.key_cursors[id];cursors.resize(tracks.size());
   for(unsigned index=0;index<tracks.size();++index){const auto& track=tracks[index];if(track.channel==layer){if(!track.bone)throw std::runtime_error("Controller references unknown actor bone");pose.bones.at(track.bone).local=track.sample(time,&cursors[index]);}}
  }else if(count){scratch.mixes.resize(pose.bones.size());std::fill(scratch.mixes.begin(),scratch.mixes.end(),ActorControllerSrtMix{});
   for(unsigned k=0;k<count;++k){const auto id=active[k];const auto time=actor_controller_key_time(channel.position[id],ticks,last_keys.at(id))/ticks;
    const auto& tracks=prepared.sets.at(id);auto& cursors=scratch.key_cursors[id];cursors.resize(tracks.size());
    for(unsigned index=0;index<tracks.size();++index){const auto& track=tracks[index];if(track.channel==layer){if(!track.bone)throw std::runtime_error("Controller mixture references unknown actor bone");scratch.mixes[track.bone].add(track.sample_srt(time,&cursors[index]),channel.tracks[id].weight);}}
   }
   for(unsigned bone=1;bone<scratch.mixes.size();++bone)if(scratch.mixes[bone].weight>0)pose.bones[bone].local=compose_actor_controller_srt(scratch.mixes[bone].value());
  }
 }
 pose.update();apply_actor_spine_yaw(pose,spine_yaw);
}
}
