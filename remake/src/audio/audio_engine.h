// =============================================================================
//  audio_engine.h — SDL2_mixer-based audio engine.
//
//  Uses SDL2_mixer (the SDL2 audio companion library) for playback + mixing.
//  SDL2_mixer 2.8.0 has built-in OGG Vorbis support (no external DLLs needed).
//
//  Supported formats:
//    - WAV  (Mix_LoadWAV)
//    - OGG  (Mix_LoadMUS for streaming, or Mix_LoadWAV for fully-decoded)
//    - MP3  (Mix_LoadWAV, if SDL2_mixer was built with MP3 support)
//
//  Architecture:
//    - AudioEngine owns the SDL2_mixer device (opened once at startup).
//    - Sound objects wrap Mix_Chunk* (short SFX, fully loaded in memory).
//    - Music objects wrap Mix_Music* (BGM, streamed from disk/memory).
//    - Up to 32 simultaneous SFX channels + 1 music channel.
// =============================================================================
#pragma once

#include <SDL_mixer.h>
#include <cstdint>
#include <string>
#include <vector>

namespace daybreak::audio {

// A short sound effect (fully decoded in memory).  Use for voice cues,
// hit sounds, UI clicks.  For BGM, use Music instead.
class Sound {
public:
    Sound() = default;
    ~Sound();

    Sound(const Sound&)            = delete;
    Sound& operator=(const Sound&) = delete;

    // Loads a sound from an in-memory buffer.  Writes to a temp file then
    // calls Mix_LoadWAV (SDL_mixer doesn't have a load-from-memory API for
    // all formats).  Returns false on failure.
    bool load_from_memory(const uint8_t* bytes, size_t size);

    // Loads a sound from a file on disk.
    bool load_from_file(const std::string& path);

    void unload();

    bool         is_loaded() const { return m_chunk != nullptr; }
    Mix_Chunk*   chunk()     const { return m_chunk; }
    int          duration_ms() const;  // approximate

private:
    Mix_Chunk* m_chunk = nullptr;
    int        m_freq   = 0;
    int        m_channels = 0;
    int        m_samples = 0;  // total samples
};

// Streaming music (BGM).  Only one music track can play at a time.
class Music {
public:
    Music() = default;
    ~Music();

    Music(const Music&)            = delete;
    Music& operator=(const Music&) = delete;

    // Loads music from a temp file (SDL_mixer needs a file path for streaming).
    bool load_from_memory(const uint8_t* bytes, size_t size);
    bool load_from_file(const std::string& path);
    void unload();

    bool       is_loaded() const { return m_music != nullptr; }
    Mix_Music* music()     const { return m_music; }

private:
    Mix_Music* m_music = nullptr;
};

// Opaque handle for a playing SFX.  0 = invalid.
using SoundHandle = int;
constexpr SoundHandle kInvalidHandle = -1;

class AudioEngine {
public:
    AudioEngine() = default;
    ~AudioEngine();

    AudioEngine(const AudioEngine&)            = delete;
    AudioEngine& operator=(const AudioEngine&) = delete;

    // Initializes SDL2_mixer (44100 Hz, stereo, 2048-sample buffer).
    // Call once at startup.  Returns false on failure.
    bool init();

    void shutdown();

    // Plays a Sound on a free channel.  Returns the channel number
    // (use as handle for stop/is_playing/set_volume), or kInvalidHandle.
    SoundHandle play(const Sound& sound, int loops = 0);

    // Plays streaming Music.  Only one music at a time.  loops=-1 = forever.
    void play_music(const Music& music, int loops = -1);

    void stop(SoundHandle handle);
    void stop_music();
    bool is_playing(SoundHandle handle) const;
    bool is_music_playing() const;

    void set_volume(SoundHandle handle, int volume);  // 0-128
    void set_music_volume(int volume);  // 0-128

    void stop_all();

    // SDL_mixer uses channels 0..31 for SFX.  We reserve channel 0 for
    // UI sounds, 1-15 for voice cues, 16-31 for gameplay SFX.
    static constexpr int kMaxChannels = 32;

private:
    bool m_initialized = false;
};

} // namespace daybreak::audio
