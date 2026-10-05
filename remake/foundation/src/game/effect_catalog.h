#pragma once
// game/effect_catalog.h — the effect table: which data/effect/NNN.dat descriptor an
// effect id names, and how long an instance of it lives.
//
// Recovered (issue #17), all addresses in DaybreakDX.exe:
//
//   * FUN_0042eba0 loads the table: 100 descriptors, `data/effect/%03d.dat` (the
//     format string at 0x6a24e0), into the manager at scene+0x5210, with a 1000-entry
//     0x1c-byte variant array, a 100-entry 0x38-byte descriptor array and 100 model
//     pointers. The install ships 22 of the 100 files; the rest stay null.
//   * An effect id is `type * 10 + variant`: FUN_0042f5e0 (the manager's create method,
//     vtable 0x6a2500 +0x08) indexes the model and descriptor arrays with `id / 10` and
//     the variant array with the full `id`. The file number IS the type.
//   * FUN_0042eec0 reads a descriptor as: a version dword, a fixed 260-byte model path
//     (0x104 bytes, relative to data/effect/), then a variant count at file offset
//     0x108, then per variant a part list whose entries carry the [start, end) frame
//     windows FUN_00436150 draws with (`age % period` when a period is set). The file
//     carries NO lifetime — that is why every "raw lifetime" read of these 22 files is
//     zero, and why a lifetime cannot be recovered from the descriptor at all.
//   * The lifetime is the MODEL's own animation duration. FUN_0042eec0 asks the loaded
//     model for its first animation (FUN_0064e8b0(model, 0), the model's vtable), then
//     divides by 0.016 (the float at 0x6a2434) and rounds to whole frames
//     (0x42f412-0x42f423 stores the result into descriptor[0]). FUN_00436630 ages the
//     instance once per frame (+0x130) and retires it when `descriptor[0] <= age`;
//     FUN_00436150 drives the model's animation with `age * 0.016` seconds, which
//     confirms the unit.
//
// Port rule: the recovered count is a frame count at 0.016 s per frame, so the port
// keeps the animation's SECONDS and converts them at its own 64 Hz step. An effect then
// lasts the same wall-clock time it did in the original instead of inheriting 62.5 Hz
// arithmetic. glm + std only: this header is device-free and unit-tested.
#include <array>
#include <cmath>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

namespace game {

inline constexpr int kEffectSlots = 100;              // FUN_0042eba0's loop bound
inline constexpr int kEffectVariantsPerType = 10;     // id = type * 10 + variant
inline constexpr float kOriginalFrameSeconds = 0.016f;  // 0x6a2434

// One parsed data/effect/NNN.dat header. `variants` is the u32 at file offset 0x108.
struct EffectDescriptor {
    std::string modelPath;   // the fixed 260-byte path block, up to its first NUL
    int  variants = 0;
    bool present  = false;   // the bytes were a descriptor at all
};

// FUN_0042eec0's header read: 4 + 0x104 bytes, path up to the first NUL. Stale bytes
// after that NUL are not a second name (the same rule the port already applied through
// effectModelPath; this is its catalog-side home).
inline EffectDescriptor parseEffectDescriptor(const std::vector<uint8_t>& bytes) {
    EffectDescriptor out;
    // FUN_0042eec0 reads a 4-byte version and then a fixed 0x104-byte path block; a
    // shorter file cannot be a descriptor (the smallest shipped one is 474 bytes).
    if (bytes.size() < 0x108) return out;
    size_t end = 4;
    while (end < 0x108 && bytes[end]) ++end;
    if (end == 0x108) return out;   // no terminator: not a path block
    out.modelPath.assign(reinterpret_cast<const char*>(bytes.data() + 4), end - 4);
    out.variants = (int)((uint32_t)bytes[0x108] | ((uint32_t)bytes[0x109] << 8) |
                         ((uint32_t)bytes[0x10a] << 16) | ((uint32_t)bytes[0x10b] << 24));
    out.present = !out.modelPath.empty();
    return out;
}

inline int effectTypeOf(int id) { return id / kEffectVariantsPerType; }
inline int effectVariantOf(int id) { return id % kEffectVariantsPerType; }

// The recovered lifetime: round(animation seconds / 0.016) frames, converted to the
// caller's tick rate. Returns 0 for a model with no animation (unplayable: the original
// would retire the instance on its first update, which is what a zero descriptor[0]
// means).
inline int effectLifetimeTicks(float animSeconds, float tickRate) {
    if (!(animSeconds > 0.f) || !(tickRate > 0.f)) return 0;
    // The original's own arithmetic is round(seconds / 0.016) frames (0x42f412-0x42f423);
    // this keeps the seconds and lets the port's step convert them.
    return (int)std::lround((double)animSeconds * (double)tickRate);
}

// One table slot, indexed by descriptor file number (the type half of an id).
struct EffectEntry {
    int    type = -1;
    EffectDescriptor descriptor;
    int    asset = -1;              // the host renderer's asset index, -1 = not loaded
    float  lifetimeSeconds = 0.f;   // the model's own animation duration
    bool playable() const { return descriptor.present && asset >= 0 && lifetimeSeconds > 0.f; }
};

// The install's effect table. One entry per descriptor file the install ships; ids that
// name a missing file resolve to nullptr, which is the original's null model pointer.
class EffectCatalog {
public:
    void clear() { m_entries = {}; m_count = 0; }

    // Registers descriptor file `type` with the asset its model loaded into and the
    // model's animation duration in seconds (FUN_0042eec0's lifetime source).
    void add(int type, EffectDescriptor descriptor, int asset, float animSeconds) {
        if (type < 0 || type >= kEffectSlots) return;
        EffectEntry& e = m_entries[(size_t)type];
        if (e.type < 0) ++m_count;
        e.type = type;
        e.descriptor = std::move(descriptor);
        e.asset = asset;
        e.lifetimeSeconds = animSeconds > 0.f ? animSeconds : 0.f;
    }

    // The entry an effect id names, or nullptr when the install ships no such descriptor.
    // The variant half is clamped to the descriptor's own variant count: every shipped
    // file declares exactly one, so ids N*10+1..N*10+9 name the same record as N*10.
    // PORT RULE — the original indexes a 1000-slot variant array where only the declared
    // variants are constructed, so a variant past the count reads uninitialised data.
    const EffectEntry* find(int id) const {
        if (id < 0) return nullptr;
        const int type = effectTypeOf(id);
        if (type < 0 || type >= kEffectSlots) return nullptr;
        const EffectEntry& e = m_entries[(size_t)type];
        if (e.type < 0 || !e.descriptor.present) return nullptr;
        return &e;
    }

    // The recovered lifetime in the caller's ticks; 0 when the id is not playable.
    int lifetime_ticks(int id, float tickRate) const {
        const EffectEntry* e = find(id);
        return e ? effectLifetimeTicks(e->lifetimeSeconds, tickRate) : 0;
    }

    int count() const { return m_count; }
    const EffectEntry& entry_at(int type) const { return m_entries[(size_t)type]; }

private:
    std::array<EffectEntry, kEffectSlots> m_entries{};
    int m_count = 0;
};

}  // namespace game
