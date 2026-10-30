#pragma once
#include "x_scene.hpp"
#include "legacy_stage_intersection_scalar24.hpp"
#include <map>
#include <algorithm>
#include <limits>
#include <optional>
namespace daybreak {
using CollisionPoint=std::array<double,3>;
struct StageCollisionFace {
    std::array<CollisionPoint,3> vertices;
    unsigned mesh=0,face=0,source_polygon=0;
    std::array<unsigned,3> source_vertices{};
    // Preserve unquantized RGBA. Missing entries stay explicit until original
    // defaults and the D3DCOLOR conversion have been verified.
    std::array<std::optional<std::array<double,4>>,3> colors{};
    bool has_color_block=false;
    unsigned attribute=0; // Original mesh attribute ID, retained across fan expansion.
};
struct StageRayHit {unsigned mesh=0,face=0;double u=0,v=0,distance=0;};
inline CollisionPoint collision_sub(const CollisionPoint& a,const CollisionPoint& b){return {{a[0]-b[0],a[1]-b[1],a[2]-b[2]}};}
inline CollisionPoint collision_cross(const CollisionPoint& a,const CollisionPoint& b){return {{a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]}};}
inline double collision_dot(const CollisionPoint& a,const CollisionPoint& b){return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];}
// Original D3DX mesh vertex/ray boundary is float3. Individual admitted
// triangles are distinct from a whole mesh's closest/publication gate.
inline LegacyStageVector collision_float_point(const CollisionPoint& point){return {{float(point[0]),float(point[1]),float(point[2])}};}
inline LegacyStageTriangle collision_native_triangle(const StageCollisionFace& face){
    return LegacyStageTriangle({{collision_float_point(face.vertices[0]),collision_float_point(face.vertices[1]),collision_float_point(face.vertices[2])}});
}
inline std::optional<StageRayHit> intersect_stage_face(const StageCollisionFace& face,const CollisionPoint& origin,const CollisionPoint& direction){
    const LegacyStageRay ray(collision_float_point(origin),collision_float_point(direction));
    const auto triangle=collision_native_triangle(face);if(!ray.admits(triangle))return {};
    if(auto hit=legacy_stage_intersect_triangle24(triangle,ray))return StageRayHit{face.mesh,face.face,hit->u,hit->v,hit->distance};
    return {};
}
struct StageCollisionMesh {
    std::vector<StageCollisionFace> faces;
    struct FaceBounds {CollisionPoint low,high;};
    // Retained bounds are diagnostic metadata; the original DLL does not
    // use a slab rejection before its PC24 triangle calculation.
    std::vector<FaceBounds> face_bounds;
    // Immutable-stage cache: one XY-side calculation per unique float vertex,
    // then the original face admission test. No double AABB approximation.
    std::vector<LegacyStageVector> native_vertices;
    std::vector<LegacyStageTriangle> native_triangles;
    std::vector<std::array<unsigned,3>> native_face_vertices;
    void prepare_acceleration(){
        face_bounds.clear();face_bounds.reserve(faces.size());
        native_vertices.clear();native_triangles.clear();native_face_vertices.clear();
        native_triangles.reserve(faces.size());native_face_vertices.reserve(faces.size());
        std::map<std::array<std::uint32_t,3>,unsigned> vertex_index;
        for(const auto& face:faces){
            FaceBounds bounds{face.vertices[0],face.vertices[0]};
            for(unsigned corner=1;corner<3;++corner)for(unsigned axis=0;axis<3;++axis){
                bounds.low[axis]=std::min(bounds.low[axis],face.vertices[corner][axis]);
                bounds.high[axis]=std::max(bounds.high[axis],face.vertices[corner][axis]);
            }
            // Historical double-backend bounds, retained for diagnostics only.
            // Their padding is not a proof of PC24 native hit conservatism.
            for(unsigned axis=0;axis<3;++axis){
                const double padding=1e-6*std::max({1.,std::abs(bounds.low[axis]),std::abs(bounds.high[axis])});
                bounds.low[axis]-=padding;bounds.high[axis]+=padding;
            }
            face_bounds.push_back(bounds);
            const auto triangle=collision_native_triangle(face);std::array<unsigned,3> indices{};
            for(unsigned corner=0;corner<3;++corner){
                std::array<std::uint32_t,3> key{};for(unsigned axis=0;axis<3;++axis)std::memcpy(&key[axis],&triangle.vertices[corner][axis],4);
                const auto inserted=vertex_index.emplace(key,unsigned(native_vertices.size()));
                if(inserted.second)native_vertices.push_back(triangle.vertices[corner]);indices[corner]=inserted.first->second;
            }
            native_triangles.push_back(triangle);native_face_vertices.push_back(indices);
        }
    }
    static bool ray_may_hit_bounds(const FaceBounds& bounds,const CollisionPoint& origin,const CollisionPoint& direction){
        double entry_distance=0,exit_distance=std::numeric_limits<double>::infinity();
        for(unsigned axis=0;axis<3;++axis){
            if(direction[axis]==0){
                if(origin[axis]<bounds.low[axis]||origin[axis]>bounds.high[axis])return false;
                continue;
            }
            const double a=(bounds.low[axis]-origin[axis])/direction[axis];
            const double b=(bounds.high[axis]-origin[axis])/direction[axis];
            entry_distance=std::max(entry_distance,std::min(a,b));exit_distance=std::min(exit_distance,std::max(a,b));
            if(entry_distance>exit_distance)return false;
        }
        return true;
    }
    // Initial fan split matches the original loader. This counter still marks
    // unresolved FINAL mapping to the optimized D3DX mesh's triangle IDs.
    // face is our per-mesh triangle ID; source_polygon preserves provenance.
    unsigned provisional_polygons=0;
    // Original static mesh load/Optimize(0x03000000) groups faces by material.
    // Stable order within each attribute keeps source provenance and tie order.
    void finalize_legacy_face_order(){
        std::stable_sort(faces.begin(),faces.end(),[](const StageCollisionFace& a,const StageCollisionFace& b){
            return a.mesh<b.mesh||(a.mesh==b.mesh&&a.attribute<b.attribute);
        });
        unsigned mesh=~0u,triangle=0;for(auto& face:faces){if(face.mesh!=mesh){mesh=face.mesh;triangle=0;}face.face=triangle++;}
    }
    static StageCollisionMesh from_scene(const XScene& scene){
        StageCollisionMesh out;
        // Original 0x42d3b0 intersects each raw mesh without applying frame matrices.
        for(unsigned m=0;m<scene.meshes.size();++m){const auto& mesh=scene.meshes[m].geometry;
            std::vector<std::optional<std::array<double,4>>> colors(mesh.vertices.size());
            for(const auto& color:mesh.colors){if(colors.at(color.index))throw std::runtime_error("Duplicate collision vertex color");colors[color.index]=color.rgba;}
            for(unsigned f=0;f<mesh.faces.size();++f){
                if(mesh.faces[f].size()!=3)throw std::runtime_error("Collision mesh requires triangles");
                StageCollisionFace face;face.mesh=m;face.face=f;face.source_polygon=f;
                face.attribute=scene.meshes[m].binding.present?scene.meshes[m].binding.faces.at(f):0;
                face.has_color_block=mesh.has_colors;
                for(unsigned c=0;c<3;++c){const auto index=mesh.faces[f][c];face.source_vertices[c]=index;face.vertices[c]=mesh.vertices.at(index);face.colors[c]=colors.at(index);}
                out.faces.push_back(face);
            }
        }out.finalize_legacy_face_order();return out;
    }
    std::vector<StageRayHit> intersect(const CollisionPoint& origin,const CollisionPoint& direction)const{
        const LegacyStageRay ray(collision_float_point(origin),collision_float_point(direction));
        const bool prepared=native_triangles.size()==faces.size()&&native_face_vertices.size()==faces.size()&&!faces.empty();
        std::vector<unsigned char> sides;if(prepared){sides.reserve(native_vertices.size());for(const auto& vertex:native_vertices)sides.push_back(ray.side(vertex));}
        std::map<unsigned,unsigned> mesh_index;std::vector<std::vector<StageRayHit>> per_mesh;
        for(std::size_t i=0;i<faces.size();++i){
            const auto& face=faces[i];const auto inserted=mesh_index.emplace(face.mesh,unsigned(per_mesh.size()));
            if(inserted.second)per_mesh.emplace_back();
            if(prepared){const auto& v=native_face_vertices[i];if(sides[v[0]]==sides[v[1]]&&sides[v[0]]==sides[v[2]])continue;}
            const auto triangle=prepared?native_triangles[i]:collision_native_triangle(face);
            if(!prepared&&!ray.admits(triangle))continue;
            if(auto hit=legacy_stage_intersect_triangle24(triangle,ray))per_mesh[inserted.first->second].push_back({face.mesh,face.face,hit->u,hit->v,hit->distance});
        }
        std::vector<StageRayHit> hits;
        for(const auto& group:per_mesh){
            // D3DX publishes ALL hits only after a strict closest update below
            // 0x799a130c. Its 63-record linked blocks are copied newest first.
            bool publish=false;for(const auto& hit:group)if(float(hit.distance)<legacy_stage_closest_ceiling()){publish=true;break;}
            if(!publish)continue;
            for(std::size_t end=group.size();end;){const auto begin=((end-1)/63)*63;hits.insert(hits.end(),group.begin()+begin,group.begin()+end);end=begin;}
        }
        return hits;
    }
    const StageCollisionFace& face_for_hit(const StageRayHit& hit)const{
        for(const auto& face:faces)if(face.mesh==hit.mesh&&face.face==hit.face)return face;
        throw std::out_of_range("Collision hit refers to unknown triangle");
    }
};
}
