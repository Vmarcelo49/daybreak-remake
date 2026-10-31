// The live match: capture gates, the per-view cameras and HUD, the effect cards,
// the match/front-end-result tick and the versus vignette.
// Included by main.cpp inside its anonymous namespace.

static bool historicalMatchCapture(const App& app) {
    return !app.frontendMatch &&
           (!app.opts.out.empty() || !app.opts.script.empty() || !app.opts.script2.empty());
}

// Draw gate for the attachment system. A weapon model is drawn only while the prop id it
// was loaded from is bound in its owner's executor state: FUN_00434a70 clears that id at
// the throw thresholds (FUN_0043ffc0's Hide pairs), which is what lets the nata leave
// Rena's hand. `ownerModel` resolves the character model of a weapon that assembly could
// not label; every other role stays visible. Gated state is per-frame in battle, so this
// only needs calling where placement is per-frame (versus and match).
static void applyWeaponVisibility(App& app) {
    std::vector<bool> visible(app.scene.models.size(), true);
    // Only a configured Match has per-fighter attachment state. The versus vignette runs
    // its own scripted fighters, so gating its weapons on app.battle (which is default
    // constructed there, with matchRig all zeroes) would read the wrong fighter entirely.
    if (!app.matchMode && !app.frontendMatch) {
        app.renderer.setModelVisibility(visible);
        return;
    }
    const size_t fighters = app.battle->fighter_count();
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.propId < 0 || sm.attachFrame < 0) continue;   // not a weapon attachment
        size_t owner = sm.ownerRig;
        if (owner >= app.scene.models.size() || app.scene.models[owner].role != "character") {
            // Weapons are appended directly after their rig, so the nearest preceding
            // character model is the owner in an unlabelled scene.
            for (size_t j = i; j-- > 0;)
                if (app.scene.models[j].role == "character") { owner = j; break; }
        }
        for (size_t fighter = 0; fighter < fighters && fighter < 4; ++fighter)
            if (app.matchRig[fighter] == owner) {
                const auto& f = app.battle->fighter(static_cast<int>(fighter));
                // The drawn mesh follows the executor's slot -> ITEM MODEL binding, not
                // the scene model's own load order: FUN_00434a70(slot, model) re-points a
                // prop slot at another of the item's models (Rena 1's 450/460 bind slot 0
                // to model 2 = 12.x, where the default slot 0 is model 0 = 11.x) and the
                // original then draws whichever model that slot names. A scene model IS
                // one of those canonical model indices, so it is visible exactly when a
                // bound slot names it. `draws_item_model` is the shared predicate: without
                // it the launch origin could be model 2 while the visible weapon was 0.
                visible[i] = f.draws_item_model(sm.propId);
                break;
            }
    }
    app.renderer.setModelVisibility(visible);
}

// The presentation blend a frame renders with. D9: a historical `--out` recipe steps one
// update per frame and renders with no interpolation (alpha 1), which is what keeps the
// banked captures byte-identical; a live frame renders with the fixed-step clock's own
// fraction. `--match-alpha` overrides both with a fixed phase (issue #39), so a headless
// recipe can render — and a test can assert on — the interpolation the live path applies.
static float matchAlphaFor(const App& app, bool capturing) {
    if (app.opts.matchAlpha >= 0.f) return app.opts.matchAlpha;
    return capturing ? 1.f : app.logicClock.alpha();
}


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
            // starts when the screen does and not at process start. It restarts on every
            // Select entry — a rematch re-enters the selection screen, and a clock latched on
            // the first appearance left the pads stuck mid-pattern there: their cursor moves
            // (keyed to the pattern's own ticks) never fired again, so no pad could
            // reach the OK cell and the rematch round's stage page opened at a different tick
            // with different settings. Per-appearance, a rematch round runs the same walk as
            // the first one — and it has the same panels to walk, because entering the select
            // scene starts an empty selection (issue #45, FrontendState::beginSelection).
            if (app.screens.current() == ui::ScreenId::Select) {
                if (!app.selectSeen) {
                    app.selectSeen = true;
                    app.selectEnterTick = app.logicTicks;
                }
            } else {
                app.selectSeen = false;
            }
            pad = fnd::input::syntheticMenuPadState(
                controller, app.selectSeen ? app.logicTicks - app.selectEnterTick : 0);
            // The pattern is the selection PANEL screen's instrument: its directions walk that
            // screen's panels and its confirms accept the OK cell that opens the stage page.
            // The stage page is that screen's sub-page (`FrontendState::stagePage`), and there
            // the same directions move the SETTINGS cursor — so the round's configuration
            // depended on the tick the page happened to open on, and a rematch (which opens it
            // at a different tick than the first round) played 240 s/175 % where the script
            // asks for 60 s/50 %. The run's own taps configure the page; the pads stay neutral
            // there. The VS presentation and the result beats advance on their own or on the
            // run's own script taps, so the pads never skip them either: an evidence run sees
            // the whole four-portrait assembly and the full victory -> quote -> report
            // sequence instead of a single faded frame (frontend/screen_vs.h, frontend/screen_result.h).
            if (app.frontend.stagePage) pad = fnd::input::SyntheticPadState{};
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


static glm::vec3 matchRenderPosition(const App& app, int fighter) {
    return glm::mix(app.previousFighter[fighter].position,
                    app.battle->fighter(fighter).position(), app.matchAlpha);
}

static glm::mat4 matchRenderMatrix(const App& app, int fighter) {
    if (app.matchAlpha == 1.f) return app.battle->fighter(fighter).modelMatrix();
    // The core's rotation is its own (pitch and throw poses included); only the root moves.
    glm::mat4 matrix = app.battle->fighter(fighter).modelMatrix();
    matrix[3] = glm::vec4(matchRenderPosition(app, fighter), 1.f);
    return matrix;
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
    // Standalone: controller 0 on the device or script, COM on the rest. The character index is
    // resolved from the same spec the scene assembly used, so the combo label matches the rig.
    app.participantCount = app.battle->fighter_count();
    for (int i = 0; i < app.participantCount; ++i) {
        ui::Participant& p = app.participants[i];
        p = ui::Participant{};
        p.panel = i;
        p.team = i / 2;
        p.character = gameplay::characterIndexForDir(charDirForSpec(app.opts.battleCharacters[i]));
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
    }
}


