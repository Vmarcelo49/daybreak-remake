// Scene 8's dialogue rules against FUN_0040eb30 and FUN_0040f4c0, without a device.
#include <cstdio>
#include <string>

#include "frontend/story_dialogue.h"

#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); ++g_failures; } } while (0)

using ui::StoryDialogue;
using Result = ui::StoryDialogue::Result;

static int g_failures = 0;

static StoryDialogue make(const char* script) { return StoryDialogue(ui::parseStoryScript(script)); }

static void testRows() {
    // One cell per frame, and row 1 starts at cell 32 however short row 0 is.
    const std::string line = "\xE3\x81\x82\xE3\x81\x84\\n\xE3\x81\x86";
    CHECK(ui::storyVisibleRows(line, 0).at(0).empty());
    CHECK(ui::storyVisibleRows(line, 1).at(0) == "\xE3\x81\x82");
    CHECK(ui::storyVisibleRows(line, 2).at(0) == "\xE3\x81\x82\xE3\x81\x84");
    CHECK(ui::storyVisibleRows(line, 32).at(1).empty());
    CHECK(ui::storyVisibleRows(line, 33).at(1) == "\xE3\x81\x86");
    // A colour crosses into the next row.
    const auto coloured = ui::storyVisibleRows("\\cff0000a\\nb\\ec", 40);
    CHECK(coloured.at(0) == "\\cff0000a");
    CHECK(coloured.at(1) == "\\cff0000b\\ec");
    // ASCII takes half a cell.
    CHECK(ui::storyVisibleRows("abc", 1).at(0) == "ab");
}

static void testFlow() {
    auto d = make("bg data/talk/back01.bmp\r\nbgm bgm01.ogg\r\nvoicedir v/\r\nVOICE a.wav\r\nabc\r\nVOICE b.wav\r\nde\r\n");
    CHECK(d.takeMusic() == "data/bgm/bgm01.ogg");
    CHECK(d.takeVoice() == "v/a.wav");
    CHECK(d.line() == "abc");
    CHECK(d.background().empty());
    d.update(false, false);  // the black screen is already full, so the swap is immediate
    CHECK(d.background() == "data/talk/back01.bmp");
    CHECK(d.backgroundFade() == 255);
    CHECK(d.update(false, false) == Result::Running);
    CHECK(d.backgroundFade() == 240);
    CHECK(d.revealed() == 1);

    // The first confirm finishes the line; the second moves on.
    d.update(true, false);
    CHECK(d.revealed() == 3 && d.line() == "abc");
    CHECK(!d.promptVisible());
    d.update(false, false);
    CHECK(d.promptVisible());
    d.update(true, false);
    CHECK(d.line() == "de");
    CHECK(d.takeVoice() == "v/b.wav");
    CHECK(d.revealed() == 0);

    d.update(true, false);
    CHECK(d.revealed() == 2);
    d.update(false, false);
    CHECK(d.update(true, false) == Result::ScriptEnded);
}

static void testSkip() {
    auto d = make("one\r\ntwo\r\n");
    CHECK(d.update(false, true) == Result::ScriptEnded);
}

static void testMove() {
    // Delta per frame, and input waits for the move.
    auto d = make("character c.bmp,2,1,100\r\nmove 2,-20,2\r\nmove 2,5,1\r\nline\r\n");
    CHECK(d.portraitX(2) == 100.f);
    d.update(true, false);
    CHECK(d.portraitX(2) == 80.f);
    CHECK(d.revealed() == 1);
    d.update(true, false);
    CHECK(d.portraitX(2) == 60.f);
    d.update(true, false);
    CHECK(d.portraitX(2) == 65.f);
    d.update(true, false);
    CHECK(d.revealed() == 4);
}

static void testFront() {
    auto d = make("front 1\r\nline\r\n");
    const auto& order = d.drawOrder();
    CHECK(order[0] == 0 && order[1] == 2 && order[5] == 1);
}

static void testInterlude() {
    auto d = make("line\r\n");
    d.beginInterlude();
    int frames = 0;
    Result result = Result::Running;
    while (result == Result::Running && frames < 1000) {
        result = d.update(false, false);
        ++frames;
    }
    CHECK(result == Result::InterludeEnded);
    CHECK(d.screenFade() == 255);
    CHECK(frames == 127 + 300);
    CHECK(d.takeMusicStop());
}

int main() {
    testRows();
    testFlow();
    testSkip();
    testMove();
    testFront();
    testInterlude();
    if (g_failures) {
        std::printf("story_dialogue_test: %d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("story_dialogue_test: ok\n");
    return 0;
}
