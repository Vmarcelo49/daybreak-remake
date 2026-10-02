// verify_textures — walks an extracted asset tree and checks the texture path.
//
//   verify_textures <assetRoot> [--misses]
//
// Two independent passes:
//   1. every .cnv in the tree is classified (image / audio / undecodable) and every
//      image is fully decoded, so a format regression cannot hide behind a model
//      that simply never references it;
//   2. every model is loaded and every material texture it references is resolved
//      through TextureCache, which is where the Shift-JIS to UTF-8 lookup lives.
//
// Build: see build.sh (needs cnv.h + sjis_table.h next to it).

#define XMODEL_IMPLEMENTATION
#include "../xmodel.h"

#define CNV_IMPLEMENTATION
#include "../cnv.h"

#include <algorithm>
#include <cstdio>
#include <filesystem>
#include <map>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace {

struct Totals {
    int cnvImages = 0, cnvAudio = 0, cnvBad = 0;
    long long imagePixels = 0;
    std::map<std::string, int> badCnv;
    int models = 0, modelFailures = 0;
    int refs = 0, resolved = 0, missed = 0;
    std::map<std::string, int> missedNames;
    std::map<std::string, int> missDirs;
    int bpp24Header = 0, bpp32Header = 0, otherBppHeader = 0;
    int compressedRejected = 0;
};

std::string jsonEscape(const std::string& s) {
    std::string o;
    for (unsigned char c : s) {
        if (c >= 0x20 && c < 0x7F) o += (char)c;
        else { char b[8]; std::snprintf(b, sizeof b, "\\x%02x", c); o += b; }
    }
    return o;
}

void scanCnv(const fs::path& root, Totals& t) {
    for (const auto& e : fs::recursive_directory_iterator(root)) {
        if (!e.is_regular_file()) continue;
        std::string ext = e.path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(),
                       [](unsigned char c) { return (char)std::tolower(c); });
        if (ext != ".cnv") continue;

        std::FILE* f = std::fopen(e.path().string().c_str(), "rb");
        if (!f) continue;
        std::fseek(f, 0, SEEK_END);
        long n = std::ftell(f);
        std::fseek(f, 0, SEEK_SET);
        std::vector<uint8_t> bytes((size_t)std::max(0L, n));
        size_t got = bytes.empty() ? 0 : std::fread(bytes.data(), 1, bytes.size(), f);
        std::fclose(f);
        bytes.resize(got);

        if (!xm::isCnvImage(bytes.data(), bytes.size())) {
            // Distinguish "audio" from "broken" the same way the header does.
            bool audio = false;
            if (bytes.size() >= 16) {
                uint32_t ch = (uint32_t)bytes[0] | ((uint32_t)bytes[1] << 8);
                uint32_t sr = (uint32_t)bytes[4] | ((uint32_t)bytes[5] << 8) |
                              ((uint32_t)bytes[6] << 16) | ((uint32_t)bytes[7] << 24);
                uint32_t bits = (uint32_t)bytes[14] | ((uint32_t)bytes[15] << 8);
                audio = (ch == 1 || ch == 2) &&
                        (sr == 11025 || sr == 22050 || sr == 44100 || sr == 48000) &&
                        (bits == 8 || bits == 16);
            }
            if (audio) { ++t.cnvAudio; continue; }
            ++t.cnvBad;
            if (t.badCnv.size() < 10) t.badCnv[e.path().string()] = (int)bytes.size();
            continue;
        }

        try {
            xm::CnvImage img = xm::decodeCnvImage(bytes.data(), bytes.size());
            ++t.cnvImages;
            t.imagePixels += (long long)img.width * img.height;
            switch (bytes[0]) {
                case 24: ++t.bpp24Header; break;
                case 32: ++t.bpp32Header; break;
                default: ++t.otherBppHeader; break;
            }
        } catch (const std::exception& ex) {
            ++t.cnvBad;
            if (t.badCnv.size() < 10) t.badCnv[e.path().string()] = (int)bytes.size();
            if (std::string(ex.what()).find("compressed") != std::string::npos) ++t.compressedRejected;
        }
    }
}

