#pragma once
#include <cstdint>
namespace daybreak {
// 0x4212f0. Valid nonnegative frame index and stable phase table required.
template<class Frames> void advance_battle_frame(std::uint32_t& index,std::uint32_t& handle,std::int32_t elapsed,const Frames& frames){
 const auto count=frames.count();
 if(index+1>=count)return;
 do{if(elapsed<frames.start(index+1))break;++index;}while(index+1<count);
 handle=frames.handle(index);
}
}
