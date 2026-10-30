#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <stdexcept>

namespace daybreak {
// Non-owning token payloads refer to the input vector, which must outlive reader.
struct XBinaryToken {
    std::uint16_t kind=0;
    std::uint32_t count=0;
    const std::uint8_t* data=nullptr;
    std::size_t size=0;
};
class XBinaryReader {
    const std::vector<std::uint8_t>& bytes_;
    std::size_t cursor_=16;
    unsigned float_bytes_=4;
    void require(std::size_t size)const{
        if(cursor_>bytes_.size()||size>bytes_.size()-cursor_)throw std::runtime_error("Truncated X binary record");
    }
    std::uint32_t integer(unsigned width){
        require(width);std::uint32_t value=0;
        for(unsigned i=0;i<width;++i)value|=std::uint32_t(bytes_[cursor_++])<<(8*i);
        return value;
    }
public:
    explicit XBinaryReader(const std::vector<std::uint8_t>& bytes):bytes_(bytes){
        if(bytes.size()<16)throw std::runtime_error("Truncated X header");
        const std::string header(bytes.begin(),bytes.begin()+16);
        if(header.substr(0,4)!="xof "||(header.substr(4,4)!="0302"&&header.substr(4,4)!="0303")||header.substr(8,4)!="bin ")throw std::runtime_error("Unsupported X encoding");
        if(header.substr(12,4)=="0064")float_bytes_=8;
        else if(header.substr(12,4)!="0032")throw std::runtime_error("Unsupported X float width");
    }
    unsigned float_bytes()const{return float_bytes_;}
    std::size_t position()const{return cursor_;}
    bool next(XBinaryToken& token){
        if(cursor_==bytes_.size())return false;
        token={};token.kind=static_cast<std::uint16_t>(integer(2));
        unsigned width=0;
        switch(token.kind){
        case 1:case 2:token.count=integer(4);width=1;break;
        case 3:token.count=1;width=4;break;
        case 5:token.count=1;width=16;break;
        case 6:token.count=integer(4);width=4;break;
        case 7:token.count=integer(4);width=float_bytes_;break;
        default:
            if(!((token.kind>=10&&token.kind<=20)||token.kind==31||(token.kind>=40&&token.kind<=52)))throw std::runtime_error("Unknown X binary token at "+std::to_string(cursor_-2));
        }
        if(width){
            if(token.count>(bytes_.size()-cursor_)/width)throw std::runtime_error("Oversized X binary record");
            token.size=std::size_t(token.count)*width;token.data=bytes_.data()+cursor_;cursor_+=token.size;
        }
        // String terminators are consumed as subsequent structural tokens.
        return true;
    }
};
}
