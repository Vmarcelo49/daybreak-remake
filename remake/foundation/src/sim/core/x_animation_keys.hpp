#pragma once
#include "x_mesh.hpp"
#include "legacy_matrix.hpp"
namespace daybreak {
struct XMatrixKey {std::uint32_t time;LegacyMatrix matrix;};
struct XMatrixTrack {std::string bone;std::vector<XMatrixKey> keys;};
struct XAnimationKeys {std::string name;std::vector<XMatrixTrack> tracks;};
// Owns parsed matrix keys. Does not assume D3DX interpolation or playback timing.
inline XAnimationKeys read_x_animation_keys(const XObject& set){
 if(set.type!="AnimationSet"||set.reference)throw std::runtime_error("Expected animation set");
 XAnimationKeys result;result.name=set.name;
 for(const auto& animation:set.children){
  if(animation.type!="Animation"||animation.reference)throw std::runtime_error("Unsupported animation set child");
  XMatrixTrack track;bool found=false;
  for(const auto& child:animation.children){
   if(child.reference){if(!track.bone.empty())throw std::runtime_error("Multiple animation bone references");track.bone=child.name;}
   else if(child.type=="AnimationKey"){
    if(found)throw std::runtime_error("Multiple matrix key tracks");found=true;XNumbers n(child);
    if(n.integer()!=4)throw std::runtime_error("Unsupported animation key type");auto count=n.integer();if(count>n.remaining()/18)throw std::runtime_error("Truncated matrix keys");
    for(std::uint32_t k=0;k<count;++k){XMatrixKey key;key.time=n.integer();if(n.integer()!=16)throw std::runtime_error("Matrix key width");for(auto& v:key.matrix){v=float(n.real());if(!std::isfinite(v))throw std::runtime_error("Matrix key out of range");}if(!track.keys.empty()&&key.time<track.keys.back().time)throw std::runtime_error("Unordered matrix keys");track.keys.push_back(key);}
    if(n.remaining())throw std::runtime_error("Trailing matrix key values");
   }else throw std::runtime_error("Unsupported animation child");
  }
  if(track.bone.empty()||!found||track.keys.empty())throw std::runtime_error("Incomplete animation track");result.tracks.push_back(std::move(track));
 }return result;
}
}
