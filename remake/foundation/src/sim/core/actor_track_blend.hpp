#pragma once
#include <array>
#include <cstdint>
#include <stdexcept>
namespace daybreak {
struct ActorBlendTrack{float weight,initial;std::int32_t duration;};
inline void blend_actor_tracks(std::array<ActorBlendTrack,256>& tracks,std::int32_t& remaining,std::uint32_t selected,std::int32_t duration){
 if(remaining<0)return;if(!duration)throw std::invalid_argument("Zero blend duration");
 for(unsigned i=0;i<256;++i){auto& t=tracks[i];
  if(i==selected){auto delta=std::int32_t(std::uint32_t(t.duration)-std::uint32_t(remaining));volatile float gap=1.f-t.initial;volatile float product=float(double(delta)*double(gap));volatile float ratio=float(double(product)/double(duration));t.weight=ratio+t.initial;}
  else{volatile float product=float(double(remaining)*double(t.initial));t.weight=float(double(product)/double(duration));}
 }--remaining;
}
}