// Fills `out` with this frame's views: the cell each one occupies (hud/view_layout.h's
// recovered FUN_006396f0 geometry), the camera pose for it — interpolated for presentation,
// or the exact camera when nothing is interpolated (alpha 1), exactly as the single-view
// path did — and that view's HUD with its markers projected through its own view-projection
// (D8). Always at least one entry, so a single-view frame takes the historical render path
// with one cell covering the target.
static void buildFrameViews(App& app, uint32_t width, uint32_t height,
                            std::vector<FrameView>& out) {
    out.clear();
    // FUN_006396f0: the result phases show one fixed fighter to everyone, full screen.
    const bool oneView = app.battle->hud_hidden();
    const game::SplitLayout layout = oneView ? game::SplitLayout::Single : game::splitLayoutFor(app.matchViewCount);
    for (int v = 0; v < app.matchViewCount; ++v) {
        const game::MatchView& view = app.matchViews[v];
        if (!view.active()) continue;
        if (oneView && !out.empty()) break;
        const game::ViewRect rect = game::viewCell(layout, oneView ? 0 : v, width, height);
        if (rect.empty()) continue;
        FrameView frameView;
        frameView.cell = rect;
        frameView.camera.rect = app.matchViewCount > 1 && !oneView
            ? render::ViewportRect{rect.x, rect.y, rect.w, rect.h}
            : render::ViewportRect{};
        frameView.camera.eye = glm::mix(view.previousEye, view.camera.eye(), app.matchAlpha);
        const glm::vec3 target = glm::mix(view.previousTarget, view.camera.target(), app.matchAlpha);
        // With nothing interpolated (alpha 1: D9's historical capture recipes, and the live
        // clock's own 1.0 edge) the reference view is the camera's own. Any fractional alpha
        // takes lookAtLH over the interpolated pose, which is what makes a --match-alpha
        // capture render the presentation the live path renders — and lookAtLH cannot
        // construct a basis from coincident eye/aim, which happens while every target is
        // dead, so that case keeps the camera's own matrix too.
        const glm::mat4 viewMatrix = app.matchAlpha == 1.f || frameView.camera.eye == target
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

// Places one bone-attached scene model on its owning rig's live pose. A weapon is a
// separate model, so its world transform is the rig's model matrix composed with the
// bone's model-space matrix — the composition the versus path once got wrong (it used
// the bone matrix alone, placing a weapon at the origin instead of in the hand).
// The match path and the animation browser (animPlayerTick, main.cpp:6092) share it so a
// weapon drawn in the browser follows the animated hand exactly as it does in a match.
static void placeAttachedProp(App& app, size_t index, size_t rig, int hand) {
    const xm::SceneModel& sm = app.scene.models[index];
    const int frame = hand == 1 && sm.offHandFrame >= 0 ? sm.offHandFrame : sm.attachFrame;
    if (rig >= app.worlds.size() || (size_t)frame >= app.worlds[rig].size()) {
        std::fprintf(stderr, "[scene] %s: attachment frame %d unusable, drawing at the origin\n",
                     sm.source.c_str(), frame);
        return;
    }
    app.modelMatrices[index] = app.modelMatrices[rig] * app.worlds[rig][(size_t)frame];
}

// Not under --debug-prims: those passes share one vertex buffer, written before the frame
// is submitted, so the negative's quad would replace the cubes.
static bool timeStopNegative(const App& app) {
    return app.matchMode && !app.opts.debugPrims && app.battle && app.battle->time_stop_active();
}

// Places each fighter's model from the live simulation. modelMatrix() is the
// reference's world matrix (translation + Y rotation, FUN_00420b30).
static void placeMatchFighters(App& app) {
    std::vector<render::SceneRenderer::TextureOverride> textures;
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        for (int fighter = 0; fighter < app.battle->fighter_count(); ++fighter)
            if (i == app.matchRig[fighter]) {
                app.modelMatrices[i] = matchRenderMatrix(app, fighter);
                break;
            }
    }
    for (size_t i = 0; i < app.scene.models.size(); ++i) {
        const xm::SceneModel& sm = app.scene.models[i];
        if (sm.attachFrame < 0) continue;
        size_t rig = app.matchRig[0];
        int owner = 0;
        for (int fighter = 1; fighter < app.battle->fighter_count(); ++fighter)
            if (app.matchRig[fighter] < i && app.matchRig[fighter] > rig) {
                rig = app.matchRig[fighter];
                owner = fighter;
            }
        placeAttachedProp(app, i, rig, app.battle->fighter(owner).item_model_hand(sm.propId));
    }
    app.renderer.setModelMatrices(app.modelMatrices);
    applyWeaponVisibility(app);
    for (int i = 0; i < app.battle->fighter_count(); ++i) {
        const auto& fighter = app.battle->fighter(i);
        if (const auto* moves = fighter.moves()) {
            // A playing activation overlay owns its set's texture events on its
            // own clock: set 69's face swap keys off the overlay elapsed (move
            // 500's phase-0 frames), not the Idle row's clock, which has already
            // run past the event window by activation time (issue #71).
            const int clock = fighter.hyper_activation_playing()
                                  ? fighter.hyper_activation_elapsed()
                                  : fighter.phase_elapsed();
            for (const auto& event : moves->texture_events(fighter.anim_set_index()))
                if (event.active(clock))
                    textures.push_back({app.matchRig[i],event.source,event.replacement});
        }
        for (int hand = 0; hand < 2; ++hand) {
            const int model = app.trailModels[static_cast<size_t>(i)][static_cast<size_t>(hand)];
            if (model < 0) continue;
            const auto& trail = fighter.trail(hand);
            const auto vertices = trail.vertices();
            app.renderer.updateDynamicMesh(static_cast<size_t>(model), vertices.data(), vertices.size(),
                                           static_cast<uint32_t>(trail.triangles()*3));
            const int itemModel = fighter.trail_item_model(hand);
            const auto* weapon = fighter.weapon();
            if (weapon && itemModel >= 0 && itemModel < weapon->slotCount &&
                weapon->slots[itemModel].has_prop()) {
                const auto& carrier = app.scene.models[static_cast<size_t>(model)];
                if (!carrier.model.meshes.empty() &&
                    !carrier.model.meshes[0].materials.empty()) {
                    const std::string& source = carrier.model.meshes[0].materials[0].texture;
                    const std::string& replacement = weapon->slots[itemModel].textureName;
                    if (!source.empty() && !replacement.empty() && source != replacement)
                        textures.push_back({static_cast<size_t>(model), source, replacement});
                }
            }
        }
    }
    app.renderer.setTextureOverrides(textures);
}

// The effect asset table the gameplay events index into (render/effect_events.h:
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
    for (int slot = 0; slot < game::kAuraSlots; ++slot) {
        char rel[32];
        std::snprintf(rel, sizeof(rel), "/aura/%02d.x", slot);
        app.fxAttach[slot] = addFxCard(app, dataDir + rel);
        if (app.fxAttach[slot] >= 0) {
            const xm::Model& m = app.scene.models[(size_t)app.fxAttach[slot]].model;
            if (!m.anims.empty() && m.ticksPerSecond > 0.f)
                app.fxAttachSeconds[slot] = m.anims[0].duration / m.ticksPerSecond;
        }
    }
    std::printf("fx assets    : %d effect descriptor(s), 7 attachment model(s)\n", loaded);
}

