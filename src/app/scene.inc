// Scene and match assembly: asset loading, the weapon/move tables, the versus
// vignette, the core battle setup and the renderer/scene teardown.
// Included by main.cpp inside its anonymous namespace.

// ---------------------------------------------------------------------------------------
// Scene assembly and camera (mirrors the reference tool's --stage/--character/--weapon
// handling, which is itself the shape of FUN_004011f0 / FUN_0064ab30 / FUN_00433eb0)
// ---------------------------------------------------------------------------------------
// Loads one character spec (base/name[:costume]) into the scene, returning the
// first appended model index. Shared by --character, --enemy and versus P2 so
// the three spellings cannot drift apart.
static bool resolveFighterWeapon(const std::string& charDir, const std::string& explicitSpec,
                                 std::string& meshSpec, int& itemId);
static size_t appendCharacter(xm::Scene& scene, const std::string& spec,
                             const xm::SceneOptions& sopt, const std::string& weaponSpec = {}) {
    std::string s;
    int costume = 0;
    splitSuffix(spec, s, costume);
    const size_t slash = s.find_last_of("/\\");
    const std::string base = (slash == std::string::npos) ? "." : s.substr(0, slash);
    const std::string name = (slash == std::string::npos) ? s : s.substr(slash + 1);
    const size_t begin = scene.models.size();
    xm::SceneOptions characterOptions = sopt;
    const int character = gameplay::characterIndexForDir(name);
    if (character >= 0) {
        std::string mesh;
        int item = 0;
        if (!resolveFighterWeapon(name,weaponSpec,mesh,item))
            throw std::runtime_error(spec + ": equipped weapon cannot be resolved");
        characterOptions.characterWeaponSlot = gameplay::weaponSlotForItem(character,item);
        characterOptions.requireCharacterData = true;
    }
    xm::Scene c = xm::loadCharacter(base, name, costume, characterOptions);
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
                                const std::string& weaponSpec, size_t ownerRig,
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
        // variant (docs/ASSET-CATALOG.md §1, docs/archive/FULL-REPLACEMENT-PLAN.md §6a).
        std::printf("stage        : %s\n", assets::describeStage(o.stage).c_str());
        if (o.match && o.battleFighterCount > 0) {
            for (int i = 0; i < o.battleFighterCount && i < 4; ++i) {
                const size_t rig = appendCharacter(scene, o.battleCharacters[i], sopt, o.battleWeapons[i]);
                if (i == 1 && enemyBegin) *enemyBegin = rig;
                const size_t character = firstCharacter(scene, rig);
                if (character >= scene.models.size()) throw std::runtime_error("battle fighter rig is missing");
                attachFighterWeapon(scene, "fighter " + std::to_string(i),
                                    o.battleCharacters[i], o.battleWeapons[i],
                                    character, sopt);
            }
            scene.source = o.stage;
            return scene;
        }
        appendCharacter(scene, o.character, sopt, o.weapon);
        {
            const size_t p1 = firstCharacter(scene, 0);
            attachFighterWeapon(scene, "P1", o.character, o.weapon, p1, sopt);
        }
        if (enemyBegin) *enemyBegin = scene.models.size();
        appendCharacter(scene, o.enemy, sopt, o.enemyWeapon);
        {
            const size_t p2 = firstCharacter(scene, enemyBegin ? *enemyBegin : 0);
            attachFighterWeapon(scene, "P2", o.enemy, o.enemyWeapon, p2, sopt);
        }
        scene.source = o.stage;
    } else if (!o.stage.empty()) {
        scene = xm::loadStage(o.stage, sopt);
    } else if (!o.character.empty()) {
        appendCharacter(scene, o.character, sopt, o.weapon);
        // A weapon rides a bone of the character, so it can only be attached once the
        // character's rig exists.
        const size_t ownerRig = firstCharacter(scene, 0);
        if (o.animPlayer) {
            // The browser exists to judge weapon-holding clips, so it gears the browsed
            // character up the way every match path does: the same item-slot resolution and
            // the same per-prop attachment (attachFighterWeapon). An empty --weapon means
            // the character's slot-0 legal weapon, e.g. item 001 for Rena 0.
            attachFighterWeapon(scene, "browser", o.character, o.weapon, ownerRig, sopt);
        } else if (!o.weapon.empty()) {
            std::string wspec;
            int slot = 0;
            splitSuffix(o.weapon, wspec, slot);
            const xm::Model* rig = ownerRig < scene.models.size() ? &scene.models[ownerRig].model
                                                                  : nullptr;
            xm::Scene w = xm::loadWeapon(wspec, slot, rig, sopt);
            for (xm::SceneModel& sm : w.models) {
                sm.ownerRig = ownerRig;
                scene.models.push_back(std::move(sm));
            }
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



// Column-major, matching WGSL's mat4x4<f32>.
Mat4 rotationZ(float radians, float scale) {
    const float c = std::cos(radians) * scale;
    const float s = std::sin(radians) * scale;
    return Mat4{{c, s, 0.f, 0.f,
                 -s, c, 0.f, 0.f,
                 0.f, 0.f, 1.f, 0.f,
                 0.f, 0.f, 0.f, 1.f}};
}

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
    const fnd::audio::LoopSheetResult sheet = fnd::audio::resolve_loop_sheet(
        oggPath, 44100, [](const std::string& path, std::vector<uint8_t>& out) {
            return fnd::assets::assetSource().read(path, out);
        });
    loop.set_source(decoded.stereo44100.data(), decoded.stereo44100.size() / 2);
    loop.set_loop(sheet.loop.startSample, sheet.loop.endSample);
    // The absent case stays silent, as FUN_00668820 is; only a sheet that is
    // there but unusable earns a line, and this one is load-time, never per-frame.
    if (!sheet.note.empty())
        std::fprintf(stderr, "[bgm] %s: no loop region, playing to EOF "
                             "[port rule: reported, FUN_00668820 is silent]\n",
                     sheet.note.c_str());
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
    applyWeaponVisibility(app);
}


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
// Parses one data/item/NNN.dat. Null when the file is missing or short.

static std::unique_ptr<gameplay::WeaponDefinition> loadItemDefinition(int itemId) {
    char path[64];
    std::snprintf(path, sizeof(path), "data/item/%03d.dat", itemId);
    std::vector<uint8_t> bytes;
    if (!fnd::assets::assetSource().read(path, bytes)) return nullptr;
    auto definition = std::make_unique<gameplay::WeaponDefinition>();
    std::string parseError;
    if (!definition->parse(itemId, bytes.data(), bytes.size(), parseError)) return nullptr;
    return definition;
}

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
    mesh.clear();
    const auto item = loadItemDefinition(itemId);
    if (!item) return false;
    for (int slot = 0; slot < item->slotCount; ++slot) {
        if (!item->slots[slot].meshName.empty()) {
            mesh = item->slots[slot].meshName;
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

// Attaches every non-empty attachment record of a parsed item, each as its own prop.
// FUN_00433eb0 loads one prop per slot whose 30-byte mesh name is non-empty and skips
// the empty ones, so an item's several non-empty slots are several props, each with its
// OWN anchors (the file's nine integers are per slot) and its own id. The executor binds
// an id per slot and clears it at throw thresholds, which is what the draw gate reads.
// Returns the number of props loaded; an item whose every slot is empty loads none and
// is still armed (its move table, bullets and damage come from the id).
static int attachItemProps(xm::Scene& scene, const gameplay::WeaponDefinition& item,
                           size_t ownerRig, const xm::SceneOptions& sopt) {
    int loaded = 0;
    for (int prop = 0; prop < item.slotCount; ++prop) {
        const gameplay::WeaponSlot& slot = item.slots[prop];
        if (slot.meshName.empty()) continue;
        const std::string path = std::string("data/item/") + slot.meshName;
        // Appending a prop may reallocate scene.models; reacquire the owner's rig
        // for each FUN_00433eb0 attachment slot rather than retaining a stale pointer.
        const xm::Model* rig = ownerRig < scene.models.size() ? &scene.models[ownerRig].model : nullptr;
        xm::Scene w = xm::loadWeapon(path, 0, rig, sopt, prop);
        if (w.models.empty()) {
            // A named attachment that will not load leaves the fighter armed but visually
            // unarmed for that prop; say so rather than dropping it silently.
            std::fprintf(stderr, "[weapons] item %03d prop %d: %s did not load\n",
                         item.id, prop, path.c_str());
            continue;
        }
        for (xm::SceneModel& sm : w.models) {
            sm.ownerRig = ownerRig;
            scene.models.push_back(std::move(sm));
            ++loaded;
        }
    }
    return loaded;
}

// Attaches one fighter's weapon props: the explicit spec, or the character's
// slot-0 legal weapon when empty — never bare by omission (every attack is a
// weapon attack, issue #26). An unjoinable spec keeps the legacy bare fallback,
// loudly. Used by every versus/match assembly path below. `ownerRig` is the
// character model the props hang off, recorded so per-frame placement never has to
// guess which fighter a weapon belongs to.
static void attachFighterWeapon(xm::Scene& scene, const std::string& label,
                                const std::string& charSpec,
                                const std::string& weaponSpec, size_t ownerRig,
                                const xm::SceneOptions& sopt) {
    const int character =
        gameplay::characterIndexForDir(charDirForSpec(charSpec));
    // resolveFighterWeapon handles an empty spec (the character's slot-0 legal weapon) and
    // an explicit one (an item mesh basename or a data/bullet/NNN directory) the same way,
    // and it is where the item id comes from — an explicit spec does NOT carry one.
    std::string mesh;
    int itemId = 0;
    if (!resolveFighterWeapon(charDirForSpec(charSpec), weaponSpec, mesh, itemId)) {
        // A roster fighter that cannot gear up fails the launch LOUDLY (rule 7: a silent
        // bare fighter is a false claim). Only unknown (custom) characters keep the bare
        // fallback, with a warning.
        if (character >= 0)
            throw std::runtime_error(
                label + " " + charSpec + " has no weapon: item '" + weaponSpec +
                "' joins none of the character's own items — roster fighters must gear up");
        std::printf("[weapons] %s (%s): unknown character, bare\n", label.c_str(),
                    charSpec.c_str());
        return;
    }
    const std::string combo =
        gameplay::comboSlotLabel(character, gameplay::weaponSlotForItem(character, itemId));
    // Every non-empty attachment record of the resolved item, each as its own prop. The
    // executor binds a prop id per slot and clears it at the throw thresholds, which is
    // what the draw gate reads.
    const auto item = loadItemDefinition(itemId);
    const int props = item ? attachItemProps(scene, *item, ownerRig, sopt) : 0;
    if (props == 0) {
        // Parsed, and no slot ships a mesh: NOT a failure. The fighter is armed with the
        // item — its move table, bullets and damage are bound by the id — and the original
        // skips the attachment load for exactly this case (FUN_00433eb0:111).
        std::printf("[weapons] %s %s: item %03d, armed; the item ships no attachment mesh"
                    " to draw\n",
                    label.c_str(), combo.c_str(), itemId);
        return;
    }
    std::printf("[weapons] %s %s: item %03d, %d attachment prop(s)\n", label.c_str(),
                combo.c_str(), itemId, props);
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
static bool loadBulletParameter(int row, const gameplay::WeaponDefinition& weapon,
                                std::unique_ptr<gameplay::BulletParameter>& out) {
    if (row < 0 || row >= weapon.bulletCount) return false;
    const gameplay::BulletDefinition* best = &weapon.bullets[row];
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
    return true;
}



static bool startCoreBattle(App& app, const MatchSetup& config) {
    sim::BattleConfig core;
    core.gameDir = fnd::assets::assetSource().installDir();
    if (app.frontendMatch) core.seed = static_cast<uint32_t>(app.logicTicks) * 2654435761u + 1u;
    core.timeLimitSeconds = static_cast<unsigned>(std::max(0, config.timeLimit));
    core.rules = {config.healthPercent, config.gaugePercent, config.balloonSize[0], config.balloonSize[1]};
    const std::string stageDir = charDirForSpec(app.opts.stage);
    core.stage = static_cast<unsigned>(std::atoi(stageDir.c_str() + std::min<size_t>(5, stageDir.size())));
    std::array<const gameplay::CharacterMoves*, 4> moves{};
    std::array<const gameplay::WeaponDefinition*, 4> weapons{};
    for (int i = 0; i < 4; ++i) {
        const std::string dir = charDirForSpec(app.opts.battleCharacters[i]);
        int character = -1;
        for (int c = 0; c < sim::character_count(); ++c)
            if (sim::character_name(c) == dir) character = c;
        const gameplay::WeaponDefinition* weapon = config.weapon[i];
        const int ownIndex = gameplay::characterIndexForDir(dir);
        const int slot = weapon ? gameplay::weaponSlotForItem(ownIndex, weapon->id) : -1;
        if (character < 0 || slot < 0) {
            app.error = "battle: fighter " + std::to_string(i) + " (" + dir + ") is not a legal combo";
            return false;
        }
        bool human = i == 0 && !app.frontendMatch;
        if (app.frontendMatch) {
            const int controller = app.frontend.slots[app.battleLaunch.fighters[i].panel].controller;
            human = controller >= 0 && controller < 4;
        }
        std::string specPath;
        int costume = 0;
        splitSuffix(app.opts.battleCharacters[i], specPath, costume);
        core.slots[static_cast<size_t>(i)] = {character, slot, !human, costume,
                                              static_cast<unsigned>(config.hyper[i])};
        moves[static_cast<size_t>(i)] = config.moves[i];
        weapons[static_cast<size_t>(i)] = weapon;
    }
    try {
        app.coreBattle.start(core, moves, weapons);
    } catch (const std::exception& error) {
        app.error = std::string("battle: ") + error.what();
        return false;
    }
    return true;
}

static bool initMatch(App& app) {
    if (app.frontendMatch && !app.scene.env.present) {
        app.error = "four-panel battles need all four env.dat spawn points";
        return false;
    }
    if (!app.frontendMatch && app.opts.battleFighterCount != 4) {
        app.error = "--match needs four fighters: pass --sim-roster=<a>,<b>,<c>,<d>";
        return false;
    }
    std::array<size_t, 4> rigs{{app.scene.models.size(), app.scene.models.size(),
                                app.scene.models.size(), app.scene.models.size()}};
    const int fighterCount = app.frontendMatch ? app.battleLaunch.fighterCount : app.opts.battleFighterCount;
    if (fighterCount != 4) {
        app.error = "the core plays four fighters, the launch built " + std::to_string(fighterCount);
        return false;
    }
    int found = 0;
    for (size_t i = 0; i < app.scene.models.size() && found < fighterCount; ++i)
        if (app.scene.models[i].role == "character") rigs[found++] = i;
    if (found != fighterCount) {
        app.error = "loaded character rigs do not match the selected roster";
        return false;
    }

    MatchSetup config;
    config.fighterCount = fighterCount;
    if (app.frontendMatch) {
        config.healthPercent = app.frontend.health;
        config.gaugePercent = app.frontend.gauge;
        config.timeLimit = app.frontend.timeLimit;
        config.balloonSize[0] = app.frontend.blueBalloon;
        config.balloonSize[1] = app.frontend.redBalloon;
        for (int i = 0; i < fighterCount; ++i) {
            const int panel = app.battleLaunch.fighters[i].panel;
            config.hyper[i] = (game::Hypermode)app.frontend.slots[panel].hypermode;
            // The selected weapon's own combat definition (issue #9): magazine sizes,
            // charge thresholds, per-shot costs and volley counts come from the item
            // file, not from a shared table.
            if (i < static_cast<int>(app.weaponDefs.size()) && app.weaponDefs[i])
                config.weapon[i] = app.weaponDefs[i].get();
        }
    }
    if (!app.frontendMatch) {
        // Standalone matches never selected weapons: resolve each fighter to its
        // character's legal combo (mesh attached at assembly; combat data here),
        // so bare-handed shared-tuning fights cannot happen by omission. The
        // frontend path arrives with weaponDefs filled and skips all of this.
        for (int i = 0; i < fighterCount; ++i) {
            if (i < static_cast<int>(app.weaponDefs.size()) && app.weaponDefs[i]) {
                config.weapon[i] = app.weaponDefs[i].get();
                continue;
            }
            const std::string& charSpec = app.opts.battleCharacters[i];
            const std::string& explicitSpec = app.opts.battleWeapons[i];
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
            for (int row = 0; row < app.weaponDefs[i]->bulletCount; ++row)
                loadBulletParameter(row, *app.weaponDefs[i],
                                    app.bulletParams[static_cast<size_t>(i)]
                                                  [static_cast<size_t>(row)]);
        }
    }

    const xm::Model* models[4] = {};
    xm::Controller* anims[4] = {};
    for (int i = 0; i < fighterCount; ++i) {
        models[i] = &app.scene.models[rigs[i]].model;
        anims[i] = &app.controllers[rigs[i]];
        // initScene cleared every binding; a front-end rig has no --anim loop to rebind it.
        anims[i]->bind(models[i]);
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

    // The aura's attach points, resolved on each fighter's own rig the way FUN_0041e180
    // resolves them once per character: eleven named frames whose world matrices are what
    // FUN_004205e0 draws the attachment on. A rig that does not carry all eleven is not a
    // shipped rig; the count is reported either way because it IS the aura instance count.
    for (int i = 0; i < fighterCount; ++i) {
        app.auraAttach[i] = game::resolveAuraAttach(app.scene.models[app.matchRig[i]].model);
        if (app.auraAttach[i].found < game::kAuraAttachPoints)
            std::printf("[aura] fighter %d: %d/%d attach points on %s\n", i,
                        app.auraAttach[i].found, game::kAuraAttachPoints,
                        app.scene.models[app.matchRig[i]].source.c_str());
    }

    if (!startCoreBattle(app, config)) return false;
    // The core chooses its own voices and SEs, so a standalone --match needs the playback half
    // of the combat layer too; the front end builds it in enterFrontendBattle.
    if (!app.frontendMatch) {
        if (!app.combatSink) app.combatSink = std::make_unique<App::CombatSink>(app);
        if (!app.combatAudio) app.combatAudio = std::make_unique<fnd::audio::CombatAudio>(*app.combatSink);
        app.combatAudio->begin_match();
        app.versusAudio.set_volumes(ui::frontendSettings().volumes);
    }
    // The roster in panel order, with each entry linked to its MatchConfig index (issue #13).
    buildMatchRoster(app);
    // The frontend already chose its device policy before it set opts.match for
    // scene assembly. Reclassifying that live session here silences every device.
    if (!app.matchInputReady) {
        if (!app.matchInput.init()) {
            app.error = "--match needs the input backend";
            return false;
        }
        app.matchInputReady = true;
    }

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
    for (int i = 0; i < app.battle->fighter_count(); ++i)
        cameraPool.push_back(&app.arenaTargets[i]);
    for (int v = 0; v < game::kMaxHumanViews; ++v) {
        game::MatchView& view = app.matchViews[v];
        view = game::MatchView{};
        if (v >= app.matchViewCount) continue;
        view.controller = viewList[v].controller;
        view.fighter = viewList[v].fighter;
        view.followed = viewList[v].fighter;
        // The camera starts pristine: eye (0,0,0), converging at 10% per update exactly
        // like the reference's ArenaCamera (camera/arena_camera.cpp). That seed is what
        // makes the first trace line comparable — the DX9's own frame-1 eye is one 10%
        // step from the origin, not the converged position.
        view.camera = gameplay::ArenaCamera{};
        view.camera.set_target_pool(cameraPool);
        view.camera.set_action_rig(&app.actionCameraModel);
        view.camera.set_active_target(view.followed);
        view.previousEye = view.camera.eye();
        view.previousTarget = view.camera.target();
    }
    for (int i = 0; i < fighterCount; ++i) app.previousFighter[i] = app.battle->fighter(i).pose();
    return true;
}


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

// A folder a run actually opened becomes the remembered one (issue #36), so the next run —
// a direct binary run, the packaged launcher, or a front end that reaches a match — starts
// from the same place instead of discovering one again. Two gates keep that honest: only a
// run that owns a user config writes anything (a capture never loads settings, so it can
// neither write nor be perturbed), and only a folder the parser would read back is stored
// (settings::storableInstallDir: absolute, and short enough for one line). A relative
// `--install=Higurashi-Daybreak` therefore behaves exactly as it always has — used for this
// run, not remembered, because "Higurashi-Daybreak" is this shell's working directory — and
// a folder that came from the working-directory fallback is not remembered either, for the
// same reason. The write goes through the usual dirty/save policy, so it is atomic and
// reported like any other settings change.
static void rememberInstallDir(App& app, const std::string& dir) {
    if (!app.settingsActive || !settings::storableInstallDir(dir)) return;
    if (app.userSettings.installDir == dir) return;
    app.userSettings.installDir = dir;
    ui::frontendSettings().installDir = dir;
    app.settingsDirty = true;
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

    // A Controller holds a raw pointer to one SceneModel's Model (assets/xmodel.h:238), and
    // assigning the new scene below frees the models those pointers name. resize() further
    // down only constructs and destroys entries, so a controller bound by an earlier match
    // survives the swap still pointing into the freed scene, and advanceAnimation
    // (main.cpp:3855-3856) evaluates every controller with a non-null model: that is the
    // reporter's std::bad_alloc (coredumpctl 563299 — evalLocal read a freed Model's frame
    // list as nf = 66584576). Clear every binding before the scene it was made against dies.
    // After this point a controller is bound only by the --anim loop below or by initMatch,
    // and both of those name models of the scene that is current here.
    for (xm::Controller& controller : app.controllers) controller.bind(nullptr);

    try {
        app.scene = loadScene(app.opts, app.error, &app.enemyBegin);
    } catch (const std::exception& e) {
        app.error = std::string("load failed: ") + e.what();
        return false;
    }
    if (app.scene.models.empty()) return false;
    // Bullet rows and generated trails join after Match binds borrowed rig pointers.
    // Bound growth avoids invalidating those models/controllers during asset finalization.
    constexpr size_t kCombatModelHeadroom = 4 * (64 + 2) + game::kEffectSlots + game::kAuraSlots;
    app.scene.models.reserve(app.scene.models.size() + kCombatModelHeadroom);
    app.controllers.reserve(app.scene.models.capacity());

    if (app.opts.list) {
        listScene(app.scene);
        return true;
    }
    xm::resolveSceneTextures(app.scene);
    app.modelMatrices.assign(app.scene.models.size(), glm::mat4(1.f));
    // A card index is only valid against the scene that produced it, so a reloaded scene
    // invalidates every shot model until bindShotModels() resolves them again (issue #32).
    for (auto& rows : app.fxShotModel) rows.fill(-1);
    // FUN_00633ca0's effect models extend the scene. Finish that growth before
    // fighters, animation controllers or collision queries borrow model pointers.
    if (app.opts.match || app.opts.versus) buildFxAssets(app);

    // Effects are part of SceneModel storage too, so finish appending them before
    // borrowing any model pointers for fighters or collision queries.
    const xm::Model* cameraMesh = nullptr;
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.hasCollisionChannel(xm::StageCollisionChannel::Camera)) cameraMesh = &sm.model;
    }
    app.cameraCollision.setMesh(cameraMesh);
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
    // Character shadows (issue #21 row 1): same rule as the toon row.
    app.appearance.shadows = app.opts.shadowsSet ? app.opts.shadows
                                                 : ui::frontendSettings().shadowRendering;
    // NPR experiments (issue #25): the flag family is opt-in, so an absent --npr leaves
    // every field at the appearance's default and the renderer takes the same path it
    // took before this issue existed. `--npr=off` is the explicit form of that state.
    if (app.opts.nprSet) app.appearance.copyExperimentsFrom(app.opts.npr);

    // Issue #32: the in-flight shot's own model is a scene model, so it joins the scene
    // here — after every path that parses a bullet file (initMatch for a standalone match,
    // enterFrontendBattle for a selected one) and before the renderer takes the draw list.
    if (app.opts.match || app.frontendMatch) bindShotModels(app);
    if (app.opts.match || app.frontendMatch) bindAnimationMaterials(app);
    app.controllers.resize(app.scene.models.size());
    app.worlds.resize(app.scene.models.size());

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
    // `outlines` is the toon hulls queued for the character/weapon draws (issue #21): they
    // are part of the draw list but are submitted only while the toggle is on, so they are
    // named here rather than left to inflate the total unexplained.
    std::printf("draws: %zu (%d textured, %d untextured, %d decals, %d effects, %d outlines), %zu GPU textures\n",
                st.draws, st.textured, st.untextured, st.decals, st.effects, st.outlines,
                st.textures);
    // The secondary lighting normals (issue #25, E/F) are built per mesh at upload, so
    // whether a scene HAS them is a load-time fact worth reporting: an experiment that
    // reports "no effect" because the stream was never built looks exactly like one that
    // reports "no effect" because the technique is invisible.
    if (st.nprMeshes > 0)
        std::printf("npr normals : %d mesh(es), %zu vertices with a secondary normal\n",
                    st.nprMeshes, st.nprVertices);
    return true;
}

// ---------------------------------------------------------------------------------------
// Offscreen capture: coverage and luminance over a frame, plus a PPM of it. The "not
// background" test is the renderer's own clear colour, so coverage counts pixels the
// scene actually reached.
// ---------------------------------------------------------------------------------------

void teardown(App& app) {
    app.menuAudio.close();
    app.movieAudio.close();
    stopCombatAudio(app);
    if (app.versusAudioOn) app.versusAudio.close();
    if (app.uiReady) app.uiRenderer.shutdown();
    if (app.pauseUiReady) app.pauseUi.shutdown();
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
    // Stepped animation presentation (issue #25 experiment J): quantise the POSE clock to
    // `poseStep` updates per second while the render clock keeps running. The scale is
    // applied to the delta rather than to each track's absolute time, so the phase a run
    // starts at (--time) is preserved and a capture stays reproducible; a delta shorter
    // than one step advances nothing, which is the whole point.
    if (app.opts.poseStep > 0.f) {
        const double step = 1.0 / (double)app.opts.poseStep;
        delta = std::floor(delta / step + 1e-9) * step;
    }
    bool moved = false;
    for (size_t i = 0; i < app.controllers.size(); ++i) {
        xm::Controller& c = app.controllers[i];
        if (!c.model()) continue;
        bool matchRig = false;
        if (app.matchMode || app.resultOverScene)
            for (int fighter = 0; fighter < app.battle->fighter_count(); ++fighter)
                matchRig = matchRig || i == app.matchRig[fighter];
        if (matchRig) continue;
        c.advanceTime((float)delta);
        moved = true;
    }
    // A match still needs the pose refreshed: the fighters moved their own tracks.
    if (app.matchMode || app.resultOverScene) moved = true;
    if (!moved) return;
    for (size_t i = 0; i < app.controllers.size(); ++i)
        if (app.controllers[i].model()) app.controllers[i].evalWorld(app.worlds[i]);
    for (int fighter = 0; fighter < app.battle->fighter_count(); ++fighter)
        app.battle->fighter(fighter).core_pose(app.worlds[app.matchRig[fighter]]);
    app.renderer.updatePose(app.worlds);
}

// ---------------------------------------------------------------------------------------
// Backend self-checks: --audio-test and --input-test exercise the media/input
// backends in-engine (same binaries, same SDL) without needing game data.
// ---------------------------------------------------------------------------------------
