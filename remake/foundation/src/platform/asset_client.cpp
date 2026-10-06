// platform/asset_client.cpp — see the header for what this replaces and why.
//
// Shape of the machine: `poll()` drains whatever the browser callbacks finished,
// then dispatches as many queued requests as the in-flight budget allows. It never
// waits, so the frame loop can call it every frame; the two places that do wait
// (`waitForGate`, `waitForMatch`) yield with emscripten_sleep(0), which is what keeps
// the page's own event loop alive while wasm is parked on a barrier.
#include "platform/asset_client.h"

#include <cstdio>
#include <cstring>

#if defined(__EMSCRIPTEN__)

#include <sys/stat.h>

#include <emscripten/emscripten.h>
#include <emscripten/fetch.h>

#include <cerrno>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

namespace plat {
namespace {

// How many requests may be outstanding at once. Six is what a browser will actually
// open per origin, so this keeps the transfer busy without queueing behind itself.
constexpr std::size_t kMaxInflight = 6;

// One retry per asset. A hash mismatch is either a truncated transfer or a server
// that changed under the catalog; both deserve one more try and neither deserves a
// loop while a player waits.
constexpr int kMaxAttempts = 2;

// Percent-encode a logical asset id for the API path. Ids are UTF-8 (the CP932 names
// were decoded on the host) and may carry characters a URL cannot.
std::string urlEncodePath(const std::string& path) {
    static const char* hex = "0123456789ABCDEF";
    std::string out;
    out.reserve(path.size());
    for (unsigned char c : path) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') ||
            c == '-' || c == '_' || c == '.' || c == '~' || c == '/' || c == ':' ||
            c == '?' || c == '&' || c == '=' || c == '#' || c == '@')
            out += (char)c;
        else {
            out += '%';
            out += hex[c >> 4];
            out += hex[c & 15];
        }
    }
    return out;
}

bool makeDirs(const std::string& path) {
    std::string cur;
    for (std::size_t i = 1; i < path.size(); ++i) {
        if (path[i] != '/') continue;
        cur = path.substr(0, i);
        if (mkdir(cur.c_str(), 0755) != 0 && errno != EEXIST) return false;
    }
    return true;
}

bool writeFile(const std::string& path, const std::vector<uint8_t>& data) {
    if (!makeDirs(path)) return false;
    std::FILE* f = std::fopen(path.c_str(), "wb");
    if (!f) return false;
    const std::size_t wrote = data.empty() ? 0 : std::fwrite(data.data(), 1, data.size(), f);
    std::fclose(f);
    return wrote == data.size();
}

// Put one asset where the asset layer will look for it.
//
// The catalogued spelling becomes a file; the other spellings this port probes become
// symlinks to it (webAssetCaseVariants carries the measured list and the reason). The
// native layer resolves those spellings through the bundle index, which folds ASCII case
// like the exe's __stricmp; a delivered tree is a plain filesystem, which does not, so
// without the aliases a loader misses a file that is sitting right there.
bool materialize(const std::string& id, const std::vector<uint8_t>& data) {
    const std::string target = webAssetTargetPath(kWebAssetMount, id);
    if (target.empty() || !writeFile(target, data)) return false;
    // Every other spelling this port probes becomes a symlink to the same bytes.
    for (const std::string& variant : webAssetCaseVariants(id)) {
        if (variant == id) continue;
        const std::string alias = webAssetTargetPath(kWebAssetMount, variant);
        if (alias.empty() || alias == target || !makeDirs(alias)) continue;
        if (symlink(target.c_str(), alias.c_str()) != 0 && errno != EEXIST) {
            std::fprintf(stderr, "[delivery] no case alias %s -> %s (%s)\n", variant.c_str(),
                         id.c_str(), std::strerror(errno));
        }
    }
    return true;
}

bool readFile(const std::string& path, std::vector<uint8_t>& out) {
    std::FILE* f = std::fopen(path.c_str(), "rb");
    if (!f) return false;
    std::fseek(f, 0, SEEK_END);
    const long size = std::ftell(f);
    std::fseek(f, 0, SEEK_SET);
    if (size < 0) {
        std::fclose(f);
        return false;
    }
    out.resize((std::size_t)size);
    const std::size_t got = size ? std::fread(out.data(), 1, (std::size_t)size, f) : 0;
    std::fclose(f);
    out.resize(got);
    return got == (std::size_t)size;
}

