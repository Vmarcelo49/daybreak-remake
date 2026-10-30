#pragma once
#include "battle_effect_animation.hpp"
#include "actor_key_pose.hpp"
#include "actor_animation_clock.hpp"
namespace daybreak {
// 5f60b0 sets controller0/track0 to signed projectile age * float(.016)
// before64e580 composes the X frame hierarchy. Mesh vertices stay in their
// authored local space; baking the bind pose would discard this animation.
struct ProjectileModelAnimation {
 ActorSkeleton skeleton;
 std::vector<unsigned> bones;
 std::vector<BattleEffectSrtTrack> tracks;
 double ticks_per_second=4800;
 unsigned period_ticks=0;
 static ProjectileModelAnimation decode(const std::vector<std::uint8_t>& bytes){
  const auto roots=XObjectReader(bytes).read();ProjectileModelAnimation result;
  result.skeleton=ActorSkeleton::decode(roots);result.skeleton.update();
  result.ticks_per_second=actor_ticks_per_second(roots);
  for(auto object=roots.rbegin();object!=roots.rend();++object)if(object->type=="AnimationSet"&&!object->reference){
   const auto animation=read_x_animation_keys(*object);
   for(const auto& track:animation.tracks){
    const unsigned bone=result.skeleton.find(track.bone);
    if(!bone)throw std::runtime_error("Projectile animation references unknown frame: "+track.bone);
    if(std::find(result.bones.begin(),result.bones.end(),bone)!=result.bones.end())throw std::runtime_error("Duplicate projectile animation output: "+track.bone);
    result.period_ticks=std::max(result.period_ticks,track.keys.back().time);
    // 64ddd0 assigns Bip01 outputs to the other controller. All currently
    // supplied projectile tracks use controller0, as the broad probe checks.
    if(actor_animation_channel(track.bone)==0){result.bones.push_back(bone);result.tracks.push_back(decode_battle_effect_animation(track,result.ticks_per_second));}
   }
   break;
  }
  return result;
 }
 double key_time(std::uint32_t frame)const{
  std::int32_t signed_age;std::memcpy(&signed_age,&frame,4);
  volatile float age=float(signed_age);volatile float seconds=age*.01600000075995922088623046875f;
  return secondary_animation_loop_key_time(seconds,ticks_per_second,period_ticks);
 }
 ActorSkeleton sample(std::uint32_t frame)const{
  auto result=skeleton;const double tick=key_time(frame);
  for(unsigned i=0;i<tracks.size();++i)result.bones[bones[i]].local=sample_battle_effect_animation(tracks[i],tick,ticks_per_second);
  update_secondary_animation_world(result);return result;
 }
};
}
