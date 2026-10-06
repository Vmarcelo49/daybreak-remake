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
//  The attachment half of the same loader (FUN_00633ca0's seven data/aura/%02d.x models,
//  issue #33), device-free and against the install:
//    * the eleven attach points FUN_0041e180 resolves on the fighter's rig and FUN_004205e0
//      draws the attachment on, in slot order, and the resolve rule: one instance per
//      resolved point, and none at all when a rig resolves none (never eleven copies of
//      frame 0);
//    * every shipped attachment is ONE unskinned model that carries no attach point of its
//      own, and every shipped character model carries all eleven points. The eleven-
//      iteration loop is therefore fully populated, so the port draws ELEVEN instances per
//      active aura, not one. A future rig with a partial attach set fails here instead of
//      quietly drawing fewer than the original.
//
//  Build: cmake --build remake/foundation/build/linux --target effect_catalog_test
//  Exit status: 0 when every check passes, 1 otherwise.
// =============================================================================
#define XMODEL_IMPLEMENTATION
#include "assets/xmodel.h"
#include "game/aura_attach.h"
#include "game/effect_catalog.h"

#include <cctype>
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

// ---------------------------------------------------------------------------
// Issue #33. A rig stub for the device-free half: the resolve rule only asks a rig for
// frames by name, so the rule is testable with no install and no asset layer.
struct StubRig {
    std::vector<std::string> frames;
    int findFrame(const std::string& name) const {
        for (size_t i = 0; i < frames.size(); ++i)
            if (frames[i] == name) return (int)i;
        return -1;
    }
};

void testAuraAttachRule() {
    section("device-free: the eleven attach points and the aura instance rule");
    checkInt(7, game::kAuraSlots, "the attachment table has the recovered seven slots");
    checkInt(11, game::kAuraAttachPoints, "the attach set has the recovered eleven points");
    // The order IS the mapping: point i is the frame whose matrix lands at +0x38c + i*0x40.
    check(std::string(game::kAuraAttachBone[0]) == "Bip00", "point 0 is Bip00 (player+0x64c)");
    check(std::string(game::kAuraAttachBone[1]) == "Bip01_Head", "point 1 is Bip01_Head (0x650)");
    check(std::string(game::kAuraAttachBone[2]) == "Bip01_Spine", "point 2 is Bip01_Spine (0x654)");
    check(std::string(game::kAuraAttachBone[8]) == "Bip01_R_Hand", "point 8 is Bip01_R_Hand (0x668)");
    check(std::string(game::kAuraAttachBone[10]) == "Bip00_R_Foot", "point 10 is Bip00_R_Foot (0x674)");

    // The rule, through the function the product calls: ONE instance per RESOLVED attach
    // point. A rig that resolves none draws none — the -1 sentinel, not frame 0, which
    // would put eleven copies of the attachment on the root bone.
    const game::AuraAttach none = game::resolveAuraAttach(StubRig{});
    checkInt(0, none.found, "a rig with no attach point draws no aura instance");
    checkInt(-1, none.frame[0], "an unresolved point stays -1, never frame 0");
    const game::AuraAttach one = game::resolveAuraAttach(StubRig{{"obj1", "Bip01_Head"}});
    checkInt(1, one.found, "a rig with one attach point draws one instance");
    checkInt(1, one.frame[0], "the resolved point carries the rig's own frame index");

    std::vector<std::string> all{"obj1"};
    for (const char* bone : game::kAuraAttachBone) all.push_back(bone);
    const game::AuraAttach full = game::resolveAuraAttach(StubRig{all});
    checkInt(11, full.found, "a rig with all eleven draws eleven instances, not one");
    checkInt(1, full.frame[0], "instance 0 is table point 0's frame");
    checkInt(11, full.frame[10], "instance 10 is table point 10's frame");
}

