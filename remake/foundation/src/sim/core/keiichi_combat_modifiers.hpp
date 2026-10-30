#pragma once
#include "battle_special_gauges.hpp"
namespace daybreak {
struct KeiichiCombatModifiers {std::uint32_t attack=100,received=100,stagger=100;};
//471234..47140d and corresponding Iron/Shovel prefixes. Original D3D x87
//precision is24 bits; store each product at float precision before truncation.
inline KeiichiCombatModifiers keiichi_combat_modifiers(std::uint32_t slow7f4,std::uint32_t attack7e0,std::uint32_t defense7e4,const BattleSpecialGauges& special){
 KeiichiCombatModifiers m{100,105,100};
 auto scale=[](std::uint32_t v,float factor){volatile float product=float(damage_signed(v))*factor;return std::uint32_t(std::int32_t(product));};
 if(damage_signed(slow7f4)>0)m.attack=scale(m.attack,.25f);
 if(damage_signed(attack7e0)>0)m.attack=scale(m.attack,1.2f);
 if(damage_signed(defense7e4)>0)m.received=scale(m.received,.8f);
 if(special.active2){m.attack=scale(m.attack,1.5f);m.received=scale(m.received,.25f);m.stagger=scale(m.stagger,.25f);}
 else if(special.active0){m.attack=scale(m.attack,1.4f);m.received=scale(m.received,.5f);m.stagger=scale(m.stagger,.5f);}
 return m;
}
}
