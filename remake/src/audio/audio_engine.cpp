// =============================================================================
//  audio_engine.cpp — SDL2_mixer implementation.
//
//  SDL2_mixer handles device management, mixing, and format decoding.
//  Our wrapper adds:
//    - load_from_memory (via temp file, since SDL_mixer needs file paths
//      for most formats)
//    - RAII (Sound/Music destructor calls Mix_FreeChunk/Mix_FreeMusic)
//    - Simple handle-based channel management
// =============================================================================
#include "audio_engine.h"

#include <SDL.h>
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>

namespace daybreak::audio {

// ----------------------------------------------------------------------------
// Helper: write bytes to a temp file and return the path.
// SDL_mixer's Mix_LoadWAV and Mix_LoadMUS take file paths; they don't have
// a generic "load from memory" API (Mix_QuickLoad_WAV only works for raw
// WAV data that's already in the right format).  So we write to a temp file.
// ----------------------------------------------------------------------------
static std::string write_temp_file(const uint8_t* bytes, size_t size,
                                    const char* suffix) {
    char tmpl[512];
    // Use GetTempPathA on Windows; fallback to /tmp on Linux (for testing).
    #ifdef _WIN32
    char tempDir[MAX_PATH];
    GetTempPathA(MAX_PATH, tempDir);
    std::snprintf(tmpl, sizeof(tmpl), "%sdaybreak_XXXXXX%s", tempDir, suffix);
    #else
    std::snprintf(tmpl, sizeof(tmpl), "/tmp/daybreak_XXXXXX%s", suffix);
    #endif

    // mkstemp would be cleaner but isn't available on MinGW without extra work.
    // Use a simple unique name based on a counter.
    static int counter = 0;
    char path[512];
    std::snprintf(path, sizeof(path), "%s", tmpl);
    char* xxx = std::strstr(path, "XXXXXX");
    if (xxx) {
        std::snprintf(xxx, 7, "%06d", counter++);
    }

    std::ofstream f(path, std::ios::binary);
    if (!f.is_open()) return {};
    f.write(reinterpret_cast<const char*>(bytes), static_cast<std::streamsize>(size));
    return std::string(path);
}

// ============================================================================
// Sound
// ============================================================================
Sound::~Sound() { unload(); }

bool Sound::load_from_memory(const uint8_t* bytes, size_t size) {
    unload();
    if (!bytes || size == 0) return false;

    // Detect format from magic bytes to pick the right temp file extension.
    const char* suffix = ".wav";
    if (size >= 4 && std::memcmp(bytes, "OggS", 4) == 0) suffix = ".ogg";
    else if (size >= 3 && bytes[0] == 0x49 && bytes[1] == 0x44 && bytes[2] == 0x33) suffix = ".mp3";

    std::string path = write_temp_file(bytes, size, suffix);
    if (path.empty()) {
        std::fprintf(stderr, "[daybreak] audio: cannot write temp file\n");
        return false;
    }

    m_chunk = Mix_LoadWAV(path.c_str());
    // Clean up temp file (SDL_mixer has already read it).
    std::remove(path.c_str());

    if (!m_chunk) {
        std::fprintf(stderr, "[daybreak] audio: Mix_LoadWAV failed: %s\n",
                     Mix_GetError());
        return false;
    }
    return true;
}

bool Sound::load_from_file(const std::string& path) {
    unload();
    m_chunk = Mix_LoadWAV(path.c_str());
    if (!m_chunk) {
        std::fprintf(stderr, "[daybreak] audio: Mix_LoadWAV(%s) failed: %s\n",
                     path.c_str(), Mix_GetError());
        return false;
    }
    return true;
}

void Sound::unload() {
    if (m_chunk) {
        Mix_FreeChunk(m_chunk);
        m_chunk = nullptr;
    }
}

int Sound::duration_ms() const {
    if (!m_chunk) return 0;
    // Mix_Chunk doesn't store duration directly.  We'd need to know the
    // format's sample rate + total samples; callers can use is_playing()
    // to check instead.
    return 0;
}

// ============================================================================
// Music
// ============================================================================
Music::~Music() { unload(); }

bool Music::load_from_memory(const uint8_t* bytes, size_t size) {
    unload();
    if (!bytes || size == 0) return false;

    const char* suffix = ".ogg";
    if (size >= 4 && std::memcmp(bytes, "RIFF", 4) == 0) suffix = ".wav";

    std::string path = write_temp_file(bytes, size, suffix);
    if (path.empty()) return false;

    m_music = Mix_LoadMUS(path.c_str());
    std::remove(path.c_str());

    if (!m_music) {
        std::fprintf(stderr, "[daybreak] audio: Mix_LoadMUS failed: %s\n",
                     Mix_GetError());
        return false;
    }
    return true;
}

bool Music::load_from_file(const std::string& path) {
    unload();
    m_music = Mix_LoadMUS(path.c_str());
    if (!m_music) {
        std::fprintf(stderr, "[daybreak] audio: Mix_LoadMUS(%s) failed: %s\n",
                     path.c_str(), Mix_GetError());
        return false;
    }
    return true;
}

void Music::unload() {
    if (m_music) {
        Mix_FreeMusic(m_music);
        m_music = nullptr;
    }
}

// ============================================================================
// AudioEngine
// ============================================================================
AudioEngine::~AudioEngine() { shutdown(); }

bool AudioEngine::init() {
    if (m_initialized) return true;

    // SDL_Init must have been called already (by main.cpp).  We just init
    // SDL_mixer's audio subsystem.
    int flags = MIX_INIT_OGG | MIX_INIT_MP3 | MIX_INIT_FLAC;
    int initted = Mix_Init(flags);
    if ((initted & flags) != flags) {
        std::fprintf(stderr, "[daybreak] audio: Mix_Init partial: got=0x%x want=0x%x (%s)\n",
                     initted, flags, Mix_GetError());
        // Not fatal — OGG is the critical one; MP3/FLAC are optional.
    }

    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048) < 0) {
        std::fprintf(stderr, "[daybreak] audio: Mix_OpenAudio failed: %s\n",
                     Mix_GetError());
        return false;
    }

    Mix_AllocateChannels(kMaxChannels);
    m_initialized = true;
    std::printf("[daybreak] audio engine initialized (SDL_mixer, 44100Hz stereo)\n");
    std::printf("[daybreak]   Mix_Init flags: 0x%x (OGG=%d, MP3=%d, FLAC=%d)\n",
                initted,
                (initted & MIX_INIT_OGG) ? 1 : 0,
                (initted & MIX_INIT_MP3) ? 1 : 0,
                (initted & MIX_INIT_FLAC) ? 1 : 0);
    return true;
}

