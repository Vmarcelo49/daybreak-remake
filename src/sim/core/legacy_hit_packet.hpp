#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include <cmath>
namespace daybreak {
struct LegacyHitNotification {std::uint32_t victim,effect,reaction;std::array<float,3> position,direction;};
// Original decoder 0x63bcf0, preceded here by packet framing validation.
inline bool decode_legacy_hit(const std::uint8_t* data,std::size_t size,LegacyHitNotification& output){
 if(!data||size!=18||data[0]!=0x35)return false;
 auto word=[&](unsigned i){return std::uint32_t(data[i])|(std::uint32_t(data[i+1])<<8);};
 auto signed_word=[&](unsigned i){auto n=word(i);return n<32768?std::int32_t(n):std::int32_t(n)-65536;};
 LegacyHitNotification result{};result.victim=data[1];result.effect=word(2);result.reaction=word(4);
 for(unsigned i=0;i<3;++i){result.position[i]=static_cast<float>(signed_word(6+2*i));result.direction[i]=static_cast<float>(signed_word(12+2*i))/100.f;}
 output=result;return true;
}
}

namespace daybreak {
// Original 0x63bbd0. Finite signed-64 conversion domain; low 16 bits are transmitted.
inline bool serialize_legacy_hit(const LegacyHitNotification& s,std::array<std::uint8_t,18>& output){
 std::array<std::uint8_t,18> result{};result[0]=0x35;result[1]=static_cast<std::uint8_t>(s.victim);
 auto word=[&](unsigned i,std::uint16_t n){result[i]=static_cast<std::uint8_t>(n);result[i+1]=static_cast<std::uint8_t>(n>>8);};
 word(2,static_cast<std::uint16_t>(s.effect));word(4,static_cast<std::uint16_t>(s.reaction));
 for(unsigned i=0;i<6;++i){volatile float value=i<3?s.position[i]:s.direction[i-3]*100.f;
  if(!std::isfinite(value)||static_cast<double>(value)<-9223372036854775808.0||static_cast<double>(value)>=9223372036854775808.0)return false;
  word(6+2*i,static_cast<std::uint16_t>(static_cast<std::int64_t>(value)));
 }
 output=result;return true;
}
}
