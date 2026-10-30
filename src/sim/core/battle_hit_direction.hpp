#pragma once
#include "battle_hit_guard.hpp"
namespace daybreak {
struct BattleHitDirection {float attack_x,attack_z,victim_x,victim_z,vector_x,vector_z;};
// 0x637e0b..0x637e81. Portable CRT backend; numerical fidelity is measured separately.
inline float battle_hit_direction(const BattleHitDirection& p,std::uint32_t flags){
 volatile float x=(flags&0x10)?-p.vector_x:p.attack_x-p.victim_x;
 volatile float z=(flags&0x10)?-p.vector_z:p.attack_z-p.victim_z;
 const double radians=std::atan2(static_cast<double>(z),static_cast<double>(x));
 volatile float turns=static_cast<float>(static_cast<long double>(radians)/3.1415927410125732421875L);
 volatile float degrees=turns*180.f;return degrees;
}
inline bool direct_and_guard_battle_hit(BattleHitGuard& s,const BattleHitDirection& p,float heading,float offset,std::uint32_t owner,std::uint32_t victim_flags,std::uint32_t attack_flags,float& impact,float& relative){
 impact=battle_hit_direction(p,attack_flags);
 return apply_battle_hit_guard(s,impact,heading,offset,owner,victim_flags,attack_flags,relative);
}
}
