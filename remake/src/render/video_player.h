// =============================================================================
//  video_player.h — pl_mpeg-based video player that decodes MPEG1 video and
//  MP2 audio to a DX9 texture.
//
//  Decoding is driven by plm_decode(dt) which handles A/V sync internally and
//  invokes the video/audio callbacks registered in start(). Audio is streamed
//  via SDL_mixer's Mix_HookMusic callback, which drains a ring of pre-decoded
//  S16 stereo chunks.
// =============================================================================
#pragma once

#include <d3d9.h>

#include <cstdint>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

// pl_mpeg is a single-file C library. We include the full header here because
// the decode callbacks need access to plm_frame_t / plm_samples_t members.
// The implementation is compiled once in video_player.cpp with
// PLM_IMPLEMENTATION defined (so this header does NOT define it).
#include "pl_mpeg.h"

namespace daybreak::render {

class VideoPlayer {
public:
    VideoPlayer() = default;
    ~VideoPlayer();

    VideoPlayer(const VideoPlayer&)            = delete;
    VideoPlayer& operator=(const VideoPlayer&) = delete;

    bool open(const std::string& path);
    bool start(IDirect3DDevice9* device);
    void update(double dt);
    void render(IDirect3DDevice9* device);
    void stop();
    void close();

    bool is_open()    const { return m_plm != nullptr; }
    bool is_playing() const { return m_playing; }
    bool is_finished() const { return m_finished; }

    int width()  const { return m_width; }
    int height() const { return m_height; }
    double duration() const;
    double current_time() const { return m_currentTime; }
    double video_fps()   const { return m_videoFps; }

private:
    // pl_mpeg callbacks (static → trampoline into the instance via user data).
    static void video_decode_callback(plm_t* plm, plm_frame_t* frame, void* user);
    static void audio_decode_callback(plm_t* plm, plm_samples_t* samples, void* user);
    static void audio_callback(void* udata, uint8_t* stream, int len);

    // pl_mpeg state.
    plm_t* m_plm = nullptr;

    // Frame dimensions (display size) and decoded BGRA buffer.
    int                 m_width  = 0;
    int                 m_height = 0;
    std::vector<uint8_t> m_bgra;       // width * height * 4, alpha pre-set to 255

    // DX9 state.
    IDirect3DDevice9*       m_device  = nullptr;
    IDirect3DTexture9*      m_texture = nullptr;
    IDirect3DVertexBuffer9* m_vb      = nullptr;
    bool                    m_textureDirty = false;

    // Playback state.
    bool   m_playing       = false;
    bool   m_finished      = false;
    double m_currentTime   = 0.0;
    double m_videoFps      = 0.0;

    // Audio streaming — SDL_mixer's Mix_HookMusic calls audio_callback which
    // drains these chunks.  audio_decode_callback converts pl_mpeg's float
    // samples to S16 stereo and pushes them here.
    std::mutex m_audioMutex;
    std::queue<std::vector<uint8_t>> m_audioChunks;
    size_t m_audioChunkOffset = 0;
};

} // namespace daybreak::render
