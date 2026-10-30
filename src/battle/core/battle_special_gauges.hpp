#pragma once
#include "battle_hit_charge.hpp"
#include "battle_attack_charge.hpp"
#include "legacy_host_battle_events.hpp"
namespace daybreak {
// One actor owns all three gauges.318 selects which contact path accumulates.
struct BattleSpecialGauges {
 std::uint32_t mode=0,charge0=0,charge1=0,charge2=0,limit0=0,limit1=0,ready1=0;
 std::uint32_t duration0=0,duration1=0;
 std::uint8_t flash=0;bool activated0=false; // actor334/aec8 presentation signals
 bool active0=false,active1=false,active2=false;
 LegacyHostBattleEvents* native_host=nullptr;unsigned native_actor=0;
 std::uint32_t notice_ready1=0; //AEC2 ready-voice byte, distinct from848 shared-target timer.
 BattleHitCharge victim_state()const{return {mode,unsigned(active0),unsigned(active2),charge0,charge2,limit0};}
 BattleAttackCharge attacker_state()const{return {mode,unsigned(active1),charge1,limit1,notice_ready1};}
 bool accepts_mode0_chord(int action,unsigned melee,unsigned shoot)const{
  return (mode&255u)==0&&!active0&&!active1&&!active2&&melee>0&&melee<3&&shoot>0&&shoot<3&&
   (action<118||(action>129&&action<180)||(action>199&&action<218)||(action>229&&action<280))&&damage_signed(charge0)>=damage_signed(limit0);
 }
 bool accepts_mode1_chord(int action,unsigned melee,unsigned shoot)const{
  return (mode&255u)==1&&!active0&&!active1&&!active2&&melee>0&&melee<3&&shoot>0&&shoot<3&&
   (action<100||action>299)&&damage_signed(charge1)>=damage_signed(limit1);
 }
 unsigned refill_step()const{return active2?2:active0?1:active1?3:1;}
 // Local activation primitives421fe0/4220e0/422160; caller owns admission,
 // action transitions and notification7. The hit-recovery mode0 variant uses
 // a separately recovered duration and must not silently use duration0.
 void begin0(){if(native_host)native_host->special(native_actor);charge0=duration0;active0=true;flash=252;activated0=true;}
 void begin1(){if(native_host){native_host->special(native_actor);native_host->system_sound(7,int(native_actor));}charge1=duration1;active1=true;}
 void begin2(std::uint32_t& health){if(native_host)native_host->special(native_actor);health=10000;charge2=duration0;active2=true;flash=252;}
 // 41f73c..41f8e3, outside hitstop gate, after action handling.
 void tick(std::uint32_t& health,int& movement_gauge){
  if((mode&255u)==0){
   if(active0){--charge0;if(damage_signed(charge0)<=0){charge0=0;active0=false;}}
   if(flash)flash=std::uint8_t(flash-4);
  }else if((mode&255u)==1){
   if(active1){--charge1;if(damage_signed(charge1)<=0){charge1=0;active1=false;}}
  }else if((mode&255u)==2){
   if(active2){
    if(movement_gauge<1000)++movement_gauge;
    if(damage_signed(health)<1){charge2=0;active2=false;}
    else if(damage_signed(health)<9){health=1;charge2=0;active2=false;}
    else health-=7;
   }
   if(flash)flash=std::uint8_t(flash-4);
  }
 }
 void store_victim(const BattleHitCharge& state){charge0=state.charge0;charge2=state.charge2;}
 void store_attacker(const BattleAttackCharge& state){charge1=state.charge;notice_ready1=state.ready;}
};
}
