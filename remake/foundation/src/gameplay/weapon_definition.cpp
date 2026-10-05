// gameplay/weapon_definition.cpp — the data/item/NNN.dat reader, transcribed from
// FUN_00433eb0 (0x433eb0). See weapon_definition.h for the field-by-field layout and
// for what is deliberately NOT here.
//
// The reader it mirrors advances a cursor through FUN_00653760 (0x653760), which is a
// ReadFile/`FUN_00663030` wrapper: sequential, fixed-size, no seeking. This translation
// keeps that discipline — a fixed cursor, every read bounds-checked, and a short file
// reported rather than read past.
#include "gameplay/weapon_definition.h"

#include <cstring>
#include <new>
#include <utility>

namespace gameplay {
namespace {

// The reader's cursor. A short read is an error, matching the original's assumption that
// the file matches its declared record counts.
class Cursor {
public:
    Cursor(const uint8_t* bytes, size_t size) : m_bytes(bytes), m_size(size) {}

    bool i32(int& out) {
        if (m_offset + 4 > m_size) return false;
        std::memcpy(&out, m_bytes + m_offset, 4);
        m_offset += 4;
        return true;
    }
    // A 30-byte name field: FUN_00433eb0 reads exactly 0x1e bytes and then relies on the
    // writer having NUL-terminated inside them. A field with no terminator is taken as
    // full rather than rejected, which is what the original's C-string handling does.
    bool name(std::string& out) {
        if (m_offset + kWeaponNameField > m_size) return false;
        const char* p = reinterpret_cast<const char*>(m_bytes + m_offset);
        size_t len = 0;
        while (len < kWeaponNameField && p[len] != '\0') ++len;
        out.assign(p, len);
        m_offset += kWeaponNameField;
        return true;
    }
    bool skip(size_t n) {
        if (m_offset + n > m_size) return false;
        m_offset += n;
        return true;
    }
    size_t offset() const { return m_offset; }

private:
    const uint8_t* m_bytes;
    size_t         m_size;
    size_t         m_offset = 0;
};

// Bound the declared counts against what the file could possibly hold, so a corrupt or
// mis-selected item cannot make the reader allocate wildly. The shipped maximums are
// 12 slots and 28 bullets.
constexpr int kMaxSlots = 16;
constexpr int kMaxBullets = 64;

}  // namespace

WeaponDefinition::~WeaponDefinition() { release(); }

void WeaponDefinition::release() noexcept {
    delete[] bullets;
    bullets = nullptr;
}

WeaponDefinition::WeaponDefinition(WeaponDefinition&& other) noexcept {
    *this = std::move(other);
}

WeaponDefinition& WeaponDefinition::operator=(WeaponDefinition&& other) noexcept {
    if (this == &other) return *this;
    release();
    id           = other.id;
    slotCount    = other.slotCount;
    bulletCount  = other.bulletCount;
    gaugeTexture = std::move(other.gaugeTexture);
    gaugeHeight0 = other.gaugeHeight0;
    gaugeHeight1 = other.gaugeHeight1;
    for (int i = 0; i < kMaxSlots; ++i) slots[i] = std::move(other.slots[i]);
    for (int i = 0; i < 2; ++i) magazines[i] = other.magazines[i];
    bullets        = other.bullets;
    other.bullets  = nullptr;
    other.slotCount = other.bulletCount = 0;
    return *this;
}

bool WeaponDefinition::parse(int itemId, const uint8_t* bytes, size_t size,
                             std::string& error) {
    release();
    id = itemId;
    if (bytes == nullptr || size < 8) {
        error = "weapon definition: file too small";
        return false;
    }
    Cursor cur(bytes, size);

    // FUN_00433eb0:62-66 — the two counts, then the gauge block.
    if (!cur.i32(slotCount) || !cur.i32(bulletCount)) {
        error = "weapon definition: truncated header";
        return false;
    }
    if (slotCount < 0 || slotCount > kMaxSlots || bulletCount < 0 ||
        bulletCount > kMaxBullets) {
        error = "weapon definition: implausible record counts";
        return false;
    }
    if (!cur.name(gaugeTexture)) {
        error = "weapon definition: truncated gauge block";
        return false;
    }
    if (!cur.i32(gaugeHeight0) || !cur.i32(gaugeHeight1)) {
        error = "weapon definition: truncated gauge heights";
        return false;
    }

    // FUN_00433eb0:96-120 — the attachment loop, bounded by the count just read.
    for (int i = 0; i < slotCount; ++i) {
        if (!cur.name(slots[i].meshName) || !cur.name(slots[i].textureName)) {
            error = "weapon definition: truncated attachment " + std::to_string(i);
            return false;
        }
        for (int f = 0; f < 9; ++f) {
            int raw = 0;
            if (!cur.i32(raw)) {
                error = "weapon definition: truncated attachment transform";
                return false;
            }
            // FUN_00433eb0:101-112 reads these as dwords and stores them through a float
            // cast; every shipped file writes integers here.
            slots[i].transform[f] = static_cast<float>(raw);
        }
    }

    // FUN_00433eb0:121-143 — exactly two magazines, in charge-level order.
    for (int m = 0; m < 2; ++m) {
        MagazineDefinition& mag = magazines[m];
        if (!cur.i32(mag.num) || !cur.i32(mag.type) || !cur.i32(mag.reloadTime) ||
            !cur.i32(mag.intervalTime) || !cur.i32(mag.chargeMax) ||
            !cur.i32(mag.chargeLevel)) {
            error = "weapon definition: truncated magazine " + std::to_string(m);
            return false;
        }
    }

    if (bulletCount == 0) {
        // A weapon with no bullet table still parsed; it simply cannot fire.
        error.clear();
        return true;
    }
    bullets = new (std::nothrow) BulletDefinition[static_cast<size_t>(bulletCount)];
    if (bullets == nullptr) {
        error = "weapon definition: out of memory";
        return false;
    }
    for (int i = 0; i < bulletCount; ++i) {
        BulletDefinition& b = bullets[i];
        if (!cur.i32(b.magazine) || !cur.i32(b.shotNum) || !cur.i32(b.type) ||
            !cur.i32(b.status)) {
            delete[] bullets;
            bullets = nullptr;
            error = "weapon definition: truncated bullet " + std::to_string(i);
            return false;
        }
    }
    error.clear();
    return true;
}

// FUN_005f8510 (0x5f8510) — data/bullet/<weaponId>/<type>.dat.
//   u32  leadingTag        (:71, FUN_00653760(local_26c,4))
//   260-byte model path block (:72, 0x104)
//   u32  variantCount      (:79)
//   variantCount x {
//     u32  variantId       (:84)   -- compared against the caller's Status
//     u32  a               (:88)
//     u32  b               (:89)
//     u32  subCount        (:90)
//     subCount x {
//       u32  sectionTag    (:94)
//       u32  entryCount    (:96)
//       entryCount x {              the 0x80-byte effect record, in FILE order
//         char name[30]              (:102)
//         u32  v04                  (:104)
//         f32  v0c, v10, v14        (:105-107)
//         u32  v24                  (:108)  hit radius
//         i32  blob[20]             (:109)  0x50 bytes read verbatim -> record +0x30
//         u32  v28                  (:111)
//         u32  v2c                  (:112)
//         u32  v08                  (:113)
//         f32  v18, v1c, v20        (:114-116)
//       }
//     }
//   }
bool parseBulletParameter(const uint8_t* bytes, size_t size, int status,
                          BulletParameter& out, std::string& error) {
    out = BulletParameter{};
    if (bytes == nullptr || size < 8) {
        error = "bullet parameter: file too small";
        return false;
    }
    Cursor cur(bytes, size);
    int tag = 0;
    if (!cur.i32(tag) || !cur.skip(0x104)) {
        error = "bullet parameter: truncated header";
        return false;
    }
    int variantCount = 0;
    if (!cur.i32(variantCount) || variantCount < 0 || variantCount > 64) {
        error = "bullet parameter: implausible variant count";
        return false;
    }
    for (int v = 0; v < variantCount; ++v) {
        int variantId = 0, a = 0, b = 0, subCount = 0;
        if (!cur.i32(variantId) || !cur.i32(a) || !cur.i32(b) || !cur.i32(subCount) ||
            subCount < 0 || subCount > 64) {
            error = "bullet parameter: truncated variant " + std::to_string(v);
            return false;
        }
        for (int s = 0; s < subCount; ++s) {
            int sectionTag = 0, entryCount = 0;
            if (!cur.i32(sectionTag) || !cur.i32(entryCount) || entryCount < 0 ||
                entryCount > 256) {
                error = "bullet parameter: truncated section";
                return false;
            }
            for (int e = 0; e < entryCount; ++e) {
                std::string name;
                int v04 = 0, v24 = 0, v28 = 0, v2c = 0, v08 = 0;
                float f0c = 0.f, f10 = 0.f, f14 = 0.f;
                float f18 = 0.f, f1c = 0.f, f20 = 0.f;
                int blob[20] = {0};
                if (!cur.name(name) || !cur.i32(v04) ||
                    !cur.i32(reinterpret_cast<int&>(f0c)) ||
                    !cur.i32(reinterpret_cast<int&>(f10)) ||
                    !cur.i32(reinterpret_cast<int&>(f14)) || !cur.i32(v24)) {
                    error = "bullet parameter: truncated effect record";
                    return false;
                }
                for (int i = 0; i < 20; ++i) {
                    if (!cur.i32(blob[i])) {
                        error = "bullet parameter: truncated combat block";
                        return false;
                    }
                }
                if (!cur.i32(v28) || !cur.i32(v2c) || !cur.i32(v08) ||
                    !cur.i32(reinterpret_cast<int&>(f18)) ||
                    !cur.i32(reinterpret_cast<int&>(f1c)) ||
                    !cur.i32(reinterpret_cast<int&>(f20))) {
                    error = "bullet parameter: truncated effect tail";
                    return false;
                }
                // The reader keeps every variant and only the one matching the caller's
                // Status is retained (FUN_005f8510:85-87); take its first entry.
                if (variantId == status) {
                    // blob[i] lands at record offset 0x30 + 4*i, so the index for a
                    // record offset O is (O - 0x30) / 4 -- NOT O itself. Verified against
                    // data/bullet/001/000.dat, whose first block reads
                    // 1750,0,0,0,0,75,75,100,40,0,0,0,0,102,113,21,30,500,1500,0.
                    out.effectName       = name;
                    out.hitRadius        = v24;
                    out.baseDamage       = blob[0x00];   // record +0x30
                    out.hpDamage         = blob[0x05];   // record +0x44
                    out.reflectDamage    = blob[0x06];   // record +0x48
                    out.gaugeGainA       = blob[0x07];   // record +0x4C
                    out.gaugeGainB       = blob[0x08];   // record +0x50
                    out.attackerHitstun  = blob[0x09];   // record +0x54
                    out.defenderHitstun  = blob[0x0a];   // record +0x58
                    out.hitResolutionField64 = blob[0x0d];   // record +0x64
                    out.hitResolutionField68 = blob[0x0e];   // record +0x68
                    out.hitEffect        = blob[0x0f];   // record +0x6C
                    out.secondaryEffect  = blob[0x10];   // record +0x70
                    out.releaseOffsetA   = blob[0x11];   // record +0x74
                    out.releaseOffsetB   = blob[0x12];   // record +0x78
                    error.clear();
                    return true;
                }
            }
        }
    }
    error = "bullet parameter: no variant matches status " + std::to_string(status);
    return false;
}

}  // namespace gameplay
