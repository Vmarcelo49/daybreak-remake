// Foundation demo: SDL3 window + WebGPU, one code path for Linux, Windows and web.
//
// With no asset argument it draws the spinning triangle that proves the
// multi-platform plumbing. With one (`--stage`, `--character`, `--weapon`,
// `--model`) it loads the game's real assets through the asset layer and draws
// them with render/scene_renderer: depth buffer, textures, per-draw uniforms,
// camera and stage fog. `--out` renders offscreen and writes a PPM, which is how
// the renderer is verified without a display.

#define SDL_MAIN_USE_CALLBACKS 1
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "gpu/gpu.h"
#include "assets/asset_source.h"
#include "assets/stage_catalog.h"
#include "platform/platform.h"
#include "platform/surface.h"
#include "platform/web_pack.h"
#include "render/arena_camera.h"
#include "render/debug_prims.h"
#include "render/scene_renderer.h"
// After the renderer on purpose: raycast.h includes assets/xmodel.h without
// XMODEL_WEBGPU (its queries need the mesh arrays, not the GPU helpers), and xmodel.h's
// include guard means a first include without that macro would hide xm::CameraUniform
// from scene_renderer.h further down.
#include "physics/raycast.h"
#include "ui/hud.h"
#include "ui/sprite.h"
#include "ui/screen.h"
#include "ui/frontend_state.h"
#include "ui/frontend_launch.h"
#include "ui/hud_atlas.h"
#include "ui/frontend_settings.h"
#include "game/hud_bridge.h"
#include "game/fighter_pose.h"
#include "gameplay/arena_camera.h"
#include "gameplay/match.h"
#include "gameplay/bot_input.h"
#include "gameplay/hud_fill.h"
#include "audio/audio.h"
#include "audio/audio_engine.h"
#include "game/effect_events.h"
#include "game/effect_descriptor.h"
#include "game/fx_cards.h"
#include "input/input_backend.h"
#include "input/input_sdl3.h"
#include "shaders/demo_wgsl.h"

namespace {

// ---------------------------------------------------------------------------------------
// Command line
// ---------------------------------------------------------------------------------------
struct Options {
    // Asset selection. Exactly one of stage/character/weapon/model, or none for the
    // triangle demo; an effect file may ride along with any of them.
    std::string model, stage, character, weapon, effect;
    bool        hudTest = false;   // composite a synthetic HUD into --out captures
    bool        debugPrims = false; // draw the deterministic debug line overlay
    bool        audioTest = false; // run the audio backend self-check and exit
    std::string audioFile;       // with --audio-test: decode a real file too
    bool        inputTest = false; // run the input backend self-check and exit
    std::string enemyWeapon;
    std::string enemy;           // versus P2, same spec syntax as --character
    std::array<std::string, 4> battleCharacters{};
    std::array<std::string, 4> battleWeapons{};
    int battleFighterCount = 0;
    bool        versus = false;  // scripted two-fighter vignette (capture-oriented)
    bool        match = false;   // playable match: the ported simulation, not a script
    std::string script;          // P1 input script (device override, DX9 format)
    std::string script2;         // P2 input script; absent -> dummy, like the DX9
    bool        hasSpawn[2] = {false, false};   // --spawn / --spawn2 x,y,z
    glm::vec3   spawn[2] = {glm::vec3(0.f), glm::vec3(0.f)};
    std::string bgm;             // versus BGM track (.ogg; sibling .sfl looped)
    std::string sfx;             // versus hit cue (.cnv)

    // Offscreen capture. Empty `out` means "draw into the window".
    std::string out;
    int         sizeW  = 512;   // --size=N (square) or --size=WxH
    int         sizeH  = 512;   // the DX9 reference frames are 800x600, so the
                                // offscreen capture has to do non-square
    int         frames = 0;        // 0 = until the window is closed

    // Animation: --anim selects a set on every model that has it, --time seeks to a
    // position, --frames with --out advances by --dt per frame.
    int         anim = -1;
    float       time = 0.f;
    float       dt   = 1.f / 60.f;

    std::string camera = "auto";   // auto|player|front|top|bounds
    bool        headless = false;  // no window/surface: offscreen captures only
    std::string install;           // dir holding daybreakXX.dat; auto-detected when empty
    bool        noCameraClamp = false;   // A/B switch for the arena eye clamp
    bool        noTextures = false;
    bool        fog        = false;   // opt-in: the DX9 reference renders unfogged
    bool        noAnim     = false;   // bind pose: the DX9 reference binds no sets
    bool        unlit      = false;
    bool        list       = false;
    std::string screen;          // --screen=<id|name>: boot a front-end screen
};

bool hasAsset(const Options& o) {
    return !o.model.empty() || !o.stage.empty() || !o.character.empty() || !o.weapon.empty() ||
           !o.effect.empty() || !o.enemy.empty();
}

// A Windows path starts with a drive-letter colon, so a `:N` suffix is only a suffix
// when the colon is the last one and is followed by digits.
void splitSuffix(const std::string& spec, std::string& path, int& value) {
    path = spec;
    value = 0;
    const size_t colon = spec.find_last_of(':');
    if (colon == std::string::npos || colon + 1 >= spec.size() ||
        !std::isdigit((unsigned char)spec[colon + 1]))
        return;
    value = std::atoi(spec.c_str() + colon + 1);
    path = spec.substr(0, colon);
}

void usage() {
    std::fprintf(stderr,
        "usage: foundation_demo [<model.x> | --model=<file.x> | --stage=<dir> |\n"
        "                       --character=<baseDir>/<name>[:costume] |\n"
        "                       --weapon=<dir or .x>[:slot] | --effect=<file.x]] [options]\n"
        "  --out=<file.ppm>   render offscreen and write a PPM (verification path)\n"
        "  --size=N|WxH       offscreen size in pixels (default 512; WxH for a\n"
        "                     non-square frame, e.g. 800x600 to match a banked\n"
        "                     DX9 reference frame)\n"
        "  --frames=N         stop after N frames (0 = until the window closes)\n"
        "  --camera=MODE      auto|player|front|top|bounds|arena\n"
        "                     (default auto: the stage's spawn point when env.dat\n"
        "                     has one, else framed bounds)\n"
        "  --anim=N --time=S --dt=S   pose with animation set N, seek and step\n"
        "  --no-textures      draw untextured, for an A/B of texture resolution\n"
        "  --no-anim          bind no animation set: render the bind pose. The DX9\n"
        "                     reference binds none either (its d3dx9 under Wine\n"
        "                     returns no animation controller at all), so a gate frame\n"
        "                     must be bind pose to be comparable with a banked one\n"
        "  --fog              apply the stage's env.dat fog. Off by default because\n"
        "                     the DX9 reference never sets FOGENABLE: its gameplay\n"
        "                     pass writes the fog parameters (FUN_00650a30) and never\n"
        "                     enables the state, so a fogged frame cannot match a\n"
        "                     banked reference frame (worth 0.037 RMSE)\n"
        "  --unlit            skip the lambert term\n"
        "  --list             print what was loaded and exit\n"
        "  --screen=<id|name> boot a front-end screen (title, 1, 0x01, ...) instead of\n"
        "                     an asset; --script= drives its menu and --out captures it\n"
        "  --effect=<file.x>  load one card with the effect role (additive pass)\n"
        "  --hud-test         composite a synthetic HUD into --out captures\n"
        "  --debug-prims      draw a deterministic debug line overlay (play-area box,\n"
        "                     aim cross, desired-eye cross under --camera=arena)\n"
        "  --install=<dir>    use this game install's daybreakXX.dat bundles; when\n"
        "                     omitted, the install is inferred from the asset paths\n"
        "  --no-camera-clamp  A/B switch: skip the arena eye's collision_camera clamp\n"
        "  --headless         no window, no surface, no swapchain: render straight to\n"
        "                     offscreen captures (needs --out). Lets verification run\n"
        "                     where no presentable display exists, on the real GPU\n"
        "  --audio-test         run the audio backend self-check and exit\n"
        "  --audio-file=<path>  with --audio-test: decode a real file as well\n"
        "  --input-test         run the input backend self-check and exit\n"
        "  --enemy=<baseDir>/<name>[:costume]  versus P2 fighter (needs --versus)\n"
        "  --versus           scripted vignette: stage + P1 + P2, arena follow,\n"
        "                     timeline HUD, BGM loop, SFX cues; needs --stage,\n"
        "                     --character, --enemy and --frames>=30\n"
        "  --bgm=<file.ogg>   versus BGM track played through the loop player\n"
        "  --sfx=<file.cnv>    versus hit cue fired at scripted hits\n"
        "  --match            playable match: the ported fighter simulation, the real\n"
        "                     match economy and live HUD values (needs --stage,\n"
        "                     --character and --enemy, like --versus)\n"
        "  --script=<file>    P1 input script for --match (\"<frame> TOKEN...\" lines,\n"
        "                     the DX9 visual-suite format); absent -> live device\n"
        "  --script2=<file>   P2 input script; absent -> P2 takes no input (dummy,\n"
        "                     exactly what the DX9 scene does)\n"
        "  --spawn=x,y,z      P1 start position (default: the stage's env.dat point)\n"
        "  --spawn2=x,y,z     P2 start position\n"
        "With no asset argument the spinning-triangle demo runs.\n");
}

bool parseArgs(int argc, char** argv, Options& o, std::string& error) {
    for (int i = 1; i < argc; ++i) {
        const std::string a = argv[i];
        auto val = [&](const char* key) {
            return a.rfind(key, 0) == 0 ? a.substr(std::strlen(key)) : std::string();
        };
        std::string v;
        if (!(v = val("--model=")).empty()) o.model = v;
        else if (!(v = val("--stage=")).empty()) o.stage = v;
        else if (!(v = val("--character=")).empty()) o.character = v;
        else if (!(v = val("--weapon=")).empty()) o.weapon = v;
        else if (!(v = val("--effect=")).empty()) o.effect = v;
        else if (!(v = val("--out=")).empty()) o.out = v;
        else if (!(v = val("--size=")).empty()) {
            const size_t x = v.find('x');
            o.sizeW = std::atoi(v.c_str());
            o.sizeH = (x == std::string::npos) ? o.sizeW : std::atoi(v.c_str() + x + 1);
        }
        else if (!(v = val("--frames=")).empty()) o.frames = std::atoi(v.c_str());
        else if (!(v = val("--anim=")).empty()) o.anim = std::atoi(v.c_str());
        else if (!(v = val("--time=")).empty()) o.time = (float)std::atof(v.c_str());
        else if (!(v = val("--dt=")).empty()) o.dt = (float)std::atof(v.c_str());
        else if (!(v = val("--camera=")).empty()) o.camera = v;
        else if (!(v = val("--audio-file=")).empty()) o.audioFile = v;
        else if (a == "--no-textures") o.noTextures = true;
        else if (a == "--fog") o.fog = true;
        else if (a == "--no-anim") o.noAnim = true;
        else if (a == "--unlit") o.unlit = true;
        else if (a == "--list") o.list = true;
        else if (a == "--hud-test") o.hudTest = true;
        else if (a == "--debug-prims") o.debugPrims = true;
        else if (!(v = val("--install=")).empty()) o.install = v;
        else if (a == "--no-camera-clamp") o.noCameraClamp = true;
        else if (a == "--headless") o.headless = true;
        else if (a == "--audio-test") o.audioTest = true;
        else if (a == "--input-test") o.inputTest = true;
        else if (!(v = val("--enemy=")).empty()) o.enemy = v;
        else if (a == "--versus") o.versus = true;
        else if (a == "--match") o.match = true;
        else if (!(v = val("--script=")).empty()) o.script = v;
        else if (!(v = val("--script2=")).empty()) o.script2 = v;
        else if (!(v = val("--screen=")).empty()) o.screen = v;
        else if (!(v = val("--spawn=")).empty() || !(v = val("--spawn2=")).empty()) {
            // Match the KEY, not the whole argument: `a` carries the value too, so
            // `a == "--spawn2"` is never true and both flags would write slot 0.
            const int slot = (a.rfind("--spawn2=", 0) == 0) ? 1 : 0;
            if (std::sscanf(v.c_str(), "%f,%f,%f", &o.spawn[slot].x, &o.spawn[slot].y,
                            &o.spawn[slot].z) == 3)
                o.hasSpawn[slot] = true;
            else {
                error = a + " needs x,y,z";
                return false;
            }
        }
        else if (!(v = val("--bgm=")).empty()) o.bgm = v;
        else if (!(v = val("--sfx=")).empty()) o.sfx = v;
        else if (a.rfind("--", 0) == 0) {
            error = "unknown option " + a;
            return false;
        } else {
            o.model = a;   // a bare path is a single .X, as in the reference tool
        }
    }
    if (o.sizeW < 16) o.sizeW = 16;
    if (o.sizeH < 16) o.sizeH = 16;
    if (o.frames < 0) o.frames = 0;
    if (o.versus) {
        // Versus is a scripted capture vignette, not an exploration mode: it needs
        // the full cast, a timeline long enough for hits plus a KO sting, and the
        // follow camera and animation the vignette is built on.
        if (o.stage.empty() || o.character.empty() || o.enemy.empty()) {
            error = "--versus needs --stage, --character and --enemy";
            return false;
        }
        if (o.frames < 30) {
            error = "--versus needs --frames>=30 for the scripted timeline";
            return false;
        }
        if (o.camera == "auto") o.camera = "arena";
        if (o.anim < 0) o.anim = 0;
    } else if (o.match) {
        // A match is the real simulation, so it needs the same full cast as versus
        // (the reference's Scene_Gameplay loads exactly two fighters) and the arena
        // follow camera; its length is the caller's business.
        if (o.stage.empty() || o.character.empty() || o.enemy.empty()) {
            error = "--match needs --stage, --character and --enemy";
            return false;
        }
        if (o.camera == "auto") o.camera = "arena";
        if (o.anim < 0) o.anim = 0;
    } else if (!o.enemy.empty()) {
        error = "--enemy needs --versus or --match (P2 placement and rig ownership live there)";
        return false;
    }
    if ((!o.script.empty() || !o.script2.empty() || o.hasSpawn[0] || o.hasSpawn[1]) &&
        !o.match && o.screen.empty()) {
        error = "--script/--script2/--spawn/--spawn2 need --match or --screen";
        return false;
    }
    if (o.headless && o.out.empty()) {
        error = "--headless needs --out: there is no window to present to";
        return false;
    }
    if (!o.out.empty()) {
        if (!hasAsset(o) && o.screen.empty()) {
            error = "--out needs an asset argument; the triangle demo draws into the window";
            return false;
        }
        if (o.frames == 0) o.frames = 1;   // a capture with no frame count means one frame
    }
    for (const char* mode : {"auto", "player", "front", "top", "bounds", "arena"})
        if (o.camera == mode) return true;
    error = "unknown --camera=" + o.camera;
    return false;
}

// ---------------------------------------------------------------------------------------
// Scene assembly and camera (mirrors the reference tool's --stage/--character/--weapon
// handling, which is itself the shape of FUN_004011f0 / FUN_0064ab30 / FUN_00433eb0)
// ---------------------------------------------------------------------------------------
// Loads one character spec (base/name[:costume]) into the scene, returning the
// first appended model index. Shared by --character, --enemy and versus P2 so
// the three spellings cannot drift apart.
static size_t appendCharacter(xm::Scene& scene, const std::string& spec,
                             const xm::SceneOptions& sopt) {
    std::string s;
    int costume = 0;
    splitSuffix(spec, s, costume);
    const size_t slash = s.find_last_of("/\\");
    const std::string base = (slash == std::string::npos) ? "." : s.substr(0, slash);
    const std::string name = (slash == std::string::npos) ? s : s.substr(slash + 1);
    const size_t begin = scene.models.size();
    xm::Scene c = xm::loadCharacter(base, name, costume, sopt);
    if (scene.source.empty()) scene.source = c.source;
    for (auto& sm : c.models) scene.models.push_back(std::move(sm));
    return begin;
}

// First model with the character role at or after `from`; scene.models.size()
// when there is none. Weapon rig ownership and P1/P2 ranges key on this.
static size_t firstCharacter(const xm::Scene& scene, size_t from) {
    for (size_t i = from; i < scene.models.size(); ++i)
        if (scene.models[i].role == "character") return i;
    return scene.models.size();
}

xm::Scene loadScene(const Options& o, std::string& error, size_t* enemyBegin = nullptr) {
    xm::SceneOptions sopt;
    sopt.resolveTextures = !o.noTextures;
    sopt.includeCollision = true;   // framing only; never drawn

    xm::Scene scene;
    if (o.versus || o.match) {
        // Versus and match compose the same way: stage, P1 (+P1 weapon on P1's rig,
        // never models[0]), then P2 — which is what Scene_Gameplay loads
        // (scenes.cpp:469-495) and what both modes need. Validation guarantees all
        // three specs; env.dat spawn points place the fighters later.
        scene = xm::loadStage(o.stage, sopt);
        // Say what the directory *is*, not just where it is: stage21 is the schoolyard at
        // night, which is how every early comparison ended up measured on the wrong
        // variant (remake/docs/ASSET-CATALOG.md §1, docs/FULL-REPLACEMENT-PLAN.md §6a).
        std::printf("stage        : %s\n", assets::describeStage(o.stage).c_str());
        if (o.match && o.battleFighterCount > 0) {
            for (int i = 0; i < o.battleFighterCount && i < 4; ++i) {
                const size_t rig = appendCharacter(scene, o.battleCharacters[i], sopt);
                if (i == 1 && enemyBegin) *enemyBegin = rig;
                if (o.battleWeapons[i].empty()) continue;
                std::string weaponSpec;
                int weaponSlot = 0;
                splitSuffix(o.battleWeapons[i], weaponSpec, weaponSlot);
                const size_t character = firstCharacter(scene, rig);
                if (character >= scene.models.size()) throw std::runtime_error("battle fighter rig is missing");
                xm::Scene weapon = xm::loadWeapon(weaponSpec, weaponSlot, &scene.models[character].model, sopt);
                for (auto& model : weapon.models) scene.models.push_back(std::move(model));
            }
            scene.source = o.stage;
            return scene;
        }
        appendCharacter(scene, o.character, sopt);
        if (!o.weapon.empty()) {
            size_t p1 = firstCharacter(scene, 0);
            std::string wspec;
            int slot = 0;
            splitSuffix(o.weapon, wspec, slot);
            const xm::Model* rig =
                p1 < scene.models.size() ? &scene.models[p1].model : nullptr;
            xm::Scene w = xm::loadWeapon(wspec, slot, rig, sopt);
            for (auto& sm : w.models) scene.models.push_back(std::move(sm));
        }
        if (enemyBegin) *enemyBegin = scene.models.size();
        appendCharacter(scene, o.enemy, sopt);
        if (!o.enemyWeapon.empty()) {
            const size_t p2 = firstCharacter(scene, enemyBegin ? *enemyBegin : 0);
            xm::Scene weapon = xm::loadWeapon(o.enemyWeapon, 0, &scene.models[p2].model, sopt);
            for (auto& model : weapon.models) scene.models.push_back(std::move(model));
        }
        scene.source = o.stage;
    } else if (!o.stage.empty()) {
        scene = xm::loadStage(o.stage, sopt);
    } else if (!o.character.empty()) {
        appendCharacter(scene, o.character, sopt);
        // A weapon rides a bone of the character, so it can only be attached once the
        // character's rig exists.
        if (!o.weapon.empty()) {
            std::string wspec;
            int slot = 0;
            splitSuffix(o.weapon, wspec, slot);
            const xm::Model* rig = scene.models.empty() ? nullptr : &scene.models[0].model;
            xm::Scene w = xm::loadWeapon(wspec, slot, rig, sopt);
            for (xm::SceneModel& sm : w.models) scene.models.push_back(std::move(sm));
        }
    } else if (!o.weapon.empty()) {
        std::string spec;
        int slot = 0;
        splitSuffix(o.weapon, spec, slot);
        scene = xm::loadWeapon(spec, slot, nullptr, sopt);
    } else if (!o.effect.empty()) {
        xm::SceneModel sm;
        sm.model = xm::loadFile(o.effect);
        sm.source = o.effect;
        sm.role = "effect";
        const size_t slash = o.effect.find_last_of("/\\");
        sm.textures =
            xm::TextureCache(slash == std::string::npos ? std::string() : o.effect.substr(0, slash + 1));
        scene.models.push_back(std::move(sm));
        scene.source = o.effect;
    } else {
        xm::SceneModel sm;
        sm.model = xm::loadFile(o.model);
        sm.source = o.model;
        sm.role = "model";
        const size_t slash = o.model.find_last_of("/\\");
        sm.textures =
            xm::TextureCache(slash == std::string::npos ? std::string() : o.model.substr(0, slash + 1));
        scene.models.push_back(std::move(sm));
        scene.source = o.model;
    }
    if (!o.effect.empty() && !scene.models.empty() &&
        scene.models.back().source != o.effect) {
        // An effect card may ride along with any other asset, the way a weapon rides
        // a character: same file loading, but the effect role routes it to the
        // additive pass instead of the opaque one.
        xm::SceneModel sm;
        sm.model = xm::loadFile(o.effect);
        sm.source = o.effect;
        sm.role = "effect";
        const size_t slash = o.effect.find_last_of("/\\");
        sm.textures =
            xm::TextureCache(slash == std::string::npos ? std::string() : o.effect.substr(0, slash + 1));
        scene.models.push_back(std::move(sm));
    }
    if (scene.models.empty())
        error = "nothing loaded from " +
                (o.stage.empty() ? (o.character.empty() ? (o.weapon.empty() ? (o.effect.empty() ? o.model : o.effect) : o.weapon)
                                                        : o.character)
                                 : o.stage);
    return scene;
}

void listScene(const xm::Scene& scene) {
    // The byte count is printed because it is the only way to tell which copy of a
    // duplicated name was loaded: bundles and an extracted tree can differ for the same
    // path (assets/asset_source.h), and that difference decides which model renders.
    for (const xm::SceneModel& sm : scene.models)
        std::printf("  %-10s %-46s bytes=%-9zu meshes=%-3zu anims=%-4zu frames=%-4zu%s\n",
                    sm.role.c_str(), sm.source.c_str(), sm.sourceBytes, sm.model.meshes.size(),
                    sm.model.anims.size(), sm.model.frames.size(),
                    sm.attachFrame >= 0 ? " (bone-attached)" : "");
    std::printf("  %zu models, %zu meshes, %zu vertices, %zu submeshes, %zu palette matrices\n",
                scene.models.size(), scene.totalMeshes(), scene.totalVertices(),
                scene.totalSubmeshes(), scene.paletteSize());
}

// Left-handed view + projection, unmodified: WebGPU presents a Y-up NDC on every
// backend, so the negation a raw Vulkan port needs would render everything upside down.
glm::mat4 viewProj(const glm::vec3& eye, const glm::vec3& target, float aspect, float radius,
                   float sceneReach) {
    const float dist = glm::length(eye - target);
    // Near scales with the distance being framed; FAR must reach the whole scene, not
    // just the subject. A stage's sky dome sits tens of thousands of units out, so a
    // far plane sized to the framed mesh clips the entire sky to the clear colour —
    // which reads as "the skybox has no texture" rather than as a clipping bug.
    const float nearZ = std::max(0.01f, dist * 0.001f);
    const float farZ = std::max({1000.f, dist + radius * 4.f, sceneReach * 1.05f});
    return glm::perspectiveLH_ZO(glm::radians(45.f), aspect, nearZ, farZ) *
           glm::lookAtLH(eye, target, glm::vec3(0, 1, 0));
}

struct Mat4 {
    float m[16];
};

// Column-major, matching WGSL's mat4x4<f32>.
Mat4 rotationZ(float radians, float scale) {
    const float c = std::cos(radians) * scale;
    const float s = std::sin(radians) * scale;
    return Mat4{{c, s, 0.f, 0.f,
                 -s, c, 0.f, 0.f,
                 0.f, 0.f, 1.f, 0.f,
                 0.f, 0.f, 0.f, 1.f}};
}

// ---------------------------------------------------------------------------------------
// The app
// ---------------------------------------------------------------------------------------
struct App {
    Options      opts;
    SDL_Window*  window = nullptr;
    gpu::Context ctx;
    gpu::Swapchain sc;

