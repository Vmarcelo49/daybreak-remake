// psp/gmo.cpp — the GMO chunk walk and the four payloads the conversion reads.
#include "psp/gmo.h"

#include <cmath>
#include <cstring>
#include <stdexcept>

namespace psp {
namespace {

constexpr std::uint16_t kBone = 0x0004;
constexpr std::uint16_t kBoneWithMesh = 0x0005;
constexpr std::uint16_t kMesh = 0x0006;
constexpr std::uint16_t kArray = 0x0007;
constexpr std::uint16_t kMaterial = 0x0008;
constexpr std::uint16_t kLayer = 0x0009;
constexpr std::uint16_t kTexture = 0x000a;
constexpr std::uint16_t kMotion = 0x000b;
constexpr std::uint16_t kCurve = 0x000c;

constexpr std::uint16_t kParent = 0x8041;
constexpr std::uint16_t kTranslate = 0x8048;
constexpr std::uint16_t kRotate = 0x804b;
constexpr std::uint16_t kBlendBones = 0x8044;
constexpr std::uint16_t kBlendOffsets = 0x8045;
constexpr std::uint16_t kMeshMaterial = 0x8061;
constexpr std::uint16_t kMeshPalette = 0x8062;
constexpr std::uint16_t kMeshDraw = 0x8066;
constexpr std::uint16_t kMaterialParams = 0x8083;
constexpr std::uint16_t kLayerTexture = 0x8091;
constexpr std::uint16_t kTextureTga = 0x8013;
constexpr std::uint16_t kMotionRange = 0x80b1;
constexpr std::uint16_t kMotionFps = 0x80b2;
constexpr std::uint16_t kMotionBinding = 0x80b3;

std::uint32_t rd16(const std::uint8_t* p) { return (std::uint32_t)p[0] | ((std::uint32_t)p[1] << 8); }
std::uint32_t rd32(const std::uint8_t* p) {
    return (std::uint32_t)p[0] | ((std::uint32_t)p[1] << 8) | ((std::uint32_t)p[2] << 16) |
           ((std::uint32_t)p[3] << 24);
}
float rdf32(const std::uint8_t* p) {
    const std::uint32_t bits = rd32(p);
    float value = 0.f;
    std::memcpy(&value, &bits, 4);
    return value;
}

// The low 12 bits of a chunk reference index a sibling list; the high bits repeat the
// chunk type, which is why every reference in this format is masked before use.
std::uint32_t referenceIndex(std::uint32_t value) { return value & 0xFFFu; }

struct Chunk {
    std::uint16_t type = 0;
    std::uint32_t header = 0;
    std::uint32_t size = 0;
    std::size_t   offset = 0;
    // A named chunk carries its name between the header and the payload, so headerSize is
    // the payload offset. The anonymous leaves (every 0x80xx type: parent, translate,
    // rotate, blend bones, material reference, ...) leave headerSize at zero and put their
    // values immediately after the 8-byte chunk header instead, which is why this is not
    // simply offset + header.
    std::size_t payload() const { return offset + (header ? header : 8); }
};

class Walk {
public:
    Walk(const std::vector<std::uint8_t>& bytes, std::size_t start, std::size_t end)
        : bytes_(bytes), end_(end), at_(start) {}

    bool next(Chunk& chunk) {
        if (at_ + 8 > end_) return false;
        chunk.type = (std::uint16_t)rd16(bytes_.data() + at_);
        chunk.header = rd16(bytes_.data() + at_ + 2);
        chunk.size = rd32(bytes_.data() + at_ + 4);
        chunk.offset = at_;
        if (chunk.size < 8 || chunk.header > chunk.size || at_ + chunk.size > end_)
            throw std::runtime_error("gmo: bad chunk at offset " +
                                     std::to_string((unsigned long long)at_));
        at_ += chunk.size;
        return true;
    }

private:
    const std::vector<std::uint8_t>& bytes_;
    std::size_t                      end_, at_;
};

std::string chunkName(const std::vector<std::uint8_t>& bytes, const Chunk& chunk) {
    if (chunk.header <= 16) return {};
    const char* start = reinterpret_cast<const char*>(bytes.data() + chunk.offset + 16);
    const std::size_t limit = chunk.header - 16;
    std::size_t length = 0;
    while (length < limit && start[length]) ++length;
    return std::string(start, length);
}

class Parser {
public:
    explicit Parser(const std::vector<std::uint8_t>& bytes) : bytes_(bytes) {}

