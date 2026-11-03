#pragma once
// platform/http.h — one blocking HTTPS GET, the updater's only network primitive (#100).
//
// Why a seam: Windows carries WinHTTP in the OS, while Linux desktops ship libcurl but do
// not promise a linkable development package. So each platform implements this header
// (http_winhttp.cpp / http_curl.cpp) and nothing else in the tree knows which one it got.
//
// Two properties are part of the interface, not of an implementation:
//   * it is safe to call from a worker thread (step 4 runs the check off the main thread);
//   * cancelling through the progress callback stops the transfer promptly.
//
// The URL policy is shared (http_policy.cpp) so both platforms refuse the same things:
// https only, every redirect hop included, with one test-only exception for the local
// CTest fixture (docs/AUTO-UPDATE.md).
#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>

namespace plat {

struct HttpRequest {
    std::string url;
    std::uint64_t maxBytes = 0;  // 0 = no limit; a larger body is refused
    int connectTimeoutSeconds = 15;
    int stallTimeoutSeconds = 30;  // no bytes for this long is a timeout
};

enum class HttpError {
    None,
    Unavailable,  // no HTTP implementation on this machine: the player downloads manually
    Network,
    Tls,
    Timeout,
    Status,  // the server answered, but not 200
    TooLarge,
    Cancelled,
    Refused,  // the URL or a redirect hop is not allowed
};

struct HttpResult {
    HttpError error = HttpError::None;
    int status = 0;
    std::string message;
};

using HttpSink = std::function<bool(const std::uint8_t*, std::size_t)>;
using HttpProgress = std::function<bool(std::uint64_t received, std::uint64_t total)>;

// Streams the body into `sink`; `progress` returns false to cancel. Either may be empty.
HttpResult httpGet(const HttpRequest& request, const HttpSink& sink,
                   const HttpProgress& progress);

// True when DAYBREAK_UPDATE_TEST_HTTP=1 is set: the CTest fixture's plain-HTTP exception.
bool testHttpAllowed();

// https:// anywhere; http:// only for 127.0.0.1:<port> or localhost:<port> in test mode.
bool allowedUrl(const std::string& url, std::string* error);

// Resolves a Location header against the request URL (the Linux client follows redirects
// itself so every hop goes through allowedUrl; WinHTTP applies its own policy).
std::string resolveRedirect(const std::string& base, const std::string& location);

// "daybreak-remake/<VERSION>", the one header the server sees.
std::string userAgent();

}  // namespace plat
