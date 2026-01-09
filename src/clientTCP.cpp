#include "clientTCP.hpp"
#include <cstring>
#include <cerrno>

namespace bh {

    ClientTCP::ClientTCP() : m_socket(AF_INET, SOCK_STREAM, 0) {}

    void ClientTCP::connect(const char* ip, uint16_t port) {
        struct sockaddr_in servaddr;
        std::memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(port);
        
        if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0) {
            throw std::runtime_error("Invalid IP address: " + std::string(ip));
        }
        
        if (::connect(m_socket.getDescriptor(), (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
            throw std::runtime_error("TCPClient connect error: " + std::string(std::strerror(errno)));
        }
    }

}