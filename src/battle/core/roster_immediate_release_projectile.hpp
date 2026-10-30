#pragma once
#include "keiichi_normal_projectile.hpp"

namespace daybreak {
// DAT-listed nonzero registrations that call original 5f5e00 immediately,
// without a child, sound or frame advance. Verified with the original handler
// across 2,496 age/owner/contact/stage/incoming-state fixtures. Item6/8 entries
// retain the historical limited owner contexts: production dispatch selects
// their complete switches first, including6's450/460 tether and8's135/186
// linked visuals. Item30's
// orbit routes are intentionally excluded: they depend on the owner's HP.
inline bool roster_immediate_release_registration(unsigned item,unsigned registration){
 switch(item){
 case 6:return registration==50;
 case 8:return registration==140||registration==150||registration==160;
 case 17:return registration==220||registration==230||registration==240;
 case 23:return registration==10;
 case 28:return registration==50;
 case 38:return registration==120||registration==130||registration==140;
 case 39:return registration==180;
 default:return false;
 }
}
inline bool tick_roster_immediate_release_projectile(KeiichiNormalProjectile& s){
 s.released=true;return false;
}
// VA 61b8e0 case 10 only releases on its first script visit. A later seeded
// frame (unreachable from ordinary DAT birth) advances without other effects.
template<class Host> bool tick_roster_birth_only_release_projectile(
 KeiichiNormalProjectile& s,Host& host){
 if(s.released)return false;
 if(s.frame==0){s.released=true;return false;}
 ++s.frame;host.advance_frame(s);return true;
}
} // namespace daybreak
