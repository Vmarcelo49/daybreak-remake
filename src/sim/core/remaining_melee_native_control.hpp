#pragma once
#include "dash_melee_native_control.hpp"
#include "legacy_trig.hpp"
#include "battle_target_position.hpp"
#include <cstring>
#include <type_traits>
#include <vector>
namespace daybreak {
using uint=unsigned int;using undefined4=std::int32_t;using float10=float;
inline float remaining_real(std::uint32_t word){float f;std::memcpy(&f,&word,4);return f;}
inline std::int32_t remaining_bits(float f){std::int32_t word;std::memcpy(&word,&f,4);return word;}
inline std::int32_t remaining_add(std::int32_t a,std::int32_t b){const auto word=std::uint32_t(a)+std::uint32_t(b);std::int32_t value;std::memcpy(&value,&word,4);return value;}
struct RemainingMeleeNativeInput : DashMeleeNativeInput {
 unsigned tick2=0,held=0,released=0,jump=0;
 std::array<std::uint8_t,3> active{};
 int slow=0,rank_timer=0,mine_clock=0;
 float heading=0,height=0;
 std::array<float,3> origin{},target_spine{};
 bool target_spine_valid=false;
 int duration=100000,hold=0;
 std::vector<int> phase_durations,phase_holds;
};
struct RemainingMeleeNativeMotion : DashMeleeNativeMotion {
 float yaw=0,orientation34=0;
 int gauge=0,rank=0,rank_timer=0,mine_clock=0,invincible=0;
};
// Raw service identity and arguments are kept at the adapter boundary. Audio
// 422490 and voice4223d0 are distinct calls, even with the same category.
struct RemainingMeleeNativeEvent {
 char kind=0;unsigned address=0,count=0;std::array<std::int32_t,6> args{};
};
struct RemainingMeleeNativeEffects {
 int next_state=-1,next_phase=-1,clock=0,frame=0,tick2=0,phase=0;
 std::array<RemainingMeleeNativeEvent,32> events{};unsigned count=0;
};
inline bool remaining_melee_native_state(unsigned state){
 switch(state){case 312:case 313:case 332:case 333:case 334:case 336:case 339:case 340:case 341:return true;default:return false;}
}
// Original slot7-admitted special melee keys; unrelated DAT-only states are excluded.
inline bool extra_melee_native_body_binding(unsigned ch,unsigned we,unsigned state){
 if(ch==14&&we==1)return state==303||state==304||state==335;
 if(ch==8&&we==2)return state==307||state==337||state==338||state==342||state==343||state==344;
 return (ch==9||ch==13)&&we<3&&state==342;
}
// Sparse native words are contained in this temporary service context, never
// exposed as actor pointers or executable machine code. Stored floats use
// explicit bit casts; the public input/motion/scratch types remain portable.
struct RemainingMeleeContext {
 std::array<std::int32_t,0x2be0> w{};
 const RemainingMeleeNativeInput& in;
 RemainingMeleeNativeEffects out;
 unsigned scratch_written=0;
 int duration=100000,hold=0;
 explicit RemainingMeleeContext(const RemainingMeleeNativeInput& input):in(input),duration(input.duration),hold(input.hold){}
 int write_scratch(unsigned index,int value){scratch_written|=1u<<(index-0x3a);w.at(index)=value;return value;}
 template<class... Args> void emit(char kind,unsigned address,Args... args){
  auto& event=out.events.at(out.count++);event.kind=kind;event.address=address;
  event.count=sizeof...(args);event.args={std::int32_t(args)...};
 }
 char byte(unsigned offset)const{return char(std::uint32_t(w.at(offset/4))>>((offset%4)*8));}
 void FUN_00421080(int state){
  emit('N',0x421080,state);out.next_state=state;
  w[0xb]=w[0xc]=w[0xd]=0;w[0x1a1]=-1;w[0x2b7b]=w[0x2b7c]=state;
  phase_metadata(0);
 }
 void phase_metadata(int phase){
  w[0x2b7d]=w[0x2b7e]=phase;w[0x2b7f]=w[0x2b81]=w[0x2b82]=0;
  if(phase>=0&&unsigned(phase)<in.phase_durations.size()){
   duration=in.phase_durations[unsigned(phase)];hold=in.phase_holds.at(unsigned(phase));
  }
 }
 void FUN_00421100(int phase){emit('H',0x421100,phase);out.next_phase=phase;phase_metadata(phase);}
 void FUN_004212f0(){
  ++out.clock;
  // Original4212f0 selects the live DAT row before geometry is evaluated.
  emit('I',0x4212f0,w[0x2b7b],w[0x2b7d],w[0x2b81]);
 }
 int FUN_004218c0(){return in.complete;}
 unsigned contact=0;
 unsigned FUN_0042c7b0(){emit('R',0x42c7b0,int(contact&65535u));return contact;}
 void FUN_0042c800(int value){emit('C',0x42c800,value);contact=0;}
 void FUN_0042c840(int value){emit('Q',0x42c840,value);}
 void FUN_00422900(){emit('A',0x422900,1);}
 void FUN_00423000(){emit('S',0x423000,1);}
 void FUN_004230e0(){emit('J',0x4230e0,1);}
 void FUN_0042c880(int value){emit('E',0x42c880,value,int(0x42c880));}
 void FUN_0042c8b0(int value){emit('E',0x42c8b0,value,int(0x42c8b0));}
 void FUN_004223d0(int a,int b,int c){emit('V',0x4223d0,int(0x4223d0),a,b,c);}
 void FUN_00422490(int a,int b,int c,int d){emit('V',0x422490,int(0x422490),a,b,c,d);}
 void FUN_00434a70(int index,int model){emit('M',0x434a70,index,model);}
 void FUN_00434bd0(){emit('L',0x434bd0);}
 void FUN_00434b30(){emit('U',0x434b30);}
 void FUN_00434b90(int value){emit('K',0x434b90,value);}
 void FUN_00434fd0(int,int,int,int){throw std::logic_error("Unreachable removed source arm");}
 void particle(int id,int x,int y,int z,int heading,int mode){emit('B',0x100e100,id,x,y,z,heading,mode);}
 template<class Pitch> void FUN_00435450(int id,int x,float y,int z,float heading,Pitch pitch){
  // Original435450's final argument is pitch, not an integer mode.
  const auto raw_pitch=[&](){if constexpr(std::is_floating_point_v<Pitch>)return remaining_bits(float(pitch));else return std::int32_t(pitch);}();
  emit('W',0x435450,id,x,remaining_bits(y),z,remaining_bits(heading),raw_pitch);
 }
 void FUN_00428510(){
  // Both admitted aliases (Rena1/341 and Chie1/313) use only the default
  // branch of428510. Source state dispatch contains no dedicated cases.
  w[0x1f5]=-1;w[0x2b81]=remaining_add(w[0x2b81],1);w[0x2b82]=remaining_add(w[0x2b82],1);
  FUN_004212f0();if(duration<w[0x2b81]&&!hold)FUN_00421100(w[0x2b7d]+1);
 }
 void FUN_0042db10(int target,int step){
  float value=remaining_real(w[0x19]);approach_battle_offset(value,remaining_real(unsigned(target)),remaining_real(unsigned(step)));w[0x19]=remaining_bits(value);
 }
 void FUN_0042dc20(int,int step){
  float offset=remaining_real(w[0x19]),movement=remaining_real(w[0x18]);
  approach_battle_offset_preserving_movement(offset,movement,remaining_real(unsigned(step)));
  w[0x19]=remaining_bits(offset);w[0x18]=remaining_bits(movement);
 }
 float FUN_0042d980()const{return float(in.distance_squared);}
 float FUN_0042da30(float=0)const{return in.height;}
 float FUN_0042de80(float value)const{return std::sqrt(value);}
 float FUN_0042da80()const{return float(std::atan2(double(in.height),std::sqrt(in.distance_squared))/double(3.1415927410125732421875f)*180.);}
 float FUN_0042dac0(int selector)const{
  if(selector!=2)throw std::logic_error("Target spine selector2 required");
  if(in.target_spine_valid)return battle_target_elevation(in.origin,in.target_spine);
  return FUN_0042da80();
 }
 float FUN_0042df90(int value)const{return std::fabs(remaining_real(unsigned(value)));}
 float FUN_00423580(int vertical,int speed)const{return float(std::atan2(double(remaining_real(unsigned(vertical))),double(remaining_real(unsigned(speed)))));}
 template<class... Args> float FUN_0065d010(float angle,Args...)const{return legacy_trig(angle,true);}
 template<class... Args> float FUN_0065d050(float angle,Args...)const{return legacy_trig(angle,false);}
 int FUN_0066b65c(bool value)const{return value;}
 unsigned FUN_0065d150()const{return 5;}
};
#if defined(DAYBREAK_COMPILED_NATIVE_BODIES)
void dispatch_remaining_melee_body(RemainingMeleeContext& n,unsigned ch,unsigned we,unsigned state);
void dispatch_extra_melee_body(RemainingMeleeContext& n,unsigned ch,unsigned we,unsigned state);
#else
#include "remaining_melee_native_bodies_20260929.hpp"
#include "extra_melee_native_bodies_20261007.hpp"
#endif
inline RemainingMeleeNativeEffects advance_remaining_melee_native_control(RosterNativeScratch& scratch,
 RemainingMeleeNativeMotion& m,const RemainingMeleeNativeInput& in){
 RemainingMeleeContext n(in);n.contact=in.contact;
 const auto real=[&](unsigned offset,float value){n.w.at(offset/4)=remaining_bits(value);};
 for(const auto pair:{std::pair<unsigned,float>{0x54,m.speed},{0x64,m.offset},{0x60,m.movement},{0x40,m.vertical},{0x58,m.gravity},{0x874,m.turn},{0x2c,m.pitch},{0x2d8,m.pivot},{0x30,m.yaw},{0x34,m.orientation34},{0x5c,in.heading},{0x68,m.extra68}})real(pair.first,pair.second);
 for(unsigned axis=0;axis<3;++axis)real(0x14+axis*4,in.origin[axis]);
 for(const auto pair:{std::pair<unsigned,int>{0xe8,scratch.e8},{0xec,scratch.ec},{0xf0,scratch.f0},{0xf4,scratch.f4},{0xf8,scratch.f8},{0x684,m.contact_mode},{0xaf60,m.rank},{0xaf64,m.rank_timer},{0xaf68,m.mine_clock},{0x7ac,m.invincible},{0x830,in.direction},{0x834,m.gauge},{0x7f4,in.slow},{0x280,int(in.jump)},{0x284,int(in.held)},{0x2b4,int(in.released)},{0xadec,int(in.state)},{0xadf4,int(in.phase)},{0xae04,int(in.frame)},{0xae08,int(in.tick2)},{0x84,in.grounded?1:0},{0xa0,in.blocked?1:0}})n.w.at(pair.first/4)=pair.second;
 // Packed original flags are independent of action clock and shared scratch.
 for(unsigned i=0;i<3;++i){
  const unsigned offset=i==0?0xaec3:i==1?0xaebe:0xaeb9;
  auto& word=n.w.at(offset/4);const unsigned shift=(offset%4)*8;
  word=std::int32_t((std::uint32_t(word)&~(255u<<shift))|(unsigned(in.voice_flags[i])<<shift));
 }
 n.w[0x844/4]=int(in.active[0])|(int(in.active[1])<<8)|(int(in.active[2])<<16);
 if(extra_melee_native_body_binding(in.character,in.weapon,in.state))dispatch_extra_melee_body(n,in.character,in.weapon,in.state);
 else dispatch_remaining_melee_body(n,in.character,in.weapon,in.state);
 const auto read=[&](unsigned offset){return remaining_real(unsigned(n.w.at(offset/4)));};
 m.speed=read(0x54);m.offset=read(0x64);m.movement=read(0x60);m.vertical=read(0x40);m.gravity=read(0x58);m.turn=read(0x874);m.pitch=read(0x2c);m.pivot=read(0x2d8);m.yaw=read(0x30);m.orientation34=read(0x34);m.extra68=read(0x68);
 m.contact_mode=n.w[0x684/4];m.gauge=n.w[0x834/4];m.rank=n.w[0xaf60/4];m.rank_timer=n.w[0xaf64/4];m.mine_clock=n.w[0xaf68/4];m.invincible=n.w[0x7ac/4];
 scratch.e8=n.w[0xe8/4];scratch.ec=n.w[0xec/4];scratch.f0=n.w[0xf0/4];scratch.f4=n.w[0xf4/4];scratch.f8=n.w[0xf8/4];scratch.known|=n.scratch_written;
 n.out.frame=n.w[0xae04/4];n.out.tick2=n.w[0xae08/4];n.out.phase=n.w[0xadf4/4];return n.out;
}
}
