#pragma once
#include "x_objects.hpp"
#include <array>
#include <cstring>
#include <cmath>
namespace daybreak {
class XNumbers {
    const std::vector<XBinaryToken>& tokens_;std::size_t token_=0,index_=0,remaining_=0;
    const XBinaryToken& current(){
        while(token_<tokens_.size()&&index_==tokens_[token_].count){++token_;index_=0;}
        if(token_==tokens_.size())throw std::runtime_error("Missing X numeric value");
        return tokens_[token_];
    }
public:
    explicit XNumbers(const XObject& object):tokens_(object.values){for(const auto& t:tokens_)remaining_+=t.count;}
    std::size_t remaining()const{return remaining_;}
    std::uint32_t integer(){
        const auto& t=current();if(t.kind!=3&&t.kind!=6)throw std::runtime_error("Expected X integer");
        const auto* p=t.data+4*index_++;--remaining_;
        return std::uint32_t(p[0])|(std::uint32_t(p[1])<<8)|(std::uint32_t(p[2])<<16)|(std::uint32_t(p[3])<<24);
    }
    double real(){
        const auto& t=current();if(t.kind!=7)throw std::runtime_error("Expected X float");
        const auto width=t.size/t.count;const auto* p=t.data+width*index_++;--remaining_;double value;
        if(width==4){float f;std::memcpy(&f,p,4);value=f;}else if(width==8)std::memcpy(&value,p,8);else throw std::runtime_error("X float width");
        if(!std::isfinite(value))throw std::runtime_error("Nonfinite X coordinate");return value;
    }
};
struct XMesh {
    std::vector<std::array<double,3>> vertices;
    std::vector<std::vector<std::uint32_t>> faces;
    bool has_normals=false,has_uvs=false;
    std::vector<std::array<double,3>> normals;
    std::vector<std::vector<std::uint32_t>> face_normals;
    std::vector<std::array<double,2>> uvs;
    struct VertexColor {std::uint32_t index;std::array<double,4> rgba;};
    bool has_colors=false;
    std::vector<VertexColor> colors;
    static XMesh decode(const XObject& object){
        if(object.type!="Mesh"||object.reference)throw std::runtime_error("Expected Mesh object");
        XNumbers input(object);XMesh mesh;const auto vertices=input.integer();
        if(vertices>input.remaining()/3)throw std::runtime_error("X vertex count exceeds data");
        mesh.vertices.reserve(vertices);
        for(unsigned i=0;i<vertices;++i)mesh.vertices.push_back({input.real(),input.real(),input.real()});
        const auto faces=input.integer();if(faces>input.remaining())throw std::runtime_error("X face count exceeds data");mesh.faces.reserve(faces);
        for(unsigned i=0;i<faces;++i){
            const auto count=input.integer();if(count>input.remaining())throw std::runtime_error("X face size exceeds data");
            std::vector<std::uint32_t> face;face.reserve(count);
            for(unsigned j=0;j<count;++j){const auto index=input.integer();if(index>=vertices)throw std::runtime_error("X vertex index out of range");face.push_back(index);}
            mesh.faces.push_back(std::move(face));
        }
        if(input.remaining())throw std::runtime_error("Trailing X mesh values");
        for(const auto& child:object.children){
            if(child.type=="MeshVertexColors"){
                if(mesh.has_colors)throw std::runtime_error("Duplicate X vertex color block");mesh.has_colors=true;
                XNumbers data(child);const auto count=data.integer();
                if(count>data.remaining()/5)throw std::runtime_error("X vertex color count exceeds data");
                mesh.colors.reserve(count);
                for(unsigned i=0;i<count;++i){
                    const auto index=data.integer();if(index>=vertices)throw std::runtime_error("X vertex color index out of range");
                    mesh.colors.push_back({index,{data.real(),data.real(),data.real(),data.real()}});
                }
                if(data.remaining())throw std::runtime_error("Trailing X vertex color values");
            }else if(child.type=="MeshTextureCoords"){
                if(mesh.has_uvs)throw std::runtime_error("Duplicate X UV block");mesh.has_uvs=true;
                XNumbers data(child);const auto count=data.integer();
                if(count!=vertices||count>data.remaining()/2)throw std::runtime_error("X UV count mismatch");
                mesh.uvs.reserve(count);
                for(unsigned i=0;i<count;++i)mesh.uvs.push_back({data.real(),data.real()});
                if(data.remaining())throw std::runtime_error("Trailing X UV values");
            }else if(child.type=="MeshNormals"){
                if(mesh.has_normals)throw std::runtime_error("Duplicate X normal block");mesh.has_normals=true;
                XNumbers data(child);const auto count=data.integer();
                if(count>data.remaining()/3)throw std::runtime_error("X normal count exceeds data");
                mesh.normals.reserve(count);
                for(unsigned i=0;i<count;++i)mesh.normals.push_back({data.real(),data.real(),data.real()});
                if(data.integer()!=faces)throw std::runtime_error("X normal face count mismatch");
                mesh.face_normals.reserve(faces);
                for(unsigned i=0;i<faces;++i){
                    const auto corners=data.integer();
                    if(corners!=mesh.faces[i].size()||corners>data.remaining())throw std::runtime_error("X normal corner count mismatch");
                    std::vector<std::uint32_t> indices;indices.reserve(corners);
                    for(unsigned j=0;j<corners;++j){const auto index=data.integer();if(index>=count)throw std::runtime_error("X normal index out of range");indices.push_back(index);}
                    mesh.face_normals.push_back(std::move(indices));
                }
                if(data.remaining())throw std::runtime_error("Trailing X normal values");
            }
        }
        return mesh;
    }
};
}
