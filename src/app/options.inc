// Command-line parsing, usage text and the --npr experiment switch family.
// Included by main.cpp inside its anonymous namespace: the app is one translation unit
// because the two tests compile main.cpp into their own TU (see the note there).


// ---------------------------------------------------------------------------------------
// Command line
// ---------------------------------------------------------------------------------------
struct Options {
    // Asset selection. Exactly one of stage/character/weapon/model, or none for the
    // triangle demo; an effect file may ride along with any of them.
    std::string model, stage, character, weapon, effect;
    bool        hudTest = false;   // composite a synthetic HUD into --out captures
    bool        hudProbe = false;  // --hud-probe: corner markers for the placement test
    // --pause-overlay=N: enter the battle pause at match frame N and composite the pause
    // overlay into the --out capture. The only way a headless run can photograph the pause
    // menu, which is otherwise reachable only by pressing the key in a live window.
    int         pauseOverlay = 0;
    bool        debugPrims = false; // draw the deterministic debug line overlay
    bool        audioTest = false; // run the audio backend self-check and exit
    bool        noAudio = false;
    bool        withAudio = false;
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
    float       dt   = static_cast<float>(gameplay::FixedStep::scriptedCaptureSeconds);

    std::string camera = "auto";   // auto|player|front|top|bounds
    bool        headless = false;  // no window/surface: offscreen captures only
    std::string install;           // dir holding daybreakXX.dat; auto-detected when empty
    bool        noCameraClamp = false;   // A/B switch for the arena eye clamp
    bool        noTextures = false;
    bool        fog        = false;   // opt-in: the DX9 reference renders unfogged
    bool        noAnim     = false;   // bind pose: the DX9 reference binds no sets
    // Interactive animation browser: one rig, no stage, arrows change the set index
    // and WASD orbits the camera. Exists because the state's anim-set table has
    // unmapped entries (Jump/Guard/TagOut return -1) and set 2 does not look like an
    // attack, which is only checkable by looking at the clips side by side.
    bool        animPlayer = false;
    // Effect cards play their model's animation (default). Off reproduces the bind-pose
    // draw the port had before V3-34, for before/after captures and for rollback.
    bool        fxAnimation = true;
    bool        unlit      = false;
    // Toon rendering (issue #21). `toonSet` separates "the flag was passed" from the
    // default: without it the live Options row governs, with it the flag wins — so a
    // capture command line pins the state it asked for, and an interactive run is never
    // overridden by a stale flag.
    bool        toon       = false;
    bool        toonSet    = false;
    // Character shadows (issue #21 row 1). Same `Set` split as the toon row: without the
    // flag the live Options row governs, with it the capture command line wins.
    bool        shadows    = false;
    bool        shadowsSet = false;
    // NPR experiment switches (issue #25). `nprSet` separates "the flag was passed" from
    // the default for the same reason `toonSet` does: a capture command line pins the
    // state it asked for, and an interactive run is never overridden by a stale flag.
    // The whole family lives in one Appearance, built by parseNprSpec below.
    render::Appearance npr{};
    bool        nprSet     = false;
    // Stepped animation presentation (issue #25 experiment J): quantise the pose clock to
    // this many updates per second while the frame rate is untouched. 0 = off, and off is
    // the only state any existing capture is in.
    float       poseStep   = 0.f;
    // --bench=N (issue #25): render N frames of the capture scene back to back, waiting
    // for the GPU after each, and print the mean frame time. 0 = off.
    int         bench      = 0;
    bool        list       = false;
    std::string screen;          // --screen=<id|name>: boot a front-end screen
    // --movie=<path>: which file the opening scene plays (default data/movie/op.mpg — the
    // original's FUN_00404eb0 @0x404eb0 opens it as "movie/op.mpg" from its data/ working
    // directory). The staff roll is the same player and the same scene kind, so it is driven
    // through this one screen rather than a second one. Naming a movie implies that scene,
    // like naming an asset implies its viewer.
    std::string movie;
    // A plain interactive launch boots scene 0x00 like the original does, unless a
    // verification run owns the input (issue #40's criterion 4). Resolved after parsing,
    // because it depends on the whole flag set; see resolveBootOpening.
    bool        bootOpening = false;
    // Split-screen verification (issue #12): open this many local human views by
    // assigning controllers 0..N-1 to the battle panels, so a headless run exercises the
    // per-controller camera/HUD path. 0 (default) keeps the historical single-view flow.
    int         localPlayers = 0;
    // --lock-taps: let those synthetic pads also tap LockSwitch (the per-view combat-target
    // cycle; issue #51 — the gesture never re-points a camera). Off by default so an
    // evidence run's fighters hold their targets and their framing stays put.
    bool        lockTaps = false;
    // --match-alpha=<fraction> (issue #39): the presentation blend every rendered frame uses,
    // overriding the product rule matchAlphaFor applies. Unset (< 0) keeps that rule — 1 while
    // capturing (D9's one-update-per-frame recipes, where the blend must return the current
    // camera so banked captures stay byte-identical) and the live clock's own fraction
    // otherwise. A fixed fraction is what lets a HEADLESS recipe render the presentation
    // interpolation buildFrameViews applies; at alpha 1 that blend is the identity, which is
    // why the live camera defect (92b6d70) survived every capture-based gate.
    float       matchAlpha = -1.f;
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
        "usage: daybreak [<model.x> | --model=<file.x> | --stage=<dir> |\n"
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
        "  --no-fx-anim       draw effect cards in bind pose (the pre-V3-34 behaviour),\n"
        "                     for before/after comparison and as a rollback switch\n"
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
        "  --npr=<spec>       NPR experiment harness (issue #25), comma-separated and\n"
        "                     applied left to right. Off by default; OFF is byte-identical\n"
        "                     to the pre-experiment renderer. Modifiers:\n"
        "                       off|on            all experiments off / the suggested stack\n"
        "                       bands:hard|soft|three   the B curve (soft width via soft:<f>)\n"
        "                       shadow:<#rrggbb>|none   the C shadow tint\n"
        "                       key:fixed|cam|off, keydir:<x,y,z>, keystr:<f>   the D key\n"
        "                       normals|nonormals, mask:<f>   the E/F secondary normals\n"
        "                       spec|nospec, spectint:<#rrggbb>, specstr:<f>   the G specular\n"
        "                       rim|norim, rimtint:<#rrggbb>, rimstr:<f>      the H rim\n"
        "                       outline:<f>       the recovered hull width x this (I)\n"
        "  --pose-step=<n>    stepped pose presentation (experiment J): pose updates per\n"
        "                     second while the frame rate is untouched. 0 = off\n"
        "  --bench=<n>        with --out: render n frames of the same scene back to back,\n"
        "                     waiting for the GPU after each, and print the mean frame time.\n"
        "                     This is the only number a headless run can quote for a\n"
        "                     technique's cost (the per-iteration delta is a CPU loop delta)\n"
        "  --toon | --no-toon toon rendering (issue #21): the character and weapon draws\n"
        "                     read the shipped data/directX/toon ramp at their diffuse\n"
        "                     term instead of the linear N.L. Off by default, which is the\n"
        "                     state every banked capture was made in\n"
        "  --shadows | --no-shadows\n"
        "                     character shadows (issue #21 row 1): every fighter's body\n"
        "                     and weapon are drawn once more into a light-space map the\n"
        "                     stage samples, so the fighters cast a shadow on the ground.\n"
        "                     Off by default, the state every banked capture was made in\n"
        "  --list             print what was loaded and exit\n"
        "  --screen=<id|name> boot a front-end screen (title, 1, 0x01, ...) instead of\n"
        "                     an asset; --script= drives its menu and --out captures it.\n"
        "                     With no --screen and no asset, an interactive launch boots\n"
        "                     the opening scene (0x00) like the original; a verification\n"
        "                     run (--out/--headless/--script/...) never does, so no\n"
        "                     evidence run pays for the movie decode (issue #40)\n"
        "  --movie=<path>     which movie to play, relative to the install (default\n"
        "                     data/movie/op.mpg); implies --screen=opening. staffroll.mpg\n"
        "                     runs through the same player this way\n"
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
        "  --no-audio           silence music, voices, effects and movie audio\n"
        "  --with-audio         enable sound for intentional listening checks;\n"
        "                      verification and --frames runs are silent by default\n"
        "  --combat-audio-log   log every dispatched combat SE/voice with its resolved file\n"
        "  --audio-file=<path>  with --audio-test: decode a real file as well\n"
        "  --input-test         run the input backend self-check and exit\n"
        "  --enemy=<baseDir>/<name>[:costume]  versus P2 fighter (needs --versus)\n"
        "  --versus           scripted vignette: stage + P1 + P2, arena follow,\n"
        "                     timeline HUD, BGM loop, SFX cues; needs --stage,\n"
        "                     --character, --enemy and --frames>=30\n"
        "  --bgm=<file.ogg>   versus BGM track played through the loop player\n"
        "  --sfx=<file.cnv>    versus hit cue fired at scripted hits\n"
        "  --match            playable match on the vendored core: needs --stage and\n"
        "                     --sim-roster\n"
        "  --script=<file>    P1 input script for --match (\"<frame> TOKEN...\" lines,\n"
        "                     the DX9 visual-suite format); absent -> live device\n"
        "  --script2=<file>   P2 input script; absent -> P2 takes no input (dummy,\n"
        "  --sim-roster=<a>,<b>,<c>,<d>  with --match: four <dir>/<name>[:costume][@weaponSlot]\n"
        "                     exactly what the DX9 scene does)\n"
        "  --local-players=N  verification: open N local human views (1..4) by assigning\n"
        "                     controllers 0..N-1 to the battle panels and give a\n"
        "                     controller with no attached pad a deterministic synthetic\n"
        "                     press pattern. Synthetic input is not physical-pad evidence;\n"
        "                     a real pad for that controller takes precedence\n"
        "  --lock-taps        let the synthetic pads tap LockSwitch too (the per-view\n"
        "                     combat-target cycle; a camera is never re-pointed). Off by\n"
        "                     default: four views each re-picking targets is churn an\n"
        "                     evidence run does not need\n"
        "  --match-alpha=<f>  render every frame at this fixed presentation fraction (0..1)\n"
        "                     instead of the product rule (1 while capturing, the live\n"
        "                     clock's own fraction otherwise). A capture then renders the\n"
        "                     live interpolation buildFrameViews applies, which alpha 1\n"
        "                     collapses to the current tick; absent, nothing changes\n"
        "With no asset argument the spinning-triangle demo runs.\n");
}