// Issue #32: resolve the in-flight shot's own model for every bound weapon, once per
// scene. The model is the 260-byte block of the level's data/bullet/<weaponId>/<type>.dat
// (gameplay::BulletParameter::modelName), which the original loads into the weapon's
// per-variant model object and the shot's own render draws — see render/shot_visual.h for
// the chain. Called after the bullet parameters exist and before setScene(), because a
// card is a scene model. A level whose model the install does not ship keeps -1, which is
// the empty model slot that same failed load leaves in the original; placeFxCards counts
// those placements instead of drawing them.
static void bindShotModels(App& app) {
    std::vector<std::pair<std::string, int>> loaded;   // path -> card, so two fighters
                                                       // with the same weapon load once
    for (size_t i = 0; i < app.bulletParams.size() && i < 4; ++i) {
        if (i >= app.weaponDefs.size() || !app.weaponDefs[i]) continue;
        const int weaponId = app.weaponDefs[i]->id;
        for (size_t row = 0; row < app.bulletParams[i].size(); ++row) {
            const gameplay::BulletParameter* p = app.bulletParams[i][row].get();
            if (!p || p->modelName.empty()) continue;
            char path[80];
            std::snprintf(path, sizeof(path), "data/bullet/%03d/%s", weaponId,
                          p->modelName.c_str());
            int card = -1;
            for (const auto& entry : loaded)
                if (entry.first == path) card = entry.second;
            if (card < 0) {
                card = addFxCard(app, path);
                loaded.emplace_back(path, card);
                if (card < 0)
                    std::fprintf(stderr, "[shot] %s: the install ships no such model; "
                                         "shots of this level draw nothing\n",
                                 path);
            }
            app.fxShotModel[i][row] = card;
            if (card >= 0) {
                app.scene.models[static_cast<size_t>(card)].role = "projectile";
                auto& variants = app.scene.models[static_cast<size_t>(card)].textureVariants;
                for (const auto& set : p->animationSets)
                    for (const auto& event : set.textures)
                        if (std::find(variants.begin(),variants.end(),event.replacement) == variants.end())
                            variants.push_back(event.replacement);
            }
        }
    }
}

static void bindAnimationMaterials(App& app) {
    std::vector<uint8_t> cameraBytes;
    if (fnd::assets::assetSource().read("data/camera/01.x",cameraBytes))
        app.actionCameraModel = xm::loadMemory(cameraBytes.data(),cameraBytes.size());
    for (auto& pair : app.trailModels) pair.fill(-1);
    for (int fighter = 0; fighter < app.battle->fighter_count(); ++fighter) {
        const size_t rig = app.matchRig[fighter];
        const auto* moves = app.battle->fighter(fighter).moves();
        const auto* weapon = app.battle->fighter(fighter).weapon();
        if (!moves || !weapon || rig >= app.scene.models.size()) continue;
        auto& variants = app.scene.models[rig].textureVariants;
        for (int set = 0; set < moves->animation_set_count(); ++set)
            for (const auto& event : moves->texture_events(set))
                if (std::find(variants.begin(),variants.end(),event.replacement) == variants.end())
                    variants.push_back(event.replacement);
        for (int hand = 0; hand < 2; ++hand) {
            int baseItemModel = hand;
            if (baseItemModel >= weapon->slotCount || !weapon->slots[baseItemModel].has_prop()) {
                baseItemModel = -1;
                for (int model = 0; model < weapon->slotCount; ++model)
                    if (weapon->slots[model].has_prop()) { baseItemModel = model; break; }
            }
            if (baseItemModel < 0) continue;
            const auto& slot = weapon->slots[baseItemModel];
            // FUN_00433eb0's meshName gate is the prop availability rule; a
            // texture-only Rena+0 item001 slot cannot own a ribbon. The handler's
            // manager slot selects the bone, while its binding may select another
            // item model's anchors and texture (Akane+0 Prop0<-item2).
            xm::SceneModel trail;
            trail.role = "effect";
            trail.source = "procedural weapon trail";
            trail.textures = xm::TextureCache("data/item/");
            xm::Mesh mesh;
            const gameplay::WeaponTrail empty;
            const auto vertices = empty.vertices();
            mesh.vertices.assign(vertices.begin(),vertices.end());
            for (uint32_t i = 0; i < gameplay::WeaponTrail::kTriangles; ++i)
                mesh.indices.insert(mesh.indices.end(), {0,i+1,i+2});
            xm::Material material;
            material.texture = slot.textureName;
            mesh.materials.push_back(material);
            mesh.submeshes.push_back({0,static_cast<uint32_t>(mesh.indices.size()),0});
            trail.model.meshes.push_back(std::move(mesh));
            for (int model = 0; model < weapon->slotCount; ++model) {
                const auto& candidate = weapon->slots[model];
                if (!candidate.has_prop() || candidate.textureName.empty() ||
                    candidate.textureName == slot.textureName ||
                    std::find(trail.textureVariants.begin(), trail.textureVariants.end(),
                              candidate.textureName) != trail.textureVariants.end())
                    continue;
                trail.textureVariants.push_back(candidate.textureName);
            }
            app.trailModels[static_cast<size_t>(fighter)][static_cast<size_t>(hand)] =
                static_cast<int>(app.scene.models.size());
            app.scene.models.push_back(std::move(trail));
            app.worlds.emplace_back();
            // The samples already include the posed Prop bone and actor transform
            // (FUN_00430120), so the trail carrier stays at identity.
            app.modelMatrices.emplace_back(1.f);
            app.controllers.emplace_back();
        }
    }
}