    // Triangle demo.
    WGPURenderPipeline pipeline = nullptr;
    WGPUBindGroup      bindGroup = nullptr;
    WGPUBuffer         vertexBuffer = nullptr;
    WGPUBuffer         uniformBuffer = nullptr;
    float              spin = 0.0f;

    // Asset path.
    xm::Scene                    scene;
    std::vector<xm::Controller>  controllers;
    std::vector<std::vector<glm::mat4>> worlds;
    std::vector<glm::mat4>       modelMatrices;
    render::SceneRenderer        renderer;
    render::DebugPrims           debugPrims;
    render::DebugLineBatch       debugLines;   // rebuilt per frame, capacity kept
    render::CubeBatch            matchCubes{2048};
    render::CubeBatch            auraCubes{64};   // additive, drawn in its own pass
    glm::vec3                    debugBoundsLo{0.f}, debugBoundsHi{0.f};
    bool                         haveDebugBounds = false;
    game::physics::CameraCollision cameraCollision;   // arena eye clamp, per stage
    ui::SpriteRenderer           uiRenderer;
    ui::ScreenStack              screens;          // front end: current screen + fade
    bool                         screensMode = false;
    bool                         frontendMatch = false;
    bool                         frontendBattleReady = false;
    bool                         rendererReady = false;
    ui::FrontendState            frontend;
    fnd::audio::Sdl3Engine        menuAudio;
    fnd::audio::SfxHandle         menuSounds[4] = {-1, -1, -1, -1};
    uint64_t                     menuSoundPlays[4] = {};
    uint64_t                     menuVoicePlays = 0;
    fnd::audio::DecodedOgg        menuBgm;
    fnd::audio::LoopPlayer        menuLoop;
    fnd::input::PlayerState       botInput[4];

    ui::HudComposer              hudComposer;
    bool                         uiReady = false;
    render::Options              renderOptions;
    render::Appearance           appearance;
    glm::vec3                    eye{0.f}, target{0.f};
    float                        cameraRadius = 1.f, sceneReach = 0.f;
    glm::vec3                    arenaDesired{0.f};
    glm::vec3                    prevEye{0.f};
    bool                         havePrevEye = false;

    // Playable match (Phase 2): the ported simulation drives the fighters, the HUD
    // values and the effects, instead of the versus vignette's frame-index script.
    gameplay::Match              match;
    bool                         matchMode = false;
    uint64_t                     matchFrame = 0;      // 1-based, the DX9's frame_count+1
    int                          ringPulse = 0;
    int                          lockedFighter = 0;   // camera target; LockSwitch tap
                                                     // cycles (Guard+AttackB too, per DX9)
    gameplay::ArenaCamera        matchCamera;         // the ported reference camera
    gameplay::CameraTarget       arenaTargets[4];     // refreshed from the live fighters
    fnd::input::Backend          matchInput;          // P1 device + script override
    bool                         matchInputReady = false;
    fnd::input::PlayerState      p2State;             // P2 script state (unused when dummy)
    std::vector<fnd::input::ScriptEvent> p2Script;
    size_t                       p2ScriptPos = 0;
    uint32_t                     p2Mask = 0;
    size_t                       matchRig[4] = {0, 0, 0, 0};   // controller index per fighter
    ui::FrontendLaunch           battleLaunch;
    uint64_t                     matchShots = 0, matchSparks = 0, matchHits = 0;
    uint64_t                     matchRoundOverFrame = 0;
    game::EffectEventQueue       matchFx;
    uint64_t                     matchFxEvents = 0;
    // B1: the live effect cards the renderer draws from the event queues above.
    // `fxAssets` is the asset table the events' `asset` field indexes into
    // (game/effect_events.h); `liveFx` is this frame's card set, owned here —
    // the set itself (game::LiveFxCard) and its update rules live in
    // game/fx_cards.h, unit-tested in tests/fx_cards_test.cpp.
    struct FxAsset { int sceneIndex = -1; };
    std::vector<FxAsset> fxAssets;
    int fxAuraIndex[2] = {-1, -1};   // per-fighter aura card, match mode
    std::vector<game::LiveFxCard> liveFx;

    // Versus vignette state (only when opts.versus): P2 range, spawn bases,
    // audio streaming, effect accounting, and the current timeline HUD.
    bool                         versusMode = false;
    size_t                       enemyBegin = 0;   // first P2 model index
    size_t                       p1Rig = 0;        // first P1 character model
    glm::vec3                    p1Base{0.f}, p2Base{0.f};
    fnd::audio::Sdl3Engine        versusAudio;
    bool                         versusAudioOn = false;
    fnd::audio::DecodedOgg        versusBgm;
    fnd::audio::LoopPlayer        versusLoop;
    fnd::audio::SfxHandle         versusSfx = fnd::audio::kInvalidSfx;
    game::EffectEventQueue        versusFx;
    uint64_t                     versusSfxPlays = 0, versusFxEvents = 0;
    uint64_t                     versusBgmPushed = 0;
    ui::HudState                 versusHud;

    double   startTime = 0.0;
    double   lastTime = 0.0;
    double   deltaSum = 0.0;
    double   deltaMin = 1e30;
    double   deltaMax = 0.0;
    uint64_t frames = 0;
    // D1 render-FPS meter: frames per wall-clock second over a rolling half
    // second, exactly what the top-right counter shows (rendering only — the
    // original floats with machine speed, fixed logic ticks underneath). The
    // shown value starts at 60 and freezes there whenever a capture fixes dt,
    // so --out frames stay deterministic pixel-for-pixel.
    double   fpsWindow = 0.0;
    int      fpsFrames = 0;
    int      fpsShown = 60;

    std::string error;
};

bool buildTrianglePipeline(App& app) {
    WGPUShaderModule shader = gpu::createShaderModule(app.ctx.device, shaders::kDemoWGSL);
    if (!shader) {
        app.error = "shader module creation failed";
        return false;
    }

    WGPUVertexAttribute attrs[2] = {};
    attrs[0].format = WGPUVertexFormat_Float32x3;
    attrs[0].offset = 0;
    attrs[0].shaderLocation = 0;
    attrs[1].format = WGPUVertexFormat_Float32x3;
    attrs[1].offset = 3 * sizeof(float);
    attrs[1].shaderLocation = 1;

    WGPUVertexBufferLayout vbl = {};
    vbl.arrayStride = 6 * sizeof(float);
    vbl.stepMode = WGPUVertexStepMode_Vertex;
    vbl.attributeCount = 2;
    vbl.attributes = attrs;

    WGPUBindGroupLayoutEntry entry = {};
    entry.binding = 0;
    entry.visibility = WGPUShaderStage_Vertex;
    entry.buffer.type = WGPUBufferBindingType_Uniform;
    entry.buffer.minBindingSize = 64;

    WGPUBindGroupLayoutDescriptor bglDesc = {};
    bglDesc.entryCount = 1;
    bglDesc.entries = &entry;
    WGPUBindGroupLayout bgl = wgpuDeviceCreateBindGroupLayout(app.ctx.device, &bglDesc);

    WGPUPipelineLayoutDescriptor plDesc = {};
    plDesc.bindGroupLayoutCount = 1;
    plDesc.bindGroupLayouts = &bgl;
    WGPUPipelineLayout layout = wgpuDeviceCreatePipelineLayout(app.ctx.device, &plDesc);

    WGPUColorTargetState target = {};
    target.format = app.sc.format;
    target.writeMask = WGPUColorWriteMask_All;
    WGPUBlendState blend = {};
    blend.color.srcFactor = WGPUBlendFactor_SrcAlpha;
    blend.color.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    blend.color.operation = WGPUBlendOperation_Add;
    blend.alpha.srcFactor = WGPUBlendFactor_One;
    blend.alpha.dstFactor = WGPUBlendFactor_OneMinusSrcAlpha;
    blend.alpha.operation = WGPUBlendOperation_Add;
    target.blend = &blend;

    WGPUFragmentState fs = {};
    fs.module = shader;
    fs.entryPoint = WGPUStringView{"fs_main", WGPU_STRLEN};
    fs.targetCount = 1;
    fs.targets = &target;

    WGPURenderPipelineDescriptor rpd = {};
    rpd.layout = layout;
    rpd.vertex.module = shader;
    rpd.vertex.entryPoint = WGPUStringView{"vs_main", WGPU_STRLEN};
    rpd.vertex.bufferCount = 1;
    rpd.vertex.buffers = &vbl;
    rpd.primitive.topology = WGPUPrimitiveTopology_TriangleList;
    rpd.primitive.frontFace = WGPUFrontFace_CCW;
    rpd.primitive.cullMode = WGPUCullMode_None;
    rpd.multisample.count = 1;
    rpd.multisample.mask = 0xFFFFFFFFu;
    rpd.fragment = &fs;

    app.pipeline = wgpuDeviceCreateRenderPipeline(app.ctx.device, &rpd);

    WGPUBindGroupEntry bgEntry = {};
    bgEntry.binding = 0;
    bgEntry.buffer = app.uniformBuffer;
    bgEntry.offset = 0;
    bgEntry.size = 64;
    WGPUBindGroupDescriptor bgDesc = {};
    bgDesc.layout = bgl;
    bgDesc.entryCount = 1;
    bgDesc.entries = &bgEntry;
    app.bindGroup = wgpuDeviceCreateBindGroup(app.ctx.device, &bgDesc);

    wgpuPipelineLayoutRelease(layout);
    wgpuBindGroupLayoutRelease(bgl);
    wgpuShaderModuleRelease(shader);

    if (!app.pipeline || !app.bindGroup) {
        app.error = "pipeline creation failed";
        return false;
    }
    return true;
}

const float kVertices[] = {
    0.00f,  0.62f, 0.0f, 1.00f, 0.35f, 0.25f,
   -0.58f, -0.52f, 0.0f, 0.25f, 0.90f, 0.45f,
    0.58f, -0.52f, 0.0f, 0.30f, 0.55f, 1.00f,
};

bool initTriangle(App& app) {
    app.vertexBuffer = gpu::createBuffer(app.ctx.device, sizeof(kVertices),
                                         WGPUBufferUsage_Vertex | WGPUBufferUsage_CopyDst,
                                         kVertices);
    app.uniformBuffer = gpu::createBuffer(app.ctx.device, 64,
                                          WGPUBufferUsage_Uniform | WGPUBufferUsage_CopyDst,
                                          nullptr);
    if (!app.vertexBuffer || !app.uniformBuffer) {
        app.error = "buffer creation failed";
        return false;
    }
    return buildTrianglePipeline(app);
}

// The whole scene path: load, pose, frame, upload. Everything after this is per-frame.
// Decodes a BGM track plus its sibling .sfl loop into engine-ready state.
// Shared by versus BGM streaming; the --audio-test file path keeps its own
// inline version because its reporting differs. Loop points are file-rate
// samples, so anything but 44100 stereo is refused rather than misaligned.
// Reads go through the asset source, so an install with only its .dat bundles
// plays BGM without an extracted tree.
static bool loadBgmTrack(const std::string& oggPath, fnd::audio::Sdl3Engine& engine,
                         fnd::audio::DecodedOgg& decoded, fnd::audio::LoopPlayer& loop,
                         std::string& error) {
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(oggPath, bytes)) {
        error = "cannot open " + oggPath;
        return false;
    }
    if (!fnd::audio::decode_ogg_s16(bytes.data(), bytes.size(), decoded) || !decoded.ok ||
        decoded.srcRate != 44100 || decoded.srcChannels != 2) {
        error = "BGM decode failed or not 44100 stereo: " + oggPath;
        return false;
    }
    std::string sflPath = oggPath;
    const size_t dot = sflPath.find_last_of('.');
    if (dot == std::string::npos) {
        error = "BGM path needs an extension to find its .sfl sibling";
        return false;
    }
    sflPath.replace(dot, std::string::npos, ".sfl");
    std::vector<uint8_t> sfl;
    if (!fnd::assets::assetSource().read(sflPath, sfl)) {
        error = "missing loop sheet " + sflPath;
        return false;
    }
    const fnd::audio::SflLoop region =
        fnd::audio::parse_sfl_loop(sfl.data(), sfl.size(), 44100);
    if (!region.valid) {
        error = "unparsable loop sheet " + sflPath;
        return false;
    }
    loop.set_source(decoded.stereo44100.data(), decoded.stereo44100.size() / 2);
    loop.set_loop(region.startSample, region.endSample);
    (void)engine;
    return true;
}

