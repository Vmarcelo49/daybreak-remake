// Types shared by the app translation unit.
// Included by main.cpp inside its anonymous namespace. The app is one
// translation unit: tests/controller_scene_lifetime_test.cpp and
// tests/windows_startup_smoke.cpp compile main.cpp into their own TU and drive
// these definitions.
#pragma once

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
    // --story=D41-0: which script scene 8 plays, with --screen=storyadv.
    std::string story;
    // --story-team=N: runs team N's six fights (the team-select scene does this in play).
    int storyTeam = -1;
    // --story-fight=F:P starts that team at fight F, part P (0 before the battle, 1 after).
    std::string storyFight;
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

struct Mat4 {
    float m[16];
};

struct BattleEntryScreen final : ui::Screen {
    ui::ScreenId update(const ui::ScreenInput&) override { return ui::ScreenId::Battle; }
    void draw(ui::SpriteRenderer&) const override {}
    const char* name() const override { return "battle"; }
};

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
    // The result screen draws over the battle it concludes (FUN_0063a740), which keeps running.
    bool                         resultOverScene = false;
    bool                         frontendMatch = false;
    bool                         frontendBattleReady = false;
    bool                         rendererReady = false;
    ui::FrontendState            frontend;
    fnd::audio::Sdl3Engine        menuAudio;
    // The opening movie's own output stream (issue #40): the original plays its audio
    // beside the front end's BGM, and one engine has one music stream, so the movie gets
    // its own. Lazily opened by the movie's first PCM frame.
    ui::MovieAudio                movieAudio;
    fnd::audio::SfxHandle         menuSounds[4] = {-1, -1, -1, -1};
    uint64_t                     menuSoundPlays[4] = {};
    uint64_t                     menuVoicePlays = 0;
    bool                         storyEscape = false;
    uint64_t                     menuBgmPushed = 0;  // frames the menu stream accepted
    fnd::audio::DecodedOgg        menuBgm;
    fnd::audio::LoopPlayer        menuLoop;
    // Which track menuBgm currently holds. A scene's music is started when its fade BEGINS
    // (see playFrontendMusic), so the factory's construction-time call must not restart the
    // same track 25 frames later; this is what lets it tell "already playing" from "new".
    std::string                   menuBgmPath;
    ui::HudComposer              hudComposer;
    bool                         uiReady = false;
    // The pause overlay's own batch (issue #50): a second SpriteRenderer, so the overlay's
    // pass and the battle HUD's passes cannot read each other's queued geometry. See
    // drawBattlePauseOverlay for what a shared one did.
    ui::SpriteRenderer           pauseUi;
    bool                         pauseUiReady = false;
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
    // The vendored core drives the battle; `battle` is all the product reads.
    sim::CoreBattle              coreBattle;
    game::Battle*                battle = &coreBattle;
    std::deque<xm::Controller>   coreShotControllers;   // this frame's shot poses
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
    // --local-players' menu clock: the tick the selection screen appeared, so the synthetic
    // pads' panel walk is timed from the screen and not from process start. Every entry is a
    // fresh selection (issue #45: FrontendState::beginSelection), so every appearance runs the
    // same walk.
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
    std::vector<std::array<std::unique_ptr<gameplay::BulletParameter>, 64>> bulletParams;
    // Parsed data/<char>/NN.dat move tables, indexed by fighter (issue #26). Owned
    // here so the pointers MatchConfig::moves hands out outlive the match. Empty
    // when the rig's .dat cannot be found, which keeps the legacy shared swing.
    std::vector<std::unique_ptr<gameplay::CharacterMoves>> moveDefs;
    uint64_t                     matchRoundOverFrame = 0;
    game::EffectEventQueue       matchFx;
    uint64_t                     matchFxEvents = 0;
    // B1/issue #17: the live effect cards the renderer draws from the event queues
    // above. A card's `asset` is a scene-model index (the catalog's, or an attachment
    // slot's); `liveFx` is this frame's card set, owned here — the set itself
    // (game::LiveFxCard) and its update rules live in render/fx_cards.h, unit-tested in
    // tests/fx_cards_test.cpp.
    // Issue #17: the effect table. `fxCatalog` maps an effect id (type*10+variant,
    // data/effect/%03d.dat) to its loaded card and its recovered lifetime; `fxAttach`
    // holds FUN_00633ca0's seven data/aura/%02d.x attachment models, whose textures are
    // the three muzzle flashes (slots 0/1/5), the blue hit (2) and the burning aura (3).
    game::EffectCatalog fxCatalog;
    int  fxAttach[game::kAuraSlots] = {-1, -1, -1, -1, -1, -1, -1};
    float fxAttachSeconds[game::kAuraSlots] = {};
    // Issue #32: the in-flight shot's own model, [fighter][chargeLevel-1]. The path is the
    // 260-byte model block of that level's data/bullet/<weaponId>/<type>.dat, resolved by
    // bindShotModels() once the scene is loaded; -1 when the level has no bullet file or
    // its block names a model the install does not ship. See render/shot_visual.h.
    std::array<std::array<int,64>,4> fxShotModel{};
    std::array<std::array<int,2>,4> trailModels{{{{-1,-1}},{{-1,-1}},{{-1,-1}},{{-1,-1}}}};
    xm::Model actionCameraModel;
    uint64_t fxShotNoModel = 0;      // live-shot placements with no model to draw
    // The eleven attach points of render/aura_attach.h, resolved once per fighter on its own
    // rig: the aura attachment draws one instance per resolved point (FUN_004205e0).
    game::AuraAttach auraAttach[4];
    // One instance id per spawned card, monotonic for the whole run: two hits in the
    // same tick are two instances and neither can retire the other (render/fx_cards.h).
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
    std::unique_ptr<CombatSink>   combatSink;
    std::unique_ptr<fnd::audio::CombatAudio> combatAudio;
    std::unordered_map<std::string, fnd::audio::SfxHandle> combatSamples;  // stem -> handle
    uint64_t                     combatVoicePlays = 0, combatSePlays = 0;
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

