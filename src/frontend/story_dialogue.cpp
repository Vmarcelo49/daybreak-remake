#include "frontend/story_dialogue.h"

#include <algorithm>
#include <utility>

namespace ui {
namespace {

// strlen in the file's CP932 bytes: the original compares its reveal counter with this, so the
// prompt appears later than the last glyph. One byte for ASCII, two for the rest.
int cp932Length(const std::string& utf8) {
    int bytes = 0;
    for (unsigned char c : utf8) {
        if (c < 0x80) ++bytes;
        else if (c >= 0xC0) bytes += 2;
    }
    return bytes;
}

}  // namespace

std::vector<std::string> storyVisibleRows(const std::string& line, int revealed) {
    constexpr int kCellsPerRow = 32, kWrapCells = 31;
    std::vector<std::string> rows(1);
    std::string colour;
    int row = 0, halfCells = 0;
    const auto newRow = [&] {
        rows.emplace_back(colour);
        ++row;
        halfCells = 0;
    };
    for (size_t i = 0; i < line.size();) {
        if (line[i] == '\\' && i + 1 < line.size()) {
            const char code = line[i + 1];
            if (code == 'n') {
                newRow();
                i += 2;
                continue;
            }
            if (code == 'c' || code == 'e') {
                const size_t length = code == 'c' ? 8 : 2;
                colour = code == 'c' ? line.substr(i, length) : std::string();
                rows.back() += line.substr(i, length);
                i += length;
                continue;
            }
        }
        const unsigned char lead = static_cast<unsigned char>(line[i]);
        const size_t length = lead < 0x80 ? 1 : lead < 0xE0 ? 2 : lead < 0xF0 ? 3 : 4;
        const int width = lead < 0x80 ? 1 : 2;
        if ((halfCells + width) / 2 > kWrapCells) newRow();
        if (row * kCellsPerRow + halfCells / 2 >= revealed) break;
        rows.back() += line.substr(i, length);
        halfCells += width;
        i += length;
    }
    return rows;
}

void StoryDialogue::load(std::vector<StoryCommand> commands) {
    commands_ = std::move(commands);
    next_ = 0;
    // FUN_0040f970 resets moves and draw order; the portraits stay until a script replaces them.
    order_ = {0, 1, 2, 3, 4, 5};
    for (auto& queue : moves_) queue.clear();
    waiting_ = false;
    interlude_ = false;
    revealed_ = 0;
    lineBytes_ = 0;
    line_.clear();
    runUntilText();
}

bool StoryDialogue::runUntilText() {
    while (next_ < commands_.size()) {
        const StoryCommand& c = commands_[next_++];
        switch (c.type) {
        case StoryCommand::Type::Text:
            line_ = c.text;
            lineBytes_ = cp932Length(line_);
            revealed_ = 0;
            waiting_ = true;
            return false;
        case StoryCommand::Type::Background:
            pendingBackground_ = c.text;
            backgroundPending_ = true;
            break;
        case StoryCommand::Type::Bgm:
            music_ = "data/bgm/" + c.text;
            break;
        case StoryCommand::Type::Character:
            portraits_[c.slot] = c.text;
            if (c.hasX) portraitX_[c.slot] = static_cast<float>(c.x);
            break;
        case StoryCommand::Type::Voice:
            // A fade or an earlier delay holds the voice back 30 frames (case 4).
            if (screenFade_ == 0 && voiceDelay_ == 0) {
                voice_ = c.text;
            } else {
                voiceDelayed_ = c.text;
                voiceDelay_ = 30;
            }
            break;
        case StoryCommand::Type::Move:
            if (c.frames > 0) moves_[c.slot].push_back({static_cast<float>(c.delta), c.frames});
            break;
        case StoryCommand::Type::Front: {
            auto found = std::find(order_.begin(), order_.end(), c.slot);
            if (found != order_.end()) std::rotate(found, found + 1, order_.end());
            break;
        }
        case StoryCommand::Type::Sleep:
            // Case 7 blocks the whole game; no shipped script uses it.
            break;
        }
    }
    return true;
}

StoryDialogue::Result StoryDialogue::update(bool advance, bool skip) {
    if (backgroundPending_) {
        if (backgroundFade_ < 0xf1) {
            backgroundFade_ += 15;
        } else {
            background_ = pendingBackground_;
            backgroundPending_ = false;
        }
        return Result::Running;
    }
    if (interlude_) return updateInterlude(advance);

    backgroundFade_ = std::max(0, backgroundFade_ - 15);
    screenFade_ = std::max(0, screenFade_ - 5);
    if (voiceDelay_ > 0 && --voiceDelay_ == 0) voice_ = std::move(voiceDelayed_);

    moving_ = false;
    for (int slot = 0; slot < kStorySlots; ++slot) {
        auto& queue = moves_[slot];
        if (queue.empty()) continue;
        portraitX_[slot] += queue.front().delta;
        if (--queue.front().frames == 0) queue.pop_front();
        moving_ = true;
    }
    if (voiceDelay_ == 0) ++revealed_;

    if ((!waiting_ || advance) && !moving_) {
        if (revealed_ < lineBytes_) {
            revealed_ = lineBytes_;
        } else {
            waiting_ = false;
            if (runUntilText()) return Result::ScriptEnded;
        }
    }
    return skip ? Result::ScriptEnded : Result::Running;
}

void StoryDialogue::beginInterlude() {
    interlude_ = true;
    interludeFrames_ = 0;
}

StoryDialogue::Result StoryDialogue::updateInterlude(bool advance) {
    if (screenFade_ < 0xfe) {
        screenFade_ += 2;
        return Result::Running;
    }
    screenFade_ = 255;
    if (interludeFrames_ == 0) musicStop_ = true;
    ++interludeFrames_;
    return advance || interludeFrames_ == 300 ? Result::InterludeEnded : Result::Running;
}

std::string StoryDialogue::takeMusic() { return std::exchange(music_, {}); }
std::string StoryDialogue::takeVoice() { return std::exchange(voice_, {}); }
bool StoryDialogue::takeMusicStop() { return std::exchange(musicStop_, false); }

bool StoryDialogue::promptVisible() const {
    return !moving_ && !backgroundPending_ && !interlude_ && lineBytes_ < revealed_ &&
           (revealed_ - lineBytes_) % 60 < 30;
}

}  // namespace ui
