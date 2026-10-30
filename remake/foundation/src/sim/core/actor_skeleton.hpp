#pragma once
#include "x_frame.hpp"
#include "legacy_matrix.hpp"
#include "frame_update.hpp"
namespace daybreak {
struct ActorBone {std::string name;unsigned parent=0,child=0,sibling=0;LegacyMatrix local{},world{};bool name_is_null=false;};
struct ActorSkeleton {
 std::vector<ActorBone> bones{ActorBone{}};unsigned root=0;
 std::vector<unsigned> name_lookup_order;
 //D3DXFrameFind43af3c searches this frame, its sibling subtree, then children.
 //Authored unnamed Frames have nonnull empty names; generated wrappers do not.
 void prepare_name_lookup(){
  name_lookup_order.clear();name_lookup_order.reserve(bones.size());
  auto visit=[&](auto&& self,unsigned id)->void{if(!id)return;const auto& b=bones.at(id);name_lookup_order.push_back(id);self(self,b.sibling);self(self,b.child);};
  visit(visit,root);
 }
 static ActorSkeleton decode(const std::vector<XObject>& objects){
  ActorSkeleton result;
  auto append=[&](auto&& self,const std::vector<XObject>& list,unsigned parent)->unsigned{
   unsigned first=0,last=0;
   for(const auto& object:list)if(object.type=="Frame"&&!object.reference){
    auto matrix=XFrameTransform::decode(object);ActorBone bone;bone.name=object.name;bone.parent=parent;
    for(unsigned i=0;i<16;++i){bone.local[i]=float(matrix.values[i]);if(!std::isfinite(bone.local[i]))throw std::runtime_error("Bone matrix exceeds float range");}
    unsigned id=unsigned(result.bones.size());result.bones.push_back(std::move(bone));if(last)result.bones[last].sibling=id;else first=id;last=id;
    auto child=self(self,object.children,id);result.bones[id].child=child;
   }
   return first;
  };result.root=append(append,objects,0);result.prepare_name_lookup();return result;
 }
 unsigned find(const std::string& name)const{
  if(!name_lookup_order.empty()){for(auto i:name_lookup_order)if(!bones[i].name_is_null&&bones[i].name==name)return i;return 0;}
  //Standalone callers may construct a hierarchy without using decode.
  auto search=[&](auto&& self,unsigned id)->unsigned{if(!id)return 0;const auto& b=bones.at(id);if(!b.name_is_null&&b.name==name)return id;auto found=self(self,b.sibling);return found?found:self(self,b.child);};
  return search(search,root);
 }
 void update(){
  struct Host{ActorSkeleton& s;unsigned extra(unsigned){return 0;}void multiply_local(unsigned,unsigned){}void combine(unsigned f,unsigned p){s.bones[f].world=multiply_matrix_scalar24(s.bones[f].local,s.bones[p].world);}void copy_local(unsigned f){s.bones[f].world=s.bones[f].local;}unsigned sibling(unsigned f){return s.bones[f].sibling;}unsigned child(unsigned f){return s.bones[f].child;}unsigned combined(unsigned f){return f;}} host{*this};
  if(root)update_frame(root,0,host);
 }
};
}