// Places both fighters for one versus frame: P1 static at its spawn, P2
// strafing on an integer triangle wave (±150 units, no trig anywhere, so
// Linux and Wine agree bit for bit). Character models translate; stage models
// stay identity; weapons re-resolve against P1's live prop bone every frame,
// unlike the bind-pose snapshot the single-asset path keeps.
//
// The facing is applied here as well, not just the translation. A character
// placed with the identity rotation shows its *back*, because these rigs are
// authored facing -Z — measured in the asset itself: data/rena/00.X's eye mesh
// lies entirely at z <= +1.1 while the hair reaches z = +26.4, and both
// ankle-to-ball vectors run down -Z. Fighter::modelMatrix carries the half turn
// for a live match (via the original's own FUN_00420b30 rotation, whose angle
// is measured from +X); this scripted path bypasses that class, so it needs the
// same convention or the vignette renders both fighters back-to-front.
static void placeVersusFighters(App& app, const glm::vec3& p1, const glm::vec3& p2) {
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.role != "character") continue;
        const bool second = i >= app.enemyBegin;
        const glm::vec3& base = second ? p2 : p1;
        // The versus spawns' facings, as the reference spawns them: 0 and pi
        // (remake/src/core/scenes.cpp:535, mirrored by MatchConfig above).
        const float yaw = second ? glm::pi<float>() : 0.f;
        app.modelMatrices[i] = glm::translate(glm::mat4(1.f), base) *
                               glm::rotate(glm::mat4(1.f), yaw + glm::pi<float>(), glm::vec3(0.f, 1.f, 0.f));
    }
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.attachFrame < 0) continue;
        if (app.p1Rig >= app.worlds.size() ||
            (size_t)sm.attachFrame >= app.worlds[app.p1Rig].size()) {
            std::fprintf(stderr, "[scene] %s: attachment frame %d unusable, drawing at the origin\n",
                         sm.source.c_str(), sm.attachFrame);
            continue;
        }
        app.modelMatrices[i] =
            app.modelMatrices[app.p1Rig] * app.worlds[app.p1Rig][(size_t)sm.attachFrame];    }
    app.renderer.setModelMatrices(app.modelMatrices);
}

static fnd::audio::SfxHandle loadSoundAsset(fnd::audio::Sdl3Engine& engine, const std::string& path) {
    std::vector<uint8_t> bytes;
    if (path.empty() || !fnd::assets::assetSource().read(path, bytes)) return fnd::audio::kInvalidSfx;
    switch (fnd::audio::detect_format(bytes.data(),bytes.size())) {
        case fnd::audio::BlobFormat::Ogg: return engine.load_ogg(bytes.data(),bytes.size());
        case fnd::audio::BlobFormat::Wav: return engine.load_wav(bytes.data(),bytes.size());
        case fnd::audio::BlobFormat::CnvPcm: return engine.load_cnv(bytes.data(),bytes.size());
        default: return fnd::audio::kInvalidSfx;
    }
}

// Versus one-time setup, after load/pose/bind and before framing: ranges,
// spawn bases, audio decode, initial placement for the setScene bake.
static bool initVersus(App& app) {
    if (!app.scene.env.present) {
        app.error = "versus needs a stage with env.dat spawns";
        return false;
    }
    app.p1Rig = firstCharacter(app.scene, 0);
    if (app.p1Rig >= app.scene.models.size()) {
        app.error = "versus found no P1 character model";
        return false;
    }
    if (firstCharacter(app.scene, app.enemyBegin) >= app.scene.models.size()) {
        app.error = "versus found no P2 character model";
        return false;
    }
    app.p1Base = app.scene.env.points[0];
    app.p2Base = app.scene.env.points[1];
    if (!app.opts.bgm.empty() || !app.opts.sfx.empty()) {
        if (!app.versusAudio.open(fnd::audio::Spec{})) {
            app.error = "versus audio needs an audio device (SDL_AUDIO_DRIVER=dummy works headless)";
            return false;
        }
        app.versusAudioOn = true;
    }
    if (!app.opts.bgm.empty()) {
        if (!loadBgmTrack(app.opts.bgm, app.versusAudio, app.versusBgm, app.versusLoop,
                          app.error))
            return false;
    }
    if (!app.opts.sfx.empty()) {
        app.versusSfx = loadSoundAsset(app.versusAudio, app.opts.sfx);
        if (app.versusSfx < 0) {
            app.error = "versus SFX decode failed for " + app.opts.sfx;
            return false;
        }
    }
    app.versusMode = true;
    placeVersusFighters(app, app.p1Base, app.p2Base);
    return true;
}

// Match one-time setup (Scene_Gameplay::on_enter, scenes.cpp:465-595): bind the two
// fighters to the scene's character models, place them at the stage's spawns, and
// load the input scripts. The spawns are env.dat's points — the stage's own data and
// what the original reads — not the DX9 remake's hardcoded pair, which its comment
// claims are the env values but are not (stage21 env.dat holds (-463,200,-2200) and
// (-1363,200,-2200); the DX9 code hardcodes (1393,200,-463) and (-2200,200,-1363)).
//
// Which point, and in what order, is settled by the original's own consumer
// FUN_00423420 (0x00423420): it copies three floats verbatim from
// scene+0x44+slot*12 into the fighter's position — no axis swap, so the file's
// (a,b,c) is the vec3 (x,y,z), y=200 the height. The fighter's slot is read from
// its own +8 field, and FUN_0064ab30 creates the four fighters in slot order 0..3,
// so P1 takes points[0] and P2 points[1] (the two z=-2200 points in stage01/stage21).
// This is why the old DX9 trace A/B only matched with an explicit --spawn2: it was
// matching the deleted DX9 build's hardcoded pair, not the original's env.dat pick.
static bool initMatch(App& app) {
    if (app.frontendMatch && !app.scene.env.present) {
        app.error = "four-panel battles need all four env.dat spawn points";
        return false;
    }
    if (!app.scene.env.present && (!app.opts.hasSpawn[0] || !app.opts.hasSpawn[1])) {
        app.error = "--match needs a stage with env.dat spawns, or --spawn/--spawn2";
        return false;
    }
    std::array<size_t, 4> rigs{{app.scene.models.size(), app.scene.models.size(),
                                app.scene.models.size(), app.scene.models.size()}};
    int fighterCount = app.frontendMatch ? app.battleLaunch.fighterCount : 2;
    if (app.frontendMatch) {
        int found = 0;
        for (size_t i = 0; i < app.scene.models.size() && found < fighterCount; ++i)
            if (app.scene.models[i].role == "character") rigs[found++] = i;
        if (found != fighterCount) {
            app.error = "front end: loaded character rigs do not match the selected roster";
            return false;
        }
    } else {
        rigs[0] = firstCharacter(app.scene, 0);
        rigs[1] = firstCharacter(app.scene, app.enemyBegin);
    }
    if (fighterCount < 2 || fighterCount > 4 || rigs[0] >= app.scene.models.size() ||
        rigs[1] >= app.scene.models.size()) {
        app.error = "--match found an invalid fighter roster";
        return false;
    }

    gameplay::MatchConfig config;
    config.fighterCount = fighterCount;
    if (app.frontendMatch) {
        config.healthPercent = app.frontend.health;
        config.gaugePercent = app.frontend.gauge;
        config.timeLimit = app.frontend.timeLimit;
        config.balloonSize[0] = app.frontend.blueBalloon;
        config.balloonSize[1] = app.frontend.redBalloon;
        for (int i = 0; i < fighterCount; ++i) {
            const int panel = app.battleLaunch.fighters[i].panel;
            config.side[i] = panel < 2 ? 0 : 1;
            config.spawn[i] = app.scene.env.points[panel];
            config.facing[i] = config.side[i] == 0 ? 0.f : 3.14159f;
            config.startHP[i] = app.frontend.health;
            config.hyper[i] = (gameplay::Hypermode)app.frontend.slots[panel].hypermode;
        }
    }
    const glm::vec3 envP1 = app.scene.env.points[0];
    // FUN_00423420 indexes spawns by the selected panel; parity captures retain slots 0/1.
    const glm::vec3 envP2 = app.scene.env.points[app.frontendMatch ? ui::kFrontendBattleSlots[1] : 1];
    if (!app.frontendMatch) {
        config.spawn[0] = app.opts.hasSpawn[0] ? app.opts.spawn[0] : envP1;
        config.spawn[1] = app.opts.hasSpawn[1] ? app.opts.spawn[1] : envP2;
        config.facing[0] = 0.0f;
        config.facing[1] = 3.14159f;
    }

    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    for (int i = 0; i < fighterCount; ++i) {
        models[i] = &app.scene.models[rigs[i]].model;
        anims[i] = &app.controllers[rigs[i]];
        app.matchRig[i] = rigs[i];
    }

    // The projectile channel (fcn.004011f0's collision_tama.x): optional, and shots
    // fly to expiry when the stage ships none (the reference's open-field case).
    const xm::Model* tamaMesh = nullptr;
    static game::physics::ModelIndex tamaIndex;
    for (const xm::SceneModel& sm : app.scene.models) {
        if (sm.role == "collision" && sm.source.find("collision_tama") != std::string::npos) {
            tamaMesh = &sm.model;
            tamaIndex = game::physics::buildModelIndex(sm.model);
            break;
        }
    }
    app.match.reset(config, models, anims, tamaMesh, tamaMesh ? &tamaIndex : nullptr);
    // Bind pose on request: the DX9 reference renders no animation (its d3dx9 under
    // Wine hands back no controller), so this is what makes a gate frame comparable.
    if (app.opts.noAnim) {
        for (int i = 0; i < fighterCount; ++i) app.match.fighter(i).set_animate(false);
        std::printf("match anim   : off (bind pose)\n");
    }
    std::printf("match        : %d fighters, tama=%s\n", fighterCount, tamaMesh ? "loaded" : "missing");

    if (!app.matchInput.init()) {
        app.error = "--match needs the input backend";
        return false;
    }
    app.matchInputReady = true;

    // BGM: the reference plays data/bgm/01.ogg on entering the match (scenes.cpp:473,
    // 570-591), looped through the .sfl sheet. --bgm overrides the track; a build
    // without an audio device keeps running silently, as the DX9 side does.
    const std::string bgm = app.opts.bgm.empty() ? (app.opts.stage + "/../bgm/01.ogg")
                                                 : app.opts.bgm;
    if (app.versusAudio.open(fnd::audio::Spec{})) {
        app.versusAudioOn = true;
        if (!loadBgmTrack(bgm, app.versusAudio, app.versusBgm, app.versusLoop, app.error)) {
            std::fprintf(stderr, "[daybreak] match: BGM unavailable (%s), running silent\n",
                         app.error.c_str());
            app.error.clear();
        } else {
            std::printf("match bgm    : %s\n", bgm.c_str());
        }
    }
    if (!app.frontendMatch && !app.opts.script.empty() && !app.matchInput.load_script(app.opts.script.c_str())) {
        app.error = "cannot read input script " + app.opts.script;
        return false;
    }
    if (!app.opts.script2.empty()) {
        std::ifstream f(app.opts.script2);
        if (!f) {
            app.error = "cannot read P2 input script " + app.opts.script2;
            return false;
        }
        std::string line;
        while (std::getline(f, line)) {
            uint64_t frame = 0;
            uint32_t mask = 0;
            if (fnd::input::parse_script_line(line.c_str(), frame, mask))
                app.p2Script.push_back({frame, mask});
        }
        std::printf("[fnd::input] script2: %s (%zu events)\n", app.opts.script2.c_str(),
                    app.p2Script.size());
    }
    app.matchMode = true;
    app.lockedFighter = 0;
    app.ringPulse = 0;
    // The camera starts pristine: eye (0,0,0), converging at 10% per update exactly
    // like the reference's ArenaCamera (gameplay/arena_camera.cpp). That seed is what
    // makes the first trace line comparable — the DX9's own frame-1 eye is one 10%
    // step from the origin, not the converged position.
    app.matchCamera = gameplay::ArenaCamera{};
    std::vector<gameplay::CameraTarget*> cameraPool;
    for (int i = 0; i < app.match.config().fighterCount; ++i) cameraPool.push_back(&app.arenaTargets[i]);
    app.matchCamera.set_target_pool(cameraPool);
    app.matchCamera.set_active_target(app.lockedFighter);
    return true;
}

// Places the two fighters' models from the live simulation. modelMatrix() is the
// reference's world matrix (translation + Y rotation, FUN_00420b30). A bone-attached
// weapon is a separate model, so its world transform is the rig's model matrix
// composed with the bone's model-space matrix — the same composition the versus path
// needs, which it got wrong (it used the bone matrix alone, so a weapon would have
// been placed at the origin instead of in the fighter's hand).
static void placeMatchFighters(App& app) {
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        for (int fighter = 0; fighter < app.match.config().fighterCount; ++fighter)
            if (i == app.matchRig[fighter]) {
                app.modelMatrices[i] = app.match.fighter(fighter).modelMatrix();
                break;
            }
    }
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.attachFrame < 0) continue;
        size_t rig = app.matchRig[0];
        for (int fighter = 1; fighter < app.match.config().fighterCount; ++fighter)
            if (app.matchRig[fighter] < i && app.matchRig[fighter] > rig) rig = app.matchRig[fighter];
        if (rig >= app.worlds.size() || (size_t)sm.attachFrame >= app.worlds[rig].size()) {
            std::fprintf(stderr, "[scene] %s: attachment frame %d unusable, drawing at the origin\n",
                         sm.source.c_str(), sm.attachFrame);
            continue;
        }
        app.modelMatrices[i] = app.modelMatrices[rig] * app.worlds[rig][(size_t)sm.attachFrame];
    }
    app.renderer.setModelMatrices(app.modelMatrices);
}

// The effect asset table the gameplay events index into (game/effect_events.h:
// `asset` is a table index, never a path). Slot 0 is the melee-hit card, resolved
// through the effect manager's descriptor (FUN_0042eec0: version plus a
// fixed 260-byte model path); the auras are
// FUN_00633ca0's data/aura/%02d.x table, slot 0 — the slot-to-fighter rule is
// not yet connected to the original state flags, so both fighters share the same card. A missing file is not fatal:
// the asset keeps sceneIndex -1 and the debug cubes stay the visible representation.

static int addFxCard(App& app, const std::string& path) {
    const int index = (int)app.scene.models.size();
    xm::SceneModel sm;
    try {
        // Bundle-first through the same seam the scene loader uses (scene.h).
        std::vector<uint8_t> bytes;
        if (!fnd::assets::assetSource().read(path, bytes))
            throw std::runtime_error("cannot read " + path);
        sm.model = xm::loadMemory(bytes.data(), bytes.size());
        sm.sourceBytes = bytes.size();
    } catch (const std::exception& e) {
        std::fprintf(stderr, "[fx] %s: %s\n", path.c_str(), e.what());
        return -1;
    }
    sm.source = path;
    sm.role = "effect";   // the additive, billboarded pass (scene_renderer)
    // The effect cards' textures ship split across two directories (measured: the
    // hitC*/muzzle/aura .cnv files sit in data/aura/ while the hitb*/g* set sits in
    // data/effect/), so the cache falls back from the card's own directory to aura/.
    const std::string dir = path.substr(0, path.find_last_of("/\\") + 1);
    const std::string auraDir = dir + "../aura/";
    sm.textures = xm::TextureCache(dir, [auraDir](const std::string& p,
                                                  std::vector<uint8_t>& out) {
        if (fnd::assets::assetSource().read(p, out)) return true;
        const size_t slash = p.find_last_of("/\\");
        const std::string name = slash == std::string::npos ? p : p.substr(slash + 1);
        return fnd::assets::assetSource().read(auraDir + name, out);
    });
    app.scene.models.push_back(std::move(sm));
    app.modelMatrices.push_back(glm::mat4(0.f));   // hidden until a card goes live
    return index;
}

static void buildFxAssets(App& app) {
    const std::string dataDir = app.opts.stage + "/..";
    std::vector<uint8_t> dat;
    const std::string hitName =
        fnd::assets::assetSource().read(dataDir + "/effect/000.dat", dat) ? game::effectModelPath(dat)
                                                                          : std::string();
    app.fxAssets.push_back(App::FxAsset{addFxCard(app, dataDir + "/effect/" + hitName)});
    if (app.opts.match) {
        const int a0 = addFxCard(app, dataDir + "/aura/00.X");
        const int a1 = addFxCard(app, dataDir + "/aura/00.X");
        app.fxAssets.push_back(App::FxAsset{a0});
        app.fxAssets.push_back(App::FxAsset{a1});
        app.fxAuraIndex[0] = a0;
        app.fxAuraIndex[1] = a1;
    }
    std::printf("fx assets    : %zu card(s) in the effect table\n", app.fxAssets.size());
}