// Drains the gameplay's event queue into the live card set. The spawn /
// kill-by-id / ttl-expiry rules live in render/fx_cards.h (unit-tested there);
// this only moves the drained events over and counts them.
static void updateFxCards(App& app, game::EffectEventQueue& q, uint64_t& events, float dt) {
    const std::vector<game::EffectEvent> ev = q.drain();
    events += ev.size();
    // The cap and the drop count live in render/fx_cards.h; the tally is cumulative so a
    // run's log can prove the population stayed bounded (issue #17).
    const game::FxCardTally t = game::updateLiveFxCards(app.liveFx, ev, dt);
    if (app.liveFx.size() > app.fxPeakLive) app.fxPeakLive = app.liveFx.size();
    app.fxTally.spawned += t.spawned;
    app.fxTally.dropped += t.dropped;
    app.fxTally.expired += t.expired;
    app.fxTally.killed  += t.killed;
}

// Spawn one effect INSTANCE: a fresh id from the run's counter, the recovered lifetime
// of `effectId` from the catalog, and the asset its descriptor loaded into. Returns
// false when the install ships no such descriptor (the original leaves that table slot
// null too), so a bad id is visible in the caller's own accounting rather than silently
// drawing the wrong card.
static bool spawnEffect(App& app, game::EffectEventQueue& queue, int effectId,
                        const glm::vec3& at, const glm::vec3& direction = glm::vec3(0.f)) {
    const game::EffectEntry* entry = app.fxCatalog.find(effectId);
    if (!entry || !entry->playable()) return false;
    // The recovered animation length is a duration; the tick quantisation follows the
    // shipped cadence rather than the superseded 64 (D15) -- the two 64s cancelled, so
    // this is a quantisation change only.
    const float portRate = static_cast<float>(gameplay::FixedStep::tickRate);
    const float ttl = (float)app.fxCatalog.lifetime_ticks(effectId, portRate) / portRate;
    queue.pushSpawn(app.fxNextInstance++, at, entry->asset, ttl, direction);
    return true;
}

// One attachment-model card (FUN_00633ca0's table) at a world point, with the model's
// own animation as its lifetime. Attachment slots are not descriptor ids: the original
// draws them on the fighter's matrices (FUN_004205e0), so they have no entry in
// data/effect/ and no manager instance.
static bool spawnAttachment(App& app, game::EffectEventQueue& queue, int slot,
                            const glm::vec3& at) {
    if (slot < 0 || slot >= game::kAuraSlots || app.fxAttach[slot] < 0) return false;
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
    // Node matrices for the animated cards of this frame. The outer vector is sized before
    // any pointer into it is taken and never grows again, so the `poseWorld` pointers stored
    // in `instances` stay valid until setEffectInstances reads them.
    std::vector<std::vector<glm::mat4>> cardWorld;
    std::vector<glm::mat4> longStopPose;
    instances.reserve(app.liveFx.size() + 2 * game::kAuraAttachPoints +
                      game::kMaxLiveShots);
    if (!app.opts.debugPrims) {
        // One node-matrix array per live card, filled in place while the instances still
        // point at it: `poseWorld` is read during setEffectInstances, not later.
        cardWorld.clear();
        cardWorld.resize(app.liveFx.size());
        for (size_t ci = 0; ci < app.liveFx.size(); ++ci) {
            const game::LiveFxCard& c = app.liveFx[ci];
            if (c.asset < 0 || (size_t)c.asset >= app.scene.models.size()) continue;
            // The request's own pose, composed with the original's order
            // (FUN_00436150's RotationZ then RotationY then translation — the same
            // helper and order render/shot_visual.h recovers for the shots). A zero
            // direction composes to the translation-only matrix this used to build,
            // so the unposed callers (muzzle, impact, aura puffs) are unchanged.
            render::SceneRenderer::EffectInstance instance;
            instance.modelIndex = c.asset;
            instance.model = game::shotModelMatrix(c.position, c.direction);
            // A card's model ships an AnimationSet — RECOVERED: FUN_00436150 drives it with
            // age * 0.016, and the descriptor lifetime is derived from the clip's own length
            // (render/effect_catalog.h) — and the port used to draw every card in its bind
            // pose. See render/fx_cards.h's cardAnimationSeconds: the clock is the card's age
            // at the animation's own rate, not a rescale.
            const xm::Model& cardModel = app.scene.models[(size_t)c.asset].model;
            // The same guard the catalog uses when it derives a descriptor's lifetime
            // (buildFxAssets): a model with no clip, or one whose ticks-per-second never
            // arrived, has no clock — treating tps == 0 as 1 Hz instead would jump the card
            // to its last frame on the first update.
            const bool animated = app.opts.fxAnimation && !cardModel.anims.empty() &&
                                  cardModel.ticksPerSecond > 0.f &&
                                  cardModel.anims[0].duration > 0.f;
            if (animated) {
                const double animSeconds =
                    cardModel.anims[0].duration / cardModel.ticksPerSecond;
                xm::Controller pose;   // fresh: this card's animation starts from bind pose
                pose.bind(&cardModel);
                pose.setAnimation(0, false);
                pose.setTrackPosition(
                    0, game::cardAnimationSeconds(c.age, c.ttl, animSeconds));
                pose.evalWorld(cardWorld[ci]);
                instance.poseWorld = &cardWorld[ci];
            }
            instances.push_back(instance);
        }
        // The aura is fighter state, not an event: FUN_004205e0 draws the selected
        // data/aura model once per attach point, on each of the eleven bone matrices at
        // player+0x38c that FUN_00421010 refreshed from the rig's own Bip frames. The port
        // does the same — one instance per resolved point, in the fighter's model space,
        // which is where a bone-attached weapon already goes. See render/aura_attach.h for
        // the enumeration that settles the instance count.
        for (int i = 0; i < 2; ++i) {
            const game::FighterView& f = app.battle->fighter(i);
            if (!f.aura_active()) continue;
            // FUN_004205e0 selects the aura card by the wire mode value — 0, 1,
            // 5 for wire modes 0/1/2 — from the same seven data/aura/%02d.x
            // attachments, not one model for every mode.
            const int wire = static_cast<int>(f.hypermode());
            const int auraModel = wire == 2 ? 5 : wire;
            const int card = (auraModel >= 0 && auraModel < game::kAuraSlots)
                                 ? app.fxAttach[auraModel]
                                 : -1;
            if (card < 0) continue;
            const size_t rig = app.matchRig[i];
            if (rig >= app.worlds.size()) continue;
            const glm::mat4 base = matchRenderMatrix(app, i);
            for (int point = 0; point < app.auraAttach[i].found; ++point) {
                const size_t frame = (size_t)app.auraAttach[i].frame[point];
                if (frame >= app.worlds[rig].size()) continue;
                instances.push_back({card, base * app.worlds[rig][frame]});
            }
        }
        // FUN_004203f0: while +0x82c runs, data/aura/06.x draws on Bip01_Spine at 128 times
        // its size, in the negative of what is behind it. It never advances the model's own
        // animation, so the instance holds the bind pose.
        const int longStopCard = app.fxAttach[6];
        if (longStopCard >= 0)
            for (int i = 0; i < app.battle->fighter_count(); ++i) {
                if (!app.battle->fighter(i).long_stopped()) continue;
                const size_t rig = app.matchRig[i];
                if (rig >= app.worlds.size()) continue;
                const int spine = app.scene.models[rig].model.findFrame("Bip01_Spine");
                if (spine < 0 || (size_t)spine >= app.worlds[rig].size()) continue;
                if (longStopPose.empty()) {
                    xm::Controller pose;
                    pose.bind(&app.scene.models[(size_t)longStopCard].model);
                    pose.evalWorld(longStopPose);
                }
                render::SceneRenderer::EffectInstance sphere;
                sphere.modelIndex = longStopCard;
                sphere.poseWorld = &longStopPose;
                sphere.model = matchRenderMatrix(app, i) * app.worlds[rig][(size_t)spine] *
                               glm::scale(glm::mat4(1.f), glm::vec3(128.f));
                sphere.billboard = false;
                sphere.invert = true;
                instances.push_back(sphere);
            }
        // The in-flight shot draws the bullet's OWN model (issue #32), at the shot's own
        // transform — the original's shot render FUN_005f60b0 composes scale, rotation and
        // translation into the model's matrix and draws it, so the instance keeps its
        // orientation instead of being yawed at the camera. RECOVERED: which model (the
        // bullet record's 260-byte block, gameplay::BulletParameter::modelName). PORT RULE:
        // the aim direction, because the per-weapon update that fills the shot's own
        // rotation fields is not recovered — render/shot_visual.h has both. A level whose
        // model the install does not ship draws nothing here, which is what the original
        // does with the empty model slot that same missing file leaves behind; the tally
        // below makes that visible instead of silent.
        size_t coreShotPoses = 0;
        app.battle->for_each_shot([&](const game::ShotView& p) {
            const int owner = p.owner;
            // The shot carries the exact item row it was launched from, so the card is
            // that row's own model; the tier only chose the row back at the release.
            const int card = (owner >= 0 && p.bulletRow >= 0 && p.bulletRow < 64)
                                 ? app.fxShotModel[owner][static_cast<size_t>(p.bulletRow)] : -1;
            if (card < 0 || (size_t)card >= app.scene.models.size()) {
                ++app.fxShotNoModel;
                return;
            }
            const xm::Controller* pose = p.controller;
            if (!pose && p.animationSeconds >= 0.f) {
                const xm::Model& model = app.scene.models[(size_t)card].model;
                if (!model.anims.empty()) {
                    // Instances keep the pointer until setEffectInstances: the deque never moves it.
                    if (coreShotPoses >= app.coreShotControllers.size()) app.coreShotControllers.emplace_back();
                    xm::Controller& controller = app.coreShotControllers[coreShotPoses++];
                    controller.bind(&model);
                    controller.setAnimation(0, true);
                    controller.setTrackPosition(0, p.animationSeconds);
                    pose = &controller;
                }
            }
            instances.push_back({card,p.modelMatrix,p.billboard,pose,p.textureOverrides,p.tint});
            ++app.fxShotCards;
        });
    }
    app.renderer.setEffectInstances(instances);
}