// One transfer. The callback fills it; poll() drains it and deletes it.
struct Fetch {
    int  item = -1;          // index into the owning set, -1 for a manifest request
    bool manifest = false;
    bool startupSet = true;
    bool ok = false;
    long status = 0;
    std::vector<uint8_t> data;
};

// Filled by the browser callbacks and drained by poll(). Single-threaded wasm, so a
// plain vector is enough; the callbacks only run while the runtime is yielding.
std::vector<Fetch*> g_completed;

void startFetch(const std::string& url, bool manifest, bool startupSet, int item) {
    Fetch* job = new Fetch();
    job->manifest = manifest;
    job->startupSet = startupSet;
    job->item = item;

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    std::strncpy(attr.requestMethod, "GET", sizeof(attr.requestMethod) - 1);
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.userData = job;
    // fetch_wait() never resolved in this setup (web_pack.cpp measured HTTP 0 on every
    // attempt), so completion goes through these callbacks and the yield loop.
    attr.onsuccess = [](emscripten_fetch_t* f) {
        auto* j = static_cast<Fetch*>(f->userData);
        j->status = (long)f->status;
        j->ok = f->status == 200;
        if (j->ok) j->data.assign(f->data, f->data + f->numBytes);
        g_completed.push_back(j);
        emscripten_fetch_close(f);
    };
    attr.onerror = [](emscripten_fetch_t* f) {
        auto* j = static_cast<Fetch*>(f->userData);
        j->status = (long)f->status;
        g_completed.push_back(j);
        emscripten_fetch_close(f);
    };
    emscripten_fetch(&attr, urlEncodePath(url).c_str());
}

// IDBFS completion plumbing: the browser calls back once per sync.
volatile int g_syncDone = 0;
volatile int g_syncErr = 0;

extern "C" void EMSCRIPTEN_KEEPALIVE webAssetSyncDone(int err) {
    g_syncErr = err;
    g_syncDone = 1;
}

// Mount the content-addressed cache once. Best effort by design: a browser that
// refuses IndexedDB (private mode, quota) gets an uncached session, never a failed
// run — the plan's "treat browser persistence as best effort".
bool ensureCacheMounted() {
    static bool attempted = false;
    static bool mounted = false;
    if (!attempted) {
        attempted = true;
        mounted = EM_ASM_INT({
            try {
                if (typeof IDBFS === 'undefined') return 0;
                try { FS.mkdir('/delivery-cache'); } catch (e) {}
                FS.mount(IDBFS, {}, '/delivery-cache');
                return 1;
            } catch (e) { return 0; }
        }) != 0;
        if (mounted) std::printf("[delivery] per-asset cache: IndexedDB mounted\n");
        else std::printf("[delivery] per-asset cache unavailable; this session is uncached\n");
    }
    return mounted;
}

bool syncCache(bool populate) {
    g_syncDone = 0;
    g_syncErr = 0;
    EM_ASM({ FS.syncfs($0, function(err) { _webAssetSyncDone(err ? 1 : 0); }); },
           populate ? 1 : 0);
    while (!g_syncDone) emscripten_sleep(0);
    return g_syncErr == 0;
}

std::string cachePathFor(const std::string& sha256) {
    return std::string(kWebAssetCacheDir) + "/" + sha256;
}

}  // namespace

AssetClient& AssetClient::instance() {
    static AssetClient client;
    return client;
}

bool AssetClient::begin(const std::string& base) {
    if (running_) return false;
    running_ = true;
    base_ = base;
    while (!base_.empty() && base_.back() == '/') base_.pop_back();
    cacheAvailable_ = ensureCacheMounted();
    if (cacheAvailable_) {
        // Populate first: a warm session must not re-request a single byte.
        if (!syncCache(true))
            std::fprintf(stderr, "[delivery] warning: cache populate failed\n");
    }
    ++networkRequests_;
    startFetch(base_ + "/api/manifest/startup", true, true, -1);
    return true;
}

