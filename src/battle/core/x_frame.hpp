#pragma once
#include "x_mesh.hpp"
namespace daybreak {
struct XFrameTransform {
    bool present=false;
    std::array<double,16> values{{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}};
    static XFrameTransform decode(const XObject& frame){
        if(frame.type!="Frame"||frame.reference)throw std::runtime_error("Expected X Frame");
        XFrameTransform result;
        for(const auto& child:frame.children)if(child.type=="FrameTransformMatrix"){
            if(result.present)throw std::runtime_error("Duplicate X frame transform");result.present=true;
            XNumbers data(child);
            for(auto& value:result.values)value=data.real();
            if(data.remaining())throw std::runtime_error("Trailing X transform values");
        }
        return result;
    }
};
}
