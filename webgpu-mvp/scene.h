// scene.h — assembles the game's three model categories into one drawable scene.
//
// Single header, C++17. Needs xmodel.h and cnv.h (+ sjis_table.h) in the same folder.
//
//   #define XMODEL_IMPLEMENTATION
//   #define CNV_IMPLEMENTATION      // exactly one .cpp defines these
//   #define SCENE_IMPLEMENTATION
//   #include "scene.h"
//
// What it encodes, and where it comes from (all read out of DaybreakDX.exe):
//
//   STAGE — FUN_004011f0 loads `data/stageNN/%02d.x` for i = 0..7 (or `%02db.x` when
//   the config byte stage+0x2c is set), so a stage is at most EIGHT visible sub-models
//   plus one collision mesh per purpose. Nothing applies a transform or a scale: the
//   meshes are authored in world space, which is why drawStage() hands back models to
//   be drawn with an identity world matrix. env.dat carries fog (start/end/colour,
//   written straight into D3DRS_FOG* by FUN_00650a30) and the stage's bounds/spawn
//   points; it does not move anything.
//
//   CHARACTER — FUN_0064ab30 picks the directory from a costume index: 0..5 map to
//   `data/<char>/`, `_B`, `_C`, `_D`, `_E`, `_F`. The .X filename is not assumed: the
//   unsuffixed `data/<char>/<id>.dat` starts with a dword 4 and then a 260-byte model
//   name ("00.X"), and that name is what gets loaded from the costume directory. Rig
//   and animation naming is uniform across costumes (Bip00/Bip01_*, 137 animation
//   sets), so animation sets are portable between them.
//
//   WEAPON — a weapon hangs off the character's Bip01_Prop1 (primary) / Bip01_Prop2
//   frames, and the model name lives inside a .dat rather than being implied by the
//   directory: `data/bullet/001/000.dat` names "03.X", not "00.X". That indirection is
//   why loadWeapon() reads the name instead of guessing it.

#pragma once

#include <string>
#include <vector>

#include "xmodel.h"
#include "cnv.h"      // declarations; define CNV_IMPLEMENTATION in exactly one .cpp

namespace xm {

// env.dat, as consumed by FUN_00650a30: linear fog plus stage bounds/spawn points.
struct StageEnv {
    bool      present = false;
    bool      fogEnabled = false;
    float     fogStart = 0.f, fogEnd = 0.f;
    glm::vec3 fogColor{0.f};
    // [14]/[18]/[1C]/[20] land in stage+0x34..0x40 and [24..53] is four vec3s at
    // stage+0x44. Their meaning is not fully pinned down (bounds / spawn points), so
    // they are exposed rather than interpreted.
    int32_t   header[4] = {0, 0, 0, 0};
    glm::vec3 points[4];
};

// One loaded model plus the texture directory it resolves against.
struct SceneModel {
    Model        model;
    TextureCache textures{std::string()};
    std::string  source;        // path it came from, for logs
    std::string  role;          // "stage", "collision", "character", "weapon"
    int          index = -1;    // stage sub-model number (0..7), else -1
    // Collision meshes are loaded for geometry queries and framing, never drawn: the
    // original keeps them in their own slots (stage+0x20/0x24/0x28) and its render
    // loop only walks the eight visible sub-model slots.
    bool         drawable = true;

    // Set for weapons: the frame on the owning character this model rides. The item
    // table's per-weapon local offset (position + two rotations, FUN_00433eb0) is not
    // parsed, so a weapon sits at the attachment bone itself.
    int          attachFrame = -1;
};

struct Scene {
    std::vector<SceneModel> models;
    StageEnv                env;
    std::string             source;

    size_t totalMeshes() const {
        size_t n = 0;
        for (const auto& m : models) n += m.model.meshes.size();
        return n;
    }
    size_t totalVertices() const {
        size_t n = 0;
        for (const auto& m : models)
            for (const auto& mesh : m.model.meshes) n += mesh.vertices.size();
        return n;
    }
    // Bounds of the geometry that is actually drawn. A stage's visible set includes an
    // inverted sky dome far larger than the play area, so `playArea` (the collision
    // meshes) is the honest frame of reference when it is present.
    bool bounds(glm::vec3& lo, glm::vec3& hi, bool playArea) const {
        lo = glm::vec3(1e30f);
        hi = glm::vec3(-1e30f);
        bool any = false;
        for (const auto& m : models) {
            const bool want = playArea ? (m.role == "collision") : m.drawable;
            if (!want) continue;
            for (const auto& mesh : m.model.meshes)
                for (const auto& v : mesh.vertices) {
                    lo = glm::min(lo, v.pos);
                    hi = glm::max(hi, v.pos);
                    any = true;
                }
        }
        return any;
    }