    GmoModel run() {
        if (bytes_.size() < 0x10 || std::memcmp(bytes_.data(), "OMG.00.1PSP", 11) != 0)
            throw std::runtime_error("gmo: not an OMG.00.1PSP model");
        descend(0x10, bytes_.size());
        resolveMeshBone();
        return std::move(model_);
    }

private:
    void descend(std::size_t start, std::size_t end) {
        Walk walk(bytes_, start, end);
        Chunk chunk;
        while (walk.next(chunk)) {
            switch (chunk.type) {
                case kBone: model_.bones.push_back(bone(chunk)); break;
                case kBoneWithMesh:
                    model_.meshBone = chunkName(bytes_, chunk);
                    descend(chunk.payload(), chunk.offset + chunk.size);
                    break;
                case kMesh: model_.meshes.push_back(mesh(chunk)); break;
                case kArray: model_.arrays.push_back(array(chunk)); break;
                case kMaterial: model_.materials.push_back(material(chunk)); break;
                case kTexture: model_.textures.push_back(texture(chunk)); break;
                case kMotion: model_.motions.push_back(motion(chunk)); break;
                // 0x0002/0x0003 are containers, 0x0009 a material layer.
                case 0x0002: case 0x0003: case kLayer:
                    descend(chunk.payload(), chunk.offset + chunk.size);
                    break;
                default: break;
            }
        }
    }

    void resolveMeshBone() {
        for (std::size_t i = 0; i < model_.bones.size(); ++i)
            if (model_.bones[i].name == model_.meshBone) {
                model_.meshBoneIndex = (unsigned)i;
                return;
            }
        throw std::runtime_error("gmo: no bone named '" + model_.meshBone + "' for the meshes");
    }

    GmoBone bone(const Chunk& chunk) {
        GmoBone out;
        out.name = chunkName(bytes_, chunk);
        Walk walk(bytes_, chunk.payload(), chunk.offset + chunk.size);
        Chunk child;
        while (walk.next(child)) {
            const std::size_t at = child.payload();
            switch (child.type) {
                case kParent:
                    out.parent = (int)referenceIndex(rd32(bytes_.data() + at));
                    break;
                case kTranslate:
                    for (unsigned i = 0; i < 3; ++i) out.translation[i] = rdf32(bytes_.data() + at + 4 * i);
                    break;
                case kRotate:
                    for (unsigned i = 0; i < 4; ++i) out.rotation[i] = rdf32(bytes_.data() + at + 4 * i);
                    break;
                case kBlendBones: {
                    const std::uint32_t count = rd32(bytes_.data() + at);
                    for (unsigned i = 0; i < count; ++i)
                        out.blendBones.push_back(referenceIndex(rd32(bytes_.data() + at + 4 + 4 * i)));
                    break;
                }
                case kBlendOffsets: {
                    const std::uint32_t count = rd32(bytes_.data() + at);
                    for (unsigned i = 0; i < count; ++i) {
                        std::array<float, 16> matrix{};
                        for (unsigned k = 0; k < 16; ++k)
                            matrix[k] = rdf32(bytes_.data() + at + 4 + i * 64 + k * 4);
                        out.offsets.push_back(matrix);
                    }
                    break;
                }
                default: break;
            }
        }
        // A missing parent chunk means a root bone; -1 is the reference parser's default.
        return out;
    }

    GmoMesh mesh(const Chunk& chunk) {
        GmoMesh out;
        out.name = chunkName(bytes_, chunk);
        Walk walk(bytes_, chunk.payload(), chunk.offset + chunk.size);
        Chunk child;
        while (walk.next(child)) {
            const std::size_t at = child.payload();
            if (child.type == kMeshMaterial) out.material = referenceIndex(rd32(bytes_.data() + at));
            else if (child.type == kMeshPalette) {
                const std::uint32_t count = rd32(bytes_.data() + at);
                for (unsigned i = 0; i < count; ++i) out.palette.push_back(rd32(bytes_.data() + at + 4 + 4 * i));
            } else if (child.type == kMeshDraw) {
                GmoDraw draw;
                draw.array = referenceIndex(rd32(bytes_.data() + at));
                draw.mode = rd32(bytes_.data() + at + 4);
                draw.count = rd32(bytes_.data() + at + 8);
                draw.repeat = rd32(bytes_.data() + at + 12);
                draw.first = rd32(bytes_.data() + at + 16);
                out.draws.push_back(draw);
            }
        }
        return out;
    }

