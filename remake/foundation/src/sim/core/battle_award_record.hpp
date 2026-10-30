#pragma once
#include "battle_award_selector.hpp"
namespace daybreak {
// actor+aedc layout. Offsets00 (legacy pointer) and84 are not selector inputs.
// Copy raw totals; select_battle_award normalizes only this independent record.
template<class Statistics> BattleAwardStatistics make_battle_award_record(const Statistics& s,
 std::uint32_t own_initial,std::uint32_t enemy_initial,std::uint32_t remaining){
 BattleAwardStatistics r;
 auto set=[&](unsigned offset,std::uint32_t value){r.words.at(offset/4)=value;};
 set(4,own_initial);set(8,enemy_initial);set(12,remaining);
 for(unsigned i=0;i<2;++i){set(0x10+i*4,s.dealt[i]);set(0x18+i*4,s.received[i]);
  set(0x24+i*4,s.attacks_received[i]);set(0x2c+i*4,s.attacks_issued[i]);
  set(0x40+i*4,s.hits_dealt[i]);set(0x4c+i*4,s.hits_received[i]);}
 set(0x20,s.healed_total);set(0x34,s.attacks_at_primary_target);set(0x38,s.shooting_attacks);set(0x3c,s.attacks_total);
 set(0x48,s.friendly_hits);set(0x54,s.guards);set(0x58,s.kills);set(0x5c,s.followup_points);set(0x60,s.deaths);
 r.store(0x64,s.target_distance_sum);r.store(0x68,s.target_height_sum);
 set(0x6c,s.step_starts);set(0x70,s.empty_shots);set(0x74,s.full_charge_shots);set(0x78,s.charge_shots);
 set(0x7c,s.match_ticks);set(0x80,s.airborne_ticks);return r;
}
template<class Statistics> std::array<BattleAwardStatistics,4> make_battle_award_records(
 const std::array<Statistics,4>& stats,const std::array<unsigned,2>& limits,
 const std::array<unsigned,2>& scores,int winner){
 if(winner<0||winner>1)throw std::invalid_argument("Awards require a decided winner");
 std::array<BattleAwardStatistics,4> result;
 for(unsigned i=0;i<4;++i){const unsigned team=i/2;
  //635d40 fills remaining only for the winning pair, even on timeout.
  result[i]=make_battle_award_record(stats[i],limits[team],limits[1-team],team==unsigned(winner)?limits[team]-scores[team]:0u);
 }
 return result;
}
}