// Drains the gameplay's event queue into the live card set. The spawn /
// kill-by-id / ttl-expiry rules live in game/fx_cards.h (unit-tested there);
// this only moves the drained events over and counts them.
static void updateFxCards(App& app, game::EffectEventQueue& q, uint64_t& events, float dt) {
    const std::vector<game::EffectEvent> ev = q.drain();
    events += ev.size();
    game::updateLiveFxCards(app.liveFx, ev, dt);
}

// Per-frame placement of the live cards: every asset model is hidden with a zero
// matrix, then the live ones get theirs. The cards are unskinned and the Effect
// pass billboards them at render time (scene_renderer), so only the model matrix
// moves each frame; setModelMatrices uploads it at the end of the placement call
// that follows.
static void placeFxCards(App& app) {
    for (const App::FxAsset& a : app.fxAssets)
        if (a.sceneIndex >= 0) app.modelMatrices[(size_t)a.sceneIndex] = glm::mat4(0.f);
    if (app.opts.debugPrims) return;   // the cube A/B view draws no cards
    for (const game::LiveFxCard& c : app.liveFx) {
        if (c.asset < 0 || (size_t)c.asset >= app.fxAssets.size()) continue;
        const int mi = app.fxAssets[(size_t)c.asset].sceneIndex;
        if (mi < 0) continue;
        app.modelMatrices[(size_t)mi] = glm::translate(glm::mat4(1.f), c.position);
    }
    // The aura is fighter state, not an event: it follows the fighter's own model
    // matrix in the fighter's local space — the data path the aura cube used.
    for (int i = 0; i < 2; ++i) {
        if (app.fxAuraIndex[i] < 0) continue;
        const gameplay::Fighter& f = app.match.fighter(i);
        if (!f.aura_active()) continue;
        app.modelMatrices[(size_t)app.fxAuraIndex[i]] =
            f.modelMatrix() * glm::translate(glm::mat4(1.f), f.aura_center_local());
    }
}

// One match frame: the reference's order lives in gameplay::Match::step; this adds
// what the scene added around it — input polling, the camera's target switch, the
// HUD values, the effect events and the debug cubes.
static void tickMatch(App& app, double dt) {
    if (app.ringPulse > 0) --app.ringPulse;
    ++app.matchFrame;   // 1-based, matching the DX9's frame_count + 1

    // P2: a script drives it when given; otherwise it takes no input, which is
    // exactly what the DX9 scene passes (scenes.cpp:680).
    const fnd::input::PlayerState* p2 = nullptr;
    if (!app.p2Script.empty()) {
        while (app.p2ScriptPos < app.p2Script.size() &&
               app.p2Script[app.p2ScriptPos].frame <= app.matchFrame) {
            app.p2Mask = app.p2Script[app.p2ScriptPos].mask;
            ++app.p2ScriptPos;
        }
        for (int a = 0; a < fnd::input::ActionCount; ++a)
            app.p2State.down[a] = (app.p2Mask & (1u << a)) != 0;
        fnd::input::compute_edges(app.p2State);
        p2 = &app.p2State;
    }

    const fnd::input::PlayerState* p1 = nullptr;
    if (app.matchInputReady && !app.frontendMatch) {
        app.matchInput.tick_script(app.matchFrame);
        app.matchInput.poll();
        p1 = &app.matchInput.player(0);
    }

    const fnd::input::PlayerState* inputs[4] = {p1, p2, nullptr, nullptr};
    if (app.frontendMatch) {
        app.matchInput.tick_script(app.frames);
        app.matchInput.poll();
        for (int i = 0; i < app.match.config().fighterCount; ++i) {
            const int panel = app.battleLaunch.fighters[i].panel;
            const int controller = app.frontend.slots[panel].controller;
            if (controller >= 0 && controller < 4) inputs[i] = &app.matchInput.player(controller);
            else {
                int target = -1;
                float nearest = 1.0e30f;
                for (int j = 0; j < app.match.config().fighterCount; ++j) {
                    if (app.match.config().side[i] == app.match.config().side[j] ||
                        !app.match.fighter(j).is_alive()) continue;
                    const glm::vec3 d = app.match.fighter(j).position() - app.match.fighter(i).position();
                    const float distance = d.x*d.x + d.z*d.z;
                    if (distance < nearest) { nearest = distance; target = j; }
                }
                if (target >= 0)
                    gameplay::updateBotInput(app.botInput[i], app.match.fighter(i),
                                             app.match.fighter(target), app.matchFrame);
                inputs[i] = &app.botInput[i];
            }
        }
        p1 = inputs[0];
    }
    const gameplay::MatchFrame f = app.match.step(inputs, dt);
    if (app.versusAudioOn)
        app.versusBgmPushed += app.versusLoop.push_next(app.versusAudio, 1024);
    app.matchShots += (uint64_t)f.shotsSpawned;
    app.matchSparks += (uint64_t)f.muzzleSparks;
    for (int i = 0; i < app.match.config().fighterCount; ++i)
        if (f.meleeHit[i]) ++app.matchHits;

    // Combat effects: a card at the victim for each connected hit, retired by the
    // next one — the versus vignette's FIFO discipline, driven by real combat.
    // INFERRED lifetime (12 s): the original's per-effect factors are un-RE'd
    // (ROADMAP-PENDING.md B1 sketch b); full-bright, no fade. Kill-chaining
    // retires every card but the last on the next hit; the final one lingers.
    for (int i = 0; i < app.match.config().fighterCount; ++i) {
        if (!f.meleeHit[i] || f.meleeVictim[i] < 0) continue;
        const glm::vec3 at = app.match.fighter(f.meleeVictim[i]).position() + glm::vec3(0.f, 100.f, 0.f);
        app.matchFx.pushSpawn((uint32_t)app.matchHits, at, 0, 12.f);
        if (app.matchHits > 1) app.matchFx.pushKill((uint32_t)(app.matchHits - 1));
    }
    // The cards must be placed before placeMatchFighters uploads the model
    // matrices (it ends with setModelMatrices), so they land this frame.
    updateFxCards(app, app.matchFx, app.matchFxEvents, (float)dt);
    placeFxCards(app);
    placeMatchFighters(app);

    // Camera: the ported reference camera (gameplay/arena_camera.{h,cpp}), fed the
    // live fighters. The target switch is the reference's (Guard just_pressed while
    // AttackB is held, scenes.cpp:644-646) and the pool does the dead-skip itself.
    // LockSwitch tap is the original's own reticle switch (input.h: tap = cycle
    // enemy): no character swap exists — the "tag" voice cluster (tagfront/
    // tagback/tagOK beside tactics/thank) is partner callouts, and the only
    // switch mechanic in the original is the target cycle (FUN_00421e30). In
    // this 1v1 port that is camera-only (shots fly the facing, which tracks
    // the single enemy); hold-for-ally needs allies first.
    for (int i = 0; i < app.match.config().fighterCount; ++i) {
        const gameplay::Fighter& f = app.match.fighter(i);
        app.arenaTargets[i].position = f.position();
        app.arenaTargets[i].facingYaw = f.facing_yaw();
        app.arenaTargets[i].alive = f.is_alive();
    }
    if (p1 && (p1->just_pressed[fnd::input::LockSwitch] ||
               (p1->just_pressed[fnd::input::Guard] && p1->down[fnd::input::AttackB]))) {
        app.matchCamera.cycle_target(true);
        // FUN_00421e30/FUN_004201a0: a 15-tick lock pulse, not a persistent angle.
        app.ringPulse = 15;
    }
    // No collision query: the DX9 match scene updates its camera with a null collision
    // frame (scenes.cpp:729). The foundation's clamp stays one argument away —
    // update(dt, {&app.cameraCollision}) — and is the original-fidelity path, not the
    // parity one. The blend is per call by design (the reference ignores dt).
    app.matchCamera.update(dt);
    app.eye = app.matchCamera.eye();
    app.target = app.matchCamera.target();
    app.lockedFighter = app.matchCamera.active_target_index() < 0
                            ? app.lockedFighter
                            : app.matchCamera.active_target_index();

    // HUD: the ported value computation, fed from the live fighter (side 0, which is
    // the only side the DX9 layout draws outside the two balloon corners).
    const gameplay::Fighter& f1 = app.match.fighter(0);
    gameplay::HudFillInput hf;
    hf.p1.hp = f1.hp() * 100 / f1.max_hp();
    hf.p1.alive = f1.is_alive();
    hf.p1.mainWhole = f1.main_whole();
    hf.p1.mainFrac = f1.main_frac();
    hf.p1.reloadOk = f1.reload_ok();
    hf.p1.chargeWhole = f1.charge_whole();
    hf.p1.chargeFrac = f1.charge_frac();
    hf.p1.shootHeld = p1 && p1->down[fnd::input::Shoot];
    hf.p1.chargeHoldFrac = f1.charge_hold_frac();
    switch (f1.charge_tier()) {   // ShotTier -> HoldTier (scenes.cpp:847-851)
        case gameplay::ShotTier::Red:    hf.p1.chargeTier = game::HoldTier::Red; break;
        case gameplay::ShotTier::Yellow: hf.p1.chargeTier = game::HoldTier::Yellow; break;
        default:                         hf.p1.chargeTier = game::HoldTier::Idle; break;
    }
    const gameplay::HypermodeParams hp = gameplay::hypermode_params(f1.hypermode());
    hf.p1.hyperName = hp.name;
    hf.p1.hyperGauge = f1.hyper_gauge();
    hf.p1.hyperActive = f1.hyper_active();
    hf.p1.hyperReady = f1.hyper_ready();
    hf.p1.hyperSecondsLeft = f1.hyper_seconds_left();
    hf.p1.hyperAura = game::GameRgb{(float)gameplay::rgbR(hp.aura) / 255.f,
                                    (float)gameplay::rgbG(hp.aura) / 255.f,
                                    (float)gameplay::rgbB(hp.aura) / 255.f};
    hf.p1.stamina = f1.stamina();
    // The reference's contextual gate is the state, not airborne() (scenes.cpp:879-882).
    hf.p1.staminaVisible = f1.state() == gameplay::FighterState::Run ||
                           f1.state() == gameplay::FighterState::Guard ||
                           f1.state() == gameplay::FighterState::Jump;
    app.versusHud = gameplay::hudStateFor(app.match.economy(), hf);
    // D1: the render-FPS counter rides the HUD state (60 while capturing).
    app.versusHud.fps = app.fpsShown;
    // The composer is clock-free by design, so the frame counter the original's
    // alternations and pulse read (FUN_00644150's `(frame % 0x1e) / 0xf` flash pair and the
    // balloon popup's growth) is carried in the state instead of read from a clock.
    app.versusHud.hudFrame = (int)app.matchFrame;
    // The boxed tactics readout (P03's 128x64 cells: 0 適当, 1 格闘, 2 射撃, 3 集中,
    // 4 各個, 5 後退). Cell 0 is 適当, which is what the original's own screen shows; the
    // tactic system itself is not ported yet, so the default stance is the honest value
    // rather than a guess at a state the simulation does not have.
    app.versusHud.commandCell = 0;

    // Per-fighter appearance state; projection is resolved with the render viewport below.
    {
        for (int i = 0; i < 2; ++i) {
            int fighterIndex = i;
            if (app.frontendMatch) {
                const int panel = ui::kFrontendBattleSlots[i];
                for (int j = 0; j < app.battleLaunch.fighterCount; ++j)
                    if (app.battleLaunch.fighters[j].panel == panel) fighterIndex = j;
            }
            const gameplay::Fighter& f = app.match.fighter(fighterIndex);
            // The ring and the com bar mark the fighter you are *not* following: the
            // original's own screen battle-hud.webp has the camera behind the player with
            // the red ring and the `com` tag on the opponent ahead of her. The camera's
            // locked target is the one being followed, so this is the inverse of it.
            app.versusHud.fighters[i].target = (fighterIndex != app.lockedFighter);
            app.versusHud.fighters[i].ringPulse = app.ringPulse;
            // Slot 0 is 1P and slot 4 is com in the tag atlas (P01 (320,256,64,32) rows);
            // the red copies sit four rows down, which is the tagSheet index.
            app.versusHud.fighters[i].slot = app.frontendMatch
                ? app.frontend.slots[ui::kFrontendBattleSlots[i]].controller : (i == 0 ? 0 : 4);
            app.versusHud.fighters[i].tagSheet = (i == 0) ? 0 : 1;
            app.versusHud.fighters[i].hp = (float)f.hp() / f.max_hp();
            app.versusHud.fighters[i].hpLag = app.versusHud.fighters[i].hp;
            app.versusHud.fighters[i].alertDir = -1;
        }
    }

    if (f.roundOver) {
        app.matchRoundOverFrame = app.matchFrame;
        std::printf("[daybreak] match: round over on side %d at frame %llu\n",
                    f.roundOverSide, (unsigned long long)app.matchFrame);
    }
}

// The trace the DX9 build prints under DAYBREAK_CAMINFO, reproduced field for field
// so `tests/compare_match_traces.py` can diff the two implementations. The probe
// fires on render calls 1, 61, 121, ... (scenes.cpp:802-805: `probe++ % 60 == 0`).
static void traceMatch(App& app) {
    if (!std::getenv("DAYBREAK_CAMINFO")) return;
    if ((app.matchFrame - 1) % 60 != 0) return;
    const gameplay::Fighter& a = app.match.fighter(0);
    const gameplay::Fighter& b = app.match.fighter(1);
    std::printf("[daybreak] cam eye=(%.0f,%.0f,%.0f) p1=(%.0f,%.0f,%.0f,%s) "
                "p2=(%.0f,%.0f,%.0f,%s)\n",
                app.eye.x, app.eye.y, app.eye.z, a.position().x, a.position().y, a.position().z,
                gameplay::state_to_anim_name(a.state()), b.position().x, b.position().y,
                b.position().z, gameplay::state_to_anim_name(b.state()));
    // The set that actually plays, next to the state it came from, and whether it was the
    // fallback. `state_to_anim_name` stays the compared field: the DX9 side of the trace
    // binds no animation sets at all, so it has no set to print and changing that field
    // would destroy the only cross-implementation oracle this project has. The fallback
    // flag is what keeps an unmapped state (Guard, Jump, TagOut) visible instead of silent.
    std::printf("[daybreak] anim p1=set %d %s%s p2=set %d %s%s\n",
                a.anim_set_index(), a.anim_set_name(), a.anim_fallback() ? " (fallback)" : "",
                b.anim_set_index(), b.anim_set_name(), b.anim_fallback() ? " (fallback)" : "");
}

// The DX9 side drew every shot, hit spark and hypermode aura as an unlit cube
// (remake/src/render/debug_prim.cpp — a cube pass, not a line pass). The foundation
// draws the same cubes from the port's own per-cube data: Projectile::kCubeSize/color
// and Spark::size/color feed the opaque batch. The cubes stay the shots' and sparks'
// representation — their real VFX are trails, which are RE-blocked (EFFECTS-TRAILS.md)
// — while the aura now draws its actual card by default; its cube only appears under
// --debug-prims, which is the A/B against the old all-cube view. Rebuilt, never appended.
static void fillMatchCubes(App& app) {
    app.matchCubes.clear();
    app.auraCubes.clear();
    for (const gameplay::Projectile& p : app.match.shots().shots()) {
        if (!p.alive) continue;
        app.matchCubes.add(p.pos, gameplay::Projectile::kCubeSize, p.color());
    }
    for (const gameplay::Spark& s : app.match.shots().sparks()) {
        if (!s.alive) continue;
        app.matchCubes.add(s.pos, s.size() * 0.5f, s.color());
    }
    if (!app.opts.debugPrims) return;   // the real aura card is the default view
    // The aura cube: the reference render's second, additive cube pass, drawn in the
    // fighter's own space: its local centre through the fighter's model matrix.
    for (int i = 0; i < 2; ++i) {
        const gameplay::Fighter& f = app.match.fighter(i);
        if (!f.aura_active()) continue;
        const glm::vec3 at = glm::vec3(f.modelMatrix() * glm::vec4(f.aura_center_local(), 1.f));
        app.auraCubes.add(at, f.aura_radius(), f.aura_color());
    }
}


// Timeline HUD for one versus frame: scripted hits at 30/55/80% drain P1 to
// 10, the last 3 frames are the KO sting, hyper fills to READY near the end.
// Pure function of the frame index — the determinism the captures rely on.
static game::GameHudValues timelineHud(uint64_t frame, uint64_t frames) {
    const uint64_t h1 = (3 * frames) / 10, h2 = (55 * frames) / 100, h3 = (8 * frames) / 10;
    game::GameHudValues v;
    v.balloon[0] = 87.f;
    v.balloon[1] = 42.f;
    v.limit = 100.f;
    v.mainWhole = 5;
    v.mainFrac = (double)(frame % 30) / 30.0;
    v.reloading = ((frame / 30) % 2 == 0);
    v.chargeWhole = 2;
    v.chargeFrac = (double)(frame % 40) / 40.0;
    v.holdVisible = true;
    v.holdFrac = 0.5f;
    v.holdTier = game::HoldTier::Yellow;
    float hp = 100.f;
    if (frame >= h1) hp -= 30.f;
    if (frame >= h2) hp -= 30.f;
    if (frame >= h3) hp -= 30.f;
    v.hp = hp;
    v.hyperName = "OYASHIRO";
    v.hyperGauge = (float)((double)frame / (double)(frames - 5));
    if (v.hyperGauge > 1.f) v.hyperGauge = 1.f;
    v.hyperReady = frame >= frames - 5;
    v.hyperAura = game::GameRgb{1.f, 1.f, 1.f};
    v.staminaVisible = true;
    v.staminaFrac = (float)(((frame * 7) % 60) / 60.0);
    v.koVisible = (frame > frames - 3);
    if (v.koVisible) v.hp = 0.f;
    return v;
}

