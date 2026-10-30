#pragma once
#include "x_mesh.hpp"
#include <map>
namespace daybreak {
struct XMaterial {
    std::array<double,4> face{};
    double power=0;
    std::array<double,3> specular{},emissive{};
    bool has_texture=false;
    std::string texture;
    static XMaterial decode(const XObject& object){
        if(object.reference||object.type!="Material")throw std::runtime_error("Expected X Material");
        XNumbers data(object);XMaterial result;
        for(auto& value:result.face)value=data.real();
        result.power=data.real();
        for(auto& value:result.specular)value=data.real();
        for(auto& value:result.emissive)value=data.real();
        if(data.remaining())throw std::runtime_error("Trailing X material values");
        for(const auto& child:object.children)if(child.type=="TextureFilename"){
            if(result.has_texture)throw std::runtime_error("Duplicate X texture filename");
            if(child.values.size()!=1||child.values[0].kind!=2||!child.children.empty())throw std::runtime_error("Invalid X texture filename");
            const auto& token=child.values[0];result.has_texture=true;
            result.texture.assign(reinterpret_cast<const char*>(token.data),token.size);
        }
        return result;
    }
};
class XMaterialNames {
    std::map<std::string,std::vector<const XObject*>> names_;
    void collect(const std::vector<XObject>& objects){
        for(const auto& object:objects){
            if(!object.reference&&object.type=="Material"&&!object.name.empty()){
                names_[object.name].push_back(&object);
            }
            collect(object.children);
        }
    }
public:
    explicit XMaterialNames(const std::vector<XObject>& roots){collect(roots);}
    const XObject& resolve(const XObject& object)const{
        if(!object.reference)return object;
        const auto found=names_.find(object.name);
        if(found==names_.end())throw std::runtime_error("Missing X material reference: "+object.name);
        if(found->second.size()!=1)throw std::runtime_error("Ambiguous X material reference: "+object.name);
        return *found->second.front();
    }
};
struct XMaterialBinding {
    bool present=false;
    std::vector<XMaterial> materials;
    std::vector<std::uint32_t> faces;
    static XMaterialBinding decode(const XObject& mesh,std::size_t face_count,const XMaterialNames& names){
        XMaterialBinding result;
        for(const auto& object:mesh.children)if(object.type=="MeshMaterialList"){
            if(result.present)throw std::runtime_error("Duplicate X material list");result.present=true;
            XNumbers data(object);const auto count=data.integer(),indexes=data.integer();
            if(indexes!=face_count||indexes>data.remaining())throw std::runtime_error("X material face count mismatch");
            result.faces.reserve(indexes);
            for(unsigned i=0;i<indexes;++i){const auto index=data.integer();if(index>=count)throw std::runtime_error("X material index out of range");result.faces.push_back(index);}
            if(data.remaining())throw std::runtime_error("Trailing X material list values");
            if(count!=object.children.size())throw std::runtime_error("X material definition count mismatch");
            for(const auto& child:object.children)result.materials.push_back(XMaterial::decode(names.resolve(child)));
        }
        return result;
    }
};
}
