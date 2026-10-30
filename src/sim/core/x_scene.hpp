#pragma once
#include "x_material.hpp"
#include "x_frame.hpp"
#include "legacy_matrix.hpp"
namespace daybreak {
enum class XMatrixMode {Scalar24,SimdOrder};
struct XSceneMesh {
    std::string name;
    XMesh geometry;
    XMaterialBinding binding;
    LegacyMatrix transform;
};
// Static scene snapshot: all returned data owns its storage. Animation and
// non-material object references are deliberately rejected, not silently lost.
struct XScene {
    std::vector<XSceneMesh> meshes;
    static XScene decode(const std::vector<std::uint8_t>& bytes,XMatrixMode mode){
        XObjectReader reader(bytes);const auto roots=reader.read();XMaterialNames names(roots);XScene out;
        const LegacyMatrix identity{{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}};
        auto visit=[&](auto&& self,const std::vector<XObject>& objects,const LegacyMatrix& parent,bool has_parent)->void{
            for(const auto& object:objects){
                if(object.reference)throw std::runtime_error("Unsupported X scene reference");
                if(object.type=="Frame"){
                    const auto parsed=XFrameTransform::decode(object);LegacyMatrix local{};
                    for(unsigned i=0;i<16;++i){local[i]=static_cast<float>(parsed.values[i]);if(!std::isfinite(local[i]))throw std::runtime_error("X frame exceeds float range");}
                    const auto combined=has_parent?(mode==XMatrixMode::Scalar24?multiply_matrix_scalar24(local,parent):multiply_matrix_simd_order(local,parent)):local;
                    self(self,object.children,combined,true);
                }else if(object.type=="Mesh"){
                    auto geometry=XMesh::decode(object);auto binding=XMaterialBinding::decode(object,geometry.faces.size(),names);
                    out.meshes.push_back({object.name,std::move(geometry),std::move(binding),parent});
                }else if(object.type!="Material"&&object.type!="FrameTransformMatrix"){
                    throw std::runtime_error("Unsupported X scene object: "+object.type);
                }
            }
        };
        visit(visit,roots,identity,false);return out;
    }
};
}