// Issue #17's acceptance evidence: what the effect layer spawned, what the cap refused, and
// the high-water mark of the live set. `dropped` must stay 0 unless the population really
// reached the cap; `peak` is the number that has to stay bounded across a long 2v2.
static void printFxSummary(const App& app) {
    std::printf("fx cards     : events=%llu spawned=%llu dropped=%llu expired=%llu "
                "killed=%llu peak=%zu/%zu, shotModels=%llu shotModelMissing=%llu "
                "badEffectId=%llu, effectDrawsAtExit=%d\n",
                (unsigned long long)app.matchFxEvents,
                (unsigned long long)app.fxTally.spawned,
                (unsigned long long)app.fxTally.dropped,
                (unsigned long long)app.fxTally.expired,
                (unsigned long long)app.fxTally.killed,
                app.fxPeakLive, game::kMaxLiveFxCards,
                (unsigned long long)app.fxShotCards,
                (unsigned long long)app.fxShotNoModel,
                (unsigned long long)app.fxBadEffect,
                app.renderer.stats().effects);
}

// One fighter's HUD-side values (hud/hud_fill.h's HudFighterValues), sampled from the
// live fighter and the input that drives it. Split out of tickMatch because each view
// samples its OWN fighter and controller with the same rules (issue #12).
static void sampleHudFill(gameplay::HudFighterValues& out, const game::FighterView& f,
                          const fnd::input::PlayerState* input) {
    out.hp = f.hp() * 100 / f.max_hp();
    out.alive = f.is_alive();
    f.hp_ghost(out.hpLag);
    out.mainWhole = f.main_whole();
    out.mainFrac = f.main_frac();
    out.reloadOk = f.reload_ok();
    out.chargeWhole = f.charge_whole();
    out.chargeFrac = f.charge_frac();
    out.shootHeld = input && input->down[fnd::input::Shoot];
    out.chargeHoldFrac = f.charge_hold_frac();
    switch (f.charge_tier()) {   // ShotTier -> HoldTier (scenes.cpp:847-851)
        case game::ShotTier::Red:    out.chargeTier = game::HoldTier::Red; break;
        case game::ShotTier::Yellow: out.chargeTier = game::HoldTier::Yellow; break;
        default:                         out.chargeTier = game::HoldTier::Idle; break;
    }
    const game::HypermodeHud hp = game::hypermode_hud(f.hypermode());
    out.hyperName = hp.name;
    out.hyperGauge = f.hyper_gauge();
    out.hyperActive = f.hyper_active();
    out.hyperReady = f.hyper_ready();
    out.hyperSecondsLeft = f.hyper_seconds_left();
    out.hyperAura = game::GameRgb{(float)game::rgbR(hp.aura) / 255.f,
                                  (float)game::rgbG(hp.aura) / 255.f,
                                  (float)game::rgbB(hp.aura) / 255.f};
    out.hyperFlash = f.hyper_flash_alpha() / 252.f;
    out.stamina = f.stamina();
    // The reference's contextual gate is the state, not airborne() (scenes.cpp:879-882).
    out.staminaVisible = f.state() == game::FighterState::Run ||
                         f.state() == game::FighterState::Guard ||
                         f.state() == game::FighterState::Jump;
}

