#pragma once
#include "actor_srt.hpp"
#include "legacy_quaternion_matrix.hpp"
namespace daybreak {
// Original X matrix-key loader / GetSRT: shortest-path linear quaternion keys.
// The controller normalizes its output and reconstructs SRT even at exact keys.
inline ActorSrt interpolate_actor_key_srt(const ActorSrt& a,const ActorSrt& b,float t){
 ActorSrt out;float dot=0;
 for(unsigned i=0;i<4;++i){volatile float p=a.rotation[i]*b.rotation[i];volatile float s=dot+p;dot=s;}
 const float sign=dot<0?-1.f:1.f;
 for(unsigned i=0;i<4;++i){volatile float end=b.rotation[i]*sign;volatile float delta=end-a.rotation[i];volatile float step=delta*t;out.rotation[i]=a.rotation[i]+step;}
 for(unsigned i=0;i<3;++i){
  volatile float ds=b.scale[i]-a.scale[i],dt=b.translation[i]-a.translation[i];
  volatile float ss=ds*t,st=dt*t;out.scale[i]=a.scale[i]+ss;out.translation[i]=a.translation[i]+st;
 }
 return out;
}
inline LegacyMatrix compose_actor_keyframe(ActorSrt value){
 float squared=0;for(float q:value.rotation){volatile float p=q*q;volatile float s=squared+p;squared=s;}
 if(!(squared>0))throw std::runtime_error("Degenerate actor key quaternion");
 const float length=std::sqrt(squared);for(auto& q:value.rotation)q/=length;
 value.rotation[3]=-value.rotation[3];auto result=quaternion_matrix_scalar24(value.rotation);
 for(unsigned r=0;r<3;++r){
  for(unsigned c=0;c<3;++c){volatile float v=result[r*4+c]*value.scale[r];result[r*4+c]=v;}
  result[12+r]=value.translation[r];
 }
 return result;
}
}
