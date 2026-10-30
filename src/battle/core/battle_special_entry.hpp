#pragma once
#include "battle_special_gauges.hpp"
#include "battle_actor_assets.hpp"
namespace daybreak {
struct BattleSpecialEntryEffects {bool started=false,finished=false,pulse=false,ground_mode2_field=false;unsigned voice_variant=0;};
//428510 states500..503. The caller owns hitstop, physics, invincibility and
//presentation consumption; phase clocks and gauge/HP writes follow the handler.
struct BattleSpecialEntry {
 unsigned state=0,phase=0,frame=0,elapsed=0,hold=0;bool recovery=false;
 unsigned secondary_frame=0; // AE08 belongs to the common awakening body.
 template<class Random> BattleSpecialEntryEffects advance(const BattleActorAssets& data,BattleSpecialGauges& gauges,std::uint32_t& hp,Random& random){
  BattleSpecialEntryEffects e;if(!state)return e;
  if(state<500||state>503)throw std::invalid_argument("Invalid special entry state");
  const bool mode2=state>=502;
  const auto duration0=[&](){return recovery?std::uint32_t(damage_signed(gauges.duration0)/4):gauges.duration0;};
  if(phase==0&&frame==0){
   e.started=true;elapsed=hold=0;
   if(mode2){gauges.begin2(hp);e.voice_variant=random.next()%64==0?1:0;}
   else {gauges.begin0();gauges.charge0=duration0();}
  }
  const auto& phases=data.state_animations_.at(state);const auto id=phases.at(phase);const auto duration=data.animation_durations_.at(id);
  if(phase+1>=phases.size()&&frame+1>=duration){state=0;e.finished=true;return e;}
  if(mode2){gauges.charge2=gauges.duration0;hp=9999;e.ground_mode2_field=state==502;}
  else gauges.charge0=duration0();
  e.pulse=elapsed==0;++elapsed;
  if(mode2&&frame==10&&hold<30){++hold;return e;}
  if(++frame>duration&&!data.animation_settings_.at(id).hold_phase&&phase+1<phases.size()){++phase;frame=0;}
  return e;
 }
};
}