    // Palette storage this scene needs, i.e. the size of the bone matrix buffer.
    size_t paletteSize() const {
        size_t n = 0;
        for (const auto& m : models) n += m.model.paletteSize();
        return n;
    }
    size_t totalSubmeshes() const {
        size_t n = 0;
        for (const auto& m : models)
            for (const auto& mesh : m.model.meshes) n += mesh.submeshes.size();
        return n;
    }
};

struct SceneOptions {
    bool resolveTextures = true;    // decode .cnv files next to each model
    bool includeCollision = false;  // collision.x / collision_camera.x / collision_tama.x
    bool variantB = false;          // the `%02db.x` detail set (config byte stage+0x2c)
    int  animIndex = -1;            // bind an animation set by index on characters
};

// Reads the model name out of a .dat header: dword 4, then a NUL-padded name field.
// Returns an empty string when the file does not have that shape.
std::string readDatModelName(const void* data, size_t size);

// data/<char>[_B.._F]. `costume` 0..5, matching FUN_0064ab30's jump table.
Scene loadCharacter(const std::string& baseDir, const std::string& character, int costume,
                    const SceneOptions& opt);

// data/stageNN: up to eight numbered sub-models, plus collision meshes on request.
Scene loadStage(const std::string& stageDir, const SceneOptions& opt);

// data/bullet/<weaponId>: the model named by the slot .dat, attached to the owning
// character's Bip01_Prop1. When no character is given the weapon is placed at the
// origin, which is still useful for inspecting the asset on its own.
Scene loadWeapon(const std::string& bulletDir, int slot, const Model* attachTo,
                 const SceneOptions& opt);

}  // namespace xm

// =======================================================================================
#ifdef SCENE_IMPLEMENTATION
#ifndef SCENE_IMPLEMENTATION_DONE
#define SCENE_IMPLEMENTATION_DONE

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>

namespace fs = std::filesystem;

