// =============================================================================
//  effect_catalog_test.cpp — issue #17: the effect table and its recovered lifetimes.
//
//  Pins, device-free:
//    * the descriptor header (version + the fixed 260-byte model path + the variant
//      count at +0x108) and its rejection of non-descriptor bytes;
//    * the id -> descriptor mapping (`type = id/10`, FUN_0042f5e0) and the variant
//      clamp;
//    * the recovered lifetime arithmetic: round(animation seconds / 0.016) frames in
//      the original, expressed in the port's own tick rate;
//    * an id whose descriptor the install does not ship resolves to nothing (the
//      original's null model pointer), and a model with no animation is unplayable.
//
//  And against the install, when one is present (skipped otherwise):
//    * all 22 shipped descriptors parse, each declares exactly one variant, and each
//      names a model under data/effect/ that loads;
//    * every shipped model carries an animation, so every shipped descriptor has a
//      recovered lifetime — the table prints it (the port's old 12 s placeholder was
//      48x the recovered value for the melee-hit card).
//
//  Build: cmake --build remake/foundation/build/linux --target effect_catalog_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#define XMODEL_IMPLEMENTATION
#include "assets/xmodel.h"
#include "game/effect_catalog.h"

#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace fs = std::filesystem;
using game::EffectCatalog;
using game::EffectDescriptor;
using game::EffectEntry;

