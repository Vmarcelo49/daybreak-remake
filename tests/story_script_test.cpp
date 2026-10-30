// The story script grammar (FUN_0065e500), then every shipped script against the install:
// each path a script names has to exist, or the scene would fail mid-dialogue.
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>

#include "assets/asset_source.h"
#include "assets/cnv.h"
#include "frontend/story_script.h"

#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr, "%s:%d: %s\n", __FILE__, __LINE__, #condition); ++g_failures; } } while (0)

namespace fs = std::filesystem;
using ui::StoryCommand;
using Type = ui::StoryCommand::Type;

static int g_failures = 0;

static void testGrammar() {
    const auto commands = ui::parseStoryScript(
        "#a comment\r\n"
        "characterdir data/talk/\r\n"
        "\r\n"
        "bgm bgm01.ogg\r\n"
        "BG data/talk/back01.bmp\r\n"
        "voicedir data/voice/scenario/D41/\r\n"
        "character c07-0.bmp,0,1,300\r\n"
        "character c06-1.bmp,1,0\r\n"
        "character NULL,2\r\n"
        "front 1\r\n"
        "VOICE D41-001-06.wav\r\n"
        "first\\nsecond\r\n"
        "move 2,-20,20\r\n"
        "sleep 500\r\n"
        "cut here,not here\r\n");
    CHECK(commands.size() == 11);
    if (commands.size() != 11) return;
    CHECK(commands[0].type == Type::Bgm && commands[0].text == "bgm01.ogg");
    CHECK(commands[1].type == Type::Background && commands[1].text == "data/talk/back01.bmp");
    CHECK(commands[2].type == Type::Character && commands[2].text == "data/talk/c07-0.bmp");
    CHECK(commands[2].slot == 0 && commands[2].hasX && commands[2].x == 300);
    CHECK(commands[3].slot == 1 && !commands[3].hasX);
    CHECK(commands[4].text == "data/talk/NULL" && commands[4].slot == 2);
    CHECK(commands[5].type == Type::Front && commands[5].slot == 1);
    CHECK(commands[6].type == Type::Voice && commands[6].text == "data/voice/scenario/D41/D41-001-06.wav");
    CHECK(commands[7].type == Type::Text && commands[7].text == "first\\nsecond");
    CHECK(commands[8].type == Type::Move && commands[8].slot == 2 && commands[8].delta == -20 && commands[8].frames == 20);
    CHECK(commands[9].type == Type::Sleep && commands[9].milliseconds == 500);
    CHECK(commands[10].text == "cut here");
}

// A pack image is found by the game's path, case-blind and whatever the extension asked for.
static void testTexturePack() {
    static const unsigned char kPng[] = {0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x08, 0x06, 0x00, 0x00, 0x00, 0xf4, 0x22, 0x7f, 0x8a, 0x00, 0x00, 0x00, 0x11, 0x49, 0x44, 0x41, 0x54, 0x78, 0x9c, 0x63, 0xe0, 0x12, 0x91, 0xfb, 0xaf, 0x61, 0x64, 0xf3, 0x1f, 0x00, 0x09, 0x41, 0x02, 0xd1, 0x14, 0x88, 0xff, 0x4a, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82};
    const fs::path root = fs::temp_directory_path() / "daybreak_pack_test";
    std::error_code ec;
    fs::remove_all(root, ec);
    fs::create_directories(root / "data" / "Rena", ec);
    std::ofstream(root / "data" / "Rena" / "Face.PNG", std::ios::binary).write(reinterpret_cast<const char*>(kPng), sizeof kPng);
    std::ofstream(root / "data" / "Rena" / "notes.txt") << "not an image";

    auto& assets = fnd::assets::assetSource();
    CHECK(assets.openTexturePack(root.string()) == 1);
    uint32_t w = 0, h = 0;
    std::vector<uint8_t> rgba;
    CHECK(assets.readPackImage("data/rena/face.cnv", w, h, rgba));
    CHECK(w == 2 && h == 1 && rgba.size() == 8 && rgba[4] == 40);
    CHECK(!assets.readPackImage("data/rena/other.cnv", w, h, rgba));
    CHECK(assets.openTexturePack("") == 0);
    CHECK(!assets.readPackImage("data/rena/face.cnv", w, h, rgba));
    fs::remove_all(root, ec);
}

static fs::path findInstall() {
    if (const char* env = std::getenv("GAME_DIR")) return env;
    std::error_code ec;
    for (fs::path r = fs::current_path(ec); !r.empty(); r = r.parent_path()) {
        if (fs::exists(r / "Higurashi-Daybreak" / "daybreak00.dat", ec)) return r / "Higurashi-Daybreak";
        if (r == r.parent_path()) break;
    }
    return {};
}

static std::string asCnv(std::string path) {
    const size_t dot = path.rfind('.');
    return path.substr(0, dot) + ".cnv";
}

// Exit 77 when there is no install, the convention of the asset-backed tests.
static bool testShippedScripts() {
    const fs::path install = findInstall();
    auto& assets = fnd::assets::assetSource();
    if (install.empty() || !assets.openInstall(install.string())) return false;

    int texts = 0, voices = 0, characters = 0, scripts = 0;
    for (int id = 1; id <= 60; ++id) {
        for (int part = 0; part < 2; ++part) {
            char path[64];
            std::snprintf(path, sizeof path, "data/scenario/D%02d-%d.txt", id, part);
            std::vector<uint8_t> bytes;
            CHECK(assets.read(path, bytes));
            ++scripts;
            const auto commands = ui::parseStoryScript(
                xm::sjisToUtf8(std::string(bytes.begin(), bytes.end())));
            for (const StoryCommand& c : commands) {
                bool found = true;
                switch (c.type) {
                case Type::Text:
                    ++texts;
                    // A keyword the parser does not know would land here as dialogue.
                    found = c.text[0] < 'A' || c.text[0] > 'z';
                    break;
                case Type::Voice: ++voices; found = assets.exists(asCnv(c.text)); break;
                case Type::Character:
                    ++characters;
                    found = assets.exists(asCnv(c.text)) && c.slot >= 0 && c.slot < 6;
                    break;
                case Type::Background: found = assets.exists(asCnv(c.text)); break;
                case Type::Bgm: found = assets.exists("data/bgm/" + c.text); break;
                case Type::Move:
                case Type::Front: found = c.slot >= 0 && c.slot < 6; break;
                case Type::Sleep: break;
                }
                if (!found) {
                    std::fprintf(stderr, "%s: bad command: %s\n", path, c.text.c_str());
                    ++g_failures;
                }
            }
        }
    }
    std::printf("scripts=%d texts=%d voices=%d characters=%d\n", scripts, texts, voices, characters);
    CHECK(scripts == 120);
    CHECK(texts == 983);
    CHECK(voices == 983);
    CHECK(characters == 1222);
    return true;
}

int main() {
    testGrammar();
    testTexturePack();
    const bool ranScripts = testShippedScripts();
    if (g_failures) {
        std::printf("story_script_test: %d failure(s)\n", g_failures);
        return 1;
    }
    std::printf("story_script_test: ok\n");
    return ranScripts ? 0 : 77;
}
