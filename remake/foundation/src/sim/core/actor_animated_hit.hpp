#pragma once
#include "actor_sampled_pose.hpp"
#include "actor_frame_cursor.hpp"
#include "actor_frame_hit.hpp"
#include "actor_frame_geometry.hpp"
namespace daybreak {
// Caller supplies independently resolved animation and source-key time.
// Frame elapsed is a game counter; it is deliberately not used as animation ticks.
inline void prepare_actor_animated_hit(ActorSkeleton& skeleton,ActorFrameCursor& cursor,
    const ActorPhaseData& phase,std::int32_t elapsed,const XAnimationKeys& animation,
    double animation_time,const LegacyMatrix& actor_world,BattleHitPipelineInput& input){
    auto next_cursor=cursor;
    const auto& frame=next_cursor.advance(phase,elapsed);
    auto next_skeleton=skeleton;
    apply_actor_sampled_pose(next_skeleton,animation,animation_time);
    auto id=next_skeleton.find(frame.bone);
    if(!id)throw std::runtime_error("Attack frame references unknown bone");
    auto next_input=input;
    bind_actor_frame_hit(frame,next_input);
    auto world=multiply_matrix_scalar24(next_skeleton.bones[id].world,actor_world);
    bind_actor_frame_geometry(frame,world,next_input.geometry);
    skeleton=std::move(next_skeleton);cursor=next_cursor;input=next_input;
}
}
