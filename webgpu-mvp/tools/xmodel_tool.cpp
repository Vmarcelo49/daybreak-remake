// xmodel_tool — CLI for the xmodel loader.
//
//   xmodel_tool stats <file.x>...            load and print per-file statistics
//   xmodel_tool dump-text <in.x> <out.txt>   write the text form used for binary input
//   xmodel_tool pose <file.x> [animIndex]    sample an animation and print a fingerprint
//   xmodel_tool corpus <path-list-file>      load every listed file, report failures
//   xmodel_tool palette <file.x>             print palette sizes per mesh
//
// Build: g++ -std=c++17 -O2 tools/xmodel_tool.cpp -o build/xmodel_tool

#define XMODEL_IMPLEMENTATION
#define CNV_IMPLEMENTATION
#define SCENE_IMPLEMENTATION
#include "../scene.h"

#include <cstdio>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

int cmdStats(const std::vector<std::string>& files) {
    int failures = 0;
    double totalConvert = 0, totalParse = 0;
    for (const std::string& f : files) {
        xm::LoadOptions opt;
        try {
            xm::Model m = xm::loadFile(f, opt);
            std::printf("%-52s %s\n", f.c_str(), m.stats.toString().c_str());
            totalConvert += m.stats.convertMs;
            totalParse += m.stats.parseMs;

            // Invariants that must hold for every shipped asset.
            for (const xm::Mesh& mesh : m.meshes) {
                if (mesh.skinned) {
                    for (const xm::Bone& b : mesh.bones) {
                        if (b.frame < 0)
                            std::printf("    ! bone '%s' has no frame\n", b.name.c_str());
                    }
                    if (mesh.skinHeader.present && mesh.bones.size() > (size_t)mesh.skinHeader.bones)
                        std::printf("    ! %zu bones exceeds XSkinMeshHeader (%d)\n",
                                    mesh.bones.size(), mesh.skinHeader.bones);
                    for (const xm::Vertex& v : mesh.vertices) {
                        for (int k = 0; k < 4; ++k)
                            if (v.weights[k] > 0.f && v.bones[k] >= mesh.bones.size())
                                std::printf("    ! vertex bone index out of range\n");
                    }
                }
                for (const xm::Submesh& s : mesh.submeshes) {
                    if ((size_t)s.firstIndex + s.indexCount > mesh.indices.size())
                        std::printf("    ! submesh index range out of bounds\n");
                }
                for (uint32_t i : mesh.indices)
                    if (i >= mesh.vertices.size()) std::printf("    ! index out of range\n");
            }
            for (const xm::AnimSet& a : m.anims)
                for (const xm::Channel& c : a.channels)
                    if (c.frame < 0 || (size_t)c.frame >= m.frames.size())
                        std::printf("    ! animation channel frame out of range\n");
        } catch (const std::exception& e) {
            std::printf("%-52s FAILED: %s\n", f.c_str(), e.what());
            ++failures;
        }
    }
    std::printf("\n%d file(s), %d failure(s); binary->text %.0f ms, text->model %.0f ms\n",
                (int)files.size(), failures, totalConvert, totalParse);
    return failures ? 1 : 0;
}

int cmdDumpText(const std::string& in, const std::string& out) {
    xm::LoadOptions opt;
    std::string text;
    opt.convertedTextOut = &text;
    try {
        xm::Model m = xm::loadFile(in, opt);
        if (text.empty()) {
            std::ifstream f(in, std::ios::binary);
            text.assign(std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>());
        }
        std::ofstream o(out, std::ios::binary);
        o.write(text.data(), (std::streamsize)text.size());
        std::printf("wrote %s (%zu bytes) from %s [%s]\n", out.c_str(), text.size(),
                    in.c_str(), m.stats.encoding.c_str());
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAILED: %s\n", e.what());
        return 1;
    }
}

