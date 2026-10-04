// SDL3 streaming backend for fnd::audio::Engine (Track M).
//
// Why one device + 33 bound streams: SDL3 binds any number of streams to a
// playback device and mixes them, which is exactly the remake's 32 SFX
// channels + 1 music stream without SDL_mixer's file-path/temp-file path.
// Sources convert once to 44100 stereo S16 on load (audio_engine.h), so every
// stream's src/dst spec is the mix spec and SDL only resamples when the
// hardware device itself disagrees.

#include "audio/audio_engine.h"

#include <SDL3/SDL.h>

#include "audio/audio_sdl3.h"

// Single-header OGG Vorbis decoder, public domain. The implementation lives
// in this TU only (STB_VORBIS_IMPLEMENTATION once); the header side stays in
// audio_engine.h's load_ogg.
#define STB_VORBIS_IMPLEMENTATION
#include "stb_vorbis.c"

namespace fnd::audio {

namespace {
constexpr int kMixFrameBytes = 2 * 2;  // S16 stereo: 2 channels x 2 bytes

float gain_for(SfxBus bus, const Volumes& v) {
    switch (bus) {
        case SfxBus::Ui: return bus_gain(v.sfx, v.master);  // no UI slider; SFX owns cues
        case SfxBus::Voice: return bus_gain(v.voice, v.master);
        case SfxBus::Sfx: return bus_gain(v.sfx, v.master);
    }
    return 1.0f;
}

SfxBus bus_of_channel(int ch) {
    if (ch == kUiChannel) return SfxBus::Ui;
    if (is_voice_channel(ch)) return SfxBus::Voice;
    return SfxBus::Sfx;
}
}  // namespace

struct Sdl3Engine::Impl {
    SDL_AudioDeviceID dev = 0;
    SDL_AudioStream* music = nullptr;
    SDL_AudioStream* slot[kMaxSfxChannels] = {};
    bool slot_busy[kMaxSfxChannels] = {};
    std::vector<std::vector<int16_t>> bank;
    std::vector<int> free_handles;
    float music_gain = 1.0f;
    float ui_gain = 1.0f, voice_gain = 1.0f, sfx_gain = 1.0f;
};

Sdl3Engine::Sdl3Engine(UnlockGate* gate)
    : impl_(new Impl), gate_(gate) {}

Sdl3Engine::~Sdl3Engine() { close(); }

bool Sdl3Engine::open(const Spec& spec) {
    if (is_open()) return true;
    if (!SDL_InitSubSystem(SDL_INIT_AUDIO)) return false;
    // The game spec is already the mix target (44100 stereo per MEDIA-INPUT
    // inventory); when hardware disagrees the bound streams resample, so the
    // request stays fixed instead of chasing the device.
    sdl3::DeviceSpec dev_spec = sdl3::to_device_spec(spec);
    SDL_AudioSpec want{SDL_AUDIO_S16, dev_spec.channels, static_cast<int>(dev_spec.sample_rate)};
    SDL_AudioSpec stream_spec{SDL_AUDIO_S16, 2, 44100};
    SDL_AudioDeviceID dev = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &want);
    if (!dev) {
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }
    SDL_AudioStream* music = SDL_CreateAudioStream(&stream_spec, &stream_spec);
    if (!music) {
        SDL_CloseAudioDevice(dev);
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
        return false;
    }
    Impl& im = *impl_;
    im.dev = dev;
    im.music = music;
    for (int i = 0; i < kMaxSfxChannels; ++i) {
        im.slot[i] = SDL_CreateAudioStream(&stream_spec, &stream_spec);
        if (!im.slot[i]) {
            close();
            return false;
        }
        im.slot_busy[i] = false;
    }
    // Bind music + all slots in one call so the device mixes them; a failed
    // bind leaves no half-wired device behind.
    std::vector<SDL_AudioStream*> all;
    all.reserve(kMaxSfxChannels + 1);
    all.push_back(im.music);
    for (auto* s : im.slot) all.push_back(s);
    if (!SDL_BindAudioStreams(im.dev, all.data(), static_cast<int>(all.size()))) {
        close();
        return false;
    }
    set_volumes(volumes_);  // apply cached sliders to the fresh streams
    SDL_ResumeAudioDevice(im.dev);
    return true;
}

