// psp/psp_model.cpp — the GMO -> .X conversion for the three PSP-only fighters.
#include "psp/psp_model.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <map>
#include <ostream>
#include <set>
#include <stdexcept>

#include "psp/gim.h"
#include "psp/psp_extract.h"
#include "psp/xfile.h"

namespace fs = std::filesystem;

namespace psp {
namespace {

// The .X tick base the PC models use; the core reads it from the file (AnimTicksPerSecond)
// and divides every key time by it, so a 30 fps motion is stored as frame * (4800 / 30).
constexpr std::uint32_t kTicksPerSecond = 4800;

using Matrix = std::array<float, 16>;

Matrix multiplyMatrix(const Matrix& a, const Matrix& b) {
    Matrix out{};
    for (unsigned row = 0; row < 4; ++row)
        for (unsigned column = 0; column < 4; ++column) {
            float sum = 0.f;
            for (unsigned k = 0; k < 4; ++k) sum += a[row * 4 + k] * b[k * 4 + column];
            out[row * 4 + column] = sum;
        }
    return out;
}

// The root frame carries the two port rules that have to apply to the whole rig: the
// fighter's draw scale, and a half turn about Y.
//
// The half turn is measured, not assumed: with the model viewer's --camera=front (the eye
// on -Z, the side the PC rigs face) a PC fighter looks at the camera and a converted PSP
// one shows its back, and the PSP bind data agrees — the face mesh of chr190.gmo sits at
// z +9.9 with a mean normal of +0.9 in z, so the PSP version is authored facing +Z while
// every PC rig faces -Z. Rotating the root keeps model and bone-anchored hit geometry
// together, exactly as the scale does.
Matrix rootFixMatrix(float scale) {
    Matrix m{};
    m[0] = -scale;
    m[5] = scale;
    m[10] = -scale;
    m[15] = 1.f;
    return m;
}

// Row-vector TRS: rotation in the 3x3 block, translation in the last row. This is the GMO's
// own layout and the one the core's quaternion_matrix_scalar24 builds, so the same numbers
// survive both readers without a transpose anywhere. `rootFixMatrix` is where a scale and a
// turn are applied, because those belong to the whole rig and not to one bone.
Matrix composeLocal(const std::array<float, 3>& translation, const std::array<float, 4>& rotation) {
    const float x = rotation[0], y = rotation[1], z = rotation[2], w = rotation[3];
    const float xx = 2.f * x * x, yy = 2.f * y * y, zz = 2.f * z * z;
    const float xy = 2.f * x * y, xz = 2.f * x * z, yz = 2.f * y * z;
    const float wx = 2.f * w * x, wy = 2.f * w * y, wz = 2.f * w * z;
    Matrix m{};
    m[0] = 1.f - yy - zz;
    m[1] = xy + wz;
    m[2] = xz - wy;
    m[4] = xy - wz;
    m[5] = 1.f - xx - zz;
    m[6] = yz + wx;
    m[8] = xz + wy;
    m[9] = yz - wx;
    m[10] = 1.f - xx - yy;
    m[12] = translation[0];
    m[13] = translation[1];
    m[14] = translation[2];
    m[15] = 1.f;
    return m;
}

// ---------------------------------------------------------------------------------------
// Geometry, grouped so one material is one .X Mesh (one draw call), which is how the
// renderer's submesh list wants it.
// ---------------------------------------------------------------------------------------
struct GroupVertex {
    std::array<float, 3>                  position{};
    std::array<float, 3>                  normal{};
    std::array<float, 2>                  uv{};
    std::vector<std::pair<unsigned, float>> influences;   // bone index, weight
};

struct Group {
    unsigned                             material = 0;
    std::string                          meshName;
    std::vector<GroupVertex>             vertices;
    std::vector<std::array<std::uint32_t, 3>> triangles;
};

class Builder {
public:
    Builder(const GmoModel& rig, const GmoModel& costume, float scale)
        : rig_(rig), costume_(costume), scale_(scale) {
        if (rig_.bones.size() != costume_.bones.size())
            throw std::runtime_error("psp model: rig and costume have " +
                                     std::to_string(rig_.bones.size()) + " and " +
                                     std::to_string(costume_.bones.size()) + " bones");
        if (rig_.meshBoneIndex != costume_.meshBoneIndex)
            throw std::runtime_error("psp model: rig and costume disagree on the mesh bone");
        for (std::size_t i = 0; i < costume_.bones.size(); ++i)
            if (costume_.bones[i].parent != rig_.bones[i].parent)
                throw std::runtime_error("psp model: rig and costume hierarchies differ at bone " +
                                         std::to_string(i));
        if (costume_.meshBoneIndex >= costume_.bones.size())
            throw std::runtime_error("psp model: mesh bone out of range");
        names_.resize(costume_.bones.size());
        for (std::size_t i = 0; i < names_.size(); ++i) names_[i] = pspBoneName(costume_.bones[i].name);
        std::set<std::string> unique;
        for (const std::string& name : names_)
            if (!unique.insert(name).second)
                throw std::runtime_error("psp model: two bones would both be named '" + name + "'");
        children_.assign(names_.size(), {});
        std::vector<unsigned> roots;
        for (std::size_t i = 0; i < costume_.bones.size(); ++i) {
            const int parent = costume_.bones[i].parent;
            if (parent < 0) roots.push_back((unsigned)i);
            else children_.at((std::size_t)parent).push_back((unsigned)i);
        }
        if (roots.empty()) throw std::runtime_error("psp model: no root bone");
        scaledRoots_.assign(names_.size(), false);
        for (unsigned root : roots) scaledRoots_[root] = true;
        roots_ = std::move(roots);
        for (std::size_t i = 0; i < costume_.bones.size(); ++i) {
            const GmoBone& bone = costume_.bones[i];
            bind_.push_back(composeLocal(bone.translation, bone.rotation));
            if (scaledRoots_[i]) bind_.back() = multiplyMatrix(bind_.back(), rootFixMatrix(scale_));
        }
    }

