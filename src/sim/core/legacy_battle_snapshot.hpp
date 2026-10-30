#pragma once
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>

namespace daybreak {
// Original 6405e0/640750 and640ac0/640ca0. Tags are hexadecimal18/19.
enum class LegacySnapshotKind : std::uint8_t { compact=0x18, dual=0x19 };
// Original FMUL occurs before66b668 with the caller's x87 precision.
// PC24 and PC53/64 can emit different low words. Never silently choose the
// callback's precision; the transport must supply its established policy.
enum class LegacySnapshotPrecision { single, extended };
struct LegacySnapshotBody {
 std::uint32_t animation=0;
 std::int32_t state=0;
 std::uint32_t phase=0;
 std::int32_t frame=0;
};
struct LegacySnapshotActor {
 std::array<float,3> position{};
 float heading=0,offset=0;
 std::array<LegacySnapshotBody,2> body{}; // primary, secondary
};
struct LegacyBattleSnapshot {
 LegacySnapshotKind kind=LegacySnapshotKind::compact;
 std::uint32_t tick=0;
 std::array<LegacySnapshotActor,4> actors{};
};
inline std::size_t legacy_snapshot_size(LegacySnapshotKind kind){
 return kind==LegacySnapshotKind::compact?69u:(kind==LegacySnapshotKind::dual?93u:0u);
}
inline LegacySnapshotKind select_legacy_snapshot_kind(const std::array<LegacySnapshotActor,4>& actors){
 //640ea0 tests AE0C!=AE10 only, even if states/phases/frames differ.
 for(const auto& actor:actors)if(actor.body[0].animation!=actor.body[1].animation)return LegacySnapshotKind::dual;
 return LegacySnapshotKind::compact;
}
inline bool encode_legacy_snapshot(const LegacyBattleSnapshot& snapshot,LegacySnapshotPrecision precision,
                                    std::array<std::uint8_t,93>& output,std::size_t& size){
 const auto length=legacy_snapshot_size(snapshot.kind);if(!length)return false;
 std::array<std::uint8_t,93> result{};result[0]=std::uint8_t(snapshot.kind);
 for(unsigned i=0;i<4;++i)result[1+i]=std::uint8_t(snapshot.tick>>(8*i));
 auto word=[&](std::size_t offset,std::uint16_t value){result[offset]=std::uint8_t(value);result[offset+1]=std::uint8_t(value>>8);};
 auto quantize=[&](std::size_t offset,float input,bool angle){
  double value=input;
  if(angle){if(precision==LegacySnapshotPrecision::single){volatile float product=input*100.f;value=product;}else value=double(input)*100.0;}
  //Native66b668 finite signed64 domain. Transmit low16, without saturation.
  if(!std::isfinite(value)||value<-9223372036854775808.0||value>=9223372036854775808.0)return false;
  word(offset,std::uint16_t(static_cast<std::int64_t>(value)));return true;
 };
 const auto stride=snapshot.kind==LegacySnapshotKind::compact?16u:22u;
 for(unsigned i=0;i<4;++i){const auto& actor=snapshot.actors[i];const auto row=5u+i*stride;
  for(unsigned axis=0;axis<3;++axis)if(!quantize(row+2*axis,actor.position[axis],false))return false;
  if(!quantize(row+6,actor.heading,true)||!quantize(row+8,actor.offset,true))return false;
  for(unsigned body=0;body<(stride==16?1u:2u);++body){const auto offset=row+10+6*body;const auto& group=actor.body[body];
   result[offset]=std::uint8_t(group.animation);word(offset+1,std::uint16_t(group.state));
   result[offset+3]=std::uint8_t(group.phase);word(offset+4,std::uint16_t(group.frame));
  }
 }
 output=result;size=length;return true;
}
inline bool decode_legacy_snapshot(const std::uint8_t* data,std::size_t size,LegacyBattleSnapshot& output){
 if(!data||size<1)return false;const auto kind=static_cast<LegacySnapshotKind>(data[0]);
 if(!legacy_snapshot_size(kind)||size!=legacy_snapshot_size(kind))return false;
 auto word=[&](std::size_t offset){return std::uint32_t(data[offset])|(std::uint32_t(data[offset+1])<<8);};
 auto signed_word=[&](std::size_t offset){auto value=word(offset);return value<32768?std::int32_t(value):std::int32_t(value)-65536;};
 LegacyBattleSnapshot result{};result.kind=kind;
 for(unsigned i=0;i<4;++i)result.tick|=std::uint32_t(data[1+i])<<(8*i);
 const auto stride=kind==LegacySnapshotKind::compact?16u:22u;
 for(unsigned i=0;i<4;++i){auto& actor=result.actors[i];const auto row=5u+i*stride;
  for(unsigned axis=0;axis<3;++axis)actor.position[axis]=float(signed_word(row+2*axis));
  actor.heading=float(signed_word(row+6))/100.f;actor.offset=float(signed_word(row+8))/100.f;
  for(unsigned body=0;body<(stride==16?1u:2u);++body){auto offset=row+10+6*body;auto& group=actor.body[body];
   group.animation=data[offset];group.state=signed_word(offset+1);group.phase=data[offset+3];group.frame=signed_word(offset+4);
  }
  if(stride==16)actor.body[1]=actor.body[0];
 }
 output=result;return true;
}
inline std::int32_t legacy_snapshot_signed(std::uint32_t value){std::int32_t result;std::memcpy(&result,&value,4);return result;}
}