namespace xm {
namespace detail {

inline bool readWholeFile(const std::string& path, std::vector<uint8_t>& out) {
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return false;
    std::fseek(f, 0, SEEK_END);
    long n = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    if (n <= 0) { std::fclose(f); return false; }
    out.resize((size_t)n);
    size_t got = std::fread(out.data(), 1, (size_t)n, f);
    std::fclose(f);
    out.resize(got);
    return got > 0;
}

inline int32_t rdI32(const uint8_t* p) {
    return (int32_t)((uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) |
                     ((uint32_t)p[3] << 24));
}

// One directory level of `dir + name`, with the separator the caller's path style
// happens to use. std::filesystem is not needed for the join itself.
inline std::string joinPath(const std::string& dir, const std::string& name) {
    if (dir.empty()) return name;
    const char last = dir.back();
    if (last == '/' || last == '\\') return dir + name;
    return dir + "/" + name;
}

// Appends a model, or reports why it could not be loaded. Failures are not fatal: a
// stage whose 07.X is absent (the common case) is still a valid stage.
inline void addModel(Scene& scene, const std::string& path, const std::string& role,
                     int index, const SceneOptions& opt, bool drawable = true) {
    std::error_code ec;
    if (!fs::exists(path, ec)) return;

    SceneModel sm;
    try {
        std::vector<uint8_t> bytes;
        if (!readWholeFile(path, bytes))
            throw std::runtime_error("cannot read " + path);
        sm.model = loadMemory(bytes.data(), bytes.size());
    } catch (const std::exception& e) {
        std::fprintf(stderr, "[scene] %s: %s\n", path.c_str(), e.what());
        return;
    }
    sm.source = path;
    sm.role = role;
    sm.index = index;
    sm.drawable = drawable;
    sm.textures = TextureCache(path.substr(0, path.find_last_of("/\\") + 1));
    scene.models.push_back(std::move(sm));
}

inline void readEnv(const std::string& path, StageEnv& env) {
    std::vector<uint8_t> b;
    if (!readWholeFile(path, b) || b.size() < 0x54) return;
    env.present = true;
    const int32_t fogStart = rdI32(b.data() + 0);
    const int32_t fogEnd = rdI32(b.data() + 4);
    // FUN_00650a30 writes fog colour as D3DRS_FOGCOLOR (0xAARRGGBB) from three ints
    // held as 0x00RRGGBB; D3D expects 8-bit channels.
    const int32_t r = rdI32(b.data() + 8), g = rdI32(b.data() + 12), bl = rdI32(b.data() + 16);
    env.fogEnabled = fogEnd > fogStart;
    env.fogStart = (float)fogStart;
    env.fogEnd = (float)fogEnd;
    env.fogColor = glm::vec3((float)(r & 0xFF), (float)(g & 0xFF), (float)(bl & 0xFF)) / 255.f;
    for (int i = 0; i < 4; ++i) env.header[i] = rdI32(b.data() + 0x14 + i * 4);
    for (int i = 0; i < 4; ++i) {
        const size_t off = 0x24 + (size_t)i * 12;
        env.points[i] = glm::vec3((float)rdI32(b.data() + off),
                                  (float)rdI32(b.data() + off + 4),
                                  (float)rdI32(b.data() + off + 8));
    }
}

}  // namespace detail

inline std::string readDatModelName(const void* data, size_t size) {
    if (!data || size < 264) return {};
    const uint8_t* d = (const uint8_t*)data;
    if (detail::rdI32(d) != 4) return {};                 // header dword is always 4
    const char* name = (const char*)d + 4;                // 260-byte NUL-padded field
    size_t len = 0;
    while (len < 260 && name[len]) ++len;
    return std::string(name, len);
}

inline Scene loadCharacter(const std::string& baseDir, const std::string& character, int costume,
                           const SceneOptions& opt) {
    Scene scene;
    // Costume index -> directory suffix, straight from the jump table at 0x41ef86.
    static const char* kSuffix[6] = {"", "_B", "_C", "_D", "_E", "_F"};
    if (costume < 0 || costume > 5) costume = 0;

    const std::string base = detail::joinPath(baseDir, character);
    const std::string dir = base + kSuffix[costume];
    scene.source = dir;

    // The .dat always lives in the unsuffixed directory and names the .X inside the
    // costume directory. Fall back to 00.X only when the .dat is missing, so a broken
    // .dat is visible in the log rather than silently substituted.
    std::string modelName;
    for (int id = 0; id < 10 && modelName.empty(); ++id) {
        char buf[32];
        std::snprintf(buf, sizeof buf, "%02d.dat", id);
        std::vector<uint8_t> bytes;
        if (detail::readWholeFile(detail::joinPath(base, buf), bytes))
            modelName = readDatModelName(bytes.data(), bytes.size());
    }
    if (modelName.empty()) {
        std::fprintf(stderr, "[scene] %s: no usable .dat model name, falling back to 00.X\n",
                     base.c_str());
        modelName = "00.X";
    }

    detail::addModel(scene, detail::joinPath(dir, modelName), "character", -1, opt);
    if (scene.models.empty()) {
        // Some costumes ship a differently numbered model; take whatever is there.
        std::error_code ec;
        for (const auto& e : fs::directory_iterator(dir, ec)) {
            std::string ext = e.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c) { return (char)std::tolower(c); });
            if (ext == ".x") {
                detail::addModel(scene, e.path().string(), "character", -1, opt);
                break;
            }
        }
    }
    return scene;
}

inline Scene loadStage(const std::string& stageDir, const SceneOptions& opt) {
    Scene scene;
    scene.source = stageDir;

    // FUN_004011f0: exactly eight slots, `%02d.x` or `%02db.x`.
    for (int i = 0; i < 8; ++i) {
        char buf[32];
        std::snprintf(buf, sizeof buf, opt.variantB ? "%02db.X" : "%02d.X", i);
        std::string path = detail::joinPath(stageDir, buf);
        std::error_code ec;
        if (!fs::exists(path, ec)) {
            std::snprintf(buf, sizeof buf, opt.variantB ? "%02db.x" : "%02d.x", i);
            path = detail::joinPath(stageDir, buf);
        }
        detail::addModel(scene, path, "stage", i, opt);
    }
    if (opt.includeCollision) {
        detail::addModel(scene, detail::joinPath(stageDir, "collision.x"), "collision", -1, opt, false);
        detail::addModel(scene, detail::joinPath(stageDir, "collision.X"), "collision", -1, opt, false);
        detail::addModel(scene, detail::joinPath(stageDir, "collision_camera.X"), "collision", -1, opt, false);
        detail::addModel(scene, detail::joinPath(stageDir, "collision_tama.x"), "collision", -1, opt, false);
    }
    detail::readEnv(detail::joinPath(stageDir, "env.dat"), scene.env);
    return scene;
}