int cmdPose(const std::string& file, int animIndex) {
    try {
        xm::Model m = xm::loadFile(file);
        if (m.anims.empty()) { std::printf("no animations\n"); return 0; }
        if (animIndex < 0 || (size_t)animIndex >= m.anims.size()) animIndex = 0;
        const xm::AnimSet& a = m.anims[(size_t)animIndex];
        std::printf("model %s | anim[%d] '%s' duration %.1f ticks @ %.0f tps (%.3f s) | "
                    "%zu frames, %zu channels\n",
                    file.c_str(), animIndex, a.name.c_str(), a.duration, m.ticksPerSecond,
                    a.duration / m.ticksPerSecond, m.frames.size(), a.channels.size());

        std::vector<glm::mat4> world;
        for (float t : {0.0f, 0.25f, 0.5f, 1.0f}) {
            m.evalPose(&a, t, true, world);
            double sum = 0;
            bool finite = true;
            for (const glm::mat4& w : world)
                for (int c = 0; c < 4; ++c)
                    for (int r = 0; r < 4; ++r) {
                        float v = w[c][r];
                        if (!std::isfinite(v)) finite = false;
                        sum += v * (1.0 + 0.001 * (c * 4 + r));
                    }
            std::printf("  t=%.2fs  frames=%zu  finite=%s  fingerprint=%.6f\n",
                        t, world.size(), finite ? "yes" : "NO", sum);
        }

        // Palette sanity: skinned meshes must produce one matrix per bone.
        std::vector<glm::mat4> pal;
        m.evalPose(&a, 0.0f, true, world);
        for (const xm::Mesh& mesh : m.meshes) {
            m.buildPalette(mesh, world, pal);
            if (mesh.skinned && pal.size() != mesh.bones.size())
                std::printf("  ! palette %zu != bones %zu for mesh '%s'\n",
                            pal.size(), mesh.bones.size(), mesh.name.c_str());
        }
        std::printf("  total palette matrices: %zu\n", m.paletteSize());
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAILED: %s\n", e.what());
        return 1;
    }
}

// Lists animation sets with their duration. The game binds 137+ sets per character
// by name, so this is the quickest way to see what a model actually ships with.
int cmdAnims(const std::string& file) {
    try {
        xm::Model m = xm::loadFile(file);
        std::printf("%s: %zu animation sets @ %.0f ticks/s\n", file.c_str(), m.anims.size(),
                    m.ticksPerSecond);
        for (size_t i = 0; i < m.anims.size(); ++i) {
            const xm::AnimSet& a = m.anims[i];
            std::printf("  [%3zu] %-28s %9.0f ticks  %7.3f s  %3zu channels\n",
                        i, a.name.c_str(), a.duration, a.duration / m.ticksPerSecond,
                        a.channels.size());
        }
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAILED: %s\n", e.what());
        return 1;
    }
}

// Camera-independent winding check: compare each triangle's geometric normal (from
// its vertex order) against the normals stored in the file. Artists author the stored
// normals outward, so whichever cross-product order agrees with them is the authored
// front face — no camera, no GPU, no guessing from a single view.
// Applies the bind-pose palette on the CPU. A skinned character must come out upright
// (head at high +Y) and the same size as its raw bind-space vertices; if it comes out
// inverted here, the fault is in the frame/palette path, not in the projection.
int cmdSkin(const std::string& file, int animIndex) {
    try {
        xm::Model m = xm::loadFile(file);
        const xm::AnimSet* anim = nullptr;
        if (animIndex >= 0 && (size_t)animIndex < m.anims.size()) anim = &m.anims[(size_t)animIndex];
        std::vector<glm::mat4> world, pal;
        m.evalPose(anim, 0.f, false, world);
        std::printf("%s  (%s)\n", file.c_str(), anim ? anim->name.c_str() : "bind pose");
        for (const xm::Mesh& mesh : m.meshes) {
            glm::vec3 rawLo(1e30f), rawHi(-1e30f), skLo(1e30f), skHi(-1e30f);
            for (const xm::Vertex& v : mesh.vertices) {
                rawLo = glm::min(rawLo, v.pos); rawHi = glm::max(rawHi, v.pos);
            }
            m.buildPalette(mesh, world, pal);
            for (const xm::Vertex& v : mesh.vertices) {
                glm::vec4 p(v.pos, 1.f);
                glm::vec4 acc(0.f);
                for (int k = 0; k < 4; ++k) {
                    if (v.weights[k] <= 0.f) continue;
                    size_t bi = v.bones[k];
                    if (bi >= pal.size()) continue;
                    acc += v.weights[k] * (pal[bi] * p);
                }
                if (glm::length(glm::vec3(acc)) > 0.f) {
                    skLo = glm::min(skLo, glm::vec3(acc));
                    skHi = glm::max(skHi, glm::vec3(acc));
                }
            }
            std::printf("  %-16s skinned=%s\n", mesh.name.c_str(), mesh.skinned ? "yes" : "no");
            std::printf("      raw     [%8.2f %8.2f %8.2f] .. [%8.2f %8.2f %8.2f]\n",
                        rawLo.x, rawLo.y, rawLo.z, rawHi.x, rawHi.y, rawHi.z);
            std::printf("      skinned [%8.2f %8.2f %8.2f] .. [%8.2f %8.2f %8.2f]\n",
                        skLo.x, skLo.y, skLo.z, skHi.x, skHi.y, skHi.z);
        }
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAILED: %s\n", e.what());
        return 1;
    }
}

