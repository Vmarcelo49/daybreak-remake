#pragma once
#include <cmath>
#include <cstdint>
namespace daybreak {
// 0x42db10: one boundary correction, not modulo. Negative steps retain original
// behavior; caller supplies the state's turn-step value (+0x874).
inline void approach_battle_offset(float& offset,float target,float step){
    volatile float delta=offset-target;
    if(delta < -180.f)delta=delta+360.f;
    if(delta > 180.f)delta=delta-360.f;
    if(step<=std::abs(float(delta))){
        if(delta<0){volatile float value=step+offset;if(value>180.f)value=value-360.f;offset=value;}
        else if(delta>0){volatile float value=offset-step;if(value < -180.f)value=value+360.f;offset=value;}
    }else offset=target;
}
// 42dc20: a full turn compensates movement; snapping the final small offset
// does not. The two angles each receive one boundary correction.
inline void approach_battle_offset_preserving_movement(float& offset,float& movement,float step){
 float delta=offset;if(delta< -180)delta+=360;if(delta>180)delta-=360;
 if(std::abs(delta)<step){offset=0;return;}
 if(delta<0){offset+=step;movement-=step;if(offset>180)offset-=360;if(movement< -180)movement+=360;}
 else if(delta>0){offset-=step;movement+=step;if(offset< -180)offset+=360;if(movement>180)movement-=360;}
}
// 0x421780 uses signs, not axis magnitudes. No input leaves offset unchanged.
inline void steer_battle_offset(float& offset,std::int32_t x,std::int32_t z,float step){
    if(x<0)approach_battle_offset(offset,z<0?45.f:z==0?90.f:135.f,step);
    else if(x==0){if(z<0)approach_battle_offset(offset,0.f,step);else if(z>0)approach_battle_offset(offset,180.f,step);}
    else approach_battle_offset(offset,z<0?-45.f:z==0?-90.f:-135.f,step);
}
}