void Sdl3Engine::close() {
    Impl& im = *impl_;
    if (im.music) {
        SDL_DestroyAudioStream(im.music);
        im.music = nullptr;
    }
    for (int i = 0; i < kMaxSfxChannels; ++i) {
        if (im.slot[i]) {
            SDL_DestroyAudioStream(im.slot[i]);
            im.slot[i] = nullptr;
        }
        im.slot_busy[i] = false;
    }
    if (im.dev) {
        SDL_CloseAudioDevice(im.dev);
        im.dev = 0;
        SDL_QuitSubSystem(SDL_INIT_AUDIO);
    }
}

bool Sdl3Engine::is_open() const { return impl_->dev != 0; }

size_t Sdl3Engine::push_music_s16(const int16_t* frames, size_t frame_count) {
    bool ready = !gate_ || gate_->ready();
    if (!sdl3::may_push(ready)) return 0;  // gated: drop, never queue
    if (!is_open() || !frames || frame_count == 0) return 0;
    if (!SDL_PutAudioStreamData(impl_->music, frames,
                                static_cast<int>(frame_count * 2 * sizeof(int16_t))))
        return 0;
    return frame_count;
}

void Sdl3Engine::set_volumes(const Volumes& v) {
    volumes_ = v;
    Impl& im = *impl_;
    im.music_gain = bus_gain(v.music, v.master);
    im.ui_gain = gain_for(SfxBus::Ui, v);
    im.voice_gain = gain_for(SfxBus::Voice, v);
    im.sfx_gain = gain_for(SfxBus::Sfx, v);
    if (!is_open()) return;  // cached above; applied on open()
    SDL_SetAudioStreamGain(im.music, im.music_gain);
    for (int i = 0; i < kMaxSfxChannels; ++i) {
        if (im.slot[i]) SDL_SetAudioStreamGain(im.slot[i], gain_for(bus_of_channel(i), v));
    }
}

SfxHandle Sdl3Engine::load_pcm_s16(const int16_t* stereo_frames, size_t frame_count) {
    if (!stereo_frames || frame_count == 0) return kInvalidSfx;
    Impl& im = *impl_;
    std::vector<int16_t> buf(stereo_frames, stereo_frames + frame_count * 2);
    if (!im.free_handles.empty()) {
        int h = im.free_handles.back();
        im.free_handles.pop_back();
        im.bank[static_cast<size_t>(h)] = std::move(buf);
        return h;
    }
    im.bank.push_back(std::move(buf));
    return static_cast<SfxHandle>(im.bank.size() - 1);
}

SfxHandle Sdl3Engine::load_wav(const uint8_t* bytes, size_t size) {
    std::vector<int16_t> pcm;
    if (!decode_wav_s16(bytes, size, pcm)) return kInvalidSfx;
    return load_pcm_s16(pcm.data(), pcm.size() / 2);
}

SfxHandle Sdl3Engine::load_cnv(const uint8_t* bytes, size_t size) {
    std::vector<int16_t> pcm;
    if (!decode_cnv_s16(bytes, size, pcm)) return kInvalidSfx;
    return load_pcm_s16(pcm.data(), pcm.size() / 2);
}

SfxHandle Sdl3Engine::load_ogg(const uint8_t* bytes, size_t size) {
    DecodedOgg decoded;
    if (!decode_ogg_s16(bytes, size, decoded)) return kInvalidSfx;
    return load_pcm_s16(decoded.stereo44100.data(), decoded.stereo44100.size() / 2);
}

bool decode_ogg_s16(const uint8_t* bytes, size_t size, DecodedOgg& out) {
    out = DecodedOgg{};
    if (!bytes || size == 0) return false;
    if (detect_format(bytes, size) != BlobFormat::Ogg) return false;
    int error = 0;
    stb_vorbis* vorbis = stb_vorbis_open_memory(bytes, (int)size, &error, nullptr);
    if (!vorbis) return false;
    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    out.srcRate = (uint32_t)info.sample_rate;
    out.srcChannels = info.channels;
    std::vector<int16_t> interleaved;
    interleaved.reserve(4096 * 2);
    for (;;) {
        int16_t chunk[4096 * 2];
        int n = stb_vorbis_get_samples_short_interleaved(vorbis, 2, chunk, 4096 * 2);
        if (n <= 0) break;
        interleaved.insert(interleaved.end(), chunk, chunk + (size_t)n * 2);
    }
    stb_vorbis_close(vorbis);
    if (interleaved.empty()) return false;
    const size_t frames = interleaved.size() / 2;
    if (info.channels == 2 && info.sample_rate == 44100) {
        out.stereo44100 = std::move(interleaved);
    } else {
        convert_to_mix_s16(reinterpret_cast<const uint8_t*>(interleaved.data()), frames,
                           info.channels, (uint32_t)info.sample_rate, 16,
                           out.stereo44100);
        if (out.stereo44100.empty()) return false;
    }
    out.ok = true;
    return true;
}

