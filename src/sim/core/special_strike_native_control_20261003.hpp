#pragma once
#include "full_charge_native_control.hpp"
namespace daybreak {
// New candidate owner, deliberately not connected to production before its gates.
struct SpecialStrikeBodyContext:FullChargeBodyContext{
 using FullChargeBodyContext::FullChargeBodyContext;
};
#if defined(DAYBREAK_COMPILED_NATIVE_BODIES)
bool special_strike_native_body_binding(unsigned ch,unsigned we,unsigned state);
void dispatch_special_strike_body(SpecialStrikeBodyContext& n,unsigned ch,unsigned we,unsigned state);
#else
#include "special_strike_native_bodies_20261003.hpp"
#endif
// Original Tomitake370 writes HP+7A4 and persistent down+7C0/+7C4.
// Other special bodies preserve the incoming values. The closed full-charge
// wrapper still uses its original FullChargeNativeMotion and dispatch.
struct SpecialStrikeNativeMotion:FullChargeNativeMotion{int health=0,down=0,down_timer=0;};
inline FullChargeNativeEffects advance_special_strike_native_control(RosterNativeScratch& scratch,SpecialStrikeNativeMotion& motion,const ShootNativeInput& in,const ShootNativeServices& services){
 auto dispatch=[&](SpecialStrikeBodyContext& n,unsigned ch,unsigned we,unsigned state){
  n.w[0x7a4/4]=motion.health;n.w[0x7c0/4]=motion.down;n.w[0x7c4/4]=motion.down_timer;
  struct ReturnDamageFields{SpecialStrikeBodyContext& n;SpecialStrikeNativeMotion& motion;~ReturnDamageFields(){motion.health=n.w[0x7a4/4];motion.down=n.w[0x7c0/4];motion.down_timer=n.w[0x7c4/4];}} writeback{n,motion};
  dispatch_special_strike_body(n,ch,we,state);
 };
 return advance_native_actor_bank<SpecialStrikeBodyContext>(scratch,motion,in,services,dispatch);
}
}