// One versus frame: strafe, placements, follow camera, timeline HUD, audio
// chunk, scripted SFX, effect events. Everything nondeterministic-input-free:
// positions, HUD, audio counts and events are pure functions of the frame.
static void tickVersus(App& app, uint64_t frame) {
    const uint64_t N = (uint64_t)app.opts.frames;
    const int64_t H = ((int64_t)N + 1) / 2;
    const int64_t ph = ((int64_t)frame - 1) % H;
    double tri = (double)ph / (double)H;
    if ((((int64_t)frame - 1) / H) % 2 == 1) tri = 1.0 - tri;
    const glm::vec3 p1 = app.p1Base;
    const glm::vec3 p2 = app.p2Base + glm::vec3((float)(300.0 * (tri - 0.5)), 0.f, 0.f);

    game::FighterPose pose;
    pose.position = (p1 + p2) * 0.5f;
    pose.facingYaw = 0.f;
    const render::ArenaFrame af = render::arenaViewProj(
        game::arenaTargetFrom(pose), render::ArenaCameraParams{}, 16.f / 9.f);
    app.target = af.aim;
    app.arenaDesired = af.eye;

    app.versusHud = game::makeHudState(timelineHud(frame, N));
    app.versusHud.hudFrame = (int)frame;
    app.versusHud.fps = app.fpsShown;   // D1: same render-FPS counter as match

    if (app.versusAudioOn)
        app.versusBgmPushed += app.versusLoop.push_next(app.versusAudio, 1024);
    // Scripted hits live here, not in the audio block: effect events must flow
    // whether or not --bgm/--sfx configured an audio device.
    const uint64_t h1 = (3 * N) / 10, h2 = (55 * N) / 100, h3 = (8 * N) / 10;
    static const int kHitChannels[3] = {16, 17, 18};
    int hit = -1;
    if (frame == h1) hit = 0;
    else if (frame == h2) hit = 1;
    else if (frame == h3) hit = 2;
    if (hit >= 0) {
        if (app.versusAudioOn && app.versusSfx >= 0) {
            fnd::audio::PlayRequest req;
            req.channel = kHitChannels[hit];
            if (app.versusAudio.play(app.versusSfx, fnd::audio::SfxBus::Sfx, req) >= 0)
                ++app.versusSfxPlays;
        }
        // Spawn now, retire the previous hit's card: lifetimes are scripted,
        // not simulated — what matters here is FIFO order and exact counts.
        // INFERRED lifetime (5 s): the original's per-effect factors are
        // un-RE'd (ROADMAP-PENDING.md B1 sketch b); full-bright, no fade.
        app.versusFx.pushSpawn((uint32_t)(hit + 1), (p1 + p2) * 0.5f, 0, 5.f);
        if (hit > 0) app.versusFx.pushKill((uint32_t)hit);
    }
    if (frame == N) app.versusFx.pushKill(3);
    // The scripted timeline has no clock: cards age at the capture's fixed step
    // (1/60), keeping a versus run a pure function of the frame index.
    updateFxCards(app, app.versusFx, app.versusFxEvents, 1.f / 60.f);
    placeFxCards(app);
    placeVersusFighters(app, p1, p2);
}

bool initScene(App& app) {
    // Install discovery: the .dat bundles are the game's own source of truth, and where
    // they exist they win over an extracted tree (asset_source.h explains why the two
    // differ). The install is inferred from whichever asset path the command line
    // already carries, so existing capture command lines keep working verbatim;
    // --install= overrides when a path points somewhere unexpected.
    if (!app.opts.install.empty()) {
        fnd::assets::assetSource().openInstall(app.opts.install);
    } else {
        for (const std::string* p : {&app.opts.stage, &app.opts.character, &app.opts.enemy,
                                     &app.opts.weapon, &app.opts.model, &app.opts.effect}) {
            if (p->empty()) continue;
            const std::string dir = fnd::assets::AssetSource::findInstallDir(*p);
            if (!dir.empty()) {
                fnd::assets::assetSource().openInstall(dir);
                break;
            }
        }
    }
    const fnd::assets::AssetSource& src = fnd::assets::assetSource();
    if (src.bundlesOpen()) {
        std::printf("assets       : %zu/%zu .dat bundle(s) from %s\n",
                    src.bundles().bundles().size(), fnd::assets::DatBundleSet::kBundleCount,
                    src.installDir().c_str());
    } else {
        std::printf("assets       : filesystem only (no daybreakXX.dat install found)\n");
    }

    try {
        app.scene = loadScene(app.opts, app.error, &app.enemyBegin);
    } catch (const std::exception& e) {
        app.error = std::string("load failed: ") + e.what();
        return false;
    }
    if (app.scene.models.empty()) return false;

    if (app.opts.list) {
        listScene(app.scene);
        return true;
    }
    xm::resolveSceneTextures(app.scene);

    // The arena camera clamp's geometry: the one model with the camera collision role.
    // Stages without it (and the two whose file parses to zero triangles) keep the
    // documented degradation — no clamp, smoothing only (game/camera_collision.h:33-35).
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        if (app.scene.models[i].role == "collision_camera") {
            app.cameraCollision.setMesh(&app.scene.models[i].model);
            std::printf("camera clamp : %s, %s\n", app.scene.models[i].source.c_str(),
                        app.cameraCollision.empty() ? "empty mesh, no clamp"
                                                    : "camera collision mesh loaded");
            break;
        }
    }

    // ---- pose: bind pose, or one animation set driven through the Controller
    app.controllers.resize(app.scene.models.size());
    app.worlds.resize(app.scene.models.size());
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        xm::Model& m = app.scene.models[i].model;
        if (app.opts.anim >= 0 && (size_t)app.opts.anim < m.anims.size()) {
            app.controllers[i].bind(&m);
            app.controllers[i].setAnimation(app.opts.anim, true);
            app.controllers[i].setTrackPosition(0, (double)app.opts.time);
            app.controllers[i].evalWorld(app.worlds[i]);
        } else {
            m.evalPose(nullptr, 0.f, false, app.worlds[i]);
        }
    }
    // A weapon is placed by the owning character's attachment bone: the original hangs
    // them off Bip01_Prop1/Prop2 and draws nothing else for them (FUN_00433eb0).
    app.modelMatrices.assign(app.scene.models.size(), glm::mat4(1.f));
    int rigIndex = -1;
    for (size_t i = 0; i < app.scene.models.size(); ++i)
        if (app.scene.models[i].role == "character") { rigIndex = (int)i; break; }
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.attachFrame < 0) continue;
        if (rigIndex < 0 || (size_t)sm.attachFrame >= app.worlds[(size_t)rigIndex].size()) {
            std::fprintf(stderr, "[scene] %s: attachment frame %d unusable, drawing at the origin\n",
                         sm.source.c_str(), sm.attachFrame);
            continue;
        }
        app.modelMatrices[i] = app.worlds[(size_t)rigIndex][(size_t)sm.attachFrame];
    }

    if (app.opts.versus) {
        if (!initVersus(app)) return false;
    } else if (app.opts.match) {
        if (!initMatch(app)) return false;
    }
    // B1: the effect asset table (hit card, plus the fighters' aura cards in match
    // mode), pushed as extra scene models before the renderer bakes the draw list.
    if (app.opts.match || app.opts.versus)
        buildFxAssets(app);

    // ---- framing. A stage's visible set includes an inverted sky dome far larger than
    // the play area, and env.dat's fog ends around 10000 units, so a bounds-fit camera
    // ends up outside the fog looking at a flat wall of fog colour. env.dat carries the
    // spawn points, which is the play area by construction — those are the sane frame
    // for a stage, and the collision meshes are the fallback for one without env.dat.
    glm::vec3 lo(1e30f), hi(-1e30f);
    if (!app.scene.bounds(lo, hi, /*playArea=*/true) &&
        !app.scene.bounds(lo, hi, /*playArea=*/false)) {
        lo = glm::vec3(-1.f);
        hi = glm::vec3(1.f);
    }
    const glm::vec3 center = (lo + hi) * 0.5f;
    float radius = glm::length(hi - lo) * 0.5f;
    if (!(radius > 0.f)) radius = 1.f;
    app.target = center;
    app.cameraRadius = radius;

    // Reach from the eye to the farthest scene corner, so the far plane always covers
    // every sub-model including the backdrop dome.
    glm::vec3 slo(1e30f), shi(-1e30f);
    app.scene.bounds(slo, shi, /*playArea=*/false);

    // The debug overlay's box: the play area when the stage declares one, because the
    // full bounds include the sky dome and would frame the whole world. Kept here so
    // the overlay is a pure function of loaded state, never of the clock.
    glm::vec3 plo(1e30f), phi(-1e30f);
    if (app.scene.bounds(plo, phi, /*playArea=*/true)) {
        app.debugBoundsLo = plo;
        app.debugBoundsHi = phi;
        app.haveDebugBounds = true;
    } else if (slo.x <= shi.x) {
        app.debugBoundsLo = slo;
        app.debugBoundsHi = shi;
        app.haveDebugBounds = true;
    }

    const bool haveSpawn = app.scene.env.present;
    const glm::vec3 spawnEye = haveSpawn ? app.scene.env.points[0] : glm::vec3(0.f);
    const std::string mode = app.opts.camera;
    const float camDist = radius * 2.0f;
    if (mode == "player" && haveSpawn) {
        app.eye = spawnEye + glm::vec3(0.f, 320.f, 0.f);   // eye height above the spawn
    } else if (mode == "player") {
        std::fprintf(stderr, "[scene] --camera=player needs env.dat; framing bounds instead\n");
        app.eye = center + glm::vec3(0.62f, 0.34f, -0.71f) * camDist;
    } else if (mode == "front") {
        app.eye = center + glm::vec3(0.f, 0.f, -1.f) * camDist;
    } else if (mode == "top") {
        app.eye = center + glm::vec3(0.02f, 1.f, -0.16f) * camDist;
    } else if (mode == "bounds") {
        app.eye = center + glm::vec3(0.9f, 0.45f, -1.15f) * camDist;
    } else if (mode == "arena" && haveSpawn) {
        // The game camera, not a framing convenience: the env.dat spawn stands in
        // for the locked-on fighter, converted through the game pose interface the
        // way gameplay code will. The desired eye is one-shot (no spring, no
        // collision clamp — both game-side per the reference); per-frame smoothing
        // happens in SDL_AppIterate.
        game::FighterPose pose;
        pose.position = spawnEye;
        pose.facingYaw = 0.f;
        const render::ArenaFrame af = render::arenaViewProj(
            game::arenaTargetFrom(pose), render::ArenaCameraParams{}, 16.f / 9.f);
        app.eye = af.eye;
        app.target = af.aim;
        app.arenaDesired = af.eye;
    } else if (mode == "arena") {
        std::fprintf(stderr, "[scene] --camera=arena needs env.dat; framing bounds instead\n");
        app.eye = center + glm::vec3(0.62f, 0.34f, -0.71f) * camDist;
    } else if (haveSpawn) {
        // auto: a stage frames from its spawn point, everything else from its bounds.
        app.eye = spawnEye + glm::vec3(0.f, 320.f, 0.f);
    } else {
        app.eye = center + glm::vec3(0.62f, 0.34f, -0.71f) * camDist;
    }
    for (int c = 0; c < 8; ++c) {
        const glm::vec3 corner((c & 1) ? shi.x : slo.x, (c & 2) ? shi.y : slo.y,
                               (c & 4) ? shi.z : slo.z);
        app.sceneReach = std::max(app.sceneReach, glm::length(corner - app.eye));
    }

    app.renderOptions.textures = !app.opts.noTextures;
    app.appearance.fog = app.opts.fog;
    app.appearance.unlit = app.opts.unlit;

    if (!app.rendererReady && !app.renderer.init(app.ctx, app.error)) return false;
    app.rendererReady = true;
    if (!app.renderer.setScene(app.scene, app.worlds, app.modelMatrices, app.renderOptions,
                               app.error))
        return false;
    app.renderer.setFog(app.scene.env);
    app.renderer.setAppearance(app.appearance);

    // The HUD test rig: same renderer, same swapchain format, one deterministic
    // synthetic HUD composited into --out captures. Font upload is fatal here (a
    // capture without labels would silently prove less); in a game it is not.
    // A match always wants it: the HUD values are live game state, not a test rig.
    if (app.opts.hudTest || app.matchMode || app.versusMode) {
        if (!app.uiReady && !app.uiRenderer.init(app.ctx.device, app.ctx.queue, app.error)) return false;
        if (!app.hudComposer.uploadFont(app.uiRenderer, app.error)) return false;
        app.uiReady = true;
    }

    // The match draws its shots and sparks as cubes (the DX9 stand-in), so the debug
    // pass is initialized whenever a match runs, not only under --debug-prims.
    if ((app.opts.debugPrims || app.matchMode) && !app.debugPrims.init(app.ctx, app.error))
        return false;

    const render::Stats& st = app.renderer.stats();
    std::printf("scene %s: %zu model(s), %zu meshes, %zu vertices, %zu palette matrices\n",
                app.scene.source.c_str(), app.scene.models.size(), app.scene.totalMeshes(),
                app.scene.totalVertices(), st.paletteMatrices);
    std::printf("bounds [%.0f %.0f %.0f] .. [%.0f %.0f %.0f]  radius %.0f\n", lo.x, lo.y, lo.z,
                hi.x, hi.y, hi.z, radius);
    std::printf("camera %s at [%.0f %.0f %.0f] looking at [%.0f %.0f %.0f] (distance %.0f)\n",
                mode.c_str(), app.eye.x, app.eye.y, app.eye.z, app.target.x, app.target.y,
                app.target.z, glm::length(app.eye - app.target));
    std::printf("far plane reach %.0f units (sky dome included)\n", app.sceneReach);
    if (app.scene.env.present)
        std::printf("fog from env.dat: %.0f..%.0f rgb(%.2f %.2f %.2f)%s\n", app.scene.env.fogStart,
                    app.scene.env.fogEnd, app.scene.env.fogColor.r, app.scene.env.fogColor.g,
                    app.scene.env.fogColor.b, app.scene.env.fogEnabled ? "" : " (disabled)");
    std::printf("draws: %zu (%d textured, %d untextured, %d decals, %d effects), %zu GPU textures\n", st.draws,
                st.textured, st.untextured, st.decals, st.effects, st.textures);
    return true;
}

// ---------------------------------------------------------------------------------------
// Offscreen capture: coverage and luminance over a frame, plus a PPM of it. The "not
// background" test is the renderer's own clear colour, so coverage counts pixels the
// scene actually reached.
// ---------------------------------------------------------------------------------------
void writePpm(const std::string& path, const std::vector<uint8_t>& rgba, int w, int h) {
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) {
        std::fprintf(stderr, "cannot write %s\n", path.c_str());
        return;
    }
    std::fprintf(f, "P6\n%d %d\n255\n", w, h);
    for (int i = 0; i < w * h; ++i) std::fwrite(rgba.data() + i * 4, 1, 3, f);
    std::fclose(f);
    std::printf("wrote %s\n", path.c_str());
}

void reportCoverage(const std::vector<uint8_t>& rgba, int w, int h) {
    int covered = 0;
    float minLum = 1.f, maxLum = 0.f;
    for (int i = 0; i < w * h; ++i) {
        const uint8_t* p = rgba.data() + i * 4;
        if (p[0] < 20 && p[1] < 22 && p[2] < 26) continue;   // clear colour
        const float lum = (0.2126f * p[0] + 0.7152f * p[1] + 0.0722f * p[2]) / 255.f;
        ++covered;
        minLum = std::min(minLum, lum);
        maxLum = std::max(maxLum, lum);
    }
    std::printf("coverage: %d px of %d (%.2f%%)  luminance %.3f..%.3f\n", covered, w * h,
                100.0 * covered / (double)(w * h), minLum, maxLum);
}

void report(App& app) {
    const double elapsed = plat::now() - app.startTime;
    const double avg = app.frames ? app.deltaSum / (double)app.frames : 0.0;
    std::printf("\n-- frame timing (variable delta, no fixed step) --\n");
    std::printf("frames      : %llu in %.3f s\n", (unsigned long long)app.frames, elapsed);
    if (app.frames > 1) {
        std::printf("delta avg   : %.3f ms (%.1f fps)\n", avg * 1000.0, avg > 0 ? 1.0 / avg : 0.0);
        std::printf("delta min   : %.3f ms\n", app.deltaMin * 1000.0);
        std::printf("delta max   : %.3f ms\n", app.deltaMax * 1000.0);
    } else {
        // The first delta is deliberately excluded (it contains setup time), so a
        // one-frame run — which is what a capture is — has no delta to report.
        std::printf("delta       : not sampled (a single frame has no delta)\n");
    }
    std::printf("RESULT: %s\n", app.error.empty() ? "ok" : app.error.c_str());
}

void teardown(App& app) {
    app.menuAudio.close();
    if (app.versusAudioOn) app.versusAudio.close();
    if (app.uiReady) app.uiRenderer.shutdown();
    app.debugPrims.shutdown();
    app.renderer.shutdown();
    if (app.bindGroup) wgpuBindGroupRelease(app.bindGroup);
    if (app.pipeline) wgpuRenderPipelineRelease(app.pipeline);
    if (app.vertexBuffer) wgpuBufferRelease(app.vertexBuffer);
    if (app.uniformBuffer) wgpuBufferRelease(app.uniformBuffer);
    if (app.sc.surface) wgpuSurfaceRelease(app.sc.surface);
    gpu::destroyContext(app.ctx);
    if (app.window) SDL_DestroyWindow(app.window);
    plat::shutdown();   // SDL_Quit; headless initialized SDL too, just without video
}

