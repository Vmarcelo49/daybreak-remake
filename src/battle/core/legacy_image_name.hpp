#pragma once
#include <string>
#include <stdexcept>
namespace daybreak {
// 0x661d10 converted-image mode: overwrite the last three bytes, without
// looking for a dot or checking the previous extension.
inline std::string legacy_converted_image_name(std::string name){
    auto nul=name.find('\0');if(nul!=name.npos)name.resize(nul);
    if(name.size()<3||name.size()>263)throw std::runtime_error("Image name outside original conversion buffer");
    name.replace(name.size()-3,3,"cnv");return name;
}
}
