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
#include "ui/participants.h"
#include "ui/hud_atlas.h"
#include "ui/frontend_settings.h"
#include "settings/user_settings.h"
#include "game/hud_bridge.h"
#include "game/fighter_pose.h"
#include "game/match_view.h"
#include "game/view_layout.h"
#include "gameplay/arena_camera.h"
#include "gameplay/battle_pause.h"
#include "gameplay/match.h"
#include "gameplay/fixed_step.h"
#include "gameplay/bot_input.h"
#include "gameplay/hud_fill.h"
#include "gameplay/result_title.h"
#include "audio/audio.h"
#include "audio/audio_engine.h"
#include "audio/combat_audio.h"
#include "game/effect_events.h"
#include "game/effect_catalog.h"
#include "game/fx_cards.h"
#include "input/input_backend.h"
#include "input/tick_input.h"
#include "input/input_sdl3.h"
#include "input/synthetic_pad.h"
#include "shaders/demo_wgsl.h"
#include <unordered_map>

namespace {

// ---------------------------------------------------------------------------------------
// Command line
// ---------------------------------------------------------------------------------------
struct Options {
    // Asset selection. Exactly one of stage/character/weapon/model, or none for the
    // triangle demo; an effect file may ride along with any of them.
    std::string model, stage, character, weapon, effect;
    bool        hudTest = false;   // composite a synthetic HUD into --out captures
    bool        hudProbe = false;  // --hud-probe: corner markers for the placement test
    bool        debugPrims = false; // draw the deterministic debug line overlay
    bool        audioTest = false; // run the audio backend self-check and exit
    bool        combatAudioLog = false;  // --combat-audio-log: name every resolved SE/voice
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
    bool        hitboxDebug = false;  // draw the recovered melee hit spheres (issue #10)
    // Interactive animation browser: one rig, no stage, arrows change the set index
    // and WASD orbits the camera. Exists because the state's anim-set table has
    // unmapped entries (Jump/Guard/TagOut return -1) and set 2 does not look like an
    // attack, which is only checkable by looking at the clips side by side.
    bool        animPlayer = false;
    bool        unlit      = false;
    // Toon rendering (issue #21). `toonSet` separates "the flag was passed" from the
    // default: without it the live Options row governs, with it the flag wins — so a
    // capture command line pins the state it asked for, and an interactive run is never
    // overridden by a stale flag.
    bool        toon       = false;
    bool        toonSet    = false;
    bool        list       = false;
    std::string screen;          // --screen=<id|name>: boot a front-end screen
    // Split-screen verification (issue #12): open this many local human views by
    // assigning controllers 0..N-1 to the battle panels, so a headless run exercises the
    // per-controller camera/HUD path. 0 (default) keeps the historical single-view flow.
    int         localPlayers = 0;
    // --lock-taps: let those synthetic pads also tap LockSwitch (the per-view camera
    // retarget). Off by default so an evidence run's cameras hold their fighters.
    bool        lockTaps = false;
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

// Forward declarations: defined beside loadWeaponDefinition below, used by the
// scene assembly above so a fighter without an explicit weapon still gears up.
static std::string charDirForSpec(const std::string& spec);
static bool resolveFighterWeapon(const std::string& charDir,
                                 const std::string& explicitSpec, std::string& meshSpec,
                                 int& itemId);

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
        "                     the set index, WASD orbits the camera, name on top\n"
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
        "  --toon | --no-toon toon rendering (issue #21): the character and weapon draws\n"
        "                     read the shipped data/directX/toon ramp at their diffuse\n"
        "                     term instead of the linear N.L. Off by default, which is the\n"
        "                     state every banked capture was made in\n"
        "  --list             print what was loaded and exit\n"
        "  --screen=<id|name> boot a front-end screen (title, 1, 0x01, ...) instead of\n"
        "                     an asset; --script= drives its menu and --out captures it\n"
        "  --effect=<file.x>  load one card with the effect role (additive pass)\n"
        "  --hud-test         composite a synthetic HUD into --out captures\n"
        "  --hud-probe        with --hud-test: draw per-view corner markers so a capture\n"
        "                     can be measured (split-screen HUD placement)\n"
        "  --debug-prims      draw a deterministic debug line overlay (play-area box,\n"
        "                     aim cross, desired-eye cross under --camera=arena)\n"
        "  --install=<dir>    use this game install's daybreakXX.dat bundles; when\n"
        "                     omitted, the install is inferred from the asset paths\n"
        "  --no-camera-clamp  A/B switch: skip the arena eye's collision_camera clamp\n"
        "  --headless         no window, no surface, no swapchain: render straight to\n"
        "                     offscreen captures (needs --out). Lets verification run\n"
        "                     where no presentable display exists, on the real GPU\n"
        "  --audio-test         run the audio backend self-check and exit\n"
        "  --combat-audio-log   log every dispatched combat SE/voice with its resolved file\n"
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
        "  --local-players=N  verification: open N local human views (1..4) by assigning\n"
        "                     controllers 0..N-1 to the battle panels and give a\n"
        "                     controller with no attached pad a deterministic synthetic\n"
        "                     press pattern. Synthetic input is not physical-pad evidence;\n"
        "                     a real pad for that controller takes precedence\n"
        "  --lock-taps        let the synthetic pads tap LockSwitch too (the per-view\n"
        "                     camera retarget). Off by default: four views each sweeping\n"
        "                     between fighters reads as a camera defect, not a gesture\n"
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
        else if (a == "--anim-player") o.animPlayer = true;
        else if (!(v = val("--time=")).empty()) o.time = (float)std::atof(v.c_str());
        else if (!(v = val("--dt=")).empty()) o.dt = (float)std::atof(v.c_str());
        else if (!(v = val("--camera=")).empty()) o.camera = v;
        else if (!(v = val("--audio-file=")).empty()) o.audioFile = v;
        else if (a == "--no-textures") o.noTextures = true;
        else if (a == "--fog") o.fog = true;
        else if (a == "--no-anim") o.noAnim = true;
        else if (a == "--unlit") o.unlit = true;
        else if (a == "--toon") { o.toon = true; o.toonSet = true; }
        else if (a == "--no-toon") { o.toon = false; o.toonSet = true; }
        else if (a == "--list") o.list = true;
        else if (a == "--hud-test") o.hudTest = true;
        else if (a == "--hud-probe") { o.hudTest = true; o.hudProbe = true; }
        else if (a == "--debug-prims") o.debugPrims = true;
        else if (!(v = val("--install=")).empty()) o.install = v;
        else if (a == "--no-camera-clamp") o.noCameraClamp = true;
        // Debug overlay: draw the recovered melee hit spheres (issue #10). Off by
        // default so no capture and no trace is affected by it.
        else if (a == "--hitbox-debug") o.hitboxDebug = true;
        else if (a == "--headless") o.headless = true;
        else if (a == "--audio-test") o.audioTest = true;
        else if (a == "--combat-audio-log") o.combatAudioLog = true;
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
        else if (!(v = val("--local-players=")).empty()) o.localPlayers = std::atoi(v.c_str());
        else if (a == "--lock-taps") o.lockTaps = true;
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
    if (o.localPlayers < 0 || o.localPlayers > 4) {
        error = "--local-players takes 0..4 (the four controller slots)";
        return false;
    }
    if (o.localPlayers > 0 && o.screen.empty()) {
        error = "--local-players needs --screen (the front end owns the controller slots)";
        return false;
    }
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

// Forward declaration: defined beside loadWeaponDefinition below, used by the
// scene assembly here so a fighter without an explicit weapon still gears up.
static void attachFighterWeapon(xm::Scene& scene, const std::string& label,
                                const std::string& charSpec,
                                const std::string& weaponSpec, const xm::Model* rig,
                                const xm::SceneOptions& sopt);

xm::Scene loadScene(const Options& o, std::string& error, size_t* enemyBegin = nullptr) {
    xm::SceneOptions sopt;
    sopt.resolveTextures = !o.noTextures;
    sopt.includeCollision = true;   // framing and gameplay queries; never drawn

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
                const size_t character = firstCharacter(scene, rig);
                if (character >= scene.models.size()) throw std::runtime_error("battle fighter rig is missing");
                attachFighterWeapon(scene, "fighter " + std::to_string(i),
                                    o.battleCharacters[i], o.battleWeapons[i],
                                    &scene.models[character].model, sopt);
            }
            scene.source = o.stage;
            return scene;
        }
        appendCharacter(scene, o.character, sopt);
        {
            size_t p1 = firstCharacter(scene, 0);
            attachFighterWeapon(scene, "P1", o.character, o.weapon,
                                p1 < scene.models.size() ? &scene.models[p1].model
                                                         : nullptr,
                                sopt);
        }
        if (enemyBegin) *enemyBegin = scene.models.size();
        appendCharacter(scene, o.enemy, sopt);
        {
            const size_t p2 = firstCharacter(scene, enemyBegin ? *enemyBegin : 0);
            attachFighterWeapon(scene, "P2", o.enemy, o.enemyWeapon,
                                &scene.models[p2].model, sopt);
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
    render::CubeBatch            hitboxCubes{4096};  // --hitbox-debug: hit/hurt volumes
    glm::vec3                    debugBoundsLo{0.f}, debugBoundsHi{0.f};
    bool                         haveDebugBounds = false;
    game::physics::CameraCollision cameraCollision;   // arena eye clamp, per stage
    game::physics::MovementCollision movementCollision; // borrowed collision.x movement/ground meshes
    const xm::Model* projectileCollisionMesh = nullptr;
    game::physics::ModelIndex projectileCollisionIndex;
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
    // One COM decision state per fighter slot (issue #14) plus the recovered tactics
    // readout the whole team shares (gameplay/bot_input.h). The brains are reseeded from
    // the match seed when a match resets, so a run replays from its seed alone.
    gameplay::BotBrain            botBrains[4];
    gameplay::TacticReadout       tacticReadout;

    ui::HudComposer              hudComposer;
    bool                         uiReady = false;
    render::Options              renderOptions;
    render::Appearance           appearance;
    glm::vec3                    eye{0.f}, target{0.f};
    float                        cameraRadius = 1.f, sceneReach = 0.f;
    glm::vec3                    arenaDesired{0.f};
    glm::vec3                    prevEye{0.f};
    bool                         havePrevEye = false;

    // --anim-player orbit. Kept separate from arenaCamera because this view has no
    // arena, no follow and no clamp: the eye is a plain orbit around the rig's origin so
    // a clip can be judged from any angle without the game camera in the way.
    float                        apYaw = 0.6f, apPitch = 0.25f, apDist = 340.f;
    int                          apIndex = 0;
    double                       apTime = 0.0;       // seconds into the clip
    double                       apLength = 1.0;     // the clip's own length
    ui::CaptionText              apText;
    ui::CaptionText              pauseText;

    // Playable match (Phase 2): the ported simulation drives the fighters, the HUD
    // values and the effects, instead of the versus vignette's frame-index script.
    gameplay::Match              match;
    bool                         matchMode = false;
    uint64_t                     matchFrame = 0;      // 1-based, the DX9's frame_count+1
    // Per-controller views of the live match (issue #12). Views exist for HUMAN
    // controllers only; a COM slot never allocates one. `matchViewCount` is how many of
    // the four are live this match, and the simulation is stepped once regardless of it.
    game::MatchView              matchViews[game::kMaxHumanViews];
    int                          matchViewCount = 0;
    // The launch roster in PANEL order (issue #13): the one list VS, the battle HUD and the
    // results all read, so the three screens cannot disagree about who is fighting. A slot
    // with no selection is absent, which is how a 1v1 stays a two-entry roster.
    ui::Participant              participants[ui::kParticipantCount];
    int                          participantCount = 0;
    // The earned-title record's own counters (issue #20): what FUN_00430880 reads that this port
    // can evidence from the frame's melee events — hits dealt/taken split by the lock each side
    // held, and the hits landed on the local (1P) fighter. Damage totals come from
    // Fighter::stats() and the capacities from the economy when the round resolves.
    struct TitleHits {
        int toTarget = 0, toOthers = 0, fromTarget = 0, fromOthers = 0, onLocalPlayer = 0;
    };
    TitleHits                    titleHits[4];
    uint32_t                     titleRng = 0x9e3779b9u;   // session RNG for the penalty rolls
    // --local-players' menu clock: the tick the selection screen appeared, so the synthetic
    // pads' panel walk is timed from the screen and not from process start.
    bool                         selectSeen = false;
    uint64_t                     selectEnterTick = 0;
    gameplay::CameraTarget       arenaTargets[4];     // refreshed from the live fighters
    fnd::input::Backend          matchInput;          // P1 device + script override
    bool                         matchInputReady = false;
    // Persisted user configuration (issue #19). `userSettings` is the last document we
    // loaded or saved; the frame loop compares it against the live settings, so every
    // change path (options, key config, a pad appearing) is caught without each screen
    // having to announce itself. Empty path or settingsActive=false means this run is a
    // capture/parity path or has no user config directory: nothing is read or written.
    settings::UserSettings       userSettings;
    std::string                  settingsPath;
    bool                         settingsActive = false;
    bool                         settingsDirty = false;
    // Battle pause (issue #15): the recovered freeze flag plus the port's menu cursor. The
    // authoritative gate lives in Match (set_paused); this is the host's presentation and
    // input state.
    bool                         battlePaused = false;
    gameplay::PauseMenu          pauseMenu;
    fnd::audio::SfxHandle        pauseSound = fnd::audio::kInvalidSfx;
    bool                         pauseSoundTried = false;
    // A standalone --match script is indexed by the match frame (the banked traces depend on
    // that), and the match frame freezes with the pause — so a scripted pause could never be
    // resumed there. The paused ticks advance this offset instead, which keeps the script
    // clock monotonic: no event is skipped while paused and none is replayed on resume.
    // Zero for every capture/replay run, which never pause.
    uint64_t                     pauseScriptAdvance = 0;
    bool                         settingsSaveReported = false;
    double                       settingsDirtyAt = 0.0;
    double                       settingsNextSaveAt = 0.0;
    fnd::input::PlayerState      p2State;             // P2 script state (unused when dummy)
    std::vector<fnd::input::ScriptEvent> p2Script;
    size_t                       p2ScriptPos = 0;
    uint32_t                     p2Mask = 0;
    size_t                       matchRig[4] = {0, 0, 0, 0};   // controller index per fighter
    ui::FrontendLaunch           battleLaunch;
    // Parsed data/item/NNN.dat for every weapon the front end selected, indexed by
    // fighter (issue #9). Owned here so the pointers MatchConfig::weapon hands out
    // outlive the match. Empty on the standalone --match path, which keeps the
    // historical shared tuning and its banked trace.
    std::vector<std::unique_ptr<gameplay::WeaponDefinition>> weaponDefs;
    // Decoded data/bullet/<weaponId>/<type>.dat parameters, parallel to weaponDefs:
    // [fighter][chargeLevel-1]. Borrowed by the fighters, so it must outlive them.
    std::vector<std::array<std::unique_ptr<gameplay::BulletParameter>, 2>> bulletParams;
    // Parsed data/<char>/NN.dat move tables, indexed by fighter (issue #26). Owned
    // here so the pointers MatchConfig::moves hands out outlive the match. Empty
    // when the rig's .dat cannot be found, which keeps the legacy shared swing.
    std::vector<std::unique_ptr<gameplay::CharacterMoves>> moveDefs;
    uint64_t                     matchShots = 0, matchSparks = 0, matchHits = 0;
    uint64_t                     matchRoundOverFrame = 0;
    game::EffectEventQueue       matchFx;
    uint64_t                     matchFxEvents = 0;
    // B1/issue #17: the live effect cards the renderer draws from the event queues
    // above. A card's `asset` is a scene-model index (the catalog's, or an attachment
    // slot's); `liveFx` is this frame's card set, owned here — the set itself
    // (game::LiveFxCard) and its update rules live in game/fx_cards.h, unit-tested in
    // tests/fx_cards_test.cpp.
    // Issue #17: the effect table. `fxCatalog` maps an effect id (type*10+variant,
    // data/effect/%03d.dat) to its loaded card and its recovered lifetime; `fxAttach`
    // holds FUN_00633ca0's seven data/aura/%02d.x attachment models, whose textures are
    // the three muzzle flashes (slots 0/1/5), the blue hit (2) and the burning aura (3).
    game::EffectCatalog fxCatalog;
    int  fxAttach[7] = {-1, -1, -1, -1, -1, -1, -1};
    float fxAttachSeconds[7] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
    int fxAuraIndex[2] = {-1, -1};   // per-fighter aura card, match mode
    // One instance id per spawned card, monotonic for the whole run: two hits in the
    // same tick are two instances and neither can retire the other (game/fx_cards.h).
    uint32_t fxNextInstance = 1;
    game::FxCardTally fxTally;       // cumulative spawn/drop/expire/kill counts
    uint64_t fxBadEffect = 0;        // impact ids the install ships no descriptor for
    uint64_t fxShotCards = 0;        // live-shot card refreshes (the in-flight visual)
    size_t   fxPeakLive = 0;         // high-water mark of the live card set (bounded)
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
    // Live combat audio (issue #16). The sink below adapts this App's battle engine and its
    // lazy sample cache to fnd::audio::CombatAudio, which owns the policy: the recovered
    // event -> voice/SE resolution, one voice channel per fighter, event identity and
    // de-duplication, suspend/resume and per-match cleanup. `combatTick` is the fixed
    // simulation tick the events are stamped with (the same clock the economy counts on).
    struct CombatSink;
    struct CombatEventSource;
    std::unique_ptr<CombatSink>   combatSink;
    std::unique_ptr<fnd::audio::CombatAudio> combatAudio;
    std::unordered_map<std::string, fnd::audio::SfxHandle> combatSamples;  // stem -> handle
    bool                         combatMatchStarted = false;
    uint32_t                     combatTick = 0;
    uint64_t                     combatEvents = 0, combatVoicePlays = 0, combatSePlays = 0;
    ui::HudState                 versusHud;

    double   startTime = 0.0;
    double   lastTime = 0.0;
    double   deltaSum = 0.0;
    double   deltaMin = 1e30;
    double   deltaMax = 0.0;
    uint64_t frames = 0;
    uint64_t logicTicks = 0;
    gameplay::FixedStep logicClock;
    fnd::input::TickInput pendingInput[4];
    fnd::input::PlayerState tickInput[4], scriptInput;
    game::FighterPose previousFighter[4];
    float matchAlpha = 1.f;
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

static bool historicalMatchCapture(const App& app) {
    return !app.frontendMatch &&
           (!app.opts.out.empty() || !app.opts.script.empty() || !app.opts.script2.empty());
}

// --- persisted user settings (issue #19) ------------------------------------------
// The config file is read and written ONLY on a plain interactive frontend run. Every
// capture, replay or bounded run is a verification path: --match, --versus, --hud-test,
// --out/--headless captures and the asset viewers must produce the same frames and the
// same traces whether or not the user has a config file, so they neither read it nor
// write it. --screen=<menu> without a capture is interactive and does use it.
static bool usesUserConfig(const Options& o) {
    return o.frames == 0 && o.out.empty() && !o.headless && !o.match && !o.versus &&
           !o.hudTest && !o.list && !o.audioTest && !o.inputTest && o.anim < 0 &&
           o.model.empty() && o.stage.empty() && o.character.empty() && o.effect.empty();
}

// Load before anything the frontend builds: the volumes and bindings are live state, so
// they are in place before the first screen, and the display preference is applied later
// (initScreens owns the resolution list). A malformed file, an unsupported version or an
// unreadable directory all land here as "keep the defaults" plus a printed reason.
static void loadUserSettings(App& app) {
    app.settingsPath = settings::defaultConfigPath();
    if (app.settingsPath.empty()) {
        std::printf("[settings] no $XDG_CONFIG_HOME or $HOME: running with defaults, "
                    "nothing will be written\n");
        return;
    }
    settings::LoadReport report;
    const bool loaded = settings::load(app.settingsPath, app.userSettings, report);
    for (const std::string& message : report.messages)
        std::printf("[settings] %s\n", message.c_str());
    ui::applyUserSettings(ui::frontendSettings(), app.userSettings);
    app.settingsActive = true;
    std::printf("[settings] %s: %s\n", app.settingsPath.c_str(),
                loaded ? "loaded" : "using defaults");
}

// The display half of the document, applied once the frontend has built the resolution
// list and installed the SDL callbacks. An unavailable size falls back to desktop (index
// 0) exactly like the Options screen's own cycle, so moving to a display that does not
// offer the stored mode cannot fail the launch.
static void applyPersistedDisplay(App& app) {
    if (!app.settingsActive) return;
    auto& settings = ui::frontendSettings();
    if (!settings.resolutionAvailable) return;   // headless/web: no modes to choose from
    std::vector<settings::DisplaySize> available;
    available.reserve(settings.resolutions.size());
    for (const ui::DisplayResolution& size : settings.resolutions)
        available.push_back({size.width, size.height});
    const int wanted = settings::chooseResolutionIndex(available, app.userSettings.resolution);
    if (app.userSettings.resolution != settings::DisplaySize{})
        std::printf("[settings] resolution %dx%d (%s)\n", app.userSettings.resolution.width,
                    app.userSettings.resolution.height,
                    wanted == 0 ? "not offered by this display, using desktop" : "restored");
    settings.resolutionIndex = wanted;
    settings.resolutionChoice = {app.userSettings.resolution.width, app.userSettings.resolution.height};
    if (app.userSettings.fullscreen) {
        settings.fullscreen = true;
        if (settings.applyFullscreen) settings.applyFullscreen(true);
        if (!settings.fullscreen)
            std::printf("[settings] fullscreen unavailable: staying windowed\n");
    } else if (wanted != 0) {
        if (!settings.applyResolution(settings.resolutions[static_cast<size_t>(wanted)]) &&
            !settings.applyResolution(settings.resolutions[0])) {
            settings.resolutionIndex = 0;
            std::printf("[settings] resolution unavailable: falling back to desktop\n");
        }
    }
}

static void flushUserSettings(App& app) {
    if (!app.settingsActive || !app.settingsDirty) return;
    std::string error;
    if (settings::save(app.settingsPath, app.userSettings, error)) {
        app.settingsDirty = false;
        app.settingsSaveReported = false;
        std::printf("[settings] saved %s\n", app.settingsPath.c_str());
        return;
    }
    // Keep the dirty flag — a later attempt may succeed — but report once and back off,
    // so an unwritable directory cannot turn into a per-frame retry storm. Nothing is
    // written anywhere else: there is no fallback into the working directory.
    if (!app.settingsSaveReported) {
        app.settingsSaveReported = true;
        std::printf("[settings] cannot save: %s\n", error.c_str());
    }
}

// The pad identity is device state, not UI state: refresh it from the backend, then let
// the comparison below notice it. A disconnected pad keeps the identity it had, which is
// what keeps its bindings on the same player across a replug.
static void pollUserSettings(App& app, double now) {
    if (!app.settingsActive) return;
    if (app.matchInputReady) {
        for (int player = 0; player < fnd::input::kMaxPlayers; ++player) {
            const std::string guid = app.matchInput.gamepad_guid(player);
            if (guid.empty()) continue;
            app.userSettings.padGuid[static_cast<size_t>(player)] = guid;
            app.userSettings.padName[static_cast<size_t>(player)] = app.matchInput.gamepad_name(player);
        }
    }
    settings::UserSettings current = ui::toUserSettings(ui::frontendSettings());
    current.padGuid = app.userSettings.padGuid;
    current.padName = app.userSettings.padName;
    if (current != app.userSettings) {
        app.userSettings = current;
        app.settingsDirty = true;
        app.settingsDirtyAt = now;
    }
    if (!app.settingsDirty) return;
    // Write when the user has stopped changing things: leaving the two config screens, or
    // a pause after the last change (which also covers a quit that never reaches the
    // shutdown flush). Keeps a slider drag from writing the file on every step.
    const bool inConfigScreen = app.screensMode &&
        (app.screens.current() == ui::ScreenId::Options ||
         app.screens.current() == ui::ScreenId::KeyConfig);
    if (inConfigScreen && now - app.settingsDirtyAt < 2.0) return;
    if (now < app.settingsNextSaveAt) return;
    flushUserSettings(app);
    if (app.settingsDirty) app.settingsNextSaveAt = now + 5.0;   // failed: try again later
}

// Defined beside the media helpers further down; the pause cue loads through it.
static fnd::audio::SfxHandle loadSoundAsset(fnd::audio::Sdl3Engine& engine, const std::string& path);
// Defined with the match setup further down; the standalone rematch rebuilds through it.
static bool initMatch(App& app);

// --- battle pause (issue #15) ------------------------------------------------------
// The freeze itself is recovered: the original's pause flag scene+0x4430 gates its whole
// battle update (FUN_00634f60 @0x635093-0x6350aa skips the frame counter and every
// fighter/economy/camera step) and is toggled from the per-fighter pause action while the
// live battle phase runs (@0x634fb3-0x635006, playing system SE 0x11). What the port adds
// is the readable four-row menu, its captions and the leave-battle actions — see
// gameplay/battle_pause.h for the full provenance and docs/PAUSE.md for the policy.

// Pause is a live-battle feature of the interactive frontend only. Every capture and
// replay path keeps its historical behaviour — --match, --versus, --hud-test,
// --screen=battle captures, --out/--headless runs and bounded --frames runs never enter
// the pause state — so their frames and traces are identical whether or not a pause key is
// bound. Same shape as #19's usesUserConfig, for the same reason.
static bool battlePauseAvailable(const App& app) {
    return app.matchMode && app.opts.out.empty() && !app.opts.headless && app.opts.frames == 0;
}

// The controller slot that drives a frontend panel, or -1 for COM. The pause edge and the
// menu read the controllers that actually own a fighter, not every open pad.
static int panelController(const App& app, int panel) {
    const int controller = app.frontend.slots[panel].controller;
    return (controller >= 0 && controller < 4) ? controller : -1;
}

// The controller slots whose pause edge counts: a front-end battle's fighters' controllers,
// or P1's device on the standalone --match path (the other live offline battle — its P2 is
// the dummy the DX9 scene passes, so there is no COM to fight). Fills `out` and returns how
// many slots there are.
static int battlePauseControllers(const App& app, int out[4]) {
    if (!app.frontendMatch) {
        out[0] = 0;
        return app.matchInputReady ? 1 : 0;
    }
    int count = 0;
    for (int i = 0; i < app.battleLaunch.fighterCount && count < 4; ++i) {
        const int controller = panelController(app, app.battleLaunch.fighters[i].panel);
        if (controller >= 0) out[count++] = controller;
    }
    return count;
}

// The pause action edge, from the same controller slots the tactics gesture reads.
static bool battlePausePressed(const App& app) {
    int controllers[4] = {-1, -1, -1, -1};
    const int count = battlePauseControllers(app, controllers);
    for (int i = 0; i < count; ++i)
        if (app.tickInput[controllers[i]].just_pressed[fnd::input::Pause]) return true;
    return false;
}

// Combat SFX are the gameplay bus (channels 16..31, audio.h). While paused no new cue can
// start (the match does not step) and this stops the ones already ringing, so a pause
// cannot leave a hit cue playing over a frozen frame. BGM is deliberately left alone: the
// original's pause path plays SE 0x11 and never touches the music stream.
static void suspendCombatSfx(App& app) {
    int first = 0, last = 0;
    if (!fnd::audio::bus_range(fnd::audio::SfxBus::Sfx, first, last)) return;
    for (int channel = first; channel <= last; ++channel) app.versusAudio.stop(channel);
}

// The recovered pause cue: system SE 0x11 (FUN_0064aed0(0x11), FUN_00634f60 @0x634fe8),
// loaded from data/sysse/017 once and reused. A missing asset leaves the pause silent
// rather than failing it.
static void playPauseCue(App& app) {
    if (!app.pauseSoundTried) {
        app.pauseSoundTried = true;
        char stem[48];
        std::snprintf(stem, sizeof(stem), "data/sysse/%03d", 0x11);
        const std::string path = fnd::assets::assetSource().resolve(
            {std::string(stem) + ".cnv", std::string(stem) + ".wav"});
        app.pauseSound = loadSoundAsset(app.menuAudio, path);
    }
    if (app.pauseSound >= 0) app.menuAudio.play(app.pauseSound, fnd::audio::SfxBus::Ui);
}

static void enterBattlePause(App& app, const char* reason) {
    if (app.battlePaused) return;
    app.battlePaused = true;
    app.match.set_paused(true);   // the authoritative gate (gameplay/match.h)
    app.pauseMenu.rows = app.frontendMatch ? gameplay::kPauseRowsWithSelection
                                           : gameplay::kPauseRowsStandalone;
    app.pauseMenu.reset();
    suspendCombatSfx(app);
    playPauseCue(app);
    std::printf("[pause] paused (%s)\n", reason);
}

static void resumeBattle(App& app) {
    if (!app.battlePaused) return;
    app.battlePaused = false;
    app.match.set_paused(false);
    app.pauseMenu.reset();
    // Nothing is replayed: the paused ticks drained the device queues, so a button held
    // across the pause has no edge left to fire (the acceptance case) and the clock's
    // remainder is exactly where the pause stopped it.
    std::printf("[pause] resumed\n");
}

// Leaving a battle without a result: the same cleanup the round-over path performs, so a
// return to selection or a rematch cannot inherit the finished match. enterFrontendBattle
// is written to be re-entered (it clears weaponDefs/bulletParams, resets the counters and
// rebuilds the scene), which is what makes repeated cycles safe.
static void leaveBattleTo(App& app, ui::ScreenId next) {
    app.matchMode = false;
    app.frontendBattleReady = false;
    app.versusAudio.clear_music();
    app.screens.request(next);
    app.screensMode = true;
}

// A rematch must replay the battle that was just left. The front end rolls a random stage
// when none was chosen (frontend_launch.cpp:39, `state.stage == 0`), so the resolved stage
// is pinned back into the front-end state before the battle is re-entered; the characters,
// weapons and controllers already live there and are unchanged by a battle.
static void pinFrontendStage(App& app) {
    const size_t digits = app.opts.stage.find_first_of("0123456789");
    if (digits == std::string::npos) return;
    const int resolved = std::atoi(app.opts.stage.c_str() + digits);
    if (resolved < 1 || resolved > 26) return;
    app.frontend.stage = resolved % 10;
    app.frontend.variation = resolved / 10;
}

static SDL_AppResult applyPauseChoice(App& app, gameplay::PauseChoice choice) {
    switch (choice) {
        case gameplay::PauseChoice::None:
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::Resume:
            resumeBattle(app);
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::Rematch:
            resumeBattle(app);
            if (!app.frontendMatch) {
                // Standalone harness: rebuild the same match in place (same opts, same
                // scene), which is the whole of a rematch there.
                if (!initMatch(app)) return SDL_APP_FAILURE;
                std::printf("[pause] rematch\n");
                return SDL_APP_CONTINUE;
            }
            pinFrontendStage(app);
            // Through the VS intro, not straight back to Battle: ScreenStack::update only
            // swaps when the target differs from the current id, so re-requesting Battle
            // while the battle screen is current is a no-op (the factory would never run
            // and the old match would keep playing). VS re-enters the battle properly,
            // countdown included.
            leaveBattleTo(app, ui::ScreenId::VsIntro);
            std::printf("[pause] rematch\n");
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::ReturnToSelection:
            resumeBattle(app);
            leaveBattleTo(app, ui::ScreenId::Select);
            std::printf("[pause] return to selection\n");
            return SDL_APP_CONTINUE;
        case gameplay::PauseChoice::Quit:
            std::printf("[pause] quit\n");
            return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

// One paused tick: the match is not stepped at all, only the menu is read. Called from the
// tick loop in place of the battle tick, so the device queues are drained at the same
// cadence they would be during play — which is what keeps a held button from arriving as a
// stale edge on resume.
static SDL_AppResult tickBattlePause(App& app) {
    ++app.pauseScriptAdvance;   // keep the standalone script clock moving (see the member)
    bool up = false, down = false, confirm = false, cancel = false;
    int controllers[4] = {-1, -1, -1, -1};
    const int count = battlePauseControllers(app, controllers);
    for (int i = 0; i < count; ++i) {
        const fnd::input::PlayerState& in = app.tickInput[controllers[i]];
        // The pause action toggles back out, exactly like the original's key.
        if (in.just_pressed[fnd::input::Pause]) {
            resumeBattle(app);
            return SDL_APP_CONTINUE;
        }
        up = up || in.just_pressed[fnd::input::Up];
        down = down || in.just_pressed[fnd::input::Down];
        confirm = confirm || in.just_pressed[fnd::input::Jump];
        cancel = cancel || in.just_pressed[fnd::input::AttackA];
    }
    return applyPauseChoice(app, app.pauseMenu.update(up, down, confirm, cancel));
}

// A readable hint from the CURRENT bindings (P1 keyboard plus, when the pausing player has
// a pad, that pad's button names), so a rebind shows up here with no second table.
static std::string bindingHint(const App& app, fnd::input::Action action, int padPlayer) {
    const auto& settings = ui::frontendSettings();
    std::string out;
    const int key = settings.keyboard[action];
    if (key >= 0) {
        const char* name = SDL_GetScancodeName(static_cast<SDL_Scancode>(key));
        if (name && *name) out = name;
    }
    if (padPlayer >= 0 && padPlayer < 4) {
        const int button = settings.gamepad[static_cast<size_t>(padPlayer)][action];
        if (button >= 0) {
            const char* name = SDL_GetGamepadStringForButton(static_cast<SDL_GamepadButton>(button));
            if (name && *name) out += out.empty() ? name : std::string(" / ") + name;
        }
    }
    return out.empty() ? "unbound" : out;
}

// The pause overlay: a system menu drawn once over the frozen frame (not per view, so a
// split-screen match gets one readable menu instead of one per cell). Text goes through the
// shared D7 caption path; a caption that cannot load leaves the pause working but silent on
// screen rather than failing the frame.
static bool drawBattlePauseOverlay(App& app, WGPUCommandEncoder encoder, WGPUTextureView view) {
    if (!app.battlePaused || !app.uiReady) return true;
    int padPlayer = 0;
    if (app.frontendMatch) {
        const int controller = panelController(app, ui::kFrontendBattleSlots[0]);
        if (controller > 0) padPlayer = controller;
    }
    std::vector<std::string> lines;
    lines.push_back("PAUSED");
    for (int row = 0; row < app.pauseMenu.rows; ++row)
        lines.push_back(std::string(row == app.pauseMenu.row ? "> " : "  ") +
                        gameplay::pauseRowLabel(row, app.pauseMenu.rows));
    lines.push_back(bindingHint(app, fnd::input::Up, padPlayer) + "/" +
                    bindingHint(app, fnd::input::Down, padPlayer) + ": choose   " +
                    bindingHint(app, fnd::input::Jump, padPlayer) + ": confirm   " +
                    bindingHint(app, fnd::input::AttackA, padPlayer) + ": back   " +
                    bindingHint(app, fnd::input::Pause, padPlayer) + ": resume");
    std::string textError;
    if (!app.pauseText.load(app.uiRenderer, 16.f, textError) ||
        !app.pauseText.prepare(app.uiRenderer, lines, textError))
        return true;
    app.uiRenderer.beginFrame(app.sc.width, app.sc.height);
    // Dim the frozen frame so the menu is readable over any stage (the same solid fill the
    // screen stack's fade overlay uses).
    app.uiRenderer.pushSolid(ui::UiRect{0.f, 0.f, static_cast<float>(app.sc.width),
                                        static_cast<float>(app.sc.height)},
                             ui::UiColor{0.f, 0.f, 0.f, 0.55f});
    float y = static_cast<float>(app.sc.height) * 0.5f - 80.f;
    const float x = static_cast<float>(app.sc.width) * 0.5f - 150.f;
    for (size_t i = 0; i < lines.size(); ++i) {
        const bool title = i == 0;
        const bool footer = i + 1 == lines.size();
        const bool selected = !title && !footer && static_cast<int>(i) - 1 == app.pauseMenu.row;
        const ui::UiColor color = title      ? ui::UiColor{1.f, 1.f, 1.f, 1.f}
                                  : selected ? ui::UiColor{1.f, 0.8f, 0.3f, 1.f}
                                             : ui::UiColor{0.85f, 0.85f, 0.9f, 1.f};
        app.pauseText.draw(app.uiRenderer, lines[i].c_str(), x, y, footer ? 0.6f : 1.f, color, 1.f);
        y += footer ? 20.f : 22.f;
    }
    return app.uiRenderer.render(encoder, view, app.sc.format, app.error);
}

// Defined beside the HUD helpers below: initMatch fills the roster while it assembles the
// match, and enterFrontendBattle fills it earlier so the VS screen can draw it.
static void buildMatchRoster(App& app);

// --local-players' synthetic pads (see input/synthetic_pad.h): a controller with no
// attached device takes the deterministic pattern for THIS tick, applied after the device
// sample so a real pad always wins. Per tick and not per render on purpose — through the
// backend's event feed the absent device's cleared state is re-sampled every render, which
// degenerates the pattern into alternating one-tick taps whose density depends on the frame
// rate; a per-tick override keeps the run deterministic and pace-independent.
void driveSyntheticLocalPads(App& app) {
    const int humans = std::clamp(app.opts.localPlayers, 0, 4);
    if (humans <= 1) return;
    for (int controller = 1; controller < humans; ++controller) {
        if (app.matchInput.device(controller) != fnd::input::DeviceType::None) continue;
        fnd::input::SyntheticPadState pad;
        if (app.matchMode) {
            pad = fnd::input::syntheticPadState(controller, app.matchFrame, app.opts.lockTaps);
        } else if (app.screensMode) {
            // The selection screen's own clock: ticks since it appeared, so the panel walk
            // starts when the screen does and not at process start.
            if (app.screens.current() == ui::ScreenId::Select && !app.selectSeen) {
                app.selectSeen = true;
                app.selectEnterTick = app.logicTicks;
            }
            pad = fnd::input::syntheticMenuPadState(
                controller, app.selectSeen ? app.logicTicks - app.selectEnterTick : 0);
            // The VS presentation and the result beats advance on their own or on the run's
            // own script taps, so the pads never skip them: an evidence run then sees the
            // whole four-portrait assembly and the full victory -> quote -> report sequence
            // instead of a single faded frame (ui/screen_vs.h, ui/screen_result.h).
            if (app.screens.current() == ui::ScreenId::VsIntro ||
                app.screens.current() == ui::ScreenId::Result)
                pad.confirm = false;
        } else {
            continue;
        }
        fnd::input::PlayerState& state = app.tickInput[controller];
        state.down[fnd::input::Up] = pad.up;
        state.down[fnd::input::Down] = pad.down;
        state.down[fnd::input::Left] = pad.left;
        state.down[fnd::input::Right] = pad.right;
        state.down[fnd::input::AttackA] = pad.melee || pad.cancel;
        state.down[fnd::input::Shoot] = pad.shoot;
        state.down[fnd::input::Jump] = pad.jump || pad.confirm;
        state.down[fnd::input::Guard] = pad.guard;
        state.down[fnd::input::LockSwitch] = pad.lock;
        fnd::input::compute_edges(state);
    }
}

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

// ---------------------------------------------------------------------------
// Live combat audio (issue #16)
// ---------------------------------------------------------------------------
// The sink adapts the battle engine to fnd::audio::CombatAudio. Samples load lazily by stem
// (the same resolve rule the rest of the host uses: .cnv first, then .wav), and the handle
// cache keeps one decoded buffer per stem for the match's lifetime, so a repeated voice never
// re-decodes. SE plays auto-pick inside the SFX bus; voice plays are pinned to the fighter's
// own channel, which is what keeps two fighters from clobbering each other.
struct App::CombatSink final : fnd::audio::CombatAudioSink {
    explicit CombatSink(App& app) : app_(app) {}

    int play(const std::string& stem, fnd::audio::SfxBus bus, int channel) override {
        if (!app_.versusAudioOn) return -1;
        const fnd::audio::SfxHandle handle = handle_for(stem);
        if (handle < 0) return -1;
        fnd::audio::PlayRequest req;
        req.channel = channel;
        return app_.versusAudio.play(handle, bus, req);
    }
    void stop(int channel) override { app_.versusAudio.stop(channel); }
    void stop_bus(fnd::audio::SfxBus bus) override { app_.versusAudio.stop_bus(bus); }

    fnd::audio::SfxHandle handle_for(const std::string& stem) {
        const auto found = app_.combatSamples.find(stem);
        if (found != app_.combatSamples.end()) return found->second;
        const auto& source = fnd::assets::assetSource();
        const std::string path = source.resolve({stem + ".cnv", stem + ".wav"});
        const fnd::audio::SfxHandle handle = loadSoundAsset(app_.versusAudio, path);
        app_.combatSamples.emplace(stem, handle);   // misses are cached too: one probe each
        return handle;
    }
    // The original discovers an event's alternatives by probing NNN upward until the file is
    // missing (FUN_00431e70:78-151). Same rule here, with a small cap so a pathological
    // directory cannot walk forever.
    int probe_alternatives(const std::string& dir, fnd::audio::VoiceEvent event, bool b_dir) {
        int count = 0;
        for (int i = 0; i < 4; ++i) {
            const std::string stem = fnd::audio::voice_asset_stem(dir, event, b_dir, i);
            if (stem.empty()) break;
            if (handle_for(stem) < 0) break;
            ++count;
        }
        return count;
    }
    App& app_;
};

// The events this port emits (issue #16). Only these are probed at match start; the rest of
// the 40-name vocabulary stays available to fnd::audio::CombatAudio without a filesystem walk.
static constexpr fnd::audio::VoiceEvent kCombatVoiceEvents[] = {
    fnd::audio::VoiceEvent::BattleStart, fnd::audio::VoiceEvent::AttackA,
    fnd::audio::VoiceEvent::Fire,        fnd::audio::VoiceEvent::Damage,
    fnd::audio::VoiceEvent::DamageDown,  fnd::audio::VoiceEvent::Guard,
    fnd::audio::VoiceEvent::Guarded,     fnd::audio::VoiceEvent::AttackKO,
    fnd::audio::VoiceEvent::DamageKO,    fnd::audio::VoiceEvent::Revival,
    fnd::audio::VoiceEvent::Oyashiro,
};

// Per-fighter voice setup for a battle: the character's own voice directory (FUN_0041e180's
// data/voice/<name>) plus the alternatives of every event this port emits. The decoded-sample
// cache is kept ACROSS matches on purpose — the stems are the same ones next round, and the
// engine has no per-handle free — while the channels are released per match (end_match).
static void setupCombatVoices(App& app) {
    if (!app.combatAudio) return;
    const int count = app.match.config().fighterCount;
    app.combatAudio->begin_match(count);
    app.combatMatchStarted = false;
    app.combatTick = 0;
    for (int i = 0; i < count; ++i) {
        const int panel = app.battleLaunch.fighters[i].panel;
        const int character = app.frontend.slots[panel].character;
        const int weapon = app.frontend.slots[panel].weapon;
        if (character < 0 || character >= gameplay::kCharacterCount) continue;
        // PORT RULE: the B-persona voice directory. The install ships renaB/rikaB/chieB/
        // hanyuB and FUN_0041e180:196-206 selects them per character, but the port only has
        // the persona gate it recovered in #20 (character 0/4 with weapon slot 2); chie's and
        // hanyu's persona gates are NOT recovered, so they keep their base directory.
        const bool persona = (character == 0 || character == 4) && weapon == 2;
        std::string dir = std::string("data/voice/") + gameplay::kCharacterDirs[character];
        if (persona) dir += "B";
        app.combatAudio->set_fighter_voice(i, dir, persona);
        for (fnd::audio::VoiceEvent event : kCombatVoiceEvents) {
            const int alternatives = app.combatSink->probe_alternatives(dir, event, persona);
            app.combatAudio->set_voice_alternatives(i, event, alternatives);
            if (app.opts.combatAudioLog && alternatives > 0)
                std::printf("[combat-audio] fighter %d panel %d %s -> %s/%s%s alternatives=%d\n",
                            i, panel, gameplay::kCharacterDirs[character], dir.c_str(),
                            fnd::audio::voice_event_name(event),
                            fnd::audio::voice_event_b_dir(event) && persona ? "_B" : "",
                            alternatives);
        }
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
// Loads and parses one weapon's data/item/NNN.dat into app.weaponDefs[fighter].
// FUN_00433eb0 builds the path as "data/item/%03d.dat" from the item id the selection
// data carries; the parse itself is gameplay::WeaponDefinition::parse, transcribed from
// that reader. Returns false only when the file is missing or short, which is a hard
// error: a selected weapon with no definition would silently fight with shared tuning.
static bool loadWeaponDefinition(App& app, int fighter, int itemId, std::string& error) {
    char path[64];
    std::snprintf(path, sizeof(path), "data/item/%03d.dat", itemId);
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(path, bytes)) {
        error = std::string("cannot read ") + path;
        return false;
    }
    auto definition = std::make_unique<gameplay::WeaponDefinition>();
    std::string parseError;
    if (!definition->parse(itemId, bytes.data(), bytes.size(), parseError)) {
        error = std::string(path) + ": " + parseError;
        return false;
    }
    if (static_cast<int>(app.weaponDefs.size()) <= fighter)
        app.weaponDefs.resize(static_cast<size_t>(fighter) + 1);
    app.weaponDefs[static_cast<size_t>(fighter)] = std::move(definition);
    return true;
}

// Character directory basename for a "base/name[:costume]"-style spec
// ("data/rena:2" → "rena"). A ":digits" tail is the costume selector
// (splitSuffix above); anything else is path text and must not be cut.
static std::string charDirForSpec(const std::string& spec) {
    std::string path = spec;
    const size_t colon = path.find_last_of(':');
    if (colon != std::string::npos && colon + 1 < path.size() &&
        std::isdigit((unsigned char)path[colon + 1]))
        path = path.substr(0, colon);
    const size_t slash = path.find_last_of("/\\");
    return slash == std::string::npos ? path : path.substr(slash + 1);
}

// The item's first NON-EMPTY attachment mesh. The original walks every slot and loads
// each slot whose 30-byte name is non-empty, skipping the empty ones (FUN_00433eb0:90-116,
// the `if (local_140[0] != '\0')` guard at :111), so a mesh that lives in a later slot IS
// the item's mesh and an item whose every slot is empty simply has none to draw.
// False means the item file itself is missing or unparseable — a real error.
static bool readItemMesh(int itemId, std::string& mesh) {
    char path[64];
    std::snprintf(path, sizeof(path), "data/item/%03d.dat", itemId);
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(path, bytes)) return false;
    gameplay::WeaponDefinition item;
    std::string parseError;
    if (!item.parse(itemId, bytes.data(), bytes.size(), parseError)) return false;
    mesh.clear();
    for (int slot = 0; slot < item.slotCount; ++slot) {
        if (!item.slots[slot].meshName.empty()) {
            mesh = item.slots[slot].meshName;
            break;
        }
    }
    return true;
}

// Resolves a standalone fighter's weapon to (meshSpec, itemId) for one
// character directory and explicit spec (possibly empty):
//   empty spec      → the character's slot-0 legal weapon, mesh and id together;
//   data/bullet/NNN → item id NNN (the bullet directory number IS the item id);
//   anything else   → the spec's basename matched against the character's own
//     items' meshes (bounded: at most 3 small files per character).
// False means no join exists — unknown character, unreadable item, or a mesh no roster
// item ships. An item that parses but ships no mesh at all is a JOIN with an empty mesh:
// the fighter is armed with that item (its move table, bullets and damage) and has no
// attachment to draw, which is the original's own behaviour (FUN_00433eb0:111).
// Which NN.dat the original pairs with the weapon is still open (issue #26),
// so this joins mesh↔item only, never NN↔weapon.
static bool resolveFighterWeapon(const std::string& charDir,
                                 const std::string& explicitSpec, std::string& meshSpec,
                                 int& itemId) {
    const int character = gameplay::characterIndexForDir(charDir);
    if (character < 0) return false;
    if (explicitSpec.empty()) {
        itemId = gameplay::kWeaponIds[character][0];
        std::string mesh;
        if (!readItemMesh(itemId, mesh)) return false;
        meshSpec = mesh.empty() ? "" : std::string("data/item/") + mesh;
        return true;
    }
    std::string path;
    int slot = 0;
    splitSuffix(explicitSpec, path, slot);
    (void)slot;
    static const std::string bulletPrefix = "data/bullet/";
    if (path.compare(0, bulletPrefix.size(), bulletPrefix) == 0) {
        const std::string num = path.substr(bulletPrefix.size());
        if (!num.empty() && num.find_first_not_of("0123456789") == std::string::npos) {
            itemId = std::atoi(num.c_str());
            // Another character's item is not a join (a rena holding mion's gun
            // would play nata swings over gun data — the false-claim trap).
            if (gameplay::weaponSlotForItem(character, itemId) < 0) return false;
            meshSpec = explicitSpec;
            return true;
        }
        return false;
    }
    const size_t slash = path.find_last_of("/\\");
    const std::string base = slash == std::string::npos ? path : path.substr(slash + 1);
    for (int w = 0; w < gameplay::weaponCountForCharacter(character); ++w) {
        const int id = gameplay::kWeaponIds[character][w];
        std::string mesh;
        if (!readItemMesh(id, mesh) || mesh.empty() || mesh != base) continue;
        itemId = id;
        meshSpec = explicitSpec;
        return true;
    }
    return false;
}

// Attaches one fighter's weapon mesh: the explicit spec, or the character's
// slot-0 legal weapon when empty — never bare by omission (every attack is a
// weapon attack, issue #26). An unjoinable spec keeps the legacy bare fallback,
// loudly. Used by every versus/match assembly path below.
static void attachFighterWeapon(xm::Scene& scene, const std::string& label,
                                const std::string& charSpec,
                                const std::string& weaponSpec, const xm::Model* rig,
                                const xm::SceneOptions& sopt) {
    const int character =
        gameplay::characterIndexForDir(charDirForSpec(charSpec));
    std::string spec = weaponSpec;
    if (spec.empty()) {
        // A roster fighter without an explicit weapon gears up with slot 0, and
        // a roster fighter that cannot gear up fails the launch LOUDLY (rule 7:
        // a silent bare fighter is a false claim). Only unknown (custom)
        // characters keep the bare fallback, with a warning.
        if (character < 0) {
            std::printf("[weapons] %s (%s): unknown character, bare\n", label.c_str(),
                        charSpec.c_str());
            return;
        }
        std::string mesh;
        int id = 0;
        if (!resolveFighterWeapon(charDirForSpec(charSpec), spec, mesh, id))
            throw std::runtime_error(
                label + " " + charSpec +
                " has no weapon: slot-0 item " +
                std::to_string(gameplay::kWeaponIds[character][0]) +
                " unreadable — roster fighters must gear up");
        const std::string combo =
            gameplay::comboSlotLabel(character, gameplay::weaponSlotForItem(character, id));
        if (mesh.empty()) {
            // Parsed, and no slot ships a mesh: NOT a failure. The fighter is armed with
            // the item — its move table, bullets and damage are bound by the id — and the
            // original skips the attachment load for exactly this case (FUN_00433eb0:111).
            std::printf("[weapons] %s %s: item %03d, armed; the item ships no attachment mesh"
                        " to draw\n",
                        label.c_str(), combo.c_str(), id);
            return;
        }
        spec = mesh;
        std::printf("[weapons] %s %s: item %03d (%s)\n", label.c_str(), combo.c_str(), id,
                    mesh.c_str());
    }
    std::string path;
    int slot = 0;
    splitSuffix(spec, path, slot);
    xm::Scene weapon = xm::loadWeapon(path, slot, rig, sopt);
    for (auto& model : weapon.models) scene.models.push_back(std::move(model));
}

// The move table lives next to the rig's own model file: "<dir>/<char>[<costume>]/NN.X"
// loads alongside "<dir>/<char>/NN.dat" (the .dat is always in the unsuffixed
// directory and names the .X; see loadCharacter). Splits the rig source into the
// parent dir and the costume-stripped character dir; the .dat does not carry the
// _B.._F costume suffix (jump table at 0x41ef86).
static void splitRigDir(const std::string& rigSource, std::string& parent,
                        std::string& base) {
    const size_t slash = rigSource.find_last_of('/');
    const std::string dir = slash == std::string::npos ? "" : rigSource.substr(0, slash);
    const size_t dslash = dir.find_last_of('/');
    parent = dslash == std::string::npos ? "" : dir.substr(0, dslash);
    base = dslash == std::string::npos ? dir : dir.substr(dslash + 1);
    static const char* kSuffix[5] = {"_B", "_C", "_D", "_E", "_F"};
    for (const char* s : kSuffix) {
        const size_t n = std::strlen(s);
        if (base.size() > n && base.compare(base.size() - n, n, s) == 0) {
            base.erase(base.size() - n);
            break;
        }
    }
}

// Legacy rig-file path: the NN of the rig's own model file. Only used when no
// weapon slot is bound; the slot-indexed path below is the joined one.
static std::string movesPathForRig(const std::string& rigSource) {
    const size_t slash = rigSource.find_last_of('/');
    const std::string file =
        slash == std::string::npos ? rigSource : rigSource.substr(slash + 1);
    const size_t dot = file.find_last_of('.');
    const std::string stem = dot == std::string::npos ? file : file.substr(0, dot);
    if (stem.empty()) return "";
    std::string parent, base;
    splitRigDir(rigSource, parent, base);
    if (base.empty()) return "";
    return (parent.empty() ? base : parent + "/" + base) + "/" + stem + ".dat";
}

// Joined path: NN IS the weapon slot (each NN.dat carries its weapon id at file
// offset 0x114, agreeing with kWeaponIds 46/46). This is the one the battles use
// whenever the fighter's weapon is known.
static std::string movesPathForSlot(const std::string& rigSource, int slot) {
    if (slot < 0) return "";
    std::string parent, base;
    splitRigDir(rigSource, parent, base);
    if (base.empty()) return "";
    char nn[8];
    std::snprintf(nn, sizeof(nn), "%02d.dat", slot);
    return (parent.empty() ? base : parent + "/" + base) + "/" + nn;
}

// Loads and parses the fighter's data/<char>/NN.dat into app.moveDefs[fighter]:
// the weapon slot's file when the slot is known (expectedId is that weapon's
// item id, verified against the file's own 0x114 field), else the rig's own NN
// file. Hard mode (a bound weapon) reports through error for the caller to
// fail the launch; soft mode keeps the legacy shared swing with a log line,
// like the bullet parameters.
static bool loadCharacterMoves(App& app, int fighter, const std::string& rigSource,
                               int slot, int expectedId, bool hard, std::string& error) {
    std::string path = movesPathForSlot(rigSource, slot);
    if (path.empty()) path = movesPathForRig(rigSource);
    if (path.empty()) return false;
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(path, bytes)) {
        // Hard for a fighter whose weapon is bound (its table must exist);
        // soft otherwise, like the bullet parameters.
        if (hard)
            error = "fighter " + std::to_string(fighter) + ": no " + path +
                    " for the bound weapon";
        else
            std::printf("[moves] fighter %d: no %s, keeping the legacy swing\n", fighter,
                        path.c_str());
        return false;
    }
    auto moves = std::make_unique<gameplay::CharacterMoves>();
    std::string parseError;
    if (!moves->parse(bytes.data(), bytes.size(), parseError)) {
        if (hard)
            error = "fighter " + std::to_string(fighter) + ": " + path + ": " +
                    parseError;
        else
            std::printf("[moves] fighter %d: %s: %s, keeping the legacy swing\n",
                        fighter, path.c_str(), parseError.c_str());
        return false;
    }
    // The file identifies its own weapon (0x114); a mismatch against the bound
    // weapon means the NN↔weapon join broke. Loud in both modes, fatal in hard.
    std::string parent, base;
    splitRigDir(rigSource, parent, base);
    const int character = gameplay::characterIndexForDir(base);
    moves->set_character_index(character);
    if (expectedId > 0 && moves->weapon_id() != expectedId) {
        if (hard) {
            error = "fighter " + std::to_string(fighter) + ": " + path +
                    " carries weapon " + std::to_string(moves->weapon_id()) +
                    ", expected " + std::to_string(expectedId);
            return false;
        }
        std::printf("[moves] fighter %d: %s carries weapon %d, expected %d\n", fighter,
                    path.c_str(), moves->weapon_id(), expectedId);
    }
    const std::string combo =
        (character >= 0 && slot >= 0)
            ? " (" + gameplay::comboSlotLabel(character, slot) + ")" : "";
    std::printf("[moves] fighter %d%s: %s (%d moves)\n", fighter, combo.c_str(),
                path.c_str(), moves->count());
    if (static_cast<int>(app.moveDefs.size()) <= fighter)
        app.moveDefs.resize(static_cast<size_t>(fighter) + 1);
    app.moveDefs[static_cast<size_t>(fighter)] = std::move(moves);
    return true;
}

// Decodes the data/bullet/<weaponId>/<type>.dat parameters for one charge level out of a
// parsed weapon. FUN_00433eb0:152 hands each bullet entry's `type * 10 + status` to
// FUN_005f80c0, which builds "data/bullet/%03d/%03d.dat" with `type` as the file and
// passes `status` to FUN_005f8510 as the variant. A missing file is not fatal: the
// fighter keeps the shared provisional shot table and the coverage table records that
// combination's projectile parameters as unrecovered.
static bool loadBulletParameter(const App& app, int fighter, int level,
                                const gameplay::WeaponDefinition& weapon,
                                std::unique_ptr<gameplay::BulletParameter>& out) {
    const gameplay::MagazineDefinition& mag = weapon.magazineForChargeLevel(level);
    // Deterministic tier -> bullet choice, matching Fighter::shot_count's rule.
    const int wantMagazine = mag.chargeLevel - 1;
    const gameplay::BulletDefinition* best = nullptr;
    for (int i = 0; i < weapon.bulletCount; ++i) {
        const gameplay::BulletDefinition& b = weapon.bullets[i];
        if (b.magazine != wantMagazine) continue;
        if (!best || b.type < best->type) best = &b;
    }
    if (!best) return false;
    char path[64];
    std::snprintf(path, sizeof(path), "data/bullet/%03d/%03d.dat", weapon.id, best->type);
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(path, bytes)) return false;
    auto parameter = std::make_unique<gameplay::BulletParameter>();
    std::string err;
    if (!gameplay::parseBulletParameter(bytes.data(), bytes.size(), best->status,
                                        *parameter, err))
        return false;
    out = std::move(parameter);
    (void)fighter;
    return true;
}

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
            // The selected weapon's own combat definition (issue #9): magazine sizes,
            // charge thresholds, per-shot costs and volley counts come from the item
            // file, not from a shared table.
            if (i < static_cast<int>(app.weaponDefs.size()) && app.weaponDefs[i])
                config.weapon[i] = app.weaponDefs[i].get();
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
        // Standalone matches never selected weapons: resolve each fighter to its
        // character's legal combo (mesh attached at assembly; combat data here),
        // so bare-handed shared-tuning fights cannot happen by omission. The
        // frontend path arrives with weaponDefs filled and skips all of this.
        for (int i = 0; i < fighterCount; ++i) {
            if (i < static_cast<int>(app.weaponDefs.size()) && app.weaponDefs[i]) {
                config.weapon[i] = app.weaponDefs[i].get();
                continue;
            }
            std::string charSpec, explicitSpec;
            if (app.opts.battleFighterCount > 0 && i < 4) {
                charSpec = app.opts.battleCharacters[i];
                explicitSpec = app.opts.battleWeapons[i];
            } else if (i == 0) {
                charSpec = app.opts.character;
                explicitSpec = app.opts.weapon;
            } else if (i == 1) {
                charSpec = app.opts.enemy;
                explicitSpec = app.opts.enemyWeapon;
            } else {
                continue;
            }
            std::string mesh;
            int itemId = 0;
            const std::string charDir = charDirForSpec(charSpec);
            if (!resolveFighterWeapon(charDir, explicitSpec, mesh, itemId)) {
                // Same rule as the mesh stage: a roster fighter with no joinable
                // weapon fails loudly; only unknown characters fall back.
                if (gameplay::characterIndexForDir(charDir) >= 0) {
                    app.error = "fighter " + std::to_string(i) + " (" + charSpec +
                                "): weapon '" + explicitSpec +
                                "' joins no roster item — roster fighters must gear up";
                    return false;
                }
                std::printf("[weapons] fighter %d (%s): no weapon join, shared tuning\n",
                            i, charSpec.c_str());
                continue;
            }
            std::string error;
            if (!loadWeaponDefinition(app, i, itemId, error)) {
                app.error = error;
                return false;
            }
            config.weapon[i] = app.weaponDefs[i].get();
        }
        // Bullet parameters for the newly bound weapons (the frontend loads its
        // own in enterFrontendBattle; missing files keep the shared table).
        if (static_cast<int>(app.bulletParams.size()) < fighterCount)
            app.bulletParams.resize(static_cast<size_t>(fighterCount));
        for (int i = 0; i < fighterCount; ++i) {
            if (i >= static_cast<int>(app.weaponDefs.size()) || !app.weaponDefs[i])
                continue;
            for (int level = 1; level <= 2; ++level)
                loadBulletParameter(app, i, level, *app.weaponDefs[i],
                                    app.bulletParams[static_cast<size_t>(i)]
                                                  [static_cast<size_t>(level - 1)]);
        }
    }

    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    for (int i = 0; i < fighterCount; ++i) {
        models[i] = &app.scene.models[rigs[i]].model;
        anims[i] = &app.controllers[rigs[i]];
        app.matchRig[i] = rigs[i];
        // Each fighter fights with its weapon slot's move table (NN = slot, id at
        // file 0x114 — not the rig's costume variant), on both the frontend and
        // the standalone paths. Without a bound weapon the rig's own NN file
        // stands in; a missing table keeps the legacy shared swing.
        const std::string& rigSource = app.scene.models[rigs[i]].source;
        std::string parent, base;
        splitRigDir(rigSource, parent, base);
        int slot = -1, expectedId = -1;
        if (config.weapon[i]) {
            expectedId = config.weapon[i]->id;
            slot = gameplay::weaponSlotForItem(gameplay::characterIndexForDir(base),
                                               expectedId);
        }
        std::string movesError;
        if (!loadCharacterMoves(app, i, rigSource, slot, expectedId, expectedId > 0,
                                movesError)) {
            // A fighter whose weapon is bound must have its table; anything else
            // keeps the legacy swing.
            if (expectedId > 0) {
                app.error = movesError;
                return false;
            }
            continue;
        }
        if (i < static_cast<int>(app.moveDefs.size()) && app.moveDefs[i])
            config.moves[i] = app.moveDefs[i].get();
    }

