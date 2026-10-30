#pragma once
#include <array>
#include <cstdint>
#include <cstring>
#include <limits>
#include <stdexcept>
namespace daybreak {
inline std::int32_t damage_signed(std::uint32_t bits){std::int32_t n;std::memcpy(&n,&bits,4);return n;}
inline std::int32_t damage_multiply(std::int32_t a,std::int32_t b){return damage_signed(std::uint32_t(a)*std::uint32_t(b));}
inline std::int32_t damage_divide(std::int32_t a,std::int32_t b){
    if(!b||(a==std::numeric_limits<std::int32_t>::min()&&b==-1))throw std::domain_error("Original damage integer division would fault");
    return a/b;
}
struct BattleDamageTotals {
    std::uint32_t health=10000;
    // Index 0: victim is attacker's +0x308 target; index 1: other victim.
    std::array<std::uint32_t,2> victim_damage{},victim_hits{},attacker_damage{},attacker_hits{};
};
struct BattleDamageApplied {std::int32_t amount=0,excess=0;std::uint32_t was_alive=0;};
// Prefix 0x639160..0x6392ad only. Lethal/survival handling follows in original
// and MUST run separately; negative health here is an intermediate result.
inline BattleDamageApplied apply_direct_damage_prefix(BattleDamageTotals& s,std::int16_t base,std::int32_t attack,std::int32_t defense,std::int32_t divisor,bool targeted){
    BattleDamageApplied result;result.was_alive=damage_signed(s.health)>0;
    auto damage=damage_divide(damage_multiply(base,attack),100);
    damage=damage_divide(damage_multiply(damage,defense),100);
    result.amount=damage_divide(damage_multiply(damage,100),divisor);
    s.health-=std::uint32_t(result.amount);
    if(damage_signed(s.health)<0)result.excess=damage_signed(0u-s.health);
    const auto credited=std::uint32_t(result.amount)-std::uint32_t(result.excess);const unsigned index=targeted?0:1;
    s.victim_damage[index]+=credited;++s.victim_hits[index];s.attacker_damage[index]+=credited;++s.attacker_hits[index];
    return result;
}
}
