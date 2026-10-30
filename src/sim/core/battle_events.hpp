#pragma once
#include <cstdint>
namespace daybreak {
struct BattleEventState {
    std::int32_t gate=0,value=10000;
    std::int8_t level=0;
    std::uint8_t flag_bf=0,flag_b8=0,flag_c0=0,flag_c1=0,flag_c2=0;
};
// 0x428250. Event routing is supplied by the host; IDs retain original values.
template<class Host> void update_battle_events(BattleEventState& s,Host& host){
    if(s.gate>=100)return;
    for(int level=4;level>=1;--level){
        if(s.value<(5-level)*2500 && s.level<level){
            s.level=static_cast<std::int8_t>(level);
            host.paired_event(14,level-1,25,15,0);
        }
    }
    if(s.flag_bf==1){s.flag_bf=0;host.event(0x422240,16,20,0);}
    if(s.flag_b8==1 && host.query()>0){
        s.flag_b8=0;
        host.event(0x4223d0,host.query()<21?18:4,15,0);
    }
    if(s.flag_c0==1){s.flag_c0=0;host.event(0x4223d0,21,15,0);}
    if(s.flag_c1==1){s.flag_c1=0;host.event(0x4223d0,38,15,0);}
    if(s.gate<100 && s.flag_c2==1){s.flag_c2=0;host.event(0x4223d0,37,15,0);}
}
}
