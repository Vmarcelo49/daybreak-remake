#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
// Scene634760 / 635d40 case1 and its shared scalar tail. Kept separate from
// CLOSED result cases2..5; enabling is explicit when a real battle is created.
struct BattleStartup {
 bool enabled=false;unsigned phase=2,frame=0;std::int32_t counter=0;
 std::array<std::int32_t,4> notice_ticks{},notice_type{};
 std::array<float,4> notice_scale{{1,1,1,1}};
 void reset(){enabled=true;phase=1;frame=0;counter=0;notice_ticks.fill(0);notice_type.fill(0);notice_scale.fill(1);}
 bool warming_up()const{return enabled&&phase==1;}
 void begin_frame(){if(enabled)++frame;}
 // true means the native first countdown event starts BGM.
 bool advance(){
  bool music=false;
  if(warming_up()){
   if(notice_ticks[0]==0){music=counter==0;if(counter==3)phase=2;counter=std::int32_t(std::uint32_t(counter)+1);}
   for(unsigned i=0;i<4;++i)if(notice_ticks[i]==0){notice_type[i]=std::int32_t(std::uint32_t(counter)+2);notice_ticks[i]=60;notice_scale[i]=6;}
  }
  if(enabled)for(unsigned i=0;i<4;++i){if(notice_ticks[i]>0)--notice_ticks[i];if(notice_scale[i]>1)notice_scale[i]-=.5f;if(notice_scale[i]<1)notice_scale[i]=1;}
  return music;
 }
};
// 634f60 acquisition precedes this gate. Directions/attack/jump/lock/release
// fields clear; HUMAN preserves28c/298, CPU clears the complete ten-word bank.
// Modern bits8/32 represent native28c/298 (target and ally command).
template<class Input> Input battle_startup_input(Input input,bool cpu){input.x=input.z=0;input.buttons&=cpu?0u:40u;return input;}
}
