// platform/http_winhttp.cpp — the Windows HTTP client, on the WinHTTP already in the OS.
//
// Why WinHTTP: it uses the system certificate store and proxy settings and adds no shipped
// bytes. Its automatic redirects are kept, but downgraded with
// WINHTTP_OPTION_REDIRECT_POLICY_DISALLOW_HTTPS_TO_HTTP and bounded by
// WINHTTP_OPTION_MAX_HTTP_AUTOMATIC_REDIRECTS, so an https -> http hop fails instead of
// downloading over plain HTTP.
//
// URLs and error text go through UTF-16 because the game folder can have a non-English
// name; the interface itself stays UTF-8 like the rest of the tree.
#include "platform/http.h"

#include <windows.h>
#include <winhttp.h>

#include <string>
#include <vector>

#ifndef WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY
#define WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY 4  // Windows 8.1; older systems use the default
#endif

namespace plat {
namespace {

std::wstring widen(const std::string& text) {
    if (text.empty()) return std::wstring();
    const int length = MultiByteToWideChar(CP_UTF8, 0, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0);
    if (length <= 0) return std::wstring();
    std::wstring wide(static_cast<std::size_t>(length), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
                        wide.data(), length);
    return wide;
}

std::string narrow(const std::wstring& text) {
    if (text.empty()) return std::string();
    const int length = WideCharToMultiByte(CP_UTF8, 0, text.data(),
                                           static_cast<int>(text.size()), nullptr, 0,
                                           nullptr, nullptr);
    if (length <= 0) return std::string();
    std::string utf8(static_cast<std::size_t>(length), '\0');
    WideCharToMultiByte(CP_UTF8, 0, text.data(), static_cast<int>(text.size()),
                        utf8.data(), length, nullptr, nullptr);
    return utf8;
}

struct Handle {
    HINTERNET value = nullptr;
    ~Handle() {
        if (value != nullptr) WinHttpCloseHandle(value);
    }
    Handle() = default;
    Handle(const Handle&) = delete;
    Handle& operator=(const Handle&) = delete;
};

HttpError mapError(DWORD code) {
    switch (code) {
        case ERROR_WINHTTP_TIMEOUT:
            return HttpError::Timeout;
        case ERROR_WINHTTP_SECURE_FAILURE:
        case ERROR_WINHTTP_SECURE_CERT_CN_INVALID:
        case ERROR_WINHTTP_SECURE_CERT_DATE_INVALID:
        case ERROR_WINHTTP_SECURE_CERT_REV_FAILED:
        case ERROR_WINHTTP_SECURE_CERT_WRONG_USAGE:
        case ERROR_WINHTTP_SECURE_CHANNEL_ERROR:
        case ERROR_WINHTTP_SECURE_INVALID_CA:
        case ERROR_WINHTTP_SECURE_INVALID_CERT:
            return HttpError::Tls;
        case ERROR_WINHTTP_INVALID_URL:
        case ERROR_WINHTTP_UNRECOGNIZED_SCHEME:
        case ERROR_WINHTTP_REDIRECT_FAILED:
            return HttpError::Refused;
        case ERROR_WINHTTP_NAME_NOT_RESOLVED:
        case ERROR_WINHTTP_CANNOT_CONNECT:
        case ERROR_WINHTTP_CONNECTION_ERROR:
        case ERROR_WINHTTP_RESPONSE_DRAIN_OVERFLOW:
        case ERROR_WINHTTP_INVALID_SERVER_RESPONSE:
            return HttpError::Network;
        default:
            return HttpError::Network;
    }
}

HttpResult fail(DWORD code, const char* what) {
    HttpResult result;
    result.error = mapError(code);
    result.message = std::string(what) + " (WinHTTP error " + std::to_string(code) + ")";
    return result;
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

    const std::wstring wideUrl = widen(request.url);
    URL_COMPONENTS components{};
    components.dwStructSize = sizeof components;
    components.dwSchemeLength = static_cast<DWORD>(-1);
    components.dwHostNameLength = static_cast<DWORD>(-1);
    components.dwUrlPathLength = static_cast<DWORD>(-1);
    components.dwExtraInfoLength = static_cast<DWORD>(-1);
    if (!WinHttpCrackUrl(wideUrl.c_str(), 0, 0, &components)) {
        result.error = HttpError::Refused;
        result.message = "the URL could not be parsed";
        return result;
    }
    const std::wstring host(components.lpszHostName, components.dwHostNameLength);
    std::wstring object(components.lpszUrlPath, components.dwUrlPathLength);
    if (components.dwExtraInfoLength != 0) {
        object.append(components.lpszExtraInfo, components.dwExtraInfoLength);
    }
    const bool secure = components.nScheme == INTERNET_SCHEME_HTTPS;

    const std::wstring agent = widen(userAgent());
    Handle session;
    session.value = WinHttpOpen(agent.c_str(), WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
                                WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (session.value == nullptr) {
        // Before Windows 8.1 there is no automatic-proxy access type.
        session.value = WinHttpOpen(agent.c_str(), WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                                    WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    }
    if (session.value == nullptr) return fail(GetLastError(), "WinHTTP could not start");

    const int connectMs = request.connectTimeoutSeconds > 0
                              ? request.connectTimeoutSeconds * 1000
                              : 15000;
    const int stallMs =
        request.stallTimeoutSeconds > 0 ? request.stallTimeoutSeconds * 1000 : 30000;
    WinHttpSetTimeouts(session.value, connectMs, connectMs, stallMs, stallMs);

    Handle connection;
    connection.value =
        WinHttpConnect(session.value, host.c_str(), components.nPort, 0);
    if (connection.value == nullptr) {
        return fail(GetLastError(), "WinHTTP could not connect");
    }
    Handle exchange;
    exchange.value = WinHttpOpenRequest(
        connection.value, L"GET", object.c_str(), nullptr, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, secure ? WINHTTP_FLAG_SECURE : 0);
    if (exchange.value == nullptr) return fail(GetLastError(), "WinHTTP could not open the request");

    DWORD redirectPolicy = WINHTTP_OPTION_REDIRECT_POLICY_DISALLOW_HTTPS_TO_HTTP;
    WinHttpSetOption(exchange.value, WINHTTP_OPTION_REDIRECT_POLICY, &redirectPolicy,
                     sizeof redirectPolicy);
    DWORD maxRedirects = 5;
    WinHttpSetOption(exchange.value, WINHTTP_OPTION_MAX_HTTP_AUTOMATIC_REDIRECTS,
                     &maxRedirects, sizeof maxRedirects);
    DWORD protocols = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
#ifdef WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3
    protocols |= WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3;
#endif
    WinHttpSetOption(exchange.value, WINHTTP_OPTION_SECURE_PROTOCOLS, &protocols,
                     sizeof protocols);

    if (!WinHttpSendRequest(exchange.value, WINHTTP_NO_ADDITIONAL_HEADERS, 0,
                            WINHTTP_NO_REQUEST_DATA, 0, 0, 0)) {
        return fail(GetLastError(), "WinHTTP could not send the request");
    }
    if (!WinHttpReceiveResponse(exchange.value, nullptr)) {
        return fail(GetLastError(), "WinHTTP received no response");
    }

    DWORD status = 0;
    DWORD statusSize = sizeof status;
    if (!WinHttpQueryHeaders(exchange.value,
                             WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                             WINHTTP_HEADER_NAME_BY_INDEX, &status, &statusSize,
                             WINHTTP_NO_HEADER_INDEX)) {
        return fail(GetLastError(), "WinHTTP did not report a status");
    }
    result.status = static_cast<int>(status);

    std::uint64_t total = 0;
    wchar_t lengthText[32] = {};
    DWORD lengthSize = sizeof lengthText;
    if (WinHttpQueryHeaders(exchange.value, WINHTTP_QUERY_CONTENT_LENGTH,
                            WINHTTP_HEADER_NAME_BY_INDEX, lengthText, &lengthSize,
                            WINHTTP_NO_HEADER_INDEX)) {
        total = std::strtoull(narrow(lengthText).c_str(), nullptr, 10);
        if (request.maxBytes != 0 && total > request.maxBytes) {
            result.error = HttpError::TooLarge;
            result.message = "the server announced a body larger than the allowed size";
            return result;
        }
    }

    if (status != 200) {
        result.error = HttpError::Status;
        result.message = "the server answered " + std::to_string(status);
        return result;
    }

    std::vector<std::uint8_t> buffer(64 * 1024);
    std::uint64_t received = 0;
    for (;;) {
        DWORD read = 0;
        if (!WinHttpReadData(exchange.value, buffer.data(),
                             static_cast<DWORD>(buffer.size()), &read)) {
            return fail(GetLastError(), "WinHTTP could not read the body");
        }
        if (read == 0) break;
        received += read;
        if (request.maxBytes != 0 && received > request.maxBytes) {
            result.error = HttpError::TooLarge;
            result.message = "the response is larger than the allowed size";
            return result;
        }
        if (progress && !progress(received, total)) {
            result.error = HttpError::Cancelled;
            result.message = "the download was cancelled";
            return result;
        }
        if (sink && !sink(buffer.data(), read)) {
            result.error = HttpError::Cancelled;
            result.message = "the download was cancelled";
            return result;
        }
    }
    return result;
}

}  // namespace plat
