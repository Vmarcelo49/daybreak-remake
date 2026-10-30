#pragma once
#include "actor_sampled_pose.hpp"
#include "actor_controller_srt.hpp"
namespace daybreak {
// FX, projectile and animated-camera X sets share the native matrix-key
// ingestion and GetSRT arithmetic with actors. Retain FLOAT source ticks.
struct BattleEffectSrtTrack {std::vector<double> times;std::vector<ActorSrt> keys;};
inline BattleEffectSrtTrack decode_battle_effect_animation(const XMatrixTrack& track,double ticks=0){
 return {actor_controller_times(track,ticks),actor_controller_keys(track)};
}
inline double secondary_animation_loop_key_time(float seconds,double ticks,unsigned last_key){
 double time=double(seconds);const double period=last_key?double(float(double(last_key)/ticks)):0;
 if(period>0){time=std::fmod(time,period);if(time<0)time+=period;}
 return time*ticks;
}
inline LegacyMatrix sample_battle_effect_animation(const BattleEffectSrtTrack& keys,double time,double ticks=0,unsigned* cursor=nullptr){
 const double frequency=ticks>0?ticks:1;
 return compose_actor_controller_srt(sample_actor_controller_srt(keys.times,keys.keys,time/frequency,frequency,cursor));
}
// Native secondary-controller relative hierarchy uses the selected DLL SIMD
// multiplication. X decoding puts each parent before its children.
inline void update_secondary_animation_world(ActorSkeleton& pose){
 for(unsigned bone=1;bone<pose.bones.size();++bone){auto& b=pose.bones[bone];b.world=b.parent?multiply_matrix_simd_order(b.local,pose.bones.at(b.parent).world):b.local;}
}
}