    // Standalone --match captures/scripts are the historical unclamped trace path:
    // their positions and camera samples remain comparable to the banked recipes.
    // Interactive --match and front-end battles use collision.x movement/ground
    // queries; no collision model keeps the existing open-field fallback.
    const game::physics::MovementCollision* movement =
        historicalMatchCapture(app) || app.movementCollision.empty()
            ? nullptr : &app.movementCollision;
    const xm::Model* tamaMesh = app.projectileCollisionMesh;
    app.match.reset(config, models, anims, tamaMesh,
                    tamaMesh ? &app.projectileCollisionIndex : nullptr, movement);
    // The roster in panel order, with each entry linked to its MatchConfig index (issue #13).
    buildMatchRoster(app);
    // The earned-title counters are per ROUND (the original clears the record with the round):
    // a repeated round must not inherit the previous one's hits.
    for (auto& hits : app.titleHits) hits = App::TitleHits{};
    // Hand each fighter its recovered projectile parameters. Match::reset has already
    // bound the weapon (MatchConfig::weapon), which sized the magazines.
    for (int i = 0; i < fighterCount; ++i)
        for (int level = 1; level <= 2; ++level)
            if (i < static_cast<int>(app.bulletParams.size()))
                app.match.fighter(i).set_bullet_parameter(
                    level, app.bulletParams[static_cast<size_t>(i)]
                               [static_cast<size_t>(level - 1)].get());
    // Bind pose on request: the DX9 reference renders no animation (its d3dx9 under
    // Wine hands back no controller), so this is what makes a gate frame comparable.
    if (app.opts.noAnim) {
        for (int i = 0; i < fighterCount; ++i) app.match.fighter(i).set_animate(false);
        std::printf("match anim   : off (bind pose)\n");
    }
    // Fresh COM decision state for this match: one RNG stream per fighter index, derived
    // from the one match seed, so the whole match replays from that seed alone (issue #14).
    for (int i = 0; i < 4; ++i)
        app.botBrains[i].reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, i));
    app.tacticReadout.reset();
    std::printf("match        : %d fighters, movement/ground=%s, projectile=%s\n",
                fighterCount, movement && !movement->empty() ? "loaded" : "disabled",
                tamaMesh ? "loaded" : "missing");

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
    // Views exist per HUMAN CONTROLLER (issue #12), keyed exactly as FUN_006396f0 keys
    // its per-view context: a controller with no human owns no view, and COM fighters
    // therefore never take one. The standalone --match path is the historical single
    // view on controller 0; FUN_0040d130:115-119 covers the same no-human case by
    // forcing one view on controller 0.
    int controllerOfFighter[4] = {-1, -1, -1, -1};
    if (app.frontendMatch) {
        for (int i = 0; i < fighterCount; ++i) {
            const int panel = app.battleLaunch.fighters[i].panel;
            const int controller = app.frontend.slots[panel].controller;
            controllerOfFighter[i] = (controller >= 0 && controller < 4) ? controller : -1;
        }
    } else {
        controllerOfFighter[0] = 0;
    }
    game::HumanView viewList[game::kMaxHumanViews];
    app.matchViewCount = game::buildHumanViews(controllerOfFighter, fighterCount, viewList);
    std::vector<gameplay::CameraTarget*> cameraPool;
    for (int i = 0; i < app.match.config().fighterCount; ++i)
        cameraPool.push_back(&app.arenaTargets[i]);
    for (int v = 0; v < game::kMaxHumanViews; ++v) {
        game::MatchView& view = app.matchViews[v];
        view = game::MatchView{};
        if (v >= app.matchViewCount) continue;
        view.controller = viewList[v].controller;
        view.fighter = viewList[v].fighter;
        view.followed = viewList[v].fighter;
        // The camera starts pristine: eye (0,0,0), converging at 10% per update exactly
        // like the reference's ArenaCamera (gameplay/arena_camera.cpp). That seed is what
        // makes the first trace line comparable — the DX9's own frame-1 eye is one 10%
        // step from the origin, not the converged position.
        view.camera = gameplay::ArenaCamera{};
        view.camera.set_target_pool(cameraPool);
        view.camera.set_active_target(view.followed);
        view.previousEye = view.camera.eye();
        view.previousTarget = view.camera.target();
    }
    for (int i = 0; i < fighterCount; ++i) app.previousFighter[i] = app.match.fighter(i).pose();
    return true;
}

