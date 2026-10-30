#pragma once
#include <cstdint>
#include <cstring>
namespace daybreak {
inline bool legacy_asin_outside_unit(float value){
 std::uint32_t raw;std::memcpy(&raw,&value,4);return (raw&0x7fffffffu)>0x3f800000u;
}
// Default masked CRT66c76f/6702ac/675d75 result. Domain failures use
// negative indefinite; NaN sign/payload survive with the quiet bit set.
inline float legacy_asin_domain_result(float value){
 std::uint32_t raw;std::memcpy(&raw,&value,4);
 raw=(raw&0x7fffffffu)>0x7f800000u?(raw|0x00400000u):0xffc00000u;
 std::memcpy(&value,&raw,4);return value;
}
}