    PspConvertedModel run(const std::vector<RgbaImage>& headPictures) {
        buildGeometry();
        PspConvertedModel out;
        out.boneNames = names_;
        out.meshes = (unsigned)groups_.size();
        for (const Group& group : groups_) out.triangles += (unsigned)group.triangles.size();

        XFile file;
        // AnimTicksPerSecond first, as the PC models have it: the core reads the clock
        // before it decodes any set.
        file.beginObject("AnimTicksPerSecond");
        file.intList({kTicksPerSecond});
        file.endObject();
        for (unsigned root : roots_) emitFrame(file, root);
        emitAnimations(file, out);
        out.x = file.take();
        emitTextures(headPictures, out);
        return out;
    }

private:
    // -- frames
    void emitFrame(XFile& file, unsigned bone) {
        // The mesh-owning frame is written **without a name**, as the PC rigs write theirs.
        // That is not cosmetic: a PC frame table anchors a state's hit record on "" when the
        // state has no hitbox, and the core resolves that name through ActorSkeleton::find.
        // A rig with no unnamed frame returns 0 there, and the core treats bone 0 as "the
        // looked-up bone is missing" and throws inside the tick
        // (development_animated_combat.hpp, snapshot_body_contact_geometry). The PC rigs have
        // such a frame, so an empty name binds; mirroring the convention keeps the borrowed
        // frame tables working unchanged, and it anchors those records on this frame's world
        // transform, which is the rig's root.
        file.beginObject("Frame", bone == costume_.meshBoneIndex ? std::string() : names_[bone]);
        file.beginObject("FrameTransformMatrix");
        file.floatList(bind_[bone].data(), 16);
        file.endObject();
        if (bone == costume_.meshBoneIndex) {
            for (const Group& group : groups_) emitMesh(file, group);
        }
        for (unsigned child : children_[bone]) emitFrame(file, child);
        file.endObject();
    }