inline Scene loadWeapon(const std::string& bulletDir, int slot, const Model* attachTo,
                        const SceneOptions& opt) {
    Scene scene;
    scene.source = bulletDir;

    // A direct .X path is accepted too: weapons also ship as data/item/NN.X, and the
    // per-character table that picks between them is not parsed.
    std::error_code fec;
    if (fs::is_regular_file(bulletDir, fec)) {
        const size_t slash = bulletDir.find_last_of("/\\");
        const std::string dir = (slash == std::string::npos) ? std::string()
                                                             : bulletDir.substr(0, slash + 1);
        detail::addModel(scene, bulletDir, "weapon", -1, opt);
        for (SceneModel& sm : scene.models) {
            if (!attachTo) break;
            int frame = attachTo->findFrame("Bip01_Prop1");
            if (frame < 0) frame = attachTo->findFrame("Bip01_Prop2");
            sm.attachFrame = frame;
            if (frame < 0)
                std::fprintf(stderr, "[scene] %s: no Bip01_Prop1/Prop2 in the character rig\n",
                             bulletDir.c_str());
        }
        (void)dir;
        return scene;
    }

    // FUN_005f80c0 builds `data/bullet/%03d/%03d.dat` with the inner file number being
    // bulletId / 10, and uses only the group whose index is bulletId % 10. For a single
    // slot request, reading `%03d.dat` for that slot is the same thing.
    char name[32];
    std::snprintf(name, sizeof name, "%03d.dat", slot);
    std::vector<uint8_t> bytes;
    std::string modelName;
    if (detail::readWholeFile(detail::joinPath(bulletDir, name), bytes))
        modelName = readDatModelName(bytes.data(), bytes.size());
    if (modelName.empty()) {
        std::error_code ec;
        for (const auto& e : fs::directory_iterator(bulletDir, ec)) {
            std::string ext = e.path().extension().string();
            std::transform(ext.begin(), ext.end(), ext.begin(),
                           [](unsigned char c) { return (char)std::tolower(c); });
            if (ext == ".x") { modelName = e.path().filename().string(); break; }
        }
    }
    if (modelName.empty()) {
        std::fprintf(stderr, "[scene] %s: no model named by slot %d\n", bulletDir.c_str(), slot);
        return scene;
    }

    detail::addModel(scene, detail::joinPath(bulletDir, modelName), "weapon", -1, opt);

    // Attach to Bip01_Prop1 (primary) or Bip01_Prop2, the frames FUN_00433eb0 resolves.
    // The caller supplies the owning character's model so the frame index is resolved
    // against the right rig; the renderer then places the weapon with that frame's
    // world matrix on the frame it draws.
    for (SceneModel& sm : scene.models) {
        if (!attachTo) break;
        int frame = attachTo->findFrame("Bip01_Prop1");
        if (frame < 0) frame = attachTo->findFrame("Bip01_Prop2");
        sm.attachFrame = frame;
        if (frame < 0)
            std::fprintf(stderr, "[scene] %s: no Bip01_Prop1/Prop2 in the character rig\n",
                         modelName.c_str());
    }
    return scene;
}

inline void resolveSceneTextures(Scene& scene) {
    int resolved = 0, missed = 0;
    for (SceneModel& sm : scene.models)
        for (Mesh& mesh : sm.model.meshes)
            for (Material& mat : mesh.materials) {
                if (mat.texture.empty()) continue;
                if (sm.textures.get(mat.texture)) ++resolved; else ++missed;
            }
    std::printf("[scene] %s: %zu model(s), %zu meshes, %zu vertices, textures %d resolved / %d missed\n",
                scene.source.c_str(), scene.models.size(), scene.totalMeshes(),
                scene.totalVertices(), resolved, missed);
}

}  // namespace xm

#endif  // SCENE_IMPLEMENTATION_DONE
#endif  // SCENE_IMPLEMENTATION