int cmdWinding(const std::vector<std::string>& files) {
    long long agreeLH = 0, agreeRH = 0, total = 0, meshes = 0, unskinned = 0;
    for (const std::string& f : files) {
        try {
            xm::Model m = xm::loadFile(f);
            for (const xm::Mesh& mesh : m.meshes) {
                if (mesh.indices.size() < 3) continue;
                ++meshes;
                if (!mesh.skinned) ++unskinned;
                for (size_t t = 0; t + 2 < mesh.indices.size(); t += 3) {
                    const xm::Vertex& a = mesh.vertices[mesh.indices[t]];
                    const xm::Vertex& b = mesh.vertices[mesh.indices[t + 1]];
                    const xm::Vertex& c = mesh.vertices[mesh.indices[t + 2]];
                    glm::vec3 avgN = a.normal + b.normal + c.normal;
                    if (glm::dot(avgN, avgN) <= 0.f) continue;
                    // LH/clockwise convention (what auto-normals assume):
                    glm::vec3 nLH = glm::cross(c.pos - a.pos, b.pos - a.pos);
                    // RH/counter-clockwise convention:
                    glm::vec3 nRH = glm::cross(b.pos - a.pos, c.pos - a.pos);
                    if (glm::dot(nLH, avgN) > 0.f) ++agreeLH;
                    if (glm::dot(nRH, avgN) > 0.f) ++agreeRH;
                    ++total;
                }
            }
        } catch (const std::exception&) { /* reported by the stats pass */ }
    }
    if (!total) { std::printf("no triangles analysed\n"); return 1; }
    std::printf("triangles analysed: %lld over %lld meshes (%lld unskinned)\n", total, meshes, unskinned);
    std::printf("  stored normals agree with LH/clockwise order : %lld (%.2f%%)\n",
                agreeLH, 100.0 * (double)agreeLH / (double)total);
    std::printf("  stored normals agree with RH/counter-clock  : %lld (%.2f%%)\n",
                agreeRH, 100.0 * (double)agreeRH / (double)total);
    return 0;
}

int cmdPalette(const std::string& file, const std::string& only) {
    try {
        xm::Model m = xm::loadFile(file);
        if (!only.empty() && m.findMesh(only) < 0) {
            std::fprintf(stderr, "no mesh named '%s' (have %zu meshes)\n", only.c_str(),
                         m.meshes.size());
            return 1;
        }
        for (const xm::Mesh& mesh : m.meshes) {
            if (!only.empty() && mesh.name != only) continue;
            std::printf("mesh '%-24s' frame=%-4d skinned=%-3s bones=%-4zu verts=%-6zu tris=%-6zu "
                        "submeshes=%-3zu colours=%s\n",
                        mesh.name.c_str(), mesh.frame, mesh.skinned ? "yes" : "no",
                        mesh.bones.size(), mesh.vertices.size(), mesh.indices.size() / 3,
                        mesh.submeshes.size(), mesh.hasVertexColors ? "yes" : "no");
        }
        return 0;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAILED: %s\n", e.what());
        return 1;
    }
}

