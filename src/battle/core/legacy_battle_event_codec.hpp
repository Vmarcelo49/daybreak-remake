#pragma once
#include <array>
#include <cstdint>
#include <cstddef>
#include <cstring>
#include <cmath>
#include <vector>
namespace daybreak {
//Fixed codecs executed at original VA63C2A0: poison/unused object bytes are
//excluded. Object offsets retain the raw ABI solely to share a single schema.
enum class LegacyEventFieldKind : std::uint8_t {Raw,Signed,Float,Float100};
struct LegacyEventField {std::uint8_t wire,native,wire_size,native_size;LegacyEventFieldKind kind;};
struct LegacyEventSchema {std::uint8_t tag,size,count;std::array<LegacyEventField,12> fields;};
struct LegacyBattleEvent {
 std::uint8_t tag=0;std::array<std::uint8_t,48> value{};
 std::uint32_t u(unsigned offset,unsigned size=4)const {std::uint32_t v=0;for(unsigned i=0;i<size;++i)v|=std::uint32_t(value.at(offset+i))<<(8*i);return v;}
 int s(unsigned offset,unsigned size=4)const {auto v=u(offset,size);if(size<4&&(v&(1u<<(size*8-1))))v|=~((1u<<(size*8))-1u);std::int32_t n;std::memcpy(&n,&v,4);return n;}
 float f(unsigned offset)const {auto n=u(offset);float v;std::memcpy(&v,&n,4);return v;}
 void put(unsigned offset,std::uint32_t v,unsigned size=4){for(unsigned i=0;i<size;++i)value.at(offset+i)=std::uint8_t(v>>(8*i));}
 void real(unsigned offset,float v){std::uint32_t n;std::memcpy(&n,&v,4);put(offset,n);}
};
inline constexpr std::array<LegacyEventSchema,36> legacy_event_schemas{{
 {0x08,3,1,{{{1,8,2,2,LegacyEventFieldKind::Raw}}}},
 {0x09,10,5,{{{1,8,2,2,LegacyEventFieldKind::Raw},{3,12,2,4,LegacyEventFieldKind::Float},{5,16,2,4,LegacyEventFieldKind::Float},{7,20,2,4,LegacyEventFieldKind::Float},{9,24,1,1,LegacyEventFieldKind::Raw}}}},
 {0x0d,7,5,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw},{3,10,1,1,LegacyEventFieldKind::Raw},{4,12,2,2,LegacyEventFieldKind::Raw},{6,14,1,1,LegacyEventFieldKind::Raw}}}},
 {0x0e,7,5,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw},{3,10,1,1,LegacyEventFieldKind::Raw},{4,12,2,2,LegacyEventFieldKind::Raw},{6,14,1,1,LegacyEventFieldKind::Raw}}}},
 {0x15,3,2,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw}}}},
 {0x1a,12,6,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,12,2,4,LegacyEventFieldKind::Float100},{4,16,2,4,LegacyEventFieldKind::Float100},{6,20,2,4,LegacyEventFieldKind::Float100},{8,24,2,4,LegacyEventFieldKind::Float},{10,28,2,4,LegacyEventFieldKind::Float100}}}},
 {0x1c,11,5,{{{1,8,2,4,LegacyEventFieldKind::Signed},{3,12,2,4,LegacyEventFieldKind::Signed},{5,16,2,4,LegacyEventFieldKind::Signed},{7,20,2,4,LegacyEventFieldKind::Signed},{9,24,2,2,LegacyEventFieldKind::Raw}}}},
 {0x1d,3,1,{{{1,8,2,2,LegacyEventFieldKind::Raw}}}},
 {0x1e,5,3,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw},{3,10,2,2,LegacyEventFieldKind::Raw}}}},
 {0x1f,2,1,{{{1,8,1,4,LegacyEventFieldKind::Signed}}}},
 {0x20,4,3,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,1,4,LegacyEventFieldKind::Signed},{3,16,1,1,LegacyEventFieldKind::Raw}}}},
 {0x21,3,2,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,1,4,LegacyEventFieldKind::Signed}}}},
 {0x22,7,3,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw},{3,12,4,4,LegacyEventFieldKind::Raw}}}},
 {0x23,5,1,{{{1,8,4,4,LegacyEventFieldKind::Raw}}}},
 {0x24,2,1,{{{1,8,1,4,LegacyEventFieldKind::Signed}}}},
 {0x26,5,4,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,1,4,LegacyEventFieldKind::Signed},{3,16,1,4,LegacyEventFieldKind::Signed},{4,20,1,1,LegacyEventFieldKind::Raw}}}},
 {0x27,6,2,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,4,4,LegacyEventFieldKind::Raw}}}},
 {0x28,6,2,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,4,4,LegacyEventFieldKind::Raw}}}},
 {0x29,4,2,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,2,2,LegacyEventFieldKind::Raw}}}},
 {0x2a,3,2,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,1,4,LegacyEventFieldKind::Signed}}}},
 {0x2b,3,2,{{{1,8,1,4,LegacyEventFieldKind::Signed},{2,12,1,4,LegacyEventFieldKind::Signed}}}},
 {0x2c,3,1,{{{1,8,2,2,LegacyEventFieldKind::Raw}}}},
 {0x2d,3,1,{{{1,8,2,2,LegacyEventFieldKind::Raw}}}},
 {0x2e,5,2,{{{1,8,2,2,LegacyEventFieldKind::Raw},{3,10,2,2,LegacyEventFieldKind::Raw}}}},
 {0x2f,5,2,{{{1,8,2,2,LegacyEventFieldKind::Raw},{3,10,2,2,LegacyEventFieldKind::Raw}}}},
 {0x30,5,2,{{{1,8,2,2,LegacyEventFieldKind::Raw},{3,10,2,2,LegacyEventFieldKind::Raw}}}},
 {0x31,3,2,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw}}}},
 {0x33,5,1,{{{1,8,4,4,LegacyEventFieldKind::Raw}}}},
 {0x34,2,1,{{{1,8,1,1,LegacyEventFieldKind::Raw}}}},
 {0x35,18,9,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,10,2,2,LegacyEventFieldKind::Raw},{4,12,2,2,LegacyEventFieldKind::Raw},{6,16,2,4,LegacyEventFieldKind::Float},{8,20,2,4,LegacyEventFieldKind::Float},{10,24,2,4,LegacyEventFieldKind::Float},{12,28,2,4,LegacyEventFieldKind::Float100},{14,32,2,4,LegacyEventFieldKind::Float100},{16,36,2,4,LegacyEventFieldKind::Float100}}}},
 {0x36,16,8,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,10,2,2,LegacyEventFieldKind::Raw},{4,12,2,4,LegacyEventFieldKind::Float},{6,16,2,4,LegacyEventFieldKind::Float},{8,20,2,4,LegacyEventFieldKind::Float},{10,24,2,4,LegacyEventFieldKind::Float100},{12,28,2,4,LegacyEventFieldKind::Float100},{14,32,2,4,LegacyEventFieldKind::Float100}}}},
 {0x38,33,10,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw},{3,12,4,4,LegacyEventFieldKind::Raw},{7,16,2,2,LegacyEventFieldKind::Raw},{9,20,4,4,LegacyEventFieldKind::Raw},{13,24,4,4,LegacyEventFieldKind::Raw},{17,28,4,4,LegacyEventFieldKind::Raw},{21,32,4,4,LegacyEventFieldKind::Raw},{25,36,4,4,LegacyEventFieldKind::Raw},{29,40,4,4,LegacyEventFieldKind::Raw}}}},
 {0x39,6,2,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,12,4,4,LegacyEventFieldKind::Raw}}}},
 {0x3a,6,2,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,12,4,4,LegacyEventFieldKind::Raw}}}},
 {0x3b,37,11,{{{1,8,1,1,LegacyEventFieldKind::Raw},{2,9,1,1,LegacyEventFieldKind::Raw},{3,12,4,4,LegacyEventFieldKind::Raw},{7,16,2,2,LegacyEventFieldKind::Raw},{9,20,4,4,LegacyEventFieldKind::Raw},{13,24,4,4,LegacyEventFieldKind::Raw},{17,28,4,4,LegacyEventFieldKind::Raw},{21,32,4,4,LegacyEventFieldKind::Raw},{25,36,4,4,LegacyEventFieldKind::Raw},{29,40,4,4,LegacyEventFieldKind::Raw},{33,44,4,4,LegacyEventFieldKind::Raw}}}},
 {0x3d,17,4,{{{1,8,4,4,LegacyEventFieldKind::Raw},{5,12,4,4,LegacyEventFieldKind::Raw},{9,16,4,4,LegacyEventFieldKind::Raw},{13,20,4,4,LegacyEventFieldKind::Raw}}}},
}};
inline const LegacyEventSchema* legacy_event_schema(unsigned tag){for(const auto& s:legacy_event_schemas)if(s.tag==tag)return &s;return nullptr;}
inline bool decode_legacy_battle_event(const std::uint8_t* wire,std::size_t size,LegacyBattleEvent& out){
 if(!wire||!size)return false;const auto* schema=legacy_event_schema(wire[0]);if(!schema||size!=schema->size)return false;
 LegacyBattleEvent p;p.tag=wire[0];
 for(unsigned j=0;j<schema->count;++j){const auto& f=schema->fields[j];std::uint32_t v=0;
  for(unsigned i=0;i<f.wire_size;++i)v|=std::uint32_t(wire[f.wire+i])<<(8*i);
  if(f.kind==LegacyEventFieldKind::Raw)p.put(f.native,v,f.native_size);
  else {const unsigned n=f.wire_size*8;if(v&(1u<<(n-1)))v|=~((1u<<n)-1u);std::int32_t signed_value;std::memcpy(&signed_value,&v,4);
   if(f.kind==LegacyEventFieldKind::Signed)p.put(f.native,v,f.native_size);
   else {volatile float converted=float(signed_value);volatile float decoded=f.kind==LegacyEventFieldKind::Float100?converted/100.f:converted;p.real(f.native,decoded);}
  }
 }
 out=p;return true;
}
inline bool encode_legacy_battle_event(const LegacyBattleEvent& p,std::vector<std::uint8_t>& out,unsigned precision=53){
 const auto* schema=legacy_event_schema(p.tag);if(!schema)return false;std::vector<std::uint8_t> wire(schema->size);wire[0]=p.tag;
 for(unsigned j=0;j<schema->count;++j){const auto& f=schema->fields[j];auto v=p.u(f.native,f.native_size);
  if(f.kind==LegacyEventFieldKind::Float||f.kind==LegacyEventFieldKind::Float100){
   //Original _ftol66B668 truncates the unspilled product. The raw codec
   //fixtures use FPCW027F (PC53); a PC24 caller must select that explicitly.
   const float input=p.f(f.native);const double product=f.kind==LegacyEventFieldKind::Float100?double(input)*100.:double(input);
   const double converted=precision==24?double(float(product)):product;
   if(!std::isfinite(converted)||double(converted)<-9223372036854775808.||double(converted)>=9223372036854775808.)return false;
   v=std::uint32_t(std::int64_t(converted));
  }
  for(unsigned i=0;i<f.wire_size;++i)wire[f.wire+i]=std::uint8_t(v>>(8*i));
 }
 out=std::move(wire);return true;
}
}