    void emitMesh(XFile& file, const Group& group) {
        const std::size_t count = group.vertices.size();
        file.beginObject("Mesh", group.meshName);

        std::vector<float> positions;
        positions.reserve(count * 3);
        for (const GroupVertex& vertex : group.vertices)
            for (float value : vertex.position) positions.push_back(value);
        file.intList({(std::uint32_t)count});
        file.floatList(positions);

        std::vector<std::uint32_t> faces;
        faces.reserve(1 + group.triangles.size() * 4);
        faces.push_back((std::uint32_t)group.triangles.size());
        for (const auto& triangle : group.triangles) {
            faces.push_back(3);
            faces.push_back(triangle[0]);
            faces.push_back(triangle[1]);
            faces.push_back(triangle[2]);
        }
        file.intList(faces);

        // Normals are per vertex, so the face lists repeat the face corner indices; both
        // readers only require the corner counts to agree with the face list.
        file.beginObject("MeshNormals");
        std::vector<float> normals;
        normals.reserve(count * 3);
        for (const GroupVertex& vertex : group.vertices)
            for (float value : vertex.normal) normals.push_back(value);
        file.intList({(std::uint32_t)count});
        file.floatList(normals);
        file.intList(faces);
        file.endObject();

        file.beginObject("MeshTextureCoords");
        std::vector<float> uvs;
        uvs.reserve(count * 2);
        for (const GroupVertex& vertex : group.vertices) {
            uvs.push_back(vertex.uv[0]);
            uvs.push_back(vertex.uv[1]);
        }
        file.intList({(std::uint32_t)count});
        file.floatList(uvs);
        file.endObject();

        emitMaterial(file, group);

        // One SkinWeights object per bone, listing the vertices it moves: the form both
        // readers decode (name, vertex indices, weights, then the bind matrix).
        std::map<unsigned, std::vector<std::pair<std::uint32_t, float>>> perBone;
        for (std::uint32_t index = 0; index < count; ++index)
            for (const auto& influence : group.vertices[index].influences)
                perBone[influence.first].push_back({index, influence.second});
        for (const auto& entry : perBone) {
            file.beginObject("SkinWeights");
            file.string(names_[entry.first]);
            std::vector<std::uint32_t> indices;
            std::vector<float> weights;
            indices.reserve(1 + entry.second.size());
            indices.push_back((std::uint32_t)entry.second.size());
            for (const auto& pair : entry.second) {
                indices.push_back(pair.first);
                weights.push_back(pair.second);
            }
            file.intList(indices);
            const std::array<float, 16> offset = bindOffset(entry.first);
            for (float value : offset) weights.push_back(value);
            file.floatList(weights);
            file.endObject();
        }
        file.endObject();   // Mesh
    }

    void emitMaterial(XFile& file, const Group& group) {
        const std::string texture = textureName(group.material);
        file.beginObject("MeshMaterialList");
        std::vector<std::uint32_t> list;
        list.reserve(2 + group.triangles.size());
        list.push_back(1);                                    // one material
        list.push_back((std::uint32_t)group.triangles.size());  // one index per face
        list.insert(list.end(), group.triangles.size(), 0u);
        file.intList(list);
        file.beginObject("Material");
        // The PC's materials are white with no power; the PSP's 0.2 ambient term belongs to
        // its own fixed-function setup, and this renderer shades with the diffuse colour, so
        // the texture would come out five times too dark with the PSP's value.
        file.floatList({1.f, 1.f, 1.f, 1.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f});
        file.beginObject("TextureFilename");
        file.string(texture + ".bmp");
        file.endObject();
        file.endObject();   // Material
        file.endObject();   // MeshMaterialList
    }

    // -- animations
    void emitAnimations(XFile& file, PspConvertedModel& out) {
        const std::vector<GmoMotion>& motions = rig_.motions;
        // Reverse document order: the core (battle_actor_assets.hpp) and the product
        // (xmodel.h finish()) both register sets back to front, so this is what makes
        // index i in either reader PSP take i.
        for (std::size_t index = motions.size(); index-- > 0;) {
            const GmoMotion& motion = motions[index];
            file.beginObject("AnimationSet", motion.name.empty() ? "Anim-" + std::to_string(index)
                                                                 : motion.name);
            if (!emitTake(file, motion)) {
                ++out.emptyTakes;
                // A take with no curve still has to occupy its index, so it becomes a
                // constant hold on the root: both readers drop a set with no tracks at all,
                // and a dropped set would shift every later index.
                //
                // Two keys, not one. A take's length is its last key time, and the core turns
                // that into whole 60 Hz frames (actor_animation_frame_count): one key is zero
                // ticks, i.e. a zero-length animation, and the row timers that scale a phase
                // to its animation's length divide by it. Keys one 30 Hz frame apart are the
                // one-frame take the PSP has (0..0), read at 60 Hz.
                file.beginObject("Animation", names_[roots_.front()]);
                file.reference(names_[roots_.front()]);
                file.beginObject("AnimationKey");
                file.intList({4, 2, 0, 16});
                file.floatList(bind_[roots_.front()].data(), 16);
                file.intList({(std::uint32_t)(kTicksPerSecond / 30), 16});
                file.floatList(bind_[roots_.front()].data(), 16);
                file.endObject();
                file.endObject();
            }
            file.endObject();
            ++out.animationSets;
        }
    }

