#pragma once
// One non-blocking UDP socket, carrying every online packet of a session.
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace net {

struct Address {
    std::uint32_t ip = 0;  // network order
    std::uint16_t port = 0;  // host order
    bool operator==(const Address& other) const { return ip == other.ip && port == other.port; }
};
bool parse_address(const std::string& text, Address& out);

class UdpSocket {
public:
    UdpSocket();
    ~UdpSocket();
    UdpSocket(const UdpSocket&) = delete;
    UdpSocket& operator=(const UdpSocket&) = delete;

    // Port 0 picks a free one. False with `error` set when the port cannot be bound.
    bool open(std::uint16_t port, std::string& error);
    std::uint16_t port() const;
    void send(const Address& to, const void* data, size_t size);
    // False when nothing is waiting.
    bool receive(Address& from, std::vector<std::uint8_t>& data);
    // Verification: every packet goes through tools/net_proxy.py, addressed in a 6-byte prefix.
    void use_proxy(const Address& proxy) { m_proxy = proxy; m_proxied = true; }

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
    Address m_proxy;
    bool m_proxied = false;
};

}  // namespace net
