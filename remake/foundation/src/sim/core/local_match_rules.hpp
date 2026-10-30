#pragma once
#include <array>
#include <vector>
namespace daybreak {
// 40acb0 local-only input branch. Values are supplied by the application's config.
struct LocalMatchRules {
 int row=0,back=0,stage=0,variant=0;bool third_variant=true;
 int seconds=0;std::array<int,4> values{}; // 6cf3b8,3bc,3b0,3b4 in UI order.
 bool start_requested=false;
 enum class Event {none,changed,start,close};
 Event update(int horizontal,int vertical,unsigned confirm,unsigned cancel,unsigned shortcut=0,bool escape=false,std::vector<unsigned>* sounds=nullptr){
  const auto sound=[&](unsigned id){if(sounds)sounds->push_back(id);};
  if(horizontal==1||horizontal==-1){
   sound(2);
   if(row==0){stage=(stage+7+horizontal)%7;if(stage!=1&&variant==2)variant=1;}
   else if(row==1){const int count=stage==1?2+int(third_variant):2;variant=(variant+count+horizontal)%count;}
   else if(row==2)seconds=(seconds+300+horizontal*60)%300;
   else if(row<7){auto& value=values.at(row-3);const int step=row<5?25:20,minimum=row<5?50:40;value+=horizontal*step;if(value<minimum)value=200;if(value>200)value=minimum;}
   else back=1-back;
   return Event::changed;
  }
  if(vertical==1||vertical==-1){sound(2);row=(row+8+vertical)%8;if(row==1&&stage==0)row=vertical<0?0:2;return Event::changed;}
  if(confirm==1&&row==7){if(back){sound(1);back=0;return Event::close;}sound(0);start_requested=true;return Event::start;}
  if(cancel==1||escape){sound(1);back=0;return Event::close;}
  if(shortcut==1){sound(0);start_requested=true;return Event::start;}
  return Event::none;
 }
};
}
