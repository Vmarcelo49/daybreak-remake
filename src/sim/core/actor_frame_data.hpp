#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string>
#include <vector>
namespace daybreak {
struct ActorFrameData {std::string bone;std::int32_t start;std::array<std::int32_t,3> first,second;std::uint32_t extent,flags28,flags2c,shape;std::array<std::uint32_t,20> fields;unsigned bone_index=0;};
struct ActorPhaseData {std::uint32_t value;std::vector<ActorFrameData> frames;};
struct ActorStateData {std::uint32_t id,a,b;std::vector<ActorPhaseData> phases;};
struct ActorFrameFile {std::uint32_t magic;std::string model;std::array<std::uint32_t,6> parameters;std::vector<ActorStateData> states;std::size_t consumed;};
// Strings retain original CP932 bytes. Bone matrices and trailing sections are unresolved.
inline ActorFrameFile read_actor_frame_data(const std::vector<std::uint8_t>& bytes,bool has_actor_parameters=true){
 std::size_t pos=0;
 auto take=[&](std::size_t n){if(n>bytes.size()-pos)throw std::runtime_error("Truncated actor frame data");auto p=bytes.data()+pos;pos+=n;return p;};
 auto word=[&](){auto p=take(4);return std::uint32_t(p[0])|(std::uint32_t(p[1])<<8)|(std::uint32_t(p[2])<<16)|(std::uint32_t(p[3])<<24);};
 auto integer=[&](){auto u=word();std::int32_t v;std::memcpy(&v,&u,4);return v;};
 auto text=[&](std::size_t n){auto p=take(n);std::size_t end=0;while(end<n&&p[end])++end;return std::string(reinterpret_cast<const char*>(p),end);};
 auto count=[&](std::uint32_t max){auto n=word();if(n>max)throw std::runtime_error("Excessive actor count");return n;};
 ActorFrameFile result{};result.magic=word();result.model=text(260);if(has_actor_parameters)for(auto& v:result.parameters)v=word();
 auto states=count(2048);
 for(std::uint32_t s=0;s<states;++s){ActorStateData state;state.id=word();state.a=word();state.b=word();auto phases=count(4096);
  for(std::uint32_t p=0;p<phases;++p){ActorPhaseData phase;phase.value=word();auto frames=count(65536);
   for(std::uint32_t f=0;f<frames;++f){ActorFrameData frame;frame.bone=text(30);frame.start=integer();for(auto& v:frame.first)v=integer();frame.extent=word();for(auto& v:frame.fields)v=word();frame.flags28=word();frame.flags2c=word();frame.shape=word();for(auto& v:frame.second)v=integer();phase.frames.push_back(std::move(frame));}
   state.phases.push_back(std::move(phase));
  }result.states.push_back(std::move(state));
 }result.consumed=pos;return result;
}
}
