// Issue #16: the live combat SE/voice policy — event identity, de-duplication, per-fighter
// voice bookkeeping, suspend/resume and repeated-match cleanup. Device-free: the sink records
// calls, so no SDL device and no audio hardware are involved.
#include <cstdio>
#include <string>
#include <vector>
#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr,"%s:%d: %s\n",__FILE__,__LINE__,#condition); return 1; } } while (false)

#include "audio/audio_engine.h"
#include "audio/combat_audio.h"
#include <cstdlib>

using namespace fnd::audio;

namespace {

struct Played {
    std::string stem;
    SfxBus      bus;
    int         channel;
};

// Records every call; `busy` mirrors the engine's channel-busy notion so the dispatcher's
// claim/release bookkeeping can be checked without a device.
class Recorder : public CombatAudioSink {
public:
    int play(const std::string& stem, SfxBus bus, int channel) override {
        const int ch = channel >= 0 ? channel : next_free(bus);
        if (ch < 0) return -1;
        if (!accept) return -1;
        // Only the VOICE bus is claimed by this layer (one channel per fighter, released by
        // stop()/end_match()). An SFX slot is one-shot: the engine frees it when its stream
        // drains, exactly like the original's 32-slot bank, so it is not tracked as busy.
        if (bus == SfxBus::Voice) busy[static_cast<size_t>(ch)] = true;
        played.push_back(Played{stem, bus, ch});
        return ch;
    }
    int play_spatial(const std::string& stem, int channel,
                     const SpatialRequest& request) override {
        spatial.push_back(request);
        return play(stem, SfxBus::Sfx, channel);
    }
    void stop(int channel) override {
        if (channel >= 0 && channel < 32) busy[static_cast<size_t>(channel)] = false;
        stops.push_back(channel);
    }
    void stop_bus(SfxBus bus) override {
        int first = 0, last = 0;
        if (!bus_range(bus, first, last)) return;
        for (int c = first; c <= last; ++c) stop(c);
        bus_stops.push_back(bus);
    }
    int next_free(SfxBus bus) const {
        int first = 0, last = 0;
        if (!bus_range(bus, first, last)) return -1;
        for (int c = first; c <= last; ++c)
            if (!busy[static_cast<size_t>(c)]) return c;
        return -1;
    }
    int busy_count() const {
        int n = 0;
        for (bool b : busy) n += b ? 1 : 0;
        return n;
    }
    bool accept = true;
    bool busy[32] = {};
    std::vector<Played> played;
    std::vector<SpatialRequest> spatial;
    std::vector<int> stops;
    std::vector<SfxBus> bus_stops;
};

CombatEvent ev(CombatEventKind kind, int fighter, int source, uint32_t tick, uint8_t seq = 0,
               bool shot = false, int hyper_mode = -1) {
    CombatEvent e;
    e.kind = kind;
    e.fighter = fighter;
    e.source = source;
    e.tick = tick;
    e.seq = seq;
    e.shot = shot;
    e.hyper_mode = hyper_mode;
    return e;
}

}  // namespace

// A source stub for the frame -> event derivation (the host's adapter is the only other
// implementation, and the derivation is what the release path shares with it).
struct SourceStub : CombatEventSource {
    int count = 4;
    bool aliveFlags[4] = {true, true, true, true};
    int fighter_count() const override { return count; }
    bool alive(int fighter) const override {
        return fighter >= 0 && fighter < 4 && aliveFlags[fighter];
    }
};