void scanModels(const fs::path& root, Totals& t, bool printMisses) {
    std::vector<fs::path> models;
    for (const auto& e : fs::recursive_directory_iterator(root)) {
        if (!e.is_regular_file()) continue;
        std::string ext = e.path().extension().string();
        std::transform(ext.begin(), ext.end(), ext.begin(),
                       [](unsigned char c) { return (char)std::tolower(c); });
        if (ext == ".x") models.push_back(e.path());
    }
    std::sort(models.begin(), models.end());

    std::map<std::string, xm::TextureCache> caches;   // one per directory
    for (const fs::path& p : models) {
        ++t.models;
        xm::Model m;
        try {
            m = xm::loadFile(p.string());
        } catch (const std::exception& ex) {
            ++t.modelFailures;
            std::fprintf(stderr, "load failed: %s: %s\n", p.string().c_str(), ex.what());
            continue;
        }
        const std::string dir = p.parent_path().string() + "/";
        auto it = caches.find(dir);
        if (it == caches.end()) it = caches.emplace(dir, xm::TextureCache(dir)).first;

        for (const xm::Mesh& mesh : m.meshes) {
            for (const xm::Material& mat : mesh.materials) {
                if (mat.texture.empty()) continue;
                ++t.refs;
                if (it->second.get(mat.texture)) {
                    ++t.resolved;
                } else {
                    ++t.missed;
                    t.missedNames[mat.texture] += 1;
                    t.missDirs[p.parent_path().filename().string()] += 1;
                    if (printMisses)
                        std::printf("  miss: %s  <- %s\n", jsonEscape(mat.texture).c_str(),
                                    p.string().c_str());
                }
            }
        }
    }
}

}  // namespace

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "usage: verify_textures <assetRoot> [--misses]\n");
        return 2;
    }
    const fs::path root = argv[1];
    bool printMisses = false;
    for (int i = 2; i < argc; ++i)
        if (std::string(argv[i]) == "--misses") printMisses = true;

    if (!fs::exists(root)) { std::fprintf(stderr, "no such path: %s\n", root.c_str()); return 2; }

    Totals t;
    scanCnv(root, t);
    std::printf("=== .cnv pass ===\n");
    std::printf("  images decoded : %d  (%.1f M pixels)\n", t.cnvImages,
                (double)t.imagePixels / 1e6);
    std::printf("  audio .cnv     : %d  (same extension, different payload)\n", t.cnvAudio);
    std::printf("  undecodable    : %d\n", t.cnvBad);
    std::printf("  declared bpp   : 24 -> %d, 32 -> %d, other -> %d\n",
                t.bpp24Header, t.bpp32Header, t.otherBppHeader);
    for (const auto& kv : t.badCnv)
        std::printf("      bad: %s (%d bytes)\n", kv.first.c_str(), kv.second);
    if (t.compressedRejected)
        std::printf("  compressed     : %d rejected\n", t.compressedRejected);

    scanModels(root, t, printMisses);
    std::printf("=== model texture pass ===\n");
    std::printf("  models loaded  : %d (failures %d)\n", t.models, t.modelFailures);
    std::printf("  texture refs   : %d, resolved %d (%.2f%%), missed %d\n", t.refs, t.resolved,
                t.refs ? 100.0 * t.resolved / t.refs : 0.0, t.missed);
    std::printf("  distinct misses: %zu\n", t.missedNames.size());
    if (!t.missedNames.empty() && !printMisses) {
        std::printf("  (first few; rerun with --misses for the full list)\n");
        int shown = 0;
        for (const auto& kv : t.missedNames) {
            if (shown++ >= 8) break;
            std::printf("      %s x%d\n", jsonEscape(kv.first).c_str(), kv.second);
        }
    }
    if (!t.missDirs.empty()) {
        std::printf("  misses by directory (where a texture is not shipped beside its model):\n");
        for (const auto& kv : t.missDirs)
            std::printf("      %-16s %d\n", kv.first.c_str(), kv.second);
    }
    return (t.cnvBad == 0 && t.modelFailures == 0) ? 0 : 1;
}
