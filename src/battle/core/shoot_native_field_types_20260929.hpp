#pragma once
namespace daybreak {
// NEW raw FIADD correction: integer arithmetic is numeric, as is FILD.
inline float shooting_source_float(unsigned ch,unsigned we,unsigned state,unsigned index,int word){
 const unsigned key=(ch*3+we)*1000+state;
 if(index<0x3a||index>0x3e)return remaining_real(unsigned(word));
 switch(index){
 default:break;}return float(word);
}
}