void AssetClient::poll() {
    if (!running_) return;

    // ---------------------------------------------------------------- completions
    for (Fetch* job : g_completed) {
        if (job->manifest) {
            WebAssetManifest parsed;
            std::string parseError;
            if (!job->ok) {
                error_ = "manifest request failed (HTTP " + std::to_string(job->status) + ")";
                failed_ = true;
            } else if (!parseAssetManifest(std::string(job->data.begin(), job->data.end()),
                                           parsed, parseError)) {
                error_ = parseError;
                failed_ = true;
            } else if (job->startupSet) {
                manifest_ = parsed;
                startupItems_.clear();
                startup_ = AssetProgress{};
                startup_.total = manifest_.entries.size();
                startup_.bytesTotal = manifest_.transferBytes();
                for (const WebAssetEntry& entry : manifest_.entries) {
                    Item item;
                    item.entry = entry;
                    startupItems_.push_back(item);
                }
                std::printf("[delivery] startup group: %zu assets, %.1f MB "
                            "(%zu gate assets), catalog %s\n",
                            startup_.total, double(startup_.bytesTotal) / 1048576.0,
                            manifest_.gateCount(), manifest_.version.c_str());
            } else {
                match_.total = parsed.entries.size();
                match_.bytesTotal = parsed.transferBytes();
                matchItems_.clear();
                for (const WebAssetEntry& entry : parsed.entries) {
                    Item item;
                    item.entry = entry;
                    matchItems_.push_back(item);
                }
                std::printf("[delivery] %s: %zu assets, %.1f MB\n", parsed.group.c_str(),
                            match_.total, double(match_.bytesTotal) / 1048576.0);
            }
        } else {
            const bool startupSet = job->startupSet;
            std::vector<Item>& items = startupSet ? startupItems_ : matchItems_;
            AssetProgress& progress = startupSet ? startup_ : match_;
            if (inflight_) --inflight_;
            if (progress.inflight) --progress.inflight;

            if (job->item >= 0 && (std::size_t)job->item < items.size()) {
                Item& item = items[(std::size_t)job->item];
                // Validate before anything reaches the filesystem: the catalog's size
                // and sha256 are the contract, and a mismatch is a failed asset, not a
                // corrupt file the loaders would later read.
                const bool sizeOk = job->ok && job->data.size() == item.entry.size;
                const bool hashOk = sizeOk && sha256Hex(job->data) == item.entry.sha256;
                if (hashOk) {
                    bytesReceived_ += job->data.size();
                    if (materialize(item.entry.id, job->data)) {
                        if (cacheAvailable_ &&
                            writeFile(cachePathFor(item.entry.sha256), job->data)) {
                            dirty_ = true;
                            ++completedSinceSync_;
                        }
                        item.state = Item::State::Ready;
                        ++progress.ready;
                        progress.bytesDone += item.entry.transferSize();
                    } else {
                        item.state = item.attempts < kMaxAttempts ? Item::State::Pending
                                                                  : Item::State::Failed;
                        if (item.state == Item::State::Failed) {
                            ++progress.failed;
                            progress.bytesDone += item.entry.transferSize();
                            std::fprintf(stderr, "[delivery] cannot write %s\n",
                                         item.entry.id.c_str());
                        }
                    }
                } else {
                    item.state = item.attempts < kMaxAttempts ? Item::State::Pending
                                                              : Item::State::Failed;
                    if (item.state == Item::State::Failed) {
                        ++progress.failed;
                        progress.bytesDone += item.entry.transferSize();
                        std::fprintf(stderr,
                                     "[delivery] %s: HTTP %ld, %zu bytes, hash %s — giving up\n",
                                     item.entry.id.c_str(), job->status, job->data.size(),
                                     sizeOk ? "mismatch" : "check");
                    }
                }
            }
        }
        delete job;
    }
    g_completed.clear();

    // -------------------------------------------------------------------- reports
    // Progress is the feature (issue #4 asks for visible progress), so these lines are
    // the deliverable rather than a debug aid — and they are throttled to ten per
    // group so a slow link cannot flood the console.
    if (startup_.total) {
        const int percent = int(100 * (startup_.ready + startup_.failed) / startup_.total);
        if (percent / 10 != lastReportedPercent_ / 10) {
            lastReportedPercent_ = percent;
            std::printf("%s\n", startup_.line(manifest_.group.empty() ? "startup"
                                                                      : manifest_.group).c_str());
        }
    }

    // ------------------------------------------------------------------- dispatch
    const auto dispatch = [&](std::vector<Item>& items, AssetProgress& progress,
                              bool startupSet) {
        // Gate assets go first. The manifest is in id order, which puts BGM and the
        // movie — fetched at startup but explicitly not part of the gate — ahead of the
        // title and menu art the first usable screen is waiting for; with a six-request
        // budget that ordering delayed the gate by everything queued in front of it
        // (measured: 140.3 MB received by the time the gate was met, against a declared
        // gate of 98.1 MB). Two passes make the gate the priority and leave the optional
        // startup assets to fill the remaining slots.
        for (int pass = 0; pass < 2; ++pass) {
            const bool wantGate = pass == 0;
            for (std::size_t i = 0; i < items.size(); ++i) {
            Item& item = items[i];
            if (item.state != Item::State::Pending) continue;
            if (item.entry.gate != wantGate) continue;
            if (inflight_ >= kMaxInflight) return;
            // A cached copy is content-addressed: same hash means same bytes, so a warm
            // session answers without a request and without re-validating the server.
            if (cacheAvailable_) {
                std::vector<uint8_t> cached;
                if (readFile(cachePathFor(item.entry.sha256), cached) &&
                    cached.size() == item.entry.size &&
                    sha256Hex(cached) == item.entry.sha256) {
                    if (materialize(item.entry.id, cached)) {
                        item.state = Item::State::Ready;
                        ++progress.ready;
                        ++progress.cached;
                        progress.bytesDone += item.entry.transferSize();
                        continue;
                    }
                }
            }
            item.state = Item::State::Fetching;
            ++item.attempts;
            ++inflight_;
            ++progress.inflight;
            ++networkRequests_;
            startFetch(base_ + "/api/asset/" + item.entry.id, false, startupSet, (int)i);
            }
        }
    };
    dispatch(startupItems_, startup_, true);
    if (matchRequested_) dispatch(matchItems_, match_, false);

    // Write the cache back in batches: one IndexedDB transaction per asset would make
    // the store the bottleneck on a fast link, and the whole point of the per-asset
    // cache is that a later session skips the network entirely.
    const bool setSettled = (startup_.total && startup_.complete()) ||
                            (matchRequested_ && match_.total && match_.complete());
    if (dirty_ && cacheAvailable_ && (completedSinceSync_ >= 16 || setSettled)) {
        dirty_ = false;
        completedSinceSync_ = 0;
        if (!syncCache(false))
            std::fprintf(stderr, "[delivery] warning: cache write-back failed\n");
    }
}

