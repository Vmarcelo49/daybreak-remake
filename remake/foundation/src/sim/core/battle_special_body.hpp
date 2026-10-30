#pragma once
#include "battle_special_entry.hpp"
#include <vector>
namespace daybreak {
enum class SpecialBodyEventKind {Particle,Begin,Sound,Voice,ClearContacts,Capacity,State,Phase};
struct SpecialBodyEvent {SpecialBodyEventKind kind;int value=0,argument=0,choice=-1;};
struct BattleSpecialBodyMotion {
 float speed=0,vertical=0,gravity=0,movement=0,turn=0,pitch=0,yaw=0,orientation=0;
 int contact_mode=-1;unsigned down=0,down_timer=0,invincible=0;int last_hit_owner=0;
};
struct BattleSpecialBodyEffects {
 BattleSpecialEntryEffects entry;
 bool tail=false;int next_state=-1,next_phase=-1;
 std::vector<SpecialBodyEvent> events;
};
// Original428510 common states500..503. It owns both clocks and ordered
// services. Presentation sinks consume the recorded events before movement.
// Signed comparisons and wrapping words match the x86 actor representation.
template<class Random> BattleSpecialBodyEffects advance_battle_special_body(
 BattleSpecialEntry& actor,BattleSpecialBodyMotion& motion,
 const BattleActorAssets& data,BattleSpecialGauges& gauges,unsigned& hp,
 bool grounded,Random& random){
 BattleSpecialBodyEffects out;if(!actor.state)return out;
 if(actor.state<500||actor.state>503)throw std::invalid_argument("Invalid awakening body State");
 motion.last_hit_owner=-1; //42851c writes+7d4 on every actual common-body visit.
 const bool mode2=actor.state>=502;
 const auto event=[&](SpecialBodyEventKind kind,int value=0,int arg=0,int choice=-1){out.events.push_back({kind,value,arg,choice});};
 const auto charge=[&](){return actor.recovery?unsigned(damage_signed(gauges.duration0)/4):gauges.duration0;};
 if(actor.phase==0&&actor.frame==0){
  out.entry.started=true;event(SpecialBodyEventKind::Particle,300);event(SpecialBodyEventKind::Particle,310);
  actor.elapsed=0;
  if(mode2){actor.hold=0;motion.speed=motion.vertical=motion.gravity=0;gauges.begin2(hp);event(SpecialBodyEventKind::Begin,2);}
  else {gauges.begin0();gauges.charge0=charge();event(SpecialBodyEventKind::Begin,actor.recovery?3:0);}
  event(SpecialBodyEventKind::Sound,49);
  if(mode2){out.entry.voice_variant=random.next()%64==0?1:0;event(SpecialBodyEventKind::Voice,20,30,int(out.entry.voice_variant));}
  else event(SpecialBodyEventKind::Voice,19,30);
  event(SpecialBodyEventKind::ClearContacts);event(SpecialBodyEventKind::Capacity,mode2?0:1);
  motion.speed=motion.vertical=0;
 }
 const auto& phases=data.state_frames_.at(actor.state);const auto id=phases.at(actor.phase).value;
 const auto duration=damage_signed(data.animation_durations_.at(id));
 if(damage_signed(actor.frame+1u)>=duration&&actor.phase+1u>=phases.size()){
  out.entry.finished=true;out.next_state=grounded?0:43;
  event(SpecialBodyEventKind::State,0);if(!grounded)event(SpecialBodyEventKind::State,43);
  actor.state=actor.phase=actor.frame=actor.secondary_frame=0;
  motion.pitch=motion.yaw=motion.orientation=0;motion.contact_mode=-1;
  if(!grounded)motion.gravity=.5f;
  return out;
 }
 if(mode2)gauges.charge2=gauges.duration0;else gauges.charge0=charge();
 out.entry.pulse=actor.elapsed==0;if(out.entry.pulse)event(SpecialBodyEventKind::Particle,360);
 ++actor.elapsed;
 if(actor.state==502){motion.contact_mode=4;out.entry.ground_mode2_field=true;}
 motion.down=100;motion.down_timer=motion.invincible=60;
 if(mode2)hp=9999;
 motion.gravity=motion.movement=motion.turn=motion.speed=0;
 if(mode2&&actor.frame==10&&damage_signed(actor.hold)<30){++actor.hold;return out;}
 ++actor.frame;++actor.secondary_frame;out.tail=true;
 if(duration<damage_signed(actor.frame)&&!data.animation_settings_.at(id).hold_phase){
  out.next_phase=int(actor.phase+1u);event(SpecialBodyEventKind::Phase,out.next_phase);
  ++actor.phase;actor.frame=actor.secondary_frame=0;
 }
 return out;
}
}
