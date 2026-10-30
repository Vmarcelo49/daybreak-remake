#pragma once
#include <cstdint>
namespace daybreak {
// 0x41fb09..0x41fb72. Integer is loaded exactly by FILD before multiplication.
inline void update_actor_track_time(float& position,float weight,std::uint32_t track,std::uint32_t selected,std::uint32_t layer,std::int32_t primary,std::int32_t secondary){
 if(!(weight>0.f)){position=0.f;return;}
 if(track==selected)position=float(double(layer==1?primary:secondary)*double(0.01600000075995922088623046875f));
}
}
