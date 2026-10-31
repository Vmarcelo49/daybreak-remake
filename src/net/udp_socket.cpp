#include "net/udp_socket.h"

#include <cstdio>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
using SocketHandle = SOCKET;
static constexpr SocketHandle kNoSocket = INVALID_SOCKET;
#else
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
using SocketHandle = int;
static constexpr SocketHandle kNoSocket = -1;
#endif

namespace net {

namespace {

constexpr size_t kProxyPrefix = 6;
constexpr size_t kMaxPacket = 1472 + kProxyPrefix;  // what fits one Ethernet frame, and the prefix

void put_address(std::uint8_t* out, const Address& address) {
    std::memcpy(out, &address.ip, 4);
    out[4] = static_cast<std::uint8_t>(address.port >> 8);
    out[5] = static_cast<std::uint8_t>(address.port);
}

Address get_address(const std::uint8_t* in) {
    Address address;
    std::memcpy(&address.ip, in, 4);
    address.port = static_cast<std::uint16_t>((in[4] << 8) | in[5]);
    return address;
}

}  // namespace

bool parse_address(const std::string& text, Address& out) {
    unsigned a, b, c, d, port;
    char end;
    if (std::sscanf(text.c_str(), "%u.%u.%u.%u:%u%c", &a, &b, &c, &d, &port, &end) != 5) return false;
    if (a > 255 || b > 255 || c > 255 || d > 255 || port == 0 || port > 65535) return false;
    const std::uint8_t bytes[4] = {static_cast<std::uint8_t>(a), static_cast<std::uint8_t>(b),
                                   static_cast<std::uint8_t>(c), static_cast<std::uint8_t>(d)};
    std::memcpy(&out.ip, bytes, 4);
    out.port = static_cast<std::uint16_t>(port);
    return true;
}

struct UdpSocket::Impl {
    SocketHandle handle = kNoSocket;
    std::uint16_t port = 0;
};

UdpSocket::UdpSocket() : m_impl(std::make_unique<Impl>()) {
#ifdef _WIN32
    WSADATA data;
    WSAStartup(MAKEWORD(2, 2), &data);
#endif
}

UdpSocket::~UdpSocket() {
    if (m_impl->handle != kNoSocket) {
#ifdef _WIN32
        closesocket(m_impl->handle);
#else
        close(m_impl->handle);
#endif
    }
#ifdef _WIN32
    WSACleanup();
#endif
}

bool UdpSocket::open(std::uint16_t port, std::string& error) {
    m_impl->handle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_impl->handle == kNoSocket) {
        error = "net: no socket";
        return false;
    }
#ifdef _WIN32
    u_long nonBlocking = 1;
    ioctlsocket(m_impl->handle, FIONBIO, &nonBlocking);
#else
    fcntl(m_impl->handle, F_SETFL, fcntl(m_impl->handle, F_GETFL, 0) | O_NONBLOCK);
#endif
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(port);
    if (bind(m_impl->handle, reinterpret_cast<const sockaddr*>(&address), sizeof address) != 0) {
        error = "net: cannot bind port " + std::to_string(port);
        return false;
    }
    socklen_t length = sizeof address;
    getsockname(m_impl->handle, reinterpret_cast<sockaddr*>(&address), &length);
    m_impl->port = ntohs(address.sin_port);
    return true;
}

std::uint16_t UdpSocket::port() const { return m_impl->port; }

void UdpSocket::send(const Address& to, const void* data, size_t size) {
    std::uint8_t packet[kMaxPacket];
    size_t prefix = 0;
    if (m_proxied) {
        put_address(packet, to);
        prefix = kProxyPrefix;
    }
    if (size + prefix > sizeof packet) return;
    std::memcpy(packet + prefix, data, size);
    const Address target = m_proxied ? m_proxy : to;
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = target.ip;
    address.sin_port = htons(target.port);
    // UDP may lose anything, so a failed send is the same as a lost packet.
    sendto(m_impl->handle, reinterpret_cast<const char*>(packet), static_cast<int>(size + prefix), 0,
           reinterpret_cast<const sockaddr*>(&address), sizeof address);
}

bool UdpSocket::receive(Address& from, std::vector<std::uint8_t>& data) {
    std::uint8_t packet[kMaxPacket];
    for (;;) {
        sockaddr_in address{};
        socklen_t length = sizeof address;
        const auto received = recvfrom(m_impl->handle, reinterpret_cast<char*>(packet), sizeof packet, 0,
                                       reinterpret_cast<sockaddr*>(&address), &length);
        if (received < 0) {
#ifdef _WIN32
            // A peer that left answers with a port-unreachable, reported here. Keep reading.
            if (WSAGetLastError() == WSAECONNRESET) continue;
#endif
            return false;
        }
        size_t skip = 0;
        if (m_proxied) {
            if (static_cast<size_t>(received) < kProxyPrefix) continue;
            from = get_address(packet);
            skip = kProxyPrefix;
        } else {
            from.ip = address.sin_addr.s_addr;
            from.port = ntohs(address.sin_port);
        }
        data.assign(packet + skip, packet + received);
        return true;
    }
}

}  // namespace net
