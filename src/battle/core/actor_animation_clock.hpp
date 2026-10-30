#pragma once
#include "x_animation_keys.hpp"
namespace daybreak {
// D3DX hierarchy loader 43c50f initializes 4800 ticks/sec, passed at 43c081.
inline double actor_ticks_per_second(const std::vector<XObject>& roots){
 double ticks=4800;bool found=false;
 for(const auto& root:roots)if(root.type=="AnimTicksPerSecond"){
  if(found)throw std::runtime_error("Duplicate animation clock");found=true;XNumbers n(root);ticks=n.integer();
  if(n.remaining()||ticks<=0)throw std::runtime_error("Invalid animation clock");
 }return ticks;
}
inline double actor_animation_key_time(std::int32_t counter,double ticks_per_second){
 // Game track position is first stored as float seconds (41fb09..41fb72).
 volatile float seconds=float(double(counter)*double(.01600000075995922088623046875f));
 return double(seconds)*ticks_per_second;
}
inline unsigned actor_animation_frame_count(unsigned last_key,double ticks_per_second){
 // 41e834: float GetPeriod result / float .016, then truncating conversion.
 volatile float period=float(double(last_key)/ticks_per_second);
 volatile float frames=period/.01600000075995922088623046875f;
 if(!std::isfinite(frames)||frames<0||double(frames)>2147483647.)throw std::runtime_error("Animation period out of range");
 return unsigned(frames);
}
}