static glm::vec3 matchRenderPosition(const App& app, int fighter) {
    return glm::mix(app.previousFighter[fighter].position,
                    app.match.fighter(fighter).position(), app.matchAlpha);
}

static glm::mat4 matchRenderMatrix(const App& app, int fighter) {
    if (app.matchAlpha == 1.f) return app.match.fighter(fighter).modelMatrix();
    const float previous = app.previousFighter[fighter].facingYaw;
    const float current = app.match.fighter(fighter).facing_yaw();
    const float yaw = previous + std::remainder(current - previous, glm::two_pi<float>()) * app.matchAlpha;
    // FUN_00420b30: the authored rig faces -Z; retain Fighter::modelMatrix's half turn.
    return glm::translate(glm::mat4(1.f), matchRenderPosition(app, fighter)) *
        glm::rotate(glm::mat4(1.f), yaw + glm::pi<float>(), glm::vec3(0.f,1.f,0.f));
}

// The launch roster (issue #13): the front end's four slots in panel order, or the
// standalone --match pair (fighters 0/1 on panels 0/1, the historical recipe). `fighter`
// links a roster entry to its MatchConfig index, which is a different index space.
static void buildMatchRoster(App& app) {
    if (app.frontendMatch) {
        app.participantCount =
            ui::buildParticipants(app.frontend.slots.data(), app.participants);
        for (int i = 0; i < app.participantCount; ++i)
            for (int j = 0; j < app.battleLaunch.fighterCount; ++j)
                if (app.battleLaunch.fighters[j].panel == app.participants[i].panel)
                    app.participants[i].fighter = j;
        return;
    }
    // Standalone: two fighters on panels 0 and 1, controller 0 on the device/script and COM
    // on the dummy opponent. The character index is resolved from the same spec the scene
    // assembly used, so the HUD's combo label matches the rig that was loaded.
    app.participantCount = app.match.config().fighterCount < 2 ? app.match.config().fighterCount : 2;
    for (int i = 0; i < app.participantCount; ++i) {
        ui::Participant& p = app.participants[i];
        p = ui::Participant{};
        p.panel = i;
        p.team = i;
        const std::string& spec = i == 0 ? app.opts.character : app.opts.enemy;
        p.character = gameplay::characterIndexForDir(charDirForSpec(spec));
        p.controller = i == 0 ? 0 : 4;
        p.fighter = i;
    }
}