bool AssetClient::waitForGate() {
    while (running_ && !gateReady() && !failed_) {
        poll();
        emscripten_sleep(0);
    }
    return gateReady();
}

bool AssetClient::waitForMatch() {
    // `match_.complete()` is false while the manifest is still in flight (an empty set is
    // not complete), so this cannot return before the set is known.
    while (matchRequested_ && !matchReady() && !failed_) {
        poll();
        emscripten_sleep(0);
    }
    return matchReady();
}

bool AssetClient::requestMatch(const std::string& stage,
                               const std::vector<std::string>& slots,
                               const std::vector<std::string>& weapons) {
    if (!running_ || matchRequested_) return false;
    matchRequested_ = true;
    std::string url = base_ + "/api/manifest/match?stage=" + urlEncodePath(stage);
    for (const std::string& slot : slots) url += "&slot=" + urlEncodePath(slot);
    for (const std::string& weapon : weapons) url += "&weapon=" + urlEncodePath(weapon);
    ++networkRequests_;
    startFetch(url, true, false, -1);
    return true;
}

bool AssetClient::gateReady() const {
    std::size_t resolved = 0, gate = 0;
    for (const Item& item : startupItems_) {
        if (!item.entry.gate) continue;
        ++gate;
        // A failed gate asset is resolved too: the barrier exists to stop a battle
        // starting on missing assets, not to hang the front end forever on one 404.
        if (item.state == Item::State::Ready || item.state == Item::State::Failed) ++resolved;
    }
    return gate > 0 && resolved == gate;
}

}  // namespace plat

#else   // native: delivery is the web's problem; the native path reads its own install.

#include <string>

namespace plat {

AssetClient& AssetClient::instance() {
    static AssetClient client;
    return client;
}

bool AssetClient::begin(const std::string&) { return false; }
void AssetClient::poll() {}
bool AssetClient::waitForGate() { return false; }
bool AssetClient::waitForMatch() { return false; }
bool AssetClient::requestMatch(const std::string&, const std::vector<std::string>&,
                               const std::vector<std::string>&) {
    return false;
}
bool AssetClient::gateReady() const { return false; }

}  // namespace plat

#endif
