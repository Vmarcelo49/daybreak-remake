#include "platform/http.h"

#include <cstdlib>
#include <cstring>

#ifndef DAYBREAK_UPDATE_VERSION
#define DAYBREAK_UPDATE_VERSION "unknown"
#endif

namespace plat {
namespace {

bool fail(std::string* error, const std::string& message) {
    if (error != nullptr) *error = message;
    return false;
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

// "127.0.0.1:8080" / "localhost:8080", with a port a server could actually listen on.
bool loopbackAuthority(const std::string& authority) {
    std::string host = authority;
    const std::size_t colon = host.find(':');
    if (colon == std::string::npos) return false;
    const std::string port = host.substr(colon + 1);
    host = host.substr(0, colon);
    if (host != "127.0.0.1" && host != "localhost") return false;
    if (port.empty() || port.size() > 5) return false;
    for (const char character : port) {
        if (character < '0' || character > '9') return false;
    }
    const long value = std::strtol(port.c_str(), nullptr, 10);
    return value >= 1 && value <= 65535;
}

std::string authority(const std::string& url, std::size_t schemeEnd) {
    const std::size_t start = schemeEnd + 3;
    std::size_t end = url.size();
    for (const char separator : {'/', '?', '#'}) {
        const std::size_t found = url.find(separator, start);
        if (found != std::string::npos && found < end) end = found;
    }
    return url.substr(start, end - start);
}

}  // namespace

bool testHttpAllowed() {
    const char* value = std::getenv("DAYBREAK_UPDATE_TEST_HTTP");
    return value != nullptr && std::strcmp(value, "1") == 0;
}

bool testLoopbackUrl(const std::string& url) {
    if (!startsWithIgnoreCase(url, "http://")) return false;
    const std::size_t schemeEnd = url.find("://");
    return loopbackAuthority(authority(url, schemeEnd));
}

std::string userAgent() {
    return std::string("daybreak-remake/") + DAYBREAK_UPDATE_VERSION;
}

bool allowedUrl(const std::string& url, std::string* error) {
    if (url.empty()) return fail(error, "empty URL");
    for (const char character : url) {
        const unsigned char value = static_cast<unsigned char>(character);
        if (value <= 0x20 || value == 0x7F) {
            return fail(error, "the URL contains a control character or a space");
        }
    }
    if (startsWithIgnoreCase(url, "https://")) {
        const std::size_t schemeEnd = url.find("://");
        const std::string host = authority(url, schemeEnd);
        if (host.empty()) return fail(error, "the URL has no host");
        if (host.find('@') != std::string::npos) {
            return fail(error, "the URL carries credentials");
        }
        return true;
    }
    if (startsWithIgnoreCase(url, "http://")) {
        if (!testHttpAllowed()) {
            return fail(error,
                        "plain HTTP is refused; updates are downloaded over HTTPS only");
        }
        const std::size_t schemeEnd = url.find("://");
        const std::string host = authority(url, schemeEnd);
        if (host.find('@') != std::string::npos) {
            return fail(error, "the URL carries credentials");
        }
        if (!loopbackAuthority(host)) {
            return fail(error,
                        "plain HTTP is only allowed for the local test server "
                        "(127.0.0.1 or localhost)");
        }
        return true;
    }
    return fail(error, "the URL must start with https://");
}

}  // namespace plat