    GmoArray array(const Chunk& chunk) {
        GmoArray out;
        const std::size_t at = chunk.payload();
        out.vertexType = rd32(bytes_.data() + at);
        const std::uint32_t count = rd32(bytes_.data() + at + 4);
        const GmoModel::VertexLayout layout = GmoModel::vertexLayout(out.vertexType);
        // The four leading dwords (type, count and two the format does not use) come before
        // the vertex run.
        const std::size_t base = at + 16;
        if (base + (std::size_t)count * layout.stride > chunk.offset + chunk.size)
            throw std::runtime_error("gmo: vertex array runs past its chunk");
        out.vertices.resize(count);
        for (unsigned i = 0; i < count; ++i) {
            const std::uint8_t* v = bytes_.data() + base + (std::size_t)i * layout.stride;
            GmoVertex& vertex = out.vertices[i];
            for (unsigned k = 0; k < layout.weightCount; ++k) vertex.weights[k] = v[layout.weightOffset + k];
            vertex.weightCount = layout.weightCount;
            vertex.uv[0] = rdf32(v + layout.uvOffset);
            vertex.uv[1] = rdf32(v + layout.uvOffset + 4);
            for (unsigned k = 0; k < 3; ++k)
                vertex.normal[k] = (float)(std::int8_t)v[layout.normalOffset + k] / 127.f;
            for (unsigned k = 0; k < 3; ++k)
                vertex.position[k] = rdf32(v + layout.positionOffset + 4 * k);
        }
        return out;
    }

    GmoMaterial material(const Chunk& chunk) {
        GmoMaterial out;
        out.name = chunkName(bytes_, chunk);
        Walk walk(bytes_, chunk.payload(), chunk.offset + chunk.size);
        Chunk child;
        while (walk.next(child)) {
            const std::size_t at = child.payload();
            if (child.type == kMaterialParams)
                for (unsigned i = 0; i < 5; ++i) out.params[i] = rdf32(bytes_.data() + at + 4 * i);
            else if (child.type == kLayer) {
                Walk layers(bytes_, at, child.offset + child.size);
                Chunk layer;
                while (layers.next(layer))
                    if (layer.type == kLayerTexture && out.texture < 0)
                        out.texture = (int)referenceIndex(rd32(bytes_.data() + layer.payload()));
            }
        }
        return out;
    }

    GmoTexture texture(const Chunk& chunk) {
        GmoTexture out;
        out.name = chunkName(bytes_, chunk);
        Walk walk(bytes_, chunk.payload(), chunk.offset + chunk.size);
        Chunk child;
        while (walk.next(child)) {
            if (child.type != kTextureTga) continue;
            // 0x8013 is a dword and then a whole TGA file. The dword is not the TGA's
            // length (it reads two bytes short in every file), and the reference importer
            // ignores it: the picture is everything from 12 bytes into the chunk to its end.
            const std::size_t start = child.offset + 12;
            if (start > child.offset + child.size)
                throw std::runtime_error("gmo: embedded TGA chunk is too short");
            out.tga.assign(bytes_.begin() + (std::ptrdiff_t)start,
                           bytes_.begin() + (std::ptrdiff_t)(child.offset + child.size));
        }
        return out;
    }

    GmoMotion motion(const Chunk& chunk) {
        GmoMotion out;
        out.name = chunkName(bytes_, chunk);
        Walk walk(bytes_, chunk.payload(), chunk.offset + chunk.size);
        Chunk child;
        while (walk.next(child)) {
            const std::size_t at = child.payload();
            if (child.type == kMotionRange) {
                out.range[0] = rdf32(bytes_.data() + at);
                out.range[1] = rdf32(bytes_.data() + at + 4);
            } else if (child.type == kMotionFps) {
                out.fps = rdf32(bytes_.data() + at);
            } else if (child.type == kMotionBinding) {
                GmoMotion::Binding binding;
                binding.bone = referenceIndex(rd32(bytes_.data() + at));
                binding.target = rd32(bytes_.data() + at + 4);
                binding.curve = referenceIndex(rd32(bytes_.data() + at + 12));
                out.bindings.push_back(binding);
            } else if (child.type == kCurve) {
                out.curves.push_back(curve(child));
            }
        }
        return out;
    }

    GmoCurve curve(const Chunk& chunk) {
        GmoCurve out;
        const std::size_t at = chunk.payload();
        out.format = rd32(bytes_.data() + at);
        out.dimensions = rd32(bytes_.data() + at + 4);
        const std::uint32_t count = rd32(bytes_.data() + at + 8);
        if (out.dimensions == 0 || out.dimensions > 4)
            throw std::runtime_error("gmo: curve with " + std::to_string(out.dimensions) + " values per key");
        const unsigned width = out.dimensions + 1;
        const std::size_t first = at + 16;   // the fourth dword is always zero
        if (first + (std::size_t)count * width * 4 > chunk.offset + chunk.size)
            throw std::runtime_error("gmo: curve keys run past their chunk");
        out.keys.resize(count);
        for (unsigned i = 0; i < count; ++i) {
            std::array<float, 5>& key = out.keys[i];
            key = {0.f, 0.f, 0.f, 0.f, 0.f};
            for (unsigned k = 0; k < width; ++k)
                key[k] = rdf32(bytes_.data() + first + ((std::size_t)i * width + k) * 4);
        }
        return out;
    }

