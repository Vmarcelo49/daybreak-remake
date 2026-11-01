#pragma once
#include <algorithm>
#include <cctype>
#include <string>

#include "frontend/screen.h"

namespace ui {

// One line of text the menu is writing: the keyboard types into it, and a pad turns the character
// at the cursor on a wheel, since it has no other way to write. The wheel's blank is how a pad deletes.
struct TextEdit {
    std::string* text = nullptr;
    std::string original, allowed;
    size_t cursor = 0, limit = 0;

    bool active() const { return text != nullptr; }

    void begin(std::string& value, const char* letters, size_t maxLength) {
        text = &value;
        original = value;
        allowed = letters;
        limit = maxLength;
        cursor = value.size();
    }

    void apply(const TextKeys& keys) {
        for (const char c : keys.typed) {
            const char letter = (char)std::toupper((unsigned char)c);
            if (allowed.find(letter) == std::string::npos || text->size() >= limit) continue;
            text->insert(cursor++, 1, letter);
        }
        for (int i = 0; i < keys.backspaces && cursor > 0; ++i) text->erase(--cursor, 1);
        move(keys.moves);
    }

    void move(int step) { cursor = (size_t)std::clamp((int)cursor + step, 0, (int)text->size()); }

    void turn(int step) {
        if (cursor == text->size()) {
            if (text->size() < limit) text->push_back(' ');
            else --cursor;
        }
        const std::string wheel = allowed.find(' ') == std::string::npos ? " " + allowed : allowed;
        const int at = (int)wheel.find((*text)[cursor]);
        const int count = (int)wheel.size();
        (*text)[cursor] = wheel[(size_t)((at + step + count) % count)];
    }

    // The text as it would be kept: blanks are only a pad's deletions, unless the line allows spaces.
    std::string value() const {
        std::string out = *text;
        if (allowed.find(' ') == std::string::npos) out.erase(std::remove(out.begin(), out.end(), ' '), out.end());
        while (!out.empty() && out.back() == ' ') out.pop_back();
        return out;
    }

    void finish() {
        *text = value();
        text = nullptr;
    }

    void cancel() {
        *text = original;
        text = nullptr;
    }
};

}  // namespace ui
