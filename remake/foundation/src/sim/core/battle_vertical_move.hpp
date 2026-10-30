#pragma once
#include "battle_horizontal_move.hpp"
#include <cmath>
namespace daybreak {
struct BattleVerticalState {BattleVector position{};float floor_distance=10000;std::uint8_t grounded=0;};
struct BattleFloorResult {float distance=10000,normal_y_abs=0,push_amount=0;BattleVector correction{};};
// Post-query portion of 0x42c970. Portable slope arithmetic pending byte parity.
inline void apply_battle_floor(BattleVerticalState& s,float velocity,BattleFloorResult result){
    s.floor_distance=result.distance;
    volatile float combined=result.distance+velocity;
    if(!s.grounded){
        if(combined<=0 && velocity<=0){
            if(result.push_amount>0 && -combined<result.push_amount){
                // Original expression is -distance + velocity, not -(distance+velocity).
                volatile float amount=-result.distance+velocity;result.push_amount=amount;
            }
            s.grounded=1;
        }
        volatile float squared=result.normal_y_abs*result.normal_y_abs;
        volatile float root=static_cast<float>(std::sqrt(squared));
        volatile float divisor=1.f-root;
        volatile float ratio=result.normal_y_abs/divisor;
        volatile float plus=ratio+1.f;
        volatile float factor=plus*result.push_amount;
        for(auto& component:result.correction)component=factor*component;
    }else if(velocity>0 || combined>20.f)s.grounded=0;
    if(!s.grounded){
        if(combined>=0)s.position[1]+=velocity;
        else s.position[1]-=combined;
    }else s.position[1]-=result.distance;
    for(unsigned i=0;i<3;++i)s.position[i]+=result.correction[i];
}
}