// ---------------------------------------------------------------------------------------
// --npr=<spec> (issue #25): the experiment harness's one switch family.
//
// The spec is a comma-separated list of modifiers, applied left to right, so a capture
// command line reads as the state it wants and a composed arm is a longer list rather
// than a new flag:
//
//   off            every experiment off (the default, and the state the shader's
//                  arithmetic is the pre-#25 arithmetic in)
//   on             the issue's suggested D/E stack: soft bands, a camera-relative key,
//                  secondary normals, a restrained rim. Deliberately not "everything":
//                  the recommended set is the experiment's own hypothesis and a capture
//                  must be able to test it as one arm.
//   bands:hard|soft|three   the B experiment's three curves (soft is the default width)
//   soft:<f>       the smoothstep's half-width (default 0.06)
//   shadow:<#rrggbb>|none   the C experiment's tint (default a warm skin shadow)
//   key:fixed|cam|off       the D experiment's arm; a weak key beside the world light
//   keydir:<x,y,z> the character-relative key direction (NprKey::Fixed)
//   keystr:<f>     the key's strength relative to the world light's diffuse (default 0.35)
//   normals|nonormals       light the secondary normals (E) while keeping the mesh
//   mask:<f>       scale on the generated shadow mask (F); 0 ignores it
//   spec|nospec    stylized hard-threshold specular (G), tint from `spectint`
//   spectint:<#rrggbb>, specstr:<f>
//   rim|norim      character-only rim light (H), tint from `rimtint`
//   rimtint:<#rrggbb>, rimstr:<f>
//   outline:<f>    the recovered hull width times this (I); 1 is the recovered value
//
// Every colour defaults to neutral except the shadow tint, which defaults to the warm
// skin shadow the issue names first: an experiment that has to be told its own colour is
// one nobody can compare against the arm that has none.
// ---------------------------------------------------------------------------------------
bool parseNprColour(const std::string& text, glm::vec3& out) {
    if (text.size() != 7 || text[0] != '#') return false;
    unsigned rgb = 0;
    for (int i = 1; i < 7; ++i) {
        const char c = text[(size_t)i];
        const int digit = (c >= '0' && c <= '9')   ? c - '0'
                          : (c >= 'a' && c <= 'f') ? c - 'a' + 10
                          : (c >= 'A' && c <= 'F') ? c - 'A' + 10
                                                   : -1;
        if (digit < 0) return false;
        rgb = rgb * 16u + (unsigned)digit;
    }
    out = glm::vec3(((rgb >> 16) & 0xFF) / 255.f, ((rgb >> 8) & 0xFF) / 255.f,
                    (rgb & 0xFF) / 255.f);
    return true;
}

