#pragma once
#include "remaining_melee_native_control.hpp"
namespace daybreak {
inline float actor_word_real(std::uint32_t value){return remaining_real(value);}
inline int actor_real_word(float value){return remaining_bits(value);}
inline int actor_word_add(int value,int delta){return remaining_add(value,delta);}
struct JumpNativeInput : RemainingMeleeNativeInput {
 int x=0,z=0;unsigned stop=0,ready1=0;
 bool active0=false,active1=false,active2=false;
};
struct JumpNativeMotion : RemainingMeleeNativeMotion {
 int last_hit_owner=0,field_exit=0;
};
struct JumpNativeEffects : RemainingMeleeNativeEffects {
 int state=0,lower_state=0,lower_phase=0,cursor_frame=0,cursor_phase=0;
 bool tail=false;
};
struct JumpBodyContext : RemainingMeleeContext {
 int cursor_frame=0,cursor_phase=0;
 explicit JumpBodyContext(const JumpNativeInput& input):RemainingMeleeContext(input){}
 void FUN_00421780(){
  float offset=remaining_real(unsigned(w[0x64/4]));
  steer_battle_offset(offset,w[0x278/4],w[0x27c/4],remaining_real(unsigned(w[0x874/4])));
  w[0x64/4]=remaining_bits(offset);
 }
 void FUN_004212f0(){cursor_frame=w[0xae04/4];cursor_phase=w[0xadf4/4];++out.clock;}
};
#if defined(DAYBREAK_COMPILED_NATIVE_BODIES)
void dispatch_jump_body(JumpBodyContext& n,unsigned ch,unsigned we,unsigned state);
#else
#include "jump_native_bodies_20260929.hpp"
#endif
// Whole original slot6 body, not a scalar movement profile. It owns both
// animation clocks, shared scratch, ordered State/Phase and frame services.
inline JumpNativeEffects advance_jump_native_control(RosterNativeScratch& scratch,JumpNativeMotion& motion,const JumpNativeInput& in){
 JumpBodyContext n(in);const auto real=[&](unsigned offset,float value){n.w.at(offset/4)=remaining_bits(value);};
 for(const auto pair:{std::pair<unsigned,float>{0x54,motion.speed},{0x64,motion.offset},{0x60,motion.movement},{0x40,motion.vertical},{0x58,motion.gravity},{0x874,motion.turn},{0x2c,motion.pitch},{0x2d8,motion.pivot},{0x30,motion.yaw},{0x34,motion.orientation34},{0x5c,in.heading},{0x68,motion.extra68}})real(pair.first,pair.second);
 for(unsigned axis=0;axis<3;++axis)real(0x14+axis*4,in.origin[axis]);
 for(const auto pair:{std::pair<unsigned,int>{0xe8,scratch.e8},{0xec,scratch.ec},{0xf0,scratch.f0},{0xf4,scratch.f4},{0xf8,scratch.f8},{0x684,motion.contact_mode},{0x7d4,motion.last_hit_owner},{0xaf6c,motion.field_exit},{0xaf60,motion.rank},{0xaf64,motion.rank_timer},{0xaf68,motion.mine_clock},{0x7ac,motion.invincible},{0x834,motion.gauge},{0x7f4,in.slow},{0x278,in.x},{0x27c,in.z},{0x280,int(in.jump)},{0xadec,int(in.state)},{0xadf0,int(in.state)},{0xadf4,int(in.phase)},{0xadf8,int(in.phase)},{0xae04,int(in.frame)},{0xae08,int(in.tick2)},{0x84,in.grounded?1:0},{0xa0,int(in.stop)},{0x844,int(in.active0)|(int(in.active1)<<8)|(int(in.active2)<<16)},{0x848,int(in.ready1)}})n.w.at(pair.first/4)=pair.second;
 dispatch_jump_body(n,in.character,in.weapon,in.state);
 const auto read=[&](unsigned offset){return remaining_real(unsigned(n.w.at(offset/4)));};
 motion.speed=read(0x54);motion.offset=read(0x64);motion.movement=read(0x60);motion.vertical=read(0x40);motion.gravity=read(0x58);motion.turn=read(0x874);motion.pitch=read(0x2c);motion.pivot=read(0x2d8);motion.yaw=read(0x30);motion.orientation34=read(0x34);motion.extra68=read(0x68);
 motion.contact_mode=n.w[0x684/4];motion.gauge=n.w[0x834/4];motion.rank=n.w[0xaf60/4];motion.rank_timer=n.w[0xaf64/4];motion.mine_clock=n.w[0xaf68/4];motion.invincible=n.w[0x7ac/4];motion.last_hit_owner=n.w[0x7d4/4];motion.field_exit=n.w[0xaf6c/4];
 scratch.e8=n.w[0xe8/4];scratch.ec=n.w[0xec/4];scratch.f0=n.w[0xf0/4];scratch.f4=n.w[0xf4/4];scratch.f8=n.w[0xf8/4];scratch.known|=n.scratch_written;
 JumpNativeEffects out;static_cast<RemainingMeleeNativeEffects&>(out)=n.out;out.frame=n.w[0xae04/4];out.tick2=n.w[0xae08/4];out.phase=n.w[0xadf4/4];out.state=n.w[0xadec/4];out.lower_state=n.w[0xadf0/4];out.lower_phase=n.w[0xadf8/4];out.cursor_frame=n.cursor_frame;out.cursor_phase=n.cursor_phase;out.tail=n.out.clock!=0;return out;
}
}
