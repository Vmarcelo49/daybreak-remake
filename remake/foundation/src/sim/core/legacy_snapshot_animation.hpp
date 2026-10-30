#pragma once
#include "legacy_battle_snapshot.hpp"
#include "actor_animation_service.hpp"

namespace daybreak {
// Raw snapshot presentation state, separate from host body admission/cursors.
// ADE0/ADFC/actor+10 remain owned by their existing DAT cursor service.
struct LegacySnapshotAnimationActor {
 std::array<float,3> position{};
 float heading=0,offset=0;
 std::array<std::int32_t,2> state{},frame{};
 std::array<std::uint32_t,2> phase{};
 ActorAnimationService animation;
 std::array<std::int32_t,256> period{};
 std::array<std::uint32_t,256> hold{};
 //421410: caller decides whether to bind. COM position is set before
 //weights are changed; callbacks can observe the native synchronous order.
 template<class Observer> void bind(unsigned slot,unsigned layer,unsigned id,Observer& observer){
  if(layer>=2||id>=256)throw std::out_of_range("Invalid native snapshot animation");
  observer.before_bind(slot,layer,id,*this);
  auto& channel=animation.channels[layer];
  channel.remaining=animation.permits_blend(channel.selected,id)?channel.tracks[channel.selected].duration:0;
  channel.selected=id;channel.position[id]=0;
  observer.set_position(slot,layer,id,0.f);
  if(channel.remaining==0){
   for(auto& track:channel.tracks)track.weight=track.initial=0;
   channel.tracks[id].weight=channel.tracks[id].initial=1;channel.remaining=-1;
  }else for(auto& track:channel.tracks)track.initial=track.weight;
  ++animation.binds;
 }
 //41f580 derives track choice from state/phase, but keeps the blend
 //denominator from the currently BOUND descriptor. No frame increment here.
 void step(const std::array<unsigned,2>& phase_selected){
  for(auto id:phase_selected)if(id>=256)throw std::out_of_range("Invalid native snapshot phase animation");
  for(unsigned layer=0;layer<2;++layer){auto& channel=animation.channels[layer];
   for(unsigned id=0;id<256;++id)update_actor_track_time(channel.position[id],channel.tracks[id].weight,id,phase_selected[layer],layer,frame[0],frame[1]);
   blend_actor_tracks(channel.tracks,channel.remaining,phase_selected[layer],channel.tracks[channel.selected].duration);
  }++animation.steps;
 }
};
struct LegacySnapshotNoObserver {
 void before_bind(unsigned,unsigned,unsigned,const LegacySnapshotAnimationActor&){}
 void set_position(unsigned,unsigned,unsigned,float){}
};
template<class Observer> inline void apply_legacy_snapshot(const LegacyBattleSnapshot& snapshot,
                             std::array<LegacySnapshotAnimationActor,4>& actors,Observer& observer){
 if(!legacy_snapshot_size(snapshot.kind))throw std::invalid_argument("Invalid native snapshot kind");
 for(const auto& actor:snapshot.actors)for(const auto& body:actor.body)
  if(body.animation>=256)throw std::out_of_range("Invalid native snapshot animation");
 for(unsigned slot=0;slot<4;++slot){auto& actor=actors[slot];const auto& wire=snapshot.actors[slot];
  actor.position=wire.position;actor.heading=wire.heading;actor.offset=wire.offset;
  if(snapshot.kind==LegacySnapshotKind::compact){
   const auto& group=wire.body[0];
   //AE0C alone gates BOTH binds. Preserve a differing AE10 if AE0C matches.
   if(actor.animation.channels[0].selected!=group.animation){actor.bind(slot,0,group.animation,observer);actor.bind(slot,1,group.animation,observer);}
   actor.state[1]=actor.state[0]=group.state;actor.phase[1]=actor.phase[0]=group.phase;actor.frame[1]=actor.frame[0]=group.frame;
   for(unsigned layer=0;layer<2;++layer){auto id=actor.animation.channels[layer].selected;
    if(actor.frame[layer]<actor.period[id]||actor.hold[id])actor.frame[layer]=legacy_snapshot_signed(std::uint32_t(actor.frame[layer])+1u);
   }
  }else{
   for(unsigned layer=0;layer<2;++layer){const auto& group=wire.body[layer];
    if(actor.animation.channels[layer].selected!=group.animation){actor.frame[layer]=0;actor.bind(slot,layer,group.animation,observer);}
    actor.state[layer]=group.state;actor.phase[layer]=group.phase;actor.frame[layer]=group.frame;
   }
  }
 }
}
}