bool parseNprSpec(const std::string& spec, render::Appearance& a, std::string& error) {
    size_t pos = 0;
    while (pos <= spec.size()) {
        const size_t comma = spec.find(',', pos);
        std::string item = spec.substr(pos, comma == std::string::npos ? std::string::npos
                                                                      : comma - pos);
        pos = comma == std::string::npos ? spec.size() + 1 : comma + 1;
        if (item.empty()) continue;
        std::string arg;
        const size_t colon = item.find(':');
        if (colon != std::string::npos) {
            arg = item.substr(colon + 1);
            item = item.substr(0, colon);
        }
        // Compound modifiers whose argument is not a number are matched whole, before the
        // split above can mistake their value for a sub-modifier.
        if (item == "bands" && (arg == "hard" || arg == "soft" || arg == "three")) {
            a.bands = arg == "hard"   ? render::NprBands::Hard
                      : arg == "three" ? render::NprBands::Three
                                       : render::NprBands::Soft;
            continue;
        }
        if (item == "shadow" && arg == "none") {
            a.shadowTint = glm::vec3(1.f);
            continue;
        }
        if (item == "key" && (arg == "fixed" || arg == "cam" || arg == "off")) {
            a.key = arg == "cam"   ? render::NprKey::Camera
                    : arg == "off" ? render::NprKey::Off
                                   : render::NprKey::Fixed;
            continue;
        }
        const float value = (float)std::atof(arg.c_str());
        if (item == "off") {
            // The experiment state only: `--npr=off` must not disturb --toon/--no-toon,
            // which is the recovered row and not part of this harness.
            const bool fog = a.fog;
            a = render::Appearance{};
            a.fog = fog;
        } else if (item == "on") {
            a.bands = render::NprBands::Soft;
            a.shadowTint = glm::vec3(0.88f, 0.78f, 0.82f);
            a.key = render::NprKey::Camera;
            a.smoothedNormals = true;
            a.rim = true;
            a.rimStrength = 0.22f;
            a.rimTint = glm::vec3(1.f, 0.97f, 0.92f);
        } else if (item == "bands") {
            a.bands = render::NprBands::Soft;
        } else if (item == "soft") {
            a.bandSoftness = value;
        } else if (item == "shadow") {
            // Bare `shadow` keeps the appearance's default tint (the warm violet-grey the
            // header documents) and only turns the experiment on; an explicit colour is
            // the authoring override.
            if (!arg.empty() && !parseNprColour(arg, a.shadowTint)) {
                error = "--npr=shadow: wants #rrggbb, got '" + arg + "'";
                return false;
            }
            if (a.bands == render::NprBands::Off) a.bands = render::NprBands::Soft;
        } else if (item == "key") {
            a.key = render::NprKey::Fixed;
        } else if (item == "keydir") {
            if (std::sscanf(arg.c_str(), "%f,%f,%f", &a.keyDir.x, &a.keyDir.y, &a.keyDir.z) != 3) {
                error = "--npr=keydir: wants x,y,z, got '" + arg + "'";
                return false;
            }
        } else if (item == "keystr") {
            a.keyStrength = value;
        } else if (item == "normals") {
            a.smoothedNormals = true;
        } else if (item == "nonormals") {
            a.smoothedNormals = false;
        } else if (item == "mask") {
            a.normalMaskBias = value;
        } else if (item == "spec") {
            a.specular = true;
        } else if (item == "nospec") {
            a.specular = false;
        } else if (item == "spectint") {
            if (!parseNprColour(arg, a.specTint)) {
                error = "--npr=spectint: wants #rrggbb, got '" + arg + "'";
                return false;
            }
        } else if (item == "specstr") {
            a.specStrength = value;
        } else if (item == "rim") {
            a.rim = true;
        } else if (item == "norim") {
            a.rim = false;
        } else if (item == "rimtint") {
            if (!parseNprColour(arg, a.rimTint)) {
                error = "--npr=rimtint: wants #rrggbb, got '" + arg + "'";
                return false;
            }
        } else if (item == "rimstr") {
            a.rimStrength = value;
        } else if (item == "outline") {
            a.outlineScale = value;
        } else {
            error = "--npr: unknown modifier '" + item + "'";
            return false;
        }
    }
    return true;
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
        else if (!(v = val("--sim-roster=")).empty()) {
            std::stringstream roster(v);
            std::string spec;
            int count = 0;
            while (count < 4 && std::getline(roster, spec, ',')) {
                // <dir>/<name>[:costume][@weaponSlot]
                const size_t at = spec.find('@');
                if (at != std::string::npos) {
                    const int character = gameplay::characterIndexForDir(charDirForSpec(spec.substr(0, at)));
                    const int slot = std::atoi(spec.c_str() + at + 1);
                    if (character >= 0 && slot >= 0 && slot < gameplay::weaponCountForCharacter(character)) {
                        char item[32];
                        std::snprintf(item, sizeof item, "data/bullet/%03d", gameplay::kWeaponIds[character][slot]);
                        o.battleWeapons[count] = item;
                    }
                    spec.resize(at);
                }
                o.battleCharacters[count++] = spec;
            }
            o.battleFighterCount = count;
            if (count >= 2) { o.character = o.battleCharacters[0]; o.enemy = o.battleCharacters[1]; }
        }
        else if (!(v = val("--size=")).empty()) {
            const size_t x = v.find('x');
            o.sizeW = std::atoi(v.c_str());
            o.sizeH = (x == std::string::npos) ? o.sizeW : std::atoi(v.c_str() + x + 1);
        }
        else if (!(v = val("--frames=")).empty()) o.frames = std::atoi(v.c_str());
        else if (!(v = val("--anim=")).empty()) o.anim = std::atoi(v.c_str());
        else if (a == "--anim-player") o.animPlayer = true;
        else if (a == "--no-fx-anim") o.fxAnimation = false;
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
        else if (a == "--shadows") { o.shadows = true; o.shadowsSet = true; }
        else if (a == "--no-shadows") { o.shadows = false; o.shadowsSet = true; }
        else if (!(v = val("--npr=")).empty()) {
            if (!parseNprSpec(v, o.npr, error)) return false;
            o.nprSet = true;
        }
        else if (!(v = val("--bench=")).empty()) {
            o.bench = std::atoi(v.c_str());
            if (o.bench < 0) {
                error = "--bench takes a frame count";
                return false;
            }
        }
        else if (!(v = val("--pose-step=")).empty()) {
            o.poseStep = (float)std::atof(v.c_str());
            if (o.poseStep < 0.f) {
                error = "--pose-step takes a non-negative updates-per-second rate";
                return false;
            }
        }
        else if (a == "--list") o.list = true;
        else if (a == "--hud-test") o.hudTest = true;
        else if (a == "--hud-probe") { o.hudTest = true; o.hudProbe = true; }
        else if (!(v = val("--pause-overlay=")).empty()) {
            o.pauseOverlay = std::atoi(v.c_str());
            if (o.pauseOverlay <= 0) {
                error = "--pause-overlay takes a match frame > 0";
                return false;
            }
        }
        else if (a == "--debug-prims") o.debugPrims = true;
        else if (!(v = val("--install=")).empty()) o.install = v;
        else if (a == "--no-camera-clamp") o.noCameraClamp = true;
        // Debug overlay: draw the recovered melee hit spheres (issue #10). Off by
        // default so no capture and no trace is affected by it.
        else if (a == "--headless") o.headless = true;
        else if (a == "--audio-test") o.audioTest = true;
        else if (a == "--no-audio" || a == "-no-audio") o.noAudio = true;
        else if (a == "--with-audio") o.withAudio = true;
        else if (a == "--combat-audio-log") o.combatAudioLog = true;
        else if (a == "--input-test") o.inputTest = true;
        else if (!(v = val("--enemy=")).empty()) o.enemy = v;
        else if (a == "--versus") o.versus = true;
        else if (a == "--match") o.match = true;
        else if (!(v = val("--script=")).empty()) o.script = v;
        else if (!(v = val("--script2=")).empty()) o.script2 = v;
        else if (!(v = val("--screen=")).empty()) o.screen = v;
        else if (!(v = val("--movie=")).empty()) o.movie = v;
        else if (!(v = val("--bgm=")).empty()) o.bgm = v;
        else if (!(v = val("--sfx=")).empty()) o.sfx = v;
        else if (!(v = val("--local-players=")).empty()) o.localPlayers = std::atoi(v.c_str());
        else if (!(v = val("--match-alpha=")).empty()) {
            char* end = nullptr;
            o.matchAlpha = std::strtof(v.c_str(), &end);
            if (end == v.c_str() || *end != '\0' ||
                !(o.matchAlpha >= 0.f && o.matchAlpha <= 1.f)) {
                error = "--match-alpha takes a fraction in [0,1]";
                return false;
            }
        }
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
    if ((!o.script.empty() || !o.script2.empty()) && !o.match && o.screen.empty()) {
        error = "--script/--script2 need --match or --screen";
        return false;
    }
    if (o.headless && o.out.empty()) {
        error = "--headless needs --out: there is no window to present to";
        return false;
    }
    if (!o.movie.empty() && !o.screen.empty()) {
        // Same parse the boot uses, so "opening", "0x00" and "screen:opening" all agree.
        ui::ScreenId id = ui::ScreenId::Quit;
        if (!ui::parseScreenId(o.screen.c_str(), id) || id != ui::ScreenId::Opening) {
            error = "--movie needs --screen=opening: that is the scene that plays a movie";
            return false;
        }
    }
    if (!o.out.empty()) {
        if (!hasAsset(o) && o.screen.empty() && o.movie.empty()) {
            error = "--out needs an asset argument; the triangle demo draws into the window";
            return false;
        }
        if (o.frames == 0) o.frames = 1;   // a capture with no frame count means one frame
    } else if (o.pauseOverlay > 0) {
        error = "--pause-overlay is a capture instrument: it needs --out";
        return false;
    }
    for (const char* mode : {"auto", "player", "front", "top", "bounds", "arena"})
        if (o.camera == mode) return true;
    error = "unknown --camera=" + o.camera;
    return false;
}