// The roster, stage and seed handed to the core.
struct MatchSetup {
    int healthPercent = 100, gaugePercent = 100;
    int timeLimit = 0;
    int balloonSize[2] = {100, 100};
    int fighterCount = 0;
    game::Hypermode hyper[4] = {game::Hypermode::Friendship, game::Hypermode::Oyashiro,
                                game::Hypermode::Friendship, game::Hypermode::Oyashiro};
    const gameplay::WeaponDefinition* weapon[4] = {};
    const gameplay::CharacterMoves* moves[4] = {};
};


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
    bool                    syntheticWhenEmpty = true;  // --hud-test; a match with no pass draws none
};


// The --screen capture's one hook: drawScreenFrame is the same three calls the window
// path makes, so a --out capture cannot drift from what the window shows.
struct ScreenCaptureHook {
    const ui::ScreenStack* screens = nullptr;
    ui::SpriteRenderer*    ui = nullptr;
    std::string*           error = nullptr;
    bool                   overlay = false;   // over a rendered scene, not a menu frame
};

// scene pass creates it, and a capture-sized run has no earlier render to borrow from.
struct CaptureHook {
    render::SceneRenderer*        renderer = nullptr;
    HudTestHook*                  hud = nullptr;    // null -> no UI pass
    render::DebugPrims*           prims = nullptr;  // null -> no prims pass
    const render::DebugLineBatch* lines = nullptr;
    const render::CubeBatch*      solid = nullptr;   // shots + sparks (opaque)
    const render::CubeBatch*      additive = nullptr;   // hypermode auras
    // One entry per view for the overlay passes: the same matrix and cell the scene pass
    // drew with, so a view's cubes and lines land in that view (issue #12). An entry with
    // an empty rect is the single-view frame, whose passes keep the full-target viewport.
    std::vector<render::ViewCamera> views;
    render::DebugPrims::Options   primOptions;
    std::string*                  error = nullptr;
    // The paused capture's App, so the frame carries the pause overlay in the live frame's
    // own order (overlay first, HUD passes over it). Null in every unpaused capture, which
    // is every capture but --pause-overlay=N. `void*` because App lives in this file's
    // anonymous namespace while CaptureHook is what the tests include.
    void*                         pauseApp = nullptr;
};