void AudioEngine::shutdown() {
    if (!m_initialized) return;
    stop_all();
    Mix_CloseAudio();
    Mix_Quit();
    m_initialized = false;
}

SoundHandle AudioEngine::play(const Sound& sound, int loops) {
    if (!m_initialized || !sound.is_loaded()) return kInvalidHandle;
    int channel = Mix_PlayChannel(-1, sound.chunk(), loops);
    if (channel < 0) {
        std::fprintf(stderr, "[daybreak] audio: Mix_PlayChannel failed: %s\n",
                     Mix_GetError());
        return kInvalidHandle;
    }
    return channel;
}

void AudioEngine::play_music(const Music& music, int loops) {
    if (!m_initialized || !music.is_loaded()) return;
    Mix_PlayMusic(music.music(), loops);
}

void AudioEngine::stop(SoundHandle handle) {
    if (handle < 0) return;
    Mix_HaltChannel(handle);
}

void AudioEngine::stop_music() {
    Mix_HaltMusic();
}

bool AudioEngine::is_playing(SoundHandle handle) const {
    if (handle < 0) return false;
    return Mix_Playing(handle) != 0;
}

bool AudioEngine::is_music_playing() const {
    return Mix_PlayingMusic() != 0;
}

void AudioEngine::set_volume(SoundHandle handle, int volume) {
    if (handle < 0) return;
    Mix_Volume(handle, volume);
}

void AudioEngine::set_music_volume(int volume) {
    Mix_VolumeMusic(volume);
}

void AudioEngine::stop_all() {
    Mix_HaltChannel(-1);
    Mix_HaltMusic();
}

} // namespace daybreak::audio