    // Returns false when the take animates nothing.
    bool emitTake(XFile& file, const GmoMotion& motion) {
        struct Channels {
            const GmoCurve* translate = nullptr;
            const GmoCurve* rotate = nullptr;
        };
        std::map<unsigned, Channels> channels;
        for (const GmoMotion::Binding& binding : motion.bindings) {
            if (binding.bone >= names_.size() || binding.curve >= motion.curves.size())
                throw std::runtime_error("psp model: motion binding out of range");
            Channels& entry = channels[binding.bone];
            if (binding.target == 0x48) entry.translate = &motion.curves[binding.curve];
            else if (binding.target == 0x4b) entry.rotate = &motion.curves[binding.curve];
            // 0x42 (scale) is left out on purpose: the only curves of that kind toggle the
            // two wapon_controll_* helper bones between 0 and 1, a zero scale here would be
            // a degenerate matrix for both readers, and nothing is drawn on those bones.
        }
        if (channels.empty()) return false;

        const float frames = std::max(1.f, std::round(motion.range[1] - motion.range[0]));
        const std::uint32_t keys = (std::uint32_t)frames + 1;
        const float ticksPerFrame = motion.fps > 0.f ? (float)kTicksPerSecond / motion.fps
                                                     : (float)kTicksPerSecond / 30.f;
        for (const auto& entry : channels) {
            const unsigned bone = entry.first;
            file.beginObject("Animation", names_[bone]);
            file.reference(names_[bone]);
            file.beginObject("AnimationKey");
            file.intList({4, keys});
            for (std::uint32_t key = 0; key < keys; ++key) {
                const float frame = motion.range[0] + (float)key;
                std::array<float, 3> translation = costume_.bones[bone].translation;
                std::array<float, 4> rotation = costume_.bones[bone].rotation;
                if (entry.second.translate) {
                    std::array<float, 4> value{0.f, 0.f, 0.f, 0.f};
                    entry.second.translate->sample(frame, value.data());
                    translation = {value[0], value[1], value[2]};
                }
                if (entry.second.rotate) {
                    std::array<float, 4> value{0.f, 0.f, 0.f, 1.f};
                    entry.second.rotate->sample(frame, value.data());
                    rotation = value;
                }
                Matrix local = composeLocal(translation, rotation);
                // A scaled root keeps its scale and its half turn in every pose, so a motion
                // that ever animates it cannot drop either.
                if (scaledRoots_[bone]) local = multiplyMatrix(local, rootFixMatrix(scale_));
                const std::uint32_t time = (std::uint32_t)std::lround(frame * ticksPerFrame);
                file.intList({time, 16});
                file.floatList(local.data(), 16);
            }
            file.endObject();   // AnimationKey
            file.endObject();   // Animation
        }
        return true;
    }