// The frame -> event derivation carries the melee voice, the SE and the audited-swing
// handshake; the cue resolution for those kinds is pinned above, this pins the emit side.
bool testFrameEvents() {
    SourceStub source;
    CombatFrameView view;
    view.swing_started[0] = true;
    view.melee_voice[0] = int(VoiceEvent::AttackB);
    view.melee_voice_alternative[0] = 2;
    view.sound_effect_id[0] = 60;
    view.sound_effect_positional[0] = true;
    view.sound_effect_position[0] = {1.f,2.f,3.f};
    view.listener_position = {4.f,5.f,6.f};
    view.listener_forward = {0.f,0.f,-1.f};
    view.listener_valid = true;
    const CombatEventList events = combat_events_for_frame(source, view, 7, false);
    bool sawSwing = false, swingSpoke = false, sawVoice = false, sawSe = false;
    for (int i = 0; i < events.count; ++i) {
        const CombatEvent& e = events.events[i];
        if (e.kind == CombatEventKind::MeleeSwing && e.fighter == 0) {
            sawSwing = true;
            swingSpoke = resolve_combat_event(e).has_voice;
        }
        if (e.kind == CombatEventKind::MeleeVoice && e.fighter == 0) {
            sawVoice = true;
            const CombatCue cue = resolve_combat_event(e);
            CHECK(cue.has_voice && cue.voice == VoiceEvent::AttackB);
            CHECK(e.voice_alternative == 2);
        }
        if (e.kind == CombatEventKind::SoundEffect && e.fighter == 0) {
            sawSe = true;
            const CombatCue cue = resolve_combat_event(e);
            CHECK(cue.has_se() && cue.se_id == 60);
            CHECK(cue.se_positional && cue.se_position.x == 1.f && cue.se_position.y == 2.f &&
                  cue.se_position.z == 3.f);
            CHECK(cue.se_listener_valid && cue.se_listener_position.x == 4.f &&
                  cue.se_listener_position.y == 5.f && cue.se_listener_position.z == 6.f);
            CHECK(cue.se_listener_forward.x == 0.f && cue.se_listener_forward.y == 0.f &&
                  cue.se_listener_forward.z == -1.f);
            CHECK(!cue.has_voice);
        }
    }
    CHECK(sawSwing && sawVoice && sawSe);
    CHECK(swingSpoke);  // no audited flag on this frame: the vocabulary fallback stands

    // With the row's cue policy recovered the swing must go silent, and the body's own
    // cue is the only voice that frame.
    CombatFrameView audited = view;
    audited.melee_voice_audited[0] = true;
    const CombatEventList auditedEvents = combat_events_for_frame(source, audited, 8, false);
    bool auditedSwingSpoke = false, auditedVoice = false;
    for (int i = 0; i < auditedEvents.count; ++i) {
        const CombatEvent& e = auditedEvents.events[i];
        if (e.kind == CombatEventKind::MeleeSwing && e.fighter == 0) {
            CHECK(e.source_voice_audited);
            auditedSwingSpoke = resolve_combat_event(e).has_voice;
        }
        if (e.kind == CombatEventKind::MeleeVoice && e.fighter == 0) auditedVoice = true;
    }
    CHECK(!auditedSwingSpoke);
    CHECK(auditedVoice);

    // A silent frame emits nothing for the fighter.
    CombatFrameView empty;
    CHECK(combat_events_for_frame(source, empty, 9, false).count == 0);
    return true;
}