// One HUD entry per roster entry: the participant's MatchConfig index, or -1 when the slot
// has no participant (a 1v1 fills entries 0 and 1, a 2v2 all four).
static int hudEntryFighter(const App& app, int entry) {
    if (entry < 0 || entry >= app.participantCount) return -1;
    return app.participants[entry].fighter;
}

// Projects every active participant's markers through one view's camera into its HUD
// (FUN_00643230 projects each fighter's ring and com bar through the same camera and viewport
// the frame uses — here, through this view's), and resolves each one's off-screen alert edge.
// Two callers: the frame path, with the interpolated camera the scene pass draws with, and the
// --local-players evidence report, which needs real marker numbers on its own frame size.
static void projectViewHud(const App& app, const float viewProj[16], float width, float height,
                           ui::HudState& hud) {
    for (int i = 0; i < ui::kHudFighterCount; ++i) {
        const int fighterIndex = hudEntryFighter(app, i);
        if (fighterIndex < 0) continue;
        const glm::vec3 position = matchRenderPosition(app, fighterIndex);
        game::projectFighterHud(viewProj, position.x, position.y, position.z, hud.fighters[i],
                                width, height);
        // An off-screen participant keeps a marker on the edge it left through. The original's
        // edge choice is not recovered (only the four marker positions, 0x643722-0x6437d0), so
        // this is a PORT RULE: the nearest edge of the view.
        hud.fighters[i].alertDir = ui::hudAlertDirection(hud.fighters[i], width, height);
    }
}

// One view as the frame renders it: the camera/cell the scene pass uses for that view and
// the HUD frame drawn over it. Built per frame from the match's per-view state, so a view's
// camera, markers and values all come from the same controller.
struct FrameView {
    // The scene/prims camera. Its rect is left empty for a single-view frame — the whole
    // target — so that frame takes the historical render path with no viewport calls at all.
    render::ViewCamera camera;
    game::ViewRect     cell;   // the cell geometry the HUD pass and the report use
    ui::HudState       hud;
};

// Fills `out` with this frame's views: the cell each one occupies (game/view_layout.h's
// recovered FUN_006396f0 geometry), the camera pose for it — interpolated for presentation,
// or the exact camera while capturing, exactly as the single-view path did — and that view's
// HUD with its markers projected through its own view-projection (D8). Always at least one
// entry, so a single-view frame takes the historical render path with one cell covering the
// target.
static void buildFrameViews(App& app, uint32_t width, uint32_t height,
                            std::vector<FrameView>& out) {
    out.clear();
    const game::SplitLayout layout = game::splitLayoutFor(app.matchViewCount);
    const bool capturing = !app.opts.out.empty();
    for (int v = 0; v < app.matchViewCount; ++v) {
        const game::MatchView& view = app.matchViews[v];
        if (!view.active()) continue;
        const game::ViewRect rect = game::viewCell(layout, v, width, height);
        if (rect.empty()) continue;
        FrameView frameView;
        frameView.cell = rect;
        frameView.camera.rect = app.matchViewCount > 1
            ? render::ViewportRect{rect.x, rect.y, rect.w, rect.h}
            : render::ViewportRect{};
        frameView.camera.eye = glm::mix(view.previousEye, view.camera.eye(), app.matchAlpha);
        const glm::vec3 target = glm::mix(view.previousTarget, view.camera.target(), app.matchAlpha);
        // matchAlpha is 1 while capturing (D9's historical one-update-per-frame recipes),
        // and the reference view is then the camera's own — lookAtLH cannot construct a
        // basis from coincident eye/aim, which happens while every target is dead.
        const glm::mat4 viewMatrix = capturing || frameView.camera.eye == target
            ? view.camera.view_matrix()
            : glm::lookAtLH(frameView.camera.eye, target, glm::vec3(0.f,1.f,0.f));
        // Each view uses its OWN cell aspect, which is D8's automatic-aspect rule applied
        // to a split screen; the original's cells were always 4:3 400x300.
        frameView.camera.viewProj =
            view.camera.proj_matrix((int)rect.w, (int)rect.h) * viewMatrix;
        frameView.hud = view.hud;
        const ui::BattleHudLayout hudLayout = ui::computeBattleHudLayout((int)rect.w, (int)rect.h);
        projectViewHud(app, &frameView.camera.viewProj[0][0], hudLayout.width, hudLayout.height,
                       frameView.hud);
        out.push_back(frameView);
    }
}

