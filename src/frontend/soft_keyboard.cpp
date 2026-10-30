#include "ui/soft_keyboard.h"
#include "ui/hud_atlas.h"
#include <algorithm>
namespace ui {
namespace {
// The name-entry grid FUN_00646bd0's sheet draws: a 16x16 character grid, then one action row
// of five cells (page flip, space, backspace, cancel, accept). The grid's cells are 32x32 and
// the action strip is 320 px of five 64 px cells.
constexpr int kGridColumns = 16;
constexpr int kCharacterRows = 16;
constexpr int kRowCount = kCharacterRows + 1;
constexpr float kCellSize = 32.f;
// The action row's cells, in the sheet's own order.
enum ActionCell { kActionPage, kActionSpace, kActionBackspace, kActionCancel, kActionAccept, kActionCellCount };
constexpr float kActionCellWidth = 320.f / (float)kActionCellCount;
// A packed PlayerName cell (row << 4 | column) drawn 24 px apart.
constexpr float kNameAdvance = 24.f;
}  // namespace

void SoftKeyboard::begin(const PlayerName& name) {
    edited_ = name;
    edited_.length = std::min(edited_.length, edited_.cells.size());
    column_ = row_ = page_ = 0;
}

KeyboardResult SoftKeyboard::update(const ScreenInput& in) {
    if (in.cancel) return KeyboardResult::Cancelled;
    if (in.up) row_ = (row_ + kRowCount - 1) % kRowCount;
    else if (in.down) row_ = (row_ + 1) % kRowCount;
    const int columns = row_ == kCharacterRows ? kActionCellCount : kGridColumns;
    column_ %= columns;
    if (in.left) column_ = (column_ + columns - 1) % columns;
    else if (in.right) column_ = (column_ + 1) % columns;
    if (!in.confirm) return KeyboardResult::Editing;
    if (row_ < kCharacterRows) {
        if (edited_.length < edited_.cells.size()) {
            edited_.pages[edited_.length] = static_cast<uint8_t>(page_);
            edited_.cells[edited_.length++] =
                static_cast<uint8_t>(row_ * kGridColumns + column_);
        }
    } else switch (column_) {
    case kActionPage: page_ = 1 - page_; break;
    case kActionSpace:
        if (edited_.length < edited_.cells.size()) {
            edited_.pages[edited_.length] = 0;
            edited_.cells[edited_.length++] = 0;
        }
        break;
    case kActionBackspace:
        if (edited_.length) {
            --edited_.length;
            edited_.cells[edited_.length] = 0;
            edited_.pages[edited_.length] = 0;
        }
        break;
    case kActionCancel: return KeyboardResult::Cancelled;
    case kActionAccept: return KeyboardResult::Accepted;
    }
    return KeyboardResult::Editing;
}

bool SoftKeyboard::load(SpriteRenderer& batch, std::string& error) {
    return uploadCnvSheet(batch, "data/chat/name_p1", sheets_[0], error) &&
           uploadCnvSheet(batch, "data/chat/name_p2", sheets_[1], error) &&
           uploadCnvSheet(batch, "data/network/nameMenu", actions_, error);
}

void SoftKeyboard::drawName(SpriteRenderer& batch, const PlayerName& name, float x, float y) const {
    for (size_t i = 0; i < std::min(name.length, name.cells.size()); ++i) {
        const uint8_t cell = name.cells[i];   // (row << 4) | column, see PlayerName
        batch.pushSprite(sheets_[name.pages[i] & 1],
                         {float(cell & 15) * kCellSize, float(cell >> 4) * kCellSize, kCellSize,
                          kCellSize},
                         0, 0, x + i * kNameAdvance, y);
    }
}

void SoftKeyboard::draw(SpriteRenderer& batch, float x, float y) const {
    batch.pushSprite(sheets_[page_], {0, 0, 512, 512}, 0, 0, x, y);
    batch.pushSprite(actions_, {32, 0, 320, 32}, 0, 0, x, y + 512);
    const bool actionRow = row_ == kCharacterRows;
    const float width = actionRow ? kActionCellWidth : kCellSize;
    const float cursorX = x + column_ * width;
    const float cursorY = y + row_ * kCellSize;
    const UiColor color{1, 0.85f, 0.2f, 1};
    batch.pushSolid({cursorX, cursorY, width, 2}, color);
    batch.pushSolid({cursorX, cursorY + 30, width, 2}, color);
    batch.pushSolid({cursorX, cursorY, 2, 32}, color);
    batch.pushSolid({cursorX + width - 2, cursorY, 2, 32}, color);
}
}