int cmdCorpus(const std::string& listFile) {
    std::ifstream in(listFile);
    if (!in) { std::fprintf(stderr, "cannot open %s\n", listFile.c_str()); return 2; }
    std::vector<std::string> files;
    std::string line;
    while (std::getline(in, line)) {
        while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
        if (!line.empty()) files.push_back(line);
    }
    return cmdStats(files);
}

// Assembles the three model categories the game ships and reports what came out.
// This is the CPU half of "can we render them all": if a scene assembles here with
// textures resolved, the GPU tool has everything it needs.
int cmdScene(const std::vector<std::string>& a) {
    if (a.size() < 2) {
        std::fprintf(stderr,
            "usage:\n"
            "  xmodel_tool scene stage <stageDir> [--b] [--collision]\n"
            "  xmodel_tool scene character <baseDir> <name> <costume 0-5>\n"
            "  xmodel_tool scene weapon <bulletDir> <slot>\n");
        return 2;
    }
    xm::SceneOptions opt;
    for (const std::string& f : a) {
        if (f == "--b") opt.variantB = true;
        if (f == "--collision") opt.includeCollision = true;
    }
    xm::Scene scene;
    if (a[0] == "stage") {
        scene = xm::loadStage(a[1], opt);
        if (scene.env.present) {
            std::printf("  env.dat: fog %.0f..%.0f rgb(%.2f %.2f %.2f) %s | header %d %d %d %d\n",
                        scene.env.fogStart, scene.env.fogEnd, scene.env.fogColor.r,
                        scene.env.fogColor.g, scene.env.fogColor.b,
                        scene.env.fogEnabled ? "enabled" : "disabled",
                        scene.env.header[0], scene.env.header[1], scene.env.header[2],
                        scene.env.header[3]);
        } else {
            std::printf("  env.dat: absent\n");
        }
    } else if (a[0] == "character") {
        scene = xm::loadCharacter(a[1], a[2], a.size() > 3 ? std::atoi(a[3].c_str()) : 0, opt);
    } else if (a[0] == "weapon") {
        scene = xm::loadWeapon(a[1], a.size() > 2 ? std::atoi(a[2].c_str()) : 0, nullptr, opt);
    } else {
        std::fprintf(stderr, "unknown scene kind '%s'\n", a[0].c_str());
        return 2;
    }

    for (const xm::SceneModel& sm : scene.models) {
        int skinned = 0, coloured = 0;
        for (const xm::Mesh& mesh : sm.model.meshes) {
            if (mesh.skinned) ++skinned;
            if (mesh.hasVertexColors) ++coloured;
        }
        std::printf("  [%-9s] %-42s meshes=%-3zu skinned=%-2d colour=%-2d anims=%-4zu frames=%zu%s\n",
                    sm.role.c_str(), sm.source.c_str(), sm.model.meshes.size(), skinned, coloured,
                    sm.model.anims.size(), sm.model.frames.size(),
                    sm.attachFrame >= 0 ? " attached" : "");
    }
    if (opt.resolveTextures) xm::resolveSceneTextures(scene);
    std::printf("  totals: %zu models, %zu meshes, %zu submeshes, %zu vertices\n",
                scene.models.size(), scene.totalMeshes(), scene.totalSubmeshes(),
                scene.totalVertices());
    return scene.models.empty() ? 1 : 0;
}

