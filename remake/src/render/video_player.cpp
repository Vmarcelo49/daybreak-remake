// =============================================================================
//  video_player.cpp — pl_mpeg decoder → DX9 texture + SDL_mixer audio.
//
//  plm_decode(dt) demuxes the MPEG-PS and decodes video/audio in sync, calling
//  the registered callbacks:
//    - video_decode_callback: plm_frame_to_bgra() → DX9 texture upload
//    - audio_decode_callback: float[-1,1] → S16 stereo → chunk queue
//  SDL_mixer's Mix_HookMusic drains the chunk queue into the output buffer.
//
//  PL_MPEG_IMPLEMENTATION must be defined in exactly one translation unit;
//  this is the only one that pulls in the pl_mpeg implementation.
// =============================================================================
#define PL_MPEG_IMPLEMENTATION
#include "video_player.h"

#include <SDL_mixer.h>
#include <d3dx9.h>
#include <cstdio>
#include <cstring>

namespace daybreak::render {

struct VertexTVT {
    float x, y, z, rhw;
    float u, v;
};
constexpr DWORD kFVF_TVT = D3DFVF_XYZRHW | D3DFVF_TEX1;

// ============================================================================
// Audio callback — called by SDL_mixer when it needs more samples.
// Drains m_audioChunks into the output stream, filling gaps with silence.
// ============================================================================
void VideoPlayer::audio_callback(void* udata, uint8_t* stream, int len) {
    VideoPlayer* self = static_cast<VideoPlayer*>(udata);
    if (!self) {
        std::memset(stream, 0, len);
        return;
    }

    std::lock_guard<std::mutex> lock(self->m_audioMutex);

    int written = 0;
    while (written < len) {
        if (self->m_audioChunks.empty()) {
            std::memset(stream + written, 0, len - written);
            break;
        }

        auto& chunk = self->m_audioChunks.front();
        size_t avail = chunk.size() - self->m_audioChunkOffset;
        size_t need  = static_cast<size_t>(len - written);

        if (avail <= need) {
            std::memcpy(stream + written,
                        chunk.data() + self->m_audioChunkOffset,
                        avail);
            written += static_cast<int>(avail);
            self->m_audioChunks.pop();
            self->m_audioChunkOffset = 0;
        } else {
            std::memcpy(stream + written,
                        chunk.data() + self->m_audioChunkOffset,
                        need);
            written += static_cast<int>(need);
            self->m_audioChunkOffset += need;
        }
    }
}

// ============================================================================
// video_decode_callback — pl_mpeg hands us a decoded YCrCb frame; convert to
// BGRA and mark the texture dirty so update()/render() uploads it.
// ============================================================================
void VideoPlayer::video_decode_callback(plm_t* /*plm*/, plm_frame_t* frame, void* user) {
    VideoPlayer* self = static_cast<VideoPlayer*>(user);
    if (!self || !frame) return;

    const int w = static_cast<int>(frame->width);

    // plm_frame_to_bgra() writes B, G, R and leaves alpha untouched. We keep
    // the buffer pre-filled with alpha=255 (set up in open()), so we only need
    // to overwrite B/G/R per frame. The stride is width * 4 bytes.
    plm_frame_to_bgra(frame, self->m_bgra.data(), w * 4);
    self->m_textureDirty = true;
    self->m_currentTime  = frame->time;
}

// ============================================================================
// audio_decode_callback — pl_mpeg hands us float[-1,1] stereo samples;
// convert to S16 and push onto the chunk queue.
// ============================================================================
void VideoPlayer::audio_decode_callback(plm_t* /*plm*/, plm_samples_t* samples, void* user) {
    VideoPlayer* self = static_cast<VideoPlayer*>(user);
    if (!self || !samples) return;

    // PLM_AUDIO_SAMPLES_PER_FRAME (1152) interleaved L/R samples.
    const int count = samples->count;  // per channel; interleaved = count*2
    std::vector<uint8_t> chunk;
    chunk.reserve(static_cast<size_t>(count) * 2 * sizeof(int16_t));

    for (int i = 0; i < count; ++i) {
        float l = samples->interleaved[i * 2];
        float r = samples->interleaved[i * 2 + 1];

        if (l > 1.0f) l = 1.0f; else if (l < -1.0f) l = -1.0f;
        if (r > 1.0f) r = 1.0f; else if (r < -1.0f) r = -1.0f;

        int16_t sl = static_cast<int16_t>(l * 32767.0f);
        int16_t sr = static_cast<int16_t>(r * 32767.0f);

        chunk.push_back(static_cast<uint8_t>(sl & 0xff));
        chunk.push_back(static_cast<uint8_t>((sl >> 8) & 0xff));
        chunk.push_back(static_cast<uint8_t>(sr & 0xff));
        chunk.push_back(static_cast<uint8_t>((sr >> 8) & 0xff));
    }

    std::lock_guard<std::mutex> lock(self->m_audioMutex);
    self->m_audioChunks.push(std::move(chunk));
}

VideoPlayer::~VideoPlayer() { close(); }

// ============================================================================
// Open — create pl_mpeg decoder, query dimensions, allocate BGRA buffer.
// ============================================================================
bool VideoPlayer::open(const std::string& path) {
    close();

    m_plm = plm_create_with_filename(path.c_str());
    if (!m_plm) {
        std::fprintf(stderr, "[daybreak] video: plm_create_with_filename failed: %s\n", path.c_str());
        return false;
    }

    // We want both video and audio decoded. pl_mpeg's *_enabled functions take
    // an int (1/0) — use literals rather than the windows.h TRUE/FALSE macros
    // to avoid a hard dependency on <windows.h> in this TU.
    plm_set_video_enabled(m_plm, 1);
    plm_set_audio_enabled(m_plm, 1);

    m_width  = plm_get_width(m_plm);
    m_height = plm_get_height(m_plm);
    m_videoFps = plm_get_framerate(m_plm);
    m_currentTime = 0.0;

    // Allocate BGRA buffer and pre-fill alpha=255. plm_frame_to_bgra() only
    // writes B/G/R, so the alpha byte stays 255 across frames.
    m_bgra.assign(static_cast<size_t>(m_width) * m_height * 4, 0);
    for (size_t i = 3; i < m_bgra.size(); i += 4) {
        m_bgra[i] = 255;
    }

    std::printf("[daybreak] video opened: %s  (%dx%d @ %.2ffps, %.1fs)\n",
                path.c_str(), m_width, m_height, m_videoFps, duration());
    return true;
}

// ============================================================================
// Start — create DX9 texture + vertex buffer, install callbacks, begin.
// ============================================================================
bool VideoPlayer::start(IDirect3DDevice9* device) {
    if (!is_open() || !device) return false;
    m_device = device;

    if (FAILED(D3DXCreateTexture(m_device, m_width, m_height, 1, 0,
                                  D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &m_texture)))
        return false;

    if (FAILED(m_device->CreateVertexBuffer(
            4 * sizeof(VertexTVT), D3DUSAGE_WRITEONLY, kFVF_TVT,
            D3DPOOL_MANAGED, &m_vb, nullptr))) {
        m_texture->Release(); m_texture = nullptr;
        return false;
    }

    plm_set_video_decode_callback(m_plm, &VideoPlayer::video_decode_callback, this);
    plm_set_audio_decode_callback(m_plm, &VideoPlayer::audio_decode_callback, this);

    m_playing  = true;
    m_finished = false;
    m_currentTime = 0.0;
    m_textureDirty = false;

    Mix_HookMusic(&VideoPlayer::audio_callback, this);
    std::printf("[daybreak] video playing: %dx%d @ %.1ffps (%.1fs)\n",
                m_width, m_height, m_videoFps, duration());
    return true;
}

// ============================================================================
// Update — drive pl_mpeg decoding; it paces video/audio and calls back.
// ============================================================================
void VideoPlayer::update(double dt) {
    if (!m_playing || !m_plm) return;

    // plm_decode demuxes and decodes as much as needed to cover dt seconds,
    // invoking the video/audio callbacks in sync. When the stream ends it
    // returns 0 and plm_has_ended() flips true.
    plm_decode(m_plm, dt);

    if (plm_has_ended(m_plm)) {
        m_finished = true;
        m_playing  = false;
    }

    if (m_textureDirty && m_texture) {
        D3DLOCKED_RECT lr;
        if (SUCCEEDED(m_texture->LockRect(0, &lr, nullptr, 0))) {
            uint8_t* dst = static_cast<uint8_t*>(lr.pBits);
            const int srcStride = m_width * 4;
            for (int y = 0; y < m_height; ++y) {
                std::memcpy(dst + y * lr.Pitch,
                            m_bgra.data() + static_cast<size_t>(y) * srcStride,
                            srcStride);
            }
            m_texture->UnlockRect(0);
        }
        m_textureDirty = false;
    }
}

// ============================================================================
// Render — full-screen quad
// ============================================================================
void VideoPlayer::render(IDirect3DDevice9* device) {
    if (!m_texture || !m_vb) return;

    D3DVIEWPORT9 vp;
    device->GetViewport(&vp);

    VertexTVT verts[4] = {
        { static_cast<float>(vp.X),            static_cast<float>(vp.Y),            0.0f, 1.0f, 0.0f, 0.0f },
        { static_cast<float>(vp.X + vp.Width), static_cast<float>(vp.Y),            0.0f, 1.0f, 1.0f, 0.0f },
        { static_cast<float>(vp.X),            static_cast<float>(vp.Y + vp.Height),0.0f, 1.0f, 0.0f, 1.0f },
        { static_cast<float>(vp.X + vp.Width), static_cast<float>(vp.Y + vp.Height),0.0f, 1.0f, 1.0f, 1.0f },
    };
    void* pVerts = nullptr;
    if (SUCCEEDED(m_vb->Lock(0, sizeof(verts), &pVerts, 0))) {
        std::memcpy(pVerts, verts, sizeof(verts));
        m_vb->Unlock();
    }

    DWORD oldFVF, oldLighting, oldZEnable, oldAlphaBlend;
    IDirect3DBaseTexture9* oldTexture = nullptr;
    device->GetFVF(&oldFVF);
    device->GetRenderState(D3DRS_LIGHTING, &oldLighting);
    device->GetRenderState(D3DRS_ZENABLE, &oldZEnable);
    device->GetRenderState(D3DRS_ALPHABLENDENABLE, &oldAlphaBlend);
    device->GetTexture(0, &oldTexture);
    if (oldTexture) oldTexture->Release();

    device->SetFVF(kFVF_TVT);
    device->SetRenderState(D3DRS_LIGHTING, FALSE);
    device->SetRenderState(D3DRS_ZENABLE, FALSE);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    device->SetTexture(0, m_texture);
    device->SetStreamSource(0, m_vb, 0, sizeof(VertexTVT));
    device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

    device->SetFVF(oldFVF);
    device->SetRenderState(D3DRS_LIGHTING, oldLighting);
    device->SetRenderState(D3DRS_ZENABLE, oldZEnable);
    device->SetRenderState(D3DRS_ALPHABLENDENABLE, oldAlphaBlend);
    device->SetTexture(0, oldTexture);
    if (oldTexture) oldTexture->Release();
}

// ============================================================================
// Stop / Close
// ============================================================================
void VideoPlayer::stop() {
    Mix_HookMusic(nullptr, nullptr);

    m_playing = false;
    if (m_texture) { m_texture->Release(); m_texture = nullptr; }
    if (m_vb)      { m_vb->Release();      m_vb = nullptr; }
    m_textureDirty = false;

    std::lock_guard<std::mutex> lock(m_audioMutex);
    while (!m_audioChunks.empty()) m_audioChunks.pop();
    m_audioChunkOffset = 0;
}

void VideoPlayer::close() {
    stop();
    if (m_plm) { plm_destroy(m_plm); m_plm = nullptr; }
    m_bgra.clear();
    m_width  = 0;
    m_height = 0;
    m_currentTime = 0.0;
    m_videoFps    = 0.0;
    m_finished = false;
}

double VideoPlayer::duration() const {
    if (!m_plm) return 0.0;
    return plm_get_duration(m_plm);
}

} // namespace daybreak::render
