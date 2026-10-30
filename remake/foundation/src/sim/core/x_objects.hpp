#pragma once
#include "x_binary.hpp"
namespace daybreak {
struct XObject {
    std::string type,name;
    bool reference=false;
    std::vector<XBinaryToken> values;
    std::vector<XObject> children;
};
// Payloads remain views into the caller-owned original byte vector.
// Templates are skipped structurally, not interpreted as a schema.
class XObjectReader {
    XBinaryReader reader_;
    XBinaryToken current_;
    bool available_=false;
    void advance(){available_=reader_.next(current_);}
    void expect(unsigned kind){if(!available_||current_.kind!=kind)throw std::runtime_error("Unexpected X object token");advance();}
    std::string name(){
        if(!available_||current_.kind!=1)throw std::runtime_error("Missing X name");
        std::string out(reinterpret_cast<const char*>(current_.data),current_.size);advance();return out;
    }
    void skip_template(){
        expect(31);name();expect(10);unsigned depth=1;
        while(depth){if(!available_)throw std::runtime_error("Unclosed X template");if(current_.kind==10)++depth;else if(current_.kind==11)--depth;advance();}
    }
    XObject object(unsigned depth){
        if(depth>256)throw std::runtime_error("Excessive X hierarchy depth");
        XObject out;
        if(current_.kind==10){
            out.reference=true;advance();out.name=name();
            if(available_&&current_.kind==5){out.values.push_back(current_);advance();}
            expect(11);return out;
        }
        out.type=name();if(available_&&current_.kind==1)out.name=name();expect(10);
        while(available_&&current_.kind!=11){
            if(current_.kind==1||current_.kind==10)out.children.push_back(object(depth+1));
            else if(current_.kind==2||current_.kind==3||current_.kind==5||current_.kind==6||current_.kind==7){out.values.push_back(current_);advance();}
            else if(current_.kind==19||current_.kind==20)advance();
            else throw std::runtime_error("Unexpected X data token "+std::to_string(current_.kind));
        }
        expect(11);return out;
    }
public:
    explicit XObjectReader(const std::vector<std::uint8_t>& bytes):reader_(bytes){advance();}
    std::vector<XObject> read(){
        std::vector<XObject> out;
        while(available_){
            if(current_.kind==31)skip_template();
            else out.push_back(object(0));
        }
        return out;
    }
};
}
