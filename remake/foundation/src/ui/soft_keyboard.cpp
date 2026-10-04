#include "ui/soft_keyboard.h"
#include "ui/hud_atlas.h"
#include <algorithm>
namespace ui {
void SoftKeyboard::begin(const PlayerName& name) {
    edited_=name; edited_.length=std::min(edited_.length,edited_.cells.size());
    column_=row_=page_=0;
}
KeyboardResult SoftKeyboard::update(const ScreenInput& in) {
    if(in.cancel) return KeyboardResult::Cancelled;
    if(in.up) row_=(row_+16)%17;
    else if(in.down) row_=(row_+1)%17;
    const int columns=row_==16?5:16;
    column_%=columns;
    if(in.left) column_=(column_+columns-1)%columns;
    else if(in.right) column_=(column_+1)%columns;
    if(!in.confirm) return KeyboardResult::Editing;
    if(row_<16) {
        if(edited_.length<edited_.cells.size()) {
            edited_.pages[edited_.length]=uint8_t(page_);
            edited_.cells[edited_.length++]=uint8_t(row_*16+column_);
        }
    } else switch(column_) {
        case 0: page_=1-page_; break;
        case 1:
            if(edited_.length<edited_.cells.size()) {
                edited_.pages[edited_.length]=0;
                edited_.cells[edited_.length++]=0;
            }
            break;
        case 2:
            if(edited_.length) {
                --edited_.length;
                edited_.cells[edited_.length]=0;
                edited_.pages[edited_.length]=0;
            }
            break;
        case 3: return KeyboardResult::Cancelled;
        case 4: return KeyboardResult::Accepted;
    }
    return KeyboardResult::Editing;
}
bool SoftKeyboard::load(SpriteRenderer& batch,std::string& error) {
    return uploadCnvSheet(batch,"data/chat/name_p1",sheets_[0],error) &&
           uploadCnvSheet(batch,"data/chat/name_p2",sheets_[1],error) &&
           uploadCnvSheet(batch,"data/network/nameMenu",actions_,error);
}
void SoftKeyboard::drawName(SpriteRenderer& batch,const PlayerName& name,float x,float y) const {
    for(size_t i=0;i<std::min(name.length,name.cells.size());++i) {
        const uint8_t cell=name.cells[i];
        batch.pushSprite(sheets_[name.pages[i]&1],{float(cell&15)*32,float(cell>>4)*32,32,32},0,0,x+i*24,y);
    }
}
void SoftKeyboard::draw(SpriteRenderer& batch,float x,float y) const {
    batch.pushSprite(sheets_[page_],{0,0,512,512},0,0,x,y);
    batch.pushSprite(actions_,{32,0,320,32},0,0,x,y+512);
    const float cursorX=x+(row_==16?column_*64.f:column_*32.f);
    const float cursorY=y+row_*32.f;
    const float width=row_==16?64.f:32.f;
    const UiColor color{1,0.85f,0.2f,1};
    batch.pushSolid({cursorX,cursorY,width,2},color);
    batch.pushSolid({cursorX,cursorY+30,width,2},color);
    batch.pushSolid({cursorX,cursorY,2,32},color);
    batch.pushSolid({cursorX+width-2,cursorY,2,32},color);
}
}
