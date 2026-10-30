#pragma once
#include "actor_animation_settings.hpp"
#include "actor_track_time.hpp"
#include "actor_track_blend.hpp"
#include <cstring>
namespace daybreak {
// Actor+75e0 records / ADE4..AE18, not a second combat state machine.
// 421410 binds metadata only; 41f580 advances it; 420b30 evaluates bones later.
struct ActorAnimationChannel {
 unsigned selected=0;
 std::int32_t remaining=-1;
 std::array<ActorBlendTrack,256> tracks{};
 std::array<float,256> position{};
};
struct ActorAnimationService {
 std::array<ActorAnimationChannel,2> channels{};
 unsigned character=0,weapon=0;
 std::uint64_t binds=0,steps=0;
 void configure(unsigned ch,unsigned we,const std::array<ActorAnimationSettings,256>& settings){
  character=ch;weapon=we;
  for(auto& channel:channels)for(unsigned i=0;i<256;++i)
   std::memcpy(&channel.tracks[i].duration,&settings[i].blend_frames,4);
 }
 bool permits_blend(unsigned old_id,unsigned new_id)const{
  // Original virtual slot+20:423310 for45 profiles; Rena iron64c8a0 only.
  return character==0&&weapon==2&&old_id==1&&(new_id==31||new_id==34||new_id==39);
 }
 void bind(unsigned layer,unsigned id){
  if(layer>=2||id>=256)throw std::out_of_range("Invalid actor animation bind");
  auto& c=channels[layer];
  c.remaining=permits_blend(c.selected,id)?c.tracks[c.selected].duration:0;
  c.selected=id;c.position[id]=0;
  if(c.remaining==0){
   for(auto& track:c.tracks)track.weight=track.initial=0;
   c.tracks[id].weight=c.tracks[id].initial=1;c.remaining=-1;
  }else for(auto& track:c.tracks)track.initial=track.weight;
  ++binds;
 }
 void bind_both(unsigned id){bind(0,id);bind(1,id);}
 void step(std::int32_t primary,std::int32_t secondary){
  for(unsigned layer=0;layer<2;++layer){auto& c=channels[layer];
   // Original41f580 calculates positions with the OLD weights first.
   for(unsigned id=0;id<256;++id)update_actor_track_time(c.position[id],c.tracks[id].weight,id,c.selected,layer,primary,secondary);
   blend_actor_tracks(c.tracks,c.remaining,c.selected,c.tracks[c.selected].duration);
  }++steps;
 }
};
}
