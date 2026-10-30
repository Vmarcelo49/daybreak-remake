// Scene 8's dialogue rules against FUN_0040eb30 and FUN_0040f4c0, without a device.
#include <cstdio>
#include <cstdint>
#include <string>
#include <vector>

#include "frontend/story_dialogue.h"
#include "frontend/story_ladder.h"

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

static void testLadder() {
    std::vector<uint8_t> bytes;
    const auto put = [&](int value) { for (int i = 0; i < 4; ++i) bytes.push_back(static_cast<uint8_t>(value >> (i * 8))); };
    put(2);
    put(0);
    for (int row = 0; row < ui::kStoryFights; ++row) {
        put(row);
        put(row + 10);
        put(row + 20);
        put(row + 30);
        put(row + 40);
    }
    for (char c : std::string("movie/e00.mpg")) bytes.push_back(static_cast<uint8_t>(c));
    bytes.push_back(0);

    uint32_t counter = 0;
    ui::StoryLadder ladder;
    CHECK(ui::parseStoryLadder(bytes, 0, [&] { return counter++; }, ladder));
    CHECK(ladder.members[0] == 2 && ladder.members[1] == 0);
    CHECK(ladder.endingMovie == "movie/e00.mpg");
    // Only rows 1..3 move.
    CHECK(ladder.fights[0].script == 40 && ladder.fights[4].script == 44 && ladder.fights[5].script == 45);
    int middle = 0;
    for (int i = 1; i <= 3; ++i) middle += ladder.fights[i].script;
    CHECK(middle == 41 + 42 + 43);
    CHECK(ladder.scriptPath() == "data/scenario/D40-0.txt");

    // Teams 1, 5 and 6 keep the file's order and draw nothing.
    counter = 0;
    CHECK(ui::parseStoryLadder(bytes, 5, [&] { return counter++; }, ladder));
    CHECK(counter == 0 && ladder.fights[1].script == 41 && ladder.fights[3].enemies[1] == 13);

    bytes.resize(20);
    CHECK(!ui::parseStoryLadder(bytes, 0, [&] { return counter++; }, ladder));

    CHECK(ui::storyEnemyWeapon(0, 0, 0, 5) == 1);   // Rena: first two only
    CHECK(ui::storyEnemyWeapon(0, 0, 4, 2) == 0);   // Rika too
    CHECK(ui::storyEnemyWeapon(0, 0, 2, 5) == 2);
    CHECK(ui::storyEnemyWeapon(7, 5, 0, 5) == 2);   // team 7's last fight
}

int main() {
    testLadder();
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
