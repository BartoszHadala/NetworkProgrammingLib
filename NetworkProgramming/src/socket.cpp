#include "socket.hpp"

namespace bh {

    Socket::Socket(int family, int type, int protocol) {
        m_sockfd = socket(family, type, protocol);
            if (m_sockfd < 0) {
                throw std::runtime_error("Socket creation failed: " + std::string(std::strerror(errno)));
            }
    }

    Socket::~Socket() {
        if (m_sockfd != -1) {
            close();
        }
    }

    void Socket::close() {
        if (m_sockfd != -1) {
            if (::close(m_sockfd) < 0) {
                throw std::runtime_error("Socket close failed: " + std::string(std::strerror(errno)));
            }
            m_sockfd = -1;
        }
    }

    int Socket::getDescriptor() const {
        return m_sockfd;
}


}