// Runtime web pack delivery; see web_pack.h for the why and the format.
#include "platform/web_pack.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <vector>

#if defined(__EMSCRIPTEN__)
#include <sys/stat.h>

#include <emscripten/emscripten.h>
#include <emscripten/fetch.h>

namespace plat {
namespace {

// Percent-encode anything outside the URL-safe set. Shift-JIS-derived texture
// names arrive here as UTF-8 (the asset layer already converted them), so this
// is UTF-8 bytes to %XX — exactly what the server decodes back to filenames.
// Scheme/host/query punctuation (:?&=#@) is legal in a URL and must survive:
// only the path bytes get encoded in practice.
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

bool fetchBytes(const std::string& url, std::vector<uint8_t>& out, std::string& error) {
    struct FetchWait {
        bool done = false;
        int status = 0;
        std::vector<uint8_t> data;
    };
    // fetch_wait() never resolved here (HTTP 0 on every attempt, exact cause
    // unknown), so completion goes through callbacks pumped by the same yield
    // the adapter/device waits already rely on.
    struct Callbacks {
        static void onSuccess(emscripten_fetch_t* fetch) {
            auto* w = static_cast<FetchWait*>(fetch->userData);
            w->status = (int)fetch->status;
            if (fetch->status == 200) w->data.assign(fetch->data, fetch->data + fetch->numBytes);
            w->done = true;
            emscripten_fetch_close(fetch);
        }
        static void onError(emscripten_fetch_t* fetch) {
            auto* w = static_cast<FetchWait*>(fetch->userData);
            w->status = (int)fetch->status;
            w->done = true;
            emscripten_fetch_close(fetch);
        }
    };
    FetchWait w;
    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    const std::string encoded = urlEncodePath(url);
    std::strncpy(attr.requestMethod, "GET", sizeof(attr.requestMethod) - 1);
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = Callbacks::onSuccess;
    attr.onerror = Callbacks::onError;
    attr.userData = &w;
    emscripten_fetch(&attr, encoded.c_str());
    while (!w.done) emscripten_sleep(0);
    if (w.status != 200) {
        error = "fetch " + url + ": HTTP " + std::to_string(w.status);
        return false;
    }
    out = std::move(w.data);
    return true;
}

// mkdir -p over MEMFS: the pack mirror needs its subdirectories before files.
bool makeDirs(const std::string& path, std::string& error) {
    std::string cur;
    for (size_t i = 1; i < path.size(); ++i) {  // skip the leading '/'
        if (path[i] != '/') continue;
        cur = path.substr(0, i);
        if (mkdir(cur.c_str(), 0755) != 0 && errno != EEXIST) {
            error = "mkdir " + cur;
            return false;
        }
    }
    return true;
}

std::string dirOf(const std::string& url) {
    const size_t slash = url.find_last_of('/');
    return slash == std::string::npos ? std::string() : url.substr(0, slash + 1);
}

uint32_t fnv1a(const uint8_t* data, size_t n) {
    uint32_t h = 2166136261u;
    for (size_t i = 0; i < n; ++i) {
        h ^= data[i];
        h *= 16777619u;
    }
    return h;
}

std::string hashName(const std::string& manifestUrl) {
    char buf[32];
    std::snprintf(buf, sizeof buf, "/packs/.hash_%08x", fnv1a(
                      reinterpret_cast<const uint8_t*>(manifestUrl.data()), manifestUrl.size()));
    return buf;
}

}  // namespace

// IndexedDB persistence (IDBFS): repeat visits skip the download entirely.
// Best-effort by design — if the mount, populate, or write-back fails, the
// session continues on MEMFS exactly as before, just uncached.
static volatile int g_syncDone = 0;
static volatile int g_syncErr = 0;
static bool g_packsMounted = false;
static bool g_idbfs = false;

extern "C" void EMSCRIPTEN_KEEPALIVE webPackSyncDone(int err) {
    g_syncErr = err;
    g_syncDone = 1;
}

namespace {

// One mount per boot; a missing IDBFS (flag not linked, storage unavailable)
// degrades to an uncached session rather than failing the run.
void ensurePacksMounted() {
    if (g_packsMounted) return;
    g_packsMounted = true;
    g_idbfs = EM_ASM_INT({
        try {
            if (typeof IDBFS === 'undefined') return 0;
            try { FS.mkdir('/packs'); } catch (e) {}
            FS.mount(IDBFS, {}, '/packs');
            return 1;
        } catch (e) { return 0; }
    }) != 0;
}

bool idbfsSync(bool populate, std::string& error) {
    if (!g_idbfs) return true;
    g_syncDone = 0;
    g_syncErr = 0;
    EM_ASM({ FS.syncfs($0, function(err) { _webPackSyncDone(err ? 1 : 0); }); },
           populate ? 1 : 0);
    while (!g_syncDone) emscripten_sleep(0);
    if (g_syncErr) {
        error = "IDBFS sync failed";
        return false;
    }
    return true;
}

// True when every listed file already sits in /packs/ under this manifest's
// hash: same manifest text plus all files present. Existence (not bytes) is
// the check — eviction wipes the store wholesale, so a full present set
// means a valid cache; anything else refetches everything, simply.
bool cacheValid(const std::vector<std::string>& files, const std::string& hashPath,
                uint32_t manifestHash) {
    char buf[16];
    std::FILE* f = std::fopen(hashPath.c_str(), "rb");
    if (!f) return false;
    const size_t got = std::fread(buf, 1, sizeof buf, f);
    std::fclose(f);
    uint32_t stored = 0;
    if (got == 0 || std::sscanf(buf, "%x", &stored) != 1 || stored != manifestHash)
        return false;
    for (const std::string& rel : files) {
        std::FILE* g = std::fopen((std::string("/packs/") + rel).c_str(), "rb");
        if (!g) return false;
        std::fclose(g);
    }
    return true;
}

void writeCacheHash(const std::string& hashPath, uint32_t manifestHash) {
    char buf[16];
    std::snprintf(buf, sizeof buf, "%08x", manifestHash);
    if (std::FILE* f = std::fopen(hashPath.c_str(), "wb")) {
        std::fwrite(buf, 1, 8, f);
        std::fclose(f);
    }
}

}  // namespace

std::string webQueryParam(const char* key) {
    char* search = (char*)EM_ASM_PTR({ return stringToNewUTF8(window.location.search); });
    const std::string query = search ? search : "";
    free(search);
    // ?pack=<url>&asset=<arg>: values run to the next '&' or end. Percent and
    // '+' decoding matches what the browser put there.
    size_t pos = (!query.empty() && query[0] == '?') ? 1 : 0;
    while (pos < query.size()) {
        const size_t eq = query.find('=', pos);
        if (eq == std::string::npos) break;
        size_t end = query.find('&', eq + 1);
        if (end == std::string::npos) end = query.size();
        if (query.compare(pos, eq - pos, key) == 0) {
            std::string out;
            for (size_t i = eq + 1; i < end; ++i) {
                if (query[i] == '+') {
                    out += ' ';
                } else if (query[i] == '%' && i + 2 < end) {
                    out += (char)(std::stoi(query.substr(i + 1, 2), nullptr, 16) & 0xFF);
                    i += 2;
                } else {
                    out += query[i];
                }
            }
            return out;
        }
        pos = end + 1;
    }
    return {};
}

bool fetchWebPack(const std::string& manifestUrl, std::string& assetArg, std::string& error) {
    std::printf("[pack] fetching %s\n", manifestUrl.c_str());
    ensurePacksMounted();
    if (g_idbfs) {
        // Best-effort populate: a failed sync just means "fetch everything",
        // never a failed run.
        std::string syncError;
        if (!idbfsSync(true, syncError))
            std::fprintf(stderr, "[pack] warning: %s\n", syncError.c_str());
    }
    std::vector<uint8_t> manifest;
    if (!fetchBytes(manifestUrl, manifest, error)) return false;
    const uint32_t manifestHash = fnv1a(manifest.data(), manifest.size());

    std::string base = dirOf(manifestUrl);
    std::string asset;
    std::vector<std::string> files;
    size_t lineStart = 0;
    const std::string text(manifest.begin(), manifest.end());
    while (lineStart <= text.size()) {
        size_t lineEnd = text.find('\n', lineStart);
        if (lineEnd == std::string::npos) lineEnd = text.size();
        std::string line = text.substr(lineStart, lineEnd - lineStart);
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (!line.empty() && line[0] != '#') {
            if (line.rfind("asset=", 0) == 0)
                asset = line.substr(6);
            else if (line.rfind("base=", 0) == 0)
                base = line.substr(5);
            else
                files.push_back(line);
        }
        if (lineEnd == text.size()) break;
        lineStart = lineEnd + 1;
    }
    if (files.empty()) {
        error = "pack manifest lists no files: " + manifestUrl;
        return false;
    }

    // Same manifest text plus every file present means the IndexedDB copy is
    // current: skip all downloads. Anything else refetches everything, simply.
    const std::string hashPath = hashName(manifestUrl);
    if (g_idbfs && cacheValid(files, hashPath, manifestHash)) {
        std::printf("[pack] cache hit: %zu files already in /packs/\n", files.size());
        assetArg = asset;
        return true;
    }

    size_t bytes = 0;
    for (const std::string& rel : files) {
        const std::string dest = std::string("/packs/") + rel;
        if (!makeDirs(dest, error)) return false;
        std::vector<uint8_t> data;
        if (!fetchBytes(base + rel, data, error)) return false;
        std::FILE* f = std::fopen(dest.c_str(), "wb");
        if (!f) {
            error = "cannot write " + dest;
            return false;
        }
        const size_t wrote = std::fwrite(data.data(), 1, data.size(), f);
        std::fclose(f);
        if (wrote != data.size()) {
            error = "short write " + dest;
            return false;
        }
        bytes += data.size();
    }
    std::printf("[pack] %zu files, %.1f MB -> /packs/ from %s\n", files.size(),
                (double)bytes / 1048576.0, manifestUrl.c_str());
    if (g_idbfs) {
        writeCacheHash(hashPath, manifestHash);
        std::string syncError;
        if (!idbfsSync(false, syncError))
            std::fprintf(stderr, "[pack] warning: %s (session continues uncached)\n",
                         syncError.c_str());
    }
    assetArg = asset;
    return true;
}

}  // namespace plat
#else   // native: packs are how the web reaches game data; native reads disk.

#include <string>

namespace plat {

std::string webQueryParam(const char*) { return {}; }

bool fetchWebPack(const std::string&, std::string&, std::string& error) {
    error = "asset packs are a web-only path; native builds read game data from disk";
    return false;
}

}  // namespace plat
#endif
