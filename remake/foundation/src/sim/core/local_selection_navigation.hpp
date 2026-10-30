#pragma once
#include <array>
#include <stdexcept>
namespace daybreak {
// 408330 local initialization and409340 state0 cursor/join prefix.
// Inputs are original signed duration counters, not raw held axes.
struct LocalSelectionNavigation {
 std::array<int,4> cursor{{0,-1,-1,-1}};
 bool update(unsigned controller,int horizontal,int vertical,unsigned confirm){
  auto& position=cursor.at(controller);
  if(position<0){if(horizontal||vertical||confirm){position=int(controller)+(controller>1?1:0);return true;}return false;}
  if(position>5)throw std::out_of_range("Selection cursor outside six cells");
  if(horizontal==1||horizontal==-1){
   if(position==5&&horizontal==1)position=4;
   else if(position==2&&horizontal==-1)position=1;
   else position=((position/3+2+horizontal)%2)*3+position%3;
   return true;
  }
  if(vertical==1||vertical==-1){position=(position+3+vertical)%3+(position/3)*3;return true;}
  return false;
 }
 // Cells2 and5 are menu actions; other cells correspond to actor slots0..3.
 int actor_slot(unsigned controller)const{const auto p=cursor.at(controller);return p<0||p==2||p==5?-1:p%3+(p/3)*2;}
};
}