int main() {
    // Spatial-SE adapter: source and listener positions are in world units; the original
    // sets distanceFactor .01, listener rolloff .0002 and buffer min distance 3. DirectSound
    // defines inverse-distance rolloff beyond minimum, so this pins unity at min, half at
    // double that distance, and equal-power pan at the listener's left/right.
    {
        SpatialPlayRequest req;
        req.listener = {};
        req.listenerForward = {0.f,0.f,1.f};
        req.minDistance = 3.f;
        req.rolloffFactor = 1.f; // one for test math; the original stage uses .0005
        req.source = {0.f,0.f,-3.f};
        SpatialMix atMin = spatial_mix(req);
        CHECK(atMin.left > .70f && atMin.left < .72f &&
              atMin.right > .70f && atMin.right < .72f);
        CHECK(std::abs(atMin.left*atMin.left + atMin.right*atMin.right - 1.f) < .001f);
        req.source = {0.f,0.f,-6.f};
        SpatialMix twice = spatial_mix(req);
        CHECK(std::abs(twice.left*twice.left + twice.right*twice.right - .25f) < .001f);
        req.source = {-3.f,0.f,0.f};
        SpatialMix left = spatial_mix(req);
        req.source = {3.f,0.f,0.f};
        SpatialMix right = spatial_mix(req);
        CHECK(left.left > left.right);
        CHECK(right.right > right.left);
        std::vector<int16_t> input{16000,16000};
        std::vector<int16_t> output;
        spatialize_s16(input.data(),1,left,output);
        CHECK(output.size()==2 && output[0] > output[1]);
    }

    // The rest of the file pins cue dispatch and the SFX bus.
    CHECK(testFrameEvents());
    auto renaVoice = ev(CombatEventKind::ShotFired, 0, -1, 77);
    renaVoice.voice_override = int(VoiceEvent::ShotA);
    CHECK(resolve_combat_event(renaVoice).voice == VoiceEvent::ShotA);
    renaVoice.voice_override = int(VoiceEvent::ShotFinal);
    CHECK(resolve_combat_event(renaVoice).voice == VoiceEvent::ShotFinal);
    renaVoice.voice_override = int(VoiceEvent::SpecialA);
    renaVoice.voice_alternative = 2;
    Recorder renaSink;
    CombatAudio renaAudio(renaSink);
    renaAudio.set_fighter_voice(0, "data/voice/rena", false);
    renaAudio.set_voice_alternatives(0, VoiceEvent::SpecialA, 3);
    renaAudio.dispatch(renaVoice);
    CHECK(renaSink.played.size() == 1);
    CHECK(renaSink.played[0].stem == voice_asset_stem("data/voice/rena", VoiceEvent::SpecialA, false, 2));
    // --- the recovered vocabulary ------------------------------------------
    CHECK(kVoiceEventCount == 40);
    CHECK(std::string(voice_event_name(VoiceEvent::AddAttack)) == "addattack");
    CHECK(std::string(voice_event_name(VoiceEvent::AttackKO)) == "attackKO");
    CHECK(std::string(voice_event_name(VoiceEvent::Revival)) == "revival");
    CHECK(std::string(voice_event_name(VoiceEvent::SpecialC)) == "specialC");
    // FUN_00431e70:72: exactly the four events with a _B directory.
    CHECK(voice_event_b_dir(VoiceEvent::AttackKO));
    CHECK(voice_event_b_dir(VoiceEvent::BattleStart));
    CHECK(voice_event_b_dir(VoiceEvent::DamageKO));
    CHECK(voice_event_b_dir(VoiceEvent::Revival));
    CHECK(!voice_event_b_dir(VoiceEvent::Damage));
    CHECK(!voice_event_b_dir(VoiceEvent::AttackA));
    // The stem follows FUN_00431e70's own format, including the _B directory.
    CHECK(voice_asset_stem("data/voice/rena", VoiceEvent::AttackA, false, 2) ==
          "data/voice/rena/attackA/002");
    CHECK(voice_asset_stem("data/voice/rena", VoiceEvent::AttackKO, true, 1) ==
          "data/voice/rena/attackKO_B/001");
    // The _B character directory is the caller's own dir; only the event dir flips here.
    CHECK(voice_asset_stem("data/voice/renaB", VoiceEvent::Damage, true, 0) ==
          "data/voice/renaB/damage/000");
    CHECK(voice_asset_stem("", VoiceEvent::Damage, false, 0).empty());

    // --- event -> cue resolution -------------------------------------------
    CHECK(resolve_combat_event(ev(CombatEventKind::MeleeSwing, 0, -1, 10, 0)).voice ==
          VoiceEvent::AttackA);
    CHECK(resolve_combat_event(ev(CombatEventKind::MeleeSwing, 0, -1, 10, 1)).voice ==
          VoiceEvent::AttackB);
    CHECK(resolve_combat_event(ev(CombatEventKind::MeleeSwing, 0, -1, 10, 2)).voice ==
          VoiceEvent::AttackC);
    CHECK(resolve_combat_event(ev(CombatEventKind::ShotFired, 1, -1, 10)).voice ==
          VoiceEvent::Fire);
    CombatEvent auditedSilentShot = ev(CombatEventKind::ShotFired, 1, -1, 11);
    auditedSilentShot.source_voice_audited = true;
    CHECK(!resolve_combat_event(auditedSilentShot).has_voice);
    auditedSilentShot.voice_override = int(VoiceEvent::ShotC);
    CHECK(resolve_combat_event(auditedSilentShot).has_voice);
    CHECK(resolve_combat_event(auditedSilentShot).voice == VoiceEvent::ShotC);
    CHECK(resolve_combat_event(ev(CombatEventKind::Hit, 2, 0, 10)).voice == VoiceEvent::Damage);
    // The melee body's own voice cue: the id IS the vocabulary index, and a row whose cue
    // policy is recovered silences the swing fallback (MeleeSwing + audited -> no voice).
    CombatEvent bodyVoice = ev(CombatEventKind::MeleeVoice, 0, -1, 12);
    bodyVoice.voice_override = int(VoiceEvent::AttackB);
    CHECK(resolve_combat_event(bodyVoice).has_voice);
    CHECK(resolve_combat_event(bodyVoice).voice == VoiceEvent::AttackB);
    bodyVoice.voice_override = int(VoiceEvent::SpecialA);
    CHECK(resolve_combat_event(bodyVoice).voice == VoiceEvent::SpecialA);
    bodyVoice.voice_override = -1;
    CHECK(!resolve_combat_event(bodyVoice).has_voice);
    CombatEvent auditedSwing = ev(CombatEventKind::MeleeSwing, 0, -1, 12, 0);
    auditedSwing.source_voice_audited = true;
    CHECK(!resolve_combat_event(auditedSwing).has_voice);
    // FUN_0042c8b0/0042c880 request a data/se id — not a voice and not an effect card.
    CombatEvent bodySe = ev(CombatEventKind::SoundEffect, 0, -1, 12);
    bodySe.se_override = 60;
    const CombatCue seCue = resolve_combat_event(bodySe);
    CHECK(seCue.has_se() && seCue.se_id == 60);
    CHECK(!seCue.has_voice);
    CHECK(resolve_combat_event(ev(CombatEventKind::SoundEffect, 0, -1, 12)).se_id == -1);
    CHECK(resolve_combat_event(ev(CombatEventKind::Blocked, 2, 0, 10)).voice ==
          VoiceEvent::Guarded);
    CHECK(resolve_combat_event(ev(CombatEventKind::GuardStart, 2, -1, 10)).voice ==
          VoiceEvent::Guard);
    CHECK(resolve_combat_event(ev(CombatEventKind::Respawn, 3, -1, 10)).voice ==
          VoiceEvent::Revival);
    CHECK(resolve_combat_event(ev(CombatEventKind::MatchStart, 3, -1, 0)).voice ==
          VoiceEvent::BattleStart);
    // HyperActivate resolves per mode (issue #71): only the Oyashiro arm
    // carries audio — the handler's TagBack line plus SE 7. Other modes (and
    // an unknown mode) stay silent rather than borrowing the oyashiro line.
    const CombatCue hyper_oya =
        resolve_combat_event(ev(CombatEventKind::HyperActivate, 1, -1, 10, 0, false, 1));
    CHECK(hyper_oya.voice == VoiceEvent::TagBack && hyper_oya.se_id == 7);
    CHECK(!resolve_combat_event(ev(CombatEventKind::HyperActivate, 1, -1, 10, 0, false, 0))
               .has_voice);
    CHECK(!resolve_combat_event(ev(CombatEventKind::HyperActivate, 0, -1, 10)).has_se());
    // The KO pair reads the blow's source, and both carry the recovered SE 9.
    const CombatCue ko_melee = resolve_combat_event(ev(CombatEventKind::Ko, 2, 0, 10));
    CHECK(ko_melee.voice == VoiceEvent::AttackKO && ko_melee.se_id == 9);
    const CombatCue ko_shot = resolve_combat_event(ev(CombatEventKind::Ko, 2, 0, 10, 0, true));
    CHECK(ko_shot.voice == VoiceEvent::DamageKO && ko_shot.se_id == 9);
    // Overkill is the recovered SE 10 (a hit on an already-down body).
    const CombatCue over = resolve_combat_event(ev(CombatEventKind::Overkill, 2, 0, 10));
    CHECK(over.voice == VoiceEvent::DamageDown && over.se_id == 10);
    // Nothing else claims an SE id: the swing/fire/block/respawn ids are NOT recovered, so
    // they must not be invented here.
    CHECK(!resolve_combat_event(ev(CombatEventKind::MeleeSwing, 0, -1, 10)).has_se());
    CHECK(!resolve_combat_event(ev(CombatEventKind::ShotFired, 0, -1, 10)).has_se());
    CHECK(!resolve_combat_event(ev(CombatEventKind::Blocked, 0, 1, 10)).has_se());
    CHECK(!resolve_combat_event(ev(CombatEventKind::Respawn, 0, -1, 10)).has_se());
    CHECK(!resolve_combat_event(ev(CombatEventKind::HyperActivate, 0, -1, 10)).has_se());

    // --- identity ----------------------------------------------------------
    // Same tick, same kind, same fighter, same seq -> the same id (a replayed frame).
    CHECK(ev(CombatEventKind::Hit, 1, 0, 42).id() == ev(CombatEventKind::Hit, 1, 0, 42).id());
    // A different tick, kind, fighter or sequence is a different event.
    CHECK(ev(CombatEventKind::Hit, 1, 0, 42).id() != ev(CombatEventKind::Hit, 1, 0, 43).id());
    CHECK(ev(CombatEventKind::Hit, 1, 0, 42).id() != ev(CombatEventKind::Ko, 1, 0, 42).id());
    CHECK(ev(CombatEventKind::Hit, 1, 0, 42).id() != ev(CombatEventKind::Hit, 2, 0, 42).id());
    CHECK(ev(CombatEventKind::Hit, 1, 0, 42, 0).id() != ev(CombatEventKind::Hit, 1, 0, 42, 1).id());
    // A 4-fighter tick with one event of every kind and fighter is 32 distinct ids.
    {
        std::vector<uint64_t> ids;
        for (int f = 0; f < 4; ++f)
            for (int k = 0; k < kCombatEventKindCount; ++k)
                ids.push_back(ev((CombatEventKind)k, f, -1, 100).id());
        for (size_t i = 0; i < ids.size(); ++i)
            for (size_t j = i + 1; j < ids.size(); ++j) CHECK(ids[i] != ids[j]);
    }

    // --- dispatch, de-duplication, per-fighter channels --------------------
    {
        Recorder rec;
        CombatAudio audio(rec);
        audio.begin_match(4);
        for (int f = 0; f < 4; ++f) {
            audio.set_fighter_voice(f, std::string("data/voice/fighter") + std::to_string(f), false);
            for (int e = 0; e < kVoiceEventCount; ++e)
                audio.set_voice_alternatives(f, (VoiceEvent)e, 3);  // three shipped takes
        }
        // Two fighters swing in the SAME tick: independent voices, independent channels.
        audio.dispatch(ev(CombatEventKind::MeleeSwing, 0, -1, 100));
        audio.dispatch(ev(CombatEventKind::MeleeSwing, 2, -1, 100));
        CHECK(rec.played.size() == 2);
        CHECK(rec.played[0].bus == SfxBus::Voice && rec.played[1].bus == SfxBus::Voice);
        CHECK(rec.played[0].channel == voice_channel_for(0));
        CHECK(rec.played[1].channel == voice_channel_for(2));
        CHECK(rec.played[0].channel != rec.played[1].channel);
        CHECK(rec.played[0].stem.find("data/voice/fighter0/attackA/") == 0);
        CHECK(rec.played[1].stem.find("data/voice/fighter2/attackA/") == 0);
        CHECK(audio.claimed_voice(0) == voice_channel_for(0));
        CHECK(audio.claimed_voice(2) == voice_channel_for(2));
        CHECK(audio.claimed_voice(1) == -1);
        CHECK(audio.claimed_channels() == 2);

        // The SAME event twice: the second is a duplicate and plays nothing.
        const size_t before = rec.played.size();
        audio.dispatch(ev(CombatEventKind::MeleeSwing, 0, -1, 100));
        CHECK(rec.played.size() == before);
        CHECK(audio.stats().duplicates == 1);
        // `dispatched` counts ACCEPTED events; the duplicate is only counted as such.
        CHECK(audio.stats().dispatched[static_cast<int>(CombatEventKind::MeleeSwing)] == 2);

        // One fighter's second line stops its own previous channel first, so one fighter
        // never stacks while the other fighter's channel is untouched.
        audio.dispatch(ev(CombatEventKind::MeleeSwing, 0, -1, 101, 1));
        CHECK(rec.played.size() == before + 1);
        CHECK(!rec.stops.empty() && rec.stops.back() == voice_channel_for(0));
        CHECK(audio.claimed_voice(2) == voice_channel_for(2));

        // A KO plays the victim's voice AND the recovered SE 9 on the SFX bus.
        audio.dispatch(ev(CombatEventKind::Hit, 2, 0, 102));
        const size_t after_hit = rec.played.size();
        audio.dispatch(ev(CombatEventKind::Ko, 2, 0, 103));
        CHECK(rec.played.size() == after_hit + 2);
        CHECK(rec.played[after_hit].bus == SfxBus::Voice);
        CHECK(rec.played[after_hit + 1].bus == SfxBus::Sfx);
        CHECK(rec.played[after_hit + 1].stem == "data/se/009");
        CHECK(audio.last_se_id() == 9);
        // The victim's KO line is the victim's own channel, not the attacker's.
        CHECK(rec.played[after_hit].channel == voice_channel_for(2));

        // Rena body SEs using FUN_0042c8b0 route through spatial playback with the
        // frame's source and listener; non-positional 0042c880 cues stay on the plain SFX path.
        CombatEvent positionalSe = ev(CombatEventKind::SoundEffect, 0, -1, 105);
        positionalSe.se_override = 61;
        positionalSe.se_positional = true;
        positionalSe.se_position = {1.f,2.f,3.f};
        positionalSe.se_listener_position = {4.f,5.f,6.f};
        positionalSe.se_listener_forward = {0.f,0.f,-1.f};
        positionalSe.se_listener_valid = true;
        audio.dispatch(positionalSe);
        CHECK(rec.spatial.size() == 1);
        CHECK(rec.spatial[0].source.x == 1.f && rec.spatial[0].source.y == 2.f &&
              rec.spatial[0].source.z == 3.f);
        CHECK(rec.spatial[0].listener.x == 4.f && rec.spatial[0].listener.y == 5.f &&
              rec.spatial[0].listener.z == 6.f);
        CHECK(rec.spatial[0].listenerForward.x == 0.f &&
              rec.spatial[0].listenerForward.y == 0.f &&
              rec.spatial[0].listenerForward.z == -1.f);
        CombatEvent nonpositionalSe = ev(CombatEventKind::SoundEffect, 0, -1, 106);
        nonpositionalSe.se_override = 62;
        audio.dispatch(nonpositionalSe);
        CHECK(rec.spatial.size() == 1);

        // Overkill uses SE 10 and the downed line.
        audio.dispatch(ev(CombatEventKind::Overkill, 1, 0, 104));
        CHECK(rec.played.back().stem == "data/se/010");
        CHECK(rec.played[rec.played.size() - 2].stem.find("data/voice/fighter1/damagedown/") == 0);

        // An event whose alternatives were never registered stays silent (no invented file).
        Recorder quiet;
        CombatAudio silent(quiet);
        silent.begin_match(2);
        silent.set_fighter_voice(0, "data/voice/rena", false);
        silent.dispatch(ev(CombatEventKind::MeleeSwing, 0, -1, 10));
        CHECK(quiet.played.empty());
        CHECK(silent.stats().voice_missing == 1);
        // A fighter with no voice directory at all is silent too.
        silent.dispatch(ev(CombatEventKind::MeleeSwing, 1, -1, 10));
        CHECK(quiet.played.empty());
    }

    // --- suspend / resume (#15's pause) ------------------------------------
    {
        Recorder rec;
        CombatAudio audio(rec);
        audio.begin_match(2);
        audio.set_fighter_voice(0, "data/voice/rena", false);
        audio.set_voice_alternatives(0, VoiceEvent::AttackA, 2);
        audio.set_voice_alternatives(0, VoiceEvent::DamageKO, 2);
        audio.dispatch(ev(CombatEventKind::MeleeSwing, 0, -1, 10));
        CHECK(audio.claimed_voice(0) == voice_channel_for(0));
        // Suspending stops the claimed voice so a pause mid-swing leaves nothing playing.
        audio.suspend();
        CHECK(audio.suspended());
        CHECK(audio.claimed_voice(0) == -1);
        CHECK(!rec.busy[static_cast<size_t>(voice_channel_for(0))]);
        const size_t before = rec.played.size();
        audio.dispatch(ev(CombatEventKind::Ko, 0, 1, 11));
        CHECK(rec.played.size() == before);          // nothing plays while paused
        CHECK(audio.stats().suspended_drops == 1);
        // ...and the dropped event is remembered, so resuming cannot replay it late.
        audio.resume();
        audio.dispatch(ev(CombatEventKind::Ko, 0, 1, 11));
        CHECK(rec.played.size() == before);
        CHECK(audio.stats().duplicates == 1);
        // A new tick after resume plays normally.
        audio.dispatch(ev(CombatEventKind::MeleeSwing, 0, -1, 12));
        CHECK(rec.played.size() == before + 1);
    }

    // --- repeated matches: no channel leak ---------------------------------
    {
        Recorder rec;
        CombatAudio audio(rec);
        for (int match = 0; match < 5; ++match) {
            audio.begin_match(4);
            for (int f = 0; f < 4; ++f) {
                audio.set_fighter_voice(f, "data/voice/rena", false);
                audio.set_voice_alternatives(f, VoiceEvent::AttackA, 2);
                audio.set_voice_alternatives(f, VoiceEvent::DamageKO, 2);
                audio.set_voice_alternatives(f, VoiceEvent::BattleStart, 2);
                audio.dispatch(ev(CombatEventKind::MatchStart, f, -1, (uint32_t)(match * 100)));
                audio.dispatch(ev(CombatEventKind::MeleeSwing, f, -1, (uint32_t)(match * 100 + 1)));
                audio.dispatch(ev(CombatEventKind::Ko, f, (f + 1) % 4, (uint32_t)(match * 100 + 2)));
            }
            CHECK(audio.claimed_channels() == 4);
            const size_t bus_stops_before = rec.bus_stops.size();
            audio.end_match();
            CHECK(audio.claimed_channels() == 0);
            CHECK(rec.busy_count() == 0);  // every claimed channel was released
            // ...and the match's one-shots are cut with it, never left ringing (#15's rule 6).
            CHECK(rec.bus_stops.size() == bus_stops_before + 1);
            CHECK(rec.bus_stops.back() == SfxBus::Sfx);
        }
        // end_match also clears the duplicate history, so the next match's first event (same
        // tick numbers on a fresh match) is not mistaken for a replay.
        Recorder rec2;
        CombatAudio again(rec2);
        again.begin_match(1);
        again.set_fighter_voice(0, "data/voice/rena", false);
        again.set_voice_alternatives(0, VoiceEvent::BattleStart, 1);
        again.dispatch(ev(CombatEventKind::MatchStart, 0, -1, 0));
        again.end_match();
        again.begin_match(1);
        again.set_fighter_voice(0, "data/voice/rena", false);
        again.set_voice_alternatives(0, VoiceEvent::BattleStart, 1);
        again.dispatch(ev(CombatEventKind::MatchStart, 0, -1, 0));
        CHECK(rec2.played.size() == 2);
    }

    // --- backpressure: a full bus is reported, never stolen ----------------
    {
        Recorder rec;
        rec.accept = false;  // the sink refuses everything
        CombatAudio audio(rec);
        audio.begin_match(1);
        audio.set_fighter_voice(0, "data/voice/rena", false);
        audio.set_voice_alternatives(0, VoiceEvent::AttackA, 1);
        audio.set_voice_alternatives(0, VoiceEvent::DamageKO, 1);
        audio.dispatch(ev(CombatEventKind::MeleeSwing, 0, -1, 1));
        CHECK(audio.stats().voice_missing == 1);
        CHECK(audio.claimed_voice(0) == -1);
        audio.dispatch(ev(CombatEventKind::Ko, 0, 1, 2));
        CHECK(audio.stats().se_missing == 1);
    }

    // --- volume changes reach playback that is already running ---------------
    // Issue #16's fourth criterion. The engine walks every BUSY slot in set_volumes and
    // applies the new gain to its stream (audio_engine.cpp), so a slider moved mid-battle
    // changes what is already playing. This opens the real backend on the dummy driver: no
    // hardware, but the same code path, and it skips cleanly when no device can be opened.
    {
        setenv("SDL_AUDIODRIVER", "dummy", 1);  // no hardware: same backend, dummy device
        Sdl3Engine engine;
        if (engine.open(Spec{})) {
            std::vector<int16_t> tone(44100 * 2, 4000);  // one second of a quiet square
            const SfxHandle h = engine.load_pcm_s16(tone.data(), 44100);
            CHECK(h >= 0);
            Volumes v;
            v.master = 100;
            v.voice = 100;
            engine.set_volumes(v);
            const int ch = engine.play(h, SfxBus::Voice);
            CHECK(ch >= 0);
            SpatialPlayRequest spatial;
            spatial.source = {-3.f,0.f,0.f};
            spatial.listener = {};
            spatial.listenerForward = {0.f,0.f,1.f};
            spatial.rolloffFactor = 1.f;
            const int spatialCh = engine.play_spatial(h, spatial);
            CHECK(spatialCh >= kSfxFirst && spatialCh <= kSfxLast);
            CHECK(engine.channel_busy(spatialCh) && engine.sfx_queued_frames(spatialCh) > 0);
            CHECK(engine.channel_busy(ch));
            // The slider moves while the cue is still queued: the gain must follow it.
            v.voice = 25;
            engine.set_volumes(v);
            CHECK(engine.bus_gain_applied(SfxBus::Voice) > 0.24f &&
                  engine.bus_gain_applied(SfxBus::Voice) < 0.26f);
            CHECK(engine.channel_busy(ch));            // still the same, still playing
            CHECK(engine.sfx_queued_frames(ch) > 0);
            // Master at 0 silences the bus without losing the per-bus setting.
            v.master = 0;
            engine.set_volumes(v);
            CHECK(engine.bus_gain_applied(SfxBus::Voice) == 0.0f);
            CHECK(engine.volumes().voice == 25);
            // A verification mute survives volume changes without overwriting settings
            // or disabling the queues that the audio policy tests exercise.
            set_output_muted(true);
            v.master = 100;
            engine.set_volumes(v);
            CHECK(engine.bus_gain_applied(SfxBus::Voice) == 0.0f);
            CHECK(engine.bus_gain_applied(SfxBus::Ui) == 0.0f);
            CHECK(engine.bus_gain_applied(SfxBus::Sfx) == 0.0f);
            CHECK(engine.volumes().master == 100);
            CHECK(engine.channel_busy(ch));
            set_output_muted(false);
            engine.set_volumes(v);
            CHECK(engine.bus_gain_applied(SfxBus::Voice) > 0.24f);
            engine.stop_bus(SfxBus::Voice);
            CHECK(!engine.channel_busy(ch));
            engine.stop(spatialCh);
            CHECK(!engine.channel_busy(spatialCh));
            engine.close();
        } else {
            std::puts("combat_audio_test: no audio device (dummy driver refused), volume "
                      "check skipped");
        }
    }

    std::puts("combat_audio_test: event identity, resolution and channel bookkeeping ok");
    // Direct requests from a backend that resolves its own cues: the given file plays on the
    // fighter's own voice channel and a repeat replaces the line instead of stacking.
    {
        Recorder sink;
        CombatAudio audio(sink);
        audio.begin_match(4);
        audio.play_voice_direct(1, "data/voice/mion/attackA/000.wav");
        audio.play_voice_direct(1, "data/voice/mion/attackB/001.wav");
        audio.play_voice_direct(7, "data/voice/mion/attackA/000.wav");
        CHECK(sink.played.size() == 2);
        CHECK(sink.played[1].stem == "data/voice/mion/attackB/001");
        CHECK(sink.played[0].channel == sink.played[1].channel);
        audio.play_se_direct(12, false, {}, {}, {0.f, 0.f, 1.f}, false);
        CHECK(sink.played.size() == 3);
        CHECK(sink.played[2].bus == SfxBus::Sfx);
        audio.play_system_se_direct(7);
        CHECK(sink.played.size() == 4);
        CHECK(sink.played[3].stem == "data/sysse/007");
    }
    return 0;
}
