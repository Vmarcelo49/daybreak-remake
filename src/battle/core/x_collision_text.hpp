#pragma once
#include "stage_collision_mesh.hpp"
#include "x_polygon_fan.hpp"
#include <cstdlib>
namespace daybreak {
// Geometry and vertex-color reader for text X collision meshes. Material,
// normal and UV children are skipped; this is not a rendering X importer.
class XCollisionTextReader {
    std::string text_;std::size_t pos_=16;std::string token_;
    void next(){
        while(pos_<text_.size()){
            const char c=text_[pos_];
            if(c==' '||c=='\r'||c=='\n'||c=='\t'){++pos_;continue;}
            if(c=='#'||(c=='/'&&pos_+1<text_.size()&&text_[pos_+1]=='/')){while(pos_<text_.size()&&text_[pos_]!='\n')++pos_;continue;}
            break;
        }
        token_.clear();if(pos_==text_.size())return;
        const auto start=pos_++;const char c=text_[start];
        if(c=='"'){
            while(pos_<text_.size()&&text_[pos_]!='"'){if(text_[pos_]=='\\'&&pos_+1<text_.size())++pos_;++pos_;}
            if(pos_==text_.size())throw std::runtime_error("Unclosed X string");++pos_;
        }else if(std::string("{};,[]<>").find(c)==std::string::npos){
            while(pos_<text_.size()&&std::string(" \t\r\n{};,[]<>\"").find(text_[pos_])==std::string::npos)++pos_;
        }
        token_=text_.substr(start,pos_-start);
    }
    void separators(){while(token_==";"||token_==",")next();}
    double number(){
        separators();if(token_.empty())throw std::runtime_error("Missing X text number");char* end=nullptr;
        const double value=std::strtod(token_.c_str(),&end);
        if(end!=token_.c_str()+token_.size()||!std::isfinite(value))throw std::runtime_error("Invalid X text number");next();return value;
    }
    unsigned count(){const auto value=number();if(value<0||value>1000000||std::floor(value)!=value)throw std::runtime_error("Invalid X text count/index");return static_cast<unsigned>(value);}
    void skip_block(){
        if(token_!="{")throw std::runtime_error("Missing X block");unsigned depth=1;next();
        while(depth){if(token_.empty())throw std::runtime_error("Unclosed X block");if(token_=="{")++depth;else if(token_=="}")--depth;if(depth>256)throw std::runtime_error("X depth limit");next();}
    }
public:
    explicit XCollisionTextReader(const std::vector<std::uint8_t>& data):text_(data.begin(),data.end()){
        if(text_.size()<16||text_.substr(0,4)!="xof "||text_.substr(8,4)!="txt "||(text_.substr(4,4)!="0302"&&text_.substr(4,4)!="0303")||(text_.substr(12,4)!="0032"&&text_.substr(12,4)!="0064"))throw std::runtime_error("Unsupported text X header");next();
    }
    StageCollisionMesh read(std::vector<std::string>* mesh_names=nullptr){
        StageCollisionMesh out;unsigned mesh=0,frame_depth=0;
        while(!token_.empty()){
            if(token_=="template"){next();next();skip_block();continue;}
            if(token_=="Frame"){next();if(token_!="{")next();if(token_!="{")throw std::runtime_error("Missing Frame block");if(++frame_depth>256)throw std::runtime_error("X frame depth limit");next();continue;}
            if(token_=="}"&&frame_depth){--frame_depth;next();continue;}
            if(token_==";"||token_==","){next();continue;}
            const auto type=token_;next();const auto object_name=token_=="{"?std::string{}:token_;if(token_!="{")next();
            if(type!="Mesh"){
                if(type!="Header"&&type!="FrameTransformMatrix"&&type!="Material")throw std::runtime_error("Unsupported collision X object: "+type);
                skip_block();continue;
            }
            if(token_!="{")throw std::runtime_error("Missing Mesh block");next();
            if(mesh_names)mesh_names->push_back(object_name);
            const unsigned vertices=count();std::vector<CollisionPoint> points;points.reserve(vertices);
            for(unsigned i=0;i<vertices;++i)points.push_back({{number(),number(),number()}});
            const auto mesh_begin=out.faces.size();const unsigned faces=count();unsigned triangle_id=0;
            for(unsigned f=0;f<faces;++f){
                const auto corners=count();if(corners<3||corners>64)throw std::runtime_error("Unsupported collision polygon size");
                if(corners>3)++out.provisional_polygons;
                std::vector<std::uint32_t> indices;for(unsigned c=0;c<corners;++c)indices.push_back(count());
                for(const auto& indices3:expand_x_polygon(indices,vertices)){StageCollisionFace face;face.mesh=mesh;face.face=triangle_id++;face.source_polygon=f;for(unsigned c=0;c<3;++c){face.source_vertices[c]=indices3[c];face.vertices[c]=points.at(indices3[c]);}out.faces.push_back(face);}
            }
            separators();
            bool has_colors=false,has_materials=false;std::vector<std::optional<std::array<double,4>>> colors(vertices);
            std::vector<unsigned> attributes(faces,0);
            while(token_!="}"){
                if(token_.empty())throw std::runtime_error("Unclosed collision Mesh");const auto child=token_;next();if(token_!="{")next();
                if(child=="MeshVertexColors"){
                    if(has_colors||token_!="{")throw std::runtime_error("Invalid collision color block");has_colors=true;next();const auto entries=count();
                    if(entries>vertices)throw std::runtime_error("Too many collision colors");
                    for(unsigned i=0;i<entries;++i){const auto index=count();if(index>=vertices||colors[index])throw std::runtime_error("Invalid collision color index");colors[index]=std::array<double,4>{{number(),number(),number(),number()}};}
                    separators();if(token_!="}")throw std::runtime_error("Trailing collision color data");next();
                }else if(child=="MeshMaterialList"){
                    if(has_materials||token_!="{")throw std::runtime_error("Invalid collision material list");has_materials=true;next();
                    const unsigned materials=count(),entries=count();if(entries!=faces)throw std::runtime_error("Collision material face count mismatch");
                    for(auto& attribute:attributes){attribute=count();if(attribute>=materials)throw std::runtime_error("Collision material index out of range");}
                    // Geometry needs the IDs, not material definitions/references.
                    unsigned depth=1;while(depth){if(token_.empty())throw std::runtime_error("Unclosed collision material list");if(token_=="{")++depth;else if(token_=="}")--depth;next();}
                }else skip_block();separators();
            }
            for(auto i=mesh_begin;i<out.faces.size();++i){out.faces[i].attribute=attributes.at(out.faces[i].source_polygon);out.faces[i].has_color_block=has_colors;for(unsigned c=0;c<3;++c)out.faces[i].colors[c]=colors.at(out.faces[i].source_vertices[c]);}
            next();++mesh;
        }
        if(frame_depth)throw std::runtime_error("Unclosed collision Frame");out.finalize_legacy_face_order();return out;
    }
};
}
