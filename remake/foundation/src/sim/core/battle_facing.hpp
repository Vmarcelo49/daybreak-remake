#pragma once
#include <cmath>
namespace daybreak {
struct BattleFacing {float heading=0,offset=0;};
// Original uses a single correction at each boundary, not modulo wrapping.
inline void apply_battle_heading(BattleFacing& s,float heading){
    volatile float delta=s.heading-heading;
    if(delta < -180.f)delta=delta+360.f;
    if(delta > 180.f)delta=delta-360.f;
    volatile float offset=delta+s.offset;
    s.heading=heading;
    if(offset < -180.f)offset=offset+360.f;
    if(offset > 180.f)offset=offset-360.f;
    s.offset=offset;
}
// Portable atan2 backend: 2009 finite local-coordinate cases match original
// 0x42dd90 including its CRT path bitwise at FPCW007f. Other FP modes and
// non-finite/extreme inputs remain unverified (target-facing-golden.txt).
inline void face_battle_target(BattleFacing& s,float x,float z,float target_x,float target_z){
    volatile float dx=target_x-x,dz=target_z-z;
    const double radians=std::atan2(static_cast<double>(dz),static_cast<double>(dx));
    volatile float turns=static_cast<float>(static_cast<long double>(radians)/3.1415927410125732421875L);
    volatile float degrees=turns*180.f;
    apply_battle_heading(s,degrees);
}
}
