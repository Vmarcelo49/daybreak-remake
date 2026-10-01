// =============================================================================
//  effect_system.cpp — see effect_system.h.
// =============================================================================
#include "render/effect_system.h"

#include <cstdio>

namespace daybreak::render {

EffectSystem::~EffectSystem() { unload_all(); }

bool EffectSystem::load(IDirect3DDevice9* device, const std::string& shader_dir) {
    if (!device) {
        std::fprintf(stderr, "[daybreak] EffectSystem: no device\n");
        return false;
    }
    unload_all();

    for (int i = 0; i < kEffectCount; ++i) {
        char path[512];
        std::snprintf(path, sizeof(path), "%s/effect_%d.bin",
                      shader_dir.c_str(), i);

        FILE* f = std::fopen(path, "rb");
        if (!f) {
            std::fprintf(stderr,
                         "[daybreak] EffectSystem: missing %s — "
                         "copy assets/shaders/ next to the .exe (see assets/shaders/README.md)\n",
                         path);
            unload_all();
            return false;
        }
        std::fseek(f, 0, SEEK_END);
        long size = std::ftell(f);
        std::fseek(f, 0, SEEK_SET);
        if (size <= 0) {
            std::fclose(f);
            std::fprintf(stderr, "[daybreak] EffectSystem: empty %s\n", path);
            unload_all();
            return false;
        }
        std::string blob(static_cast<size_t>(size), '\0');
        if (std::fread(blob.data(), 1, blob.size(), f) != blob.size()) {
            std::fclose(f);
            std::fprintf(stderr, "[daybreak] EffectSystem: short read %s\n", path);
            unload_all();
            return false;
        }
        std::fclose(f);

        HRESULT hr = D3DXCreateEffect(device, blob.data(),
                                      static_cast<UINT>(blob.size()),
                                      nullptr, nullptr, 0, nullptr,
                                      &m_effects[i], nullptr);
        if (FAILED(hr) || !m_effects[i]) {
            std::fprintf(stderr,
                         "[daybreak] EffectSystem: D3DXCreateEffect failed for %s (hr=0x%08lx)\n",
                         path, static_cast<unsigned long>(hr));
            m_effects[i] = nullptr;
            unload_all();
            return false;
        }
        ++m_loaded;
    }

    std::printf("[daybreak] EffectSystem: %d/%d effects loaded from %s\n",
                m_loaded, kEffectCount, shader_dir.c_str());
    return true;
}

void EffectSystem::unload_all() {
    for (int i = 0; i < kEffectCount; ++i) {
        if (m_effects[i]) {
            m_effects[i]->Release();
            m_effects[i] = nullptr;
        }
    }
    m_loaded = 0;
}

ID3DXEffect* EffectSystem::effect(int index) const {
    if (index < 0 || index >= kEffectCount) return nullptr;
    return m_effects[index];
}

} // namespace daybreak::render
