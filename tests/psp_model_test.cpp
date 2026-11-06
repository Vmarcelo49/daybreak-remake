// The PSP conversion, end to end: the player's own disc in, a fighter the port can draw and
// simulate out.
//
// This is the install-backed check for the extractor and the GMO -> .X conversion
// (docs/psp/MODEL-CONVERSION.md). It is deliberately two readers deep: the port draws what
// xm::loadMemory produces and the simulation reads what the vendored core's XObjectReader
// produces, from the same bytes (design decision D-3a), so both have to accept every file —
// and the 76 motion takes have to arrive at the same index in both.
//
// Skips with code 77 when there is no ISO to read: the disc is the player's, never the
// repository's.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "battle/core/actor_sampled_pose.hpp"
#include "battle/core/actor_skeleton.hpp"
#include "battle/core/actor_skin.hpp"
#include "battle/core/x_animation_keys.hpp"
#include "battle/core/x_objects.hpp"
#include "psp/psp_extract.h"
#include "psp/psp_manifest.h"
#include "psp/psp_model.h"
#include "xmodel.h"

namespace fs = std::filesystem;
namespace core = daybreak;

namespace {

int failures = 0;

void check(bool ok, const std::string& what) {
    if (!ok) {
        std::printf("  FAIL %s\n", what.c_str());
        ++failures;
    }
}

std::vector<std::uint8_t> readBytes(const fs::path& path) {
    std::vector<std::uint8_t> bytes;
    std::FILE* file = std::fopen(path.string().c_str(), "rb");
    if (!file) return bytes;
    std::fseek(file, 0, SEEK_END);
    const long size = std::ftell(file);
    std::fseek(file, 0, SEEK_SET);
    if (size > 0) {
        bytes.resize((std::size_t)size);
        if (std::fread(bytes.data(), 1, bytes.size(), file) != bytes.size()) bytes.clear();
    }
    std::fclose(file);
    return bytes;
}

bool finite(const std::array<float, 16>& m) {
    for (float value : m)
        if (!std::isfinite(value)) return false;
    return true;
}

// One converted model through both readers.
void checkModel(const std::string& label, const std::vector<std::uint8_t>& bytes, unsigned expectedBones,
                unsigned expectedSets) {
    std::printf("  %s: %zu bytes\n", label.c_str(), bytes.size());
    check(!bytes.empty(), label + ": model is empty");
    if (bytes.empty()) return;

    // -- the product's loader, i.e. what the renderer draws -------------------------------
    xm::Model model;
    try {
        model = xm::loadMemory(bytes.data(), bytes.size());
    } catch (const std::exception& failure) {
        check(false, label + ": xm::loadMemory threw " + failure.what());
        return;
    }
    check(model.frames.size() == expectedBones,
          label + ": " + std::to_string(model.frames.size()) + " xm frames, expected " +
              std::to_string(expectedBones));
    check(model.anims.size() == expectedSets,
          label + ": " + std::to_string(model.anims.size()) + " xm animation sets, expected " +
              std::to_string(expectedSets));
    check(model.meshes.size() >= 4,
          label + ": " + std::to_string(model.meshes.size()) + " xm meshes, expected the four materials");
    check(std::fabs(model.ticksPerSecond - 4800.f) < 0.5f, label + ": xm ticks per second is not 4800");
    for (const xm::Mesh& mesh : model.meshes) {
        check(mesh.skinned, label + ": mesh " + mesh.name + " is not skinned");
        check(!mesh.submeshes.empty(), label + ": mesh " + mesh.name + " has no draw");
        for (const xm::Material& material : mesh.materials)
            check(!material.texture.empty(), label + ": mesh " + mesh.name + " has an unnamed texture");
        for (const xm::Vertex& vertex : mesh.vertices)
            check(std::isfinite(vertex.pos.x) && std::isfinite(vertex.pos.y) &&
                      std::isfinite(vertex.pos.z),
                  label + ": non-finite vertex in " + mesh.name);
    }
    // Every set samples: the renderer's own path, at the start, middle and end of each take.
    std::vector<glm::mat4> world;
    for (std::size_t set = 0; set < model.anims.size(); ++set) {
        const xm::AnimSet& anim = model.anims[set];
        check(!anim.channels.empty(), label + ": set " + std::to_string(set) + " has no channels");
        for (float seconds : {0.f, anim.duration * 0.5f, anim.duration}) {
            model.evalPose(&anim, seconds, false, world);
            check(world.size() == model.frames.size(),
                  label + ": set " + std::to_string(set) + " posed " + std::to_string(world.size()) +
                      " frames, expected " + std::to_string(model.frames.size()));
            for (const glm::mat4& matrix : world)
                for (int column = 0; column < 4; ++column)
                    for (int row = 0; row < 4; ++row)
                        check(std::isfinite(matrix[column][row]),
                              label + ": non-finite pose in set " + std::to_string(set));
        }
    }

    // -- the core's reader, i.e. what the simulation and the hit records use ---------------
    std::vector<core::XObject> roots;
    core::ActorSkeleton skeleton;
    core::ActorSkin skin;
    try {
        roots = core::XObjectReader(bytes).read();
        skeleton = core::ActorSkeleton::decode(roots);
        skeleton.update();
        skin = core::ActorSkin::decode(roots, skeleton);
    } catch (const std::exception& failure) {
        check(false, label + ": core decode threw " + failure.what());
        return;
    }
    check(skeleton.bones.size() == expectedBones + 1,
          label + ": core has " + std::to_string(skeleton.bones.size()) +
              " bones (with the dummy root), expected " + std::to_string(expectedBones + 1));
    check(skin.meshes.size() == model.meshes.size(),
          label + ": core skin has " + std::to_string(skin.meshes.size()) + " meshes, the renderer " +
              std::to_string(model.meshes.size()));

    // The names the core looks up by hand, and the channel split that decides which bones an
    // upper-body-only bind moves (core/actor_sampled_pose.hpp).
    for (const char* name : {"Bip01_Spine", "Bip01_Neck", "Bip01_Head", "Bip01_L_Hand",
                             "Bip01_R_Hand", "Bip01_Prop1", "Bip01_Prop2"}) {
        const unsigned bone = skeleton.find(name);
        check(bone != 0, label + ": the core cannot find bone " + name);
        check(core::actor_animation_channel(name) == 1,
              label + ": " + name + " is not on the core's upper-body channel");
    }
    check(core::actor_animation_channel("Bip00_L_Thigh") == 0,
          label + ": the legs are not on the core's lower-body channel");

    // The core registers sets in reverse file order, so its index i must be PSP take i: the
    // converted file writes take N-1 first for exactly this reason.
    std::vector<const core::XObject*> sets;
    for (auto it = roots.rbegin(); it != roots.rend(); ++it)
        if (it->type == "AnimationSet" && !it->reference) sets.push_back(&*it);
    check(sets.size() == expectedSets,
          label + ": core sees " + std::to_string(sets.size()) + " animation sets, expected " +
              std::to_string(expectedSets));
    std::size_t sampled = 0;
    for (const core::XObject* set : sets) {
        const core::XAnimationKeys keys = core::read_x_animation_keys(*set);
        check(!keys.tracks.empty(), label + ": a core animation set has no tracks");
        for (const core::XMatrixTrack& track : keys.tracks) {
            check(skeleton.find(track.bone) != 0, label + ": track for unknown bone " + track.bone);
            for (std::uint32_t time : {track.keys.front().time, track.keys.back().time}) {
                const core::LegacyMatrix matrix = core::sample_actor_matrix(track, (double)time);
                check(finite(matrix), label + ": non-finite core sample in " + keys.name);
            }
            ++sampled;
        }
    }
    std::printf("    %zu animation sets, %zu tracks sampled, %zu core bones, %zu skin meshes\n",
                sets.size(), sampled, skeleton.bones.size(), skin.meshes.size());
}

}  // namespace