    const std::vector<std::uint8_t>& bytes_;
    GmoModel                         model_;
};

}  // namespace

GmoModel::VertexLayout GmoModel::vertexLayout(std::uint32_t vertexType) {
    // Bit fields: 0-1 UV kind, 2-4 colour kind, 5-6 normal kind, 7-8 position kind,
    // 9-10 weight component size, 14-16 weight count - 1. The high byte is a GMO-side flag
    // no reader needs.
    static const unsigned size[4] = {0, 1, 2, 4};
    const unsigned weightKind = (vertexType >> 9) & 3u;
    const unsigned weightCount = ((vertexType >> 14) & 7u) + 1u;
    const unsigned uvKind = vertexType & 3u;
    const unsigned normalKind = (vertexType >> 5) & 3u;
    const unsigned positionKind = (vertexType >> 7) & 3u;
    if (weightKind != 1 || uvKind != 3 || normalKind != 1 || positionKind != 3)
        throw std::runtime_error("gmo: unhandled vertex type");

    unsigned at = 0, largest = 1;
    auto place = [&](unsigned item, unsigned count) {
        if (!item) return 0u;
        at = (at + item - 1) & ~(item - 1);
        const unsigned start = at;
        at += item * count;
        if (item > largest) largest = item;
        return start;
    };
    VertexLayout layout;
    layout.weightCount = weightCount;
    layout.weightOffset = place(size[weightKind], weightCount);
    layout.uvOffset = place(size[uvKind], 2);
    // The colour member sits between the UVs and the normal and is never present in the
    // files this port reads; placing it keeps the offsets right if one ever is.
    static const unsigned colourSize[8] = {0, 0, 0, 0, 2, 2, 2, 4};
    place(colourSize[(vertexType >> 2) & 7u], 1);
    layout.normalOffset = place(size[normalKind], 3);
    layout.positionOffset = place(size[positionKind], 3);
    layout.stride = (at + largest - 1) & ~(largest - 1);
    return layout;
}

void GmoCurve::sample(float frame, float* out) const {
    if (keys.empty()) throw std::runtime_error("gmo: curve with no keys");
    auto copy = [&](const std::array<float, 5>& key) {
        for (unsigned i = 0; i < dimensions; ++i) out[i] = key[1 + i];
    };
    if (frame <= keys.front()[0]) { copy(keys.front()); return; }
    if (frame >= keys.back()[0]) { copy(keys.back()); return; }
    for (std::size_t i = 1; i < keys.size(); ++i) {
        const std::array<float, 5>& next = keys[i];
        if (frame >= next[0]) continue;
        const std::array<float, 5>& previous = keys[i - 1];
        const float span = next[0] - previous[0];
        const float t = span > 0.f ? (frame - previous[0]) / span : 1.f;
        if (mode() == 0) { copy(previous); return; }
        if (mode() == 4 && dimensions == 4) {
            // Shortest-arc slerp over the stored (x, y, z, w) order, as the reference
            // importer does.
            float a[4], b[4];
            for (unsigned k = 0; k < 4; ++k) { a[k] = previous[1 + k]; b[k] = next[1 + k]; }
            float dot = a[0] * b[0] + a[1] * b[1] + a[2] * b[2] + a[3] * b[3];
            if (dot < 0.f) {
                for (float& value : b) value = -value;
                dot = -dot;
            }
            if (dot > 0.9995f) {
                for (unsigned k = 0; k < 4; ++k) out[k] = a[k] + (b[k] - a[k]) * t;
            } else {
                const float theta = std::acos(dot);
                const float sinTheta = std::sin(theta);
                const float wa = std::sin((1.f - t) * theta) / sinTheta;
                const float wb = std::sin(t * theta) / sinTheta;
                for (unsigned k = 0; k < 4; ++k) out[k] = a[k] * wa + b[k] * wb;
            }
            return;
        }
        if (mode() == 1 || mode() == 4) {
            for (unsigned k = 0; k < dimensions; ++k)
                out[k] = previous[1 + k] + (next[1 + k] - previous[1 + k]) * t;
            return;
        }
        throw std::runtime_error("gmo: unsupported curve interpolation " + std::to_string(mode()));
    }
    copy(keys.back());
}

GmoModel GmoModel::parse(const std::vector<std::uint8_t>& bytes) {
    Parser parser(bytes);
    return parser.run();
}

}  // namespace psp
