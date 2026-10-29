// Issue #16, asset-backed: a live COM 2v2 on four shipped combos drives the real combat audio
// policy through the shared frame -> event derivation, and the run is repeated to show channel
// cleanup. Skipped when the install (or one of its item/move tables) is absent, like the other
// asset-backed tests; the device-free coverage lives in combat_audio_test.
#include <cstdio>
#include <cstring>
#include <cmath>
#include <filesystem>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#condition); return 1; } } while (false)

#include "audio/combat_audio.h"
#include "gameplay/bot_brain.h"
#include "gameplay/bot_input.h"
#include "gameplay/character_moves.h"
#include "gameplay/fixed_step.h"
#include "gameplay/match.h"
#include "gameplay/weapon_definition.h"

namespace fs = std::filesystem;
using namespace fnd::audio;

namespace {

fs::path findInstall() {
    if (const char* env = std::getenv("GAME_DIR")) return fs::path(env);
    fs::path game = fs::path("Higurashi-Daybreak");
    for (const fs::path& d : {fs::absolute(fs::path(".")), fs::current_path()}) {
        for (fs::path r = d; !r.empty(); r = r.parent_path()) {
            std::error_code ec;
            if (fs::is_directory(r / "remake" / "foundation", ec)) {
                game = r / "Higurashi-Daybreak";
                break;
            }
            if (r == r.parent_path()) break;
        }
        std::error_code ec;
        if (fs::is_directory(game / "data", ec)) return game;
    }
    return fs::path();
}

bool readFile(const fs::path& p, std::vector<uint8_t>& out) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return false;
    out.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    return !out.empty();
}

// Records the cues and checks every stem against the INSTALL: a resolved voice/SE that does
// not name a shipped file would be an invented mapping, which is the failure this test exists
// to catch. `stop_bus` mirrors the engine's bus-level stop so the cleanup assertion is real.
class InstallSink : public CombatAudioSink {
public:
    explicit InstallSink(fs::path install) : install_(std::move(install)) {}
    int play(const std::string& stem, SfxBus bus, int channel) override {
        const int ch = channel >= 0 ? channel : 16;  // the engine's own auto-pick, simplified
        if (bus == SfxBus::Voice) busy[static_cast<size_t>(ch)] = true;
        Played p{stem, bus, ch};
        p.on_disk = fs::exists(install_ / (stem + ".cnv")) || fs::exists(install_ / (stem + ".wav"));
        played.push_back(p);
        return ch;
    }
    void stop(int channel) override {
        if (channel >= 0 && channel < 32) busy[static_cast<size_t>(channel)] = false;
    }
    void stop_bus(SfxBus bus) override {
        int first = 0, last = 0;
        if (!bus_range(bus, first, last)) return;
        for (int c = first; c <= last; ++c) stop(c);
    }
    struct Played {
        std::string stem;
        SfxBus      bus;
        int         channel;
        bool        on_disk = false;
    };
    int busy_count() const {
        int n = 0;
        for (bool b : busy) n += b ? 1 : 0;
        return n;
    }
    fs::path install_;
    bool busy[32] = {};
    std::vector<Played> played;
};

// The probe FUN_00431e70 performs: NNN upward until the file is missing.
int probe(const fs::path& install, const std::string& dir, VoiceEvent event, bool b_dir) {
    int count = 0;
    for (int i = 0; i < 4; ++i) {
        const std::string stem = voice_asset_stem(dir, event, b_dir, i);
        if (stem.empty()) break;
        if (!fs::exists(install / (stem + ".cnv")) && !fs::exists(install / (stem + ".wav"))) break;
        ++count;
    }
    return count;
}

