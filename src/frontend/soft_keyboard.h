#pragma once
#include <array>
#include "frontend/screen.h"
namespace ui {
// FUN_00646bd0 stores eight packed (row << 4 | column) glyph coordinates.
struct PlayerName { std::array<uint8_t,8> cells{}; std::array<uint8_t,8> pages{}; size_t length=0; };
enum class KeyboardResult { Editing, Accepted, Cancelled };
class SoftKeyboard {
public:
    void begin(const PlayerName& name);
    KeyboardResult update(const ScreenInput& input);
    const PlayerName& value() const { return edited_; }
    int column() const { return column_; }
    int row() const { return row_; }
    int page() const { return page_; }
    bool load(SpriteRenderer& batch, std::string& error);
    void draw(SpriteRenderer& batch,float x,float y) const;
    void drawName(SpriteRenderer& batch,const PlayerName&,float x,float y) const;
private:
    PlayerName edited_;
    int column_=0,row_=0,page_=0;
    int sheets_[2]={-1,-1},actions_=-1;
};
}