// Re-poses from the controllers after advancing the clock. The pose is a pure
// function of elapsed time, so the frame delta may be whatever the display gives us.
//
// In a match the two fighter controllers are skipped: the ported Fighter advances its
// own animation inside update() (fighter.cpp:219), exactly as the DX9 model did, and
// advancing them here as well would run the fighters' animation at double speed.
void advanceAnimation(App& app, double delta) {
    bool moved = false;
    for (size_t i = 0; i < app.controllers.size(); ++i) {
        xm::Controller& c = app.controllers[i];
        if (!c.model()) continue;
        bool matchRig = false;
        if (app.matchMode)
            for (int fighter = 0; fighter < app.match.config().fighterCount; ++fighter)
                matchRig = matchRig || i == app.matchRig[fighter];
        if (matchRig) continue;
        c.advanceTime((float)delta);
        moved = true;
    }
    // A match still needs the pose refreshed: the fighters moved their own tracks.
    if (app.matchMode) moved = true;
    if (!moved) return;
    for (size_t i = 0; i < app.controllers.size(); ++i)
        if (app.controllers[i].model()) app.controllers[i].evalWorld(app.worlds[i]);
    app.renderer.updatePose(app.worlds);
}

// ---------------------------------------------------------------------------------------
// Backend self-checks: --audio-test and --input-test exercise the media/input
// backends in-engine (same binaries, same SDL) without needing game data.
// ---------------------------------------------------------------------------------------
bool runAudioTest(App& app) {
    // A 440 Hz sine, one second, mix-ready stereo: synthesized so the check needs
    // no copyrighted bytes and stays deterministic across targets.
    fnd::audio::Sdl3Engine engine(nullptr);   // null gate: native always ready
    fnd::audio::Spec spec;
    if (!engine.open(spec)) {
        app.error = "audio device open failed";
        return false;
    }
    std::vector<int16_t> tone(44100 * 2);
    for (size_t i = 0; i < 44100; ++i) {
        const float v = std::sin(2.f * 3.14159265f * 440.f * (float)i / 44100.f);
        const int16_t q = (int16_t)(v * 32767.f);
        tone[i * 2] = q;
        tone[i * 2 + 1] = q;
    }
    const size_t pushed = engine.push_music_s16(tone.data(), tone.size() / 2);
    fnd::audio::SfxHandle h = engine.load_pcm_s16(tone.data(), tone.size() / 2);
    const int ch = engine.play(h, fnd::audio::SfxBus::Sfx);
    fnd::audio::Volumes vols;
    vols.music = 50;
    vols.sfx = 25;
    engine.set_volumes(vols);
    std::printf("audio-test: device open, music pushed %zu/44100 frames, sfx handle %d on channel %d\n",
                pushed, (int)h, ch);
    std::printf("audio-test: music queued %zu frames, music gain %.2f, sfx gain %.2f\n",
                engine.music_queued_frames(), engine.music_gain(),
                engine.bus_gain_applied(fnd::audio::SfxBus::Sfx));
    if (!app.opts.audioFile.empty()) {
        // A real shipped file through the same bank: format-detected, decoded,
        // and fired once. Local data only, never committed.
        std::ifstream f(app.opts.audioFile, std::ios::binary);
        if (!f) {
            app.error = "cannot open " + app.opts.audioFile;
            return false;
        }
        const std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(f)),
                                         std::istreambuf_iterator<char>());
        fnd::audio::SfxHandle fh = fnd::audio::kInvalidSfx;
        const char* kind = "unknown";
        switch (fnd::audio::detect_format(bytes.data(), bytes.size())) {
            case fnd::audio::BlobFormat::Ogg:
                fh = engine.load_ogg(bytes.data(), bytes.size());
                kind = "ogg";
                break;
            case fnd::audio::BlobFormat::Wav:
                fh = engine.load_wav(bytes.data(), bytes.size());
                kind = "wav";
                break;
            case fnd::audio::BlobFormat::CnvPcm:
                fh = engine.load_cnv(bytes.data(), bytes.size());
                kind = "cnv";
                break;
            default: break;
        }
        if (fh < 0) {
            app.error = "decode failed for " + app.opts.audioFile;
            return false;
        }
        const int fch = engine.play(fh, fnd::audio::SfxBus::Sfx);
        std::printf("audio-test: file %s (%s, %zu bytes) decoded, handle %d on channel %d\n",
                    app.opts.audioFile.c_str(), kind, bytes.size(), (int)fh, fch);
        if (fch < 0) {
            app.error = "file playback failed";
            return false;
        }
        // A sibling .sfl file carries the BGM loop region. When one parses,
        // stream the track through it twice in engine-sized chunks: this is the
        // production streaming path (decode once, push looped chunks), verified
        // by exact frame accounting rather than by listening.
        if (std::string(kind) == "ogg") {
            std::string sflPath = app.opts.audioFile;
            const size_t dot = sflPath.find_last_of('.');
            if (dot != std::string::npos) {
                sflPath.replace(dot, std::string::npos, ".sfl");
                std::ifstream sf(sflPath, std::ios::binary);
                if (sf) {
                    const std::vector<uint8_t> sfl((std::istreambuf_iterator<char>(sf)),
                                                   std::istreambuf_iterator<char>());
                    fnd::audio::DecodedOgg decoded;
                    if (fnd::audio::decode_ogg_s16(bytes.data(), bytes.size(), decoded) &&
                        decoded.ok && decoded.srcRate == 44100 && decoded.srcChannels == 2) {
                        const fnd::audio::SflLoop loop =
                            fnd::audio::parse_sfl_loop(sfl.data(), sfl.size(), 44100);
                        if (loop.valid) {
                            fnd::audio::LoopPlayer player;
                            player.set_source(decoded.stereo44100.data(),
                                              decoded.stereo44100.size() / 2);
                            player.set_loop(loop.startSample, loop.endSample);
                            size_t streamed = 0;
                            // Two full loops, bounded: a runaway wrap would show
                            // up here as iterations past the budget, not a hang.
                            const size_t budget =
                                (2 * (loop.endSample - loop.startSample) + loop.endSample) /
                                    4096 +
                                8;
                            for (size_t i = 0; i < budget && player.loops_completed() < 2;
                                 ++i)
                                streamed += player.push_next(engine, 4096);
                            // Two wraps land at end + (end - start): the opening
                            // [0, end) pass plus one full [start, end) loop.
                            const size_t expect =
                                2 * (size_t)loop.endSample - loop.startSample;
                            // The call containing the second wrap keeps pushing
                            // into the third pass up to its chunk budget, so the
                            // total overshoots by less than one chunk: wraps are
                            // the exact signal, totals are bounded each side.
                            std::printf("audio-test: loop %u..%u streamed %zu frames, %llu wraps\n",
                                        loop.startSample, loop.endSample, streamed,
                                        (unsigned long long)player.loops_completed());
                            if (player.loops_completed() != 2 || streamed < expect ||
                                streamed >= expect + 4096 ||
                                player.position() < loop.startSample ||
                                player.position() >= loop.endSample) {
                                app.error = "loop streaming mismatch";
                                return false;
                            }
                        } else {
                            std::printf("audio-test: .sfl present but unparsable, loop test skipped\n");
                        }
                    }
                }
            }
        }
    }
    engine.close();
    return pushed == 44100 && h >= 0 && ch >= 0;
}

bool runInputTest(App& app) {
    fnd::input::Backend backend;
    if (!backend.init()) {
        app.error = "input backend init failed";
        return false;
    }
    // Canned tap on P1 melee (X): down at frame 2, up at frame 4. No hardware
    // input exists headless, so the event-held set carries the whole test.
    bool ok = true;
    for (uint64_t frame = 1; frame <= 6; ++frame) {
        if (frame == 2) backend.note_key(fnd::input::sdl3::kScMelee, true);
        if (frame == 4) backend.note_key(fnd::input::sdl3::kScMelee, false);
        backend.poll();
        const fnd::input::PlayerState& p0 = backend.player(0);
        const bool held = p0.down[fnd::input::AttackA];
        const bool jp = p0.just_pressed[fnd::input::AttackA];
        const bool jr = p0.just_released[fnd::input::AttackA];
        const int timer = p0.press_timer[fnd::input::AttackA];
        std::printf("input-test: frame %llu held=%d just_pressed=%d just_released=%d timer=%d\n",
                    (unsigned long long)frame, (int)held, (int)jp, (int)jr, timer);
        if (jp != (frame == 2) || jr != (frame == 4) || held != (frame >= 2 && frame < 4))
            ok = false;
    }
    backend.shutdown();
    if (!ok) app.error = "input edge sequence mismatch";
    return ok;
}

// Round-start art comes from FUN_00633ca0; the three-second 1v1 clock is
// a port flow rule, independent of the original's unlocated trigger sequence.
class RoundStartScreen final : public ui::Screen {
public:
    RoundStartScreen(ui::SpriteRenderer& batch, bool& ready, std::string& error) : ready_(ready) {
        ui::uploadCnvSheet(batch, "data/object/P09", sheet_, error);
    }
    bool loaded() const { return sheet_ >= 0; }
    ui::ScreenId update(const ui::ScreenInput&) override {
        if (++frame_ >= 180) ready_ = true;
        return ui::ScreenId::Battle;
    }
    const char* name() const override { return "countdown"; }
    void draw(ui::SpriteRenderer& batch) const override {
        batch.pushSolid({0,0,800,600},{0,0,0,1});
        const int n = std::min(2, frame_ / 60);
        const float w = n == 2 ? 128.f : 192.f;
        batch.pushSprite(sheet_, {n*192.f,0,w,256},w/2,128,400,300,.5f);
    }
private:
    bool& ready_;
    int frame_ = 0, sheet_ = -1;
};

static void playFrontendMusic(App& app, ui::ScreenId id) {
    if (!app.menuAudio.is_open()) return;
    const int localSide = app.frontend.slots[0].controller < 4 ? 0 : 1;
    const char* path = id == ui::ScreenId::Title ? "data/bgm/title.ogg" :
        id == ui::ScreenId::Select ? "data/bgm/select01.ogg" :
        id == ui::ScreenId::VsIntro ? "data/bgm/vs.ogg" :
        id == ui::ScreenId::Result && app.frontend.resultWinner >= 0 ?
            (app.frontend.resultWinner == localSide ? "data/bgm/win.ogg" : "data/bgm/lose.ogg") : nullptr;
    app.menuAudio.clear_music();
    app.menuLoop = fnd::audio::LoopPlayer{};
    if (!path) return;
    std::string failure;
    if (!loadBgmTrack(path, app.menuAudio, app.menuBgm, app.menuLoop, failure))
        std::fprintf(stderr, "[menu] %s\n", failure.c_str());
}

static bool enterFrontendBattle(App& app) {
    // Direct --screen=vsintro/battle gets a usable two-fighter default.
    for (int i = 0; i < 2; ++i) if (app.frontend.slots[ui::kFrontendBattleSlots[i]].character < 0) {
        app.frontend.slots[ui::kFrontendBattleSlots[i]].character = i;
        app.frontend.slots[ui::kFrontendBattleSlots[i]].controller = i == 0 ? 0 : 4;
    }
    ui::FrontendLaunch launch;
    if (!ui::frontendLaunch(app.frontend, launch, app.error, (uint32_t)app.frames)) return false;
    app.battleLaunch = launch;
    app.frontendMatch = true;
    app.frontendBattleReady = false;
    app.frontend.resultStats = {};
    app.opts.stage = launch.stage;
    app.opts.character = launch.character;
    app.opts.enemy = launch.enemy;
    app.opts.weapon = launch.weapon;
    app.opts.enemyWeapon = launch.enemyWeapon;
    app.opts.battleFighterCount = launch.fighterCount;
    for (int i = 0; i < launch.fighterCount; ++i) {
        app.opts.battleCharacters[i] = launch.fighters[i].character;
        app.opts.battleWeapons[i] = launch.fighters[i].weapon;
    }
    app.opts.match = true;
    app.opts.camera = "arena";
    app.matchFrame = app.matchRoundOverFrame = 0;
    for (auto& input : app.botInput) input = {};
    app.matchHits = app.matchShots = app.matchSparks = 0;
    app.liveFx.clear(); app.fxAssets.clear();
    app.matchFx.drain();
    if (!initScene(app)) return false;
    app.versusAudio.set_volumes(ui::frontendSettings().volumes);
    app.matchMode = false;
    std::printf("[menu] battle: %d fighters on %s\n", launch.fighterCount, launch.stage.c_str());
    return true;
}

// --screen: the front end's entry point. The stack is built with the app's own
// makeScreen factory, so an id the port has not implemented is the factory's `default`
// — no scene, no fake transition (ui/screen.h) — and the input backend is the same one
// --match uses, so a script drives the menu through the vocabulary the DX9 suite speaks.
bool initScreens(App& app) {
    ui::ScreenId id = ui::ScreenId::Quit;
    if (!ui::parseScreenId(app.opts.screen.c_str(), id)) {
        app.error = "unknown --screen=" + app.opts.screen;
        return false;
    }
    // No asset path on this command line to infer the install from: --install= is the
    // hint, and assetSource() falls back to the filesystem (running from the install
    // dir works).
    if (!app.opts.install.empty()) fnd::assets::assetSource().openInstall(app.opts.install);
    // No scene is ever submitted on this path, but the capture readback lives in
    // SceneRenderer (device/queue/instance plus the mapped-buffer copy), so a --out menu
    // frame needs it initialized even though render() is never called.
    if (!app.rendererReady && !app.renderer.init(app.ctx, app.error)) return false;
    app.rendererReady = true;
    if (!app.uiReady && !app.uiRenderer.init(app.ctx.device, app.ctx.queue, app.error)) return false;
    app.uiReady = true;
    auto factory = [&app](ui::ScreenId sid) -> std::unique_ptr<ui::Screen> {
        playFrontendMusic(app, sid);
        if (sid == ui::ScreenId::Battle) {
            if (!enterFrontendBattle(app)) return nullptr;
            auto countdown = std::make_unique<RoundStartScreen>(app.uiRenderer, app.frontendBattleReady, app.error);
            if (!countdown->loaded()) return nullptr;
            return countdown;
        }
        auto screen = ui::makeScreen(sid, app.uiRenderer, app.frontend, app.error);
        if (screen) std::printf("[menu] scene: %s\n", screen->name());
        return screen;
    };
    if (!app.screens.begin(id, factory, app.error)) return false;
    if (!app.matchInput.init()) {
        app.error = "--screen needs the input backend";
        return false;
    }
    app.matchInputReady = true;
    if (!app.opts.script.empty() && !app.matchInput.load_script(app.opts.script.c_str())) {
        app.error = "cannot read input script " + app.opts.script;
        return false;
    }
    auto& settings = ui::frontendSettings();
    settings.applyVolumes = [&app](const fnd::audio::Volumes& v) {
        app.menuAudio.set_volumes(v);
        app.versusAudio.set_volumes(v);
    };
    settings.resolutionAvailable = false;
    settings.resolutions = {{0, 0}};
    settings.resolutionIndex = 0;
#if !defined(__EMSCRIPTEN__)
    if (app.window) {
        const SDL_DisplayID display = SDL_GetDisplayForWindow(app.window);
        if (const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(display))
            settings.displayResolution = {mode->w, mode->h};
        int width = 0, height = 0;
        SDL_GetWindowSizeInPixels(app.window, &width, &height);
        settings.currentResolution = {width, height};
        constexpr ui::DisplayResolution common[] = {
            {800,600},{960,540},{1024,768},{1280,720},{1280,960},{1600,900},
            {1920,1080},{1920,1200},{2560,1080},{2560,1440},{3440,1440},{3840,2160}
        };
        auto addResolution = [&settings](ui::DisplayResolution size) {
            if (size.width > 0 && size.height > 0 &&
                std::find(settings.resolutions.begin(), settings.resolutions.end(), size) == settings.resolutions.end())
                settings.resolutions.push_back(size);
        };
        for (const auto size : common) addResolution(size);
        addResolution(settings.currentResolution);
        int count = 0;
        SDL_DisplayMode** modes = SDL_GetFullscreenDisplayModes(display, &count);
        if (modes) {
            for (int i = 0; i < count; ++i) addResolution({modes[i]->w, modes[i]->h});
            SDL_free(modes);
        }
        std::sort(settings.resolutions.begin() + 1, settings.resolutions.end(),
            [](ui::DisplayResolution a, ui::DisplayResolution b) {
                return a.width == b.width ? a.height < b.height : a.width < b.width;
            });
        const auto current = std::find(settings.resolutions.begin(), settings.resolutions.end(), settings.currentResolution);
        settings.resolutionIndex = static_cast<int>(current - settings.resolutions.begin());
        settings.resolutionAvailable = true;
    }
#endif
    settings.applyResolution = [&app](const ui::DisplayResolution& requested) {
#if defined(__EMSCRIPTEN__)
        (void)app; (void)requested;
        return false;
#else
        if (!app.window) return false;
        auto& settings = ui::frontendSettings();
        const SDL_DisplayID display = SDL_GetDisplayForWindow(app.window);
        const SDL_DisplayMode* desktop = SDL_GetDesktopDisplayMode(display);
        if (!desktop) return false;
        settings.displayResolution = {desktop->w,desktop->h};
        const bool useDesktop = requested.width == 0;
        const int width = useDesktop ? desktop->w : requested.width;
        const int height = useDesktop ? desktop->h : requested.height;
        if (settings.fullscreen) {
            SDL_DisplayMode mode;
            if (!useDesktop && (!SDL_GetClosestFullscreenDisplayMode(display,width,height,0.f,true,&mode) ||
                mode.w != width || mode.h != height)) return false;
            return SDL_SetWindowFullscreenMode(app.window,useDesktop ? nullptr : &mode);
        }
        const float density = std::max(0.1f,SDL_GetWindowPixelDensity(app.window));
        return SDL_SetWindowSize(app.window,static_cast<int>(std::lround(width/density)),
            static_cast<int>(std::lround(height/density)));
#endif
    };
    settings.applyFullscreen = [&app](bool enabled) {
        auto& settings = ui::frontendSettings();
        if (!app.window) { settings.fullscreen = false; return; }
        const int previousResolution = settings.resolutionIndex;
#if !defined(__EMSCRIPTEN__)
        if (enabled && !settings.applyResolution(settings.resolutions[settings.resolutionIndex])) {
            if (!settings.applyResolution(settings.resolutions[0])) { settings.fullscreen = false; return; }
            settings.resolutionIndex = 0;
        }
#endif
        if (!SDL_SetWindowFullscreen(app.window,enabled)) {
            settings.fullscreen = !enabled;
            settings.resolutionIndex = previousResolution;
        }
    };
    settings.applyBindings = [&app]() {
        const auto& settings = ui::frontendSettings();
        for (int a = 0; a < fnd::input::ActionCount; ++a) {
            app.matchInput.set_keyboard_binding((fnd::input::Action)a, settings.keyboard[a]);
            for (int p = 0; p < 4; ++p)
                app.matchInput.set_gamepad_binding(p, (fnd::input::Action)a, settings.gamepad[p][a]);
        }
    };
    settings.applyBindings();
    // FUN_00647e00 loads the system bank separately from gameplay data/se.
    if (app.menuAudio.open(fnd::audio::Spec{})) {
        app.menuAudio.set_volumes(settings.volumes);
        for (int i = 0; i < 4; ++i) {
            char stem[48];
            std::snprintf(stem, sizeof(stem), "data/sysse/%03d", i);
            const auto& source = fnd::assets::assetSource();
            const std::string path = source.resolve({std::string(stem)+".cnv", std::string(stem)+".wav"});
            app.menuSounds[i] = loadSoundAsset(app.menuAudio, path);
        }
    }
    playFrontendMusic(app, id);
    app.screensMode = true;
    std::printf("screen       : %s (0x%02x)\n", app.screens.screen()->name(),
                (int)app.screens.current());
    return true;
}

}  // namespace

