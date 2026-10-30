#pragma once
#include "battle_damage_scaling.hpp"
#include "battle_random.hpp"
namespace daybreak {
struct BattleHitStatus{std::array<std::uint32_t,8> duration,power;std::uint32_t newly_applied;};
// Original 0x6387e7..0x638a18. Slots 1/2 belong to support handling.
inline void apply_battle_hit_status(BattleHitStatus& s,std::uint32_t flags,std::uint32_t duration,std::uint32_t power,std::uint32_t attack){
 for(unsigned i=0;i<8;++i){
  if(i==1||i==2||!(flags&(0x40u<<i)))continue;
  if(!s.duration[i]&&i)s.newly_applied=1;
  const auto strength=i==4?std::uint32_t(damage_divide(damage_multiply(damage_signed(power),damage_signed(attack)),100)):power;
  if(!s.duration[i]||(damage_signed(s.power[i])<=damage_signed(strength)&&damage_signed(s.duration[i])<damage_signed(duration))){s.duration[i]=duration;s.power[i]=strength;}
 }
}
// 42e110 decrements nonzero durations, then removes slot0 outside its reactions.
// This adapter covers the eight attack-owned slots; +7fc (ninth timer) is separate.
inline void tick_battle_hit_status(BattleHitStatus& s,unsigned state){
 for(auto& duration:s.duration)if(duration)--duration;
 if(state!=106&&state!=107&&state!=108&&state!=206)s.duration[0]=0;
}
struct BattleStatusPulse {
 unsigned slot=0,visual_id=0,attached_id=0;
 bool visual=false,attached=false;
 std::array<std::uint32_t,3> random_words{};unsigned random_count=0;
};
struct BattleStatusTickEffects {std::array<BattleStatusPulse,5> pulses{};std::uint32_t health_delta=0;};
//42e110 status tail: decrement first, then4/5/6/1/2. Visual randomness is
// consumed on every active tick, even when the particle cadence does not fire.
// Reaction-state effects and the ninth timer at+7fc remain separate.
template<class Observer> BattleStatusTickEffects advance_battle_hit_status_observed(BattleHitStatus& s,unsigned state,std::uint32_t& health,BattleRandom& random,Observer& observer){
 tick_battle_hit_status(s,state);BattleStatusTickEffects out;
 observer.reaction(random);
 const std::array<unsigned,5> slots{4,5,6,1,2},visuals{60,90,80,400,390},periods{15,10,15,30,30},attached{34,37,35,0,0};
 for(unsigned i=0;i<slots.size();++i){auto& p=out.pulses[i];p.slot=slots[i];p.visual_id=visuals[i];p.attached_id=attached[i];const auto duration=s.duration[p.slot];
  if(!duration)continue;
  p.visual=damage_signed(duration)%int(periods[i])==0;p.attached=p.attached_id&&damage_signed(duration)%60==0;
  if(p.attached)observer.sound(p.attached_id); // These42c8b0 IDs are SE, not attached visual objects.
  if(p.slot==4&&damage_signed(s.power[4])<damage_signed(health)){
   const auto before=health;health-=s.power[4];out.health_delta=before-health;
  }
  if(p.slot!=6){p.random_count=3;for(auto& word:p.random_words){word=random.next();observer.random(word);}}
  if(p.visual)observer.visual(p);
 }
 return out;
}
inline BattleStatusTickEffects advance_battle_hit_status(BattleHitStatus& s,unsigned state,std::uint32_t& health,BattleRandom& random){
 struct Observer{void reaction(BattleRandom&){}void sound(unsigned){}void random(unsigned){}void visual(const BattleStatusPulse&){};} observer;
 return advance_battle_hit_status_observed(s,state,health,random,observer);
}

}
