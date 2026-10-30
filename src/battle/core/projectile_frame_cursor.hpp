#pragma once
#include "actor_frame_data.hpp"
#include "keiichi_normal_projectile.hpp"
namespace daybreak {
// 5f5bf0 starts on phase index 0 / frame index 0; 5f75a0 only moves
// forward, including over multiple DAT records on a single update.
struct ProjectileFrameCursor {
    std::size_t index=0;
    const ActorFrameData& current(const ActorStateData& variant)const{
        if(variant.phases.empty()||index>=variant.phases[0].frames.size())
            throw std::runtime_error("Projectile frame cursor outside phase zero");
        return variant.phases[0].frames[index];
    }
    void advance(const ActorStateData& variant,std::uint32_t tick){
        current(variant);
        const auto& frames=variant.phases[0].frames;
        while(index+1<frames.size()&&projectile_signed(tick)>=frames[index+1].start)++index;
    }
};
}