    // -- geometry
    void buildGeometry() {
        std::map<unsigned, std::size_t> byMaterial;
        for (std::size_t meshIndex = 0; meshIndex < costume_.meshes.size(); ++meshIndex) {
            const GmoMesh& mesh = costume_.meshes[meshIndex];
            if (mesh.material >= costume_.materials.size())
                throw std::runtime_error("psp model: mesh material out of range");
            auto found = byMaterial.find(mesh.material);
            std::size_t groupIndex = 0;
            if (found == byMaterial.end()) {
                groupIndex = groups_.size();
                byMaterial.emplace(mesh.material, groupIndex);
                Group group;
                group.material = mesh.material;
                group.meshName = std::string("mesh-") + std::to_string(mesh.material);
                groups_.push_back(std::move(group));
            } else {
                groupIndex = found->second;
            }
            Group& group = groups_[groupIndex];
            std::map<std::pair<std::uint32_t, std::uint32_t>, std::uint32_t> remap;
            for (const GmoDraw& draw : mesh.draws) {
                if (draw.array >= costume_.arrays.size())
                    throw std::runtime_error("psp model: draw references a missing vertex array");
                const GmoArray& array = costume_.arrays[draw.array];
                auto vertexAt = [&](std::uint32_t index) {
                    const std::pair<std::uint32_t, std::uint32_t> key{draw.array, index};
                    auto found2 = remap.find(key);
                    if (found2 != remap.end()) return found2->second;
                    if (index >= array.vertices.size())
                        throw std::runtime_error("psp model: draw index past its vertex array");
                    GroupVertex vertex;
                    vertex.position = array.vertices[index].position;
                    vertex.normal = array.vertices[index].normal;
                    vertex.uv = array.vertices[index].uv;
                    vertex.influences = influencesOf(mesh, array.vertices[index]);
                    const std::uint32_t local = (std::uint32_t)group.vertices.size();
                    group.vertices.push_back(std::move(vertex));
                    remap.emplace(key, local);
                    return local;
                };
                const std::uint32_t mode = draw.mode & 0xFFu;
                if (mode != 3 && mode != 4)
                    throw std::runtime_error("psp model: draw mode " + std::to_string(mode));
                const bool strip = mode == 4;
                for (std::uint32_t repeat = 0; repeat < draw.repeat; ++repeat) {
                    const std::uint32_t start = draw.first + repeat * draw.count;
                    // A strip of n vertices has n-2 triangles; a list of n has ceil((n-2)/3).
                    const std::uint32_t tris = strip ? draw.count - 2 : (draw.count) / 3;
                    for (std::uint32_t k = 0; k < tris; ++k) {
                        std::uint32_t a = start + (strip ? k : k * 3);
                        std::uint32_t b = a + 1;
                        std::uint32_t c = a + 2;
                        // A strip alternates winding between triangles; flipping the odd
                        // ones keeps every face in the mesh wound the same way.
                        if (strip && (k & 1)) std::swap(a, b);
                        const std::uint32_t ia = vertexAt(a), ib = vertexAt(b), ic = vertexAt(c);
                        if (ia == ib || ib == ic || ia == ic) continue;
                        group.triangles.push_back({ia, ib, ic});
                    }
                }
            }
        }
        groups_.erase(std::remove_if(groups_.begin(), groups_.end(),
                                     [](const Group& group) { return group.triangles.empty(); }),
                      groups_.end());
        // The renderer's submesh order is the file's; keep the groups in material order so
        // body/face/head/hair draw in the order the PSP data lists them.
        std::sort(groups_.begin(), groups_.end(),
                  [](const Group& a, const Group& b) { return a.material < b.material; });
    }

    std::vector<std::pair<unsigned, float>> influencesOf(const GmoMesh& mesh, const GmoVertex& vertex) const {
        const GmoBone& owner = costume_.bones[costume_.meshBoneIndex];
        std::map<unsigned, float> merged;
        for (unsigned slot = 0; slot < vertex.weightCount; ++slot) {
            const unsigned weight = vertex.weights[slot];
            if (!weight) continue;
            if (slot >= mesh.palette.size()) throw std::runtime_error("psp model: palette shorter than the weight count");
            const unsigned blendSlot = mesh.palette[slot];
            if (blendSlot >= owner.blendBones.size()) throw std::runtime_error("psp model: palette past the blend bone list");
            merged[owner.blendBones[blendSlot]] += (float)weight / 128.f;
        }
        std::vector<std::pair<unsigned, float>> influences(merged.begin(), merged.end());
        float total = 0.f;
        for (const auto& entry : influences) total += entry.second;
        // Four influences is what both readers keep (the renderer drops the weakest and
        // renormalises, the core picks the four largest), so the file keeps the four
        // largest itself and normalises once.
        std::partial_sort(influences.begin(),
                          influences.begin() + (std::ptrdiff_t)std::min<std::size_t>(4, influences.size()),
                          influences.end(),
                          [](const auto& a, const auto& b) { return a.second > b.second; });
        if (influences.size() > 4) influences.resize(4);
        float kept = 0.f;
        for (const auto& entry : influences) kept += entry.second;
        if (kept <= 0.f) return {};
        for (auto& entry : influences) entry.second /= kept;
        return influences;
    }

    std::array<float, 16> bindOffset(unsigned bone) const {
        const GmoBone& owner = costume_.bones[costume_.meshBoneIndex];
        for (std::size_t slot = 0; slot < owner.blendBones.size(); ++slot)
            if (owner.blendBones[slot] == bone) {
                if (slot >= owner.offsets.size())
                    throw std::runtime_error("psp model: blend bone has no bind matrix");
                return owner.offsets[slot];
            }
        throw std::runtime_error("psp model: skin bone without a bind matrix");
    }

