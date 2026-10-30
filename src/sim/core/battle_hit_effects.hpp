#pragma once
#include "battle_hit_contact.hpp"
#include "battle_hit_reaction.hpp"
#include "battle_damage_scaling.hpp"
#include "legacy_hit_packet.hpp"
namespace daybreak {
// 0x6380c8..0x638287: external effect, reaction and notification backends.
// send_hit receives original unquantized fields; serialize_legacy_hit handles wire format.
template<class Host> void emit_battle_hit_effects(BattleHitReaction& state,BattleRandom& random,const BattleHitContact& contact,std::uint32_t victim,std::uint32_t effect,std::uint32_t reaction,std::uint8_t network,Host& host){
 std::array<float,3> position{},direction{};
 for(unsigned i=0;i<3;++i){position[i]=contact.victim_point[i];direction[i]=position[i]-contact.attack_point[i];}
 if(damage_signed(effect)>0)host.effect(damage_signed(effect),position,direction,victim);
 select_battle_hit_reaction(state,reaction,random);
 const auto selected=state.selected<32768?std::int32_t(state.selected):std::int32_t(state.selected)-65536;
 if(selected>0){host.reaction(selected,position,1u);
  if(network==1){LegacyHitNotification notification{std::uint8_t(victim),std::uint16_t(effect),std::uint16_t(state.selected),position,direction};host.send_hit(notification);}
 }
}
}
