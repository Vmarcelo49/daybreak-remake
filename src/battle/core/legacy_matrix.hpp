#pragma once
#include <array>
namespace daybreak {
using LegacyMatrix=std::array<float,16>;
// DLL RVA 0x208719 SIMD order. Rows 0/3 pair sums; rows 1/2 sum left-to-right.
inline LegacyMatrix multiply_matrix_simd_order(const LegacyMatrix& a,const LegacyMatrix& b){
    LegacyMatrix out{};
    for(unsigned row=0;row<4;++row)for(unsigned col=0;col<4;++col){
        volatile float p0=a[row*4]*b[col],p1=a[row*4+1]*b[4+col];
        volatile float p2=a[row*4+2]*b[8+col],p3=a[row*4+3]*b[12+col];
        volatile float first=p0+p1;
        if(row==0||row==3){volatile float second=p2+p3;out[row*4+col]=first+second;}
        else {volatile float second=first+p2;out[row*4+col]=second+p3;}
    }
    return out;
}
// d3dx9_25.dll RVA 0x3f02b scalar implementation, x87 24-bit precision.
// CPU-dispatched SIMD implementations are not covered by this function.
inline LegacyMatrix multiply_matrix_scalar24(const LegacyMatrix& a,const LegacyMatrix& b){
    constexpr unsigned order[16][4]={{3,0,2,1},{1,3,2,0},{3,0,2,1},{3,2,0,1},
        {3,0,1,2},{2,3,1,0},{1,3,0,2},{1,3,2,0},
        {3,0,1,2},{3,2,1,0},{1,0,3,2},{3,2,1,0},
        {3,2,0,1},{3,1,2,0},{2,1,0,3},{3,1,0,2}};
    LegacyMatrix out{};
    for(unsigned i=0;i<16;++i){
        auto product=[&](unsigned k){volatile float value=a[(i/4)*4+k]*b[k*4+i%4];return value;};
        volatile float sum=product(order[i][0]);
        for(unsigned j=1;j<4;++j)sum=sum+product(order[i][j]);
        out[i]=sum;
    }
    return out;
}
}
