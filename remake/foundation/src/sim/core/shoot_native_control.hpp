#pragma once
#include "dash_native_control.hpp"
#include <functional>
#include <map>
#include <string>
#include <type_traits>
#include "shoot_native_field_types_20260929.hpp"
namespace daybreak {
using ulonglong=std::uint64_t;
// This NEW owner is not enabled in DevelopmentAnimatedCombat until the new
// original-byte/service and world composition checks pass.
struct ShootNativePhase {int animation=0,duration=0,hold=0;};
using ShootNativeDat=std::map<unsigned,std::vector<ShootNativePhase>>;
struct ShootNativeInput : DashNativeInput {
 unsigned shoot_held=0,shoot_released=0;
 int ammunition_primary=0,ammunition_secondary=0;
 int lower_state=0,lower_phase=0,lower_animation=-1;
 int ally_index=0;unsigned voice_flag2=0;
 const ShootNativeDat* dat=nullptr;
 std::function<ShootNativePhase(int)> animation_metadata;
 std::function<unsigned()> random;
};
struct ShootNativeMotion : DashNativeMotion {float extra100=0,extra10c=0;};
struct ShootNativeEvent {char kind=0;unsigned address=0;std::vector<std::int32_t> args;std::string name;};
struct ShootBodyContext;
struct ShootNativeServices {
 // Return-valued/mutable world services must execute during the source body.
 // The bridge may update ammunition or paired-victim fields in the portable
 // bank before the next source statement. No native actor pointers are used.
 std::function<int(const ShootNativeEvent&,ShootBodyContext&)> invoke;
 // The Ghidra field cast can denote FLD or FILD. The service audit supplies
 // this explicit interpretation for mixed scratch fields; no guessed zero.
 std::function<float(unsigned,std::int32_t)> source_float;
};
struct ShootNativeEffects {
 std::vector<ShootNativeEvent> events;
 std::vector<char> clock_order;
 unsigned scratch_written=0;
 int state=0,lower_state=0,phase=0,lower_phase=0,frame=0,tick2=0;
 int cursor_frame=0,cursor_phase=0;
 bool tail=false,bounds_recovered=false;unsigned missing_state=0,missing_phase=0;
};
struct ShootingDatBounds:std::out_of_range{unsigned state,phase;ShootingDatBounds(unsigned s,unsigned p):std::out_of_range("Original shooting phase outside DAT"),state(s),phase(p){}};
struct ShootBodyContext {
 std::array<std::int32_t,0x2be0> w{};
 const ShootNativeInput& in;const ShootNativeServices& services;
 ShootNativeEffects out;int duration=0,hold=0;float last_fp=0;long double last_curve_angle=0;
 std::int32_t phase_animation=0;
 explicit ShootBodyContext(const ShootNativeInput& input,const ShootNativeServices& port):in(input),services(port),duration(input.duration),hold(input.hold){}
 template<class T> static std::int32_t raw(T value){if constexpr(std::is_floating_point_v<T>)return remaining_bits(float(value));else return std::int32_t(value);}
 template<class... Args> int event(char kind,unsigned address,Args... args){
  out.events.push_back({kind,address,{raw(args)...},{}});
  const auto request=out.events.back(); // The callback can append State services.
  if(!services.invoke)throw std::logic_error("Unbound synchronous shooting service");
  return services.invoke(request,*this);
 }
 float source_float(unsigned index)const{
  return services.source_float?services.source_float(index,w.at(index)):shooting_source_float(in.character,in.weapon,in.state,index,w.at(index));
 }
 int write_scratch(unsigned index,int value){out.scratch_written|=1u<<(index-0x3a);w.at(index)=value;return value;}
 int write_clock(unsigned index,int value){w.at(index)=value;out.clock_order.push_back(index==0x2b81?'1':'2');return value;}
 char byte(unsigned offset)const{return char(std::uint32_t(w.at(offset/4))>>((offset%4)*8));}
 void metadata(unsigned state,unsigned phase,bool upper_only=false){
  if(!in.dat)throw std::logic_error("Shooting DAT catalog missing");
  if(phase>=in.dat->at(state).size())throw ShootingDatBounds(state,phase);
  const auto& value=in.dat->at(state).at(phase);phase_animation=value.animation;
  // Native tail reads ADE4 (lower metadata); Complete reads ADE8 (upper).
  // Upper-only walking admission must retain lower duration/hold as well.
  if(!upper_only){const auto lower_state=unsigned(w[0xadf0/4]);if(phase>=in.dat->at(lower_state).size())throw ShootingDatBounds(lower_state,phase);const auto& lower=in.dat->at(lower_state).at(phase);duration=lower.duration;hold=lower.hold;}
  w[0xadf4/4]=int(phase);w[0xadfc/4]=0;
  if(!upper_only){w[0xadf8/4]=int(phase);write_clock(0xae08/4,0);}
  write_clock(0xae04/4,0);
 }
 void FUN_00421080(int state){
  event('N',0x421080,state);w[0xb]=w[0xc]=w[0xd]=0;w[0x1a1]=-1;w[0x2b7b]=w[0x2b7c]=state;metadata(unsigned(state),0);
 }
 void FUN_00421100(int phase){event('H',0x421100,phase);metadata(unsigned(w[0x2b7b]),unsigned(phase));}
 void FUN_004211f0(int state){event('Y',0x4211f0,state);w[0x1a1]=-1;w[0x2b7b]=state;metadata(unsigned(state),0,true);}
 void FUN_004212f0(){out.cursor_frame=w[0x2b81];out.cursor_phase=w[0x2b7d];out.tail=true;out.clock_order.push_back('F');event('F',0x4212f0,out.cursor_phase,out.cursor_frame);}
 ShootNativePhase selected_animation(int animation)const{
  if(in.animation_metadata)return in.animation_metadata(animation);
  for(const auto& state:*in.dat)for(const auto& phase:state.second)if(phase.animation==animation)return phase;
  throw std::out_of_range("Lower animation metadata absent from DAT");
 }
 int FUN_00421410(int channel,int animation){const auto result=event('I',0x421410,channel,animation);if(channel==0){const auto phase=selected_animation(animation);duration=phase.duration;hold=phase.hold;}return result;}
 int FUN_004218c0(){if(!in.dat)throw std::logic_error("Shooting DAT catalog missing");const auto& upper=in.dat->at(unsigned(w[0xadec/4]));return remaining_add(w[0xae04/4],1)>=upper.at(unsigned(w[0xadf4/4])).duration&&w[0xadf4/4]>=int(upper.size())-1;}
 // The common428510 default source has no custom branch for400..469.
 void FUN_00428510(){w[0x1f5]=-1;write_clock(0x2b81,remaining_add(w[0x2b81],1));write_clock(0x2b82,remaining_add(w[0x2b82],1));FUN_004212f0();if(duration<w[0x2b81]&&!hold)FUN_00421100(w[0x2b7d]+1);}
 std::int32_t* FUN_004244e0(int phase){phase_animation=event('D',0x4244e0,phase);return &phase_animation;}
 void FUN_00421780(){float offset=remaining_real(unsigned(w[0x19]));steer_battle_offset(offset,w[0x9e],w[0x9f],remaining_real(unsigned(w[0x21d])));w[0x19]=remaining_bits(offset);}
 void FUN_0042db10(int target,int step){float offset=remaining_real(unsigned(w[0x19]));approach_battle_offset(offset,remaining_real(unsigned(target)),remaining_real(unsigned(step)));w[0x19]=remaining_bits(offset);}
 void FUN_0042dc20(int,int step){float offset=remaining_real(unsigned(w[0x19])),movement=remaining_real(unsigned(w[0x18]));approach_battle_offset_preserving_movement(offset,movement,remaining_real(unsigned(step)));w[0x19]=remaining_bits(offset);w[0x18]=remaining_bits(movement);}
 float FUN_0042d980(){return last_fp=float(in.distance_squared);}
 template<class... Args> float FUN_0042da30(Args...){return last_fp=in.height;}
 float FUN_0042da80(){return last_fp=float(std::atan2(double(in.height),std::sqrt(in.distance_squared))/double(3.1415927410125732421875f)*180.);}
 float FUN_0042dac0(int selector){if(selector!=2||!in.target_spine_valid)throw std::logic_error("Shooting target spine selector2 required");return last_fp=battle_target_elevation(in.origin,in.target_spine);}
 float FUN_0042de80(float value){return last_fp=std::sqrt(value);}
 float FUN_0042df90(int value){return last_fp=std::fabs(remaining_real(unsigned(value)));}
 float FUN_00423580(int vertical,int speed){last_curve_angle=std::atan2(static_cast<long double>(remaining_real(unsigned(vertical))),static_cast<long double>(remaining_real(unsigned(speed))));return last_fp=float(last_curve_angle);}
 float shooting_curve_degrees()const{volatile float divided=float(last_curve_angle/static_cast<long double>(3.1415927410125732421875f));volatile float degrees=divided*180.f;return degrees;}
 template<class T,class... Args> float FUN_0065d010(T angle,Args...){return last_fp=legacy_trig(remaining_real(unsigned(raw(angle))),true);}
 template<class T,class... Args> float FUN_0065d050(T angle,Args...){return last_fp=legacy_trig(remaining_real(unsigned(raw(angle))),false);}
 int FUN_0066b668(){if(!std::isfinite(last_fp)||last_fp>=2147483648.f||last_fp<-2147483648.f)return std::numeric_limits<int>::min();return int(last_fp);}
 int shooting_ftol(float value){last_fp=value;return FUN_0066b668();}
 int shooting_heading_clamp(float lower_delta,float upper_delta){const float heading=source_float(0x17),base=heading+source_float(0x19);volatile float selected=std::min(float(shooting_ftol(heading)),float(base+upper_delta));return shooting_ftol(std::max(float(selected),float(base+lower_delta)));}
 template<class... Args> unsigned FUN_0065d150(Args...){if(!in.random)throw std::logic_error("Shooting RNG service missing");return in.random();}
 unsigned FUN_0042c7b0(){return unsigned(event('R',0x42c7b0));}
 void FUN_0042c800(int value){event('C',0x42c800,value);}
 void FUN_0042c840(int value){event('Q',0x42c840,value);}
 void FUN_00422900(){event('A',0x422900,1);}
 void FUN_00423000(){event('S',0x423000,1);}
 void FUN_004230e0(){event('J',0x4230e0,1);}
 void FUN_0042c880(int value){event('E',0x42c880,value);}
 void FUN_0042c8b0(int value){event('E',0x42c8b0,value);}
 template<class... Args> void FUN_00422240(Args... args){event('V',0x422240,args...);}
 template<class... Args> void FUN_004223d0(Args... args){event('V',0x4223d0,args...);}
 template<class... Args> void FUN_00422490(Args... args){event('V',0x422490,args...);}
 template<class... Args> int FUN_00422950(Args... args){return event('T',0x422950,args...);}
 template<class... Args> int FUN_00422bd0(Args... args){return event('T',0x422bd0,args...);}
 void FUN_00434a70(int index,int model){event('M',0x434a70,index,model);}
 void FUN_00434bd0(){event('L',0x434bd0);}
 void FUN_00434b30(){event('U',0x434b30);}
 void FUN_00434b90(int value){event('K',0x434b90,value);}
 template<class... Args> void FUN_00434fd0(Args... args){event('B',0x434fd0,args...);}
 template<class... Args> void FUN_00435000(Args... args){event('B',0x435000,args...);}
 template<class... Args> void FUN_00435220(Args... args){event('B',0x435220,args...);}
 template<class... Args> void FUN_00435450(Args... args){event('W',0x435450,args...);}
 template<class... Args> void particle(Args... args){event('P',0x100e100,args...);}
 int FUN_0064e6c0(const char* name){out.events.push_back({'O',0x64e6c0,{},name});if(!services.invoke)throw std::logic_error("Unbound bone matrix handle service");const auto request=out.events.back();return services.invoke(request,*this);}
};
#if defined(DAYBREAK_COMPILED_NATIVE_BODIES)
bool shoot_native_body_binding(unsigned ch,unsigned we,unsigned state);
void dispatch_shoot_body(ShootBodyContext& n,unsigned ch,unsigned we,unsigned state);
#else
#include "shoot_native_bodies_20260929.hpp"
#endif
// Explicit bank initialization keeps the source whole-body compiler separate
// from runtime-owned physics, assets, models, ammunition and paired victims.
inline ShootNativeEffects advance_shoot_native_control(RosterNativeScratch& scratch,ShootNativeMotion& motion,const ShootNativeInput& in,const ShootNativeServices& services){
 ShootBodyContext n(in,services);const auto real=[&](unsigned offset,float value){n.w.at(offset/4)=remaining_bits(value);};
 for(const auto p:{std::pair<unsigned,float>{0x54,motion.speed},{0x64,motion.offset},{0x60,motion.movement},{0x40,motion.vertical},{0x58,motion.gravity},{0x874,motion.turn},{0x2c,motion.pitch},{0x2d8,motion.pivot},{0x30,motion.yaw},{0x34,motion.orientation34},{0x5c,in.heading},{0x68,motion.extra68},{0x7c,in.floor_height},{0x100,motion.extra100},{0x10c,motion.extra10c}})real(p.first,p.second);
 for(unsigned axis=0;axis<3;++axis)real(0x14+axis*4,in.origin[axis]);
 for(const auto p:{std::pair<unsigned,int>{0xe8,scratch.e8},{0xec,scratch.ec},{0xf0,scratch.f0},{0xf4,scratch.f4},{0xf8,scratch.f8},{0x684,motion.contact_mode},{0x7d4,motion.last_hit_owner},{0xaf6c,motion.field_exit},{0xaf48,motion.dash_count},{0xaf60,motion.rank},{0xaf64,motion.rank_timer},{0xaf68,motion.mine_clock},{0x7ac,motion.invincible},{0x834,motion.gauge},{0x7f4,in.slow},{0x278,in.x},{0x27c,in.z},{0x280,int(in.jump)},{0x284,int(in.held)},{0x288,int(in.shoot_held)},{0x2b4,int(in.released)},{0x2b8,int(in.shoot_released)},{0x6dc,in.ammunition_primary},{0x720,in.ammunition_secondary},{0xadec,int(in.state)},{0xadf0,in.lower_state},{0xadf4,int(in.phase)},{0xadf8,in.lower_phase},{0xae04,int(in.frame)},{0xae08,int(in.tick2)},{0x84,in.grounded?1:0},{0xa0,int(in.stop)},{0x844,int(in.active0)|(int(in.active1)<<8)|(int(in.active2)<<16)},{0x848,int(in.ready1)}})n.w.at(p.first/4)=p.second;
 n.w[0x304/4]=in.ally_index;n.w[0xaeb8/4]=int((in.voice_flag2&255u)<<8);
 const auto& lower=in.dat->at(unsigned(in.lower_state)).at(unsigned(in.lower_phase));n.duration=lower.duration;n.hold=lower.hold;
 if(in.lower_animation>=0){const auto selected=n.selected_animation(in.lower_animation);n.duration=selected.duration;n.hold=selected.hold;}
 try{dispatch_shoot_body(n,in.character,in.weapon,in.state);}catch(const ShootingDatBounds& missing){n.out.bounds_recovered=true;n.out.missing_state=missing.state;n.out.missing_phase=missing.phase;n.FUN_00421080(in.grounded?0:43);}
 const auto read=[&](unsigned offset){return remaining_real(unsigned(n.w.at(offset/4)));};
 motion.speed=read(0x54);motion.offset=read(0x64);motion.movement=read(0x60);motion.vertical=read(0x40);motion.gravity=read(0x58);motion.turn=read(0x874);motion.pitch=read(0x2c);motion.pivot=read(0x2d8);motion.yaw=read(0x30);motion.orientation34=read(0x34);motion.extra68=read(0x68);motion.extra100=read(0x100);motion.extra10c=read(0x10c);
 motion.contact_mode=n.w[0x684/4];motion.gauge=n.w[0x834/4];motion.rank=n.w[0xaf60/4];motion.rank_timer=n.w[0xaf64/4];motion.mine_clock=n.w[0xaf68/4];motion.invincible=n.w[0x7ac/4];motion.last_hit_owner=n.w[0x7d4/4];motion.field_exit=n.w[0xaf6c/4];motion.dash_count=n.w[0xaf48/4];
 scratch.e8=n.w[0xe8/4];scratch.ec=n.w[0xec/4];scratch.f0=n.w[0xf0/4];scratch.f4=n.w[0xf4/4];scratch.f8=n.w[0xf8/4];scratch.known|=n.out.scratch_written;
 n.out.state=n.w[0xadec/4];n.out.lower_state=n.w[0xadf0/4];n.out.phase=n.w[0xadf4/4];n.out.lower_phase=n.w[0xadf8/4];n.out.frame=n.w[0xae04/4];n.out.tick2=n.w[0xae08/4];return n.out;
}
}