    // -- textures
    std::string textureName(unsigned material) const {
        const GmoMaterial& entry = costume_.materials.at(material);
        if (entry.texture < 0 || (std::size_t)entry.texture >= costume_.textures.size())
            throw std::runtime_error("psp model: material '" + entry.name + "' has no texture");
        return costume_.textures[(std::size_t)entry.texture].name;
    }

    void emitTextures(const std::vector<RgbaImage>& headPictures, PspConvertedModel& out) const {
        std::set<std::string> done;
        for (const Group& group : groups_) {
            const std::string name = textureName(group.material);
            if (!done.insert(name).second) continue;
            const GmoTexture& texture = costume_.textures.at((std::size_t)costume_.materials.at(group.material).texture);
            RgbaImage image;
            if (!texture.tga.empty()) {
                image = decodeTga(texture.tga);
            } else {
                const int picture = pspHeadPicture(name);
                if (picture < 0)
                    throw std::runtime_error("psp model: texture '" + name + "' is neither embedded nor in the head atlas");
                if ((std::size_t)picture >= headPictures.size())
                    throw std::runtime_error("psp model: the head atlas has no picture " + std::to_string(picture));
                image = headPictures[(std::size_t)picture];
            }
            out.textures.push_back({name + ".cnv", encodeCnv(image)});
        }
    }

