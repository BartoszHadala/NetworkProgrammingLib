#include "socket.hpp"

namespace bh {

    Socket::Socket(int family, int type, int protocol) {
        m_sockfd = ::socket(family, type, protocol);
            if (m_sockfd < 0) {
                throw std::runtime_error("Socket creation failed: " + std::string(std::strerror(errno)));
            }
    }

    Socket::Socket() : m_sockfd(-1) {}

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

    bool Socket::isValid() const {
        return m_sockfd >= 0;
    }

    Socket::operator bool() const {
        return isValid();
    }

    bool Socket::operator==(const Socket& other) const {
        return m_sockfd == other.m_sockfd;
    }

    bool Socket::operator!=(const Socket& other) const {
        return !(*this == other);
    }

}