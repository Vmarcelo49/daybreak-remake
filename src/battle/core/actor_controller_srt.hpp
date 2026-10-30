#pragma once
#include "actor_srt.hpp"
#include "legacy_quaternion_matrix.hpp"
#include "x_animation_keys.hpp"
#include <xmmintrin.h>
namespace daybreak {
// D3DX9_25's selected Vec4/QuaternionNormalize (60677f). Keep the paired
// sums and Newton step: scalar sqrt division gives different X-controller keys.
inline std::array<float,4> actor_controller_normalize4(const std::array<float,4>& q){
 __m128 x=_mm_set_ss(q[0]),y=_mm_set_ss(q[1]),z=_mm_set_ss(q[2]),w=_mm_set_ss(q[3]);
 auto n=_mm_add_ss(_mm_add_ss(_mm_mul_ss(x,x),_mm_mul_ss(y,y)),_mm_add_ss(_mm_mul_ss(z,z),_mm_mul_ss(w,w)));
 auto r=_mm_rsqrt_ss(n);
 auto f=_mm_mul_ss(_mm_mul_ss(_mm_sub_ss(_mm_set_ss(3.f),_mm_mul_ss(n,_mm_mul_ss(r,r))),_mm_set_ss(.5f)),r);
 return {_mm_cvtss_f32(_mm_mul_ss(x,f)),_mm_cvtss_f32(_mm_mul_ss(y,f)),_mm_cvtss_f32(_mm_mul_ss(z,f)),_mm_cvtss_f32(_mm_mul_ss(w,f))};
}
// Vec3Normalize 608854 has a different Newton multiplication order.
inline std::array<float,3> actor_controller_normalize3(const std::array<float,3>& v){
 __m128 x=_mm_set_ss(v[0]),y=_mm_set_ss(v[1]),z=_mm_set_ss(v[2]);
 auto n=_mm_add_ss(_mm_add_ss(_mm_mul_ss(x,x),_mm_mul_ss(y,y)),_mm_mul_ss(z,z));
 if(_mm_cvtss_f32(n)<1.4210854715202004e-14f)return {};
 auto r=_mm_rsqrt_ss(n);
 auto f=_mm_mul_ss(_mm_sub_ss(_mm_set_ss(3.f),_mm_mul_ss(_mm_mul_ss(r,n),r)),_mm_mul_ss(r,_mm_set_ss(.5f)));
 return {_mm_cvtss_f32(_mm_mul_ss(x,f)),_mm_cvtss_f32(_mm_mul_ss(y,f)),_mm_cvtss_f32(_mm_mul_ss(z,f))};
}
// X matrix-key type4 ingestion, distinct from public MatrixDecompose.
// The supplied actor key corpus has no tiny or reflected axes. Preserve the
// previous fallback for those unsupported inputs rather than changing FX math.
inline ActorSrt actor_controller_key_srt(const LegacyMatrix& m){
 ActorSrt out{};LegacyMatrix basis{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
 for(unsigned r=0;r<3;++r){
  volatile float x=m[r*4]*m[r*4],y=m[r*4+1]*m[r*4+1],z=m[r*4+2]*m[r*4+2];
  volatile float pair=r==2?z+y:x+y,n=r==2?pair+x:pair+z;out.scale[r]=std::sqrt(n);out.translation[r]=m[12+r];
  const auto v=actor_controller_normalize3({m[r*4],m[r*4+1],m[r*4+2]});for(unsigned c=0;c<3;++c)basis[r*4+c]=v[c];
 }
 const double determinant=double(m[0])*(double(m[5])*m[10]-double(m[6])*m[9])-double(m[1])*(double(m[4])*m[10]-double(m[6])*m[8])+double(m[2])*(double(m[4])*m[9]-double(m[5])*m[8]);
 if(*std::min_element(out.scale.begin(),out.scale.end())<.0001f||determinant<0){out=decompose_actor_key_srt(m);out.rotation[3]=-out.rotation[3];return out;}
 out.rotation=matrix_quaternion_scalar24(basis);return out;
}
inline std::vector<ActorSrt> actor_controller_keys(const XMatrixTrack& track){
 std::vector<ActorSrt> result;result.reserve(track.keys.size());
 for(const auto& key:track.keys){auto value=actor_controller_key_srt(key.matrix);
  if(!result.empty()){float dot=0;for(unsigned i:{0u,1u,3u,2u}){volatile float product=result.back().rotation[i]*value.rotation[i],sum=dot+product;dot=sum;}
   if(dot<0)for(auto& q:value.rotation)q=-q;
  }result.push_back(value);
 }return result;
}
inline std::vector<double> actor_controller_times(const XMatrixTrack& track,double ticks){
 std::vector<double> result;result.reserve(track.keys.size());for(const auto& key:track.keys)result.push_back(double(float(key.time)));return result;
}
// Native GetSRT caches its interval, including the side used at exact internal
// keys. Most gameplay samples stay in the same/adjacent interval; search only
// after larger clock jumps. Keep this state per actor, outside shared assets.
inline unsigned actor_controller_key_interval(const std::vector<double>& times,double time,unsigned* cursor){
 unsigned index=cursor?*cursor:0;index=std::min(index,unsigned(times.size()-2));unsigned low=0,high=0;
 if(time>times[index+1]){++index;if(time<=times[index+1]){if(cursor)*cursor=index;return index;}low=index;high=unsigned(times.size()-1);}
 else if(time<times[index]){if(index&&time>=times[index-1]){--index;if(cursor)*cursor=index;return index;}high=index;}
 else{if(cursor)*cursor=index;return index;}
 while(low<high){index=(low+high)/2;if(time<times[index])high=index;else if(time>times[index+1])low=index+1;else break;}
 if(cursor)*cursor=index;return index;
}
inline ActorSrt sample_actor_controller_srt(const std::vector<double>& times,const std::vector<ActorSrt>& keys,double time,double ticks=1,unsigned* cursor=nullptr){
 if(!std::isfinite(time)||keys.empty())throw std::runtime_error("Invalid prepared actor sample");
 // GetSourceTicksPerSecond is4800 in the supplied models. X keys remain
 // FLOAT source ticks; GetSRT4394b7 multiplies periodic seconds under PC24.
 time=double(float(time*ticks));
 if(time<=times.front())return keys.front();if(time>=times.back())return keys.back();
 const auto lo=actor_controller_key_interval(times,time,cursor),i=lo+1;
 // GetSRT subtracts DOUBLE key/query times under x87 PC24 before division.
 // Explicit stores reproduce that precision without depending on thread FPU state.
 volatile float span=float(times[i]-times[lo]),offset=float(time-times[lo]),t=offset/span;
 if(span<=1.0e-8f)return keys[i];
 const auto& a=keys[lo];const auto& b=keys[i];ActorSrt out;
 auto lerp=[&](float start,float end){volatile float delta=end-start,step=delta*t,value=start+step;return value;};
 for(unsigned j=0;j<3;++j){out.scale[j]=lerp(a.scale[j],b.scale[j]);out.translation[j]=lerp(a.translation[j],b.translation[j]);}
 for(unsigned j=0;j<4;++j)out.rotation[j]=lerp(a.rotation[j],b.rotation[j]);
 out.rotation=actor_controller_normalize4(out.rotation);return out;
}
inline LegacyMatrix compose_actor_controller_srt(ActorSrt value){
 value.rotation=actor_controller_normalize4(value.rotation);auto result=quaternion_matrix_scalar24(value.rotation);
 for(unsigned r=0;r<3;++r){for(unsigned c=0;c<3;++c){volatile float v=result[r*4+c]*value.scale[r];result[r*4+c]=v;}result[12+r]=value.translation[r];}return result;
}
struct ActorControllerSrtMix {
 float weight=0;ActorSrt sum{};
 void add(const ActorSrt& value,float amount){
  if(!(amount>0))return;float dot=0;if(weight>0)for(unsigned i=0;i<4;++i){volatile float p=sum.rotation[i]*value.rotation[i],s=dot+p;dot=s;}
  const float sign=dot<0?-1.f:1.f;
  for(unsigned i=0;i<3;++i){volatile float s=value.scale[i]*amount,t=value.translation[i]*amount;sum.scale[i]+=s;sum.translation[i]+=t;}
  for(unsigned i=0;i<4;++i){volatile float a=amount*sign,q=value.rotation[i]*a;sum.rotation[i]+=q;}weight+=amount;
 }
 ActorSrt value()const{if(!(weight>0))throw std::logic_error("Empty actor controller mixture");auto out=sum;volatile float reciprocal=1.f/weight;for(unsigned i=0;i<3;++i){out.scale[i]*=reciprocal;out.translation[i]*=reciprocal;}return out;}
};
}
