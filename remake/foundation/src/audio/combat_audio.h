// The core's combat audio requests, played through the host's engine: one voice channel per
// fighter, the SE bus for one-shots, and the stage's spatial parameters.
//  * The gameplay SE bank is data/se/%03d with 32 slots per play (FUN_0064ade0), played through
//    FUN_0065a220; the system bank is data/sysse/%03d (FUN_00647e00).
//  * Independent per-player voice bookkeeping is the original's own design: FUN_0064ada0 selects
//    each player's audio object and FUN_0064ab30 wires its volumes into it.
#pragma once

#include <array>
#include <string>

#include "audio/audio_engine.h"  // SfxBus + the channel reservation constants

namespace fnd::audio {

// The host adapts its loaded-sample cache to this. `play` returns the channel it played on
// (or -1 when the sample is missing or the bus is full, which is backpressure, not an error).
class CombatAudioSink {
public:
    struct SpatialRequest {
        AudioPoint3 source{};
        AudioPoint3 listener{};
        AudioPoint3 listenerForward{0.f, 0.f, 1.f};
        float rolloffFactor = 0.0005f;  // FUN_00648ad0/006492f0 battle-stage SetRolloffFactor
        float minDistance = 3.f;        // FUN_006676d0 SetMinDistance, DS3D default init
    };
    virtual ~CombatAudioSink() = default;
    virtual int play(const std::string& asset_stem, SfxBus bus, int channel) = 0;
    virtual int play_spatial(const std::string& asset_stem, int channel, const SpatialRequest& request) = 0;
    virtual void stop(int channel) = 0;
    virtual void stop_bus(SfxBus bus) = 0;
};

// One voice channel per fighter, so two fighters never clobber each other's line.
inline int voice_channel_for(int fighter) { return kVoiceFirst + (fighter < 0 ? 0 : fighter % 4); }

class CombatAudio {
public:
    explicit CombatAudio(CombatAudioSink& sink) : sink_(sink) {}

    void begin_match();
    void play_se(int id, bool positional, const AudioPoint3& position, const AudioPoint3& listener,
                 const AudioPoint3& forward, bool listenerValid);
    // data/sysse's separate bank, always nonpositional.
    void play_system_se(int id);
    void play_voice(int fighter, const std::string& path, bool positional = false, const AudioPoint3& position = {},
                    const AudioPoint3& listener = {}, const AudioPoint3& forward = {}, bool listenerValid = false);

    // While suspended nothing plays and the voice channels are free. BGM is the pause's own.
    void suspend();
    void resume() { suspended_ = false; }
    bool suspended() const { return suspended_; }

    // Stops the match's voices and one-shots, so nothing rings into the next screen.
    void end_match();

    struct Stats {
        int suspended_drops = 0;
        int voice_plays = 0;
        int voice_missing = 0;
        int se_plays = 0;
        int se_missing = 0;   // the sink refused (no sample / bus full)
    };
    const Stats& stats() const { return stats_; }
    int claimed_channels() const;

private:
    void stop_voices();

    CombatAudioSink& sink_;
    std::array<int, 4> voiceChannel_{{-1, -1, -1, -1}};
    bool suspended_ = false;
    Stats stats_{};
};

}  // namespace fnd::audio
