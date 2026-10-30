#pragma once
#include "actor_frame_data.hpp"
#include "battle_hit_pipeline.hpp"
namespace daybreak {
// Map only data-owned fields. Caller supplies actor/world state and transformed geometry.
inline void bind_actor_frame_hit(const ActorFrameData& f,BattleHitPipelineInput& p){
 auto field=[&](unsigned offset){return f.fields.at((offset-0x30)/4);};
 p.extent=f.extent;p.geometry.shape=f.shape;p.pre.attack_flags=f.flags2c;
 p.hit.base=damage_signed(field(0x30));p.pre.status_power=field(0x34);p.pre.status_duration=field(0x38);p.pre.team_modifier=field(0x3c);
 p.pre.victim_charge_base=damage_signed(field(0x44));p.pre.attacker_charge_base=damage_signed(field(0x48));p.pre.stagger.gate=field(0x4c);p.pre.stagger.down_add=field(0x50);
 p.pre.attack_stop=field(0x54);p.pre.victim_stop=field(0x58);p.pre.stagger.state64=field(0x64);p.pre.stagger.state68=field(0x68);
 p.reaction=field(0x6c);p.effect=field(0x70);p.pre.stagger.vertical=field(0x74);p.pre.stagger.horizontal=field(0x78);
}
}
