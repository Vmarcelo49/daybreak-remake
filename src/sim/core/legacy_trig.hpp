#pragma once
#include "legacy_cosine_table.hpp"
#include <cmath>
#include <cstring>
#include <stdexcept>
namespace daybreak {
enum class TrigPrecision {Float24,Double53};
inline float legacy_trig(float angle,bool sine,TrigPrecision precision=TrigPrecision::Float24){
    // Actual65d010/050 ->66b668: masked nonfinite FISTP qword yields
    // integer-indefinite whose low EAX is zero. Both lookups select table[0].
    if(!std::isfinite(angle)){float value;const auto raw=legacy_cosine_bits[0];std::memcpy(&value,&raw,4);return value;}
    long double scaled;
    if(precision==TrigPrecision::Float24){volatile float product=angle*10.f;volatile float shifted=product-(sine?900.f:0.f);scaled=shifted;}
    else {volatile double product=double(angle)*10.;volatile double shifted=product-(sine?900.:0.);scaled=shifted;}
    // FUN_0066b668 (_ftol2) is a 64-bit FISTP and returns EAX, so a large angle keeps its low
    // 32 bits instead of failing; past 2^63 FISTP is integer-indefinite with EAX 0.
    const bool fits=scaled>-9223372036854775808.L&&scaled<9223372036854775808.L;
    const auto low=fits?static_cast<std::uint32_t>(static_cast<std::uint64_t>(static_cast<std::int64_t>(scaled))):0u;
    // FUN_0066b65c is abs(). Its one overflow, 0x80000000, stays in range here (see PATCHES.md).
    const auto magnitude=low>>31?0u-low:low;auto bits=legacy_cosine_bits[magnitude%3600];float result;std::memcpy(&result,&bits,4);return result;
}
}