    const GmoModel&                     rig_;
    const GmoModel&                     costume_;
    float                               scale_ = 1.f;
    std::vector<std::string>            names_;
    std::vector<std::vector<unsigned>>  children_;
    std::vector<unsigned>               roots_;
    std::vector<Matrix>                 bind_;
    std::vector<bool>                   scaledRoots_;
    std::vector<Group>                  groups_;
};

std::vector<std::uint8_t> readBytes(const std::string& path) {
    std::ifstream stream(fs::u8path(path), std::ios::binary);
    if (!stream) throw std::runtime_error("cannot read " + path);
    std::vector<std::uint8_t> bytes((std::istreambuf_iterator<char>(stream)),
                                    std::istreambuf_iterator<char>());
    if (bytes.empty()) throw std::runtime_error(path + " is empty");
    return bytes;
}

void writeBytes(const std::string& path, const std::vector<std::uint8_t>& bytes) {
    const fs::path file = fs::u8path(path);
    std::error_code error;
    if (!file.parent_path().empty()) fs::create_directories(file.parent_path(), error);
    std::ofstream stream(file, std::ios::binary | std::ios::trunc);
    if (!stream) throw std::runtime_error("cannot write " + path);
    stream.write(reinterpret_cast<const char*>(bytes.data()), (std::streamsize)bytes.size());
    if (!stream) throw std::runtime_error("cannot write " + path);
}

std::string joinPath(const std::string& directory, const std::string& rest) {
    if (directory.empty()) return rest;
    return (directory.back() == '/' || directory.back() == '\\') ? directory + rest
                                                                 : directory + "/" + rest;
}

}  // namespace

const std::vector<PspFighter>& pspFighters() {
    // Costume lists and the scales from docs/PSP-CHARACTERS-PLAN.md's height table. The
    // scales are the plan's starting values, judged by eye against the PC cast.
    static const std::vector<PspFighter> fighters = {
        {"satoshi", "g3d/chrm17.gmo", "g3d/chrt17.gim",
         {"g3d/chr170.gmo", "g3d/chr171.gmo", "g3d/chr172.gmo", "g3d/chr173.gmo", "g3d/chr174.gmo"}, 0.97f},
        {"miyoko", "g3d/chrm18.gmo", "g3d/chrt18.gim",
         {"g3d/chr180.gmo", "g3d/chr181.gmo", "g3d/chr182.gmo", "g3d/chr183.gmo", "g3d/chr184.gmo",
          "g3d/chr185.gmo", "g3d/chr186.gmo"}, 0.86f},
        {"okonogi", "g3d/chrm19.gmo", "g3d/chrt19.gim",
         {"g3d/chr190.gmo", "g3d/chr191.gmo", "g3d/chr192.gmo"}, 1.14f},
    };
    return fighters;
}

std::string pspBoneName(const std::string& name) {
    // The upper body gets the "Bip01" prefix the PC rigs use (that prefix is the core's
    // upper-body channel), the legs the Bip00 one, and the two weapon hands become the
    // props the attachment and muzzle code looks up. Names not in the table are kept: the
    // hair, cloth, skirt and finger chains have no PC equivalent and the core never looks
    // them up.
    static const std::pair<const char*, const char*> kNames[] = {
        {"root", "Bip00"},
        {"lefthip", "Bip00_L_Thigh"},
        {"leftknee", "Bip00_L_Calf"},
        {"leftfoot", "Bip00_L_Foot"},
        {"lefttoe1", "Bip00_L_Toe0"},
        {"righthip", "Bip00_R_Thigh"},
        {"rightknee", "Bip00_R_Calf"},
        {"rightfoot", "Bip00_R_Foot"},
        {"righttoe1", "Bip00_R_Toe0"},
        {"spine1", "Bip01_Spine"},
        {"spine2", "Bip01_Spine1"},
        {"neck", "Bip01_Neck"},
        {"head", "Bip01_Head"},
        {"leftcollar", "Bip01_L_Clavicle"},
        {"leftshoulder", "Bip01_L_UpperArm"},
        {"leftelbow", "Bip01_L_Forearm"},
        {"lefthand", "Bip01_L_Hand"},
        {"rightcollar", "Bip01_R_Clavicle"},
        {"rightshoulder", "Bip01_R_UpperArm"},
        {"rightelbow", "Bip01_R_Forearm"},
        {"righthand", "Bip01_R_Hand"},
        {"weapon_r", "Bip01_Prop1"},
        {"weapon_l", "Bip01_Prop2"},
    };
    for (const auto& entry : kNames)
        if (name == entry.first) return entry.second;
    return name;
}

int pspHeadPicture(const std::string& textureName) {
    // chrtNN.gim holds ten pictures in the order the model's material names expect: the
    // eight face expressions, then the hair, then the scalp with the ear. Measured on
    // Okonogi by the reference importer (gmo_blender.py's HEAD_PICTURES).
    //
    // The shipped texture names disagree on how many underscores separate the character
    // number from the part ("chr19__face" but "chr17_face" and "chr186_body"), so the test
    // is on the last part and its separating underscore, not on a fixed spelling.
    static const std::pair<const char*, int> kParts[] = {
        {"_face", 0}, {"_hair", 8}, {"_head", 9},
    };
    for (const auto& part : kParts) {
        const std::size_t length = std::strlen(part.first);
        if (textureName.size() > length &&
            textureName.compare(textureName.size() - length, length, part.first) == 0)
            return part.second;
    }
    return -1;
}

PspConvertedModel buildPspModel(const GmoModel& rig, const GmoModel& costume,
                                const std::vector<RgbaImage>& headPictures, float scale) {
    Builder builder(rig, costume, scale);
    return builder.run(headPictures);
}

std::vector<std::string> convertPspFighters(const std::string& dataDir, std::ostream& log) {
    std::vector<std::string> written;
    for (const PspFighter& fighter : pspFighters()) {
        const std::vector<std::uint8_t> rigBytes = readBytes(pspRawPath(dataDir, fighter.rig));
        const GmoModel rig = GmoModel::parse(rigBytes);
        const std::vector<RgbaImage> heads = decodeGim(readBytes(pspRawPath(dataDir, fighter.head)));
        for (std::size_t costume = 0; costume < fighter.costumes.size(); ++costume) {
            // The core selects the model directory per costume: data/<name>, then
            // data/<name>_B, _C, ... (character_asset_files.hpp), so a costume needs its own
            // folder even though the skeleton and every motion are identical.
            std::string folder = "data/" + fighter.name;
            if (costume) folder += "_" + std::string(1, (char)('A' + costume));
            const std::string directory = joinPath(dataDir, folder);
            const GmoModel mesh = GmoModel::parse(readBytes(pspRawPath(dataDir, fighter.costumes[costume])));
            PspConvertedModel model = buildPspModel(rig, mesh, heads, fighter.scale);
            const std::string xPath = joinPath(directory, "00.X");
            writeBytes(xPath, model.x);
            written.push_back(folder + "/00.X");
            for (const PspConvertedModel::Texture& texture : model.textures) {
                writeBytes(joinPath(directory, texture.file), texture.cnv);
                written.push_back(folder + "/" + texture.file);
            }
            log << "psp: " << folder << "/00.X " << model.boneNames.size() << " bones, "
                << model.meshes << " meshes, " << model.triangles << " triangles, "
                << model.animationSets << " animation sets (" << model.emptyTakes
                << " empty takes kept), " << model.x.size() << " bytes, " << model.textures.size()
                << " textures\n";
        }
    }
    return written;
}

}  // namespace psp
