#pragma once
#include "legacy_host_battle_mirror.hpp"
#include "battle_effect_request.hpp"
#include "battle_event_feedback.hpp"
#include "battle_contact_feedback.hpp"
#include "legacy_hit_packet.hpp"
#include "legacy_trig.hpp"
#include <atomic>
#include <stdexcept>
namespace daybreak {
//6B7630 is process lifetime, initialized to1, and5F8BA0 adds2 in every role.
//A session can supply its own sequence; starting a round does not reset it.
struct LegacyProjectileSerialSequence {
 std::atomic<std::uint32_t> value{1};
 std::uint32_t next(){return value.fetch_add(2,std::memory_order_relaxed)+2u;}
};
inline LegacyProjectileSerialSequence& legacy_projectile_serial_sequence(){static LegacyProjectileSerialSequence s;return s;}
//Immediate original producer calls, in execution order. The caller serializes
//this queue BEFORE640EA0's end-of-update mirror. Flags exclude NOLOOPBACK.
class LegacyHostBattleEvents {
 LegacyProjectileSerialSequence* serial_;
 unsigned precision_=53;
 std::array<LegacyHostMirrorPeer,8> peers_{};
 std::vector<LegacyHostMirrorMessage> pending_;
 static LegacyBattleEvent packet(unsigned tag){LegacyBattleEvent p;p.tag=std::uint8_t(tag);return p;}
 static void vector(LegacyBattleEvent& p,unsigned offset,const std::array<float,3>& v){for(unsigned i=0;i<3;++i)p.real(offset+4*i,v[i]);}
 void send(const LegacyBattleEvent& p,unsigned recipient=0,unsigned timeout=0,unsigned flags=8){
  LegacyHostMirrorMessage m{recipient,timeout,flags,{}};
  if(!encode_legacy_battle_event(p,m.wire,precision_))throw std::domain_error("Nonfinite original host event");
  pending_.push_back(std::move(m));
 }
 template<class Emit> void human_peers(unsigned actor,Emit emit){for(unsigned n=1;n<8;++n)if(peers_[n].connected&&peers_[n].actor==actor)emit(n);}
public:
 explicit LegacyHostBattleEvents(LegacyProjectileSerialSequence& serial=legacy_projectile_serial_sequence()):serial_(&serial){}
 void configure(const std::array<LegacyHostMirrorPeer,8>& peers,unsigned precision=53){peers_=peers;precision_=precision;}
 std::uint32_t next_projectile(){return serial_->next();}
 const auto& pending()const{return pending_;}
 void consumed(){pending_.clear();}
 void projectile_birth(unsigned owner,unsigned target,std::uint32_t serial,unsigned ordinal,const std::array<float,3>& position,const std::array<float,3>& direction){
  auto p=packet(0x38);p.put(8,owner,1);p.put(9,target,1);p.put(12,serial);p.put(16,ordinal,2);vector(p,20,position);vector(p,32,direction);send(p,0,0,0x88);
 }
 void projectile_release(unsigned attack_owner,std::uint32_t serial){if(!serial)return;auto p=packet(0x39);p.put(8,attack_owner,1);p.put(12,serial);send(p,0,0,0x88);}
 void projectile_target(unsigned attack_owner,std::uint32_t serial){if(!serial)return;auto p=packet(0x3a);p.put(8,attack_owner,1);p.put(12,serial);send(p,0,0,0x88);}
 void projectile_reflect(unsigned manager,unsigned target,unsigned attack_owner,std::uint32_t serial,const std::array<float,3>& position,float heading,float offset,float pitch,float speed){
  if(!serial)return;auto p=packet(0x3b);p.put(8,manager,1);p.put(9,target,1);p.put(12,serial);
  //Original5F72C0 never stores native+10/wire7..8. Fix that undefined
  //stack value explicitly; the packet layout and all defined fields agree.
  p.put(16,attack_owner,2);vector(p,20,position);p.real(32,heading);p.real(36,offset);p.real(40,pitch);p.real(44,speed);send(p,0,0,0x88);
 }
 void special(unsigned actor){auto p=packet(0x24);p.put(8,actor);send(p);}
 void activated(unsigned actor){auto p=packet(0x1f);p.put(8,actor);send(p);}
 void hit(const LegacyHitNotification& h){
  //637950 sends only when resolved sound is signed WORD>0, including FX0.
  if(std::int16_t(h.reaction&65535u)<=0)return;
  auto p=packet(0x35);p.put(8,h.victim,1);p.put(10,h.effect,2);p.put(12,h.reaction,2);vector(p,16,h.position);vector(p,28,h.direction);send(p);
 }
 void effect(const BattleEffectRequest& e){
  auto p=packet(0x36);p.put(8,e.actor,1);p.put(10,e.id,2);vector(p,12,e.position);
  std::array<float,3> direction{};
  if(e.direction)direction=*e.direction;
  else {const float cp=legacy_trig(e.pitch,false);direction={cp*legacy_trig(e.heading,false),legacy_trig(e.pitch,true),cp*legacy_trig(e.heading,true)};}
  vector(p,24,direction);send(p);
 }
 void voice(const BattleEventVoiceRequest& v){
  //422560/730 send before the host's HUMAN playback gate. Ordinary
  //wrappers send after local selection. Never encode selected_choice:
  //random wrappers retain wireFF and do not consume another RNG value.
  const bool alternate=v.source==0x4223d0||v.source==0x422490;
  auto p=packet(alternate?0x0e:0x0d);p.put(8,v.actor,1);p.put(9,v.category,1);p.put(10,std::uint32_t(v.choice),1);p.put(12,v.priority,2);p.put(14,v.option,1);
  if(v.recipient>=0)human_peers(unsigned(v.recipient),[&](unsigned n){send(p,n);});else send(p);
 }
 void system_sound(unsigned code,int recipient=-1){auto p=packet(8);p.put(8,code,2);if(recipient<0)send(p,0,16,2);else human_peers(unsigned(recipient),[&](unsigned n){send(p,n,16,2);});}
 //Only64B060 emits09.42C880/42C8B0 call it with type0/1; direct
 //64AE70 contact reaction playback is carried by35 and remains local.
 void spatial_sound(unsigned code,const std::array<float,3>& position,unsigned raw_type){auto p=packet(9);p.put(8,code,2);vector(p,12,position);p.put(24,raw_type,1);send(p,0,16,2);}
 //422950/422BD0 publish before held action, damage or pair mutation.
 void capture(unsigned holder,unsigned held,unsigned mode){auto p=packet(0x20);p.put(8,holder);p.put(12,held);p.put(16,mode,1);send(p);}
 void release_held(unsigned holder,unsigned held){auto p=packet(0x21);p.put(8,holder);p.put(12,held);send(p);}
 //422F40 leaves the unused native pitch DWORD unwritten. Define it as zero;
 //the original receiver does not read pitch when the transmitted flag is zero.
 void manual(unsigned actor,unsigned enabled,float pitch){auto p=packet(0x22);p.put(8,actor,1);p.put(9,enabled,1);p.real(12,enabled?pitch:0.f);send(p);}
 void time_stop(unsigned actor,std::uint32_t ticks){auto p=packet(0x28);p.put(8,actor);p.put(12,ticks);send(p);}
 void defeat(unsigned attacker,unsigned victim){auto p=packet(0x31);p.put(8,attacker,1);p.put(9,victim,1);send(p);}
 void clock(std::uint32_t old_ticks){if(std::int32_t(old_ticks)%120!=60)return;auto p=packet(0x33);p.put(8,old_ticks);send(p,0,0,2);}
 void timeout(unsigned winner){auto p=packet(0x34);p.put(8,winner,1);send(p);}
 void awards(const std::array<unsigned,4>& titles){auto p=packet(0x3d);for(unsigned i=0;i<4;++i)p.put(8+4*i,titles[i]);send(p,0,0,0x88);}
 //634CA0 viewer cycling only. This is not a per-frame context prefix.
 void viewer(unsigned peer,unsigned actor,unsigned mode){if(peer&&peer<8){auto p=packet(0x15);p.put(8,actor,1);p.put(9,mode,1);send(p,peer);}}
};
}