int main(int argc, char** argv) {
    const char* iso = std::getenv("DAYBREAK_PSP_ISO");
    if (!iso || !*iso) {
        std::puts("PSP_MODEL: skipped, DAYBREAK_PSP_ISO is not set");
        return 77;
    }
    if (!fs::exists(iso)) {
        std::printf("PSP_MODEL: skipped, DAYBREAK_PSP_ISO points at nothing (%s)\n", iso);
        return 77;
    }
    if (argc < 2) {
        std::puts("usage: psp_model_test <assets/psp/manifest.txt>");
        return 2;
    }

    // A scratch psp-data, not the one beside the executable: the test must not disturb an
    // extraction the player already has, and it has to be able to run twice.
    const fs::path root = fs::temp_directory_path() / "daybreak-psp-model-test";
    std::error_code ignored;
    fs::remove_all(root, ignored);
    fs::create_directories(root, ignored);

    psp::PspExtractOptions options;
    options.isoPath = iso;
    options.dataDir = root.string();
    psp::PspManifest manifest = psp::PspManifest::load(argv[1]);
    options.manifest = &manifest;
    psp::registerAllPspConverters();
    std::printf("PSP_MODEL: extracting %zu files into %s\n", manifest.entries.size(), root.c_str());
    psp::PspExtractReport report;
    try {
        report = psp::extractPsp(options, std::cout);
    } catch (const std::exception& failure) {
        std::printf("PSP_MODEL: FAIL extraction: %s\n", failure.what());
        return 1;
    }
    check(report.rawFiles.size() == manifest.entries.size(),
          "extraction wrote " + std::to_string(report.rawFiles.size()) + " of " +
              std::to_string(manifest.entries.size()) + " files");
    check(!report.converted.empty(), "no converter wrote anything");

    // Every fighter, every costume: the folder names are the core's (character_asset_files.hpp).
    for (const psp::PspFighter& fighter : psp::pspFighters()) {
        for (std::size_t costume = 0; costume < fighter.costumes.size(); ++costume) {
            std::string folder = "data/" + fighter.name;
            if (costume) folder += "_" + std::string(1, (char)('A' + costume));
            const std::vector<std::uint8_t> bytes = readBytes(root / folder / "00.X");
            check(!bytes.empty(), folder + "/00.X was not written");
            if (bytes.empty()) continue;
            const unsigned bones = fighter.name == "satoshi" ? 68u : 77u;
            checkModel(folder, bytes, bones, 76);
            // The textures the materials name have to exist beside the model, or the renderer
            // draws an untextured fighter (TextureCache resolves <name>.bmp to <name>.cnv).
            for (const auto& entry : fs::directory_iterator(root / folder)) {
                if (entry.path().extension() == ".cnv") check(entry.file_size() > 17, entry.path().string() + " is too small");
            }
        }
    }

    fs::remove_all(root, ignored);
    if (failures) {
        std::printf("PSP_MODEL: %d failure(s)\n", failures);
        return 1;
    }
    std::puts("PSP_MODEL: ok");
    return 0;
}
