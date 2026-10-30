#pragma once
// frontend/story_dialogue.h — scene 8's dialogue state, without a device (FUN_0040e720 ctor,
// FUN_0040eb30 update, FUN_0040f4c0 command runner). The screen draws what this reports.
#include <array>
#include <deque>
#include <string>
#include <vector>

#include "frontend/story_script.h"

namespace ui {

inline constexpr int kStorySlots = 6;

// Which rows of a line are on screen after `revealed` frames. FUN_0040f130 draws a grid of 32
// cells per row, one cell per frame, so a short row still spends its blank cells before the
// next one starts. Each row keeps the colour escape it inherits. A full-width glyph takes one
// cell and an ASCII one half; a row wraps at 31 cells, the width of the 0x2f8 pane.
std::vector<std::string> storyVisibleRows(const std::string& line, int revealed);

class StoryDialogue {
public:
    enum class Result { Running, ScriptEnded, InterludeEnded };

    explicit StoryDialogue(std::vector<StoryCommand> commands) { load(std::move(commands)); }

    // Starts a script: the commands up to its first line of text run now (FUN_0040f970).
    void load(std::vector<StoryCommand> commands);

    // One frame. `advance` is the confirm button, `skip` the start button, which ends the
    // script at once (FUN_0040eb30:82-99).
    Result update(bool advance, bool skip);

    // The black screen between one fight's closing dialogue and the next one: the fade out,
    // then 300 frames or a confirm (FUN_0040eb30:104-130).
    void beginInterlude();

    // One-shots for the host. Empty means nothing new.
    std::string takeMusic();
    std::string takeVoice();
    bool takeMusicStop();

    const std::string& background() const { return background_; }
    const std::string& portrait(int slot) const { return portraits_[slot]; }
    float portraitX(int slot) const { return portraitX_[slot]; }
    // Back to front (FUN_0040f4c0's case 6 moves a slot to the end).
    const std::array<int, kStorySlots>& drawOrder() const { return order_; }
    const std::string& line() const { return line_; }
    int revealed() const { return revealed_; }
    // 0..255 black: under the portraits while the background changes, over everything else.
    int backgroundFade() const { return backgroundFade_; }
    int screenFade() const { return screenFade_; }
    bool promptVisible() const;

private:
    struct Move { float delta; int frames; };
    bool runUntilText();  // true when the queue is empty
    Result updateInterlude(bool advance);

    std::vector<StoryCommand> commands_;
    size_t next_ = 0;
    std::string background_, pendingBackground_;
    bool backgroundPending_ = false;
    std::array<std::string, kStorySlots> portraits_{};
    std::array<float, kStorySlots> portraitX_{};
    std::array<int, kStorySlots> order_{{0, 1, 2, 3, 4, 5}};
    std::array<std::deque<Move>, kStorySlots> moves_{};
    bool moving_ = false;
    std::string line_;
    int lineBytes_ = 0;
    int revealed_ = 0;
    bool waiting_ = false;
    int backgroundFade_ = 255;
    int screenFade_ = 0;
    int voiceDelay_ = 0;
    bool interlude_ = false;
    int interludeFrames_ = 0;
    std::string music_, voice_, voiceDelayed_;
    bool musicStop_ = false;
};

}  // namespace ui
