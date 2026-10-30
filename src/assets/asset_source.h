#pragma once
// assets/asset_source.h — the one seam through which the asset layer reaches bytes.
//
// Why it exists: the shipped game keeps its data inside the daybreakXX.dat archives, and
// the exe reads it from there — FUN_00653540 walks its bundle list and FUN_00662f70
// probes a name, first match winning. Reading the extracted tree instead is NOT the same
// thing: 983 names ship in more than one bundle and 445 of those groups differ in bytes,
// so a tree read can hand back a different model than the game does. That is measured,
// not assumed — tests/dat_bundle_bytes.cpp compares both against the oracle.
//
// With an install open, lookups are bundle-first; with none, every call falls through to
// the filesystem, so a checkout with only an extracted tree keeps working unchanged.
//
// Callers pass whatever path they already have (absolute, install-relative, or a bundle
// key): toKey() maps it, and a path outside the install has no key and goes to the
// filesystem. Nothing here caches decoded data — it answers where bytes come from, not
// what they mean.
#include <cstdint>
#include <string>
#include <vector>

#include "dat_bundle.h"

namespace fnd::assets {

class AssetSource {
public:
    static AssetSource& instance();

    // `installDir` is the directory holding daybreakXX.dat; missing bundles are
    // tolerated and counted by the caller through bundles(). Opening twice replaces the
    // previous install. Returns false only when nothing at all could be opened.
    bool openInstall(const std::string& installDir);
    void closeInstall();

    bool                bundlesOpen() const { return bundlesOpen_; }
    const DatBundleSet& bundles() const { return bundles_; }
    const std::string&  installDir() const { return installDir_; }

    // Walks up from `path` (file or directory) looking for the directory that contains
    // daybreak00.dat; "" when there is none. This is what lets an install be discovered
    // from the asset path a capture command line already carries, with no new flag.
    static std::string findInstallDir(const std::string& path);

    // Install-relative bundle key ("data/rika/01.X"), or "" when `path` is outside the
    // install and does not already look like a key.
    std::string toKey(const std::string& path) const;

    // Bundle first — exact, then ASCII-case-insensitive, the comparison the exe's bundle
    // index uses (__stricmp at 0x00663c20) — then the filesystem.
    bool exists(const std::string& path) const;
    bool read(const std::string& path, std::vector<uint8_t>& out) const;

    // First candidate that exists, or "" when none do. Use this instead of probing
    // several spellings yourself: a case-folding source resolves every spelling to the
    // same entry, so probing "x.X" and "x.x" separately loads one file twice (measured:
    // +1 model and +909 vertices on a case-insensitive filesystem, and now on every
    // platform through the bundle lookup).
    std::string resolve(const std::vector<std::string>& candidates) const;

    // Full keys of the entries directly inside bundle directory `dir`. Empty when that
    // directory is in no bundle, which is the caller's signal to fall back to
    // fs::directory_iterator. Order is bundle order then table order: stable across runs,
    // unlike the filesystem's, which matters because a caller picks the first match.
    std::vector<std::string> listDir(const std::string& dir) const;

private:
    AssetSource() = default;

    DatBundleSet bundles_;
    std::string  installDir_;   // normalized, no trailing separator
    bool         bundlesOpen_ = false;
};

// Shorthand: every call site wants the process-wide source, and passing one around would
// mean threading it through the header-only asset layer for no gain.
inline AssetSource& assetSource() { return AssetSource::instance(); }

}  // namespace fnd::assets
