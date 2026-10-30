#pragma once
#include "actor_frame_data.hpp"
#include "battle_frame_advance.hpp"
namespace daybreak {
// Index handles remain valid across vector relocation; phase data must stay unchanged while advancing.
struct ActorFrameCursor {
 std::uint32_t index=0,handle=0;
 const ActorFrameData& advance(const ActorPhaseData& phase,std::int32_t elapsed){
  if(phase.frames.empty()||index>=phase.frames.size()||handle>=phase.frames.size())throw std::out_of_range("Invalid actor frame cursor");
  struct View{const ActorPhaseData& phase;std::uint32_t count()const{return std::uint32_t(phase.frames.size());}std::int32_t start(std::uint32_t i)const{return phase.frames.at(i).start;}std::uint32_t handle(std::uint32_t i)const{return i;}};
  advance_battle_frame(index,handle,elapsed,View{phase});return phase.frames.at(handle);
 }
};
}
