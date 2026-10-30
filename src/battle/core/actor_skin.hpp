#pragma once
#include "actor_skeleton.hpp"
#include "actor_world_hierarchy.hpp"
#include <algorithm>
#include <utility>
#include <xmmintrin.h>
namespace daybreak {
struct ActorSkinWeight {unsigned bone;float weight;LegacyMatrix offset;};
struct ActorNativeSkinWeight {unsigned bone;float weight;};
struct ActorSkinMesh {
 XMesh mesh;unsigned owner=0;
 std::vector<std::vector<ActorSkinWeight>> weights;
 std::vector<std::pair<unsigned,LegacyMatrix>> used_bones;
 std::vector<std::vector<ActorNativeSkinWeight>> native_weights;
};
struct ActorSkin {
 std::vector<ActorSkinMesh> meshes;
 static std::vector<ActorNativeSkinWeight> native_vertex_weights(const ActorSkinMesh& mesh,unsigned vertex){
  std::vector<ActorNativeSkinWeight> weights;weights.reserve(mesh.weights.at(vertex).size());
  for(const auto& w:mesh.weights[vertex])weights.push_back({w.bone,w.weight});
  auto index=[&](unsigned bone){auto i=std::find_if(mesh.used_bones.begin(),mesh.used_bones.end(),[&](const auto& b){return b.first==bone;});if(i==mesh.used_bones.end())throw std::runtime_error("Skin influence lacks bone palette");return unsigned(i-mesh.used_bones.begin());};
  std::stable_sort(weights.begin(),weights.end(),[&](const auto& a,const auto& b){return index(a.bone)<index(b.bone);});
  //DLL5E12A selects at most four largest influences; later entries keep the
  //remaining swapped order.69879 packs index*2+weight in one FLOAT.
  //5E298 initializes best weight AND index to zero each pass. An all-zero
  //tail swaps with slot zero before filtering, changing positive order too.
  for(unsigned i=0;i<std::min<std::size_t>(4,weights.size());++i){unsigned best=0;float maximum=0;for(unsigned j=i;j<weights.size();++j)if(weights[j].weight>maximum){maximum=weights[j].weight;best=j;}std::swap(weights[i],weights[best]);}
  weights.erase(std::remove_if(weights.begin(),weights.end(),[](const auto& w){return w.weight<=0;}),weights.end());
  for(auto& w:weights){const float base=float(index(w.bone)*2);volatile float packed=base+w.weight;volatile float decoded=packed-base;w.weight=decoded;}
  return weights;
 }
 static std::array<float,3> transform_point(const LegacyMatrix& m,const std::array<float,3>& v){
  const auto xy=_mm_add_ps(_mm_mul_ps(_mm_loadu_ps(m.data()),_mm_set1_ps(v[0])),_mm_mul_ps(_mm_loadu_ps(m.data()+4),_mm_set1_ps(v[1])));
  const auto zw=_mm_add_ps(_mm_mul_ps(_mm_loadu_ps(m.data()+8),_mm_set1_ps(v[2])),_mm_loadu_ps(m.data()+12));
  const auto p=_mm_add_ps(xy,zw),w=_mm_shuffle_ps(p,p,_MM_SHUFFLE(3,3,3,3));
  const auto r=_mm_rcp_ps(w);
  const auto reciprocal=_mm_sub_ps(_mm_add_ps(r,r),_mm_mul_ps(_mm_mul_ps(r,w),r));
  float out[4];_mm_storeu_ps(out,_mm_mul_ps(p,reciprocal));return {out[0],out[1],out[2]};
 }
 static std::array<float,3> transform_normal(const LegacyMatrix& m,const std::array<float,3>& v){
  const auto xy=_mm_add_ps(_mm_mul_ps(_mm_loadu_ps(m.data()),_mm_set1_ps(v[0])),_mm_mul_ps(_mm_loadu_ps(m.data()+4),_mm_set1_ps(v[1])));
  const auto p=_mm_add_ps(xy,_mm_mul_ps(_mm_loadu_ps(m.data()+8),_mm_set1_ps(v[2])));
  float out[4];_mm_storeu_ps(out,p);return {out[0],out[1],out[2]};
 }
 static ActorSkin decode(const std::vector<XObject>& roots,const ActorSkeleton& skeleton){
  ActorSkin out;unsigned source_frame=0;
  auto visit=[&](auto&& self,const std::vector<XObject>& objects,unsigned owner)->void{
   for(const auto& object:objects){
    //Mesh ownership is source identity, not FrameFind's first name match.
    //Use the same authored DFS IDs as ActorSkeleton::decode, including duplicates.
    if(object.type=="Frame"&&!object.reference){auto id=++source_frame;const auto& bone=skeleton.bones.at(id);if(bone.name!=object.name||bone.parent!=owner)throw std::runtime_error("Mesh frame hierarchy mismatch");self(self,object.children,id);}
    if(object.type!="Mesh")continue;
    ActorSkinMesh mesh;mesh.owner=owner;mesh.mesh=XMesh::decode(object);mesh.weights.resize(mesh.mesh.vertices.size());
    for(const auto& child:object.children)if(child.type=="SkinWeights"){
     if(child.values.empty()||child.values.front().kind!=2)throw std::runtime_error("Missing skin bone name");
     const auto& token=child.values.front();std::string name(reinterpret_cast<const char*>(token.data),token.size);
     if(!name.empty()&&name.back()==0)name.pop_back();auto bone=skeleton.find(name);if(!bone)throw std::runtime_error("Unknown skin bone: "+name);
     auto numeric=child;numeric.values.erase(numeric.values.begin());XNumbers n(numeric);auto count=n.integer();
     if(count>n.remaining()/2)throw std::runtime_error("Truncated skin weights");
     std::vector<unsigned> indices;std::vector<float> weights;
     for(unsigned i=0;i<count;++i){auto index=n.integer();if(index>=mesh.weights.size())throw std::runtime_error("Skin vertex index");indices.push_back(index);}
     for(unsigned i=0;i<count;++i){auto weight=float(n.real());if(!std::isfinite(weight)||weight<0)throw std::runtime_error("Invalid skin weight");weights.push_back(weight);}
     LegacyMatrix offset;for(auto& v:offset){v=float(n.real());if(!std::isfinite(v))throw std::runtime_error("Skin offset range");}
     if(n.remaining())throw std::runtime_error("Trailing skin values");
     {
      auto existing=std::find_if(mesh.used_bones.begin(),mesh.used_bones.end(),[&](const auto& used){return used.first==bone;});
      if(existing==mesh.used_bones.end())mesh.used_bones.emplace_back(bone,offset);
      else if(existing->second!=offset)throw std::runtime_error("Conflicting skin bone offsets");
     }
     for(unsigned i=0;i<count;++i)mesh.weights[indices[i]].push_back({bone,weights[i],offset});
    }
    mesh.native_weights.resize(mesh.weights.size());for(unsigned v=0;v<mesh.weights.size();++v)mesh.native_weights[v]=native_vertex_weights(mesh,v);
    out.meshes.push_back(std::move(mesh));
   }
  };visit(visit,roots,0);if(source_frame+1!=skeleton.bones.size())throw std::runtime_error("Mesh frame count mismatch");return out;
 }
 //64E420 multiplies each bind offset by the frame's combined WORLD matrix.
 //Use the same hierarchy as contacts/attachments, never relative skin then world.
 void vertices_into(const ActorSkinMesh& mesh,const ActorSkeleton& pose,const LegacyMatrix& world,
  std::vector<std::array<float,3>>& result,std::vector<LegacyMatrix>& palette)const{
  std::vector<LegacyMatrix> combined;combine_actor_world_hierarchy(pose,world,combined);
  vertices_into_world(mesh,combined,result,palette);
 }
 void vertices_into_world(const ActorSkinMesh& mesh,const std::vector<LegacyMatrix>& combined,
  std::vector<std::array<float,3>>& result,std::vector<LegacyMatrix>& palette)const{
  result.resize(mesh.mesh.vertices.size());
  palette.resize(combined.size());
  // SkinWeights are immutable; prepare each bone's offset once at decode time
  // instead of searching every vertex influence on every rendered frame.
  for(const auto& used:mesh.used_bones)
   palette.at(used.first)=multiply_matrix_simd_order(used.second,combined.at(used.first));
  const auto& rigid=combined.at(mesh.owner);
  for(unsigned i=0;i<result.size();++i){
   result[i]={};
   const std::array<float,3> source{{float(mesh.mesh.vertices[i][0]),float(mesh.mesh.vertices[i][1]),float(mesh.mesh.vertices[i][2])}};
   if(mesh.used_bones.empty())result[i]=transform_point(rigid,source);
   else {std::vector<ActorNativeSkinWeight> fallback;const auto& weights=mesh.native_weights.size()==mesh.weights.size()?mesh.native_weights[i]:(fallback=native_vertex_weights(mesh,i));
    for(const auto& influence:weights){const auto p=transform_point(palette[influence.bone],source);for(unsigned c=0;c<3;++c){volatile float product=p[c]*influence.weight;volatile float sum=result[i][c]+product;result[i][c]=sum;}}
   }
   for(float v:result[i])if(!std::isfinite(v))throw std::runtime_error("Nonfinite skinned vertex");
  }
 }
 std::array<float,3> normal_into_world(const ActorSkinMesh& mesh,unsigned vertex,const std::array<float,3>& source,
  const std::vector<LegacyMatrix>& combined,const std::vector<LegacyMatrix>& palette)const{
  if(mesh.used_bones.empty())return transform_normal(combined.at(mesh.owner),source);
  std::vector<ActorNativeSkinWeight> fallback;const auto& weights=mesh.native_weights.size()==mesh.weights.size()?mesh.native_weights[vertex]:(fallback=native_vertex_weights(mesh,vertex));
  std::array<float,3> result{};for(const auto& influence:weights){const auto n=transform_normal(palette.at(influence.bone),source);for(unsigned a=0;a<3;++a){volatile float product=n[a]*influence.weight;volatile float sum=result[a]+product;result[a]=sum;}}
  return result;
 }
 // Legacy diagnostic API: blending matrices before normal transformation has
 // different rounding from UpdateSkinnedMesh. Rendering uses normal_into_world.
 void normal_matrices_into(const ActorSkinMesh& mesh,const ActorSkeleton& pose,const LegacyMatrix& world,
  const std::vector<LegacyMatrix>& palette,std::vector<std::array<float,9>>& result)const{
  std::vector<LegacyMatrix> combined;combine_actor_world_hierarchy(pose,world,combined);
  normal_matrices_into_world(mesh,combined,palette,result);
 }
 void normal_matrices_into_world(const ActorSkinMesh& mesh,const std::vector<LegacyMatrix>& combined,
  const std::vector<LegacyMatrix>& palette,std::vector<std::array<float,9>>& result)const{
  result.resize(mesh.mesh.vertices.size());
  const auto& rigid=combined.at(mesh.owner);
  for(unsigned v=0;v<result.size();++v){auto& r=result[v];r={};
   if(mesh.weights[v].empty())for(unsigned row=0;row<3;++row)for(unsigned c=0;c<3;++c)r[row*3+c]=rigid[row*4+c];
   else for(const auto& influence:mesh.weights[v]){const auto& m=palette.at(influence.bone);for(unsigned row=0;row<3;++row)for(unsigned c=0;c<3;++c)r[row*3+c]+=m[row*4+c]*influence.weight;}
   for(float value:r)if(!std::isfinite(value))throw std::runtime_error("Nonfinite skinned normal matrix");
  }
 }
 std::vector<std::array<float,3>> vertices(const ActorSkinMesh& mesh,const ActorSkeleton& pose,const LegacyMatrix& world)const{
  std::vector<std::array<float,3>> result;
  std::vector<LegacyMatrix> palette;
  vertices_into(mesh,pose,world,result,palette);
  return result;
 }
};
}
