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
    if(!std::isfinite(scaled)||scaled<=-2147483648.L||scaled>=2147483648.L)throw std::runtime_error("Legacy angle outside defined conversion range");
    auto index=static_cast<std::int32_t>(scaled);if(index<0)index=-index;auto bits=legacy_cosine_bits[static_cast<unsigned>(index)%3600];float result;std::memcpy(&result,&bits,4);return result;
}
}
