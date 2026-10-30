#pragma once
#include "rena_projectile_switches.hpp"
#include "tomitake_chie_projectile_switches.hpp"
#include "item37_projectile.hpp"

namespace daybreak {
inline bool remaining_roster_projectile_item(unsigned item){
 return item==1||item==3||item==33||item==37||item==12||item==42||item==25;
}
template<class Host> bool tick_remaining_roster_projectile(KeiichiNormalProjectile& s,unsigned reg,Host& host){
 switch(unsigned(s.item)){
 case 1:return tick_item1_projectile(s,reg,host);
 case 3:return tick_item3_projectile(s,reg,host);
 case 33:return tick_item33_projectile(s,reg,host);
 case 37:return tick_item37_projectile(s,reg,host);
 case 12:return tick_item12_projectile(s,reg,host);
 case 42:return tick_item42_projectile(s,reg,host);
 case 25:return tick_item25_projectile(s,reg,host);
 default:throw std::invalid_argument("Unrecognized remaining roster projectile item");
 }
}
}
