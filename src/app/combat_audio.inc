// Combat audio: the engine-backed sink, the lazily decoded sample cache, the
// per-match voice setup and the two match-end evidence functions.
// Included by main.cpp inside its anonymous namespace.

// Reads go through the asset source, so an install with only its .dat bundles
// plays BGM without an extracted tree.
//
// Only the track itself is required. A missing or unusable loop sheet is "no
// loop region" (resolve_loop_sheet, audio_format.h), so a track that ships
// without one — data/bgm/vs.ogg is the only one on this install — plays once to
// EOF instead of failing the load; the region is still written to the player,
// which would otherwise keep the previous track's points.

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
    int play_spatial(const std::string& stem, int channel,
                     const SpatialRequest& request) override {
        if (!app_.versusAudioOn) return -1;
        const fnd::audio::SfxHandle handle = handle_for(stem);
        if (handle < 0) return -1;
        fnd::audio::SpatialPlayRequest req;
        req.channel = channel;
        req.source = request.source;
        req.listener = request.listener;
        req.listenerForward = request.listenerForward;
        req.rolloffFactor = request.rolloffFactor;
        req.minDistance = request.minDistance;
        return app_.versusAudio.play_spatial(handle, req);
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
    App& app_;
};

static void setupCombatVoices(App& app) {
    if (app.combatAudio) app.combatAudio->begin_match();
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
    std::printf("[combat-audio] match end: voice=%d se=%d suspended_drops=%d voice_missing=%d se_missing=%d "
                "channels_held=%d\n", stats.voice_plays, stats.se_plays, stats.suspended_drops,
                stats.voice_missing, stats.se_missing, app.combatAudio->claimed_channels());
}