SDL_AppResult SDL_AppInit(void** appstate, int argc, char** argv) {
    auto* app = new App();
    *appstate = app;

#if defined(__EMSCRIPTEN__)
    // argv never reaches wasm, so the web build takes its asset three ways, in
    // this order: ?pack=<manifest-url> (fetched into /packs/, asset= line wins),
    // ?asset=<single CLI arg>, then the configure-time FOUNDATION_WEB_ASSET.
    // Plain builds with none of these keep the triangle demo.
    {
        static std::string webAsset;
        const std::string packUrl = plat::webQueryParam("pack");
        std::string packAsset;
        if (!packUrl.empty() && !plat::fetchWebPack(packUrl, packAsset, app->error))
            return SDL_APP_FAILURE;
        webAsset = plat::webQueryParam("asset");
        if (webAsset.empty()) webAsset = packAsset;
#ifdef FOUNDATION_WEB_ASSET
        if (webAsset.empty()) webAsset = FOUNDATION_WEB_ASSET;
#endif
        static std::vector<std::string> webArgs;
        static std::vector<const char*> webArgv;
        webArgs.clear();
        webArgs.push_back("foundation_demo");
        if (!webAsset.empty()) webArgs.push_back(webAsset);
        // Local browser verification needs the same multi-asset recipe as native.
        const std::string extra = plat::webQueryParam("args");
        size_t begin = 0;
        while (begin < extra.size()) {
            const size_t end = extra.find('|', begin);
            const std::string arg = extra.substr(begin, end == std::string::npos ? end : end - begin);
            if (!arg.empty()) webArgs.push_back(arg);
            if (end == std::string::npos) break;
            begin = end + 1;
        }
        webArgv.clear();
        for (const auto& arg : webArgs) webArgv.push_back(arg.c_str());
        argc = (int)webArgv.size();
        argv = const_cast<char**>(webArgv.data());
    }
#endif
    if (!parseArgs(argc, argv, app->opts, app->error)) {
        usage();
        return SDL_APP_FAILURE;
    }

    // Headless verification: no window, no surface, no swapchain, so the adapter is
    // requested without a presentation target. That is what lets a machine with no
    // DRI3/Wayland display render on the real GPU: Mesa's Vulkan WSI cannot present
    // on Xvfb ("No DRI3 support detected - required for presentation"), and wgpu then
    // falls back to software GL, which would make a Linux/Wine capture pair compare
    // two different rasterizers.
    if (app->opts.headless) {
        if (!SDL_Init(SDL_INIT_EVENTS)) {
            app->error = SDL_GetError();
            return SDL_APP_FAILURE;
        }
        if (!gpu::createContext(app->ctx, nullptr, app->error)) return SDL_APP_FAILURE;
        std::printf("=== daybreak foundation ===\n");
        std::printf("video driver : headless (no window, no surface)\n");
        std::printf("adapter      : %s [%s]\n", app->ctx.adapterName.c_str(),
                    app->ctx.backend.c_str());
    } else {
        if (!plat::init(app->error)) return SDL_APP_FAILURE;

        app->window = plat::createWindow("daybreak foundation", 960, 540, app->error);
        if (!app->window) return SDL_APP_FAILURE;

        // instance -> surface -> adapter/device: the surface has to exist before the
        // adapter is chosen, because it is requested as "compatible with" it.
        if (!gpu::createInstance(app->ctx, app->error)) return SDL_APP_FAILURE;
        app->sc.surface = plat::createSurface(app->ctx.instance, app->window);
        if (!app->sc.surface) {
            app->error = "surface creation failed";
            return SDL_APP_FAILURE;
        }
        if (!gpu::createContext(app->ctx, app->sc.surface, app->error)) return SDL_APP_FAILURE;

        int w = 960, h = 540;
        SDL_GetWindowSizeInPixels(app->window, &w, &h);
        if (!gpu::configureSwapchain(app->ctx, app->sc, (uint32_t)w, (uint32_t)h, app->error))
            return SDL_APP_FAILURE;

        std::printf("=== daybreak foundation ===\n");
        std::printf("video driver : %s\n", plat::videoDriver());
        std::printf("adapter      : %s [%s]\n", app->ctx.adapterName.c_str(),
                    app->ctx.backend.c_str());
        std::printf("surface      : %dx%d, %d format(s), %d present mode(s), fifo=%s\n", w, h,
                    app->sc.formatCount, app->sc.presentModeCount,
                    app->sc.supportsFifo ? "yes" : "no");
        std::printf("present mode : %s\n", gpu::presentModeName(app->sc.presentMode));
    }

    if (app->opts.audioTest) return runAudioTest(*app) ? SDL_APP_SUCCESS : SDL_APP_FAILURE;
    if (app->opts.inputTest) return runInputTest(*app) ? SDL_APP_SUCCESS : SDL_APP_FAILURE;

    const bool ok = !app->opts.screen.empty() ? initScreens(*app)
                   : hasAsset(app->opts)       ? initScene(*app)
                                               : initTriangle(*app);
    if (!ok) return SDL_APP_FAILURE;

    app->startTime = app->lastTime = plat::now();
    return app->opts.list ? SDL_APP_SUCCESS : SDL_APP_CONTINUE;
}

// ---------------------------------------------------------------------------------------
// The --hud-test rig: one deterministic synthetic HUD, composited into --out captures
// through the renderer's UiHook (same encoder, same 3D-then-UI order a game uses).
// Fixed values, so captures stay byte-identical across runs and targets.
// ---------------------------------------------------------------------------------------
struct HudTestHook {
    ui::SpriteRenderer* ui = nullptr;
    ui::HudComposer*    hud = nullptr;
    std::string*        error = nullptr;
    ui::HudState        state;
    bool                hasState = false;   // false -> syntheticHudState()
    bool                referenceCoordinates = true;
};

ui::HudState syntheticHudState() {
    // Field-equal to game::syntheticHudState() by construction (the track's own
    // test pins it); forwarding keeps one definition of the test values.
    return game::syntheticHudState();
}

HudTestHook battleHudHook(App& app) {
    HudTestHook hook{&app.uiRenderer, &app.hudComposer, &app.error};
    if (app.matchMode || app.versusMode) {
        hook.state = app.versusHud;
        hook.hasState = true;
        hook.referenceCoordinates = !app.matchMode;
    }
    return hook;
}

bool hudTestHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                 uint32_t w, uint32_t h, void* ud) {
    auto* hk = static_cast<HudTestHook*>(ud);
    hk->ui->beginFrame(w, h);
    ui::HudState state = hk->hasState ? hk->state : syntheticHudState();
    if (hk->referenceCoordinates) {
        const auto layout = ui::computeBattleHudLayout(w,h);
        for (auto& fighter : state.fighters) {
            fighter.ringX += (layout.width-800.f)*.5f;
            fighter.barX += (layout.width-800.f)*.5f;
            fighter.ringY += (layout.height-600.f)*.5f;
            fighter.barY += (layout.height-600.f)*.5f;
        }
    }
    hk->hud->compose(*hk->ui, state);
    return hk->ui->render(enc, view, format, *hk->error);
}

// The --screen capture's one hook: drawScreenFrame is the same three calls the window
// path makes, so a --out capture cannot drift from what the window shows.
struct ScreenCaptureHook {
    const ui::ScreenStack* screens = nullptr;
    ui::SpriteRenderer*    ui = nullptr;
    std::string*           error = nullptr;
};

bool screenCaptureHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                       uint32_t w, uint32_t h, void* ud) {
    auto* sk = static_cast<ScreenCaptureHook*>(ud);
    return ui::drawScreenFrame(*sk->screens, *sk->ui, w, h, enc, view, format, *sk->error);
}

// The overlay's line set: a pure function of loaded state (bounds, aim, desired eye), so
// two runs of the same frame upload identical bytes — no clock, no RNG, no container
// iteration whose order could vary. render/debug_prims.h documents why captures care.
//
// The eye->aim ray is deliberately NOT drawn: the camera always looks at the aim (and
// sits at the desired eye), so such a segment is edge-on and invisible. The arena mode
// marks the desired eye with its own cross instead — the point the clamp and the
// smoothing spring pull towards, and the one place a camera bug shows up.
void fillDebugLines(App& app) {
    app.debugLines.clear();
    float cross = 40.f;
    if (app.haveDebugBounds) {
        app.debugLines.box(app.debugBoundsLo, app.debugBoundsHi, render::kYellow);
        // Sized from the box so the cross reads at any framing distance: a fixed 40
        // units is sub-pixel in a stage whose play area spans thousands.
        cross = std::max(20.f, 0.015f * glm::length(app.debugBoundsHi - app.debugBoundsLo));
    }
    app.debugLines.cross(app.target, cross, render::kRed);
    if (app.opts.camera == "arena")
        app.debugLines.cross(app.arenaDesired, cross * 0.75f, render::kCyan);
}

// capture() owns its colour and depth textures and takes ONE hook, so the UI pass and
// the prims pass share this one: HUD first (it is the frame's overlay), prims second.
// Both preserve the frame they annotate (LoadOp_Load), so the order between them is
// the only difference. The depth view is read inside the hook, never before it: the
// scene pass creates it, and a capture-sized run has no earlier render to borrow from.
struct CaptureHook {
    render::SceneRenderer*        renderer = nullptr;
    HudTestHook*                  hud = nullptr;    // null -> no UI pass
    render::DebugPrims*           prims = nullptr;  // null -> no prims pass
    const render::DebugLineBatch* lines = nullptr;
    const render::CubeBatch*      solid = nullptr;   // shots + sparks (opaque)
    const render::CubeBatch*      additive = nullptr;   // hypermode auras
    glm::mat4                     viewProj{1.f};
    render::DebugPrims::Options   primOptions;
    std::string*                  error = nullptr;
};