// A "verification run" produces evidence rather than being played: --out= writes a
// frame, --headless has no window to play in, --script=/--script2= take their input from
// a file, --match/--versus are the standalone harness vignettes (the front end is the
// product path), --hud-test is the HUD test rig, --bench= measures cost and --list
// enumerates the assets and exits. It is used to default the audio output to muted.
// Physical input is NOT gated by it: the devices are always read, and an unfocused window
// simply ignores them (input_backend's focus gate).
static bool verificationRun(const Options& o) {
    return o.headless || !o.out.empty() || !o.script.empty() || !o.script2.empty() ||
           o.match || o.versus || o.hudTest || o.bench > 0 || o.list;
}

// A plain interactive launch is the original's boot: scene 0x00, the opening movie, then
// the title. Everything else keeps the behaviour it had — an explicit --screen, an asset
// viewer, and every verification run (which is exactly the runs whose startup must not
// carry a 22.7 MB decode, issue #40's criterion 4). PORT RULE: the original has no such
// switch, it simply boots scene 0x00 every time; the set that opts out is the port's.
static bool resolveBootOpening(const Options& o) {
    if (!o.screen.empty() || hasAsset(o)) return false;
    if (!o.movie.empty()) return true;   // --movie names the scene it belongs to
    return !verificationRun(o);
}
