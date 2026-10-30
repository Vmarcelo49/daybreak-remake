#pragma once
#include <array>
#include "network_ownership_build.hpp"
#include <cstdint>
#include <limits>
#include <optional>
#include <stdexcept>

namespace daybreak::net {
// New rebuild protocol, NOT a DirectPlay or original-game packet layout.
struct Input {
    std::uint32_t buttons=0;
    std::int16_t x=0,z=0;
    bool operator==(const Input& b)const{return buttons==b.buttons&&x==b.x&&z==b.z;}
};
struct InputPacket {std::uint64_t session=0;std::uint32_t tick=0;std::uint8_t slot=0;Input input;};
using InputBytes=std::array<std::uint8_t,28>;
inline bool valid_input(const Input& i){return i.buttons<=0xffff&&i.x!=-32768&&i.z!=-32768;}
inline InputBytes encode(const InputPacket& p){
    if(!p.session||p.slot>=4||!valid_input(p.input))throw std::invalid_argument("Invalid battle input");
    InputBytes b{{'D','B','I','N',std::uint8_t(shared_network_native_input_enabled?2:1),p.slot,0,0}};
    auto put=[&](unsigned offset,std::uint64_t value,unsigned n){for(unsigned i=0;i<n;++i)b[offset+i]=std::uint8_t(value>>(i*8));};
    put(8,p.session,8);put(16,p.tick,4);put(20,p.input.buttons,4);
    put(24,std::uint16_t(p.input.x),2);put(26,std::uint16_t(p.input.z),2);return b;
}
inline std::optional<InputPacket> decode(const std::uint8_t* b,std::size_t size){
    if(!b||size!=28||b[0]!='D'||b[1]!='B'||b[2]!='I'||b[3]!='N'||b[4]!=(shared_network_native_input_enabled?2:1)||b[5]>=4||b[6]||b[7])return {};
    auto get=[&](unsigned offset,unsigned n){std::uint64_t value=0;for(unsigned i=0;i<n;++i)value|=std::uint64_t(b[offset+i])<<(i*8);return value;};
    auto axis=[&](unsigned offset){const auto u=std::uint32_t(get(offset,2));return std::int16_t(u>=32768?std::int32_t(u)-65536:std::int32_t(u));};
    InputPacket p{get(8,8),std::uint32_t(get(16,4)),b[5],{std::uint32_t(get(20,4)),axis(24),axis(26)}};
    if(!p.session||!valid_input(p.input))return {};return p;
}
enum class Receive {accepted,duplicate,conflict,wrong_session,wrong_slot,stale,too_far,exhausted};
class InputChannel {
public:
    static constexpr unsigned capacity=128;
    using Frame=std::array<Input,4>;
private:
    struct Cell {Frame inputs{};std::uint8_t mask=0;};
    std::array<Cell,capacity> cells_{};
    std::uint64_t session_;
    std::uint32_t tick_;
    bool exhausted_=false;
public:
    explicit InputChannel(std::uint64_t session,std::uint32_t first_tick=0):session_(session),tick_(first_tick){if(!session)throw std::invalid_argument("Zero session");}
    std::uint32_t next_tick()const{return tick_;}
    std::uint64_t session()const{return session_;}
    std::optional<Frame> peek()const{
        if(exhausted_||cells_[tick_%capacity].mask!=15)return {};
        return cells_[tick_%capacity].inputs;
    }
    // expected_slot MUST come from the connection's assigned identity, not the packet.
    Receive receive(const InputPacket& p,unsigned expected_slot){
        if(p.session!=session_)return Receive::wrong_session;
        if(p.slot>=4||p.slot!=expected_slot||!valid_input(p.input))return Receive::wrong_slot;
        if(exhausted_)return Receive::exhausted;
        if(p.tick<tick_)return Receive::stale;
        if(std::uint64_t(p.tick)-tick_>=capacity)return Receive::too_far;
        auto& cell=cells_[p.tick%capacity];const auto bit=std::uint8_t(1u<<p.slot);
        if(cell.mask&bit)return cell.inputs[p.slot]==p.input?Receive::duplicate:Receive::conflict;
        cell.inputs[p.slot]=p.input;cell.mask|=bit;return Receive::accepted;
    }
    std::optional<Frame> take(){
        if(exhausted_)return {};
        auto& cell=cells_[tick_%capacity];if(cell.mask!=15)return {};
        Frame result=cell.inputs;cell=Cell{};
        if(tick_==std::numeric_limits<std::uint32_t>::max())exhausted_=true;else ++tick_;
        return result;
    }
};
}
