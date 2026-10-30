#pragma once
#include "legacy_matrix.hpp"
#include <cmath>
namespace daybreak {
// D3DX scalar 440b01, x87 24-bit arithmetic. MatrixDecompose flips w afterward.
inline std::array<float,4> matrix_quaternion_scalar24(const LegacyMatrix& m){
 auto add=[](float a,float b){volatile float r=a+b;return r;};auto sub=[](float a,float b){volatile float r=a-b;return r;};
 auto mul=[](float a,float b){volatile float r=a*b;return r;};
 std::array<float,4> q{};float trace=add(add(m[5],m[0]),m[10]);
 if(trace>0.f){q[3]=mul(std::sqrt(add(trace,1.f)),0.5f);volatile float factor=0.25f/q[3];q[0]=mul(sub(m[6],m[9]),factor);q[1]=mul(sub(m[8],m[2]),factor);q[2]=mul(sub(m[1],m[4]),factor);}
 else{float d[3]={sub(sub(m[0],m[5]),m[10]),sub(sub(m[5],m[0]),m[10]),sub(m[10],add(m[5],m[0]))};unsigned i=d[0]<d[1]?1:0;if(d[i]<d[2])i=2;unsigned j=(i+1)%3,k=(j+1)%3;q[i]=mul(std::sqrt(add(d[i],1.f)),0.5f);volatile float factor=0.25f/q[i];q[j]=mul(add(m[j*4+i],m[i*4+j]),factor);q[k]=mul(add(m[k*4+i],m[i*4+k]),factor);q[3]=mul(sub(m[j*4+k],m[k*4+j]),factor);}
 return q;
}
}
