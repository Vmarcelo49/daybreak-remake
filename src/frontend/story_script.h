#pragma once
// frontend/story_script.h — the story dialogue scripts, data/scenario/D<id>-<part>.txt.
//
// Device-free so the grammar can be tested against every shipped script without a GPU.
// FUN_0065e500 turns a file into a command queue and FUN_0040f4c0 runs it until the next line
// of text, in file order. Keywords compare case-blind; anything else is text. A field ends at
// a comma or the end of the line, text included (FUN_0065f280). The directory directives set
// a prefix for later commands and queue nothing.
#include <string>
#include <vector>

namespace ui {

struct StoryCommand {
    enum class Type { Text, Background, Bgm, Character, Voice, Move, Front, Sleep };
    Type type = Type::Text;

    // Text: the line, with its \n, \cRRGGBB and \e escapes still in it.
    // Background, Character, Voice: the path, directory prefix included. Bgm: a name under data/bgm/.
    std::string text;
    int slot = 0;        // Character, Move, Front: 0..5
    bool hasX = false;   // Character: a zero third field keeps the slot's x
    int x = 0;           // Character
    int delta = 0;       // Move: pixels per frame, for `frames`
    int frames = 0;      // Move
    int milliseconds = 0;  // Sleep
};

// `utf8` is the whole file after sjisToUtf8.
std::vector<StoryCommand> parseStoryScript(const std::string& utf8);

}  // namespace ui