// One match frame: the reference's order lives in game::Battle::step; this adds
// what the scene added around it — tick inputs, the camera's target switch, the
// HUD values, the effect events and the debug cubes.
// ---------------------------------------------------------------------------

// The per-view presentation state — the arena camera each human view follows and that
// view's HUD — refreshed from the CURRENT match state. Split out of tickMatch (issue #47)
// because the pre-round countdown runs it every tick over a HELD round: the arena the digit
// animates over then has a live camera instead of the (0,0,0) seed it is built with, while
// nothing steps the simulation. `inputs` is the per-fighter input array tickMatch built;
// the countdown passes none, which is what keeps every view gesture (LockSwitch) out of the
// pre-round phase as well as out of the match itself.
static void updateMatchViews(App& app, const fnd::input::PlayerState* inputs[4], double dt) {
    for (int i = 0; i < app.battle->fighter_count(); ++i) {
        const game::FighterView& fighter = app.battle->fighter(i);
        app.arenaTargets[i].position = fighter.position();
        app.arenaTargets[i].facingYaw = fighter.facing_yaw();
        if (!historicalMatchCapture(app)) {
            // The movement turn (FUN_00421780 / FUN_0042db10) rotates the body,
            // not the lock-on view. Keep the camera's orbit on the combat bearing.
            const int target = app.battle->aim_target(i);
            if (target >= 0) {
                const glm::vec3 direction = app.battle->fighter(target).position() - fighter.position();
                if (direction.x * direction.x + direction.z * direction.z > 0.0001f)
                    app.arenaTargets[i].facingYaw = std::atan2(direction.x, direction.z);
            }
        }
        app.arenaTargets[i].alive = fighter.is_alive();
    }

    // Camera and HUD, once per human view (issue #12). The original runs this same loop
    // over controller slots (FUN_006396f0:108-188), and each view's state is keyed by its
    // controller: the camera follows that view's own fighter, its LockSwitch gestures
    // re-pick that view's target, and its HUD is filled from that fighter's resources.
    // The caller owns the match step; this loop never advances the simulation.
    const gameplay::CollisionQuery cameraQuery =
        (!historicalMatchCapture(app) && !app.opts.noCameraClamp)
            ? gameplay::CollisionQuery{&app.cameraCollision}
            : gameplay::CollisionQuery{};
    for (int v = 0; v < app.matchViewCount; ++v) {
        game::MatchView& view = app.matchViews[v];
        if (!view.active() || view.fighter >= app.battle->fighter_count()) continue;
        const fnd::input::PlayerState* viewInput = inputs[view.fighter];
        // Scripted/offscreen standalone runs retain the banked null-query camera path;
        // live matches clamp the eye against collision_camera.x unless the A/B switch asks
        // for the historical unclamped behavior. The blend remains per call as in the port.
        // The render blends this tick's camera with the one the PREVIOUS tick ended on
        // (glm::mix(previousEye, camera.eye(), matchAlpha) in buildFrameViews), so the
        // snapshot has to advance once per tick, before the update. Advancing it only on
        // the first tick left every live frame interpolating from the match's opening
        // pose: the eye then swept between that pose and the current one as the tick
        // fraction changed, which reads as a camera that never settles. Captures never
        // showed it because matchAlpha is 1 while capturing, where the mix returns the
        // current camera unchanged (D9's one-update-per-frame recipes).
        view.previousEye = view.camera.eye();
        view.previousTarget = view.camera.target();
        const auto& cameraFighter = app.battle->fighter(view.followed);
        const int actionOpponent = app.battle->locked_target(view.followed);
        view.camera.set_action(cameraFighter.action_camera(), cameraFighter.position(), cameraFighter.facing_yaw(),
            actionOpponent >= 0 ? app.battle->fighter(actionOpponent).position() : cameraFighter.position());
        game::CameraPoseView corePose;
        if (app.battle->camera_pose(view.fighter, corePose))
            view.camera.set_external_pose(corePose.eye, corePose.lookAt, corePose.fovY, corePose.nearPlane);
        else
            view.camera.update(dt,cameraQuery);
        // Mirror the camera's own selection back into the view. Since issue #51 the tap no
        // longer cycles the camera and nothing else in a match calls cycle_target, so this
        // is the construction value for the whole match; it stays because view.followed IS
        // the per-view "who am I following" the split-screen evidence line prints and
        // tests/lock_switch_camera_test.cpp asserts, and dropping the mirror would let the
        // two silently disagree the day anything re-points a camera again.
        if (view.camera.active_target_index() >= 0) view.followed = view.camera.active_target_index();

        // This view's HUD: the ported value computation (hud/hud_fill.h, unchanged),
        // fed from the view's own fighter. Which side goes where is the DX9 layout's:
        // the balloon corners are the only two-side readout (side 0 left, side 1 right),
        // every other field belongs to the viewer's fighter.
        gameplay::HudFillInput hf;
        sampleHudFill(hf.p1, app.battle->fighter(view.fighter), viewInput);
        view.hud = gameplay::hudStateFor(app.battle->economy(), hf);
        // D1: the render-FPS counter rides the HUD state (60 while capturing). The
        // original draws it once, outside its view loop (FUN_006396f0:203-210), so only
        // the first view carries it.
        view.hud.fps = app.fpsShown;
        const game::BattleNotice notice = app.battle->notice(view.fighter);
        view.hud.noticeType = notice.type;
        view.hud.noticeScale = notice.scale;
        const game::BattleResultNotice result = app.battle->result_notice();
        view.hud.resultWinner = result.winner;
        view.hud.resultMain = result.main;
        view.hud.resultSecondary = result.secondary;
        view.hud.resultMainScale = result.mainScale;
        view.hud.resultSecondaryScale = result.secondaryScale;
        view.hud.resultBarOffset = result.barOffset;
        view.hud.commandCell = app.battle->cpu_command(view.fighter, view.hud.commandScale);
        view.hud.roundTicks = app.battle->round_ticks_left();
        view.hud.directionWarnings.clear();
        for (const game::DirectionWarningView& w : app.battle->direction_warnings(view.fighter)) {
            if (w.state == 0 || w.direction < 0 || w.direction > 3) continue;
            view.hud.directionWarnings.push_back(
                {w.direction, w.state == 1 ? 0 : (w.ticks % 10 < 5) + 1, (float)w.ticks * .005f + 1.f});
        }
        const game::LockRingView lockRing = app.battle->lock_ring(view.fighter);
        view.hud.scope = lockRing.manualAim;
        view.hud.showFps = (v == 0);
        // The composer is clock-free by design, so the frame counter the original's
        // alternations and pulse read (FUN_00644150's `(frame % 0x1e) / 0xf` flash pair and
        // the balloon popup's growth) is carried in the state instead of read from a clock.
        view.hud.hudFrame = (int)app.matchFrame;
        // Outgoing and incoming locks are distinct: having a target does not tell
        // us the fighter's team or whether its lock is mutual with this viewer.
        const int lockedTarget = app.battle->locked_target(view.fighter);
        const int viewPulse = app.battle->lock_pulse(view.fighter);
        // One HUD entry per ROSTER entry (issue #13): the participant's own fighter, its
        // team and its controller. A 1v1 fills two, a 2v2 all four.
        for (int i = 0; i < ui::kHudFighterCount; ++i) {
            view.hud.fighters[i] = ui::HudFighterHud{};
            const int fighterIndex = hudEntryFighter(app, i);
            if (fighterIndex < 0) continue;
            const ui::Participant& p = app.participants[i];
            const game::FighterView& f = app.battle->fighter(fighterIndex);
            const int viewSide = app.battle->side(view.fighter);
            view.hud.fighters[i].role = fighterIndex == view.fighter
                ? ui::HudFighterRole::Owner
                : (app.battle->side(fighterIndex) == viewSide ? ui::HudFighterRole::Ally
                                                                    : ui::HudFighterRole::Enemy);
            view.hud.fighters[i].target = (fighterIndex == lockedTarget);
            view.hud.fighters[i].targetsViewer =
                app.battle->locked_target(fighterIndex) == view.fighter;
            view.hud.fighters[i].ringPulse =
                (fighterIndex == lockedTarget) ? viewPulse : 0;
            // Slot 0 is 1P and slot 4 is com in the tag atlas (P01 (320,256,64,32) rows);
            // the red copies sit four rows down, which is the tagSheet index.
            view.hud.fighters[i].slot = p.controller;
            view.hud.fighters[i].tagSheet = p.team;
            view.hud.fighters[i].hp = (float)f.hp() / f.max_hp();
            float ghost = 0.f;
            view.hud.fighters[i].hpLag = f.hp_ghost(ghost) ? ghost / 100.f : view.hud.fighters[i].hp;
            view.hud.fighters[i].allyBar = view.hud.fighters[i].role == ui::HudFighterRole::Ally;
            // draw_battle_lock_hud's cell: invincible, on an ally, Friendship, or plain.
            if (!lockRing.manualAim && fighterIndex == lockRing.target) {
                ui::HudFighterHud& hud = view.hud.fighters[i];
                hud.ring = true;
                hud.ringCol = !lockRing.invincible && !lockRing.onAlly && lockRing.friendship ? 2 : 0;
                hud.ringRow = lockRing.invincible ? 0 : lockRing.onAlly ? 2
                              : lockRing.friendship ? (lockRing.joint ? (view.hud.hudFrame % 30) / 15 : 0) : 1;
                hud.ringSecond = lockRing.shared && !lockRing.onAlly;
            }
        }
    }

    // The banked trace (tests/compare_match_traces.py) prints the eye the reference camera
    // reported for the primary view, so keep app.eye/app.target on it: the render loop
    // later replaces them with the interpolated presentation values.
    const game::MatchView& primary = app.matchViews[0];
    app.eye = primary.camera.eye();
    app.target = primary.camera.target();
}