constexpr VoiceEvent kEvents[] = {
    VoiceEvent::BattleStart, VoiceEvent::AttackA,   VoiceEvent::Fire,     VoiceEvent::Damage,
    VoiceEvent::DamageDown,  VoiceEvent::Guard,     VoiceEvent::Guarded,  VoiceEvent::AttackKO,
    VoiceEvent::DamageKO,    VoiceEvent::Revival,   VoiceEvent::Oyashiro,
    VoiceEvent::TagBack,
    VoiceEvent::ShotA, VoiceEvent::ShotB, VoiceEvent::ShotC, VoiceEvent::ShotFinal,
    VoiceEvent::SpecialA,
};

// The adapter the host also uses, over a live Match.
class MatchSource : public CombatEventSource {
public:
    explicit MatchSource(const gameplay::Match& m) : match_(m) {}
    int fighter_count() const override { return match_.config().fighterCount; }
    bool alive(int fighter) const override {
        return fighter >= 0 && fighter < match_.config().fighterCount &&
               match_.fighter(fighter).is_alive();
    }
    const gameplay::Match& match_;
};

CombatFrameView viewOf(const gameplay::MatchFrame& f) {
    CombatFrameView v;
    for (int i = 0; i < 4; ++i) {
        v.swing_started[i] = f.swingStarted[i];
        v.melee_voice[i] = f.meleeVoice[i];
        v.melee_voice_alternative[i] = f.meleeVoiceAlternative[i];
        v.melee_voice_audited[i] = f.sourceMeleeVoiceAudited[i];
        v.sound_effect_id[i] = f.soundEffectId[i];
        v.sound_effect_positional[i] = f.soundEffectPositional[i];
        v.sound_effect_position[i] = {f.soundEffectPosition[i].x,
                                       f.soundEffectPosition[i].y,
                                       f.soundEffectPosition[i].z};
        v.shot_fired[i]    = f.shotFired[i];
        v.shot_voice[i] = f.shotVoice[i];
        v.shot_voice_alternative[i] = f.shotVoiceAlternative[i];
        v.shot_voice_audited[i] = f.sourceShotVoiceAudited[i];
        v.hyper_started[i] = f.hyperStarted[i];
        v.hyper_mode[i] = f.hyperMode[i];
        v.guard_started[i] = f.guardStarted[i];
        v.respawned[i]     = f.respawned[i];
        v.blocked[i]       = f.blocked[i];
        v.melee_hit[i]     = f.meleeHit[i];
        v.melee_victim[i]  = f.meleeVictim[i];
        v.overkill_hits[i] = f.overkillHits[i];
    }
    v.listener_position = {f.audioListenerPosition.x, f.audioListenerPosition.y,
                           f.audioListenerPosition.z};
    v.listener_forward = {f.audioListenerForward.x, f.audioListenerForward.y,
                          f.audioListenerForward.z};
    v.listener_valid = f.audioListenerValid;
    v.shot_hit_count = f.shotHitCount;
    for (int k = 0; k < f.shotHitCount; ++k) {
        v.shot_hits[k].shooter = f.shotHits[k].shooter;
        v.shot_hits[k].victim  = f.shotHits[k].victim;
        v.shot_hits[k].blocked = f.shotHits[k].blocked;
    }
    return v;
}

}  // namespace

