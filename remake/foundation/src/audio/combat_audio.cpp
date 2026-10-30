#include "audio/combat_audio.h"

#include <cstdio>

namespace fnd::audio {

namespace {

CombatAudioSink::SpatialRequest stage_spatial_request(const AudioPoint3& source, const AudioPoint3& listener,
                                                      const AudioPoint3& forward) {
    CombatAudioSink::SpatialRequest request;
    request.source = source;
    request.listener = listener;
    request.listenerForward = forward;
    return request;
}

std::string numbered_stem(const char* dir, int id) {
    char number[16];
    std::snprintf(number, sizeof(number), "%03d", id < 0 ? 0 : id);
    return std::string(dir) + "/" + number;
}

}  // namespace

void CombatAudio::begin_match() {
    end_match();
    stats_ = Stats{};
}

void CombatAudio::play_se(int id, bool positional, const AudioPoint3& position, const AudioPoint3& listener,
                          const AudioPoint3& forward, bool listenerValid) {
    if (suspended_) {
        ++stats_.suspended_drops;
        return;
    }
    // The channel is not claimed: an SE is one-shot and frees itself when it drains.
    const std::string stem = numbered_stem("data/se", id);
    const int played = positional && listenerValid
        ? sink_.play_spatial(stem, -1, stage_spatial_request(position, listener, forward))
        : sink_.play(stem, SfxBus::Sfx, -1);
    if (played < 0) ++stats_.se_missing;
    else ++stats_.se_plays;
}

void CombatAudio::play_system_se(int id) {
    if (suspended_) {
        ++stats_.suspended_drops;
        return;
    }
    if (sink_.play(numbered_stem("data/sysse", id), SfxBus::Sfx, -1) < 0) ++stats_.se_missing;
    else ++stats_.se_plays;
}

void CombatAudio::play_voice(int fighter, const std::string& path, bool positional, const AudioPoint3& position,
                             const AudioPoint3& listener, const AudioPoint3& forward, bool listenerValid) {
    if (fighter < 0 || fighter >= 4) return;
    if (suspended_) {
        ++stats_.suspended_drops;
        return;
    }
    int& claimed = voiceChannel_[static_cast<size_t>(fighter)];
    const int channel = voice_channel_for(fighter);
    if (claimed >= 0) sink_.stop(claimed);
    const size_t dot = path.find_last_of('.');
    const std::string stem = dot == std::string::npos ? path : path.substr(0, dot);
    claimed = positional && listenerValid
        ? sink_.play_spatial(stem, channel, stage_spatial_request(position, listener, forward))
        : sink_.play(stem, SfxBus::Voice, channel);
    if (claimed < 0) ++stats_.voice_missing;
    else ++stats_.voice_plays;
}

void CombatAudio::stop_voices() {
    for (int& channel : voiceChannel_) {
        if (channel >= 0) sink_.stop(channel);
        channel = -1;
    }
}

void CombatAudio::suspend() {
    if (suspended_) return;
    suspended_ = true;
    stop_voices();
}

void CombatAudio::end_match() {
    sink_.stop_bus(SfxBus::Sfx);
    stop_voices();
    suspended_ = false;
}

int CombatAudio::claimed_channels() const {
    int n = 0;
    for (int channel : voiceChannel_)
        if (channel >= 0) ++n;
    return n;
}

}  // namespace fnd::audio
