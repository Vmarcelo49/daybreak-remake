// psp/psp_extract.cpp — ISO -> pack -> manifest-checked raw files -> converters.
#include "psp/psp_extract.h"

#include <filesystem>
#include <fstream>
#include <ostream>
#include <stdexcept>

#include "psp/iso9660.h"
#include "psp/psp_pack.h"
#include "update/crypto.h"

namespace fs = std::filesystem;

namespace psp {
namespace {

std::vector<PspConverter>& converterList() {
    static std::vector<PspConverter> converters;
    return converters;
}

void makeParentDirectories(const std::string& file) {
    const fs::path parent = fs::u8path(file).parent_path();
    if (parent.empty()) return;
    std::error_code error;
    fs::create_directories(parent, error);
    if (error) throw std::runtime_error("cannot create " + parent.u8string() + ": " + error.message());
}

void writeFile(const std::string& file, const std::vector<std::uint8_t>& bytes) {
    makeParentDirectories(file);
    std::ofstream stream(fs::u8path(file), std::ios::binary | std::ios::trunc);
    if (!stream) throw std::runtime_error("cannot write " + file);
    stream.write(reinterpret_cast<const char*>(bytes.data()), (std::streamsize)bytes.size());
    if (!stream) throw std::runtime_error("cannot write " + file);
}

std::string percent(std::uint64_t part, std::uint64_t whole) {
    if (!whole) return "0%";
    return std::to_string((unsigned)(part * 100 / whole)) + "%";
}

}  // namespace

std::string pspRawPath(const std::string& dataDir, const std::string& packPath) {
    const char last = dataDir.empty() ? '/' : dataDir.back();
    const std::string root = (last == '/' || last == '\\') ? dataDir : dataDir + "/";
    return root + "psp/" + packPath;
}

void registerPspConverter(std::string name, PspConverterFn run) {
    converterList().push_back({std::move(name), std::move(run)});
}

const std::vector<PspConverter>& pspConverters() { return converterList(); }

PspExtractReport extractPsp(const PspExtractOptions& options, std::ostream& log) {
    if (!options.manifest) throw std::runtime_error("psp: no manifest to verify against");
    if (options.isoPath.empty()) throw std::runtime_error("psp: no ISO given");

    log << "psp: reading " << options.isoPath << '\n';
    IsoImage iso = IsoImage::open(options.isoPath);
    PspPack pack = PspPack::open(iso, options.packPath);
    log << "psp: " << pack.size() << " files in " << options.packPath << '\n';

    PspExtractReport report;
    std::uint64_t total = 0;
    for (const PspManifestEntry& entry : options.manifest->entries) total += entry.size;

    std::vector<std::uint8_t> bytes;
    for (const PspManifestEntry& entry : options.manifest->entries) {
        const PspPackEntry* packed = pack.find(entry.path);
        if (!packed)
            throw std::runtime_error("psp: this disc has no " + entry.path +
                                     " — is it Higurashi Daybreak Portable Mega Edition?");
        std::string error;
        if (!pack.inflate(*packed, bytes, error))
            throw std::runtime_error("psp: " + entry.path + ": " + error);
        if (bytes.size() != entry.size)
            throw std::runtime_error("psp: " + entry.path + ": expected " +
                                     std::to_string(entry.size) + " bytes, inflated " +
                                     std::to_string(bytes.size()) +
                                     " — the dump is not the game this build expects");
        const std::string digest = update::sha256Hex(bytes.data(), bytes.size());
        if (digest != entry.sha256)
            throw std::runtime_error("psp: " + entry.path + ": sha256 " + digest +
                                     " does not match the manifest (" + entry.sha256 +
                                     ") — the dump is damaged or re-encoded");
        writeFile(pspRawPath(options.dataDir, entry.path), bytes);
        report.rawFiles.push_back(entry.path);
        report.bytes += bytes.size();
        log << "psp: " << entry.path << ' ' << bytes.size() << " bytes " << percent(report.bytes, total)
            << '\n';
    }
    log << "psp: " << report.rawFiles.size() << " files, " << report.bytes
        << " bytes verified against the manifest, under " << options.dataDir << "/psp\n";

    if (options.convert) {
        PspConverterContext context;
        context.dataDir = options.dataDir;
        context.installDir = options.installDir;
        context.log = &log;
        for (const PspConverter& converter : pspConverters()) {
            log << "psp: converting " << converter.name << '\n';
            const std::vector<std::string> written = converter.run(context);
            report.converted.insert(report.converted.end(), written.begin(), written.end());
            log << "psp: " << converter.name << " wrote " << written.size() << " file(s)\n";
        }
    }
    return report;
}

}  // namespace psp
