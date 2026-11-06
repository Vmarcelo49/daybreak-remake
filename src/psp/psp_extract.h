#pragma once
// psp/psp_extract.h — `daybreak --extract-psp=<iso>`: the player's disc into psp-data/.
//
// Two stages, in this order, so a later track can add a converter without touching this
// one:
//
//   1. raw    every file in assets/psp/manifest.txt, inflated, hash-checked and written
//             to <psp-data>/psp/<pack path> exactly as the pack stores it. This is the
//             only stage that needs the ISO, and the only one that verifies anything.
//   2. convert each registered converter reads those raw files and writes the remake's own
//             formats under <psp-data>/data/... (psp_convert.h). Nothing here re-reads the
//             ISO, so a converter is a pure function of psp-data/psp/.
//
// The split is what makes the extractor reviewable: stage 1 is "did we get the right
// bytes", stage 2 is "what do those bytes mean".
#include <cstdint>
#include <functional>
#include <iosfwd>
#include <string>
#include <vector>

#include "psp/psp_manifest.h"

namespace psp {

struct PspExtractOptions {
    std::string isoPath;
    std::string dataDir;        // the `psp-data` root, absolute
    std::string packPath = "PSP_GAME/USRDIR/_pack/gzpack.pck";
    const PspManifest* manifest = nullptr;
    // The PC install, for the converters that start from the PC game's own tables (the moveset
    // converter reads the dispatch combo's frame table from it). Empty means "the caller had
    // none": such a converter reports and skips instead of failing the extraction.
    std::string installDir;
    bool convert = true;        // run the registered converters once the raw files land
};

struct PspExtractReport {
    std::vector<std::string> rawFiles;   // pack paths written, in manifest order
    std::vector<std::string> converted;  // dataDir-relative files the converters wrote
    std::uint64_t            bytes = 0;  // of the raw payloads
};

// Throws std::runtime_error with a message meant for the player when the image is not the
// game, the pack is missing or a file's hash differs from the manifest.
PspExtractReport extractPsp(const PspExtractOptions& options, std::ostream& log);

// ---------------------------------------------------------------------------------------
// The converter seam (design decision D-3a).
//
// A converter owns one output family and reads only <psp-data>/psp/ (and, when it needs the
// PC game's own tables, the install). `run` returns the paths it wrote, relative to the
// psp-data root, so the report can list them. Registering is a plain call; pspConverters() is
// the list the extractor walks, in registration order, and registerAllPspConverters()
// (psp_convert.cpp) is the one place the list is spelled out: the models, then the movesets,
// which read the converted model for the take count each frame table's phases refer to.
// ---------------------------------------------------------------------------------------
struct PspConverterContext {
    std::string    dataDir;      // the psp-data root: raw files are in <dataDir>/psp
    std::string    installDir;   // the PC install, when the caller had one; may be empty
    std::ostream*  log = nullptr;
};

using PspConverterFn = std::function<std::vector<std::string>(const PspConverterContext&)>;

struct PspConverter {
    std::string    name;
    PspConverterFn run;
};

void registerPspConverter(std::string name, PspConverterFn run);
const std::vector<PspConverter>& pspConverters();

// Defined in psp_convert.cpp: registers every converter this build has.
void registerAllPspConverters();

// `<dataDir>/psp/<pack path>`, the raw layout every converter and Track C reads.
std::string pspRawPath(const std::string& dataDir, const std::string& packPath);

}  // namespace psp
