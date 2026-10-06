#pragma once
// platform/asset_client.h — asynchronous per-asset delivery from the host's own server.
//
// What this replaces: the pack loader (platform/web_pack.cpp) fetched one manifest's
// whole file list into /packs/ before anything could start, validated the set by
// "every file exists" and cached it by the manifest's text hash. That is the shape
// issue #4 asks to retire: it cannot express "only what this screen needs", it
// re-downloads everything when one asset changes, and it has no per-asset progress.
//
// What this is: one request per asset, validated against the catalog's sha256 and
// size, materialised into the virtual filesystem at the path the *unchanged* native
// asset layer already opens, and cached per asset by its own content hash — so a
// changed asset invalidates exactly itself and nothing else. Requests are
// outstanding across yields; `poll()` never blocks, and the only place that waits is
// the startup gate and the match barrier, both of which yield to the browser.
//
// PORT DECISION: the client, the cache identity and the readiness barrier are this
// issue's design. The rules behind the ids (archive precedence, case folding) are
// recovered and live in src/assets/ and webdelivery/daybreak_web/bundles.py; the
// server's catalog is the single source of truth for what an id's bytes must be.
#include <cstdint>
#include <string>
#include <vector>

#include "platform/web_assets.h"

namespace plat {

// Where the delivered assets are materialised: the MEMFS root, because the front
// end's own asset paths are install-relative ("data/title/back00.cnv") and the
// unchanged reader resolves them against the working directory.
inline const char* kWebAssetMount = "/";
// Content-addressed cache directory (IDBFS-backed where the browser allows).
inline const char* kWebAssetCacheDir = "/delivery-cache";

class AssetClient {
public:
    static AssetClient& instance();

    // Starts the startup group from `<base>/api/manifest/startup` (`base` empty =
    // same origin). Non-blocking; returns false when the client is already running.
    bool begin(const std::string& base = "");

    // Pumps completions and dispatches queued requests. Call it once per frame and
    // after every yield; it never blocks and never sleeps.
    void poll();

    // Yields to the browser until every gate asset is ready (or the set has failed
    // through its retry budget). Web-only; on native it returns false immediately.
    bool waitForGate();

    // The match group for a confirmed stage and its character+weapon combos. Slots
    // are `name[:costume]`, weapons are `%03d` bullet directories or `item/NN`.
    bool requestMatch(const std::string& stage, const std::vector<std::string>& slots,
                      const std::vector<std::string>& weapons);
    // Yields until the match group is resolved (ready or failed) — the VS barrier.
    bool waitForMatch();

    bool running() const { return running_; }
    bool catalogKnown() const { return !manifest_.version.empty(); }
    bool gateReady() const;
    bool startupComplete() const { return startup_.complete(); }
    bool failed() const { return failed_; }
    bool matchRequested() const { return matchRequested_; }
    bool matchReady() const { return matchRequested_ && match_.complete(); }
    bool cacheAvailable() const { return cacheAvailable_; }

    const std::string& error() const { return error_; }
    const WebAssetManifest& manifest() const { return manifest_; }
    const AssetProgress& startupProgress() const { return startup_; }
    const AssetProgress& matchProgress() const { return match_; }
    // Requests actually sent over the network this session (a warm cache shows 0).
    uint64_t networkRequests() const { return networkRequests_; }
    uint64_t bytesReceived() const { return bytesReceived_; }

private:
    AssetClient() = default;

    struct Item {
        WebAssetEntry entry;
        enum class State { Pending, Fetching, Ready, Failed } state = State::Pending;
        int attempts = 0;
    };

    // The request sets. Two are enough: the front end's startup group and the
    // confirmed match's group. A third set (a stage change mid-session) reuses the
    // match slot, because the previous match's assets stay materialised.
    std::vector<Item> startupItems_;
    std::vector<Item> matchItems_;
    WebAssetManifest  manifest_;
    AssetProgress     startup_;
    AssetProgress     match_;
    std::string       base_;
    std::string       error_;
    bool              running_ = false;
    bool              failed_ = false;
    bool              matchRequested_ = false;
    bool              cacheAvailable_ = false;
    bool              dirty_ = false;
    std::size_t       inflight_ = 0;
    std::size_t       completedSinceSync_ = 0;
    uint64_t          networkRequests_ = 0;
    uint64_t          bytesReceived_ = 0;
    int               lastReportedPercent_ = -1;
};

// Shorthand, like assetSource(): every call site wants the process-wide client.
inline AssetClient& assetClient() { return AssetClient::instance(); }

}  // namespace plat
