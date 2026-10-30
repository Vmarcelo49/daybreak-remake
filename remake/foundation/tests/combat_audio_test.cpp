// The core's audio requests through fnd::audio::CombatAudio: spatial law, voice channels,
// suspend and cleanup. Device-free: the sink records calls.
#include <cmath>
#include <cstdio>
#include <string>
#include <vector>

#include "audio/combat_audio.h"

using namespace fnd::audio;

#define CHECK(condition) do { if (!(condition)) { std::fprintf(stderr, "line %d: %s\n", __LINE__, #condition); return 1; } } while (0)

namespace {

class Recorder : public CombatAudioSink {
public:
    int play(const std::string& stem, SfxBus bus, int channel) override {
        plays.push_back(stem);
        buses.push_back(bus);
        return channel >= 0 ? channel : 16;
    }
    int play_spatial(const std::string& stem, int channel, const SpatialRequest& request) override {
        spatialStems.push_back(stem);
        spatial.push_back(request);
        return channel >= 0 ? channel : 16;
    }
    void stop(int channel) override { stopped.push_back(channel); }
    void stop_bus(SfxBus bus) override { stoppedBuses.push_back(bus); }

    std::vector<std::string> plays, spatialStems;
    std::vector<SfxBus> buses, stoppedBuses;
    std::vector<SpatialRequest> spatial;
    std::vector<int> stopped;
};

}  // namespace

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
        // The battle stage's own values: the distance must be audible in world units.
        req.rolloffFactor = .0005f;
        const auto gain = [&](float distance) {
            req.source = {0.f,0.f,-distance};
            const SpatialMix mix = spatial_mix(req);
            return std::sqrt(mix.left*mix.left + mix.right*mix.right);
        };
        CHECK(std::abs(gain(1000.f) - .857f) < .002f);
        CHECK(std::abs(gain(6003.f) - .5f) < .002f);
        std::vector<int16_t> input{16000,16000};
        std::vector<int16_t> output;
        spatialize_s16(input.data(),1,left,output);
        CHECK(output.size()==2 && output[0] > output[1]);
    }

    {
        Recorder sink;
        CombatAudio audio(sink);
        audio.begin_match();
        // A positional voice keeps its fighter's channel but takes the spatial path.
        audio.play_voice(0, "data/voice/rena/attackA/000.wav", true, {0.f,0.f,1000.f}, {}, {0.f,0.f,1.f}, true);
        CHECK(sink.spatial.size() == 1 && sink.spatial[0].source.z == 1000.f);
        CHECK(sink.spatialStems[0] == "data/voice/rena/attackA/000");
        // A new line on one fighter replaces that fighter's line and no other.
        audio.play_voice(1, "data/voice/mion/shotA/000.wav");
        audio.play_voice(0, "data/voice/rena/battlestart/000.wav");
        CHECK(sink.spatial.size() == 1 && sink.plays.size() == 2);
        CHECK(sink.stopped == std::vector<int>{voice_channel_for(0)});
        CHECK(audio.claimed_channels() == 2);
        audio.play_se(5, true, {1.f,0.f,0.f}, {}, {0.f,0.f,1.f}, true);
        CHECK(sink.spatialStems.back() == "data/se/005");
        audio.play_se(6, true, {1.f,0.f,0.f}, {}, {0.f,0.f,1.f}, false);
        CHECK(sink.plays.back() == "data/se/006");
        audio.play_system_se(7);
        CHECK(sink.plays.back() == "data/sysse/007");
        // Suspending frees the voices and drops requests until resume.
        audio.suspend();
        CHECK(audio.claimed_channels() == 0);
        const size_t before = sink.plays.size();
        audio.play_system_se(7);
        audio.play_voice(0, "data/voice/rena/damage/000.wav");
        CHECK(sink.plays.size() == before && audio.stats().suspended_drops == 2);
        audio.resume();
        audio.play_voice(0, "data/voice/rena/damage/000.wav");
        CHECK(audio.claimed_channels() == 1);
        // Leaving the match cuts both.
        audio.end_match();
        CHECK(audio.claimed_channels() == 0 && sink.stoppedBuses.back() == SfxBus::Sfx);
    }
    std::puts("combat_audio_test: spatial law, voice channels, suspend and cleanup ok");
    return 0;
}
