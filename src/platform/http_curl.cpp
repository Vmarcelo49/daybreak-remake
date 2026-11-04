// platform/http_curl.cpp — the Linux HTTP client: libcurl loaded at run time, never linked.
//
// Why dlopen: every desktop distribution ships libcurl, but its development package is not
// something a player has, and linking it would make the game depend on a library version we
// do not ship. Loading it by name keeps the binary self-contained; when neither soname
// loads, the updater reports Unavailable and the player downloads the release by hand.
//
// Redirects are followed here rather than by curl, so every hop passes allowedUrl: that is
// what turns an https -> http redirect into Refused instead of a downgraded download.
#include "platform/http.h"

#include <dlfcn.h>

#include <cstdlib>
#include <cstring>
#include <string>

#include "curl/curl.h"

namespace plat {
namespace {

struct CurlApi {
    CURLcode (*global_init)(long) = nullptr;
    CURL* (*easy_init)() = nullptr;
    void (*easy_cleanup)(CURL*) = nullptr;
    CURLcode (*easy_setopt)(CURL*, CURLoption, ...) = nullptr;
    CURLcode (*easy_perform)(CURL*) = nullptr;
    CURLcode (*easy_getinfo)(CURL*, CURLINFO, ...) = nullptr;
    const char* (*easy_strerror)(CURLcode) = nullptr;
};

bool envIsOne(const char* name) {
    const char* value = std::getenv(name);
    return value != nullptr && std::strcmp(value, "1") == 0;
}

CurlApi loadCurl() {
    CurlApi api;
    void* handle = nullptr;
    for (const char* name : {"libcurl.so.4", "libcurl-gnutls.so.4"}) {
        handle = dlopen(name, RTLD_NOW | RTLD_LOCAL);
        if (handle != nullptr) break;
    }
    if (handle == nullptr) return api;
    const auto load = [handle](const char* symbol) { return dlsym(handle, symbol); };
    api.global_init = reinterpret_cast<CURLcode (*)(long)>(load("curl_global_init"));
    api.easy_init = reinterpret_cast<CURL* (*)()>(load("curl_easy_init"));
    api.easy_cleanup = reinterpret_cast<void (*)(CURL*)>(load("curl_easy_cleanup"));
    api.easy_setopt =
        reinterpret_cast<CURLcode (*)(CURL*, CURLoption, ...)>(load("curl_easy_setopt"));
    api.easy_perform = reinterpret_cast<CURLcode (*)(CURL*)>(load("curl_easy_perform"));
    api.easy_getinfo =
        reinterpret_cast<CURLcode (*)(CURL*, CURLINFO, ...)>(load("curl_easy_getinfo"));
    api.easy_strerror =
        reinterpret_cast<const char* (*)(CURLcode)>(load("curl_easy_strerror"));
    if (api.global_init == nullptr || api.easy_init == nullptr ||
        api.easy_cleanup == nullptr || api.easy_setopt == nullptr ||
        api.easy_perform == nullptr || api.easy_getinfo == nullptr ||
        api.easy_strerror == nullptr) {
        return CurlApi();
    }
    if (api.global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) return CurlApi();
    return api;
}

CurlApi& api() {
    static CurlApi instance = loadCurl();
    return instance;
}

bool startsWithIgnoreCase(const std::string& text, const char* prefix) {
    const std::size_t length = std::strlen(prefix);
    if (text.size() < length) return false;
    for (std::size_t index = 0; index < length; ++index) {
        char left = text[index];
        char right = prefix[index];
        if (left >= 'A' && left <= 'Z') left = static_cast<char>(left - 'A' + 'a');
        if (right >= 'A' && right <= 'Z') right = static_cast<char>(right - 'A' + 'a');
        if (left != right) return false;
    }
    return true;
}

struct TransferState {
    const HttpSink* sink = nullptr;
    const HttpProgress* progress = nullptr;
    std::uint64_t received = 0;
    std::uint64_t maxBytes = 0;
    HttpError error = HttpError::None;
    std::string message;
    int status = 0;
    bool forwarding = true;  // false while the response is a redirect or an error
};

size_t onWrite(char* data, size_t size, size_t count, void* userdata) {
    auto* state = static_cast<TransferState*>(userdata);
    const std::size_t bytes = size * count;
    state->received += bytes;
    if (state->maxBytes != 0 && state->received > state->maxBytes) {
        state->error = HttpError::TooLarge;
        state->message = "the response is larger than the allowed size";
        return 0;
    }
    if (!state->forwarding) return bytes;
    if (state->sink != nullptr && *state->sink) {
        if (!(*state->sink)(reinterpret_cast<const std::uint8_t*>(data), bytes)) {
            state->error = HttpError::Cancelled;
            state->message = "the download was cancelled";
            return 0;
        }
    }
    return bytes;
}

size_t onHeader(char* data, size_t size, size_t count, void* userdata) {
    auto* state = static_cast<TransferState*>(userdata);
    const std::size_t bytes = size * count;
    const std::string line(data, bytes);
    if (line.compare(0, 5, "HTTP/") == 0) {
        const std::size_t space = line.find(' ');
        if (space != std::string::npos) {
            state->status = std::atoi(line.c_str() + space + 1);
            state->forwarding = state->status == 200;
        }
    } else if (startsWithIgnoreCase(line, "content-length:")) {
        const std::uint64_t length =
            std::strtoull(line.c_str() + 15, nullptr, 10);
        if (state->maxBytes != 0 && length > state->maxBytes) {
            state->error = HttpError::TooLarge;
            state->message = "the server announced a body larger than the allowed size";
            return 0;
        }
    }
    return bytes;
}

int onProgress(void* userdata, curl_off_t totalDownload, curl_off_t downloaded,
               curl_off_t, curl_off_t) {
    auto* state = static_cast<TransferState*>(userdata);
    if (state->progress != nullptr && *state->progress) {
        const auto received =
            static_cast<std::uint64_t>(downloaded < 0 ? 0 : downloaded);
        const auto total =
            static_cast<std::uint64_t>(totalDownload < 0 ? 0 : totalDownload);
        if (!(*state->progress)(received, total)) {
            state->error = HttpError::Cancelled;
            state->message = "the download was cancelled";
            return 1;
        }
    }
    return 0;
}

void setProtocols(const CurlApi& curl, CURL* handle, bool allowHttp) {
    const char* list = allowHttp ? "https,http" : "https";
    if (curl.easy_setopt(handle, CURLOPT_PROTOCOLS_STR, list) == CURLE_UNKNOWN_OPTION) {
        // curl < 7.85 has only the bitmask options, which are deprecated in the headers
        // exactly because of the runtime this branch exists for.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        const long mask = CURLPROTO_HTTPS | (allowHttp ? CURLPROTO_HTTP : 0);
        curl.easy_setopt(handle, CURLOPT_PROTOCOLS, mask);
        curl.easy_setopt(handle, CURLOPT_REDIR_PROTOCOLS, mask);
#pragma GCC diagnostic pop
    }
}

HttpError mapCurl(CURLcode code) {
    switch (code) {
        case CURLE_UNSUPPORTED_PROTOCOL:
        case CURLE_URL_MALFORMAT:
            return HttpError::Refused;
        case CURLE_COULDNT_RESOLVE_PROXY:
        case CURLE_COULDNT_RESOLVE_HOST:
        case CURLE_COULDNT_CONNECT:
        case CURLE_SEND_ERROR:
        case CURLE_RECV_ERROR:
        case CURLE_GOT_NOTHING:
        case CURLE_PARTIAL_FILE:
            return HttpError::Network;
        case CURLE_OPERATION_TIMEDOUT:
            return HttpError::Timeout;
        case CURLE_SSL_CONNECT_ERROR:
        case CURLE_PEER_FAILED_VERIFICATION:
        case CURLE_SSL_CERTPROBLEM:
        case CURLE_SSL_CIPHER:
        case CURLE_SSL_ISSUER_ERROR:
        case CURLE_SSL_INVALIDCERTSTATUS:
            return HttpError::Tls;
        case CURLE_FILESIZE_EXCEEDED:
            return HttpError::TooLarge;
        case CURLE_ABORTED_BY_CALLBACK:
        case CURLE_WRITE_ERROR:
            return HttpError::Cancelled;
        default:
            return HttpError::Network;
    }
}

}  // namespace

HttpResult httpGet(const HttpRequest& request, const HttpSink& sink,
                   const HttpProgress& progress) {
    HttpResult result;
    std::string policyError;
    if (!allowedUrl(request.url, &policyError)) {
        result.error = HttpError::Refused;
        result.message = policyError;
        return result;
    }
    // The "libcurl is missing" test needs the test-only HTTP switch as well, so a release
    // build cannot reach it by accident.
    if (testHttpAllowed() && envIsOne("DAYBREAK_UPDATE_TEST_NO_CURL")) {
        result.error = HttpError::Unavailable;
        result.message =
            "updates need libcurl, which this system does not provide; download the "
            "release manually";
        return result;
    }
    CurlApi& curl = api();
    if (curl.easy_perform == nullptr) {
        result.error = HttpError::Unavailable;
        result.message =
            "updates need libcurl, which this system does not provide; download the "
            "release manually";
        return result;
    }
    CURL* handle = curl.easy_init();
    if (handle == nullptr) {
        result.error = HttpError::Unavailable;
        result.message = "libcurl could not create a request";
        return result;
    }
    struct Guard {
        const CurlApi* curl;
        CURL* handle;
        ~Guard() { curl->easy_cleanup(handle); }
    } guard{&curl, handle};

    const std::string agent = userAgent();
    std::string url = request.url;
    int redirects = 0;
    for (;;) {
        TransferState state;
        state.sink = &sink;
        state.progress = &progress;
        state.maxBytes = request.maxBytes;

        curl.easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl.easy_setopt(handle, CURLOPT_NOSIGNAL, 1L);
        // Followed below, hop by hop: curl's own follower cannot check each target.
        curl.easy_setopt(handle, CURLOPT_FOLLOWLOCATION, 0L);
        curl.easy_setopt(handle, CURLOPT_HTTPGET, 1L);
        curl.easy_setopt(handle, CURLOPT_CONNECTTIMEOUT,
                         static_cast<long>(request.connectTimeoutSeconds));
        curl.easy_setopt(handle, CURLOPT_LOW_SPEED_LIMIT, 1L);
        curl.easy_setopt(handle, CURLOPT_LOW_SPEED_TIME,
                         static_cast<long>(request.stallTimeoutSeconds));
        if (request.maxBytes != 0) {
            curl.easy_setopt(handle, CURLOPT_MAXFILESIZE_LARGE,
                             static_cast<curl_off_t>(request.maxBytes));
        }
        curl.easy_setopt(handle, CURLOPT_WRITEFUNCTION, &onWrite);
        curl.easy_setopt(handle, CURLOPT_WRITEDATA, &state);
        curl.easy_setopt(handle, CURLOPT_HEADERFUNCTION, &onHeader);
        curl.easy_setopt(handle, CURLOPT_HEADERDATA, &state);
        curl.easy_setopt(handle, CURLOPT_XFERINFOFUNCTION, &onProgress);
        curl.easy_setopt(handle, CURLOPT_XFERINFODATA, &state);
        curl.easy_setopt(handle, CURLOPT_NOPROGRESS, 0L);
        curl.easy_setopt(handle, CURLOPT_USERAGENT, agent.c_str());
        setProtocols(curl, handle, testHttpAllowed());

        const CURLcode code = curl.easy_perform(handle);
        if (state.error != HttpError::None) {
            result.error = state.error;
            result.status = state.status;
            result.message = state.message;
            return result;
        }
        if (code != CURLE_OK) {
            result.error = mapCurl(code);
            result.message = curl.easy_strerror(code);
            return result;
        }
        if (state.status >= 300 && state.status < 400) {
            if (redirects >= 5) {
                result.error = HttpError::Refused;
                result.message = "too many redirects";
                return result;
            }
            // curl resolved the Location header against the request URL for us; the
            // policy check below is still ours, on every hop.
            char* target = nullptr;
            if (curl.easy_getinfo(handle, CURLINFO_REDIRECT_URL, &target) != CURLE_OK ||
                target == nullptr) {
                result.error = HttpError::Refused;
                result.message = "the redirect has no target";
                return result;
            }
            const std::string next = target;
            std::string redirectError;
            if (!allowedUrl(next, &redirectError)) {
                result.error = HttpError::Refused;
                result.message = "redirect refused: " + redirectError;
                return result;
            }
            url = next;
            ++redirects;
            continue;
        }
        result.status = state.status;
        if (state.status != 200) {
            result.error = HttpError::Status;
            result.message = "the server answered " + std::to_string(state.status);
            return result;
        }
        return result;
    }
}

}  // namespace plat
