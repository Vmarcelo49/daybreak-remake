#pragma once
#include "battle_damage_scaling.hpp"
namespace daybreak {
// Portable fields used by422ab0/422bd0. Pair links are reciprocal while held.
// The caller owns stable actor records. Other action/input state lives in Host.
struct BattleThrowActor {
 BattleThrowActor* paired=nullptr;
 std::uint32_t count=0,total=0;
 std::array<float,3> position{};
 float heading=0,offset=0,horizontal=0,vertical=0;
 std::uint8_t blocked=0,release_result=0,capture_mode=0;
};
//Optional notifications preserve the existing standalone local Host contract.
template<class Host> auto notify_battle_capture(Host& h,BattleThrowActor& a,BattleThrowActor& v,std::uint8_t mode,int)->decltype(h.capture_notify(a,v,mode),void()){h.capture_notify(a,v,mode);}
template<class Host> void notify_battle_capture(Host&,BattleThrowActor&,BattleThrowActor&,std::uint8_t,long){}
template<class Host> auto notify_battle_release(Host& h,BattleThrowActor& a,BattleThrowActor& v,int)->decltype(h.release_notify(a,v),void()){h.release_notify(a,v);}
template<class Host> void notify_battle_release(Host&,BattleThrowActor&,BattleThrowActor&,long){}
// 422950, local path. The nonzero attachment token identifies a bone name
// resolved by Host via423530/64e6c0 (D3DXFrameFind), never an RNG seed. The target is actor+308, not necessarily an enemy.
// Bone binding happens even when the target is already paired and capture fails.
// An existing pair receives another action without rewriting its blocked/link fields.
template<class Host> bool capture_battle_actor(BattleThrowActor& attacker,BattleThrowActor& target,
 std::int16_t state,std::uint8_t mode,std::uint32_t attachment,Host& host){
 if(attachment)host.attachment(attachment);
 if(attacker.paired){notify_battle_capture(host,attacker,*attacker.paired,mode,0);host.action(*attacker.paired,state);attacker.capture_mode=mode;return true;}
 if(target.paired)return false;
 notify_battle_capture(host,attacker,target,mode,0);attacker.paired=&target;host.action(target,state);target.blocked=1;target.paired=&attacker;
 attacker.capture_mode=mode;return true;
}
struct BattleThrowRelease {
 std::int16_t normal_state=0,death_state=0,damage=0;
 std::uint8_t scaling=0;
 float rotation=0,horizontal=0,vertical=0;
};
inline std::int16_t battle_throw_damage(std::int16_t base,std::uint32_t count,std::uint8_t scaling){
 const int percent=!scaling||count==1?100:count==2?70:count==3?50:33;
 const auto bits=std::uint16_t((int(base)*percent)/100);
 std::int16_t result;std::memcpy(&result,&bits,2);return result;
}
// 422ab0, local path. Damage is nonlethal; the requested action is applied
// regardless of the damage helper return. Optional attachment-bone binding precedes counts.
template<class Host> std::uint8_t damage_held_battle_actor(BattleThrowActor& attacker,
 std::int16_t state,std::int16_t damage,std::uint8_t scaling,std::uint32_t attachment,Host& host){
 if(!attacker.paired)return 0;auto& victim=*attacker.paired;
 if(attachment)host.attachment(attachment);
 ++victim.count;++victim.total;
 host.damage(attacker,victim,battle_throw_damage(damage,victim.count,scaling),0,1);
 host.action(victim,state);
 return 0;
}
// 422bd0, local path. Host damage returns639160's signed16 outcome, horizontal
// implements42cb50 collision movement, and facing implements42dd90. PositionY
// is preserved. Finite bounded angles are required, as in the original loop.
template<class Host> std::uint8_t release_held_battle_actor(BattleThrowActor& attacker,
 const BattleThrowRelease& input,Host& host){
 if(!attacker.paired)return 0;auto& victim=*attacker.paired;
 notify_battle_release(host,attacker,victim,0);++victim.count;++victim.total;victim.blocked=0;
 const auto outcome=host.damage(attacker,victim,battle_throw_damage(input.damage,victim.count,input.scaling),input.death_state,0);
 host.action(victim,outcome==503?503:outcome<0?input.normal_state:input.death_state);
 victim.horizontal=input.horizontal;victim.vertical=input.vertical;
 volatile float x=victim.position[0]-attacker.position[0],z=victim.position[2]-attacker.position[2];
 victim.position[0]=attacker.position[0];victim.position[2]=attacker.position[2];
 host.horizontal(victim,std::array<float,3>{{x,0,z}});host.facing(victim);
 volatile float offset=attacker.heading+attacker.offset;offset=offset-victim.heading;offset=offset+input.rotation;
 victim.offset=offset;
 while(victim.offset < -180.f)victim.offset+=360.f;
 while(victim.offset > 180.f)victim.offset-=360.f;
 victim.paired=nullptr;attacker.paired=nullptr;
 return attacker.release_result;
}
}
