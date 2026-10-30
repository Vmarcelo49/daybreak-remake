#pragma once
#include "battle_damage_scaling.hpp"
#include "battle_random.hpp"
#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
namespace daybreak {
inline unsigned victory_grade(unsigned limit,unsigned winner_used,unsigned loser_used,unsigned hp0,unsigned hp1){
 const auto capped=std::min(damage_signed(limit),damage_signed(loser_used));
 const auto margin=damage_signed(unsigned(capped)-winner_used);
 return margin<30?(damage_signed(hp0)<5000&&damage_signed(hp1)<5000?4u:3u):margin<50?2u:1u;
}
struct VictoryLine {std::string voice,text,script;unsigned grade=0,index=0;};
// Win scripts are CP932 byte strings: alternating VOICE and formatted-text lines.
inline std::vector<VictoryLine> read_victory_lines(const std::vector<std::uint8_t>& bytes){
 std::vector<std::string> lines;std::string line;
 for(auto c:bytes){if(c=='\r'||c=='\n'){if(!line.empty()){lines.push_back(line);line.clear();}}else line+=char(c);}
 if(!line.empty())lines.push_back(line);
 if(lines.empty()||lines.size()%2)throw std::runtime_error("Incomplete victory voice/text pairs");
 std::vector<VictoryLine> out;
 for(unsigned i=0;i<lines.size();i+=2){
  if(lines[i].compare(0,6,"VOICE ")||lines[i].size()==6)throw std::runtime_error("Invalid victory voice command");
  out.push_back({lines[i].substr(6),lines[i+1],{},0,i/2});
 }
 return out;
}
template<class Exists,class Read> VictoryLine select_victory_line(unsigned character0,unsigned character1,unsigned grade,BattleRandom& random,Exists exists,Read read){
 if(character1<character0)std::swap(character0,character1);
 char path[96];std::snprintf(path,sizeof path,"data/scenario/win/%02u-%02u-%u.txt",character0,character1,grade);
 if(!exists(path)){
  unsigned fallback=character0<16?(character1==16?16:17):character0==17?17:character1==16?16:16+random.next()%2;
  std::snprintf(path,sizeof path,"data/scenario/win/%02u.txt",fallback);
 }
 auto lines=read_victory_lines(read(path));auto selected=lines[random.next()%lines.size()];selected.script=path;selected.grade=grade;return selected;
}
}
