#pragma once
#include "battle_hit_eligibility.hpp"
#include "battle_sphere_hit.hpp"
#include "battle_segment_hit.hpp"
namespace daybreak {
struct BattleHitGeometry {
    std::array<float,3> primary{},secondary{},start{},end{};
    std::uint32_t shape=0;
};
struct BattleHitContacts {bool primary=false,secondary=false;bool any()const{return primary||secondary;}};
// Coordinates resolve original +0xa4/+0xb4 victim and +0xc4/+0xd4 attack
// records. Both victim spheres have radius 30. Shape 0 selects a sphere.
inline BattleHitContacts query_battle_hit(const BattleHitEligibility& gate,const BattleHitGeometry& g){
    if(!eligible_battle_hit(gate))return {};
    volatile float radius=static_cast<float>(damage_signed(gate.extent));
    if(!g.shape)return {battle_spheres_overlap(g.primary,30.f,g.start,radius),battle_spheres_overlap(g.secondary,30.f,g.start,radius)};
    return {battle_segment_hit(g.primary,30.f,g.start,g.end,radius),battle_segment_hit(g.secondary,30.f,g.start,g.end,radius)};
}
}