// Walks a tree and assembles every stage, character/costume and weapon directory it
// finds. One pass over the shipped data is the cheapest way to see whether any
// category has a case the loader cannot handle.
int cmdSceneAll(const std::string& root) {
    xm::SceneOptions opt;
    int stages = 0, chars = 0, weapons = 0, failed = 0;
    size_t meshes = 0, verts = 0;
    std::vector<std::string> problems;

    std::error_code ec;
    for (const auto& e : fs::directory_iterator(root, ec)) {
        if (!e.is_directory()) continue;
        const std::string name = e.path().filename().string();
        if (name.rfind("stage", 0) == 0) {
            xm::Scene s = xm::loadStage(e.path().string(), opt);
            if (s.models.empty()) { ++failed; problems.push_back("stage " + name + ": no models"); }
            else { ++stages; meshes += s.totalMeshes(); verts += s.totalVertices(); }
        } else if (name.rfind("bullet", 0) == 0) {
            for (const auto& w : fs::directory_iterator(e.path(), ec)) {
                if (!w.is_directory()) continue;
                xm::Scene s = xm::loadWeapon(w.path().string(), 0, nullptr, opt);
                if (s.models.empty()) {
                    ++failed;
                    problems.push_back("weapon " + w.path().filename().string() + ": no model");
                } else { ++weapons; meshes += s.totalMeshes(); verts += s.totalVertices(); }
            }
        }
    }
    // Characters: a directory holding a NN.dat referencing a model, plus costume dirs.
    for (const auto& e : fs::directory_iterator(root, ec)) {
        if (!e.is_directory()) continue;
        const std::string name = e.path().filename().string();
        if (name.rfind("stage", 0) == 0 || name.rfind("bullet", 0) == 0) continue;
        // A character directory is identified by a .dat that actually names a model —
        // other directories ship .dat files too (data/scenario is scripts, not a rig).
        bool namesModel = false;
        for (const auto& f : fs::directory_iterator(e.path(), ec)) {
            if (f.path().extension() != ".dat") continue;
            std::vector<uint8_t> bytes;
            std::FILE* fh = std::fopen(f.path().string().c_str(), "rb");
            if (!fh) continue;
            std::fseek(fh, 0, SEEK_END);
            long n = std::ftell(fh);
            std::fseek(fh, 0, SEEK_SET);
            if (n > 0) {
                bytes.resize((size_t)n);
                size_t got = std::fread(bytes.data(), 1, bytes.size(), fh);
                bytes.resize(got);
            }
            std::fclose(fh);
            if (!xm::readDatModelName(bytes.data(), bytes.size()).empty()) { namesModel = true; break; }
        }
        if (!namesModel) continue;
        for (int costume = 0; costume < 6; ++costume) {
            xm::Scene s = xm::loadCharacter(root, name, costume, opt);
            if (s.models.empty()) {
                if (costume == 0) { ++failed; problems.push_back("character " + name + ": no model"); }
                continue;   // most characters only ship a few costumes
            }
            ++chars; meshes += s.totalMeshes(); verts += s.totalVertices();
        }
    }
    std::printf("scenes assembled: %d stages, %d character/costumes, %d weapons\n",
                stages, chars, weapons);
    std::printf("  %zu meshes, %zu vertices total\n", meshes, verts);
    std::printf("  failures: %d\n", failed);
    for (const std::string& p : problems) std::printf("      %s\n", p.c_str());
    return failed ? 1 : 0;
}

