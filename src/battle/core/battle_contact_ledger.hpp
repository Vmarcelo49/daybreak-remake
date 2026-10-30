#pragma once
#include <array>
#include <cstdint>
namespace daybreak {
// Actor+88 ushort flags; +90 signed remaining counts.42c800/42c840/42c7b0.
struct BattleContactLedger {
 std::array<std::uint16_t,4> flags{};std::array<std::uint32_t,4> remaining{};
 void clear_flags(std::uint16_t value=0){flags.fill(value);}
 void set_capacity(std::uint32_t value){remaining.fill(value);}
 bool eligible(unsigned target)const{return flags.at(target)==0&&remaining.at(target)>0&&remaining.at(target)<=0x7fffffffu;}
 std::uint16_t combined()const{std::uint16_t result=0;for(auto value:flags)result|=value;return result;}
 void consume(unsigned target,std::uint16_t value){flags.at(target)=value;--remaining.at(target);}
};
}
