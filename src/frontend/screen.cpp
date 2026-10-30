// frontend/screen.cpp — the screen ids, the factory and the 25-frame fade.
// The header carries the provenance; this file is the transcription of
// FUN_00657c80 (switcher) and FUN_004020a0 (factory) as a host-side machine.
#include "frontend/screen.h"

#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <utility>

#include "frontend/screen_title.h"
#include "frontend/screen_opening.h"
#include "frontend/screen_select.h"
#include "frontend/screen_vs.h"
#include "frontend/screen_options.h"
#include "frontend/frontend_state.h"
#include "frontend/screen_story.h"
#include "frontend/screen_result.h"

namespace ui {
namespace {

// The RE'd ids of screen.h, by the lowercase name a `--screen=` argument may use. One
// table, in this translation unit: an id is its ScreenId row plus its name here.
struct ScreenName {
    const char* name;
    ScreenId    id;
};
constexpr ScreenName kScreenNames[] = {
    {"opening", ScreenId::Opening},           {"title", ScreenId::Title},
    {"select", ScreenId::Select},             {"prologue", ScreenId::Prologue},
    {"storyteam", ScreenId::StoryTeam},       {"options", ScreenId::Options},
    {"keyconfig", ScreenId::KeyConfig},       {"storyadv", ScreenId::StoryAdv},
    {"vsintro", ScreenId::VsIntro},           {"battle", ScreenId::Battle},
    {"netplay", ScreenId::NetplayMenu},       {"netplaylobby", ScreenId::NetplayLobby},
    {"netplayentry", ScreenId::NetplayEntry}, {"gameover", ScreenId::GameOver},
    {"result", ScreenId::Result},             {"staffroll", ScreenId::StaffRoll},
    {"quit", ScreenId::Quit},
};

bool equalsIgnoreCase(const char* a, const char* b) {
    for (; *a && *b; ++a, ++b)
        if (std::tolower((unsigned char)*a) != std::tolower((unsigned char)*b)) return false;
    return *a == '\0' && *b == '\0';
}

// Scene 0x00's host-owned seams: the movie's audio output, the input backend whose raw key
// state the recovered skip reads (frontend/screen_opening.h), and which file it plays. They arrive
// through setOpeningHost instead of the factory's argument list because ui::makeScreen's
// signature is deliberately the original factory's own (FUN_004020a0); the two pointers stay
// null in a test, and the entry then reports the missing host rather than building a screen
// that cannot work.
MovieAudio*          gOpeningAudio = nullptr;
fnd::input::Backend* gOpeningInput = nullptr;
std::string          gOpeningMovie = fnd::movie::kOpeningMovie;

// FUN_004020a0's switch as one table: the ids the port can construct and the
// constructor for each. Battle is hosted by the application because it owns simulation.
struct ScreenEntry {
    ScreenId id;
    std::unique_ptr<Screen> (*make)(SpriteRenderer&, FrontendState&, std::string&);
};
// Not constexpr: scene 0x00's entry reads the host seams above.
const ScreenEntry kScreens[] = {
    {ScreenId::Opening, [](SpriteRenderer& batch, FrontendState&, std::string& error) {
         if (!gOpeningInput || !gOpeningAudio) {
             error = "the opening scene needs its audio engine and input backend";
             return std::unique_ptr<Screen>{};
         }
         return makeOpeningScreen(batch, *gOpeningInput, *gOpeningAudio, gOpeningMovie,
                                  error);
     }},
    {ScreenId::Title, [](SpriteRenderer& batch, FrontendState& state, std::string& error) {
         state.story.active = false;
         return makeTitleScreen(batch,error);
     }},
    {ScreenId::Prologue, [](SpriteRenderer& batch, FrontendState&, std::string& error) {
         if (!gOpeningInput || !gOpeningAudio) {
             error = "the prologue needs its audio engine and input backend";
             return std::unique_ptr<Screen>{};
         }
         return makeOpeningScreen(batch, *gOpeningInput, *gOpeningAudio, "movie/prologue.mpg", error,
                                  ScreenId::Prologue, ScreenId::StoryTeam);
     }},
    {ScreenId::StoryTeam, &makeStoryTeamScreen},
    {ScreenId::Options, [](SpriteRenderer& batch, FrontendState&, std::string& error) { return makeOptionsScreen(batch,error); }},
    {ScreenId::KeyConfig, [](SpriteRenderer& batch, FrontendState&, std::string& error) { return makeKeyConfigScreen(batch,error); }},
    {ScreenId::Select, &makeSelectScreen},
    {ScreenId::VsIntro, [](SpriteRenderer& batch, FrontendState& state, std::string& error) {
         return makeVsScreen(batch, state, error);
     }},
    {ScreenId::Result, [](SpriteRenderer& batch, FrontendState& state, std::string& error) {
         return state.story.active ? makeStoryRetryScreen(batch, state, error)
                                   : makeResultScreen(batch, state, error);
     }},
    {ScreenId::StoryAdv, &makeStoryScreen},
    {ScreenId::GameOver, &makeGameOverScreen},
};

}  // namespace

void setOpeningHost(MovieAudio* audio, fnd::input::Backend* input, std::string movie) {
    gOpeningAudio = audio;
    gOpeningInput = input;
    if (!movie.empty()) gOpeningMovie = std::move(movie);
}

bool screenAvailable(ScreenId id) {
    // Battle presentation owns live simulation and is constructed by the application.
    if (id == ScreenId::Battle) return true;
    for (const ScreenEntry& e : kScreens)
        if (e.id == id) return true;
    return false;
}

std::unique_ptr<Screen> makeScreen(ScreenId id, SpriteRenderer& batch, FrontendState& state,
                                   std::string& error) {
    for (const ScreenEntry& e : kScreens)
        if (e.id == id) return e.make(batch, state, error);
    // Quit is the factory's own `default` (FUN_004020a0 returns null for 0x16): no
    // scene is the normal way to leave, so it is not an error. Any other id is a
    // screen the port has not built yet, which is.
    if (id != ScreenId::Quit) {
        char id_text[16];
        std::snprintf(id_text, sizeof(id_text), "0x%02x", (int)id);
        error = std::string("scene ") + id_text + " has no screen yet";
    }
    return nullptr;
}

bool parseScreenId(const char* text, ScreenId& out) {
    if (!text) return false;
    while (*text == ' ') ++text;
    // Numbers first: "1" and "0x01" are the ids as the RE writes them, and a future id
    // may have no name yet. Base 10 unless the "0x" is spelled out, so "016" is 16 and
    // not an octal surprise.
    if (*text >= '0' && *text <= '9') {
        const int base = (text[0] == '0' && (text[1] == 'x' || text[1] == 'X')) ? 16 : 10;
        char* end = nullptr;
        const long value = std::strtol(text, &end, base);
        while (end && *end == ' ') ++end;
        if (!end || *end != '\0') return false;
        out = (ScreenId)value;
        return true;
    }
    // Names, with an optional "screen"/"scene" prefix.
    for (const char* prefix : {"screen", "scene"}) {
        const size_t n = std::strlen(prefix);
        if (std::strncmp(text, prefix, n) == 0) {
            text += n;
            while (*text == ' ' || *text == ':' || *text == '=' || *text == '-') ++text;
            break;
        }
    }
    for (const ScreenName& s : kScreenNames)
        if (equalsIgnoreCase(text, s.name)) {
            out = s.id;
            return true;
        }
    return false;
}

uint8_t ScreenStack::fadeAlpha8(int frame) {
    if (frame <= 0) return 0;
    if (frame >= 0x18) return 0xff;   // FUN_00657c80.c:24-28 pins 0xff000000 from 0x18
    return (uint8_t)(frame * 10 + 5);
}

bool ScreenStack::begin(ScreenId id, Factory factory, std::string& error) {
    factory_ = std::move(factory);
    current_ = factory_ ? factory_(id) : nullptr;
    if (!current_) {
        if (error.empty()) error = "cannot start on the requested screen";
        finished_ = true;
        currentId_ = target_ = ScreenId::Quit;
        return false;
    }
    currentId_ = target_ = id;
    fade_ = 0;
    finished_ = false;
    return true;
}

ScreenId ScreenStack::update(const ScreenInput& in) {
    if (!current_) return currentId_;

    // FUN_00657ef0.c:29-34: the update runs every frame, whether or not a fade is in
    // flight, and its return value is the next id.
    const ScreenId next = current_->update(in);

    if (target_ != currentId_) {
        // Fading out: FUN_00657c80.c:32-64 increments the counter once per frame and
        // swaps at 0x19, so the old screen is alive for all 25 fade frames.
        if (++fade_ >= kFadeFrames) {
            fade_ = kFadeFrames;
            current_ = factory_ ? factory_(target_) : nullptr;   // vtable slot 2
            if (!current_) {
                // The factory's default: no scene, and the loop tears the app down
                // (FUN_00657c80.c:58 and FUN_00657ef0.c:49-53).
                finished_ = true;
                currentId_ = target_;
                return currentId_;
            }
            currentId_ = target_;
            if (instant_) fade_ = 0;
            instant_ = false;
        }
        return currentId_;
    }

    if (next != currentId_) {
        target_ = next;   // latched; see the header's second difference
        fade_ = 1;
        return currentId_;
    }
    // Fading in: FUN_00657c80.c:12-31's `param_2 == current` branch walks the counter
    // back down, which is the same 25-frame ramp in reverse.
    if (fade_ > 0) --fade_;
    return currentId_;
}

void ScreenStack::drawContent(SpriteRenderer& batch) const {
    if (current_) current_->draw(batch);
}

void ScreenStack::draw(SpriteRenderer& batch) const {
    drawContent(batch);
    if (fade_ > 0)
        batch.pushSolid(UiRect{0.f, 0.f, 800.f, 600.f},
                        UiColor{0.f, 0.f, 0.f, fadeAlpha8(fade_) / 255.f});
}

bool drawScreenFrame(const ScreenStack& stack, SpriteRenderer& batch, uint32_t w, uint32_t h,
                     WGPUCommandEncoder encoder, WGPUTextureView view, WGPUTextureFormat format,
                     std::string& error) {
    batch.beginFrame(w, h);
    // The opaque menu background: a menu frame has no scene pass under it, so the screen is
    // composited over a defined black (the same one captureUi gives a --out frame).
    batch.pushSolid({0.f, 0.f, float(w), float(h)}, {0.f, 0.f, 0.f, 1.f});
    const UiCanvasTransform canvas = fitCanvas({w, h});
    batch.setCanvasTransform(canvas.scale, canvas.x, canvas.y);
    batch.setCanvasClip({true, 0.f, 0.f, 800.f, 600.f});
    // Screen + FUN_00657c80's fade quad, both in the 800x600 canvas. The background above
    // already covers everything outside it, so a fade reads as a full-frame ramp — the
    // menu path's established pixels, unchanged.
    stack.draw(batch);
    batch.resetCanvasTransform();
    return batch.render(encoder, view, format, error);
}

bool drawScreenOverlay(const ScreenStack& stack, SpriteRenderer& batch, uint32_t w, uint32_t h,
                       WGPUCommandEncoder encoder, WGPUTextureView view, WGPUTextureFormat format,
                       std::string& error) {
    batch.beginFrame(w, h);
    const UiCanvasTransform canvas = fitCanvas({w, h});
    batch.setCanvasTransform(canvas.scale, canvas.x, canvas.y);
    stack.drawContent(batch);
    batch.resetCanvasTransform();
    // FUN_00657c80 fades the whole frame, so the ramp covers the target, not the canvas.
    if (stack.fadeFrame() > 0)
        batch.pushSolid({0.f, 0.f, float(w), float(h)},
                        UiColor{0.f, 0.f, 0.f, ScreenStack::fadeAlpha8(stack.fadeFrame()) / 255.f});
    return batch.render(encoder, view, format, error);
}

}  // namespace ui