// ---------------------------------------------------------------------------------------
// The battle behind the result screen: the core keeps animating, with no input and no sound,
// because the screen has taken over the audio.
static void tickResultScene(App& app, double dt) {
    for (int i = 0; i < app.battle->fighter_count(); ++i)
        app.previousFighter[i] = app.battle->fighter(i).pose();
    const fnd::input::PlayerState* none[4] = {};
    const game::BattleFrame f = app.battle->step(none, dt);
    for (const auto& spawn : f.effectSpawns) spawnEffect(app, app.matchFx, spawn.id, spawn.position, spawn.direction);
    updateFxCards(app, app.matchFx, app.matchFxEvents, (float)dt);
    updateMatchViews(app, none, dt);
}

static void tickMatch(App& app, double dt) {
    for (int i = 0; i < app.battle->fighter_count(); ++i)
        app.previousFighter[i] = app.battle->fighter(i).pose();
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
    // lookup yields a FIGHTER index, and the controller slot is a third, distinct index space.
    int viewerIndex = 0;
    if (app.frontendMatch)
        for (int j = 0; j < app.battleLaunch.fighterCount; ++j)
            if (app.battleLaunch.fighters[j].panel == ui::kFrontendBattleSlots[0]) {
                viewerIndex = j;
                break;
            }

    const fnd::input::PlayerState* inputs[4] = {p1, p2, nullptr, nullptr};
    if (app.frontendMatch) {
        for (int i = 0; i < app.battle->fighter_count(); ++i) {
            const int panel = app.battleLaunch.fighters[i].panel;
            const int controller = app.frontend.slots[panel].controller;
            // A null input is a COM: the core runs its own CPU driver.
            inputs[i] = controller >= 0 && controller < 4 ? &app.tickInput[controller] : nullptr;
        }
    }
    // FUN_006358c0's one global listener follows DAT_006cfba4's selected fighter.
    // The port has per-view cameras; the first human view is the explicit single-listener
    // adaptation, otherwise use the standalone P1 viewer.
    const int listenerFighter = app.matchViewCount > 0 && app.matchViews[0].followed >= 0
                                    ? app.matchViews[0].followed : viewerIndex;
    app.battle->set_primary_listener_fighter(listenerFighter);
    const game::BattleFrame f = app.battle->step(inputs, dt);
    if (app.versusAudioOn)
        app.versusBgmPushed += app.versusLoop.push_next(app.versusAudio, 1024);
    // The core's own audio requests for this tick.
    if (app.combatAudio) {
        const auto toArray = [](const glm::vec3& v) { return fnd::audio::AudioPoint3{v.x, v.y, v.z}; };
        for (const auto& cue : f.soundCues) {
            if (cue.system) app.combatAudio->play_system_se(cue.id);
            else app.combatAudio->play_se(cue.id, cue.positional, toArray(cue.position),
                                                 toArray(f.audioListenerPosition), toArray(f.audioListenerForward),
                                                 f.audioListenerValid);
        }
        for (const auto& cue : f.voiceCues)
            app.combatAudio->play_voice(cue.fighter, cue.path, cue.positional, toArray(cue.position),
                                               toArray(f.audioListenerPosition), toArray(f.audioListenerForward),
                                               f.audioListenerValid);
        if (app.opts.combatAudioLog)
            for (const auto& cue : f.voiceCues)
                std::printf("[combat-audio] tick %llu voice fighter=%d %s\n", (unsigned long long)app.matchFrame, cue.fighter, cue.path.c_str());
    }
    for (const auto& spawn : f.effectSpawns)
        if (!spawnEffect(app, app.matchFx, spawn.id, spawn.position, spawn.direction)) ++app.fxBadEffect;
    for (int i = 0; i < app.battle->fighter_count(); ++i) {
        // Hypermode: the recovered burning effect 380 re-spawns every 7 frames
        // ONLY while the fighter is in the downed/burning move family
        // (FUN_0042e110:83-95 gates on executor rows 0x6a/0x6b/0x6c/0xce) — never
        // for a merely hyper-active fighter, whose aura is the attach card, not
        // the burn (issue #71). The port approximates the family with its
        // Knockdown state. The cadence is the simulation tick, not the render
        // rate, and the jitter is a deterministic function of (fighter, tick) — the
        // original's rand()%100 - 50 box around the fighter's position.
        if (app.battle->fighter(i).aura_active() &&
            app.battle->fighter(i).state() == game::FighterState::Knockdown &&
            app.matchFrame % 7 == 0) {
            const uint32_t h = (uint32_t)(app.matchFrame / 7) * 2654435761u +
                               (uint32_t)i * 40503u;
            const glm::vec3 at = app.battle->fighter(i).position() +
                                 glm::vec3((float)(h % 100) - 50.f,
                                           (float)((h >> 8) % 60),
                                           (float)((h >> 16) % 100) - 50.f);
            spawnEffect(app, app.matchFx, 380, at);
        }
    }
    // The in-flight shot is NOT a card: it is the bullet's own model, drawn at the shot's
    // own transform by placeFxCards() (issue #32). See render/shot_visual.h.
    updateFxCards(app, app.matchFx, app.matchFxEvents, (float)dt);

    updateMatchViews(app, inputs, dt);

    if (f.roundOver) {
        app.matchRoundOverFrame = app.matchFrame;
        // Issue #11: roundOverSide is the WINNER (the original's scene+0x442c), and
        // roundEnd() says which rule ended it — a balloon burst or the time limit.
        const gameplay::MatchEconomy& eco = app.battle->economy();
        std::printf("[daybreak] match: round over, side %d wins (%s) at frame %llu\n",
                    f.roundOverSide,
                    eco.roundEnd() == gameplay::RoundEnd::Timeout ? "time up" : "burst",
                    (unsigned long long)app.matchFrame);
        printFxSummary(app);
    }
}