void Sdl3Engine::clear_music() {
    if (is_open()) SDL_ClearAudioStream(impl_->music);
}

void Sdl3Engine::clear_bank() {
    Impl& im = *impl_;
    im.bank.clear();
    im.free_handles.clear();
}

int Sdl3Engine::play(SfxHandle h, SfxBus bus, const PlayRequest& req) {
    bool ready = !gate_ || gate_->ready();
    if (!sdl3::may_push(ready)) return -1;  // gated: drop, never queue
    if (!is_open()) return -1;
    Impl& im = *impl_;
    if (h < 0 || static_cast<size_t>(h) >= im.bank.size() || im.bank[static_cast<size_t>(h)].empty())
        return -1;
    int ch = req.channel;
    if (ch < 0) {
        int first = 0, last = -1;
        if (!bus_range(bus, first, last)) return -1;
        ch = -1;
        for (int c = first; c <= last; ++c) {
            // Lazy reclaim: a slot whose stream drained is free without the
            // caller polling. Queued==0 right after put is impossible here
            // because put precedes any drain, so this cannot free a live play.
            if (im.slot_busy[c] && SDL_GetAudioStreamQueued(im.slot[c]) == 0)
                im.slot_busy[c] = false;
            if (!im.slot_busy[c]) {
                ch = c;
                break;
            }
        }
        if (ch < 0) return -1;  // bus full: backpressure, never steal
    } else {
        if (ch < 0 || ch >= kMaxSfxChannels || im.slot_busy[ch]) return -1;
    }
    const std::vector<int16_t>& buf = im.bank[static_cast<size_t>(h)];
    if (!SDL_PutAudioStreamData(im.slot[ch], buf.data(), static_cast<int>(buf.size() * sizeof(int16_t))))
        return -1;
    im.slot_busy[ch] = true;
    return ch;
}

void Sdl3Engine::stop(int channel) {
    if (channel < 0 || channel >= kMaxSfxChannels || !is_open()) return;
    SDL_ClearAudioStream(impl_->slot[channel]);
    impl_->slot_busy[channel] = false;
}

void Sdl3Engine::stop_all_sfx() {
    if (!is_open()) return;
    for (int i = 0; i < kMaxSfxChannels; ++i) stop(i);
}

bool Sdl3Engine::channel_busy(int channel) const {
    if (channel < 0 || channel >= kMaxSfxChannels || !is_open()) return false;
    const Impl& im = *impl_;
    if (!im.slot_busy[channel]) return false;
    // Same lazy reclaim as play(): drained means free.
    if (SDL_GetAudioStreamQueued(im.slot[channel]) == 0) {
        const_cast<Impl&>(im).slot_busy[channel] = false;
        return false;
    }
    return true;
}

size_t Sdl3Engine::music_queued_frames() const {
    if (!is_open()) return 0;
    return static_cast<size_t>(SDL_GetAudioStreamQueued(impl_->music)) /
           static_cast<size_t>(kMixFrameBytes);
}

size_t Sdl3Engine::sfx_queued_frames(int channel) const {
    if (channel < 0 || channel >= kMaxSfxChannels || !is_open()) return 0;
    return static_cast<size_t>(SDL_GetAudioStreamQueued(impl_->slot[channel])) /
           static_cast<size_t>(kMixFrameBytes);
}

float Sdl3Engine::music_gain() const { return impl_->music_gain; }

float Sdl3Engine::bus_gain_applied(SfxBus bus) const {
    const Impl& im = *impl_;
    switch (bus) {
        case SfxBus::Ui: return im.ui_gain;
        case SfxBus::Voice: return im.voice_gain;
        case SfxBus::Sfx: return im.sfx_gain;
    }
    return 1.0f;
}

size_t Sdl3Engine::bank_size() const { return impl_->bank.size(); }

}  // namespace fnd::audio