void testInstallAuraTable(int argc, char** argv) {
    section("asset-backed: the shipped attachments, and the rigs they are drawn on");
    const fs::path install = findInstall(argc, argv);
    std::error_code ec;
    if (install.empty() || !fs::is_directory(install / "data", ec)) {
        skip("the install's attachment table and character rigs (no install found)");
        return;
    }
    // 1. FUN_00633ca0's seven models. Each is ONE model, so the instance count cannot come
    //    from the attachment; six ship one mesh and 03.X (the burning aura) three.
    const fs::path auraDir = install / "data" / "aura";
    int attachments = 0;
    for (int slot = 0; slot < game::kAuraSlots; ++slot) {
        fs::path file;
        for (const char* ext : {".x", ".X"}) {
            char name[16];
            std::snprintf(name, sizeof(name), "%02d%s", slot, ext);
            if (fs::exists(auraDir / name, ec)) {
                file = auraDir / name;
                break;
            }
        }
        if (file.empty()) {
            char want[24];
            std::snprintf(want, sizeof(want), "data/aura/%02d.x", slot);
            check(false, std::string(want) + " is installed");
            continue;
        }
        ++attachments;
        const xm::Model m = xm::loadFile(file.string());
        int skinned = 0;
        for (const xm::Mesh& mesh : m.meshes) skinned += mesh.skinned ? 1 : 0;
        const std::string label = file.filename().string();
        check(!m.meshes.empty(), label + " ships at least one mesh");
        checkInt(0, skinned, label + " is unskinned (the card is placed by one matrix)");
        checkInt(0, game::resolveAuraAttach(m).found,
                 label + " carries no attach point of its own (the rig supplies them)");
        std::printf("        %-6s %2zu frame(s) %zu mesh(es) %4d vert(s) %zu anim(s), %.3f s\n",
                    label.c_str(), m.frames.size(), m.meshes.size(), m.stats.vertices,
                    m.anims.size(),
                    m.anims.empty() ? 0.0
                                    : (double)(m.anims[0].duration /
                                               (m.ticksPerSecond > 0 ? m.ticksPerSecond : 1.f)));
    }
    checkInt(game::kAuraSlots, attachments, "the install ships all seven data/aura models");

    // 2. The rigs. The eleven draws land because every character model carries all eleven
    //    attach points; a rig with only some of them would draw FEWER than the original's
    //    eleven (the original copies from the null frame pointer instead of skipping), so a
    //    partial rig is what this enumeration exists to catch.
    int models = 0, complete = 0, none = 0, partial = 0;
    std::vector<std::string> partialNames;
    for (const fs::directory_entry& dirEntry : fs::directory_iterator(install / "data", ec)) {
        if (!dirEntry.is_directory(ec)) continue;
        for (const fs::directory_entry& f : fs::directory_iterator(dirEntry.path(), ec)) {
            const std::string name = f.path().filename().string();
            if (name.size() != 4 || name[2] != '.' || (name[3] != 'X' && name[3] != 'x')) continue;
            if (!std::isdigit((unsigned char)name[0]) || !std::isdigit((unsigned char)name[1]))
                continue;
            const xm::Model m = xm::loadFile(f.path().string());
            if (m.frames.empty()) continue;
            ++models;
            const int found = game::resolveAuraAttach(m).found;
            if (found == game::kAuraAttachPoints) ++complete;
            else if (found == 0) ++none;
            else {
                ++partial;
                partialNames.push_back(dirEntry.path().filename().string() + "/" + name);
            }
        }
    }
    std::printf("        %d model(s): %d carry all %d attach points, %d carry none\n", models,
                complete, game::kAuraAttachPoints, none);
    check(complete > 0, "the install ships character rigs with the full attach set");
    checkInt(0, partial, "no shipped rig is partially equipped (0 or 11 points, never between)");
    for (const std::string& name : partialNames) std::printf("        partial: %s\n", name.c_str());
}

}  // namespace

int main(int argc, char** argv) {
    std::puts("effect_catalog_test — issue #17 effect table, issue #33 attach points");
    testDescriptorHeader();
    testIdMappingAndLifetime();
    testInstallTable(argc, argv);
    testAuraAttachRule();
    testInstallAuraTable(argc, argv);
    std::printf("\n%d checks, %d failure(s)%s\n", checks, failures,
                skipped ? " (with skips)" : "");
    return failures == 0 ? 0 : 1;
}
