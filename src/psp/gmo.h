#pragma once
// psp/gmo.h — the PSP's "OMG" model container, as far as the port needs it.
//
// One GMO carries a chunk tree: bones with their bind transform and their blend-bone
// list, skinned meshes with vertex arrays, materials with textures, whole TGA files, and —
// in the separate chrmNN.gmo — a set of motions. tools/asset-tools/gmo_blender.py is the
// reference parser for this format and the one this reader was written against (it keeps
// its keys un-baked and reproduces the file's raw pose to 0.0018 units), so the field
// layouts below are that parser's, not a second opinion.
//
// A chunk header is {u16 type, u16 headerSize, u32 size}; headerSize is the offset of the
// payload, so it must be read rather than assumed 0x10. Matrices are stored row-vector
// (translation in 12..14), which is also how the PC's .X stores them, so no transpose
// happens anywhere in the conversion.
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace psp {

struct GmoBone {
    std::string              name;
    int                      parent = -1;
    std::array<float, 3>     translation{0.f, 0.f, 0.f};
    std::array<float, 4>     rotation{0.f, 0.f, 0.f, 1.f};  // x, y, z, w as stored
    std::vector<std::uint32_t> blendBones;                  // bone indices, slot order
    std::vector<std::array<float, 16>> offsets;             // inverse bind, row-vector
};

struct GmoVertex {
    std::array<float, 3>        position{};
    std::array<float, 3>        normal{};
    std::array<float, 2>        uv{};
    std::array<std::uint8_t, 8> weights{};
    unsigned                    weightCount = 0;
};

struct GmoArray {
    std::uint32_t           vertexType = 0;
    std::vector<GmoVertex>  vertices;
};

struct GmoDraw {           // one 0x8066: a strip or list over one array
    std::uint32_t array = 0;
    std::uint32_t mode = 0;    // low byte: 3 = triangle list, 4 = triangle strip
    std::uint32_t count = 0;
    std::uint32_t repeat = 0;
    std::uint32_t first = 0;
};

struct GmoMesh {
    std::string                name;
    std::uint32_t              material = 0;
    std::vector<std::uint32_t> palette;   // vertex weight slot -> index into blendBones
    std::vector<GmoDraw>       draws;
};

struct GmoMaterial {
    std::string        name;
    int                texture = -1;
    std::array<float, 5> params{};   // diffuse rgb, alpha, power
};

struct GmoTexture {
    std::string                name;
    std::vector<std::uint8_t>  tga;   // empty for a texture that lives in another file
};

// 0x000c. The low nibble of `format` is the interpolation: 0 constant, 1 linear, 4 slerp
// (quaternions). chrm19.gmo also uses high bits (0x4400) that no consumer reads.
struct GmoCurve {
    std::uint32_t                              format = 0;
    std::uint32_t                              dimensions = 0;
    std::vector<std::array<float, 5>>          keys;   // time, then up to four values

    unsigned mode() const { return format & 15u; }
    // Writes `dimensions` values for `frame`, between the first and last key.
    void sample(float frame, float* out) const;
    float lastTime() const { return keys.empty() ? 0.f : keys.back()[0]; }
};

struct GmoMotion {
    struct Binding {
        std::uint32_t bone = 0;    // index into the bone list
        std::uint32_t target = 0;  // 0x48 translate, 0x4b rotate, 0x42 scale
        std::uint32_t curve = 0;   // index into `curves`
    };
    std::string             name;
    std::array<float, 2>    range{0.f, 0.f};   // frames
    float                   fps = 30.f;
    std::vector<Binding>    bindings;
    std::vector<GmoCurve>   curves;
};

struct GmoModel {
    std::vector<GmoBone>     bones;
    std::vector<GmoMotion>   motions;
    std::vector<GmoArray>    arrays;
    std::vector<GmoMesh>     meshes;
    std::vector<GmoMaterial> materials;
    std::vector<GmoTexture>  textures;
    // The bone a 0x0005 chunk hangs its meshes off: the mesh-owning bone's name, resolved
    // to a bone index after the walk (it is the bone of the same name in every shipped
    // character file, and the chunk is a sibling of that bone's 0x0004 chunk, not its
    // child).
    std::string meshBone;
    unsigned    meshBoneIndex = 0;

    // Throws std::runtime_error naming the offset when the container is not a GMO or a
    // chunk runs past its parent.
    static GmoModel parse(const std::vector<std::uint8_t>& bytes);

    // Vertex layout of a PSP GE vertex: weight, UV, colour, normal, position, each aligned
    // to its own size and the stride to the largest member.
    struct VertexLayout {
        unsigned weightOffset = 0, weightCount = 0, uvOffset = 0, normalOffset = 0,
                 positionOffset = 0, stride = 0;
    };
    static VertexLayout vertexLayout(std::uint32_t vertexType);
};

}  // namespace psp
