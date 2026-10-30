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
    bool name(std::string& out, size_t width = kWeaponNameField) {
        if (m_offset + width > m_size) return false;
        const char* p = reinterpret_cast<const char*>(m_bytes + m_offset);
        size_t len = 0;
        while (len < width && p[len] != '\0') ++len;
        out.assign(p, len);
        m_offset += width;
        return true;
    }
    // The 260-byte model block of a bullet or effect descriptor: fixed width, NUL-padded,
    // read whole. FUN_005f8510:73 hands the bytes straight to wsprintfA("%s%s", dir, block),
    // so the name ends at the first NUL. A block with no NUL at all is the one case the
    // original reads past; here it yields an empty name (no model), which is the same
    // outcome as a blank block rather than a second invented rule.
    bool modelName(std::string& out) {
        constexpr size_t kModelBlock = 0x104;
        if (m_offset + kModelBlock > m_size) return false;
        const char* p = reinterpret_cast<const char*>(m_bytes + m_offset);
        size_t len = 0;
        while (len < kModelBlock && p[len] != '\0') ++len;
        out.assign(p, len < kModelBlock ? len : 0);
        m_offset += kModelBlock;
        return true;
    }
    size_t offset() const { return m_offset; }
    bool record(MoveEntry& out) {
        return readCombatRecord(m_bytes, m_size, m_offset, out);
    }

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
        float* anchors[3] = {slots[i].muzzle, slots[i].ribbonRoot, slots[i].ribbonTip};
        for (int f = 0; f < 9; ++f) {
            int raw = 0;
            if (!cur.i32(raw)) {
                error = "weapon definition: truncated attachment anchors";
                return false;
            }
            // FUN_00433eb0:101-112 reads these as dwords and stores them through a float
            // cast (FILD); every shipped file writes integers here.
            anchors[f / 3][f % 3] = static_cast<float>(raw);
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
        if (!cur.i32(b.magazine) || !cur.i32(b.poolCapacity) || !cur.i32(b.type) ||
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
//   260-byte model path block (:72, 0x104) — the bullet's own model. The reader joins it
//     to the bullet directory and loads it (:73-75, FUN_0064d940) before it reads a
//     single combat field, and a load failure aborts the whole file, so this block is
//     load-bearing data and not a comment field.
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
//         i32  v0c, v10, v14        (:105-107), numeric conversion to floats
//         u32  v24                  (:108)  hit radius
//         i32  blob[20]             (:109)  0x50 bytes read verbatim -> record +0x30
//         u32  v28                  (:111)
//         u32  v2c                  (:112)
//         u32  v08                  (:113)
//         i32  v18, v1c, v20        (:114-116), numeric conversion to floats
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
    if (!cur.i32(out.formatTag) || !cur.modelName(out.modelName)) {
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
        if (variantId == status) {
            out.priority = a;
            out.cancelThreshold = b;
            out.phases.clear(); // Repeated IDs overwrite, just like NN.dat rows.
        }
        for (int s = 0; s < subCount; ++s) {
            int sectionTag = 0, entryCount = 0;
            if (!cur.i32(sectionTag) || !cur.i32(entryCount) || entryCount < 0 ||
                entryCount > 256) {
                error = "bullet parameter: truncated section";
                return false;
            }
            if (variantId == status) {
                if (entryCount > MovePhase::kMaxPhaseEntries) {
                    error = "bullet parameter: phase entry storage exceeded";
                    return false;
                }
                out.phases.emplace_back();
                out.phases.back().setIndex = sectionTag;
            }
            for (int e = 0; e < entryCount; ++e) {
                MoveEntry record;
                if (!cur.record(record)) {
                    error = "bullet parameter: truncated state record";
                    return false;
                }
                // FUN_005f8510 consumes every variant, but binds only caller Status.
                if (variantId == status) {
                    auto& phase = out.phases.back();
                    phase.entries[phase.entryCount++] = record;
                }
            }
        }
    }
    // FUN_005f8510's trailer has the same 12 + 132*n byte rows as NN.dat.
    // Never stop after the first matching combat record: later phases/material
    // intervals are part of the same projectile definition.
    int setCount = 0;
    if (!cur.i32(setCount) || setCount < 0 || setCount > CharacterMoves::kMaxAnimationSets) {
        error = "bullet parameter: invalid animation trailer";
        return false;
    }
    out.animationSets.resize(static_cast<size_t>(setCount));
    for (auto& set : out.animationSets) {
        int count = 0;
        if (!cur.i32(set.transition) || !cur.i32(set.phaseGate) || !cur.i32(count) ||
            count < 0 || count > 4096) {
            error = "bullet parameter: truncated animation row";
            return false;
        }
        for (int i = 0; i < count; ++i) {
            TextureEvent event;
            if (!cur.i32(event.start) || !cur.i32(event.end) || !cur.i32(event.repeat) ||
                !cur.name(event.source, 60) || !cur.name(event.replacement, 60)) {
                error = "bullet parameter: truncated texture interval";
                return false;
            }
            set.textures.push_back(std::move(event));
        }
    }
    if (cur.offset() != size) {
        error = "bullet parameter: unexpected trailing bytes";
        return false;
    }
    if (!out.phases.empty()) {
        if (out.phases.front().entryCount) {
            const auto& record = out.phases.front().entries[0];
            out.boneName = record.boneName;
            out.hitRadius = record.hitRadius;
            out.baseDamage = record.baseDamage;
            out.hpDamage = record.hpDamage;
            out.reflectDamage = record.reflectDamage;
            out.gaugeGainA = record.gaugeGainA;
            out.gaugeGainB = record.gaugeGainB;
            out.attackerHitstun = record.attackerHitstun;
            out.defenderHitstun = record.defenderHitstun;
            out.hitResolutionField64 = record.combat[13];
            out.hitResolutionField68 = record.combat[14];
            out.hitSound = record.combat[15];
            out.impactEffect = record.combat[16];
            out.releaseOffsetA = record.combat[17];
            out.releaseOffsetB = record.combat[18];
        }
        error.clear();
        return true;
    }
    error = "bullet parameter: no variant matches status " + std::to_string(status);
    return false;
}

}  // namespace gameplay
