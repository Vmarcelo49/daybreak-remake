#include "update_test_suites.h"

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "platform/http.h"

namespace {

using update_test::check;
using update_test::expect;

void setTestMode(bool enabled) {
    if (enabled) {
        setenv("DAYBREAK_UPDATE_TEST_HTTP", "1", 1);
    } else {
        unsetenv("DAYBREAK_UPDATE_TEST_HTTP");
    }
}

void testUrlPolicy() {
    std::string error;
    setTestMode(true);
    check(plat::allowedUrl("https://github.com/x", &error), "https is allowed");
    check(plat::allowedUrl("HTTPS://github.com/x", &error),
          "the scheme is case-insensitive");
    check(plat::allowedUrl("http://127.0.0.1:8080/x", &error),
          "loopback http is allowed in test mode");
    check(plat::allowedUrl("http://localhost:9/x", &error),
          "localhost is allowed in test mode");
    check(!plat::allowedUrl("http://example.com/x", &error),
          "a remote http host is refused even in test mode");
    check(!plat::allowedUrl("http://127.0.0.1/x", &error), "loopback needs a port");
    check(!plat::allowedUrl("ftp://example.com/x", &error), "ftp is refused");
    check(!plat::allowedUrl("https://user:pass@example.com/x", &error),
          "credentials are refused");
    check(!plat::allowedUrl("", &error), "an empty URL is refused");
    check(!plat::allowedUrl("https://example.com/a b", &error),
          "a space is refused");

    setTestMode(false);
    check(!plat::allowedUrl("http://127.0.0.1:8080/x", &error),
          "loopback http is refused without the test switch");
    setTestMode(true);
}

void testMissingCurl() {
    setTestMode(true);
    setenv("DAYBREAK_UPDATE_TEST_NO_CURL", "1", 1);
    plat::HttpRequest request;
    request.url = "https://example.com/x";
    const plat::HttpResult result = plat::httpGet(request, nullptr, nullptr);
    check(result.error == plat::HttpError::Unavailable,
          "a missing libcurl reports Unavailable");
    check(result.message.find("libcurl") != std::string::npos,
          "the message names libcurl: " + result.message);
    unsetenv("DAYBREAK_UPDATE_TEST_NO_CURL");
}

plat::HttpResult get(const std::string& url, std::uint64_t maxBytes,
                     std::string* body, int stallSeconds = 30) {
    plat::HttpRequest request;
    request.url = url;
    request.maxBytes = maxBytes;
    request.connectTimeoutSeconds = 5;
    request.stallTimeoutSeconds = stallSeconds;
    return plat::httpGet(
        request,
        [body](const std::uint8_t* data, std::size_t size) {
            if (body != nullptr) {
                body->append(reinterpret_cast<const char*>(data), size);
            }
            return true;
        },
        nullptr);
}

void testLiveServer(const std::string& base) {
    setTestMode(true);
    {
        std::string body;
        bool progressed = false;
        plat::HttpRequest request;
        request.url = base + "/ok";
        request.maxBytes = 1 << 20;
        const plat::HttpResult result = plat::httpGet(
            request,
            [&body](const std::uint8_t* data, std::size_t size) {
                body.append(reinterpret_cast<const char*>(data), size);
                return true;
            },
            [&progressed](std::uint64_t, std::uint64_t) {
                progressed = true;
                return true;
            });
        check(result.error == plat::HttpError::None && result.status == 200,
              "GET /ok is 200: " + result.message);
        expect(body, "hello update", "the body arrives");
        check(progressed, "progress was reported");
    }
    {
        std::string body;
        const plat::HttpResult result = get(base + "/redirect/3", 1 << 20, &body);
        check(result.error == plat::HttpError::None && result.status == 200,
              "a three-hop redirect chain lands: " + result.message);
        expect(body, "hello update", "the redirected body arrives");
    }
    {
        const plat::HttpResult result = get(base + "/redirect/6", 1 << 20, nullptr);
        check(result.error == plat::HttpError::Refused,
              "a redirect chain past the limit is refused: " + result.message);
    }
    {
        const plat::HttpResult result = get(base + "/missing", 1 << 20, nullptr);
        check(result.error == plat::HttpError::Status && result.status == 404,
              "404 reports Status with the code: " + result.message);
    }
    {
        const plat::HttpResult result = get(base + "/big", 1024, nullptr);
        check(result.error == plat::HttpError::TooLarge,
              "a Content-Length over maxBytes is TooLarge: " + result.message);
    }
    {
        const plat::HttpResult result = get(base + "/chunked", 1024, nullptr);
        check(result.error == plat::HttpError::TooLarge,
              "a streamed body over maxBytes is TooLarge: " + result.message);
    }
    {
        plat::HttpRequest request;
        request.url = base + "/slow";
        request.maxBytes = 1 << 20;
        std::uint64_t seen = 0;
        const plat::HttpResult result = plat::httpGet(
            request, [](const std::uint8_t*, std::size_t) { return true; },
            [&seen](std::uint64_t received, std::uint64_t) {
                // curl reports progress during connect too; cancel once bytes arrived.
                if (received == 0) return true;
                seen = received;
                return false;
            });
        check(result.error == plat::HttpError::Cancelled,
              "a progress callback that returns false cancels: " + result.message);
        check(seen > 0, "the cancel happened after data arrived");
    }
    {
        const plat::HttpResult result = get(base + "/stall", 1 << 20, nullptr, 1);
        check(result.error == plat::HttpError::Timeout,
              "a stalled body times out: " + result.message);
    }
    {
        setTestMode(false);
        const plat::HttpResult result = get(base + "/ok", 1 << 20, nullptr);
        check(result.error == plat::HttpError::Refused,
              "plain HTTP is refused when the test switch is off: " + result.message);
        setTestMode(true);
    }
}

}  // namespace

int main(int argc, char** argv) {
    testUrlPolicy();
    testMissingCurl();
    if (argc < 2) {
        std::fprintf(stderr, "usage: update_http_test <base-url>\n");
        return 2;
    }
    testLiveServer(argv[1]);
    return update_test::report("update_http_test");
}
