#pragma once
#include <zlib.h>
#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <vector>
namespace daybreak {
inline bool compressed_x(const std::vector<std::uint8_t>& data){
    return data.size()>=16 && (!std::memcmp(data.data()+8,"bzip",4)||!std::memcmp(data.data()+8,"tzip",4));
}
inline std::vector<std::uint8_t> expand_x(const std::vector<std::uint8_t>& data){
    if(data.size()<26 || std::memcmp(data.data(),"xof ",4) || !compressed_x(data))
        throw std::runtime_error("Invalid compressed X header");
    auto u16=[&](std::size_t p){return unsigned(data[p])|(unsigned(data[p+1])<<8);};
    const std::uint32_t expected=u16(16)|(std::uint32_t(u16(18))<<16);
    if(expected<16 || expected>128u*1024*1024)throw std::runtime_error("X expansion size limit");
    std::vector<std::uint8_t> out(data.begin(),data.begin()+16);
    std::memcpy(out.data()+8,data[8]=='b'?"bin ":"txt ",4);
    std::size_t pos=20;
    while(pos<data.size()){
        if(data.size()-pos<6)throw std::runtime_error("Truncated X compression block");
        const auto decoded=u16(pos),stored=u16(pos+2);pos+=4;
        if(!decoded || decoded>32768 || stored<2 || stored>data.size()-pos ||
           data[pos]!='C' || data[pos+1]!='K')throw std::runtime_error("Invalid X compression block");
        if(decoded>expected-out.size())throw std::runtime_error("X expansion exceeds header");
        z_stream stream{};
        if(inflateInit2(&stream,-15)!=Z_OK)throw std::runtime_error("X inflater initialization failed");
        struct End {z_stream* stream;~End(){inflateEnd(stream);}} end{&stream};
        const auto dictionary=std::min<std::size_t>(out.size()-16,32768);
        if(dictionary && inflateSetDictionary(&stream,out.data()+out.size()-dictionary,static_cast<uInt>(dictionary))!=Z_OK)
            throw std::runtime_error("X inflater dictionary failed");
        std::array<std::uint8_t,32769> chunk{};
        stream.next_in=const_cast<Bytef*>(data.data()+pos+2);stream.avail_in=stored-2;
        stream.next_out=chunk.data();stream.avail_out=decoded+1;
        const int result=inflate(&stream,Z_FINISH);
        if(result!=Z_STREAM_END || stream.total_out!=decoded || stream.avail_in)
            throw std::runtime_error("Invalid X deflate stream or length");
        out.insert(out.end(),chunk.begin(),chunk.begin()+decoded);pos+=stored;
    }
    if(out.size()!=expected)throw std::runtime_error("X expansion size mismatch");
    return out;
}
}
