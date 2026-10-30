#pragma once
#include "actor_frame_data.hpp"
#include <map>
namespace daybreak {
struct ActorAnimationEvent {
 std::array<std::uint32_t,3> timing{};
 std::string source_texture,replacement_texture;
};
struct ActorAnimationSettings {
 std::uint32_t blend_frames=0,hold_phase=0;
 std::vector<ActorAnimationEvent> events;
};
struct ActorAnimationSection {std::vector<ActorAnimationSettings> animations;std::size_t consumed=0;};
// 41e180 after the state/frame table: count, blend, hold flag, event count,
// then 3 words and two fixed 60-byte names per event. Names retain CP932 bytes.
inline ActorAnimationSection read_actor_animation_settings(const std::vector<std::uint8_t>& bytes,std::size_t offset,unsigned count_override=0xffffffffu){
 if(offset>bytes.size())throw std::runtime_error("Animation section offset out of range");
 auto take=[&](std::size_t n){if(n>bytes.size()-offset)throw std::runtime_error("Truncated animation settings");auto p=bytes.data()+offset;offset+=n;return p;};
 auto word=[&](){auto p=take(4);return std::uint32_t(p[0])|(std::uint32_t(p[1])<<8)|(std::uint32_t(p[2])<<16)|(std::uint32_t(p[3])<<24);};
 auto name=[&](){auto p=take(60);unsigned n=0;while(n<60&&p[n])++n;return std::string(reinterpret_cast<const char*>(p),n);};
 ActorAnimationSection result;auto count=word();
 // Effect loader42eec0 reads the serialized count but always consumes one
 // group record, including supplied files that serialize count zero.
 if(count_override!=0xffffffffu)count=count_override;
 if(count>256)throw std::runtime_error("Too many animation settings");
 for(unsigned i=0;i<count;++i){
  ActorAnimationSettings setting;setting.blend_frames=word();setting.hold_phase=word();auto events=word();
  if(events>(bytes.size()-offset)/132)throw std::runtime_error("Truncated animation events");
  for(unsigned j=0;j<events;++j){ActorAnimationEvent e;for(auto& t:e.timing)t=word();e.source_texture=name();e.replacement_texture=name();setting.events.push_back(std::move(e));}
  result.animations.push_back(std::move(setting));
 }
 result.consumed=offset;return result;
}
// 41d870 constructs256 records at+75e0; 4231c0 initializes+1c=1,+20=0.
// 41e180 overwrites only the records present in DAT. Keep serialized count separate.
inline std::array<ActorAnimationSettings,256> actor_runtime_animation_settings(const ActorAnimationSection& section){
 if(section.animations.size()>256)throw std::runtime_error("Too many animation settings");
 std::array<ActorAnimationSettings,256> result;
 for(auto& setting:result)setting.blend_frames=1;
 for(std::size_t i=0;i<section.animations.size();++i)result[i]=section.animations[i];
 return result;
}
// 41f580 clears the per-texture remap each frame, then applies active events
// in file order. End is exclusive; positive periods wrap the signed counter.
inline std::map<std::string,std::string> actor_texture_remaps(const ActorAnimationSettings& settings,std::int32_t elapsed){
 std::map<std::string,std::string> result;
 for(const auto& event:settings.events){
  std::array<std::int32_t,3> timing;std::memcpy(timing.data(),event.timing.data(),sizeof timing);
  const auto tick=timing[2]>0?elapsed%timing[2]:elapsed;
  if(timing[0]<=tick&&tick<timing[1])result[event.source_texture]=event.replacement_texture;
 }
 return result;
}

}