// The original game's frame rate is whatever the monitor does (its cap is the refresh
// rate), so animation must be a pure function of elapsed time: stepping 1 s as one big
// frame, as 60 frames, or as 144 frames has to land on the same pose. This checks that
// by advancing a Controller three different ways and comparing the resulting matrices.
int cmdDtCheck(const std::string& file, int animIndex) {
    try {
        xm::Model m = xm::loadFile(file);
        if (m.anims.empty()) { std::printf("%s: no animations\n", file.c_str()); return 0; }
        if (animIndex < 0 || (size_t)animIndex >= m.anims.size()) animIndex = 0;

        auto poseAfter = [&](double totalSeconds, int steps) {
            xm::Controller c;
            c.bind(&m);
            c.setAnimation(animIndex, true);
            for (int i = 0; i < steps; ++i)
                c.advanceTime((float)(totalSeconds / steps));
            std::vector<glm::mat4> world;
            c.evalWorld(world);
            return world;
        };

        const std::vector<glm::mat4> one = poseAfter(1.0, 1);
        struct Case { const char* name; int steps; };
        const Case cases[] = {{"60 Hz", 60}, {"120 Hz", 120}, {"144 Hz", 144}, {"30 Hz", 30}};
        std::printf("%s anim[%d] '%s': pose after 1.0 s vs a single 1.0 s step\n",
                    file.c_str(), animIndex, m.anims[(size_t)animIndex].name.c_str());
        double worstOverall = 0.0;
        for (const Case& c : cases) {
            const std::vector<glm::mat4> many = poseAfter(1.0, c.steps);
            double worst = 0.0;
            for (size_t i = 0; i < one.size() && i < many.size(); ++i)
                for (int col = 0; col < 4; ++col)
                    for (int row = 0; row < 4; ++row)
                        worst = std::max(worst, (double)std::fabs(one[i][col][row] - many[i][col][row]));
            worstOverall = std::max(worstOverall, worst);
            std::printf("  %-7s %4d steps: max matrix delta %.3e %s\n", c.name, c.steps, worst,
                        worst < 1e-4 ? "OK" : "FRAME-RATE DEPENDENT");
        }
        // A second run of the same schedule must be bit-identical: no hidden state.
        const std::vector<glm::mat4> again = poseAfter(1.0, 60);
        double repeatDelta = 0.0;
        for (size_t i = 0; i < again.size(); ++i)
            for (int col = 0; col < 4; ++col)
                for (int row = 0; row < 4; ++row)
                    repeatDelta = std::max(repeatDelta,
                        (double)std::fabs(again[i][col][row] - poseAfter(1.0, 60)[i][col][row]));
        std::printf("  repeatability: max delta %.3e %s\n", repeatDelta,
                    repeatDelta == 0.0 ? "(bit-identical)" : "");
        return worstOverall < 1e-4 ? 0 : 1;
    } catch (const std::exception& e) {
        std::fprintf(stderr, "FAILED: %s\n", e.what());
        return 1;
    }
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr,
            "usage:\n"
            "  xmodel_tool stats <file.x>...\n"
            "  xmodel_tool dump-text <in.x> <out.txt>\n"
            "  xmodel_tool pose <file.x> [animIndex]\n"
            "  xmodel_tool palette <file.x> [meshName]\n"
            "  xmodel_tool anims <file.x>\n"
            "  xmodel_tool winding <file.x>...\n"
            "  xmodel_tool skin <file.x> [animIndex]\n"
            "  xmodel_tool corpus <path-list-file>\n"
            "  xmodel_tool scene <stage|character|weapon> ...\n"
            "  xmodel_tool sceneall <assetRoot>\n"
            "  xmodel_tool dtcheck <file.x> [animIndex]\n");
        return 2;
    }
    std::string cmd = argv[1];
    std::vector<std::string> rest;
    for (int i = 2; i < argc; ++i) rest.push_back(argv[i]);

    if (cmd == "corpus" && !rest.empty()) return cmdCorpus(rest[0]);
    if (cmd == "scene" && !rest.empty()) return cmdScene(rest);
    if (cmd == "sceneall" && !rest.empty()) return cmdSceneAll(rest[0]);
    if (cmd == "dtcheck" && !rest.empty())
        return cmdDtCheck(rest[0], rest.size() > 1 ? std::atoi(rest[1].c_str()) : 0);
    if (cmd == "dump-text" && rest.size() >= 2) return cmdDumpText(rest[0], rest[1]);
    if (cmd == "pose" && !rest.empty())
        return cmdPose(rest[0], rest.size() > 1 ? std::atoi(rest[1].c_str()) : 0);
    if (cmd == "palette" && !rest.empty())
        return cmdPalette(rest[0], rest.size() > 1 ? rest[1] : std::string());
    if (cmd == "winding" && !rest.empty()) return cmdWinding(rest);
    if (cmd == "skin" && !rest.empty())
        return cmdSkin(rest[0], rest.size() > 1 ? std::atoi(rest[1].c_str()) : -1);
    if (cmd == "anims" && !rest.empty()) return cmdAnims(rest[0]);
    if (cmd == "stats" && !rest.empty()) return cmdStats(rest);

    std::fprintf(stderr, "bad arguments\n");
    return 2;
}