bool captureHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                 uint32_t w, uint32_t h, void* ud) {
    auto* ck = static_cast<CaptureHook*>(ud);
    if (ck->hud && !hudTestHook(enc, view, format, w, h, ck->hud)) return false;
    if (ck->solid && !ck->solid->empty()) {
        const render::Target t{enc, view, format, w, h};
        render::DebugPrims::Options o;   // depth-tested, the reference's opaque cube pass
        if (!ck->prims->drawCubes(t, ck->viewProj, *ck->solid, ck->renderer->depthView(), o,
                                  *ck->error))
            return false;
    }
    if (ck->additive && !ck->additive->empty()) {
        const render::Target t{enc, view, format, w, h};
        render::DebugPrims::Options o;
        o.additive = true;   // SrcAlpha/One, the aura pass's blend
        if (!ck->prims->drawCubes(t, ck->viewProj, *ck->additive, ck->renderer->depthView(), o,
                                  *ck->error))
            return false;
    }
    if (ck->prims && ck->lines && !ck->lines->empty()) {
        const render::Target target{enc, view, format, w, h};
        if (!ck->prims->draw(target, ck->viewProj, *ck->lines, ck->renderer->depthView(),
                             ck->primOptions, *ck->error))
            return false;
    }
    return true;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* app = static_cast<App*>(appstate);

    // The whole frame model, in three lines: real elapsed time in, no fixed step,
    // no accumulator. Present pacing is the swapchain's job (FIFO).
    const double now = plat::now();
    const double delta = now - app->lastTime;
    app->lastTime = now;
    if (app->frames > 0) {  // skip the first sample: it includes setup time
        app->deltaSum += delta;
        if (delta < app->deltaMin) app->deltaMin = delta;
        if (delta > app->deltaMax) app->deltaMax = delta;
    }
    ++app->frames;

    const bool capturing = !app->opts.out.empty();

    // Render-FPS meter tick (D1): wall-clock frames per second, frozen at 60
    // while capturing so the counter cannot make two --out runs differ.
    if (capturing) {
        app->fpsShown = 60;
        app->fpsWindow = 0.0;
        app->fpsFrames = 0;
    } else if (app->frames > 1) {  // first delta includes setup time
        app->fpsWindow += delta;
        ++app->fpsFrames;
        if (app->fpsWindow >= 0.5) {
            app->fpsShown = (int)std::lround((double)app->fpsFrames / app->fpsWindow);
            app->fpsWindow = 0.0;
            app->fpsFrames = 0;
        }
    }

    if (capturing) {
        // Verify with real time, not with a fixed step: the pose follows the clock, so
        // a capture after N frames of --dt is the pose at N * dt seconds.
        if (app->opts.anim >= 0 && app->frames > 1) advanceAnimation(*app, (double)app->opts.dt);
    } else if (!app->controllers.empty()) {
        advanceAnimation(*app, delta);
    }

    if (app->versusMode) tickVersus(*app, app->frames);
    if (app->matchMode) {
        // The match runs on the same fixed step the DX9 harness uses (1/60) whenever
        // it is capturing, and on the real delta in a live window — the reference's
        // own split (fixed step for the suite, wall time otherwise).
        tickMatch(*app, capturing ? app->opts.dt : delta);
        traceMatch(*app);
        if (app->frontendMatch && app->match.economy().roundOver()) {
            const int loser = app->match.economy().roundOverSide();
            app->frontend.resultWinner = loser < 0 ? -1 : 1 - loser;
            for (int i = 0; i < app->match.config().fighterCount; ++i) {
                const auto& stats = app->match.fighter(i).stats();
                const int panel = app->battleLaunch.fighters[i].panel;
                app->frontend.resultStats[panel] = {stats.kos,stats.deaths,stats.damageDealt,stats.damageTaken};
            }
            app->matchMode = false;
            app->frontendBattleReady = false;
            app->versusAudio.clear_music();
            app->screens.request(ui::ScreenId::Result);
            app->screensMode = true;
        }
    }

    if (app->screensMode) {
        // The stack ticks on app->frames, the same 1-based index the DX9 suite's input
        // scripts are written in (tickMatch keys its scripts on matchFrame for the same
        // reason). Confirm is Jump — Z, the menu confirm — and cancel is AttackA (X).
        app->matchInput.tick_script(app->frames);
        app->matchInput.poll();
        ui::ScreenInput in;
        in.up      = app->matchInput.any_just_pressed(fnd::input::Up);
        in.down    = app->matchInput.any_just_pressed(fnd::input::Down);
        in.left    = app->matchInput.any_just_pressed(fnd::input::Left);
        in.right   = app->matchInput.any_just_pressed(fnd::input::Right);
        in.confirm = app->matchInput.any_just_pressed(fnd::input::Jump);
        in.cancel  = app->matchInput.any_just_pressed(fnd::input::AttackA);
        in.separatePlayers = true;
        for (int p = 0; p < 4; ++p) {
            const auto& input = app->matchInput.player(p);
            auto& buttons = in.players[p];
            buttons.up = input.just_pressed[fnd::input::Up];
            buttons.down = input.just_pressed[fnd::input::Down];
            buttons.left = input.just_pressed[fnd::input::Left];
            buttons.right = input.just_pressed[fnd::input::Right];
            buttons.confirm = input.just_pressed[fnd::input::Jump];
            buttons.cancel = input.just_pressed[fnd::input::AttackA];
        }
        app->screens.update(in);
        if (!app->error.empty()) return SDL_APP_FAILURE;
        if (app->menuAudio.music_queued_frames() < 4096)
            app->menuLoop.push_next(app->menuAudio, 1024);
        const std::string voice = app->screens.takeVoice();
        if (!voice.empty()) {
            auto& source = fnd::assets::assetSource();
            const size_t dot = voice.find_last_of('.');
            const std::string stem = dot == std::string::npos ? voice : voice.substr(0,dot);
            const std::string path = source.resolve({stem+".cnv",stem+".wav"});
            const auto handle = loadSoundAsset(app->menuAudio,path);
            if (app->menuAudio.play(handle,fnd::audio::SfxBus::Voice) >= 0) ++app->menuVoicePlays;
        }
        if (app->screens.current() == ui::ScreenId::Battle && app->frontendBattleReady && app->screens.fadeFrame() == 0) {
            app->screensMode = false;
            app->matchMode = true;
            return SDL_APP_CONTINUE;
        }
        const int cue = app->screens.takeSound();
        if (cue >= 0 && cue < 4 && app->menuSounds[cue] >= 0) {
            app->menuAudio.stop(fnd::audio::kUiChannel);
            if (app->menuAudio.play(app->menuSounds[cue], fnd::audio::SfxBus::Ui) >= 0)
                ++app->menuSoundPlays[cue];
        }
        // 終了 reaches here: its item returns 0x16, the factory has no such scene, and
        // the switcher reads the null scene as "no scene: quit" (ui/screen.h).
        if (app->screens.finished()) return app->error.empty() ? SDL_APP_SUCCESS : SDL_APP_FAILURE;

        if (capturing) {
            if (app->frames >= (uint64_t)app->opts.frames) {
                std::vector<uint8_t> rgba;
                ScreenCaptureHook hook{&app->screens, &app->uiRenderer, &app->error};
                // captureUi: a menu frame has no 3D scene, so the scene pass is skipped
                // and the UI hook draws onto the cleared target (scene_renderer.h).
                if (!app->renderer.captureUi((uint32_t)app->opts.sizeW,
                                             (uint32_t)app->opts.sizeH, rgba, app->error,
                                             screenCaptureHook, &hook))
                    return SDL_APP_FAILURE;
                reportCoverage(rgba, app->opts.sizeW, app->opts.sizeH);
                writePpm(app->opts.out, rgba, app->opts.sizeW, app->opts.sizeH);
                return SDL_APP_SUCCESS;
            }
            return SDL_APP_CONTINUE;   // wait for the capture frame, as the asset path does
        }

        gpu::Frame frame;
        if (!gpu::beginFrame(app->ctx, app->sc, frame, app->error)) return SDL_APP_FAILURE;
        // Clear first: the UI pass loads (sprite.cpp:468), the screen art is authored
        // 800x600, and a larger window would otherwise present undefined backbuffer
        // pixels around it. Same opaque-black background captureUi gives a --out frame.
        WGPURenderPassColorAttachment clear = {};
        clear.view = frame.view;
        clear.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
        clear.loadOp = WGPULoadOp_Clear;
        clear.storeOp = WGPUStoreOp_Store;
        clear.clearValue = WGPUColor{0.0, 0.0, 0.0, 1.0};
        WGPURenderPassDescriptor clearPass = {};
        clearPass.colorAttachmentCount = 1;
        clearPass.colorAttachments = &clear;
        WGPURenderPassEncoder clearRp =
            wgpuCommandEncoderBeginRenderPass(frame.encoder, &clearPass);
        wgpuRenderPassEncoderEnd(clearRp);
        wgpuRenderPassEncoderRelease(clearRp);
        if (!ui::drawScreenFrame(app->screens, app->uiRenderer, app->sc.width, app->sc.height,
                                 frame.encoder, frame.view, app->sc.format, app->error)) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (!gpu::endFrame(app->ctx, app->sc, frame)) return SDL_APP_FAILURE;
    } else if (hasAsset(app->opts)) {
        const uint32_t w = capturing ? (uint32_t)app->opts.sizeW : app->sc.width;
        const uint32_t h = capturing ? (uint32_t)app->opts.sizeH : app->sc.height;
        // Not in match mode: tickMatch already stepped the ported reference camera,
        // and this block's spring would overwrite its eye with the demo's own framing.
        if (app->opts.camera == "arena" && !app->matchMode) {
            // First frame seeds from the desired eye, so single-frame captures stay
            // exactly deterministic; longer runs converge through the dt-correct
            // spring instead of snapping.
            if (!app->havePrevEye) {
                app->prevEye = app->arenaDesired;
                app->havePrevEye = true;
            }
            // Captures step the spring with the fixed --dt, not wall time: the
            // eye must be as deterministic as the pose or captures would drift.
            const double stepDt = capturing ? (double)app->opts.dt : delta;
            // Clamp the desired eye against the stage's camera collision mesh before
            // smoothing, exactly as the reference composes it (arena_camera.cpp:106-131):
            // one query, the 20-unit margin inside arenaClampEye, no second refine pass.
            // Stages without camera geometry answer "no hit" and this is a pass-through.
            glm::vec3 desired = app->arenaDesired;
            if (!app->opts.noCameraClamp) {
                const game::CameraClampResult clamp =
                    app->cameraCollision.queryClamp({app->target, desired});
                if (clamp.hit) {
                    const float segment = glm::length(desired - app->target);
                    desired = render::arenaClampEye(app->target, desired,
                                                    game::clampHitDistance(clamp, segment));
                }
            }
            app->eye = render::arenaSmoothEyeDt(app->prevEye, desired, (float)stepDt, 0.1f);
            app->prevEye = app->eye;
        }
        // One matrix, built once and handed to both the scene pass and the prims pass:
        // the overlay is only correct if it is projected exactly like the frame under it.
        // Match frames use the reference camera's own projection (fov pi/4, near 1,
        // far 100000) and view, so a foundation frame and a banked DX9 frame of the
        // same case differ by their content, not by their projection.
        const glm::mat4 vp = app->matchMode
            ? app->matchCamera.proj_matrix((int)w, (int)h) * app->matchCamera.view_matrix()
            : viewProj(app->eye, app->target, (float)w / (float)h,
                       app->cameraRadius, app->sceneReach);
        if (app->matchMode) {
            // FUN_00643230 projects through the same camera and aspect used for the frame.
            const auto layout = ui::computeBattleHudLayout(w,h);
            for (int i = 0; i < 2; ++i) {
                int fighterIndex = i;
                if (app->frontendMatch) {
                    const int panel = ui::kFrontendBattleSlots[i];
                    for (int j = 0; j < app->battleLaunch.fighterCount; ++j)
                        if (app->battleLaunch.fighters[j].panel == panel) fighterIndex = j;
                }
                const auto& fighter = app->match.fighter(fighterIndex);
                game::projectFighterHud(&vp[0][0],fighter.position().x,fighter.position().y,
                                       fighter.position().z,app->versusHud.fighters[i],
                                       layout.width,layout.height);
            }
        }
        app->renderer.setCamera(vp);
        app->renderer.setEye(app->eye);

        if (capturing) {
            // --out without --frames means one frame, so the last frame is always defined.
            if (app->frames >= (uint64_t)app->opts.frames) {
                std::vector<uint8_t> rgba;
                HudTestHook hook = battleHudHook(*app);
                const bool useHud = (app->opts.hudTest || app->versusMode || app->matchMode) &&
                                    app->uiReady;
                CaptureHook cap;
                cap.renderer = &app->renderer;
                cap.error = &app->error;
                cap.viewProj = vp;
                if (useHud) cap.hud = &hook;
                // One batch for both sources: the debug overlay and the match's
                // shots/sparks share the pass, so neither can clobber the other.
                if (app->opts.debugPrims || app->matchMode) {
                    if (app->opts.debugPrims) fillDebugLines(*app);
                    else app->debugLines.clear();
                    if (app->matchMode) fillMatchCubes(*app);
                    cap.prims = &app->debugPrims;
                    cap.lines = &app->debugLines;
                    if (app->matchMode) {
                        cap.solid = &app->matchCubes;
                        cap.additive = &app->auraCubes;
                    }
                }
                const bool useHook = useHud || cap.prims;
                if (!app->renderer.capture((uint32_t)app->opts.sizeW,
                                           (uint32_t)app->opts.sizeH, rgba, app->error,
                                           useHook ? captureHook : nullptr,
                                           useHook ? &cap : nullptr))
                    return SDL_APP_FAILURE;
                reportCoverage(rgba, app->opts.sizeW, app->opts.sizeH);
                writePpm(app->opts.out, rgba, app->opts.sizeW, app->opts.sizeH);
                if (app->opts.debugPrims) {
                    const render::DebugPrims::Stats& ds = app->debugPrims.stats();
                    std::printf("debug prims : %zu line(s), %zu vertices, %zu dropped, %zu pass(es)\n",
                                ds.lines, ds.vertices, ds.droppedVertices, ds.passes);
                }
                if (app->matchMode) {
                    const gameplay::MatchEconomy& eco = app->match.economy();
                    std::printf("match: %llu frames, hp1=%d hp2=%d, balloon=%.0f%%/%.0f%% "
                                "(LIMIT %.0f%%), shots=%llu sparks=%llu hits=%llu, "
                                "fx events=%llu, bgm pushed %llu frames, %llu wraps, roundOver=%d\n",
                                (unsigned long long)app->matchFrame, app->match.fighter(0).hp(),
                                app->match.fighter(1).hp(), (double)eco.balloon(0),
                                (double)eco.balloon(1), (double)eco.limit(),
                                (unsigned long long)app->matchShots,
                                (unsigned long long)app->matchSparks,
                                (unsigned long long)app->matchHits,
                                (unsigned long long)app->matchFxEvents,
                                (unsigned long long)app->versusBgmPushed,
                                (unsigned long long)app->versusLoop.loops_completed(),
                                app->matchRoundOverFrame ? 1 : 0);
                }
                if (app->versusMode) {
                    std::printf("versus: %llu frames, hp1=%.0f hp2=%.0f, bgm pushed %llu frames, %llu wraps, sfx plays %llu, fx events %llu\n",
                                (unsigned long long)app->frames, (double)app->versusHud.hp, 100.0,
                                (unsigned long long)app->versusBgmPushed,
                                (unsigned long long)app->versusLoop.loops_completed(),
                                (unsigned long long)app->versusSfxPlays,
                                (unsigned long long)app->versusFxEvents);
                }
                return SDL_APP_SUCCESS;
            }
            return SDL_APP_CONTINUE;
        }

        gpu::Frame frame;
        if (!gpu::beginFrame(app->ctx, app->sc, frame, app->error)) {
            // A lost/outdated surface is recoverable in principle; for the foundation
            // demo it is enough to stop cleanly rather than spin on a broken swapchain.
            return SDL_APP_FAILURE;
        }
        render::Target target;
        target.encoder = frame.encoder;
        target.colorView = frame.view;
        target.format = app->sc.format;
        target.width = app->sc.width;
        target.height = app->sc.height;
        if (!app->renderer.render(target, app->error)) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (app->opts.debugPrims || app->matchMode) {
            if (app->opts.debugPrims) fillDebugLines(*app);
            else app->debugLines.clear();
            if (app->matchMode) fillMatchCubes(*app);
            if (app->matchMode && !app->matchCubes.empty()) {
                render::DebugPrims::Options cubeOptions;
                if (!app->debugPrims.drawCubes(target, vp, app->matchCubes,
                                               app->renderer.depthView(), cubeOptions,
                                               app->error)) {
                    gpu::endFrame(app->ctx, app->sc, frame);
                    return SDL_APP_FAILURE;
                }
            }
            if (app->matchMode && !app->auraCubes.empty()) {
                render::DebugPrims::Options cubeOptions;
                cubeOptions.additive = true;
                if (!app->debugPrims.drawCubes(target, vp, app->auraCubes,
                                               app->renderer.depthView(), cubeOptions,
                                               app->error)) {
                    gpu::endFrame(app->ctx, app->sc, frame);
                    return SDL_APP_FAILURE;
                }
            }
            render::DebugPrims::Options primOptions;   // depth-tested: lines behind walls hide
            if (!app->debugPrims.draw(target, vp, app->debugLines, app->renderer.depthView(),
                                      primOptions, app->error)) {
                gpu::endFrame(app->ctx, app->sc, frame);
                return SDL_APP_FAILURE;
            }
        }
        if (app->uiReady && (app->opts.hudTest || app->matchMode || app->versusMode)) {
            HudTestHook hook = battleHudHook(*app);
            if (!hudTestHook(frame.encoder,frame.view,app->sc.format,app->sc.width,app->sc.height,&hook)) {
                gpu::endFrame(app->ctx,app->sc,frame);
                return SDL_APP_FAILURE;
            }
        }
        if (!gpu::endFrame(app->ctx, app->sc, frame)) return SDL_APP_FAILURE;
    } else {
        app->spin += (float)delta * 1.2f;
        const Mat4 transform = rotationZ(app->spin, 1.0f);
        wgpuQueueWriteBuffer(app->ctx.queue, app->uniformBuffer, 0, transform.m, sizeof(transform.m));

        gpu::Frame frame;
        if (!gpu::beginFrame(app->ctx, app->sc, frame, app->error)) return SDL_APP_FAILURE;

        WGPURenderPassColorAttachment color = {};
        color.view = frame.view;
        color.depthSlice = WGPU_DEPTH_SLICE_UNDEFINED;
        color.loadOp = WGPULoadOp_Clear;
        color.storeOp = WGPUStoreOp_Store;
        color.clearValue = WGPUColor{0.06, 0.07, 0.09, 1.0};

        WGPURenderPassDescriptor pass = {};
        pass.colorAttachmentCount = 1;
        pass.colorAttachments = &color;

        WGPURenderPassEncoder rp = wgpuCommandEncoderBeginRenderPass(frame.encoder, &pass);
        wgpuRenderPassEncoderSetPipeline(rp, app->pipeline);
        wgpuRenderPassEncoderSetBindGroup(rp, 0, app->bindGroup, 0, nullptr);
        wgpuRenderPassEncoderSetVertexBuffer(rp, 0, app->vertexBuffer, 0, WGPU_WHOLE_SIZE);
        wgpuRenderPassEncoderDraw(rp, 3, 1, 0, 0);
        wgpuRenderPassEncoderEnd(rp);
        wgpuRenderPassEncoderRelease(rp);

        if (!gpu::endFrame(app->ctx, app->sc, frame)) return SDL_APP_FAILURE;
    }

    if (app->opts.frames > 0 && app->frames >= (uint64_t)app->opts.frames) return SDL_APP_SUCCESS;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event) {
    auto* app = static_cast<App*>(appstate);
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
            if (ui::bindingCaptureActive()) {
                app->matchInput.suppress_key((int)event->key.scancode);
                if (event->key.key == SDLK_ESCAPE) ui::cancelBindingCapture();
                else if (!event->key.repeat) ui::submitBindingInput(true, 0, (int)event->key.scancode);
                return SDL_APP_CONTINUE;
            }
            app->matchInput.note_key((int)event->key.scancode, true);
            if (event->key.key == SDLK_ESCAPE) return SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_KEY_UP:
            app->matchInput.note_key((int)event->key.scancode, false);
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            app->matchInput.note_focus_lost();
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            if (ui::bindingCaptureActive()) {
                const int player = app->matchInput.gamepad_player((int32_t)event->gbutton.which);
                app->matchInput.suppress_gamepad_button(player,(int)event->gbutton.button);
                ui::submitBindingInput(false, player, (int)event->gbutton.button);
            }
            break;
        case SDL_EVENT_WINDOW_DISPLAY_CHANGED:
            if (app->window) {
                const SDL_DisplayID display = SDL_GetDisplayForWindow(app->window);
                if (const SDL_DisplayMode* mode = SDL_GetDesktopDisplayMode(display))
                    ui::frontendSettings().displayResolution = {mode->w,mode->h};
            }
            break;
        case SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED: {
            // A resized window needs the swapchain reconfigured, not just a new
            // viewport: the surface's back buffers are sized at configure time.
            const uint32_t w = (uint32_t)event->window.data1;
            const uint32_t h = (uint32_t)event->window.data2;
            if (w && h && !gpu::configureSwapchain(app->ctx, app->sc, w, h, app->error))
                return SDL_APP_FAILURE;
            if (app->window && w && h) {
                auto& settings = ui::frontendSettings();
                settings.currentResolution = {static_cast<int>(w),static_cast<int>(h)};
                if (settings.resolutionAvailable && !settings.fullscreen) {
                    auto current = std::find(settings.resolutions.begin(),settings.resolutions.end(),settings.currentResolution);
                    if (current == settings.resolutions.end()) {
                        settings.resolutions.push_back(settings.currentResolution);
                        settings.resolutionIndex = static_cast<int>(settings.resolutions.size()) - 1;
                    } else settings.resolutionIndex = static_cast<int>(current - settings.resolutions.begin());
                }
            }
            break;
        }
        default:
            break;
    }
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult) {
    auto* app = static_cast<App*>(appstate);
    if (!app) return;
    if (!app->opts.screen.empty())
        std::printf("menu-audio: confirm=%llu back=%llu cursor=%llu ready=%llu voices=%llu\n",
            (unsigned long long)app->menuSoundPlays[0], (unsigned long long)app->menuSoundPlays[1],
            (unsigned long long)app->menuSoundPlays[2], (unsigned long long)app->menuSoundPlays[3],
            (unsigned long long)app->menuVoicePlays);
    ui::frontendSettings().applyVolumes = {};
    ui::frontendSettings().applyFullscreen = {};
    ui::frontendSettings().applyResolution = {};
    ui::frontendSettings().applyBindings = {};
    report(*app);
    teardown(*app);
    delete app;
}
