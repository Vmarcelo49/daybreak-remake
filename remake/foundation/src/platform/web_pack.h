#pragma once
// Runtime asset-pack delivery for the web build.
//
// WHY this exists alongside --preload-file: preload bundles one monolithic
// .data that must fully download before main() runs, with no caching and no
// granularity. The release shape is per-pack HTTP fetch into the Emscripten
// virtual filesystem, cached by the browser's HTTP cache, with user-supplied
// data the repo never sees. The asset layer itself is untouched: once the
// files sit under /packs/, it opens them exactly as native opens disk.
//
// Manifest format (plain text, served over HTTP next to the files):
//   asset=<single CLI asset arg, e.g. --character=/packs/akane:0>
//   base=<URL files resolve against; defaults to the manifest's directory>
//   <relative path, one per line; mirrored to /packs/<path>>
// A scripts/make_pack.py generates these from an extracted tree; see docs.
#include <string>

namespace plat {

// URL query access for the web build (window.location.search). Empty when
// absent. Native stub returns "" — argv is the native mechanism.
std::string webQueryParam(const char* key);

// Downloads the manifest, then every listed file into /packs/. On success
// fills assetArg from the manifest's asset= line ("" when absent) and returns
// true. Web-only in practice; native builds return false ("packs are how the
// web reaches game data — native reads disk directly").
bool fetchWebPack(const std::string& manifestUrl, std::string& assetArg, std::string& error);

}  // namespace plat
