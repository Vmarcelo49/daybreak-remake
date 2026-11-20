// Issue #99: the shipped story map and its display-time lookup, without a device or game data.
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <string>

#include "frontend/story_dialogue.h"
#include "frontend/story_script.h"
#include "ui/sheet_locale.h"
#include "ui/story_locale.h"

#define CHECK(condition) do { if (!(condition)) { \
    std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); ++g_failures; } } while (0)

static int g_failures = 0;

static std::string readShipped() {
    std::ifstream file("assets/locale/story_en.json", std::ios::binary);
    if (!file.good())
        file.open(std::filesystem::path(__FILE__).parent_path().parent_path() /
                      "assets/locale/story_en.json", std::ios::binary);
    if (!file.good()) return {};
    return {std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>()};
}

static void testParser() {
    std::map<std::string, std::string> entries;
    std::string error;
    CHECK(ui::parseStoryTranslations("{\"a#0\":\"one\",\"win/x.txt#1\":\"two\\\\nthree\"}",
                                     entries, error));
    CHECK(error.empty());
    CHECK(entries.size() == 2);
    if (entries.size() == 2) {
        CHECK(entries.at("a#0") == "one");
        // JSON \\ becomes one literal backslash: the caption walker's \n, not a real newline.
        CHECK(entries.at("win/x.txt#1") == "two\\nthree");
    }
    CHECK(ui::parseStoryTranslations("{\"k\":\"say \\\"hi\\\"\"}", entries, error));
    CHECK(entries.at("k") == "say \"hi\"");
    for (const char* bad : {"", "[]", "{", "{\"k\":1}", "{\"k\":\"v\",}",
                            "{\"k\":\"v\"} trailing", "{\"k\":\"v\",\"k\":\"w\"}",
                            "{\"k\":\"unterminated}", "{\"k\\q\":\"v\"}", "{\"k\":\"v\" \"j\"}"}) {
        error.clear();
        CHECK(!ui::parseStoryTranslations(bad, entries, error));
        CHECK(!error.empty());
        CHECK(entries.empty());
    }
}

static void testKeyBuilder() {
    CHECK(ui::storyTranslationKey("data/scenario/D01-0.txt", 0) == "D01-0.txt#0");
    CHECK(ui::storyTranslationKey("data/scenario/win/05-08-4.txt", 0) == "win/05-08-4.txt#0");
    CHECK(ui::storyTranslationKey("data/scenario/win/05-08-4.txt", 12) == "win/05-08-4.txt#12");
    CHECK(ui::storyTranslationKey("D01-0.txt", 2) == "D01-0.txt#2");
    CHECK(ui::storyTranslationKey("synthetic.txt", 7) == "synthetic.txt#7");
}

static void testShippedFile() {
    const std::string json = readShipped();
    CHECK(!json.empty());
    std::map<std::string, std::string> entries;
    std::string error;
    CHECK(ui::parseStoryTranslations(json, entries, error));
    CHECK(error.empty());
    CHECK(entries.size() == 2274);
    int dialogue = 0, win = 0;
    for (const auto& [key, value] : entries) {
        CHECK(!value.empty());
        for (unsigned char c : value) CHECK(c >= 32 && c < 127);  // no Japanese enters the repo
        const size_t hash = key.rfind('#');
        CHECK(hash != std::string::npos && hash > 0 && hash + 1 < key.size());
        for (unsigned char c : key)
            CHECK((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') ||
                  (c >= 'a' && c <= 'z') || c == '.' || c == '-' || c == '/' || c == '#');
        if (key.compare(0, 4, "win/") == 0) ++win; else ++dialogue;
    }
    CHECK(dialogue == 983);
    CHECK(win == 1291);
    CHECK(ui::setStoryTranslationLanguage("en"));
    CHECK(ui::storyTranslationCount() == 2274);
    // Every shipped key resolves to its own entry through the same lookup the screens call.
    for (const auto& [key, value] : entries) CHECK(ui::storyTranslation(key) == value);
}

static void testModeToggle() {
    std::string error;
    CHECK(ui::setSheetLanguage("ja", error));  // the existing EN/JP toggle owns both routes
    CHECK(error.empty());
    CHECK(ui::storyTranslationCount() == 0);
    CHECK(ui::storyDisplayText("data/scenario/D01-0.txt", 0, "JP line") == "JP line");
    CHECK(ui::storyDisplayText("data/scenario/win/00-00-1.txt", 0, "JP quote") == "JP quote");

    CHECK(ui::setSheetLanguage("en", error));
    CHECK(error.empty());
    CHECK(ui::storyTranslationCount() == 2274);
    CHECK(ui::storyDisplayText("data/scenario/D01-0.txt", 0, "JP line") ==
          "Oh-ho-ho-ho! I'm sorry to do this so suddenly, but I'll crush you right here!");
    CHECK(ui::storyDisplayText("data/scenario/D01-0.txt", 2, "JP line") ==
          ui::storyTranslation("D01-0.txt#2"));
    CHECK(ui::storyDisplayText("data/scenario/win/00-00-1.txt", 0, "JP quote") ==
          "\\cFFCCAAStrangely, they never counterattacked.\\nI wonder why, why?");

    CHECK(ui::setSheetLanguage("ja", error));
    CHECK(ui::storyTranslationCount() == 0);
    CHECK(ui::storyDisplayText("data/scenario/D01-0.txt", 0, "JP line") == "JP line");
    CHECK(ui::storyDisplayText("data/scenario/win/00-00-1.txt", 0, "JP quote") == "JP quote");
}

static void testMissingFallbackAndScreens() {
    CHECK(ui::setStoryTranslationLanguage("en"));
    const size_t before = ui::storyTranslationMissingCount();
    CHECK(ui::storyDisplayText("data/scenario/NO_SUCH.txt", 0, "original") == "original");
    CHECK(ui::storyDisplayText("data/scenario/NO_SUCH.txt", 0, "original") == "original");
    CHECK(ui::storyTranslationMissingCount() == before + 1);  // logged once, not once per line

    // A synthetic script whose key is absent keeps its own line, even in English mode.
    const ui::StoryDialogue missing(ui::parseStoryScript("original line\n"),
                                    "data/scenario/NO_SUCH.txt");
    CHECK(missing.line() == "original line");

    // A synthetic script that names a shipped file uses that file's text-command ordinals.
    ui::StoryDialogue present(ui::parseStoryScript("original line\nsecond line\n"),
                              "data/scenario/D01-0.txt");
    CHECK(present.line() == ui::storyTranslation("D01-0.txt#0"));
    present.update(true, false);
    present.update(false, false);
    present.update(true, false);
    CHECK(present.line() == ui::storyTranslation("D01-0.txt#1"));
}

int main() {
    testParser();
    testKeyBuilder();
    testShippedFile();
    testModeToggle();
    testMissingFallbackAndScreens();
    if (g_failures) {
        std::printf("story_translation_test: %d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("story_translation_test: ok\n");
    return 0;
}