namespace {

int checks = 0;
int failures = 0;
int skipped = 0;

void check(bool ok, const std::string& what) {
    ++checks;
    if (!ok) {
        ++failures;
        std::printf("  FAIL  %s\n", what.c_str());
    } else {
        std::printf("  ok    %s\n", what.c_str());
    }
}
void checkInt(long long want, long long got, const std::string& what) {
    check(want == got, what + " (want " + std::to_string(want) + ", got " +
                           std::to_string(got) + ")");
}
void section(const char* title) { std::printf("\n== %s\n", title); }
void skip(const char* what) {
    ++skipped;
    std::printf("  SKIP  %s\n", what);
}

std::vector<uint8_t> synthDescriptor(const std::string& modelPath, uint32_t variants,
                                     uint32_t version = 3) {
    std::vector<uint8_t> bytes(0x108 + 4, 0);
    bytes[0] = (uint8_t)(version & 0xff);
    bytes[1] = (uint8_t)((version >> 8) & 0xff);
    bytes[2] = (uint8_t)((version >> 16) & 0xff);
    bytes[3] = (uint8_t)((version >> 24) & 0xff);
    std::snprintf(reinterpret_cast<char*>(bytes.data() + 4), 0x104, "%s", modelPath.c_str());
    bytes[0x108] = (uint8_t)(variants & 0xff);
    bytes[0x109] = (uint8_t)((variants >> 8) & 0xff);
    return bytes;
}

bool readFile(const fs::path& p, std::vector<uint8_t>& out) {
    std::ifstream in(p, std::ios::binary);
    if (!in) return false;
    out.assign(std::istreambuf_iterator<char>(in), std::istreambuf_iterator<char>());
    return !out.empty();
}

fs::path findInstall(int argc, char** argv) {
    if (argc > 1) return fs::path(argv[1]);
    if (const char* env = std::getenv("GAME_DIR")) return fs::path(env);
    std::error_code ec;
    for (fs::path r = fs::current_path(); !r.empty(); r = r.parent_path()) {
        if (fs::is_directory(r / "remake" / "foundation", ec)) {
            const fs::path game = r / "Higurashi-Daybreak";
            if (fs::is_directory(game / "data", ec)) return game;
        }
        if (r == r.parent_path()) break;
    }
    return fs::path();
}

// ---------------------------------------------------------------------------
void testDescriptorHeader() {
    section("device-free: the FUN_0042eec0 descriptor header");
    const auto bytes = synthDescriptor("14.X", 1);
    const EffectDescriptor d = game::parseEffectDescriptor(bytes);
    check(d.present, "a well-formed descriptor is present");
    check(d.modelPath == "14.X", "the 260-byte block's first NUL-terminated string is the model");
    checkInt(1, d.variants, "the u32 at +0x108 is the variant count");

    check(!game::parseEffectDescriptor({}).present, "empty bytes are not a descriptor");
    std::vector<uint8_t> shortFile(0x100, 0);
    check(!game::parseEffectDescriptor(shortFile).present,
          "a file shorter than the 0x108 header is rejected");

    std::vector<uint8_t> unterminated(0x108 + 4, 'A');
    check(!game::parseEffectDescriptor(unterminated).present,
          "a path block with no NUL is rejected (FUN_0042eec0's read stops at 0x104)");

    // Stale bytes after the first NUL are not a second name (the DX9 reader's rule).
    std::vector<uint8_t> twoNames = synthDescriptor("14.X", 1);
    std::snprintf(reinterpret_cast<char*>(twoNames.data() + 4), 0x104, "14.X");
    twoNames[9] = '.';
    twoNames[10] = 'X';
    check(game::parseEffectDescriptor(twoNames).modelPath == "14.X",
          "bytes after the first NUL do not extend the model path");
}

void testIdMappingAndLifetime() {
    section("device-free: the id space and the recovered lifetime");
    checkInt(0, game::effectTypeOf(0), "id 0 is type 0");
    checkInt(0, game::effectTypeOf(9), "id 9 is type 0 variant 9");
    checkInt(1, game::effectTypeOf(10), "id 10 is type 1");
    checkInt(38, game::effectTypeOf(380), "id 380 is type 38 (the burning aura's puff)");
    checkInt(0, game::effectVariantOf(10), "id 10 is variant 0");
    checkInt(9, game::effectVariantOf(39), "id 39 is variant 9");

    // The original: round(seconds / 0.016) frames. 0.25 s -> 16 frames at 62.5 fps.
    checkInt(16, (int)std::lround(0.25 / game::kOriginalFrameSeconds),
             "the recovered conversion turns 0.25 s into 16 original frames");
    // The port keeps the seconds: the same effect at 64 Hz.
    checkInt(16, game::effectLifetimeTicks(0.25f, 64.f), "0.25 s is 16 ticks at 64 Hz");
    checkInt(0, game::effectLifetimeTicks(0.f, 64.f), "no animation means no lifetime");
    checkInt(0, game::effectLifetimeTicks(-1.f, 64.f), "a negative duration is not a lifetime");
    checkInt(0, game::effectLifetimeTicks(0.25f, 0.f), "a zero tick rate is not a lifetime");

    EffectCatalog cat;
    cat.add(0, game::parseEffectDescriptor(synthDescriptor("14.X", 1)), 7, 0.25f);
    check(cat.find(0) != nullptr, "a registered descriptor is found by its own id");
    check(cat.find(3) != nullptr, "ids N*10+1..9 clamp onto the same descriptor record");
    check(cat.find(10) == nullptr, "an id whose descriptor the install does not ship resolves to nothing");
    check(cat.find(-1) == nullptr, "a negative id resolves to nothing");
    checkInt(16, cat.lifetime_ticks(0, 64.f), "the catalog reports the recovered tick count");
    checkInt(0, cat.lifetime_ticks(10, 64.f), "an unshipped id has no lifetime");
    const EffectEntry* e = cat.find(0);
    check(e && e->playable(), "an entry with a model, an asset and an animation is playable");
    checkInt(1, cat.count(), "the catalog counts the descriptors it holds");

    EffectCatalog dead;
    dead.add(2, game::parseEffectDescriptor(synthDescriptor("13.X", 1)), 3, 0.f);
    check(dead.find(20) && !dead.find(20)->playable(),
          "a model with no animation is present but not playable (descriptor[0] == 0 retires at once)");
    checkInt(0, dead.lifetime_ticks(20, 64.f), "an unplayable entry has no lifetime");
}

// ---------------------------------------------------------------------------
void testInstallTable(int argc, char** argv) {
    section("asset-backed: the 22 shipped descriptors and their model lifetimes");
    const fs::path install = findInstall(argc, argv);
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data" / "effect", ec)) {
        skip("the install's effect table (no install found)");
        return;
    }
    EffectCatalog cat;
    int present = 0, withModel = 0, withAnim = 0;
    for (int type = 0; type < game::kEffectSlots; ++type) {
        char rel[64];
        std::snprintf(rel, sizeof(rel), "data/effect/%03d.dat", type);
        std::vector<uint8_t> bytes;
        if (!readFile(install / rel, bytes)) continue;
        const EffectDescriptor d = game::parseEffectDescriptor(bytes);
        if (!d.present) {
            check(false, std::string(rel) + " parses as a descriptor");
            continue;
        }
        ++present;
        checkInt(1, d.variants, std::string(rel) + " declares exactly one variant");

        // The lifetime source: the model's own first animation (FUN_0042eec0).
        const fs::path model = install / "data" / "effect" / d.modelPath;
        if (!fs::exists(model, ec)) {
            check(false, std::string(rel) + " names an installed model (" + d.modelPath + ")");
            continue;
        }
        const xm::Model m = xm::loadFile(model.string());
        ++withModel;
        const float seconds =
            m.anims.empty() ? 0.f : m.anims[0].duration / (m.ticksPerSecond > 0 ? m.ticksPerSecond : 1.f);
        if (seconds > 0.f) ++withAnim;
        cat.add(type, d, /*asset=*/type, seconds);
        std::printf("        id %3d  %-9s %-9s %5.3f s -> %3d ticks @64Hz (%2d original frames)\n",
                    type * 10, rel + 11, d.modelPath.c_str(), (double)seconds,
                    cat.lifetime_ticks(type * 10, 64.f),
                    (int)std::lround(seconds / game::kOriginalFrameSeconds));
    }
    checkInt(22, present, "the install ships 22 effect descriptors");
    checkInt(22, withModel, "every descriptor's model loads");
    checkInt(22, withAnim, "every shipped effect model carries an animation (the lifetime source)");
    checkInt(22, cat.count(), "the catalog holds one entry per shipped descriptor");
    // The melee-hit card the port drew for 12 s: 14.X is 0.250 s.
    checkInt(16, cat.lifetime_ticks(0, 64.f), "the melee-hit card (id 0 -> 14.X) lives 16 ticks at 64 Hz");
    check(cat.lifetime_ticks(0, 64.f) < 64, "the recovered hit-card lifetime is under a second");
}

}  // namespace

int main(int argc, char** argv) {
    std::puts("effect_catalog_test — issue #17 effect table");
    testDescriptorHeader();
    testIdMappingAndLifetime();
    testInstallTable(argc, argv);
    std::printf("\n%d checks, %d failure(s)%s\n", checks, failures,
                skipped ? " (with skips)" : "");
    return failures == 0 ? 0 : 1;
}