// The trace the DX9 build prints under DAYBREAK_CAMINFO, reproduced field for field
// so `tests/compare_match_traces.py` can diff the two implementations. The probe
// fires on render calls 1, 61, 121, ... (scenes.cpp:802-805: `probe++ % 60 == 0`).
static void traceMatch(App& app) {
    if (!std::getenv("DAYBREAK_CAMINFO")) return;
    if ((app.matchFrame - 1) % 60 != 0) return;
    const game::FighterView& a = app.battle->fighter(0);
    const game::FighterView& b = app.battle->fighter(1);
    std::printf("[daybreak] cam eye=(%.0f,%.0f,%.0f) p1=(%.0f,%.0f,%.0f,%s) "
                "p2=(%.0f,%.0f,%.0f,%s)\n",
                app.eye.x, app.eye.y, app.eye.z, a.position().x, a.position().y, a.position().z,
                game::state_to_anim_name(a.state()), b.position().x, b.position().y,
                b.position().z, game::state_to_anim_name(b.state()));
    // The set that actually plays, next to the state it came from, and why it is what
    // it is. `state_to_anim_name` stays the compared field: the DX9 side of the trace
    // binds no animation sets at all, so it has no set to print and changing that field
    // would destroy the only cross-implementation oracle this project has. The two
    // annotations keep an unmapped state visible instead of silent: "(no selector)" is
    // the recovered hold (Guard binds no clip at all), while "(fallback)" is a selector
    // or table row the port has not recovered.
    auto annotate = [](const game::FighterView& f) -> const char* {
        if (f.anim_no_selector()) return " (no selector)";
        if (f.anim_fallback())    return " (fallback)";
        return "";
    };
    std::printf("[daybreak] anim p1=set %d %s%s p2=set %d %s%s\n",
                a.anim_set_index(), a.anim_set_name(), annotate(a),
                b.anim_set_index(), b.anim_set_name(), annotate(b));
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
    // Issue #17: shots and sparks draw as real effect cards by default; these cubes are
    // the explicit A/B view behind --debug-prims, which is also where the aura cube lives.
    if (app.opts.debugPrims) {
        app.battle->for_each_shot([&](const game::ShotView& p) {
            app.matchCubes.add(p.pos, game::kShotCubeSize, p.color);
        });
        app.battle->for_each_spark([&](const game::SparkView& s) {
            app.matchCubes.add(s.pos, s.size * 0.5f, s.color);
        });
    }
    if (!app.opts.debugPrims) return;   // the real aura card is the default view
    // The aura cube: the reference render's second, additive cube pass, drawn in the
    // fighter's own space: its local centre through the fighter's model matrix.
    for (int i = 0; i < 2; ++i) {
        const game::FighterView& f = app.battle->fighter(i);
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