// Places each fighter's model from the live simulation. modelMatrix() is the
// reference's world matrix (translation + Y rotation, FUN_00420b30). A bone-attached
// weapon is a separate model, so its world transform is the rig's model matrix
// composed with the bone's model-space matrix — the same composition the versus path
// needs, which it got wrong (it used the bone matrix alone, so a weapon would have
// been placed at the origin instead of in the fighter's hand).
static void placeMatchFighters(App& app) {
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        for (int fighter = 0; fighter < app.match.config().fighterCount; ++fighter)
            if (i == app.matchRig[fighter]) {
                app.modelMatrices[i] = matchRenderMatrix(app, fighter);
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
    // Issue #17: an effect card is drawn per live instance, not as a base draw, so the
    // scene's draw count does not grow with the size of the effect table.
    sm.instancesOnly = true;
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
    // Issue #17: load the install's effect table instead of one hard-coded card.
    // FUN_0042eba0 loads 100 descriptors (data/effect/%03d.dat) into the manager at
    // scene+0x5210; the install ships 22. The lifetime is NOT in the descriptor file --
    // FUN_0042eec0 takes it from the model's own first animation, divided by 0.016 and
    // rounded to frames (0x42f412-0x42f423) -- so it is read here from the loaded model.
    int loaded = 0;
    for (int type = 0; type < game::kEffectSlots; ++type) {
        char rel[64];
        std::snprintf(rel, sizeof(rel), "/effect/%03d.dat", type);
        std::vector<uint8_t> dat;
        if (!fnd::assets::assetSource().read(dataDir + rel, dat)) continue;
        const game::EffectDescriptor desc = game::parseEffectDescriptor(dat);
        if (!desc.present) {
            std::fprintf(stderr, "[fx] %s: not an effect descriptor\n", rel);
            continue;
        }
        const std::string model = dataDir + "/effect/" + desc.modelPath;
        const int asset = addFxCard(app, model);
        float seconds = 0.f;
        if (asset >= 0) {
            const xm::Model& m = app.scene.models[(size_t)asset].model;
            if (!m.anims.empty() && m.ticksPerSecond > 0.f)
                seconds = m.anims[0].duration / m.ticksPerSecond;
        }
        app.fxCatalog.add(type, desc, asset, seconds);
        if (asset >= 0) ++loaded;
    }
    // FUN_00633ca0's attachment table: seven data/aura/%02d.x models, drawn on the
    // fighter's own matrices (FUN_004205e0). Their textures name the roles: 0/1/5 are
    // the three muzzle flashes, 2 the blue hit flash, 3 the burning aura, 4 a bucket.
    for (int slot = 0; slot < 7; ++slot) {
        char rel[32];
        std::snprintf(rel, sizeof(rel), "/aura/%02d.x", slot);
        app.fxAttach[slot] = addFxCard(app, dataDir + rel);
        if (app.fxAttach[slot] >= 0) {
            const xm::Model& m = app.scene.models[(size_t)app.fxAttach[slot]].model;
            if (!m.anims.empty() && m.ticksPerSecond > 0.f)
                app.fxAttachSeconds[slot] = m.anims[0].duration / m.ticksPerSecond;
        }
    }
    if (app.opts.match) {
        // The per-fighter aura follows the fighter's own model matrix (below), so it
        // needs one card per fighter slot even though both may name the same model.
        app.fxAuraIndex[0] = addFxCard(app, dataDir + "/aura/03.X");
        app.fxAuraIndex[1] = addFxCard(app, dataDir + "/aura/03.X");
    }
    std::printf("fx assets    : %d effect descriptor(s), 7 attachment model(s)\n", loaded);
}

// Drains the gameplay's event queue into the live card set. The spawn /
// kill-by-id / ttl-expiry rules live in game/fx_cards.h (unit-tested there);
// this only moves the drained events over and counts them.
static void updateFxCards(App& app, game::EffectEventQueue& q, uint64_t& events, float dt) {
    const std::vector<game::EffectEvent> ev = q.drain();
    events += ev.size();
    // The cap and the drop count live in game/fx_cards.h; the tally is cumulative so a
    // run's log can prove the population stayed bounded (issue #17).
    const game::FxCardTally t = game::updateLiveFxCards(app.liveFx, ev, dt);
    if (app.liveFx.size() > app.fxPeakLive) app.fxPeakLive = app.liveFx.size();
    app.fxTally.spawned += t.spawned;
    app.fxTally.dropped += t.dropped;
    app.fxTally.expired += t.expired;
    app.fxTally.killed  += t.killed;
}

// The instance-id base for live-shot cards: the pool slot index is the low half, so one
// card follows one shot for its whole flight. Kept far above the per-event instance
// counter's range so the two id spaces cannot collide (a shot's flight is a few hundred
// ticks, so the counter would need ~2^30 spawns to reach it).
inline constexpr uint32_t kFxShotCardId = 0x40000000u;

// Spawn one effect INSTANCE: a fresh id from the run's counter, the recovered lifetime
// of `effectId` from the catalog, and the asset its descriptor loaded into. Returns
// false when the install ships no such descriptor (the original leaves that table slot
// null too), so a bad id is visible in the caller's own accounting rather than silently
// drawing the wrong card.
static bool spawnEffect(App& app, game::EffectEventQueue& queue, int effectId,
                        const glm::vec3& at) {
    const game::EffectEntry* entry = app.fxCatalog.find(effectId);
    if (!entry || !entry->playable()) return false;
    const float ttl = (float)app.fxCatalog.lifetime_ticks(effectId, 64.f) / 64.f;
    queue.pushSpawn(app.fxNextInstance++, at, entry->asset, ttl);
    return true;
}

// One attachment-model card (FUN_00633ca0's table) at a world point, with the model's
// own animation as its lifetime. Attachment slots are not descriptor ids: the original
// draws them on the fighter's matrices (FUN_004205e0), so they have no entry in
// data/effect/ and no manager instance.
static bool spawnAttachment(App& app, game::EffectEventQueue& queue, int slot,
                            const glm::vec3& at) {
    if (slot < 0 || slot >= 7 || app.fxAttach[slot] < 0) return false;
    const float ttl = app.fxAttachSeconds[slot] > 0.f ? app.fxAttachSeconds[slot] : 0.1f;
    queue.pushSpawn(app.fxNextInstance++, at, app.fxAttach[slot], ttl);
    return true;
}

// Per-frame placement of the live cards: every asset model is hidden with a zero
// matrix, then the live ones get theirs. The cards are unskinned and the Effect
// pass billboards them at render time (scene_renderer), so only the model matrix
// moves each frame; setModelMatrices uploads it at the end of the placement call
// that follows.
static void placeFxCards(App& app) {
    std::vector<render::SceneRenderer::EffectInstance> instances;
    instances.reserve(app.liveFx.size() + 4);
    if (!app.opts.debugPrims) {
        for (const game::LiveFxCard& c : app.liveFx) {
            if (c.asset < 0 || (size_t)c.asset >= app.scene.models.size()) continue;
            instances.push_back({c.asset, glm::translate(glm::mat4(1.f), c.position)});
        }
        // The aura is fighter state, not an event: it follows the fighter's own model
        // matrix in the fighter's local space. FUN_004205e0 draws it once per fighter
        // matrix (11 of them); the port keeps the single local-space placement the aura
        // cube used, which is the same transform without the per-bone repetition.
        for (int i = 0; i < 2; ++i) {
            if (app.fxAuraIndex[i] < 0) continue;
            const gameplay::Fighter& f = app.match.fighter(i);
            if (!f.aura_active()) continue;
            instances.push_back({app.fxAuraIndex[i],
                                 matchRenderMatrix(app, i) *
                                     glm::translate(glm::mat4(1.f), f.aura_center_local())});
        }
    }
    app.renderer.setEffectInstances(instances);
}

// Issue #17's acceptance evidence: what the effect layer spawned, what the cap refused, and
// the high-water mark of the live set. `dropped` must stay 0 unless the population really
// reached the cap; `peak` is the number that has to stay bounded across a long 2v2.
static void printFxSummary(const App& app) {
    std::printf("fx cards     : events=%llu spawned=%llu dropped=%llu expired=%llu "
                "killed=%llu peak=%zu/%zu, liveShots=%llu badEffectId=%llu, "
                "effectDrawsAtExit=%d\n",
                (unsigned long long)app.matchFxEvents,
                (unsigned long long)app.fxTally.spawned,
                (unsigned long long)app.fxTally.dropped,
                (unsigned long long)app.fxTally.expired,
                (unsigned long long)app.fxTally.killed,
                app.fxPeakLive, game::kMaxLiveFxCards,
                (unsigned long long)app.fxShotCards,
                (unsigned long long)app.fxBadEffect,
                app.renderer.stats().effects);
}

// Issue #14's acceptance evidence, from the run's own counters: how each COM moved,
// what it asked for, every request the resource gates refused (a refused move that is not
// retried in a loop) and the bounded wall recovery. `blocked` counts probes whose wanted
// direction the stage refused; `stuck` the recoveries that fired. Printed at round over
// and again at the end of a capture run, so a match that never finishes still reports.
static void printComSummary(const App& app) {
    for (int i = 0; i < app.match.config().fighterCount; ++i) {
        const gameplay::BotStats& bs = app.botBrains[i].stats();
        if (bs.ticks == 0) continue;   // a human slot
        std::printf("match com %d : tactic=%s action=%s moved=%.0f, "
                    "melee=%llu blockedMelee=%llu shots=%llu fired=%llu "
                    "blockedShot=%llu, dash=%llu jump=%llu guard=%llu "
                    "evade=%llu hyper=%llu retarget=%llu, "
                    "wallTicks=%llu stuck=%llu turns=%llu\n",
                    i,
                    gameplay::bot_tactic_name(app.botBrains[i].tactic()),
                    gameplay::bot_action_name(app.botBrains[i].decision().action),
                    (double)bs.distanceMoved,
                    (unsigned long long)bs.meleePresses,
                    (unsigned long long)bs.meleeBlocked,
                    (unsigned long long)bs.shotsStarted,
                    (unsigned long long)bs.shotsFired,
                    (unsigned long long)bs.shotBlocked,
                    (unsigned long long)bs.dashStarts,
                    (unsigned long long)bs.jumps,
                    (unsigned long long)bs.guards,
                    (unsigned long long)bs.evades,
                    (unsigned long long)bs.hypers,
                    (unsigned long long)bs.retargets,
                    (unsigned long long)bs.blockedTicks,
                    (unsigned long long)bs.stuckRecoveries,
                    (unsigned long long)bs.directionChanges);
    }
}

// How long LockSwitch must be HELD, with no fresh tap, before the selection moves to an
// ally (input.h: "hold = aim ally"). PORT RULE: the hold itself is recovered
// (FUN_00421e30's 0xb4, re-pinned by FUN_0041f580:244), but the gesture length that
// raises it is not in the corpus, so this threshold only has to be long enough that a tap
// still physically held does not undo itself — a couple of fixed ticks.
static constexpr int kLockHoldTicks = 2;

// One fighter's HUD-side values (gameplay/hud_fill.h's HudFighterValues), sampled from the
// live fighter and the input that drives it. Split out of tickMatch because each view
// samples its OWN fighter and controller with the same rules (issue #12).
static void sampleHudFill(gameplay::HudFighterValues& out, const gameplay::Fighter& f,
                          const fnd::input::PlayerState* input) {
    out.hp = f.hp() * 100 / f.max_hp();
    out.alive = f.is_alive();
    out.mainWhole = f.main_whole();
    out.mainFrac = f.main_frac();
    out.reloadOk = f.reload_ok();
    out.chargeWhole = f.charge_whole();
    out.chargeFrac = f.charge_frac();
    out.shootHeld = input && input->down[fnd::input::Shoot];
    out.chargeHoldFrac = f.charge_hold_frac();
    switch (f.charge_tier()) {   // ShotTier -> HoldTier (scenes.cpp:847-851)
        case gameplay::ShotTier::Red:    out.chargeTier = game::HoldTier::Red; break;
        case gameplay::ShotTier::Yellow: out.chargeTier = game::HoldTier::Yellow; break;
        default:                         out.chargeTier = game::HoldTier::Idle; break;
    }
    const gameplay::HypermodeParams hp = gameplay::hypermode_params(f.hypermode());
    out.hyperName = hp.name;
    out.hyperGauge = f.hyper_gauge();
    out.hyperActive = f.hyper_active();
    out.hyperReady = f.hyper_ready();
    out.hyperSecondsLeft = f.hyper_seconds_left();
    out.hyperAura = game::GameRgb{(float)gameplay::rgbR(hp.aura) / 255.f,
                                  (float)gameplay::rgbG(hp.aura) / 255.f,
                                  (float)gameplay::rgbB(hp.aura) / 255.f};
    out.stamina = f.stamina();
    // The reference's contextual gate is the state, not airborne() (scenes.cpp:879-882).
    out.staminaVisible = f.state() == gameplay::FighterState::Run ||
                         f.state() == gameplay::FighterState::Guard ||
                         f.state() == gameplay::FighterState::Jump;
}

// One match frame: the reference's order lives in gameplay::Match::step; this adds
// what the scene added around it — tick inputs, the camera's target switch, the
// HUD values, the effect events and the debug cubes.
// ---------------------------------------------------------------------------
// Live combat audio dispatch (issue #16)
// ---------------------------------------------------------------------------
// Every event below is read from the MatchFrame the fixed 64 Hz step just produced, so the
// audio is a function of simulation state and not of what a render pass happened to see. Each
// event is stamped with that frame's tick and a per-tick sequence, which is the identity
// fnd::audio::CombatAudio de-duplicates on: the same frame replayed (a catch-up step, a
// rollback resimulation) carries the same ids and plays nothing twice.
// The adapter that lets the shared derivation read the live match (issue #16).
struct App::CombatEventSource final : fnd::audio::CombatEventSource {
    explicit CombatEventSource(const App& app) : app_(app) {}
    int fighter_count() const override { return app_.match.config().fighterCount; }
    bool alive(int fighter) const override {
        return fighter >= 0 && fighter < app_.match.config().fighterCount &&
               app_.match.fighter(fighter).is_alive();
    }
    const App& app_;
};

// The frame the simulation just produced, copied into the module's own view. Keeping the
// derivation in fnd::audio (and the copy here) is what lets the asset-backed match test
// exercise exactly the events the release path dispatches.
static fnd::audio::CombatFrameView combatFrameView(const gameplay::MatchFrame& f) {
    fnd::audio::CombatFrameView view;
    for (int i = 0; i < 4; ++i) {
        view.swing_started[i] = f.swingStarted[i];
        view.shot_fired[i]    = f.shotFired[i];
        view.hyper_started[i] = f.hyperStarted[i];
        view.guard_started[i] = f.guardStarted[i];
        view.respawned[i]     = f.respawned[i];
        view.blocked[i]       = f.blocked[i];
        view.melee_hit[i]     = f.meleeHit[i];
        view.melee_victim[i]  = f.meleeVictim[i];
        view.overkill_hits[i] = f.overkillHits[i];
    }
    view.shot_hit_count = f.shotHitCount < gameplay::MatchFrame::kMaxShotHits
                              ? f.shotHitCount : gameplay::MatchFrame::kMaxShotHits;
    for (int k = 0; k < view.shot_hit_count; ++k) {
        view.shot_hits[k].shooter = f.shotHits[k].shooter;
        view.shot_hits[k].victim  = f.shotHits[k].victim;
        view.shot_hits[k].blocked = f.shotHits[k].blocked;
    }
    return view;
}

// Every event below comes from the MatchFrame the fixed 64 Hz step just produced, so the audio
// is a function of simulation state and not of what a render pass happened to see. Each event
// is stamped with that frame's tick and a per-tick sequence, which is the identity
// fnd::audio::CombatAudio de-duplicates on: the same frame replayed (a catch-up step, a
// rollback resimulation) carries the same ids and plays nothing twice.
static void dispatchCombatAudio(App& app, const gameplay::MatchFrame& f) {
    if (!app.combatAudio) return;
    const uint32_t tick = (uint32_t)app.matchFrame;   // 1-based, same clock as the captures
    App::CombatEventSource source(app);
    const fnd::audio::CombatEventList list = fnd::audio::combat_events_for_frame(
        source, combatFrameView(f), tick, !app.combatMatchStarted);
    if (!app.combatMatchStarted && list.count > 0) app.combatMatchStarted = true;
    for (int i = 0; i < list.count; ++i) {
        const fnd::audio::CombatEvent& e = list.events[i];
        app.combatAudio->dispatch(e);
        ++app.combatEvents;
        if (app.opts.combatAudioLog) {
            // Evidence line: one per dispatched event, naming the file/SE the policy resolved
            // (empty voice = the event has no line, -1 = no evidenced SE id).
            const std::string& voice = app.combatAudio->last_voice_stem();
            std::printf("[combat-audio] tick %u %-12s fighter=%d source=%d%s -> voice=%s se=%d\n",
                        tick, fnd::audio::combat_event_name(e.kind), e.fighter, e.source,
                        e.shot ? " (shot)" : "",
                        voice.empty() ? "(none)" : voice.c_str(),
                        app.combatAudio->last_se_id());
        }
    }
}

// "Stop everything this match started" (issue #16's cleanup entry point, named for #15's
// leave path): releases the combat layer's voice channels and cuts the SFX bus. Null-safe, so
// a leave path can call it whether or not a battle ever built the layer.
static void stopCombatAudio(App& app) {
    if (app.combatAudio) app.combatAudio->end_match();
}

// The match-end evidence: what was dispatched, what played, and how many voice channels the
// layer still holds (issue #16's leak check). Called wherever the match ends.
static void reportCombatAudio(App& app) {
    if (!app.combatAudio) return;
    const auto& stats = app.combatAudio->stats();
    app.combatVoicePlays = (uint64_t)stats.voice_plays;
    app.combatSePlays = (uint64_t)stats.se_plays;
    if (!app.opts.combatAudioLog) return;
    std::printf("[combat-audio] match end: events=%llu voice=%d se=%d duplicates=%d "
                "suspended_drops=%d voice_missing=%d se_missing=%d channels_held=%d\n",
                (unsigned long long)app.combatEvents, stats.voice_plays, stats.se_plays,
                stats.duplicates, stats.suspended_drops, stats.voice_missing, stats.se_missing,
                app.combatAudio->claimed_channels());
    for (int k = 0; k < fnd::audio::kCombatEventKindCount; ++k)
        if (stats.dispatched[k] > 0)
            std::printf("[combat-audio]   %-12s %d\n",
                        fnd::audio::combat_event_name((fnd::audio::CombatEventKind)k),
                        stats.dispatched[k]);
}

static void tickMatch(App& app, double dt) {
    // The 15-tick switch pulse is not counted here: Match's lock table owns and decays
    // it (gameplay/target_lock.h, FUN_004201a0), so the HUD reads one source of truth.
    for (int i = 0; i < app.match.config().fighterCount; ++i)
        app.previousFighter[i] = app.match.fighter(i).pose();
    ++app.matchFrame;   // 1-based simulation tick, matching banked captures

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

    // Standalone --match: P1 is the live device (or its script override) and P2 the script
    // or dummy. A front-end match replaces both with the controller each fighter is
    // assigned to (issue #12), which is also what gives each view its own input.
    const fnd::input::PlayerState* p1 = nullptr;
    if (app.matchInputReady && !app.frontendMatch) p1 = &app.tickInput[0];

    // The viewer is the fighter on panel kFrontendBattleSlots[0] (1P). A PANEL index; the
    // lookup yields a FIGHTER index, and the controller slot is a third, distinct index
    // space (see gameplay/target_lock.h). Read before the step because the COM brains want
    // the leader's lock, and again below for the HUD.
    int viewerIndex = 0;
    if (app.frontendMatch)
        for (int j = 0; j < app.battleLaunch.fighterCount; ++j)
            if (app.battleLaunch.fighters[j].panel == ui::kFrontendBattleSlots[0]) {
                viewerIndex = j;
                break;
            }

    // The recovered tactics gesture: any human pressing Tactics cycles the team cell, which
    // FUN_0041f580:291-295 mirrors onto player 0's +0x310, and every COM reads that cell.
    // Keeping ONE cell is exactly what the mirroring produces.
    {
        bool pressed = false;
        if (app.frontendMatch) {
            for (int i = 0; i < app.battleLaunch.fighterCount && !pressed; ++i) {
                const int controller =
                    app.frontend.slots[app.battleLaunch.fighters[i].panel].controller;
                if (controller >= 0 && controller < 4)
                    pressed = app.tickInput[controller].just_pressed[fnd::input::Tactics];
            }
        } else if (p1) {
            pressed = p1->just_pressed[fnd::input::Tactics];
        }
        if (pressed) {
            const gameplay::BotTactic cell = app.tacticReadout.press();
            for (gameplay::BotBrain& brain : app.botBrains) brain.set_tactic(cell);
        }
        app.tacticReadout.tick();
    }

    const fnd::input::PlayerState* inputs[4] = {p1, p2, nullptr, nullptr};
    if (app.frontendMatch) {
        for (int i = 0; i < app.match.config().fighterCount; ++i) {
            const int panel = app.battleLaunch.fighters[i].panel;
            const int controller = app.frontend.slots[panel].controller;
            if (controller >= 0 && controller < 4) inputs[i] = &app.tickInput[controller];
            else {
                // COM. The decision state owns the target pick, the movement, the presses
                // and the retarget request; gameplay/bot_input.h turns that into this
                // fighter's input for the tick (issue #14).
                gameplay::BotContext bot;
                bot.match = &app.match;
                bot.fighterIndex = i;
                bot.leaderTarget = app.match.locked_target(viewerIndex);
                gameplay::updateBotInput(app.botBrains[i], bot, app.botInput[i],
                                         app.matchFrame);
                inputs[i] = &app.botInput[i];
            }
        }
    }
    const gameplay::MatchFrame f = app.match.step(inputs, dt);
    for (int i = 0; i < app.match.config().fighterCount; ++i)
        if (f.respawned[i]) app.previousFighter[i] = app.match.fighter(i).pose();
    if (app.versusAudioOn)
        app.versusBgmPushed += app.versusLoop.push_next(app.versusAudio, 1024);
    app.matchShots += (uint64_t)f.shotsSpawned;
    app.matchSparks += (uint64_t)f.muzzleSparks;
    for (int i = 0; i < app.match.config().fighterCount; ++i)
        if (f.meleeHit[i]) ++app.matchHits;
    // Live combat audio (issue #16): the frame just produced is the event source.
    dispatchCombatAudio(app, f);
    // The earned-title counters (issue #20). The original splits them the same way: the damage
    // functions credit the attacker's "to target/others" pair by whether the victim was its
    // lock (FUN_00639160), the hit functions credit the victim's "from target/others" pair by
    // whether the two held each other (FUN_00423000), and both count the attacker's hits on the
    // local player's fighter (FUN_00423000:22-25). Shot hits are NOT counted: the projectile
    // pool reports no victim, so the melee/shot comparisons stay among the unresolved
    // conditions (gameplay/result_title.h).
    {
        const int localFighter = app.matchViewCount > 0 ? app.matchViews[0].fighter : 0;
        for (int i = 0; i < app.match.config().fighterCount; ++i) {
            if (!f.meleeHit[i] || f.meleeVictim[i] < 0) continue;
            const int victim = f.meleeVictim[i];
            if (victim >= 4 || i >= 4) continue;
            if (app.match.locked_target(i) == victim) ++app.titleHits[i].toTarget;
            else ++app.titleHits[i].toOthers;
            if (app.match.locked_target(victim) == i) ++app.titleHits[victim].fromTarget;
            else ++app.titleHits[victim].fromOthers;
            if (victim == localFighter) ++app.titleHits[i].onLocalPlayer;
        }
    }

    // Combat effects (issue #17). Every card is one INSTANCE of one combat event: the
    // muzzle flash of a shot that was fired, the impact effect the shot carried, the
    // melee-hit card, the in-flight shot itself, and the burning aura's periodic puffs.
    // Each gets its own id, so simultaneous hits cannot retire each other's cards (the
    // old code kill-chained the previous hit's card on every new hit). Lifetimes are the
    // models' own animation durations, recovered through FUN_0042eec0; nothing here is a
    // fixed 12 s.
    for (int i = 0; i < app.match.config().fighterCount && i < 4; ++i) {
        // Muzzle flash: the recovered attachment models (FUN_00633ca0 slots 0/1/5 are the
        // three マズルフラッシュ cards, selected by the three attack-start methods
        // 0x421fe0/0x4220e0/0x422160). PORT RULE: which firing state owns which slot is
        // not established, so the shot tier picks them in that order.
        if (f.shotFired[i]) {
            const gameplay::ShotTier tier = app.match.fighter(i).last_shot_tier();
            const int slot = tier == gameplay::ShotTier::Tap      ? 0
                             : tier == gameplay::ShotTier::Yellow ? 1
                                                                  : 5;
            spawnAttachment(app, app.matchFx, slot, f.shotPoints[i]);
        }
        // Hypermode: the recovered burning aura is attachment slot 3 (炎上オーラ), and
        // FUN_0042e110 re-spawns effect 380 every 7 frames while the fighter is in the
        // downed/burning move family. The cadence is the simulation tick, not the render
        // rate, and the jitter is a deterministic function of (fighter, tick) — the
        // original's rand()%100 - 50 box around the fighter's position.
        if (app.match.fighter(i).aura_active() && app.matchFrame % 7 == 0) {
            const uint32_t h = (uint32_t)(app.matchFrame / 7) * 2654435761u +
                               (uint32_t)i * 40503u;
            const glm::vec3 at = app.match.fighter(i).position() +
                                 glm::vec3((float)(h % 100) - 50.f,
                                           (float)((h >> 8) % 60),
                                           (float)((h >> 16) % 100) - 50.f);
            spawnEffect(app, app.matchFx, 380, at);
        }
    }
    // Impact effects: the shot's own bullet record names the id (record +0x70 through
    // FUN_00637950:221-228 -> FUN_00435990 -> the manager's create), spawned at the
    // contact point the pool reported. A blocked hit still spawns in the original, so the
    // effect is not gated on damage.
    for (int k = 0; k < f.shotHitCount; ++k) {
        const gameplay::MatchFrame::ShotHit& hit = f.shotHits[k];
        if (!spawnEffect(app, app.matchFx, hit.effect, hit.point) && hit.effect >= 0)
            ++app.fxBadEffect;
    }
    // Melee hits keep the port's existing choice of the hit card (id 0 -> 000.dat ->
    // 14.X, the 8-quad hitC01/hitC05 card) now that its lifetime is recovered; the
    // original's melee hit path spawns no effect of its own (FUN_00639160 has no manager
    // call), so this is a PORT RULE, not a recovered binding.
    for (int i = 0; i < app.match.config().fighterCount; ++i) {
        if (!f.meleeHit[i] || f.meleeVictim[i] < 0) continue;
        const glm::vec3 at = app.match.fighter(f.meleeVictim[i]).position() +
                             glm::vec3(0.f, 100.f, 0.f);
        spawnEffect(app, app.matchFx, 0, at);
    }
    // The in-flight shot. PORT RULE: the original's projectile visual is not recoverable
    // from the shipped data — the descriptor table has no projectile entries, the 10
    // trail textures FUN_00633ca0 loads are never read by anything but the destructor
    // (FUN_00634520), and a bullet record names only an attachment part ('Bip00'), never
    // a model — so the port draws each live shot with the effect its own record names
    // (the id it will spawn on impact). The card's id is the pool SLOT, so a shot
    // refreshes one card in place for its whole flight.
    {
        const auto& shots = app.match.shots().shots();
        for (size_t slot = 0; slot < shots.size(); ++slot) {
            const gameplay::Projectile& p = shots[slot];
            if (!p.alive) continue;
            const game::EffectEntry* entry = app.fxCatalog.find(p.impactEffect);
            if (!entry || !entry->playable()) continue;
            app.matchFx.pushSpawn(kFxShotCardId + (uint32_t)slot, p.pos, entry->asset,
                                  (float)app.fxCatalog.lifetime_ticks(p.impactEffect, 64.f) / 64.f);
            ++app.fxShotCards;
        }
    }
    updateFxCards(app, app.matchFx, app.matchFxEvents, (float)dt);

    // The viewer is the fighter on panel kFrontendBattleSlots[0] (1P); its index was
    // resolved before the step, above.
    // The camera and HUD state below run per view; the targets they read are refreshed
    // once here from the live fighters. The pool does the dead-skip itself, and a real
    // target change arms the retarget blend so a switch lands fast without cutting.
    for (int i = 0; i < app.match.config().fighterCount; ++i) {
        const gameplay::Fighter& fighter = app.match.fighter(i);
        app.arenaTargets[i].position = fighter.position();
        app.arenaTargets[i].facingYaw = fighter.facing_yaw();
        app.arenaTargets[i].alive = fighter.is_alive();
    }

    // Camera and HUD, once per human view (issue #12). The original runs this same loop
    // over controller slots (FUN_006396f0:108-188), and each view's state is keyed by its
    // controller: the camera follows that view's own fighter, its LockSwitch gestures
    // re-pick that view's target, and its HUD is filled from that fighter's resources.
    // The MATCH itself was stepped once above, before this loop — views never advance it.
    const gameplay::CollisionQuery cameraQuery =
        (!historicalMatchCapture(app) && !app.opts.noCameraClamp)
            ? gameplay::CollisionQuery{&app.cameraCollision}
            : gameplay::CollisionQuery{};
    for (int v = 0; v < app.matchViewCount; ++v) {
        game::MatchView& view = app.matchViews[v];
        if (!view.active() || view.fighter >= app.match.config().fighterCount) continue;
        const fnd::input::PlayerState* viewInput = inputs[view.fighter];
        // LockSwitch is the original's target switch (input.h: tap = cycle enemy,
        // hold = aim ally) and it is TWO writes, not one. The cycle is FUN_00421e30's: it
        // moves the camera's followed player AND re-picks the viewer's combat target
        // (FUN_00421f30's +0x304) through the recovered wrap-around index walk. They are
        // kept separate from here on — the camera owns who is followed, gameplay/
        // target_lock.h owns who each fighter attacks — so two players hold different
        // locks while each camera follows its own player.
        if (viewInput && viewInput->just_pressed[fnd::input::LockSwitch]) {
            app.match.cycle_locked_target(view.fighter, true);
            view.camera.cycle_target(true);
            view.lockHeldTicks = 0;
        } else if (viewInput && viewInput->down[fnd::input::LockSwitch]) {
            // Held past the threshold, so the tap above is not undone by the finger still
            // being on the button. PORT RULE: the original's hold is recovered as the
            // 180-tick dwell FUN_0041f580:244 re-pins on an ally selection, but the gesture
            // length that raises it is not, so this threshold is a port constant.
            if (++view.lockHeldTicks >= kLockHoldTicks)
                app.match.lock_ally_target(view.fighter);
        } else {
            view.lockHeldTicks = 0;
        }
        // The DX9 reference's own camera switch (Guard just_pressed while its heavy key was
        // held, scenes.cpp:644-646) went with that key: the original has one melee input and
        // no heavy bit (issue #10), so target cycling is the recovered LockSwitch action
        // alone (gameplay/target_lock.h).
        // Scripted/offscreen standalone runs retain the banked null-query camera path;
        // live matches clamp the eye against collision_camera.x unless the A/B switch asks
        // for the historical unclamped behavior. The blend remains per call as in the port.
        view.camera.update(dt,cameraQuery);
        if (view.camera.active_target_index() >= 0) view.followed = view.camera.active_target_index();
        // The first camera tick has no valid earlier view to interpolate from.
        if (app.matchFrame == 1 || !view.primed) {
            view.previousEye = view.camera.eye();
            view.previousTarget = view.camera.target();
            view.primed = true;
        }

        // This view's HUD: the ported value computation (gameplay/hud_fill.h, unchanged),
        // fed from the view's own fighter. Which side goes where is the DX9 layout's:
        // the balloon corners are the only two-side readout (side 0 left, side 1 right),
        // every other field belongs to the viewer's fighter.
        gameplay::HudFillInput hf;
        sampleHudFill(hf.p1, app.match.fighter(view.fighter), viewInput);
        view.hud = gameplay::hudStateFor(app.match.economy(), hf);
        // D1: the render-FPS counter rides the HUD state (60 while capturing). The
        // original draws it once, outside its view loop (FUN_006396f0:203-210), so only
        // the first view carries it.
        view.hud.fps = app.fpsShown;
        view.hud.showFps = (v == 0);
        // The composer is clock-free by design, so the frame counter the original's
        // alternations and pulse read (FUN_00644150's `(frame % 0x1e) / 0xf` flash pair and
        // the balloon popup's growth) is carried in the state instead of read from a clock.
        view.hud.hudFrame = (int)app.matchFrame;
        // The boxed tactics readout (P03's 128x64 cells: 0 適当, 1 格闘, 2 射撃, 3 集中,
        // 4 各個, 5 後退). The cell IS the COM decision state's tactic: gameplay/bot_input.h
        // owns the recovered pairing of the +0x310 cell with the +0x314 display timer
        // (FUN_0041f580:291-295 writes it, FUN_004201a0:13-15 drains it, FUN_00644150:92-96
        // fades it), so what the HUD draws and what the COM obeys cannot drift apart.
        view.hud.commandCell = app.tacticReadout.hud_cell();

        // Per-fighter appearance state; projection happens per view with that view's
        // matrix (D8), below. The viewer's own lock names the fighter its ring and com bar
        // belong to: FUN_00643230:61 reads the target-valid flag as (+0x304 > -1) on the
        // fighter being drawn, and 0x421e30/0x421f30's +0x30c pulse as its scale and arc
        // twist (hud.h:83-86), so both come from the view's own lock and not from which
        // player its camera happens to follow.
        const int lockedTarget = app.match.locked_target(view.fighter);
        const int viewPulse = app.match.lock_pulse(view.fighter);
        // One HUD entry per ROSTER entry (issue #13): the participant's own fighter, its
        // team and its controller. A 1v1 fills two, a 2v2 all four.
        for (int i = 0; i < ui::kHudFighterCount; ++i) {
            view.hud.fighters[i] = ui::HudFighterHud{};
            const int fighterIndex = hudEntryFighter(app, i);
            if (fighterIndex < 0) continue;
            const ui::Participant& p = app.participants[i];
            const gameplay::Fighter& f = app.match.fighter(fighterIndex);
            // Owner / ally / enemy from THIS view's point of view: the original's owner is
            // the fighter whose +0x300 equals the view player's (FUN_00643230:63-69), and
            // the team is the match's side table.
            const int viewSide = app.match.config().side[view.fighter];
            view.hud.fighters[i].role = fighterIndex == view.fighter
                ? ui::HudFighterRole::Owner
                : (app.match.config().side[fighterIndex] == viewSide ? ui::HudFighterRole::Ally
                                                                    : ui::HudFighterRole::Enemy);
            view.hud.fighters[i].target = (fighterIndex == lockedTarget);
            // Ring art row 0 while the fighter is in an action (the original's action
            // counter, hud+0x7ac > 0). PORT RULE: Fighter carries no action counter, so the
            // action states that counter corresponds to stand in for it.
            view.hud.fighters[i].acting = f.state() == gameplay::FighterState::AttackA ||
                                          f.state() == gameplay::FighterState::AttackC ||
                                          f.state() == gameplay::FighterState::Hit ||
                                          f.state() == gameplay::FighterState::Knockdown ||
                                          f.state() == gameplay::FighterState::KO;
            // The fighter's OWN lock (green ring) is not the viewer's target: FUN_00643230
            // reads fighter+0x304 for the ring and the view player's +0x304 for the com bar.
            view.hud.fighters[i].locked = app.match.locked_target(fighterIndex) >= 0;
            view.hud.fighters[i].hyper = f.hyper_active();
            // The pulse belongs to the fighter that switched, so only that fighter's HUD
            // entry scales and twists; partners' rings stay at rest.
            view.hud.fighters[i].ringPulse = (fighterIndex == view.fighter) ? viewPulse : 0;
            // Slot 0 is 1P and slot 4 is com in the tag atlas (P01 (320,256,64,32) rows);
            // the red copies sit four rows down, which is the tagSheet index.
            view.hud.fighters[i].slot = p.controller;
            view.hud.fighters[i].tagSheet = p.team;
            view.hud.fighters[i].hp = (float)f.hp() / f.max_hp();
            view.hud.fighters[i].hpLag = view.hud.fighters[i].hp;
            view.hud.fighters[i].alertDir = -1;   // the render pass resolves it per view
        }
    }

    // The banked trace (tests/compare_match_traces.py) prints the eye the reference camera
    // reported for the primary view, so keep app.eye/app.target on it: the render loop
    // later replaces them with the interpolated presentation values.
    const game::MatchView& primary = app.matchViews[0];
    app.eye = primary.camera.eye();
    app.target = primary.camera.target();

    if (f.roundOver) {
        app.matchRoundOverFrame = app.matchFrame;
        // Issue #11: roundOverSide is the WINNER (the original's scene+0x442c), and
        // roundEnd() says which rule ended it — a balloon burst or the time limit.
        const gameplay::MatchEconomy& eco = app.match.economy();
        std::printf("[daybreak] match: round over, side %d wins (%s) at frame %llu\n",
                    f.roundOverSide,
                    eco.roundEnd() == gameplay::RoundEnd::Timeout ? "time up" : "burst",
                    (unsigned long long)app.matchFrame);
        printComSummary(app);
        printFxSummary(app);
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
// --hitbox-debug overlay colours. Green is what you can HURT, red is what HITS, and
// grey is anything that is neither — the convention a future marker follows rather than
// re-deciding. Grey is defined but not yet drawn: there is no third category today, and
// an unused colour constant would be dead code.
static constexpr render::DebugColor kHurtVolume  = render::packColor(0, 230, 60, 90);
static constexpr render::DebugColor kHitVolume   = render::packColor(255, 40, 40, 110);
static constexpr render::DebugColor kOtherVolume = render::packColor(150, 150, 150, 90);

static void fillMatchCubes(App& app) {
    app.matchCubes.clear();
    app.auraCubes.clear();
    app.hitboxCubes.clear();
    // Issue #17: shots and sparks draw as real effect cards by default; these cubes are
    // the explicit A/B view behind --debug-prims, which is also where the aura cube lives.
    if (app.opts.debugPrims) {
        for (const gameplay::Projectile& p : app.match.shots().shots()) {
            if (!p.alive) continue;
            app.matchCubes.add(p.pos, gameplay::Projectile::kCubeSize, p.color());
        }
        for (const gameplay::Spark& s : app.match.shots().sparks()) {
            if (!s.alive) continue;
            app.matchCubes.add(s.pos, s.size() * 0.5f, s.color());
        }
    }
    // --hitbox-debug: the recovered melee hit spheres from issue #10, drawn as filled
    // translucent red volumes. These are the SAME anchors and radius try_melee_hit()
    // tests (Fighter::hitbox_debug() reads the fighter's own rules), so the overlay
    // cannot drift from the simulation. Separate from matchCubes so it can be toggled
    // without changing what the shots/sparks pass submits.
    if (app.opts.hitboxDebug) {
        for (int i = 0; i < app.match.config().fighterCount; ++i) {
            const gameplay::Fighter::HitboxDebug hb = app.match.fighter(i).hitbox_debug();
            for (const glm::vec3& anchor : hb.anchors)
                app.hitboxCubes.addSphere(anchor, hb.anchorRadius, kHurtVolume);
            if (hb.attacking)
                app.hitboxCubes.addSphere(hb.attackCenter, hb.attackRadius, kHitVolume);
        }
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
        // Issue #17: the recovered hit card (id 0 -> data/effect/000.dat -> 14.X) with the
        // lifetime its own model animates for (0.250 s), and one INSTANCE per scripted
        // hit. The old scripted 5 s placeholder and its kill-chaining are gone, so this
        // capture shows a card only within its recovered lifetime of a hit: the recipe is
        // `--versus --frames=<hit frame + 8>` (the hits are at 30/55/80% of --frames).
        spawnEffect(app, app.versusFx, 0, (p1 + p2) * 0.5f);
    }
    // The scripted timeline has no clock: cards age at the capture's fixed step
    // (1/60), keeping a versus run a pure function of the frame index.
    updateFxCards(app, app.versusFx, app.versusFxEvents, 1.f / 60.f);
    placeFxCards(app);
    placeVersusFighters(app, p1, p2);
}

// --- game folder: what counts as usable, and what to say when it is not -------------
// An explicit folder (--install=, $DAYBREAK_INSTALL) must be a bundle install: openInstall
// is the only route that can read a folder by name, because the filesystem fallback
// resolves the asset layer's own relative keys ("data/...") against the working directory.
// The extracted-tree route therefore stays what it always was — running the port from that
// folder — and the message below says so instead of promising a read that cannot happen.
//
// A wrong folder is nearly always "pointed at the wrong one", so the message names it, says
// what is missing and gives the next step; a developer backtrace is not an acceptable
// user-facing failure. The packaged launcher prints the same shape when it finds no folder
// at all (package/README-LINUX.md documents the search order).
static std::string installUnusableMessage(const std::string& dir, const char* source) {
    return std::string("no game data in \"") + dir + "\" (" + source +
           "): the folder has no daybreakXX.dat files. Point at the folder that contains "
           "daybreak00.dat (your Higurashi Daybreak install); an extracted data/ tree is "
           "used by running the port from inside that folder instead";
}

// Opens `dir` as the game folder or reports why it cannot be one.
static bool openInstallOrReport(const std::string& dir, const char* source, std::string& error) {
    if (fnd::assets::assetSource().openInstall(dir)) return true;
    error = installUnusableMessage(dir, source);
    return false;
}

bool initScene(App& app) {
    // Install discovery: the .dat bundles are the game's own source of truth, and where
    // they exist they win over an extracted tree (asset_source.h explains why the two
    // differ). The install is inferred from whichever asset path the command line
    // already carries, so existing capture command lines keep working verbatim;
    // --install= overrides when a path points somewhere unexpected.
    if (!app.opts.install.empty()) {
        // An explicit folder that is unusable is a mistake worth failing on: silently
        // falling through to the filesystem would report a missing asset several screens
        // later instead of naming the wrong path.
        if (!openInstallOrReport(app.opts.install, "--install=", app.error)) return false;
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
    app.modelMatrices.assign(app.scene.models.size(), glm::mat4(1.f));
    // FUN_00633ca0's effect models extend the scene. Finish that growth before
    // fighters, animation controllers or collision queries borrow model pointers.
    if (app.opts.match || app.opts.versus) buildFxAssets(app);

    // Effects are part of SceneModel storage too, so finish appending them before
    // borrowing any model pointers for fighters or collision queries.
    const xm::Model* movementMesh = nullptr;
    const xm::Model* groundMesh = nullptr;
    const xm::Model* cameraMesh = nullptr;
    app.projectileCollisionMesh = nullptr;
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.hasCollisionChannel(xm::StageCollisionChannel::Movement)) movementMesh = &sm.model;
        if (sm.hasCollisionChannel(xm::StageCollisionChannel::Ground)) groundMesh = &sm.model;
        if (sm.hasCollisionChannel(xm::StageCollisionChannel::Projectile)) {
            app.projectileCollisionMesh = &sm.model;
            app.projectileCollisionIndex = game::physics::buildModelIndex(sm.model);
        }
        if (sm.hasCollisionChannel(xm::StageCollisionChannel::Camera)) cameraMesh = &sm.model;
    }
    app.movementCollision.setMeshes(movementMesh, groundMesh);
    app.cameraCollision.setMesh(cameraMesh);
    if (movementMesh)
        std::printf("movement collision : collision.x (%s)\n",
                    app.movementCollision.empty() ? "empty mesh" : "swept query loaded");
    if (groundMesh)
        std::printf("ground collision   : collision.x (%s)\n",
                    app.movementCollision.empty() ? "empty mesh" : "surface query loaded");
    if (app.projectileCollisionMesh)
        std::printf("projectile collision: collision_tama.x\n");
    if (cameraMesh)
        std::printf("camera collision   : collision_camera.x (%s)\n",
                    app.cameraCollision.empty() ? "empty mesh, no clamp" : "loaded");

    // ---- pose: bind pose, or one animation set driven through the Controller
    app.controllers.resize(app.scene.models.size());
    app.worlds.resize(app.scene.models.size());
    if (app.opts.animPlayer) app.apIndex = std::min(app.opts.anim, app.scene.models.empty()
                                       ? 0 : (int)app.scene.models[0].model.anims.size());
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
    // Toon rendering (issue #21): a capture flag wins; otherwise the persisted/live
    // Options state, which the per-frame sync below keeps up to date so the row needs no
    // restart (and the renderer no re-upload).
    app.appearance.toon = app.opts.toonSet ? app.opts.toon
                                           : ui::frontendSettings().toonRendering;

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
    // The animation browser draws its set name through the same sprite/caption path, so
    // it needs the UI renderer even though it is not a match and draws no battle HUD.
    if (app.opts.hudTest || app.matchMode || app.versusMode || app.opts.animPlayer) {
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
    std::printf("\n-- render frame timing (wall-clock delta) --\n");
    std::printf("frames      : %llu in %.3f s\n", (unsigned long long)app.frames, elapsed);
    if (app.opts.match || !app.opts.screen.empty())
        std::printf("logic       : %llu ticks, %s\n", (unsigned long long)app.logicTicks,
                    app.opts.out.empty() ? "64 Hz" : "explicit capture cadence");
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
    stopCombatAudio(app);
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
// The round-start countdown. Its art is the original's own: P09's three cells (0,0,192,256),
// (192,0,192,256) and (384,0,128,256), registered by FUN_00633ca0 @0x633ca0 with pivots
// (96,128), (96,128) and (64,128), drawn at the frame centre.
//
// TIMING (issue #13): the recovered pre-round phase is NOT three seconds — FUN_00634760
// @0x634760 sets phase 1 and FUN_00635d40:62-83 hands over to the fight after THREE frames,
// arming each view's centre sting for 0x3c = 60 frames at scale 6.0 shrinking to 1.0. The
// code that walks the three digits is not in the corpus, so the port keeps its documented
// three-second countdown (ROADMAP-PENDING's D3 row) rather than inventing a pace. What it
// adds here is the BATTLE STATE around the digit: the round settings and every participant
// (team, combo, controller), so the countdown shows who is about to fight.
class RoundStartScreen final : public ui::Screen {
public:
    RoundStartScreen(ui::SpriteRenderer& batch, App& app, bool& ready, int tickRate,
                     std::string& error)
        : app_(app), ready_(ready), tickRate_(tickRate) {
        ui::uploadCnvSheet(batch, "data/object/P09", sheet_, error);
        if (!loadCaptionFont(text_, 18.f, error)) return;
        // The round's own settings, then one line per participant. The roster is the
        // selection (issue #13), so a 2v2 lists four.
        std::vector<std::string> lines;
        char settings[96];
        std::snprintf(settings, sizeof(settings), "TIME %ds   BALLOON %d%% / %d%%",
                      app_.frontend.timeLimit, app_.frontend.blueBalloon,
                      app_.frontend.redBalloon);
        lines.push_back(settings);
        settingsLayout_ = text_.layout(lines.back().c_str());
        for (int i = 0; i < app_.participantCount; ++i) {
            const ui::Participant& p = app_.participants[i];
            lines.push_back(std::string(ui::teamLabel(p.team)) + "  " + p.combo() + "  " +
                            ui::controllerLabel(p.controller));
            rosterLayout_[i] = text_.layout(lines.back().c_str());
        }
        textSlot_ = batch.addTexture(text_.atlasWidth(), text_.atlasHeight(),
                                     text_.atlasRGBA().data(), error);
    }
    bool loaded() const { return sheet_ >= 0; }
    ui::ScreenId update(const ui::ScreenInput&) override {
        if (++frame_ >= 3 * tickRate_) ready_ = true;
        return ui::ScreenId::Battle;
    }
    const char* name() const override { return "countdown"; }
    void draw(ui::SpriteRenderer& batch) const override {
        batch.pushSolid({0,0,800,600},{0,0,0,1});
        const int n = std::min(2, frame_ / tickRate_);
        const float w = n == 2 ? 128.f : 192.f;
        batch.pushSprite(sheet_, {n*192.f,0,w,256},w/2,128,400,300,.5f);
        if (textSlot_ < 0) return;
        drawCaptionLayout(batch, text_, settingsLayout_, textSlot_, bitmapSlot_, 40.f, 40.f, .8f,
                          ui::kHudWhite, 2.f);
        for (int i = 0; i < app_.participantCount; ++i)
            drawCaptionLayout(batch, text_, rosterLayout_[i], textSlot_, bitmapSlot_, 40.f,
                              70.f + 26.f * (float)i, .8f,
                              app_.participants[i].team == 0 ? ui::kHudLimitLeft
                                                             : ui::kHudLimitRight,
                              2.f);
    }
private:
    App& app_;
    bool& ready_;
    int frame_ = 0, sheet_ = -1;
    int tickRate_;
    ui::TextLayer text_;
    ui::TextLayout settingsLayout_, rosterLayout_[ui::kParticipantCount];
    mutable int bitmapSlot_ = -1;
    int textSlot_ = -1;
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
    // --local-players=N (verification): open N local human views by assigning controllers
    // 0..N-1 in panel order. One or two humans fight the 1v1 panel pair (0 blue, 2 red);
    // three or four use all four panels as a 2v2, where the human-less panel stays COM and
    // must not allocate a view (issue #12). This is the same controller-slot order
    // FUN_0040d130 counts humans in and FUN_006396f0 keys views by.
    if (app.opts.localPlayers > 0) {
        static constexpr int kDuelPanels[2] = {0, 2};
        static constexpr int kTeamPanels[4] = {0, 1, 2, 3};
        const int humans = app.opts.localPlayers;
        const int panelCount = humans <= 2 ? 2 : 4;
        const int* panels = humans <= 2 ? kDuelPanels : kTeamPanels;
        // Roster picks that actually gear up: a character whose slot-0 item does not join
        // fails the launch loudly (rule 7), and an install gap in one character's item data
        // must not turn a --local-players run into a false negative about split-screen.
        int chosen[4] = {-1, -1, -1, -1};
        for (int i = 0; i < panelCount; ++i) {
            for (int candidate = 0; candidate < gameplay::kCharacterCount && chosen[i] < 0;
                 ++candidate) {
                bool used = false;
                for (int j = 0; j < i; ++j) used = used || chosen[j] == candidate;
                if (used) continue;
                std::string mesh;
                int itemId = 0;
                if (resolveFighterWeapon(gameplay::kCharacterDirs[candidate], "", mesh, itemId) &&
                    !mesh.empty())
                    chosen[i] = candidate;
            }
            if (chosen[i] < 0) chosen[i] = i;   // nothing usable: let the loud error fire
        }
        for (int i = 0; i < panelCount; ++i) {
            ui::FrontendSlot& slot = app.frontend.slots[panels[i]];
            if (slot.character < 0) slot.character = chosen[i];
            slot.controller = i < humans ? i : 4;
        }
        // Keep the match to the panels this flag selected: a panel left over from an
        // earlier menu run would silently add a fighter (and a COM slot) to the roster.
        for (int i = 0; i < 4; ++i) {
            bool selected = false;
            for (int j = 0; j < panelCount; ++j) selected = selected || panels[j] == i;
            if (!selected) app.frontend.slots[i] = ui::FrontendSlot{};
        }
    }
    ui::FrontendLaunch launch;
    if (!ui::frontendLaunch(app.frontend, launch, app.error, (uint32_t)app.logicTicks)) return false;
    app.battleLaunch = launch;
    // The penalty flag is per PLAYER: a panel that is COM has no player, so its flag is cleared
    // (FUN_0040d130:99-101 clears DAT_006cfdf1 for a panel whose controller byte says COM).
    for (int panel = 0; panel < 4; ++panel)
        if (app.frontend.slots[panel].controller >= 4) app.frontend.penaltyDecided[panel] = false;
    // The roster the VS screen, the battle HUD and the results all read (issue #13). Built
    // here because VS runs before the match exists; initMatch rebuilds it for the standalone
    // path and to link each entry to its MatchConfig index.
    buildMatchRoster(app);
    // Parse every selected weapon's combat definition now, so the battle has real
    // per-weapon tuning by the time initMatch builds MatchConfig (issue #9).
    app.weaponDefs.clear();
    app.weaponDefs.resize(static_cast<size_t>(launch.fighterCount));
    app.bulletParams.clear();
    app.bulletParams.resize(static_cast<size_t>(launch.fighterCount));
    for (int i = 0; i < launch.fighterCount; ++i)
        if (!loadWeaponDefinition(app, i, launch.fighters[i].weaponId, app.error))
            return false;
    // Load the recovered per-weapon projectile parameters. Damage, hit radius and hitstun
    // are used here; blob fields +0x64/+0x68 are retained as decoded values, but their
    // hit-resolution use does not establish a charge-tier shot selector. A level with no
    // matching bullet file stays empty, the shared provisional table for that port tier.
    for (int i = 0; i < launch.fighterCount; ++i)
        for (int level = 1; level <= 2; ++level)
            loadBulletParameter(app, i, level, *app.weaponDefs[static_cast<size_t>(i)],
                                app.bulletParams[static_cast<size_t>(i)]
                                          [static_cast<size_t>(level - 1)]);
    app.frontendMatch = true;
    app.frontendBattleReady = false;
    app.battlePaused = false;   // a fresh battle never starts paused (issue #15)
    app.match.set_paused(false);
    app.pauseMenu.reset();
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
    app.liveFx.clear();
    app.fxCatalog.clear();
    for (int& slot : app.fxAttach) slot = -1;
    for (float& sec : app.fxAttachSeconds) sec = 0.f;
    app.fxNextInstance = 1;
    app.fxTally = game::FxCardTally{};
    app.fxBadEffect = app.fxShotCards = 0;
    app.matchFx.drain();
    if (!initScene(app)) return false;
    app.versusAudio.set_volumes(ui::frontendSettings().volumes);
    // Live combat audio (issue #16): the sink adapts this App's battle engine, the dispatcher
    // owns the recovered event -> voice/SE policy. Built here, after the match exists, so the
    // per-fighter voice directories come from the actual launch roster.
    if (!app.combatSink) app.combatSink = std::make_unique<App::CombatSink>(app);
    if (!app.combatAudio) app.combatAudio = std::make_unique<fnd::audio::CombatAudio>(*app.combatSink);
    setupCombatVoices(app);
    app.matchMode = false;
    std::printf("[menu] battle: %d fighters on %s\n", launch.fighterCount, launch.stage.c_str());
    // The spawn each fighter starts from: MatchConfig keys it by the fighter's PANEL
    // (FUN_00423420 indexes the stage's env points by the selected panel), so a 2v2 starts
    // from four different points. Printed because how far apart teammates stand is the whole
    // question behind the four-fighter spawn-crowding note in ROADMAP-PENDING.md.
    for (int i = 0; i < launch.fighterCount; ++i) {
        const glm::vec3& spawn = app.scene.env.points[launch.fighters[i].panel];
        std::printf("[menu]   fighter %d panel %d spawn=(%.0f,%.0f,%.0f)\n", i,
                    launch.fighters[i].panel, spawn.x, spawn.y, spawn.z);
    }
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
    // Front-end install: --install= wins, then $DAYBREAK_INSTALL — the two spellings that
    // make the binary usable on its own. The packaged launcher (package/daybreak) owns the
    // wider search (saved preference, package directory, conventional locations) and
    // always hands the chosen folder in as --install=, so the order is defined once, in
    // package/README-LINUX.md. With neither, the historical filesystem fallback stays:
    // running from the install directory (or an extracted tree) must keep working.
    std::string install = app.opts.install;
    const char* installSource = "--install=";
    if (install.empty()) {
        if (const char* env = std::getenv("DAYBREAK_INSTALL"); env && *env) {
            install = env;
            installSource = "DAYBREAK_INSTALL";
        }
    }
    if (!install.empty()) {
        if (!openInstallOrReport(install, installSource, app.error)) return false;
        std::printf("[install] game folder: %s (from %s)\n", install.c_str(), installSource);
    } else if (!fnd::assets::assetSource().exists("data/title/back00.cnv")) {
        // No folder named and the working directory is not one either (neither a bundle
        // install nor an extracted tree): the title art is the first read of a front-end
        // run, so fail here naming the folder to point at instead of leaving a per-asset
        // message from inside the title screen.
        app.error = "no Higurashi Daybreak data found: neither --install= nor DAYBREAK_INSTALL "
                    "was given and the current directory has no data/title/back00.cnv. Point "
                    "the port at your game folder, e.g. --install=\"/path/to/Higurashi-Daybreak\"";
        return false;
    } else {
        std::printf("[install] no --install= and no DAYBREAK_INSTALL: reading data/ from the "
                    "current directory\n");
    }
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
            auto countdown = std::make_unique<RoundStartScreen>(app.uiRenderer, app, app.frontendBattleReady,
                app.opts.out.empty() ? gameplay::FixedStep::tickRate : 60, app.error);
            if (!countdown->loaded()) return nullptr;
            return countdown;
        }
        auto screen = ui::makeScreen(sid, app.uiRenderer, app.frontend, app.error);
        if (screen) std::printf("[menu] scene: %s (tick %llu)\n", screen->name(), (unsigned long long)app.logicTicks);
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
    if (app.settingsActive) {
        // Stable-controller identity: the hints have to be in place before the first pad
        // poll, so a replugged pad is given back its player slot (issue #19).
        for (int player = 0; player < fnd::input::kMaxPlayers; ++player)
            app.matchInput.set_gamepad_guid_hint(player, app.userSettings.padGuid[static_cast<size_t>(player)]);
        applyPersistedDisplay(app);
    }
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
            app->error = "could not create a window surface: run the game from a desktop "
                         "session with a working Wayland or X11 display";
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
        std::printf("surface format: 0x%x\n", (unsigned)app->sc.format);
        std::printf("present mode : %s\n", gpu::presentModeName(app->sc.presentMode));
    }

    if (app->opts.audioTest) return runAudioTest(*app) ? SDL_APP_SUCCESS : SDL_APP_FAILURE;
    if (app->opts.inputTest) return runInputTest(*app) ? SDL_APP_SUCCESS : SDL_APP_FAILURE;

    // Persisted settings land before any screen exists, so the first frame the frontend
    // draws already uses the user's volumes and bindings (issue #19). Capture and parity
    // runs skip this entirely — see usesUserConfig.
    if (usesUserConfig(app->opts)) loadUserSettings(*app);

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
//
// A match composites one pass per human view (issue #12): each pass draws its view's own
// HUD state into that view's cell. Everything else is one pass over the whole target, which
// is exactly what this hook did before split-screen existed.
// ---------------------------------------------------------------------------------------
struct HudPass {
    ui::HudState  state;
    bool          hasState = false;   // false -> syntheticHudState()
    bool          referenceCoordinates = true;
    ui::UiViewport viewport{};        // cell inside the render target (x/y = 0 when single)
};

struct HudTestHook {
    ui::SpriteRenderer* ui = nullptr;
    ui::HudComposer*    hud = nullptr;
    std::string*        error = nullptr;
    bool                probe = false;   // --hud-probe: per-view corner markers
    std::vector<HudPass> passes;
    // The split-screen separators, drawn after every view (FUN_006396f0:191-195). Empty
    // for a single view, which is the historical path.
    std::vector<ui::UiRect> separators;
    ui::UiViewport          target{};
};

ui::HudState syntheticHudState() {
    // Field-equal to game::syntheticHudState() by construction (the track's own
    // test pins it); forwarding keeps one definition of the test values.
    return game::syntheticHudState();
}

HudTestHook battleHudHook(App& app) {
    HudTestHook hook{&app.uiRenderer, &app.hudComposer, &app.error, app.opts.hudProbe};
    if (app.versusMode) {
        hook.passes.push_back(HudPass{app.versusHud, true, true, {}});
    }
    return hook;
}

// The match's HUD passes: one per rendered view, in view order, each carrying the state
// that view's controller filled at tick time and the cell geometry gave it.
void appendMatchHudPasses(App& app, const std::vector<FrameView>& views, uint32_t width,
                          uint32_t height, HudTestHook& hook) {
    hook.target = ui::UiViewport{width, height, 0, 0};
    for (const FrameView& view : views) {
        HudPass pass;
        pass.state = view.hud;
        pass.hasState = true;
        // A match view's markers were already projected into its own logical viewport, so
        // they need no reference-coordinate shift; the versus vignette still does.
        pass.referenceCoordinates = false;
        pass.viewport = ui::UiViewport{(uint32_t)view.cell.w, (uint32_t)view.cell.h,
                                       (uint32_t)view.cell.x, (uint32_t)view.cell.y};
        hook.passes.push_back(std::move(pass));
    }
    const int separators = game::separatorCount(game::splitLayoutFor(app.matchViewCount));
    for (int i = 0; i < separators; ++i) {
        const game::ViewRect rect = game::separatorRect(i, width, height);
        hook.separators.push_back(ui::UiRect{rect.x, rect.y, rect.w, rect.h});
    }
}

// The split-screen evidence line: which layout ran, and per view its controller, its
// fighter, its cell and the HUD values that view actually drew. Printed on the capture
// frame and periodically by --local-players, so a headless run shows independent per-view
// cameras and HUD values without reading pixels.
void reportMatchViews(const App& app, uint32_t width, uint32_t height) {
    const game::SplitLayout layout = game::splitLayoutFor(app.matchViewCount);
    std::printf("[split] layout=%s views=%d target=%ux%u roster=%d\n",
                layout == game::SplitLayout::Single ? "single"
                                                    : (layout == game::SplitLayout::Two ? "two" : "four"),
                app.matchViewCount, width, height, app.participantCount);
    for (int v = 0; v < app.matchViewCount; ++v) {
        const game::MatchView& view = app.matchViews[v];
        if (!view.active()) continue;
        const game::ViewRect rect = game::viewCell(layout, v, width, height);
        const ui::HudState& hud = view.hud;
        std::printf("[split] view %d: controller=%d fighter=%d cell=(%.0f,%.0f,%.0f,%.0f) "
                    "hp=%.0f main=%d charge=%d stamina=%.2f hyper=%s gauge=%.2f\n",
                    v, view.controller, view.fighter, rect.x, rect.y, rect.w, rect.h, hud.hp,
                    hud.mainWhole, hud.chargeWhole, hud.staminaFrac, hud.hyperName.c_str(),
                    hud.hyperGauge);
        // Per-participant markers, projected through THIS view's camera on this frame's own
        // cell: the entry's role, its tag (controller/COM), whether this view sees it and
        // which edge its marker points at when it does not (issue #13's evidence line).
        ui::HudState projected = hud;
        const glm::mat4 viewProj = view.camera.proj_matrix((int)rect.w, (int)rect.h) *
                                   view.camera.view_matrix();
        projectViewHud(app, &viewProj[0][0], rect.w, rect.h, projected);
        for (int i = 0; i < app.participantCount; ++i) {
            const ui::HudFighterHud& f = projected.fighters[i];
            const ui::Participant& p = app.participants[i];
            std::printf("[split]   p%d panel=%d team=%d %s %s role=%s fighter=%d visible=%d "
                        "target=%d acting=%d alert=%d hp=%.0f ring=(%.0f,%.0f)\n",
                        i, p.panel, p.team, ui::controllerLabel(p.controller), p.combo().c_str(),
                        f.role == ui::HudFighterRole::Owner
                            ? "owner"
                            : (f.role == ui::HudFighterRole::Ally ? "ally" : "enemy"),
                        p.fighter, f.visible ? 1 : 0, f.target ? 1 : 0, f.acting ? 1 : 0,
                        f.alertDir, f.hp * 100.f, f.ringX, f.ringY);
        }
    }
}

bool hudTestHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                 uint32_t w, uint32_t h, void* ud) {
    auto* hk = static_cast<HudTestHook*>(ud);
    if (hk->passes.empty()) {
        HudPass pass;
        pass.viewport = ui::UiViewport{w, h, 0, 0};
        hk->passes.push_back(std::move(pass));
    }
    for (const HudPass& pass : hk->passes) {
        // A pass with no cell of its own is the whole target — the versus vignette, the
        // synthetic --hud-test frame and every pre-split-screen capture path.
        const ui::UiViewport viewport = pass.viewport.w && pass.viewport.h
            ? pass.viewport
            : ui::UiViewport{w, h, 0, 0};
        hk->ui->beginFrame(viewport);
        ui::HudState state = pass.hasState ? pass.state : syntheticHudState();
        if (pass.referenceCoordinates) {
            const auto layout = ui::computeBattleHudLayout(viewport.w,viewport.h);
            for (auto& fighter : state.fighters) {
                fighter.ringX += (layout.width-800.f)*.5f;
                fighter.barX += (layout.width-800.f)*.5f;
                fighter.ringY += (layout.height-600.f)*.5f;
                fighter.barY += (layout.height-600.f)*.5f;
            }
        }
        hk->hud->compose(*hk->ui, state);
        if (hk->probe) {
            // Two markers in the VIEW's own coordinates: the top-left and the
            // bottom-right corner of this pass's viewport. A capture then pins the
            // view -> target mapping exactly (tests/hud_cell_scale.py): correct means
            // each cell's markers sit on that cell's corners, and the split-screen HUD
            // scale defect moved them to half the cell instead. The composer leaves its
            // canvas transform and clip set, so both are reset first — otherwise the
            // markers inherit the HUD's own clip and half of them never reach the frame.
            hk->ui->resetCanvasTransform();
            const float mw = 6.f;
            hk->ui->pushSolid({0.f, 0.f, mw, mw}, ui::UiColor{1.f, 0.f, 1.f, 1.f});
            hk->ui->pushSolid({(float)viewport.w - mw, (float)viewport.h - mw, mw, mw},
                              ui::UiColor{0.f, 1.f, 1.f, 1.f});
        }
        if (!hk->ui->render(enc, view, format, *hk->error)) return false;
    }
    if (!hk->separators.empty()) {
        hk->ui->beginFrame(hk->target);
        for (const ui::UiRect& rect : hk->separators)
            hk->ui->pushSolid(rect, ui::UiColor{0.f, 0.f, 0.f, 1.f});
        if (!hk->ui->render(enc, view, format, *hk->error)) return false;
    }
    return true;
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
// --anim-player input. Arrows step the set index, WASD orbits. This view deliberately
// ignores matchInput: a clip browser wants raw keys, not the gameplay action map, where
// Up is bound to double-tap dash.
static void animPlayerKey(App& app, SDL_Keycode key) {
    int sets = 0;
    if (!app.scene.models.empty()) sets = (int)app.scene.models[0].model.anims.size();
    if (sets <= 0) return;
    switch (key) {
        case SDLK_RIGHT: case SDLK_UP:
            app.apIndex = (app.apIndex + 1) % sets;
            break;
        case SDLK_LEFT: case SDLK_DOWN:
            app.apIndex = (app.apIndex - 1 + sets) % sets;
            break;
        case SDLK_W: app.apPitch -= 0.08f; break;
        case SDLK_S: app.apPitch += 0.08f; break;
        case SDLK_A: app.apYaw -= 0.12f; break;
        case SDLK_D: app.apYaw += 0.12f; break;
        default: return;
    }
    app.apPitch = std::clamp(app.apPitch, -1.2f, 1.2f);
    app.apTime = 0.0;   // a new clip starts at its beginning
}

// Advances the browsed clip and re-poses the rig. Runs in the frame loop so the clip
// plays, is looped at its own length, and re-poses when the index changes.
static void animPlayerTick(App& app, double dt) {
    if (app.scene.models.empty()) return;
    xm::Model& m = app.scene.models[0].model;
    if (app.apIndex < 0 || app.apIndex >= (int)m.anims.size()) return;

    xm::Controller& c = app.controllers[0];
    if (app.apIndex != app.opts.anim) {
        app.opts.anim = app.apIndex;
        c.bind(&m);
        c.setAnimation(app.apIndex, true);
        // AnimSet::duration is in the file's own ticks; setTrackPosition takes SECONDS
        // and converts through Model::ticksPerSecond (xmodel.h:1979). So the length is
        // converted here once, and the per-frame seek stays in seconds.
        const double tps = m.ticksPerSecond > 0.f ? (double)m.ticksPerSecond : 4800.0;
        app.apLength = std::max(0.05, (double)m.anims[app.apIndex].duration / tps);
        app.apTime = 0.0;
    }
    app.apTime += dt;
    if (app.apTime > app.apLength) app.apTime = std::fmod(app.apTime, app.apLength);
    c.setTrackPosition(0, app.apTime);
    c.evalWorld(app.worlds[0]);

    const float ch = std::cos(app.apPitch);
    app.target = glm::vec3(0.f, 80.f, 0.f);
    app.eye = app.target + glm::vec3(std::sin(app.apYaw) * ch, std::sin(app.apPitch),
                                     std::cos(app.apYaw) * ch) * app.apDist;
}

// scene pass creates it, and a capture-sized run has no earlier render to borrow from.
struct CaptureHook {
    render::SceneRenderer*        renderer = nullptr;
    HudTestHook*                  hud = nullptr;    // null -> no UI pass
    render::DebugPrims*           prims = nullptr;  // null -> no prims pass
    const render::DebugLineBatch* lines = nullptr;
    const render::CubeBatch*      solid = nullptr;   // shots + sparks (opaque)
    const render::CubeBatch*      additive = nullptr;   // hypermode auras
    const render::CubeBatch*      hitbox  = nullptr;   // --hitbox-debug melee spheres
    // One entry per view for the overlay passes: the same matrix and cell the scene pass
    // drew with, so a view's cubes and lines land in that view (issue #12). An entry with
    // an empty rect is the single-view frame, whose passes keep the full-target viewport.
    std::vector<render::ViewCamera> views;
    render::DebugPrims::Options   primOptions;
    std::string*                  error = nullptr;
};

bool captureHook(WGPUCommandEncoder enc, WGPUTextureView view, WGPUTextureFormat format,
                 uint32_t w, uint32_t h, void* ud) {
    auto* ck = static_cast<CaptureHook*>(ud);
    if (ck->hud && !hudTestHook(enc, view, format, w, h, ck->hud)) return false;
    if (!ck->prims) return true;
    const render::Target target{enc, view, format, w, h};
    for (const render::ViewCamera& frameView : ck->views) {
        const render::ViewportRect& rect = frameView.rect;
        if (ck->solid && !ck->solid->empty()) {
            render::DebugPrims::Options o;   // depth-tested, the reference's opaque cube pass
            o.viewport = rect;
            if (!ck->prims->drawCubes(target, frameView.viewProj, *ck->solid,
                                      ck->renderer->depthView(), o, *ck->error))
                return false;
        }
        // Straight alpha (not additive): a translucent hit volume should tint what is behind
        // it rather than blow out, so overlapping fighters stay readable.
        if (ck->hitbox && !ck->hitbox->empty()) {
            render::DebugPrims::Options o;
            o.viewport = rect;
            if (!ck->prims->drawCubes(target, frameView.viewProj, *ck->hitbox,
                                      ck->renderer->depthView(), o, *ck->error))
                return false;
        }
        if (ck->additive && !ck->additive->empty()) {
            render::DebugPrims::Options o;
            o.additive = true;   // SrcAlpha/One, the aura pass's blend
            o.viewport = rect;
            if (!ck->prims->drawCubes(target, frameView.viewProj, *ck->additive,
                                      ck->renderer->depthView(), o, *ck->error))
                return false;
        }
        if (ck->lines && !ck->lines->empty()) {
            render::DebugPrims::Options o = ck->primOptions;
            o.viewport = rect;
            if (!ck->prims->draw(target, frameView.viewProj, *ck->lines,
                                 ck->renderer->depthView(), o, *ck->error))
                return false;
        }
    }
    return true;
}

static SDL_AppResult tickFrontend(App& state) {
    App* app = &state;
    auto anyPressed = [&](fnd::input::Action action) {
        for (const auto& player : app->tickInput) if (player.just_pressed[action]) return true;
        return false;
    };
    ui::ScreenInput in;
    in.up      = anyPressed(fnd::input::Up);
    in.down    = anyPressed(fnd::input::Down);
    in.left    = anyPressed(fnd::input::Left);
    in.right   = anyPressed(fnd::input::Right);
    in.confirm = anyPressed(fnd::input::Jump);
    in.cancel  = anyPressed(fnd::input::AttackA);
    in.separatePlayers = true;
    for (int p = 0; p < 4; ++p) {
        const auto& input = app->tickInput[p];
        auto& buttons = in.players[p];
        buttons.up = input.just_pressed[fnd::input::Up];
        buttons.down = input.just_pressed[fnd::input::Down];
        buttons.left = input.just_pressed[fnd::input::Left];
        buttons.right = input.just_pressed[fnd::input::Right];
        buttons.confirm = input.just_pressed[fnd::input::Jump];
        buttons.cancel = input.just_pressed[fnd::input::AttackA];
    }
    const ui::ScreenId previousScreen = app->screens.current();
    app->screens.update(in);
    if (previousScreen != app->screens.current() && app->screens.current() == ui::ScreenId::Battle)
        app->lastTime = plat::now();
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

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate) {
    auto* app = static_cast<App*>(appstate);

    // Rendering measures wall time; combat and menu frame counters use 64 Hz ticks.
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
    } else if (!app->controllers.empty() && !app->matchMode && !app->frontendMatch) {
        advanceAnimation(*app, delta);
    }

    if (app->versusMode) tickVersus(*app, app->frames);
    if (app->matchInputReady) {
        app->matchInput.poll(false);
        app->matchInput.sample_tick_inputs(app->pendingInput);
    }
    pollUserSettings(*app, now);
    // The toon toggle is a draw-time switch (issue #21): the Options row flips live state
    // and the renderer's copy follows it here, so no scene re-upload and no restart is
    // behind the change. Only the interactive frontend reaches this (settingsActive is
    // false for every capture recipe), and an explicit --toon/--no-toon still wins.
    if (app->settingsActive && app->rendererReady) {
        const bool toon = app->opts.toonSet ? app->opts.toon
                                            : ui::frontendSettings().toonRendering;
        if (toon != app->appearance.toon) {
            app->appearance.toon = toon;
            app->renderer.setAppearance(app->appearance);
        }
    }
    // The animation browser owns its own clock rather than the match's fixed step, so the
    // clip advances at wall-clock rate and reads as a smooth player.
    if (app->opts.animPlayer) animPlayerTick(*app, delta);

    // While paused the clock is not advanced at all, so paused wall time cannot become
    // catch-up ticks when the pause ends; the paused ticks still run so the device queues
    // are drained and the menu can be driven (issue #15).
    const int ticks = capturing ? 1
                    : (app->battlePaused ? 1
                                         : app->logicClock.advance(app->frames > 1 ? delta : 0.0));
    app->matchAlpha = capturing ? 1.f : app->logicClock.alpha();
    for (int tick = 0; tick < ticks; ++tick) {
        ++app->logicTicks;
        for (int p = 0; p < 4; ++p) app->tickInput[p] = app->pendingInput[p].consume();
        driveSyntheticLocalPads(*app);
        if (app->matchInput.script_active()) {
            const uint64_t scriptTick = app->frontendMatch || app->screensMode
                ? app->logicTicks : app->matchFrame + 1 + app->pauseScriptAdvance;
            app->matchInput.sample_script(app->scriptInput, scriptTick);
            app->tickInput[0] = app->scriptInput;
        }
        if (app->matchMode) {
            if (app->battlePaused) {
                const SDL_AppResult result = tickBattlePause(*app);
                if (result != SDL_APP_CONTINUE) return result;
                continue;   // frozen: no match step, no animation, no counters this tick
            }
            if (battlePauseAvailable(*app) && battlePausePressed(*app)) {
                enterBattlePause(*app, "pause key");
                continue;
            }
            if (!capturing) advanceAnimation(*app, gameplay::FixedStep::seconds);
            tickMatch(*app, capturing ? app->opts.dt : gameplay::FixedStep::seconds);
            traceMatch(*app);
            // --local-players evidence: the per-view cameras/HUD values every 128 ticks,
            // bounded by the run's own length so a long run cannot flood the log.
            if (app->opts.localPlayers > 0 && app->matchFrame % 128 == 0)
                reportMatchViews(*app, capturing ? (uint32_t)app->opts.sizeW : app->sc.width,
                                 capturing ? (uint32_t)app->opts.sizeH : app->sc.height);
            if (app->frontendMatch && app->match.economy().roundOver()) {
                // The economy reports the WINNING side (issue #11); the DX9 port
                // reported the burst side here and this line inverted it.
                const gameplay::MatchEconomy& eco = app->match.economy();
                app->frontend.resultWinner = eco.roundOverSide();
                app->frontend.matchFrame = app->matchFrame;
                // The quote rule's inputs (FUN_00635d40:288-318): the balloon margin, clamped
                // by the winner's own capacity, and whether both winners ended below half HP.
                {
                    const int winner = std::max(0, app->frontend.resultWinner);
                    const int loser = 1 - winner;
                    const int winnerCapacity = (int)eco.capacity(winner);
                    const int loserBalloon = (int)eco.balloon(loser);
                    const int winnerBalloon = (int)eco.balloon(winner);
                    app->frontend.resultMargin =
                        std::min(winnerCapacity, loserBalloon) - winnerBalloon;
                    bool hurt = true;
                    for (int i = 0; i < app->match.config().fighterCount; ++i)
                        if (app->match.config().side[i] == winner &&
                            app->match.fighter(i).hp() * 2 >= app->match.fighter(i).max_hp())
                            hurt = false;
                    app->frontend.resultWinnersHurt = hurt;
                }
                for (int i = 0; i < app->match.config().fighterCount; ++i) {
                    const auto& stats = app->match.fighter(i).stats();
                    const int panel = app->battleLaunch.fighters[i].panel;
                    app->frontend.resultStats[panel] = {stats.kos,stats.deaths,stats.damageDealt,stats.damageTaken};
                    // The earned title (issue #20): the recovered record + chain. The port fills
                    // the fields it can evidence; the chain skips the conditions whose fields are
                    // not recovered and says so through `resolved`.
                    const int side = app->match.config().side[i];
                    gameplay::ResultRecord record;
                    record.teamCapacity = (int)eco.capacity(side);
                    record.enemyCapacity = (int)eco.capacity(1 - side);
                    record.koed = eco.koAt(i) >= 0 || !app->match.fighter(i).is_alive();
                    // The port's stats are not split by the fighter's lock, so the damage sits in
                    // the "others" bucket; the chain's split-specific damage conditions are among
                    // the skipped ones. UNIT: the original's record is HP-scale damage (10000 per
                    // fighter — FUN_00639160 subtracts the same value it credits from the victim's
                    // +0x7a4) while this port's kMaxHP is 100, so the ×100 puts the record in the
                    // unit the chain's `capacity * N / 100` thresholds are written in.
                    record.damageToOthers = stats.damageDealt * 100;
                    record.damageFromOthers = stats.damageTaken * 100;
                    record.hitsToTarget = app->titleHits[i].toTarget;
                    record.hitsToOthers = app->titleHits[i].toOthers;
                    record.hitsFromTarget = app->titleHits[i].fromTarget;
                    record.hitsFromOthers = app->titleHits[i].fromOthers;
                    record.hitsOnLocalPlayer = app->titleHits[i].onLocalPlayer;
                    bool resolved = false;
                    const int title = gameplay::resultTitleIndex(record, app->titleRng, &resolved);
                    static gameplay::ResultTitleTable titleTable;
                    static bool titleTableTried = false;
                    if (!titleTableTried) {
                        titleTableTried = true;
                        std::string titleError;
                        const std::string& install = fnd::assets::assetSource().installDir();
                        if (install.empty() ||
                            !gameplay::loadResultTitles(install + "/DaybreakDX.exe", titleTable,
                                                        titleError))
                            std::fprintf(stderr, "[title] names unavailable: %s\n",
                                         titleError.empty() ? "no install open" : titleError.c_str());
                    }
                    app->frontend.resultTitleText[panel] = titleTable.text(title);
                    // The penalty title's session flag (FUN_00635d40:377-380), keyed by the panel
                    // because that is a local player's stable identity here. Session state only:
                    // it is never written to any settings file.
                    if (title == gameplay::kResultTitlePenalty &&
                        app->frontend.slots[panel].controller < 4)
                        app->frontend.penaltyDecided[panel] = true;
                    std::printf("[title] panel %d fighter %d side %d ko=%d dmg=%d/%d "
                                "hits=%d+%d/%d+%d on1p=%d -> %d '%s'%s\n",
                                panel, i, side, record.koed ? 1 : 0, record.damageDealt(),
                                record.damageTaken(), record.hitsToTarget, record.hitsToOthers,
                                record.hitsFromTarget, record.hitsFromOthers,
                                record.hitsOnLocalPlayer, title, titleTable.text(title),
                                resolved ? "" : " (chain reached unrecovered conditions)");
                }
                app->matchMode = false;
                app->frontendBattleReady = false;
                app->versusAudio.clear_music();
                // The match is over: release every channel the combat layer claimed, so the
                // result screen's own cues and the next match start from a clean bus
                // (issue #16's repeated-match cleanup). The decoded sample cache stays.
                reportCombatAudio(*app);
                stopCombatAudio(*app);
                app->screens.request(ui::ScreenId::Result);
                app->screensMode = true;
                const SDL_AppResult result = tickFrontend(*app);
                if (result != SDL_APP_CONTINUE) return result;
            }
        } else if (app->screensMode) {
            const SDL_AppResult result = tickFrontend(*app);
            if (result != SDL_APP_CONTINUE) return result;
            // Loading a new battle must not turn asset-load time into combat ticks.
            if (app->matchMode) {
                app->lastTime = plat::now();
                return SDL_APP_CONTINUE;
            }
        }
    }

    if (app->matchMode) {
        placeFxCards(*app);
        placeMatchFighters(*app);
    }

    if (app->screensMode) {

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
        // This frame's views (issue #12): a match builds one per human controller — its own
        // camera, its own cell and its own HUD — while every other asset path keeps the one
        // historical view, whose matrix the scene and prims passes have always shared.
        // Match frames use the reference camera's own projection (fov pi/4, near 50,
        // far 150000) so a foundation frame and a banked DX9 frame of the same case differ
        // by their content, not by their projection.
        std::vector<FrameView> frameViews;
        std::vector<render::ViewCamera> frameCameras;
        glm::mat4 vp;
        if (app->matchMode) {
            buildFrameViews(*app, w, h, frameViews);
            for (const FrameView& view : frameViews) frameCameras.push_back(view.camera);
            vp = frameCameras.front().viewProj;
            // The primary view's interpolated presentation eye/aim: the paths that read
            // app.eye/app.target (billboard eye, debug crosses) stay on the first player.
            app->eye = frameCameras.front().eye;
            app->target = glm::mix(app->matchViews[0].previousTarget,
                                   app->matchViews[0].camera.target(), app->matchAlpha);
        } else {
            // Every other path: one view over the whole target, the matrix the scene and
            // prims passes have always shared in this branch.
            vp = viewProj(app->eye, app->target, (float)w / (float)h, app->cameraRadius,
                          app->sceneReach);
            render::ViewCamera camera;
            camera.viewProj = vp;
            camera.eye = app->eye;
            frameCameras.push_back(camera);
        }
        app->renderer.setCamera(vp);
        app->renderer.setEye(app->eye);

        if (capturing) {
            // --out without --frames means one frame, so the last frame is always defined.
            if (app->frames >= (uint64_t)app->opts.frames) {
                std::vector<uint8_t> rgba;
                HudTestHook hook = battleHudHook(*app);
                if (app->matchMode) appendMatchHudPasses(*app, frameViews, w, h, hook);
                const bool useHud = (app->opts.hudTest || app->versusMode || app->matchMode) &&
                                    app->uiReady;
                CaptureHook cap;
                cap.renderer = &app->renderer;
                cap.error = &app->error;
                cap.views = frameCameras;
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
                        if (app->opts.hitboxDebug) cap.hitbox = &app->hitboxCubes;
                    }
                }
                const bool useHook = useHud || cap.prims;
                // Only more than one view takes the split-screen scene pass; a single view
                // keeps render()'s exact commands (and the banked captures' pixels).
                const std::vector<render::ViewCamera>* viewArg =
                    app->matchMode && frameCameras.size() > 1 ? &frameCameras : nullptr;
                if (!app->renderer.capture((uint32_t)app->opts.sizeW,
                                           (uint32_t)app->opts.sizeH, rgba, app->error,
                                           useHook ? captureHook : nullptr,
                                           useHook ? &cap : nullptr, viewArg))
                    return SDL_APP_FAILURE;
                reportCoverage(rgba, app->opts.sizeW, app->opts.sizeH);
                writePpm(app->opts.out, rgba, app->opts.sizeW, app->opts.sizeH);
                if (app->opts.debugPrims) {
                    const render::DebugPrims::Stats& ds = app->debugPrims.stats();
                    std::printf("debug prims : %zu line(s), %zu vertices, %zu dropped, %zu pass(es)\n",
                                ds.lines, ds.vertices, ds.droppedVertices, ds.passes);
                }
                // The front-end battle runs the same Match as --match, so its end-of-run
                // summary (and issue #14's per-COM counters) is printed for it too.
                if (app->matchMode || app->frontendMatch) {
                    reportMatchViews(*app, w, h);
                    const gameplay::MatchEconomy& eco = app->match.economy();
                    std::printf("match: %llu frames, hp1=%d hp2=%d, balloon=%.0f%%/%.0f%% "
                                "(LIMIT %.0f%%/%.0f%%), shots=%llu sparks=%llu hits=%llu, "
                                "fx events=%llu, bgm pushed %llu frames, %llu wraps, roundOver=%d\n",
                                (unsigned long long)app->matchFrame, app->match.fighter(0).hp(),
                                app->match.fighter(1).hp(), (double)eco.balloon(0),
                                (double)eco.balloon(1), (double)eco.capacity(0),
                                (double)eco.capacity(1),
                                (unsigned long long)app->matchShots,
                                (unsigned long long)app->matchSparks,
                                (unsigned long long)app->matchHits,
                                (unsigned long long)app->matchFxEvents,
                                (unsigned long long)app->versusBgmPushed,
                                (unsigned long long)app->versusLoop.loops_completed(),
                                app->matchRoundOverFrame ? 1 : 0);
                    // Issue #11's single-counted audit: one KO credit per death, one
                    // Overkill credit per hit, one respawn per return.
                    std::printf("match round : winner=%d (%s), KOs=%d/%d overkill=%d/%d "
                                "respawns=%d/%d, time left=%.1fs\n",
                                eco.roundOverSide(),
                                eco.roundEnd() == gameplay::RoundEnd::Timeout ? "time up" :
                                (eco.roundEnd() == gameplay::RoundEnd::Burst ? "burst" : "running"),
                                eco.kos(0), eco.kos(1), eco.overkills(0), eco.overkills(1),
                                eco.respawns(0), eco.respawns(1), eco.timeLeft());
                    // Issue #14's per-COM counters (see printComSummary) and issue #17's
                    // effect population (see printFxSummary).
                    printComSummary(*app);
                    printFxSummary(*app);
                }
                if (app->versusMode) {
                    std::printf("versus: %llu frames, hp1=%.0f hp2=%.0f, bgm pushed %llu frames, %llu wraps, sfx plays %llu, fx events %llu\n",
                                (unsigned long long)app->frames, (double)app->versusHud.hp, 100.0,
                                (unsigned long long)app->versusBgmPushed,
                                (unsigned long long)app->versusLoop.loops_completed(),
                                (unsigned long long)app->versusSfxPlays,
                                (unsigned long long)app->versusFxEvents);
                    printFxSummary(*app);
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
        const bool multiView = app->matchMode && frameCameras.size() > 1;
        const bool sceneOk = multiView ? app->renderer.renderViews(target, frameCameras, app->error)
                                       : app->renderer.render(target, app->error);
        if (!sceneOk) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (app->opts.debugPrims || app->matchMode) {
            if (app->opts.debugPrims) fillDebugLines(*app);
            else app->debugLines.clear();
            if (app->matchMode) fillMatchCubes(*app);
            for (const render::ViewCamera& camera : frameCameras) {
                if (app->matchMode && !app->matchCubes.empty()) {
                    render::DebugPrims::Options cubeOptions;
                    cubeOptions.viewport = camera.rect;
                    if (!app->debugPrims.drawCubes(target, camera.viewProj, app->matchCubes,
                                                   app->renderer.depthView(), cubeOptions,
                                                   app->error)) {
                        gpu::endFrame(app->ctx, app->sc, frame);
                        return SDL_APP_FAILURE;
                    }
                }
                if (app->matchMode && app->opts.hitboxDebug && !app->hitboxCubes.empty()) {
                    // Straight alpha (not additive): the volume should tint what is behind
                    // it rather than blow out, so overlapping fighters stay readable.
                    render::DebugPrims::Options hitboxOptions;
                    hitboxOptions.viewport = camera.rect;
                    if (!app->debugPrims.drawCubes(target, camera.viewProj, app->hitboxCubes,
                                                   app->renderer.depthView(), hitboxOptions,
                                                   app->error)) {
                        gpu::endFrame(app->ctx, app->sc, frame);
                        return SDL_APP_FAILURE;
                    }
                }
                if (app->matchMode && !app->auraCubes.empty()) {
                    render::DebugPrims::Options cubeOptions;
                    cubeOptions.additive = true;
                    cubeOptions.viewport = camera.rect;
                    if (!app->debugPrims.drawCubes(target, camera.viewProj, app->auraCubes,
                                                   app->renderer.depthView(), cubeOptions,
                                                   app->error)) {
                        gpu::endFrame(app->ctx, app->sc, frame);
                        return SDL_APP_FAILURE;
                    }
                }
                // depth-tested: lines behind walls hide
                render::DebugPrims::Options primOptions;
                primOptions.viewport = camera.rect;
                if (!app->debugPrims.draw(target, camera.viewProj, app->debugLines,
                                          app->renderer.depthView(), primOptions, app->error)) {
                    gpu::endFrame(app->ctx, app->sc, frame);
                    return SDL_APP_FAILURE;
                }
            }
        }
        if (app->opts.animPlayer && app->uiReady && !app->scene.models.empty()) {
            char buf[160];
            const xm::Model& m = app->scene.models[0].model;
            const char* name = (app->apIndex >= 0 && app->apIndex < (int)m.anims.size())
                                   ? m.anims[app->apIndex].name.c_str() : "(none)";
            std::snprintf(buf, sizeof(buf), "[%d/%d]  %s", app->apIndex,
                          (int)m.anims.size(), name);
            const std::string line = buf;
            const std::string hint = "arrows: set index    WASD: orbit";
            std::string textError;
            if (app->apText.load(app->uiRenderer, 14.f, textError) &&
                app->apText.prepare(app->uiRenderer, {line, hint}, textError)) {
                app->uiRenderer.beginFrame(app->sc.width, app->sc.height);
                app->apText.draw(app->uiRenderer, line.c_str(), 24.f, 20.f, 1.f, ui::kHudWhite);
                app->apText.draw(app->uiRenderer, hint.c_str(), 24.f, 40.f, 1.f, ui::kHudWhite);
                if (!app->uiRenderer.render(frame.encoder, frame.view, app->sc.format, app->error)) {
                    gpu::endFrame(app->ctx, app->sc, frame);
                    return SDL_APP_FAILURE;
                }
            }
        }
        if (!drawBattlePauseOverlay(*app, frame.encoder, frame.view)) {
            gpu::endFrame(app->ctx, app->sc, frame);
            return SDL_APP_FAILURE;
        }
        if (app->uiReady && (app->opts.hudTest || app->matchMode || app->versusMode)) {
            HudTestHook hook = battleHudHook(*app);
            if (app->matchMode)
                appendMatchHudPasses(*app, frameViews, app->sc.width, app->sc.height, hook);
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
            if (event->key.key == SDLK_ESCAPE) {
                // A live offline battle: Escape opens the pause menu (or leaves it) instead
                // of killing the process — the audit's "Escape exits immediately" is what
                // this replaces. Every capture/replay path keeps the old behaviour, and so
                // does every menu screen.
                if (battlePauseAvailable(*app)) {
                    if (app->battlePaused) resumeBattle(*app);
                    else enterBattlePause(*app, "Escape");
                    return SDL_APP_CONTINUE;
                }
                return SDL_APP_SUCCESS;
            }
            if (app->opts.animPlayer && !event->key.repeat) animPlayerKey(*app, event->key.key);
            break;
        case SDL_EVENT_KEY_UP:
            app->matchInput.note_key((int)event->key.scancode, false);
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            // #6's safety fix: held keys are dropped so a lost KEY_UP cannot hold Guard.
            app->matchInput.note_focus_lost();
            // A live battle must not keep running (and keep taking damage) while the player
            // cannot see or control it, so focus loss pauses it. Regaining focus does NOT
            // auto-resume: the player resumes deliberately. A scripted verification run is
            // left alone — its script owns the pause state, and a stray focus event must not
            // make a recipe non-deterministic.
            if (battlePauseAvailable(*app) && !app->battlePaused &&
                !app->matchInput.script_active())
                enterBattlePause(*app, "focus lost");
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
            if (ui::bindingCaptureActive()) {
                const int player = app->matchInput.gamepad_player((int32_t)event->gbutton.which);
                app->matchInput.suppress_gamepad_button(player,(int)event->gbutton.button);
                ui::submitBindingInput(false, player, (int)event->gbutton.button);
            } else {
                const int player = app->matchInput.gamepad_player((int32_t)event->gbutton.which);
                app->matchInput.note_gamepad_button(player, (int)event->gbutton.button, true);
            }
            break;
        case SDL_EVENT_GAMEPAD_BUTTON_UP:
            app->matchInput.note_gamepad_button(
                app->matchInput.gamepad_player((int32_t)event->gbutton.which),
                (int)event->gbutton.button, false);
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
    flushUserSettings(*app);   // last chance for a change made after the last screen exit
    ui::frontendSettings().applyVolumes = {};
    ui::frontendSettings().applyFullscreen = {};
    ui::frontendSettings().applyResolution = {};
    ui::frontendSettings().applyBindings = {};
    report(*app);
    teardown(*app);
    delete app;
}