int main() {
    const fs::path install = findInstall();
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data", ec)) {
        // Exit 77: the install is this suite's only prerequisite, and CTest's
        // SKIP_RETURN_CODE records it as a skip rather than a pass (audit finding B).
        // The device-free policy coverage lives in combat_audio_test either way.
        std::puts("combat_audio_match_test: no install, skipped (device-free coverage is in "
                  "combat_audio_test)");
        return 77;
    }
    // Four shipped combos, slot 0, exactly as the live path binds them (AGENTS rule 7).
    static const int kRoster[4] = {0, 1, 2, 4};
    std::vector<std::unique_ptr<gameplay::WeaponDefinition>> weapons;
    std::vector<std::unique_ptr<gameplay::CharacterMoves>> tables;
    std::string err;
    for (int i = 0; i < 4; ++i) {
        const int character = kRoster[i];
        const int itemId = gameplay::kWeaponIds[character][0];
        char item[64];
        std::snprintf(item, sizeof(item), "item/%03d.dat", itemId);
        std::vector<uint8_t> bytes;
        if (!readFile(install / "data" / item, bytes)) {
            // The install is present, so this file is expected to be there: a missing
            // item is a broken install, and calling it a skip hid exactly that.
            std::printf("combat_audio_match_test: FAIL: %s is missing from an install that "
                        "exists\n", item);
            return 1;
        }
        auto w = std::make_unique<gameplay::WeaponDefinition>();
        if (!w->parse(itemId, bytes.data(), bytes.size(), err)) {
            std::printf("combat_audio_match_test: FAIL: %s did not parse: %s\n",
                        item, err.c_str());
            return 1;
        }
        char table[64];
        std::snprintf(table, sizeof(table), "%s/00.dat", gameplay::kCharacterDirs[character]);
        std::vector<uint8_t> moveBytes;
        auto m = std::make_unique<gameplay::CharacterMoves>();
        if (!readFile(install / "data" / table, moveBytes)) {
            std::printf("combat_audio_match_test: FAIL: %s is missing from an install that "
                        "exists\n", table);
            return 1;
        }
        if (!m->parse(moveBytes.data(), moveBytes.size(), err)) {
            std::printf("combat_audio_match_test: FAIL: %s did not parse: %s\n",
                        table, err.c_str());
            return 1;
        }
        weapons.push_back(std::move(w));
        tables.push_back(std::move(m));
    }

    InstallSink sink(install);
    CombatAudio audio(sink);
    long long total_events = 0;
    long long voice_files_missing = 0;
    long long channel_high_water = 0;

    for (int match_index = 0; match_index < 2; ++match_index) {
        gameplay::MatchConfig config;
        config.fighterCount = 4;
        const int sides[4] = {0, 0, 1, 1};
        for (int i = 0; i < 4; ++i) {
            config.side[i] = sides[i];
            config.spawn[i] = glm::vec3(-260.f + 90.f * i, 0.f, -160.f);
            config.facing[i] = 0.f;
            config.weapon[i] = weapons[(size_t)i].get();
            config.moves[i] = tables[(size_t)i].get();
            // The two conditions the live release round does not reach on its own: a full
            // gauge (so the COM's own hyper decision fires) and reduced HP (so hits KO, bodies
            // go down and the respawn path runs) — low enough to reach a KO quickly, high
            // enough that the fighters keep fighting. Both are MatchConfig inputs.
            config.startGauge[i] = 1.0f;
            config.startHP[i] = 30;
        }
        // A full balloon budget: the round must not end after the first two KOs, or the run
        // would never reach the respawn/hyper/overkill mix it exists to cover.
        config.balloonSize[0] = config.balloonSize[1] = 100;

        gameplay::Match match;
        const xm::Model* models[4] = {};
        xm::Controller* anims[4] = {};
        match.reset(config, models, anims, nullptr, nullptr, nullptr);
        match.economy().setLogFile(nullptr);

        gameplay::BotBrain brains[4];
        gameplay::BotContext ctx[4];
        for (int i = 0; i < 4; ++i) {
            brains[i].reset(gameplay::bot_seed(gameplay::MatchRng::kDefaultSeed, i));
            ctx[i].match = &match;
            ctx[i].fighterIndex = i;
            ctx[i].leaderTarget = match.locked_target(0);
        }

        // The audio side, set up exactly like the host: per-fighter voice directory from the
        // character, alternatives probed from the install, then one dispatch per tick.
        audio.begin_match(4);
        for (int i = 0; i < 4; ++i) {
            const std::string dir =
                std::string("data/voice/") + gameplay::kCharacterDirs[kRoster[i]];
            audio.set_fighter_voice(i, dir, false);
            for (VoiceEvent e : kEvents)
                audio.set_voice_alternatives(i, e, probe(install, dir, e, false));
        }

        fnd::input::PlayerState inputs[4];
        bool match_start = true;
        bool hyper_input_driven = false;
        bool round_over = false;
        uint32_t tick = 0;
        for (; tick < 4000 && !round_over; ++tick) {
            for (int i = 0; i < 4; ++i) gameplay::updateBotInput(brains[i], ctx[i], inputs[i], tick);
            // This gate verifies audio dispatch. Drive its hyper input explicitly so
            // a slower source magazine does not make coverage depend on an AI seed.
            // Fighter 0 keeps the default Friendship mode, so the run covers its
            // S-press presentation (TagBack line plus SE 7, issue #71).
            if (!hyper_input_driven && match.fighter(0).actionable()) {
                match.fighter(0).set_hyper_gauge(1.f);
                inputs[0].down[fnd::input::Action::Special] = true;
                inputs[0].just_pressed[fnd::input::Action::Special] = true;
                hyper_input_driven = true;
            }
            const fnd::input::PlayerState* in[4] = {&inputs[0], &inputs[1], &inputs[2], &inputs[3]};
            const gameplay::MatchFrame frame = match.step(in, gameplay::FixedStep::seconds);
            CHECK(frame.audioListenerValid);
            CHECK(std::isfinite(frame.audioListenerPosition.x) &&
                  std::isfinite(frame.audioListenerPosition.y) &&
                  std::isfinite(frame.audioListenerPosition.z));
            CHECK(std::abs(glm::length(frame.audioListenerForward) - 1.f) < .001f);
            MatchSource source(match);
            const CombatEventList list =
                combat_events_for_frame(source, viewOf(frame), tick + 1, match_start);
            match_start = false;
            for (int i = 0; i < list.count; ++i) {
                audio.dispatch(list.events[i]);
                ++total_events;
            }
            const int claimed = audio.claimed_channels();
            if (claimed > channel_high_water) channel_high_water = claimed;
            round_over = frame.roundOver;
        }
        std::printf("combat_audio_match_test: match %d ran %u ticks\n", match_index, tick);

        const auto& stats = audio.stats();
        CHECK(stats.dispatched[static_cast<int>(CombatEventKind::MeleeSwing)] > 0);
        CHECK(stats.dispatched[static_cast<int>(CombatEventKind::ShotFired)] > 0);
        CHECK(stats.dispatched[static_cast<int>(CombatEventKind::Hit)] > 0);
        CHECK(stats.dispatched[static_cast<int>(CombatEventKind::Ko)] > 0);
        CHECK(stats.dispatched[static_cast<int>(CombatEventKind::Respawn)] > 0);
        CHECK(stats.dispatched[static_cast<int>(CombatEventKind::HyperActivate)] > 0);
        CHECK(stats.voice_plays > 0);
        CHECK(stats.se_plays > 0);          // the KO/overkill ids on the SFX bus
        CHECK(stats.duplicates == 0);       // one dispatch per event id, across both matches
        CHECK(stats.voice_missing == 0);    // every voice the run asked for is shipped
        CHECK(audio.claimed_channels() == 4);
        CHECK(sink.busy_count() == 4);
        audio.end_match();
        CHECK(audio.claimed_channels() == 0);
        CHECK(sink.busy_count() == 0);
    }

    // Every cue the run played names a file the install actually ships.
    for (const InstallSink::Played& p : sink.played)
        if (!p.on_disk) {
            std::fprintf(stderr, "missing asset for cue %s\n", p.stem.c_str());
            ++voice_files_missing;
        }
    CHECK(voice_files_missing == 0);
    CHECK(sink.played.size() > 100);
    CHECK(total_events > 100);
    CHECK(channel_high_water == 4);  // one voice channel per fighter, never more

    std::printf("combat_audio_match_test: %lld events over two matches, %zu cues, "
                "channel high-water %lld, all files shipped\n",
                total_events, sink.played.size(), channel_high_water);
    return 0;
}
